/*!
   \file    gd32a7xx_syscfg.h
   \brief   definitions for the SYSCFG

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

#ifndef GD32A7XX_SYSCFG_H
#define GD32A7XX_SYSCFG_H

#include "gd32a7xx.h"

/* SYSCFG definitions */
#define SYSCFG                                       SYSCFG_BASE                        /*!< SYSCFG base address */

/* registers definitions */
#define SYSCFG_PMCFG                                 REG32(SYSCFG + 0x00000004U)        /*!< peripheral mode configuration register */
#define SYSCFG_EXTISS0                               REG32(SYSCFG + 0x00000008U)        /*!< EXTI sources selection register 0 */
#define SYSCFG_EXTISS1                               REG32(SYSCFG + 0x0000000CU)        /*!< EXTI sources selection register 1 */
#define SYSCFG_EXTISS2                               REG32(SYSCFG + 0x00000010U)        /*!< EXTI sources selection register 2 */
#define SYSCFG_EXTISS3                               REG32(SYSCFG + 0x00000014U)        /*!< EXTI sources selection register 3 */
#define SYSCFG_STAT                                  REG32(SYSCFG + 0x00000020U)        /*!< system status register */
#define SYSCFG_CFG                                   REG32(SYSCFG + 0x00000024U)        /*!< system configuration register */
#define SYSCFG_TIMERBKINSEL                          REG32(SYSCFG + 0x0000002CU)        /*!< TIMER break input select register */
#define SYSCFG_CPU0ICAC                              REG32(SYSCFG + 0x00000030U)        /*!< CPU0 ICACHE error status register */
#define SYSCFG_CPU0DCAC                              REG32(SYSCFG + 0x00000034U)        /*!< CPU0 DCACHE error status register */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define SYSCFG_CPU1ICAC                              REG32(SYSCFG + 0x00000038U)        /*!< CPU1 ICACHE error status register */
#define SYSCFG_CPU1DCAC                              REG32(SYSCFG + 0x0000003CU)        /*!< CPU1 DCACHE error status register */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define SYSCFG_CPUCTL                                REG32(SYSCFG + 0x00000050U)        /*!< CPU control register */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define SYSCFG_CPUSTAT                               REG32(SYSCFG + 0x00000054U)        /*!< CPU platform status register */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define SYSCFG_CPU0CS                                REG32(SYSCFG + 0x00000058U)        /*!< CPU0 interrupt status and control register */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define SYSCFG_CPU1CS                                REG32(SYSCFG + 0x0000005CU)        /*!< CPU1 interrupt status and control register */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define SYSCFG_SRAMCFG                               REG32(SYSCFG + 0x00000068U)        /*!< SRAM configuration register */
#define SYSCFG_RMCFG                                 REG32(SYSCFG + 0x0000006CU)        /*!< recovery mode configuration register */
#define SYSCFG_HSMSTAT                               REG32(SYSCFG + 0x00000070U)        /*!< HSM sub system status register */
#define SYSCFG_TIMER0CFG0                            REG32(SYSCFG + 0x00000100U)        /*!< TIMER0 configuration register */
#define SYSCFG_TIMER0CFG1                            REG32(SYSCFG + 0x00000104U)        /*!< TIMER0 configuration register */
#define SYSCFG_TIMER0CFG2                            REG32(SYSCFG + 0x00000108U)        /*!< TIMER0 configuration register */
#define SYSCFG_TIMER1CFG0                            REG32(SYSCFG + 0x0000010CU)        /*!< TIMER1 configuration register */
#define SYSCFG_TIMER1CFG1                            REG32(SYSCFG + 0x00000110U)        /*!< TIMER1 configuration register */
#define SYSCFG_TIMER1CFG2                            REG32(SYSCFG + 0x00000114U)        /*!< TIMER1 configuration register */
#define SYSCFG_TIMER2CFG0                            REG32(SYSCFG + 0x00000118U)        /*!< TIMER2 configuration register */
#define SYSCFG_TIMER2CFG1                            REG32(SYSCFG + 0x0000011CU)        /*!< TIMER2 configuration register */
#define SYSCFG_TIMER2CFG2                            REG32(SYSCFG + 0x00000120U)        /*!< TIMER2 configuration register */
#define SYSCFG_TIMER7CFG0                            REG32(SYSCFG + 0x00000124U)        /*!< TIMER7 configuration register */
#define SYSCFG_TIMER7CFG1                            REG32(SYSCFG + 0x00000128U)        /*!< TIMER7 configuration register */
#define SYSCFG_TIMER7CFG2                            REG32(SYSCFG + 0x0000012CU)        /*!< TIMER7 configuration register */
#define SYSCFG_TIMER19CFG0                           REG32(SYSCFG + 0x00000130U)        /*!< TIMER19 configuration register */
#define SYSCFG_TIMER19CFG1                           REG32(SYSCFG + 0x00000134U)        /*!< TIMER19 configuration register */
#define SYSCFG_TIMER19CFG2                           REG32(SYSCFG + 0x00000138U)        /*!< TIMER19 configuration register */
#define SYSCFG_TIMER20CFG0                           REG32(SYSCFG + 0x0000013CU)        /*!< TIMER20 configuration register */
#define SYSCFG_TIMER20CFG1                           REG32(SYSCFG + 0x00000140U)        /*!< TIMER20 configuration register */
#define SYSCFG_TIMER20CFG2                           REG32(SYSCFG + 0x00000144U)        /*!< TIMER20 configuration register */
#define SYSCFG_TIMER60CFG0                           REG32(SYSCFG + 0x00000148U)        /*!< TIMER60 configuration register */
#define SYSCFG_TIMER60CFG1                           REG32(SYSCFG + 0x0000014CU)        /*!< TIMER60 configuration register */
#define SYSCFG_TIMER60CFG2                           REG32(SYSCFG + 0x00000150U)        /*!< TIMER60 configuration register */
#define SYSCFG_TIMER61CFG0                           REG32(SYSCFG + 0x00000154U)        /*!< TIMER61 configuration register */
#define SYSCFG_TIMER61CFG1                           REG32(SYSCFG + 0x00000158U)        /*!< TIMER61 configuration register */
#define SYSCFG_TIMER61CFG2                           REG32(SYSCFG + 0x0000015CU)        /*!< TIMER61 configuration register */
#define SYSCFG_TIMER62CFG0                           REG32(SYSCFG + 0x00000160U)        /*!< TIMER62 configuration register */
#define SYSCFG_TIMER62CFG1                           REG32(SYSCFG + 0x00000164U)        /*!< TIMER62 configuration register */
#define SYSCFG_TIMER62CFG2                           REG32(SYSCFG + 0x00000168U)        /*!< TIMER62 configuration register */
#define SYSCFG_TIMER63CFG0                           REG32(SYSCFG + 0x0000016CU)        /*!< TIMER63 configuration register */
#define SYSCFG_TIMER63CFG1                           REG32(SYSCFG + 0x00000170U)        /*!< TIMER63 configuration register */
#define SYSCFG_TIMER63CFG2                           REG32(SYSCFG + 0x00000174U)        /*!< TIMER63 configuration register */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define SYSCFG_CPID                                  REG32(SYSCFG + 0x00000220U)        /*!< core processor ID register */
#define SYSCFG_CPNUM                                 REG32(SYSCFG + 0x00000224U)        /*!< core porcessor number register */
#define SYSCFG_CPCFGINF0                             REG32(SYSCFG + 0x0000022CU)        /*!< core processor configuration information register 0 */
#define SYSCFG_CPCFGINF1                             REG32(SYSCFG + 0x00000234U)        /*!< core processor configuration information register 1 */
#define SYSCFG_CPCFGINF2                             REG32(SYSCFG + 0x00000238U)        /*!< core processor configuration information register 2 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define SYSCFG_CP0ID                                 REG32(SYSCFG + 0x00000240U)        /*!< core processor 0 ID register */
#define SYSCFG_CP0NUM                                REG32(SYSCFG + 0x00000244U)        /*!< core processor 0 number register */
#define SYSCFG_CP0CFGINF0                            REG32(SYSCFG + 0x0000024CU)        /*!< core processor 0 configuration information register 0 */
#define SYSCFG_CP0CFGINF1                            REG32(SYSCFG + 0x00000254U)        /*!< core processor 0 configuration information register 1 */
#define SYSCFG_CP0CFGINF2                            REG32(SYSCFG + 0x00000258U)        /*!< core processor 0 configuration information register 2 */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define SYSCFG_CP1ID                                 REG32(SYSCFG + 0x00000260U)        /*!< core processor 1 ID register */
#define SYSCFG_CP1NUM                                REG32(SYSCFG + 0x00000264U)        /*!< core processor 1 number register */
#define SYSCFG_CP1CFGINF0                            REG32(SYSCFG + 0x0000026CU)        /*!< core processor 1 configuration information register 0 */
#define SYSCFG_CP1CFGINF1                            REG32(SYSCFG + 0x00000274U)        /*!< core processor 1 configuration information register 1 */
#define SYSCFG_CP1CFGINF2                            REG32(SYSCFG + 0x00000278U)        /*!< core processor 1 configuration information register 2 */
#define SYSCFG_IRCP0INTSTAT0                         REG32(SYSCFG + 0x00000300U)        /*!< interrupt router core processor 0 interrupt status register 0 */
#define SYSCFG_IRCP0INTSTAT1                         REG32(SYSCFG + 0x00000308U)        /*!< interrupt router core processor 0 interrupt status register 1 */
#define SYSCFG_IRCP0INTSTAT2                         REG32(SYSCFG + 0x00000310U)        /*!< interrupt router core processor 0 interrupt status register 2 */
#define SYSCFG_IRCP0INTSTAT3                         REG32(SYSCFG + 0x00000318U)        /*!< interrupt router core processor 0 interrupt status register 3 */
#define SYSCFG_IRCP1INTSTAT0                         REG32(SYSCFG + 0x00000320U)        /*!< interrupt router core processor 1 interrupt status register 0 */
#define SYSCFG_IRCP1INTSTAT1                         REG32(SYSCFG + 0x00000328U)        /*!< interrupt router core processor 1 interrupt status register 1 */
#define SYSCFG_IRCP1INTSTAT2                         REG32(SYSCFG + 0x00000330U)        /*!< interrupt router core processor 1 interrupt status register 2 */
#define SYSCFG_IRCP1INTSTAT3                         REG32(SYSCFG + 0x00000338U)        /*!< interrupt router core processor 1 interrupt status register 3 */
#define SYSCFG_IRCP0INT0                             REG32(SYSCFG + 0x00000304U)        /*!< interrupt router core processor 0 interrupt generation register 0 */
#define SYSCFG_IRCP0INT1                             REG32(SYSCFG + 0x0000030CU)        /*!< interrupt router core processor 0 interrupt generation register 1 */
#define SYSCFG_IRCP0INT2                             REG32(SYSCFG + 0x00000314U)        /*!< interrupt router core processor 0 interrupt generation register 2 */
#define SYSCFG_IRCP0INT3                             REG32(SYSCFG + 0x0000031CU)        /*!< interrupt router core processor 0 interrupt generation register 3 */
#define SYSCFG_IRCP1INT0                             REG32(SYSCFG + 0x00000324U)        /*!< interrupt router core processor 1 interrupt generation register 0 */
#define SYSCFG_IRCP1INT1                             REG32(SYSCFG + 0x0000032CU)        /*!< interrupt router core processor 1 interrupt generation register 1 */
#define SYSCFG_IRCP1INT2                             REG32(SYSCFG + 0x00000334U)        /*!< interrupt router core processor 1 interrupt generation register 2 */
#define SYSCFG_IRCP1INT3                             REG32(SYSCFG + 0x0000033CU)        /*!< interrupt router core processor 1 interrupt generation register 3 */
#define SYSCFG_IRCPUCTL                              REG32(SYSCFG + 0x00000340U)        /*!< interrupt router core processor control register */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define SYSCFG_MEMAEXCTL                             REG32(SYSCFG + 0x00000350U)        /*!< memory access execution control register */
#define SYSCFG_BM1EDCEN                              REG32(SYSCFG + 0x00000360U)        /*!< bus matrix1 interconnect error detection enable register */
#define SYSCFG_BM2EDCEN                              REG32(SYSCFG + 0x00000364U)        /*!< bus matrix2 interconnect error detection enable register */
#define SYSCFG_BUSCHKCFG                             REG32(SYSCFG + 0x00000368U)        /*!< bus check configuration register */
#define SYSCFG_TMRFCS                                REG32(SYSCFG + 0x00000370U)        /*!< TMR fault status and control register */

/* bits definitions */
/* SYSCFG_PMCFG */
#define SYSCFG_PMCFG_I2C0FMPEN                       BIT(0)                             /*!< I2C0 fast mode plus enable */
#define SYSCFG_PMCFG_I2C1FMPEN                       BIT(1)                             /*!< I2C1 fast mode plus enable */

/* SYSCFG_EXTISS0 */
#define SYSCFG_EXTISS0_EXTI0_SS                      BITS(0,3)                          /*!< EXTI 0 sources selection */
#define SYSCFG_EXTISS0_EXTI1_SS                      BITS(4,7)                          /*!< EXTI 1 sources selection */
#define SYSCFG_EXTISS0_EXTI2_SS                      BITS(8,11)                         /*!< EXTI 2 sources selection */
#define SYSCFG_EXTISS0_EXTI3_SS                      BITS(12,15)                        /*!< EXTI 3 sources selection */

/* SYSCFG_EXTISS1 */
#define SYSCFG_EXTISS1_EXTI4_SS                      BITS(0,3)                          /*!< EXTI 4 sources selection */
#define SYSCFG_EXTISS1_EXTI5_SS                      BITS(4,7)                          /*!< EXTI 5 sources selection */
#define SYSCFG_EXTISS1_EXTI6_SS                      BITS(8,11)                         /*!< EXTI 6 sources selection */
#define SYSCFG_EXTISS1_EXTI7_SS                      BITS(12,15)                        /*!< EXTI 7 sources selection */

/* SYSCFG_EXTISS2 */
#define SYSCFG_EXTISS2_EXTI8_SS                      BITS(0,3)                          /*!< EXTI 8 sources selection */
#define SYSCFG_EXTISS2_EXTI9_SS                      BITS(4,7)                          /*!< EXTI 9 sources selection */
#define SYSCFG_EXTISS2_EXTI10_SS                     BITS(8,11)                         /*!< EXTI 10 sources selection */
#define SYSCFG_EXTISS2_EXTI11_SS                     BITS(12,15)                        /*!< EXTI 11 sources selection */

