/*!
    \file    gd32a7xx_rcu.h
    \brief   definitions for the RCU

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

#ifndef GD32A7XX_RCU_H
#define GD32A7XX_RCU_H

#include "gd32a7xx.h"


/* RCU definitions */
#define CCTL                            RCU_BASE                                               /*!< CCTL base address */
#define RCTL                            RCU_BASE+0x2C00U                                       /*!< RCTL base address */
                                                                                         
/* CCTL registers definitions */                                                         
#define RCU_CTL                         REG32(CCTL + 0x00000000U)                              /*!< control register */
#define RCU_CFG0                        REG32(CCTL + 0x00000004U)                              /*!< clock configuration register 0 */
#define RCU_INT                         REG32(CCTL + 0x00000008U)                              /*!< clock interrupt register */
#define RCU_AHBEN                       REG32(CCTL + 0x00000014U)                              /*!< AHB enable register */
#define RCU_APB2EN                      REG32(CCTL + 0x00000018U)                              /*!< APB2 enable register */
#define RCU_APB1EN                      REG32(CCTL + 0x0000001CU)                              /*!< APB1 enable register */
#define RCU_BDCTL                       REG32(CCTL + 0x00000020U)                              /*!< backup domain control register */
#define RCU_APB2EN_ADD                  REG32(CCTL + 0x00000024U)                              /*!< APB2 enable additional register */
#define RCU_AHBEN_ADD                   REG32(CCTL + 0x00000028U)                              /*!< AHB enable additional register */
#define RCU_CFG1                        REG32(CCTL + 0x0000002CU)                              /*!< clock configuration register 1 */
#define RCU_CFG2                        REG32(CCTL + 0x00000030U)                              /*!< clock configuration register 2 */
#define RCU_CFG3                        REG32(CCTL + 0x00000034U)                              /*!< clock configuration register 3 */
#define RCU_PLLLOL                      REG32(CCTL + 0x00000038U)                              /*!< PLL loss of lock register */
#define RCU_CKDCTL                      REG32(CCTL + 0x0000003CU)                              /*!< Clock detect control register */
#define RCU_CKFMCTL(ckfmx)              REG32(((CCTL) + 0x40U) + 0x10U * (ckfmx))              /*!< Clock frequency monitor control register */
#define RCU_CKFMRCCFG(ckfmx)            REG32(((CCTL) + 0x44U) + 0x10U * (ckfmx))              /*!< Clock frequency monitor reference count configuration register */
#define RCU_CKFMHTHCFG(ckfmx)           REG32(((CCTL) + 0x48U) + 0x10U * (ckfmx))              /*!< CKFM high threshold configuration register */
#define RCU_CKFMLTHCFG(ckfmx)           REG32(((CCTL) + 0x4CU) + 0x10U * (ckfmx))              /*!< CKFM low threshold configuration register */
#define RCU_BUSIM_TMR                   REG32(CCTL + 0x00000090U)                              /*!< CCTL TMR register */
#define RCU_PLLFRA                      REG32(CCTL + 0x00000098U)                              /*!< PLL fraction configuration register */
#define RCU_PLLSSCTL                    REG32(CCTL + 0x0000009CU)                              /*!< PLL clock spread spectrum control register */
                                                                                         
/* RCTL registers definitions */                                                         
#define RCU_SYSRSTSTAT                  REG32(RCTL + 0x00000000U)                              /*!< System reset status register */
#define RCU_BUSCTL                      REG32(RCTL + 0x00000004U)                              /*!< Bus control register */
#define RCU_SUBSERSTAT                  REG32(RCTL + 0x00000008U)                              /*!< Subsystem/external reset status register */
#define RCU_SUBSRCTL                    REG32(RCTL + 0x0000000CU)                              /*!< Subsystem reset control register */
#define RCU_SUBSRPACTL                  REG32(RCTL + 0x00000010U)                              /*!< Subsystem reset pin assert control register */
#define RCU_SUBSRMUCNT                  REG32(RCTL + 0x00000014U)                              /*!< Subsystem reset mode upgrade counter register */
#define RCU_SUBSRMUTH                   REG32(RCTL + 0x00000018U)                              /*!< Subsystem reset mode upgrade threshold register  */
#define RCU_SYSMRUTH                    REG32(RCTL + 0x0000001CU)                              /*!< System reset mode upgrade threshold register */
#define RCU_ERPACFG                     REG32(RCTL + 0x00000020U)                              /*!< External reset pin assert configuration register */
#define RCU_RDSMSTAT                    REG32(RCTL + 0x00000024U)                              /*!< Reset during standby mode status register */
#define RCU_SUBSRTO                     REG32(RCTL + 0x00000028U)                              /*!< Subsystem reset timeout register */
#define RCU_LPDBGSTAT                   REG32(RCTL + 0x0000002CU)                              /*!< Low power debug status register */
#define RCU_AHBRST                      REG32(RCTL + 0x00000030U)                              /*!< AHB reset register */
#define RCU_APB1RST                     REG32(RCTL + 0x00000034U)                              /*!< APB1 reset register */
#define RCU_APB2RST                     REG32(RCTL + 0x00000038U)                              /*!< APB2 reset register */
#define RCU_APB2RST_ADD                 REG32(RCTL + 0x0000003CU)                              /*!< APB2 reset additional register */
#define RCU_PORSTAT0                    REG32(RCTL + 0x00000040U)                              /*!< Power-on reset during POR watchdog overflows status register 0 */
#define RCU_PORSTAT1                    REG32(RCTL + 0x00000044U)                              /*!< Power-on reset during POR watchdog overflows status register 1 */
#define RCU_PORSTAT2                    REG32(RCTL + 0x00000048U)                              /*!< Power-on reset during POR watchdog overflows status register 2 */
#define RCU_PORSTAT3                    REG32(RCTL + 0x0000004CU)                              /*!< Power-on reset during POR watchdog overflows status register 3 */
#define RCU_TMRERRSTAT                  REG32(RCTL + 0x00000050U)                              /*!< Triple modular redundancy error status */
#define RCU_SYSRSTUCNT                  REG32(RCTL + 0x00000054U)                              /*!< System reset upgrade counter register */
#define RCU_SUBSRSTCNT                  REG32(RCTL + 0x00000058U)                              /*!< Subsystem reset counter register */
#define RCU_SYSRSTCNT                   REG32(RCTL + 0x0000005CU)                              /*!< System reset counter register */
#define RCU_SUBSRSTAD                   REG32(RCTL + 0x00000060U)                              /*!< Subsystem reset all disable register */

/* bits definitions */
/* RCU_CTL */
#define RCU_CTL_IRC48MADJ               BITS(3,7)                                              /*!< internal 48M RC oscillator clock trim adjust value */
#define RCU_CTL_IRC48MCALIB             BITS(8,15)                                             /*!< internal 48M RC oscillator calibration value */
#define RCU_CTL_HXTALEN                 BIT(16)                                                /*!< external high speed oscillator enable */
#define RCU_CTL_HXTALSTB                BIT(17)                                                /*!< external crystal oscillator clock stabilization flag */
#define RCU_CTL_HXTALBPS                BIT(18)                                                /*!< external crystal oscillator clock bypass mode enable */
#define RCU_CTL_CKMEN                   BIT(19)                                                /*!< HXTAL clock monitor enable */
#define RCU_CTL_LXTALSTBC               BIT(20)                                                /*!< clear LXTAL clock stabilization flag */
#define RCU_CTL_HXTALSCAL               BITS(22,23)                                            /*!< HXTAL frequency scale select */
#define RCU_CTL_PLLEN                   BIT(24)                                                /*!< PLL enable */
#define RCU_CTL_PLLSTB                  BIT(25)                                                /*!< PLL clock stabilization flag */
#define RCU_CTL_HXTALSTBC               BIT(28)                                                /*!< clear external crystal oscillator clock stabilization flag */
                                                                                    
/* RCU_CFG0 */                                                                      
#define RCU_CFG0_SCS                    BITS(0,1)                                              /*!< system clock switch */
#define RCU_CFG0_SCSS                   BITS(2,3)                                              /*!< system clock switch status */
#define RCU_CFG0_AHBPSC                 BITS(4,7)                                              /*!< AHB prescaler selection */
#define RCU_CFG0_APB1PSC                BITS(8,10)                                             /*!< APB1 prescaler selection */
#define RCU_CFG0_APB2PSC                BITS(11,13)                                            /*!< APB2 prescaler selection */
#define RCU_CFG0_PLLSEL                 BIT(16)                                                /*!< PLL clock source selection */
#define RCU_CFG0_PLLMF                  BITS(17,23)                                            /*!< PLL clock multiplication factor */
#define RCU_CFG0_CKOUT1SEL              BITS(24,26)                                            /*!< CKOUT clock source selection */
#define RCU_CFG0_PLLMF_7                BIT(27)                                                /*!< bit 7 of PLLMF */
#define RCU_CFG0_CKOUT1DIV              BITS(28,30)                                            /*!< CK_OUT divider which the CK_OUT frequency can be reduced */
#define RCU_CFG0_PLLDV                  BIT(31)                                                /*!< CK_PLL divide by 1 or 2 for CK_OUT0 */
                                                                                    
/* RCU_INT */                                                                       
#define RCU_INT_LXTALSTBIF              BIT(1)                                                /*!< LXTAL stabilization interrupt flag */
#define RCU_INT_HXTALSTBIF              BIT(3)                                                /*!< HXTAL stabilization interrupt flag */
#define RCU_INT_PLLSTBIF                BIT(4)                                                /*!< PLL stabilization interrupt flag */
#define RCU_INT_CKMIF                   BIT(7)                                                /*!< HXTAL clock stuck interrupt flag */
#define RCU_INT_LXTALSTBIE              BIT(9)                                                /*!< LXTAL stabilization interrupt enable */
#define RCU_INT_HXTALSTBIE              BIT(11)                                               /*!< HXTAL stabilization interrupt enable */
#define RCU_INT_PLLSTBIE                BIT(12)                                               /*!< PLL stabilization interrupt enable */
#define RCU_INT_LXTALSTBIC              BIT(17)                                               /*!< LXTAL stabilization interrupt clear */
#define RCU_INT_HXTALSTBIC              BIT(19)                                               /*!< HXTAL stabilization interrupt clear */
#define RCU_INT_PLLSTBIC                BIT(20)                                               /*!< PLL stabilization interrupt clear */
#define RCU_INT_CKMIC                   BIT(23)                                               /*!< HXTAL clock stuck interrupt clear */

/* RCU_AHBRST */
#define RCU_AHBRST_PARST                  BIT(0)                                              /*!< GPIOA reset */
#define RCU_AHBRST_PBRST                  BIT(1)                                              /*!< GPIOB reset */
#define RCU_AHBRST_PCRST                  BIT(2)                                              /*!< GPIOC reset */
#define RCU_AHBRST_PDRST                  BIT(3)                                              /*!< GPIOD reset */
#define RCU_AHBRST_PERST                  BIT(4)                                              /*!< GPIOE reset */
#define RCU_AHBRST_PFRST                  BIT(5)                                              /*!< GPIOF reset */
#define RCU_AHBRST_PGRST                  BIT(6)                                              /*!< GPIOG reset */
#define RCU_AHBRST_PHRST                  BIT(7)                                              /*!< GPIOH reset */
#define RCU_AHBRST_PIRST                  BIT(8)                                              /*!< GPIOI reset */
#define RCU_AHBRST_PJRST                  BIT(9)                                              /*!< GPIOJ reset */
#define RCU_AHBRST_PKRST                  BIT(10)                                             /*!< GPIOK reset */
#define RCU_AHBRST_PLRST                  BIT(11)                                             /*!< GPIOL reset */
#define RCU_AHBRST_PMRST                  BIT(12)                                             /*!< GPIOM reset */
#define RCU_AHBRST_PNRST                  BIT(13)                                             /*!< GPION reset */
#define RCU_AHBRST_DMA0RST                BIT(14)                                             /*!< DMA0 reset */
#define RCU_AHBRST_DMA1RST                BIT(15)                                             /*!< DMA1 reset */
#define RCU_AHBRST_DMAMUXRST              BIT(16)                                             /*!< DMAMUX reset */
#define RCU_AHBRST_QSPIRST                BIT(18)                                             /*!< QSPI reset */
#define RCU_AHBRST_CRCRST                 BIT(20)                                             /*!< CRC reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_AHBRST_MFCOMRST               BIT(21)                                             /*!< MFCOM reset */
#define RCU_AHBRST_MCMUARST               BIT(22)                                             /*!< MCMUA reset */
#define RCU_AHBRST_MCMUBRST               BIT(23)                                             /*!< MCMUB reset */
#define RCU_AHBRST_HWSEMRST               BIT(24)                                             /*!< HWSEM reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_AHBRST_HSMIFRST               BIT(25)                                             /*!< HSMIF reset */
#define RCU_AHBRST_IRMRST                 BIT(28)                                             /*!< IRM reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_AHBRST_IOCRST                 BIT(29)                                             /*!< IOC reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_AHBRST_STCMRST                BIT(30)                                             /*!< STCM reset */
#define RCU_AHBRST_MTCRST                 BIT(31)                                             /*!< MTC reset */
                                                                                         
/* RCU_APB2RST */                                                                        
#define RCU_APB2RST_SYSCFGRST             BIT(0)                                               /*!< System configuration reset */
#define RCU_APB2RST_LIN0RST               BIT(1)                                               /*!< LIN0 reset */
#define RCU_APB2RST_LIN1RST               BIT(2)                                               /*!< LIN1 reset */
#define RCU_APB2RST_LIN2RST               BIT(3)                                               /*!< LIN2 reset */
#define RCU_APB2RST_LIN3RST               BIT(4)                                               /*!< LIN3 reset */
#define RCU_APB2RST_LIN4RST               BIT(5)                                               /*!< LIN4 reset */
#define RCU_APB2RST_LIN5RST               BIT(6)                                               /*!< LIN5 reset */
#define RCU_APB2RST_ADC0RST               BIT(8)                                               /*!< ADC0 reset */
#define RCU_APB2RST_ADC1RST               BIT(9)                                               /*!< ADC1 reset */
#define RCU_APB2RST_TIMER0RST             BIT(10)                                              /*!< TIMER0 reset */
#define RCU_APB2RST_SPI0RST               BIT(11)                                              /*!< SPI0 reset */
#define RCU_APB2RST_TIMER7RST             BIT(12)                                              /*!< TIMER7 reset */
#define RCU_APB2RST_SPI4RST               BIT(16)                                              /*!< SPI4 reset */
#define RCU_APB2RST_SPI5RST               BIT(17)                                              /*!< SPI5 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB2RST_ADC2RST               BIT(18)                                              /*!< ADC2 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB2RST_TIMER19RST            BIT(19)                                              /*!< TIMER19 reset */
#define RCU_APB2RST_TIMER1RST             BIT(20)                                              /*!< TIMER1 reset */
#define RCU_APB2RST_TIMER5RST             BIT(21)                                              /*!< TIMER5 reset */
#define RCU_APB2RST_TIMER62RST            BIT(22)                                              /*!< TIMER62 reset */
#define RCU_APB2RST_CMP1RST               BIT(23)                                              /*!< CMP1 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB2RST_USART5RST             BIT(24)                                              /*!< USART5 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB2RST_SPI1RST               BIT(25)                                              /*!< SPI1 reset */
#define RCU_APB2RST_CMP0RST               BIT(26)                                              /*!< CMP0 reset */
                                                                                       
/* RCU_APB2RST_ADD */                                                                  
#define RCU_APB2RST_ADD_CAN0RST           BIT(8)                                               /*!< CAN0 cluster reset */
#define RCU_APB2RST_ADD_CAN1RST           BIT(9)                                               /*!< CAN1 cluster reset */
#define RCU_APB2RST_ADD_CAN2RST           BIT(10)                                              /*!< CAN2 cluster reset */
                                                                                       
/* RCU_APB1RST */                                                                      
#define RCU_APB1RST_TIMER20RST            BIT(0)                                               /*!< TIMER20 reset */
#define RCU_APB1RST_TIMER2RST             BIT(1)                                               /*!< TIMER2 reset */
#define RCU_APB1RST_TIMER60RST            BIT(2)                                               /*!< TIMER60 reset */
#define RCU_APB1RST_TIMER6RST             BIT(3)                                               /*!< TIMER6 reset */
#define RCU_APB1RST_WWDGT0RST             BIT(4)                                               /*!< WWDGT0 reset */
#define RCU_APB1RST_FWDGT0RST             BIT(5)                                               /*!< FWDGT0 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB1RST_SPI6RST               BIT(6)                                               /*!< SPI6 reset */
#define RCU_APB1RST_SPI7RST               BIT(7)                                               /*!< SPI7 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB1RST_I2C0RST               BIT(10)                                              /*!< I2C0 reset */
#define RCU_APB1RST_I2C1RST               BIT(11)                                              /*!< I2C1 reset */
#define RCU_APB1RST_BKPRST                BIT(12)                                              /*!< BKP reset */
#define RCU_APB1RST_DAC0RST               BIT(14)                                              /*!< DAC0 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB1RST_ENETRST               BIT(15)                                              /*!< ENET reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB1RST_TIMER61RST            BIT(16)                                              /*!< TIMER61 reset */
#define RCU_APB1RST_TIMER63RST            BIT(17)                                              /*!< TIMER63 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB1RST_SENTRST               BIT(18)                                              /*!< SENT reset */
#define RCU_APB1RST_LIN6RST               BIT(19)                                              /*!< LIN6 reset */
#define RCU_APB1RST_LIN7RST               BIT(20)                                              /*!< LIN7 reset */
#define RCU_APB1RST_LIN8RST               BIT(21)                                              /*!< LIN8 reset */
#define RCU_APB1RST_LIN9RST               BIT(22)                                              /*!< LIN9 reset */
#define RCU_APB1RST_LIN10RST              BIT(23)                                              /*!< LIN10 reset */
#define RCU_APB1RST_LIN11RST              BIT(24)                                              /*!< LIN11 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB1RST_DAC1RST               BIT(25)                                              /*!< DAC1 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB1RST_WWDGT1RST             BIT(26)                                              /*!< WWDGT1 reset */
#define RCU_APB1RST_FWDGT1RST             BIT(27)                                              /*!< FWDGT1 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB1RST_SPI3RST               BIT(28)                                              /*!< SPI3 reset */
#define RCU_APB1RST_SPI4RST               BIT(29)                                              /*!< SPI4 reset */

/* RCU_AHBEN */
#define RCU_AHBEN_PAEN                  BIT(0)                               /*!< GPIOA clock enable */
#define RCU_AHBEN_PBEN                  BIT(1)                               /*!< GPIOB clock enable */
#define RCU_AHBEN_PCEN                  BIT(2)                               /*!< GPIOC clock enable */
#define RCU_AHBEN_PDEN                  BIT(3)                               /*!< GPIOD clock enable */
#define RCU_AHBEN_PEEN                  BIT(4)                               /*!< GPIOE clock enable */
#define RCU_AHBEN_PFEN                  BIT(5)                               /*!< GPIOF clock enable */
#define RCU_AHBEN_PGEN                  BIT(6)                               /*!< GPIOG clock enable */
#define RCU_AHBEN_PHEN                  BIT(7)                               /*!< GPIOH clock enable */
#define RCU_AHBEN_PIEN                  BIT(8)                               /*!< GPIOI clock enable */
#define RCU_AHBEN_PJEN                  BIT(9)                               /*!< GPIOJ clock enable */
#define RCU_AHBEN_PKEN                  BIT(10)                              /*!< GPIOK clock enable */
#define RCU_AHBEN_PLEN                  BIT(11)                              /*!< GPIOL clock enable */
#define RCU_AHBEN_PMEN                  BIT(12)                              /*!< GPIOM clock enable */
#define RCU_AHBEN_PNEN                  BIT(13)                              /*!< GPION clock enable */
#define RCU_AHBEN_DMA0EN                BIT(14)                              /*!< DMA0 clock enable */
#define RCU_AHBEN_DMA1EN                BIT(15)                              /*!< DMA1 clock enable */
#define RCU_AHBEN_DMAMUXEN              BIT(16)                              /*!< DMAMUX clock enable */
#define RCU_AHBEN_QSPIEN                BIT(18)                              /*!< QSPI clock enable */
#define RCU_AHBEN_CRCEN                 BIT(20)                              /*!< CRC clock enable */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_AHBEN_MFCOMEN               BIT(21)                              /*!< MFCOM clock enable */
#define RCU_AHBEN_MCMUAEN               BIT(22)                              /*!< MCMUA clock enable */
#define RCU_AHBEN_MCMUBEN               BIT(23)                              /*!< MCMUB clock enable */
#define RCU_AHBEN_HWSEMEN               BIT(24)                              /*!< HWSEM clock enable */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_AHBEN_HSMIFEN               BIT(25)                              /*!< HSMIF clock enable */
#define RCU_AHBEN_FMUEN                 BIT(27)                              /*!< FMU clock enable */
#define RCU_AHBEN_IRMEN                 BIT(28)                              /*!< IRM clock enable */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_AHBEN_IOCEN                 BIT(29)                              /*!< IOC clock enable */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_AHBEN_STCMEN                BIT(30)                              /*!< STCM clock enable */
#define RCU_AHBEN_MTCEN                 BIT(31)                              /*!< MTC clock enable */

