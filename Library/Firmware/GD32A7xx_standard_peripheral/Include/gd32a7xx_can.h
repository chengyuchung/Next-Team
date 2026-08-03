/*!
    \file    gd32a7xx_can.h
    \brief   definitions for the CAN

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

#ifndef GD32A7XX_CAN_H
#define GD32A7XX_CAN_H

#include "gd32a7xx.h"
#include "stdlib.h"

/* CAN definitions */
/* CAN base addresses */
#define CAN0                          CAN_BASE                                            /*!< CAN0 base address */
#define CAN1                          (CAN_BASE + 0x00004000U)                            /*!< CAN1 base address */
#define CAN2                          (CAN_BASE + 0x00010000U)                            /*!< CAN2 base address */
/* CAN system registers offset address from base address */
#define CAN_SYSREG_OFFSET             (0x00001800U)                                       /*!< CAN system registers offset */

/* registers definitions */
/* SYSREG registers definitions */
#define CAN_MRAM(canx)                REG32((canx) + CAN_SYSREG_OFFSET + 0x00000000U)     /*!< CAN MRAM initialization register */
#define CAN_DMR(canx)                 REG32((canx) + CAN_SYSREG_OFFSET + 0x00000020U)     /*!< CAN disable modification on read register */
#define CAN_CSR(canx)                 REG32((canx) + CAN_SYSREG_OFFSET + 0x00000024U)     /*!< CAN clock stop request register */
#define CAN_CSA(canx)                 REG32((canx) + CAN_SYSREG_OFFSET + 0x00000028U)     /*!< CAN clock stop acknowledge register */
#define CAN_CTL(canx)                 REG32((canx) + CAN_SYSREG_OFFSET + 0x00000070U)     /*!< CAN control register */
#define CAN_MERRCTL(canx)             REG32((canx) + CAN_SYSREG_OFFSET + 0x00000080U)     /*!< CAN memory error control register */
#define CAN_CERRR0(canx)              REG32((canx) + CAN_SYSREG_OFFSET + 0x00000084U)     /*!< CAN correctable error record register 0 */
#define CAN_CERRR1(canx)              REG32((canx) + CAN_SYSREG_OFFSET + 0x00000088U)     /*!< CAN correctable error record register 1 */
#define CAN_CERRR2(canx)              REG32((canx) + CAN_SYSREG_OFFSET + 0x0000008CU)     /*!< CAN correctable error record register 2 */
#define CAN_CERRR3(canx)              REG32((canx) + CAN_SYSREG_OFFSET + 0x00000090U)     /*!< CAN correctable error record register 3 */
#define CAN_NCERRR(canx)              REG32((canx) + CAN_SYSREG_OFFSET + 0x00000094U)     /*!< CAN noncorrectable error record register */
#define CAN_MERRSTAT(canx)            REG32((canx) + CAN_SYSREG_OFFSET + 0x0000009CU)     /*!< CAN memory error status register */
/* M_CAN registers definitions */
#define CAN_M_CAN_CREL(dtm_canx)      REG32((dtm_canx) + 0x00U)                           /*!< M_CAN core release register */
#define CAN_M_CAN_ENDN(dtm_canx)      REG32((dtm_canx) + 0x04U)                           /*!< M_CAN endian register */
#define CAN_M_CAN_DBTP(dtm_canx)      REG32((dtm_canx) + 0x0CU)                           /*!< M_CAN data bit timing and prescaler register */
#define CAN_M_CAN_TEST(dtm_canx)      REG32((dtm_canx) + 0x10U)                           /*!< M_CAN test register */
#define CAN_M_CAN_RWD(dtm_canx)       REG32((dtm_canx) + 0x14U)                           /*!< M_CAN RAM watchdog register */
#define CAN_M_CAN_CCCR(dtm_canx)      REG32((dtm_canx) + 0x18U)                           /*!< M_CAN CC control register */
#define CAN_M_CAN_NBTP(dtm_canx)      REG32((dtm_canx) + 0x1CU)                           /*!< M_CAN nominal bit timing and prescaler register */
#define CAN_M_CAN_TSCC(dtm_canx)      REG32((dtm_canx) + 0x20U)                           /*!< M_CAN timestamp counter configuration register */
#define CAN_M_CAN_TSCV(dtm_canx)      REG32((dtm_canx) + 0x24U)                           /*!< M_CAN timestamp counter value register */
#define CAN_M_CAN_TOCC(dtm_canx)      REG32((dtm_canx) + 0x28U)                           /*!< M_CAN timeout counter configuration register */
#define CAN_M_CAN_TOCV(dtm_canx)      REG32((dtm_canx) + 0x2CU)                           /*!< M_CAN timeout counter value register */
#define CAN_M_CAN_ECR(dtm_canx)       REG32((dtm_canx) + 0x40U)                           /*!< M_CAN error counter register */
#define CAN_M_CAN_PSR(dtm_canx)       REG32((dtm_canx) + 0x44U)                           /*!< M_CAN protocol status register */
#define CAN_M_CAN_TDCR(dtm_canx)      REG32((dtm_canx) + 0x48U)                           /*!< M_CAN transmitter delay compensation register */
#define CAN_M_CAN_IR(dtm_canx)        REG32((dtm_canx) + 0x50U)                           /*!< M_CAN interrupt register */
#define CAN_M_CAN_IE(dtm_canx)        REG32((dtm_canx) + 0x54U)                           /*!< M_CAN interrupt enable register */
#define CAN_M_CAN_ILS(dtm_canx)       REG32((dtm_canx) + 0x58U)                           /*!< M_CAN interrupt line select register */
#define CAN_M_CAN_ILE(dtm_canx)       REG32((dtm_canx) + 0x5CU)                           /*!< M_CAN interrupt line enable register */
#define CAN_M_CAN_GFC(dtm_canx)       REG32((dtm_canx) + 0x80U)                           /*!< M_CAN global filter configuration register */
#define CAN_M_CAN_SIDFC(dtm_canx)     REG32((dtm_canx) + 0x84U)                           /*!< M_CAN standard ID filter configuration register */
#define CAN_M_CAN_XIDFC(dtm_canx)     REG32((dtm_canx) + 0x88U)                           /*!< M_CAN extended ID filter configuration register */
#define CAN_M_CAN_XIDAM(dtm_canx)     REG32((dtm_canx) + 0x90U)                           /*!< M_CAN extended ID AND mask register */
#define CAN_M_CAN_HPMS(dtm_canx)      REG32((dtm_canx) + 0x94U)                           /*!< M_CAN high priority message status register */
#define CAN_M_CAN_NDAT1(dtm_canx)     REG32((dtm_canx) + 0x98U)                           /*!< M_CAN new data 1 register */
#define CAN_M_CAN_NDAT2(dtm_canx)     REG32((dtm_canx) + 0x9CU)                           /*!< M_CAN new data 2 register */
#define CAN_M_CAN_RXF0C(dtm_canx)     REG32((dtm_canx) + 0xA0U)                           /*!< M_CAN Rx FIFO 0 configuration register */
#define CAN_M_CAN_RXF0S(dtm_canx)     REG32((dtm_canx) + 0xA4U)                           /*!< M_CAN Rx FIFO 0 status register */
#define CAN_M_CAN_RXF0A(dtm_canx)     REG32((dtm_canx) + 0xA8U)                           /*!< M_CAN Rx FIFO 0 acknowledge register */
#define CAN_M_CAN_RXBC(dtm_canx)      REG32((dtm_canx) + 0xACU)                           /*!< M_CAN Rx buffer configuration register */
#define CAN_M_CAN_RXF1C(dtm_canx)     REG32((dtm_canx) + 0xB0U)                           /*!< M_CAN Rx FIFO 1 configuration register */
#define CAN_M_CAN_RXF1S(dtm_canx)     REG32((dtm_canx) + 0xB4U)                           /*!< M_CAN Rx FIFO 1 status register */
#define CAN_M_CAN_RXF1A(dtm_canx)     REG32((dtm_canx) + 0xB8U)                           /*!< M_CAN Rx FIFO 1 acknowledge register */
#define CAN_M_CAN_RXESC(dtm_canx)     REG32((dtm_canx) + 0xBCU)                           /*!< M_CAN Rx buffer/FIFO element size configuration register */
#define CAN_M_CAN_TXBC(dtm_canx)      REG32((dtm_canx) + 0xC0U)                           /*!< M_CAN Tx buffer configuration register */
#define CAN_M_CAN_TXFQS(dtm_canx)     REG32((dtm_canx) + 0xC4U)                           /*!< M_CAN Tx FIFO/queue status register */
#define CAN_M_CAN_TXESC(dtm_canx)     REG32((dtm_canx) + 0xC8U)                           /*!< M_CAN Tx buffer element size configuration register */
#define CAN_M_CAN_TXBRP(dtm_canx)     REG32((dtm_canx) + 0xCCU)                           /*!< M_CAN Tx buffer request pending register */
#define CAN_M_CAN_TXBAR(dtm_canx)     REG32((dtm_canx) + 0xD0U)                           /*!< M_CAN Tx buffer add request register */
#define CAN_M_CAN_TXBCR(dtm_canx)     REG32((dtm_canx) + 0xD4U)                           /*!< M_CAN Tx buffer cancellation request register */
#define CAN_M_CAN_TXBTO(dtm_canx)     REG32((dtm_canx) + 0xD8U)                           /*!< M_CAN Tx buffer transmission occurred register */
#define CAN_M_CAN_TXBCF(dtm_canx)     REG32((dtm_canx) + 0xDCU)                           /*!< M_CAN Tx buffer cancellation finished register */
#define CAN_M_CAN_TXBTIE(dtm_canx)    REG32((dtm_canx) + 0xE0U)                           /*!< M_CAN Tx buffer transmission interrupt enable register */
#define CAN_M_CAN_TXBCIE(dtm_canx)    REG32((dtm_canx) + 0xE4U)                           /*!< M_CAN Tx buffer cancellation finished interrupt enable register */
#define CAN_M_CAN_TXEFC(dtm_canx)     REG32((dtm_canx) + 0xF0U)                           /*!< M_CAN Tx event FIFO configuration register */
#define CAN_M_CAN_TXEFS(dtm_canx)     REG32((dtm_canx) + 0xF4U)                           /*!< M_CAN Tx event FIFO status register */
#define CAN_M_CAN_TXEFA(dtm_canx)     REG32((dtm_canx) + 0xF8U)                           /*!< M_CAN Tx event FIFO acknowledge register */
/* DMU registers definitions */
#define CAN_DMU_DMUCR(dtm_canx)       REG32((dtm_canx) + 0x000003C0U)                     /*!< DMU control register */
#define CAN_DMU_DMUI(dtm_canx)        REG32((dtm_canx) + 0x000003C4U)                     /*!< DMU interface register */
#define CAN_DMU_DMUQC(dtm_canx)       REG32((dtm_canx) + 0x000003C8U)                     /*!< DMU queue control register */
#define CAN_DMU_DMUIR(dtm_canx)       REG32((dtm_canx) + 0x000003CCU)                     /*!< DMU interrupt register */
#define CAN_DMU_DMUIE(dtm_canx)       REG32((dtm_canx) + 0x000003D0U)                     /*!< DMU interrupt enable register */
#define CAN_DMU_DMUC(dtm_canx)        REG32((dtm_canx) + 0x000003D4U)                     /*!< DMU configuration register */

/* bits definitions */
/* CAN_MRAM */
#define CAN_MRAM_IRF                  BIT(0)                                              /*!< CAN share message SRAM initialization finish */

/* CAN_DMR */
#define CAN_DMR_DMORD0                BIT(0)                                              /*!< "disable modification on read" function enable for M_CAN of the first DTM_CAN in a CAN cluster */
#define CAN_DMR_DMORD1                BIT(1)                                              /*!< "disable modification on read" function enable for M_CAN of the second DTM_CAN in a CAN cluster */
#define CAN_DMR_DMORD2                BIT(2)                                              /*!< "disable modification on read" function enable for M_CAN of the third DTM_CAN in a CAN cluster */

/* CAN_CSR */
#define CAN_CSR_CSR0                  BIT(0)                                              /*!< clock stop request signal for M_CAN of the first DTM_CAN in a CAN cluster */
#define CAN_CSR_CSR1                  BIT(1)                                              /*!< clock stop request signal for M_CAN of the second DTM_CAN in a CAN cluster */
#define CAN_CSR_CSR2                  BIT(2)                                              /*!< clock stop request signal for M_CAN of the third DTM_CAN in a CAN cluster */

/* CAN_CSA */
#define CAN_CSA_CSA0                  BIT(0)                                              /*!< clock stop acknowledge for M_CAN of the first DTM_CAN in a CAN cluster */
#define CAN_CSA_CSA1                  BIT(1)                                              /*!< clock stop acknowledge for M_CAN of the second DTM_CAN in a CAN cluster */
#define CAN_CSA_CSA2                  BIT(2)                                              /*!< clock stop acknowledge for M_CAN of the third DTM_CAN in a CAN cluster */

/* CAN_CTL */
#define CAN_CTL_DMAEN0                BIT(12)                                             /*!< DMA request enable for M_CAN of the first DTM_CAN in a CAN cluster */
#define CAN_CTL_DMAEN1                BIT(13)                                             /*!< DMA request enable for M_CAN of the second DTM_CAN in a CAN cluster */
#define CAN_CTL_DMAEN2                BIT(14)                                             /*!< DMA request enable for M_CAN of the third DTM_CAN in a CAN cluster */
#define CAN_CTL_ECRWEN                BIT(29)                                             /*!< CAN_MERRCTL register write access enable */

/* CAN_MERRCTL */
#define CAN_MERRCTL_ECCEN             BIT(8)                                              /*!< enable ECC */
#define CAN_MERRCTL_CEIE              BIT(16)                                             /*!< correctable error interrupt enable */
#define CAN_MERRCTL_NCEIE             BIT(17)                                             /*!< noncorrectable error interrupt enable */
#define CAN_MERRCTL_RWDIS             BIT(31)                                             /*!< CAN_MERRCTL register write access disable */

/* CAN_CERRRx(x=0..3) */
#define CAN_CERRR_CERA                BITS(0,10)                                          /*!< correctable error record address */
#define CAN_CERRR_CERS                BIT(24)                                             /*!< correctable error record status */

/* CAN_NCERRR */
#define CAN_NCERRR_NCERA              BITS(0,10)                                          /*!< noncorrectable error record address */
#define CAN_NCERRR_NCERS              BIT(24)                                             /*!< noncorrectable error record status */

/* CAN_MERRSTAT */
#define CAN_MERRSTAT_NCE_EAEF         BIT(24)                                             /*!< noncorrectable EDC after ECC error flag */
#define CAN_MERRSTAT_NCE_AEDCF        BIT(25)                                             /*!< noncorrectable address EDC error flag */
#define CAN_MERRSTAT_NCDEF            BIT(26)                                             /*!< noncorrectable double bit error flag */
#define CAN_MERRSTAT_BUFOVF           BIT(27)                                             /*!< correctable error record buffer overflow flag */
#define CAN_MERRSTAT_CEOVF            BIT(28)                                             /*!< correctable error overflow flag */
#define CAN_MERRSTAT_NCEOVF           BIT(29)                                             /*!< noncorrectable error overflow flag */
#define CAN_MERRSTAT_CEF              BIT(30)                                             /*!< correctable error flag */

/* CAN_M_CAN_CREL */
#define CAN_M_CAN_CREL_DAY            BITS(0,7)                                           /*!< timestamp day */
#define CAN_M_CAN_CREL_MON            BITS(8,15)                                          /*!< timestamp month */
#define CAN_M_CAN_CREL_YEAR           BITS(16,19)                                         /*!< timestamp year */
#define CAN_M_CAN_CREL_SUBSTEP        BITS(20,23)                                         /*!< sub-step of Core Release */
#define CAN_M_CAN_CREL_STEP           BITS(24,27)                                         /*!< step of Core Release */
#define CAN_M_CAN_CREL_REL            BITS(28,31)                                         /*!< core release */

/* CAN_M_CAN_ENDN */
#define CAN_M_CAN_ENDN_ETV            BITS(0,31)                                          /*!< endianness test value */

/* CAN_M_CAN_DBTP */
#define CAN_M_CAN_DBTP_DSJW           BITS(0,3)                                           /*!< data resynchronization jump width */
#define CAN_M_CAN_DBTP_DTSEG2         BITS(4,7)                                           /*!< data time segment 2 */
#define CAN_M_CAN_DBTP_DTSEG1         BITS(8,12)                                          /*!< data time segment 1 */
#define CAN_M_CAN_DBTP_DBRP           BITS(16,20)                                         /*!< data bit rate prescaler */
#define CAN_M_CAN_DBTP_TDC            BIT(23)                                             /*!< transmitter delay compensation */

/* CAN_M_CAN_TEST */
#define CAN_M_CAN_TEST_LBCK           BIT(4)                                              /*!< loop back mode */
#define CAN_M_CAN_TEST_TX             BITS(5,6)                                           /*!< control of TX pin */
#define CAN_M_CAN_TEST_RX             BIT(7)                                              /*!< receive pin */
#define CAN_M_CAN_TEST_TXBNP          BITS(8,12)                                          /*!< Tx buffer number prepared */
#define CAN_M_CAN_TEST_PVAL           BIT(13)                                             /*!< prepared valid */
#define CAN_M_CAN_TEST_TXBNS          BITS(16,20)                                         /*!< Tx buffer number started */
#define CAN_M_CAN_TEST_SVAL           BIT(21)                                             /*!< started valid */

/* CAN_M_CAN_RWD */
#define CAN_M_CAN_RWD_WDC             BITS(0,7)                                           /*!< watchdog configuration */
#define CAN_M_CAN_RWD_WDV             BITS(8,15)                                          /*!< watchdog value */

/* CAN_M_CAN_CCCR */
#define CAN_M_CAN_CCCR_INIT           BIT(0)                                              /*!< initialization */
#define CAN_M_CAN_CCCR_CCE            BIT(1)                                              /*!< configuration change enable */
#define CAN_M_CAN_CCCR_ASM            BIT(2)                                              /*!< restricted operation mode */
#define CAN_M_CAN_CCCR_CSA            BIT(3)                                              /*!< clock stop acknowledge */
#define CAN_M_CAN_CCCR_CSR            BIT(4)                                              /*!< clock stop request */
#define CAN_M_CAN_CCCR_MON            BIT(5)                                              /*!< bus monitoring mode */
#define CAN_M_CAN_CCCR_DAR            BIT(6)                                              /*!< disable automatic retransmission */
#define CAN_M_CAN_CCCR_TEST           BIT(7)                                              /*!< test mode enable */
#define CAN_M_CAN_CCCR_FDOE           BIT(8)                                              /*!< FD operation enable */
#define CAN_M_CAN_CCCR_BRSE           BIT(9)                                              /*!< bit rate switch enable */
#define CAN_M_CAN_CCCR_WMM            BIT(11)                                             /*!< wide message marker */
#define CAN_M_CAN_CCCR_PXHD           BIT(12)                                             /*!< protocol exception handling disable */
#define CAN_M_CAN_CCCR_EFBI           BIT(13)                                             /*!< edge filtering during bus integration */
#define CAN_M_CAN_CCCR_TXP            BIT(14)                                             /*!< transmit pause */
#define CAN_M_CAN_CCCR_NISO           BIT(15)                                             /*!< non ISO operation */

/* CAN_M_CAN_NBTP */
#define CAN_M_CAN_NBTP_NTSEG2         BITS(0,6)                                           /*!< nominal time segment 2 */
#define CAN_M_CAN_NBTP_NTSEG1         BITS(8,15)                                          /*!< nominal time segment 1 */
#define CAN_M_CAN_NBTP_NBRP           BITS(16,24)                                         /*!< nominal bit rate prescaler */
#define CAN_M_CAN_NBTP_NSJW           BITS(25,31)                                         /*!< nominal (re)synchronization jump width */

/* CAN_M_CAN_TSCC */
#define CAN_M_CAN_TSCC_TSS            BITS(0,1)                                           /*!< timestamp select */
#define CAN_M_CAN_TSCC_TCP            BITS(16,19)                                         /*!< timestamp counter prescaler */

