/*!
    \file    gd32a7xx_STCM.c
    \brief   STCM driver

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

#include "gd32a7xx_stcm.h"

/* DLC to data size in bytes definitions */
static const uint32_t stcm_unlock_key[3][2] = { {STCM_UNLOCK_KEY_LOOP0_KEY0, STCM_UNLOCK_KEY_LOOP0_KEY1}, 
                                                {STCM_UNLOCK_KEY_LOOP1_KEY0, STCM_UNLOCK_KEY_LOOP1_KEY1}, 
                                                {STCM_UNLOCK_KEY_LOOP2_KEY0, STCM_UNLOCK_KEY_LOOP2_KEY1} };

/*!
    \brief      reset STCM register (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void stcm_deinit(void)
{
    /* reset STCM */
    rcu_periph_reset_enable(RCU_STCMRST);
    rcu_periph_reset_disable(RCU_STCMRST);
}

/*!
    \brief      unlock STCM config registers (API_ID(0x0002U))
    \param[in]  key_loop_index: STCM registers unlock key loop index
        \arg      STCM_UNLOCK_KEY_LOOP0: unlock key loop index 0
        \arg      STCM_UNLOCK_KEY_LOOP1: unlock key loop index 1
        \arg      STCM_UNLOCK_KEY_LOOP2: unlock key loop index 2
    \param[out] none
    \retval     none
*/
void stcm_unlock(uint8_t key_loop_index)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_UNLOCK_KEY_LOOP_INDEX(key_loop_index)){
           fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0002U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* unlock STCM config registers */
        STCM_WPK = stcm_unlock_key[key_loop_index][0U];
        STCM_WPK = stcm_unlock_key[key_loop_index][1U];
    }
}

/*!
    \brief      STCM write access enable (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void stcm_writeacess_enable(void)
{
    /* enable STCM write access */
    STCM_CFG0 |= STCM_CFG0_WAP;
}

/*!
    \brief      STCM write access disable (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void stcm_writeacess_disable(void)
{
    /* disable STCM write access */
    STCM_CFG0 &= ~STCM_CFG0_WAP;
}

/*!
    \brief      TMR (Triple-Modular Redundancy) run BIST phase enable (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void stcm_tmr_enable(void)
{
    /* enable TMR (Triple-Modular Redundancy) */
    STCM_TMRCS = STCM_RUNBP_TMREN;
}

/*!
    \brief      TMR (Triple-Modular Redundancy) run BIST phase disable (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void stcm_tmr_disable(void)
{
    /* disable TMR (Triple-Modular Redundancy) */
    STCM_TMRCS = STCM_RUNBP_TMRDIS;
}

/*!
    \brief      BIST executed with PLL enabled (API_ID(0x0007U))
    \param[in]  mbistpllen: MBIST executed with PLL enabled, ENABLE or DISABLE
        \arg      ENABLE: MBIST executed with PLL enabled
        \arg      DISABLE: MBIST executed with PLL disabled
    \param[in]  lbistpllen: LBIST executed with PLL enabled, ENABLE or DISABLE
        \arg      ENABLE: MBIST executed with PLL enabled
        \arg      DISABLE: MBIST executed with PLL disabled
    \param[out] none
    \retval     none
*/
void stcm_bist_with_pll(uint32_t mbistpllen, uint32_t lbistpllen)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BIST_PLL_ENABLE_CFG(mbistpllen) ||
       NOT_BIST_PLL_ENABLE_CFG(lbistpllen)){
           fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0007U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable MBIST & LBIST PLL by clearing the LBEPLLEN and MBEPLLEN bit in STCM_BRCS register */
#if defined(GD32A714X) || defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        STCM_BRCS &= ~(STCM_BRCS_LBEPLLEN | STCM_BRCS_MBEPLLEN);
#else
        STCM_BRCS &=  ~STCM_BRCS_MBEPLLEN;
#endif /* defined(GD32A714X) || defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        if(mbistpllen != (uint32_t)DISABLE)
        {
            /* enable the MBIST PLL */
            STCM_BRCS |= STCM_BRCS_MBEPLLEN;
        }
#if defined(GD32A714X) || defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        if(lbistpllen != (uint32_t)DISABLE)
        {
            /* enable the LBIST PLL */
            STCM_BRCS |= STCM_BRCS_LBEPLLEN;
        }
#endif /* defined(GD32A714X) || defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    }
}

