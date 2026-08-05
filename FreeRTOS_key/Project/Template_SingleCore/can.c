#include "can.h"
#include "main.h"
#include "fault_manager.h"
#include "system_state.h"
#include "temp_sensor.h"
#include <string.h>

/*
 * CAN 应用层实现
 * 初始化 CAN 时钟与 CAN0/CAN2/CAN4/CAN5 的引脚及参数
 * 双向通信 ID 设计：
 *   0x188 查询类（双向）：上位机查询请求 + MCU 数据响应
 *   0x189 控制类（双向）：上位机控制命令 + MCU ACK 响应
 *   0x18A 配置类（双向）：上位机配置命令 + MCU ACK 响应
 * 通过 Byte0 高4位区分方向：0x1=上位机, 0x2=MCU
 */


can_transmit_message_struct tx_message;
can_receive_message_struct rx_message;
can_transmit_message_struct fdtx_message;
can_receive_message_struct fdrx_message;
volatile uint8_t g_can4_rx_event = 0U;

static volatile uint8_t s_upload_env_flag = 0U;
static volatile uint8_t s_upload_state_flag = 0U;
static volatile uint8_t s_upload_system_state_flag = 0U;
static volatile uint8_t s_upload_fault_flag = 0U;
static volatile uint8_t s_upload_temp_flag = 0U;

/*
 * 系统状态变化标志
 *   由 system_state 模块置位
 *   用于触发状态变化时主动上报 CAN 数据
 */
volatile uint8_t g_system_state_changed_flag = 0U;

/*
 * CAN 上报缓存：环境数据/执行状态/系统状态/故障信息/温度数据
 * 由应用层写入，发送函数从这里读取并组帧
 */
static can_env_data_t s_env = {0};
static can_state_data_t s_state = {0};
static can_system_state_data_t s_system_state_frame = {0};
static can_fault_data_t s_fault = {0};
static can_temp_data_t s_temp = {{0}};

void can_gpio_config(void)
{
    rcu_dtm_can_clock_config(DTM_CAN0, RCU_DTM_CANSRC_PCLK2);
    rcu_periph_clock_enable(RCU_DTM_CAN0);
    rcu_dtm_can_clock_config(DTM_CAN1, RCU_DTM_CANSRC_PCLK2);
    rcu_periph_clock_enable(RCU_DTM_CAN1);
    rcu_dtm_can_clock_config(DTM_CAN2, RCU_DTM_CANSRC_PCLK2);
    rcu_periph_clock_enable(RCU_DTM_CAN2);
    rcu_dtm_can_clock_config(DTM_CAN3, RCU_DTM_CANSRC_PCLK2);
    rcu_periph_clock_enable(RCU_DTM_CAN3);
    rcu_dtm_can_clock_config(DTM_CAN4, RCU_DTM_CANSRC_PCLK2);
    rcu_periph_clock_enable(RCU_DTM_CAN4);
    rcu_dtm_can_clock_config(DTM_CAN5, RCU_DTM_CANSRC_PCLK2);
    rcu_periph_clock_enable(RCU_DTM_CAN5);
    rcu_dtm_can_clock_config(DTM_CAN6, RCU_DTM_CANSRC_PCLK2);
    rcu_periph_clock_enable(RCU_DTM_CAN6);
    rcu_dtm_can_clock_config(DTM_CAN7, RCU_DTM_CANSRC_PCLK2);
    rcu_periph_clock_enable(RCU_DTM_CAN7);
    rcu_periph_clock_enable(RCU_GPIOH);
    rcu_periph_clock_enable(RCU_GPIOM);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOE);

    can_deinit(DTM_CAN0);
    can_deinit(DTM_CAN2);
    can_deinit(DTM_CAN4);
    can_deinit(DTM_CAN5);

    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_10);
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_10);
    gpio_af_set(GPIOH, GPIO_AF_4, GPIO_PIN_10);

    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_12);
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_af_set(GPIOH, GPIO_AF_8, GPIO_PIN_12);

    gpio_output_options_set(GPIOM, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_2);
    gpio_mode_set(GPIOM, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_2);
    gpio_af_set(GPIOM, GPIO_AF_3, GPIO_PIN_2);

    gpio_output_options_set(GPIOM, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_3);
    gpio_mode_set(GPIOM, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_3);
    gpio_af_set(GPIOM, GPIO_AF_8, GPIO_PIN_3);

    gpio_output_options_set(GPIOH, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_11);
    gpio_mode_set(GPIOH, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_11);
    gpio_af_set(GPIOH, GPIO_AF_1, GPIO_PIN_11);

    gpio_output_options_set(GPIOB, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_12);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_12);
    gpio_af_set(GPIOB, GPIO_AF_8, GPIO_PIN_12);

    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_15);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_PULLUP, GPIO_PIN_15);
    gpio_af_set(GPIOE, GPIO_AF_3, GPIO_PIN_15);

    gpio_output_options_set(GPIOE, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_14);
    gpio_mode_set(GPIOE, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO_PIN_14);
    gpio_af_set(GPIOE, GPIO_AF_8, GPIO_PIN_14);
}



