/*!
    \file    gd32a7xx_fmc.h
    \brief   definitions for the FMC

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

#ifndef GD32A7XX_FMC_H
#define GD32A7XX_FMC_H

#include "gd32a7xx.h"

/* FMC and option bytes definition */
#define FMC                          FMC_BASE                                           /*!< FMC register base address */
#define OB                           OB_BASE                                            /*!< HOST option bytes base address */
#define HSM_OB                       ((uint32_t)0x1FFFF880U)                            /*!< HSM option bytes base address */

/* registers definitions */
#define FMC_WS                       REG32((FMC) + 0x00000000U)                         /*!< FMC wait state register */
#define FMC_SPCKEY                   REG32((FMC) + 0x00000004U)                         /*!< FMC unlock SPC protection register */
#define FMC_KEY0                     REG32((FMC) + 0x00000014U)                         /*!< FMC unlock key register 0 */
#define FMC_STAT0                    REG32((FMC) + 0x00000018U)                         /*!< FMC status register 0 */
#define FMC_CTL0                     REG32((FMC) + 0x0000001CU)                         /*!< FMC control register 0 */
#define FMC_ADDR0                    REG32((FMC) + 0x00000020U)                         /*!< FMC address register 0 */
#define FMC_WDATL0                   REG32((FMC) + 0x00000024U)                         /*!< FMC write data register LOW 0 */
#define FMC_WDATH0                   REG32((FMC) + 0x00000028U)                         /*!< FMC write data register HIGH 0 */
#define FMC_OBSTAT                   REG32((FMC) + 0x00000030U)                         /*!< FMC option byte status register */
#define FMC_WP0                      REG32((FMC) + 0x00000034U)                         /*!< FMC erase/program protection register 0 */
#define FMC_WP1                      REG32((FMC) + 0x00000038U)                         /*!< FMC erase/program protection register 1 */
#define FMC_WP2                      REG32((FMC) + 0x0000003CU)                         /*!< FMC erase/program protection register 2 */
#define FMC_OBUSER1_0                REG32((FMC) + 0x00000040U)                         /*!< FMC option byte USER1 register 0 */
#define FMC_OBUSER1_1                REG32((FMC) + 0x00000044U)                         /*!< FMC option byte USER1 register 1 */
#define FMC_HSMOBSTAT                REG32((FMC) + 0x00000048U)                         /*!< FMC HSM option byte status register */
#define FMC_HSMWP                    REG32((FMC) + 0x0000004CU)                         /*!< FMC HSM erase/program protection register */
#define FMC_BLK0ECCCS                REG32((FMC) + 0x00000060U)                         /*!< FMC block 0 ECC control and status register */
#define FMC_BLK0UCECCADDR            REG32((FMC) + 0x00000064U)                         /*!< FMC block 0 UCECC address register */
#define FMC_BLK0CECCADDR0            REG32((FMC) + 0x00000068U)                         /*!< FMC block 0 CECC address0 register */
#define FMC_BLK0CECCADDR1            REG32((FMC) + 0x0000006CU)                         /*!< FMC block 0 CECC address1 register */
#define FMC_BLK0CECCADDR2            REG32((FMC) + 0x00000070U)                         /*!< FMC block 0 CECC address2 register */
#define FMC_BLK0CECCADDR3            REG32((FMC) + 0x00000074U)                         /*!< FMC block 0 CECC address3 register */
#define FMC_BUF0ECCCS                REG32((FMC) + 0x00000080U)                         /*!< FMC buffer 0 control register */
#define FMC_BUF0UCECCADDR            REG32((FMC) + 0x00000084U)                         /*!< FMC buffer 0 UCECC address register */
#define FMC_BUF0CECCADDR0            REG32((FMC) + 0x00000088U)                         /*!< FMC buffer 0 correct ECC address0 register */
#define FMC_BUF0CECCADDR1            REG32((FMC) + 0x0000008CU)                         /*!< FMC buffer 0 correct ECC address1 register */
#define FMC_BUF0CECCADDR2            REG32((FMC) + 0x00000090U)                         /*!< FMC buffer 0 correct ECC address2 register */
#define FMC_BUF0CECCADDR3            REG32((FMC) + 0x00000094U)                         /*!< FMC buffer 0 correct ECC address3 register */
#define FMC_FPB_ECCCS                REG32((FMC) + 0x000000A0U)                         /*!< FMC fast program buffer ECC control and status register */
#define FMC_FPB_UCECCADDR            REG32((FMC) + 0x000000A4U)                         /*!< FMC fast program buffer UCECC address register */
#define FMC_FPB_CECCADDR0            REG32((FMC) + 0x000000A8U)                         /*!< FMC fast program buffer correct ECC address0 register */
#define FMC_FPB_CECCADDR1            REG32((FMC) + 0x000000ACU)                         /*!< FMC fast program buffer correct ECC address1 register */
#define FMC_FPB_CECCADDR2            REG32((FMC) + 0x000000B0U)                         /*!< FMC fast program buffer correct ECC address2 register */
#define FMC_FPB_CECCADDR3            REG32((FMC) + 0x000000B4U)                         /*!< FMC fast program buffer correct ECC address3 register */
#define FMC_PID0                     REG32((FMC) + 0x000000D0U)                         /*!< FMC product ID register 0 */
#define FMC_PID1                     REG32((FMC) + 0x000000D4U)                         /*!< FMC product ID register 1 */
#define FMC_KEY1                     REG32((FMC) + 0x00000114U)                         /*!< FMC unlock key register 1 */
#define FMC_STAT1                    REG32((FMC) + 0x00000118U)                         /*!< FMC status register 1 */
#define FMC_CTL1                     REG32((FMC) + 0x0000011CU)                         /*!< FMC control register 1 */
#define FMC_ADDR1                    REG32((FMC) + 0x00000120U)                         /*!< FMC address register 1 */
#define FMC_WDATL1                   REG32((FMC) + 0x00000124U)                         /*!< FMC write data register LOW 1 */
#define FMC_WDATH1                   REG32((FMC) + 0x00000128U)                         /*!< FMC write data register HIGH 1 */
#define FMC_BLK1ECCCS                REG32((FMC) + 0x00000160U)                         /*!< FMC block 1 ECC control and status register */
#define FMC_BLK1UCECCADDR            REG32((FMC) + 0x00000164U)                         /*!< FMC block 1 UCECC address register */
#define FMC_BLK1CECCADDR0            REG32((FMC) + 0x00000168U)                         /*!< FMC block 1 CECC address0 register */
#define FMC_BLK1CECCADDR1            REG32((FMC) + 0x0000016CU)                         /*!< FMC block 1 CECC address1 register */
#define FMC_BLK1CECCADDR2            REG32((FMC) + 0x00000170U)                         /*!< FMC block 1 CECC address2 register */
#define FMC_BLK1CECCADDR3            REG32((FMC) + 0x00000174U)                         /*!< FMC block 1 CECC address3 register */
#define FMC_BUF1ECCCS                REG32((FMC) + 0x00000180U)                         /*!< FMC buffer 1 control register */
#define FMC_BUF1UCECCADDR            REG32((FMC) + 0x00000184U)                         /*!< FMC buffer 1 UCECC address register */
#define FMC_BUF1CECCADDR0            REG32((FMC) + 0x00000188U)                         /*!< FMC buffer 1 correct ECC address0 register */
#define FMC_BUF1CECCADDR1            REG32((FMC) + 0x0000018CU)                         /*!< FMC buffer 1 correct ECC address1 register */
#define FMC_BUF1CECCADDR2            REG32((FMC) + 0x00000190U)                         /*!< FMC buffer 1 correct ECC address2 register */
#define FMC_BUF1CECCADDR3            REG32((FMC) + 0x00000194U)                         /*!< FMC buffer 1 correct ECC address3 register */
#define FMC_BLK2ECCCS                REG32((FMC) + 0x00000260U)                         /*!< FMC block 2 ECC control and status register */
#define FMC_BLK2UCECCADDR            REG32((FMC) + 0x00000264U)                         /*!< FMC block 2 UCECC address register */
#define FMC_BLK2CECCADDR0            REG32((FMC) + 0x00000268U)                         /*!< FMC block 2 CECC address0 register */
#define FMC_BLK2CECCADDR1            REG32((FMC) + 0x0000026CU)                         /*!< FMC block 2 CECC address1 register */
#define FMC_BLK2CECCADDR2            REG32((FMC) + 0x00000270U)                         /*!< FMC block 2 CECC address2 register */
#define FMC_BLK2CECCADDR3            REG32((FMC) + 0x00000274U)                         /*!< FMC block 2 CECC address3 register */
#define FMC_BUF2ECCCS                REG32((FMC) + 0x00000280U)                         /*!< FMC buffer 2 control register */
#define FMC_BUF2UCECCADDR            REG32((FMC) + 0x00000284U)                         /*!< FMC buffer 2 UCECC address register */
#define FMC_BUF2CECCADDR0            REG32((FMC) + 0x00000288U)                         /*!< FMC buffer 2 correct ECC address0 register */
#define FMC_BUF2CECCADDR1            REG32((FMC) + 0x0000028CU)                         /*!< FMC buffer 2 correct ECC address1 register */
#define FMC_BUF2CECCADDR2            REG32((FMC) + 0x00000290U)                         /*!< FMC buffer 2 correct ECC address2 register */
#define FMC_BUF2CECCADDR3            REG32((FMC) + 0x00000294U)                         /*!< FMC buffer 2 correct ECC address3 register */
#define FMC_BLK3ECCCS                REG32((FMC) + 0x00000360U)                         /*!< FMC block 3 ECC control and status register */
#define FMC_BLK3UCECCADDR            REG32((FMC) + 0x00000364U)                         /*!< FMC block 3 UCECC address register */
#define FMC_BLK3CECCADDR0            REG32((FMC) + 0x00000368U)                         /*!< FMC block 3 CECC address0 register */
#define FMC_BLK3CECCADDR1            REG32((FMC) + 0x0000036CU)                         /*!< FMC block 3 CECC address1 register */
#define FMC_BLK3CECCADDR2            REG32((FMC) + 0x00000370U)                         /*!< FMC block 3 CECC address2 register */
#define FMC_BLK3CECCADDR3            REG32((FMC) + 0x00000374U)                         /*!< FMC block 3 CECC address3 register */
#define FMC_BUF3ECCCS                REG32((FMC) + 0x00000380U)                         /*!< FMC buffer 3 control register */
#define FMC_BUF3UCECCADDR            REG32((FMC) + 0x00000384U)                         /*!< FMC buffer 3 UCECC address register */
#define FMC_BUF3CECCADDR0            REG32((FMC) + 0x00000388U)                         /*!< FMC buffer 3 correct ECC address0 register */
#define FMC_BUF3CECCADDR1            REG32((FMC) + 0x0000038CU)                         /*!< FMC buffer 3 correct ECC address1 register */
#define FMC_BUF3CECCADDR2            REG32((FMC) + 0x00000390U)                         /*!< FMC buffer 3 correct ECC address2 register */
#define FMC_BUF3CECCADDR3            REG32((FMC) + 0x00000394U)                         /*!< FMC buffer 3 correct ECC address3 register */

#define OP_BYTE(x)                   REG32(OB + ((uint32_t)((uint32_t)0x04U * (x))))    /*!< HOST option bytes value */
#define OB_SPC                       REG16((OB) + 0x00000000U)                          /*!< HOST option bytes security protection value*/
#define OB_USER                      REG16((OB) + 0x00000002U)                          /*!< HOST option bytes user value*/
#define OB_SPC_USER                  REG32((OB) + 0x00000000U)                          /*!< HOST option bytes security protection value and user value */
#define OB_DATA                      REG32((OB) + 0x00000004U)                          /*!< HOST option bytes data value */

#define HSMOP_BYTE(x)                REG32(HSM_OB + ((uint32_t)((uint32_t)0x04U * (x))))/*!< HSM option bytes value */
#define OB_HSMUSER                   REG16((HSM_OB) + 0x00000000U)                      /*!< HSM option bytes user value*/
#define OB_HSMSPC                    REG16((HSM_OB) + 0x00000002U)                      /*!< HSM option bytes security protection value*/

/* bits definitions */
/* FMC_WS */
#define FMC_WS_WSCNT                 BITS(0,2)                                          /*!< wait state counter */

/* FMC_SPCKEY */
#define FMC_SPCKEY_SPCKEY            BITS(0,31)                                         /*!< SPC protection unlock key */

/* FMC_KEY0 */
#define FMC_KEY0_KEY                 BITS(0,31)                                         /*!< FMC control register 0 unlock key bits */

