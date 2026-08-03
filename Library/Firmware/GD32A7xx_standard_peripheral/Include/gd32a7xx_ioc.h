/*!
    \file    gd32a7xx_ioc.h
    \brief   definitions for the IOC

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

#ifndef GD32A7XX_IOC_H
#define GD32A7XX_IOC_H

#include "gd32a7xx.h"

/* IOC base definition*/
#define IOC                                     IOC_BASE                                        /*!< IOC base address */

/* registers definitions */
#define IOC_CTL                                 REG32(IOC + 0x00000000U)                        /*!< control register */
#define IOC_RSTSTATC                            REG32(IOC + 0x00000004U)                        /*!< reset status clear register */
#define IOC_RST0                                REG32(IOC + 0x00000008U)                        /*!< reset register 0 */
#define IOC_RST1                                REG32(IOC + 0x0000000CU)                        /*!< reset register 1 */
#define IOC_RFPMESTAT                           REG32(IOC + 0x00000018U)                        /*!< reference signal FPMx edge status register */
#define IOC_MFPMESTAT                           REG32(IOC + 0x0000001CU)                        /*!< monitor signal FPMx edge status register */
#define IOC_FPMCFG(fpmx)                        REG32(IOC + 0x00000020U + (fpmx)*4U)            /*!< FPMx configuration register */
#define IOC_RFPMCNT(fpmx)                       REG32(IOC + 0x00000040U + (fpmx)*4U)           /*!< reference signal FPMx count register */
#define IOC_MFPMCNT(fpmx)                       REG32(IOC + 0x00000060U + (fpmx)*4U)           /*!< monitor signal FPMx count register */
#define IOC_RICTL                               REG32(IOC + 0x00000080U)                        /*!< RSG combiner reference signal input control register */
#define IOC_EGMCNT(egmx)                        REG32(IOC + 0x00000084U + (egmx)*4U)            /*!< EGMx count register */
#define IOC_EGMCTL(egmx)                        REG32(IOC + 0x000000A4U + (egmx)*4U)            /*!< EGMx control register */
#define IOC_EGMCFG(egmx)                        REG32(IOC + 0x000000C4U + (egmx)*4U)            /*!< EGMx configuration register */
#define IOC_SEGMCTL0                            REG32(IOC + 0x000000E4U)                        /*!< SEGM control register 0 */
#define IOC_SEGMCTL1                            REG32(IOC + 0x000000E8U)                        /*!< SEGM control register 1 */
#define IOC_SEGMTER0                            REG32(IOC + 0x000000ECU)                        /*!< SEGM generation event record register0 */
#define IOC_SEGMTER1                            REG32(IOC + 0x000000F0U)                        /*!< SEGM generation event record register1 */
#define IOC_TMRINTSTAT                          REG32(IOC + 0x000000F4U)                        /*!< TMR interrupt and status register */
#define IOC_INTSTAT                             REG32(IOC + 0x000000F8U)                        /*!< interrupt and status register */

/* fields definitions */
/* IOC_CTL */
#define IOC_CTL_IOCEN                           BIT(0)                                          /*!< IOC enable */
#define IOC_CTL_IOCENF                          BIT(1)                                          /*!< IOC status */
#define IOC_CTL_CLKEN                           BIT(3)                                          /*!< clock enable */
#define IOC_CTL_PSC                             BITS(8,15)                                      /*!< clock prescaler selection */

/* IOC_RSTSTATC */
#define IOC_RSTSTATC_RSTFC                      BIT(0)                                          /*!< clear reset flag */

/* IOC_RST0 */
#define IOC_RST0_RST0                           BIT(0)                                          /*!< reset IOC */

/* IOC_RST1 */
#define IOC_RST1_RST1                           BIT(0)                                          /*!< reset IOC */
#define IOC_RST1_RSTF                           BIT(1)                                          /*!< IOC reset flag */

/* IOC_RFPMESTAT */
#define IOC_RFPMESTAT_FPM0FEF                   BIT(0)                                          /*!< reference signal FPM0 falling edge flag */
#define IOC_RFPMESTAT_FPM1FEF                   BIT(1)                                          /*!< reference signal FPM1 falling edge flag */
#define IOC_RFPMESTAT_FPM2FEF                   BIT(2)                                          /*!< reference signal FPM2 falling edge flag */
#define IOC_RFPMESTAT_FPM3FEF                   BIT(3)                                          /*!< reference signal FPM3 falling edge flag */
#define IOC_RFPMESTAT_FPM4FEF                   BIT(4)                                          /*!< reference signal FPM4 falling edge flag */
#define IOC_RFPMESTAT_FPM5FEF                   BIT(5)                                          /*!< reference signal FPM5 falling edge flag */
#define IOC_RFPMESTAT_FPM6FEF                   BIT(6)                                          /*!< reference signal FPM6 falling edge flag */
#define IOC_RFPMESTAT_FPM7FEF                   BIT(7)                                          /*!< reference signal FPM7 falling edge flag */
#define IOC_RFPMESTAT_FPM0REF                   BIT(16)                                         /*!< reference signal FPM0 rising edge flag */
#define IOC_RFPMESTAT_FPM1REF                   BIT(17)                                         /*!< reference signal FPM1 rising edge flag */
#define IOC_RFPMESTAT_FPM2REF                   BIT(18)                                         /*!< reference signal FPM2 rising edge flag */
#define IOC_RFPMESTAT_FPM3REF                   BIT(19)                                         /*!< reference signal FPM3 rising edge flag */
#define IOC_RFPMESTAT_FPM4REF                   BIT(20)                                         /*!< reference signal FPM4 rising edge flag */
#define IOC_RFPMESTAT_FPM5REF                   BIT(21)                                         /*!< reference signal FPM5 rising edge flag */
#define IOC_RFPMESTAT_FPM6REF                   BIT(22)                                         /*!< reference signal FPM6 rising edge flag */
#define IOC_RFPMESTAT_FPM7REF                   BIT(23)                                         /*!< reference signal FPM7 rising edge flag */

/* IOC_MFPMESTAT */
#define IOC_MFPMESTAT_FPM0FEF                   BIT(0)                                          /*!< monitor signal FPM0 falling edge flag */
#define IOC_MFPMESTAT_FPM1FEF                   BIT(1)                                          /*!< monitor signal FPM1 falling edge flag */
#define IOC_MFPMESTAT_FPM2FEF                   BIT(2)                                          /*!< monitor signal FPM2 falling edge flag */
#define IOC_MFPMESTAT_FPM3FEF                   BIT(3)                                          /*!< monitor signal FPM3 falling edge flag */
#define IOC_MFPMESTAT_FPM4FEF                   BIT(4)                                          /*!< monitor signal FPM4 falling edge flag */
#define IOC_MFPMESTAT_FPM5FEF                   BIT(5)                                          /*!< monitor signal FPM5 falling edge flag */
#define IOC_MFPMESTAT_FPM6FEF                   BIT(6)                                          /*!< monitor signal FPM6 falling edge flag */
#define IOC_MFPMESTAT_FPM7FEF                   BIT(7)                                          /*!< monitor signal FPM7 falling edge flag */
#define IOC_MFPMESTAT_FPM0REF                   BIT(16)                                         /*!< monitor signal FPM0 rising edge flag */
#define IOC_MFPMESTAT_FPM1REF                   BIT(17)                                         /*!< monitor signal FPM1 rising edge flag */
#define IOC_MFPMESTAT_FPM2REF                   BIT(18)                                         /*!< monitor signal FPM2 rising edge flag */
#define IOC_MFPMESTAT_FPM3REF                   BIT(19)                                         /*!< monitor signal FPM3 rising edge flag */
#define IOC_MFPMESTAT_FPM4REF                   BIT(20)                                         /*!< monitor signal FPM4 rising edge flag */
#define IOC_MFPMESTAT_FPM5REF                   BIT(21)                                         /*!< monitor signal FPM5 rising edge flag */
#define IOC_MFPMESTAT_FPM6REF                   BIT(22)                                         /*!< monitor signal FPM6 rising edge flag */
#define IOC_MFPMESTAT_FPM7REF                   BIT(23)                                         /*!< monitor signal FPM7 rising edge flag */

