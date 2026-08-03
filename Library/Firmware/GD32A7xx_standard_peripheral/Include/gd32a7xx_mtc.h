/*!
    \file    gd32a7xx_mtc.h
    \brief   definitions for the MTC

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

#ifndef GD32A7XX_MTC_H
#define GD32A7XX_MTC_H

#include "gd32a7xx.h"

/* MTC definitions */
#define MTC                            MTC_BASE                        /*!< MTC bsae address */

/* registers definitions */
#define MTC_CTL0                       REG32((MTC) + 0x00000000U)      /*!< MTC global enable register */
#define MTC_CHCTL0                     REG32((MTC) + 0x00000004U)      /*!< MTC channel enable register 0 */
#define MTC_CHCTL1                     REG32((MTC) + 0x00000008U)      /*!< MTC channel enable register 1 */
#define MTC_CTL1                       REG32((MTC) + 0x0000000CU)      /*!< MTC EDC mode register */
#define MTC_EBGCFG0                    REG32((MTC) + 0x00000010U)      /*!< MTC error bits generate configuration register 0 */
#define MTC_EBGCFG1                    REG32((MTC) + 0x00000014U)      /*!< MTC error bits generate configuration register 1 */
#define MTC_EBGCFG2                    REG32((MTC) + 0x00000018U)      /*!< MTC error bits generate configuration register 2 */
#define MTC_EBGCFG3                    REG32((MTC) + 0x0000001CU)      /*!< MTC error bits generate configuration register 3 */
#define MTC_EBGCFG4                    REG32((MTC) + 0x00000020U)      /*!< MTC error bits generate configuration register 4 */
#define MTC_TMREN                      REG32((MTC) + 0x00000024U)      /*!< MTC triple modular redundancy enable register */
#define MTC_TMRSTAT                    REG32((MTC) + 0x00000028U)      /*!< MTC triple modular redundancy status register */
#define MTC_TMRFC                      REG32((MTC) + 0x0000002CU)      /*!< MTC triple modular redundancy flag clear register */

/* bits definitions */
/* MTC_CTL0 */
#define MTC_CTL0_GMTEN                 BITS(0, 15)                     /*!< MTC global memory test enable bits */

/* MTC_CTL1 */
#define MTC_CTL1_EDCMOD                BITS(0, 1)                      /*!< EDC error bits generation mode selection bits */

/* MTC_EBGCFG0 */
#define MTC_EBGCFG0_EBG                BITS(0, 31)                     /*!< error bits generate configuration bit */

/* MTC_EBGCFG1 */
#define MTC_EBGCFG1_EBG                BITS(0, 31)                     /*!< error bits generate configuration bit */

/* MTC_EBGCFG2 */
#define MTC_EBGCFG2_EBG                BITS(0, 31)                     /*!< error bits generate configuration bit */

/* MTC_EBGCFG3 */
#define MTC_EBGCFG3_EBG                BITS(0, 31)                     /*!< error bits generate configuration bit */

/* MTC_EBGCFG4 */
#define MTC_EBGCFG4_EBG                BITS(0, 31)                     /*!< error bits generate configuration bit */

/* MTC_TMREN */
#define MTC_TMR_EN                     BIT(0)                          /*!< TMR enable bit */

/* MTC_TMRSTAT */
#define MTC_TMR_ERR                    BIT(0)                          /*!< TMR error flag bit */

/* MTC_TMRFC */
#define MTC_TMR_FC                     BIT(0)                          /*!< clear MTC TMR error flag */

/* MTC_CTL0 configuration */
#define MTC_ENABLE                     ((uint16_t)0xA55AU)             /* error injection enable */

/* MTC EDC mode */
#define EDC_IN                         ((uint8_t)0x02U)                /*!< EDC injucton */
#define EDC_ECC_IN                     ((uint8_t)0x01U)                /*!< EDC after ECC injection */

