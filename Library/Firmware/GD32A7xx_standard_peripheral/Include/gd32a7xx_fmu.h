/*!
    \file    gd32a7xx_fmu.h
    \brief   definitions for the FMU

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

#ifndef GD32A7XX_FMU_H
#define GD32A7XX_FMU_H

#include "gd32a7xx.h"

/* FMU definitions */
#define FMU                                      FMU_BASE + 0x00000000U                                    /*!< FMU base address */
#define FMU_FGTSEN_BASE                          FMU_BASE + 0x00000140U                                    /*!< FMU fault group trigger source enable register base address */
#define FMU_FGTSSTAT_BASE                        FMU_BASE + 0x00000160U                                    /*!< FMU fault group trigger source status register base address */
#define FMU_FGSWTEN_BASE                         FMU_BASE + 0x00000180U                                    /*!< FMU fault group software triggered fault enable register base address */

/* registers definitions */
#define FMU_CTL                                  REG32((FMU) + 0x00000000U)                                /*!< FMU control register */
#define FMU_CTLKEY                               REG32((FMU) + 0x00000004U)                                /*!< FMU control key register */
#define FMU_CFG                                  REG32((FMU) + 0x00000008U)                                /*!< FMU configuration register */
#define FMU_FGCFG                                REG32((FMU) + 0x0000001CU)                                /*!< FMU fault group configuration register */
#define FMU_FGSUBSRCFG                           REG32((FMU) + 0x0000004CU)                                /*!< FMU fault group subsystem reset configuration register */
#define FMU_FGSTAT                               REG32((FMU) + 0x00000080U)                                /*!< FMU fault group status register */
#define FMU_FGKEY                                REG32((FMU) + 0x00000090U)                                /*!< FMU fault group key register */
#define FMU_FGEN                                 REG32((FMU) + 0x00000094U)                                /*!< FMU fault group enable register  */
#define FMU_FGCMTEN                              REG32((FMU) + 0x000000A4U)                                /*!< FMU fault group CAUTION work mode timeout enable register */
#define FMU_FGCMTVAL                             REG32((FMU) + 0x000000B4U)                                /*!< FMU fault group CAUTION work mode timeout value register */
#define FMU_IMTVAL                               REG32((FMU) + 0x000000B8U)                                /*!< FMU INIT work mode timeout value register */
#define FMU_FPCTL                                REG32((FMU) + 0x000000BCU)                                /*!< FMU fault pin control */
#define FMU_STAT                                 REG32((FMU) + 0x000000C0U)                                /*!< FMU status register */
#define FMU_NTCHSTAT                             REG32((FMU) + 0x000000C4U)                                /*!< FMU NORMAL transform to CAUTION work mode hold status register */
#define FMU_CTFHSTAT                             REG32((FMU) + 0x000000C8U)                                /*!< FMU CAUTION transform to FAULT work mode hold status register */
#define FMU_NTFHSTAT                             REG32((FMU) + 0x000000CCU)                                /*!< NORMAL transform to FAULT work mode hold status register */
#define FMU_FTCHSTAT                             REG32((FMU) + 0x000000D0U)                                /*!< FMU FAULT transform to CAUTION work mode hold status register */
#define FMU_FFGNCFG                              REG32((FMU) + 0x000000DCU)                                /*!< FMU fake fault group fault number configuration register  */
#define FMU_INTRPD                               REG32((FMU) + 0x000000E0U)                                /*!< FMU interrupt request pending register */
#define FMU_IMTINTREN                            REG32((FMU) + 0x000000E4U)                                /*!< FMU INIT work mode timeout interrupt request enable register */
#define FMU_TCLOCK                               REG32((FMU) + 0x000000F0U)                                /*!< FMU temporary configuration lock register  */
#define FMU_PCLOCK                               REG32((FMU) + 0x000000F4U)                                /*!< FMU permanent Configuration Lock register */
#define FMU_FOT                                  REG32((FMU) + 0x000000F8U)                                /*!< FMU fault output timer register */
#define FMU_CMINTREN                             REG32((FMU) + 0x000000FCU)                                /*!< FMU fault group CAUTION work mode interrupt request enable register */
#define FMU_FMNMIINTREN                          REG32((FMU) + 0x0000010CU)                                /*!< FMU fault group FAULT work mode NMI interrupt request enable register */
#define FMU_FPOEN                                REG32((FMU) + 0x0000011CU)                                /*!< FMU fault group FFIO output enable register */
#define FMU_GPOEN                                REG32((FMU) + 0x00000120U)                                /*!< FMU fault group GFIO output enable register */
#define FMU_FHTOEN                               REG32((FMU) + 0x00000124U)                                /*!< FMU fault holding timer output enable register */
#define FMU_CMCNT                                REG32((FMU) + 0x0000012CU)                                /*!< FMU fault group CAUTION work mode counter register */
#define FMU_IMCNT                                REG32((FMU) + 0x00000134U)                                /*!< FMU fault group INIT work mode counter register  */
#define FMU_FOCNT                                REG32((FMU) + 0x00000138U)                                /*!< FMU fatal fault output counter register */
#define FMU_GOCNT                                REG32((FMU) + 0x0000013CU)                                /*!< FMU general fault output counter register */
#define FMU_FGTSEN(x)                            REG32((uint32_t)(FMU_FGTSEN_BASE + ((x) << 2)))           /*!< FMU fault group trigger source enable register */
#define FMU_FGTSSTAT(x)                          REG32((uint32_t)(FMU_FGTSSTAT_BASE + ((x) << 2)))         /*!< FMU fault group trigger source status register */
#define FMU_FG_SWTEN(x)                          REG32((uint32_t)(FMU_FGSWTEN_BASE + ((x) << 2)))          /*!< FMU fault group software triggered fault enable register */
#define FMU_TMRES                                REG32((FMU) + 0x00000240U)                                /*!< FMU TMR enable and status register */

/* bits definitions */
/* FMU_CTL */
#define FMU_CTL_EOP                              BITS(0,4)                                                 /*!< execute operation bits */
#define FMU_CTL_OPSTAT                           BITS(6,7)                                                 /*!< operation status bits */
#define FMU_CTL_DBGEN                            BIT(9)                                                    /*!< debug mode enable bit */

/* FMU_CTLKEY */
#define FMU_CTLKEY_CTLKEY                        BITS(0,31)                                                /*!< unlock operation control key */

/* FMU_CFG */
#define FMU_CFG_GOMSET                           BITS(3,5)                                                 /*!< GFIO signals work mode set bits */
#define FMU_CFG_FOMSET                           BITS(6,8)                                                 /*!< FFIO signals work mode set bits */
#define FMU_CFG_FOPCFG                           BIT(9)                                                    /*!< FFIO signals polarity configuration bit */
#define FMU_CFG_GOPCFG                           BIT(10)                                                   /*!< GFIO signal polarity configuration bit */
#define FMU_CFG_FOMCFG                           BIT(11)                                                   /*!< FFIO signals work mode configuration bit */
#define FMU_CFG_FOPRE                            BITS(16,19)                                               /*!< FFIO signals time switching clock prescaler configuration bits */
#define FMU_CFG_GOSCFG                           BITS(20,21)                                               /*!< GFIO signals configuration bits */
#define FMU_CFG_FOSCFG                           BITS(22,23)                                               /*!< FFIO signals configuration bits */
#define FMU_CFG_FOSEN                            BIT(24)                                                   /*!< FFIO signals enable bit */
#define FMU_CFG_GOSEN                            BIT(25)                                                   /*!< GFIO signals enable bit */

/* FMU_FGCFG */
#define FMU_FGCFG_FGCFG0                         BIT(0)                                                    /*!< fault group recovery type configuration bit0 */
#define FMU_FGCFG_FGCFG1                         BIT(1)                                                    /*!< fault group recovery type configuration bit1 */
#define FMU_FGCFG_FGCFG2                         BIT(2)                                                    /*!< fault group recovery type configuration bit2 */
#define FMU_FGCFG_FGCFG3                         BIT(3)                                                    /*!< fault group recovery type configuration bit3 */
#define FMU_FGCFG_FGCFG4                         BIT(4)                                                    /*!< fault group recovery type configuration bit4 */
#define FMU_FGCFG_FGCFG5                         BIT(5)                                                    /*!< fault group recovery type configuration bit5 */
#define FMU_FGCFG_FGCFG6                         BIT(6)                                                    /*!< fault group recovery type configuration bit6 */
#define FMU_FGCFG_FGCFG7                         BIT(7)                                                    /*!< fault group recovery type configuration bit7 */
#define FMU_FGCFG_FGCFG8                         BIT(8)                                                    /*!< fault group recovery type configuration bit8 */
#define FMU_FGCFG_FGCFG9                         BIT(9)                                                    /*!< fault group recovery type configuration bit9 */
#define FMU_FGCFG_FGCFG10                        BIT(10)                                                   /*!< fault group recovery type configuration bit10 */
#define FMU_FGCFG_FGCFG11                        BIT(11)                                                   /*!< fault group recovery type configuration bit11 */

/* FMU_FGSUBSRCFG */
#define FMU_FGSUBSRCFG_RST0                      BITS(0,1)                                                 /*!< fault group subsystem reset reaction configuration  bits0 */
#define FMU_FGSUBSRCFG_RST1                      BITS(2,3)                                                 /*!< fault group subsystem reset reaction configuration  bits1 */
#define FMU_FGSUBSRCFG_RST2                      BITS(4,5)                                                 /*!< fault group subsystem reset reaction configuration  bits2 */
#define FMU_FGSUBSRCFG_RST3                      BITS(6,7)                                                 /*!< fault group subsystem reset reaction configuration  bits3 */
#define FMU_FGSUBSRCFG_RST4                      BITS(8,9)                                                 /*!< fault group subsystem reset reaction configuration  bits4 */
#define FMU_FGSUBSRCFG_RST5                      BITS(10,11)                                               /*!< fault group subsystem reset reaction configuration  bits5 */
#define FMU_FGSUBSRCFG_RST6                      BITS(12,13)                                               /*!< fault group subsystem reset reaction configuration  bits6 */
#define FMU_FGSUBSRCFG_RST7                      BITS(14,15)                                               /*!< fault group subsystem reset reaction configuration  bits7 */
#define FMU_FGSUBSRCFG_RST8                      BITS(16,17)                                               /*!< fault group subsystem reset reaction configuration  bits8 */
#define FMU_FGSUBSRCFG_RST9                      BITS(18,19)                                               /*!< fault group subsystem reset reaction configuration  bits9 */
#define FMU_FGSUBSRCFG_RST10                     BITS(20,21)                                               /*!< fault group subsystem reset reaction configuration  bits10 */
#define FMU_FGSUBSRCFG_RST11                     BITS(22,23)                                               /*!< fault group subsystem reset reaction configuration  bits11 */

