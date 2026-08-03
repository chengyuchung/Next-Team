/*!
    \file  system_gd32a72xx.c
    \brief CMSIS Cortex-M7 Device Peripheral Access Layer Source File for
           GD32A7XX Device Series
*/

/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
 * Copyright (c) 2025, GigaDevice Semiconductor Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

#include "gd32a7xx.h"

#define __IRC48M          (IRC48M_VALUE)            /* internal 8 MHz RC oscillator frequency */
#define __HXTAL           (HXTAL_VALUE)             /* high speed crystal oscillator frequency */

//#define EVB_V15_LDO_RUN

#ifndef GD32A72XX_M7_1
#define VECT_TAB_OFFSET   (uint32_t)0x400U          /* vector table base offset */
#else
#define VECT_TAB_OFFSET   (uint32_t)0x00U           /* vector table base offset */
#endif

/* select a system clock by uncommenting the following line */
/* use IRC48M */
//#define __SYSTEM_CLOCK_IRC48M                            (uint32_t)(__IRC48M)
//#define __SYSTEM_CLOCK_96M_PLL_IRC48M                    (uint32_t)(96000000)
//#define __SYSTEM_CLOCK_120M_PLL_IRC48M                   (uint32_t)(120000000)
//#define __SYSTEM_CLOCK_160M_PLL_IRC48M                   (uint32_t)(160000000)

/* use HXTAL(CK_HXTAL = 25M)*/
//#define __SYSTEM_CLOCK_HXTAL                             (uint32_t)(__HXTAL)
//#define __SYSTEM_CLOCK_100M_PLL_HXTAL                    (uint32_t)(100000000)
//#define __SYSTEM_CLOCK_120M_PLL_HXTAL                    (uint32_t)(120000000)
#define __SYSTEM_CLOCK_160M_PLL_HXTAL                    (uint32_t)(160000000)



/* set the system clock frequency and declare the system clock configuration function */
#ifdef __SYSTEM_CLOCK_IRC48M 
uint32_t SystemCoreClock = __SYSTEM_CLOCK_IRC48M;
#ifdef SYSTEM_CLK_CFG
static void system_clock_48m_irc48m(void);
#endif /* SYSTEM_CLK_CFG */
#elif defined (__SYSTEM_CLOCK_96M_PLL_IRC48M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_96M_PLL_IRC48M;
#ifdef SYSTEM_CLK_CFG
static void system_clock_96m_pll_irc48m(void);
#endif /* SYSTEM_CLK_CFG */
#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC48M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLL_IRC48M;
#ifdef SYSTEM_CLK_CFG
static void system_clock_120m_pll_irc48m(void);
#endif /* SYSTEM_CLK_CFG */
#elif defined (__SYSTEM_CLOCK_160M_PLL_IRC48M)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_160M_PLL_IRC48M;
#ifdef SYSTEM_CLK_CFG
static void system_clock_160M_pll_irc48m(void);
#endif /* SYSTEM_CLK_CFG */

#elif defined (__SYSTEM_CLOCK_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_HXTAL;
#ifdef SYSTEM_CLK_CFG
static void system_clock_hxtal(void);
#endif /* SYSTEM_CLK_CFG */
#elif defined (__SYSTEM_CLOCK_100M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_100M_PLL_HXTAL;
#ifdef SYSTEM_CLK_CFG
static void system_clock_100m_pll_hxtal(void);
#endif /* SYSTEM_CLK_CFG */
#elif defined (__SYSTEM_CLOCK_120M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_120M_PLL_HXTAL;
#ifdef SYSTEM_CLK_CFG
static void system_clock_120M_pll_hxtal(void);
#endif /* SYSTEM_CLK_CFG */
#elif defined (__SYSTEM_CLOCK_160M_PLL_HXTAL)
uint32_t SystemCoreClock = __SYSTEM_CLOCK_160M_PLL_HXTAL;
#ifdef SYSTEM_CLK_CFG
static void system_clock_160M_pll_hxtal(void);
#endif /* SYSTEM_CLK_CFG */
#endif /* __SYSTEM_CLOCK_IRC48M */

#ifdef SYSTEM_CLK_CFG
/* configure the system clock */
static void system_clock_config(void);

static void _delay(volatile uint32_t cnt)
{
    while(cnt--);
}

#endif /* SYSTEM_CLK_CFG */

