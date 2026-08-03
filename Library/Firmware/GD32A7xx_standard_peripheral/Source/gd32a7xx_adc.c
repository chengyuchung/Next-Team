/*!
    \file    gd32a7xx_adc.c
    \brief   ADC driver

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

/*!
    \page    misra_violations MISRA-C:2012 violations

    \section [MISRA-C:2012]
             Violates MISRA C:2012 Rule-16.1 (Required) All switch statements shall be well-formed.
             The for loop statement is necessary in the switch statement, otherwise, it will increase the amount of code.
*/

#include "gd32a7xx_adc.h"

/*!
    \brief      reset ADC (API_ID(0x0001U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     none
*/
void adc_deinit(uint32_t adc_periph)
{
    uint32_t i;
    uint32_t j;
    uint32_t x;
    uint32_t y;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* reset ADC registers */
        ADC_CTL(adc_periph) = ADC_RESET_VALUE;
        ADC_STAT(adc_periph) = ADC_STAT_RESET_VALUE;
        for(i = 0x02U; i < 0x50U; i ++){
            x = i;
            REG32((adc_periph) + (x*0x04U)) = ADC_RESET_VALUE;
        }
        /* reset routine sequence registers */
        for(i = 0x80U; i < 0xBCU; i ++){
            x = i;
            REG32((adc_periph) + (x*0x04U)) = ADC_RESET_VALUE;
        }
        /* reset inserted sequence registers */
        for(j = 0x00U; j < 0x06U; j ++){
            for(i = 0xC0U; i < 0x108U; i ++){
                x = i;
                y = j;
                REG32((adc_periph) + (x*0x04U)+(y*0x50U)) = ADC_RESET_VALUE;
            }
        }
        /* reset selftest sequence registers */
        for(i = 0x180U; i < 0x187U; i ++){
            x = i;
            REG32((adc_periph) + (x*0x00000004U)) = ADC_RESET_VALUE;
        }
        ADC_SSTWDCFGx(adc_periph, 0U) = ADC_SSTWDCFG0_RESET_VALUE;
        ADC_SSTWDCFGx(adc_periph, 1U) = ADC_SSTWDCFG1_RESET_VALUE;
        ADC_SSTWDCFGx(adc_periph, 2U) = ADC_SSTWDCFG2_RESET_VALUE;
        ADC_CSTWDCFGx(adc_periph, 0U) = ADC_CSTWDCFGx_RESET_VALUE;
        ADC_CSTWDCFGx(adc_periph, 1U) = ADC_CSTWDCFGx_RESET_VALUE;
        ADC_CSTWDCFGx(adc_periph, 2U) = ADC_CSTWDCFGx_RESET_VALUE;
        ADC_CSTWDCFGx(adc_periph, 3U) = ADC_CSTWDCFG3_RESET_VALUE;
        ADC_DTALTCFG(adc_periph) = ADC_RESET_VALUE;

        switch(adc_periph) {
        case ADC0:
            rcu_periph_reset_enable(RCU_ADC0RST);
            rcu_periph_reset_disable(RCU_ADC0RST);
            break;
        case ADC1:
            rcu_periph_reset_enable(RCU_ADC1RST);
            rcu_periph_reset_disable(RCU_ADC1RST);
            break;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case ADC2:
            rcu_periph_reset_enable(RCU_ADC2RST);
            rcu_periph_reset_disable(RCU_ADC2RST);
            break;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        default:
            break;
        }
    }
}

/*!
    \brief      enable ADC interface (API_ID(0x0002U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     none
*/
void adc_enable(uint32_t adc_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0002U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U == (ADC_CTL(adc_periph) & ADC_CTL_ADCON)) {
            /* enable ADC */
            ADC_CTL(adc_periph) |= (uint32_t)ADC_CTL_ADCON;
        }else{
            /* illegal parameters */
        }
    }
}

/*!
    \brief      disable ADC interface (API_ID(0x0003U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     none
*/
void adc_disable(uint32_t adc_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable ADC */
        ADC_CTL(adc_periph) &= ~((uint32_t)ADC_CTL_ADCON);
    }
}

/*!
    \brief      configure ADC data alignment (API_ID(0x0004U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  data_alignment: data alignment select
                only one parameter can be selected which is shown as below:
      \arg        ADC_DATAALIGN_RIGHT: right alignment
      \arg        ADC_DATAALIGN_LEFT: left alignment
    \param[out] none
    \retval     none
*/
void adc_data_alignment_config(uint32_t adc_periph, uint32_t data_alignment)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else if(NOT_ADC_DATA_ALIGNMENT(data_alignment)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CTL(adc_periph) &= ~((uint32_t)ADC_CTL_DAL);
        ADC_CTL(adc_periph) |= (uint32_t)data_alignment;
    }
}

/*!
    \brief      configure ADC resolution (API_ID(0x0005U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  resolution: ADC resolution
                only one parameter can be selected which is shown as below:
      \arg        ADC_RESOLUTION_12B: 12-bit ADC resolution
      \arg        ADC_RESOLUTION_10B: 10-bit ADC resolution
      \arg        ADC_RESOLUTION_8B: 8-bit ADC resolution
      \arg        ADC_RESOLUTION_6B: 6-bit ADC resolution
    \param[out] none
    \retval     none
*/
void adc_resolution_config(uint32_t adc_periph, uint32_t resolution)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else if(NOT_ADC_RESOLUTION(resolution)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CTL(adc_periph) &= ~((uint32_t)ADC_CTL_DRES);
        ADC_CTL(adc_periph) |= (uint32_t)resolution;
    }
}

/*!
    \brief      configure the ADC sync mode (API_ID(0x0006U))
    \param[in]  mode: ADC mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_MODE_FREE: all the ADCs work independently
      \arg        ADC_DUAL_ROUTINE_PARALLEL_INSERTED_PARALLEL: ADC0 and ADC1 work in combined routine parallel + inserted parallel mode
      \arg        ADC_DUAL_ROUTINE_PARALLEL_ROTATION: ADC0 and ADC1 work in combined routine parallel + trigger rotation mode
      \arg        ADC_DUAL_INSERTED_PARALLEL: ADC0 and ADC1 work in inserted parallel mode
      \arg        ADC_DUAL_ROUTINE_PARALLEL: ADC0 and ADC1 work in routine parallel mode
      \arg        ADC_DUAL_FOLLOWUP: ADC0 and ADC1 work in follow-up mode
      \arg        ADC_DUAL_TRRIGGER_ROTATION: ADC0 and ADC1 work in trigger rotation mode
      \arg        ADC_ALL_ROUTINE_PARALLEL_INSERTED_PARALLEL: ADC0, ADC1 and ADC2 work in combined routine parallel + inserted parallel mode (only available in GD32A714X, GD32A72XX and GD32A74XX)
      \arg        ADC_ALL_ROUTINE_PARALLEL_ROTATION: ADC0, ADC1 and ADC2 work in combined routine parallel + trigger rotation mode (only available in GD32A714X, GD32A72XX and GD32A74XX)
      \arg        ADC_ALL_INSERTED_PARALLEL: ADC0, ADC1 and ADC2 work in inserted parallel mode (only available in GD32A714X, GD32A72XX and GD32A74XX)
      \arg        ADC_ALL_ROUTINE_PARALLEL: ADC0, ADC1 and ADC2 work in routine parallel mode (only available in GD32A714X, GD32A72XX and GD32A74XX)
      \arg        ADC_ALL_FOLLOWUP: ADC0, ADC1 and ADC2 work in follow-up mode (only available in GD32A714X, GD32A72XX and GD32A74XX)
      \arg        ADC_ALL_TRRIGGER_ROTATION: ADC0, ADC1 and ADC2 work in trigger rotation mode (only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     none
*/
void adc_mode_config(uint32_t mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_mode(mode)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_SYNCCTL &= ~((uint32_t)ADC_SYNCCTL_SYNCM);
        ADC_SYNCCTL |= mode;
    }
}

/*!
    \brief      configure ADC internal channels (API_ID(0x0007U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  internal_channel: the internal channels
                only one parameter can be selected which is shown as below:
      \arg        ADC_CHANNEL_INTERNAL_VREFINT: internal reference voltage vrefint channel
      \arg        ADC_CHANNEL_INTERNAL_HP_TEMPSENSOR: high-precision temperature sensor channel
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_internal_channel_config(uint32_t adc_periph, uint32_t internal_channel, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else if(NOT_ADC_INTERNAL_CHANNEL(internal_channel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            ADC_CTL(adc_periph) |= (uint32_t)internal_channel;
        } else {
            ADC_CTL(adc_periph) &= ~((uint32_t)internal_channel);
        }
    }
}

/*!
    \brief      configure ADC calibration mode (API_ID(0x0008U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  clb_mode: calibration mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_CALIBRATION_OFFSET_MISMATCH: ADC calibration offset and mismatch mode
      \arg        ADC_CALIBRATION_OFFSET: ADC calibration offset mode
    \param[out] none
    \retval     none
*/
void adc_calibration_mode_config(uint32_t adc_periph, uint32_t clb_mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else if(NOT_ADC_CALIBRATION_MODE(clb_mode)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CTL(adc_periph) &= ~((uint32_t)ADC_CTL_CALMOD);
        ADC_CTL(adc_periph) |= clb_mode;
    }
}

/*!
    \brief      configure ADC calibration number (API_ID(0x0009U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  cal_num: calibration number
                only one parameter can be selected which is shown as below:
      \arg        ADC_CALIBRATION_NUM1: calibrate 1 time
      \arg        ADC_CALIBRATION_NUM3: calibrate 3 times
      \arg        ADC_CALIBRATION_NUM7: calibrate 7 times
      \arg        ADC_CALIBRATION_NUM15: calibrate 15 times
      \arg        ADC_CALIBRATION_NUM31: calibrate 31 times
    \param[out] none
    \retval     none
*/
void adc_calibration_number(uint32_t adc_periph, uint32_t cal_num)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else if(NOT_ADC_CALIBRATION_NUMBER(cal_num)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = ADC_CTL(adc_periph);
        reg &= ~((uint32_t)ADC_CTL_CALNUM);
        reg |= cal_num;
        ADC_CTL(adc_periph) = reg;
    }
}

/*!
    \brief      ADC calibration and reset calibration (API_ID(0x000AU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     ErrStatus: status of error (ERROR or SUCCESS)
*/
ErrStatus adc_calibration_enable(uint32_t adc_periph)
{
    uint32_t timerout = ADC_CALIBRATION_TIMEROUT;
    ErrStatus status = ERROR;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* reset the selected ADC calibration registers */
        ADC_CTL(adc_periph) |= (uint32_t) ADC_CTL_RSTCLB;
        /* check the RSTCLB bit state */
        while((0U != (ADC_CTL(adc_periph) & ADC_CTL_RSTCLB)) && (0U != timerout)) {
            timerout --;
        }

        if(0U != (ADC_CTL(adc_periph) & ADC_CTL_RSTCLB)) {
            /* illegal parameters */
        } else {
            /* enable ADC calibration process */
            ADC_CTL(adc_periph) |= ADC_CTL_CLB;
            /* check the CLB bit state */
            while((0U != (ADC_CTL(adc_periph) & ADC_CTL_CLB)) && (0U != timerout)) {
                timerout --;
            }
            
            if(0U != (ADC_CTL(adc_periph) & ADC_CTL_CLB)) {
                /* illegal parameters */
            } else {
                status = SUCCESS;
            }
        }
    }
    return status;
}

/*!
    \brief      enable DMA request (API_ID(0x000BU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     none
*/
void adc_dma_mode_enable(uint32_t adc_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CTL(adc_periph) |= (uint32_t)ADC_CTL_DMA;
    }
}

/*!
    \brief      disable DMA request (API_ID(0x000CU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     none
*/
void adc_dma_mode_disable(uint32_t adc_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CTL(adc_periph) &= ~((uint32_t)ADC_CTL_DMA);
    }
}

/*!
    \brief      enable ADC sequence DMA request (API_ID(0x000DU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     none
*/
void adc_sequence_dma_enable(uint32_t adc_periph, uint32_t adc_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RDATA(adc_periph) |= ((uint32_t)ADC_RDATA_RDMAEN);
        } else {
            ADC_IxDATA(adc_periph, adc_sequence) |= ((uint32_t)ADC_IDATA_IDMAEN);
        }
    }
}

/*!
    \brief      disable ADC sequence DMA request (API_ID(0x000EU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     none
*/
void adc_sequence_dma_disable(uint32_t adc_periph, uint32_t adc_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RDATA(adc_periph) &= ~((uint32_t)ADC_RDATA_RDMAEN);
        } else {
            ADC_IxDATA(adc_periph, adc_sequence) &= ~((uint32_t)ADC_IDATA_IDMAEN);
        }
    }
}

/*!
    \brief      enable ADC sequence channel dma request (API_ID(0x000FU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     none
*/
void adc_sequence_channel_dma_enable(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x000FU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCFGx(adc_periph, rank) |= ((uint32_t)ADC_RCFG_RCHDMAEN);
        } else {
            ADC_IxCFGy(adc_periph, adc_sequence, rank) |= ((uint32_t)ADC_ICFG_ICHDMAEN);
        }
    }
}

/*!
    \brief      disable ADC sequence channel dma request (API_ID(0x0010U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     none
*/
void adc_sequence_channel_dma_disable(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0010U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCFGx(adc_periph, rank) &= ~((uint32_t)ADC_RCFG_RCHDMAEN);
        } else {
            ADC_IxCFGy(adc_periph, adc_sequence, rank) &= ~((uint32_t)ADC_ICFG_ICHDMAEN);
        }
    }
}

/*!
    \brief      when DMA=1, the DMA engine issues a request at end of each conversion (API_ID(0x0011U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_enable(uint32_t adc_periph, uint32_t adc_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0011U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCTL(adc_periph) |= ((uint32_t)ADC_RCTL_RDDM);
        } else {
            ADC_IxCTL(adc_periph, adc_sequence) |= ((uint32_t)ADC_ICTL_IDDM);
        }
    }
}

/*!
    \brief      the DMA engine is disabled after the end of transfer signal from DMA controller is detected (API_ID(0x0012U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     none
*/
void adc_dma_request_after_last_disable(uint32_t adc_periph, uint32_t adc_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCTL(adc_periph) &= ~((uint32_t)ADC_RCTL_RDDM);
        } else {
            ADC_IxCTL(adc_periph, adc_sequence) &= ~((uint32_t)ADC_ICTL_IDDM);
        }
    }
}