/* SYSCFG_EXTISS3 */
#define SYSCFG_EXTISS3_EXTI12_SS                     BITS(0,3)                          /*!< EXTI 12 sources selection */
#define SYSCFG_EXTISS3_EXTI13_SS                     BITS(4,7)                          /*!< EXTI 13 sources selection */
#define SYSCFG_EXTISS3_EXTI14_SS                     BITS(8,11)                         /*!< EXTI 14 sources selection */
#define SYSCFG_EXTISS3_EXTI15_SS                     BITS(12,15)                        /*!< EXTI 15 sources selection */

/* SYSCFG_STAT */
#define SYSCFG_STAT_CKMNMIIF                         BIT(3)                             /*!< HXTAL clock moniotor NMI interrupt flag */
#define SYSCFG_STAT_NMIPINIF                         BIT(4)                             /*!< NMI interrupt flag from EXTI pin */
#define SYSCFG_STAT_FMUNMIIF                         BIT(5)                             /*!< NMI interrupt flag from FMU */

/* SYSCFG_CFG */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define SYSCFG_CFG_CM7_1_TXEVEN                      BIT(0)                             /*!< enable bit of EVENTOUT from CM7_1 */
#define SYSCFG_CFG_CKMNMIIE1                         BIT(3)                             /*!< enable bit of HXTAL clock moniotor NMI interrupt flag connection to CPU1 NMI interrupt */
#define SYSCFG_CFG_NMIPINIE1                         BIT(4)                             /*!< enable bit of NMI interrupt flag from EXTI pin connection to CPU1 NMI interrupt */
#define SYSCFG_CFG_FMUNMIIE1                         BIT(5)                             /*!< enable bit of NMI interrupt flag from FMU connection to CPU1 NMI interrupt */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define SYSCFG_CFG_CM7_0_TXEVEN                      BIT(16)                            /*!< enable bit of EVENTOUT from CM7_0 */
#define SYSCFG_CFG_CKMNMIIE0                         BIT(19)                            /*!< enable bit of HXTAL clock moniotor NMI interrupt flag connection to CPU0 NMI interrupt */
#define SYSCFG_CFG_NMIPINIE0                         BIT(20)                            /*!< enable bit of NMI interrupt flag from EXTI pin connection to CPU0 NMI interrupt */
#define SYSCFG_CFG_FMUNMIIE0                         BIT(21)                            /*!< enable bit of NMI interrupt flag from FMU connection to CPU0 NMI interrupt */
#define SYSCFG_CFG_CM23_TXEVEN                       BIT(24)                            /*!< enable bit of EVENTOUT from CM23(HSM) */

/* SYSCFG_TIMERBKINSEL */
#define SYSCFG_TIMERBKINSEL_TIMER64_BRKIN3_SEL       BIT(0)                             /*!< TIMER64 break input 3 selection */
#define SYSCFG_TIMERBKINSEL_TIMER64_BRKIN2_SEL       BIT(1)                             /*!< TIMER64 break input 2 selection */
#define SYSCFG_TIMERBKINSEL_TIMER64_BRKIN1_SEL       BIT(2)                             /*!< TIMER64 break input 1 selection */
#define SYSCFG_TIMERBKINSEL_TIMER64_BRKIN0_SEL       BIT(3)                             /*!< TIMER64 break input 0 selection */
#define SYSCFG_TIMERBKINSEL_TIMER63_BRKIN3_SEL       BIT(4)                             /*!< TIMER63 break input 3 selection */
#define SYSCFG_TIMERBKINSEL_TIMER63_BRKIN2_SEL       BIT(5)                             /*!< TIMER63 break input 2 selection */
#define SYSCFG_TIMERBKINSEL_TIMER63_BRKIN1_SEL       BIT(6)                             /*!< TIMER63 break input 1 selection */
#define SYSCFG_TIMERBKINSEL_TIMER63_BRKIN0_SEL       BIT(7)                             /*!< TIMER63 break input 0 selection */
#define SYSCFG_TIMERBKINSEL_TIMER62_BRKIN3_SEL       BIT(8)                             /*!< TIMER62 break input 3 selection */
#define SYSCFG_TIMERBKINSEL_TIMER62_BRKIN2_SEL       BIT(9)                             /*!< TIMER62 break input 2 selection */
#define SYSCFG_TIMERBKINSEL_TIMER62_BRKIN1_SEL       BIT(10)                            /*!< TIMER62 break input 1 selection */
#define SYSCFG_TIMERBKINSEL_TIMER62_BRKIN0_SEL       BIT(11)                            /*!< TIMER62 break input 0 selection */
#define SYSCFG_TIMERBKINSEL_TIMER61_BRKIN3_SEL       BIT(12)                            /*!< TIMER61 break input 3 selection */
#define SYSCFG_TIMERBKINSEL_TIMER61_BRKIN2_SEL       BIT(13)                            /*!< TIMER61 break input 2 selection */
#define SYSCFG_TIMERBKINSEL_TIMER61_BRKIN1_SEL       BIT(14)                            /*!< TIMER61 break input 1 selection */
#define SYSCFG_TIMERBKINSEL_TIMER61_BRKIN0_SEL       BIT(15)                            /*!< TIMER61 break input 0 selection */
#define SYSCFG_TIMERBKINSEL_TIMER21_BRKIN3_SEL       BIT(16)                            /*!< TIMER21 break input 3 selection */
#define SYSCFG_TIMERBKINSEL_TIMER21_BRKIN2_SEL       BIT(17)                            /*!< TIMER21 break input 2 selection */
#define SYSCFG_TIMERBKINSEL_TIMER21_BRKIN1_SEL       BIT(18)                            /*!< TIMER21 break input 1 selection */
#define SYSCFG_TIMERBKINSEL_TIMER21_BRKIN0_SEL       BIT(19)                            /*!< TIMER21 break input 0 selection */
#define SYSCFG_TIMERBKINSEL_TIMER20_BRKIN3_SEL       BIT(20)                            /*!< TIMER20 break input 3 selection */
#define SYSCFG_TIMERBKINSEL_TIMER20_BRKIN2_SEL       BIT(21)                            /*!< TIMER20 break input 2 selection */
#define SYSCFG_TIMERBKINSEL_TIMER20_BRKIN1_SEL       BIT(22)                            /*!< TIMER20 break input 1 selection */
#define SYSCFG_TIMERBKINSEL_TIMER20_BRKIN0_SEL       BIT(23)                            /*!< TIMER20 break input 0 selection */
#define SYSCFG_TIMERBKINSEL_TIMER8_BRKIN3_SEL        BIT(24)                            /*!< TIMER8 break input 3 selection */
#define SYSCFG_TIMERBKINSEL_TIMER8_BRKIN2_SEL        BIT(25)                            /*!< TIMER8 break input 2 selection */
#define SYSCFG_TIMERBKINSEL_TIMER8_BRKIN1_SEL        BIT(26)                            /*!< TIMER8 break input 1 selection */
#define SYSCFG_TIMERBKINSEL_TIMER8_BRKIN0_SEL        BIT(27)                            /*!< TIMER8 break input 0 selection */
#define SYSCFG_TIMERBKINSEL_TIMER1_BRKIN3_SEL        BIT(28)                            /*!< TIMER1 break input 3 selection */
#define SYSCFG_TIMERBKINSEL_TIMER1_BRKIN2_SEL        BIT(29)                            /*!< TIMER1 break input 2 selection */
#define SYSCFG_TIMERBKINSEL_TIMER1_BRKIN1_SEL        BIT(30)                            /*!< TIMER1 break input 1 selection */
#define SYSCFG_TIMERBKINSEL_TIMER1_BRKIN0_SEL        BIT(31)                            /*!< TIMER1 break input 0 selection */

/* SYSCFG_CPU0ICAC */
#define SYSCFG_CPU0ICAC_CPU0_ICERR                   BITS(6,27)                         /*!< CPU0 ICACHE error bank information */
#define SYSCFG_CPU0ICAC_CPU0_ICDET                   BITS(28,31)                        /*!< CPU0 ICACHE error detection information */

/* SYSCFG_CPU0DCAC */
#define SYSCFG_CPU0DCAC_CPU0_DCERR                   BITS(6,27)                         /*!< CPU0 DCACHE error bank information */
#define SYSCFG_CPU0DCAC_CPU0_DCDET                   BITS(28,31)                        /*!< CPU0 DCACHE error detection information */

#if defined (GD32A72XX) || defined (GD32A74XX)
/* SYSCFG_CPU1ICAC */
#define SYSCFG_CPU1ICAC_CPU1_ICERR                   BITS(6,27)                         /*!< CPU1 ICACHE error bank information */
#define SYSCFG_CPU1ICAC_CPU1_ICDET                   BITS(28,31)                        /*!< CPU1 ICACHE error detection information */

/* SYSCFG_CPU1DCAC */
#define SYSCFG_CPU1DCAC_CPU1_DCERR                   BITS(6,27)                         /*!< CPU1 DCACHE error bank information */
#define SYSCFG_CPU1DCAC_CPU1_DCDET                   BITS(28,31)                        /*!< CPU1 DCACHE error detection information */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A72XX) || defined (GD32A74XX)
/* SYSCFG_CPUCTL */
#define SYSCFG_CPUCTL_CPU1_HOLD                      BIT(3)                             /*!< CPU1 hold bit */
#define SYSCFG_CPUCTL_CPU1_AHBSPRI                   BIT(11)                            /*!< CPU1 AHB slave priority bit */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define SYSCFG_CPUCTL_CPU0_HOLD                      BIT(19)                            /*!< CPU0 hold bit */
#define SYSCFG_CPUCTL_CPU0_AHBSPRI                   BIT(27)                            /*!< CPU0 AHB slave priority bit */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* SYSCFG_CPUSTAT */
#define SYSCFG_CPUSTAT_CPUSTAT                       BITS(0,1)                          /*!< CPU information for the chip */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* SYSCFG_CPU0CS */
#define SYSCFG_CPU0CS_WAS                            BIT(5)                             /*!< CPU0 write abort on AHB slave */
#define SYSCFG_CPU0CS_WASOVF                         BIT(6)                             /*!< CPU0 write abort on AHB slave overrun flag */
#define SYSCFG_CPU0CS_FIOPIF                         BIT(10)                            /*!< CPU0 FPU invalid operation interrupt status flag */
#define SYSCFG_CPU0CS_FDZIF                          BIT(11)                            /*!< CPU0 FPU divide-by-zero interrupt status flag */
#define SYSCFG_CPU0CS_FUFIF                          BIT(12)                            /*!< CPU0 FPU underflow interrupt status flag */
#define SYSCFG_CPU0CS_FOVFIF                         BIT(13)                            /*!< CPU0 FPU overflow interrupt status flag */
#define SYSCFG_CPU0CS_FIDIF                          BIT(14)                            /*!< CPU0 FPU input denormal interrupt status flag */
#define SYSCFG_CPU0CS_FIXIF                          BIT(15)                            /*!< CPU0 FPU inexact operation interrupt status flag */
#define SYSCFG_CPU0CS_WAIE                           BIT(21)                            /*!< CPU0 TCM write abort interrupt enable */
#define SYSCFG_CPU0CS_FIOPIE                         BIT(26)                            /*!< CPU0 FPU invalid operation interrupt enable */
#define SYSCFG_CPU0CS_FDZIE                          BIT(27)                            /*!< CPU0 FPU divide-by-zero interrupt enable */
#define SYSCFG_CPU0CS_FUFIE                          BIT(28)                            /*!< CPU0 FPU underflow interrupt enable */
#define SYSCFG_CPU0CS_FOVFIE                         BIT(29)                            /*!< CPU0 FPU overflow interrupt enable */
#define SYSCFG_CPU0CS_FIDIE                          BIT(30)                            /*!< CPU0 FPU input denormal interrupt enable */
#define SYSCFG_CPU0CS_FIXIE                          BIT(31)                            /*!< CPU0 FPU inexact operation interrupt enable */

#if defined (GD32A72XX) || defined (GD32A74XX)
/* SYSCFG_CPU1CS */
#define SYSCFG_CPU1CS_WAS                            BIT(5)                             /*!< CPU1 write abort on AHB slave */
#define SYSCFG_CPU1CS_WASOVF                         BIT(6)                             /*!< CPU1 write abort on AHB slave overrun flag */
#define SYSCFG_CPU1CS_FIOPIF                         BIT(10)                            /*!< CPU1 FPU invalid operation interrupt status flag */
#define SYSCFG_CPU1CS_FDZIF                          BIT(11)                            /*!< CPU1 FPU divide-by-zero interrupt status flag */
#define SYSCFG_CPU1CS_FUFIF                          BIT(12)                            /*!< CPU1 FPU underflow interrupt status flag */
#define SYSCFG_CPU1CS_FOVFIF                         BIT(13)                            /*!< CPU1 FPU overflow interrupt status flag */
#define SYSCFG_CPU1CS_FIDIF                          BIT(14)                            /*!< CPU1 FPU input denormal interrupt status flag */
#define SYSCFG_CPU1CS_FIXIF                          BIT(15)                            /*!< CPU1 FPU inexact operation interrupt status flag */
#define SYSCFG_CPU1CS_WAIE                           BIT(21)                            /*!< CPU1 TCM write abort interrupt enable */
#define SYSCFG_CPU1CS_FIOPIE                         BIT(26)                            /*!< CPU1 FPU invalid operation interrupt enable */
#define SYSCFG_CPU1CS_FDZIE                          BIT(27)                            /*!< CPU1 FPU divide-by-zero interrupt enable */
#define SYSCFG_CPU1CS_FUFIE                          BIT(28)                            /*!< CPU1 FPU underflow interrupt enable */
#define SYSCFG_CPU1CS_FOVFIE                         BIT(29)                            /*!< CPU1 FPU overflow interrupt enable */
#define SYSCFG_CPU1CS_FIDIE                          BIT(30)                            /*!< CPU1 FPU input denormal interrupt enable */
#define SYSCFG_CPU1CS_FIXIE                          BIT(31)                            /*!< CPU1 FPU inexact operation interrupt enable */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* SYSCFG_SRAMCFG */
#define SYSCFG_SRAMCFG_TCM_WAITSTATE                 BIT(0)                             /*!< TCM(ITCM/D0TCM/D1TCM) wait-state insert bit */
#define SYSCFG_SRAMCFG_SRAM_WAITSTATE                BIT(1)                             /*!< SRAM wait-state insert bit */

/* SYSCFG_RMCFG */
#define SYSCFG_RMCFG_RM_SUBSRST_DIS                  BIT(0)                             /*!< disable recovery mode on subsystem reset */
#define SYSCFG_RMCFG_RM_SYSRST_DIS                   BIT(1)                             /*!< disable recovery mode on system reset */

/* SYSCFG_HSMSTAT */
#define SYSCFG_HSMSTAT_HSM_ENTER_STDBY               BIT(0)                             /*!< indicates that the HSM sub system has entered standby separately */

