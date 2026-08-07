#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <stdint.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : can_protocol
 * 文件功能 : CAN 应用层协议定义（BSW Services 层）
 *
 * 设计目标 :
 *   1) 定义 CAN 帧格式、ID、消息号、数据结构；
 *   2) 提供帧的打包和解包接口；
 *   3) 不包含业务逻辑处理，只负责协议层的数据转换。
 *
 * 协议说明 :
 *   双向通信 ID：
 *     0x188  查询类（双向）：上位机查询请求 + MCU 数据响应
 *     0x189  控制类（双向）：上位机控制命令 + MCU ACK 响应
 *     0x18A  配置类（双向）：上位机配置命令 + MCU ACK 响应
 *
 *   通信方向通过 Byte0 的源节点地址区分：
 *     Byte0[7:4] = 源节点地址（0x1=上位机, 0x2=MCU）
 * ============================================================================
 */

/* 双向通信 ID（请求和响应共用） */
#define CAN_ID_QUERY             0x188U
#define CAN_ID_CONTROL           0x189U
#define CAN_ID_CONFIG            0x18AU

/* 源节点地址（Byte0 高4位） */
#define CAN_NODE_HOST            0x10U
#define CAN_NODE_MCU             0x20U

/* 兼容旧定义 */
#define CAN_ID_CMD               CAN_ID_QUERY
#define CAN_ID_ACK               CAN_ID_CONTROL
#define CAN_ID_RESEND_REQUEST    0xFFFU

/* 查询类消息号（Byte1），ID=0x188 双向 */
#define CAN_QRY_ENV     0x00U
#define CAN_QRY_STA     0x01U
#define CAN_QRY_SYS     0x02U
#define CAN_QRY_FLT       0x03U
#define CAN_QRY_TEMP      0x04U
#define CAN_QRY_TEMP_HI   0x05U
#define CAN_QRY_THRESHOLD 0x06U

/* 保留字节填充值 */
#define CAN_RSVD_FILL   0xCCU

/* 控制类消息号（Byte1），ID=0x189 双向 */
#define CAN_CTL_POWER_ON     0x00U
#define CAN_CTL_SLEEP        0x01U
#define CAN_CTL_IGNITE       0x02U
#define CAN_CTL_EXTINGUISH   0x03U
#define CAN_CTL_RESET        0x04U
#define CAN_CTL_CLEAR_FAULT  0x05U
#define CAN_CTL_MANUAL_ENTER 0x06U
#define CAN_CTL_MANUAL_EXIT  0x07U
#define CAN_CTL_BUZZER_MUTE  0x08U
#define CAN_CTL_COOLER       0x09U
#define CAN_CTL_HEATER       0x0AU
#define CAN_CTL_FAN          0x0BU
#define CAN_CTL_PUMP         0x0CU
#define CAN_CTL_GATE         0x0DU

/* 系统复位校验码 */
#define CAN_CTL_RESET_MAGIC  0xA5A5U

/* 配置类消息号（Byte1），ID=0x18A 双向 */
#define CAN_CFG_HIGH_TEMP_THRESHOLD     0x00U
#define CAN_CFG_DANGER_TEMP_THRESHOLD   0x01U
#define CAN_CFG_LOW_TEMP_THRESHOLD      0x02U
#define CAN_CFG_FALLBACK_CONFIRM_COUNT  0x03U
#define CAN_CFG_GUARD_SLEEP_INTERVAL    0x04U
#define CAN_CFG_GUARD_HANDLING_BUDGET   0x05U
#define CAN_CFG_APP_TASK_PERIOD         0x06U

/* ACK 响应结果码（Byte2） */
#define CAN_ACK_OK          0x00U
#define CAN_ACK_REJECTED    0x01U
#define CAN_ACK_ILLEGAL     0x02U
#define CAN_ACK_CHECK_FAIL  0x03U
#define CAN_ACK_NOT_MANUAL  0x04U

/* 主动事件标识（Byte1 特殊值） */
#define CAN_EVT_MANUAL_EXIT_DANGER 0xF1U

/* 查询类数据响应格式 */
typedef struct {
    int16_t temperature;
    int16_t pressure_kpa;
    uint8_t press_alarm;
    uint8_t gas_leak;
} can_env_data_t;

typedef struct {
    int16_t temperature[4];
} can_temp_data_t;

typedef struct {
    uint8_t fan_duty;
    uint8_t pump_duty;
    uint8_t cooler_on;
    uint8_t gate_on;
} can_state_data_t;

typedef struct {
    uint8_t level;
    uint8_t reserved[7];
} can_system_state_data_t;

typedef struct {
    uint8_t cooler_fault;
    uint8_t heater_fault;
    uint8_t gas_sensor;
    uint8_t gate_fault;
    uint8_t fan_fault;
    uint8_t pump_fault;
    uint8_t press_sensor;
} can_fault_data_t;

typedef struct {
    uint16_t low_temp_threshold_tenths;
    uint16_t high_temp_threshold_tenths;
    uint16_t danger_temp_threshold_tenths;
} can_threshold_data_t;

/*
 * CAN 协议层接口 - 查询类响应发送
 */
ErrStatus can_protocol_send_env_response(uint8_t msg_id, int16_t temp_tenths, int16_t pressure_kpa, uint8_t press_alarm, uint8_t gas_leak);
ErrStatus can_protocol_send_state_response(uint8_t msg_id, uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on);
ErrStatus can_protocol_send_system_state_response(uint8_t msg_id, uint8_t level);
ErrStatus can_protocol_send_fault_response(uint8_t cooler_mask, uint8_t heater_mask, uint8_t gas_sensor, uint8_t gate_fault, uint8_t fan_fault, uint8_t pump_fault, uint8_t press_sensor);
ErrStatus can_protocol_send_temp_response(int16_t temp_ch0, int16_t temp_ch1, int16_t temp_ch2, int16_t temp_ch3);
ErrStatus can_protocol_send_threshold_response(uint8_t msg_id, uint16_t low_temp, uint16_t high_temp, uint16_t danger_temp);

/*
 * CAN 协议层接口 - 控制类/配置类 ACK 响应
 */
ErrStatus can_protocol_send_control_ack(uint8_t msg_id, uint8_t result);
ErrStatus can_protocol_send_config_ack(uint8_t msg_id, uint8_t result);

#ifdef __cplusplus
}
#endif

#endif /* CAN_PROTOCOL_H */
