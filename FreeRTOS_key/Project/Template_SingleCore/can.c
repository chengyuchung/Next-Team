#include "can.h"
#include "main.h"
#include "fault_manager.h"
#include "system_state.h"
#include "temp_sensor.h"
#include <string.h>

/*
 * CAN 应用层实现
 * 初始化 CAN 时钟与 CAN0/CAN2/CAN4/CAN5 的引脚及参数
 * 数据帧走独立 ID：0x180~0x184 上报，0x188 接收请求，0x186 回 ACK
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

    filter_element.filter_type = CAN_FILTER_DUAL;
    filter_element.config = CAN_FILTER_TO_RXFIFO0;
    filter_element.id1 = CAN_ID_CMD;
    filter_element.id2_or_mask_or_rxbuffercfg = CAN_ID_CMD;

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
    tx_message.id = CAN_ID_CMD;
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
    fdtx_message.id = CAN_ID_CMD;
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


ErrStatus can_send_env(int16_t max_temp_tenths, int16_t pressure_kpa, uint8_t press_alarm, uint8_t gas_leak)
{
    uint8_t data[8] = {0};

    /* Byte[0,1]: 最高温度 int16_t，高字节在前（0.1C 单位） */
    data[0] = (uint8_t)((uint16_t)max_temp_tenths >> 8);
    data[1] = (uint8_t)((uint16_t)max_temp_tenths & 0xFFU);

    /* Byte[2,3]: 压力 int16_t，单位 kPa */
    data[2] = (uint8_t)((uint16_t)pressure_kpa >> 8);
    data[3] = (uint8_t)((uint16_t)pressure_kpa & 0xFFU);

    /* Byte[4]: 压力报警标志 */
    data[4] = press_alarm;

    /* Byte[5]: 气体泄漏标志 */
    data[5] = gas_leak;

    /* Byte[6,7]: 预留（未使用 CRC 校验） */
    return can_send_std_frame(DTM_CAN4, CAN_ID_ENV, data, 8U);
}

ErrStatus can_upload_env(void)
{
    system_state_input_t input;
    temp_result_t temp_result;

    system_state_get_input(&input);
    temp_get_last(&temp_result);

    /* 压力单位换算为 kPa（除以 1000） */
    int16_t pressure_kpa = (int16_t)((input.pressure_pa < 0) ? 0 : ((uint32_t)input.pressure_pa / 1000U));

    /* 温度取自 temp_sensor 的最高温度；压力报警 = pressure_alarm，气体报警 = gas_alarm */
    return can_send_env(temp_result.maximum_temperature, pressure_kpa,
                       input.pressure_alarm, input.gas_alarm);
}

ErrStatus can_upload_state(void)
{
    system_state_status_t status;
    system_state_get_status(&status);
    uint8_t fan_duty = status.fan_duty_percent;
    uint8_t pump_duty = status.pump_duty_percent;
    /* 4 路制冷中任一路开启，则 cooler_on=1 */
    uint8_t cooler_on = (uint8_t)(status.cooler_enable[0] | status.cooler_enable[1] |
                                   status.cooler_enable[2] | status.cooler_enable[3]);
    uint8_t gate_on = status.gate_enable;
    return can_send_state(fan_duty, pump_duty, cooler_on, gate_on);
}

ErrStatus can_upload_system_state(void)
{
    system_state_status_t status;
    system_state_get_status(&status);
    uint8_t level = (status.state == SYSTEM_STATE_NORMAL)   ? 1U :
                    (status.state == SYSTEM_STATE_LOW_TEMP)  ? 2U :
                    (status.state == SYSTEM_STATE_HIGH_TEMP) ? 3U : 4U;
    return can_send_system_state(level);
}

ErrStatus can_upload_fault(void)
{
    system_state_input_t input;
    fault_manager_status_t fault_status;
    uint8_t fault_heater = 0U;
    uint8_t fault_cooler = 0U;
    uint8_t fault_temp_sensor = 0U;
    uint8_t fault_press_sensor = 0U;
    uint8_t fault_gas_sensor = 0U;

    system_state_get_input(&input);
    fault_manager_get_act_fault(&fault_heater, &fault_cooler);
    fault_temp_sensor = (input.temperature_valid != 0U) ? 0U : 1U;
    fault_press_sensor = (input.pressure_valid != 0U) ? 0U : 1U;
    fault_gas_sensor = (input.gas_valid != 0U) ? 0U : 1U;
    return can_send_fault(fault_heater, fault_cooler, 0U, 0U,
                          fault_temp_sensor, fault_press_sensor, fault_gas_sensor);
}

