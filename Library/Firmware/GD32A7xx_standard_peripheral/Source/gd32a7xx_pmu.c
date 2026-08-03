/*!
    \file    gd32a7xx_pmu.c
    \brief   PMU driver

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

#include "gd32a7xx_pmu.h"

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      enable final step regulator (API_ID: 0x0001U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_run_ldo_enable(void)
{
    PMU_CFG |= PMU_CFG_FSREN;
}

/*!
    \brief      disable final step regulator (API_ID: 0x0002U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_run_ldo_disable(void)
{
    PMU_CFG &= ~PMU_CFG_FSREN;
}

/*!
    \brief      enable final step regulator auto truns over (API_ID: 0x0003U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_run_ldo_auto_switch_enable(void)
{
    PMU_CFG |= PMU_CFG_FSRATO;
}

/*!
    \brief      disable final step regulator auto truns over (API_ID: 0x0004U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_run_ldo_auto_switch_disable(void)
{
    PMU_CFG &= ~PMU_CFG_FSRATO;
}

/*!
    \brief      enable final step regulator base control (API_ID: 0x0005U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_base_control_enable(void)
{
    PMU_CFG |= PMU_CFG_FSRCTLEN;
}

/*!
    \brief      disable final step regulator base control (API_ID: 0x0006U) 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_base_control_disable(void)
{
    PMU_CFG &= ~PMU_CFG_FSRCTLEN;
}

/*!
    \brief      disable final step regulator and final step regulator base control simultaneously (API_ID: 0x0007U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_run_ldo_and_base_control_disable(void)
{
    PMU_CFG &= ~(PMU_CFG_FSREN | PMU_CFG_FSRCTLEN);
}

/*!
    \brief      enable fast recovery from LCM (API_ID: 0x0008U) 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_fast_recovery_enable(void)
{
    PMU_CFG |= PMU_CFG_FREC;
}

/*!
    \brief      disable fast recovery from LCM (API_ID: 0x0009U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_fast_recovery_disable(void)
{
    PMU_CFG &= ~PMU_CFG_FREC;
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      enable PMU LVD (API_ID(0x000aU))
    \param[in]  pmu_domain: PMU LVD domain
                only one parameter can be selected which is shown as below:
      \arg        PMU_V25_DOMAIN: V25 domain
      \arg        PMU_VDDB_DOMAIN: VDDB domain
    \param[out] none
    \retval     none
*/
void pmu_lvd_enable(uint32_t pmu_domain)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_DOMAIN(pmu_domain)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000aU), ERR_PARAM_INVALID);
    }else 
#endif
    {
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        if(PMU_V25_DOMAIN == pmu_domain){
            PMU_CFG |= PMU_CFG_V25LVRDEN;
        }else{
            PMU_CFG |= PMU_CFG_VBLVRDEN;
        }
#else
        PMU_CFG |= PMU_CFG_V25LVRDEN;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    }
}

/*!
    \brief      disable PMU LVD (API_ID(0x000bU))
    \param[in]  pmu_domain: PMU LVD domain
                only one parameter can be selected which is shown as below:
      \arg        PMU_V25_DOMAIN: V25 domain
      \arg        PMU_VDDB_DOMAIN: VDDB domain
    \param[out] none
    \retval     none
*/
void pmu_lvd_disable(uint32_t pmu_domain)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_DOMAIN(pmu_domain)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000bU), ERR_PARAM_INVALID);
    }else
#endif
    {
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        if(PMU_V25_DOMAIN == pmu_domain){
            PMU_CFG &= ~PMU_CFG_V25LVRDEN;
        }else{
            PMU_CFG &= ~PMU_CFG_VBLVRDEN;
        }
#else
        PMU_CFG &= ~PMU_CFG_V25LVRDEN;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    }
}

/*!
    \brief      enable temperature monitor (API_ID(0x000cU))
    \param[in]  temp_monitor: temperature monitor number
                only one parameter can be selected which is shown as below:
      \arg        PMU_TEMPERATURE_MONITOR_0: temperature monitor 0
      \arg        PMU_TEMPERATURE_MONITOR_1: temperature monitor 1
    \param[out] none
    \retval     none
*/
void pmu_temperature_monitor_enable(uint32_t temp_monitor)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_TEMPERATURE_MONITOR(temp_monitor)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000cU), ERR_PARAM_INVALID);
    }else
