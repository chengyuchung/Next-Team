/*!
    \file    gd32a7xx_ioc.c
    \brief   IOC driver

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

#include "gd32a7xx_ioc.h"

/*!
    \brief      enable IOC (API_ID: 0x0001U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_enable(void)
{
    IOC_CTL &= ~(IOC_CTL_IOCEN);
}

/*!
    \brief      disable IOC (API_ID: 0x0002U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_disable(void)
{
    IOC_CTL |= IOC_CTL_IOCEN;
}

/*!
    \brief      reset IOC (API_ID: 0x0003U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_reset(void)
{
    IOC_RST0 |= IOC_RST0_RST0;
    IOC_RST1 |= IOC_RST1_RST1;
}

/*!
    \brief      get IOC enable flag (API_ID: 0x0004U)
    \param[in]  none
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus ioc_enable_flag_get(void)
{
    FlagStatus reval;
    if(0U == ((IOC_CTL & IOC_CTL_IOCENF))) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      get IOC reset flag (API_ID: 0x0005U)
    \param[in]  none
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus ioc_reset_flag_get(void)
{
    FlagStatus reval;
    if((uint32_t)RESET != (IOC_RST1 & (IOC_RST1_RSTF))) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear IOC reset flag (API_ID: 0x0006U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_reset_flag_clear(void)
{
    IOC_RSTSTATC |= IOC_RSTSTATC_RSTFC;
}

/*!
    \brief      enable IOC clock (API_ID: 0x0007U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_clock_enable(void)
{
    IOC_CTL &= ~(IOC_CTL_CLKEN);
}

/*!
    \brief      disable IOC clock (API_ID: 0x0008U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_clock_disable(void)
{
    IOC_CTL |= IOC_CTL_CLKEN;
}

/*!
    \brief      configure IOC clock prescaler (API_ID: 0x0009U)
    \param[in]  psc: 0-0x000000FF, clock prescaler
    \param[out] none
    \retval     none
*/
void ioc_prescaler_config(uint8_t psc)
{
    IOC_CTL &= ~IOC_CTL_PSC;
    IOC_CTL |= ((uint32_t)psc << 8U);
}

/*!
    \brief      configure IOC FPM mode (API_ID: 0x000AU)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[in]  fpm_mode: FPM mode
                only one parameter can be selected which is shown as below:
      \arg        DLY_DEB_BOTH_EDGE: delayed debounce filter mode on both edges
      \arg        IMM_DEB_BOTH_EDGE: immediate debounce filter mode on both edges
      \arg        IMM_DEBE_R_EDGE: immediate debounce filter mode on rising edge, no filtering on falling edge
      \arg        IMM_DEBE_F_EDGE: no filtering on rising edge, immediate debounce filter mode on falling edge
      \arg        DLY_DEB_R_EDGE_IMM_DEB_F_EDGE: delayed debounce filter mode on rising edge, immediate debounce filter mode on falling edge
      \arg        IMM_DEB_R_EDGE_DLY_DEB_F_EDGE: immediate debounce filter mode on rising edge, delayed debounce filter mode on falling edge
      \arg        PRESCALER_R_EDGE: prescaler mode (triggered on rising edge)
      \arg        PRESCALER_F_EDGE: prescaler mode (triggered on falling edge)
    \param[out] none
    \retval     none
*/
void ioc_fpm_mode_config(ioc_fpmx_enum fpmx, uint32_t fpm_mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FPM_MODE(fpm_mode)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_FPMCFG((uint32_t)fpmx) &= ~IOC_FPMX_CFG_MSEL;
        IOC_FPMCFG((uint32_t)fpmx) |= fpm_mode;
    }
}

/*!
    \brief      configure IOC FPM reference input signal selection (API_ID: 0x000BU)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[in]  input_signal: reference input signal
                only one parameter can be selected which is shown as below:
      \arg        FPM_SO_REF: select FPMx_SO
      \arg        IOC_REFERENCE: select IOC_reference[x]
      \arg        RSG_REFERENCE: select RSG_reference[x]
    \param[out] none
    \retval     none
*/
void ioc_fpm_reference_signal_select(ioc_fpmx_enum fpmx, uint32_t input_signal)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FPM_REF_INPUT_SIGNAL(input_signal)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_FPMCFG((uint32_t)fpmx) &= ~IOC_FPMX_CFG_RISEL;
        IOC_FPMCFG((uint32_t)fpmx) |= input_signal;
    }
}