/* CAN_M_CAN_TSCV */
#define CAN_M_CAN_TSCV_TSC            BITS(0,15)                                          /*!< timestamp counter */

/* CAN_M_CAN_TOCC */
#define CAN_M_CAN_TOCC_ETOC           BIT(0)                                              /*!< enable timeout counter */
#define CAN_M_CAN_TOCC_TOS            BITS(1,2)                                           /*!< timeout select */
#define CAN_M_CAN_TOCC_TOP            BITS(16,31)                                         /*!< timeout period */

/* CAN_M_CAN_TOCV */
#define CAN_M_CAN_TOCV_TOC            BITS(0,15)                                          /*!< timeout counter */

/* CAN_M_CAN_ECR */
#define CAN_M_CAN_ECR_TEC             BITS(0,7)                                           /*!< transmit error counter */
#define CAN_M_CAN_ECR_REC             BITS(8,14)                                          /*!< receive error counter */
#define CAN_M_CAN_ECR_RP              BIT(15)                                             /*!< receive error passive */
#define CAN_M_CAN_ECR_CEL             BITS(16,23)                                         /*!< CAN error logging */

/* CAN_M_CAN_PSR */
#define CAN_M_CAN_PSR_LEC             BITS(0,2)                                           /*!< last error code */
#define CAN_M_CAN_PSR_ACT             BITS(3,4)                                           /*!< activity */
#define CAN_M_CAN_PSR_EP              BIT(5)                                              /*!< error passive */
#define CAN_M_CAN_PSR_EW              BIT(6)                                              /*!< warning status */
#define CAN_M_CAN_PSR_BO              BIT(7)                                              /*!< bus_off status */
#define CAN_M_CAN_PSR_DLEC            BITS(8,10)                                          /*!< data last error code */
#define CAN_M_CAN_PSR_RESI            BIT(11)                                             /*!< ESI flag of received CAN FD message */
#define CAN_M_CAN_PSR_RBRS            BIT(12)                                             /*!< BRS flag of received CAN FD message */
#define CAN_M_CAN_PSR_RFDF            BIT(13)                                             /*!< receive an FD message */
#define CAN_M_CAN_PSR_PXE             BIT(14)                                             /*!< protocol exception event */
#define CAN_M_CAN_PSR_TDCV            BITS(16,22)                                         /*!< transmitter delay compensation value */

/* CAN_M_CAN_TDCR */
#define CAN_M_CAN_TDCR_TDCF           BITS(0,6)                                           /*!< transmitter delay compensation filter window length */
#define CAN_M_CAN_TDCR_TDCO           BITS(8,14)                                          /*!< transmitter delay compensation offset */

/* CAN_M_CAN_IR */
#define CAN_M_CAN_IR_RF0N             BIT(0)                                              /*!< Rx FIFO 0 new message */
#define CAN_M_CAN_IR_RF0W             BIT(1)                                              /*!< Rx FIFO 0 watermark reached */
#define CAN_M_CAN_IR_RF0F             BIT(2)                                              /*!< Rx FIFO 0 full */
#define CAN_M_CAN_IR_RF0L             BIT(3)                                              /*!< Rx FIFO 0 message lost */
#define CAN_M_CAN_IR_RF1N             BIT(4)                                              /*!< Rx FIFO 1 new message */
#define CAN_M_CAN_IR_RF1W             BIT(5)                                              /*!< Rx FIFO 1 watermark reached */
#define CAN_M_CAN_IR_RF1F             BIT(6)                                              /*!< Rx FIFO 1 full */
#define CAN_M_CAN_IR_RF1L             BIT(7)                                              /*!< Rx FIFO 1 message lost */
#define CAN_M_CAN_IR_HPM              BIT(8)                                              /*!< high priority message */
#define CAN_M_CAN_IR_TC               BIT(9)                                              /*!< transmission completed */
#define CAN_M_CAN_IR_TCF              BIT(10)                                             /*!< transmission cancellation finished */
#define CAN_M_CAN_IR_TFE              BIT(11)                                             /*!< Tx FIFO empty */
#define CAN_M_CAN_IR_TEFN             BIT(12)                                             /*!< Tx event FIFO new entry */
#define CAN_M_CAN_IR_TEFW             BIT(13)                                             /*!< Tx event FIFO watermark reached */
#define CAN_M_CAN_IR_TEFF             BIT(14)                                             /*!< Tx event FIFO full */
#define CAN_M_CAN_IR_TEFL             BIT(15)                                             /*!< Tx event FIFO element lost */
#define CAN_M_CAN_IR_TSW              BIT(16)                                             /*!< timestamp wrapped around */
#define CAN_M_CAN_IR_MRAF             BIT(17)                                             /*!< message RAM access failure */
#define CAN_M_CAN_IR_TOO              BIT(18)                                             /*!< timeout occurred */
#define CAN_M_CAN_IR_DRX              BIT(19)                                             /*!< message stored to dedicated Rx buffer */
#define CAN_M_CAN_IR_ELO              BIT(22)                                             /*!< error logging overflow */
#define CAN_M_CAN_IR_EP               BIT(23)                                             /*!< error passive */
#define CAN_M_CAN_IR_EW               BIT(24)                                             /*!< warning status */
#define CAN_M_CAN_IR_BO               BIT(25)                                             /*!< bus_off status */
#define CAN_M_CAN_IR_WDI              BIT(26)                                             /*!< watchdog interrupt */
#define CAN_M_CAN_IR_PEA              BIT(27)                                             /*!< protocol error in arbitration phase */
#define CAN_M_CAN_IR_PED              BIT(28)                                             /*!< protocol error in data phase */

/* CAN_M_CAN_IE */
#define CAN_M_CAN_IE_RF0NE            BIT(0)                                              /*!< Rx FIFO 0 new message interrupt enable */
#define CAN_M_CAN_IE_RF0WE            BIT(1)                                              /*!< Rx FIFO 0 watermark reached interrupt enable */
#define CAN_M_CAN_IE_RF0FE            BIT(2)                                              /*!< Rx FIFO 0 full interrupt enable */
#define CAN_M_CAN_IE_RF0LE            BIT(3)                                              /*!< Rx FIFO 0 message lost interrupt enable */
#define CAN_M_CAN_IE_RF1NE            BIT(4)                                              /*!< Rx FIFO 1 new message interrupt enable */
#define CAN_M_CAN_IE_RF1WE            BIT(5)                                              /*!< Rx FIFO 1 watermark reached interrupt enable */
#define CAN_M_CAN_IE_RF1FE            BIT(6)                                              /*!< Rx FIFO 1 full interrupt enable */
#define CAN_M_CAN_IE_RF1LE            BIT(7)                                              /*!< Rx FIFO 1 message lost interrupt enable */
#define CAN_M_CAN_IE_HPME             BIT(8)                                              /*!< high priority message interrupt enable */
#define CAN_M_CAN_IE_TCE              BIT(9)                                              /*!< transmission completed interrupt enable */
#define CAN_M_CAN_IE_TCFE             BIT(10)                                             /*!< transmission cancellation finished interrupt enable */
#define CAN_M_CAN_IE_TFEE             BIT(11)                                             /*!< Tx FIFO empty interrupt enable */
#define CAN_M_CAN_IE_TEFNE            BIT(12)                                             /*!< Tx event FIFO new entry interrupt enable */
#define CAN_M_CAN_IE_TEFWE            BIT(13)                                             /*!< Tx event FIFO watermark reached interrupt enable */
#define CAN_M_CAN_IE_TEFFE            BIT(14)                                             /*!< Tx event FIFO full interrupt enable */
#define CAN_M_CAN_IE_TEFLE            BIT(15)                                             /*!< Tx event FIFO element lost interrupt enable */
#define CAN_M_CAN_IE_TSWE             BIT(16)                                             /*!< timestamp wrapped around interrupt enable */
#define CAN_M_CAN_IE_MRAFE            BIT(17)                                             /*!< message RAM access failure interrupt enable */
#define CAN_M_CAN_IE_TOOE             BIT(18)                                             /*!< timeout occurred interrupt enable */
#define CAN_M_CAN_IE_DRXE             BIT(19)                                             /*!< message stored to dedicated Rx buffer interrupt enable */
#define CAN_M_CAN_IE_ELOE             BIT(22)                                             /*!< error logging overflow interrupt enable */
#define CAN_M_CAN_IE_EPE              BIT(23)                                             /*!< error passive interrupt enable */
#define CAN_M_CAN_IE_EWE              BIT(24)                                             /*!< warning status interrupt enable */
#define CAN_M_CAN_IE_BOE              BIT(25)                                             /*!< bus_off status interrupt enable */
#define CAN_M_CAN_IE_WDIE             BIT(26)                                             /*!< watchdog interrupt enable */
#define CAN_M_CAN_IE_PEAE             BIT(27)                                             /*!< protocol error in arbitration phase interrupt enable */
#define CAN_M_CAN_IE_PEDE             BIT(28)                                             /*!< protocol error in data phase interrupt enable */

/* CAN_M_CAN_ILS */
#define CAN_M_CAN_ILS_RF0NL           BIT(0)                                              /*!< Rx FIFO 0 new message interrupt line */
#define CAN_M_CAN_ILS_RF0WL           BIT(1)                                              /*!< Rx FIFO 0 watermark reached interrupt line */
#define CAN_M_CAN_ILS_RF0FL           BIT(2)                                              /*!< Rx FIFO 0 full interrupt line */
#define CAN_M_CAN_ILS_RF0LL           BIT(3)                                              /*!< Rx FIFO 0 message lost interrupt line */
#define CAN_M_CAN_ILS_RF1NL           BIT(4)                                              /*!< Rx FIFO 1 new message interrupt line */
#define CAN_M_CAN_ILS_RF1WL           BIT(5)                                              /*!< Rx FIFO 1 watermark reached interrupt line */
#define CAN_M_CAN_ILS_RF1FL           BIT(6)                                              /*!< Rx FIFO 1 full interrupt line */
#define CAN_M_CAN_ILS_RF1LL           BIT(7)                                              /*!< Rx FIFO 1 message lost interrupt line */
#define CAN_M_CAN_ILS_HPML            BIT(8)                                              /*!< high priority message interrupt line */
#define CAN_M_CAN_ILS_TCL             BIT(9)                                              /*!< transmission completed interrupt line */
#define CAN_M_CAN_ILS_TCFL            BIT(10)                                             /*!< transmission cancellation finished interrupt line */
#define CAN_M_CAN_ILS_TFEL            BIT(11)                                             /*!< Tx FIFO empty interrupt line */
#define CAN_M_CAN_ILS_TEFNL           BIT(12)                                             /*!< Tx event FIFO new entry interrupt line */
#define CAN_M_CAN_ILS_TEFWL           BIT(13)                                             /*!< Tx event FIFO watermark reached interrupt line */
#define CAN_M_CAN_ILS_TEFFL           BIT(14)                                             /*!< Tx event FIFO full interrupt line */
#define CAN_M_CAN_ILS_TEFLL           BIT(15)                                             /*!< Tx event FIFO element lost interrupt line */
#define CAN_M_CAN_ILS_TSWL            BIT(16)                                             /*!< timestamp wrapped around interrupt line */
#define CAN_M_CAN_ILS_MRAFL           BIT(17)                                             /*!< message RAM access failure interrupt line */
#define CAN_M_CAN_ILS_TOOL            BIT(18)                                             /*!< timeout occurred interrupt line */
#define CAN_M_CAN_ILS_DRXL            BIT(19)                                             /*!< message stored to dedicated Rx buffer interrupt line */
#define CAN_M_CAN_ILS_ELOL            BIT(22)                                             /*!< error logging overflow interrupt line */
#define CAN_M_CAN_ILS_EPL             BIT(23)                                             /*!< error passive interrupt line */
#define CAN_M_CAN_ILS_EWL             BIT(24)                                             /*!< warning status interrupt line */
#define CAN_M_CAN_ILS_BOL             BIT(25)                                             /*!< bus_off status interrupt line */
#define CAN_M_CAN_ILS_WDIL            BIT(26)                                             /*!< watchdog interrupt line */
#define CAN_M_CAN_ILS_PEAL            BIT(27)                                             /*!< protocol error in arbitration phase interrupt line */
#define CAN_M_CAN_ILS_PEDL            BIT(28)                                             /*!< protocol error in data phase interrupt line */

/* CAN_M_CAN_ILE */
#define CAN_M_CAN_ILE_EINT0           BIT(0)                                              /*!< enable interrupt line 0 */
#define CAN_M_CAN_ILE_EINT1           BIT(1)                                              /*!< enable interrupt line 1 */

/* CAN_M_CAN_GFC */
#define CAN_M_CAN_GFC_RRFE            BIT(0)                                              /*!< reject remote frames extended */
#define CAN_M_CAN_GFC_RRFS            BIT(1)                                              /*!< reject remote frames standard */
#define CAN_M_CAN_GFC_ANFE            BITS(2,3)                                           /*!< accept non-matching frames extended */
#define CAN_M_CAN_GFC_ANFS            BITS(4,5)                                           /*!< accept non-matching frames standard */

/* CAN_M_CAN_SIDFC */
#define CAN_M_CAN_SIDFC_FLSSA         BITS(2,15)                                          /*!< filter list standard start address */
#define CAN_M_CAN_SIDFC_LSS           BITS(16,23)                                         /*!< list size standard */

/* CAN_M_CAN_XIDFC */
#define CAN_M_CAN_XIDFC_FLESA         BITS(2,15)                                          /*!< filter list extended start address */
#define CAN_M_CAN_XIDFC_LSE           BITS(16,22)                                         /*!< list size extended */

/* CAN_M_CAN_XIDAM */
#define CAN_M_CAN_XIDAM_EIDM          BITS(0,28)                                          /*!< extended ID mask */

/* CAN_M_CAN_HPMS */
#define CAN_M_CAN_HPMS_BIDX           BITS(0,5)                                           /*!< buffer index */
#define CAN_M_CAN_HPMS_MSI            BITS(6,7)                                           /*!< message storage indicator */
#define CAN_M_CAN_HPMS_FIDX           BITS(8,14)                                          /*!< filter index */
#define CAN_M_CAN_HPMS_FLST           BIT(15)                                             /*!< filter list */

/* CAN_M_CAN_NDAT1 */
#define CAN_M_CAN_NDAT1_ND(x)         BIT(x)                                              /*!< new data flag Rx buffer 0~31 */

/* CAN_M_CAN_NDAT2 */
#define CAN_M_CAN_NDAT2_ND(x)         BIT(x)                                              /*!< new data flag Rx buffer 32~63 */

/* CAN_M_CAN_RXF0C / CAN_M_CAN_RXF1C */
#define CAN_M_CAN_RXFXC_FSA           BITS(2,15)                                          /*!< Rx FIFO start address */
#define CAN_M_CAN_RXFXC_FS            BITS(16,22)                                         /*!< Rx FIFO size */
#define CAN_M_CAN_RXFXC_FWM           BITS(24,30)                                         /*!< Rx FIFO watermark */
#define CAN_M_CAN_RXFXC_FOM           BIT(31)                                             /*!< FIFO operation mode */

/* CAN_M_CAN_RXF0S / CAN_M_CAN_RXF1S */
#define CAN_M_CAN_RXFXS_FFL           BITS(0,6)                                           /*!< Rx FIFO fill level */
#define CAN_M_CAN_RXFXS_FGI           BITS(8,13)                                          /*!< Rx FIFO get index */
#define CAN_M_CAN_RXFXS_FPI           BITS(16,21)                                         /*!< Rx FIFO put index */
#define CAN_M_CAN_RXFXS_FF            BIT(24)                                             /*!< Rx FIFO full */
#define CAN_M_CAN_RXFXS_RFL           BIT(25)                                             /*!< Rx FIFO message lost */

/* CAN_M_CAN_RXF0A / CAN_M_CAN_RXF1A */
#define CAN_M_CAN_RXFXA_FAI           BITS(0,5)                                           /*!< Rx FIFO acknowledge index */

/* CAN_M_CAN_RXBC */
#define CAN_M_CAN_RXBC_RBSA           BITS(2,15)                                          /*!< Rx buffer start address */

/* CAN_M_CAN_RXESC */
#define CAN_M_CAN_RXESC_F0DS          BITS(0,2)                                           /*!< Rx FIFO 0 data field size */
#define CAN_M_CAN_RXESC_F1DS          BITS(4,6)                                           /*!< Rx FIFO 1 data field size */
#define CAN_M_CAN_RXESC_RBDS          BITS(8,10)                                          /*!< Rx buffer data field size */

/* CAN_M_CAN_TXBC */
#define CAN_M_CAN_TXBC_TBSA           BITS(2,15)                                          /*!< Tx buffer start address */
#define CAN_M_CAN_TXBC_NDTB           BITS(16,21)                                         /*!< number of dedicated transmit buffers */
#define CAN_M_CAN_TXBC_TFQS           BITS(24,29)                                         /*!< Tx FIFO/Queue size */
#define CAN_M_CAN_TXBC_TFQM           BIT(30)                                             /*!< Tx FIFO/Queue mode */

/* CAN_M_CAN_TXFQS */
#define CAN_M_CAN_TXFQS_TFFL          BITS(0,5)                                           /*!< Tx FIFO free level */
#define CAN_M_CAN_TXFQS_TFGI          BITS(8,12)                                          /*!< Tx FIFO get index */
#define CAN_M_CAN_TXFQS_TFQPI         BITS(16,20)                                         /*!< Tx FIFO/Queue put index */
#define CAN_M_CAN_TXFQS_TFQF          BIT(21)                                             /*!< Tx FIFO/Queue full */

/* CAN_M_CAN_TXESC */
#define CAN_M_CAN_TXESC_TBDS          BITS(0,2)                                           /*!< Tx buffer data field size */

/* CAN_M_CAN_TXBRP */
#define CAN_M_CAN_TXBRP_TRP(x)        BIT(x)                                              /*!< transmission request pending x */

/* CAN_M_CAN_TXBAR */
#define CAN_M_CAN_TXBAR_AR(x)         BIT(x)                                              /*!< add request x */

/* CAN_M_CAN_TXBCR */
#define CAN_M_CAN_TXBCR_CR(x)         BIT(x)                                              /*!< cancellation request x */

/* CAN_M_CAN_TXBTO */
#define CAN_M_CAN_TXBTO_TO(x)         BIT(x)                                              /*!< transmission occurred x */

/* CAN_M_CAN_TXBCF */
#define CAN_M_CAN_TXBCF_CF(x)         BIT(x)                                              /*!< cancellation finished x */

/* CAN_M_CAN_TXBTIE */
#define CAN_M_CAN_TXBTIE_TIE(x)       BIT(x)                                              /*!< transmission interrupt enable x */

/* CAN_M_CAN_TXBCIE */
#define CAN_M_CAN_TXBCIE_CFIE(x)      BIT(x)                                              /*!< cancellation finished interrupt enable x */

/* CAN_M_CAN_TXEFC */
#define CAN_M_CAN_TXEFC_EFSA          BITS(2,15)                                          /*!< event FIFO start address */
#define CAN_M_CAN_TXEFC_EFS           BITS(16,21)                                         /*!< event FIFO size */
#define CAN_M_CAN_TXEFC_EFWM          BITS(24,29)                                         /*!< event FIFO watermark */

/* CAN_M_CAN_TXEFS */
#define CAN_M_CAN_TXEFS_EFFL          BITS(0,5)                                           /*!< event FIFO fill level */
#define CAN_M_CAN_TXEFS_EFGI          BITS(8,12)                                          /*!< event FIFO get index */
#define CAN_M_CAN_TXEFS_EFPI          BITS(16,20)                                         /*!< event FIFO put index */
#define CAN_M_CAN_TXEFS_EFF           BIT(24)                                             /*!< event FIFO full */
#define CAN_M_CAN_TXEFS_TEFL          BIT(25)                                             /*!< Tx event FIFO element lost */

/* CAN_M_CAN_TXEFA */
#define CAN_M_CAN_TXEFA_EFAI          BITS(0,4)                                           /*!< event FIFO acknowledge index */

