/*!
    \file    gd32a7xx_mcmu.h
    \brief   definitions for the MCMU

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
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#ifndef GD32A7XX_MCMU_H
#define GD32A7XX_MCMU_H

#include "gd32a7xx.h"

/* PMU definitions */
#define MCMUA                       MCMU_BASE                       /*!< MCMUA base address */
#define MCMUB                       (MCMU_BASE+0x00000400U)         /*!< MCMUB base address */

/* registers definitions */
#define MCMU_PAR(mcmux)             REG32((mcmux) + 0x00000004U)    /*!< Parameter register */
#define MCMU_CTL(mcmux)             REG32((mcmux) + 0x00000008U)    /*!< Control register */
#define MCMU_STAT(mcmux)            REG32((mcmux) + 0x0000000CU)    /*!< Status register */
#define MCMU_SCTL(mcmux)            REG32((mcmux) + 0x00000100U)    /*!< Signal control register */
#define MCMU_SSTAT(mcmux)           REG32((mcmux) + 0x00000104U)    /*!< Signal status register */
#define MCMU_NINTEN(mcmux)          REG32((mcmux) + 0x00000110U)    /*!< Normal interrupt enable register */
#define MCMU_NINTCTL(mcmux)         REG32((mcmux) + 0x00000114U)    /*!< Normal interrupt control register */
#define MCMU_NINTSTAT(mcmux)        REG32((mcmux) + 0x00000118U)    /*!< Normal interrupt Status register */
#define MCMU_TINTCTL(mcmux)         REG32((mcmux) + 0x00000120U)    /*!< Transmit Interrupt Control register */
#define MCMU_TINTSTAT(mcmux)        REG32((mcmux) + 0x00000124U)    /*!< Transmit Interrupt Status register */
#define MCMU_RINTCTL(mcmux)         REG32((mcmux) + 0x00000128U)    /*!< Receive Interrupt Control register */
#define MCMU_RINTSTAT(mcmux)        REG32((mcmux) + 0x0000012CU)    /*!< Receive Interrupt Status register */
#define MCMU_TDATA(mcmux,chy)       REG32((mcmux) + 0x00000200U + (chy) * 0x04U)   /*!< Transmit data register */
#define MCMU_RDATA(mcmux,chy)       REG32((mcmux) + 0x00000280U + (chy) * 0x04U)   /*!< Receive data register */
#define MCMU_PERRSTAT(mcmux)        REG32((mcmux) + 0x00000300U)   /*!< Parity Error Status register */
#define MCMU_PERRFE(mcmux)          REG32((mcmux) + 0x00000304U)   /*!< Parity Error fault enable register */
#define MCMU_TMRFACS(mcmux)         REG32((mcmux) + 0x00000308U)   /*!< TMR fault control and status register */

/* bits definitions */
/* MCMU_PAR */
#define MCMU_PAR_TRNUM                BITS(0,7)                     /*!< The number of transmit registers */
#define MCMU_PAR_RRNUM                BITS(8,15)                    /*!< The number of receive registers */
#define MCMU_PAR_NINTNUM              BITS(16,23)                   /*!< The number of normal interrupt requests available */
#define MCMU_PAR_SIGNALNUM            BITS(24,31)                   /*!< The number of signal bits */

/* MCMU_CTL */
#define MCMU_CTL_SWRST                BIT(0)                        /*!< Software reset MCMU */

/* MCMU_STAT */
#define MCMU_STAT_RSTSF               BIT(0)                        /*!< MCMU reset state flag */
#define MCMU_STAT_RSTIF               BIT(1)                        /*!< MCMU reset interrupt flag */
#define MCMU_STAT_EVF                 BIT(2)                        /*!< MCMU event flag */
#define MCMU_STAT_SUF                 BIT(3)                        /*!< MCMU Signal update flag */
#define MCMU_STAT_NIF                 BIT(4)                        /*!< MCMU Normal interrupt flag */
#define MCMU_STAT_TEF                 BIT(5)                        /*!< MCMU Transmit empty flag */
#define MCMU_STAT_RNEF                BIT(6)                        /*!< MCMU Receive not empty flag */

