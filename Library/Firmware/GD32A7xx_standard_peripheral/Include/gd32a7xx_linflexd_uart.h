/*!
    \file    gd32a7xx_linflexd_uart.h
    \brief   definitions for the LINFLEXD_UART

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

#ifndef GD32A7XX_LINFLEXD_UART_H
#define GD32A7XX_LINFLEXD_UART_H

#include "gd32a7xx.h"

/* peripheral address definitions */
#define LINFLEXD_UART0                (LINFLEXD_BASE + 0x00008000U)               /*!< LINFLEXD_UART0 base address */
#define LINFLEXD_UART1                (LINFLEXD_BASE + 0x00008400U)               /*!< LINFLEXD_UART1 base address */
#define LINFLEXD_UART2                (LINFLEXD_BASE + 0x00008800U)               /*!< LINFLEXD_UART2 base address */
#define LINFLEXD_UART3                (LINFLEXD_BASE + 0x00008C00U)               /*!< LINFLEXD_UART3 base address */
#define LINFLEXD_UART4                (LINFLEXD_BASE + 0x00009000U)               /*!< LINFLEXD_UART4 base address */
#define LINFLEXD_UART5                (LINFLEXD_BASE + 0x00009400U)               /*!< LINFLEXD_UART5 base address */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define LINFLEXD_UART6                LINFLEXD_BASE                               /*!< LINFLEXD_UART6 base address (Only for GD32A714Axx /A72xAxx / A74xAxx devices) */
#define LINFLEXD_UART7                (LINFLEXD_BASE + 0x00000400U)               /*!< LINFLEXD_UART7 base address (Only for GD32A714Axx /A72xAxx / A74xAxx devices) */
#define LINFLEXD_UART8                (LINFLEXD_BASE + 0x00000800U)               /*!< LINFLEXD_UART8 base address (Only for GD32A714Axx /A72xAxx / A74xAxx devices) */
#define LINFLEXD_UART9                (LINFLEXD_BASE + 0x00000C00U)               /*!< LINFLEXD_UART9 base address (Only for GD32A714Axx /A72xAxx / A74xAxx devices) */
#define LINFLEXD_UART10               (LINFLEXD_BASE + 0x00001000U)               /*!< LINFLEXD_UART10 base address (Only for GD32A714Axx /A72xAxx / A74xAxx devices) */
#define LINFLEXD_UART11               (LINFLEXD_BASE + 0x00001400U)               /*!< LINFLEXD_UART11 base address (Only for GD32A714Axx /A72xAxx / A74xAxx devices) */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* registers definitions (all) */
#define LINFLEXD_UART_LINCR1(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x00000000U)              /*!< LINFLEXD_UART control register 1 */
#define LINFLEXD_UART_LINIER(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x00000004U)              /*!< LINFLEXD_UART interrupt enable register */
#define LINFLEXD_UART_LINSR(linflexdx_uartx)         REG32((linflexdx_uartx) + 0x00000008U)              /*!< LINFLEXD_UART status register */
#define LINFLEXD_UART_LINESR(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x0000000CU)              /*!< LINFLEXD_UART error status register */
#define LINFLEXD_UART_UARTCR(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x00000010U)              /*!< LINFLEXD_UART mode control register */
#define LINFLEXD_UART_UARTSR(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x00000014U)              /*!< LINFLEXD_UART mode status register */
#define LINFLEXD_UART_LINTCSR(linflexdx_uartx)       REG32((linflexdx_uartx) + 0x00000018U)              /*!< LINFLEXD_UART timeout control status register */
#define LINFLEXD_UART_LINOCR(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x0000001CU)              /*!< LINFLEXD_UART output compare register */
#define LINFLEXD_UART_LINTOCR(linflexdx_uartx)       REG32((linflexdx_uartx) + 0x00000020U)              /*!< LINFLEXD_UART timeout control register */
#define LINFLEXD_UART_LINFBRR(linflexdx_uartx)       REG32((linflexdx_uartx) + 0x00000024U)              /*!< LINFLEXD_UART fractional baud rate register */
#define LINFLEXD_UART_LINIBRR(linflexdx_uartx)       REG32((linflexdx_uartx) + 0x00000028U)              /*!< LINFLEXD_UART integer baud rate register */
#define LINFLEXD_UART_LINCFR(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x0000002CU)              /*!< LINFLEXD_UART checksum field register */
#define LINFLEXD_UART_LINCR2(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x00000030U)              /*!< LINFLEXD_UART control register 2 */
#define LINFLEXD_UART_BIDR(linflexdx_uartx)          REG32((linflexdx_uartx) + 0x00000034U)              /*!< LINFLEXD_UART buffer identifier register */
#define LINFLEXD_UART_BDRL(linflexdx_uartx)          REG32((linflexdx_uartx) + 0x00000038U)              /*!< LINFLEXD_UART buffer data register least significant */
#define LINFLEXD_UART_BDRM(linflexdx_uartx)          REG32((linflexdx_uartx) + 0x0000003CU)              /*!< LINFLEXD_UART buffer data register most significant */
#define LINFLEXD_UART_IFER(linflexdx_uartx)          REG32((linflexdx_uartx) + 0x00000040U)              /*!< LINFLEXD_UART identifier filter enable register */
#define LINFLEXD_UART_IFMI(linflexdx_uartx)          REG32((linflexdx_uartx) + 0x00000044U)              /*!< LINFLEXD_UART identifier filter match index */
#define LINFLEXD_UART_IFMR(linflexdx_uartx)          REG32((linflexdx_uartx) + 0x00000048U)              /*!< LINFLEXD_UART identifier filter mode register */
#define LINFLEXD_UART_IFCR(linflexdx_uartx, n)       REG32((linflexdx_uartx) + 0x0000004CU + (n) * 0x4U) /*!< LINFLEXD_UART identifier filter control register */
#define LINFLEXD_UART_GCR(linflexdx_uartx)           REG32((linflexdx_uartx) + 0x0000008CU)              /*!< LINFLEXD_UART global control register */
#define LINFLEXD_UART_UARTPTO(linflexdx_uartx)       REG32((linflexdx_uartx) + 0x00000090U)              /*!< LINFLEXD_UART UART preset timeout register */
#define LINFLEXD_UART_UARTCTO(linflexdx_uartx)       REG32((linflexdx_uartx) + 0x00000094U)              /*!< LINFLEXD_UART UART current timeout register */
#define LINFLEXD_UART_DMATXE(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x00000098U)              /*!< LINFLEXD_UART DMA Tx enable register */
#define LINFLEXD_UART_DMARXE(linflexdx_uartx)        REG32((linflexdx_uartx) + 0x0000009CU)              /*!< LINFLEXD_UART DMA Rx enable register */
#define LINFLEXD_UART_LIN_STCTL(linflexdx_uartx)     REG32((linflexdx_uartx) + 0x000000A0U)              /*!< LINFLEXD_UART stop control register */

