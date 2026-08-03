/*!
    \file    gd32a7xx_cmp.h
    \brief   definitions for the CMP

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

#ifndef GD32A7XX_CMP_H
#define GD32A7XX_CMP_H

#include "gd32a7xx.h"

/* CMP definitions */
#define CMP0                                     (CMP_BASE + 0x00001000U)       /*!< CMP0 base address */
#define CMP1                                     (CMP_BASE + 0x00000000U)       /*!< CMP1 base address */

/* registers definitions */
#define CMP_CS(CMPx)                             REG32((CMPx) + 0x00000000U)    /*!< CMPx control and status register */

#define CMP_RRCTL(CMPx)                          REG32((CMPx) + 0x00000010U)    /*!< CMPx Round robin control register 0 */
#define CMP_RRCHCTL(CMPx)                        REG32((CMPx) + 0x00000014U)    /*!< CMPx Round robin control register 1 */
#define CMP_RRCOMO(CMPx)                         REG32((CMPx) + 0x00000018U)    /*!< CMPx Round robin control and status register */
#define CMP_RRCOMF(CMPx)                         REG32((CMPx) + 0x0000001CU)    /*!< CMPx Round robin status register */
#define CMP_RRTCTL(CMPx)                         REG32((CMPx) + 0x00000020U)    /*!< CMPx Round robin trigger timer control register */
#define CMP_RRTTRGV(CMPx)                        REG32((CMPx) + 0x00000024U)    /*!< CMPx Round robin trigger timer value register */
#define CMP_RRTCNT(CMPx)                         REG32((CMPx) + 0x00000028U)    /*!< CMPx Round robin timer counter register */

/* bits definitions */
/* CMPx_CS */
#define CMP_CS_CMPXEN                            BIT(0)                         /*!< CMPx enable */
#define CMP_CS_CMPXM                             BITS(2,3)                      /*!< CMPx mode */
#define CMP_CS_CMPXMESEL                         BITS(4,6)                      /*!< CMP_IM external input selection */
#define CMP_CS_CMPXMISEL                         BITS(7,9)                      /*!< CMP_IM internal input selection */
#define CMP_CS_CMPXPESEL                         BITS(10,12)                    /*!< CMP_IP external input selection */
#define CMP_CS_CMPXPSEL                          BIT(13)                        /*!< CMP_IP input selection */
#define CMP_CS_CMPXPL                            BIT(15)                        /*!< CMPx output polarity */
#define CMP_CS_CMPXHST                           BITS(16,17)                    /*!< CMPx hysteresis */
#define CMP_CS_CMPXBLK                           BITS(18,20)                    /*!< CMPx output blanking source */
#define CMP_CS_CMPXBEN                           BIT(22)                        /*!< CMPx scaler bridge enable bit */
#define CMP_CS_CMPXSEN                           BIT(23)                        /*!< CMPx voltage input scaler */
#define CMP_CS_CMPXOSEL                          BITS(24,25)                    /*!< CMPx output selection */
#define CMP_CS_CMPXMESEL3                        BIT(26)                        /*!< CMP_IM external input selection */
#define CMP_CS_CMPXPESEL3                        BIT(27)                        /*!< CMP_IP external input selection */
#define CMP_CS_CMPXO                             BIT(30)                        /*!< CMPx output state */
#define CMP_CS_CMPXLK                            BIT(31)                        /*!< CMPx lock */

/* CMP_RRCTL */
#define CMP_RRCTL_RREN                           BIT(0)                         /*!< CMP round robin enable */
#define CMP_RRCTL_RRSAMCFG                       BITS(8,9)                      /*!< CMP round robin sample clocks configuration */
#define CMP_RRCTL_RRTINIT                        BITS(16,21)                    /*!< CMP round robin time initialization */
#define CMP_RRCTL_RRIE                           BIT(31)                        /*!< interrupt enable for round robin */

/* CMP_RRCHCTL */
#define CMP_RRCHCTL_NSPECH0EN                    BIT(0)                         /*!< CMP round robin non-specified mux port channel 0 enable */
#define CMP_RRCHCTL_NSPECH1EN                    BIT(1)                         /*!< CMP round robin non-specified mux port channel 1 enable */
#define CMP_RRCHCTL_NSPECH2EN                    BIT(2)                         /*!< CMP round robin non-specified mux port channel 2 enable */
#define CMP_RRCHCTL_NSPECH3EN                    BIT(3)                         /*!< CMP round robin non-specified mux port channel 3 enable */
#define CMP_RRCHCTL_NSPECH4EN                    BIT(4)                         /*!< CMP round robin non-specified mux port channel 4 enable */
#define CMP_RRCHCTL_NSPECH5EN                    BIT(5)                         /*!< CMP round robin non-specified mux port channel 5 enable */
#define CMP_RRCHCTL_NSPECH6EN                    BIT(6)                         /*!< CMP round robin non-specified mux port channel 6 enable */
#define CMP_RRCHCTL_NSPECH7EN                    BIT(7)                         /*!< CMP round robin non-specified mux port channel 7 enable */
#define CMP_RRCHCTL_NSPECH8EN                    BIT(8)                         /*!< CMP round robin non-specified mux port channel 8 enable(only for CMP0) */
#define CMP_RRCHCTL_NSPECH9EN                    BIT(9)                         /*!< CMP round robin non-specified mux port channel 9 enable(only for CMP0) */
#define CMP_RRCHCTL_NSPECH10EN                   BIT(10)                        /*!< CMP round robin non-specified mux port channel 10 enable(only for CMP0) */
#define CMP_RRCHCTL_SPEPS                        BIT(16)                        /*!< CMP round robin specified port selection */
#define CMP_RRCHCTL_RRSPECHS                     BITS(20,23)                    /*!< CMP round robin specified channel selection */