/* MCMU_SCTL */
#define MCMU_SCTL_SIGNAL0             BIT(0)                        /*!< signal0 to the other MCMU */
#define MCMU_SCTL_SIGNAL1             BIT(1)                        /*!< signal1 to the other MCMU */
#define MCMU_SCTL_SIGNAL2             BIT(2)                        /*!< signal2 to the other MCMU */

/* MCMU_SSTAT */
#define MCMU_STAT_SIGNAL0S            BIT(0)                        /*!< signal0 from the other MCMU */
#define MCMU_STAT_SIGNAL1S            BIT(1)                        /*!< signal1 from the other MCMU */
#define MCMU_STAT_SIGNAL2S            BIT(2)                        /*!< signal2 from the other MCMU */

/* MCMU_NINTEN */
#define MCMU_NINTEN_NIE0              BIT(0)                        /*!< Enable normal interrupt */

/* MCMU_NINTCTL */
#define MCMU_NINTCTL_NIR0             BIT(0)                        /*!< normal interrupt request */

/* MCMU_NINTSTAT */
#define MCMU_NINTSTAT_NIF0            BIT(0)                        /*!< normal interrupt flag */

/* MCMU_TINTCTL */
#define MCMU_TINTCTL_TIE0             BIT(0)                        /*!< transmit 0 interrupt enable */
#define MCMU_TINTCTL_TIE1             BIT(1)                        /*!< transmit 1 interrupt enable */
#define MCMU_TINTCTL_TIE2             BIT(2)                        /*!< transmit 2 interrupt enable */
#define MCMU_TINTCTL_TIE3             BIT(3)                        /*!< transmit 3 interrupt enable */

/* MCMU_TINTSTAT */
#define MCMU_TINTSTAT_TEF0            BIT(0)                        /*!< transmit register 0 empty */
#define MCMU_TINTSTAT_TEF1            BIT(1)                        /*!< transmit register 1 empty */
#define MCMU_TINTSTAT_TEF2            BIT(2)                        /*!< transmit register 2 empty */
#define MCMU_TINTSTAT_TEF3            BIT(3)                        /*!< transmit register 3 empty */

/* MCMU_RINTCTL */
#define MCMU_RINTCTL_RIE0             BIT(0)                        /*!< receive 0 interrupt enable */
#define MCMU_RINTCTL_RIE1             BIT(1)                        /*!< receive 1 interrupt enable */
#define MCMU_RINTCTL_RIE2             BIT(2)                        /*!< receive 2 interrupt enable */
#define MCMU_RINTCTL_RIE3             BIT(3)                        /*!< receive 3 interrupt enable */

/* MCMU_RINTSTAT */
#define MCMU_RINTSTAT_RNEF0           BIT(0)                        /*!< receive register 0 not empty */
#define MCMU_RINTSTAT_RNEF1           BIT(1)                        /*!< receive register 1 not empty */
#define MCMU_RINTSTAT_RNEF2           BIT(2)                        /*!< receive register 2 not empty */
#define MCMU_RINTSTAT_RNEF3           BIT(3)                        /*!< receive register 3 not empty */

/* MCMU_TDATA */
#define MCMU_TDATA_TDATA              BITS(0,31)                    /*!< Transmit Data */

/* MCMU_RDATA */
#define MCMU_RDATA_RDATA              BITS(0,31)                    /*!< Receive Data */

/* MCMU_PERRSTAT */
#define MCMU_PERRSTAT_PERR0F          BIT(0)                        /*!< receive register 0 parity check error flag */
#define MCMU_PERRSTAT_PERR1F          BIT(1)                        /*!< receive register 1 parity check error flag */
#define MCMU_PERRSTAT_PERR2F          BIT(2)                        /*!< receive register 2 parity check error flag */
#define MCMU_PERRSTAT_PERR3F          BIT(3)                        /*!< receive register 3 parity check error flag */

