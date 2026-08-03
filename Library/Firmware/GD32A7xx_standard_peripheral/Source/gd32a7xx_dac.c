/*!
    \file    gd32a7xx_dac.c
    \brief   DAC driver

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

#include "gd32a7xx_dac.h"

#define DAC_WATI_TIME_MASK          ((uint32_t)0x000000FFU)
#define DAC_STAT_FLAG_MASK0         (DAC_FLAG_LTOVIF | DAC_FLAG_LTDIF | DAC_FLAG_DDUDR0)
#define DAC_INT_EN_MASK0            (DAC_INT_DDUDR0)
#define DAC_INT_EN_MASK1            (DAC_INT_LTDIF | DAC_INT_LTOVIF)
#define DAC_INT_FLAG_MASK0          (DAC_INT_FLAG_DDUDR0)
#define DAC_INT_FLAG_MASK1          (DAC_INT_FLAG_LTOVIF | DAC_INT_FLAG_LTDIF)
#define DAC_REG_DEFAULT_VALUE       ((uint32_t)0x00000000U)

/*!
    \brief      deinitialize DAC (API_ID(0x0001U))
    \param[in]  dac_periph: DACx(x=0,1)
    \param[out] none
    \retval     none
*/
void dac_deinit(uint32_t dac_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0001), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DEN0);
        DAC_CTL0(dac_periph) = DAC_REG_DEFAULT_VALUE;
        DAC_SWT(dac_periph) = DAC_REG_DEFAULT_VALUE;
        DAC_OUT0_R12DH(dac_periph) = DAC_REG_DEFAULT_VALUE;
        DAC_OUT0_L12DH(dac_periph) = DAC_REG_DEFAULT_VALUE;
        DAC_OUT0_R8DH(dac_periph) = DAC_REG_DEFAULT_VALUE;
        DAC_OUT0_DO(dac_periph) = DAC_REG_DEFAULT_VALUE;
        DAC_STAT0(dac_periph) = DAC_REG_DEFAULT_VALUE;
        DAC_LTCTL(dac_periph) = DAC_REG_DEFAULT_VALUE;
        DAC_LTPAT(dac_periph) = DAC_REG_DEFAULT_VALUE;
        switch(dac_periph){
            case DAC0:
                /* assign default values to registers */
                /* reset DAC0 */
                rcu_periph_reset_enable(RCU_DAC0RST);
                rcu_periph_reset_disable(RCU_DAC0RST);
                break;
            case DAC1:
                /* assign default values to registers */
                /* reset DAC1 */
                rcu_periph_reset_enable(RCU_DAC1RST);
                rcu_periph_reset_disable(RCU_DAC1RST);
                break;
            default:
                break;
        }
    }
}

/*!
    \brief      enable DAC (API_ID(0x0002U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_enable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0002), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_CTL0(dac_periph) |= (uint32_t)DAC_CTL0_DEN0;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      disable DAC (API_ID(0x0003U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_disable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0003), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DEN0);
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      enable DAC DMA function (API_ID(0x0004U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_dma_enable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0004), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_CTL0(dac_periph) |= (uint32_t)DAC_CTL0_DDMAEN0;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      disable DAC DMA function (API_ID(0x0005U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_dma_disable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0005), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DDMAEN0);
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      configure GPIO connection (API_ID(0x0006U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  gpio_connect: DAC_OUTx connect GPIO mode
                only one parameter can be selected which is shown as below:
      \arg        PIN_PERIPHERAL: DAC_OUTx(x=0) connected to the external pin and on chip peripherals(CMP)
      \arg        PIN_PERIPHERAL_BUFFER: Whether DAC_OUTx(x=0) is connected to external pin and on chip peripherals(CMP) depends on the output buffer
    \param[out] none
    \retval     none
*/
void dac_gpio_connect_config(uint32_t dac_periph, uint8_t dac_out, uint32_t gpio_connect)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0006), ERR_PERIPH);
    }else if (NOT_DAC_DDISC0(gpio_connect)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0006), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            /* configure GPIO connection */
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DDISC0);
            DAC_CTL0(dac_periph) |= gpio_connect;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      enable DAC output buffer (API_ID(0x0007U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_output_buffer_enable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0007), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DBOFF0);
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      disable DAC output buffer (API_ID(0x0008U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_output_buffer_disable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0008), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_CTL0(dac_periph) |= (uint32_t)DAC_CTL0_DBOFF0;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      get DAC output value (API_ID(0x0009U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     DAC output data: 0~4095
*/
uint16_t dac_output_value_get(uint32_t dac_periph, uint8_t dac_out)
{
    uint16_t data = 0U;
    
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0009), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            /* store the DACx_OUT0 output value */
            data = (uint16_t)DAC_OUT0_DO(dac_periph);
        } else {
            /* illegal parameters */
        }
    }
    
    return data;
}