/*!
    \brief      configure ADC average conversion (API_ID(0x0013U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_average_config(uint32_t adc_periph, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            ADC_CTL(adc_periph) |= ADC_CTL_AVRGEN;
        } else {
            ADC_CTL(adc_periph) &= ~ADC_CTL_AVRGEN;
        }
    }
}

/*!
    \brief      configure ADC average conversion number (API_ID(0x0014U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  aver_num: average number
                only one parameter can be selected which is shown as below:
      \arg        ADC_AVERAGE_2_CONVERSIONS: 2 conversion data average
      \arg        ADC_AVERAGE_4_CONVERSIONS: 4 conversion data average
      \arg        ADC_AVERAGE_8_CONVERSIONS: 8 conversion data average
      \arg        ADC_AVERAGE_16_CONVERSIONS: 16 conversion data average
      \arg        ADC_AVERAGE_32_CONVERSIONS: 32 conversion data average
      \arg        ADC_AVERAGE_64_CONVERSIONS: 64 conversion data average
      \arg        ADC_AVERAGE_128_CONVERSIONS: 128 conversion data average
      \arg        ADC_AVERAGE_256_CONVERSIONS: 256 conversion data average
    \param[out] none
    \retval     none
*/
void adc_average_number_config(uint32_t adc_periph, uint32_t aver_num)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    } else if(NOT_ADC_AVERAGE_NUMBER(aver_num)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0014U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = ADC_CTL(adc_periph);

        reg &= ~((uint32_t)ADC_CTL_AVRGSEL);
        reg |= aver_num;
        ADC_CTL(adc_periph) = reg;
    }
}

/*!
    \brief      configure ADC overwrite mode (API_ID(0x0015U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_overwrite_config(uint32_t adc_periph, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            ADC_CTL(adc_periph) |= ADC_CTL_OVWEN;
        } else {
            ADC_CTL(adc_periph) &= ~ADC_CTL_OVWEN;
        }
    }
}

/*!
    \brief      configure the ADC idle state clock (API_ID(0x0016U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  ack_cfg: auto clock configure
                only one parameter can be selected which is shown as below:
      \arg        ADC_CLOCK_IDLE_STATE_ON: clock on
      \arg        ADC_CLOCK_IDLE_STATE_OFF: clock automatic off when the ADC in idle state
    \param[out] none
    \retval     none
*/
void adc_auto_clock_config(uint32_t adc_periph, uint32_t ack_cfg)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    } else if(NOT_ADC_AUTO_CLOCK(ack_cfg)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0016U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CTL(adc_periph) &= ~((uint32_t)ADC_CTL_CKAUTO);
        ADC_CTL(adc_periph) |= ack_cfg;
    }
}

/*!
    \brief      configure the ADC external analog multiplexers decode signals delay (API_ID(0x0017U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  external_delay: external decode signals delay, it can be 0~0xFFFF
    \param[out] none
    \retval     none
*/
void adc_external_decode_signals_delay_config(uint32_t adc_periph, uint32_t external_delay)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    } else if(NOT_ADC_DECODE_SIGNAL_DELAY(external_delay)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0017U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_EDDLY(adc_periph) &= ~((uint32_t)ADC_EDDLY_EDDLY);
        ADC_EDDLY(adc_periph) |= external_delay;
    }
}

/*!
    \brief      configure the ADC convert start delay (API_ID(0x0018U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  cs_delay: the delay from trigger to start conversion, it can be 0~0xFFFF
    \param[out] none
    \retval     none
*/
void adc_convert_start_delay_config(uint32_t adc_periph, uint32_t cs_delay)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else if(NOT_ADC_START_CONVERSION_DELAY(cs_delay)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0018U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CSDLY(adc_periph) &= ~((uint32_t)ADC_CSDLY_CSDLY);
        ADC_CSDLY(adc_periph) |= cs_delay;
    }
}

/*!
    \brief      enable the ADC convert start delay sequence (API_ID(0x0019U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  cs_sequence: the delay from trigger to start conversion of sequence enable
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE_TRIGGER_DELAY: routine sequence trigger delay
      \arg        ADC_INSERTED_SEQUENCE0_TRIGGER_DELAY: inserted sequence 0 trigger delay
      \arg        ADC_INSERTED_SEQUENCE1_TRIGGER_DELAY: inserted sequence 1 trigger delay
      \arg        ADC_INSERTED_SEQUENCE2_TRIGGER_DELAY: inserted sequence 2 trigger delay
      \arg        ADC_INSERTED_SEQUENCE3_TRIGGER_DELAY: inserted sequence 3 trigger delay
      \arg        ADC_INSERTED_SEQUENCE4_TRIGGER_DELAY: inserted sequence 4 trigger delay
      \arg        ADC_INSERTED_SEQUENCE5_TRIGGER_DELAY: inserted sequence 5 trigger delay
    \param[out] none
    \retval     none
*/
void adc_convert_start_delay_enable(uint32_t adc_periph, uint32_t cs_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else if(NOT_ADC_DELAY_ENABLE_SEQUENCE(cs_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0019U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CSDLY(adc_periph) |= cs_sequence;
    }
}

/*!
    \brief      disable the ADC convert start delay sequence (API_ID(0x001AU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  cs_sequence: the delay from trigger to start conversion enable
                only one parameter can be selected which is shown as below:
      \arg        ADC_ALL_TRIGGER_DELAY_DISABLE: all groups trigger delay disable
      \arg        ADC_ROUTINE_SEQUENCE_TRIGGER_DELAY: routine sequence trigger delay
      \arg        ADC_INSERTED_SEQUENCE0_TRIGGER_DELAY: inserted sequence 0 trigger delay
      \arg        ADC_INSERTED_SEQUENCE1_TRIGGER_DELAY: inserted sequence 1 trigger delay
      \arg        ADC_INSERTED_SEQUENCE2_TRIGGER_DELAY: inserted sequence 2 trigger delay
      \arg        ADC_INSERTED_SEQUENCE3_TRIGGER_DELAY: inserted sequence 3 trigger delay
      \arg        ADC_INSERTED_SEQUENCE4_TRIGGER_DELAY: inserted sequence 4 trigger delay
      \arg        ADC_INSERTED_SEQUENCE5_TRIGGER_DELAY: inserted sequence 5 trigger delay
    \param[out] none
    \retval     none
*/
void adc_convert_start_delay_disable(uint32_t adc_periph, uint32_t cs_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    } else if(NOT_ADC_DELAY_DISABLE_SEQUENCE(cs_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ALL_TRIGGER_DELAY_DISABLE == cs_sequence) {
            ADC_CSDLY(adc_periph) = (uint32_t)cs_sequence;
        } else {
            ADC_CSDLY(adc_periph) &= ~((uint32_t)cs_sequence);
        }
    }
}

/*!
    \brief      configure ADC restart or resume sequence when this sequence be suspended (API_ID(0x001BU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  adc_resel: select which way to recovery sequence conversion
                only one parameter can be selected which is shown as below:
      \arg        ADC_RESUME_SEQUENCE: resume sequence conversion
      \arg        ADC_RESTART_SEQUENCE: restart sequence conversion
    \param[out] none
    \retval     none
*/
void adc_restart_resume_sequence_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t adc_resel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001BU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_RECOVERY_CONVERSION(adc_resel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCTL(adc_periph) &= ~((uint32_t)ADC_RCTL_RRESTART);
            ADC_RCTL(adc_periph) |= (uint32_t)adc_resel;
        } else {
            ADC_IxCTL(adc_periph, adc_sequence) &= ~((uint32_t)ADC_ICTL_IRESTART);
            ADC_IxCTL(adc_periph, adc_sequence) |= (uint32_t)adc_resel;
        }
    }
}

/*!
    \brief      abort ADC current sequence conversion (API_ID(0x001CU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     none
*/
void adc_sequence_abort(uint32_t adc_periph, uint32_t adc_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCTL(adc_periph) |= (uint32_t)ADC_RCTL_RABORT;
        } else {
            ADC_IxCTL(adc_periph, adc_sequence) |= (uint32_t)ADC_ICTL_IABORT;
        }
    }
}

/*!
    \brief      configure ADC gain mode (API_ID(0x001DU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_gain_config(uint32_t adc_periph, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            ADC_CTL(adc_periph) |= ADC_CTL_GAINEN;
        } else {
            ADC_CTL(adc_periph) &= ~ADC_CTL_GAINEN;
        }
    }
}

/*!
    \brief      configure the ADC gain factor (API_ID(0x001EU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  gain_factor: gain factor, it can be 0~0x3FFF
    \param[out] none
    \retval     none
*/
void adc_gain_factor_config(uint32_t adc_periph, uint32_t gain_factor)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    } else if(NOT_ADC_GAIN_FACTOR(gain_factor)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001EU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_GAINCFG(adc_periph) &= ~((uint32_t)ADC_GAINCFG_GAIN);
        ADC_GAINCFG(adc_periph) |= gain_factor;
    }
}

/*!
    \brief      enable offset y mode (API_ID(0x001FU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  off_num: offset number, it can be 0~3
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_offset_config(uint32_t adc_periph, uint32_t off_num, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    } else if(NOT_ADC_OFFSET_NUMBER(off_num)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001FU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x001FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            ADC_OFFCFGx(adc_periph, off_num) |= ADC_OFFCFG_OFFEN;
        } else {
            ADC_OFFCFGx(adc_periph, off_num) &= ~ADC_OFFCFG_OFFEN;
        }
    }
}

/*!
    \brief      configure the ADC offset function parameters (API_ID(0x0020U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  off_num: offset number, it can be 0~3
    \param[in]  off_factor: offset factor, it can be 0~0xFFF
    \param[in]  off_ch: offset channel, it can be 0~0x3D
    \param[in]  off_pos: offset positive or negative
                only one parameter can be selected which is shown as below:
      \arg        ADC_NEGATIVE_OFFSET: negative offset
      \arg        ADC_POSITIVE_OFFSET: positive offset
    \param[out] none
    \retval     none
*/
void adc_offset_parameter_config(uint32_t adc_periph, uint32_t off_num, uint32_t off_factor, uint32_t off_ch, uint32_t off_pos)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0020U), ERR_PERIPH);
    } else if(NOT_ADC_OFFSET_NUMBER(off_num)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0020U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_OFFSET_FACTOR(off_factor)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0020U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_OFFSET_CHANNEL(off_ch)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0020U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_OFFSET_POSITIVE(off_pos)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0020U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the offset factor */
        ADC_OFFCFGx(adc_periph, off_num) &= ~((uint32_t)ADC_OFFCFG_OFFSET);
        ADC_OFFCFGx(adc_periph, off_num) |= off_factor;

        /* configure the channel selection for offset */
        ADC_OFFCFGx(adc_periph, off_num) &= ~((uint32_t)ADC_OFFCFG_OFFCH);
        ADC_OFFCFGx(adc_periph, off_num) |= off_ch << 16U;

        /* configure the positive offset */
        ADC_OFFCFGx(adc_periph, off_num) &= ~((uint32_t)ADC_OFFCFG_OFFPOS);
        ADC_OFFCFGx(adc_periph, off_num) |= off_pos;
    }
}

/*!
    \brief      configure ADC data signed mode (API_ID(0x0021U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  off_num: offset number, it can be 0~3
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_signed_data_configure(uint32_t adc_periph, uint32_t off_num, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0021U), ERR_PERIPH);
    } else if(NOT_ADC_OFFSET_NUMBER(off_num)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0021U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0021U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            ADC_OFFCFGx(adc_periph, off_num) |= ADC_OFFCFG_SIGNEN;
        } else {
            ADC_OFFCFGx(adc_periph, off_num) &= ~ADC_OFFCFG_SIGNEN;
        }
    }
}

/*!
    \brief      configure the length of routine sequence or inserted sequence (API_ID(0x0022U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  length: the length of the channel, routine channel 1-28, inserted channel 1-4
    \param[out] none
    \retval     none
*/
void adc_channel_length_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t length)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0022U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0022U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            if((length >= 1U) && (length <= 28U)) {
                /* configure the length of routine sequence */
                ADC_RCTL(adc_periph) &= ~((uint32_t)ADC_RCTL_RL);
                ADC_RCTL(adc_periph) |= RCTL_RL((uint32_t)(length - 1U));
            } else {
                /* illegal parameters */
            }
        } else {
            if((length >= 1U) && (length <= 4U)) {
                /* configure the length of inserted sequence */
                ADC_IxCTL(adc_periph, adc_sequence) &= ~((uint32_t)ADC_ICTL_IL);
                ADC_IxCTL(adc_periph, adc_sequence) |= ICTL_IL((uint32_t)(length - 1U));
            } else {
                /* illegal parameters */
            }
        }
    }
}

/*!
    \brief      configure ADC sequence channel (API_ID(0x0023U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[in]  adc_channel: the ADC channel, this parameter must be between 0 to 61
    \param[in]  sample_time: the sample time value, this parameter must be between 0 to 638
    \param[out] none
    \retval     none
*/
void adc_sequence_channel_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank, uint32_t adc_channel, uint32_t sample_time)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0023U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0023U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_CHANNEL(adc_channel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_SAMPLE_TIME(sample_time)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCFGx(adc_periph, rank) &= ~((uint32_t)(ADC_RCFG_RSQ | ADC_RCFG_RSMP));
            ADC_RCFGx(adc_periph, rank) |= (uint32_t)(adc_channel | (sample_time << 16U));
        } else {
            ADC_IxCFGy(adc_periph, adc_sequence, rank) &= ~((uint32_t)(ADC_ICFG_ISQ | ADC_ICFG_ISMP));
            ADC_IxCFGy(adc_periph, adc_sequence, rank) |= (uint32_t)(adc_channel | (sample_time << 16U));
        }
    }
}

/*!
    \brief      configure the routine sequence conversion mode (API_ID(0x0024U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_mode: select the conversion mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_ONE_SHOT_MODE: one-shot mode
      \arg        ADC_CONTINUOUS_MODE: continuous mode
    \param[out] none
    \retval     none
*/
void adc_routine_sequence_conversion_mode_config(uint32_t adc_periph, uint32_t adc_mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0024U), ERR_PERIPH);
    } else if(NOT_ADC_ROUTINE_MODE(adc_mode)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0024U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_RCTL(adc_periph) &= ~((uint32_t)ADC_RCTL_RMODE);
        ADC_RCTL(adc_periph) |= (uint32_t)adc_mode;
    }
}

/*!
    \brief      configure ADC external trigger mode for channel (API_ID(0x0025U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  adc_trigger: select external trigger
                only one parameter can be selected which is shown as below:
      \arg        ADC_EXTERNAL_TRIGGER_DISABLE: external trigger for channel disable
      \arg        ADC_EXTERNAL_TRIGGER_RISING_EDGE: rising edge of external trigger for channel
      \arg        ADC_EXTERNAL_TRIGGER_FALLING_EDGE: falling edge of external trigger for channel
      \arg        ADC_EXTERNAL_TRIGGER_RISING_FALLING_EDGE: rising and falling edge of external trigger for channel
    \param[out] none
    \retval     none
*/
void adc_external_trigger_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t adc_trigger)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0025U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0025U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_TRIGGER(adc_trigger)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0025U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCTL(adc_periph) &= ~((uint32_t)ADC_RCTL_ETMRC);
            ADC_RCTL(adc_periph) |= (uint32_t)adc_trigger;
        } else {
            ADC_IxCTL(adc_periph, adc_sequence) &= ~((uint32_t)ADC_ICTL_ETMIC);
            ADC_IxCTL(adc_periph, adc_sequence) |= (uint32_t)adc_trigger;
        }
    }
}