/* CMP_RRCOMO */
#define CMP_RRCOMO_CH0COMO                       BIT(0)                         /*!< CMP round robin channel 0 compare output state */
#define CMP_RRCOMO_CH1COMO                       BIT(1)                         /*!< CMP round robin channel 1 compare output state */
#define CMP_RRCOMO_CH2COMO                       BIT(2)                         /*!< CMP round robin channel 2 compare output state */
#define CMP_RRCOMO_CH3COMO                       BIT(3)                         /*!< CMP round robin channel 3 compare output state */
#define CMP_RRCOMO_CH4COMO                       BIT(4)                         /*!< CMP round robin channel 4 compare output state */
#define CMP_RRCOMO_CH5COMO                       BIT(5)                         /*!< CMP round robin channel 5 compare output state */
#define CMP_RRCOMO_CH6COMO                       BIT(6)                         /*!< CMP round robin channel 6 compare output state */
#define CMP_RRCOMO_CH7COMO                       BIT(7)                         /*!< CMP round robin channel 7 compare output state */
#define CMP_RRCOMO_CH8COMO                       BIT(8)                         /*!< CMP round robin channel 8 compare output state(only for CMP0) */
#define CMP_RRCOMO_CH9COMO                       BIT(9)                         /*!< CMP round robin channel 9 compare output state(only for CMP0) */
#define CMP_RRCOMO_CH10COMO                      BIT(10)                        /*!< CMP round robin channel 10 compare output state(only for CMP0) */

/* CMP_RRCOMF */
#define CMP_RRCOMF_CH0COMF                       BIT(0)                         /*!< CMP round robin channel 0 compare result flag */
#define CMP_RRCOMF_CH1COMF                       BIT(1)                         /*!< CMP round robin channel 1 compare result flag */
#define CMP_RRCOMF_CH2COMF                       BIT(2)                         /*!< CMP round robin channel 2 compare result flag */
#define CMP_RRCOMF_CH3COMF                       BIT(3)                         /*!< CMP round robin channel 3 compare result flag */
#define CMP_RRCOMF_CH4COMF                       BIT(4)                         /*!< CMP round robin channel 4 compare result flag */
#define CMP_RRCOMF_CH5COMF                       BIT(5)                         /*!< CMP round robin channel 5 compare result flag */
#define CMP_RRCOMF_CH6COMF                       BIT(6)                         /*!< CMP round robin channel 6 compare result flag */
#define CMP_RRCOMF_CH7COMF                       BIT(7)                         /*!< CMP round robin channel 7 compare result flag */
#define CMP_RRCOMF_CH8COMF                       BIT(8)                         /*!< CMP round robin channel 8 compare result flag(only for CMP0) */
#define CMP_RRCOMF_CH9COMF                       BIT(9)                         /*!< CMP round robin channel 9 compare result flag(only for CMP0) */
#define CMP_RRCOMF_CH10COMF                      BIT(10)                        /*!< CMP round robin channel 10 compare result flag(only for CMP0) */

/* CMP_RRTCTL */
#define CMP_RRTCTL_RRCEN                          BIT(0)                        /*!< CMP round robin counter enable */
#define CMP_RRTCTL_RRTRGEN                        BIT(1)                        /*!< CMP round robin trigger enable */
#define CMP_RRTCTL_CLRCNT                         BIT(2)                        /*!< clear the RRCNT[31:0] value */
#define CMP_RRTCTL_UPVAL                          BIT(3)                        /*!< update the RRTVAL[31:0] value */

/* constants definitions */
/* CMP operating mode */
#define CS_CMPXM(regval)                         (BITS(2,3) & ((uint32_t)(regval) << 2U))
#define CMP_MODE_HIGHSPEED                       CS_CMPXM(0)                                            /*!< CMP mode high speed */
#define CMP_MODE_MIDDLESPEED                     CS_CMPXM(1)                                            /*!< CMP mode middle speed */
#define CMP_MODE_LOWSPEED                        CS_CMPXM(3)                                            /*!< CMP mode low speed */

/* CMP hysteresis */
#define CS_CMPXHST(regval)                       (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define CMP_HYSTERESIS_NO                        CS_CMPXHST(0)                                          /*!< CMP output no hysteresis */
#define CMP_HYSTERESIS_LOW                       CS_CMPXHST(1)                                          /*!< CMP output low hysteresis */
#define CMP_HYSTERESIS_MIDDLE                    CS_CMPXHST(2)                                          /*!< CMP output middle hysteresis */
#define CMP_HYSTERESIS_HIGH                      CS_CMPXHST(3)                                          /*!< CMP output high hysteresis */