/* MCMU_PERRFE */
#define MCMU_PERRFE_PERR0FE           BIT(0)                        /*!< enable receive register 0 parity check error connection to FMU */
#define MCMU_PERRFE_PERR1FE           BIT(1)                        /*!< enable receive register 1 parity check error connection to FMU */
#define MCMU_PERRFE_PERR2FE           BIT(2)                        /*!< enable receive register 2 parity check error connection to FMU */
#define MCMU_PERRFE_PERR3FE           BIT(3)                        /*!< enable receive register 3 parity check error connection to FMU */

/* MCMU_TMRFACS */
#define MCMU_TMRFACS_SCTLIE           BIT(1)                        /*!< enable TMR fault alarm of SCTL register to FMU */
#define MCMU_TMRFACS_NINTIE           BIT(2)                        /*!< enable TMR fault alarm of NINTEN and NINTCTL registers to FMU */
#define MCMU_TMRFACS_TCTLIE           BIT(3)                        /*!< enable TMR fault alarm of TINTCTL register to FMU */
#define MCMU_TMRFACS_RCTLIE           BIT(4)                        /*!< enable TMR fault alarm of RINTCTL register to FMU */
#define MCMU_TMRFACS_SCTLIF           BIT(17)                       /*!< TMR fault alarm flag of SCTL register */
#define MCMU_TMRFACS_NINTIF           BIT(18)                       /*!< TMR fault alarm flag of NINTEN and NINTCTL registers */
#define MCMU_TMRFACS_TCTLIF           BIT(19)                       /*!< TMR fault alarm flag of TINTCTL register */
#define MCMU_TMRFACS_RCTLIF           BIT(20)                       /*!< TMR fault alarm flag of RINTCTL register */

/* constants definitions */
/* MCMU parameter type */
typedef enum {
    MCMU_PAR_TRANSMIT = 0U,         /*!< The number of transmit registers */
    MCMU_PAR_RECEIVE,               /*!< The number of receive registers */
    MCMU_PAR_NORMAL,                /*!< The number of normal interrupt requests available */
    MCMU_PAR_SIGNAL                 /*!< The number of signal bits */
} mcmu_parameter_enum;

