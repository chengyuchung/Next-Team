/*!
    \file    app_tasks.c
    \brief   FreeRTOS 任务框架与 IPC 管理 (GD32A7xx 热管理系统)

    \note    本文件职责：
             1) 创建和管理 FreeRTOS 任务（init/app/temp/guard/can_rx）
             2) 创建和管理 IPC 资源（信号量、队列）
             3) 注册按键回调处理
             4) CAN 命令分发（需要访问任务间 IPC）
             5) 管理全局运行时配置参数

             业务逻辑已拆分到独立模块：
               - MCAL/actor_hal.c       : 执行器硬件抽象层
               - BSW/Services/sensor_manager.c : 传感器数据聚合与缓存
               - App/thermal_control.c  : 热管理状态机与控制逻辑
               - App/power_mode.c       : 低功耗模式管理
               - App/ignition_control.c : 点火控制逻辑

             任务架构：
               init_task    : 板级初始化 → 创建 IPC 与任务 → 进入 guard → 自删除
               app_task     : 正常模式周期控制循环（调用 thermal_control）
               temp_task    : 后台温度采集任务（分阶段避免阻塞控制循环）
               guard_task   : 低功耗巡检模式（长睡眠 / 巡检交替）
               can_rx_task  : 解析 CAN 请求帧（查询/控制/配置 → ACK）

             KEY_3 -> 点火切换 (PF0)，guard 模式下忽略；
             KEY_4 -> guard / 正常模式切换，也用于把系统从 tickless idle 唤醒；
             CAN RX -> can_rx_task 解析报文；guard 模式下只有收到
                       CAN_CTL_POWER_ON 控制命令才会唤醒 guard_task 退出
                       guard（其余报文正常收发 ACK，但不影响低功耗状态）。
*/

#include "gd32a7xx.h"
#include "gd32a712_evb.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include <string.h>

#include "main.h"
#include "app_tasks.h"

#include "can_app.h"

/* ============================================================
 *  FreeRTOS hook implementations (required by FreeRTOSConfig.h)
 * ============================================================ */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    /* Stack overflow detected: disable interrupts and halt.
     * Attach a debugger and inspect pcTaskName to identify the offending task.
     * Consider increasing the stack size via the APP/GUARD/CANRX_TASK_STACK macros. */
    taskDISABLE_INTERRUPTS();
    for( ;; ) {}
}

void vApplicationMallocFailedHook(void)
{
    /* Heap exhausted: disable interrupts and halt.
     * Increase configTOTAL_HEAP_SIZE in FreeRTOSConfig.h if this is hit. */
    taskDISABLE_INTERRUPTS();
    for( ;; ) {}
}

/* ============================================================================
 * 架构分层说明 (重构后的模块组织)
 * ============================================================================
 *
 * 本系统采用分层架构，按照 AUTOSAR 风格组织代码：
 *
 * 1. MCAL (Microcontroller Abstraction Layer) - 硬件抽象层
 *    - actor_hal.c         : GPIO 执行器统一接口（制冷/加热/蜂鸣器/排气阀）
 *    - adc_manager.c       : ADC 多通道管理（压力/气体传感器）
 *    - can_driver.c        : CAN 驱动封装
 *    - key.c               : 按键中断管理（KEY_3 点火 / KEY_4 guard 模式）
 *
 * 2. BSW/EcuAL (ECU Abstraction Layer) - ECU 抽象层
 *    - temp_sensor.c       : DS18B20 温度传感器驱动
 *    - pressure_sensor.c   : 压力传感器数据处理
 *    - gas_sensor.c        : 气体传感器数据处理
 *
 * 3. BSW/Services (Basic Software Services) - 基础软件服务层
 *    - sensor_manager.c    : 传感器数据聚合与缓存管理
 *    - system_state.c      : 热管理状态机（NORMAL/LOW_TEMP/HIGH_TEMP/DANGER）
 *    - fault_manager.c     : 故障记录与管理
 *    - can_protocol.c      : CAN 协议栈（帧打包/解析）
 *
 * 4. App (Application Layer) - 应用层
 *    - thermal_control.c   : 热控制业务逻辑（状态机更新 + 执行器驱动）
 *    - power_mode.c        : 低功耗模式管理（guard 模式进入/退出）
 *    - ignition_control.c  : 点火控制逻辑（按键 + CAN 命令 + 安全检查）
 *    - can_app.c           : CAN 应用层（查询命令处理 + 数据上报）
 *    - app_tasks.c (本文件): 任务框架与 IPC 管理
 *
 * 数据流示例：
 *   温度采集: temp_sensor (EcuAL) → sensor_manager (BSW) → thermal_control (App)
 *   执行器控制: thermal_control (App) → actor_hal (MCAL) → GPIO 寄存器
 *   状态上报: system_state (BSW) → can_app (App) → can_protocol (BSW) → can_driver (MCAL)
 *
 * ============================================================================ */

#include "watchdog.h"
#include "BSW/EcuAL/pressure_sensor.h"
#include "BSW/EcuAL/gas_sensor.h"
#include "BSW/EcuAL/temp_sensor.h"
#include "MCAL/adc_manager.h"
#include "motor_pwm_gd32.h"
#include "relay_power.h"
#include "MCAL/actor_hal.h"
#include "key.h"
#include "BSW/Services/system_state.h"
#include "BSW/Services/fault_manager.h"
#include "BSW/Services/sensor_manager.h"
#include "App/thermal_control.h"
#include "App/power_mode.h"
#include "App/ignition_control.h"

/* ---- task priorities (configMAX_PRIORITIES == 8) ----------------------
 * INIT_TASK 优先级必须高于所有应用任务，确保初始化完成后再让应用任务运行，
 * 避免 guard_task 在 s_guard_mode_active 设置前就抢占并进入"等待进入 guard"的分支。
 * 
 * TEMP_TASK 优先级高于 APP_TASK：DS18B20 的 1-Wire 位时序对延时极敏感
 * （读采样窗口 ~15us），若被 app_task 抢占会破坏位时序导致 CRC 失败。
 * 让温度任务优先级更高，可保证它短促的位操作突发不被 app_task 打断；
 * 而 750ms 的转换等待用 vTaskDelay 让出 CPU，因此不会饿死 app_task。 */