/* FMU_FGSTAT */
#define FMU_FGSTAT_FGSTAT0                       BIT(0)                                                    /*!< fault group fault status bit0 */
#define FMU_FGSTAT_FGSTAT1                       BIT(1)                                                    /*!< fault group fault status bit1 */
#define FMU_FGSTAT_FGSTAT2                       BIT(2)                                                    /*!< fault group fault status bit2 */
#define FMU_FGSTAT_FGSTAT3                       BIT(3)                                                    /*!< fault group fault status bit3 */
#define FMU_FGSTAT_FGSTAT4                       BIT(4)                                                    /*!< fault group fault status bit4 */
#define FMU_FGSTAT_FGSTAT5                       BIT(5)                                                    /*!< fault group fault status bit5 */
#define FMU_FGSTAT_FGSTAT6                       BIT(6)                                                    /*!< fault group fault status bit6 */
#define FMU_FGSTAT_FGSTAT7                       BIT(7)                                                    /*!< fault group fault status bit7 */
#define FMU_FGSTAT_FGSTAT8                       BIT(8)                                                    /*!< fault group fault status bit8 */
#define FMU_FGSTAT_FGSTAT9                       BIT(9)                                                    /*!< fault group fault status bit9 */
#define FMU_FGSTAT_FGSTAT10                      BIT(10)                                                   /*!< fault group fault status bit10 */
#define FMU_FGSTAT_FGSTAT11                      BIT(11)                                                   /*!< fault group fault status bit11 */

/* FMU_FGKEY */
#define FMU_FGKEY_FGKEY                          BITS(0,31)                                                /*!< unlock fault group status register key */

/* FMU_FGEN */
#define FMU_FGEN_FGEN0                           BIT(0)                                                    /*!< fault group enable bit0 */
#define FMU_FGEN_FGEN1                           BIT(1)                                                    /*!< fault group enable bit1 */
#define FMU_FGEN_FGEN2                           BIT(2)                                                    /*!< fault group enable bit2 */
#define FMU_FGEN_FGEN3                           BIT(3)                                                    /*!< fault group enable bit3 */
#define FMU_FGEN_FGEN4                           BIT(4)                                                    /*!< fault group enable bit4 */
#define FMU_FGEN_FGEN5                           BIT(5)                                                    /*!< fault group enable bit5 */
#define FMU_FGEN_FGEN6                           BIT(6)                                                    /*!< fault group enable bit6 */
#define FMU_FGEN_FGEN7                           BIT(7)                                                    /*!< fault group enable bit7 */
#define FMU_FGEN_FGEN8                           BIT(8)                                                    /*!< fault group enable bit8 */
#define FMU_FGEN_FGEN9                           BIT(9)                                                    /*!< fault group enable bit9 */
#define FMU_FGEN_FGEN10                          BIT(10)                                                   /*!< fault group enable bit10 */
#define FMU_FGEN_FGEN11                          BIT(11)                                                   /*!< fault group enable bit11 */

/* FMU_FGCMTEN */
#define FMU_FGCMTEN_FGCMTEN0                     BIT(0)                                                    /*!< fault group CAUTION work mode timeout enable bit0 */
#define FMU_FGCMTEN_FGCMTEN1                     BIT(1)                                                    /*!< fault group CAUTION work mode timeout enable bit1 */
#define FMU_FGCMTEN_FGCMTEN2                     BIT(2)                                                    /*!< fault group CAUTION work mode timeout enable bit2 */
#define FMU_FGCMTEN_FGCMTEN3                     BIT(3)                                                    /*!< fault group CAUTION work mode timeout enable bit3 */
#define FMU_FGCMTEN_FGCMTEN4                     BIT(4)                                                    /*!< fault group CAUTION work mode timeout enable bit4 */
#define FMU_FGCMTEN_FGCMTEN5                     BIT(5)                                                    /*!< fault group CAUTION work mode timeout enable bit5 */
#define FMU_FGCMTEN_FGCMTEN6                     BIT(6)                                                    /*!< fault group CAUTION work mode timeout enable bit6 */
#define FMU_FGCMTEN_FGCMTEN7                     BIT(7)                                                    /*!< fault group CAUTION work mode timeout enable bit7 */
#define FMU_FGCMTEN_FGCMTEN8                     BIT(8)                                                    /*!< fault group CAUTION work mode timeout enable bit8 */
#define FMU_FGCMTEN_FGCMTEN9                     BIT(9)                                                    /*!< fault group CAUTION work mode timeout enable bit9 */
#define FMU_FGCMTEN_FGCMTEN10                    BIT(10)                                                   /*!< fault group CAUTION work mode timeout enable bit10 */
#define FMU_FGCMTEN_FGCMTEN11                    BIT(11)                                                   /*!< fault group CAUTION work mode timeout enable bit11 */

/* FMU_FGCMTVAL */
#define FMU_FGCMTVAL_FGCMTVAL                    BITS(0,31)                                                /*!< fault group CAUTION work mode timeout value bits */

/* FMU_IMTVAL */
#define FMU_IMTVAL_IMTVAL                        BITS(0,2)                                                 /*!< FMU INIT work mode timeout value bits */

/* FMU_FPCTL */ 
#define FMU_FPCTL_FPO0                           BIT(0)                                                    /*!< FFIO0 output signal configuration bit */
#define FMU_FPCTL_FPO1                           BIT(1)                                                    /*!< FFIO1 output signal configuration bit */
#define FMU_FPCTL_GPO                            BIT(2)                                                    /*!< GFIO output signal configuration bit */
#define FMU_FPCTL_FPI0                           BIT(4)                                                    /*!< FFIO0 signal input status */
#define FMU_FPCTL_FPI1                           BIT(5)                                                    /*!< FFIO1 signal input status */
#define FMU_FPCTL_GPI                            BIT(6)                                                    /*!< GFIO signal input status */

/* FMU_STAT */
#define FMU_STAT_FCSTAT                          BITS(0,2)                                                 /*!< FMU current work mode state bits */
#define FMU_STAT_FSTAT                           BIT(3)                                                    /*!< FMU faulty state bit */
#define FMU_STAT_FPSTAT                          BITS(4,5)                                                 /*!< FFIO signal states */
#define FMU_STAT_GPSTAT                          BIT(6)                                                    /*!< GFIO signal states */

/* FMU_NTCHSTAT */
#define FMU_NTCHSTAT_NTCHSTAT0                   BIT(0)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit0 */
#define FMU_NTCHSTAT_NTCHSTAT1                   BIT(1)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit1 */
#define FMU_NTCHSTAT_NTCHSTAT2                   BIT(2)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit2 */
#define FMU_NTCHSTAT_NTCHSTAT3                   BIT(3)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit3 */
#define FMU_NTCHSTAT_NTCHSTAT4                   BIT(4)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit4 */
#define FMU_NTCHSTAT_NTCHSTAT5                   BIT(5)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit5 */
#define FMU_NTCHSTAT_NTCHSTAT6                   BIT(6)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit6 */
#define FMU_NTCHSTAT_NTCHSTAT7                   BIT(7)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit7 */
#define FMU_NTCHSTAT_NTCHSTAT8                   BIT(8)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit8 */
#define FMU_NTCHSTAT_NTCHSTAT9                   BIT(9)                                                    /*!< NORMAL transform to CAUTION work mode hold status bit9 */
#define FMU_NTCHSTAT_NTCHSTAT10                  BIT(10)                                                   /*!< NORMAL transform to CAUTION work mode hold status bit10 */
#define FMU_NTCHSTAT_NTCHSTAT11                  BIT(11)                                                   /*!< NORMAL transform to CAUTION work mode hold status bit11 */

/* FMU_CTFHSTAT */
#define FMU_CTFHSTAT_CTFHSTAT0                   BIT(0)                                                    /*!< CAUTION transform to FAULT work mode hold status bit0 */
#define FMU_CTFHSTAT_CTFHSTAT1                   BIT(1)                                                    /*!< CAUTION transform to FAULT work mode hold status bit1 */
#define FMU_CTFHSTAT_CTFHSTAT2                   BIT(2)                                                    /*!< CAUTION transform to FAULT work mode hold status bit2 */
#define FMU_CTFHSTAT_CTFHSTAT3                   BIT(3)                                                    /*!< CAUTION transform to FAULT work mode hold status bit3 */
#define FMU_CTFHSTAT_CTFHSTAT4                   BIT(4)                                                    /*!< CAUTION transform to FAULT work mode hold status bit4 */
#define FMU_CTFHSTAT_CTFHSTAT5                   BIT(5)                                                    /*!< CAUTION transform to FAULT work mode hold status bit5 */
#define FMU_CTFHSTAT_CTFHSTAT6                   BIT(6)                                                    /*!< CAUTION transform to FAULT work mode hold status bit6 */
#define FMU_CTFHSTAT_CTFHSTAT7                   BIT(7)                                                    /*!< CAUTION transform to FAULT work mode hold status bit7 */
#define FMU_CTFHSTAT_CTFHSTAT8                   BIT(8)                                                    /*!< CAUTION transform to FAULT work mode hold status bit8 */
#define FMU_CTFHSTAT_CTFHSTAT9                   BIT(9)                                                    /*!< CAUTION transform to FAULT work mode hold status bit9 */
#define FMU_CTFHSTAT_CTFHSTAT10                  BIT(10)                                                   /*!< CAUTION transform to FAULT work mode hold status bit10 */
#define FMU_CTFHSTAT_CTFHSTAT11                  BIT(11)                                                   /*!< CAUTION transform to FAULT work mode hold status bit11 */