/*!
    \brief      setup the micro-controller system, initialize the system
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemInit(void)
{
    /* FPU settings */
#if (__FPU_PRESENT == 1U) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3UL << 10U * 2U) | (3UL << 11U * 2U)); /* set CP10 and CP11 Full Access */
#endif
#ifdef SYSTEM_CLK_CFG
    REG32(0x4900101C) |= (1<<13U);
    REG32(0x40007000) = 0x00010000U;
    RCU_APB2EN |= RCU_APB2EN_CFGEN;
    SYSCFG_SRAMCFG &= ~SYSCFG_SRAMCFG_SRAM_WAITSTATE;
    /* Unlock FMU, RCU, HWSEM, HSMIF, PMU, SYSCFG register */
    REG32(PRPU + 0x000U) = 0xA1B2C4U;
    REG32(PRPU + 0x064U) = 0xA1B2DDU;
    REG32(PRPU + 0x07CU) = 0xA1B2E3U;
    REG32(PRPU + 0x080U) = 0xA1B2E4U;
    REG32(PRPU + 0x0FCU) = 0xA1B303U;
    REG32(PRPU + 0x110U) = 0xA1B308U;

    /* reset the RCU clock configuration to the default reset state */
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    /* software delay to prevent the impact of Vcore fluctuations. It is strongly recommended to include it to avoid issues caused by self-removal. */
    _delay(50);
    /* reset HXTALSCAL, LCKMEN, PLLMEN, PLLEN, CKMEN and HXTALEN bits */
    RCU_CTL &= ~(RCU_CTL_PLLEN | RCU_CTL_CKMEN | RCU_CTL_HXTALEN | RCU_CTL_HXTALSCAL );
    /* disable all interrupts */
    RCU_INT = 0x00FF0000U;

    /* Reset CFG0,CFG1,CFG2,CFG3 registers */
    RCU_CFG0 = 0x00202400;
    RCU_CFG1 = 0x00000000U;
    RCU_CFG2 = 0x00000000U;
    RCU_CFG3 = 0x00000000U;
    /* reset HXTALBPS bit */
    RCU_CTL &= ~(RCU_CTL_HXTALBPS);

    /* configure HXTALSCAL according to HXTAL_VALUE */
    if(HXTAL_VALUE > 32000000U) {
        RCU_CTL |= HXTAL_SCALE_32M_TO_40M;
    }
    else if(HXTAL_VALUE > 16000000U) {
        RCU_CTL |= HXTAL_SCALE_16M_TO_32M;
    }
    else if(HXTAL_VALUE > 8000000U) {
        RCU_CTL |= HXTAL_SCALE_8M_TO_16M;
    } else {
       /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
#ifdef EVB_V15_LDO_RUN
    rcu_periph_clock_enable(RCU_GPIOL);
    gpio_mode_set(GPIOL, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO_PIN_1);
    pmu_base_control_enable();
    if(PMU_CFG_FREC == (PMU_CFG & PMU_CFG_FREC)){
        _delay(0xD0);
    }else{
        _delay(0x250);
    }
    while(SET == pmu_flag_get(PMU_FLAG_V15LVDSF));
    pmu_flag_clear(PMU_FLAG_V15LVDF);
    pmu_run_ldo_enable();
#endif /* EVB_V15_LDO_RUN */
    /* configure the system clock source, PLL Multiplier, AHB/APBx prescalers and Flash settings */
    system_clock_config();
#endif /* SYSTEM_CLK_CFG */

    /* clear FMU_FGTSSTAT1 Bit20/21 */
    FMU_FGTSSTAT(1) |= 0x00600000;

#ifdef VECT_TAB_SRAM
    nvic_vector_table_set(NVIC_VECTTAB_RAM, VECT_TAB_OFFSET);
#else
    nvic_vector_table_set(NVIC_VECTTAB_FLASH, VECT_TAB_OFFSET);
#endif
}

