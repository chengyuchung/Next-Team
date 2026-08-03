/*!
    \file    gd32a7xx_busim.c
    \brief   BUSIM driver

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

#include "gd32a7xx_busim.h"

/*!
    \brief      configure arbitration mode, API ID: 0x0001
    \param[in]  slaveport: specify the slave port to be configured
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_BM1_SLAVEx, x=0~4
      \arg        BUSIM_BM2_SLAVEx, x=0~3
    \param[in]  aribitration: specify the arbitration mode used
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_ARBITRATION_FIXED: fixed priority mode
      \arg        BUSIM_ARBITRATION_ROUNDROBIN: round-robin priority mode
    \param[out] none
    \retval     none
*/
void busim_arbitration_config(uint32_t slaveport, uint32_t aribitration)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_BM_SLAVE(slaveport)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(1), ERR_PARAM_INVALID);
    } else if(NOT_BUSIM_ARBITRATION(aribitration)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(1), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        BUSIM_BMCTL(slaveport) &= ~BUSIM_CTL_ARBMOD;
        BUSIM_BMCTL(slaveport) |= aribitration;
    }
}

/*!
    \brief      configure fixed priority, API ID: 0x0002
    \param[in]  slaveport: specify the slave port to be configured
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_BM1_SLAVEx, x=0~4
      \arg        BUSIM_BM2_SLAVEx, x=0~3
    \param[in]  masterport: specify the master port to be configured
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_BM1_MASTERx, x=0~7
      \arg        BUSIM_BM2_MASTERx, x=0~6
    \param[in]  priority: specify the priority to be configured
                only one parameter can be selected which is shown as below:
      \arg        PRIORITY_L1: master has L1 priority on associated slave port
      \arg        PRIORITY_L2: master has L2 priority on associated slave port
      \arg        PRIORITY_L3: master has L3 priority on associated slave port
      \arg        PRIORITY_L4: master has L4 priority on associated slave port
      \arg        PRIORITY_L5: master has L5 priority on associated slave port
      \arg        PRIORITY_L6: master has L6 priority on associated slave port
      \arg        PRIORITY_L7: master has L7 priority on associated slave port
      \arg        PRIORITY_L8: master has L8 priority on associated slave port
    \param[out] none
    \retval     none
*/
void busim_fixed_priority_config(uint32_t slaveport, uint32_t masterport, uint32_t priority)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_BM_SLAVE(slaveport)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(2), ERR_PARAM_INVALID);
    } else if(NOT_BUSIM_BM_MASTER(masterport)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(2), ERR_PARAM_INVALID);
    } else if(NOT_BUSIM_PRIORITY(priority)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(2), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        BUSIM_BMSPCFG(slaveport) &= (uint32_t)~(BITS(0, 2) << masterport);
        BUSIM_BMSPCFG(slaveport) |= (uint32_t)(priority << masterport);
    }
}

/*!
    \brief      enable highest priority mode, API ID: 0x0003
    \param[in]  slaveport: specify the slave port to be configured
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_BM1_SLAVEx, x=0~4
      \arg        BUSIM_BM2_SLAVEx, x=0~3
    \param[in]  master_port: specify the master port
      \arg        BUSIM_MASTER_PORTx, x=0~7
    \param[out] none
    \retval     none
*/
void busim_highest_priority_enable(uint32_t slaveport, uint32_t master_port)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_BM_SLAVE(slaveport)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(3), ERR_PARAM_INVALID);
    } else if(NOT_BUSIM_MASTER_PORT(master_port)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(3), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        BUSIM_BMCTL(slaveport) |= BUSIM_CTL_HPM0EN << master_port;
    }
}

/*!
    \brief      disable highest priority mode, API ID: 0x0004
    \param[in]  slaveport: specify the slave port to be configured
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_BM1_SLAVEx, x=0~4
      \arg        BUSIM_BM2_SLAVEx, x=0~3
    \param[in]  master_port: specify the master port
      \arg        BUSIM_MASTER_PORTx, x=0~7
    \param[out] none
    \retval     none
*/
void busim_highest_priority_disable(uint32_t slaveport, uint32_t master_port)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_BM_SLAVE(slaveport)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(4), ERR_PARAM_INVALID);
    } else if(NOT_BUSIM_MASTER_PORT(master_port)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(4), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        BUSIM_BMCTL(slaveport) &= ~(BUSIM_CTL_HPM0EN << master_port);
    }
}

