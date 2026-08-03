/*!
    \file    gd32a7xx_cltcfg.c
    \brief   CLTCFG driver

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

#include "gd32a7xx_cltcfg.h"

#define ADC_CH_OFFSET                             (16U)
#define ADC_PIN_MASK                              ((uint32_t)0x0000067EU)
#define CORE_WAIT_OFFSET                          (16U)
#define CORE_WAIT_MASK                            ((uint32_t)0x00060000U)
#define BOOT_ADREESS_OFFSET                       (1U)
#define CLTCFG_LC_MASK                            ((uint32_t)0x00000007U)

/*!
    \brief      get PMU input isolation state
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: RESET or SET
*/
FlagStatus cltcfg_iso_state_get(void)
{
    uint32_t reg;
    FlagStatus state;

    /* get the value of CLTCFG_SR_STAT0 register */
    reg = CLTCFG_SR_STAT0;

    if(0U != (CLTCFG_SR_STAT0_ISO_STAT & reg)) {
        /* input isolation is in active state */
        state = SET;
    }else{
        /* input isolation is in inactive state */
        state = RESET;
    }

    return state;
}

/*!
    \brief      clear PMU input isolation state 
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus cltcfg_iso_state_clear(void)
{
    uint32_t reg;
    ErrStatus state;

    /* get the value of CLTCFG_SR_STAT0 register */
    reg = CLTCFG_SR_STAT0;

    if(0U != (CLTCFG_SR_STAT0_ISO_STAT & reg)) {
        /* write 1 to clear CLTCFG_SR_STAT0_ISO_STAT bit */
        CLTCFG_SR_STAT0 |= CLTCFG_SR_STAT0_ISO_STAT;

        /* get the value of CLTCFG_SR_STAT0 register again */
        reg = CLTCFG_SR_STAT0;
        /* check CLTCFG_SR_STAT0_ISO_STAT is cleared */
        if(0U != (CLTCFG_SR_STAT0_ISO_STAT & reg)) {
            state = ERROR;
        }else{
            state = SUCCESS;
        }
    }else{
        /* PMU input isolation state does not need to be cleared */
        state = SUCCESS;
    }

    return state;
}

/*!
    \brief      get reset pin mode
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: RESET or SET
*/
FlagStatus cltcfg_reset_pin_mode_get(void)
{
    uint32_t reg;
    FlagStatus state;

    /* get the value of CLTCFG_SR_STAT1 register */
    reg = CLTCFG_SR_STAT1;

    if(0U != (CLTCFG_SR_STAT1_RSTPIN_MOD & reg)) {
        /* reset pin acts as dedicated */
        state = SET;
    }else{
        /* reset pin acts as general GPIO pin multiplexed with non-reset function */
        state = RESET;
    }

    return state;
}

/*!
    \brief      get fatal fault IO mode
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: RESET or SET
*/
FlagStatus cltcfg_ffio_mode_get(void)
{
    uint32_t reg;
    FlagStatus state;

    /* get the value of CLTCFG_SR_STAT2 register */
    reg = CLTCFG_SR_STAT2;

    if(0U != (CLTCFG_SR_STAT2_FFIOMOD & reg)) {
        /* FFIO[0] and FFIO[1] acts as dedicated fatal fault reaction pins */
        state = SET;
    }else{
        /* FFIO[0] and FFIO[1] acts as general GPIO pins */
        state = RESET;
    }

    return state;
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      get the specified ENET DMA transfer channel state
    \param[in]  channel: ENET DMA channel
                only one parameter can be selected which is shown as below:
      \arg        ENET_CH0: channel 0
      \arg        ENET_CH1: channel 1
    \param[out] none
    \retval     FlagStatus: RESET or SET
*/
FlagStatus cltcfg_enet_ch_state_get(enet_ch_enum channel)
{
    uint32_t reg;
    FlagStatus state = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_CHANNEL(channel)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_SUBSR_STAT0 register */
        reg = CLTCFG_SUBSR_STAT0;

        if(0U != ((uint32_t)channel & reg)) {
            state = SET;
        }else {
            state = RESET;
        }
    }

    return state;
}