/* bits definitions (only for LINFlexD_UART) */
/* LINCR1 */
#define LINFLEXD_UART_LINCR1_INIT             BIT(0)                               /*!< initialization mode request */
#define LINFLEXD_UART_LINCR1_SLEEP            BIT(1)                               /*!< sleep mode request */
#define LINFLEXD_UART_LINCR1_RBLM             BIT(2)                               /*!< receiver buffer locked mode */
#define LINFLEXD_UART_LINCR1_LBKM             BIT(5)                               /*!< loop back mode */
#define LINFLEXD_UART_LINCR1_AUTOWU           BIT(12)                              /*!< automatic wake-up */

/* LINIER */
#define LINFLEXD_UART_LINIER_HRIE             BIT(0)                               /*!< header received interrupt enable */
#define LINFLEXD_UART_LINIER_DTIE             BIT(1)                               /*!< data transmitted interrupt enable */
#define LINFLEXD_UART_LINIER_DRIE             BIT(2)                               /*!< data reception complete interrupt enable */
#define LINFLEXD_UART_LINIER_TOIE             BIT(3)                               /*!< timeout interrupt enable */
#define LINFLEXD_UART_LINIER_WUIE             BIT(5)                               /*!< wakeup interrupt enable */
#define LINFLEXD_UART_LINIER_LSIE             BIT(6)                               /*!< LIN state interrupt enable */
#define LINFLEXD_UART_LINIER_BOIE             BIT(7)                               /*!< buffer overrun interrupt enable */
#define LINFLEXD_UART_LINIER_FEIE             BIT(8)                               /*!< frame error interrupt enable */
#define LINFLEXD_UART_LINIER_HEIE             BIT(11)                              /*!< header error interrupt enable */
#define LINFLEXD_UART_LINIER_CEIE             BIT(12)                              /*!< checksum error interrupt enable */
#define LINFLEXD_UART_LINIER_BEIE             BIT(13)                              /*!< bit error interrupt enable */
#define LINFLEXD_UART_LINIER_OCIE             BIT(14)                              /*!< output compare interrupt enable */
#define LINFLEXD_UART_LINIER_SZIE             BIT(15)                              /*!< stuck at zero interrupt enable */

/* LINSR */
#define LINFLEXD_UART_LINSR_HRF               BIT(0)                               /*!< header received flag */
#define LINFLEXD_UART_LINSR_DTF               BIT(1)                               /*!< data transmission completed flag */
#define LINFLEXD_UART_LINSR_DRF               BIT(2)                               /*!< data reception completed flag */
#define LINFLEXD_UART_LINSR_WUF               BIT(5)                               /*!< wakeup flag */
#define LINFLEXD_UART_LINSR_RDI               BIT(6)                               /*!< receiver data input */
#define LINFLEXD_UART_LINSR_RXBUSY            BIT(7)                               /*!< receiver busy flag */
#define LINFLEXD_UART_LINSR_DRBNE             BIT(8)                               /*!< data reception buffer not empty flag */
#define LINFLEXD_UART_LINSR_RMB               BIT(9)                               /*!< release message buffer */
#define LINFLEXD_UART_LINSR_LINS              BITS(12, 15)                         /*!< LIN state */
#define LINFLEXD_UART_LINSR_RDC               BITS(16, 18)                         /*!< receive data byte count */
#define LINFLEXD_UART_LINSR_AUTOSYNC_COMP     BIT(19)                              /*!< autosynchronization complete */

/* UARTCR */
#define LINFLEXD_UART_UARTCR_UART             BIT(0)                               /*!< UART mode */
#define LINFLEXD_UART_UARTCR_WL0              BIT(1)                               /*!< word length in UART mode */
#define LINFLEXD_UART_UARTCR_PCE              BIT(2)                               /*!< parity control enable */
#define LINFLEXD_UART_UARTCR_PC0              BIT(3)                               /*!< parity control 0 */
#define LINFLEXD_UART_UARTCR_TXEN             BIT(4)                               /*!< transmitter enable */
#define LINFLEXD_UART_UARTCR_RXEN             BIT(5)                               /*!< receiver enable */
#define LINFLEXD_UART_UARTCR_PC1              BIT(6)                               /*!< parity control 1 */
#define LINFLEXD_UART_UARTCR_WL1              BIT(7)                               /*!< word length in UART mode 1 */
#define LINFLEXD_UART_UARTCR_TFBM             BIT(8)                               /*!< tx FIFO/buffer mode */
#define LINFLEXD_UART_UARTCR_RFBM             BIT(9)                               /*!< rx FIFO/buffer mode */
#define LINFLEXD_UART_UARTCR_RDFL_RFC         BITS(10, 12)                         /*!< receiver data field length/rx FIFO counter */
#define LINFLEXD_UART_UARTCR_TDFL_TFC         BITS(13, 15)                         /*!< transmitter data field length/tx FIFO counter */
#define LINFLEXD_UART_UARTCR_WLS              BIT(16)                              /*!< special word length in UART mode */
#define LINFLEXD_UART_UARTCR_SBUR             BITS(17, 18)                         /*!< number of stop bits in UART reception mode */
#define LINFLEXD_UART_UARTCR_DTU              BIT(19)                              /*!< disable timeout in UART mode */
#define LINFLEXD_UART_UARTCR_NEF              BITS(20, 22)                         /*!< number of expected frames */
#define LINFLEXD_UART_UARTCR_ROSE             BIT(23)                              /*!< reduced oversampling enable */
#define LINFLEXD_UART_UARTCR_OSR              BITS(24, 27)                         /*!< oversampling rate */
#define LINFLEXD_UART_UARTCR_CSP              BITS(28, 30)                         /*!< configurable sample point */
#define LINFLEXD_UART_UARTCR_MIS              BIT(31)                              /*!< monitor idle state */

