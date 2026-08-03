/*!
    \file    gd32a7xx_rcu.c
    \brief   RCU driver

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

#include "gd32a7xx_rcu.h"

/* define startup timeout count */
#define OSC_STARTUP_TIMEOUT         ((uint32_t)0x000FFFFFU)
#define LXTAL_STARTUP_TIMEOUT       ((uint32_t)0x03FFFFFFU)

/* RCU IRC48M adjust value mask and offset*/
#define RCU_IRC48M_ADJUST_MASK       ((uint8_t)0x1FU)
#define RCU_IRC48M_ADJUST_OFFSET     ((uint32_t)3U)

/*!
    \brief      deinitialize the RCU (API_ID(0x0001U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_deinit(void)
{
    RCU_CFG0 &= ~RCU_CFG0_SCS;
    while((RCU_CFG0 & RCU_CFG0_SCSS) != RCU_SCSS_IRC48M) {
    }
    /* reset CTL register */
    RCU_CTL &= ~(RCU_CTL_PLLEN | RCU_CTL_CKMEN | RCU_CTL_HXTALEN | RCU_CTL_HXTALSCAL);
    RCU_CTL &= ~RCU_CTL_HXTALBPS;
    /* reset CFG0 register */
    RCU_CFG0 = 0x00202400U;
    /* reset INT and CFG1 and CFG2 register */
    RCU_INT = 0x00000000U;
    RCU_CFG1 = 0x00000000U;
    RCU_CFG2 = 0x00000000U;
    RCU_CFG3 = 0x00000000U;
    RCU_PLLFRA = 0x00000000U;
    RCU_PLLFRA = 0x00000000U;
    RCU_PLLSSCTL = 0x00000000U;
    /* reset RCTL register */
    RCU_SYSRSTSTAT |= 0x60041759U;
    RCU_BUSCTL = 0x00000000U;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_SUBSERSTAT = 0xE0110EDFU;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */   
#if defined (GD32A711X_A712X)   
    RCU_SUBSERSTAT = 0xE011065DU;
#endif /* defined(GD32A711X_A712X) */
    RCU_SUBSRPACTL = 0x00000000U;
    RCU_SUBSRMUCNT = 0xFU;
    RCU_SYSRSTUCNT = 0xFU;
    RCU_SUBSRMUTH = 0xFU;
    RCU_SYSMRUTH = 0xFU;
    RCU_SUBSRTO = 0x00000001U;
    RCU_AHBRST = 0x00000000U;
    RCU_APB1RST = 0x00000000U;
    RCU_APB2RST = 0x00000000U;
    RCU_APB2RST_ADD = 0x00000000U;
    RCU_PORSTAT0 = 0xFFFFFFFFU;
    RCU_PORSTAT1 = 0xFFFFFFFFU;
    RCU_PORSTAT2 = 0xFFFFFFFFU;
    RCU_PORSTAT3 = 0xFFFFFFFFU;
}

/*!
    \brief      enable the peripherals clock (API_ID(0x0002U))
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg    RCU_GPIOA: GPIOA clock
      \arg    RCU_GPIOB: GPIOB clock
      \arg    RCU_GPIOC: GPIOC clock
      \arg    RCU_GPIOD: GPIOD clock
      \arg    RCU_GPIOE: GPIOE clock
      \arg    RCU_GPIOF: GPIOF clock
      \arg    RCU_GPIOG: GPIOG clock
      \arg    RCU_GPIOH: GPIOH clock
      \arg    RCU_GPIOI: GPIOI clock
      \arg    RCU_GPIOJ: GPIOJ clock
      \arg    RCU_GPIOK: GPIOK clock
      \arg    RCU_GPIOL: GPIOL clock
      \arg    RCU_GPIOM: GPIOM clock
      \arg    RCU_GPION: GPION clock
      \arg    RCU_DMA0: DMA0 clock
      \arg    RCU_DMA1: DMA1 clock
      \arg    RCU_DMAMUX: DMAMUX clock
      \arg    RCU_QSPI: QSPI clock
      \arg    RCU_CRC: CRC clock
      \arg    RCU_MFCOM: MFCOM clock (not for GD32A711X_A712X)
      \arg    RCU_MCMUA: MUA clock (not for GD32A711X_A712X)
      \arg    RCU_MCMUB: MUB clock (not for GD32A711X_A712X)
      \arg    RCU_HWSEM: HWSEM clock (not for GD32A711X_A712X)
      \arg    RCU_HSMIF: HSMIF clock
      \arg    RCU_FMU: FMU clock
      \arg    RCU_IRM: IRM clock
      \arg    RCU_IOC: IOC clock (not for GD32A711X_A712X)
      \arg    RCU_STCM: STCM clock
      \arg    RCU_MTC: MTC clock
      \arg    RCU_SYSCFG: SYSCFG clock
      \arg    RCU_LINFLEXD0: LINFlexD0 clock
      \arg    RCU_LINFLEXD1: LINFlexD1 clock
      \arg    RCU_LINFLEXD2: LINFlexD2 clock
      \arg    RCU_LINFLEXD3: LINFlexD3 clock
      \arg    RCU_LINFLEXD4: LINFlexD4 clock
      \arg    RCU_LINFLEXD5: LINFlexD5 clock
      \arg    RCU_TRIGSEL: TRIGSEL clock
      \arg    RCU_ADC0: ADC0 clock
      \arg    RCU_ADC1: ADC1 clock
      \arg    RCU_TIMER0:TIMER0 clock
      \arg    RCU_SPI0: SPI0 clock
      \arg    RCU_TIMER7: TIMER7 clock
      \arg    RCU_SPI4: SPI4 clock
      \arg    RCU_SPI5: SPI5 clock
      \arg    RCU_ADC2: ADC2 clock (not for GD32A711X_A712X)
      \arg    RCU_TIMER19: TIMER19 clock
      \arg    RCU_TIMER1: TIMER1 clock
      \arg    RCU_TIMER5: TIMER5 clock
      \arg    RCU_TIMER62: TIMER62 clock
      \arg    RCU_CMP1: CMP1 clock
      \arg    RCU_SPI1: SPI1 clock
      \arg    RCU_CMP0: CMP0 clock
      \arg    RCU_TIMER20: TIMER20 clock
      \arg    RCU_TIMER2: TIMER2 clock
      \arg    RCU_TIMER60: TIMER60 clock
      \arg    RCU_TIMER6: TIMER6 clock
      \arg    RCU_WWDGT0: WWDGT0 clock
      \arg    RCU_FWDGT0: FWDGT0 clock
      \arg    RCU_SPI6: SPI6 clock (not for GD32A711X_A712X)
      \arg    RCU_SPI7: SPI7 clock (not for GD32A711X_A712X)
      \arg    RCU_I2C0: I2C0 clock
      \arg    RCU_I2C1: I2C1 clock
      \arg    RCU_BKP: BKP clock
      \arg    RCU_PMU: PMU clock
      \arg    RCU_DAC0: DAC clock
      \arg    RCU_ENET: ENET clock (not for GD32A711X_A712X)
      \arg    RCU_TIMER61:   ENET clock
      \arg    RCU_TIMER63:   TIMER63 clock
      \arg    RCU_SENT: SENT clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD6: RCU_LINFlexD6 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD7: RCU_LINFlexD7 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD8: RCU_LINFlexD8 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD9: RCU_LINFlexD9 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD10: RCU_LINFlexD10 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD11: RCU_LINFlexD11 clock (not for GD32A711X_A712X)
      \arg    RCU_DAC1: DAC1 clock
      \arg    RCU_WWDGT1:WWDGT1 clock (not for GD32A711X_A712X)
      \arg    RCU_FWDGT1:FWDGT1 clock (not for GD32A711X_A712X)
      \arg    RCU_SPI2: SPI2 clock
      \arg    RCU_SPI3: SPI3 clock
      \arg    RCU_CLTCFG: CLTCFG clock
      \arg    RCU_RTC: RTC clock
      \arg    RCU_DTM_CAN0: DTM_CAN0 clock
      \arg    RCU_DTM_CAN1: DTM_CAN1 clock
      \arg    RCU_DTM_CAN2: DTM_CAN2 clock
      \arg    RCU_DTM_CAN3: DTM_CAN3 clock
      \arg    RCU_DTM_CAN4: DTM_CAN4 clock
      \arg    RCU_DTM_CAN5: DTM_CAN5 clock
      \arg    RCU_DTM_CAN6: DTM_CAN6 clock
      \arg    RCU_DTM_CAN7: DTM_CAN7 clock 
      \arg    RCU_CM7_0: CM7_0 clock
      \arg    RCU_CM7_1: CM7_1 clock (not for GD32A711X_A712X / GD32A714X)
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_enable(rcu_periph_enum periph)
{
    RCU_CCTL_REG_VAL(periph) |= BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      disable the peripherals clock (API_ID(0x0003U))
    \param[in]  periph: RCU peripherals, refer to rcu_periph_enum
                only one parameter can be selected which is shown as below:
      \arg    RCU_GPIOA: GPIOA clock
      \arg    RCU_GPIOB: GPIOB clock
      \arg    RCU_GPIOC: GPIOC clock
      \arg    RCU_GPIOD: GPIOD clock
      \arg    RCU_GPIOE: GPIOE clock
      \arg    RCU_GPIOF: GPIOF clock
      \arg    RCU_GPIOG: GPIOG clock
      \arg    RCU_GPIOH: GPIOH clock
      \arg    RCU_GPIOI: GPIOI clock
      \arg    RCU_GPIOJ: GPIOJ clock
      \arg    RCU_GPIOK: GPIOK clock
      \arg    RCU_GPIOL: GPIOL clock
      \arg    RCU_GPIOM: GPIOM clock
      \arg    RCU_GPION: GPION clock
      \arg    RCU_DMA0: DMA0 clock
      \arg    RCU_DMA1: DMA1 clock
      \arg    RCU_DMAMUX: DMAMUX clock
      \arg    RCU_QSPI: QSPI clock
      \arg    RCU_CRC: CRC clock
      \arg    RCU_MFCOM: MFCOM clock (not for GD32A711X_A712X)
      \arg    RCU_MCMUA: MCMUA clock (not for GD32A711X_A712X)
      \arg    RCU_MCMUB: MCMUB clock (not for GD32A711X_A712X)
      \arg    RCU_HWSEM: HWSEM clock (not for GD32A711X_A712X)
      \arg    RCU_HSMIF: HSMIF clock
      \arg    RCU_FMU: FMU clock
      \arg    RCU_IRM: IRM clock
      \arg    RCU_IOC: IOC clock (not for GD32A711X_A712X)
      \arg    RCU_STCM: STCM clock
      \arg    RCU_MTC: MTC clock
      \arg    RCU_SYSCFG: SYSCFG clock
      \arg    RCU_LINFLEXD0: LINFlexD0 clock
      \arg    RCU_LINFLEXD1: LINFlexD1 clock
      \arg    RCU_LINFLEXD2: LINFlexD2 clock
      \arg    RCU_LINFLEXD3: LINFlexD3 clock
      \arg    RCU_LINFLEXD4: LINFlexD4 clock
      \arg    RCU_LINFLEXD5: LINFlexD5 clock
      \arg    RCU_TRIGSEL: TRIGSEL clock
      \arg    RCU_ADC0: ADC0 clock
      \arg    RCU_ADC1: ADC1 clock
      \arg    RCU_TIMER0:TIMER0 clock
      \arg    RCU_SPI0: SPI0 clock
      \arg    RCU_TIMER7: TIMER7 clock
      \arg    RCU_SPI4: SPI4 clock
      \arg    RCU_SPI5: SPI5 clock
      \arg    RCU_ADC2: ADC2 clock (not for GD32A711X_A712X)
      \arg    RCU_TIMER19: TIMER19 clock
      \arg    RCU_TIMER1: TIMER1 clock
      \arg    RCU_TIMER5: TIMER5 clock
      \arg    RCU_TIMER62: TIMER62 clock
      \arg    RCU_CMP1: CMP1 clock
      \arg    RCU_SPI1: SPI1 clock
      \arg    RCU_CMP0: CMP0 clock
      \arg    RCU_TIMER20: TIMER20 clock
      \arg    RCU_TIMER2: TIMER2 clock
      \arg    RCU_TIMER60: TIMER60 clock
      \arg    RCU_TIMER6: TIMER6 clock
      \arg    RCU_WWDGT0: WWDGT0 clock
      \arg    RCU_FWDGT0: FWDGT0 clock
      \arg    RCU_SPI6: SPI6 clock (not for GD32A711X_A712X)
      \arg    RCU_SPI7: SPI7 clock (not for GD32A711X_A712X)
      \arg    RCU_I2C0: I2C0 clock
      \arg    RCU_I2C1: I2C1 clock
      \arg    RCU_BKP: BKP clock
      \arg    RCU_PMU: PMU clock
      \arg    RCU_DAC0: DAC clock
      \arg    RCU_ENET: ENET clock (not for GD32A711X_A712X)
      \arg    RCU_TIMER61:   ENET clock
      \arg    RCU_TIMER63:   TIMER63 clock
      \arg    RCU_LINFLEXD6: LIN6 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD7: LIN7 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD8: LIN8 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD9: LIN9 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD10: LIN10 clock (not for GD32A711X_A712X)
      \arg    RCU_LINFLEXD11: LIN11 clock (not for GD32A711X_A712X)
      \arg    RCU_DAC1: DAC1 clock
      \arg    RCU_WWDGT1:WWDGT1 clock (not for GD32A711X_A712X)
      \arg    RCU_FWDGT1:FWDGT1 clock (not for GD32A711X_A712X)
      \arg    RCU_SPI2: SPI2 clock
      \arg    RCU_SPI3: SPI3 clock
      \arg    RCU_CLTCFG: CLTCFG clock
      \arg    RCU_RTC: RTC clock
      \arg    RCU_DTM_CAN0: DTM_CAN0 clock
      \arg    RCU_DTM_CAN1: DTM_CAN1 clock
      \arg    RCU_DTM_CAN2: DTM_CAN2 clock
      \arg    RCU_DTM_CAN3: DTM_CAN3 clock
      \arg    RCU_DTM_CAN4: DTM_CAN4 clock
      \arg    RCU_DTM_CAN5: DTM_CAN5 clock
      \arg    RCU_DTM_CAN6: DTM_CAN6 clock
      \arg    RCU_DTM_CAN7: DTM_CAN7 clock
      \arg    RCU_CM7_0: CM7_0 clock
      \arg    RCU_CM7_1: CM7_1 clock (not for GD32A711X_A712X / GD32A714X)
    \param[out] none
    \retval     none
*/
void rcu_periph_clock_disable(rcu_periph_enum periph)
{
    RCU_CCTL_REG_VAL(periph) &= ~BIT(RCU_BIT_POS(periph));
}