/*!
    \brief      first BIST select (API_ID(0x0008U))
    \param[in]  ptr: pointer to the first BIST
                only one parameter can be selected which is shown as below:
      \arg        STCM_PTR_MBISTx (x=0~12): the first BIST is MBISTx
      \arg        STCM_PTR_LBIST : the first BIST is LBIST
      \arg        STCM_PTR_NIL : no BIST select
    \param[out] none
    \retval     none
*/
void stcm_firstbist(uint32_t ptr)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BIST_FIRST_PTR(ptr)){
       fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0008U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* setup the first BIST to be executed */
        STCM_CFG0 &= ~STCM_CFG0_FBPTR;
        STCM_CFG0 |= ptr;
    }
}

/*!
    \brief      BIST general error mapping (API_ID(0x0009U))
    \param[in]  general_err_code:  BIST general error code
      \arg        STCM_BEM_PLLUNLK_ERR: PLL unlock error mapping code
      \arg        STCM_BEM_MBWDG_ERR: MBIST watchdog error mapping code
      \arg        STCM_BEM_LBWDG_ERR: LBIST watchdog error mapping code
      \arg        STCM_BEM_ENG_ERR: engine error mapping code
      \arg        STCM_BEM_INVP_ERR: invalid pointer error mapping code
      \arg        STCM_BEM_BPSEL_ERR: BIST partition error mapping code
      \arg        STCM_BEM_INVAITADDR_ERR: invalid AIT address error mapping code
    \param[in]  unrecoverable: BIST general error mapping
                only one parameter can be selected which is shown as below:
      \arg        STCM_ERROR_RECOVERABLE: BIST general recoverable error mapping
      \arg        STCM_ERROR_UNRECOVERABLE: BIST general unrecoverable error mapping
    \param[out] none
    \retval     none
*/
void stcm_general_bist_error_mapping(uint32_t general_err_code, uint32_t unrecoverable)
{
#ifdef FW_DEBUG_ERR_REPORT
    if( NOT_BIST_GENERAL_ERROR_CODE(general_err_code) ||
        NOT_ERROR_MAPPING_CFG(unrecoverable)){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0009U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_BEM &= ~(STCM_ERROR_UNRECOVERABLE << general_err_code);
        STCM_BEM |= (unrecoverable << general_err_code);
    }
}

