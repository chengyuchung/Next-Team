/*!
    \file    gd32a7xx_sram_tcm.h
    \brief   definitions for the SRAM and TCM register

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

#ifndef GD32A7XX_SRAM_TCM_H
#define GD32A7XX_SRAM_TCM_H

#include "gd32a7xx.h"

#define SRAM_REG                         SRAMC_BASE                          /*!< SRAM_REG register base address */
#define TCM_REG                          TCMREG_BASE                         /*!< TCM_REG register base address */

/* SRAM_REG registers definitions */
#define SRAM_INTEN                       REG32(SRAM_REG + 0x00000000U)                /*!< SRAM interrupt enable register */
#define SRAM_ERR                         REG32(SRAM_REG + 0x00000004U)                /*!< SRAM error status register  */
#define SRAM_CBEADDR0(m)                 REG32(SRAM_REG + 0x00000008U + 0x00000004U * (m))  /*!< SRAM correctable bit error address 0 for SRAM0/1 register */
#define SRAM_CBEADDR1(m)                 REG32(SRAM_REG + 0x00000010U + 0x00000004U * (m))  /*!< SRAM correctable bit error address 1 for SRAM0/1 register */
#define SRAM_CBEADDR2(m)                 REG32(SRAM_REG + 0x00000018U + 0x00000004U * (m))  /*!< SRAM correctable bit error address 2 for SRAM0/1 register */
#define SRAM_CBEADDR3(m)                 REG32(SRAM_REG + 0x00000020U + 0x00000004U * (m))  /*!< SRAM correctable bit error address 3 for SRAM0/1 register */
#define SRAM_UBEADDR(m)                  REG32(SRAM_REG + 0x00000028U + 0x00000004U * (m))  /*!< SRAM uncorrectable bit error address for SRAM0/1 register */
#define SRAM_BUFVLD                      REG32(SRAM_REG + 0x00000030U)                /*!< SRAM buffer valid register */
#define SRAM_OVF                         REG32(SRAM_REG + 0x00000034U)                /*!< SRAM overflow status register */
#define SRAM_WP                          REG32(SRAM_REG + 0x00000038U)                /*!< SRAM write protection register */
#define SRAM_ECCCERR                     REG32(SRAM_REG + 0x0000003CU)                /*!< SRAM ECC code error status register */

/* TCM_REG registers definitions */
#define TCM_INTEN                        REG32(TCM_REG + 0x00000000U)                 /*!< TCM interrupt enable register */
#define TCM_ERR                          REG32(TCM_REG + 0x00000004U)                 /*!< TCM error status register  */
#define TCM_CBEADDR0(m)                  REG32(TCM_REG + 0x00000008U + 0x00000004U*(m))     /*!< TCM correctable bit error address 0 for \
                                                                                            CM7_0_ITCM/CM7_0_D0TCM/CM7_0_D1TCM/CM7_1_ITCM/CM7_1_D0TCM/CM7_1_D1TCM register */
#define TCM_CBEADDR1(m)                  REG32(TCM_REG + 0x00000020U + 0x00000004U*(m))     /*!< TCM correctable bit error address 1 for \
                                                                                            CM7_0_ITCM/CM7_0_D0TCM/CM7_0_D1TCM/CM7_1_ITCM/CM7_1_D0TCM/CM7_1_D1TCM register */
#define TCM_CBEADDR2(m)                  REG32(TCM_REG + 0x00000038U + 0x00000004U*(m))     /*!< TCM correctable bit error address 2 for \
                                                                                            CM7_0_ITCM/CM7_0_D0TCM/CM7_0_D1TCM/CM7_1_ITCM/CM7_1_D0TCM/CM7_1_D1TCM register */
#define TCM_CBEADDR3(m)                  REG32(TCM_REG + 0x00000050U + 0x00000004U*(m))     /*!< TCM correctable bit error address 3 for \
                                                                                            CM7_0_ITCM/CM7_0_D0TCM/CM7_0_D1TCM/CM7_1_ITCM/CM7_1_D0TCM/CM7_1_D1TCM register */
#define TCM_UBEADDR(m)                   REG32(TCM_REG + 0x00000068U + 0x00000004U*(m))     /*!< TCM uncorrectable bit error address for \
                                                                                            CM7_0_ITCM/CM7_0_D0TCM/CM7_0_D1TCM/CM7_1_ITCM/CM7_1_D0TCM/CM7_1_D1TCM register */
#define TCM_BUFVLD                       REG32(TCM_REG + 0x00000080U)                 /*!< TCM buffer valid register */
#define TCM_OVF                          REG32(TCM_REG + 0x00000084U)                 /*!< TCM overflow status register */
#define TCM_WP                           REG32(TCM_REG + 0x00000088U)                 /*!< TCM write protection register */
#define TCM0_ECCCERR                     REG32(TCM_REG + 0x0000008CU)                 /*!< TCM0 ECC code error status register */
#if defined(GD32A72XX) || defined(GD32A74XX)
#define TCM1_ECCCERR                     REG32(TCM_REG + 0x00000090U)                 /*!< TCM1 ECC code error status register */
#endif

/* SRAM register bits definitions */
/* SRAM_INTEN */
#define SRAM_INTEN_SRAM_CBEIE            BIT(0)                              /*!< SRAM0/1 correctable bit error interrupt enable */
#define SRAM_INTEN_SRAM_UBEIE            BIT(1)                              /*!< SRAM0/1 uncorrectable bit error interrupt enable */
#define SRAM_INTEN_SRAM_OVFIE            BIT(2)                              /*!< SRAM0/1 address buffer overflow interrupt enable */
#define SRAM_INTEN_SRAM_CTLEIE           BIT(3)                              /*!< SRAM0/1 controller redundancy check error interrupt enable */

/* SRAM_ERR */
#define SRAM_ERR_SRAM0_CTLERR            BIT(0)                              /*!< SRAM0 controller redundancy check error flag */
#define SRAM_ERR_SRAM1_CTLERR            BIT(1)                              /*!< SRAM1 controller redundancy check error flag */
#define SRAM_ERR_SRAM0_ECCCERR           BIT(2)                              /*!< SRAM0 ECC single bit correctable error flag */
#define SRAM_ERR_SRAM1_ECCCERR           BIT(3)                              /*!< SRAM0 ECC single bit correctable error flag */
#define SRAM_ERR_SRAM0_ADDRERR           BIT(4)                              /*!< SRAM0 ECC single bit address error flag */
#define SRAM_ERR_SRAM1_ADDRERR           BIT(5)                              /*!< SRAM1 ECC single bit address error flag */
#define SRAM_ERR_SRAM0_ECCUERR           BIT(6)                              /*!< SRAM0 ECC double bit uncorrectable error flag */
#define SRAM_ERR_SRAM1_ECCUERR           BIT(7)                              /*!< SRAM1 ECC double bit uncorrectable error flag */
#define SRAM_ERR_SRAM0_EDCERR            BIT(8)                              /*!< SRAM0 EDC after ECC checker error flag */
#define SRAM_ERR_SRAM1_EDCERR            BIT(9)                              /*!< SRAM1 EDC after ECC checker error flag */