/* CMP inverting input */
#define CS_CMPXMISEL(regval)                     (BITS(7,9) & ((uint32_t)(regval) << 7U))
#define CS_CMPXMESEL(regval)                     (BITS(4,6) & ((uint32_t)(regval) << 4U))
#define CS_CMPXMESEL3(regval)                    (BIT(26) & ((uint32_t)(regval) << 26U))
#define CMP_INVERTING_INPUT_1_4VREFINT           CS_CMPXMISEL(0)                                        /*!< CMP inverting input 1/4 Vrefint */
#define CMP_INVERTING_INPUT_1_2VREFINT           CS_CMPXMISEL(1)                                        /*!< CMP inverting input 1/2 Vrefint */
#define CMP_INVERTING_INPUT_3_4VREFINT           CS_CMPXMISEL(2)                                        /*!< CMP inverting input 3/4 Vrefint */
#define CMP_INVERTING_INPUT_VREFINT              CS_CMPXMISEL(3)                                        /*!< CMP inverting input Vrefint */
#define CMP_INVERTING_INPUT_DAC_OUT              CS_CMPXMISEL(4)                                        /*!< CMP inverting input DAC0_OUT0 for CMP0 or DAC1_OUT0 for CMP1 */
#define CMP_INVERTING_INPUT_EXTERNAL_INPUT       CS_CMPXMISEL(5)                                        /*!< CMP inverting input when use round robin */
#define CMP_INVERTING_INPUT_PF5_PC6              (CS_CMPXMISEL(5) | CS_CMPXMESEL(0))                    /*!< CMP inverting input PF5 for CMP0 or PC6 for CMP1 */
#define CMP_INVERTING_INPUT_PF4_PG7              (CS_CMPXMISEL(5) | CS_CMPXMESEL(1))                    /*!< CMP inverting input PF4 for CMP0 or PG7 for CMP1 */
#define CMP_INVERTING_INPUT_PA2_PJ11             (CS_CMPXMISEL(5) | CS_CMPXMESEL(2))                    /*!< CMP inverting input PA2 for CMP0 or PJ11 for CMP1 */
#define CMP_INVERTING_INPUT_PC2_PA14             (CS_CMPXMISEL(5) | CS_CMPXMESEL(3))                    /*!< CMP inverting input PC2 for CMP0 or PA14 for CMP1 */
#define CMP_INVERTING_INPUT_PA1_PK1              (CS_CMPXMISEL(5) | CS_CMPXMESEL(4))                    /*!< CMP inverting input PA1 for CMP0 or PK1 for CMP1 */
#define CMP_INVERTING_INPUT_PF3_PK2              (CS_CMPXMISEL(5) | CS_CMPXMESEL(5))                    /*!< CMP inverting input PF3 for CMP0 or PK2 for CMP1 */
#define CMP_INVERTING_INPUT_PH2_PG2              (CS_CMPXMISEL(5) | CS_CMPXMESEL(6))                    /*!< CMP inverting input PH2 for CMP0 or PG2 for CMP1 */
#define CMP_INVERTING_INPUT_PH3_PG5              (CS_CMPXMISEL(5) | CS_CMPXMESEL(7))                    /*!< CMP inverting input PH3 for CMP0 or PG5 for CMP1 */
#define CMP_INVERTING_INPUT_PA14                 (CS_CMPXMISEL(5) | CS_CMPXMESEL(0) | CS_CMPXMESEL3(1)) /*!< CMP inverting input PA14(only for CMP0) */
#define CMP_INVERTING_INPUT_PC6                  (CS_CMPXMISEL(5) | CS_CMPXMESEL(1) | CS_CMPXMESEL3(1)) /*!< CMP inverting input PC6(only for CMP0) */
#define CMP_INVERTING_INPUT_PG7                  (CS_CMPXMISEL(5) | CS_CMPXMESEL(2) | CS_CMPXMESEL3(1)) /*!< CMP inverting input PG7(only for CMP0) */

/* CMP noninverting input */
#define CS_CMPXPSEL(regval)                      (BIT(13) & ((uint32_t)(regval) << 13U))
#define CS_CMPXPESEL(regval)                     (BITS(10,12) & ((uint32_t)(regval) << 10U))
#define CS_CMPXPESEL3(regval)                    (BIT(27) & ((uint32_t)(regval) << 27U))
#define CMP_NONINVERTING_DAC_OUT                 CS_CMPXPSEL(1)                                         /*!< CMP noninverting input DAC0_OUT0 for CMP0 or DAC1_OUT0 for CMP1 */
#define CMP_NONINVERTING_INPUT_PF5_PC6           (CS_CMPXPSEL(0) | CS_CMPXPESEL(0))                     /*!< CMP noninverting input PF5 for CMP0 or PC6 for CMP1 */
#define CMP_NONINVERTING_INPUT_PF4_PG7           (CS_CMPXPSEL(0) | CS_CMPXPESEL(1))                     /*!< CMP noninverting input PF4 for CMP0 or PG7 for CMP1 */
#define CMP_NONINVERTING_INPUT_PA2_PJ11          (CS_CMPXPSEL(0) | CS_CMPXPESEL(2))                     /*!< CMP noninverting input PA2 for CMP0 or PJ11 for CMP1 */
#define CMP_NONINVERTING_INPUT_PC2_PA14          (CS_CMPXPSEL(0) | CS_CMPXPESEL(3))                     /*!< CMP noninverting input PC2 for CMP0 or PA14 for CMP1 */
#define CMP_NONINVERTING_INPUT_PA1_PK1           (CS_CMPXPSEL(0) | CS_CMPXPESEL(4))                     /*!< CMP noninverting input PA1 for CMP0 or PK1 for CMP1 */
#define CMP_NONINVERTING_INPUT_PF3_PK2           (CS_CMPXPSEL(0) | CS_CMPXPESEL(5))                     /*!< CMP noninverting input PF3 for CMP0 or PK2 for CMP1 */
#define CMP_NONINVERTING_INPUT_PH2_PG2           (CS_CMPXPSEL(0) | CS_CMPXPESEL(6))                     /*!< CMP noninverting input PH2 for CMP0 or PG2 for CMP1 */
#define CMP_NONINVERTING_INPUT_PH3_PG5           (CS_CMPXPSEL(0) | CS_CMPXPESEL(7))                     /*!< CMP noninverting input PH3 for CMP0 or PG5 for CMP1 */
#define CMP_NONINVERTING_INPUT_PA14              (CS_CMPXPSEL(0) | CS_CMPXPESEL(0) | CS_CMPXPESEL3(1))  /*!< CMP noninverting input PA14(only for CMP0) */
#define CMP_NONINVERTING_INPUT_PC6               (CS_CMPXPSEL(0) | CS_CMPXPESEL(1) | CS_CMPXPESEL3(1))  /*!< CMP noninverting input PC6(only for CMP0) */
#define CMP_NONINVERTING_INPUT_PG7               (CS_CMPXPSEL(0) | CS_CMPXPESEL(2) | CS_CMPXPESEL3(1))  /*!< CMP noninverting input PG7(only for CMP0) */

