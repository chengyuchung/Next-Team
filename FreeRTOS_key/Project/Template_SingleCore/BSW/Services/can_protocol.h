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
#define CAN_QRY_ENV       0x00U
#define CAN_QRY_STA       0x01U
#define CAN_QRY_SYS       0x02U
#define CAN_QRY_FLT       0x03U
#define CAN_QRY_TEMP_CH0  0x04U  /* 分区温度 - 通道0 */
#define CAN_QRY_TEMP_CH1  0x05U  /* 分区温度 - 通道1 */
#define CAN_QRY_TEMP_CH2  0x06U  /* 分区温度 - 通道2 */
#define CAN_QRY_TEMP_CH3  0x07U  /* 分区温度 - 通道3 */
#define CAN_QRY_THRESHOLD 0x08U  /* 温度阈值查询 */
#define CAN_QRY_GUARD_SLEEP  0x09U  /* guard 睡眠时长查询（基准值 + 当前自适应值） */
#define CAN_QRY_GUARD_BUDGET 0x0AU  /* guard 巡检异常处理后 NORMAL 持续确认时长查询（基准值 + 当前自适应值） */
#define CAN_QRY_TEMP_ALL     0x0BU  /* 4路分区温度一次性查询：MCU依次回复4帧，
                                      * 消息号仍分别回显 CAN_QRY_TEMP_CH0~CH3，
                                      * 帧格式与单路查询完全一致 */
#define CAN_QRY_ADC_RAW      0x0CU  /* ADC原始raw值查询（气体传感器），
                                      * 用于现场标定 fault_manager 的固定阈值，
                                      * 标定完成后此查询可长期保留，不影响正常运行 */
#define CAN_QRY_GAS_THRESHOLD 0x0DU /* 气体传感器故障判定区间查询（下限+上限），
                                      * 用于核实 CAN_CFG_GAS_SENSOR_RAW_MIN/MAX
                                      * 配置命令是否生效 */
#define CAN_QRY_PREDICT_STATUS 0x0EU /* 异常升温预警功能状态查询：返回配置参数+告警标志 */
#define CAN_QRY_TEMP_RATE      0x0FU /* 4路分区温度变化量查询（调试用，单位 0.1°C/帧） */

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
#define CAN_CTL_TEMP_PREDICT_ENABLE 0x0EU  /* 异常升温预警功能使能开关 */

/* 系统复位校验码 */
#define CAN_CTL_RESET_MAGIC  0xA5A5U

/* 配置类消息号（Byte1），ID=0x18A 双向
 * 0x00~0x02 三个温度阈值配置：Byte[2,3] = uint16_t，高字节在前，
 * 单位 0.1°C（与 CAN_QRY_THRESHOLD 查询响应格式一致），取值范围 0~1000。 */
#define CAN_CFG_HIGH_TEMP_THRESHOLD     0x00U
#define CAN_CFG_DANGER_TEMP_THRESHOLD   0x01U
#define CAN_CFG_LOW_TEMP_THRESHOLD      0x02U
#define CAN_CFG_FALLBACK_CONFIRM_COUNT  0x03U
#define CAN_CFG_GUARD_SLEEP_INTERVAL    0x04U
#define CAN_CFG_GUARD_HANDLING_BUDGET   0x05U
#define CAN_CFG_APP_TASK_PERIOD         0x06U
#define CAN_CFG_GAS_SENSOR_RAW_MIN      0x07U  /* 气体传感器故障判定下限（ADC raw，0~4095） */
#define CAN_CFG_GAS_SENSOR_RAW_MAX      0x08U  /* 气体传感器故障判定上限（ADC raw，0~4095） */
#define CAN_CFG_RISE_DANGER_THRESHOLD   0x09U  /* 单次采样升温触发DANGER的阈值，Byte[2,3] uint16_t，
                                                * 高字节在前，单位0.1°C，范围1~200，默认20（=2.0°C）*/
#define CAN_CFG_RISE_HIGH_THRESHOLD     0x0AU  /* 单次采样升温触发HIGH_TEMP的阈值，Byte[2,3] uint16_t，
                                                * 高字节在前，单位0.1°C，范围1~200，默认15（=1.5°C）*/