#endif
    {
        if(PMU_TEMPERATURE_MONITOR_0 == temp_monitor){
            PMU_CFG |= PMU_CFG_TEMP0EN;
        }else{
            PMU_CFG |= PMU_CFG_TEMP1EN;
        }
    }
}

/*!
    \brief      disable temperature monitor (API_ID(0x000dU))
    \param[in]  temp_monitor: temperature monitor number
                only one parameter can be selected which is shown as below:
      \arg        PMU_TEMPERATURE_MONITOR_0: temperature monitor 0
      \arg        PMU_TEMPERATURE_MONITOR_1: temperature monitor 1
    \param[out] none
    \retval     none
*/
void pmu_temperature_monitor_disable(uint32_t temp_monitor)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_TEMPERATURE_MONITOR(temp_monitor)) {
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000dU), ERR_PARAM_INVALID);
    }else
#endif
    {
        if(PMU_TEMPERATURE_MONITOR_0 == temp_monitor){
            PMU_CFG &= ~PMU_CFG_TEMP0EN;
        }else{
            PMU_CFG &= ~PMU_CFG_TEMP1EN;
        }
    }
}

/*!
    \brief      select temperature monitor threshold (API_ID(0x000eU))
    \param[in]  temp_monitor: temperature monitor number
                only one parameter can be selected which is shown as below:
      \arg        PMU_TEMPERATURE_MONITOR_0: temperature monitor 0
      \arg        PMU_TEMPERATURE_MONITOR_1: temperature monitor 1
    \param[in]  temp_level: temperature monitor threshold
                only one parameter can be selected which is shown as below:
      \arg        PMU_TEMPERATURE_LEVEL_145: temperature threshold around 145
      \arg        PMU_TEMPERATURE_LEVEL_155: temperature threshold around 155
    \param[out] none
    \retval     none
*/
void pmu_temperature_level_select(uint32_t temp_monitor, uint32_t temp_level)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_TEMPERATURE_MONITOR(temp_monitor)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000eU), ERR_PARAM_INVALID);
    }else if(NOT_PMU_TEMPERATURE_LEVEL(temp_level)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000eU), ERR_PARAM_INVALID);
    }else
#endif
    {
        if(PMU_TEMPERATURE_MONITOR_0 == temp_monitor){
            if(PMU_TEMPERATURE_LEVEL_145 == temp_level){
                PMU_CFG &= ~PMU_CFG_TEMP0SEL;
            }else{
                PMU_CFG |= PMU_CFG_TEMP0SEL;
            }
        }else{
            if(PMU_TEMPERATURE_LEVEL_145 == temp_level){
                PMU_CFG &= ~PMU_CFG_TEMP1SEL;
            }else{
                PMU_CFG |= PMU_CFG_TEMP1SEL;
            }
        }
    }
}

/*!
    \brief      set clock state when enter standby mode (API_ID(0x000fU))
    \param[in]  clk_src: clock source
                only one parameter can be selected which is shown as below:
      \arg        PMU_CLK_IRC48M: clock source is IRC48M
      \arg        PMU_CLK_IRC40K: clock source is IRC40K
    \param[in]  state: clock state in standby mode
                only one parameter can be selected which is shown as below:
      \arg        ENABLE: clock is on in standby mode
      \arg        DISABLE: clock is off in standby mode
    \param[out] none
    \retval     none
*/
void pmu_standby_clock_state_set(uint32_t clk_src, ControlStatus state)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_CLK_SOURCE(clk_src)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000fU), ERR_PARAM_INVALID);
    }else if(NOT_CONTROL_STATUS(state)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x000fU), ERR_PARAM_INVALID);
    }else
#endif
    {
        if(PMU_CLK_IRC48M == clk_src){
            if(ENABLE == state){
                PMU_CFG |= PMU_CFG_STBIRC48MCTL;
            }else{
                PMU_CFG &= ~PMU_CFG_STBIRC48MCTL;
            }
        }else{
            if(ENABLE == state){
                PMU_CFG |= PMU_CFG_STBIRC40KCTL;
            }else{
                PMU_CFG &= ~PMU_CFG_STBIRC40KCTL;
            }
        }
    }
}