/* CAN_DMU_DMUCR */
#define CAN_DMU_DMUCR_DAY             BITS(0,7)                                           /*!< time stamp day (two digit, BCD-coded) */
#define CAN_DMU_DMUCR_MON             BITS(8,15)                                          /*!< time stamp month (two digit, BCD-coded) */
#define CAN_DMU_DMUCR_YEAR            BITS(16,19)                                         /*!< time stamp year (one digit, BCD-coded) */
#define CAN_DMU_DMUCR_SUBSTEP         BITS(20,23)                                         /*!< sub-step of core release (one digit, BCD-coded) */
#define CAN_DMU_DMUCR_STEP            BITS(24,27)                                         /*!< step of core release (one digit, BCD-coded) */
#define CAN_DMU_DMUCR_REL             BITS(28,31)                                         /*!< core release (one digit, BCD-coded) */

/* CAN_DMU_DMUI */
#define CAN_DMU_DMUI_TXR              BIT(0)                                              /*!< TX service request line of DMU */
#define CAN_DMU_DMUI_RX0R             BIT(1)                                              /*!< RX0 service request line of DMU */
#define CAN_DMU_DMUI_RX1R             BIT(2)                                              /*!< RX1 service request line of DMU */
#define CAN_DMU_DMUI_TXER             BIT(3)                                              /*!< TX event service request line of DMU */
#define CAN_DMU_DMUI_TFQPIP           BITS(8,12)                                          /*!< TX FIFO/Queue put index previous */
#define CAN_DMU_DMUI_ENA              BIT(15)                                             /*!< DMU is enabled */
#define CAN_DMU_DMUI_EHS              BITS(24,26)                                         /*!< element handler state */
#define CAN_DMU_DMUI_TX               BIT(28)                                             /*!< TX DMU element service */
#define CAN_DMU_DMUI_RX0              BIT(29)                                             /*!< RX0 DMU element service */
#define CAN_DMU_DMUI_RX1              BIT(30)                                             /*!< RX1 DMU element service */
#define CAN_DMU_DMUI_TXE              BIT(31)                                             /*!< TX event DMU element service */

/* CAN_DMU_DMUQC */
#define CAN_DMU_DMUQC_TXEEC           BITS(0,7)                                           /*!< TX element enqueueing counter */
#define CAN_DMU_DMUQC_RX0EDC          BITS(8,15)                                          /*!< RX0 element dequeueing counter */
#define CAN_DMU_DMUQC_RX1EDC          BITS(16,23)                                         /*!< RX1 element dequeueing counter */
#define CAN_DMU_DMUQC_TXEEDC          BITS(24,31)                                         /*!< TX event element dequeueing counter */

/* CAN_DMU_DMUIR */
#define CAN_DMU_DMUIR_TXENSA          BIT(0)                                              /*!< TX element not start address */
#define CAN_DMU_DMUIR_TXEIE           BIT(1)                                              /*!< TX element illegal enqueueing */
#define CAN_DMU_DMUIR_TXEIAS          BIT(2)                                              /*!< TX element illegal access sequence */
#define CAN_DMU_DMUIR_TXEIDLC         BIT(3)                                              /*!< TX element illegal DLC */
#define CAN_DMU_DMUIR_TXEWATA         BIT(4)                                              /*!< TX element write after trigger address */
#define CAN_DMU_DMUIR_TXEIR           BIT(5)                                              /*!< TX element illegal read */
#define CAN_DMU_DMUIR_TXEE            BIT(6)                                              /*!< TX element enqueued */
#define CAN_DMU_DMUIR_RX0ENSA         BIT(8)                                              /*!< RX0 element not start address */
#define CAN_DMU_DMUIR_RX0EID          BIT(9)                                              /*!< RX0 element illegal dequeueing */
#define CAN_DMU_DMUIR_RX0EIAS         BIT(10)                                             /*!< RX0 element illegal access sequence */
#define CAN_DMU_DMUIR_RX0EIW          BIT(11)                                             /*!< RX0 element illegal write */
#define CAN_DMU_DMUIR_RX0ED           BIT(12)                                             /*!< RX0 element dequeued */
#define CAN_DMU_DMUIR_RX1ENSA         BIT(16)                                             /*!< RX1 element not start address */
#define CAN_DMU_DMUIR_RX1EID          BIT(17)                                             /*!< RX1 element illegal dequeueing */
#define CAN_DMU_DMUIR_RX1EIAS         BIT(18)                                             /*!< RX1 element illegal access sequence */
#define CAN_DMU_DMUIR_RX1EIW          BIT(19)                                             /*!< RX1 element illegal write */
#define CAN_DMU_DMUIR_RX1ED           BIT(20)                                             /*!< RX1 element dequeued */
#define CAN_DMU_DMUIR_TXEENSA         BIT(24)                                             /*!< TX event element not start address */
#define CAN_DMU_DMUIR_TXEEID          BIT(25)                                             /*!< TX event element illegal dequeueing */
#define CAN_DMU_DMUIR_TXEEIAS         BIT(26)                                             /*!< TX event element illegal access sequence */
#define CAN_DMU_DMUIR_TXEEIW          BIT(27)                                             /*!< TX event element illegal write */
#define CAN_DMU_DMUIR_TXEED           BIT(28)                                             /*!< TX event element dequeued */
#define CAN_DMU_DMUIR_IAC             BIT(30)                                             /*!< illegal access while in configuration mode */

/* CAN_DMU_DMUIE */
#define CAN_DMU_DMUIE_TXENSAE         BIT(0)                                              /*!< TX element not start address enable */
#define CAN_DMU_DMUIE_TXEIEE          BIT(1)                                              /*!< TX element illegal enqueueing enable */
#define CAN_DMU_DMUIE_TXEIASE         BIT(2)                                              /*!< TX element illegal access sequence enable */
#define CAN_DMU_DMUIE_TXEIDLCE        BIT(3)                                              /*!< TX element illegal DLC enable */
#define CAN_DMU_DMUIE_TXEWATAE        BIT(4)                                              /*!< TX element write after trigger address enable */
#define CAN_DMU_DMUIE_TXEIRE          BIT(5)                                              /*!< TX element illegal read enable */
#define CAN_DMU_DMUIE_TXEEE           BIT(6)                                              /*!< TX element enqueued enable */
#define CAN_DMU_DMUIE_RX0ENSAE        BIT(8)                                              /*!< RX0 element not start address enable */
#define CAN_DMU_DMUIE_RX0EIDE         BIT(9)                                              /*!< RX0 element illegal dequeueing enable */
#define CAN_DMU_DMUIE_RX0EIASE        BIT(10)                                             /*!< RX0 element illegal access sequence enable */
#define CAN_DMU_DMUIE_RX0EIWE         BIT(11)                                             /*!< RX0 element illegal write enable */
#define CAN_DMU_DMUIE_RX0EDE          BIT(12)                                             /*!< RX0 element dequeued enable */
#define CAN_DMU_DMUIE_RX1ENSAE        BIT(16)                                             /*!< RX1 element not start address enable */
#define CAN_DMU_DMUIE_RX1EIDE         BIT(17)                                             /*!< RX1 element illegal dequeueing enable */
#define CAN_DMU_DMUIE_RX1EIASE        BIT(18)                                             /*!< RX1 element illegal access sequence enable */
#define CAN_DMU_DMUIE_RX1EIWE         BIT(19)                                             /*!< RX1 element illegal write enable */
#define CAN_DMU_DMUIE_RX1EDE          BIT(20)                                             /*!< RX1 element dequeued enable */
#define CAN_DMU_DMUIE_TXEENSAE        BIT(24)                                             /*!< TX event element not start address enable */
#define CAN_DMU_DMUIE_TXEEIDE         BIT(25)                                             /*!< TX event element illegal dequeueing enable */
#define CAN_DMU_DMUIE_TXEEIASE        BIT(26)                                             /*!< TX event element illegal access sequence enable */
#define CAN_DMU_DMUIE_TXEEIWE         BIT(27)                                             /*!< TX event element illegal write enable */
#define CAN_DMU_DMUIE_TXEEDE          BIT(28)                                             /*!< TX event element dequeued enable */
#define CAN_DMU_DMUIE_IACE            BIT(30)                                             /*!< illegal access while in configuration mode enable */

/* CAN_DMU_DMUC */
#define CAN_DMU_DMUC_TTS              BIT(0)                                              /*!< transfer timestamp */

/* CAN_R0 */
#define CAN_R0_ID                     BITS(0,28)                                          /*!< identifier */
#define CAN_R0_RTR                    BIT(29)                                             /*!< remote transmission request */
#define CAN_R0_XTD                    BIT(30)                                             /*!< extended identifier */
#define CAN_R0_ESI                    BIT(31)                                             /*!< error state indicator */

/* CAN_R1A */
#define CAN_R1A_RXTS                  BITS(0,15)                                          /*!< identifier */
#define CAN_R1A_DLC                   BITS(16,19)                                         /*!< data length code */
#define CAN_R1A_BRS                   BIT(20)                                             /*!< bit rate switch */
#define CAN_R1A_FDF                   BIT(21)                                             /*!< FD format */
#define CAN_R1A_FIDX                  BITS(24,30)                                         /*!< filter index */
#define CAN_R1A_ANMF                  BIT(31)                                             /*!< accepted non-matching frame */

/* CAN_T0 */
#define CAN_T0_ID                     BITS(0,28)                                          /*!< identifier */
#define CAN_T0_RTR                    BIT(29)                                             /*!< remote transmission request */
#define CAN_T0_XTD                    BIT(30)                                             /*!< extended identifier */
#define CAN_T0_ESI                    BIT(31)                                             /*!< error state indicator */

/* CAN_T1 */
#define CAN_T1_MM_HIGH                BITS(8,15)                                          /*!< message marker high byte */
#define CAN_T1_DLC                    BITS(16,19)                                         /*!< data length code */
#define CAN_T1_BRS                    BIT(20)                                             /*!< bit rate switch */
#define CAN_T1_FDF                    BIT(21)                                             /*!< FD format */
#define CAN_T1_EFC                    BIT(23)                                             /*!< event FIFO control */
#define CAN_T1_MM_LOW                 BITS(24,31)                                         /*!< message marker low byte */

/* CAN_T2 */
#define CAN_T2_DB0                    BITS(0,7)                                           /*!< data byte 0 */
#define CAN_T2_DB1                    BITS(8,15)                                          /*!< data byte 1 */
#define CAN_T2_DB2                    BITS(16,23)                                         /*!< data byte 2 */
#define CAN_T2_DB3                    BITS(24,31)                                         /*!< data byte 3 */

/* CAN_T3 */
#define CAN_T3_DB4                    BITS(0,7)                                           /*!< data byte 4 */
#define CAN_T3_DB5                    BITS(8,15)                                          /*!< data byte 5 */
#define CAN_T3_DB6                    BITS(16,23)                                         /*!< data byte 6 */
#define CAN_T3_DB7                    BITS(24,31)                                         /*!< data byte 7 */

/* CAN_E0 */
#define CAN_E0_ID                     BITS(0,28)                                          /*!< identifier */
#define CAN_E0_RTR                    BIT(29)                                             /*!< remote transmission request */
#define CAN_E0_XTD                    BIT(30)                                             /*!< extended identifier */
#define CAN_E0_ESI                    BIT(31)                                             /*!< error state indicator */

/* CAN_E1A */
#define CAN_E1A_TXTS                  BITS(0,15)                                          /*!< TX timestamp */
#define CAN_E1A_DLC                   BITS(16,19)                                         /*!< data length code */
#define CAN_E1A_BRS                   BIT(20)                                             /*!< bit rate switch */
#define CAN_E1A_FDF                   BIT(21)                                             /*!< FD format */
#define CAN_E1A_ET                    BITS(22,23)                                         /*!< event type */
#define CAN_E1A_MM_LOW                BITS(24,31)                                         /*!< message marker low byte */

/* CAN_E1B */
#define CAN_E1B_MM_HIGH               BITS(8,15)                                          /*!< message marker high byte */
#define CAN_E1B_DLC                   BITS(16,19)                                         /*!< data length code */
#define CAN_E1B_BRS                   BIT(20)                                             /*!< bit rate switch */
#define CAN_E1B_FDF                   BIT(21)                                             /*!< FD format */
#define CAN_E1B_ET                    BITS(22,23)                                         /*!< event type */
#define CAN_E1B_MM_LOW                BITS(24,31)                                         /*!< message marker low byte */

/* CAN_S0 */
#define CAN_S0_SFID2                  BITS(0,10)                                          /*!< standard filter ID 2 */
#define CAN_S0_SFID1                  BITS(16,26)                                         /*!< standard filter ID 1 */
#define CAN_S0_SFEC                   BITS(27,29)                                         /*!< standard filter element configuration */
#define CAN_S0_SFT                    BITS(30,31)                                         /*!< standard filter type */

/* CAN_F0 */
#define CAN_F0_EFID1                  BITS(0,28)                                          /*!< extended filter ID 1 */
#define CAN_F0_EFEC                   BITS(29,31)                                         /*!< extended filter element configuration */

/* CAN_F1 */
#define CAN_F1_EFID2                  BITS(0,28)                                          /*!< extended filter ID 2 */
#define CAN_F1_EFT                    BITS(30,31)                                         /*!< extended filter type */

/* constants definitions */
/* define the CAN bit position and its register index offset */
#define CAN_REGIDX_BIT(regidx, bitpos) (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define CAN_REG_VAL(canx, offset)      (REG32((uint32_t)(canx) + (((uint32_t)(offset) & 0x0000FFFFU)>> 6U)))
#define CAN_BIT_POS(val)               ((uint32_t)(val) & 0x0000001FU)
#define CAN_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22U) | (uint32_t)((bitpos2) << 16U)\
                                                              | (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos)))
#define CAN_REG_VAL2(canx, offset)     (REG32((uint32_t)(canx) + ((uint32_t)(offset) >> 22U)))
#define CAN_BIT_POS2(val)              (((uint32_t)(val) & 0x001F0000U) >> 16U)
#define CAN_CERRR(canx, num)           REG32((canx) + 0x00000084U + (num) * 0x00000004U) /*!< CAN correctable error record x register */

/* register offset */
#define MERRCTL_REG_OFFSET             ((uint32_t)0x00000080U)                            /*!< CAN_MERRCTL register offset */
#define MERRSTAT_REG_OFFSET            ((uint32_t)0x0000009CU)                            /*!< CAN_MERRSTAT register offset */
#define IR_REG_OFFSET                  ((uint32_t)0x00000050U)                            /*!< CAN_M_CAN_IR register offset */
#define IE_REG_OFFSET                  ((uint32_t)0x00000054U)                            /*!< CAN_M_CAN_IE register offset */
#define PSR_REG_OFFSET                 ((uint32_t)0x00000044U)                            /*!< CAN_M_CAN_PSR register offset */
#define TXBTIE_REG_OFFSET              ((uint32_t)0x000000E0U)                            /*!< CAN_M_CAN_TXBTIE register offset */
#define TXBCIE_REG_OFFSET              ((uint32_t)0x000000E4U)                            /*!< CAN_M_CAN_TXBCIE register offset */
#define TXBTO_REG_OFFSET               ((uint32_t)0x000000D8U)                            /*!< CAN_M_CAN_TXBTO register offset */
#define TXBCF_REG_OFFSET               ((uint32_t)0x000000DCU)                            /*!< CAN_M_CAN_TXBCF register offset */
#define DMUIR_REG_OFFSET               ((uint32_t)0x000003CCU)                            /*!< CAN_DMU_DMUIR register offset */
#define DMUIE_REG_OFFSET               ((uint32_t)0x000003D0U)                            /*!< CAN_DMU_DMUIE register offset */

/* enumerations definitions */
/* DTM_CAN base addresses */
typedef enum {
    DTM_CAN0                         = (CAN0 + 0x00002000U),                              /*!< DTM_CAN0 base address */
    DTM_CAN1                         = (CAN0 + 0x00002800U),                              /*!< DTM_CAN1 base address */
    DTM_CAN2                         = (CAN1 + 0x00002000U),                              /*!< DTM_CAN2 base address */
    DTM_CAN3                         = (CAN1 + 0x00002800U),                              /*!< DTM_CAN3 base address */
    DTM_CAN4                         = (CAN1 + 0x00003000U),                              /*!< DTM_CAN4 base address */
    DTM_CAN5                         = (CAN2 + 0x00002000U),                              /*!< DTM_CAN5 base address */
    DTM_CAN6                         = (CAN2 + 0x00002800U),                              /*!< DTM_CAN6 base address */
    DTM_CAN7                         = (CAN2 + 0x00003000U)                               /*!< DTM_CAN7 base address */
} can_dtm_canx_enum;

/* memory error index */
typedef enum {
    CAN_MEM_ERR_CORRECTABLE_0        = 0U,                                                /*!< CAN memory error correctable 0 */
    CAN_MEM_ERR_CORRECTABLE_1        = 1U,                                                /*!< CAN memory error correctable 1 */
    CAN_MEM_ERR_CORRECTABLE_2        = 2U,                                                /*!< CAN memory error correctable 2 */
    CAN_MEM_ERR_CORRECTABLE_3        = 3U,                                                /*!< CAN memory error correctable 3 */
    CAN_MEM_ERR_NONCORRECTABLE       = 4U                                                 /*!< CAN memory error noncorrectable */
} can_memory_error_index_enum;

/* CAN FD operation mode */
typedef enum {
    CAN_CLASSIC_MODE                 = 0U,                                                /*!< classic CAN mode */
    CAN_FD_MODE                      = 1U                                                 /*!< CAN FD mode */
} can_fd_mode_enum;

/* M_CAN operation modes */
typedef enum {
    CAN_MODE_NORMAL                  = 0U,                                                /*!< normal operation mode */
    CAN_MODE_INIT                    = 1U,                                                /*!< initialization mode */
    CAN_MODE_SLEEP                   = 2U,                                                /*!< sleep mode */
    CAN_MODE_MONITOR                 = 3U,                                                /*!< bus monitoring mode */
    CAN_MODE_RESTRICTED              = 4U,                                                /*!< restricted operation mode */
    CAN_MODE_TEST                    = 5U,                                                /*!< test mode */
    CAN_MODE_EXTERNAL_LOOPBACK       = 6U,                                                /*!< external loopback mode */
    CAN_MODE_INTERNAL_LOOPBACK       = 7U                                                 /*!< internal loopback mode */
} can_operating_mode_enum;

/* frame / filter format */
typedef enum {
    CAN_FF_STANDARD                  = 0U,                                                /*!< standard format frame / filter */
    CAN_FF_EXTENDED                  = 1U                                                 /*!< extended format frame / filter */
} can_ff_enum;

/* frame type */
typedef enum {
    CAN_FT_DATA                      = 0U,                                                /*!< data frame */
    CAN_FT_REMOTE                    = 1U                                                 /*!< remote frame */
} can_frame_type_enum;

/* operation mode for determining a timeout */
typedef enum {
    CAN_TIMEOUT_CONTINUOUS           = 0U,                                                /*!< timeout continuous operation */
    CAN_TIMEOUT_TXFIFO               = 1U,                                                /*!< timeout controlled by Tx FIFO */
    CAN_TIMEOUT_RXFIFO0              = 2U,                                                /*!< timeout controlled by Rx FIFO 0 */
    CAN_TIMEOUT_RXFIFO1              = 3U                                                 /*!< timeout controlled by Rx FIFO 1 */
} can_timeout_mode_enum;

/* filter type */
typedef enum {
    CAN_FILTER_RANGE                 = 0U,                                                /*!< range filter from SFID1 to SFID2 (SFID2 >= SFID1) */
    CAN_FILTER_DUAL                  = 1U,                                                /*!< dual ID filter for SFID1 or SFID2 */
    CAN_FILTER_MASK                  = 2U,                                                /*!< classic filter: SFID1 = filter, SFID2 = mask */
    CAN_FILTER_RANGE_NOMASK_DISABLE  = 3U                                                 /*!< range filter SFID1 to SFID2, EIDM mask not applied */
} can_filter_type_enum;

