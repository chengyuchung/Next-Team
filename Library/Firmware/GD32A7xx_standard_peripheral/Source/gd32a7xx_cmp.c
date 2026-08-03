/*!
    \file    gd32a7xx_cmp.c
    \brief   CMP driver

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

#include "gd32a7xx_cmp.h"

/*!
    \brief      deinitialize comparator (API_ID(0x0001U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_deinit(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CMP0 == cmp_periph){
            /* disable CMP0 */
            cmp_disable(CMP0);
            /* reset CMP0 */
            rcu_periph_reset_enable(RCU_CMP0RST);
            rcu_periph_reset_disable(RCU_CMP0RST);
        }else if(CMP1 == cmp_periph){
            /* disable CMP1 */
            cmp_disable(CMP1);
            /* reset CMP1 */
            rcu_periph_reset_enable(RCU_CMP1RST);
            rcu_periph_reset_disable(RCU_CMP1RST);
        }else{
            /* illegal parameters */
        }
    }
}

/*!
    \brief      initialize comparator mode (API_ID(0x0002U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  operating_mode
                only one parameter can be selected which is shown as below:
      \arg        CMP_MODE_HIGHSPEED: high speed mode
      \arg        CMP_MODE_MIDDLESPEED: medium speed mode
      \arg        CMP_MODE_LOWSPEED: low speed mode
    \param[in]  inverting_input
                only one parameter can be selected which is shown as below:
      \arg        CMP_INVERTING_INPUT_1_4VREFINT: CMP inverting input 1/4 Vrefint
      \arg        CMP_INVERTING_INPUT_1_2VREFINT: CMP inverting input 1/2 Vrefint
      \arg        CMP_INVERTING_INPUT_3_4VREFINT: CMP inverting input 3/4 Vrefint
      \arg        CMP_INVERTING_INPUT_VREFINT: CMP inverting input Vrefint
      \arg        CMP_INVERTING_INPUT_DAC_OUT: CMP inverting input DAC0_OUT0 for CMP0 or DAC1_OUT0 for CMP1
      \arg        CMP_INVERTING_INPUT_PF5_PC6: CMP inverting input PF5 for CMP0 or PC6 for CMP1
      \arg        CMP_INVERTING_INPUT_PF4_PG7: CMP inverting input PF4 for CMP0 or PG7 for CMP1
      \arg        CMP_INVERTING_INPUT_PA2_PJ11: CMP inverting input PA2 for CMP0 or PJ11 for CMP1
      \arg        CMP_INVERTING_INPUT_PC2_PA14: CMP inverting input PC2 for CMP0 or PA14 for CMP1
      \arg        CMP_INVERTING_INPUT_PA1_PK1: CMP inverting input PA1 for CMP0 or PK1 for CMP1
      \arg        CMP_INVERTING_INPUT_PF3_PK2: CMP inverting input PF3 for CMP0 or PK2 for CMP1
      \arg        CMP_INVERTING_INPUT_PH2_PG2: CMP inverting input PH2 for CMP0 or PG2 for CMP1
      \arg        CMP_INVERTING_INPUT_PH3_PG5: CMP inverting input PH3 for CMP0 or PG5 for CMP1
      \arg        CMP_INVERTING_INPUT_PA14: CMP inverting input PA14(only for CMP0)
      \arg        CMP_INVERTING_INPUT_PC6: CMP inverting input PC6(only for CMP0)
      \arg        CMP_INVERTING_INPUT_PG7: CMP inverting input PG7(only for CMP0)
    \param[in]  output_hysteresis
                only one parameter can be selected which is shown as below:
      \arg        CMP_HYSTERESIS_NO: output no hysteresis
      \arg        CMP_HYSTERESIS_LOW: output low hysteresis
      \arg        CMP_HYSTERESIS_MIDDLE: output middle hysteresis
      \arg        CMP_HYSTERESIS_HIGH: output high hysteresis
    \param[out] none
    \retval     none
*/
void cmp_mode_init(uint32_t cmp_periph, uint32_t operating_mode, uint32_t inverting_input, uint32_t output_hysteresis)
{
    uint32_t temp;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0002U), ERR_PERIPH);
    }else if(NOT_CMP_OPERATING_MODE(operating_mode)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    }else if(NOT_CMP_INVERTING_INPUT(inverting_input)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    }else if(NOT_CMP_OUTPUT_HYSTERESIS(output_hysteresis)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp = CMP_CS(cmp_periph);
        /* initialize comparator  mode */
        temp &= ~(uint32_t)(CMP_CS_CMPXM | CMP_CS_CMPXMESEL | CMP_CS_CMPXMISEL | CMP_CS_CMPXHST);
        temp |= (uint32_t)(operating_mode | inverting_input | output_hysteresis);
        CMP_CS(cmp_periph) =  temp;
    }
}