/*!
    \brief      start PMU analog BIST (API_ID: 0x0010U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_analog_bist_start(void)
{
    PMU_ABCTL = PMU_ABCTL_ABEN;
}

/*!
    \brief      write PMU control key (API_ID: 0x0011U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_control_key_write(void)
{
    PMU_CTLKEY = PMU_CTL_KEY_VLE;
    PMU_CTLKEY = (~PMU_CTL_KEY_VLE) & PMU_CTLKEY_CTLKEY;
}

/*!
    \brief      enable PMU mode update (API_ID: 0x0012U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_mode_update_enable(void)
{
    PMU_MODUPD = PMU_MODUPD_MODUPD;
}


/*!
    \brief      request system reset (API_ID: 0x0013U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_system_reset_request(void)
{
    /* set system reset request */
    PMU_MODCFG |= PMU_MODCFG_SRSTR;
    /* enable mode update */
    PMU_MODUPD = PMU_MODUPD_MODUPD;
    /* write control key */
    PMU_CTLKEY = PMU_CTL_KEY_VLE;
    PMU_CTLKEY = (~PMU_CTL_KEY_VLE) & PMU_CTLKEY_CTLKEY;
}

/*!
    \brief      request subsystem reset (API_ID: 0x0014U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_subsystem_reset_request(void)
{
    /* set subsystem reset request */
    PMU_MODCFG |= PMU_MODCFG_SSRSTR;
    /* enable mode update */
    PMU_MODUPD = PMU_MODUPD_MODUPD;
    /* write control key */
    PMU_CTLKEY = PMU_CTL_KEY_VLE;
    PMU_CTLKEY = (~PMU_CTL_KEY_VLE) & PMU_CTLKEY_CTLKEY;
}

/*!
    \brief      set PMU core boot address (API_ID(0x0015U))
    \param[in]  core_id: core id
                only one parameter can be selected which is shown as below:
      \arg        PMU_CORE_ID_0: main core id 0
      \arg        PMU_CORE_ID_1: main core id 1
    \param[in]  boot_addr: boot address
    \param[out] none
    \retval     none
*/
void pmu_core_boot_address_set(uint32_t core_id, uint32_t boot_addr)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CORE_ID(core_id)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    }else
#endif
    {
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        if(PMU_CORE_ID_0 == core_id){
            PMU_C0BTADDR = boot_addr;
        }else{
            PMU_C1BTADDR = boot_addr;
        }
#else
        PMU_C0BTADDR = boot_addr;
#endif
    }
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      set PMU main core id (API_ID(0x0016U))
    \param[in]  core_id: core id
                only one parameter can be selected which is shown as below:
      \arg        PMU_CORE_ID_0: main core id 0
      \arg        PMU_CORE_ID_1: main core id 1
    \param[out] none
    \retval     none
*/
void pmu_main_core_id_set(uint32_t core_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CORE_ID(core_id)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0016U), ERR_PARAM_INVALID);
    }else
#endif
    {
        PMU_MCID = core_id;
    }
}

/*!
    \brief      get PMU main core id (API_ID: 0x0017U)
    \param[in]  none
    \param[out] none
    \retval     core id
      \arg        PMU_CORE_ID_0: main core id 0
      \arg        PMU_CORE_ID_1: main core id 1
*/
uint32_t pmu_main_core_id_get(void)
{
    uint32_t core_id;

    core_id = PMU_MCID & PMU_MCID_MCID;

    return core_id;
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      enable PMU core update (API_ID: 0x0018U) 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_core_update_enable(void)
{
    PMU_CUPD = PMU_CUPD_CUPD;
}

/*!
    \brief      pmu work in standby mode (API_ID: 0x0019U) 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_to_standbymode(void)
{
    /* set standby request */
    PMU_MODCFG |= PMU_MODCFG_STBR;
    /* enable mode update */
    PMU_MODUPD = PMU_MODUPD_MODUPD;
    /* write control key */
    PMU_CTLKEY = PMU_CTL_KEY_VLE;
    PMU_CTLKEY = (~PMU_CTL_KEY_VLE) & PMU_CTLKEY_CTLKEY;

    /* reset wakeup flag */
    PMU_LVCS = PMU_LVCS_PORF;

    /* set sleepdeep bit of Cortex-M7 system control register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* select WFI or WFE command to enter standby mode */
    __WFI();
}