#ifdef SYSTEM_CLK_CFG
/*!
    \brief      configure the system clock
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_config(void)
{
#ifdef __SYSTEM_CLOCK_IRC48M
    system_clock_48m_irc48m();
#elif defined (__SYSTEM_CLOCK_96M_PLL_IRC48M)
    system_clock_96m_pll_irc48m();
#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC48M)
    system_clock_120m_pll_irc48m();
#elif defined (__SYSTEM_CLOCK_160M_PLL_IRC48M)
    system_clock_160M_pll_irc48m();

#elif defined (__SYSTEM_CLOCK_HXTAL)
    system_clock_hxtal();
#elif defined (__SYSTEM_CLOCK_100M_PLL_HXTAL)
    system_clock_100m_pll_hxtal();
#elif defined (__SYSTEM_CLOCK_120M_PLL_HXTAL)
    system_clock_120M_pll_hxtal();
#elif defined (__SYSTEM_CLOCK_160M_PLL_HXTAL)
    system_clock_160M_pll_hxtal();
#endif /* __SYSTEM_CLOCK_IRC48M */
}

#ifdef __SYSTEM_CLOCK_IRC48M
/*!
    \brief      configure the system clock to 48M by IRC48M
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_48m_irc48m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(1);

    /* enable PMU clock */
    RCU_APB1EN |= RCU_APB1EN_PMUEN;

    /* wait until IRC48M is stable or the startup time is longer than IRC48M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (PMU_LVCS & PMU_LVCS_IRC48MSTB);
    } while((0U == stab_flag) && (IRC48M_STARTUP_TIMEOUT != timeout));

        /* if fail */
    if(0U == (PMU_LVCS & PMU_LVCS_IRC48MSTB)) {
        while(1) {
        }
    }

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    reg_temp = RCU_CFG0;
    /* select IRC48M as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_IRC48M;
    RCU_CFG0 = reg_temp;

    /* wait until IRC48M is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_IRC48M) {
    }
}

#elif defined (__SYSTEM_CLOCK_96M_PLL_IRC48M)
/*!
    \brief      configure the system clock to 96M by PLL which selects IRC48M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_96m_pll_irc48m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(3);
    RCU_APB2EN |= RCU_APB2EN_CFGEN;
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_SRAM_WAITSTATE;

    /* enable PMU clock */
    RCU_APB1EN |= RCU_APB1EN_PMUEN;
    
    /* wait until IRC48M is stable or the startup time is longer than IRC48M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (PMU_LVCS & PMU_LVCS_IRC48MSTB);
    } while((0U == stab_flag) && (IRC48M_STARTUP_TIMEOUT != timeout));

        /* if fail */
    if(0U == (PMU_LVCS & PMU_LVCS_IRC48MSTB)) {
        while(1) {
        }
    }

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC48M/6) * 24 / 2 = 96 MHz */
    RCU_CFG1 &=  ~(RCU_CFG1_PREDV | RCU_CFG1_PLLDIVP);
    RCU_CFG1 |=  (RCU_PREDV_DIV6 | (1U<<3U));
    RCU_CFG0 &= ~(RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_7);
    RCU_CFG0 |= (RCU_PLLSRC_IRC48M | (24U<<17U));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_PLL_P) {
    }
}

#elif defined (__SYSTEM_CLOCK_120M_PLL_IRC48M)
/*!
    \brief      configure the system clock to 120M by PLL which selects IRC48M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120m_pll_irc48m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(4);
    RCU_APB2EN |= RCU_APB2EN_CFGEN;
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_SRAM_WAITSTATE;

    /* enable PMU clock */
    RCU_APB1EN |= RCU_APB1EN_PMUEN;

    /* wait until IRC48M is stable or the startup time is longer than IRC48M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (PMU_LVCS & PMU_LVCS_IRC48MSTB);
    } while((0U == stab_flag) && (IRC48M_STARTUP_TIMEOUT != timeout));

        /* if fail */
    if(0U == (PMU_LVCS & PMU_LVCS_IRC48MSTB)) {
        while(1) {
        }
    }

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC48M/6) * 90 / 6 = 120 MHz */
    RCU_CFG1 &=  ~(RCU_CFG1_PREDV | RCU_CFG1_PLLDIVP);
    RCU_CFG1 |=  (RCU_PREDV_DIV6 | (5U<<3U));
    RCU_CFG0 &= ~(RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_7);
    RCU_CFG0 |= (RCU_PLLSRC_IRC48M | (90U<<17U));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_PLL_P) {
    }
}

