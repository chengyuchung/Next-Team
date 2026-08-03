/*!
    \file    gd32a7xx_syscfg.c
    \brief   SYSCFG driver

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

#include "gd32a7xx_syscfg.h"

/*!
    \brief      reset the SYSCFG registers, API ID: 0x0001
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_deinit(void)
{
    SYSCFG_PMCFG        = 0U;
    SYSCFG_EXTISS0      = 0U;
    SYSCFG_EXTISS1      = 0U;
    SYSCFG_EXTISS2      = 0U;
    SYSCFG_EXTISS3      = 0U;
    SYSCFG_STAT         = 8U;
    SYSCFG_CFG          = 0x00280028U;
    SYSCFG_TIMERBKINSEL = 0U;
    SYSCFG_CPU0CS = 0x20U;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    SYSCFG_CPU1CS = 0x20U;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    SYSCFG_SRAMCFG     = 0U;
    SYSCFG_RMCFG       = 0U;
    SYSCFG_TIMER0CFG0  = 0U;
    SYSCFG_TIMER0CFG1  = 0U;
    SYSCFG_TIMER0CFG2  = 0U;
    SYSCFG_TIMER1CFG0  = 0U;
    SYSCFG_TIMER1CFG1  = 0U;
    SYSCFG_TIMER1CFG2  = 0U;
    SYSCFG_TIMER2CFG0  = 0U;
    SYSCFG_TIMER2CFG1  = 0U;
    SYSCFG_TIMER2CFG2  = 0U;
    SYSCFG_TIMER7CFG0  = 0U;
    SYSCFG_TIMER7CFG1  = 0U;
    SYSCFG_TIMER7CFG2  = 0U;
    SYSCFG_TIMER19CFG0 = 0U;
    SYSCFG_TIMER19CFG1 = 0U;
    SYSCFG_TIMER19CFG2 = 0U;
    SYSCFG_TIMER20CFG0 = 0U;
    SYSCFG_TIMER20CFG1 = 0U;
    SYSCFG_TIMER20CFG2 = 0U;
    SYSCFG_TIMER60CFG0 = 0U;
    SYSCFG_TIMER60CFG1 = 0U;
    SYSCFG_TIMER60CFG2 = 0U;
    SYSCFG_TIMER61CFG0 = 0U;
    SYSCFG_TIMER61CFG1 = 0U;
    SYSCFG_TIMER61CFG2 = 0U;
    SYSCFG_TIMER62CFG0 = 0U;
    SYSCFG_TIMER62CFG1 = 0U;
    SYSCFG_TIMER62CFG2 = 0U;
    SYSCFG_TIMER63CFG0 = 0U;
    SYSCFG_TIMER63CFG1 = 0U;
    SYSCFG_TIMER63CFG2 = 0U;
#if defined (GD32A72XX) || defined (GD32A74XX)
    SYSCFG_IRCP0INTSTAT0 = 0x3U;
    SYSCFG_IRCP0INTSTAT1 = 0x3U;
    SYSCFG_IRCP0INTSTAT2 = 0x3U;
    SYSCFG_IRCP0INTSTAT3 = 0x3U;
    SYSCFG_IRCP1INTSTAT0 = 0x3U;
    SYSCFG_IRCP1INTSTAT1 = 0x3U;
    SYSCFG_IRCP1INTSTAT2 = 0x3U;
    SYSCFG_IRCP1INTSTAT3 = 0x3U;
    SYSCFG_IRCP0INT0     = 0U;
    SYSCFG_IRCP0INT1     = 0U;
    SYSCFG_IRCP0INT2     = 0U;
    SYSCFG_IRCP0INT3     = 0U;
    SYSCFG_IRCP1INT0     = 0U;
    SYSCFG_IRCP1INT1     = 0U;
    SYSCFG_IRCP1INT2     = 0U;
    SYSCFG_IRCP1INT3     = 0U;
    SYSCFG_IRCPUCTL      = 0U;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
    SYSCFG_MEMAEXCTL = 0U;
    SYSCFG_BM1EDCEN  = 0U;
    SYSCFG_BM2EDCEN  = 0U;
    SYSCFG_BUSCHKCFG = 0U;
    SYSCFG_TMRFCS    = 0xF0000U;
    rcu_periph_reset_enable(RCU_SYSCFGRST);
    rcu_periph_reset_disable(RCU_SYSCFGRST);
}

/*!
    \brief      configure the GPIO pin as EXTI line, API ID: 0x0002
    \param[in]  exti_port: specify the gpio port used in EXTI
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_GPIOx(x = A,B,C..N): EXTI gpio port
    \param[in]  exti_pin: specify the EXTI line
                only one parameter can be selected which is shown as below:
      \arg        EXTI_SOURCE_PINx(for GPIOA\GPIOB\GPIOC\GPIOD\GPIOE\GPIOF\GPIOG\GPIOH\GPIOI\GPIOJ\
                                       GPIOK\GPIOL\GPIOM, x = 0..15, for GPION, x = 0..11): EXTI GPIO pin
    \param[out] none
    \retval     none
*/
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin)
{
    uint32_t clear_exti_mask = ~((uint32_t)EXTI_SS_MASK << (EXTI_SS_MSTEP(exti_pin)));
    uint32_t config_exti_mask = ((uint32_t)exti_port) << (EXTI_SS_MSTEP(exti_pin));

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTI_SOURCE_GPIO(exti_port)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(5), ERR_PARAM_INVALID);
    } else if(NOT_EXTI_SOURCE_PIN(exti_pin) && (exti_port != EXTI_SOURCE_GPION)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(5), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(exti_pin / EXTI_SS_JSTEP) {
        case EXTISS0:
            /* clear EXTI source line(0..3) */
            SYSCFG_EXTISS0 &= clear_exti_mask;
            /* configure EXTI source line(0..3) */
            SYSCFG_EXTISS0 |= config_exti_mask;
            break;
        case EXTISS1:
            /* clear EXTI source line(4..7) */
            SYSCFG_EXTISS1 &= clear_exti_mask;
            /* configure EXTI source line(4..7) */
            SYSCFG_EXTISS1 |= config_exti_mask;
            break;
        case EXTISS2:
            /* clear EXTI source line(8..11) */
            SYSCFG_EXTISS2 &= clear_exti_mask;
            /* configure EXTI source line(8..11) */
            SYSCFG_EXTISS2 |= config_exti_mask;
            break;
        case EXTISS3:
            /* clear EXTI source line(12..15) */
            SYSCFG_EXTISS3 &= clear_exti_mask;
            /* configure EXTI source line(12..15) */
            SYSCFG_EXTISS3 |= config_exti_mask;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      enable I2Cx(x=0,1) fast mode plus, API ID: 0x0003
    \param[in]  i2c_fmp
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SYSCFG_I2C_FMP(i2c_fmp)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(3), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_PMCFG |= i2c_fmp;
    }
}

/*!
    \brief      disable I2Cx(x=0,1) fast mode plus, API ID: 0x0004
    \param[in]  i2c_fmp
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_I2C0_FMP: I2C0 fast mode plus
      \arg        SYSCFG_I2C1_FMP: I2C1 fast mode plus
    \param[out] none
    \retval     none
*/
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SYSCFG_I2C_FMP(i2c_fmp)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(4), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_PMCFG &= ~i2c_fmp;
    }
}

/*!
    \brief      enable the tx EVENTOUT from CM_x, API ID: 0x0006
    \param[in]  core_txeven
                one or more parameters can be selected which are shown as below:
      \arg        CORE_TX_EVENTOUT_CM7_0: Cortex-M7 core 0(CM7_0) TX EVENTOUT
      \arg        CORE_TX_EVENTOUT_CM7_1: Cortex-M7 core 1(CM7_1) TX EVENTOUT
      \arg        CORE_TX_EVENTOUT_CM23: Cortex-M23 core(CM23 HSM) TX EVENTOUT
    \param[out] none
    \retval     none
*/
void syscfg_tx_eventout_enable(uint32_t core_txeven)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CORE_TX_EVENTOUT_CM(core_txeven)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(6), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_CFG |= (uint32_t)core_txeven;
    }
}

