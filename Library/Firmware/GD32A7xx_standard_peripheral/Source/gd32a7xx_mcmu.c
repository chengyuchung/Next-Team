/*!
    \file    gd32a7xx_mcmu.c
    \brief   MCMU driver

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
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#include "gd32a7xx_mcmu.h"

/*!
    \brief      get available MCMU parameter (API_ID: 0x0001U)
    \param[in]  mcmu_periph : parameter source, MCMUA or MCMUB
    \param[in]  para_type : parameter type
                only one parameter can be selected which is shown as below:
      \arg        MCMU_PAR_TRANSMIT : The number of transmit registers
      \arg        MCMU_PAR_RECEIVE  : The number of receive registers
      \arg        MCMU_PAR_NORMAL   : The number of normal interrupt requests available
      \arg        MCMU_PAR_SIGNAL   : The number of signal bits
    \param[out] none
    \retval     uint8_t: the available number of parameter
*/
uint8_t mcmu_parameter_get(uint32_t mcmu_periph, mcmu_parameter_enum para_type)
{
    uint8_t reval = 0U;
    uint8_t index_start;
    uint8_t index_end;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else if(NOT_MCMU_PARAMETER(para_type)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0001U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        index_start = (uint8_t)para_type << 3U;
        index_end = index_start + 7U;
        reval = (uint8_t)((MCMU_PAR(mcmu_periph) & BITS(index_start, index_end)) >> index_start);
    }
    return reval;
}

/*!
    \brief      reset MCMU register (API_ID: 0x0002U)
    \param[in]  mcmu_periph : reset trigger source, MCMUA or MCMUB
    \param[out] none
    \retval     none
*/
void mcmu_reset(uint32_t mcmu_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0002U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* reset MCMU */
        MCMU_CTL(mcmu_periph) = MCMU_CTL_SWRST;
    }
}

/*!
    \brief      set the signal to the other MCMU (API_ID: 0x0003U)
    \param[in]  mcmu_periph : signal source, MCMUA or MCMUB
    \param[in]  signal : signal index
                one or more parameters can be selected which are shown as below:
      \arg        MCMU_SIGNAL0: MCMU signal0 to the other MCMU
      \arg        MCMU_SIGNAL1: MCMU signal1 to the other MCMU
      \arg        MCMU_SIGNAL2: MCMU signal2 to the other MCMU
    \param[out] none
    \retval     none
*/
void mcmu_signal_set(uint32_t mcmu_periph, uint32_t signal)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_MCMU_SIGNAL(signal)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        MCMU_SCTL(mcmu_periph) |= signal;
    }
}

/*!
    \brief      clear the signal to the other MCMU (API_ID: 0x0004U)
    \param[in]  mcmu_periph : signal source, MCMUA or MCMUB
    \param[in]  signal : signal index
                one or more parameters can be selected which are shown as below:
      \arg        MCMU_SIGNAL0: MCMU signal0 to the other MCMU
      \arg        MCMU_SIGNAL1: MCMU signal1 to the other MCMU
      \arg        MCMU_SIGNAL2: MCMU signal2 to the other MCMU
    \param[out] none
    \retval     none
*/
void mcmu_signal_clear(uint32_t mcmu_periph, uint32_t signal)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else if(NOT_MCMU_SIGNAL(signal)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        MCMU_SCTL(mcmu_periph) &= ~(signal);
    }
}

/*!
    \brief      generate the normal interrupt to the other MCMU (API_ID: 0x0005U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[out] none
    \retval     none
*/
void mcmu_normal_interrupt_request(uint32_t mcmu_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        MCMU_NINTCTL(mcmu_periph) |= MCMU_NINTCTL_NIR0;
    }
}

/*!
    \brief      transmit data (API_ID: 0x0006U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  chy : transmit channel, 0~3
    \param[in]  data : transmit data, 0~0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void mcmu_transmit_data(uint32_t mcmu_periph, uint32_t chy, uint32_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else if(NOT_MCMU_DATA_CHANNEL(chy)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0006U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        MCMU_TDATA(mcmu_periph, chy) = data;
    }
}

/*!
    \brief      receive data (API_ID: 0x0007U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  chy : receive channel, 0~3
    \param[out] none
    \retval     data : receive data, 0~0xFFFFFFFF
*/
uint32_t mcmu_receive_data(uint32_t mcmu_periph, uint32_t chy)
{
    uint32_t reval = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else if(NOT_MCMU_DATA_CHANNEL(chy)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0007U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = MCMU_RDATA(mcmu_periph, chy);
    }
    return reval;
}