/* filter element configuration */
typedef enum {
    CAN_FILTER_DISABLE               = 0U,                                                /*!< disable filter element */
    CAN_FILTER_TO_RXFIFO0            = 1U,                                                /*!< store in Rx FIFO 0 if filter matches */
    CAN_FILTER_TO_RXFIFO1            = 2U,                                                /*!< store in Rx FIFO 1 if filter matches */
    CAN_FILTER_REJECT                = 3U,                                                /*!< reject element if filter matches */
    CAN_FILTER_HP                    = 4U,                                                /*!< set high priority if filter matches */
    CAN_FILTER_TO_RXFIFO0_HP         = 5U,                                                /*!< set high priority and store in FIFO 0 if filter matches */
    CAN_FILTER_TO_RXFIFO1_HP         = 6U,                                                /*!< set high priority and store in FIFO 1 if filter matches */
    CAN_FILTER_TO_RXBUFFER           = 7U                                                 /*!< store into Rx Buffer, filter element is Rx Buffer index */
} can_filter_element_enum;

/* storage type */
typedef enum {
    CAN_RXFIFO0                      = 0U,                                                /*!< accept in Rx FIFO 0 */
    CAN_RXFIFO1                      = 1U,                                                /*!< accept in Rx FIFO 1 */
    CAN_RXBUFFER                     = 2U                                                 /*!< accept in Rx buffer */
} can_storage_type_enum;

/* TX pin output control */
typedef enum {
    CAN_TX_CONTROL_NORMAL            = 0U,                                                /*!< CAN_TX pin is controlled by the CAN core */
    CAN_TX_CONTROL_SAMPLE_POINT      = 1U,                                                /*!< sample point can be monitored at CAN_TX pin */
    CAN_TX_CONTROL_DOMINANT          = 2U,                                                /*!< CAN_TX pin drives a dominant state (low) */
    CAN_TX_CONTROL_RECESSIVE         = 3U                                                 /*!< CAN_TX pin drives a recessive state (high) */
} can_tx_control_enum;

/* message storage indicator */
typedef enum {
    CAN_MSI_NO_STORE                 = 0U,                                                /*!< message is not stored */
    CAN_MSI_MESSAGE_LOST             = 1U,                                                /*!< FIFO message lost */
    CAN_MSI_RXFIFO0                  = 2U,                                                /*!< FIFO 0 message available */
    CAN_MSI_RXFIFO1                  = 3U                                                 /*!< FIFO 1 message available */
} can_msi_enum;

/* TX event type */
typedef enum {
    CAN_NONE                         = 1U,                                                /*!< reserved */
    CAN_TX                           = 1U,                                                /*!< Tx event */
    CAN_TX_AFTER_CANCEL              = 2U,                                                /*!< transmission in spite of cancellation */
} can_tx_ev_type_enum;

/* error status */
typedef enum {
    CAN_ERROR_NONE                   = 0U,                                                /*!< no error */
    CAN_ERROR_STUFF                  = 1U,                                                /*!< stuff error */
    CAN_ERROR_FORM                   = 2U,                                                /*!< form error */
    CAN_ERROR_ACK                    = 3U,                                                /*!< acknowledge error */
    CAN_ERROR_RECESSIVE_BIT          = 4U,                                                /*!< recessive bit error */
    CAN_ERROR_DOMINANT_BIT           = 5U,                                                /*!< dominant bit error */
    CAN_ERROR_CRC                    = 6U,                                                /*!< CRC error */
    CAN_ERROR_NOCHANGE               = 7U                                                 /*!< no CAN bus event was detected since the last CPU read access to the register */
} can_error_enum;

/* protocol activity */
typedef enum {
    CAN_ACTIVITY_SYNC                = 0U,                                                /*!< synchronizing */
    CAN_ACTIVITY_IDLE                = 1U,                                                /*!< idle state */
    CAN_ACTIVITY_RX                  = 2U,                                                /*!< reception state */
    CAN_ACTIVITY_TX                  = 3U                                                 /*!< transmission state */
} can_activity_enum;

/* fifo type */
typedef enum {
    CAN_FIFO_TX                      = 0U,                                                /*!< Tx FIFO */
    CAN_FIFO_RX0                     = 1U,                                                /*!< Rx FIFO 0 */
    CAN_FIFO_RX1                     = 2U,                                                /*!< Rx FIFO 1 */
    CAN_FIFO_TXEVENT                 = 3U                                                 /*!< Tx event FIFO */
} can_fifo_type_enum;

/* CAN memory error flags */
typedef enum {
    CAN_FLAG_NCE_EAE                 = CAN_MERRSTAT_NCE_EAEF,                             /*!< noncorrectable ECC after EDC error flag */
    CAN_FLAG_NCE_AEDC                = CAN_MERRSTAT_NCE_AEDCF,                            /*!< noncorrectable address EDC error flag */
    CAN_FLAG_NCDE                    = CAN_MERRSTAT_NCDEF,                                /*!< noncorrectable double bit error flag */
    CAN_FLAG_BUFOV                   = CAN_MERRSTAT_BUFOVF,                               /*!< correctable error record buffer overflow flag */
    CAN_FLAG_CEOV                    = CAN_MERRSTAT_CEOVF,                                /*!< correctable error overflow flag */
    CAN_FLAG_NCEOV                   = CAN_MERRSTAT_NCEOVF,                               /*!< noncorrectable error overflow flag */
    CAN_FLAG_CE                      = CAN_MERRSTAT_CEF                                   /*!< correctable error flag */
} can_memerr_flag_enum;

/* CAN memory error interrupt flags */
typedef enum {
    CAN_INT_FLAG_CE                  = CAN_MERRSTAT_CEF,                                  /*!< correctable error interrupt flag */
    CAN_INT_FLAG_NCE                 = (CAN_MERRSTAT_NCE_EAEF | CAN_MERRSTAT_NCE_AEDCF | CAN_MERRSTAT_NCDEF)  /*!< noncorrectable error interrupt flag */
} can_memerr_interrupt_flag_enum;

/* CAN memory error interrupts */
typedef enum {
    CAN_INT_CE                       = CAN_MERRCTL_CEIE,                                  /*!< correctable error interrupt */
    CAN_INT_NCE                      = CAN_MERRCTL_NCEIE                                  /*!< noncorrectable error interrupt */
} can_memerr_interrupt_enum;

/* CAN flags */
typedef enum {
    /* flags in CAN_M_CAN_IR register */
    CAN_FLAG_RFIFO0_NEW              = CAN_REGIDX_BIT(IR_REG_OFFSET, 0U),                 /*!< Rx FIFO 0 new message flag */
    CAN_FLAG_RFIFO0_WM               = CAN_REGIDX_BIT(IR_REG_OFFSET, 1U),                 /*!< Rx FIFO 0 watermark reached flag */
    CAN_FLAG_RFIFO0_FULL             = CAN_REGIDX_BIT(IR_REG_OFFSET, 2U),                 /*!< Rx FIFO 0 full flag */
    CAN_FLAG_RFIFO0_MESLOST          = CAN_REGIDX_BIT(IR_REG_OFFSET, 3U),                 /*!< Rx FIFO 0 message lost flag */
    CAN_FLAG_RFIFO1_NEW              = CAN_REGIDX_BIT(IR_REG_OFFSET, 4U),                 /*!< Rx FIFO 1 new message flag */
    CAN_FLAG_RFIFO1_WM               = CAN_REGIDX_BIT(IR_REG_OFFSET, 5U),                 /*!< Rx FIFO 1 watermark reached flag */
    CAN_FLAG_RFIFO1_FULL             = CAN_REGIDX_BIT(IR_REG_OFFSET, 6U),                 /*!< Rx FIFO 1 full flag */
    CAN_FLAG_RFIFO1_MESLOST          = CAN_REGIDX_BIT(IR_REG_OFFSET, 7U),                 /*!< Rx FIFO 1 message lost flag */
    CAN_FLAG_HIGH_PRI_MES            = CAN_REGIDX_BIT(IR_REG_OFFSET, 8U),                 /*!< high priority message flag */
    CAN_FLAG_TX_COMPLETE             = CAN_REGIDX_BIT(IR_REG_OFFSET, 9U),                 /*!< transmission completed flag */
    CAN_FLAG_TX_CANCELLED            = CAN_REGIDX_BIT(IR_REG_OFFSET, 10U),                /*!< transmission cancellation finished flag */
    CAN_FLAG_TXFIFO_EMPTY            = CAN_REGIDX_BIT(IR_REG_OFFSET, 11U),                /*!< Tx FIFO empty flag */
    CAN_FLAG_TXEVFIFO_NEW            = CAN_REGIDX_BIT(IR_REG_OFFSET, 12U),                /*!< Tx event FIFO new entry flag */
    CAN_FLAG_TXEVFIFO_WM             = CAN_REGIDX_BIT(IR_REG_OFFSET, 13U),                /*!< Tx event FIFO watermark reached flag */
    CAN_FLAG_TXEVFIFO_FULL           = CAN_REGIDX_BIT(IR_REG_OFFSET, 14U),                /*!< Tx event FIFO full flag */
    CAN_FLAG_TXEVFIFO_ELELOST        = CAN_REGIDX_BIT(IR_REG_OFFSET, 15U),                /*!< Tx event FIFO element lost flag */
    CAN_FLAG_TIMESTAMP_WRAP          = CAN_REGIDX_BIT(IR_REG_OFFSET, 16U),                /*!< timestamp wraparound flag */
    CAN_FLAG_RAM_ACCESS_FAIL         = CAN_REGIDX_BIT(IR_REG_OFFSET, 17U),                /*!< message RAM access failure flag */
    CAN_FLAG_TIMEOUT                 = CAN_REGIDX_BIT(IR_REG_OFFSET, 18U),                /*!< timeout occurred flag */
    CAN_FLAG_RXBUFFER_NEW            = CAN_REGIDX_BIT(IR_REG_OFFSET, 19U),                /*!< message stored to dedicated Rx buffer flag */
    CAN_FLAG_ERRLOG_OVERFLOW         = CAN_REGIDX_BIT(IR_REG_OFFSET, 22U),                /*!< error logging overflow flag */
    CAN_FLAG_ERR_PASSIVE_CHANGE      = CAN_REGIDX_BIT(IR_REG_OFFSET, 23U),                /*!< error passive change flag */
    CAN_FLAG_WARNING_CHANGE          = CAN_REGIDX_BIT(IR_REG_OFFSET, 24U),                /*!< warning status change flag */
    CAN_FLAG_BUSOFF_CHANGE           = CAN_REGIDX_BIT(IR_REG_OFFSET, 25U),                /*!< bus_off status change flag */
    CAN_FLAG_WATCHDOG                = CAN_REGIDX_BIT(IR_REG_OFFSET, 26U),                /*!< watchdog interrupt flag */
    CAN_FLAG_PROT_ERR_ARBITRATION    = CAN_REGIDX_BIT(IR_REG_OFFSET, 27U),                /*!< protocol error in arbitration phase flag */
    CAN_FLAG_PROT_ERR_DATA           = CAN_REGIDX_BIT(IR_REG_OFFSET, 28U),                /*!< protocol error in data phase flag */
    /* CAN_M_CAN_TXBTIE interrupts */
    CAN_FLAG_TXBUF0_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 0U),              /*!< Tx buffer 0 transmission flag */
    CAN_FLAG_TXBUF1_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 1U),              /*!< Tx buffer 1 transmission flag */
    CAN_FLAG_TXBUF2_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 2U),              /*!< Tx buffer 2 transmission flag */
    CAN_FLAG_TXBUF3_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 3U),              /*!< Tx buffer 3 transmission flag */
    CAN_FLAG_TXBUF4_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 4U),              /*!< Tx buffer 4 transmission flag */
    CAN_FLAG_TXBUF5_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 5U),              /*!< Tx buffer 5 transmission flag */
    CAN_FLAG_TXBUF6_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 6U),              /*!< Tx buffer 6 transmission flag */
    CAN_FLAG_TXBUF7_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 7U),              /*!< Tx buffer 7 transmission flag */
    CAN_FLAG_TXBUF8_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 8U),              /*!< Tx buffer 8 transmission flag */
    CAN_FLAG_TXBUF9_COMPLETE         = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 9U),              /*!< Tx buffer 9 transmission flag */
    CAN_FLAG_TXBUF10_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 10U),             /*!< Tx buffer 10 transmission flag */
    CAN_FLAG_TXBUF11_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 11U),             /*!< Tx buffer 11 transmission flag */
    CAN_FLAG_TXBUF12_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 12U),             /*!< Tx buffer 12 transmission flag */
    CAN_FLAG_TXBUF13_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 13U),             /*!< Tx buffer 13 transmission flag */
    CAN_FLAG_TXBUF14_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 14U),             /*!< Tx buffer 14 transmission flag */
    CAN_FLAG_TXBUF15_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 15U),             /*!< Tx buffer 15 transmission flag */
    CAN_FLAG_TXBUF16_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 16U),             /*!< Tx buffer 16 transmission flag */
    CAN_FLAG_TXBUF17_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 17U),             /*!< Tx buffer 17 transmission flag */
    CAN_FLAG_TXBUF18_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 18U),             /*!< Tx buffer 18 transmission flag */
    CAN_FLAG_TXBUF19_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 19U),             /*!< Tx buffer 19 transmission flag */
    CAN_FLAG_TXBUF20_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 20U),             /*!< Tx buffer 20 transmission flag */
    CAN_FLAG_TXBUF21_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 21U),             /*!< Tx buffer 21 transmission flag */
    CAN_FLAG_TXBUF22_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 22U),             /*!< Tx buffer 22 transmission flag */
    CAN_FLAG_TXBUF23_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 23U),             /*!< Tx buffer 23 transmission flag */
    CAN_FLAG_TXBUF24_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 24U),             /*!< Tx buffer 24 transmission flag */
    CAN_FLAG_TXBUF25_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 25U),             /*!< Tx buffer 25 transmission flag */
    CAN_FLAG_TXBUF26_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 26U),             /*!< Tx buffer 26 transmission flag */
    CAN_FLAG_TXBUF27_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 27U),             /*!< Tx buffer 27 transmission flag */
    CAN_FLAG_TXBUF28_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 28U),             /*!< Tx buffer 28 transmission flag */
    CAN_FLAG_TXBUF29_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 29U),             /*!< Tx buffer 29 transmission flag */
    CAN_FLAG_TXBUF30_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 30U),             /*!< Tx buffer 30 transmission flag */
    CAN_FLAG_TXBUF31_COMPLETE        = CAN_REGIDX_BIT(TXBTO_REG_OFFSET, 31U),             /*!< Tx buffer 31 transmission flag */
    /* CAN_M_CAN_TXBCIE interrupts */
    CAN_FLAG_TXBUF0_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 0U),              /*!< Tx buffer 0 transmission cancel finished flag */
    CAN_FLAG_TXBUF1_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 1U),              /*!< Tx buffer 1 transmission cancel finished flag */
    CAN_FLAG_TXBUF2_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 2U),              /*!< Tx buffer 2 transmission cancel finished flag */
    CAN_FLAG_TXBUF3_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 3U),              /*!< Tx buffer 3 transmission cancel finished flag */
    CAN_FLAG_TXBUF4_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 4U),              /*!< Tx buffer 4 transmission cancel finished flag */
    CAN_FLAG_TXBUF5_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 5U),              /*!< Tx buffer 5 transmission cancel finished flag */
    CAN_FLAG_TXBUF6_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 6U),              /*!< Tx buffer 6 transmission cancel finished flag */
    CAN_FLAG_TXBUF7_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 7U),              /*!< Tx buffer 7 transmission cancel finished flag */
    CAN_FLAG_TXBUF8_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 8U),              /*!< Tx buffer 8 transmission cancel finished flag */
    CAN_FLAG_TXBUF9_CANCELLED        = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 9U),              /*!< Tx buffer 9 transmission cancel finished flag */
    CAN_FLAG_TXBUF10_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 10U),             /*!< Tx buffer 10 transmission cancel finished flag */
    CAN_FLAG_TXBUF11_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 11U),             /*!< Tx buffer 11 transmission cancel finished flag */
    CAN_FLAG_TXBUF12_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 12U),             /*!< Tx buffer 12 transmission cancel finished flag */
    CAN_FLAG_TXBUF13_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 13U),             /*!< Tx buffer 13 transmission cancel finished flag */
    CAN_FLAG_TXBUF14_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 14U),             /*!< Tx buffer 14 transmission cancel finished flag */
    CAN_FLAG_TXBUF15_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 15U),             /*!< Tx buffer 15 transmission cancel finished flag */
    CAN_FLAG_TXBUF16_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 16U),             /*!< Tx buffer 16 transmission cancel finished flag */
    CAN_FLAG_TXBUF17_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 17U),             /*!< Tx buffer 17 transmission cancel finished flag */
    CAN_FLAG_TXBUF18_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 18U),             /*!< Tx buffer 18 transmission cancel finished flag */
    CAN_FLAG_TXBUF19_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 19U),             /*!< Tx buffer 19 transmission cancel finished flag */
    CAN_FLAG_TXBUF20_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 20U),             /*!< Tx buffer 20 transmission cancel finished flag */
    CAN_FLAG_TXBUF21_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 21U),             /*!< Tx buffer 21 transmission cancel finished flag */
    CAN_FLAG_TXBUF22_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 22U),             /*!< Tx buffer 22 transmission cancel finished flag */
    CAN_FLAG_TXBUF23_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 23U),             /*!< Tx buffer 23 transmission cancel finished flag */
    CAN_FLAG_TXBUF24_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 24U),             /*!< Tx buffer 24 transmission cancel finished flag */
    CAN_FLAG_TXBUF25_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 25U),             /*!< Tx buffer 25 transmission cancel finished flag */
    CAN_FLAG_TXBUF26_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 26U),             /*!< Tx buffer 26 transmission cancel finished flag */
    CAN_FLAG_TXBUF27_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 27U),             /*!< Tx buffer 27 transmission cancel finished flag */
    CAN_FLAG_TXBUF28_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 28U),             /*!< Tx buffer 28 transmission cancel finished flag */
    CAN_FLAG_TXBUF29_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 29U),             /*!< Tx buffer 29 transmission cancel finished flag */
    CAN_FLAG_TXBUF30_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 30U),             /*!< Tx buffer 30 transmission cancel finished flag */
    CAN_FLAG_TXBUF31_CANCELLED       = CAN_REGIDX_BIT(TXBCF_REG_OFFSET, 31U),             /*!< Tx buffer 31 transmission cancel finished flag */
    /* flags in CAN_DMU_DMUIR register */
    DMU_FLAG_TX_ELE_NOT_STADDR       = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 0U),              /*!< TX element not start address flag */
    DMU_FLAG_TX_ELE_ILLE_ENQ         = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 1U),              /*!< TX element illegal enqueueing flag */
    DMU_FLAG_TX_ELE_ILLE_ACCSEQ      = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 2U),              /*!< TX element illegal access sequence flag */
    DMU_FLAG_TX_ELE_ILLE_DLC         = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 3U),              /*!< TX element illegal DLC flag */
    DMU_FLAG_TX_ELE_WRITE_AFTTRIG    = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 4U),              /*!< TX element write after trigger address flag */
    DMU_FLAG_TX_ELE_ILLE_READ        = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 5U),              /*!< TX element illegal read flag */
    DMU_FLAG_TX_ELE_ENQ              = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 6U),              /*!< TX element enqueued flag */
    DMU_FLAG_RX0_ELE_NOT_STADDR      = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 8U),              /*!< RX0 element not start address flag */
    DMU_FLAG_RX0_ELE_ILLE_DEQ        = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 9U),              /*!< RX0 element illegal dequeueing flag */
    DMU_FLAG_RX0_ELE_ILLE_ACCSEQ     = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 10U),             /*!< RX0 element illegal access sequence flag */
    DMU_FLAG_RX0_ELE_ILLE_WRITE      = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 11U),             /*!< RX0 element illegal write flag */
    DMU_FLAG_RX0_ELE_DEQ             = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 12U),             /*!< RX0 element dequeued flag */
    DMU_FLAG_RX1_ELE_NOT_STADDR      = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 16U),             /*!< RX1 element not start address flag */
    DMU_FLAG_RX1_ELE_ILLE_DEQ        = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 17U),             /*!< RX1 element illegal dequeueing flag */
    DMU_FLAG_RX1_ELE_ILLE_ACCSEQ     = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 18U),             /*!< RX1 element illegal access sequence flag */
    DMU_FLAG_RX1_ELE_ILLE_WRITE      = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 19U),             /*!< RX1 element illegal write flag */
    DMU_FLAG_RX1_ELE_DEQ             = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 20U),             /*!< RX1 element dequeued flag */
    DMU_FLAG_TXEV_ELE_NOT_STADDR     = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 24U),             /*!< TX event element not start address flag */
    DMU_FLAG_TXEV_ELE_ILLE_DEQ       = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 25U),             /*!< TX event element illegal dequeueing flag */
    DMU_FLAG_TXEV_ELE_ILLE_ACCSEQ    = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 26U),             /*!< TX event element illegal access sequence flag */
    DMU_FLAG_TXEV_ELE_ILLE_WRITE     = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 27U),             /*!< TX event element illegal write flag */
    DMU_FLAG_TXEV_ELE_DEQ            = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 28U),             /*!< TX event element dequeued flag */
    DMU_FLAG_ILLE_ACC_IN_CONFIG      = CAN_REGIDX_BIT(DMUIR_REG_OFFSET, 30U)              /*!< illegal access while in configuration mode flag */
} can_dtmcan_flag_enum;