/*!
    \brief      disable the tx EVENTOUT from CM_x, API ID: 0x0007
    \param[in]  core_txeven
                one or more parameters can be selected which are shown as below:
      \arg        CORE_TX_EVENTOUT_CM7_0: Cortex-M7 core 0(CM7_0) TX EVENTOUT
      \arg        CORE_TX_EVENTOUT_CM7_1: Cortex-M7 core 1(CM7_1) TX EVENTOUT
      \arg        CORE_TX_EVENTOUT_CM23: Cortex-M23 core(CM23 HSM) TX EVENTOUT
    \param[out] none
    \retval     none
*/
void syscfg_tx_eventout_disable(uint32_t core_txeven)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CORE_TX_EVENTOUT_CM(core_txeven)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(7), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_CFG &= ~(uint32_t)core_txeven;
    }
}

/*!
    \brief      select TRIGSEL or GPIO as TIMER break input source, API ID: 0x0008
    \param[in]  timer_bkin
                one or more parameters can be selected which are shown as below:
      \arg        TIMERx_BRKINy_TRIG (x=0,7,19,20,60,61,62,63 y=0,1,2,3):TIMERx break input y source
    \param[in]  source_sel
                only one parameter can be selected which are shown as below:
      \arg        TIMER_BRKIN_SEL_GPIO: TIMER break input select from GPIO pin
      \arg        TIMER_BRKIN_SEL_TRIGSEL: TIMER break input select from TRIGSEL
    \param[out] none
    \retval     none
*/
void syscfg_timer_bkin_select(uint32_t timer_bkin, uint32_t source_sel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SYSCFG_TIMER_BKIN(timer_bkin)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(8), ERR_PARAM_INVALID);
    } else if(NOT_SYSCFG_TIMER_BRKIN_SEL(source_sel)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(8), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(TIMER_BRKIN_SEL_GPIO == source_sel) {
            /* select GPIO */
            SYSCFG_TIMERBKINSEL &= ~(uint32_t)timer_bkin;
        } else {
            /* select TRIGSEL */
            SYSCFG_TIMERBKINSEL |= (uint32_t)timer_bkin;
        }
    }
}

/*!
    \brief      CPU core held release set, API ID: 0x0009
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1, only for GD32A72XX/GD32A74XX
    \param[in]  hold_release
                only one parameter can be selected which are shown as below:
      \arg        CPU_HOLD: CPU held
      \arg        CPU_RELEASE: CPU released
    \param[out] none
    \retval     none
*/
void syscfg_cpu_hold_release_set(uint8_t core_num, uint8_t hold_release)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(9), ERR_PARAM_INVALID);
    } else if(NOT_CPU_HOLD_RELEASE(hold_release)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(9), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            /* configure CM7_0 */
            if(CPU_HOLD == hold_release) {
                SYSCFG_CPUCTL &= ~SYSCFG_CPUCTL_CPU0_HOLD;
            } else {
                SYSCFG_CPUCTL |= SYSCFG_CPUCTL_CPU0_HOLD;
            }
        } else {
#if defined (GD32A72XX) || defined (GD32A74XX)
            /* configure CM7_1 */
            if(CPU_HOLD == hold_release) {
                SYSCFG_CPUCTL &= ~SYSCFG_CPUCTL_CPU1_HOLD;
            } else {
                SYSCFG_CPUCTL |= SYSCFG_CPUCTL_CPU1_HOLD;
            }
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        }
    }
}

/*!
    \brief      CPU core AHB slave port priority set, API ID: 0x000A
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  priority
                only one parameter can be selected which are shown as below:
      \arg        ROUND_ROBIN: round-robin arbitration
      \arg        AHBS_HIGHER_PRIO: AHB slave port has higher access priority than core access
    \param[out] none
    \retval     none
*/
void syscfg_cpu_ahbs_priority_set(uint8_t core_num, uint8_t priority)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(10), ERR_PARAM_INVALID);
    } else if(NOT_SYSCFG_PRIORITY(priority)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(10), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            /* configure CM7_0 */
            if(ROUND_ROBIN == priority) {
                SYSCFG_CPUCTL &= ~SYSCFG_CPUCTL_CPU0_AHBSPRI;
            } else {
                SYSCFG_CPUCTL |= SYSCFG_CPUCTL_CPU0_AHBSPRI;
            }
        } else {
#if defined (GD32A72XX) || defined (GD32A74XX)
            /* configure CM7_1 */
            if(ROUND_ROBIN == priority) {
                SYSCFG_CPUCTL &= ~SYSCFG_CPUCTL_CPU1_AHBSPRI;
            } else {
                SYSCFG_CPUCTL |= SYSCFG_CPUCTL_CPU1_AHBSPRI;
            }
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        }
    }
}

/*!
    \brief      enable TCM wait state, API ID: 0x000B
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_tcm_wait_state_enable(void)
{
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_TCM_WAITSTATE;
}

/*!
    \brief      disable TCM wait state, API ID: 0x000C
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_tcm_wait_state_disable(void)
{
    SYSCFG_SRAMCFG &= ~SYSCFG_SRAMCFG_TCM_WAITSTATE;
}

/*!
    \brief      enable SRAM wait state, API ID: 0x000D
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_sram_wait_state_enable(void)
{
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_SRAM_WAITSTATE;
}

/*!
    \brief      disable SRAM wait state, API ID: 0x000E
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_sram_wait_state_disable(void)
{
    SYSCFG_SRAMCFG &= ~SYSCFG_SRAMCFG_SRAM_WAITSTATE;
}

/*!
    \brief      allow recovery mode on system or subsystem reset, API ID: 0x000F
    \param[in]  rm_reset
                only one parameter can be selected which are shown as below:
      \arg        RM_SYSTEM_RESET: recovery mode sequence on system reset
      \arg        RM_SUBSYSTEM_RESET: recovery mode sequence on subsystem reset
    \param[out] none
    \retval     none
*/
void syscfg_recovery_mode_allow(uint8_t rm_reset)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SYSCFG_RM_RESET(rm_reset)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(15), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(RM_SYSTEM_RESET == rm_reset) {
            SYSCFG_RMCFG &= ~SYSCFG_RMCFG_RM_SYSRST_DIS;
        } else {
            SYSCFG_RMCFG &= ~SYSCFG_RMCFG_RM_SUBSRST_DIS;
        }
    }
}

/*!
    \brief      disable recovery mode on system or subsystem reset, API ID: 0x0010
    \param[in]  rm_reset
      \arg        RM_SYSTEM_RESET: recovery mode sequence on system reset
      \arg        RM_SUBSYSTEM_RESET: recovery mode sequence on subsystem reset
    \param[out] none
    \retval     none
*/
void syscfg_recovery_mode_disable(uint8_t rm_reset)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SYSCFG_RM_RESET(rm_reset)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(16), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(RM_SYSTEM_RESET == rm_reset) {
            SYSCFG_RMCFG |= SYSCFG_RMCFG_RM_SYSRST_DIS;
        } else {
            SYSCFG_RMCFG |= SYSCFG_RMCFG_RM_SUBSRST_DIS;
        }
    }
}

#if defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      lock interrupt router core processor control register, API ID: 0x0011
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_router_reg_lock(void)
{
    SYSCFG_IRCPUCTL |= SYSCFG_IRCPUCTL_LK;
}

/*!
    \brief      configure core processor as trusted core, API ID: 0x0012
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[out] none
    \retval     none
*/
void syscfg_trusted_core_config_enable(uint8_t core_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(18), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            SYSCFG_IRCPUCTL |= SYSCFG_IRCPUCTL_CP0TR;
        } else {
            SYSCFG_IRCPUCTL |= SYSCFG_IRCPUCTL_CP1TR;
        }
    }
}

/*!
    \brief      configure core processor as non-trusted core, API ID: 0x0013
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[out] none
    \retval     none
*/
void syscfg_trusted_core_config_disable(uint8_t core_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(19), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            SYSCFG_IRCPUCTL &= ~SYSCFG_IRCPUCTL_CP0TR;
        } else {
            SYSCFG_IRCPUCTL &= ~SYSCFG_IRCPUCTL_CP1TR;
        }
    }
}
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      hard-lock the memory access execution control register, API ID: 0x0014
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_mem_access_ctlreg_hard_lock(void)
{
    SYSCFG_MEMAEXCTL |= SYSCFG_MEMAEXCTL_HLKEN;
}