/* IOC_FPMx_CFG */
#define IOC_FPMX_CFG_CMP                        BITS(0,15)                                      /*!< the value of 16 bit comparator*/
#define IOC_FPMX_CFG_MSEL                       BITS(16,18)                                     /*!< FPM mode*/
#define IOC_FPMX_CFG_MISEL                      BITS(19,20)                                     /*!< monitor input signal selection*/
#define IOC_FPMX_CFG_RCNT                       BIT(22)                                         /*!< reset the counter of timer*/
#define IOC_FPMX_CFG_RISEL                      BITS(24,26)                                     /*!< reference input signal selection*/

/* IOC_RFPMxCNT */
#define IOC_RFPMXCNT_CNT                        BITS(0,15)                                      /*!< the value of the reference signal FPM timer counter*/

/* IOC_MFPMxCNT */
#define IOC_MFPMxCNT_CNT                        BITS(0,15)                                      /*!< the value of the monitor signal FPM timer counter*/

/* IOC_RICTL */
#define IOC_RICTL_TIEEN0                        BIT(0)                                          /*!< TRIGGSEL input 0 selection for RSG combiner*/
#define IOC_RICTL_TIEEN1                        BIT(1)                                          /*!< TRIGGSEL input 1 selection for RSG combiner*/
#define IOC_RICTL_TIEEN2                        BIT(2)                                          /*!< TRIGGSEL input 2 selection for RSG combiner*/
#define IOC_RICTL_TIEEN3                        BIT(3)                                          /*!< TRIGGSEL input 3 selection for RSG combiner*/
#define IOC_RICTL_TIEEN4                        BIT(4)                                          /*!< TRIGGSEL input 4 selection for RSG combiner*/
#define IOC_RICTL_TIEEN5                        BIT(5)                                          /*!< TRIGGSEL input 5 selection for RSG combiner*/
#define IOC_RICTL_TIEEN6                        BIT(6)                                          /*!< TRIGGSEL input 6 selection for RSG combiner*/
#define IOC_RICTL_TIEEN7                        BIT(7)                                          /*!< TRIGGSEL input 7 selection for RSG combiner*/

/* IOC_EGMxCNT */
#define IOC_EGMXCNT_CNT                         BITS(0,23)                                      /*!< The value of event window count*/
#define IOC_EGMXCNT_CNTOVF                      BIT(31)                                         /*!< Overflow flag*/

/* IOC_EGMxCTL */
#define IOC_EGMXCTL_INVREN                      BIT(0)                                          /*!< enable invert reference signal*/
#define IOC_EGMXCTL_INVMEN                      BIT(1)                                          /*!< enable invert monitor signal*/
#define IOC_EGMXCTL_MREN                        BIT(2)                                          /*!< enable monitor signal from the FPM compared with reference signal*/
#define IOC_EGMXCTL_EWGRM                       BIT(3)                                          /*!< event window generation run mode*/
#define IOC_EGMXCTL_EWGSIGS                     BIT(4)                                          /*!< event window generation signal selection*/
#define IOC_EGMXCTL_EVDIS                       BIT(5)                                          /*!< Disable event generated*/
#define IOC_EGMXCTL_EWAES                       BITS(8,11)                                      /*!< event window triger edge selection*/
#define IOC_EGMXCTL_INVEWEN                     BIT(12)                                         /*!< invert event window*/
#define IOC_EGMXCTL_MONSIGS                     BITS(16,18)                                     /*!< monitor signal selection*/
#define IOC_EGMXCTL_REFSIGS                     BITS(20,22)                                     /*!< reference signal selection*/

/* IOC_EGMxCFG */
#define IOC_EGMXCFG_EWCTH                       BITS(0,23)                                      /*!< event window count threshold*/

/* IOC_SEGMCTL0 */
#define IOC_SEGMCTL0_CH0ES                      BITS(0,2)                                       /*!< SEGM channel 0 event selection*/
#define IOC_SEGMCTL0_CH0THR                     BITS(4,7)                                       /*!< SEGM Channel 0 event counter threshold*/
#define IOC_SEGMCTL0_CH1ES                      BITS(8,10)                                      /*!< SEGM channel 1 event selection*/
#define IOC_SEGMCTL0_CH1THR                     BITS(12,15)                                     /*!< SEGM Channel 1 event counter threshold*/
#define IOC_SEGMCTL0_CH2ES                      BITS(16,18)                                     /*!< SEGM channel 2 event selection*/
#define IOC_SEGMCTL0_CH2THR                     BITS(20,23)                                     /*!< SEGM Channel 2 event counter threshold*/
#define IOC_SEGMCTL0_CH3ES                      BITS(24,26)                                     /*!< SEGM channel 3 event selection*/
#define IOC_SEGMCTL0_CH3THR                     BITS(28,31)                                     /*!< SEGM Channel 3 event counter threshold*/

/* IOC_SEGMCTL1 */
#define IOC_SEGMCTL1_EGM_ETM0EN                 BIT(0)                                          /*!< enable EGM_ETM0 selection*/
#define IOC_SEGMCTL1_EGM_ETM1EN                 BIT(1)                                          /*!< enable EGM_ETM1 selection*/
#define IOC_SEGMCTL1_EGM_ETM2EN                 BIT(2)                                          /*!< enable EGM_ETM2 selection*/
#define IOC_SEGMCTL1_EGM_ETM3EN                 BIT(3)                                          /*!< enable EGM_ETM3 selection*/
#define IOC_SEGMCTL1_EGM_ETM4EN                 BIT(4)                                          /*!< enable EGM_ETM4 selection*/
#define IOC_SEGMCTL1_EGM_ETM5EN                 BIT(5)                                          /*!< enable EGM_ETM5 selection*/
#define IOC_SEGMCTL1_EGM_ETM6EN                 BIT(6)                                          /*!< enable EGM_ETM6 selection*/
#define IOC_SEGMCTL1_EGM_ETM7EN                 BIT(7)                                          /*!< enable EGM_ETM7 selection*/
#define IOC_SEGMCTL1_SEGM_CH0EN                 BIT(16)                                         /*!< enable SEGM channel 0 selection*/
#define IOC_SEGMCTL1_SEGM_CH1EN                 BIT(17)                                         /*!< enable SEGM channel 1 selection*/
#define IOC_SEGMCTL1_SEGM_CH2EN                 BIT(18)                                         /*!< enable SEGM channel 2 selection*/
#define IOC_SEGMCTL1_SEGM_CH3EN                 BIT(19)                                         /*!< enable SEGM channel 3 selection*/