/*!
    \brief      enable ADC sequence software trigger (API_ID(0x0026U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     none
*/
void adc_sequence_software_trigger_enable(uint32_t adc_periph, uint32_t adc_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0026U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0026U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCTL(adc_periph) |= (uint32_t)ADC_RCTL_SWRCST;
        } else {
            ADC_IxCTL(adc_periph, adc_sequence) |= (uint32_t)ADC_ICTL_SWICST;
        }
    }
}

/*!
    \brief      configure ADC channel pre-sample function (API_ID(0x0027U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_channel: it can be 0~61
    \param[in]  presamplepara: ADC pre-sample function parameter struct
                  time:  it can be 0~638
                  volselect: ADC_PSMPVSEL_VREFN,ADC_PSMPVSEL_VREFP
                  follow:ADC_NO_CONVERSION_AFTER_PRESAMPLE,ADC_PRESAMPLE_FOLLOW_CONVERSION
                  enable: ENABLE,DISABLE
    \param[out] none
    \retval     none
*/
void adc_channel_presample_config(uint32_t adc_periph, uint32_t adc_channel, adc_presample_parameter_struct *presamplepara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0027U), ERR_PERIPH);
    } else if(NOT_ADC_CHANNEL(adc_channel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0027U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_VALID_POINTER(presamplepara)) {
	fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0027U), ERR_PARAM_POINTER);
    } else
	
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CHCFGx(adc_periph, adc_channel) &= ~((uint32_t)(ADC_CHCFG_PSMPVSEL | ADC_CHCFG_DISSMP));
        ADC_PSMPCFG(adc_periph) &= ~((uint32_t)ADC_PSMPCFG_PSMP);

        if(ENABLE == presamplepara->enable) {
            ADC_CHCFGx(adc_periph, adc_channel) |= (uint32_t)(presamplepara->volselect | presamplepara->follow);
            ADC_PSMPCFG(adc_periph) |= (uint32_t)presamplepara->time;
            ADC_CHCFGx(adc_periph, adc_channel) |= ADC_CHCFG_PSMPEN;
        } else {
            ADC_CHCFGx(adc_periph, adc_channel) &= ~(uint32_t)ADC_CHCFG_PSMPEN;
        }
    }
}


/*!
    \brief      read ADC sequence channel data register (API_ID(0x0028U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     the conversion value: 0~0xFFFF
*/
uint16_t adc_channel_data_read(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
    uint16_t data = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0028U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0028U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0028U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            data = (uint16_t)(ADC_RCHDATAx(adc_periph, rank) & ADC_RCHDATA_RCHDATA);
        } else {
            data = (uint16_t)(ADC_IxCHDATAy(adc_periph, adc_sequence, rank) & ADC_ICHDATA_ICHDATA);
        }
    }
    return data;
}

/*!
    \brief      read ADC sequence data register (API_ID(0x0029U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     the conversion value: 0~0xFFFF
*/
uint16_t adc_sequence_data_read(uint32_t adc_periph, uint32_t adc_sequence)
{
    uint16_t data = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0029U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0029U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            data = (uint16_t)(ADC_RDATA(adc_periph) & ADC_RDATA_RDATA);
        } else {
            data = (uint16_t)(ADC_IxDATA(adc_periph, adc_sequence) & ADC_IDATA_IDATA);
        }
    }
    return data;
}

/*!
    \brief      configure ADC channel analog watchdog events (API_ID(0x002AU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_channel: it can be 0~61
    \param[in]  awd_sel: analog watchdog select
                only one parameter can be selected which is shown as below:
      \arg        ADC_ANALOG_WATCHDOG0: analog watchdog 0
      \arg        ADC_ANALOG_WATCHDOG1: analog watchdog 1
      \arg        ADC_ANALOG_WATCHDOG2: analog watchdog 2
      \arg        ADC_ANALOG_WATCHDOG3: analog watchdog 3
    \param[in]  awd_event: analog watchdog event select
                only one parameter can be selected which is shown as below:
      \arg        ADC_ANALOG_WATCHDOG_DISABLE: disable analog watchdog
      \arg        ADC_RESULT_WDLT: result <= WDLT
      \arg        ADC_WDLT_RESULT_WDHT: WDLT < result <= WDHT
      \arg        ADC_WDHT_RESULT: result > WDHT
      \arg        ADC_WDLT_RESULT: result > WDLT
      \arg        ADC_WDHT_RESULT_WDLT: result > WDHT or result <= WDLT
      \arg        ADC_RESULT_WDHT: result <= WDHT
    \param[out] none
    \retval     none
*/
void adc_channel_analog_watchdog_event_config(uint32_t adc_periph, uint32_t adc_channel, uint32_t awd_sel, uint32_t awd_event)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002AU), ERR_PERIPH);
    } else if(NOT_ADC_CHANNEL(adc_channel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002AU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_ANALOG_WATCHDOG(awd_sel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002AU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_ANALOG_WATCHDOG_EVENT(awd_event)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CHCFGx(adc_periph, adc_channel) &= ~((uint32_t)(ADC_CHCFG_WDSEL | ADC_CHCFG_WDMSEL));
        ADC_CHCFGx(adc_periph, adc_channel) |= (uint32_t)((awd_sel << 3) | awd_event);
    }
}

/*!
    \brief      configure the ADC analog watchdog threshold value (API_ID(0x002BU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  awd_sel: analog watchdog select
                only one parameter can be selected which is shown as below:
      \arg        ADC_ANALOG_WATCHDOG0: ADC analog watchdog 0
      \arg        ADC_ANALOG_WATCHDOG1: ADC analog watchdog 1
      \arg        ADC_ANALOG_WATCHDOG2: ADC analog watchdog 2
      \arg        ADC_ANALOG_WATCHDOG3: ADC analog watchdog 3
    \param[in]  low_value: analog watchdog low threshold value, it can be 0~0xFFF
    \param[in]  high_value: analog watchdog high threshold value, it can be 0~0xFFF
    \param[out] none
    \retval     none
*/
void adc_watchdog_threshold_config(uint32_t adc_periph, uint32_t awd_sel, uint32_t low_value, uint32_t high_value)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002BU), ERR_PERIPH);
    } else if(NOT_ADC_ANALOG_WATCHDOG(awd_sel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002BU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_WATCHDOG_THRESHOLD(low_value)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002BU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_WATCHDOG_THRESHOLD(high_value)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002BU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_WDTx(adc_periph, awd_sel) &= (uint32_t)(~(ADC_WDT_WDHT | ADC_WDT_WDLT));
        ADC_WDTx(adc_periph, awd_sel) |= low_value | (high_value << 16U);
    }
}

/*!
    \brief      configure ADC sequence stream mode (API_ID(0x002CU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_stream_mode_config(uint32_t adc_periph, uint32_t adc_sequence, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002CU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002CU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
                ADC_RSTREAM(adc_periph) |= ((uint32_t)ADC_RSTREAM_RSTREAMEN);
            } else {
                ADC_IxSTREAM(adc_periph, adc_sequence) |= ((uint32_t)ADC_ISTREAM_ISTREAMEN);
            }
        } else {
            if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
                ADC_RSTREAM(adc_periph) &= ~((uint32_t)ADC_RSTREAM_RSTREAMEN);
            } else {
                ADC_IxSTREAM(adc_periph, adc_sequence) &= ~((uint32_t)ADC_ISTREAM_ISTREAMEN);
            }
        }
    }
}

/*!
    \brief      configure ADC sequence stream counter value (API_ID(0x002DU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  counter: the stream counter, it can be 0x1~0x10000
    \param[out] none
    \retval     none
*/
void adc_stream_counter_value_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t counter)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002DU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002DU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_STREAM_COUNTER_VALUE(counter)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002DU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure routine sequence stream counter value */
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            reg = ADC_RSTREAM(adc_periph);
            reg &= ~(uint32_t)ADC_RSTREAM_RSTREAMCNT;
            reg |= (uint32_t)(counter - 1U);
            ADC_RSTREAM(adc_periph) = reg;
        } else {
            /* configure inserted sequence stream counter value */
            reg = ADC_IxSTREAM(adc_periph, adc_sequence);
            reg &= ~(uint32_t)ADC_ISTREAM_ISTREAMCNT;
            reg |= (uint32_t)(counter - 1U);
            ADC_IxSTREAM(adc_periph, adc_sequence) = reg;
        }
    }
}

/*!
    \brief      configure ADC sequence stream mode reload (API_ID(0x002EU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_stream_mode_reload_config(uint32_t adc_periph, uint32_t adc_sequence, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002EU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002EU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
                ADC_RSTREAM(adc_periph) |= ((uint32_t)ADC_RSTREAM_RSTREAMAREN);
            } else {
                ADC_IxSTREAM(adc_periph, adc_sequence) |= ((uint32_t)ADC_ISTREAM_ISTREAMAREN);
            }
        } else {
            if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
                ADC_RSTREAM(adc_periph) &= ~((uint32_t)ADC_RSTREAM_RSTREAMAREN);
            } else {
                ADC_IxSTREAM(adc_periph, adc_sequence) &= ~((uint32_t)ADC_ISTREAM_ISTREAMAREN);
            }
        }
    }
}

/*!
    \brief      configure ADC self test (API_ID(0x002FU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_selftest_configure(uint32_t adc_periph, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002FU), ERR_PERIPH);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x002FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            ADC_STCFG(adc_periph) |= ADC_STCFG_STEN;
        } else {
            ADC_STCFG(adc_periph) &= ~ADC_STCFG_STEN;
        }
    }
}

/*!
    \brief      configure the selftest capacitive and supply sample time (API_ID(0x0030U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_selftest: select selftest mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY: supply self test
      \arg        ADC_SELFTEST_CAPACITIVE: capacitive self test
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE: supply and capacitive
    \param[in]  csamp: sampling time for capacitive selftest, it can be 0~638
    \param[in]  ssamp: sampling time for supply selftest, it can be 0~638
    \param[out] none
    \retval     none
*/
void adc_selftest_sample_time_config(uint32_t adc_periph, uint32_t adc_selftest, uint32_t ssamp, uint32_t csamp)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0030U), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_MODE(adc_selftest)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0030U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SAMPLE_TIME(ssamp)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0030U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_SAMPLE_TIME(csamp)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0030U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_SELFTEST_SUPPLY == adc_selftest) {
            /* configure self test supply sample time */
            ADC_STSAMPT(adc_periph) &= ~(uint32_t)(ADC_STSAMPT_SSPT);
            ADC_STSAMPT(adc_periph) |= (uint32_t)ssamp;
        } else if(ADC_SELFTEST_CAPACITIVE == adc_selftest) {
            /* configure self test capacitive sample time */
            ADC_STSAMPT(adc_periph) &= ~(uint32_t)ADC_STSAMPT_CSPT;
            ADC_STSAMPT(adc_periph) |= (uint32_t)(csamp << 16U);
        } else {
            /* configure self test capacitive and supply sample time */
            ADC_STSAMPT(adc_periph) &= ~(uint32_t)(ADC_STSAMPT_SSPT | ADC_STSAMPT_CSPT);
            ADC_STSAMPT(adc_periph) |= (uint32_t)(ssamp | (csamp << 16U));
        }
    }
}

/*!
    \brief      select the capacitive and supply selftest steps in one shot mode (API_ID(0x0031U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  st_step: select capacitive and supply selftest steps
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP0: for supply or capacitive self test step 0
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP1: for supply or capacitive self test step 1
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP2: for supply or capacitive self test step 2
      \arg        ADC_SELFTEST_CAPACITIVE_STEP3: for capacitive self test step 3
      \arg        ADC_SELFTEST_CAPACITIVE_STEP4: for capacitive self test step 4
      \arg        ADC_SELFTEST_CAPACITIVE_STEP5: for capacitive self test step 5
      \arg        ADC_SELFTEST_CAPACITIVE_STEP6: for capacitive self test step 6
      \arg        ADC_SELFTEST_CAPACITIVE_STEP7: for capacitive self test step 7
    \param[out] none
    \retval     none
*/
void adc_selftest_step_select_in_oneshot_mode(uint32_t adc_periph, uint32_t st_step)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0031U), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_STEP(st_step)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0031U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_STCFG(adc_periph) &= ~(uint32_t)(ADC_STCFG_STSSEL);
        ADC_STCFG(adc_periph) |= (uint32_t)st_step;
    }
}

/*!
    \brief      configure the self test mode (API_ID(0x0032U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_selftest: select selftest mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY: supply self test
      \arg        ADC_SELFTEST_CAPACITIVE: capacitive self test
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE: supply and capacitive self test
    \param[out] none
    \retval     none
*/
void adc_selftest_mode_config(uint32_t adc_periph, uint32_t adc_selftest)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0032U), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_MODE(adc_selftest)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0032U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_STCFG(adc_periph) &= ~(uint32_t)(ADC_STCFG_STMSEL);
        ADC_STCFG(adc_periph) |= (uint32_t)adc_selftest;
    }
}

/*!
    \brief      configure the self test execution rate in continous mode (API_ID(0x0033U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  st_rate: a self test step is executed after the routine sequence has been converted x times, x can be 1~256
    \param[out] none
    \retval     none
*/
void adc_selftest_rate_config(uint32_t adc_periph, uint32_t st_rate)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0033U), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_RATE(st_rate)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0033U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_STCFG(adc_periph) &= ~(uint32_t)(ADC_STCFG_STEXER);
        ADC_STCFG(adc_periph) |= (uint32_t)((st_rate - 1U) << 16U);
    }
}

/*!
    \brief      read the self test error data (API_ID(0x0034U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  st_data: select read which selftest mode step data
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY_STEP0_DATA: error data of supply self test step 0
      \arg        ADC_SELFTEST_SUPPLY_STEP1_DATA: error data of supply self test step 1
      \arg        ADC_SELFTEST_SUPPLY_STEP2_DATA: error data of supply self test step 2
      \arg        ADC_SELFTEST_CAPACITIVE_STEP_DATA: error data of capacitive self test steps
    \param[out] none
    \retval     the error value: 0~0xFFF
*/
uint32_t adc_selftest_error_data_read(uint32_t adc_periph, uint32_t st_data)
{
    uint32_t data = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0034U), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_STEP_DATA(st_data)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0034U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(st_data) {
        /* read error data of supply self  test step 0 */
        case ADC_SELFTEST_SUPPLY_STEP0_DATA:
            data = (uint32_t)((ADC_STEDATA1(adc_periph) & ADC_STEDATA1_SST0EDATA) >> 16U);
            break;
        /* read error data of supply self  test step 1 */
        case ADC_SELFTEST_SUPPLY_STEP1_DATA:
            data = (uint32_t)(ADC_STEDATA0(adc_periph) & ADC_STEDATA0_SST1EDATA);
            break;
        /* read error data of supply self  test step 2 */
        case ADC_SELFTEST_SUPPLY_STEP2_DATA:
            data = (uint32_t)((ADC_STEDATA0(adc_periph) & ADC_STEDATA0_SST2EDATA) >> 16U);
            break;
        /* read error data of capacitive self test step */
        case ADC_SELFTEST_CAPACITIVE_STEP_DATA:
            data = (uint32_t)(ADC_STEDATA1(adc_periph) & ADC_STEDATA1_CSTEDATA);
            break;
        default:
            break;
        }
    }
    return data;
}