/* SRAM_CEBADDR0 */
#define SRAM_CBEADDR0_SRAM_CBEADDR0      BITS(0,31)                          /*!< first correctable bit error address of SRAM */

/* SRAM_CEBADDR1 */
#define SRAM_CBEADDR1_SRAM_CBEADDR1      BITS(0,31)                          /*!< second correctable bit error address of SRAM */

/* SRAM_CEBADDR2 */
#define SRAM_CBEADDR2_SRAM_CBEADDR2      BITS(0,31)                          /*!< third correctable bit error address of SRAM */

/* SRAM_CEBADDR3 */
#define SRAM_CBEADDR3_SRAM_CBEADDR3      BITS(0,31)                          /*!< fourth correctable bit error address of SRAM */

/* SRAM_UBEADDR */
#define SRAM_UBEADDR_SRAM_UBEADDR        BITS(0,31)                          /*!< un-correctable bit error address of SRAM */

/* SRAM_BUFVLD */
#define SRAM_BUFVLD_SRAM0_CBEADDRVLD0    BIT(0)                              /*!< SRAM0 correctable bit error address0 valid flag */
#define SRAM_BUFVLD_SRAM0_CBEADDRVLD1    BIT(1)                              /*!< SRAM0 correctable bit error address1 valid flag */
#define SRAM_BUFVLD_SRAM0_CBEADDRVLD2    BIT(2)                              /*!< SRAM0 correctable bit error address2 valid flag */
#define SRAM_BUFVLD_SRAM0_CBEADDRVLD3    BIT(3)                              /*!< SRAM0 correctable bit error address3 valid flag */

#define SRAM_BUFVLD_SRAM1_CBEADDRVLD0    BIT(4)                              /*!< SRAM1 correctable bit error address0 valid flag */
#define SRAM_BUFVLD_SRAM1_CBEADDRVLD1    BIT(5)                              /*!< SRAM1 correctable bit error address1 valid flag */
#define SRAM_BUFVLD_SRAM1_CBEADDRVLD2    BIT(6)                              /*!< SRAM1 correctable bit error address2 valid flag */
#define SRAM_BUFVLD_SRAM1_CBEADDRVLD3    BIT(7)                              /*!< SRAM1 correctable bit error address3 valid flag */

#define SRAM_BUFVLD_SRAM0_UBEADDRVLD     BIT(8)                              /*!< SRAM0 un-correctable bit error address valid flag */
#define SRAM_BUFVLD_SRAM1_UBEADDRVLD     BIT(9)                              /*!< SRAM1 un-correctable bit error address valid flag */

/* SRAM_OVF */
#define SRAM_OVF_SRAM0_CBEOVF            BIT(0)                              /*!< SRAM0 correctable bit error address buffer overflow */
#define SRAM_OVF_SRAM1_CBEOVF            BIT(1)                              /*!< SRAM1 correctable bit error address buffer overflow */

/* SRAM_WP */
#define SRAM_WP_SRAM_P0WP                BIT(0)                              /*!< SRAM page 0 write protection bit */
#define SRAM_WP_SRAM_P1WP                BIT(1)                              /*!< SRAM page 1 write protection bit */
#define SRAM_WP_SRAM_P2WP                BIT(2)                              /*!< SRAM page 2 write protection bit */
#define SRAM_WP_SRAM_P3WP                BIT(3)                              /*!< SRAM page 3 write protection bit */
#define SRAM_WP_SRAM_P4WP                BIT(4)                              /*!< SRAM page 4 write protection bit */
#define SRAM_WP_SRAM_P5WP                BIT(5)                              /*!< SRAM page 5 write protection bit */
#define SRAM_WP_SRAM_P6WP                BIT(6)                              /*!< SRAM page 6 write protection bit */
#define SRAM_WP_SRAM_P7WP                BIT(7)                              /*!< SRAM page 7 write protection bit */
#define SRAM_WP_SRAM_P8WP                BIT(8)                              /*!< SRAM page 8 write protection bit */
#define SRAM_WP_SRAM_P9WP                BIT(9)                              /*!< SRAM page 9 write protection bit */
#define SRAM_WP_SRAM_P10WP               BIT(10)                             /*!< SRAM page 10 write protection bit */
#define SRAM_WP_SRAM_P11WP               BIT(11)                             /*!< SRAM page 11 write protection bit */
#define SRAM_WP_SRAM_P12WP               BIT(12)                             /*!< SRAM page 12 write protection bit */
#define SRAM_WP_SRAM_P13WP               BIT(13)                             /*!< SRAM page 13 write protection bit */
#define SRAM_WP_SRAM_P14WP               BIT(14)                             /*!< SRAM page 14 write protection bit */
#define SRAM_WP_SRAM_P15WP               BIT(15)                             /*!< SRAM page 15 write protection bit */
#define SRAM_WP_SRAM_P16WP               BIT(16)                             /*!< SRAM page 16 write protection bit */
#define SRAM_WP_SRAM_P17WP               BIT(17)                             /*!< SRAM page 17 write protection bit */
#define SRAM_WP_SRAM_P18WP               BIT(18)                             /*!< SRAM page 18 write protection bit */
#define SRAM_WP_SRAM_P19WP               BIT(19)                             /*!< SRAM page 19 write protection bit */

/* SRAM_ECCCERR */
#define SRAM_ECCCERR_SRAM0_ECCCDET       BITS(0,8)                           /*!< SRAM0 ecc code calculated with check error detected */
#define SRAM_ECCCERR_SRAM1_ECCCDET       BITS(16,24)                         /*!< SRAM1 ecc code calculated with check error detected */

/* TCM_REG register bits definitions */
/* SRAM_INTEN */
#define TCM_INTEN_TCM0_CBEIE             BIT(0)                              /*!< TCM of CM7_0 correctable bit error interrupt enable */
#define TCM_INTEN_TCM1_CBEIE             BIT(1)                              /*!< TCM of CM7_1 correctable bit error interrupt enable */