/* Timer configuration selection register*/
#define SYSCFG_TIMERCFG_TSCFG0                       BITS(0,4)                          /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG1                       BITS(5,9)                          /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG2                       BITS(10,14)                        /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG3                       BITS(16,20)                        /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG4                       BITS(21,25)                        /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG5                       BITS(26,30)                        /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG6                       BITS(0,4)                          /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG7                       BITS(5,9)                          /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG8                       BITS(10,14)                        /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG9                       BITS(16,20)                        /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG10                      BITS(21,25)                        /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG11                      BITS(26,30)                        /*!< TIMER configuration selection */
#define SYSCFG_TIMERCFG_TSCFG15                      BITS(16,20)                        /*!< TIMER configuration selection */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* SYSCFG_CPID */
#define SYSCFG_CPID_CPID                             BITS(0,31)                         /*!< ID of CPx, 43_4D_37_30h: CPx = Cortex-M7_0, 43_4D_37_31h: CPx = Cortex-M7_1 */

/* SYSCFG_CPNUM */
#define SYSCFG_CPNUM_CPNUM                           BITS(0,1)                          /*!< core number of CPx, 00: Cortex-M7_0 core0, 01: Cortex-M7_1 core 1 */

/* SYSCFG_CPCFGINF0 */
#define SYSCFG_CPCFGINF0_DC_WAY                      BITS(0,7)                          /*!< CPx level 1 data cache ways */
#define SYSCFG_CPCFGINF0_DC_SZ                       BITS(8,15)                         /*!< CPx level 1 data cache size */
#define SYSCFG_CPCFGINF0_IC_WAY                      BITS(16,23)                        /*!< CPx level 1 instruction cache ways */
#define SYSCFG_CPCFGINF0_IC_SZ                       BITS(24,31)                        /*!< CPx level 1 instruction cache size */

/* SYSCFG_CPCFGINF1 */
#define SYSCFG_CPCFGINF1_ITCM_SZ                     BITS(16,23)                        /*!< CPx instruction tightly coupled memory size */
#define SYSCFG_CPCFGINF1_DTCM_SZ                     BITS(24,31)                        /*!< CPx tightly coupled data memory size */

/* SYSCFG_CPCFGINF2 */
#define SYSCFG_CPCFGINF2_FPU                         BIT(0)                             /*!< CPx floating point unit provided bit */
#define SYSCFG_CPCFGINF2_SIMD                        BIT(1)                             /*!< CPx SIMD/NEON instruction support bit */
#define SYSCFG_CPCFGINF2_MMU                         BIT(2)                             /*!< CPx memory management unit support bit */
#define SYSCFG_CPCFGINF2_CMPU                        BIT(3)                             /*!< CPx core memory protection unit support bit */
#define SYSCFG_CPCFGINF2_CRPY                        BIT(4)                             /*!< CPx cryptography support bit */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* SYSCFG_CP0ID */
#define SYSCFG_CP0ID_CPID                            BITS(0,31)                         /*!< ID of CPx, 43_4D_37_30h: CPx = Cortex-M7_0, 43_4D_37_31h: CPx = Cortex-M7_1 */

/* SYSCFG_CP0NUM */
#define SYSCFG_CP0NUM_CPNUM                          BITS(0,1)                          /*!< core number of CPx, 00: Cortex-M7_0 core0, 01: Cortex-M7_1 core 1 */

/* SYSCFG_CP0CFGINF0 */
#define SYSCFG_CP0CFGINF0_DC_WAY                     BITS(0,7)                          /*!< CP0 level 1 data cache ways */
#define SYSCFG_CP0CFGINF0_DC_SZ                      BITS(8,15)                         /*!< CP0 level 1 data cache size */
#define SYSCFG_CP0CFGINF0_IC_WAY                     BITS(16,23)                        /*!< CP0 level 1 instruction cache ways */
#define SYSCFG_CP0CFGINF0_IC_SZ                      BITS(24,31)                        /*!< CP0 level 1 instruction cache size */

/* SYSCFG_CP0CFGINF1 */
#define SYSCFG_CP0CFGINF1_ITCM_SZ                    BITS(16,23)                        /*!< CP0 instruction tightly coupled memory size */
#define SYSCFG_CP0CFGINF1_DTCM_SZ                    BITS(24,31)                        /*!< CP0 tightly coupled data memory size */

/* SYSCFG_CP0CFGINF2 */
#define SYSCFG_CP0CFGINF2_FPU                        BIT(0)                             /*!< CP0 floating point unit provided bit */
#define SYSCFG_CP0CFGINF2_SIMD                       BIT(1)                             /*!< CP0 SIMD/NEON instruction support bit */
#define SYSCFG_CP0CFGINF2_MMU                        BIT(2)                             /*!< CP0 memory management unit support bit */
#define SYSCFG_CP0CFGINF2_CMPU                       BIT(3)                             /*!< CP0 core memory protection unit support bit */
#define SYSCFG_CP0CFGINF2_CRPY                       BIT(4)                             /*!< CP0 cryptography support bit */

#if defined (GD32A72XX) || defined (GD32A74XX)
/* SYSCFG_CP1ID */
#define SYSCFG_CP1ID_CPID                            BITS(0,31)                         /*!< ID of CPx, 43_4D_37_30h: CPx = Cortex-M7_0, 43_4D_37_31h: CPx = Cortex-M7_1 */

/* SYSCFG_CP1NUM */
#define SYSCFG_CP1NUM_CPNUM                          BITS(0,1)                          /*!< core number of CP1, 00: Cortex-M7_0 core0, 01: Cortex-M7_1 core 1 */

/* SYSCFG_CP1CFGINF0 */
#define SYSCFG_CP1CFGINF0_DC_WAY                     BITS(0,7)                          /*!< CP1 level 1 data cache ways */
#define SYSCFG_CP1CFGINF0_DC_SZ                      BITS(8,15)                         /*!< CP1 level 1 data cache size */
#define SYSCFG_CP1CFGINF0_IC_WAY                     BITS(16,23)                        /*!< CP1 level 1 instruction cache ways */
#define SYSCFG_CP1CFGINF0_IC_SZ                      BITS(24,31)                        /*!< CP1 level 1 instruction cache size */

/* SYSCFG_CP1CFGINF1 */
#define SYSCFG_CP1CFGINF1_ITCM_SZ                    BITS(16,23)                        /*!< CP1 instruction tightly coupled memory size */
#define SYSCFG_CP1CFGINF1_DTCM_SZ                    BITS(24,31)                        /*!< CP1 tightly coupled data memory size */

/* SYSCFG_CP1CFGINF2 */
#define SYSCFG_CP1CFGINF2_FPU                        BIT(0)                             /*!< CP1 floating point unit provided bit */
#define SYSCFG_CP1CFGINF2_SIMD                       BIT(1)                             /*!< CP1 SIMD/NEON instruction support bit */
#define SYSCFG_CP1CFGINF2_MMU                        BIT(2)                             /*!< CP1 memory management unit support bit */
#define SYSCFG_CP1CFGINF2_CMPU                       BIT(3)                             /*!< CP1 core memory protection unit support bit */
#define SYSCFG_CP1CFGINF2_CRPY                       BIT(4)                             /*!< CP1 cryptography support bit */

/* SYSCFG_IRCP0INTSTAT0 */
#define SYSCFG_IRCP0INTSTAT0_CP0IF                   BIT(0)                             /*!< CP0-to-CP0 INT0 interrupt status */
#define SYSCFG_IRCP0INTSTAT0_CP1IF                   BIT(1)                             /*!< CP1-to-CP0 INT0 interrupt status */

/* SYSCFG_IRCP0INTSTAT1 */
#define SYSCFG_IRCP0INTSTAT1_CP0IF                   BIT(0)                             /*!< CP0-to-CP0 INT1 interrupt status */
#define SYSCFG_IRCP0INTSTAT1_CP1IF                   BIT(1)                             /*!< CP1-to-CP0 INT1 interrupt status */

/* SYSCFG_IRCP0INTSTAT2 */
#define SYSCFG_IRCP0INTSTAT2_CP0IF                   BIT(0)                             /*!< CP0-to-CP0 INT2 interrupt status */
#define SYSCFG_IRCP0INTSTAT2_CP1IF                   BIT(1)                             /*!< CP1-to-CP0 INT2 interrupt status */

/* SYSCFG_IRCP0INTSTAT3 */
#define SYSCFG_IRCP0INTSTAT3_CP0IF                   BIT(0)                             /*!< CP0-to-CP0 INT3 interrupt status */
#define SYSCFG_IRCP0INTSTAT3_CP1IF                   BIT(1)                             /*!< CP1-to-CP0 INT3 interrupt status */

/* SYSCFG_IRCP1INTSTAT0 */
#define SYSCFG_IRCP1INTSTAT0_CP0IF                   BIT(0)                             /*!< CP0-to-CP1 INT0 interrupt status */
#define SYSCFG_IRCP1INTSTAT0_CP1IF                   BIT(1)                             /*!< CP1-to-CP1 INT0 interrupt status */

/* SYSCFG_IRCP1INTSTAT1 */
#define SYSCFG_IRCP1INTSTAT1_CP0IF                   BIT(0)                             /*!< CP0-to-CP1 INT1 interrupt status */
#define SYSCFG_IRCP1INTSTAT1_CP1IF                   BIT(1)                             /*!< CP1-to-CP1 INT1 interrupt status */

/* SYSCFG_IRCP1INTSTAT2 */
#define SYSCFG_IRCP1INTSTAT2_CP0IF                   BIT(0)                             /*!< CP0-to-CP1 INT2 interrupt status */
#define SYSCFG_IRCP1INTSTAT2_CP1IF                   BIT(1)                             /*!< CP1-to-CP1 INT2 interrupt status */

/* SYSCFG_IRCP1INTSTAT3 */
#define SYSCFG_IRCP1INTSTAT3_CP0IF                   BIT(0)                             /*!< CP0-to-CP1 INT3 interrupt status */
#define SYSCFG_IRCP1INTSTAT3_CP1IF                   BIT(1)                             /*!< CP1-to-CP1 INT3 interrupt status */

/* SYSCFG_IRCP0INT0 */
#define SYSCFG_IRCP0INT0_CPIE                        BIT(0)                             /*!< CP0 INT0 interrupt enable */

/* SYSCFG_IRCP0INT1 */
#define SYSCFG_IRCP0INT1_CPIE                        BIT(0)                             /*!< CP0 INT1 interrupt enable */

/* SYSCFG_IRCP0INT2 */
#define SYSCFG_IRCP0INT2_CPIE                        BIT(0)                             /*!< CP0 INT2 interrupt enable */

/* SYSCFG_IRCP0INT3 */
#define SYSCFG_IRCP0INT3_CPIE                        BIT(0)                             /*!< CP0 INT3 interrupt enable */

/* SYSCFG_IRCP1INT0 */
#define SYSCFG_IRCP1INT0_CPIE                        BIT(0)                             /*!< CP1 INT0 interrupt enable */

/* SYSCFG_IRCP1INT1 */
#define SYSCFG_IRCP1INT1_CPIE                        BIT(0)                             /*!< CP1 INT1 interrupt enable */

/* SYSCFG_IRCP1INT2 */
#define SYSCFG_IRCP1INT2_CPIE                        BIT(0)                             /*!< CP1 INT2 interrupt enable */

/* SYSCFG_IRCP1INT3 */
#define SYSCFG_IRCP1INT3_CPIE                        BIT(0)                             /*!< CP1 INT3 interrupt enable */

/* SYSCFG_IRCPUCTL */
#define SYSCFG_IRCPUCTL_CP0TR                        BIT(0)                             /*!< CP0 as trusted core */
#define SYSCFG_IRCPUCTL_CP1TR                        BIT(1)                             /*!< CP1 as trusted core */
#define SYSCFG_IRCPUCTL_LK                           BIT(31)                            /*!< provides a locking mechanism of the register */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* SYSCFG_MEMAEXCTL */
#define SYSCFG_MEMAEXCTL_SRAM0_EXDIS                 BIT(0)                             /*!< SRAM 0 controller access execution control */
#define SYSCFG_MEMAEXCTL_SRAM1_EXDIS                 BIT(1)                             /*!< SRAM 1 controller access execution control */
#define SYSCFG_MEMAEXCTL_ITCM0_DA_EXDIS              BIT(8)                             /*!< ITCM core 0 direct access execution control */
#define SYSCFG_MEMAEXCTL_ITCM1_DA_EXDIS              BIT(9)                             /*!< ITCM core 1 direct access execution control */
#define SYSCFG_MEMAEXCTL_ITCM0_BDA_EXDIS             BIT(12)                            /*!< ITCM core 0 backdoor access execution control */
#define SYSCFG_MEMAEXCTL_ITCM1_BDA_EXDIS             BIT(13)                            /*!< ITCM core 1 backdoor access execution control */
#define SYSCFG_MEMAEXCTL_DTCM0_DA_EXDIS              BIT(16)                            /*!< DTCM core 0 direct access execution control */
#define SYSCFG_MEMAEXCTL_DTCM1_DA_EXDIS              BIT(17)                            /*!< DTCM core 1 direct access execution control */
#define SYSCFG_MEMAEXCTL_DTCM0_BDA_EXDIS             BIT(20)                            /*!< DTCM core 0 backdoor access execution control */
#define SYSCFG_MEMAEXCTL_DTCM1_BDA_EXDIS             BIT(21)                            /*!< DTCM core 1 backdoor access execution control */
#define SYSCFG_MEMAEXCTL_SLKEN                       BIT(30)                            /*!< soft lock of the register */
#define SYSCFG_MEMAEXCTL_HLKEN                       BIT(31)                            /*!< hard lock of the register */