/*!
    \brief      soft-lock the memory access execution control register, API ID: 0x0015
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_mem_access_ctlreg_soft_lock(void)
{
    SYSCFG_MEMAEXCTL |= SYSCFG_MEMAEXCTL_SLKEN;
}

/*!
    \brief      soft-unlock the memory access execution control register, API ID: 0x0016
    \param[in]  none
    \param[out] none
    \retval     none
*/
void syscfg_mem_access_ctlreg_soft_unlock(void)
{
    SYSCFG_MEMAEXCTL &= ~SYSCFG_MEMAEXCTL_SLKEN;
}

/*!
    \brief      allow memory access execution, API ID: 0x0017
    \param[in]  periph_ctl: specify the memory access bit in SYSCFG_MEMAEXCTL
                one or more parameters can be selected which are shown as below:
      \arg        MEMAEXCTL_SRAM0: SRAM 0 controller access execution control bit
      \arg        MEMAEXCTL_SRAM1: SRAM 1 controller access execution control bit
      \arg        MEMAEXCTL_ITCM0_DA: ITCM core 0 direct access execution control bit
      \arg        MEMAEXCTL_ITCM1_DA: ITCM core 1 direct access execution control bit
      \arg        MEMAEXCTL_ITCM0_BDA: ITCM core 0 backdoor access execution control bit
      \arg        MEMAEXCTL_ITCM1_BDA: ITCM core 1 backdoor access execution control bit
      \arg        MEMAEXCTL_DTCM0_DA: DTCM core 0 direct access execution control bit
      \arg        MEMAEXCTL_DTCM1_DA: DTCM core 1 direct access execution control bit
      \arg        MEMAEXCTL_DTCM0_BDA: DTCM core 0 backdoor access execution control bit
      \arg        MEMAEXCTL_DTCM1_BDA: DTCM core 1 backdoor access execution control bit
    \param[out] none
    \retval     none
*/
void syscfg_mem_access_allow(uint32_t periph_ctl)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_MEMAEXCTL_PERIPH(periph_ctl)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(23), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_MEMAEXCTL &= ~periph_ctl;
    }
}

/*!
    \brief      disable memory access execution, API ID: 0x0018
    \param[in]  periph_ctl: specify the memory access bit in SYSCFG_MEMAEXCTL
                one or more parameters can be selected which are shown as below:
      \arg        MEMAEXCTL_SRAM0: SRAM 0 controller access execution control bit
      \arg        MEMAEXCTL_SRAM1: SRAM 1 controller access execution control bit
      \arg        MEMAEXCTL_ITCM0_DA: ITCM core 0 direct access execution control bit
      \arg        MEMAEXCTL_ITCM1_DA: ITCM core 1 direct access execution control bit
      \arg        MEMAEXCTL_ITCM0_BDA: ITCM core 0 backdoor access execution control bit
      \arg        MEMAEXCTL_ITCM1_BDA: ITCM core 1 backdoor access execution control bit
      \arg        MEMAEXCTL_DTCM0_DA: DTCM core 0 direct access execution control bit
      \arg        MEMAEXCTL_DTCM1_DA: DTCM core 1 direct access execution control bit
      \arg        MEMAEXCTL_DTCM0_BDA: DTCM core 0 backdoor access execution control bit
      \arg        MEMAEXCTL_DTCM1_BDA: DTCM core 1 backdoor access execution control bit
    \param[out] none
    \retval     none
*/
void syscfg_mem_access_disable(uint32_t periph_ctl)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_MEMAEXCTL_PERIPH(periph_ctl)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(24), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_MEMAEXCTL |= periph_ctl;
    }
}

/*!
    \brief      enable peripheral bus matrix error detection function, API ID: 0x0019
    \param[in]  periph
                only one parameter can be selected which are shown as below:
      \arg        BM1_RD_DATA_CHK_DMA0MEM: read data check DMA0 memory accesses
      \arg        BM1_RD_DATA_CHK_DMA0PERIPH: read data check DMA0 peripheral accesses
      \arg        BM1_RD_DATA_CHK_DMA1MEM: read data check DMA1 memory accesses
      \arg        BM1_RD_DATA_CHK_DMA1PERIPH: read data check DMA1 peripheral accesses
      \arg        BM1_RD_DATA_CHK_HSM_BM1: read data check HSM BM1
      \arg        BM1_RD_DATA_CHK_ENET: read data check ENET
      \arg        BM1_RD_DATA_CHK_CM7_0: read data check Cortex-M7_0_AXIM
      \arg        BM1_RD_DATA_CHK_CM7_1: read data check Cortex-M7_1_AXIM
      \arg        BM1_WR_DATA_CHK_SRAM0: write data check SRAM0
      \arg        BM1_ADDR_CHK_SRAM0: address check SRAM0
      \arg        BM1_WR_DATA_CHK_SRAM1: write data check SRAM1
      \arg        BM1_ADDR_CHK_SRAM1: address check SRAM1
      \arg        BM1_WR_DATA_CHK_QSPI: write data check QSPI
      \arg        BM1_ADDR_CHK_QSPI: address check QSPI
      \arg        BM1_WR_DATA_CHK_FMC0: write data check FMC_0
      \arg        BM1_ADDR_CHK_FMC0: address check FMC_0
      \arg        BM1_WR_DATA_CHK_FMC1: write data check FMC_1
      \arg        BM1_ADDR_CHK_FMC1: address check FMC_1
      \arg        BM1_WR_DATA_CHK_FMC2: write data check FMC_2
      \arg        BM1_ADDR_CHK_FMC2: address check FMC_2
      \arg        BM1_WR_DATA_CHK_TCM: write data check TCM
      \arg        BM1_ADDR_CHK_TCM: address check TCM
      \arg        BM2_RD_DATA_CHK_DMA0MEM: read data check DMA0 memory accesses
      \arg        BM2_RD_DATA_CHK_DMA0PERIPH: read data check DMA0 peripheral accesses
      \arg        BM2_RD_DATA_CHK_DMA1MEM: read data check DMA1 memory accesses
      \arg        BM2_RD_DATA_CHK_DMA1PERIPH: read data check DMA1 peripheral accesses
      \arg        BM2_RD_DATA_CHK_HSM_BM2: read data check HSM BM2
      \arg        BM2_RD_DATA_CHK_AHBP_CM7_0: read data check Cortex-M7_0_AHBP
      \arg        BM2_RD_DATA_CHK_AHBP_CM7_1: read data check Cortex-M7_1_AHBP
      \arg        BM2_WR_DATA_CHK_APB1: write data check APB1
      \arg        BM2_ADDR_CHK_APB1: address check APB1
      \arg        BM2_WR_DATA_CHK_APB2: write data check APB2
      \arg        BM2_ADDR_CHK_APB2: address check APB2
      \arg        BM2_WR_DATA_CHK_AHB1: write data check AHB1
      \arg        BM2_ADDR_CHK_AHB1: address check AHB1
      \arg        BM2_WR_DATA_CHK_AHB2: write data check AHB2
      \arg        BM2_ADDR_CHK_AHB2: address check AHB2
    \param[out] none
    \retval     none
*/
void syscfg_bus_matrix_error_detect_enable(uint32_t periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BM_PERIPH(periph)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(25), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U == (uint32_t)(periph & BUS_MATRIX_2)) {
            /* bus matrix 1 peripheral */
            SYSCFG_BM1EDCEN |= (uint32_t)(periph);
        } else {
            /* bus matrix 2 peripheral */
            SYSCFG_BM2EDCEN |= (uint32_t)(periph & ~BUS_MATRIX_2);
        }
    }
}

