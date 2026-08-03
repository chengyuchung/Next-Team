/*!
    \file    gd32a7xx_prpu.c
    \brief   PRPU driver

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

#include "gd32a7xx_prpu.h"

/*!
    \brief      lock peripheral registers (API_ID: 0x0001U)
    \param[in]  periph: protected peripheral
               only one parameter can be selected which is shown as below:
    \arg            0x00 - 0x68: Peripheral index
    \param[out] none
    \retval     none
*/
void prpu_periph_lock(uint32_t periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_PRPU_PROTECTED_PERIPH(periph)) {
        fw_debug_report_err(PRPU_MODULE_ID, API_ID(0x0001U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        PRPU_LKPROT(periph) = PRPU_LOCK_KEY;
    }
}

/*!
    \brief      unlock peripheral registers (API_ID: 0x0002U)
    \param[in]  periph: protected peripheral
               only one parameter can be selected which is shown as below:
    \arg            0x00 - 0x68: Peripheral index
    \param[out] none
    \retval     none
*/
void prpu_periph_unlock(uint32_t periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_PRPU_PROTECTED_PERIPH(periph)) {
        fw_debug_report_err(PRPU_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        PRPU_LKPROT(periph) = PRPU_UNLOCK_KEY + periph;
    }
}

/*!
    \brief      get Peripheral registers lock state (API_ID: 0x0003U)
    \param[in]  periph: protected peripheral
               only one parameter can be selected which is shown as below:
    \arg            0x00 - 0x68: Peripheral index
    \param[out] none
    \retval     FlagStatus:SET-unlock or RESET-lock
*/
FlagStatus prpu_periph_state_get(uint32_t periph)
{
    FlagStatus retval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_PRPU_PROTECTED_PERIPH(periph)) {
        fw_debug_report_err(PRPU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (PRPU_LKPROT(periph))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}
