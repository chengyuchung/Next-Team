/*!
    \file    gd32a7xx_fwdgt.c
    \brief   FWDGT driver

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

#include "gd32a7xx_fwdgt.h"

/*!
    \brief      reset the free watchdog timer configuration (API_ID(0x0001U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[out] none
    \retval     none
*/
void fwdgt_deinit(uint32_t fwdgtx_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else
#endif
    {
        /* reset FWDGT register */
        FWDGT_CTL(fwdgtx_periph) = FWDGT_WRITEACCESS_ENABLE;
        FWDGT_PSC(fwdgtx_periph) = 0x00000000U;
        FWDGT_RLD(fwdgtx_periph) = 0x00001FFFU;
        FWDGT_WND(fwdgtx_periph) = 0x000FFFFFU;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        if(FWDGT0 == fwdgtx_periph) {
            /* reset FWDGT0 */
            rcu_periph_reset_enable(RCU_FWDGT0RST);
            rcu_periph_reset_disable(RCU_FWDGT0RST);
        } else {
            /* reset FWDGT1 */
            rcu_periph_reset_enable(RCU_FWDGT1RST);
            rcu_periph_reset_disable(RCU_FWDGT1RST);
        }
#else
        /* reset FWDGT0 */
        rcu_periph_reset_enable(RCU_FWDGT0RST);
        rcu_periph_reset_disable(RCU_FWDGT0RST);
#endif

    }
}

/*!
    \brief      enable write access to FWDGT_PSC, FWDGT_RLD and FWDGT_WND (API_ID(0x0002U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[out] none
    \retval     none
*/

void fwdgt_write_protection_disable(uint32_t fwdgtx_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0002U), ERR_PERIPH);
    } else
#endif
    {
        FWDGT_CTL(fwdgtx_periph) = FWDGT_WRITEACCESS_ENABLE;
    }
}

/*!
    \brief      disable write access to FWDGT_PSC, FWDGT_RLD and FWDGT_WND (API_ID(0x0003U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[out] none
    \retval     none
*/
void fwdgt_write_protection_enable(uint32_t fwdgtx_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else
#endif
    {
        FWDGT_CTL(fwdgtx_periph) = FWDGT_WRITEACCESS_DISABLE;
    }
}
/*!
    \brief      start the FWDGT counter (API_ID(0x0004U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[out] none
    \retval     none
*/
void fwdgt_enable(uint32_t fwdgtx_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else
#endif
    {
        FWDGT_CTL(fwdgtx_periph) = FWDGT_KEY_ENABLE;
    }
}

/*!
    \brief      configure the FWDGT counter prescaler value (API_ID(0x0005U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[in]  prescaler_value: specify prescaler value
                only one parameter can be selected which is shown as below:
      \arg        FWDGT_PSC_DIV4: FWDGT prescaler set to 4
      \arg        FWDGT_PSC_DIV8: FWDGT prescaler set to 8
      \arg        FWDGT_PSC_DIV16: FWDGT prescaler set to 16
      \arg        FWDGT_PSC_DIV32: FWDGT prescaler set to 32
      \arg        FWDGT_PSC_DIV64: FWDGT prescaler set to 64
      \arg        FWDGT_PSC_DIV128: FWDGT prescaler set to 128
      \arg        FWDGT_PSC_DIV256: FWDGT prescaler set to 256
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus fwdgt_prescaler_value_config(uint32_t fwdgtx_periph, uint16_t prescaler_value)
{
    uint32_t timeout = FWDGT_PSC_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else if(NOT_FWDGT_PSC_VALUE(prescaler_value)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* enable write access to FWDGT_PSC */
        FWDGT_CTL(fwdgtx_periph) = FWDGT_WRITEACCESS_ENABLE;

        /* wait until the PUD flag to be reset */
        do {
            flag_status = FWDGT_STAT(fwdgtx_periph) & FWDGT_STAT_PUD;
        } while((--timeout > (uint32_t)0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        /* configure FWDGT */
        FWDGT_PSC(fwdgtx_periph) = (uint32_t)prescaler_value;
    }
    return status;
}

/*!
    \brief      configure the FWDGT counter reload value (API_ID(0x0006U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[in]  reload_value: specify reload value(0x0000 - 0xFFFFF)
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus fwdgt_reload_value_config(uint32_t fwdgtx_periph, uint32_t reload_value)
{
    uint32_t timeout = FWDGT_RLD_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else if(NOT_FWDGT_RELOAD(reload_value)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0006U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        /* enable write access to FWDGT_RLD */
        FWDGT_CTL(fwdgtx_periph) = FWDGT_WRITEACCESS_ENABLE;

        /* wait until the RUD flag to be reset */
        do {
            flag_status = FWDGT_STAT(fwdgtx_periph) & FWDGT_STAT_RUD;
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status =  ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        FWDGT_RLD(fwdgtx_periph) = RLD_RLD(reload_value);
    }
    return status;

}

