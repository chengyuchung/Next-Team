#include "can_app.h"
#include "can_driver.h"
#include "can_protocol.h"
#include "system_state.h"
#include "../BSW/EcuAL/temp_sensor.h"
#include "../BSW/EcuAL/adc_ecual.h"
#include "../BSW/Services/fault_manager.h"
#include "app_tasks.h"
#include "main.h"

/*
 * ============================================================================
 * 模块名称 : can_app
 * 文件功能 : CAN 应用层业务逻辑处理
 * ============================================================================
 */

volatile uint8_t g_can4_rx_event = 0U;

static volatile uint8_t s_upload_env_flag = 0U;
static volatile uint8_t s_upload_state_flag = 0U;
static volatile uint8_t s_upload_system_state_flag = 0U;
static volatile uint8_t s_upload_fault_flag = 0U;
static volatile uint8_t s_upload_temp_ch_mask = 0U;  /* bit0~3 = CH0~CH3 待上报 */
static volatile uint8_t s_upload_threshold_flag = 0U;
static volatile uint8_t s_upload_guard_sleep_flag = 0U;
static volatile uint8_t s_upload_guard_budget_flag = 0U;
static volatile uint8_t s_upload_adc_raw_flag = 0U;
static volatile uint8_t s_upload_gas_threshold_flag = 0U;
static volatile uint8_t s_upload_predict_status_flag = 0U;

void can_app_init(void)
{
    can_driver_gpio_config();
    can_driver_config(DTM_CAN4, 500U);
    can_driver_enable_rx_interrupt(DTM_CAN4, CAN4_RX_IRQ_PRIO);
}

ErrStatus can_app_handle_query(uint8_t msg_id)
{
    switch(msg_id) {
    case CAN_QRY_ENV:
        s_upload_env_flag = 1U;
        break;
    case CAN_QRY_STA:
        s_upload_state_flag = 1U;
        break;
    case CAN_QRY_SYS:
        s_upload_system_state_flag = 1U;
        break;
    case CAN_QRY_FLT:
        s_upload_fault_flag = 1U;
        break;
    case CAN_QRY_TEMP_CH0:
        s_upload_temp_ch_mask |= 0x01U;
        break;
    case CAN_QRY_TEMP_CH1:
        s_upload_temp_ch_mask |= 0x02U;
        break;
    case CAN_QRY_TEMP_CH2:
        s_upload_temp_ch_mask |= 0x04U;
        break;
    case CAN_QRY_TEMP_CH3:
        s_upload_temp_ch_mask |= 0x08U;
        break;
    case CAN_QRY_TEMP_ALL:
        /* 一次查询，MCU依次回复4帧（CH0~CH3，帧格式与单路查询一致） */
        s_upload_temp_ch_mask |= 0x0FU;
        break;
    case CAN_QRY_THRESHOLD:
        s_upload_threshold_flag = 1U;
        break;
    case CAN_QRY_GUARD_SLEEP:
        s_upload_guard_sleep_flag = 1U;
        break;
    case CAN_QRY_GUARD_BUDGET:
        s_upload_guard_budget_flag = 1U;
        break;
    case CAN_QRY_ADC_RAW:
        s_upload_adc_raw_flag = 1U;
        break;
    case CAN_QRY_GAS_THRESHOLD:
        s_upload_gas_threshold_flag = 1U;
        break;
    case CAN_QRY_PREDICT_STATUS:
        s_upload_predict_status_flag = 1U;
        break;
    default:
        return ERROR;
    }
    return SUCCESS;
}

void can_app_process_pending_uploads(void)
{
    if(s_upload_env_flag != 0U) {
        s_upload_env_flag = 0U;
        (void)can_app_upload_env();
    }

    if(s_upload_state_flag != 0U) {
        s_upload_state_flag = 0U;
        (void)can_app_upload_state();
    }

    if(s_upload_system_state_flag != 0U) {
        s_upload_system_state_flag = 0U;
        (void)can_app_upload_system_state();
    }

    if(s_upload_fault_flag != 0U) {
        s_upload_fault_flag = 0U;
        (void)can_app_upload_fault();
    }

    if(s_upload_temp_ch_mask != 0U) {
        uint8_t mask = s_upload_temp_ch_mask;
        s_upload_temp_ch_mask = 0U;
        (void)can_app_upload_temp_mask(mask);
    }

    if(s_upload_threshold_flag != 0U) {
        s_upload_threshold_flag = 0U;
        (void)can_app_upload_threshold();
    }

    if(s_upload_guard_sleep_flag != 0U) {
        s_upload_guard_sleep_flag = 0U;
        (void)can_app_upload_guard_sleep();
    }

    if(s_upload_guard_budget_flag != 0U) {
        s_upload_guard_budget_flag = 0U;
        (void)can_app_upload_guard_budget();
    }

    if(s_upload_adc_raw_flag != 0U) {
        s_upload_adc_raw_flag = 0U;
        (void)can_app_upload_adc_raw();
    }

    if(s_upload_gas_threshold_flag != 0U) {
        s_upload_gas_threshold_flag = 0U;
        (void)can_app_upload_gas_threshold();
    }

    if(s_upload_predict_status_flag != 0U) {
        s_upload_predict_status_flag = 0U;
        (void)can_app_upload_predict_status();
    }
}