/*!
    \brief      configure IOC FPM monitor input signal selection (API_ID: 0x000CU)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[in]  input_signal: monitor input signal
                only one parameter can be selected which is shown as below:
      \arg        FPM_SO_MON: select FPMx_SO
      \arg        IOC_MONITOR: select IOC_rmonitor[x]
    \param[out] none
    \retval     none
*/
void ioc_fpm_monitor_signal_select(ioc_fpmx_enum fpmx, uint32_t input_signal)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FPM_MON_INPUT_SIGNAL(input_signal)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_FPMCFG((uint32_t)fpmx) &= ~IOC_FPMX_CFG_MISEL;
        IOC_FPMCFG((uint32_t)fpmx) |= input_signal;
    }
}

/*!
    \brief      enable reset the counter of timer (API_ID: 0x000DU)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[out] none
    \retval     none
*/
void ioc_fpm_timer_reset_enable(ioc_fpmx_enum fpmx)
{
    IOC_FPMCFG((uint32_t)fpmx) |= IOC_FPMX_CFG_RCNT;
}

/*!
    \brief      disable reset the counter of timer, decrement the counter by one (API_ID: 0x000EU)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[out] none
    \retval     none
*/
void ioc_fpm_timer_reset_disable(ioc_fpmx_enum fpmx)
{
    IOC_FPMCFG((uint32_t)fpmx) &= ~IOC_FPMX_CFG_RCNT;
}

/*!
    \brief      configure the value of 16 bit comparator (API_ID: 0x000FU)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[in]  value: 0x0000-0xFFFF, the value of 16 bit comparator
    \param[out] none
    \retval     none
*/
void ioc_fpm_cmp_config(ioc_fpmx_enum fpmx, uint16_t value)
{
    IOC_FPMCFG((uint32_t)fpmx) &= ~IOC_FPMX_CFG_CMP;
    IOC_FPMCFG((uint32_t)fpmx) |= value;
}

/*!
    \brief      get the value of reference signal FPM timer counter (API_ID: 0x0010U)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[out] none
    \retval     none
*/
uint32_t ioc_rfpm_counter_get(ioc_fpmx_enum fpmx)
{
    uint32_t reval;
    reval = IOC_RFPMCNT((uint32_t)fpmx);
    return reval;
}

/*!
    \brief      get the value of monitor signal FPM timer counter (API_ID: 0x0011U)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[out] none
    \retval     none
*/
uint32_t ioc_mfpm_counter_get(ioc_fpmx_enum fpmx)
{
    uint32_t reval;
    reval = IOC_MFPMCNT((uint32_t)fpmx);
    return reval;
}