/* UARTSR */
#define LINFLEXD_UART_UARTSR_NF               BIT(0)                               /*!< noise flag */
#define LINFLEXD_UART_UARTSR_DTF_TFF          BIT(1)                               /*!< data transmission completed flag/ tx FIFO full flag */
#define LINFLEXD_UART_UARTSR_DRF_RFE          BIT(2)                               /*!< data reception completed flag / rx FIFO empty flag */
#define LINFLEXD_UART_UARTSR_TO               BIT(3)                               /*!< timeout */
#define LINFLEXD_UART_UARTSR_RFNE             BIT(4)                               /*!< receive FIFO not empty */
#define LINFLEXD_UART_UARTSR_WUF              BIT(5)                               /*!< wakeup flag */
#define LINFLEXD_UART_UARTSR_RDI              BIT(6)                               /*!< receiver data input */
#define LINFLEXD_UART_UARTSR_BOF              BIT(7)                               /*!< FIFO / buffer overrun flag */
#define LINFLEXD_UART_UARTSR_FEF              BIT(8)                               /*!< framing error flag */
#define LINFLEXD_UART_UARTSR_RMB              BIT(9)                               /*!< release message buffer */
#define LINFLEXD_UART_UARTSR_PE               BITS(10, 13)                         /*!< parity error flag */
#define LINFLEXD_UART_UARTSR_OCF              BIT(14)                              /*!< output compare flag */
#define LINFLEXD_UART_UARTSR_SZF              BIT(15)                              /*!< stuck at zero flag */

/* LINFBRR */
#define LINFLEXD_UART_LINFBRR_FBR             BITS(0, 3)                           /*!< fractional baud rate */

/* LINIBRR */
#define LINFLEXD_UART_LINIBRR_IBR             BITS(0, 19)                          /*!< integer baud rate */

/* LINCR2 */
#define LINFLEXD_UART_LINCR2_ABRQ             BIT(9)                               /*!< abort request */

/* BDRL */
#define LINFLEXD_UART_BDRL_DATA0              BITS(0, 7)                           /*!< data byte 0 */
#define LINFLEXD_UART_BDRL_DATA1              BITS(8, 15)                          /*!< data byte 1 */
#define LINFLEXD_UART_BDRL_DATA2              BITS(16, 23)                         /*!< data byte 2 */
#define LINFLEXD_UART_BDRL_DATA3              BITS(24, 31)                         /*!< data byte 3 */

/* BDRM */
#define LINFLEXD_UART_BDRM_DATA4              BITS(0, 7)                           /*!< data byte 4 */
#define LINFLEXD_UART_BDRM_DATA5              BITS(8, 15)                          /*!< data byte 5 */
#define LINFLEXD_UART_BDRM_DATA6              BITS(16, 23)                         /*!< data byte 6 */
#define LINFLEXD_UART_BDRM_DATA7              BITS(24, 31)                         /*!< data byte 7 */

/* GCR */
#define LINFLEXD_UART_GCR_SR                  BIT(0)                               /*!< soft reset */
#define LINFLEXD_UART_GCR_STOP                BIT(1)                               /*!< one or two stop bit configuration */
#define LINFLEXD_UART_GCR_RDLIS               BIT(2)                               /*!< receive data level inversion selection */
#define LINFLEXD_UART_GCR_TDLIS               BIT(3)                               /*!< transmit data level inversion selection */
#define LINFLEXD_UART_GCR_RDFBM               BIT(4)                               /*!< receive data first bit MSB */
#define LINFLEXD_UART_GCR_TDFBM               BIT(5)                               /*!< transmit data first bit MSB */

/* UARTPTO */
#define LINFLEXD_UART_UARTPTO_PTO             BITS(0, 11)                          /*!< preset timeout */

/* UARTCTO */
#define LINFLEXD_UART_UARTCTO_CTO             BITS(0, 11)                          /*!< current timeout value */

/* DMATXE */
#define LINFLEXD_UART_DMATXE_DTE0             BIT(0)                               /*!< DMA Tx channel 0 enable */

/* DMARXE */
#define LINFLEXD_UART_DMARXE_DRE0             BIT(0)                               /*!< DMA Rx channel 0 enable */

/* LIN_STCTL */
#define LINFLEXD_UART_LIN_STCTL_STOP          BIT(0)                               /*!< terminate the transmission */
#define LINFLEXD_UART_LIN_STCTL_ACK           BIT(1)                               /*!< the stop function takes effect */
#define LINFLEXD_UART_LIN_STCTL_SIZE          BITS(2, 3)                           /*!< the byte size transmitted on the IPS bus */
#define LINFLEXD_UART_LIN_STCTL_TX_INV        BIT(4)                               /*!< TX pin level inversion */
#define LINFLEXD_UART_LIN_STCTL_RX_INV        BIT(5)                               /*!< RX pin level inversion */