/*!
    \brief      set DAC data holding register value (API_ID(0x000AU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  dac_align: DAC data alignment mode
                only one parameter can be selected which is shown as below:
      \arg        DAC_ALIGN_12B_R: 12-bit right-aligned data
      \arg        DAC_ALIGN_12B_L: 12-bit left-aligned data
      \arg        DAC_ALIGN_8B_R: 8-bit right-aligned data
    \param[in]  data: data to be loaded(0~4095)
    \param[out] none
    \retval     none
*/
void dac_data_set(uint32_t dac_periph, uint8_t dac_out, uint32_t dac_align, uint16_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000A), ERR_PERIPH);
    } else if(NOT_DAC_ALIGN(dac_align)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000A), ERR_PARAM_INVALID);
    } else if((DAC_ALIGN_12B_R == dac_align) && NOT_DAC_R12DATA_RANGE(data)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000A), ERR_PARAM_OUT_OF_RANGE);
    } else if((DAC_ALIGN_12B_L == dac_align) && NOT_DAC_L12DATA_RANGE(data)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000A), ERR_PARAM_OUT_OF_RANGE);
    } else if(DAC_ALIGN_8B_R == dac_align && NOT_DAC_R8DATA_RANGE(data)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000A), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* DAC_OUT0 data alignment */
        if(DAC_OUT0 == dac_out){
            switch(dac_align){
            /* 12-bit right-aligned data */
            case DAC_ALIGN_12B_R:
                DAC_OUT0_R12DH(dac_periph) = data;
                break;
            /* 12-bit left-aligned data */
            case DAC_ALIGN_12B_L:
                DAC_OUT0_L12DH(dac_periph) = data;
                break;
            /* 8-bit right-aligned data */
            case DAC_ALIGN_8B_R:
                DAC_OUT0_R8DH(dac_periph) = data;
                break;
            default:
                break;
            }
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      enable DAC trigger (API_ID(0x000BU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_trigger_enable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000B), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_CTL0(dac_periph) |= (uint32_t)DAC_CTL0_DTEN0;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      disable DAC trigger (API_ID(0x000CU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[out] none
    \retval     none
*/
void dac_trigger_disable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000C), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DTEN0);
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      configure DAC trigger source (API_ID(0x000DU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  triggersource: external trigger of DAC
                only one parameter can be selected which is shown as below:
      \arg        DAC_TRIGGER_EXTERNAL: TRIGSEL trigger
      \arg        DAC_TRIGGER_SOFTWARE: software trigger
    \param[out] none
    \retval     none
*/
void dac_trigger_source_config(uint32_t dac_periph, uint8_t dac_out, uint32_t triggersource)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000D), ERR_PERIPH);
    } else if(NOT_DAC_TRIGGER(triggersource)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000D), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            /* configure DACx_OUT0 trigger source */
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DTSEL0);
            DAC_CTL0(dac_periph) |= triggersource;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      enable DAC software trigger (API_ID(0x000EU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \retval     none
*/
void dac_software_trigger_enable(uint32_t dac_periph, uint8_t dac_out)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000E), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            DAC_SWT(dac_periph) |= (uint32_t)DAC_SWT_SWTR0;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      configure DAC wave mode (API_ID(0x000FU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  wave_mode: DAC wave mode
                only one parameter can be selected which is shown as below:
      \arg        DAC_WAVE_DISABLE: wave mode disable
      \arg        DAC_WAVE_MODE_LFSR: LFSR noise mode
      \arg        DAC_WAVE_MODE_TRIANGLE: triangle noise mode
    \param[out] none
    \retval     none
*/
void dac_wave_mode_config(uint32_t dac_periph, uint8_t dac_out, uint32_t wave_mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000F), ERR_PERIPH);
    } else if(NOT_DAC_WAVE_MODE(wave_mode)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x000F), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            /* configure DACx_OUT0 wave mode */
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DWM0);
            DAC_CTL0(dac_periph) |= wave_mode;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      configure DAC LFSR noise mode (API_ID(0x0010U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  unmask_bits: LFSR noise unmask bits
                only one parameter can be selected which is shown as below:
      \arg        DAC_LFSR_BIT0: unmask the LFSR bit0
      \arg        DAC_LFSR_BITS1_0: unmask the LFSR bits[1:0]
      \arg        DAC_LFSR_BITS2_0: unmask the LFSR bits[2:0]
      \arg        DAC_LFSR_BITS3_0: unmask the LFSR bits[3:0]
      \arg        DAC_LFSR_BITS4_0: unmask the LFSR bits[4:0]
      \arg        DAC_LFSR_BITS5_0: unmask the LFSR bits[5:0]
      \arg        DAC_LFSR_BITS6_0: unmask the LFSR bits[6:0]
      \arg        DAC_LFSR_BITS7_0: unmask the LFSR bits[7:0]
      \arg        DAC_LFSR_BITS8_0: unmask the LFSR bits[8:0]
      \arg        DAC_LFSR_BITS9_0: unmask the LFSR bits[9:0]
      \arg        DAC_LFSR_BITS10_0: unmask the LFSR bits[10:0]
      \arg        DAC_LFSR_BITS11_0: unmask the LFSR bits[11:0]
    \param[out] none
    \retval     none
*/
void dac_lfsr_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t unmask_bits)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0010), ERR_PERIPH);
    } else if(NOT_DAC_LFSR_MODE(unmask_bits)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0010), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            /* configure DACx_OUT0 LFSR noise mode */
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DWBW0);
            DAC_CTL0(dac_periph) |= unmask_bits;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      configure DAC triangle noise mode (API_ID(0x0011U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_out: DAC_OUTx(x=0)
    \param[in]  amplitude: the amplitude of the triangle
                only one parameter can be selected which is shown as below:
      \arg        DAC_TRIANGLE_AMPLITUDE_1: triangle amplitude is 1
      \arg        DAC_TRIANGLE_AMPLITUDE_3: triangle amplitude is 3
      \arg        DAC_TRIANGLE_AMPLITUDE_7: triangle amplitude is 7
      \arg        DAC_TRIANGLE_AMPLITUDE_15: triangle amplitude is 15
      \arg        DAC_TRIANGLE_AMPLITUDE_31: triangle amplitude is 31
      \arg        DAC_TRIANGLE_AMPLITUDE_63: triangle amplitude is 63
      \arg        DAC_TRIANGLE_AMPLITUDE_127: triangle amplitude is 127
      \arg        DAC_TRIANGLE_AMPLITUDE_255: triangle amplitude is 255
      \arg        DAC_TRIANGLE_AMPLITUDE_511: triangle amplitude is 511
      \arg        DAC_TRIANGLE_AMPLITUDE_1023: triangle amplitude is 1023
      \arg        DAC_TRIANGLE_AMPLITUDE_2047: triangle amplitude is 2047
      \arg        DAC_TRIANGLE_AMPLITUDE_4095: triangle amplitude is 4095
    \param[out] none
    \retval     none
*/
void dac_triangle_noise_config(uint32_t dac_periph, uint8_t dac_out, uint32_t amplitude)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0011), ERR_PERIPH);
    } else if(NOT_DAC_TRIANGLE_AMPL(amplitude)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0011), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DAC_OUT0 == dac_out){
            /* configure DACx_OUT0 triangle noise mode */
            DAC_CTL0(dac_periph) &= (uint32_t)(~DAC_CTL0_DWBW0);
            DAC_CTL0(dac_periph) |= amplitude;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      enable DAC loop test (API_ID(0x0012U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[out] none
    \retval     none
*/
void dac_loop_test_enable(uint32_t dac_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0012), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DAC_LTCTL(dac_periph) |= (uint32_t)DAC_LTCTL_LTEN;
    }
}

/*!
    \brief      disable DAC loop test (API_ID(0x0013U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[out] none
    \retval     none
*/
void dac_loop_test_disable(uint32_t dac_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0013), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DAC_LTCTL(dac_periph) &= ~(uint32_t)DAC_LTCTL_LTEN;
    }
}

