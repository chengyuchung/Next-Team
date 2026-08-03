/*!
    \file    gd32a7xx_linflexd_lin.h
    \brief   definitions for the LINFLEXD LIN

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

#ifndef GD32A7XX_LINFLEXD_LIN_H
#define GD32A7XX_LINFLEXD_LIN_H

#include "gd32a7xx.h"

/* peripheral definitions */
/* peripheral base addresses */
#define LINFLEXD_LIN0           (LINFLEXD_BASE + 0x8000U)    /*!< LINFlexD0 base address */
#define LINFLEXD_LIN1           (LINFLEXD_BASE + 0x8400U)    /*!< LINFlexD1 base address */
#define LINFLEXD_LIN2           (LINFLEXD_BASE + 0x8800U)    /*!< LINFlexD2 base address */
#define LINFLEXD_LIN3           (LINFLEXD_BASE + 0x8C00U)    /*!< LINFlexD3 base address */
#define LINFLEXD_LIN4           (LINFLEXD_BASE + 0x9000U)    /*!< LINFlexD4 base address */
#define LINFLEXD_LIN5           (LINFLEXD_BASE + 0x9400U)    /*!< LINFlexD5 base address */

#define LINFLEXD_LIN6           (LINFLEXD_BASE)              /*!< LINFlexD6 base address */
#define LINFLEXD_LIN7           (LINFLEXD_BASE + 0x0400U)    /*!< LINFlexD7 base address */
#define LINFLEXD_LIN8           (LINFLEXD_BASE + 0x0800U)    /*!< LINFlexD8 base address */
#define LINFLEXD_LIN9           (LINFLEXD_BASE + 0x0C00U)    /*!< LINFlexD9 base address */
#define LINFLEXD_LIN10          (LINFLEXD_BASE + 0x1000U)    /*!< LINFlexD10 base address */
#define LINFLEXD_LIN11          (LINFLEXD_BASE + 0x1400U)    /*!< LINFlexD11 base address */

/* registers definitions */
#define LINFLEXD_LINCR1(linflexdx)    REG32((linflexdx) + 0x00000000U)              /*!< LIN control register 1 */
#define LINFLEXD_LINIER(linflexdx)    REG32((linflexdx) + 0x00000004U)              /*!< LIN interrupt enable register */
#define LINFLEXD_LINSR(linflexdx)     REG32((linflexdx) + 0x00000008U)              /*!< LIN status register */
#define LINFLEXD_LINESR(linflexdx)    REG32((linflexdx) + 0x0000000CU)              /*!< LIN error status register */
#define LINFLEXD_LINTCSR(linflexdx)   REG32((linflexdx) + 0x00000018U)              /*!< LIN timeout control status register */
#define LINFLEXD_LINOCR(linflexdx)    REG32((linflexdx) + 0x0000001CU)              /*!< LIN output compare register */
#define LINFLEXD_LINTOCR(linflexdx)   REG32((linflexdx) + 0x00000020U)              /*!< LIN timeout control register */
#define LINFLEXD_LINFBRR(linflexdx)   REG32((linflexdx) + 0x00000024U)              /*!< LIN fractional baud rate register */
#define LINFLEXD_LINIBRR(linflexdx)   REG32((linflexdx) + 0x00000028U)              /*!< LIN integer baud rate register */
#define LINFLEXD_LINCFR(linflexdx)    REG32((linflexdx) + 0x0000002CU)              /*!< LIN checksum field register */
#define LINFLEXD_LINCR2(linflexdx)    REG32((linflexdx) + 0x00000030U)              /*!< LIN control register 2 */
#define LINFLEXD_BIDR(linflexdx)      REG32((linflexdx) + 0x00000034U)              /*!< LIN buffer identifier register */
#define LINFLEXD_BDRL(linflexdx)      REG32((linflexdx) + 0x00000038U)              /*!< LIN buffer data register least significant */
#define LINFLEXD_BDRM(linflexdx)      REG32((linflexdx) + 0x0000003CU)              /*!< LIN buffer data register most significant */
#define LINFLEXD_IFER(linflexdx)      REG32((linflexdx) + 0x00000040U)              /*!< LIN identifier filter enable register */
#define LINFLEXD_IFMI(linflexdx)      REG32((linflexdx) + 0x00000044U)              /*!< LIN identifier filter match index */
#define LINFLEXD_IFMR(linflexdx)      REG32((linflexdx) + 0x00000048U)              /*!< LIN identifier filter mode register */
#define LINFLEXD_IFCR(linflexdx, n)   REG32((linflexdx) + 0x0000004CU + (n) * 0x4U) /*!< LIN identifier filter control register */
#define LINFLEXD_GCR(linflexdx)       REG32((linflexdx) + 0x0000008CU)              /*!< LIN global control register */
#define LINFLEXD_DMATXE(linflexdx)    REG32((linflexdx) + 0x00000098U)              /*!< LIN DMA Tx enable register */
#define LINFLEXD_DMARXE(linflexdx)    REG32((linflexdx) + 0x0000009CU)              /*!< LIN DMA Rx enable register */
#define LINFLEXD_LIN_STCTL(linflexdx) REG32((linflexdx) + 0x000000A0U)              /*!< LIN stop control register */

/* bits definitions */

/* LINFLEXD_LINCR1 */
#define LINFLEXD_LINCR1_INIT          BIT(0)                               /*!< initialization mode request */
#define LINFLEXD_LINCR1_SLEEP         BIT(1)                               /*!< sleep mode request */
#define LINFLEXD_LINCR1_RBLM          BIT(2)                               /*!< receiver buffer locked mode */
#define LINFLEXD_LINCR1_SSBL          BIT(3)                               /*!< slave mode sync break length */
#define LINFLEXD_LINCR1_MME           BIT(4)                               /*!< master mode enable */
#define LINFLEXD_LINCR1_LBKM          BIT(5)                               /*!< loop back mode */
#define LINFLEXD_LINCR1_BF            BIT(7)                               /*!< bypass filter */
#define LINFLEXD_LINCR1_MBL           BITS(8, 11)                          /*!< master break length */
#define LINFLEXD_LINCR1_AUTOWU        BIT(12)                              /*!< automatic wake-up */
#define LINFLEXD_LINCR1_LASE          BIT(13)                              /*!< LIN autosynchronization enable */
#define LINFLEXD_LINCR1_CFD           BIT(14)                              /*!< checksum field disable */
#define LINFLEXD_LINCR1_CCD           BIT(15)                              /*!< checksum calculation disable */
#define LINFLEXD_LINCR1_NLSE          BIT(16)                              /*!< LIN state capture enable on bit error */

/* LINFLEXD_LINIER */
#define LINFLEXD_LINIER_HRIE          BIT(0)                               /*!< header received interrupt enable */
#define LINFLEXD_LINIER_DTIE          BIT(1)                               /*!< data transmitted interrupt enable */
#define LINFLEXD_LINIER_DRIE          BIT(2)                               /*!< data reception complete interrupt enable */
#define LINFLEXD_LINIER_TOIE          BIT(3)                               /*!< timeout interrupt enable */
#define LINFLEXD_LINIER_WUIE          BIT(5)                               /*!< wakeup interrupt enable */
#define LINFLEXD_LINIER_LSIE          BIT(6)                               /*!< LIN state interrupt enable */
#define LINFLEXD_LINIER_BOIE          BIT(7)                               /*!< buffer overrun interrupt enable */
#define LINFLEXD_LINIER_FEIE          BIT(8)                               /*!< frame error interrupt enable */
#define LINFLEXD_LINIER_HEIE          BIT(11)                              /*!< header error interrupt enable */
#define LINFLEXD_LINIER_CEIE          BIT(12)                              /*!< checksum error interrupt enable */
#define LINFLEXD_LINIER_BEIE          BIT(13)                              /*!< bit error interrupt enable */
#define LINFLEXD_LINIER_OCIE          BIT(14)                              /*!< output compare interrupt enable */
#define LINFLEXD_LINIER_SZIE          BIT(15)                              /*!< stuck at zero interrupt enable */