/*!
    \brief      read the selftest data (API_ID(0x0035U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     the conversion value: 0~0xFFF
*/
uint32_t adc_selftest_data_read(uint32_t adc_periph)
{
    uint32_t data = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0035U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        data = (uint32_t)(ADC_STDATA(adc_periph) & ADC_STDATA_STDATA);
    }
    return data;
}

/*!
    \brief      get the self test capacitive occurred error step (API_ID(0x0036U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     error step: 0~0x7
*/
uint32_t adc_selftest_capacitive_error_step_get(uint32_t adc_periph)
{
    uint32_t step = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0036U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        step = (uint32_t)(ADC_STSTAT(adc_periph) & ADC_STSTAT_CSTESTP);
    }
    return step;
}

/*!
    \brief      get the self test which step converted result (API_ID(0x0037U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     step: 0~0xF
*/
uint32_t adc_selftest_converted_step_get(uint32_t adc_periph)
{
    uint32_t step = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0037U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        step = (uint32_t)((ADC_STDATA(adc_periph) & ADC_STDATA_STSTP) >> 16U);
    }
    return step;
}

/*!
    \brief      get the status of self test previous conversion data whether was overwritten without read (API_ID(0x0038U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_selftest_overwrite_status_get(uint32_t adc_periph)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0038U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (ADC_STDATA(adc_periph) & ADC_STDATA_STOVWF)) {
            reval = SET;
        } else {
            /* illegal parameters */
        }
    }
    return reval;
}

/*!
    \brief      get the status of selftest whether new conversion data is available (API_ID(0x0039U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_selftest_conversion_data_available_get(uint32_t adc_periph)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0039U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (ADC_STDATA(adc_periph) & ADC_STDATA_STAVLB)) {
            reval = SET;
        } else {
            /* illegal parameters */
        }
    }
    return reval;
}

/*!
    \brief      configure the self test analog watchdog threshold value (API_ID(0x003AU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  st_sel: select self test mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY: supply self test
      \arg        ADC_SELFTEST_CAPACITIVE: capacitive self test
    \param[in]  st_step: select capacitive and supply selftest steps
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP0: for supply or capacitive self test step 0
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP1: for supply or capacitive self test step 1
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP2: for supply or capacitive self test step 2
      \arg        ADC_SELFTEST_CAPACITIVE_STEP3: for capacitive self test step 3
      \arg        ADC_SELFTEST_CAPACITIVE_STEP4: for capacitive self test step 4
      \arg        ADC_SELFTEST_CAPACITIVE_STEP5: for capacitive self test step 5
      \arg        ADC_SELFTEST_CAPACITIVE_STEP6: for capacitive self test step 6
      \arg        ADC_SELFTEST_CAPACITIVE_STEP7: for capacitive self test step 7
    \param[in]  low_thl: low threshold value, between 0~0xFFF(just for supply self test step 1/2)
    \param[in]  high_thl: high threshold value, between 0~0xFFF(just for supply self test step 0/1 and capacitive steps)
    \param[out] none
    \retval     none
*/
void adc_selftest_analog_watchdog_step_threshold_config(uint32_t adc_periph, uint32_t st_sel, uint32_t st_step, uint32_t low_thl, uint32_t high_thl)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003AU), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_MODE_SUP_CAP(st_sel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003AU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SELFTEST_STEP(st_step)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003AU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SELFTEST_THRESHOLD(low_thl)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003AU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_SELFTEST_THRESHOLD(high_thl)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003AU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_SELFTEST_SUPPLY == st_sel) {
            switch(st_step) {
            case 0:
                ADC_SSTWDCFGx(adc_periph, st_step) &= ~(uint32_t)(ADC_SSTWDCFG_SSTWDHT);
                ADC_SSTWDCFGx(adc_periph, st_step) |= (uint32_t)(high_thl << 16U);
                break;
            case 1:
                ADC_SSTWDCFGx(adc_periph, st_step) &= ~(uint32_t)(ADC_SSTWDCFG_SSTWDLT | ADC_SSTWDCFG_SSTWDHT);
                ADC_SSTWDCFGx(adc_periph, st_step) |= (uint32_t)(low_thl | high_thl << 16U);
                break;
            case 2:
                ADC_SSTWDCFGx(adc_periph, st_step) &= ~(uint32_t)(ADC_SSTWDCFG_SSTWDLT);
                ADC_SSTWDCFGx(adc_periph, st_step) |= (uint32_t)(low_thl);
                break;
            default:
                break;
            }
        } else {
            if(st_step % 2U == 0U) {
                ADC_CSTWDCFGx(adc_periph, st_step / 2U) &= ~(uint32_t)(ADC_CSTWDCFG_CSTWDHT0);
                ADC_CSTWDCFGx(adc_periph, st_step / 2U) |= (uint32_t)(high_thl);
            } else {
                ADC_CSTWDCFGx(adc_periph, st_step / 2U) &= ~(uint32_t)(ADC_CSTWDCFG_CSTWDHT1);
                ADC_CSTWDCFGx(adc_periph, st_step / 2U) |= (uint32_t)(high_thl << 16U);
            }
        }
    }
}

/*!
    \brief      configure the self test analog watchdog (API_ID(0x003BU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  st_sel: select self test mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY: supply self test
      \arg        ADC_SELFTEST_CAPACITIVE: capacitive self test
    \param[in]  st_step: select capacitive and supply selftest steps
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP0: for supply or capacitive self test step 0
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP1: for supply or capacitive self test step 1
      \arg        ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP2: for supply or capacitive self test step 2
      \arg        ADC_SELFTEST_CAPACITIVE_STEP3: for capacitive self test step 3
      \arg        ADC_SELFTEST_CAPACITIVE_STEP4: for capacitive self test step 4
      \arg        ADC_SELFTEST_CAPACITIVE_STEP5: for capacitive self test step 5
      \arg        ADC_SELFTEST_CAPACITIVE_STEP6: for capacitive self test step 6
      \arg        ADC_SELFTEST_CAPACITIVE_STEP7: for capacitive self test step 7
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_selftest_analog_watchdog_config(uint32_t adc_periph, uint32_t st_sel, uint32_t st_step, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003BU), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_MODE_SUP_CAP(st_sel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003BU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SELFTEST_STEP(st_step)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003BU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            if(ADC_SELFTEST_SUPPLY == st_sel) {
                ADC_SSTWDCFGx(adc_periph, st_step) |= (uint32_t)ADC_SSTWDCFG_SSTWDEN;
            } else {
                if(st_step % 2U == 0U) {
                    ADC_CSTWDCFGx(adc_periph, st_step / 2U) |= (uint32_t)(ADC_CSTWDCFG_CSTWDEN0);
                } else {
                    ADC_CSTWDCFGx(adc_periph, st_step / 2U) |= (uint32_t)(ADC_CSTWDCFG_CSTWDEN1);
                }
            }
        } else {
            if(ADC_SELFTEST_SUPPLY == st_sel) {
                ADC_SSTWDCFGx(adc_periph, st_step) &= ~(uint32_t)ADC_SSTWDCFG_SSTWDEN;
            } else {
                if(st_step % 2U == 0U) {
                    ADC_CSTWDCFGx(adc_periph, st_step / 2U) &= ~(uint32_t)(ADC_CSTWDCFG_CSTWDEN0);
                } else {
                    ADC_CSTWDCFGx(adc_periph, st_step / 2U) &= ~(uint32_t)(ADC_CSTWDCFG_CSTWDEN1);
                }
            }
        }
    }
}

/*!
    \brief      configure the self test watchdog timer safe time (API_ID(0x003CU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  st_time: self test safe time
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_TIME_0_1MS: about 0.1ms at 15MHz ADC clock frequency
      \arg        ADC_SELFTEST_TIME_0_5MS: about 0.5ms at 15MHz ADC clock frequency
      \arg        ADC_SELFTEST_TIME_1MS: about 1ms at 15MHz ADC clock frequency
      \arg        ADC_SELFTEST_TIME_2MS: about 2ms at 15MHz ADC clock frequency
      \arg        ADC_SELFTEST_TIME_5MS: about 5ms at 15MHz ADC clock frequency
      \arg        ADC_SELFTEST_TIME_10MS: about 10ms at 15MHz ADC clock frequency
      \arg        ADC_SELFTEST_TIME_20MS: about 20ms at 15MHz ADC clock frequency
      \arg        ADC_SELFTEST_TIME_50MS: about 50ms at 15MHz ADC clock frequency
    \param[out] none
    \retval     none
*/
void adc_selftest_watchdog_timer_safe_time_config(uint32_t adc_periph, uint32_t st_time)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003CU), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_SAFE_TIME(st_time)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_STCFG(adc_periph) &= ~(uint32_t)(ADC_STCFG_STWDT);
        ADC_STCFG(adc_periph) |= (uint32_t)st_time;
    }
}

/*!
    \brief      configure ADC selftest watchdog timer (API_ID(0x003DU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  st_sel: select self test mode
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_SUPPLY: supply self test
      \arg        ADC_SELFTEST_CAPACITIVE: capacitive self test
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_selftest_watchdog_timer_config(uint32_t adc_periph, uint32_t st_sel, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003DU), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_MODE_SUP_CAP(st_sel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003DU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            if(ADC_SELFTEST_SUPPLY == st_sel) {
                ADC_SSTWDCFGx(adc_periph, 0U) |= (uint32_t)ADC_SSTWDCFG_SSTWDTEN;
            } else {
                ADC_CSTWDCFGx(adc_periph, 3U) |= (uint32_t)ADC_CSTWDCFG_CSTWDTEN;
            }
        } else {
            if(ADC_SELFTEST_SUPPLY == st_sel) {
                ADC_SSTWDCFGx(adc_periph, 0U) &= ~(uint32_t)ADC_SSTWDCFG_SSTWDTEN;
            } else {
                ADC_CSTWDCFGx(adc_periph, 3U) &= ~(uint32_t)ADC_CSTWDCFG_CSTWDTEN;
            }
        }
    }
}

/*!
    \brief      self test registers lock (API_ID(0x003EU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  state: lock or unlock
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_REGISTER_UNLOCK: self test registers unlock
      \arg        ADC_SELFTEST_REGISTER_LOCK: self test registers lock
    \param[out] none
    \retval     none
*/
void adc_selftest_config_lock(uint32_t adc_periph, uint32_t state)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003EU), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_LOCK(state)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_CTL(adc_periph) &= ~((uint32_t)ADC_CTL_STLK);
        ADC_CTL(adc_periph) |= state;
    }
}

/*!
    \brief      configure DAC to ADC loop test (API_ID(0x003FU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  newvalue: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void adc_dac_looptest_config(uint32_t adc_periph, ControlStatus newvalue)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003FU), ERR_PERIPH);
    } else if(NOT_ADC_ENABLE_DISABLE(newvalue)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x003FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ENABLE == newvalue) {
            ADC_DTALTCFG(adc_periph) |= ADC_DTALTCFG_LTEN;
        } else {
            ADC_DTALTCFG(adc_periph) &= ~ADC_DTALTCFG_LTEN;
        }
    }
}

/*!
    \brief      configure the DAC to ADC loop test threshold value (API_ID(0x0040U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  low_thl: low threshold value, between 0~0xFF
    \param[in]  high_thl: high threshold value, between 0~0xFF
    \param[out] none
    \retval     none
*/
void adc_dac_looptest_threshold_config(uint32_t adc_periph, uint32_t low_thl, uint32_t high_thl)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0040U), ERR_PERIPH);
    } else if(NOT_ADC_LOOPTEST_THRESHOLD(low_thl)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0040U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ADC_LOOPTEST_THRESHOLD(high_thl)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0040U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_DTALTCFG(adc_periph) &= ~(uint32_t)(ADC_DTALTCFG_LTLT | ADC_DTALTCFG_LTHT);
        ADC_DTALTCFG(adc_periph) |= (uint32_t)(low_thl | (high_thl << 16U));
    }
}

/*!
    \brief      select which DAC used to loop test (API_ID(0x0041U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  dac_select: select DAC
                only one parameter can be selected which is shown as below:
      \arg        NO_DAC_SELECT: do not select DAC
      \arg        DAC0_SELECT: select DAC0_OUT0 as ADC input
      \arg        DAC1_SELECT: select DAC1_OUT0 as ADC input
    \param[out] none
    \retval     none
*/
void adc_dac_looptest_dac_select(uint32_t adc_periph, uint32_t dac_select)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0041U), ERR_PERIPH);
    } else if(NOT_ADC_LOOPTEST_DAC(dac_select)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0041U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_DTALTCFG(adc_periph) &= ~(uint32_t)(ADC_DTALTCFG_DAC0SEL | ADC_DTALTCFG_DAC1SEL);
        ADC_DTALTCFG(adc_periph) |= (uint32_t)(dac_select);
    }
}

/*!
    \brief      get the ADC current state (API_ID(0x0042U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  state: the ADC state bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_STATE_IDLE: ADC not work
      \arg        ADC_STATE_WAIT: ADC in conversion start delay state
      \arg        ADC_STATE_PSAMP: ADC in presampling state
      \arg        ADC_STATE_EDDLY: ADC in external decode signals delay state
      \arg        ADC_STATE_SAMP: ADC in sampling state
      \arg        ADC_STATE_CONV: ADC in converting state
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_current_state_get(uint32_t adc_periph, uint32_t state)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0042U), ERR_PERIPH);
    } else if(NOT_ADC_STATE(state)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0042U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((ADC_STAT(adc_periph) & ADC_STAT_ADCSTAT) == state) {
            reval = SET;
        } else {
            /* illegal parameters */
        }
    }
    return reval;
}

/*!
    \brief      get the ADC current active sequence (API_ID(0x0043U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     sequence number: 0~0x7
*/
uint32_t adc_active_sequence_get(uint32_t adc_periph)
{
    uint32_t group_num = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0043U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        group_num = (uint32_t)((ADC_STAT(adc_periph) & ADC_STAT_ACTSQ) >> 3U);
    }
    return group_num;
}

/*!
    \brief      get the ADC current active channel (API_ID(0x0044U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[out] none
    \retval     channel number: 0~61
*/
uint32_t adc_active_channel_get(uint32_t adc_periph)
{
    uint32_t channel_num = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        channel_num = (uint32_t)((ADC_STAT(adc_periph) & ADC_STAT_ACTCH) >> 8U);
    }
    return channel_num;
}

/*!
    \brief      get which channel converted this conversion data in channel register (API_ID(0x0045U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     the channel num: 0~61
*/
uint32_t adc_channel_converted_channel_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
    uint32_t data = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0045U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0045U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0045U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            data = (uint32_t)((ADC_RCHDATAx(adc_periph, rank) & ADC_RCHDATA_RCH) >> 16U);
        } else {
            data = (uint32_t)((ADC_IxCHDATAy(adc_periph, adc_sequence, rank) & ADC_ICHDATA_ICH) >> 16U);
        }
    }
    return data;
}

