/*!
    \file    gd32a7xx_stcm.h
    \brief   definitions for the STCM
    
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

#ifndef GD32A7XX_STCM_H
#define GD32A7XX_STCM_H

#include "gd32a7xx.h"

/* STCM definitions */
#define STCM                          STCM_BASE                     /*!< STCM base address */

/* registers definitions */
#define STCM_TMRCS                    REG32((STCM) + 0x00000000U)   /*!< TMR control and status register */
#define STCM_BRCS                     REG32((STCM) + 0x00000004U)   /*!< BIST running control and status register */
#define STCM_WPK                      REG32((STCM) + 0x00000008U)   /*!< write protection key register */
#define STCM_CFG0                     REG32((STCM) + 0x0000000CU)   /*!< configuration register 0 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_CFG1                     REG32((STCM) + 0x00000010U)   /*!< configuration register 1 */
#define STCM_LBWDGT                   REG32((STCM) + 0x00000014U)   /*!< LBIST watchdog timer register */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_MBWDGT                   REG32((STCM) + 0x00000018U)   /*!< MBIST watchdog timer register */
#define STCM_BESTAT0                  REG32((STCM) + 0x0000001CU)   /*!< BIST error state register 0 */
#define STCM_BESTAT1                  REG32((STCM) + 0x00000020U)   /*!< BIST error state register 1 */
#define STCM_BEM                      REG32((STCM) + 0x00000024U)   /*!< BIST error mapping register */
#define STCM_BINTVL                   REG32((STCM) + 0x00000028U)   /*!< BIST interval register */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_LBCNTSTRAP               REG32((STCM) + 0x00000030U)   /*!< LBIST count timeout strap register */
#define STCM_LBPSTAT                  REG32((STCM) + 0x00000034U)   /*!< LBIST phase state register */
#define STCM_LBPE_STAT                REG32((STCM) + 0x00000038U)   /*!< LBIST phase end state register */
#define STCM_LBPEM                    REG32((STCM) + 0x0000003CU)   /*!< LBIST phase error mapping register */
#define STCM_LBPEINF                  REG32((STCM) + 0x00000040U)   /*!< LBIST phase error information register */
#define STCM_LBAITINTVL               REG32((STCM) + 0x00000044U)   /*!< LBIST AIT interval register */
#define STCM_LBPSCC                   REG32((STCM) + 0x00000048U)   /*!< LBIST peripheral shift clock control register */
#define STCM_LBPCFG                   REG32((STCM) + 0x00000060U)   /*!< LBIST phase configuration */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_MBALGSEL                 REG32((STCM) + 0x00000080U)   /*!< MBIST algorithm selection register */
#define STCM_MBPSTAT                  REG32((STCM) + 0x00000084U)   /*!< MBIST phase state register */
#define STCM_MBPE_STAT                REG32((STCM) + 0x00000088U)   /*!< MBIST phase end state register */
#define STCM_MBPEM                    REG32((STCM) + 0x0000008CU)   /*!< MBIST phase error mapping register */
#define STCM_MBLAUNCH                 REG32((STCM) + 0x00000090U)   /*!< MBIST phase launch register */
#define STCM_MB0PCFG                  REG32((STCM) + 0x000000A0U)   /*!< MBIST0 phase configuration register */
#define STCM_MB1PCFG                  REG32((STCM) + 0x000000A4U)   /*!< MBIST1 phase configuration register */
#define STCM_MB2PCFG                  REG32((STCM) + 0x000000A8U)   /*!< MBIST2 phase configuration register */
#define STCM_MB3PCFG                  REG32((STCM) + 0x000000ACU)   /*!< MBIST3 phase configuration register */
#define STCM_MB4PCFG                  REG32((STCM) + 0x000000B0U)   /*!< MBIST4 phase configuration register */
#define STCM_MB5PCFG                  REG32((STCM) + 0x000000B4U)   /*!< MBIST5 phase configuration register */
#define STCM_MB6PCFG                  REG32((STCM) + 0x000000B8U)   /*!< MBIST6 phase configuration register */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_MB7PCFG                  REG32((STCM) + 0x000000BCU)   /*!< MBIST7 phase configuration register */
#define STCM_MB8PCFG                  REG32((STCM) + 0x000000C0U)   /*!< MBIST8 phase configuration register */
#define STCM_MB9PCFG                  REG32((STCM) + 0x000000C4U)   /*!< MBIST9 phase configuration register */
#define STCM_MB10PCFG                 REG32((STCM) + 0x000000C8U)   /*!< MBIST10 phase configuration register */
#define STCM_MB11PCFG                 REG32((STCM) + 0x000000CCU)   /*!< MBIST11 phase configuration register */
#define STCM_MB12PCFG                 REG32((STCM) + 0x000000D0U)   /*!< MBIST12 phase configuration register */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_MBPCFG(mbistx)           REG32((STCM) + 0x000000A0U + (mbistx) * 0x4U)      /*!< MBISTx phase configuration register */

/* bits definitions */
/* STCM_TMRCS */
#define STCM_TMRCS_TMR_RUNBP_EN       BIT(0)                        /*!< TMR(Triple-Modular Redundancy) run BIST phase enable */
#define STCM_TMRCS_TMR_RUNBP          BIT(1)                        /*!< TMR(Triple-Modular Redundancy) state of run BIST phase */

/* STCM_BRCS */
#define STCM_BRCS_RUNBP               BIT(0)                        /*!< run BIST phase */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_BRCS_LBEPLLEN            BIT(8)                        /*!< LBIST executed with PLL enabled */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#define STCM_BRCS_MBEPLLEN            BIT(9)                        /*!< MBIST executed with PLL enabled */

