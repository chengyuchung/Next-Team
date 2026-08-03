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
ErrStatus can_handle_cmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3);
ErrStatus can_send_std_frame(can_dtm_canx_enum dtm_canx, uint32_t std_id, uint8_t *data, uint8_t len);
uint8_t can_crc8(const uint8_t *data, uint8_t len);


#define CAN_ID_ENV               0x180U
#define CAN_ID_STA               0x181U
#define CAN_ID_SYS_STATE         0x182U
#define CAN_ID_FLT               0x183U
#define CAN_ID_CMD               0x188U
#define CAN_ID_RESEND_REQUEST    0xFFFU

#define CAN_APP_ID_ENV       CAN_ID_ENV
#define CAN_APP_ID_STATE     CAN_ID_STA
#define CAN_APP_ID_SYS_STATE CAN_ID_SYS_STATE
#define CAN_APP_ID_FAULT     CAN_ID_FLT
#define CAN_APP_ID_CMD       CAN_ID_CMD

#define CAN_CMD_ENV     0x00U
#define CAN_CMD_STA     0x01U
#define CAN_CMD_ALM     0x02U
#define CAN_CMD_FLT     0x03U

/* 0: 虚拟数据，1: 真实数据 */
#ifndef CAN_APP_USE_REAL_DATA
#define CAN_APP_USE_REAL_DATA  1U
#endif

typedef struct {
    uint16_t temp_int;
    uint16_t temp_frac;
    uint16_t press_int;
    uint16_t press_frac;
    uint8_t gas_leak;
} can_env_data_t;

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

/* 命令帧格式：Byte0=cmd, Byte1~3=arg, Byte4~7=预留 */
typedef struct {
    uint8_t cmd;
    uint8_t arg1;
    uint8_t arg2;
    uint8_t arg3;
    uint8_t reserved[4];
} can_cmd_data_t;

void can_set_env_data(const can_env_data_t *data);
void can_set_state_data(const can_state_data_t *data);
void can_set_state_frame_data(const can_system_state_data_t *data);
void can_set_fault_data(const can_fault_data_t *data);
ErrStatus can_upload_env(void);
ErrStatus can_upload_state(void);
ErrStatus can_upload_system_state(void);
ErrStatus can_upload_fault(void);
void can_process_pending_uploads(void);
ErrStatus can_upload_all(void);
ErrStatus can_upload_demo(void);
ErrStatus can_send_env(uint16_t temp_int, uint16_t temp_frac, uint16_t press_int, uint16_t press_frac, uint8_t gas_leak);
ErrStatus can_send_state(uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on);
ErrStatus can_send_system_state(uint8_t level);
ErrStatus can_send_fault(uint8_t fault_fan, uint8_t fault_pump, uint8_t fault_cool, uint8_t fault_gate, uint8_t fault_temp_sensor, uint8_t fault_press_sensor, uint8_t fault_gas_sensor);
ErrStatus can_handle_cmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3);
ErrStatus can_send_cmd_reply(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3);

#endif
