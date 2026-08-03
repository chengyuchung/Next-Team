/*!
    \file    gd32a7xx_wwdgt.c
    \brief   WWDGT driver

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

#include "gd32a7xx_wwdgt.h"

/*!
    \brief      reset the window watchdog timer configuration (API_ID(0x0001U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus wwdgt_deinit(uint32_t wwdgt_periph)
{
    uint32_t timeout = WWDGT_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else
#endif
    {
        /* wait until the CNT_NREF flag to be reset */
        do {
            flag_status = (WWDGT_STAT(wwdgt_periph) & WWDGT_STAT_CNT_NREF);
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }

        /* reset WWDGT register */
        WWDGT_CTL(wwdgt_periph) = 0x0000007FU;
        WWDGT_CFG(wwdgt_periph) = 0x0000007FU;
        WWDGT_ALMSTATM(wwdgt_periph) = 0x00000003U;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        if(WWDGT0 == wwdgt_periph) {
            /* reset WWDGT0 */
            rcu_periph_reset_enable(RCU_WWDGT0RST);
            rcu_periph_reset_disable(RCU_WWDGT0RST);
        } else {
            /* reset WWDGT1 */
            rcu_periph_reset_enable(RCU_WWDGT1RST);
            rcu_periph_reset_disable(RCU_WWDGT1RST);
        }
#else
        /* reset WWDGT0 */
        rcu_periph_reset_enable(RCU_WWDGT0RST);
        rcu_periph_reset_disable(RCU_WWDGT0RST);
#endif
    }
    return status;
}

/*!
    \brief      start the WWDGT counter (API_ID(0x0002U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus wwdgt_enable(uint32_t wwdgt_periph)
{
    uint32_t timeout = WWDGT_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0002U), ERR_PERIPH);
    } else
#endif
    {
        /* wait until the CNT_NREF flag to be reset */
        do {
            flag_status = (WWDGT_STAT(wwdgt_periph) & WWDGT_STAT_CNT_NREF);
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        WWDGT_CTL(wwdgt_periph) |= WWDGT_CTL_WDGTEN;
    }
    return status;
}

/*!
    \brief      configure the WWDGT counter value (API_ID(0x0003U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[in]  counter_value: 0x40 - 0x7F
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus wwdgt_counter_update(uint32_t wwdgt_periph, uint16_t counter_value)
{
    uint32_t timeout = WWDGT_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_WWDGT_COUNTER(counter_value)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        /* wait until the CNT_NREF flag to be reset */
        do {
            flag_status = (WWDGT_STAT(wwdgt_periph) & WWDGT_STAT_CNT_NREF);
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        WWDGT_CTL(wwdgt_periph) = (uint32_t)(CTL_CNT(counter_value));
    }
    return status;
}