/*!
    \brief      configure the FWDGT counter window value (API_ID(0x0007U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[in]  window_value: specify window value(0x0000 - 0xFFFFF)
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus fwdgt_window_value_config(uint32_t fwdgtx_periph, uint32_t window_value)
{
    uint32_t time_index = FWDGT_WND_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else if(NOT_FWDGT_WINDOW(window_value)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0007U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        /* enable write access to FWDGT_WND */
        FWDGT_CTL(fwdgtx_periph) = FWDGT_WRITEACCESS_ENABLE;

        /* wait until the WUD flag to be reset */
        do {
            flag_status = FWDGT_STAT(fwdgtx_periph) & FWDGT_STAT_WUD;
        } while((--time_index > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        FWDGT_WND(fwdgtx_periph) = WND_WND(window_value);
    }
    return status;
}

/*!
    \brief      reload the counter of FWDGT (API_ID(0x0008U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus fwdgt_counter_reload(uint32_t fwdgtx_periph)
{
    uint32_t timeout = FWDGT_RLD_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else
#endif
    {
        /* wait until the RLD_BSY flag to be reset */
        do {
            flag_status = FWDGT_STAT(fwdgtx_periph) & FWDGT_STAT_RLD_BSY;
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        FWDGT_CTL(fwdgtx_periph) = FWDGT_KEY_RELOAD;
    }
    return status;
}

/*!
    \brief      configure counter reload value, and prescaler divider value (API_ID(0x0009U))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[in]  reload_value: specify reload value(0x0000 - 0xFFFFF)
    \param[in]  prescaler_div: FWDGT prescaler value
                only one parameter can be selected which is shown as below:
      \arg        FWDGT_PSC_DIV4: FWDGT prescaler set to 4
      \arg        FWDGT_PSC_DIV8: FWDGT prescaler set to 8
      \arg        FWDGT_PSC_DIV16: FWDGT prescaler set to 16
      \arg        FWDGT_PSC_DIV32: FWDGT prescaler set to 32
      \arg        FWDGT_PSC_DIV64: FWDGT prescaler set to 64
      \arg        FWDGT_PSC_DIV128: FWDGT prescaler set to 128
      \arg        FWDGT_PSC_DIV256: FWDGT prescaler set to 256
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
                NOTE: Each reload time must be at an interval of at least 200 microseconds 
*/
ErrStatus fwdgt_config(uint32_t fwdgtx_periph, uint32_t reload_value, uint16_t prescaler_value)
{
    uint32_t timeout = FWDGT_PSC_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else if(NOT_FWDGT_RELOAD(reload_value)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0009U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_FWDGT_PSC_VALUE(prescaler_value)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* enable write access to FWDGT_PSC,and FWDGT_RLD */
        FWDGT_CTL(fwdgtx_periph) = FWDGT_WRITEACCESS_ENABLE;

        /* wait until the PUD flag to be reset */
        do {
            flag_status = FWDGT_STAT(fwdgtx_periph) & FWDGT_STAT_PUD;
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }

        /* configure FWDGT */
        FWDGT_PSC(fwdgtx_periph) = (uint32_t)prescaler_value;

        timeout = FWDGT_RLD_TIMEOUT;
        /* wait until the RUD flag to be reset */
        do {
            flag_status = FWDGT_STAT(fwdgtx_periph) & FWDGT_STAT_RUD;
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        /* NOTE: Each reload time must be at an interval of at least 200 microseconds */
        FWDGT_RLD(fwdgtx_periph) = RLD_RLD(reload_value);

        timeout = FWDGT_RLD_TIMEOUT;
        /* wait until the RLD_BSY flag to be reset */
        do {
            flag_status = FWDGT_STAT(fwdgtx_periph) & FWDGT_STAT_RLD_BSY;
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        /* reload the counter */
        FWDGT_CTL(fwdgtx_periph) = FWDGT_KEY_RELOAD;
    }
    return status;
}

/*!
    \brief      get flag state of FWDGT (API_ID(0x000AU))
    \param[in]  fwdgtx_periph: FWDGTx(x=0,1)
    \param[in]  flag: flag to get
                only one parameter can be selected which is shown as below:
      \arg        FWDGT_FLAG_PUD: a write operation to FWDGT_PSC register is on going
      \arg        FWDGT_FLAG_RUD: a write operation to FWDGT_RLD register is on going
      \arg        FWDGT_FLAG_WUD: a write operation to FWDGT_WND register is on going
      \arg        FWDGT_STAT_RLD_BSY:  FWDGT counter-reload is on going
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fwdgt_flag_get(uint32_t fwdgtx_periph, uint32_t flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FWDGT_PERIPH(fwdgtx_periph)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else if(NOT_FWDGT_FLAG(flag)) {
        fw_debug_report_err(FWDGT_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(0U != (FWDGT_STAT(fwdgtx_periph) & flag)) {
            reval = SET;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
    }
    return reval;
}
