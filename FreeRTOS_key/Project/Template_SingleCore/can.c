#include "can.h"
#include "main.h"
#include "fault_manager.h"
#include "system_state.h"
#include <string.h>

/*
 * CAN 协议与底层说明
 * 1) 这里保留了项目原有的 CAN0/CAN2/CAN4/CAN5 底层初始化，避免删减后引发总线卡死。
 * 2) 当前上层协议主要围绕 CAN4 展开，使用 0x184 命令帧请求 0x180~0x183 的业务帧。
 * 3) 虚拟数据模式由 CAN_APP_USE_REAL_DATA 控制，0=虚拟数据，1=真实业务数据。
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

/*
 * 状态变化通知标志：
 *   由 system_state 模块置位；
 *   主循环主动消费，而不是依赖 CAN 接收中断。
 */
volatile uint8_t g_system_state_changed_flag = 0U;

/*
 * 真实运行缓存：按帧拆分，分别保存环境/状态/警报/故障数据。
 * 上层模块可以只更新自己关心的那一帧数据，互不影响。
 */
static can_env_data_t s_env = {0};
static can_state_data_t s_state = {0};
static can_system_state_data_t s_system_state_frame = {0};
static can_fault_data_t s_fault = {0};

/*
 * 虚拟数据集：同样按帧拆分，方便调试时单独修改某一帧的测试值。
 * 下面这 4 组数据就是 CAN4 联调时的默认测试源。
 */
static const can_env_data_t s_demo_env = {
    25U,
    60U,
    1013U,
    0U
};

static const can_state_data_t s_demo_state = {
    1U,
    1U,
    1U,
    1U
};

static const can_system_state_data_t s_demo_system_state = {
    1U,
    {0U, 0U, 0U, 0U, 0U, 0U, 0U}
};

static const can_fault_data_t s_demo_fault = {
    1U,
    1U,
    1U,
    1U,
    1U,
    1U,
    1U
};

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
 * @brief  DTM CAN4 消息发送测试函数
 *
 * @note   该函数用于初始化并发送一个标准的CAN数据帧，以验证DTM CAN4模块的发送功能。
 *
 * @param  None
 *
 * @retval ErrStatus
 *         - SUCCESS: 消息成功准备并加入发送队列
 *         - ERROR:   获取发送邮箱失败，消息未发送
 */