/* LINFLEXD_LINSR */
#define LINFLEXD_LINSR_HRF            BIT(0)                               /*!< header received flag */
#define LINFLEXD_LINSR_DTF            BIT(1)                               /*!< data transmission completed flag */
#define LINFLEXD_LINSR_DRF            BIT(2)                               /*!< data reception completed flag */
#define LINFLEXD_LINSR_WUF            BIT(5)                               /*!< wakeup flag */
#define LINFLEXD_LINSR_RDI            BIT(6)                               /*!< receiver data input */
#define LINFLEXD_LINSR_RXBUSY         BIT(7)                               /*!< receiver busy flag */
#define LINFLEXD_LINSR_DRBNE          BIT(8)                               /*!< data reception buffer not empty flag */
#define LINFLEXD_LINSR_RMB            BIT(9)                               /*!< release message buffer */
#define LINFLEXD_LINSR_LINS           BITS(12, 15)                         /*!< LIN state */
#define LINFLEXD_LINSR_RDC            BITS(16, 18)                         /*!< receive data byte count */
#define LINFLEXD_LINSR_AUTOSYNC_COMP  BIT(19)                              /*!< autosynchronization complete */

/* LINFLEXD_LINESR */
#define LINFLEXD_LINESR_NF            BIT(0)                               /*!< noise flag */
#define LINFLEXD_LINESR_BOF           BIT(7)                               /*!< buffer overrun flag */
#define LINFLEXD_LINESR_FEF           BIT(8)                               /*!< framing error flag */
#define LINFLEXD_LINESR_IDPEF         BIT(9)                               /*!< ID parity error flag */
#define LINFLEXD_LINESR_SDEF          BIT(10)                              /*!< break delimiter error flag */
#define LINFLEXD_LINESR_SFEF          BIT(11)                              /*!< sync field error flag */
#define LINFLEXD_LINESR_CEF           BIT(12)                              /*!< checksum error flag */
#define LINFLEXD_LINESR_BEF           BIT(13)                              /*!< bit error flag */
#define LINFLEXD_LINESR_OCF           BIT(14)                              /*!< output compare flag */
#define LINFLEXD_LINESR_SZF           BIT(15)                              /*!< stuck at zero flag */

/* LINFLEXD_LINTCSR */
#define LINFLEXD_LINTCSR_MODE             BIT(10)            /*!< timeout counter mode */
#define LINFLEXD_LINTCSR_IOT              BIT(9)             /*!< idle on timeout */
#define LINFLEXD_LINTCSR_TOCE             BIT(8)             /*!< timeout counter enable */
#define LINFLEXD_LINTCSR_CNT              BITS(0,7)          /*!< counter value */

/* LINFLEXD_LINOCR */
#define LINFLEXD_LINOCR_OC2               BITS(8,15)         /*!< output compare value 2 */
#define LINFLEXD_LINOCR_OC1               BITS(0,7)          /*!< output compare value 1 */

/* LINFLEXD_LINTOCR */
#define LINFLEXD_LINTOCR_RTO              BITS(8,11)         /*!< response timeout value */
#define LINFLEXD_LINTOCR_HTO              BITS(0,6)          /*!< header timeout value */

/* LINFLEXD_LINFBRR */
#define LINFLEXD_LINFBRR_FBR              BITS(0,3)          /*!< fractional baud rate */

/* LINFLEXD_LINIBRR */
#define LINFLEXD_LINIBRR_IBR              BITS(0,19)         /*!< integer baud rate */

/* LINFLEXD_LINCFR */
#define LINFLEXD_LINCFR_CF                BITS(0,7)          /*!< checksum bits */

/* LINFLEXD_LINCR2 */
#define LINFLEXD_LINCR2_TBDE              BIT(15)            /*!< two-bit delimiter enable */
#define LINFLEXD_LINCR2_IOBE              BIT(14)            /*!< idle on bit error */
#define LINFLEXD_LINCR2_IOPE              BIT(13)            /*!< idle on identifier parity error */
#define LINFLEXD_LINCR2_WURQ              BIT(12)            /*!< wakeup generate request */
#define LINFLEXD_LINCR2_DDRQ              BIT(11)            /*!< data discard request */
#define LINFLEXD_LINCR2_DTRQ              BIT(10)            /*!< data transmission request */
#define LINFLEXD_LINCR2_ABRQ              BIT(9)             /*!< abort request */
#define LINFLEXD_LINCR2_HTRQ              BIT(8)             /*!< header transmission request */

/* LINFLEXD_BIDR */
#define LINFLEXD_BIDR_DFL                 BITS(10,12)        /*!< data field length */
#define LINFLEXD_BIDR_DIR                 BIT(9)             /*!< direction */
#define LINFLEXD_BIDR_CCS                 BIT(8)             /*!< classic checksum */
#define LINFLEXD_BIDR_ID                  BITS(0,5)          /*!< identifier part */

/* LINFLEXD_BDRL */
#define LINFLEXD_BDRL_DATA3               BITS(24,31)        /*!< data byte 3 */
#define LINFLEXD_BDRL_DATA2               BITS(16,23)        /*!< data byte 2 */
#define LINFLEXD_BDRL_DATA1               BITS(8,15)         /*!< data byte 1 */
#define LINFLEXD_BDRL_DATA0               BITS(0,7)          /*!< data byte 0 */

/* LINFLEXD_BDRM */
#define LINFLEXD_BDRM_DATA7               BITS(24,31)        /*!< data byte 7 */
#define LINFLEXD_BDRM_DATA6               BITS(16,23)        /*!< data byte 6 */
#define LINFLEXD_BDRM_DATA5               BITS(8,15)         /*!< data byte 5 */
#define LINFLEXD_BDRM_DATA4               BITS(0,7)          /*!< data byte 4 */

/* LINFLEXD_IFER */
#define LINFLEXD_IFER_FACT15              BIT(15)            /*!< filter active 15 */
#define LINFLEXD_IFER_FACT14              BIT(14)            /*!< filter active 14 */
#define LINFLEXD_IFER_FACT13              BIT(13)            /*!< filter active 13 */
#define LINFLEXD_IFER_FACT12              BIT(12)            /*!< filter active 12 */
#define LINFLEXD_IFER_FACT11              BIT(11)            /*!< filter active 11 */
#define LINFLEXD_IFER_FACT10              BIT(10)            /*!< filter active 10 */
#define LINFLEXD_IFER_FACT9               BIT(9)             /*!< filter active 9 */
#define LINFLEXD_IFER_FACT8               BIT(8)             /*!< filter active 8 */
#define LINFLEXD_IFER_FACT7               BIT(7)             /*!< filter active 7 */
#define LINFLEXD_IFER_FACT6               BIT(6)             /*!< filter active 6 */
#define LINFLEXD_IFER_FACT5               BIT(5)             /*!< filter active 5 */
#define LINFLEXD_IFER_FACT4               BIT(4)             /*!< filter active 4 */
#define LINFLEXD_IFER_FACT3               BIT(3)             /*!< filter active 3 */
#define LINFLEXD_IFER_FACT2               BIT(2)             /*!< filter active 2 */
#define LINFLEXD_IFER_FACT1               BIT(1)             /*!< filter active 1 */
#define LINFLEXD_IFER_FACT0               BIT(0)             /*!< filter active 0 */

/* LINFLEXD_IFMI */
#define LINFLEXD_IFMI_IFMI                BITS(0,4)          /*!< filter match index */