/*!
    \brief      DAC loop test FIFO flush (API_ID(0x0014U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[out] none
    \retval     none
*/
void dac_loop_test_fifo_flush(uint32_t dac_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0014), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DAC_LTCTL(dac_periph) |= (uint32_t)DAC_LTCTL_LTFF;
    }
}

/*!
    \brief      configure DAC loop test wait time (API_ID(0x0015U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_looptest_wait_time: 0x00~0xFF
    \param[out] none
    \retval     none
*/
void dac_loop_test_wait_time(uint32_t dac_periph, uint8_t dac_looptest_wait_time)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0015), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DAC_LTCTL(dac_periph) &= ~(uint32_t)(DAC_LTCTL_LTWT); 
        DAC_LTCTL(dac_periph) |= (uint32_t)((((uint32_t)dac_looptest_wait_time) & DAC_WATI_TIME_MASK) << 16U);
    }
}

/*!
    \brief      get the remaining number of loop test pattern to be converted (API_ID(0x0016U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[out] none
    \retval     the remaining number:0x0~0x8
*/
uint16_t dac_loop_test_remaining_number_read(uint32_t dac_periph)
{
    uint16_t lpnum = 0;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0016), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        lpnum = (uint16_t)((DAC_LTCTL(dac_periph) & DAC_LTCTL_LTCNUM)>>28);
    }
   return (lpnum);
}