#define INIT_TASK_PRIO       ( tskIDLE_PRIORITY + 4 )
#define APP_TASK_PRIO        ( tskIDLE_PRIORITY + 2 )
#define GUARD_TASK_PRIO      ( tskIDLE_PRIORITY + 2 )
#define TEMP_TASK_PRIO       ( tskIDLE_PRIORITY + 3 )
#define IGNITION_TASK_PRIO   ( tskIDLE_PRIORITY + 3 )
#define CAN_RX_TASK_PRIO     ( tskIDLE_PRIORITY + 3 )

/* ---- task stack sizes (in words) -------------------------------------- */
#define APP_TASK_STACK       ( configMINIMAL_STACK_SIZE * 4 )
#define GUARD_TASK_STACK     ( configMINIMAL_STACK_SIZE * 4 )
#define TEMP_TASK_STACK      ( configMINIMAL_STACK_SIZE * 2 )
#define IGNITION_TASK_STACK  ( configMINIMAL_STACK_SIZE * 2 )
#define CAN_RX_TASK_STACK    ( configMINIMAL_STACK_SIZE * 4 )

/* ---- application timing -----------------------------------------------
 * 100ms 控制周期：对电池包热管理这类大惯性系统，10Hz 已足够快，
 * 相比 20ms 大幅降低 CPU 占用与调度开销，也给 tickless idle 更多机会。 */
#define APP_TASK_PERIOD_MS   ( 500U )

/* 温度采集周期：DS18B20 12bit 转换约需 750ms，取 1000ms 留余量。
 * 温度是大惯性物理量，1Hz 采样对电池包热管理足够；温度趋势预测
 * 也是基于真实采样间隔算斜率，与该周期一致。 */
#define TEMP_SAMPLE_PERIOD_MS       ( 1000U )
#define TEMP_CONVERSION_WAIT_MS     ( 780U )  /* 启动转换后让出 CPU 的等待时间 */

/* 运行时可配置参数定义（通过 CAN 0x20 配置类命令动态修改） */
uint32_t g_app_task_period_ms         = APP_TASK_PERIOD_MS;
uint32_t g_guard_sleep_interval_ms    = 15U * 1000U;  /* 自适应长睡眠的基准值/上限参考 */
uint32_t g_guard_handling_budget_ms   = 30U * 1000U;  /* 巡检异常处理后，NORMAL 持续确认时长 */

/* 自适应长睡眠时长：guard_task 每次全新进入 guard 模式时，从
 * g_guard_sleep_interval_ms 这个基准值重新开始；此后每完成一次巡检唤醒：
 *   - 本轮巡检期间只要出现过非 NORMAL 状态 -> 下一轮睡眠时长缩短 10%
 *     （连续异常会持续缩短，越危险醒得越勤）；
 *   - 本轮巡检从头到尾都是 NORMAL           -> 下一轮睡眠时长增加 20%
 *     （逐步恢复到基准，且无上限——按需求只约束下限）；
 *   - 下限固定为 GUARD_ADAPTIVE_SLEEP_MIN_MS，不受 g_guard_sleep_interval_ms
 *     配置值影响。 */
#define GUARD_ADAPTIVE_SLEEP_MIN_MS   (  5U * 1000U )
#define GUARD_ADAPTIVE_SHRINK_PCT     ( 90U )   /* 缩短 10%：乘以 90% */
#define GUARD_ADAPTIVE_GROW_PCT       ( 120U )  /* 增加 20%：乘以 120% */
static uint32_t s_guard_current_sleep_interval_ms = 15U * 1000U;

/* ---- guard (低功耗巡检) mode timing ------------------------------------
 * KEY_4 切换进入/退出 guard 巡检模式：
 *   - 上电默认处于 guard 模式：relay_power_init(0U) 把 PG0 置低，
 *     外设整体断电；app_task 被挂起，guard_task 在 tickless idle 中休眠；
 *   - 用户按一次 KEY_4：guard_key1_sem 触发 -> power_mode_exit_guard() ->
 *     relay_power_on() -> vTaskResume(app_task)，系统进入正常运行模式；
 *   - 正常运行模式下，guard_task 每 g_guard_sleep_interval_ms 醒来一次
 *     （不过此时仅作超时检测，因为 s_guard_mode_active == 0）；
 *   - 用户再次按 KEY_4：power_mode_enter_guard() -> relay_power_off() ->
 *     vTaskSuspend(app_task)，回到 guard 模式；
 *   - 每次"定时唤醒 + 外设上电 + 跑 GUARD_PATROL_DURATION_MS 的巡检循环"
 *     的能力保留：guard_task 检测到任何非 NORMAL 状态就会临时拉高
 *     relay_power 并执行 actuator 动作；
 *   - 巡检内部按状态机决定行为：
 *       state == NORMAL           -> 巡检结束，关电，进入下一轮长睡；
 *       state == PRE/WARNING/DANGER -> 持续执行状态机分支 (风扇/泵/加热/制冷/
 *                                      蜂鸣/门)；持续处理直到回到 NORMAL 并保持
 *                                      g_guard_handling_budget_ms 时长才允许断电，
 *                                      不设超时上限（处理到底）；
 *   - 唤醒源：KEY_4 任意时刻按下立刻退出 guard；CAN 侧仅当收到
 *     CAN_CTL_POWER_ON 控制命令时才会退出 guard（can_handle_control()
 *     内部按当前模式触发 s_guard_key1_sem，不是 ISR 里盲醒）；
 *     KEY_3 只翻点火，不参与 guard 唤醒。 */
#define GUARD_PATROL_DURATION_MS    (  5U * 1000U )  /* 每次唤醒后的巡检持续时长 */
#define GUARD_PATROL_PERIOD_MS      ( APP_TASK_PERIOD_MS ) /* 巡检内部采样周期，与 app_task 保持一致 */
#define GUARD_POWER_ON_SETTLE_MS   ( 50U )          /* PG0 继电器上电到外设可用的稳定延时 */

/* ============================================================
 *  IPC objects (created in init_task, referenced by key callbacks)
 * ============================================================ */