#elif defined (__SYSTEM_CLOCK_160M_PLL_IRC48M)
/*!
    \brief      configure the system clock to 160M by PLL which selects IRC48M as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_160M_pll_irc48m(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(5);
    RCU_APB2EN |= RCU_APB2EN_CFGEN;
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_SRAM_WAITSTATE;

    /* enable PMU clock */
    RCU_APB1EN |= RCU_APB1EN_PMUEN;

    /* wait until IRC48M is stable or the startup time is longer than IRC48M_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (PMU_LVCS & PMU_LVCS_IRC48MSTB);
    } while((0U == stab_flag) && (IRC48M_STARTUP_TIMEOUT != timeout));

        /* if fail */
    if(0U == (PMU_LVCS & PMU_LVCS_IRC48MSTB)) {
        while(1) {
        }
    }

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/1 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL = (CK_IRC48M/6) * 20 = 160 MHz */
    RCU_CFG1 &=  ~(RCU_CFG1_PREDV | RCU_CFG1_PLLDIVP);
    RCU_CFG1 |=  RCU_PREDV_DIV6 ;
    RCU_CFG0 &= ~(RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_7);
    RCU_CFG0 |= (RCU_PLLSRC_IRC48M | (20U<<17U));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_PLL_P) {
    }
}

#elif defined (__SYSTEM_CLOCK_HXTAL)
/*!
    \brief      configure the system clock to HXTAL
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(0);
    RCU_APB2EN |= RCU_APB2EN_CFGEN;
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_SRAM_WAITSTATE;

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    reg_temp = RCU_CFG0;
    /* select HXTAL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_HXTAL;
    RCU_CFG0 = reg_temp;

    /* wait until HXTAL is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_HXTAL) {
    }
}

#elif defined (__SYSTEM_CLOCK_100M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 100M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_100m_pll_hxtal(void)
{
    uint32_t timeout = 0U;
    uint32_t stab_flag = 0U;
    __IO uint32_t reg_temp;

    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(3);
    RCU_APB2EN |= RCU_APB2EN_CFGEN;
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_SRAM_WAITSTATE;

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL_P(CK_PLL_Q) = (HXTAL / 1) * 16 / 4= 100 MHz */
    RCU_CFG1 &=  ~(RCU_CFG1_PREDV | RCU_CFG1_PLLDIVP | RCU_CFG1_PLLDIVQ);
    RCU_CFG1 |=  (RCU_PREDV_DIV1 |(3U<<3U)| (3U<<9U));
    RCU_CFG0 &= ~(RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_7);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | (16U<<17U));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_PLL_P) {
    }
}
#elif defined (__SYSTEM_CLOCK_120M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 120M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_120M_pll_hxtal(void)
{
    uint32_t timeout;
    uint32_t stab_flag;
    __IO uint32_t reg_temp;

    timeout = 0U;
    
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(4);
    RCU_APB2EN |= RCU_APB2EN_CFGEN;
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_SRAM_WAITSTATE;

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL_P(CK_PLL_Q) = (HXTAL / 1) * 24 / 5 = 120 MHz */
    RCU_CFG1 &= ~(RCU_CFG1_PREDV | RCU_CFG1_PLLDIVP | RCU_CFG1_PLLDIVQ);
    RCU_CFG1 |= (RCU_PREDV_DIV1 | (4U<<3U)| (4U<<9U));
    RCU_CFG0 &= ~(RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_7);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | (24U<<17U));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_PLL_P) {
    }
}
#elif defined (__SYSTEM_CLOCK_160M_PLL_HXTAL)
/*!
    \brief      configure the system clock to 160M by PLL which selects HXTAL as its clock source
    \param[in]  none
    \param[out] none
    \retval     none
*/
static void system_clock_160M_pll_hxtal(void)
{
    uint32_t timeout;
    uint32_t stab_flag;
    __IO uint32_t reg_temp;
    
    timeout = 0U;
    
    /* enable HXTAL */
    RCU_CTL |= RCU_CTL_HXTALEN;

    /* wait until HXTAL is stable or the startup time is longer than HXTAL_STARTUP_TIMEOUT */
    do {
        timeout++;
        stab_flag = (RCU_CTL & RCU_CTL_HXTALSTB);
    } while((0U == stab_flag) && (HXTAL_STARTUP_TIMEOUT != timeout));

    /* if fail */
    if(0U == (RCU_CTL & RCU_CTL_HXTALSTB)) {
        while(1) {
        }
    }

    FMC_WS = (FMC_WS & (~FMC_WS_WSCNT)) | WS_WSCNT(5);
    RCU_APB2EN |= RCU_APB2EN_CFGEN;
    SYSCFG_SRAMCFG |= SYSCFG_SRAMCFG_SRAM_WAITSTATE;

    /* AHB = SYSCLK */
    RCU_CFG0 |= RCU_AHB_CKSYS_DIV1;
    /* APB2 = AHB/2 */
    RCU_CFG0 |= RCU_APB2_CKAHB_DIV2;
    /* APB1 = AHB/2 */
    RCU_CFG0 |= RCU_APB1_CKAHB_DIV2;

    /* CK_PLL_P(CK_PLL_Q) = (HXTAL / 1) * 32 / 5 = 160 MHz */
    RCU_CFG1 &=  ~(RCU_CFG1_PREDV | RCU_CFG1_PLLDIVP | RCU_CFG1_PLLDIVQ);
    RCU_CFG1 |=  (RCU_PREDV_DIV1 | (4U<<3U) | (4U<<9U));
    RCU_CFG0 &= ~(RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_7);
    RCU_CFG0 |= (RCU_PLLSRC_HXTAL | (32U<<17U));

    /* enable PLL */
    RCU_CTL |= RCU_CTL_PLLEN;

    /* wait until PLL is stable */
    while(0U == (RCU_CTL & RCU_CTL_PLLSTB)) {
    }

    reg_temp = RCU_CFG0;
    /* select PLL as system clock */
    reg_temp &= ~RCU_CFG0_SCS;
    reg_temp |= RCU_CKSYSSRC_PLLP;
    RCU_CFG0 = reg_temp;

    /* wait until PLL is selected as system clock */
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_PLL_P) {
    }
}
#endif /* __SYSTEM_CLOCK_IRC48M */