void can_config(can_dtm_canx_enum dtm_canx, uint32_t baudrate_khz)
{
    can_parameter_struct can_param;
    can_filter_struct can_filter;
    can_rx_fifo_struct rx_fifo0_config;
    can_tx_buffer_struct tx_buffer_config;
    can_filter_element_struct filter_element;

    can_struct_para_init(CAN_INIT_STRUCT, &can_param);
    can_struct_para_init(CAN_FILTER_STRUCT, &can_filter);
    can_struct_para_init(CAN_RX_FIFO_STRUCT, &rx_fifo0_config);
    can_struct_para_init(CAN_TX_BUFFER_STRUCT, &tx_buffer_config);
    can_struct_para_init(CAN_FILTER_ELEMENT_STRUCT, &filter_element);

    can_param.auto_retransmission_enable = ENABLE;
    can_param.transmit_pause_enable = DISABLE;
    can_param.edge_filter_enable = DISABLE;
    can_param.protocol_exception_enable = DISABLE;
    can_param.wide_message_enable = DISABLE;

    {
        uint32_t can_clock_khz = 80000U;
        uint32_t tseg1 = 13U;
        uint32_t tseg2 = 6U;
        uint32_t total_tq = tseg1 + tseg2 + 1U;
        uint32_t prescaler = (can_clock_khz / baudrate_khz) / total_tq;
        can_param.prescaler = prescaler;
        can_param.resync_jump_width = 2;
        can_param.time_segment_1 = tseg1;
        can_param.time_segment_2 = tseg2;
    }

    can_filter.non_match_std_frame_accept = CAN_ACCEPT_INTO_RXFIFO0;
    can_filter.non_match_ext_frame_accept = CAN_ACCEPT_INTO_RXFIFO0;
    can_filter.remote_std_frame_accept = CAN_REMOTE_FILTER;
    can_filter.remote_ext_frame_accept = CAN_REMOTE_FILTER;
    can_filter.filter_start_address_std_frame = 0;
    can_filter.filter_start_address_ext_frame = 0;
    can_filter.filter_number_std_frame = 1;
    can_filter.filter_number_ext_frame = 0;
    can_filter.and_mask_ext_frame = 0;

    rx_fifo0_config.fifo_operation_mode = CAN_RXFIFO_BLOCKING;
    rx_fifo0_config.fifo_watermark = 0;
    rx_fifo0_config.fifo_size = 8;
    rx_fifo0_config.fifo_start_address = 0x100;
    rx_fifo0_config.fifo_element_size = CAN_RXFS_8BYTES;

    tx_buffer_config.tx_buffer_start_address = 0x300;
    tx_buffer_config.dedicate_buffer_size = 4;
    tx_buffer_config.fifo_or_queue_mode = CAN_TXFIFO_OPERATION;
    tx_buffer_config.fifo_or_queue_size = 4;
    tx_buffer_config.tx_buffer_element_size = CAN_TXBS_8BYTES;

    can_param.filter_config = &can_filter;
    can_param.rx_fifo0_config = &rx_fifo0_config;
    can_param.rx_fifo1_config = NULL;
    can_param.rx_buffer_config = NULL;
    can_param.tx_buffer_config = &tx_buffer_config;
    can_param.tx_event_fifo_config = NULL;

    while(SET != can_sram_init_state_get(dtm_canx)) {
    }
    can_init(dtm_canx, &can_param);
    can_operating_mode_enable(dtm_canx, CAN_MODE_NORMAL);
}