/*!
    \brief      BIST phase interval config (API_ID(0x000AU))
    \param[in]  interval: the intervals between each BIST phase 
      \arg        0x0~0xFFFFFFFF: HCLK cycles
    \param[out] none
    \retval     none
*/
void stcm_bist_phase_intvl_cfg(uint32_t interval)
{
    STCM_BINTVL &= ~STCM_BINTVL_INTVL;
    STCM_BINTVL |= interval;
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      LBIST AIT packet interval config (API_ID(0x000BU))
    \param[in]  interval: the intervals between each LBIST packet 
      \arg        0x0~0xFFFFFFFF: HCLK cycles
    \param[out] none
    \retval     none
*/
void stcm_lbist_ait_packet_intvl_cfg (uint32_t interval)
{
    STCM_LBAITINTVL &= ~STCM_LBAITINTVL_INTVL;
    STCM_LBAITINTVL |= interval;
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      MBIST config (API_ID(0x000CU))
    \param[in]  mbistnum: the number of MBIST to be config
      \arg        0~12: MBIST x(x=0~12)
    \param[in]  spm: serial mode or parallel mode with next BIST
                only one parameter can be selected which is shown as below:
      \arg        STCM_SERIAL_MODE: serial mode, if the next BIST is LBIST or NIL, only STCM_SERIAL_MODE can be selescted
      \arg        STCM_PARALLEL_MODE: parallel mode
    \param[in]  nextptr: pointer to the next BIST
                only one parameter can be selected which is shown as below:
      \arg        STCM_PTR_MBISTx (x=0~12): the next BIST is MBISTx
      \arg        STCM_PTR_LBIST : the next BIST is LBIST
      \arg        STCM_PTR_NIL : no next BIST 
    \param[in]  mben: MBIST enable
                only one parameter can be selected which is shown as below:
      \arg        STCM_MBIST_DIS: MBIST disabled for execution
      \arg        STCM_MBIST_EN: MBIST enabled for execution
    \param[out] none
    \retval     none
*/
void stcm_mbist_config(uint32_t mbistnum, uint32_t spm, uint32_t nextptr, uint32_t mben)
{
#ifdef FW_DEBUG_ERR_REPORT
    if((mbistnum > STCM_MBIST_MAX_NUM)  ||
        NOT_MBIST_EXECUTION_MODE(spm)   ||
        NOT_MBIST_NEXT_PTR(nextptr)     ||
        NOT_MBIST_ENABLE_CFG(mben)){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x000CU),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_MBPCFG(mbistnum) = spm | nextptr | mben;
    }
}

/*!
    \brief      MBIST partition error mapping (API_ID(0x000DU))
    \param[in]  mbistnum: the number of MBIST to be config
      \arg        0~12: MBIST x(x=0~12)
    \param[in]  unrecoverable: MBIST partition error mapping
                only one parameter can be selected which is shown as below:
      \arg        STCM_ERROR_RECOVERABLE: MBIST partition recoverable error mapping
      \arg        STCM_ERROR_UNRECOVERABLE: MBIST partition unrecoverable error mapping
    \param[out] none
    \retval     none
*/
void stcm_mbist_errormapping(uint32_t mbistnum, uint32_t unrecoverable)
{
#ifdef FW_DEBUG_ERR_REPORT
    if((mbistnum > STCM_MBIST_MAX_NUM) || \
        NOT_ERROR_MAPPING_CFG(unrecoverable)){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x000DU),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_MBPEM &= ~(STCM_ERROR_UNRECOVERABLE << mbistnum);
        STCM_MBPEM |= (unrecoverable << mbistnum);
    }
}

/*!
    \brief      MBIST watchdog config (API_ID(0x000EU))
    \param[in]  counter: MBIST watchdog timeout configuration
      \arg        1~0xFFFFFFFF : MBIST watchdog clocks 
    \param[in]  clkdiv: MBIST watchdog clock divider
                only one parameter can be selected which is shown as below:
      \arg        STCM_MBISTWDG_CLKDIV1: HCLK / 1
      \arg        STCM_MBISTWDG_CLKDIV4: HCLK / 4
      \arg        STCM_MBISTWDG_CLKDIV16: HCLK / 16
      \arg        STCM_MBISTWDG_CLKDIV64: HCLK / 64
    \param[out] none
    \retval     none
*/
void stcm_mbist_wdg_config(uint32_t counter, uint32_t clkdiv)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_MBIST_WDG_CLKDIV(clkdiv)){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x000EU),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_MBWDGT = counter;
        STCM_CFG0 &= ~STCM_CFG0_MBWDG_DIV;
        STCM_CFG0 |= clkdiv;
    }
}

