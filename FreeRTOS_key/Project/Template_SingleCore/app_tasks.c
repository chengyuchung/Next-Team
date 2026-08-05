/*!
    \file    app_tasks.c
    \brief   FreeRTOS 应用层任务集中管理 (GD32A7xx 热管理系统)

    \note    原先集中在 main.c 的全部任务与辅助函数迁移到此文件，main.c
             只保留 main() 入口与板级外设初始化 (board_init)。

             任务与角色：
               init_task    : 板级初始化 -> 创建 IPC 与任务 -> 进入 guard -> 自删除
               app_task     : 正常模式周期控制循环（状态机 + CAN 上报）
               guard_task   : 低功耗巡检模式（长睡眠 / 巡检交替）
               ignition_task: KEY_3 点火切换（EXTI4 -> ignition_sem）
               can_rx_task  : 解析 CAN 请求帧（查询/控制/配置 -> ACK）

             KEY_3 -> 点火切换 (PF0)，guard 模式下忽略；
             KEY_4 -> guard / 正常模式切换，也用于把系统从 tickless idle 唤醒；
             CAN RX -> can_rx_task；guard 模式下同时唤醒 guard_task。
*/

#include "gd32a7xx.h"
#include "gd32a712_evb.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "main.h"
#include "app_tasks.h"

#include "can.h"

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
#include "watchdog.h"
#include "bmp280.h"
#include "temp_sensor.h"
#include "adc_manager.h"
#include "mq9.h"
#include "motor_pwm_gd32.h"
#include "relay_power.h"
#include "actor.h"
#include "key.h"
#include "power_manager.h"
#include "system_state.h"
#include "fault_manager.h"

/* ---- task priorities (configMAX_PRIORITIES == 8) ----------------------
 * TEMP_TASK 优先级高于 APP_TASK：DS18B20 的 1-Wire 位时序对延时极敏感
 * （读采样窗口 ~15us），若被 app_task 抢占会破坏位时序导致 CRC 失败。
 * 让温度任务优先级更高，可保证它短促的位操作突发不被 app_task 打断；
 * 而 750ms 的转换等待用 vTaskDelay 让出 CPU，因此不会饿死 app_task。 */
#define INIT_TASK_PRIO       ( tskIDLE_PRIORITY + 1 )
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
uint32_t g_guard_sleep_interval_ms    = 15U * 1000U;
uint32_t g_guard_handling_budget_ms   = 30U * 1000U;

/* ---- guard (低功耗巡检) mode timing ------------------------------------
 * KEY_4 切换进入/退出 guard 巡检模式：
 *   - 上电默认处于 guard 模式：relay_power_init(0U) 把 PG0 置低，
 *     外设整体断电；app_task 被挂起，guard_task 在 tickless idle 中休眠；
 *   - 用户按一次 KEY_4：guard_key1_sem 触发 -> guard_exit() ->
 *     relay_power_on() -> vTaskResume(app_task)，系统进入正常运行模式；
 *   - 正常运行模式下，guard_task 每 g_guard_sleep_interval_ms 醒来一次
 *     （不过此时仅作超时检测，因为 s_guard_mode_active == 0）；
 *   - 用户再次按 KEY_4：guard_enter() -> relay_power_off() ->
 *     vTaskSuspend(app_task)，回到 guard 模式；
 *   - 每次"定时唤醒 + 外设上电 + 跑 GUARD_PATROL_DURATION_MS 的巡检循环"
 *     的能力保留：guard_task 检测到任何非 NORMAL 状态就会临时拉高
 *     relay_power 并执行 actuator 动作；
 *   - 巡检内部按状态机决定行为：
 *       state == NORMAL           -> 巡检结束，关电，进入下一轮长睡；
 *       state == PRE/WARNING/DANGER -> 持续执行状态机分支 (风扇/泵/加热/制冷/
 *                                      蜂鸣/门)；最长可再延长 g_guard_handling_budget_ms；
 *   - 唤醒源：KEY_4 任意时刻按下立刻退出 guard；CAN4 收到任意报文也
 *     会立即唤醒 guard_task；KEY_3 只翻点火，不参与 guard 唤醒。 */