/* RCU_APB2EN */
#define RCU_APB2EN_CFGEN                BIT(0)                                /*!< System configuration clock enable */
#define RCU_APB2EN_LINFLEXD0EN          BIT(1)                                /*!< LINFlexD0 clock enable */
#define RCU_APB2EN_LINFLEXD1EN          BIT(2)                                /*!< LINFlexD1 clock enable */
#define RCU_APB2EN_LINFLEXD2EN          BIT(3)                                /*!< LINFlexD2 clock enable */
#define RCU_APB2EN_LINFLEXD3EN          BIT(4)                                /*!< LINFlexD3 clock enable */
#define RCU_APB2EN_LINFLEXD4EN          BIT(5)                                /*!< LINFlexD4 clock enable */
#define RCU_APB2EN_LINFLEXD5EN          BIT(6)                                /*!< LINFlexD5 clock enable */
#define RCU_APB2EN_TRIGSELEN            BIT(7)                                /*!< TRIGSEL clock enable */
#define RCU_APB2EN_ADC0EN               BIT(8)                                /*!< ADC0 clock enable */
#define RCU_APB2EN_ADC1EN               BIT(9)                                /*!< ADC1 clock enable */
#define RCU_APB2EN_TIMER0EN             BIT(10)                               /*!< TIMER0 clock enable */
#define RCU_APB2EN_SPI0EN               BIT(11)                               /*!< SPI0 clock enable */
#define RCU_APB2EN_TIMER7EN             BIT(12)                               /*!< TIMER7 clock enable */
#define RCU_APB2EN_SPI4EN               BIT(16)                               /*!< SPI4 clock enable */
#define RCU_APB2EN_SPI5EN               BIT(17)                               /*!< SPI5 clock enable */
#define RCU_APB2EN_ADC2EN               BIT(18)                               /*!< ADC2 clock enable */
#define RCU_APB2EN_TIMER19EN            BIT(19)                               /*!< TIMER19 clock enable */
#define RCU_APB2EN_TIMER1EN             BIT(20)                               /*!< TIMER1 clock enable */
#define RCU_APB2EN_TIMER5EN             BIT(21)                               /*!< TIMER5 clock enable */
#define RCU_APB2EN_TIMER62EN            BIT(22)                               /*!< TIMER62 clock enable */
#define RCU_APB2EN_CMP1EN               BIT(23)                               /*!< CMP1 clock enable */
#define RCU_APB2EN_SPI1EN               BIT(25)                               /*!< SPI1 clock enable */
#define RCU_APB2EN_CMP0EN               BIT(26)                               /*!< CMP0 clock enable */

/* RCU_APB1EN */
#define RCU_APB1EN_TIMER20EN            BIT(0)                                /*!< TIMER20 clock enable */
#define RCU_APB1EN_TIMER2EN             BIT(1)                                /*!< TIMER2 clock enable */
#define RCU_APB1EN_TIMER60EN            BIT(2)                                /*!< TIMER60 clock enable */
#define RCU_APB1EN_TIMER6EN             BIT(3)                                /*!< TIMER6 clock enable */
#define RCU_APB1EN_WWDGT0EN             BIT(4)                                /*!< WWDGT0 clock enable */
#define RCU_APB1EN_FWDGT0EN             BIT(5)                                /*!< FWDGT0 clock enable */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB1EN_SPI6EN               BIT(6)                                /*!< SPI6 clock enable */
#define RCU_APB1EN_SPI7EN               BIT(7)                                /*!< SPI7 clock enable */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB1EN_I2C0EN               BIT(10)                               /*!< I2C0 clock enable */
#define RCU_APB1EN_I2C1EN               BIT(11)                               /*!< I2C1 clock enable */
#define RCU_APB1EN_BKPEN                BIT(12)                               /*!< BKP clock enable */
#define RCU_APB1EN_PMUEN                BIT(13)                               /*!< PMU clock enable */
#define RCU_APB1EN_DAC0EN               BIT(14)                               /*!< DAC0 clock enable */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB1EN_ENETEN               BIT(15)                               /*!< ENET clock enable */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB1EN_TIMER61EN            BIT(16)                               /*!< TIMER61 clock enable */
#define RCU_APB1EN_TIMER63EN            BIT(17)                               /*!< TIMER63 clock enable */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB1EN_SENTEN               BIT(18)                               /*!< SENT clock enable */
#define RCU_APB1EN_LIN6EN               BIT(19)                               /*!< LIN6 clock enable */
#define RCU_APB1EN_LIN7EN               BIT(20)                               /*!< LIN7 clock enable */
#define RCU_APB1EN_LIN8EN               BIT(21)                               /*!< LIN8 clock enable */
#define RCU_APB1EN_LIN9EN               BIT(22)                               /*!< LIN9 clock enable */
#define RCU_APB1EN_LIN10EN              BIT(23)                               /*!< LIN10 clock enable */
#define RCU_APB1EN_LIN11EN              BIT(24)                               /*!< LIN11 clock enable */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB1EN_DAC1EN               BIT(25)                               /*!< DAC1 clock enable */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_APB1EN_WWDGT1EN             BIT(26)                               /*!< WWDGT1 clock enable */
#define RCU_APB1EN_FWDGT1EN             BIT(27)                               /*!< FWDGT1 clock enable */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_APB1EN_SPI2EN               BIT(28)                               /*!< SPI2 clock enable */
#define RCU_APB1EN_SPI3EN               BIT(29)                               /*!< SPI3 clock enable */
#define RCU_APB1EN_CLTCFGEN             BIT(30)                               /*!< CLTCFG clock enable */

/* RCU_BDCTL */
#define RCU_BDCTL_LXTALEN               BIT(0)                                /*!< LXTAL enable */
#define RCU_BDCTL_LXTALSTB              BIT(1)                                /*!< low speed crystal oscillator stabilization flag */
#define RCU_BDCTL_LXTALBPS              BIT(2)                                /*!< LXTAL bypass mode enable */
#define RCU_BDCTL_LXTALDRI              BITS(3,4)                             /*!< LXTAL drive capability */
#define RCU_BDCTL_RTCSRC                BITS(8,9)                             /*!< RTC clock source selection */
#define RCU_BDCTL_RTCEN                 BIT(15)                               /*!< RTC clock enable */

/* RCU_APB2EN_ADD */
#define RCU_APB2EN_ADD_DTM_CAN0EN           BIT(0)                                /*!< DTM_CAN0 clock enable */
#define RCU_APB2EN_ADD_DTM_CAN1EN           BIT(1)                                /*!< DTM_CAN1 clock enable */
#define RCU_APB2EN_ADD_DTM_CAN2EN           BIT(2)                                /*!< DTM_CAN2 clock enable */
#define RCU_APB2EN_ADD_DTM_CAN3EN           BIT(3)                                /*!< DTM_CAN3 clock enable */
#define RCU_APB2EN_ADD_DTM_CAN4EN           BIT(4)                                /*!< DTM_CAN4 clock enable */
#define RCU_APB2EN_ADD_DTM_CAN5EN           BIT(5)                                /*!< DTM_CAN5 clock enable */
#define RCU_APB2EN_ADD_DTM_CAN6EN           BIT(6)                                /*!< DTM_CAN6 clock enable */
#define RCU_APB2EN_ADD_DTM_CAN7EN           BIT(7)                                /*!< DTM_CAN7 clock enable */

/* RCU_AHBEN_ADD */
#define RCU_AHBEN_ADD_CM7_0_EN           BIT(0)                               /*!< CPU CM7_0 clock enable */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_AHBEN_ADD_CM7_1_EN           BIT(1)                               /*!< CPU CM7_1 clock enable */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* RCU_CFG1 */
#define RCU_CFG1_PREDV                  BITS(0,2)                             /*!< CK_HXTAL or IRC48M divider previous PLL */
#define RCU_CFG1_PLLDIVP                BITS(3,8)                             /*!< PLL VCO clock divide */
#define RCU_CFG1_PLLDIVQ                BITS(9,14)                            /*!< PLL VCO clock divide */
#define RCU_CFG1_FWDGT0SEL              BIT(15)                               /*!< FWDGTSEL0 clock select */
#define RCU_CFG1_CKOUT0SEL              BITS(16,19)                           /*!< CK_OUT0 clock source selection */
#define RCU_CFG1_CKOUT0DIV              BITS(20,22)                           /*!< The CK_OUT0 divider which the CK_OUT2 frequency can be reduced, */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_CFG1_ATESEL                 BITS(24,25)                           /*!< ATE clock of STCM */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_CFG1_AITSEL                 BITS(26,27)                           /*!< AIT clock of STCM */
#define RCU_CFG1_IRC48MFR               BIT(30)                               /*!< IRC48M fail response */

/* RCU_CFG2 */
#define RCU_CFG2_USART0SEL              BITS(0,1)                             /*!< USART0 clock source selection */
#define RCU_CFG2_USART1SEL              BITS(2,3)                             /*!< USART1 clock source selection */
#define RCU_CFG2_USART2SEL              BITS(4,5)                             /*!< USART2 clock source selection */
#define RCU_CFG2_USART3SEL              BITS(6,7)                             /*!< USART3 clock source selection */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_CFG2_USART4SEL              BITS(8,9)                             /*!< USART4 clock source selection */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_CFG2_DTM_CAN0SEL            BITS(10,11)                           /*!< DTM_CAN0 clock source selection */
#define RCU_CFG2_DTM_CAN1SEL            BITS(12,13)                           /*!< DTM_CAN1 clock source selection */
#define RCU_CFG2_DTM_CAN2SEL            BITS(14,15)                           /*!< DTM_CAN2 clock source selection */
#define RCU_CFG2_DTM_CAN3SEL            BITS(16,17)                           /*!< DTM_CAN3 clock source selection */
#define RCU_CFG2_DTM_CAN4SEL            BITS(18,19)                           /*!< DTM_CAN4 clock source selection */
#define RCU_CFG2_DTM_CAN5SEL            BITS(20,21)                           /*!< DTM_CAN5 clock source selection */
#define RCU_CFG2_DTM_CAN6SEL            BITS(22,23)                           /*!< DTM_CAN6 clock source selection */
#define RCU_CFG2_ADCCLK_MUX             BIT(24)                               /*!< ADC clock source selection */
#define RCU_CFG2_ADCSEL                 BIT(25)                               /*!< ADC clock source selection */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_CFG2_FWDGT1SEL              BIT(26)                               /*!< FWDGT1SEL clock select */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_CFG2_ADCPSC                 BITS(27,31)                           /*!< ADC clock prescaler selection */

/* RCU_CFG3 */
#define RCU_CFG3_SPISEL                 BITS(0,1)                             /*!< SPI clock source selection */
#define RCU_CFG3_DTM_CAN7SEL            BITS(2,3)                             /*!< DTM_CAN7 clock source selection */
#define RCU_CFG3_SPIDIV                 BITS(4,9)                             /*!< SPI clock divider */
#define RCU_CFG3_LINFLEXDDIV            BITS(10,13)                           /*!< LINFlexD clock divider */
#define RCU_CFG3_LINFLEXDSEL            BITS(14,15)                           /*!< LINFlexD clock source selection */
#define RCU_CFG3_WWDGT0SEL              BITS(16,18)                           /*!< WWDGT0SEL clock select */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_CFG3_WWDGT1SEL              BITS(19,21)                           /*!< WWDGT1SEL clock select */
#define RCU_CFG3_ENETTSSEL              BITS(22,24)                           /*!< ENETTS CLK divider */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_CFG3_QSPISEL                BITS(25,26)                           /*!< QSPI clock source selection */
#define RCU_CFG3_TRACEDIV               BITS(27,29)                           /*!< TRACE clock divider */
#define RCU_CFG3_TRACESEL               BITS(30,31)                           /*!< TRACE clock source selection */

/* RCU_PLLLOL */
#define RCU_PLLLOL_PLLLOLCTL            BITS(0,1)                             /*!< Adjust the loss of lock accuracy */
#define RCU_PLLLOL_PLLLOLF              BIT(2)                                /*!< Loss of lock detector flag */
#define RCU_PLLLOL_PLLLOLFC             BIT(3)                                /*!< Clear PLLLOLF flag */

/* RCU_CKDCTL */
#define RCU_CKDCTL_CKD0_FDEN            BIT(0)                                /*!< CKD0 frequency detect Enable */
#define RCU_CKDCTL_CKD0_FDERR           BIT(1)                                /*!< CKD0 frequency detect error */
#define RCU_CKDCTL_CKD0_FDEIE           BIT(2)                                /*!< CKD0 frequency detect error interrupt enable */
#define RCU_CKDCTL_CKD1_FDEN            BIT(8)                                /*!< CKD1 frequency detect Enable */
#define RCU_CKDCTL_CKD1_FDERR           BIT(9)                                /*!< CKD1 frequency detect error */
#define RCU_CKDCTL_CKD1_FDEIE           BIT(10)                               /*!< CKD1 frequency detect error interrupt enable */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_CKDCTL_CKD2_FDEN            BIT(16)                               /*!< CKD2 frequency detect Enable */
#define RCU_CKDCTL_CKD2_FDERR           BIT(17)                               /*!< CKD2 frequency detect error */
#define RCU_CKDCTL_CKD2_FDEIE           BIT(18)                               /*!< CKD2 frequency detect error interrupt enable */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* RCU_CKFMCTL */
#define RCU_CKFMCTL_FMEN                BIT(0)                                /*!< Frequency monitor Enable */
#define RCU_CKFMCTL_FLMIN               BIT(1)                                /*!< Frequency lower than low frequency reference threshold event status */
#define RCU_CKFMCTL_FHMAX               BIT(2)                                /*!< Frequency higher than high frequency reference threshold event status */
#define RCU_CKFMCTL_FLMINIE             BIT(3)                                /*!< Frequency Lower than Low Frequency Reference Threshold synchronous interrupt Enable*/
#define RCU_CKFMCTL_FHMAXIE             BIT(4)                                /*!< Frequency Higher than High Frequency Reference Threshold synchronous interrupt Enable */
#define RCU_CKFMCTL_FLMINRE             BIT(5)                                /*!< Frequency Lower than Low Frequency Reference Threshold reset Enable*/
#define RCU_CKFMCTL_FHMAXRE             BIT(6)                                /*!< Frequency Higher than High Frequency Reference Threshold reset Enable */

/* RCU_CKFMRCCFG */
#define RCU_CKFMRCCFG_REF_CNT           BITS(0,15)                            /*!< Reference clock count */

/* RCU_CKFMHTHCFG */                                                   
#define RCU_CKFMHTHCFG_HFMAX            BITS(0,23)                            /*!< High frequency reference threshold */

/* RCU_CKFMLTHCFG */                                                   
#define RCU_CKFMLTHCFG_LFMIN            BITS(0,23)                            /*!< Low frequency reference threshold */

/* RCU_BUSIM_TMR */
#define RCU_BUSIM_TMR_TMR_EN0            BIT(0)                               /*!< TMR error 0 output to fmu enable */
#define RCU_BUSIM_TMR_TMR_EN1            BIT(1)                               /*!< TMR error 1 output to fmu enable */
#define RCU_BUSIM_TMR_TMR_EN2            BIT(2)                               /*!< TMR error 2 output to fmu enable */
#define RCU_BUSIM_TMR_TMR_EN3            BIT(3)                               /*!< TMR error 3 output to fmu enable */
#define RCU_BUSIM_TMR_TMR_ST0            BIT(4)                               /*!< System clock switching TMR error status */
#define RCU_BUSIM_TMR_TMR_ST1            BIT(5)                               /*!< Clock enable TMR error status */
#define RCU_BUSIM_TMR_TMR_ST2            BIT(6)                               /*!< Clock monitor enable register TMR error status */
#define RCU_BUSIM_TMR_TMR_ST3            BIT(7)                               /*!< The TMR error occurs in any bit of TRIM register */

/* RCU_PLLFRA */
#define RCU_PLLFRA_PLLFRACN             BITS(0,13)                            /*!< Fractional part of the multiplication factor for PLL VCO */
#define RCU_PLLFRA_PLLFRAEN             BIT(15)                               /*!< PLL fractional latch enable */

/* RCU_PLLSSCTL */
#define RCU_PLLSSCTL_MODCNT             BITS(0,10)                            /*!< these bits configure PLL spread spectrum modulation 
                                                                                    profile amplitude and frequency. the following criteria 
                                                                                    must be met: MODSTEP*MODCNT <=2^14 */
#define RCU_PLLSSCTL_MODSTEP            BITS(13,22)                           /*!< these bits configure PLL spread spectrum modulation 
                                                                                   profile amplitude and frequency. the following criteria 
                                                                                   must be met: MODSTEP*MODCNT <=2^14 */
#define RCU_PLLSSCTL_SS_TYPE            BIT(30)                               /*!< PLL spread spectrum modulation type select */
#define RCU_PLLSSCTL_SSCGBYP            BIT(31)                               /*!< PLL spread spectrum modulation bypass enable */

/* RCU_SYSRSTSTAT */
#define RCU_SYSRSTSTAT_PORF             BIT(0)                                 /*!< Power-on reset flag */
#define RCU_SYSRSTSTAT_FMU_REA_FAIL     BIT(3)                                 /*!< 'System' reset flag FMU_REA_FAIL */
#define RCU_SYSRSTSTAT_STCM_REC_FAIL    BIT(4)                                 /*!< 'System' reset flag STCM_REC_FAIL */
#define RCU_SYSRSTSTAT_RCTL_SUBSRUF     BIT(6)                                 /*!< 'System' reset flag RCTL_SUBSRUF */
#define RCU_SYSRSTSTAT_LOHRSTF          BIT(8)                                 /*!< Lost of HXTAL error reset flag */
#define RCU_SYSRSTSTAT_LOPRSTF          BIT(9)                                 /*!< Lost of PLL error reset flag */
#define RCU_SYSRSTSTAT_CORE_CK_FAIL     BIT(10)                                /*!< 'System' reset flag CORE_CK_FAIL */
#define RCU_SYSRSTSTAT_SYS_CK_FAIL      BIT(12)                                /*!< 'System' reset flag SYS_CK_FAIL */
#define RCU_SYSRSTSTAT_HSM_SYS_RSTF     BIT(18)                                /*!< 'System' reset flag HSM_SYS_RSTF */
#define RCU_SYSRSTSTAT_SW_SYS_RSTF      BIT(29)                                /*!< 'System' reset flag SW_SYS_RSTF */
#define RCU_SYSRSTSTAT_DBG_SYS_RSTF     BIT(30)                                /*!< 'System' reset flag DBG_SYS_RSTF */

/* RCU_BUSCTL */
#define RCU_BUSCTL_BUSCTL               BIT(0)                                 /*!< bus access control */

/* RCU_SUBSERSTAT */
#define RCU_SUBSERSTAT_EXRF             BIT(0)                                 /*!< External reset flag EXRF */
#define RCU_SUBSERSTAT_OBSTDBY_RSTF     BIT(2)                                 /*!< Subsystem reset flag OBSTDBY_RSTF */
#define RCU_SUBSERSTAT_FMU_RSTF         BIT(3)                                 /*!< Subsystem reset flag FMU_RSTF */
#define RCU_SUBSERSTAT_ST_FINISH        BIT(4)                                 /*!< Subsystem reset flag ST_FINISH */
#define RCU_SUBSERSTAT_FWDGT0_RSTF      BIT(6)                                 /*!< Subsystem reset flag FWDGT0_RSTF */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_SUBSERSTAT_FWDGT1_RSTF      BIT(7)                                 /*!< Subsystem reset flag FWDGT1_RSTF */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_SUBSERSTAT_SWRSTF           BIT(9)                                 /*!< Software reset flag */
#define RCU_SUBSERSTAT_WWDGT0_RSTF      BIT(10)                                /*!< Subsystem reset flag WWDGT0_RSTF */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_SUBSERSTAT_WWDGT1_RSTF      BIT(11)                                /*!< Subsystem reset flag WWDGT1_RSTF */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_SUBSERSTAT_HSM_WDGT_RSTF    BIT(16)                                /*!< Subsystem reset flag HSM_WDGT_RSTF */
#define RCU_SUBSERSTAT_HSM_APP_RSTF     BIT(20)                                /*!< Subsystem reset flag HSM_APP_RSTF */
#define RCU_SUBSERSTAT_SW_SUBS_RSTF     BIT(29)                                /*!< Subsystem reset flag SW_SUBS_RSTF */
#define RCU_SUBSERSTAT_DBG_RSTF         BIT(30)                                /*!< Debug reset flag DBG_RSTF */
#define RCU_SUBSERSTAT_OBL_RSTF         BIT(31)                                /*!< Option byte loader reset flag */
/* RCU_SUBSRCTL */
#define RCU_SUBSRCTL_FMU_RST_RD        BIT(3)                                  /*!< FMU_RD disable control */
#define RCU_SUBSRCTL_FWDGT0_RST_RD     BIT(6)                                  /*!< FWDGT0_RST_RD disable control */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_SUBSRCTL_FWDGT1_RST_RD     BIT(7)                                  /*!< FWDGT1_RST disable control */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_SUBSRCTL_WWDGT0_RST_RD     BIT(10)                                 /*!< WWDGT0_RST disable control */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_SUBSRCTL_WWDGT1_RST_RD     BIT(11)                                 /*!< WWDGT1_RST disable control */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_SUBSRCTL_DBG_RST_RD        BIT(30)                                 /*!< DBG_RST disable control */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_SUBSRCTL_OBL_RST_RD        BIT(31)                                 /*!< OBL_RST disable control */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* RCU_SUBSRPACTL */
#define RCU_SUBSRPACTL_ST_FINISH_RPAEN   BIT(4)                                /*!< Reset pin assert enable for subsystem reset ST_FINISH */


/* RCU_SUBSRMUCNT */
#define RCU_SUBSRMUCNT_SUBSRMUCNT        BITS(0,3)                             /*!< Subsystem reset mode upgrade counter */

/* RCU_SUBSRMUTH */
#define RCU_SUBSRMUTH_SUBSRMUTH          BITS(0,3)                             /*!< Subsystem reset mode upgrade threshold */

/* RCU_SYSMRUTH */
#define RCU_SYSMRUTH_SYSMRUTH            BITS(0,3)                             /*!< System reset mode upgrade threshold */

/* RCU_ERPACFG */
#define RCU_ERPACFG_ERPAETEN             BIT(0)                                /*!< External reset pin assert enable */