/* CMP output polarity*/
#define CS_CMPXPL(regval)                        (BIT(15) & ((uint32_t)(regval) << 15U))
#define CMP_OUTPUT_POLARITY_NONINVERTED          CS_CMPXPL(0)                                           /*!< CMP output not inverted */
#define CMP_OUTPUT_POLARITY_INVERTED             CS_CMPXPL(1)                                           /*!< CMP output inverted */

/* CMP blanking source */
#define CS_CMPXBLK(regval)                       (BITS(18,20) & ((uint32_t)(regval) << 18U))
#define CMP_BLANKING_NONE                        CS_CMPXBLK(0)                                          /*!< CMP no blanking source */
#define CMP_BLANKING_TIMER0_OC1                  CS_CMPXBLK(1)                                          /*!< CMP TIMER0_CH1 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER7_OC1                  CS_CMPXBLK(2)                                          /*!< CMP TIMER7_CH1 output compare signal selected as blanking source */
#define CMP_BLANKING_TIMER1_OC1                  CS_CMPXBLK(3)                                          /*!< CMP TIMER1_CH1 output compare signal selected as blanking source */

/* CMP output */
#define CS_CMPXOSEL(regval)                      (BITS(24,25) & ((uint32_t)(regval) << 24U))
#define CMP_OUTPUT_NONE                          CS_CMPXOSEL(0)                                         /*!< CMP output none */
#define CMP_OUTPUT_TIMER0_IC0_TIMER20_IC0        CS_CMPXOSEL(1)                                         /*!< CMP0 output TIMER0_CH0 input capture, CMP1 output TIMER20_CH0 input capture */
#define CMP_OUTPUT_TIMER7_IC0_TIMER60_IC0        CS_CMPXOSEL(2)                                         /*!< CMP0 output TIMER7_CH0 input capture, CMP1 output TIMER60_CH0 input capture */

/* CMP output level */
#define CMP_OUTPUTLEVEL_HIGH                     ((uint32_t)0x00000001U)                                /*!< comparator output high */
#define CMP_OUTPUTLEVEL_LOW                      ((uint32_t)0x00000000U)                                /*!< comparator output low */

/* CMP round robin specified channel definitions */
#define RRCHCTL_RRSPECHS(regval)                 (BITS(20,23) & ((uint32_t)(regval) << 20))
#define CMP_RRSPE_CHANNEL_0                      RRCHCTL_RRSPECHS(0)                                    /*!< CMP round robin channel 0 */
#define CMP_RRSPE_CHANNEL_1                      RRCHCTL_RRSPECHS(1)                                    /*!< CMP round robin channel 1 */
#define CMP_RRSPE_CHANNEL_2                      RRCHCTL_RRSPECHS(2)                                    /*!< CMP round robin channel 2 */
#define CMP_RRSPE_CHANNEL_3                      RRCHCTL_RRSPECHS(3)                                    /*!< CMP round robin channel 3 */
#define CMP_RRSPE_CHANNEL_4                      RRCHCTL_RRSPECHS(4)                                    /*!< CMP round robin channel 4 */
#define CMP_RRSPE_CHANNEL_5                      RRCHCTL_RRSPECHS(5)                                    /*!< CMP round robin channel 5 */
#define CMP_RRSPE_CHANNEL_6                      RRCHCTL_RRSPECHS(6)                                    /*!< CMP round robin channel 6 */
#define CMP_RRSPE_CHANNEL_7                      RRCHCTL_RRSPECHS(7)                                    /*!< CMP round robin channel 7 */
#define CMP_RRSPE_CHANNEL_8                      RRCHCTL_RRSPECHS(8)                                    /*!< CMP round robin channel 8 */
#define CMP_RRSPE_CHANNEL_9                      RRCHCTL_RRSPECHS(9)                                    /*!< CMP round robin channel 9 */
#define CMP_RRSPE_CHANNEL_10                     RRCHCTL_RRSPECHS(10)                                   /*!< CMP round robin channel 10 */

/* CMP round robin non-specified channel definitions */
#define CMP_RRNONSPE_CHANNEL_0                   ((uint32_t)0x00000001U)                                /*!< CMP round robin channel 0 */
#define CMP_RRNONSPE_CHANNEL_1                   ((uint32_t)0x00000002U)                                /*!< CMP round robin channel 1 */
#define CMP_RRNONSPE_CHANNEL_2                   ((uint32_t)0x00000004U)                                /*!< CMP round robin channel 2 */
#define CMP_RRNONSPE_CHANNEL_3                   ((uint32_t)0x00000008U)                                /*!< CMP round robin channel 3 */
#define CMP_RRNONSPE_CHANNEL_4                   ((uint32_t)0x00000010U)                                /*!< CMP round robin channel 4 */
#define CMP_RRNONSPE_CHANNEL_5                   ((uint32_t)0x00000020U)                                /*!< CMP round robin channel 5 */
#define CMP_RRNONSPE_CHANNEL_6                   ((uint32_t)0x00000040U)                                /*!< CMP round robin channel 6 */
#define CMP_RRNONSPE_CHANNEL_7                   ((uint32_t)0x00000080U)                                /*!< CMP round robin channel 7 */
#define CMP_RRNONSPE_CHANNEL_8                   ((uint32_t)0x00000100U)                                /*!< CMP round robin channel 8 */
#define CMP_RRNONSPE_CHANNEL_9                   ((uint32_t)0x00000200U)                                /*!< CMP round robin channel 9 */
#define CMP_RRNONSPE_CHANNEL_10                  ((uint32_t)0x00000400U)                                /*!< CMP round robin channel 10 */

