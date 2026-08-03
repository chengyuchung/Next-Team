/*!
    \file    gd32a7xx_wwdgt.h
    \brief   definitions for the WWDGT

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

#ifndef GD32A7XX_WWDGT_H
#define GD32A7XX_WWDGT_H

#include "gd32a7xx.h"

/* WWDGT definitions */
#define WWDGT0                          WWDGT_BASE                                       /*!< WWDGT0 base address */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define WWDGT1                          (WWDGT_BASE + 0x0000B000U)                        /*!< WWDGT1 base address */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* registers definitions */
#define WWDGT_CTL(wwdgtx)               REG32((wwdgtx) + 0x00000000U)                    /*!< WWDGT control register */
#define WWDGT_CFG(wwdgtx)               REG32((wwdgtx) + 0x00000004U)                    /*!< WWDGT configuration register */
#define WWDGT_STAT(wwdgtx)              REG32((wwdgtx) + 0x00000008U)                    /*!< WWDGT status register */
#define WWDGT_ALMSTAT(wwdgtx)           REG32((wwdgtx) + 0x0000000CU)                    /*!< WWDGT ALARM Status register */
#define WWDGT_ALMSTATM(wwdgtx)          REG32((wwdgtx) + 0x00000010U)                    /*!< WWDGT ALARM Status mask register */

/* bits definitions */
/* WWDGT_CTL */
#define WWDGT_CTL_CNT                   BITS(0,6)                                        /*!< WWDGT counter value */
#define WWDGT_CTL_WDGTEN                BIT(7)                                           /*!< WWDGT counter enable */

/* WWDGT_CFG */
#define WWDGT_CFG_WIN                   BITS(0,6)                                        /*!< WWDGT counter window value */
#define WWDGT_CFG_PSC                   (BITS(7,8) | BITS(16,18))                        /*!< WWDGT prescaler divider value */
#define WWDGT_CFG_EWIE                  BIT(9)                                           /*!< WWDGT early wakeup interrupt enable */

/* WWDGT_STAT */
#define WWDGT_STAT_EWIF                 BIT(0)                                           /*!< WWDGT early wakeup interrupt flag */
#define WWDGT_STAT_CNT_NREF             BIT(31)                                          /*!< WWDGT count cannot updata flag */

/* WWDGT_ALMSTAT */
#define WWDGT_ALMSTAT_NAERR             BIT(0)                                           /*!< WWDGT cannot be activated error flag */
#define WWDGT_ALMSTAT_EWIERR            BIT(1)                                           /*!< Early wakeup interrupt cannot be generated normally error flag */

/* WWDGT_ALMSTATM */
#define WWDGT_ALMSTAT_EWIEM             BIT(1)                                           /*!< EWIERR status mask bit */
#define WWDGT_ALMSTAT_NAEM              BIT(0)                                           /*!< NAERR status mask bit */

/* constants definitions */
#define CFG_PSC(regval)                 ((BITS(7,8) & ((uint32_t)(regval) << 7U)) | (BITS(16,18) & ((uint32_t)(regval) << 14U)))   /*!< write value to WWDGT_CFG_PSC bit field */

#define WWDGT_CFG_PSC_DIV1              ((uint32_t)CFG_PSC(0))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/1 */
#define WWDGT_CFG_PSC_DIV2              ((uint32_t)CFG_PSC(1))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/2 */
#define WWDGT_CFG_PSC_DIV4              ((uint32_t)CFG_PSC(2))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/4 */
#define WWDGT_CFG_PSC_DIV8              ((uint32_t)CFG_PSC(3))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/8 */
#define WWDGT_CFG_PSC_DIV16             ((uint32_t)CFG_PSC(4))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/16 */
#define WWDGT_CFG_PSC_DIV32             ((uint32_t)CFG_PSC(5))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/32 */
#define WWDGT_CFG_PSC_DIV64             ((uint32_t)CFG_PSC(6))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/64 */
#define WWDGT_CFG_PSC_DIV128            ((uint32_t)CFG_PSC(7))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/128 */
#define WWDGT_CFG_PSC_DIV256            ((uint32_t)CFG_PSC(8))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/256 */
#define WWDGT_CFG_PSC_DIV512            ((uint32_t)CFG_PSC(9))                           /*!< the time base of WWDGT = (WWDGT_CLK/4096)/512 */
#define WWDGT_CFG_PSC_DIV1024           ((uint32_t)CFG_PSC(10))                          /*!< the time base of WWDGT = (WWDGT_CLK/4096)/1024 */
#define WWDGT_CFG_PSC_DIV2048           ((uint32_t)CFG_PSC(11))                          /*!< the time base of WWDGT = (WWDGT_CLK/4096)/2048 */
#define WWDGT_CFG_PSC_DIV4096           ((uint32_t)CFG_PSC(12))                          /*!< the time base of WWDGT = (WWDGT_CLK/4096)/4096 */
#define WWDGT_CFG_PSC_DIV8192           ((uint32_t)CFG_PSC(13))                          /*!< the time base of WWDGT = (WWDGT_CLK/4096)/8192 */
#define WWDGT_CFG_PSC_DIV16384          ((uint32_t)CFG_PSC(14))                          /*!< the time base of WWDGT = (WWDGT_CLK/4096)/16384 */
#define WWDGT_CFG_PSC_DIV32768          ((uint32_t)CFG_PSC(15))                          /*!< the time base of WWDGT = (WWDGT_CLK/4096)/32768 */
#define WWDGT_CFG_PSC_DIV65536          ((uint32_t)CFG_PSC(16))                          /*!< the time base of WWDGT = (WWDGT_CLK/4096)/65536 */
#define WWDGT_CFG_PSC_DIV131072         ((uint32_t)CFG_PSC(17))                          /*!< the time base of WWDGT = (WWDGT_CLK/4096)/131072 */

