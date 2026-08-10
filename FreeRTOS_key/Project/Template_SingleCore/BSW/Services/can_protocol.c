#include "can_protocol.h"
#include "can_driver.h"
#include "system_state.h"
#include "main.h"

/*
 * ============================================================================
 * 模块名称 : can_protocol
 * 文件功能 : CAN 协议层实现 - 帧打包与解包
 * ============================================================================
 */

/*
 * can_protocol_send_env_response - 查询类环境数据响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_ENV）
 *   Byte[2,3]  最高温度 int16_t，高字节在前（0.1C 单位）
 *   Byte[4,5]  压力 int16_t，单位 kPa
 *   Byte6      压力报警标志
 *   Byte7      气体泄漏标志
 */
ErrStatus can_protocol_send_env_response(uint8_t msg_id, int16_t max_temp_tenths, int16_t pressure_kpa, uint8_t press_alarm, uint8_t gas_leak)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = (uint8_t)((uint16_t)max_temp_tenths >> 8);
    data[3] = (uint8_t)((uint16_t)max_temp_tenths & 0xFFU);
    data[4] = (uint8_t)((uint16_t)pressure_kpa >> 8);
    data[5] = (uint8_t)((uint16_t)pressure_kpa & 0xFFU);
    data[6] = press_alarm;
    data[7] = gas_leak;

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_state_response - 查询类执行状态响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0  源节点（0x20=MCU）
 *   Byte1  消息号（回显 CAN_QRY_STA）
 *   Byte2  风扇占空比
 *   Byte3  水泵占空比
 *   Byte4  制冷片开关
 *   Byte5  排气阀开关
 *   Byte6~7 保留
 */