/* CAN interrupt flag */
typedef enum {
    /* CAN_M_CAN_IR interrupt flags */
    CAN_INT_FLAG_RFIFO0_NEW                   = CAN_REGIDX_BIT2(IE_REG_OFFSET, 0U, IR_REG_OFFSET, 0U),                /*!< Rx FIFO 0 new message interrupt */
    CAN_INT_FLAG_RFIFO0_WM                    = CAN_REGIDX_BIT2(IE_REG_OFFSET, 1U, IR_REG_OFFSET, 1U),                /*!< Rx FIFO 0 watermark reached interrupt */
    CAN_INT_FLAG_RFIFO0_FULL                  = CAN_REGIDX_BIT2(IE_REG_OFFSET, 2U, IR_REG_OFFSET, 2U),                /*!< Rx FIFO 0 full interrupt */
    CAN_INT_FLAG_RFIFO0_MESLOST               = CAN_REGIDX_BIT2(IE_REG_OFFSET, 3U, IR_REG_OFFSET, 3U),                /*!< Rx FIFO 0 message lost interrupt */
    CAN_INT_FLAG_RFIFO1_NEW                   = CAN_REGIDX_BIT2(IE_REG_OFFSET, 4U, IR_REG_OFFSET, 4U),                /*!< Rx FIFO 1 new message interrupt */
    CAN_INT_FLAG_RFIFO1_WM                    = CAN_REGIDX_BIT2(IE_REG_OFFSET, 5U, IR_REG_OFFSET, 5U),                /*!< Rx FIFO 1 watermark reached interrupt */
    CAN_INT_FLAG_RFIFO1_FULL                  = CAN_REGIDX_BIT2(IE_REG_OFFSET, 6U, IR_REG_OFFSET, 6U),                /*!< Rx FIFO 1 full interrupt */
    CAN_INT_FLAG_RFIFO1_MESLOST               = CAN_REGIDX_BIT2(IE_REG_OFFSET, 7U, IR_REG_OFFSET, 7U),                /*!< Rx FIFO 1 message lost interrupt */
    CAN_INT_FLAG_HIGH_PRI_MES                 = CAN_REGIDX_BIT2(IE_REG_OFFSET, 8U, IR_REG_OFFSET, 8U),                /*!< high priority message interrupt */
    CAN_INT_FLAG_TX_COMPLETE                  = CAN_REGIDX_BIT2(IE_REG_OFFSET, 9U, IR_REG_OFFSET, 9U),                /*!< transmission completed interrupt */
    CAN_INT_FLAG_TX_CANCELLED                 = CAN_REGIDX_BIT2(IE_REG_OFFSET, 10U, IR_REG_OFFSET, 10U),              /*!< transmission cancellation finished interrupt */
    CAN_INT_FLAG_TXFIFO_EMPTY                 = CAN_REGIDX_BIT2(IE_REG_OFFSET, 11U, IR_REG_OFFSET, 11U),              /*!< Tx FIFO empty interrupt */
    CAN_INT_FLAG_TXEVFIFO_NEW                 = CAN_REGIDX_BIT2(IE_REG_OFFSET, 12U, IR_REG_OFFSET, 12U),              /*!< Tx event FIFO new entry interrupt */
    CAN_INT_FLAG_TXEVFIFO_WM                  = CAN_REGIDX_BIT2(IE_REG_OFFSET, 13U, IR_REG_OFFSET, 13U),              /*!< Tx event FIFO watermark reached interrupt */
    CAN_INT_FLAG_TXEVFIFO_FULL                = CAN_REGIDX_BIT2(IE_REG_OFFSET, 14U, IR_REG_OFFSET, 14U),              /*!< Tx event FIFO full interrupt */
    CAN_INT_FLAG_TXEVFIFO_ELELOST             = CAN_REGIDX_BIT2(IE_REG_OFFSET, 15U, IR_REG_OFFSET, 15U),              /*!< Tx event FIFO element lost interrupt */
    CAN_INT_FLAG_TIMESTAMP_WRAP               = CAN_REGIDX_BIT2(IE_REG_OFFSET, 16U, IR_REG_OFFSET, 16U),              /*!< timestamp wraparound interrupt */
    CAN_INT_FLAG_RAM_ACCESS_FAIL              = CAN_REGIDX_BIT2(IE_REG_OFFSET, 17U, IR_REG_OFFSET, 17U),              /*!< message RAM access failure interrupt */
    CAN_INT_FLAG_TIMEOUT                      = CAN_REGIDX_BIT2(IE_REG_OFFSET, 18U, IR_REG_OFFSET, 18U),              /*!< timeout occurred interrupt */
    CAN_INT_FLAG_RXBUFFER_NEW                 = CAN_REGIDX_BIT2(IE_REG_OFFSET, 19U, IR_REG_OFFSET, 19U),              /*!< message stored to dedicated Rx buffer interrupt */
    CAN_INT_FLAG_ERRLOG_OVERFLOW              = CAN_REGIDX_BIT2(IE_REG_OFFSET, 22U, IR_REG_OFFSET, 22U),              /*!< error logging overflow interrupt */
    CAN_INT_FLAG_ERR_PASSIVE_CHANGE           = CAN_REGIDX_BIT2(IE_REG_OFFSET, 23U, IR_REG_OFFSET, 23U),              /*!< error passive interrupt */
    CAN_INT_FLAG_WARNING_CHANGE               = CAN_REGIDX_BIT2(IE_REG_OFFSET, 24U, IR_REG_OFFSET, 24U),              /*!< warning status interrupt */
    CAN_INT_FLAG_BUSOFF_CHANGE                = CAN_REGIDX_BIT2(IE_REG_OFFSET, 25U, IR_REG_OFFSET, 25U),              /*!< bus_off status interrupt */
    CAN_INT_FLAG_WATCHDOG                     = CAN_REGIDX_BIT2(IE_REG_OFFSET, 26U, IR_REG_OFFSET, 26U),              /*!< watchdog interrupt */
    CAN_INT_FLAG_PROT_ERR_ARBITRATION         = CAN_REGIDX_BIT2(IE_REG_OFFSET, 27U, IR_REG_OFFSET, 27U),              /*!< protocol error in arbitration phase interrupt */
    CAN_INT_FLAG_PROT_ERR_DATA                = CAN_REGIDX_BIT2(IE_REG_OFFSET, 28U, IR_REG_OFFSET, 28U),              /*!< protocol error in data phase interrupt */
    /* CAN_M_CAN_TXBTIE interrupts */
    CAN_INT_FLAG_TXBUF0_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 0U, TXBTO_REG_OFFSET, 0U),         /*!< Tx buffer 0 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF1_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 1U, TXBTO_REG_OFFSET, 1U),         /*!< Tx buffer 1 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF2_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 2U, TXBTO_REG_OFFSET, 2U),         /*!< Tx buffer 2 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF3_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 3U, TXBTO_REG_OFFSET, 3U),         /*!< Tx buffer 3 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF4_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 4U, TXBTO_REG_OFFSET, 4U),         /*!< Tx buffer 4 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF5_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 5U, TXBTO_REG_OFFSET, 5U),         /*!< Tx buffer 5 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF6_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 6U, TXBTO_REG_OFFSET, 6U),         /*!< Tx buffer 6 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF7_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 7U, TXBTO_REG_OFFSET, 7U),         /*!< Tx buffer 7 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF8_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 8U, TXBTO_REG_OFFSET, 8U),         /*!< Tx buffer 8 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF9_COMPLETE              = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 9U, TXBTO_REG_OFFSET, 9U),         /*!< Tx buffer 9 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF10_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 10U, TXBTO_REG_OFFSET, 10U),       /*!< Tx buffer 10 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF11_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 11U, TXBTO_REG_OFFSET, 11U),       /*!< Tx buffer 11 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF12_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 12U, TXBTO_REG_OFFSET, 12U),       /*!< Tx buffer 12 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF13_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 13U, TXBTO_REG_OFFSET, 13U),       /*!< Tx buffer 13 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF14_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 14U, TXBTO_REG_OFFSET, 14U),       /*!< Tx buffer 14 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF15_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 15U, TXBTO_REG_OFFSET, 15U),       /*!< Tx buffer 15 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF16_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 16U, TXBTO_REG_OFFSET, 16U),       /*!< Tx buffer 16 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF17_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 17U, TXBTO_REG_OFFSET, 17U),       /*!< Tx buffer 17 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF18_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 18U, TXBTO_REG_OFFSET, 18U),       /*!< Tx buffer 18 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF19_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 19U, TXBTO_REG_OFFSET, 19U),       /*!< Tx buffer 19 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF20_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 20U, TXBTO_REG_OFFSET, 20U),       /*!< Tx buffer 20 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF21_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 21U, TXBTO_REG_OFFSET, 21U),       /*!< Tx buffer 21 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF22_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 22U, TXBTO_REG_OFFSET, 22U),       /*!< Tx buffer 22 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF23_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 23U, TXBTO_REG_OFFSET, 23U),       /*!< Tx buffer 23 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF24_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 24U, TXBTO_REG_OFFSET, 24U),       /*!< Tx buffer 24 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF25_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 25U, TXBTO_REG_OFFSET, 25U),       /*!< Tx buffer 25 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF26_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 26U, TXBTO_REG_OFFSET, 26U),       /*!< Tx buffer 26 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF27_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 27U, TXBTO_REG_OFFSET, 27U),       /*!< Tx buffer 27 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF28_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 28U, TXBTO_REG_OFFSET, 28U),       /*!< Tx buffer 28 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF29_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 29U, TXBTO_REG_OFFSET, 29U),       /*!< Tx buffer 29 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF30_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 30U, TXBTO_REG_OFFSET, 30U),       /*!< Tx buffer 30 transmission interrupt flag */
    CAN_INT_FLAG_TXBUF31_COMPLETE             = CAN_REGIDX_BIT2(TXBTIE_REG_OFFSET, 31U, TXBTO_REG_OFFSET, 31U),       /*!< Tx buffer 31 transmission interrupt flag */
    /* CAN_M_CAN_TXBCIE interrupts */
    CAN_INT_FLAG_TXBUF0_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 0U, TXBCF_REG_OFFSET, 0U),         /*!< Tx buffer 0 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF1_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 1U, TXBCF_REG_OFFSET, 1U),         /*!< Tx buffer 1 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF2_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 2U, TXBCF_REG_OFFSET, 2U),         /*!< Tx buffer 2 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF3_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 3U, TXBCF_REG_OFFSET, 3U),         /*!< Tx buffer 3 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF4_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 4U, TXBCF_REG_OFFSET, 4U),         /*!< Tx buffer 4 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF5_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 5U, TXBCF_REG_OFFSET, 5U),         /*!< Tx buffer 5 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF6_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 6U, TXBCF_REG_OFFSET, 6U),         /*!< Tx buffer 6 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF7_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 7U, TXBCF_REG_OFFSET, 7U),         /*!< Tx buffer 7 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF8_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 8U, TXBCF_REG_OFFSET, 8U),         /*!< Tx buffer 8 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF9_CANCELLED             = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 9U, TXBCF_REG_OFFSET, 9U),         /*!< Tx buffer 9 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF10_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 10U, TXBCF_REG_OFFSET, 10U),       /*!< Tx buffer 10 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF11_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 11U, TXBCF_REG_OFFSET, 11U),       /*!< Tx buffer 11 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF12_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 12U, TXBCF_REG_OFFSET, 12U),       /*!< Tx buffer 12 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF13_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 13U, TXBCF_REG_OFFSET, 13U),       /*!< Tx buffer 13 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF14_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 14U, TXBCF_REG_OFFSET, 14U),       /*!< Tx buffer 14 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF15_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 15U, TXBCF_REG_OFFSET, 15U),       /*!< Tx buffer 15 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF16_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 16U, TXBCF_REG_OFFSET, 16U),       /*!< Tx buffer 16 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF17_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 17U, TXBCF_REG_OFFSET, 17U),       /*!< Tx buffer 17 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF18_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 18U, TXBCF_REG_OFFSET, 18U),       /*!< Tx buffer 18 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF19_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 19U, TXBCF_REG_OFFSET, 19U),       /*!< Tx buffer 19 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF20_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 20U, TXBCF_REG_OFFSET, 20U),       /*!< Tx buffer 20 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF21_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 21U, TXBCF_REG_OFFSET, 21U),       /*!< Tx buffer 21 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF22_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 22U, TXBCF_REG_OFFSET, 22U),       /*!< Tx buffer 22 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF23_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 23U, TXBCF_REG_OFFSET, 23U),       /*!< Tx buffer 23 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF24_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 24U, TXBCF_REG_OFFSET, 24U),       /*!< Tx buffer 24 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF25_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 25U, TXBCF_REG_OFFSET, 25U),       /*!< Tx buffer 25 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF26_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 26U, TXBCF_REG_OFFSET, 26U),       /*!< Tx buffer 26 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF27_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 27U, TXBCF_REG_OFFSET, 27U),       /*!< Tx buffer 27 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF28_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 28U, TXBCF_REG_OFFSET, 28U),       /*!< Tx buffer 28 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF29_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 29U, TXBCF_REG_OFFSET, 29U),       /*!< Tx buffer 29 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF30_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 30U, TXBCF_REG_OFFSET, 30U),       /*!< Tx buffer 30 transmission cancel finished interrupt flag */
    CAN_INT_FLAG_TXBUF31_CANCELLED            = CAN_REGIDX_BIT2(TXBCIE_REG_OFFSET, 31U, TXBCF_REG_OFFSET, 31U),       /*!< Tx buffer 31 transmission cancel finished interrupt flag */
    /* CAN_DMU_DMUIR interrupt flags */
    DMU_INT_FLAG_TX_ELE_NOT_STADDR            = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 0U, DMUIR_REG_OFFSET, 0U),          /*!< TX element not start address interrupt */
    DMU_INT_FLAG_TX_ELE_ILLE_ENQ              = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 1U, DMUIR_REG_OFFSET, 1U),          /*!< TX element illegal enqueueing interrupt */
    DMU_INT_FLAG_TX_ELE_ILLE_ACCSEQ           = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 2U, DMUIR_REG_OFFSET, 2U),          /*!< TX element illegal access sequence interrupt */
    DMU_INT_FLAG_TX_ELE_ILLE_DLC              = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 3U, DMUIR_REG_OFFSET, 3U),          /*!< TX element illegal DLC interrupt */
    DMU_INT_FLAG_TX_ELE_WRITE_AFTTRIG         = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 4U, DMUIR_REG_OFFSET, 4U),          /*!< TX element write after trigger address interrupt */
    DMU_INT_FLAG_TX_ELE_ILLE_READ             = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 5U, DMUIR_REG_OFFSET, 5U),          /*!< TX element illegal read interrupt */
    DMU_INT_FLAG_TX_ELE_ENQ                   = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 6U, DMUIR_REG_OFFSET, 6U),          /*!< TX element enqueued interrupt */
    DMU_INT_FLAG_RX0_ELE_NOT_STADDR           = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 8U, DMUIR_REG_OFFSET, 8U),          /*!< RX0 element not start address interrupt */
    DMU_INT_FLAG_RX0_ELE_ILLE_DEQ             = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 9U, DMUIR_REG_OFFSET, 9U),          /*!< RX0 element illegal dequeueing interrupt */
    DMU_INT_FLAG_RX0_ELE_ILLE_ACCSEQ          = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 10U, DMUIR_REG_OFFSET, 10U),        /*!< RX0 element illegal access sequence interrupt */
    DMU_INT_FLAG_RX0_ELE_ILLE_WRITE           = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 11U, DMUIR_REG_OFFSET, 11U),        /*!< RX0 element illegal write interrupt */
    DMU_INT_FLAG_RX0_ELE_DEQ                  = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 12U, DMUIR_REG_OFFSET, 12U),        /*!< RX0 element dequeued interrupt */
    DMU_INT_FLAG_RX1_ELE_NOT_STADDR           = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 16U, DMUIR_REG_OFFSET, 16U),        /*!< RX1 element not start address interrupt */
    DMU_INT_FLAG_RX1_ELE_ILLE_DEQ             = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 17U, DMUIR_REG_OFFSET, 17U),        /*!< RX1 element illegal dequeueing interrupt */
    DMU_INT_FLAG_RX1_ELE_ILLE_ACCSEQ          = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 18U, DMUIR_REG_OFFSET, 18U),        /*!< RX1 element illegal access sequence interrupt */
    DMU_INT_FLAG_RX1_ELE_ILLE_WRITE           = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 19U, DMUIR_REG_OFFSET, 19U),        /*!< RX1 element illegal write interrupt */
    DMU_INT_FLAG_RX1_ELE_DEQ                  = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 20U, DMUIR_REG_OFFSET, 20U),        /*!< RX1 element dequeued interrupt */
    DMU_INT_FLAG_TXEV_ELE_NOT_STADDR          = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 24U, DMUIR_REG_OFFSET, 24U),        /*!< TX event element not start address interrupt */
    DMU_INT_FLAG_TXEV_ELE_ILLE_DEQ            = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 25U, DMUIR_REG_OFFSET, 25U),        /*!< TX event element illegal dequeueing interrupt */
    DMU_INT_FLAG_TXEV_ELE_ILLE_ACCSEQ         = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 26U, DMUIR_REG_OFFSET, 26U),        /*!< TX event element illegal access sequence interrupt */
    DMU_INT_FLAG_TXEV_ELE_ILLE_WRITE          = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 27U, DMUIR_REG_OFFSET, 27U),        /*!< TX event element illegal write interrupt */
    DMU_INT_FLAG_TXEV_ELE_DEQ                 = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 28U, DMUIR_REG_OFFSET, 28U),        /*!< TX event element dequeued interrupt */
    DMU_INT_FLAG_ILLE_ACC_IN_CONFIG           = CAN_REGIDX_BIT2(DMUIE_REG_OFFSET, 30U, DMUIR_REG_OFFSET, 30U)         /*!< illegal access while in configuration mode interrupt */
} can_dtmcan_interrupt_flag_enum;