typedef enum {
    WWDGT_FLAG_NO_ERR = 0,
    WWDGT_FLAG_ERR    = 1
} wwdgt_error_flag_enum;

/* WWDGT_CTL register value */
#define CTL_CNT(regval)                 (BITS(0,6) & ((uint32_t)(regval) << 0U))         /*!< write value to WWDGT_CTL_CNT bit field */
/* WWDGT_CFG register value */
#define CFG_WIN(regval)                 (BITS(0,6) & ((uint32_t)(regval) << 0U))         /*!< write value to WWDGT_CFG_WIN bit field */

#define WWDGT_TIMEOUT                   ((uint32_t)0x000FFFFFU)                          /*!< WWDGT register write timeout */
/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check peripherals */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_WWDGT_PERIPH(periph)        (((periph) != WWDGT0) && ((periph) != WWDGT1))
#else
#define NOT_WWDGT_PERIPH(periph)      ((periph) != WWDGT0)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* check the counter */
#define COUNTER_LOW_VALUE               ((uint32_t)0x00000040U)                          /*!< minimum counter value */
#define COUNTER_HIGH_VALUE              ((uint32_t)0x0000007FU)                          /*!< maximum counter value */
#define NOT_WWDGT_COUNTER(counter)      ((COUNTER_LOW_VALUE > (counter)) || (COUNTER_HIGH_VALUE < (counter)))

/* check the window value */
#define WWDWND_LOW_VALUE                ((uint32_t)0x00000040U)                          /*!< minimum window value */
#define WWDWND_HIGH_VALUE               ((uint32_t)0x0000007FU)                          /*!< maximum window value */
#define NOT_WWDGT_WINDOW(window)        ((WWDWND_LOW_VALUE > (window)) || (WWDWND_HIGH_VALUE < (window)))

/* check WWDGT interrupt flag status */
#define NOT_WWDGT_PSC_VALUE(prescaler)  (((prescaler) != WWDGT_CFG_PSC_DIV1) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV2) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV4) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV8) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV16) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV32) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV64) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV128) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV256) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV512) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV1024) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV2048) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV4096) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV8192) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV16384) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV32768) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV65536) && \
                                        ((prescaler) != WWDGT_CFG_PSC_DIV131072))

/* check WWDGT STAT flag  */
#define NOT_WWDGT_STAT_FLAG(err_flag)   (((err_flag) != WWDGT_STAT_EWIF) && ((err_flag) != WWDGT_STAT_CNT_NREF))

/* check WWDGT error flag  */
#define NOT_WWDGT_ERR_FLAG(err_flag)    (((err_flag) != WWDGT_ALMSTAT_NAERR) && ((err_flag) != WWDGT_ALMSTAT_EWIERR))
#endif
/* function declarations */
/* reset the WWDGT configuration */
ErrStatus wwdgt_deinit(uint32_t wwdgt_periph);
/* start the WWDGT counter */
ErrStatus wwdgt_enable(uint32_t wwdgt_periph);

/* configure the WWDGT counter value */
ErrStatus wwdgt_counter_update(uint32_t wwdgt_periph, uint16_t counter_value);
/* configure counter value, window value, and prescaler divider value */
ErrStatus wwdgt_config(uint32_t wwdgt_periph, uint16_t counter, uint16_t window, uint32_t prescaler);

/* check early wakeup interrupt state of WWDGT */
FlagStatus wwdgt_flag_get(uint32_t wwdgt_periph, uint32_t flag);
/* clear early wakeup interrupt state of WWDGT */
void wwdgt_flag_clear(uint32_t wwdgt_periph);
/* enable early wakeup interrupt of WWDGT */
void wwdgt_interrupt_enable(uint32_t wwdgt_periph);

/* check early wakeup interrupt cannot be generated normally error flag and WWDGT cannot be activated error flag. */
FlagStatus wwdgt_error_flag_get(uint32_t wwdgt_periph, uint32_t err_flag);
/* clear early wakeup interrupt cannot be generated normally error flag and WWDGT cannot be activated error flag. */
void wwdgt_error_flag_clear(uint32_t wwdgt_periph, uint32_t err_flag);
/* mask early wakeup interrupt cannot be generated normally and WWDGT cannot be activated error flag. */
void wwdgt_flag_mask(uint32_t wwdgt_periph, uint32_t err_flag);
/* unmask early wakeup interrupt cannot be generated normally and WWDGT cannot be activated error flag. */
void wwdgt_flag_unmask(uint32_t wwdgt_periph, uint32_t err_flag);
#endif /* GD32A7XX_WWDGT_H */