/* IOC_SEGMTER0 */
#define IOC_SEGMTER0_EGM0TE0                    BIT(0)                                          /*!< EGM0 triggered system event flag at last time*/
#define IOC_SEGMTER0_EGM1TE0                    BIT(1)                                          /*!< EGM1 triggered system event flag at last time*/
#define IOC_SEGMTER0_EGM2TE0                    BIT(2)                                          /*!< EGM2 triggered system event flag at last time*/
#define IOC_SEGMTER0_EGM3TE0                    BIT(3)                                          /*!< EGM3 triggered system event flag at last time*/
#define IOC_SEGMTER0_EGM4TE0                    BIT(4)                                          /*!< EGM4 triggered system event flag at last time*/
#define IOC_SEGMTER0_EGM5TE0                    BIT(5)                                          /*!< EGM5 triggered system event flag at last time*/
#define IOC_SEGMTER0_EGM6TE0                    BIT(6)                                          /*!< EGM6 triggered system event flag at last time*/
#define IOC_SEGMTER0_EGM7TE0                    BIT(7)                                          /*!< EGM7 triggered system event flag at last time*/
#define IOC_SEGMTER0_EGM0TE1                    BIT(16)                                         /*!< EGM0 triggered system event flag before EGM*/
#define IOC_SEGMTER0_EGM1TE1                    BIT(17)                                         /*!< EGM1 triggered system event flag before EGM*/
#define IOC_SEGMTER0_EGM2TE1                    BIT(18)                                         /*!< EGM2 triggered system event flag before EGM*/
#define IOC_SEGMTER0_EGM3TE1                    BIT(19)                                         /*!< EGM3 triggered system event flag before EGM*/
#define IOC_SEGMTER0_EGM4TE1                    BIT(20)                                         /*!< EGM4 triggered system event flag before EGM*/
#define IOC_SEGMTER0_EGM5TE1                    BIT(21)                                         /*!< EGM5 triggered system event flag before EGM*/
#define IOC_SEGMTER0_EGM6TE1                    BIT(22)                                         /*!< EGM6 triggered system event flag before EGM*/
#define IOC_SEGMTER0_EGM7TE1                    BIT(23)                                         /*!< EGM7 triggered system event flag before EGM*/

/* IOC_SEGMTER1 */
#define IOC_SEGMTER1_EGM0TE2                    BIT(0)                                           /*!< EGM0 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM1TE2                    BIT(1)                                           /*!< EGM1 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM2TE2                    BIT(2)                                           /*!< EGM2 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM3TE2                    BIT(3)                                           /*!< EGM3 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM4TE2                    BIT(4)                                           /*!< EGM4 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM5TE2                    BIT(5)                                           /*!< EGM5 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM6TE2                    BIT(6)                                           /*!< EGM6 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM7TE2                    BIT(7)                                           /*!< EGM7 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM0TE3                    BIT(16)                                          /*!< EGM0 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM1TE3                    BIT(17)                                          /*!< EGM1 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM2TE3                    BIT(18)                                          /*!< EGM2 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM3TE3                    BIT(19)                                          /*!< EGM3 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM4TE3                    BIT(20)                                          /*!< EGM4 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM5TE3                    BIT(21)                                          /*!< EGM5 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM6TE3                    BIT(22)                                          /*!< EGM6 triggered system event flag before EGM*/
#define IOC_SEGMTER1_EGM7TE3                    BIT(23)                                          /*!< EGM7 triggered system event flag before EGM*/

/* IOC_TMRINTSTAT */
#define IOC_TMRINTSTAT_TMRERR_PSCIE             BIT(0)                                           /*!< TMRERR_PSC interrupt enable*/
#define IOC_TMRINTSTAT_TMRERR_PSCIF             BIT(1)                                           /*!< clock prescaler selection TMR rectify error alarm flag*/
#define IOC_TMRINTSTAT_TMRERR_CLKENIE           BIT(2)                                           /*!< TMREER_CLKEN interrupt enable*/
#define IOC_TMRINTSTAT_TMRERR_CLKENIF           BIT(3)                                           /*!< clock control enable TMR rectify error alarm flag*/
#define IOC_TMRINTSTAT_TMRERR_MCENIE            BIT(4)                                           /*!< TMRERR_MCEN interrupt enable*/
#define IOC_TMRINTSTAT_TMRERR_MCENIF            BIT(5)                                           /*!< module close enable TMR rectify error alarm flag*/

/* IOC_INTSTAT */
#define IOC_INTSTAT_ALRMIE                      BIT(0)                                           /*!< alarm interrupt enable*/
#define IOC_INTSTAT_ALRMIF                      BIT(1)                                           /*!< SEGM event trigger activity flag*/

/* constants definitions */

#define IOC_FPM_CHANNEL_NUM         8U
#define IOC_EGM_CHANNEL_NUM         8U
#define IOC_RSG_CHANNEL_NUM         8U
#define IOC_SEGM_CHANNEL_NUM        4U

/* FPM mode definition */
#define FPM_MODE(regval)                       (BITS(16,18) & ((uint32_t)(regval) << 16U))
#define DLY_DEB_BOTH_EDGE                      FPM_MODE(0)                                       /*!< delayed debounce filter mode on both edges */
#define IMM_DEB_BOTH_EDGE                      FPM_MODE(1)                                       /*!< immediate debounce filter mode on both edges */
#define IMM_DEBE_R_EDGE                        FPM_MODE(2)                                       /*!< immediate debounce filter mode on rising edge, no filtering on falling edge */
#define IMM_DEBE_F_EDGE                        FPM_MODE(3)                                       /*!< no filtering on rising edge, immediate debounce filter mode on falling edge */
#define DLY_DEB_R_EDGE_IMM_DEB_F_EDGE          FPM_MODE(4)                                       /*!< delayed debounce filter mode on rising edge, immediate debounce filter mode on falling edge */
#define IMM_DEB_R_EDGE_DLY_DEB_F_EDGE          FPM_MODE(5)                                       /*!< immediate debounce filter mode on rising edge, delayed debounce filter mode on falling edge */
#define PRESCALER_R_EDGE                       FPM_MODE(6)                                       /*!< prescaler mode (triggered on rising edge) */
#define PRESCALER_F_EDGE                       FPM_MODE(7)                                       /*!< prescaler mode (triggered on falling edge) */

/* reference FPM input signal definiton */
#define REFERENCE_SIGNAL(regval)               (BITS(24,26) & ((uint32_t)(regval) << 24U))
#define FPM_SO_REF                             REFERENCE_SIGNAL(0)                               /*!< select FPMx_SO */
#define IOC_REFERENCE                          REFERENCE_SIGNAL(1)                               /*!< select IOC_reference[x] */
#define RSG_REFERENCE                          REFERENCE_SIGNAL(4)                               /*!< select RSG_reference[x] */

/* reference FPM input signal definiton */
#define MONITOR_SIGNAL(regval)                 (BITS(19,20) & ((uint32_t)(regval) << 19U))
#define FPM_SO_MON                             MONITOR_SIGNAL(0)                                 /*!< select FPMx_SO */
#define IOC_MONITOR                            MONITOR_SIGNAL(1)                                 /*!< select IOC_monitor[x] */