/* define the MCMU bit position and its register index offset REG2[31:22] BIT2[21:16] REG[15:6] BIT[5:0] */
#define MCMU_REGIDX_BIT(regidx, bitpos)     (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define MCMU_REG_VAL(mcmux, offset)        (REG32((mcmux) + (((uint32_t)(offset) & 0x0000FFC0U) >> 6)))
#define MCMU_BIT_POS(val)                   ((uint32_t)(val) & 0x0000001FU)
#define MCMU_REGIDX_BIT2(regidx2, bitpos2, regidx, bitpos)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16) |\
                                                              (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define MCMU_REG_VAL2(mcmux, offset)       (REG32((mcmux) + (((uint32_t)(offset) & 0xFFC00000U) >> 22)))
#define MCMU_BIT_POS2(val)                  (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define MCMU_CTL_REG_OFFSET         ((uint32_t)0x008U)        /*!< Control register offset */
#define MCMU_STAT_REG_OFFSET        ((uint32_t)0x00CU)        /*!< Status register offset */
#define MCMU_SCTL_REG_OFFSET        ((uint32_t)0x100U)        /*!< Signal control register offset */
#define MCMU_SSTAT_REG_OFFSET       ((uint32_t)0x104U)        /*!< Signal status register offset */
#define MCMU_NINTEN_REG_OFFSET      ((uint32_t)0x110U)        /*!< Normal interrupt enable register offset */
#define MCMU_NINTCTL_REG_OFFSET     ((uint32_t)0x114U)        /*!< Normal interrupt control register offset */
#define MCMU_NINTSTAT_REG_OFFSET    ((uint32_t)0x118U)        /*!< Normal interrupt Status register offset */
#define MCMU_TINTCTL_REG_OFFSET     ((uint32_t)0x120U)        /*!< Transmit Interrupt Control register offset */
#define MCMU_TINTSTAT_REG_OFFSET    ((uint32_t)0x124U)        /*!< Transmit Interrupt Status register offset */
#define MCMU_RINTCTL_REG_OFFSET     ((uint32_t)0x128U)        /*!< Receive Interrupt Control register offset */
#define MCMU_RINTSTAT_REG_OFFSET    ((uint32_t)0x12CU)        /*!< Receive Interrupt Status register offset */

/* enable or disable MCMU interrupt */
typedef enum {
    /* MCMU_NINTEN register */
    MCMU_INT_NIF0               = MCMU_REGIDX_BIT(MCMU_NINTEN_REG_OFFSET, 0U),          /*!< normal interrupt */
    /* MCMU_TINTCTL register */
    MCMU_INT_TEF0               = MCMU_REGIDX_BIT(MCMU_TINTCTL_REG_OFFSET, 0U),         /*!< transmit interrupt 0 */
    MCMU_INT_TEF1               = MCMU_REGIDX_BIT(MCMU_TINTCTL_REG_OFFSET, 1U),         /*!< transmit interrupt 1 */
    MCMU_INT_TEF2               = MCMU_REGIDX_BIT(MCMU_TINTCTL_REG_OFFSET, 2U),         /*!< transmit interrupt 2 */
    MCMU_INT_TEF3               = MCMU_REGIDX_BIT(MCMU_TINTCTL_REG_OFFSET, 3U),         /*!< transmit interrupt 3 */
    /* MCMU_RINTCTL register */
    MCMU_INT_RNEF0              = MCMU_REGIDX_BIT(MCMU_RINTCTL_REG_OFFSET, 0U),         /*!< receive interrupt 0 */
    MCMU_INT_RNEF1              = MCMU_REGIDX_BIT(MCMU_RINTCTL_REG_OFFSET, 1U),         /*!< receive interrupt 1 */
    MCMU_INT_RNEF2              = MCMU_REGIDX_BIT(MCMU_RINTCTL_REG_OFFSET, 2U),         /*!< receive interrupt 2 */
    MCMU_INT_RNEF3              = MCMU_REGIDX_BIT(MCMU_RINTCTL_REG_OFFSET, 3U)          /*!< receive interrupt 3 */
} mcmu_interrupt_enum;

/* MCMU flags */
typedef enum {
    /* MCMU_STAT register */
    MCMU_FLAG_RSTSF     = MCMU_REGIDX_BIT(MCMU_STAT_REG_OFFSET, 0U),        /*!< MCMU reset state flag */
    MCMU_FLAG_RSTIF     = MCMU_REGIDX_BIT(MCMU_STAT_REG_OFFSET, 1U),        /*!< MCMU reset interrupt flag */
    MCMU_FLAG_EVF       = MCMU_REGIDX_BIT(MCMU_STAT_REG_OFFSET, 2U),        /*!< MCMU side event flag */
    MCMU_FLAG_SUF       = MCMU_REGIDX_BIT(MCMU_STAT_REG_OFFSET, 3U),        /*!< MCMU Signal update flag */
    MCMU_FLAG_NIF       = MCMU_REGIDX_BIT(MCMU_STAT_REG_OFFSET, 4U),        /*!< MCMU Normal interrupt flag */
    MCMU_FLAG_TEF       = MCMU_REGIDX_BIT(MCMU_STAT_REG_OFFSET, 5U),        /*!< MCMU Transmit empty flag */
    MCMU_FLAG_RNEF      = MCMU_REGIDX_BIT(MCMU_STAT_REG_OFFSET, 6U),        /*!< MCMU Receive not empty flag */
    /* MCMU_SCTL register */
    MCMU_FLAG_SIGNAL0   = MCMU_REGIDX_BIT(MCMU_SCTL_REG_OFFSET, 0U),        /*!< signal0 to the other MCMU */
    MCMU_FLAG_SIGNAL1   = MCMU_REGIDX_BIT(MCMU_SCTL_REG_OFFSET, 1U),        /*!< signal1 to the other MCMU */
    MCMU_FLAG_SIGNAL2   = MCMU_REGIDX_BIT(MCMU_SCTL_REG_OFFSET, 2U),        /*!< signal2 to the other MCMU */
    /* MCMU_SSTAT register */
    MCMU_FLAG_SIGNAL0S  = MCMU_REGIDX_BIT(MCMU_SSTAT_REG_OFFSET, 0U),       /*!< signal0 from the other MCMU */
    MCMU_FLAG_SIGNAL1S  = MCMU_REGIDX_BIT(MCMU_SSTAT_REG_OFFSET, 1U),       /*!< signal1 from the other MCMU */
    MCMU_FLAG_SIGNAL2S  = MCMU_REGIDX_BIT(MCMU_SSTAT_REG_OFFSET, 2U),       /*!< signal2 from the other MCMU */
    /* MCMU_NINTCTL register */
    MCMU_FLAG_NIR0      = MCMU_REGIDX_BIT(MCMU_NINTCTL_REG_OFFSET, 0U),     /*!< normal interrupt request (only be cleared by the other MCMU) */
    /* MCMU_NINTSTAT register */
    MCMU_FLAG_NIF0      = MCMU_REGIDX_BIT(MCMU_NINTSTAT_REG_OFFSET, 0U),    /*!< normal interrupt flag from the other MCMU */
    /* MCMU_TINTSTAT register */
    MCMU_FLAG_TEF0      = MCMU_REGIDX_BIT(MCMU_TINTSTAT_REG_OFFSET, 0U),    /*!< transmit data register 0 empty flag */
    MCMU_FLAG_TEF1      = MCMU_REGIDX_BIT(MCMU_TINTSTAT_REG_OFFSET, 1U),    /*!< transmit data register 1 empty flag */
    MCMU_FLAG_TEF2      = MCMU_REGIDX_BIT(MCMU_TINTSTAT_REG_OFFSET, 2U),    /*!< transmit data register 2 empty flag */
    MCMU_FLAG_TEF3      = MCMU_REGIDX_BIT(MCMU_TINTSTAT_REG_OFFSET, 3U),    /*!< transmit data register 3 empty flag */
    /* MCMU_RINTSTAT register */
    MCMU_FLAG_RNEF0     = MCMU_REGIDX_BIT(MCMU_RINTSTAT_REG_OFFSET, 0U),    /*!< receive data register 0 not empty */
    MCMU_FLAG_RNEF1     = MCMU_REGIDX_BIT(MCMU_RINTSTAT_REG_OFFSET, 1U),    /*!< receive data register 1 not empty */
    MCMU_FLAG_RNEF2     = MCMU_REGIDX_BIT(MCMU_RINTSTAT_REG_OFFSET, 2U),    /*!< receive data register 2 not empty */
    MCMU_FLAG_RNEF3     = MCMU_REGIDX_BIT(MCMU_RINTSTAT_REG_OFFSET, 3U)     /*!< receive data register 3 not empty */
} mcmu_flag_enum;

/* MCMU interrupt flags */
typedef enum {
    /* MCMU_NINTSTAT register */
    MCMU_INT_FLAG_NIF0          = MCMU_REGIDX_BIT2(MCMU_NINTEN_REG_OFFSET, 0U, MCMU_NINTSTAT_REG_OFFSET, 0U),     /*!< normal interrupt flag from the other MCMU */
    /* MCMU_TINTCTL register */
    MCMU_INT_FLAG_TEF0          = MCMU_REGIDX_BIT2(MCMU_TINTCTL_REG_OFFSET, 0U, MCMU_TINTSTAT_REG_OFFSET, 0U),      /*!< transmit data register 0 empty flag */
    MCMU_INT_FLAG_TEF1          = MCMU_REGIDX_BIT2(MCMU_TINTCTL_REG_OFFSET, 1U, MCMU_TINTSTAT_REG_OFFSET, 1U),      /*!< transmit data register 1 empty flag */
    MCMU_INT_FLAG_TEF2          = MCMU_REGIDX_BIT2(MCMU_TINTCTL_REG_OFFSET, 2U, MCMU_TINTSTAT_REG_OFFSET, 2U),      /*!< transmit data register 2 empty flag */
    MCMU_INT_FLAG_TEF3          = MCMU_REGIDX_BIT2(MCMU_TINTCTL_REG_OFFSET, 3U, MCMU_TINTSTAT_REG_OFFSET, 3U),      /*!< transmit data register 3 empty flag */
    /* MCMU_RINTCTL register */
    MCMU_INT_FLAG_RNEF0         = MCMU_REGIDX_BIT2(MCMU_RINTCTL_REG_OFFSET, 0U, MCMU_RINTSTAT_REG_OFFSET, 0U),      /*!< receive data register 0 not empty flag */
    MCMU_INT_FLAG_RNEF1         = MCMU_REGIDX_BIT2(MCMU_RINTCTL_REG_OFFSET, 1U, MCMU_RINTSTAT_REG_OFFSET, 1U),      /*!< receive data register 1 not empty flag */
    MCMU_INT_FLAG_RNEF2         = MCMU_REGIDX_BIT2(MCMU_RINTCTL_REG_OFFSET, 2U, MCMU_RINTSTAT_REG_OFFSET, 2U),      /*!< receive data register 2 not empty flag */
    MCMU_INT_FLAG_RNEF3         = MCMU_REGIDX_BIT2(MCMU_RINTCTL_REG_OFFSET, 3U, MCMU_RINTSTAT_REG_OFFSET, 3U)       /*!< receive data register 3 not empty flag */
} mcmu_interrupt_flag_enum;

/* MCMU signal */
#define MCMU_SIGNAL0        MCMU_SCTL_SIGNAL0                   /*!< MCMU signal0 to the other MCMU */
#define MCMU_SIGNAL1        MCMU_SCTL_SIGNAL1                   /*!< MCMU signal1 to the other MCMU */
#define MCMU_SIGNAL2        MCMU_SCTL_SIGNAL2                   /*!< MCMU signal2 to the other MCMU */

/* MCMU TMR fault alarm enable */
#define MCMU_TMR_ALARM_SCTL          MCMU_TMRFACS_SCTLIE        /* TMR fault alarm of SCTL register to FMU */
#define MCMU_TMR_ALARM_NINT          MCMU_TMRFACS_NINTIE        /* TMR fault alarm of NINTEN and NINTCTL registers to FMU */
#define MCMU_TMR_ALARM_TINT          MCMU_TMRFACS_TCTLIE        /* TMR fault alarm of TINTCTL register to FMU */
#define MCMU_TMR_ALARM_RINT          MCMU_TMRFACS_RCTLIE        /* TMR fault alarm of RINTCTL register to FMU */

/* MCMU TMR fault flags */
#define MCMU_TMR_FLAG_SCTL            MCMU_TMRFACS_SCTLIF       /* TMR fault alarm flag of SCTL register */
#define MCMU_TMR_FLAG_NINT            MCMU_TMRFACS_NINTIF       /* TMR fault alarm flag of NINTEN and NINTCTL registers */
#define MCMU_TMR_FLAG_TINT            MCMU_TMRFACS_TCTLIF       /* TMR fault alarm flag of TINTCTL register */
#define MCMU_TMR_FLAG_RINT            MCMU_TMRFACS_RCTLIF       /* TMR fault alarm flag of RINTCTL register */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check peripherals */
#define NOT_MCMU_PERIPH(periph)          (((periph) != MCMUA) && ((periph) != MCMUB))

/* check parameter type */
#define NOT_MCMU_PARAMETER(para)         (((para) != MCMU_PAR_TRANSMIT)   && \
                                          ((para) != MCMU_PAR_RECEIVE)    && \
                                          ((para) != MCMU_PAR_NORMAL)     && \
                                          ((para) != MCMU_PAR_SIGNAL))