static SemaphoreHandle_t s_ignition_sem   = NULL;
QueueHandle_t     can4_rx_queue  = NULL;

/* given by key callback (KEY_4) on every press, and additionally by
 * can_handle_control() when a CAN_CTL_POWER_ON command is received while
 * guard mode is active (see the CAN_CTL_POWER_ON case below). guard_task
 * blocks on it with a timeout so the idle task can enter tickless sleep,
 * and any give wakes guard_task immediately to enter or exit guard mode.
 * KEY_3 (EXTI4) drives s_ignition_sem instead and does not participate
 * in guard wakeup. */
static SemaphoreHandle_t s_guard_key1_sem = NULL;

#define CAN4_RX_QUEUE_LEN    ( 8U )

/* ---- flags defined elsewhere ------------------------------------------ */
extern volatile uint8_t g_system_state_changed_flag;   /* can.c */
extern volatile uint8_t g_key4_event;                  /* key.c */
extern volatile uint8_t s_guard_mode_active;           /* power_mode.c */

/* ---- module-local state ----------------------------------------------- */


/* ---- forward declarations --------------------------------------------- */
static void init_task(void *pvParameters);
static void app_task(void *pvParameters);
static void temp_task(void *pvParameters);
static void guard_task(void *pvParameters);
static void can_rx_task(void *pvParameters);

static uint8_t can_handle_control(uint8_t msg_id, const uint8_t *param);
static uint8_t can_handle_config(uint8_t msg_id, const uint8_t *param);