/* STCM_WPK */
#define STCM_WPK_WPK                  BITS(0,31)                    /*!< STCM write protection key */

/* STCM_CFG0 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_CFG0_REF_DIV             BITS(0,2)                     /*!< reference clock divider */
#define STCM_CFG0_AOSEL               BIT(4)                        /*!< RAM or ROM selection */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_CFG0_WAP                 BIT(8)                        /*!< write access protection */
#define STCM_CFG0_MBWDG_DIV           BITS(16,18)                   /*!< MBIST watchdog clock divider */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_CFG0_LBWDG_DIV           BITS(20,22)                   /*!< LBIST watchdog clock divider */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_CFG0_FBPTR               BITS(25,30)                   /*!< first BIST pointer */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* STCM_CFG1 */
#define STCM_CFG1_LBAITPN             BITS(0,5)                     /*!< the AIT packet number of executing LBIST during phase */
#define STCM_CFG1_LBAITPADDR          BITS(21,31)                   /*!< the first AIT packet address of executing LBIST during phase */

/* STCM_LBWDGT */
#define STCM_LBWDGT_LBWDGT            BITS(0,31)                    /*!< LBIST watchdog timer */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* STCM_MBWDGT  */
#define STCM_MBWDGT_MBWDGT            BITS(0,31)                    /*!< MBIST watchdog timer */

/* STCM_BESTAT0 */
#define STCM_BESTAT0_PLLULK           BIT(0)                        /*!< PLL unlock error state */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_BESTAT0_LBWDG            BIT(1)                        /*!< LBIST watchdog error state */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_BESTAT0_INVPTR           BIT(2)                        /*!< invalid LBIST pointer error state */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_BESTAT0_BPSEL            BIT(3)                        /*!< BIST phase select error state */
#define STCM_BESTAT0_INVAITPADDR      BIT(4)                        /*!< invalid AIT packet address error state */
#define STCM_BESTAT0_MBWDG12          BIT(18)                       /*!< MBIST partition 12 watchdog error state */
#define STCM_BESTAT0_MBWDG11          BIT(19)                       /*!< MBIST partition 11 watchdog error state */
#define STCM_BESTAT0_MBWDG10          BIT(20)                       /*!< MBIST partition 10 watchdog error state */
#define STCM_BESTAT0_MBWDG9           BIT(21)                       /*!< MBIST partition 9 watchdog error state */
#define STCM_BESTAT0_MBWDG8           BIT(22)                       /*!< MBIST partition 8 watchdog error state */
#define STCM_BESTAT0_MBWDG7           BIT(23)                       /*!< MBIST partition 7 watchdog error state */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_BESTAT0_MBWDG6           BIT(24)                       /*!< MBIST partition 6 watchdog error state */
#define STCM_BESTAT0_MBWDG5           BIT(25)                       /*!< MBIST partition 5 watchdog error state */
#define STCM_BESTAT0_MBWDG4           BIT(26)                       /*!< MBIST partition 4 watchdog error state */
#define STCM_BESTAT0_MBWDG3           BIT(27)                       /*!< MBIST partition 3 watchdog error state */
#define STCM_BESTAT0_MBWDG2           BIT(28)                       /*!< MBIST partition 2 watchdog error state */
#define STCM_BESTAT0_MBWDG1           BIT(29)                       /*!< MBIST partition 1 watchdog error state */
#define STCM_BESTAT0_MBWDG0           BIT(30)                       /*!< MBIST partition 0 watchdog error state */
#define STCM_BESTAT0_MBWDGEG          BIT(31)                       /*!< MBIST watchdog global error state */

/* STCM_BESTAT1 */
#define STCM_BESTAT1_SP0              BIT(0)                        /*!< SMART protocol error state 0 */
#define STCM_BESTAT1_SP1              BIT(1)                        /*!< SMART protocol error state 1 */
#define STCM_BESTAT1_SP2              BIT(2)                        /*!< SMART protocol error state 2 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_BESTAT1_AITP0            BIT(4)                        /*!< AIT protocol error state 0 */
#define STCM_BESTAT1_AITP1            BIT(5)                        /*!< AIT protocol error state 1 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_BESTAT1_RES              BIT(30)                       /*!< recoverable error state */
#define STCM_BESTAT1_UES              BIT(31)                       /*!< unrecoverable error state */

/* STCM_BEM */
#define STCM_BEM_PLLUNLK              BIT(0)                        /*!< PLL unlock unrecoverable error mapping */
#define STCM_BEM_MBWDG                BIT(1)                        /*!< MBIST watchdog unrecoverable error mapping */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_BEM_LBWDG                BIT(2)                        /*!< LBIST watchdog unrecoverable error mapping */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_BEM_ENG                  BIT(3)                        /*!< Engine unrecoverable error mapping */
#define STCM_BEM_INVPTR               BIT(4)                        /*!< invalid pointer unrecoverable error mapping */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_BEM_BPSEL                BIT(5)                        /*!< BIST partition selection unrecoverable error mapping */
#define STCM_BEM_INVAITADDR           BIT(6)                        /*!< invalid AIT address unrecoverable error mapping */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* STCM_BINTVL */
#define STCM_BINTVL_INTVL             BITS(0,31)                    /*!< BIST phase interval */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* STCM_LBCNTSTRAP */
#define STCM_LBCNTSTRAP_LB_CNT_STRAP  BITS(0,7)                     /*!< LBIST timeout count strap */

/* STCM_LBPSTAT */
#define STCM_LBPSTAT_LBP              BITS(0,1)                     /*!< LBIST phase state */

/* STCM_LBPE_STAT */
#define STCM_LBPE_STAT_LBPEF          BITS(0,1)                     /*!< LBIST phase end flag */