/*!
    \brief      get reference signal FPM edge status (API_ID: 0x0012U)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[in]  edge_flag: FPM edge status flag, refer to ioc_fpm_edge_stat_enum
                only one parameter can be selected which is shown as below:
      \arg        FPM_FLAG_FALLING_EDGE: FPM falling edge flag
      \arg        FPM_FLAG_RISING_EDGE: FPM rising edge flag
    \param[out] none
    \retval     none
*/
FlagStatus ioc_rfpm_glitch_flag_get(ioc_fpmx_enum fpmx, ioc_fpm_edge_stat_enum edge_flag)
{
    FlagStatus reval;
    uint32_t flagstatus;

    if(FPM_FLAG_FALLING_EDGE == edge_flag) {
        flagstatus = (uint32_t)(IOC_RFPMESTAT >> (uint32_t)fpmx);
    } else {
        flagstatus = (uint32_t)(IOC_RFPMESTAT >> ((uint32_t)fpmx + 16U));
    }

    if(0U != (flagstatus & 0x01U)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      get monitor signal FPM edge status (API_ID: 0x0013U)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[in]  edge_flag: FPM edge status flag, refer to ioc_fpm_edge_stat_enum
                only one parameter can be selected which is shown as below:
      \arg        FPM_FLAG_FALLING_EDGE: FPM falling edge flag
      \arg        FPM_FLAG_RISING_EDGE: FPM rising edge flag
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus ioc_mfpm_glitch_flag_get(ioc_fpmx_enum fpmx, ioc_fpm_edge_stat_enum edge_flag)
{
    FlagStatus reval;
    uint32_t flagstatus;

    if(FPM_FLAG_FALLING_EDGE == edge_flag) {
        flagstatus = (uint32_t)(IOC_MFPMESTAT >> (uint32_t)fpmx);
    } else {
        flagstatus = (uint32_t)(IOC_MFPMESTAT >> ((uint32_t)fpmx + 16U));
    }

    if(0U != (flagstatus & 0x01U)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear reference signal FPM edge status (API_ID: 0x0014U)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[in]  edge_flag: FPM edge status flag, refer to ioc_fpm_edge_stat_enum
                only one parameter can be selected which is shown as below:
      \arg        FPM_FLAG_FALLING_EDGE: FPM falling edge flag
      \arg        FPM_FLAG_RISING_EDGE: FPM rising edge flag
    \param[out] none
    \retval     none
*/
void ioc_rfpm_glitch_flag_clear(ioc_fpmx_enum fpmx, ioc_fpm_edge_stat_enum edge_flag)
{
    if(FPM_FLAG_FALLING_EDGE == edge_flag) {
        IOC_RFPMESTAT &= ~((uint32_t)1U << (uint32_t)fpmx);
    } else {
        IOC_RFPMESTAT &= ~((uint32_t)1U << ((uint32_t)fpmx + 16U));
    }
}

/*!
    \brief      clear reference signal FPM edge status(API_ID: 0x0015U)
    \param[in]  fpmx: FPMx, refer to ioc_fpmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FPM0
      \arg        IOC_FPM1
      \arg        IOC_FPM2
      \arg        IOC_FPM3
      \arg        IOC_FPM4
      \arg        IOC_FPM5
      \arg        IOC_FPM6
      \arg        IOC_FPM7
    \param[in]  edge_flag: FPM edge status flag, refer to ioc_fpm_edge_stat_enum
                only one parameter can be selected which is shown as below:
      \arg        FPM_FLAG_FALLING_EDGE: FPM falling edge flag
      \arg        FPM_FLAG_RISING_EDGE: FPM rising edge flag
    \param[out] none
    \retval     none
*/
void ioc_mfpm_glitch_flag_clear(ioc_fpmx_enum fpmx, ioc_fpm_edge_stat_enum edge_flag)
{
    if(FPM_FLAG_FALLING_EDGE == edge_flag) {
        IOC_MFPMESTAT &= ~((uint32_t)1U << (uint32_t)fpmx);
    } else {
        IOC_MFPMESTAT &= ~((uint32_t)1U << ((uint32_t)fpmx + 16U));
    }
}

/*!
    \brief      enable TRIGSEL input selection for RSG combiner (API_ID: 0x0016U)
    \param[in]  trigsel_input: TRIGSEL input
                only one parameter can be selected which is shown as below:
      \arg        RSG_TRIGSEL_INPUT0
      \arg        RSG_TRIGSEL_INPUT1
      \arg        RSG_TRIGSEL_INPUT2
      \arg        RSG_TRIGSEL_INPUT3
      \arg        RSG_TRIGSEL_INPUT4
      \arg        RSG_TRIGSEL_INPUT5
      \arg        RSG_TRIGSEL_INPUT6
      \arg        RSG_TRIGSEL_INPUT7
    \param[out] none
    \retval     none
*/
void ioc_rsg_input_enable(uint32_t trigsel_input)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RSG_TRIGSEL_INPUT(trigsel_input)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_RICTL |= trigsel_input;
    }
}

/*!
    \brief      disable TRIGSEL input selection for RSG combiner (API_ID: 0x0017U)
    \param[in]  trigsel_input: TRIGSEL input
                only one parameter can be selected which is shown as below:
      \arg        RSG_TRIGSEL_INPUT0
      \arg        RSG_TRIGSEL_INPUT1
      \arg        RSG_TRIGSEL_INPUT2
      \arg        RSG_TRIGSEL_INPUT3
      \arg        RSG_TRIGSEL_INPUT4
      \arg        RSG_TRIGSEL_INPUT5
      \arg        RSG_TRIGSEL_INPUT6
      \arg        RSG_TRIGSEL_INPUT7
    \param[out] none
    \retval     none
*/
void ioc_rsg_input_disable(uint32_t trigsel_input)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RSG_TRIGSEL_INPUT(trigsel_input)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_RICTL &= ~trigsel_input;
    }
}

/*!
    \brief      select reference signal (API_ID: 0x0018U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[in]  ref_signal: reference signal
                only one parameter can be selected which is shown as below:
      \arg        REFERENCE0
      \arg        REFERENCE1
      \arg        REFERENCE2
      \arg        REFERENCE3
      \arg        REFERENCE4
      \arg        REFERENCE5
      \arg        REFERENCE6
      \arg        REFERENCE7
    \param[out] none
    \retval     none
*/
void ioc_egm_reference_signal_select(ioc_egmx_enum egmx, uint32_t ref_signal)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_EGM_REFERENCE_SIGNAL(ref_signal)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_REFSIGS;
        IOC_EGMCTL((uint32_t)egmx) |= ref_signal;
    }
}

