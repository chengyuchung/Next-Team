/*!
    \file    gd32a7xx_gdap.c
    \brief   GD-AP driver

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

#include "gd32a7xx_gdap.h"

/*!
    \brief      configure debug authentication mode (API_ID: 0x0001U)
    \param[in]  auth_target: select current authentication target
      \arg        HOST_AUTH: host authentication
      \arg        HSM_AUTH: hsm authentication
    \param[out] none
    \retval     none
*/
void gd_ap_authentication_target_config(gd_ap_auth_traget_enum auth_target)
{
    switch(auth_target) {
        case HOST_AUTH:
            GD_AP_AUTH_CTL &= ~GD_AP_AUTH_CTL_AUTH_MODSEL;
        break;
        case HSM_AUTH:
            GD_AP_AUTH_CTL |= GD_AP_AUTH_CTL_AUTH_MODSEL;
            break;
        default:
            break;
        }
}

/*!
    \brief      configure the data is ready for static authentication (API_ID: 0x0002U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_authentication_ready_config(void)
{
    GD_AP_AUTH_CTL |= GD_AP_AUTH_CTL_DATRDY;
}

/*!
    \brief      enable debug authentication request (API_ID: 0x0003U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_authentication_request_enable(void)
{
    GD_AP_AUTH_CTL |= GD_AP_AUTH_CTL_AUTHREQEN;
}

/*!
    \brief      disable debug authentication request (API_ID: 0x0004U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_authentication_request_disable(void)
{
    GD_AP_AUTH_CTL &= ~GD_AP_AUTH_CTL_AUTHREQEN;
}

/*!
    \brief      get the key challenge value (API_ID: 0x0005U)
    \param[in]  none
    \param[out] key_challenge: key challenge value
    \retval     none
*/
void gd_ap_key_challenge_value_get(uint32_t key_challenge[])
{
    uint32_t index;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(key_challenge)){
        fw_debug_report_err(GD_AP_MODULE_ID, API_ID(0x0005U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* read GD_AP_KEYCHLG(x) register value */
        for(index = 0U ;index < 4U; index++)
        {
            key_challenge[index] = (uint32_t)(GD_AP_KEYCHLG(index));
        }
    }
}

/*!
    \brief      configure the key response value (API_ID: 0x0006U)
    \param[in]  none
    \param[out] key_response: key response value
    \retval     none
*/
void gd_ap_key_response_value_config(uint32_t key_response[])
{
    uint32_t index;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(key_response)){
        fw_debug_report_err(GD_AP_MODULE_ID, API_ID(0x0006U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* write GD_AP_KEYRESP(x) register value */
        for(index = 0U; index < 4U; index++)
        {
            GD_AP_KEYRESP(index) = key_response[index];
        }
    }
}

/*!
    \brief      get challenge ready flag (API_ID: 0x0007U)
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus gd_ap_challenge_reday_state_get(void)
{
    FlagStatus ret_flag;
    if(0U != (GD_AP_AUTH_STAT & GD_AP_AUTH_STAT_CHLGRDY)) {
        ret_flag = SET;
    } else {
        ret_flag = RESET;
    }
    return ret_flag;
}

/*!
    \brief      get current challenge mode (API_ID: 0x0008U)
    \param[in]  none
    \param[out] none
    \retval     gdap_auth_mode_enum: DYNAMIC_AUTH or STATIC_AUTH
*/
gd_ap_auth_mode_enum gd_ap_challenge_mode_state_get(void)
{
    gd_ap_auth_mode_enum auth_mode;
    if(0U != (GD_AP_AUTH_STAT & GD_AP_AUTH_STAT_CHLGMOD)) {
        auth_mode = STATIC_AUTH;
    } else {
        auth_mode = DYNAMIC_AUTH;
    }
    return auth_mode;
}

/*!
    \brief      get current host static authentication and host/hsm dynamic authentication status (API_ID: 0x0009U)
    \param[in]  auth_flag: authentication flag
                only one parameter can be selected which is shown as below:
      \arg        GD_AP_HOST_SAUTH_FLAG: host static authentication success flag
      \arg        GD_AP_HOST_DAUTH_FLAG: host dynamic authentication success flag
      \arg        GD_AP_HSM_DAUTH_FLAG: hsm dynamic authentication success flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus gd_ap_authentiction_state_get(uint32_t auth_flag)
{
    uint32_t reg;
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_GD_AP_AUTH_FLAG(auth_flag)) {
        fw_debug_report_err(GD_AP_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    }else
#endif
    {
        reg = GD_AP_AUTH_STAT;
        if(0U != (reg & auth_flag)){
            reval = SET;
        }
    }
    return reval;
}

/*!
    \brief      enable system reset or subsystem reset (API_ID: 0x000AU)
    \param[in]  rst_type: reset type selected
                only one parameter can be selected which is shown as below:
      \arg        SYSTEM_RESET: system reset
      \arg        SUBSYSTEM_RESET: subsystem reset
    \param[out] none
    \retval     none
*/
void gd_ap_reset_enable(gd_ap_reset_type_enum rst_type)
{
    switch(rst_type) {
    case SYSTEM_RESET:
        GD_AP_CTL |= GD_AP_CTL_SYSRSTEN;
    break;
    case SUBSYSTEM_RESET:
        GD_AP_CTL |= GD_AP_CTL_SUBSYSRSTEN;
        break;
    default:
        break;
    }
}

/*!
    \brief      disable system reset or subsystem reset (API_ID: 0x000BU)
    \param[in]  rst_type: reset type selected
                only one parameter can be selected which is shown as below:
      \arg        SYSTEM_RESET: system reset
      \arg        SUBSYSTEM_RESET: subsystem reset
    \param[out] none
    \retval     none
*/
void gd_ap_reset_disable(gd_ap_reset_type_enum rst_type)
{
    switch(rst_type) {
    case SYSTEM_RESET:
        GD_AP_CTL &= ~GD_AP_CTL_SYSRSTEN;
    break;
    case SUBSYSTEM_RESET:
        GD_AP_CTL &= ~GD_AP_CTL_SUBSYSRSTEN;
        break;
    default:
        break;
    }
}

/*!
    \brief      enable core debug request (API_ID: 0x000CU)
    \param[in]  target_core: core id
                only one parameter can be selected which is shown as below:
      \arg        CORE_CM7_0: CM7_0 core
      \arg        CORE_CM7_1: CM7_1 core
      \arg        CORE_CM23: CM23 core
    \param[out] none
    \retval     none
*/
void gd_ap_core_debug_request_enable(gd_ap_target_core_enum target_core)
{
    switch(target_core){
    /* enable CM7_0 debug request */
    case CORE_CM7_0:
        GD_AP_CTL |= GD_AP_CTL_CM7_0_DBGREQEN;
        break;
#if defined (GD32A72XX) || defined (GD32A74XX)
    /* enable CM7_1 debug request */
    case CORE_CM7_1:
        GD_AP_CTL |= GD_AP_CTL_CM7_1_DBGREQEN;
        break;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
    
    /* enable CM23 debug request */
    case CORE_CM23:
        GD_AP_CTL |= GD_AP_CTL_CM23_DBGREQEN;
        break;
    
    default :
        break;
    }
}

/*!
    \brief      disable core debug request (API_ID: 0x000DU)
    \param[in]  target_core: core id
                only one parameter can be selected which is shown as below:
      \arg        CORE_CM7_0: CM7_0 core
      \arg        CORE_CM7_1: CM7_1 core
      \arg        CORE_CM23: CM23 core
    \param[out] none
    \retval     none
*/
void gd_ap_core_debug_request_disable(gd_ap_target_core_enum target_core)
{
    switch(target_core){
    /* disable CM7_0 debug request */
    case CORE_CM7_0:
        GD_AP_CTL &=~ GD_AP_CTL_CM7_0_DBGREQEN;
        break;
#if defined (GD32A72XX) || defined (GD32A74XX)
    /* disable CM7_1 debug request */
    case CORE_CM7_1:
        GD_AP_CTL &=~ GD_AP_CTL_CM7_1_DBGREQEN;
        break;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
    /* disable CM23 debug request */
    case CORE_CM23:
        GD_AP_CTL &=~ GD_AP_CTL_CM23_DBGREQEN;
        break;

    default :
        break;
    }
}

/*!
    \brief      enable power watchdog (API_ID: 0x000EU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_power_watchdog_enable(void)
{
    GD_AP_CTL |= GD_AP_CTL_PORWDGTEN;
}

/*!
    \brief      disable power watchdog (API_ID: 0x000FU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_power_watchdog_disable(void)
{
    GD_AP_CTL &= ~GD_AP_CTL_PORWDGTEN;
}

/*!
    \brief      enable tpiu override (API_ID: 0x0010U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_tpiu_override_enable(void)
{
    GD_AP_CTL |= GD_AP_CTL_TPIUOVRDEN;
}

/*!
    \brief      disable tpiu override (API_ID: 0x0011U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_tpiu_override_disable(void)
{
    GD_AP_CTL &= ~GD_AP_CTL_TPIUOVRDEN;
}

/*!
    \brief      enable swo override (API_ID: 0x0012U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_swo_override_enable(void)
{
    GD_AP_CTL |= GD_AP_CTL_SWOOVRDEN;
}

/*!
    \brief      disable swo override (API_ID: 0x0013U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_swo_override_disable(void)
{
    GD_AP_CTL &= ~GD_AP_CTL_SWOOVRDEN;
}

/*!
    \brief      enable core debug restarted (API_ID: 0x0014U) 
    \param[in]  target_core: core id
                only one parameter can be selected which is shown as below:
      \arg        CORE_CM7_0: CM7_0 core
      \arg        CORE_CM7_1: CM7_1 core
      \arg        CORE_CM23: CM23 core
    \param[out] none
    \retval     none
*/
void gd_ap_debug_restart_enable(gd_ap_target_core_enum target_core)
{
    switch(target_core){
        /* enable CM7_0 debug request  */
        case CORE_CM7_0:
            GD_AP_CTL |= GD_AP_CTL_CM7_0_DBG_RSTARTEN;
            break;
#if defined (GD32A72XX) || defined (GD32A74XX)
        /* enable CM7_1 debug request  */
        case CORE_CM7_1:
            GD_AP_CTL |= GD_AP_CTL_CM7_1_DBG_RSTARTEN;
            break;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        /* enable CM23 debug request  */
        case CORE_CM23:
            GD_AP_CTL |= GD_AP_CTL_CM23_DBG_RSTARTEN;
            break;
        default :
            break;
        }
}

/*!
    \brief      disable core debug restarted (API_ID: 0x0015U)
    \param[in]  target_core: core id
                only one parameter can be selected which is shown as below:
      \arg        CORE_CM7_0: CM7_0 core
      \arg        CORE_CM7_1: CM7_1 core
      \arg        CORE_CM23: CM23 core
    \param[out] none
    \retval     none
*/
void gd_ap_debug_restart_disable(gd_ap_target_core_enum target_core)
{
    switch(target_core){
        /* enable CM7_0 debug request  */
        case CORE_CM7_0:
            GD_AP_CTL &= ~GD_AP_CTL_CM7_0_DBG_RSTARTEN;
            break;
#if defined (GD32A72XX) || defined (GD32A74XX)
        /* enable CM7_1 debug request  */
        case CORE_CM7_1:
            GD_AP_CTL &= ~GD_AP_CTL_CM7_1_DBG_RSTARTEN;
            break;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        /* enable CM23 debug request  */
        case CORE_CM23:
            GD_AP_CTL &= ~GD_AP_CTL_CM23_DBG_RSTARTEN;
            break;
        default :
            break;
    }
}

/*!
    \brief      enable trace clock (API_ID: 0x0016U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_trace_clock_enable(void)
{
    GD_AP_CTL |= (uint32_t)GD_AP_CTL_TRACE_CLKEN;
}

/*!
    \brief      disable trace clock (API_ID: 0x0017U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_trace_clock_disable(void)
{
    GD_AP_CTL &= (uint32_t)(~GD_AP_CTL_TRACE_CLKEN);
}

/*!
    \brief      enable low power debug mode (API_ID: 0x0018U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_low_power_enable(void)
{
    GD_AP_LPCTL0 |= GD_AP_LPCTL0_LPDBGEN;
}

/*!
    \brief      disable low power debug mode (API_ID: 0x0019U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void gd_ap_low_power_disable(void)
{
    GD_AP_LPCTL0 &= ~GD_AP_LPCTL0_LPDBGEN;
}

/*!
    \brief      on exiting standby mode, waiting until the debugger write to allow it to exit reset (API_ID: 0x001AU)
    \param[in]  exit_reset_mode: exit reset mode
                only one parameter can be selected which is shown as below:
      \arg        EXIT_RESET_NORMAL: normal exit reset
      \arg        EXIT_RESET_WAIT: on exiting standby mode, RCTL waits until the debugger writes
    \param[out] none
    \retval     none
*/
void gd_ap_wait_reset_config(gd_ap_exit_reset_mode_enum exit_reset_mode)
{
    switch(exit_reset_mode){
        /* normal exit reset  */
        case EXIT_RESET_NORMAL:
            GD_AP_LPCTL1 &= ~GD_AP_LPCTL1_WAITRST;
            break;
        /* on exiting standby mode, RCTL waits until the debugger writes  */
        case EXIT_RESET_WAIT:
            GD_AP_LPCTL1 |= GD_AP_LPCTL1_WAITRST;
            break;
        default :
            break;
    }
}

#if defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      TPIU flush trigger reset operation or prevented reset operation after TPIU is enabled (API_ID: 0x001BU)
    \param[in]  entry_reset_mode: entry reset mode
                only one parameter can be selected which is shown as below:
      \arg        ENTRY_RESET_NORMAL: normal entry reset
      \arg        ENTRY_RESET_BLOCK: PMU will waiting for TPIU flush done signal then generating low power entry sequence
    \param[out] none
    \retval     none
*/
void gd_ap_reset_block_config(gd_ap_entry_reset_mode_enum entry_reset_mode)
{
   switch(entry_reset_mode)
   {
       /* normal entry reset */
       case ENTRY_RESET_NORMAL:
           GD_AP_LPCTL1 &= ~GD_AP_LPCTL1_RST_BLK;
           break;
       /* PMU will waiting for TPIU flush done signal then generating low power entry sequence */
       case ENTRY_RESET_BLOCK:
           GD_AP_LPCTL1 |= GD_AP_LPCTL1_RST_BLK;
           break;
       default :
           break;
   }
}
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      enable debug function (API_ID: 0x001CU)
    \param[in]  debug
                only one parameter can be selected which is shown as below:
      \arg        CORE_CM23_DEBUG: core CM23 debug enable
      \arg        CORE_CM23_NON_INVASIVE_DEBUG: core CM23 non-invasive debug enable
      \arg        CORE_CM7_COMPOMENT_DEBUG: CM7 subsysterm, ITM, ETM and CTI compoment debug enable 
      \arg        CORE_CM7_COMPOMENT_NON_INVASIVE_DEBUG: CM7 subsysterm, ITM, ETM and CTI compoment non-invasive debug enable
      \arg        CORE_CM7_DEBUG: core CM7 debug enable
      \arg        CORE_CM7_NON_INVASIVE_DEBUG: core CM7 non-invasive debug enable

    \param[out] none
    \retval     none
*/
void gd_ap_debug_enable(uint32_t debug)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_GD_AP_CORE_DEBUG(debug)) {
        fw_debug_report_err(GD_AP_MODULE_ID, API_ID(0x001CU), ERR_PARAM_INVALID);
    }else
#endif
    {
        GD_AP_DBGEN |= debug;
    }
}