/* STCM_LBPEM */
#define STCM_LBPEM_LBP                BIT(0)                        /*!< LBIST phase unreconverable error mapping */

/* STCM_LBPEINF */
#define STCM_LBPEINF_AIT_STAT         BITS(0,3)                     /*!< these bits stored the state of AIT when LBIST execution result is failed or timeout */
#define STCM_LBPEINF_LBPEADDR         BITS(16,26)                   /*!< LBIST phase0 error address */

/* STCM_BINTVL */
#define STCM_LBAITINTVL_INTVL         BITS(0,31)                    /*!< LBIST AIT packet interval */

/* STCM_LBPSCC */
#define STCM_LBPSCC_PSCC_STEP         BITS(4,6)                     /*!< peripheral shift clock control step size */
#define STCM_LBPSCC_PSCC_SEN          BIT(7)                        /*!< peripheral shift clock control start enable */
#define STCM_LBPSCC_PSCC_EEN          BIT(8)                        /*!< peripheral shift clock control end enable */

/* STCM_LBPCFG */
#define STCM_LBPCFG_SHR               BITS(13,15)                   /*!< shift rate */
#define STCM_LBPCFG_NXTPTR            BITS(25,30)                   /*!< next LBIST or MBIST pointer */
#define STCM_LBPCFG_SPM               BIT(31)                       /*!< serial or parallel mode */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* STCM_MBALGSEL */
#define STCM_MBALGSEL_MBALG0          BIT(0)                        /*!< MBIST algorithm 0 selection */
#define STCM_MBALGSEL_MBALG1          BIT(1)                        /*!< MBIST algorithm 1 selection */
#define STCM_MBALGSEL_MBALG2          BIT(2)                        /*!< MBIST algorithm 2 selection */
#define STCM_MBALGSEL_MBALG3          BIT(3)                        /*!< MBIST algorithm 3 selection */
#define STCM_MBALGSEL_MBALG4          BIT(4)                        /*!< MBIST algorithm 4 selection */
#define STCM_MBALGSEL_MBALG5          BIT(5)                        /*!< MBIST algorithm 5 selection */
#define STCM_MBALGSEL_MBALG6          BIT(6)                        /*!< MBIST algorithm 6 selection */
#define STCM_MBALGSEL_MBALG7          BIT(7)                        /*!< MBIST algorithm 7 selection */
#define STCM_MBALGSEL_MBALG8          BIT(8)                        /*!< MBIST algorithm 8 selection */
#define STCM_MBALGSEL_MBALG9          BIT(9)                        /*!< MBIST algorithm 9 selection */
#define STCM_MBALGSEL_MBALG10         BIT(10)                       /*!< MBIST algorithm 10 selection */
#define STCM_MBALGSEL_MBALG11         BIT(11)                       /*!< MBIST algorithm 11 selection */
#define STCM_MBALGSEL_MBALG12         BIT(12)                       /*!< MBIST algorithm 12 selection */
#define STCM_MBALGSEL_MBALG13         BIT(13)                       /*!< MBIST algorithm 13 selection */

/* STCM_MBPSTAT */
#define STCM_MBPSTAT_MBP0             BITS(0,1)                     /*!< MBIST partition 0 state */
#define STCM_MBPSTAT_MBP1             BITS(2,3)                     /*!< MBIST partition 1 state */
#define STCM_MBPSTAT_MBP2             BITS(4,5)                     /*!< MBIST partition 2 state */
#define STCM_MBPSTAT_MBP3             BITS(6,7)                     /*!< MBIST partition 3 state */
#define STCM_MBPSTAT_MBP4             BITS(8,9)                     /*!< MBIST partition 4 state */
#define STCM_MBPSTAT_MBP5             BITS(10,11)                   /*!< MBIST partition 5 state */
#define STCM_MBPSTAT_MBP6             BITS(12,13)                   /*!< MBIST partition 6 state */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_MBPSTAT_MBP7             BITS(14,15)                   /*!< MBIST partition 7 state */
#define STCM_MBPSTAT_MBP8             BITS(16,17)                   /*!< MBIST partition 8 state */
#define STCM_MBPSTAT_MBP9             BITS(18,19)                   /*!< MBIST partition 9 state */
#define STCM_MBPSTAT_MBP10            BITS(20,21)                   /*!< MBIST partition 10 state */
#define STCM_MBPSTAT_MBP11            BITS(22,23)                   /*!< MBIST partition 11 state */
#define STCM_MBPSTAT_MBP12            BITS(24,25)                   /*!< MBIST partition 12 state */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* STCM_MBPE_STAT */
#define STCM_MBPE_STAT_MBP0EF         BITS(0,1)                     /*!< MBIST partition 0 end flag */
#define STCM_MBPE_STAT_MBP1EF         BITS(2,3)                     /*!< MBIST partition 1 end flag */
#define STCM_MBPE_STAT_MBP2EF         BITS(4,5)                     /*!< MBIST partition 2 end flag */
#define STCM_MBPE_STAT_MBP3EF         BITS(6,7)                     /*!< MBIST partition 3 end flag */
#define STCM_MBPE_STAT_MBP4EF         BITS(8,9)                     /*!< MBIST partition 4 end flag */
#define STCM_MBPE_STAT_MBP5EF         BITS(10,11)                   /*!< MBIST partition 5 end flag */
#define STCM_MBPE_STAT_MBP6EF         BITS(12,13)                   /*!< MBIST partition 6 end flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_MBPE_STAT_MBP7EF         BITS(14,15)                   /*!< MBIST partition 7 end flag */
#define STCM_MBPE_STAT_MBP8EF         BITS(16,17)                   /*!< MBIST partition 8 end flag */
#define STCM_MBPE_STAT_MBP9EF         BITS(18,19)                   /*!< MBIST partition 9 end flag */
#define STCM_MBPE_STAT_MBP10EF        BITS(20,21)                   /*!< MBIST partition 10 end flag */
#define STCM_MBPE_STAT_MBP11EF        BITS(22,23)                   /*!< MBIST partition 11 end flag */
#define STCM_MBPE_STAT_MBP12EF        BITS(24,25)                   /*!< MBIST partition 12 end flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* STCM_MBPEM */
#define STCM_MBPEM_MBP0               BIT(0)                        /*!< MBIST partition 0 unrecoverable error mapping */
#define STCM_MBPEM_MBP1               BIT(1)                        /*!< MBIST partition 1 unrecoverable error mapping */
#define STCM_MBPEM_MBP2               BIT(2)                        /*!< MBIST partition 2 unrecoverable error mapping */
#define STCM_MBPEM_MBP3               BIT(3)                        /*!< MBIST partition 3 unrecoverable error mapping */
#define STCM_MBPEM_MBP4               BIT(4)                        /*!< MBIST partition 4 unrecoverable error mapping */
#define STCM_MBPEM_MBP5               BIT(5)                        /*!< MBIST partition 5 unrecoverable error mapping */
#define STCM_MBPEM_MBP6               BIT(6)                        /*!< MBIST partition 6 unrecoverable error mapping */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_MBPEM_MBP7               BIT(7)                        /*!< MBIST partition 7 unrecoverable error mapping */
#define STCM_MBPEM_MBP8               BIT(8)                        /*!< MBIST partition 8 unrecoverable error mapping */
#define STCM_MBPEM_MBP9               BIT(9)                        /*!< MBIST partition 9 unrecoverable error mapping */
#define STCM_MBPEM_MBP10              BIT(10)                       /*!< MBIST partition 10 unrecoverable error mapping */
#define STCM_MBPEM_MBP11              BIT(11)                       /*!< MBIST partition 11 unrecoverable error mapping */
#define STCM_MBPEM_MBP12              BIT(12)                       /*!< MBIST partition 12 unrecoverable error mapping */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* STCM_MBLAUNCH */
#define STCM_MBLAUNCH_MBLAUNCH        BITS(0,2)                     /*!< MBIST launch configuration */