/*!
    \brief      initialize comparator input (API_ID(0x0003U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  noninverting_input
                only one parameter can be selected which is shown as below:
      \arg        CMP_NONINVERTING_DAC_OUT: CMP noninverting input DAC0_OUT0 for CMP0 or DAC1_OUT0 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PF5_PC6: CMP noninverting input PF5 for CMP0 or PC6 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PF4_PG7: CMP noninverting input PF4 for CMP0 or PG7 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PA2_PJ11: CMP noninverting input PA2 for CMP0 or PJ11 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PC2_PA14: CMP noninverting input PC2 for CMP0 or PA14 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PA1_PK1: CMP noninverting input PA1 for CMP0 or PK1 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PF3_PK2: CMP noninverting input PF3 for CMP0 or PK2 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PH2_PG2: CMP noninverting input PH2 for CMP0 or PG2 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PH3_PG5: CMP noninverting input PH3 for CMP0 or PG5 for CMP1
      \arg        CMP_NONINVERTING_INPUT_PA14: CMP noninverting input PA14(only for CMP0)
      \arg        CMP_NONINVERTING_INPUT_PC6: CMP noninverting input PC6(only for CMP0)
      \arg        CMP_NONINVERTING_INPUT_PG7:  CMP noninverting input PG7(only for CMP0)
    \param[out] none
    \retval     none
*/
void cmp_noninverting_input_select(uint32_t cmp_periph, uint32_t noninverting_input)
{
    uint32_t temp;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    }else if(NOT_CMP_NONINVERTING_INPUT(noninverting_input)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp = CMP_CS(cmp_periph);
        /* initialize comparator mode */
        temp &= ~(uint32_t)(CMP_CS_CMPXPESEL | CMP_CS_CMPXPSEL | CMP_CS_CMPXPESEL3);
        temp |= (uint32_t)noninverting_input;
        CMP_CS(cmp_periph) = temp;
    }
}

/*!
    \brief      initialize comparator output (API_ID(0x0004U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  output_selection
                only one parameter can be selected which is shown as below:
      \arg        CMP_OUTPUT_NONE: output no selection
      \arg        CMP_OUTPUT_TIMER0_IC0_TIMER20_IC0: CMP0 output TIMER0_CH0 input capture, CMP1 output TIMER20_CH0 input capture
      \arg        CMP_OUTPUT_TIMER7_IC0_TIMER60_IC0: CMP0 output TIMER7_CH0 input capture, CMP1 output TIMER60_CH0 input capture
    \param[in]  output_polarity
                only one parameter can be selected which is shown as below:
      \arg        CMP_OUTPUT_POLARITY_INVERTED: output is inverted
      \arg        CMP_OUTPUT_POLARITY_NONINVERTED: output is not inverted
    \param[out] none
    \retval     none
*/
void cmp_output_init(uint32_t cmp_periph, uint32_t output_selection, uint32_t output_polarity)
{
    uint32_t temp;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    }else if(NOT_CMP_OUTPUT_SELECTION(output_selection)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    }else if(NOT_CMP_OUTPUT_POLARITY(output_polarity)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp = CMP_CS(cmp_periph);
        /* initialize comparator  output */
        temp &= ~(uint32_t)CMP_CS_CMPXOSEL;
        temp |= (uint32_t)output_selection;
        /* output polarity */
        if(CMP_OUTPUT_POLARITY_INVERTED == output_polarity) {
            temp |= (uint32_t)CMP_CS_CMPXPL;
        } else {
            temp &= ~(uint32_t)CMP_CS_CMPXPL;
        }
        CMP_CS(cmp_periph) = temp;
    }
}

/*!
    \brief      initialize comparator blanking function (API_ID(0x0005U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  blanking_source_selection
                only one parameter can be selected which is shown as below:
      \arg        CMP_BLANKING_NONE: CMP no blanking source
      \arg        CMP_BLANKING_TIMER0_OC1: CMP TIMER0_CH1 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER1_OC1: CMP TIMER1_CH1 output compare signal selected as blanking source
      \arg        CMP_BLANKING_TIMER7_OC1: CMP TIMER7_CH1 output compare signal selected as blanking source
    \param[out] none
    \retval     none
*/
void cmp_blanking_init(uint32_t cmp_periph, uint32_t blanking_source_selection)
{
    uint32_t temp;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    }else if(NOT_CMP_BLK_SOURCE_SEL(blanking_source_selection)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp = CMP_CS(cmp_periph);
        temp &= ~(uint32_t)CMP_CS_CMPXBLK;
        temp |= (uint32_t)blanking_source_selection;
        CMP_CS(cmp_periph) = temp;
    }
}

