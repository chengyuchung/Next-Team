#include "can_driver.h"

/*
 * ============================================================================
 * 模块名称 : can_driver
 * 文件功能 : CAN 硬件驱动层实现（MCAL 层）
 * ============================================================================
 */

void can_driver_gpio_config(void)
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

void can_driver_config(can_dtm_canx_enum dtm_canx, uint32_t baudrate_khz)
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

ErrStatus can_driver_send_std_frame(can_dtm_canx_enum dtm_canx, uint32_t std_id, uint8_t *data, uint8_t len)
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

void can_driver_enable_rx_interrupt(can_dtm_canx_enum dtm_canx, uint8_t irqn_priority)
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