/* FMC_STAT0 */
#define FMC_STAT0_BUSY               BIT(0)                                             /*!< busy flag in stat0 register */
#define FMC_STAT0_PGSERR             BIT(1)                                             /*!< program sequence error flag in stat0 register */
#define FMC_STAT0_PGERR              BIT(2)                                             /*!< program error flag in stat0 register in stat0 register */
#define FMC_STAT0_WPERR              BIT(4)                                             /*!< erase/program protection error flag in stat0 register */
#define FMC_STAT0_ENDF               BIT(5)                                             /*!< end of operation flag in stat0 register */
#define FMC_STAT0_CBCMDERR           BIT(6)                                             /*!< checked area by the check blank command is all 0xFF or not in stat0 register */
#define FMC_STAT0_LOADECCERR         BIT(12)                                            /*!< uncorrected ECC error when load in stat0 register */
#define FMC_STAT0_COMPERR            BIT(13)                                            /*!< complement error in writing data flag in stat0 register */
#define FMC_STAT0_TMRERR             BIT(14)                                            /*!< TMR error flag bit in stat0 register */
#define FMC_STAT0_RSTERR             BIT(15)                                            /*!< POR or system reset error during erase/program flag in stat0 register */

/* FMC_CTL0 */
#define FMC_CTL0_PG                  BIT(0)                                             /*!< program command bit in ctl0 register */
#define FMC_CTL0_PER                 BIT(1)                                             /*!< page erase command bit in ctl0 register */
#define FMC_CTL0_MER                 BIT(2)                                             /*!< mass erase command bit in ctl0 register */
#define FMC_CTL0_START               BIT(6)                                             /*!< send command to FMC bit in ctl0 register */
#define FMC_CTL0_LK                  BIT(7)                                             /*!< lock bit of FMC_CTL0 register in ctl0 register */
#define FMC_CTL0_FSTPG               BIT(8)                                             /*!< fast program command bit in ctl0 register */
#define FMC_CTL0_ERRIE               BIT(10)                                            /*!< error interrupt enable bit in ctl0 register */
#define FMC_CTL0_ENDIE               BIT(12)                                            /*!< end of operation interrupt enable bit in ctl0 register */
#define FMC_CTL0_OBRLD               BIT(13)                                            /*!< option bytes reload bit in ctl0 register */
#define FMC_CTL0_CBCMD               BIT(16)                                            /*!< send check blank command in ctl0 register */
#define FMC_CTL0_MASTERID            BITS(20,23)                                        /*!< the Master ID of unlock FMC_CTL0 register in ctl0 register */
#define FMC_CTL0_CBCMDLEN            BITS(29,31)                                        /*!< check blank command read length in ctl0 register */

/* FMC_ADDR0 */
#define FMC_ADDR0_ADDR               BITS(0,31)                                         /*!< flash erase/program command address bits */

/* FMC_WDATL0 */
#define FMC_WDATL0_WDATA             BITS(0,31)                                         /*!< flash program command write data bits in write data low 0 register */

/* FMC_WDATH0 */
#define FMC_WDATH0_WDATA             BITS(0,31)                                         /*!< flash program command write data bits in write data high 0 register */

/* FMC_OBSTAT */
#define FMC_OBSTAT_OBERR             BIT(0)                                             /*!< HOST option bytes read error bit */
#define FMC_OBSTAT_PLEVEL            BITS(1,2)                                          /*!< HOST security protection level bits */
#define FMC_OBSTAT_SPCS              BIT(3)                                             /*!< HOST security protection state bits */
#define FMC_OBSTAT_nFWDG0_HW         BIT(8)                                             /*!< Free watchdog 0 mode configuration bit */
#define FMC_OBSTAT_nRST_STDBY        BIT(10)                                            /*!< Reset mode configuration bit when entering standby mode */
#define FMC_OBSTAT_nFWDG1_HW         BIT(13)                                            /*!< Free watchdog 1 mode configuration bit */
#define FMC_OBSTAT_nFWDG_STDBY       BIT(14)                                            /*!< Free watchdog count mode configuration bit in standby mode */
#define FMC_OBSTAT_DATA              BITS(16,31)                                        /*!< HOST option bytes data bits */

/* FMC_WP0 */
#define FMC_WP0_BK0WP                BITS(0,31)                                         /*!< store OB_BK0WP[31:0] of HOST option bytes block after system reset */

/* FMC_WP1 */
#define FMC_WP1_BK1WP                BITS(0,31)                                         /*!< store OB_BK1WP[31:0] of HOST option bytes block after system reset */

/* FMC_WP2 */
#define FMC_WP2_DFWP                 BITS(0,7)                                          /*!< store OB_DFWP[7:0] of HOST option bytes block after system reset */

/* FMC_OBUSER1_0 */
#define FMC_OBUSER1_0_USER1          BITS(0,31)                                         /*!< store OB_USER1[31:0] of HOST option bytes block after system reset */

/* FMC_OBUSER1_1 */
#define FMC_OBUSER1_1_USER1          BITS(0,31)                                         /*!< store OB_USER1[63:32] of HOST option bytes block after system reset */

/* FMC_HSMOBSTAT */
#define FMC_HSMOBSTAT_OBERR          BIT(0)                                             /*!< HSM option byte read error bit */
#define FMC_HSMOBSTAT_HSMSPCSET      BIT(1)                                             /*!< HSM security protection set bit */
#define FMC_HSMOBSTAT_HSMSPCS        BIT(2)                                             /*!< HSM security protection state */
#define FMC_HSMOBSTAT_USER           BITS(16,21)                                        /*!< Store OB_HSMUSER[5:0] of HSM option byte block after system reset */
#define FMC_HSMOBSTAT_HSM_nWWDG_HW   BIT(22)                                            /*!< HSM window watch dog mode configuration bit */
#define FMC_HSMOBSTAT_SWAP           BIT(23)                                            /*!< bank swap */
#define FMC_HSMOBSTAT_SPC            BITS(24,31)                                        /*!< HSM option byte security protection code */

/* FMC_HSMWP */
#define FMC_HSMWP_HSMPFWP            BITS(0,7)                                          /*!< store OB_HSMPFWP[7:0] of HSM option bytes block after system reset */
#define FMC_HSMWP_HSMDFWP            BITS(8,15)                                         /*!< store OB_HSMDFWP[7:0] of HSM option bytes block after system reset */
#define FMC_HSMWP_HSMSIZE            BITS(16,20)                                        /*!< HSM bank 0 / bank 1 size */
#define FMC_HSMWP_HSMSEC             BIT(23)                                            /*!< HSM security */
#define FMC_HSMWP_HSMEN              BIT(29)                                            /*!< HSM enable */
#define FMC_HSMWP_HOSTSIZE           BITS(30,31)                                        /*!< HOST bank 0 / bank 1 size */

/* FMC_BLKECCCS */
#define FMC_BLKECCCS_ECCCOR0         BIT(16)                                            /*!< block one bit error detected and correct flag 0 */
#define FMC_BLKECCCS_ECCCOR1         BIT(17)                                            /*!< block one bit error detected and correct flag 1 */
#define FMC_BLKECCCS_ECCCOR2         BIT(18)                                            /*!< block one bit error detected and correct flag 2 */
#define FMC_BLKECCCS_ECCCOR3         BIT(19)                                            /*!< block one bit error detected and correct flag 3 */
#define FMC_BLKECCCS_ECCCORC         BIT(20)                                            /*!< write 1 to clear ECCORx (x = 0, 1, 2, 3) */
#define FMC_BLKECCCS_ECCCORIE        BIT(24)                                            /*!< block one bit error correct interrupt enable */
#define FMC_BLKECCCS_ECCDETIE        BIT(25)                                            /*!< block two bit errors detect / EDC error / address ECC error interrupt enable */
#define FMC_BLKECCCS_ECCCOROVIE      BIT(26)                                            /*!< block more than 4 one bit error detect interrupt enable */
#define FMC_BLKECCCS_ECCAERR         BIT(28)                                            /*!< block one bit ECC error in address stage */
#define FMC_BLKECCCS_ECCCOROV        BIT(29)                                            /*!< block more than 4 one bit error flag */
#define FMC_BLKECCCS_ECCEDC          BIT(30)                                            /*!< block EDC after ECC checker error flag */
#define FMC_BLKECCCS_ECCDET          BIT(31)                                            /*!< block two bits error detect flag */

/* FMC_BLKUCECCADDR */
#define FMC_BLKUCECCADDR_ECCADDR     BITS(0,21)                                         /*!< the offset address of double word where an uncorrectable ECC error in block x is detected (x = 0, 1, 2, 3) */

/* FMC_BLKCECCADDR0 */
#define FMC_BLKCECCADDR0_ECCADDR     BITS(0,21)                                         /*!< the offset address of double word where an correctable ECC error 0 in block x is detected (x = 0, 1, 2, 3) */

/* FMC_BLKCECCADDR1 */
#define FMC_BLKCECCADDR1_ECCADDR     BITS(0,21)                                         /*!< the offset address of double word where an correctable ECC error 1 in block x is detected (x = 0, 1, 2, 3) */

/* FMC_BLKCECCADDR2 */
#define FMC_BLKCECCADDR2_ECCADDR     BITS(0,21)                                         /*!< the offset address of double word where an correctable ECC error 2 in block x is detected (x = 0, 1, 2, 3) */

/* FMC_BLKCECCADDR3 */
#define FMC_BLKCECCADDR3_ECCADDR     BITS(0,21)                                         /*!< the offset address of double word where an correctable ECC error 3 in block x is detected (x = 0, 1, 2, 3) */

/* FMC_BUFECCCS */
#define FMC_BUFECCCS_CBUFEN          BIT(0)                                             /*!< read code buffers enable bit */
#define FMC_BUFECCCS_DBUFEN          BIT(1)                                             /*!< read data buffers enable bit */
#define FMC_BUFECCCS_CPFEN           BIT(2)                                             /*!< code prefetch enable */
#define FMC_BUFECCCS_DPFEN           BIT(3)                                             /*!< data prefetch enable */
#define FMC_BUFECCCS_BUFEN           BIT(4)                                             /*!< buffers enable */
#define FMC_BUFECCCS_ECCCOR0         BIT(16)                                            /*!< buffer one bit error detected and correct flag 0 */
#define FMC_BUFECCCS_ECCCOR1         BIT(17)                                            /*!< buffer one bit error detected and correct flag 1 */
#define FMC_BUFECCCS_ECCCOR2         BIT(18)                                            /*!< buffer one bit error detected and correct flag 2 */
#define FMC_BUFECCCS_ECCCOR3         BIT(19)                                            /*!< buffer one bit error detected and correct flag 3 */
#define FMC_BUFECCCS_ECCCORC         BIT(20)                                            /*!< write 1 to clear ECCORx (x = 0, 1, 2, 3)*/
#define FMC_BUFECCCS_ECCCORIE        BIT(24)                                            /*!< buffer one bit error correct interrupt enable */
#define FMC_BUFECCCS_ECCDETIE        BIT(25)                                            /*!< buffer two bit errors detect / EDC error / address ECC error interrupt enable */
#define FMC_BUFECCCS_ECCCOROVIE      BIT(26)                                            /*!< buffer more than 4 one bit error detect interrupt enable */
#define FMC_BUFECCCS_ECCAERR         BIT(28)                                            /*!< buffer one bit ECC error in address stage */
#define FMC_BUFECCCS_ECCCOROV        BIT(29)                                            /*!< buffer more than 4 one bit error detected */
#define FMC_BUFECCCS_ECCEDC          BIT(30)                                            /*!< buffer EDC after ECC checker error flag */
#define FMC_BUFECCCS_ECCDET          BIT(31)                                            /*!< buffer two bits error detect flag */

/* FMC_BUFUCECCADDR */
#define FMC_BUFUCECCADDR_ECCADDR     BITS(0,23)                                         /*!< the offset address of double word where an uncorrectable ECC error in buffer x is detected (x = 0, 1, 2, 3) */

/* FMC_BUFCECCADDR0 */
#define FMC_BUFCECCADDR0_ECCADDR     BITS(0,23)                                         /*!< the offset address of double word where an correctable ECC error 0 in buffer x is detected (x = 0, 1, 2, 3) */

/* FMC_BUFCECCADDR1 */
#define FMC_BUFCECCADDR1_ECCADDR     BITS(0,23)                                         /*!< the offset address of double word where an correctable ECC error 1 in buffer x is detected (x = 0, 1, 2, 3) */

/* FMC_BUFCECCADDR2 */
#define FMC_BUFCECCADDR2_ECCADDR     BITS(0,23)                                         /*!< the offset address of double word where an correctable ECC error 2 in buffer x is detected (x = 0, 1, 2, 3) */

/* FMC_BUFCECCADDR3 */
#define FMC_BUFCECCADDR3_ECCADDR     BITS(0,23)                                         /*!< the offset address of double word where an correctable ECC error 3 in buffer x is detected (x = 0, 1, 2, 3) */