/*!
    \brief      initialize comparator round robin clock (API_ID(0x0006U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  sample_clock:
                only one parameter can be selected which is shown as below:
      \arg        RRCTL_RRSAMCFG_xCLK(x=0,1,2,3)
    \param[in]  init_delay:
                only one parameter can be selected which is shown as below:
      \arg        RRCTL_RRTINIT_xCLK(x=1~63)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_clock_init(uint32_t cmp_periph, uint32_t sample_clock, uint32_t init_delay)
{
    uint32_t temp;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    }else if(NOT_CMP_SAMPLE_CLOCK(sample_clock)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    }else if(CMP_RR_INIT_DELAY_CLOCK(init_delay)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp = CMP_RRCTL(cmp_periph);
        temp &= ~(uint32_t)(CMP_RRCTL_RRSAMCFG | CMP_RRCTL_RRTINIT);
        temp |= (uint32_t)sample_clock | init_delay;
        CMP_RRCTL(cmp_periph) = temp;
    }
}

/*!
    \brief      initialize comparator round robin channel config (API_ID(0x0007U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  specified_port: 
                only one parameter can be selected which is shown as below:
      \arg        CMP_RRINVERTING_PORT: select the inverting port
      \arg        CMP_RRNONINVERTING_PORT: select the non-inverting port
    \param[in]  specified_channel: select comparator round robin fixed channel
                only one parameter can be selected which is shown as below:
      \arg        CMP_RRSPE_CHANNEL_x(x = 0~10)
    \param[in]  non_specified_channel: select comparator round robin non-specified_channel channel
                one or more parameters can be selected which are shown as below:
      \arg        CMP_RRNONSPE_CHANNEL_x(x = 0~10)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_channel_config(uint32_t cmp_periph, uint32_t specified_port, uint32_t specified_channel, uint32_t non_specified_channel)
{
    uint32_t temp;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    }else if(NOT_CMP_SPECIFIED_PORT(specified_port)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    }else if(NOT_CMP_SPECIFIED_CHANNEL(specified_channel)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    }else if(NOT_CMP_NONSPE_CHANNEL(non_specified_channel)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp = CMP_RRCHCTL(cmp_periph);
        temp &= ~(uint32_t)(CMP_RRCHCTL_SPEPS | CMP_RRCHCTL_RRSPECHS);
        temp |= (uint32_t)specified_port | specified_channel | non_specified_channel;
        CMP_RRCHCTL(cmp_periph) = temp;
    }
}
/*  */
/*!
    \brief      initialize comparator round robin non-specified channel pre-set state (API_ID(0x0008U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  non_specified_channel: select all comparator round robin non-specified_channel, which the pre_define channel state should be set
                one or more parameters can be selected which are shown as below:
      \arg        CMP_RRNONSPE_CHANNEL_x(x = 0~10) (all channels of the pre_define need to be written together)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_channel_preset(uint32_t cmp_periph, uint32_t non_specified_channel)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    }else if(NOT_CMP_NONSPE_CHANNEL(non_specified_channel)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRCOMO(cmp_periph) = (uint32_t)non_specified_channel;
    }
    
}

/*!
    \brief      comparator round robin timer trigger value config (API_ID(0x0009U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  value: timer trigger value(0x00000000~0xFFFFFFFF)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_trigger_timer_value_config(uint32_t cmp_periph, uint32_t value)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRTTRGV(cmp_periph) = (uint32_t)value;
    }
}

/*!
    \brief      comparator round robin timer trigger value reload (API_ID(0x000AU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_trigger_timer_value_reload(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRTCTL(cmp_periph) |= (uint32_t)CMP_RRTCTL_UPVAL;
    }
}

/*!
    \brief      comparator round robin timer counter clear (API_ID(0x000BU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_trigger_timer_counter_clear(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRTCTL(cmp_periph) |= (uint32_t)CMP_RRTCTL_CLRCNT;
    }
}

/*!
    \brief      enable comparator (API_ID(0x000CU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_enable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXEN;
    }
}

/*!
    \brief      disable comparator (API_ID(0x000DU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_disable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_CS(cmp_periph) &= ~(uint32_t)CMP_CS_CMPXEN;
    }
}

/*!
    \brief      enable the voltage scaler (API_ID(0x000EU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_voltage_scaler_enable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXSEN;
    }
}

/*!
    \brief      disable the voltage scaler (API_ID(0x000FU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_voltage_scaler_disable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_CS(cmp_periph) &= ~(uint32_t)CMP_CS_CMPXSEN;
    }
}

/*!
    \brief      enable the scaler bridge (API_ID(0x0010U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_scaler_bridge_enable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXBEN;
    }
}

/*!
    \brief      disable the scaler bridge (API_ID(0x0011U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_scaler_bridge_disable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_CS(cmp_periph) &= ~(uint32_t)CMP_CS_CMPXBEN;
    }
}

/*!
    \brief      enable comparator round robin (API_ID(0x0012U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_enable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRCTL(cmp_periph) |= (uint32_t)CMP_RRCTL_RREN;
    }
}

/*!
    \brief      disable comparator round robin (API_ID(0x0013U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_disable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRCTL(cmp_periph) &= ~(uint32_t)CMP_RRCTL_RREN;
    }
}

/*!
    \brief      enable comparator round robin counter (API_ID(0x0014U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_trigger_timer_counter_enable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRTCTL(cmp_periph) |= (uint32_t)CMP_RRTCTL_RRCEN;
    }
}

/*!
    \brief      disable comparator round robin counter (API_ID(0x0015U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_trigger_timer_counter_disable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRTCTL(cmp_periph) &= ~(uint32_t)CMP_RRTCTL_RRCEN;
    }
}

/*!
    \brief      enable comparator round robin trigger (API_ID(0x0016U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_trigger_enable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRTCTL(cmp_periph) |= (uint32_t)CMP_RRTCTL_RRTRGEN;
    }
}

/*!
    \brief      disable comparator round robin trigger (API_ID(0x0017U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_trigger_disable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRTCTL(cmp_periph) &= ~(uint32_t)CMP_RRTCTL_RRTRGEN;
    }
}

/*!
    \brief      lock the comparator (API_ID(0x0018U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_lock_enable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* lock CMP */
        CMP_CS(cmp_periph) |= (uint32_t)CMP_CS_CMPXLK;
    }
}