/* FMU_NTFHSTAT */
#define FMU_NTFHSTAT_NTFHSTAT0                   BIT(0)                                                    /*!< NORMAL transform to FAULT work mode hold status bit0 */
#define FMU_NTFHSTAT_NTFHSTAT1                   BIT(1)                                                    /*!< NORMAL transform to FAULT work mode hold status bit1 */
#define FMU_NTFHSTAT_NTFHSTAT2                   BIT(2)                                                    /*!< NORMAL transform to FAULT work mode hold status bit2 */
#define FMU_NTFHSTAT_NTFHSTAT3                   BIT(3)                                                    /*!< NORMAL transform to FAULT work mode hold status bit3 */
#define FMU_NTFHSTAT_NTFHSTAT4                   BIT(4)                                                    /*!< NORMAL transform to FAULT work mode hold status bit4 */
#define FMU_NTFHSTAT_NTFHSTAT5                   BIT(5)                                                    /*!< NORMAL transform to FAULT work mode hold status bit5 */
#define FMU_NTFHSTAT_NTFHSTAT6                   BIT(6)                                                    /*!< NORMAL transform to FAULT work mode hold status bit6 */
#define FMU_NTFHSTAT_NTFHSTAT7                   BIT(7)                                                    /*!< NORMAL transform to FAULT work mode hold status bit7 */
#define FMU_NTFHSTAT_NTFHSTAT8                   BIT(8)                                                    /*!< NORMAL transform to FAULT work mode hold status bit8 */
#define FMU_NTFHSTAT_NTFHSTAT9                   BIT(9)                                                    /*!< NORMAL transform to FAULT work mode hold status bit9 */
#define FMU_NTFHSTAT_NTFHSTAT10                  BIT(10)                                                   /*!< NORMAL transform to FAULT work mode hold status bit10 */
#define FMU_NTFHSTAT_NTFHSTAT11                  BIT(11)                                                   /*!< NORMAL transform to FAULT work mode hold status bit11 */

/* FMU_FTCHSTAT */
#define FMU_FTCHSTAT_FTCHSTAT0                   BIT(0)                                                    /*!< FAULT transform to CAUTION work mode hold status bit0 */
#define FMU_FTCHSTAT_FTCHSTAT1                   BIT(1)                                                    /*!< FAULT transform to CAUTION work mode hold status bit1 */
#define FMU_FTCHSTAT_FTCHSTAT2                   BIT(2)                                                    /*!< FAULT transform to CAUTION work mode hold status bit2 */
#define FMU_FTCHSTAT_FTCHSTAT3                   BIT(3)                                                    /*!< FAULT transform to CAUTION work mode hold status bit3 */
#define FMU_FTCHSTAT_FTCHSTAT4                   BIT(4)                                                    /*!< FAULT transform to CAUTION work mode hold status bit4 */
#define FMU_FTCHSTAT_FTCHSTAT5                   BIT(5)                                                    /*!< FAULT transform to CAUTION work mode hold status bit5 */
#define FMU_FTCHSTAT_FTCHSTAT6                   BIT(6)                                                    /*!< FAULT transform to CAUTION work mode hold status bit6 */
#define FMU_FTCHSTAT_FTCHSTAT7                   BIT(7)                                                    /*!< FAULT transform to CAUTION work mode hold status bit7 */
#define FMU_FTCHSTAT_FTCHSTAT8                   BIT(8)                                                    /*!< FAULT transform to CAUTION work mode hold status bit8 */
#define FMU_FTCHSTAT_FTCHSTAT9                   BIT(9)                                                    /*!< FAULT transform to CAUTION work mode hold status bit9 */
#define FMU_FTCHSTAT_FTCHSTAT10                  BIT(10)                                                   /*!< FAULT transform to CAUTION work mode hold status bit10 */
#define FMU_FTCHSTAT_FTCHSTAT11                  BIT(11)                                                   /*!< FAULT transform to CAUTION work mode hold status bit11 */

/* FMU_FFGNCFG */
#define FMU_FFGNCFG_NUM                          BITS(0,7)                                                 /*!< injection fake fake FG fault number */
#define FMU_FFGNCFG_FFGEN                        BITS(8,9)                                                 /*!< fake FG fault enable enable */

/* FMU_INTRPD */
#define FMU_INTRPD_INITINTRPD                    BIT(0)                                                    /*!< INIT work mode timeout interrupt request pending bit */
#define FMU_INTRPD_CAUINTRPD                     BIT(1)                                                    /*!< CAUTION work mode interrupt request pending bit */
#define FMU_INTRPD_NMIINTRPD                     BIT(2)                                                    /*!< NMI interrupt request pending bit */

/* FMU_IMTINTREN */
#define FMU_IMTINTREN_INITTIE                    BIT(0)                                                    /*!< INIT work mode timeout interrupt enable bit */

/* FMU_TCLOCK */
#define FMU_TCLOCK_TCLK                          BITS(0,8)                                                 /*!< INIT work mode transition temporary lock bits */

/* FMU_PCLOCK */
#define FMU_PCLOCK_VPCLK                         BITS(0,8)                                                 /*!< INIT work mode transition permanent lock bits */

/* FMU_FOT */
#define FMU_FOT_FOT                              BITS(0,13)                                                /*!< fault output(FFIO) timer configure bits */

/* FMU_CMINTREN */ 
#define FMU_CMINTREN_CMINTREN0                   BIT(0)                                                    /*!< CAUTION work mode interrupt request enable bit0 */
#define FMU_CMINTREN_CMINTREN1                   BIT(1)                                                    /*!< CAUTION work mode interrupt request enable bit1 */
#define FMU_CMINTREN_CMINTREN2                   BIT(2)                                                    /*!< CAUTION work mode interrupt request enable bit2 */
#define FMU_CMINTREN_CMINTREN3                   BIT(3)                                                    /*!< CAUTION work mode interrupt request enable bit3 */
#define FMU_CMINTREN_CMINTREN4                   BIT(4)                                                    /*!< CAUTION work mode interrupt request enable bit4 */
#define FMU_CMINTREN_CMINTREN5                   BIT(5)                                                    /*!< CAUTION work mode interrupt request enable bit5 */
#define FMU_CMINTREN_CMINTREN6                   BIT(6)                                                    /*!< CAUTION work mode interrupt request enable bit6 */
#define FMU_CMINTREN_CMINTREN7                   BIT(7)                                                    /*!< CAUTION work mode interrupt request enable bit7 */
#define FMU_CMINTREN_CMINTREN8                   BIT(8)                                                    /*!< CAUTION work mode interrupt request enable bit8 */
#define FMU_CMINTREN_CMINTREN9                   BIT(9)                                                    /*!< CAUTION work mode interrupt request enable bit9 */
#define FMU_CMINTREN_CMINTREN10                  BIT(10)                                                   /*!< CAUTION work mode interrupt request enable bit10 */
#define FMU_CMINTREN_CMINTREN11                  BIT(11)                                                   /*!< CAUTION work mode interrupt request enable bit11 */

/* FMU_FMNMIINTREN*/
#define FMU_FMNMIINTREN_FMNMIINTREN0             BIT(0)                                                    /*!< FAULT work mode NMI interrupt request enable bit0 */
#define FMU_FMNMIINTREN_FMNMIINTREN1             BIT(1)                                                    /*!< FAULT work mode NMI interrupt request enable bit1 */
#define FMU_FMNMIINTREN_FMNMIINTREN2             BIT(2)                                                    /*!< FAULT work mode NMI interrupt request enable bit2 */
#define FMU_FMNMIINTREN_FMNMIINTREN3             BIT(3)                                                    /*!< FAULT work mode NMI interrupt request enable bit3 */
#define FMU_FMNMIINTREN_FMNMIINTREN4             BIT(4)                                                    /*!< FAULT work mode NMI interrupt request enable bit4 */
#define FMU_FMNMIINTREN_FMNMIINTREN5             BIT(5)                                                    /*!< FAULT work mode NMI interrupt request enable bit5 */
#define FMU_FMNMIINTREN_FMNMIINTREN6             BIT(6)                                                    /*!< FAULT work mode NMI interrupt request enable bit6 */
#define FMU_FMNMIINTREN_FMNMIINTREN7             BIT(7)                                                    /*!< FAULT work mode NMI interrupt request enable bit7 */
#define FMU_FMNMIINTREN_FMNMIINTREN8             BIT(8)                                                    /*!< FAULT work mode NMI interrupt request enable bit8 */
#define FMU_FMNMIINTREN_FMNMIINTREN9             BIT(9)                                                    /*!< FAULT work mode NMI interrupt request enable bit9 */
#define FMU_FMNMIINTREN_FMNMIINTREN10            BIT(10)                                                   /*!< FAULT work mode NMI interrupt request enable bit10 */
#define FMU_FMNMIINTREN_FMNMIINTREN11            BIT(11)                                                   /*!< FAULT work mode NMI interrupt request enable bit11 */

/* FMU_FPOEN */
#define FMU_FPOEN_FPOEN0                         BIT(0)                                                    /*!< FAULT work mode FFIO signaling enable bit0 */
#define FMU_FPOEN_FPOEN1                         BIT(1)                                                    /*!< FAULT work mode FFIO signaling enable bit1 */
#define FMU_FPOEN_FPOEN2                         BIT(2)                                                    /*!< FAULT work mode FFIO signaling enable bit2 */
#define FMU_FPOEN_FPOEN3                         BIT(3)                                                    /*!< FAULT work mode FFIO signaling enable bit3 */
#define FMU_FPOEN_FPOEN4                         BIT(4)                                                    /*!< FAULT work mode FFIO signaling enable bit4 */
#define FMU_FPOEN_FPOEN5                         BIT(5)                                                    /*!< FAULT work mode FFIO signaling enable bit5 */
#define FMU_FPOEN_FPOEN6                         BIT(6)                                                    /*!< FAULT work mode FFIO signaling enable bit6 */
#define FMU_FPOEN_FPOEN7                         BIT(7)                                                    /*!< FAULT work mode FFIO signaling enable bit7 */
#define FMU_FPOEN_FPOEN8                         BIT(8)                                                    /*!< FAULT work mode FFIO signaling enable bit8 */
#define FMU_FPOEN_FPOEN9                         BIT(9)                                                    /*!< FAULT work mode FFIO signaling enable bit9 */
#define FMU_FPOEN_FPOEN10                        BIT(10)                                                   /*!< FAULT work mode FFIO signaling enable bit10 */
#define FMU_FPOEN_FPOEN11                        BIT(11)                                                   /*!< FAULT work mode FFIO signaling enable bit11 */