/*!
    \brief      reset the peripherals (API_ID(0x0004U))
    \param[in]  periph_reset: RCU peripherals reset, refer to rcu_periph_reset_enum
                only one parameter can be selected which is shown as below:
      \arg    RCU_GPIOARST: GPIOA reset
      \arg    RCU_GPIOBRST: GPIOB reset
      \arg    RCU_GPIOCRST: GPIOC reset
      \arg    RCU_GPIODRST: GPIOD reset
      \arg    RCU_GPIOERST: GPIOE reset
      \arg    RCU_GPIOFRST: GPIOF reset
      \arg    RCU_GPIOGRST: GPIOG reset
      \arg    RCU_GPIOHRST: GPIOH reset
      \arg    RCU_GPIOIRST: GPIOI reset
      \arg    RCU_GPIOJRST: GPIOJ reset
      \arg    RCU_GPIOKRST: GPIOK reset
      \arg    RCU_GPIOLRST: GPIOL reset
      \arg    RCU_GPIOMRST: GPIOM reset
      \arg    RCU_GPIONRST: GPION reset
      \arg    RCU_DMA0RST: DMA0 reset
      \arg    RCU_DMA1RST: DMA1 reset
      \arg    RCU_DMAMUXRST: DMAMUX reset
      \arg    RCU_QSPIRST: QSPI reset
      \arg    RCU_CRCRST: CRC reset
      \arg    RCU_MFCOMRST: MFCOM reset (not for GD32A711X_A712X)
      \arg    RCU_MCMUARST: MCMUA reset (not for GD32A711X_A712X)
      \arg    RCU_MCMUBRST: MCMUB reset (not for GD32A711X_A712X)
      \arg    RCU_HWSEMRST: HWSEM reset (not for GD32A711X_A712X)
      \arg    RCU_HSMIFRST: HSMIF reset
      \arg    RCU_IRMRST: IRM reset
      \arg    RCU_IOCRST: IOC reset (not for GD32A711X_A712X)
      \arg    RCU_STCMRST: STCM reset
      \arg    RCU_MTCRST: MTC reset
      \arg    RCU_SYSCFGRST: SYSCFG reset
      \arg    RCU_LINFLEXD0RST: LINFlexD0 reset
      \arg    RCU_LINFLEXD1RST: LINFlexD1 reset
      \arg    RCU_LINFLEXD2RST: LINFlexD2 reset
      \arg    RCU_LINFLEXD3RST: LINFlexD3 reset
      \arg    RCU_LINFLEXD4RST: LINFlexD4 reset
      \arg    RCU_LINFLEXD5RST: LINFlexD5 reset
      \arg    RCU_ADC0RST: ADC0 reset
      \arg    RCU_ADC1RST: ADC1 reset
      \arg    RCU_TIMER0RST:TIMER0 reset
      \arg    RCU_SPI0RST: SPI0 reset
      \arg    RCU_TIMER7RST: TIMER7 reset
       \arg    RCU_SPI4RST: SPI4 reset
      \arg    RCU_SPI5RST: SPI5 reset
      \arg    RCU_ADC2RST: ADC2 reset (not for GD32A711X_A712X)
      \arg    RCU_TIMER19RST: TIMER19 reset
      \arg    RCU_TIMER1RST: TIMER1 reset
      \arg    RCU_TIMER5RST: TIMER5 reset
      \arg    RCU_TIMER62RST:TIMER62 reset
      \arg    RCU_CMP1RST: CMP1 reset
      \arg    RCU_SPI1RST: SPI1 reset
      \arg    RCU_CMP0RST: CMP0 reset
      \arg    RCU_TIMER20RST: TIMER20 reset
      \arg    RCU_TIMER2RST: TIMER2 reset
      \arg    RCU_TIMER60RST: TIMER60 reset
      \arg    RCU_TIMER6RST:TIMER6 reset
      \arg    RCU_WWDGT0RST:WWDGT0 reset
      \arg    RCU_FWDGT0RST:FWDGT0 reset
      \arg    RCU_SPI6RST: SPI6 reset (not for GD32A711X_A712X)
      \arg    RCU_SPI7RST: SPI7 reset (not for GD32A711X_A712X)
      \arg    RCU_I2C0RST: I2C0 reset
      \arg    RCU_I2C1RST: I2C1 reset
      \arg    RCU_BKPRST: BKP reset
      \arg    RCU_DAC0RST: DAC0 reset
      \arg    RCU_ENETRST: ENET reset (not for GD32A711X_A712X)
      \arg    RCU_TIMER61RST: TIMER61 reset
      \arg    RCU_TIMER63RST: TIMER63 reset
      \arg    RCU_SENTRST: SENT reset (not for GD32A711X_A712X)
      \arg    RCU_LIN6RST: LIN6 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN7RST: LIN7 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN8RST: LIN8 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN9RST: LIN9 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN10RST: LIN10 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN11RST: LIN11 reset (not for GD32A711X_A712X)
      \arg    RCU_DAC1RST: DAC1 reset
      \arg    RCU_WWDGT1RST:WWDGT1 reset (not for GD32A711X_A712X)
      \arg    RCU_FWDGT1RST:WWDGT1 reset (not for GD32A711X_A712X)
      \arg    RCU_SPI2RST: SPI2 reset
      \arg    RCU_SPI3RST: SPI3 reset
      \arg    RCU_CLTCFGRST: CLTCFG reset (not for GD32A711X_A712X)
      \arg    RCU_CAN0RST: CAN0 cluster reset
      \arg    RCU_CAN1RST: CAN1 cluster reset
      \arg    RCU_CAN2RST: CAN2 cluster reset
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset)
{
    RCU_RCTL_REG_VAL(periph_reset) |= BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      disable reset the peripheral (API_ID(0x0005U))
    \param[in]  periph_reset: RCU peripherals reset, refer to rcu_periph_reset_enum
                only one parameter can be selected which is shown as below:
      \arg    RCU_GPIOARST: GPIOA reset
      \arg    RCU_GPIOBRST: GPIOB reset
      \arg    RCU_GPIOCRST: GPIOC reset
      \arg    RCU_GPIODRST: GPIOD reset
      \arg    RCU_GPIOERST: GPIOE reset
      \arg    RCU_GPIOFRST: GPIOF reset
      \arg    RCU_GPIOGRST: GPIOG reset
      \arg    RCU_GPIOHRST: GPIOH reset
      \arg    RCU_GPIOIRST: GPIOI reset
      \arg    RCU_GPIOJRST: GPIOJ reset
      \arg    RCU_GPIOKRST: GPIOK reset
      \arg    RCU_GPIOLRST: GPIOL reset
      \arg    RCU_GPIOMRST: GPIOM reset
      \arg    RCU_GPIONRST: GPION reset
      \arg    RCU_DMA0RST: DMA0 reset
      \arg    RCU_DMA1RST: DMA1 reset
      \arg    RCU_DMAMUXRST: DMAMUX reset
      \arg    RCU_QSPIRST: QSPI reset
      \arg    RCU_CRCRST: CRC reset
      \arg    RCU_MFCOMRST: MFCOM reset (not for GD32A711X_A712X)
      \arg    RCU_MCMUARST: MCMUA reset (not for GD32A711X_A712X)
      \arg    RCU_MCMUBRST: MCMUB reset (not for GD32A711X_A712X)
      \arg    RCU_HWSEMRST: HWSEM reset (not for GD32A711X_A712X)
      \arg    RCU_HSMIFRST: HSMIF reset
      \arg    RCU_IRMRST: IRM reset
      \arg    RCU_IOCRST: IOC reset (not for GD32A711X_A712X)
      \arg    RCU_STCMRST: STCM reset
      \arg    RCU_MTCRST: MTC reset
      \arg    RCU_SYSCFGRST: SYSCFG reset
      \arg    RCU_LINFLEXD0RST: LINFlexD0 reset
      \arg    RCU_LINFLEXD1RST: LINFlexD1 reset
      \arg    RCU_LINFLEXD2RST: LINFlexD2 reset
      \arg    RCU_LINFLEXD3RST: LINFlexD3 reset
      \arg    RCU_LINFLEXD4RST: LINFlexD4 reset
      \arg    RCU_LINFLEXD5RST: LINFlexD5 reset
      \arg    RCU_ADC0RST: ADC0 reset
      \arg    RCU_ADC1RST: ADC1 reset
      \arg    RCU_TIMER0RST:TIMER0 reset
      \arg    RCU_SPI0RST: SPI0 reset
      \arg    RCU_TIMER7RST: TIMER7 reset
      \arg    RCU_SPI4RST: SPI4 reset
      \arg    RCU_SPI5RST: SPI5 reset
      \arg    RCU_ADC2RST: ADC2 reset (not for GD32A711X_A712X)
      \arg    RCU_TIMER19RST: TIMER19 reset
      \arg    RCU_TIMER1RST: TIMER1 reset
      \arg    RCU_TIMER5RST: TIMER5 reset
      \arg    RCU_TIMER62RST:TIMER62 reset
      \arg    RCU_CMP1RST: CMP1 reset
      \arg    RCU_SPI1RST: SPI1 reset
      \arg    RCU_CMP0RST: CMP0 reset
      \arg    RCU_TIMER20RST: TIMER20 reset
      \arg    RCU_TIMER2RST: TIMER2 reset
      \arg    RCU_TIMER60RST: TIMER60 reset
      \arg    RCU_TIMER6RST:TIMER6 reset
      \arg    RCU_WWDGT0RST:WWDGT0 reset
      \arg    RCU_FWDGT0RST:FWDGT0 reset
      \arg    RCU_SPI6RST: SPI6 reset (not for GD32A711X_A712X)
      \arg    RCU_SPI7RST: SPI7 reset (not for GD32A711X_A712X)
      \arg    RCU_I2C0RST: I2C0 reset
      \arg    RCU_I2C1RST: I2C1 reset
      \arg    RCU_BKPRST: BKP reset
      \arg    RCU_DAC0RST: DAC0 reset
      \arg    RCU_ENETRST: ENET reset (not for GD32A711X_A712X)
      \arg    RCU_TIMER61RST: TIMER61 reset
      \arg    RCU_TIMER63RST: TIMER63 reset
      \arg    RCU_SENTRST: SENT reset (not for GD32A711X_A712X)
      \arg    RCU_LIN6RST: LIN6 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN7RST: LIN7 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN8RST: LIN8 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN9RST: LIN9 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN10RST: LIN10 reset (not for GD32A711X_A712X)
      \arg    RCU_LIN11RST: LIN11 reset (not for GD32A711X_A712X)
      \arg    RCU_DAC1RST: DAC1 reset
      \arg    RCU_WWDGT1RST:WWDGT1 reset (not for GD32A711X_A712X)
      \arg    RCU_FWDGT1RST:WWDGT1 reset (not for GD32A711X_A712X)
      \arg    RCU_SPI2RST: SPI2 reset
      \arg    RCU_SPI3RST: SPI3 reset
      \arg    RCU_CLTCFGRST: CLTCFG reset (not for GD32A711X_A712X)
      \arg    RCU_CAN0RST: CAN0 cluster reset
      \arg    RCU_CAN1RST: CAN1 cluster reset
      \arg    RCU_CAN2RST: CAN2 cluster reset
    \param[out] none
    \retval     none
*/
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset)
{
    RCU_RCTL_REG_VAL(periph_reset) &= ~BIT(RCU_BIT_POS(periph_reset));
}

/*!
    \brief      configure the system clock source (API_ID(0x0006U))
    \param[in]  ck_sys: system clock source select
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKSYSSRC_IRC48M: select CK_IRC48M as the CK_SYS source
      \arg        RCU_CKSYSSRC_HXTAL: select CK_HXTAL as the CK_SYS source
      \arg        RCU_CKSYSSRC_PLLP: select CK_PLLP as the CK_SYS source
    \param[out] none
    \retval     none
*/
void rcu_system_clock_source_config(uint32_t ck_sys)
{
    uint32_t reg;

    reg = RCU_CFG0;
    /* reset the SCS bits and set according to ck_sys */
    reg &= ~RCU_CFG0_SCS;
    RCU_CFG0 = (reg | ck_sys);

}

/*!
    \brief      get the system clock source (API_ID(0x0007U))
    \param[in]  none
    \param[out] none
    \retval     ck_sys: which clock is selected as CK_SYS source
      \arg        RCU_SCSS_IRC48M: CK_IRC48M is selected as the CK_SYS source
      \arg        RCU_SCSS_HXTAL: CK_HXTAL is selected as the CK_SYS source
      \arg        RCU_SCSS_PLL_P: CK_PLL_P is selected as the CK_SYS source
*/
uint32_t rcu_system_clock_source_get(void)
{
    uint32_t ck_sys = 0U;
    switch(RCU_CFG0 & RCU_CFG0_SCSS) {
    case RCU_SCSS_IRC48M:
        ck_sys = RCU_SCSS_IRC48M;
        break;
    case RCU_SCSS_HXTAL:
        ck_sys = RCU_SCSS_HXTAL;
        break;
    case RCU_SCSS_PLL_P:
        ck_sys = RCU_SCSS_PLL_P;
        break;
    default:
        break;
    }
    return ck_sys;
}