#define TCM_INTEN_TCM0_UBEIE             BIT(2)                              /*!< TCM of CM7_0 uncorrectable bit error interrupt enable */
#define TCM_INTEN_TCM1_UBEIE             BIT(3)                              /*!< TCM of CM7_1 uncorrectable bit error interrupt enable */

#define TCM_INTEN_TCM0_OVFIE             BIT(4)                              /*!< TCM of CM7_0 address buffer overflow interrupt enable */
#define TCM_INTEN_TCM1_OVFIE             BIT(5)                              /*!< TCM of CM7_1 address buffer overflow interrupt enable */

#define TCM_INTEN_TCM0_CTLEIE            BIT(6)                              /*!< TCM of CM7_0 controller redundancy check error interrupt enable */
#define TCM_INTEN_TCM1_CTLEIE            BIT(7)                              /*!< TCM of CM7_1 controller redundancy check error interrupt enable */

/* TCM_ERR */
#define TCM_ERR_TCM0_CTLERR              BIT(0)                              /*!< TCM of CM7_0 controller redundancy check error flag */
#define TCM_ERR_TCM1_CTLERR              BIT(1)                              /*!< TCM of CM7_1 controller redundancy check error flag */

#define TCM_ERR_ITCM0_ECCCERR            BIT(2)                              /*!< ITCM of CM7_0 single bit correctable error flag */
#define TCM_ERR_D0TCM0_ECCCERR           BIT(3)                              /*!< D0TCM0 of CM7_0 single bit correctable error flag */
#define TCM_ERR_D1TCM0_ECCCERR           BIT(4)                              /*!< D1TCM0 of CM7_0 single bit correctable error flag */
#define TCM_ERR_ITCM1_ECCCERR            BIT(5)                              /*!< ITCM of CM7_1 single bit correctable error flag */
#define TCM_ERR_D0TCM1_ECCCERR           BIT(6)                              /*!< D0TCM0 of CM7_1 single bit correctable error flag */
#define TCM_ERR_D1TCM1_ECCCERR           BIT(7)                              /*!< D1TCM0 of CM7_1 single bit correctable error flag */

#define TCM_ERR_ITCM0_ADDRERR            BIT(8)                              /*!< ITCM of CM7_0 single bit address error flag */
#define TCM_ERR_D0TCM0_ADDRERR           BIT(9)                              /*!< D0TCM0 of CM7_0 single bit address error flag */
#define TCM_ERR_D1TCM0_ADDRERR           BIT(10)                             /*!< D1TCM0 of CM7_0 single bit address error flag */
#define TCM_ERR_ITCM1_ADDRERR            BIT(11)                             /*!< ITCM of CM7_1 single bit address error flag */
#define TCM_ERR_D0TCM1_ADDRERR           BIT(12)                             /*!< D0TCM0 of CM7_1 single bit address error flag */
#define TCM_ERR_D1TCM1_ADDRERR           BIT(13)                             /*!< D1TCM0 of CM7_1 single bit address error flag */

#define TCM_ERR_ITCM0_ECCUERR            BIT(16)                             /*!< ITCM of CM7_0 ECC double bit uncorrectable error flag */
#define TCM_ERR_D0TCM0_ECCUERR           BIT(17)                             /*!< D0TCM0 of CM7_0 ECC double bit uncorrectable error flag */
#define TCM_ERR_D1TCM0_ECCUERR           BIT(18)                             /*!< D1TCM0 of CM7_0 ECC double bit uncorrectable error flag */
#define TCM_ERR_ITCM1_ECCUERR            BIT(19)                             /*!< ITCM of CM7_1 ECC double bit uncorrectable error flag */
#define TCM_ERR_D0TCM1_ECCUERR           BIT(20)                             /*!< D0TCM0 of CM7_1 ECC double bit uncorrectable error flag */
#define TCM_ERR_D1TCM1_ECCUERR           BIT(21)                             /*!< D1TCM0 of CM7_1 ECC double bit uncorrectable error flag */

#define TCM_ERR_ITCM0_EDCERR             BIT(24)                             /*!< ITCM of CM7_0 EDC after ECC checker error flag */
#define TCM_ERR_D0TCM0_EDCERR            BIT(25)                             /*!< D0TCM0 of CM7_0 EDC after ECC checker error flag */
#define TCM_ERR_D1TCM0_EDCERR            BIT(26)                             /*!< D1TCM0 of CM7_0 EDC after ECC checker error flag */
#define TCM_ERR_ITCM1_EDCERR             BIT(27)                             /*!< ITCM of CM7_1 EDC after ECC checker error flag */
#define TCM_ERR_D0TCM1_EDCERR            BIT(28)                             /*!< D0TCM0 of CM7_1 EDC after ECC checker error flag */
#define TCM_ERR_D1TCM1_EDCERR            BIT(29)                             /*!< D1TCM0 of CM7_1 EDC after ECC checker error flag */

/* TCM_CEBADDR0 */
#define TCM_CBEADDR0_TCM_CBEADDR0        BITS(0,31)                          /*!< first correctable bit error address of TCM */

/* TCM_CEBADDR1 */
#define TCM_CBEADDR1_TCM_CBEADDR1        BITS(0,31)                          /*!< second correctable bit error address of TCM */

/* TCM_CEBADDR2 */
#define TCM_CBEADDR2_TCM_CBEADDR2        BITS(0,31)                          /*!< third correctable bit error address of TCM */

/* TCM_CEBADDR3 */
#define TCM_CBEADDR3_TCM_CBEADDR3        BITS(0,31)                          /*!< fourth correctable bit error address of TCM */

/* TCM_UBEADDR */
#define TCM_UBEADDR_TCM_UBEADDR          BITS(0,31)                          /*!< un-correctable bit error address of TCM */

/* TCM_BUFVLD */
#define TCM_BUFVLD_ITCM0_CBEADDRVLD0     BIT(0)                              /*!< ITCM of CM7_0 correctable bit error address0 valid flag */
#define TCM_BUFVLD_ITCM0_CBEADDRVLD1     BIT(1)                              /*!< ITCM of CM7_0 correctable bit error address1 valid flag */
#define TCM_BUFVLD_ITCM0_CBEADDRVLD2     BIT(2)                              /*!< ITCM of CM7_0 correctable bit error address2 valid flag */
#define TCM_BUFVLD_ITCM0_CBEADDRVLD3     BIT(3)                              /*!< ITCM of CM7_0 correctable bit error address3 valid flag */