void canfd_config(void)
{
    can_parameter_struct can_param;
    can_filter_struct can_filter;
    can_rx_fifo_struct rx_fifo0_config;
    can_tx_buffer_struct tx_buffer_config;
    can_filter_element_struct filter_element;
    can_fd_parameter_struct can_fd_param;

    can_struct_para_init(CAN_INIT_STRUCT, &can_param);
    can_struct_para_init(CAN_FILTER_STRUCT, &can_filter);
    can_struct_para_init(CAN_RX_FIFO_STRUCT, &rx_fifo0_config);
    can_struct_para_init(CAN_TX_BUFFER_STRUCT, &tx_buffer_config);
    can_struct_para_init(CAN_FILTER_ELEMENT_STRUCT, &filter_element);
    can_struct_para_init(CAN_FD_INIT_STRUCT, &can_fd_param);

    can_param.auto_retransmission_enable = ENABLE;
    can_param.transmit_pause_enable = DISABLE;
    can_param.edge_filter_enable = ENABLE;
    can_param.protocol_exception_enable = ENABLE;
    can_param.wide_message_enable = DISABLE;

    can_param.prescaler = 4;
    can_param.resync_jump_width = 2;
    can_param.time_segment_1 = 13;
    can_param.time_segment_2 = 6;

    can_fd_param.bitrate_switch_enable = ENABLE;
    can_fd_param.iso_can_fd_enable = ENABLE;
    can_fd_param.tdc_enable = DISABLE;
    can_fd_param.prescaler = 2;
    can_fd_param.resync_jump_width = 2;
    can_fd_param.time_segment_1 = 13;
    can_fd_param.time_segment_2 = 6;

    can_filter.non_match_std_frame_accept = CAN_ACCEPT_INTO_RXFIFO0;
    can_filter.non_match_ext_frame_accept = CAN_ACCEPT_INTO_RXFIFO0;
    can_filter.remote_std_frame_accept = CAN_REMOTE_FILTER;
    can_filter.remote_ext_frame_accept = CAN_REMOTE_FILTER;
    can_filter.filter_start_address_std_frame = 0;
    can_filter.filter_start_address_ext_frame = 0;
    can_filter.filter_number_std_frame = 1;
    can_filter.filter_number_ext_frame = 0;
    can_filter.and_mask_ext_frame = 0;

    rx_fifo0_config.fifo_operation_mode = CAN_RXFIFO_BLOCKING;
    rx_fifo0_config.fifo_watermark = 0;
    rx_fifo0_config.fifo_size = 8;
    rx_fifo0_config.fifo_start_address = 0x100;
    rx_fifo0_config.fifo_element_size = CAN_RXFS_16BYTES;

    tx_buffer_config.tx_buffer_start_address = 0x300;
    tx_buffer_config.dedicate_buffer_size = 4;
    tx_buffer_config.fifo_or_queue_mode = CAN_TXFIFO_OPERATION;
    tx_buffer_config.fifo_or_queue_size = 4;
    tx_buffer_config.tx_buffer_element_size = CAN_TXBS_16BYTES;

    can_param.filter_config = &can_filter;
    can_param.rx_fifo0_config = &rx_fifo0_config;
    can_param.rx_fifo1_config = NULL;
    can_param.rx_buffer_config = NULL;
    can_param.tx_buffer_config = &tx_buffer_config;
    can_param.tx_event_fifo_config = NULL;

    filter_element.filter_type = CAN_FILTER_RANGE;
    filter_element.config = CAN_FILTER_TO_RXFIFO0;
    filter_element.id1 = CAN_ID_QUERY;
    filter_element.id2_or_mask_or_rxbuffercfg = CAN_ID_CONFIG;

    while(SET != can_sram_init_state_get(DTM_CAN0)) {
    }
    can_init(DTM_CAN0, &can_param);
    while(SET != can_sram_init_state_get(DTM_CAN2)) {
    }
    can_init(DTM_CAN2, &can_param);

    can_filter_set(DTM_CAN0, CAN_FF_STANDARD, 0, &filter_element);
    can_filter_set(DTM_CAN2, CAN_FF_STANDARD, 0, &filter_element);

    can_operating_mode_enable(DTM_CAN0, CAN_MODE_INIT);
    can_fd_config(DTM_CAN0, &can_fd_param);
    can_operating_mode_enable(DTM_CAN2, CAN_MODE_INIT);
    can_fd_config(DTM_CAN2, &can_fd_param);

    can_interrupt_enable(DTM_CAN2, CAN_INT_RFIFO0_NEW);
    can_mcan_interrupt_line_config(DTM_CAN2, CAN_INTR_LINE0, CAN_INT_RFIFO0_NEW);
    can_mcan_interrupt_line_enable(DTM_CAN2, CAN_INTR_LINE0);
    nvic_irq_enable(DTM_CAN2_INT0_IRQn, 0, 0);

    can_operating_mode_enable(DTM_CAN2, CAN_MODE_NORMAL);
    can_operating_mode_enable(DTM_CAN0, CAN_MODE_NORMAL);
}