/*!
    \brief      mcmu interrupt enable (API_ID: 0x0008U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  interrupt : mcmu interrupts
                only one parameter can be selected which is shown as below:
      \arg        MCMU_INT_NIF0  : normal interrupt
      \arg        MCMU_INT_TEF0  : transmit interrupt 0
      \arg        MCMU_INT_TEF1  : transmit interrupt 1
      \arg        MCMU_INT_TEF2  : transmit interrupt 2
      \arg        MCMU_INT_TEF3  : transmit interrupt 3
      \arg        MCMU_INT_RNEF0 : receive interrupt 0
      \arg        MCMU_INT_RNEF1 : receive interrupt 1
      \arg        MCMU_INT_RNEF2 : receive interrupt 2
      \arg        MCMU_INT_RNEF3 : receive interrupt 3
    \param[out] none
    \retval     none
*/
void mcmu_interrupt_enable(uint32_t mcmu_periph, mcmu_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else if(NOT_MCMU_INTERRUPT(interrupt)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        MCMU_REG_VAL(mcmu_periph, interrupt) |= BIT(MCMU_BIT_POS(interrupt));
    }
}

/*!
    \brief      mcmu interrupt disable (API_ID: 0x0009U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  interrupt : mcmu interrupts
                only one parameter can be selected which is shown as below:
      \arg        MCMU_INT_NIF0  : normal interrupt
      \arg        MCMU_INT_TEF0  : transmit interrupt 0
      \arg        MCMU_INT_TEF1  : transmit interrupt 1
      \arg        MCMU_INT_TEF2  : transmit interrupt 2
      \arg        MCMU_INT_TEF3  : transmit interrupt 3
      \arg        MCMU_INT_RNEF0 : receive interrupt 0
      \arg        MCMU_INT_RNEF1 : receive interrupt 1
      \arg        MCMU_INT_RNEF2 : receive interrupt 2
      \arg        MCMU_INT_RNEF3 : receive interrupt 3
    \param[out] none
    \retval     none
*/
void mcmu_interrupt_disable(uint32_t mcmu_periph, mcmu_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else if(NOT_MCMU_INTERRUPT(interrupt)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        MCMU_REG_VAL(mcmu_periph, interrupt) &= ~BIT(MCMU_BIT_POS(interrupt));
    }
}

/*!
    \brief      get mcmu flag status (API_ID: 0x000AU)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  flag : mcmu flags type
                only one parameter can be selected which is shown as below:
      \arg        MCMU_FLAG_RSTSF   : MCMU reset state flag
      \arg        MCMU_FLAG_RSTIF   : MCMU reset interrupt flag
      \arg        MCMU_FLAG_EVF     : MCMU side event flag
      \arg        MCMU_FLAG_SUF     : MCMU Signal update flag
      \arg        MCMU_FLAG_NIF     : MCMU Normal interrupt flag
      \arg        MCMU_FLAG_TEF     : MCMU Transmit empty flag
      \arg        MCMU_FLAG_RNEF    : MCMU Receive not empty flag
      \arg        MCMU_FLAG_SIGNAL0 : signal0 to the other MCMU
      \arg        MCMU_FLAG_SIGNAL1 : signal1 to the other MCMU
      \arg        MCMU_FLAG_SIGNAL2 : signal2 to the other MCMU
      \arg        MCMU_FLAG_SIGNAL0S: signal0 from the other MCMU
      \arg        MCMU_FLAG_SIGNAL1S: signal1 from the other MCMU
      \arg        MCMU_FLAG_SIGNAL2S: signal2 from the other MCMU
      \arg        MCMU_FLAG_NIR0    : normal interrupt request (only be cleared by the other MCMU)
      \arg        MCMU_FLAG_NIF0    : normal interrupt flag from the other MCMU
      \arg        MCMU_FLAG_TEF0    : transmit data register 0 empty flag
      \arg        MCMU_FLAG_TEF1    : transmit data register 1 empty flag
      \arg        MCMU_FLAG_TEF2    : transmit data register 2 empty flag
      \arg        MCMU_FLAG_TEF3    : transmit data register 3 empty flag
      \arg        MCMU_FLAG_RNEF0   : receive data register 0 not empty
      \arg        MCMU_FLAG_RNEF1   : receive data register 1 not empty
      \arg        MCMU_FLAG_RNEF2   : receive data register 2 not empty
      \arg        MCMU_FLAG_RNEF3   : receive data register 3 not empty
    \param[out] none
    \retval     FlagStatus : SET or RESET
*/
FlagStatus mcmu_flag_get(uint32_t mcmu_periph, mcmu_flag_enum flag)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else if(NOT_MCMU_GET_FLAG(flag)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (MCMU_REG_VAL(mcmu_periph, flag) & BIT(MCMU_BIT_POS(flag)))) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      mcmu flag clear (API_ID: 0x000BU)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  flag : mcmu flags type
                only one parameter can be selected which is shown as below:
      \arg        MCMU_FLAG_RSTIF   : MCMU reset interrupt flag
      \arg        MCMU_FLAG_NIF0    : normal interrupt flag from the other MCMU
    \param[out] none
    \retval     none