/* constants definitions */
/* define the LINFlexD_UART bit position and its register index offset */
#define LINFLEXD_UART_REGIDX_BIT(regidx, bitpos)    (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define LINFLEXD_UART_REG_VAL(linflexd_uartx, offset)       (REG32((linflexd_uartx) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define LINFLEXD_UART_BIT_POS(val)                  ((uint32_t)(val) & 0x0000001FU)
#define LINFLEXD_UART_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                              | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define LINFLEXD_UART_REG_VAL2(linflexd_uartx, offset)       (REG32((linflexd_uartx) + ((uint32_t)(offset) >> 22)))
#define LINFLEXD_UART_BIT_POS2(val)                  (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define LINFLEXD_UART_LINIER_REG_OFFSET             0x00000004U                 /*!< LINIER register offset */
#define LINFLEXD_UART_UARTSR_REG_OFFSET             0x00000014U                 /*!< UARTSR register offset */

/* LINFlexD_UART flags */
typedef enum {
    /* flags in UARTSR */
    LINFLEXD_UART_FLAG_NF              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 0U),     /*!< noise flag */
    LINFLEXD_UART_FLAG_DTF_TFF         = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 1U),     /*!< data transmission completed flag/ Tx FIFO full flag */
    LINFLEXD_UART_FLAG_DRF_RFE         = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 2U),     /*!< data reception completed flag / Rx FIFO empty flag */
    LINFLEXD_UART_FLAG_TO              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 3U),     /*!< timeout flag */
    LINFLEXD_UART_FLAG_RFNE            = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 4U),     /*!< receive FIFO not empty flag */
    LINFLEXD_UART_FLAG_WUF             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 5U),     /*!< wakeup flag */
    LINFLEXD_UART_FLAG_RDI             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 6U),     /*!< receiver input state flag */
    LINFLEXD_UART_FLAG_BOF             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 7U),     /*!< FIFO / buffer overrun flag */
    LINFLEXD_UART_FLAG_FEF             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 8U),     /*!< frame error flag */
    LINFLEXD_UART_FLAG_RMB             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 9U),     /*!< release message buffer flag */
    LINFLEXD_UART_FLAG_PE0             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 10U),    /*!< parity error 0 flag */
    LINFLEXD_UART_FLAG_PE1             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 11U),    /*!< parity error 1 flag */
    LINFLEXD_UART_FLAG_PE2             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 12U),    /*!< parity error 2 flag */
    LINFLEXD_UART_FLAG_PE3             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 13U),    /*!< parity error 3 flag */
    LINFLEXD_UART_FLAG_OCF             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 14U),    /*!< output compare flag */
    LINFLEXD_UART_FLAG_SZF             = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_UARTSR_REG_OFFSET, 15U),    /*!< stuck at zero flag */
} linflexd_uart_flag_enum;

/* LINFlexD_UART interrupts */
typedef enum {
    /* interrupts in LINIER */
    LINFLEXD_UART_INT_DTF              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_LINIER_REG_OFFSET, 1U),     /*!< data transmitted interrupt */
    LINFLEXD_UART_INT_DRF              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_LINIER_REG_OFFSET, 2U),     /*!< data reception complete interrupt */
    LINFLEXD_UART_INT_TO               = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_LINIER_REG_OFFSET, 3U),     /*!< timeout interrupt */
    LINFLEXD_UART_INT_WUF              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_LINIER_REG_OFFSET, 5U),     /*!< wakeup interrupt */
    LINFLEXD_UART_INT_BOF              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_LINIER_REG_OFFSET, 7U),     /*!< buffer overrun interrupt */
    LINFLEXD_UART_INT_FEF              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_LINIER_REG_OFFSET, 8U),     /*!< frame error interrupt */
    LINFLEXD_UART_INT_OCF              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_LINIER_REG_OFFSET, 14U),    /*!< output compare interrupt */
    LINFLEXD_UART_INT_SZF              = LINFLEXD_UART_REGIDX_BIT(LINFLEXD_UART_LINIER_REG_OFFSET, 15U),    /*!< stuck at zero interrupt */
} linflexd_uart_interrupt_enum;

/* LINFlexD_UART interrupt flags */
typedef enum {
    /* interrupt flags in UARTSR and LINIER */
    LINFLEXD_UART_INT_FLAG_DTF         = LINFLEXD_UART_REGIDX_BIT2(LINFLEXD_UART_LINIER_REG_OFFSET, 1U, LINFLEXD_UART_UARTSR_REG_OFFSET, 1U),     /*!< data transmission completed interrupt and flag */
    LINFLEXD_UART_INT_FLAG_DRF         = LINFLEXD_UART_REGIDX_BIT2(LINFLEXD_UART_LINIER_REG_OFFSET, 2U, LINFLEXD_UART_UARTSR_REG_OFFSET, 2U),     /*!< data reception completed interrupt and flag */
    LINFLEXD_UART_INT_FLAG_TO          = LINFLEXD_UART_REGIDX_BIT2(LINFLEXD_UART_LINIER_REG_OFFSET, 3U, LINFLEXD_UART_UARTSR_REG_OFFSET, 3U),     /*!< timeout interrupt and flag */
    LINFLEXD_UART_INT_FLAG_WUF         = LINFLEXD_UART_REGIDX_BIT2(LINFLEXD_UART_LINIER_REG_OFFSET, 5U, LINFLEXD_UART_UARTSR_REG_OFFSET, 5U),     /*!< wakeup interrupt and flag */
    LINFLEXD_UART_INT_FLAG_BOF         = LINFLEXD_UART_REGIDX_BIT2(LINFLEXD_UART_LINIER_REG_OFFSET, 7U, LINFLEXD_UART_UARTSR_REG_OFFSET, 7U),     /*!< buffer overrun interrupt and flag */
    LINFLEXD_UART_INT_FLAG_FEF         = LINFLEXD_UART_REGIDX_BIT2(LINFLEXD_UART_LINIER_REG_OFFSET, 8U, LINFLEXD_UART_UARTSR_REG_OFFSET, 8U),     /*!< framing error interrupt and flag */
    LINFLEXD_UART_INT_FLAG_OCF         = LINFLEXD_UART_REGIDX_BIT2(LINFLEXD_UART_LINIER_REG_OFFSET, 14U, LINFLEXD_UART_UARTSR_REG_OFFSET, 14U),   /*!< output compare interrupt and flag */
    LINFLEXD_UART_INT_FLAG_SZF         = LINFLEXD_UART_REGIDX_BIT2(LINFLEXD_UART_LINIER_REG_OFFSET, 15U, LINFLEXD_UART_UARTSR_REG_OFFSET, 15U),   /*!< stuck at zero interrupt and flag */
} linflexd_uart_interrupt_flag_enum;