/*!
    \brief      clear the specified ENET DMA transfer channel state
    \param[in]  channel: ENET DMA channel
                only one parameter can be selected which is shown as below:
      \arg        ENET_CH0: channel 0
      \arg        ENET_CH1: channel 1
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus cltcfg_enet_ch_state_clear(enet_ch_enum channel)
{
    uint32_t reg;
    ErrStatus state = ERROR;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_CHANNEL(channel)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_SUBSR_STAT0 register */
        reg = CLTCFG_SUBSR_STAT0;

        if(0U != ((uint32_t)channel & reg)) {
            /* write 1 to clear state bit */
            reg = (uint32_t)channel;
            CLTCFG_SUBSR_STAT0 = reg;

            /* read back the value of CLTCFG_SUBSR_STAT0 register */
            reg = CLTCFG_SUBSR_STAT0;
            if(0U != ((uint32_t)channel & reg)) {
                state = ERROR;
            }else{
                state = SUCCESS;
            }
        }else {
            /* no need write clear, cause this bit is already cleared */
            state = SUCCESS;
        }
    }

    return state;
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      get the power watch dog state
    \param[in]  none
    \param[out] none
    \retval     ControlStatus: DISABLE or ENABLE
*/
ControlStatus cltcfg_porwdg_status_get(void)
{
    uint32_t reg;
    ControlStatus state;

    /* get the value of CLTCFG_SUBSR_STAT1 register */
    reg = CLTCFG_SUBSR_STAT1;

    if(0U != (CLTCFG_SUBSR_STAT1_PWDGEN_STAT & reg)) {
        state = ENABLE;
    } else {
        state = DISABLE;
    }

    return state;
}

/*!
    \brief      get the final-step regulator state
    \param[in]  none
    \param[out] none
    \retval     ControlStatus: DISABLE or ENABLE
*/
ControlStatus cltcfg_fs_status_get(void)
{
    uint32_t reg;
    ControlStatus state;

    /* get the value of CLTCFG_SUBSR_STAT1 register */
    reg = CLTCFG_SUBSR_STAT1;

    if(0U != (CLTCFG_SUBSR_STAT1_FSRDIS_STAT & reg)) {
        state = DISABLE;
    } else {
        state = ENABLE;
    }

    return state;
}

/*!
    \brief      get the system reset upgrade state
    \param[in]  sysrst_ug: system reset resource of upgrade function
                only one parameter can be selected which is shown as below:
      \arg        FMU_REA_FAIL_UPGRADE   : the upgrade function of FMU_REA_FAIL reset
      \arg        STCM_REC_FAIL_UPGRADE  : the upgrade function of STCM_REC_FAIL reset
      \arg        RCTL_SBSRU_UPGRADE     : the upgrade function of RCTL_SBSRU reset
      \arg        LOHRST_UPGRADE         : the upgrade function of LOHRST reset
      \arg        LOPRST_UPGRADE         : the upgrade function of LOPRST reset
      \arg        HSM_SYS_RST_UPGRADE    : the upgrade function of HSM_SYS_RST reset
      \arg        SW_SYS_RST_UPGRADE     : the upgrade function of SW_SYS_RST reset
      \arg        DBG_SYS_RST_UPGRADE    : the upgrade function of DBG_SYS_RST reset
    \param[out] none
    \retval     FlagStatus: RESET or SET
*/
FlagStatus cltcfg_sysrst_upgrade_get(srug_enum sysrst_ug)
{
    uint32_t reg;
    uint32_t temp_0;
    uint32_t temp_1;
    FlagStatus state = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SRUG_RESOURCE(sysrst_ug)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_SUBSR_STAT1 register */
        temp_0 = (CLTCFG_SUBSR_STAT1 & CLTCFG_SUBSR_STAT1_SRUG);
        /* get the value of CLTCFG_SUBSR_STAT2 register */
        temp_1 = (CLTCFG_SUBSR_STAT2 & CLTCFG_SUBSR_STAT2_SRUG);

        reg = (temp_0 | temp_1);
        if(0U != (((uint32_t)sysrst_ug) & reg)) {
            state = SET;
        } else {
            state = RESET;
        }
    }

    return state;
}