/* check signal */
#define NOT_MCMU_SIGNAL(signal)         (((signal) != MCMU_SIGNAL0) && \
                                         ((signal) != MCMU_SIGNAL1) && \
                                         ((signal) != MCMU_SIGNAL2))

/* check Transmit/Receive data channel  */
#define MCMU_DATA_CHANNEL_HIGH            (uint32_t)3U
#define NOT_MCMU_DATA_CHANNEL(ch)       ((ch) > MCMU_DATA_CHANNEL_HIGH)

/* check MCMU get flag */
#define NOT_MCMU_GET_FLAG(flag)         (((flag) != MCMU_FLAG_RSTSF)    && \
                                         ((flag) != MCMU_FLAG_RSTIF)    && \
                                         ((flag) != MCMU_FLAG_EVF)      && \
                                         ((flag) != MCMU_FLAG_SUF)      && \
                                         ((flag) != MCMU_FLAG_NIF)      && \
                                         ((flag) != MCMU_FLAG_TEF)      && \
                                         ((flag) != MCMU_FLAG_RNEF)     && \
                                         ((flag) != MCMU_FLAG_SIGNAL0)  && \
                                         ((flag) != MCMU_FLAG_SIGNAL1)  && \
                                         ((flag) != MCMU_FLAG_SIGNAL2)  && \
                                         ((flag) != MCMU_FLAG_SIGNAL0S) && \
                                         ((flag) != MCMU_FLAG_SIGNAL1S) && \
                                         ((flag) != MCMU_FLAG_SIGNAL2S) && \
                                         ((flag) != MCMU_FLAG_NIR0)     && \
                                         ((flag) != MCMU_FLAG_NIF0)     && \
                                         ((flag) != MCMU_FLAG_TEF0)     && \
                                         ((flag) != MCMU_FLAG_TEF1)     && \
                                         ((flag) != MCMU_FLAG_TEF2)     && \
                                         ((flag) != MCMU_FLAG_TEF3)     && \
                                         ((flag) != MCMU_FLAG_RNEF0)    && \
                                         ((flag) != MCMU_FLAG_RNEF1)    && \
                                         ((flag) != MCMU_FLAG_RNEF2)    && \
                                         ((flag) != MCMU_FLAG_RNEF3))