/* LINFlexD_UART parity type */
typedef enum
{
    LINFLEXD_UART_PARITY_EVEN = 0U,         /*!< LINFLEXD_UART parity with even type */
    LINFLEXD_UART_PARITY_ODD = 1U,          /*!< LINFLEXD_UART parity with odd type */
    LINFLEXD_UART_PARITY_ALWAYS_0 = 2U,     /*!< LINFLEXD_UART parity always 0 */
    LINFLEXD_UART_PARITY_ALWAYS_1 = 3U      /*!< LINFLEXD_UART parity always 1 */
} linflexd_uart_parity_type_enum;

/* LINFlexD_UART stop bits count */
typedef enum
{
    LINFLEXD_UART_ONE_STOP_BIT = 0U,        /*!< LINFLEXD_UART 1 stop bit */
    LINFLEXD_UART_TWO_STOP_BITS = 1U,       /*!< LINFLEXD_UART 2 stop bits */
    LINFLEXD_UART_THREE_STOP_BITS = 2U      /*!< LINFLEXD_UART 3 stop bits (only for receiver) */
} linflexd_uart_stop_bits_count_enum;

/* LINFlexD_UART word length */
typedef enum
{
    LINFLEXD_UART_7_BITS = 0U,              /*!< LINFLEXD_UART word length of 7-bit */
    LINFLEXD_UART_8_BITS = 1U,              /*!< LINFLEXD_UART word length of 8-bit */
    LINFLEXD_UART_15_BITS = 2U,             /*!< LINFLEXD_UART word length of 15-bit */
    LINFLEXD_UART_16_BITS = 3U              /*!< LINFLEXD_UART word length of 16-bit */
} linflexd_uart_word_length_enum;

/* LINFlexD_UART rx and tx mode */
typedef enum
{
    LINFLEXD_UART_TXRX_BUFFER_MODE = 0U,    /*!< LINFLEXD_UART TX/RX buffer mode */
    LINFLEXD_UART_TXRX_FIFO_MODE = 1U       /*!< LINFLEXD_UART TX/RX FIFO mode */
} linflexd_uart_txrx_mode_enum;

/* LINFlexD_UART state */
typedef enum
{
    LINFLEXD_UART_STATE_SLEEP_MODE = 0U,        /*!< sleep mode, low power state */
    LINFLEXD_UART_STATE_INIT_MODE = 1U,         /*!< initialization mode, registers can be configured */
    LINFLEXD_UART_STATE_IDLE_MODE = 2U,         /*!< idle mode, ready to transmit or receive data */
    LINFLEXD_UART_STATE_SYNC_BREAK = 3U,        /*!< synchronization break state, start of a LIN frame (only for LIN) */
    LINFLEXD_UART_STATE_SYNC_DEL = 4U,          /*!< synchronization delimiter state, part of LIN header (only for LIN) */
    LINFLEXD_UART_STATE_SYNC_FIELD = 5U,        /*!< synchronization field state, used for bit rate sync (only for LIN) */
    LINFLEXD_UART_STATE_IDENTIFIER_FIELD = 6U,  /*!< identifier field state, processing LIN frame ID (only for LIN) */
    LINFLEXD_UART_STATE_HEADER_RX_TX = 7U,      /*!< header reception/transmission state (only for LIN) */
    LINFLEXD_UART_STATE_DATA_RX_TX = 8U,        /*!< data reception/transmission state */
    LINFLEXD_UART_STATE_CHECKSUM = 9U           /*!< checksum state, processing LIN frame verification (only for LIN) */
} linflexd_uart_state_enum;

/* LINFlexD_UART mode */
typedef enum
{
    LINFLEXD_LIN_MODE = 0U,                 /*!< LIN mode */
    LINFLEXD_UART_MODE = 1U                 /*!< UART mode */
} linflexd_uart_mode_enum;

/* LINFlexD_UART timeout counter reset mode */
typedef enum
{
    LINFLEXD_UART_TIMEOUT_SW_HANDLE = 0U,              /*!< timeout must be handled by software */
    LINFLEXD_UART_TIMEOUT_DISABLE_AFTER_FRAMES = 1U    /*!< timeout is disabled after receiving the configured number of data frames */
} linflexd_uart_timeout_control_enum;

/* LINFlexD_UART data first bit MSB */
typedef enum {
    LINFLEXD_UART_DATAFIRST_LSB = 0U,            /*!< LSB first */
    LINFLEXD_UART_DATAFIRST_MSB = 1U             /*!< MSB first */
} linflexd_uart_datafirst_enum;