/* ---- key callback handlers (called from ISR context via key.c) -------- */
static void key3_ignition_callback(key_id_t key_id, void *context)
{
    SemaphoreHandle_t sem = (SemaphoreHandle_t)context;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    (void)key_id;
    if(sem != NULL) {
        xSemaphoreGiveFromISR(sem, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

static void key4_guard_callback(key_id_t key_id, void *context)
{
    SemaphoreHandle_t sem = (SemaphoreHandle_t)context;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    
    (void)key_id;
    
    /* 检查信号量是否有效（防止在 FreeRTOS 启动前中断触发） */
    if(sem == NULL) {
        return;
    }
    
    xSemaphoreGiveFromISR(sem, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/* ============================================================
 *  app_tasks_start : create init_task. Called from main() before
 *                    vTaskStartScheduler().
 * ============================================================ */
void app_tasks_start(void)
{
    xTaskCreate(init_task, "INIT", configMINIMAL_STACK_SIZE * 2, NULL, INIT_TASK_PRIO, NULL);
}

/* ============================================================
 *  init_task : one-shot bring-up of the whole board, then create
 *              the application tasks and delete itself.
 * ============================================================ */
static void init_task(void *pvParameters)
{
    (void)pvParameters;

    board_init();

    /* create IPC used by key callbacks */
    s_ignition_sem   = xSemaphoreCreateBinary();
    s_guard_key1_sem = xSemaphoreCreateBinary();
    /* Use can_rx_frame_t (14 B) instead of can_receive_message_struct (76 B)
     * to save 496 B of heap across the 8-slot queue. */
    can4_rx_queue  = xQueueCreate(CAN4_RX_QUEUE_LEN, sizeof(can_rx_frame_t));
    configASSERT(s_ignition_sem   != NULL);
    configASSERT(s_guard_key1_sem != NULL);
    configASSERT(can4_rx_queue  != NULL);

    /* 初始化传感器管理模块（创建温度缓存互斥锁等） */
    configASSERT(sensor_manager_init() != 0U);

    /* 初始化热管理控制模块 */
    thermal_control_init();

    /* 初始化点火控制模块 */
    ignition_control_init(s_ignition_sem);

    /* 注册按键回调函数（解耦：MCAL 层不再直接操作信号量）
     * KEY_3 -> ignition_sem (点火切换)
     * KEY_4 -> guard_key1_sem (guard 模式切换) */
    (void)key_register_callback(KEY_ID_3, key3_ignition_callback, (void *)s_ignition_sem);
    (void)key_register_callback(KEY_ID_4, key4_guard_callback, (void *)s_guard_key1_sem);

    /* 按键初始化：参考官方 Template_SingleCore demo，在 FreeRTOS 启动后、
     * 信号量创建后、回调注册后再初始化按键，这样可以确保中断触发时
     * 所有资源都已准备好。
     * KEY_1 (GPIO only, no EXTI - intentionally unused now);
     * KEY_3 (EXTI_4, IRQ EXTI4)       = ignition toggle (PF0);
     * KEY_4 (EXTI_5, IRQ EXTI5_9)     = guard / normal mode toggle. */
    key_init();

    /* create application tasks */
    TaskHandle_t app_task_handle = NULL;
    TaskHandle_t temp_task_handle = NULL;
    configASSERT(xTaskCreate(app_task,                "APP",   APP_TASK_STACK,      NULL, APP_TASK_PRIO,      &app_task_handle)  == pdPASS);
    configASSERT(xTaskCreate(temp_task,               "TEMP",  TEMP_TASK_STACK,     NULL, TEMP_TASK_PRIO,     &temp_task_handle) == pdPASS);
    configASSERT(xTaskCreate(guard_task,              "GUARD", GUARD_TASK_STACK,    NULL, GUARD_TASK_PRIO,    NULL)              == pdPASS);
    configASSERT(xTaskCreate(ignition_control_task,   "IGN",   IGNITION_TASK_STACK, NULL, IGNITION_TASK_PRIO, NULL)              == pdPASS);
    configASSERT(xTaskCreate(can_rx_task,             "CANRX", CAN_RX_TASK_STACK,   NULL, CAN_RX_TASK_PRIO,   NULL)              == pdPASS);

    /* 初始化低功耗模式管理模块 */
    power_mode_init(app_task_handle, temp_task_handle);

    /* Boot default is guard mode: relay OFF, app_task suspended.
     * 
     * CRITICAL: 必须在 guard_task 开始运行前就设置 s_guard_mode_active = 1，
     * 否则 guard_task 会进入"等待进入 guard"的外层等待，导致第一次 KEY_4
     * 只是让它进入巡检循环，第二次 KEY_4 才退出 guard。
     * 
     * 通过将 INIT_TASK_PRIO 设置为高于所有应用任务，确保此处执行完毕后
     * guard_task 才开始运行，此时它会检测到 s_guard_mode_active == 1，
     * 直接跳过外层等待进入巡检循环。第一次 KEY_4 就能正确退出 guard。 */
    power_mode_enter_guard();

    vTaskDelete(NULL);
    for( ;; ) {
    }
}

/* ============================================================
 *  app_task : periodic control loop (was the bare-metal while(1)).
 * ============================================================ */
static void app_task(void *pvParameters)
{
    TickType_t last_wake = xTaskGetTickCount();
    (void)pvParameters;

    for( ;; ) {
        uint32_t now_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

        /* KEY_3 (ignition toggle) and KEY_4 (guard toggle) are owned
         * entirely by their ISRs (gd32a7xx_it.c). app_task only runs
         * the periodic control loop and never touches relay_power -
         * the relay follows the mode (see guard_enter / guard_exit). */

        thermal_control_update(now_ms);

        if(g_system_state_changed_flag != 0U) {
            g_system_state_changed_flag = 0U;
            (void)can_upload_system_state();
            (void)can_upload_env();
            (void)can_upload_temp();
        }

        can_process_pending_uploads();

#if WATCHDOG_ENABLE
        watchdog_feed();
#endif

        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(g_app_task_period_ms));
    }
}

/* ============================================================
 *  temp_task : 独立温度采集任务（异步采集架构核心）。
 *
 *  职责：约每 TEMP_SAMPLE_PERIOD_MS(1s) 完成一次 4 路 DS18B20 采集，
 *        把结果写入受互斥锁保护的温度缓存，供 app_task 非阻塞读取。
 *
 *  为什么单独成任务：
 *    - DS18B20 12bit 转换约需 750ms。若在 app_task 里同步采集，会把本应
 *      20ms 的控制循环拖成 ~800ms，状态机响应、CAN 处理、喂狗全部被拖慢。
 *    - 拆出来后，app_task 真正按 20ms 周期跑，温度按 1s 周期在后台刷新。
 *
 *  为什么优先级高于 app_task 且用分阶段采集：
 *    - 1-Wire 位时序对延时极敏感，位操作突发期间不能被 app_task 抢占，
 *      否则时序错乱、CRC 失败。高优先级保证位操作突发不被打断。
 *    - 但 750ms 转换等待用 vTaskDelay 让出 CPU（不是忙等），期间 app_task
 *      正常运行，因此高优先级不会饿死控制循环。
 *
 *  时序：
 *    temp_start_all()           // 阶段1：启动转换（几 ms 位操作，不被抢占）
 *    vTaskDelay(780ms)          // 让出 CPU，app_task 期间照常跑
 *    temp_read_all()            // 阶段3：读取+CRC（几~十几 ms 位操作）
 *    temp_cache_store()         // 写缓存
 *    vTaskDelayUntil(剩余到 1s) // 对齐采样周期
 *
 *  guard 模式：进入 guard 时本任务被挂起（sensors 断电，采集无意义），
 *  巡检期间由 guard_task 自行同步采集并写缓存（见 guard_task）。
 * ============================================================ */
static void temp_task(void *pvParameters)
{
    TickType_t last_wake = xTaskGetTickCount();
    (void)pvParameters;

    for( ;; ) {
        temp_result_t result;
        uint32_t sample_time_ms;

        /* 阶段1：启动全部通道转换（短促位操作，高优先级下不被 app_task 抢占） */
        temp_start_all();

        /* 阶段2：让出 CPU 等待转换完成。这段时间 app_task 照常以 20ms 运行。 */
        vTaskDelay(pdMS_TO_TICKS(TEMP_CONVERSION_WAIT_MS));

        /* 阶段3：读取 + CRC 校验，得到每一路温度 */
        (void)temp_read_all(&result);
        sample_time_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

        /* 写入缓存供状态机消费 */
        sensor_manager_store_temperature(&result, sample_time_ms);

        /* 对齐到固定采样周期（已消耗约 780ms+读取时间，这里补足到 1s） */
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(TEMP_SAMPLE_PERIOD_MS));
    }
}

/* ============================================================
 *  guard_task : KEY_4 toggles a low-power "patrol" mode.
 *
 *  While active:
 *    - app_task (and its actuators) is suspended;
 *    - the task alternates between a long tickless sleep
 *      (g_guard_sleep_interval_ms, via vTaskDelay -> idle task ->
 *      portSUPPRESS_TICKS_AND_SLEEP()/WFI) and a short patrol window
 *      (GUARD_PATROL_DURATION_MS) where it re-powers peripherals and
 *      reuses thermal_control_update() to sample/react exactly like
 *      app_task normally does;
 *    - waking the MCU from WFI does NOT re-power external sensors/
 *      actuators (PMU wake only restores the core), so PG0 must be
 *      re-asserted via relay_power_on() explicitly on every patrol,
 *      with a short settle delay before trusting sensor reads;
 *    - if the state machine stays at NORMAL during the whole patrol,
 *      the board is powered back off and we go back to the long sleep;
 *    - if any non-NORMAL state appears (LOW_TEMP / HIGH_TEMP /
 *      DANGER), the board stays powered and actuators stay driven
 *      until the state returns to NORMAL and remains stable for
 *      g_guard_handling_budget_ms, sampling every GUARD_PATROL_PERIOD_MS.
 *      No timeout: keeps handling until truly safe.
 *    - KEY_4 pressed again (guard_key1_sem) aborts immediately, either
 *      out of the sleep, out of an in-progress patrol, or out of the
 *      handling window, and hands control back to app_task.
 *
 *  Boot:  init_task calls power_mode_enter_guard() before deleting itself, so by
 *         the time this task is scheduled s_guard_mode_active is
 *         already 1. The first iteration of the outer loop therefore
 *         skips the outer wait + power_mode_enter_guard() and goes straight into
 *         the patrol loop. The first KEY_4 press from the user wakes
 *         the inner semaphore and exits guard mode (normal operation).
 *         From then on every KEY_4 press toggles guard mode.
 * ============================================================ */
/*
 * guard_update_handling_state
 *   巡检/延长处理窗口内每轮调用一次，推进 in_handling 状态：
 *     - 读到非 NORMAL：立即（重新）置 in_handling=1，清空"NORMAL 持续
 *       确认"计时；
 *     - 读到 NORMAL 但当前不在 in_handling：本轮至今未出现异常，直接
 *       维持 in_handling=0，无需确认；
 *     - 读到 NORMAL 且当前处于 in_handling：开始/继续累计连续 NORMAL
 *       时长，只有连续满 g_guard_handling_budget_ms 才真正清 in_handling，
 *       否则继续保持 in_handling=1（防止单次读数刚好回落到 NORMAL 就被
 *       当成安全立刻断电，而下一刻又反弹回危险状态）。
 */
static void guard_update_handling_state(uint8_t *in_handling,
                                         uint8_t *normal_confirm_active,
                                         TickType_t *normal_confirm_start,
                                         uint8_t *had_abnormal)
{
    TickType_t now_tick = xTaskGetTickCount();

    if(system_state_get_state() != SYSTEM_STATE_NORMAL) {
        *normal_confirm_active = 0U;
        *in_handling = 1U;
        *had_abnormal = 1U;  /* 本轮巡检出现过异常，供自适应睡眠时长使用 */
        return;
    }

    /* state == NORMAL */
    if(*in_handling == 0U) {
        return; /* 本轮巡检至今未出现异常，无需确认 */
    }

    if(*normal_confirm_active == 0U) {
        *normal_confirm_active = 1U;
        *normal_confirm_start  = now_tick;
        return;
    }

    if((now_tick - *normal_confirm_start) >= pdMS_TO_TICKS(g_guard_handling_budget_ms)) {
        *in_handling = 0U;
        *normal_confirm_active = 0U;
    }
}

/*
 * guard_adjust_sleep_interval
 *   每完成一次巡检（无论是否触发过 in_handling）调用一次，按本轮巡检是否
 *   出现过非 NORMAL 状态来调整下一轮长睡眠时长：
 *     - had_abnormal != 0：缩短 10%（乘以 90%），下限钳位到
 *       GUARD_ADAPTIVE_SLEEP_MIN_MS（5s），越危险醒得越勤；
 *     - had_abnormal == 0：增加 20%（乘以 120%），不设上限——只要连续
 *       多轮都正常，睡眠间隔会持续变长，直至用户按 KEY_4 退出 guard
 *       或再次出现异常。
 *   *90/100 或 *120/100 之后大概率不是 1000 的整数倍（例如 36000*90/100=
 *   32400ms=32.4s），四舍五入到最近的整数秒后再存回，保证任意时刻
 *   s_guard_current_sleep_interval_ms 都是 1000 的整数倍（整数秒），不会
 *   出现 32.4s 这种带小数的睡眠时长。
 *   用 uint64_t 中间量避免 *120/100 在大数值下溢出 uint32_t。
 */
/*
 * app_tasks_get_guard_current_sleep_ms
 *   对外暴露 s_guard_current_sleep_interval_ms 的只读访问接口，供
 *   can_app.c 的 CAN_QRY_GUARD_SLEEP 查询响应读取。s_guard_current_sleep_interval_ms
 *   是普通 uint32_t（非 volatile），但读取本身是单条 32 位对齐的
 *   load 指令，在 Cortex-M 上具有原子性，can_rx_task 里偶尔读到
 *   guard_task 正在写入前/后的值也不会造成撕裂读，可接受。
 */
uint32_t app_tasks_get_guard_current_sleep_ms(void)
{
    return s_guard_current_sleep_interval_ms;
}

static void guard_adjust_sleep_interval(uint8_t had_abnormal)
{
    uint64_t raw_ms;
    uint64_t new_interval_ms;

    if(had_abnormal != 0U) {
        raw_ms = ((uint64_t)s_guard_current_sleep_interval_ms
                  * GUARD_ADAPTIVE_SHRINK_PCT) / 100ULL;
    } else {
        raw_ms = ((uint64_t)s_guard_current_sleep_interval_ms
                  * GUARD_ADAPTIVE_GROW_PCT) / 100ULL;
    }

    /* 四舍五入到最近的整数秒：小数部分 >= 0.5s 向上取整，否则向下取整。 */
    new_interval_ms = ((raw_ms + 500ULL) / 1000ULL) * 1000ULL;

    if((had_abnormal != 0U) && (new_interval_ms < GUARD_ADAPTIVE_SLEEP_MIN_MS)) {
        new_interval_ms = GUARD_ADAPTIVE_SLEEP_MIN_MS;
    }

    s_guard_current_sleep_interval_ms = (uint32_t)new_interval_ms;
}

static void guard_task(void *pvParameters)
{
    (void)pvParameters;

    /* 覆盖上电即处于 guard 模式的场景（init_task 已调用
     * power_mode_enter_guard()，此时 s_guard_mode_active 已是 1，
     * 下面第一次外层判断会被跳过，所以在循环外先初始化一次）。 */
    s_guard_current_sleep_interval_ms = g_guard_sleep_interval_ms;

    for( ;; ) {
            /* If guard is already active (we entered it from init_task
             * before guard_task even got a chance to run), skip the
             * outer wait + power_mode_enter_guard() and go straight into the patrol
             * loop, which already blocks on s_guard_key1_sem with a timeout
             * and exits guard on the next KEY_4 press. */
        if(s_guard_mode_active == 0U) {
            /* idle, waiting for KEY_4 to request guard mode */
            if(xSemaphoreTake(s_guard_key1_sem, portMAX_DELAY) != pdTRUE) {
                continue;
            }

            power_mode_enter_guard();

            /* 每次全新进入 guard 模式，自适应睡眠时长都从配置基准值
             * 重新开始，不沿用上次退出 guard 前累积的缩短/放大结果。 */
            s_guard_current_sleep_interval_ms = g_guard_sleep_interval_ms;
        }

        while(s_guard_mode_active != 0U) {
            /* long low-power sleep between patrols; tickless idle lets
             * the core WFI here instead of ticking every 1ms.
             * 睡眠时长使用自适应值 s_guard_current_sleep_interval_ms，
             * 而非固定的 g_guard_sleep_interval_ms：上一轮巡检若检测到
             * 异常就会缩短，全程 NORMAL 则会放大（见 guard_adjust_sleep_interval）。 */
            if(xSemaphoreTake(s_guard_key1_sem, pdMS_TO_TICKS(s_guard_current_sleep_interval_ms)) == pdTRUE) {
                break; /* KEY_4 pressed again: exit guard mode */
            }

            /* woke up on schedule: power the external board, wait for
             * sensors to come up, then keep sampling/driving actuators
             * for as long as the state machine says "something is wrong". */
            relay_power_on();
            gd_eval_led_on(LED4);  /* 巡检窗口开始，点亮 LED4 指示"临时工作中" */
            vTaskDelay(pdMS_TO_TICKS(GUARD_POWER_ON_SETTLE_MS));

            {
                TickType_t patrol_last_wake = xTaskGetTickCount();
                TickType_t patrol_end       = patrol_last_wake + pdMS_TO_TICKS(GUARD_PATROL_DURATION_MS);
                uint8_t    in_handling      = 0U;
                uint8_t    aborted          = 0U;
                uint8_t    temp_started     = 0U;  /* 标记是否已启动温度转换 */
                uint8_t    normal_confirm_active = 0U; /* 是否正在累计"连续 NORMAL"确认 */
                TickType_t normal_confirm_start  = 0U; /* 连续 NORMAL 确认起始时刻 */
                uint8_t    had_abnormal     = 0U;  /* 本轮巡检（含延长处理窗口）是否出现过非 NORMAL，
                                                     * 用于驱动自适应睡眠时长；一旦置 1 就不会清零，
                                                     * 即便之后连续 NORMAL 满足确认时长清了 in_handling */

                /* 巡检开始立即启动第一次温度转换(非阻塞,仅几ms位操作) */
                temp_start_all();
                temp_started = 1U;

                while(xTaskGetTickCount() < patrol_end) {
                    uint32_t now_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

                    /* 若已启动转换且等待足够时间,读取结果并写入缓存;
                     * 然后立即启动下一次转换。分阶段采集避免每次循环都忙等 750ms。 */
                    if(temp_started != 0U) {
                        temp_result_t result;
                        vTaskDelay(pdMS_TO_TICKS(TEMP_CONVERSION_WAIT_MS));
                        if(temp_read_all(&result) != 0U) {
                            sensor_manager_store_temperature(&result, now_ms);
                        }
                        temp_start_all();  /* 启动下一次转换 */
                    }
                    thermal_control_update(now_ms);

                    if(g_system_state_changed_flag != 0U) {
                        g_system_state_changed_flag = 0U;
                        (void)can_upload_system_state();
                        (void)can_upload_env();
                        (void)can_upload_temp();
                    }
                    can_process_pending_uploads();

                    /* KEY_4 during a patrol: cut it short and exit guard mode */
                    if(xSemaphoreTake(s_guard_key1_sem, 0) == pdTRUE) {
                        aborted = 1U;
                        break;
                    }

                    /* 更新处理状态：只有连续 NORMAL 满 g_guard_handling_budget_ms
                     * 才清 in_handling，否则维持处理/保持上电。 */
                    guard_update_handling_state(&in_handling,
                                                 &normal_confirm_active, &normal_confirm_start,
                                                 &had_abnormal);

                    vTaskDelayUntil(&patrol_last_wake, pdMS_TO_TICKS(GUARD_PATROL_PERIOD_MS));
                }

                /* 巡检窗口（GUARD_PATROL_DURATION_MS）结束后，如果仍在处理异常
                 * (in_handling=1)，继续保持上电并采样，直到连续 NORMAL 满
                 * g_guard_handling_budget_ms 才允许断电。不设超时上限，处理到底。
                 * KEY_4 任意时刻可中断退出 guard。 */
                while((in_handling != 0U) && (s_guard_mode_active != 0U)) {
                    uint32_t now_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

                    /* 同上：分阶段采集温度，避免忙等 */
                    if(temp_started != 0U) {
                        temp_result_t result;
                        vTaskDelay(pdMS_TO_TICKS(TEMP_CONVERSION_WAIT_MS));
                        if(temp_read_all(&result) != 0U) {
                            sensor_manager_store_temperature(&result, now_ms);
                        }
                        temp_start_all();
                    }
                    thermal_control_update(now_ms);

                    if(g_system_state_changed_flag != 0U) {
                        g_system_state_changed_flag = 0U;
                        (void)can_upload_system_state();
                        (void)can_upload_env();
                        (void)can_upload_temp();
                    }
                    can_process_pending_uploads();

                    if(xSemaphoreTake(s_guard_key1_sem, 0) == pdTRUE) {
                        aborted = 1U;
                        break;
                    }

                    /* 同上：只有连续 NORMAL 满 g_guard_handling_budget_ms 才清 in_handling */
                    guard_update_handling_state(&in_handling,
                                                 &normal_confirm_active, &normal_confirm_start,
                                                 &had_abnormal);

                    vTaskDelayUntil(&patrol_last_wake, pdMS_TO_TICKS(GUARD_PATROL_PERIOD_MS));
                }

                /* 根据本轮巡检（含延长处理窗口）是否出现过非 NORMAL，调整
                 * 下一轮长睡眠时长：出现过异常 -> 缩短 10%（下限 5s）；
                 * 全程 NORMAL -> 增加 20%（不设上限）。用户中断(aborted)时
                 * 不调整，因为本轮巡检并未正常走完。 */
                if(aborted == 0U) {
                    guard_adjust_sleep_interval(had_abnormal);
                }

                /* Power the board back off ONLY if nothing required action.
                 * in_handling is cleared only after state has been NORMAL
                 * continuously for g_guard_handling_budget_ms. */
                if((aborted == 0U) && (in_handling == 0U)) {
                    /* 断电前先强制关闭状态指示灯，避免 GPIO 输出寄存器残留导致
                     * 下次上电瞬间误显示。thermal_control_update() 会在巡检期间
                     * 根据状态机点亮这些灯，但巡检结束长睡眠前必须归零。 */
                    actor_set_channel(GPIO_CH_LED_WHITE, 0U);
                    actor_set_channel(GPIO_CH_LED_GREEN, 0U);
                    actor_set_channel(GPIO_CH_LED_YELLOW, 0U);
                    actor_set_channel(GPIO_CH_LED_RED, 0U);
                    relay_power_off();
                    gd_eval_led_off(LED4);  /* 巡检窗口结束（恢复长睡眠），熄灭 LED4 */
                }

                if(aborted != 0U) {
                    /* User pressed KEY_4 to leave guard mode: drop out
                     * of the patrol and let power_mode_exit_guard() restore power. */
                    gd_eval_led_off(LED4);  /* 用户中断巡检退出 guard，熄灭 LED4 */
                    break;
                }
            }
        }

        power_mode_exit_guard();

        /* 不会再出现"in_handling 未清零、跨长睡眠保持上电"的场景，因为
         * 延长处理循环不设超时上限，必须连续 NORMAL 满 g_guard_handling_budget_ms
         * 才断电。此兜底仅处理 KEY_4 中断巡检的情况（用户在外层循环顶部按键
         * 直接 break，不经过巡检内部的熄灭逻辑），确保退出 guard 后 LED4 一定是灭的。 */
        gd_eval_led_off(LED4);
    }
}

/* ============================================================
 *  can_handle_control : 执行控制类命令（请求帧 Byte0=0x10）。
 *    在 can_rx_task 上下文调用，返回 ACK 结果码 (CAN_ACK_*)。
 *    0x00~0x07 为通用控制；0x08~0x0D 为维护模式直控，仅手动模式下生效；
 *    0x0E 为温度趋势预测使能开关，任何模式下均可切换。
 *    电源开关不直接调用 guard_enter/exit（避免与 guard_task 抢占），
 *    而是按当前模式决定是否给 guard_key1_sem 触发一次状态切换。
 * ============================================================ */
static uint8_t can_handle_control(uint8_t msg_id, const uint8_t *param)
{
    switch(msg_id) {
    case CAN_CTL_POWER_ON:
        /* 仅当处于 guard 模式时才触发退出，回到正常模式 */
        if(s_guard_mode_active != 0U) {
            (void)xSemaphoreGive(s_guard_key1_sem);
        }
        return CAN_ACK_OK;

    case CAN_CTL_SLEEP:
        /* 仅当处于正常模式时才触发进入 guard */
        if(s_guard_mode_active == 0U) {
            (void)xSemaphoreGive(s_guard_key1_sem);
        }
        return CAN_ACK_OK;

    case CAN_CTL_IGNITE:
        return ignition_control_handle_ignite();

    case CAN_CTL_EXTINGUISH:
        return ignition_control_handle_extinguish();

    case CAN_CTL_RESET:
        {
            /* Byte2=高字节, Byte3=低字节，校验防误触 */
            uint16_t magic = (uint16_t)(((uint16_t)param[0] << 8) | param[1]);
            if(magic != CAN_CTL_RESET_MAGIC) {
                return CAN_ACK_CHECK_FAIL;
            }
            /* 先回执，稍作延时确保帧发出，再复位 */
            (void)can_send_control_ack(CAN_CTL_RESET, CAN_ACK_OK);
            vTaskDelay(pdMS_TO_TICKS(50U));
            NVIC_SystemReset();
        }
        return CAN_ACK_OK; /* 正常不会执行到 */

    case CAN_CTL_CLEAR_FAULT:
        fault_manager_reset();
        return CAN_ACK_OK;

    case CAN_CTL_MANUAL_ENTER:
        thermal_control_set_manual_mode(1U);
        return CAN_ACK_OK;

    case CAN_CTL_MANUAL_EXIT:
        thermal_control_set_manual_mode(0U);
        return CAN_ACK_OK;

    /* --- 维护模式直控：仅手动模式下生效，否则拒绝 --- */
    case CAN_CTL_BUZZER_MUTE:
        if(thermal_control_get_manual_mode() == 0U) { return CAN_ACK_NOT_MANUAL; }
        /* Byte2=1开/0关；静音即关闭蜂鸣器 */
        actor_set_channel(GPIO_CH_BUZZER, (param[0] != 0U) ? 1U : 0U);
        return CAN_ACK_OK;

    case CAN_CTL_COOLER:
        if(thermal_control_get_manual_mode() == 0U) { return CAN_ACK_NOT_MANUAL; }
        if(param[0] > 3U) { return CAN_ACK_ILLEGAL; }
        actor_set_channel((actor_channel_t)(GPIO_CH_COOLER1 + param[0]),
                          (param[1] != 0U) ? 1U : 0U);
        return CAN_ACK_OK;

    case CAN_CTL_HEATER:
        if(thermal_control_get_manual_mode() == 0U) { return CAN_ACK_NOT_MANUAL; }
        if(param[0] > 3U) { return CAN_ACK_ILLEGAL; }
        actor_set_channel((actor_channel_t)(GPIO_CH_HEATER1 + param[0]),
                          (param[1] != 0U) ? 1U : 0U);
        return CAN_ACK_OK;

    case CAN_CTL_FAN:
        if(thermal_control_get_manual_mode() == 0U) { return CAN_ACK_NOT_MANUAL; }
        if(param[1] > 100U) { return CAN_ACK_ILLEGAL; }
        pwm_set_enable(PWM_FAN, (param[0] != 0U) ? 1U : 0U);
        pwm_set_duty_percent(PWM_FAN, param[1]);
        return CAN_ACK_OK;

    case CAN_CTL_PUMP:
        if(thermal_control_get_manual_mode() == 0U) { return CAN_ACK_NOT_MANUAL; }
        if(param[1] > 100U) { return CAN_ACK_ILLEGAL; }
        pwm_set_enable(PWM_PUMP, (param[0] != 0U) ? 1U : 0U);
        pwm_set_duty_percent(PWM_PUMP, param[1]);
        return CAN_ACK_OK;

    case CAN_CTL_GATE:
        if(thermal_control_get_manual_mode() == 0U) { return CAN_ACK_NOT_MANUAL; }
        actor_set_channel(GPIO_CH_GATE, (param[0] != 0U) ? 1U : 0U);
        return CAN_ACK_OK;

    case CAN_CTL_TEMP_PREDICT_ENABLE:
        /* Byte2 = 1开/0关。与维护模式无关，任何模式下都可切换，
         * 立即影响 system_state_task() 里的预测升级判断。 */
        g_temp_prediction_enable = (param[0] != 0U) ? 1U : 0U;
        return CAN_ACK_OK;

    default:
        return CAN_ACK_ILLEGAL;
    }
}

/* ============================================================
 *  can_handle_config : 处理配置类消息 (0x20)，动态修改运行参数
 *    param[0~5] 对应 Byte2~7。
 *    返回 ACK 结果码 (CAN_ACK_*)。
 * ============================================================ */
static uint8_t can_handle_config(uint8_t msg_id, const uint8_t *param)
{
    switch(msg_id) {
    case CAN_CFG_HIGH_TEMP_THRESHOLD:
        {
            uint8_t integer = param[0];
            uint8_t decimal = param[1];
            if((integer > 100U) || (decimal > 9U)) {
                return CAN_ACK_ILLEGAL;
            }
            g_high_temp_threshold_tenths = (uint16_t)(integer * 10U + decimal);
        }
        return CAN_ACK_OK;

    case CAN_CFG_DANGER_TEMP_THRESHOLD:
        {
            uint8_t integer = param[0];
            uint8_t decimal = param[1];
            if((integer > 100U) || (decimal > 9U)) {
                return CAN_ACK_ILLEGAL;
            }
            g_danger_temp_threshold_tenths = (uint16_t)(integer * 10U + decimal);
        }
        return CAN_ACK_OK;

    case CAN_CFG_LOW_TEMP_THRESHOLD:
        {
            uint8_t integer = param[0];
            uint8_t decimal = param[1];
            if((integer > 100U) || (decimal > 9U)) {
                return CAN_ACK_ILLEGAL;
            }
            g_low_temp_threshold_tenths = (uint16_t)(integer * 10U + decimal);
        }
        return CAN_ACK_OK;

    case CAN_CFG_FALLBACK_CONFIRM_COUNT:
        {
            uint8_t count = param[0];
            if((count == 0U) || (count > 10U)) {
                return CAN_ACK_ILLEGAL;
            }
            g_fallback_confirm_count = count;
        }
        return CAN_ACK_OK;

    case CAN_CFG_GUARD_SLEEP_INTERVAL:
        {
            uint8_t tens = param[0];
            uint8_t ones = param[1];
            uint32_t seconds = (uint32_t)(tens * 10U + ones);
            if((seconds < 5U) || (seconds > 255U)) {
                return CAN_ACK_ILLEGAL;
            }
            g_guard_sleep_interval_ms = seconds * 1000U;
            /* 同步更新自适应睡眠时长当前值，让配置立即生效：下次长睡眠
             * 会从新的基准值开始，而不是沿用旧基准累积的缩短/放大结果。 */
            s_guard_current_sleep_interval_ms = g_guard_sleep_interval_ms;
        }
        return CAN_ACK_OK;

    case CAN_CFG_GUARD_HANDLING_BUDGET:
        {
            uint8_t tens = param[0];
            uint8_t ones = param[1];
            uint32_t seconds = (uint32_t)(tens * 10U + ones);
            if((seconds < 5U) || (seconds > 255U)) {
                return CAN_ACK_ILLEGAL;
            }
            g_guard_handling_budget_ms = seconds * 1000U;
        }
        return CAN_ACK_OK;

    case CAN_CFG_APP_TASK_PERIOD:
        {
            uint8_t period_ms = param[0];
            if((period_ms < 10U) || (period_ms > 100U)) {
                return CAN_ACK_ILLEGAL;
            }
            g_app_task_period_ms = (uint32_t)period_ms;
        }
        return CAN_ACK_OK;

    default:
        return CAN_ACK_ILLEGAL;
    }
}

/* ============================================================
 *  can_rx_task : blocks on can4_rx_queue filled by DTM_CAN4 ISR,
 *                parses request frames off the ISR context.
 *    报文类别由 ID 区分：0x188=查询, 0x189=控制, 0x18A=配置。
 *    帧格式：Byte0=源节点地址, Byte1=消息号, Byte2~7=参数。
 *    只处理来自上位机的帧（Byte0=CAN_NODE_HOST），忽略自身回显。
 *    查询类只置位上报标志（响应走 0x188）；控制/配置类回同 ID ACK。
 * ============================================================ */
static void can_rx_task(void *pvParameters)
{
    can_rx_frame_t rx_msg;
    (void)pvParameters;

    for( ;; ) {
        if(xQueueReceive(can4_rx_queue, &rx_msg, portMAX_DELAY) == pdTRUE) {
            uint8_t src_node;
            uint8_t msg_id;
            uint8_t param[6] = {0};
            uint8_t i;

            /* xtd: 0 = standard frame (only these are accepted) */
            if(rx_msg.xtd != 0U) {
                continue;
            }

            /* 仅接受上位机 -> MCU 方向的请求帧，避免处理自身响应回显 */
            src_node = (rx_msg.data_bytes > 0U) ? (rx_msg.data[0] & 0xF0U) : 0xFFU;
            if(src_node != CAN_NODE_HOST) {
                continue;
            }

            msg_id = (rx_msg.data_bytes > 1U) ? rx_msg.data[1] : 0U;
            for(i = 0U; (i < 6U) && ((uint16_t)(i + 2U) < rx_msg.data_bytes); i++) {
                param[i] = rx_msg.data[i + 2U];
            }

            switch(rx_msg.id) {
            case CAN_ID_QUERY:
                /* 查询类命令立即响应,不再延迟到主循环。
                 * 避免 guard 模式巡检期间响应延迟过大导致上位机超时。 */
                (void)can_handle_query(msg_id);
                can_process_pending_uploads();
                break;

            case CAN_ID_CONTROL:
                {
                    uint8_t result = can_handle_control(msg_id, param);
                    (void)can_send_control_ack(msg_id, result);
                }
                break;

            case CAN_ID_CONFIG:
                {
                    uint8_t result = can_handle_config(msg_id, param);
                    (void)can_send_config_ack(msg_id, result);
                }
                break;

            default:
                break;
            }
        }
    }
}