/* RCU_RDSMSTAT */
#define RCU_RDSMSTAT_SYSRESF          BIT(0)                                   /*!< System reset event occurred flag in standby mode */
#define RCU_RDSMSTAT_SUBSRESF         BIT(1)                                   /*!< Subsystem reset event occurred flag in standby mode */

/* RCU_SUBSRTO */
#define RCU_SUBSRTO_SUBSRTOEN         BIT(0)                                   /*!< Subsystem reset timer enable */
#define RCU_SUBSRTO_SUBSRTO           BITS(1,31)                               /*!< Subsystem reset timer value */

/* RCU_LPDBGSTAT */
#define RCU_LPDBGSTAT_LPDBGF          BIT(0)                                   /*!< Low-Power debug flag */

/* RCU_PORSTAT0 */
#define RCU_PORSTAT0_PORWDG_OVF0      BIT(0)                             /*!< PORWDG_OVF0 captures the status of subsystem reset sequence process SUBSRST0 when PORWDG overflows */
#define RCU_PORSTAT0_PORWDG_OVF1      BIT(1)                             /*!< PORWDG_OVF1 captures the status of subsystem reset sequence process SUBSRST1 when PORWDG overflows */
#define RCU_PORSTAT0_PORWDG_OVF2      BIT(2)                             /*!< PORWDG_OVF2 captures the status of subsystem reset sequence process SUBSRST2 when PORWDG overflows*/
#define RCU_PORSTAT0_PORWDG_OVF3      BIT(3)                             /*!< PORWDG_OVF3 captures the status of subsystem reset sequence process SUBSRST3 when PORWDG overflows*/
#define RCU_PORSTAT0_PORWDG_OVF4      BIT(4)                             /*!< PORWDG_OVF4 captures the status of subsystem reset sequence process SUBSRST4 when PORWDG overflows*/
#define RCU_PORSTAT0_PORWDG_OVF5      BIT(5)                             /*!< PORWDG_OVF5 captures the status of subsystem reset sequence process SUBSRST5 when PORWDG overflows*/
#define RCU_PORSTAT0_PORWDG_OVF6      BIT(6)                             /*!< PORWDG_OVF6 captures the status of subsystem reset sequence process SUBSRST6 when PORWDG overflows*/
#define RCU_PORSTAT0_PORWDG_OVF10     BIT(10)                            /*!< PORWDG_OVF10 captures the status of subsystem reset sequence process SUBSRST7 when PORWDG overflows*/
#define RCU_PORSTAT0_PORWDG_OVF11     BIT(11)                            /*!< PORWDG_OVF11 captures the status of subsystem reset sequence process SUBSRST8 when PORWDG overflows*/
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_PORSTAT0_PORWDG_OVF14     BIT(14)                            /*!< PORWDG_OVF14 captures the status of subsystem reset sequence process SUBSRST9 when PORWDG overflows*/
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_PORSTAT0_PORWDG_OVF20     BIT(20)                            /*!< PORWDG_OVF20 captures the status of subsystem reset sequence process SYSRST0 when PORWDG overflows */
#define RCU_PORSTAT0_PORWDG_OVF29     BIT(29)                            /*!< PORWDG_OVF29 captures the status of standby entry request initiated by PMU when PORWDG overflows */
#define RCU_PORSTAT0_PORWDG_OVF30     BIT(30)                            /*!< PORWDG_OVF30 captures the status of standby exit acknowledgement by PMU when POR_WDG overflows */
#define RCU_PORSTAT0_PORWDG_OVF31     BIT(31)                            /*!< PORWDG_OVF31 captures RCTL reset event (if occurred) while the device is in standby mode*/

/* RCU_PORSTAT1 */
#define RCU_PORSTAT1_PORWDG_OVF32      BIT(0)                            /*!< PORWDG_OVF32 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[0]) */
#define RCU_PORSTAT1_PORWDG_OVF33      BIT(1)                            /*!< PORWDG_OVF33 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[1]) */
#define RCU_PORSTAT1_PORWDG_OVF34      BIT(2)                            /*!< PORWDG_OVF34 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[2]) */
#define RCU_PORSTAT1_PORWDG_OVF35      BIT(3)                            /*!< PORWDG_OVF35 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[3]) */
#define RCU_PORSTAT1_PORWDG_OVF36      BIT(4)                            /*!< PORWDG_OVF36 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[4]) */
#define RCU_PORSTAT1_PORWDG_OVF37      BIT(5)                            /*!< PORWDG_OVF37 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[5]) */
#define RCU_PORSTAT1_PORWDG_OVF38      BIT(6)                            /*!< PORWDG_OVF38 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[6]) */
#define RCU_PORSTAT1_PORWDG_OVF39      BIT(7)                            /*!< PORWDG_OVF39 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[7]) */
#define RCU_PORSTAT1_PORWDG_OVF40      BIT(8)                            /*!< PORWDG_OVF40 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[8]) */
#define RCU_PORSTAT1_PORWDG_OVF41      BIT(9)                            /*!< PORWDG_OVF41 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[9]) */
#define RCU_PORSTAT1_PORWDG_OVF42      BIT(10)                           /*!< PORWDG_OVF42 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[10]) */
#define RCU_PORSTAT1_PORWDG_OVF43      BIT(11)                           /*!< PORWDG_OVF43 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[11]) */
#define RCU_PORSTAT1_PORWDG_OVF44      BIT(12)                           /*!< PORWDG_OVF44 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[12]) */
#define RCU_PORSTAT1_PORWDG_OVF45      BIT(13)                           /*!< PORWDG_OVF45 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[13]) */
#define RCU_PORSTAT1_PORWDG_OVF46      BIT(14)                           /*!< PORWDG_OVF46 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[14]) */
#define RCU_PORSTAT1_PORWDG_OVF47      BIT(15)                           /*!< PORWDG_OVF47 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[15]) */
#define RCU_PORSTAT1_PORWDG_OVF48      BIT(16)                           /*!< PORWDG_OVF48 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[16]) */
#define RCU_PORSTAT1_PORWDG_OVF49      BIT(17)                           /*!< PORWDG_OVF49 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[17]) */
#define RCU_PORSTAT1_PORWDG_OVF50      BIT(18)                           /*!< PORWDG_OVF50 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[18]) */
#define RCU_PORSTAT1_PORWDG_OVF51      BIT(19)                           /*!< PORWDG_OVF51 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[19]) */
#define RCU_PORSTAT1_PORWDG_OVF52      BIT(20)                           /*!< PORWDG_OVF52 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[20]) */
#define RCU_PORSTAT1_PORWDG_OVF53      BIT(21)                           /*!< PORWDG_OVF53 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[21]) */
#define RCU_PORSTAT1_PORWDG_OVF54      BIT(22)                           /*!< PORWDG_OVF54 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[22]) */
#define RCU_PORSTAT1_PORWDG_OVF55      BIT(23)                           /*!< PORWDG_OVF55 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[23]) */
#define RCU_PORSTAT1_PORWDG_OVF56      BIT(24)                           /*!< PORWDG_OVF56 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[24]) */
#define RCU_PORSTAT1_PORWDG_OVF57      BIT(25)                           /*!< PORWDG_OVF57 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[25]) */
#define RCU_PORSTAT1_PORWDG_OVF58      BIT(26)                           /*!< PORWDG_OVF58 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[26]) */
#define RCU_PORSTAT1_PORWDG_OVF59      BIT(27)                           /*!< PORWDG_OVF59 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[27]) */
#define RCU_PORSTAT1_PORWDG_OVF60      BIT(28)                           /*!< PORWDG_OVF60 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[28]) */
#define RCU_PORSTAT1_PORWDG_OVF61      BIT(29)                           /*!< PORWDG_OVF61 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[29]) */
#define RCU_PORSTAT1_PORWDG_OVF62      BIT(30)                           /*!< PORWDG_OVF62 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[30]) */
#define RCU_PORSTAT1_PORWDG_OVF63      BIT(31)                           /*!< PORWDG_OVF63 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[31]) */

/* RCU_PORSTAT2 */
#define RCU_PORSTAT2_PORWDG_OVF64      BIT(0)                            /*!< PORWDG_OVF64 captures RCTL system event status register when PORWDG overflows (RCU_SYSRSTSTAT[0]) */
#define RCU_PORSTAT2_PORWDG_OVF65      BIT(1)                            /*!< PORWDG_OVF65 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[1]) */
#define RCU_PORSTAT2_PORWDG_OVF66      BIT(2)                            /*!< PORWDG_OVF66 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[2]) */
#define RCU_PORSTAT2_PORWDG_OVF67      BIT(3)                            /*!< PORWDG_OVF67 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[3]) */
#define RCU_PORSTAT2_PORWDG_OVF68      BIT(4)                            /*!< PORWDG_OVF68 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[4]) */
#define RCU_PORSTAT2_PORWDG_OVF69      BIT(5)                            /*!< PORWDG_OVF69 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[5]) */
#define RCU_PORSTAT2_PORWDG_OVF70      BIT(6)                            /*!< PORWDG_OVF70 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[6]) */
#define RCU_PORSTAT2_PORWDG_OVF71      BIT(7)                            /*!< PORWDG_OVF71 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[7]) */
#define RCU_PORSTAT2_PORWDG_OVF72      BIT(8)                            /*!< PORWDG_OVF72 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[8]) */
#define RCU_PORSTAT2_PORWDG_OVF73      BIT(9)                            /*!< PORWDG_OVF73 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[9]) */
#define RCU_PORSTAT2_PORWDG_OVF74      BIT(10)                           /*!< PORWDG_OVF74 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[10]) */
#define RCU_PORSTAT2_PORWDG_OVF75      BIT(11)                           /*!< PORWDG_OVF75 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[11]) */
#define RCU_PORSTAT2_PORWDG_OVF76      BIT(12)                           /*!< PORWDG_OVF76 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[12]) */
#define RCU_PORSTAT2_PORWDG_OVF77      BIT(13)                           /*!< PORWDG_OVF77 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[13]) */
#define RCU_PORSTAT2_PORWDG_OVF78      BIT(14)                           /*!< PORWDG_OVF78 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[14]) */
#define RCU_PORSTAT2_PORWDG_OVF79      BIT(15)                           /*!< PORWDG_OVF79 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[15]) */
#define RCU_PORSTAT2_PORWDG_OVF80      BIT(16)                           /*!< PORWDG_OVF80 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[16]) */
#define RCU_PORSTAT2_PORWDG_OVF81      BIT(17)                           /*!< PORWDG_OVF81 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[17]) */
#define RCU_PORSTAT2_PORWDG_OVF82      BIT(18)                           /*!< PORWDG_OVF82 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[18]) */
#define RCU_PORSTAT2_PORWDG_OVF83      BIT(19)                           /*!< PORWDG_OVF83 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[19]) */
#define RCU_PORSTAT2_PORWDG_OVF84      BIT(20)                           /*!< PORWDG_OVF84 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[20]) */
#define RCU_PORSTAT2_PORWDG_OVF85      BIT(21)                           /*!< PORWDG_OVF85 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[21]) */
#define RCU_PORSTAT2_PORWDG_OVF86      BIT(22)                           /*!< PORWDG_OVF86 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[22]) */
#define RCU_PORSTAT2_PORWDG_OVF87      BIT(23)                           /*!< PORWDG_OVF87 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[23]) */
#define RCU_PORSTAT2_PORWDG_OVF88      BIT(24)                           /*!< PORWDG_OVF88 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[24]) */
#define RCU_PORSTAT2_PORWDG_OVF89      BIT(25)                           /*!< PORWDG_OVF89 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[25]) */
#define RCU_PORSTAT2_PORWDG_OVF90      BIT(26)                           /*!< PORWDG_OVF90 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[26]) */
#define RCU_PORSTAT2_PORWDG_OVF91      BIT(27)                           /*!< PORWDG_OVF91 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[27]) */
#define RCU_PORSTAT2_PORWDG_OVF92      BIT(28)                           /*!< PORWDG_OVF92 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[28]) */
#define RCU_PORSTAT2_PORWDG_OVF93      BIT(29)                           /*!< PORWDG_OVF93 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[29]) */
#define RCU_PORSTAT2_PORWDG_OVF94      BIT(30)                           /*!< PORWDG_OVF94 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[30]) */
#define RCU_PORSTAT2_PORWDG_OVF95      BIT(31)                           /*!< PORWDG_OVF95 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[31]) */

/* RCU_PORSTAT3 */
#define RCU_PORSTAT3_PORWDG_OVF96      BIT(0)                            /*!< PORWDG_OVF96 captures captures PORWDG reset event if PORWDG initiates a POR sequence */

/* RCU_TMRERRSTAT */
#define RCU_TMRERRSTAT_TMR_RCU_SYSRSTSTATEN       BIT(0)                            /*!< RCU_SYSRSTSTAT TMR error output enable */
#define RCU_TMRERRSTAT_TMR_RCU_SYSRSTSTAT         BIT(1)                            /*!< RCU_SYSRSTSTAT TMR error status */
#define RCU_TMRERRSTAT_TMR_RCU_SUBSRCTLEN         BIT(2)                            /*!< RCU_SUBSRCTL TMR error output enable */
#define RCU_TMRERRSTAT_TMR_RCU_SUBSRCTL           BIT(3)                            /*!< RCU_SUBSRCTL TMR error status */
#define RCU_TMRERRSTAT_TMR_RCU_SUBSRPACTLEN       BIT(4)                            /*!< RCU_SUBSRPACTL TMR error output enable */
#define RCU_TMRERRSTAT_TMR_RCU_SUBSRPACTL         BIT(5)                            /*!< RCU_SUBSRPACTL TMR error status */
#define RCU_TMRERRSTAT_TMR_RCU_SYSMRETHEN         BIT(6)                            /*!< RCU_SYSMRETH TMR error output enable */
#define RCU_TMRERRSTAT_TMR_RCU_SYSMRETH           BIT(7)                            /*!< RCU_SYSMRETH TMR error status */
#define RCU_TMRERRSTAT_TMR_RCU_ERPACFGEN          BIT(8)                            /*!< TMR_RCU_ERPACFG TMR error output enable */
#define RCU_TMRERRSTAT_TMR_RCU_ERPACFG            BIT(9)                            /*!< TMR_RCU_ERPACFG TMR error status */
#define RCU_TMRERRSTAT_TMR_AHBRSTEN               BIT(10)                           /*!< AHBRST TMR error output enable */
#define RCU_TMRERRSTAT_TMR_AHBRST                 BIT(11)                           /*!< AHBRST TMR error status */
#define RCU_TMRERRSTAT_TMR_APBRSTEN               BIT(12)                           /*!< APBRST1/2  TMR error output enable */
#define RCU_TMRERRSTAT_TMR_APBRST                 BIT(13)                           /*!< APBRST1/2  TMR error status */
#define RCU_TMRERRSTAT_TMR_PORWDG1EN              BIT(16)                           /*!< PORWDG1 TMR error output enable */
#define RCU_TMRERRSTAT_TMR_PORWDG1                BIT(17)                           /*!< PORWDG1 TMR error status */
#define RCU_TMRERRSTAT_TMR_PORWDG2EN              BIT(18)                           /*!< PORWDG2 TMR error output enable */
#define RCU_TMRERRSTAT_TMR_PORWDG2                BIT(19)                           /*!< PORWDG2 TMR error status */
#define RCU_TMRERRSTAT_TMR_PORWDG3EN              BIT(20)                           /*!< PORWDG3 TMR error output enable */
#define RCU_TMRERRSTAT_TMR_PORWDG3                BIT(21)                           /*!< PORWDG3 TMR error status */
#define RCU_TMRERRSTAT_TMR_PORWDG4EN              BIT(22)                           /*!< PORWDG4 TMR error output enable */
#define RCU_TMRERRSTAT_TMR_PORWDG4                BIT(23)                           /*!< PORWDG4 TMR error status */

/* RCU_SYSRSTUCNT */
#define RCU_SYSRSTUCNT_SYSRTOEN                   BITS(0,3)                         /*!< System reset upgrade counter */

/* RCU_SUBSRSTCNT */
#define RCU_SUBSRSTCNT_SUBSRSTCNT                 BITS(0,3)                         /*!< Subsystem reset counter */

/* RCU_SYSRSTCNT */
#define RCU_SYSRSTCNT_SYSRSTCNT                   BITS(0,3)                         /*!< System reset counter */

/* RCU_SUBSRSTAD */
#define RCU_SUBSRSTAD_SUBSRST_ALL_DIS             BIT(0)                            /*!< Disable all subsystem reset */

/* CKFMx select */
#define CKFM0                                     0x0U                            /*!< CKFM0 */
#define CKFM1                                     0x1U                            /*!< CKFM1 */
#define CKFM2                                     0x2U                            /*!< CKFM2 */
#define CKFM3                                     0x3U                            /*!< CKFM3 */
#define CKFM4                                     0x4U                            /*!< CKFM4 */