/*!
    \brief      configure default access the slave port by the master port which is the last master accessed or determined by DMP[2:0], API ID: 0x0005
    \param[in]  slaveport: specify the slave port to be configured
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_BM1_SLAVEx, x=0~4
      \arg        BUSIM_BM2_SLAVEx, x=0~3
    \param[in]  defaultmaster: specify the default master
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_DEFAULTMASTER_Mx(x=0~7): default access the slave port by the master port Mx
      \arg        BUSIM_DEFAULTMASTER_LAST: default master port strategy select
    \param[out] none
    \retval     none
*/
void busim_default_master_access_config(uint32_t slaveport, uint32_t defaultmaster)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_BM_SLAVE(slaveport)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(5), ERR_PARAM_INVALID);
    } else if(NOT_BUSIM_DEFAULT_MASTER(defaultmaster)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(5), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t temp = BUSIM_BMCTL(slaveport);
        temp &= ~(BUSIM_CTL_DMPSEL | BUSIM_CTL_DMP);
        temp |= defaultmaster;
        BUSIM_BMCTL(slaveport) = temp;
    }
}

/*!
    \brief      lock BUSIM control and slave port priority configuration register, API ID: 0x0006
    \param[in]  slaveport: specify the slave port to be configured
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_BM1_SLAVEx, x=0~4
      \arg        BUSIM_BM2_SLAVEx, x=0~3
    \param[out] none
    \retval     none
*/
void busim_reg_lock(uint32_t slaveport)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_BM_SLAVE(slaveport)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(6), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        BUSIM_BMCTL(slaveport) |= BUSIM_CTL_ROEN;
    }
}

/*!
    \brief      enable BUSIM TMR error, API ID: 0x0007
    \param[in]  tmrerr
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_TMRERR_EXTMPU: TMR error 0 (EXTMPU) output to FMU
      \arg        BUSIM_TMRERR_IMICU: TMR error 1 (IMICU) output to FMU
    \param[out] none
    \retval     none
*/
void busim_tmr_error_enable(uint32_t tmrerr)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_TMRERR(tmrerr)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(7), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        BUSIM_TMRFCS |= tmrerr;
    }
}

/*!
    \brief      disable BUSIM TMR error, API ID: 0x0008
    \param[in]  tmrerr
                only one parameter can be selected which is shown as below:
      \arg        BUSIM_TMRERR_EXTMPU: TMR error 0 (EXTMPU) output to FMU
      \arg        BUSIM_TMRERR_IMICU: TMR error 1 (IMICU) output to FMU
    \param[out] none
    \retval     none
*/
void busim_tmr_error_disable(uint32_t tmrerr)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_TMRERR(tmrerr)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(8), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        BUSIM_TMRFCS &= (uint32_t)~tmrerr;
    }
}

/*!
    \brief      get TMR error interrupt flag, API ID: 0x0009
    \param[in]  tmrerr_flag
                only one parameter can be selected which are shown as below:
      \arg        BUSIM_TMRERR_FLAG_EXTMPU: EXTMPU enable register TMR error status
      \arg        BUSIM_TMRERR_FLAG_IMICU: IMICU enable register TMR error status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus busim_tmr_error_flag_get(uint32_t tmrerr_flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_TMRERR_FLAG(tmrerr_flag)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(9), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (BUSIM_TMRFCS & tmrerr_flag)) {
            reval = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return reval;
}

/*!
    \brief      clear TMR error interrupt flag, API ID: 0x000A
    \param[in]  tmrerr_flag
                only one parameter can be selected which are shown as below:
      \arg        BUSIM_TMRERR_FLAG_EXTMPU: EXTMPU enable register TMR error status
      \arg        BUSIM_TMRERR_FLAG_IMICU: IMICU enable register TMR error status
    \param[out] none
    \retval     none
*/
void busim_tmr_error_flag_clear(uint32_t tmrerr_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUSIM_TMRERR_FLAG(tmrerr_flag)) {
        fw_debug_report_err(BUSIM_MODULE_ID, API_ID(10), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        BUSIM_TMRFCS |= tmrerr_flag;
    }
}
