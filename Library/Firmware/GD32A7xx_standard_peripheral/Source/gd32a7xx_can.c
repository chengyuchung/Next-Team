/*!
    \file    gd32a7xx_can.c
    \brief   CAN driver

    \version 2025-08-06, V0.1.0, firmware for GD32A7xx
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include "gd32a7xx_can.h"

/* DLC to data size in bytes definitions */
static const uint8_t dlc_to_databytes[16] = {0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 12U, 16U, 20U, 24U, 32U, 48U, 64U};
static const uint8_t fifo_element_sz[8] = {16U, 20U, 24U, 28U, 32U, 40U, 56U, 72U};

/* write data to destination array */
static void can_data_write(uint32_t dest[], uint8_t src[], uint32_t len);
/* computes the dlc field value, given a payload size (in bytes) */
static uint32_t can_dlc_value_compute(uint32_t payload_size);
/* receive CAN message from a specific memory address */
static can_receive_message_struct can_receive_by_addr(uint32_t addr);
/* convert DTM_CANx to CAN */
static uint32_t can_dtm_to_can(can_dtm_canx_enum dtm_canx);

/* private constants */
#define CAN_TIMEOUT_COUNT              ((uint32_t)0x0000FFFFU)   /*!< CAN timeout count value */
#define CAN_MERRSTAT_NCE_MASK          ((uint32_t)0x07000000U)   /*!< noncorrectable error mask */
#define CAN_TDCV_MASK                  ((uint16_t)0x007FU)       /*!< transmitter delay compensation value mask */

#define CAN_FLITER_ES_STD              ((uint32_t)0x00000004U)   /*!< standard filter element size */
#define CAN_FLITER_ES_EXT              ((uint32_t)0x00000008U)   /*!< extended filter element size */

#define CAN_ID_EXT_MASK                ((uint32_t)0x1FFFFFFFU)   /*!< extended identifier */
#define CAN_ID_STD_MASK                ((uint32_t)0x000007FFU)   /*!< standard identifier */
#define CAN_ID_STD_OFFSET              (18U)                     /*!< standard identifier offset */

#define TX_MM_HIGH_OFFSET              (8U)                      /*!< message marker high byte offset */
#define TX_MM_LOW_OFFSET               (24U)                     /*!< message marker low byte offset */

#define CAN_M_CAN_TEST_TXBNP_OFFSET    (8U)                      /*!< bit offset of TXBNP in CAN_M_CAN_TEST */
#define CAN_M_CAN_TEST_TXBNS_OFFSET    (16U)                     /*!< bit offset of TXBNS in CAN_M_CAN_TEST */

#define CAN_M_CAN_RWD_WDV_OFFSET       (8U)                      /*!< bit offset of WDV in CAN_M_CAN_RWD */

#define CAN_M_CAN_PSR_DLEC_OFFSET      ((uint32_t)0x00000008U)   /*!< bit offset of DLEC in CAN_M_CAN_PSR */
#define CAN_M_CAN_PSR_ACT_OFFSET       ((uint32_t)0x00000003U)   /*!< bit offset of ACT in CAN_M_CAN_PSR */

#define CAN_M_CAN_CCCR_WMM_OFFSET      (11U)                     /*!< bit offset of WMM in CAN_M_CAN_CCCR */
#define CAN_E0_RTR_OFFSET              (29U)                     /*!< bit offset of RTR in CAN_E0 */
#define CAN_E0_XTD_OFFSET              (30U)                     /*!< bit offset of XTD in CAN_E0 */
#define CAN_E0_ESI_OFFSET              (31U)                     /*!< bit offset of ESI in CAN_E0 */
#define CAN_E1_DLC_OFFSET              (16U)                     /*!< bit offset of DLC in CAN_E1 */
#define CAN_E1_BRS_OFFSET              (20U)                     /*!< bit offset of BRS in CAN_E1 */
#define CAN_E1_FDF_OFFSET              (21U)                     /*!< bit offset of FDF in CAN_E1 */
#define CAN_E1_ET_OFFSET               (22U)                     /*!< bit offset of ET in CAN_E1 */
#define CAN_E1_MM_LOW_OFFSET           (24U)                     /*!< bit offset of MM_LOW in CAN_E1 */

#define CAN_DMUI_RX0R_OFFSET           (1U)                      /*!< bit offset of RX0R in CAN_DMU_DMUI */
#define CAN_DMUI_RX1R_OFFSET           (2U)                      /*!< bit offset of RX1R in CAN_DMU_DMUI */
#define CAN_DMUI_TXER_OFFSET           (3U)                      /*!< bit offset of TXER in CAN_DMU_DMUI */
#define CAN_DMUI_TFQPIP_OFFSET         (8U)                      /*!< bit offset of TFQPIP in CAN_DMU_DMUI */
#define CAN_DMUI_ENA_OFFSET            (15U)                     /*!< bit offset of ENA in CAN_DMU_DMUI */
#define CAN_DMUI_EHS_OFFSET            (24U)                     /*!< bit offset of EHS in CAN_DMU_DMUI */
#define CAN_DMUI_TX_OFFSET             (28U)                     /*!< bit offset of TX in CAN_DMU_DMUI */
#define CAN_DMUI_RX0_OFFSET            (29U)                     /*!< bit offset of RX0 in CAN_DMU_DMUI */
#define CAN_DMUI_RX1_OFFSET            (30U)                     /*!< bit offset of RX1 in CAN_DMU_DMUI */
#define CAN_DMUI_TXE_OFFSET            (31U)                     /*!< bit offset of TXE in CAN_DMU_DMUI */

#define CAN_R0_RTR_OFFSET              (29U)                     /*!< bit offset of RTR in CAN_R0 */
#define CAN_R0_XTD_OFFSET              (30U)                     /*!< bit offset of XTD in CAN_R0 */
#define CAN_R0_ESI_OFFSET              (31U)                     /*!< bit offset of ESI in CAN_R0 */

#define CAN_R1A_DLC_OFFSET             (16U)                     /*!< bit offset of DLC in CAN_R1A */
#define CAN_R1A_BRS_OFFSET             (20U)                     /*!< bit offset of BRS in CAN_R1A */
#define CAN_R1A_FDF_OFFSET             (21U)                     /*!< bit offset of FDF in CAN_R1A */
#define CAN_R1A_FIDX_OFFSET            (24U)                     /*!< bit offset of FIDX in CAN_R1A */
#define CAN_R1A_ANMF_OFFSET            (31U)                     /*!< bit offset of ANMF in CAN_R1A */

/*!
    \brief      deinitialize CAN (API_ID(0x0001U))
                notice that only CAN cluster deinitialization is supported
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_deinit(can_dtm_canx_enum dtm_canx)
{
    /* determine which CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
    case DTM_CAN1:
        /* reset CAN0 */
        rcu_periph_reset_enable(RCU_CAN0RST);
        rcu_periph_reset_disable(RCU_CAN0RST);
        break;
    case DTM_CAN2:
    case DTM_CAN3:
    case DTM_CAN4:
        /* reset CAN1 */
        rcu_periph_reset_enable(RCU_CAN1RST);
        rcu_periph_reset_disable(RCU_CAN1RST);
        break;
    case DTM_CAN5:
    case DTM_CAN6:
    case DTM_CAN7:
        /* reset CAN2 */
        rcu_periph_reset_enable(RCU_CAN2RST);
        rcu_periph_reset_disable(RCU_CAN2RST);
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize CAN parameter structure with a default value (API_ID(0x0002U))
    \param[in]  type: the type of parameter struct
                only one parameter can be selected which is shown as below:
      \arg        CAN_INIT_STRUCT: CAN initialization parameter struct
      \arg        CAN_FD_INIT_STRUCT: CAN FD initialization parameter struct
      \arg        CAN_FILTER_STRUCT: CAN filter parameter struct
      \arg        CAN_FILTER_ELEMENT_STRUCT: ID filter element parameter struct
      \arg        CAN_RX_MESSAGE_STRUCT: received message parameter struct
      \arg        CAN_TX_MESSAGE_STRUCT: transmit message parameter struct
      \arg        CAN_TX_BUFFER_STRUCT: transmit buffer configuration parameter struct
      \arg        CAN_TXEV_FIFO_STRUCT: transmit event FIFO configuration parameter struct
      \arg        CAN_TXEV_ELEMENT_STRUCT: transmit event FIFO element parameter struct
      \arg        CAN_RX_FIFO_STRUCT: receive FIFO configuration parameter struct
      \arg        CAN_RX_BUFFER_STRUCT: receive buffer configuration parameter struct
      \arg        CAN_HIGHPRI_MESSAGE_STATE_STRUCT: high priority message state parameter struct
      \arg        CAN_ERR_COUNT_STRUCT: error counter parameter struct
      \arg        CAN_DMU_QUEUE_COUNT_STRUCT: DMU queue counter parameter struct
    \param[in]  p_struct: the pointer of the specific struct
    \param[out] none
    \retval     none
*/
void can_struct_para_init(can_struct_type_enum type, void *p_struct)
{
    uint8_t i;

    /* get type of the struct */
    switch(type) {
    /* CAN initialization parameter struct */
    case CAN_INIT_STRUCT:
        /* initialize CAN initialization parameter struct with default value */
        ((can_parameter_struct *)p_struct)->auto_retransmission_enable = ENABLE;
        ((can_parameter_struct *)p_struct)->transmit_pause_enable = DISABLE;
        ((can_parameter_struct *)p_struct)->edge_filter_enable = DISABLE;
        ((can_parameter_struct *)p_struct)->protocol_exception_enable = DISABLE;
        ((can_parameter_struct *)p_struct)->wide_message_enable = DISABLE;
        ((can_parameter_struct *)p_struct)->prescaler = 1U;
        ((can_parameter_struct *)p_struct)->resync_jump_width = 1U;
        ((can_parameter_struct *)p_struct)->time_segment_1 = 2U;
        ((can_parameter_struct *)p_struct)->time_segment_2 = 2U;
        ((can_parameter_struct *)p_struct)->filter_config = NULL;
        ((can_parameter_struct *)p_struct)->rx_fifo0_config = NULL;
        ((can_parameter_struct *)p_struct)->rx_fifo1_config = NULL;
        ((can_parameter_struct *)p_struct)->rx_buffer_config = NULL;
        ((can_parameter_struct *)p_struct)->tx_buffer_config = NULL;
        ((can_parameter_struct *)p_struct)->tx_event_fifo_config = NULL;
        break;
    /* CAN FD initialization parameter struct */
    case CAN_FD_INIT_STRUCT:
        /* initialize CAN FD initialization parameter struct with default value */
        ((can_fd_parameter_struct *)p_struct)->iso_can_fd_enable = DISABLE;
        ((can_fd_parameter_struct *)p_struct)->bitrate_switch_enable = DISABLE;
        ((can_fd_parameter_struct *)p_struct)->tdc_enable = DISABLE;
        ((can_fd_parameter_struct *)p_struct)->tdc_offset = 0U;
        ((can_fd_parameter_struct *)p_struct)->tdc_filter_window = 0U;
        ((can_fd_parameter_struct *)p_struct)->prescaler = 1U;
        ((can_fd_parameter_struct *)p_struct)->resync_jump_width = 1U;
        ((can_fd_parameter_struct *)p_struct)->time_segment_1 = 1U;
        ((can_fd_parameter_struct *)p_struct)->time_segment_2 = 2U;
        break;
    /* CAN filter parameter struct */
    case CAN_FILTER_STRUCT:
        /* initialize CAN filter parameter struct with default value */
        ((can_filter_struct *)p_struct)->and_mask_ext_frame = 0U;
        ((can_filter_struct *)p_struct)->non_match_std_frame_accept = CAN_ACCEPT_INTO_RXFIFO0;
        ((can_filter_struct *)p_struct)->non_match_ext_frame_accept = CAN_ACCEPT_INTO_RXFIFO0;
        ((can_filter_struct *)p_struct)->remote_std_frame_accept = CAN_REMOTE_FILTER;
        ((can_filter_struct *)p_struct)->remote_ext_frame_accept = CAN_REMOTE_FILTER;
        ((can_filter_struct *)p_struct)->filter_start_address_std_frame = 0U;
        ((can_filter_struct *)p_struct)->filter_start_address_ext_frame = 0U;
        ((can_filter_struct *)p_struct)->filter_number_std_frame = 0U;
        ((can_filter_struct *)p_struct)->filter_number_ext_frame = 0U;
        break;
    /* ID filter element parameter struct */
    case CAN_FILTER_ELEMENT_STRUCT:
        /* initialize standard ID filter element parameter struct with default value */
        ((can_filter_element_struct *)p_struct)->filter_type = CAN_FILTER_RANGE;
        ((can_filter_element_struct *)p_struct)->config = CAN_FILTER_DISABLE;
        ((can_filter_element_struct *)p_struct)->id1 = 0U;
        ((can_filter_element_struct *)p_struct)->id2_or_mask_or_rxbuffercfg = 0U;
        break;
    /* received message parameter struct */
    case CAN_RX_MESSAGE_STRUCT:
        /* initialize received message parameter struct with default value */
        ((can_receive_message_struct *)p_struct)->id = 0U;
        ((can_receive_message_struct *)p_struct)->rtr = (uint32_t)CAN_FT_DATA;
        ((can_receive_message_struct *)p_struct)->xtd = (uint32_t)CAN_FF_STANDARD;
        ((can_receive_message_struct *)p_struct)->esi = 0U;
        ((can_receive_message_struct *)p_struct)->timestamp = 0U;
        ((can_receive_message_struct *)p_struct)->dlc = 0U;
        ((can_receive_message_struct *)p_struct)->brs = CAN_BRS_DISABLE;
        ((can_receive_message_struct *)p_struct)->fdf = (uint32_t)CAN_CLASSIC_MODE;
        ((can_receive_message_struct *)p_struct)->filter_index = 0U;
        ((can_receive_message_struct *)p_struct)->non_match = CAN_MATCH_FILTER_FRAME;
        ((can_receive_message_struct *)p_struct)->data_bytes = 0U;

        for(i = 0U; i < 64U; i++) {
            ((can_receive_message_struct *)p_struct)->data[i] = 0U;
        }
        break;
    /* transmit message parameter struct */
    case CAN_TX_MESSAGE_STRUCT:
        /* initialize transmit message parameter struct with default value */
        ((can_transmit_message_struct *)p_struct)->id = 0U;
        ((can_transmit_message_struct *)p_struct)->rtr = CAN_FT_DATA;
        ((can_transmit_message_struct *)p_struct)->xtd = CAN_FF_STANDARD;
        ((can_transmit_message_struct *)p_struct)->esi = 0U;
        ((can_transmit_message_struct *)p_struct)->message_marker = 0U;
        ((can_transmit_message_struct *)p_struct)->brs = DISABLE;
        ((can_transmit_message_struct *)p_struct)->fdf = DISABLE;
        ((can_transmit_message_struct *)p_struct)->ev_fifo_control = CAN_TXEVENT_FIFO_DISABLE;
        ((can_transmit_message_struct *)p_struct)->data_bytes = 0U;

        for(i = 0U; i < 64U; i++) {
            ((can_transmit_message_struct *)p_struct)->data[i] = 0U;
        }
        break;
    /* transmit buffer configuration parameter struct */
    case CAN_TX_BUFFER_STRUCT:
        /* initialize transmit buffer configuration parameter struct with default value */
        ((can_tx_buffer_struct *)p_struct)->tx_buffer_start_address = 0U;
        ((can_tx_buffer_struct *)p_struct)->dedicate_buffer_size = 0U;
        ((can_tx_buffer_struct *)p_struct)->fifo_or_queue_mode = (uint16_t)CAN_TXFIFO_OPERATION;
        ((can_tx_buffer_struct *)p_struct)->fifo_or_queue_size = 0U;
        ((can_tx_buffer_struct *)p_struct)->tx_buffer_element_size = CAN_TXBS_8BYTES;
        break;
    /* transmit event FIFO configuration parameter struct */
    case CAN_TXEV_FIFO_STRUCT:
        /* initialize transmit event FIFO configuration parameter struct with default value */
        ((can_tx_event_fifo_struct *)p_struct)->fifo_watermark = 0U;
        ((can_tx_event_fifo_struct *)p_struct)->fifo_size = 0U;
        ((can_tx_event_fifo_struct *)p_struct)->fifo_start_address = 0U;
        break;
    /* transmit event FIFO element parameter struct */
    case CAN_TXEV_ELEMENT_STRUCT:
        /* initialize transmit event FIFO configuration parameter struct with default value */
        ((can_txev_fifo_element_struct *)p_struct)->id = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->rtr = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->xtd = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->esi = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->dlc = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->data_length = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->fdf = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->brs = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->event_type = CAN_NONE;
        ((can_txev_fifo_element_struct *)p_struct)->message_marker = 0U;
        ((can_txev_fifo_element_struct *)p_struct)->timestamp = 0U;
        break;
    /* receive FIFO configuration parameter struct */
    case CAN_RX_FIFO_STRUCT:
        /* initialize receive FIFO configuration parameter struct with default value */
        ((can_rx_fifo_struct *)p_struct)->fifo_operation_mode = (uint16_t)CAN_RXFIFO_BLOCKING;
        ((can_rx_fifo_struct *)p_struct)->fifo_watermark = 0U;
        ((can_rx_fifo_struct *)p_struct)->fifo_size = 0U;
        ((can_rx_fifo_struct *)p_struct)->fifo_start_address = 0U;
        ((can_rx_fifo_struct *)p_struct)->fifo_element_size = CAN_RXFS_8BYTES;
        break;
    /* receive buffer configuration parameter struct */
    case CAN_RX_BUFFER_STRUCT:
        /* initialize receive buffer configuration parameter struct with default value */
        ((can_rx_buffer_struct *)p_struct)->buffer_start_address = 0U;
        ((can_rx_buffer_struct *)p_struct)->buffer_element_size = CAN_RXBS_8BYTES;
        break;
    /* high priority message state parameter struct */
    case CAN_HIGHPRI_MESSAGE_STATE_STRUCT:
        /* initialize high priority message state parameter struct with default value */
        ((can_high_prio_message_state_struct *)p_struct)->storage_addr = 0U;
        ((can_high_prio_message_state_struct *)p_struct)->match_filter_addr = 0U;
        ((can_high_prio_message_state_struct *)p_struct)->storage_indicator = 0;
        break;
    /* error counter parameter struct */
    case CAN_ERR_COUNT_STRUCT:
        /* initialize error counter parameter struct with default value */
        ((can_error_cnt_struct *)p_struct)->rx_err_cnt = 0U;
        ((can_error_cnt_struct *)p_struct)->tx_err_cnt = 0U;
        ((can_error_cnt_struct *)p_struct)->err_logging = 0U;
        ((can_error_cnt_struct *)p_struct)->rx_err_passive = RESET;
        break;
    /* DMU queue counter parameter struct */
    case CAN_DMU_QUEUE_COUNT_STRUCT:
        /* initialize DMU queue counter parameter struct with default value */
        ((can_dmu_queue_cnt_struct *)p_struct)->tx_enqueue_cnt = 0U;
        ((can_dmu_queue_cnt_struct *)p_struct)->rx0_dequeue_cnt = 0U;
        ((can_dmu_queue_cnt_struct *)p_struct)->rx1_dequeue_cnt = 0U;
        ((can_dmu_queue_cnt_struct *)p_struct)->tx_event_dequeue_cnt = 0U;
        break;
    default:
        break;
    }
}