/* CKDX select */
typedef enum {
    CKD0 = 0x0U,                                                                   /*!< CKD 0 */
    CKD1,                                                                          /*!< CKD 1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    CKD2,                                                                          /*!< CKD 2 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
} ckd_enum;


/* constants definitions */
/* define the peripheral clock enable bit position and its register index offset */
#define RCU_REGIDX_BIT(regidx, bitpos)      (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define RCU_CCTL_REG_VAL(periph)            (REG32(CCTL + ((uint32_t)(periph) >> 6)))
#define RCU_RCTL_REG_VAL(periph)            (REG32(RCTL + ((uint32_t)(periph) >> 6)))
#define RCU_BIT_POS(val)                    ((uint32_t)(val) & 0x0000001FU)

/* register offset */
/* peripherals enable */
#define AHBEN_REG_OFFSET                0x00000014U                          /*!< AHB enable register offset */
#define APB1EN_REG_OFFSET               0x0000001CU                          /*!< APB1 enable register offset */
#define APB2EN_REG_OFFSET               0x00000018U                          /*!< APB2 enable register offset */
#define APB2EN_ADD_REG_OFFSET           0x00000024U                          /*!< APB2 enable register offset */
#define AHBEN_ADD_REG_OFFSET            0x00000028U                          /*!< AHB enable register offset */

/* peripherals reset */
#define AHBRST_REG_OFFSET               0x00000030U                          /*!< AHB reset register offset */
#define APB1RST_REG_OFFSET              0x00000034U                          /*!< APB1 reset register offset */
#define APB2RST_REG_OFFSET              0x00000038U                          /*!< APB2 reset register offset */
#define APB2RST_ADD_REG_OFFSET          0x0000003CU                          /*!< APB2 ADD reset register offset */

/* clock control */
#define CTL_REG_OFFSET                  0x00000000U                          /*!< control register offset */
#define BDCTL_REG_OFFSET                0x00000020U                          /*!< backup domain control register offset */

/* clock stabilization and stuck interrupt */
#define INT_REG_OFFSET                  0x00000008U                          /*!< clock interrupt register offset */

/* configuration register */
#define CFG0_REG_OFFSET                 0x00000004U                          /*!< clock configuration register 0 offset */
#define CFG1_REG_OFFSET                 0x0000002CU                          /*!< clock configuration register 1 offset */
#define CFG2_REG_OFFSET                 0x00000030U                          /*!< clock configuration register 2 offset */
#define CFG3_REG_OFFSET                 0x00000034U                          /*!< clock configuration register 3 offset */

/* POR watchdog overflows status register */
#define PORSTAT0_REG_OFFSET             0x00000040U                          /*!< POR watchdog overflows status register 0 offset */
#define PORSTAT1_REG_OFFSET             0x00000044U                          /*!< POR watchdog overflows status register 1 offset */
#define PORSTAT2_REG_OFFSET             0x00000048U                          /*!< POR watchdog overflows status register 2 offset */
#define PORSTAT3_REG_OFFSET             0x0000004CU                          /*!< POR watchdog overflows status register 3 offset */

/* peripheral clock enable */
typedef enum {
    /* AHB peripherals */
    RCU_GPIOA     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 0U),                     /*!< GPIOA clock */
    RCU_GPIOB     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 1U),                     /*!< GPIOB clock */
    RCU_GPIOC     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 2U),                     /*!< GPIOC clock */
    RCU_GPIOD     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 3U),                     /*!< GPIOD clock */
    RCU_GPIOE     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 4U),                     /*!< GPIOE clock */
    RCU_GPIOF     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 5U),                     /*!< GPIOF clock */
    RCU_GPIOG     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 6U),                     /*!< GPIOA clock */
    RCU_GPIOH     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 7U),                     /*!< GPIOB clock */
    RCU_GPIOI     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 8U),                     /*!< GPIOC clock */
    RCU_GPIOJ     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 9U),                     /*!< GPIOD clock */
    RCU_GPIOK     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 10U),                    /*!< GPIOE clock */
    RCU_GPIOL     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 11U),                    /*!< GPIOF clock */
    RCU_GPIOM     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 12U),                    /*!< GPIOE clock */
    RCU_GPION     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 13U),                    /*!< GPIOF clock */
    RCU_DMA0      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 14U),                    /*!< DMA0 clock */
    RCU_DMA1      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 15U),                    /*!< DMA1 clock */
    RCU_DMAMUX    = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 16U),                    /*!< DMAMUX clock */
    RCU_QSPI      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 18U),                    /*!< QSPI clock */
    RCU_CRC       = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 20U),                    /*!< CRC clock */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_MFCOM     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 21U),                    /*!< MFCOM clock */
    RCU_MCMUA     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 22U),                    /*!< MCMUA clock */
    RCU_MCMUB     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 23U),                    /*!< MCMUB clock */
    RCU_HWSEM     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 24U),                    /*!< HWSEM clock */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_HSMIF     = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 25U),                    /*!< HSMIF clock */
    RCU_FMU       = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 27U),                    /*!< FMU clock */
    RCU_IRM       = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 28U),                    /*!< IRM clock */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_IOC       = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 29U),                    /*!< IOC clock */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_STCM      = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 30U),                    /*!< STCM clock */
    RCU_MTC       = RCU_REGIDX_BIT(AHBEN_REG_OFFSET, 31U),                    /*!< MTC clock */
    /* APB2 peripherals */
    RCU_SYSCFG    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 0U),                    /*!< SYSCFG clock */
    RCU_LINFLEXD0 = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 1U),                    /*!< LINFlexD0 clock */
    RCU_LINFLEXD1 = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 2U),                    /*!< LINFlexD1 clock */
    RCU_LINFLEXD2 = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 3U),                    /*!< LINFlexD2 clock */
    RCU_LINFLEXD3 = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 4U),                    /*!< LINFlexD3 clock */
    RCU_LINFLEXD4 = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 5U),                    /*!< LINFlexD4 clock */
    RCU_LINFLEXD5 = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 6U),                    /*!< LINFlexD5 clock */
    RCU_TRIGSEL   = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 7U),                    /*!< TRIGSEL clock */
    RCU_ADC0      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 8U),                    /*!< ADC0 clock */
    RCU_ADC1      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 9U),                    /*!< ADC1 clock */
    RCU_TIMER0    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 10U),                   /*!< TIMER0 clock */
    RCU_SPI0      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 11U),                   /*!< SPI0 clock */
    RCU_TIMER7    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 12U),                   /*!< TIMER7 clock */
    RCU_SPI4      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 16U),                   /*!< SPI4 clock */
    RCU_SPI5      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 17U),                   /*!< SPI5 clock */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_ADC2      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 18U),                   /*!< ADC2 clock */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_TIMER19   = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 19U),                   /*!< TIMER19 clock */
    RCU_TIMER1    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 20U),                   /*!< TIMER1 clock */
    RCU_TIMER5    = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 21U),                   /*!< TIMER5 clock */
    RCU_TIMER62   = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 22U),                   /*!< TIMER62 clock */
    RCU_CMP1      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 23U),                   /*!< CMP1 clock */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_SPI1      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 25U),                   /*!< SPI1 clock */
    RCU_CMP0      = RCU_REGIDX_BIT(APB2EN_REG_OFFSET, 26U),                     /*!< CMP0 clock */

    /* APB1 peripherals */
    RCU_TIMER20   = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 0U),                    /*!< TIMER20 clock */
    RCU_TIMER2    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 1U),                    /*!< TIMER2 clock */
    RCU_TIMER60   = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 2U),                    /*!< TIMER60 clock */
    RCU_TIMER6    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 3U),                    /*!< TIMER6 clock */
    RCU_WWDGT0    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 4U),                    /*!< WWDGT0 clock */
    RCU_FWDGT0    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 5U),                    /*!< FWDGT0 clock */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_SPI6      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 6U),                    /*!< SPI6 clock */
    RCU_SPI7      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 7U),                    /*!< SPI7 clock */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_I2C0      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 10U),                   /*!< I2C0 clock */
    RCU_I2C1      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 11U),                   /*!< I2C1 clock */
    RCU_BKP       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 12U),                   /*!< BKP clock */
    RCU_PMU       = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 13U),                   /*!< PMU clock */
    RCU_DAC0      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 14U),                   /*!< DAC0 clock */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_ENET      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 15U),                   /*!< ENET clock */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_TIMER61   = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 16U),                   /*!< TIMER61 clock */
    RCU_TIMER63   = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 17U),                   /*!< TIMER63 clock */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_SENT      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 18U),                   /*!< SENT clock */
    RCU_LINFLEXD6      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 19U),                   /*!< RCU_LINFlexD6 clock */
    RCU_LINFLEXD7      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 20U),                   /*!< RCU_LINFlexD7 clock */
    RCU_LINFLEXD8      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 21U),                   /*!< RCU_LINFlexD8 clock */
    RCU_LINFLEXD9      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 22U),                   /*!< RCU_LINFlexD9 clock */
    RCU_LINFLEXD10     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 23U),                   /*!< RCU_LINFlexD10 clock */
    RCU_LINFLEXD11     = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 24U),                   /*!< RCU_LINFlexD11 clock */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_DAC1      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 25U),                   /*!< DAC1 clock */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_WWDGT1    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 26U),                   /*!< WWDGT1 clock */
    RCU_FWDGT1    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 27U),                   /*!< FWDGT1 clock */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_SPI2      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 28U),                   /*!< SPI2 clock */
    RCU_SPI3      = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 29U),                   /*!< SPI3 clock */
    RCU_CLTCFG    = RCU_REGIDX_BIT(APB1EN_REG_OFFSET, 30U),                   /*!< CLTCFG clock */
    RCU_RTC       = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 15U),                    /*!< RTC clock */
    /* APB2_ADD peripherals */
    RCU_DTM_CAN0      = RCU_REGIDX_BIT(APB2EN_ADD_REG_OFFSET, 0U),            /*!< DTM_CAN0 clock */
    RCU_DTM_CAN1      = RCU_REGIDX_BIT(APB2EN_ADD_REG_OFFSET, 1U),            /*!< DTM_CAN1 clock */
    RCU_DTM_CAN2      = RCU_REGIDX_BIT(APB2EN_ADD_REG_OFFSET, 2U),            /*!< DTM_CAN2 clock */
    RCU_DTM_CAN3      = RCU_REGIDX_BIT(APB2EN_ADD_REG_OFFSET, 3U),            /*!< DTM_CAN3 clock */
    RCU_DTM_CAN4      = RCU_REGIDX_BIT(APB2EN_ADD_REG_OFFSET, 4U),            /*!< DTM_CAN4 clock */
    RCU_DTM_CAN5      = RCU_REGIDX_BIT(APB2EN_ADD_REG_OFFSET, 5U),            /*!< DTM_CAN5 clock */
    RCU_DTM_CAN6      = RCU_REGIDX_BIT(APB2EN_ADD_REG_OFFSET, 6U),            /*!< DTM_CAN6 clock */
    RCU_DTM_CAN7      = RCU_REGIDX_BIT(APB2EN_ADD_REG_OFFSET, 7U),            /*!< DTM_CAN7 clock */

    /* AHB_ADD peripherals */
    RCU_CM7_0      = RCU_REGIDX_BIT(AHBEN_ADD_REG_OFFSET, 0U),                /*!< CM7_0 clock */
#if defined (GD32A72XX) || defined (GD32A74XX)
    RCU_CM7_1      = RCU_REGIDX_BIT(AHBEN_ADD_REG_OFFSET, 1U),                /*!< CM7_1 clock */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
} rcu_periph_enum;

/* peripherals reset */
typedef enum {
    /* AHB peripherals */
    RCU_GPIOARST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 0U),                 /*!< GPIOA reset */
    RCU_GPIOBRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 1U),                 /*!< GPIOB reset */
    RCU_GPIOCRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 2U),                 /*!< GPIOC reset */
    RCU_GPIODRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 3U),                 /*!< GPIOD reset */
    RCU_GPIOERST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 4U),                 /*!< GPIOE reset */
    RCU_GPIOFRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 5U),                 /*!< GPIOF reset */
    RCU_GPIOGRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 6U),                 /*!< GPIOA reset */
    RCU_GPIOHRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 7U),                 /*!< GPIOB reset */
    RCU_GPIOIRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 8U),                 /*!< GPIOC reset */
    RCU_GPIOJRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 9U),                 /*!< GPIOD reset */
    RCU_GPIOKRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 10U),                /*!< GPIOE reset */
    RCU_GPIOLRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 11U),                /*!< GPIOF reset */
    RCU_GPIOMRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 12U),                /*!< GPIOE reset */
    RCU_GPIONRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 13U),                /*!< GPIOF reset */
    RCU_DMA0RST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 14U),                /*!< DMA0 reset */
    RCU_DMA1RST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 15U),                /*!< DMA1 reset */
    RCU_DMAMUXRST    = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 16U),                /*!< DMAMUX reset */
    RCU_QSPIRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 18U),                /*!< QSPI reset */
    RCU_CRCRST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 20U),                /*!< CRC reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_MFCOMRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 21U),                /*!< MFCOM reset */
    RCU_MCMUARST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 22U),                /*!< MCMUA reset */
    RCU_MCMUBRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 23U),                /*!< MCMUB reset */
    RCU_HWSEMRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 24U),                /*!< HWSEM reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_HSMIFRST     = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 25U),                /*!< HSMIF reset */
    RCU_IRMRST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 28U),                /*!< IRM reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_IOCRST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 29U),                /*!< IOC reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_STCMRST      = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 30U),                /*!< STCM reset */
    RCU_MTCRST       = RCU_REGIDX_BIT(AHBRST_REG_OFFSET, 31U),                /*!< MTC reset */
    /* APB2 peripherals */
    RCU_SYSCFGRST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 0U),                /*!< SYSCFG reset */
    RCU_LINFLEXD0RST = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 1U),                /*!< LINFlexD0 reset */
    RCU_LINFLEXD1RST = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 2U),                /*!< LINFlexD1 reset */
    RCU_LINFLEXD2RST = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 3U),                /*!< LINFlexD2 reset */
    RCU_LINFLEXD3RST = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 4U),                /*!< LINFlexD3 reset */
    RCU_LINFLEXD4RST = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 5U),                /*!< LINFlexD4 reset */
    RCU_LINFLEXD5RST = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 6U),                /*!< LINFlexD5 reset */
    RCU_ADC0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 8U),                /*!< ADC0 reset */
    RCU_ADC1RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 9U),                /*!< ADC1 reset */
    RCU_TIMER0RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 10U),               /*!< TIMER0 reset */
    RCU_SPI0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 11U),               /*!< SPI0 reset */
    RCU_TIMER7RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 12U),               /*!< TIMER7 reset */
    RCU_SPI4RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 16U),               /*!< SPI4 reset */
    RCU_SPI5RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 17U),               /*!< SPI5 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_ADC2RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 18U),               /*!< ADC2 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_TIMER19RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 19U),               /*!< TIMER19 reset */
    RCU_TIMER1RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 20U),               /*!< TIMER1 reset */
    RCU_TIMER5RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 21U),               /*!< TIMER5 reset */
    RCU_TIMER62RST   = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 22U),               /*!< TIMER62 reset */
    RCU_CMP1RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 23U),               /*!< CMP1 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_USART5RST    = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 24U),               /*!< USART5 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_SPI1RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 25U),               /*!< SPI1 reset */
    RCU_CMP0RST      = RCU_REGIDX_BIT(APB2RST_REG_OFFSET, 26U),               /*!< CMP0 reset */

    /* APB1 peripherals */
    RCU_TIMER20RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 0U),                /*!< TIMER20 reset */
    RCU_TIMER2RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 1U),                /*!< TIMER2 reset */
    RCU_TIMER60RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 2U),                /*!< TIMER60 reset */
    RCU_TIMER6RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 3U),                /*!< TIMER6 reset */
    RCU_WWDGT0RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 4U),                /*!< WWDGT0 reset */
    RCU_FWDGT0RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 5U),                /*!< FWDGT0 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_SPI6RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 6U),                /*!< SPI6 reset */
    RCU_SPI7RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 7U),                /*!< SPI7 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_I2C0RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 10U),               /*!< I2C0 reset */
    RCU_I2C1RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 11U),               /*!< I2C1 reset */
    RCU_BKPRST       = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 12U),               /*!< BKP reset */
    RCU_DAC0RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 14U),               /*!< DAC0 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_ENETRST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 15U),               /*!< ENET reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_TIMER61RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 16U),               /*!< TIMER61 reset */
    RCU_TIMER63RST   = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 17U),               /*!< TIMER63 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_SENTRST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 18U),               /*!< SENT reset */
    RCU_LINFLEXD6RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 19U),               /*!< RCU_LINFlexD6 reset */
    RCU_LINFLEXD7RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 20U),               /*!< RCU_LINFlexD7 reset */
    RCU_LINFLEXD8RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 21U),               /*!< RCU_LINFlexD8 reset */
    RCU_LINFLEXD9RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 22U),               /*!< RCU_LINFlexD9 reset */
    RCU_LINFLEXD10RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 23U),               /*!< RCU_LINFlexD10 reset */
    RCU_LINFLEXD11RST     = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 24U),               /*!< RCU_LINFlexD11 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_DAC1RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 25U),               /*!< DAC1 reset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_WWDGT1RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 26U),               /*!< WWDGT1 reset */
    RCU_FWDGT1RST    = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 27U),               /*!< FWDGT1 reset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_SPI2RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 28U),               /*!< SPI2 reset */
    RCU_SPI3RST      = RCU_REGIDX_BIT(APB1RST_REG_OFFSET, 29U),               /*!< SPI3 reset */
    /* APB2_ADD peripherals */
    RCU_CAN0RST      = RCU_REGIDX_BIT(APB2RST_ADD_REG_OFFSET, 8U),            /*!< CAN0 cluster reset */
    RCU_CAN1RST      = RCU_REGIDX_BIT(APB2RST_ADD_REG_OFFSET, 9U),            /*!< CAN1 cluster reset */
    RCU_CAN2RST      = RCU_REGIDX_BIT(APB2RST_ADD_REG_OFFSET, 10U),           /*!< CAN2 cluster reset */
} rcu_periph_reset_enum;

/* clock stabilization interrupt enable or disable */
typedef enum {
    RCU_INT_LXTALSTB           = RCU_REGIDX_BIT(INT_REG_OFFSET, 9U),         /*!< LXTAL stabilization interrupt enable */
    RCU_INT_HXTALSTB           = RCU_REGIDX_BIT(INT_REG_OFFSET, 11U),        /*!< HXTAL stabilization interrupt enable */
    RCU_INT_PLLSTB             = RCU_REGIDX_BIT(INT_REG_OFFSET, 12U),        /*!< PLL stabilization interrupt enable */
} rcu_int_enum;

/* POR watchdog overflow flag */
typedef enum {
    /* RCU_PORSTAT0 flag */
    RCU_FLAG_OVF0     = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 0U),                   /*!< PORWDG_OVF0 captures the status of subsystem reset sequence process SUBSRST0 when PORWDG overflows */
    RCU_FLAG_OVF1     = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 1U),                   /*!< PORWDG_OVF1 captures the status of subsystem reset sequence process SUBSRST1 when PORWDG overflows */
    RCU_FLAG_OVF2     = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 2U),                   /*!< PORWDG_OVF2 captures the status of subsystem reset sequence process SUBSRST2 when PORWDG overflows*/
    RCU_FLAG_OVF3     = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 3U),                   /*!< PORWDG_OVF3 captures the status of subsystem reset sequence process SUBSRST3 when PORWDG overflows*/
    RCU_FLAG_OVF4     = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 4U),                   /*!< PORWDG_OVF4 captures the status of subsystem reset sequence process SUBSRST4 when PORWDG overflows*/
    RCU_FLAG_OVF5     = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 5U),                   /*!< PORWDG_OVF5 captures the status of subsystem reset sequence process SUBSRST5 when PORWDG overflows*/
    RCU_FLAG_OVF6     = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 6U),                   /*!< PORWDG_OVF6 captures the status of subsystem reset sequence process SUBSRST6 when PORWDG overflows*/
    RCU_FLAG_OVF10    = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 10U),                  /*!< PORWDG_OVF10 captures the status of subsystem reset sequence process SUBSRST7 when PORWDG overflows*/
    RCU_FLAG_OVF11    = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 11U),                  /*!< PORWDG_OVF11 captures the status of subsystem reset sequence process SUBSRST8 when PORWDG overflows*/
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    RCU_FLAG_OVF14    = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 14U),                  /*!< PORWDG_OVF14 captures the status of subsystem reset sequence process SUBSRST9 when PORWDG overflows*/
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    RCU_FLAG_OVF20    = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 20U),                  /*!< PORWDG_OVF20 captures the status of subsystem reset sequence process SYSRST0 when PORWDG overflows*/
    RCU_FLAG_OVF29    = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 29U),                  /*!< PORWDG_OVF29 captures the status of standby entry request initiated by PMU when PORWDG overflows*/
    RCU_FLAG_OVF30    = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 30U),                  /*!< PORWDG_OVF30 captures the status of standby exit acknowledgement by PMU when POR_WDG overflows*/
    RCU_FLAG_OVF31    = RCU_REGIDX_BIT(PORSTAT0_REG_OFFSET, 31U),                  /*!< PORWDG_OVF31 captures RCTL reset event (if occurred) while the device is in standby mode*/
    /* RCU_PORSTAT1 flag */
    RCU_FLAG_OVF32   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 0U),                   /*!< PORWDG_OVF32 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[0]) */
    RCU_FLAG_OVF33   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 1U),                   /*!< PORWDG_OVF33 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[1]) */
    RCU_FLAG_OVF34   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 2U),                   /*!< PORWDG_OVF34 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[2]) */
    RCU_FLAG_OVF35   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 3U),                   /*!< PORWDG_OVF35 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[3]) */
    RCU_FLAG_OVF36   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 4U),                   /*!< PORWDG_OVF36 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[4]) */
    RCU_FLAG_OVF37   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 5U),                   /*!< PORWDG_OVF37 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[5]) */
    RCU_FLAG_OVF38   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 6U),                   /*!< PORWDG_OVF38 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[6]) */
    RCU_FLAG_OVF39   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 7U),                   /*!< PORWDG_OVF39 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[7]) */
    RCU_FLAG_OVF40   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 8U),                   /*!< PORWDG_OVF40 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[8]) */
    RCU_FLAG_OVF41   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 9U),                   /*!< PORWDG_OVF41 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[9]) */
    RCU_FLAG_OVF42   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 10U),                  /*!< PORWDG_OVF42 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[10]) */
    RCU_FLAG_OVF43   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 11U),                  /*!< PORWDG_OVF43 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[11]) */
    RCU_FLAG_OVF44   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 12U),                  /*!< PORWDG_OVF44 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[12]) */
    RCU_FLAG_OVF45   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 13U),                  /*!< PORWDG_OVF45 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[13]) */
    RCU_FLAG_OVF46   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 14U),                  /*!< PORWDG_OVF46 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[14]) */
    RCU_FLAG_OVF47   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 15U),                  /*!< PORWDG_OVF47 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[15]) */
    RCU_FLAG_OVF48   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 16U),                  /*!< PORWDG_OVF48 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[16]) */
    RCU_FLAG_OVF49   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 17U),                  /*!< PORWDG_OVF49 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[17]) */
    RCU_FLAG_OVF50   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 18U),                  /*!< PORWDG_OVF50 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[18]) */
    RCU_FLAG_OVF51   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 19U),                  /*!< PORWDG_OVF51 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[19]) */
    RCU_FLAG_OVF52   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 20U),                  /*!< PORWDG_OVF52 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[20]) */
    RCU_FLAG_OVF53   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 21U),                  /*!< PORWDG_OVF53 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[21]) */
    RCU_FLAG_OVF54   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 22U),                  /*!< PORWDG_OVF54 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[22]) */
    RCU_FLAG_OVF55   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 23U),                  /*!< PORWDG_OVF55 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[23]) */
    RCU_FLAG_OVF56   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 24U),                  /*!< PORWDG_OVF56 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[24]) */
    RCU_FLAG_OVF57   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 25U),                  /*!< PORWDG_OVF57 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[25]) */
    RCU_FLAG_OVF58   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 26U),                  /*!< PORWDG_OVF58 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[26]) */
    RCU_FLAG_OVF59   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 27U),                  /*!< PORWDG_OVF59 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[27]) */
    RCU_FLAG_OVF60   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 28U),                  /*!< PORWDG_OVF60 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[28]) */
    RCU_FLAG_OVF61   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 29U),                  /*!< PORWDG_OVF61 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[29]) */
    RCU_FLAG_OVF62   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 30U),                  /*!< PORWDG_OVF62 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[30]) */
    RCU_FLAG_OVF63   = RCU_REGIDX_BIT(PORSTAT1_REG_OFFSET, 31U),                  /*!< PORWDG_OVF63 captures RCTL subsystem/external event status register when PORWDG overflows (RCU_SUBSERSTAT[31]) */
    /* RCU_PORSTAT2 flag */
    RCU_FLAG_OVF64   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 0U),                   /*!< PORWDG_OVF64 captures RCTL system event status register when PORWDG overflows (RCU_SYSRSTSTAT[0]) */
    RCU_FLAG_OVF65   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 1U),                   /*!< PORWDG_OVF65 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[1]) */
    RCU_FLAG_OVF66   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 2U),                   /*!< PORWDG_OVF66 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[2]) */
    RCU_FLAG_OVF67   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 3U),                   /*!< PORWDG_OVF67 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[3]) */
    RCU_FLAG_OVF68   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 4U),                   /*!< PORWDG_OVF68 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[4]) */
    RCU_FLAG_OVF69   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 5U),                   /*!< PORWDG_OVF69 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[5]) */
    RCU_FLAG_OVF70   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 6U),                   /*!< PORWDG_OVF70 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[6]) */
    RCU_FLAG_OVF71   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 7U),                   /*!< PORWDG_OVF71 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[7]) */
    RCU_FLAG_OVF72   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 8U),                   /*!< PORWDG_OVF72 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[8]) */
    RCU_FLAG_OVF73   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 9U),                   /*!< PORWDG_OVF73 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[9]) */
    RCU_FLAG_OVF74   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 10U),                  /*!< PORWDG_OVF74 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[10]) */
    RCU_FLAG_OVF75   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 11U),                  /*!< PORWDG_OVF75 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[11]) */
    RCU_FLAG_OVF76   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 12U),                  /*!< PORWDG_OVF76 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[12]) */
    RCU_FLAG_OVF77   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 13U),                  /*!< PORWDG_OVF77 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[13]) */
    RCU_FLAG_OVF78   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 14U),                  /*!< PORWDG_OVF78 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[14]) */
    RCU_FLAG_OVF79   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 15U),                  /*!< PORWDG_OVF79 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[15]) */
    RCU_FLAG_OVF80   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 16U),                  /*!< PORWDG_OVF80 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[16]) */
    RCU_FLAG_OVF81   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 17U),                  /*!< PORWDG_OVF81 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[17]) */
    RCU_FLAG_OVF82   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 18U),                  /*!< PORWDG_OVF82 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[18]) */
    RCU_FLAG_OVF83   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 19U),                  /*!< PORWDG_OVF83 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[19]) */
    RCU_FLAG_OVF84   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 20U),                  /*!< PORWDG_OVF84 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[20]) */
    RCU_FLAG_OVF85   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 21U),                  /*!< PORWDG_OVF85 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[21]) */
    RCU_FLAG_OVF86   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 22U),                  /*!< PORWDG_OVF86 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[22]) */
    RCU_FLAG_OVF87   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 23U),                  /*!< PORWDG_OVF87 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[23]) */
    RCU_FLAG_OVF88   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 24U),                  /*!< PORWDG_OVF88 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[24]) */
    RCU_FLAG_OVF89   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 25U),                  /*!< PORWDG_OVF89 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[25]) */
    RCU_FLAG_OVF90   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 26U),                  /*!< PORWDG_OVF90 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[26]) */
    RCU_FLAG_OVF91   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 27U),                  /*!< PORWDG_OVF91 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[27]) */
    RCU_FLAG_OVF92   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 28U),                  /*!< PORWDG_OVF92 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[28]) */
    RCU_FLAG_OVF93   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 29U),                  /*!< PORWDG_OVF93 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[29]) */
    RCU_FLAG_OVF94   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 30U),                  /*!< PORWDG_OVF94 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[30]) */
    RCU_FLAG_OVF95   = RCU_REGIDX_BIT(PORSTAT2_REG_OFFSET, 31U),                  /*!< PORWDG_OVF95 captures the status of subsystem reset sequence process (RCU_SYSRSTSTAT[31]) */
    /* RCU_PORSTAT3 flag */                                                       
    RCU_FLAG_OVF96   = RCU_REGIDX_BIT(PORSTAT3_REG_OFFSET, 0U),                   /*!< PORWDG_OVF96 captures captures PORWDG reset event if PORWDG initiates a POR sequence */

} por_watchdog_overflow_flag_enum;