/*!
    \brief      get previous mode (API_ID: 0x001aU)
    \param[in]  none
    \param[out] none
    \retval     previous mode
      \arg        PMU_PRE_MODE_RESET: previous mode was reset (any reset)
      \arg        PMU_PRE_MODE_STANDBY: previous mode was standby mode
*/
uint32_t pmu_previous_mode_get(void)
{
    uint32_t mode;
    
    mode = PMU_MODSTAT & PMU_MODSTAT_PREMOD;
    
    return mode;
}

/*!
    \brief      enable write access to the registers in backup domain (API_ID: 0x001bU) 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_enable(void)
{
    PMU_CTL |= PMU_CTL_BKPWEN;
}

/*!
    \brief      disable write access to the registers in backup domain (API_ID: 0x001cU) 
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_backup_write_disable(void)
{
    PMU_CTL &= ~PMU_CTL_BKPWEN;
}

/*!
    \brief      clear all LVCS register flags (API_ID: 0x001dU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pmu_all_flags_clear(void)
{
    PMU_LVCS = (uint32_t)0xFFFFFFFFU;
}

/*!
    \brief      get PMU flag (API_ID(0x001eU))
    \param[in]  flag: the pmu flag bits
                only one parameter can be selected which are shown as below:
      \arg        PMU_FLAG_VAHVDF: VDDA domain HVD flag
      \arg        PMU_FLAG_VBHVDF: VDDB domain HVD flag
      \arg        PMU_FLAG_V25HVDF: V25 domain HVD flag 
      \arg        PMU_FLAG_V11HVDF: V11 domain HVD flag 
      \arg        PMU_FLAG_V5ALVDF: VDDA domain 5V LVD flag
      \arg        PMU_FLAG_V15LVDF: V15 domain LVD flag
      \arg        PMU_FLAG_TMP0IF: temperature monitor 0 interrupt flag 
      \arg        PMU_FLAG_TMP1IF: temperature monitor 1 interrupt flag 
      \arg        PMU_FLAG_VAHVDSF: VDDA domain HVD status flag
      \arg        PMU_FLAG_VBHVDSF: VDDB domain HVD status flag
      \arg        PMU_FLAG_V25HVDSF: V25 domain HVD status flag 
      \arg        PMU_FLAG_V11HVDSF: V11 domain HVD status flag 
      \arg        PMU_FLAG_V5ALVDSF: VDDA domain 5V LVD status flag
      \arg        PMU_FLAG_V15LVDSF: V15 domain LVD status flag
      \arg        PMU_FLAG_TPM0OF: temperature monitor 0 output flag
      \arg        PMU_FLAG_TPM1OF: temperature monitor 1 output flag
      \arg        PMU_FLAG_VALVRNF: VDDA domain LVR NCM flag 
      \arg        PMU_FLAG_VALVRNLF: VDDA domain LVR NCM or LCM flag  
      \arg        PMU_FLAG_VBLVRNF: VDDB domain LVR NCM flag 
      \arg        PMU_FLAG_VBLVRNLF: VDDB domain LVR NCM or LCM flag 
      \arg        PMU_FLAG_V25LVRNF: V25 domain LVR NCM flag 
      \arg        PMU_FLAG_V25LVRNLF: V25 domain LVR NCM or LCM flag 
      \arg        PMU_FLAG_V11LVRNF: V11 domain LVR NCM flag  
      \arg        PMU_FLAG_V11LVRNLF: V11 domain LVR NCM or LCM flag  
      \arg        PMU_FLAG_V15HVDF: V15 domain HVD flag 
      \arg        PMU_FLAG_V15HVDSF: V15 domain HVD status flag 
      \arg        PMU_FLAG_IRC48MSTBF: IRC48M stabilization status flag 
      \arg        PMU_FLAG_IRC40KSTBF: IRC40K stabilization status flag 
      \arg        PMU_FLAG_PORF: POR flag
      \arg        PMU_FLAG_FSRSF: final step regulator status flag
      \arg        PMU_FLAG_V11RUNABF: V11 run ABIST test flag 
      \arg        PMU_FLAG_V11STBABF: V11 standby ABIST test flag 
      \arg        PMU_FLAG_V25ABF: V25 ABIST test flag
      \arg        PMU_FLAG_VAABF: VDDA ABIST test flag
      \arg        PMU_FLAG_VBABF: VDDB ABIST test flag
      \arg        PMU_FLAG_TEMP0ABF: high temperature 0 flag
      \arg        PMU_FLAG_TEMP1ABF: high temperature 1 flag
      \arg        PMU_FLAG_HVDV11ABF: HVD V11 ABIST test flag
      \arg        PMU_FLAG_HVDV25ABF: HVD V25 ABIST test flag
      \arg        PMU_FLAG_HVDVAABF: HVD VDDA ABIST test flag
      \arg        PMU_FLAG_HVDVBABF: HVD VDDB ABIST test flag
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus pmu_flag_get(pmu_flag_enum flag)
{
    FlagStatus status ;

    if(0U != (PMU_REG_VAL(flag) & BIT(PMU_BIT_POS(flag)))){
        status = SET;
    } else {
        status = RESET;
    }
    
    return status;
}

/*!
    \brief      clear PMU flag (API_ID(0x001fU))
    \param[in]  flag: the pmu flag bits
                only one parameter can be selected which are shown as below:
      \arg        PMU_FLAG_VAHVDF: VDDA domain HVD flag
      \arg        PMU_FLAG_VBHVDF: VDDB domain HVD flag
      \arg        PMU_FLAG_V25HVDF: V25 domain HVD flag 
      \arg        PMU_FLAG_V11HVDF: V11 domain HVD flag 
      \arg        PMU_FLAG_V5ALVDF: VDDA domain 5V LVD flag
      \arg        PMU_FLAG_TMP0IF: temperature monitor 0 interrupt flag 
      \arg        PMU_FLAG_TMP1IF: temperature monitor 1 interrupt flag 
      \arg        PMU_FLAG_V15LVDF: V15 domain LVD flag
      \arg        PMU_FLAG_VALVRNF: VDDA domain LVR NCM flag 
      \arg        PMU_FLAG_VALVRNLF: VDDA domain LVR NCM or LCM flag  
      \arg        PMU_FLAG_VBLVRNF: VDDB domain LVR NCM flag 
      \arg        PMU_FLAG_VBLVRNLF: VDDB domain LVR NCM or LCM flag 
      \arg        PMU_FLAG_V25LVRNF: V25 domain LVR NCM flag 
      \arg        PMU_FLAG_V25LVRNLF: V25 domain LVR NCM or LCM flag 
      \arg        PMU_FLAG_V11LVRNF: V11 domain LVR NCM flag  
      \arg        PMU_FLAG_V11LVRNLF: V11 domain LVR NCM or LCM flag  
      \arg        PMU_FLAG_V15HVDF: V15 domain HVD flag 
      \arg        PMU_FLAG_PORF: VDDA domain HVD flag
      \arg        PMU_FLAG_FSRSF: final step regulator status flag
      \arg        PMU_FLAG_V11RUNABF: V11 run ABIST test flag 
      \arg        PMU_FLAG_V11STBABF: V11 standby ABIST test flag 
      \arg        PMU_FLAG_V25ABF: V25 ABIST test flag
      \arg        PMU_FLAG_VAABF: VDDA ABIST test flag
      \arg        PMU_FLAG_VBABF: VDDB ABIST test flag
      \arg        PMU_FLAG_TEMP0ABF: high temperature 0 flag
      \arg        PMU_FLAG_TEMP1ABF: high temperature 1 flag
      \arg        PMU_FLAG_HVDV11ABF: HVD V11 ABIST test flag
      \arg        PMU_FLAG_HVDV25ABF: HVD V25 ABIST test flag
      \arg        PMU_FLAG_HVDVAABF: HVD VDDA ABIST test flag
      \arg        PMU_FLAG_HVDVBABF: HVD VDDB ABIST test flag
    \param[out] none
    \retval     none
*/
void pmu_flag_clear(pmu_flag_enum flag)
{
    PMU_REG_VAL(flag) = BIT(PMU_BIT_POS(flag));
}