/* STCM_MBxPCFG */
#define STCM_MBXPCFG_MBEN             BIT(0)                        /*!< MBIST partition x(x = 0~12) execute enable */
#define STCM_MBXPCFG_FAST_MOD         BIT(1)                        /*!< MBIST partition x(x = 0~12) executed in fast mode */
#define STCM_MBXPCFG_NXTPTR           BITS(25,30)                   /*!< next LBIST or MBIST pointer */
#define STCM_MBXPCFG_SPM              BIT(31)                       /*!< serial or parallel mode */

/* constants definitions */
typedef enum {
    STCM_NOTCOMPLETE     = 0U,                                      /*!< BIST execution not yet completed */
    STCM_FAILED          = 1U,                                      /*!< BIST execution failed */
    STCM_SUCCESSFUL      = 2U,                                      /*!< BIST execution successful  */
    STCM_ENDERROR        = 3U,                                      /*!< BIST execution end error */
    STCM_RESULTERROR     = 4U                                       /*!< BIST execution result error */
} stcm_bist_state;

/* TMR state */
typedef enum {
    STCM_TMR_NORMAL      = 0U,                                      /*!< TMR(Triple-Modular Redundancy) run BIST phase normal state */
    STCM_TMR_ERR         = 1U                                       /*!< TMR(Triple-Modular Redundancy) run BIST phase error state */
} stcm_tmr_state;

/* STCM error code */
typedef enum {
    BESTAT0_PLLULK          =    0U  << 1U | 0U,                    /*!< PLLULK error extract code*/
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    BESTAT0_LBWDG           =    1U  << 1U | 0U,                    /*!< LBWDG error extract code*/
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    BESTAT0_INVPTR          =    2U  << 1U | 0U,                    /*!< INVPTR error extract code*/
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    BESTAT0_BPSEL           =    3U  << 1U | 0U,                    /*!< BPSEL error extract code*/
    BESTAT0_INVAITPADDR     =    4U  << 1U | 0U,                    /*!< INVAITPADDR error extract code*/
    BESTAT0_MBWDG12         =    18U << 1U | 0U,                    /*!< MBWDG12 error extract code*/
    BESTAT0_MBWDG11         =    19U << 1U | 0U,                    /*!< MBWDG11 error extract code*/
    BESTAT0_MBWDG10         =    20U << 1U | 0U,                    /*!< MBWDG10 error extract code*/
    BESTAT0_MBWDG9          =    21U << 1U | 0U,                    /*!< MBWDG9 error extract code*/
    BESTAT0_MBWDG8          =    22U << 1U | 0U,                    /*!< MBWDG8 error extract code*/
    BESTAT0_MBWDG7          =    23U << 1U | 0U,                    /*!< MBWDG7 error extract code*/
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    BESTAT0_MBWDG6          =    24U << 1U | 0U,                    /*!< MBWDG6 error extract code*/
    BESTAT0_MBWDG5          =    25U << 1U | 0U,                    /*!< MBWDG5 error extract code*/
    BESTAT0_MBWDG4          =    26U << 1U | 0U,                    /*!< MBWDG4 error extract code*/
    BESTAT0_MBWDG3          =    27U << 1U | 0U,                    /*!< MBWDG3 error extract code*/
    BESTAT0_MBWDG2          =    28U << 1U | 0U,                    /*!< MBWDG2 error extract code*/
    BESTAT0_MBWDG1          =    29U << 1U | 0U,                    /*!< MBWDG1 error extract code*/
    BESTAT0_MBWDG0          =    30U << 1U | 0U,                    /*!< MBWDG0 error extract code*/
    BESTAT0_MBWDGEG         =    31U << 1U | 0U,                    /*!< MBWDGEG error extract code*/
    BESTAT1_SP0             =    0U  << 1U | 1U,                    /*!< SP0 error extract code*/
    BESTAT1_SP1             =    1U  << 1U | 1U,                    /*!< SP1 error extract code*/
    BESTAT1_SP2             =    2U  << 1U | 1U,                    /*!< SP2 error extract code*/
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    BESTAT1_AITP0           =    4U  << 1U | 1U,                    /*!< AITP0 error extract code*/
    BESTAT1_AITP1           =    5U  << 1U | 1U,                    /*!< AITP1 error extract code*/
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    BESTAT1_RECOV           =    30U << 1U | 1U,                    /*!< RECOV error extract code*/
    BESTAT1_UNRECOV         =    31U << 1U | 1U                     /*!< UNRECOV error extract code*/
} stcm_error_code_enum;