/**
 * @brief  DTM CAN4 报文发送测试
 * @note   构造一帧固定数据从 DTM CAN4 发送，用于验证 CAN 通道是否正常
 * @param  None
 *
 * @retval ErrStatus
 *         - SUCCESS: 报文已加入发送队列
 *         - ERROR:   无可用发送邮箱
 */
ErrStatus dtm_can4_message_transmit_test(void)
{
    uint8_t transmit_mailbox = 0;
    ErrStatus ret = SUCCESS;
    uint16_t i;

    /* 初始化 CAN 发送报文结构 */
    can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &tx_message);
    tx_message.id = CAN_ID_QUERY;
    tx_message.rtr = CAN_FT_DATA;
    tx_message.xtd = CAN_FF_STANDARD;
    tx_message.esi = 0;
    tx_message.brs = DISABLE;
    tx_message.fdf = DISABLE;
    tx_message.message_marker = 0;
    tx_message.ev_fifo_control = CAN_TXEVENT_FIFO_DISABLE;
    tx_message.data_bytes = 8;

    /* 填充 8 字节测试数据 */
    for(i = 0; i < 8; i++) {
        tx_message.data[i] = i + 1;
    }

    /* 申请发送邮箱并准备 CAN 报文 */
    transmit_mailbox = can_message_transmit_prepare(DTM_CAN4, &tx_message);
    if(transmit_mailbox == 0xFF) {
        ret = ERROR;
    } else {
        /* 将报文加入发送队列 */
        can_message_transmit_add(DTM_CAN4, transmit_mailbox);
    }
    return ret;
}

ErrStatus dtm_can0_message_transmit_test(void)
{
    uint8_t transmit_mailbox = 0;
    ErrStatus ret = SUCCESS;
    uint16_t i;

    can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &fdtx_message);
    fdtx_message.id = CAN_ID_QUERY;
    fdtx_message.rtr = CAN_FT_DATA;
    fdtx_message.xtd = CAN_FF_STANDARD;
    fdtx_message.esi = 0;
    fdtx_message.brs = ENABLE;
    fdtx_message.fdf = ENABLE;
    fdtx_message.message_marker = 0;
    fdtx_message.ev_fifo_control = CAN_TXEVENT_FIFO_DISABLE;
    fdtx_message.data_bytes = 16;
    for(i = 0; i < 16; i++) {
        fdtx_message.data[i] = i + 1;
    }

    transmit_mailbox = can_message_transmit_prepare(DTM_CAN0, &fdtx_message);
    if(transmit_mailbox == 0xFF) {
        ret = ERROR;
    } else {
        can_message_transmit_add(DTM_CAN0, transmit_mailbox);
    }
    return ret;
}

ErrStatus can_send_std_frame(can_dtm_canx_enum dtm_canx, uint32_t std_id, uint8_t *data, uint8_t len)
{
    if(len > 8U) {
        len = 8U;
    }

    can_transmit_message_struct tx_msg;
    uint8_t mailbox;
    can_struct_para_init(CAN_TX_MESSAGE_STRUCT, &tx_msg);

    tx_msg.id = std_id;
    tx_msg.xtd = CAN_FF_STANDARD;
    tx_msg.rtr = CAN_FT_DATA;
    tx_msg.fdf = DISABLE;
    tx_msg.brs = DISABLE;
    tx_msg.data_bytes = len;
    for(uint8_t i = 0U; i < len; i++) {
        tx_msg.data[i] = data[i];
    }

    mailbox = can_message_transmit_prepare(dtm_canx, &tx_msg);
    if(mailbox == 0xFF) {
        return ERROR;
    }
    can_message_transmit_add(dtm_canx, mailbox);
    return SUCCESS;
}