/* LINFLEXD_IFMR */
#define LINFLEXD_IFMR_IFM7                BIT(7)             /*!< filter mode 7 */
#define LINFLEXD_IFMR_IFM6                BIT(6)             /*!< filter mode 6 */
#define LINFLEXD_IFMR_IFM5                BIT(5)             /*!< filter mode 5 */
#define LINFLEXD_IFMR_IFM4                BIT(4)             /*!< filter mode 4 */
#define LINFLEXD_IFMR_IFM3                BIT(3)             /*!< filter mode 3 */
#define LINFLEXD_IFMR_IFM2                BIT(2)             /*!< filter mode 2 */
#define LINFLEXD_IFMR_IFM1                BIT(1)             /*!< filter mode 1 */
#define LINFLEXD_IFMR_IFM0                BIT(0)             /*!< filter mode 0 */

/* LINFLEXD_IFCR */
#define LINFLEXD_IFCR_DFL                 BITS(10,12)        /*!< data field length */
#define LINFLEXD_IFCR_DIR                 BIT(9)             /*!< direction */
#define LINFLEXD_IFCR_CSS                 BIT(8)             /*!< classic checksum */
#define LINFLEXD_IFCR_ID                  BITS(0,5)          /*!< identifier */

/* LINFLEXD_GCR */
#define LINFLEXD_GCR_TDFBM                BIT(5)             /*!< transmit data first bit MSB */
#define LINFLEXD_GCR_RDFBM                BIT(4)             /*!< receive data first bit MSB */
#define LINFLEXD_GCR_TDLIS                BIT(3)             /*!< transmit data level inversion selection */
#define LINFLEXD_GCR_RDLIS                BIT(2)             /*!< received data level inversion selection */
#define LINFLEXD_GCR_STOP                 BIT(1)             /*!< one or two stop bit configuration */
#define LINFLEXD_GCR_SR                   BIT(0)             /*!< soft reset */

/* LINFLEXD_DMATXE */
#define LINFLEXD_DMATXE_DTE15             BIT(15)            /*!< DMA Tx channel 15 enable */
#define LINFLEXD_DMATXE_DTE14             BIT(14)            /*!< DMA Tx channel 14 enable */
#define LINFLEXD_DMATXE_DTE13             BIT(13)            /*!< DMA Tx channel 13 enable */
#define LINFLEXD_DMATXE_DTE12             BIT(12)            /*!< DMA Tx channel 12 enable */
#define LINFLEXD_DMATXE_DTE11             BIT(11)            /*!< DMA Tx channel 11 enable */
#define LINFLEXD_DMATXE_DTE10             BIT(10)            /*!< DMA Tx channel 10 enable */
#define LINFLEXD_DMATXE_DTE9              BIT(9)             /*!< DMA Tx channel 9 enable */
#define LINFLEXD_DMATXE_DTE8              BIT(8)             /*!< DMA Tx channel 8 enable */
#define LINFLEXD_DMATXE_DTE7              BIT(7)             /*!< DMA Tx channel 7 enable */
#define LINFLEXD_DMATXE_DTE6              BIT(6)             /*!< DMA Tx channel 6 enable */
#define LINFLEXD_DMATXE_DTE5              BIT(5)             /*!< DMA Tx channel 5 enable */
#define LINFLEXD_DMATXE_DTE4              BIT(4)             /*!< DMA Tx channel 4 enable */
#define LINFLEXD_DMATXE_DTE3              BIT(3)             /*!< DMA Tx channel 3 enable */
#define LINFLEXD_DMATXE_DTE2              BIT(2)             /*!< DMA Tx channel 2 enable */
#define LINFLEXD_DMATXE_DTE1              BIT(1)             /*!< DMA Tx channel 1 enable */
#define LINFLEXD_DMATXE_DTE0              BIT(0)             /*!< DMA Tx channel 0 enable */

/* LINFLEXD_DMARXE */
#define LINFLEXD_DMARXE_DRE15             BIT(15)            /*!< DMA Rx channel 15 enable */
#define LINFLEXD_DMARXE_DRE14             BIT(14)            /*!< DMA Rx channel 14 enable */
#define LINFLEXD_DMARXE_DRE13             BIT(13)            /*!< DMA Rx channel 13 enable */
#define LINFLEXD_DMARXE_DRE12             BIT(12)            /*!< DMA Rx channel 12 enable */
#define LINFLEXD_DMARXE_DRE11             BIT(11)            /*!< DMA Rx channel 11 enable */
#define LINFLEXD_DMARXE_DRE10             BIT(10)            /*!< DMA Rx channel 10 enable */
#define LINFLEXD_DMARXE_DRE9              BIT(9)             /*!< DMA Rx channel 9 enable */
#define LINFLEXD_DMARXE_DRE8              BIT(8)             /*!< DMA Rx channel 8 enable */
#define LINFLEXD_DMARXE_DRE7              BIT(7)             /*!< DMA Rx channel 7 enable */
#define LINFLEXD_DMARXE_DRE6              BIT(6)             /*!< DMA Rx channel 6 enable */
#define LINFLEXD_DMARXE_DRE5              BIT(5)             /*!< DMA Rx channel 5 enable */
#define LINFLEXD_DMARXE_DRE4              BIT(4)             /*!< DMA Rx channel 4 enable */
#define LINFLEXD_DMARXE_DRE3              BIT(3)             /*!< DMA Rx channel 3 enable */
#define LINFLEXD_DMARXE_DRE2              BIT(2)             /*!< DMA Rx channel 2 enable */
#define LINFLEXD_DMARXE_DRE1              BIT(1)             /*!< DMA Rx channel 1 enable */
#define LINFLEXD_DMARXE_DRE0              BIT(0)             /*!< DMA Rx channel 0 enable */

/* LINFLEXD_LIN_STCTL */
#define LINFLEXD_LIN_STCTL_RX_INV         BIT(5)             /*!< RX pin level inversion */
#define LINFLEXD_LIN_STCTL_TX_INV         BIT(4)             /*!< TX pin level inversion */
#define LINFLEXD_LIN_STCTL_SIZE           BITS(2,3)          /*!< the byte size transmitted on the IPS bus */
#define LINFLEXD_LIN_STCTL_ACK            BIT(1)             /*!< the stop function takes effect */
#define LINFLEXD_LIN_STCTL_STOP           BIT(0)             /*!< terminate the transmission */

/* constants definitions */
/* define the LINFLEXD bit position and its register index offset */
#define LINFLEXD_REGIDX_BIT(regidx, bitpos)    (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define LINFLEXD_REG_VAL(linflexdx, offset)    (REG32((linflexdx) + (((uint32_t)(offset) & 0x0000FFFFU) >> 6)))
#define LINFLEXD_BIT_POS(val)                  ((uint32_t)((uint32_t)(val) & 0x1FU))
#define LINFLEXD_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22) | (uint32_t)((bitpos2) << 16)\
                                                              | (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos)))
#define LINFLEXD_REG_VAL2(linflexdx, offset)   (REG32((linflexdx) + ((uint32_t)(offset) >> 22)))
#define LINFLEXD_BIT_POS2(val)                 (((uint32_t)(val) & 0x001F0000U) >> 16)

/* register offset */
#define LINFLEXD_LINCR1_REG_OFFSET             0x00000000U                 /*!< LINCR1 register offset */
#define LINFLEXD_LINIER_REG_OFFSET             0x00000004U                 /*!< LINIER register offset */
#define LINFLEXD_LINSR_REG_OFFSET              0x00000008U                 /*!< LINSR register offset */
#define LINFLEXD_LINESR_REG_OFFSET             0x0000000CU                 /*!< LINESR register offset */
#define LINFLEXD_DMATXE_REG_OFFSET             0x00000098U                 /*!< DMATXE register offset */
#define LINFLEXD_DMARXE_REG_OFFSET             0x0000009CU                 /*!< DMArXE register offset */