#define TCM_BUFVLD_D0TCM0_CBEADDRVLD0    BIT(4)                              /*!< D0TCM of CM7_0 correctable bit error address0 valid flag */
#define TCM_BUFVLD_D0TCM0_CBEADDRVLD1    BIT(5)                              /*!< D0TCM of CM7_0 correctable bit error address1 valid flag */
#define TCM_BUFVLD_D0TCM0_CBEADDRVLD2    BIT(6)                              /*!< D0TCM of CM7_0 correctable bit error address2 valid flag */
#define TCM_BUFVLD_D0TCM0_CBEADDRVLD3    BIT(7)                              /*!< D0TCM of CM7_0 correctable bit error address3 valid flag */

#define TCM_BUFVLD_D1TCM0_CBEADDRVLD0    BIT(8)                              /*!< D1TCM of CM7_0 correctable bit error address0 valid flag */
#define TCM_BUFVLD_D1TCM0_CBEADDRVLD1    BIT(9)                              /*!< D1TCM of CM7_0 correctable bit error address1 valid flag */
#define TCM_BUFVLD_D1TCM0_CBEADDRVLD2    BIT(10)                             /*!< D1TCM of CM7_0 correctable bit error address2 valid flag */
#define TCM_BUFVLD_D1TCM0_CBEADDRVLD3    BIT(11)                             /*!< D1TCM of CM7_0 correctable bit error address3 valid flag */

#define TCM_BUFVLD_ITCM1_CBEADDRVLD0     BIT(12)                             /*!< ITCM of CM7_1 correctable bit error address0 valid flag */
#define TCM_BUFVLD_ITCM1_CBEADDRVLD1     BIT(13)                             /*!< ITCM of CM7_1 correctable bit error address1 valid flag */
#define TCM_BUFVLD_ITCM1_CBEADDRVLD2     BIT(14)                             /*!< ITCM of CM7_1 correctable bit error address2 valid flag */
#define TCM_BUFVLD_ITCM1_CBEADDRVLD3     BIT(15)                             /*!< ITCM of CM7_1 correctable bit error address3 valid flag */

#define TCM_BUFVLD_D0TCM1_CBEADDRVLD0    BIT(16)                             /*!< D0TCM of CM7_1 correctable bit error address0 valid flag */
#define TCM_BUFVLD_D0TCM1_CBEADDRVLD1    BIT(17)                             /*!< D0TCM of CM7_1 correctable bit error address1 valid flag */
#define TCM_BUFVLD_D0TCM1_CBEADDRVLD2    BIT(18)                             /*!< D0TCM of CM7_1 correctable bit error address2 valid flag */
#define TCM_BUFVLD_D0TCM1_CBEADDRVLD3    BIT(19)                             /*!< D0TCM of CM7_1 correctable bit error address3 valid flag */

#define TCM_BUFVLD_D1TCM1_CBEADDRVLD0    BIT(20)                             /*!< D1TCM of CM7_1 correctable bit error address0 valid flag */
#define TCM_BUFVLD_D1TCM1_CBEADDRVLD1    BIT(21)                             /*!< D1TCM of CM7_1 correctable bit error address1 valid flag */
#define TCM_BUFVLD_D1TCM1_CBEADDRVLD2    BIT(22)                             /*!< D1TCM of CM7_1 correctable bit error address2 valid flag */
#define TCM_BUFVLD_D1TCM1_CBEADDRVLD3    BIT(23)                             /*!< D1TCM of CM7_1 correctable bit error address3 valid flag */

#define TCM_BUFVLD_ITCM0_UBEADDRVLD      BIT(26)                             /*!< ITCM of CM7_0 un-correctable bit error address valid flag */
#define TCM_BUFVLD_D0TCM0_UBEADDRVLD     BIT(27)                             /*!< D0TCM of CM7_0 un-correctable bit error address valid flag */
#define TCM_BUFVLD_D1TCM0_UBEADDRVLD     BIT(28)                             /*!< D1TCM of CM7_0 un-correctable bit error address valid flag */

#define TCM_BUFVLD_ITCM1_UBEADDRVLD      BIT(29)                             /*!< ITCM of CM7_1 un-correctable bit error address valid flag */
#define TCM_BUFVLD_D0TCM1_UBEADDRVLD     BIT(30)                             /*!< D0TCM of CM7_1 un-correctable bit error address valid flag */
#define TCM_BUFVLD_D1TCM1_UBEADDRVLD     BIT(31)                             /*!< D1TCM of CM7_1 un-correctable bit error address valid flag */

/* TCM_OVF */
#define TCM_OVF_ITCM0_CBEOVF             BIT(0)                              /*!< ITCM of CM7_0 correctable bit error address buffer overflow */
#define TCM_OVF_D0TCM0_CBEOVF            BIT(1)                              /*!< D0TCM of CM7_0 correctable bit error address buffer overflow */
#define TCM_OVF_D1TCM0_CBEOVF            BIT(2)                              /*!< D1TCM of CM7_0 correctable bit error address buffer overflow */
#define TCM_OVF_ITCM1_CBEOVF             BIT(3)                              /*!< ITCM of CM7_1 correctable bit error address buffer overflow */
#define TCM_OVF_D0TCM1_CBEOVF            BIT(4)                              /*!< D0TCM of CM7_1 correctable bit error address buffer overflow */
#define TCM_OVF_D1TCM1_CBEOVF            BIT(5)                              /*!< D1TCM of CM7_1 correctable bit error address buffer overflow */

/* TCM_WP */
#define TCM_WP_ITCM0_P0WP                BIT(0)                              /*!< ITCM of CM7_0 page 0 write protection bit */
#define TCM_WP_ITCM0_P1WP                BIT(1)                              /*!< ITCM of CM7_0 page 1 write protection bit */
#define TCM_WP_ITCM0_P2WP                BIT(2)                              /*!< ITCM of CM7_0 page 2 write protection bit */
#define TCM_WP_ITCM0_P3WP                BIT(3)                              /*!< ITCM of CM7_0 page 3 write protection bit */

#define TCM_WP_ITCM1_P0WP                BIT(4)                              /*!< ITCM of CM7_1 page 0 write protection bit */
#define TCM_WP_ITCM1_P1WP                BIT(5)                              /*!< ITCM of CM7_1 page 1 write protection bit */
#define TCM_WP_ITCM1_P2WP                BIT(6)                              /*!< ITCM of CM7_1 page 2 write protection bit */
#define TCM_WP_ITCM1_P3WP                BIT(7)                              /*!< ITCM of CM7_1 page 3 write protection bit */