/*!
    \brief      configure the clock out function availability
    \param[in]  config: clock out configuration
                only one parameter can be selected which is shown as below:
      \arg        CKOUT1_NOT_AVAILABLE   : The CKOUT1 function is not available while system reset or subsystem reset on PM4
      \arg        CKOUT1_AVAILABLE       : The CKOUT1 function is available while system reset or subsystem reset on PM4
    \param[out] none
    \retval     none
*/
void cltcfg_ckout_standby_config(ckout_valid_enum config)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CKOUT_CONFIG(config)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_POR_CTL0 register */
        reg = CLTCFG_POR_CTL0;

        if(CKOUT1_NOT_AVAILABLE == config) {
            reg &= (~CLTCFG_POR_CTL0_CKOUT1_CFG);
            CLTCFG_POR_CTL0 = reg;
        } else {
            reg |= CLTCFG_POR_CTL0_CKOUT1_CFG;
            CLTCFG_POR_CTL0 = reg;
        }
    }
}

/*!
    \brief      enable the the power watchdog monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_porwdg_monitor_enable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_POR_CTL0 register */
    reg = CLTCFG_POR_CTL0;

    /* enable the the power watchdog monitor */
    reg &= (~CLTCFG_POR_CTL0_PWD_MONDIS);
    CLTCFG_POR_CTL0 = reg;
}

/*!
    \brief      disable the the power watchdog monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_porwdg_monitor_disable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_POR_CTL0 register */
    reg = CLTCFG_POR_CTL0;

    /* disable the the power watchdog monitor */
    reg |= CLTCFG_POR_CTL0_PWD_MONDIS;
    CLTCFG_POR_CTL0 = reg;
}

/*!
    \brief      power watchdog timeout value configuration
    \param[in]  porwdg_timeout_enum: timeout value
                only one parameter can be selected which is shown as below:
      \arg      POR_WDG_TIMEOUT_06_25: power watchdog timeout value = 06.25ms
      \arg      POR_WDG_TIMEOUT_12_50: power watchdog timeout value = 12.50ms
      \arg      POR_WDG_TIMEOUT_25_00: power watchdog timeout value = 25.00ms
      \arg      POR_WDG_TIMEOUT_50_00: power watchdog timeout value = 50.00ms
    \param[out] none
    \retval     none
*/
void cltcfg_porwdg_timeout_config(porwdg_timeout_enum timeout)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TIMEOUT_VALUE(timeout)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_POR_CTL0 register */
        reg = CLTCFG_POR_CTL0;

        /* clear bits[10:9] */
        reg &= (~CLTCFG_POR_CTL0_PWDTO);

        reg |= (uint32_t)timeout;
        CLTCFG_POR_CTL0 = reg;
    }
}

/*!
    \brief      enable the FMU monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_fmu_monitor_enable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_POR_CTL1 register */
    reg = CLTCFG_POR_CTL1;

    reg &= (~CLTCFG_POR_CTL1_FMU_MONDIS);
    CLTCFG_POR_CTL1 = reg;
}

/*!
    \brief      disable the FMU monitor
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_fmu_monitor_disable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_POR_CTL1 register */
    reg = CLTCFG_POR_CTL1;

    reg |= CLTCFG_POR_CTL1_FMU_MONDIS;
    CLTCFG_POR_CTL1 = reg;
}