/* FMC_FPBECCCS */
#define FMC_FPBECCCS_ECCCOR0         BIT(16)                                            /*!< fast program buffer one bit error detected and correct flag 0 */
#define FMC_FPBECCCS_ECCCOR1         BIT(17)                                            /*!< fast program buffer one bit error detected and correct flag 1 */
#define FMC_FPBECCCS_ECCCOR2         BIT(18)                                            /*!< fast program buffer one bit error detected and correct flag 2 */
#define FMC_FPBECCCS_ECCCOR3         BIT(19)                                            /*!< fast program buffer one bit error detected and correct flag 3 */
#define FMC_FPBECCCS_ECCCORC         BIT(20)                                            /*!< write 1 to clear ECCORx (x = 0,1,2,3) */
#define FMC_FPBECCCS_ECCCORIE        BIT(24)                                            /*!< fast program buffer one bit error correct interrupt enable */
#define FMC_FPBECCCS_ECCDETIE        BIT(25)                                            /*!< fast program buffer two bit errors detect / EDC error / address ECC error interrupt enable */
#define FMC_FPBECCCS_ECCCOROVIE      BIT(26)                                            /*!< fast program buffer more than 4 one bit error detect interrupt enable */
#define FMC_FPBECCCS_ECCAERR         BIT(28)                                            /*!< fast program buffer one bit ECC error in address stage */
#define FMC_FPBECCCS_ECCCOROV        BIT(29)                                            /*!< fast program buffer more than 4 one bit error detected */
#define FMC_FPBECCCS_ECCEDC          BIT(30)                                            /*!< fast program buffer EDC after ECC checker error flag */
#define FMC_FPBECCCS_ECCDET          BIT(31)                                            /*!< fast program buffer two bits error detect flag */

/* FMC_FPB_UCECCADDR */
#define FMC_FPB_UCECCADDR_ECCADDR    BITS(0,9)                                          /*!< the offset address of double word where an uncorrectable ECC error in fast program buffer is detected */

/* FMC_FPB_CECCADDR0 */
#define FMC_FPB_CECCADDR0_ECCADDR    BITS(0,9)                                          /*!< the offset address of double word where an correctable ECC error 0 in fast program buffer is detected */

/* FMC_FPB_CECCADDR1 */
#define FMC_FPB_CECCADDR1_ECCADDR    BITS(0,9)                                          /*!< the offset address of double word where an correctable ECC error 1 in fast program buffer is detected */

/* FMC_FPB_CECCADDR2 */
#define FMC_FPB_CECCADDR2_ECCADDR    BITS(0,9)                                          /*!< the offset address of double word where an correctable ECC error 2 in fast program buffer is detected */

/* FMC_FPB_CECCADDR3 */
#define FMC_FPB_CECCADDR3_ECCADDR    BITS(0,9)                                          /*!< the offset address of double word where an correctable ECC error 3 in fast program buffer is detected */

/* FMC_PID0 */
#define FMC_PID0_PID                 BITS(0,31)                                         /*!< Product reserved ID code register 0 */

/* FMC_PID1 */
#define FMC_PID1_PID                 BITS(0,31)                                         /*!< Product reserved ID code register 1 */

/* FMC_STAT1 */
#define FMC_STAT1_BUSY               BIT(0)                                             /*!< busy flag in stat1 register */
#define FMC_STAT1_PGSERR             BIT(1)                                             /*!< program sequence error flag in stat1 register */
#define FMC_STAT1_PGERR              BIT(2)                                             /*!< program error flag in stat1 register */
#define FMC_STAT1_WPERR              BIT(4)                                             /*!< erase/program protection error flag in stat1 register */
#define FMC_STAT1_ENDF               BIT(5)                                             /*!< end of operation flag in stat1 register */
#define FMC_STAT1_CBCMDERR           BIT(6)                                             /*!< checked area by the check blank command is all 0xFF or not in stat1 register */
#define FMC_STAT1_TMRERR             BIT(14)                                            /*!< TMR error flag bit in stat1 register */
#define FMC_STAT1_RSTERR             BIT(15)                                            /*!< POR or system reset during erase/program flag in stat1 register */

/* FMC_CTL1 */
#define FMC_CTL1_PG                  BIT(0)                                             /*!< program command bit in ctl1 register */
#define FMC_CTL1_PER                 BIT(1)                                             /*!< page erase command bit in ctl1 register */
#define FMC_CTL1_START               BIT(6)                                             /*!< send command to FMC bit in ctl1 register */
#define FMC_CTL1_LK                  BIT(7)                                             /*!< lock bit in ctl1 register */
#define FMC_CTL1_FSTPG               BIT(8)                                             /*!< fast program command bit in ctl1 register */
#define FMC_CTL1_ERRIE               BIT(10)                                            /*!< error interrupt enable bit in ctl1 register */
#define FMC_CTL1_ENDIE               BIT(12)                                            /*!< end of operation interrupt enable bit in ctl1 register */
#define FMC_CTL1_CBCMD               BIT(16)                                            /*!< option bytes reload bit in ctl1 register */
#define FMC_CTL1_MASTERID            BITS(20,22)                                        /*!< the Master ID of unlock FMC_CTL1 register in ctl1 register */
#define FMC_CTL1_CBCMDLEN            BITS(29,31)                                        /*!< check blank command read length in ctl1 register */

/* FMC_ADDR1 */
#define FMC_ADDR1_ADDR               BITS(0,31)                                         /*!< flash bank1 command address bits */

/* FMC_WDATL1 */
#define FMC_WDATL1_WDATA             BITS(0,31)                                         /*!< flash program command write data bits in write data low 1 register */

/* FMC_WDATH1 */
#define FMC_WDATH1_WDATA             BITS(0,31)                                         /*!< flash program command write data bits in write data high 1 register */

/* constants definitions */
/* FMC hsm option bytes initialize struct */
typedef struct {
    union {
        struct {
            uint8_t   hsmuser: 6;                                                       /*!< hsm option bytes hsmuser sub fields */
            uint8_t   hsm_nwwdg_hw: 1;                                                  /*!< hsm option bytes nwwdg_hw fields */
            uint8_t   bswap: 1;                                                         /*!< hsm option bytes bswap fields */
        }  hsmuser_struct;
        uint8_t hsm_user;
    } ob_hsmuser;                                                                       /*!< hsm option bytes hsmuser fields */
    uint8_t ob_hsmspc;                                                                  /*!< hsm option bytes hsmspc fields */
    uint8_t ob_hsmpfwp;                                                                 /*!< hsm option bytes hsmpfwp fields */
    uint8_t ob_hsmdfwp;                                                                 /*!< hsm option bytes hsmdfwp fields */
} fmc_hsm_opt_parameter_struct;

/* FMC state */
typedef enum {
    FMC_READY,                                                                          /*!< the operation has been completed */
    FMC_BUSY,                                                                           /*!< the operation is in progress */
    FMC_PGSERR,                                                                         /*!< program sequence error */
    FMC_PGERR,                                                                          /*!< program error */
    FMC_WPERR,                                                                          /*!< erase/program protection error */
    FMC_CBCMDERR,                                                                       /*!< the checked area not blank error */
    FMC_LOADECCERR,                                                                     /*!< uncorrected ECC error when load HOST OPT / HSM OPT / HSM OTP */
    FMC_COMPERR,                                                                        /*!< complement error in writing data */
    FMC_TMRERR,                                                                         /*!< TMR error */
    FMC_RSTERR,                                                                         /*!< POR or system reset during flash erase/program error */
    FMC_TOERR,                                                                          /*!< timeout error */
    FMC_OB_HSPC,                                                                        /*!< FMC HOST is under high security protection */
    FMC_HSMOB_HSPC                                                                      /*!< FMC HSM is under high security protection */
} fmc_state_enum;

/* FMC control interface 0 area */
typedef enum {
    BANK0_AREA = 0,                                                                     /*!< main flash bank0 area */
    BANK1_AREA,                                                                         /*!< main flash bank1 area */
    DATA_FLASH_AREA,                                                                    /*!< HOST data area */
    HSM_BANK_AREA,                                                                      /*!< HSM bank area */
    HSM_DATA_AREA                                                                       /*!< HSM data flash area */
} fmc_area_enum;

/* FMC register number */
typedef enum {
    FMC_REG_0 = 0,                                                                      /*!< FMC block0, buffer0 or fast program buffer register */
    FMC_REG_1 = 1,                                                                      /*!< FMC block1 or buffer1 register */
    FMC_REG_2 = 2,                                                                      /*!< FMC block2 or buffer2 register */
    FMC_REG_3 = 3                                                                       /*!< FMC block3 or buffer3 register */
} fmc_register_enum;

/* FMC buffer number */
typedef enum {
    FMC_BUFF_0 = 0,                                                                     /*!< FMC buffer 0 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    FMC_BUFF_1 = 1,                                                                     /*!< FMC buffer 1 (Only applicable to GD32A72XX / GD32A74XX) */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
    FMC_BUFF_2 = 2,                                                                     /*!< FMC buffer 2 */
    FMC_BUFF_3 = 3                                                                      /*!< FMC buffer 3 */
} fmc_buff_enum;

/* FMC correctable ECC address */
typedef enum {
    CECC_ADDR0 = 0,                                                                     /*!< FMC correctable ECC address 0 */
    CECC_ADDR1 = 1,                                                                     /*!< FMC correctable ECC address 1 */
    CECC_ADDR2 = 2,                                                                     /*!< FMC correctable ECC address 2 */
    CECC_ADDR3 = 3                                                                      /*!< FMC correctable ECC address 3 */
} fmc_cecc_addr_enum;

/* define the FMC bit position and its register index offset */
#define FMC_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define FMC_REG_VAL(offset)             (REG32(FMC + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U)))
#define FMC_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)
#define FMC_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22U) | (uint32_t)((bitpos2) << 16U)\
                                                             | (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos)))
#define FMC_REG_VAL2(offset)            (REG32(FMC + ((uint32_t)(offset) >> 22U)))
#define FMC_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16U)

#define FMC_REG_VAL3(offset, macro)     (REG32(FMC + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U) + 0x100U * (uint32_t)(macro)))
#define FMC_REG_VAL4(offset, macro)     (REG32(FMC + ((uint32_t)(offset) >> 22U) + 0x100U * (uint32_t)(macro)))

/* register offset */
#define FMC_STAT0_REG_OFFSET            ((uint32_t)0x00000018U)                         /*!< STAT0 register offset */
#define FMC_STAT1_REG_OFFSET            ((uint32_t)0x00000118U)                         /*!< STAT1 register offset */
#define FMC_CTL0_REG_OFFSET             ((uint32_t)0x0000001CU)                         /*!< CTL0 register offset */
#define FMC_CTL1_REG_OFFSET             ((uint32_t)0x0000011CU)                         /*!< CTL1 register offset */
#define FMC_OBSTAT_REG_OFFSET           ((uint32_t)0x00000030U)                         /*!< OBSTAT register offset */
#define FMC_HSMOBSTAT_REG_OFFSET        ((uint32_t)0x00000048U)                         /*!< HSMOBSTAT register offset */
#define FMC_BLKECCCS_REG_OFFSET         ((uint32_t)0x00000060U)                         /*!< BLKxECCCS register offset */
#define FMC_BUFECCCS_REG_OFFSET         ((uint32_t)0x00000080U)                         /*!< BUFxECCCS register offset */
#define FMC_FPBECCCS_REG_OFFSET         ((uint32_t)0x000000A0U)                         /*!< FPBxECCCS register offset */

/* FMC flags */
typedef enum {
    /* flags in STAT0 register */
    FMC_STAT0_FLAG_BUSY       = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 0U),              /*!< busy flag in stat0 register */
    FMC_STAT0_FLAG_PGSERR     = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 1U),              /*!< program sequence error flag in stat0 register */
    FMC_STAT0_FLAG_PGERR      = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 2U),              /*!< program error flag in stat0 register */
    FMC_STAT0_FLAG_WPERR      = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 4U),              /*!< erase/program protection error flag in stat0 register */
    FMC_STAT0_FLAG_END        = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 5U),              /*!< end of operation flag in stat0 register */
    FMC_STAT0_FLAG_CBCMDERR   = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 6U),              /*!< checked area by the check blank command is all 0xFF or not flag in stat0 register */
    FMC_STAT0_FLAG_LOADECCERR = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 12U),             /*!< uncorrected ECC error when load flag in stat0 register */
    FMC_STAT0_FLAG_COMPERR    = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 13U),             /*!< complement error flag in stat0 register */
    FMC_STAT0_FLAG_TMRERR     = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 14U),             /*!< TMR error flag in stat0 register */
    FMC_STAT0_FLAG_RSTERR     = FMC_REGIDX_BIT(FMC_STAT0_REG_OFFSET, 15U),             /*!< POR or system reset during erase/program flag in stat0 register */
    /* flags in STAT1 register */
    FMC_STAT1_FLAG_BUSY       = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 0U),              /*!< busy flag in stat1 register */
    FMC_STAT1_FLAG_PGSERR     = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 1U),              /*!< program sequence error flag in stat1 register */
    FMC_STAT1_FLAG_PGERR      = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 2U),              /*!< program error flag in stat1 register */
    FMC_STAT1_FLAG_WPERR      = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 4U),              /*!< erase/program protection error flag in stat1 register */
    FMC_STAT1_FLAG_END        = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 5U),              /*!< end of operation flag in stat1 register */
    FMC_STAT1_FLAG_CBCMDERR   = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 6U),              /*!< checked area by the check blank command is all 0xFF or not flag in stat1 register */
    FMC_STAT1_FLAG_TMRERR     = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 14U),             /*!< TMR error flag in stat1 register */
    FMC_STAT1_FLAG_RSTERR     = FMC_REGIDX_BIT(FMC_STAT1_REG_OFFSET, 15U),             /*!< POR or system reset during erase/program flag in stat1 register */
    /* flags in OBSTAT register */
    FMC_FLAG_OBERR            = FMC_REGIDX_BIT(FMC_OBSTAT_REG_OFFSET, 0U),             /*!< HOST option bytes error flag */
    /* flags in HSMOBSTAT register */
    FMC_FLAG_HSMOBERR         = FMC_REGIDX_BIT(FMC_HSMOBSTAT_REG_OFFSET, 0U)           /*!< HSM option bytes read error flag */
} fmc_flag_enum;