/*!
    \brief      get MBIST partition status (API_ID(0x000FU))
    \param[in]  mbistnum: the number of MBIST to be config
      \arg        0~12: MBIST x(x=0~12)
    \param[out] none
    \retval     MBIST partition result
      \arg        STCM_NOTCOMPLETE: BIST execution not yet completed
      \arg        STCM_FAILED: BIST execution failed
      \arg        STCM_SUCCESSFUL: BIST execution successful 
      \arg        STCM_ENDERROR: BIST execution end error
      \arg        STCM_RESULTERROR: BIST execution result error 
*/
stcm_bist_state stcm_mbist_stat_get(uint32_t mbistnum)
{
    stcm_bist_state mbist_state;
    uint32_t end , result;
#ifdef FW_DEBUG_ERR_REPORT
    if(mbistnum > STCM_MBIST_MAX_NUM){
        mbist_state = STCM_NOTCOMPLETE;
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x000FU),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        end = (STCM_MBPE_STAT >> (mbistnum * 2U)) & STCM_END_FINISH;
        result = (STCM_MBPSTAT >> (mbistnum * 2U)) & STCM_RESULE_SUCCESSFUL;
        if(end == STCM_END_FINISH)
        {
            if(result == STCM_RESULE_SUCCESSFUL)
            {
                mbist_state = STCM_SUCCESSFUL;
            }
            else if(result == STCM_RESULT_FAILED)
            {
                mbist_state = STCM_FAILED;
            }
            else
            {
                mbist_state = STCM_RESULTERROR;
            }
        }
        else if(end == STCM_END_NOTCOMPLETE)
        {
            mbist_state = STCM_NOTCOMPLETE;
        }
        else
        {
            mbist_state = STCM_ENDERROR;
        }
    }
     return mbist_state;
}

/*!
    \brief      MBIST launch config (API_ID(0x00010U))
    \param[in]  launch: MBIST launch configuration
                only one parameter can be selected which is shown as below:
      \arg        STCM_MBLAUNCH_NOP: NOP,reset value
      \arg        STCM_MBLAUNCH_RUNONLY: run BIST only, STCM runs the selected BISTs without programming them first
      \arg        STCM_MBLAUNCH_PROGONLY: program BIST only,STCM only programs BISTs and does not start them
      \arg        STCM_MBLAUNCH_RUN_PROG: program BISTs and start them
    \param[out] none
    \retval     none
*/
void stcm_mbist_launch_config(uint32_t launch)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_MBIST_LAUNCH_CFG(launch)){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0010U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_MBLAUNCH = launch;
    }
}

/*!
    \brief      MBIST algorithm selection(API_ID(0x00011U))
    \param[in]  algo: MBIST algorithm selection, when multiple algorithms are selected, the algorithms will be executed in LSB order
                one or more parameters can be selected which are shown as below:
      \arg        MBIST_ALGO_x (x=0~13): MBIST algorithm x selection
    \param[out] none
    \retval     none
*/
void stcm_mbist_algosel(uint32_t algo)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(0U != (algo & (~MBIST_ALGO_AVAILABLE_MASK))){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0011U),ERR_PARAM_INVALID);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_MBALGSEL = algo;
    }
}
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      LBIST config (API_ID(0x00012U))
    \param[in]  spm: serial mode or parallel mode with next BIST
                only one parameter can be selected which is shown as below:
      \arg        STCM_SERIAL_MODE: serial mode, if the next BIST is MBIST or NIL, only STCM_SERIAL_MODE can be selected
    \param[in]  nextptr: pointer to the next BIST
                only one parameter can be selected which is shown as below:
      \arg        STCM_PTR_MBISTx (x=0~12): the next BIST is MBISTx
      \arg        STCM_PTR_NIL : no next BIST 
    \param[in]  shr: shift rate
                only one parameter can be selected which is shown as below:
      \arg        STCM_LBIST_SHR_FULL: Full rate of BIST clock
      \arg        STCM_LBIST_SHR_DIVx (x=2~8): 1/x rate of BIST clock
    \param[in]  datasource: AIT packet is read from ROM or RAM
                only one parameter can be selected which is shown as below:
      \arg        STCM_AIT_ROM: AIT packet is read from ROM
      \arg        STCM_AIT_RAM: AIT packet is read from RAM
    \param[in]  clkdiv: LBIST reference clock divider
                only one parameter can be selected which is shown as below:
      \arg        STCM_AITCLK_DIV1: CK_AIT / 1
      \arg        STCM_AITCLK_DIV2: CK_AIT / 2
      \arg        STCM_AITCLK_DIV10: CK_AIT / 10
    \param[out] none
    \retval     none