/* LINFlexD_UART TX and RX invert configure */
typedef enum {
    LINFLEXD_UART_TXRX_INVERT_DISABLE = 0U,       /*!< TX/RX data/pin level not inversion */
    LINFLEXD_UART_TXRX_INVERT_ENABLE = 1U         /*!< TX/RX data/pin level inversion */
} linflexd_uart_txrx_invert_enum;

/* LINFlexD_UART IPS bus size type */
typedef enum{
    LINFLEXD_UART_IPS_DATA_WORD = 0U,       /*!< Word size (32-bit) data transmitted on IPS bus */
    LINFLEXD_UART_IPS_DATA_BYTE = 1U,       /*!< Byte size (8-bit) data transmitted on IPS bus */
    LINFLEXD_UART_IPS_DATA_HALFWORD = 2U    /*!< Half-word size (16-bit) data transmitted on IPS bus */
} linflexd_uart_ips_sizetype_enum;

/* LINFlexD_UART parameter structure */
typedef struct {
    uint32_t                            baudrate;      /*!< baud rate */
    ControlStatus                       parityenable;  /*!< parity control - ENABLE/DISABLE */
    linflexd_uart_parity_type_enum      paritytype;    /*!< always 0/always 1/even/odd */
    linflexd_uart_stop_bits_count_enum  stopbitscount; /*!< number of stop bits */
    linflexd_uart_word_length_enum      wordlength;    /*!< number of bits per transmitted/received word */
    linflexd_uart_txrx_mode_enum        txmodetype;    /*!< type of UART tx transfer (buffer/fifo) */
    linflexd_uart_txrx_mode_enum        rxmodetype;    /*!< type of UART rx transfer (buffer/fifo) */
} linflexd_uart_parameter_struct;

/* configure LINFlexD_UART transmitter */
#define UARTCR_TXEN(regval)                   (BIT(4) & ((uint32_t)(regval) << 4))
#define LINFLEXD_UART_TRANSMIT_ENABLE         UARTCR_TXEN(1)                    /*!< enable transmitter */
#define LINFLEXD_UART_TRANSMIT_DISABLE        UARTCR_TXEN(0)                    /*!< disable transmitter */

/* configure LINFlexD_UART receiver */
#define UARTCR_RXEN(regval)                   (BIT(5) & ((uint32_t)(regval) << 5))
#define LINFLEXD_UART_RECEIVE_ENABLE          UARTCR_RXEN(1)                    /*!< enable receiver */
#define LINFLEXD_UART_RECEIVE_DISABLE         UARTCR_RXEN(0)                    /*!< disable receiver */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check LINFLEXD_UART peripherals */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) 
#define NOT_LINFLEXD_UART_PERIPH(periph)     (((periph) != LINFLEXD_UART0)  && ((periph) != LINFLEXD_UART1)  && \
                                              ((periph) != LINFLEXD_UART2)  && ((periph) != LINFLEXD_UART3)  && \
                                              ((periph) != LINFLEXD_UART4)  && ((periph) != LINFLEXD_UART5)  && \
                                              ((periph) != LINFLEXD_UART6)  && ((periph) != LINFLEXD_UART7)  && \
                                              ((periph) != LINFLEXD_UART8)  && ((periph) != LINFLEXD_UART9)  && \
                                              ((periph) != LINFLEXD_UART10) && ((periph) != LINFLEXD_UART11))
#else
#define NOT_LINFLEXD_UART_PERIPH(periph)     (((periph) != LINFLEXD_UART0)  && ((periph) != LINFLEXD_UART1)  && \
                                              ((periph) != LINFLEXD_UART2)  && ((periph) != LINFLEXD_UART3)  && \
                                              ((periph) != LINFLEXD_UART4)  && ((periph) != LINFLEXD_UART5))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* check if the baudrate is not a LINFlexD_UART baudrate */
#define NOT_LINFLEXD_UART_BAUDRATE(baudval)                  ((baudval) == 0U)

/* check integer baud rate parameter */
#define NOT_LINFLEXD_UART_IBR(ibr)                           ((ibr) > 0xFFFFFU)

/* check fractional baud rate parameter */
#define NOT_LINFLEXD_UART_FBR(fbr)                           ((fbr) > 0xFU)

/* check LINFlexD_UART transmitter configuration */
#define NOT_LINFLEXD_UART_TRANSMITTER_CONFIG(mode)           (((mode) != LINFLEXD_UART_TRANSMIT_ENABLE) && \
                                                             ((mode) != LINFLEXD_UART_TRANSMIT_DISABLE))

/* check LINFlexD_UART receiver configuration */
#define NOT_LINFLEXD_UART_RECEIVER_CONFIG(mode)              (((mode) != LINFLEXD_UART_RECEIVE_ENABLE) && \
                                                             ((mode) != LINFLEXD_UART_RECEIVE_DISABLE))

/* check LINFlexD_UART receiver configuration */
#define NOT_LINFLEXD_UART_RXTX_FIELDLENGTH(length)           (((length) != 0x0U) && ((length) != 0x1U) && \
                                                             ((length) != 0x2U) && ((length) != 0x3U) && \
                                                             ((length) != 0x4U))

/* check timeout value parameter */
#define NOT_LINFLEXD_UART_TIMEOUT_VALUE(value)               ((value) > 0xFFFU)

/* check frame count parameter */
#define NOT_LINFLEXD_UART_EXPECTED_FRAME_COUNT(length)       ((length) > 0x7U)

/* check oversampling rate parameter (valid values are 4, 5, 6, 8) */
#define NOT_LINFLEXD_UART_OSRCOUNT(count)                    ((count) != 0x4U && (count) != 0x5U && \
                                                             (count) != 0x6U && (count) != 0x8U)