/* FMC interrupt flags */
typedef enum {
    /* interrupt flags in STAT0 register */
    FMC_STAT0_INT_FLAG_PGSERR   = FMC_REGIDX_BIT2(FMC_CTL0_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 1U),        /*!< program sequence error interrupt flag in stat0 register */
    FMC_STAT0_INT_FLAG_PGERR    = FMC_REGIDX_BIT2(FMC_CTL0_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 2U),        /*!< program error interrupt flag in stat0 register */
    FMC_STAT0_INT_FLAG_WPERR    = FMC_REGIDX_BIT2(FMC_CTL0_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 4U),        /*!< erase/program protection error interrupt flag in stat0 register */
    FMC_STAT0_INT_FLAG_END      = FMC_REGIDX_BIT2(FMC_CTL0_REG_OFFSET, 12U, FMC_STAT0_REG_OFFSET, 5U),        /*!< end of operation interrupt flag in stat0 register */
    FMC_STAT0_INT_FLAG_CBCMDERR = FMC_REGIDX_BIT2(FMC_CTL0_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 6U),        /*!< checked area by the check blank command is all 0xFF or not interrupt flag in stat0 register */
    FMC_STAT0_INT_FLAG_COMPERR  = FMC_REGIDX_BIT2(FMC_CTL0_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 13U),       /*!< complement error flag in stat0 register */
    FMC_STAT0_INT_FLAG_TMRERR   = FMC_REGIDX_BIT2(FMC_CTL0_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 14U),       /*!< TMR error flag in stat0 register */
    FMC_STAT0_INT_FLAG_RSTERR   = FMC_REGIDX_BIT2(FMC_CTL0_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 15U),       /*!< POR or system reset during erase/program interrupt flag in stat0 register */
    /* interrupt flags in STAT1 register */
    FMC_STAT1_INT_FLAG_PGSERR   = FMC_REGIDX_BIT2(FMC_CTL1_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 1U),        /*!< program sequence error interrupt flag in stat1 register */
    FMC_STAT1_INT_FLAG_PGERR    = FMC_REGIDX_BIT2(FMC_CTL1_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 2U),        /*!< program error interrupt flag in stat1 register */
    FMC_STAT1_INT_FLAG_WPERR    = FMC_REGIDX_BIT2(FMC_CTL1_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 4U),        /*!< erase/program protection error interrupt flag in stat1 register */
    FMC_STAT1_INT_FLAG_END      = FMC_REGIDX_BIT2(FMC_CTL1_REG_OFFSET, 12U, FMC_STAT0_REG_OFFSET, 5U),        /*!< end of operation interrupt flag in stat1 register */
    FMC_STAT1_INT_FLAG_CBCMDERR = FMC_REGIDX_BIT2(FMC_CTL1_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 6U),        /*!< checked area by the check blank command is all 0xFF or not interrupt flag in stat1 register */
    FMC_STAT1_INT_FLAG_TMRERR   = FMC_REGIDX_BIT2(FMC_CTL1_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 14U),       /*!< TMR error flag in stat1 register */
    FMC_STAT1_INT_FLAG_RSTERR   = FMC_REGIDX_BIT2(FMC_CTL1_REG_OFFSET, 10U, FMC_STAT0_REG_OFFSET, 15U)        /*!< POR or system reset during erase/program interrupt flag in stat1 register */
} fmc_interrupt_flag_enum;

/* FMC interrupt */
typedef enum {
    /* interrupt in CTL0 register */
    FMC_CTL0_INT_ERR = FMC_REGIDX_BIT(FMC_CTL0_REG_OFFSET, 10U),                        /*!< error interrupt in ctl0 register */
    FMC_CTL0_INT_END = FMC_REGIDX_BIT(FMC_CTL0_REG_OFFSET, 12U),                        /*!< end of operation interrupt in ctl0 register */
    /* interrupt in CTL1 register */
    FMC_CTL1_INT_ERR = FMC_REGIDX_BIT(FMC_CTL1_REG_OFFSET, 10U),                        /*!< error interrupt in ctl0 register */
    FMC_CTL1_INT_END = FMC_REGIDX_BIT(FMC_CTL1_REG_OFFSET, 12U)                         /*!< end of operation interrupt in ctl0 register */
} fmc_interrupt_enum;

/* FMC ECC flags */
typedef enum {
    /* flags in BLKxECCCS register */
    FMC_BLKFLAG_ECCCOR0  = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 16U),                /*!< block one bit error detected and correct flag 0 */
    FMC_BLKFLAG_ECCCOR1  = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 17U),                /*!< block one bit error detected and correct flag 1 */
    FMC_BLKFLAG_ECCCOR2  = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 18U),                /*!< block one bit error detected and correct flag 2 */
    FMC_BLKFLAG_ECCCOR3  = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 19U),                /*!< block one bit error detected and correct flag 3 */
    FMC_BLKFLAG_ECCAERR  = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 28U),                /*!< block one bit error flag at ECC address */
    FMC_BLKFLAG_ECCCOROV = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 29U),                /*!< block more than 4 one bit error detected */
    FMC_BLKFLAG_ECCEDC   = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 30U),                /*!< block EDC after ECC checker error flag */
    FMC_BLKFLAG_ECCDET   = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 31U),                /*!< block two bit errors detect flag */
    /* flags in BUFxECCCS register */
    FMC_BUFFLAG_ECCCOR0  = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 16U),                /*!< buffer one bit error detected and correct flag 0 */
    FMC_BUFFLAG_ECCCOR1  = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 17U),                /*!< buffer one bit error detected and correct flag 1 */
    FMC_BUFFLAG_ECCCOR2  = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 18U),                /*!< buffer one bit error detected and correct flag 2 */
    FMC_BUFFLAG_ECCCOR3  = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 19U),                /*!< buffer one bit error detected and correct flag 3 */
    FMC_BUFFLAG_ECCAERR  = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 28U),                /*!< buffer one bit error flag at ECC address */
    FMC_BUFFLAG_ECCCOROV = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 29U),                /*!< buffer more than 4 one bit error detected */
    FMC_BUFFLAG_ECCEDC   = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 30U),                /*!< buffer EDC after ECC checker error flag */
    FMC_BUFFLAG_ECCDET   = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 31U),                /*!< buffer two bit errors detect flag */
    /* flags in FPB_ECCCS register */
    FMC_FPBFLAG_ECCCOR0  = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 16U),                /*!< fast program buffer one bit error detected and correct flag 0 */
    FMC_FPBFLAG_ECCCOR1  = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 17U),                /*!< fast program buffer one bit error detected and correct flag 1 */
    FMC_FPBFLAG_ECCCOR2  = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 18U),                /*!< fast program buffer one bit error detected and correct flag 2 */
    FMC_FPBFLAG_ECCCOR3  = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 19U),                /*!< fast program buffer one bit error detected and correct flag 3 */
    FMC_FPBFLAG_ECCAERR  = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 28U),                /*!< fast program buffer ECC address one bit error flag */
    FMC_FPBFLAG_ECCCOROV = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 29U),                /*!< fast program buffer more than 4 one bit error detected */
    FMC_FPBFLAG_ECCEDC   = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 30U),                /*!< fast program buffer EDC after ECC checker error flag */
    FMC_FPBFLAG_ECCDET   = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 31U)                 /*!< fast program buffer two bit errors detect flag */
} fmc_ecc_flag_enum;

/* FMC ECC interrupt */
typedef enum {
    /* interrupt in BLKxECCCS register */
    FMC_BLK_INT_ECCCOR  = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 24U),                  /*!< block one bit error correct interrupt */
    FMC_BLK_INT_ECCDET  = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 25U),                  /*!< block two bits error interrupt */
    FMC_BLK_INT_ECCCORV = FMC_REGIDX_BIT(FMC_BLKECCCS_REG_OFFSET, 26U),                  /*!< block more than 4 one bit error detect interrupt */
    /* interrupt in BUFxECCCS register */
    FMC_BUF_INT_ECCCOR  = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 24U),                  /*!< buffer one bit error correct interrupt */
    FMC_BUF_INT_ECCDET  = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 25U),                  /*!< buffer two bits error interrupt */
    FMC_BUF_INT_ECCCORV = FMC_REGIDX_BIT(FMC_BUFECCCS_REG_OFFSET, 26U),                  /*!< buffer more than 4 one bit error detect interrupt */
    /* interrupt in FPB_ECCCS register */
    FMC_FPB_INT_ECCCOR  = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 24U),                  /*!< fast program buffer one bit error correct interrupt */
    FMC_FPB_INT_ECCDET  = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 25U),                  /*!< fast program buffer two bits error interrupt */
    FMC_FPB_INT_ECCCORV = FMC_REGIDX_BIT(FMC_FPBECCCS_REG_OFFSET, 26U),                  /*!< fast program buffer more than 4 one bit error detect interrupt */
} fmc_ecc_interrupt_enum;