/*!
    \brief      configure counter value, window value, and prescaler divider value (API_ID(0x0004U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[in]  counter: 0x40 - 0x7F
    \param[in]  window: 0x40 - 0x7F
    \param[in]  prescaler: WWDGT prescaler value
                only one parameter can be selected which is shown as below:
      /arg      WWDGT_CFG_PSC_DIV1 : the time base of WWDGT = (WWDGT_CLK/4096)/1
      /arg      WWDGT_CFG_PSC_DIV2 : the time base of WWDGT = (WWDGT_CLK/4096)/2
      /arg      WWDGT_CFG_PSC_DIV4 : the time base of WWDGT = (WWDGT_CLK/4096)/4
      /arg      WWDGT_CFG_PSC_DIV8: the time base of WWDGT = (WWDGT_CLK/4096)/8
      /arg      WWDGT_CFG_PSC_DIV16  : the time base of WWDGT = (WWDGT_CLK/4096)/16
      /arg      WWDGT_CFG_PSC_DIV32  : the time base of WWDGT = (WWDGT_CLK/4096)/32
      /arg      WWDGT_CFG_PSC_DIV64  : the time base of WWDGT = (WWDGT_CLK/4096)/64
      /arg      WWDGT_CFG_PSC_DIV128 : the time base of WWDGT = (WWDGT_CLK/4096)/128
      /arg      WWDGT_CFG_PSC_DIV256 : the time base of WWDGT = (WWDGT_CLK/4096)/256
      /arg      WWDGT_CFG_PSC_DIV512 : the time base of WWDGT = (WWDGT_CLK/4096)/512
      /arg      WWDGT_CFG_PSC_DIV1024  : the time base of WWDGT = (WWDGT_CLK/4096)/1024
      /arg      WWDGT_CFG_PSC_DIV2048  : the time base of WWDGT = (WWDGT_CLK/4096)/2048
      /arg      WWDGT_CFG_PSC_DIV4096  : the time base of WWDGT = (WWDGT_CLK/4096)/4096
      /arg      WWDGT_CFG_PSC_DIV8192  : the time base of WWDGT = (WWDGT_CLK/4096)/8192
      /arg      WWDGT_CFG_PSC_DIV16384 : the time base of WWDGT = (WWDGT_CLK/4096)/16384
      /arg      WWDGT_CFG_PSC_DIV32768 : the time base of WWDGT = (WWDGT_CLK/4096)/32768
      /arg      WWDGT_CFG_PSC_DIV65536 : the time base of WWDGT = (WWDGT_CLK/4096)/65536
      /arg      WWDGT_CFG_PSC_DIV131072 : the time base of WWDGT = (WWDGT_CLK/4096)/131072
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus wwdgt_config(uint32_t wwdgt_periph, uint16_t counter, uint16_t window, uint32_t prescaler)
{
    uint32_t timeout = WWDGT_TIMEOUT;
    uint32_t flag_status;
    ErrStatus status = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else if(NOT_WWDGT_COUNTER(counter)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0004U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_WWDGT_WINDOW(window)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0004U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_WWDGT_PSC_VALUE(prescaler)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* wait until the CNT_NREF flag to be reset */
        do {
            flag_status = (WWDGT_STAT(wwdgt_periph) & WWDGT_STAT_CNT_NREF);
        } while((--timeout > 0U) && (0U != flag_status));

        if(0U != flag_status) {
            status = ERROR;
        }
        else{
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        WWDGT_CTL(wwdgt_periph) = (uint32_t)(CTL_CNT(counter));
        WWDGT_CFG(wwdgt_periph) = (uint32_t)(CFG_WIN(window) | prescaler);
    }
    return status;
}

/*!
    \brief      check early wakeup interrupt state of WWDGT (API_ID(0x0005U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[in]  flag
                only one parameter can be selected which is shown as below:
      \arg        WWDGT_STAT_EWIF: WWDGT early wakeup interrupt flag
      \arg        WWDGT_STAT_CNT_NREF: WWDGT count cannot updata flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus wwdgt_flag_get(uint32_t wwdgt_periph, uint32_t flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else if(NOT_WWDGT_STAT_FLAG(flag)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(flag == WWDGT_STAT_EWIF) {
            if(0U != (WWDGT_STAT(wwdgt_periph) & WWDGT_STAT_EWIF)) {
                reval = SET;
            } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }
        } else {
            if(0U != (WWDGT_STAT(wwdgt_periph) & WWDGT_STAT_CNT_NREF)) {
                reval = SET;
            } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }
        }
    }
    return reval;

}

/*!
    \brief      clear early wakeup interrupt state of WWDGT (API_ID(0x0006U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[out] none
    \retval     none
*/
void wwdgt_flag_clear(uint32_t wwdgt_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else
#endif
    {
        WWDGT_STAT(wwdgt_periph) &= ~(uint32_t)WWDGT_STAT_EWIF;
    }
}

/*!
    \brief      enable early wakeup interrupt of WWDGT (API_ID(0x0007U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[out] none
    \retval     none
*/
void wwdgt_interrupt_enable(uint32_t wwdgt_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else
#endif
    {
        WWDGT_CFG(wwdgt_periph) |= WWDGT_CFG_EWIE;
    }
}