/* master break length */
#define LINFLEXD_BREAK_LENGTH_10_BIT           ((uint32_t)0x00000000U)     /*!< 10-bit break length */
#define LINFLEXD_BREAK_LENGTH_11_BIT           ((uint32_t)0x00000100U)     /*!< 11-bit break length */
#define LINFLEXD_BREAK_LENGTH_12_BIT           ((uint32_t)0x00000200U)     /*!< 12-bit break length */
#define LINFLEXD_BREAK_LENGTH_13_BIT           ((uint32_t)0x00000300U)     /*!< 13-bit break length */
#define LINFLEXD_BREAK_LENGTH_14_BIT           ((uint32_t)0x00000400U)     /*!< 14-bit break length */
#define LINFLEXD_BREAK_LENGTH_15_BIT           ((uint32_t)0x00000500U)     /*!< 15-bit break length */
#define LINFLEXD_BREAK_LENGTH_16_BIT           ((uint32_t)0x00000600U)     /*!< 16-bit break length */
#define LINFLEXD_BREAK_LENGTH_17_BIT           ((uint32_t)0x00000700U)     /*!< 17-bit break length */
#define LINFLEXD_BREAK_LENGTH_18_BIT           ((uint32_t)0x00000800U)     /*!< 18-bit break length */
#define LINFLEXD_BREAK_LENGTH_19_BIT           ((uint32_t)0x00000900U)     /*!< 19-bit break length */
#define LINFLEXD_BREAK_LENGTH_20_BIT           ((uint32_t)0x00000A00U)     /*!< 20-bit break length */
#define LINFLEXD_BREAK_LENGTH_21_BIT           ((uint32_t)0x00000B00U)     /*!< 21-bit break length */
#define LINFLEXD_BREAK_LENGTH_22_BIT           ((uint32_t)0x00000C00U)     /*!< 22-bit break length */
#define LINFLEXD_BREAK_LENGTH_23_BIT           ((uint32_t)0x00000D00U)     /*!< 23-bit break length */
#define LINFLEXD_BREAK_LENGTH_36_BIT           ((uint32_t)0x00000E00U)     /*!< 36-bit break length */
#define LINFLEXD_BREAK_LENGTH_50_BIT           ((uint32_t)0x00000F00U)     /*!< 50-bit break length */

/* slave mode sync break length */
#define LINFLEXD_SLAVE_BREAK_11_BIT             ((uint32_t)0x00000000U)    /*!< 11-bit break length */
#define LINFLEXD_SLAVE_BREAK_10_BIT             LINFLEXD_LINCR1_SSBL       /*!< 10-bit break length */

/* receiver buffer locked mode */
#define LINFLEXD_RECEIVER_BUFFER_NORMAL       ((uint32_t)0x00000000U)      /*!< normal receiver buffer mode */
#define LINFLEXD_RECEIVER_BUFFER_LOCKED       LINFLEXD_LINCR1_RBLM         /*!< receiver buffer locked mode */

/* bypass filter */
#define BYPASS_LINFLEXD_FILTER_DISABLE          ((uint32_t)0x00000000U)    /*!< bypass filter disable */
#define BYPASS_LINFLEXD_FILTER_ENABLE           LINFLEXD_LINCR1_BF         /*!< bypass filter enable */
                                                                          
/* automatic wake up */                                                   
#define LINFLEXD_WAKEUP_SOFTWARE_CLEAR          ((uint32_t)0x00000000U)    /*!< software wake-up */
#define LINFLEXD_WAKEUP_HARDWARE_CLEAR          LINFLEXD_LINCR1_AUTOWU     /*!< automatic wake-up */
                                                                          
/* LIN autosynchronization enable */                                      
#define LINFLEXD_AUTOSYNC_DISABLE               ((uint32_t)0x00000000U)    /*!< auto synchronization disable */
#define LINFLEXD_AUTOSYNC_ENABLE                LINFLEXD_LINCR1_LASE       /*!< auto synchronization enable */
                                                                          
/* checksum field disable */                                              
#define LINFLEXD_CHECKSUM_FIELD_ENABLE          ((uint32_t)0x00000000U)    /*!< checksum field enable */
#define LINFLEXD_CHECKSUM_FIELD_DISABLE         LINFLEXD_LINCR1_CFD        /*!< checksum field disable */
                                                                          
/* checksum calculation disable */                                        
#define LINFLEXD_CHECKSUM_CALC_ENABLE           ((uint32_t)0x00000000U)    /*!< checksum calculation enable */
#define LINFLEXD_CHECKSUM_CALC_DISABLE          LINFLEXD_LINCR1_CCD        /*!< checksum calculation disable */
                                                                          
/* LIN state capture enable on bit error */                               
#define LINFLEXD_STATE_CAPTURE_DISABLE          ((uint32_t)0x00000000U)    /*!< LIN state capture disable */
#define LINFLEXD_STATE_CAPTURE_ENABLE           LINFLEXD_LINCR1_NLSE       /*!< LIN state capture enable */

/* LIN mode state */
#define LINFLEXD_LIN_STATE(regval)             (BITS(12, 15) & ((uint32_t)(regval) << 12U))
#define LINFLEXD_LIN_STATE_IDLE                LINFLEXD_LIN_STATE(0)       /*!< idle state */
#define LINFLEXD_LIN_STATE_SYNC_BREAK          LINFLEXD_LIN_STATE(1)       /*!< sync break state */
#define LINFLEXD_LIN_STATE_SYNC_DEL            LINFLEXD_LIN_STATE(2)       /*!< sync del state */
#define LINFLEXD_LIN_STATE_SYNC                LINFLEXD_LIN_STATE(3)       /*!< sync state */
#define LINFLEXD_LIN_STATE_ID                  LINFLEXD_LIN_STATE(4)       /*!< ID state */
#define LINFLEXD_LIN_STATE_HEADER_RX           LINFLEXD_LIN_STATE(5)       /*!< header rx state */
#define LINFLEXD_LIN_STATE_HEADER_TX           LINFLEXD_LIN_STATE(6)       /*!< header tx state */
#define LINFLEXD_LIN_STATE_DATA_RX             LINFLEXD_LIN_STATE(7)       /*!< data rx state */
#define LINFLEXD_LIN_STATE_DATA_TX             LINFLEXD_LIN_STATE(8)       /*!< data tx state */
#define LINFLEXD_LIN_STATE_CHECKSUM            LINFLEXD_LIN_STATE(9)       /*!< checksum state */