/* TRIGSEL input selection for RSG definiton */
#define RSG_TRIGSEL_INPUT0                     IOC_RICTL_TIEEN0                                  /*!< TRIGSEL input0 selection for RSG combiner */
#define RSG_TRIGSEL_INPUT1                     IOC_RICTL_TIEEN1                                  /*!< TRIGSEL input1 selection for RSG combiner */
#define RSG_TRIGSEL_INPUT2                     IOC_RICTL_TIEEN2                                  /*!< TRIGSEL input2 selection for RSG combiner */
#define RSG_TRIGSEL_INPUT3                     IOC_RICTL_TIEEN3                                  /*!< TRIGSEL input3 selection for RSG combiner */
#define RSG_TRIGSEL_INPUT4                     IOC_RICTL_TIEEN4                                  /*!< TRIGSEL input4 selection for RSG combiner */
#define RSG_TRIGSEL_INPUT5                     IOC_RICTL_TIEEN5                                  /*!< TRIGSEL input5 selection for RSG combiner */
#define RSG_TRIGSEL_INPUT6                     IOC_RICTL_TIEEN6                                  /*!< TRIGSEL input6 selection for RSG combiner */
#define RSG_TRIGSEL_INPUT7                     IOC_RICTL_TIEEN7                                  /*!< TRIGSEL input7 selection for RSG combiner */

/* EGM reference signal  definiton */
#define EGM_REFERENCE_SIGNAL(regval)           (BITS(20,22) & ((uint32_t)(regval) << 20))
#define REFERENCE0                             EGM_REFERENCE_SIGNAL(0)                           /*!< reference[0] */
#define REFERENCE1                             EGM_REFERENCE_SIGNAL(1)                           /*!< reference[1] */
#define REFERENCE2                             EGM_REFERENCE_SIGNAL(2)                           /*!< reference[2] */
#define REFERENCE3                             EGM_REFERENCE_SIGNAL(3)                           /*!< reference[3] */
#define REFERENCE4                             EGM_REFERENCE_SIGNAL(4)                           /*!< reference[4] */
#define REFERENCE5                             EGM_REFERENCE_SIGNAL(5)                           /*!< reference[5] */
#define REFERENCE6                             EGM_REFERENCE_SIGNAL(6)                           /*!< reference[6] */
#define REFERENCE7                             EGM_REFERENCE_SIGNAL(7)                           /*!< reference[7] */

/* EGM monitor signal definiton */
#define EGM_MONITORE_SIGNAL(regval)            (BITS(16,18) & ((uint32_t)(regval) << 16))
#define MONITOR0                               EGM_MONITORE_SIGNAL(0)                            /*!< monitor[0] */
#define MONITOR1                               EGM_MONITORE_SIGNAL(1)                            /*!< monitor[1] */
#define MONITOR2                               EGM_MONITORE_SIGNAL(2)                            /*!< monitor[2] */
#define MONITOR3                               EGM_MONITORE_SIGNAL(3)                            /*!< monitor[3] */
#define MONITOR4                               EGM_MONITORE_SIGNAL(4)                            /*!< monitor[4] */
#define MONITOR5                               EGM_MONITORE_SIGNAL(5)                            /*!< monitor[5] */
#define MONITOR6                               EGM_MONITORE_SIGNAL(6)                            /*!< monitor[6] */
#define MONITOR7                               EGM_MONITORE_SIGNAL(7)                            /*!< monitor[7] */

/* event window generation signal definiton */
#define EVENT_TRI_REFERENCE_SIGNAL             0U                                                /*!< reference signal */
#define EVENT_TRI_MONITOR_SIGNAL               IOC_EGMXCTL_EWGSIGS                               /*!< monitor signal */

/* EGM event window triger edge definiton */
#define EVENT_WIN_TRIGER_EDGE(regval)          (BITS(8,11) & ((uint32_t)(regval) << 8))
#define NO_EDGE_CLR_GATE                       EVENT_WIN_TRIGER_EDGE(0)                           /*!< neither edge used to clear event window counter. neither edge used to gate event generation */
#define REDGE_CLR                              EVENT_WIN_TRIGER_EDGE(1)                           /*!< rising edge used to clear event window counter. neither edge used to gate event generation */
#define FEDGE_CLR                              EVENT_WIN_TRIGER_EDGE(2)                           /*!< falling edge used to clear event window counter. neither edge used to gate event generation */
#define BOTH_EDGE_CLR                          EVENT_WIN_TRIGER_EDGE(3)                           /*!< both rising and falling edges used to clear event window counter. neither edge used to gate event generation */
#define REDGE_GATE                             EVENT_WIN_TRIGER_EDGE(4)                           /*!< neither edge used to clear event window counter. rising edge used to gate event generation */
#define REDGE_CLR_REDGE_GATE                   EVENT_WIN_TRIGER_EDGE(5)                           /*!< rising edge used to clear event window counter. rising edge used to gate event generation */
#define FEDGE_CLR_REDGE_GATE                   EVENT_WIN_TRIGER_EDGE(6)                           /*!< falling edge used to clear event window counter. rising edge used to gate event generation */
#define BOTH_EDGE_CLR_REDGE_GATE               EVENT_WIN_TRIGER_EDGE(7)                           /*!< both rising and falling edges used to clear event window counter. rising edge used to gate event generation */
#define FEDGE_GATE                             EVENT_WIN_TRIGER_EDGE(8)                           /*!< neither edge used to clear event window counter. falling edge used to gate event generation */
#define REDGE_CLR_FEDGE_GATE                   EVENT_WIN_TRIGER_EDGE(9)                           /*!< rising edge used to clear event window counter. falling edge used to gate event generation */
#define FEDGE_CLR_FEDGE_GATE                   EVENT_WIN_TRIGER_EDGE(10)                          /*!< Falling edge used to clear event window counter. Falling edge used to gate event generation */
#define BOTH_EDGE_CLR_FEDGE_GATE               EVENT_WIN_TRIGER_EDGE(11)                          /*!< both rising and falling edges used to clear event window counter. falling edge used to gate event generation */
#define BOTH_EDGE_GATE                         EVENT_WIN_TRIGER_EDGE(12)                          /*!< neither edge used to clear event window counter. both rising and falling edges used to gate event generation */
#define REDGE_CLR_BOTH_EDGE_GATE               EVENT_WIN_TRIGER_EDGE(13)                          /*!< rising edge used to clear event window counter. both rising and falling edges used to gate event generation */
#define FEDGE_CLR_BOTH_EDGE_GATE               EVENT_WIN_TRIGER_EDGE(14)                          /*!< falling edge used to clear event window counter. both rising and falling edges used to gate event generation */
#define BOTH_EDGE_CLR_GATE                     EVENT_WIN_TRIGER_EDGE(15)                          /*!< both rising and falling edges used to clear event window counter. both rising and falling edges used to gate event generation */

/* event window generation run mode definition */
#define FREE_RUNNING_MODE                      0U                                                /*!< free running mode */
#define GATE_MODE                              IOC_EGMXCTL_EWGRM                                 /*!< gated mode */