/*!
    \brief      disable debug function (API_ID: 0x001DU)
    \param[in]  debug
                only one parameter can be selected which is shown as below:
      \arg        CORE_CM23_DEBUG: core CM23 debug disable
      \arg        CORE_CM23_NON_INVASIVE_DEBUG: core CM23 non-invasive debug disable
      \arg        CORE_CM7_COMPOMENT_DEBUG: CM7 subsysterm, ITM, ETM and CTI compoment debug disable 
      \arg        CORE_CM7_COMPOMENT_NON_INVASIVE_DEBUG: CM7 subsysterm, ITM, ETM and CTI compoments non-invasive debug disable
      \arg        CORE_CM7_DEBUG: core CM7 debug disable
      \arg        CORE_CM7_NON_INVASIVE_DEBUG: core CM7 non-invasive debug disable

    \param[out] none
    \retval     none
*/
void gd_ap_debug_disable(uint32_t debug)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_GD_AP_CORE_DEBUG(debug)) {
        fw_debug_report_err(GD_AP_MODULE_ID, API_ID(0x001DU), ERR_PARAM_INVALID);
    }else
#endif
    {
        GD_AP_DBGEN &= ~debug;
    }
}

/*!
    \brief      target core entry reset state (API_ID: 0x001EU)
    \param[in]  target_core: core id
                only one parameter can be selected which is shown as below:
      \arg        CORE_CM7_0: CM7_0 core
      \arg        CORE_CM7_1: CM7_1 core
    \param[out] none
    \retval     none
*/
void gd_ap_entry_reset_config(gd_ap_target_core_enum target_core)
{
    {
        switch(target_core){
            /* CM7_0 core exti reset state */
            case CORE_CM7_0:
                GD_AP_RST &= ~GD_AP_CM7_0_RST;
                break;
#if defined (GD32A72XX) || defined (GD32A74XX)
            /* CM7_1 core exti reset state */
            case CORE_CM7_1:
                GD_AP_RST &= ~GD_AP_CM7_1_RST;
                break;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
            default :
                break;
        }
    }
}