/* LINFLEXD flags */
typedef enum {
    /* flags in LINSR */
    LINFLEXD_FLAG_HRF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINSR_REG_OFFSET, 0U),      /*!< header received flag */
    LINFLEXD_FLAG_DTF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINSR_REG_OFFSET, 1U),      /*!< data transmission completed flag */
    LINFLEXD_FLAG_DRF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINSR_REG_OFFSET, 2U),      /*!< data reception completed flag */
    LINFLEXD_FLAG_WUF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINSR_REG_OFFSET, 5U),      /*!< wakeup flag */
    LINFLEXD_FLAG_RXBUSY          = LINFLEXD_REGIDX_BIT(LINFLEXD_LINSR_REG_OFFSET, 7U),      /*!< receiver busy flag */
    LINFLEXD_FLAG_DRBNE           = LINFLEXD_REGIDX_BIT(LINFLEXD_LINSR_REG_OFFSET, 8U),      /*!< data reception buffer not empty flag */
    LINFLEXD_FLAG_RMB             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINSR_REG_OFFSET, 9U),      /*!< release message buffer */
    LINFLEXD_FLAG_AUTOSYNC_COMP   = LINFLEXD_REGIDX_BIT(LINFLEXD_LINSR_REG_OFFSET, 19U),     /*!< autosynchronization complete */
    /* flags in LINESR */
    LINFLEXD_FLAG_NF              = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 0U),     /*!< noise flag */
    LINFLEXD_FLAG_BOF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 7U),     /*!< buffer overrun flag */
    LINFLEXD_FLAG_FEF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 8U),     /*!< framing error flag */
    LINFLEXD_FLAG_IDPEF           = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 9U),     /*!< ID parity error flag */
    LINFLEXD_FLAG_SDEF            = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 10U),    /*!< break delimiter error flag */
    LINFLEXD_FLAG_SFEF            = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 11U),    /*!< sync field error flag */
    LINFLEXD_FLAG_CEF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 12U),    /*!< checksum error flag */
    LINFLEXD_FLAG_BEF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 13U),    /*!< bit error flag */
    LINFLEXD_FLAG_OCF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 14U),    /*!< output compare flag */
    LINFLEXD_FLAG_SZF             = LINFLEXD_REGIDX_BIT(LINFLEXD_LINESR_REG_OFFSET, 15U),    /*!< stuck at zero flag */
} linflexd_flag_enum;

/* LINFLEXD interrupt flags */
typedef enum {
    /* interrupt flags in LINSR and LINIER */
    LINFLEXD_INT_FLAG_HRF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINSR_REG_OFFSET, 0U, LINFLEXD_LINIER_REG_OFFSET, 0U),   /*!< header received interrupt and flag */
    LINFLEXD_INT_FLAG_DTF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINSR_REG_OFFSET, 1U, LINFLEXD_LINIER_REG_OFFSET, 1U),   /*!< data transmission completed interrupt and flag */
    LINFLEXD_INT_FLAG_DRF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINSR_REG_OFFSET, 2U, LINFLEXD_LINIER_REG_OFFSET, 2U),   /*!< data reception completed interrupt and flag */
    LINFLEXD_INT_FLAG_WUF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINSR_REG_OFFSET, 5U, LINFLEXD_LINIER_REG_OFFSET, 5U),   /*!< wakeup interrupt and flag */
    /* interrupt flags in LINESR and LINIER */
    LINFLEXD_INT_FLAG_BOF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 7U,  LINFLEXD_LINIER_REG_OFFSET, 7U),  /*!< buffer overrun interrupt and flag */
    LINFLEXD_INT_FLAG_FEF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 8U,  LINFLEXD_LINIER_REG_OFFSET, 8U),  /*!< framing error interrupt and flag */
    LINFLEXD_INT_FLAG_IDPEF          = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 9U,  LINFLEXD_LINIER_REG_OFFSET, 11U), /*!< ID parity error interrupt and flag */
    LINFLEXD_INT_FLAG_SDEF           = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 10U, LINFLEXD_LINIER_REG_OFFSET, 11U), /*!< Sync Break delimiter error interrupt and flag */
    LINFLEXD_INT_FLAG_SFEF           = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 11U, LINFLEXD_LINIER_REG_OFFSET, 11U), /*!< Sync field error interrupt and flag */
    LINFLEXD_INT_FLAG_CEF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 12U, LINFLEXD_LINIER_REG_OFFSET, 12U), /*!< checksum error interrupt and flag */
    LINFLEXD_INT_FLAG_BEF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 13U, LINFLEXD_LINIER_REG_OFFSET, 13U), /*!< bit error interrupt and flag */
    LINFLEXD_INT_FLAG_OCF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 14U, LINFLEXD_LINIER_REG_OFFSET, 14U), /*!< output compare interrupt and flag */
    LINFLEXD_INT_FLAG_SZF            = LINFLEXD_REGIDX_BIT2(LINFLEXD_LINESR_REG_OFFSET, 15U, LINFLEXD_LINIER_REG_OFFSET, 15U), /*!< stuck at zero interrupt and flag */
} linflexd_interrupt_flag_enum;

/* LINFLEXD interrupts */
typedef enum {
    /* interrupts in LINIER */
    LINFLEXD_INT_HRIE               = LINFLEXD_LINIER_HRIE,   /*!< header received interrupt */
    LINFLEXD_INT_DTIE               = LINFLEXD_LINIER_DTIE,   /*!< data transmitted interrupt */
    LINFLEXD_INT_DRIE               = LINFLEXD_LINIER_DRIE,   /*!< data reception complete interrupt */
    LINFLEXD_INT_TOIE               = LINFLEXD_LINIER_TOIE,   /*!< timeout interrupt */
    LINFLEXD_INT_WUIE               = LINFLEXD_LINIER_WUIE,   /*!< wakeup interrupt */
    LINFLEXD_INT_LSIE               = LINFLEXD_LINIER_LSIE,   /*!< LIN state interrupt */
    LINFLEXD_INT_BOIE               = LINFLEXD_LINIER_BOIE,   /*!< buffer overrun interrupt */
    LINFLEXD_INT_FEIE               = LINFLEXD_LINIER_FEIE,   /*!< frame error interrupt */
    LINFLEXD_INT_HEIE               = LINFLEXD_LINIER_HEIE,  /*!< header error interrupt */
    LINFLEXD_INT_CEIE               = LINFLEXD_LINIER_CEIE,  /*!< checksum error interrupt */
    LINFLEXD_INT_BEIE               = LINFLEXD_LINIER_BEIE,  /*!< bit error interrupt */
    LINFLEXD_INT_OCIE               = LINFLEXD_LINIER_OCIE,  /*!< output compare interrupt */
    LINFLEXD_INT_SZIE               = LINFLEXD_LINIER_SZIE,  /*!< stuck at zero interrupt */
} linflexd_interrupt_enum;

/* LINFLEXD dma tx channel */
typedef enum {
    /* interrupts in LINIER */
    LINFLEXD_DMATX_CHANNEL0            = LINFLEXD_DMATXE_DTE0,   /*!< header received interrupt */
    LINFLEXD_DMATX_CHANNEL1            = LINFLEXD_DMATXE_DTE1,   /*!< data transmitted interrupt */
    LINFLEXD_DMATX_CHANNEL2            = LINFLEXD_DMATXE_DTE2,   /*!< data reception complete interrupt */
    LINFLEXD_DMATX_CHANNEL3            = LINFLEXD_DMATXE_DTE3,   /*!< timeout interrupt */
    LINFLEXD_DMATX_CHANNEL4            = LINFLEXD_DMATXE_DTE4,   /*!< wakeup interrupt */
    LINFLEXD_DMATX_CHANNEL5            = LINFLEXD_DMATXE_DTE5,   /*!< LIN state interrupt */
    LINFLEXD_DMATX_CHANNEL6            = LINFLEXD_DMATXE_DTE6,   /*!< buffer overrun interrupt */
    LINFLEXD_DMATX_CHANNEL7            = LINFLEXD_DMATXE_DTE7,   /*!< frame error interrupt */
    LINFLEXD_DMATX_CHANNEL8            = LINFLEXD_DMATXE_DTE8,  /*!< header error interrupt */
    LINFLEXD_DMATX_CHANNEL9            = LINFLEXD_DMATXE_DTE9,  /*!< checksum error interrupt */
    LINFLEXD_DMATX_CHANNEL10           = LINFLEXD_DMATXE_DTE10,  /*!< bit error interrupt */
    LINFLEXD_DMATX_CHANNEL11           = LINFLEXD_DMATXE_DTE11,  /*!< output compare interrupt */
    LINFLEXD_DMATX_CHANNEL12           = LINFLEXD_DMATXE_DTE12,  /*!< stuck at zero interrupt */
    LINFLEXD_DMATX_CHANNEL13           = LINFLEXD_DMATXE_DTE13,  /*!< bit error interrupt */
    LINFLEXD_DMATX_CHANNEL14           = LINFLEXD_DMATXE_DTE14,  /*!< output compare interrupt */
    LINFLEXD_DMATX_CHANNEL15           = LINFLEXD_DMATXE_DTE15,  /*!< stuck at zero interrupt */
} linflexd_dma_tx_channel_enum;