/*!
    \brief      configure whether to generate an interrupt or a reset after PLL loss of lock event occurs
    \param[in]  config: configuration of PLL loss of lock event
                only one parameter can be selected which is shown as below:
      \arg      GENERATE_A_SYS_RST: generate a system reset if PLL loss of lock event occurs
      \arg      GENERATE_AN_INT   : generate an interrupt if PLL loss of lock event occurs
    \param[out] none
    \retval     none
*/
void cltcfg_pll_lol_config(lol_cfg_enum config)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LOL_CONFIG(config)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_POR_CTL1 register */
        reg = CLTCFG_POR_CTL1;

        /* clear bit9 */
        reg &= (~CLTCFG_POR_CTL1_LOLINT_CFG);

        reg |= (uint32_t)config;

        CLTCFG_POR_CTL1 = reg;
    }
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      enable slow trace over subsystem reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_slow_trace_enable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_SR_CTL0 register */
    reg = CLTCFG_SR_CTL0;

    reg |= CLTCFG_SR_CTL0_STOSSREN;

    CLTCFG_SR_CTL0 = reg;
}

/*!
    \brief      disable slow trace over subsystem reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_slow_trace_disable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_SR_CTL0 register */
    reg = CLTCFG_SR_CTL0;

    reg &= (~CLTCFG_SR_CTL0_STOSSREN);

    CLTCFG_SR_CTL0 = reg;
}

/*!
    \brief      enable fast trace over subsystem reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_fast_trace_enable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_SR_CTL0 register */
    reg = CLTCFG_SR_CTL0;

    reg |= CLTCFG_SR_CTL0_FTOSSREN;

    CLTCFG_SR_CTL0 = reg;
}

/*!
    \brief      disable fast trace over subsystem reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_fast_trace_disable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_SR_CTL0 register */
    reg = CLTCFG_SR_CTL0;

    reg &= (~CLTCFG_SR_CTL0_FTOSSREN);

    CLTCFG_SR_CTL0 = reg;
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      configure the fault reaction state during selftest
    \param[in]  state: configuration of the FFIO
                only one parameter can be selected which is shown as below:
      \arg      CHANGE_TO_HIGH_Z_STATE: FFIO will change to high Z during selftest when device is under reset
      \arg      REMAIN_IN_FAULT_STATE : FFIO will remain in fault state during selftest when device is under reset
    \param[out] none
    \retval     none
*/
void cltcfg_fault_reaction_config(ffio_state_enum state)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_FFIO_CONFIG(state)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_SR_CTL1 register */
        reg = CLTCFG_SR_CTL1;

        /* clear bit7 */
        reg &= (~CLTCFG_SR_CTL1_FRCFG);

        reg |= (uint32_t)state;

        CLTCFG_SR_CTL1 = reg;
    }
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      select the ENET mode
    \param[in]  mode: ENET mode
                only one parameter can be selected which is shown as below:
      \arg      ENET_MII_MODE  : mii mode
      \arg      ENET_RMII_MODE : rmii mode
    \param[out] none
    \retval     none
*/
void cltcfg_enet_mode_select(enet_mode_enum mode)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_MODE(mode)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0016U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_SUBSR_CTL0 register */
        reg = CLTCFG_SUBSR_CTL0;

        /* clear bit7 */
        reg &= (~CLTCFG_SUBSR_CTL0_ENET_MODE_SEL);

        reg |= (uint32_t)mode;

        CLTCFG_SUBSR_CTL0 = reg;
    }
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      enable IO retaing function before standy entry
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_io_retain_enable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_SUBSR_CTL0 register */
    reg = CLTCFG_SUBSR_CTL0;

    reg &= (~CLTCFG_SUBSR_CTL0_PAD_RET_CFG);

    CLTCFG_SUBSR_CTL0 = reg;
}

/*!
    \brief      disable IO retaing function after standy exit
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_io_retain_disable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_SUBSR_CTL0 register */
    reg = CLTCFG_SUBSR_CTL0;

    reg |= CLTCFG_SUBSR_CTL0_PAD_RET_CFG;

    CLTCFG_SUBSR_CTL0 = reg;
}

