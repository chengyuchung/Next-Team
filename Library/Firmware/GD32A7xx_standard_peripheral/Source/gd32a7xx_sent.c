/*!
    \file    gd32a7xx_sent.c
    \brief   SENT driver

    \version 2025-08-06, V0.1.0, firmware for GD32A7xx
*/

/*
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

/*!
    \page    misra_violations MISRA-C:2012 violations

    \section [MISRA-C:2012]
             violates MISRA C:2012 Rule-10.8 (Required) The value of a composite expression
             shall not be cast to a different essential type category or a wider essential type
*/

#include "gd32a7xx_sent.h"

#define SENT_INIT_MASK                          ((uint32_t)0xFFFFFDFFU)  /*!< SENT parameter initialization mask */
#define SENT_DFTTH_OFFSET                       ((uint32_t)0x00000004U)  /*!< SENT channel filter threshold offset */
#define SENT_DATANIBBLE1_POSITION_OFFSET        ((uint32_t)0x00000004U)  /*!< SENT data nibble position 1 offset */
#define SENT_DATANIBBLE2_POSITION_OFFSET        ((uint32_t)0x00000008U)  /*!< SENT data nibble position 2 offset */
#define SENT_DATANIBBLE3_POSITION_OFFSET        ((uint32_t)0x0000000CU)  /*!< SENT data nibble position 3 offset */
#define SENT_DATANIBBLE4_POSITION_OFFSET        ((uint32_t)0x00000010U)  /*!< SENT data nibble position 4 offset */
#define SENT_DATANIBBLE5_POSITION_OFFSET        ((uint32_t)0x00000014U)  /*!< SENT data nibble position 5 offset */
#define SENT_DATANIBBLE6_POSITION_OFFSET        ((uint32_t)0x00000018U)  /*!< SENT data nibble position 6 offset */
#define SENT_DATANIBBLE7_POSITION_OFFSET        ((uint32_t)0x0000001CU)  /*!< SENT data nibble position 7 offset */
#define SENT_STATCOM_OFFSET                     ((uint32_t)0x00000008U)  /*!< SENT status & communication nibble offset */
#define SENT_MSGID_OFFSET                       ((uint32_t)0x00000010U)  /*!< SENT message id offset */
#define SENT_ESDT_OFFSET                        ((uint32_t)0x0000001FU)  /*!< SENT enhanced message type offset */
#define SENT_SDCRC_OFFSET                       ((uint32_t)0x00000018U)  /*!< SENT serial data crc offset */
#define SENT_EGDE_COUNT_OFFSET                  ((uint32_t)0x00000014U)  /*!< SENT egde count offset */
#define SENT_FDIV_DIVMOD_OFFSET                 ((uint32_t)0x0000000EU)  /*!< SENT fractional divider mode offset */
#define SENT_TICK_FACTOR                        ((double)56)             /*!< SENT tick clock factor */

/* get SENT module clock */
static double sent_get_module_clock(void);
/* get SENT channel clock */
static double sent_get_channel_clock(sent_channel_enum channelx);

/*!
    \brief      reset SENT (API_ID: 0x0001U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sent_deinit(void)
{
    /* disable SENT */
    sent_disable();
    /* reset SENT */
    rcu_periph_reset_enable(RCU_SENTRST);
    rcu_periph_reset_disable(RCU_SENTRST);
}

/*!
    \brief      initialize the parameters of SENT struct with default values (API_ID: 0x0002U)
    \param[in]  none
    \param[out] sent_struct: the initialized structure sent_parameter_struct pointer
    \retval     none
*/
void sent_struct_para_init(sent_parameter_struct *sent_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(sent_struct)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the structure with default values */
        sent_struct->freq_drift_check          = SENT_FREQ_DRIFT_CHECK_DISABLE;
        sent_struct->freq_drift_error_mode     = SENT_FREQ_DRIFT_ERROR_DISABLE;
        sent_struct->serial_message_mode       = SENT_SHORT_SERIAL_MESSAGE;
        sent_struct->serial_message_crc_mode   = SENT_SERIAL_MESSAGE_NORMAL_CRC;
        sent_struct->data_length               = SENT_DATALEN_6_NIBBLE;
        sent_struct->cons_sync_check_mode      = SENT_CONS_SYNC_CHECK_AFTER;
        sent_struct->crc                       = SENT_CRC_ENABLE;
        sent_struct->serial_data_crc           = SENT_SERIAL_DATA_CRC_ENABLE;
        sent_struct->serial_data_parse         = SENT_SERIAL_DATA_HARDWARE_PARSE;
        sent_struct->status_nibble_in_crc      = SENT_STATUS_NIBBLE_NOT_IN_CRC;
        sent_struct->alter_crc_mode            = SENT_STANDARD_CRC;
        sent_struct->ignore_pause              = SENT_IGNORE_PAUSE;
        sent_struct->pulse_polarity            = SENT_PULSE_POLARITY_LOW;
    }
}