/* oscillator types */
typedef enum {
    RCU_HXTAL                  = RCU_REGIDX_BIT(CTL_REG_OFFSET, 16U),        /*!< HXTAL */
    RCU_LXTAL                  = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 0U),       /*!< LXTAL */
    RCU_PLL_CK                 = RCU_REGIDX_BIT(CTL_REG_OFFSET, 24U),        /*!< PLL */
} rcu_osci_type_enum;

/* rcu clock frequency */
typedef enum {
    CK_SYS      = 0,                                                         /*!< system clock */
    CK_AHB,                                                                  /*!< AHB clock */
    CK_APB1,                                                                 /*!< APB1 clock */
    CK_APB2,                                                                 /*!< APB2 clock */
    CK_LINFLEXD,                                                             /*!< LINFlexD clock */
} rcu_clock_freq_enum;

/* RCU_CTL register bit define */
/* HXTAL frequency scale select */
#define CTL0_HXTALSCAL(regval)          (BITS(22,23) & ((uint32_t)(regval) << 22))
#define HXTAL_SCALE_4M_TO_8M            CTL0_HXTALSCAL(0)                    /*!< HXTAL scale is 2M-8MHz */
#define HXTAL_SCALE_8M_TO_16M           CTL0_HXTALSCAL(1)                    /*!< HXTAL scale is 8M-16MHz */
#define HXTAL_SCALE_16M_TO_32M          CTL0_HXTALSCAL(2)                    /*!< HXTAL scale is 16M-32MHz */
#define HXTAL_SCALE_32M_TO_40M          CTL0_HXTALSCAL(3)                    /*!< HXTAL scale is 32M-40MHz */

/* RCU_CFG0 register bit define */
/* system clock source select */
#define CFG0_SCS(regval)                (BITS(0,1) & ((uint32_t)(regval) << 0))
#define RCU_CKSYSSRC_IRC48M             CFG0_SCS(0)                          /*!< system clock source select IRC48M */
#define RCU_CKSYSSRC_HXTAL              CFG0_SCS(1)                          /*!< system clock source select HXTAL */
#define RCU_CKSYSSRC_PLLP               CFG0_SCS(2)                          /*!< system clock source select PLLP */

/* system clock source select status */
#define CFG0_SCSS(regval)               (BITS(2,3) & ((uint32_t)(regval) << 2))
#define RCU_SCSS_IRC48M                 CFG0_SCSS(0)                         /*!< system clock source select IRC48M */
#define RCU_SCSS_HXTAL                  CFG0_SCSS(1)                         /*!< system clock source select HXTAL */
#define RCU_SCSS_PLL_P                  CFG0_SCSS(2)                         /*!< system clock source select PLL_P */

/* AHB prescaler selection */
#define CFG0_AHBPSC(regval)             (BITS(4,7) & ((uint32_t)(regval) << 4))
#define RCU_AHB_CKSYS_DIV1              CFG0_AHBPSC(0)                       /*!< AHB prescaler select CK_SYS */
#define RCU_AHB_CKSYS_DIV2              CFG0_AHBPSC(8)                       /*!< AHB prescaler select CK_SYS/2 */
#define RCU_AHB_CKSYS_DIV4              CFG0_AHBPSC(9)                       /*!< AHB prescaler select CK_SYS/4 */
#define RCU_AHB_CKSYS_DIV8              CFG0_AHBPSC(10)                      /*!< AHB prescaler select CK_SYS/8 */
#define RCU_AHB_CKSYS_DIV16             CFG0_AHBPSC(11)                      /*!< AHB prescaler select CK_SYS/16 */
#define RCU_AHB_CKSYS_DIV64             CFG0_AHBPSC(12)                      /*!< AHB prescaler select CK_SYS/64 */
#define RCU_AHB_CKSYS_DIV128            CFG0_AHBPSC(13)                      /*!< AHB prescaler select CK_SYS/128 */
#define RCU_AHB_CKSYS_DIV256            CFG0_AHBPSC(14)                      /*!< AHB prescaler select CK_SYS/256 */
#define RCU_AHB_CKSYS_DIV512            CFG0_AHBPSC(15)                      /*!< AHB prescaler select CK_SYS/512 */

/* APB1 prescaler selection */
#define CFG0_APB1PSC(regval)            (BITS(8,10) & ((uint32_t)(regval) << 8))
#define RCU_APB1_CKAHB_DIV1             CFG0_APB1PSC(0)                      /*!< APB1 prescaler select CK_AHB */
#define RCU_APB1_CKAHB_DIV2             CFG0_APB1PSC(4)                      /*!< APB1 prescaler select CK_AHB/2 */
#define RCU_APB1_CKAHB_DIV4             CFG0_APB1PSC(5)                      /*!< APB1 prescaler select CK_AHB/4 */
#define RCU_APB1_CKAHB_DIV8             CFG0_APB1PSC(6)                      /*!< APB1 prescaler select CK_AHB/8 */
#define RCU_APB1_CKAHB_DIV16            CFG0_APB1PSC(7)                      /*!< APB1 prescaler select CK_AHB/16 */

/* APB2 prescaler selection */
#define CFG0_APB2PSC(regval)            (BITS(11,13) & ((uint32_t)(regval) << 11))
#define RCU_APB2_CKAHB_DIV1             CFG0_APB2PSC(0)                      /*!< APB2 prescaler select CK_AHB */
#define RCU_APB2_CKAHB_DIV2             CFG0_APB2PSC(4)                      /*!< APB2 prescaler select CK_AHB/2 */
#define RCU_APB2_CKAHB_DIV4             CFG0_APB2PSC(5)                      /*!< APB2 prescaler select CK_AHB/4 */
#define RCU_APB2_CKAHB_DIV8             CFG0_APB2PSC(6)                      /*!< APB2 prescaler select CK_AHB/8 */
#define RCU_APB2_CKAHB_DIV16            CFG0_APB2PSC(7)                      /*!< APB2 prescaler select CK_AHB/16 */

/* APB2 prescaler selection */
#define PLLMF_7                         RCU_CFG0_PLLMF_7                     /*!< bit 7 of PLLMF */
#define CFG0_PLLMF(regval)              (BITS(17,23) & ((uint32_t)(regval) << 17))
#define PLLMF(x)                        ((x > 0x7FU) ? (PLLMF_7 | CFG0_PLLMF(x & 0x7FU)) : (CFG0_PLLMF(x)))

/* CKOUT1 Clock source selection */
#define CFG0_CKOUT1SEL(regval)          (BITS(24,26) & ((uint32_t)(regval) << 24))
#define RCU_CKOUT1SRC_IRC48M            CFG0_CKOUT1SEL(0)                     /*!< IRC48M clock is selected as CK_OUT1 clock source */
#define RCU_CKOUT1SRC_HXTAL             CFG0_CKOUT1SEL(1)                     /*!< HXTAL is selected as CK_OUT1 clock source */
#define RCU_CKOUT1SRC_IRC40K            CFG0_CKOUT1SEL(2)                     /*!< IRC40K is selected as CK_OUT1 clock source */
#define RCU_CKOUT1SRC_LXTAL             CFG0_CKOUT1SEL(3)                     /*!< LXTAL clock is selected as CK_OUT1 clock source */
#define RCU_CKOUT1SRC_CKAPB2            CFG0_CKOUT1SEL(4)                     /*!< CK_APB2 is selected as CK_OUT1 clock source */

/* CK_OUT1 divider */
#define CFG0_CKOUT1DIV(regval)           (BITS(28,30) & ((uint32_t)(regval) << 28))
#define RCU_CKOUT1_DIV1                  CFG0_CKOUT1DIV(0)                     /*!< CK_OUT1 is divided by 1 */
#define RCU_CKOUT1_DIV2                  CFG0_CKOUT1DIV(1)                     /*!< CK_OUT1 is divided by 2 */
#define RCU_CKOUT1_DIV4                  CFG0_CKOUT1DIV(2)                     /*!< CK_OUT1 is divided by 4 */
#define RCU_CKOUT1_DIV8                  CFG0_CKOUT1DIV(3)                     /*!< CK_OUT1 is divided by 8 */
#define RCU_CKOUT1_DIV16                 CFG0_CKOUT1DIV(4)                     /*!< CK_OUT1 is divided by 16 */
#define RCU_CKOUT1_DIV32                 CFG0_CKOUT1DIV(5)                     /*!< CK_OUT1 is divided by 32 */
#define RCU_CKOUT1_DIV64                 CFG0_CKOUT1DIV(6)                     /*!< CK_OUT1 is divided by 64 */
#define RCU_CKOUT1_DIV128                CFG0_CKOUT1DIV(7)                     /*!< CK_OUT1 is divided by 128 */

/* The CK_PLL divide by 1 or 2 for CK_OUT0 */
#define CFG0_PLLDV(regval)              (BIT(31) & ((uint32_t)(regval) << 31))

/* RCU_CFG1 register bit define */
/* PREDV division factor */
#define CFG1_PREDV(regval)              (BITS(0,2) & ((uint32_t)(regval) << 0))
#define RCU_PREDV_DIV1                  CFG1_PREDV(0)                        /*!< PREDV input clock source not divided */
#define RCU_PREDV_DIV2                  CFG1_PREDV(2)                        /*!< PREDV input clock source divided by 2 */
#define RCU_PREDV_DIV3                  CFG1_PREDV(3)                        /*!< PREDV input clock source divided by 3 */
#define RCU_PREDV_DIV4                  CFG1_PREDV(4)                        /*!< PREDV input clock source divided by 4 */
#define RCU_PREDV_DIV5                  CFG1_PREDV(5)                        /*!< PREDV input clock source divided by 5 */
#define RCU_PREDV_DIV6                  CFG1_PREDV(6)                        /*!< PREDV input clock source divided by 6 */
#define RCU_PREDV_DIV7                  CFG1_PREDV(7)                        /*!< PREDV input clock source divided by 7 */

/* The PLLQ clock prescaler */
#define RCU_PLLQPSC_DIV_MIN          ((uint32_t)1U)                          /*!< PLLQPSC_DIV min value */
#define RCU_PLLQPSC_DIV_MAX          ((uint32_t)64U)                         /*!< PLLQPSC_DIV max value */

/* The PLLP clock prescaler */
#define RCU_PLLPPSC_DIV_MIN          ((uint32_t)1U)                          /*!< PLLPPSC_DIV min value */
#define RCU_PLLPPSC_DIV_MAX          ((uint32_t)64U)                         /*!< PLLPPSC_DIV max value */

/* FWDGT clock source selection */
#define CFG1_FWDGTSRC(regval)          (BIT(0) & ((uint32_t)(regval)))
#define RCU_FWDGTSRC_IRC40K             CFG1_FWDGTSRC(0)                    /*!< IRC40K is selected as FWDGT clock source */
#define RCU_FWDGTSRC_LXTAL              CFG1_FWDGTSRC(1)                    /*!< LXTAL is selected as FWDGT clock source */

/* IRC48M response fail configuration */
#define RCU_IRC48M_POR                   0U                                 /*!< IRC48M fail response,POR reset is triggered */
#define RCU_FFIO0_FFIO1                  1U                                 /*!< the failure of IRC48M will set FFIO0 and FFIO1 pins to High-Z state */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* MFCOM prescaler select */
#define CFG1_MFCOMPSC(regval)           (BITS(28,29) & ((uint32_t)(regval) << 28))
#define RCU_CKMFCOM_CKAHB_DIV1          CFG1_MFCOMPSC(0)                       /*!< MFCOM prescaler select CK_AHB */
#define RCU_CKMFCOM_CKAHB_DIV2          CFG1_MFCOMPSC(1)                       /*!< MFCOM prescaler select CK_AHB/2 */
#define RCU_CKMFCOM_CKAHB_DIV4          CFG1_MFCOMPSC(2)                       /*!< MFCOM prescaler select CK_AHB/4 */
#define RCU_CKMFCOM_CKAHB_DIV8          CFG1_MFCOMPSC(3)                       /*!< MFCOM prescaler select CK_AHB/8 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* AIT clock source select */
#define CFG1_AITSRC(regval)             (BITS(26,27) & ((uint32_t)(regval) << 26))
#define RCU_CKAITSRC_IRC48M             CFG1_AITSRC(0)                         /*!< AIT clock source select CK_IRC48M */
#define RCU_CKAITSRC_CK_PLL_Q_DIV2      CFG1_AITSRC(1)                         /*!< AIT clock source select CK_PLL_Q/2 */
#define RCU_CKAITSRC_CK_PLL_Q_DIV3      CFG1_AITSRC(2)                         /*!< AIT clock source select CK_PLL_Q/3 */
#define RCU_CKAITSRC_CK_PLL_Q_DIV4      CFG1_AITSRC(3)                         /*!< AIT clock source select CK_PLL_Q/4 */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* ATE clock source select */
#define CFG1_ATESRC(regval)             (BITS(24,25) & ((uint32_t)(regval) << 24))
#define RCU_CKATESRC_IRC48M             CFG1_ATESRC(0)                         /*!< ATE clock source select IRC48M */
#define RCU_CKATESRC_CK_PLL_Q_DIV2      CFG1_ATESRC(1)                         /*!< ATE clock source select CK_PLL_Q/2 */
#define RCU_CKATESRC_CK_PLL_Q_DIV3      CFG1_ATESRC(2)                         /*!< ATE clock source select CK_PLL_Q/3 */
#define RCU_CKATESRC_CK_PLL_Q_DIV4      CFG1_ATESRC(3)                         /*!< ATE clock source select CK_PLL_Q/4 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* ADC prescaler select */
#define CFG2_ADCPSC(regval)             (BITS(27,31) & ((uint32_t)(regval) << 27))
#define RCU_CKADC_DIV2                  CFG2_ADCPSC(0)                       /*!< ADC prescaler select CK_ADC/2 */
#define RCU_CKADC_DIV3                  CFG2_ADCPSC(2)                       /*!< ADC prescaler select CK_ADC/3 */
#define RCU_CKADC_DIV4                  CFG2_ADCPSC(3)                       /*!< ADC prescaler select CK_ADC/4 */
#define RCU_CKADC_DIV5                  CFG2_ADCPSC(4)                       /*!< ADC prescaler select CK_ADC/5 */
#define RCU_CKADC_DIV6                  CFG2_ADCPSC(5)                       /*!< ADC prescaler select CK_ADC/6 */
#define RCU_CKADC_DIV7                  CFG2_ADCPSC(6)                       /*!< ADC prescaler select CK_ADC/7 */
#define RCU_CKADC_DIV8                  CFG2_ADCPSC(7)                       /*!< ADC prescaler select CK_ADC/8 */
#define RCU_CKADC_DIV9                  CFG2_ADCPSC(8)                       /*!< ADC prescaler select CK_ADC/9 */
#define RCU_CKADC_DIV10                 CFG2_ADCPSC(9)                       /*!< ADC prescaler select CK_ADC/10 */
#define RCU_CKADC_DIV11                 CFG2_ADCPSC(10)                      /*!< ADC prescaler select CK_ADC/11 */
#define RCU_CKADC_DIV12                 CFG2_ADCPSC(11)                      /*!< ADC prescaler select CK_ADC/12 */
#define RCU_CKADC_DIV13                 CFG2_ADCPSC(12)                      /*!< ADC prescaler select CK_ADC/13 */
#define RCU_CKADC_DIV14                 CFG2_ADCPSC(13)                      /*!< ADC prescaler select CK_ADC/14 */
#define RCU_CKADC_DIV15                 CFG2_ADCPSC(14)                      /*!< ADC prescaler select CK_ADC/15 */
#define RCU_CKADC_DIV16                 CFG2_ADCPSC(15)                      /*!< ADC prescaler select CK_ADC/16 */
#define RCU_CKADC_DIV17                 CFG2_ADCPSC(16)                      /*!< ADC prescaler select CK_ADC/17 */
#define RCU_CKADC_DIV18                 CFG2_ADCPSC(17)                      /*!< ADC prescaler select CK_ADC/18 */
#define RCU_CKADC_DIV19                 CFG2_ADCPSC(18)                      /*!< ADC prescaler select CK_ADC/19 */
#define RCU_CKADC_DIV20                 CFG2_ADCPSC(19)                      /*!< ADC prescaler select CK_ADC/20 */
#define RCU_CKADC_DIV21                 CFG2_ADCPSC(20)                      /*!< ADC prescaler select CK_ADC/21 */
#define RCU_CKADC_DIV22                 CFG2_ADCPSC(21)                      /*!< ADC prescaler select CK_ADC/22 */
#define RCU_CKADC_DIV23                 CFG2_ADCPSC(22)                      /*!< ADC prescaler select CK_ADC/23 */
#define RCU_CKADC_DIV24                 CFG2_ADCPSC(23)                      /*!< ADC prescaler select CK_ADC/24 */
#define RCU_CKADC_DIV25                 CFG2_ADCPSC(24)                      /*!< ADC prescaler select CK_ADC/25 */
#define RCU_CKADC_DIV26                 CFG2_ADCPSC(25)                      /*!< ADC prescaler select CK_ADC/26 */
#define RCU_CKADC_DIV27                 CFG2_ADCPSC(26)                      /*!< ADC prescaler select CK_ADC/27 */
#define RCU_CKADC_DIV28                 CFG2_ADCPSC(27)                      /*!< ADC prescaler select CK_ADC/28 */
#define RCU_CKADC_DIV29                 CFG2_ADCPSC(28)                      /*!< ADC prescaler select CK_ADC/29 */
#define RCU_CKADC_DIV30                 CFG2_ADCPSC(29)                      /*!< ADC prescaler select CK_ADC/30 */
#define RCU_CKADC_DIV31                 CFG2_ADCPSC(30)                      /*!< ADC prescaler select CK_ADC/31 */
#define RCU_CKADC_DIV32                 CFG2_ADCPSC(31)                      /*!< ADC prescaler select CK_ADC/32 */

/* PLL clock source selection */
#define RCU_PLLSRC_IRC48M              ((uint32_t)0x00000000U)               /*!< IRC48M clock is selected as clock source of PLL */
#define RCU_PLLSRC_HXTAL                RCU_CFG0_PLLSEL                      /*!< HXTAL is selected as clock source of PLL */