/* SYSCFG_BM1EDCEN */
#define SYSCFG_BM1EDCEN_RDC_DMA0_M_EN                BIT(0)                             /*!< enable read data check DMA0 memory accesses */
#define SYSCFG_BM1EDCEN_RDC_DMA0_P_EN                BIT(1)                             /*!< enable read data check DMA0 peripheral accesses */
#define SYSCFG_BM1EDCEN_RDC_DMA1_M_EN                BIT(2)                             /*!< enable read data check DMA1 memory accesses */
#define SYSCFG_BM1EDCEN_RDC_DMA1_P_EN                BIT(3)                             /*!< enable read data check DMA1 peripheral accesses */
#define SYSCFG_BM1EDCEN_RDC_HSM_BM1_EN               BIT(4)                             /*!< enable read data check HSM BM1 */
#define SYSCFG_BM1EDCEN_RDC_ENET_EN                  BIT(5)                             /*!< enable read data check ENET */
#define SYSCFG_BM1EDCEN_RDC_CM7_0_EN                 BIT(6)                             /*!< enable read data check Cortex-M7_0_AXIM */
#define SYSCFG_BM1EDCEN_RDC_CM7_1_EN                 BIT(8)                             /*!< enable read data check Cortex-M7_1_AXIM */
#define SYSCFG_BM1EDCEN_WDC_SRAM0_EN                 BIT(12)                            /*!< enable write data check SRAM0 */
#define SYSCFG_BM1EDCEN_ADDC_SRAM0_EN                BIT(13)                            /*!< enable address check SRAM0 */
#define SYSCFG_BM1EDCEN_WDC_SRAM1_EN                 BIT(14)                            /*!< enable write data check SRAM1 */
#define SYSCFG_BM1EDCEN_ADDC_SRAM1_EN                BIT(15)                            /*!< enable address check SRAM1 */
#define SYSCFG_BM1EDCEN_WDC_QSPI_EN                  BIT(16)                            /*!< enable write data check QSPI */
#define SYSCFG_BM1EDCEN_ADDC_QSPI_EN                 BIT(17)                            /*!< enable address check QSPI */
#define SYSCFG_BM1EDCEN_WDC_FMC_0_EN                 BIT(18)                            /*!< enable write data check FMC_0 */
#define SYSCFG_BM1EDCEN_ADDC_FMC_0_EN                BIT(19)                            /*!< enable address check FMC_0 */
#define SYSCFG_BM1EDCEN_WDC_FMC_1_EN                 BIT(20)                            /*!< enable write data check FMC_1 */
#define SYSCFG_BM1EDCEN_ADDC_FMC_1_EN                BIT(21)                            /*!< enable address check FMC_1 */
#define SYSCFG_BM1EDCEN_WDC_FMC_2_EN                 BIT(22)                            /*!< enable write data check FMC_2 */
#define SYSCFG_BM1EDCEN_ADDC_FMC_2_EN                BIT(23)                            /*!< enable address check FMC_2 */
#define SYSCFG_BM1EDCEN_WDC_TCM_EN                   BIT(24)                            /*!< enable write data check TCM */
#define SYSCFG_BM1EDCEN_ADDC_TCM_EN                  BIT(25)                            /*!< enable address check TCM */

/* SYSCFG_BM2EDCEN */
#define SYSCFG_BM2EDCEN_RDC_DMA0_M_EN                BIT(0)                             /*!< enable read data check DMA0 memory accesses */
#define SYSCFG_BM2EDCEN_RDC_DMA0_P_EN                BIT(1)                             /*!< enable read data check DMA0 peripheral accesses */
#define SYSCFG_BM2EDCEN_RDC_DMA1_M_EN                BIT(2)                             /*!< enable read data check DMA1 memory accesses */
#define SYSCFG_BM2EDCEN_RDC_DMA1_P_EN                BIT(3)                             /*!< enable read data check DMA1 peripheral accesses */
#define SYSCFG_BM2EDCEN_RDC_HSM_BM2_EN               BIT(5)                             /*!< enable read data check HSM BM2 */
#define SYSCFG_BM2EDCEN_RDC_AHBP0_EN                 BIT(7)                             /*!< enable read data check Cortex-M7_0_AHBP */
#define SYSCFG_BM2EDCEN_RDC_AHBP1_EN                 BIT(9)                             /*!< enable read data check Cortex-M7_1_AHBP */
#define SYSCFG_BM2EDCEN_WDC_APB1_EN                  BIT(20)                            /*!< enable write data check APB1 */
#define SYSCFG_BM2EDCEN_ADDC_APB1_EN                 BIT(21)                            /*!< enable address check APB1 */
#define SYSCFG_BM2EDCEN_WDC_APB2_EN                  BIT(22)                            /*!< enable write data check APB2 */
#define SYSCFG_BM2EDCEN_ADDC_APB2_EN                 BIT(23)                            /*!< enable address check APB2 */
#define SYSCFG_BM2EDCEN_WDC_AHB1_EN                  BIT(24)                            /*!< enable write data check AHB1 */
#define SYSCFG_BM2EDCEN_ADDC_AHB1_EN                 BIT(25)                            /*!< enable address check AHB1 */
#define SYSCFG_BM2EDCEN_WDC_AHB2_EN                  BIT(26)                            /*!< enable write data check AHB2 */
#define SYSCFG_BM2EDCEN_ADDC_AHB2_EN                 BIT(27)                            /*!< enable address check AHB2 */

/* SYSCFG_BUSCHKCFG */
#define SYSCFG_BUSCHKCFG_ENET_CHKEN                  BIT(1)                             /*!< enable or disable ENET mem port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_HSM_CHKEN                   BIT(2)                             /*!< enable or disable HSM port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_DMA0M_CHKEN                 BIT(3)                             /*!< enable or disable DMA0 mem port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_DMA0P_CHKEN                 BIT(4)                             /*!< enable or disable DMA0 peri port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_DMA1M_CHKEN                 BIT(5)                             /*!< enable or disable DMA1 mem port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_DMA1P_CHKEN                 BIT(6)                             /*!< enable or disable DMA1 peri port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_AHBP_CM7_0_CHKEN            BIT(7)                             /*!< enable or disable CM7_0 AHBP port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_AHBP_CM7_1_CHKEN            BIT(8)                             /*!< enable or disable CM7_1 AHBP port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_AXIM_CM7_0_CHKEN            BIT(9)                             /*!< enable or disable CM7_0 AXIM port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_AXIM_CM7_1_CHKEN            BIT(10)                            /*!< enable or disable CM7_1 AXIM port timeout and slaver ID check */
#define SYSCFG_BUSCHKCFG_DMA0M_SPLT_WGT_CHKEN        BIT(11)                            /*!< enable or disable split0 widget of DMA0 mem redundant check */
#define SYSCFG_BUSCHKCFG_DMA0P_SPLT_WGT_CHKEN        BIT(12)                            /*!< enable or disable split0 widget of DMA0 peri redundant check */
#define SYSCFG_BUSCHKCFG_DMA1M_SPLT_WGT_CHKEN        BIT(13)                            /*!< enable or disable split0 widget of DMA1 mem redundant check */
#define SYSCFG_BUSCHKCFG_DMA1P_SPLT_WGT_CHKEN        BIT(14)                            /*!< enable or disable split0 widget of DMA1 peri redundant check */
#define SYSCFG_BUSCHKCFG_HSM_SPLT_WGT_CHKEN          BIT(15)                            /*!< enable or disable split1 widget of HSM redundant check. */
#define SYSCFG_BUSCHKCFG_TCM_SPLT_WGT_CHKEN          BIT(16)                            /*!< enable or disable split1 widget of TCM SRAM redundant check */
#define SYSCFG_BUSCHKCFG_HSM_H2H1_WGT_CHKEN          BIT(17)                            /*!< enable or disable H2H1 widget of HSM redundant check */
#define SYSCFG_BUSCHKCFG_DMA0M_H2H0_WGT_CHKEN        BIT(18)                            /*!< enable or disable H2H0 widget of DMA0 mem redundant check */
#define SYSCFG_BUSCHKCFG_DMA0P_H2H0_WGT_CHKEN        BIT(19)                            /*!< enable or disable H2H0 widget of DMA0 peri redundant check */
#define SYSCFG_BUSCHKCFG_DMA1M_H2H0_WGT_CHKEN        BIT(20)                            /*!< enable or disable H2H0 widget of DMA1 mem redundant check */
#define SYSCFG_BUSCHKCFG_DMA1P_H2H0_WGT_CHKEN        BIT(21)                            /*!< enable or disable H2H0 widget of DMA1 peri redundant check */
#define SYSCFG_BUSCHKCFG_QSPI_H2H0_WGT_CHKEN         BIT(22)                            /*!< enable or disable H2H0 widget of QSPI redundant check */
#define SYSCFG_BUSCHKCFG_TCM_H2H0_WGT_CHKEN          BIT(23)                            /*!< enable or disable H2H0 widget of TCM redundant check */
#define SYSCFG_BUSCHKCFG_ENET_WGT_CHKEN              BIT(24)                            /*!< enable or disable ENET 1:1/1:2 widget check */
#define SYSCFG_BUSCHKCFG_TCM_WGT_CHKEN               BIT(25)                            /*!< enable or disable TCM 1:1 widget check */
#define SYSCFG_BUSCHKCFG_APB1_CHKEN                  BIT(27)                            /*!< enable or disable APB1 redundant check */
#define SYSCFG_BUSCHKCFG_APB2_CHKEN                  BIT(28)                            /*!< enable or disable APB2 redundant check */
#define SYSCFG_BUSCHKCFG_AHB1_CHKEN                  BIT(29)                            /*!< enable or disable AHB1 redundant check */
#define SYSCFG_BUSCHKCFG_AHB2_CHKEN                  BIT(30)                            /*!< enable or disable AHB2 redundant check */

/* SYSCFG_TMRCS */
#define SYSCFG_TMRCS_TMRERR_FMUNMIENIE               BIT(0)                             /*!< TMR fault interrupt enable of the FMU NMI interrupt flag enable */
#define SYSCFG_TMRCS_TMRERR_CPUENIE                  BIT(1)                             /*!< TMR fault interrupt enable of the CPU released */
#define SYSCFG_TMRCS_TMRERR_MEMEXECRIE               BIT(2)                             /*!< TMR fault interrupt enable of the memory execution control register */
#define SYSCFG_TMRCS_TMRERR_CPUINTIE                 BIT(3)                             /*!< TMR fault interrupt enable of the interrupt router CPn interrupt status register */
#define SYSCFG_TMRCS_TMRERR_FMUNMIENIF               BIT(16)                            /*!< TMR fault flag of the FMU NMI interrupt flag enable */
#define SYSCFG_TMRCS_TMRERR_CPUENIF                  BIT(17)                            /*!< TMR fault flag of the CPU released register */
#define SYSCFG_TMRCS_TMRERR_MEMEXECRIF               BIT(18)                            /*!< TMR fault flag of the memory execution control register */
#define SYSCFG_TMRCS_TMRERR_CPUINTIF                 BIT(19)                            /*!< TMR fault flag of the interrupt router CPn interrupt status register */


/* constants definitions */
/* core num definitions */
#define CM7_0                                        ((uint8_t)0x00U)                   /*!< Cortex-M7 core 0 */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define CM7_1                                        ((uint8_t)0x01U)                   /*!< Cortex-M7 core 1 */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

#define CPU0_ID                                      ((uint32_t)0x434D3730U)            /*!< Cortex-M7_0 */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define CPU1_ID                                      ((uint32_t)0x434D3731U)            /*!< Cortex-M7_1 */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

#define ICACHE_INFO                                  ((uint32_t)0x00000000U)            /*!< I-Cache information */
#define DCACHE_INFO                                  ((uint32_t)0x00000001U)            /*!< D-Cache information */
#define ITCM_INFO                                    ((uint32_t)0x00000000U)            /*!< ITCM information */
#define DTCM_INFO                                    ((uint32_t)0x00000001U)            /*!< DTCM information */

/* EXTI source select definition */
#define EXTISS0                                      ((uint8_t)0x00U)                   /*!< EXTI source select register 0 */
#define EXTISS1                                      ((uint8_t)0x01U)                   /*!< EXTI source select register 1 */
#define EXTISS2                                      ((uint8_t)0x02U)                   /*!< EXTI source select register 2 */
#define EXTISS3                                      ((uint8_t)0x03U)                   /*!< EXTI source select register 3 */

/* EXTI source select mask bits definition */
#define EXTI_SS_MASK                                 BITS(0,3)                          /*!< EXTI source select mask */

/* EXTI source select jumping step definition */
#define EXTI_SS_JSTEP                                ((uint8_t)(0x04U))                 /*!< EXTI source select jumping step */

/* EXTI source select moving step definition */
#define EXTI_SS_MSTEP(pin)                           (EXTI_SS_JSTEP * ((pin) % EXTI_SS_JSTEP))   /*!< EXTI source select moving step */

/* EXTI source port definitions */
#define EXTI_SOURCE_GPIOA                            ((uint8_t)0x00U)                    /*!< EXTI GPIOA configuration */
#define EXTI_SOURCE_GPIOB                            ((uint8_t)0x01U)                    /*!< EXTI GPIOB configuration */
#define EXTI_SOURCE_GPIOC                            ((uint8_t)0x02U)                    /*!< EXTI GPIOC configuration */
#define EXTI_SOURCE_GPIOD                            ((uint8_t)0x03U)                    /*!< EXTI GPIOD configuration */
#define EXTI_SOURCE_GPIOE                            ((uint8_t)0x04U)                    /*!< EXTI GPIOE configuration */
#define EXTI_SOURCE_GPIOF                            ((uint8_t)0x05U)                    /*!< EXTI GPIOF configuration */
#define EXTI_SOURCE_GPIOG                            ((uint8_t)0x06U)                    /*!< EXTI GPIOG configuration */
#define EXTI_SOURCE_GPIOH                            ((uint8_t)0x07U)                    /*!< EXTI GPIOH configuration */
#define EXTI_SOURCE_GPIOI                            ((uint8_t)0x08U)                    /*!< EXTI GPIOI configuration */
#define EXTI_SOURCE_GPIOJ                            ((uint8_t)0x09U)                    /*!< EXTI GPIOJ configuration */
#define EXTI_SOURCE_GPIOK                            ((uint8_t)0x0AU)                    /*!< EXTI GPIOK configuration */
#define EXTI_SOURCE_GPIOL                            ((uint8_t)0x0BU)                    /*!< EXTI GPIOL configuration */
#define EXTI_SOURCE_GPIOM                            ((uint8_t)0x0CU)                    /*!< EXTI GPIOM configuration */
#define EXTI_SOURCE_GPION                            ((uint8_t)0x0DU)                    /*!< EXTI GPION configuration */

/* EXTI source pin definitions */
#define EXTI_SOURCE_PIN0                             ((uint8_t)0x00U)                    /*!< EXTI GPIO pin0 configuration */
#define EXTI_SOURCE_PIN1                             ((uint8_t)0x01U)                    /*!< EXTI GPIO pin1 configuration */
#define EXTI_SOURCE_PIN2                             ((uint8_t)0x02U)                    /*!< EXTI GPIO pin2 configuration */
#define EXTI_SOURCE_PIN3                             ((uint8_t)0x03U)                    /*!< EXTI GPIO pin3 configuration */
#define EXTI_SOURCE_PIN4                             ((uint8_t)0x04U)                    /*!< EXTI GPIO pin4 configuration */
#define EXTI_SOURCE_PIN5                             ((uint8_t)0x05U)                    /*!< EXTI GPIO pin5 configuration */
#define EXTI_SOURCE_PIN6                             ((uint8_t)0x06U)                    /*!< EXTI GPIO pin6 configuration */
#define EXTI_SOURCE_PIN7                             ((uint8_t)0x07U)                    /*!< EXTI GPIO pin7 configuration */
#define EXTI_SOURCE_PIN8                             ((uint8_t)0x08U)                    /*!< EXTI GPIO pin8 configuration */
#define EXTI_SOURCE_PIN9                             ((uint8_t)0x09U)                    /*!< EXTI GPIO pin9 configuration */
#define EXTI_SOURCE_PIN10                            ((uint8_t)0x0AU)                    /*!< EXTI GPIO pin10 configuration */
#define EXTI_SOURCE_PIN11                            ((uint8_t)0x0BU)                    /*!< EXTI GPIO pin11 configuration */
#define EXTI_SOURCE_PIN12                            ((uint8_t)0x0CU)                    /*!< EXTI GPIO pin12 configuration */
#define EXTI_SOURCE_PIN13                            ((uint8_t)0x0DU)                    /*!< EXTI GPIO pin13 configuration */
#define EXTI_SOURCE_PIN14                            ((uint8_t)0x0EU)                    /*!< EXTI GPIO pin14 configuration */
#define EXTI_SOURCE_PIN15                            ((uint8_t)0x0FU)                    /*!< EXTI GPIO pin15 configuration */