#define TCM_WP_DTCM0_P0WP                BIT(16)                             /*!< DTCM of CM7_0 page 0 write protection bit */
#define TCM_WP_DTCM0_P1WP                BIT(17)                             /*!< DTCM of CM7_0 page 1 write protection bit */
#define TCM_WP_DTCM0_P2WP                BIT(18)                             /*!< DTCM of CM7_0 page 2 write protection bit */
#define TCM_WP_DTCM0_P3WP                BIT(19)                             /*!< DTCM of CM7_0 page 3 write protection bit */
#define TCM_WP_DTCM0_P4WP                BIT(20)                             /*!< DTCM of CM7_0 page 4 write protection bit */
#define TCM_WP_DTCM0_P5WP                BIT(21)                             /*!< DTCM of CM7_0 page 5 write protection bit */
#define TCM_WP_DTCM0_P6WP                BIT(22)                             /*!< DTCM of CM7_0 page 6 write protection bit */
#define TCM_WP_DTCM0_P7WP                BIT(23)                             /*!< DTCM of CM7_0 page 7 write protection bit */

#define TCM_WP_DTCM1_P0WP                BIT(24)                             /*!< DTCM of CM7_1 page 0 write protection bit */
#define TCM_WP_DTCM1_P1WP                BIT(25)                             /*!< DTCM of CM7_1 page 1 write protection bit */
#define TCM_WP_DTCM1_P2WP                BIT(26)                             /*!< DTCM of CM7_1 page 2 write protection bit */
#define TCM_WP_DTCM1_P3WP                BIT(27)                             /*!< DTCM of CM7_1 page 3 write protection bit */
#define TCM_WP_DTCM1_P4WP                BIT(28)                             /*!< DTCM of CM7_1 page 4 write protection bit */
#define TCM_WP_DTCM1_P5WP                BIT(29)                             /*!< DTCM of CM7_1 page 5 write protection bit */
#define TCM_WP_DTCM1_P6WP                BIT(30)                             /*!< DTCM of CM7_1 page 6 write protection bit */
#define TCM_WP_DTCM1_P7WP                BIT(31)                             /*!< DTCM of CM7_1 page 7 write protection bit */

/* TCM0_ECCCERR */
#define TCM0_ECCCERR_ITCM0_ECCCDET       BITS(0,8)                           /*!< ITCM0 of CM7_0 ecc code calculated with check error detected */
#define TCM0_ECCCERR_D0TCM0_ECCCDET      BITS(16,23)                         /*!< D0TCM0 of CM7_0 ecc code calculated with check error detected */
#define TCM0_ECCCERR_D1TCM0_ECCCDET      BITS(24,31)                         /*!< D1TCM0 of CM7_0 ecc code calculated with check error detected */

/* TCM1_ECCCERR */
#define TCM1_ECCCERR_ITCM1_ECCCDET       BITS(0,8)                           /*!< ITCM1 of CM7_1 ecc code calculated with check error detected */
#define TCM1_ECCCERR_D0TCM1_ECCCDET      BITS(16,23)                         /*!< D0TCM1 of CM7_1 ecc code calculated with check error detected */
#define TCM1_ECCCERR_D1TCM1_ECCCDET      BITS(24,31)                         /*!< D1TCM1 of CM7_1 ecc code calculated with check error detected */

/* constants definitions */
/* SRAM ID */
#define SRAM_ID_SRAM0                           ((uint32_t)0U)               /*!< SRAM0 */
#define SRAM_ID_SRAM1                           ((uint32_t)1U)               /*!< SRAM1 */

/* TCM ID */
#define TCM_ID_ITCM0                            ((uint32_t)0U)               /*!< ITCM of CM7_0 */
#define TCM_ID_D0TCM0                           ((uint32_t)1U)               /*!< D0TCM of CM7_0 */
#define TCM_ID_D1TCM0                           ((uint32_t)2U)               /*!< D1TCM of CM7_0 */
#define TCM_ID_ITCM1                            ((uint32_t)3U)               /*!< ITCM of CM7_1 */
#define TCM_ID_D0TCM1                           ((uint32_t)4U)               /*!< D0TCM of CM7_1 */
#define TCM_ID_D1TCM1                           ((uint32_t)5U)               /*!< D1TCM of CM7_1 */

/* SRAM0/1 interrupt enable/disable */
#define SRAM_INT_CORRECTABLE_ERROR              SRAM_INTEN_SRAM_CBEIE        /*!< SRAM single bit ecc error interrupt */
#define SRAM_INT_UNCORRECTABLE_ERROR            SRAM_INTEN_SRAM_UBEIE        /*!< SRAM double bit ecc error interrupt */
#define SRAM_INT_ADDRESS_BUFFER_OVERFLOW        SRAM_INTEN_SRAM_OVFIE        /*!< SRAM ecc error address buffer overflow interrupt */
#define SRAM_INT_CONTROLLER_REDUNDANCY_CHECK    SRAM_INTEN_SRAM_CTLEIE       /*!< SRAM controller redundancy check error interrupt */

/* TCM interrupt enable/disable */
#define TCM_INT_CORRECTABLE_ERROR               TCM_INTEN_TCM0_CBEIE         /*!< TCM single bit ecc error interrupt */
#define TCM_INT_UNCORRECTABLE_ERROR             TCM_INTEN_TCM0_UBEIE         /*!< TCM double bit ecc error interrupt */
#define TCM_INT_ADDRESS_BUFFER_OVERFLOW         TCM_INTEN_TCM0_OVFIE         /*!< TCM ecc error address buffer overflow interrupt */
#define TCM_INT_CONTROLLER_REDUNDANCY_CHECK     TCM_INTEN_TCM0_CTLEIE        /*!< TCM controller redundancy check error interrupt */

/* SRAM error flag */
#define SRAM_FLAG_CTLERR                        SRAM_ERR_SRAM0_CTLERR        /*!< SRAM controller redundancy check error flag */
#define SRAM_FLAG_ECCCERR                       SRAM_ERR_SRAM0_ECCCERR       /*!< SRAM ECC single bit ecc error flag */
#define SRAM_FLAG_ADDRERR                       SRAM_ERR_SRAM0_ADDRERR       /*!< SRAM ECC single bit address error flag */
#define SRAM_FLAG_ECCUERR                       SRAM_ERR_SRAM0_ECCUERR       /*!< SRAM ECC double bit ecc error flag */
#define SRAM_FLAG_EDCERR                        SRAM_ERR_SRAM0_EDCERR        /*!< SRAM EDC after ECC checker error flag */

/* TCM error flag */
#define TCM_FLAG_CTLERR                         TCM_ERR_TCM0_CTLERR          /*!< TCM controller redundancy check error flag */
#define TCM_FLAG_ECCCERR                        TCM_ERR_ITCM0_ECCCERR        /*!< TCM ECC single bit ecc error flag */
#define TCM_FLAG_ADDRERR                        TCM_ERR_ITCM0_ADDRERR        /*!< TCM ECC single bit address error flag */
#define TCM_FLAG_ECCUERR                        TCM_ERR_ITCM0_ECCUERR        /*!< TCM ECC double bit ecc error flag */
#define TCM_FLAG_EDCERR                         TCM_ERR_ITCM0_EDCERR         /*!< TCM EDC after ECC checker error flag */