*/
void mcmu_flag_clear(uint32_t mcmu_periph, mcmu_flag_enum flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else if(NOT_MCMU_CLEAR_FLAG(flag)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear by write 1 */
        MCMU_REG_VAL(mcmu_periph, flag) = BIT(MCMU_BIT_POS(flag));
    }
}

/*!
    \brief      get mcmu interrupt flag status (API_ID: 0x000CU)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  flag : mcmu flags
                only one parameter can be selected which is shown as below:
      \arg        MCMU_INT_FLAG_NIF0   : normal interrupt flag from the other MCMU
      \arg        MCMU_INT_FLAG_TEF0   : transmit data register 0 empty flag
      \arg        MCMU_INT_FLAG_TEF1   : transmit data register 1 empty flag
      \arg        MCMU_INT_FLAG_TEF2   : transmit data register 2 empty flag
      \arg        MCMU_INT_FLAG_TEF3   : transmit data register 3 empty flag
      \arg        MCMU_INT_FLAG_RNEF0  : receive data register 0 not empty flag
      \arg        MCMU_INT_FLAG_RNEF1  : receive data register 1 not empty flag
      \arg        MCMU_INT_FLAG_RNEF2  : receive data register 2 not empty flag
      \arg        MCMU_INT_FLAG_RNEF3  : receive data register 3 not empty flag
    \param[out] none
    \retval     FlagStatus : SET or RESET
*/
FlagStatus mcmu_interrupt_flag_get(uint32_t mcmu_periph, mcmu_interrupt_flag_enum int_flag)
{
    FlagStatus reval = RESET;
    uint32_t intenable;
    uint32_t flagstatus;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else if(NOT_MCMU_INTERRUPT_GET_FLAG(int_flag)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the interrupt enable bit status */
        intenable = (MCMU_REG_VAL2(mcmu_periph, int_flag) & BIT(MCMU_BIT_POS2(int_flag)));
        /* get the corresponding flag bit status */
        flagstatus = (MCMU_REG_VAL(mcmu_periph, int_flag) & BIT(MCMU_BIT_POS(int_flag)));

        if((flagstatus != 0U) && (intenable != 0U)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear mcmu interrupt flag (API_ID: 0x000DU)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  flag : mcmu flags
                only one parameter can be selected which is shown as below:
      \arg        MCMU_INT_FLAG_NIF0    : normal interrupt flag from the other MCMU
    \param[out] none
    \retval     FlagStatus : SET or RESET
*/
void mcmu_interrupt_flag_clear(uint32_t mcmu_periph, mcmu_interrupt_flag_enum int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    } else if(NOT_MCMU_INTERRUPT_CLEAR_FLAG(int_flag)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear by write 1 */
        MCMU_REG_VAL(mcmu_periph, int_flag) = BIT(MCMU_BIT_POS(int_flag));
    }
}


/*!
    \brief      enable parity error report to FMU (API_ID: 0x000EU)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  chy : receive channel, 0~3
    \param[out] none
    \retval     none
*/
void mcmu_parity_error_report_enable(uint32_t mcmu_periph, uint32_t chy)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    } else if(NOT_MCMU_DATA_CHANNEL(chy)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000EU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        MCMU_PERRFE(mcmu_periph) |= BIT(chy);
    }
}

/*!
    \brief      disable parity error report to FMU (API_ID: 0x000FU)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  chy : receive channel, 0~3
    \param[out] none
    \retval     none
*/
void mcmu_parity_error_report_disable(uint32_t mcmu_periph, uint32_t chy)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    } else if(NOT_MCMU_DATA_CHANNEL(chy)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x000FU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        MCMU_PERRFE(mcmu_periph) &= ~(BIT(chy));
    }
}

/*!
    \brief      parity error state get (API_ID: 0x0010U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  chy : receive channel, 0~3
    \param[out] none
    \retval     FlagStatus : SET or RESET
*/
FlagStatus mcmu_parity_error_get(uint32_t mcmu_periph, uint32_t chy)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    } else if(NOT_MCMU_DATA_CHANNEL(chy)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0010U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (MCMU_PERRSTAT(mcmu_periph) & BIT(chy))) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      parity error clear (API_ID: 0x0011U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  chy : receive channel, 0~3
    \param[out] none
    \retval     none
*/
void mcmu_parity_error_clear(uint32_t mcmu_periph, uint32_t chy)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else if(NOT_MCMU_DATA_CHANNEL(chy)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0011U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear by write 1 */
        MCMU_PERRSTAT(mcmu_periph) = BIT(chy);
    }
}