/* CKOUT0 Clock source selection */
#define CFG1_CKOUT0SEL(regval)           (BITS(16,19) & ((uint32_t)(regval) << 16))
#define RCU_CKOUT0SRC_CORECK             CFG1_CKOUT0SEL(0)                     /*!< Core clock is selected */
#define RCU_CKOUT0SRC_CKAPB1             CFG1_CKOUT0SEL(1)                     /*!< CK_APB1 is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_IRC40K             CFG1_CKOUT0SEL(2)                     /*!< IRC40K is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_LXTAL              CFG1_CKOUT0SEL(3)                     /*!< LXTAL clock is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_CKSYS              CFG1_CKOUT0SEL(4)                     /*!< CK_SYS is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_IRC48M             CFG1_CKOUT0SEL(5)                     /*!< IRC48M is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_HXTAL              CFG1_CKOUT0SEL(6)                     /*!< HXTAL is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_CKPLLP             CFG1_CKOUT0SEL(7)                     /*!< CK_PLLP clock is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_CKPLLP_DIV2        (CFG1_CKOUT0SEL(7) | BIT(31))         /*!< CK_PLL/2 is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_CKAPB2             CFG1_CKOUT0SEL(9)                     /*!< CK_APB2 is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_HSMPCLK            CFG1_CKOUT0SEL(10)                    /*!< HSM_PCLK clock is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_HSMHCLK            CFG1_CKOUT0SEL(11)                    /*!< HSM_HCLK is selected as CK_OUT0 clock source */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_CKOUT0SRC_CKENETRX           CFG1_CKOUT0SEL(12)                    /*!< CK_ENETRX is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_CKENETTX           CFG1_CKOUT0SEL(13)                    /*!< CK_ENETTX is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_CKENETMACRMI       CFG1_CKOUT0SEL(14)                    /*!< CK_ENETMACRMI clock is selected as CK_OUT0 clock source */
#define RCU_CKOUT0SRC_CKENETTS           CFG1_CKOUT0SEL(15)                    /*!< CK_ENETTS is selected as CK_OUT0 clock source */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* CK_OUT0 divider */
#define CFG1_CKOUT0DIV(regval)           (BITS(20,22) & ((uint32_t)(regval) << 20))
#define RCU_CKOUT0_DIV1                  CFG1_CKOUT0DIV(0)                     /*!< CK_OUT0 is divided by 1 */
#define RCU_CKOUT0_DIV2                  CFG1_CKOUT0DIV(1)                     /*!< CK_OUT0 is divided by 2 */
#define RCU_CKOUT0_DIV4                  CFG1_CKOUT0DIV(2)                     /*!< CK_OUT0 is divided by 4 */
#define RCU_CKOUT0_DIV8                  CFG1_CKOUT0DIV(3)                     /*!< CK_OUT0 is divided by 8 */
#define RCU_CKOUT0_DIV16                 CFG1_CKOUT0DIV(4)                     /*!< CK_OUT0 is divided by 16 */
#define RCU_CKOUT0_DIV32                 CFG1_CKOUT0DIV(5)                     /*!< CK_OUT0 is divided by 32 */
#define RCU_CKOUT0_DIV64                 CFG1_CKOUT0DIV(6)                     /*!< CK_OUT0 is divided by 64 */
#define RCU_CKOUT0_DIV128                CFG1_CKOUT0DIV(7)                     /*!< CK_OUT0 is divided by 128 */

/* LXTAL drive capability */
#define BDCTL_LXTALDRI(regval)           (BITS(3,4) & ((uint32_t)(regval) << 3))
#define RCU_LXTAL_LOWDRI                 BDCTL_LXTALDRI(0)                    /*!< lower driving capability */
#define RCU_LXTAL_MED_LOWDRI             BDCTL_LXTALDRI(1)                    /*!< medium low driving capability */
#define RCU_LXTAL_MED_HIGHDRI            BDCTL_LXTALDRI(2)                    /*!< medium high driving capability */
#define RCU_LXTAL_HIGHDRI                BDCTL_LXTALDRI(3)                    /*!< higher driving capability */

/* RTC clock entry selection */
#define BDCTL_RTCSRC(regval)             (BITS(8,9) & ((uint32_t)(regval) << 8))
#define RCU_RTCSRC_NONE                  BDCTL_RTCSRC(0)                     /*!< no clock is selected */
#define RCU_RTCSRC_LXTAL                 BDCTL_RTCSRC(1)                     /*!< LXTAL is selected as RTC clock source */
#define RCU_RTCSRC_IRC40K                BDCTL_RTCSRC(2)                     /*!< IRC40K is selected as RTC clock source */
#define RCU_RTCSRC_HXTAL_DIV_128         BDCTL_RTCSRC(3)                     /*!< HXTAL/128 is selected as RTC clock source */

/* ADC clock source selection */
#define CFG2_ADCSRC(regval)              (BITS(24,25) & ((uint32_t)(regval) << 24))
#define RCU_ADCSRC_HCLK                  CFG2_ADCSRC(0)                    /*!< HCLK is selected as ADC clock source */
#define RCU_ADCSRC_SYS                   CFG2_ADCSRC(1)                    /*!< CK_SYS is selected as ADC clock source */
#define RCU_ADCSRC_PLLP                  CFG2_ADCSRC(3)                    /*!< PLLP is selected as ADC clock source */

/* SPI clock source selection */
#define CFG3_SPISRC(regval)              (BITS(0,1) & ((uint32_t)(regval)))
#define RCU_SPISRC_APB1                  CFG3_SPISRC(0)                    /*!< CK_APB1 is selected as SPI clock source */
#define RCU_SPISRC_APB2                  CFG3_SPISRC(1)                    /*!< CK_APB2 is selected as SPI clock source */
#define RCU_SPISRC_IRC48M                CFG3_SPISRC(2)                    /*!< CK_IRC48M is selected as SPI clock source */
#define RCU_SPISRC_AHB                   CFG3_SPISRC(3)                    /*!< CK_AHB is selected as SPI clock source */

/* DTM_CAN clock source selection */
#define CFG2_DTM_CAN0SRC(regval)             (BITS(2,3) & ((uint32_t)(regval) << 2))
#define RCU_DTM_CANSRC_HXTAL                 CFG2_DTM_CAN0SRC(3)                      /*!< CK_HXTAL is selected as DTM_CAN clock source */
#define RCU_DTM_CANSRC_AHB                   CFG2_DTM_CAN0SRC(2)                      /*!< AHB is selected as DTM_CAN clock source */
#define RCU_DTM_CANSRC_PCLK2                 CFG2_DTM_CAN0SRC(1)                      /*!< PCLK2 is selected as DTM_CAN clock source */
#define RCU_DTM_CANSRC_IRC48M                CFG2_DTM_CAN0SRC(0)                      /*!< IRC48M is selected as DTM_CAN clock source */

/* TRACE clock source selection */
#define CFG3_TRACESRC(regval)            (BITS(30,31) & ((uint32_t)(regval) << 30))
#define RCU_TRACESRC_PLLQ                CFG3_TRACESRC(3)                      /*!< PLLQ is selected as TRACE clock source */
#define RCU_TRACESRC_PLLP                CFG3_TRACESRC(2)                      /*!< PLLP is selected as TRACE clock source */
#define RCU_TRACESRC_HXTAL               CFG3_TRACESRC(1)                      /*!< HXTAL is selected as TRACE clock source */
#define RCU_TRACESRC_IRC48M              CFG3_TRACESRC(0)                      /*!< IRC48M is selected as TRACE clock source */

/* QSPI clock source selection */
#define CFG3_QSPISRC(regval)             (BITS(25,26) & ((uint32_t)(regval) << 25))
#define RCU_QSPISRC_IRC48M               CFG3_QSPISRC(0)                      /*!< IRC48M is selected as QSPI clock source */
#define RCU_QSPISRC_HCLK                 CFG3_QSPISRC(1)                      /*!< HCLK is selected as QSPI clock source */
#define RCU_QSPISRC_PLLP                 CFG3_QSPISRC(2)                      /*!< PLLP is selected as QSPI clock source */
#define RCU_QSPISRC_PLLQ                 CFG3_QSPISRC(3)                      /*!< PLLQ is selected as QSPI clock source */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* ENETTS clock source selection */
#define CFG3_ENETTSSRC(regval)           (BITS(22,24) & ((uint32_t)(regval) << 22))
#define RCU_ENETTSSRC_CK_ENETTX          CFG3_ENETTSSRC(4)                    /*!< CK_ENETTX is selected as ENETTS clock source */
#define RCU_ENETTSSRC_CK_ENETRX          CFG3_ENETTSSRC(3)                    /*!< CK_ENETRX is selected as ENETTS clock source */
#define RCU_ENETTSSRC_PLLP               CFG3_ENETTSSRC(2)                    /*!< PLLP is selected as ENETTS clock source */
#define RCU_ENETTSSRC_HXTAL              CFG3_ENETTSSRC(1)                    /*!< HXTAL is selected as ENETTS clock source */
#define RCU_ENETTSSRC_IRC48M             CFG3_ENETTSSRC(0)                    /*!< IRC48M is selected as ENETTS clock source */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* WWDGT clock source selection */
#define CFG3_WWDGT0SRC(regval)           (BITS(16,18) & ((uint32_t)(regval) << 16))
#define RCU_WWDGTSRC_IRC48M              CFG3_WWDGT0SRC(0)                  /*!< CK_HXTAL is selected as WWDGT0 clock source */
#define RCU_WWDGTSRC_LXTAL               CFG3_WWDGT0SRC(1)                  /*!< LXTAL is selected as WWDGT0 clock source */
#define RCU_WWDGTSRC_IRC40K              CFG3_WWDGT0SRC(2)                  /*!< IRC40K is selected as WWDGT0 clock source */
#define RCU_WWDGTSRC_HXTAL               CFG3_WWDGT0SRC(3)                  /*!< HXTAL is selected as WWDGT0 clock source */
#define RCU_WWDGTSRC_CKSYS               CFG3_WWDGT0SRC(4)                  /*!< CK_SYS is selected as WWDGT0 clock source */
#define RCU_WWDGTSRC_PCLK1               CFG3_WWDGT0SRC(5)                  /*!< PCLK1 is selected as WWDGT0 clock source */

/* LINFlexD clock source selection */
#define CFG3_LINFLEXDSRC(regval)         (BITS(14,15) & ((uint32_t)(regval) << 14))
#define RCU_LINFLEXDSRC_CKSYS            CFG3_LINFLEXDSRC(3)                /*!< CK_SYS is selected as LINFlexD clock source */
#define RCU_LINFLEXDSRC_PLL_P            CFG3_LINFLEXDSRC(2)                /*!< PLL_P is selected as LINFlexD clock source */
#define RCU_LINFLEXDSRC_HXTAL            CFG3_LINFLEXDSRC(1)                /*!< HXTAL is selected as LINFlexD clock source */
#define RCU_LINFLEXDSRC_IRC48M           CFG3_LINFLEXDSRC(0)                /*!< IRC48M is selected as LINFlexD clock source */

/* TRACE clock source selection */
#define CFG3_TRACEDIV(regval)            (BITS(27,29) & ((uint32_t)(regval) << 27))
#define RCU_CKTRACE_DIV1                 CFG3_TRACEDIV(0)                      /*!< CK_TRACE is not divided */
#define RCU_CKTRACE_DIV2                 CFG3_TRACEDIV(1)                      /*!< CK_TRACE is divided by 2 */
#define RCU_CKTRACE_DIV3                 CFG3_TRACEDIV(2)                      /*!< CK_TRACE is divided by 3 */
#define RCU_CKTRACE_DIV4                 CFG3_TRACEDIV(3)                      /*!< CK_TRACE is divided by 4 */
#define RCU_CKTRACE_DIV5                 CFG3_TRACEDIV(4)                      /*!< CK_TRACE is divided by 5*/
#define RCU_CKTRACE_DIV6                 CFG3_TRACEDIV(5)                      /*!< CK_TRACE is divided by 6 */
#define RCU_CKTRACE_DIV7                 CFG3_TRACEDIV(6)                      /*!< CK_TRACE is divided by 7 */
#define RCU_CKTRACE_DIV8                 CFG3_TRACEDIV(7)                      /*!< CK_TRACE is divided by 8 */

/* adjust the PLL loss of lock accuracy */
#define PLLLOL_PLLLOLCTL(regval)         (BITS(0,1) & ((uint32_t)(regval)))
#define RCU_PLLLOL_UNLOCK_RANGE_1        PLLLOL_PLLLOLCTL(0)                   /*!< Unlock range = expected value(100) �� 5 */
#define RCU_PLLLOL_UNLOCK_RANGE_2        PLLLOL_PLLLOLCTL(1)                   /*!< Unlock range = expected value(100) �� 9 */
#define RCU_PLLLOL_UNLOCK_RANGE_3        PLLLOL_PLLLOLCTL(2)                   /*!< Unlock range = expected value(100) �� 17 */
#define RCU_PLLLOL_UNLOCK_RANGE_4        PLLLOL_PLLLOLCTL(3)                   /*!< Unlock range = expected value(100) �� 33 */

/* adjust the PLL loss of lock accuracy */
#define PLLSSCTL_SS_TYPE(regval)         (BIT(30) & ((uint32_t)(regval)<< 30))
#define RCU_SS_TYPE_CENTER               PLLSSCTL_SS_TYPE(0)                /*!< enter spread type is selected */
#define RCU_SS_TYPE_DOWN                 PLLSSCTL_SS_TYPE(1)                /*!< down spread type is selected */

/* RCTL flag definitions */
/* RCTL system reset flag definitions */
#define RCU_FLAG_POR                          RCU_SYSRSTSTAT_PORF                                 /*!< Power-on reset flag */
#define RCU_FLAG_FMU_REA_FAIL                 RCU_SYSRSTSTAT_FMU_REA_FAIL                         /*!< System reset flag FMU_REA_FAIL */
#define RCU_FLAG_STCM_REC_FAIL                RCU_SYSRSTSTAT_STCM_REC_FAIL                        /*!< System reset flag STCM_REC_FAIL */
#define RCU_FLAG_RCTL_SUBSRU                  RCU_SYSRSTSTAT_RCTL_SUBSRUF                         /*!< System reset flag RCTL_SUBSRUF */
#define RCU_FLAG_LOHRST                       RCU_SYSRSTSTAT_LOHRSTF                              /*!< Lost of HXTAL error reset flag */
#define RCU_FLAG_LOPRST                       RCU_SYSRSTSTAT_LOPRSTF                              /*!< Lost of PLL error reset flag */
#define RCU_FLAG_CORE_CK_FAIL                 RCU_SYSRSTSTAT_CORE_CK_FAIL                         /*!< Core clock fail reset flag */
#define RCU_FLAG_SYS_CK_FAIL                  RCU_SYSRSTSTAT_SYS_CK_FAIL                          /*!< CK_SYS fail reset flag */
#define RCU_FLAG_HSM_SYSRST                   RCU_SYSRSTSTAT_HSM_SYS_RSTF                         /*!< System reset flag HSM_SYS_RSTF */
#define RCU_FLAG_SW_SYSRST                    RCU_SYSRSTSTAT_SW_SYS_RSTF                          /*!< System reset flag SW_SYS_RSTF */
#define RCU_FLAG_DBG_SYSRST                   RCU_SYSRSTSTAT_DBG_SYS_RSTF                         /*!< System reset flag DBG_SYS_RSTF */
/* RCTL subsystem reset flag definitions */
#define RCU_FLAG_EXTRST                       RCU_SUBSERSTAT_EXRF                                 /*!< External reset flag EXRF */
#define RCU_FLAG_OBSTDBY                      RCU_SUBSERSTAT_OBSTDBY_RSTF                         /*!< Subsystem reset flag OBSTDBY_RSTF */
#define RCU_FLAG_FMU                          RCU_SUBSERSTAT_FMU_RSTF                             /*!< Subsystem reset flag FMU_RSTF */
#define RCU_FLAG_ST_FINISH                    RCU_SUBSERSTAT_ST_FINISH                            /*!< Subsystem reset flag ST_FINISH */
#define RCU_FLAG_FWDGT0                       RCU_SUBSERSTAT_FWDGT0_RSTF                          /*!< Subsystem reset flag FWDGT0_RSTF */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_FLAG_FWDGT1                       RCU_SUBSERSTAT_FWDGT1_RSTF                          /*!< Subsystem reset flag FWDGT1_RSTF */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_FLAG_SWRST                        RCU_SUBSERSTAT_SWRSTF                               /*!< Software reset flag */
#define RCU_FLAG_WWDGT0                       RCU_SUBSERSTAT_WWDGT0_RSTF                          /*!< Subsystem reset flag WWDGT0_RSTF */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define RCU_FLAG_WWDGT1                       RCU_SUBSERSTAT_WWDGT1_RSTF                          /*!< Subsystem reset flag WWDGT1_RSTF */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RCU_FLAG_HSM_WDGT                     RCU_SUBSERSTAT_HSM_WDGT_RSTF                        /*!< Subsystem reset flag HSM_WDGT_RSTF */
#define RCU_FLAG_HSM_APP                      RCU_SUBSERSTAT_HSM_APP_RSTF                         /*!< Subsystem reset flag HSM_APP_RSTF */
#define RCU_FLAG_SW_SUBS                      RCU_SUBSERSTAT_SW_SUBS_RSTF                         /*!< Subsystem reset flag SW_SUBS_RSTF */
#define RCU_FLAG_DBG                          RCU_SUBSERSTAT_DBG_RSTF                             /*!< Debug reset flag DBG_RSTF */
#define RCU_FLAG_OBL                          RCU_SUBSERSTAT_OBL_RSTF                             /*!< Option byte loader reset flag */


/* RCTL TMR flag definitions */
#define RCU_FLAG_RCU_SYSRSTSTAT               RCU_TMRERRSTAT_TMR_RCU_SYSRSTSTAT                   /*!< RCU_SYSRSTSTAT TMR error status */
#define RCU_FLAG_RCU_SUBSRCTL                 RCU_TMRERRSTAT_TMR_RCU_SUBSRCTL                     /*!< RCU_SUBSRCTL TMR error status */
#define RCU_FLAG_RCU_SUBSRPACTL               RCU_TMRERRSTAT_TMR_RCU_SUBSRPACTL                   /*!< RCU_SUBSRPACTL TMR error status */
#define RCU_FLAG_RCU_SYSMRETH                 RCU_TMRERRSTAT_TMR_RCU_SYSMRETH                     /*!< RCU_SYSMRETH TMR error status */
#define RCU_FLAG_RCU_ERPACFG                  RCU_TMRERRSTAT_TMR_RCU_ERPACFG                      /*!< RCU_ERPACFG TMR error status */
#define RCU_FLAG_AHBRST                       RCU_TMRERRSTAT_TMR_AHBRST                           /*!< AHBRST TMR error status */
#define RCU_FLAG_APBRST                       RCU_TMRERRSTAT_TMR_APBRST                           /*!< APBRST1/2 TMR error status */
#define RCU_FLAG_PORWDG1                      RCU_TMRERRSTAT_TMR_PORWDG1                          /*!< PORWDG1 TMR error status */
#define RCU_FLAG_PORWDG2                      RCU_TMRERRSTAT_TMR_PORWDG2                          /*!< PORWDG2 TMR error status*/
#define RCU_FLAG_PORWDG3                      RCU_TMRERRSTAT_TMR_PORWDG3                          /*!< PORWDG3 TMR error status */
#define RCU_FLAG_PORWDG4                      RCU_TMRERRSTAT_TMR_PORWDG4                          /*!< PORWDG4 TMR error status */

/* RCTL standby reset flag definitions */
#define RCU_FLAG_SYSRST                       RCU_RDSMSTAT_SYSRESF                                /*!< System reset event occurred flag in standby mode */
#define RCU_FLAG_SUBSRST                      RCU_RDSMSTAT_SUBSRESF                               /*!< Subsystem reset event occurred flag in standby mode */
/* RCTL Low-Power debug flag definitions */
#define RCU_FLAG_LPDBG                        RCU_LPDBGSTAT_LPDBGF                                /*!< Low-Power debug flag */

/* CCTL flag definitions */
/* clock stabilization and peripheral reset flags */
typedef enum {
    /* clock stabilization flags */
    RCU_FLAG_HXTALSTB      = RCU_REGIDX_BIT(CTL_REG_OFFSET, 17U),            /*!< HXTAL stabilization flag */
    RCU_FLAG_PLLSTB        = RCU_REGIDX_BIT(CTL_REG_OFFSET, 25U),            /*!< PLL stabilization flag */
    RCU_FLAG_LXTALSTB      = RCU_REGIDX_BIT(BDCTL_REG_OFFSET, 1U),           /*!< LXTAL stabilization flag */
} rcu_flag_enum;

/* clock stabilization and ckm interrupt flags */
typedef enum {
    RCU_INT_FLAG_LXTALSTB  = RCU_REGIDX_BIT(INT_REG_OFFSET, 1U),             /*!< LXTAL stabilization interrupt flag */
    RCU_INT_FLAG_HXTALSTB  = RCU_REGIDX_BIT(INT_REG_OFFSET, 3U),             /*!< HXTAL stabilization interrupt flag */
    RCU_INT_FLAG_PLLSTB    = RCU_REGIDX_BIT(INT_REG_OFFSET, 4U),             /*!< PLL stabilization interrupt flag */
    RCU_INT_FLAG_CKM       = RCU_REGIDX_BIT(INT_REG_OFFSET, 7U),             /*!< HXTAL clock stuck interrupt flag */
} rcu_int_flag_enum;

/* clock frequency monitor interrupt flags */
#define RCU_FLAG_FLMIN     RCU_CKFMCTL_FLMIN                                 /*!< Frequency lower than low frequency reference threshold event status */
#define RCU_FLAG_FHMAX     RCU_CKFMCTL_FHMAX                                 /*!< Frequency higher than high frequency reference threshold event status */

/* clock stabilization and stuck interrupt flags clear */
typedef enum {
    RCU_INT_FLAG_LXTALSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 17U),        /*!< LXTAL stabilization interrupt flag clear */
    RCU_INT_FLAG_HXTALSTB_CLR  = RCU_REGIDX_BIT(INT_REG_OFFSET, 19U),        /*!< HXTAL stabilization interrupt flag clear */
    RCU_INT_FLAG_PLLSTB_CLR    = RCU_REGIDX_BIT(INT_REG_OFFSET, 20U),        /*!< PLL stabilization interrupt flag clear */
    RCU_INT_FLAG_CKM_CLR       = RCU_REGIDX_BIT(INT_REG_OFFSET, 23U),        /*!< CKM interrupt flag clear */
} rcu_int_flag_clear_enum;

/* CCTL TMR flag definitions */
#define RCU_FLAG_ST0                          RCU_BUSIM_TMR_TMR_ST0                               /*!< System clock switching TMR error status */
#define RCU_FLAG_ST1                          RCU_BUSIM_TMR_TMR_ST1                               /*!< Clock enable TMR error status */
#define RCU_FLAG_ST2                          RCU_BUSIM_TMR_TMR_ST2                               /*!< Clock monitor enable register TMR error status */
#define RCU_FLAG_ST3                          RCU_BUSIM_TMR_TMR_ST3                               /*!< The TMR error occurs in any bit of TRIM register */
/* CCTL loss of lock detector flag definition */
#define RCU_FLAG_PLLLOL                       RCU_PLLLOL_PLLLOLF                                  /*!< Clear PLLLOLF flag */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check system clock source */
#define NOT_RCU_CKSYSSRC(ck_sys)                               (((ck_sys) != RCU_CKSYSSRC_IRC48M) && ((ck_sys) != RCU_CKSYSSRC_HXTAL) && \
                                                               ((ck_sys) != RCU_CKSYSSRC_PLL))