/*!
    \brief      initialize SENT parameter  (API_ID: 0x0003U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  sent_struct: SENT parameter initialization stuct members of the structure
                            and the member values are shown as below:
                  freq_drift_check       : SENT_FREQ_DRIFT_CHECK_ENABLE, SENT_FREQ_DRIFT_CHECK_DISABLE
                  freq_drift_error_mode  : SENT_FREQ_DRIFT_ERROR_ENABLE, SENT_FREQ_DRIFT_ERROR_DISABLE
                  serial_message_mode    : SENT_SHORT_SERIAL_MESSAGE, SENT_ENHANCED_SERIAL_MESSAGE
                  serial_message_crc_mode: SENT_SERIAL_MESSAGE_AUGMENTATION_CRC, SENT_SERIAL_MESSAGE_NORMAL_CRC
                  data_length            : SENT_DATALEN_x_NIBBLE (x = 0...7)
                  cons_sync_check_mode   : SENT_CONS_SYNC_CHECK_AFTER, SENT_CONS_SYNC_CHECK_BEFORE
                  crc                    : SENT_CRC_ENABLE, SENT_CRC_DISABLE
                  serial_data_crc        : SENT_SERIAL_DATA_CRC_ENABLE, SENT_SERIAL_DATA_CRC_DISABLE
                  serial_data_parse      : SENT_SERIAL_DATA_HARDWARE_PARSE, SENT_SERIAL_DATA_SOFTWARE_PARSE
                  status_nibble_in_crc   : SENT_STATUS_NIBBLE_IN_CRC, SENT_STATUS_NIBBLE_NOT_IN_CRC
                  alter_crc_mode         : SENT_PARALLEL_CRC, SENT_STANDARD_CRC
                  ignore_pause           : SENT_IGNORE_PAUSE, SENT_NOT_IGNORE_PAUSE
                  pulse_polarity         : SENT_PULSE_POLARITY_HIGH, SENT_PULSE_POLARITY_LOW
    \param[out] none
    \retval     none
*/
void sent_init(sent_channel_enum channelx, sent_parameter_struct *sent_struct)
{
    uint32_t reg1;
    uint32_t reg2;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(sent_struct)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else if(NOT_SENT_FREQ_DRIFT_CHECK(sent_struct ->freq_drift_check)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_FREQ_DRIFT_ERROR(sent_struct ->freq_drift_error_mode)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_SERIAL_MSG_MODE(sent_struct ->serial_message_mode)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_SERIAL_MSG_CRC_MODE(sent_struct ->serial_message_crc_mode)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_DATA_LENGTH(sent_struct ->data_length)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_CONS_SYNC_CHECK(sent_struct ->cons_sync_check_mode)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_CRC(sent_struct ->crc)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_SERIAL_DATA_CRC(sent_struct ->serial_data_crc)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_SERIAL_DATA_PARSE(sent_struct ->serial_data_parse)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_STATUS_NIBBLE_IN_CRC(sent_struct ->status_nibble_in_crc)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_ALTER_CRC(sent_struct ->alter_crc_mode)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_IGNORE_PAUSE(sent_struct ->ignore_pause)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SENT_PULSE_POLARITY(sent_struct ->pulse_polarity)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure receiver control parameters */
        reg1 = sent_struct->freq_drift_check | sent_struct->freq_drift_error_mode | sent_struct->serial_message_mode \
               | sent_struct->serial_message_crc_mode | sent_struct->data_length | sent_struct->cons_sync_check_mode \
               | sent_struct->crc | sent_struct->serial_data_crc | sent_struct->serial_data_parse | sent_struct->status_nibble_in_crc \
               | sent_struct->alter_crc_mode | sent_struct->ignore_pause;
            
        reg2 = SENT_CHCS((uint32_t)channelx);
        reg2 &= SENT_INIT_MASK;
        /* configure pulse polarity */
        reg2 |= sent_struct->pulse_polarity;

        /* write to registers */
        SENT_CHRCTL((uint32_t)channelx) = (uint32_t)reg1;
        SENT_CHCS((uint32_t)channelx) = (uint32_t)reg2;
    }
}