/*!
    \brief      tmr error report to FMU (API_ID: 0x0012U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  tmr : mcmu tmr fault
                one or more parameters can be selected which are shown as below:
      \arg        MCMU_TMR_ALARM_SCTL: TMR fault alarm of SCTL register to FMU
      \arg        MCMU_TMR_ALARM_NINT: TMR fault alarm of NINTEN and NINTCTL registers to FMU
      \arg        MCMU_TMR_ALARM_TINT: TMR fault alarm of TINTCTL register to FMU
      \arg        MCMU_TMR_ALARM_RINT: TMR fault alarm of RINTCTL register to FMU
    \param[out] none
    \retval     none
*/
void mcmu_tmr_error_report_enable(uint32_t mcmu_periph, uint32_t tmr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else if(NOT_MCMU_TMR_ALARM(tmr)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* prevent the upper 16 bit being cleared by write 1 */
        MCMU_TMRFACS(mcmu_periph) = (MCMU_TMRFACS(mcmu_periph) & 0x0000FFFFUL) | tmr;
    }
}

/*!
    \brief      tmr error did not report to FMU (API_ID: 0x0013U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  tmr : mcmu tmr fault
                one or more parameters can be selected which are shown as below:
      \arg        MCMU_TMR_ALARM_SCTL: TMR fault alarm of SCTL register to FMU
      \arg        MCMU_TMR_ALARM_NINT: TMR fault alarm of NINTEN and NINTCTL registers to FMU
      \arg        MCMU_TMR_ALARM_TINT: TMR fault alarm of TINTCTL register to FMU
      \arg        MCMU_TMR_ALARM_RINT: TMR fault alarm of RINTCTL register to FMU
    \param[out] none
    \retval     none
*/
void mcmu_tmr_error_report_disable(uint32_t mcmu_periph, uint32_t tmr)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    } else if(NOT_MCMU_TMR_ALARM(tmr)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* prevent the upper 16 bit being cleared by write 1 */
        MCMU_TMRFACS(mcmu_periph) = (MCMU_TMRFACS(mcmu_periph) & 0x0000FFFFUL) & (~tmr);
    }
}

/*!
    \brief      tmr error flag get (API_ID: 0x0014U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  tmrflag : mcmu tmr flags
                only one parameter can be selected which are shown as below:
      \arg        MCMU_TMR_FLAG_SCTL: TMR fault alarm flag of SCTL register
      \arg        MCMU_TMR_FLAG_NINT: TMR fault alarm flag of NINTEN and NINTCTL registers
      \arg        MCMU_TMR_FLAG_TINT: TMR fault alarm flag of TINTCTL register
      \arg        MCMU_TMR_FLAG_RINT: TMR fault alarm flag of RINTCTL register
    \param[out] none
    \retval     FlagStatus : SET or RESET
*/
FlagStatus mcmu_tmr_error_get(uint32_t mcmu_periph, uint32_t tmr_flag)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    } else if(NOT_MCMU_TMR_FLAG(tmr_flag)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0014U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (MCMU_TMRFACS(mcmu_periph) & tmr_flag)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      tmr error flag clear (API_ID: 0x0015U)
    \param[in]  mcmu_periph : MCMUA or MCMUB
    \param[in]  tmrflag : mcmu tmr flags
                one or more parameters can be selected which are shown as below:
      \arg        MCMU_TMR_FLAG_SCTL: TMR fault alarm flag of SCTL register
      \arg        MCMU_TMR_FLAG_NINT: TMR fault alarm flag of NINTEN and NINTCTL registers
      \arg        MCMU_TMR_FLAG_TINT: TMR fault alarm flag of TINTCTL register
      \arg        MCMU_TMR_FLAG_RINT: TMR fault alarm flag of RINTCTL register
    \param[out] none
    \retval     none
*/
void mcmu_tmr_error_clear(uint32_t mcmu_periph, uint32_t tmr_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MCMU_PERIPH(mcmu_periph)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    } else if(NOT_MCMU_TMR_FLAG(tmr_flag)) {
        fw_debug_report_err(MCMU_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* prevent the upper 16 bit being cleared by write 1 */
        MCMU_TMRFACS(mcmu_periph) = (MCMU_TMRFACS(mcmu_periph) & 0x0000FFFFUL) | tmr_flag;
    }
}
#endif /* #if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
