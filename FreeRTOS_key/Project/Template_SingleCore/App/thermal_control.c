#include "thermal_control.h"
#include "BSW/Services/sensor_manager.h"
#include "BSW/Services/system_state.h"
#include "BSW/EcuAL/temp_sensor.h"
#include "BSW/EcuAL/pressure_sensor.h"
#include "BSW/EcuAL/gas_sensor.h"
#include "MCAL/actor_hal.h"
#include "motor_pwm_gd32.h"
#include "main.h"
#include "can_app.h"
#include "BSW/Services/fault_manager.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : thermal_control
 * 文件功能 : 热管理控制业务逻辑
 * 
 * 实现说明 :
 *   1) 聚合传感器数据（温度、压力、气体）并组装状态机输入；
 *   2) 驱动 system_state 热管理状态机；
 *   3) 根据状态机输出控制执行器（PWM、GPIO、继电器）；
 *   4) 支持手动模式与自动模式切换。
 * ============================================================================
 */

/* 手动/自动模式标志 */
static volatile uint8_t s_manual_mode = 0U;

/* 点火锁定标志（DANGER 状态强制锁定） */
static uint8_t s_ignition_locked = 0U;

/* 温度样本消费追踪（用于判定新样本） */
static uint32_t s_consumed_sample_time_ms = 0U;
static uint8_t  s_consumed_sample_valid = 0U;

void thermal_control_init(void)
{
    s_manual_mode = 0U;
    s_ignition_locked = 0U;
    s_consumed_sample_time_ms = 0U;
    s_consumed_sample_valid = 0U;
}

void thermal_control_set_manual_mode(uint8_t enable)
{
    s_manual_mode = (enable != 0U) ? 1U : 0U;
}

uint8_t thermal_control_get_manual_mode(void)
{
    return s_manual_mode;
}

uint8_t thermal_control_is_ignition_locked(void)
{
    return s_ignition_locked;
}

void thermal_control_update(uint32_t now_ms)
{
    system_state_input_t input = {0};
    pressure_sensor_data_t bmp_result = {0};
    temp_result_t temp_result = {0};
    gas_sensor_result_t gas_result = {0};
    system_state_status_t status;

    input.now_ms = now_ms;
    input.ignition_on = ignition_get();

    /* 4路DS18B20分区测温：改为从温度缓存非阻塞读取（由 temp_task 约每秒刷新），
     * 不再在这里忙等 ~800ms 采集，使控制循环得以按真实周期高频运行。
     * 下标i对应加热片(i+1)/制冷片(i+1)所在分区。 */
    {
        uint32_t sample_time_ms = 0U;
        uint8_t  has_sample = sensor_manager_load_temperature(&temp_result, &sample_time_ms);
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

    /* BMP280 只负责压力监测（泄压判断），不再参与温度风险判断。
     * 通过 ECUAL 层抽象接口读取，隔离驱动细节。 */
    if(pressure_sensor_read(&bmp_result) != 0U) {
        input.pressure_valid = bmp_result.valid;
        input.pressure_pa = bmp_result.pressure_pa;
        input.pressure_alarm = bmp_result.alarm;
    } else {
        input.pressure_valid = 0U;
        input.pressure_pa = 0;
        input.pressure_alarm = 0U;
    }

    (void)gas_sensor_task();
    if(get_gas(&gas_result) != 0U) {
        input.gas_valid = gas_result.valid;
        input.gas_alarm = gas_result.alarm;
    } else {
        input.gas_valid = 0U;
        input.gas_alarm = 0U;
    }

    system_state_task(&input);

    /* 气体传感器故障检测：读取 ADC 输出值，判断是否在正常区间，
     * 更新连续异常计数，并缓存结果供 fault_manager_get_status()
     *（CAN 上报等消费方）读取。必须每个控制周期都调用一次，
     * 否则故障计数永远不会推进。 */
    fault_manager_update();

    /* 应用状态机输出到执行器 */
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

    /* 系统状态LED指示灯控制（互斥点亮，始终反映状态机状态）
     *
     * 注意：这里控制的是硬件电路板上的状态指示灯（PG2~PG5），
     * 已改用独立引脚，不再与开发板板载 LED1~LED4 (PE10~PE13) 共用，
     * 避免 guard/点火/巡检等调试灯逻辑与温度状态灯互相覆盖。 */
    actor_set_channel(GPIO_CH_LED_WHITE,  (status.state == SYSTEM_STATE_LOW_TEMP) ? 1U : 0U);
    actor_set_channel(GPIO_CH_LED_GREEN,  (status.state == SYSTEM_STATE_NORMAL) ? 1U : 0U);
    actor_set_channel(GPIO_CH_LED_YELLOW, (status.state == SYSTEM_STATE_HIGH_TEMP) ? 1U : 0U);
    actor_set_channel(GPIO_CH_LED_RED,    (status.state == SYSTEM_STATE_DANGER) ? 1U : 0U);
}