#define GUARD_PATROL_DURATION_MS    (  5U * 1000U )  /* 每次唤醒后的巡检持续时长 */
#define GUARD_PATROL_PERIOD_MS      ( APP_TASK_PERIOD_MS ) /* 巡检内部采样周期，与 app_task 保持一致 */
#define GUARD_POWER_ON_SETTLE_MS    ( 50U )          /* PG0 继电器上电到外设可用的稳定延时 */

/* ============================================================
 *  IPC objects (created in init_task, referenced by gd32a7xx_it.c)
 * ============================================================ */
SemaphoreHandle_t ignition_sem   = NULL;
QueueHandle_t     can4_rx_queue  = NULL;

/* given by EXTI5_9_IRQHandler (KEY_4) on every press, and additionally
 * by DTM_CAN4 INT0 (CAN RX) while guard mode is active. guard_task blocks
 * on it with a timeout so the idle task can enter tickless sleep, and any
 * give wakes guard_task immediately to enter or exit guard mode.
 * KEY_3 (EXTI4) drives ignition_sem instead and does not participate
 * in guard wakeup. */
SemaphoreHandle_t guard_key1_sem = NULL;

#define CAN4_RX_QUEUE_LEN    ( 8U )

/* ---- flags defined elsewhere ------------------------------------------ */
extern volatile uint8_t g_system_state_changed_flag;   /* can.c */
extern volatile uint8_t g_key4_event;                  /* key.c */

/* ---- module-local state ----------------------------------------------- */
static uint8_t s_ignition_locked = 0U;   /* 1 = DANGER 状态强制锁定，禁止点火 */
/* 手动/维护模式：1 = 状态机不再接管执行器，只听 CAN 直控命令。
 * 由 0x0C/0x0D 显式切换；DANGER 状态会强制清零并夺回控制权。 */
static volatile uint8_t s_manual_mode = 0U;
static TaskHandle_t s_app_task_handle = NULL;
static TaskHandle_t s_temp_task_handle = NULL;
/* note: not static, ISRs in gd32a7xx_it.c need to read this to know
 * whether an external event (CAN RX) should also wake guard_task.
 * guard_enter/exit are the only writers. */
volatile uint8_t s_guard_mode_active = 0U;

/* ============================================================
 *  温度缓存（异步采集架构）
 *
 *  由 temp_task 约每秒刷新一次，app_task / guard_task 以非阻塞方式读取。
 *  这样温度采集那 ~800ms 的耗时不再阻塞 20ms 的高频控制循环，状态机得以
 *  真正按 g_app_task_period_ms 周期运行，同时温度趋势预测基于 sample_time_ms
 *  的真实采样间隔计算斜率。
 *
 *  访问一律通过互斥锁保护，保证 temp_result_t 这一整块数据的读写原子性。
 * ============================================================ */
typedef struct {
    temp_result_t result;       /* 最近一次采集结果 */
    uint32_t sample_time_ms;    /* 该结果的采集完成时间戳 */
    uint8_t  has_sample;        /* 是否已至少完成过一次采集 */
} temp_cache_t;

static temp_cache_t     s_temp_cache;
static SemaphoreHandle_t s_temp_cache_mutex = NULL;
/* 记录状态机上一次消费的温度样本时间戳，用于判定本帧是否为新样本
 * （新样本才推进温度变化率历史）。 */
static uint32_t         s_consumed_sample_time_ms = 0U;
static uint8_t          s_consumed_sample_valid = 0U;

/*
 * temp_cache_store
 *   把一帧采集结果写入缓存（加锁保护）。由采集侧（temp_task / guard 巡检）调用。
 */
static void temp_cache_store(const temp_result_t *result, uint32_t sample_time_ms)
{
    if((result == NULL) || (s_temp_cache_mutex == NULL)) {
        return;
    }
    if(xSemaphoreTake(s_temp_cache_mutex, portMAX_DELAY) == pdTRUE) {
        s_temp_cache.result = *result;
        s_temp_cache.sample_time_ms = sample_time_ms;
        s_temp_cache.has_sample = 1U;
        (void)xSemaphoreGive(s_temp_cache_mutex);
    }
}