/* STCM_BEM */
#define STCM_BEM_PLLUNLK_ERR               0U                        /*!< PLL unlock unrecoverable error mapping bit position */
#define STCM_BEM_MBWDG_ERR                 1U                        /*!< MBIST watchdog unrecoverable error mapping bit position */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_BEM_LBWDG_ERR                 2U                        /*!< LBIST watchdog unrecoverable error mapping bit position */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_BEM_ENG_ERR                   3U                        /*!< engine unrecoverable error mapping bit position */
#define STCM_BEM_INVP_ERR                  4U                        /*!< invalid pointer unrecoverable error mapping bit position */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_BEM_BPSEL_ERR                 5U                        /*!< BIST partition selection unrecoverable error mapping bit position */
#define STCM_BEM_INVAITADDR_ERR            6U                        /*!< invalid AIT address unrecoverable error mapping bit position */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
                                           
#define STCM_RUNBP_TMRDIS                  ((uint32_t)0x00000000U)
#define STCM_RUNBP_TMREN                   STCM_TMRCS_TMR_RUNBP_EN
                                           
#define STCM_UNLOCK_KEY_LOOP0              ((uint8_t)0x00U)
#define STCM_UNLOCK_KEY_LOOP0_KEY0         ((uint32_t)0x8E6B2508U)
#define STCM_UNLOCK_KEY_LOOP0_KEY1         ((uint32_t)0xAC4B130AU)
#define STCM_UNLOCK_KEY_LOOP1              ((uint8_t)0x01U)
#define STCM_UNLOCK_KEY_LOOP1_KEY0         ((uint32_t)0x9F7C3619U)
#define STCM_UNLOCK_KEY_LOOP1_KEY1         ((uint32_t)0xBD5C241BU)
#define STCM_UNLOCK_KEY_LOOP2              ((uint8_t)0x02U)
#define STCM_UNLOCK_KEY_LOOP2_KEY0         ((uint32_t)0xA08D472AU)
#define STCM_UNLOCK_KEY_LOOP2_KEY1         ((uint32_t)0xCE6D352CU)

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define LBISTWDGDIV(regval)                (BITS(20,22) & ((uint32_t)(regval) << 20U))
#define STCM_LBISTWDG_CLKDIV1              LBISTWDGDIV(0)
#define STCM_LBISTWDG_CLKDIV4              LBISTWDGDIV(1)
#define STCM_LBISTWDG_CLKDIV16             LBISTWDGDIV(2)
#define STCM_LBISTWDG_CLKDIV64             LBISTWDGDIV(3)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#define MBISTWDGDIV(regval)                (BITS(16,18) & ((uint32_t)(regval) << 16U))
#define STCM_MBISTWDG_CLKDIV1              MBISTWDGDIV(0)
#define STCM_MBISTWDG_CLKDIV4              MBISTWDGDIV(1)
#define STCM_MBISTWDG_CLKDIV16             MBISTWDGDIV(2)
#define STCM_MBISTWDG_CLKDIV64             MBISTWDGDIV(3)

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_AIT_ROM                       ((uint32_t)0x00000000U)
#define STCM_AIT_RAM                       STCM_CFG0_AOSEL

#define AITCLKDIV(regval)                  (BITS(0,2) & ((uint32_t)(regval) << 0U))
#define STCM_AITCLK_DIV1                   AITCLKDIV(0)
#define STCM_AITCLK_DIV2                   AITCLKDIV(1)
#define STCM_AITCLK_DIV10                  AITCLKDIV(2)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#define STCM_SERIAL_MODE                   ((uint32_t)0x00000000U)
#define STCM_PARALLEL_MODE                 ((uint32_t)0x80000000U)
                                           
#define STCM_END_NOTCOMPLETE               ((uint32_t)0x00000000U)
#define STCM_END_FINISH                    ((uint32_t)0x00000003U)
#define STCM_RESULT_FAILED                 ((uint32_t)0x00000000U)
#define STCM_RESULE_SUCCESSFUL             ((uint32_t)0x00000003U)
                                           
#define STCM_ERROR_RECOVERABLE             ((uint32_t)0x00000000U)
#define STCM_ERROR_UNRECOVERABLE           ((uint32_t)0x00000001U)
                                           