/*!
    \brief      get whether the previous conversion data was overwritten without read in channel register (API_ID(0x0046U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_channel_overwrite_status_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0046U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0046U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0046U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            if(0U != (ADC_RCHDATAx(adc_periph, rank) & ADC_RCHDATA_RCHOVWF)){
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            if(0U != (ADC_IxCHDATAy(adc_periph, adc_sequence, rank) & ADC_ICHDATA_ICHOVWF)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      get whether the new conversion data is available in channel register (API_ID(0x0047U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_channel_conversion_data_available_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0047U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0047U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            if(0U != (ADC_RCHDATAx(adc_periph, rank) & ADC_RCHDATA_RCHAVLB)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            if(0U != (ADC_IxCHDATAy(adc_periph, adc_sequence, rank) & ADC_ICHDATA_ICHAVLB)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      get which channel converted this conversion data in sequence register (API_ID(0x0048U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     the channel num: 0~61
*/
uint32_t adc_sequence_converted_channel_get(uint32_t adc_periph, uint32_t adc_sequence)
{
    uint32_t data = 0U;
    
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0048U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0048U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            data = (uint32_t)((ADC_RDATA(adc_periph) & ADC_RDATA_RSQCH) >> 16U);
        } else {
            data = (uint32_t)((ADC_IxDATA(adc_periph, adc_sequence) & ADC_IDATA_ISQCH) >> 16U);
        }
    }
    
    return data;
}

/*!
    \brief      get whether the previous conversion data was overwritten without read in sequence register (API_ID(0x0049U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_sequence_overwrite_status_get(uint32_t adc_periph, uint32_t adc_sequence)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0049U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0049U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            if(0U != (ADC_RDATA(adc_periph) & ADC_RDATA_ROVWF)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            if(0U != (ADC_IxDATA(adc_periph, adc_sequence) & ADC_IDATA_IOVWF)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      get whether the new conversion data is available in sequence register (API_ID(0x004AU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_sequence_conversion_data_available_get(uint32_t adc_periph, uint32_t adc_sequence)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004AU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            if(0U != (ADC_RDATA(adc_periph) & ADC_RDATA_RAVLB)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            if(0U != (ADC_IxDATA(adc_periph, adc_sequence) & ADC_IDATA_IAVLB)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      get ADC flag (API_ID(0x004BU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  flag: the ADC flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_ACTST: self test ongoing flag
      \arg        ADC_FLAG_EORC: end of routine sequence conversion flag
      \arg        ADC_FLAG_EOI0C: end of inserted sequence 0 conversion flag
      \arg        ADC_FLAG_EOI1C: end of inserted sequence 1 conversion flag
      \arg        ADC_FLAG_EOI2C: end of inserted sequence 2 conversion flag
      \arg        ADC_FLAG_EOI3C: end of inserted sequence 3 conversion flag
      \arg        ADC_FLAG_EOI4C: end of inserted sequence 4 conversion flag
      \arg        ADC_FLAG_EOI5C: end of inserted sequence 5 conversion flag
      \arg        ADC_FLAG_EORCHC: end of routine sequence channel conversion flag
      \arg        ADC_FLAG_EOI0CHC: end of inserted sequence 0 channel conversion flag
      \arg        ADC_FLAG_EOI1CHC: end of inserted sequence 1 channel conversion flag
      \arg        ADC_FLAG_EOI2CHC: end of inserted sequence 2 channel conversion flag
      \arg        ADC_FLAG_EOI3CHC: end of inserted sequence 3 channel conversion flag
      \arg        ADC_FLAG_EOI4CHC: end of inserted sequence 4 channel conversion flag
      \arg        ADC_FLAG_EOI5CHC: end of inserted sequence 5 channel conversion flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_flag_get(uint32_t adc_periph, uint32_t flag)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004BU), ERR_PERIPH);
    } else if(NOT_ADC_FLAG(flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (ADC_STAT(adc_periph) & flag)) {
            reval = SET;
        } else {
            /* illegal parameters */
        }
    }
    return reval;
}

/*!
    \brief      get ADC error flag (API_ID(0x004CU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  flag: the ADC error flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_RSUSPDF: routine sequence hold flag
      \arg        ADC_FLAG_RABORTF: routine sequence aborted flag
      \arg        ADC_FLAG_RTRGE: routine sequence trigger error flag
      \arg        ADC_FLAG_I0SUSPDF: inserted sequence 0 suspended flag
      \arg        ADC_FLAG_I0ABORTF: inserted sequence 0 aborted flag
      \arg        ADC_FLAG_I0TRGE: inserted sequence 0 trigger error flag
      \arg        ADC_FLAG_I1SUSPDF: inserted sequence 1 suspended flag
      \arg        ADC_FLAG_I1ABORTF: inserted sequence 1 aborted flag
      \arg        ADC_FLAG_I1TRGE: inserted sequence 1 trigger error flag
      \arg        ADC_FLAG_I2SUSPDF: inserted sequence 2 suspended flag
      \arg        ADC_FLAG_I2ABORTF: inserted sequence 2 aborted flag
      \arg        ADC_FLAG_I2TRGE: inserted sequence 2 trigger error flag
      \arg        ADC_FLAG_I3SUSPDF: inserted sequence 3 suspended flag
      \arg        ADC_FLAG_I3ABORTF: inserted sequence 3 aborted flag
      \arg        ADC_FLAG_I3TRGE: inserted sequence 3 trigger error flag
      \arg        ADC_FLAG_I4SUSPDF: inserted sequence 4 suspended flag
      \arg        ADC_FLAG_I4ABORTF: inserted sequence 4 aborted flag
      \arg        ADC_FLAG_I4TRGE: inserted sequence 4 trigger error flag
      \arg        ADC_FLAG_I5ABORTF: inserted sequence 5 aborted flag
      \arg        ADC_FLAG_I5TRGE: inserted sequence 5 trigger error flag
      \arg        ADC_FLAG_WDE: analog watchdog flag
      \arg        ADC_FLAG_LTE: DAC - ADC loop test error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_error_flag_get(uint32_t adc_periph, uint32_t error_flag)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004CU), ERR_PERIPH);
    } else if(NOT_ADC_ERROR_FLAG(error_flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_FLAG_LTE == error_flag) {
            if(0U != (ADC_DTALTCFG(adc_periph) & ADC_DTALTCFG_LTE)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            if(0U != (ADC_ESTAT(adc_periph) & error_flag)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear ADC flag (API_ID(0x004DU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  flag: the ADC flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_ACTST: self test ongoing flag
      \arg        ADC_FLAG_EORC: end of routine sequence conversion flag
      \arg        ADC_FLAG_EOI0C: end of inserted sequence 0 conversion flag
      \arg        ADC_FLAG_EOI1C: end of inserted sequence 1 conversion flag
      \arg        ADC_FLAG_EOI2C: end of inserted sequence 2 conversion flag
      \arg        ADC_FLAG_EOI3C: end of inserted sequence 3 conversion flag
      \arg        ADC_FLAG_EOI4C: end of inserted sequence 4 conversion flag
      \arg        ADC_FLAG_EOI5C: end of inserted sequence 5 conversion flag
      \arg        ADC_FLAG_EORCHC: end of routine sequence channel conversion flag
      \arg        ADC_FLAG_EOI0CHC: end of inserted sequence 0 channel conversion flag
      \arg        ADC_FLAG_EOI1CHC: end of inserted sequence 1 channel conversion flag
      \arg        ADC_FLAG_EOI2CHC: end of inserted sequence 2 channel conversion flag
      \arg        ADC_FLAG_EOI3CHC: end of inserted sequence 3 channel conversion flag
      \arg        ADC_FLAG_EOI4CHC: end of inserted sequence 4 channel conversion flag
      \arg        ADC_FLAG_EOI5CHC: end of inserted sequence 5 channel conversion flag
    \param[out] none
    \retval     none
*/
void adc_flag_clear(uint32_t adc_periph, uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004DU), ERR_PERIPH);
    } else if(NOT_ADC_FLAG(flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_STAT(adc_periph) = ~(uint32_t)flag;
    }
}

/*!
    \brief      clear ADC error flag (API_ID(0x004EU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  error_flag: the ADC error flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_FLAG_RABORTF: sequence aborted flag
      \arg        ADC_FLAG_RTRGE: routine sequence trigger error flag
      \arg        ADC_FLAG_I0ABORTF: inserted sequence 0 aborted flag
      \arg        ADC_FLAG_I0TRGE: inserted sequence 0 trigger error flag
      \arg        ADC_FLAG_I1ABORTF: inserted sequence 1 aborted flag
      \arg        ADC_FLAG_I1TRGE: inserted sequence 1 trigger error flag
      \arg        ADC_FLAG_I2ABORTF: inserted sequence 2 aborted flag
      \arg        ADC_FLAG_I2TRGE: inserted sequence 2 trigger error flag
      \arg        ADC_FLAG_I3ABORTF: inserted sequence 3 aborted flag
      \arg        ADC_FLAG_I3TRGE: inserted sequence 3 trigger error flag
      \arg        ADC_FLAG_I4ABORTF: inserted sequence 4 aborted flag
      \arg        ADC_FLAG_I4TRGE: inserted sequence 4 trigger error flag
      \arg        ADC_FLAG_I5ABORTF: inserted sequence 5 aborted flag
      \arg        ADC_FLAG_I5TRGE: inserted sequence 5 trigger error flag
      \arg        ADC_FLAG_WDE: analog watchdog interrupt flag
      \arg        ADC_FLAG_LTE: DAC - ADC loop test error flag
    \param[out] none
    \retval     none
*/
void adc_error_flag_clear(uint32_t adc_periph, uint32_t error_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004EU), ERR_PERIPH);
    } else if(NOT_ADC_ERROR_FLAG(error_flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_FLAG_LTE == error_flag) {
            ADC_DTALTCFG(adc_periph) &= ~(uint32_t)ADC_DTALTCFG_LTE;
        } else {
            ADC_ESTAT(adc_periph) = ~(uint32_t)error_flag;
        }
    }
}

/*!
    \brief      enable ADC interrupt (API_ID(0x004FU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  inserted_sequence: select the inserted sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_SEQUENCE_NONE: none inserted sequence (only for ADC_INT_RTRGEIE, ADC_INT_EORCIE, ADC_INT_RSTREAMIE, ADC_INT_ANALOG_WATCHDOG0,
                                              ADC_INT_ANALOG_WATCHDOG1, ADC_INT_ANALOG_WATCHDOG2, ADC_INT_ANALOG_WATCHDOG3 and ADC_INT_LOOPTEST)
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0 (only for ADC_INT_ITRGEIE, ADC_INT_IEOCIE and ADC_INT_ISTREAMIE)
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1 (only for ADC_INT_ITRGEIE, ADC_INT_IEOCIE and ADC_INT_ISTREAMIE)
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2 (only for ADC_INT_ITRGEIE, ADC_INT_IEOCIE and ADC_INT_ISTREAMIE)
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3 (only for ADC_INT_ITRGEIE, ADC_INT_IEOCIE and ADC_INT_ISTREAMIE)
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4 (only for ADC_INT_ITRGEIE, ADC_INT_IEOCIE and ADC_INT_ISTREAMIE)
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5 (only for ADC_INT_ITRGEIE, ADC_INT_IEOCIE and ADC_INT_ISTREAMIE)
    \param[in]  interrupt: the ADC interrupt
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_RTRGEIE: routine sequence trigger error interrupt
      \arg        ADC_INT_EORCIE: routine sequence end conversion interrupt
      \arg        ADC_INT_RSTREAMIE: routine sequence stream mode interrupt
      \arg        ADC_INT_ITRGEIE: inserted sequence trigger error interrupt
      \arg        ADC_INT_IEOCIE: inserted sequence end conversion interrupt
      \arg        ADC_INT_ISTREAMIE: inserted sequence stream mode interrupt
      \arg        ADC_INT_ANALOG_WATCHDOG0: analog watchdog 0 interrupt
      \arg        ADC_INT_ANALOG_WATCHDOG1: analog watchdog 1 interrupt
      \arg        ADC_INT_ANALOG_WATCHDOG2: analog watchdog 2 interrupt
      \arg        ADC_INT_ANALOG_WATCHDOG3: analog watchdog 3 interrupt
      \arg        ADC_INT_LOOPTEST: DAC to ADC loop test error interrupt
      \arg        ADC_INT_OVERWRITE: sequence overwrite interrupt
      \arg        ADC_INT_CHOVERWRITE: Channel overwrite interrupt interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_enable(uint32_t adc_periph, uint32_t inserted_sequence, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004FU), ERR_PERIPH);
    } else if(NOT_ADC_INSERTED_SEQUENCE(inserted_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004FU), ERR_PARAM_INVALID);
    } else if(NOT_ADC_INTERRUPT(interrupt)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x004FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(interrupt) {
        /* enable routine trigger specified when sequence is convering interrupt */
        case ADC_INT_RTRGEIE:
            ADC_RCTL(adc_periph) |= (uint32_t)ADC_RCTL_RTRGEIE;
            break;
        /* enable routine sequence sequence end of conversion interrupt */
        case ADC_INT_EORCIE:
            ADC_RCTL(adc_periph) |= (uint32_t)ADC_RCTL_EORCIE;
            break;
        case ADC_INT_RSTREAMIE:
            ADC_RSTREAM(adc_periph) |= ((uint32_t)ADC_RSTREAM_RSTREAMIE);
            break;
        /* enable inserted trigger specified when sequence is convering interrupt */
        case ADC_INT_ITRGEIE:
            ADC_IxCTL(adc_periph, inserted_sequence) |= (uint32_t)ADC_ICTL_ITRGEIE;
            break;
        /* enable inserted sequence sequence end of conversion interrupt */
        case ADC_INT_IEOCIE:
            ADC_IxCTL(adc_periph, inserted_sequence) |= (uint32_t)ADC_ICTL_IEOCIE;
            break;
        /* enable inserted sequence stream mode interrupt */
        case ADC_INT_ISTREAMIE:
            ADC_IxSTREAM(adc_periph, inserted_sequence) |= ((uint32_t)ADC_ISTREAM_ISTREAMIE);
            break;
        /* enable analog watchdog 0 interrupt */
        case ADC_INT_ANALOG_WATCHDOG0:
            ADC_WDTx(adc_periph, ADC_ANALOG_WATCHDOG0) |= (uint32_t)ADC_WDT_WDEIE;
            break;
        /* enable analog watchdog 1 interrupt */
        case ADC_INT_ANALOG_WATCHDOG1:
            ADC_WDTx(adc_periph, ADC_ANALOG_WATCHDOG1) |= (uint32_t)ADC_WDT_WDEIE;
            break;
        /* enable analog watchdog 2 interrupt */
        case ADC_INT_ANALOG_WATCHDOG2:
            ADC_WDTx(adc_periph, ADC_ANALOG_WATCHDOG2) |= (uint32_t)ADC_WDT_WDEIE;
            break;
        /* enable analog watchdog 3 interrupt */
        case ADC_INT_ANALOG_WATCHDOG3:
            ADC_WDTx(adc_periph, ADC_ANALOG_WATCHDOG3) |= (uint32_t)ADC_WDT_WDEIE;
            break;
        /* enable DAC to ADC loop test error interrupt */
        case ADC_INT_LOOPTEST:
            ADC_DTALTCFG(adc_periph) |= ADC_DTALTCFG_LTEIE;
            break;
        /* enable sequence overwrite interrupt */
        case ADC_INT_OVERWRITE:
            ADC_CTL(adc_periph) |= ADC_CTL_OVWIE;
            break;
        /* enable Channel overwrite interrupt interrupt */
        case ADC_INT_CHOVERWRITE:
            ADC_CTL(adc_periph) |= ADC_CTL_CHOVWIE;
            break;

        default:
            break;
        }
    }
}