/*!
    \brief      ADC channel pin selection
    \param[in]  pin_sel: select drive pin
                only one parameter can be selected which is shown as below:
      \arg      ADC0_CH8_DP_PC6  : ADC0 CH8 selects the PC6 as drive pin
      \arg      ADC0_CH8_DP_PD13 : ADC0 CH8 selects the PD13 as drive pin

      \arg      ADC0_CH9_DP_PG7  : ADC0 CH9 selects the PG7 as drive pin
      \arg      ADC0_CH9_DP_PD11 : ADC0 CH9 selects the PD11 as drive pin

      \arg      ADC1_CH14_DP_PA15: ADC1 CH14 selects the PA15 as drive pin
      \arg      ADC1_CH14_DP_PJ5 : ADC1 CH14 selects the PJ5 as drive pin

      \arg      ADC1_CH15_DP_PA13: ADC1 CH15 selects the PA13 as drive pin
      \arg      ADC1_CH15_DP_PB11: ADC1 CH15 selects the PB11 as drive pin

      \arg      ADC1_CH22_DP_PG6 : ADC1 CH22 selects the PG6 as drive pin
      \arg      ADC1_CH22_DP_PA9 : ADC1 CH22 selects the PA9 as drive pin

      \arg      ADC1_CH23_DP_PG8 : ADC1 CH23 selects the PG8 as drive pin
      \arg      ADC1_CH23_DP_PA11: ADC1 CH23 selects the PA11 as drive pin

      \arg      ADC2_CH8_DP_PL2  : ADC2 CH8 selects the PL2 as drive pin
      \arg      ADC2_CH8_DP_PD13 : ADC2 CH8 selects the PD13 as drive pin
      \note     ADC2_CH8_DP_PL2 and ADC2_CH8_DP_PD13 are only for GD32A714Axx/A72xAxx/A74xAxx devices

      \arg      ADC2_CH9_DP_PC13 : ADC2 CH9 selects the PC13 as drive pin
      \arg      ADC2_CH9_DP_PD11 : ADC2 CH9 selects the PD11 as drive pin
      \note     ADC2_CH9_DP_PC13 and ADC2_CH9_DP_PD11 are only for GD32A714Axx/A72xAxx/A74xAxx devices
    \param[out] none
    \retval     none
*/
void cltcfg_adc_drive_pin_select(drive_pin_enum pin_sel)
{
    uint32_t reg;
    uint32_t adc_ch;
    uint32_t pin;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ADC_DRIVE_PIN(pin_sel)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0019U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_SUBSR_CTL1 register */
        reg = CLTCFG_SUBSR_CTL1;

        adc_ch = (uint32_t)pin_sel >> ADC_CH_OFFSET;
        pin = (uint32_t)pin_sel & ADC_PIN_MASK;

        /* clear the specified ADC channel drive pin bit  */
        reg &= (~adc_ch);
        /* write drive pin configuration */
        reg |= pin;

        CLTCFG_SUBSR_CTL1 = reg;
    }
}

/*!
    \brief      configure CM7 core wait mode
    \param[in]  config: configuration for CM7 core wait mode
                only one parameter can be selected which is shown as below:
      \arg      CORE_0_WAIT_DIS: disable CM7 core 0 wait mode
      \arg      CORE_0_WAIT_EN:  put CM7 core 0 into wait mode by CPUWAIT

      \arg      CORE_1_WAIT_DIS: disable CM7 core 1 wait mode
      \arg      CORE_1_WAIT_EN:  put CM7 core 1 into wait mode by CPUWAIT
      \note     CORE_1_WAIT_DIS and CORE_1_WAIT_EN are only for GD32A714Axx/A72xAxx/A74xAxx devices
    \param[out] none
    \retval     none
*/
void cltcfg_core_wait_mode_config(wait_mode_enum config)
{
    uint32_t reg;
    uint32_t core;
    uint32_t wait_mode;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_WAIT_MODE_CONFIG(config)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x001AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_SUBSR_CTL1 register */
        reg = CLTCFG_SUBSR_CTL1;

        core = (uint32_t)config & CORE_WAIT_MASK;
        wait_mode = (uint32_t)config << CORE_WAIT_OFFSET;

        /* clear the specified core bit */
        reg &= (~core);
        /* write wait mode configuration */
        reg |= wait_mode;

        CLTCFG_SUBSR_CTL1 = reg;
    }
}