ErrStatus can_upload_temp(void)
{
    system_state_input_t input;
    system_state_get_input(&input);

    int16_t temp_ch0 = input.zone_temp_valid[0] ? input.zone_temperature_tenths[0] : 0;
    int16_t temp_ch1 = input.zone_temp_valid[1] ? input.zone_temperature_tenths[1] : 0;
    int16_t temp_ch2 = input.zone_temp_valid[2] ? input.zone_temperature_tenths[2] : 0;
    int16_t temp_ch3 = input.zone_temp_valid[3] ? input.zone_temperature_tenths[3] : 0;

    return can_send_temp(temp_ch0, temp_ch1, temp_ch2, temp_ch3);
}

ErrStatus can_send_state(uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on)
{
    uint8_t data[8] = {0};

    data[0] = fan_duty;
    data[1] = pump_duty;
    data[2] = cooler_on;
    data[3] = gate_on;
    return can_send_std_frame(DTM_CAN4, CAN_ID_STA, data, 8U);
}

ErrStatus can_send_system_state(uint8_t level)
{
    uint8_t data[8] = {0};
    data[0] = level;
    return can_send_std_frame(DTM_CAN4, CAN_ID_SYS_STATE, data, 8U);
}

ErrStatus can_send_fault(uint8_t fault_fan, uint8_t fault_pump, uint8_t fault_cool, uint8_t fault_gate, uint8_t fault_temp_sensor, uint8_t fault_press_sensor, uint8_t fault_gas_sensor)
{
    uint8_t data[8] = {0};
    data[0] = fault_fan;
    data[1] = fault_pump;
    data[2] = fault_cool;
    data[3] = fault_gate;
    data[4] = fault_temp_sensor;
    data[5] = fault_press_sensor;
    data[6] = fault_gas_sensor;
    return can_send_std_frame(DTM_CAN4, CAN_ID_FLT, data, 8U);
}

/*
 * can_send_temp - 上报 4 路温度数据 (ID: 0x184)
 *   每路 int16_t，高字节在前，单位 0.1C
 *   不含 CRC 校验
 */
ErrStatus can_send_temp(int16_t temp_ch0, int16_t temp_ch1, int16_t temp_ch2, int16_t temp_ch3)
{
    uint8_t data[8] = {0};

    data[0] = (uint8_t)((uint16_t)temp_ch0 >> 8);
    data[1] = (uint8_t)((uint16_t)temp_ch0 & 0xFFU);
    data[2] = (uint8_t)((uint16_t)temp_ch1 >> 8);
    data[3] = (uint8_t)((uint16_t)temp_ch1 & 0xFFU);
    data[4] = (uint8_t)((uint16_t)temp_ch2 >> 8);
    data[5] = (uint8_t)((uint16_t)temp_ch2 & 0xFFU);
    data[6] = (uint8_t)((uint16_t)temp_ch3 >> 8);
    data[7] = (uint8_t)((uint16_t)temp_ch3 & 0xFFU);

    return can_send_std_frame(DTM_CAN4, CAN_ID_TEMP, data, 8U);
}

/*
 * can_handle_query - 处理查询类请求（Byte0=0x00）
 *   仅置位对应上报标志，实际组帧在主循环 can_process_pending_uploads() 完成。
 *   查询响应走各自数据帧 ID（0x180~0x184），不占用 0x186。
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

/*
 * can_send_ack - 发送控制/配置类执行结果回执 (ID: 0x186)
 *   Byte0 回显类别，Byte1 回显消息号，Byte2 结果码 (CAN_ACK_*)，
 *   Byte3 当前点火状态，Byte4 当前系统状态等级，其余预留。
 */
ErrStatus can_send_ack(uint8_t category, uint8_t msg_id, uint8_t result)
{
    uint8_t data[8] = {0};
    data[0] = category;
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
    return can_send_std_frame(DTM_CAN4, CAN_ID_ACK, data, 8U);
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