*/
void stcm_lbist_config(uint32_t spm, uint32_t nextptr, uint32_t shr, uint32_t datasource, uint32_t clkdiv)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LBIST_EXECUTION_MODE(spm)      ||
       NOT_LBIST_NEXT_PTR(nextptr)        ||
       NOT_LBIST_SHIFT_RATE(shr)          ||
       NOT_LBIST_DATA_SOURCE(datasource)  ||
       NOT_LBIST_CLKDIV(clkdiv)){
       fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0012U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_LBPCFG = spm | nextptr | shr;
        STCM_CFG0 &= ~(STCM_CFG0_AOSEL | STCM_CFG0_REF_DIV);
        STCM_CFG0 |= datasource | clkdiv ;
    }
}

/*!
    \brief      LBIST partition error mapping (API_ID(0x00013U))
    \param[in]  unrecoverable: LBIST partition error mapping
                only one parameter can be selected which is shown as below:
      \arg        STCM_ERROR_RECOVERABLE: LBIST partition recoverable error mapping
      \arg        STCM_ERROR_UNRECOVERABLE: LBIST partition unrecoverable error mapping
    \param[out] none
    \retval     none
*/
void stcm_lbist_errormapping(uint32_t unrecoverable)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ERROR_MAPPING_CFG(unrecoverable)){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0013U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_LBPEM &= ~(STCM_ERROR_UNRECOVERABLE);
        STCM_LBPEM |= unrecoverable;
    }
}

/*!
    \brief      LBIST watchdog config (API_ID(0x00014U))
    \param[in]  counter: LBIST watchdog timeout configuration
      \arg        1~0xFFFFFFFF: LBIST watchdog clocks 
    \param[in]  clkdiv: LBIST watchdog clock divider
                only one parameter can be selected which is shown as below:
      \arg        STCM_LBISTWDG_CLKDIV1: HCLK / 1
      \arg        STCM_LBISTWDG_CLKDIV4: HCLK / 4
      \arg        STCM_LBISTWDG_CLKDIV16: HCLK / 16
      \arg        STCM_LBISTWDG_CLKDIV64: HCLK / 64
    \param[out] none
    \retval     none
*/
void stcm_lbist_wdg_config(uint32_t counter, uint32_t clkdiv)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LBIST_WDG_CLKDIV(clkdiv)){
       fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0014U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_LBWDGT = counter;
        STCM_CFG0 &= ~STCM_CFG0_LBWDG_DIV;
        STCM_CFG0 |= clkdiv;
    }
}

/*!
    \brief      get LBIST partition status (API_ID(0x00015U))
    \param[in]  none
    \param[out] none
    \retval     LBIST result
      \arg        STCM_NOTCOMPLETE: BIST execution not yet completed
      \arg        STCM_FAILED: BIST execution failed
      \arg        STCM_SUCCESSFUL: BIST execution successful 
      \arg        STCM_ENDERROR: BIST execution end error
      \arg        STCM_RESULTERROR: BIST execution result error 
*/
stcm_bist_state stcm_lbist_stat_get(void)
{
    uint32_t end, result;
    stcm_bist_state lbist_state;

    end = STCM_LBPE_STAT & STCM_END_FINISH;
    result = STCM_LBPSTAT & STCM_RESULE_SUCCESSFUL;

    if(end == STCM_END_FINISH)
    {
        if(result == STCM_RESULE_SUCCESSFUL)
        {
            lbist_state = STCM_SUCCESSFUL;
        }
        else if(result == STCM_RESULT_FAILED)
        {
            lbist_state = STCM_FAILED;
        }
        else
        {
            lbist_state = STCM_RESULTERROR;
        }
    }
    else if(end == STCM_END_NOTCOMPLETE)
    {
        lbist_state = STCM_NOTCOMPLETE;
    }
    else
    {
        lbist_state = STCM_ENDERROR;
    }
    return lbist_state;
}