/* FMU_GPOEN */
#define FMU_GPOEN_GPOEN0                         BIT(0)                                                    /*!< FAULT work mode GFIO signaling enable bit0 */
#define FMU_GPOEN_GPOEN1                         BIT(1)                                                    /*!< FAULT work mode GFIO signaling enable bit1 */
#define FMU_GPOEN_GPOEN2                         BIT(2)                                                    /*!< FAULT work mode GFIO signaling enable bit2 */
#define FMU_GPOEN_GPOEN3                         BIT(3)                                                    /*!< FAULT work mode GFIO signaling enable bit3 */
#define FMU_GPOEN_GPOEN4                         BIT(4)                                                    /*!< FAULT work mode GFIO signaling enable bit4 */
#define FMU_GPOEN_GPOEN5                         BIT(5)                                                    /*!< FAULT work mode GFIO signaling enable bit5 */
#define FMU_GPOEN_GPOEN6                         BIT(6)                                                    /*!< FAULT work mode GFIO signaling enable bit6 */
#define FMU_GPOEN_GPOEN7                         BIT(7)                                                    /*!< FAULT work mode GFIO signaling enable bit7 */
#define FMU_GPOEN_GPOEN8                         BIT(8)                                                    /*!< FAULT work mode GFIO signaling enable bit8 */
#define FMU_GPOEN_GPOEN9                         BIT(9)                                                    /*!< FAULT work mode GFIO signaling enable bit9 */
#define FMU_GPOEN_GPOEN10                        BIT(10)                                                   /*!< FAULT work mode GFIO signaling enable bit10 */
#define FMU_GPOEN_GPOEN11                        BIT(11)                                                   /*!< FAULT work mode GFIO signaling enable bit11 */

/* FMU_FHTOEN */
#define FMU_FHTOEN_FHTOEN0                       BIT(0)                                                    /*!< FAULT work mode holding timer output enable bit0 */
#define FMU_FHTOEN_FHTOEN1                       BIT(1)                                                    /*!< FAULT work mode holding timer output enable bit1 */
#define FMU_FHTOEN_FHTOEN2                       BIT(2)                                                    /*!< FAULT work mode holding timer output enable bit2 */
#define FMU_FHTOEN_FHTOEN3                       BIT(3)                                                    /*!< FAULT work mode holding timer output enable bit3 */
#define FMU_FHTOEN_FHTOEN4                       BIT(4)                                                    /*!< FAULT work mode holding timer output enable bit4 */
#define FMU_FHTOEN_FHTOEN5                       BIT(5)                                                    /*!< FAULT work mode holding timer output enable bit5 */
#define FMU_FHTOEN_FHTOEN6                       BIT(6)                                                    /*!< FAULT work mode holding timer output enable bit6 */
#define FMU_FHTOEN_FHTOEN7                       BIT(7)                                                    /*!< FAULT work mode holding timer output enable bit7 */
#define FMU_FHTOEN_FHTOEN8                       BIT(8)                                                    /*!< FAULT work mode holding timer output enable bit8 */
#define FMU_FHTOEN_FHTOEN9                       BIT(9)                                                    /*!< FAULT work mode holding timer output enable bit9 */
#define FMU_FHTOEN_FHTOEN10                      BIT(10)                                                   /*!< FAULT work mode holding timer output enable bit10 */
#define FMU_FHTOEN_FHTOEN11                      BIT(11)                                                   /*!< FAULT work mode holding timer output enable bit11 */

/* FMU_CMCNT */
#define FMU_CMCNT_CMCNT                          BITS(0,31)                                                /*!< CAUTION work mode timer count configure bits */

/* FMU_IMCNT */
#define FMU_IMCNT_IMCNT                          BITS(0,31)                                                /*!< INIT work mode timer count configure bits */

/* FMU_FOCNT */
#define FMU_FOCNT_FOCNT                          BITS(0,31)                                                /*!< fatal fault output timer count configure bits */

/* FMU_GOCNT */
#define FMU_GOCNT_GOCNT                          BITS(0,31)                                                /*!< general fault output timer count configure bits */

/* FMU_FGINTEN(x) (x=0...4) */
#define FMU_FGTSEN_FGTSEN0                       BIT(0)                                                    /*!< FG trigger source enable bit0 */
#define FMU_FGTSEN_FGTSEN1                       BIT(1)                                                    /*!< FG trigger source enable bit1 */
#define FMU_FGTSEN_FGTSEN2                       BIT(2)                                                    /*!< FG trigger source enable bit2 */
#define FMU_FGTSEN_FGTSEN3                       BIT(3)                                                    /*!< FG trigger source enable bit3 */
#define FMU_FGTSEN_FGTSEN4                       BIT(4)                                                    /*!< FG trigger source enable bit4 */
#define FMU_FGTSEN_FGTSEN5                       BIT(5)                                                    /*!< FG trigger source enable bit5 */
#define FMU_FGTSEN_FGTSEN6                       BIT(6)                                                    /*!< FG trigger source enable bit6 */
#define FMU_FGTSEN_FGTSEN7                       BIT(7)                                                    /*!< FG trigger source enable bit7 */
#define FMU_FGTSEN_FGTSEN8                       BIT(8)                                                    /*!< FG trigger source enable bit8 */
#define FMU_FGTSEN_FGTSEN9                       BIT(9)                                                    /*!< FG trigger source enable bit9 */
#define FMU_FGTSEN_FGTSEN10                      BIT(10)                                                   /*!< FG trigger source enable bit10 */
#define FMU_FGTSEN_FGTSEN11                      BIT(11)                                                   /*!< FG trigger source enable bit11 */
#define FMU_FGTSEN_FGTSEN12                      BIT(12)                                                   /*!< FG trigger source enable bit12 */
#define FMU_FGTSEN_FGTSEN13                      BIT(13)                                                   /*!< FG trigger source enable bit13 */
#define FMU_FGTSEN_FGTSEN14                      BIT(14)                                                   /*!< FG trigger source enable bit14 */
#define FMU_FGTSEN_FGTSEN15                      BIT(15)                                                   /*!< FG trigger source enable bit16 */
#define FMU_FGTSEN_FGTSEN16                      BIT(16)                                                   /*!< FG trigger source enable bit16 */
#define FMU_FGTSEN_FGTSEN17                      BIT(17)                                                   /*!< FG trigger source enable bit17 */
#define FMU_FGTSEN_FGTSEN18                      BIT(18)                                                   /*!< FG trigger source enable bit18 */
#define FMU_FGTSEN_FGTSEN19                      BIT(19)                                                   /*!< FG trigger source enable bit19 */
#define FMU_FGTSEN_FGTSEN20                      BIT(20)                                                   /*!< FG trigger source enable bit20 */
#define FMU_FGTSEN_FGTSEN21                      BIT(21)                                                   /*!< FG trigger source enable bit21 */
#define FMU_FGTSEN_FGTSEN22                      BIT(22)                                                   /*!< FG trigger source enable bit22 */
#define FMU_FGTSEN_FGTSEN23                      BIT(23)                                                   /*!< FG trigger source enable bit23 */
#define FMU_FGTSEN_FGTSEN24                      BIT(24)                                                   /*!< FG trigger source enable bit24 */
#define FMU_FGTSEN_FGTSEN25                      BIT(25)                                                   /*!< FG trigger source enable bit25 */
#define FMU_FGTSEN_FGTSEN26                      BIT(26)                                                   /*!< FG trigger source enable bit26 */
#define FMU_FGTSEN_FGTSEN27                      BIT(27)                                                   /*!< FG trigger source enable bit27 */
#define FMU_FGTSEN_FGTSEN28                      BIT(28)                                                   /*!< FG trigger source enable bit28 */
#define FMU_FGTSEN_FGTSEN29                      BIT(29)                                                   /*!< FG trigger source enable bit29 */
#define FMU_FGTSEN_FGTSEN30                      BIT(30)                                                   /*!< FG trigger source enable bit30 */
#define FMU_FGTSEN_FGTSEN31                      BIT(31)                                                   /*!< FG trigger source enable bit31 */

/* FMU_FGTSSTAT(x) (x=0...4) */
#define FMU_FGTSSTAT_FGTSSTAT0                   BIT(0)                                                    /*!< FG trigger source status bit0 */
#define FMU_FGTSSTAT_FGTSSTAT1                   BIT(1)                                                    /*!< FG trigger source status bit 1 */
#define FMU_FGTSSTAT_FGTSSTAT2                   BIT(2)                                                    /*!< FG trigger source status bit 2 */
#define FMU_FGTSSTAT_FGTSSTAT3                   BIT(3)                                                    /*!< FG trigger source status bit 3 */
#define FMU_FGTSSTAT_FGTSSTAT4                   BIT(4)                                                    /*!< FG trigger source status bit 4 */
#define FMU_FGTSSTAT_FGTSSTAT5                   BIT(5)                                                    /*!< FG trigger source status bit 5 */
#define FMU_FGTSSTAT_FGTSSTAT6                   BIT(6)                                                    /*!< FG trigger source status bit 6 */
#define FMU_FGTSSTAT_FGTSSTAT7                   BIT(7)                                                    /*!< FG trigger source status bit 7 */
#define FMU_FGTSSTAT_FGTSSTAT8                   BIT(8)                                                    /*!< FG trigger source status bit 8 */
#define FMU_FGTSSTAT_FGTSSTAT9                   BIT(9)                                                    /*!< FG trigger source status bit 9 */
#define FMU_FGTSSTAT_FGTSSTAT10                  BIT(10)                                                   /*!< FG trigger source status bit 10 */
#define FMU_FGTSSTAT_FGTSSTAT11                  BIT(11)                                                   /*!< FG trigger source status bit 11 */
#define FMU_FGTSSTAT_FGTSSTAT12                  BIT(12)                                                   /*!< FG trigger source status bit 12 */
#define FMU_FGTSSTAT_FGTSSTAT13                  BIT(13)                                                   /*!< FG trigger source status bit 13 */
#define FMU_FGTSSTAT_FGTSSTAT14                  BIT(14)                                                   /*!< FG trigger source status bit 14 */
#define FMU_FGTSSTAT_FGTSSTAT15                  BIT(15)                                                   /*!< FG trigger source status bit 16 */
#define FMU_FGTSSTAT_FGTSSTAT16                  BIT(16)                                                   /*!< FG trigger source status bit 16 */
#define FMU_FGTSSTAT_FGTSSTAT17                  BIT(17)                                                   /*!< FG trigger source status bit 17 */
#define FMU_FGTSSTAT_FGTSSTAT18                  BIT(18)                                                   /*!< FG trigger source status bit 18 */
#define FMU_FGTSSTAT_FGTSSTAT19                  BIT(19)                                                   /*!< FG trigger source status bit 19 */
#define FMU_FGTSSTAT_FGTSSTAT20                  BIT(20)                                                   /*!< FG trigger source status bit 20 */
#define FMU_FGTSSTAT_FGTSSTAT21                  BIT(21)                                                   /*!< FG trigger source status bit 21 */
#define FMU_FGTSSTAT_FGTSSTAT22                  BIT(22)                                                   /*!< FG trigger source status bit 22 */
#define FMU_FGTSSTAT_FGTSSTAT23                  BIT(23)                                                   /*!< FG trigger source status bit 23 */
#define FMU_FGTSSTAT_FGTSSTAT24                  BIT(24)                                                   /*!< FG trigger source status bit 24 */
#define FMU_FGTSSTAT_FGTSSTAT25                  BIT(25)                                                   /*!< FG trigger source status bit 25 */
#define FMU_FGTSSTAT_FGTSSTAT26                  BIT(26)                                                   /*!< FG trigger source status bit 26 */
#define FMU_FGTSSTAT_FGTSSTAT27                  BIT(27)                                                   /*!< FG trigger source status bit 27 */
#define FMU_FGTSSTAT_FGTSSTAT28                  BIT(28)                                                   /*!< FG trigger source status bit 28 */
#define FMU_FGTSSTAT_FGTSSTAT29                  BIT(29)                                                   /*!< FG trigger source status bit 29 */
#define FMU_FGTSSTAT_FGTSSTAT30                  BIT(30)                                                   /*!< FG trigger source status bit 30 */
#define FMU_FGTSSTAT_FGTSSTAT31                  BIT(31)                                                   /*!< FG trigger source status bit 31 */