/* check MCMU clear flag */
#define NOT_MCMU_CLEAR_FLAG(flag)        (((flag) != MCMU_FLAG_RSTIF)   && \
                                          ((flag) != MCMU_FLAG_NIF0))

/* check MCMU interrupt */
#define NOT_MCMU_INTERRUPT(interrupt)   (((interrupt) != MCMU_INT_NIF0)    && \
                                         ((interrupt) != MCMU_INT_TEF0)    && \
                                         ((interrupt) != MCMU_INT_TEF1)    && \
                                         ((interrupt) != MCMU_INT_TEF2)    && \
                                         ((interrupt) != MCMU_INT_TEF3)    && \
                                         ((interrupt) != MCMU_INT_RNEF0)   && \
                                         ((interrupt) != MCMU_INT_RNEF1)   && \
                                         ((interrupt) != MCMU_INT_RNEF2)   && \
                                         ((interrupt) != MCMU_INT_RNEF3))

/* check MCMU interrupt get flag */
#define NOT_MCMU_INTERRUPT_GET_FLAG(flag)     (((flag) != MCMU_INT_FLAG_NIF0)     && \
                                               ((flag) != MCMU_INT_FLAG_TEF0)     && \
                                               ((flag) != MCMU_INT_FLAG_TEF1)     && \
                                               ((flag) != MCMU_INT_FLAG_TEF2)     && \
                                               ((flag) != MCMU_INT_FLAG_TEF3)     && \
                                               ((flag) != MCMU_INT_FLAG_RNEF0)    && \
                                               ((flag) != MCMU_INT_FLAG_RNEF1)    && \
                                               ((flag) != MCMU_INT_FLAG_RNEF2)    && \
                                               ((flag) != MCMU_INT_FLAG_RNEF3))