void can_set_env_data(const can_env_data_t *data)
{
    if(data != NULL) {
        s_env = *data;
    }
}

void can_set_state_data(const can_state_data_t *data)
{
    if(data != NULL) {
        s_state = *data;
    }
}

void can_set_state_frame_data(const can_system_state_data_t *data)
{
    if(data != NULL) {
        s_system_state_frame = *data;
    }
}

void can_set_fault_data(const can_fault_data_t *data)
{
    if(data != NULL) {
        s_fault = *data;
    }
}

void can_set_temp_data(const can_temp_data_t *data)
{
    if(data != NULL) {
        s_temp = *data;
    }
}


/*
 * can_send_env_response - 查询类环境数据响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0      源节点（0x20=MCU）
 *   Byte1      消息号（回显 CAN_QRY_ENV）
 *   Byte[2,3]  最高温度 int16_t，高字节在前（0.1C 单位）
 *   Byte[4,5]  压力 int16_t，单位 kPa
 *   Byte6      压力报警标志
 *   Byte7      气体泄漏标志
 */
ErrStatus can_send_env_response(uint8_t msg_id, int16_t max_temp_tenths, int16_t pressure_kpa, uint8_t press_alarm, uint8_t gas_leak)
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

    return can_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

ErrStatus can_upload_env(void)
{
    system_state_input_t input;
    temp_result_t temp_result;

    system_state_get_input(&input);
    temp_get_last(&temp_result);

    int16_t pressure_kpa = (int16_t)((input.pressure_pa < 0) ? 0 : ((uint32_t)input.pressure_pa / 1000U));

    return can_send_env_response(CAN_QRY_ENV, temp_result.maximum_temperature, pressure_kpa,
                                 input.pressure_alarm, input.gas_alarm);
}

/*
 * can_send_state_response - 查询类执行状态响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0  源节点（0x20=MCU）
 *   Byte1  消息号（回显 CAN_QRY_STA）
 *   Byte2  风扇占空比
 *   Byte3  水泵占空比
 *   Byte4  制冷片开关
 *   Byte5  排气阀开关
 *   Byte6~7 保留
 */