#define STCM_PTR_MBIST0                    ((uint32_t)0x00000000U)
#define STCM_PTR_MBIST1                    ((uint32_t)0x02000000U)
#define STCM_PTR_MBIST2                    ((uint32_t)0x04000000U)
#define STCM_PTR_MBIST3                    ((uint32_t)0x06000000U)
#define STCM_PTR_MBIST4                    ((uint32_t)0x08000000U)
#define STCM_PTR_MBIST5                    ((uint32_t)0x0A000000U)
#define STCM_PTR_MBIST6                    ((uint32_t)0x0C000000U)
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_PTR_MBIST7                    ((uint32_t)0x0E000000U)
#define STCM_PTR_MBIST8                    ((uint32_t)0x10000000U)
#define STCM_PTR_MBIST9                    ((uint32_t)0x12000000U)
#define STCM_PTR_MBIST10                   ((uint32_t)0x14000000U)
#define STCM_PTR_MBIST11                   ((uint32_t)0x16000000U)
#define STCM_PTR_MBIST12                   ((uint32_t)0x18000000U)
#define STCM_PTR_LBIST                     ((uint32_t)0x40000000U)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define STCM_PTR_NIL                       ((uint32_t)0x7E000000U)

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define SHIFTRATE(regval)                  (BITS(13,15) & ((uint32_t)(regval) << 13U))
#define STCM_LBIST_SHR_FULL                SHIFTRATE(0)
#define STCM_LBIST_SHR_DIV2                SHIFTRATE(1)
#define STCM_LBIST_SHR_DIV3                SHIFTRATE(2)
#define STCM_LBIST_SHR_DIV4                SHIFTRATE(3)
#define STCM_LBIST_SHR_DIV5                SHIFTRATE(4)
#define STCM_LBIST_SHR_DIV6                SHIFTRATE(5)
#define STCM_LBIST_SHR_DIV7                SHIFTRATE(6)
#define STCM_LBIST_SHR_DIV8                SHIFTRATE(7)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#define MBIST_ALGO_AVAILABLE_MASK          BITS(0,13)
#define MBIST_ALGO_0                       STCM_MBALGSEL_MBALG0
#define MBIST_ALGO_1                       STCM_MBALGSEL_MBALG1
#define MBIST_ALGO_2                       STCM_MBALGSEL_MBALG2
#define MBIST_ALGO_3                       STCM_MBALGSEL_MBALG3
#define MBIST_ALGO_4                       STCM_MBALGSEL_MBALG4
#define MBIST_ALGO_5                       STCM_MBALGSEL_MBALG5
#define MBIST_ALGO_6                       STCM_MBALGSEL_MBALG6
#define MBIST_ALGO_7                       STCM_MBALGSEL_MBALG7
#define MBIST_ALGO_8                       STCM_MBALGSEL_MBALG8
#define MBIST_ALGO_9                       STCM_MBALGSEL_MBALG9
#define MBIST_ALGO_10                      STCM_MBALGSEL_MBALG10
#define MBIST_ALGO_11                      STCM_MBALGSEL_MBALG11
#define MBIST_ALGO_12                      STCM_MBALGSEL_MBALG12
#define MBIST_ALGO_13                      STCM_MBALGSEL_MBALG13
                                           
/* port control value definitions */       
#define MBLAUNCH(regval)                   (BITS(0,2) & ((uint32_t)(regval) << 0U))
#define STCM_MBLAUNCH_NOP                  MBLAUNCH(0)
#define STCM_MBLAUNCH_RUNONLY              MBLAUNCH(1)
#define STCM_MBLAUNCH_PROGONLY             MBLAUNCH(4)
#define STCM_MBLAUNCH_RUN_PROG             MBLAUNCH(5)
                                           
#define STCM_MBIST_DIS                     ((uint32_t)0x00000000U)
#define STCM_MBIST_EN                      STCM_MBXPCFG_MBEN
                                           
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_MBIST_MAX_NUM                 12U
#else
#define STCM_MBIST_MAX_NUM                 6U
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define STCM_LBIST_SHIFTCLK_STEP_MAX       8U
#define STCM_LBIST_SHIFTCLK_STEP_MIN       1U
                                           
#define STCM_LBIST_ENG_TIMESTRAP_MAX       0xFFU
                                           
#define STCM_LBIST_AIT_PACKET_NUM_0        0U
#define STCM_LBIST_AIT_PACKET_NUM_1        1U
#define STCM_LBIST_AIT_PACKET_NUM_2        2U
#define STCM_LBIST_AIT_PACKET_NUM_3        3U
#define STCM_LBIST_AIT_PACKET_NUM_MAX      4U
#define STCM_LBIST_AIT_PACKET_BYTES        384U

/* port control value definitions */       
#define AIT_PACKET_ADDR(packet_index)      (STCM_CFG1_LBAITPADDR & (((uint32_t)(packet_index) * STCM_LBIST_AIT_PACKET_BYTES) << 21U))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#ifdef FW_DEBUG_ERR_REPORT
#define NOT_UNLOCK_KEY_LOOP_INDEX(key_loop_index)         ((key_loop_index) > STCM_UNLOCK_KEY_LOOP2 )

#define NOT_BIST_PLL_ENABLE_CFG(bistpllen)                (((bistpllen) != (uint32_t)DISABLE) && ((bistpllen) != (uint32_t)ENABLE))

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_BIST_FIRST_PTR(ptr)                           (((ptr) != STCM_PTR_MBIST0) && ((ptr)  != STCM_PTR_MBIST1)  && ((ptr)  != STCM_PTR_MBIST2)  && \
                                                           ((ptr) != STCM_PTR_MBIST3) && ((ptr)  != STCM_PTR_MBIST4)  && ((ptr)  != STCM_PTR_MBIST5)  && \
                                                           ((ptr) != STCM_PTR_MBIST6) && ((ptr)  != STCM_PTR_MBIST7)  && ((ptr)  != STCM_PTR_MBIST8)  && \
                                                           ((ptr) != STCM_PTR_MBIST9) && ((ptr)  != STCM_PTR_MBIST10) && ((ptr)  != STCM_PTR_MBIST11) && \
                                                           ((ptr) != STCM_PTR_MBIST12) && ((ptr) != STCM_PTR_LBIST)   && ((ptr)  != STCM_PTR_NIL))