/* FMU_FGSWTEN(x) (x=0...2) */
#define FMU_FGSWTEN_FGSWTEN0                     BITS(0,1)                                                 /*!< Software triggered fault enable bits0 */
#define FMU_FGSWTEN_FGSWTEN1                     BITS(2,3)                                                 /*!< Software triggered fault enable bits1 */
#define FMU_FGSWTEN_FGSWTEN2                     BITS(4,5)                                                 /*!< Software triggered fault enable bits2 */
#define FMU_FGSWTEN_FGSWTEN3                     BITS(6,7)                                                 /*!< Software triggered fault enable bits3 */
#define FMU_FGSWTEN_FGSWTEN4                     BITS(8,9)                                                 /*!< Software triggered fault enable bits4 */
#define FMU_FGSWTEN_FGSWTEN5                     BITS(10,11)                                               /*!< Software triggered fault enable bits5 */
#define FMU_FGSWTEN_FGSWTEN6                     BITS(12,13)                                               /*!< Software triggered fault enable bits6 */
#define FMU_FGSWTEN_FGSWTEN7                     BITS(14,15)                                               /*!< Software triggered fault enable bits7 */

/* FMU_TMRES */
#define FMU_TMRES_TMREN0                         BIT(0)                                                    /*!< TMR error output enable 0 */
#define FMU_TMRES_TMRS0                          BIT(1)                                                    /*!< DBGEN register TMR error status */
#define FMU_TMRES_TMREN1                         BIT(2)                                                    /*!< TMR error output enable bit 1 */
#define FMU_TMRES_TMRS1                          BIT(3)                                                    /*!< FOSEN, FOSCFG[1:0], GOSEN and GOSCFG[1:0] bits TMR error status */
#define FMU_TMRES_TMREN2                         BIT(4)                                                    /*!< TMR error output enable bit 2 */
#define FMU_TMRES_TMRS2                          BIT(5)                                                    /*!< FMU_FGCFG and FMU_FGEN registers TMR error status */

/* constants definitions */
/* FMU fault pin parameter struct definitions */
typedef struct
{
    uint32_t gosen;                                                                                        /*!< enable or disable GFIO signal */
    uint32_t fosen;                                                                                        /*!< enable or disable FFIO signals */
    uint32_t foscfg;                                                                                       /*!< configure FFIO signals */
    uint32_t goscfg;                                                                                       /*!< configure GFIO signal */
    uint32_t fopre;                                                                                        /*!< configure fatal fault output pin signals time switching clock prescaler */
    uint32_t fomcfg;                                                                                       /*!< configure FFIO signals work mode is consistent with FG fault or not when FMU is in INIT work mode */
    uint32_t gopcfg;                                                                                       /*!< configure GFIO signal polarity */
    uint32_t fopcfg;                                                                                       /*!< configure FFIO signal polarity */
    uint32_t fomset;                                                                                       /*!< set FFIO signals work mode */
    uint32_t gomset;                                                                                       /*!< set GFIO signal work mode */
}fmu_fio_parameter_struct;

/* FMU parameter struct definitions */
typedef struct
{
    uint16_t recovery_type;                                                                                /*!< fault recovery type (hardware recovery or software recovery) */
    ControlStatus sub_rst;                                                                                 /*!< configure fault group subsystem reset */
    ControlStatus fault_group_en;                                                                          /*!< configure fault group (enable or disable) */
    ControlStatus caution_timeout_en;                                                                      /*!< configure fault group CAUTION  work mode timeout (enable or disable) */
    uint32_t caution_timeout_value;                                                                        /*!< fault group CAUTION  work mode timeout value */
    uint32_t init_timeout_value;                                                                           /*!< INIT work mode timeout value */
    uint16_t faultout_timer_value;                                                                         /*!< fault output (FFIO) timer value */
    ControlStatus caution_int_en;                                                                          /*!< configure CAUTION work mode interrupt request (enable or disable) */
    ControlStatus nmi_en;                                                                                  /*!< configure NMI request (enable or disable) */
    ControlStatus ffio_output_en;                                                                          /*!< configure FFIO signals (enable or disable) */
    ControlStatus gfio_output_en;                                                                          /*!< configure GFIO signal (enable or disable) */
    ControlStatus gpo_en;                                                                                  /*!< configure FAULT work mode holding timer output (GPO) (enable or disable) */
}fmu_parameter_struct;

/* FMU execute operation definition */
typedef enum
{
    FMU_TRAN_INIT_WORK_MODE     = 0U,                                                                       /*!< FMU execute operation that transform to INIT work mode */
    FMU_TRAN_NORMAL_WORK_MODE   = 1U,                                                                       /*!< FMU execute operation that transform to NORMAL work mode */
    FMU_CLR_HOLDING_STATUS_REGS = 2U,                                                                       /*!< FMU execute operation that clear the hold status register */
    FMU_CLR_OPERATION           = 3U,                                                                       /*!< FMU execute operation that clear operation status */
    FMU_NO_EXE_OPERATION        = 4U,                                                                       /*!< FMU no execute operation */
}fmu_operation_enum;

typedef enum
{
    FMU_OPS_IDLE                = 0U,                                                                       /*!< FMU operation status is idle */
    FMU_OPS_ONGOING             = 1U,                                                                       /*!< FMU operation status is on going */
    FMU_OPS_NOTSUCCESS          = 2U,                                                                       /*!< FMU operation is not success */
    FMU_OPS_SUCCESS             = 3U                                                                        /*!< FMU operation is success */
}fmu_operation_status_enum;

/* fmu_lock_type_enum */
typedef enum
{
    FMU_LOCK_EOP1               = BIT(0),                                                                   /*!< EOP1 lock */
    FMU_LOCK_EOP2               = BIT(1),                                                                   /*!< EOP2 lock */
    FMU_LOCK_TRANS_TEMP         = BIT(2),                                                                   /*!< INIT work mode transition temporary lock  */
    FMU_LOCK_TRANS_PERM         = BIT(3),                                                                   /*!< INIT work mode transition permanent lock */
    FMU_LOCK_FG_STAT            = BIT(4)                                                                    /*!< FG status lock */
}fmu_lock_type_enum;

/* FMU fault reaction type enum */
typedef enum
{
    FMU_FRETN_CAUINT2CPU        = 0U,                                                                       /*!< FMU fault reaction type is CAUTION to CPU */
    FMU_FRETN_NMI2CPU           = 1U,                                                                       /*!< FMU fault reaction type is NMI to CPU */
    FMU_FRETN_SUBRST2RCU        = 2U,                                                                       /*!< FMU fault reaction type is subsystem reset to RCU */
    FMU_FRETN_RST2RCU           = 3U,                                                                       /*!< FMU fault reaction type is reset to RCU */
    FMU_FRETN_GPO               = 4U,                                                                       /*!< FMU fault reaction type is FAULT work status holding timer output */
    FMU_FRETN_GFIO              = 5U,                                                                       /*!< FMU fault reaction type is FG GFIO pin output */
    FMU_FRETN_FFIO              = 6U                                                                        /*!< FMU fault reaction type is FG FFIO pin output */
}fmu_fretn_type_enum;

/* FMU timer type enum */
typedef enum
{
    FMU_CAUTION_TIMEROUT        = 0U,                                                                        /*!< FG CAUTION work mode timerout value */
    FMU_INIT_TIMEROUT           = 1U,                                                                        /*!< FG INIT work mode timerout value */
    FMU_FAULT_OUTPUT_TIMER      = 2U                                                                         /*!< FG FAULT work mode timer */
}fmu_tim_type_enum;

/* FMU FFIO state type definition */
typedef enum
{
    FFIO_STATUS_LOW0_LOW1       = 0U,                                                                       /*!< FFIO0 and FFIO1 status are low */
    FFIO_STATUS_HIGH0_LOW1      = 1U,                                                                       /*!< FFIO0 status is high and FFIO1 status is low */
    FFIO_STATUS_LOW0_HIGH1      = 2U,                                                                       /*!< FFIO0 status is low and FFIO1 output is high */
    FFIO_STATUS_HIGH0_HIGH1     = 3U                                                                        /*!< FFIO0 and FFIO1 statuss are high */
}fmu_ffio_status_enum;

typedef enum
{
    FMU_NO_FAULTY               = 0U,                                                                       /*!< FMU not in faulty condition */
    FMU_IN_FAULTY               = 1U                                                                        /*!< FMU in faulty condition */
}fmu_faulty_status_enum;

/* FMU FFIO state type definition */
typedef enum
{
    FMU_STATUS_NORMAL           = 0U,                                                                       /*!< FMU the current is NORMAL status */
    FMU_STATUS_INIT             = 1U,                                                                       /*!< FMU the current is INIT status */
    FMU_STATUS_CAUTION          = 2U,                                                                       /*!< FMU the current is CAUTION status */
    FMU_STATUS_FAULT            = 3U                                                                        /*!< FMU the current is FAULT status */
}fmu_status_enum;

