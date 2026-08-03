/*!
    \file    gd32a7xx_mtc.c
    \brief   MTC driver

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

#include "gd32a7xx_mtc.h"

/*!
    \brief      mtc deinit (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mtc_deinit(void)
{
    /* reset MTC register */
    MTC_CTL0     =    0x00000000U;
    MTC_CHCTL0   =    0x00000000U;
    MTC_CHCTL1   =    0x00000000U;
    MTC_CTL1     =    0x00000000U;
    MTC_EBGCFG0  =    0x00000000U;
    MTC_EBGCFG1  =    0x00000000U;
    MTC_EBGCFG2  =    0x00000000U;
    MTC_EBGCFG3  =    0x00000000U;
    MTC_EBGCFG4  =    0x00000000U;
    MTC_TMREN    =    0x00000000U;
    MTC_TMRFC    =    0x00000000U;

    rcu_periph_reset_enable(RCU_MTCRST);
    rcu_periph_reset_disable(RCU_MTCRST);
}

/*!
    \brief      enable global memory test (API_ID(0x0002U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mtc_enable(void)
{
    MTC_CTL0 = MTC_ENABLE;
}

/*!
    \brief      disable global memory test (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mtc_disable(void)
{
    MTC_CTL0 &= (uint32_t)(~MTC_CTL0_GMTEN);
}

/*!
    \brief      select EDC error bits generation mode (API_ID(0x0004U))
    \param[in]  mode: error mode
                only one parameter can be selected which is shown as below:
      \arg        EDCMOD_ECC: error bits generation of ECC 
      \arg        EDCMOD_EDC: EDC error injecton
      \arg        EDCMOD_EDC_ECC: EDC after ECC error injection
    \param[out] none
    \retval     none
*/
void mtc_error_mode(uint8_t mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MTC_ERR_MODE(mode)) {
        fw_debug_report_err(MTC_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else
#endif
    {
        MTC_CTL1 = mode;
    }
}

/*!
    \brief      enable memory test channel x (API_ID(0x0005U))
    \param[in]  channel: MTC channel
                only one parameter can be selected which is shown as below:
      \arg      MTC_CHCTL0_CHENx(x = 0...31),refer MTC channel mapping
                MTC_CHCTL1_CHENx(x = 32...60),refer MTC channel mapping
    \param[out] none
    \retval     none
*/
void mtc_channel_enable(mtc_channel_enum channel)
{
    uint32_t mtc_channel = (uint32_t)channel;

    if(mtc_channel < 32U) {
        MTC_CHCTL0 |= BIT(mtc_channel);
    } else {
        MTC_CHCTL1 |= BIT(mtc_channel - 32U);
    }

}

/*!
    \brief      disable memory test channel x (API_ID(0x0006U))
    \param[in]  channel: MTC channel
                only one parameter can be selected which is shown as below:
      \arg      MTC_CHCTL0_CHENx(x = 0...31),refer MTC channel mapping
                MTC_CHCTL1_CHENx(x = 32...60),refer MTC channel mapping
    \param[out] none
    \retval     none
*/
void mtc_channel_disable(mtc_channel_enum channel)
{
    uint32_t mtc_channel = (uint32_t)channel;

    if(mtc_channel < 32U) {
        MTC_CHCTL0 &= ~BIT(mtc_channel);
    } else {
        MTC_CHCTL1 &= ~BIT(mtc_channel - 32U);
    }

}

/*!
    \brief      configure single error bit (API_ID(0x0007U))
    \param[in]  u16bitpos: bit position
      \arg      u16bitpos(0...159)
    \param[out] none
    \retval     none
*/
void mtc_inject_single_bit(uint16_t u16bitpos)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MTC_BIT(u16bitpos)) {
        fw_debug_report_err(MTC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        if(u16bitpos < 32U * 1U) {
            MTC_EBGCFG0 |= BIT(u16bitpos);
        } else if(u16bitpos < 32U * 2U) {
            MTC_EBGCFG1 |= BIT(u16bitpos - 32U * 1U);
        } else if(u16bitpos < 32U * 3U) {
            MTC_EBGCFG2 |= BIT(u16bitpos - 32U * 2U);
        } else if(u16bitpos < 32U * 4U) {
            MTC_EBGCFG3 |= BIT(u16bitpos - 32U * 3U);
        } else {
            MTC_EBGCFG4 |= BIT(u16bitpos - 32U * 4U);
        }
    }
}

/*!
    \brief      configure multi error bit (API_ID(0x0008U))
    \param[in]  u16bitpos1: first bit position
    \param[in]  u16bitpos2: second bit position
    \param[out] none
    \retval     none
*/
void mtc_inject_multi_bit(uint16_t u16bitpos1, uint16_t u16bitpos2)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_MTC_BIT(u16bitpos1) || NOT_MTC_BIT(u16bitpos2)) {
        fw_debug_report_err(MTC_MODULE_ID, API_ID(0x0008U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        mtc_inject_single_bit(u16bitpos1);
        mtc_inject_single_bit(u16bitpos2);
    }
}

/*!
    \brief      TMR enable (API_ID(0x0009U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mtc_tmr_enable(void)
{
    MTC_TMREN |= MTC_TMR_EN;
}


/*!
    \brief      TMR disable (API_ID(0x000AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mtc_tmr_disable(void)
{
    MTC_TMREN &= ~MTC_TMR_EN;
}

/*!
    \brief      get TMR error flag (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
FlagStatus mtc_tmr_flag_get(void)
{
    FlagStatus flag_satus = RESET;
    if(0U != (MTC_TMRSTAT & MTC_TMR_ERR)) {
        flag_satus = SET;
    }
    return flag_satus;
}


/*!
    \brief      clear TMR error flag  (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void mtc_tmr_flag_clear(void)
{
    MTC_TMRFC |= MTC_TMR_FC;
}