/*!
    \brief      select monitor signal (API_ID: 0x0019U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[in]  mon_signal: monitor signal
                only one parameter can be selected which is shown as below:
      \arg        MONITOR0
      \arg        MONITOR1
      \arg        MONITOR2
      \arg        MONITOR3
      \arg        MONITOR4
      \arg        MONITOR5
      \arg        MONITOR6
      \arg        MONITOR7
    \param[out] none
    \retval     none
*/
void ioc_egm_monitor_signal_select(ioc_egmx_enum egmx, uint32_t mon_signal)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_EGM_MONITOR_SIGNAL(mon_signal)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_MONSIGS;
        IOC_EGMCTL((uint32_t)egmx) |= mon_signal;
    }
}

/*!
    \brief      enable invert reference signal (API_ID: 0x001AU)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_reference_signal_invert_enable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) |= IOC_EGMXCTL_INVREN;
}

/*!
    \brief      disable invert reference signal (API_ID: 0x001BU)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_reference_signal_invert_disable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_INVREN;
}

/*!
    \brief      enable invert monitor signal (API_ID: 0x001CU)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_monitor_signal_invert_enable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) |= IOC_EGMXCTL_INVMEN;
}

/*!
    \brief      disable invert monitor signal (API_ID: 0x001DU)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_monitor_signal_invert_disable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_INVMEN;
}

/*!
    \brief      slect event window generation signal (API_ID: 0x001EU)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[in]  signal: event window generation signal
                only one parameter can be selected which is shown as below:
      \arg        EVENT_TRI_REFERENCE_SIGNAL: reference signal
      \arg        EVENT_TRI_MONITOR_SIGNAL: monitor signal
    \param[out] none
    \retval     none
*/
void ioc_egm_event_window_signal_select(ioc_egmx_enum egmx, uint32_t signal)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_EVENT_WIN_GENERATION_SIGNAL(signal)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_EWGSIGS;
        IOC_EGMCTL((uint32_t)egmx) |= signal;
    }
}

/*!
    \brief      select event window triger edge (API_ID: 0x001FU)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[in]  triger_edge: event window triger edge
                only one parameter can be selected which is shown as below:
      \arg        NO_EDGE_CLR_GATE: neither edge used to clear event window counter. neither edge used to gate event generation.
      \arg        REDGE_CLR: rising edge used to clear event window counter. neither edge used to gate event generation.
      \arg        FEDGE_CLR: falling edge used to clear event window counter. neither edge used to gate event generation.
      \arg        BOTH_EDGE_CLR: both rising and falling edges used to clear event window counter. neither edge used to gate event generation.
      \arg        REDGE_GATE: neither edge used to clear event window counter. rising edge used to gate event generation.
      \arg        REDGE_CLR_REDGE_GATE: rising edge used to clear event window counter. rising edge used to gate event generation.
      \arg        FEDGE_CLR_REDGE_GATE: falling edge used to clear event window counter. rising edge used to gate event generation.
      \arg        BOTH_EDGE_CLR_REDGE_GATE: both rising and falling edges used to clear event window counter. rising edge used to gate event generation.
      \arg        FEDGE_GATE: neither edge used to clear event window counter. falling edge used to gate event generation.
      \arg        REDGE_CLR_FEDGE_GATE: rising edge used to clear event window counter. falling edge used to gate event generation.
      \arg        FEDGE_CLR_FEDGE_GATE:Falling edge used to clear event window counter. Falling edge used to gate event generation.
      \arg        BOTH_EDGE_CLR_FEDGE_GATE: both rising and falling edges used to clear event window counter. falling edge used to gate event generation.
      \arg        BOTH_EDGE_GATE: neither edge used to clear event window counter. both rising and falling edges used to gate event generation.
      \arg        REDGE_CLR_BOTH_EDGE_GATE: rising edge used to clear event window counter. both rising and falling edges used to gate event generation.
      \arg        FEDGE_CLR_BOTH_EDGE_GATE: falling edge used to clear event window counter. both rising and falling edges used to gate event generation.
      \arg        BOTH_EDGE_CLR_GATE: both rising and falling edges used to clear event window counter. both rising and falling edges used to gate event generation.
    \param[out] none
    \retval     none
*/
void ioc_egm_event_window_triger_edge_select(ioc_egmx_enum egmx, uint32_t triger_edge)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_EGM_EVENT_WIN_TRIGER(triger_edge)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_EWAES;
        IOC_EGMCTL((uint32_t)egmx) |= triger_edge;
    }
}