/* I2Cx fast mode plus enable */
#define SYSCFG_I2C0_FMP                              SYSCFG_PMCFG_I2C0FMPEN              /*!< I2C0 fast mode plus */
#define SYSCFG_I2C1_FMP                              SYSCFG_PMCFG_I2C1FMPEN              /*!< I2C1 fast mode plus */

/* TIMER break input source select */
#define TIMER_BRKIN_SEL_GPIO                         ((uint32_t)0x00000000U)             /*!< TIMER break input select from GPIO pin */
#define TIMER_BRKIN_SEL_TRIGSEL                      ((uint32_t)0x00000001U)             /*!< TIMER break input select from TRIGSEL */

/* TIMERx break input y */
#define TIMER63_BRKIN3_TRIG                          SYSCFG_TIMERBKINSEL_TIMER64_BRKIN3_SEL /*!< TIMER63 break input 3 selection */
#define TIMER63_BRKIN2_TRIG                          SYSCFG_TIMERBKINSEL_TIMER64_BRKIN2_SEL /*!< TIMER63 break input 2 selection */
#define TIMER63_BRKIN1_TRIG                          SYSCFG_TIMERBKINSEL_TIMER64_BRKIN1_SEL /*!< TIMER63 break input 1 selection */
#define TIMER63_BRKIN0_TRIG                          SYSCFG_TIMERBKINSEL_TIMER64_BRKIN0_SEL /*!< TIMER63 break input 0 selection */
#define TIMER62_BRKIN3_TRIG                          SYSCFG_TIMERBKINSEL_TIMER63_BRKIN3_SEL /*!< TIMER62 break input 3 selection */
#define TIMER62_BRKIN2_TRIG                          SYSCFG_TIMERBKINSEL_TIMER63_BRKIN2_SEL /*!< TIMER62 break input 2 selection */
#define TIMER62_BRKIN1_TRIG                          SYSCFG_TIMERBKINSEL_TIMER63_BRKIN1_SEL /*!< TIMER62 break input 1 selection */
#define TIMER62_BRKIN0_TRIG                          SYSCFG_TIMERBKINSEL_TIMER63_BRKIN0_SEL /*!< TIMER62 break input 0 selection */
#define TIMER61_BRKIN3_TRIG                          SYSCFG_TIMERBKINSEL_TIMER62_BRKIN3_SEL /*!< TIMER61 break input 3 selection */
#define TIMER61_BRKIN2_TRIG                          SYSCFG_TIMERBKINSEL_TIMER62_BRKIN2_SEL /*!< TIMER61 break input 2 selection */
#define TIMER61_BRKIN1_TRIG                          SYSCFG_TIMERBKINSEL_TIMER62_BRKIN1_SEL /*!< TIMER61 break input 1 selection */
#define TIMER61_BRKIN0_TRIG                          SYSCFG_TIMERBKINSEL_TIMER62_BRKIN0_SEL /*!< TIMER61 break input 0 selection */
#define TIMER60_BRKIN3_TRIG                          SYSCFG_TIMERBKINSEL_TIMER61_BRKIN3_SEL /*!< TIMER60 break input 3 selection */
#define TIMER60_BRKIN2_TRIG                          SYSCFG_TIMERBKINSEL_TIMER61_BRKIN2_SEL /*!< TIMER60 break input 2 selection */
#define TIMER60_BRKIN1_TRIG                          SYSCFG_TIMERBKINSEL_TIMER61_BRKIN1_SEL /*!< TIMER60 break input 1 selection */
#define TIMER60_BRKIN0_TRIG                          SYSCFG_TIMERBKINSEL_TIMER61_BRKIN0_SEL /*!< TIMER60 break input 0 selection */
#define TIMER20_BRKIN3_TRIG                          SYSCFG_TIMERBKINSEL_TIMER21_BRKIN3_SEL /*!< TIMER20 break input 3 selection */
#define TIMER20_BRKIN2_TRIG                          SYSCFG_TIMERBKINSEL_TIMER21_BRKIN2_SEL /*!< TIMER20 break input 2 selection */
#define TIMER20_BRKIN1_TRIG                          SYSCFG_TIMERBKINSEL_TIMER21_BRKIN1_SEL /*!< TIMER20 break input 1 selection */
#define TIMER20_BRKIN0_TRIG                          SYSCFG_TIMERBKINSEL_TIMER21_BRKIN0_SEL /*!< TIMER20 break input 0 selection */
#define TIMER19_BRKIN3_TRIG                          SYSCFG_TIMERBKINSEL_TIMER20_BRKIN3_SEL /*!< TIMER19 break input 3 selection */
#define TIMER19_BRKIN2_TRIG                          SYSCFG_TIMERBKINSEL_TIMER20_BRKIN2_SEL /*!< TIMER19 break input 2 selection */
#define TIMER19_BRKIN1_TRIG                          SYSCFG_TIMERBKINSEL_TIMER20_BRKIN1_SEL /*!< TIMER19 break input 1 selection */
#define TIMER19_BRKIN0_TRIG                          SYSCFG_TIMERBKINSEL_TIMER20_BRKIN0_SEL /*!< TIMER19 break input 0 selection */
#define TIMER7_BRKIN3_TRIG                           SYSCFG_TIMERBKINSEL_TIMER8_BRKIN3_SEL  /*!< TIMER7 break input 3 selection */
#define TIMER7_BRKIN2_TRIG                           SYSCFG_TIMERBKINSEL_TIMER8_BRKIN2_SEL  /*!< TIMER7 break input 2 selection */
#define TIMER7_BRKIN1_TRIG                           SYSCFG_TIMERBKINSEL_TIMER8_BRKIN1_SEL  /*!< TIMER7 break input 1 selection */
#define TIMER7_BRKIN0_TRIG                           SYSCFG_TIMERBKINSEL_TIMER8_BRKIN0_SEL  /*!< TIMER7 break input 0 selection */
#define TIMER0_BRKIN3_TRIG                           SYSCFG_TIMERBKINSEL_TIMER1_BRKIN3_SEL  /*!< TIMER0 break input 3 selection */
#define TIMER0_BRKIN2_TRIG                           SYSCFG_TIMERBKINSEL_TIMER1_BRKIN2_SEL  /*!< TIMER0 break input 2 selection */
#define TIMER0_BRKIN1_TRIG                           SYSCFG_TIMERBKINSEL_TIMER1_BRKIN1_SEL  /*!< TIMER0 break input 1 selection */
#define TIMER0_BRKIN0_TRIG                           SYSCFG_TIMERBKINSEL_TIMER1_BRKIN0_SEL  /*!< TIMER0 break input 0 selection */

#define CPU_HOLD                                     ((uint8_t)0x00U)                     /*!< CPU held */
#define CPU_RELEASE                                  ((uint8_t)0x01U)                     /*!< CPU released */

#define ROUND_ROBIN                                  ((uint8_t)0x00U)                     /*!< round-robin arbitration */
#define AHBS_HIGHER_PRIO                             ((uint8_t)0x01U)                     /*!< AHB slave port has higher access priority than core access */

#define RM_SYSTEM_RESET                              ((uint8_t)0x00U)                     /*!< recovery mode sequence on system reset */
#define RM_SUBSYSTEM_RESET                           ((uint8_t)0x01U)                     /*!< recovery mode sequence on subsystem reset */

/* SYSCFG flag definitions */
#define SYSCFG_FLAG_CKMNMIERR                        SYSCFG_STAT_CKMNMIIF                 /*!< HXTAL clock monitor NMI error flag */
#define SYSCFG_FLAG_NMIPINERR                        SYSCFG_STAT_NMIPINIF                 /*!< NMI pin error flag */
#define SYSCFG_FLAG_FMUNMIERR                        SYSCFG_STAT_FMUNMIIF                 /*!< FMU NMI error flag */

#define SYSCFG_FLAG_CPU0_WR_ABORT                    (SYSCFG_CPU0CS_WAS)                  /*!< CPU0 write abort on AHB slave flag */
#define SYSCFG_FLAG_CPU1_WR_ABORT                    (SYSCFG_CPU1CS_WAS | 0x01U)          /*!< CPU1 write abort on AHB slave flag */

/* SYSCFG interrupt flag constants definitions */
#define SYSCFG_INT_FLAG_CKMNMIERR                    SYSCFG_STAT_CKMNMIIF                 /*!< HXTAL clock monitor NMI error interrupt flag */
#define SYSCFG_INT_FLAG_NMIPINERR                    SYSCFG_STAT_NMIPINIF                 /*!< NMI from EXTI pin error interrupt flag */
#define SYSCFG_INT_FLAG_FMUNMIERR                    SYSCFG_STAT_FMUNMIIF                 /*!< FMU NMI error interrupt flag */

/* SYSCFG interrupt enable/disable constants definitions */
#define SYSCFG_INT_CPU0_CKMNMI                       SYSCFG_CFG_CKMNMIIE0                 /*!< NMI interrupt from EXTI enable bit of CPU0 */
#define SYSCFG_INT_CPU0_NMIPIN                       SYSCFG_CFG_NMIPINIE0                 /*!< HXTAL clock monitor NMI interrupt enable bit of CPU0 */
#define SYSCFG_INT_CPU0_FMUNMI                       SYSCFG_CFG_FMUNMIIE0                 /*!< FMU NMI interrupt enable bit of CPU0 */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define SYSCFG_INT_CPU1_CKMNMI                       SYSCFG_CFG_CKMNMIIE1                 /*!< NMI interrupt from EXTI enable bit of CPU1 */
#define SYSCFG_INT_CPU1_NMIPIN                       SYSCFG_CFG_NMIPINIE1                 /*!< HXTAL clock monitor NMI interrupt enable bit of CPU1 */
#define SYSCFG_INT_CPU1_FMUNMI                       SYSCFG_CFG_FMUNMIIE1                 /*!< FMU NMI interrupt enable bit of CPU1 */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* SYSCFG FPU and TCM write abort on slave overrun interrupt definitions */
#define SYSCFG_FPUINT_INEXACT                        SYSCFG_CPU0CS_FIXIE                  /*!< FPU inexact interrupt */
#define SYSCFG_FPUINT_INPUT_ABNORMAL                 SYSCFG_CPU0CS_FIDIE                  /*!< FPU input abnormal interrupt */
#define SYSCFG_FPUINT_OVERFLOW                       SYSCFG_CPU0CS_FOVFIE                 /*!< FPU overflow interrupt */
#define SYSCFG_FPUINT_UNDERFLOW                      SYSCFG_CPU0CS_FUFIE                  /*!< FPU underflow interrupt */
#define SYSCFG_FPUINT_DIV0                           SYSCFG_CPU0CS_FDZIE                  /*!< FPU divide-by-zero interrupt */
#define SYSCFG_FPUINT_INVALID_OPERATION              SYSCFG_CPU0CS_FIOPIE                 /*!< FPU invalid operation interrupt */
#define SYSCFG_TCMINT_WR_ABORT                       SYSCFG_CPU0CS_WAIE                   /*!< write abort on slave overrun interrupt */

/* SYSCFG FPU and TCM write abort on slave overrun interrupt flag definitions */
#define SYSCFG_FPUINT_FLAG_INEXACT                   SYSCFG_CPU0CS_FIXIF                  /*!< FPU inexact interrupt flag */
#define SYSCFG_FPUINT_FLAG_INPUT_ABNORMAL            SYSCFG_CPU0CS_FIDIF                  /*!< FPU input abnormal interrupt flag */
#define SYSCFG_FPUINT_FLAG_OVERFLOW                  SYSCFG_CPU0CS_FOVFIF                 /*!< FPU overflow interrupt flag */
#define SYSCFG_FPUINT_FLAG_UNDERFLOW                 SYSCFG_CPU0CS_FUFIF                  /*!< FPU underflow interrupt flag */
#define SYSCFG_FPUINT_FLAG_DIV0                      SYSCFG_CPU0CS_FDZIF                  /*!< FPU divide-by-zero interrupt flag */
#define SYSCFG_FPUINT_FLAG_INVALID_OPERATION         SYSCFG_CPU0CS_FIOPIF                 /*!< FPU invalid operation interrupt flag */
#define SYSCFG_TCMINT_FLAG_WR_ABORT                  SYSCFG_CPU0CS_WASOVF                 /*!< write abort on slave overrun interrupt flag */

/* SYSCFG core txev event output enable/disable constants definitions */
#define CORE_TX_EVENTOUT_CM7_0                       SYSCFG_CFG_CM7_0_TXEVEN              /*!< Cortex-M7 core 0(CM7_0) TX EVENTOUT */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define CORE_TX_EVENTOUT_CM7_1                       SYSCFG_CFG_CM7_1_TXEVEN              /*!< Cortex-M7 core 1(CM7_1) TX EVENTOUT */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define CORE_TX_EVENTOUT_CM23                        SYSCFG_CFG_CM23_TXEVEN               /*!< Cortex-M23 core(CM23 HSM) TX EVENTOUT */

#if defined (GD32A72XX) || defined (GD32A74XX)
/* interrupt router core processer interrupt interrupt definitions */
#define INTROUTER_CP_INT_0                          ((uint32_t)0x00000000U)               /*!< interrupt router core processer interrupt 0 */
#define INTROUTER_CP_INT_1                          ((uint32_t)0x00000001U)               /*!< interrupt router core processer interrupt 1 */
#define INTROUTER_CP_INT_2                          ((uint32_t)0x00000002U)               /*!< interrupt router core processer interrupt 2 */
#define INTROUTER_CP_INT_3                          ((uint32_t)0x00000003U)               /*!< interrupt router core processer interrupt 3 */