/*!
    \brief      initialize CAN (API_ID(0x0003U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  can_parameter: CAN initialization parameter struct
                  auto_retransmission_enable: ENABLE, DISABLE
                  transmit_pause_enable: ENABLE, DISABLE
                  edge_filter_enable: ENABLE, DISABLE
                  protocol_exception_enable: ENABLE, DISABLE
                  wide_message_enable: ENABLE, DISABLE
                  prescaler: 1~512
                  resync_jump_width: 1~128
                  time_segment_1: 2~256
                  time_segment_2: 2~128
                  filter_config: filter configuration
                    and_mask_ext_frame: 0~0x1FFFFFFF
                    non_match_std_frame_accept: CAN_ACCEPT_INTO_RXFIFO0, CAN_ACCEPT_INTO_RXFIFO1, CAN_REJECT_NON_MATCHING
                    non_match_ext_frame_accept: CAN_ACCEPT_INTO_RXFIFO0, CAN_ACCEPT_INTO_RXFIFO1, CAN_REJECT_NON_MATCHING
                    remote_std_frame_accept: CAN_REMOTE_FILTER, CAN_REMOTE_REJECT
                    remote_ext_frame_accept: CAN_REMOTE_FILTER, CAN_REMOTE_REJECT
                    filter_start_address_std_frame: 0~0xFFFF
                    filter_start_address_ext_frame: 0~0xFFFF
                    filter_number_std_frame: 0~128
                    filter_number_ext_frame: 0~64
                  rx_fifo_config: Rx FIFO configuration
                    fifo_operation_mode: CAN_RXFIFO_BLOCKING, CAN_RXFIFO_OVERWRITE
                    fifo_watermark: 0~0x40
                    fifo_size: 0~0x40
                    fifo_start_address: 0~0xFFFF
                    fifo_element_size: CAN_RXFS_8BYTES, CAN_RXFS_12BYTES, CAN_RXFS_16BYTES, CAN_RXFS_20BYTES, CAN_RXFS_24BYTES,
                                       CAN_RXFS_32BYTES, CAN_RXFS_48BYTES, CAN_RXFS_64BYTES
                  rx_buffer_config: Rx buffer configuration
                    buffer_start_address: 0~0xFFFF
                    buffer_element_size: CAN_RXBS_8BYTES, CAN_RXBS_12BYTES, CAN_RXBS_16BYTES, CAN_RXBS_20BYTES, CAN_RXBS_24BYTES,
                                         CAN_RXBS_32BYTES, CAN_RXBS_48BYTES, CAN_RXBS_64BYTES
                  tx_buffer_config: Tx buffer configuration
                    tx_buffer_start_address: 0~0xFFFF
                    dedicate_buffer_size: 0~32
                    fifo_or_queue_mode: CAN_TXFIFO_OPERATION, CAN_TXQUEUE_OPERATION
                    fifo_or_queue_size: 0~32
                    tx_buffer_element_size: CAN_TXBS_8BYTES, CAN_TXBS_12BYTES, CAN_TXBS_16BYTES, CAN_TXBS_20BYTES, CAN_TXBS_24BYTES,
                                            CAN_TXBS_32BYTES, CAN_TXBS_48BYTES, CAN_TXBS_64BYTES
                  tx_event_fifo_config: Tx event FIFO configuration
                    fifo_watermark: 0~32
                    fifo_size: 0~32
                    fifo_start_address: 0~0xFFFF
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_init(can_dtm_canx_enum dtm_canx, can_parameter_struct *can_parameter)
{
    uint32_t timeout = CAN_TIMEOUT_COUNT;
    uint32_t reg_val;
    ErrStatus reval = SUCCESS;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* check can_parameter pointer is NULL */
    if(NULL == can_parameter) {
        reval = ERROR;
    } else {
        /* enable initialization mode */
        CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_INIT;

        /* wait until initialization mode is entered */
        while((0U == (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_INIT)) && (0U != timeout)) {
            timeout--;
        }

        /* check the entering of initialization mode */
        if(0U == (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_INIT)) {
            reval =  ERROR;
        } else {
            /* enable configuration change */
            CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_CCE;

            /* set the automatic retransmission */
            if(DISABLE != can_parameter->auto_retransmission_enable) {
                CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_DAR;
            } else {
                CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_DAR;
            }

            /* set the transmit pause */
            if(DISABLE != can_parameter->transmit_pause_enable) {
                CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_TXP;
            } else {
                CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_TXP;
            }

            /* set the edge filtering during bus integration */
            if(DISABLE != can_parameter->edge_filter_enable) {
                CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_EFBI;
            } else {
                CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_EFBI;
            }

            /* set the protocol exception handling */
            if(DISABLE != can_parameter->protocol_exception_enable) {
                CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_PXHD;
            } else {
                CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_PXHD;
            }

            /* set the wide message mark handling */
            if(DISABLE != can_parameter->wide_message_enable) {
                CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_WMM;
            } else {
                CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_WMM;
            }

            /* configure bit timing parameters */
            reg_val = CAN_M_CAN_NBTP(can_periph);
            reg_val &= ~(CAN_M_CAN_NBTP_NSJW | CAN_M_CAN_NBTP_NBRP | CAN_M_CAN_NBTP_NTSEG1 | CAN_M_CAN_NBTP_NTSEG2);
            reg_val |= (((uint32_t)NBTP_NSJW(can_parameter->resync_jump_width - 1U)) | \
                        ((uint32_t)NBTP_NBRP(can_parameter->prescaler - 1U)) | \
                        ((uint32_t)NBTP_NTSEG1(can_parameter->time_segment_1 - 1U)) | \
                        ((uint32_t)NBTP_NTSEG2(can_parameter->time_segment_2 - 1U)));
            CAN_M_CAN_NBTP(can_periph) = reg_val;

            /* configure filter parameters if provided */
            if(NULL != can_parameter->filter_config) {
                /* configure standard ID filter settings */
                can_parameter->filter_config->filter_start_address_std_frame = can_parameter->filter_config->filter_start_address_std_frame >> 2U;
                CAN_M_CAN_SIDFC(can_periph) = (((uint32_t)SIDFC_FLSSA(can_parameter->filter_config->filter_start_address_std_frame)) | \
                                               ((uint32_t)SIDFC_LSS(can_parameter->filter_config->filter_number_std_frame)));

                /* configure extended ID filter settings */
                can_parameter->filter_config->filter_start_address_ext_frame = can_parameter->filter_config->filter_start_address_ext_frame >> 2U;
                CAN_M_CAN_XIDFC(can_periph) = (((uint32_t)XIDFC_FLESA(can_parameter->filter_config->filter_start_address_ext_frame)) | \
                                               ((uint32_t)XIDFC_LSE(can_parameter->filter_config->filter_number_ext_frame)));

                /* configure extended ID AND mask */
                CAN_M_CAN_XIDAM(can_periph) = (uint32_t)XIDAM_EIDM(can_parameter->filter_config->and_mask_ext_frame);

                /* configure global filter settings */
                reg_val = CAN_M_CAN_GFC(can_periph);
                reg_val &= ~(CAN_M_CAN_GFC_RRFE | CAN_M_CAN_GFC_RRFS | CAN_M_CAN_GFC_ANFE | CAN_M_CAN_GFC_ANFS);

                /* set remote frames settings */
                if(CAN_REMOTE_FILTER != can_parameter->filter_config->remote_ext_frame_accept) {
                    reg_val |= CAN_M_CAN_GFC_RRFE;
                }

                if(CAN_REMOTE_FILTER != can_parameter->filter_config->remote_std_frame_accept) {
                    reg_val |= CAN_M_CAN_GFC_RRFS;
                }

                /* set non-matching frames settings */
                reg_val |= (((uint32_t)GFC_ANFE(can_parameter->filter_config->non_match_ext_frame_accept)) | \
                            ((uint32_t)GFC_ANFS(can_parameter->filter_config->non_match_std_frame_accept)));

                CAN_M_CAN_GFC(can_periph) = reg_val;
            }

            /* configure Rx FIFO 0 parameters if provided */
            if(NULL != can_parameter->rx_fifo0_config) {
                /* configure Rx FIFO 0 */
                can_parameter->rx_fifo0_config->fifo_start_address = can_parameter->rx_fifo0_config->fifo_start_address >> 2U;
                CAN_M_CAN_RXF0C(can_periph) = (((uint32_t)RXFXC_FSA(can_parameter->rx_fifo0_config->fifo_start_address)) | \
                                               ((uint32_t)RXFXC_FS(can_parameter->rx_fifo0_config->fifo_size)) | \
                                               ((uint32_t)RXFXC_FWM(can_parameter->rx_fifo0_config->fifo_watermark)) | \
                                               ((uint32_t)(can_parameter->rx_fifo0_config->fifo_operation_mode)));

                /* configure Rx FIFO 0 element size */
                CAN_M_CAN_RXESC(can_periph) &= ~CAN_M_CAN_RXESC_F0DS;
                CAN_M_CAN_RXESC(can_periph) |= ((uint32_t)RXESC_F0DS(can_parameter->rx_fifo0_config->fifo_element_size));
            }

            /* configure Rx FIFO 1 parameters if provided */
            if(NULL != can_parameter->rx_fifo1_config) {
                /* configure Rx FIFO 1 */
                can_parameter->rx_fifo1_config->fifo_start_address = can_parameter->rx_fifo1_config->fifo_start_address >> 2U;
                CAN_M_CAN_RXF1C(can_periph) = (((uint32_t)RXFXC_FSA(can_parameter->rx_fifo1_config->fifo_start_address)) | \
                                               ((uint32_t)RXFXC_FS(can_parameter->rx_fifo1_config->fifo_size)) | \
                                               ((uint32_t)RXFXC_FWM(can_parameter->rx_fifo1_config->fifo_watermark)) | \
                                               ((uint32_t)(can_parameter->rx_fifo1_config->fifo_operation_mode)));

                /* configure Rx FIFO 1 element size */
                CAN_M_CAN_RXESC(can_periph) &= ~CAN_M_CAN_RXESC_F1DS;
                CAN_M_CAN_RXESC(can_periph) |= ((uint32_t)RXESC_F1DS(can_parameter->rx_fifo1_config->fifo_element_size));
            }

            /* configure Rx buffer parameters if provided */
            if(NULL != can_parameter->rx_buffer_config) {
                /* configure Rx buffer */
                can_parameter->rx_buffer_config->buffer_start_address = can_parameter->rx_buffer_config->buffer_start_address >> 2U;
                CAN_M_CAN_RXBC(can_periph) = ((uint32_t)RXBC_RBSA(can_parameter->rx_buffer_config->buffer_start_address));

                /* configure Rx buffer element size */
                CAN_M_CAN_RXESC(can_periph) &= ~CAN_M_CAN_RXESC_RBDS;
                CAN_M_CAN_RXESC(can_periph) |= ((uint32_t)RXESC_RBDS(can_parameter->rx_buffer_config->buffer_element_size));
            }

            /* configure Tx buffer parameters if provided */
            if(NULL != can_parameter->tx_buffer_config) {
                if((can_parameter->tx_buffer_config->fifo_or_queue_size + can_parameter->tx_buffer_config->dedicate_buffer_size) > 32U) {
                    reval = ERROR;
                } else {
                    /* configure Tx buffer */
                    can_parameter->tx_buffer_config->tx_buffer_start_address = can_parameter->tx_buffer_config->tx_buffer_start_address >> 2U;
                    CAN_M_CAN_TXBC(can_periph) = (((uint32_t)TXBC_TBSA(can_parameter->tx_buffer_config->tx_buffer_start_address)) | \
                                                  ((uint32_t)TXBC_NDTB(can_parameter->tx_buffer_config->dedicate_buffer_size)) | \
                                                  ((uint32_t)TXBC_TFQS(can_parameter->tx_buffer_config->fifo_or_queue_size)) | \
                                                  ((uint32_t)(can_parameter->tx_buffer_config->fifo_or_queue_mode)));

                    /* configure Tx buffer element size */
                    CAN_M_CAN_TXESC(can_periph) = ((uint32_t)TXESC_TBDS(can_parameter->tx_buffer_config->tx_buffer_element_size));
                }
            }

            /* configure Tx event FIFO parameters if provided */
            if(NULL != can_parameter->tx_event_fifo_config) {
                /* configure Tx event FIFO */
                can_parameter->tx_event_fifo_config->fifo_start_address = can_parameter->tx_event_fifo_config->fifo_start_address >> 2U;
                CAN_M_CAN_TXEFC(can_periph) = (((uint32_t)TXEFC_EFSA(can_parameter->tx_event_fifo_config->fifo_start_address)) | \
                                               ((uint32_t)TXEFC_EFS(can_parameter->tx_event_fifo_config->fifo_size)) | \
                                               ((uint32_t)TXEFC_EFWM(can_parameter->tx_event_fifo_config->fifo_watermark)));
            }

            /* exit initialization mode */
            CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_INIT;
        }
    }

    return reval;
}

/*!
    \brief      get SRAM initialization state (API_ID(0x0004U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_sram_init_state_get(can_dtm_canx_enum dtm_canx)
{
    FlagStatus ret = RESET;
    uint32_t can_periph;

    /* determine which DTM_CAN is selected */
    can_periph = can_dtm_to_can(dtm_canx);

    /* check if SRAM initialization is done */
    if(0U != (CAN_MRAM(can_periph) & CAN_MRAM_IRF)) {
        ret = SET;
    }
    return ret;
}

/*!
    \brief      add standard message ID filter element (API_ID(0x0005U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  frame_format: frame format
      \arg        CAN_FF_STANDARD: standard format filter
      \arg        CAN_FF_EXTENDED: extended format filter
    \param[in]  element_index: ID filter element index
      \arg        min value: 0
      \arg        max value: filter_number_std_frame - 1 or filter_number_ext_frame
    \param[in]  filter: ID filter element parameter struct
                  filter_type: CAN_FILTER_RANGE, CAN_FILTER_DUAL, CAN_FILTER_MASK, CAN_FILTER_RANGE_NOMASK_DISABLE
                  config: CAN_FILTER_DISABLE, CAN_FILTER_TO_RXFIFO0, CAN_FILTER_TO_RXFIFO1, CAN_FILTER_REJECT,
                          CAN_FILTER_HP, CAN_FILTER_TO_RXFIFO0_HP, CAN_FILTER_TO_RXFIFO1_HP, CAN_FILTER_TO_RXBUFFER
                  id1: 0~0x7FF or 0~0x1FFFFFFF
                  id2_or_mask_or_rxbuffercfg: 0~0x7FF or 0~0x1FFFFFFF
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_filter_set(can_dtm_canx_enum dtm_canx, can_ff_enum frame_format, uint8_t element_index, can_filter_element_struct *filter)
{
    uint32_t sxidfc_reg;
    uint32_t filter_start_address;
    uint32_t filter_number;
    uint32_t filter_address;
    uint32_t *filter_element_addr;
    uint32_t each_element_size;
    uint32_t mem_start_address;
    ErrStatus status = SUCCESS;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* check input parameters */
    if(NULL == filter) {
        status = ERROR;
    } else {
        if(CAN_FF_STANDARD == frame_format) {
            /* get filter list standard start address and filter number */
            sxidfc_reg = CAN_M_CAN_SIDFC(can_periph);
            filter_start_address = GET_SIDFC_FLSSA(sxidfc_reg) * 4U;
            filter_number = GET_SIDFC_LSS(sxidfc_reg);
            each_element_size = CAN_FLITER_ES_STD;
        } else {
            /* get filter list extended start address and filter number */
            sxidfc_reg = CAN_M_CAN_XIDFC(can_periph);
            filter_start_address = GET_XIDFC_FLESA(sxidfc_reg) * 4U;
            filter_number = GET_XIDFC_LSE(sxidfc_reg);
            each_element_size = CAN_FLITER_ES_EXT;
        }

        /* check element index */
        if(element_index >= filter_number) {
            status = ERROR;
        } else {
            mem_start_address = can_dtm_to_can(dtm_canx);
            /* calculate filter element address */
            filter_address = filter_start_address + (element_index * each_element_size);
            filter_element_addr = (uint32_t *)(mem_start_address + filter_address);

            /* write filter element values */
            if(CAN_FF_STANDARD == frame_format) {
                *filter_element_addr = (SFET_SFT((uint32_t)filter->filter_type) |
                                        SFET_SFEC((uint32_t)filter->config) |
                                        SFET_SFID1(filter->id1) |
                                        SFET_SFID2(filter->id2_or_mask_or_rxbuffercfg));
            } else {
                /* write filter element values - first word */
                *filter_element_addr = (EFET_EFEC((uint32_t)filter->config) |
                                        EFET_EFID1(filter->id1));

                /* write filter element values - second word */
                filter_element_addr++;
                *filter_element_addr = (EFET_EFT((uint32_t)filter->filter_type) |
                                        EFET_EFID2(filter->id2_or_mask_or_rxbuffercfg));
            }
        }
    }

    return status;
}

/*!
    \brief      enable selected operating mode (API_ID(0x0006U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  mode: the operating mode
                only one parameter can be selected which is shown as below:
      \arg        CAN_MODE_NORMAL: normal operation mode
      \arg        CAN_MODE_INIT: initialization mode
      \arg        CAN_MODE_SLEEP: sleep mode
      \arg        CAN_MODE_MONITOR: bus monitoring mode
      \arg        CAN_MODE_RESTRICTED: restricted operation mode
      \arg        CAN_MODE_TEST: test mode
      \arg        CAN_MODE_EXTERNAL_LOOPBACK: external loopback mode
      \arg        CAN_MODE_INTERNAL_LOOPBACK: internal loopback mode
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_operating_mode_enable(can_dtm_canx_enum dtm_canx, can_operating_mode_enum mode)
{
    uint32_t timeout = CAN_TIMEOUT_COUNT;
    uint32_t reg;
    ErrStatus reval = SUCCESS;
    uint32_t can_periph = (uint32_t)dtm_canx;

    if(CAN_MODE_SLEEP == mode) {
        /* enter sleep mode */
        CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_CSR;
        /* wait until sleep mode is entered */
        while((0U == (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_CSA)) && (0U != timeout)) {
            timeout--;
        }
        /* check the entering of sleep mode */
        if(0U == (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_CSA)) {
            reval =  ERROR;
        }
    } else {
        /* enter initialization mode */
        CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_INIT;
        /* wait until initialization mode is entered */
        while((0U == (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_INIT)) && (0U != timeout)) {
            timeout--;
        }
        /* check the entering of initialization mode */
        if(0U == (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_INIT)) {
            reval =  ERROR;
        } else {
            CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_CCE;
            CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_CSR;
            /* wait until sleep mode is exit */
            while((0U != (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_CSA)) && (0U != timeout)) {
                timeout--;
            }
            /* check the sleep mode is exit */
            if(0U != (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_CSA)) {
                reval =  ERROR;
            } else if(CAN_MODE_INIT != mode) {
                reg = CAN_M_CAN_CCCR(can_periph);
                reg &= ~(CAN_M_CAN_CCCR_MON | CAN_M_CAN_CCCR_ASM);

                switch(mode) {
                case CAN_MODE_NORMAL:
                    /* enter normal operation mode */
                    reg &= ~CAN_M_CAN_CCCR_TEST;
                    CAN_M_CAN_CCCR(can_periph) = reg;
                    break;
                case CAN_MODE_RESTRICTED:
                    /* enter restricted operation mode */
                    reg &= ~CAN_M_CAN_CCCR_TEST;
                    reg |= CAN_M_CAN_CCCR_ASM;
                    CAN_M_CAN_CCCR(can_periph) = reg;
                    break;
                case CAN_MODE_MONITOR:
                    /* enter bus monitoring mode */
                    reg |= CAN_M_CAN_CCCR_MON;
                    CAN_M_CAN_CCCR(can_periph) = reg;
                    if(0U != (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_TEST)) {
                        CAN_M_CAN_TEST(can_periph) &= ~CAN_M_CAN_TEST_LBCK;
                    }
                    break;
                case CAN_MODE_TEST:
                    /* enter test mode */
                    reg |= CAN_M_CAN_CCCR_TEST;
                    CAN_M_CAN_CCCR(can_periph) = reg;
                    /* exit external or internal loopback mode */
                    CAN_M_CAN_TEST(can_periph) &= ~CAN_M_CAN_TEST_LBCK;
                    break;
                case CAN_MODE_EXTERNAL_LOOPBACK:
                    /* enter external loopback mode */
                    reg |= CAN_M_CAN_CCCR_TEST;
                    CAN_M_CAN_CCCR(can_periph) = reg;
                    CAN_M_CAN_TEST(can_periph) |= CAN_M_CAN_TEST_LBCK;
                    break;
                case CAN_MODE_INTERNAL_LOOPBACK:
                    /* first enter test mode */
                    reg |= CAN_M_CAN_CCCR_TEST | CAN_M_CAN_CCCR_MON;
                    CAN_M_CAN_CCCR(can_periph) = reg;
                    /* then enter internal loopback mode */
                    CAN_M_CAN_TEST(can_periph) |= CAN_M_CAN_TEST_LBCK;
                    break;
                default:
                    break;
                }

                /* exit initialization mode */
                CAN_M_CAN_CCCR(can_periph) &= ~(CAN_M_CAN_CCCR_INIT | CAN_M_CAN_CCCR_CCE);
            } else {
                /* initialization mode do nothing */
            }
        }
    }

    return reval;
}