/* LINFLEXD dma rx channel */
typedef enum {
    /* interrupts in LINIER */
    LINFLEXD_DMARX_CHANNEL0            = LINFLEXD_DMARXE_DRE0,   /*!< header received interrupt */
    LINFLEXD_DMARX_CHANNEL1            = LINFLEXD_DMARXE_DRE1,   /*!< data transmitted interrupt */
    LINFLEXD_DMARX_CHANNEL2            = LINFLEXD_DMARXE_DRE2,   /*!< data reception complete interrupt */
    LINFLEXD_DMARX_CHANNEL3            = LINFLEXD_DMARXE_DRE3,   /*!< timeout interrupt */
    LINFLEXD_DMARX_CHANNEL4            = LINFLEXD_DMARXE_DRE4,   /*!< wakeup interrupt */
    LINFLEXD_DMARX_CHANNEL5            = LINFLEXD_DMARXE_DRE5,   /*!< LIN state interrupt */
    LINFLEXD_DMARX_CHANNEL6            = LINFLEXD_DMARXE_DRE6,   /*!< buffer overrun interrupt */
    LINFLEXD_DMARX_CHANNEL7            = LINFLEXD_DMARXE_DRE7,   /*!< frame error interrupt */
    LINFLEXD_DMARX_CHANNEL8            = LINFLEXD_DMARXE_DRE8,  /*!< header error interrupt */
    LINFLEXD_DMARX_CHANNEL9            = LINFLEXD_DMARXE_DRE9,  /*!< checksum error interrupt */
    LINFLEXD_DMARX_CHANNEL10           = LINFLEXD_DMARXE_DRE10,  /*!< bit error interrupt */
    LINFLEXD_DMARX_CHANNEL11           = LINFLEXD_DMARXE_DRE11,  /*!< output compare interrupt */
    LINFLEXD_DMARX_CHANNEL12           = LINFLEXD_DMARXE_DRE12,  /*!< stuck at zero interrupt */
    LINFLEXD_DMARX_CHANNEL13           = LINFLEXD_DMARXE_DRE13,  /*!< bit error interrupt */
    LINFLEXD_DMARX_CHANNEL14           = LINFLEXD_DMARXE_DRE14,  /*!< output compare interrupt */
    LINFLEXD_DMARX_CHANNEL15           = LINFLEXD_DMARXE_DRE15,  /*!< stuck at zero interrupt */
} linflexd_dma_rx_channel_enum;

/* LINFLEXD node enum */
typedef enum
{
    LINFlexD_SLAVE = 0U,        /*!< Node acts as a slave in LINFlexD mode */
    LINFlexD_MASTER = 1U,       /*!< Node acts as a master in LINFlexD mode */
} linflexd_lin_node_enum;

typedef enum
{
    LIN_ENHANCED_CHECKSUM = 0,    /*!< LINFlexD enhanced checksum method */
    LIN_CLASSIC_CHECKSUM = 1      /*!< LINFlexD classical checksum method */
} linflexd_lin_checksum_enum;

typedef enum
{
    LIN_MASTER_RESPONSE = 0,    /*!< LIN master send response, slave receive */
    LIN_SLAVE_RESPONSE = 1,    /*!< LIN slave send response, master receive */
    LIN_SLAVE_TO_SLAVE = 2     /*!< LIN slave send response, slave receive
                                        Master only send out header */
} linflexd_lin_response_enum;

typedef enum
{
    LINFlexD_RX = 0U,        /*!< Receive frames in LIN */
    LINFlexD_TX = 1U         /*!< Transmit frames in LIN */
} linflexd_lin_direction_enum;

typedef enum
{
    LINFlexD_DMA_RX = 0U,        /*!< Receive frames in LIN */
    LINFlexD_DMA_TX = 1U         /*!< Transmit frames in LIN */
} linflexd_lin_dma_direction_enum;

typedef enum
{
    LINFlexD_BREAK_10_BIT = 0x00U,                      /*!< LIN break 10 bits */
    LINFlexD_BREAK_11_BIT = 0x01U,                      /*!< LIN break 11 bits */
    LINFlexD_BREAK_12_BIT = 0x02U,                      /*!< LIN break 12 bits */
    LINFlexD_BREAK_13_BIT = 0x03U,                      /*!< LIN break 13 bits */
    LINFlexD_BREAK_14_BIT = 0x04U,                      /*!< LIN break 14 bits */
    LINFlexD_BREAK_15_BIT = 0x05U,                      /*!< LIN break 15 bits */
    LINFlexD_BREAK_16_BIT = 0x06U,                      /*!< LIN break 16 bits */
    LINFlexD_BREAK_17_BIT = 0x07U,                      /*!< LIN break 17 bits */
    LINFlexD_BREAK_18_BIT = 0x08U,                      /*!< LIN break 18 bits */
    LINFlexD_BREAK_19_BIT = 0x09U,                      /*!< LIN break 19 bits */
    LINFlexD_BREAK_20_BIT = 0x10U,                      /*!< LIN break 20 bits */
    LINFlexD_BREAK_21_BIT = 0x11U,                      /*!< LIN break 21 bits */
    LINFlexD_BREAK_22_BIT = 0x12U,                      /*!< LIN break 22 bits */
    LINFlexD_BREAK_23_BIT = 0x13U,                      /*!< LIN break 23 bits */
    LINFlexD_BREAK_36_BIT = 0x14U,                      /*!< LIN break 36 bits */
    LINFlexD_BREAK_50_BIT = 0x15U,                      /*!< LIN break 50 bits */
} linflexd_lin_break_length_enum;

typedef enum
{
    LINFlexD_STATE_SLEEP_MODE = 0U,                     /*!< Sleep mode */
    LINFlexD_STATE_INIT_MODE = 1U,                      /*!< Initialization mode */
    LINFlexD_STATE_IDLE_MODE = 2U,                      /*!< Idle mode */
    LINFlexD_STATE_SYNC_BREAK = 3U,                     /*!< Sync break */
    LINFlexD_STATE_SYNC_DEL = 4U,                       /*!< Sync delimiter */
    LINFlexD_STATE_SYNC_FIELD = 5U,                     /*!< Sync field */
    LINFlexD_STATE_IDENTIFIER_FIELD = 6U,               /*!< Identifier field */
    LINFlexD_STATE_HEADER_RX_TX = 7U,                   /*!< Header transmit/receive */
    LINFlexD_STATE_DATA_RX_TX = 8U,                     /*!< Data transmit/receive */
    LINFlexD_STATE_CHECKSUM = 9U                        /*!< Check sum */
} linflexd_lin_hw_state_enum;