#else
#define NOT_BIST_FIRST_PTR(ptr)                           (((ptr) != STCM_PTR_MBIST0) && ((ptr)  != STCM_PTR_MBIST1)  && ((ptr)  != STCM_PTR_MBIST2)  && \
                                                           ((ptr) != STCM_PTR_MBIST3) && ((ptr)  != STCM_PTR_MBIST4)  && ((ptr)  != STCM_PTR_MBIST5)  && \
                                                           ((ptr) != STCM_PTR_MBIST6) && ((ptr)  != STCM_PTR_NIL))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_BIST_GENERAL_ERROR_CODE(general_err_code)     (((general_err_code) != STCM_BEM_PLLUNLK_ERR) && ((general_err_code) != STCM_BEM_MBWDG_ERR) && \
                                                           ((general_err_code) != STCM_BEM_LBWDG_ERR)   && ((general_err_code) != STCM_BEM_ENG_ERR)   && \
                                                           ((general_err_code) != STCM_BEM_INVP_ERR)    && ((general_err_code) != STCM_BEM_BPSEL_ERR) && \
                                                           ((general_err_code) != STCM_BEM_INVAITADDR_ERR))
#else
#define NOT_BIST_GENERAL_ERROR_CODE(general_err_code)     (((general_err_code) != STCM_BEM_PLLUNLK_ERR) && ((general_err_code) != STCM_BEM_MBWDG_ERR) && \
                                                           ((general_err_code) != STCM_BEM_ENG_ERR)     && ((general_err_code) != STCM_BEM_INVP_ERR)   )
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#define NOT_MBIST_EXECUTION_MODE(spm)                     (((spm) != STCM_SERIAL_MODE) && ((spm) != STCM_PARALLEL_MODE))

#define NOT_ERROR_MAPPING_CFG(unrecoverable)              (((unrecoverable) != STCM_ERROR_RECOVERABLE) && ((unrecoverable) != STCM_ERROR_UNRECOVERABLE))

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_MBIST_NEXT_PTR(nextptr)                       (((nextptr) != STCM_PTR_MBIST0)  && ((nextptr) != STCM_PTR_MBIST1)  && ((nextptr) != STCM_PTR_MBIST2)  && \
                                                           ((nextptr) != STCM_PTR_MBIST3)  && ((nextptr) != STCM_PTR_MBIST4)  && ((nextptr) != STCM_PTR_MBIST5)  && \
                                                           ((nextptr) != STCM_PTR_MBIST6)  && ((nextptr) != STCM_PTR_MBIST7)  && ((nextptr) != STCM_PTR_MBIST8)  && \
                                                           ((nextptr) != STCM_PTR_MBIST9)  && ((nextptr) != STCM_PTR_MBIST10) && ((nextptr) != STCM_PTR_MBIST11) && \
                                                           ((nextptr) != STCM_PTR_MBIST12) && ((nextptr) != STCM_PTR_LBIST)   && ((nextptr) != STCM_PTR_NIL))
#else
#define NOT_MBIST_NEXT_PTR(nextptr)                       (((nextptr) != STCM_PTR_MBIST0)  && ((nextptr) != STCM_PTR_MBIST1)  && ((nextptr) != STCM_PTR_MBIST2)  && \
                                                           ((nextptr) != STCM_PTR_MBIST3)  && ((nextptr) != STCM_PTR_MBIST4)  && ((nextptr) != STCM_PTR_MBIST5)  && \
                                                           ((nextptr) != STCM_PTR_MBIST6)  && ((nextptr) != STCM_PTR_NIL))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
                                                           
#define NOT_MBIST_ENABLE_CFG(mben)                        (((mben) != STCM_MBIST_DIS) && ((mben) != STCM_MBIST_EN))
                                                          
#define NOT_MBIST_WDG_CLKDIV(clkdiv)                      (((clkdiv) != STCM_MBISTWDG_CLKDIV1)  && ((clkdiv) != STCM_MBISTWDG_CLKDIV4) && \
                                                           ((clkdiv) != STCM_MBISTWDG_CLKDIV16) && ((clkdiv) != STCM_MBISTWDG_CLKDIV64) )
                                                           
#define NOT_MBIST_LAUNCH_CFG(launch)                      (((launch) != STCM_MBLAUNCH_NOP)      && ((launch) != STCM_MBLAUNCH_RUNONLY) && \
                                                           ((launch) != STCM_MBLAUNCH_PROGONLY) && ((launch) != STCM_MBLAUNCH_RUN_PROG) )
                                                           
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_LBIST_EXECUTION_MODE(spm)                     (((spm) != STCM_SERIAL_MODE) && ((spm) != STCM_PARALLEL_MODE))
#define NOT_LBIST_NEXT_PTR(nextptr)                       (((nextptr) != STCM_PTR_MBIST0)  && ((nextptr) != STCM_PTR_MBIST1)  && ((nextptr) != STCM_PTR_MBIST2)  && \
                                                           ((nextptr) != STCM_PTR_MBIST3)  && ((nextptr) != STCM_PTR_MBIST4)  && ((nextptr) != STCM_PTR_MBIST5)  && \
                                                           ((nextptr) != STCM_PTR_MBIST6)  && ((nextptr) != STCM_PTR_MBIST7)  && ((nextptr) != STCM_PTR_MBIST8)  && \
                                                           ((nextptr) != STCM_PTR_MBIST9)  && ((nextptr) != STCM_PTR_MBIST10) && ((nextptr) != STCM_PTR_MBIST11) && \
                                                           ((nextptr) != STCM_PTR_MBIST12) && ((nextptr) != STCM_PTR_NIL))
                                                           