#define CAN_CFG_RISE_CONFIRM_COUNT      0x0BU  /* 连续确认次数，Byte2 = uint8_t，范围1~10，默认2 */

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
    uint8_t gas_sensor;      /* 气体传感器故障（0=正常，1=故障） */
    uint8_t cooler_rsvd;     /* 制冷片故障（预留，填0） */
    uint8_t heater_rsvd;     /* 加热片故障（预留，填0） */
    uint8_t temp_sensor_rsvd;/* 温度传感器故障（预留，填0） */
    uint8_t fan_rsvd;        /* 风扇故障（预留，填0） */
    uint8_t pump_rsvd;       /* 水泵故障（预留，填0） */
    uint8_t gate_rsvd;       /* 排气阀故障（预留，填0） */
    uint8_t press_sensor_rsvd; /* 气压传感器故障（预留，填0） */
} can_fault_data_t;

typedef struct {
    uint16_t low_temp_threshold_tenths;
    uint16_t high_temp_threshold_tenths;
    uint16_t danger_temp_threshold_tenths;
} can_threshold_data_t;

typedef struct {
    uint16_t base_seconds;      /* 配置的基准值（g_guard_sleep_interval_ms / 1000） */
    uint16_t current_seconds;   /* 自适应算法当前实际生效的睡眠时长（秒） */
} can_guard_sleep_data_t;

typedef struct {
    uint16_t base_seconds;      /* 配置的基准值（g_guard_handling_budget_ms / 1000） */
    uint16_t current_seconds;   /* 自适应算法当前实际生效的确认时长（秒），只增不减 */
} can_guard_budget_data_t;

typedef struct {
    uint16_t gas_sensor_raw;    /* 气体传感器 ADC 原始值（PD11/ADC0_IN9，0~4095） */
    uint16_t reserved_raw;      /* 预留字段（原制冷片电流通道已移除，0xFFFF=无效） */
} can_adc_raw_data_t;

typedef struct {
    uint16_t raw_min;   /* 气体传感器故障判定下限（ADC raw，0~4095） */
    uint16_t raw_max;   /* 气体传感器故障判定上限（ADC raw，0~4095） */
} can_gas_threshold_data_t;

typedef struct {
    uint8_t enable;            /* 预警功能使能，1=开启，0=关闭 */
    uint16_t danger_threshold; /* DANGER 升温阈值，单位 0.1°C */
    uint16_t high_threshold;   /* HIGH_TEMP 升温阈值，单位 0.1°C */
    uint8_t predictive_alarm;  /* 全局预警告警标志 */
    uint8_t zone_predictive[4]; /* 各分区预警触发标志 */
} can_predict_status_data_t;

typedef struct {
    int16_t zone_temp_delta[4]; /* 各分区温度变化量，单位 0.1°C，符号表示升降 */
} can_temp_rate_data_t;

/*
 * CAN 协议层接口 - 查询类响应发送
 */
ErrStatus can_protocol_send_env_response(uint8_t msg_id, int16_t temp_tenths, int16_t pressure_kpa, uint8_t press_alarm, uint8_t gas_leak);
ErrStatus can_protocol_send_state_response(uint8_t msg_id, uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on);
ErrStatus can_protocol_send_system_state_response(uint8_t msg_id, uint8_t level);
ErrStatus can_protocol_send_fault_response(uint8_t gas_sensor, uint8_t cooler_rsvd, uint8_t heater_rsvd, uint8_t temp_sensor_rsvd, uint8_t fan_rsvd, uint8_t pump_rsvd, uint8_t gate_rsvd, uint8_t press_sensor_rsvd);
ErrStatus can_protocol_send_temp_ch_response(uint8_t msg_id, int16_t temp_tenths);
ErrStatus can_protocol_send_threshold_response(uint8_t msg_id, uint16_t low_temp, uint16_t high_temp, uint16_t danger_temp);
ErrStatus can_protocol_send_guard_sleep_response(uint16_t base_seconds, uint16_t current_seconds);
ErrStatus can_protocol_send_guard_budget_response(uint16_t base_seconds, uint16_t current_seconds);
ErrStatus can_protocol_send_adc_raw_response(uint16_t gas_sensor_raw, uint16_t reserved_raw);
ErrStatus can_protocol_send_gas_threshold_response(uint16_t raw_min, uint16_t raw_max);
ErrStatus can_protocol_send_predict_status_response(uint8_t enable, uint16_t danger_threshold,
                                                     uint16_t high_threshold, uint8_t predictive_alarm,
                                                     const uint8_t zone_predictive[4]);
ErrStatus can_protocol_send_temp_rate_response(uint8_t ch, int16_t delta_tenths);

/*
 * CAN 协议层接口 - 控制类/配置类 ACK 响应
 */
ErrStatus can_protocol_send_control_ack(uint8_t msg_id, uint8_t result);
ErrStatus can_protocol_send_config_ack(uint8_t msg_id, uint8_t result);

#ifdef __cplusplus
}
#endif

#endif /* CAN_PROTOCOL_H */