/*!
    \brief      get PMU interrupt flag (API_ID(0x0020U))
    \param[in]  int_flag: the pmu interrupt flag bits
                only one parameter can be selected which are shown as below:
      \arg        PMU_INT_FLAG_VAHVD : VDDA domain HVD interrupt flag
      \arg        PMU_INT_FLAG_VBHVD : VDDB domain HVD interrupt flag
      \arg        PMU_INT_FLAG_V25HVD: V25 domain HVD interrupt flag 
      \arg        PMU_INT_FLAG_V11HVD: V11 domain HVD interrupt flag 
      \arg        PMU_INT_FLAG_V15HVD: V15 domain HVD interrupt flag 
      \arg        PMU_INT_FLAG_V5ALVD: VDDA domain 5V LVD interrupt flag
      \arg        PMU_INT_FLAG_V15LVD: V15 domain LVD interrupt flag
      \arg        PMU_INT_FLAG_TMP0: temperature monitor 0 interrupt flag
      \arg        PMU_INT_FLAG_TMP1: temperature monitor 1 interrupt flag
    \param[out] none
    \retval     FlagStatus: status of flag (RESET or SET)
*/
FlagStatus pmu_interrupt_flag_get(uint32_t int_flag)
{
    FlagStatus status = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_INTERRUPT(int_flag)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0020U), ERR_PARAM_INVALID);
    }else