/* CMP round robin specified port selection */
#define RRCHCTL_SPEPS(regval)                     (BIT(16) & ((uint32_t)(regval) << 16))
#define CMP_RRINVERTING_PORT                      RRCHCTL_SPEPS(0)                                      /*!< select the inverting port */
#define CMP_RRNONINVERTING_PORT                   RRCHCTL_SPEPS(1)                                      /*!< select the non-inverting port */

/* CMP round robin compare result flag */
#define CMP_FLAG_CH0COMF                         CMP_RRCOMF_CH0COMF                                     /*!< CMP round robin channel 0 compare result flag */
#define CMP_FLAG_CH1COMF                         CMP_RRCOMF_CH1COMF                                     /*!< CMP round robin channel 1 compare result flag */
#define CMP_FLAG_CH2COMF                         CMP_RRCOMF_CH2COMF                                     /*!< CMP round robin channel 2 compare result flag */
#define CMP_FLAG_CH3COMF                         CMP_RRCOMF_CH3COMF                                     /*!< CMP round robin channel 3 compare result flag */
#define CMP_FLAG_CH4COMF                         CMP_RRCOMF_CH4COMF                                     /*!< CMP round robin channel 4 compare result flag */
#define CMP_FLAG_CH5COMF                         CMP_RRCOMF_CH5COMF                                     /*!< CMP round robin channel 5 compare result flag */
#define CMP_FLAG_CH6COMF                         CMP_RRCOMF_CH6COMF                                     /*!< CMP round robin channel 6 compare result flag */
#define CMP_FLAG_CH7COMF                         CMP_RRCOMF_CH7COMF                                     /*!< CMP round robin channel 7 compare result flag */
#define CMP_FLAG_CH8COMF                         CMP_RRCOMF_CH8COMF                                     /*!< CMP round robin channel 8 compare result flag(only for CMP0) */
#define CMP_FLAG_CH9COMF                         CMP_RRCOMF_CH9COMF                                     /*!< CMP round robin channel 9 compare result flag(only for CMP0) */
#define CMP_FLAG_CH10COMF                        CMP_RRCOMF_CH10COMF                                    /*!< CMP round robin channel 10 compare result flag(only for CMP0) */

/* CMP round robin number of sample clocks */
#define RRCTL_RRSAMCFG(regval)                   (BITS(8,9) & ((uint32_t)(regval) << 8))
#define RRCTL_RRSAMCFG_0CLK                      RRCTL_RRSAMCFG(0)                                      /*!< round robin 0 sample clock */
#define RRCTL_RRSAMCFG_1CLK                      RRCTL_RRSAMCFG(1)                                      /*!< round robin 1 sample clock */
#define RRCTL_RRSAMCFG_2CLK                      RRCTL_RRSAMCFG(2)                                      /*!< round robin 2 sample clock */
#define RRCTL_RRSAMCFG_3CLK                      RRCTL_RRSAMCFG(3)                                      /*!< round robin 3 sample clock */