/*!
    \brief      configure the AHB clock prescaler selection (API_ID(0x0008U))
    \param[in]  ck_ahb: AHB clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_AHB_CKSYS_DIVx, x=1, 2, 4, 8, 16, 64, 128, 256, 512
    \param[out] none
    \retval     none
*/
void rcu_ahb_clock_config(uint32_t ck_ahb)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_AHB_PSC(ck_ahb)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG0;
        /* reset the AHBPSC bits and set according to ck_ahb */
        reg &= ~RCU_CFG0_AHBPSC;
        RCU_CFG0 = (reg | ck_ahb);
    }
}

/*!
    \brief      configure the APB1 clock prescaler selection (API_ID(0x0009U))
    \param[in]  ck_apb1: APB1 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB1_CKAHB_DIV1: select CK_AHB as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV2: select CK_AHB/2 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV4: select CK_AHB/4 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV8: select CK_AHB/8 as CK_APB1
      \arg        RCU_APB1_CKAHB_DIV16: select CK_AHB/16 as CK_APB1
    \param[out] none
    \retval     none
*/
void rcu_apb1_clock_config(uint32_t ck_apb1)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_APB1_PSC(ck_apb1)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG0;
        /* reset the APB1PSC and set according to ck_apb1 */
        reg &= ~RCU_CFG0_APB1PSC;
        RCU_CFG0 = (reg | ck_apb1);
    }
}

/*!
    \brief      configure the APB2 clock prescaler selection (API_ID(0x000AU))
    \param[in]  ck_apb2: APB2 clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_APB2_CKAHB_DIV1: select CK_AHB as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV2: select CK_AHB/2 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV4: select CK_AHB/4 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV8: select CK_AHB/8 as CK_APB2
      \arg        RCU_APB2_CKAHB_DIV16: select CK_AHB/16 as CK_APB2
    \param[out] none
    \retval     none
*/
void rcu_apb2_clock_config(uint32_t ck_apb2)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_APB2_PSC(ck_apb2)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG0;
        /* reset the APB2PSC and set according to ck_apb2 */
        reg &= ~RCU_CFG0_APB2PSC;
        RCU_CFG0 = (reg | ck_apb2);
    }
}

/*!
    \brief      configure the CK_OUT clock source (API_ID(0x000BU))
    \param[in]  ckout0_src: CK_OUT clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKOUT0SRC_CORECK: CORECK is selected
      \arg        RCU_CKOUT0SRC_CKAPB1: CK_APB1 is selected
      \arg        RCU_CKOUT0SRC_IRC40K: IRC40K is selected
      \arg        RCU_CKOUT0SRC_LXTAL: LXTAL is selected
      \arg        RCU_CKOUT0SRC_CKSYS: CK_SYS is selected
      \arg        RCU_CKOUT0SRC_IRC48M: IRC48M is selected
      \arg        RCU_CKOUT0SRC_HXTAL: HXTAL is selected
      \arg        RCU_CKOUT0SRC_CKPLLP: CK_PLLP is selected
      \arg        RCU_CKOUT0SRC_CKPLLP_DIV2: CK_PLLP_DIV2 is selected
      \arg        RCU_CKOUT0SRC_CKAPB2: CK_APB2 is selected
      \arg        RCU_CKOUT0SRC_HSMPCLK: HSM_PCLK is selected
      \arg        RCU_CKOUT0SRC_HSMHCLK: HSM_HCLK is selected
      \arg        RCU_CKOUT0SRC_CKENETRX: CK_ENETRX is selected (not for GD32A711X_A712X)
      \arg        RCU_CKOUT0SRC_CKENETTX: CK_ENETTX is selected (not for GD32A711X_A712X)
      \arg        RCU_CKOUT0SRC_CKENETMACRMI: CK_ENETMACRMI is selected (not for GD32A711X_A712X)
      \arg        RCU_CKOUT0SRC_CKENETTS: CK_ENETTS is selected (not for GD32A711X_A712X)
    \param[in]  ckout_div: CK_OUT divider
      \arg        RCU_CKOUT0_DIVx(x=1,2,4,8,16,32,64,128): CK_OUT is divided by x
    \param[out] none
    \retval     none
*/
void rcu_ckout0_config(uint32_t ckout_src, uint32_t ckout_div)
{
    uint32_t ckout;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKOUT0SRC(ckout_src)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKOUT0_DIV(ckout_div)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ckout = RCU_CFG1;
        /* reset the CKOUTSEL and CKOUTDIV bits, and set according to ckout_src and ckout_div */
        ckout &= ~(RCU_CFG1_CKOUT0SEL | RCU_CFG1_CKOUT0DIV);
        RCU_CFG1 = (ckout | (ckout_src & BITS(16, 19)) | ckout_div);

        /* reset the PLLDV bit and set according to ckout_src */
        if(ckout_src == RCU_CKOUT0SRC_CKPLLP) {
            RCU_CFG0 |= RCU_CFG0_PLLDV;
        } else {
            RCU_CFG0 &= ~(RCU_CFG0_PLLDV);
        }
    }
}

/*!
    \brief      configure the CK_OUT1 clock source (API_ID(0x000CU))
    \param[in]  ckout1_src: CK_OUT1 clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKOUT1SRC_IRC40K: IRC40K selected
      \arg        RCU_CKOUT1SRC_LXTAL: LXTAL selected
      \arg        RCU_CKOUT1SRC_CKAPB2: CK_APB2 clock selected
      \arg        RCU_CKOUT1SRC_IRC48M: high speed 48M internal oscillator clock selected
      \arg        RCU_CKOUT1SRC_HXTAL: HXTAL clock selected
    \param[in]  ckout1_div: CK_OUT1 divider
                only one parameter can be selected which is shown as below:    
      \arg        RCU_CKOUT1_DIVx(x=1,2,4,8,16,32,64,128): CK_OUT is divided by x
    \param[out] none
    \retval     none
*/
void rcu_ckout1_config(uint32_t ckout1_src, uint32_t ckout1_div)
{
    uint32_t ckout1;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKOUT1SRC(ckout1_src)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKOUT1_DIV(ckout1_div)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ckout1 = RCU_CFG0;
        /* reset the CKOUT1SEL, CKOUT1DIV bits and set according to ckout_src and ckout_div */
        ckout1 &= ~(RCU_CFG0_CKOUT1SEL | RCU_CFG0_CKOUT1DIV);
        RCU_CFG0 = (ckout1 | ckout1_src | ckout1_div);
    }
}

/*!
    \brief      configure the main PLL clock (API_ID(0x000DU))
    \param[in]  pll_src: PLL clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLSRC_IRC48M: select CK_IRC48M as PLL source clock
      \arg        RCU_PLLSRC_HXTAL: select HXTAL as PLL source clock
    \param[in]  pll_predv: the PLL output frequency division factor from input clock
                only one parameter can be selected which is shown as below:
      \arg        this parameter should be selected 1,2,3,4,5,6,7
    \param[in]  pll_n: the PLL VCO clock multi factor
                only one parameter can be selected which is shown as below:
      \arg        this parameter should be selected between 16 and 255
    \param[in]  pll_pllpdiv: the PLL_P output frequency division factor from PLL VCO clock
                only one parameter can be selected which is shown as below:
      \arg        this parameter should be selected between 1 and 64
    \param[in]  pll_pllqdiv: the PLL_Q output frequency division factor from PLL VCO clock
                only one parameter can be selected which is shown as below:
      \arg        this parameter should be selected between 1 and 64
    \param[out] none
    \retval     none
*/
void rcu_pll_config(uint32_t pll_src, uint32_t pll_predv, uint32_t pll_n, uint32_t pll_pllpdiv, uint32_t pll_pllqdiv)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_PLLSRC(pll_src)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_PLL_PREDV_RANGE(pll_predv)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000DU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_RCU_PLL_N_RANGE(pll_n)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000DU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_RCU_PLLDIV_RANGE(pll_pllpdiv)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000DU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_RCU_PLLDIV_RANGE(pll_pllqdiv)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000DU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CFG1 &=  ~(RCU_CFG1_PREDV | RCU_CFG1_PLLDIVP | RCU_CFG1_PLLDIVQ);
        RCU_CFG1 |= (pll_predv | ((pll_pllpdiv - 1U) << 3U) | ((pll_pllqdiv - 1U) << 9U));
        RCU_CFG0 &= ~(RCU_CFG0_PLLMF | RCU_CFG0_PLLMF_7 | RCU_CFG0_PLLSEL);
        if(pll_n <= 0x7FU) {
            RCU_CFG0 |= (pll_src | (pll_n << 17U));
        } else {
            pll_n = pll_n & 0x7FU;
            RCU_CFG0 |= (pll_src | (pll_n << 17U) | BIT(27U));
        }
    }
}

/*!
    \brief      configure the ADC prescaler factor (API_ID(0x000EU))
    \param[in]  adc_src: ADC clock source
                only one parameter can be selected which is shown as below:
      \arg        RCU_ADCSRC_HCLK: HCLK is selected as ADC clock source
      \arg        RCU_ADCSRC_SYS: CK_SYS is selected as ADC clock source
      \arg        RCU_ADCSRC_PLLP: PLL_P is selected as ADC clock source
    \param[in]  adc_psc: ADC prescaler factor
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKADC_DIVx (x=2,3,...,32): ADC prescaler select CK_ADC/x
    \param[out] none
    \retval     none
*/
void rcu_adc_clock_config(uint32_t adc_src, uint32_t adc_psc)
{
    uint32_t reg;
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKADC_CKAHB_PSC(adc_psc)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_ADCSRC(adc_src)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG2;
        reg &= ~(RCU_CFG2_ADCCLK_MUX | RCU_CFG2_ADCSEL | RCU_CFG2_ADCPSC);
        RCU_CFG2 = (reg | adc_src | adc_psc);
    }
}

/*!
    \brief      configure the SPI prescaler factor (API_ID(0x000FU))
    \param[in]  spi_src: SPI clock source
                only one parameter can be selected which is shown as below:
      \arg        RCU_SPISRC_APB1: CK_APB1 is selected as SPI clock source
      \arg        RCU_SPISRC_APB2: CK_APB2 is selected as SPI clock source
      \arg        RCU_SPISRC_IRC48M: IRC48M is selected as SPI clock source
      \arg        RCU_SPISRC_AHB: CK_AHB is selected as SPI clock source
    \param[in]  spi_div: SPI prescaler factor
                only one parameter can be selected which is shown as below:
      \arg        1,...,64: SPI prescaler
    \param[out] none
    \retval     none
*/
void rcu_spi_clock_config(uint32_t spi_src, uint32_t spi_div)
{
    uint32_t reg;
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKSPIDIV(spi_div)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_SPISRC(spi_src)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG3;
        reg &= ~(RCU_CFG3_SPISEL| RCU_CFG3_SPIDIV);
        RCU_CFG3 = (reg | spi_src | (spi_div - 1U) << 4U);
    }
}

/*!
    \brief      configure the RTC clock source selection (API_ID(0x0010U))
    \param[in]  rtc_clock_source: RTC clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_RTCSRC_NONE: no clock selected
      \arg        RCU_RTCSRC_LXTAL: CK_LXTAL selected as RTC source clock
      \arg        RCU_RTCSRC_IRC40K: CK_IRC40K selected as RTC source clock
      \arg        RCU_RTCSRC_HXTAL_DIV_128: CK_HXTAL/128 selected as RTC source clock
    \param[out] none
    \retval     none
*/
void rcu_rtc_clock_config(uint32_t rtc_clock_source)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_RTCSRC(rtc_clock_source)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_BDCTL;
        /* reset the RTCSRC bits and set according to rtc_clock_source */
        reg &= ~RCU_BDCTL_RTCSRC;
        RCU_BDCTL = (reg | rtc_clock_source);
    }
}