#define NOT_LBIST_SHIFT_RATE(shr)                         (((shr) != STCM_LBIST_SHR_FULL) && ((shr) != STCM_LBIST_SHR_DIV2) && ((shr) != STCM_LBIST_SHR_DIV3) && \
                                                           ((shr) != STCM_LBIST_SHR_DIV4) && ((shr) != STCM_LBIST_SHR_DIV5) && ((shr) != STCM_LBIST_SHR_DIV6) && \
                                                           ((shr) != STCM_LBIST_SHR_DIV7) && ((shr) != STCM_LBIST_SHR_DIV8))
                                                           
#define NOT_LBIST_DATA_SOURCE(datasource)                 (((datasource) != STCM_AIT_ROM) && ((datasource) != STCM_AIT_RAM))

#define NOT_LBIST_CLKDIV(clkdiv)                          (((clkdiv) != STCM_AITCLK_DIV1) && ((clkdiv) != STCM_AITCLK_DIV2) && ((clkdiv) != STCM_AITCLK_DIV10))

#define NOT_LBIST_WDG_CLKDIV(clkdiv)                      (((clkdiv) != STCM_LBISTWDG_CLKDIV1)  && ((clkdiv) != STCM_LBISTWDG_CLKDIV4) && \
                                                           ((clkdiv) != STCM_LBISTWDG_CLKDIV16) && ((clkdiv) != STCM_LBISTWDG_CLKDIV64))
                                                           
#define NOT_LBIST_SHIFTCLK_STEP_SIZE(stepsize)            (((stepsize) > STCM_LBIST_SHIFTCLK_STEP_MAX) || ((stepsize) < STCM_LBIST_SHIFTCLK_STEP_MIN))

#define NOT_LBIST_SHIFTCLK_START_EN(starten)              (((starten) != (uint32_t)DISABLE) && ((starten) != (uint32_t)ENABLE))

#define NOT_LBIST_SHIFTCLK_END_EN(enden)                  (((enden) != (uint32_t)DISABLE) && ((enden) != (uint32_t)ENABLE))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#endif

/* function declarations */
/* reset STCM register */
void stcm_deinit(void);
/* unlock STCM config registers */
void stcm_unlock(uint8_t key_loop_index);
/* STCM write access enable */
void stcm_writeacess_enable(void);
/* STCM write access disable */
void stcm_writeacess_disable(void);
/* TMR (Triple-Modular Redundancy) run BIST phase enable */
void stcm_tmr_enable(void);
/* TMR (Triple-Modular Redundancy) run BIST phase disable */
void stcm_tmr_disable(void);
/* BIST executed with PLL enabled */
void stcm_bist_with_pll(uint32_t mbistpllen, uint32_t lbistpllen);
/* first BIST select */
void stcm_firstbist(uint32_t ptr);
/* BIST general error mapping */
void stcm_general_bist_error_mapping(uint32_t general_err_code, uint32_t unrecoverable);
/* BIST phase interval config */
void stcm_bist_phase_intvl_cfg(uint32_t interval);
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* LBIST AIT packet interval config */
void stcm_lbist_ait_packet_intvl_cfg (uint32_t interval);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
/* MBIST config */
void stcm_mbist_config(uint32_t mbistnum, uint32_t spm, uint32_t nextptr, uint32_t mben);
/* MBIST partition error mapping */
void stcm_mbist_errormapping(uint32_t mbistnum, uint32_t unrecoverable);
/* MBIST watchdog config */
void stcm_mbist_wdg_config(uint32_t counter, uint32_t clkdiv);
/* get MBIST partition status */
stcm_bist_state stcm_mbist_stat_get(uint32_t mbistnum);
/* MBIST launch config */
void stcm_mbist_launch_config(uint32_t launch);
/* MBIST algorithm selection */
void stcm_mbist_algosel(uint32_t algo);
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* LBIST config */
void stcm_lbist_config(uint32_t spm, uint32_t nextptr, uint32_t shr, uint32_t datasource, uint32_t clkdiv);
/* LBIST partition error mapping */
void stcm_lbist_errormapping(uint32_t unrecoverable);
/* LBIST watchdog config */
void stcm_lbist_wdg_config(uint32_t counter, uint32_t clkdiv);
/* get LBIST partition status */
stcm_bist_state stcm_lbist_stat_get(void);
/* LBIST shift clock config */
void stcm_lbist_shiftclk_config(uint32_t stepsize, uint32_t starten, uint32_t enden);
/* LBIST engine timeout strap config */
void stcm_lbist_engine_timestrap_config (uint32_t timestrap);
/* LBIST packet config */
void stcm_lbist_packet_config(uint8_t first_ait_packet_index, uint8_t ait_packet_num);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
/* BIST start */
void stcm_bist_start(void);
/* get TMR state */
stcm_tmr_state stcm_tmr_stat_get(void);
/* get BIST error state */
FlagStatus stcm_bist_err_stat_get(stcm_error_code_enum error_code);
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* get the timeout or failed LBIST AIT information */
void stcm_failed_timeout_lbist_ait_info_get(uint16_t *packet_addr,uint8_t *ait_stat);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#endif /* GD32A7XX_STCM_H */
