#ifndef _CAN_H
#define _CAN_H
#include "main.h"

typedef struct {
     
  uint32_t id;
  uint8_t data;
  uint8_t len;

} can_hand_t;

extern volatile uint8_t g_can4_rx_event;
/*
can_hand_t dtm_can0_data;
can_hand_t dtm_can2_data;
can_hand_t dtm_can5_data;
can_hand_t dtm_can4_data;
*/
void can_gpio_config(void);
void can_config(can_dtm_canx_enum dtm_canx, uint32_t baudrate_khz);

void DTM_CAN0_INT0_IRQHandler(void);
void DTM_CAN0_INT2_IRQHandler(void);
void DTM_CAN0_INT4_IRQHandler(void);
void DTM_CAN0_INT5_IRQHandler(void);
void can_enable_rx_interrupt(can_dtm_canx_enum dtm_canx, uint8_t irqn_priority);
void can4_rx0_irq_handler(void);
ErrStatus can_handle_query(uint8_t msg_id);
ErrStatus can_send_std_frame(can_dtm_canx_enum dtm_canx, uint32_t std_id, uint8_t *data, uint8_t len);


/*
 * ============================================================================
 * CAN 应用层协议（上位机 <-> MCU）
 *
 * 双向通信 ID（请求和响应共用同一 ID）：
 *   0x188  查询类（双向）：上位机查询请求 + MCU 数据响应
 *   0x189  控制类（双向）：上位机控制命令 + MCU ACK 响应
 *   0x18A  配置类（双向）：上位机配置命令 + MCU ACK 响应
 *
 * 通信方向通过 Byte0 的源节点地址区分：
 *   Byte0[7:4] = 源节点地址（0x1=上位机, 0x2=MCU）
 *   Byte0[3:0] = 保留（预留多节点扩展）
 *
 * 数据帧格式：
 *   Byte0      源节点地址（高4位）+ 保留（低4位）
 *   Byte1      消息号（具体功能）
 *   Byte2~7    数据段（根据消息号解析）
 *
 * 不再做软件 CRC（硬件 CRC 已保证完整性）。
 * ============================================================================
 */

/* 双向通信 ID（请求和响应共用） */
#define CAN_ID_QUERY             0x188U  /* 查询类：请求 + 数据响应 */
#define CAN_ID_CONTROL           0x189U  /* 控制类：命令 + ACK */
#define CAN_ID_CONFIG            0x18AU  /* 配置类：命令 + ACK */

/* 源节点地址（Byte0 高4位） */
#define CAN_NODE_HOST            0x10U   /* 上位机 */
#define CAN_NODE_MCU             0x20U   /* MCU */

/* 兼容旧定义 */
#define CAN_ID_CMD               CAN_ID_QUERY
#define CAN_ID_ACK               CAN_ID_CONTROL
#define CAN_ID_RESEND_REQUEST    0xFFFU

/* 查询类消息号（Byte1），ID=0x188 双向 */
#define CAN_QRY_ENV     0x00U  /* 环境数据（温度+压力+告警） */
#define CAN_QRY_STA     0x01U  /* 执行状态（风扇/水泵/制冷/阀门） */
#define CAN_QRY_SYS     0x02U  /* 系统状态等级（NORMAL/LOW_TEMP/HIGH_TEMP/DANGER） */
#define CAN_QRY_FLT     0x03U  /* 故障信息（执行器+传感器故障） */
#define CAN_QRY_TEMP    0x04U  /* 4路温度：请求号 + 第1帧响应号（ch0,ch1） */
#define CAN_QRY_TEMP_HI 0x05U  /* 4路温度：第2帧响应号（ch2,ch3），MCU 内部使用 */

/* 保留字节填充值（未使用的数据位统一填 0xCC，便于抓包识别） */
#define CAN_RSVD_FILL   0xCCU