/* FMC ECC interrupt flags */
typedef enum {
    /* interrupt flags in BLKECCCS register */
    FMC_BLK_INT_FLAG_ECCCOR0  = FMC_REGIDX_BIT2(FMC_BLKECCCS_REG_OFFSET, 24U, FMC_BLKECCCS_REG_OFFSET, 16U),      /*!< block one bit error detected and correct interrupt flag 0 */
    FMC_BLK_INT_FLAG_ECCCOR1  = FMC_REGIDX_BIT2(FMC_BLKECCCS_REG_OFFSET, 24U, FMC_BLKECCCS_REG_OFFSET, 17U),      /*!< block one bit error detected and correct interrupt flag 1 */
    FMC_BLK_INT_FLAG_ECCCOR2  = FMC_REGIDX_BIT2(FMC_BLKECCCS_REG_OFFSET, 24U, FMC_BLKECCCS_REG_OFFSET, 18U),      /*!< block one bit error detected and correct interrupt flag 2 */
    FMC_BLK_INT_FLAG_ECCCOR3  = FMC_REGIDX_BIT2(FMC_BLKECCCS_REG_OFFSET, 24U, FMC_BLKECCCS_REG_OFFSET, 19U),      /*!< block one bit error detected and correct interrupt flag 3 */
    FMC_BLK_INT_FLAG_ECCAERR  = FMC_REGIDX_BIT2(FMC_BLKECCCS_REG_OFFSET, 25U, FMC_BLKECCCS_REG_OFFSET, 28U),      /*!< block one bit error flag at ECC address */
    FMC_BLK_INT_FLAG_ECCCOROV = FMC_REGIDX_BIT2(FMC_BLKECCCS_REG_OFFSET, 26U, FMC_BLKECCCS_REG_OFFSET, 29U),      /*!< block more than 4 one bit error detected interrupt flag */
    FMC_BLK_INT_FLAG_ECCEDC   = FMC_REGIDX_BIT2(FMC_BLKECCCS_REG_OFFSET, 24U, FMC_BLKECCCS_REG_OFFSET, 30U),      /*!< block EDC after ECC checker error interrupt flag */
    FMC_BLK_INT_FLAG_ECCDET   = FMC_REGIDX_BIT2(FMC_BLKECCCS_REG_OFFSET, 25U, FMC_BLKECCCS_REG_OFFSET, 31U),      /*!< block two bit errors detect interrupt flag */
    /* interrupt flags in BUFECCCS register */
    FMC_BUF_INT_FLAG_ECCCOR0  = FMC_REGIDX_BIT2(FMC_BUFECCCS_REG_OFFSET, 24U, FMC_BUFECCCS_REG_OFFSET, 16U),      /*!< buffer one bit error detected and correct interrupt flag 0 */
    FMC_BUF_INT_FLAG_ECCCOR1  = FMC_REGIDX_BIT2(FMC_BUFECCCS_REG_OFFSET, 24U, FMC_BUFECCCS_REG_OFFSET, 17U),      /*!< buffer one bit error detected and correct interrupt flag 1 */
    FMC_BUF_INT_FLAG_ECCCOR2  = FMC_REGIDX_BIT2(FMC_BUFECCCS_REG_OFFSET, 24U, FMC_BUFECCCS_REG_OFFSET, 18U),      /*!< buffer one bit error detected and correct interrupt flag 2 */
    FMC_BUF_INT_FLAG_ECCCOR3  = FMC_REGIDX_BIT2(FMC_BUFECCCS_REG_OFFSET, 24U, FMC_BUFECCCS_REG_OFFSET, 19U),      /*!< buffer one bit error detected and correct interrupt flag 3 */
    FMC_BUF_INT_FLAG_ECCAERR  = FMC_REGIDX_BIT2(FMC_BUFECCCS_REG_OFFSET, 25U, FMC_BUFECCCS_REG_OFFSET, 28U),      /*!< buffer one bit error flag at ECC address */
    FMC_BUF_INT_FLAG_ECCCOROV = FMC_REGIDX_BIT2(FMC_BUFECCCS_REG_OFFSET, 26U, FMC_BUFECCCS_REG_OFFSET, 29U),      /*!< buffer more than 4 one bit error detected interrupt flag */
    FMC_BUF_INT_FLAG_ECCEDC   = FMC_REGIDX_BIT2(FMC_BUFECCCS_REG_OFFSET, 24U, FMC_BUFECCCS_REG_OFFSET, 30U),      /*!< buffer EDC after ECC checker error interrupt flag */
    FMC_BUF_INT_FLAG_ECCDET   = FMC_REGIDX_BIT2(FMC_BUFECCCS_REG_OFFSET, 25U, FMC_BUFECCCS_REG_OFFSET, 31U),      /*!< buffer two bit errors detect interrupt flag */
    /* interrupt flags in FPBECCCS register */
    FMC_FPB_INT_FLAG_ECCCOR0  = FMC_REGIDX_BIT2(FMC_FPBECCCS_REG_OFFSET, 24U, FMC_FPBECCCS_REG_OFFSET, 16U),      /*!< fast program buffer one bit error detected and correct interrupt flag 0 */
    FMC_FPB_INT_FLAG_ECCCOR1  = FMC_REGIDX_BIT2(FMC_FPBECCCS_REG_OFFSET, 24U, FMC_FPBECCCS_REG_OFFSET, 17U),      /*!< fast program buffer one bit error detected and correct interrupt flag 1 */
    FMC_FPB_INT_FLAG_ECCCOR2  = FMC_REGIDX_BIT2(FMC_FPBECCCS_REG_OFFSET, 24U, FMC_FPBECCCS_REG_OFFSET, 18U),      /*!< fast program buffer one bit error detected and correct interrupt flag 2 */
    FMC_FPB_INT_FLAG_ECCCOR3  = FMC_REGIDX_BIT2(FMC_FPBECCCS_REG_OFFSET, 24U, FMC_FPBECCCS_REG_OFFSET, 19U),      /*!< fast program buffer one bit error detected and correct interrupt flag 3 */
    FMC_FPB_INT_FLAG_ECCAERR  = FMC_REGIDX_BIT2(FMC_FPBECCCS_REG_OFFSET, 25U, FMC_FPBECCCS_REG_OFFSET, 28U),      /*!< fast program buffer one bit error flag at ECC address */
    FMC_FPB_INT_FLAG_ECCCOROV = FMC_REGIDX_BIT2(FMC_FPBECCCS_REG_OFFSET, 26U, FMC_FPBECCCS_REG_OFFSET, 29U),      /*!< fast program buffer more than 4 one bit error detected interrupt flag */
    FMC_FPB_INT_FLAG_ECCEDC   = FMC_REGIDX_BIT2(FMC_FPBECCCS_REG_OFFSET, 24U, FMC_FPBECCCS_REG_OFFSET, 30U),      /*!< fast program buffer EDC after ECC checker error interrupt flag */
    FMC_FPB_INT_FLAG_ECCDET   = FMC_REGIDX_BIT2(FMC_FPBECCCS_REG_OFFSET, 25U, FMC_FPBECCCS_REG_OFFSET, 31U)       /*!< fast program buffer two bit errors detect interrupt flag */
} fmc_ecc_interrupt_flag_enum;

/* unlock key x */
#define UNLOCK_KEY0(x)               ((uint32_t)(0x45670123U + (x)))                    /*!< unlock key x 0 */
#define UNLOCK_KEY1(x)               ((uint32_t)(0xCDEF89ABU + (x)))                    /*!< unlock key x 1 */

/* wait state counter value */
#define WS_WSCNT(regval)             (BITS(0,2) & ((uint32_t)(regval) << 0))
#define WS_WSCNT_0                   WS_WSCNT(0)                                        /*!< 0 wait state added */
#define WS_WSCNT_1                   WS_WSCNT(1)                                        /*!< 1 wait state added */
#define WS_WSCNT_2                   WS_WSCNT(2)                                        /*!< 2 wait state added */
#define WS_WSCNT_3                   WS_WSCNT(3)                                        /*!< 3 wait state added */
#define WS_WSCNT_4                   WS_WSCNT(4)                                        /*!< 4 wait state added */
#define WS_WSCNT_5                   WS_WSCNT(5)                                        /*!< 5 wait state added */

/* check blank command read length */
#define FMC_CBCMDLEN_2_DW            ((uint32_t)0x00000000U)                            /*!< check blank command read length is 2 double words (16 bytes) */
#define FMC_CBCMDLEN_4_DW            ((uint32_t)0x00000001U)                            /*!< check blank command read length is 4 double words (32 bytes) */
#define FMC_CBCMDLEN_8_DW            ((uint32_t)0x00000002U)                            /*!< check blank command read length is 8 double words (64 bytes) */
#define FMC_CBCMDLEN_16_DW           ((uint32_t)0x00000003U)                            /*!< check blank command read length is 16 double words (128 bytes) */
#define FMC_CBCMDLEN_32_DW           ((uint32_t)0x00000004U)                            /*!< check blank command read length is 32 double words (256 bytes) */
#define FMC_CBCMDLEN_64_DW           ((uint32_t)0x00000005U)                            /*!< check blank command read length is 64 double words (512 bytes) */
#define FMC_CBCMDLEN_128_DW          ((uint32_t)0x00000006U)                            /*!< check blank command read length is 128 double words (1024 bytes) */
#define FMC_CBCMDLEN_256_DW          ((uint32_t)0x00000007U)                            /*!< check blank command read length is 256 double words (2048 bytes) */

/* HSM bank size config */
#define HSM_BANK_SIZE_NONE           ((uint32_t)0x00000000U)                            /*!< HSM bank size is none */
#define HSM_BANK_SIZE_16K            ((uint32_t)0x00000001U)                            /*!< HSM bank size is 16K */
#define HSM_BANK_SIZE_32K            ((uint32_t)0x00000002U)                            /*!< HSM bank size is 32K */
#define HSM_BANK_SIZE_48K            ((uint32_t)0x00000003U)                            /*!< HSM bank size is 48K */
#define HSM_BANK_SIZE_64K            ((uint32_t)0x00000004U)                            /*!< HSM bank size is 64K */
#define HSM_BANK_SIZE_80K            ((uint32_t)0x00000005U)                            /*!< HSM bank size is 80K */
#define HSM_BANK_SIZE_96K            ((uint32_t)0x00000006U)                            /*!< HSM bank size is 96K */
#define HSM_BANK_SIZE_112K           ((uint32_t)0x00000007U)                            /*!< HSM bank size is 112K */
#define HSM_BANK_SIZE_128K           ((uint32_t)0x00000008U)                            /*!< HSM bank size is 128K */
#define HSM_BANK_SIZE_144K           ((uint32_t)0x00000009U)                            /*!< HSM bank size is 144K */
#define HSM_BANK_SIZE_160K           ((uint32_t)0x0000000AU)                            /*!< HSM bank size is 160K */
#define HSM_BANK_SIZE_176K           ((uint32_t)0x0000000BU)                            /*!< HSM bank size is 176K */
#define HSM_BANK_SIZE_192K           ((uint32_t)0x0000000CU)                            /*!< HSM bank size is 192K */
#define HSM_BANK_SIZE_208K           ((uint32_t)0x0000000DU)                            /*!< HSM bank size is 208K */
#define HSM_BANK_SIZE_224K           ((uint32_t)0x0000000EU)                            /*!< HSM bank size is 224K */
#define HSM_BANK_SIZE_240K           ((uint32_t)0x0000000FU)                            /*!< HSM bank size is 240K */
#define HSM_BANK_SIZE_256K           ((uint32_t)0x00000010U)                            /*!< HSM bank size is 256K */

/* the master ID */
#define CTL_MASTERID(regval)         (BITS(20,23) & ((uint32_t)(regval) << 20))
#define CTL_MASTERID_AXIM_CM7_0      CTL_MASTERID(0U)                                   /*!< AXIM_CM7_0 */
#define CTL_MASTERID_AXIM_CM7_1      CTL_MASTERID(1U)                                   /*!< AXIM_CM7_1 */
#define CTL_MASTERID_DMA0_MEM        CTL_MASTERID(2U)                                   /*!< DMA0_MEM */
#define CTL_MASTERID_DMA1_MEM        CTL_MASTERID(3U)                                   /*!< DMA1_MEM */
#define CTL_MASTERID_HSM_CM23        CTL_MASTERID(4U)                                   /*!< HSM */
#define CTL_MASTERID_ENET            CTL_MASTERID(5U)                                   /*!< ENET_CM23 */
#define CTL_MASTERID_AHBP_CM7_1      CTL_MASTERID(7U)                                   /*!< AHBP_CM7_1 */
#define CTL_MASTERID_DMA0_PERIPH     CTL_MASTERID(10U)                                  /*!< DMA0_PERIPH */
#define CTL_MASTERID_DMA1_PERIPH     CTL_MASTERID(11U)                                  /*!< DMA1_PERIPH */
#define CTL_MASTERID_HSM_DMA         CTL_MASTERID(12U)                                  /*!< HSM_DMA */
#define CTL_MASTERID_AHBP_CM7_0      CTL_MASTERID(14U)                                  /*!< AHBP_CM7_0 */

#define FMC_BLKECCCS(blockx)         REG32((FMC) + 0x60U + 0x100U * (uint32_t)(blockx)) /*!< FMC block x ECC control and status register */
#define FMC_BLKUCECCADDR(blockx)     REG32((FMC) + 0x64U + 0x100U * (uint32_t)(blockx)) /*!< FMC block x UCECC address register */
#define FMC_BLKCECCADDR0(blockx)     REG32((FMC) + 0x68U + 0x100U * (uint32_t)(blockx)) /*!< FMC block x CECC address0 register */
#define FMC_BLKCECCADDR1(blockx)     REG32((FMC) + 0x6CU + 0x100U * (uint32_t)(blockx)) /*!< FMC block x CECC address1 register */
#define FMC_BLKCECCADDR2(blockx)     REG32((FMC) + 0x70U + 0x100U * (uint32_t)(blockx)) /*!< FMC block x CECC address2 register */
#define FMC_BLKCECCADDR3(blockx)     REG32((FMC) + 0x74U + 0x100U * (uint32_t)(blockx)) /*!< FMC block x CECC address3 register */

#define FMC_BUFECCCS(bufx)           REG32((FMC) + 0x80U + 0x100U * (uint32_t)(bufx))   /*!< FMC buffer x control register */
#define FMC_BUFUCECCADDR(bufx)       REG32((FMC) + 0x84U + 0x100U * (uint32_t)(bufx))   /*!< FMC buffer x UCECC address register */
#define FMC_BUFCECCADDR0(bufx)       REG32((FMC) + 0x88U + 0x100U * (uint32_t)(bufx))   /*!< FMC buffer x correct ECC address0 register */
#define FMC_BUFCECCADDR1(bufx)       REG32((FMC) + 0x8CU + 0x100U * (uint32_t)(bufx))   /*!< FMC buffer x correct ECC address1 register */
#define FMC_BUFCECCADDR2(bufx)       REG32((FMC) + 0x90U + 0x100U * (uint32_t)(bufx))   /*!< FMC buffer x correct ECC address2 register */
#define FMC_BUFCECCADDR3(bufx)       REG32((FMC) + 0x94U + 0x100U * (uint32_t)(bufx))   /*!< FMC buffer x correct ECC address3 register */