/* write protection for sram page(16KB) */
#define SRAM_WP_SRAM0_P0                        SRAM_WP_SRAM_P0WP            /*!< SRAM0 page 0 write protection bit */
#define SRAM_WP_SRAM0_P1                        SRAM_WP_SRAM_P1WP            /*!< SRAM0 page 1 write protection bit */
#define SRAM_WP_SRAM0_P2                        SRAM_WP_SRAM_P2WP            /*!< SRAM0 page 2 write protection bit */
#define SRAM_WP_SRAM0_P3                        SRAM_WP_SRAM_P3WP            /*!< SRAM0 page 3 write protection bit */
#define SRAM_WP_SRAM0_P4                        SRAM_WP_SRAM_P4WP            /*!< SRAM0 page 4 write protection bit */
#define SRAM_WP_SRAM0_P5                        SRAM_WP_SRAM_P5WP            /*!< SRAM0 page 5 write protection bit */
#define SRAM_WP_SRAM0_P6                        SRAM_WP_SRAM_P6WP            /*!< SRAM0 page 6 write protection bit */
#define SRAM_WP_SRAM0_P7                        SRAM_WP_SRAM_P7WP            /*!< SRAM0 page 7 write protection bit */
#define SRAM_WP_SRAM0_P8                        SRAM_WP_SRAM_P8WP            /*!< SRAM0 page 8 write protection bit */
#define SRAM_WP_SRAM0_P9                        SRAM_WP_SRAM_P9WP            /*!< SRAM0 page 9 write protection bit */
#define SRAM_WP_SRAM1_P0                        SRAM_WP_SRAM_P10WP           /*!< SRAM1 page 0 write protection bit */
#define SRAM_WP_SRAM1_P1                        SRAM_WP_SRAM_P11WP           /*!< SRAM1 page 1 write protection bit */
#define SRAM_WP_SRAM1_P2                        SRAM_WP_SRAM_P12WP           /*!< SRAM1 page 2 write protection bit */
#define SRAM_WP_SRAM1_P3                        SRAM_WP_SRAM_P13WP           /*!< SRAM1 page 3 write protection bit */
#define SRAM_WP_SRAM1_P4                        SRAM_WP_SRAM_P14WP           /*!< SRAM1 page 4 write protection bit */
#define SRAM_WP_SRAM1_P5                        SRAM_WP_SRAM_P15WP           /*!< SRAM1 page 5 write protection bit */
#define SRAM_WP_SRAM1_P6                        SRAM_WP_SRAM_P16WP           /*!< SRAM1 page 6 write protection bit */
#define SRAM_WP_SRAM1_P7                        SRAM_WP_SRAM_P17WP           /*!< SRAM1 page 7 write protection bit */
#define SRAM_WP_SRAM1_P8                        SRAM_WP_SRAM_P18WP           /*!< SRAM1 page 8 write protection bit */
#define SRAM_WP_SRAM1_P9                        SRAM_WP_SRAM_P19WP           /*!< SRAM1 page 9 write protection bit */
#define SRAM_WP_SRAM0_ALL                       BITS(0,9)                    /*!< SRAM0 all page write protection bit */
#define SRAM_WP_SRAM1_ALL                       BITS(10,19)                  /*!< SRAM1 all page write protection bit */
#define SRAM_WP_ALL                             BITS(0,19)                   /*!< SRAM0/1 all page write protection bit */

/* write protection for sram page(8KB) */
#define TCM_WP_ITCM0_P0                         TCM_WP_ITCM0_P0WP            /*!< ITCM of CM7_0 page 0 write protection bit */
#define TCM_WP_ITCM0_P1                         TCM_WP_ITCM0_P1WP            /*!< ITCM of CM7_0 page 1 write protection bit */
#define TCM_WP_ITCM0_P2                         TCM_WP_ITCM0_P2WP            /*!< ITCM of CM7_0 page 2 write protection bit */
#define TCM_WP_ITCM0_P3                         TCM_WP_ITCM0_P3WP            /*!< ITCM of CM7_0 page 3 write protection bit */

#define TCM_WP_ITCM1_P0                         TCM_WP_ITCM1_P0WP            /*!< ITCM of CM7_1 page 0 write protection bit */
#define TCM_WP_ITCM1_P1                         TCM_WP_ITCM1_P1WP            /*!< ITCM of CM7_1 page 1 write protection bit */
#define TCM_WP_ITCM1_P2                         TCM_WP_ITCM1_P2WP            /*!< ITCM of CM7_1 page 2 write protection bit */
#define TCM_WP_ITCM1_P3                         TCM_WP_ITCM1_P3WP            /*!< ITCM of CM7_1 page 3 write protection bit */

#define TCM_WP_DTCM0_P0                         TCM_WP_DTCM0_P0WP            /*!< DTCM of CM7_0 page 0 write protection bit */
#define TCM_WP_DTCM0_P1                         TCM_WP_DTCM0_P1WP            /*!< DTCM of CM7_0 page 1 write protection bit */
#define TCM_WP_DTCM0_P2                         TCM_WP_DTCM0_P2WP            /*!< DTCM of CM7_0 page 2 write protection bit */
#define TCM_WP_DTCM0_P3                         TCM_WP_DTCM0_P3WP            /*!< DTCM of CM7_0 page 3 write protection bit */
#define TCM_WP_DTCM0_P4                         TCM_WP_DTCM0_P4WP            /*!< DTCM of CM7_0 page 4 write protection bit */
#define TCM_WP_DTCM0_P5                         TCM_WP_DTCM0_P5WP            /*!< DTCM of CM7_0 page 5 write protection bit */
#define TCM_WP_DTCM0_P6                         TCM_WP_DTCM0_P6WP            /*!< DTCM of CM7_0 page 6 write protection bit */
#define TCM_WP_DTCM0_P7                         TCM_WP_DTCM0_P7WP            /*!< DTCM of CM7_0 page 7 write protection bit */