/*!
    \brief      configure boot mode
    \param[in]  mode: boot mode
                only one parameter can be selected which is shown as below:
      \arg      NORMAL_BOOT_MODE: normal boot mode
      \arg      FAST_BOOT_MODE: fast boot mode
    \param[out] none
    \retval     none
*/
void cltcfg_boot_mode_config(boot_mode_enum mode)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BOOT_MODE(mode)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x001BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_SUBSR_CTL2 register */
        reg = CLTCFG_SUBSR_CTL2;

        /* clear the boot mode bit and write configuration */
        reg &= (~CLTCFG_SUBSR_CTL2_BTMOD);
        reg |= (uint32_t)mode;

        CLTCFG_SUBSR_CTL2 = reg;
    }
}

/*!
    \brief      configure boot address after exiting from standby
    \param[in]  boot_addr: SBAF application boot address after standby exit
    \param[out] none
    \retval     none
*/
void cltcfg_boot_address_config(uint32_t boot_addr)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_FAST_BOOT_ADDR(boot_addr)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x001CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = (uint32_t)(boot_addr << BOOT_ADREESS_OFFSET);

        CLTCFG_SUBSR_CTL2 = reg;
    }
}

/*!
    \brief      enable the triple modular redundancy function of specified modul
    \param[in]  modul: the specified modul
                only one parameter can be selected which is shown as below:
      \arg      TMR_GPIO        : gpio tmr
      \arg      TMR_SYSTEM_RESET: system reset tmr
      \arg      TMR_BOOT_MODE   : boot mode tmr
      \arg      TMR_WAIT_MODE   : wait mode tmr
      \arg      TMR_STANDBY_MODE: standby mode tmr
      \arg      TMR_WATCHDOG    : watchdog tmr
    \param[out] none
    \retval     none
*/
void cltcfg_tmr_enable(tmr_modul_enum modul)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TMR_MODUL(modul)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x001DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_TMR_CTL register */
        reg = CLTCFG_TMR_CTL;

        reg |= (uint32_t)modul;

        CLTCFG_TMR_CTL = reg;
    }
}

/*!
    \brief      disable the triple modular redundancy function of specified modul
    \param[in]  modul: the specified modul
                only one parameter can be selected which is shown as below:
      \arg      TMR_GPIO        : gpio tmr
      \arg      TMR_SYSTEM_RESET: system reset tmr
      \arg      TMR_BOOT_MODE   : boot mode tmr
      \arg      TMR_WAIT_MODE   : wait mode tmr
      \arg      TMR_STANDBY_MODE: standby mode tmr
      \arg      TMR_WATCHDOG    : watchdog tmr
    \param[out] none
    \retval     none
*/
void cltcfg_tmr_disable(tmr_modul_enum modul)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TMR_MODUL(modul)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x001EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_TMR_CTL register */
        reg = CLTCFG_TMR_CTL;

        reg &= ~((uint32_t)modul);

        CLTCFG_TMR_CTL = reg;
    }
}