/* fmu_lock_type_enum */
typedef enum
{
    FMU_TRANS_N2C              = BIT(0),                                                                    /*!< FMU work mode transition type is NORMAL to CAUTION */
    FMU_TRANS_C2F              = BIT(1),                                                                    /*!< FMU work mode transition type is CAUTION to FAULT */
    FMU_TRANS_N2F              = BIT(2),                                                                    /*!< FMU work mode transition type is NORMAL to FAULT */
    FMU_TRANS_F2C              = BIT(3)                                                                     /*!< FMU work mode transition type is FAULT to CAUTION */
}fmu_trans_type_enum;

/* FMU interrupt type enum */
typedef enum
{
    FMU_INT_INIT                = 0U,                                                                       /*!< INIT timeout interrupt is pending */
    FMU_INT_CAUTION             = 1U,                                                                       /*!< CAUTION timeout interrupt is pending */
    FMU_INT_NMI                 = 2U                                                                        /*!< NMI interrupt */
}fmu_int_type_enum;

typedef enum
{
    FMU_CAUTION_WORK_MODE_CNT  = 0U,                                                                        /*!< FG CAUTION work mode counter */
    FMU_INIT_WORK_MODE_CNT     = 1U,                                                                        /*!< FG INIT work mode counter */
    FMU_FF_OUTPUT_CNT          = 2U,                                                                        /*!< fatal fault output counter */
    FMU_GF_OUTPUT_CNT          = 3U                                                                         /*!< general fault output counter */
}fmu_cnt_type_enum;

/* fmu_lock_type_enum */
typedef enum
{
    FMU_TME0_DBGEN           = BIT(0),                                                                      /*!< enable TMR error output 0 */
    FMU_TME1_FOS_GOS_ENCFG   = BIT(1),                                                                      /*!< enable TMR error output 1 */
    FMU_TME2_FG_ENCFG        = BIT(2)                                                                       /*!< enable TMR error output 2 */
}fmu_tmr_error_type_enum;

/* constants definitions */
typedef FlagStatus fio_status;

#define FMU_FG_EN(ID)                           BIT(ID)                                                     /*!< FMU fault groupt channel enable */

/* FMU operation status definitions */
#define FMU_OPSTAT(regval)                      (BITS(6,7) & ((uint32_t)(regval) << 6))
#define FMU_OPSTAT_IDLE                         FMU_OPSTAT(0)                                               /*!< operation status is idle */
#define FMU_OPSTAT_ONGOING                      FMU_OPSTAT(1)                                               /*!< operation status is ongoing */
#define FMU_OPSTAT_NOTSUCCESS                   FMU_OPSTAT(2)                                               /*!< operation status is not success */
#define FMU_OPSTAT_SUCCESS                      FMU_OPSTAT(3)                                               /*!< operation status is success */

/* FMU execute operation difinitions */
#define FMU_NO_OPERATION                        ((uint32_t)0x00000000U)                                     /*!< no execute operation (EOP0) */
#define FMU_TO_INIT_WORK_MODE                   ((uint32_t)0x00000001U)                                     /*!< execute operation which will transform FMU to INIT work mode (EOP1) */
#define FMU_TO_NORMAL_WORK_MODE                 ((uint32_t)0x00000002U)                                     /*!< execute operation which will transform FMU to NORMAL work mode (EOP2) */
#define FMU_FG_STAT_CLR                         ((uint32_t)0x0000000CU)                                     /*!< execute clean a FG fault flag in FMU_FGSTAT register operation is on going (EOP12) */
#define FMU_CLR_HOLD_STATUS_REGS                ((uint32_t)0x0000000DU)                                     /*!< execute operation which will clean the hold status register (EOP13) */
#define FMU_INIT_TIMEOUT_ON_GOING               ((uint32_t)0x0000000EU)                                     /*!< INIT work mode timeout is on going (EOP14) */
#define FMU_CLR_OPERATION_STATUS                ((uint32_t)0x0000000FU)                                     /*!< execute operation which will set OPSTAT[1:0] to idle (EOP15) */

/* FMU key value */
#define FMU_EOP1_KEY_U32                        ((uint32_t)0x85A670B9UL)                                    /*!< FMU key to enter INIT state */
#define FMU_EOP2_KEY_U32                        ((uint32_t)0x4C30765DUL)                                    /*!< FMU key to enter NORMAL state */
#define FMU_TEMP_LOCK_KEY_U32                   ((uint32_t)0xFFFFFF34UL)                                    /*!< FMU key to transiently lock the config registers */
#define FMU_TEMP_UNLOCK_KEY_U32                 ((uint32_t)0x000000DAUL)                                    /*!< FMU key to unlock the transiently locked config registers */
#define FMU_PERM_LOCK_KEY_U32                   ((uint32_t)0x000000FFUL)                                    /*!< FMU key to permanently lock the config registers */
#define FMU_FG_KEY_UNLOCK_U32                   ((uint32_t)0xDA3778FBUL)                                    /*!< FMU key to unlock FMU_FGSTAT registers for write access */

/* FMU status field description */
#define FMU_NORMAL_STATUS                       ((uint32_t)0x00000000U)                                     /*!< FMU the current is NORMAL state */
#define FMU_INIT_STATUS                         ((uint32_t)0x00000001U)                                     /*!< FMU the current is INIT state */
#define FMU_CAUTION_STATUS                      ((uint32_t)0x00000002U)                                     /*!< FMU the current is CAUTION state */
#define FMU_FAULT_STATUS                        ((uint32_t)0x00000003U)                                     /*!< FMU the current is FAULT state */

/* GFIO siganls work mode configuration */
#define FMU_GOMSET_MODE(regval)                 (BITS(3,5) & ((uint32_t)(regval) << 3))
#define FMU_GOMSET_FAULT_OUTPUT_MODE            FMU_GOMSET_MODE(2)                                          /*!< GFIO the protocol of the signaling is Bi-stable */
#define FMU_GOMSET_MODE_TEST0                   FMU_GOMSET_MODE(5)                                          /*!< GFIO the protocol of the signaling is test 0 */
#define FMU_GOMSET_MODE_TEST1                   FMU_GOMSET_MODE(7)                                          /*!< GFIO the protocol of the signaling is test 1 */

/* FFIO siganls work mode configuration */
#define FMU_FOMSET_MODE(regval)                 (BITS(6,8) & ((uint32_t)(regval) << 6))
#define FMU_FOMSET_MODE_BI_STABLE               FMU_FOMSET_MODE(2)                                          /*!< FFIO the protocol of the signaling is Bi-stable */
#define FMU_FOMSET_MODE_TIME_SWITCHING          FMU_FOMSET_MODE(3)                                          /*!< FFIO the protocol of the signaling is time-switching */
#define FMU_FOMSET_MODE_TEST0                   FMU_FOMSET_MODE(5)                                          /*!< FFIO the protocol of the signaling is test 0 */
#define FMU_FOMSET_MODE_TEST1                   FMU_FOMSET_MODE(6)                                          /*!< FFIO the protocol of the signaling is test 1 */
#define FMU_FOMSET_MODE_TEST2                   FMU_FOMSET_MODE(7)                                          /*!< FFIO the protocol of the signaling is test 2 */

/* FFIO siganls polarity configuration */
#define FMU_FOPCFG_HIGH0_LOW1                   FMU_CFG_FOPCFG                                              /*!< FFIO 1 is high and FFin 0 is low for the faulty infication */
#define FMU_FOPCFG_HIGH1_LOW0                   (uint32_t)(0x00000000U)                                     /*!< FFIO 1 is low and FFin 0 is high for the faulty infication */

/* GFIO siganls polarity configuration */
#define FMU_GOPS_HIGH                           FMU_CFG_GOPCFG                                              /*!< GFIO fault state output is high  */
#define FMU_GOPS_LOW                            (uint32_t)(0x00000000U)                                     /*!< GFIO fault state output is low  */

/* FFIO siganls work mode is consistent with FG fault or not */
#define FMU_FOMCFG_CONSISTENT                   FMU_CFG_FOMCFG                                              /*!< configuration indication is the same as the non-faulty indication */
#define FMU_FOMCFG_NOTCONSISTENT                (uint32_t)(0x00000000U)                                     /*!< configuration indication is the different as the non-faulty indication */

/* FFIO time switching prescaler factor */
#define FMU_FOPRE_DIV(regval)                   (BITS(16,19) & ((uint32_t)(regval) << 16))
#define FMU_FOPRE_DIV_2                         FMU_FOPRE_DIV(0)                                            /*!< FFIO and GFIO time switching prescaler is divided by 2*/
#define FMU_FOPRE_DIV_4                         FMU_FOPRE_DIV(1)                                            /*!< FFIO and GFIO time switching prescaler is divided by 4 */
#define FMU_FOPRE_DIV_8                         FMU_FOPRE_DIV(2)                                            /*!< FFIO and GFIO time switching prescaler is divided by 8 */
#define FMU_FOPRE_DIV_16                        FMU_FOPRE_DIV(3)                                            /*!< FFIO and GFIO time switching prescaler is divided by 16 */
#define FMU_FOPRE_DIV_32                        FMU_FOPRE_DIV(4)                                            /*!< FFIO and GFIO time switching prescaler is divided by 32 */
#define FMU_FOPRE_DIV_64                        FMU_FOPRE_DIV(5)                                            /*!< FFIO and GFIO time switching prescaler is divided by 64 */
#define FMU_FOPRE_DIV_128                       FMU_FOPRE_DIV(6)                                            /*!< FFIO and GFIO time switching prescaler is divided by 128 */
#define FMU_FOPRE_DIV_256                       FMU_FOPRE_DIV(7)                                            /*!< FFIO and GFIO time switching prescaler is divided by 256 */
#define FMU_FOPRE_DIV_512                       FMU_FOPRE_DIV(8)                                            /*!< FFIO and GFIO time switching prescaler is divided by 512 */
#define FMU_FOPRE_DIV_1024                      FMU_FOPRE_DIV(9)                                            /*!< FFIO and GFIO time switching prescaler is divided by 1024 */
#define FMU_FOPRE_DIV_2048                      FMU_FOPRE_DIV(10)                                           /*!< FFIO and GFIO time switching prescaler is divided by 2048 */
#define FMU_FOPRE_DIV_4096                      FMU_FOPRE_DIV(11)                                           /*!< FFIO and GFIO time switching prescaler is divided by 4096 */

