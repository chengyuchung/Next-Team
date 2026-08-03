/*!
    \file    gd32a7xx_rtc.c
    \brief   RTC driver

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

#include "gd32a7xx_rtc.h"

/*!
    \brief      enter RTC configuration mode (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_configuration_mode_enter(void)
{
    RTC_CTL |= RTC_CTL_CMF;
}

/*!
    \brief      exit RTC configuration mode (API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_configuration_mode_exit(void)
{
    RTC_CTL &= ~RTC_CTL_CMF;
}

/*!
    \brief      wait RTC last write operation finished flag set (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus rtc_lwoff_wait(void)
{
    uint32_t timeout = RTC_LWOFF_TIMEOUT;
    ErrStatus status = SUCCESS;

    /* loop until LWOFF flag is set */
    while(((uint32_t)RESET == (RTC_CTL & RTC_CTL_LWOFF)) && (timeout != (uint32_t)0)) {
        timeout--;
    }
    if(((uint32_t)RESET == (RTC_CTL & RTC_CTL_LWOFF))) {
        status = ERROR;
    } else {
        /* do nothing */
    }
    return status;
}

/*!
    \brief      wait RTC registers synchronized flag set (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     ERROR or SUCCESS
*/
ErrStatus rtc_register_sync_wait(void)
{
    uint32_t timeout = RTC_REG_SYNC_TIMEOUT;
    ErrStatus status = SUCCESS;

    /* clear RSYNF flag */
    RTC_CTL &= ~RTC_CTL_RSYNF;
    /* loop until RSYNF flag is set */
    while(((uint32_t)RESET == (RTC_CTL & RTC_CTL_RSYNF)) && (timeout != (uint32_t)0)) {
        timeout--;
    }
    if(((uint32_t)RESET == (RTC_CTL & RTC_CTL_RSYNF))) {
        status = ERROR;
    } else {
        /* do nothing */
    }
    return status;
}

/*!
    \brief      get RTC counter value (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     RTC counter value
*/
uint32_t rtc_counter_get(void)
{
    uint32_t temp;
    temp = RTC_CNTL;
    temp |= (RTC_CNTH << 16);
    return temp;
}

/*!
    \brief      set RTC counter value (API_ID(0x0006U))
    \param[in]  cnt: RTC counter value
    \param[out] none
    \retval     none
*/
void rtc_counter_set(uint32_t cnt)
{
    /* enter RTC configuration mode */
    RTC_CTL |= RTC_CTL_CMF;
    /* set the RTC counter high bits */
    RTC_CNTH = cnt >> 16;
    /* set the RTC counter low bits */
    RTC_CNTL = (cnt & RTC_LOW_VALUE);
    /* exit RTC configuration mode */
    RTC_CTL &= ~RTC_CTL_CMF;
}

/*!
    \brief      set RTC prescaler value (API_ID(0x0007U))
    \param[in]  psc: RTC prescaler value, it can be 0x00001~0xFFFFF
    \param[out] none
    \retval     none
*/
void rtc_prescaler_set(uint32_t psc)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RTC_PSC(psc)) {
        fw_debug_report_err(RTC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        /* enter RTC configuration mode */
        RTC_CTL |= RTC_CTL_CMF;
        /* set the RTC prescaler high bits */
        RTC_PSCH = (psc & RTC_HIGH_VALUE) >> 16;
        /* set the RTC prescaler low bits */
        RTC_PSCL = (psc & RTC_LOW_VALUE);
        /* exit RTC configuration mode */
        RTC_CTL &= ~RTC_CTL_CMF;
    }
}

/*!
    \brief      set RTC alarm value (API_ID(0x0008U))
    \param[in]  alarm: RTC alarm value
    \param[out] none
    \retval     none
*/
void rtc_alarm_config(uint32_t alarm)
{
    /* enter RTC configuration mode */
    RTC_CTL |= RTC_CTL_CMF;
    /* set the alarm high bits */
    RTC_ALRMH = alarm >> 16;
    /* set the alarm low bits */
    RTC_ALRML = (alarm & RTC_LOW_VALUE);
    /* exit RTC configuration mode */
    RTC_CTL &= ~RTC_CTL_CMF;
}

/*!
    \brief      get RTC divider value (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     RTC divider value
*/
uint32_t rtc_divider_get(void)
{
    uint32_t temp;
    temp = (RTC_DIVH & RTC_DIVH_DIV) << 16;
    temp |= RTC_DIVL;
    return temp;
}