/*!
    \brief      get the triple modular redundancy error flag of specified modul
    \param[in]  err_flag: the tmr error flag
                only one parameter can be selected which is shown as below:
      \arg      TMR_FLAG_IOTMRERR: gpio tmr error flag
      \arg      TMR_FLAG_SRTMRERR: system reset tmr error flag
      \arg      TMR_FLAG_BTTMRERR: boot mode tmr error flag
      \arg      TMR_FLAG_WMTMRERR: wait mode tmr error flag
      \arg      TMR_FLAG_SBTMRERR: standby mode tmr error flag
      \arg      TMR_FLAG_WDTMRERR: watchdog tmr error flag
    \param[out] none
    \retval     FlagStatus: RESET or SET
*/
FlagStatus cltcfg_tmr_error_flag_get(tmr_err_enum err_flag)
{
    uint32_t reg;
    FlagStatus state = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TMR_ERR_FLAG(err_flag)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x001FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the value of CLTCFG_TMR_STAT register */
        reg = CLTCFG_TMR_STAT;

        if(0U != (reg & (uint32_t)err_flag)) {
            state = SET;
        } else {
            state = RESET;
        }
    }

    return state;
}

/*!
    \brief      clear the triple modular redundancy error flag of specified modul
    \param[in]  err_flag: the tmr error flag
                only one parameter can be selected which is shown as below:
      \arg      TMR_FLAG_IOTMRERR: gpio tmr error flag
      \arg      TMR_FLAG_SRTMRERR: system reset tmr error flag
      \arg      TMR_FLAG_BTTMRERR: boot mode tmr error flag
      \arg      TMR_FLAG_WMTMRERR: wait mode tmr error flag
      \arg      TMR_FLAG_SBTMRERR: standby mode tmr error flag
      \arg      TMR_FLAG_WDTMRERR: watchdog tmr error flag
    \param[out] none
    \retval     none
*/
void cltcfg_tmr_error_flag_clear(tmr_err_enum err_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TMR_ERR_FLAG(err_flag)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0020U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear the specified error flag */
        CLTCFG_TMR_FC = (uint32_t)err_flag;
    }
}

/*!
    \brief      get current chip life cycle
    \param[in]  none
    \param[out] none
    \retval     lc_enum: life cycle state
      \arg        LC_FA               : failure analysis
      \arg        LC_UNKNOWN_STATE    : unknown life cycle state
      \arg        LC_OEM_PRODUCTION   : OEM production
      \arg        LC_CUSTOMER_DELIVERY: customer delivery
      \arg        LC_GD_PRODUCTION    : GD production
      \arg        LC_IN_FIELD         : in field
*/
lc_enum cltcfg_current_lc_get(void)
{
    uint32_t reg;
    lc_enum lc = LC_UNKNOWN_STATE;

    /* get the value of CLCS fields in CLTCFG_LC_CS register */
    reg = (uint32_t)CLTCFG_LC_CS;
    reg &= CLTCFG_LC_MASK;

    switch(reg) {
    /* the chip current life cycle is FA */
    case LC_FA:
        lc = LC_FA;
        break;
    /* the chip current life cycle is OEM_PRODUCTION */
    case LC_OEM_PRODUCTION:
        lc = LC_OEM_PRODUCTION;
        break;
    /* the chip current life cycle is CUSTOMER_DELIVERY */
    case LC_CUSTOMER_DELIVERY:
        lc = LC_CUSTOMER_DELIVERY;
        break;
    /* the chip current life cycle is GD_PRODUCTION */
    case LC_GD_PRODUCTION:
        lc = LC_GD_PRODUCTION;
        break;
    /* the chip current life cycle is IN_FILED */
    case LC_IN_FIELD:
        lc = LC_IN_FIELD;
        break;
    default:
        break;
    }

    return lc;
}

