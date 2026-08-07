#include "power_mode.h"
#include "relay_power.h"
#include "MCAL/actor_hal.h"
#include "motor_pwm_gd32.h"
#include "main.h"
#include "gd32a712_evb.h"

/*
 * ============================================================================
 * 模块名称 : power_mode
 * 文件功能 : 低功耗模式管理（Guard 巡检模式）
 * 
 * 实现说明 :
 *   1) 管理 guard 模式标志位（s_guard_mode_active）；
 *   2) 进入 guard：挂起 app_task/temp_task，关闭继电器和执行器；
 *   3) 退出 guard：恢复继电器电源，恢复任务；
 *   4) 提供查询接口供 ISR 和其他模块使用。
 * ============================================================================
 */

/* Guard 模式激活标志（需要在 ISR 中读取，因此声明为 volatile）
 * 注意：不声明为 static，因为 gd32a7xx_it.c 中的 CAN RX ISR 需要读取此标志
 * 来判断是否唤醒 guard_task。guard_enter/exit 是唯一的写入者。 */
volatile uint8_t s_guard_mode_active = 0U;

/* 任务句柄（用于挂起/恢复） */
static TaskHandle_t s_app_task_handle = NULL;
static TaskHandle_t s_temp_task_handle = NULL;

void power_mode_init(TaskHandle_t app_task_handle, TaskHandle_t temp_task_handle)
{
    s_app_task_handle = app_task_handle;
    s_temp_task_handle = temp_task_handle;
    s_guard_mode_active = 0U;
}

void power_mode_enter_guard(void)
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

    /* LED 指示：Guard 模式 */
    gd_eval_led_off(LED1);  /* LED1 灭表示系统未在正常工作 */
    gd_eval_led_on(LED2);   /* LED2 亮表示进入 Guard 模式 */
}

void power_mode_exit_guard(void)
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

    /* LED 指示：正常模式 */
    gd_eval_led_on(LED1);   /* LED1 亮表示系统正常工作 */
    gd_eval_led_off(LED2);  /* LED2 灭表示退出 Guard 模式 */
}

uint8_t power_mode_is_guard_active(void)
{
    return s_guard_mode_active;
}