#endif
    {
        if(0U != (PMU_LVCS & int_flag)){
            status = SET;
        } else {
            status = RESET;
        }
    }
    
    return status;
}

/*!
    \brief      clear PMU interrupt flag (API_ID(0x0021U))
    \param[in]  int_flag: the pmu interrupt flag bits
                only one parameter can be selected which are shown as below:
      \arg        PMU_INT_FLAG_VAHVD : VDDA domain HVD interrupt flag
      \arg        PMU_INT_FLAG_VBHVD : VDDB domain HVD interrupt flag
      \arg        PMU_INT_FLAG_V25HVD: V25 domain HVD interrupt flag 
      \arg        PMU_INT_FLAG_V11HVD: V11 domain HVD interrupt flag 
      \arg        PMU_INT_FLAG_V15HVD: V15 domain HVD interrupt flag 
      \arg        PMU_INT_FLAG_V5ALVD: VDDA domain 5V LVD interrupt flag
      \arg        PMU_INT_FLAG_V15LVD: V15 domain LVD interrupt flag
      \arg        PMU_INT_FLAG_TMP0: temperature monitor 0 interrupt flag
      \arg        PMU_INT_FLAG_TMP1: temperature monitor 1 interrupt flag
    \param[out] none
    \retval     none
*/
void pmu_interrupt_flag_clear(uint32_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_INTERRUPT(int_flag)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0021U), ERR_PARAM_INVALID);
    }else
#endif
    {
        PMU_LVCS = int_flag;
    }
}

/*!
    \brief      enable the PMU interrupt (API_ID(0x0022U))
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which are shown as below:
      \arg        PMU_INT_HVD: high voltage detect interrupt
      \arg        PMU_INT_LVD: low voltage detect interrupt
      \arg        PMU_INT_TMP: temperature monitor detect interrupt
    \param[out] none
    \retval     none
*/
void pmu_interrupt_enable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_INTERRUPT_ENABLE(interrupt)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0022U), ERR_PARAM_INVALID);
    }else
#endif
    {
        PMU_CFG |= interrupt;
    }
}

/*!
    \brief      disable the PMU interrupt (API_ID(0x0023U))
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which are shown as below:
      \arg        PMU_INT_HVD: high voltage detect interrupt
      \arg        PMU_INT_LVD: low voltage detect interrupt
      \arg        PMU_INT_TMP: temperature monitor detect interrupt
    \param[out] none
    \retval     none
*/
void pmu_interrupt_disable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_PMU_INTERRUPT_ENABLE(interrupt)){
        fw_debug_report_err(PMU_MODULE_ID, API_ID(0x0023U), ERR_PARAM_INVALID);
    }else
#endif
    {
        PMU_CFG &= ~interrupt;
    }
}