/*!
    \brief      enable SENT (API_ID: 0x0004U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sent_enable(void)
{
    SENT_CS |= SENT_CS_SENTEN;
}

/*!
    \brief      disable SENT (API_ID: 0x0005U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sent_disable(void)
{
    SENT_CS &= ~(SENT_CS_SENTEN);
}

/*!
    \brief      enable SENT sleep mode (API_ID: 0x0006U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sent_sleep_enable(void)
{
    SENT_CS |= SENT_CS_SLPEN;
}

/*!
    \brief      disable SENT sleep mode (API_ID: 0x0007U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void sent_sleep_disable(void)
{
    SENT_CS &= ~(SENT_CS_SLPEN);
}

/*!
    \brief      get SENT state (API_ID: 0x0008U)
    \param[in]  none
    \param[out] none
    \retval     ControlStatus: ENABLE or DISABLE
*/
ControlStatus sent_state_get(void)
{
    ControlStatus  status;

    if((uint32_t)RESET != (SENT_CS & SENT_CS_SENTF)){
        status = ENABLE;
    }else{
        status = DISABLE;
    }
    return status;
}

/*!
    \brief      enable SENT channel x (API_ID: 0x0009U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     none
*/
void sent_channel_enable(sent_channel_enum channelx)
{
    SENT_CHRCTL((uint32_t)channelx) |= SENT_CHXRCTL_CHEN;
}

/*!
    \brief      disable SENT channel x (API_ID: 0x000AU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     none
*/
void sent_channel_disable(sent_channel_enum channelx)
{
    SENT_CHRCTL((uint32_t)channelx) &= ~(SENT_CHXRCTL_CHEN);
}

/*!
    \brief      get SENT channel state (API_ID: 0x000BU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     state of SENT channel x
      \arg        SENT_CH_STOP: channel is disabled
      \arg        SENT_CH_INIT: channel is enabled, but synchronization/calibration pulse  has not been received
      \arg        SENT_CH_RUN : channel is enabled and the synchronization/calibration pulse received was out of the correct frequency range or had frequency drift and was out of range
      \arg        SENT_CH_SYNC: Channel is enabled and synchronization/calibration pulse received is valid and in the synchronization state
*/
uint32_t sent_channel_state_get(sent_channel_enum channelx)
{
    uint32_t state;

    state = SENT_CHRSTAT((uint32_t)channelx) & SENT_CHXRSTAT_CHSTAT;

    return state;
}

/*!
    \brief      select SENT channel x input (API_ID: 0x000CU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  inputx: SENT channel input x (x = 0...3)
                only one parameter can be selected which is shown as below:
      \arg        SENT_ALTI_INPUT0: SENT channel input 0
      \arg        SENT_ALTI_INPUT1: SENT channel input 1
      \arg        SENT_ALTI_INPUT2: SENT channel input 2
      \arg        SENT_ALTI_INPUT3: SENT channel input 3
    \param[out] none
    \retval     none
*/
void sent_channel_input_select(sent_channel_enum channelx, sent_channel_input_enum inputx)
{
    uint32_t reg = SENT_CHCS((uint32_t)channelx);

    reg &=~SENT_CHXCS_INSEL;
    reg |= (uint32_t)inputx;
    SENT_CHCS((uint32_t)channelx) = reg;
}

/*!
    \brief      configure SENT module clock (API_ID: 0x000DU)
    \param[in]  dividermode: divider mode
                only one parameter can be selected which is shown as below:
      \arg        SENT_CLOCKDIVIDERMODE_OFF: disable fractional divider, no output clock is generated
      \arg        SENT_CLOCKDIVIDERMODE_NORMAL: normal divider mode
      \arg        SENT_CLOCKDIVIDERMODE_FRACTIONAL: fractional divider mode
    \param[in]  stepvalue: 0...0x3FF
    \param[out] none
    \retval     none
*/
void sent_module_clock_config(uint32_t dividermode, uint32_t stepvalue)
{
    uint32_t reg = SENT_FDIV;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SENT_CLOCK_DIVIDER_MODE(dividermode)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else if(NOT_SENT_CLOCK_STEP(stepvalue)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x000DU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure divider mode */
        reg &= ~(SENT_FDIV_DIVMOD);
        reg |= (dividermode << SENT_FDIV_DIVMOD_OFFSET);
        /* configure stepvalue */
        reg &= ~(SENT_FDIV_STEP);
        reg |= (SENT_FDIV_STEP & stepvalue);
        
        SENT_FDIV = reg;
    }
}