/*
 * temp_cache_load
 *   从缓存读取最近一帧结果（加锁保护）。由消费侧（状态机输入组装）调用。
 *   返回 1 表示缓存中已有有效样本；0 表示尚未完成过任何采集。
 */
static uint8_t temp_cache_load(temp_result_t *result, uint32_t *sample_time_ms)
{
    uint8_t has_sample = 0U;

    if((result == NULL) || (sample_time_ms == NULL) || (s_temp_cache_mutex == NULL)) {
        return 0U;
    }
    if(xSemaphoreTake(s_temp_cache_mutex, portMAX_DELAY) == pdTRUE) {
        *result = s_temp_cache.result;
        *sample_time_ms = s_temp_cache.sample_time_ms;
        has_sample = s_temp_cache.has_sample;
        (void)xSemaphoreGive(s_temp_cache_mutex);
    }
    return has_sample;
}

/*
 * temp_sample_blocking_to_cache
 *   同步完成一次完整温度采集（忙等约 750ms）并写入缓存。
 *   供 guard 巡检使用：此时 app_task 与 temp_task 均已挂起，忙等无副作用。
 */
static void temp_sample_blocking_to_cache(uint32_t now_ms)
{
    temp_result_t result;
    if(temp_get(&result) != 0U) {
        temp_cache_store(&result, now_ms);
    } else {
        /* 全部失效也要写入缓存，让状态机据此把各分区标记为无效 */
        temp_cache_store(&result, now_ms);
    }
}

/* ---- forward declarations --------------------------------------------- */
static void init_task(void *pvParameters);
static void app_task(void *pvParameters);
static void temp_task(void *pvParameters);
static void guard_task(void *pvParameters);
static void ignition_task(void *pvParameters);
static void can_rx_task(void *pvParameters);

static void apply_state_to_actuators(void);
static void system_state_update_input(uint32_t now_ms);
static void guard_enter(void);
static void guard_exit(void);
static uint8_t can_handle_control(uint8_t msg_id, const uint8_t *param);
static uint8_t can_handle_config(uint8_t msg_id, const uint8_t *param);

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

    /* create IPC used by ISRs (gd32a7xx_it.c) */
    ignition_sem   = xSemaphoreCreateBinary();
    guard_key1_sem = xSemaphoreCreateBinary();
    /* 温度缓存互斥锁：保护 temp_task 写入与消费侧读取之间的数据一致性 */
    s_temp_cache_mutex = xSemaphoreCreateMutex();
    /* Use can_rx_frame_t (14 B) instead of can_receive_message_struct (76 B)
     * to save 496 B of heap across the 8-slot queue. */
    can4_rx_queue  = xQueueCreate(CAN4_RX_QUEUE_LEN, sizeof(can_rx_frame_t));
    configASSERT(ignition_sem   != NULL);
    configASSERT(guard_key1_sem != NULL);
    configASSERT(s_temp_cache_mutex != NULL);
    configASSERT(can4_rx_queue  != NULL);

    /* create application tasks */
    configASSERT(xTaskCreate(app_task,      "APP",   APP_TASK_STACK,      NULL, APP_TASK_PRIO,      &s_app_task_handle)  == pdPASS);
    configASSERT(xTaskCreate(temp_task,     "TEMP",  TEMP_TASK_STACK,     NULL, TEMP_TASK_PRIO,     &s_temp_task_handle) == pdPASS);
    configASSERT(xTaskCreate(guard_task,    "GUARD", GUARD_TASK_STACK,    NULL, GUARD_TASK_PRIO,    NULL)                == pdPASS);
    configASSERT(xTaskCreate(ignition_task, "IGN",   IGNITION_TASK_STACK, NULL, IGNITION_TASK_PRIO, NULL)                == pdPASS);
    configASSERT(xTaskCreate(can_rx_task,   "CANRX", CAN_RX_TASK_STACK,   NULL, CAN_RX_TASK_PRIO,   NULL)                == pdPASS);

    /* Boot default is guard mode: relay OFF, app_task suspended,
     * guard_task already inside the patrol loop. The first KEY_4 press
     * wakes guard_task out of the inner semaphore and exits guard.
     * We do this AFTER creating the tasks so guard_enter() can use the
     * already-stored s_app_task_handle, and BEFORE deleting ourselves
     * so the kernel is fully up when we touch its state. */
    guard_enter();

    vTaskDelete(NULL);
    for( ;; ) {
    }
}