/* GFIO control configuration */
#define FMU_GFIO_CONTRONL(regval)                (BITS(20,21) & ((uint32_t)(regval) << 20))
#define FMU_GFIO_CONTRONL_FSM                    FMU_GFIO_CONTRONL(0)                                       /*!< GFIO controlled by the FSM */
#define FMU_GFIO_CONTRONL_LOW                    FMU_GFIO_CONTRONL(1)                                       /*!< GFIO is always low */
#define FMU_GFIO_CONTRONL_HIGH                   FMU_GFP_CONTRONL(3)                                        /*!< GFIO is high until a fault occurs on a channel theresfter controlled by the FSM */

/* FFIO control configuration */
#define FMU_FFIO_CONTRONL(regval)                (BITS(22,23) & ((uint32_t)(regval) << 22))
#define FMU_FFIO_CONTRONL_FSM                    FMU_FFIO_CONTRONL(0)                                       /*!< FFIO controlled by the FSM */
#define FMU_FFIO_CONTRONL_LOW                    FMU_FFIO_CONTRONL(1)                                       /*!< FFIO is always low */
#define FMU_FFIO_CONTRONL_HIGH                   FMU_FFIO_CONTRONL(3)                                       /*!< FFIO is high until a fault occurs on a channel theresfter controlled by the FSM */

/* FFIO output control definitions */
#define FMU_FOS_ENABLE                          FMU_CFG_FOSEN                                               /*!< FFIO enable singal output */
#define FMU_FOS_DISABLE                        (uint32_t)(0x00000000U)                                      /*!< FFIO disable singal output */

/* GFIO output control definitions */
#define FMU_GOS_ENABLE                          FMU_CFG_GOSEN                                               /*!< GFIO enable singal output */
#define FMU_GOS_DISABLE                        (uint32_t)(0x00000000U)                                      /*!< GFIO disable singal output */

/* Fault pin definitions */
#define FMU_FFPO_0                              FMU_FPCTL_FPO0                                              /*!< FFIO 0 output */
#define FMU_FFPO_1                              FMU_FPCTL_FPO1                                              /*!< FFIO 1 output */
#define FMU_GFPO                                FMU_FPCTL_GPO                                               /*!< GFIO output */
#define FMU_FFPI_0                              FMU_FPCTL_FPI0                                              /*!< FFIO 0 input */
#define FMU_FFPI_1                              FMU_FPCTL_FPI1                                              /*!< FFIO 1 input */
#define FMU_GFPI                                FMU_FPCTL_GPI                                               /*!< GFIO input */

/* FFIO state definitions */
#define FMU_FFIO_INPUT_STAT(regval)             (BITS(4,5) & ((uint32_t)(regval) << 4))
#define FMU_FFIO_LOW0_LOW1                      FMU_FFIO_INPUT_STAT(0)                                      /*!< FFIO input state is low0, low1 */
#define FMU_FFIO_HIGH0_LOW1                     FMU_FFIO_INPUT_STAT(1)                                      /*!< FFIO input state is low0, high1 */
#define FMU_FFIO_LOW0_HIGH1                     FMU_FFIO_INPUT_STAT(2)                                      /*!< FFIO input state is high0, low1 */
#define FMU_FFIO_HIGH0_HIGH1                    FMU_FFIO_INPUT_STAT(3)                                      /*!< FFIO input state is high0, high1 */

/* fault recovery type is hardware recovery or software recovery */
#define FMU_HW_RECOVERY                         ((uint16_t)0x0000U)                                         /*!< fault recovery type is hardware recovery */
#define FMU_SW_RECOVERY                         ((uint16_t)0x0001U)                                         /*!< fault recovery type is software recovery */

/* enable or disable fault group subsystem reset */
#define FMU_SUB_RST_DISABLE                    ((uint32_t)0x0003U)                                          /*!< disable fault group subsystem reset */
#define FMU_SUB_RST_ENABLE                     ((uint32_t)0x0001U)                                          /*!< enable fault group subsystem reset */

/* enable or disable FG */
#define FMU_FG_DISABLE                          ((uint32_t)0x0000U)                                         /*!< disable FG */
#define FMU_FG_ENABLE                           ((uint32_t)0x0001U)                                         /*!< enable FG */

/* CAUTION work mode timeout is enable or disable */
#define FMU_CMT_DISABLE                         ((uint32_t)0x0000U)                                         /*!< fault group CAUTION work mode timeout is disable */
#define FMU_CMT_ENABLE                          ((uint32_t)0x0001U)                                         /*!< fault group CAUTION work mode timeout is enable */

/* CAUTION work mode interrupt request is enable or disable */
#define FMU_CMI_DISABLE                         ((uint32_t)0x0000U)                                         /*!< fault group CAUTION work mode interrupt request is disable */
#define FMU_CMI_ENABLE                          ((uint32_t)0x0001U)                                         /*!< fault group CAUTION work mode interrupt request is enable */

/* FAULT work mode non-maskable interrupt request is enable or disable */
#define FMU_NMI_DISABLE                         ((uint32_t)0x0000U)                                         /*!< fault group FAULT work mode non-maskable interrupt request is disable */
#define FMU_NMI_ENABLE                          ((uint32_t)0x0001U)                                         /*!< fault group FAULT work mode non-maskable interrupt request is enable */

/* FAULT work mode FFIO or GFIO output indication is enable or disable */
#define FMU_PINOUT_DISABLE                      ((uint32_t)0x0000U)                                         /*!< fault group FAULT work mode FFIO or GFIO output indication is disable */
#define FMU_PINOUT_ENABLE                       ((uint32_t)0x0001U)                                         /*!< fault group FAULT work mode FFIO or GFIO output indicationt is enable */

/* FAULT work mode holding timer output is enable or disable */
#define FMU_HOLD_TIMER_DISABLE                  ((uint32_t)0x0000U)                                         /*!< fault group FAULT work mode holding timer output is disable */
#define FMU_HOLD_TIMER_ENABLE                   ((uint32_t)0x0001U)                                         /*!< fault group FAULT work mode holding timer output is enable */

/* FAULT work mode holding timer output is enable or disable */
#define FMU_FAKE_FG_DISABLE                     ((uint32_t)0x0100U)                                         /*!< fake fault group injection is disable */
#define FMU_FAKE_FG_ENABLE                      ((uint32_t)0x0200U)                                         /*!< fake fault group injectiont is enable */

/* FMU irq status flag */
#define FMU_INIT_INT_PEND                       ((uint32_t)0x00000001U)                                     /*!< INIT state timeout interrupt is occuring */
#define FMU_CAUTION_INT_PEND                    ((uint32_t)0x00000002U)                                     /*!< CAUTION state timeout interrupt is occuring */
#define FMU_NMI_PEND                            ((uint32_t)0x00000004U)                                     /*!< NMI is occuring */

/* FMU CAUTION and INIT state default timeout value and minmum fault-out timer interval */
#define FMU_INIT_TIMEOUT_INIT_VALUE             ((uint32_t)(0x00000005U))                                   /*!< FMU INIT state default timeout value */
#define FMU_CAUTION_TIMEOUT_INIT_VALUE          ((uint32_t)(0x0003A980U))                                   /*!< FMU CAUTION state default timeout value */
#define FMU_FAULTOUT_TIME_INIT_VALUE            ((uint16_t)(0x0000U))                                       /*!< FMU FAULT state pin default timer interval */

/* FG states are no faults */
#define FMU_NO_FAULT                            ((uint16_t)0x0000U)                                         /*!< no faulty */

/* FUM fault source */
#define FMU_FAULT_REASON(regval)                (BITS(8,9) & ((uint32_t)(regval) << 8))
#define FMU_NO_TO_FAULT                         FMU_FAULT_REASON(0)                                         /*!< no fault */
#define FMU_FAULT_GROUP                         FMU_FAULT_REASON(2)                                         /*!< FG fault */
#define FMU_MULTIPLE_FAULT                      FMU_FAULT_REASON(3)                                         /*!< multiple faults */

/* fault group ID definitions */
#define FAULT_GROUP_ID_0                        (uint16_t)(0x0000)                                          /*!< fault group 0 */
#define FAULT_GROUP_ID_1                        (uint16_t)(0x0001)                                          /*!< fault group 1 */
#define FAULT_GROUP_ID_2                        (uint16_t)(0x0002)                                          /*!< fault group 2 */
#define FAULT_GROUP_ID_3                        (uint16_t)(0x0003)                                          /*!< fault group 3 */
#define FAULT_GROUP_ID_4                        (uint16_t)(0x0004)                                          /*!< fault group 4 */
#define FAULT_GROUP_ID_5                        (uint16_t)(0x0005)                                          /*!< fault group 5 */
#define FAULT_GROUP_ID_6                        (uint16_t)(0x0006)                                          /*!< fault group 6 */
#define FAULT_GROUP_ID_7                        (uint16_t)(0x0007)                                          /*!< fault group 7 */
#define FAULT_GROUP_ID_8                        (uint16_t)(0x0008)                                          /*!< fault group 8 */
#define FAULT_GROUP_ID_9                        (uint16_t)(0x0009)                                          /*!< fault group 9 */
#define FAULT_GROUP_ID_10                       (uint16_t)(0x000A)                                          /*!< fault group 10 */
#define FAULT_GROUP_ID_11                       (uint16_t)(0x000B)                                          /*!< fault group 11 */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check FMU FG */
#define NOT_FMU_FG(id)                          (((id) != FAULT_GROUP_ID_0)  && \
                                                 ((id) != FAULT_GROUP_ID_1)  && \
                                                 ((id) != FAULT_GROUP_ID_2)  && \
                                                 ((id) != FAULT_GROUP_ID_3)  && \
                                                 ((id) != FAULT_GROUP_ID_4)  && \
                                                 ((id) != FAULT_GROUP_ID_5)  && \
                                                 ((id) != FAULT_GROUP_ID_6)  && \
                                                 ((id) != FAULT_GROUP_ID_7)  && \
                                                 ((id) != FAULT_GROUP_ID_8)  && \
                                                 ((id) != FAULT_GROUP_ID_9)  && \
                                                 ((id) != FAULT_GROUP_ID_10) && \
                                                 ((id) != FAULT_GROUP_ID_11))