/* CAN interrupt flags */
typedef enum {
    /* CAN_M_CAN_IE interrupts */
    CAN_INT_RFIFO0_NEW                        = CAN_REGIDX_BIT(IE_REG_OFFSET, 0U),                 /*!< Rx FIFO 0 new message interrupt */
    CAN_INT_RFIFO0_WM                         = CAN_REGIDX_BIT(IE_REG_OFFSET, 1U),                 /*!< Rx FIFO 0 watermark reached interrupt */
    CAN_INT_RFIFO0_FULL                       = CAN_REGIDX_BIT(IE_REG_OFFSET, 2U),                 /*!< Rx FIFO 0 full interrupt */
    CAN_INT_RFIFO0_MESLOST                    = CAN_REGIDX_BIT(IE_REG_OFFSET, 3U),                 /*!< Rx FIFO 0 message lost interrupt */
    CAN_INT_RFIFO1_NEW                        = CAN_REGIDX_BIT(IE_REG_OFFSET, 4U),                 /*!< Rx FIFO 1 new message interrupt */
    CAN_INT_RFIFO1_WM                         = CAN_REGIDX_BIT(IE_REG_OFFSET, 5U),                 /*!< Rx FIFO 1 watermark reached interrupt */
    CAN_INT_RFIFO1_FULL                       = CAN_REGIDX_BIT(IE_REG_OFFSET, 6U),                 /*!< Rx FIFO 1 full interrupt */
    CAN_INT_RFIFO1_MESLOST                    = CAN_REGIDX_BIT(IE_REG_OFFSET, 7U),                 /*!< Rx FIFO 1 message lost interrupt */
    CAN_INT_HIGH_PRI_MES                      = CAN_REGIDX_BIT(IE_REG_OFFSET, 8U),                 /*!< high priority message interrupt */
    CAN_INT_TX_COMPLETE                       = CAN_REGIDX_BIT(IE_REG_OFFSET, 9U),                 /*!< transmission completed interrupt */
    CAN_INT_TX_CANCELLED                      = CAN_REGIDX_BIT(IE_REG_OFFSET, 10U),                /*!< transmission cancellation finished interrupt */
    CAN_INT_TXFIFO_EMPTY                      = CAN_REGIDX_BIT(IE_REG_OFFSET, 11U),                /*!< Tx FIFO empty interrupt */
    CAN_INT_TXEVFIFO_NEW                      = CAN_REGIDX_BIT(IE_REG_OFFSET, 12U),                /*!< Tx event FIFO new entry interrupt */
    CAN_INT_TXEVFIFO_WM                       = CAN_REGIDX_BIT(IE_REG_OFFSET, 13U),                /*!< Tx event FIFO watermark reached interrupt */
    CAN_INT_TXEVFIFO_FULL                     = CAN_REGIDX_BIT(IE_REG_OFFSET, 14U),                /*!< Tx event FIFO full interrupt */
    CAN_INT_TXEVFIFO_ELELOST                  = CAN_REGIDX_BIT(IE_REG_OFFSET, 15U),                /*!< Tx event FIFO element lost interrupt */
    CAN_INT_TIMESTAMP_WRAP                    = CAN_REGIDX_BIT(IE_REG_OFFSET, 16U),                /*!< timestamp wraparound interrupt */
    CAN_INT_RAM_ACCESS_FAIL                   = CAN_REGIDX_BIT(IE_REG_OFFSET, 17U),                /*!< message RAM access failure interrupt */
    CAN_INT_TIMEOUT                           = CAN_REGIDX_BIT(IE_REG_OFFSET, 18U),                /*!< timeout occurred interrupt */
    CAN_INT_RXBUFFER_NEW                      = CAN_REGIDX_BIT(IE_REG_OFFSET, 19U),                /*!< message stored to dedicated Rx buffer interrupt */
    CAN_INT_ERRLOG_OVERFLOW                   = CAN_REGIDX_BIT(IE_REG_OFFSET, 22U),                /*!< error logging overflow interrupt */
    CAN_INT_ERR_PASSIVE_CHANGE                = CAN_REGIDX_BIT(IE_REG_OFFSET, 23U),                /*!< error passive interrupt */
    CAN_INT_WARNING_CHANGE                    = CAN_REGIDX_BIT(IE_REG_OFFSET, 24U),                /*!< warning status interrupt */
    CAN_INT_BUSOFF_CHANGE                     = CAN_REGIDX_BIT(IE_REG_OFFSET, 25U),                /*!< bus_off status interrupt */
    CAN_INT_WATCHDOG                          = CAN_REGIDX_BIT(IE_REG_OFFSET, 26U),                /*!< watchdog interrupt */
    CAN_INT_PROT_ERR_ARBITRATION              = CAN_REGIDX_BIT(IE_REG_OFFSET, 27U),                /*!< protocol error in arbitration phase interrupt */
    CAN_INT_PROT_ERR_DATA                     = CAN_REGIDX_BIT(IE_REG_OFFSET, 28U),                /*!< protocol error in data phase interrupt */
    /* CAN_M_CAN_TXBTIE interrupts */
    CAN_INT_TXBUF0_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 0U),             /*!< Tx buffer 0 transmission interrupt */
    CAN_INT_TXBUF1_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 1U),             /*!< Tx buffer 1 transmission interrupt */
    CAN_INT_TXBUF2_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 2U),             /*!< Tx buffer 2 transmission interrupt */
    CAN_INT_TXBUF3_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 3U),             /*!< Tx buffer 3 transmission interrupt */
    CAN_INT_TXBUF4_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 4U),             /*!< Tx buffer 4 transmission interrupt */
    CAN_INT_TXBUF5_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 5U),             /*!< Tx buffer 5 transmission interrupt */
    CAN_INT_TXBUF6_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 6U),             /*!< Tx buffer 6 transmission interrupt */
    CAN_INT_TXBUF7_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 7U),             /*!< Tx buffer 7 transmission interrupt */
    CAN_INT_TXBUF8_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 8U),             /*!< Tx buffer 8 transmission interrupt */
    CAN_INT_TXBUF9_COMPLETE                   = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 9U),             /*!< Tx buffer 9 transmission interrupt */
    CAN_INT_TXBUF10_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 10U),            /*!< Tx buffer 10 transmission interrupt */
    CAN_INT_TXBUF11_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 11U),            /*!< Tx buffer 11 transmission interrupt */
    CAN_INT_TXBUF12_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 12U),            /*!< Tx buffer 12 transmission interrupt */
    CAN_INT_TXBUF13_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 13U),            /*!< Tx buffer 13 transmission interrupt */
    CAN_INT_TXBUF14_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 14U),            /*!< Tx buffer 14 transmission interrupt */
    CAN_INT_TXBUF15_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 15U),            /*!< Tx buffer 15 transmission interrupt */
    CAN_INT_TXBUF16_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 16U),            /*!< Tx buffer 16 transmission interrupt */
    CAN_INT_TXBUF17_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 17U),            /*!< Tx buffer 17 transmission interrupt */
    CAN_INT_TXBUF18_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 18U),            /*!< Tx buffer 18 transmission interrupt */
    CAN_INT_TXBUF19_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 19U),            /*!< Tx buffer 19 transmission interrupt */
    CAN_INT_TXBUF20_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 20U),            /*!< Tx buffer 20 transmission interrupt */
    CAN_INT_TXBUF21_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 21U),            /*!< Tx buffer 21 transmission interrupt */
    CAN_INT_TXBUF22_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 22U),            /*!< Tx buffer 22 transmission interrupt */
    CAN_INT_TXBUF23_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 23U),            /*!< Tx buffer 23 transmission interrupt */
    CAN_INT_TXBUF24_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 24U),            /*!< Tx buffer 24 transmission interrupt */
    CAN_INT_TXBUF25_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 25U),            /*!< Tx buffer 25 transmission interrupt */
    CAN_INT_TXBUF26_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 26U),            /*!< Tx buffer 26 transmission interrupt */
    CAN_INT_TXBUF27_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 27U),            /*!< Tx buffer 27 transmission interrupt */
    CAN_INT_TXBUF28_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 28U),            /*!< Tx buffer 28 transmission interrupt */
    CAN_INT_TXBUF29_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 29U),            /*!< Tx buffer 29 transmission interrupt */
    CAN_INT_TXBUF30_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 30U),            /*!< Tx buffer 30 transmission interrupt */
    CAN_INT_TXBUF31_COMPLETE                  = CAN_REGIDX_BIT(TXBTIE_REG_OFFSET, 31U),            /*!< Tx buffer 31 transmission interrupt */
    /* CAN_M_CAN_TXBCIE interrupts */
    CAN_INT_TXBUF0_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 0U),             /*!< Tx buffer 0 transmission cancel finished interrupt */
    CAN_INT_TXBUF1_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 1U),             /*!< Tx buffer 1 transmission cancel finished interrupt */
    CAN_INT_TXBUF2_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 2U),             /*!< Tx buffer 2 transmission cancel finished interrupt */
    CAN_INT_TXBUF3_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 3U),             /*!< Tx buffer 3 transmission cancel finished interrupt */
    CAN_INT_TXBUF4_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 4U),             /*!< Tx buffer 4 transmission cancel finished interrupt */
    CAN_INT_TXBUF5_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 5U),             /*!< Tx buffer 5 transmission cancel finished interrupt */
    CAN_INT_TXBUF6_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 6U),             /*!< Tx buffer 6 transmission cancel finished interrupt */
    CAN_INT_TXBUF7_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 7U),             /*!< Tx buffer 7 transmission cancel finished interrupt */
    CAN_INT_TXBUF8_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 8U),             /*!< Tx buffer 8 transmission cancel finished interrupt */
    CAN_INT_TXBUF9_CANCELLED                  = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 9U),             /*!< Tx buffer 9 transmission cancel finished interrupt */
    CAN_INT_TXBUF10_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 10U),            /*!< Tx buffer 10 transmission cancel finished interrupt */
    CAN_INT_TXBUF11_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 11U),            /*!< Tx buffer 11 transmission cancel finished interrupt */
    CAN_INT_TXBUF12_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 12U),            /*!< Tx buffer 12 transmission cancel finished interrupt */
    CAN_INT_TXBUF13_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 13U),            /*!< Tx buffer 13 transmission cancel finished interrupt */
    CAN_INT_TXBUF14_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 14U),            /*!< Tx buffer 14 transmission cancel finished interrupt */
    CAN_INT_TXBUF15_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 15U),            /*!< Tx buffer 15 transmission cancel finished interrupt */
    CAN_INT_TXBUF16_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 16U),            /*!< Tx buffer 16 transmission cancel finished interrupt */
    CAN_INT_TXBUF17_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 17U),            /*!< Tx buffer 17 transmission cancel finished interrupt */
    CAN_INT_TXBUF18_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 18U),            /*!< Tx buffer 18 transmission cancel finished interrupt */
    CAN_INT_TXBUF19_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 19U),            /*!< Tx buffer 19 transmission cancel finished interrupt */
    CAN_INT_TXBUF20_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 20U),            /*!< Tx buffer 20 transmission cancel finished interrupt */
    CAN_INT_TXBUF21_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 21U),            /*!< Tx buffer 21 transmission cancel finished interrupt */
    CAN_INT_TXBUF22_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 22U),            /*!< Tx buffer 22 transmission cancel finished interrupt */
    CAN_INT_TXBUF23_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 23U),            /*!< Tx buffer 23 transmission cancel finished interrupt */
    CAN_INT_TXBUF24_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 24U),            /*!< Tx buffer 24 transmission cancel finished interrupt */
    CAN_INT_TXBUF25_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 25U),            /*!< Tx buffer 25 transmission cancel finished interrupt */
    CAN_INT_TXBUF26_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 26U),            /*!< Tx buffer 26 transmission cancel finished interrupt */
    CAN_INT_TXBUF27_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 27U),            /*!< Tx buffer 27 transmission cancel finished interrupt */
    CAN_INT_TXBUF28_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 28U),            /*!< Tx buffer 28 transmission cancel finished interrupt */
    CAN_INT_TXBUF29_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 29U),            /*!< Tx buffer 29 transmission cancel finished interrupt */
    CAN_INT_TXBUF30_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 30U),            /*!< Tx buffer 30 transmission cancel finished interrupt */
    CAN_INT_TXBUF31_CANCELLED                 = CAN_REGIDX_BIT(TXBCIE_REG_OFFSET, 31U),            /*!< Tx buffer 31 transmission cancel finished interrupt */
    /* CAN_DMU_DMUIE interrupts */
    DMU_INT_TX_ELE_NOT_STADDR                 = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 0U),              /*!< TX element not start address interrupt */
    DMU_INT_TX_ELE_ILLE_ENQ                   = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 1U),              /*!< TX element illegal enqueueing interrupt */
    DMU_INT_TX_ELE_ILLE_ACCSEQ                = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 2U),              /*!< TX element illegal access sequence interrupt */
    DMU_INT_TX_ELE_ILLE_DLC                   = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 3U),              /*!< TX element illegal DLC interrupt */
    DMU_INT_TX_ELE_WRITE_AFTTRIG              = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 4U),              /*!< TX element write after trigger address interrupt */
    DMU_INT_TX_ELE_ILLE_READ                  = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 5U),              /*!< TX element illegal read interrupt */
    DMU_INT_TX_ELE_ENQ                        = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 6U),              /*!< TX element enqueued interrupt */
    DMU_INT_RX0_ELE_NOT_STADDR                = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 8U),              /*!< RX0 element not start address interrupt */
    DMU_INT_RX0_ELE_ILLE_DEQ                  = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 9U),              /*!< RX0 element illegal dequeueing interrupt */
    DMU_INT_RX0_ELE_ILLE_ACCSEQ               = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 10U),             /*!< RX0 element illegal access sequence interrupt */
    DMU_INT_RX0_ELE_ILLE_WRITE                = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 11U),             /*!< RX0 element illegal write interrupt */
    DMU_INT_RX0_ELE_DEQ                       = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 12U),             /*!< RX0 element dequeued interrupt */
    DMU_INT_RX1_ELE_NOT_STADDR                = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 16U),             /*!< RX1 element not start address interrupt */
    DMU_INT_RX1_ELE_ILLE_DEQ                  = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 17U),             /*!< RX1 element illegal dequeueing interrupt */
    DMU_INT_RX1_ELE_ILLE_ACCSEQ               = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 18U),             /*!< RX1 element illegal access sequence interrupt */
    DMU_INT_RX1_ELE_ILLE_WRITE                = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 19U),             /*!< RX1 element illegal write interrupt */
    DMU_INT_RX1_ELE_DEQ                       = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 20U),             /*!< RX1 element dequeued interrupt */
    DMU_INT_TXEV_ELE_NOT_STADDR               = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 24U),             /*!< TX event element not start address interrupt */
    DMU_INT_TXEV_ELE_ILLE_DEQ                 = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 25U),             /*!< TX event element illegal dequeueing interrupt */
    DMU_INT_TXEV_ELE_ILLE_ACCSEQ              = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 26U),             /*!< TX event element illegal access sequence interrupt */
    DMU_INT_TXEV_ELE_ILLE_WRITE               = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 27U),             /*!< TX event element illegal write interrupt */
    DMU_INT_TXEV_ELE_DEQ                      = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 28U),             /*!< TX event element dequeued interrupt */
    DMU_INT_ILLE_ACC_IN_CONFIG                = CAN_REGIDX_BIT(DMUIE_REG_OFFSET, 30U)              /*!< illegal access while in configuration mode interrupt */
} can_dtmcan_interrupt_enum;

/* parameter types */
typedef enum {
    CAN_INIT_STRUCT                  = 0U,                                                /*!< basic CAN initialization structure */
    CAN_FD_INIT_STRUCT               = 1U,                                                /*!< CAN FD (Flexible Data-rate) initialization structure */
    CAN_FILTER_STRUCT                = 2U,                                                /*!< CAN message filter configuration structure */
    CAN_FILTER_ELEMENT_STRUCT        = 3U,                                                /*!< ID filter element structure */
    CAN_RX_MESSAGE_STRUCT            = 4U,                                                /*!< received message structure */
    CAN_TX_MESSAGE_STRUCT            = 5U,                                                /*!< transmit message structure */
    CAN_TX_BUFFER_STRUCT             = 6U,                                                /*!< transmit buffer configuration structure */
    CAN_TXEV_FIFO_STRUCT             = 7U,                                                /*!< transmit event FIFO structure */
    CAN_TXEV_ELEMENT_STRUCT          = 8U,                                                /*!< transmit event FIFO element structure */
    CAN_RX_FIFO_STRUCT               = 9U,                                                /*!< receive FIFO configuration structure */
    CAN_RX_BUFFER_STRUCT             = 10U,                                               /*!< receive buffer configuration structure */
    CAN_HIGHPRI_MESSAGE_STATE_STRUCT = 11U,                                               /*!< high priority message state structure */
    CAN_ERR_COUNT_STRUCT             = 12U,                                               /*!< error counter structure */
    CAN_DMU_QUEUE_COUNT_STRUCT       = 13U                                                /*!< DMU queue counter structure */
} can_struct_type_enum;

/* structure definitions */
/* CAN message structure */
typedef struct {
    uint32_t id : 29;                                                                     /*!< identifier */
    uint32_t rtr : 1;                                                                     /*!< remote transmission request */
    uint32_t xtd : 1;                                                                     /*!< extended ID or standard ID */
    uint32_t esi : 1;                                                                     /*!< error state indicator */
    uint32_t timestamp : 16;                                                              /*!< timestamp */
    uint32_t dlc : 4;                                                                     /*!< data length code in bytes */
    uint32_t brs : 1;                                                                     /*!< bit rate switch */
    uint32_t fdf : 1;                                                                     /*!< FD format indicator */
    uint32_t reserve1 : 2;                                                                /*!< reserve bits 1 */
    uint32_t filter_index : 7;                                                            /*!< index of matching Rx acceptance filter element */
    uint32_t non_match : 1;                                                               /*!< accepted non-matching frame */
    uint8_t data[64];                                                                     /*!< data */
    uint32_t data_bytes;                                                                  /*!< data bytes */
} can_receive_message_struct;

/* CAN transmit message structure */
typedef struct {
    uint32_t id;                                                                          /*!< identifier */
    can_frame_type_enum rtr;                                                              /*!< remote transmission request */
    can_ff_enum xtd;                                                                      /*!< extended ID or standard ID */
    ControlStatus fdf;                                                                    /*!< FD format indicator */
    ControlStatus brs;                                                                    /*!< bit rate switch */
    uint8_t esi;                                                                          /*!< error state indicator */
    uint8_t ev_fifo_control;                                                              /*!< event FIFO control */
    uint16_t message_marker;                                                              /*!< wide message marker */
    uint8_t data[64];                                                                     /*!< transmit data */
    uint32_t data_bytes;                                                                  /*!< data bytes */
} can_transmit_message_struct;

/* CAN filter parameter structure */
typedef struct {
    uint32_t and_mask_ext_frame;                                                          /*!< extended ID AND mask which is ANDed with the Message ID of a received frame */
    uint8_t non_match_std_frame_accept;                                                   /*!< received messages with 11-bit IDs that do not match any element of the filter list treatment */
    uint8_t non_match_ext_frame_accept;                                                   /*!< received messages with 29-bit IDs that do not match any element of the filter list treatment */
    uint8_t remote_std_frame_accept;                                                      /*!< filter or reject remote frames with 11-bit IDs */
    uint8_t remote_ext_frame_accept;                                                      /*!< filter or reject remote frames with 29-bit IDs */
    uint16_t filter_start_address_std_frame;                                              /*!< filter start address of 11-bit IDs */
    uint16_t filter_start_address_ext_frame;                                              /*!< filter start address of 29-bit IDs */
    uint8_t filter_number_std_frame;                                                      /*!< filter number of 11-bit IDs */
    uint8_t filter_number_ext_frame;                                                      /*!< filter number of 29-bit IDs */
} can_filter_struct;

/* CAN filter element parameter structure */
typedef struct {
    can_filter_type_enum filter_type;                                                     /*!< filter type for 29-bit IDs */
    can_filter_element_enum config;                                                       /*!< filter element configuration for 29-bit IDs */
    uint32_t id1;                                                                         /*!< extended filter ID1 */
    uint32_t id2_or_mask_or_rxbuffercfg;                                                  /*!< extended filter ID2 or ID1 mask or for Rx buffer store configuration */
} can_filter_element_struct;

/* CAN Rx FIFOx parameter structure */
typedef struct {
    uint16_t fifo_operation_mode;                                                         /*!< FIFO operation mode */
    uint16_t fifo_watermark;                                                              /*!< FIFO watermark */
    uint16_t fifo_size;                                                                   /*!< FIFO size */
    uint16_t fifo_start_address;                                                          /*!< start address of Rx FIFOx in message RAM */
    uint16_t fifo_element_size;                                                           /*!< FIFO data field size */
} can_rx_fifo_struct;

/* CAN Rx buffer parameter structure */
typedef struct {
    uint16_t buffer_start_address;                                                        /*!< start address of Rx buffer in message RAM */
    uint16_t buffer_element_size;                                                         /*!< Rx buffer data field size */
} can_rx_buffer_struct;