/* interrupt router core processer interrupt interrupt flag definitions */
#define INTROUTER_CP_INT_FLAG_CP0_CP0               SYSCFG_IRCP0INTSTAT0_CP0IF            /*!< CP0 to CP0 interrupt flag */
#define INTROUTER_CP_INT_FLAG_CP1_CP0               SYSCFG_IRCP0INTSTAT0_CP1IF            /*!< CP1 to CP0 interrupt flag */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* TMR error interrupt definitions */
#define TMRERR_INT_FMUNMI                           SYSCFG_TMRCS_TMRERR_FMUNMIENIE        /*!< TMR fault interrupt enable of the FMU NMI interrupt flag enable */
#define TMRERR_INT_CPEN                             SYSCFG_TMRCS_TMRERR_CPUENIE           /*!< TMR fault interrupt enable of the CPU released */
#define TMRERR_INT_MEMEXECR                         SYSCFG_TMRCS_TMRERR_MEMEXECRIE        /*!< TMR fault interrupt enable of the memory execution control register */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define TMRERR_INT_CPINT                            SYSCFG_TMRCS_TMRERR_CPUINTIE          /*!< TMR fault interrupt enable of the interrupt router CPn interrupt status register */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* TMR error interrupt definitions */
#define TMRERR_INT_FLAG_FMUNMI                      SYSCFG_TMRCS_TMRERR_FMUNMIENIF        /*!< TMR fault interrupt flag of the FMU NMI interrupt flag enable */
#define TMRERR_INT_FLAG_CPEN                        SYSCFG_TMRCS_TMRERR_CPUENIF           /*!< TMR fault interrupt flag of the CPU released */
#define TMRERR_INT_FLAG_MEMEXECR                    SYSCFG_TMRCS_TMRERR_MEMEXECRIF        /*!< TMR fault interrupt flag of the memory execution control register */
#define TMRERR_INT_FLAG_CPINT                       SYSCFG_TMRCS_TMRERR_CPUINTIF          /*!< TMR fault interrupt flag of the interrupt router CPn interrupt status register */

/* interrupt router core processor interrupt definitions */
/* CACHE status definitions */
#define CPU_CACHE_ERROR_DETECTION                   ((uint32_t)0x00000000U)               /*!< select detection information of CPU */
#define CPU_CACHE_ERROR_BANK                        ((uint32_t)0x00000001U)               /*!< select error information of CPU */

/* CACHE status information */
#define CPU0_CACHE_DETECTION                        SYSCFG_CPU0ICAC_CPU0_ICDET            /*!< CACHE error detection information of CPU0 */
#define CPU0_CACHE_ERROR                            SYSCFG_CPU0ICAC_CPU0_ICERR            /*!< CACHE error bank information of CPU0 */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define CPU1_CACHE_DETECTION                        SYSCFG_CPU1ICAC_CPU1_ICDET            /*!< CACHE error detection information of CPU1 */
#define CPU1_CACHE_ERROR                            SYSCFG_CPU1ICAC_CPU1_ICERR            /*!< CACHE error bank information of CPU1 */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* memory access peripheral control bit */
#define MEMAEXCTL_SRAM0                             SYSCFG_MEMAEXCTL_SRAM0_EXDIS          /*!< SRAM 0 controller access execution control */
#define MEMAEXCTL_SRAM1                             SYSCFG_MEMAEXCTL_SRAM1_EXDIS          /*!< SRAM 1 controller access execution control */
#define MEMAEXCTL_ITCM0_DA                          SYSCFG_MEMAEXCTL_ITCM0_DA_EXDIS       /*!< ITCM core 0 direct access execution control */
#define MEMAEXCTL_ITCM1_DA                          SYSCFG_MEMAEXCTL_ITCM1_DA_EXDIS       /*!< ITCM core 1 direct access execution control */
#define MEMAEXCTL_ITCM0_BDA                         SYSCFG_MEMAEXCTL_ITCM0_BDA_EXDIS      /*!< ITCM core 0 backdoor access execution control */
#define MEMAEXCTL_ITCM1_BDA                         SYSCFG_MEMAEXCTL_ITCM1_BDA_EXDIS      /*!< ITCM core 1 backdoor access execution control */
#define MEMAEXCTL_DTCM0_DA                          SYSCFG_MEMAEXCTL_DTCM0_DA_EXDIS       /*!< DTCM core 0 direct access execution control */
#define MEMAEXCTL_DTCM1_DA                          SYSCFG_MEMAEXCTL_DTCM1_DA_EXDIS       /*!< DTCM core 1 direct access execution control */
#define MEMAEXCTL_DTCM0_BDA                         SYSCFG_MEMAEXCTL_DTCM0_BDA_EXDIS      /*!< DTCM core 0 backdoor access execution control */
#define MEMAEXCTL_DTCM1_BDA                         SYSCFG_MEMAEXCTL_DTCM1_BDA_EXDIS      /*!< DTCM core 1 backdoor access execution control */

/* bus matrix definition */
#define BUS_MATRIX_1                                ((uint32_t)0x00000000U)               /*!< bus matrix 1 */
#define BUS_MATRIX_2                                BIT(31)                               /*!< bus matrix 2 */

/* bus matrix interconnect error detection */
#define BM1_RD_DATA_CHK_DMA0MEM                     ((uint32_t)(SYSCFG_BM1EDCEN_RDC_DMA0_M_EN | BUS_MATRIX_1)) /*!< read data check DMA0 memory accesses */
#define BM1_RD_DATA_CHK_DMA0PERIPH                  ((uint32_t)(SYSCFG_BM1EDCEN_RDC_DMA0_P_EN | BUS_MATRIX_1)) /*!< read data check DMA0 peripheral accesses */
#define BM1_RD_DATA_CHK_DMA1MEM                     ((uint32_t)(SYSCFG_BM1EDCEN_RDC_DMA1_M_EN | BUS_MATRIX_1)) /*!< read data check DMA1 memory accesses */
#define BM1_RD_DATA_CHK_DMA1PERIPH                  ((uint32_t)(SYSCFG_BM1EDCEN_RDC_DMA1_P_EN | BUS_MATRIX_1)) /*!< read data check DMA1 peripheral accesses */
#define BM1_RD_DATA_CHK_HSM_BM1                     ((uint32_t)(SYSCFG_BM1EDCEN_RDC_HSM_BM1_EN| BUS_MATRIX_1)) /*!< read data check HSM BM1 */
#define BM1_RD_DATA_CHK_ENET                        ((uint32_t)(SYSCFG_BM1EDCEN_RDC_ENET_EN   | BUS_MATRIX_1)) /*!< read data check ENET */
#define BM1_RD_DATA_CHK_CM7_0                       ((uint32_t)(SYSCFG_BM1EDCEN_RDC_CM7_0_EN  | BUS_MATRIX_1)) /*!< read data check Cortex-M7_0_AXIM */
#define BM1_RD_DATA_CHK_CM7_1                       ((uint32_t)(SYSCFG_BM1EDCEN_RDC_CM7_1_EN  | BUS_MATRIX_1)) /*!< read data check Cortex-M7_1_AXIM */
#define BM1_WR_DATA_CHK_SRAM0                       ((uint32_t)(SYSCFG_BM1EDCEN_WDC_SRAM0_EN  | BUS_MATRIX_1)) /*!< write data check SRAM0 */
#define BM1_ADDR_CHK_SRAM0                          ((uint32_t)(SYSCFG_BM1EDCEN_ADDC_SRAM0_EN | BUS_MATRIX_1)) /*!< address check SRAM0 */
#define BM1_WR_DATA_CHK_SRAM1                       ((uint32_t)(SYSCFG_BM1EDCEN_WDC_SRAM1_EN  | BUS_MATRIX_1)) /*!< write data check SRAM1 */
#define BM1_ADDR_CHK_SRAM1                          ((uint32_t)(SYSCFG_BM1EDCEN_ADDC_SRAM1_EN | BUS_MATRIX_1)) /*!< address check SRAM1 */
#define BM1_WR_DATA_CHK_QSPI                        ((uint32_t)(SYSCFG_BM1EDCEN_WDC_QSPI_EN   | BUS_MATRIX_1)) /*!< write data check QSPI */
#define BM1_ADDR_CHK_QSPI                           ((uint32_t)(SYSCFG_BM1EDCEN_ADDC_QSPI_EN  | BUS_MATRIX_1)) /*!< address check QSPI */
#define BM1_WR_DATA_CHK_FMC0                        ((uint32_t)(SYSCFG_BM1EDCEN_WDC_FMC_0_EN  | BUS_MATRIX_1)) /*!< write data check FMC_0 */
#define BM1_ADDR_CHK_FMC0                           ((uint32_t)(SYSCFG_BM1EDCEN_ADDC_FMC_0_EN | BUS_MATRIX_1)) /*!< address check FMC_0 */
#define BM1_WR_DATA_CHK_FMC1                        ((uint32_t)(SYSCFG_BM1EDCEN_WDC_FMC_1_EN  | BUS_MATRIX_1)) /*!< write data check FMC_1 */
#define BM1_ADDR_CHK_FMC1                           ((uint32_t)(SYSCFG_BM1EDCEN_ADDC_FMC_1_EN | BUS_MATRIX_1)) /*!< address check FMC_1 */
#define BM1_WR_DATA_CHK_FMC2                        ((uint32_t)(SYSCFG_BM1EDCEN_WDC_FMC_2_EN  | BUS_MATRIX_1)) /*!< write data check FMC_2 */
#define BM1_ADDR_CHK_FMC2                           ((uint32_t)(SYSCFG_BM1EDCEN_ADDC_FMC_2_EN | BUS_MATRIX_1)) /*!< address check FMC_2 */
#define BM1_WR_DATA_CHK_TCM                         ((uint32_t)(SYSCFG_BM1EDCEN_WDC_TCM_EN    | BUS_MATRIX_1)) /*!< write data check TCM */
#define BM1_ADDR_CHK_TCM                            ((uint32_t)(SYSCFG_BM1EDCEN_ADDC_TCM_EN   | BUS_MATRIX_1)) /*!< address check TCM */
#define BM2_RD_DATA_CHK_DMA0MEM                     ((uint32_t)(SYSCFG_BM2EDCEN_RDC_DMA0_M_EN | BUS_MATRIX_2)) /*!< read data check DMA0 memory accesses */
#define BM2_RD_DATA_CHK_DMA0PERIPH                  ((uint32_t)(SYSCFG_BM2EDCEN_RDC_DMA0_P_EN | BUS_MATRIX_2)) /*!< read data check DMA0 peripheral accesses */
#define BM2_RD_DATA_CHK_DMA1MEM                     ((uint32_t)(SYSCFG_BM2EDCEN_RDC_DMA1_M_EN | BUS_MATRIX_2)) /*!< read data check DMA1 memory accesses */
#define BM2_RD_DATA_CHK_DMA1PERIPH                  ((uint32_t)(SYSCFG_BM2EDCEN_RDC_DMA1_P_EN | BUS_MATRIX_2)) /*!< read data check DMA1 peripheral accesses */
#define BM2_RD_DATA_CHK_HSM_BM2                     ((uint32_t)(SYSCFG_BM2EDCEN_RDC_HSM_BM2_EN| BUS_MATRIX_2)) /*!< read data check HSM BM2 */
#define BM2_RD_DATA_CHK_AHBP_CM7_0                  ((uint32_t)(SYSCFG_BM2EDCEN_RDC_AHBP0_EN  | BUS_MATRIX_2)) /*!< read data check Cortex-M7_0_AHBP */
#define BM2_RD_DATA_CHK_AHBP_CM7_1                  ((uint32_t)(SYSCFG_BM2EDCEN_RDC_AHBP1_EN  | BUS_MATRIX_2)) /*!< read data check Cortex-M7_1_AHBP */
#define BM2_WR_DATA_CHK_APB1                        ((uint32_t)(SYSCFG_BM2EDCEN_WDC_APB1_EN   | BUS_MATRIX_2)) /*!< write data check APB1 */
#define BM2_ADDR_CHK_APB1                           ((uint32_t)(SYSCFG_BM2EDCEN_ADDC_APB1_EN  | BUS_MATRIX_2)) /*!< address check APB1 */
#define BM2_WR_DATA_CHK_APB2                        ((uint32_t)(SYSCFG_BM2EDCEN_WDC_APB2_EN   | BUS_MATRIX_2)) /*!< write data check APB2 */
#define BM2_ADDR_CHK_APB2                           ((uint32_t)(SYSCFG_BM2EDCEN_ADDC_APB2_EN  | BUS_MATRIX_2)) /*!< address check APB2 */
#define BM2_WR_DATA_CHK_AHB1                        ((uint32_t)(SYSCFG_BM2EDCEN_WDC_AHB1_EN   | BUS_MATRIX_2)) /*!< write data check AHB1 */
#define BM2_ADDR_CHK_AHB1                           ((uint32_t)(SYSCFG_BM2EDCEN_ADDC_AHB1_EN  | BUS_MATRIX_2)) /*!< address check AHB1 */
#define BM2_WR_DATA_CHK_AHB2                        ((uint32_t)(SYSCFG_BM2EDCEN_WDC_AHB2_EN   | BUS_MATRIX_2)) /*!< write data check AHB2 */
#define BM2_ADDR_CHK_AHB2                           ((uint32_t)(SYSCFG_BM2EDCEN_ADDC_AHB2_EN  | BUS_MATRIX_2)) /*!< address check AHB2 */