/*!
    \brief      disable selected operating mode (API_ID(0x0007U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  mode: the operating mode
                only one parameter can be selected which is shown as below:
      \arg        CAN_MODE_INIT: initialization mode
      \arg        CAN_MODE_SLEEP: sleep mode
      \arg        CAN_MODE_MONITOR: bus monitoring mode
      \arg        CAN_MODE_RESTRICTED: restricted operation mode
      \arg        CAN_MODE_TEST: test mode
      \arg        CAN_MODE_EXTERNAL_LOOPBACK: external loopback mode
      \arg        CAN_MODE_INTERNAL_LOOPBACK: internal loopback mode
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_operating_mode_disable(can_dtm_canx_enum dtm_canx, can_operating_mode_enum mode)
{
    uint32_t timeout = CAN_TIMEOUT_COUNT;
    ErrStatus reval = SUCCESS;
    uint32_t can_periph = (uint32_t)dtm_canx;

    switch(mode) {
    case CAN_MODE_INIT:
        /* exit initialization mode */
        CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_INIT;
        /* wait until initialization mode is entered */
        while((0U != (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_INIT)) && (0U != timeout)) {
            timeout--;
        }
        /* check the entering of initialization mode */
        if(0U != (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_INIT)) {
            reval =  ERROR;
        }
        break;
    case CAN_MODE_SLEEP:
        /* exit sleep mode */
        CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_CSR;
        /* wait until sleep mode is exit */
        while((0U != (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_CSA)) && (0U != timeout)) {
            timeout--;
        }
        /* check the sleep mode is exit */
        if(0U != (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_CSA)) {
            reval =  ERROR;
        }
        break;
    case CAN_MODE_RESTRICTED:
        /* exit restricted operation mode */
        CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_ASM;
        break;
    case CAN_MODE_MONITOR:
        /* exit bus monitoring mode */
        CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_MON;
        break;
    case CAN_MODE_INTERNAL_LOOPBACK:
    case CAN_MODE_TEST:
    case CAN_MODE_EXTERNAL_LOOPBACK:
        if(CAN_MODE_INTERNAL_LOOPBACK == mode) {
            CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_MON;
        }
        /* enter initialization mode */
        CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_INIT;
        /* wait until initialization mode is entered */
        while((0U == (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_INIT)) && (0U != timeout)) {
            timeout--;
        }
        /* check the entering of initialization mode */
        if(0U == (CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_INIT)) {
            reval =  ERROR;
        } else {
            CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_CCE;
            /* exit test mode */
            CAN_M_CAN_CCCR(can_periph) &= ~CAN_M_CAN_CCCR_TEST;
        }
        /* exit initialization mode */
        CAN_M_CAN_CCCR(can_periph) &= ~(CAN_M_CAN_CCCR_INIT | CAN_M_CAN_CCCR_CCE);
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief      enable automatic retransmission (API_ID(0x0008U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_automatic_retransmission_enable(can_dtm_canx_enum dtm_canx)
{
    /* disable automatic retransmission mode */
    CAN_M_CAN_CCCR((uint32_t)dtm_canx) &= ~CAN_M_CAN_CCCR_DAR;
}

/*!
    \brief      disable automatic retransmission (API_ID(0x0009U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_automatic_retransmission_disable(can_dtm_canx_enum dtm_canx)
{
    /* enable automatic retransmission mode */
    CAN_M_CAN_CCCR((uint32_t)dtm_canx) |= CAN_M_CAN_CCCR_DAR;
}

/*!
    \brief      get Tx buffer number from CAN_M_CAN_TEST register (API_ID(0x000AU))
                notice to enter CAN_MODE_TEST mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  number_type: type of Tx buffer number to get
                only one parameter can be selected which is shown as below:
      \arg        CAN_TEST_TXBUF_LAST_STARTED: Tx buffer number which started last
      \arg        CAN_TEST_TXBUF_LAST_PREPARED: Tx buffer number which prepared last
    \param[out] none
    \retval     0~31 or 0xFF
*/
uint8_t can_test_txbuffer_number_get(uint32_t dtm_canx, uint32_t number_type)
{
    uint8_t number = 0xFFU;
    uint32_t can_periph = (uint32_t)dtm_canx;

    if(CAN_TEST_TXBUF_LAST_STARTED == number_type) {
        /* check Tx buffer number started valid flag */
        if(0U != (CAN_M_CAN_TEST(can_periph) & CAN_M_CAN_TEST_SVAL)) {
            /* get Tx buffer number which started last */
            number = (uint8_t)((CAN_M_CAN_TEST(can_periph) & CAN_M_CAN_TEST_TXBNS) >> CAN_M_CAN_TEST_TXBNS_OFFSET);
        }
    } else if(CAN_TEST_TXBUF_LAST_PREPARED == number_type) {
        /* check Tx buffer number prepared valid flag */
        if(0U != (CAN_M_CAN_TEST(can_periph) & CAN_M_CAN_TEST_PVAL)) {
            /* get Tx buffer number which prepared last */
            number = (uint8_t)((CAN_M_CAN_TEST(can_periph) & CAN_M_CAN_TEST_TXBNP) >> CAN_M_CAN_TEST_TXBNP_OFFSET);
        }
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }

    return number;
}

/*!
    \brief      configure CAN transmit pin output (API_ID(0x000BU))
                notice to enter CAN_MODE_TEST mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  tx_control: CAN transmit pin output control
                only one parameter can be selected which is shown as below:
      \arg        CAN_TX_CONTROL_NORMAL: CAN_TX pin is controlled by the CAN core
      \arg        CAN_TX_CONTROL_SAMPLE_POINT: sample point can be monitored at CAN_TX pin
      \arg        CAN_TX_CONTROL_DOMINANT: CAN_TX pin drives a dominant state (low)
      \arg        CAN_TX_CONTROL_RECESSIVE: CAN_TX pin drives a recessive state (high)
    \param[out] none
    \retval     none
*/
void can_test_transmit_pin_output_config(uint32_t dtm_canx, can_tx_control_enum tx_control)
{
    /* configure TX pin output control */
    CAN_M_CAN_TEST((uint32_t)dtm_canx) &= ~CAN_M_CAN_TEST_TX;
    CAN_M_CAN_TEST((uint32_t)dtm_canx) |= TEST_TX((uint32_t)tx_control);
}

/*!
    \brief      get CAN receive pin state (API_ID(0x000CU))
                notice to enter CAN_MODE_TEST mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus can_test_receive_pin_state_get(uint32_t dtm_canx)
{
    FlagStatus reval = RESET;

    if(0U != (CAN_M_CAN_TEST((uint32_t)dtm_canx) & CAN_M_CAN_TEST_RX)) {
        reval = SET;
    }

    return reval;
}

/*!
    \brief      set CAN FD operation mode (API_ID(0x000DU))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  can_fd_para_init: CAN FD initialization parameter struct
                  iso_can_fd_enable: ENABLE, DISABLE
                  bitrate_switch_enable: ENABLE, DISABLE
                  tdc_enable: ENABLE, DISABLE
                  tdc_offset: 0~127
                  tdc_filter_window: 0~127
                  prescaler: 1~32
                  resync_jump_width: 1~16
                  time_segment_1: 1~32
                  time_segment_2: 2~16
    \param[out] none
    \retval     none
*/
void can_fd_config(can_dtm_canx_enum dtm_canx, can_fd_parameter_struct *can_fd_para_init)
{
    uint32_t reg_val;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* enable CAN FD operation */
    CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_FDOE;
    CAN_M_CAN_CCCR(can_periph) &= ~(CAN_M_CAN_CCCR_NISO | CAN_M_CAN_CCCR_BRSE);

    /* enable/disable ISO CAN FD protocol */
    if(DISABLE == can_fd_para_init->iso_can_fd_enable) {
        /* non-ISO CAN FD */
        CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_NISO;
    }

    /* enable/disable bit rate switching */
    if(DISABLE != can_fd_para_init->bitrate_switch_enable) {
        /* enable bit rate switching */
        CAN_M_CAN_CCCR(can_periph) |= CAN_M_CAN_CCCR_BRSE;
    }

    /* configure bit timing parameters for data phase */
    reg_val = CAN_M_CAN_DBTP(can_periph);
    reg_val &= ~(CAN_M_CAN_DBTP_DSJW | CAN_M_CAN_DBTP_DTSEG2 | CAN_M_CAN_DBTP_DTSEG1 | CAN_M_CAN_DBTP_DBRP | CAN_M_CAN_DBTP_TDC);
    reg_val |= (DBTP_DSJW(can_fd_para_init->resync_jump_width - 1U) | \
                DBTP_DTSEG2(can_fd_para_init->time_segment_2 - 1U) | \
                DBTP_DTSEG1(can_fd_para_init->time_segment_1 - 1U) | \
                DBTP_DBRP(can_fd_para_init->prescaler - 1U));

    /* configure transmitter delay compensation */
    if(DISABLE != can_fd_para_init->tdc_enable) {
        /* enable transmitter delay compensation */
        reg_val |= CAN_M_CAN_DBTP_TDC;

        CAN_M_CAN_TDCR(can_periph) &= ~(CAN_M_CAN_TDCR_TDCO | CAN_M_CAN_TDCR_TDCF);
        /* configure transmitter delay compensation offset */
        CAN_M_CAN_TDCR(can_periph) |= TDCR_TDCO((uint32_t)can_fd_para_init->tdc_offset);
        /* configure transmitter delay compensation filter window */
        CAN_M_CAN_TDCR(can_periph) |= TDCR_TDCF((uint32_t)can_fd_para_init->tdc_filter_window);
    }

    CAN_M_CAN_DBTP(can_periph) = reg_val;
}

/*!
    \brief      disable CAN FD mode (API_ID(0x000EU))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_fd_disable(can_dtm_canx_enum dtm_canx)
{
    /* disable CAN FD operation */
    CAN_M_CAN_CCCR((uint32_t)dtm_canx) &= ~CAN_M_CAN_CCCR_FDOE;
}

/*!
    \brief      get transmitter delay compensation value (API_ID(0x000FU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     0~127
*/
uint16_t can_tdc_get(can_dtm_canx_enum dtm_canx)
{
    return CAN_M_CAN_PSR_HIGH((uint32_t)dtm_canx) & CAN_TDCV_MASK;
}

/*!
    \brief      configure transmitter delay compensation (API_ID(0x0010U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  enable
      \arg        ENABLE
      \arg        DISABLE
    \param[in]  offset: transmitter delay compensation offset
      \arg        0~0x7F
    \param[in]  filter_window: transmitter delay compensation filter window
      \arg        0~0x7F
    \param[out] none
    \retval     none
*/
void can_tdc_config(can_dtm_canx_enum dtm_canx, ControlStatus enable, uint8_t offset, uint8_t filter_window)
{
    uint32_t can_periph = (uint32_t)dtm_canx;
    if(ENABLE == enable) {
        /* enable transmitter delay compensation */
        CAN_M_CAN_DBTP(can_periph) |= CAN_M_CAN_DBTP_TDC;

        CAN_M_CAN_TDCR(can_periph) &= ~(CAN_M_CAN_TDCR_TDCO | CAN_M_CAN_TDCR_TDCF);
        /* configure transmitter delay compensation offset */
        CAN_M_CAN_TDCR(can_periph) |= TDCR_TDCO((uint32_t)offset);
        /* configure transmitter delay compensation filter window */
        CAN_M_CAN_TDCR(can_periph) |= TDCR_TDCF((uint32_t)filter_window);
    } else {
        /* disable transmitter delay compensation */
        CAN_M_CAN_DBTP(can_periph) &= ~CAN_M_CAN_DBTP_TDC;
    }
}

/*!
    \brief      enable edge filtering during bus integration (API_ID(0x0011U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_edge_filtering_enable(can_dtm_canx_enum dtm_canx)
{
    /* enable edge filtering during bus integration */
    CAN_M_CAN_CCCR((uint32_t)dtm_canx) |= CAN_M_CAN_CCCR_EFBI;
}

/*!
    \brief      disable edge filtering during bus integration (API_ID(0x0012U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_edge_filtering_disable(can_dtm_canx_enum dtm_canx)
{
    /* disable edge filtering during bus integration */
    CAN_M_CAN_CCCR((uint32_t)dtm_canx) &= ~CAN_M_CAN_CCCR_EFBI;
}

/*!
    \brief      enable protocol exception handling (API_ID(0x0013U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_protocol_exception_enable(can_dtm_canx_enum dtm_canx)
{
    /* enable protocol exception handling */
    CAN_M_CAN_CCCR((uint32_t)dtm_canx) &= ~CAN_M_CAN_CCCR_PXHD;
}

/*!
    \brief      disable protocol exception handling (API_ID(0x0014U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_protocol_exception_disable(can_dtm_canx_enum dtm_canx)
{
    /* disable protocol exception handling */
    CAN_M_CAN_CCCR((uint32_t)dtm_canx) |= CAN_M_CAN_CCCR_PXHD;
}

/*!
    \brief      enable 'disable modification on read' function for DTM_CAN (API_ID(0x0015U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_dismodify_on_read_enable(can_dtm_canx_enum dtm_canx)
{
    /* determine which DTM_CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
        CAN_DMR(CAN0) |= CAN_DMR_DMORD0;
        break;
    case DTM_CAN1:
        CAN_DMR(CAN0) |= CAN_DMR_DMORD1;
        break;
    case DTM_CAN2:
        CAN_DMR(CAN1) |= CAN_DMR_DMORD0;
        break;
    case DTM_CAN3:
        CAN_DMR(CAN1) |= CAN_DMR_DMORD1;
        break;
    case DTM_CAN4:
        CAN_DMR(CAN1) |= CAN_DMR_DMORD2;
        break;
    case DTM_CAN5:
        CAN_DMR(CAN2) |= CAN_DMR_DMORD0;
        break;
    case DTM_CAN6:
        CAN_DMR(CAN2) |= CAN_DMR_DMORD1;
        break;
    case DTM_CAN7:
        CAN_DMR(CAN2) |= CAN_DMR_DMORD2;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable 'disable modification on read' function for DTM_CAN (API_ID(0x0016U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_dismodify_on_read_disable(can_dtm_canx_enum dtm_canx)
{
    /* determine which DTM_CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
        CAN_DMR(CAN0) &= ~CAN_DMR_DMORD0;
        break;
    case DTM_CAN1:
        CAN_DMR(CAN0) &= ~CAN_DMR_DMORD1;
        break;
    case DTM_CAN2:
        CAN_DMR(CAN1) &= ~CAN_DMR_DMORD0;
        break;
    case DTM_CAN3:
        CAN_DMR(CAN1) &= ~CAN_DMR_DMORD1;
        break;
    case DTM_CAN4:
        CAN_DMR(CAN1) &= ~CAN_DMR_DMORD2;
        break;
    case DTM_CAN5:
        CAN_DMR(CAN2) &= ~CAN_DMR_DMORD0;
        break;
    case DTM_CAN6:
        CAN_DMR(CAN2) &= ~CAN_DMR_DMORD1;
        break;
    case DTM_CAN7:
        CAN_DMR(CAN2) &= ~CAN_DMR_DMORD2;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable clock stop request for DTM_CAN (API_ID(0x0017U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_clock_stop_request_enable(can_dtm_canx_enum dtm_canx)
{
    /* determine which DTM_CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
        CAN_CSR(CAN0) |= CAN_CSR_CSR0;
        break;
    case DTM_CAN1:
        CAN_CSR(CAN0) |= CAN_CSR_CSR1;
        break;
    case DTM_CAN2:
        CAN_CSR(CAN1) |= CAN_CSR_CSR0;
        break;
    case DTM_CAN3:
        CAN_CSR(CAN1) |= CAN_CSR_CSR1;
        break;
    case DTM_CAN4:
        CAN_CSR(CAN1) |= CAN_CSR_CSR2;
        break;
    case DTM_CAN5:
        CAN_CSR(CAN2) |= CAN_CSR_CSR0;
        break;
    case DTM_CAN6:
        CAN_CSR(CAN2) |= CAN_CSR_CSR1;
        break;
    case DTM_CAN7:
        CAN_CSR(CAN2) |= CAN_CSR_CSR2;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable clock stop request for DTM_CAN (API_ID(0x0018U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_clock_stop_request_disable(can_dtm_canx_enum dtm_canx)
{
    /* determine which DTM_CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
        CAN_CSR(CAN0) &= ~CAN_CSR_CSR0;
        break;
    case DTM_CAN1:
        CAN_CSR(CAN0) &= ~CAN_CSR_CSR1;
        break;
    case DTM_CAN2:
        CAN_CSR(CAN1) &= ~CAN_CSR_CSR0;
        break;
    case DTM_CAN3:
        CAN_CSR(CAN1) &= ~CAN_CSR_CSR1;
        break;
    case DTM_CAN4:
        CAN_CSR(CAN1) &= ~CAN_CSR_CSR2;
        break;
    case DTM_CAN5:
        CAN_CSR(CAN2) &= ~CAN_CSR_CSR0;
        break;
    case DTM_CAN6:
        CAN_CSR(CAN2) &= ~CAN_CSR_CSR1;
        break;
    case DTM_CAN7:
        CAN_CSR(CAN2) &= ~CAN_CSR_CSR2;
        break;
    default:
        break;
    }
}

/*!
    \brief      get clock stop acknowledge for DTM_CAN (API_ID(0x0019U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_clock_stop_acknowledge_get(can_dtm_canx_enum dtm_canx)
{
    FlagStatus ret = RESET;
    uint32_t flag = 0U;

    /* determine which DTM_CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
        /* get clock stop acknowledge for DTM_CAN0 */
        flag = CAN_CSA(CAN0) & CAN_CSA_CSA0;
        break;
    case DTM_CAN1:
        /* get clock stop acknowledge for DTM_CAN1 */
        flag = CAN_CSA(CAN0) & CAN_CSA_CSA1;
        break;
    case DTM_CAN2:
        /* get clock stop acknowledge for DTM_CAN2 */
        flag = CAN_CSA(CAN1) & CAN_CSA_CSA0;
        break;
    case DTM_CAN3:
        /* get clock stop acknowledge for DTM_CAN3 */
        flag = CAN_CSA(CAN1) & CAN_CSA_CSA1;
        break;
    case DTM_CAN4:
        /* get clock stop acknowledge for DTM_CAN4 */
        flag = CAN_CSA(CAN1) & CAN_CSA_CSA2;
        break;
    case DTM_CAN5:
        /* get clock stop acknowledge for DTM_CAN5 */
        flag = CAN_CSA(CAN2) & CAN_CSA_CSA0;
        break;
    case DTM_CAN6:
        /* get clock stop acknowledge for DTM_CAN6 */
        flag = CAN_CSA(CAN2) & CAN_CSA_CSA1;
        break;
    case DTM_CAN7:
        /* get clock stop acknowledge for DTM_CAN7 */
        flag = CAN_CSA(CAN2) & CAN_CSA_CSA2;
        break;
    default:
        break;
    }

    if(0U != flag) {
        ret = SET;
    }
    return ret;
}

/*!
    \brief      enable DMA request for DTM_CAN (API_ID(0x001AU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_dma_request_enable(can_dtm_canx_enum dtm_canx)
{
    /* determine which DTM_CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
        CAN_CTL(CAN0) |= CAN_CTL_DMAEN0;
        break;
    case DTM_CAN1:
        CAN_CTL(CAN0) |= CAN_CTL_DMAEN1;
        break;
    case DTM_CAN2:
        CAN_CTL(CAN1) |= CAN_CTL_DMAEN0;
        break;
    case DTM_CAN3:
        CAN_CTL(CAN1) |= CAN_CTL_DMAEN1;
        break;
    case DTM_CAN4:
        CAN_CTL(CAN1) |= CAN_CTL_DMAEN2;
        break;
    case DTM_CAN5:
        CAN_CTL(CAN2) |= CAN_CTL_DMAEN0;
        break;
    case DTM_CAN6:
        CAN_CTL(CAN2) |= CAN_CTL_DMAEN1;
        break;
    case DTM_CAN7:
        CAN_CTL(CAN2) |= CAN_CTL_DMAEN2;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable DMA request for DTM_CAN (API_ID(0x001BU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_dma_request_disable(can_dtm_canx_enum dtm_canx)
{
    /* determine which DTM_CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
        CAN_CTL(CAN0) &= ~CAN_CTL_DMAEN0;
        break;
    case DTM_CAN1:
        CAN_CTL(CAN0) &= ~CAN_CTL_DMAEN1;
        break;
    case DTM_CAN2:
        CAN_CTL(CAN1) &= ~CAN_CTL_DMAEN0;
        break;
    case DTM_CAN3:
        CAN_CTL(CAN1) &= ~CAN_CTL_DMAEN1;
        break;
    case DTM_CAN4:
        CAN_CTL(CAN1) &= ~CAN_CTL_DMAEN2;
        break;
    case DTM_CAN5:
        CAN_CTL(CAN2) &= ~CAN_CTL_DMAEN0;
        break;
    case DTM_CAN6:
        CAN_CTL(CAN2) &= ~CAN_CTL_DMAEN1;
        break;
    case DTM_CAN7:
        CAN_CTL(CAN2) &= ~CAN_CTL_DMAEN2;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable CAN_MERRCTL register write access (API_ID(0x001CU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_merrctl_write_access_enable(can_dtm_canx_enum dtm_canx)
{
    uint32_t can_periph;

    /* determine which DTM_CAN is selected */
    can_periph = can_dtm_to_can(dtm_canx);

    /* enable CAN_MERRCTL register write */
    CAN_CTL(can_periph) |= CAN_CTL_ECRWEN;

    /* clear RWDIS bit */
    CAN_MERRCTL(can_periph) &= ~CAN_MERRCTL_RWDIS;
}

/*!
    \brief      disable CAN_MERRCTL register write access (API_ID(0x001DU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_merrctl_write_access_disable(can_dtm_canx_enum dtm_canx)
{
    uint32_t can_periph;

    /* determine which DTM_CAN is selected */
    can_periph = can_dtm_to_can(dtm_canx);

    /* enable CAN_MERRCTL register write */
    CAN_CTL(can_periph) |= CAN_CTL_ECRWEN;

    /* set RWDIS bit */
    CAN_MERRCTL(can_periph) |= CAN_MERRCTL_RWDIS;

    /* disable CAN_MERRCTL register write */
    CAN_CTL(can_periph) &= ~CAN_CTL_ECRWEN;
}

/*!
    \brief      enable error report and error status update (API_ID(0x001EU))
                notice to call can_merrctl_write_access_enable() function as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_ecc_enable(can_dtm_canx_enum dtm_canx)
{
    ErrStatus ret_status = SUCCESS;
    uint32_t can_periph;
    uint32_t ctl, merrctl;

    /* determine which DTM_CAN is selected */
    can_periph = can_dtm_to_can(dtm_canx);
    ctl = CAN_CTL(can_periph);
    merrctl = CAN_MERRCTL(can_periph);

    /* check if CAN_MERRCTL register is write-protected */
    if((0U != (merrctl & CAN_MERRCTL_RWDIS)) || (0U == (ctl & CAN_CTL_ECRWEN))) {
        ret_status = ERROR;
    } else {
        /* enable ECC */
        CAN_MERRCTL(can_periph) |= CAN_MERRCTL_ECCEN;
    }

    return ret_status;
}

/*!
    \brief      disable error report and error status update (API_ID(0x001FU))
                notice to call can_merrctl_write_access_enable() function as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_ecc_disable(can_dtm_canx_enum dtm_canx)
{
    ErrStatus ret_status = SUCCESS;
    uint32_t can_periph;
    uint32_t ctl, merrctl;

    /* determine which DTM_CAN is selected */
    can_periph = can_dtm_to_can(dtm_canx);
    ctl = CAN_CTL(can_periph);
    merrctl = CAN_MERRCTL(can_periph);

    /* check if CAN_MERRCTL register is write-protected */
    if((0U != (merrctl & CAN_MERRCTL_RWDIS)) || (0U == (ctl & CAN_CTL_ECRWEN))) {
        ret_status = ERROR;
    } else {
        /* disable ECC */
        CAN_MERRCTL(can_periph) &= ~CAN_MERRCTL_ECCEN;
    }

    return ret_status;
}

/*!
    \brief      get memory error status (API_ID(0x0020U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  index: memory error index
                only one parameter can be selected which is shown as below:
      \arg        CAN_MEM_ERR_CORRECTABLE_0: CAN memory error correctable 0
      \arg        CAN_MEM_ERR_CORRECTABLE_1: CAN memory error correctable 1
      \arg        CAN_MEM_ERR_CORRECTABLE_2: CAN memory error correctable 2
      \arg        CAN_MEM_ERR_CORRECTABLE_3: CAN memory error correctable 3
      \arg        CAN_MEM_ERR_NONCORRECTABLE: CAN memory error noncorrectable
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_memory_error_status_get(can_dtm_canx_enum dtm_canx, can_memory_error_index_enum index)
{
    FlagStatus flag = RESET;
    uint32_t can_periph;

    /* determine which DTM_CAN is selected */
    can_periph = can_dtm_to_can(dtm_canx);

    if(index == CAN_MEM_ERR_NONCORRECTABLE) {
        if(0U != (CAN_NCERRR(can_periph) & CAN_NCERRR_NCERS)) {
            flag = SET;
        }
    } else {
        if(0U != (CAN_CERRR(can_periph, (uint32_t)index) & CAN_CERRR_CERS)) {
            flag = SET;
        }
    }

    return flag;
}

/*!
    \brief      get memory error address (API_ID(0x0021U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  index: memory error index
                only one parameter can be selected which is shown as below:
      \arg        CAN_MEM_ERR_CORRECTABLE_0: CAN memory error correctable 0
      \arg        CAN_MEM_ERR_CORRECTABLE_1: CAN memory error correctable 1
      \arg        CAN_MEM_ERR_CORRECTABLE_2: CAN memory error correctable 2
      \arg        CAN_MEM_ERR_CORRECTABLE_3: CAN memory error correctable 3
      \arg        CAN_MEM_ERR_NONCORRECTABLE: CAN memory error noncorrectable
    \param[out] none
    \retval     memory error address
*/
uint32_t can_memory_error_address_get(can_dtm_canx_enum dtm_canx, can_memory_error_index_enum index)
{
    uint32_t ret;
    uint32_t can_periph;

    /* determine which DTM_CAN is selected */
    can_periph = can_dtm_to_can(dtm_canx);

    /* get memory error address */
    if(index == CAN_MEM_ERR_NONCORRECTABLE) {
        ret = GET_NCERRR_NCERA(CAN_NCERRR(can_periph));
    } else {
        ret = GET_CERRR_CERA(CAN_CERRR(can_periph, (uint32_t)index));
    }

    return ret;
}