/*!
    \brief      disable ADC interrupt (API_ID(0x0050U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  inserted_sequence: select the inserted sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_INSERTED_SEQUENCE_NONE: none inserted sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  interrupt: the ADC interrupt
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_RTRGEIE: routine sequence trigger error interrupt
      \arg        ADC_INT_EORCIE: routine sequence end conversion interrupt
      \arg        ADC_INT_RSTREAMIE: routine sequence stream mode interrupt
      \arg        ADC_INT_ITRGEIE: inserted sequence trigger error interrupt
      \arg        ADC_INT_IEOCIE: inserted sequence end conversion interrupt
      \arg        ADC_INT_ISTREAMIE: inserted sequence stream mode interrupt
      \arg        ADC_INT_ANALOG_WATCHDOG0: analog watchdog 0 interrupt
      \arg        ADC_INT_ANALOG_WATCHDOG1: analog watchdog 1 interrupt
      \arg        ADC_INT_ANALOG_WATCHDOG2: analog watchdog 2 interrupt
      \arg        ADC_INT_ANALOG_WATCHDOG3: analog watchdog 3 interrupt
      \arg        ADC_INT_LOOPTEST: DAC to ADC loop test error interrupt
      \arg        ADC_INT_OVERWRITE: sequence overwrite interrupt
      \arg        ADC_INT_CHOVERWRITE: Channel overwrite interrupt interrupt
    \param[out] none
    \retval     none
*/
void adc_interrupt_disable(uint32_t adc_periph, uint32_t inserted_sequence, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0050U), ERR_PERIPH);
    } else if(NOT_ADC_INSERTED_SEQUENCE(inserted_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0050U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_INTERRUPT(interrupt)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0050U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(interrupt) {
        /* disable routine trigger specified when sequence is convering interrupt */
        case ADC_INT_RTRGEIE:
            ADC_RCTL(adc_periph) &= ~(uint32_t)ADC_RCTL_RTRGEIE;
            break;
        /* disable routine sequence sequence end of conversion interrupt */
        case ADC_INT_EORCIE:
            ADC_RCTL(adc_periph) &= ~(uint32_t)ADC_RCTL_EORCIE;
            break;
        case ADC_INT_RSTREAMIE:
            ADC_RSTREAM(adc_periph) &= ~((uint32_t)ADC_RSTREAM_RSTREAMIE);
            break;
        /* disable inserted trigger specified when sequence is convering interrupt */
        case ADC_INT_ITRGEIE:
            ADC_IxCTL(adc_periph, inserted_sequence) &= ~(uint32_t)ADC_ICTL_ITRGEIE;
            break;
        /* disable inserted sequence sequence end of conversion interrupt */
        case ADC_INT_IEOCIE:
            ADC_IxCTL(adc_periph, inserted_sequence) &= ~(uint32_t)ADC_ICTL_IEOCIE;
            break;
        /* disable inserted sequence stream mode interrupt */
        case ADC_INT_ISTREAMIE:
            ADC_IxSTREAM(adc_periph, inserted_sequence) &= ~((uint32_t)ADC_ISTREAM_ISTREAMIE);
            break;
        /* disable analog watchdog 0 interrupt */
        case ADC_INT_ANALOG_WATCHDOG0:
            ADC_WDTx(adc_periph, ADC_ANALOG_WATCHDOG0) &= (uint32_t)(~ADC_WDT_WDEIE);
            break;
        /* disable analog watchdog 1 interrupt */
        case ADC_INT_ANALOG_WATCHDOG1:
            ADC_WDTx(adc_periph, ADC_ANALOG_WATCHDOG1) &= (uint32_t)(~ADC_WDT_WDEIE);
            break;
        /* disable analog watchdog 2 interrupt */
        case ADC_INT_ANALOG_WATCHDOG2:
            ADC_WDTx(adc_periph, ADC_ANALOG_WATCHDOG2) &= (uint32_t)(~ADC_WDT_WDEIE);
            break;
        /* disable analog watchdog 3 interrupt */
        case ADC_INT_ANALOG_WATCHDOG3:
            ADC_WDTx(adc_periph, ADC_ANALOG_WATCHDOG3) &= (uint32_t)(~ADC_WDT_WDEIE);
            break;
        /* disable DAC to ADC loop test error interrupt */
        case ADC_INT_LOOPTEST:
            ADC_DTALTCFG(adc_periph) &= ~ADC_DTALTCFG_LTEIE;
            break;
        /* disable sequence overwrite interrupt */
        case ADC_INT_OVERWRITE:
            ADC_CTL(adc_periph) &= ~ADC_CTL_OVWIE;
            break;
        /* disable Channel overwrite interrupt interrupt */
        case ADC_INT_CHOVERWRITE:
            ADC_CTL(adc_periph) &= ~ADC_CTL_CHOVWIE;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      get the ADC interrupt flag (API_ID(0x0051U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  int_flag: the ADC interrupt flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_EORC:  end of routine sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI0C: end of inserted sequence 0 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI1C: end of inserted sequence 1 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI2C: end of inserted sequence 2 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI3C: end of inserted sequence 3 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI4C: end of inserted sequence 4 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI5C: end of inserted sequence 5 conversion interrupt flag
      \arg        ADC_INT_FLAG_EORCHC:  end of routine sequence channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI0CHC: end of inserted sequence 0 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI1CHC: end of inserted sequence 0 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI2CHC: end of inserted sequence 2 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI3CHC: end of inserted sequence 3 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI4CHC: end of inserted sequence 4 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI5CHC: end of inserted sequence 5 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_RTRGE: routine sequence trigger error interrupt flag
      \arg        ADC_INT_FLAG_I0TRGE: inserted sequence 0 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I1TRGE: inserted sequence 1 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I2TRGE: inserted sequence 2 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I3TRGE: inserted sequence 3 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I4TRGE: inserted sequence 4 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I5TRGE: inserted sequence 5 trigger error interrupt flag
      \arg        ADC_INT_FLAG_LTE: DAC - ADC loop test error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, uint32_t int_flag)
{
    uint32_t reg1 = ADC_STAT(adc_periph);
    uint32_t reg3 = ADC_ESTAT(adc_periph);
    uint32_t reg2 = 0U;
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0051U), ERR_PERIPH);
    } else if(NOT_ADC_INTERRUPT_FLAG(int_flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0051U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(int_flag) {
        /* ADC routine end of sequence conversion interrupt */
        case ADC_INT_FLAG_EORC:{
            reg1 = reg1 & ADC_STAT_EORC;
            reg2 = ADC_RCTL(adc_periph) & ADC_RCTL_EORCIE;
            break;
        }
        /* ADC inserted sequence0 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI0C:{
            reg1 = reg1 & ADC_STAT_EOI0C;
            reg2 = ADC_IxCTL(adc_periph, 0U) & ADC_ICTL_IEOCIE;
            break;
        }
        /* ADC inserted sequence1 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI1C:{
            reg1 = reg1 & ADC_STAT_EOI1C;
            reg2 = ADC_IxCTL(adc_periph, 1U) & ADC_ICTL_IEOCIE;
            break;
        }
        /* ADC inserted sequence2 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI2C:{
            reg1 = reg1 & ADC_STAT_EOI2C;
            reg2 = ADC_IxCTL(adc_periph, 2U) & ADC_ICTL_IEOCIE;
            break;
        }
        /* ADC inserted sequence3 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI3C:{
            reg1 = reg1 & ADC_STAT_EOI3C;
            reg2 = ADC_IxCTL(adc_periph, 3U) & ADC_ICTL_IEOCIE;
            break;
        }
        /* ADC inserted sequence4 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI4C:{
            reg1 = reg1 & ADC_STAT_EOI4C;
            reg2 = ADC_IxCTL(adc_periph, 4U) & ADC_ICTL_IEOCIE;
            break;
        }
        /* ADC inserted sequence5 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI5C:{
            reg1 = reg1 & ADC_STAT_EOI5C;
            reg2 = ADC_IxCTL(adc_periph, 5U) & ADC_ICTL_IEOCIE;
            break;
        }
        /* ADC routine sequence end of channel conversion interrupt */
        case ADC_INT_FLAG_EORCHC:{
            reg1 = reg1 & ADC_STAT_EORCHC;
            reg2 = 0U;
            for(uint32_t i = 0U; i < 28U; i++) {
                if(0U != (ADC_RCFGx(adc_periph, i) & ((uint32_t)ADC_RCFG_RCHIE))) {
                    reg2 = 1U;
                    break;
                } else {
                    /* illegal parameters */
                }
            }
            break;
        }
        /* ADC inserted sequence0 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI0CHC:{
            reg1 = reg1 & ADC_STAT_EOI0CHC;
            reg2 = 0U;
            for(uint32_t i = 0U; i < 4U; i++) {
                if(0U != (ADC_IxCFGy(adc_periph, 0U, i) & ((uint32_t)ADC_ICFG_ICHIE))) {
                    reg2 = 1U;
                    break;
                } else {
                    /* illegal parameters */
                }
            }
            break;
        }
        /* ADC inserted sequence1 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI1CHC:{
            reg1 = reg1 & ADC_STAT_EOI1CHC;
            reg2 = 0U;
            for(uint32_t i = 0U; i < 4U; i++) {
                if(0U != (ADC_IxCFGy(adc_periph, 1U, i) & ((uint32_t)ADC_ICFG_ICHIE))) {
                    reg2 = 1U;
                    break;
                } else {
                    /* illegal parameters */
                }
            }
            break;
        }
        /* ADC inserted sequence2 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI2CHC:{
            reg1 = reg1 & ADC_STAT_EOI2CHC;
            reg2 = 0U;
            for(uint32_t i = 0U; i < 4U; i++) {
                if(0U != (ADC_IxCFGy(adc_periph, 2U, i) & ((uint32_t)ADC_ICFG_ICHIE))) {
                    reg2 = 1U;
                    break;
                } else {
                    /* illegal parameters */
                }
            }
            break;
        }
        /* ADC inserted sequence3 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI3CHC:{
            reg1 = reg1 & ADC_STAT_EOI3CHC;
            reg2 = 0U;
            for(uint32_t i = 0U; i < 4U; i++) {
                if(0U != (ADC_IxCFGy(adc_periph, 3U, i) & ((uint32_t)ADC_ICFG_ICHIE))) {
                    reg2 = 1U;
                    break;
                } else {
                    /* illegal parameters */
                }
            }
            break;
        }
        /* ADC inserted sequence4 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI4CHC:{
            reg1 = reg1 & ADC_STAT_EOI4CHC;
            reg2 = 0U;
            for(uint32_t i = 0U; i < 4U; i++) {
                if(0U != (ADC_IxCFGy(adc_periph, 4U, i) & ((uint32_t)ADC_ICFG_ICHIE))) {
                    reg2 = 1U;
                    break;
                } else {
                    /* illegal parameters */
                }
            }
            break;
        }
        /* ADC inserted sequence0 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI5CHC:{
            reg1 = reg1 & ADC_STAT_EOI5CHC;
            reg2 = 0U;
            for(uint32_t i = 0U; i < 4U; i++) {
                if(0U != (ADC_IxCFGy(adc_periph, 5U, i) & ((uint32_t)ADC_ICFG_ICHIE))) {
                    reg2 = 1U;
                    break;
                } else {
                    /* illegal parameters */
                }
            }
            break;
        }
        /* ADC routine sequence trigger error interrupt */
        case ADC_INT_FLAG_RTRGE:{
            reg3 = reg3 & ADC_ESTAT_RTRGE;
            reg1 = reg3;
            reg2 = ADC_RCTL(adc_periph) & ADC_RCTL_RTRGEIE;
            break;
        }
        /* ADC inserted sequence0 trigger error interrupt */
        case ADC_INT_FLAG_I0TRGE:{
            reg3 = reg3 & ADC_ESTAT_I0TRGE;
            reg1 = reg3;
            reg2 = ADC_IxCTL(adc_periph, 0U) & ADC_ICTL_ITRGEIE;
            break;
        }
        /* ADC inserted sequence1 trigger error interrupt */
        case ADC_INT_FLAG_I1TRGE:{
            reg3 = reg3 & ADC_ESTAT_I1TRGE;
            reg1 = reg3;
            reg2 = ADC_IxCTL(adc_periph, 1U) & ADC_ICTL_ITRGEIE;
            break;
        }
        /* ADC inserted sequence2 trigger error interrupt */
        case ADC_INT_FLAG_I2TRGE:{
            reg3 = reg3 & ADC_ESTAT_I2TRGE;
            reg1 = reg3;
            reg2 = ADC_IxCTL(adc_periph, 2U) & ADC_ICTL_ITRGEIE;
            break;
        }
        /* ADC inserted sequence3 trigger error interrupt */
        case ADC_INT_FLAG_I3TRGE:{
            reg3 = reg3 & ADC_ESTAT_I3TRGE;
            reg1 = reg3;
            reg2 = ADC_IxCTL(adc_periph, 3U) & ADC_ICTL_ITRGEIE;
            break;
        }
        /* ADC inserted sequence4 trigger error interrupt */
        case ADC_INT_FLAG_I4TRGE:{
            reg3 = reg3 & ADC_ESTAT_I4TRGE;
            reg1 = reg3;
            reg2 = ADC_IxCTL(adc_periph, 4U) & ADC_ICTL_ITRGEIE;
            break;
        }
        /* ADC inserted sequence5 trigger error interrupt */
        case ADC_INT_FLAG_I5TRGE:{
            reg3 = reg3 & ADC_ESTAT_I5TRGE;
            reg1 = reg3;
            reg2 = ADC_IxCTL(adc_periph, 5U) & ADC_ICTL_ITRGEIE;
            break;
        }
        /* ADC inserted sequence5 trigger error interrupt */
        case ADC_INT_FLAG_LTE:{
            reg1 = ADC_DTALTCFG(adc_periph) & ADC_DTALTCFG_LTE;
            reg2 = ADC_DTALTCFG(adc_periph) & ADC_DTALTCFG_LTEIE;
            break;
        }
        default :
            break;
        }

        /*get ADC interrupt flag status */
        if((0U != reg1) && (0U != reg2)) {
            reval = SET;
        } else {
            /* illegal parameters */
        }
    }
    return reval;
}