/*!
    \brief      get output level (API_ID(0x0019U))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     the output level
      \arg        CMP_OUTPUTLEVEL_HIGH: output high level
      \arg        CMP_OUTPUTLEVEL_LOW: output low level
*/
uint32_t cmp_output_level_get(uint32_t cmp_periph)
{
    uint32_t reval = CMP_OUTPUTLEVEL_LOW;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get output level of CMP */
        if((uint32_t)RESET != (CMP_CS(cmp_periph) & CMP_CS_CMPXO)) {
            reval = CMP_OUTPUTLEVEL_HIGH;
        } else {
            reval = CMP_OUTPUTLEVEL_LOW;
        }
    }
    return reval;
}

/*!
    \brief      get comparator round robin non-specified_channel compare result flag (API_ID(0x001AU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  non_specified_channel: select comparator round robin non-specified_channel channel
                only one parameter can be selected which is shown as below:
      \arg        CMP_RRNONSPE_CHANNEL_x(x = 0~10)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cmp_roundrobin_flag_get(uint32_t cmp_periph, uint32_t non_specified_channel)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    }else if(NOT_CMP_NONSPE_CHANNEL(non_specified_channel)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x001AU), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get non-specified_channel flag of CMP */
        if((uint32_t)RESET != (CMP_RRCOMF(cmp_periph) & non_specified_channel)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear comparator round robin non-specified_channel compare result flag (API_ID(0x001BU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[in]  non_specified_channel: select comparator round robin non-specified_channel channel
                one or more parameters can be selected which are shown as below:
      \arg        CMP_RRNONSPE_CHANNEL_x(x = 0~10)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_flag_clear(uint32_t cmp_periph, uint32_t non_specified_channel)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    }else if(NOT_CMP_NONSPE_CHANNEL(non_specified_channel)){
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x001BU), ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRCOMF(cmp_periph) = non_specified_channel;
    }
}

/*!
    \brief      enable comparator round robin interrupt (API_ID(0x001CU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_interrupt_enable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRCTL(cmp_periph) |= (uint32_t)CMP_RRCTL_RRIE;
    }
}

/*!
    \brief      disable comparator round robin interrupt (API_ID(0x001DU))
    \param[in]  cmp_periph: CMPx(x=0,1)
    \param[out] none
    \retval     none
*/
void cmp_roundrobin_interrupt_disable(uint32_t cmp_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CMP_PERIPH(cmp_periph)) {
        fw_debug_report_err(CMP_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        CMP_RRCTL(cmp_periph) &= ~(uint32_t)CMP_RRCTL_RRIE;
    }
}