/* ============================================================
 *  Gather sensor inputs, run the state machine, drive outputs.
 * ============================================================ */
static void system_state_update_input(uint32_t now_ms)
{
    system_state_input_t input = {0};
    bmp280_data_t bmp_result = {0};
    temp_result_t temp_result = {0};
    mq9_result_t gas_result = {0};

    input.now_ms = now_ms;
    input.ignition_on = ignition_get();

    /* 4路DS18B20分区测温：改为从温度缓存非阻塞读取（由 temp_task 约每秒刷新），
     * 不再在这里忙等 ~800ms 采集，使控制循环得以按真实周期高频运行。
     * 下标i对应加热片(i+1)/制冷片(i+1)所在分区。 */
    {
        uint32_t sample_time_ms = 0U;
        uint8_t  has_sample = temp_cache_load(&temp_result, &sample_time_ms);
        uint8_t  zi;

        if((has_sample != 0U) && (temp_result.valid != 0U)) {
            input.temperature_valid = temp_result.valid;
            input.temp_sensor_valid_count = temp_result.valid_count;
            input.temp_sensor_fault_mask = temp_result.fault_mask;
            for(zi = 0U; zi < 4U; zi++) {
                input.zone_temperature_tenths[zi] = temp_result.temperature[zi];
                input.zone_temp_valid[zi] = temp_result.channel_valid[zi];
            }
        } else {
            input.temperature_valid = 0U;
            input.temp_sensor_valid_count = 0U;
            input.temp_sensor_fault_mask = 0x0FU;
            for(zi = 0U; zi < 4U; zi++) {
                input.zone_temperature_tenths[zi] = 0;
                input.zone_temp_valid[zi] = 0U;
            }
        }

        /* 携带样本采集时间戳，并判定本帧是否为"新样本"：
         * 只有采集时间戳相对上次消费发生变化，才认为来了新的一帧温度，
         * 供状态机据此推进温度变化率历史（与调用频率解耦）。 */
        input.temp_sample_time_ms = sample_time_ms;
        if(has_sample == 0U) {
            input.temp_sample_fresh = 0U;
        } else if((s_consumed_sample_valid == 0U) ||
                  (sample_time_ms != s_consumed_sample_time_ms)) {
            input.temp_sample_fresh = 1U;
            s_consumed_sample_time_ms = sample_time_ms;
            s_consumed_sample_valid = 1U;
        } else {
            input.temp_sample_fresh = 0U;
        }
    }

    /* BMP280 只负责压力监测（泄压判断），不再参与温度风险判断。 */
    if(pressure_get(&bmp_result) != 0U) {
        input.pressure_valid = bmp_result.valid;
        input.pressure_pa = bmp_result.pressure_pa;
        input.pressure_alarm = bmp_result.alarm;
    } else {
        input.pressure_valid = 0U;
        input.pressure_pa = 0;
        input.pressure_alarm = 0U;
    }

    (void)mq9_task();
    if(get_gas(&gas_result) != 0U) {
        input.gas_valid = gas_result.valid;
        input.gas_alarm = gas_result.alarm;
    } else {
        input.gas_valid = 0U;
        input.gas_alarm = 0U;
    }

    system_state_task(&input);

    apply_state_to_actuators();
}