/* 控制类消息号（Byte1），ID=0x189 双向 */
#define CAN_CTL_POWER_ON     0x00U /* 开电源 / 进入正常模式（退出 guard） */
#define CAN_CTL_SLEEP        0x01U /* 进入休眠 / guard 模式 */
#define CAN_CTL_IGNITE       0x02U /* 打火（PF0 拉高，DANGER 锁定时拒绝） */
#define CAN_CTL_EXTINGUISH   0x03U /* 熄火（PF0 拉低） */
#define CAN_CTL_RESET        0x04U /* 系统复位（Byte2~3 校验码防误触） */
#define CAN_CTL_CLEAR_FAULT  0x05U /* 清除故障 */
#define CAN_CTL_MANUAL_ENTER 0x06U /* 进入手动模式：状态机不再接管执行器 */
#define CAN_CTL_MANUAL_EXIT  0x07U /* 退出手动模式：恢复状态机自动接管 */
/* --- 以下为维护模式直控（仅手动模式下生效，否则回 CAN_ACK_NOT_MANUAL） --- */
#define CAN_CTL_BUZZER_MUTE  0x08U /* 蜂鸣器静音：Byte2=1开/0关 */
#define CAN_CTL_COOLER       0x09U /* 制冷片开关：Byte2=通道0~3, Byte3=1开/0关 */
#define CAN_CTL_HEATER       0x0AU /* 加热片开关：Byte2=通道0~3, Byte3=1开/0关 */
#define CAN_CTL_FAN          0x0BU /* 风扇：Byte2=1开/0关, Byte3=占空比0~100 */
#define CAN_CTL_PUMP         0x0CU /* 水泵：Byte2=1开/0关, Byte3=占空比0~100 */
#define CAN_CTL_GATE         0x0DU /* 排气阀：Byte2=1开/0关 */

/* 系统复位校验码（Byte2=高字节, Byte3=低字节），防误触 */
#define CAN_CTL_RESET_MAGIC  0xA5A5U

/* 配置类消息号（Byte1），ID=0x18A 双向 */
#define CAN_CFG_HIGH_TEMP_THRESHOLD     0x00U /* 设置高温阈值（Byte2=整数, Byte3=小数, 单位0.1°C） */
#define CAN_CFG_DANGER_TEMP_THRESHOLD   0x01U /* 设置危险阈值（Byte2=整数, Byte3=小数, 单位0.1°C） */
#define CAN_CFG_LOW_TEMP_THRESHOLD      0x02U /* 设置低温阈值（Byte2=整数, Byte3=小数, 单位0.1°C） */
#define CAN_CFG_FALLBACK_CONFIRM_COUNT  0x03U /* 设置回落确认次数（Byte2=次数） */
#define CAN_CFG_GUARD_SLEEP_INTERVAL    0x04U /* 设置巡检休眠时长（Byte2=十位, Byte3=个位, 单位秒, 16进制转10进制） */
#define CAN_CFG_GUARD_HANDLING_BUDGET   0x05U /* 设置异常处理预算（Byte2=十位, Byte3=个位, 单位秒, 16进制转10进制） */
#define CAN_CFG_APP_TASK_PERIOD         0x06U /* 设置状态机周期（Byte2=周期, 单位ms） */

/* ACK 响应结果码（Byte2，用于控制类和配置类响应） */
#define CAN_ACK_OK          0x00U /* 执行成功 */
#define CAN_ACK_REJECTED    0x01U /* 被拒绝（如 DANGER 锁定禁止打火） */
#define CAN_ACK_ILLEGAL     0x02U /* 非法命令 / 参数越界 */
#define CAN_ACK_CHECK_FAIL  0x03U /* 校验码错误（复位防误触） */
#define CAN_ACK_NOT_MANUAL  0x04U /* 未处于手动模式，直控命令被拒绝 */

/* 主动事件标识（Byte1 特殊值）：MCU 主动上报事件
 * 事件帧使用控制类 ID (0x189)，Byte0=CAN_NODE_MCU，Byte1=0xF0+ 来区分 */
#define CAN_EVT_MANUAL_EXIT_DANGER 0xF1U /* DANGER 触发，已强制退出手动模式 */

/* 0: 虚拟数据，1: 真实数据（已废弃，统一使用真实数据） */

/* 查询类数据响应格式（ID=0x188, Byte0=CAN_NODE_MCU）*/

/* CAN_QRY_ENV (0x00) 环境数据响应 */
typedef struct {
    int16_t temperature;    /* 最高温度，十分之一摄氏度 */
    int16_t pressure_kpa;   /* 压力，单位 kPa */
    uint8_t press_alarm;    /* 压力异常标志 */
    uint8_t gas_leak;       /* 气体泄漏标志 */
} can_env_data_t;

/* CAN_QRY_TEMP (0x04) 4路温度详细数据响应 */
typedef struct {
    int16_t temperature[4];  /* 4路温度，十分之一摄氏度 */
} can_temp_data_t;

