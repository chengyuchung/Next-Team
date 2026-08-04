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
void bsp_board_config(void);
void can_config(can_dtm_canx_enum dtm_canx, uint32_t baudrate_khz);
void canfd_config(void);
void communication_check(void);
ErrStatus dtm_can4_message_transmit_test(void);
ErrStatus dtm_can0_message_transmit_test(void);

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
 * 方向由报文 ID 区分：
 *   0x188  上位机 -> MCU  请求帧（查询 / 控制 / 配置）
 *   0x186  MCU -> 上位机  响应帧（控制 / 配置 的执行结果 ACK）
 *
 * 数据帧仍走各自独立 ID（0x180~0x184），保留完整 8 字节，
 * 查询类请求的响应即为对应数据帧，不走 0x186。
 *
 * 请求帧（0x188）字节布局：
 *   Byte0  类别 category : 0x00=查询  0x10=控制  0x20=配置
 *   Byte1  消息号 msg id  : 该类别下的具体功能
 *   Byte2~7             : 仅配置类使用（携带参数），查询/控制类不使用
 *
 * 不再做软件 CRC（硬件 CRC 已保证完整性）。
 * ============================================================================
 */

/* 数据帧 ID（MCU -> 上位机，查询响应即为这些帧） */
#define CAN_ID_ENV               0x180U
#define CAN_ID_STA               0x181U
#define CAN_ID_SYS_STATE         0x182U
#define CAN_ID_FLT               0x183U
#define CAN_ID_TEMP              0x184U  /* 4路温度，每路2字节，共8字节 */

/* 方向 ID */
#define CAN_ID_CMD               0x188U  /* 上位机 -> MCU  请求帧 */
#define CAN_ID_ACK               0x186U  /* MCU -> 上位机  响应/回执帧 */
#define CAN_ID_RESEND_REQUEST    0xFFFU

#define CAN_APP_ID_ENV       CAN_ID_ENV
#define CAN_APP_ID_STATE     CAN_ID_STA
#define CAN_APP_ID_SYS_STATE CAN_ID_SYS_STATE
#define CAN_APP_ID_FAULT     CAN_ID_FLT
#define CAN_APP_ID_TEMP      CAN_ID_TEMP
#define CAN_APP_ID_CMD       CAN_ID_CMD
#define CAN_APP_ID_ACK       CAN_ID_ACK

/* 请求帧 Byte0：类别 */
#define CAN_CAT_QUERY   0x00U  /* 查询类（请求上报，无副作用） */
#define CAN_CAT_CONTROL 0x10U  /* 控制类（有副作用） */
#define CAN_CAT_CONFIG  0x20U  /* 配置类（改参数，Byte2~7 带数据） */

/* 查询类消息号（Byte1），响应走对应数据帧 ID */
#define CAN_QRY_ENV     0x00U  /* 环境数据    -> 0x180 */
#define CAN_QRY_STA     0x01U  /* 执行状态    -> 0x181 */
#define CAN_QRY_SYS     0x02U  /* 系统状态等级 -> 0x182 */
#define CAN_QRY_FLT     0x03U  /* 故障信息    -> 0x183 */
#define CAN_QRY_TEMP    0x04U  /* 4路温度     -> 0x184 */

/* 控制类消息号（Byte1） */
#define CAN_CTL_POWER_ON     0x00U /* 开电源 / 进入正常模式（退出 guard） */
#define CAN_CTL_SLEEP        0x01U /* 进入休眠 / guard 模式 */
#define CAN_CTL_IGNITE       0x02U /* 打火（PF0 拉高，DANGER 锁定时拒绝） */
#define CAN_CTL_EXTINGUISH   0x03U /* 熄火（PF0 拉低） */
#define CAN_CTL_RESET        0x04U /* 系统复位（Byte2~3 校验码防误触） */
#define CAN_CTL_CLEAR_FAULT  0x05U /* 清除故障 */
/* --- 以下为维护模式直控（仅手动模式下生效，否则回 CAN_ACK_NOT_MANUAL） --- */
#define CAN_CTL_BUZZER_MUTE  0x06U /* 蜂鸣器静音：Byte2=1开/0关 */
#define CAN_CTL_COOLER       0x07U /* 制冷片开关：Byte2=通道0~3, Byte3=1开/0关 */
#define CAN_CTL_HEATER       0x08U /* 加热片开关：Byte2=通道0~3, Byte3=1开/0关 */
#define CAN_CTL_FAN          0x09U /* 风扇：Byte2=1开/0关, Byte3=占空比0~100 */
#define CAN_CTL_PUMP         0x0AU /* 水泵：Byte2=1开/0关, Byte3=占空比0~100 */
#define CAN_CTL_GATE         0x0BU /* 排气阀：Byte2=1开/0关 */

/* 手动/维护模式进退（显式切换） */
#define CAN_CTL_MANUAL_ENTER 0x0CU /* 进入手动模式：状态机不再接管执行器 */
#define CAN_CTL_MANUAL_EXIT  0x0DU /* 退出手动模式：恢复状态机自动接管 */

/* 系统复位校验码（Byte2=高字节, Byte3=低字节），防误触 */
#define CAN_CTL_RESET_MAGIC  0xA5A5U