ErrStatus can_send_state_response(uint8_t msg_id, uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on)
{
    uint8_t data[8] = {0};

    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = fan_duty;
    data[3] = pump_duty;
    data[4] = cooler_on;
    data[5] = gate_on;

    return can_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

ErrStatus can_upload_state(void)
{
    system_state_status_t status;
    system_state_get_status(&status);
    uint8_t fan_duty = status.fan_duty_percent;
    uint8_t pump_duty = status.pump_duty_percent;
    uint8_t cooler_on = (uint8_t)(status.cooler_enable[0] | status.cooler_enable[1] |
                                   status.cooler_enable[2] | status.cooler_enable[3]);
    uint8_t gate_on = status.gate_enable;
    return can_send_state_response(CAN_QRY_STA, fan_duty, pump_duty, cooler_on, gate_on);
}

/*
 * can_send_system_state_response - 查询类系统状态等级响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *   Byte0  源节点（0x20=MCU）
 *   Byte1  消息号（回显 CAN_QRY_SYS）
 *   Byte2  状态等级（1=NORMAL, 2=LOW_TEMP, 3=HIGH_TEMP, 4=DANGER）
 *   Byte3~7 保留
 */
ErrStatus can_send_system_state_response(uint8_t msg_id, uint8_t level)
{
    uint8_t data[8] = {0};
    data[0] = CAN_NODE_MCU;
    data[1] = msg_id;
    data[2] = level;
    return can_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

ErrStatus can_upload_system_state(void)
{
    system_state_status_t status;
    system_state_get_status(&status);
    uint8_t level = (status.state == SYSTEM_STATE_NORMAL)   ? 1U :
                    (status.state == SYSTEM_STATE_LOW_TEMP)  ? 2U :
                    (status.state == SYSTEM_STATE_HIGH_TEMP) ? 3U : 4U;
    return can_send_system_state_response(CAN_QRY_SYS, level);
}

/*
 * can_send_fault_response - 查询类故障信息响应 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *
 * Byte0  源节点（CAN_NODE_MCU）
 * Byte1  消息号（CAN_QRY_FLT = 0x03）
 * Byte2  [7:4] cooler_mask  制冷片故障掩码（bit0~3 = 1~4号片）
 *        [3:0] heater_mask  加热片故障掩码（bit0~3 = 1~4号片）
 * Byte3  [7:4] gas_sensor   气体传感器故障（bit0）
 *        [3:0] gate_fault   排气阀故障（bit0）
 * Byte4  [7:4] fan_fault    风扇故障（bit0）
 *        [3:0] pump_fault   水泵故障（bit0）
 * Byte5  [7:4] press_sensor 气压传感器故障（bit0）
 *        [3:0] 预留，填 0xC
 * Byte6~7 预留，填 0xCC
 */
ErrStatus can_send_fault_response(uint8_t cooler_mask, uint8_t heater_mask,
                                   uint8_t gas_sensor, uint8_t gate_fault,
                                   uint8_t fan_fault, uint8_t pump_fault,
                                   uint8_t press_sensor)
{
    uint8_t data[8] = {0};
    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_FLT;
    data[2] = (uint8_t)(((cooler_mask & 0x0FU) << 4) | (heater_mask & 0x0FU));
    data[3] = (uint8_t)(((gas_sensor  & 0x01U) << 4) | (gate_fault  & 0x01U));
    data[4] = (uint8_t)(((fan_fault   & 0x01U) << 4) | (pump_fault  & 0x01U));
    data[5] = (uint8_t)(((press_sensor & 0x01U) << 4) | 0x0CU);
    data[6] = CAN_RSVD_FILL;
    data[7] = CAN_RSVD_FILL;
    return can_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);
}

ErrStatus can_upload_fault(void)
{
    /* TODO: 接入真实执行器故障检测数据后替换下方占位 0。
     * 当前仅上报传感器有效性故障，执行器故障暂时全部填 0。 */
    return can_send_fault_response(0U, 0U, 0U, 0U, 0U, 0U, 0U);
}

/*
 * can_send_temp_response - 4路温度查询响应，连发两帧 (ID: 0x188, Byte0=CAN_NODE_MCU)
 *
 * 帧1（Byte1=CAN_QRY_TEMP 0x04）：
 *   Byte2~3  ch0 温度（int16_t，高字节在前，0.1°C 单位）
 *   Byte4~5  ch1 温度
 *   Byte6~7  预留，填 0xCC
 *
 * 帧2（Byte1=CAN_QRY_TEMP_HI 0x05）：
 *   Byte2~3  ch2 温度
 *   Byte4~5  ch3 温度
 *   Byte6~7  预留，填 0xCC
 *
 * 主机只需发一帧请求（Byte1=0x04），MCU 自动回两帧。
 */
ErrStatus can_send_temp_response(int16_t temp_ch0, int16_t temp_ch1,
                                  int16_t temp_ch2, int16_t temp_ch3)
{
    uint8_t data[8] = {0};
    ErrStatus ret;

    /* 帧1：ch0 + ch1 */
    data[0] = CAN_NODE_MCU;
    data[1] = CAN_QRY_TEMP;
    data[2] = (uint8_t)((uint16_t)temp_ch0 >> 8);
    data[3] = (uint8_t)((uint16_t)temp_ch0 & 0xFFU);
    data[4] = (uint8_t)((uint16_t)temp_ch1 >> 8);
    data[5] = (uint8_t)((uint16_t)temp_ch1 & 0xFFU);
    data[6] = CAN_RSVD_FILL;
    data[7] = CAN_RSVD_FILL;
    ret = can_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U);

    /* 帧2：ch2 + ch3 */
    data[1] = CAN_QRY_TEMP_HI;
    data[2] = (uint8_t)((uint16_t)temp_ch2 >> 8);
    data[3] = (uint8_t)((uint16_t)temp_ch2 & 0xFFU);
    data[4] = (uint8_t)((uint16_t)temp_ch3 >> 8);
    data[5] = (uint8_t)((uint16_t)temp_ch3 & 0xFFU);
    if(can_send_std_frame(DTM_CAN4, CAN_ID_QUERY, data, 8U) != SUCCESS) {
        ret = ERROR;
    }

    return ret;
}