/*!
    \brief      disable peripheral in bus matrix error detection function, API ID: 0x001A
    \param[in]  periph
                only one parameter can be selected which are shown as below:
      \arg        BM1_RD_DATA_CHK_DMA0MEM: read data check DMA0 memory accesses
      \arg        BM1_RD_DATA_CHK_DMA0PERIPH: read data check DMA0 peripheral accesses
      \arg        BM1_RD_DATA_CHK_DMA1MEM: read data check DMA1 memory accesses
      \arg        BM1_RD_DATA_CHK_DMA1PERIPH: read data check DMA1 peripheral accesses
      \arg        BM1_RD_DATA_CHK_HSM_BM1: read data check HSM BM1
      \arg        BM1_RD_DATA_CHK_ENET: read data check ENET
      \arg        BM1_RD_DATA_CHK_CM7_0: read data check Cortex-M7_0_AXIM
      \arg        BM1_RD_DATA_CHK_CM7_1: read data check Cortex-M7_1_AXIM
      \arg        BM1_WR_DATA_CHK_SRAM0: write data check SRAM0
      \arg        BM1_ADDR_CHK_SRAM0: address check SRAM0
      \arg        BM1_WR_DATA_CHK_SRAM1: write data check SRAM1
      \arg        BM1_ADDR_CHK_SRAM1: address check SRAM1
      \arg        BM1_WR_DATA_CHK_QSPI: write data check QSPI
      \arg        BM1_ADDR_CHK_QSPI: address check QSPI
      \arg        BM1_WR_DATA_CHK_FMC0: write data check FMC_0
      \arg        BM1_ADDR_CHK_FMC0: address check FMC_0
      \arg        BM1_WR_DATA_CHK_FMC1: write data check FMC_1
      \arg        BM1_ADDR_CHK_FMC1: address check FMC_1
      \arg        BM1_WR_DATA_CHK_FMC2: write data check FMC_2
      \arg        BM1_ADDR_CHK_FMC2: address check FMC_2
      \arg        BM1_WR_DATA_CHK_TCM: write data check TCM
      \arg        BM1_ADDR_CHK_TCM: address check TCM
      \arg        BM2_RD_DATA_CHK_DMA0MEM: read data check DMA0 memory accesses
      \arg        BM2_RD_DATA_CHK_DMA0PERIPH: read data check DMA0 peripheral accesses
      \arg        BM2_RD_DATA_CHK_DMA1MEM: read data check DMA1 memory accesses
      \arg        BM2_RD_DATA_CHK_DMA1PERIPH: read data check DMA1 peripheral accesses
      \arg        BM2_RD_DATA_CHK_HSM_BM2: read data check HSM BM2
      \arg        BM2_RD_DATA_CHK_AHBP_CM7_0: read data check Cortex-M7_0_AHBP
      \arg        BM2_RD_DATA_CHK_AHBP_CM7_1: read data check Cortex-M7_1_AHBP
      \arg        BM2_WR_DATA_CHK_APB1: write data check APB1
      \arg        BM2_ADDR_CHK_APB1: address check APB1
      \arg        BM2_WR_DATA_CHK_APB2: write data check APB2
      \arg        BM2_ADDR_CHK_APB2: address check APB2
      \arg        BM2_WR_DATA_CHK_AHB1: write data check AHB1
      \arg        BM2_ADDR_CHK_AHB1: address check AHB1
      \arg        BM2_WR_DATA_CHK_AHB2: write data check AHB2
      \arg        BM2_ADDR_CHK_AHB2: address check AHB2
    \param[out] none
    \retval     none
*/
void syscfg_bus_matrix_error_detect_disable(uint32_t periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BM_PERIPH(periph)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(26), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U == (uint32_t)(periph & BUS_MATRIX_2)) {
            /* bus matrix 1 peripheral */
            SYSCFG_BM1EDCEN &= (uint32_t)(~periph);
        } else {
            /* bus matrix 2 peripheral */
            SYSCFG_BM2EDCEN &= (uint32_t)~(periph & ~BUS_MATRIX_2);
        }
    }
}

/*!
    \brief      enable peripheral bus check function, API ID: 0x001B
    \param[in]  periph
                one or more parameters can be selected which are shown as below:
      \arg        ENET_MEM_PORT_CHK: ENET mem port timeout and slaver ID check, only in GD32A714Axx /A72xAxx / A74xAxx
      \arg        HSM_PORT_CHK: HSM port timeout and slaver ID check
      \arg        DMA0MEM_PORT_CHK: DMA0 mem port timeout and slaver ID check
      \arg        DMA0PERIPH_PORT_CHK: DMA0 peri port timeout and slaver ID check
      \arg        DMA1MEM_PORT_CHK: DMA1 mem port timeout and slaver ID check
      \arg        DMA1PERIPH_PORT_CHK: DMA1 peri port timeout and slaver ID check
      \arg        AHBP_CM7_0_PORT_CHK: CM7_0 AHBP port timeout and slaver ID check
      \arg        AHBP_CM7_1_PORT_CHK: CM7_1 AHBP port timeout and slaver ID check
      \arg        AXIM_CM7_0_PORT_CHK: CM7_0 AXIM port timeout and slaver ID check
      \arg        AXIM_CM7_1_PORT_CHK: CM7_1 AXIM port timeout and slaver ID check
      \arg        DMA0MEM_SPLIT0_WIDGET_CHK: split0 widget of DMA0 mem redundant check
      \arg        DMA0PERIPH_SPLIT0_WIDGET_CHK: split0 widget of DMA0 peri redundant check
      \arg        DMA1MEM_SPLIT0_WIDGET_CHK: split0 widget of DMA1 mem redundant check
      \arg        DMA1PERIPH_SPLIT0_WIDGET_CHK: split0 widget of DMA1 peri redundant check
      \arg        HSM_SPLIT1_WIDGET_CHK: split1 widget of HSM redundant check
      \arg        TCM_SPLIT1_WIDGET_CHK: split1 widget of TCM SRAM redundant check
      \arg        HSM_H2H1_WIDGET_CHK: H2H1 widget of HSM redundant check
      \arg        DMA0MEM_H2H0_WIDGET_CHK: H2H0 widget of DMA0 mem redundant check
      \arg        DMA0PERIPH_H2H0_WIDGET_CHK: H2H0 widget of DMA0 peri redundant check
      \arg        DMA1MEM_H2H0_WIDGET_CHK: H2H0 widget of DMA1 mem redundant check
      \arg        DMA1PERIPH_H2H0_WIDGET_CHK: H2H0 widget of DMA1 peri redundant check
      \arg        QSPI_H2H0_WIDGET_CHK: H2H0 widget of QSPI redundant check
      \arg        TCM_H2H0_WIDGET_CHK: H2H0 widget of TCM redundant check
      \arg        ENET_WIDGET_CHK: ENET 1:1/1:2 widget check
      \arg        TCM_WIDGET_CHK: TCM 1:1 widget check
      \arg        APB1_CHK: APB1 redundant check
      \arg        APB2_CHK: APB2 redundant check
      \arg        AHB1_CHK: AHB1 redundant check
      \arg        AHB2_CHK: AHB2 redundant check
    \param[out] none
    \retval     none
*/
void syscfg_bus_check_enable(uint32_t periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUS_CHK_PERIPH(periph)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(27), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_BUSCHKCFG |= periph;
    }
}