/* SEGM channel x event definition */
#define SEGM_EGM_EVENT(regval)                 (BITS(0,2) & (uint32_t)regval)
#define SEGM_EGM_EVENT0                        SEGM_EGM_EVENT(0)                                 /*!< EGM event 0 */
#define SEGM_EGM_EVENT1                        SEGM_EGM_EVENT(1)                                 /*!< EGM event 1 */
#define SEGM_EGM_EVENT2                        SEGM_EGM_EVENT(2)                                 /*!< EGM event 2 */
#define SEGM_EGM_EVENT3                        SEGM_EGM_EVENT(3)                                 /*!< EGM event 3 */
#define SEGM_EGM_EVENT4                        SEGM_EGM_EVENT(4)                                 /*!< EGM event 4 */
#define SEGM_EGM_EVENT5                        SEGM_EGM_EVENT(5)                                 /*!< EGM event 5 */
#define SEGM_EGM_EVENT6                        SEGM_EGM_EVENT(6)                                 /*!< EGM event 6 */
#define SEGM_EGM_EVENT7                        SEGM_EGM_EVENT(7)                                 /*!< EGM event 7 */

/* SEGM EGM_ETMx enable definition */
#define SEGM_EGM_EVENT0_ENABLE                 IOC_SEGMCTL1_EGM_ETM0EN                           /*!< enable EGM event 0 selection */
#define SEGM_EGM_EVENT1_ENABLE                 IOC_SEGMCTL1_EGM_ETM1EN                           /*!< enable EGM event 1 selection */
#define SEGM_EGM_EVENT2_ENABLE                 IOC_SEGMCTL1_EGM_ETM2EN                           /*!< enable EGM event 2 selection */
#define SEGM_EGM_EVENT3_ENABLE                 IOC_SEGMCTL1_EGM_ETM3EN                           /*!< enable EGM event 3 selection */
#define SEGM_EGM_EVENT4_ENABLE                 IOC_SEGMCTL1_EGM_ETM4EN                           /*!< enable EGM event 4 selection */
#define SEGM_EGM_EVENT5_ENABLE                 IOC_SEGMCTL1_EGM_ETM5EN                           /*!< enable EGM event 5 selection */
#define SEGM_EGM_EVENT6_ENABLE                 IOC_SEGMCTL1_EGM_ETM6EN                           /*!< enable EGM event 6 selection */
#define SEGM_EGM_EVENT7_ENABLE                 IOC_SEGMCTL1_EGM_ETM7EN                           /*!< enable EGM event 7 selection */

/* SEGM EGM_ETMx disable definition */
#define SEGM_EGM_EVENT0_DISABLE                ~IOC_SEGMCTL1_EGM_ETM0EN                          /*!< enable EGM event 0 selection */
#define SEGM_EGM_EVENT1_DISABLE                ~IOC_SEGMCTL1_EGM_ETM1EN                          /*!< enable EGM event 1 selection */
#define SEGM_EGM_EVENT2_DISABLE                ~IOC_SEGMCTL1_EGM_ETM2EN                          /*!< enable EGM event 2 selection */
#define SEGM_EGM_EVENT3_DISABLE                ~IOC_SEGMCTL1_EGM_ETM3EN                          /*!< enable EGM event 3 selection */
#define SEGM_EGM_EVENT4_DISABLE                ~IOC_SEGMCTL1_EGM_ETM4EN                          /*!< enable EGM event 4 selection */
#define SEGM_EGM_EVENT5_DISABLE                ~IOC_SEGMCTL1_EGM_ETM5EN                          /*!< enable EGM event 5 selection */
#define SEGM_EGM_EVENT6_DISABLE                ~IOC_SEGMCTL1_EGM_ETM6EN                          /*!< enable EGM event 6 selection */
#define SEGM_EGM_EVENT7_DISABLE                ~IOC_SEGMCTL1_EGM_ETM7EN                          /*!< enable EGM event 7 selection */

/* define the IOC bit position and its register index offset */
#define IOC_REGIDX_BIT(regidx, bitpos)     (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define IOC_REG_VAL(offset)                (REG32(IOC + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define IOC_BIT_POS(val)                   ((uint32_t)(val) & 0x0000001FU)
#define IOC_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                              | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define IOC_REG_VAL2(offset)               (REG32(IOC + ((uint32_t)(offset) >> 22)))
#define IOC_BIT_POS2(val)                  (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define IOC_SEGMTER0_REG_OFFSET                ((uint32_t)0x000000ECU)        /*!< IOC_SEGMTER0 register offset */
#define IOC_SEGMTER1_REG_OFFSET                ((uint32_t)0x000000F0U)        /*!< IOC_SEGMTER1 register offset */
#define IOC_TMRINTSTAT_REG_OFFSET              ((uint32_t)0x000000F4U)        /*!< IOC_TMRINTSTAT register offset */

typedef enum
{
    EGM0_TRIG_SYSTEM_EVENT_FLAG0 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 0),
    EGM1_TRIG_SYSTEM_EVENT_FLAG0 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 1),
    EGM2_TRIG_SYSTEM_EVENT_FLAG0 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 2),
    EGM3_TRIG_SYSTEM_EVENT_FLAG0 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 3),
    EGM4_TRIG_SYSTEM_EVENT_FLAG0 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 4),
    EGM5_TRIG_SYSTEM_EVENT_FLAG0 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 5),
    EGM6_TRIG_SYSTEM_EVENT_FLAG0 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 6),
    EGM7_TRIG_SYSTEM_EVENT_FLAG0 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 7),
    EGM0_TRIG_SYSTEM_EVENT_FLAG1 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 16),
    EGM1_TRIG_SYSTEM_EVENT_FLAG1 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 17),
    EGM2_TRIG_SYSTEM_EVENT_FLAG1 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 18),
    EGM3_TRIG_SYSTEM_EVENT_FLAG1 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 19),
    EGM4_TRIG_SYSTEM_EVENT_FLAG1 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 20),
    EGM5_TRIG_SYSTEM_EVENT_FLAG1 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 21),
    EGM6_TRIG_SYSTEM_EVENT_FLAG1 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 22),
    EGM7_TRIG_SYSTEM_EVENT_FLAG1 = IOC_REGIDX_BIT(IOC_SEGMTER0_REG_OFFSET, 23),
    EGM0_TRIG_SYSTEM_EVENT_FLAG2 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 0),
    EGM1_TRIG_SYSTEM_EVENT_FLAG2 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 1),
    EGM2_TRIG_SYSTEM_EVENT_FLAG2 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 2),
    EGM3_TRIG_SYSTEM_EVENT_FLAG2 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 3),
    EGM4_TRIG_SYSTEM_EVENT_FLAG2 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 4),
    EGM5_TRIG_SYSTEM_EVENT_FLAG2 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 5),
    EGM6_TRIG_SYSTEM_EVENT_FLAG2 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 6),
    EGM7_TRIG_SYSTEM_EVENT_FLAG2 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 7),
    EGM0_TRIG_SYSTEM_EVENT_FLAG3 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 16),
    EGM1_TRIG_SYSTEM_EVENT_FLAG3 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 17),
    EGM2_TRIG_SYSTEM_EVENT_FLAG3 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 18),
    EGM3_TRIG_SYSTEM_EVENT_FLAG3 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 19),
    EGM4_TRIG_SYSTEM_EVENT_FLAG3 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 20),
    EGM5_TRIG_SYSTEM_EVENT_FLAG3 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 21),
    EGM6_TRIG_SYSTEM_EVENT_FLAG3 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 22),
    EGM7_TRIG_SYSTEM_EVENT_FLAG3 = IOC_REGIDX_BIT(IOC_SEGMTER1_REG_OFFSET, 23)
} ioc_segm_generate_event_flag_enum;