/*!
    \brief      clear CAN_CERRR0 - CAN_CERRR3, and CAN_NCERRR register record (API_ID(0x0022U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_memory_error_record_clear(can_dtm_canx_enum dtm_canx)
{
    uint32_t can_periph;

    /* determine which DTM_CAN is selected */
    can_periph = can_dtm_to_can(dtm_canx);

    /* enable CAN_MERRCTL register write */
    CAN_CTL(can_periph) |= CAN_CTL_ECRWEN;
    /* clear RWDIS bit */
    CAN_MERRCTL(can_periph) &= ~CAN_MERRCTL_RWDIS;

    /* disable ECC to clear memory error records */
    CAN_MERRCTL(can_periph) &= ~CAN_MERRCTL_ECCEN;

    /* enable ECC again */
    CAN_MERRCTL(can_periph) |= CAN_MERRCTL_ECCEN;
}


/*!
    \brief      configure the message RAM watchdog counter (API_ID(0x0023U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  counter: message RAM watchdog counter start value
      \arg        0~255
    \param[out] none
    \retval     none
*/
void can_sram_watchdog_config(uint32_t dtm_canx, uint8_t counter)
{
    /* configure watchdog counter */
    CAN_M_CAN_RWD(dtm_canx) &= ~CAN_M_CAN_RWD_WDC;
    CAN_M_CAN_RWD(dtm_canx) |= (uint32_t)counter & CAN_M_CAN_RWD_WDC;
}

/*!
    \brief      get message RAM watchdog counter value (API_ID(0x0024U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     0~255
*/
uint8_t can_sram_watchdog_counter_get(uint32_t dtm_canx)
{
    return (uint8_t)((CAN_M_CAN_RWD(dtm_canx) & CAN_M_CAN_RWD_WDV) >> CAN_M_CAN_RWD_WDV_OFFSET);
}

/*!
    \brief      timeout configuration (API_ID(0x0025U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  prescaler: timestamp and timeout counter prescaler
      \arg        1~16
    \param[out] none
    \retval     none
*/
void can_timestamp_timeout_prescaler_config(can_dtm_canx_enum dtm_canx, uint16_t prescaler)
{
    uint32_t temp;

    /* configure timestamp and timeout prescaler */
    temp = CAN_M_CAN_TSCC((uint32_t)dtm_canx);
    temp &= ~CAN_M_CAN_TSCC_TCP;
    temp |= TSCC_TCP((uint32_t)prescaler - 1U);
    CAN_M_CAN_TSCC((uint32_t)dtm_canx) = temp;
}

/*!
    \brief      enable CAN timestamp (API_ID(0x0026U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_timestamp_enable(can_dtm_canx_enum dtm_canx)
{
    uint32_t temp;

    /* enable timestamp */
    temp = CAN_M_CAN_TSCC((uint32_t)dtm_canx);
    temp &= ~CAN_M_CAN_TSCC_TSS;
    temp |= CAN_TS_INTERNAL;
    CAN_M_CAN_TSCC((uint32_t)dtm_canx) = temp;
}

/*!
    \brief      disable CAN timestamp (API_ID(0x0027U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_timestamp_disable(can_dtm_canx_enum dtm_canx)
{
    uint32_t temp;

    /* disable timestamp */
    temp = CAN_M_CAN_TSCC((uint32_t)dtm_canx);
    temp &= ~CAN_M_CAN_TSCC_TSS;
    temp |= CAN_TS_DISABLE;
    CAN_M_CAN_TSCC((uint32_t)dtm_canx) = temp;
}

/*!
    \brief      reset CAN timestamp counter value (API_ID(0x0028U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_timestamp_reset(can_dtm_canx_enum dtm_canx)
{
    CAN_M_CAN_TSCV((uint32_t)dtm_canx) = 0U;
}

/*!
    \brief      enable timeout counter (API_ID(0x0029U))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  timeout_mode: timeout counter operating mode
                only one parameter can be selected which is shown as below:
      \arg        CAN_TIMEOUT_CONTINUOUS: continuous operation
      \arg        CAN_TIMEOUT_TXFIFO: controlled by Tx event FIFO
      \arg        CAN_TIMEOUT_RXFIFO0: controlled by Rx FIFO 0
      \arg        CAN_TIMEOUT_RXFIFO1: controlled by Rx FIFO 1
    \param[in]  timeout_period: timeout period
      \arg        0~0xFFFF
    \param[out] none
    \retval     none
*/
void can_timeout_enable(can_dtm_canx_enum dtm_canx, can_timeout_mode_enum timeout_mode, uint16_t timeout_period)
{
    uint32_t temp;

    /* configure timeout counter */
    temp = CAN_M_CAN_TOCC((uint32_t)dtm_canx);
    temp &= ~(CAN_M_CAN_TOCC_TOS | CAN_M_CAN_TOCC_TOP);
    temp |= (CAN_M_CAN_TOCC_ETOC | TOCC_TOS((uint32_t)timeout_mode) | TOCC_TOP(timeout_period));
    CAN_M_CAN_TOCC((uint32_t)dtm_canx) = temp;
}

/*!
    \brief      disable timeout counter (API_ID(0x002AU))
                notice to enter CAN_MODE_INIT mode as condition
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_timeout_disable(can_dtm_canx_enum dtm_canx)
{
    /* disable timeout counter */
    CAN_M_CAN_TOCC((uint32_t)dtm_canx) &= ~CAN_M_CAN_TOCC_ETOC;
}

/*!
    \brief      get timeout counter value (API_ID(0x002BU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     0~0xFFFF
*/
uint16_t can_timeout_value_get(can_dtm_canx_enum dtm_canx)
{
    /* get timeout counter value */
    return ((uint16_t)(CAN_M_CAN_TOCV((uint32_t)dtm_canx) & CAN_M_CAN_TOCV_TOC));
}

/*!
    \brief      restart CAN timeout counter value (API_ID(0x002CU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_timeout_restart(can_dtm_canx_enum dtm_canx)
{
    CAN_M_CAN_TOCV((uint32_t)dtm_canx) = 0U;
}

/*!
    \brief      get Tx FIFO / Tx queue free level (API_ID(0x002DU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     0~32
*/
uint8_t can_tx_fifo_free_level_get(can_dtm_canx_enum dtm_canx)
{
    /* get Tx FIFO free level */
    return (uint8_t)(CAN_M_CAN_TXFQS((uint32_t)dtm_canx) & CAN_M_CAN_TXFQS_TFFL);
}

/*!
    \brief      get Tx FIFO / Tx event FIFO / Rx FIFO get index (API_ID(0x002EU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  fifo_type: FIFO type
                only one parameter can be selected which is shown as below:
      \arg        CAN_FIFO_TX: Tx FIFO
      \arg        CAN_FIFO_RX0: Rx FIFO 0
      \arg        CAN_FIFO_RX1: Rx FIFO 1
      \arg        CAN_FIFO_TXEVENT: Tx event FIFO
    \param[out] none
    \retval     0~31 or 0~63
*/
uint8_t can_fifo_get_index_get(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type)
{
    uint8_t get_index = 0U;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* get FIFO get index based on FIFO type */
    switch(fifo_type) {
    case CAN_FIFO_TX:
        get_index = (uint8_t)(GET_TXFQS_TFGI(CAN_M_CAN_TXFQS(can_periph)));
        break;
    case CAN_FIFO_RX0:
        get_index = (uint8_t)(GET_RXFXS_FXGI(CAN_M_CAN_RXF0S(can_periph)));
        break;
    case CAN_FIFO_RX1:
        get_index = (uint8_t)(GET_RXFXS_FXGI(CAN_M_CAN_RXF1S(can_periph)));
        break;
    case CAN_FIFO_TXEVENT:
        get_index = (uint8_t)(GET_TXEFS_EFGI(CAN_M_CAN_TXEFS(can_periph)));
        break;
    default:
        break;
    }

    return get_index;
}

/*!
    \brief      get Tx FIFO / Tx queue / Tx event FIFO / Rx FIFO put index (API_ID(0x002FU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  fifo_type: FIFO type
                only one parameter can be selected which is shown as below:
      \arg        CAN_FIFO_TX: Tx FIFO
      \arg        CAN_FIFO_RX0: Rx FIFO 0
      \arg        CAN_FIFO_RX1: Rx FIFO 1
      \arg        CAN_FIFO_TXEVENT: Tx event FIFO
    \param[out] none
    \retval     0~31 or 0~63
*/
uint8_t can_fifo_put_index_get(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type)
{
    uint8_t put_index = 0U;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* get FIFO put index based on FIFO type */
    switch(fifo_type) {
    case CAN_FIFO_TX:
        put_index = (uint8_t)(GET_TXFQS_TFQPI(CAN_M_CAN_TXFQS(can_periph)));
        break;
    case CAN_FIFO_RX0:
        put_index = (uint8_t)(GET_RXFXS_FXPI(CAN_M_CAN_RXF0S(can_periph)));
        break;
    case CAN_FIFO_RX1:
        put_index = (uint8_t)(GET_RXFXS_FXPI(CAN_M_CAN_RXF1S(can_periph)));
        break;
    case CAN_FIFO_TXEVENT:
        put_index = (uint8_t)(GET_TXEFS_EFPI(CAN_M_CAN_TXEFS(can_periph)));
        break;
    default:
        break;
    }

    return put_index;
}

/*!
    \brief      get Tx FIFO / Tx queue / Tx event FIFO / Rx FIFO full state (API_ID(0x0030U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  fifo_type: FIFO type
                only one parameter can be selected which is shown as below:
      \arg        CAN_FIFO_TX: Tx FIFO
      \arg        CAN_FIFO_RX0: Rx FIFO 0
      \arg        CAN_FIFO_RX1: Rx FIFO 1
      \arg        CAN_FIFO_TXEVENT: Tx event FIFO
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_fifo_full_state_get(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type)
{
    uint32_t flag = 0U;
    FlagStatus state = RESET;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* get FIFO full state based on FIFO type */
    switch(fifo_type) {
    case CAN_FIFO_TX:
        flag = CAN_M_CAN_TXFQS(can_periph) & CAN_M_CAN_TXFQS_TFQF;
        break;
    case CAN_FIFO_RX0:
        flag = CAN_M_CAN_RXF0S(can_periph) & CAN_M_CAN_RXFXS_FF;
        break;
    case CAN_FIFO_RX1:
        flag = CAN_M_CAN_RXF1S(can_periph) & CAN_M_CAN_RXFXS_FF;
        break;
    case CAN_FIFO_TXEVENT:
        flag = CAN_M_CAN_TXEFS(can_periph) & CAN_M_CAN_TXEFS_EFF;
        break;
    default:
        break;
    }

    if(0U != flag) {
        state = SET;
    }

    return state;
}

/*!
    \brief      get Tx event FIFO / Rx FIFO fill level (API_ID(0x0031U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  fifo_type: FIFO type
                only one parameter can be selected which is shown as below:
      \arg        CAN_FIFO_RX0: Rx FIFO 0
      \arg        CAN_FIFO_RX1: Rx FIFO 1
      \arg        CAN_FIFO_TXEVENT: Tx event FIFO
    \param[out] none
    \retval     0~32 or 0~64
*/
uint8_t can_fifo_fill_level_get(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type)
{
    uint8_t fill_level = 0U;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* get FIFO fill level based on FIFO type */
    switch(fifo_type) {
    case CAN_FIFO_RX0:
        fill_level = (uint8_t)(CAN_M_CAN_RXF0S(can_periph) & CAN_M_CAN_RXFXS_FFL);
        break;
    case CAN_FIFO_RX1:
        fill_level = (uint8_t)(CAN_M_CAN_RXF1S(can_periph) & CAN_M_CAN_RXFXS_FFL);
        break;
    case CAN_FIFO_TXEVENT:
        fill_level = (uint8_t)(CAN_M_CAN_TXEFS(can_periph) & CAN_M_CAN_TXEFS_EFFL);
        break;
    default:
        break;
    }

    return fill_level;
}

/*!
    \brief      acknowledge Tx event FIFO / Rx FIFO messages (API_ID(0x0032U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  fifo_type: FIFO type
                only one parameter can be selected which is shown as below:
      \arg        CAN_FIFO_RX0: Rx FIFO 0
      \arg        CAN_FIFO_RX1: Rx FIFO 1
      \arg        CAN_FIFO_TXEVENT: Tx event FIFO
    \param[out] none
    \retval     none
*/
void can_fifo_acknowledge(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type)
{
    uint8_t index;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* get FIFO get index */
    index = can_fifo_get_index_get(dtm_canx, fifo_type);

    /* acknowledge FIFO based on FIFO type */
    switch(fifo_type) {
    case CAN_FIFO_RX0:
        CAN_M_CAN_RXF0A(can_periph) = index;
        break;
    case CAN_FIFO_RX1:
        CAN_M_CAN_RXF1A(can_periph) = index;
        break;
    case CAN_FIFO_TXEVENT:
        CAN_M_CAN_TXEFA(can_periph) = index;
        break;
    default:
        break;
    }
}

/*!
    \brief      read a Tx event FIFO element (API_ID(0x0033U))
    \param[in]  dtm_canx: DTM_CANx(x=0,1,2,3,4,5,6,7)
    \param[out] txevent: pointer to Tx event FIFO element structure
    \retval     none
*/
void can_txev_fifo_read(can_dtm_canx_enum dtm_canx, can_txev_fifo_element_struct *txevent)
{
    uint32_t e0, e1;
    uint32_t address;
    uint8_t wmm, index;
    uint32_t event_type;
    uint32_t txev_fifo_saddr, mem_address;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* check if Tx event FIFO is not empty */
    if(0U != (CAN_M_CAN_TXEFS(can_periph) & CAN_M_CAN_TXEFS_EFFL)) {
        /* get Tx event FIFO get index */
        index = (uint8_t)(GET_TXEFS_EFGI(CAN_M_CAN_TXEFS(can_periph)));
        /* get Tx event FIFO element start address */
        txev_fifo_saddr = GET_TXEFC_EFSA(CAN_M_CAN_TXEFC(can_periph)) * 4U;
        /* determine which DTM_CAN is selected */
        mem_address = can_dtm_to_can(dtm_canx);
        /* calculate Tx event FIFO element address */
        address = mem_address + txev_fifo_saddr + ((uint32_t)index * 8U);

        /* check if wide message marker is enabled */
        wmm = (uint8_t)((CAN_M_CAN_CCCR(can_periph) & CAN_M_CAN_CCCR_WMM) >> CAN_M_CAN_CCCR_WMM_OFFSET);

        /* get first word of Tx event FIFO element (E0) */
        e0 = REG32(address);
        /* get second word of Tx event FIFO element (E1A or E1B) */
        address += 4U;
        e1 = REG32(address);

        /* copy R0 and R1 words to message structure */
        txevent->id = e0 & CAN_E0_ID;
        txevent->rtr = (e0 & CAN_E0_RTR) >> CAN_E0_RTR_OFFSET;
        txevent->xtd = (e0 & CAN_E0_RTR) >> CAN_E0_XTD_OFFSET;
        txevent->esi = (e0 & CAN_E0_RTR) >> CAN_E0_ESI_OFFSET;

        /* if is standard identifier */
        if(0U == txevent->xtd) {
            txevent->id >>= 18U;
        }

        txevent->dlc = (uint8_t)((e1 & CAN_E1A_DLC) >> CAN_E1_DLC_OFFSET);
        txevent->brs = (uint8_t)((e1 & CAN_E1A_BRS) >> CAN_E1_BRS_OFFSET);
        txevent->fdf = (uint8_t)((e1 & CAN_E1A_FDF) >> CAN_E1_FDF_OFFSET);

        /* calculate data length based on DLC value */
        if(txevent->fdf == 1U) {
            /* CAN FD frame */
            txevent->data_length = dlc_to_databytes[txevent->dlc];
        } else {
            /* classic CAN frame */
            if(txevent->dlc <= 8U) {
                txevent->data_length = txevent->dlc;
            } else {
                txevent->data_length = 8U;
            }
        }

        /* get event type */
        event_type = (e1 & CAN_E1A_ET) >> CAN_E1_ET_OFFSET;
        if(1U == event_type) {
            txevent->event_type = CAN_TX;
        } else if(2U == event_type) {
            txevent->event_type = CAN_TX_AFTER_CANCEL;
        } else {
            txevent->event_type = CAN_NONE;
        }

        /* get timestamp if available */
        if(0U == wmm) {
            txevent->timestamp = (uint16_t)(e1 & CAN_E1A_TXTS);
            txevent->message_marker = (uint16_t)((e1 & CAN_E1A_MM_LOW) >> CAN_E1_MM_LOW_OFFSET);
        } else {
            txevent->timestamp = 0U;
            txevent->message_marker = (uint16_t)((e1 & CAN_E1B_MM_LOW) >> CAN_E1_MM_LOW_OFFSET);
            txevent->message_marker |= (uint16_t)(e1 & CAN_E1B_MM_HIGH);
        }

        /* update Tx event FIFO get index */
        CAN_M_CAN_TXEFA(can_periph) = index;
    }
}

/*!
    \brief      configure CAN transmission message (API_ID(0x0034U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  transmit_message: CAN transmit message struct
                  id: 0~0x3FF or 0~0x1FFFFFFF
                  rtr: CAN_FT_DATA, CAN_FT_REMOTE
                  xtd: CAN_FF_STANDARD, CAN_FF_EXTENDED
                  esi: 0, 1
                  brs: ENABLE, DISABLE
                  fdf: ENABLE, DISABLE
                  message_marker: 0~0xFFFF
                  ev_fifo_control: CAN_TXEVENT_FIFO_STORE, CAN_TXEVENT_FIFO_DISABLE
                  data: transmit data
                  data_bytes: 0~64
    \param[out] none
    \retval     the Tx buffer index to transmit: 0~31 or 0xFF
*/
uint8_t can_message_transmit_prepare(can_dtm_canx_enum dtm_canx, can_transmit_message_struct *transmit_message)
{
    uint32_t txfqs_reg;
    uint32_t buffer_index = 0x000000FFU;
    uint32_t tx_buffer_start_address;
    uint32_t buffer_element_size;
    uint32_t dedicated_buffer_size;
    uint32_t *buffer_addr;
    uint32_t t0_word = 0U;
    uint32_t t1_word = 0U;
    uint32_t dlc;
    uint8_t i = 0U;
    uint32_t length;
    uint32_t mem_address;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* get Tx FIFO/Queue status */
    txfqs_reg = CAN_M_CAN_TXFQS(can_periph);
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NULL == transmit_message) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0034U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get Tx buffer configuration */
        tx_buffer_start_address = GET_TXBC_TBSA(CAN_M_CAN_TXBC(can_periph)) * 4U;
        dedicated_buffer_size = GET_TXBC_NDTB(CAN_M_CAN_TXBC(can_periph));
        if(dedicated_buffer_size > 0x20U) {
            dedicated_buffer_size = 0x20U;
        }

        /* get buffer index */
        if(dedicated_buffer_size > 0U) {
            /* use dedicated buffer */
            buffer_index = 0U;
            for(i = 0U; i < dedicated_buffer_size; i++) {
                /* check if buffer is free */
                if(0U == (CAN_M_CAN_TXBRP(can_periph) & ((uint32_t)1U << i))) {
                    buffer_index = (uint32_t)i;
                    break;
                }
            }
        }
        if(((uint32_t)i == dedicated_buffer_size) && (0U != (txfqs_reg & CAN_M_CAN_TXFQS_TFQF))) {
            /* Tx buffer is full */
            buffer_index = 0xFFU;
        } else {
            if(((uint32_t)i == dedicated_buffer_size) && (0U == (txfqs_reg & CAN_M_CAN_TXFQS_TFQF))) {
                /* no free dedicated buffer, use queue/FIFO */
                buffer_index = GET_TXFQS_TFQPI(txfqs_reg);
            }
            /* determine which DTM_CAN is selected */
            mem_address = can_dtm_to_can(dtm_canx);
            /* get element size */
            buffer_element_size = GET_TXESC_TBDS(CAN_M_CAN_TXESC(can_periph));
            /* calculate buffer address */
            buffer_addr = (uint32_t *)(mem_address + tx_buffer_start_address + (buffer_index * fifo_element_sz[buffer_element_size]));

            /* prepare T0 word */
            if(CAN_FF_EXTENDED == transmit_message->xtd) {
                /* extended ID */
                t0_word |= (transmit_message->id & CAN_ID_EXT_MASK) | CAN_T0_XTD;
            } else {
                /* standard ID */
                t0_word |= ((transmit_message->id & CAN_ID_STD_MASK) << CAN_ID_STD_OFFSET);
            }
            /* remote frame */
            if(CAN_FT_REMOTE == transmit_message->rtr) {
                t0_word |= CAN_T0_RTR;
            }
            /* error state indicator */
            if(1U == transmit_message->esi) {
                t0_word |= CAN_T0_ESI;
            }

            /* prepare T1 word */
            dlc = can_dlc_value_compute(transmit_message->data_bytes);
            t1_word |= E1A_DLC(dlc);
            /* FD control */
            if(DISABLE != transmit_message->fdf) {
                t1_word |= CAN_T1_FDF;
                if(DISABLE != transmit_message->brs) {
                    t1_word |= CAN_T1_BRS;
                }
            }
            /* event FIFO control */
            if(CAN_TXEVENT_FIFO_STORE == transmit_message->ev_fifo_control) {
                t1_word |= CAN_T1_EFC;
            }
            /* message marker */
            t1_word |= (((uint32_t)transmit_message->message_marker >> 8U) & 0xFFU) << TX_MM_HIGH_OFFSET;
            t1_word |= (((uint32_t)transmit_message->message_marker & 0xFFU)) << TX_MM_LOW_OFFSET;

            /* write T0 and T1 words to buffer */
            *buffer_addr = t0_word;
            buffer_addr++;
            *buffer_addr = t1_word;
            buffer_addr++;

            /* write data bytes */
            length = fifo_element_sz[buffer_element_size];
            if(transmit_message->data_bytes < length) {
                length = transmit_message->data_bytes;
            }
            can_data_write((uint32_t *)buffer_addr, (uint8_t *)(transmit_message->data), length);
        }
    }
    return (uint8_t)buffer_index;
}