/*!
    \brief      disable peripheral bus check function, API ID: 0x001C
    \param[in]  periph
                one or more parameters can be selected which are shown as below:
      \arg        ENET_MEM_PORT_CHK: ENET mem port timeout and slaver ID check, only in GD32A714Axx /A72xAxx / A74xAxx
      \arg        HSM_PORT_CHK: HSM port timeout and slaver ID check
      \arg        DMA0MEM_PORT_CHK: DMA0 mem port timeout and slaver ID check
      \arg        DMA0PERIPH_PORT_CHK: DMA0 peri port timeout and slaver ID check
      \arg        DMA1MEM_PORT_CHK: DMA1 mem port timeout and slaver ID check
      \arg        DMA1PERIPH_PORT_CHK: DMA1 peri port timeout and slaver ID check
      \arg        AHBP_CM7_0_PORT_CHK: CM7_0 AHBP port timeout and slaver ID check
      \arg        AHBP_CM7_1_PORT_CHK: CM7_1 AHBP port timeout and slaver ID check
      \arg        AXIM_CM7_0_PORT_CHK: CM7_0 AXIM port timeout and slaver ID check
      \arg        AXIM_CM7_1_PORT_CHK: CM7_1 AXIM port timeout and slaver ID check
      \arg        DMA0MEM_SPLIT0_WIDGET_CHK: split0 widget of DMA0 mem redundant check
      \arg        DMA0PERIPH_SPLIT0_WIDGET_CHK: split0 widget of DMA0 peri redundant check
      \arg        DMA1MEM_SPLIT0_WIDGET_CHK: split0 widget of DMA1 mem redundant check
      \arg        DMA1PERIPH_SPLIT0_WIDGET_CHK: split0 widget of DMA1 peri redundant check
      \arg        HSM_SPLIT1_WIDGET_CHK: split1 widget of HSM redundant check
      \arg        TCM_SPLIT1_WIDGET_CHK: split1 widget of TCM SRAM redundant check
      \arg        HSM_H2H1_WIDGET_CHK: H2H1 widget of HSM redundant check
      \arg        DMA0MEM_H2H0_WIDGET_CHK: H2H0 widget of DMA0 mem redundant check
      \arg        DMA0PERIPH_H2H0_WIDGET_CHK: H2H0 widget of DMA0 peri redundant check
      \arg        DMA1MEM_H2H0_WIDGET_CHK: H2H0 widget of DMA1 mem redundant check
      \arg        DMA1PERIPH_H2H0_WIDGET_CHK: H2H0 widget of DMA1 peri redundant check
      \arg        QSPI_H2H0_WIDGET_CHK: H2H0 widget of QSPI redundant check
      \arg        TCM_H2H0_WIDGET_CHK: H2H0 widget of TCM redundant check
      \arg        ENET_WIDGET_CHK: ENET 1:1/1:2 widget check, only in GD32A714Axx /A72xAxx / A74xAxx
      \arg        TCM_WIDGET_CHK: TCM 1:1 widget check
      \arg        APB1_CHK: APB1 redundant check
      \arg        APB2_CHK: APB2 redundant check
      \arg        AHB1_CHK: AHB1 redundant check
      \arg        AHB2_CHK: AHB2 redundant check
    \param[out] none
    \retval     none
*/
void syscfg_bus_check_disable(uint32_t periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BUS_CHK_PERIPH(periph)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(28), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_BUSCHKCFG &= ~periph;
    }
}

/*!
    \brief      enable the interrupt from the peripheral to the CPU NMI, API ID: 0x001D
    \param[in]  cpu_interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_INT_CPU0_CKMNMI: NMI interrupt from EXTI enable bit of CPU0
      \arg        SYSCFG_INT_CPU0_NMIPIN: HXTAL clock monitor NMI interrupt enable bit of CPU0
      \arg        SYSCFG_INT_CPU0_FMUNMI: FMU NMI interrupt enable bit of CPU0
      \arg        SYSCFG_INT_CPU1_CKMNMI: NMI interrupt from EXTI enable bit of CPU1
      \arg        SYSCFG_INT_CPU1_NMIPIN: HXTAL clock monitor NMI interrupt enable bit of CPU1
      \arg        SYSCFG_INT_CPU1_FMUNMI: FMU NMI interrupt enable bit of CPU1
    \param[out] none
    \retval     none
*/
void syscfg_nmi_interrupt_enable(uint32_t cpu_interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SYSCFG_INT_CPU_NMI(cpu_interrupt)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(29), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_CFG |= cpu_interrupt;
    }
}

/*!
    \brief      disable the interrupt from the peripheral to the CPU NMI, API ID: 0x001F
    \param[in]  cpu_interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_INT_CPU0_CKMNMI: NMI interrupt from EXTI enable bit of CPU0
      \arg        SYSCFG_INT_CPU0_NMIPIN: HXTAL clock monitor NMI interrupt enable bit of CPU0
      \arg        SYSCFG_INT_CPU0_FMUNMI: FMU NMI interrupt enable bit of CPU0
      \arg        SYSCFG_INT_CPU1_CKMNMI: NMI interrupt from EXTI enable bit of CPU1
      \arg        SYSCFG_INT_CPU1_NMIPIN: HXTAL clock monitor NMI interrupt enable bit of CPU1
      \arg        SYSCFG_INT_CPU1_FMUNMI: FMU NMI interrupt enable bit of CPU1
    \param[out] none
    \retval     none
*/
void syscfg_nmi_interrupt_disable(uint32_t cpu_interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SYSCFG_INT_CPU_NMI(cpu_interrupt)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(30), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_CFG &= ~cpu_interrupt;
    }
}

/*!
    \brief      enable FPU error and TCM write abort interrupt, API ID: 0x0020
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  fpu_tcm_int
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_INEXACT: FPU inexact interrupt
      \arg        SYSCFG_FPUINT_INPUT_ABNORMAL: FPU input abnormal interrupt
      \arg        SYSCFG_FPUINT_OVERFLOW: FPU overflow interrupt
      \arg        SYSCFG_FPUINT_UNDERFLOW: FPU underflow interrupt
      \arg        SYSCFG_FPUINT_DIV0: FPU divide-by-zero interrupt
      \arg        SYSCFG_FPUINT_INVALID_OPERATION: FPU invalid operation interrupt
      \arg        SYSCFG_TCMINT_WR_ABORT: write abort on slave overrun interrupt
    \param[out] none
    \retval     none
*/
void syscfg_fpu_tcm_interrupt_enable(uint8_t core_num, uint32_t fpu_tcm_int)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(31), ERR_PARAM_INVALID);
    } else if(NOT_FPU_TCM_INT(fpu_tcm_int)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(31), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            /* configure CM7_0 */
            SYSCFG_CPU0CS |= fpu_tcm_int;
        } else {
#if defined (GD32A72XX) || defined (GD32A74XX)
            /* configure CM7_1 */
            SYSCFG_CPU1CS |= fpu_tcm_int;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        }
    }
}

/*!
    \brief      disable FPU error and TCM write abort interrupt, API ID: 0x0021
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  cpu_interrupt
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_INEXACT: FPU inexact interrupt
      \arg        SYSCFG_FPUINT_INPUT_ABNORMAL: FPU input abnormal interrupt
      \arg        SYSCFG_FPUINT_OVERFLOW: FPU overflow interrupt
      \arg        SYSCFG_FPUINT_UNDERFLOW: FPU underflow interrupt
      \arg        SYSCFG_FPUINT_DIV0: FPU divide-by-zero interrupt
      \arg        SYSCFG_FPUINT_INVALID_OPERATION: FPU invalid operation interrupt
      \arg        SYSCFG_TCMINT_WR_ABORT: write abort on slave overrun interrupt
    \param[out] none
    \retval     none
*/
void syscfg_fpu_tcm_interrupt_disable(uint8_t core_num, uint32_t fpu_tcm_int)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(32), ERR_PARAM_INVALID);
    } else if(NOT_FPU_TCM_INT(fpu_tcm_int)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(32), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            /* configure CM7_0 */
            SYSCFG_CPU0CS &= ~fpu_tcm_int;
        } else {
#if defined (GD32A72XX) || defined (GD32A74XX)
            /* configure CM7_1 */
            SYSCFG_CPU1CS &= ~fpu_tcm_int;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        }
    }
}

#if defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      enable interrupt router interrupt, API ID: 0x0022
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  ir_cp_int
                only one parameter can be selected which are shown as below:
      \arg        INTROUTER_CP_INT_0: interrupt router core processer interrupt 0
      \arg        INTROUTER_CP_INT_1: interrupt router core processer interrupt 1
      \arg        INTROUTER_CP_INT_2: interrupt router core processer interrupt 2
      \arg        INTROUTER_CP_INT_3: interrupt router core processer interrupt 3
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_router_interrupt_enable(uint8_t core_num, uint32_t ir_cp_int)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(33), ERR_PARAM_INVALID);
    } else if(NOT_IR_CP_INT(ir_cp_int)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(33), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            /* configure CM7_0 interrupt router */
            REG32(SYSCFG + 0x00000304U + (uint32_t)(ir_cp_int * 0x08U)) |= SYSCFG_IRCP0INT0_CPIE;
        } else {
            /* configure CM7_1 interrupt router */
            REG32(SYSCFG + 0x00000324U + (uint32_t)(ir_cp_int * 0x08U)) |= SYSCFG_IRCP1INT0_CPIE;
        }
    }
}