/* MTC EDC mode */
#define EDCMOD(regval)                 (BITS(0,1) & ((uint32_t)(regval) << 0))
#define EDCMOD_ECC                     EDCMOD(0)                       /*!< error bits generation of ECC */
#define EDCMOD_EDC                     EDCMOD(1)                       /*!< error bits generation of EDC */
#define EDCMOD_EDC_ECC                 EDCMOD(2)                       /*!< error bits generation of EDC after ECC */

/* MTC channel */
typedef enum {
    /* MTC_CHCTL0 */
    MTC_CHCTL0_CHEN0 = 0,                                              /*!< memory test channel enable bit 0 */
    MTC_CHCTL0_CHEN1,                                                  /*!< memory test channel enable bit 1 */
    MTC_CHCTL0_CHEN2,                                                  /*!< memory test channel enable bit 2 */
    MTC_CHCTL0_CHEN3,                                                  /*!< memory test channel enable bit 3 */
    MTC_CHCTL0_CHEN4,                                                  /*!< memory test channel enable bit 4 */
    MTC_CHCTL0_CHEN5,                                                  /*!< memory test channel enable bit 5 */
    MTC_CHCTL0_CHEN6,                                                  /*!< memory test channel enable bit 6 */
    MTC_CHCTL0_CHEN7,                                                  /*!< memory test channel enable bit 7 */
    MTC_CHCTL0_CHEN8,                                                  /*!< memory test channel enable bit 8 */
    MTC_CHCTL0_CHEN9,                                                  /*!< memory test channel enable bit 9 */
    MTC_CHCTL0_CHEN10,                                                 /*!< memory test channel enable bit 10 */
    MTC_CHCTL0_CHEN11,                                                 /*!< memory test channel enable bit 11 */
    MTC_CHCTL0_CHEN12,                                                 /*!< memory test channel enable bit 12 */
    MTC_CHCTL0_CHEN13,                                                 /*!< memory test channel enable bit 13 */
    MTC_CHCTL0_CHEN14,                                                 /*!< memory test channel enable bit 14 */
    MTC_CHCTL0_CHEN15,                                                 /*!< memory test channel enable bit 15 */
    MTC_CHCTL0_CHEN16,                                                 /*!< memory test channel enable bit 16 */
    MTC_CHCTL0_CHEN17,                                                 /*!< memory test channel enable bit 17 */
    MTC_CHCTL0_CHEN18,                                                 /*!< memory test channel enable bit 18 */
    MTC_CHCTL0_CHEN19,                                                 /*!< memory test channel enable bit 19 */
    MTC_CHCTL0_CHEN20,                                                 /*!< memory test channel enable bit 20 */
    MTC_CHCTL0_CHEN21,                                                 /*!< memory test channel enable bit 21 */
    MTC_CHCTL0_CHEN22,                                                 /*!< memory test channel enable bit 22 */
    MTC_CHCTL0_CHEN23,                                                 /*!< memory test channel enable bit 23 */
    MTC_CHCTL0_CHEN24,                                                 /*!< memory test channel enable bit 24 */
    MTC_CHCTL0_CHEN25,                                                 /*!< memory test channel enable bit 25 */
    MTC_CHCTL0_CHEN26,                                                 /*!< memory test channel enable bit 26 */
    MTC_CHCTL0_CHEN27,                                                 /*!< memory test channel enable bit 27 */
    MTC_CHCTL0_CHEN28,                                                 /*!< memory test channel enable bit 28 */
    MTC_CHCTL0_CHEN29,                                                 /*!< memory test channel enable bit 29 */
    MTC_CHCTL0_CHEN30,                                                 /*!< memory test channel enable bit 30 */
    MTC_CHCTL0_CHEN31,                                                 /*!< memory test channel enable bit 31 */
    /* MTC_CHCTL1 */
    MTC_CHCTL1_CHEN32,                                                 /*!< memory test channel enable bit 32 */
    MTC_CHCTL1_CHEN33,                                                 /*!< memory test channel enable bit 33 */
    MTC_CHCTL1_CHEN34,                                                 /*!< memory test channel enable bit 34 */
    MTC_CHCTL1_CHEN35,                                                 /*!< memory test channel enable bit 35 */
    MTC_CHCTL1_CHEN36,                                                 /*!< memory test channel enable bit 36 */
    MTC_CHCTL1_CHEN37,                                                 /*!< memory test channel enable bit 37 */
    MTC_CHCTL1_CHEN38,                                                 /*!< memory test channel enable bit 38 */
    MTC_CHCTL1_CHEN39,                                                 /*!< memory test channel enable bit 39 */
    MTC_CHCTL1_CHEN40,                                                 /*!< memory test channel enable bit 40 */
    MTC_CHCTL1_CHEN41,                                                 /*!< memory test channel enable bit 41 */
    MTC_CHCTL1_CHEN42,                                                 /*!< memory test channel enable bit 42 */
    MTC_CHCTL1_CHEN43,                                                 /*!< memory test channel enable bit 43 */
    MTC_CHCTL1_CHEN44,                                                 /*!< memory test channel enable bit 44 */
    MTC_CHCTL1_CHEN45,                                                 /*!< memory test channel enable bit 45 */
    MTC_CHCTL1_CHEN46,                                                 /*!< memory test channel enable bit 46 */
    MTC_CHCTL1_CHEN47,                                                 /*!< memory test channel enable bit 47 */
    MTC_CHCTL1_CHEN48,                                                 /*!< memory test channel enable bit 48 */
    MTC_CHCTL1_CHEN49,                                                 /*!< memory test channel enable bit 49 */
    MTC_CHCTL1_CHEN50,                                                 /*!< memory test channel enable bit 50 */
    MTC_CHCTL1_CHEN51,                                                 /*!< memory test channel enable bit 51 */
    MTC_CHCTL1_CHEN52,                                                 /*!< memory test channel enable bit 52 */
    MTC_CHCTL1_CHEN53,                                                 /*!< memory test channel enable bit 53 */
    MTC_CHCTL1_CHEN54,                                                 /*!< memory test channel enable bit 54 */
    MTC_CHCTL1_CHEN55,                                                 /*!< memory test channel enable bit 55 */
    MTC_CHCTL1_CHEN56,                                                 /*!< memory test channel enable bit 56 */
    MTC_CHCTL1_CHEN57,                                                 /*!< memory test channel enable bit 57 */
    MTC_CHCTL1_CHEN58,                                                 /*!< memory test channel enable bit 58 */
    MTC_CHCTL1_CHEN59,                                                 /*!< memory test channel enable bit 59 */
    MTC_CHCTL1_CHEN60                                                  /*!< memory test channel enable bit 60 */
} mtc_channel_enum;