/* CMP round robin initialization delay */
#define RRCTL_RRTINIT(regval)                    (BITS(16,21) & ((uint32_t)(regval) << 16))
#define RRCTL_RRTINIT_1CLK                       RRCTL_RRTINIT(1)                                       /*!< round robin initialization delay 1 clock */
#define RRCTL_RRTINIT_2CLK                       RRCTL_RRTINIT(2)                                       /*!< round robin initialization delay 2 clock */
#define RRCTL_RRTINIT_3CLK                       RRCTL_RRTINIT(3)                                       /*!< round robin initialization delay 3 clock */
#define RRCTL_RRTINIT_4CLK                       RRCTL_RRTINIT(4)                                       /*!< round robin initialization delay 4 clock */
#define RRCTL_RRTINIT_5CLK                       RRCTL_RRTINIT(5)                                       /*!< round robin initialization delay 5 clock */
#define RRCTL_RRTINIT_6CLK                       RRCTL_RRTINIT(6)                                       /*!< round robin initialization delay 6 clock */
#define RRCTL_RRTINIT_7CLK                       RRCTL_RRTINIT(7)                                       /*!< round robin initialization delay 7 clock */
#define RRCTL_RRTINIT_8CLK                       RRCTL_RRTINIT(8)                                       /*!< round robin initialization delay 8 clock */
#define RRCTL_RRTINIT_9CLK                       RRCTL_RRTINIT(9)                                       /*!< round robin initialization delay 9 clock */
#define RRCTL_RRTINIT_10CLK                      RRCTL_RRTINIT(10)                                      /*!< round robin initialization delay 10 clock */
#define RRCTL_RRTINIT_11CLK                      RRCTL_RRTINIT(11)                                      /*!< round robin initialization delay 11 clock */
#define RRCTL_RRTINIT_12CLK                      RRCTL_RRTINIT(12)                                      /*!< round robin initialization delay 12 clock */
#define RRCTL_RRTINIT_13CLK                      RRCTL_RRTINIT(13)                                      /*!< round robin initialization delay 13 clock */
#define RRCTL_RRTINIT_14CLK                      RRCTL_RRTINIT(14)                                      /*!< round robin initialization delay 14 clock */
#define RRCTL_RRTINIT_15CLK                      RRCTL_RRTINIT(15)                                      /*!< round robin initialization delay 15 clock */
#define RRCTL_RRTINIT_16CLK                      RRCTL_RRTINIT(16)                                      /*!< round robin initialization delay 16 clock */
#define RRCTL_RRTINIT_17CLK                      RRCTL_RRTINIT(17)                                      /*!< round robin initialization delay 17 clock */
#define RRCTL_RRTINIT_18CLK                      RRCTL_RRTINIT(18)                                      /*!< round robin initialization delay 18 clock */
#define RRCTL_RRTINIT_19CLK                      RRCTL_RRTINIT(19)                                      /*!< round robin initialization delay 19 clock */
#define RRCTL_RRTINIT_20CLK                      RRCTL_RRTINIT(20)                                      /*!< round robin initialization delay 20 clock */
#define RRCTL_RRTINIT_21CLK                      RRCTL_RRTINIT(21)                                      /*!< round robin initialization delay 21 clock */
#define RRCTL_RRTINIT_22CLK                      RRCTL_RRTINIT(22)                                      /*!< round robin initialization delay 22 clock */
#define RRCTL_RRTINIT_23CLK                      RRCTL_RRTINIT(23)                                      /*!< round robin initialization delay 23 clock */
#define RRCTL_RRTINIT_24CLK                      RRCTL_RRTINIT(24)                                      /*!< round robin initialization delay 24 clock */
#define RRCTL_RRTINIT_25CLK                      RRCTL_RRTINIT(25)                                      /*!< round robin initialization delay 25 clock */
#define RRCTL_RRTINIT_26CLK                      RRCTL_RRTINIT(26)                                      /*!< round robin initialization delay 26 clock */
#define RRCTL_RRTINIT_27CLK                      RRCTL_RRTINIT(27)                                      /*!< round robin initialization delay 27 clock */
#define RRCTL_RRTINIT_28CLK                      RRCTL_RRTINIT(28)                                      /*!< round robin initialization delay 28 clock */
#define RRCTL_RRTINIT_29CLK                      RRCTL_RRTINIT(29)                                      /*!< round robin initialization delay 29 clock */
#define RRCTL_RRTINIT_30CLK                      RRCTL_RRTINIT(30)                                      /*!< round robin initialization delay 30 clock */
#define RRCTL_RRTINIT_31CLK                      RRCTL_RRTINIT(31)                                      /*!< round robin initialization delay 31 clock */
#define RRCTL_RRTINIT_32CLK                      RRCTL_RRTINIT(32)                                      /*!< round robin initialization delay 32 clock */
#define RRCTL_RRTINIT_33CLK                      RRCTL_RRTINIT(33)                                      /*!< round robin initialization delay 33 clock */
#define RRCTL_RRTINIT_34CLK                      RRCTL_RRTINIT(34)                                      /*!< round robin initialization delay 34 clock */
#define RRCTL_RRTINIT_35CLK                      RRCTL_RRTINIT(35)                                      /*!< round robin initialization delay 35 clock */
#define RRCTL_RRTINIT_36CLK                      RRCTL_RRTINIT(36)                                      /*!< round robin initialization delay 36 clock */
#define RRCTL_RRTINIT_37CLK                      RRCTL_RRTINIT(37)                                      /*!< round robin initialization delay 37 clock */
#define RRCTL_RRTINIT_38CLK                      RRCTL_RRTINIT(38)                                      /*!< round robin initialization delay 38 clock */
#define RRCTL_RRTINIT_39CLK                      RRCTL_RRTINIT(39)                                      /*!< round robin initialization delay 39 clock */
#define RRCTL_RRTINIT_40CLK                      RRCTL_RRTINIT(40)                                      /*!< round robin initialization delay 40 clock */
#define RRCTL_RRTINIT_41CLK                      RRCTL_RRTINIT(41)                                      /*!< round robin initialization delay 41 clock */
#define RRCTL_RRTINIT_42CLK                      RRCTL_RRTINIT(42)                                      /*!< round robin initialization delay 42 clock */
#define RRCTL_RRTINIT_43CLK                      RRCTL_RRTINIT(43)                                      /*!< round robin initialization delay 43 clock */
#define RRCTL_RRTINIT_44CLK                      RRCTL_RRTINIT(44)                                      /*!< round robin initialization delay 44 clock */
#define RRCTL_RRTINIT_45CLK                      RRCTL_RRTINIT(45)                                      /*!< round robin initialization delay 45 clock */
#define RRCTL_RRTINIT_46CLK                      RRCTL_RRTINIT(46)                                      /*!< round robin initialization delay 46 clock */
#define RRCTL_RRTINIT_47CLK                      RRCTL_RRTINIT(47)                                      /*!< round robin initialization delay 47 clock */
#define RRCTL_RRTINIT_48CLK                      RRCTL_RRTINIT(48)                                      /*!< round robin initialization delay 48 clock */
#define RRCTL_RRTINIT_49CLK                      RRCTL_RRTINIT(49)                                      /*!< round robin initialization delay 49 clock */
#define RRCTL_RRTINIT_50CLK                      RRCTL_RRTINIT(50)                                      /*!< round robin initialization delay 50 clock */
#define RRCTL_RRTINIT_51CLK                      RRCTL_RRTINIT(51)                                      /*!< round robin initialization delay 51 clock */
#define RRCTL_RRTINIT_52CLK                      RRCTL_RRTINIT(52)                                      /*!< round robin initialization delay 52 clock */
#define RRCTL_RRTINIT_53CLK                      RRCTL_RRTINIT(53)                                      /*!< round robin initialization delay 53 clock */
#define RRCTL_RRTINIT_54CLK                      RRCTL_RRTINIT(54)                                      /*!< round robin initialization delay 54 clock */
#define RRCTL_RRTINIT_55CLK                      RRCTL_RRTINIT(55)                                      /*!< round robin initialization delay 55 clock */
#define RRCTL_RRTINIT_56CLK                      RRCTL_RRTINIT(56)                                      /*!< round robin initialization delay 56 clock */
#define RRCTL_RRTINIT_57CLK                      RRCTL_RRTINIT(57)                                      /*!< round robin initialization delay 57 clock */
#define RRCTL_RRTINIT_58CLK                      RRCTL_RRTINIT(58)                                      /*!< round robin initialization delay 58 clock */
#define RRCTL_RRTINIT_59CLK                      RRCTL_RRTINIT(59)                                      /*!< round robin initialization delay 59 clock */
#define RRCTL_RRTINIT_60CLK                      RRCTL_RRTINIT(60)                                      /*!< round robin initialization delay 60 clock */
#define RRCTL_RRTINIT_61CLK                      RRCTL_RRTINIT(61)                                      /*!< round robin initialization delay 61 clock */
#define RRCTL_RRTINIT_62CLK                      RRCTL_RRTINIT(62)                                      /*!< round robin initialization delay 62 clock */
#define RRCTL_RRTINIT_63CLK                      RRCTL_RRTINIT(63)                                      /*!< round robin initialization delay 63 clock */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check CMP peripherals */
#define NOT_CMP_PERIPH(cmp_periph)                       (((cmp_periph) != CMP0) && ((cmp_periph) != CMP1))