/*!
    \brief      target core exit reset state (API_ID: 0x001FU)
    \param[in]  target_core: core id
                only one parameter can be selected which is shown as below:
      \arg        CORE_CM7_0: CM7_0 core
      \arg        CORE_CM7_1: CM7_1 core
    \param[out] none
    \retval     none
*/
void gd_ap_exit_reset_config(gd_ap_target_core_enum target_core)
{
    switch(target_core){
        /* CM7_0 core entry reset state  */
        case CORE_CM7_0:
            GD_AP_RST |= GD_AP_CM7_0_RST;
            break;
#if defined (GD32A72XX) || defined (GD32A74XX)
        /* CM7_1 core entry reset state  */
        case CORE_CM7_1:
            GD_AP_RST |= GD_AP_CM7_1_RST;
            break;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        default :
            break;
    }
}

/*!
    \brief      get gd_ap idcode (API_ID: 0x0020U)
    \param[in]  none
    \param[out] none
    \retval     gd ap idcode
*/
uint32_t gd_ap_idcode_value_get(void)
{
    return GD_AP_ID;
}

/*!
    \brief      get debug software access flag (API_ID: 0x0021U)
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus gd_ap_debug_software_access_state_get(void)
{
    FlagStatus ret_flag;
    if(0U != (GD_AP_AUTH_STAT & GD_AP_AUTH_STAT_SWACC)) {
        ret_flag = SET;
    } else {
        ret_flag = RESET;
    }
    return ret_flag;
}

/*!
    \brief      get gd_ap flag (API_ID: 0x0022U)
    \param[in]  flag
                only one parameter can be selected which is shown as below:
      \arg        SYSTEM_RESET_FLAG: MCU is in system reset state
      \arg        SUBSYSTEM_RESET_FLAG: MCU is in subsystem reset state
      \arg        HSM_DEBUG_CONNECT_FALG: HSM debug connect state
      \arg        HOST_DEBUG_CONNECT_FALG: HOST debug connect state
      \arg        CM7_0_HALT_FLAG: core CM7_0 is halted state
      \arg        CM7_1_HALT_FLAG: core CM7_1 is halted state
      \arg        CM23_HALT_FLAG: core CM23 is halted state
      \arg        CM7_0_DEBUG_RESTART_FLAG: core CM7_0 debug restarted state
      \arg        CM7_1_DEBUG_RESTART_FLAG: core CM7_1 debug restarted state
      \arg        CM23_DEBUG_RESTART_FLAG: core CM23 debug restarted state
    \param[out] none
    \retval     none
*/
FlagStatus gd_ap_flag_get(uint32_t flag)
{
    uint32_t ret;
    FlagStatus ret_flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_GD_AP_FLAG(flag)) {
        fw_debug_report_err(GD_AP_MODULE_ID, API_ID(0x0022U), ERR_PARAM_INVALID);
    }else
#endif
    {
        ret = GD_AP_STAT;
        if (0U != (ret & flag)){
            ret_flag = SET;
        }
    }
    return ret_flag;
}