/*!
    \brief      disable interrupt router interrupt, API ID: 0x0023
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  ir_cp_int
                only one parameter can be selected which are shown as below:
      \arg        INTROUTER_CP_INT_0: interrupt router core processer interrupt 0
      \arg        INTROUTER_CP_INT_1: interrupt router core processer interrupt 1
      \arg        INTROUTER_CP_INT_2: interrupt router core processer interrupt 2
      \arg        INTROUTER_CP_INT_3: interrupt router core processer interrupt 3
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_router_interrupt_disable(uint8_t core_num, uint32_t ir_cp_int)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(34), ERR_PARAM_INVALID);
    } else if(NOT_IR_CP_INT(ir_cp_int)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(34), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            /* configure CM7_0 interrupt router */
            REG32(SYSCFG + 0x00000304U + ir_cp_int * 0x08U) &= ~SYSCFG_IRCP0INT0_CPIE;
        } else {
            /* configure CM7_1 interrupt router */
            REG32(SYSCFG + 0x00000324U + ir_cp_int * 0x08U) &= ~SYSCFG_IRCP1INT0_CPIE;
        } 
    }
}
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      enable TMR error interrupt, API ID: 0x0024
    \param[in]  tmrerr_int
                only one parameter can be selected which are shown as below:
      \arg        TMRERR_INT_FMUNMI: TMR fault interrupt enable of the FMU NMI interrupt flag enable
      \arg        TMRERR_INT_CPEN: TMR fault interrupt enable of the CPU released
      \arg        TMRERR_INT_MEMEXECR: TMR fault interrupt enable of the memory execution control register
      \arg        TMRERR_INT_CPINT: TMR fault interrupt enable of the interrupt router CPn interrupt status register
    \param[out] none
    \retval     none
*/
void syscfg_tmr_error_interrupt_enable(uint32_t tmrerr_int)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TMRERR_INT(tmrerr_int)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(35), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_TMRFCS |= tmrerr_int;
    }
}

/*!
    \brief      disable TMR error interrupt, API ID: 0x0025
    \param[in]  tmrerr_int
                only one parameter can be selected which are shown as below:
      \arg        TMRERR_INT_FMUNMI: TMR fault interrupt enable of the FMU NMI interrupt flag enable
      \arg        TMRERR_INT_CPEN: TMR fault interrupt enable of the CPU released
      \arg        TMRERR_INT_MEMEXECR: TMR fault interrupt enable of the memory execution control register
      \arg        TMRERR_INT_CPINT: TMR fault interrupt enable of the interrupt router CPn interrupt status register
    \param[out] none
    \retval     none
*/
void syscfg_tmr_error_interrupt_disable(uint32_t tmrerr_int)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TMRERR_INT(tmrerr_int)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(36), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_TMRFCS &= ~tmrerr_int;
    }
}

/*!
    \brief      get NMI interrupt flag, API ID: 0x0026
    \param[in]  nmi_flag
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FLAG_CKMNMIERR: HXTAL clock monitor NMI error flag
      \arg        SYSCFG_FLAG_NMIPINERR: NMI pin error flag
      \arg        SYSCFG_FLAG_FMUNMIERR: FMU NMI error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_nmi_flag_get(uint32_t nmi_flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_NMI_FLAG(nmi_flag)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(37), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (SYSCFG_STAT & nmi_flag)) {
            reval = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return reval;
}

/*!
    \brief      get FPU error and TCM write abort interrupt flag, API ID: 0x0027
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  fpu_tcm_intflag
                one or more parameters can be selected which are shown as below:
      \arg        SYSCFG_FPUINT_FLAG_INEXACT: FPU inexact interrupt flag
      \arg        SYSCFG_FPUINT_FLAG_INPUT_ABNORMAL: FPU input abnormal interrupt flag
      \arg        SYSCFG_FPUINT_FLAG_OVERFLOW: FPU overflow interrupt flag
      \arg        SYSCFG_FPUINT_FLAG_UNDERFLOW: FPU underflow interrupt flag
      \arg        SYSCFG_FPUINT_FLAG_DIV0: FPU divide-by-zero interrupt flag
      \arg        SYSCFG_FPUINT_FLAG_INVALID_OPERATION: FPU invalid operation interrupt flag
      \arg        SYSCFG_TCMINT_FLAG_WR_ABORT: write abort on slave overrun interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_fpu_tcm_interrupt_flag_get(uint8_t core_num, uint32_t fpu_tcm_intflag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(38), ERR_PARAM_INVALID);
    } else if(NOT_FPU_TCM_INTFLAG(fpu_tcm_intflag)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(38), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            if(0U != (SYSCFG_CPU0CS & fpu_tcm_intflag)) {
                reval = SET;
            } else {
                /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
            }
        } else {
#if defined (GD32A72XX) || defined (GD32A74XX)
            if(0U != (SYSCFG_CPU1CS & fpu_tcm_intflag)) {
                reval = SET;
            } else {
                /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
            }
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        }
    }
    return reval;
}

/*!
    \brief      get CPU I-Cache error status, API ID: 0x0028
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  cache_error
                only one parameter can be selected which are shown as below:
      \arg        CPU_CACHE_ERROR_DETECTION: select detection information of CPU
      \arg        CPU_CACHE_ERROR_BANK: select error information of CPU
    \param[out] none
    \retval     I-Cache error
*/
uint32_t syscfg_icache_error_status_get(uint8_t core_num, uint32_t cache_error)
{
    uint32_t reval = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(39), ERR_PARAM_INVALID);
    } else if(NOT_CPU_CACHE_ERROR(cache_error)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(39), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            if(CPU_CACHE_ERROR_DETECTION != cache_error) {
                reval = (uint32_t)((uint32_t)(SYSCFG_CPU0ICAC & 0x0FFFFFC0U) >> 6U);
            } else {
                reval = (uint32_t)(SYSCFG_CPU0ICAC >> 28U);
            }
        } else {
#if defined (GD32A72XX) || defined (GD32A74XX)
            if(CPU_CACHE_ERROR_DETECTION != cache_error) {
                reval = (uint32_t)((SYSCFG_CPU1ICAC & 0x0FFFFFC0U) >> 6U);
            } else {
                reval = (uint32_t)(SYSCFG_CPU1ICAC >> 28U);
            }
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        }
    }
    return reval;
}

/*!
    \brief      get CPU D-Cache error status, API ID: 0x0029
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  cache_error
                only one parameter can be selected which are shown as below:
      \arg        CPU_CACHE_ERROR_DETECTION: select detection information of CPU
      \arg        CPU_CACHE_ERROR_BANK: select error information of CPU
    \param[out] none
    \retval     D-Cache error
*/
uint32_t syscfg_dcache_error_status_get(uint8_t core_num, uint32_t cache_error)
{
    uint32_t reval = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(40), ERR_PARAM_INVALID);
    } else if(NOT_CPU_CACHE_ERROR(cache_error)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(40), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            if(CPU_CACHE_ERROR_DETECTION != cache_error) {
                reval = (uint32_t)((SYSCFG_CPU0DCAC & 0x0FFFFFC0U) >> 6U);
            } else {
                reval = (uint32_t)(SYSCFG_CPU0DCAC >> 28U);
            }
        } else {
#if defined (GD32A72XX) || defined (GD32A74XX)
            if(CPU_CACHE_ERROR_DETECTION != cache_error) {
                reval = (uint32_t)((SYSCFG_CPU1DCAC & 0x0FFFFFC0U) >> 6U);
            } else {
                reval = (uint32_t)(SYSCFG_CPU1DCAC >> 28U);
            }
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
        }
    }
    return reval;
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      get CPU platform status, API ID: 0x002A
    \param[in]  none
    \param[out] none
    \retval     CPU platform status information
      \arg        LOCKSTEP_MODE: the host core is in lockstep mode
      \arg        SINGLE_CORE: the host core is single core
      \arg        DUAL_CORE: the host core is dual core