/*!
    \brief      update the SystemCoreClock with current core clock retrieved from CPU registers
    \param[in]  none
    \param[out] none
    \retval     none
*/
void SystemCoreClockUpdate(void)
{
    uint32_t sws;
    uint32_t pllsel, pllmf, ck_src, idx, clk_exp;
    uint32_t predv0, plldivp;

    /* exponent of AHB, APB1 and APB2 clock divider */
    uint8_t ahb_exp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8};

    sws = RCU_CFG0 & RCU_CFG0_SCSS;
    switch(sws) {
    /* IRC48M is selected as CK_SYS */
    case RCU_SCSS_IRC48M:
        SystemCoreClock = IRC48M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case RCU_SCSS_HXTAL:
        SystemCoreClock = HXTAL_VALUE;
        break;
    /* PLL is selected as CK_SYS */
    case RCU_SCSS_PLL_P:
        /* PLL clock source selection, HXTAL or IRC48M */
        pllsel = (RCU_CFG0 & RCU_CFG0_PLLSEL);

        if(RCU_PLLSRC_HXTAL == pllsel) {
            /* PLL clock source is HXTAL */
            ck_src = HXTAL_VALUE;
            predv0 = (RCU_CFG1 & RCU_CFG1_PREDV);
            if (predv0 != 0U) {
                /* Apply the pre-division factor */
                ck_src /= predv0;
            }
        } else {
            /* PLL clock source is IRC48M */
            ck_src = IRC48M_VALUE;
            predv0 = (RCU_CFG1 & RCU_CFG1_PREDV);
            if (predv0 != 0U) {
                /* Apply the pre-division factor */
                ck_src /= predv0;
            }
        }
        plldivp = GET_BITS(RCU_CFG1, 3U, 8U);
        /* PLL multiplication factor */
        pllmf = GET_BITS(RCU_CFG0, 17, 23);
        if((RCU_CFG0 & RCU_CFG0_PLLMF_7) != 0U) {
           pllmf += 128U;
        }

        SystemCoreClock = ck_src * pllmf / (plldivp + 1U);

        break;
    /* IRC48M is selected as CK_SYS */
    default:
        SystemCoreClock = IRC48M_VALUE;
        break;
    }

    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4, 7);
    clk_exp = ahb_exp[idx];
    SystemCoreClock >>= clk_exp;
}

#endif /* SYSTEM_CLK_CFG */

#ifdef __FIRMWARE_VERSION_DEFINE
/*!
    \brief      get firmware version
    \param[in]  none
    \param[out] none
    \retval     firmware version
*/
uint32_t gd32a7xx_firmware_version_get(void)
{
    return GD32A7XX_STDPERIPH_VERSION;
}
#endif /* __FIRMWARE_VERSION_DEFINE */