/* check CMP operating mode */
#define NOT_CMP_OPERATING_MODE(operating_mode)           (((operating_mode) != CMP_MODE_HIGHSPEED)   && ((operating_mode) != CMP_MODE_MIDDLESPEED) && \
                                                         ((operating_mode) != CMP_MODE_LOWSPEED))

/* check CMP output hysteresis */
#define NOT_CMP_OUTPUT_HYSTERESIS(output_hysteresis)     (((output_hysteresis) != CMP_HYSTERESIS_NO)     && ((output_hysteresis) != CMP_HYSTERESIS_LOW) && \
                                                         ((output_hysteresis) != CMP_HYSTERESIS_MIDDLE) && ((output_hysteresis) != CMP_HYSTERESIS_HIGH))

/* check CMP inverting input */
#define NOT_CMP_INVERTING_INPUT(inverting_input)         (((inverting_input) != CMP_INVERTING_INPUT_1_4VREFINT) && ((inverting_input) != CMP_INVERTING_INPUT_1_2VREFINT) && \
                                                         ((inverting_input) != CMP_INVERTING_INPUT_3_4VREFINT) && ((inverting_input) != CMP_INVERTING_INPUT_VREFINT) && \
                                                         ((inverting_input) != CMP_INVERTING_INPUT_DAC_OUT)    && ((inverting_input) != CMP_INVERTING_INPUT_PF5_PC6) && \
                                                         ((inverting_input) != CMP_INVERTING_INPUT_PF4_PG7)    && ((inverting_input) != CMP_INVERTING_INPUT_PA2_PJ11) && \
                                                         ((inverting_input) != CMP_INVERTING_INPUT_PC2_PA14)   && ((inverting_input) != CMP_INVERTING_INPUT_PA1_PK1) && \
                                                         ((inverting_input) != CMP_INVERTING_INPUT_PF3_PK2)    && ((inverting_input) != CMP_INVERTING_INPUT_PH2_PG2) && \
                                                         ((inverting_input) != CMP_INVERTING_INPUT_PH3_PG5)    && ((inverting_input) != CMP_INVERTING_INPUT_PA14) && \
                                                         ((inverting_input) != CMP_INVERTING_INPUT_PC6)        && ((inverting_input) != CMP_INVERTING_INPUT_PG7))

/* check CMP noninverting input */
#define NOT_CMP_NONINVERTING_INPUT(noninverting_input)   (((noninverting_input) != CMP_NONINVERTING_DAC_OUT)        && ((noninverting_input) != CMP_NONINVERTING_INPUT_PF5_PC6) && \
                                                         ((noninverting_input) != CMP_NONINVERTING_INPUT_PF4_PG7)  && ((noninverting_input) != CMP_NONINVERTING_INPUT_PA2_PJ11) && \
                                                         ((noninverting_input) != CMP_NONINVERTING_INPUT_PC2_PA14) && ((noninverting_input) != CMP_NONINVERTING_INPUT_PA1_PK1) && \
                                                         ((noninverting_input) != CMP_NONINVERTING_INPUT_PF3_PK2)  && ((noninverting_input) != CMP_NONINVERTING_INPUT_PH2_PG2) && \
                                                         ((noninverting_input) != CMP_NONINVERTING_INPUT_PH3_PG5)  && ((noninverting_input) != CMP_NONINVERTING_INPUT_PA14) && \
                                                         ((noninverting_input) != CMP_NONINVERTING_INPUT_PC6)      && ((noninverting_input) != CMP_NONINVERTING_INPUT_PG7))

/* check CMP output polarity */
#define NOT_CMP_OUTPUT_POLARITY(output_polarity)         (((output_polarity) != CMP_OUTPUT_POLARITY_NONINVERTED) && ((output_polarity) != CMP_OUTPUT_POLARITY_INVERTED))

/* check CMP blanking source selection */
#define NOT_CMP_BLK_SOURCE_SEL(blanking_source)          (((blanking_source) != CMP_BLANKING_NONE)       && ((blanking_source) != CMP_BLANKING_TIMER0_OC1) && \
                                                         ((blanking_source) != CMP_BLANKING_TIMER7_OC1) && ((blanking_source) != CMP_BLANKING_TIMER1_OC1))

/* check CMP output selection */
#define NOT_CMP_OUTPUT_SELECTION(output_selection)       (((output_selection) != CMP_OUTPUT_NONE)       && ((output_selection) != CMP_OUTPUT_TIMER0_IC0_TIMER20_IC0) && \
                                                         ((output_selection) != CMP_OUTPUT_TIMER7_IC0_TIMER60_IC0))