/*!
    \brief      LBIST shift clock config (API_ID(0x00016U))
    \param[in]  stepsize: Peripheral shift clock control step size
      \arg        1~8: Peripheral shift clock control step size
    \param[in]  starten: Peripheral shift clock control start enable
      \arg        ENABLE: Peripheral shift clock control start enabled 
      \arg        DISABLE: Peripheral shift clock control start disabled
    \param[in]  enden: Peripheral shift clock control end enable
      \arg        ENABLE: Peripheral shift clock control end enabled 
      \arg        DISABLE: Peripheral shift clock control end disabled
    \param[out] none
    \retval     none
*/
void stcm_lbist_shiftclk_config(uint32_t stepsize, uint32_t starten, uint32_t enden)
{
#ifdef FW_DEBUG_ERR_REPORT
    if( NOT_LBIST_SHIFTCLK_STEP_SIZE(stepsize) || NOT_LBIST_SHIFTCLK_START_EN(starten) || NOT_LBIST_SHIFTCLK_END_EN(enden)){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0016U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_LBPSCC = (stepsize-1U)<<4U;
        if(starten != (uint32_t)DISABLE)
        {
            STCM_LBPSCC |= STCM_LBPSCC_PSCC_SEN;
        }
        if(enden != (uint32_t)DISABLE)
        {
            STCM_LBPSCC |= STCM_LBPSCC_PSCC_EEN;
        }
    }
}

/*!
    \brief      LBIST engine timeout strap config (API_ID(0x00017U))
    \param[in]  timestrap: engine timeout strap raw data, the actual value is 2^timestrap AIT engine reference clock cycles
    \param[out] none
    \retval     none
*/
void stcm_lbist_engine_timestrap_config (uint32_t timestrap)
{
#ifdef FW_DEBUG_ERR_REPORT
    if((timestrap > STCM_LBIST_ENG_TIMESTRAP_MAX)){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0017U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_LBCNTSTRAP = timestrap;
    }
}