/*!
    \brief      clear ADC interrupt flag (API_ID(0x0052U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  int_flag: the ADC interrupt flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_INT_FLAG_EORC:  end of routine sequence conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI0C: end of inserted sequence 0 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI1C: end of inserted sequence 1 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI2C: end of inserted sequence 2 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI3C: end of inserted sequence 3 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI4C: end of inserted sequence 4 conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI5C: end of inserted sequence 5 conversion interrupt flag
      \arg        ADC_INT_FLAG_EORCHC:  end of routine sequence channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI0CHC: end of inserted sequence 0 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI1CHC: end of inserted sequence 0 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI2CHC: end of inserted sequence 2 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI3CHC: end of inserted sequence 3 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI4CHC: end of inserted sequence 4 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_EOI5CHC: end of inserted sequence 5 channel conversion interrupt flag
      \arg        ADC_INT_FLAG_RTRGE: routine sequence trigger error interrupt flag
      \arg        ADC_INT_FLAG_I0TRGE: inserted sequence 0 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I1TRGE: inserted sequence 1 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I2TRGE: inserted sequence 2 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I3TRGE: inserted sequence 3 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I4TRGE: inserted sequence 4 trigger error interrupt flag
      \arg        ADC_INT_FLAG_I5TRGE: inserted sequence 5 trigger error interrupt flag
      \arg        ADC_INT_FLAG_LTE: DAC - ADC loop test error interrupt flag
    \param[out] none
    \retval     none
*/
void adc_interrupt_flag_clear(uint32_t adc_periph, uint32_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0052U), ERR_PERIPH);
    } else if(NOT_ADC_INTERRUPT_FLAG(int_flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0052U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(int_flag) {
        /* ADC routine end of sequence conversion interrupt */
        case ADC_INT_FLAG_EORC:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EORC);
            break;
        /* ADC inserted sequence0 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI0C:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI0C);
            break;
        /* ADC inserted sequence1 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI1C:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI1C);
            break;
        /* ADC inserted sequence2 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI2C:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI2C);
            break;
        /* ADC inserted sequence3 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI3C:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI3C);
            break;
        /* ADC inserted sequence4 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI4C:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI4C);
            break;
        /* ADC inserted sequence5 end of sequence conversion interrupt */
        case ADC_INT_FLAG_EOI5C:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI5C);
            break;
        /* ADC routine sequence end of channel conversion interrupt */
        case ADC_INT_FLAG_EORCHC:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EORCHC);
            break;
        /* ADC inserted sequence0 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI0CHC:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI0CHC);
            break;
        /* ADC inserted sequence1 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI1CHC:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI1CHC);
            break;
        /* ADC inserted sequence2 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI2CHC:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI2CHC);
            break;
        /* ADC inserted sequence3 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI3CHC:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI3CHC);
            break;
        /* ADC inserted sequence4 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI4CHC:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI4CHC);
            break;
        /* ADC inserted sequence0 end of channel conversion interrupt */
        case ADC_INT_FLAG_EOI5CHC:
            ADC_STAT(adc_periph) = ~((uint32_t)ADC_STAT_EOI5CHC);
            break;
        /* ADC routine sequence trigger error interrupt */
        case ADC_INT_FLAG_RTRGE:
            ADC_ESTAT(adc_periph) = ~((uint32_t)ADC_ESTAT_RTRGE);
            break;
        /* ADC inserted sequence0 trigger error interrupt */
        case ADC_INT_FLAG_I0TRGE:
            ADC_ESTAT(adc_periph) = ~((uint32_t)ADC_ESTAT_I0TRGE);
            break;
        /* ADC inserted sequence1 trigger error interrupt */
        case ADC_INT_FLAG_I1TRGE:
            ADC_ESTAT(adc_periph) = ~((uint32_t)ADC_ESTAT_I1TRGE);
            break;
        /* ADC inserted sequence2 trigger error interrupt */
        case ADC_INT_FLAG_I2TRGE:
            ADC_ESTAT(adc_periph) = ~((uint32_t)ADC_ESTAT_I2TRGE);
            break;
        /* ADC inserted sequence3 trigger error interrupt */
        case ADC_INT_FLAG_I3TRGE:
            ADC_ESTAT(adc_periph) = ~((uint32_t)ADC_ESTAT_I3TRGE);
            break;
        /* ADC inserted sequence4 trigger error interrupt */
        case ADC_INT_FLAG_I4TRGE:
            ADC_ESTAT(adc_periph) = ~((uint32_t)ADC_ESTAT_I4TRGE);
            break;
        /* ADC inserted sequence5 trigger error interrupt */
        case ADC_INT_FLAG_I5TRGE:
            ADC_ESTAT(adc_periph) = ~((uint32_t)ADC_ESTAT_I5TRGE);
            break;
        /* DAC - ADC loop test error interrupt flag */
        case ADC_INT_FLAG_LTE:
            ADC_DTALTCFG(adc_periph) &= ~(uint32_t)ADC_DTALTCFG_LTE;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      get ADC sequence channel end of conversion flag (API_ID(0x0053U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_channel_flag_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0053U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0053U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0053U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            if(0U != (ADC_RCHINF(adc_periph) & ((uint32_t) (0x1U) << rank))) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            if(0U != (ADC_IxCHINTF(adc_periph, adc_sequence) & ((uint32_t) (0x1U) << rank))) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear ADC sequence channel end of conversion flag (API_ID(0x0054U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     none
*/
void adc_channel_flag_clear(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0054U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0054U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0054U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCHINF(adc_periph) = ~(0x1U << rank);
        } else {
            ADC_IxCHINTF(adc_periph, adc_sequence) = ~(0x1U << rank);
        }
    }
}

/*!
    \brief      enable ADC sequence channel end of conversion interrupt (API_ID(0x0055U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     none
*/
void adc_channel_interrupt_enable(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0055U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0055U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0055U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCFGx(adc_periph, rank) |= ((uint32_t)ADC_RCFG_RCHIE);
        } else {
            ADC_IxCFGy(adc_periph, adc_sequence, rank) |= ((uint32_t)ADC_ICFG_ICHIE);
        }
    }
}

/*!
    \brief      disable ADC sequence channel end of conversion interrupt (API_ID(0x0056U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     none
*/
void adc_channel_interrupt_disable(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0056U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0056U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0056U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCFGx(adc_periph, rank) &= ~((uint32_t)ADC_RCFG_RCHIE);
        } else {
            ADC_IxCFGy(adc_periph, adc_sequence, rank) &= ~((uint32_t)ADC_ICFG_ICHIE);
        }
    }
}

/*!
    \brief      get ADC sequence channel end of conversion interrupt flag (API_ID(0x0057U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_channel_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
    FlagStatus reval = RESET;
    uint32_t reg1;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0057U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0057U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0057U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            /*get routine sequence channel interrupt flag status */
            reg1 = ADC_RCFGx(adc_periph, rank) & ADC_RCFG_RCHIE;
            if((0U != (ADC_RCHINF(adc_periph) & ((uint32_t) (0x1U) << rank))) && (0U != reg1)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            /*get inserted sequence channel interrupt flag status */
            reg1 = ADC_IxCFGy(adc_periph, adc_sequence, rank) & ADC_ICFG_ICHIE;
            if((0U != (ADC_IxCHINTF(adc_periph, adc_sequence) & ((uint32_t) (0x1U) << rank))) && (0U != reg1)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear ADC sequence channel end of conversion interrupt flag (API_ID(0x0058U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     none
*/
void adc_channel_interrupt_flag_clear(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0058U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0058U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0058U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RCHINF(adc_periph) = ~(0x1U << rank);
        } else {
            ADC_IxCHINTF(adc_periph, adc_sequence) = ~(0x1U << rank);
        }
    }
}

/*!
    \brief      get the ADC stream conversion complete flag (API_ID(0x0059U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_stream_flag_get(uint32_t adc_periph, uint32_t adc_sequence)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0059U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0059U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            if(0U != (ADC_RSTREAM(adc_periph) & ADC_RSTREAM_RSTREAMF)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            if(0U != (ADC_IxSTREAM(adc_periph, adc_sequence) & ADC_ISTREAM_ISTREAMF)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear the ADC stream conversion complete flag (API_ID(0x005AU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     none
*/
void adc_stream_flag_clear(uint32_t adc_periph, uint32_t adc_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005AU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RSTREAM(adc_periph) &= ~(uint32_t)ADC_RSTREAM_RSTREAMF;
        } else {
            ADC_IxSTREAM(adc_periph, adc_sequence) &= ~(uint32_t)ADC_ISTREAM_ISTREAMF;
        }
    }
}

/*!
    \brief      get the ADC stream conversion complete interrupt flag (API_ID(0x005BU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_stream_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_sequence)
{
    FlagStatus reval = RESET;
    uint32_t state;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005BU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            state = (ADC_RSTREAM(adc_periph) & ADC_RSTREAM_RSTREAMF);
            if((0U != (ADC_RSTREAM(adc_periph) & ADC_RSTREAM_RSTREAMIE))&&(0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            state = (ADC_IxSTREAM(adc_periph, adc_sequence) & ADC_ISTREAM_ISTREAMF);
            if((0U !=(ADC_IxSTREAM(adc_periph, adc_sequence) & ADC_ISTREAM_ISTREAMIE))&&(0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear the ADC stream conversion complete interrupt flag (API_ID(0x005CU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     none
*/
void adc_stream_interrupt_flag_clear(uint32_t adc_periph, uint32_t adc_sequence)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005CU), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            ADC_RSTREAM(adc_periph) &= ~(uint32_t)ADC_RSTREAM_RSTREAMF;
        } else {
            ADC_IxSTREAM(adc_periph, adc_sequence) &= ~(uint32_t)ADC_ISTREAM_ISTREAMF;
        }
    }
}

/*!
    \brief      get ADC self test flag (API_ID(0x005DU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  flag: ADC self test flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_FLAG_STODE: selftest step order error flag
      \arg        ADC_SELFTEST_FLAG_WDTE: selftest watchdog timer error flag
      \arg        ADC_SELFTEST_FLAG_CSTE: selftest capacitive error flag
      \arg        ADC_SELFTEST_FLAG_SSTE0: selftest supply step0 error flag
      \arg        ADC_SELFTEST_FLAG_SSTE1: selftest supply step1 error flag
      \arg        ADC_SELFTEST_FLAG_SSTE2: selftest supply step2 error flag
      \arg        ADC_SELFTEST_FLAG_STEOVW: selftest error status overwrtie flag
      \arg        ADC_SELFTEST_FLAG_EOSSTC: all supply selftest steps end flag
      \arg        ADC_SELFTEST_FLAG_EOCSTC: all capacitive selftest steps end flag
      \arg        ADC_SELFTEST_FLAG_EOSTC: selftest end of conversion flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_selftest_flag_get(uint32_t adc_periph, uint32_t flag)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005DU), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_FLAG(flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (ADC_STSTAT(adc_periph) & flag)) {
            reval = SET;
        } else {
            /* illegal parameters */
        }
    }
    return reval;
}

/*!
    \brief      clear ADC selftest flag (API_ID(0x005EU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  flag: the ADC self test flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_FLAG_STODE: selftest step order error flag
      \arg        ADC_SELFTEST_FLAG_WDTE: selftest watchdog timer error flag
      \arg        ADC_SELFTEST_FLAG_CSTE: selftest capacitive error flag
      \arg        ADC_SELFTEST_FLAG_SSTE0: selftest supply step0 error flag
      \arg        ADC_SELFTEST_FLAG_SSTE1: selftest supply step1 error flag
      \arg        ADC_SELFTEST_FLAG_SSTE2: selftest supply step2 error flag
      \arg        ADC_SELFTEST_FLAG_STEOVW: selftest error status overwrtie flag
      \arg        ADC_SELFTEST_FLAG_EOSSTC: all supply selftest steps end flag
      \arg        ADC_SELFTEST_FLAG_EOCSTC: all capacitive selftest steps end flag
      \arg        ADC_SELFTEST_FLAG_EOSTC: selftest end of conversion flag
    \param[out] none
    \retval     none
*/
void adc_selftest_flag_clear(uint32_t adc_periph, uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005EU), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_FLAG(flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_STSTAT(adc_periph) = ~(uint32_t)flag;
    }
}