/* option bytes security protection level in FMC_OBSTAT register */
#define OB_OBSTAT_PLEVEL_NO          ((uint8_t)0x00U)                                   /*!< no security protection */
#define OB_OBSTAT_PLEVEL_LOW         ((uint8_t)0x01U)                                   /*!< low security protection */
#define OB_OBSTAT_PLEVEL_HIGH        ((uint8_t)0x03U)                                   /*!< high security protection */

/* option bytes security protection configuration */
#define FMC_NSPC                     ((uint16_t)0x5AA5U)                                /*!< no security protection */
#define FMC_LSPC                     ((uint16_t)0x44BBU)                                /*!< low security protection, any value except 0xA5 or 0xCC */
#define FMC_HSPC                     ((uint16_t)0x33CCU)                                /*!< high security protection */

/* option bytes software/hardware free watchdog timer0 */
#define OB_FWDGT0_HW                 ((uint16_t)0x0100U)                                /*!< hardware free watchdog timer0 */
#define OB_FWDGT0_SW                 ((uint16_t)0x0001U)                                /*!< software free watchdog timer0 */

/* option bytes reset or not entering standby mode */
#define OB_STDBY_RST                 ((uint16_t)0x0400U)                                /*!< generate a reset instead of entering standby mode */
#define OB_STDBY_NRST                ((uint16_t)0x0004U)                                /*!< no reset when entering standby mode */

/* option bytes software/hardware free watchdog timer1 */
#define OB_FWDGT1_HW                 ((uint16_t)0x2000U)                                /*!< hardware free watchdog timer1 */
#define OB_FWDGT1_SW                 ((uint16_t)0x0020U)                                /*!< software free watchdog timer1 */

/* option bytes free watchdog 0/1 stop or continue counting in standby mode */
#define OB_FWDG_STDBY_STOP           ((uint16_t)0x4000U)                                /*!< free watchdog 0/1 stop counting in standby mode */
#define OB_FWDG_STDBY_CONT           ((uint16_t)0x0040U)                                /*!< free watchdog 0/1 continue counting in standby */

/* HSM option bytes security protection configuration */
#define HSM_NSPC                     ((uint16_t)0x5AA5U)                                /*!< no security protection */
#define HSM_LSPC                     ((uint16_t)0x44BBU)                                /*!< low security protection, any value except 0xA5 or 0xCC */
#define HSM_HSPC                     ((uint16_t)0x33CCU)                                /*!< high security protection */

/* HSM option bytes security protection level in FMC_HSMOBSTAT register */
#define HSM_OBSTAT_PLEVEL_NO          ((uint8_t)0x00U)                                  /*!< no security protection */
#define HSM_OBSTAT_PLEVEL_LOW         ((uint8_t)0x01U)                                  /*!< low security protection */
#define HSM_OBSTAT_PLEVEL_HIGH        ((uint8_t)0x03U)                                  /*!< high security protection */

/* HSM option bytes swap configuration */
#define HSM_OB_SWAP_PFLASH0          ((uint16_t)0x8000U)                                /*!< bank0 and HSM bank 0 at Pflash0, bank1 and HSM bank 1 at Pflash1 */
#define HSM_OB_SWAP_PFLASH1          ((uint16_t)0x0080U)                                /*!< bank0 and HSM bank 0 at Pflash1, bank1 and HSM bank 1 at Pflash0 */

/* HSM option bytes HSM watchdog configuration */
#define HSM_OB_WWDG_HW               ((uint16_t)0x4000U)                                /*!< hardware HSM watchdog */
#define HSM_OB_WWDG_SW               ((uint16_t)0x0040U)                                /*!< software HSM watchdog */

#define BANK0_BASE_ADDRESS           ((uint32_t)0x08000000U)                            /*!< FMC bank0 base address */
#define HSM_BANK0_ADDRESS            ((uint32_t)0x08440000U)                            /*!< FMC HSM code0 address */
#define HSM_BANK0_MAX_SIZE           ((uint32_t)0x00040000U)                            /*!< FMC HSM code0 max size */
#define HSM_BANK1_ADDRESS            ((uint32_t)0x08480000U)                            /*!< FMC HSM code0 address */
#define HSM_BANK1_MAX_SIZE           ((uint32_t)0x00040000U)                            /*!< FMC HSM code0 max size */
#define HOST_DATA_BASE_ADDRESS       ((uint32_t)0x08800000U)                            /*!< FMC dflash0 base address */
#define HOST_DATA_SIZE               ((uint32_t)0x00020000U)                            /*!< FMC HOST data size */
#define HSM_DATA_BASE_ADDRESS        ((uint32_t)0x08880000U)                            /*!< FMC HSM data base address */
#define HSM_DATA_SIZE                ((uint32_t)0x00018000U)                            /*!< FMC HSM data size */
#define SBAF_BASE_ADDRESS            ((uint32_t)0x08400000U)                            /*!< FMC sBAF base address */
#define SBAF_SIZE                    ((uint32_t)0x00008000U)                            /*!< FMC sBAF size */

#define OTP_BASE_ADDRESS             ((uint32_t)0x1FFF7000U)                            /*!< FMC OTP base address */
#define OTP_SIZE                     ((uint32_t)0x00000800U)                            /*!< FMC OTP size */
#define HSM_OTP_BASE_ADDRESS         ((uint32_t)0x1FFFF900U)                            /*!< FMC HSM OTP base address */
#define HSM_OTP_SIZE                 ((uint32_t)0x000000E8U)                            /*!< FMC HSM OTP size */

#define OB_WORD_CNT                  ((uint8_t)0x0EU)                                   /*!< word count of HOST option bytes */
#define OB_DOUBLEWORD_CNT            ((uint8_t)0x07U)                                   /*!< double-word count of HOST option bytes */
#define HSM_OB_WORD_CNT              ((uint8_t)0x02U)                                   /*!< word count of HSM option bytes */
#define HSM_OB_DOUBLEWORD_CNT        ((uint8_t)0x01U)                                   /*!< double-word count of HSM option bytes */

#define FMC_TIMEOUT_COUNT            ((uint32_t)0xFFFF0000U)                            /*!< count to judge of FMC timeout */
#define DOUBLEWORD_CNT_IN_ROW        ((uint8_t)0x40U)                                   /*!< double-word count in one row data */
#define CBCMDLEN_OF_ONE_ROW          ((uint8_t)0x05U)                                   /*!< CBCMD read length of one row data */

/* LC address definition */
#define LC_MARKED                    ((uint64_t)0x55AA50AF55AA50AFU)                    /*!< LC marked value */
#define LC_ERASED                    ((uint64_t)0xFFFFFFFFFFFFFFFFU)                    /*!< LC erased value */
#define LC_SLOT_SIZE                 ((uint32_t)0x0000000FU)                            /*!< FMC HSM OTP size */
#define LC_SLOT0_BASE_ADDRESS        ((uint32_t)0x1FFFF900U)                            /*!< FMC LC slot0 base address */
#define LC_SLOT1_BASE_ADDRESS        ((uint32_t)0x1FFFF910U)                            /*!< FMC LC slot1 base address */
#define LC_SLOT2_BASE_ADDRESS        ((uint32_t)0x1FFFF920U)                            /*!< FMC LC slot2 base address */
#define LC_SLOT3_BASE_ADDRESS        ((uint32_t)0x1FFFF930U)                            /*!< FMC LC slot3 base address */
#define LC_SLOT4_BASE_ADDRESS        ((uint32_t)0x1FFFF940U)                            /*!< FMC LC slot4 base address */
#define LC_IN_FIELD_RECOVER_MODE     ((uint32_t)0x1FFFF950U)                            /*!< FMC LC IN_FIELD_RECOVER_MODE base address */

/* APP DBG */
#define HOST_DBG_DISABLE_ADDRESS     ((uint32_t)0x1FFFF958U)                            /*!< HOST dbg base address */
#define HSM_DBG_DISABLE_ADDRESS      ((uint32_t)0x1FFFF960U)                            /*!< HSM dbg base address */

/* HOST/HSM password address definition */
#define HOST_DBG_PASSWORD_ADDRESS    ((uint32_t)0x1FFFF968U)                            /*!< HOST password base address */
#define HSM_DBG_PASSWORD_ADDRESS     ((uint32_t)0x1FFFF978U)                            /*!< HSM password base address */

/* CRYP key address definition */
#define CRYP_KEY1_BASE_ADDRESS       ((uint32_t)0x1FFFF988U)                            /*!< FMC CRYP KEY1 base address */
#define CRYP_KEY2_BASE_ADDRESS       ((uint32_t)0x1FFFF9A8U)                            /*!< FMC CRYP KEY2 base address */

/* SPC key address definition */
#define SPC_KEY_BASE_ADDRESS         ((uint32_t)0x1FFFF9C8U)                            /*!< SPC key base address */

/* HSM SIZE address */
#define HSM_SIZE_ADDRESS             ((uint32_t)0x1FFFF9D8U)                            /*!< HSM SIZE base address */

/* HSM SEC address */
#define HSM_SEC_ADDRESS              ((uint32_t)0x1FFFF9E0U)                            /*!< HSM SEC base address */

/*!< HOST option bytes user bits */
#define FMC_OBSTAT_USER              BITS(8,15)                                         /*!< HOST option bytes user bits */

/*!< HOST option bytes cltcfg bits */
#define FMC_OB_CLTCFG_RSTPIN_MOD         BIT(0)                                         /*!< reset pin mode */
#define FMC_OB_CLTCFG_FFIOMOD            BIT(1)                                         /*!< configuration of the fatal fault pins mode */
#define FMC_OB_CLTCFG_PWDGEN             BIT(7)                                         /*!< POR watchdog enable */
#define FMC_OB_CLTCFG_FMU_REA_FAIL_UEN   BIT(11)                                        /*!< FMU react failed upgrade enable */
#define FMC_OB_CLTCFG_STCM_REC_FAIL_UEN  BIT(12)                                        /*!< STCM recover failed upgrade enable */
#define FMC_OB_CLTCFG_RCTL_SUBSRU_UEN    BIT(14)                                        /*!< subsystem reset upgrade enable */
#define FMC_OB_CLTCFG_LOHRST_UEN         BIT(16)                                        /*!< loss of HXTAL error upgrade enable */
#define FMC_OB_CLTCFG_LOPRST_UEN         BIT(17)                                        /*!< loss of PLL error upgrade enable */
#define FMC_OB_CLTCFG_HSM_SYS_RST_UEN    BIT(26)                                        /*!< HSM system reset detection upgrade enable */
#define FMC_OB_CLTCFG_SW_SYS_RST_UEN     BIT(37)                                        /*!< software system reset upgrade enable */
#define FMC_OB_CLTCFG_DBG_SYS_RST_UEN    BIT(38)                                        /*!< debug system reset upgrade enable */

/*!< ECCCORx clear bit  */
#define FMC_ECCCOR_CLEAR                 BIT(20)                                        /*!< ECCCORx clear bit */
#define FMC_PID_0                        (0U)                                           /*!< PID0 index */
#define FMC_PID_1                        (1U)                                           /*!< PID1 index */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check wait state counter value */
#define NOT_FMC_WS_WSCNT(wscnt)                                 (((wscnt) != WS_WSCNT_0) && ((wscnt) != WS_WSCNT_1) && \
                                                                 ((wscnt) != WS_WSCNT_2) && ((wscnt) != WS_WSCNT_3) && \
                                                                 ((wscnt) != WS_WSCNT_4) && ((wscnt) != WS_WSCNT_5))
/* check buffer number index */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_FMC_BUFFER_INDEX(index)                             (((index) != FMC_BUFF_0) && ((index) != FMC_BUFF_1) && \
                                                                 ((index) != FMC_BUFF_2) && ((index) != FMC_BUFF_3))
#else
#define NOT_FMC_BUFFER_INDEX(index)                             (((index) != FMC_BUFF_0) && ((index) != FMC_BUFF_2) && \
                                                                 ((index) != FMC_BUFF_3))
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
/* check interface 0 address */
#define NOT_FMC_VALID_INTERFACE0_ADDRESS(address)               (((address) < 0x08000000U) || (((address) < 0X08440000U) && (address) > 0x08400000U) || \
                                                                 (((address) < 0x08800000U) && (address) > 0x084BFFFFU) || ((address) > 0x0881FFFFU))
/* check interface 0 OPT address */
#define NOT_FMC_VALID_INTERFACE0_OTP_ADDRESS(address)           ((((address) < 0x1FFF7000U) || (address) > 0x1FFF77FFU))

/* check check blank address configuration */
#define NOT_FMC_VALID_BLANK_ADDRESS_CONFIG(address, length)     ((((address)%0x800U) + (((uint32_t)1U << ((length) + 4U)))) > 0x800U)
/* check HOST flash area */
#define NOT_FMC_HOST_AREA(area)                                 (((area) != BANK0_AREA) && ((area) != BANK1_AREA) && \
                                                                 ((area) != DATA_FLASH_AREA))