ErrStatus can_protocol_send_state_response(uint8_t msg_id, uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = fan_duty;
    data[3] = pump_duty;
    data[4] = cooler_on;
    data[5] = gate_on;

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_system_state_response - 查询类系统状态等级响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0  源节点（0x20=MCU）
 *   Byte1  消息号（回显 CAN_QRY_SYS）
 *   Byte2  状态等级（1=NORMAL, 2=LOW_TEMP, 3=HIGH_TEMP, 4=DANGER）
 *   Byte3~7 保留
 */
ErrStatus can_protocol_send_system_state_response(uint8_t msg_id, uint8_t level)
{
    uint8_t data[8] = {0};
    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = level;
    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_fault_response - 查询类故障信息响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *
 * Byte0  源节点（CAN_NODE_MCU）
 * Byte1  消息号（CAN_QRY_FLT = 0x03）
 * Byte2  气体传感器故障（0=正常，1=故障）
 * Byte3  制冷片故障（预留，填 0）
 * Byte4  加热片故障（预留，填 0）
 * Byte5  温度传感器故障（预留，填 0）
 * Byte6  [7:4] 风扇故障（预留，填 0）
 *        [3:0] 水泵故障（预留，填 0）
 * Byte7  [7:4] 排气阀故障（预留，填 0）
 *        [3:0] 气压传感器故障（预留，填 0）
 */
ErrStatus can_protocol_send_fault_response(uint8_t gas_sensor,
                                   uint8_t cooler_rsvd,
                                   uint8_t heater_rsvd,
                                   uint8_t temp_sensor_rsvd,
                                   uint8_t fan_rsvd,
                                   uint8_t pump_rsvd,
                                   uint8_t gate_rsvd,
                                   uint8_t press_sensor_rsvd)
{
    uint8_t data[8] = {0};
    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_FLT;
    data[2] = (gas_sensor & 0x01U);
    data[3] = (cooler_rsvd & 0x01U);
    data[4] = (heater_rsvd & 0x01U);
    data[5] = (temp_sensor_rsvd & 0x01U);
    data[6] = (uint8_t)(((fan_rsvd & 0x01U) << 4) | (pump_rsvd & 0x01U));
    data[7] = (uint8_t)(((gate_rsvd & 0x01U) << 4) | (press_sensor_rsvd & 0x01U));
    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_temp_ch_response - 单路分区温度查询响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_TEMP_CH0~CH3）
 *   Byte[2,3]  该路温度 int16_t，高字节在前（0.1°C 单位）
 *   Byte4~7    预留，填 0xCC
 */
ErrStatus can_protocol_send_temp_ch_response(uint8_t msg_id, int16_t temp_tenths)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = (uint8_t)((uint16_t)temp_tenths >> 8);
    data[3] = (uint8_t)((uint16_t)temp_tenths & 0xFFU);
    data[4] = CAN_RSVD_FILL;
    data[5] = CAN_RSVD_FILL;
    data[6] = CAN_RSVD_FILL;
    data[7] = CAN_RSVD_FILL;

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_threshold_response - 查询类温度阈值响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_THRESHOLD）
 *   Byte[2,3]  低温阈值 uint16_t，高字节在前（0.1°C 单位）
 *   Byte[4,5]  高温阈值 uint16_t，高字节在前（0.1°C 单位）
 *   Byte[6,7]  危险阈值 uint16_t，高字节在前（0.1°C 单位）
 */
ErrStatus can_protocol_send_threshold_response(uint8_t msg_id, uint16_t low_temp, uint16_t high_temp, uint16_t danger_temp)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = (uint8_t)(low_temp >> 8);
    data[3] = (uint8_t)(low_temp & 0xFFU);
    data[4] = (uint8_t)(high_temp >> 8);
    data[5] = (uint8_t)(high_temp & 0xFFU);
    data[6] = (uint8_t)(danger_temp >> 8);
    data[7] = (uint8_t)(danger_temp & 0xFFU);

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_guard_sleep_response - guard 睡眠时长查询响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_GUARD_SLEEP）
 *   Byte[2,3]  基准值 uint16_t，高字节在前，单位：秒（对应 g_guard_sleep_interval_ms）
 *   Byte[4,5]  当前生效值 uint16_t，高字节在前，单位：秒（自适应算法实时结果）
 *   Byte6~7    预留，填 0xCC
 */
ErrStatus can_protocol_send_guard_sleep_response(uint16_t base_seconds, uint16_t current_seconds)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_GUARD_SLEEP;
    data[2] = (uint8_t)(base_seconds >> 8);
    data[3] = (uint8_t)(base_seconds & 0xFFU);
    data[4] = (uint8_t)(current_seconds >> 8);
    data[5] = (uint8_t)(current_seconds & 0xFFU);
    data[6] = CAN_RSVD_FILL;
    data[7] = CAN_RSVD_FILL;

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_guard_budget_response - guard 巡检异常处理后 NORMAL 持续确认时长查询响应
 *   (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_GUARD_BUDGET）
 *   Byte[2,3]  基准值 uint16_t，高字节在前，单位：秒（对应 g_guard_handling_budget_ms）
 *   Byte[4,5]  当前生效值 uint16_t，高字节在前，单位：秒（自适应算法实时结果，
 *              只增不减：本轮巡检出现过非 NORMAL 就增加 10%）
 *   Byte6~7    预留，填 0xCC
 */
ErrStatus can_protocol_send_guard_budget_response(uint16_t base_seconds, uint16_t current_seconds)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_GUARD_BUDGET;
    data[2] = (uint8_t)(base_seconds >> 8);
    data[3] = (uint8_t)(base_seconds & 0xFFU);
    data[4] = (uint8_t)(current_seconds >> 8);
    data[5] = (uint8_t)(current_seconds & 0xFFU);
    data[6] = CAN_RSVD_FILL;
    data[7] = CAN_RSVD_FILL;

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_control_ack - 控制类 ACK 响应 (ID: 0x189, Byte0=CAN_NODE_MCU)
 *   Byte0  源节点（0x20=MCU）
 *   Byte1  回显消息号
 *   Byte2  结果码（CAN_ACK_*）
 *   Byte3  当前点火状态
 *   Byte4  当前系统状态等级
 *   Byte5~7 保留
 */
/*
 * can_protocol_send_adc_raw_response - ADC原始raw值查询响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_ADC_RAW）
 *   Byte[2,3]  气体传感器 ADC raw uint16_t，高字节在前（PD11/ADC0_IN9，0~4095）
 *   Byte[4,5]  预留字段（原制冷片电流通道已移除，填 0xFFFF 表示无效）
 *   Byte6~7    预留，填 0xCC
 *
 * 用途：现场标定 fault_manager 固定阈值时，通过此帧直接读取气体传感器 ADC
 * 实测原始值，不依赖调试器。
 */
ErrStatus can_protocol_send_adc_raw_response(uint16_t gas_sensor_raw, uint16_t reserved_raw)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_ADC_RAW;
    data[2] = (uint8_t)(gas_sensor_raw >> 8);
    data[3] = (uint8_t)(gas_sensor_raw & 0xFFU);
    data[4] = (uint8_t)(reserved_raw >> 8);
    data[5] = (uint8_t)(reserved_raw & 0xFFU);
    data[6] = CAN_RSVD_FILL;
    data[7] = CAN_RSVD_FILL;

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_gas_threshold_response - 气体传感器故障判定区间查询响应
 *   (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_GAS_THRESHOLD）
 *   Byte[2,3]  下限 uint16_t，高字节在前（ADC raw，0~4095）
 *   Byte[4,5]  上限 uint16_t，高字节在前（ADC raw，0~4095）
 *   Byte6~7    预留，填 0xCC
 *
 * 用途：核实 CAN_CFG_GAS_SENSOR_RAW_MIN/MAX 配置命令是否生效。
 */
ErrStatus can_protocol_send_gas_threshold_response(uint16_t raw_min, uint16_t raw_max)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_GAS_THRESHOLD;
    data[2] = (uint8_t)(raw_min >> 8);
    data[3] = (uint8_t)(raw_min & 0xFFU);
    data[4] = (uint8_t)(raw_max >> 8);
    data[5] = (uint8_t)(raw_max & 0xFFU);
    data[6] = CAN_RSVD_FILL;
    data[7] = CAN_RSVD_FILL;

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_predict_status_response - 异常升温预警功能状态查询响应
 *   (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_PREDICT_STATUS）
 *   Byte2      使能标志（1=开启，0=关闭）
 *   Byte[3,4]  DANGER 升温阈值 uint16_t，高字节在前，单位 0.1°C
 *   Byte[5,6]  HIGH_TEMP 升温阈值 uint16_t，高字节在前，单位 0.1°C
 *   Byte7      全局预警告警标志（bit7=全局，bit0~3=zone0~3）
 */
ErrStatus can_protocol_send_predict_status_response(uint8_t enable, uint16_t danger_threshold,
                                                     uint16_t high_threshold, uint8_t predictive_alarm,
                                                     const uint8_t zone_predictive[4])
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_PREDICT_STATUS;
    data[2] = enable;
    data[3] = (uint8_t)(danger_threshold >> 8);
    data[4] = (uint8_t)(danger_threshold & 0xFFU);
    data[5] = (uint8_t)(high_threshold >> 8);
    data[6] = (uint8_t)(high_threshold & 0xFFU);
    data[7] = (uint8_t)((predictive_alarm ? 0x80U : 0U) |
                        (zone_predictive[0] ? 0x01U : 0U) |
                        (zone_predictive[1] ? 0x02U : 0U) |
                        (zone_predictive[2] ? 0x04U : 0U) |
                        (zone_predictive[3] ? 0x08U : 0U));

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

/*
 * can_protocol_send_temp_rate_response - 单个分区温度变化量查询响应
 *   (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_TEMP_RATE）
 *   Byte2      分区号（0~3）
 *   Byte[3,4]  温度变化量 int16_t，高字节在前，单位 0.1°C（符号表示升降）
 *   Byte5~7    预留，填 0xCC
 *
 * 用途：调试每帧升温幅度，负值表示降温，正值表示升温。
 */
ErrStatus can_protocol_send_temp_rate_response(uint8_t ch, int16_t delta_tenths)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_TEMP_RATE;
    data[2] = ch;
    data[3] = (uint8_t)((uint16_t)delta_tenths >> 8);
    data[4] = (uint8_t)((uint16_t)delta_tenths & 0xFFU);
    data[5] = CAN_RSVD_FILL;
    data[6] = CAN_RSVD_FILL;
    data[7] = CAN_RSVD_FILL;

    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

ErrStatus can_protocol_send_control_ack(uint8_t msg_id, uint8_t result)
{
    uint8_t data[8] = {0};
    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = result;
    data[3] = ignition_get();
    {
        system_state_status_t status;
        system_state_get_status(&status);
        data[4] = (status.state == SYSTEM_STATE_NORMAL)   ? 1U :
                  (status.state == SYSTEM_STATE_LOW_TEMP)  ? 2U :
                  (status.state == SYSTEM_STATE_HIGH_TEMP) ? 3U : 4U;
    }
    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_CONTROL, data, 8U);
}

/*
 * can_protocol_send_config_ack - 配置类 ACK 响应 (ID: 0x18A, Byte0=CAN_NODE_MCU)
 *   格式同控制类 ACK
 */
ErrStatus can_protocol_send_config_ack(uint8_t msg_id, uint8_t result)
{
    uint8_t data[8] = {0};
    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = result;
    data[3] = ignition_get();
    {
        system_state_status_t status;
        system_state_get_status(&status);
        data[4] = (status.state == SYSTEM_STATE_NORMAL)   ? 1U :
                  (status.state == SYSTEM_STATE_LOW_TEMP)  ? 2U :
                  (status.state == SYSTEM_STATE_HIGH_TEMP) ? 3U : 4U;
    }
    return can_driver_send_std_frame(DTM_CAN4, CAN_ID_CONFIG, data, 8U);
}