ErrStatus can_upload_temp(void)
{
    system_state_input_t input;
    system_state_get_input(&input);

    int16_t temp_ch0 = input.zone_temp_valid[0] ? input.zone_temperature_tenths[0] : 0;
    int16_t temp_ch1 = input.zone_temp_valid[1] ? input.zone_temperature_tenths[1] : 0;
    int16_t temp_ch2 = input.zone_temp_valid[2] ? input.zone_temperature_tenths[2] : 0;
    int16_t temp_ch3 = input.zone_temp_valid[3] ? input.zone_temperature_tenths[3] : 0;

    return can_send_temp_response(temp_ch0, temp_ch1, temp_ch2, temp_ch3);
}

/*
 * can_send_control_ack - 控制类 ACK 响应 (ID: 0x189, Byte0=CAN_NODE_MCU)
 *   Byte0  源节点（0x20=MCU）
 *   Byte1  回显消息号
 *   Byte2  结果码（CAN_ACK_*）
 *   Byte3  当前点火状态
 *   Byte4  当前系统状态等级
 *   Byte5~7 保留
 */
ErrStatus can_send_control_ack(uint8_t msg_id, uint8_t result)
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
    return can_send_std_frame(DTM_CAN4, CAN_ID_CONTROL, data, 8U);
}

/*
 * can_send_config_ack - 配置类 ACK 响应 (ID: 0x18A, Byte0=CAN_NODE_MCU)
 *   格式同控制类 ACK
 */
ErrStatus can_send_config_ack(uint8_t msg_id, uint8_t result)
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
    return can_send_std_frame(DTM_CAN4, CAN_ID_CONFIG, data, 8U);
}

/*
 * can_handle_query - 处理查询类请求（ID=0x188, Byte0=CAN_NODE_HOST）
 *   仅置位对应上报标志，实际组帧在主循环 can_process_pending_uploads() 完成。
 *   查询响应走相同 ID (0x188)，通过 Byte0=CAN_NODE_MCU 区分方向。
 */
ErrStatus can_handle_query(uint8_t msg_id)
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

void can_process_pending_uploads(void)
{
    if(s_upload_env_flag != 0U) {
        s_upload_env_flag = 0U;
        (void)can_upload_env();
    }

    if(s_upload_state_flag != 0U) {
        s_upload_state_flag = 0U;
        (void)can_upload_state();
    }

    if(s_upload_system_state_flag != 0U) {
        s_upload_system_state_flag = 0U;
        (void)can_upload_system_state();
    }

    if(s_upload_fault_flag != 0U) {
        s_upload_fault_flag = 0U;
        (void)can_upload_fault();
    }

    if(s_upload_temp_flag != 0U) {
        s_upload_temp_flag = 0U;
        (void)can_upload_temp();
    }
}


void can_enable_rx_interrupt(can_dtm_canx_enum dtm_canx, uint8_t irqn_priority)
{
    can_interrupt_enable(dtm_canx, CAN_INT_RFIFO0_NEW);
    can_mcan_interrupt_line_config(dtm_canx, CAN_INTR_LINE0, CAN_INT_RFIFO0_NEW);
    can_mcan_interrupt_line_enable(dtm_canx, CAN_INTR_LINE0);
    if(dtm_canx == DTM_CAN0) {
        nvic_irq_enable(DTM_CAN0_INT0_IRQn, irqn_priority, 0);
    }
    if(dtm_canx == DTM_CAN2) {
        nvic_irq_enable(DTM_CAN2_INT0_IRQn, irqn_priority, 0);
    }
    if(dtm_canx == DTM_CAN4) {
        nvic_irq_enable(DTM_CAN4_INT0_IRQn, irqn_priority, 0);
    }
    if(dtm_canx == DTM_CAN5) {
        nvic_irq_enable(DTM_CAN5_INT0_IRQn, irqn_priority, 0);
    }
}