*/
syscfg_cpustat_enum syscfg_cpu_platform_status_get(void)
{
    syscfg_cpustat_enum syscfg_cpustat = LOCKSTEP_MODE;
    switch(SYSCFG_CPUSTAT & SYSCFG_CPUSTAT_CPUSTAT) {
    /* get CPU platform status */
    case 2:
        syscfg_cpustat = SINGLE_CORE;
        break;
    case 3:
        syscfg_cpustat = DUAL_CORE;
        break;
    default:
        break;
    }
    return syscfg_cpustat;
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      get HSM sub system has entered standby flag, API ID: 0x002B
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_hsm_enter_standby_flag_get(void)
{
    FlagStatus reval = RESET;
    if(0U != (SYSCFG_HSMSTAT & SYSCFG_HSMSTAT_HSM_ENTER_STDBY)) {
        reval = SET;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    return reval;
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      get core processor ID, API ID: 0x002C
    \param[in]  none
    \param[out] none
    \retval     core processor ID
*/
uint32_t syscfg_cpu_id_get(void)
{
    uint32_t core_id = 0U;
    if(CPU0_ID == SYSCFG_CPID) {
        core_id = CPU0_ID;
    }
#if defined (GD32A72XX) || defined (GD32A74XX)
    else if(CPU1_ID == SYSCFG_CPID) {
        core_id = CPU1_ID;
    }
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
    else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    return core_id;
}


/*!
    \brief      get core processor number, API ID: 0x002D
    \param[in]  none
    \param[out] none
    \retval     core processor number
*/
uint8_t syscfg_cpu_number_get(void)
{
    uint8_t core_num = 0U;
    if(CM7_0 == (SYSCFG_CPNUM & SYSCFG_CPNUM_CPNUM)) {
        core_num = CM7_0;
    }
#if defined (GD32A72XX) || defined (GD32A74XX)
    else if(CM7_1 == (SYSCFG_CPNUM & SYSCFG_CPNUM_CPNUM)) {
        core_num = CM7_1;
    }
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
    else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    return core_num;
}

/*!
    \brief      get CPU cache information, API ID: 0x002E
    \param[in]  cache_info
                only one parameter can be selected which are shown as below:
      \arg        ICACHE_INFO: I-Cache information
      \arg        DCACHE_INFO: D-Cache information
    \param[out] none
    \retval     CPU cache information
*/
uint32_t syscfg_cpu_cache_info_get(uint32_t cache_info)
{
    uint32_t ret_cache_info = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CACHE_INFO(cache_info)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(45), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ICACHE_INFO == cache_info) {
            ret_cache_info = (uint32_t)((uint32_t)((SYSCFG_CPCFGINF0 & BITS(16, 31)) >> 16U));
        } else {
            ret_cache_info = (uint32_t)(SYSCFG_CPCFGINF0 & BITS(0, 15));
        }
    }
    return ret_cache_info;
}

/*!
    \brief      get TCM size information, API ID: 0x002F
    \param[in]  tcm_info
                only one parameter can be selected which are shown as below:
      \arg        ITCM_INFO: ITCM information
      \arg        DTCM_INFO: DTCM information
    \param[out] none
    \retval     TCM information
*/
uint32_t syscfg_cpu_tcm_size_get(uint32_t tcm_info)
{
    uint32_t ret_tcm_info = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TCM_INFO(tcm_info)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(46), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ITCM_INFO == tcm_info) {
            ret_tcm_info = (uint32_t)((uint32_t)((SYSCFG_CPCFGINF1 & SYSCFG_CPCFGINF1_ITCM_SZ) >> 16U));
        } else {
            ret_tcm_info = (uint32_t)((uint32_t)((SYSCFG_CPCFGINF1 & SYSCFG_CPCFGINF1_DTCM_SZ) >> 24U));
        }
    }
    return ret_tcm_info;
}

/*!
    \brief      get core processor configuration information, API ID: 0x0030
    \param[in]  none
    \param[out] none
    \retval     core processor configuration information
*/
uint32_t syscfg_cpu_config_info_get(void)
{
    return (uint32_t)(SYSCFG_CPCFGINF2 & BITS(0, 4));
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      get core 0 processor ID, API ID: 0x0036
    \param[in]  none
    \param[out] none
    \retval     core processor ID
*/
uint32_t syscfg_cpu0_id_get(void)
{
    return SYSCFG_CP0ID;
}


/*!
    \brief      get core processor 0 number, API ID: 0x0037
    \param[in]  none
    \param[out] none
    \retval     core processor number
*/
uint8_t syscfg_cpu0_number_get(void)
{
    return (uint8_t)SYSCFG_CP0NUM;
}

/*!
    \brief      get CPU 0 cache information, API ID: 0x0038
    \param[in]  cache_info
                only one parameter can be selected which are shown as below:
      \arg        ICACHE_INFO: I-Cache information
      \arg        DCACHE_INFO: D-Cache information
    \param[out] none
    \retval     CPU cache information
*/
uint32_t syscfg_cpu0_cache_info_get(uint32_t cache_info)
{
    uint32_t ret_cache_info = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CACHE_INFO(cache_info)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(56), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ICACHE_INFO == cache_info) {
            ret_cache_info = (uint32_t)((uint32_t)((SYSCFG_CP0CFGINF0 & BITS(16, 31)) >> 16U));
        } else {
            ret_cache_info = (uint32_t)(SYSCFG_CP0CFGINF0 & BITS(0, 15));
        }
    }
    return ret_cache_info;
}

/*!
    \brief      get CPU 0 TCM size information, API ID: 0x0039
    \param[in]  tcm_info
                only one parameter can be selected which are shown as below:
      \arg        ITCM_INFO: ITCM information
      \arg        DTCM_INFO: DTCM information
    \param[out] none
    \retval     TCM information
*/
uint32_t syscfg_cpu0_tcm_size_get(uint32_t tcm_info)
{
    uint32_t ret_tcm_info = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TCM_INFO(tcm_info)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(57), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ITCM_INFO == tcm_info) {
            ret_tcm_info = (uint32_t)((uint32_t)((SYSCFG_CP0CFGINF1 & SYSCFG_CP0CFGINF1_ITCM_SZ) >> 16U));
        } else {
            ret_tcm_info = (uint32_t)((uint32_t)((SYSCFG_CP0CFGINF1 & SYSCFG_CP0CFGINF1_DTCM_SZ) >> 24U));
        }
    }
    return ret_tcm_info;
}

/*!
    \brief      get core 0 processor configuration information, API ID: 0x003A
    \param[in]  none
    \param[out] none
    \retval     core processor configuration information
*/
uint32_t syscfg_cpu0_config_info_get(void)
{
    return (uint32_t)(SYSCFG_CP0CFGINF2 & BITS(0, 4));
}

#if defined (GD32A72XX) || defined (GD32A74XX)

/*!
    \brief      get core 1 processor ID, API ID: 0x003B
    \param[in]  none
    \param[out] none
    \retval     core processor ID
*/
uint32_t syscfg_cpu1_id_get(void)
{
    return SYSCFG_CP1ID;
}


/*!
    \brief      get core processor 1 number, API ID: 0x003C
    \param[in]  none
    \param[out] none
    \retval     core processor number
*/
uint8_t syscfg_cpu1_number_get(void)
{
    return SYSCFG_CP1NUM;
}

/*!
    \brief      get CPU 1 cache information, API ID: 0x003D
    \param[in]  cache_info
                only one parameter can be selected which are shown as below:
      \arg        ICACHE_INFO: I-Cache information
      \arg        DCACHE_INFO: D-Cache information
    \param[out] none
    \retval     CPU cache information
*/
uint32_t syscfg_cpu1_cache_info_get(uint32_t cache_info)
{
    uint32_t ret_cache_info = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CACHE_INFO(cache_info)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(61), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ICACHE_INFO == cache_info) {
            ret_cache_info = (uint32_t)((uint32_t)((SYSCFG_CP1CFGINF0 & BITS(16, 31)) >> 16U));
        } else {
            ret_cache_info = (uint32_t)(SYSCFG_CP1CFGINF0 & BITS(0, 15));
        }
    }
    return ret_cache_info;
}