/*!
    \brief      configure SENT ticks clock (API_ID: 0x000EU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  tick_unit: 0.00000004 ~ 0.001024
    \param[out] none
    \retval     none
*/
void sent_channel_tick_clock_config(sent_channel_enum channelx, double tick_unit)
{
    double         fracdiv;
    uint32_t       psc = 0U;
    uint32_t       div = 0U;
    double         result;
    uint32_t       div_max;
    uint32_t       reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SENT_CHANNEL_TICK(tick_unit)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x000EU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get fracdiv */
        fracdiv = sent_get_module_clock();
        result  = fracdiv * SENT_TICK_FACTOR * tick_unit;
        for (div_max = 2200U; div_max < 49100U ; div_max++){
            psc = (uint32_t)(result / (double)div_max);
            div = (uint32_t)(result / (double)psc);

            /* count psc and div value */
            if ((psc < 0x00001000U) && (psc > 0x00000000U)){
                break;
            } else {
                /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
            }
        }

        /* configure psc */
        reg = SENT_CHPSC((uint32_t)channelx);
        reg &= ~(SENT_CHXPSC_PSC);
        reg |= (SENT_CHXPSC_PSC & (psc - 0x00000001U));
        SENT_CHPSC((uint32_t)channelx) = reg;
        
        /* configure div */
        reg =  SENT_CHFDIV((uint32_t)channelx);
        reg &= ~(SENT_CHXFDIV_DIV);
        reg |= (SENT_CHXFDIV_DIV & div);
        SENT_CHFDIV((uint32_t)channelx) = reg;
    }
}

/*!
    \brief      set SENT filter threshold (API_ID: 0x000FU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  threshold: 0...0xF
    \param[out] none
    \retval     none
*/
void sent_filter_threshold_set(sent_channel_enum channelx, uint32_t threshold)
{
    uint32_t reg = SENT_CHCS((uint32_t)channelx);
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SENT_CHANNEL_FILTER_TH(threshold)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x000FU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg &= ~(SENT_CHXCS_DFTTH);
        reg |= (threshold << SENT_DFTTH_OFFSET);
        SENT_CHCS((uint32_t)channelx) = reg;
    }
}

/*!
    \brief      configure the SENT channel data nibble storage position (API_ID: 0x0010U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  data: SENT nibble control parameter stuct members of the structure
                            and the member values are shown as below:
                  nibblex_position (x = 0...7): specifies the received nibblex control, refer to sent_nibble_position_enum
    \param[out] none
    \retval     none
*/
void sent_data_nibble_pos_config(sent_channel_enum channelx, sent_nibble_control_struct *data)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(data)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0010U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SENT_CHRDPCFG((uint32_t)channelx) = ((uint32_t)(data->nibble0_position) | ((uint32_t)(data->nibble1_position) << SENT_DATANIBBLE1_POSITION_OFFSET) | \
                                            ((uint32_t)(data->nibble2_position) << SENT_DATANIBBLE2_POSITION_OFFSET) | ((uint32_t)(data->nibble3_position) << SENT_DATANIBBLE3_POSITION_OFFSET) | \
                                            ((uint32_t)(data->nibble4_position) << SENT_DATANIBBLE4_POSITION_OFFSET) | ((uint32_t)(data->nibble5_position) << SENT_DATANIBBLE5_POSITION_OFFSET) | \
                                            ((uint32_t)(data->nibble6_position) << SENT_DATANIBBLE6_POSITION_OFFSET) | ((uint32_t)(data->nibble7_position) << SENT_DATANIBBLE7_POSITION_OFFSET));
    }
}

/*!
    \brief      configure the SENT timestamp prescaler (API_ID: 0x0011U)
    \param[in]  psc: timestamp prescaler, 0 ~ 0x000FFFFF
    \param[out] none
    \retval     none
*/
void sent_timestamp_prescaler_config(uint32_t psc)
{
    uint32_t reg = SENT_TSPSC;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SENT_TIMESTAMP_PRESCALER(psc)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0011U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg &= ~(SENT_TSPSC_TSPSC);
        reg |= psc;
        SENT_TSPSC = reg;
    }
}