/*!
    \brief      get real chip life cycle
    \param[in]  none
    \param[out] none
    \retval     lc_enum: life cycle state
      \arg        LC_FA               : failure analysis
      \arg        LC_UNKNOWN_STATE    : unknown life cycle state
      \arg        LC_OEM_PRODUCTION   : OEM production
      \arg        LC_CUSTOMER_DELIVERY: customer delivery
      \arg        LC_GD_PRODUCTION    : GD production
      \arg        LC_IN_FIELD         : in field
*/
lc_enum cltcfg_real_lc_get(void)
{
    uint32_t reg;
    lc_enum lc = LC_UNKNOWN_STATE;

    /* get the value of RLCS fields in CLTCFG_LC_CS register */
    reg = (uint32_t)CLTCFG_LC_CS >> 4;
    reg &= (CLTCFG_LC_MASK);

    switch(reg) {
    /* chip the current life cycle is FA */
    case LC_FA:
        lc = LC_FA;
        break;
    /* chip the current life cycle is OEM_PRODUCTION */
    case LC_OEM_PRODUCTION:
        lc = LC_OEM_PRODUCTION;
        break;
    /* chip the current life cycle is CUSTOMER_DELIVERY */
    case LC_CUSTOMER_DELIVERY:
        lc = LC_CUSTOMER_DELIVERY;
        break;
    /* chip the current life cycle is GD_PRODUCTION */
    case LC_GD_PRODUCTION:
        lc = LC_GD_PRODUCTION;
        break;
    /* chip the current life cycle is IN_FILED */
    case LC_IN_FIELD:
        lc = LC_IN_FIELD;
        break;
    default:
        break;
    }

    return lc;
}

/*!
    \brief      enable force life cycle
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_force_lc_enable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_LC_CS register */
    reg = CLTCFG_LC_CS;

    reg |= CLTCFG_LC_CS_FLCEN;

    CLTCFG_LC_CS = reg;
}

/*!
    \brief      disable force life cycle
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cltcfg_force_lc_disable(void)
{
    uint32_t reg;

    /* get the value of CLTCFG_LC_CS register */
    reg = CLTCFG_LC_CS;

    reg &= (~CLTCFG_LC_CS_FLCEN);

    CLTCFG_LC_CS = reg;
}

/*!
    \brief      provide provisions for a temporary life cycle update
    \param[in]  update_step: update step number
      \arg      LC_TEMP_NO_FORCE_UPDATE: no force update
      \arg      LC_TEMP_UPDATE_NEXT_ONE: force LC to one next step
      \arg      LC_TEMP_UPDATE_NEXT_TWO: force LC to two next steps
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus cltcfg_temporary_lc_config(lc_update_step_enum update_step)
{
    lc_enum lc;
    ErrStatus state = ERROR;
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_UPDATE_STEP_NUM(update_step)) {
        fw_debug_report_err(CLTCFG_MODULE_ID, API_ID(0x0025U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the real life cycle */
        lc = cltcfg_real_lc_get();
        /* get and clear the value of FTNLCS bits fields in the CLTCFG_LC_CS register */
        reg = CLTCFG_LC_CS;
        reg &= (~CLTCFG_LC_CS_FTNLCS);

        switch(lc) {
        /* chip the current life cycle is FA */
        case LC_FA:
            /* not allowed to move LC in FA */
            state = ERROR;
            break;
        /* chip the current life cycle is OEM_PRODUCTION */
        case LC_OEM_PRODUCTION:
            if(update_step < LC_TEMP_UPDATE_NEXT_TWO) {
                reg |= (uint32_t)update_step;
                CLTCFG_LC_CS = reg;
                state = SUCCESS;
            } else {
                /* two steps update is not allowed */
                state = ERROR;
            }
            break;
        /* chip the current life cycle is CUSTOMER_DELIVERY */
        case LC_CUSTOMER_DELIVERY:
            reg |= (uint32_t)update_step;
            CLTCFG_LC_CS = reg;
            state = SUCCESS;
            break;
        /* chip the current life cycle is GD_PRODUCTION */
        case LC_GD_PRODUCTION:
            if(update_step < LC_TEMP_UPDATE_NEXT_TWO) {
                reg |= (uint32_t)update_step;
                CLTCFG_LC_CS = reg;
                state = SUCCESS;
            } else {
                /* two steps update is not allowed */
                state = ERROR;
            }
            break;
        /* chip the current life cycle is IN_FILED */
        case LC_IN_FIELD:
            /* not allowed to move LC in IN_FIELD */
            state = ERROR;
            break;
        default:
            break;
        }
    }

    return state;
}