/*!
    \brief      add an transmission request (API_ID(0x0035U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  tx_buffer: tx buffer index
      \arg        0-31
    \param[out] none
    \retval     none
*/
void can_message_transmit_add(can_dtm_canx_enum dtm_canx, uint8_t tx_buffer)
{
    uint32_t can_periph = (uint32_t)dtm_canx;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(tx_buffer > 31U) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0035U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* add transmission request */
        CAN_M_CAN_TXBAR(can_periph) |= ((uint32_t)1U << tx_buffer);
    }
}

/*!
    \brief      cancel an transmission request (API_ID(0x0036U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  tx_buffer: tx buffer index
      \arg        0-31
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_message_transmit_cancel(can_dtm_canx_enum dtm_canx, uint8_t tx_buffer)
{
    uint32_t timeout = CAN_TIMEOUT_COUNT;
    ErrStatus ret = SUCCESS;
    uint32_t can_periph = (uint32_t)dtm_canx;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(tx_buffer > 31U) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0036U), ERR_PARAM_OUT_OF_RANGE);
        ret = ERROR;
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* request cancellation */
        CAN_M_CAN_TXBCR(can_periph) |= ((uint32_t)1U << tx_buffer);

        /* wait for cancellation to complete */
        while(((CAN_M_CAN_TXBCF(can_periph) & ((uint32_t)1U << tx_buffer)) == 0U) && (timeout > 0U)) {
            timeout--;
        }

        if((CAN_M_CAN_TXBCF(can_periph) & ((uint32_t)1U << tx_buffer)) == 0U) {
            /* cancellation failed */
            ret = ERROR;
        }
    }
    return ret;
}

/*!
    \brief      get an transmission status (API_ID(0x0037U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  tx_buffer: tx buffer index
      \arg        0-31
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_message_transmit_status_get(can_dtm_canx_enum dtm_canx, uint8_t tx_buffer)
{
    FlagStatus ret = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(tx_buffer > 31U) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0037U), ERR_PARAM_OUT_OF_RANGE);
        ret = RESET;
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* transmission occurred */
        if(0U != (CAN_M_CAN_TXBTO((uint32_t)dtm_canx) & ((uint32_t)1U << tx_buffer))) {
            ret = SET;
        }
    }
    return ret;
}

/*!
    \brief      get an transmission pending status (API_ID(0x0038U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  tx_buffer: tx buffer index
      \arg        0-31
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_message_transmit_pending_status_get(can_dtm_canx_enum dtm_canx, uint8_t tx_buffer)
{
    FlagStatus ret = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(tx_buffer > 31U) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0038U), ERR_PARAM_OUT_OF_RANGE);
        ret = RESET;
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* transmission request pending */
        if(0U != (CAN_M_CAN_TXBRP((uint32_t)dtm_canx) & ((uint32_t)1U << tx_buffer))) {
            ret = SET;
        }
    }
    return ret;
}

/*!
    \brief      pack CAN transmission message for DMU Tx transmission (API_ID(0x0039U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  transmit_message: CAN transmit message struct
                  id: 0~0x3FF or 0~0x1FFFFFFF
                  rtr: CAN_FT_DATA, CAN_FT_REMOTE
                  xtd: CAN_FF_STANDARD, CAN_FF_EXTENDED
                  esi: 0, 1
                  brs: ENABLE, DISABLE
                  fdf: ENABLE, DISABLE
                  message_marker: 0~0xFFFF
                  ev_fifo_control: CAN_TXEVENT_FIFO_STORE, CAN_TXEVENT_FIFO_DISABLE
                  data: transmit data
                  data_bytes: 0~64
    \param[in]  array_size: array size of dmu_tx[]
    \param[out] dmu_tx: pointer to the array for transmission
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus can_dmu_message_transmit_prepare(can_dtm_canx_enum dtm_canx, can_transmit_message_struct *transmit_message, uint32_t dmu_tx[],
        uint32_t array_size)
{
    uint32_t *buffer_addr = dmu_tx;
    uint32_t t0_word = 0U;
    uint32_t t1_word = 0U;
    uint32_t dlc;
    uint32_t buffer_element_size, length;
    uint32_t can_periph = (uint32_t)dtm_canx;
    ErrStatus ret;

    /* get element size */
    buffer_element_size = GET_TXESC_TBDS(CAN_M_CAN_TXESC(can_periph));
    length = fifo_element_sz[buffer_element_size];
#ifdef FW_DEBUG_ERR_REPORT
    ret = ERROR;
    /* check parameter */
    if(NULL == transmit_message) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0039U), ERR_PARAM_POINTER);
    } else if((array_size * 4U) < length) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0039U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* prepare T0 word */
        if(CAN_FF_EXTENDED == transmit_message->xtd) {
            /* extended ID */
            t0_word |= (transmit_message->id & CAN_ID_EXT_MASK) | CAN_T0_XTD;
        } else {
            /* standard ID */
            t0_word |= ((transmit_message->id & CAN_ID_STD_MASK) << CAN_ID_STD_OFFSET);
        }
        /* remote frame */
        if(CAN_FT_REMOTE == transmit_message->rtr) {
            t0_word |= CAN_T0_RTR;
        }
        /* error state indicator */
        if(1U == transmit_message->esi) {
            t0_word |= CAN_T0_ESI;
        }

        /* prepare T1 word */
        dlc = can_dlc_value_compute(transmit_message->data_bytes);
        t1_word |= E1A_DLC(dlc);
        /* FD control */
        if(DISABLE != transmit_message->fdf) {
            t1_word |= CAN_T1_FDF;
            if(DISABLE != transmit_message->brs) {
                t1_word |= CAN_T1_BRS;
            }
        }
        /* event FIFO control */
        if(CAN_TXEVENT_FIFO_STORE == transmit_message->ev_fifo_control) {
            t1_word |= CAN_T1_EFC;
        }
        /* message marker */
        t1_word |= (((uint32_t)transmit_message->message_marker >> 8U) & 0xFFU) << TX_MM_HIGH_OFFSET;
        t1_word |= (((uint32_t)transmit_message->message_marker & 0xFFU)) << TX_MM_LOW_OFFSET;

        /* write T0 and T1 words to buffer */
        *buffer_addr = t0_word;
        buffer_addr++;
        *buffer_addr = t1_word;
        buffer_addr++;

        /* write data bytes */
        if(transmit_message->data_bytes < length) {
            length = transmit_message->data_bytes;
        }
        can_data_write((uint32_t *)buffer_addr, (uint8_t *)(transmit_message->data), length);
        ret = SUCCESS;
    }
    return ret;
}

/*!
    \brief      release Rx buffer (API_ID(0x003AU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  buffer_index: buffer index
      \arg        0-63
    \param[out] none
    \retval     none
*/
void can_rx_buffer_release(can_dtm_canx_enum dtm_canx, uint8_t buffer_index)
{
    /* check input parameters */
    if(buffer_index > 63U) {
        return;
    }

    /* release Rx buffer by clearing New Data flag */
    if(buffer_index < 32U) {
        CAN_M_CAN_NDAT1((uint32_t)dtm_canx) = ((uint32_t)1U << buffer_index);
    } else {
        CAN_M_CAN_NDAT2((uint32_t)dtm_canx) = ((uint32_t)1U << (buffer_index - 32U));
    }
}

/*!
    \brief      get CAN receive message (API_ID(0x003BU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  storage_type: where the message is stored
                only one parameter can be selected which is shown as below:
      \arg        CAN_RXFIFO0: Rx FIFO 0
      \arg        CAN_RXFIFO1: Rx FIFO 1
      \arg        CAN_RXBUFFER: Rx buffer
    \param[out] receive_message: receive message pointer
    \retval     none
*/
void can_message_receive(can_dtm_canx_enum dtm_canx, can_storage_type_enum storage_type, can_receive_message_struct *receive_message)
{
    uint32_t rx_buffer_start_address;
    uint32_t element_size;
    uint32_t buffer_addr = 0U;
    uint32_t i, j;
    uint32_t index = 0U;
    uint32_t fill_level = 0U;
    uint32_t mem_address;
    can_receive_message_struct temp_message;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* get FIFO/buffer fill level */
    switch(storage_type) {
    case CAN_RXFIFO0:
        fill_level = CAN_M_CAN_RXF0S(can_periph) & CAN_M_CAN_RXFXS_FFL;
        break;
    case CAN_RXFIFO1:
        fill_level = CAN_M_CAN_RXF1S(can_periph) & CAN_M_CAN_RXFXS_FFL;
        break;
    case CAN_RXBUFFER:
        fill_level = CAN_M_CAN_NDAT1(can_periph);
        fill_level |= CAN_M_CAN_NDAT2(can_periph);
        break;
    default:
        break;
    }

    /* check input parameters */
    if((NULL != receive_message) && (0U != fill_level)) {
        /* determine which DTM_CAN is selected */
        mem_address = can_dtm_to_can(dtm_canx);
        /* get buffer address based on storage type */
        switch(storage_type) {
        case CAN_RXFIFO0:
            rx_buffer_start_address = GET_RXFXC_FSA(CAN_M_CAN_RXF0C(can_periph)) * 4U;
            element_size = GET_RXESC_F0DS(CAN_M_CAN_RXESC(can_periph));
            index = GET_RXFXS_FXGI(CAN_M_CAN_RXF0S(can_periph));
            buffer_addr = mem_address + rx_buffer_start_address + (index * fifo_element_sz[element_size]);
            break;
        case CAN_RXFIFO1:
            rx_buffer_start_address = GET_RXFXC_FSA(CAN_M_CAN_RXF1C(can_periph)) * 4U;
            element_size = GET_RXESC_F1DS(CAN_M_CAN_RXESC(can_periph));
            index = GET_RXFXS_FXGI(CAN_M_CAN_RXF1S(can_periph));
            buffer_addr = mem_address + rx_buffer_start_address + (index * fifo_element_sz[element_size]);
            break;
        case CAN_RXBUFFER:
            rx_buffer_start_address = GET_RXBC_RBSA(CAN_M_CAN_RXBC(can_periph)) * 4U;
            element_size = GET_RXESC_RBDS(CAN_M_CAN_RXESC(can_periph));
            for(i = 0U; i < 32U; i++) {
                /* check if buffer is updated */
                if(0U != (CAN_M_CAN_NDAT1(can_periph) & ((uint32_t)1U << i))) {
                    index = i;
                    break;
                }
            }
            if(32U == i) {
                for(j = 0U; j < 32U; j++) {
                    /* check if buffer is updated */
                    if(0U != (CAN_M_CAN_NDAT2(can_periph) & ((uint32_t)1U << j))) {
                        index = j + 32U;
                        break;
                    }
                }
            }
            buffer_addr = mem_address + rx_buffer_start_address + (index * fifo_element_sz[element_size]);
            break;
        default:
            break;
        }

        can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &temp_message);
        /* receive message from the calculated address */
        temp_message = can_receive_by_addr(buffer_addr);
        /* copy received message to output structure */
        *receive_message = temp_message;

        /* acknowledge FIFO or release Rx buffer */
        switch(storage_type) {
        case CAN_RXFIFO0:
            CAN_M_CAN_RXF0A(can_periph) = index;
            break;
        case CAN_RXFIFO1:
            CAN_M_CAN_RXF1A(can_periph) = index;
            break;
        case CAN_RXBUFFER:
            /* release Rx buffer by clearing new data flag */
            if(index < 32U) {
                CAN_M_CAN_NDAT1(can_periph) = ((uint32_t)1U << index);
            } else {
                CAN_M_CAN_NDAT2(can_periph) = ((uint32_t)1U << (index - 32U));
            }
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      get high priority CAN message (API_ID(0x003CU))
    \param[in]  high_message: high priority message state structure
                  storage_addr: 0~0xFFFFFFFF
                  match_filter_addr: 0~0xFFFFFFFF
                  storage_indicator: -1, 0, CAN_MSI_RXFIFO0, CAN_MSI_RXFIFO1
    \param[out] none
    \retval     can_receive_message_struct: received message structure
*/
can_receive_message_struct can_high_priority_message_receive(can_high_prio_message_state_struct high_message)
{
    can_receive_message_struct receive_message;
    uint32_t storage_addr = high_message.storage_addr;;

    /* initialize receive message with zeros */
    can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &receive_message);

    /* check if message is available, and storage address is valid */
    if((((int)CAN_MSI_RXFIFO0 == high_message.storage_indicator) ||
            ((int)CAN_MSI_RXFIFO1 == high_message.storage_indicator)) &&
            (0U != storage_addr)) {
        /* receive message from storage address using the existing function */
        receive_message = can_receive_by_addr(storage_addr);
    }

    return receive_message;
}

/*!
    \brief      get high priority message state (API_ID(0x003DU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     high priority message state
*/
can_high_prio_message_state_struct can_high_priority_message_state_get(can_dtm_canx_enum dtm_canx)
{
    can_high_prio_message_state_struct state;
    uint32_t hpms_reg;
    uint32_t indicator;
    uint32_t mem_address;
    uint32_t ele_size;
    uint32_t can_periph = (uint32_t)dtm_canx;

    /* determine which DTM_CAN is selected */
    mem_address = can_dtm_to_can(dtm_canx);

    /* read high priority message status register */
    hpms_reg = CAN_M_CAN_HPMS(can_periph);

    /* parse status information */
    if(0U != (hpms_reg & CAN_M_CAN_HPMS_FLST)) {
        state.match_filter_addr = mem_address + GET_XIDFC_FLESA(CAN_M_CAN_XIDFC(can_periph)) * 4U + GET_HPMS_FIDX(hpms_reg) * CAN_FLITER_ES_EXT;
    } else {
        state.match_filter_addr = mem_address + GET_SIDFC_FLSSA(CAN_M_CAN_SIDFC(can_periph)) * 4U + GET_HPMS_FIDX(hpms_reg) * CAN_FLITER_ES_STD;
    }

    indicator = GET_HPMS_MSI(hpms_reg);
    if((uint32_t)CAN_MSI_RXFIFO0 == indicator) {
        ele_size = GET_RXESC_F0DS(CAN_M_CAN_RXESC(can_periph));
        state.storage_addr = mem_address + GET_RXFXC_FSA(CAN_M_CAN_RXF0C(can_periph)) * 4U + GET_HPMS_BIDX(hpms_reg) * fifo_element_sz[ele_size];
        state.storage_indicator = (int)CAN_MSI_RXFIFO0;
    } else if((uint32_t)CAN_MSI_RXFIFO1 == indicator) {
        ele_size = GET_RXESC_F1DS(CAN_M_CAN_RXESC(can_periph));
        state.storage_addr = mem_address + GET_RXFXC_FSA(CAN_M_CAN_RXF1C(can_periph)) * 4U + GET_HPMS_BIDX(hpms_reg) * fifo_element_sz[ele_size];
        state.storage_indicator = (int)CAN_MSI_RXFIFO1;
    } else if((uint32_t)CAN_MSI_MESSAGE_LOST == indicator) {
        state.storage_addr = 0U;
        state.storage_indicator = -1;
    } else {
        state.storage_addr = 0U;
        state.storage_indicator = 0;
    }

    return state;
}

/*!
    \brief      get CAN FD protocol status information (API_ID(0x003EU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     can_fd_protocol_status_struct
*/
can_fd_protocol_status_struct can_fd_protocol_state_info_get(can_dtm_canx_enum dtm_canx)
{
    can_fd_protocol_status_struct fd_status;
    uint16_t reg_val;

    /* read PSR register byte 2 */
    reg_val = (uint16_t)CAN_M_CAN_PSR_BYTE2((uint32_t)dtm_canx) << 8U;

    /* get protocol exception event flag */
    if(0U != (reg_val & CAN_M_CAN_PSR_PXE)) {
        fd_status.protocol_exp = SET;
    } else {
        fd_status.protocol_exp = RESET;
    }

    /* get FD message received flag */
    if(0U != (reg_val & CAN_M_CAN_PSR_RFDF)) {
        fd_status.fd_message_received = SET;
    } else {
        fd_status.fd_message_received = RESET;
    }

    /* get BRS flag of last received CAN FD message */
    if(0U != (reg_val & CAN_M_CAN_PSR_RBRS)) {
        fd_status.brs_of_last_rx = SET;
    } else {
        fd_status.brs_of_last_rx = RESET;
    }

    /* get ESI flag of last received CAN FD message */
    if(0U != (reg_val & CAN_M_CAN_PSR_RESI)) {
        fd_status.esi_of_last_rx = SET;
    } else {
        fd_status.esi_of_last_rx = RESET;
    }

    /* get data phase last error code */
    reg_val = (uint16_t)(reg_val & CAN_M_CAN_PSR_DLEC) >> CAN_M_CAN_PSR_DLEC_OFFSET;
    fd_status.data_phase_errcode = (can_error_enum)reg_val;

    return fd_status;
}

/*!
    \brief      get CAN protocol state information (API_ID(0x003FU))
                notice call this function will also reset bit PXE, RFDF, RBRS, RESI bits in CAN_M_CAN_PSR register
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     can_protocol_status_struct
*/
can_protocol_status_struct can_protocol_state_info_get(can_dtm_canx_enum dtm_canx)
{
    can_protocol_status_struct protocol_status;
    uint32_t reg_val, temp;

    /* read PSR register */
    reg_val = CAN_M_CAN_PSR((uint32_t)dtm_canx);

    /* get bus_off status */
    if(0U != (reg_val & CAN_M_CAN_PSR_BO)) {
        protocol_status.bus_off = SET;
    } else {
        protocol_status.bus_off = RESET;
    }

    /* get warning status */
    if(0U != (reg_val & CAN_M_CAN_PSR_EW)) {
        protocol_status.error_warning = SET;
    } else {
        protocol_status.error_warning = RESET;
    }

    /* get error passive state */
    if(0U != (reg_val & CAN_M_CAN_PSR_EP)) {
        protocol_status.error_passive = SET;
    } else {
        protocol_status.error_passive = RESET;
    }

    /* get CAN communication state */
    temp = (reg_val & CAN_M_CAN_PSR_ACT) >> CAN_M_CAN_PSR_ACT_OFFSET;
    protocol_status.node = (can_activity_enum)temp;

    /* get last error code */
    temp = reg_val & CAN_M_CAN_PSR_LEC;
    protocol_status.errcode = (can_error_enum)temp;

    return protocol_status;
}

/*!
    \brief      get CAN error counter (API_ID(0x0040U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     can_error_cnt_struct
*/
can_error_cnt_struct can_communication_error_counter_get(can_dtm_canx_enum dtm_canx)
{
    uint32_t ecr_reg;
    can_error_cnt_struct error_counter;

    /* get error counter register */
    ecr_reg = CAN_M_CAN_ECR((uint32_t)dtm_canx);

    /* extract RX and TX error counter values */
    error_counter.rx_err_cnt = (uint8_t)GET_ECR_REC(ecr_reg);
    error_counter.tx_err_cnt = (uint8_t)GET_ECR_TEC(ecr_reg);
    error_counter.err_logging = (uint8_t)GET_ECR_CEL(ecr_reg);
    if(0U != (ecr_reg & CAN_M_CAN_ECR_RP)) {
        error_counter.rx_err_passive = SET;
    } else {
        error_counter.rx_err_passive = RESET;
    }

    return error_counter;
}

/*!
    \brief      get all DMU queueing counters (API_ID(0x0041U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     can_dmu_queue_cnt_struct
*/
can_dmu_queue_cnt_struct can_dmu_queue_counter_get(can_dtm_canx_enum dtm_canx)
{
    uint32_t dmuqc_reg;
    can_dmu_queue_cnt_struct queue_counter;

    /* get DMU queue counter register */
    dmuqc_reg = CAN_DMU_DMUQC((uint32_t)dtm_canx);

    /* extract counter values */
    queue_counter.tx_enqueue_cnt = (uint8_t)GET_DMUQC_TXEEC(dmuqc_reg);
    queue_counter.rx0_dequeue_cnt = (uint8_t)GET_DMUQC_RX0EDC(dmuqc_reg);
    queue_counter.rx1_dequeue_cnt = (uint8_t)GET_DMUQC_RX1EDC(dmuqc_reg);
    queue_counter.tx_event_dequeue_cnt = (uint8_t)GET_DMUQC_TXEEDC(dmuqc_reg);

    return queue_counter;
}

/*!
    \brief      reset all DMU counters (API_ID(0x0042U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     none
*/
void can_dmu_counter_reset(can_dtm_canx_enum dtm_canx)
{
    /* write any value to reset the counters */
    CAN_DMU_DMUQC((uint32_t)dtm_canx) = 0xFFFFFFFFU;
}

/*!
    \brief      get DMU internal finite state machine (API_ID(0x0043U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     can_dmu_internal_struct
*/
can_dmu_internal_struct can_dmu_internal_fsm_get(can_dtm_canx_enum dtm_canx)
{
    can_dmu_internal_struct dmu_internal;
    uint32_t reg_val;

    /* get DMU interface register value */
    reg_val = CAN_DMU_DMUI((uint32_t)dtm_canx);
    dmu_internal.txr = reg_val & CAN_DMU_DMUI_TXR;
    dmu_internal.rx0r = (reg_val & CAN_DMU_DMUI_RX0R) >> CAN_DMUI_RX0R_OFFSET;
    dmu_internal.rx1r = (reg_val & CAN_DMU_DMUI_RX1R) >> CAN_DMUI_RX1R_OFFSET;
    dmu_internal.txer = (reg_val & CAN_DMU_DMUI_TXER) >> CAN_DMUI_TXER_OFFSET;
    dmu_internal.tx_fq_put_index_pre = (reg_val & CAN_DMU_DMUI_TFQPIP) >> CAN_DMUI_TFQPIP_OFFSET;
    dmu_internal.dmu_en = (reg_val & CAN_DMU_DMUI_ENA) >> CAN_DMUI_ENA_OFFSET;
    dmu_internal.dmu_elem_handler_state = (reg_val & CAN_DMU_DMUI_EHS) >> CAN_DMUI_EHS_OFFSET;
    dmu_internal.tx_serve = (reg_val & CAN_DMU_DMUI_TX) >> CAN_DMUI_TX_OFFSET;
    dmu_internal.rx0_serve = (reg_val & CAN_DMU_DMUI_RX0) >> CAN_DMUI_RX0_OFFSET;
    dmu_internal.rx1_serve = (reg_val & CAN_DMU_DMUI_RX1) >> CAN_DMUI_RX1_OFFSET;
    dmu_internal.txe_serve = (reg_val & CAN_DMU_DMUI_TXE) >> CAN_DMUI_TXE_OFFSET;

    return dmu_internal;
}

/*!
    \brief      configure CAN interrupt line (API_ID(0x0044U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  line_number: interrupt line number
                only one parameter can be selected which is shown as below:
      \arg        CAN_INTR_LINE0: interrupt line 0
      \arg        CAN_INTR_LINE1: interrupt line 1
    \param[in]  interrupt: interrupt sources
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_RFIFO0_NEW: Rx FIFO 0 new message interrupt
      \arg        CAN_INT_RFIFO0_WM: Rx FIFO 0 watermark reached interrupt
      \arg        CAN_INT_RFIFO0_FULL: Rx FIFO 0 full interrupt
      \arg        CAN_INT_RFIFO0_MESLOST: Rx FIFO 0 message lost interrupt
      \arg        CAN_INT_RFIFO1_NEW: Rx FIFO 1 new message interrupt
      \arg        CAN_INT_RFIFO1_WM: Rx FIFO 1 watermark reached interrupt
      \arg        CAN_INT_RFIFO1_FULL: Rx FIFO 1 full interrupt
      \arg        CAN_INT_RFIFO1_MESLOST: Rx FIFO 1 message lost interrupt
      \arg        CAN_INT_HIGH_PRI_MES: high priority message interrupt
      \arg        CAN_INT_TX_COMPLETE: transmission completed interrupt
      \arg        CAN_INT_TX_CANCELLED: transmission cancellation finished interrupt
      \arg        CAN_INT_TXFIFO_EMPTY: Tx FIFO empty interrupt
      \arg        CAN_INT_TXEVFIFO_NEW: Tx event FIFO new entry interrupt
      \arg        CAN_INT_TXEVFIFO_WM: Tx event FIFO watermark reached interrupt
      \arg        CAN_INT_TXEVFIFO_FULL: Tx event FIFO full interrupt
      \arg        CAN_INT_TXEVFIFO_ELELOST: Tx event FIFO element lost interrupt
      \arg        CAN_INT_TIMESTAMP_WRAP: timestamp wraparound interrupt
      \arg        CAN_INT_RAM_ACCESS_FAIL: message RAM access failure interrupt
      \arg        CAN_INT_TIMEOUT: timeout occurred interrupt
      \arg        CAN_INT_RXBUFFER_NEW: message stored to dedicated Rx buffer interrupt
      \arg        CAN_INT_ERRLOG_OVERFLOW: error logging overflow interrupt
      \arg        CAN_INT_ERR_PASSIVE_CHANGE: error passive interrupt
      \arg        CAN_INT_WARNING_CHANGE: warning status interrupt
      \arg        CAN_INT_BUSOFF_CHANGE: bus_off status interrupt
      \arg        CAN_INT_WATCHDOG: watchdog interrupt
      \arg        CAN_INT_PROT_ERR_ARBITRATION: protocol error in arbitration phase interrupt
      \arg        CAN_INT_PROT_ERR_DATA: protocol error in data phase interrupt
    \param[out] none
    \retval     none
*/
void can_mcan_interrupt_line_config(can_dtm_canx_enum dtm_canx, uint8_t line_number, can_dtmcan_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    uint32_t reg_offset = (uint32_t)interrupt >> 6U;

    /* check parameter */
    if(IE_REG_OFFSET != reg_offset) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0044U), ERR_PARAM_INVALID);
    } else if(line_number > CAN_INTR_LINE1) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x0044U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the interrupt line */
        if(CAN_INTR_LINE0 == line_number) {
            /* assign to line 0 */
            CAN_M_CAN_ILS((uint32_t)dtm_canx) &= ~(uint32_t)interrupt;
        } else {
            /* assign to line 1 */
            CAN_M_CAN_ILS((uint32_t)dtm_canx) |= (uint32_t)interrupt;
        }
    }
}