/* check FMU operation type */
#define NOT_FMU_OPTYPE(optype)                  (((optype) != FMU_TRAN_INIT_WORK_MODE)      && \
                                                 ((optype) != FMU_TRAN_NORMAL_WORK_MODE)    && \
                                                 ((optype) != FMU_CLR_HOLDING_STATUS_REGS)  && \
                                                 ((optype) != FMU_NO_EXE_OPERATION)  && \
                                                 ((optype) != FMU_CLR_OPERATION))

/* check FMU lock type */
#define NOT_FMU_LKTYPE(lktype)                  (((lktype) != FMU_LOCK_EOP1)      && \
                                                 ((lktype) != FMU_LOCK_EOP2)      && \
                                                 ((lktype) != FMU_LOCK_FG_STAT)   && \
                                                 ((lktype) != FMU_LOCK_TRANS_TEMP))

/* check FMU lock type lock */
#define NOT_FMU_LKTYPE_LK(lktype)                (((lktype) != FMU_LOCK_TRANS_TEMP)      && \
                                                 ((lktype) != FMU_LOCK_TRANS_PERM))

/* check FMU recovery type */
#define NOT_FMU_RECOVERY_TYPE(recovery_type)    (((recovery_type) != FMU_HW_RECOVERY)      && \
                                                 ((recovery_type) != FMU_SW_RECOVERY))

/* check FMU recovery type */
#define NOT_FMU_REACTION_TYPE(reaction_type)    (((reaction_type) != FMU_FRETN_CAUINT2CPU)  && \
                                                 ((reaction_type) != FMU_FRETN_SUBRST2RCU)  && \
                                                 ((reaction_type) != FMU_FRETN_NMI2CPU)     && \
                                                 ((reaction_type) != FMU_FRETN_FFIO)        && \
                                                 ((reaction_type) != FMU_FRETN_GFIO)        && \
                                                 ((reaction_type) != FMU_FRETN_GPO))

/* check control status */
#define NOT_FMU_CONTROL_STATUS(new_value)        (((new_value) != ENABLE) && \
                                                 ((new_value) != DISABLE))

/* check FMU timer type */
#define NOT_FMU_TIMTYPE(tim_type)               (((tim_type) != FMU_CAUTION_TIMEROUT) && \
                                                 ((tim_type) != FMU_INIT_TIMEROUT) && \
                                                 ((tim_type) != FMU_FAULT_OUTPUT_TIMER))

/* check the length of FMU timer value */
#define FMU_TIMER_IMT_HIGH_VALUE                ((uint32_t)0x00000007U)         /*!< maximum FMU INIT work mode timeout value */
#define FMU_TIMER_FOT_HIGH_VALUE                ((uint32_t)0x00003FFFU)         /*!< maximum FMU FOT timer value */
#define NOT_FMU_TIMER_IMT_LENGTH(tim_value)     ((FMU_TIMER_IMT_HIGH_VALUE < (tim_value)))
#define NOT_FMU_TIMER_FOT_LENGTH(tim_value)     ((FMU_TIMER_FOT_HIGH_VALUE < (tim_value)))

/* check FMU FIO */
#define NOT_FMU_FO(fio)                         (((fio) != FMU_FFPO_0) && \
                                                 ((fio) != FMU_FFPO_1) && \
                                                 ((fio) != FMU_GFPO))

#define NOT_FMU_FI(fio)                         (((fio) != FMU_FFPI_0) && \
                                                 ((fio) != FMU_FFPI_1) && \
                                                 ((fio) != FMU_GFPI))

/* check FIO status */
#define NOT_FIO_STATUS(new_value)               (((new_value) != RESET) && \
                                                 ((new_value) != SET))

/* check the range of FMU fake FG */
#define FMU_FAKE_FG_HIGH_VALUE                  ((uint8_t)0x9FU)                /*!< maximum FMU fake FG  */
#define NOT_FMU_FAKE_FG_VALUE(value)            ((FMU_FAKE_FG_HIGH_VALUE < (value)))

/* check FMU work mode transition type */
#define NOT_FMU_TRANS_TYPE(type)                (((type) != FMU_TRANS_N2C)  && \
                                                 ((type) != FMU_TRANS_C2F) && \
                                                 ((type) != FMU_TRANS_N2F) && \
                                                 ((type) != FMU_TRANS_F2C))

/* check FMU interrupt type */
#define NOT_FMU_INT_TYPE(type)                  (((type) != FMU_INT_INIT)     && \
                                                 ((type) != FMU_INT_CAUTION) && \
                                                 ((type) != FMU_INT_NMI))

#define NOT_FMU_INT_TYPE_CLEAR(type)            (((type) != FMU_INT_INIT))

/* check FMU counter type */
#define NOT_FMU_CNT_TYPE(type)                  (((type) != FMU_CAUTION_WORK_MODE_CNT)     && \
                                                 ((type) != FMU_INIT_WORK_MODE_CNT)       && \
                                                 ((type) != FMU_FF_OUTPUT_CNT)            && \
                                                 ((type) != FMU_GF_OUTPUT_CNT))

/* check the range of FMU software triggered fault */
#define FMU_SOFT_TRI_LOW_VALUE                  ((uint8_t)0x88U)                /*!< minimum FMU software triggered fault */
#define NOT_FMU_SOFT_TRI_VALUE(value)           ((FMU_SOFT_TRI_LOW_VALUE > (value)) || (FMU_FAKE_FG_HIGH_VALUE < (value)))

/* check FMU counter type */
#define NOT_FMU_TMR_ERR_TYPE(type)              (((type) != FMU_TME0_DBGEN)                && \
                                                 ((type) != FMU_TME1_FOS_GOS_ENCFG)       && \
                                                 ((type) != FMU_TME2_FG_ENCFG))

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* FMU fault IO configuration and read functions*/
/* initialize the struct parameters of FMU FIO */
void fmu_fio_para_init(fmu_fio_parameter_struct* fmu_fio_struct);
/* configure FMU FIO */
void fmu_fio_config(fmu_fio_parameter_struct* fmu_fio_struct);

/* initialize the parameters of FMU structure with the default values */
void fmu_para_init(fmu_parameter_struct* fmu_struct);
/* configure FMU parameter */
void fmu_config(fmu_parameter_struct* fmu_struct, uint16_t fault_group_id);
/* execute FMU operation */
void fmu_operation_execute(fmu_operation_enum operation_type);
/* FMU read current operation status */
fmu_operation_status_enum fmu_operation_status_read(void);

/* unlock FMU */
void fmu_unlock(fmu_lock_type_enum lock_type);
/* lock FMU */
void fmu_lock(fmu_lock_type_enum lock_type);
/* configure FMU recovery type */
void fmu_fg_recovery_type_config(uint16_t recovery_type, uint16_t fault_group_id);
/* configure FMU fault reaction */
void fmu_fault_reaction_config(fmu_fretn_type_enum reaction_type, uint16_t fault_group_id, ControlStatus new_value);


/* configure FMU timer */
void fmu_timer_config(fmu_tim_type_enum tim_type, uint32_t tim_value);
/* configure FMU FIO */
void fmu_fio_output_config(uint32_t fault_pin, fio_status output_value);
/* get FMU fault IO signal input status */
fio_status fmu_fio_input_get(uint32_t fault_pin);
/* read FMU FFIO signal control status */
fmu_ffio_status_enum fmu_ffio_status_read(void);
/* read FMU GFpin signal control status */
fio_status fmu_gfio_status_read(void);
/* get FMU status */
fmu_faulty_status_enum fmu_status_get(void);
/* read FMU current work mode */
fmu_status_enum fmu_workmode_read(void);
/* injection FMU fake FG fault */
void fmu_ff_injection(uint32_t fault_group_id);
/* read FMU transition FG */
uint32_t fmu_trans_fg_read(fmu_trans_type_enum trans_type);
/* read FMU counter */
uint32_t fmu_counter_read(fmu_cnt_type_enum cnt_type);

/* configure FMU TMR error output */
void fmu_tmr_error_output_config(fmu_tmr_error_type_enum tmr_error_type, ControlStatus new_value);

/* flag get and clear */
/* get FMU fault flag */
uint32_t fmu_fault_flag_get(void);
/* clear FMU FG status */
void fmu_fg_status_clear(uint16_t fault_group_id);
/* get FMU group fault status */
FlagStatus fmu_fg_status_get(uint16_t fault_group_id);
/* get FMU FG trigger source status */
FlagStatus fmu_fg_trigger_source_status_get(uint8_t trigger_source_num);
/* clear FMU FG trigger source status */
void fmu_fg_trigger_source_status_clear(uint8_t trigger_source_num);
/* get FMU TMR error output status */
FlagStatus fmu_tmr_error_status_get(fmu_tmr_error_type_enum tmr_error_type);
/* clear FMU TMR error output status */
void fmu_tmr_error_status_clear(fmu_tmr_error_type_enum tmr_error_type);

/* enable FMU debug mode */
void fmu_dbg_enable(void);
/* disable FMU debug mode */
void fmu_dbg_disable(void);
/* enabled FMU FG */
void fmu_fg_enable(uint16_t fault_group_id);
/* disabled FMU FG */
void fmu_fg_disable(uint16_t fault_group_id);
/* enable FMU CAUTION timeout */
void fmu_caution_timeout_enable(uint16_t fault_group_id);
/* disable FMU CAUTION timeout */
void fmu_caution_timeout_disable(uint16_t fault_group_id);
/* enable injection FMU fake FG */
void fmu_ff_inject_enable(void);
/* disable injection FMU fake FG */
void fmu_ff_inject_disable(void);
/* enable FMU FG trigger source */
void fmu_fg_trigger_source_enable(uint8_t trigger_source_num);
/* disable FMU FG trigger source */
void fmu_fg_trigger_source_disable(uint8_t trigger_source_num);
/* enable FMU software triggered fault */
void fmu_fg_soft_trig_fault_enable(uint8_t soft_trig_fault_num);
/* disable FMU software triggered fault */
void fmu_fg_soft_trig_fault_disable(uint8_t soft_trig_fault_num);
/* enable FMU INIT status timeout interrupt */
void fmu_init_timeout_irq_enable(void);
/* disable FMU INIT status timeout interrupt */
void fmu_init_timeout_irq_disable(void);

/* get FMU current interrupt status */
FlagStatus fmu_interrupt_flag_get(fmu_int_type_enum int_type);
/* clear FMU interrupt flag */
void fmu_interrupt_flag_clear(fmu_int_type_enum int_type);

#endif /* GD32A7XX_FMU_H */