/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check MTC ECC error mode */
#define NOT_MTC_ERR_MODE(mode)         (((mode) != EDCMOD_ECC) &&((mode) != EDCMOD_EDC) && ((mode) != EDCMOD_EDC_ECC))

/* check MTC error bit */
#define MTC_BIT_HIGH_VALUE             ((uint32_t)0x0000009FU)        /*!< maximum bit value */
#define NOT_MTC_BIT(value)             ((MTC_BIT_HIGH_VALUE < (value)))

#endif

/* function declarations */
/* mtc deinit */
void mtc_deinit(void);
/* enable global memory test */
void mtc_enable(void);
/* disable global memory test */
void mtc_disable(void);
/* select EDC error bits generation mode */
void mtc_error_mode(uint8_t mode);
/* enable memory test channel x */
void mtc_channel_enable(mtc_channel_enum channel);
/* disable memory test channel x */
void mtc_channel_disable(mtc_channel_enum channel);
/* configure sigle error bit */
void mtc_inject_single_bit(uint16_t u16bitpos);
/* configure multi error bit */
void mtc_inject_multi_bit(uint16_t u16bitpos1, uint16_t u16bitpos2);
/* TMR enable */
void mtc_tmr_enable(void);
/* TMR disable */
void mtc_tmr_disable(void);
/* get TMR flag  */
FlagStatus mtc_tmr_flag_get(void);
/* TMR flag clear  */
void mtc_tmr_flag_clear(void);

#endif /* GD32A7XX_MTC_H */