/*!
    \brief      enable CAN interrupt line (API_ID(0x0045U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  line_number: CAN interrupt line number
                only one parameter can be selected which is shown as below:
      \arg        CAN_INTR_LINE0: CAN interrupt line 0
      \arg        CAN_INTR_LINE1: CAN interrupt line 1
    \param[out] none
    \retval     none
*/
void can_mcan_interrupt_line_enable(can_dtm_canx_enum dtm_canx, uint8_t line_number)
{
    /* check parameter */
    if(CAN_INTR_LINE0 == line_number) {
        /* enable interrupt line 0 */
        CAN_M_CAN_ILE((uint32_t)dtm_canx) |= CAN_M_CAN_ILE_EINT0;
    } else if(CAN_INTR_LINE1 == line_number) {
        /* enable interrupt line 1 */
        CAN_M_CAN_ILE((uint32_t)dtm_canx) |= CAN_M_CAN_ILE_EINT1;
    } else {
        /* parameter error, no operation */
    }
}

/*!
    \brief      disable CAN interrupt line (API_ID(0x0046U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  line_number: CAN interrupt line number
                only one parameter can be selected which is shown as below:
      \arg        CAN_INTR_LINE0: CAN interrupt line 0
      \arg        CAN_INTR_LINE1: CAN interrupt line 1
    \param[out] none
    \retval     none
*/
void can_mcan_interrupt_line_disable(can_dtm_canx_enum dtm_canx, uint8_t line_number)
{
    /* check parameter */
    if(CAN_INTR_LINE0 == line_number) {
        /* disable interrupt line 0 */
        CAN_M_CAN_ILE((uint32_t)dtm_canx) &= ~CAN_M_CAN_ILE_EINT0;
    } else if(CAN_INTR_LINE1 == line_number) {
        /* disable interrupt line 1 */
        CAN_M_CAN_ILE((uint32_t)dtm_canx) &= ~CAN_M_CAN_ILE_EINT1;
    } else {
        /* parameter error, no operation */
    }
}

/*!
    \brief      get CAN memory error flag (API_ID(0x0047U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  flag: memory error flags
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_NCE_EAE: noncorrectable ECC after EDC error flag
      \arg        CAN_FLAG_NCE_AEDC: noncorrectable address EDC error flag
      \arg        CAN_FLAG_NCDE: noncorrectable double bit error flag
      \arg        CAN_FLAG_BUFOV: correctable error record buffer overflow flag
      \arg        CAN_FLAG_CEOV: correctable error overflow flag
      \arg        CAN_FLAG_NCEOV: noncorrectable error overflow flag
      \arg        CAN_FLAG_CE: correctable error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_memerr_flag_get(can_dtm_canx_enum dtm_canx, can_memerr_flag_enum flag)
{
    FlagStatus ret = RESET;
    uint32_t can_periph;

    can_periph = can_dtm_to_can(dtm_canx);

    /* check the memory error flag */
    if(0U != (CAN_MERRSTAT(can_periph) & (uint32_t)flag)) {
        ret = SET;
    }
    return ret;
}

/*!
    \brief      clear CAN memory error flag (API_ID(0x0048U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  flag: memory error flags
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_NCE_EAE: noncorrectable ECC after EDC error flag
      \arg        CAN_FLAG_NCE_AEDC: noncorrectable address EDC error flag
      \arg        CAN_FLAG_NCDE: noncorrectable double bit error flag
      \arg        CAN_FLAG_BUFOV: correctable error record buffer overflow flag
      \arg        CAN_FLAG_CEOV: correctable error overflow flag
      \arg        CAN_FLAG_NCEOV: noncorrectable error overflow flag
      \arg        CAN_FLAG_CE: correctable error flag
    \param[out] none
    \retval     none
*/
void can_memerr_flag_clear(can_dtm_canx_enum dtm_canx, can_memerr_flag_enum flag)
{
    uint32_t can_periph;

    can_periph = can_dtm_to_can(dtm_canx);
    /* clear the memory error flag */
    CAN_MERRSTAT(can_periph) = (uint32_t)flag;
}

/*!
    \brief      enable or disable memory ecc interrupt (API_ID(0x0049U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  interrupt: memory error interrupts
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_CE: correctable error interrupt
      \arg        CAN_INT_NCE: noncorrectable error interrupt
    \param[out] none
    \retval     none
*/
void can_memerr_interrupt_enable(can_dtm_canx_enum dtm_canx, can_memerr_interrupt_enum interrupt)
{
    uint32_t can_periph;

    can_periph = can_dtm_to_can(dtm_canx);

    /* enable CAN_MERRCTL register write */
    CAN_CTL(can_periph) |= CAN_CTL_ECRWEN;
    /* clear RWDIS bit */
    CAN_MERRCTL(can_periph) &= ~CAN_MERRCTL_RWDIS;

    /* enable the selected interrupt */
    CAN_MERRCTL(can_periph) |= (uint32_t)interrupt;
}

/*!
    \brief      disable CAN interrupt (API_ID(0x004AU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  interrupt: memory error interrupts
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_CE: correctable error interrupt
      \arg        CAN_INT_NCE: noncorrectable error interrupt
    \param[out] none
    \retval     none
*/
void can_memerr_interrupt_disable(can_dtm_canx_enum dtm_canx, can_memerr_interrupt_enum interrupt)
{
    uint32_t can_periph;

    can_periph = can_dtm_to_can(dtm_canx);

    /* enable CAN_MERRCTL register write */
    CAN_CTL(can_periph) |= CAN_CTL_ECRWEN;
    /* clear RWDIS bit */
    CAN_MERRCTL(can_periph) &= ~CAN_MERRCTL_RWDIS;

    /* disable the selected interrupt */
    CAN_MERRCTL(can_periph) &= ~(uint32_t)interrupt;
}

/*!
    \brief      get CAN interrupt flag (API_ID(0x004BU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  int_flag: memory error interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_FLAG_CE: correctable error interrupt flag
      \arg        CAN_INT_FLAG_NCE: noncorrectable error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_memerr_interrupt_flag_get(can_dtm_canx_enum dtm_canx, can_memerr_interrupt_flag_enum int_flag)
{
    uint32_t val;
    FlagStatus ret = RESET;
    uint32_t can_periph, merrctl;

    can_periph = can_dtm_to_can(dtm_canx);

    /* get the interrupt flag */
    val = CAN_MERRSTAT(can_periph) & (uint32_t)int_flag;
    merrctl = CAN_MERRCTL(can_periph);

    /* check if interrupt is enabled for the flag */
    if(CAN_INT_FLAG_CE == int_flag) {
        if((0U != val) && (0U != (merrctl & (uint32_t)CAN_INT_CE))) {
            ret = SET;
        }
    } else {
        /* for CAN_INT_FLAG_NCE */
        if((0U != val) && (0U != (merrctl & (uint32_t)CAN_INT_NCE))) {
            ret = SET;
        }
    }

    return ret;
}

/*!
    \brief      clear CAN interrupt flag (API_ID(0x004CU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  int_flag: memory error interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_FLAG_CE: correctable error interrupt flag
      \arg        CAN_INT_FLAG_NCE: noncorrectable error interrupt flag
    \param[out] none
    \retval     none
*/
void can_memerr_interrupt_flag_clear(can_dtm_canx_enum dtm_canx, can_memerr_interrupt_flag_enum int_flag)
{
    uint32_t can_periph;

    can_periph = can_dtm_to_can(dtm_canx);
    /* clear the interrupt flag */
    CAN_MERRSTAT(can_periph) = (uint32_t)int_flag;
}

/*!
    \brief      get CAN flag (API_ID(0x004DU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  flag: CAN flags
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_RFIFO0_NEW: Rx FIFO 0 new message flag
      \arg        CAN_FLAG_RFIFO0_WM: Rx FIFO 0 watermark reached flag
      \arg        CAN_FLAG_RFIFO0_FULL: Rx FIFO 0 full flag
      \arg        CAN_FLAG_RFIFO0_MESLOST: Rx FIFO 0 message lost flag
      \arg        CAN_FLAG_RFIFO1_NEW: Rx FIFO 1 new message flag
      \arg        CAN_FLAG_RFIFO1_WM: Rx FIFO 1 watermark reached flag
      \arg        CAN_FLAG_RFIFO1_FULL: Rx FIFO 1 full flag
      \arg        CAN_FLAG_RFIFO1_MESLOST: Rx FIFO 1 message lost flag
      \arg        CAN_FLAG_HIGH_PRI_MES: high priority message flag
      \arg        CAN_FLAG_TX_COMPLETE: transmission completed flag
      \arg        CAN_FLAG_TX_CANCELLED: transmission cancellation finished flag
      \arg        CAN_FLAG_TXFIFO_EMPTY: Tx FIFO empty flag
      \arg        CAN_FLAG_TXEVFIFO_NEW: Tx event FIFO new entry flag
      \arg        CAN_FLAG_TXEVFIFO_WM: Tx event FIFO watermark reached flag
      \arg        CAN_FLAG_TXEVFIFO_FULL: Tx event FIFO full flag
      \arg        CAN_FLAG_TXEVFIFO_ELELOST: Tx event FIFO element lost flag
      \arg        CAN_FLAG_TIMESTAMP_WRAP: timestamp wraparound flag
      \arg        CAN_FLAG_RAM_ACCESS_FAIL: message RAM access failure flag
      \arg        CAN_FLAG_TIMEOUT: timeout occurred flag
      \arg        CAN_FLAG_RXBUFFER_NEW: message stored to dedicated Rx buffer flag
      \arg        CAN_FLAG_ERRLOG_OVERFLOW: error logging overflow flag
      \arg        CAN_FLAG_ERR_PASSIVE_CHANGE: error passive flag
      \arg        CAN_FLAG_WARNING_CHANGE: warning status flag
      \arg        CAN_FLAG_BUSOFF_CHANGE: bus_off status flag
      \arg        CAN_FLAG_WATCHDOG: watchdog flag
      \arg        CAN_FLAG_PROT_ERR_ARBITRATION: protocol error in arbitration phase flag
      \arg        CAN_FLAG_PROT_ERR_DATA: protocol error in data phase flag
      \arg        CAN_FLAG_TXBUF0_COMPLETE: Tx buffer 0 transmission flag
      \arg        CAN_FLAG_TXBUF1_COMPLETE: Tx buffer 1 transmission flag
      \arg        CAN_FLAG_TXBUF2_COMPLETE: Tx buffer 2 transmission flag
      \arg        CAN_FLAG_TXBUF3_COMPLETE: Tx buffer 3 transmission flag
      \arg        CAN_FLAG_TXBUF4_COMPLETE: Tx buffer 4 transmission flag
      \arg        CAN_FLAG_TXBUF5_COMPLETE: Tx buffer 5 transmission flag
      \arg        CAN_FLAG_TXBUF6_COMPLETE: Tx buffer 6 transmission flag
      \arg        CAN_FLAG_TXBUF7_COMPLETE: Tx buffer 7 transmission flag
      \arg        CAN_FLAG_TXBUF8_COMPLETE: Tx buffer 8 transmission flag
      \arg        CAN_FLAG_TXBUF9_COMPLETE: Tx buffer 9 transmission flag
      \arg        CAN_FLAG_TXBUF10_COMPLETE: Tx buffer 10 transmission flag
      \arg        CAN_FLAG_TXBUF11_COMPLETE: Tx buffer 11 transmission flag
      \arg        CAN_FLAG_TXBUF12_COMPLETE: Tx buffer 12 transmission flag
      \arg        CAN_FLAG_TXBUF13_COMPLETE: Tx buffer 13 transmission flag
      \arg        CAN_FLAG_TXBUF14_COMPLETE: Tx buffer 14 transmission flag
      \arg        CAN_FLAG_TXBUF15_COMPLETE: Tx buffer 15 transmission flag
      \arg        CAN_FLAG_TXBUF16_COMPLETE: Tx buffer 16 transmission flag
      \arg        CAN_FLAG_TXBUF17_COMPLETE: Tx buffer 17 transmission flag
      \arg        CAN_FLAG_TXBUF18_COMPLETE: Tx buffer 18 transmission flag
      \arg        CAN_FLAG_TXBUF19_COMPLETE: Tx buffer 19 transmission flag
      \arg        CAN_FLAG_TXBUF20_COMPLETE: Tx buffer 20 transmission flag
      \arg        CAN_FLAG_TXBUF21_COMPLETE: Tx buffer 21 transmission flag
      \arg        CAN_FLAG_TXBUF22_COMPLETE: Tx buffer 22 transmission flag
      \arg        CAN_FLAG_TXBUF23_COMPLETE: Tx buffer 23 transmission flag
      \arg        CAN_FLAG_TXBUF24_COMPLETE: Tx buffer 24 transmission flag
      \arg        CAN_FLAG_TXBUF25_COMPLETE: Tx buffer 25 transmission flag
      \arg        CAN_FLAG_TXBUF26_COMPLETE: Tx buffer 26 transmission flag
      \arg        CAN_FLAG_TXBUF27_COMPLETE: Tx buffer 27 transmission flag
      \arg        CAN_FLAG_TXBUF28_COMPLETE: Tx buffer 28 transmission flag
      \arg        CAN_FLAG_TXBUF29_COMPLETE: Tx buffer 29 transmission flag
      \arg        CAN_FLAG_TXBUF30_COMPLETE: Tx buffer 30 transmission flag
      \arg        CAN_FLAG_TXBUF31_COMPLETE: Tx buffer 31 transmission flag
      \arg        CAN_FLAG_TXBUF0_CANCELLED: Tx buffer 0 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF1_CANCELLED: Tx buffer 1 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF2_CANCELLED: Tx buffer 2 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF3_CANCELLED: Tx buffer 3 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF4_CANCELLED: Tx buffer 4 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF5_CANCELLED: Tx buffer 5 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF6_CANCELLED: Tx buffer 6 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF7_CANCELLED: Tx buffer 7 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF8_CANCELLED: Tx buffer 8 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF9_CANCELLED: Tx buffer 9 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF10_CANCELLED: Tx buffer 10 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF11_CANCELLED: Tx buffer 11 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF12_CANCELLED: Tx buffer 12 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF13_CANCELLED: Tx buffer 13 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF14_CANCELLED: Tx buffer 14 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF15_CANCELLED: Tx buffer 15 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF16_CANCELLED: Tx buffer 16 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF17_CANCELLED: Tx buffer 17 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF18_CANCELLED: Tx buffer 18 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF19_CANCELLED: Tx buffer 19 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF20_CANCELLED: Tx buffer 20 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF21_CANCELLED: Tx buffer 21 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF22_CANCELLED: Tx buffer 22 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF23_CANCELLED: Tx buffer 23 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF24_CANCELLED: Tx buffer 24 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF25_CANCELLED: Tx buffer 25 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF26_CANCELLED: Tx buffer 26 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF27_CANCELLED: Tx buffer 27 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF28_CANCELLED: Tx buffer 28 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF29_CANCELLED: Tx buffer 29 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF30_CANCELLED: Tx buffer 30 transmission cancel finished flag
      \arg        CAN_FLAG_TXBUF31_CANCELLED: Tx buffer 31 transmission cancel finished flag
      \arg        DMU_FLAG_TX_ELE_NOT_STADDR: TX element not start address flag
      \arg        DMU_FLAG_TX_ELE_ILLE_ENQ: TX element illegal enqueueing flag
      \arg        DMU_FLAG_TX_ELE_ILLE_ACCSEQ: TX element illegal access sequence flag
      \arg        DMU_FLAG_TX_ELE_ILLE_DLC: TX element illegal DLC flag
      \arg        DMU_FLAG_TX_ELE_WRITE_AFTTRIG: TX element write after trigger address flag
      \arg        DMU_FLAG_TX_ELE_ILLE_READ: TX element illegal read flag
      \arg        DMU_FLAG_TX_ELE_ENQ: TX element enqueued flag
      \arg        DMU_FLAG_RX0_ELE_NOT_STADDR: RX0 element not start address flag
      \arg        DMU_FLAG_RX0_ELE_ILLE_DEQ: RX0 element illegal dequeueing flag
      \arg        DMU_FLAG_RX0_ELE_ILLE_ACCSEQ: RX0 element illegal access sequence flag
      \arg        DMU_FLAG_RX0_ELE_ILLE_WRITE: RX0 element illegal write flag
      \arg        DMU_FLAG_RX0_ELE_DEQ: RX0 element dequeued flag
      \arg        DMU_FLAG_RX1_ELE_NOT_STADDR: RX1 element not start address flag
      \arg        DMU_FLAG_RX1_ELE_ILLE_DEQ: RX1 element illegal dequeueing flag
      \arg        DMU_FLAG_RX1_ELE_ILLE_ACCSEQ: RX1 element illegal access sequence flag
      \arg        DMU_FLAG_RX1_ELE_ILLE_WRITE: RX1 element illegal write flag
      \arg        DMU_FLAG_RX1_ELE_DEQ: RX1 element dequeued flag
      \arg        DMU_FLAG_TXEV_ELE_NOT_STADDR: TX event element not start address flag
      \arg        DMU_FLAG_TXEV_ELE_ILLE_DEQ: TX event element illegal dequeueing flag
      \arg        DMU_FLAG_TXEV_ELE_ILLE_ACCSEQ: TX event element illegal access sequence flag
      \arg        DMU_FLAG_TXEV_ELE_ILLE_WRITE: TX event element illegal write flag
      \arg        DMU_FLAG_TXEV_ELE_DEQ: TX event element dequeued flag
      \arg        DMU_FLAG_ILLE_ACC_IN_CONFIG: illegal access while in configuration mode flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_flag_get(can_dtm_canx_enum dtm_canx, can_dtmcan_flag_enum flag)
{
    uint32_t val;
    uint32_t reg;
    FlagStatus reval = RESET;

    /* get the flag register */
    reg = CAN_REG_VAL(dtm_canx, flag);

    /* get the flag bit position */
    val = ((uint32_t)1U << (CAN_BIT_POS(flag)));

    /* check the flag */
    if(0U != (reg & val)) {
        reval = SET;
    }

    return reval;
}