/* bus check definition */
#define ENET_MEM_PORT_CHK                           SYSCFG_BUSCHKCFG_ENET_CHKEN           /*!< ENET mem port timeout and slaver ID check, only in GD32A714Axx /A72xAxx / A74xAxx */
#define HSM_PORT_CHK                                SYSCFG_BUSCHKCFG_HSM_CHKEN            /*!< HSM port timeout and slaver ID check */
#define DMA0MEM_PORT_CHK                            SYSCFG_BUSCHKCFG_DMA0M_CHKEN          /*!< DMA0 mem port timeout and slaver ID check */
#define DMA0PERIPH_PORT_CHK                         SYSCFG_BUSCHKCFG_DMA0P_CHKEN          /*!< DMA0 peri port timeout and slaver ID check */
#define DMA1MEM_PORT_CHK                            SYSCFG_BUSCHKCFG_DMA1M_CHKEN          /*!< DMA1 mem port timeout and slaver ID check */
#define DMA1PERIPH_PORT_CHK                         SYSCFG_BUSCHKCFG_DMA1P_CHKEN          /*!< DMA1 peri port timeout and slaver ID check */
#define AHBP_CM7_0_PORT_CHK                         SYSCFG_BUSCHKCFG_AHBP_CM7_0_CHKEN     /*!< CM7_0 AHBP port timeout and slaver ID check */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define AHBP_CM7_1_PORT_CHK                         SYSCFG_BUSCHKCFG_AHBP_CM7_1_CHKEN     /*!< CM7_1 AHBP port timeout and slaver ID check */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define AXIM_CM7_0_PORT_CHK                         SYSCFG_BUSCHKCFG_AXIM_CM7_0_CHKEN     /*!< CM7_0 AXIM port timeout and slaver ID check */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define AXIM_CM7_1_PORT_CHK                         SYSCFG_BUSCHKCFG_AXIM_CM7_1_CHKEN     /*!< CM7_1 AXIM port timeout and slaver ID check */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define DMA0MEM_SPLIT0_WIDGET_CHK                   SYSCFG_BUSCHKCFG_DMA0M_SPLT_WGT_CHKEN /*!< split0 widget of DMA0 mem redundant check */
#define DMA0PERIPH_SPLIT0_WIDGET_CHK                SYSCFG_BUSCHKCFG_DMA0P_SPLT_WGT_CHKEN /*!< split0 widget of DMA0 peri redundant check */
#define DMA1MEM_SPLIT0_WIDGET_CHK                   SYSCFG_BUSCHKCFG_DMA1M_SPLT_WGT_CHKEN /*!< split0 widget of DMA1 mem redundant check */
#define DMA1PERIPH_SPLIT0_WIDGET_CHK                SYSCFG_BUSCHKCFG_DMA1P_SPLT_WGT_CHKEN /*!< split0 widget of DMA1 peri redundant check */
#define HSM_SPLIT1_WIDGET_CHK                       SYSCFG_BUSCHKCFG_HSM_SPLT_WGT_CHKEN   /*!< split1 widget of HSM redundant check */
#define TCM_SPLIT1_WIDGET_CHK                       SYSCFG_BUSCHKCFG_TCM_SPLT_WGT_CHKEN   /*!< split1 widget of TCM SRAM redundant check */
#define HSM_H2H1_WIDGET_CHK                         SYSCFG_BUSCHKCFG_HSM_H2H1_WGT_CHKEN   /*!< H2H1 widget of HSM redundant check */
#define DMA0MEM_H2H0_WIDGET_CHK                     SYSCFG_BUSCHKCFG_DMA0M_H2H0_WGT_CHKEN /*!< H2H0 widget of DMA0 mem redundant check */
#define DMA0PERIPH_H2H0_WIDGET_CHK                  SYSCFG_BUSCHKCFG_DMA0P_H2H0_WGT_CHKEN /*!< H2H0 widget of DMA0 peri redundant check */
#define DMA1MEM_H2H0_WIDGET_CHK                     SYSCFG_BUSCHKCFG_DMA1M_H2H0_WGT_CHKEN /*!< H2H0 widget of DMA1 mem redundant check */
#define DMA1PERIPH_H2H0_WIDGET_CHK                  SYSCFG_BUSCHKCFG_DMA1P_H2H0_WGT_CHKEN /*!< H2H0 widget of DMA1 peri redundant check */
#define QSPI_H2H0_WIDGET_CHK                        SYSCFG_BUSCHKCFG_QSPI_H2H0_WGT_CHKEN  /*!< H2H0 widget of QSPI redundant check */
#define TCM_H2H0_WIDGET_CHK                         SYSCFG_BUSCHKCFG_TCM_H2H0_WGT_CHKEN   /*!< H2H0 widget of TCM redundant check */
#define ENET_WIDGET_CHK                             SYSCFG_BUSCHKCFG_ENET_WGT_CHKEN       /*!< ENET 1:1/1:2 widget check, only in GD32A714Axx /A72xAxx / A74xAxx */
#define TCM_WIDGET_CHK                              SYSCFG_BUSCHKCFG_TCM_WGT_CHKEN        /*!< TCM 1:1 widget check */
#define APB1_CHK                                    SYSCFG_BUSCHKCFG_APB1_CHKEN           /*!< APB1 redundant check */
#define APB2_CHK                                    SYSCFG_BUSCHKCFG_APB2_CHKEN           /*!< APB2 redundant check */
#define AHB1_CHK                                    SYSCFG_BUSCHKCFG_AHB1_CHKEN           /*!< AHB1 redundant check */
#define AHB2_CHK                                    SYSCFG_BUSCHKCFG_AHB2_CHKEN           /*!< AHB2 redundant check */

/* timer tigger source select definition */
#define TIMER_SMCFG_TRGSEL_NONE                    ((uint8_t)0x00U)                       /*!< trigger input is none */
#define TIMER_SMCFG_TRGSEL_ITI0                    ((uint8_t)0x01U)                       /*!< internal trigger input 0 */
#define TIMER_SMCFG_TRGSEL_ITI1                    ((uint8_t)0x02U)                       /*!< internal trigger input 1 */
#define TIMER_SMCFG_TRGSEL_ITI2                    ((uint8_t)0x03U)                       /*!< internal trigger input 2 */
#define TIMER_SMCFG_TRGSEL_ITI3                    ((uint8_t)0x04U)                       /*!< internal trigger input 3 */
#define TIMER_SMCFG_TRGSEL_ITI4                    ((uint8_t)0x05U)                       /*!< internal trigger input 4 */
#define TIMER_SMCFG_TRGSEL_ITI5                    ((uint8_t)0x06U)                       /*!< internal trigger input 5 */
#define TIMER_SMCFG_TRGSEL_ITI6                    ((uint8_t)0x07U)                       /*!< internal trigger input 6 */
#define TIMER_SMCFG_TRGSEL_ITI7                    ((uint8_t)0x08U)                       /*!< internal trigger input 7 */
#define TIMER_SMCFG_TRGSEL_ITI8                    ((uint8_t)0x09U)                       /*!< internal trigger input 8 */
#define TIMER_SMCFG_TRGSEL_ITI9                    ((uint8_t)0x0AU)                       /*!< internal trigger input 9 */
#define TIMER_SMCFG_TRGSEL_CI0F_ED                 ((uint8_t)0x15U)                       /*!< TI0 edge detector */
#define TIMER_SMCFG_TRGSEL_CI0FE0                  ((uint8_t)0x16U)                       /*!< filtered TIMER input 0 */
#define TIMER_SMCFG_TRGSEL_CI1FE1                  ((uint8_t)0x17U)                       /*!< filtered TIMER input 1 */
#define TIMER_SMCFG_TRGSEL_ETIFP                   ((uint8_t)0x18U)                       /*!< external trigger */
#define TIMER_SMCFG_TRGSEL_CI2FE2                  ((uint8_t)0x19U)                       /*!< filtered TIMER input 2 */
#define TIMER_SMCFG_TRGSEL_CI3FE3                  ((uint8_t)0x1AU)                       /*!< filtered TIMER input 3 */
#define TIMER_SMCFG_TRGSEL_MCI0FEM0                ((uint8_t)0x1BU)                       /*!< filtered output of multi mode channel 0 */
#define TIMER_SMCFG_TRGSEL_MCI1FEM1                ((uint8_t)0x1CU)                       /*!< filtered output of multi mode channel 1 */
#define TIMER_SMCFG_TRGSEL_MCI2FEM2                ((uint8_t)0x1DU)                       /*!< filtered output of multi mode channel 2 */
#define TIMER_SMCFG_TRGSEL_MCI3FEM3                ((uint8_t)0x1EU)                       /*!< filtered output of multi mode channel 3 */

/* timer tigger mode select definition */
#define TIMER_QUAD_DECODER_MODE0                   ((uint8_t)0x00U)                       /*!< quadrature decoder mode 0 */
#define TIMER_QUAD_DECODER_MODE1                   ((uint8_t)0x01U)                       /*!< quadrature decoder mode 1 */
#define TIMER_QUAD_DECODER_MODE2                   ((uint8_t)0x02U)                       /*!< quadrature decoder mode 2 */
#define TIMER_SLAVE_MODE_RESTART                   ((uint8_t)0x03U)                       /*!< restart mode */
#define TIMER_SLAVE_MODE_PAUSE                     ((uint8_t)0x04U)                       /*!< pause mode */
#define TIMER_SLAVE_MODE_EVENT                     ((uint8_t)0x05U)                       /*!< event mode */
#define TIMER_SLAVE_MODE_EXTERNAL0                 ((uint8_t)0x06U)                       /*!< external clock mode 0 */
#define TIMER_SLAVE_MODE_RESTART_EVENT             ((uint8_t)0x07U)                       /*!< restart + event mode */
#define TIMER_DECODER_MODE0                        ((uint8_t)0x08U)                       /*!< decoder mode 0 */
#define TIMER_DECODER_MODE1                        ((uint8_t)0x09U)                       /*!< decoder mode 1 */
#define TIMER_DECODER_MODE2                        ((uint8_t)0x0AU)                       /*!< decoder mode 2 */
#define TIMER_DECODER_MODE3                        ((uint8_t)0x0BU)                       /*!< decoder mode 3 */
#define TIMER_SLAVE_MODE_DISABLE                   ((uint8_t)0x0FU)                       /*!< slave mode disable */

#define SYSCFG_TIMERCFG0(syscfg_timerx)            REG32(SYSCFG + 0x100U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG1(syscfg_timerx)            REG32(SYSCFG + 0x104U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */
#define SYSCFG_TIMERCFG2(syscfg_timerx)            REG32(SYSCFG + 0x108U + (syscfg_timerx) * 0x0CU)/*!< TIMERx configuration register */

#define SYSCFG_TIMERCFG(syscfg_timerx)             ((uint32_t)(SYSCFG_BASE + 0x100U + (syscfg_timerx) * 0x0CU))

#define SYSCFG_TIMER0                              ((uint8_t)0x00U)                       /*!< SYSCFG TIMER0 */
#define SYSCFG_TIMER1                              ((uint8_t)0x01U)                       /*!< SYSCFG TIMER1 */
#define SYSCFG_TIMER2                              ((uint8_t)0x02U)                       /*!< SYSCFG TIMER2 */
#define SYSCFG_TIMER7                              ((uint8_t)0x03U)                       /*!< SYSCFG TIMER7 */
#define SYSCFG_TIMER19                             ((uint8_t)0x04U)                       /*!< SYSCFG TIMER19 */
#define SYSCFG_TIMER20                             ((uint8_t)0x05U)                       /*!< SYSCFG TIMER20 */
#define SYSCFG_TIMER60                             ((uint8_t)0x06U)                       /*!< SYSCFG TIMER60 */
#define SYSCFG_TIMER61                             ((uint8_t)0x07U)                       /*!< SYSCFG TIMER61 */
#define SYSCFG_TIMER62                             ((uint8_t)0x08U)                       /*!< SYSCFG TIMER62 */
#define SYSCFG_TIMER63                             ((uint8_t)0x09U)                       /*!< SYSCFG TIMER63 */

typedef enum {
    LOCKSTEP_MODE = 1U,                            /*!< the host core is in lockstep mode */
    SINGLE_CORE,                                   /*!< the host core is single core */
    DUAL_CORE,                                     /*!< the host core is dual core */
} syscfg_cpustat_enum;

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

#define NOT_EXTI_SOURCE_GPIO(exti_port)           (((exti_port) != EXTI_SOURCE_GPIOA) && ((exti_port) != EXTI_SOURCE_GPIOB) && \
                                                  ((exti_port) != EXTI_SOURCE_GPIOC) && ((exti_port) != EXTI_SOURCE_GPIOD) && \
                                                  ((exti_port) != EXTI_SOURCE_GPIOE) && ((exti_port) != EXTI_SOURCE_GPIOF) && \
                                                  ((exti_port) != EXTI_SOURCE_GPIOG) && ((exti_port) != EXTI_SOURCE_GPIOH) && \
                                                  ((exti_port) != EXTI_SOURCE_GPIOI) && ((exti_port) != EXTI_SOURCE_GPIOJ) && \
                                                  ((exti_port) != EXTI_SOURCE_GPIOK) && ((exti_port) != EXTI_SOURCE_GPIOL) && \
                                                  ((exti_port) != EXTI_SOURCE_GPIOM) && ((exti_port) != EXTI_SOURCE_GPION))

#define NOT_EXTI_SOURCE_PIN(exti_pin)             (((exti_pin) != EXTI_SOURCE_PIN0)  && ((exti_pin) != EXTI_SOURCE_PIN1) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN2)  && ((exti_pin) != EXTI_SOURCE_PIN3) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN4)  && ((exti_pin) != EXTI_SOURCE_PIN5) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN6)  && ((exti_pin) != EXTI_SOURCE_PIN7) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN8)  && ((exti_pin) != EXTI_SOURCE_PIN9) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN10) && ((exti_pin) != EXTI_SOURCE_PIN11) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN12) && ((exti_pin) != EXTI_SOURCE_PIN13) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN14) && ((exti_pin) != EXTI_SOURCE_PIN15))

#define NOT_EXTI_SOURCE_PIN_ADD(exti_pin)         (((exti_pin) != EXTI_SOURCE_PIN0)  && ((exti_pin) != EXTI_SOURCE_PIN1) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN2)  && ((exti_pin) != EXTI_SOURCE_PIN3) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN4)  && ((exti_pin) != EXTI_SOURCE_PIN5) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN6)  && ((exti_pin) != EXTI_SOURCE_PIN7) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN8)  && ((exti_pin) != EXTI_SOURCE_PIN9) && \
                                                  ((exti_pin) != EXTI_SOURCE_PIN10) && ((exti_pin) != EXTI_SOURCE_PIN11))

#define NOT_SYSCFG_I2C_FMP(i2c_fmp)               (((i2c_fmp) > 3U) || (0U == (i2c_fmp)))

#define NOT_STCM_INTERFACE_SEL(interface_sel)     (((interface_sel) != STCM_INTERFACE_JTAG) && ((interface_sel) != STCM_INTERFACE_APB))

#define NOT_CORE_TX_EVENTOUT_CM(core_txeven)      ((((core_txeven) & 0xFEFEFFFEU) != 0U) || (0U == (core_txeven)))

#define NOT_SYSCFG_TIMER_BKIN(timer_bkin)         (0U == (timer_bkin))

#define NOT_SYSCFG_TIMER_BRKIN_SEL(source_sel)    (((source_sel) != TIMER_BRKIN_SEL_GPIO)    && ((source_sel) != TIMER_BRKIN_SEL_TRIGSEL))

#if defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_CM7_NUM(core_num)                     (((core_num) != CM7_0) && ((core_num) != CM7_1))
#else 
#define NOT_CM7_NUM(core_num)                     (((core_num) != CM7_0))
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

#define NOT_CPU_HOLD_RELEASE(hold_release)        (((hold_release) != CPU_HOLD)    && ((hold_release) != CPU_RELEASE))

#define NOT_SYSCFG_PRIORITY(priority)             (((priority) != ROUND_ROBIN)      && ((priority) != AHBS_HIGHER_PRIO))