/* check configurable sample point (valid values are 2, 3, 4, 5) */
#define NOT_LINFLEXD_UART_CSPCOUNT(count)                    ((count) != 0x2U && (count) != 0x3U && \
                                                             (count) != 0x4U && (count) != 0x5U)

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* initialization and configuration functions */
/* reset LINFlexD_UART */
ErrStatus linflexd_uart_deinit(uint32_t linflexd_uart_periph);
/* initialize the parameters of LINFlexD_UART struct with default values */
void linflexd_uart_struct_para_init(linflexd_uart_parameter_struct *linflexd_uart_struct);
/* initialize LINFlexD_UART parameter */
ErrStatus linflexd_uart_init(uint32_t linflexd_uart_periph, linflexd_uart_parameter_struct *linflexd_uart_struct);
/* LINFlexD_UART enter init mode */
void linflexd_uart_initmode_enter(uint32_t linflexd_uart_periph);
/* LINFlexD_UART enter normal mode */
void linflexd_uart_normalmode_enter(uint32_t linflexd_uart_periph);
/* LINFlexD_UART soft reset */
void linflexd_uart_soft_reset(uint32_t linflexd_uart_periph);

/* mode and state control functions */
/* enable LINFlexD_UART sleep mode */
void linflexd_uart_sleepmode_enable(uint32_t linflexd_uart_periph);
/* disable LINFlexD_UART sleep mode */
void linflexd_uart_sleepmode_disable(uint32_t linflexd_uart_periph);
/* get LINFlexD_UART sleep mode */
FlagStatus linflexd_uart_sleepmode_get(uint32_t linflexd_uart_periph);
/* enable LINFlexD_UART receiver buffer locked mode */
void linflexd_uart_receiverbufferlocked_enable(uint32_t linflexd_uart_periph);
/* disable LINFlexD_UART receiver buffer locked mode */
void linflexd_uart_receiverbufferlocked_disable(uint32_t linflexd_uart_periph);
/* enable LINFlexD_UART loopback mode */
void linflexd_uart_loopback_enable(uint32_t linflexd_uart_periph);
/* disable LINFlexD_UART loopback mode */
void linflexd_uart_loopback_disable(uint32_t linflexd_uart_periph);
/* config LINFlexD_UART auto wakeup hardware to clear the SLEEP bit */
void linflexd_uart_autowake_hw_clear(uint32_t linflexd_uart_periph);
/* config LINFlexD_UART auto wakeup software to clear the SLEEP bit */
void linflexd_uart_autowake_sw_clear(uint32_t linflexd_uart_periph);
/* LINFlexD_UART mode (LIN/UART) set */
void linflexd_uart_mode_set(uint32_t linflexd_uart_periph, linflexd_uart_mode_enum mode);
/* LINFlexD_UART current state get */
linflexd_uart_state_enum linflexd_uart_state_get(uint32_t linflexd_uart_periph);
/* LINFlexD_UART abort the current transmission */
void linflexd_uart_abort_request(uint32_t linflexd_uart_periph);
/* LINFlexD_UART terminate the transmission */
void linflexd_uart_terminate_transmit(uint32_t linflexd_uart_periph, ControlStatus mode);
/* LINFlexD_UART stop state get */
FlagStatus linflexd_uart_stop_get(uint32_t linflexd_uart_periph);

/* parameter setting functions */
/* LINFlexD_UART integer baudrate set */
void linflexd_uart_integer_baudrate_set(uint32_t linflexd_uart_periph, uint32_t ibr);
/* LINFlexD_UART fractional baudrate set */
void linflexd_uart_fractional_baudrate_set(uint32_t linflexd_uart_periph, uint8_t fbr);
/* configure LINFlexD_UART baudrate value */
ErrStatus linflexd_uart_baudrate_set(uint32_t linflexd_uart_periph, uint32_t baudval);
/* LINFlexD_UART word length set */
void linflexd_uart_wordlength_set(uint32_t linflexd_uart_periph, linflexd_uart_word_length_enum length);
/* get LINFlexD_UART word length */
linflexd_uart_word_length_enum linflexd_uart_wordlength_get(uint32_t linflexd_uart_periph);
/* enable LINFlexD_UART parity bit */
void linflexd_uart_paritycontrol_enable(uint32_t linflexd_uart_periph);
/* disable LINFlexD_UART parity bit */
void linflexd_uart_paritycontrol_disable(uint32_t linflexd_uart_periph);
/* LINFlexD_UART parity type set */
void linflexd_uart_paritytype_set(uint32_t linflexd_uart_periph, linflexd_uart_parity_type_enum paritytype);
/* set LINFlexD_UART receiver data field length */
void linflexd_uart_rxdatafieldlength_set(uint32_t linflexd_uart_periph, uint8_t length);
/* set LINFlexD_UART transmitter data field length */
void linflexd_uart_txdatafieldlength_set(uint32_t linflexd_uart_periph, uint8_t length);
/* set LINFlexD_UART number of stop bits for Rx */
void linflexd_uart_rxstopbitscount_set(uint32_t linflexd_uart_periph, linflexd_uart_stop_bits_count_enum stopbitscount);
/* set LINFlexD_UART number of stop bits for Tx */
void linflexd_uart_txstopbitscount_set(uint32_t linflexd_uart_periph, linflexd_uart_stop_bits_count_enum stopbitscount);
/* LINFlexD_UART monitors the idle state of the reception line */
void linflexd_uart_idle_receive_line_monitor(uint32_t linflexd_uart_periph);
/* LINFlexD_UART monitors the number of bits to be received */
void linflexd_uart_number_receive_bits_monitor(uint32_t linflexd_uart_periph);
/* set LINFlexD_UART reset mode of the timeout counter */
void linflexd_uart_timeout_resetmode_set(uint32_t linflexd_uart_periph, linflexd_uart_timeout_control_enum mode);
/* set LINFlexD_UART value of the timeout counter */
void linflexd_uart_idle_timeoutvalue_set(uint32_t linflexd_uart_periph, uint32_t value);
/* enable LINFlexD_UART special word length mode */
void linflexd_uart_specialwordlength_enable(uint32_t linflexd_uart_periph);
/* disable LINFlexD_UART special word length mode */
void linflexd_uart_specialwordlength_disable(uint32_t linflexd_uart_periph);
/* set LINFlexD_UART number of expected frame */
void linflexd_uart_expect_framenumber_set(uint32_t linflexd_uart_periph, uint8_t framecount);
/* config LINFlexD_UART transmit data first bit MSB */
void linflexd_uart_transmit_datafirst_config(uint32_t linflexd_uart_periph, linflexd_uart_datafirst_enum mode);
/* config LINFlexD_UART received data first bit MSB */
void linflexd_uart_receive_datafirst_config(uint32_t linflexd_uart_periph, linflexd_uart_datafirst_enum mode);
/* config LINFlexD_UART transmit invert */
void linflexd_uart_transmitdata_invert_config(uint32_t linflexd_uart_periph, linflexd_uart_txrx_invert_enum mode);
/* config LINFlexD_UART receive invert */
void linflexd_uart_receivedata_invert_config(uint32_t linflexd_uart_periph, linflexd_uart_txrx_invert_enum mode);
/* config LINFlexD_UART transmit invert */
void linflexd_uart_transmitpin_invert_config(uint32_t linflexd_uart_periph, linflexd_uart_txrx_invert_enum mode);
/* config LINFlexD_UART receive invert */
void linflexd_uart_receivepin_invert_config(uint32_t linflexd_uart_periph, linflexd_uart_txrx_invert_enum mode);
/* set LINFlexD_UART byte size for transmission on the IPS bus */
void linflexd_uart_ips_size_set(uint32_t linflexd_uart_periph, linflexd_uart_ips_sizetype_enum size);