/*!
    \brief      enable event window inverted (API_ID: 0x0020U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_event_window_invert_enable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) |= IOC_EGMXCTL_INVEWEN;
}

/*!
    \brief      disable event window inverted (API_ID: 0x0021U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_event_window_invert_disable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_INVEWEN;
}

/*!
    \brief      enable events generated (API_ID: 0x0022U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_event_generate_enable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_EVDIS;
}

/*!
    \brief      disable events generated (API_ID: 0x0023U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_event_generate_disable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) |= IOC_EGMXCTL_EVDIS;
}

/*!
    \brief      configure event window generation run mode (API_ID: 0x0024U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[in]  mode: run mode
                only one parameter can be selected which is shown as below:
      \arg        FREE_RUNNING_MODE: free running mode
      \arg        GATE_MODE: gate mode
    \param[out] none
    \retval     none
*/
void ioc_egm_event_generate_mode_config(ioc_egmx_enum egmx, uint32_t mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_EVENT_WIN_RUN_MODE(mode)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0024U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_EWGRM;
        IOC_EGMCTL((uint32_t)egmx) |= mode;
    }
}

/*!
    \brief      enable monitor signal from the FPM compared with reference signal (API_ID: 0x0025U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_monitor_signal_compare_enable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) |= IOC_EGMXCTL_MREN;
}

/*!
    \brief      disable monitor signal from the FPM compared with reference signal, monitor signal is from monitor[x] (API_ID: 0x0026U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_monitor_signal_compare_disable(ioc_egmx_enum egmx)
{
    IOC_EGMCTL((uint32_t)egmx) &= ~IOC_EGMXCTL_MREN;
}

/*!
    \brief      configure event count threshold (API_ID: 0x0027U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[in]  threshold: event count threshold, 0x00000000-0x00FFFFFF
    \param[out] none
    \retval     none
*/
void ioc_egm_event_window_threshold_config(ioc_egmx_enum egmx, uint32_t threshold)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_EGM_EVENT_WIN_VALUE(threshold)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0027U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_EGMCFG((uint32_t)egmx) &= ~IOC_EGMXCFG_EWCTH;
        IOC_EGMCFG((uint32_t)egmx) |= threshold;
    }
}

/*!
    \brief      get the value of EGM event window counter (API_ID: 0x0028U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     the value of EGM event window counter, 0x00000000-0x00FFFFFF
*/
uint32_t ioc_egm_event_window_counter_get(ioc_egmx_enum egmx)
{
    uint32_t reval;
    reval = IOC_EGMCNT((uint32_t)egmx);
    return reval;
}

/*!
    \brief      get the overflow flag (API_ID: 0x0029U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus ioc_egm_counter_overflow_flag_get(ioc_egmx_enum egmx)
{
    FlagStatus reval;

    if(0U != ((IOC_EGMCNT((uint32_t)egmx) & (IOC_EGMXCNT_CNTOVF)) >> 31U)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear the overflow flag (API_ID: 0x0030U)
    \param[in]  egmx: egmx, refer to ioc_egmx_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_EGM0
      \arg        IOC_EGM1
      \arg        IOC_EGM2
      \arg        IOC_EGM3
      \arg        IOC_EGM4
      \arg        IOC_EGM5
      \arg        IOC_EGM6
      \arg        IOC_EGM7
    \param[out] none
    \retval     none
*/
void ioc_egm_counter_overflow_flag_clear(ioc_egmx_enum egmx)
{
    IOC_EGMCNT((uint32_t)egmx) &= ~IOC_EGMXCNT_CNTOVF;
}