/*!
    \brief      get CPU 1 TCM size information, API ID: 0x003E
    \param[in]  tcm_info
                only one parameter can be selected which are shown as below:
      \arg        ITCM_INFO: ITCM information
      \arg        DTCM_INFO: DTCM information
    \param[out] none
    \retval     TCM information
*/
uint32_t syscfg_cpu1_tcm_size_get(uint32_t tcm_info)
{
    uint32_t ret_tcm_info = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TCM_INFO(tcm_info)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(62), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(ITCM_INFO == tcm_info) {
            ret_tcm_info = (uint32_t)((uint32_t)((SYSCFG_CP1CFGINF1 & SYSCFG_CP1CFGINF1_ITCM_SZ) >> 16U));
        } else {
            ret_tcm_info = (uint32_t)((uint32_t)((SYSCFG_CP1CFGINF1 & SYSCFG_CP1CFGINF1_DTCM_SZ) >> 24U));
        }
    }
    return ret_tcm_info;
}

/*!
    \brief      get core 1 processor configuration information, API ID: 0x003F
    \param[in]  none
    \param[out] none
    \retval     core processor configuration information
*/
uint32_t syscfg_cpu1_config_info_get(void)
{
    return (uint32_t)(SYSCFG_CP1CFGINF2 & BITS(0, 4));
}

#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      get interrupt router interrupt flag, API ID: 0x0031
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  ir_cp_int
                only one parameter can be selected which are shown as below:
      \arg        INTROUTER_CP_INT_0: interrupt router core processer interrupt 0
      \arg        INTROUTER_CP_INT_1: interrupt router core processer interrupt 1
      \arg        INTROUTER_CP_INT_2: interrupt router core processer interrupt 2
      \arg        INTROUTER_CP_INT_3: interrupt router core processer interrupt 3
    \param[in]  int_flag
                only one parameter can be selected which are shown as below:
      \arg        INTROUTER_CP_INT_FLAG_CP1_CP0: CP1 to CP0 interrupt flag
      \arg        INTROUTER_CP_INT_FLAG_CP0_CP0: CP0 to CP0 interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_interrupt_router_interrupt_flag_get(uint8_t core_num, uint32_t ir_cp_int, uint32_t int_flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(48), ERR_PARAM_INVALID);
    } else if(NOT_IR_CP_INT(ir_cp_int)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(48), ERR_PARAM_INVALID);
    } else if(NOT_IR_CP_INT_FLAG(int_flag)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(48), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            /* CM7_0 interrupt router */
            if(0U != (REG32(SYSCFG + 0x00000300U + (uint32_t)(ir_cp_int * 0x08U)) & int_flag)) {
                reval = SET;
            } else {
                /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
            }
        } else {
            /* CM7_1 interrupt router */
            if(0U != (REG32(SYSCFG + 0x00000320U + (uint32_t)(ir_cp_int * 0x08U)) & int_flag)) {
                reval = SET;
            } else {
                /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear interrupt router interrupt flag, API ID: 0x0032
    \param[in]  core_num
                only one parameter can be selected which are shown as below:
      \arg        CM7_0: Cortex-M7 core 0
      \arg        CM7_1: Cortex-M7 core 1
    \param[in]  ir_cp_int
                only one parameter can be selected which are shown as below:
      \arg        INTROUTER_CP_INT_0: interrupt router core processer interrupt 0
      \arg        INTROUTER_CP_INT_1: interrupt router core processer interrupt 1
      \arg        INTROUTER_CP_INT_2: interrupt router core processer interrupt 2
      \arg        INTROUTER_CP_INT_3: interrupt router core processer interrupt 3
    \param[in]  int_flag
                only one parameter can be selected which are shown as below:
      \arg        INTROUTER_CP_INT_FLAG_CP1_CP0: CP1 to CP0 interrupt flag
      \arg        INTROUTER_CP_INT_FLAG_CP0_CP0: CP0 to CP0 interrupt flag
    \param[out] none
    \retval     none
*/
void syscfg_interrupt_router_interrupt_flag_clear(uint8_t core_num, uint32_t ir_cp_int, uint32_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CM7_NUM(core_num)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(50), ERR_PARAM_INVALID);
    } else if(NOT_IR_CP_INT(ir_cp_int)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(50), ERR_PARAM_INVALID);
    } else if(NOT_IR_CP_INT_FLAG(int_flag)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(50), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(CM7_0 == core_num) {
            /* CM7_0 interrupt router */
            REG32(SYSCFG + 0x00000300U + (uint32_t)(ir_cp_int * 0x08U)) |= int_flag;
        } else {
            /* CM7_1 interrupt router */
            REG32(SYSCFG + 0x00000320U + (uint32_t)(ir_cp_int * 0x08U)) |= int_flag;
        }
    }
}
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      get TMR error interrupt flag, API ID: 0x0033
    \param[in]  tmrerr_intflag
                only one parameter can be selected which are shown as below:
      \arg        TMRERR_INT_FLAG_FMUNMI: TMR fault interrupt flag of the FMU NMI interrupt flag enable
      \arg        TMRERR_INT_FLAG_CPEN: TMR fault interrupt flag of the CPU released
      \arg        TMRERR_INT_FLAG_MEMEXECR: TMR fault interrupt flag of the memory execution control register
      \arg        TMRERR_INT_FLAG_CPINT: TMR fault interrupt flag of the interrupt router CPn interrupt status register
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus syscfg_tmr_error_flag_get(uint32_t tmrerr_intflag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TMRERR_INT_FLAG(tmrerr_intflag)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(49), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (SYSCFG_TMRFCS & tmrerr_intflag)) {
            reval = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return reval;
}

/*!
    \brief      clear SYSCFG CPU flag, API ID: 0x0034
    \param[in]  nmi_flag
                only one parameter can be selected which are shown as below:
      \arg        SYSCFG_FLAG_CKMNMIERR: HXTAL clock monitor NMI error flag
      \arg        SYSCFG_FLAG_CPU0_WR_ABORT: CPU0 write abort on AHB slave flag
      \arg        SYSCFG_FLAG_CPU1_WR_ABORT: CPU1 write abort on AHB slave flag
    \param[out] none
    \retval     none
*/
void syscfg_cpu_flag_clear(uint32_t nmi_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_NMI_CLEAR_FLAG(nmi_flag)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(51), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(nmi_flag) {
        case SYSCFG_FLAG_CKMNMIERR:
            /* clear CKMNMIERR flag in SYSCFG_STAT register */
            SYSCFG_STAT |= SYSCFG_STAT_CKMNMIIF;
            break;
        case SYSCFG_FLAG_CPU0_WR_ABORT:
            /* clear WAS flag in SYSCFG_CPU0CS register */
            SYSCFG_CPU0CS |= SYSCFG_CPU0CS_WAS;
            break;
        default:
#if defined (GD32A72XX) || defined (GD32A74XX)
            /* clear WAS flag in SYSCFG_CPU1CS register */
            SYSCFG_CPU1CS |= SYSCFG_CPU1CS_WAS;
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
            break;
        }
    }
}

/*!
    \brief      clear TMR error interrupt flag, API ID: 0x0035
    \param[in]  tmrerr_intflag
                one or more parameters can be selected which are shown as below:
      \arg        TMRERR_INT_FLAG_FMUNMI: TMR fault interrupt flag of the FMU NMI interrupt flag enable
      \arg        TMRERR_INT_FLAG_CPEN: TMR fault interrupt flag of the CPU released
      \arg        TMRERR_INT_FLAG_MEMEXECR: TMR fault interrupt flag of the memory execution control register
      \arg        TMRERR_INT_FLAG_CPINT: TMR fault interrupt flag of the interrupt router CPn interrupt status register
    \param[out] none
    \retval     none
*/
void syscfg_tmr_error_int_flag_clear(uint32_t tmrerr_intflag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TMRERR_INT_FLAG(tmrerr_intflag)) {
        fw_debug_report_err(SYSCFG_MODULE_ID, API_ID(52), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SYSCFG_TMRFCS |= tmrerr_intflag;
    }
}