/*!
    \brief      check early wakeup interrupt cannot be generated normally error flag or WWDGT cannot be activated error flag (API_ID(0x0008U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[in]  err_flag
                only one parameter can be selected which is shown as below:
      \arg        WWDGT_ALMSTAT_NAERR: WWDGT cannot be activated error flag
      \arg        WWDGT_ALMSTAT_EWIERR: Early wakeup interrupt cannot be generated normally error flag
    \param[out] none
    \retval     error flag:SET/RESET
*/
FlagStatus wwdgt_error_flag_get(uint32_t wwdgt_periph, uint32_t err_flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else if(NOT_WWDGT_ERR_FLAG(err_flag)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(err_flag == WWDGT_ALMSTAT_EWIERR) {
            if(0U != (WWDGT_ALMSTAT(wwdgt_periph) & WWDGT_ALMSTAT_EWIERR)) {
                reval = SET;
            } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }
        } else {
            if(0U != (WWDGT_ALMSTAT(wwdgt_periph) & WWDGT_ALMSTAT_NAERR)) {
                reval = SET;
            } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear early wakeup interrupt cannot be generated normally error flag or WWDGT cannot be activated error flag (API_ID(0x0009U))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[in]  err_flag
                only one parameter can be selected which is shown as below:
      \arg        WWDGT_ALMSTAT_NAERR: WWDGT cannot be activated error flag
      \arg        WWDGT_ALMSTAT_EWIERR: Early wakeup interrupt cannot be generated normally error flag
    \param[out] none
    \retval     none
*/
void wwdgt_error_flag_clear(uint32_t wwdgt_periph, uint32_t err_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else if(NOT_WWDGT_ERR_FLAG(err_flag)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(err_flag == WWDGT_ALMSTAT_EWIERR) {
            WWDGT_ALMSTAT(wwdgt_periph) |= WWDGT_ALMSTAT_EWIERR;
        } else {
            WWDGT_ALMSTAT(wwdgt_periph) |= WWDGT_ALMSTAT_NAERR;
        }
    }
}

/*!
    \brief      mask early wakeup interrupt cannot be generated normally error flag or WWDGT cannot be activated error flag (API_ID(0x000AU))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[in]  err_flag
                only one parameter can be selected which is shown as below:
      \arg        WWDGT_ALMSTAT_NAERR: WWDGT cannot be activated error flag
      \arg        WWDGT_ALMSTAT_EWIERR: Early wakeup interrupt cannot be generated normally error flag
    \param[out] none
    \retval     none
*/
void wwdgt_flag_mask(uint32_t wwdgt_periph, uint32_t err_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else if(NOT_WWDGT_ERR_FLAG(err_flag)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(err_flag == WWDGT_ALMSTAT_EWIERR) {
            WWDGT_ALMSTATM(wwdgt_periph) |= WWDGT_ALMSTAT_EWIEM;
        } else {
            WWDGT_ALMSTATM(wwdgt_periph) |= WWDGT_ALMSTAT_NAEM;
        }
    }
}

/*!
    \brief      unmask early wakeup interrupt cannot be generated normally error flag or WWDGT cannot be activated error flag (API_ID(0x000BU))
    \param[in]  wwdgt_periph: WWDGTx, x=0,1
    \param[in]  err_flag
                only one parameter can be selected which is shown as below:
      \arg        WWDGT_ALMSTAT_NAERR: WWDGT cannot be activated error flag
      \arg        WWDGT_ALMSTAT_EWIERR: Early wakeup interrupt cannot be generated normally error flag
    \param[out] none
    \retval     none
*/
void wwdgt_flag_unmask(uint32_t wwdgt_periph, uint32_t err_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else if(NOT_WWDGT_ERR_FLAG(err_flag)) {
        fw_debug_report_err(WWDGT_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(err_flag == WWDGT_ALMSTAT_EWIERR) {
            WWDGT_ALMSTATM(wwdgt_periph) &= (~WWDGT_ALMSTAT_EWIEM);
        } else {
            WWDGT_ALMSTATM(wwdgt_periph) &= (~WWDGT_ALMSTAT_NAEM);
        }
    }
}