/*!
    \brief      select SEGM channel event(API_ID: 0x0031U)
    \param[in]  channel: SEGM channel, refer to ioc_segm_channel_enum
                only one parameter can be selected which is shown as below:
      \arg        SEGM_CHANNEL_0
      \arg        SEGM_CHANNEL_1
      \arg        SEGM_CHANNEL_2
      \arg        SEGM_CHANNEL_3
    \param[in]  event: SEGM channel event
                only one parameter can be selected which is shown as below:
      \arg        SEGM_EGM_EVENT0
      \arg        SEGM_EGM_EVENT1
      \arg        SEGM_EGM_EVENT2
      \arg        SEGM_EGM_EVENT3
      \arg        SEGM_EGM_EVENT4
      \arg        SEGM_EGM_EVENT5
      \arg        SEGM_EGM_EVENT6
      \arg        SEGM_EGM_EVENT7
    \param[out] none
    \retval     none
*/
void ioc_segm_input_seclect(ioc_segm_channel_enum channel, uint32_t event)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SEGM_EVENT(event)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0031U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(channel) {
        case SEGM_CHANNEL_0:
            IOC_SEGMCTL0 &= ~IOC_SEGMCTL0_CH0ES;
            IOC_SEGMCTL0 |= event;
            break;
        case SEGM_CHANNEL_1:
            IOC_SEGMCTL0 &= ~IOC_SEGMCTL0_CH1ES;
            IOC_SEGMCTL0 |= (event << 8U);
            break;
        case SEGM_CHANNEL_2:
            IOC_SEGMCTL0 &= ~IOC_SEGMCTL0_CH2ES;
            IOC_SEGMCTL0 |= (event << 16U);
            break;
        case SEGM_CHANNEL_3:
            IOC_SEGMCTL0 &= ~IOC_SEGMCTL0_CH3ES;
            IOC_SEGMCTL0 |= (event << 24U);
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      configure SEGM channel event counter threshold (API_ID: 0x0032U)
    \param[in]  channel: SEGM channel, refer to ioc_segm_channel_enum
                only one parameter can be selected which is shown as below:
      \arg        SEGM_CHANNEL_0
      \arg        SEGM_CHANNEL_1
      \arg        SEGM_CHANNEL_2
      \arg        SEGM_CHANNEL_3
    \param[in]  threshold: 0x00000000-0x0000000F
    \param[out] none
    \retval     none
*/
void ioc_segm_counter_threshold_config(ioc_segm_channel_enum channel, uint32_t threshold)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SEGM_EVENT_COUNTER_VALUE(threshold)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0032U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(channel) {
        case SEGM_CHANNEL_0:
            IOC_SEGMCTL0 &= ~IOC_SEGMCTL0_CH0THR;
            IOC_SEGMCTL0 |= (threshold << 4U);
            break;
        case SEGM_CHANNEL_1:
            IOC_SEGMCTL0 &= ~IOC_SEGMCTL0_CH1THR;
            IOC_SEGMCTL0 |= (threshold << 12U);
            break;
        case SEGM_CHANNEL_2:
            IOC_SEGMCTL0 &= ~IOC_SEGMCTL0_CH2THR;
            IOC_SEGMCTL0 |= (threshold << 20U);
            break;
        case SEGM_CHANNEL_3:
            IOC_SEGMCTL0 &= ~IOC_SEGMCTL0_CH3THR;
            IOC_SEGMCTL0 |= (threshold << 28U);
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      enable EGM_EVENTx selection(API_ID: 0x0033U)
    \param[in]  egm_event: enable EGM_EVENTx selection
                only one parameter can be selected which is shown as below:
      \arg        SEGM_EGM_EVENT0_ENABLE
      \arg        SEGM_EGM_EVENT1_ENABLE
      \arg        SEGM_EGM_EVENT2_ENABLE
      \arg        SEGM_EGM_EVENT3_ENABLE
      \arg        SEGM_EGM_EVENT4_ENABLE
      \arg        SEGM_EGM_EVENT5_ENABLE
      \arg        SEGM_EGM_EVENT6_ENABLE
      \arg        SEGM_EGM_EVENT7_ENABLE
    \param[out] none
    \retval     none
*/
void ioc_segm_egm_event_enable(uint32_t egm_event)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SEGM_EGM_EVENT_ENABLE(egm_event)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0033U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {

        IOC_SEGMCTL1 |= egm_event;

    }
}

/*!
    \brief      disable EGM_ETMx selection(API_ID: 0x0034U)
    \param[in]  egm_event: disable EGM_EVENTx selection
                only one parameter can be selected which is shown as below:
      \arg        SEGM_EGM_EVENT0_DISABLE
      \arg        SEGM_EGM_EVENT1_DISABLE
      \arg        SEGM_EGM_EVENT2_DISABLE
      \arg        SEGM_EGM_EVENT3_DISABLE
      \arg        SEGM_EGM_EVENT4_DISABLE
      \arg        SEGM_EGM_EVENT5_DISABLE
      \arg        SEGM_EGM_EVENT6_DISABLE
      \arg        SEGM_EGM_EVENT7_DISABLE
    \param[out] none
    \retval     none
*/
void ioc_segm_egm_event_disable(uint32_t egm_event)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SEGM_EGM_EVENT_DISABLE(egm_event)) {
        fw_debug_report_err(I2C_MODULE_ID, API_ID(0x0034U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IOC_SEGMCTL1 &= egm_event;
    }
}

/*!
    \brief      enable SEGM channel selection(API_ID: 0x0035U)
    \param[in]  channel: SEGM channel, refer to ioc_segm_channel_enum
                only one parameter can be selected which is shown as below:
      \arg        SEGM_CHANNEL_0
      \arg        SEGM_CHANNEL_1
      \arg        SEGM_CHANNEL_2
      \arg        SEGM_CHANNEL_3
    \param[out] none
    \retval     none
*/
void ioc_segm_channel_enable(ioc_segm_channel_enum channel)
{
    switch(channel) {
    case SEGM_CHANNEL_0:
        IOC_SEGMCTL1 |= IOC_SEGMCTL1_SEGM_CH0EN;
        break;
    case SEGM_CHANNEL_1:
        IOC_SEGMCTL1 |= IOC_SEGMCTL1_SEGM_CH1EN;
        break;
    case SEGM_CHANNEL_2:
        IOC_SEGMCTL1 |= IOC_SEGMCTL1_SEGM_CH2EN;
        break;
    case SEGM_CHANNEL_3:
        IOC_SEGMCTL1 |= IOC_SEGMCTL1_SEGM_CH3EN;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable SEGM channel selection(API_ID: 0x0036U)
    \param[in]  channel: SEGM channel, refer to ioc_segm_channel_enum
                only one parameter can be selected which is shown as below:
      \arg        SEGM_CHANNEL_0
      \arg        SEGM_CHANNEL_1
      \arg        SEGM_CHANNEL_2
      \arg        SEGM_CHANNEL_3
    \param[out] none
    \retval     none
*/
void ioc_segm_channel_disable(ioc_segm_channel_enum channel)
{
    switch(channel) {
    case SEGM_CHANNEL_0:
        IOC_SEGMCTL1 &= ~IOC_SEGMCTL1_SEGM_CH0EN;
        break;
    case SEGM_CHANNEL_1:
        IOC_SEGMCTL1 &= ~IOC_SEGMCTL1_SEGM_CH1EN;
        break;
    case SEGM_CHANNEL_2:
        IOC_SEGMCTL1 &= ~IOC_SEGMCTL1_SEGM_CH2EN;
        break;
    case SEGM_CHANNEL_3:
        IOC_SEGMCTL1 &= ~IOC_SEGMCTL1_SEGM_CH3EN;
        break;
    default:
        break;
    }
}

/*!
    \brief      get SEGM system event recore flag(API_ID: 0x0037U)
    \param[in]  flag: EGMx (x = 0...7) triggered system event flag, refer to ioc_segm_generate_event_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        EGM0_TRIG_SYSTEM_EVENT_FLAG0
      \arg        EGM1_TRIG_SYSTEM_EVENT_FLAG0
      \arg        EGM2_TRIG_SYSTEM_EVENT_FLAG0
      \arg        EGM3_TRIG_SYSTEM_EVENT_FLAG0
      \arg        EGM4_TRIG_SYSTEM_EVENT_FLAG0
      \arg        EGM5_TRIG_SYSTEM_EVENT_FLAG0
      \arg        EGM6_TRIG_SYSTEM_EVENT_FLAG0
      \arg        EGM7_TRIG_SYSTEM_EVENT_FLAG0
      \arg        EGM0_TRIG_SYSTEM_EVENT_FLAG1
      \arg        EGM1_TRIG_SYSTEM_EVENT_FLAG1
      \arg        EGM2_TRIG_SYSTEM_EVENT_FLAG1
      \arg        EGM3_TRIG_SYSTEM_EVENT_FLAG1
      \arg        EGM4_TRIG_SYSTEM_EVENT_FLAG1
      \arg        EGM5_TRIG_SYSTEM_EVENT_FLAG1
      \arg        EGM6_TRIG_SYSTEM_EVENT_FLAG1
      \arg        EGM7_TRIG_SYSTEM_EVENT_FLAG1
      \arg        EGM0_TRIG_SYSTEM_EVENT_FLAG2
      \arg        EGM1_TRIG_SYSTEM_EVENT_FLAG2
      \arg        EGM2_TRIG_SYSTEM_EVENT_FLAG2
      \arg        EGM3_TRIG_SYSTEM_EVENT_FLAG2
      \arg        EGM4_TRIG_SYSTEM_EVENT_FLAG2
      \arg        EGM5_TRIG_SYSTEM_EVENT_FLAG2
      \arg        EGM6_TRIG_SYSTEM_EVENT_FLAG2
      \arg        EGM7_TRIG_SYSTEM_EVENT_FLAG2
      \arg        EGM0_TRIG_SYSTEM_EVENT_FLAG3
      \arg        EGM1_TRIG_SYSTEM_EVENT_FLAG3
      \arg        EGM2_TRIG_SYSTEM_EVENT_FLAG3
      \arg        EGM3_TRIG_SYSTEM_EVENT_FLAG3
      \arg        EGM4_TRIG_SYSTEM_EVENT_FLAG3
      \arg        EGM5_TRIG_SYSTEM_EVENT_FLAG3
      \arg        EGM6_TRIG_SYSTEM_EVENT_FLAG3
      \arg        EGM7_TRIG_SYSTEM_EVENT_FLAG3
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus ioc_segm_history_trigge_flag_get(ioc_segm_generate_event_flag_enum flag)
{
    FlagStatus reval;

    if(0U != (IOC_REG_VAL(flag) & BIT(IOC_BIT_POS(flag)))) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      enable IOC TMR interrupt(API_ID: 0x0038U)
    \param[in]  tmr_interrupt: TMR interrupt, refer to ioc_tmr_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_INT_TMRERR_PSC
      \arg        IOC_INT_TMRERR_CLKEN
      \arg        IOC_INT_TMRERR_MCEN
    \param[out] none
    \retval     none
*/
void ioc_tmr_interrupt_enable(ioc_tmr_interrupt_enum tmr_interrupt)
{
    IOC_REG_VAL(tmr_interrupt) |= BIT(IOC_BIT_POS(tmr_interrupt));
}

/*!
    \brief      disable IOC TMR interrupt(API_ID: 0x0039U)
    \param[in]  tmr_interrupt: TMR interrupt, refer to ioc_tmr_interrupt_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_INT_TMRERR_PSC
      \arg        IOC_INT_TMRERR_CLKEN
      \arg        IOC_INT_TMRERR_MCEN
    \param[out] none
    \retval     none
*/
void ioc_tmr_interrupt_disable(ioc_tmr_interrupt_enum tmr_interrupt)
{

    IOC_REG_VAL(tmr_interrupt) &= ~BIT(IOC_BIT_POS(tmr_interrupt));
}

/*!
    \brief      get IOC TMR flag(API_ID: 0x003AU)
    \param[in]  tmr_flag: TMR flag, refer to ioc_tmr_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FLAG_TMRERR_PSC
      \arg        IOC_FLAG_TMRERR_CLKEN
      \arg        IOC_FLAG_TMRERR_MCEN
    \param[out] none
    \retval     none
*/
FlagStatus ioc_tmr_flag_get(ioc_tmr_flag_enum tmr_flag)
{
    FlagStatus reval;

    if(0U != (IOC_REG_VAL(tmr_flag) & BIT(IOC_BIT_POS(tmr_flag)))) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      clear IOC TMR flag(API_ID: 0x003BU)
    \param[in]  tmr_flag: TMR flag, refer to ioc_tmr_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_FLAG_TMRERR_PSC
      \arg        IOC_FLAG_TMRERR_CLKEN
      \arg        IOC_FLAG_TMRERR_MCEN
    \param[out] none
    \retval     none
*/
void ioc_tmr_flag_clear(ioc_tmr_flag_enum tmr_flag)
{
    IOC_REG_VAL(tmr_flag) |= BIT(IOC_BIT_POS(tmr_flag));
}

/*!
    \brief      get IOC TMR interrupt and flag status(API_ID: 0x003CU)
    \param[in]  tmr_int_flag: TMR flag, refer to ioc_tmr_interrupt_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        IOC_INT_FLAG_TMRERR_PSC
      \arg        IOC_INT_FLAG_TMRERR_CLKEN
      \arg        IOC_INT_FLAG_TMRERR_MCEN
    \param[out] none
    \retval     none
*/
FlagStatus ioc_tmr_interrupt_flag_get(ioc_tmr_interrupt_flag_enum tmr_int_flag)
{
    FlagStatus reval;
    uint32_t intenable, flagStatus;

    /* get the interrupt enable bit status */
    intenable = (IOC_REG_VAL(tmr_int_flag) & BIT(IOC_BIT_POS(tmr_int_flag)));
    /* get the corresponding flag bit status */
    flagStatus = (IOC_REG_VAL2(tmr_int_flag) & BIT(IOC_BIT_POS2(tmr_int_flag)));

    if((0U != flagStatus) && (0U != intenable)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      enable alarm interrupt(API_ID: 0x003DU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_alarm_interrupt_enable(void)
{
    IOC_INTSTAT |= IOC_INTSTAT_ALRMIE;
}

/*!
    \brief      disable alarm interrupt(API_ID: 0x003EU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_alarm_interrupt_disable(void)
{
    IOC_INTSTAT &= ~IOC_INTSTAT_ALRMIE;
}

/*!
    \brief      get SEGM event trigger flag(API_ID: 0x003FU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
FlagStatus ioc_segm_systerm_event_trigge_flag_get(void)
{
    FlagStatus reval;
    if(0U != (IOC_INTSTAT & IOC_INTSTAT_ALRMIF)) {
        reval = SET;
    } else {
        reval = RESET;
    }
    return reval;
}

/*!
    \brief      clear SEGM event trigger flag(API_ID: 0x0040U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ioc_segm_systerm_event_trigge_flag_clear(void)
{
    IOC_INTSTAT |= IOC_INTSTAT_ALRMIF;
}