/* check AHB clock prescaler parameter */
#define NOT_RCU_AHB_PSC(ck_ahb)                                (((ck_ahb) != RCU_AHB_CKSYS_DIV1)   && ((ck_ahb) != RCU_AHB_CKSYS_DIV2) && \
                                                               ((ck_ahb) != RCU_AHB_CKSYS_DIV4)   && ((ck_ahb) != RCU_AHB_CKSYS_DIV8) && \
                                                               ((ck_ahb) != RCU_AHB_CKSYS_DIV16)  && ((ck_ahb) != RCU_AHB_CKSYS_DIV64) && \
                                                               ((ck_ahb) != RCU_AHB_CKSYS_DIV128) && ((ck_ahb) != RCU_AHB_CKSYS_DIV256) && \
                                                               ((ck_ahb) != RCU_AHB_CKSYS_DIV512))
/* check APB1 clock prescaler parameter */
#define NOT_RCU_APB1_PSC(ck_apb1)                              (((ck_apb1) != RCU_APB1_CKAHB_DIV1)  && ((ck_apb1) != RCU_APB1_CKAHB_DIV2) && \
                                                               ((ck_apb1) != RCU_APB1_CKAHB_DIV4)  && ((ck_apb1) != RCU_APB1_CKAHB_DIV8) && \
                                                               ((ck_apb1) != RCU_APB1_CKAHB_DIV16))
/* check APB2 clock prescaler parameter */
#define NOT_RCU_APB2_PSC(ck_apb2)                              (((ck_apb2) != RCU_APB2_CKAHB_DIV1)  && ((ck_apb2) != RCU_APB2_CKAHB_DIV2) && \
                                                               ((ck_apb2) != RCU_APB2_CKAHB_DIV4)  && ((ck_apb2) != RCU_APB2_CKAHB_DIV8) && \
                                                               ((ck_apb2) != RCU_APB2_CKAHB_DIV16))

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* check CK_OUT0 clock source */
#define NOT_RCU_CKOUT0SRC(ckout_src)                           (((ckout_src) != RCU_CKOUT0SRC_CORECK)       && ((ckout_src) != RCU_CKOUT0SRC_CKAPB1) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_IRC40K)       && ((ckout_src) != RCU_CKOUT0SRC_LXTAL) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_CKSYS)        && ((ckout_src) != RCU_CKOUT0SRC_IRC48M) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_HXTAL)        && ((ckout_src) != RCU_CKOUT0SRC_CKPLLP) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_CKPLLP_DIV2)  && ((ckout_src) != RCU_CKOUT0SRC_CKAPB2) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_HSMPCLK)      && ((ckout_src) != RCU_CKOUT0SRC_HSMHCLK) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_CKENETRX)     && ((ckout_src) != RCU_CKOUT0SRC_CKENETTX) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_CKENETMACRMI) && ((ckout_src) != RCU_CKOUT0SRC_CKENETTS))
/* check CK_OUT0 clock prescaler parameter */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A711X_A712X)
/* check CK_OUT0 clock source */
#define NOT_RCU_CKOUT0SRC(ckout_src)                           (((ckout_src) != RCU_CKOUT0SRC_CORECK)       && ((ckout_src) != RCU_CKOUT0SRC_CKAPB1) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_IRC40K)       && ((ckout_src) != RCU_CKOUT0SRC_LXTAL) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_CKSYS)        && ((ckout_src) != RCU_CKOUT0SRC_IRC48M) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_HXTAL)        && ((ckout_src) != RCU_CKOUT0SRC_CKPLLP) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_CKPLLP_DIV2)  && ((ckout_src) != RCU_CKOUT0SRC_CKAPB2) && \
                                                               ((ckout_src) != RCU_CKOUT0SRC_HSMPCLK)      && ((ckout_src) != RCU_CKOUT0SRC_HSMHCLK))
#endif /*defined(GD32A711X_A712X)*/

#define NOT_RCU_CKOUT0_DIV(ckout_div)                          (((ckout_div) != RCU_CKOUT0_DIV1)   && ((ckout_div) != RCU_CKOUT0_DIV2) && \
                                                               ((ckout_div) != RCU_CKOUT0_DIV4)   && ((ckout_div) != RCU_CKOUT0_DIV8) && \
                                                               ((ckout_div) != RCU_CKOUT0_DIV16)  && ((ckout_div) != RCU_CKOUT0_DIV32) && \
                                                               ((ckout_div) != RCU_CKOUT0_DIV64)  && ((ckout_div) != RCU_CKOUT0_DIV128))
/* check CK_OUT1 clock source */
#define NOT_RCU_CKOUT1SRC(ckout1_src)                          (((ckout1_src) != RCU_CKOUT1SRC_IRC40K) && ((ckout1_src) != RCU_CKOUT1SRC_LXTAL) && \
                                                               ((ckout1_src) != RCU_CKOUT1SRC_CKAPB2) && ((ckout1_src) != RCU_CKOUT1SRC_IRC48M) && \
                                                               ((ckout1_src) != RCU_CKOUT1SRC_HXTAL))
/* check CK_OUT1 clock prescaler parameter */
#define NOT_RCU_CKOUT1_DIV(ckout1_div)                         (((ckout1_div) != RCU_CKOUT1_DIV1)   && ((ckout1_div) != RCU_CKOUT1_DIV2) && \
                                                               ((ckout1_div) != RCU_CKOUT1_DIV4)   && ((ckout1_div) != RCU_CKOUT1_DIV8) && \
                                                               ((ckout1_div) != RCU_CKOUT1_DIV16)  && ((ckout1_div) != RCU_CKOUT1_DIV32) && \
                                                               ((ckout1_div) != RCU_CKOUT1_DIV64)  && ((ckout1_div) != RCU_CKOUT1_DIV128))
/* check the main PLL clock parameter */
#define NOT_RCU_PLLSRC(pll_src)                                (((pll_src) != RCU_PLLSRC_IRC48M) && ((pll_src) != RCU_PLLSRC_HXTAL))
/* check the main PLL prescaler range */
#define RCU_PLL_PREDV_MIN                                      1U
#define RCU_PLL_PREDV_MAX                                      7U
#define NOT_RCU_PLL_PREDV_RANGE(pll_predv)                     (((pll_predv) < RCU_PLL_PREDV_MIN) || ((pll_predv) > RCU_PLL_PREDV_MAX))
/* check the PLL VCO clock multi factor range */
#define RCU_PLL_N_MIN                                          16U
#define RCU_PLL_N_MAX                                          255U
#define NOT_RCU_PLL_N_RANGE(pll_n)                             (((pll_n) < RCU_PLL_N_MIN) || ((pll_n) > RCU_PLL_N_MAX))
/* check the PLL output frequency division factor range */
#define RCU_PLLDIV_MIN                                         1U
#define RCU_PLLDIV_MAX                                         64U
#define NOT_RCU_PLLDIV_RANGE(pll_plldiv)                      (((pll_plldiv) < RCU_PLLDIV_MIN) || ((pll_plldiv) > RCU_PLLDIV_MAX))
/* check ADC clock source */
#define NOT_RCU_ADCSRC(adc_src)                               (((adc_src) != RCU_ADCSRC_HCLK) && ((adc_src) != RCU_ADCSRC_SYS) && \
                                                              ((adc_src) != RCU_ADCSRC_PLLP))
/* check ADC prescaler factor */
#define NOT_RCU_CKADC_CKAHB_PSC(adc_psc)                      (((adc_psc) != RCU_CKADC_DIV2)  && ((adc_psc) != RCU_CKADC_DIV3) && \
                                                              ((adc_psc) != RCU_CKADC_DIV4)  && ((adc_psc) != RCU_CKADC_DIV5) && \
                                                              ((adc_psc) != RCU_CKADC_DIV6)  && ((adc_psc) != RCU_CKADC_DIV7) && \
                                                              ((adc_psc) != RCU_CKADC_DIV8)  && ((adc_psc) != RCU_CKADC_DIV9) && \
                                                              ((adc_psc) != RCU_CKADC_DIV10) && ((adc_psc) != RCU_CKADC_DIV11) && \
                                                              ((adc_psc) != RCU_CKADC_DIV12) && ((adc_psc) != RCU_CKADC_DIV13) && \
                                                              ((adc_psc) != RCU_CKADC_DIV14) && ((adc_psc) != RCU_CKADC_DIV15) && \
                                                              ((adc_psc) != RCU_CKADC_DIV16) && ((adc_psc) != RCU_CKADC_DIV17) && \
                                                              ((adc_psc) != RCU_CKADC_DIV18) && ((adc_psc) != RCU_CKADC_DIV19) && \
                                                              ((adc_psc) != RCU_CKADC_DIV20) && ((adc_psc) != RCU_CKADC_DIV21) && \
                                                              ((adc_psc) != RCU_CKADC_DIV22) && ((adc_psc) != RCU_CKADC_DIV23) && \
                                                              ((adc_psc) != RCU_CKADC_DIV24) && ((adc_psc) != RCU_CKADC_DIV25) && \
                                                              ((adc_psc) != RCU_CKADC_DIV26) && ((adc_psc) != RCU_CKADC_DIV27) && \
                                                              ((adc_psc) != RCU_CKADC_DIV28) && ((adc_psc) != RCU_CKADC_DIV29) && \
                                                              ((adc_psc) != RCU_CKADC_DIV30) && ((adc_psc) != RCU_CKADC_DIV31) && \
                                                              ((adc_psc) != RCU_CKADC_DIV32))
/* check the SPI clock source */
/* check SPI clock source */
/* check SPI clock source */
#define NOT_RCU_SPISRC(spi_src)                              (((spi_src) != RCU_SPISRC_APB1)                  && \
                                                             ((spi_src) != RCU_SPISRC_APB2)                  && \
                                                             ((spi_src) != RCU_SPISRC_IRC48M)                && \
                                                             ((spi_src) != RCU_SPISRC_AHB))
/* check the SPI clock divider range */
#define RCU_SPI_DIV_MIN                                      1U
#define RCU_SPI_DIV_MAX                                      64U
#define NOT_RCU_CKSPIDIV(spi_div)                            (((spi_div) < RCU_SPI_DIV_MIN) || ((spi_div) > RCU_SPI_DIV_MAX))
/* check RTC clock source */
#define NOT_RCU_RTCSRC(rtc_clock_source)                      (((rtc_clock_source) != RCU_RTCSRC_NONE)          && ((rtc_clock_source) != RCU_RTCSRC_LXTAL) && \
                                                              ((rtc_clock_source) != RCU_RTCSRC_IRC40K)        && ((rtc_clock_source) != RCU_RTCSRC_HXTAL_DIV_128))
/* check USART periph */
#define NOT_RCU_USART_PERIPH(usart_clock_source)              (((usart_clock_source) != USART0) && ((usart_clock_source) != USART1) && \
                                                              ((usart_clock_source) != USART2) && ((usart_clock_source) != USART3) && \
                                                              ((usart_clock_source) != USART4) && ((usart_clock_source) != USART5))
/* check USART clock source */
#define NOT_RCU_USARTSRC(usart_clock_source)                  (((usart_clock_source) != RCU_USARTSRC_IRC48M)  && ((usart_clock_source) != RCU_USARTSRC_LXTAL) && \
                                                              ((usart_clock_source) != RCU_USARTSRC_HCLK)    && ((usart_clock_source) != RCU_USARTSRC_PCLK1_2))

/* check DTM_CAN periph */
#define NOT_RCU_DTM_CAN_PERIPH(dtm_can_periph)                (((dtm_can_periph) != (uint32_t)DTM_CAN0) && ((dtm_can_periph) != (uint32_t)DTM_CAN1) && \
                                                              ((dtm_can_periph) != (uint32_t)DTM_CAN2) && ((dtm_can_periph) != (uint32_t)DTM_CAN3) && \
                                                              ((dtm_can_periph) != (uint32_t)DTM_CAN4) && ((dtm_can_periph) != (uint32_t)DTM_CAN5) && \
                                                              ((dtm_can_periph) != (uint32_t)DTM_CAN6) && ((dtm_can_periph) != (uint32_t)DTM_CAN7))

/* check the DTM_CAN clock source */
#define NOT_RCU_DTM_CANSRC(dtm_can_clock_source)                      (((dtm_can_clock_source) != RCU_DTM_CANSRC_HXTAL)       && ((dtm_can_clock_source) != RCU_DTM_CANSRC_AHB) && \
                                                              ((dtm_can_clock_source) != RCU_DTM_CANSRC_PCLK2 ) && ((dtm_can_clock_source) != RCU_DTM_CANSRC_IRC48M))

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* check WWDGT periph */
#define NOT_RCU_WWDGT_PERIPH(wwdgt_periph)                    (((wwdgt_periph) != WWDGT0) && ((wwdgt_periph) != WWDGT1))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A711X_A712X)
/* check WWDGT periph */
#define NOT_RCU_WWDGT_PERIPH(wwdgt_periph)                    (((wwdgt_periph) != WWDGT0))
#endif /*defined(GD32A711X_A712X)*/

/* check the WWDGT clock source */
#define NOT_RCU_WWDGTSRC(wwdgt_clock_source)                  (((wwdgt_clock_source) != RCU_WWDGTSRC_IRC48M) && ((wwdgt_clock_source) != RCU_WWDGTSRC_LXTAL) && \
                                                              ((wwdgt_clock_source) != RCU_WWDGTSRC_IRC40K) && ((wwdgt_clock_source) != RCU_WWDGTSRC_HXTAL) && \
                                                              ((wwdgt_clock_source) != RCU_WWDGTSRC_CKSYS)  && ((wwdgt_clock_source) != RCU_WWDGTSRC_PCLK1))

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* check FWDGT periph */
#define NOT_RCU_FWDGT_PERIPH(fwdgt_periph)                    (((fwdgt_periph) != FWDGT0) && ((fwdgt_periph) != FWDGT1))
/* check the FWDGT clock source */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A711X_A712X)
/* check FWDGT periph */
#define NOT_RCU_FWDGT_PERIPH(fwdgt_periph)                    (((fwdgt_periph) != FWDGT0))
/* check the FWDGT clock source */
#endif /*defined(GD32A711X_A712X)*/

#define NOT_RCU_FWDGTSRC(fwdgt_clock_source)                  (((fwdgt_clock_source) != RCU_FWDGTSRC_IRC40K) && ((fwdgt_clock_source) != RCU_FWDGTSRC_LXTAL))
/* check the LIN clock source */
/* check LINFlexD clock source */
#define NOT_RCU_LINFLEXDSRC(linflexd_clock_source)           (((linflexd_clock_source) != RCU_LINFLEXDSRC_CKSYS)    && \
                                                             ((linflexd_clock_source) != RCU_LINFLEXDSRC_PLL_P)    && \
                                                             ((linflexd_clock_source) != RCU_LINFLEXDSRC_HXTAL)    && \
                                                             ((linflexd_clock_source) != RCU_LINFLEXDSRC_IRC48M))
/* check the MFCOM clock prescaler */
#define NOT_RCU_CKMFCOM_CKAHB_DIV(mfcom_psc)                  (((mfcom_psc) != RCU_CKMFCOM_CKAHB_DIV1) && ((mfcom_psc) != RCU_CKMFCOM_CKAHB_DIV2) && \
                                                              ((mfcom_psc) != RCU_CKMFCOM_CKAHB_DIV4) && ((mfcom_psc) != RCU_CKMFCOM_CKAHB_DIV8))
/* check AIT clock source */
#define NOT_RCU_CKAITSRC(ait_clock_source)                    (((ait_clock_source) != RCU_CKAITSRC_IRC48M)      && ((ait_clock_source) != RCU_CKAITSRC_CK_PLL_Q_DIV2) && \
                                                              ((ait_clock_source) != RCU_CKAITSRC_CK_PLL_Q_DIV3) && ((ait_clock_source) != RCU_CKAITSRC_CK_PLL_Q_DIV4))
/* check ATE clock source */
#define NOT_RCU_CKATESRC(ate_clock_source)                    (((ate_clock_source) != RCU_CKATESRC_IRC48M)      && ((ate_clock_source) != RCU_CKATESRC_CK_PLL_Q_DIV2) && \
                                                              ((ate_clock_source) != RCU_CKATESRC_CK_PLL_Q_DIV3) && ((ate_clock_source) != RCU_CKATESRC_CK_PLL_Q_DIV4))
/* check TRACE clock source */
#define NOT_RCU_TRACESRC(trace_clock_source)                  (((trace_clock_source) != RCU_TRACESRC_PLLQ)   && ((trace_clock_source) != RCU_TRACESRC_PLLP) && \
                                                              ((trace_clock_source) != RCU_TRACESRC_HXTAL)   && ((trace_clock_source) != RCU_TRACESRC_IRC48M))
/* check the TRACE clock prescaler */
#define NOT_RCU_CKTRACE_DIV(trace_clock_psc)                  (((trace_clock_psc) != RCU_CKTRACE_DIV1) && ((trace_clock_psc) != RCU_CKTRACE_DIV2) && \
                                                              ((trace_clock_psc) != RCU_CKTRACE_DIV3) && ((trace_clock_psc) != RCU_CKTRACE_DIV4) && \
                                                              ((trace_clock_psc) != RCU_CKTRACE_DIV5) && ((trace_clock_psc) != RCU_CKTRACE_DIV6) && \
                                                              ((trace_clock_psc) != RCU_CKTRACE_DIV7) && ((trace_clock_psc) != RCU_CKTRACE_DIV8))
/* check QSPI clock source */
#define NOT_RCU_QSPISRC(qspi_clock_source)                    (((qspi_clock_source) != RCU_QSPISRC_PLLQ)   && ((qspi_clock_source) != RCU_QSPISRC_PLLP) && \
                                                              ((qspi_clock_source) != RCU_QSPISRC_HCLK)   && ((qspi_clock_source) != RCU_QSPISRC_IRC48M))
/* check ENET clock source */
#define NOT_RCU_ENETTSSRC(enet_clock_source)                  (((enet_clock_source) != RCU_ENETTSSRC_CK_ENETTX) && ((enet_clock_source) != RCU_ENETTSSRC_CK_ENETRX) && \
                                                              ((enet_clock_source) != RCU_ENETTSSRC_PLLP)      && ((enet_clock_source) != RCU_ENETTSSRC_HXTAL) && \
                                                              ((enet_clock_source) != RCU_ENETTSSRC_IRC48M))
/* check the LXTAL drive capability */
#define NOT_RCU_LXTAL_DRIVE(lxtal_dricap)                     (((lxtal_dricap) != RCU_LXTAL_LOWDRI)      && ((lxtal_dricap) != RCU_LXTAL_MED_LOWDRI) && \
                                                              ((lxtal_dricap) != RCU_LXTAL_MED_HIGHDRI) && ((lxtal_dricap) != RCU_LXTAL_HIGHDRI))
/* check HXTAL frequency scale */
#define NOT_HXTAL_SCALE(hxtal_scal)                           (((hxtal_scal) != HXTAL_SCALE_4M_TO_8M)   && ((hxtal_scal) != HXTAL_SCALE_8M_TO_16M) && \
                                                              ((hxtal_scal) != HXTAL_SCALE_16M_TO_32M) && ((hxtal_scal) != HXTAL_SCALE_32M_TO_40M))
/* check input of PLL clock perescaler */
#define NOT_RCU_PREDV_DIV(prediv)                             (((prediv) != RCU_PREDV_DIV1) && ((prediv) != RCU_PREDV_DIV2) && \
                                                              ((prediv) != RCU_PREDV_DIV3) && ((prediv) != RCU_PREDV_DIV4) && \
                                                              ((prediv) != RCU_PREDV_DIV5) && ((prediv) != RCU_PREDV_DIV6) && \
                                                              ((prediv) != RCU_PREDV_DIV7))
/* check the IRC48M adjust value */
#define RCU_IRC48M_ADJVAL_MAX                                 0x1FU
#define NOT_RCU_IRC48M_ADJVAL_RANGE(irc48m_adjval)            ((irc48m_adjval) > RCU_IRC48M_ADJVAL_MAX)

/* check the CKFM peripheral (interrupt)*/
#define NOT_RCU_CKFM_PERIPH(ckfmx)                           (((ckfmx) != CKFM0) && ((ckfmx) != CKFM1) && ((ckfmx) != CKFM2) && ((ckfmx) != CKFM3) && ((ckfmx) != CKFM4))

/* check the frequency monitor interrupt */
#define NOT_RCU_CKFMCTL_INT(interrupt)                        (((interrupt) != RCU_CKFMCTL_FLMINRE) && ((interrupt) != RCU_CKFMCTL_FHMAXRE))

/* check the CKFM peripheral (reset) */
#define NOT_RCU_CKFM_RST_PERIPH(ckfmx)                        (((ckfmx) != CKFM1) && ((ckfmx) != CKFM2))

/* check the CKFM peripheral (interrupt)*/
#define NOT_RCU_CKFM_INT_PERIPH(ckfmx)                        (((ckfmx) != CKFM0) && ((ckfmx) != CKFM3) && ((ckfmx) != CKFM4))

/* check the frequency monitor(0,3,4) interrupt */
#define NOT_RCU_CKFMCTL_INI(interrupt)                        (((interrupt) != RCU_CKFMCTL_FLMINIE) && ((interrupt) != RCU_CKFMCTL_FHMAXIE))