/*!
    \brief      configure the DTM_CAN clock source selection (API_ID(0x0011U))
    \param[in]  dtm_can_periph: DTM_CANx(x=0,1,..,7)(DTM_CAN6\DTM_CAN7 are not for GD32A711X_A712X)
                only one parameter can be selected.
    \param[in]  dtm_can_clock_source: DTM_CAN clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_DTM_CANSRC_HXTAL: HXTAL clock selected as DTM_CAN source clock
      \arg        RCU_DTM_CANSRC_AHB: AHB clock selected as DTM_CAN source clock
      \arg        RCU_DTM_CANSRC_PCLK2: PCLK2 clock selected as DTM_CAN source clock
      \arg        RCU_DTM_CANSRC_IRC48M: IRC48M clock selected as DTM_CAN source clock
    \param[out] none
    \retval     none
*/
void rcu_dtm_can_clock_config(uint32_t dtm_can_periph, uint32_t dtm_can_clock_source)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_DTM_CAN_PERIPH(dtm_can_periph)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else if(NOT_RCU_DTM_CANSRC(dtm_can_clock_source)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0011U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {

        reg = RCU_CFG2;
        switch(dtm_can_periph) {
        case DTM_CAN0:
            /* reset the DTM_CAN0SEL bits and set according to dtm_can_clock_source */
            reg &= ~RCU_CFG2_DTM_CAN0SEL;
            RCU_CFG2 = (reg | (uint32_t)(dtm_can_clock_source << 8U));
            break;
        case DTM_CAN1:
            /* reset the DTM_CAN1SEL bits and set according to dtm_can_clock_source */
            reg &= ~RCU_CFG2_DTM_CAN1SEL;
            RCU_CFG2 = (reg | (uint32_t)(dtm_can_clock_source << 10U));
            break;
        case DTM_CAN2:
            /* reset the DTM_CAN1SEL bits and set according to dtm_can_clock_source */
            reg &= ~RCU_CFG2_DTM_CAN2SEL;
            RCU_CFG2 = (reg | (uint32_t)(dtm_can_clock_source << 12U));
            break;
        case DTM_CAN3:
            /* reset the DTM_CAN1SEL bits and set according to dtm_can_clock_source */
            reg &= ~RCU_CFG2_DTM_CAN3SEL;
            RCU_CFG2 = (reg | (uint32_t)(dtm_can_clock_source << 14U));
            break;
        case DTM_CAN4:
            /* reset the DTM_CAN1SEL bits and set according to dtm_can_clock_source */
            reg &= ~RCU_CFG2_DTM_CAN4SEL;
            RCU_CFG2 = (reg | (uint32_t)(dtm_can_clock_source << 16U));
            break;
        case DTM_CAN5:
            /* reset the DTM_CAN1SEL bits and set according to dtm_can_clock_source */
            reg &= ~RCU_CFG2_DTM_CAN5SEL;
            RCU_CFG2 = (reg | (uint32_t)(dtm_can_clock_source << 18U));
            break;
        case DTM_CAN6:
            /* reset the DTM_CAN1SEL bits and set according to dtm_can_clock_source */
            reg &= ~RCU_CFG2_DTM_CAN6SEL;
            RCU_CFG2 = (reg | (uint32_t)(dtm_can_clock_source << 20U));
            break;
        case DTM_CAN7:
            reg = RCU_CFG3;
            /* reset the DTM_CAN1SEL bits and set according to dtm_can_clock_source */
            reg &= ~RCU_CFG3_DTM_CAN7SEL;
            RCU_CFG3 = (reg | (uint32_t)(dtm_can_clock_source));
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      configure the WWDGT clock source selection (API_ID(0x0012U))
    \param[in]  wwdgt_periph: WWDGTx(x=0,1)(WWDGT1 is not applicable to GD32A711X_A712X)
    \param[in]  wwdgt_clock_source: WWDGT clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_WWDGTSRC_IRC48M: IRC48M clock selected as WWDGT source clock
      \arg        RCU_WWDGTSRC_LXTAL: LXTAL clock selected as WWDGT source clock
      \arg        RCU_WWDGTSRC_IRC40K: IRC40K clock selected as WWDGT source clock
      \arg        RCU_WWDGTSRC_HXTAL: HXTAL clock selected as WWDGT source clock
      \arg        RCU_WWDGTSRC_CKSYS: CK_SYS clock selected as WWDGT source clock
      \arg        RCU_WWDGTSRC_PCLK1: PCLK1 clock selected as WWDGT source clock
    \param[out] none
    \retval     none
*/
void rcu_wwdgt_clock_config(uint32_t wwdgt_periph, uint32_t wwdgt_clock_source)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_WWDGT_PERIPH(wwdgt_periph)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else if(NOT_RCU_WWDGTSRC(wwdgt_clock_source)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG3;
        switch(wwdgt_periph) {
        case WWDGT0:
            /* reset the WWDGT0SEL bits and set according to wwdgt_clock_source */
            reg &= ~RCU_CFG3_WWDGT0SEL;
            RCU_CFG3 = (reg | (uint32_t)(wwdgt_clock_source));
            break;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case WWDGT1:
            /* reset the WWDGT1SEL bits and set according to wwdgt_clock_source */
            reg &= ~RCU_CFG3_WWDGT1SEL;
            RCU_CFG3 = (reg | (uint32_t)(wwdgt_clock_source) << 3U);
            break;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        default:
            break;
        }
    }
}

/*!
    \brief      configure the FWDGT clock source selection (API_ID(0x0013U))
    \param[in]  fwdgt_periph: FWDGTx(x=0,1)(FWDGT1 is not applicable to GD32A711X_A712X)
    \param[in]  fwdgt_clock_source: FWDGT clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_FWDGTSRC_IRC40K: IRC40k clock selected as FWDGT source clock
      \arg        RCU_FWDGTSRC_LXTAL: LXTAL clock selected as FWDGT source clock
    \param[out] none
    \retval     none
*/
void rcu_fwdgt_clock_config(uint32_t fwdgt_periph, uint32_t fwdgt_clock_source)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_FWDGT_PERIPH(fwdgt_periph)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    } else if(NOT_RCU_FWDGTSRC(fwdgt_clock_source)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(fwdgt_periph) {
        case FWDGT0:
            reg = RCU_CFG1;
            /* reset the FWDGT0SEL bits and set according to fwdgt_clock_source */
            reg &= ~RCU_CFG1_FWDGT0SEL;
            RCU_CFG1 = (reg | (uint32_t)(fwdgt_clock_source) << 15U);
            break;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case FWDGT1:
            reg = RCU_CFG2;
            /* reset the FWDGT1SEL bits and set according to fwdgt_clock_source */
            reg &= ~RCU_CFG2_FWDGT1SEL;
            RCU_CFG2 = (reg | (uint32_t)(fwdgt_clock_source) << 26U);
            break;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        default:
            break;
        }
    }
}

/*!
    \brief      configure the LINFlexD clock source selection (API_ID(0x0014U))
    \param[in]  linflexd_clock_source: LINFlexD clock source selection
                only one parameter LINFlexD be selected which is shown as below:
      \arg        RCU_LINFLEXDSRC_CKSYS: CK_SYS clock selected as LINFlexD source clock
      \arg        RCU_LINFLEXDSRC_HXTAL: HXTAL clock selected as LINFlexD source clock
      \arg        RCU_LINFLEXDSRC_PLL_P: PLL_P clock selected as LINFlexD source clock
      \arg        RCU_LINFLEXDSRC_IRC48M: IRC48M clock selected as LINFlexD source clock
    \param[in]  linflexddiv: LIN clock division(LIN_clock/linflexddiv)
                only one parameter can be selected which is shown as below:
      \arg        this parameter should be selected as 1,2,..,14,15

    \param[out] none
    \retval     none
*/
void rcu_linflexd_clock_config(uint32_t linflexd_clock_source, uint32_t linflexddiv)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_LINFLEXDSRC(linflexd_clock_source) || (linflexddiv == 0U)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0014U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG3;
        /* reset the LINFlexDSEL bits and set according to linflexd_clock_source */
        reg &= ~(RCU_CFG3_LINFLEXDSEL | RCU_CFG3_LINFLEXDDIV);
        RCU_CFG3 = (reg | (linflexd_clock_source | (((linflexddiv - 1U) & (0xFU)) << 10U)));
    }
}

/*!
    \brief      configure the AIT clock source selection (API_ID(0x0015U))
    \param[in]  ait_clock_source: AIT clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKAITSRC_IRC48M: AIT clock source select CK_IRC48M
      \arg        RCU_CKAITSRC_CK_PLL_Q_DIV2: AIT clock source select CK_PLL_Q/2
      \arg        RCU_CKAITSRC_CK_PLL_Q_DIV3: AIT clock source select CK_PLL_Q/3
      \arg        RCU_CKAITSRC_CK_PLL_Q_DIV4: AIT clock source select CK_PLL_Q/4
    \param[out] none
    \retval     none
*/
void rcu_ait_clock_config(uint32_t ait_clock_source)
{
    uint32_t reg;
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKAITSRC(ait_clock_source)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG1;
        /* reset the AITSEL bits and set according to ait_clock_source */
        reg &= ~RCU_CFG1_AITSEL;
        RCU_CFG1 = (reg | (uint32_t)(ait_clock_source));
    }
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      configure the ATE clock source selection (API_ID(0x0016U))
    \param[in]  ait_clock_source: ATE clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKATESRC_IRC48M: ATE clock source select CK_IRC48M
      \arg        RCU_CKATESRC_CK_PLL_Q_DIV2: ATE clock source select CK_PLL_Q/2
      \arg        RCU_CKATESRC_CK_PLL_Q_DIV3: ATE clock source select CK_PLL_Q/3
      \arg        RCU_CKATESRC_CK_PLL_Q_DIV4: ATE clock source select CK_PLL_Q/4
    \param[out] none
    \retval     none
*/
void rcu_ate_clock_config(uint32_t ate_clock_source)
{
    uint32_t reg;
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKATESRC(ate_clock_source)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0016U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG1;
        /* reset the ATESEL bits and set according to ate_clock_source */
        reg &= ~RCU_CFG1_ATESEL;
        RCU_CFG1 = (reg | (uint32_t)(ate_clock_source));
    }
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      configure the TRACE clock source selection (API_ID(0x0017U))
    \param[in]  trace_clock_source: TRACE clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_TRACESRC_PLLQ: PLLQ is selected as TRACE clock source
      \arg        RCU_TRACESRC_PLLP: PLLP is selected as TRACE clock source
      \arg        RCU_TRACESRC_HXTAL: HXTAL is selected as TRACE clock source
      \arg        RCU_TRACESRC_IRC48M: IRC48M is selected as TRACE clock source
    \param[in]  trace_clock_psc: TRACE clock prescaler selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKTRACE_DIV1: TRACE clock is divided by 1
      \arg        RCU_CKTRACE_DIV2: TRACE clock is divided by 2
      \arg        RCU_CKTRACE_DIV3: TRACE clock is divided by 3
      \arg        RCU_CKTRACE_DIV4: TRACE clock is divided by 4
      \arg        RCU_CKTRACE_DIV5: TRACE clock is divided by 5
      \arg        RCU_CKTRACE_DIV6: TRACE clock is divided by 6
      \arg        RCU_CKTRACE_DIV7: TRACE clock is divided by 7
      \arg        RCU_CKTRACE_DIV8: TRACE clock is divided by 8
    \param[out] none
    \retval     none
*/
void rcu_trace_clock_source_config(uint32_t trace_clock_source, uint32_t trace_clock_psc)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_TRACESRC(trace_clock_source)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0017U), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKTRACE_DIV(trace_clock_psc)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0017U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG3;
        /* reset the TRACESEL and TRACEDIV bits and set according to ate_clock_source */
        reg &= ~(RCU_CFG3_TRACESEL | RCU_CFG3_TRACEDIV);
        RCU_CFG3 = (reg | (uint32_t)(trace_clock_source) | (uint32_t)(trace_clock_psc));
    }
}

/*! \brief      configure the QSPI clock source selection (API_ID(0x0018U))
    \param[in]  qspi_clock_source: QSPI clock source selection
                only one parameter can be selected which is shown as below:
      \arg        RCU_QSPISRC_PLLQ: PLLQ is selected as QSPI clock source
      \arg        RCU_QSPISRC_PLLP: PLLP is selected as QSPI clock source
      \arg        RCU_QSPISRC_HCLK: HCLK is selected as QSPI clock source
      \arg        RCU_QSPISRC_IRC48M: IRC48M is selected as QSPI clock source
    \param[out] none
    \retval     none
*/
void rcu_qspi_clock_source_config(uint32_t qspi_clock_source)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_QSPISRC(qspi_clock_source)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0018U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG3;
        /* reset the QSPISEL bits and set according to qspi_clock_source */
        reg &= ~RCU_CFG3_QSPISEL;
        RCU_CFG3 = (reg | (uint32_t)(qspi_clock_source));
    }
}

/*! \brief      configure the LXTAL drive capability (API_ID(0x0019U))
    \param[in]  lxtal_dricap: drive capability of LXTAL
                only one parameter can be selected which is shown as below:
      \arg        RCU_LXTAL_LOWDRI: lower driving capability
      \arg        RCU_LXTAL_MED_LOWDRI: medium low driving capability
      \arg        RCU_LXTAL_MED_HIGHDRI: medium high driving capability
      \arg        RCU_LXTAL_HIGHDRI: higher driving capability
    \param[out] none
    \retval     none
*/
void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_LXTAL_DRIVE(lxtal_dricap)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0019U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_BDCTL;
        /* reset the LXTALDRI bits and set according to lxtal_dricap */
        reg &= ~RCU_BDCTL_LXTALDRI;
        RCU_BDCTL = (reg | lxtal_dricap);
    }
}

/*! \brief      wait for oscillator stabilization flags is SET or oscillator startup is timeout (API_ID(0x001AU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci)
{
    uint32_t stb_cnt = 0U;
    ErrStatus reval = ERROR;
    FlagStatus osci_stat = RESET;

    switch(osci) {
    /* wait HXTAL stable */
    case RCU_HXTAL:
        while((RESET == osci_stat) && (HXTAL_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_HXTALSTB);
            stb_cnt++;
        }
        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_HXTALSTB)) {
            reval = SUCCESS;
        }
        break;
    /* wait LXTAL stable */
    case RCU_LXTAL:
        while((RESET == osci_stat) && (LXTAL_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_LXTALSTB);
            stb_cnt++;
        }
        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_LXTALSTB)) {
            reval = SUCCESS;
        }
        break;
    /* wait PLL stable */
    case RCU_PLL_CK:
        while((RESET == osci_stat) && (OSC_STARTUP_TIMEOUT != stb_cnt)) {
            osci_stat = rcu_flag_get(RCU_FLAG_PLLSTB);
            stb_cnt++;
        }
        /* check whether flag is set or not */
        if(RESET != rcu_flag_get(RCU_FLAG_PLLSTB)) {
            reval = SUCCESS;
        }
        break;
    default:
        break;
    }
    /* return value */
    return reval;
}

/*! \brief      turn on the oscillator (API_ID(0x001BU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
    \param[out] none
    \retval     none
*/
void rcu_osci_on(rcu_osci_type_enum osci)
{
    RCU_CCTL_REG_VAL(osci) |= BIT(RCU_BIT_POS(osci));
}

/*! \brief      turn off the oscillator (API_ID(0x001CU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
      \arg        RCU_PLL_CK: phase locked loop(PLL)
    \param[out] none
    \retval     none
*/
void rcu_osci_off(rcu_osci_type_enum osci)
{
    RCU_CCTL_REG_VAL(osci) &= ~BIT(RCU_BIT_POS(osci));
}

/*! \brief      enable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it (API_ID(0x001DU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
    \param[out] none
    \retval     none
*/
void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci)
{
    uint32_t reg;

    switch(osci) {
    /* enable HXTAL to bypass mode */
    case RCU_HXTAL:
        reg = RCU_CTL;
        RCU_CTL &= ~RCU_CTL_HXTALEN;
        RCU_CTL = (reg | RCU_CTL_HXTALBPS);
        break;
    /* enable LXTAL to bypass mode */
    case RCU_LXTAL:
        reg = RCU_BDCTL;
        RCU_BDCTL &= ~RCU_BDCTL_LXTALEN;
        RCU_BDCTL = (reg | RCU_BDCTL_LXTALBPS);
        break;
    default:
        break;
    }
}