typedef enum
{
    /* Generic error codes */
    STATUS_SUCCESS                         = 0x000U,    /*!< Generic operation success status */
    STATUS_ERROR                           = 0x001U,    /*!< Generic operation failure status */
    STATUS_BUSY                            = 0x002U,    /*!< Generic operation busy status */
    STATUS_TIMEOUT                         = 0x003U,    /*!< Generic operation timeout status */
    STATUS_UNSUPPORTED                     = 0x004U,    /*!< Generic operation unsupported status */
    STATUS_NOCLOCK                         = 0x005U,    /*!< Generic operation noclock status */
    STATUS_InvalidArgument                 = 0x006U,    /*!< Generic operation invalid argument status */
    /* UART specific error codes */
    STATUS_UART_TX_UNDERRUN                = 0x600U,  /*!< TX underrun error */
    STATUS_UART_RX_OVERRUN                 = 0x601U,  /*!< RX overrun error */
    STATUS_UART_ABORTED                    = 0x602U,  /*!< A transfer was aborted */
    STATUS_UART_FRAMING_ERROR              = 0x603U,  /*!< Framing error */
    STATUS_UART_PARITY_ERROR               = 0x604U,  /*!< Parity error */
    STATUS_UART_NOISE_ERROR                = 0x605U,  /*!< Noise error */
    STATUS_UART_IDLE_ERROR                 = 0x606U,  /*!< Line idle error */
    /* LINFlexD specific error codes */
    STATUS_LINFlexD_NO_HEADER_RECEIVED     = 0x700U,  /*!< LINFlexD no header received */
    STATUS_LINFlexD_ABORT_TIMEOUT          = 0x701U,  /*!< LINFlexD abort transfer timeout error*/
} linflexd_lin_status_enum;

/* LINFLEXD id filter structure */
typedef struct
{
    FlagStatus filterEnable;                      /*!< Enable the id filters */
    uint8_t maskEnable;                           /*!< Mask enable for filter pairs */
    uint32_t dataFieldLength;                      /*!< LIN frame data length */
    linflexd_lin_direction_enum direction;        /*!< The direction of data field */
    linflexd_lin_checksum_enum checksumType;      /*!< LIN Checksum method */
    uint8_t id;                                   /*!< LIN ID */
    uint8_t data[8];                              /*!< LIN Data pointer */
} linflexd_lin_id_filter_struct;

/* structure definitions */
/* LINFLEXD parameter structure */
typedef struct {
    uint32_t baudRate;                              /*!< baudrate of LIN Hardware Interface to configure */
    linflexd_lin_node_enum ismaster;                /*!< Node function as Master or Slave */
    linflexd_lin_break_length_enum breakLength;     /*!< Break length, only for master mode */
    FlagStatus autobaudEnable;                      /*!< Enable Autobaud feature, only for slave mode */
    uint8_t responseTimeoutValue;                   /*!< Timeout value for response */
    uint8_t headerTimeoutValue;                     /*!< Timeout value for header */
    uint8_t filterCount;                            /*!< Actual filters used */
    linflexd_lin_id_filter_struct *slaveFilterCfgPtr; /*!< Slave filter configurations, only for slave mode */
    uint8_t *classicID;                             /*!< List of IDs use classic checksum */
    uint8_t numOfClassicID;                         /*!< Number of IDs use classic checksum */
    uint32_t linStatecaputure;                      /*!< LIN state capture disable or enable on bit error*/
    uint32_t checksumCalculaton;                    /*!< Checksum calculation disable or enable*/
    uint32_t checksumField;                         /*!< Checksum field disable or enable*/
    uint32_t automaticWakeUp;                       /*!< Automatic Wake-Up by software or hardware*/
    uint32_t bypassFilter;                          /*!< Bypass filter-controls the receive filter bypass function*/
    uint32_t slaveSyncLength;                       /*!< Slave mode sync break length-sets the number of bit times for break field detection*/
    uint32_t receiverBufferLock;                    /*!< Receiver buffer locked mode locked or not*/
} linflexd_lin_parameter_struct;

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check LINFLEXD_LIN peripherals */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) 
#define NOT_LINFLEXD_LIN_PERIPH(periph)     (((periph) != LINFLEXD_LIN0)  && ((periph) != LINFLEXD_LIN1)  && \
                                              ((periph) != LINFLEXD_LIN2)  && ((periph) != LINFLEXD_LIN3)  && \
                                              ((periph) != LINFLEXD_LIN4)  && ((periph) != LINFLEXD_LIN5)  && \
                                              ((periph) != LINFLEXD_LIN6)  && ((periph) != LINFLEXD_LIN7)  && \
                                              ((periph) != LINFLEXD_LIN8)  && ((periph) != LINFLEXD_LIN9)  && \
                                              ((periph) != LINFLEXD_LIN10) && ((periph) != LINFLEXD_LIN11))
#else
#define NOT_LINFLEXD_LIN_PERIPH(periph)     (((periph) != LINFLEXD_LIN0)  && ((periph) != LINFLEXD_LIN1)  && \
                                              ((periph) != LINFLEXD_LIN2)  && ((periph) != LINFLEXD_LIN3)  && \
                                              ((periph) != LINFLEXD_LIN4)  && ((periph) != LINFLEXD_LIN5))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* check if the baudrate is not a LINFlexD_UART baudrate */
#define NOT_LINFLEXD_LIN_BAUDRATE(baudval)                  ((baudval) == 0U)

/* check integer baud rate parameter */
#define NOT_LINFLEXD_LIN_IBR(ibr)                           ((ibr) > 0xFFFFFU)

/* check fractional baud rate parameter */
#define NOT_LINFLEXD_LIN_FBR(fbr)                           ((fbr) > 0xFU)

/* check LINFlexD_LIN transmit receive data length */
#define NOT_LINFLEXD_LIN_TR_DATALENGTH(size)                ((size) > 0xFU)

/* check LINFlexD_LIN SLEEP */
#define NOT_LINFLEXD_LIN_SLEEP_ENABLE(enable)               (((enable) != 0x0U) && ((enable) != 0x1U))

/* check LINFlexD_LIN BIDR ID*/
#define NOT_LINFLEXD_LIN_BIDR_ID(id)                        ((id) > 0x3FU)

/* check response timeout value parameter */
#define NOT_LINFLEXD_LIN_RESPONSE_TIMEOUT_VALUE(value)      ((value) > 0x0FU)

/* check header timeout value parameter */
#define NOT_LINFLEXD_LIN_HEADER_TIMEOUT_VALUE(value)        ((value) > 0x7FU)

/* check filter count parameter */
#define NOT_LINFLEXD_LIN_FILTER_COUNT(filtercount)          ((filtercount) > 0x0FU)

/* check stop bits parameter */
#define NOT_LINFLEXD_LIN_STOP_BIT(stopbits)                 (((stopbits) != 0x0U) && ((stopbits) != 0x1U))

/* check ips bus size parameter */
#define NOT_LINFLEXD_LIN_IPS_BUS_SIZE(size)                 ((size) > 0x3U)
/* check transmit data length parameter */
#define NOT_LINFLEXD_LIN_DATA_LENGTH_SIZE(size)             ((size) > 0x8U)
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* initialization functions */
/* reset LIN Peripheral */
ErrStatus linflexd_deinit(uint32_t linflexdx);
/* Initialize LIN peripheral parameter structure */
void linflexd_lin_struct_para_init(linflexd_lin_parameter_struct *initpara);
/* Initialize LIN peripheral */
ErrStatus linflexd_lin_init(uint32_t lin_periph, linflexd_lin_parameter_struct *initpara);