typedef enum
{
    IOC_INT_TMRERR_PSC           = IOC_REGIDX_BIT(IOC_TMRINTSTAT_REG_OFFSET, 0),
    IOC_INT_TMRERR_CLKEN         = IOC_REGIDX_BIT(IOC_TMRINTSTAT_REG_OFFSET, 2),
    IOC_INT_TMRERR_MCEN          = IOC_REGIDX_BIT(IOC_TMRINTSTAT_REG_OFFSET, 4),
} ioc_tmr_interrupt_enum;

typedef enum
{
    IOC_FLAG_TMRERR_PSC      = IOC_REGIDX_BIT(IOC_TMRINTSTAT_REG_OFFSET, 1),
    IOC_FLAG_TMRERR_CLKEN    = IOC_REGIDX_BIT(IOC_TMRINTSTAT_REG_OFFSET, 3),
    IOC_FLAG_TMRERR_MCEN     = IOC_REGIDX_BIT(IOC_TMRINTSTAT_REG_OFFSET, 5),
} ioc_tmr_flag_enum;

typedef enum
{
    IOC_INT_FLAG_TMRERR_PSC      = IOC_REGIDX_BIT2(IOC_TMRINTSTAT_REG_OFFSET, 0, IOC_TMRINTSTAT_REG_OFFSET, 1),
    IOC_INT_FLAG_TMRERR_CLKEN    = IOC_REGIDX_BIT2(IOC_TMRINTSTAT_REG_OFFSET, 2, IOC_TMRINTSTAT_REG_OFFSET, 3),
    IOC_INT_FLAG_TMRERR_MCEN     = IOC_REGIDX_BIT2(IOC_TMRINTSTAT_REG_OFFSET, 4, IOC_TMRINTSTAT_REG_OFFSET, 5),
} ioc_tmr_interrupt_flag_enum;

typedef enum
{
    FPM_FLAG_FALLING_EDGE = 0U,
    FPM_FLAG_RISING_EDGE
} ioc_fpm_edge_stat_enum;

typedef enum
{
    IOC_FPM0 = 0U,
    IOC_FPM1,
    IOC_FPM2,
    IOC_FPM3,
    IOC_FPM4,
    IOC_FPM5,
    IOC_FPM6,
    IOC_FPM7
} ioc_fpmx_enum;

typedef enum
{
    IOC_EGM0 = 0U,
    IOC_EGM1,
    IOC_EGM2,
    IOC_EGM3,
    IOC_EGM4,
    IOC_EGM5,
    IOC_EGM6,
    IOC_EGM7
} ioc_egmx_enum;

typedef enum
{
    SEGM_CHANNEL_0 = 0U,
    SEGM_CHANNEL_1,
    SEGM_CHANNEL_2,
    SEGM_CHANNEL_3
} ioc_segm_channel_enum;

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check FPM mode */
#define NOT_FPM_MODE(mode)                               (((mode) != DLY_DEB_BOTH_EDGE) && \
                                                          ((mode) != IMM_DEB_BOTH_EDGE) && \
                                                          ((mode) != IMM_DEBE_R_EDGE) && \
                                                          ((mode) != IMM_DEBE_F_EDGE) && \
                                                          ((mode) != DLY_DEB_R_EDGE_IMM_DEB_F_EDGE) && \
                                                          ((mode) != IMM_DEB_R_EDGE_DLY_DEB_F_EDGE) && \
                                                          ((mode) != PRESCALER_R_EDGE) && \
                                                          ((mode) != PRESCALER_F_EDGE))

/* check FPM reference input signal */
#define NOT_FPM_REF_INPUT_SIGNAL(signal)                 (((signal) != FPM_SO_REF) && \
                                                          ((signal) != IOC_REFERENCE) && \
                                                          ((signal) != RSG_REFERENCE))

/* check FPM monitor input signal */
#define NOT_FPM_MON_INPUT_SIGNAL(signal)                 (((signal) != FPM_SO_MON) && ((signal) != IOC_MONITOR))

/* check TRIGSEL input for RSG */
#define NOT_RSG_TRIGSEL_INPUT(signal)                    (((signal) != RSG_TRIGSEL_INPUT0) && \
                                                          ((signal) != RSG_TRIGSEL_INPUT1) && \
                                                          ((signal) != RSG_TRIGSEL_INPUT2) && \
                                                          ((signal) != RSG_TRIGSEL_INPUT3) && \
                                                          ((signal) != RSG_TRIGSEL_INPUT4) && \
                                                          ((signal) != RSG_TRIGSEL_INPUT5) && \
                                                          ((signal) != RSG_TRIGSEL_INPUT6) && \
                                                          ((signal) != RSG_TRIGSEL_INPUT7))

/* check EGM reference signal */
#define NOT_EGM_REFERENCE_SIGNAL(signal)                 (((signal) != REFERENCE0) && \
                                                          ((signal) != REFERENCE1) && \
                                                          ((signal) != REFERENCE2) && \
                                                          ((signal) != REFERENCE3) && \
                                                          ((signal) != REFERENCE4) && \
                                                          ((signal) != REFERENCE5) && \
                                                          ((signal) != REFERENCE6) && \
                                                          ((signal) != REFERENCE7))

/* check EGM monitor signal */
#define NOT_EGM_MONITOR_SIGNAL(signal)                   (((signal) != MONITOR0) && \
                                                          ((signal) != MONITOR1) && \
                                                          ((signal) != MONITOR2) && \
                                                          ((signal) != MONITOR3) && \
                                                          ((signal) != MONITOR4) && \
                                                          ((signal) != MONITOR5) && \
                                                          ((signal) != MONITOR6) && \
                                                          ((signal) != MONITOR7))

/* check event window generation signal */
#define NOT_EVENT_WIN_GENERATION_SIGNAL(signal)          (((signal) != EVENT_TRI_REFERENCE_SIGNAL) && ((signal) != EVENT_TRI_MONITOR_SIGNAL))

/* check EGM window triger edge */
#define NOT_EGM_EVENT_WIN_TRIGER(value)                  (((value) != NO_EDGE_CLR_GATE) && \
                                                          ((value) != REDGE_CLR) && \
                                                          ((value) != FEDGE_CLR) && \
                                                          ((value) != BOTH_EDGE_CLR) && \
                                                          ((value) != REDGE_GATE) && \
                                                          ((value) != REDGE_CLR_REDGE_GATE) && \
                                                          ((value) != FEDGE_CLR_REDGE_GATE) && \
                                                          ((value) != BOTH_EDGE_CLR_REDGE_GATE) && \
                                                          ((value) != FEDGE_GATE) && \
                                                          ((value) != REDGE_CLR_FEDGE_GATE) && \
                                                          ((value) != FEDGE_CLR_FEDGE_GATE) && \
                                                          ((value) != BOTH_EDGE_CLR_FEDGE_GATE) && \
                                                          ((value) != BOTH_EDGE_GATE) && \
                                                          ((value) != REDGE_CLR_BOTH_EDGE_GATE) && \
                                                          ((value) != FEDGE_CLR_BOTH_EDGE_GATE) && \
                                                          ((value) != BOTH_EDGE_CLR_GATE))