/* check interface 1 OPT address */
#define NOT_FMC_VALID_INTERFACE1_OTP_ADDRESS(address)           ((((address) < 0x1FFFF900U) || (address) > 0x1FFFF9E7U))
/* check interface 1 data flash address */
#define NOT_FMC_VALID_INTERFACE1_DATA_FLASH_ADDRESS(address)    ((((address) < 0x08880000U) || (address) > 0x08897FFFU))
/* check LC slot address */
#define NOT_FMC_LC_SLOT_ADDRESS(address)                        (((address) != LC_SLOT0_BASE_ADDRESS) && ((address) != LC_SLOT1_BASE_ADDRESS) && \
                                                                 ((address) != LC_SLOT2_BASE_ADDRESS) && ((address) != LC_SLOT3_BASE_ADDRESS) && \
                                                                 ((address) != LC_SLOT4_BASE_ADDRESS) && ((address) != LC_IN_FIELD_RECOVER_MODE))
/* check debug password address */
#define NOT_FMC_DBG_PASSWORD_ADDRESS(address)                   (((address) != HOST_DBG_PASSWORD_ADDRESS) && ((address) != HSM_DBG_PASSWORD_ADDRESS))
/* check HSM cryp key address */
#define NOT_FMC_CRYP_KEY_ADDRESS(address)                       (((address) != CRYP_KEY1_BASE_ADDRESS) && ((address) != CRYP_KEY2_BASE_ADDRESS))
/* check HSM cryp key address */
#define NOT_FMC_HSM_BANK_SIZE(hsm_size)                         (((hsm_size) > 0x10U))
/* check security protection value */
#define NOT_FMC_SPC_VALUE(ob_spc)                               (((ob_spc) != FMC_NSPC) && ((ob_spc) != FMC_LSPC) && ((ob_spc) != FMC_HSPC))
/* check HSM flash area */
#define NOT_FMC_HSM_AREA(area)                                  (((area) != HSM_BANK_AREA) && ((area) != HSM_DATA_AREA))
/* check HSM security protection value */
#define NOT_FMC_HSM_SPC_VALUE(ob_hsmspc)                        (((ob_hsmspc) != HSM_NSPC) && ((ob_hsmspc) != HSM_LSPC) && ((ob_hsmspc) != HSM_HSPC))
/* check HSM SWAP option bytes */
#define NOT_FMC_HSM_SWAP_VALUE(hsmob_swap)                      (((hsmob_swap) != HSM_OB_SWAP_PFLASH0) && ((hsmob_swap) != HSM_OB_SWAP_PFLASH1))
/* check HSM window watchdog option bytes */
#define NOT_FMC_HSM_WWDG_VALUE(hsmob_wwdg)                      (((hsmob_wwdg) != HSM_OB_WWDG_HW) && ((hsmob_wwdg) != HSM_OB_WWDG_SW))
/* check HSM HSMUSER option bytes */
#define FMC_HSM_HSMUSER_VALUE_HIGH                               (0x3FU)
#define NOT_FMC_HSM_HSMUSER_VALUE(hsmob_user)                    (FMC_HSM_HSMUSER_VALUE_HIGH < (hsmob_user))
/* check FMC flag */
#define NOT_FMC_FLAG(flag)                                      (((flag) != FMC_STAT0_FLAG_BUSY)      && ((flag) != FMC_STAT0_FLAG_PGSERR) && \
                                                                 ((flag) != FMC_STAT0_FLAG_PGERR)     && ((flag) != FMC_STAT0_FLAG_WPERR) && \
                                                                 ((flag) != FMC_STAT0_FLAG_END)       && ((flag) != FMC_STAT0_FLAG_CBCMDERR) && \
                                                                 ((flag) != FMC_STAT0_FLAG_LOADECCERR) && ((flag) != FMC_STAT0_FLAG_COMPERR) && \
                                                                 ((flag) != FMC_STAT0_FLAG_TMRERR)    && ((flag) != FMC_STAT0_FLAG_RSTERR) && \
                                                                 ((flag) != FMC_STAT1_FLAG_BUSY)      && ((flag) != FMC_STAT1_FLAG_PGSERR) && \
                                                                 ((flag) != FMC_STAT1_FLAG_PGERR)     && ((flag) != FMC_STAT1_FLAG_WPERR) && \
                                                                 ((flag) != FMC_STAT1_FLAG_END)       && ((flag) != FMC_STAT1_FLAG_CBCMDERR) && \
                                                                 ((flag) != FMC_STAT1_FLAG_TMRERR)    && ((flag) != FMC_STAT1_FLAG_RSTERR) && \
                                                                 ((flag) != FMC_FLAG_OBERR)           && ((flag) != FMC_FLAG_HSMOBERR))
/* check FMC clear flag */
#define NOT_FMC_CLEAR_FLAG(flag)                                 (((flag) != FMC_STAT0_FLAG_PGSERR)   && ((flag) != FMC_STAT0_FLAG_PGERR) && \
                                                                  ((flag) != FMC_STAT0_FLAG_WPERR)    && ((flag) != FMC_STAT0_FLAG_END) && \
                                                                  ((flag) != FMC_STAT0_FLAG_CBCMDERR) && ((flag) != FMC_STAT0_FLAG_LOADECCERR) && \
                                                                  ((flag) != FMC_STAT0_FLAG_COMPERR)  && ((flag) != FMC_STAT0_FLAG_RSTERR)&& \
                                                                  ((flag) != FMC_STAT1_FLAG_PGSERR)   && ((flag) != FMC_STAT1_FLAG_PGERR) && \
                                                                  ((flag) != FMC_STAT1_FLAG_WPERR)    && ((flag) != FMC_STAT1_FLAG_END) && \
                                                                  ((flag) != FMC_STAT1_FLAG_CBCMDERR) && ((flag) != FMC_STAT1_FLAG_RSTERR))
/* check FMC interrupt */
#define NOT_FMC_INT(interrupt)                                   (((interrupt) != FMC_CTL0_INT_ERR) && ((interrupt) != FMC_CTL0_INT_END) && \
                                                                  ((interrupt) != FMC_CTL1_INT_ERR) && ((interrupt) != FMC_CTL1_INT_END))
/* check FMC interrupt flag */
#define NOT_FMC_INT_FLAG(int_flag)                               (((int_flag) != FMC_STAT0_INT_FLAG_PGSERR)   && ((int_flag) != FMC_STAT0_INT_FLAG_PGERR) && \
                                                                  ((int_flag) != FMC_STAT0_INT_FLAG_WPERR)    && ((int_flag) != FMC_STAT0_INT_FLAG_END) && \
                                                                  ((int_flag) != FMC_STAT0_INT_FLAG_CBCMDERR) && ((int_flag) != FMC_STAT0_INT_FLAG_RSTERR) && \
                                                                  ((int_flag) != FMC_STAT1_INT_FLAG_PGSERR)   && ((int_flag) != FMC_STAT1_INT_FLAG_PGERR) && \
                                                                  ((int_flag) != FMC_STAT1_INT_FLAG_WPERR)    && ((int_flag) != FMC_STAT1_INT_FLAG_END) && \
                                                                  ((int_flag) != FMC_STAT1_INT_FLAG_CBCMDERR) && ((int_flag) != FMC_STAT1_INT_FLAG_RSTERR))

/* check FMC interrupt clear flag */
#define NOT_FMC_INT_CLEAR_FLAG(int_flag)                          (((int_flag) != FMC_STAT0_INT_FLAG_PGSERR)  && ((int_flag) != FMC_STAT0_INT_FLAG_PGERR) && \
                                                                   ((int_flag) != FMC_STAT0_INT_FLAG_WPERR)    && ((int_flag) != FMC_STAT0_INT_FLAG_END) && \
                                                                   ((int_flag) != FMC_STAT0_INT_FLAG_CBCMDERR) && ((int_flag) != FMC_STAT0_INT_FLAG_COMPERR) && \
                                                                   ((int_flag) != FMC_STAT0_INT_FLAG_RSTERR)   && ((int_flag) != FMC_STAT1_INT_FLAG_PGSERR) && \
                                                                   ((int_flag) != FMC_STAT1_INT_FLAG_PGERR)    && ((int_flag) != FMC_STAT1_INT_FLAG_WPERR) && \
                                                                   ((int_flag) != FMC_STAT1_INT_FLAG_END)      && ((int_flag) != FMC_STAT1_INT_FLAG_CBCMDERR) && \
                                                                   ((int_flag) != FMC_STAT1_INT_FLAG_RSTERR))

/* check FMC ECC flag */
#define NOT_FMC_ECC_FLAG(ecc_flag)                               (((ecc_flag) != FMC_BLKFLAG_ECCCOR0)  && ((ecc_flag) != FMC_BLKFLAG_ECCCOR1) && \
                                                                  ((ecc_flag) != FMC_BLKFLAG_ECCCOR2)  && ((ecc_flag) != FMC_BLKFLAG_ECCCOR3) && \
                                                                  ((ecc_flag) != FMC_BLKFLAG_ECCAERR)  && ((ecc_flag) != FMC_BLKFLAG_ECCCOROV) && \
                                                                  ((ecc_flag) != FMC_BLKFLAG_ECCEDC)   && ((ecc_flag) != FMC_BLKFLAG_ECCDET) && \
                                                                  ((ecc_flag) != FMC_BUFFLAG_ECCCOR0)  && ((ecc_flag) != FMC_BUFFLAG_ECCCOR1) && \
                                                                  ((ecc_flag) != FMC_BUFFLAG_ECCCOR2)  && ((ecc_flag) != FMC_BUFFLAG_ECCCOR3) && \
                                                                  ((ecc_flag) != FMC_BUFFLAG_ECCAERR)  && ((ecc_flag) != FMC_BUFFLAG_ECCCOROV) && \
                                                                  ((ecc_flag) != FMC_BUFFLAG_ECCEDC)   && ((ecc_flag) != FMC_BUFFLAG_ECCDET) && \
                                                                  ((ecc_flag) != FMC_FPBFLAG_ECCCOR0)  && ((ecc_flag) != FMC_FPBFLAG_ECCCOR1) && \
                                                                  ((ecc_flag) != FMC_FPBFLAG_ECCCOR2)  && ((ecc_flag) != FMC_FPBFLAG_ECCCOR3) && \
                                                                  ((ecc_flag) != FMC_FPBFLAG_ECCAERR)  && ((ecc_flag) != FMC_FPBFLAG_ECCCOROV) && \
                                                                  ((ecc_flag) != FMC_FPBFLAG_ECCEDC)   &&((ecc_flag) != FMC_FPBFLAG_ECCDET))

/* check FMC register number flag */
#define NOT_FMC_REG_NUM(reg_num)                                  (((reg_num) != FMC_REG_0) && ((reg_num) != FMC_REG_1) && \
                                                                   ((reg_num) != FMC_REG_2) && ((reg_num) != FMC_REG_3))
/* check FMC ECC interrupt */
#define NOT_FMC_ECC_INT(interrupt)                                (((interrupt) != FMC_BLK_INT_ECCCOR)  && ((interrupt) != FMC_BLK_INT_ECCDET) && \
                                                                   ((interrupt) != FMC_BLK_INT_ECCCORV) && ((interrupt) != FMC_BUF_INT_ECCCOR) && \
                                                                   ((interrupt) != FMC_BUF_INT_ECCDET)  && ((interrupt) != FMC_BUF_INT_ECCCORV) && \
                                                                   ((interrupt) != FMC_FPB_INT_ECCCOR) && ((interrupt) != FMC_FPB_INT_ECCDET)  && \
                                                                   ((interrupt) != FMC_FPB_INT_ECCCORV))
/* check FMC ECC interrupt flag */
#define NOT_FMC_ECC_INT_FLAG(ecc_int_flag)                        (((ecc_int_flag) != FMC_BLK_INT_FLAG_ECCCOR0)  && ((ecc_int_flag) != FMC_BLK_INT_FLAG_ECCCOR1) && \
                                                                   ((ecc_int_flag) != FMC_BLK_INT_FLAG_ECCCOR2)  && ((ecc_int_flag) != FMC_BLK_INT_FLAG_ECCCOR3) && \
                                                                   ((ecc_int_flag) != FMC_BLK_INT_FLAG_ECCAERR)  && ((ecc_int_flag) != FMC_BLK_INT_FLAG_ECCCOROV) && \
                                                                   ((ecc_int_flag) != FMC_BLK_INT_FLAG_ECCEDC)   && ((ecc_int_flag) != FMC_BLK_INT_FLAG_ECCDET) && \
                                                                   ((ecc_int_flag) != FMC_BUF_INT_FLAG_ECCCOR0)  && ((ecc_int_flag) != FMC_BUF_INT_FLAG_ECCCOR1) && \
                                                                   ((ecc_int_flag) != FMC_BUF_INT_FLAG_ECCCOR2)  && ((ecc_int_flag) != FMC_BUF_INT_FLAG_ECCCOR3) && \
                                                                   ((ecc_int_flag) != FMC_BUF_INT_FLAG_ECCAERR)  && ((ecc_int_flag) != FMC_BUF_INT_FLAG_ECCCOROV) && \
                                                                   ((ecc_int_flag) != FMC_BUF_INT_FLAG_ECCEDC)   && ((ecc_int_flag) != FMC_BUF_INT_FLAG_ECCDET) && \
                                                                   ((ecc_int_flag) != FMC_FPB_INT_FLAG_ECCCOR0)  && ((ecc_int_flag) != FMC_FPB_INT_FLAG_ECCCOR1) && \
                                                                   ((ecc_int_flag) != FMC_FPB_INT_FLAG_ECCCOR2)  && ((ecc_int_flag) != FMC_FPB_INT_FLAG_ECCCOR3) && \
                                                                   ((ecc_int_flag) != FMC_FPB_INT_FLAG_ECCAERR)  && ((ecc_int_flag) != FMC_FPB_INT_FLAG_ECCCOROV) && \
                                                                   ((ecc_int_flag) != FMC_FPB_INT_FLAG_ECCEDC)   && ((ecc_int_flag) != FMC_FPB_INT_FLAG_ECCDET))