/*!
    \brief      write loop test pattern in to FIFO (API_ID(0x0017U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  dac_looptest_pattern: 0x000~0xFFF
    \param[out] none
    \retval     none
*/
void dac_loop_test_pattern(uint32_t dac_periph, uint32_t dac_looptest_pattern)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0017), ERR_PERIPH);
    } else if(NOT_DAC_LPTEST_PATTERN(dac_looptest_pattern)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0017), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DAC_LTPAT(dac_periph) = (uint32_t)(dac_looptest_pattern);
    }
}

/*!
    \brief      get the DAC flag (API_ID(0x0018U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  flag: the DAC status flags, only one parameter can be selected which is shown
                as below:
      \arg        DAC_FLAG_LTOVIF: loop test overflow interrupt flag
      \arg        DAC_FLAG_LTDIF: loop test done interrupt flag
      \arg        DAC_FLAG_DDUDR0: DACx_OUT0 DMA underrun flag
    \param[out] none
    \retval     the state of DAC bit(SET or RESET)
*/
FlagStatus dac_flag_get(uint32_t dac_periph, uint32_t flag)
{
    FlagStatus reval = RESET;
    uint32_t reg;
    
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0018), ERR_PERIPH);
    } else if(NOT_DAC_FLAG(flag)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0018), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = DAC_STAT0(dac_periph);
        if((0U != (flag & DAC_STAT_FLAG_MASK0)) && (0U != (reg & flag))){
            /* check DAC_STAT0 flag */
            reval = SET;
        } else {
            /* illegal parameters */
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear the DAC flag (API_ID(0x0019U))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  flag: DAC flag
                only one parameter can be selected which is shown as below:
      \arg        DAC_FLAG_LTOVIF: loop test overflow interrupt flag
      \arg        DAC_FLAG_LTDIF: loop test done interrupt flag
      \arg        DAC_FLAG_DDUDR0: DACx_OUT0 DMA underrun flag
    \param[out] none
    \retval     none
*/
void dac_flag_clear(uint32_t dac_periph, uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x0019), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (flag & DAC_STAT_FLAG_MASK0)){
            /* check DAC_STAT0 flag */
            DAC_STAT0(dac_periph) = (uint32_t)(flag & DAC_STAT_FLAG_MASK0);
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      enable DAC interrupt (API_ID(0x001AU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  interrupt: the DAC interrupt
                only one parameter can be selected which is shown as below:
      \arg        DAC_INT_LTOVIF: loop test overflow interrupt
      \arg        DAC_INT_LTDIF: loop test done interrupt
      \arg        DAC_INT_DDUDR0: DACx_OUT0 DMA underrun interrupt     
    \param[out] none
    \retval     none
*/
void dac_interrupt_enable(uint32_t dac_periph, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x001A), ERR_PERIPH);
    } else if(NOT_DAC_INT(interrupt)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x001A), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (interrupt & DAC_INT_EN_MASK0)){
            /* enable underrun interrupt */
            DAC_CTL0(dac_periph) |= (uint32_t)(interrupt & DAC_INT_EN_MASK0);
        } else {
            /* illegal parameters */
        }
        
        if(0U != (interrupt & DAC_INT_EN_MASK1)){
            /* enable loop test done and overflow interrupt */
            DAC_LTCTL(dac_periph) |= (uint32_t)(interrupt & DAC_INT_EN_MASK1);
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      disable DAC interrupt (API_ID(0x001BU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  interrupt: the DAC interrupt
                only one parameter can be selected which is shown as below:
      \arg        DAC_INT_LTOVIF: loop test overflow interrupt
      \arg        DAC_INT_LTDIF: loop test done interrupt
      \arg        DAC_INT_DDUDR0: DACx_OUT0 DMA underrun interrupt
    \param[out] none
    \retval     none
*/
void dac_interrupt_disable(uint32_t dac_periph, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x001B), ERR_PERIPH);
    } else if(NOT_DAC_INT(interrupt)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x001B), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (interrupt & DAC_INT_EN_MASK0)){
            /* disable underrun interrupt */
            DAC_CTL0(dac_periph) &= (uint32_t)(~(interrupt & DAC_INT_EN_MASK0));
        } else {
            /* illegal parameters */
        }
        
        if(0U != (interrupt & DAC_INT_EN_MASK1)){
            /* disable loop test done and overflow interrupt */
            DAC_LTCTL(dac_periph) &= (uint32_t)(~(interrupt & DAC_INT_EN_MASK1));
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      get the DAC interrupt flag (API_ID(0x001CU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  int_flag: DAC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        DAC_INT_FLAG_LTOVIF: loop test overflow interrupt flag
      \arg        DAC_INT_FLAG_LTDIF: loop test done interrupt flag
      \arg        DAC_INT_FLAG_DDUDR0: DACx_OUT0 DMA underrun interrupt flag
    \param[out] none
    \retval     the state of DAC interrupt flag(SET or RESET)
*/
FlagStatus dac_interrupt_flag_get(uint32_t dac_periph, uint32_t int_flag)
{
    uint32_t reg1 = 0U, reg2 = 0U;
    FlagStatus reval = RESET;
    
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x001C), ERR_PERIPH);
    } else if(NOT_DAC_INT_FLAG(int_flag)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x001C), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (int_flag & DAC_INT_FLAG_MASK0)){
            /* check underrun interrupt int_flag */
            reg1 = DAC_STAT0(dac_periph) & int_flag;
            reg2 = DAC_CTL0(dac_periph) & int_flag;
        } else {
            /* illegal parameters */
        }
        
        if(0U != (int_flag & DAC_INT_FLAG_MASK1)){
            /* check loop test done and overflow int_flag */
            reg1 = DAC_STAT0(dac_periph) & int_flag;
            reg2 = DAC_LTCTL(dac_periph) & int_flag;
        } else {
            /* illegal parameters */
        }

        /*get DAC interrupt flag status */
        if((0U != reg1) && (0U != reg2)){
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    
    return reval;
}

/*!
    \brief      clear the DAC interrupt flag (API_ID(0x001DU))
    \param[in]  dac_periph: DACx(x=0, 1)
    \param[in]  int_flag: DAC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        DAC_INT_FLAG_LTOVIF: loop test overflow interrupt flag
      \arg        DAC_INT_FLAG_LTDIF: loop test done interrupt flag
      \arg        DAC_INT_FLAG_DDUDR0: DACx_OUT0 DMA underrun interrupt flag
    \param[out] none
    \retval     none
*/
void dac_interrupt_flag_clear(uint32_t dac_periph, uint32_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DAC_PERIPH(dac_periph)){
        fw_debug_report_err(DAC_MODULE_ID, API_ID(0x001D), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear underrun interrupt int_flag */
        if(0U != (int_flag & (DAC_INT_FLAG_MASK0 | DAC_INT_FLAG_MASK1))){
            DAC_STAT0(dac_periph) = (uint32_t)(int_flag & (DAC_INT_FLAG_MASK0 | DAC_INT_FLAG_MASK1));
        } else {
            /* illegal parameters */
        }
    }
}