static void apply_state_to_actuators(void)
{
    system_state_status_t status;
    system_state_get_status(&status);

    /* 手动模式安全兜底：一旦系统进入 DANGER，状态机强制夺回控制权，
     * 自动退出手动模式并主动上报事件帧，随后按下方正常逻辑降温/切点火。 */
    if((s_manual_mode != 0U) && (status.state == SYSTEM_STATE_DANGER)) {
        s_manual_mode = 0U;
        (void)can_send_control_ack(CAN_EVT_MANUAL_EXIT_DANGER, CAN_ACK_OK);
    }

    /* 手动/维护模式下不覆盖执行器（风扇/水泵/制冷/加热/蜂鸣/泄压阀），
     * 完全交给 CAN 直控命令；仅保留下方点火安全逻辑与状态指示灯。 */
    if(s_manual_mode == 0U) {
        pwm_set_enable(PWM_FAN, status.fan_enable);
        pwm_set_duty_percent(PWM_FAN, status.fan_duty_percent);
        pwm_set_enable(PWM_PUMP, status.pump_enable);
        pwm_set_duty_percent(PWM_PUMP, status.pump_duty_percent);

        /* 4个制冷片独立控制 */
        actor_set_channel(GPIO_CH_COOLER1, status.cooler_enable[0]);
        actor_set_channel(GPIO_CH_COOLER2, status.cooler_enable[1]);
        actor_set_channel(GPIO_CH_COOLER3, status.cooler_enable[2]);
        actor_set_channel(GPIO_CH_COOLER4, status.cooler_enable[3]);

        /* 4个PTC加热片独立控制 */
        actor_set_channel(GPIO_CH_HEATER1, status.heater_enable[0]);
        actor_set_channel(GPIO_CH_HEATER2, status.heater_enable[1]);
        actor_set_channel(GPIO_CH_HEATER3, status.heater_enable[2]);
        actor_set_channel(GPIO_CH_HEATER4, status.heater_enable[3]);

        actor_set_channel(GPIO_CH_BUZZER, status.buzzer_enable);
        actor_set_channel(GPIO_CH_GATE,   status.gate_enable);
    }

    /* DANGER 状态下强制切断点火（PF0 拉低），并锁定 ignition_task
     * 使其忽略此时的 KEY_3 切换请求；其余状态解锁，恢复按键正常控制。
     * 此逻辑在任何模式（含手动模式）下都执行，作为点火安全边界。 */
    s_ignition_locked = (status.ignition_allowed == 0U) ? 1U : 0U;
    if(s_ignition_locked != 0U) {
        ignition_set(0U);
    }

    /* 系统状态LED指示灯控制（互斥点亮，始终反映状态机状态） */
    actor_set_channel(GPIO_CH_LED_WHITE,  (status.state == SYSTEM_STATE_LOW_TEMP) ? 1U : 0U);
    actor_set_channel(GPIO_CH_LED_GREEN,  (status.state == SYSTEM_STATE_NORMAL) ? 1U : 0U);
    actor_set_channel(GPIO_CH_LED_YELLOW, (status.state == SYSTEM_STATE_HIGH_TEMP) ? 1U : 0U);
    actor_set_channel(GPIO_CH_LED_RED,    (status.state == SYSTEM_STATE_DANGER) ? 1U : 0U);
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

        system_state_update_input(now_ms);

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
        temp_cache_store(&result, sample_time_ms);

        /* 对齐到固定采样周期（已消耗约 780ms+读取时间，这里补足到 1s） */
        vTaskDelayUntil(&last_wake, pdMS_TO_TICKS(TEMP_SAMPLE_PERIOD_MS));
    }
}
/* ============================================================
 *  guard_enter / guard_exit : housekeeping around the patrol loop.
 *  Suspending app_task (rather than just leaving it running) is what
 *  lets the idle task actually see a long expected-idle-time and call
 *  portSUPPRESS_TICKS_AND_SLEEP() between patrols; app_task's normal
 *  20 ms period would otherwise keep the tick alive continuously.
 * ============================================================ */
static void guard_enter(void)
{
    s_guard_mode_active = 1U;

    if(s_app_task_handle != NULL) {
        vTaskSuspend(s_app_task_handle);
    }

    /* 挂起温度采集任务：guard 模式下继电器断电，DS18B20 无供电，采集无意义。
     * 巡检窗口内改由 guard_task 在重新上电后自行同步采集并写缓存。 */
    if(s_temp_task_handle != NULL) {
        vTaskSuspend(s_temp_task_handle);
    }

    /* stop actuators driven by the normal control loop before sleeping */
    relay_power_off();
    actor_set_all_off();
    pwm_set_enable(PWM_FAN, 0U);
    pwm_set_enable(PWM_PUMP, 0U);
    ignition_set(0U);   /* guard 模式下点火强制归零：点火任务继续运行，
                         * 但此时 PG0 已切断，PF0 的电平失去意义，
                         * 仅作软件状态同步 */

    gd_eval_led_off(LED1);
}

