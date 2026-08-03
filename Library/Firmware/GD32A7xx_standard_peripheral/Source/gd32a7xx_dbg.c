/*!
    \file    gd32a7xx_dbg.c
    \brief   DBG driver

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

#include "gd32a7xx_dbg.h"

#define DBG_RESET_VAL           ((uint32_t)0x00000000U)   /*!< DBG reset value */

/*!
    \brief      deinitialize the DBG (API_ID: 0x0001U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dbg_deinit(void)
{
    DBG_CTL0 = DBG_RESET_VAL;
    DBG_CTL1 = DBG_RESET_VAL;
    DBG_CTL2 = DBG_RESET_VAL;
}

/*!
    \brief      enable low power behavior when the mcu is in debug mode (API_ID: 0x0002U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dbg_low_power_enable(void)
{
    DBG_CTL0 |= DBG_LOW_POWER_STANDBY;
}

/*!
    \brief      disable low power behavior when the mcu is in debug mode (API_ID: 0x0003U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void dbg_low_power_disable(void)
{
    DBG_CTL0 &= ~DBG_LOW_POWER_STANDBY;
}

/*!
    \brief      enable peripheral behavior when the mcu is in debug mode (API_ID: 0x0004U)
    \param[in]  dbg_periph: refer to dbg_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        DBG_TIMERx_HOLD (x=0,1,2,5,6,7,19,20,60,61,62,63): hold TIMERx counter when core is halted
      \arg        DBG_I2Cx_HOLD (x=0,1): hold I2Cx smbus timeout when core is halted
      \arg        DBG_WWDGTx_HOLD (x=0,1): hold WWDGT counter when core is halted
      \arg        DBG_MFCOM_HOLD : hold MFCOM counter when core is halted
      \arg        DBG_FWDGTx_HOLD (x=0,1): hold FWDGT counter when core is halted
    \param[out] none
    \retval     none
*/
void dbg_periph_enable(dbg_periph_enum dbg_periph)
{
    DBG_REG_VAL(dbg_periph) |= BIT(DBG_BIT_POS(dbg_periph));
}

/*!
    \brief      disable peripheral behavior when the mcu is in debug mode (API_ID: 0x0005U)
    \param[in]  dbg_periph: refer to dbg_periph_enum
                only one parameter can be selected which is shown as below:
      \arg        DBG_TIMERx_HOLD (x=0,1,2,5,6,7,19,20,60,61,62,63): hold TIMERx counter when core is halted
      \arg        DBG_I2Cx_HOLD (x=0,1): hold I2Cx smbus timeout when core is halted
      \arg        DBG_WWDGTx_HOLD (x=0,1): hold WWDGT counter when core is halted
      \arg        DBG_MFCOM_HOLD : hold MFCOM counter when core is halted
      \arg        DBG_FWDGTx_HOLD (x=0,1): hold FWDGT counter when core is halted
    \param[out] none
    \retval     none
*/
void dbg_periph_disable(dbg_periph_enum dbg_periph)
{
    DBG_REG_VAL(dbg_periph) &= ~BIT(DBG_BIT_POS(dbg_periph));
}