/* check the frequency monitor0 reset */
#define NOT_RCU_CKFMCTL_RST(reset)                            (((reset) != RCU_CKFMCTL_FHMAXRE) && ((reset) != RCU_CKFMCTL_FLMINRE))

/* check the frequency monitor(1,2) reset */
#define NOT_RCU_CKFMCTL_RST_1(reset)                          (((reset) != RCU_CKFMCTL_FLMINIE) && ((reset) != RCU_CKFMCTL_FHMAXIE))

/* check the clock frequency which to get*/
#define NOT_RCU_CK_FREQ(interrupt)                            (((interrupt) != CK_SYS)    && ((interrupt) != CK_AHB) && \
                                                              ((interrupt) != CK_APB1)   && ((interrupt) != CK_APB2) && \
                                                              ((interrupt) != CK_LINFLEXD))
/* check the system reset flag*/
#define NOT_RCU_SYS_RESET_FLAG(sysrst_flag)                   (((sysrst_flag) != RCU_FLAG_POR)           && ((sysrst_flag) != RCU_FLAG_FMU_REA_FAIL) && \
                                                              ((sysrst_flag) != RCU_FLAG_STCM_REC_FAIL) && ((sysrst_flag) != RCU_FLAG_RCTL_SUBSRU) && \
                                                              ((sysrst_flag) != RCU_FLAG_LOHRST)        && ((sysrst_flag) != RCU_FLAG_LOPRST) && \
                                                              ((sysrst_flag) != RCU_FLAG_CORE_CK_FAIL)  && ((sysrst_flag) != RCU_FLAG_SYS_CK_FAIL) && \
                                                              ((sysrst_flag) != RCU_FLAG_HSM_SYSRST)    && ((sysrst_flag) != RCU_FLAG_SW_SYSRST) && \
                                                              ((sysrst_flag) != RCU_FLAG_DBG_SYSRST))

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* check the subsystem reset flag*/
#define NOT_RCU_SUBSYS_RESET_FLAG(subsysrst_flag)             (((subsysrst_flag) != RCU_FLAG_EXTRST)   && \
                                                              ((subsysrst_flag) != RCU_FLAG_OBSTDBY)   && ((subsysrst_flag) != RCU_FLAG_FMU) && \
                                                              ((subsysrst_flag) != RCU_FLAG_ST_FINISH) && ((subsysrst_flag) != RCU_FLAG_FWDGT0) && \
                                                              ((subsysrst_flag) != RCU_FLAG_FWDGT1)    && ((subsysrst_flag) != RCU_FLAG_SWRST) && \
                                                              ((subsysrst_flag) != RCU_FLAG_WWDGT0)    && ((subsysrst_flag) != RCU_FLAG_WWDGT1) && \
                                                              ((subsysrst_flag) != RCU_FLAG_HSM_WDGT)  && ((subsysrst_flag) != RCU_FLAG_HSM_APP) && \
                                                              ((subsysrst_flag) != RCU_FLAG_SW_SUBS)   && ((subsysrst_flag) != RCU_FLAG_DBG) && \
                                                              ((subsysrst_flag) != RCU_FLAG_OBL))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A711X_A712X)
/* check the subsystem reset flag*/
#define NOT_RCU_SUBSYS_RESET_FLAG(subsysrst_flag)             (((subsysrst_flag) != RCU_FLAG_EXTRST)   && \
                                                              ((subsysrst_flag) != RCU_FLAG_OBSTDBY)   && ((subsysrst_flag) != RCU_FLAG_FMU) && \
                                                              ((subsysrst_flag) != RCU_FLAG_ST_FINISH) && ((subsysrst_flag) != RCU_FLAG_FWDGT0) && \
                                                              ((subsysrst_flag) != RCU_FLAG_WWDGT0)    && ((subsysrst_flag) != RCU_FLAG_SWRST) && \
                                                              ((subsysrst_flag) != RCU_FLAG_HSM_WDGT)  && ((subsysrst_flag) != RCU_FLAG_HSM_APP) && \
                                                              ((subsysrst_flag) != RCU_FLAG_SW_SUBS)   && ((subsysrst_flag) != RCU_FLAG_DBG) && \
                                                              ((subsysrst_flag) != RCU_FLAG_OBL))
#endif /*defined(GD32A711X_A712X)*/

/* check RCTL triple modular redundancy error output*/
#define NOT_RCU_TMRERRSTAT_TMR_EN(rctl_tmr)                   (((rctl_tmr) != RCU_TMRERRSTAT_TMR_RCU_SYSRSTSTATEN) && ((rctl_tmr) != RCU_TMRERRSTAT_TMR_RCU_SUBSRCTLEN) && \
                                                              ((rctl_tmr) != RCU_TMRERRSTAT_TMR_RCU_SUBSRPACTLEN) && ((rctl_tmr) != RCU_TMRERRSTAT_TMR_RCU_SYSMRETHEN) && \
                                                              ((rctl_tmr) != RCU_TMRERRSTAT_TMR_RCU_ERPACFGEN)    && ((rctl_tmr) != RCU_TMRERRSTAT_TMR_AHBRSTEN) && \
                                                              ((rctl_tmr) != RCU_TMRERRSTAT_TMR_APBRSTEN)         && ((rctl_tmr) != RCU_TMRERRSTAT_TMR_PORWDG1EN) && \
                                                              ((rctl_tmr) != RCU_TMRERRSTAT_TMR_PORWDG2EN)        && ((rctl_tmr) != RCU_TMRERRSTAT_TMR_PORWDG3EN) && \
                                                              ((rctl_tmr) != RCU_TMRERRSTAT_TMR_PORWDG4EN))
/* check CCTL triple modular redundancy error output*/
#define NOT_RCU_BUSIM_TMR_TMR_EN(cctl_tmr)                    (((cctl_tmr) != RCU_BUSIM_TMR_TMR_EN0) && ((cctl_tmr) != RCU_BUSIM_TMR_TMR_EN1) && \
                                                              ((cctl_tmr) != RCU_BUSIM_TMR_TMR_EN2) && ((cctl_tmr) != RCU_BUSIM_TMR_TMR_EN3))
/* check RCTL TMR flags*/
#define NOT_RCU_RCTL_TMR_FLAG(rctl_tmr_flag)                  (((rctl_tmr_flag) != RCU_FLAG_RCU_SYSRSTSTAT) && ((rctl_tmr_flag) != RCU_FLAG_RCU_SUBSRCTL) && \
                                                              ((rctl_tmr_flag) != RCU_FLAG_RCU_SUBSRPACTL) && ((rctl_tmr_flag) != RCU_FLAG_RCU_SYSMRETH) && \
                                                              ((rctl_tmr_flag) != RCU_FLAG_RCU_ERPACFG)    && ((rctl_tmr_flag) != RCU_FLAG_AHBRST) && \
                                                              ((rctl_tmr_flag) != RCU_FLAG_APBRST)         && ((rctl_tmr_flag) != RCU_FLAG_PORWDG1) && \
                                                              ((rctl_tmr_flag) != RCU_FLAG_PORWDG2)        && ((rctl_tmr_flag) != RCU_FLAG_PORWDG3) && \
                                                              ((rctl_tmr_flag) != RCU_FLAG_PORWDG4))

/* check CCTL TMR flags*/
#define NOT_RCU_CCTL_TMR_FLAG(cctl_tmr_flag)                  (((cctl_tmr_flag) != RCU_FLAG_ST0) && ((cctl_tmr_flag) != RCU_FLAG_ST1) && \
                                                              ((cctl_tmr_flag) != RCU_FLAG_ST2) && ((cctl_tmr_flag) != RCU_FLAG_ST3))
/* check PLL loss of lock accuracy*/
#define NOT_RCU_PLLLOL_UNLOCK_RANGE(lol_accuracy)             (((lol_accuracy) != RCU_PLLLOL_UNLOCK_RANGE_1) && ((lol_accuracy) != RCU_PLLLOL_UNLOCK_RANGE_2) && \
                                                              ((lol_accuracy) != RCU_PLLLOL_UNLOCK_RANGE_3) && ((lol_accuracy) != RCU_PLLLOL_UNLOCK_RANGE_4))
/* check PLL spread spectrum modulation type*/
#define NOT_RCU_SS_TYPE(spread_spectrum_type)                 (((spread_spectrum_type) != RCU_SS_TYPE_CENTER) && ((spread_spectrum_type) != RCU_SS_TYPE_DOWN))
/* check standby reset flag*/
#define NOT_RCU_STANDBY_RESET_FLAG(flag)                      (((flag) != RCU_FLAG_SYSRST)  && ((flag) != RCU_FLAG_SUBSRST))

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* check subsystem reset pin assertion*/
#define NOT_RCU_SUBSRPACTL_RPAEN(subsysrsrt)                  ((subsysrsrt) != RCU_SUBSRPACTL_ST_FINISH_RPAEN)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A711X_A712X)
/* check subsystem reset pin assertion*/
#define NOT_RCU_SUBSRPACTL_RPAEN(subsysrsrt)                  ((subsysrsrt) != RCU_SUBSRPACTL_ST_FINISH_RPAEN)
#endif /*defined(GD32A711X_A712X)*/

/* check control status */
#define NOT_CTL_STATUS(reset_pin_assert)                      (((reset_pin_assert) != ENABLE)  && ((reset_pin_assert) != DISABLE))

#endif /* FW_DEBUG_ERR_REPORT */


/* function declarations */
/* peripherals clock configure functions */
/* deinitialize the RCU */
void rcu_deinit(void);
/* enable the peripherals clock */
void rcu_periph_clock_enable(rcu_periph_enum periph);
/* disable the peripherals clock */
void rcu_periph_clock_disable(rcu_periph_enum periph);
/* reset the peripherals */
void rcu_periph_reset_enable(rcu_periph_reset_enum periph_reset);
/* disable reset the peripheral */
void rcu_periph_reset_disable(rcu_periph_reset_enum periph_reset);

/* system and peripherals clock source, system reset configure functions */
/* configure the system clock source */
void rcu_system_clock_source_config(uint32_t ck_sys);
/* get the system clock source */
uint32_t rcu_system_clock_source_get(void);
/* configure the AHB prescaler selection */
void rcu_ahb_clock_config(uint32_t ck_ahb);
/* configure the APB1 prescaler selection */
void rcu_apb1_clock_config(uint32_t ck_apb1);
/* configure the APB2 prescaler selection */
void rcu_apb2_clock_config(uint32_t ck_apb2);
/* configure the CK_OUT0 clock source and divider */
void rcu_ckout0_config(uint32_t ckout_src, uint32_t ckout_div);
/* configure the CK_OUT1 clock source and divider */
void rcu_ckout1_config(uint32_t ckout1_src, uint32_t ckout_div);
/* configure the PLL clock source selection and PLL multiply factor */
void rcu_pll_config(uint32_t pll_src, uint32_t pll_predv, uint32_t pll_n, uint32_t pll_pllpdiv, uint32_t pll_pllqdiv);
/* configure the ADC division factor and ADC clock source */
void rcu_adc_clock_config(uint32_t adc_src, uint32_t adc_psc);
/* configure the SPI division factor and SPI clock source */
void rcu_spi_clock_config(uint32_t spi_src, uint32_t spi_div);
/* configure the RTC clock source selection */
void rcu_rtc_clock_config(uint32_t rtc_clock_source);
/* configure the DTM_CAN clock source selection */
void rcu_dtm_can_clock_config(uint32_t dtm_can_periph, uint32_t dtm_can_clock_source);
/* configure the WWDGT clock source selection */
void rcu_wwdgt_clock_config(uint32_t wwdgt_periph, uint32_t wwdgt_clock_source);
/* configure the FWDGT clock source selection */
void rcu_fwdgt_clock_config(uint32_t fwdgt_periph, uint32_t fwdgt_clock_source);
/* configure the linflexd clock source selection */
void rcu_linflexd_clock_config(uint32_t linflexd_clock_source, uint32_t linflexddiv);

/* configure the AIT clock source selection */
void rcu_ait_clock_config(uint32_t ait_clock_source);
/* configure the ATE clock source selection */
void rcu_ate_clock_config(uint32_t ate_clock_source);
/* configure the TRACE clock source selection */
void rcu_trace_clock_source_config(uint32_t trace_clock_source, uint32_t trace_clock_psc);
/* configure the QSPI clock source selection */
void rcu_qspi_clock_source_config(uint32_t qspi_clock_source);

/* LXTAL, IRC48M, PLL and other oscillator configure functions */
/* configure the LXTAL drive capability */
void rcu_lxtal_drive_capability_config(uint32_t lxtal_dricap);
/* wait for oscillator stabilization flags is SET or oscillator startup is timeout */
ErrStatus rcu_osci_stab_wait(rcu_osci_type_enum osci);
/* turn on the oscillator */
void rcu_osci_on(rcu_osci_type_enum osci);
/* turn off the oscillator */
void rcu_osci_off(rcu_osci_type_enum osci);
/* enable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it */
void rcu_osci_bypass_mode_enable(rcu_osci_type_enum osci);
/* disable the oscillator bypass mode, HXTALEN or LXTALEN must be reset before it */
void rcu_osci_bypass_mode_disable(rcu_osci_type_enum osci);
/* configure the HXTAL frequency scale select */
void rcu_hxtal_frequency_scale_select(uint32_t hxtal_scal);
/* configure the HXTAL or IRC48M divider used as input of PLL */
void rcu_prediv_config(uint32_t prediv);
/* set the IRC48M adjust value */
void rcu_irc48m_adjust_value_set(uint32_t irc48m_adjval);
/* configure the IRC48M fail response */
void rcu_irc48m_fail_response_config(uint32_t irc48m_fail);

/* clock monitor configure functions */
/* enable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_enable(void);
/* disable the HXTAL clock monitor */
void rcu_hxtal_clock_monitor_disable(void);
/* frequency monitor enable */
void rcu_frequency_monitor_enable(uint32_t ckfmx);
/* frequency monitor disable */
void rcu_frequency_monitor_disable(uint32_t ckfmx);
/* frequency monitor0 system reset enable */
void rcu_frequency_monitor0_system_reset_enable(uint32_t sys_rst);
/* frequency monitor0 system reset disable */
void rcu_frequency_monitor0_system_reset_disable( uint32_t sys_rst);
/* frequency monitor system reset enable */
void rcu_frequency_monitor_system_reset_enable(uint32_t ckfmx, uint32_t interrupt);
/* frequency monitor system reset disable */
void rcu_frequency_monitor_system_reset_disable(uint32_t ckfmx, uint32_t interrupt);
/* frequency monitor interrupt enable */
void rcu_frequency_monitor_interrupt_enable(uint32_t ckfmx,uint32_t interrupt);
/* frequency monitor interrupt disable */
void rcu_frequency_monitor_interrupt_disable(uint32_t ckfmx,uint32_t interrupt);
/* get frequency monitor flag */
FlagStatus rcu_frequency_monitor_flag_get(uint32_t ckfmx,uint32_t interrupt_flag);
/* clear frequency monitor flag */
void rcu_frequency_monitor_flag_clear(uint32_t ckfmx,uint32_t interrupt_flag);
/* reference count configuration */
void rcu_reference_count_config(uint32_t ckfmx, uint32_t count);
/* high threshold configuration */
void rcu_monitored_hthreshold_config(uint32_t ckfmx, uint32_t hthreshold);
/* low threshold configuration */
void rcu_monitored_lthreshold_config(uint32_t ckfmx, uint32_t lthreshold);
/* frequency detect enable */
void rcu_frequency_detect_enable(ckd_enum ckdx);
/* frequency detect disable */
void rcu_frequency_detect_disable(ckd_enum ckdx);
/* frequency detect interrupt enable */
void rcu_frequency_detect_error_interrupt_enable(ckd_enum ckdx);
/* frequency detect interrupt disable */
void rcu_frequency_detect_error_interrupt_disable(ckd_enum ckdx);
/* clock frequency get functions */
/* get the system clock, bus and peripheral clock frequency */
uint32_t rcu_clock_freq_get(rcu_clock_freq_enum clock);


/* system/subsystem reset flag  */
/* clear the system reset flag */
void rcu_system_reset_flag_clear(uint32_t sysrst_flag);
/* clear the sub system reset flag */
void rcu_subsystem_reset_flag_clear(uint32_t subsysrst_flag);
/* get the system reset flag */
FlagStatus rcu_system_reset_flag_get(uint32_t sysrst_flag);
/* get the sub system reset flag */
FlagStatus rcu_subsystem_reset_flag_get(uint32_t subsysrst_flag);
/* get subsystem reset upgrade counter */
uint32_t rcu_subsystem_reset_upgrade_counter_get(void);
/* get system reset upgrade counter */
uint32_t rcu_system_reset_upgrade_counter_get(void);
/* get subsystem reset counter */
uint32_t rcu_subsystem_reset_counter_get(void);
/* get system reset counter*/
uint32_t rcu_system_reset_counter_get(void);
/* clear subsystem reset upgrade counter */
void rcu_subsystem_reset_upgrade_counter_clear(void);
/* clear subsystem reset counter */
void rcu_subsystem_reset_counter_clear(void);
/* clear system reset counter */
void rcu_system_reset_counter_clear(void);
/* config system reset upgrade threshold */
void rcu_system_reset_upgrade_threshold_config(uint32_t upgrade_threshold);
/* config subsystem reset upgrade threshold */
void rcu_subsystem_reset_upgrade_threshold_config(uint32_t upgrade_threshold);
/* enable bus access during SUBSRST1 stage */
void rcu_subsystem_reset_bus_access_enable(void);
/* disable bus access during SUBSRST1 stage */
void rcu_subsystem_reset_bus_access_disable(void);
/* enable external reset pin assert.NOTE: this API must use only as part of the mainreset domain self-test entry procedure */
void rcu_external_reset_pin_assert_enable(void);
/* disable external reset pin assert */
void rcu_external_reset_pin_assert_disable(void);
/* config subsystem reset timer value */
void rcu_subsystem_reset_timeout_config(uint32_t timeout);
/* enable subsystem reset entry timer */
void rcu_subsystem_reset_entry_timer_enable(void);
/* disable subsystem reset entry timer */
void rcu_subsystem_reset_entry_timer_disable(void);
/* enable subsystem reset request */
ErrStatus rcu_all_subsystem_reset_request_enable(void);
/* disable subsystem reset request */
ErrStatus rcu_all_subsystem_reset_request_disable(void);
/* get the standby reset flags */
FlagStatus rcu_standby_reset_flag_get(uint32_t flag);
/* clear the standby reset flags */
void rcu_standby_reset_flag_clear(uint32_t flag);
/* get the low power debug flag */
FlagStatus rcu_low_power_debug_flag_get(void);
/* get the por watchdog overflow flags */
FlagStatus rcu_por_watchdog_overflow_flag_get(por_watchdog_overflow_flag_enum flag);
/* clear the por watchdog overflow flags */
void rcu_por_watchdog_overflow_flag_clear(por_watchdog_overflow_flag_enum flag);

/* flag & interrupt functions */
/* get the clock stabilization and peripheral reset flags */
FlagStatus rcu_flag_get(rcu_flag_enum flag);
/* get the clock stabilization interrupt and ckm flags */
FlagStatus rcu_interrupt_flag_get(rcu_int_flag_enum int_flag);
/* clear the interrupt flags */
void rcu_interrupt_flag_clear(rcu_int_flag_clear_enum int_flag);
/* enable the stabilization interrupt */
void rcu_interrupt_enable(rcu_int_enum interrupt);
/* disable the stabilization interrupt */
void rcu_interrupt_disable(rcu_int_enum interrupt);

/*TMR function*/
/* enable the RCTL TMR */
void rcu_rctl_tmr_enable(uint32_t rctl_tmr);
/* disable the RCTL TMR */
void rcu_rctl_tmr_disable(uint32_t rctl_tmr);
/* enable the CCTL TMR */
void rcu_cctl_tmr_enable(uint32_t cctl_tmr);
/* disable the CCTL TMR */
void rcu_cctl_tmr_disable(uint32_t cctl_tmr);
/* get the RCTL TMR flag */
FlagStatus rcu_rctl_tmr_flag_get(uint32_t rctl_tmr_flag);
/* clear the RCTL TMR flag */
void rcu_rctl_tmr_flag_clear(uint32_t rctl_tmr_flag);
/* get the CCTL TMR flag */
FlagStatus rcu_cctl_tmr_flag_get(uint32_t cctl_tmr_flag);
/* clear the CCTL TMR flag */
void rcu_cctl_tmr_flag_clear(uint32_t cctl_tmr_flag);

/*PLL function*/
/* adjust the PLL loss of lock accuracy */
void rcu_pll_loss_of_lock_config(uint32_t lol_accuracy);
/* get the loss of lock detector flag */
FlagStatus rcu_pll_loss_of_lock_flag_get(void);
/* clear the loss of lock detector flag */
void rcu_pll_loss_of_lock_flag_clear(void);
/* config fractional part of the multiplication factor for PLL VCO */
void rcu_pll_fractional_config(uint32_t pll_fractional);
/* enable PLL fractional latch */
void rcu_pll_fractional_latch_enable(void);
/* disable PLL fractional latch */
void rcu_pll_fractional_latch_disable(void);
/* configure the spread spectrum modulation for the main PLL clock */
void rcu_spread_spectrum_config(uint32_t spread_spectrum_type, uint32_t modstep, uint32_t modcnt);
/* enable the PLL spread spectrum modulation */
void rcu_spread_spectrum_enable(void);
/* disable the PLL spread spectrum modulation */
void rcu_spread_spectrum_disable(void);
/* config subsystem reset */
void rcu_subsystem_reset_config(uint32_t subsysrsrt, ControlStatus reset_config);
/* config subsystem reset pin assertion */
void rcu_subsystem_reset_pin_assertion_config(uint32_t subsysrsrt, ControlStatus reset_pin_assert);
#endif /* GD32A7XX_RCU_H */