/*!
    \brief      get SENT current timestamp (API_ID: 0x0012U)
    \param[in]  none
    \param[out] none
    \retval     uint32_t: 0 ~ 0xFFFFFFFF
*/
uint32_t sent_timestamp_get(void)
{
    return (SENT_TS);
}

/*!
    \brief      set SENT watchdog threshold (API_ID: 0x0013U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  threshold: 0...0xFFFF
    \param[out] none
    \retval     none
*/
void sent_watchdog_threshold_set(sent_channel_enum channelx, uint16_t threshold)
{
    uint32_t reg = SENT_CHWDGT((uint32_t)channelx);

    reg &= ~(SENT_CHXWDGT_THOLD);
    reg |= threshold;
    SENT_CHWDGT((uint32_t)channelx) = reg;
}

/*!
    \brief      SENT receive data nibble (API_ID: 0x0014U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     uint32_t: 0 ~ 0xFFFFFFFF
*/
uint32_t sent_receive_data(sent_channel_enum channelx)
{
    return (SENT_CHRDATA((uint32_t)channelx));
}

/*!
    \brief      SENT receive frame (API_ID: 0x0015U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
      \param[out] frame: the structure sent_frame_struct pointer, point to the received frame
    \retval     none
*/
void sent_receive_frame(sent_channel_enum channelx, sent_frame_struct *frame)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(frame)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0015U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        frame->data         = SENT_CHRDATA((uint32_t)channelx) ;
        frame->timestamp    = SENT_CHTS((uint32_t)channelx);
        frame->statusnibble = (uint8_t)((SENT_CHRSTAT((uint32_t)channelx) & SENT_CHXRSTAT_STACOM) >> SENT_STATCOM_OFFSET);
        frame->crcnibble    = (uint8_t)(SENT_CHRSTAT((uint32_t)channelx) & SENT_CHXRSTAT_CRC);
    }
}

/*!
    \brief      SENT receive serial message (API_ID: 0x0016U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
      \param[out] message: the structure sent_serialmessage_frame_struct pointer, point to the received serial message
    \retval     none
*/
void sent_receive_serial_message(sent_channel_enum channelx, sent_serialmessage_frame_struct *message)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(message)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0016U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        message->serialdata = (uint16_t)(SENT_CHRSDSTAT((uint32_t)channelx) & SENT_CHXRSDSTAT_SDATA);
        message->messageid  = (uint8_t)((SENT_CHRSDSTAT((uint32_t)channelx) & SENT_CHXRSDSTAT_MSGID)>> SENT_MSGID_OFFSET);
        message->configbit  = (uint8_t)((SENT_CHRSDSTAT((uint32_t)channelx) & SENT_CHXRSDSTAT_ESDT)>>SENT_ESDT_OFFSET);
        message->crc        = (uint8_t)((SENT_CHRSDSTAT((uint32_t)channelx) & SENT_CHXRSDSTAT_SDCRC)>>SENT_SDCRC_OFFSET);
    }
}

/*!
    \brief      get the falling edge count occurring on the selected SENT input pin (API_ID: 0x0017U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     uint8_t: 0 ~ 0xFF
*/
uint8_t sent_input_edge_count_get(sent_channel_enum channelx)
{
    return (uint8_t)((SENT_CHCS((uint32_t)channelx) & SENT_CHXCS_EGCNT) >> SENT_EGDE_COUNT_OFFSET);
}

/*!
    \brief      clear the falling edge count occurring on the selected SENT input pin (API_ID: 0x0018U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     none
*/
void sent_input_edge_count_clear(sent_channel_enum channelx)
{
    SENT_CHCS((uint32_t)channelx) |= SENT_CHXCS_EGCNTC;
}

/*!
    \brief      get SENT frame length (API_ID: 0x0019U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     3.68E-5~1.120256
*/
double sent_get_frame_length(sent_channel_enum channelx)
{
    uint32_t reg;
    double length;
    double fpsc;

    /* get fpsc */
    fpsc = sent_get_channel_clock(channelx);
    /* get frame length */
    reg = GET_BITS(SENT_CHRSTAT((uint32_t)channelx), 16U, 31U);
    length = (double)((double)reg / fpsc);
    
    return length;
}

/*!
    \brief      get SENT synchronization pulse length (API_ID: 0x001AU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     2.24E-5~5.7344E-2
*/
double sent_get_sync_length(sent_channel_enum channelx)
{
    uint32_t reg;
    double length;
    double fpsc;
    
    /* get fpsc */
    fpsc = sent_get_channel_clock(channelx);
    /* get synchronization pulse length */
    reg = GET_BITS(SENT_CHFDIV((uint32_t)channelx), 16U, 31U);
    length = (double)((double)reg / fpsc);
    
    return length;
}