/*! \brief      disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it (API_ID(0x001EU))
    \param[in]  osci: oscillator types, refer to rcu_osci_type_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_HXTAL: high speed crystal oscillator(HXTAL)
      \arg        RCU_LXTAL: low speed crystal oscillator(LXTAL)
    \param[out] none
    \retval     none
*/
void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci)
{
    uint32_t reg;

    switch(osci) {
    /* disable HXTAL to bypass mode */
    case RCU_HXTAL:
        reg = RCU_CTL;
        RCU_CTL &= ~RCU_CTL_HXTALEN;
        RCU_CTL = (reg & ~RCU_CTL_HXTALBPS);
        break;
    /* disable LXTAL to bypass mode */
    case RCU_LXTAL:
        reg = RCU_BDCTL;
        RCU_BDCTL &= ~RCU_BDCTL_LXTALEN;
        RCU_BDCTL = (reg & ~RCU_BDCTL_LXTALBPS);
        break;
    default:
        break;
    }
}

/*! \brief      HXTAL frequency scale select (API_ID(0x001FU))
    \param[in]  hxtal_scal: HXTAL frequency scale
                only one parameter can be selected which is shown as below:
      \arg        HXTAL_SCALE_4M_TO_8M: HXTAL scale is 4-8MHz
      \arg        HXTAL_SCALE_8M_TO_16M: HXTAL scale is 8-16MHz
      \arg        HXTAL_SCALE_16M_TO_32M: HXTAL scale is 16-32MHz
      \arg        HXTAL_SCALE_32M_TO_40M: HXTAL scale is 32-40MHz
    \param[out] none
    \retval     none
*/
void rcu_hxtal_frequency_scale_select(uint32_t hxtal_scal)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HXTAL_SCALE(hxtal_scal)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x001FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CTL &= ~RCU_CTL_HXTALSCAL;
        RCU_CTL |= hxtal_scal;
    }
}

/*!
    \brief      configure the HXTAL or IRC48M divider used as input of PLL (API_ID(0x0020U))
    \param[in]  prediv: clock perescaler
                only one parameter can be selected which is shown as below:
      \arg        RCU_PREDV_DIVx(x=1..7): HXTAL divided x used as input of PLL
    \param[out] none
    \retval     none
*/
void rcu_prediv_config(uint32_t prediv)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_PREDV_DIV(prediv)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0020U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CFG1;
        /* reset the PREDV bits and set according to prediv */
        reg &= ~RCU_CFG1_PREDV;
        RCU_CFG1 = (reg | prediv);
    }
}

/*!
    \brief      set the IRC48M adjust value (API_ID(0x0021U))
    \param[in]  irc48m_adjval: IRC48M adjust value, must be between 0 and 0x1F
                only one parameter can be selected which is shown as below:
      \arg        0x00 - 0x1F
    \param[out] none
    \retval     none
*/
void rcu_irc48m_adjust_value_set(uint32_t irc48m_adjval)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_IRC48M_ADJVAL_RANGE(irc48m_adjval)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0021U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_CTL;
        /* reset the IRC48MADJ bits and set according to irc48m_adjval */
        reg &= ~RCU_CTL_IRC48MADJ;
        RCU_CTL = (reg | ((irc48m_adjval & RCU_IRC48M_ADJUST_MASK) << RCU_IRC48M_ADJUST_OFFSET));
    }
}
/*!
    \brief     configure the IRC48M fail responsee (API_ID(0x0022U))
    \param[in]  irc48m_fail: IRC48M fail response
                only one parameter can be selected which is shown as below:
      \arg        RCU_IRC48M_POR: IRC48M fail response,POR reset is triggered
      \arg        RCU_FFIO0_FFIO1: the failure of IRC48M will set FFIO0 and FFIO1 pins to High-Z state
    \param[out] none
    \retval     none
*/
void rcu_irc48m_fail_response_config(uint32_t irc48m_fail)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(irc48m_fail != RCU_IRC48M_POR && irc48m_fail != RCU_FFIO0_FFIO1) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0022U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CFG1 &= ~RCU_CFG1_IRC48MFR;
        RCU_CFG1 |= (irc48m_fail << 30U);
    }
}

/*! \brief      enable the HXTAL clock monitor (API_ID(0x0023U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_enable(void)
{
    RCU_CTL |= RCU_CTL_CKMEN;
}

/*! \brief      disable the HXTAL clock monitor (API_ID(0x0024U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_hxtal_clock_monitor_disable(void)
{
    RCU_CTL &= ~RCU_CTL_CKMEN;
}

/*!
    \brief      frequency monitor enable (API_ID(0x0025U))
    \param[in]  uint32_t: CKFMx(x=0...4)  only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor_enable(uint32_t ckfmx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFM_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0025U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(ckfmx) |= RCU_CKFMCTL_FMEN;
    }
}

/*!
    \brief      frequency monitor disable (API_ID(0x0026U))
    \param[in]  ckfmx: CKFMx(x=0...4) only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor_disable(uint32_t ckfmx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFM_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0026U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(ckfmx) &= ~RCU_CKFMCTL_FMEN;
    }
}

/*!
    \brief      frequency monitor0 system reset enable (API_ID(0x0027U))
    \param[in]  sys_rst: frequency monitor0 (CKFM0) system reset
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKFMCTL_FHMAXRE: Frequency higher than FHMAX system reset enable
      \arg        RCU_CKFMCTL_FLMINRE: Frequency lower than FLMIN system reset enable
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor0_system_reset_enable(uint32_t sys_rst)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFMCTL_RST(sys_rst)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0027U), ERR_PARAM_INVALID);
     } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(0U) |= sys_rst;
    }
}

/*!
    \brief      frequency monitor0 system reset disable (API_ID(0x0028U))
    \param[in]  sys_rst: frequency monitor0 (CKFM0) system reset
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKFMCTL_FLMINRE: Frequency lower than FLMIN system reset disable
      \arg        RCU_CKFMCTL_FHMAXRE: Frequency higher than FHMAX system reset disable
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor0_system_reset_disable( uint32_t sys_rst)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFMCTL_RST(sys_rst)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0028U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(0U) &= ~sys_rst;
    }
}

/*!
    \brief      frequency monitor system reset enable (API_ID(0x0029U))
    \param[in]  ckfmx: CKFMx(x=1,2) only one parameter can be selected
    \param[in]  interrupt: frequency monitor interrupt
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKFMCTL_FHMAXIE: Frequency higher than FHMAX system reset enable
      \arg        RCU_CKFMCTL_FLMINIE: Frequency lower than FLMIN system reset enable
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor_system_reset_enable(uint32_t ckfmx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFMCTL_RST_1(interrupt)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0029U), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKFM_RST_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0029U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(ckfmx) |= interrupt;
    }
}

/*!
    \brief      frequency monitor system reset disable (API_ID(0x002AU))
    \param[in]  ckfmx: CKFMx(x=1,2) only one parameter can be selected
    \param[in]  interrupt: frequency monitor interrupt
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKFMCTL_FLMINIE: Frequency lower than FLMIN system reset disable
      \arg        RCU_CKFMCTL_FHMAXIE: Frequency higher than FHMAX system reset disable
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor_system_reset_disable(uint32_t ckfmx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFMCTL_RST_1(interrupt)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002AU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKFM_RST_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(ckfmx) &= ~interrupt;
    }
}

/*!
    \brief      frequency monitor interrupt enable (API_ID(0x002BU))
    \param[in]  ckfmx: CKFMx(x=0,3,4) only one parameter can be selected
    \param[in]  interrupt: frequency monitor interrupt
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKFMCTL_FLMINIE: Frequency lower than FLMIN interrupt disable
      \arg        RCU_CKFMCTL_FHMAXIE: Frequency higher than FHMAX interrupt disable
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor_interrupt_enable(uint32_t ckfmx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFMCTL_INI(interrupt)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002BU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKFM_INT_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(ckfmx) |= interrupt;
    }
}

/*! \brief      frequency monitor interrupt disable (API_ID(0x002CU))
    \param[in]  uint32_t: CKFMx(x=0,3,4) only one parameter can be selected
    \param[in]  interrupt: frequency monitor interrupt
                only one parameter can be selected which is shown as below:
      \arg        RCU_CKFMCTL_FLMINIE: Frequency lower than FLMIN interrupt disable
      \arg        RCU_CKFMCTL_FHMAXIE: Frequency higher than FHMAX interrupt disable
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor_interrupt_disable(uint32_t ckfmx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFMCTL_INI(interrupt)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002CU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKFM_INT_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(ckfmx) &= ~interrupt;
    }
}

/*!
    \brief      get frequency monitor flag (API_ID(0x002DU))
    \param[in]  ckfmx: CKFMx(x=0...4) only one parameter can be selected
    \param[in]  interrupt_flag: frequency monitor flag
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_FLMIN: Frequency lower than low frequency reference threshold event status
      \arg        RCU_FLAG_FHMAX: Frequency higher than high frequency reference threshold event status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_frequency_monitor_flag_get(uint32_t ckfmx, uint32_t interrupt_flag)
{
    FlagStatus flag = RESET ;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if((interrupt_flag != RCU_FLAG_FLMIN) && (interrupt_flag != RCU_FLAG_FHMAX)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002DU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKFM_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(interrupt_flag == (RCU_CKFMCTL(ckfmx) & (interrupt_flag))) {
            flag = SET;
        } else {
            flag = RESET;
        }
    }
    return flag;
}

/*! \brief      clear frequency monitor interrupt flag (API_ID(0x002EU))
    \param[in]  ckfmx: CKFMx(x=0...4) only one parameter can be selected
    \param[in]  interrupt_flag: frequency monitor flag
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_FLMIN: Frequency lower than low frequency reference threshold event status
      \arg        RCU_FLAG_FHMAX: Frequency higher than high frequency reference threshold event status
    \param[out] none
    \retval     none
*/
void rcu_frequency_monitor_flag_clear(uint32_t ckfmx, uint32_t interrupt_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if((interrupt_flag != RCU_FLAG_FLMIN) && (interrupt_flag != RCU_FLAG_FHMAX)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002EU), ERR_PARAM_INVALID);
    } else if(NOT_RCU_CKFM_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMCTL(ckfmx) = interrupt_flag;
    }
}