/* CAN Tx buffer parameter structure */
typedef struct {
    uint16_t tx_buffer_start_address;                                                     /*!< start address of Tx buffer in message RAM */
    uint16_t dedicate_buffer_size;                                                        /*!< number of dedicated transmit buffers */
    uint16_t fifo_or_queue_mode;                                                          /*!< except dedicated transmit buffers, others operate in Tx FIFO or Tx queue mode */
    uint16_t fifo_or_queue_size;                                                          /*!< number of Tx buffers used for Tx FIFO / queue */
    uint16_t tx_buffer_element_size;                                                      /*!< Tx buffer data field size */
} can_tx_buffer_struct;

/* CAN Tx event FIFO parameter structure */
typedef struct {
    uint16_t fifo_watermark;                                                              /*!< FIFO watermark */
    uint16_t fifo_size;                                                                   /*!< FIFO size */
    uint16_t fifo_start_address;                                                          /*!< start address of Tx event FIFO in message RAM */
} can_tx_event_fifo_struct;

/* Tx event FIFO element structure */
typedef struct {
    uint32_t id : 29;                                                                     /*!< identifier */
    uint32_t rtr : 1;                                                                     /*!< remote transmission request */
    uint32_t xtd : 1;                                                                     /*!< extended identifier */
    uint32_t esi : 1;                                                                     /*!< error state indicator */
    uint32_t dlc;                                                                         /*!< data length code */
    uint32_t data_length;                                                                 /*!< data length */
    uint8_t fdf;                                                                          /*!< FD format */
    uint8_t brs;                                                                          /*!< bit rate switch */
    can_tx_ev_type_enum event_type;                                                       /*!< event type */
    uint16_t message_marker;                                                              /*!< message marker */
    uint16_t timestamp;                                                                   /*!< Tx timestamp */
} can_txev_fifo_element_struct;

/* CAN initialize parameters structure */
typedef struct {
    ControlStatus auto_retransmission_enable;                                             /*!< automatic retransmission */
    ControlStatus transmit_pause_enable;                                                  /*!< transmit pause */
    ControlStatus edge_filter_enable;                                                     /*!< edge filter enable*/
    ControlStatus protocol_exception_enable;                                              /*!< protocol exception enable */
    ControlStatus wide_message_enable;                                                    /*!< 16-bit wide message mark enable */
    uint32_t prescaler;                                                                   /*!< baudrate prescaler */
    uint32_t resync_jump_width;                                                           /*!< resynchronization jump width */
    uint32_t time_segment_1;                                                              /*!< time segment 1 */
    uint32_t time_segment_2;                                                              /*!< time segment 2 */
    can_filter_struct *filter_config;                                                     /*!< filter configuration */
    can_rx_fifo_struct *rx_fifo0_config;                                                  /*!< Rx FIFO0 configuration */
    can_rx_fifo_struct *rx_fifo1_config;                                                  /*!< Rx FIFO1 configuration */
    can_rx_buffer_struct *rx_buffer_config;                                               /*!< Rx buffer configuration */
    can_tx_buffer_struct *tx_buffer_config;                                               /*!< Tx buffer configuration */
    can_tx_event_fifo_struct *tx_event_fifo_config;                                       /*!< Tx event FIFO configuration */
} can_parameter_struct;

/* FD initialize parameter structure */
typedef struct {
    ControlStatus iso_can_fd_enable;                                                      /*!< ISO CAN FD protocol enable */
    ControlStatus bitrate_switch_enable;                                                  /*!< data bit rate switch */
    ControlStatus tdc_enable;                                                             /*!< transmitter delay compensation enable */
    uint32_t tdc_offset;                                                                  /*!< transmitter delay compensation offset */
    uint32_t tdc_filter_window;                                                           /*!< transmitter delay compensation filter window length */
    uint32_t prescaler;                                                                   /*!< baudrate prescaler */
    uint32_t resync_jump_width;                                                           /*!< resynchronization jump width */
    uint32_t time_segment_1;                                                              /*!< time segment 1 */
    uint32_t time_segment_2;                                                              /*!< time segment 2 */
} can_fd_parameter_struct;

/* FD protocol state inforamtion structure */
typedef struct {
    FlagStatus protocol_exp;                                                              /*!< protocol exception event occurred */
    FlagStatus fd_message_received;                                                       /*!< message in CAN FD format with FDF flag set has been received */
    FlagStatus brs_of_last_rx;                                                            /*!< last received CAN FD message had its BRS flag set */
    FlagStatus esi_of_last_rx;                                                            /*!< last received CAN FD message had its ESI flag set */
    can_error_enum data_phase_errcode;                                                    /*!< data phase last error code */
} can_fd_protocol_status_struct;

/* CAN protocol state inforamtion structure */
typedef struct {
    FlagStatus bus_off;                                                                   /*!< bus_off status */
    FlagStatus error_warning;                                                             /*!< warning status */
    FlagStatus error_passive;                                                             /*!< error_passive state */
    can_activity_enum node;                                                               /*!< CAN communication state */
    can_error_enum errcode;                                                               /*!< last error code */
} can_protocol_status_struct;

/* CAN high priority message state parameter structure */
typedef struct {
    uint32_t storage_addr;                                                                /*!< message storage address */
    uint32_t match_filter_addr;                                                           /*!< matching filter address */
    int storage_indicator;                                                                /*!< indicator of message storage */
} can_high_prio_message_state_struct;

/* CAN communication error counter structure */
typedef struct {
    uint8_t rx_err_cnt;                                                                   /*!< RX error counter */
    uint8_t tx_err_cnt;                                                                   /*!< TX error counter */
    uint8_t err_logging;                                                                  /*!< CAN error logging */
    FlagStatus rx_err_passive;                                                            /*!< receive error passive flag */
} can_error_cnt_struct;

/* DMU queue counter structure */
typedef struct {
    uint8_t tx_enqueue_cnt;                                                               /*!< TX element enqueueing counter */
    uint8_t rx0_dequeue_cnt;                                                              /*!< RX0 element dequeueing counter */
    uint8_t rx1_dequeue_cnt;                                                              /*!< RX1 element dequeueing counter */
    uint8_t tx_event_dequeue_cnt;                                                         /*!< TX event element dequeueing counter */
} can_dmu_queue_cnt_struct;

/* DMU internal structure */
typedef struct {
    uint32_t txr : 1;                                                                     /*!< TX service request line, indicates a TX request is pending */
    uint32_t rx0r : 1;                                                                    /*!< RX0 service request line, indicates an RX0 FIFO message is pending */
    uint32_t rx1r : 1;                                                                    /*!< RX1 service request line, indicates an RX1 FIFO message is pending */
    uint32_t txer : 1;                                                                    /*!< TX event service request line, indicates a TX event is pending */
    uint32_t reserved1 : 4;                                                               /*!< reserved bits 1 */
    uint32_t tx_fq_put_index_pre : 5;                                                     /*!< TX FIFO/Queue put index previous, indicates the last TX buffer index used */
    uint32_t reserved2 : 2;                                                               /*!< reserved bits 2 */
    uint32_t dmu_en : 1;                                                                  /*!< DMU enable status, indicates whether the DMU is enabled */
    uint32_t reserved3 : 8;                                                               /*!< reserved bits 3 */
    uint32_t dmu_elem_handler_state : 3;                                                  /*!< DMU element handler state, indicates the current state of the element handler */
    uint32_t tx_serve : 1;                                                                /*!< TX service status, indicates the TX service is being handled */
    uint32_t rx0_serve : 1;                                                               /*!< RX0 service status, indicates the RX0 service is being handled */
    uint32_t rx1_serve : 1;                                                               /*!< RX1 service status, indicates the RX1 service is being handled */
    uint32_t txe_serve : 1;                                                               /*!< TX event service status, indicates the TX event service is being handled */
} can_dmu_internal_struct;

/* defines for Tx buffer element size */
#define GET_TXESC_TBDS(regval)         GET_BITS((regval),0,2)                             /*!< get TX buffer element size */
#define TXESC_TBDS(regval)             (BITS(0,2) & ((uint32_t)(regval) << 0U))           /*!< write value to CAN_M_CAN_TXESC_TBDS bit field */
#define CAN_TXBS_8BYTES                ((uint16_t)0x0000U)                                /*!< TX buffer element size: 8 bytes data field */
#define CAN_TXBS_12BYTES               ((uint16_t)0x0001U)                                /*!< TX buffer element size: 12 bytes data field */
#define CAN_TXBS_16BYTES               ((uint16_t)0x0002U)                                /*!< TX buffer element size: 16 bytes data field */
#define CAN_TXBS_20BYTES               ((uint16_t)0x0003U)                                /*!< TX buffer element size: 20 bytes data field */
#define CAN_TXBS_24BYTES               ((uint16_t)0x0004U)                                /*!< TX buffer element size: 24 bytes data field */
#define CAN_TXBS_32BYTES               ((uint16_t)0x0005U)                                /*!< TX buffer element size: 32 bytes data field */
#define CAN_TXBS_48BYTES               ((uint16_t)0x0006U)                                /*!< TX buffer element size: 48 bytes data field */
#define CAN_TXBS_64BYTES               ((uint16_t)0x0007U)                                /*!< TX buffer element size: 64 bytes data field */

/* defines for Rx FIFO element size */
#define CAN_RXFS_8BYTES                ((uint16_t)0x0000U)                                /*!< RX FIFO element size: 8 bytes data field */
#define CAN_RXFS_12BYTES               ((uint16_t)0x0001U)                                /*!< RX FIFO element size: 12 bytes data field */
#define CAN_RXFS_16BYTES               ((uint16_t)0x0002U)                                /*!< RX FIFO element size: 16 bytes data field */
#define CAN_RXFS_20BYTES               ((uint16_t)0x0003U)                                /*!< RX FIFO element size: 20 bytes data field */
#define CAN_RXFS_24BYTES               ((uint16_t)0x0004U)                                /*!< RX FIFO element size: 24 bytes data field */
#define CAN_RXFS_32BYTES               ((uint16_t)0x0005U)                                /*!< RX FIFO element size: 32 bytes data field */
#define CAN_RXFS_48BYTES               ((uint16_t)0x0006U)                                /*!< RX FIFO element size: 48 bytes data field */
#define CAN_RXFS_64BYTES               ((uint16_t)0x0007U)                                /*!< RX FIFO element size: 64 bytes data field */

/* defines for Rx buffer element size */
#define CAN_RXBS_8BYTES                ((uint16_t)0x0000U)                                /*!< RX buffer element size: 8 bytes data field */
#define CAN_RXBS_12BYTES               ((uint16_t)0x0001U)                                /*!< RX buffer element size: 12 bytes data field */
#define CAN_RXBS_16BYTES               ((uint16_t)0x0002U)                                /*!< RX buffer element size: 16 bytes data field */
#define CAN_RXBS_20BYTES               ((uint16_t)0x0003U)                                /*!< RX buffer element size: 20 bytes data field */
#define CAN_RXBS_24BYTES               ((uint16_t)0x0004U)                                /*!< RX buffer element size: 24 bytes data field */
#define CAN_RXBS_32BYTES               ((uint16_t)0x0005U)                                /*!< RX buffer element size: 32 bytes data field */
#define CAN_RXBS_48BYTES               ((uint16_t)0x0006U)                                /*!< RX buffer element size: 48 bytes data field */
#define CAN_RXBS_64BYTES               ((uint16_t)0x0007U)                                /*!< RX buffer element size: 64 bytes data field */

/* defines for non matching frames acceptance */
#define CAN_ACCEPT_INTO_RXFIFO0        ((uint8_t)0x00U)                                   /*!< acceptance non-matching frames into Rx FIFO 0 */
#define CAN_ACCEPT_INTO_RXFIFO1        ((uint8_t)0x01U)                                   /*!< acceptance non-matching frames into Rx FIFO 1 */
#define CAN_REJECT_NON_MATCHING        ((uint8_t)0x02U)                                   /*!< rejection non-matching frames */

/* defines for remote frames acceptance */
#define CAN_REMOTE_FILTER              ((uint8_t)0x00U)                                   /*!< filter remote standard frames */
#define CAN_REMOTE_REJECT              ((uint8_t)0x01U)                                   /*!< reject all remote standard frames */

/* defines for non-matching frame acceptance indicator */
#define CAN_NON_MATCH_FRAME            ((uint32_t)0x00000001U)                            /*!< accepted non-matching frame */
#define CAN_MATCH_FILTER_FRAME         ((uint32_t)0x00000000U)                            /*!< frame matched a filter element */

/* defines for bitrate switch */
#define CAN_BRS_ENABLE                 ((uint32_t)0x00000001U)                            /*!< enable bitrate switch */
#define CAN_BRS_DISABLE                ((uint32_t)0x00000000U)                            /*!< disable bitrate switch */

/* defines for event FIFO control */
#define CAN_TXEVENT_FIFO_STORE         ((uint8_t)0x01U)                                   /*!< store tx event FIFO element */
#define CAN_TXEVENT_FIFO_DISABLE       ((uint8_t)0x00U)                                   /*!< do not store tx event FIFO element */

/* defines for TXFQS.TFQM behavior of Tx FIFO/Queue */
#define CAN_TXFIFO_OPERATION           ((uint32_t)0x00000000U)                            /*!< Tx FIFO operation */
#define CAN_TXQUEUE_OPERATION          CAN_M_CAN_TXBC_TFQM                                /*!< Tx Queue operation */

/* defines for Rx FIFO operation mode */
#define CAN_RXFIFO_BLOCKING            ((uint32_t)0x00000000U)                            /*!< FIFO blocking mode */
#define CAN_RXFIFO_OVERWRITE           CAN_M_CAN_RXFXC_FOM                                /*!< FIFO overwrite mode */

/* CAN_M_CAN_DBTP register */
#define DBTP_DSJW(regval)              (BITS(0,3) & ((uint32_t)(regval) << 0U))           /*!< write value to CAN_M_CAN_DBTP_DSJW bit field */
#define DBTP_DTSEG2(regval)            (BITS(4,7) & ((uint32_t)(regval) << 4U))           /*!< write value to CAN_M_CAN_DBTP_DTSEG2 bit field */
#define DBTP_DTSEG1(regval)            (BITS(8,12) & ((uint32_t)(regval) << 8U))          /*!< write value to CAN_M_CAN_DBTP_DTSEG1 bit field */
#define DBTP_DBRP(regval)              (BITS(16,20) & ((uint32_t)(regval) << 16U))        /*!< write value to CAN_M_CAN_DBTP_DBRP bit field */

/* CAN_M_CAN_TEST register */
#define CAN_TEST_TXBUF_LAST_STARTED    ((uint32_t)0x00000000U)                            /*!< Tx buffer number which started last */
#define CAN_TEST_TXBUF_LAST_PREPARED   ((uint32_t)0x00000001U)                            /*!< Tx buffer number which prepared last */
#define TEST_TX(regval)                (BITS(5,6) & ((uint32_t)(regval) << 5U))           /*!< write value to CAN_M_CAN_TEST_TX bit field */

/* CAN_M_CAN_NBTP register */
#define NBTP_NTSEG2(regval)            (BITS(0,6) & ((uint32_t)(regval) << 0U))           /*!< write value to CAN_M_CAN_NBTP_NTSEG2 bit field */
#define NBTP_NTSEG1(regval)            (BITS(8,15) & ((uint32_t)(regval) << 8U))          /*!< write value to CAN_M_CAN_NBTP_NTSEG1 bit field */
#define NBTP_NBRP(regval)              (BITS(16,24) & ((uint32_t)(regval) << 16U))        /*!< write value to CAN_M_CAN_NBTP_NBRP bit field */
#define NBTP_NSJW(regval)              (BITS(25,31) & ((uint32_t)(regval) << 25U))        /*!< write value to CAN_M_CAN_NBTP_NSJW bit field */

/* CAN_M_CAN_ECR register */
#define GET_ECR_TEC(regval)            GET_BITS((regval),0,7)                             /*!< get transmit error counter */
#define GET_ECR_REC(regval)            GET_BITS((regval),8,14)                            /*!< get receive error counter */
#define GET_ECR_CEL(regval)            GET_BITS((regval),16,23)                           /*!< get CAN error logging */

/* CAN_M_CAN_SIDFC register */
#define SIDFC_FLSSA(regval)            (BITS(2,15) & ((uint32_t)(regval) << 2U))          /*!< write value to CAN_M_CAN_SIDFC_FLSSA bit field */
#define SIDFC_LSS(regval)              (BITS(16,23) & ((uint32_t)(regval) << 16U))        /*!< write value to CAN_M_CAN_SIDFC_LSS bit field */
#define GET_SIDFC_FLSSA(regval)        GET_BITS((regval),2,15)                            /*!< get standard identifier filter start address */
#define GET_SIDFC_LSS(regval)          GET_BITS((regval),16,23)                           /*!< get standard identifier filter number */

/* CAN_M_CAN_XIDFC register */
#define XIDFC_FLESA(regval)            (BITS(2,15) & ((uint32_t)(regval) << 2U))          /*!< write value to CAN_M_CAN_XIDFC_FLESA bit field */
#define XIDFC_LSE(regval)              (BITS(16,22) & ((uint32_t)(regval) << 16U))        /*!< write value to CAN_M_CAN_XIDFC_LSE bit field */
#define GET_XIDFC_FLESA(regval)        GET_BITS((regval),2,15)                            /*!< get extended identifier filter start address */
#define GET_XIDFC_LSE(regval)          GET_BITS((regval),16,22)                           /*!< get extended identifier filter number */

/* CAN_M_CAN_XIDAM register */
#define XIDAM_EIDM(regval)             (BITS(0,28) & ((uint32_t)(regval) << 0U))          /*!< write value to CAN_M_CAN_XIDAM_EIDM bit field */

/* CAN_M_CAN_HPMS register */
#define GET_HPMS_BIDX(regval)          GET_BITS((regval),0,5)                             /*!< get index of Rx FIFO element */
#define GET_HPMS_MSI(regval)           GET_BITS((regval),6,7)                             /*!< get message storage indicator */
#define GET_HPMS_FIDX(regval)          GET_BITS((regval),8,14)                            /*!< get index of matching filter element */

/* CAN_M_CAN_GFC register */
#define GFC_ANFE(regval)               (BITS(2,3) & ((uint32_t)(regval) << 2U))           /*!< write value to CAN_M_CAN_GFC_ANFE bit field */
#define GFC_ANFS(regval)               (BITS(4,5) & ((uint32_t)(regval) << 4U))           /*!< write value to CAN_M_CAN_GFC_ANFS bit field */

/* CAN_M_CAN_RXFxC register */
#define GET_RXFXC_FSA(regval)          GET_BITS((regval),2,15)                            /*!< get Rx FIFO x start address */
#define RXFXC_FSA(regval)              (BITS(2,15) & ((uint32_t)(regval) << 2U))          /*!< write value to CAN_M_CAN_RXFxC_FSA bit field */
#define RXFXC_FS(regval)               (BITS(16,22) & ((uint32_t)(regval) << 16U))        /*!< write value to CAN_M_CAN_RXFxC_FS bit field */
#define RXFXC_FWM(regval)              (BITS(24,30) & ((uint32_t)(regval) << 24U))        /*!< write value to CAN_M_CAN_RXFxC_FWM bit field */

/* CAN_M_CAN_RXFxS register */
#define GET_RXFXS_FXGI(regval)         GET_BITS((regval),8,13)                            /*!< get Rx FIFO x get index */
#define GET_RXFXS_FXPI(regval)         GET_BITS((regval),16,21)                           /*!< get Rx FIFO x put index */

/* CAN_M_CAN_RXESC register */
#define GET_RXESC_F0DS(regval)         GET_BITS((regval),0,2)                             /*!< get Rx FIFO 0 element size */
#define GET_RXESC_F1DS(regval)         GET_BITS((regval),4,6)                             /*!< get Rx FIFO 1 element size */
#define GET_RXESC_RBDS(regval)         GET_BITS((regval),8,10)                             /*!< get Rx buffer element size */
#define RXESC_F0DS(regval)             (BITS(0,2) & ((uint32_t)(regval) << 0U))           /*!< write value to CAN_M_CAN_RXESC_F0DS bit field */
#define RXESC_F1DS(regval)             (BITS(4,6) & ((uint32_t)(regval) << 4U))           /*!< write value to CAN_M_CAN_RXESC_F1DS bit field */
#define RXESC_RBDS(regval)             (BITS(8,10) & ((uint32_t)(regval) << 8U))          /*!< write value to CAN_M_CAN_RXESC_RBDS bit field */