/*!
    \brief      set SENT channel flag status (API_ID: 0x001BU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  flag: SENT flag status
                only one parameter can be selected which is shown as below:
      \arg        SENT_FLAG_RSF     : receive success flag
      \arg        SENT_FLAG_RBNE    : receive buffer not empty flag
      \arg        SENT_FLAG_RXOVERR : receive buffer overflow error flag
      \arg        SENT_FLAG_FDEVERR : frequency deviation error flag
      \arg        SENT_FLAG_FDERR   : frequency drift error flag
      \arg        SENT_FLAG_NNIBERR : number of nibbles error flag
      \arg        SENT_FLAG_NIBVERR : nibble value error flag
      \arg        SENT_FLAG_CRCERR  : CRC error flag
      \arg        SENT_FLAG_SSDSTERR: short serial data message start bit error flag
      \arg        SENT_FLAG_SDRBNE  : serial data receive buffer not empty flag
      \arg        SENT_FLAG_SDCRCERR: serial data CRC error flag
      \arg        SENT_FLAG_WDERR   : watchdog error flag
    \param[out] none
    \retval     none
*/
void sent_channel_flag_set(sent_channel_enum channelx, sent_channel_flag_enum flag)
{
    SENT_CHSTATCTL((uint32_t)channelx) |= BIT(SENT_BIT_POS((uint32_t)flag));
}

/*!
    \brief      get SENT channel status (API_ID: 0x001CU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  flag: SENT flag status
                only one parameter can be selected which is shown as below:
      \arg        SENT_FLAG_RSF     : receive success flag
      \arg        SENT_FLAG_RBNE    : receive buffer not empty flag
      \arg        SENT_FLAG_RXOVERR : receive buffer overflow error flag
      \arg        SENT_FLAG_FDEVERR : frequency deviation error flag
      \arg        SENT_FLAG_FDERR   : frequency drift error flag
      \arg        SENT_FLAG_NNIBERR : number of nibbles error flag
      \arg        SENT_FLAG_NIBVERR : nibble value error flag
      \arg        SENT_FLAG_CRCERR  : CRC error flag
      \arg        SENT_FLAG_SSDSTERR: short serial data message start bit error flag
      \arg        SENT_FLAG_SDRBNE  : serial data receive buffer not empty flag
      \arg        SENT_FLAG_SDCRCERR: serial data CRC error flag
      \arg        SENT_FLAG_WDERR   : watchdog error flag
      \arg        SENT_FLAG_REGNDF  : rising edge noise detect flag
      \arg        SENT_FLAG_FEGNDF  : falling edge noise detect flag
      \arg        SENT_FLAG_RSL     : receive signal level
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sent_channel_flag_get(sent_channel_enum channelx, sent_channel_flag_enum flag)
{
    FlagStatus  status;

    if(0U != ((SENT_REG_VAL((uint32_t)flag, (uint32_t)channelx)) & BIT(SENT_BIT_POS((uint32_t)flag)))) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/*!
    \brief      clear SENT channel status (API_ID: 0x001DU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  flag: SENT flag status
                only one parameter can be selected which is shown as below:
      \arg        SENT_FLAG_RSFC     : receive success flag clear 
      \arg        SENT_FLAG_RBNEC    : receive buffer not empty flag clear
      \arg        SENT_FLAG_RXOVERRC : receive buffer overflow error flag clear
      \arg        SENT_FLAG_FDEVERRC : frequency deviation error flag clear
      \arg        SENT_FLAG_FDERRC   : frequency drift error flag clear
      \arg        SENT_FLAG_NNIBERRC : number of nibbles error flag clear
      \arg        SENT_FLAG_NIBVERRC : nibble value error flag clear
      \arg        SENT_FLAG_CRCERRC  : CRC error flag clear
      \arg        SENT_FLAG_SSDSTERRC: short serial data message start bit error flag clear
      \arg        SENT_FLAG_SDRBNEC  : serial data receive buffer not empty flag clear
      \arg        SENT_FLAG_SDCRCERRC: serial data CRC error flag clear
      \arg        SENT_FLAG_WDERRC   : watchdog error flag clear
      \arg        SENT_FLAG_REGNDFC  : rising edge noise detect flag clear
      \arg        SENT_FLAG_FEGNDFC  : falling edge noise detect flag clear
    \param[out] none
    \retval     none
*/
void sent_channel_flag_clear(sent_channel_enum channelx, sent_channel_flag_clear_enum flag)
{
    (SENT_REG_VAL((uint32_t)flag, (uint32_t)channelx)) = BIT(SENT_BIT_POS((uint32_t)flag));
}