/*!
    \brief      reference count configuration (API_ID(0x002FU))
    \param[in]  uint32_t: CKFMx(x=0...4) only one parameter can be selected
    \param[in]  count: reference count, only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_reference_count_config(uint32_t ckfmx, uint32_t count)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFM_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x002FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMRCCFG(ckfmx) &= ~RCU_CKFMRCCFG_REF_CNT;
        RCU_CKFMRCCFG(ckfmx) |= (RCU_CKFMRCCFG_REF_CNT & count);
    }
}

/*!
    \brief      reference count configuration (API_ID(0x0030U))
    \param[in]  uint32_t: CKFMx(x=0...4) only one parameter can be selected
    \param[in]  hthreshold: high frequency reference threshold, only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_monitored_hthreshold_config(uint32_t ckfmx, uint32_t hthreshold)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFM_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0030U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMHTHCFG(ckfmx) &= ~RCU_CKFMHTHCFG_HFMAX;
        RCU_CKFMHTHCFG(ckfmx) |= (RCU_CKFMHTHCFG_HFMAX & hthreshold);
    }
}

/*!
    \brief      reference count configuration (API_ID(0x0031U))
    \param[in]  uint32_t: CKFMx(x=0...4) only one parameter can be selected
    \param[in]  lthreshold: low frequency reference threshold, only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_monitored_lthreshold_config(uint32_t ckfmx, uint32_t lthreshold)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CKFM_PERIPH(ckfmx)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0031U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_CKFMLTHCFG(ckfmx) &= ~RCU_CKFMLTHCFG_LFMIN;
        RCU_CKFMLTHCFG(ckfmx) |= (RCU_CKFMLTHCFG_LFMIN & lthreshold);
    }
}

/*!
    \brief      frequency detect enable (API_ID(0x0032U))
    \param[in]  ckd_enum: CKDx(x=0...2),(CKD2 is not applicable to GD32A711X_A712X)
                only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_frequency_detect_enable(ckd_enum ckdx)
{
    RCU_CKDCTL |= (uint32_t)1U << ((uint32_t)ckdx << 3U);
}

/*!
    \brief      frequency detect disable (API_ID(0x0033U))
    \param[in]  ckd_enum: CKDx(x=0...2)(CKD2 is not applicable to GD32A711X_A712X)
                only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_frequency_detect_disable(ckd_enum ckdx)
{
    RCU_CKDCTL &= ~((uint32_t)1U << ((uint32_t)ckdx << 3U));
}

/*!
    \brief      frequency detect interrupt enable (API_ID(0x0034U))
    \param[in]  ckd_enum: CKDx(x=0...2)(CKD2 is not applicable to GD32A711X_A712X)
                only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_frequency_detect_error_interrupt_enable(ckd_enum ckdx)
{
    RCU_CKDCTL |= (uint32_t)4U << ((uint32_t)ckdx << 3U);
}

/*!
    \brief      frequency detect interrupt disable (API_ID(0x0035U))
    \param[in]  ckd_enum: CKDx(x=0...2)(CKD2 is not applicable to GD32A711X_A712X)
                only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_frequency_detect_error_interrupt_disable(ckd_enum ckdx)
{
    RCU_CKDCTL &= ~((uint32_t)4U << ((uint32_t)ckdx << 3U));
}

/*!
    \brief      get the system clock, bus and peripheral clock frequency (API_ID(0x0036U))
    \param[in]  clock: the clock frequency which to get
                only one parameter can be selected which is shown as below:
      \arg        CK_SYS: system clock frequency
      \arg        CK_AHB: AHB clock frequency
      \arg        CK_APB1: APB1 clock frequency
      \arg        CK_APB2: APB2 clock frequency
      \arg        CK_LINFLEXD: LINFlexD clock frequency
    \param[out] none
    \retval     clock frequency of system, AHB, APB1, APB2, LINFlexD
*/
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock)
{
    uint32_t sws, ck_freq = 0U;
    uint32_t cksys_freq, ahb_freq, apb1_freq, apb2_freq, pll_freq = 0U;
    uint32_t linflexd_freq, linflexd_div;
    uint32_t pllsel, pllmf, plldivp, ck_src, idx, clk_exp;
    uint32_t predv0;

    /* exponent of AHB, APB1 and APB2 clock divider */

    uint16_t ahb_exp[16] = {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 2U, 4U, 8U, 16U, 64U, 128U, 256U, 512U};
    uint8_t apb1_exp[8] = {0U, 0U, 0U, 0U, 2U, 4U, 8U, 16U};
    uint8_t apb2_exp[8] = {0U, 0U, 0U, 0U, 2U, 4U, 8U, 16U};

    sws = RCU_CFG0 & RCU_CFG0_SCSS;
    switch(sws) {
    /* IRC48M is selected as CK_SYS */
    case RCU_SCSS_IRC48M:
        cksys_freq = IRC48M_VALUE;
        break;
    /* HXTAL is selected as CK_SYS */
    case RCU_SCSS_HXTAL:
        cksys_freq = HXTAL_VALUE;
        break;
    /* PLL is selected as CK_SYS */
    case RCU_SCSS_PLL_P:
        /* PLL clock source selection, HXTAL or IRC48M */
        pllsel = (RCU_CFG0 & RCU_CFG0_PLLSEL);
        if(RCU_PLLSRC_HXTAL == pllsel) {
            /* PLL clock source is HXTAL */
            ck_src = HXTAL_VALUE;
            predv0 = (RCU_CFG1 & RCU_CFG1_PREDV);
            if(predv0 != 0U) {
                ck_src /= predv0;
            }
        } else {
            /* PLL clock source is IRC48M */
            ck_src = IRC48M_VALUE ;
            predv0 = (RCU_CFG1 & RCU_CFG1_PREDV);
            if(predv0 != 0U) {
                ck_src /= predv0;
            }
        }
        /* PLL multiplication factor */
        pllmf = GET_BITS(RCU_CFG0, 17U, 23U);
        if((RCU_CFG0 & RCU_CFG0_PLLMF_7) != 0U) {
            pllmf += 128U;
        }
        plldivp =  GET_BITS(RCU_CFG1, 3U, 8U);
        pll_freq = (ck_src * pllmf) / (plldivp + 1U);
        cksys_freq = pll_freq;
        break;
    /* IRC48M is selected as CK_SYS */
    default:
        cksys_freq = IRC48M_VALUE;
        break;
    }
    /* calculate AHB clock frequency */
    idx = GET_BITS(RCU_CFG0, 4U, 7U);
    clk_exp = ahb_exp[idx];
    if(clk_exp != 0U) {
        ahb_freq = cksys_freq / clk_exp;
    } else {
        ahb_freq = cksys_freq;
    }
    /* calculate APB1 clock frequency */
    idx = GET_BITS(RCU_CFG0, 8U, 10U);
    clk_exp = apb1_exp[idx];
    if(clk_exp != 0U) {
        apb1_freq = ahb_freq / clk_exp;
    } else {
        apb1_freq = ahb_freq;
    }
    /* calculate APB2 clock frequency */
    idx = GET_BITS(RCU_CFG0, 11U, 13U);
    clk_exp = apb2_exp[idx];
    if(clk_exp != 0U) {
        apb2_freq = ahb_freq / clk_exp;
    } else {
        apb2_freq = ahb_freq;
    }
    if((RCU_CTL & RCU_CTL_PLLSTB) == RCU_CTL_PLLSTB) {
        /* PLL clock source selection, HXTAL or IRC48M */
        pllsel = (RCU_CFG0 & RCU_CFG0_PLLSEL);
        if(RCU_PLLSRC_HXTAL == pllsel) {
            /* PLL clock source is HXTAL */
            ck_src = HXTAL_VALUE;
        } else {
            /* PLL clock source is IRC48M */
            ck_src = IRC48M_VALUE ;
        }
        predv0 = (RCU_CFG1 & RCU_CFG1_PREDV);
        if(predv0 == 0U) {
            predv0 = 1U;
            ck_src /= predv0;
        } else {
            ck_src /= predv0;
        }
        /* PLL multiplication factor */
        pllmf = GET_BITS(RCU_CFG0, 17U, 23U);
        if((RCU_CFG0 & RCU_CFG0_PLLMF_7) != 0U) {
            pllmf += 128U;
        }
        plldivp =  GET_BITS(RCU_CFG1, 3U, 8U);
        pll_freq = (ck_src * pllmf) / (plldivp + 1U);
    }
    /* return the clocks frequency */
    switch(clock) {
    case CK_SYS:
        ck_freq = cksys_freq;
        break;
    case CK_AHB:
        ck_freq = ahb_freq;
        break;
    case CK_APB1:
        ck_freq = apb1_freq;
        break;
    case CK_APB2:
        ck_freq = apb2_freq;
        break;
    case CK_LINFLEXD:
        linflexd_div = GET_BITS(RCU_CFG3, 10U, 13U);
        /* calculate LINFlexDX clock frequency */
        if((RCU_CFG3 & RCU_CFG3_LINFLEXDSEL) == RCU_LINFLEXDSRC_HXTAL) {
            linflexd_freq = HXTAL_VALUE / (linflexd_div + 1U);
        } else if((RCU_CFG3 & RCU_CFG3_LINFLEXDSEL) == RCU_LINFLEXDSRC_IRC48M) {
            linflexd_freq = IRC48M_VALUE / (linflexd_div + 1U);
        } else if((RCU_CFG3 & RCU_CFG3_LINFLEXDSEL) == RCU_LINFLEXDSRC_CKSYS) {
            linflexd_freq = cksys_freq / (linflexd_div + 1U);
        } else  {
            linflexd_freq = pll_freq / (linflexd_div + 1U);
        }
        ck_freq = linflexd_freq;
        break;
    default:
        break;
    }
    return ck_freq;
}
/*!
    \brief      clear the system reset flag  (API_ID(0x0037U))
    \param[in]  flag: the system reset flag
                only one parameter can be selected which is shown as below:
    \arg        RCU_FLAG_POR:Power-on reset flag
    \arg        RCU_FLAG_FMU_REA_FAIL: System reset flag FMU_REA_FAIL
    \arg        RCU_FLAG_STCM_REC_FAIL: System reset flag STCM_REC_FAIL
    \arg        RCU_FLAG_RCTL_SUBSRU: System reset flag RCTL_SUBSRUF
    \arg        RCU_FLAG_LOHRST: Lost of HXTAL error reset flag
    \arg        RCU_FLAG_LOPRST: Lost of PLL error reset flag
    \arg        RCU_FLAG_CORE_CK_FAIL: Core clock fail reset flag
    \arg        RCU_FLAG_SYS_CK_FAIL: CK_SYS fail reset flag
    \arg        RCU_FLAG_HSM_SYSRST: System reset flag HSM_SYS_RSTF
    \arg        RCU_FLAG_SW_SYSRST: System reset flag SW_SYS_RSTF
    \arg        RCU_FLAG_DBG_SYSRST: System reset flag DBG_SYS_RSTF
    \param[out] none
    \retval     none
*/
void rcu_system_reset_flag_clear(uint32_t sysrst_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_SYS_RESET_FLAG(sysrst_flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0037U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_SYSRSTSTAT = sysrst_flag;
    }
}

/*!
    \brief      clear the subsystem reset flag (API_ID(0x0038U))
    \param[in]  flag: the subsystem reset flag
                 only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_EXTRST: External reset flag EXRF
      \arg        RCU_FLAG_OBSTDBY: Subsystem reset flag OBSTDBY_RSTF
      \arg        RCU_FLAG_FMU: Subsystem reset flag FMU_RSTF
      \arg        RCU_SUBSERSTAT_ST_FINISH: Subsystem reset flag ST_FINISH
      \arg        RCU_FLAG_FWDGT0: Subsystem reset flag FWDGT0_RSTF
      \arg        RCU_FLAG_FWDGT1: Subsystem reset flag FWDGT1_RSTF (not applicable to GD32A711X_A712X)
      \arg        RCU_FLAG_SWRST: Software reset flag
      \arg        RCU_FLAG_WWDGT0: Subsystem reset flag WWDGT0_RSTF
      \arg        RCU_FLAG_WWDGT1: Subsystem reset flag WWDGT1_RSTF (not applicable to GD32A711X_A712X)
      \arg        RCU_FLAG_HSM_WDGT: Subsystem reset flag HSM_WDGT_RSTF
      \arg        RCU_FLAG_HSM_APP: Subsystem reset flag HSM_APP_RSTF
      \arg        RCU_FLAG_SW_SUBS: Subsystem reset flag SW_SUBS_RSTF
      \arg        RCU_FLAG_DBG: Debug reset flag DBG_RSTF
      \arg        RCU_FLAG_OBL: Option byte loader reset flag
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_flag_clear(uint32_t subsysrst_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_SUBSYS_RESET_FLAG(subsysrst_flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0038U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_SUBSERSTAT = subsysrst_flag;
    }
}
/*!
    \brief      get the system reset flags (API_ID(0x0039U))
    \param[in]  flag: the system reset flag
                only one parameter can be selected which is shown as below:
    \arg        RCU_FLAG_POR:Power-on reset flag
    \arg        RCU_FLAG_FMU_REA_FAIL: System reset flag FMU_REA_FAIL
    \arg        RCU_FLAG_STCM_REC_FAIL: System reset flag STCM_REC_FAIL
    \arg        RCU_FLAG_RCTL_SUBSRU: System reset flag RCTL_SUBSRUF
    \arg        RCU_FLAG_LOHRST: Lost of HXTAL error reset flag
    \arg        RCU_FLAG_LOPRST: Lost of PLL error reset flag
    \arg        RCU_FLAG_CORE_CK_FAIL: Core clock fail reset flag
    \arg        RCU_FLAG_SYS_CK_FAIL: CK_SYS fail reset flag
    \arg        RCU_FLAG_HSM_SYSRST: System reset flag HSM_SYS_RSTF
    \arg        RCU_FLAG_SW_SYSRST: System reset flag SW_SYS_RSTF
    \arg        RCU_FLAG_DBG_SYSRST: System reset flag DBG_SYS_RSTF
    \param[out] none
    \retval     none
*/
FlagStatus rcu_system_reset_flag_get(uint32_t sysrst_flag)
{
    FlagStatus flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_SYS_RESET_FLAG(sysrst_flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0039U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the flag */
        if((RCU_SYSRSTSTAT & sysrst_flag) == sysrst_flag) {
            flag = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return flag;
}

/*!
    \brief      get the subsystem reset flags (API_ID(0x003AU))
    \param[in]  flag: the subsystem reset flag
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_EXTRST: External reset flag EXRF
      \arg        RCU_FLAG_OBSTDBY: Subsystem reset flag OBSTDBY_RSTF
      \arg        RCU_FLAG_FMU: Subsystem reset flag FMU_RSTF
      \arg        RCU_SUBSERSTAT_ST_FINISH: Subsystem reset flag ST_FINISH
      \arg        RCU_FLAG_FWDGT0: Subsystem reset flag FWDGT0_RSTF
      \arg        RCU_FLAG_FWDGT1: Subsystem reset flag FWDGT1_RSTF (not applicable to GD32A711X_A712X)
      \arg        RCU_FLAG_SWRST: Software reset flag
      \arg        RCU_FLAG_WWDGT0: Subsystem reset flag WWDGT0_RSTF
      \arg        RCU_FLAG_WWDGT1: Subsystem reset flag WWDGT1_RSTF (not applicable to GD32A711X_A712X)
      \arg        RCU_FLAG_HSM_WDGT: Subsystem reset flag HSM_WDGT_RSTF
      \arg        RCU_FLAG_HSM_APP: Subsystem reset flag HSM_APP_RSTF
      \arg        RCU_FLAG_SW_SUBS: Subsystem reset flag SW_SUBS_RSTF
      \arg        RCU_FLAG_DBG: Debug reset flag DBG_RSTF
      \arg        RCU_FLAG_OBL: Option byte loader reset flag
    \param[out] none
    \retval     none
*/
FlagStatus rcu_subsystem_reset_flag_get(uint32_t subsysrst_flag)
{
    FlagStatus flag;
    flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_SUBSYS_RESET_FLAG(subsysrst_flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x003AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the flag */
        if((RCU_SUBSERSTAT & subsysrst_flag) == subsysrst_flag) {
            flag = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return flag;
}

/*!
    \brief      get subsystem reset upgrade counter (API_ID(0x003BU))
    \param[in]  none
    \param[out] none
    \retval     subsystem reset upgrade counter
*/
uint32_t rcu_subsystem_reset_upgrade_counter_get(void)
{
    return (RCU_SUBSRMUCNT & RCU_SUBSRMUCNT_SUBSRMUCNT);
}

/*!
    \brief      get system reset upgrade counter (API_ID(0x003CU))
    \param[in]  none
    \param[out] none
    \retval     system reset upgrade counter
*/
uint32_t rcu_system_reset_upgrade_counter_get(void)
{
    return (RCU_SYSRSTUCNT & RCU_SYSRSTUCNT_SYSRTOEN);
}

/*!
    \brief      get subsystem reset counter (API_ID(0x003DU))
    \param[in]  none
    \param[out] none
    \retval     subsystem reset counter
*/
uint32_t rcu_subsystem_reset_counter_get(void)
{
    return (RCU_SUBSRSTCNT & RCU_SUBSRSTCNT_SUBSRSTCNT);
}

/*!
    \brief      get system reset upgrade counter (API_ID(0x003EU))
    \param[in]  none
    \param[out] none
    \retval     system reset upgrade counter
*/
uint32_t rcu_system_reset_counter_get(void)
{
    return (RCU_SYSRSTCNT & RCU_SYSRSTCNT_SYSRSTCNT);
}

/*!
    \brief     clear subsystem reset upgrade counter (API_ID(0x003FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_upgrade_counter_clear(void)
{
    RCU_SUBSRMUCNT |= RCU_SUBSRMUCNT_SUBSRMUCNT;
}

/*!
    \brief      clear subsystem reset counter (API_ID(0x0040U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_counter_clear(void)
{
    RCU_SUBSRSTCNT |=  RCU_SUBSRSTCNT_SUBSRSTCNT;
}

/*!
    \brief      clear system reset counter (API_ID(0x0041U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_system_reset_counter_clear(void)
{
    RCU_SYSRSTCNT &= ~ RCU_SYSRSTCNT_SYSRSTCNT;
}

/*!
    \brief      config system reset upgrade threshold (API_ID(0x0042U))
    \param[in]  upgrade_threshold: system reset mode upgrade threshold,only one parameter can be selected
      \arg        This parameter should be selected between 0 and 0xF.
    \param[out] none
    \retval     none
*/
void rcu_system_reset_upgrade_threshold_config(uint32_t upgrade_threshold)
{
    uint32_t reg;
    reg = RCU_SYSMRUTH;
    /* reset the RCU_SYSMRUTH_SYSMRUTH bits and set according to upgrade_threshold */
    reg &= ~RCU_SYSMRUTH_SYSMRUTH;
    RCU_SYSMRUTH = (reg | (uint32_t)(upgrade_threshold & 0xFU));
}


/*! \brief      config subsystem reset upgrade threshold (API_ID(0x0043U))
    \param[in]  upgrade_threshold: subsystem reset mode upgrade counter,only one parameter can be selected
      \arg        This parameter should be selected between 0 and 0xF.
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_upgrade_threshold_config(uint32_t upgrade_threshold)
{
    uint32_t reg;
    reg = RCU_SUBSRMUTH;
    /* reset the RCU_SUBSRMUTH_SUBSRMUTH bits and set according to upgrade_threshold */
    reg &= ~RCU_SUBSRMUTH_SUBSRMUTH;
    RCU_SUBSRMUTH = (reg | (uint32_t)(upgrade_threshold & 0xFU));
}

/*! \brief      enable bus access during SUBSRST1 stage (API_ID(0x0044U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_bus_access_enable(void)
{
    RCU_BUSCTL |= RCU_BUSCTL_BUSCTL;
}

/*! \brief      disable bus access during SUBSRST1 stage (API_ID(0x0045U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_bus_access_disable(void)
{
    RCU_BUSCTL &= ~RCU_BUSCTL_BUSCTL;
}

/*! \brief      enable external reset pin assert (API_ID(0x0046U)) NOTE: this API must use only as part of the mainreset domain self-test entry procedure.
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_external_reset_pin_assert_enable(void)
{
    RCU_ERPACFG |= RCU_ERPACFG_ERPAETEN;
}

/*! \brief      disable external reset pin assert (API_ID(0x0047U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_external_reset_pin_assert_disable(void)
{
    RCU_ERPACFG &= ~RCU_ERPACFG_ERPAETEN;
}

/*! \brief      config subsystem reset timer value (API_ID(0x0048U))
    \param[in]  timeout: subsystem reset mode upgrade counter
      \arg        This parameter should be selected between 0 and 0x7FFFFFFF.
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_timeout_config(uint32_t timeout)
{
    uint32_t reg;
    reg = RCU_SUBSRTO;
    /* reset the RCU_SUBSRTO_SUBSRTO bits and set according to timeout */
    reg &= ~RCU_SUBSRTO_SUBSRTO;
    RCU_SUBSRTO = (reg | (uint32_t)((timeout & 0x7FFFFFFFU) << 1U));
}

/*!
    \brief      enable subsystem reset entry timer (API_ID(0x0049U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_entry_timer_enable(void)
{
    RCU_SUBSRTO |= RCU_SUBSRTO_SUBSRTOEN;
}

/*!
    \brief      disable subsystem reset entry timer (API_ID(0x004AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_entry_timer_disable(void)
{
    RCU_SUBSRTO &= ~RCU_SUBSRTO_SUBSRTOEN;
}

/*!
    \brief      enable subsystem reset request (API_ID(0x004BU))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
ErrStatus rcu_all_subsystem_reset_request_enable(void)
{
    ErrStatus status;
    RCU_SUBSRSTAD = 0x112B112BU;
    if(0U == (RCU_SUBSRSTAD & RCU_SUBSRSTAD_SUBSRST_ALL_DIS)) {
        status = SUCCESS;
    } else {
        status = ERROR;
    }
    return status;
}

/*!
    \brief      disable subsystem reset request (API_ID(0x004CU))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
ErrStatus rcu_all_subsystem_reset_request_disable(void)
{
    ErrStatus status;
    RCU_SUBSRSTAD = 0xA211A211U;
    if(0U != (RCU_SUBSRSTAD & RCU_SUBSRSTAD_SUBSRST_ALL_DIS)) {
        status = SUCCESS;
    } else {
        status = ERROR;
    }
    return status;
}

/*! \brief      get the standby reset flags (API_ID(0x004DU))
    \param[in]  flag: standby reset flag
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_SYSRST: system reset event occurred flag in standby mode
      \arg        RCU_FLAG_SUBSRST: subsystem reset event occurred flag in standby mode
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_standby_reset_flag_get(uint32_t flag)
{
    FlagStatus reset_flag = RESET;
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_STANDBY_RESET_FLAG(flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x004DU), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the loss of lock detector flag */
        if(flag == (RCU_RDSMSTAT & flag)) {
            reset_flag = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return reset_flag;
}

/*!
    \brief      clear the standby reset flags (API_ID(0x004EU))
    \param[in]  flag: standby reset flag
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_SYSRST: system reset event occurred flag in standby mode
      \arg        RCU_FLAG_SUBSRST: subsystem reset event occurred flag in standby mode
    \param[out] none
    \retval     none
*/
void rcu_standby_reset_flag_clear(uint32_t flag)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_STANDBY_RESET_FLAG(flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x004EU), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_RDSMSTAT |= flag;
    }
}