/*!
    \brief      enable RTC interrupt (API_ID(0x000AU))
    \param[in]  interrupt: specify which interrupt to enbale
                only one parameter can be selected which is shown as below:
          \arg    RTC_INT_SECOND: second interrupt
          \arg    RTC_INT_ALARM: alarm interrupt
          \arg    RTC_INT_OVERFLOW: overflow interrupt
    \param[out] none
    \retval     none
*/
void rtc_interrupt_enable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RTC_INT(interrupt)) {
        fw_debug_report_err(RTC_MODULE_ID, API_ID(0x000AU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        RTC_INTEN |= interrupt;
    }
}

/*!
    \brief      disable RTC interrupt (API_ID(0x000BU))
    \param[in]  interrupt: specify which interrupt to disbale
                only one parameter can be selected which is shown as below:
          \arg    RTC_INT_SECOND: second interrupt
          \arg    RTC_INT_ALARM: alarm interrupt
          \arg    RTC_INT_OVERFLOW: overflow interrupt
    \param[out] none
    \retval     none
*/
void rtc_interrupt_disable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RTC_INT(interrupt)) {
        fw_debug_report_err(RTC_MODULE_ID, API_ID(0x000BU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        RTC_INTEN &= ~interrupt;
    }
}

/*!
    \brief      get RTC flag status (API_ID(0x000CU))
    \param[in]  flag: specify which flag status to get
                only one parameter can be selected which is shown as below:
          \arg    RTC_FLAG_SECOND: second interrupt flag
          \arg    RTC_FLAG_ALARM: alarm interrupt flag
          \arg    RTC_FLAG_OVERFLOW: overflow interrupt flag
          \arg    RTC_FLAG_RSYN: registers synchronized flag
          \arg    RTC_FLAG_LWOF: last write operation finished flag
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus rtc_flag_get(uint32_t flag)
{
    FlagStatus revel = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RTC_FLAG(flag)) {
        fw_debug_report_err(RTC_MODULE_ID, API_ID(0x000CU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        if(0U != (RTC_CTL & flag)) {
            revel = SET;
        } else {
            /* do nothing */
        }
    }
    return revel;
}

/*!
    \brief      clear RTC flag status (API_ID(0x000DU))
    \param[in]  flag: specify which flag status to clear
                only one parameter can be selected which is shown as below:
          \arg    RTC_FLAG_SECOND: second interrupt flag
          \arg    RTC_FLAG_ALARM: alarm interrupt flag
          \arg    RTC_FLAG_OVERFLOW: overflow interrupt flag
          \arg    RTC_FLAG_RSYN: registers synchronized flag
    \param[out] none
    \retval     none
*/
void rtc_flag_clear(uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RTC_CLEAR_FLAG(flag)) {
        fw_debug_report_err(RTC_MODULE_ID, API_ID(0x000DU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        /* clear RTC flag */
        RTC_CTL &= ~flag;
    }
}

/*!
    \brief      get RTC interrupt flag status (API_ID(0x000EU))
    \param[in]  flag: specify which flag status to get
                only one parameter can be selected which is shown as below:
      \arg        RTC_INT_FLAG_SECOND: second interrupt flag
      \arg        RTC_INT_FLAG_ALARM: alarm interrupt flag
      \arg        RTC_INT_FLAG_OVERFLOW: overflow interrupt flag
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus rtc_interrupt_flag_get(uint32_t flag)
{
    FlagStatus revel = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RTC_INT_FLAG(flag)) {
        fw_debug_report_err(RTC_MODULE_ID, API_ID(0x000EU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        if(0U != (RTC_CTL & flag)) {
            revel = SET;
        } else {
            /* do nothing */
        }
    }
    return revel;
}

/*!
    \brief      clear RTC interrupt flag status (API_ID(0x000FU))
    \param[in]  flag: specify which flag status to clear
                only one parameter can be selected which is shown as below:
      \arg        RTC_INT_FLAG_SECOND: second interrupt flag
      \arg        RTC_INT_FLAG_ALARM: alarm interrupt flag
      \arg        RTC_INT_FLAG_OVERFLOW: overflow interrupt flag
    \param[out] none
    \retval     none
*/
void rtc_interrupt_flag_clear(uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RTC_INT_FLAG(flag)) {
        fw_debug_report_err(RTC_MODULE_ID, API_ID(0x000FU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        /* clear RTC interrupt flag */
        RTC_CTL &= ~flag;
    }
}