/* 配置类消息号（Byte1） */
#define CAN_CFG_HIGH_TEMP_THRESHOLD     0x00U /* 设置高温阈值（Byte2=整数, Byte3=小数, 单位0.1°C） */
#define CAN_CFG_DANGER_TEMP_THRESHOLD   0x01U /* 设置危险阈值（Byte2=整数, Byte3=小数, 单位0.1°C） */
#define CAN_CFG_LOW_TEMP_THRESHOLD      0x02U /* 设置低温阈值（Byte2=整数, Byte3=小数, 单位0.1°C） */
#define CAN_CFG_FALLBACK_CONFIRM_COUNT  0x03U /* 设置回落确认次数（Byte2=次数） */
#define CAN_CFG_GUARD_SLEEP_INTERVAL    0x04U /* 设置巡检休眠时长（Byte2=十位, Byte3=个位, 单位秒, 16进制转10进制） */
#define CAN_CFG_GUARD_HANDLING_BUDGET   0x05U /* 设置异常处理预算（Byte2=十位, Byte3=个位, 单位秒, 16进制转10进制） */
#define CAN_CFG_APP_TASK_PERIOD         0x06U /* 设置状态机周期（Byte2=周期, 单位ms） */

/* ACK 帧（0x186）结果码（Byte2） */
#define CAN_ACK_OK          0x00U /* 执行成功 */
#define CAN_ACK_REJECTED    0x01U /* 被拒绝（如 DANGER 锁定禁止打火） */
#define CAN_ACK_ILLEGAL     0x02U /* 非法命令 / 参数越界 */
#define CAN_ACK_CHECK_FAIL  0x03U /* 校验码错误（复位防误触） */
#define CAN_ACK_NOT_MANUAL  0x04U /* 未处于手动模式，直控命令被拒绝 */

/* 主动事件帧（0x186）：MCU 主动上报，非请求响应。
 * 用 Byte0=CAN_CAT_EVENT 与普通 ACK 区分。 */
#define CAN_CAT_EVENT       0xF0U /* 事件类（MCU 主动上报） */
#define CAN_EVT_MANUAL_EXIT_DANGER 0x01U /* DANGER 触发，已强制退出手动模式 */

/* 兼容旧调用点（逐步废弃） */
#define CAN_CMD_ENV     CAN_QRY_ENV
#define CAN_CMD_STA     CAN_QRY_STA
#define CAN_CMD_ALM     CAN_QRY_SYS
#define CAN_CMD_FLT     CAN_QRY_FLT
#define CAN_CMD_TEMP    CAN_QRY_TEMP

/* 0: 虚拟数据，1: 真实数据（已废弃，统一使用真实数据） */

typedef struct {
    int16_t temperature;    /* 最高温度，十分之一摄氏度 */
    int16_t pressure_kpa; /* 压力，单位 kPa */
    uint8_t press_alarm;   /* 压力异常标志 */
    uint8_t gas_leak;      /* 气体泄漏标志 */
} can_env_data_t;

/*
 * 温度帧数据 (0x184)
 *   4路温度，每路 int16_t，十分之一摄氏度
 *   Byte[0,1] = 通道0温度
 *   Byte[2,3] = 通道1温度
 *   Byte[4,5] = 通道2温度
 *   Byte[6,7] = 通道3温度
 */
typedef struct {
    int16_t temperature[4];  /* 4路温度，十分之一摄氏度 */
} can_temp_data_t;

typedef struct {
    uint8_t fan_duty;      /* 风扇占空比 */
    uint8_t pump_duty;     /* 水泵占空比 */
    uint8_t cooler_on;     /* 制冷片开关 */
    uint8_t gate_on;       /* 排气阀开关 */
} can_state_data_t;

/*
 * 系统状态帧数据：
 *   使用 1~4 表示系统状态等级：
 *     1 = NORMAL
 *     2 = LOW_TEMP
 *     3 = HIGH_TEMP
 *     4 = DANGER
 *   其余字节保留，便于后续扩展。
 */
typedef struct {
    uint8_t level;
    uint8_t reserved[7];
} can_system_state_data_t;


typedef struct {
    uint8_t fan;
    uint8_t pump;
    uint8_t cool;
    uint8_t gate;
    uint8_t temp_sensor;
    uint8_t press_sensor;
    uint8_t gas_sensor;
} can_fault_data_t;

/* 请求帧格式（0x188）：Byte0=类别, Byte1=消息号, Byte2~7=配置类参数 */
typedef struct {
    uint8_t category;   /* CAN_CAT_* */
    uint8_t msg_id;     /* 该类别下的具体功能 */
    uint8_t param[6];   /* 仅配置类使用 */
} can_request_t;

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
ErrStatus can_send_env(int16_t temp_tenths, int16_t pressure_pa, uint8_t press_alarm, uint8_t gas_leak);
ErrStatus can_send_state(uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on);
ErrStatus can_send_system_state(uint8_t level);
ErrStatus can_send_fault(uint8_t fault_fan, uint8_t fault_pump, uint8_t fault_cool, uint8_t fault_gate, uint8_t fault_temp_sensor, uint8_t fault_press_sensor, uint8_t fault_gas_sensor);
ErrStatus can_send_temp(int16_t temp_ch0, int16_t temp_ch1, int16_t temp_ch2, int16_t temp_ch3);
ErrStatus can_handle_query(uint8_t msg_id);
ErrStatus can_send_ack(uint8_t category, uint8_t msg_id, uint8_t result);

#endif