#define TCM_WP_DTCM1_P0                         TCM_WP_DTCM1_P0WP            /*!< DTCM of CM7_1 page 0 write protection bit */
#define TCM_WP_DTCM1_P1                         TCM_WP_DTCM1_P1WP            /*!< DTCM of CM7_1 page 1 write protection bit */
#define TCM_WP_DTCM1_P2                         TCM_WP_DTCM1_P2WP            /*!< DTCM of CM7_1 page 2 write protection bit */
#define TCM_WP_DTCM1_P3                         TCM_WP_DTCM1_P3WP            /*!< DTCM of CM7_1 page 3 write protection bit */
#define TCM_WP_DTCM1_P4                         TCM_WP_DTCM1_P4WP            /*!< DTCM of CM7_1 page 4 write protection bit */
#define TCM_WP_DTCM1_P5                         TCM_WP_DTCM1_P5WP            /*!< DTCM of CM7_1 page 5 write protection bit */
#define TCM_WP_DTCM1_P6                         TCM_WP_DTCM1_P6WP            /*!< DTCM of CM7_1 page 6 write protection bit */
#define TCM_WP_DTCM1_P7                         TCM_WP_DTCM1_P7WP            /*!< DTCM of CM7_1 page 7 write protection bit */

#define TCM_WP_ITCM0_ALL                        BITS(0,3)                    /*!< ITCM0 all page write protection bit */
#define TCM_WP_ITCM1_ALL                        BITS(4,7)                    /*!< ITCM1 all page write protection bit */
#define TCM_WP_DTCM0_ALL                        BITS(16,23)                  /*!< DTCM0 all page write protection bit */
#define TCM_WP_DTCM1_ALL                        BITS(24,31)                  /*!< DTCM1 all page write protection bit */
#define TCM_WP_ALL                              (BITS(0,7) | BITS(16,31))    /*!< TCM all page write protection bit */

/* single bit ecc error address index */
#define ECC_CBE_ADDRESS0                        ((uint32_t)0U)               /*!< single bit ecc error address index0 */
#define ECC_CBE_ADDRESS1                        ((uint32_t)1U)               /*!< single bit ecc error address index1 */
#define ECC_CBE_ADDRESS2                        ((uint32_t)2U)               /*!< single bit ecc error address index2 */
#define ECC_CBE_ADDRESS3                        ((uint32_t)3U)               /*!< single bit ecc error address index3 */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check SRAM ID */
#define NOT_SRAM_ID(id)                         (((id) != SRAM_ID_SRAM0) && \
                                                 ((id) != SRAM_ID_SRAM1))
/* check SRAM interrupt */
#define NOT_SRAM_INTERRUPT(interrupt)           (((interrupt) != SRAM_INT_CORRECTABLE_ERROR          )   && \
                                                 ((interrupt) != SRAM_INT_UNCORRECTABLE_ERROR        )   && \
                                                 ((interrupt) != SRAM_INT_ADDRESS_BUFFER_OVERFLOW    )   && \
                                                 ((interrupt) != SRAM_INT_CONTROLLER_REDUNDANCY_CHECK))

/* check SRAM get flag */
#define NOT_SRAM_GET_FLAG(flag)                 (((flag) != SRAM_FLAG_CTLERR )   && \
                                                 ((flag) != SRAM_FLAG_ECCCERR)   && \
                                                 ((flag) != SRAM_FLAG_ADDRERR)   && \
                                                 ((flag) != SRAM_FLAG_ECCUERR)   && \
                                                 ((flag) != SRAM_FLAG_EDCERR ))

/* check SRAM clear flag */
#define NOT_SRAM_CLEAR_FLAG(flag)               (((flag) != SRAM_FLAG_CTLERR )   && \
                                                 ((flag) != SRAM_FLAG_ECCCERR)   && \
                                                 ((flag) != SRAM_FLAG_ADDRERR)   && \
                                                 ((flag) != SRAM_FLAG_ECCUERR)   && \
                                                 ((flag) != SRAM_FLAG_EDCERR ))

/* check the range of SRAM address index */
#define NOT_SRAM_ADDRESS_INDEX(index)           (((index) != ECC_CBE_ADDRESS0)   && \
                                                 ((index) != ECC_CBE_ADDRESS1)   && \
                                                 ((index) != ECC_CBE_ADDRESS2)   && \
                                                 ((index) != ECC_CBE_ADDRESS3))

/* check SRAM write protection page */
#define NOT_SRAM_WP_PAGE(page)                  (((page) != SRAM_WP_SRAM0_P0 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P1 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P2 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P3 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P4 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P5 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P6 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P7 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P8 )   && \
                                                 ((page) != SRAM_WP_SRAM0_P9 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P0 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P1 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P2 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P3 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P4 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P5 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P6 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P7 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P8 )   && \
                                                 ((page) != SRAM_WP_SRAM1_P9 )   && \
                                                 ((page) != SRAM_WP_SRAM0_ALL)   && \
                                                 ((page) != SRAM_WP_SRAM1_ALL)   && \
                                                 ((page) != SRAM_WP_ALL      ))

/* check TCM ID */
#define NOT_TCM_ID(id)                          (((id) != TCM_ID_ITCM0  ) && \
                                                 ((id) != TCM_ID_D0TCM0 ) && \
                                                 ((id) != TCM_ID_D1TCM0 ) && \
                                                 ((id) != TCM_ID_ITCM1  ) && \
                                                 ((id) != TCM_ID_D0TCM1 ) && \
                                                 ((id) != TCM_ID_D1TCM1 ))

/* check TCM interrupt */
#define NOT_TCM_INTERRUPT(interrupt)            (((interrupt) != TCM_INT_CORRECTABLE_ERROR          )   && \
                                                 ((interrupt) != TCM_INT_UNCORRECTABLE_ERROR        )   && \
                                                 ((interrupt) != TCM_INT_ADDRESS_BUFFER_OVERFLOW    )   && \
                                                 ((interrupt) != TCM_INT_CONTROLLER_REDUNDANCY_CHECK))

/* check TCM get flag */
#define NOT_TCM_GET_FLAG(flag)                  (((flag) != TCM_FLAG_CTLERR )   && \
                                                 ((flag) != TCM_FLAG_ECCCERR)   && \
                                                 ((flag) != TCM_FLAG_ADDRERR)   && \
                                                 ((flag) != TCM_FLAG_ECCUERR)   && \
                                                 ((flag) != TCM_FLAG_EDCERR ))

/* check TCM clear flag */
#define NOT_TCM_CLEAR_FLAG(flag)                (((flag) != TCM_FLAG_CTLERR )   && \
                                                 ((flag) != TCM_FLAG_ECCCERR)   && \
                                                 ((flag) != TCM_FLAG_ADDRERR)   && \
                                                 ((flag) != TCM_FLAG_ECCUERR)   && \
                                                 ((flag) != TCM_FLAG_EDCERR ))