/*!
    \brief      enable SENT  channel interrupt (API_ID: 0x001EU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  interrupt: SENT interrupt
                only one parameter can be selected which is shown as below:
      \arg        SENT_INT_RSF     : receive success interrupt enable
      \arg        SENT_INT_RBNE    : receive buffer not empty interrupt enable
      \arg        SENT_INT_RXOVERR : receive buffer overflow error interrupt enable
      \arg        SENT_INT_FDEVERR : frequency deviation error interrupt enable
      \arg        SENT_INT_FDERR   : frequency drift error interrupt enable
      \arg        SENT_INT_NNIBERR : number of nibbles error interrupt enable
      \arg        SENT_INT_NIBVERR : nibble value error interrupt enable
      \arg        SENT_INT_CRCERR  : CRC error interrupt enable
      \arg        SENT_INT_SSDSTERR: short serial data message start bit error interrupt enable
      \arg        SENT_INT_SDRBNE  : serial data receive buffer not empty interrupt enable
      \arg        SENT_INT_SDCRCERR: serial data CRC error interrupt enable
      \arg        SENT_INT_WDERR   : watchdog error interrupt enable
    \param[out] none
    \retval     none
*/
void sent_channel_interrupt_enable(sent_channel_enum channelx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SENT_INTERRUPT(interrupt)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x001EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SENT_CHINTEN((uint32_t)channelx) |= interrupt;
    }
}
/*!
    \brief      disable SENT channel interrupt (API_ID: 0x001FU)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  interrupt: SENT interrupt
                only one parameter can be selected which is shown as below:
      \arg        SENT_INT_RSF     : receive success interrupt enable
      \arg        SENT_INT_RBNE    : receive buffer not empty interrupt enable
      \arg        SENT_INT_RXOVERR : receive buffer overflow error interrupt enable
      \arg        SENT_INT_FDEVERR : frequency deviation error interrupt enable
      \arg        SENT_INT_FDERR   : frequency drift error interrupt enable
      \arg        SENT_INT_NNIBERR : number of nibbles error interrupt enable
      \arg        SENT_INT_NIBVERR : nibble value error interrupt enable
      \arg        SENT_INT_CRCERR  : CRC error interrupt enable
      \arg        SENT_INT_SSDSTERR: short serial data message start bit error interrupt enable
      \arg        SENT_INT_SDRBNE  : serial data receive buffer not empty interrupt enable
      \arg        SENT_INT_SDCRCERR: serial data CRC error interrupt enable
      \arg        SENT_INT_WDERR   : watchdog error interrupt enable
    \param[out] none
    \retval     none
*/
void sent_channel_interrupt_disable(sent_channel_enum channelx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SENT_INTERRUPT(interrupt)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x001FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SENT_CHINTEN((uint32_t)channelx) &= ~interrupt;
    }
}

/*!
    \brief      get SENT channel interrupt and flag status (API_ID: 0x0020U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  int_flag: interrupt and flag type
                only one parameter can be selected which is shown as below:
      \arg        SENT_INT_FLAG_RSF     : receive success interrupt flag
      \arg        SENT_INT_FLAG_RBNE    : receive buffer not empty interrupt flag
      \arg        SENT_INT_FLAG_RXOVERR : receive buffer overflow error interrupt flag
      \arg        SENT_INT_FLAG_FDEVERR : frequency deviation error interrupt flag
      \arg        SENT_INT_FLAG_FDERR   : frequency drift error interrupt flag
      \arg        SENT_INT_FLAG_NNIBERR : number of nibbles error interrupt flag
      \arg        SENT_INT_FLAG_NIBVERR : nibble value error interrupt flag
      \arg        SENT_INT_FLAG_CRCERR  : CRC error interrupt flag
      \arg        SENT_INT_FLAG_SSDSTERR: short serial data message start bit error interrupt flag
      \arg        SENT_INT_FLAG_SDRBNE  : serial data receive buffer not empty interrupt flag
      \arg        SENT_INT_FLAG_SDCRCERR: serial data CRC error interrupt flag
      \arg        SENT_INT_FLAG_WDERR   : watchdog error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sent_channel_interrupt_flag_get(sent_channel_enum channelx, uint32_t int_flag)
{
    FlagStatus  status = RESET;
    uint32_t intenable, flagstatus;
    
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SENT_INT_FLAG(int_flag)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0020U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the interrupt enable bit status */
        intenable = SENT_CHINTEN((uint32_t)channelx) & int_flag;
        /* get the corresponding flag bit status */
        flagstatus = SENT_CHSTAT((uint32_t)channelx) & int_flag;

        if(0U != (flagstatus & intenable)) {
            status = SET;
        } else {
            status = RESET;
        }
    }
    return status;
}