ErrStatus can_app_upload_env(void)
{
    system_state_input_t input;
    temp_result_t temp_result;

    system_state_get_input(&input);
    temp_get_last(&temp_result);

    int16_t pressure_kpa = (int16_t)((input.pressure_pa < 0) ? 0 : ((uint32_t)input.pressure_pa / 1000U));

    return can_protocol_send_env_response(CAN_QRY_ENV, temp_result.maximum_temperature, pressure_kpa,
                                 input.pressure_alarm, input.gas_alarm);
}

ErrStatus can_app_upload_state(void)
{
    system_state_status_t status;
    system_state_get_status(&status);
    uint8_t fan_duty = status.fan_duty_percent;
    uint8_t pump_duty = status.pump_duty_percent;
    uint8_t cooler_on = (uint8_t)(status.cooler_enable[0] | status.cooler_enable[1] |
                                   status.cooler_enable[2] | status.cooler_enable[3]);
    uint8_t gate_on = status.gate_enable;
    return can_protocol_send_state_response(CAN_QRY_STA, fan_duty, pump_duty, cooler_on, gate_on);
}

ErrStatus can_app_upload_system_state(void)
{
    system_state_status_t status;
    system_state_get_status(&status);
    uint8_t level = (status.state == SYSTEM_STATE_NORMAL)   ? 1U :
                    (status.state == SYSTEM_STATE_LOW_TEMP)  ? 2U :
                    (status.state == SYSTEM_STATE_HIGH_TEMP) ? 3U : 4U;
    return can_protocol_send_system_state_response(CAN_QRY_SYS, level);
}

ErrStatus can_app_upload_fault(void)
{
    fault_manager_status_t fm_status;

    fault_manager_get_status(&fm_status);

    /* 上报新格式故障帧：
     * Byte2: 气体传感器故障
     * Byte3~7: 预留字段，暂无检测逻辑，全部填 0 */
    return can_protocol_send_fault_response(
        fm_status.gas_sensor_fault,      /* Byte2: 气体传感器 */
        fm_status.cooler_fault_rsvd,     /* Byte3: 制冷片（预留） */
        fm_status.heater_fault_rsvd,     /* Byte4: 加热片（预留） */
        fm_status.temp_sensor_fault_rsvd,/* Byte5: 温度传感器（预留） */
        fm_status.fan_fault_rsvd,        /* Byte6[7:4]: 风扇（预留） */
        fm_status.pump_fault_rsvd,       /* Byte6[3:0]: 水泵（预留） */
        fm_status.gate_fault_rsvd,       /* Byte7[7:4]: 排气阀（预留） */
        fm_status.press_sensor_fault_rsvd/* Byte7[3:0]: 气压传感器（预留） */
    );
}

ErrStatus can_app_upload_temp_mask(uint8_t ch_mask)
{
    static const uint8_t msg_id_of_ch[4] = {
        CAN_QRY_TEMP_CH0, CAN_QRY_TEMP_CH1, CAN_QRY_TEMP_CH2, CAN_QRY_TEMP_CH3
    };
    system_state_input_t input;
    ErrStatus ret = SUCCESS;
    uint8_t ch;

    system_state_get_input(&input);

    for(ch = 0U; ch < 4U; ch++) {
        if((ch_mask & (uint8_t)(1U << ch)) != 0U) {
            int16_t temp = input.zone_temp_valid[ch] ? input.zone_temperature_tenths[ch] : 0;
            if(can_protocol_send_temp_ch_response(msg_id_of_ch[ch], temp) != SUCCESS) {
                ret = ERROR;
            }
        }
    }

    return ret;
}

ErrStatus can_app_upload_temp(void)
{
    return can_app_upload_temp_mask(0x0FU);
}

ErrStatus can_app_upload_threshold(void)
{
    return can_protocol_send_threshold_response(CAN_QRY_THRESHOLD,
                                                 g_low_temp_threshold_tenths,
                                                 g_high_temp_threshold_tenths,
                                                 g_danger_temp_threshold_tenths);
}

ErrStatus can_app_upload_guard_sleep(void)
{
    uint16_t base_seconds    = (uint16_t)(g_guard_sleep_interval_ms / 1000U);
    uint16_t current_seconds = (uint16_t)(app_tasks_get_guard_current_sleep_ms() / 1000U);
    return can_protocol_send_guard_sleep_response(base_seconds, current_seconds);
}

ErrStatus can_app_upload_guard_budget(void)
{
    uint16_t base_seconds    = (uint16_t)(g_guard_handling_budget_ms / 1000U);
    uint16_t current_seconds = (uint16_t)(app_tasks_get_guard_current_budget_ms() / 1000U);
    return can_protocol_send_guard_budget_response(base_seconds, current_seconds);
}

ErrStatus can_app_upload_adc_raw(void)
{
    uint16_t gas_sensor_raw = 0U;

    /* 读取失败时保留 0，不影响上报（上位机可结合失败情况自行判断）。 */
    (void)adc_ecual_read_raw(ADC_ECUAL_CH_GAS_SENSOR, &gas_sensor_raw);

    /* 制冷片电流通道已移除，第二个参数填 0xFFFF 表示无效 */
    return can_protocol_send_adc_raw_response(gas_sensor_raw, 0xFFFFU);
}

ErrStatus can_app_upload_gas_threshold(void)
{
    return can_protocol_send_gas_threshold_response(g_gas_sensor_raw_min, g_gas_sensor_raw_max);
}

ErrStatus can_app_upload_predict_status(void)
{
    system_state_status_t status;
    system_state_get_status(&status);
    return can_protocol_send_predict_status_response(
        g_temp_prediction_enable,
        status.zone_predict_trigger_count);
}