/* check MCMU interrupt clear flag */
#define NOT_MCMU_INTERRUPT_CLEAR_FLAG(flag)   ((flag) != MCMU_INT_FLAG_NIF0)

/* check MCMU TMR fault alarm */
#define NOT_MCMU_TMR_ALARM(alarm)             (((alarm) != MCMU_TMR_ALARM_SCTL)   && \
                                               ((alarm) != MCMU_TMR_ALARM_NINT)   && \
                                               ((alarm) != MCMU_TMR_ALARM_TINT)   && \
                                               ((alarm) != MCMU_TMR_ALARM_RINT))

/* check MCMU TMR fault flag */
#define NOT_MCMU_TMR_FLAG(flag)               (((flag) != MCMU_TMR_FLAG_SCTL)   && \
                                               ((flag) != MCMU_TMR_FLAG_NINT)   && \
                                               ((flag) != MCMU_TMR_FLAG_TINT)   && \
                                               ((flag) != MCMU_TMR_FLAG_RINT))
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* get available number of MCMU parameter */
uint8_t mcmu_parameter_get(uint32_t mcmu_periph, mcmu_parameter_enum para_type);
/* reset MCMU register */
void mcmu_reset(uint32_t mcmu_periph);

/* set the signal to the other MCMU */
void mcmu_signal_set(uint32_t mcmu_periph, uint32_t signal);
/* clear the signal to the other MCMU */
void mcmu_signal_clear(uint32_t mcmu_periph, uint32_t signal);