/* CAN_QRY_STA (0x01) 执行状态响应 */
typedef struct {
    uint8_t fan_duty;      /* 风扇占空比 */
    uint8_t pump_duty;     /* 水泵占空比 */
    uint8_t cooler_on;     /* 制冷片开关 */
    uint8_t gate_on;       /* 排气阀开关 */
} can_state_data_t;

/* CAN_QRY_SYS (0x02) 系统状态等级响应 */
typedef struct {
    uint8_t level;         /* 1=NORMAL, 2=LOW_TEMP, 3=HIGH_TEMP, 4=DANGER */
    uint8_t reserved[7];
} can_system_state_data_t;

/*
 * CAN_QRY_FLT (0x03) 故障信息响应（6字节数据段）
 *
 * Byte2  [7:4] cooler_fault[3:0]  4个制冷片故障，bit0=1号...bit3=4号
 *        [3:0] heater_fault[3:0]  4个加热片故障，bit0=1号...bit3=4号
 * Byte3  [7:4] gas_sensor          气体传感器故障（bit0）
 *        [3:0] gate_fault          排气阀故障（bit0）
 * Byte4  [7:4] fan_fault           风扇故障（bit0）
 *        [3:0] pump_fault          水泵故障（bit0）
 * Byte5  [7:4] press_sensor        气压传感器故障（bit0）
 *        [3:0] 预留，填 0xC
 * Byte6~7 预留，填 0xCC
 */
typedef struct {
    uint8_t cooler_fault;   /* bit0~3 = 制冷片1~4 */
    uint8_t heater_fault;   /* bit0~3 = 加热片1~4 */
    uint8_t gas_sensor;
    uint8_t gate_fault;
    uint8_t fan_fault;
    uint8_t pump_fault;
    uint8_t press_sensor;
} can_fault_data_t;

/* 控制类/配置类 ACK 响应格式（ID=0x189/0x18A, Byte0=CAN_NODE_MCU）
 *   Byte0  源节点（CAN_NODE_MCU）
 *   Byte1  回显消息号
 *   Byte2  结果码（CAN_ACK_*）
 *   Byte3  当前点火状态
 *   Byte4  当前系统状态等级
 *   Byte5~7 保留
 */

void can_set_env_data(const can_env_data_t *data);
void can_set_state_data(const can_state_data_t *data);
void can_set_state_frame_data(const can_system_state_data_t *data);
void can_set_fault_data(const can_fault_data_t *data);
void can_set_temp_data(const can_temp_data_t *data);
ErrStatus can_upload_env(void);
ErrStatus can_upload_state(void);
ErrStatus can_upload_system_state(void);
ErrStatus can_upload_fault(void);
ErrStatus can_upload_temp(void);
void can_process_pending_uploads(void);
ErrStatus can_upload_all(void);
ErrStatus can_upload_demo(void);

/* 查询类响应发送函数（ID=0x188, Byte0=CAN_NODE_MCU） */
ErrStatus can_send_env_response(uint8_t msg_id, int16_t temp_tenths, int16_t pressure_kpa, uint8_t press_alarm, uint8_t gas_leak);
ErrStatus can_send_state_response(uint8_t msg_id, uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on);
ErrStatus can_send_system_state_response(uint8_t msg_id, uint8_t level);
/* 故障响应：cooler_mask/heater_mask 为 bit0~3 分别对应 1~4 号片；
 * 其余为单点故障标志（0=正常, 非0=故障）。数据接入前统一传 0。 */
ErrStatus can_send_fault_response(uint8_t cooler_mask, uint8_t heater_mask, uint8_t gas_sensor, uint8_t gate_fault, uint8_t fan_fault, uint8_t pump_fault, uint8_t press_sensor);
/* 温度响应：一次调用连发两帧（0x04: ch0,ch1 / 0x05: ch2,ch3） */
ErrStatus can_send_temp_response(int16_t temp_ch0, int16_t temp_ch1, int16_t temp_ch2, int16_t temp_ch3);

/* 控制类/配置类 ACK 响应发送函数（ID=0x189/0x18A, Byte0=CAN_NODE_MCU） */
ErrStatus can_send_control_ack(uint8_t msg_id, uint8_t result);
ErrStatus can_send_config_ack(uint8_t msg_id, uint8_t result);

/* 查询请求处理函数 */
ErrStatus can_handle_query(uint8_t msg_id);

#endif