/*!
    \brief      clear CAN flag (API_ID(0x004EU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  flag: CAN flags
                only one parameter can be selected which is shown as below:
      \arg        CAN_FLAG_RFIFO0_NEW: Rx FIFO 0 new message flag
      \arg        CAN_FLAG_RFIFO0_WM: Rx FIFO 0 watermark reached flag
      \arg        CAN_FLAG_RFIFO0_FULL: Rx FIFO 0 full flag
      \arg        CAN_FLAG_RFIFO0_MESLOST: Rx FIFO 0 message lost flag
      \arg        CAN_FLAG_RFIFO1_NEW: Rx FIFO 1 new message flag
      \arg        CAN_FLAG_RFIFO1_WM: Rx FIFO 1 watermark reached flag
      \arg        CAN_FLAG_RFIFO1_FULL: Rx FIFO 1 full flag
      \arg        CAN_FLAG_RFIFO1_MESLOST: Rx FIFO 1 message lost flag
      \arg        CAN_FLAG_HIGH_PRI_MES: high priority message flag
      \arg        CAN_FLAG_TX_COMPLETE: transmission completed flag
      \arg        CAN_FLAG_TX_CANCELLED: transmission cancellation finished flag
      \arg        CAN_FLAG_TXFIFO_EMPTY: Tx FIFO empty flag
      \arg        CAN_FLAG_TXEVFIFO_NEW: Tx event FIFO new entry flag
      \arg        CAN_FLAG_TXEVFIFO_WM: Tx event FIFO watermark reached flag
      \arg        CAN_FLAG_TXEVFIFO_FULL: Tx event FIFO full flag
      \arg        CAN_FLAG_TXEVFIFO_ELELOST: Tx event FIFO element lost flag
      \arg        CAN_FLAG_TIMESTAMP_WRAP: timestamp wraparound flag
      \arg        CAN_FLAG_RAM_ACCESS_FAIL: message RAM access failure flag
      \arg        CAN_FLAG_TIMEOUT: timeout occurred flag
      \arg        CAN_FLAG_RXBUFFER_NEW: message stored to dedicated Rx buffer flag
      \arg        CAN_FLAG_ERRLOG_OVERFLOW: error logging overflow flag
      \arg        CAN_FLAG_ERR_PASSIVE_CHANGE: error passive flag
      \arg        CAN_FLAG_WARNING_CHANGE: warning status flag
      \arg        CAN_FLAG_BUSOFF_CHANGE: bus_off status flag
      \arg        CAN_FLAG_WATCHDOG: watchdog flag
      \arg        CAN_FLAG_PROT_ERR_ARBITRATION: protocol error in arbitration phase flag
      \arg        CAN_FLAG_PROT_ERR_DATA: protocol error in data phase flag
      \arg        DMU_FLAG_TX_ELE_NOT_STADDR: TX element not start address flag
      \arg        DMU_FLAG_TX_ELE_ILLE_ENQ: TX element illegal enqueueing flag
      \arg        DMU_FLAG_TX_ELE_ILLE_ACCSEQ: TX element illegal access sequence flag
      \arg        DMU_FLAG_TX_ELE_ILLE_DLC: TX element illegal DLC flag
      \arg        DMU_FLAG_TX_ELE_WRITE_AFTTRIG: TX element write after trigger address flag
      \arg        DMU_FLAG_TX_ELE_ILLE_READ: TX element illegal read flag
      \arg        DMU_FLAG_TX_ELE_ENQ: TX element enqueued flag
      \arg        DMU_FLAG_RX0_ELE_NOT_STADDR: RX0 element not start address flag
      \arg        DMU_FLAG_RX0_ELE_ILLE_DEQ: RX0 element illegal dequeueing flag
      \arg        DMU_FLAG_RX0_ELE_ILLE_ACCSEQ: RX0 element illegal access sequence flag
      \arg        DMU_FLAG_RX0_ELE_ILLE_WRITE: RX0 element illegal write flag
      \arg        DMU_FLAG_RX0_ELE_DEQ: RX0 element dequeued flag
      \arg        DMU_FLAG_RX1_ELE_NOT_STADDR: RX1 element not start address flag
      \arg        DMU_FLAG_RX1_ELE_ILLE_DEQ: RX1 element illegal dequeueing flag
      \arg        DMU_FLAG_RX1_ELE_ILLE_ACCSEQ: RX1 element illegal access sequence flag
      \arg        DMU_FLAG_RX1_ELE_ILLE_WRITE: RX1 element illegal write flag
      \arg        DMU_FLAG_RX1_ELE_DEQ: RX1 element dequeued flag
      \arg        DMU_FLAG_TXEV_ELE_NOT_STADDR: TX event element not start address flag
      \arg        DMU_FLAG_TXEV_ELE_ILLE_DEQ: TX event element illegal dequeueing flag
      \arg        DMU_FLAG_TXEV_ELE_ILLE_ACCSEQ: TX event element illegal access sequence flag
      \arg        DMU_FLAG_TXEV_ELE_ILLE_WRITE: TX event element illegal write flag
      \arg        DMU_FLAG_TXEV_ELE_DEQ: TX event element dequeued flag
      \arg        DMU_FLAG_ILLE_ACC_IN_CONFIG: illegal access while in configuration mode flag
    \param[out] none
    \retval     none
*/
void can_flag_clear(can_dtm_canx_enum dtm_canx, can_dtmcan_flag_enum flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    uint32_t reg_offset = (uint32_t)flag >> 6U;

    /* check parameter */
    if(PSR_REG_OFFSET == reg_offset) {
        fw_debug_report_err(CAN_MODULE_ID, API_ID(0x004EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear the flag */
        CAN_REG_VAL(dtm_canx, flag) = ((uint32_t)1U << (CAN_BIT_POS(flag)));
    }
}

/*!
    \brief      enable CAN interrupt (API_ID(0x004FU))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  interrupt: interrupt sources
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_RFIFO0_NEW: Rx FIFO 0 new message interrupt
      \arg        CAN_INT_RFIFO0_WM: Rx FIFO 0 watermark reached interrupt
      \arg        CAN_INT_RFIFO0_FULL: Rx FIFO 0 full interrupt
      \arg        CAN_INT_RFIFO0_MESLOST: Rx FIFO 0 message lost interrupt
      \arg        CAN_INT_RFIFO1_NEW: Rx FIFO 1 new message interrupt
      \arg        CAN_INT_RFIFO1_WM: Rx FIFO 1 watermark reached interrupt
      \arg        CAN_INT_RFIFO1_FULL: Rx FIFO 1 full interrupt
      \arg        CAN_INT_RFIFO1_MESLOST: Rx FIFO 1 message lost interrupt
      \arg        CAN_INT_HIGH_PRI_MES: high priority message interrupt
      \arg        CAN_INT_TX_COMPLETE: transmission completed interrupt
      \arg        CAN_INT_TX_CANCELLED: transmission cancellation finished interrupt
      \arg        CAN_INT_TXFIFO_EMPTY: Tx FIFO empty interrupt
      \arg        CAN_INT_TXEVFIFO_NEW: Tx event FIFO new entry interrupt
      \arg        CAN_INT_TXEVFIFO_WM: Tx event FIFO watermark reached interrupt
      \arg        CAN_INT_TXEVFIFO_FULL: Tx event FIFO full interrupt
      \arg        CAN_INT_TXEVFIFO_ELELOST: Tx event FIFO element lost interrupt
      \arg        CAN_INT_TIMESTAMP_WRAP: timestamp wraparound interrupt
      \arg        CAN_INT_RAM_ACCESS_FAIL: message RAM access failure interrupt
      \arg        CAN_INT_TIMEOUT: timeout occurred interrupt
      \arg        CAN_INT_RXBUFFER_NEW: message stored to dedicated Rx buffer interrupt
      \arg        CAN_INT_ERRLOG_OVERFLOW: error logging overflow interrupt
      \arg        CAN_INT_ERR_PASSIVE_CHANGE: error passive interrupt
      \arg        CAN_INT_WARNING_CHANGE: warning status interrupt
      \arg        CAN_INT_BUSOFF_CHANGE: bus_off status interrupt
      \arg        CAN_INT_WATCHDOG: watchdog interrupt
      \arg        CAN_INT_PROT_ERR_ARBITRATION: protocol error in arbitration phase interrupt
      \arg        CAN_INT_PROT_ERR_DATA: protocol error in data phase interrupt
      \arg        CAN_INT_TXBUF0_COMPLETE: Tx buffer 0 transmission interrupt
      \arg        CAN_INT_TXBUF1_COMPLETE: Tx buffer 1 transmission interrupt
      \arg        CAN_INT_TXBUF2_COMPLETE: Tx buffer 2 transmission interrupt
      \arg        CAN_INT_TXBUF3_COMPLETE: Tx buffer 3 transmission interrupt
      \arg        CAN_INT_TXBUF4_COMPLETE: Tx buffer 4 transmission interrupt
      \arg        CAN_INT_TXBUF5_COMPLETE: Tx buffer 5 transmission interrupt
      \arg        CAN_INT_TXBUF6_COMPLETE: Tx buffer 6 transmission interrupt
      \arg        CAN_INT_TXBUF7_COMPLETE: Tx buffer 7 transmission interrupt
      \arg        CAN_INT_TXBUF8_COMPLETE: Tx buffer 8 transmission interrupt
      \arg        CAN_INT_TXBUF9_COMPLETE: Tx buffer 9 transmission interrupt
      \arg        CAN_INT_TXBUF10_COMPLETE: Tx buffer 10 transmission interrupt
      \arg        CAN_INT_TXBUF11_COMPLETE: Tx buffer 11 transmission interrupt
      \arg        CAN_INT_TXBUF12_COMPLETE: Tx buffer 12 transmission interrupt
      \arg        CAN_INT_TXBUF13_COMPLETE: Tx buffer 13 transmission interrupt
      \arg        CAN_INT_TXBUF14_COMPLETE: Tx buffer 14 transmission interrupt
      \arg        CAN_INT_TXBUF15_COMPLETE: Tx buffer 15 transmission interrupt
      \arg        CAN_INT_TXBUF16_COMPLETE: Tx buffer 16 transmission interrupt
      \arg        CAN_INT_TXBUF17_COMPLETE: Tx buffer 17 transmission interrupt
      \arg        CAN_INT_TXBUF18_COMPLETE: Tx buffer 18 transmission interrupt
      \arg        CAN_INT_TXBUF19_COMPLETE: Tx buffer 19 transmission interrupt
      \arg        CAN_INT_TXBUF20_COMPLETE: Tx buffer 20 transmission interrupt
      \arg        CAN_INT_TXBUF21_COMPLETE: Tx buffer 21 transmission interrupt
      \arg        CAN_INT_TXBUF22_COMPLETE: Tx buffer 22 transmission interrupt
      \arg        CAN_INT_TXBUF23_COMPLETE: Tx buffer 23 transmission interrupt
      \arg        CAN_INT_TXBUF24_COMPLETE: Tx buffer 24 transmission interrupt
      \arg        CAN_INT_TXBUF25_COMPLETE: Tx buffer 25 transmission interrupt
      \arg        CAN_INT_TXBUF26_COMPLETE: Tx buffer 26 transmission interrupt
      \arg        CAN_INT_TXBUF27_COMPLETE: Tx buffer 27 transmission interrupt
      \arg        CAN_INT_TXBUF28_COMPLETE: Tx buffer 28 transmission interrupt
      \arg        CAN_INT_TXBUF29_COMPLETE: Tx buffer 29 transmission interrupt
      \arg        CAN_INT_TXBUF30_COMPLETE: Tx buffer 30 transmission interrupt
      \arg        CAN_INT_TXBUF31_COMPLETE: Tx buffer 31 transmission interrupt
      \arg        CAN_INT_TXBUF0_CANCELLED: Tx buffer 0 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF1_CANCELLED: Tx buffer 1 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF2_CANCELLED: Tx buffer 2 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF3_CANCELLED: Tx buffer 3 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF4_CANCELLED: Tx buffer 4 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF5_CANCELLED: Tx buffer 5 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF6_CANCELLED: Tx buffer 6 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF7_CANCELLED: Tx buffer 7 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF8_CANCELLED: Tx buffer 8 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF9_CANCELLED: Tx buffer 9 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF10_CANCELLED: Tx buffer 10 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF11_CANCELLED: Tx buffer 11 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF12_CANCELLED: Tx buffer 12 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF13_CANCELLED: Tx buffer 13 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF14_CANCELLED: Tx buffer 14 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF15_CANCELLED: Tx buffer 15 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF16_CANCELLED: Tx buffer 16 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF17_CANCELLED: Tx buffer 17 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF18_CANCELLED: Tx buffer 18 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF19_CANCELLED: Tx buffer 19 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF20_CANCELLED: Tx buffer 20 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF21_CANCELLED: Tx buffer 21 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF22_CANCELLED: Tx buffer 22 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF23_CANCELLED: Tx buffer 23 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF24_CANCELLED: Tx buffer 24 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF25_CANCELLED: Tx buffer 25 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF26_CANCELLED: Tx buffer 26 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF27_CANCELLED: Tx buffer 27 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF28_CANCELLED: Tx buffer 28 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF29_CANCELLED: Tx buffer 29 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF30_CANCELLED: Tx buffer 30 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF31_CANCELLED: Tx buffer 31 transmission cancel finished interrupt
      \arg        DMU_INT_TX_ELE_NOT_STADDR: TX element not start address interrupt
      \arg        DMU_INT_TX_ELE_ILLE_ENQ: TX element illegal enqueueing interrupt
      \arg        DMU_INT_TX_ELE_ILLE_ACCSEQ: TX element illegal access sequence interrupt
      \arg        DMU_INT_TX_ELE_ILLE_DLC: TX element illegal DLC interrupt
      \arg        DMU_INT_TX_ELE_WRITE_AFTTRIG: TX element write after trigger address interrupt
      \arg        DMU_INT_TX_ELE_ILLE_READ: TX element illegal read interrupt
      \arg        DMU_INT_TX_ELE_ENQ: TX element enqueued interrupt
      \arg        DMU_INT_RX0_ELE_NOT_STADDR: RX0 element not start address interrupt
      \arg        DMU_INT_RX0_ELE_ILLE_DEQ: RX0 element illegal dequeueing interrupt
      \arg        DMU_INT_RX0_ELE_ILLE_ACCSEQ: RX0 element illegal access sequence interrupt
      \arg        DMU_INT_RX0_ELE_ILLE_WRITE: RX0 element illegal write interrupt
      \arg        DMU_INT_RX0_ELE_DEQ: RX0 element dequeued interrupt
      \arg        DMU_INT_RX1_ELE_NOT_STADDR: RX1 element not start address interrupt
      \arg        DMU_INT_RX1_ELE_ILLE_DEQ: RX1 element illegal dequeueing interrupt
      \arg        DMU_INT_RX1_ELE_ILLE_ACCSEQ: RX1 element illegal access sequence interrupt
      \arg        DMU_INT_RX1_ELE_ILLE_WRITE: RX1 element illegal write interrupt
      \arg        DMU_INT_RX1_ELE_DEQ: RX1 element dequeued interrupt
      \arg        DMU_INT_TXEV_ELE_NOT_STADDR: TX event element not start address interrupt
      \arg        DMU_INT_TXEV_ELE_ILLE_DEQ: TX event element illegal dequeueing interrupt
      \arg        DMU_INT_TXEV_ELE_ILLE_ACCSEQ: TX event element illegal access sequence interrupt
      \arg        DMU_INT_TXEV_ELE_ILLE_WRITE: TX event element illegal write interrupt
      \arg        DMU_INT_TXEV_ELE_DEQ: TX event element dequeued interrupt
      \arg        DMU_INT_ILLE_ACC_IN_CONFIG: illegal access while in configuration mode interrupt
    \param[out] none
    \retval     none
*/
void can_interrupt_enable(can_dtm_canx_enum dtm_canx, can_dtmcan_interrupt_enum interrupt)
{
    CAN_REG_VAL(dtm_canx, interrupt) |= ((uint32_t)1U << (CAN_BIT_POS(interrupt)));
}

/*!
    \brief      disable CAN interrupt (API_ID(0x0050U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  interrupt: interrupt sources
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_RFIFO0_NEW: Rx FIFO 0 new message interrupt
      \arg        CAN_INT_RFIFO0_WM: Rx FIFO 0 watermark reached interrupt
      \arg        CAN_INT_RFIFO0_FULL: Rx FIFO 0 full interrupt
      \arg        CAN_INT_RFIFO0_MESLOST: Rx FIFO 0 message lost interrupt
      \arg        CAN_INT_RFIFO1_NEW: Rx FIFO 1 new message interrupt
      \arg        CAN_INT_RFIFO1_WM: Rx FIFO 1 watermark reached interrupt
      \arg        CAN_INT_RFIFO1_FULL: Rx FIFO 1 full interrupt
      \arg        CAN_INT_RFIFO1_MESLOST: Rx FIFO 1 message lost interrupt
      \arg        CAN_INT_HIGH_PRI_MES: high priority message interrupt
      \arg        CAN_INT_TX_COMPLETE: transmission completed interrupt
      \arg        CAN_INT_TX_CANCELLED: transmission cancellation finished interrupt
      \arg        CAN_INT_TXFIFO_EMPTY: Tx FIFO empty interrupt
      \arg        CAN_INT_TXEVFIFO_NEW: Tx event FIFO new entry interrupt
      \arg        CAN_INT_TXEVFIFO_WM: Tx event FIFO watermark reached interrupt
      \arg        CAN_INT_TXEVFIFO_FULL: Tx event FIFO full interrupt
      \arg        CAN_INT_TXEVFIFO_ELELOST: Tx event FIFO element lost interrupt
      \arg        CAN_INT_TIMESTAMP_WRAP: timestamp wraparound interrupt
      \arg        CAN_INT_RAM_ACCESS_FAIL: message RAM access failure interrupt
      \arg        CAN_INT_TIMEOUT: timeout occurred interrupt
      \arg        CAN_INT_RXBUFFER_NEW: message stored to dedicated Rx buffer interrupt
      \arg        CAN_INT_ERRLOG_OVERFLOW: error logging overflow interrupt
      \arg        CAN_INT_ERR_PASSIVE_CHANGE: error passive interrupt
      \arg        CAN_INT_WARNING_CHANGE: warning status interrupt
      \arg        CAN_INT_BUSOFF_CHANGE: bus_off status interrupt
      \arg        CAN_INT_WATCHDOG: watchdog interrupt
      \arg        CAN_INT_PROT_ERR_ARBITRATION: protocol error in arbitration phase interrupt
      \arg        CAN_INT_PROT_ERR_DATA: protocol error in data phase interrupt
      \arg        CAN_INT_TXBUF0_COMPLETE: Tx buffer 0 transmission interrupt
      \arg        CAN_INT_TXBUF1_COMPLETE: Tx buffer 1 transmission interrupt
      \arg        CAN_INT_TXBUF2_COMPLETE: Tx buffer 2 transmission interrupt
      \arg        CAN_INT_TXBUF3_COMPLETE: Tx buffer 3 transmission interrupt
      \arg        CAN_INT_TXBUF4_COMPLETE: Tx buffer 4 transmission interrupt
      \arg        CAN_INT_TXBUF5_COMPLETE: Tx buffer 5 transmission interrupt
      \arg        CAN_INT_TXBUF6_COMPLETE: Tx buffer 6 transmission interrupt
      \arg        CAN_INT_TXBUF7_COMPLETE: Tx buffer 7 transmission interrupt
      \arg        CAN_INT_TXBUF8_COMPLETE: Tx buffer 8 transmission interrupt
      \arg        CAN_INT_TXBUF9_COMPLETE: Tx buffer 9 transmission interrupt
      \arg        CAN_INT_TXBUF10_COMPLETE: Tx buffer 10 transmission interrupt
      \arg        CAN_INT_TXBUF11_COMPLETE: Tx buffer 11 transmission interrupt
      \arg        CAN_INT_TXBUF12_COMPLETE: Tx buffer 12 transmission interrupt
      \arg        CAN_INT_TXBUF13_COMPLETE: Tx buffer 13 transmission interrupt
      \arg        CAN_INT_TXBUF14_COMPLETE: Tx buffer 14 transmission interrupt
      \arg        CAN_INT_TXBUF15_COMPLETE: Tx buffer 15 transmission interrupt
      \arg        CAN_INT_TXBUF16_COMPLETE: Tx buffer 16 transmission interrupt
      \arg        CAN_INT_TXBUF17_COMPLETE: Tx buffer 17 transmission interrupt
      \arg        CAN_INT_TXBUF18_COMPLETE: Tx buffer 18 transmission interrupt
      \arg        CAN_INT_TXBUF19_COMPLETE: Tx buffer 19 transmission interrupt
      \arg        CAN_INT_TXBUF20_COMPLETE: Tx buffer 20 transmission interrupt
      \arg        CAN_INT_TXBUF21_COMPLETE: Tx buffer 21 transmission interrupt
      \arg        CAN_INT_TXBUF22_COMPLETE: Tx buffer 22 transmission interrupt
      \arg        CAN_INT_TXBUF23_COMPLETE: Tx buffer 23 transmission interrupt
      \arg        CAN_INT_TXBUF24_COMPLETE: Tx buffer 24 transmission interrupt
      \arg        CAN_INT_TXBUF25_COMPLETE: Tx buffer 25 transmission interrupt
      \arg        CAN_INT_TXBUF26_COMPLETE: Tx buffer 26 transmission interrupt
      \arg        CAN_INT_TXBUF27_COMPLETE: Tx buffer 27 transmission interrupt
      \arg        CAN_INT_TXBUF28_COMPLETE: Tx buffer 28 transmission interrupt
      \arg        CAN_INT_TXBUF29_COMPLETE: Tx buffer 29 transmission interrupt
      \arg        CAN_INT_TXBUF30_COMPLETE: Tx buffer 30 transmission interrupt
      \arg        CAN_INT_TXBUF31_COMPLETE: Tx buffer 31 transmission interrupt
      \arg        CAN_INT_TXBUF0_CANCELLED: Tx buffer 0 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF1_CANCELLED: Tx buffer 1 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF2_CANCELLED: Tx buffer 2 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF3_CANCELLED: Tx buffer 3 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF4_CANCELLED: Tx buffer 4 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF5_CANCELLED: Tx buffer 5 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF6_CANCELLED: Tx buffer 6 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF7_CANCELLED: Tx buffer 7 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF8_CANCELLED: Tx buffer 8 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF9_CANCELLED: Tx buffer 9 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF10_CANCELLED: Tx buffer 10 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF11_CANCELLED: Tx buffer 11 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF12_CANCELLED: Tx buffer 12 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF13_CANCELLED: Tx buffer 13 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF14_CANCELLED: Tx buffer 14 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF15_CANCELLED: Tx buffer 15 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF16_CANCELLED: Tx buffer 16 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF17_CANCELLED: Tx buffer 17 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF18_CANCELLED: Tx buffer 18 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF19_CANCELLED: Tx buffer 19 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF20_CANCELLED: Tx buffer 20 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF21_CANCELLED: Tx buffer 21 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF22_CANCELLED: Tx buffer 22 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF23_CANCELLED: Tx buffer 23 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF24_CANCELLED: Tx buffer 24 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF25_CANCELLED: Tx buffer 25 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF26_CANCELLED: Tx buffer 26 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF27_CANCELLED: Tx buffer 27 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF28_CANCELLED: Tx buffer 28 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF29_CANCELLED: Tx buffer 29 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF30_CANCELLED: Tx buffer 30 transmission cancel finished interrupt
      \arg        CAN_INT_TXBUF31_CANCELLED: Tx buffer 31 transmission cancel finished interrupt
      \arg        DMU_INT_TX_ELE_NOT_STADDR: TX element not start address interrupt
      \arg        DMU_INT_TX_ELE_ILLE_ENQ: TX element illegal enqueueing interrupt
      \arg        DMU_INT_TX_ELE_ILLE_ACCSEQ: TX element illegal access sequence interrupt
      \arg        DMU_INT_TX_ELE_ILLE_DLC: TX element illegal DLC interrupt
      \arg        DMU_INT_TX_ELE_WRITE_AFTTRIG: TX element write after trigger address interrupt
      \arg        DMU_INT_TX_ELE_ILLE_READ: TX element illegal read interrupt
      \arg        DMU_INT_TX_ELE_ENQ: TX element enqueued interrupt
      \arg        DMU_INT_RX0_ELE_NOT_STADDR: RX0 element not start address interrupt
      \arg        DMU_INT_RX0_ELE_ILLE_DEQ: RX0 element illegal dequeueing interrupt
      \arg        DMU_INT_RX0_ELE_ILLE_ACCSEQ: RX0 element illegal access sequence interrupt
      \arg        DMU_INT_RX0_ELE_ILLE_WRITE: RX0 element illegal write interrupt
      \arg        DMU_INT_RX0_ELE_DEQ: RX0 element dequeued interrupt
      \arg        DMU_INT_RX1_ELE_NOT_STADDR: RX1 element not start address interrupt
      \arg        DMU_INT_RX1_ELE_ILLE_DEQ: RX1 element illegal dequeueing interrupt
      \arg        DMU_INT_RX1_ELE_ILLE_ACCSEQ: RX1 element illegal access sequence interrupt
      \arg        DMU_INT_RX1_ELE_ILLE_WRITE: RX1 element illegal write interrupt
      \arg        DMU_INT_RX1_ELE_DEQ: RX1 element dequeued interrupt
      \arg        DMU_INT_TXEV_ELE_NOT_STADDR: TX event element not start address interrupt
      \arg        DMU_INT_TXEV_ELE_ILLE_DEQ: TX event element illegal dequeueing interrupt
      \arg        DMU_INT_TXEV_ELE_ILLE_ACCSEQ: TX event element illegal access sequence interrupt
      \arg        DMU_INT_TXEV_ELE_ILLE_WRITE: TX event element illegal write interrupt
      \arg        DMU_INT_TXEV_ELE_DEQ: TX event element dequeued interrupt
      \arg        DMU_INT_ILLE_ACC_IN_CONFIG: illegal access while in configuration mode interrupt
    \param[out] none
    \retval     none
*/
void can_interrupt_disable(can_dtm_canx_enum dtm_canx, can_dtmcan_interrupt_enum interrupt)
{
    CAN_REG_VAL(dtm_canx, interrupt) &= ~(uint32_t)((uint32_t)1U << (CAN_BIT_POS(interrupt)));
}

/*!
    \brief      get CAN interrupt flag (API_ID(0x0051U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  int_flag: interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_FLAG_RFIFO0_NEW: Rx FIFO 0 new message interrupt flag
      \arg        CAN_INT_FLAG_RFIFO0_WM: Rx FIFO 0 watermark reached interrupt flag
      \arg        CAN_INT_FLAG_RFIFO0_FULL: Rx FIFO 0 full interrupt flag
      \arg        CAN_INT_FLAG_RFIFO0_MESLOST: Rx FIFO 0 message lost interrupt flag
      \arg        CAN_INT_FLAG_RFIFO1_NEW: Rx FIFO 1 new message interrupt flag
      \arg        CAN_INT_FLAG_RFIFO1_WM: Rx FIFO 1 watermark reached interrupt flag
      \arg        CAN_INT_FLAG_RFIFO1_FULL: Rx FIFO 1 full interrupt flag
      \arg        CAN_INT_FLAG_RFIFO1_MESLOST: Rx FIFO 1 message lost interrupt flag
      \arg        CAN_INT_FLAG_HIGH_PRI_MES: high priority message interrupt flag
      \arg        CAN_INT_FLAG_TX_COMPLETE: transmission completed interrupt flag
      \arg        CAN_INT_FLAG_TX_CANCELLED: transmission cancellation finished interrupt flag
      \arg        CAN_INT_FLAG_TXFIFO_EMPTY: Tx FIFO empty interrupt flag
      \arg        CAN_INT_FLAG_TXEVFIFO_NEW: Tx event FIFO new entry interrupt flag
      \arg        CAN_INT_FLAG_TXEVFIFO_WM: Tx event FIFO watermark reached interrupt flag
      \arg        CAN_INT_FLAG_TXEVFIFO_FULL: Tx event FIFO full interrupt flag
      \arg        CAN_INT_FLAG_TXEVFIFO_ELELOST: Tx event FIFO element lost interrupt flag
      \arg        CAN_INT_FLAG_TIMESTAMP_WRAP: timestamp wraparound interrupt flag
      \arg        CAN_INT_FLAG_RAM_ACCESS_FAIL: message RAM access failure interrupt flag
      \arg        CAN_INT_FLAG_TIMEOUT: timeout occurred interrupt flag
      \arg        CAN_INT_FLAG_RXBUFFER_NEW: message stored to dedicated Rx buffer interrupt flag
      \arg        CAN_INT_FLAG_ERRLOG_OVERFLOW: error logging overflow interrupt flag
      \arg        CAN_INT_FLAG_ERR_PASSIVE_CHANGE: error passive interrupt flag
      \arg        CAN_INT_FLAG_WARNING_CHANGE: warning status interrupt flag
      \arg        CAN_INT_FLAG_BUSOFF_CHANGE: bus_off status interrupt flag
      \arg        CAN_INT_FLAG_WATCHDOG: watchdog interrupt flag
      \arg        CAN_INT_FLAG_PROT_ERR_ARBITRATION: protocol error in arbitration phase interrupt flag
      \arg        CAN_INT_FLAG_PROT_ERR_DATA: protocol error in data phase interrupt flag
      \arg        CAN_INT_FLAG_TXBUF0_COMPLETE: Tx buffer 0 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF1_COMPLETE: Tx buffer 1 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF2_COMPLETE: Tx buffer 2 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF3_COMPLETE: Tx buffer 3 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF4_COMPLETE: Tx buffer 4 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF5_COMPLETE: Tx buffer 5 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF6_COMPLETE: Tx buffer 6 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF7_COMPLETE: Tx buffer 7 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF8_COMPLETE: Tx buffer 8 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF9_COMPLETE: Tx buffer 9 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF10_COMPLETE: Tx buffer 10 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF11_COMPLETE: Tx buffer 11 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF12_COMPLETE: Tx buffer 12 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF13_COMPLETE: Tx buffer 13 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF14_COMPLETE: Tx buffer 14 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF15_COMPLETE: Tx buffer 15 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF16_COMPLETE: Tx buffer 16 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF17_COMPLETE: Tx buffer 17 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF18_COMPLETE: Tx buffer 18 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF19_COMPLETE: Tx buffer 19 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF20_COMPLETE: Tx buffer 20 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF21_COMPLETE: Tx buffer 21 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF22_COMPLETE: Tx buffer 22 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF23_COMPLETE: Tx buffer 23 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF24_COMPLETE: Tx buffer 24 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF25_COMPLETE: Tx buffer 25 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF26_COMPLETE: Tx buffer 26 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF27_COMPLETE: Tx buffer 27 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF28_COMPLETE: Tx buffer 28 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF29_COMPLETE: Tx buffer 29 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF30_COMPLETE: Tx buffer 30 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF31_COMPLETE: Tx buffer 31 transmission interrupt flag
      \arg        CAN_INT_FLAG_TXBUF0_CANCELLED: Tx buffer 0 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF1_CANCELLED: Tx buffer 1 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF2_CANCELLED: Tx buffer 2 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF3_CANCELLED: Tx buffer 3 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF4_CANCELLED: Tx buffer 4 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF5_CANCELLED: Tx buffer 5 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF6_CANCELLED: Tx buffer 6 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF7_CANCELLED: Tx buffer 7 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF8_CANCELLED: Tx buffer 8 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF9_CANCELLED: Tx buffer 9 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF10_CANCELLED: Tx buffer 10 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF11_CANCELLED: Tx buffer 11 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF12_CANCELLED: Tx buffer 12 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF13_CANCELLED: Tx buffer 13 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF14_CANCELLED: Tx buffer 14 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF15_CANCELLED: Tx buffer 15 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF16_CANCELLED: Tx buffer 16 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF17_CANCELLED: Tx buffer 17 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF18_CANCELLED: Tx buffer 18 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF19_CANCELLED: Tx buffer 19 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF20_CANCELLED: Tx buffer 20 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF21_CANCELLED: Tx buffer 21 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF22_CANCELLED: Tx buffer 22 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF23_CANCELLED: Tx buffer 23 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF24_CANCELLED: Tx buffer 24 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF25_CANCELLED: Tx buffer 25 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF26_CANCELLED: Tx buffer 26 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF27_CANCELLED: Tx buffer 27 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF28_CANCELLED: Tx buffer 28 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF29_CANCELLED: Tx buffer 29 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF30_CANCELLED: Tx buffer 30 transmission cancel finished interrupt flag
      \arg        CAN_INT_FLAG_TXBUF31_CANCELLED: Tx buffer 31 transmission cancel finished interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_NOT_STADDR: TX element not start address interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ILLE_ENQ: TX element illegal enqueueing interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ILLE_ACCSEQ: TX element illegal access sequence interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ILLE_DLC: TX element illegal DLC interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_WRITE_AFTTRIG: TX element write after trigger address interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ILLE_READ: TX element illegal read interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ENQ: TX element enqueued interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_NOT_STADDR: RX0 element not start address interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_ILLE_DEQ: RX0 element illegal dequeueing interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_ILLE_ACCSEQ: RX0 element illegal access sequence interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_ILLE_WRITE: RX0 element illegal write interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_DEQ: RX0 element dequeued interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_NOT_STADDR: RX1 element not start address interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_ILLE_DEQ: RX1 element illegal dequeueing interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_ILLE_ACCSEQ: RX1 element illegal access sequence interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_ILLE_WRITE: RX1 element illegal write interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_DEQ: RX1 element dequeued interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_NOT_STADDR: TX event element not start address interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_ILLE_DEQ: TX event element illegal dequeueing interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_ILLE_ACCSEQ: TX event element illegal access sequence interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_ILLE_WRITE: TX event element illegal write interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_DEQ: TX event element dequeued interrupt flag
      \arg        DMU_INT_FLAG_ILLE_ACC_IN_CONFIG: illegal access while in configuration mode interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus can_interrupt_flag_get(can_dtm_canx_enum dtm_canx, can_dtmcan_interrupt_flag_enum int_flag)
{
    FlagStatus reval = RESET;
    uint32_t ret1;
    uint32_t ret2;

    /* get the status of interrupt enable bit */
    ret1 = (CAN_REG_VAL(dtm_canx, int_flag) & BIT(CAN_BIT_POS(int_flag)));
    /* get the status of interrupt flag */
    ret2 = (CAN_REG_VAL2(dtm_canx, int_flag) & BIT(CAN_BIT_POS2(int_flag)));

    if((0U != ret1) && (0U != ret2)) {
        reval = SET;
    }

    return reval;
}

/*!
    \brief      clear CAN interrupt flag (API_ID(0x0052U))
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[in]  int_flag: interrupt flags
                only one parameter can be selected which is shown as below:
      \arg        CAN_INT_FLAG_RFIFO0_NEW: Rx FIFO 0 new message interrupt flag
      \arg        CAN_INT_FLAG_RFIFO0_WM: Rx FIFO 0 watermark reached interrupt flag
      \arg        CAN_INT_FLAG_RFIFO0_FULL: Rx FIFO 0 full interrupt flag
      \arg        CAN_INT_FLAG_RFIFO0_MESLOST: Rx FIFO 0 message lost interrupt flag
      \arg        CAN_INT_FLAG_RFIFO1_NEW: Rx FIFO 1 new message interrupt flag
      \arg        CAN_INT_FLAG_RFIFO1_WM: Rx FIFO 1 watermark reached interrupt flag
      \arg        CAN_INT_FLAG_RFIFO1_FULL: Rx FIFO 1 full interrupt flag
      \arg        CAN_INT_FLAG_RFIFO1_MESLOST: Rx FIFO 1 message lost interrupt flag
      \arg        CAN_INT_FLAG_HIGH_PRI_MES: high priority message interrupt flag
      \arg        CAN_INT_FLAG_TX_COMPLETE: transmission completed interrupt flag
      \arg        CAN_INT_FLAG_TX_CANCELLED: transmission cancellation finished interrupt flag
      \arg        CAN_INT_FLAG_TXFIFO_EMPTY: Tx FIFO empty interrupt flag
      \arg        CAN_INT_FLAG_TXEVFIFO_NEW: Tx event FIFO new entry interrupt flag
      \arg        CAN_INT_FLAG_TXEVFIFO_WM: Tx event FIFO watermark reached interrupt flag
      \arg        CAN_INT_FLAG_TXEVFIFO_FULL: Tx event FIFO full interrupt flag
      \arg        CAN_INT_FLAG_TXEVFIFO_ELELOST: Tx event FIFO element lost interrupt flag
      \arg        CAN_INT_FLAG_TIMESTAMP_WRAP: timestamp wraparound interrupt flag
      \arg        CAN_INT_FLAG_RAM_ACCESS_FAIL: message RAM access failure interrupt flag
      \arg        CAN_INT_FLAG_TIMEOUT: timeout occurred interrupt flag
      \arg        CAN_INT_FLAG_RXBUFFER_NEW: message stored to dedicated Rx buffer interrupt flag
      \arg        CAN_INT_FLAG_ERRLOG_OVERFLOW: error logging overflow interrupt flag
      \arg        CAN_INT_FLAG_ERR_PASSIVE_CHANGE: error passive interrupt flag
      \arg        CAN_INT_FLAG_WARNING_CHANGE: warning status interrupt flag
      \arg        CAN_INT_FLAG_BUSOFF_CHANGE: bus_off status interrupt flag
      \arg        CAN_INT_FLAG_WATCHDOG: watchdog interrupt flag
      \arg        CAN_INT_FLAG_PROT_ERR_ARBITRATION: protocol error in arbitration phase interrupt flag
      \arg        CAN_INT_FLAG_PROT_ERR_DATA: protocol error in data phase interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_NOT_STADDR: TX element not start address interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ILLE_ENQ: TX element illegal enqueueing interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ILLE_ACCSEQ: TX element illegal access sequence interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ILLE_DLC: TX element illegal DLC interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_WRITE_AFTTRIG: TX element write after trigger address interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ILLE_READ: TX element illegal read interrupt flag
      \arg        DMU_INT_FLAG_TX_ELE_ENQ: TX element enqueued interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_NOT_STADDR: RX0 element not start address interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_ILLE_DEQ: RX0 element illegal dequeueing interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_ILLE_ACCSEQ: RX0 element illegal access sequence interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_ILLE_WRITE: RX0 element illegal write interrupt flag
      \arg        DMU_INT_FLAG_RX0_ELE_DEQ: RX0 element dequeued interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_NOT_STADDR: RX1 element not start address interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_ILLE_DEQ: RX1 element illegal dequeueing interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_ILLE_ACCSEQ: RX1 element illegal access sequence interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_ILLE_WRITE: RX1 element illegal write interrupt flag
      \arg        DMU_INT_FLAG_RX1_ELE_DEQ: RX1 element dequeued interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_NOT_STADDR: TX event element not start address interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_ILLE_DEQ: TX event element illegal dequeueing interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_ILLE_ACCSEQ: TX event element illegal access sequence interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_ILLE_WRITE: TX event element illegal write interrupt flag
      \arg        DMU_INT_FLAG_TXEV_ELE_DEQ: TX event element dequeued interrupt flag
      \arg        DMU_INT_FLAG_ILLE_ACC_IN_CONFIG: illegal access while in configuration mode interrupt flag
    \param[out] none
    \retval     none
*/
void can_interrupt_flag_clear(can_dtm_canx_enum dtm_canx, can_dtmcan_interrupt_flag_enum int_flag)
{
    /* clear the flag */
    CAN_REG_VAL2(dtm_canx, int_flag) = ((uint32_t)1U << (CAN_BIT_POS2(int_flag)));
}

/*!
    \brief      convert DTM_CANx to CAN
    \param[in]  dtm_canx: DTM_CANx(x=0..7)
    \param[out] none
    \retval     CANx(x=0,1,2)
*/
static uint32_t can_dtm_to_can(can_dtm_canx_enum dtm_canx)
{
    uint32_t can_periph = 0U;

    /* determine which DTM_CAN is selected */
    switch(dtm_canx) {
    case DTM_CAN0:
    case DTM_CAN1:
        can_periph = CAN0;
        break;
    case DTM_CAN2:
    case DTM_CAN3:
    case DTM_CAN4:
        can_periph = CAN1;
        break;
    case DTM_CAN5:
    case DTM_CAN6:
    case DTM_CAN7:
        can_periph = CAN2;
        break;
    default:
        break;
    }
    return can_periph;
}

/*!
    \brief      receive CAN message from a specific memory address
    \param[in]  addr: buffer memory address of the message to read
    \param[out] none
    \retval     can_receive_message_struct
*/
static can_receive_message_struct can_receive_by_addr(uint32_t addr)
{
    can_receive_message_struct receive_message;
    uint32_t *buffer_addr = (uint32_t *)addr;
    uint32_t r0_word;
    uint32_t r1_word;
    uint8_t i, j;
    uint32_t temp;

    can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &receive_message);

    /* read R0 and R1 words */
    r0_word = *buffer_addr;
    buffer_addr++;
    r1_word = *buffer_addr;
    buffer_addr++;

    /* copy R0 and R1 words to message structure */
    receive_message.id = r0_word & CAN_R0_ID;
    receive_message.rtr = (r0_word & CAN_R0_RTR) >> CAN_R0_RTR_OFFSET;
    receive_message.xtd = (r0_word & CAN_R0_XTD) >> CAN_R0_XTD_OFFSET;
    receive_message.esi = (r0_word & CAN_R0_ESI) >> CAN_R0_ESI_OFFSET;
    receive_message.timestamp = r1_word & CAN_R1A_RXTS;
    receive_message.dlc = (r1_word & CAN_R1A_DLC) >> CAN_R1A_DLC_OFFSET;
    receive_message.brs = (r1_word & CAN_R1A_BRS) >> CAN_R1A_BRS_OFFSET;
    receive_message.fdf = (r1_word & CAN_R1A_FDF) >> CAN_R1A_FDF_OFFSET;
    receive_message.filter_index = (r1_word & CAN_R1A_FIDX) >> CAN_R1A_FIDX_OFFSET;
    receive_message.non_match = (r1_word & CAN_R1A_ANMF) >> CAN_R1A_ANMF_OFFSET;

    /* if is standard identifier */
    if(0U == receive_message.xtd) {
        receive_message.id >>= 18U;
    }

    /* calculate data length */
    receive_message.data_bytes = dlc_to_databytes[receive_message.dlc];

    /* read data bytes */
    j = (uint8_t)((receive_message.data_bytes + 3U) / 4U);
    for(i = 0U; i < j; i++) {
        temp = *(uint32_t *)buffer_addr;
        receive_message.data[i * 4U] = (uint8_t)(temp & 0xFFU);
        receive_message.data[i * 4U + 1U] = (uint8_t)((temp & 0xFF00U) >> 8U);
        receive_message.data[i * 4U + 2U] = (uint8_t)((temp & 0xFF0000U) >> 16U);
        receive_message.data[i * 4U + 3U] = (uint8_t)((temp & 0xFF000000U) >> 24U);

        buffer_addr++;
    }

    /* handle partial data bytes */
    j = (uint8_t)(receive_message.data_bytes % 4U);
    if(1U == j) {
        receive_message.data[(i - 1U) * 4U + 1U] = 0U;
        receive_message.data[(i - 1U) * 4U + 2U] = 0U;
        receive_message.data[(i - 1U) * 4U + 3U] = 0U;
    } else if(2U == j) {
        receive_message.data[(i - 1U) * 4U + 2U] = 0U;
        receive_message.data[(i - 1U) * 4U + 3U] = 0U;
    } else if(3U == j) {
        receive_message.data[(i - 1U) * 4U + 3U] = 0U;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }

    return receive_message;
}