/* transmit and receive functions */
/* configure LINFlexD_UART transmitter */
void linflexd_uart_transmitter_config(uint32_t linflexd_uart_periph, uint32_t txconfig);
/* configure LINFlexD_UART receiver */
void linflexd_uart_receiver_config(uint32_t linflexd_uart_periph, uint32_t rxconfig);
/* set LINFlexD_UART transmitter mode (FIFO/Buffer) */
void linflexd_uart_txmode_set(uint32_t linflexd_uart_periph, linflexd_uart_txrx_mode_enum mode);
/* set LINFlexD_UART receiver mode (FIFO/Buffer) */
void linflexd_uart_rxmode_set(uint32_t linflexd_uart_periph, linflexd_uart_txrx_mode_enum mode);
/* flush the data register of LINFlexD_UART receive buffer */
void linflexd_uart_rxfifo_flush(uint32_t linflexd_uart_periph);
/* LINFlexD_UART transmit the tx data by byte */
void linflexd_uart_byte_transmit(uint32_t linflexd_uart_periph, uint8_t data);
/* LINFlexD_UART transmit the tx data by halfword */
void linflexd_uart_halfword_transmit(uint32_t linflexd_uart_periph, uint16_t data);
/* LINFlexD_UART receive the rx data by byte */
uint8_t linflexd_uart_byte_receive(uint32_t linflexd_uart_periph);
/* LINFlexD_UART receive the rx data by halfword */
uint16_t linflexd_uart_halfword_receive(uint32_t linflexd_uart_periph);
/* enable LINFlexD_UART tx dma channel */
void linflexd_uart_tx_dma_enable(uint32_t linflexd_uart_periph);
/* disable LINFlexD_UART tx dma channel */
void linflexd_uart_tx_dma_disable(uint32_t linflexd_uart_periph);
/* enable LINFlexD_UART rx dma channel */
void linflexd_uart_rx_dma_enable(uint32_t linflexd_uart_periph);
/* disable LINFlexD_UART rx dma channel */
void linflexd_uart_rx_dma_disable(uint32_t linflexd_uart_periph);

/* higher speed baudrate functions */
/* enable LINFlexD_UART reduced oversampling */
void linflexd_uart_reducedoversampling_enable(uint32_t linflexd_uart_periph);
/* disable LINFlexD_UART reduced oversampling */
void linflexd_uart_reducedoversampling_disable(uint32_t linflexd_uart_periph);
/* set LINFlexD_UART over sampling rate */
void linflexd_uart_oversamplingrate_set(uint32_t linflexd_uart_periph, uint8_t osrcount);
/* set LINFlexD_UART configurable sample points */
void linflexd_uart_samplepoint_set(uint32_t linflexd_uart_periph, uint8_t cspcount);

/* interrupt and flag functions */
/* return LINFlexD_UART flag */
FlagStatus linflexd_uart_flag_get(uint32_t linflexd_uart_periph, linflexd_uart_flag_enum flag);
/* clear LINFlexD_UART interrupt flag */
void linflexd_uart_flag_clear(uint32_t linflexd_uart_periph, linflexd_uart_flag_enum flag);
/* enable LINFlexD_UART interrupt */
void linflexd_uart_interrupt_enable(uint32_t linflexd_uart_periph, linflexd_uart_interrupt_enum interrupt);
/* disable LINFlexD_UART interrupt */
void linflexd_uart_interrupt_disable(uint32_t linflexd_uart_periph, linflexd_uart_interrupt_enum interrupt);
/* get LINFlexD_UART interrupt flag */
FlagStatus linflexd_uart_interrupt_flag_get(uint32_t linflexd_uart_periph, linflexd_uart_interrupt_flag_enum int_flag);
/* clear LINFlexD_UART interrupt flag */
void linflexd_uart_interrupt_flag_clear(uint32_t linflexd_uart_periph, linflexd_uart_interrupt_flag_enum int_flag);

#endif /* GD32A7XX_LINFLEXD_UART_H */