/*!
    \brief      get SENT channel global interrupt and flag status (API_ID: 0x0021U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sent_channel_global_interrupt_flag_get(sent_channel_enum channelx)
{
    FlagStatus  status;
    uint32_t reg;

    /* get global interrupt and flag status */
    reg = SENT_GINTF & BIT((uint32_t)channelx);

    if(0U != reg) {
        status = SET;
    } else {
        status = RESET;
    }

    return status;
}

/*!
    \brief      clear SENT channel interrupt flag (API_ID: 0x0022U)
    \param[in]  channelx: SENT channel x (x = 0...5)
                only one parameter can be selected which is shown as below:
      \arg        SENT_CH0: SENT channel 0
      \arg        SENT_CH1: SENT channel 1
      \arg        SENT_CH2: SENT channel 2
      \arg        SENT_CH3: SENT channel 3
      \arg        SENT_CH4: SENT channel 4
      \arg        SENT_CH5: SENT channel 5
    \param[in]  int_flag: interrupt and flag type
                only one parameter can be selected which is shown as below:
      \arg        SENT_INT_FLAG_RSF     : receive success interrupt flag
      \arg        SENT_INT_FLAG_RBNE    : receive buffer not empty interrupt flag
      \arg        SENT_INT_FLAG_RXOVERR : receive buffer overflow error interrupt flag
      \arg        SENT_INT_FLAG_FDEVERR : frequency deviation error interrupt flag
      \arg        SENT_INT_FLAG_FDERR   : frequency drift error interrupt flag
      \arg        SENT_INT_FLAG_NNIBERR : number of nibbles error interrupt flag
      \arg        SENT_INT_FLAG_NIBVERR : nibble value error interrupt flag
      \arg        SENT_INT_FLAG_CRCERR  : CRC error interrupt flag
      \arg        SENT_INT_FLAG_SSDSTERR: short serial data message start bit error interrupt flag
      \arg        SENT_INT_FLAG_SDRBNE  : serial data receive buffer not empty interrupt flag
      \arg        SENT_INT_FLAG_SDCRCERR: serial data CRC error interrupt flag
      \arg        SENT_INT_FLAG_WDERR   : watchdog error interrupt flag
    \param[out] none
    \retval     none
*/
void sent_channel_interrupt_flag_clear(sent_channel_enum channelx, uint32_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SENT_INT_FLAG(int_flag)) {
        fw_debug_report_err(SENT_MODULE_ID, API_ID(0x0022U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SENT_CHSTATC((uint32_t)channelx) |= int_flag;
    }
}

/*!
    \brief      get SENT module clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
static double sent_get_module_clock(void)
{
    uint32_t fsys;
    uint32_t stepvalue = GET_BITS(SENT_FDIV, 0U, 9U);
    uint32_t dividermode = GET_BITS(SENT_FDIV, 14U, 15U);
    double   fracdiv = 0.0f;

    /* get SENT clock */
    fsys = rcu_clock_freq_get(CK_APB1);
    
    if (SENT_CLOCKDIVIDERMODE_NORMAL == dividermode) {
        fracdiv = (double)fsys / (1024.0f - (double)stepvalue);
    } else if (SENT_CLOCKDIVIDERMODE_FRACTIONAL == dividermode) {
        fracdiv = ((double)fsys * (double)stepvalue) / 1024.0f;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }

    return fracdiv;
}

/*!
    \brief      get SENT channel clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
static double sent_get_channel_clock(sent_channel_enum channelx)
{
    double fracdiv;
    uint32_t psc = GET_BITS(SENT_CHPSC((uint32_t)channelx), 0U, 11U);
    double   fpsc;

    /* get fracdiv */
    fracdiv = sent_get_module_clock();
    /* get fpsc */
    fpsc = fracdiv / (double)(psc + 0x00000001U);

    return fpsc;
}