/* CAN_M_CAN_RXBC register */
#define GET_RXBC_RBSA(regval)          GET_BITS((regval),2,15)                             /*!< get Rx buffer start address */
#define RXBC_RBSA(regval)              (BITS(2,15) & ((uint32_t)(regval) << 2U))          /*!< write value to CAN_M_CAN_RXBC_RBSA bit field */

/* CAN_M_CAN_TXBC register */
#define GET_TXBC_TBSA(regval)         GET_BITS((regval),2,15)                             /*!< get Tx buffers start address */
#define GET_TXBC_NDTB(regval)         GET_BITS((regval),16,21)                            /*!< get number of dedicated transmit buffers */
#define TXBC_TBSA(regval)             (BITS(2,15) & ((uint32_t)(regval) << 2U))           /*!< write value to CAN_M_CAN_TXBC_TBSA bit field */
#define TXBC_NDTB(regval)             (BITS(16,21) & ((uint32_t)(regval) << 16U))         /*!< write value to CAN_M_CAN_TXBC_NDTB bit field */
#define TXBC_TFQS(regval)             (BITS(24,29) & ((uint32_t)(regval) << 24U))         /*!< write value to CAN_M_CAN_TXBC_TFQS bit field */

/* CAN_M_CAN_TXEFC register */
#define GET_TXEFC_EFSA(regval)         GET_BITS((regval),2,15)                             /*!< get Tx FIFO element start address */
#define TXEFC_EFSA(regval)            (BITS(2,15) & ((uint32_t)(regval) << 2U))           /*!< write value to CAN_M_CAN_TXEFC_EFSA bit field */
#define TXEFC_EFS(regval)             (BITS(16,21) & ((uint32_t)(regval) << 16U))         /*!< write value to CAN_M_CAN_TXEFC_EFS bit field */
#define TXEFC_EFWM(regval)            (BITS(24,29) & ((uint32_t)(regval) << 24U))         /*!< write value to CAN_M_CAN_TXEFC_EFWM bit field */

/* CAN_M_CAN_TXEFS register */
#define GET_TXEFS_EFGI(regval)        GET_BITS((regval),8,12)                             /*!< get Tx event FIFO get index */
#define GET_TXEFS_EFPI(regval)        GET_BITS((regval),16,20)                            /*!< get Tx event FIFO put index */

/* CAN_M_CAN_TXFQS register */
#define GET_TXFQS_TFGI(regval)        GET_BITS((regval),8,12)                             /*!< get Tx FIFO get index */
#define GET_TXFQS_TFQPI(regval)       GET_BITS((regval),16,20)                            /*!< get Tx FIFO/Queue put index */

/* standard filter element */
#define SFET_SFID2(regval)            (BITS(0,10) & ((uint32_t)(regval) << 0))            /*!< write value to standard filter element table SFID2 bit field */
#define SFET_SFID1(regval)            (BITS(16,26) & ((uint32_t)(regval) << 16))          /*!< write value to standard filter element table SFID1 bit field */
#define SFET_SFEC(regval)             (BITS(27,29) & ((uint32_t)(regval) << 27U))         /*!< write value to standard filter element table SFEC bit field */
#define SFET_SFT(regval)              (BITS(30,31) & ((uint32_t)(regval) << 30U))         /*!< write value to standard filter element table SFT bit field */

/* extended filter element */
#define EFET_EFID1(regval)            (BITS(0,28) & ((uint32_t)(regval) << 0))            /*!< write value to extended filter element table EFID1 bit field */
#define EFET_EFEC(regval)             (BITS(29,31) & ((uint32_t)(regval) << 29U))         /*!< write value to extended filter element table EFEC bit field */
#define EFET_EFID2(regval)            (BITS(0,28) & ((uint32_t)(regval) << 0))            /*!< write value to extended filter element table EFID2 bit field */
#define EFET_EFT(regval)              (BITS(30,31) & ((uint32_t)(regval) << 30U))         /*!< write value to extended filter element table EFT bit field */

/* CAN_M_CAN_PSR register */
#define GET_PSR_TDCV(regval)          GET_BITS((regval),0,6)                              /*!< get transmitter delay compensation value */
#define CAN_M_CAN_PSR_HIGH(dtm_canx)  REG16((dtm_canx) + 0x46U)                           /*!< M_CAN protocol status register high bytes */
#define CAN_M_CAN_PSR_BYTE2(dtm_canx) REG8((dtm_canx) + 0x45U)                            /*!< M_CAN protocol status register byte 2 */

/* CAN_M_CAN_TDCR register */
#define TDCR_TDCF(regval)             (BITS(0,6) & ((uint32_t)(regval) << 0))             /*!< write value to CAN_M_CAN_TDCR_TDCF bit field */
#define TDCR_TDCO(regval)             (BITS(8,14) & ((uint32_t)(regval) << 8U))           /*!< write value to CAN_M_CAN_TDCR_TDCO bit field */

/* CAN_M_CAN_TSCC register */
#define TSCC_TCP(regval)              (BITS(16,19) & ((uint32_t)(regval) << 16))          /*!< write value to CAN_M_CAN_TSCC_TCP bit field */

/* CAN_M_CAN_TOCC register */
#define TOCC_TOP(regval)              (BITS(16,31) & ((uint32_t)(regval) << 16))          /*!< write value to CAN_M_CAN_TOCC_TOP bit field */

/* CAN_DMU_DMUQC register */
#define GET_DMUQC_TXEEC(regval)       GET_BITS((regval),0,7)                              /*!< get TX element enqueueing counter */
#define GET_DMUQC_RX0EDC(regval)      GET_BITS((regval),8,15)                             /*!< get RX0 element dequeueing counter*/
#define GET_DMUQC_RX1EDC(regval)      GET_BITS((regval),16,23)                            /*!< get RX1 element dequeueing counter */
#define GET_DMUQC_TXEEDC(regval)      GET_BITS((regval),24,31)                            /*!< get TX event element dequeueing counter */

/* Tx event FIFO element */
#define E1A_DLC(regval)               (BITS(16,19) & ((uint32_t)(regval) << 16))          /*!< write value to data length code */

/* CAN_NCERRR register */
#define GET_NCERRR_NCERA(regval)      GET_BITS((regval),0,10)                             /*!< get noncorrectable error record address */

/* CAN_CERRRx register */
#define GET_CERRR_CERA(regval)        GET_BITS((regval),0,10)                             /*!< get correctable error record address */

/* defines for timestamp select */
#define CAN_TS_DISABLE                ((uint32_t)0x00000000U)                             /*!< timestamp counter disable */
#define CAN_TS_INTERNAL               ((uint32_t)0x00000001U)                             /*!< timestamp counter enabled, internal count value */

/* defines for timeout operation mode */
#define TOCC_TOS(regval)              (BITS(1,2) & ((uint32_t)(regval) << 1U))            /*!< write value to CAN_M_CAN_TOCC_TOS bit field */

/* DMU element handler state values */
#define DMU_EHS_WAIT4CCE              ((uint32_t)0x00000000U)                             /*!< wait for bit M_CAN:CAN_M_CAN_CCCR.CCE getting zero */
#define DMU_EHS_WAIT4SA               ((uint32_t)0x00000001U)                             /*!< wait for Start Address */
#define DMU_EHS_WAIT4TA               ((uint32_t)0x00000002U)                             /*!< wait for Trigger Address */
#define DMU_EHS_TRANSFER              ((uint32_t)0x00000003U)                             /*!< wait for transfer of Element word */
#define DMU_EHS_ACK2MCAN              ((uint32_t)0x00000004U)                             /*!< acknowledge to M_CAN */
#define DMU_EHS_RECOVERY              ((uint32_t)0x00000005U)                             /*!< exception recovery */

/* CAN interrupt line number definition */
#define CAN_INTR_LINE0                ((uint8_t)0x00U)                                    /*!< CAN interrupt line 0 */
#define CAN_INTR_LINE1                ((uint8_t)0x01U)                                    /*!< CAN interrupt line 1 */

/* function declarations */
/* initialization functions */
/* deinitialize CAN */
void can_deinit(can_dtm_canx_enum dtm_canx);
/* initialize CAN parameter structure with a default value */
void can_struct_para_init(can_struct_type_enum type, void *p_struct);
/* initialize CAN */
ErrStatus can_init(can_dtm_canx_enum dtm_canx, can_parameter_struct *can_parameter);
/* get SRAM initialization state */
FlagStatus can_sram_init_state_get(can_dtm_canx_enum dtm_canx);
/* add message ID filter element */
ErrStatus can_filter_set(can_dtm_canx_enum dtm_canx, can_ff_enum frame_format, uint8_t element_index, can_filter_element_struct *filter);

/* operating mode related functions */
/* enable selected operating mode */
ErrStatus can_operating_mode_enable(can_dtm_canx_enum dtm_canx, can_operating_mode_enum mode);
/* disable selected operating mode */
ErrStatus can_operating_mode_disable(can_dtm_canx_enum dtm_canx, can_operating_mode_enum mode);
/* enable automatic retransmission */
void can_automatic_retransmission_enable(can_dtm_canx_enum dtm_canx);
/* disable automatic retransmission */
void can_automatic_retransmission_disable(can_dtm_canx_enum dtm_canx);

/* test mode related functions */
/* get Tx buffer number from CAN_M_CAN_TEST register */
uint8_t can_test_txbuffer_number_get(uint32_t dtm_canx, uint32_t number_type);
/* configure CAN transmit pin output */
void can_test_transmit_pin_output_config(uint32_t dtm_canx, can_tx_control_enum tx_control);
/* get CAN receive pin state */
FlagStatus can_test_receive_pin_state_get(uint32_t dtm_canx);

/* CAN FD mode related functions */
/* set CAN FD operation mode */
void can_fd_config(can_dtm_canx_enum dtm_canx, can_fd_parameter_struct *can_fd_para_init);
/* disable CAN FD mode */
void can_fd_disable(can_dtm_canx_enum dtm_canx);
/* get transmitter delay compensation value */
uint16_t can_tdc_get(can_dtm_canx_enum dtm_canx);
/* configure transmitter delay compensation */
void can_tdc_config(can_dtm_canx_enum dtm_canx, ControlStatus enable, uint8_t offset, uint8_t filter_window);
/* enable edge filtering during bus integration */
void can_edge_filtering_enable(can_dtm_canx_enum dtm_canx);
/* disable edge filtering during bus integration */
void can_edge_filtering_disable(can_dtm_canx_enum dtm_canx);
/* enable protocol exception handling */
void can_protocol_exception_enable(can_dtm_canx_enum dtm_canx);
/* disable protocol exception handling */
void can_protocol_exception_disable(can_dtm_canx_enum dtm_canx);

/* CAN_SYSREG related configuration functions */
/* enable 'disable modification on read' function for DTM_CAN */
void can_dismodify_on_read_enable(can_dtm_canx_enum dtm_canx);
/* disable 'disable modification on read' function for DTM_CAN */
void can_dismodify_on_read_disable(can_dtm_canx_enum dtm_canx);
/* enable clock stop request for DTM_CAN */
void can_clock_stop_request_enable(can_dtm_canx_enum dtm_canx);
/* disable clock stop request for DTM_CAN */
void can_clock_stop_request_disable(can_dtm_canx_enum dtm_canx);
/* get clock stop acknowledge for DTM_CAN */
FlagStatus can_clock_stop_acknowledge_get(can_dtm_canx_enum dtm_canx);
/* enable DMA request for DTM_CAN */
void can_dma_request_enable(can_dtm_canx_enum dtm_canx);
/* disable DMA request for DTM_CAN */
void can_dma_request_disable(can_dtm_canx_enum dtm_canx);

/* share SRAM related functions */
/* enable CAN_MERRCTL register write access */
void can_merrctl_write_access_enable(can_dtm_canx_enum dtm_canx);
/* disable CAN_MERRCTL register write access */
void can_merrctl_write_access_disable(can_dtm_canx_enum dtm_canx);
/* enable error report and error status update */
ErrStatus can_ecc_enable(can_dtm_canx_enum dtm_canx);
/* disable error report and error status update */
ErrStatus can_ecc_disable(can_dtm_canx_enum dtm_canx);
/* get memory error status */
FlagStatus can_memory_error_status_get(can_dtm_canx_enum dtm_canx, can_memory_error_index_enum index);
/* get memory error address */
uint32_t can_memory_error_address_get(can_dtm_canx_enum dtm_canx, can_memory_error_index_enum index);
/* clear CAN_CERRR0 - CAN_CERRR3, and CAN_NCERRR register record */
void can_memory_error_record_clear(can_dtm_canx_enum dtm_canx);
/* configure the message RAM watchdog counter */
void can_sram_watchdog_config(uint32_t dtm_canx, uint8_t counter);
/* get message RAM watchdog counter value */
uint8_t can_sram_watchdog_counter_get(uint32_t dtm_canx);

/* timeout and timestamp functions */
/* timeout configuration */
void can_timestamp_timeout_prescaler_config(can_dtm_canx_enum dtm_canx, uint16_t prescaler);
/* enable CAN timestamp */
void can_timestamp_enable(can_dtm_canx_enum dtm_canx);
/* disable CAN timestamp */
void can_timestamp_disable(can_dtm_canx_enum dtm_canx);
/* reset CAN timestamp counter value */
void can_timestamp_reset(can_dtm_canx_enum dtm_canx);
/* enable timeout counter */
void can_timeout_enable(can_dtm_canx_enum dtm_canx, can_timeout_mode_enum timeout_mode, uint16_t timeout_period);
/* disable timeout counter */
void can_timeout_disable(can_dtm_canx_enum dtm_canx);
/* get timeout counter value */
uint16_t can_timeout_value_get(can_dtm_canx_enum dtm_canx);
/* restart CAN timeout counter value */
void can_timeout_restart(can_dtm_canx_enum dtm_canx);

/* FIFO functions */
/* get Tx FIFO / Tx queue free level */
uint8_t can_tx_fifo_free_level_get(can_dtm_canx_enum dtm_canx);
/* get Tx FIFO / Tx event FIFO / Rx FIFO get index */
uint8_t can_fifo_get_index_get(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type);
/* get Tx FIFO / Tx queue / Tx event FIFO / Rx FIFO put index */
uint8_t can_fifo_put_index_get(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type);
/* get Tx FIFO / Tx queue / Tx event FIFO / Rx FIFO full state */
FlagStatus can_fifo_full_state_get(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type);
/* get Tx event FIFO / Rx FIFO fill level */
uint8_t can_fifo_fill_level_get(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type);
/* acknowledge Tx event FIFO / Rx FIFO messages */
void can_fifo_acknowledge(can_dtm_canx_enum dtm_canx, can_fifo_type_enum fifo_type);
/* read a Tx event FIFO element */
void can_txev_fifo_read(can_dtm_canx_enum dtm_canx, can_txev_fifo_element_struct *txevent);

/* transmit functions */
/* configure CAN transmission message */
uint8_t can_message_transmit_prepare(can_dtm_canx_enum dtm_canx, can_transmit_message_struct *transmit_message);
/* add an transmission request */
void can_message_transmit_add(can_dtm_canx_enum dtm_canx, uint8_t tx_buffer);
/* cancel an transmission request */
ErrStatus can_message_transmit_cancel(can_dtm_canx_enum dtm_canx, uint8_t tx_buffer);
/* get an transmission status */
FlagStatus can_message_transmit_status_get(can_dtm_canx_enum dtm_canx, uint8_t tx_buffer);
/* get an transmission pending status */
FlagStatus can_message_transmit_pending_status_get(can_dtm_canx_enum dtm_canx, uint8_t tx_buffer);
/* pack CAN transmission message for DMU Tx transmission */
ErrStatus can_dmu_message_transmit_prepare(can_dtm_canx_enum dtm_canx, can_transmit_message_struct *transmit_message, uint32_t dmu_tx[], uint32_t array_size);

/* receive functions */
/* release Rx buffer */
void can_rx_buffer_release(can_dtm_canx_enum dtm_canx, uint8_t buffer_index);
/* get CAN receive message */
void can_message_receive(can_dtm_canx_enum dtm_canx, can_storage_type_enum storage_type, can_receive_message_struct *receive_message);
/* get high priority message state */
can_high_prio_message_state_struct can_high_priority_message_state_get(can_dtm_canx_enum dtm_canx);
/* get high priority CAN message */
can_receive_message_struct can_high_priority_message_receive(can_high_prio_message_state_struct high_message);

/* error status */
/* get CAN FD protocol status information */
can_fd_protocol_status_struct can_fd_protocol_state_info_get(can_dtm_canx_enum dtm_canx);
/* get CAN protocol state information */
can_protocol_status_struct can_protocol_state_info_get(can_dtm_canx_enum dtm_canx);
/* get CAN error counter */
can_error_cnt_struct can_communication_error_counter_get(can_dtm_canx_enum dtm_canx);

/* DMU counter functions */
/* get all DMU queueing counters */
can_dmu_queue_cnt_struct can_dmu_queue_counter_get(can_dtm_canx_enum dtm_canx);
/* reset all DMU counters */
void can_dmu_counter_reset(can_dtm_canx_enum dtm_canx);
/* get DMU internal finite state machine */
can_dmu_internal_struct can_dmu_internal_fsm_get(can_dtm_canx_enum dtm_canx);

/* interrupt configuration */
/* configure CAN interrupt line */
void can_mcan_interrupt_line_config(can_dtm_canx_enum dtm_canx, uint8_t line_number, can_dtmcan_interrupt_enum interrupt);
/* enable CAN interrupt line */
void can_mcan_interrupt_line_enable(can_dtm_canx_enum dtm_canx, uint8_t line_number);
/* disable CAN interrupt line */
void can_mcan_interrupt_line_disable(can_dtm_canx_enum dtm_canx, uint8_t line_number);

/* interrupt & flag */
/* get CAN memory error flag */
FlagStatus can_memerr_flag_get(can_dtm_canx_enum dtm_canx, can_memerr_flag_enum flag);
/* clear CAN memory error flag */
void can_memerr_flag_clear(can_dtm_canx_enum dtm_canx, can_memerr_flag_enum flag);
/* enable or disable memory ecc interrupt */
void can_memerr_interrupt_enable(can_dtm_canx_enum dtm_canx, can_memerr_interrupt_enum interrupt);
/* disable CAN interrupt */
void can_memerr_interrupt_disable(can_dtm_canx_enum dtm_canx, can_memerr_interrupt_enum interrupt);
/* get CAN interrupt flag */
FlagStatus can_memerr_interrupt_flag_get(can_dtm_canx_enum dtm_canx, can_memerr_interrupt_flag_enum int_flag);
/* clear CAN interrupt flag */
void can_memerr_interrupt_flag_clear(can_dtm_canx_enum dtm_canx, can_memerr_interrupt_flag_enum int_flag);

/* get CAN flag */
FlagStatus can_flag_get(can_dtm_canx_enum dtm_canx, can_dtmcan_flag_enum flag);
/* clear CAN flag */
void can_flag_clear(can_dtm_canx_enum dtm_canx, can_dtmcan_flag_enum flag);
/* enable CAN interrupt */
void can_interrupt_enable(can_dtm_canx_enum dtm_canx, can_dtmcan_interrupt_enum interrupt);
/* disable CAN interrupt */
void can_interrupt_disable(can_dtm_canx_enum dtm_canx, can_dtmcan_interrupt_enum interrupt);
/* get CAN interrupt flag */
FlagStatus can_interrupt_flag_get(can_dtm_canx_enum dtm_canx, can_dtmcan_interrupt_flag_enum int_flag);
/* clear CAN interrupt flag */
void can_interrupt_flag_clear(can_dtm_canx_enum dtm_canx, can_dtmcan_interrupt_flag_enum int_flag);

#endif /* GD32A7XX_CAN_H */