/*!
    \brief      get the low power debug flag (API_ID(0x004FU))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_low_power_debug_flag_get(void)
{
    FlagStatus flag;
    /* get the loss of lock detector flag */
    if(RCU_FLAG_LPDBG == (RCU_LPDBGSTAT & RCU_FLAG_LPDBG)) {
        flag = SET;
    } else {
        flag = RESET;
    }
    return flag;
}

/*!
    \brief      get the por watchdog overflow flags (API_ID(0x0050U))
    \param[in]  flag: por watchdog overflow flags
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_OVFx: x=0,..,6 or x=10,11,14(for GD32A711X_A712X),20 or x=29,..,30.
      \arg        RCU_FLAG_OVFx: x=32,..,63.
      \arg        RCU_FLAG_OVFx: x=64,..,95.
      \arg        RCU_FLAG_OVF96.
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_por_watchdog_overflow_flag_get(por_watchdog_overflow_flag_enum flag)
{
    FlagStatus verflow_flag = RESET;

    /* get the loss of lock detector flag */
    if(0U != (RCU_RCTL_REG_VAL(flag) & BIT(RCU_BIT_POS(flag)))) {
        verflow_flag = SET;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    return verflow_flag;
}

/*!
    \brief      clear the por watchdog overflow flags (API_ID(0x0051U))
    \param[in]  flag: por watchdog overflow flags
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_OVFx: x=0,..,6 or x=10,11,14(for GD32A711X_A712X),20 or x=29,..,30.
      \arg        RCU_FLAG_OVFx: x=32,..,63.
      \arg        RCU_FLAG_OVFx: x=64,..,95.
      \arg        RCU_FLAG_OVF96.
    \param[out] none
    \retval     none
*/
void rcu_por_watchdog_overflow_flag_clear(por_watchdog_overflow_flag_enum flag)
{
    RCU_RCTL_REG_VAL(flag) |= BIT(RCU_BIT_POS(flag));
}


/*!
    \brief      get the clock stabilization and peripheral reset flags (API_ID(0x0052U))
    \param[in]  flag: the clock stabilization and peripheral reset flags, refer to rcu_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_HXTALSTB: HXTAL stabilization flag
      \arg        RCU_FLAG_PLLSTB: PLL stabilization flag
      \arg        RCU_FLAG_LXTALSTB: LXTAL stabilization flag
    \param[out] none
    \retval     none
*/
FlagStatus rcu_flag_get(rcu_flag_enum flag)
{
    FlagStatus return_flag;
    return_flag = RESET;

    /* get the rcu flag */
    if(0U != (RCU_CCTL_REG_VAL(flag) & BIT(RCU_BIT_POS(flag)))) {
        return_flag = SET;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    return return_flag;
}

/*!
    \brief      get the clock stabilization interrupt and ckm flags (API_ID(0x0053U))
    \param[in]  int_flag: interrupt and ckm flags, refer to rcu_int_flag_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_LXTALSTB: LXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_HXTALSTB: HXTAL stabilization interrupt flag
      \arg        RCU_INT_FLAG_PLLSTB: PLL stabilization interrupt flag
      \arg        RCU_INT_FLAG_CKM: HXTAL clock stuck interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag)
{
    FlagStatus flag = RESET;

    /* get the rcu interrupt flag */
    if(0U != (RCU_CCTL_REG_VAL(int_flag) & BIT(RCU_BIT_POS(int_flag)))) {
        flag = SET;
    } else {
        /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
    }
    return flag;
}

/*!
    \brief      clear the interrupt flags (API_ID(0x0054U))
    \param[in]  int_flag: clock stabilization and stuck interrupt flags clear, refer to rcu_int_flag_clear_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_FLAG_LXTALSTB_CLR: LXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_HXTALSTB_CLR: HXTAL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_PLLSTB_CLR: PLL stabilization interrupt flag clear
      \arg        RCU_INT_FLAG_CKM_CLR: HXTAL clock monitor interrupt flag clear
    \param[out] none
    \retval     none
*/
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag)
{
    RCU_CCTL_REG_VAL(int_flag) |= BIT(RCU_BIT_POS(int_flag));
}

/*!
    \brief      enable the stabilization interrupt (API_ID(0x0055U))
    \param[in]  interrupt: clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt
      \arg        RCU_INT_PLLSTB: PLL stabilization interrupt
    \param[out] none
    \retval     none
*/
void rcu_interrupt_enable(rcu_int_enum interrupt)
{
    RCU_CCTL_REG_VAL(interrupt) |= BIT(RCU_BIT_POS(interrupt));
}

/*!
    \brief      disable the stabilization interrupt (API_ID(0x0056U))
    \param[in]  interrupt clock stabilization interrupt, refer to rcu_int_enum
                only one parameter can be selected which is shown as below:
      \arg        RCU_INT_LXTALSTB: LXTAL stabilization interrupt
      \arg        RCU_INT_HXTALSTB: HXTAL stabilization interrupt
      \arg        RCU_INT_PLLSTB: PLL stabilization interrupt
    \param[out] none
    \retval     none
*/
void rcu_interrupt_disable(rcu_int_enum interrupt)
{
    RCU_CCTL_REG_VAL(interrupt) &= ~BIT(RCU_BIT_POS(interrupt));
}

/*!    \brief      enable the RCTL triple modular redundancy error output (API_ID(0x0057U))
    \param[in]  rctl_tmr: RCTL triple modular redundancy error output enable
                only one parameter can be selected which is shown as below:
      \arg        RCU_TMRERRSTAT_TMR_RCU_SYSRSTSTATEN: RCU_SUBSERSTAT TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_RCU_SUBSRCTLEN: RCU_SUBSRCTL TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_RCU_SUBSRPACTLEN: RCU_SUBSRPACTL TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_RCU_SYSMRETHEN: RCU_SYSMRETH TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_RCU_ERPACFGEN: RCU_ERPACFG TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_AHBRSTEN: TMR_AHBRST TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_APBRSTEN: TMR_APBRST TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_PORWDG1EN: TMR_PORWDG1 TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_PORWDG2EN: TMR_PORWDG2 TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_PORWDG3EN: TMR_PORWDG3 TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_PORWDG4EN: TMR_PORWDG4 TMR error output enable
    \param[out] none
    \retval     none
*/
void rcu_rctl_tmr_enable(uint32_t rctl_tmr)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_TMRERRSTAT_TMR_EN(rctl_tmr)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0057U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_TMRERRSTAT |= rctl_tmr;
    }
}

/*! \brief      disable the RCTL triple modular redundancy error output (API_ID(0x0058U))
    \param[in]  rctl_tmr: RCTL triple modular redundancy error output disable
                only one parameter can be selected which is shown as below:
      \arg        RCU_TMRERRSTAT_TMR_RCU_SYSRSTSTATEN: RCU_SUBSERSTAT TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_RCU_SUBSRCTLEN: RCU_SUBSRCTL TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_RCU_SUBSRPACTLEN: RCU_SUBSRPACTL TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_RCU_SYSMRETHEN: RCU_SYSMRETH TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_RCU_ERPACFGEN: RCU_ERPACFG TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_AHBRSTEN: TMR_AHBRST TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_APBRSTEN: TMR_APBRST TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_PORWDG1EN: TMR_PORWDG1 TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_PORWDG2EN: TMR_PORWDG2 TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_PORWDG3EN: TMR_PORWDG3 TMR error output enable
      \arg        RCU_TMRERRSTAT_TMR_PORWDG4EN: TMR_PORWDG4 TMR error output enable
    \param[out] none
    \retval     none
*/
void rcu_rctl_tmr_disable(uint32_t rctl_tmr)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_TMRERRSTAT_TMR_EN(rctl_tmr)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0058U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_TMRERRSTAT &= ~rctl_tmr;
    }
}