#define NOT_SYSCFG_RM_RESET(rm_reset)             (((rm_reset) != RM_SYSTEM_RESET)    && ((rm_reset) != RM_SUBSYSTEM_RESET))

#define NOT_MEMAEXCTL_PERIPH(periph_ctl)          ((((periph_ctl) & 0xFFCCCCFCU) != 0U) || (0U == (periph_ctl)))

#define NOT_BM_PERIPH(periph)                     (((periph) != BM1_RD_DATA_CHK_DMA0MEM)    && ((periph) != BM1_RD_DATA_CHK_DMA0PERIPH) && \
                                                  ((periph) != BM1_RD_DATA_CHK_DMA1MEM)    && ((periph) != BM1_RD_DATA_CHK_DMA1PERIPH) && \
                                                  ((periph) != BM1_RD_DATA_CHK_HSM_BM1)    && ((periph) != BM1_RD_DATA_CHK_ENET) && \
                                                  ((periph) != BM1_RD_DATA_CHK_CM7_0)      && ((periph) != BM1_RD_DATA_CHK_CM7_1) && \
                                                  ((periph) != BM1_WR_DATA_CHK_SRAM0)      && ((periph) != BM1_ADDR_CHK_SRAM0) && \
                                                  ((periph) != BM1_WR_DATA_CHK_SRAM1)      && ((periph) != BM1_ADDR_CHK_SRAM1) && \
                                                  ((periph) != BM1_WR_DATA_CHK_QSPI)       && ((periph) != BM1_ADDR_CHK_QSPI) && \
                                                  ((periph) != BM1_WR_DATA_CHK_FMC0)       && ((periph) != BM1_ADDR_CHK_FMC0) && \
                                                  ((periph) != BM1_WR_DATA_CHK_FMC1)       && ((periph) != BM1_ADDR_CHK_FMC1) && \
                                                  ((periph) != BM1_WR_DATA_CHK_FMC2)       && ((periph) != BM1_ADDR_CHK_FMC2) && \
                                                  ((periph) != BM1_WR_DATA_CHK_TCM)        && ((periph) != BM1_ADDR_CHK_TCM) && \
                                                  ((periph) != BM2_RD_DATA_CHK_DMA0MEM)    && ((periph) != BM2_RD_DATA_CHK_DMA0PERIPH) && \
                                                  ((periph) != BM2_RD_DATA_CHK_DMA1MEM)    && ((periph) != BM2_RD_DATA_CHK_DMA1PERIPH) && \
                                                  ((periph) != BM2_RD_DATA_CHK_HSM_BM2)    && ((periph) != BM2_RD_DATA_CHK_AHBP_CM7_0) && \
                                                  ((periph) != BM2_RD_DATA_CHK_AHBP_CM7_1) && ((periph) != BM2_WR_DATA_CHK_APB1) && \
                                                  ((periph) != BM2_ADDR_CHK_APB1)          && ((periph) != BM2_WR_DATA_CHK_APB2) && \
                                                  ((periph) != BM2_ADDR_CHK_APB2)          && ((periph) != BM2_WR_DATA_CHK_AHB1) && \
                                                  ((periph) != BM2_ADDR_CHK_AHB1)          && ((periph) != BM2_WR_DATA_CHK_AHB2) && \
                                                  ((periph) != BM2_ADDR_CHK_AHB2))

#if defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_BUS_CHK_PERIPH(periph)                ((((periph) & 0x84000001U) != 0U) || (0U == (periph)))
#elif defined (GD32A714X)
#define NOT_BUS_CHK_PERIPH(periph)                ((((periph) & 0x84000501U) != 0U) || (0U == (periph)))
#else
#define NOT_BUS_CHK_PERIPH(periph)                ((((periph) & 0x85000503U) != 0U) || (0U == (periph)))
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_SYSCFG_INT_CPU_NMI(cpu_interrupt)     ((((cpu_interrupt) & 0xFFC7FFC7U) != 0U) || (0U == (cpu_interrupt)))
#else
#define NOT_SYSCFG_INT_CPU_NMI(cpu_interrupt)     ((((cpu_interrupt) & 0xFFC7FFFFU) != 0U) || (0U == (cpu_interrupt)))
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

#define NOT_FPU_TCM_INT(fpu_tcm_int)              ((((fpu_tcm_int) & 0x03DFFFFFU) != 0U) || (0U == (fpu_tcm_int)))

#define NOT_FPU_TCM_INTFLAG(fpu_tcm_intflag)      ((((fpu_tcm_intflag) & 0xFFFF03BFU) != 0U) || (0U == (fpu_tcm_intflag)))

#define NOT_IR_CP_INT(ir_cp_int)                  (((ir_cp_int) != INTROUTER_CP_INT_0) && ((ir_cp_int) != INTROUTER_CP_INT_1) && \
                                                  ((ir_cp_int) != INTROUTER_CP_INT_2) && ((ir_cp_int) != INTROUTER_CP_INT_3))

#if defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_TMRERR_INT(tmrerr_int)                (((tmrerr_int) != TMRERR_INT_FMUNMI)   && ((tmrerr_int) != TMRERR_INT_CPEN) && \
                                                  ((tmrerr_int) != TMRERR_INT_MEMEXECR) && ((tmrerr_int) != TMRERR_INT_CPINT))
#else
#define NOT_TMRERR_INT(tmrerr_int)                (((tmrerr_int) != TMRERR_INT_FMUNMI)   && ((tmrerr_int) != TMRERR_INT_CPEN) && \
                                                  ((tmrerr_int) != TMRERR_INT_MEMEXECR))
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

#define NOT_NMI_FLAG(nmi_flag)                    ((((nmi_flag) & 0xFFFFFFC7U) != 0U) || (0U == (nmi_flag)))

#if defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_NMI_CLEAR_FLAG(nmi_flag)              (((nmi_flag) != SYSCFG_FLAG_CKMNMIERR) && ((nmi_flag) != SYSCFG_FLAG_CPU0_WR_ABORT) && \
                                                  ((nmi_flag) != SYSCFG_FLAG_CPU1_WR_ABORT))
#else
#define NOT_NMI_CLEAR_FLAG(nmi_flag)              (((nmi_flag) != SYSCFG_FLAG_CKMNMIERR) && ((nmi_flag) != SYSCFG_FLAG_CPU0_WR_ABORT))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#define NOT_CPU_CACHE_ERROR(cache_error)          (((cache_error) != CPU_CACHE_ERROR_DETECTION) && ((cache_error) != CPU_CACHE_ERROR_BANK))

#define NOT_CACHE_INFO(cache_info)                (((cache_info) != ICACHE_INFO) && ((cache_info) != DCACHE_INFO))

#define NOT_TCM_INFO(tcm_info)                    (((tcm_info) != ITCM_INFO) && ((tcm_info) != DTCM_INFO))

#define NOT_IR_CP_INT_FLAG(int_flag)              (((int_flag) != INTROUTER_CP_INT_FLAG_CP1_CP0) && ((int_flag) != INTROUTER_CP_INT_FLAG_CP0_CP0))

#define NOT_TMRERR_INT_FLAG(tmrerr_intflag)       (((tmrerr_intflag) != TMRERR_INT_FLAG_FMUNMI)   && ((tmrerr_intflag) != TMRERR_INT_FLAG_CPEN) && \
                                                  ((tmrerr_intflag) != TMRERR_INT_FLAG_MEMEXECR) && ((tmrerr_intflag) != TMRERR_INT_FLAG_CPINT))

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* initialization functions */
/* reset the SYSCFG registers */
void syscfg_deinit(void);

/* configure the GPIO pin as EXTI line */
void syscfg_exti_line_config(uint8_t exti_port, uint8_t exti_pin);
/* enable I2Cx(x=0,1) fast mode plus */
void syscfg_i2c_fast_mode_plus_enable(uint32_t i2c_fmp);
/* disable I2Cx(x=0,1) fast mode plus */
void syscfg_i2c_fast_mode_plus_disable(uint32_t i2c_fmp);

/* enable the tx EVENTOUT from CM_x */
void syscfg_tx_eventout_enable(uint32_t core_txeven);
/* disable the tx EVENTOUT from CM_x */
void syscfg_tx_eventout_disable(uint32_t core_txeven);

/* select TRIGSEL or GPIO as TIMER break input source */
void syscfg_timer_bkin_select(uint32_t timer_bkin, uint32_t source_sel);

/* CPU core held release set */
void syscfg_cpu_hold_release_set(uint8_t core_num, uint8_t hold_release);
/* CPU core AHB slave port priority set */
void syscfg_cpu_ahbs_priority_set(uint8_t core_num, uint8_t priority);

/* enable TCM wait state */
void syscfg_tcm_wait_state_enable(void);
/* disable TCM wait state */
void syscfg_tcm_wait_state_disable(void);
/* enable SRAM wait state */
void syscfg_sram_wait_state_enable(void);
/* disable SRAM wait state */
void syscfg_sram_wait_state_disable(void);

/* allow recovery mode on system or subsystem reset */
void syscfg_recovery_mode_allow(uint8_t rm_reset);
/* disable recovery mode on system or subsystem reset */
void syscfg_recovery_mode_disable(uint8_t rm_reset);

#if defined (GD32A72XX) || defined (GD32A74XX)
/* lock interrupt router core processor control register */
void syscfg_interrupt_router_reg_lock(void);
/* configure core processor as trusted core */
void syscfg_trusted_core_config_enable(uint8_t core_num);
/* configure core processor as non-trusted core */
void syscfg_trusted_core_config_disable(uint8_t core_num);
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
/* hard-lock the memory access execution control register */
void syscfg_mem_access_ctlreg_hard_lock(void);
/* soft-lock the memory access execution control register */
void syscfg_mem_access_ctlreg_soft_lock(void);
/* soft-unlock the memory access execution control register */
void syscfg_mem_access_ctlreg_soft_unlock(void);
/* allow memory access execution */
void syscfg_mem_access_allow(uint32_t periph_ctl);
/* disable memory access execution */
void syscfg_mem_access_disable(uint32_t periph_ctl);
/* enable peripheral bus matrix error detection function */
void syscfg_bus_matrix_error_detect_enable(uint32_t periph);
/* disable peripheral in bus matrix error detection function */
void syscfg_bus_matrix_error_detect_disable(uint32_t periph);
/* enable peripheral bus check function */
void syscfg_bus_check_enable(uint32_t periph);
/* disable peripheral bus check function */
void syscfg_bus_check_disable(uint32_t periph);

/* flag and interrupt functions */
/* enable the interrupt from the peripheral to the CPU NMI */
void syscfg_nmi_interrupt_enable(uint32_t cpu_interrupt);
/* disable the interrupt from the peripheral to the CPU NMI */
void syscfg_nmi_interrupt_disable(uint32_t cpu_interrupt);
/* enable FPU error and TCM write abort interrupt */
void syscfg_fpu_tcm_interrupt_enable(uint8_t core_num, uint32_t fpu_tcm_int);
/* disable FPU error and TCM write abort interrupt */
void syscfg_fpu_tcm_interrupt_disable(uint8_t core_num, uint32_t fpu_tcm_int);
#if defined (GD32A72XX) || defined (GD32A74XX)
/* enable interrupt router interrupt */
void syscfg_interrupt_router_interrupt_enable(uint8_t core_num, uint32_t ir_cp_int);
/* disable interrupt router interrupt */
void syscfg_interrupt_router_interrupt_disable(uint8_t core_num, uint32_t ir_cp_int);
#endif
/* enable TMR error interrupt */
void syscfg_tmr_error_interrupt_enable(uint32_t tmrerr_int);
/* disable TMR error interrupt */
void syscfg_tmr_error_interrupt_disable(uint32_t tmrerr_int);

/* get NMI interrupt flag */
FlagStatus syscfg_nmi_flag_get(uint32_t nmi_flag);
/* get FPU error and TCM write abort interrupt flag */
FlagStatus syscfg_fpu_tcm_interrupt_flag_get(uint8_t core_num, uint32_t fpu_tcm_intflag);
/* get CPU I-Cache error status */
uint32_t syscfg_icache_error_status_get(uint8_t core_num, uint32_t cache_error);
/* get CPU D-Cache error status */
uint32_t syscfg_dcache_error_status_get(uint8_t core_num, uint32_t cache_error);
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* get CPU platform status */
syscfg_cpustat_enum syscfg_cpu_platform_status_get(void);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
/* get HSM sub system has entered standby flag */
FlagStatus syscfg_hsm_enter_standby_flag_get(void);
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* get core processor ID */
uint32_t syscfg_cpu_id_get(void);
/* get core processor number */
uint8_t syscfg_cpu_number_get(void);
/* get CPU cache information */
uint32_t syscfg_cpu_cache_info_get(uint32_t cache_info);
/* get TCM size information */
uint32_t syscfg_cpu_tcm_size_get(uint32_t tcm_info);
/* get core processor configuration information */
uint32_t syscfg_cpu_config_info_get(void);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
/* get core 0 processor ID */
uint32_t syscfg_cpu0_id_get(void);
/* get core 0 processor number */
uint8_t syscfg_cpu0_number_get(void);
/* get CPU 0 cache information */
uint32_t syscfg_cpu0_cache_info_get(uint32_t cache_info);
/* get CPU 0 TCM size information */
uint32_t syscfg_cpu0_tcm_size_get(uint32_t tcm_info);
/* get core 0 processor configuration information */
uint32_t syscfg_cpu0_config_info_get(void);
#if defined (GD32A72XX) || defined (GD32A74XX)
/* get core 1 processor ID */
uint32_t syscfg_cpu1_id_get(void);
/* get core 1 processor number */
uint8_t syscfg_cpu1_number_get(void);
/* get CPU 1 cache information */
uint32_t syscfg_cpu1_cache_info_get(uint32_t cache_info);
/* get CPU 1 TCM size information */
uint32_t syscfg_cpu1_tcm_size_get(uint32_t tcm_info);
/* get core 1 processor configuration information */
uint32_t syscfg_cpu1_config_info_get(void);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined (GD32A72XX) || defined (GD32A74XX)
/* get interrupt router interrupt flag */
FlagStatus syscfg_interrupt_router_interrupt_flag_get(uint8_t core_num, uint32_t ir_cp_int, uint32_t int_flag);
/* clear interrupt router interrupt flag */
void syscfg_interrupt_router_interrupt_flag_clear(uint8_t core_num, uint32_t ir_cp_int, uint32_t int_flag);
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
/* get TMR error interrupt flag */
FlagStatus syscfg_tmr_error_flag_get(uint32_t tmrerr_intflag);
/* clear SYSCFG CPU flag */
void syscfg_cpu_flag_clear(uint32_t nmi_flag);
/* clear TMR error interrupt flag */
void syscfg_tmr_error_int_flag_clear(uint32_t tmrerr_intflag);

#endif /* GD32A7XX_SYSCFG_H */