/*!
    \brief      write data to the destination array
    \param[in]  src: data source address
    \param[in]  len: data length be byte
    \param[out] dest: data destination address
    \retval     none
*/
static void can_data_write(uint32_t dest[], uint8_t src[], uint32_t len)
{
    uint32_t i;
    uint32_t cnt;

    /* get the word length of the data */
    cnt = (len + 3U) / 4U;
    for(i = 0U; i < cnt; i++) {
        dest[i] = (uint32_t)src[4U * i] | ((uint32_t)src[4U * i + 1U] << 8U) | ((uint32_t)src[4U * i + 2U] << 16U) | ((uint32_t)src[4U * i + 3U] << 24U);
    }

    cnt = len % 4U;
    if(0U != cnt) {
        dest[i - 1U] &= (((uint32_t)1U << ((4U - cnt) * 8U)) - 1U);
    }
}

/*!
    \brief      computes the DLC field value, given a payload size (in bytes)
    \param[in]  payload_size: payload size
    \param[out] none
    \retval     0~15
*/
static uint32_t can_dlc_value_compute(uint32_t payload_size)
{
    uint32_t ret;

    if(payload_size <= 8U) {
        ret = payload_size;
    } else if(payload_size <= 24U) {
        ret = (payload_size - 9U) / 4U + 9U;
    } else {
        ret = (payload_size - 17U) / 16U + 13U;
    }
    return ret;
}