/* check CMP round robin specified channel */
#define NOT_CMP_SPECIFIED_CHANNEL(specified_channel)     (((specified_channel) != CMP_RRSPE_CHANNEL_0)  && ((specified_channel) != CMP_RRSPE_CHANNEL_1) && \
                                                         ((specified_channel) != CMP_RRSPE_CHANNEL_2)  && ((specified_channel) != CMP_RRSPE_CHANNEL_3) && \
                                                         ((specified_channel) != CMP_RRSPE_CHANNEL_4)  && ((specified_channel) != CMP_RRSPE_CHANNEL_5) && \
                                                         ((specified_channel) != CMP_RRSPE_CHANNEL_6)  && ((specified_channel) != CMP_RRSPE_CHANNEL_7) && \
                                                         ((specified_channel) != CMP_RRSPE_CHANNEL_8)  && ((specified_channel) != CMP_RRSPE_CHANNEL_9) && \
                                                         ((specified_channel) != CMP_RRSPE_CHANNEL_10))

/* check CMP round robin non_specified channel */
#define CMP_RR_NONSPE_CHANNEL_HIGH                       ((uint32_t)0x000007FFU)
#define NOT_CMP_NONSPE_CHANNEL(non_specified_channel)    (CMP_RR_NONSPE_CHANNEL_HIGH < (non_specified_channel))

/* check CMP round robin specified port */
#define NOT_CMP_SPECIFIED_PORT(specified_port)           (((specified_port) != CMP_RRNONINVERTING_PORT) && ((specified_port) != CMP_RRINVERTING_PORT))

/* check CMP round robin sample clock */
#define NOT_CMP_SAMPLE_CLOCK(sample_clock)               (((sample_clock) != RRCTL_RRSAMCFG_0CLK) && ((sample_clock) != RRCTL_RRSAMCFG_1CLK) && \
                                                         ((sample_clock) != RRCTL_RRSAMCFG_2CLK) && ((sample_clock) != RRCTL_RRSAMCFG_3CLK))
/* check CMP round robin initialization delay clock */
#define CMP_RR_INIT_DELAY_HIGH                           ((uint32_t)0x003F0000U)
#define CMP_RR_INIT_DELAY_CLOCK(init_delay)              (CMP_RR_INIT_DELAY_HIGH < (init_delay))

#endif

/* function declarations */
/* initialization functions */
/* deinitialize comparator */
void cmp_deinit(uint32_t cmp_periph);
/* initialize comparator mode */
void cmp_mode_init(uint32_t cmp_periph, uint32_t operating_mode, uint32_t inverting_input, uint32_t output_hysteresis);
/* initialize comparator input */
void cmp_noninverting_input_select(uint32_t cmp_periph, uint32_t noninverting_input);
/* initialize comparator output */
void cmp_output_init(uint32_t cmp_periph, uint32_t output_selection, uint32_t output_polarity);
/* initialize comparator blanking function */
void cmp_blanking_init(uint32_t cmp_periph, uint32_t blanking_source_selection);
/* initialize comparator round robin clock */
void cmp_roundrobin_clock_init(uint32_t cmp_periph, uint32_t sample_clock, uint32_t init_delay);
/* initialize comparator round robin channel config */
void cmp_roundrobin_channel_config(uint32_t cmp_periph, uint32_t specified_port, uint32_t specified_channel, uint32_t non_specified_channel);
/* initialize comparator round robin non-specified channel pre-set state */
void cmp_roundrobin_channel_preset(uint32_t cmp_periph, uint32_t non_specified_channel);
/* comparator round robin timer trigger value config */
void cmp_roundrobin_trigger_timer_value_config(uint32_t cmp_periph, uint32_t value);
/* comparator round robin timer trigger value reload */
void cmp_roundrobin_trigger_timer_value_reload(uint32_t cmp_periph);
/* comparator round robin timer counter clear */
void cmp_roundrobin_trigger_timer_counter_clear(uint32_t cmp_periph);

/* enable functions */
/* enable comparator */
void cmp_enable(uint32_t cmp_periph);
/* disable comparator */
void cmp_disable(uint32_t cmp_periph);
/* enable the voltage scaler */
void cmp_voltage_scaler_enable(uint32_t cmp_periph);
/* disable the voltage scaler */
void cmp_voltage_scaler_disable(uint32_t cmp_periph);
/* enable the scaler bridge */
void cmp_scaler_bridge_enable(uint32_t cmp_periph);
/* disable the scaler bridge */
void cmp_scaler_bridge_disable(uint32_t cmp_periph);
/* enable comparator round robin */
void cmp_roundrobin_enable(uint32_t cmp_periph);
/* disable comparator round robin */
void cmp_roundrobin_disable(uint32_t cmp_periph);
/* enable comparator round robin counter */
void cmp_roundrobin_trigger_timer_counter_enable(uint32_t cmp_periph);
/* disable comparator round robin counter */
void cmp_roundrobin_trigger_timer_counter_disable(uint32_t cmp_periph);
/* enable comparator round robin trigger */
void cmp_roundrobin_trigger_enable(uint32_t cmp_periph);
/* disable comparator round robin trigger */
void cmp_roundrobin_trigger_disable(uint32_t cmp_periph);
/* lock the comparator */
void cmp_lock_enable(uint32_t cmp_periph);

/* output functions */
/* get output level */
uint32_t cmp_output_level_get(uint32_t cmp_periph);

/* flag and interrupt functions */
/* get comparator round robin non-specified_channel compare result flag */
FlagStatus cmp_roundrobin_flag_get(uint32_t cmp_periph, uint32_t non_specified_channel);
/* clear comparator round robin non-specified_channel compare result flag */
void cmp_roundrobin_flag_clear(uint32_t cmp_periph, uint32_t non_specified_channel);
/* enable comparator round robin interrupt */
void cmp_roundrobin_interrupt_enable(uint32_t cmp_periph);
/* disable comparator round robin interrupt */
void cmp_roundrobin_interrupt_disable(uint32_t cmp_periph);

#endif /* GD32A7XX_CMP_H */