ErrStatus dtm_can4_message_transmit_test(void)
{
    uint8_t transmit_mailbox = 0;
    ErrStatus ret = SUCCESS;
    uint16_t i;

    /* 初始化CAN发送消息结构体参数 */
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

    /* 填充8字节的数据载荷，数据内容为1到8 */
    for(i = 0; i < 8; i++) {
        tx_message.data[i] = i + 1;
    }

    /* 准备CAN消息传输，获取可用的发送邮箱 */
    transmit_mailbox = can_message_transmit_prepare(DTM_CAN4, &tx_message);
    if(transmit_mailbox == 0xFF) {
        ret = ERROR;
    } else {
        /* 将消息添加到指定的发送邮箱以启动传输 */
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


uint8_t can_crc8(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0x00U;
    uint8_t i;
    uint8_t j;

    if(data == NULL) {
        return 0U;
    }

    for(i = 0U; i < len; i++) {
        crc ^= data[i];
        for(j = 0U; j < 8U; j++) {
            if((crc & 0x80U) != 0U) {
                crc = (uint8_t)((crc << 1U) ^ 0x07U);
            } else {
                crc <<= 1U;
            }
        }
    }

    return crc;
}

ErrStatus can_send_env(uint16_t temp_int, uint16_t temp_frac, uint16_t press_int, uint16_t press_frac, uint8_t gas_leak)
{
    uint8_t data[8] = {0};
    data[0] = (uint8_t)(temp_int >> 8);
    data[1] = (uint8_t)(temp_int & 0xFFU);
    data[2] = (uint8_t)(temp_frac & 0xFFU);
    data[3] = (uint8_t)(press_int >> 8);
    data[4] = (uint8_t)(press_int & 0xFFU);
    data[5] = (uint8_t)(press_frac & 0xFFU);
    data[6] = gas_leak;
    data[7] = can_crc8(data, 7U);
    return can_send_std_frame(DTM_CAN4, CAN_ID_ENV, data, 8U);
}

ErrStatus can_upload_env(void)
{
#if (CAN_APP_USE_REAL_DATA == 0U)
    return can_send_env(s_demo_env.temp_int, s_demo_env.temp_frac, s_demo_env.press_int, s_demo_env.press_frac, s_demo_env.gas_leak);
#else
    system_state_input_t input;
    int32_t temp_c;
    uint32_t pressure_pa;

    system_state_get_input(&input);

    temp_c = input.max_temperature_tenths;
    if(temp_c < 0) {
        temp_c = -temp_c;
    }
    s_env.temp_int = (uint16_t)(temp_c / 10);
    s_env.temp_frac = (uint16_t)(temp_c % 10);

    pressure_pa = (input.pressure_pa < 0) ? 0U : (uint32_t)input.pressure_pa;
    s_env.press_int = (uint16_t)(pressure_pa / 1000U);
    s_env.press_frac = (uint16_t)((pressure_pa % 1000U) / 10U);
    s_env.gas_leak = input.gas_alarm;

    return can_send_env(s_env.temp_int, s_env.temp_frac, s_env.press_int, s_env.press_frac, s_env.gas_leak);
#endif
}

ErrStatus can_upload_state(void)
{
#if (CAN_APP_USE_REAL_DATA == 0U)
    uint8_t fan_duty = s_demo_state.fan_duty;
    uint8_t pump_duty = s_demo_state.pump_duty;
    uint8_t cooler_on = s_demo_state.cooler_on;
    uint8_t gate_on = s_demo_state.gate_on;
#else
    system_state_status_t status;
    system_state_get_status(&status);
    uint8_t fan_duty = status.fan_duty_percent;
    uint8_t pump_duty = status.pump_duty_percent;
    /* 制冷片状态：4路中任意一路开启则cooler_on=1 */
    uint8_t cooler_on = (uint8_t)(status.cooler_enable[0] | status.cooler_enable[1] |
                                   status.cooler_enable[2] | status.cooler_enable[3]);
    uint8_t gate_on = status.gate_enable;
#endif
    return can_send_state(fan_duty, pump_duty, cooler_on, gate_on);
}

ErrStatus can_upload_system_state(void)
{
#if (CAN_APP_USE_REAL_DATA == 0U)
    uint8_t level = s_demo_system_state.level;
#else
    system_state_status_t status;
    system_state_get_status(&status);
    uint8_t level = (status.state == SYSTEM_STATE_NORMAL) ? 1U :
                    (status.state == SYSTEM_STATE_PRE_WARNING) ? 2U :
                    (status.state == SYSTEM_STATE_WARNING) ? 3U : 4U;
#endif
    return can_send_system_state(level);
}

ErrStatus can_upload_fault(void)
{
#if (CAN_APP_USE_REAL_DATA == 0U)
    uint8_t fault_fan = s_demo_fault.fan;
    uint8_t fault_pump = s_demo_fault.pump;
    uint8_t fault_cool = s_demo_fault.cool;
    uint8_t fault_gate = s_demo_fault.gate;
    uint8_t fault_temp_sensor = s_demo_fault.temp_sensor;
    uint8_t fault_press_sensor = s_demo_fault.press_sensor;
    uint8_t fault_gas_sensor = s_demo_fault.gas_sensor;
#else
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
#endif
    return can_send_fault(fault_heater, fault_cooler, 0U, 0U, fault_temp_sensor, fault_press_sensor, fault_gas_sensor);
}

ErrStatus can_send_state(uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on)
{
    uint8_t data[8] = {0};

    data[0] = fan_duty;
    data[1] = pump_duty;
    data[2] = cooler_on;
    data[3] = gate_on;
    data[7] = can_crc8(data, 7U);
    return can_send_std_frame(DTM_CAN4, CAN_ID_STA, data, 8U);
}

ErrStatus can_send_system_state(uint8_t level)
{
    uint8_t data[8] = {0};
    data[0] = level;
    data[7] = can_crc8(data, 7U);
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
    data[7] = can_crc8(data, 7U);
    return can_send_std_frame(DTM_CAN4, CAN_ID_FLT, data, 8U);
}

ErrStatus can_handle_cmd(uint8_t cmd, uint8_t arg1, uint8_t arg2, uint8_t arg3)
{
    switch(cmd) {
    case CAN_CMD_ENV:
        s_upload_env_flag = 1U;
        break;
    case CAN_CMD_STA:
        s_upload_state_flag = 1U;
        break;
    case CAN_CMD_ALM:
        s_upload_system_state_flag = 1U;
        break;
    case CAN_CMD_FLT:
        s_upload_fault_flag = 1U;
        break;
    default:
        break;
    }

    (void)arg1;
    (void)arg2;
    (void)arg3;
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
}

ErrStatus can_upload_all(void)
{
    ErrStatus ret = SUCCESS;
    ret |= can_upload_env();
    ret |= can_upload_state();
    ret |= can_upload_system_state();
    ret |= can_upload_fault();
    return ret;
}

ErrStatus can_upload_demo(void)
{
#if (CAN_APP_USE_REAL_DATA == 0U)
    can_set_env_data(&s_demo_env);
    can_set_state_data(&s_demo_state);
    can_set_state_frame_data(&s_demo_system_state);
    can_set_fault_data(&s_demo_fault);
#endif
    return can_upload_all();
}

static uint8_t can_cmd_to_id(uint8_t cmd)
{
    switch(cmd) {
    case CAN_CMD_ENV:
        return (uint8_t)CAN_ID_ENV;
    case CAN_CMD_STA:
        return (uint8_t)CAN_ID_STA;
    case CAN_CMD_ALM:
        return (uint8_t)CAN_ID_SYS_STATE;
    case CAN_CMD_FLT:
        return (uint8_t)CAN_ID_FLT;
    default:
        return 0U;
    }
}

ErrStatus can_send_cmd_reply(uint8_t cmd, uint8_t a1, uint8_t a2, uint8_t a3)
{
    uint8_t data[8] = {0};
    uint8_t id = can_cmd_to_id(cmd);
    if(id == 0U) {
        return ERROR;
    }
    data[0] = cmd;
    data[1] = a1;
    data[2] = a2;
    data[3] = a3;
    data[7] = can_crc8(data, 7U);
    return can_send_std_frame(DTM_CAN4, id, data, 8U);
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