/* check FMC correctable ECC address  */
#define NOT_CECC_ADDR(cecc_addr)                                  (((cecc_addr) != CECC_ADDR0) && ((cecc_addr) != CECC_ADDR1) && \
                                                                   ((cecc_addr) != CECC_ADDR2) && ((cecc_addr) != CECC_ADDR3))
/* check FMC PID index */
#define NOT_FMC_PID_INDEX(pidx)                                   (((pidx) != FMC_PID_0) && ((pidx) != FMC_PID_1))
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* FMC programming functions */
/* unlock the control register 0/1 operation */
void fmc_unlock(void);
/* unlock the control register 0 operation */
void fmc_ctl0_unlock(void);
/* unlock the control register 1 operation */
void fmc_ctl1_unlock(void);
/* lock the control register 0/1 operation */
void fmc_lock(void);
/* lock the control register 0 operation */
void fmc_ctl0_lock(void);
/* lock the control register 1 operation */
void fmc_ctl1_lock(void);

/* set the wait state counter value */
void fmc_wscnt_set(uint8_t wscnt);
/* enable buffer x */
void fmc_buffer_enable(fmc_buff_enum index);
/* disable buffer x */
void fmc_buffer_disable(fmc_buff_enum index);
/* enable buffer x read code buffers */
void fmc_code_current_buffer_enable(fmc_buff_enum index);
/* disable buffer x read code buffers */
void fmc_code_current_buffer_disable(fmc_buff_enum index);
/* enable buffer x read data buffers */
void fmc_data_current_buffer_enable(fmc_buff_enum index);
/* disable buffer x read data buffers */
void fmc_data_current_buffer_disable(fmc_buff_enum index);
/* enable buffer x code prefetch */
void fmc_code_prefetch_buffer_enable(fmc_buff_enum index);
/* disable buffer x code prefetch */
void fmc_code_prefetch_buffer_disable(fmc_buff_enum index);
/* enable buffer x data prefetch */
void fmc_data_prefetch_buffer_enable(fmc_buff_enum index);
/* disable buffer x data prefetch */
void fmc_data_prefetch_buffer_disable(fmc_buff_enum index);

/* FMC HOST */
/* check whether area in bank0/bank1/data flash page is blank or not by check blank command */
fmc_state_enum fmc_blank_check(uint32_t address, uint8_t length);
/* get base address of bank0 */
uint32_t fmc_bank0_base_address_get(void);
/* get base address of bank1 */
uint32_t fmc_bank1_base_address_get(void);
/* erase bank0/bank1/data flash page */
fmc_state_enum fmc_page_erase(uint32_t page_address);
/* mass erase bank0/bank1/data flash */
fmc_state_enum fmc_mass_erase(fmc_area_enum area);
/* program a double word at the corresponding address in bank0 / bank1 / data flash */
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data);
/* fast program one row data (64 double-word) starting at the corresponding address in bank0 / bank1 / data flash */
fmc_state_enum fmc_fast_program(uint32_t address, uint64_t data[]);
/* program a double word at the corresponding address in OTP */
fmc_state_enum fmc_otp_doubleword_program(uint32_t address, uint64_t data);
/* bank0 / bank1 size get */
uint32_t fmc_bank_size_get(void);

/* FMC HSM */
/* check whether area in HSM data flash page is blank or not by check blank command */
fmc_state_enum fmc_hsm_data_blank_check(uint32_t address, uint8_t length);
/* get base address of HSM bank 0 */
uint32_t fmc_hsm_bank0_address_get(void);
/* get base address of HSM bank 1 */
uint32_t fmc_hsm_bank1_address_get(void);
/* erase HSM bank page */
fmc_state_enum fmc_hsm_bank_page_erase(uint32_t page_address);
/* program a double word at the corresponding address in HSM bank0 / bank1 flash */
fmc_state_enum fmc_hsm_bank_doubleword_program(uint32_t address, uint64_t data);
/* fast program one row data (64 double-word) starting at the corresponding address in HSM bank0 / bank1 flash */
fmc_state_enum fmc_hsm_bank_fast_program(uint32_t address, uint64_t data[]);
/* HSM erase data flash page */
fmc_state_enum fmc_hsm_data_page_erase(uint32_t page_address);
/* program a double word at the corresponding address in HSM data flash */
fmc_state_enum fmc_hsm_data_doubleword_program(uint32_t address, uint64_t data);
/* HSM fast program one row data (64 double-word) starting at the corresponding address */
fmc_state_enum fmc_hsm_data_fast_program(uint32_t address, uint64_t data[]);
/* program a double word at the corresponding address in HSM OTP */
fmc_state_enum hsm_otp_doubleword_program(uint32_t address, uint64_t data);
/* HSM system mark LC slot valid field */
fmc_state_enum hsm_lc_valid_mark(uint32_t address);
/* HSM system mark LC slot invalid field */
fmc_state_enum hsm_lc_invalid_mark(uint32_t address);
/* HOST dbg disable */
fmc_state_enum hsm_host_dbg_disable(void);
/* HSM dbg disable */
fmc_state_enum hsm_hsm_dbg_disable(void);
/* HOST / HSM debug password configuration in HSM OTP */
fmc_state_enum hsm_debug_password_config(uint32_t address, uint64_t data[]);
/* HSM cryp key configuration in HSM OTP */
fmc_state_enum hsm_cryp_key_config(uint32_t address, uint64_t data[]);
/* HSM SPC key configuration in HSM OTP */
fmc_state_enum hsm_spc_key_config(uint64_t data[]);
/* unlock SPC protection with SPC key */
void spc_unlock(uint32_t key[]);
/* configure HSM bank0 / bank1 size */
fmc_state_enum hsm_bank_size_config(uint64_t hsm_size);
/* HSM security enable */
fmc_state_enum hsm_sec_enable(void);
/* HSM factory test mode disable */
fmc_state_enum hsm_factory_disable(void);
/* HSM bank0 / bank1 size get */
uint32_t hsm_bank_size_get(void);

/* FMC option bytes functions */
/* force to reload the HOST and HSM option bytes */
void ob_reset(void);
/* erase the HOST option bytes */
fmc_state_enum ob_erase(void);
/* configure HOST option bytes write protection */
fmc_state_enum ob_write_protection_config(fmc_area_enum wp_area, uint32_t ob_wp);
/* configure HOST system security protection */
fmc_state_enum ob_security_protection_config(uint16_t ob_spc);
/* program the user HOST option bytes */
fmc_state_enum ob_user_write(uint16_t ob_user);
/* program the data HOST option bytes */
fmc_state_enum ob_data_program(uint16_t ob_data);
/* program the cltcfg HOST option bytes */
fmc_state_enum ob_cltcfg_config(uint64_t ob_cltcfg);
/* get the value of FMC option bytes OB_USER in FMC_OBSTAT register */
uint8_t ob_user_get(void);
/* get the value of FMC option bytes OB_DATA in FMC_OBSTAT register */
uint16_t ob_data_get(void);
/* get the value of FMC option bytes BK0WP in FMC_WP0 register */
uint32_t ob_bk0_write_protection_get(void);
/* get the value of FMC option bytes BK1WP in FMC_WP1 register */
uint32_t ob_bk1_write_protection_get(void);
/* get the value of FMC option bytes DFWP in FMC_WP2 register */
uint8_t ob_df_write_protection_get(void);
/* get the value of FMC option bytes security protection level (PLEVEL) in FMC_OBSTAT register */
uint8_t ob_plevel_get(void);

/* FMC HSM option bytes functions */
/* erase the HSM option bytes */
fmc_state_enum hsm_ob_erase(void);
/* initialize the hsm option bytes parameters struct with the default values */
void hsm_ob_para_struct_init(fmc_hsm_opt_parameter_struct *init_struct);
/* configure HSM option bytes */
fmc_state_enum hsm_ob_config(fmc_hsm_opt_parameter_struct *hsmob);
/* configure HSM option bytes write protection */
fmc_state_enum hsm_ob_write_protection_config(fmc_area_enum wp_area, uint8_t ob_hsmwp);
/* configure security protection in HSM option bytes */
fmc_state_enum hsm_ob_security_protection_config(uint16_t ob_hsmspc);
/* configure swap in HSM option bytes */
fmc_state_enum hsm_ob_swap_config(uint16_t hsmob_swap);
/* configure window watchdog in HSM option bytes */
fmc_state_enum hsm_ob_wwdg_config(uint16_t hsmob_wwdg);
/* program the user data in HSM option bytes */
fmc_state_enum hsm_ob_user_write(uint8_t hsmob_user);
/* get the value of FMC HSM option bytes HSMPFWP in FMC_HSMWP register */
uint8_t hsm_ob_pflash_write_protection_get(void);
/* get the value of FMC HSM option bytes HSMDFWP in FMC_HSMWP register */
uint8_t hsm_ob_df_write_protection_get(void);
/* get the value of HSM option bytes security protection level in FMC_HSMOBSTAT register */
uint8_t hsm_ob_spc_get(void);
/* get the value of HSM option bytes BSWAP in FMC_HSMOBSTAT register */
uint8_t hsm_ob_swap_get(void);

/* interrupt & flag functions */
/* get FMC flag status */
FlagStatus fmc_flag_get(fmc_flag_enum flag);
/* clear FMC flag status */
void fmc_flag_clear(fmc_flag_enum flag);
/* enable FMC interrupt */
void fmc_interrupt_enable(fmc_interrupt_enum interrupt);
/* disable FMC interrupt */
void fmc_interrupt_disable(fmc_interrupt_enum interrupt);
/* get FMC interrupt flag status */
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum int_flag);
/* clear FMC interrupt flag status */
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum int_flag);

/* ECC interrupt & flag functions */
/* get FMC ECC flag status */
FlagStatus fmc_ecc_flag_get(fmc_ecc_flag_enum flag, fmc_register_enum reg_num);
/* clear FMC ECC flag status */
void fmc_ecc_flag_clear(fmc_ecc_flag_enum flag, fmc_register_enum reg_num);
/* enable FMC ECC interrupt */
void fmc_ecc_interrupt_enable(fmc_ecc_interrupt_enum interrupt, fmc_register_enum reg_num);
/* disable FMC ECC interrupt */
void fmc_ecc_interrupt_disable(fmc_ecc_interrupt_enum interrupt, fmc_register_enum reg_num);
/* get FMC ECC interrupt flag status */
FlagStatus fmc_ecc_interrupt_flag_get(fmc_ecc_interrupt_flag_enum int_flag, fmc_register_enum reg_num);
/* clear FMC ECC interrupt flag status */
void fmc_ecc_interrupt_flag_clear(fmc_ecc_interrupt_flag_enum int_flag, fmc_register_enum reg_num);
/* get FMC block correctable ecc error address */
uint32_t fmc_block_cecc_address_get(fmc_register_enum reg_num, fmc_cecc_addr_enum address_idx);
/* get FMC block uncorrectable ecc error address */
uint32_t fmc_block_ucecc_address_get(fmc_register_enum reg_num);
/* get FMC buffer correctable ecc error address */
uint32_t fmc_buffer_cecc_address_get(fmc_register_enum reg_num, fmc_cecc_addr_enum address_idx);
/* get FMC buffer uncorrectable ecc error address */
uint32_t fmc_buffer_ucecc_address_get(fmc_register_enum reg_num);
/* get FMC fast program buffer correctable ecc error address */
uint32_t fmc_fpb_cecc_address_get(fmc_cecc_addr_enum address_idx);
/* get FMC fast program buffer uncorrectable ecc error address */
uint32_t fmc_fpb_ucecc_address_get(void);
/* get PID */
uint32_t fmc_pid_get(uint32_t pidx);

#endif /* GD32A7XX_FMC_H */