/*!
    \brief      LBIST packet config (API_ID(0x00018U))
    \param[in]  first_ait_packet_index: first AIT packet index
    \param[in]  ait_packet_num:  AIT packet number to be executed
    \param[out] none
    \retval     none
*/
void stcm_lbist_packet_config(uint8_t first_ait_packet_index, uint8_t ait_packet_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    if((first_ait_packet_index >= STCM_LBIST_AIT_PACKET_NUM_MAX) || (ait_packet_num > STCM_LBIST_AIT_PACKET_NUM_MAX) ){
        fw_debug_report_err(STCM_MODULE_ID,API_ID(0x0018U),ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        STCM_CFG1 &= ~(STCM_CFG1_LBAITPN | STCM_CFG1_LBAITPADDR);
        STCM_CFG1 |= AIT_PACKET_ADDR(first_ait_packet_index) | ait_packet_num;
    }
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      BIST start (API_ID(0x00019U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void stcm_bist_start(void)
{
    STCM_BRCS = STCM_BRCS_RUNBP;
}

/*!
    \brief      get TMR state (API_ID(0x0001AU))
    \param[in]  none
    \param[out] none
    \retval     TMR state
      \arg       STCM_TMR_ERR: TMR(Triple-Modular Redundancy) run BIST phase error state 
      \arg       STCM_TMR_NORMAL: TMR(Triple-Modular Redundancy) run BIST phase normal state
*/
stcm_tmr_state stcm_tmr_stat_get(void)
{
    stcm_tmr_state tmr_state = STCM_TMR_NORMAL;
    if( 1U == ((STCM_TMRCS & STCM_TMRCS_TMR_RUNBP)>>1U)){
        tmr_state = STCM_TMR_ERR;
    }
    return tmr_state;
}

/*!
    \brief      get BIST error state (API_ID(0x0001BU))
    \param[in]  error_code: BIST error code
                only one parameter can be selected which is shown as below:
      \arg        BESTAT0_PLLULK: PLL unlock error code
      \arg        BESTAT0_LBWDG: LBIST watchdog error code
      \arg        BESTAT0_INVPTR: invalid LBIST pointer error code
      \arg        BESTAT0_BPSEL: BIST phase select error state flag
      \arg        BESTAT0_INVAITPADDR: invalid AIT packet address error code
      \arg        BESTAT0_MBWDGx(x=0~12): MBIST partition x watchdog error code
      \arg        BESTAT0_MBWDGEG: MBIST watchdog global error code
      \arg        BESTAT1_SP0: SMART protocol error code 0
      \arg        BESTAT1_SP1: SMART protocol error code 1
      \arg        BESTAT1_SP2: SMART protocol error code 2
      \arg        BESTAT1_AITP0: AIT protocol error code 0
      \arg        BESTAT1_AITP1: AIT protocol error code 1
      \arg        BESTAT1_RECOV: recoverable error code
      \arg        BESTAT1_UNRECOV: unrecoverable error code
    \param[out] none
    \retval     BIST error state
      \arg        RESET: BIST error is reset
      \arg        SET: BIST error is set
*/
FlagStatus stcm_bist_err_stat_get(stcm_error_code_enum error_code)
{
    FlagStatus bist_err_sate = RESET;
    switch(error_code){
        case BESTAT0_PLLULK:
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case BESTAT0_LBWDG:
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        case BESTAT0_INVPTR:
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case BESTAT0_BPSEL:
        case BESTAT0_INVAITPADDR:
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        case BESTAT0_MBWDG0:
        case BESTAT0_MBWDG1:
        case BESTAT0_MBWDG2:
        case BESTAT0_MBWDG3:
        case BESTAT0_MBWDG4:
        case BESTAT0_MBWDG5:
        case BESTAT0_MBWDG6:
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case BESTAT0_MBWDG7:
        case BESTAT0_MBWDG8:
        case BESTAT0_MBWDG9:
        case BESTAT0_MBWDG10:
        case BESTAT0_MBWDG11:
        case BESTAT0_MBWDG12:
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        case BESTAT0_MBWDGEG:
          if(1U == ((STCM_BESTAT0 >> ((uint32_t)error_code>>1U)) & 0x00000001U)){
            bist_err_sate = SET;
          }
        break;
        case BESTAT1_SP0:
        case BESTAT1_SP1:
        case BESTAT1_SP2:
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case BESTAT1_AITP0:
        case BESTAT1_AITP1:
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        case BESTAT1_RECOV:
        case BESTAT1_UNRECOV:
          if(1U == ((STCM_BESTAT1 >> ((uint32_t)error_code>>1U)) & 0x00000001U)){
            bist_err_sate = SET;
          }
        break;
        default:
#ifdef FW_DEBUG_ERR_REPORT
            fw_debug_report_err(STCM_MODULE_ID,API_ID(0x001BU),ERR_PARAM_INVALID);
#endif /* FW_DEBUG_ERR_REPORT */
        break;
    }
    return bist_err_sate;
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      get the timeout or failed LBIST AIT information (API_ID(0x0001CU))
    \param[in]  none
    \param[out] packet_addr: timeout or failed ait address
    \param[out] ait_stat: timeout or failed ait state
    \retval     none
*/
void stcm_failed_timeout_lbist_ait_info_get(uint16_t *packet_addr,uint8_t *ait_stat)
{
#ifdef FW_DEBUG_ERR_REPORT
    if((NOT_VALID_POINTER(packet_addr)) || (NOT_VALID_POINTER(ait_stat))) {
        fw_debug_report_err(STCM_MODULE_ID, API_ID(0x001CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        *packet_addr = (uint16_t)(STCM_LBPEINF & STCM_LBPEINF_LBPEADDR)>>16U;
        *ait_stat    = (uint8_t)(STCM_LBPEINF & STCM_LBPEINF_AIT_STAT);
    }
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