/*! \brief      enable the CCTL triple modular redundancy error output (API_ID(0x0059U))
    \param[in]  cctl_tmr: CCTL triple modular redundancy error output enable
                only one parameter can be selected which is shown as below:
      \arg        RCU_BUSIM_TMR_TMR_EN0: TMR error 0 output to fmu enable
      \arg        RCU_BUSIM_TMR_TMR_EN1: TMR error 1 output to fmu enable
      \arg        RCU_BUSIM_TMR_TMR_EN2: TMR error 2 output to fmu enable
      \arg        RCU_BUSIM_TMR_TMR_EN3: TMR error 3 output to fmu enable
    \param[out] none
    \retval     none
*/
void rcu_cctl_tmr_enable(uint32_t cctl_tmr)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_BUSIM_TMR_TMR_EN(cctl_tmr)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0059U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_BUSIM_TMR |= cctl_tmr;
    }
}

/*!
    \brief      disable the CCTL triple modular redundancy error output (API_ID(0x005AU))
    \param[in]  cctl_tmr: CCTL triple modular redundancy error output disable
                only one parameter can be selected which is shown as below:
      \arg        RCU_BUSIM_TMR_TMR_EN0: TMR error 0 output to fmu enable
      \arg        RCU_BUSIM_TMR_TMR_EN1: TMR error 1 output to fmu enable
      \arg        RCU_BUSIM_TMR_TMR_EN2: TMR error 2 output to fmu enable
      \arg        RCU_BUSIM_TMR_TMR_EN3: TMR error 3 output to fmu enable
    \param[out] none
    \retval     none
*/
void rcu_cctl_tmr_disable(uint32_t cctl_tmr)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_BUSIM_TMR_TMR_EN(cctl_tmr)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x005AU), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_BUSIM_TMR &= ~cctl_tmr;
    }
}

/*!
    \brief      get the RCTL TMR flags (API_ID(0x005BU))
    \param[in]  rctl_tmr_flag: RCTL TMR flags
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_RCU_SYSRSTSTAT: RCU_SYSRSTSTAT TMR error status
      \arg        RCU_FLAG_RCU_SUBSRCTL: RCU_SUBSRCTL TMR error status
      \arg        RCU_FLAG_RCU_SUBSRPACTL: RCU_SUBSRPACTL TMR error status
      \arg        RCU_FLAG_RCU_SYSMRETH: RCU_SYSMRETH TMR error status
      \arg        RCU_FLAG_RCU_ERPACFG: RCU_ERPACFG TMR error status
      \arg        RCU_FLAG_AHBRST: AHBRST TMR error status
      \arg        RCU_FLAG_APBRST: APBRST1/2 TMR error status
      \arg        RCU_FLAG_PORWDG1: PORWDG1 TMR error status
      \arg        RCU_FLAG_PORWDG2: PORWDG2 TMR error status
      \arg        RCU_FLAG_PORWDG3: PORWDG3 TMR error status
      \arg        RCU_FLAG_PORWDG4: PORWDG4 TMR error status
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_rctl_tmr_flag_get(uint32_t rctl_tmr_flag)
{
    FlagStatus flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_RCTL_TMR_FLAG(rctl_tmr_flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x005BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the RCTL TMR flag */
        if(0U != (RCU_TMRERRSTAT & rctl_tmr_flag)) {
            flag = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return flag;
}

/*!
    \brief      clear the RCTL TMR flags (API_ID(0x005CU))
    \param[in]  rctl_tmr_flag: RCTL TMR flags clear
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_RCU_SYSRSTSTAT: RCU_SYSRSTSTAT TMR error status
      \arg        RCU_FLAG_RCU_SUBSRCTL: RCU_SUBSRCTL TMR error status
      \arg        RCU_FLAG_RCU_SUBSRPACTL: RCU_SUBSRPACTL TMR error status
      \arg        RCU_FLAG_RCU_SYSMRETH: RCU_SYSMRETH TMR error status
      \arg        RCU_FLAG_RCU_ERPACFG: RCU_ERPACFG TMR error status
      \arg        RCU_FLAG_AHBRST: AHBRST TMR error status
      \arg        RCU_FLAG_APBRST: APBRST1/2 TMR error status
      \arg        RCU_FLAG_PORWDG1: PORWDG1 TMR error status
      \arg        RCU_FLAG_PORWDG2: PORWDG2 TMR error status
      \arg        RCU_FLAG_PORWDG3: PORWDG3 TMR error status
      \arg        RCU_FLAG_PORWDG4: PORWDG4 TMR error status
    \param[out] none
    \retval     none
*/
void rcu_rctl_tmr_flag_clear(uint32_t rctl_tmr_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_RCTL_TMR_FLAG(rctl_tmr_flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x005CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_TMRERRSTAT |= rctl_tmr_flag;
    }
}

/*!
    \brief      get the CCTL TMR flags (API_ID(0x005DU))
    \param[in]  cctl_tmr_flag: CCTL TMR flags
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_ST0: System clock switching TMR error status
      \arg        RCU_FLAG_ST1: Clock enable TMR error status
      \arg        RCU_FLAG_ST2: Clock monitor enable register TMR error status
      \arg        RCU_FLAG_ST3: the TMR error occurs in any bit of TRIM register
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_cctl_tmr_flag_get(uint32_t cctl_tmr_flag)
{
    FlagStatus flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CCTL_TMR_FLAG(cctl_tmr_flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x005DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the CCTL TMR flag */
        if(0U != (RCU_BUSIM_TMR & cctl_tmr_flag)) {
            flag = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return flag;
}

/*!
    \brief      clear the CCTL TMR flags (API_ID(0x005EU))
    \param[in]  cctl_tmr_flag: CCTL TMR flags clear
                only one parameter can be selected which is shown as below:
      \arg        RCU_FLAG_ST0: System clock switching TMR error status
      \arg        RCU_FLAG_ST1: Clock enable TMR error status
      \arg        RCU_FLAG_ST2: Clock monitor enable register TMR error status
      \arg        RCU_FLAG_ST3: the TMR error occurs in any bit of TRIM register
    \param[out] none
    \retval     none
*/
void rcu_cctl_tmr_flag_clear(uint32_t cctl_tmr_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_CCTL_TMR_FLAG(cctl_tmr_flag)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x005EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        RCU_BUSIM_TMR |= cctl_tmr_flag;
    }
}

/*!
    \brief      adjust the PLL loss of lock accuracy (API_ID(0x005FU))
    \param[in]  lol_accuracy: PLL loss of lock accuracy
                only one parameter can be selected which is shown as below:
      \arg        RCU_PLLLOL_UNLOCK_RANGE_1: (expected value(100) - 5) <= Unlock range <= (expected value(100) + 5)
      \arg        RCU_PLLLOL_UNLOCK_RANGE_2: (expected value(100) - 9) <= Unlock range <= (expected value(100) + 9)
      \arg        RCU_PLLLOL_UNLOCK_RANGE_3: (expected value(100) - 17) <= Unlock range <= (expected value(100) + 17)
      \arg        RCU_PLLLOL_UNLOCK_RANGE_4: (expected value(100) - 33) <= Unlock range <= (expected value(100) + 33)
    \param[out] none
    \retval     none
*/
void rcu_pll_loss_of_lock_config(uint32_t lol_accuracy)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_PLLLOL_UNLOCK_RANGE(lol_accuracy)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x005FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_PLLLOL;
        /* reset the RCU_PLLLOL_PLLLOLCTL bits and set according to lol_accuracy */
        reg &= ~RCU_PLLLOL_PLLLOLCTL;
        RCU_PLLLOL = (reg | (uint32_t)(lol_accuracy));
    }
}

/*!
    \brief      get the loss of lock detector flag (API_ID(0x0060U))
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus rcu_pll_loss_of_lock_flag_get(void)
{
    FlagStatus flag;
    /* get the loss of lock detector flag */
    if(0U != (RCU_PLLLOL & RCU_FLAG_PLLLOL)) {
        flag = SET;
    } else {
        flag = RESET;
    }
    return flag;
}

/*!
    \brief      clear the loss of lock detector flag (API_ID(0x0061U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_pll_loss_of_lock_flag_clear(void)
{
    RCU_PLLLOL |= RCU_PLLLOL_PLLLOLFC;
}

/*!
    \brief      config fractional part of the multiplication factor for PLL VCO (API_ID(0x0062U))
    \param[in]  pll_fractional: fractional part of the multiplication factor,only one parameter can be selected
    \param[out] none
    \retval     none
*/
void rcu_pll_fractional_config(uint32_t pll_fractional)
{
    uint32_t reg;
    reg = RCU_PLLFRA;
    /* reset the RCU_PLLFRA_PLLFRACN bits and set according to pll_fractional */
    reg &= ~RCU_PLLFRA_PLLFRACN;
    RCU_PLLFRA = (reg | (uint32_t)(pll_fractional & 0x3FFFU));
}

/*!
    \brief      enable PLL fractional latch (API_ID(0x0063U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_pll_fractional_latch_enable(void)
{
    RCU_PLLFRA |= RCU_PLLFRA_PLLFRAEN;
}

/*!
    \brief      disable PLL fractional latch (API_ID(0x0064U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_pll_fractional_latch_disable(void)
{
    RCU_PLLFRA &= ~RCU_PLLFRA_PLLFRAEN;
}

/*!
    \brief    configure the spread spectrum modulation for the main PLL clock (API_ID(0x0065U))
    \param[in]  spread_spectrum_type: PLL spread spectrum modulation type select
                only one parameter can be selected which is shown as below:
      \arg        RCU_SS_TYPE_CENTER: center spread type is selected
      \arg        RCU_SS_TYPE_DOWN: down spread type is selected
    \param[in]  modstep: configure PLL spread spectrum modulation profile amplitude and frequency
                only one parameter can be selected which is shown as below:
      \arg        This parameter should be selected between 0 and 0x3FF.The following criteria must be met: MODSTEP*MODCNT <=2^14
    \param[in]  modcnt: configure PLL spread spectrum modulation profile amplitude and frequency
                only one parameter can be selected which is shown as below:
      \arg        This parameter should be selected between 0 and 0x7FF.The following criteria must be met: MODSTEP*MODCNT <=2^14
    \param[out] none
    \retval     none
*/
void rcu_spread_spectrum_config(uint32_t spread_spectrum_type, uint32_t modstep, uint32_t modcnt)
{
    uint32_t reg;
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_SS_TYPE(spread_spectrum_type)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0065U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = RCU_PLLSSCTL;
        /* reset the RCU_PLLSSCTL register bits */
        reg &= ~(RCU_PLLSSCTL_MODCNT | RCU_PLLSSCTL_MODSTEP | RCU_PLLSSCTL_SS_TYPE);
        RCU_PLLSSCTL = (reg | spread_spectrum_type | ((modstep & 0x3FFU) << 13U) | (modcnt & 0x7FFU));
    }
}

/*!
    \brief    disble the PLL spread spectrum modulation (API_ID(0x0066U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_spread_spectrum_disable(void)
{
    RCU_PLLSSCTL |= RCU_PLLSSCTL_SSCGBYP;
}

/*!
    \brief    enable the PLL spread spectrum modulation (API_ID(0x0067U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rcu_spread_spectrum_enable(void)
{
    RCU_PLLSSCTL &= ~RCU_PLLSSCTL_SSCGBYP;
}

/*!
    \brief      config subsystem reset (API_ID(0x0068U))
    \param[in]  subsysrsrt: subsystem reset type
                one or more parameter can be selected which is shown as below:
      \arg        RCU_SUBSRCTL_FMU_RST_RD: subsystem reset FMU_RST
      \arg        RCU_SUBSRCTL_FWDGT0_RST_RD: subsystem reset FWDGT0_RST
      \arg        RCU_SUBSRCTL_FWDGT1_RST_RD: subsystem reset FWDGT1_RST (not for GD32A711X_A712X)
      \arg        RCU_SUBSRCTL_WWDGT0_RST_RD: subsystem reset WWDGT0_RST
      \arg        RCU_SUBSRCTL_WWDGT1_RST_RD: subsystem reset WWDGT1_RST (not for GD32A711X_A712X)
      \arg        RCU_SUBSRCTL_DBG_RST_RD: subsystem reset DBG_RST
      \arg        RCU_SUBSRCTL_OBL_RST_RD: subsystem reset OBL_RST (not for GD32A711X_A712X)
    \param[in]  reset_config: trigger a reset or trigger an interrupt.
                only one parameter can be selected which is shown as below:
      \arg        DISABLE: trigger a reset
      \arg        ENABLE: trigger an interrupt
    \param[out] none
    \retval     none
    \note       this register can be written to only once after a system reset or POR reset and this register is
                reset only on POR reset and any system reset.
*/
void rcu_subsystem_reset_config(uint32_t subsysrsrt, ControlStatus reset_config)
{    
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CTL_STATUS(reset_config)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0068U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        if(reset_config == DISABLE) {
            RCU_SUBSRCTL &= ~subsysrsrt;
        } else {
            RCU_SUBSRCTL |= subsysrsrt;
        }
    }
}

/*!
    \brief      config subsystem reset pin assertion (API_ID(0x0069U))
    \param[in]  subsysrsrt: subsystem reset type
                only one parameter can be selected which is shown as below:
      \arg        RCU_SUBSRPACTL_ST_FINISH_RPAEN: Reset pin assert enable for subsystem reset ST_FINISH
    \param[in]  reset_pin_assert: External reset pin assertion control
                only one parameter can be selected which is shown as below:
      \arg        DISABLE: do not assert the external reset pin
      \arg        ENABLE: assert the external reset pin
    \param[out] none
    \retval     none
*/
void rcu_subsystem_reset_pin_assertion_config(uint32_t subsysrsrt, ControlStatus reset_pin_assert)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_RCU_SUBSRPACTL_RPAEN(subsysrsrt)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0069U), ERR_PARAM_INVALID);   
    } else if(NOT_CTL_STATUS(reset_pin_assert)) {
        fw_debug_report_err(RCU_MODULE_ID, API_ID(0x0069U), ERR_PARAM_INVALID);
    } else
    #endif /* FW_DEBUG_ERR_REPORT */
    {
        if(reset_pin_assert == DISABLE) {
            RCU_SUBSRPACTL &= ~subsysrsrt;
        } else {
            RCU_SUBSRPACTL |= subsysrsrt;
        }
    }
}
