#include "can_app.h"
#include "can_driver.h"
#include "can_protocol.h"
#include "system_state.h"
#include "../BSW/EcuAL/temp_sensor.h"

/*
 * ============================================================================
 * 模块名称 : can_app
 * 文件功能 : CAN 应用层业务逻辑处理
 * ============================================================================
 */

volatile uint8_t g_can4_rx_event = 0U;
volatile uint8_t g_system_state_changed_flag = 0U;

static volatile uint8_t s_upload_env_flag = 0U;
static volatile uint8_t s_upload_state_flag = 0U;
static volatile uint8_t s_upload_system_state_flag = 0U;
static volatile uint8_t s_upload_fault_flag = 0U;
static volatile uint8_t s_upload_temp_flag = 0U;

void can_app_init(void)
{
    can_driver_gpio_config();
    can_driver_config(DTM_CAN4, 500U);
    can_driver_enable_rx_interrupt(DTM_CAN4, 2U);
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
    case CAN_QRY_TEMP:
        s_upload_temp_flag = 1U;
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

    if(s_upload_temp_flag != 0U) {
        s_upload_temp_flag = 0U;
        (void)can_app_upload_temp();
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
    return can_protocol_send_fault_response(0U, 0U, 0U, 0U, 0U, 0U, 0U);
}

ErrStatus can_app_upload_temp(void)
{
    system_state_input_t input;
    system_state_get_input(&input);

    int16_t temp_ch0 = input.zone_temp_valid[0] ? input.zone_temperature_tenths[0] : 0;
    int16_t temp_ch1 = input.zone_temp_valid[1] ? input.zone_temperature_tenths[1] : 0;
    int16_t temp_ch2 = input.zone_temp_valid[2] ? input.zone_temperature_tenths[2] : 0;
    int16_t temp_ch3 = input.zone_temp_valid[3] ? input.zone_temperature_tenths[3] : 0;

    return can_protocol_send_temp_response(temp_ch0, temp_ch1, temp_ch2, temp_ch3);
}