/* application function declarations */
/* Set the baud rate of the LIN module */
void linflexd_lin_baudrate_set(uint32_t lin_periph, uint32_t baudval);
/* set integer part of LIN baudrate register */
void linflexd_lin_set_integer_baudrate(uint32_t lin_periph, uint32_t ibr);
/* set fractional part of LIN baudrate register */
void linflexd_lin_set_fractional_baudrate(uint32_t lin_periph, uint8_t fbr);
/* LIN mode data transfer */
void linflexd_lin_data_transmit(uint32_t lin_periph, uint8_t *data, uint8_t size);
/* LIN mode data transfer */
void linflexd_lin_data_receive(uint32_t lin_periph, uint8_t *data, uint8_t size);
/* Get LIN checksum */
uint8_t linflexd_lin_get_checksum(uint32_t lin_periph);
/* LIN module enters initialization mode */
void linflexd_lin_enter_init_mode(uint32_t lin_periph);
/* LIN module enters normal operation mode */
void linflexd_lin_enter_normal_mode(uint32_t lin_periph);
/* Set LIN module to enter or exit sleep mode */
void linflexd_lin_set_sleep_mode(uint32_t lin_periph, uint8_t enable);
/* Get LIN module sleep mode */
FlagStatus linflexd_lin_get_sleep_mode(uint32_t lin_periph);
/* Enable LIN module auto synchronization */
void linflexd_lin_auto_sync_enable(uint32_t lin_periph);
/* Disable LIN module auto synchronization */
void linflexd_lin_auto_sync_disable(uint32_t lin_periph);
/* enable LIN module loopback mode */
void linflexd_lin_loopback_enable(uint32_t lin_periph);
/* disable LIN module loopback mode */
void linflexd_lin_loopback_disable(uint32_t lin_periph);
/* Configure LIN module transfer direction */
void linflexd_lin_set_direction(uint32_t lin_periph, linflexd_lin_direction_enum dir);
/* Configure LIN module transfer data length */
void linflexd_lin_set_data_length(uint32_t lin_periph, uint32_t size);
/* Configure LIN module identifier filter */
void linflexd_lin_set_bidr(uint32_t lin_periph, uint8_t id, uint32_t size, linflexd_lin_direction_enum dir, linflexd_lin_checksum_enum ccs);
/* Enable header transfer request */
void linflexd_lin_header_request_enable(uint32_t lin_periph);
/* Enable data transfer request */
void linflexd_lin_data_request_enable(uint32_t lin_periph);
/* Enable LIN module wakeup request */
void linflexd_lin_wakeup_request_enable(uint32_t lin_periph);
/* Config LINFlexD_LIN auto wakeup hardware to clear the SLEEP bit */
void linflexd_lin_autowake_hw_clear(uint32_t lin_periph);
/* Config LINFlexD_LIN auto wakeup software to clear the SLEEP bit */
void linflexd_lin_autowake_sw_clear(uint32_t lin_periph);
/* Enable LIN module data discard request */
void linflexd_lin_data_discard_enable(uint32_t lin_periph);
/* Enable idle on bit error for LIN module */
void linflexd_lin_idle_bit_error_enable(uint32_t lin_periph);
/* Disable idle on bit error for LIN module */
void linflexd_lin_idle_bit_error_disable(uint32_t lin_periph);
/* Enable idle on parity error for LIN module */
void linflexd_lin_idle_parity_error_enable(uint32_t lin_periph);
/* Disable idle on parity error for LIN module */
void linflexd_lin_idle_parity_error_disable(uint32_t lin_periph);
/* Enable LIN module transfer abort request */
void linflexd_lin_transfer_abort_enable(uint32_t lin_periph);
/* Get LIN transfer abort status */
uint8_t linflexd_lin_get_transfer_abort(uint32_t lin_periph);
/* Set ID in LIN BIDR register */
void linflexd_lin_set_bidr_id(uint32_t lin_periph, uint8_t id);
/* Get ID in LIN BIDR register */
uint8_t linflexd_lin_get_bidr_id(uint32_t lin_periph);
/* Enable LIN master mode */
void linflexd_lin_master_mode_enable(uint32_t lin_periph);
/* Disable LIN master mode */
void linflexd_lin_master_mode_disable(uint32_t lin_periph);
/* Get current working state of LIN */
linflexd_lin_hw_state_enum linflexd_lin_get_state(uint32_t lin_periph);

/* LIN timeout */
/* Enable timeout */
void linflexd_lin_timeout_enable(uint32_t lin_periph);
/* Disable timeout */
void linflexd_lin_timeout_disable(uint32_t lin_periph);
/* Set timeout value */
void linflexd_lin_set_timeout_value(uint32_t lin_periph, uint8_t responseTimeout, uint8_t headerTimeout);
/* Set oc value */
void linflexd_lin_set_oc_value(uint32_t lin_periph, uint8_t oc1, uint8_t oc2);

/* LIN identifier filter */
/* Configure LIN identifier filter */
void linflexd_lin_config_id_filter(uint32_t lin_periph, uint8_t filterCount, linflexd_lin_id_filter_struct *config);
/* Get identifier filter match index */
uint8_t linflexd_lin_get_filter_match_index(uint32_t lin_periph);

/* LIN transmit order */
/*  set byte order msb enable for LIN data transmission */
void linflexd_lin_tx_order_msb_enable(uint32_t lin_periph);
/*  set byte order msb disable for LIN data transmission */
void linflexd_lin_tx_order_msb_disable(uint32_t lin_periph);
/* set byte order msb enable for LIN data reception */
void linflexd_lin_rx_order_msb_enable(uint32_t lin_periph);
/* set byte order msb disable for LIN data reception */
void linflexd_lin_rx_order_msb_disable(uint32_t lin_periph);

/* LIN transmit stop and soft reset */
/* Configure number of stop bits for LIN */
void linflexd_lin_stop_bit_config(uint32_t lin_periph, uint8_t stopBits);
/* Perform software reset on LIN module enable */
void linflexd_lin_soft_reset_enable(uint32_t lin_periph);
/* Perform software reset on LIN module disable */
void linflexd_lin_soft_reset_disable(uint32_t lin_periph);
/* Enable LIN signal inversion function */
void linflexd_lin_inversion_enable(uint32_t lin_periph);
/* Disable LIN signal inversion function */
void linflexd_lin_inversion_disable(uint32_t lin_periph);
/* Two Bit delimiter enable for LIN module */
void linflexd_lin_two_bit_delimiter_enable(uint32_t lin_periph);
/* Two Bit delimiter disnable for LIN module */
void linflexd_lin_two_bit_delimiter_disable(uint32_t lin_periph);
/* Set LIN module to enter STOP request */
void linflexd_lin_stop_request_set(uint32_t lin_periph);
/* Get LIN module STOP request acknowledge status */
uint8_t linflexd_lin_stop_ack_get(uint32_t lin_periph);

/* LIN dma */
/* Enable DMA TX function for LIN */
void linflexd_lin_dma_tx_enable(uint32_t lin_periph,linflexd_dma_tx_channel_enum dma);
/* Disable DMA TX function for LIN */
void linflexd_lin_dma_tx_disable(uint32_t lin_periph,linflexd_dma_tx_channel_enum dma);
/* Enable DMA RX function for LIN */
void linflexd_lin_dma_rx_enable(uint32_t lin_periph,linflexd_dma_rx_channel_enum dma);
/* Disable DMA RX function for LIN */
void linflexd_lin_dma_rx_disable(uint32_t lin_periph,linflexd_dma_rx_channel_enum dma);

/* interrupt & flag functions */
/* Get LIN status flag */
FlagStatus linflexd_lin_flag_get(uint32_t lin_periph, linflexd_flag_enum flag);
/* Clear LIN status flag */
void linflexd_lin_flag_clear(uint32_t lin_periph, linflexd_flag_enum flag);
/* Enable interrupt */
void linflexd_lin_interrupt_enable(uint32_t lin_periph, linflexd_interrupt_enum interrupt);
/* Disable interrupt */
void linflexd_lin_interrupt_disable(uint32_t lin_periph, linflexd_interrupt_enum interrupt);
/* Get LIN interrupt flag status */
FlagStatus linflexd_lin_interrupt_flag_get(uint32_t lin_periph, linflexd_interrupt_flag_enum flag);
/* Clear LIN interrupt flag */
void linflexd_lin_interrupt_flag_clear(uint32_t lin_periph,linflexd_interrupt_flag_enum flag);

#endif /* GD32A7XX_LINFLEXD_LIN_H */