static void guard_exit(void)
{
    /* Restore full power: relay ON (PG0 high), app_task resumed.
     * Always reset ignition (PF0) to 0 when entering normal mode so
     * that any KEY_3 presses during guard have no accumulated effect
     * once we wake up. */
    ignition_set(0U);
    relay_power_on();
    s_guard_mode_active = 0U;

    if(s_app_task_handle != NULL) {
        vTaskResume(s_app_task_handle);
    }

    /* 恢复温度采集任务：回到正常模式，后台采集重新接管温度缓存刷新。
     * 采样历史让状态机在收到新样本时自然重建，无需在此特殊处理。 */
    if(s_temp_task_handle != NULL) {
        vTaskResume(s_temp_task_handle);
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
 *      reuses system_state_update_input() to sample/react exactly like
 *      app_task normally does;
 *    - waking the MCU from WFI does NOT re-power external sensors/
 *      actuators (PMU wake only restores the core), so PG0 must be
 *      re-asserted via relay_power_on() explicitly on every patrol,
 *      with a short settle delay before trusting sensor reads;
 *    - if the state machine stays at NORMAL during the whole patrol,
 *      the board is powered back off and we go back to the long sleep;
 *    - if any non-NORMAL state appears (LOW_TEMP / HIGH_TEMP /
 *      DANGER), the board stays powered and actuators stay driven
 *      for up to g_guard_handling_budget_ms, sampling every
 *      GUARD_PATROL_PERIOD_MS, until we either get back to NORMAL or
 *      the budget expires; in the latter case the next patrol
 *      continues where this one left off with PG0 still on;
 *    - KEY_4 pressed again (guard_key1_sem) aborts immediately, either
 *      out of the sleep, out of an in-progress patrol, or out of the
 *      handling window, and hands control back to app_task.
 *
 *  Boot:  init_task calls guard_enter() before deleting itself, so by
 *         the time this task is scheduled s_guard_mode_active is
 *         already 1. The first iteration of the outer loop therefore
 *         skips the outer wait + guard_enter() and goes straight into
 *         the patrol loop. The first KEY_4 press from the user wakes
 *         the inner semaphore and exits guard mode (normal operation).
 *         From then on every KEY_4 press toggles guard mode.
 * ============================================================ */
static void guard_task(void *pvParameters)
{
    (void)pvParameters;

    for( ;; ) {
        /* If guard is already active (we entered it from init_task
         * before guard_task even got a chance to run), skip the
         * outer wait + guard_enter() and go straight into the patrol
         * loop, which already blocks on guard_key1_sem with a timeout
         * and exits guard on the next KEY_4 press. */
        if(s_guard_mode_active == 0U) {
            /* idle, waiting for KEY_4 to request guard mode */
            if(xSemaphoreTake(guard_key1_sem, portMAX_DELAY) != pdTRUE) {
                continue;
            }

            guard_enter();
        }

        while(s_guard_mode_active != 0U) {
            /* long low-power sleep between patrols; tickless idle lets
             * the core WFI here instead of ticking every 1ms */
            if(xSemaphoreTake(guard_key1_sem, pdMS_TO_TICKS(g_guard_sleep_interval_ms)) == pdTRUE) {
                break; /* KEY_4 pressed again: exit guard mode */
            }

            /* woke up on schedule: power the external board, wait for
             * sensors to come up, then keep sampling/driving actuators
             * for as long as the state machine says "something is wrong". */
            relay_power_on();
            vTaskDelay(pdMS_TO_TICKS(GUARD_POWER_ON_SETTLE_MS));

            {
                TickType_t patrol_last_wake = xTaskGetTickCount();
                TickType_t patrol_end       = patrol_last_wake + pdMS_TO_TICKS(GUARD_PATROL_DURATION_MS);
                TickType_t handling_deadline = 0U;
                uint8_t    in_handling      = 0U;
                uint8_t    aborted          = 0U;

                while(xTaskGetTickCount() < patrol_end) {
                    uint32_t now_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

                    /* temp_task 在 guard 模式下已挂起，这里同步采集一次温度写入缓存，
                     * 再交给状态机消费（等价于旧版 update_input 内部的同步采集）。 */
                    temp_sample_blocking_to_cache(now_ms);
                    system_state_update_input(now_ms);

                    if(g_system_state_changed_flag != 0U) {
                        g_system_state_changed_flag = 0U;
                        (void)can_upload_system_state();
                        (void)can_upload_env();
                        (void)can_upload_temp();
                    }
                    can_process_pending_uploads();

                    /* KEY_4 during a patrol: cut it short and exit guard mode */
                    if(xSemaphoreTake(guard_key1_sem, 0) == pdTRUE) {
                        aborted = 1U;
                        break;
                    }

                    /* The actual decision: stay powered as long as the
                     * state machine reports something beyond NORMAL.
                     * NORMAL -> we may go back to the long sleep.
                     * Any other state -> keep the board powered and
                     * keep driving actuators until either we get back
                     * to NORMAL or the 10 s patrol window ends. */
                    if(system_state_get_state() != SYSTEM_STATE_NORMAL) {
                        if(in_handling == 0U) {
                            in_handling      = 1U;
                            handling_deadline = xTaskGetTickCount()
                                              + pdMS_TO_TICKS(g_guard_handling_budget_ms);
                        }
                    } else {
                        in_handling = 0U;
                    }

                    vTaskDelayUntil(&patrol_last_wake, pdMS_TO_TICKS(GUARD_PATROL_PERIOD_MS));
                }

                /* If we're handling a real condition, stay awake past the
                 * nominal 10 s window for up to g_guard_handling_budget_ms,
                 * still sampling every GUARD_PATROL_PERIOD_MS. KEY_4 still
                 * wins and breaks out immediately. */
                while((in_handling != 0U)
                   && (xTaskGetTickCount() < handling_deadline)
                   && (s_guard_mode_active != 0U)) {
                    uint32_t now_ms = (uint32_t)(xTaskGetTickCount() * portTICK_PERIOD_MS);

                    /* 同上：guard 模式下 temp_task 已挂起，先同步采集写缓存 */
                    temp_sample_blocking_to_cache(now_ms);
                    system_state_update_input(now_ms);

                    if(g_system_state_changed_flag != 0U) {
                        g_system_state_changed_flag = 0U;
                        (void)can_upload_system_state();
                        (void)can_upload_env();
                        (void)can_upload_temp();
                    }
                    can_process_pending_uploads();

                    if(xSemaphoreTake(guard_key1_sem, 0) == pdTRUE) {
                        aborted = 1U;
                        break;
                    }

                    if(system_state_get_state() == SYSTEM_STATE_NORMAL) {
                        in_handling = 0U;
                    }

                    vTaskDelayUntil(&patrol_last_wake, pdMS_TO_TICKS(GUARD_PATROL_PERIOD_MS));
                }

                /* Power the board back off ONLY if nothing required action.
                 * If we are still in an abnormal state at the deadline,
                 * we deliberately keep PG0 on across the next long sleep
                 * window: the next patrol will continue where this one
                 * left off, and actuators stay driven. */
                if((aborted == 0U) && (in_handling == 0U)) {
                    relay_power_off();
                }

                if(aborted != 0U) {
                    /* User pressed KEY_4 to leave guard mode: drop out
                     * of the patrol and let guard_exit() restore power. */
                    break;
                }
            }
        }

        guard_exit();
    }
}

/* ============================================================
 *  ignition_task : blocks on ignition_sem given by EXTI4 (KEY_3) ISR.
 * ============================================================ */
static void ignition_task(void *pvParameters)
{
    (void)pvParameters;

    for( ;; ) {
        if(xSemaphoreTake(ignition_sem, portMAX_DELAY) == pdTRUE) {
            /* DANGER 状态下 s_ignition_locked 为 1，忽略此次按键请求，
             * 保证点火始终保持在强制关闭状态。 */
            if(s_ignition_locked == 0U) {
                ignition_set((uint8_t)!ignition_get());
            }
        }
    }
}

/* ============================================================
 *  can_handle_control : 执行控制类命令（请求帧 Byte0=0x10）。
 *    在 can_rx_task 上下文调用，返回 ACK 结果码 (CAN_ACK_*)。
 *    0x00~0x05 已实现；0x06~0x0B 属维护模式直控，尚未实现，返回非法。
 *    电源开关不直接调用 guard_enter/exit（避免与 guard_task 抢占），
 *    而是按当前模式决定是否给 guard_key1_sem 触发一次状态切换。
 * ============================================================ */
static uint8_t can_handle_control(uint8_t msg_id, const uint8_t *param)
{
    switch(msg_id) {
    case CAN_CTL_POWER_ON:
        /* 仅当处于 guard 模式时才触发退出，回到正常模式 */
        if(s_guard_mode_active != 0U) {
            (void)xSemaphoreGive(guard_key1_sem);
        }
        return CAN_ACK_OK;

    case CAN_CTL_SLEEP:
        /* 仅当处于正常模式时才触发进入 guard */
        if(s_guard_mode_active == 0U) {
            (void)xSemaphoreGive(guard_key1_sem);
        }
        return CAN_ACK_OK;

    case CAN_CTL_IGNITE:
        /* DANGER 锁定时禁止打火 */
        if(s_ignition_locked != 0U) {
            return CAN_ACK_REJECTED;
        }
        ignition_set(1U);
        return CAN_ACK_OK;

    case CAN_CTL_EXTINGUISH:
        ignition_set(0U);
        return CAN_ACK_OK;

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
        s_manual_mode = 1U;
        return CAN_ACK_OK;

    case CAN_CTL_MANUAL_EXIT:
        s_manual_mode = 0U;
        return CAN_ACK_OK;

    /* --- 维护模式直控：仅手动模式下生效，否则拒绝 --- */
    case CAN_CTL_BUZZER_MUTE:
        if(s_manual_mode == 0U) { return CAN_ACK_NOT_MANUAL; }
        /* Byte2=1开/0关；静音即关闭蜂鸣器 */
        actor_set_channel(GPIO_CH_BUZZER, (param[0] != 0U) ? 1U : 0U);
        return CAN_ACK_OK;

    case CAN_CTL_COOLER:
        if(s_manual_mode == 0U) { return CAN_ACK_NOT_MANUAL; }
        if(param[0] > 3U) { return CAN_ACK_ILLEGAL; }
        actor_set_channel((actor_channel_t)(GPIO_CH_COOLER1 + param[0]),
                          (param[1] != 0U) ? 1U : 0U);
        return CAN_ACK_OK;

    case CAN_CTL_HEATER:
        if(s_manual_mode == 0U) { return CAN_ACK_NOT_MANUAL; }
        if(param[0] > 3U) { return CAN_ACK_ILLEGAL; }
        actor_set_channel((actor_channel_t)(GPIO_CH_HEATER1 + param[0]),
                          (param[1] != 0U) ? 1U : 0U);
        return CAN_ACK_OK;

    case CAN_CTL_FAN:
        if(s_manual_mode == 0U) { return CAN_ACK_NOT_MANUAL; }
        if(param[1] > 100U) { return CAN_ACK_ILLEGAL; }
        pwm_set_enable(PWM_FAN, (param[0] != 0U) ? 1U : 0U);
        pwm_set_duty_percent(PWM_FAN, param[1]);
        return CAN_ACK_OK;

    case CAN_CTL_PUMP:
        if(s_manual_mode == 0U) { return CAN_ACK_NOT_MANUAL; }
        if(param[1] > 100U) { return CAN_ACK_ILLEGAL; }
        pwm_set_enable(PWM_PUMP, (param[0] != 0U) ? 1U : 0U);
        pwm_set_duty_percent(PWM_PUMP, param[1]);
        return CAN_ACK_OK;

    case CAN_CTL_GATE:
        if(s_manual_mode == 0U) { return CAN_ACK_NOT_MANUAL; }
        actor_set_channel(GPIO_CH_GATE, (param[0] != 0U) ? 1U : 0U);
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
                (void)can_handle_query(msg_id);
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