/* check event window generation run mode */
#define NOT_EVENT_WIN_RUN_MODE(mode)                     (((mode) != FREE_RUNNING_MODE) && ((mode) != GATE_MODE))

/* check clock prescaler */
#define EGM_EVENT_WIN_LOW_VALUE                          ((uint32_t)0x00000000U)        /*!< minimum threshold value */
#define EGM_EVENT_WIN_HIGH_VALUE                         ((uint32_t)0x00FFFFFFU)        /*!< maximum threshold value */
#define NOT_EGM_EVENT_WIN_VALUE(threshold)               (EGM_EVENT_WIN_HIGH_VALUE < (threshold))

/* check SEGM channel x event */
#define NOT_SEGM_EVENT(event)                            (((event) != SEGM_EGM_EVENT0) && \
                                                          ((event) != SEGM_EGM_EVENT1) && \
                                                          ((event) != SEGM_EGM_EVENT2) && \
                                                          ((event) != SEGM_EGM_EVENT3) && \
                                                          ((event) != SEGM_EGM_EVENT4) && \
                                                          ((event) != SEGM_EGM_EVENT5) && \
                                                          ((event) != SEGM_EGM_EVENT6) && \
                                                          ((event) != SEGM_EGM_EVENT7))

/* check SEGM Channel event counter threshold */
#define SEGM_EVENT_COUNTER_HIGH_VALUE                    ((uint32_t)0x0000000FU)        /*!< maximum threshold value */
#define NOT_SEGM_EVENT_COUNTER_VALUE(threshold)          (SEGM_EVENT_COUNTER_HIGH_VALUE < (threshold))

/* check SEGM EGM_EVENT enable */
#define NOT_SEGM_EGM_EVENT_ENABLE(event)                 (((event) != SEGM_EGM_EVENT0_ENABLE) && \
                                                          ((event) != SEGM_EGM_EVENT1_ENABLE) && \
                                                          ((event) != SEGM_EGM_EVENT2_ENABLE) && \
                                                          ((event) != SEGM_EGM_EVENT3_ENABLE) && \
                                                          ((event) != SEGM_EGM_EVENT4_ENABLE) && \
                                                          ((event) != SEGM_EGM_EVENT5_ENABLE) && \
                                                          ((event) != SEGM_EGM_EVENT6_ENABLE) && \
                                                          ((event) != SEGM_EGM_EVENT7_ENABLE))

/* check SEGM EGM_EVENT disable */
#define NOT_SEGM_EGM_EVENT_DISABLE(event)                (((event) != SEGM_EGM_EVENT0_DISABLE) && \
                                                          ((event) != SEGM_EGM_EVENT1_DISABLE) && \
                                                          ((event) != SEGM_EGM_EVENT2_DISABLE) && \
                                                          ((event) != SEGM_EGM_EVENT3_DISABLE) && \
                                                          ((event) != SEGM_EGM_EVENT4_DISABLE) && \
                                                          ((event) != SEGM_EGM_EVENT5_DISABLE) && \
                                                          ((event) != SEGM_EGM_EVENT6_DISABLE) && \
                                                          ((event) != SEGM_EGM_EVENT7_DISABLE))

/* check SEGM EGM_EVENT disable */
#define NOT_SEGM_SYSTEM_EVENT_FLAG(flag)                 (((flag) != EGM0_TRIG_SYSTEM_EVENT_FLAG0) && \
                                                          ((flag) != EGM1_TRIG_SYSTEM_EVENT_FLAG0) && \
                                                          ((flag) != EGM2_TRIG_SYSTEM_EVENT_FLAG0) && \
                                                          ((flag) != EGM3_TRIG_SYSTEM_EVENT_FLAG0) && \
                                                          ((flag) != EGM4_TRIG_SYSTEM_EVENT_FLAG0) && \
                                                          ((flag) != EGM5_TRIG_SYSTEM_EVENT_FLAG0) && \
                                                          ((flag) != EGM6_TRIG_SYSTEM_EVENT_FLAG0) && \
                                                          ((flag) != EGM7_TRIG_SYSTEM_EVENT_FLAG0) && \
                                                          ((flag) != EGM0_TRIG_SYSTEM_EVENT_FLAG1) && \
                                                          ((flag) != EGM1_TRIG_SYSTEM_EVENT_FLAG1) && \
                                                          ((flag) != EGM2_TRIG_SYSTEM_EVENT_FLAG1) && \
                                                          ((flag) != EGM3_TRIG_SYSTEM_EVENT_FLAG1) && \
                                                          ((flag) != EGM4_TRIG_SYSTEM_EVENT_FLAG1) && \
                                                          ((flag) != EGM5_TRIG_SYSTEM_EVENT_FLAG1) && \
                                                          ((flag) != EGM6_TRIG_SYSTEM_EVENT_FLAG1) && \
                                                          ((flag) != EGM7_TRIG_SYSTEM_EVENT_FLAG1) && \
                                                          ((flag) != EGM0_TRIG_SYSTEM_EVENT_FLAG2) && \
                                                          ((flag) != EGM1_TRIG_SYSTEM_EVENT_FLAG2) && \
                                                          ((flag) != EGM2_TRIG_SYSTEM_EVENT_FLAG2) && \
                                                          ((flag) != EGM3_TRIG_SYSTEM_EVENT_FLAG2) && \
                                                          ((flag) != EGM4_TRIG_SYSTEM_EVENT_FLAG2) && \
                                                          ((flag) != EGM5_TRIG_SYSTEM_EVENT_FLAG2) && \
                                                          ((flag) != EGM6_TRIG_SYSTEM_EVENT_FLAG2) && \
                                                          ((flag) != EGM7_TRIG_SYSTEM_EVENT_FLAG2) && \
                                                          ((flag) != EGM0_TRIG_SYSTEM_EVENT_FLAG3) && \
                                                          ((flag) != EGM1_TRIG_SYSTEM_EVENT_FLAG3) && \
                                                          ((flag) != EGM2_TRIG_SYSTEM_EVENT_FLAG3) && \
                                                          ((flag) != EGM3_TRIG_SYSTEM_EVENT_FLAG3) && \
                                                          ((flag) != EGM4_TRIG_SYSTEM_EVENT_FLAG3) && \
                                                          ((flag) != EGM5_TRIG_SYSTEM_EVENT_FLAG3) && \
                                                          ((flag) != EGM6_TRIG_SYSTEM_EVENT_FLAG3) && \
                                                          ((flag) != EGM7_TRIG_SYSTEM_EVENT_FLAG3))

/* check IOC IMR interrupt */
#define NOT_IOC_TMR_INTERRUPT(interrupt)                 (((interrupt) != IOC_INT_TMRERR_PSC) && \
                                                          ((interrupt) != IOC_INT_TMRERR_CLKEN) && \
                                                          ((interrupt) != IOC_INT_TMRERR_MCEN))

#define NOT_IOC_TMR_FLAG(flag)                           (((flag) != IOC_FLAG_TMRERR_PSC) && \
                                                          ((flag) != IOC_FLAG_TMRERR_CLKEN) && \
                                                          ((flag) != IOC_FLAG_TMRERR_MCEN))

#define NOT_IOC_TMR_INT_FLAG(int_flag)                   (((int_flag) != IOC_INT_FLAG_TMRERR_PSC) && \
                                                          ((int_flag) != IOC_INT_FLAG_TMRERR_CLKEN) && \
                                                          ((int_flag) != IOC_INT_FLAG_TMRERR_MCEN))

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */

/* enable IOC */
void ioc_enable(void);
/* disable IOC */
void ioc_disable(void);
/* reset IOC */
void ioc_reset(void);
/* get IOC enable flag */
FlagStatus ioc_enable_flag_get(void);
/* get IOC reset flag */
FlagStatus ioc_reset_flag_get(void);
/* clear IOC reset flag */
void ioc_reset_flag_clear(void);
/* enable IOC clock */
void ioc_clock_enable(void);
/* disable IOC clock */
void ioc_clock_disable(void);
/* configure IOC clock prescaler */
void ioc_prescaler_config(uint8_t psc);
/* configure IOC FPM mode */
void ioc_fpm_mode_config(ioc_fpmx_enum fpmx, uint32_t fpm_mode);
/* configure IOC FPM reference input signal selection */
void ioc_fpm_reference_signal_select(ioc_fpmx_enum fpmx, uint32_t input_signal);
/* configure IOC FPM monitor input signal selection */
void ioc_fpm_monitor_signal_select(ioc_fpmx_enum fpmx, uint32_t input_signal);
/* enable reset the counter of timer */
void ioc_fpm_timer_reset_enable(ioc_fpmx_enum fpmx);
/* disable reset the counter of timer, decrement the counter by one */
void ioc_fpm_timer_reset_disable(ioc_fpmx_enum fpmx);
/* configure the value of 16 bit comparator */
void ioc_fpm_cmp_config(ioc_fpmx_enum fpmx, uint16_t value);
/* get the value of reference signal FPM timer counter */
uint32_t ioc_rfpm_counter_get(ioc_fpmx_enum fpmx);
/* get the value of monitor signal FPM timer counter */
uint32_t ioc_mfpm_counter_get(ioc_fpmx_enum fpmx);
/* get reference signal FPM edge status */
FlagStatus ioc_rfpm_glitch_flag_get(ioc_fpmx_enum fpmx, ioc_fpm_edge_stat_enum edge_flag);
/* get monitor signal FPM edge status */
FlagStatus ioc_mfpm_glitch_flag_get(ioc_fpmx_enum fpmx, ioc_fpm_edge_stat_enum edge_flag);
/* clear reference signal FPM edge status */
void ioc_rfpm_glitch_flag_clear(ioc_fpmx_enum fpmx, ioc_fpm_edge_stat_enum edge_flag);
/* clear reference signal FPM edge status */
void ioc_mfpm_glitch_flag_clear(ioc_fpmx_enum fpmx, ioc_fpm_edge_stat_enum edge_flag);
/* enable TRIGSEL input selection for RSG combiner */
void ioc_rsg_input_enable(uint32_t trigsel_input);
/* disable TRIGSEL input selection for RSG combiner */
void ioc_rsg_input_disable(uint32_t trigsel_input);
/* select reference signal */
void ioc_egm_reference_signal_select(ioc_egmx_enum egmx, uint32_t ref_signal);
/* select monitor signal */
void ioc_egm_monitor_signal_select(ioc_egmx_enum egmx, uint32_t mon_signal);
/* enable invert reference signal */
void ioc_egm_reference_signal_invert_enable(ioc_egmx_enum egmx);
/* disable invert reference signal */
void ioc_egm_reference_signal_invert_disable(ioc_egmx_enum egmx);
/* enable invert monitor signal */
void ioc_egm_monitor_signal_invert_enable(ioc_egmx_enum egmx);
/* disable invert monitor signal */
void ioc_egm_monitor_signal_invert_disable(ioc_egmx_enum egmx);
/* slect event window generation signal */
void ioc_egm_event_window_signal_select(ioc_egmx_enum egmx, uint32_t signal);
/* elect event window triger edge */
void ioc_egm_event_window_triger_edge_select(ioc_egmx_enum egmx, uint32_t triger_edge);
/* enable event window inverted */
void ioc_egm_event_window_invert_enable(ioc_egmx_enum egmx);
/* disable event window inverted */
void ioc_egm_event_window_invert_disable(ioc_egmx_enum egmx);
/* enable events generated */
void ioc_egm_event_generate_enable(ioc_egmx_enum egmx);
/* disable events generated */
void ioc_egm_event_generate_disable(ioc_egmx_enum egmx);
/* configure event window generation run mode */
void ioc_egm_event_generate_mode_config(ioc_egmx_enum egmx, uint32_t mode);
/* enable monitor signal from the FPM compared with reference signal */
void ioc_egm_monitor_signal_compare_enable(ioc_egmx_enum egmx);
/* disable monitor signal from the FPM compared with reference signal, monitor signal is from monitor[x] */
void ioc_egm_monitor_signal_compare_disable(ioc_egmx_enum egmx);
/* configure event count threshold */
void ioc_egm_event_window_threshold_config(ioc_egmx_enum egmx, uint32_t threshold);
/* get the value of EGM event window counter */
uint32_t ioc_egm_event_window_counter_get(ioc_egmx_enum egmx);
/* get the overflow flag */
FlagStatus ioc_egm_counter_overflow_flag_get(ioc_egmx_enum egmx);
/* clear the overflow flag */
void ioc_egm_counter_overflow_flag_clear(ioc_egmx_enum egmx);
/* select SEGM channel event */
void ioc_segm_input_seclect(ioc_segm_channel_enum channel, uint32_t event);
/* select SEGM channel event */
void ioc_segm_counter_threshold_config(ioc_segm_channel_enum channel, uint32_t threshold);
/* enable EGM_EVENTx selection */
void ioc_segm_egm_event_enable(uint32_t egm_event);
/* disable EGM_ETMx selection */
void ioc_segm_egm_event_disable(uint32_t egm_event);
/* enable SEGM channel selection */
void ioc_segm_channel_enable(ioc_segm_channel_enum channel);
/* disable SEGM channel selection */
void ioc_segm_channel_disable(ioc_segm_channel_enum channel);
/* get SEGM system event recore flag */
FlagStatus ioc_segm_history_trigge_flag_get(ioc_segm_generate_event_flag_enum flag);
/* enable IOC TMR interrupt */
void ioc_tmr_interrupt_enable(ioc_tmr_interrupt_enum tmr_interrupt);
/* disable IOC TMR interrupt */
void ioc_tmr_interrupt_disable(ioc_tmr_interrupt_enum tmr_interrupt);
/* get IOC TMR flag */
FlagStatus ioc_tmr_flag_get(ioc_tmr_flag_enum tmr_flag);
/* clear IOC TMR flag */
void ioc_tmr_flag_clear(ioc_tmr_flag_enum tmr_flag);
/* get IOC TMR interrupt and flag status */
FlagStatus ioc_tmr_interrupt_flag_get(ioc_tmr_interrupt_flag_enum tmr_int_flag);
/* enable alarm interrupt */
void ioc_alarm_interrupt_enable(void);
/* disable alarm interrupt */
void ioc_alarm_interrupt_disable(void);
/* get SEGM event trigger flag */
FlagStatus ioc_segm_systerm_event_trigge_flag_get(void);
/* clear SEGM event trigger flag */
void ioc_segm_systerm_event_trigge_flag_clear(void);

#endif /* GD32A7XX_IOC_H */