/*!
    \brief      enable ADC selftest interrupt (API_ID(0x005FU))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  interrupt: the ADC selftest interrupt
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_INT_FMUSSTEIE: interrupt for supply selftest error to FMU
      \arg        ADC_SELFTEST_INT_FMUCSTEIE: interrupt for capacitive selftest error to FMU
      \arg        ADC_SELFTEST_INT_FMUWDTEIE: interrupt for watchdog timer error to FMU
      \arg        ADC_SELFTEST_INT_FMUSTODEIE: interrup for selftest sequence error to FMU
      \arg        ADC_SELFTEST_INT_STODEIE: interrupt for step order error
      \arg        ADC_SELFTEST_INT_WDTEIE: interrupt for watchdog timer error
      \arg        ADC_SELFTEST_INT_CSTEIE: interrupt for capacitive selftest error
      \arg        ADC_SELFTEST_INT_SSTEIE0: interrupt for supply selftest step0 error
      \arg        ADC_SELFTEST_INT_SSTEIE1: interrupt for supply selftest step1 error
      \arg        ADC_SELFTEST_INT_SSTEIE2: interrupt for supply selftest step2 error
      \arg        ADC_SELFTEST_INT_STEOVWIE: interrupt for selftest error(SERR2,SERR1,SERR0,CERR) be overwrite
      \arg        ADC_SELFTEST_INT_EOSSTCIE: interrupt for all supply selftest end
      \arg        ADC_SELFTEST_INT_EOCSTCIE: interrupt for all capacitive selftest end
      \arg        ADC_SELFTEST_INT_EOSTCIE: interrupt for all selftest end
    \param[out] none
    \retval     none
*/
void adc_selftest_interrupt_enable(uint32_t adc_periph, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005FU), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_INTERRUPT(interrupt)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x005FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(interrupt) {
        /* enable the interrupt of supply selftest error to FMU enable */
        case ADC_SELFTEST_INT_FMUSSTEIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_FMUSSTEIE;
            break;
        /* enable the interrupt of capacitive selftest error to FMU enable */
        case ADC_SELFTEST_INT_FMUCSTEIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_FMUCSTEIE;
            break;
        /* enable the interrupt of watchdog timer error to FMU enable */
        case ADC_SELFTEST_INT_FMUWDTEIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_FMUWDTEIE;
            break;
        /* enable the interrupt of selftest sequence error to FMU enable */
        case ADC_SELFTEST_INT_FMUSTODEIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_FMUSTODEIE;
            break;
        /* enable the interrupt of selftest step order error enable */
        case ADC_SELFTEST_INT_STODEIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_STODEIE;
            break;
        /* enable the interrupt of watchdog timer error enable */
        case ADC_SELFTEST_INT_WDTEIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_WDTEIE;
            break;
        /* enable the interrupt of capacitive selftest error enable */
        case ADC_SELFTEST_INT_CSTEIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_CSTEIE;
            break;
        /* enable the interrupt of supply selftest step0 error enable */
        case ADC_STINTEN_SST0EIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_SST0EIE;
            break;
        /* enable the interrupt of supply selftest step1 error enable */
        case ADC_STINTEN_SST1EIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_SST1EIE;
            break;
        /* enable the interrupt of supply selftest step2 error enable */
        case ADC_STINTEN_SST2EIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_SST2EIE;
            break;
        /* enable the interrupt of selftest error(SERR2,SERR1,SERR0,CERR) be overwrite */
        case ADC_SELFTEST_INT_STEOVWIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_STEOVWIE;
            break;
        /* enable the interrupt of all supply selftest end enable */
        case ADC_SELFTEST_INT_EOSSTCIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_EOSSTCIE;
            break;
        /* enable the interrupt of all capacitive selftest end enable */
        case ADC_SELFTEST_INT_EOCSTCIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_EOCSTCIE;
            break;
        /* enable the interrupt of all selftest end enable */
        case ADC_SELFTEST_INT_EOSTCIE:
            ADC_STINTEN(adc_periph) |= (uint32_t)ADC_STINTEN_EOSTCIE;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      disable ADC selftest interrupt (API_ID(0x0060U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  interrupt: the ADC selftest interrupt
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_INT_FMUSSTEIE: interrupt for supply selftest error to FMU
      \arg        ADC_SELFTEST_INT_FMUCSTEIE: interrupt for capacitive selftest error to FMU
      \arg        ADC_SELFTEST_INT_FMUWDTEIE: interrupt for watchdog timer error to FMU
      \arg        ADC_SELFTEST_INT_FMUSTODEIE: interrup for selftest sequence error to FMU
      \arg        ADC_SELFTEST_INT_STODEIE: interrupt for step order error error
      \arg        ADC_SELFTEST_INT_WDTEIE: interrupt for watchdog timer error
      \arg        ADC_SELFTEST_INT_CSTEIE: interrupt for capacitive selftest error
      \arg        ADC_SELFTEST_INT_SSTEIE0: interrupt for supply selftest step0 error
      \arg        ADC_SELFTEST_INT_SSTEIE1: interrupt for supply selftest step1 error
      \arg        ADC_SELFTEST_INT_SSTEIE2: interrupt for supply selftest step2 error
      \arg        ADC_SELFTEST_INT_STEOVWIE: interrupt for selftest error(SERR2,SERR1,SERR0,CERR) be overwrite
      \arg        ADC_SELFTEST_INT_EOSSTCIE: interrupt for all supply selftest end
      \arg        ADC_SELFTEST_INT_EOCSTCIE: interrupt for all capacitive selftest end
      \arg        ADC_SELFTEST_INT_EOSTCIE: interrupt for all selftest end
    \param[out] none
    \retval     none
*/
void adc_selftest_interrupt_disable(uint32_t adc_periph, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0060U), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_INTERRUPT(interrupt)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0060U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(interrupt) {
        /* enable the interrupt of supply selftest error to FMU enable */
        case ADC_SELFTEST_INT_FMUSSTEIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_FMUSSTEIE;
            break;
        /* enable the interrupt of capacitive selftest error to FMU enable */
        case ADC_SELFTEST_INT_FMUCSTEIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_FMUCSTEIE;
            break;
        /* enable the interrupt of watchdog timer error to FMU enable */
        case ADC_SELFTEST_INT_FMUWDTEIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_FMUWDTEIE;
            break;
        /* enable the interrupt of selftest sequence error to FMU enable */
        case ADC_SELFTEST_INT_FMUSTODEIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_FMUSTODEIE;
            break;
        /* enable the interrupt of selftest step order error enable */
        case ADC_SELFTEST_INT_STODEIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_STODEIE;
            break;
        /* enable the interrupt of watchdog timer error enable */
        case ADC_SELFTEST_INT_WDTEIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_WDTEIE;
            break;
        /* enable the interrupt of capacitive selftest error enable */
        case ADC_SELFTEST_INT_CSTEIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_CSTEIE;
            break;
        /* enable the interrupt of supply selftest step0 error enable */
        case ADC_SELFTEST_INT_SSTEIE0:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_SST0EIE;
            break;
        /* enable the interrupt of supply selftest step1 error enable */
        case ADC_SELFTEST_INT_SSTEIE1:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_SST1EIE;
            break;
        /* enable the interrupt of supply selftest step2 error enable */
        case ADC_SELFTEST_INT_SSTEIE2:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_SST2EIE;
            break;
        /* enable the interrupt of selftest error(SERR2,SERR1,SERR0,CERR) be overwrite */
        case ADC_SELFTEST_INT_STEOVWIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_STEOVWIE;
            break;
        /* enable the interrupt of all supply selftest end enable */
        case ADC_SELFTEST_INT_EOSSTCIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_EOSSTCIE;
            break;
        /* enable the interrupt of all capacitive selftest end enable */
        case ADC_SELFTEST_INT_EOCSTCIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_EOCSTCIE;
            break;
        /* enable the interrupt of all selftest end enable */
        case ADC_SELFTEST_INT_EOSTCIE:
            ADC_STINTEN(adc_periph) &= ~(uint32_t)ADC_STINTEN_EOSTCIE;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      get ADC self test interrupt flag (API_ID(0x0061U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  int_flag: ADC self test flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_INT_FLAG_STODE: selftest step order error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_WDTE: selftest watchdog timer error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_CSTE: selftest capacitive error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_SSTE0: selftest supply step0 error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_SSTE1: selftest supply step1 error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_SSTE2: selftest supply step2 error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_STEOVW: selftest error status overwrtie interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_EOSSTC: all supply selftest steps end interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_EOCSTC: all capacitive selftest steps end interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_EOSTC: selftest end of conversion interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_selftest_interrupt_flag_get(uint32_t adc_periph, uint32_t int_flag)
{
    FlagStatus reval = RESET;
    uint32_t state;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0061U), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_INTERRUPT_FLAG(int_flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0061U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* check the interrupt bits */
        switch(int_flag) {
        case ADC_SELFTEST_INT_FLAG_STODE:
            /* get the selftest step order error interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_STODE;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_STODEIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_WDTE:
            /* get the selftest watchdog timer error interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_WDTE;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_WDTEIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_CSTE:
            /* get the selftest capacitive error interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_CSTE;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_CSTEIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_SSTE0:
            /* get the selftest supply step0 error interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_SST0E;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_SST0EIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_SSTE1:
            /* get the selftest supply step1 error interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_SST1E;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_SST1EIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_SSTE2:
            /* get the selftest supply step2 error interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_SST2E;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_SST2EIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_STEOVW:
            /* get the selftest error status overwrtie interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_STEOVW;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_STEOVWIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_EOSSTC:
            /* get all supply selftest steps end interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_EOSSTC;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_EOSSTCIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_EOCSTC:
            /* get all capacitive selftest steps end interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_EOCSTC;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_EOCSTCIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        case ADC_SELFTEST_INT_FLAG_EOSTC:
            /* get the selftest end of conversion interrupt flag */
            state = ADC_STSTAT(adc_periph) & ADC_STSTAT_EOSTC;
            if((0U != (ADC_STINTEN(adc_periph) & ADC_STINTEN_EOSTCIE)) && (0U != state)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
            break;
        default:
            break;
        }
    }
    return reval;
}

/*!
    \brief      clear ADC selftest flag (API_ID(0x0062U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  int_flag: the ADC self test flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_SELFTEST_INT_FLAG_STODE: selftest step order error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_WDTE: selftest watchdog timer error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_CSTE: selftest capacitive error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_SSTE0: selftest supply step0 error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_SSTE1: selftest supply step1 error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_SSTE2: selftest supply step2 error interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_STEOVW: selftest error status overwrtie interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_EOSSTC: all supply selftest steps end interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_EOCSTC: all capacitive selftest steps end interrupt flag
      \arg        ADC_SELFTEST_INT_FLAG_EOSTC: selftest end of conversion interrupt flag
    \param[out] none
    \retval     none
*/
void adc_selftest_interrupt_flag_clear(uint32_t adc_periph, uint32_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0062U), ERR_PERIPH);
    } else if(NOT_ADC_SELFTEST_INTERRUPT_FLAG(int_flag)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0062U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ADC_STSTAT(adc_periph) = ~(uint32_t)int_flag;
    }
}

/*!
    \brief      get ADC channel analog watchdog flag (API_ID(0x0063U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_channel: it can be 0~61
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_channel_analog_watchdog_flag_get(uint32_t adc_periph, uint32_t adc_channel)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0063U), ERR_PERIPH);
    } else if(NOT_ADC_CHANNEL(adc_channel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0063U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((31U < adc_channel) && (61U >= adc_channel)) {
            /* get channel 32~61 analog watchdog flag */
            if(0U != (ADC_WDINTF1(adc_periph) & ((uint32_t) (0x1U) << (adc_channel-32U)))) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            /* get channel 0~31 analog watchdog flag */
            if(0U != (ADC_WDINTF0(adc_periph) & ((uint32_t) (0x1U) << adc_channel))) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear ADC channel analog watchdog flag (API_ID(0x0064U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_channel: it can be 0~61 or 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void adc_channel_analog_watchdog_flag_clear(uint32_t adc_periph, uint32_t adc_channel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0064U), ERR_PERIPH);
    } else if(NOT_ADC_WATCHDOG_CHANNEL(adc_channel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0064U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((adc_channel > 31U) && (adc_channel <= 61U)) {
            /* clear channel 32~61 analog watchdog flag */
            ADC_WDINTF1(adc_periph) = ~(0x1U << (adc_channel-32U));
        } else if(adc_channel <= 31U) {
            /* clear channel 0~31 analog watchdog flag */
            ADC_WDINTF0(adc_periph) = ~(0x1U << adc_channel);
        } else if(0xFFFFFFFFU == adc_channel) {
            /* clear all channel flags */
            ADC_ESTAT(adc_periph) = ~(uint32_t)ADC_FLAG_WDE;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      get ADC channel analog watchdog interrupt flag (API_ID(0x0065U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_channel: it can be 0~61
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_channel_analog_watchdog_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_channel)
{
    FlagStatus reval = RESET;
    uint32_t index;
    uint32_t status;

    index = (ADC_CHCFGx(adc_periph, adc_channel) & ADC_CHCFG_WDSEL) >> 3U;
    status = ADC_WDTx(adc_periph, index) & ADC_WDT_WDEIE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0065U), ERR_PERIPH);
    } else if(NOT_ADC_CHANNEL(adc_channel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0065U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((31U < adc_channel) && (61U >= adc_channel)) {
            /* get channel 32~61 analog watchdog flag */
            if((0U != (ADC_WDINTF1(adc_periph) & ((uint32_t) (0x1U) << (adc_channel-32U)))) && (0U != status)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            /* get channel 0~31 analog watchdog flag */
            if((0U != (ADC_WDINTF0(adc_periph) & ((uint32_t) (0x1U) << adc_channel))) && (0U != status)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear ADC channel analog watchdog interrupt flag (API_ID(0x0066U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_channel: it can be 0~61 or 0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void adc_channel_analog_watchdog_interrupt_flag_clear(uint32_t adc_periph, uint32_t adc_channel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0066U), ERR_PERIPH);
    } else if(NOT_ADC_WATCHDOG_CHANNEL(adc_channel)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0066U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((adc_channel > 31U) && (adc_channel <= 61U)) {
            /* clear channel 32~61 analog watchdog interrupt flag */
            ADC_WDINTF1(adc_periph) = ~(0x1U << (adc_channel-32U));
        } else if(adc_channel <= 31U) {
            /* clear channel 0~31 analog watchdog interrupt flag */
            ADC_WDINTF0(adc_periph) = ~(0x1U << adc_channel);
        } else if(0xFFFFFFFFU == adc_channel) {
            /* clear all channel interrupt flags */
            ADC_ESTAT(adc_periph) = ~(uint32_t)ADC_FLAG_WDE;
        } else {
            /* illegal parameters */
        }
    }
}

/*!
    \brief      get ADC sequence channel overwrite interrupt flag (API_ID(0x0067U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  adc_sequence: select the sequence
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[in]  rank: the sequence rank, routine sequence is 0 to 27(ADC2 just supports 0 to 23), and inserted sequence is 0 to 3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_channel_overwrite_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank)
{
    FlagStatus reval = RESET;
    uint32_t reg1;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0067U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0067U), ERR_PARAM_INVALID);
    } else if(NOT_ADC_SEQUENCE_RANK(rank)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0067U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg1 = ADC_CTL(adc_periph) & ADC_CTL_CHOVWIE;
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            /*get routine sequence channel interrupt flag status */
            if((0U != (ADC_RCHDATAx(adc_periph,rank) & ADC_RCHDATA_RCHOVWF)) && (0U != reg1)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            /*get inserted sequence channel interrupt flag status */
            if((0U != (ADC_IxCHDATAy(adc_periph, adc_sequence, rank) & ADC_ICHDATA_ICHOVWF)) && (0U != reg1)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

/*!
    \brief      get the ADC sequence interrupt overwrite flag (API_ID(0x0068U))
    \param[in]  adc_periph: ADCx, x=0,1,2 (x=2 only available in GD32A714X, GD32A72XX and GD32A74XX)
    \param[in]  int_flag: the ADC interrupt flag bits
                only one parameter can be selected which is shown as below:
      \arg        ADC_ROUTINE_SEQUENCE: routine sequence
      \arg        ADC_INSERTED_SEQUENCE0: inserted sequence 0
      \arg        ADC_INSERTED_SEQUENCE1: inserted sequence 1
      \arg        ADC_INSERTED_SEQUENCE2: inserted sequence 2
      \arg        ADC_INSERTED_SEQUENCE3: inserted sequence 3
      \arg        ADC_INSERTED_SEQUENCE4: inserted sequence 4
      \arg        ADC_INSERTED_SEQUENCE5: inserted sequence 5
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus adc_overwrite_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_sequence)
{
    uint32_t reg1;
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_periph(adc_periph)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0069U), ERR_PERIPH);
    } else if(NOT_ADC_SEQUENCE(adc_sequence)) {
        fw_debug_report_err(ADC_MODULE_ID, API_ID(0x0069U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg1 = ADC_CTL(adc_periph) & ADC_CTL_OVWIE;
        if(ADC_ROUTINE_SEQUENCE == adc_sequence) {
            /*get routine sequence channel interrupt flag status */
            if((0U != (ADC_RDATA(adc_periph) & ADC_RDATA_ROVWF)) && (0U != reg1)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        } else {
            /*get inserted sequence channel interrupt flag status */
            if((0U != (ADC_IxDATA(adc_periph, adc_sequence) & ADC_IDATA_IOVWF)) && (0U != reg1)) {
                reval = SET;
            } else {
                /* illegal parameters */
            }
        }
    }
    return reval;
}