/* generate the normal interrupt to the other MCMU */
void mcmu_normal_interrupt_request(uint32_t mcmu_periph);

/* transmit data */
void mcmu_transmit_data(uint32_t mcmu_periph, uint32_t chy, uint32_t data);
/* receive data */
uint32_t mcmu_receive_data(uint32_t mcmu_periph, uint32_t chy);

/* mcmu interrupt enable */
void mcmu_interrupt_enable(uint32_t mcmu_periph, mcmu_interrupt_enum interrupt);
/* mcmu interrupt disable */
void mcmu_interrupt_disable(uint32_t mcmu_periph, mcmu_interrupt_enum interrupt);
/* get mcmu flag status */
FlagStatus mcmu_flag_get(uint32_t mcmu_periph, mcmu_flag_enum flag);
/* mcmu flag clear */
void mcmu_flag_clear(uint32_t mcmu_periph, mcmu_flag_enum flag);
/* get mcmu interrupt flag status */
FlagStatus mcmu_interrupt_flag_get(uint32_t mcmu_periph, mcmu_interrupt_flag_enum int_flag);
/* clear mcmu interrupt flag */
void mcmu_interrupt_flag_clear(uint32_t mcmu_periph, mcmu_interrupt_flag_enum int_flag);

/* parity error report to FMU */
void mcmu_parity_error_report_enable(uint32_t mcmu_periph, uint32_t chy);
/* parity error did not report to FMU */
void mcmu_parity_error_report_disable(uint32_t mcmu_periph, uint32_t chy);
/* parity error state get */
FlagStatus mcmu_parity_error_get(uint32_t mcmu_periph, uint32_t chy);
/* parity error clear */
void mcmu_parity_error_clear(uint32_t mcmu_periph, uint32_t chy);

/* tmr error report to FMU */
void mcmu_tmr_error_report_enable(uint32_t mcmu_periph, uint32_t tmr);
/* tmr error did not report to FMU */
void mcmu_tmr_error_report_disable(uint32_t mcmu_periph, uint32_t tmr);
/* tmr error flag get */
FlagStatus mcmu_tmr_error_get(uint32_t mcmu_periph, uint32_t tmr_flag);
/* tmr error flag clear */
void mcmu_tmr_error_clear(uint32_t mcmu_periph, uint32_t tmr_flag);

#endif /* GD32A7XX_MCMU_H */
#endif /* #if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