/* check the range of TCM address index */
#define NOT_TCM_ADDRESS_INDEX(index)            (((index) != ECC_CBE_ADDRESS0)   && \
                                                 ((index) != ECC_CBE_ADDRESS1)   && \
                                                 ((index) != ECC_CBE_ADDRESS2)   && \
                                                 ((index) != ECC_CBE_ADDRESS3))

/* check TCM write protection page */
#define NOT_TCM_WP_PAGE(page)                   (((page) != TCM_WP_ITCM0_P0 )   && \
                                                 ((page) != TCM_WP_ITCM0_P1 )   && \
                                                 ((page) != TCM_WP_ITCM0_P2 )   && \
                                                 ((page) != TCM_WP_ITCM0_P3 )   && \
                                                 ((page) != TCM_WP_ITCM1_P0 )   && \
                                                 ((page) != TCM_WP_ITCM1_P1 )   && \
                                                 ((page) != TCM_WP_ITCM1_P2 )   && \
                                                 ((page) != TCM_WP_ITCM1_P3 )   && \
                                                 ((page) != TCM_WP_DTCM0_P0 )   && \
                                                 ((page) != TCM_WP_DTCM0_P1 )   && \
                                                 ((page) != TCM_WP_DTCM0_P2 )   && \
                                                 ((page) != TCM_WP_DTCM0_P3 )   && \
                                                 ((page) != TCM_WP_DTCM0_P4 )   && \
                                                 ((page) != TCM_WP_DTCM0_P5 )   && \
                                                 ((page) != TCM_WP_DTCM0_P6 )   && \
                                                 ((page) != TCM_WP_DTCM0_P7 )   && \
                                                 ((page) != TCM_WP_DTCM1_P0 )   && \
                                                 ((page) != TCM_WP_DTCM1_P1 )   && \
                                                 ((page) != TCM_WP_DTCM1_P2 )   && \
                                                 ((page) != TCM_WP_DTCM1_P3 )   && \
                                                 ((page) != TCM_WP_DTCM1_P4 )   && \
                                                 ((page) != TCM_WP_DTCM1_P5 )   && \
                                                 ((page) != TCM_WP_DTCM1_P6 )   && \
                                                 ((page) != TCM_WP_DTCM1_P7 )   && \
                                                 ((page) != TCM_WP_ITCM0_ALL)   && \
                                                 ((page) != TCM_WP_ITCM1_ALL)   && \
                                                 ((page) != TCM_WP_DTCM0_ALL)   && \
                                                 ((page) != TCM_WP_DTCM1_ALL)   && \
                                                 ((page) != TCM_WP_ALL      ))
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* enable sram0/1 ecc error interrupt */
void sram_ecc_interrupt_enable(uint32_t interrupt);
/* disable sram0/1 and tcm ecc error interrupt */
void sram_ecc_interrupt_disable(uint32_t interrupt);
/* get sram0/1 error flag is set or not */
FlagStatus sram_error_flag_get(uint32_t sram_id, uint32_t flag);
/* clear sram0/1 error flag */
void sram_error_flag_clear(uint32_t sram_id, uint32_t flag);

/* get sram0/1 single bit ecc error address */
uint32_t sram_ecc_single_bit_address_get(uint32_t sram_id, uint32_t address_idx);
/* get sram0/1 double bit ecc error address */
uint32_t sram_ecc_double_bit_address_get(uint32_t sram_id);
/* get sram0/1 single bit ecc error address valid status */
FlagStatus sram_ecc_single_bit_address_valid_get(uint32_t sram_id, uint32_t address_idx);
/* get sram0/1 mutli bit ecc error address valid status */
FlagStatus sram_ecc_double_bit_address_valid_get(uint32_t sram_id);
/* clear sram0/1 single bit ecc error address valid status */
void sram_ecc_single_bit_address_valid_clear(uint32_t sram_id, uint32_t address_idx);
/* clear sram0/1 mutli bit ecc error address valid status */
void sram_ecc_double_bit_address_valid_clear(uint32_t sram_id);
/* get sram0/1 single bit ecc error address buffer overflow status */
FlagStatus sram_error_address_buffer_overflow_get(uint32_t sram_id);
/* clear sram0/1 single bit ecc error address buffer overflow status */
void sram_error_address_buffer_overflow_clear(uint32_t sram_id);

/* get sram0/1 ecc code of detected ecc error  */
uint32_t sram_ecc_code_get(uint32_t sram_id);
/* configure sram0/1 write protection */
void sram_write_protect_config(uint32_t wp_page, ControlStatus enable);
/* get sram0/1 write protection status */
FlagStatus sram_write_protection_get(uint32_t wp_page);

/* enable tcm ecc error interrupt */
void tcm_ecc_interrupt_enable(uint32_t tcm_id, uint32_t interrupt);
/*disable tcm ecc error interrupt */
void tcm_ecc_interrupt_disable(uint32_t tcm_id, uint32_t interrupt);
/* get tcm error flag is set or not */
FlagStatus tcm_error_flag_get(uint32_t tcm_id, uint32_t flag);
/* clear tcm error flag */
void tcm_error_flag_clear(uint32_t tcm_id, uint32_t flag);

/* get tcm single bit ecc error address */
uint32_t tcm_ecc_single_bit_address_get(uint32_t tcm_id, uint32_t address_index);
/* get tcm double bit ecc error address */
uint32_t tcm_ecc_double_bit_address_get(uint32_t tcm_id);
/* get tcm single bit ecc error address valid status */
FlagStatus tcm_ecc_single_bit_address_valid_get(uint32_t tcm_id, uint32_t address_index);
/* get tcm double bit ecc error address valid status */
FlagStatus tcm_ecc_double_bit_address_valid_get(uint32_t tcm_id);
/* clear tcm single bit ecc error address valid status */
void tcm_ecc_single_bit_address_valid_clear(uint32_t tcm_id, uint32_t address_index);
/* clear tcm double bit ecc error address valid status */
void tcm_ecc_double_bit_address_valid_clear(uint32_t tcm_id);
/* get tcm single bit ecc error address buffer overflow status */
FlagStatus tcm_error_address_buffer_overflow_get(uint32_t tcm_id);
/* clear tcm single bit ecc error address buffer overflow status */
void tcm_error_address_buffer_overflow_clear(uint32_t tcm_id);

/* get tcm ecc code of detected ecc error  */
uint32_t tcm_ecc_code_get(uint32_t tcm_id);
/* configure tcm write protection */
void tcm_write_protect_config(uint32_t wp_page, ControlStatus enable);
/* get tcm write protection status */
FlagStatus tcm_write_protection_get(uint32_t wp_page);

#endif /* GD32A7XX_SRAM_TCM_H */
