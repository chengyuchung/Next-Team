/*!
    \file    gd32a7xx_qspi.h
    \brief   definitions for the QSPI

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

#ifndef GD32A7XX_QSPI_H
#define GD32A7XX_QSPI_H

#include "gd32a7xx.h"

/* QSPI definitions */
#define QSPI                              QSPI_BASE
/* CPDM definitions */
#define CPDM_QSPI                         (QSPI_BASE + (uint32_t)0x400)        /*!< QSPI CPDM base address */

/* registers definitions */
#define QSPI_CTL                          REG32(QSPI + 0x00000000U)            /*!< QSPI control register */
#define QSPI_DCFG                         REG32(QSPI + 0x00000004U)            /*!< QSPI device configuration register */
#define QSPI_STAT                         REG32(QSPI + 0x00000008U)            /*!< QSPI status register */
#define QSPI_STATC                        REG32(QSPI + 0x0000000CU)            /*!< QSPI status clear register */
#define QSPI_DTLEN                        REG32(QSPI + 0x00000010U)            /*!< QSPI data length register */
#define QSPI_TCFG                         REG32(QSPI + 0x00000014U)            /*!< QSPI transfer configuration register */
#define QSPI_ADDR                         REG32(QSPI + 0x00000018U)            /*!< QSPI address register */
#define QSPI_ALTE                         REG32(QSPI + 0x0000001CU)            /*!< QSPI alternate bytes register */
#define QSPI_DATA                         REG32(QSPI + 0x00000020U)            /*!< QSPI data register */
#define QSPI_STATMK                       REG32(QSPI + 0x00000024U)            /*!< QSPI status mask register */
#define QSPI_STATMATCH                    REG32(QSPI + 0x00000028U)            /*!< QSPI status match register */
#define QSPI_INTERVAL                     REG32(QSPI + 0x0000002CU)            /*!< QSPI interval register */
#define QSPI_TMOUT                        REG32(QSPI + 0x00000030U)            /*!< QSPI timeout register */
#define QSPI_FLUSH                        REG32(QSPI + 0x00000034U)            /*!< QSPI FIFO flush register */
#define QSPI_TMR                          REG32(QSPI + 0x00000038U)            /*!< QSPI triple-mode redundancy register */

#define CPDM_CTL                          REG32(CPDM_QSPI + 0x00000000U)       /*!< CPDM control register */
#define CPDM_CFG                          REG32(CPDM_QSPI + 0x00000004U)       /*!< CPDM configuration register */

/* bits definitions */
/* QSPI_CTL */
#define QSPI_CTL_QSPIEN                   BIT(0)                               /*!< enable QSPI */
#define QSPI_CTL_ABORT                    BIT(1)                               /*!< abort request */
#define QSPI_CTL_DMAEN                    BIT(2)                               /*!< enable DMA */
#define QSPI_CTL_TMOUTEN                  BIT(3)                               /*!< timeout counter enable */
#define QSPI_CTL_SSAMPLE                  BIT(4)                               /*!< sample shift */
#define QSPI_CTL_OCKDEN                   BIT(5)                               /*!< output clock delay is enabled when reading data from flash */
#define QSPI_CTL_FTL                      BITS(8,11)                           /*!< fifo threshold level */
#define QSPI_CTL_OCKDV                    BITS(12,15)                          /*!< output clock delay vlaue */
#define QSPI_CTL_TERRIE                   BIT(16)                              /*!< enable transfer error interrupt */
#define QSPI_CTL_TCIE                     BIT(17)                              /*!< enable transfer complete interrupt */
#define QSPI_CTL_FTIE                     BIT(18)                              /*!< enable fifo threshold interrupt */
#define QSPI_CTL_RPMFIE                   BIT(19)                              /*!< enable read polling mode match interrupt */
#define QSPI_CTL_TMOUTIE                  BIT(20)                              /*!< enable timeout interrupt */
#define QSPI_CTL_RPMS                     BIT(22)                              /*!< read polling mode stop */
#define QSPI_CTL_RPMM                     BIT(23)                              /*!< read polling match mode */
#define QSPI_CTL_PSC                      BITS(24,31)                          /*!< prescaler */

/* QSPI_DCFG */
#define QSPI_DCFG_CKMOD                   BIT(0)                               /*!< this bit indicates the sck level when qspi is free */
#define QSPI_DCFG_RXSFT                   BITS(1,3)                            /*!< shift receive step if receive data delay more than 0.5 cycle */
#define QSPI_DCFG_RCKSEL                  BIT(4)                               /*!< receive clock select */
#define QSPI_DCFG_DLYSCEN                 BIT(5)                               /*!< delay scan enable */
#define QSPI_DCFG_CSHC                    BITS(8,10)                           /*!< chip select high cycle */
#define QSPI_DCFG_FMSZ                    BITS(16,20)                          /*!< flash memory size */
#define QSPI_DCFG_CSNCKM                  BIT(30)                              /*!< CSN falls and rises one or two sck cycle select */

/* QSPI_STAT */
#define QSPI_STAT_TERR                    BIT(0)                               /*!< transfer error flag */
#define QSPI_STAT_TC                      BIT(1)                               /*!< transfer complete flag */
#define QSPI_STAT_FT                      BIT(2)                               /*!< fifo threshold flag */
#define QSPI_STAT_RPMF                    BIT(3)                               /*!< read polling match flag */
#define QSPI_STAT_TMOUT                   BIT(4)                               /*!< timeout flag */
#define QSPI_STAT_BUSY                    BIT(5)                               /*!< busy flag */
#define QSPI_STAT_FL                      BITS(8,12)                           /*!< FIFO level */

/* QSPI_STATC */
#define QSPI_STATC_TERRC                  BIT(0)                               /*!< clear transfer error flag */
#define QSPI_STATC_TCC                    BIT(1)                               /*!< clear transfer complete flag */
#define QSPI_STATC_RPMFC                  BIT(3)                               /*!< clear read polling mode match flag */
#define QSPI_STATC_TMOUTC                 BIT(4)                               /*!< clear timeout flag */

/* QSPI_DTLEN */
#define QSPI_DTLEN_DTLEN                  BITS(0,31)                           /*!< data length */

/* QSPI_TCFG */
#define QSPI_TCFG_INSTRUCTION             BITS(0,7)                            /*!< command information to be send to the flash memory */
#define QSPI_TCFG_IMOD                    BITS(8,9)                            /*!< instruction mode */
#define QSPI_TCFG_ADDRMOD                 BITS(10,11)                          /*!< address mode */
#define QSPI_TCFG_ADDRSZ                  BITS(12,13)                          /*!< address size */
#define QSPI_TCFG_ALTEMOD                 BITS(14,15)                          /*!< alternate bytes mode */
#define QSPI_TCFG_ALTESZ                  BITS(16,17)                          /*!< alternate bytes size */
#define QSPI_TCFG_DUMYC                   BITS(18,22)                          /*!< number of dummy cycles */
#define QSPI_TCFG_DATAMOD                 BITS(24,25)                          /*!< data mode */
#define QSPI_TCFG_FMOD                    BITS(26,27)                          /*!< functional mode */
#define QSPI_TCFG_SIOO                    BIT(28)                              /*!< send instruction only once */
#define QSPI_TCFG_DDRHEN                  BIT(30)                              /*!< ddr hold enable */
#define QSPI_TCFG_DDREN                   BIT(31)                              /*!< double data rate mode enable */

/* QSPI_ADDR */
#define QSPI_ADDR_ADDR                    BITS(0,31)                           /*!< address to be send to the external flash memory */

/* QSPI_ALTE */
#define QSPI_ALTE_ALTE                    BITS(0,31)                           /*!< optional data to be send to the flash memory */

/* QSPI_DATA */
#define QSPI_DATA_DATA                    BITS(0,31)                           /*!< data to be transferred through the flash memory */

/* QSPI_STATMK */
#define QSPI_STATMK_MASK                  BITS(0,31)                           /*!< status mask */

/* QSPI_STATMATCH */
#define QSPI_STATMATCH_MATCH              BITS(0,31)                           /*!< status match */

/* QSPI_INTERVAL */
#define QSPI_INTERVAL_INTERVAL            BITS(0,15)                           /*!< interval cycle */

/* QSPI_TMOUT */
#define QSPI_TMOUT_TMOUTCYC               BITS(0,15)                           /*!< timeout cycle */

/* QSPI_FLUSH */
#define QSPI_FLUSH_FLUSH                  BIT(0)                               /*!< used to flush all QSPI interval FIFO */

/* QSPI_TMR */
#define QSPI_TMR_EN0                      BIT(0)                               /*!< QSPI_CTL alarm enable */
#define QSPI_TMR_ST0                      BIT(1)                               /*!< QSPI_CTL alarm status */
#define QSPI_TMR_EN1                      BIT(2)                               /*!< QSPI_DTLEN alarm enable */
#define QSPI_TMR_ST1                      BIT(3)                               /*!< QSPI_DTLEN alarm status */
#define QSPI_TMR_EN2                      BIT(4)                               /*!< QSPI_TCFG alarm enable */
#define QSPI_TMR_ST2                      BIT(5)                               /*!< QSPI_TCFG alarm status */
#define QSPI_TMR_EN3                      BIT(6)                               /*!< QSPI_FLUSH alarm enable */
#define QSPI_TMR_ST3                      BIT(7)                               /*!< QSPI_FLUSH alarm status */

/* CPDM_CTL */
#define CPDM_CTL_CPDMEN            BIT(0)                         /*!< CPDM enable */
#define CPDM_CTL_DLSEN             BIT(1)                         /*!< CPDM delay line sample module enable */

/* CPDM_CFG */
#define CPDM_CFG_CPSEL             BITS(0,3)                      /*!< CPDM Select the phase of the output clock */
#define CPDM_CFG_DLSTCNT           BITS(8,14)                     /*!< CPDM Defines a delay step count for a unit delay UNIT */
#define CPDM_CFG_DLLEN             BITS(16,27)                    /*!< CPDM Delay line length */
#define CPDM_CFG_DLLENF            BIT(31)                        /*!< CPDM Valid mark of delay line length */


/* constants definitions */
/* QSPI init struct definitions */
typedef struct {
    uint32_t prescaler;                                                        /*!< specifies the prescaler factor for generating clock based on the AHB clock.
                                                                                    this parameter can be a number between 0 and 255 */
    uint32_t fifo_threshold;                                                   /*!< specifies the threshold number of bytes in the FIFO (used only in normal mode)
                                                                                    this parameter can be a value between 1 and 16 */
    uint32_t sample_shift;                                                     /*!< specifies the sample shift. the data is sampled 1/2 clock cycle delay later to
                                                                                    take in account external signal delays */
    uint32_t flash_size;                                                       /*!< specifies the flash size. flash_size+1 is effectively the number of address bits
                                                                                    required to address the flash memory. The flash capacity can be up to 4GB
                                                                                    (addressed using 32 bits) in normal mode, but the addressable space in
                                                                                    memory mapped mode is limited to 128MB
                                                                                    this parameter can be a number between 0 and 31 */
    uint32_t cs_high_time;                                                     /*!< specifies the chip select high time. cs_high_time+1 defines the minimum number
                                                                                    of clock cycles which the chip select must remain high between commands */
    uint32_t clock_mode;                                                       /*!< specifies the clock mode. it indicates the level that clock takes between commands */
} qspi_init_struct;

/* QSPI command struct definitions */
typedef struct {
    uint32_t instruction_mode;                                                 /*!< specifies the instruction mode */
    uint32_t instruction;                                                      /*!< specifies the instruction to be sent
                                                                                    this parameter can be a value (8-bit) between 0x00 and 0xFF */
    uint32_t addr_mode;                                                        /*!< specifies the address mode */
    uint32_t addr_size;                                                        /*!< specifies the address size */
    uint32_t addr;                                                             /*!< specifies the address to be sent (Size from 1 to 4 bytes according addr_size)
                                                                                    this parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
    uint32_t altebytes_mode;                                                   /*!< specifies the alternate bytes mode */
    uint32_t altebytes_size;                                                   /*!< specifies the alternate bytes size */
    uint32_t altebytes;                                                        /*!< specifies the alternate Bytes to be sent (size from 1 to 4 bytes according altebytes_size)
                                                                                    this parameter can be a value (32-bits) between 0x0 and 0xFFFFFFFF */
    uint32_t dummycycles;                                                      /*!< specifies the number of dummy cycles.
                                                                                    this parameter can be a number between 0 and 31 */
    uint32_t data_mode;                                                        /*!< specifies the data mode (used for dummy cycles and data phases) */
    uint32_t data_length;                                                      /*!< specifies the number of data to transfer. (this is the number of bytes)
                                                                                    this parameter can be any value between 0 and 0xFFFFFFFF (0 means undefined length
                                                                                    until end of memory) */
    uint32_t sioo_mode;                                                        /*!< specifies the send instruction only once mode */
    uint32_t trans_rate;                                                       /*!< specifies the trans rate is str or dtr */
    uint32_t trans_delay;                                                      /*!< specifies the trans delay is 0 or 1/4 cycle */
} qspi_command_struct;

/* QSPI read polling struct definitions */
typedef struct {
    uint32_t match;                                                            /*!< specifies the value to be compared with the masked status register to get a match.
                                                                                    this parameter can be any value between 0 and 0xFFFFFFFF */
    uint32_t mask;                                                             /*!< specifies the mask to be applied to the status bytes received.
                                                                                    this parameter can be any value between 0 and 0xFFFFFFFF */
    uint32_t interval;                                                         /*!< specifies the number of clock cycles between two read during read polling phases.
                                                                                    this parameter can be any value between 0 and 0xFFFF */
    uint32_t statusbytes_size;                                                 /*!< specifies the size of the status bytes received.
                                                                                    this parameter can be any value between 1 and 4 */
    uint32_t match_mode;                                                       /*!< specifies the method used for determining a match. */
    uint32_t polling_stop;                                                     /*!< specifies if read polling is stopped after a match. */
} qspi_polling_struct;

/* QSPI flag definitions */
#define QSPI_FLAG_BUSY                    QSPI_STAT_BUSY                       /*!< busy flag */
#define QSPI_FLAG_TERR                    QSPI_STAT_TERR                       /*!< transfer error flag */
#define QSPI_FLAG_TC                      QSPI_STAT_TC                         /*!< transfer complete flag */
#define QSPI_FLAG_FT                      QSPI_STAT_FT                         /*!< fifo threshold flag */
#define QSPI_FLAG_RPMF                    QSPI_STAT_RPMF                       /*!< read polling match flag */
#define QSPI_FLAG_TMOUT                   QSPI_STAT_TMOUT                      /*!< timeout flag */

/* QSPI interrupt flag definitions */
#define QSPI_INT_FLAG_TERR                QSPI_STAT_TERR                       /*!< transfer error interrupt flag */
#define QSPI_INT_FLAG_TC                  QSPI_STAT_TC                         /*!< transfer complete interrupt flag */
#define QSPI_INT_FLAG_FT                  QSPI_STAT_FT                         /*!< fifo threshold interrupt flag */
#define QSPI_INT_FLAG_RPMF                QSPI_STAT_RPMF                       /*!< read polling match interrupt flag */
#define QSPI_INT_FLAG_TMOUT               QSPI_STAT_TMOUT                      /*!< timeout interrupt flag */

/* QSPI clock mode */
#define QSPI_CLOCK_MODE_LOW               ((uint32_t)0x00000000U)              /*!< QSPI clock must stay low when CSN is high */
#define QSPI_CLOCK_MODE_HIGH              QSPI_DCFG_CKMOD                      /*!< QSPI clock must stay high when CSN is high */

/* QSPI sample shift(more than 1/2) */
#define DCFG_SSAMPLE(regval)              (BITS(1,3) & ((uint32_t)(regval) << 1))
#define QSPI_SHIFTING_NONE                DCFG_SSAMPLE(0)                      /*!< no shift when sample data */
#define QSPI_SHIFTING_1_CYCLE             DCFG_SSAMPLE(1)                      /*!< 1 sck cycle shift when sample data */
#define QSPI_SHIFTING_2_CYCLE             DCFG_SSAMPLE(2)                      /*!< 2 sck cycle shift when sample data */
#define QSPI_SHIFTING_3_CYCLE             DCFG_SSAMPLE(3)                      /*!< 3 sck cycle shift when sample data */
#define QSPI_SHIFTING_4_CYCLE             DCFG_SSAMPLE(4)                      /*!< 4 sck cycle shift when sample data */
#define QSPI_SHIFTING_5_CYCLE             DCFG_SSAMPLE(5)                      /*!< 5 sck cycle shift when sample data */
#define QSPI_SHIFTING_6_CYCLE             DCFG_SSAMPLE(6)                      /*!< 6 sck cycle shift when sample data */
#define QSPI_SHIFTING_7_CYCLE             DCFG_SSAMPLE(7)                      /*!< 7 sck cycle shift when sample data */

/* QSPI clock mode */
#define QSPI_RECEIVE_CLOCK_SCK            ((uint32_t)0x00000000U)              /*!< QSPI receive clock choose sck */
#define QSPI_RECEIVE_CLOCK_DQS            QSPI_DCFG_RCKSEL                     /*!< QSPI receive clock choose dqs */

/* QSPI sample shift */
#define QSPI_SAMPLE_SHIFTING_NONE         ((uint32_t)0x00000000U)              /*!< no shift when sample data */
#define QSPI_SAMPLE_SHIFTING_HALFCYCLE    QSPI_CTL_SSAMPLE                     /*!< 1/2 sck cycle shift when sample data */

/* QSPI CSN cycle */
#define QSPI_CSN_1_CYCLE                  ((uint32_t)0x00000000U)              /*!< csn falls and rises 1 sck cycle */
#define QSPI_CSN_2_CYCLE                  QSPI_DCFG_CSNCKM                     /*!< csn falls and rises 2 sck cycle  */

/* QSPI chip select high cycle */
#define DCFG_CSHC(regval)                 (BITS(8,10) & ((uint32_t)(regval) << 8))
#define QSPI_CS_HIGH_TIME_1_CYCLE         DCFG_CSHC(0)                         /*!< QSPI CS stays high for at least 1 cycle */
#define QSPI_CS_HIGH_TIME_2_CYCLE         DCFG_CSHC(1)                         /*!< QSPI CS stays high for at least 2 cycles */
#define QSPI_CS_HIGH_TIME_3_CYCLE         DCFG_CSHC(2)                         /*!< QSPI CS stays high for at least 3 cycles */
#define QSPI_CS_HIGH_TIME_4_CYCLE         DCFG_CSHC(3)                         /*!< QSPI CS stays high for at least 4 cycles */
#define QSPI_CS_HIGH_TIME_5_CYCLE         DCFG_CSHC(4)                         /*!< QSPI CS stays high for at least 5 cycles */
#define QSPI_CS_HIGH_TIME_6_CYCLE         DCFG_CSHC(5)                         /*!< QSPI CS stays high for at least 6 cycles */
#define QSPI_CS_HIGH_TIME_7_CYCLE         DCFG_CSHC(6)                         /*!< QSPI CS stays high for at least 7 cycles */
#define QSPI_CS_HIGH_TIME_8_CYCLE         DCFG_CSHC(7)                         /*!< QSPI CS stays high for at least 8 cycles */

/* QSPI instruction mode */
#define TCFG_IMODE(regval)                (BITS(8,9) & ((uint32_t)(regval) << 8))
#define QSPI_INSTRUCTION_NONE             TCFG_IMODE(0)                        /*!< no instruction */
#define QSPI_INSTRUCTION_1_LINE           TCFG_IMODE(1)                        /*!< instruction on a single line */
#define QSPI_INSTRUCTION_2_LINES          TCFG_IMODE(2)                        /*!< instruction on two lines */
#define QSPI_INSTRUCTION_4_LINES          TCFG_IMODE(3)                        /*!< instruction on four lines */

/* QSPI address mode */
#define TCFG_ADDRMOD(regval)              (BITS(10,11) & ((uint32_t)(regval) << 10))
#define QSPI_ADDR_NONE                    TCFG_ADDRMOD(0)                      /*!< no address */
#define QSPI_ADDR_1_LINE                  TCFG_ADDRMOD(1)                      /*!< address on a single line */
#define QSPI_ADDR_2_LINES                 TCFG_ADDRMOD(2)                      /*!< address on two lines */
#define QSPI_ADDR_4_LINES                 TCFG_ADDRMOD(3)                      /*!< address on four lines */

/* QSPI address size */
#define TCFG_ADDRSZ(regval)               (BITS(12,13) & ((uint32_t)(regval) << 12))
#define QSPI_ADDR_8_BITS                  TCFG_ADDRSZ(0)                       /*!< 8 bits address */
#define QSPI_ADDR_16_BITS                 TCFG_ADDRSZ(1)                       /*!< 16 bits address */
#define QSPI_ADDR_24_BITS                 TCFG_ADDRSZ(2)                       /*!< 24 bits address */
#define QSPI_ADDR_32_BITS                 TCFG_ADDRSZ(3)                       /*!< 32 bits address */

/* QSPI alternate bytes mode */
#define TCFG_ALTEMOD(regval)              (BITS(14,15) & ((uint32_t)(regval) << 14))
#define QSPI_ALTE_BYTES_NONE              TCFG_ALTEMOD(0)                      /*!< no alternate bytes */
#define QSPI_ALTE_BYTES_1_LINE            TCFG_ALTEMOD(1)                      /*!< alternate bytes on a single line */
#define QSPI_ALTE_BYTES_2_LINES           TCFG_ALTEMOD(2)                      /*!< alternate bytes on two lines */
#define QSPI_ALTE_BYTES_4_LINES           TCFG_ALTEMOD(3)                      /*!< alternate bytes on four lines */

/* QSPI alternate bytes size */
#define TCFG_ALTESZ(regval)               (BITS(16,17) & ((uint32_t)(regval) << 16))
#define QSPI_ALTE_BYTES_8_BITS            TCFG_ALTESZ(0)                       /*!< 8 bits alternate byte */
#define QSPI_ALTE_BYTES_16_BITS           TCFG_ALTESZ(1)                       /*!< 16 bits alternate bytes */
#define QSPI_ALTE_BYTES_24_BITS           TCFG_ALTESZ(2)                       /*!< 24 bits alternate bytes */
#define QSPI_ALTE_BYTES_32_BITS           TCFG_ALTESZ(3)                       /*!< 32 bits alternate bytes */

/* QSPI data mode */
#define TCFG_DATAMOD(regval)              (BITS(24,25) & ((uint32_t)(regval) << 24))
#define QSPI_DATA_NONE                    TCFG_DATAMOD(0)                      /*!< no data */
#define QSPI_DATA_1_LINE                  TCFG_DATAMOD(1)                      /*!< data on a single line */
#define QSPI_DATA_2_LINES                 TCFG_DATAMOD(2)                      /*!< data on two lines */
#define QSPI_DATA_4_LINES                 TCFG_DATAMOD(3)                      /*!< data on four lines */

/* QSPI functional mode */
#define TCFG_FMOD(regval)                 (BITS(26,27) & ((uint32_t)(regval) << 26))
#define QSPI_NORMAL_WRITE                 TCFG_FMOD(0)                         /*!< normal write mode */
#define QSPI_NORMAL_READ                  TCFG_FMOD(1)                         /*!< normal read mode */
#define QSPI_READ_POLLING                 TCFG_FMOD(2)                         /*!< read polling mode */
#define QSPI_MEMORY_MAPPED                TCFG_FMOD(3)                         /*!< memory mapped mode */

/* QSPI sioo mode */
#define QSPI_SIOO_INST_EVERY_CMD          ((uint32_t)0x00000000U)              /*!< send instruction on every command sequence */
#define QSPI_SIOO_INST_ONLY_FIRST_CMD     QSPI_TCFG_SIOO                       /*!< send instruction only for the first command sequence */

/* QSPI ddr mode */
#define QSPI_SDR_MODE                     ((uint32_t)0x00000000U)              /*!< single data rate */
#define QSPI_DDR_MODE                     QSPI_TCFG_DDREN                      /*!< double data rate */

/* QSPI ddr output hold */
#define QSPI_DDR_HOLD_DISABLE             ((uint32_t)0x00000000U)              /*!< disable ddr output hold */
#define QSPI_DDR_HOLD_ENABLE              QSPI_TCFG_DDRHEN                     /*!< enable ddr output hold */

/* QSPI timeout count */
#define QSPI_TMOUT_DISABLE                ((uint32_t)0x00000000U)              /*!< disable timeout counter */
#define QSPI_TMOUT_ENABLE                 QSPI_CTL_TMOUTEN                     /*!< enable timeout counter */

/* QSPI match mode */
#define QSPI_MATCH_MODE_AND               ((uint32_t)0x00000000U)              /*!< and match mode */
#define QSPI_MATCH_MODE_OR                QSPI_CTL_RPMM                        /*!< or match mode */

/* QSPI read polling stop */
#define QSPI_POLLING_STOP_DISABLE         ((uint32_t)0x00000000U)              /*!< disable read polling mode stop */
#define QSPI_POLLING_STOP_ENABLE          QSPI_CTL_RPMS                        /*!< enable read polling mode stop */

/* QSPI interrupt */
#define QSPI_INT_TC                       QSPI_CTL_TCIE                        /*!< transfer complete interrupt */
#define QSPI_INT_FT                       QSPI_CTL_FTIE                        /*!< FIFO threshold interrupt */
#define QSPI_INT_TERR                     QSPI_CTL_TERRIE                      /*!< transfer error interrupt */
#define QSPI_INT_RPMF                     QSPI_CTL_RPMFIE                      /*!< read polling match interrupt */
#define QSPI_INT_TMOUT                    QSPI_CTL_TMOUTIE                     /*!< timeout interrupt */

/* QSPI prescaler */
#define QSPI_MAX_PRESCALER                    ((uint32_t)0x00000100U)               /*!< Max QSPI prescaler  */

/* QSPI fifo threahold */
#define QSPI_MAX_FIFO_THREAHOLD               ((uint32_t)0x00000010U)               /*!< Max QSPI fifo threahold  */

/* QSPI flash size */
#define QSPI_MAX_FLASH_SIZE                   ((uint32_t)0x0000001CU)               /*!< Max QSPI flash size  */
#define QSPI_MIN_FLASH_SIZE                   ((uint32_t)0x00000000U)               /*!< Min QSPI flash size  */

/* QSPI instruction */
#define QSPI_MAX_INSTRUCTIN                   ((uint32_t)0x000000FFU)               /*!< Max QSPI instruction  */
#define QSPI_MIN_INSTRUCTIN                   ((uint32_t)0x00000000U)               /*!< Min QSPI instruction  */

/* QSPI dumycycles */
#define QSPI_MAX_DUMMYCYCLES                   ((uint32_t)0x0000001FU)               /*!< Max QSPI dumycycles  */
#define QSPI_MIN_DUMMYCYCLES                   ((uint32_t)0x00000000U)               /*!< Min QSPI dumycycles  */

/* QSPI match value */
#define QSPI_MAX_MATCH_VALUE                   ((uint32_t)0xFFFFFFFFU)               /*!< Max QSPI match value  */
#define QSPI_MIN_MATCH_VALUE                   ((uint32_t)0x00000000U)               /*!< Min QSPI match value  */

/* QSPI mask value */
#define QSPI_MAX_MASK_VALUE                   ((uint32_t)0xFFFFFFFFU)               /*!< Max QSPI mask value  */
#define QSPI_MIN_MASK_VALUE                   ((uint32_t)0x00000000U)               /*!< Min QSPI mask value  */

/* QSPI clock cycles */
#define QSPI_MAX_CLK_CYC                      ((uint32_t)0x0000FFFFU)               /*!< Max QSPI clock cycles  */
#define QSPI_MIN_CLK_CYC                      ((uint32_t)0x00000000U)               /*!< Min QSPI clock cycles  */

/* QSPI phase */
#define QSPI_MAX_PHASE                         ((uint32_t)0x0000000CU)               /*!< Max QSPI phase  */
#define QSPI_MIN_PHASE                         ((uint32_t)0x00000000U)               /*!< Min QSPI phase  */

/* QSPI statusbytes size */
#define QSPI_MAX_SATUSBYTES_SIZE               ((uint32_t)0x00000004U)               /*!< Max QSPI statusbytes size  */
#define QSPI_MIN_SATUSBYTES_SIZE               ((uint32_t)0x00000000U)               /*!< Min QSPI statusbytes size  */

/* QSPI timeout */
#define QSPI_MAX_TIMEOUT                       ((uint32_t)0x0000FFFFU)               /*!< Max QSPI timeout  */
#define QSPI_MIN_TIMEOUT                       ((uint32_t)0x00000000U)               /*!< Min QSPI timeout  */

/* CPDM delay step count */
#define CPDM_MAX_DELAY_STEP_COUNT              ((uint32_t)0x0000007FU)               /*!< Max CPDM delay step count  */
#define CPDM_MIN_DELAY_STEP_COUNT              ((uint32_t)0x00000000U)               /*!< Min CPDM delay step count  */

/* CPDM phase */
#define CPDM_MAX_PHASE                         ((uint32_t)0x0000000CU)               /*!< Max Select value of the phase */
#define CPDM_MIN_PHASE                         ((uint32_t)0x00000000U)               /*!< Min Select value of the phase */

/* QSPI interrupt */
#define CLOCK_DELAY_VALUE_HIGH                 ((uint32_t)0x0000000FU)               /*!< Max clock delay value  */
#define CLOCK_DELAY_VALUE_LOW                  ((uint32_t)0x00000000U)               /*!< Min clock delay value */

/* QSPI command config timeout */
#define QSPI_COMMAND_CONFIG_TOMEOUT            ((uint16_t)0x0FFFFU)                  /*!< command config timeout */

/* QSPI data transmit timeout */
#define QSPI_DATA_TRANSMIT_TOMEOUT             ((uint16_t)0x0FFFFU)                  /*!< data transmi timeout */

/* QSPI data receive timeout */
#define QSPI_DATA_RECEIVE_TOMEOUT              ((uint16_t)0x0FFFFU)                  /*!< data receive timeout */

/* QSPI data abort timeout */
#define QSPI_DATA_ABORT_TOMEOUT                ((uint16_t)0x0FFFFU)                  /*!< data abort timeout */

#define QSPI_TMRALM_CTL_FLAG                   QSPI_TMR_ST0                          /*!< QSPI_CTL register triple-mode redundancy alarm flag */
#define QSPI_TMRALM_DTLEN_FLAG                 QSPI_TMR_ST1                          /*!< QSPI_DTLEN register triple-mode redundancy alarm flag */
#define QSPI_TMRALM_TCFG_FLAG                  QSPI_TMR_ST2                          /*!< QSPI_TCFG register triple-mode redundancy alarm flag */
#define QSPI_TMRALM_FLUSH_FLAG                 QSPI_TMR_ST3                          /*!< QSPI_FLUSH register triple-mode redundancy alarm flag */

#define QSPI_TMRALM_CTL                        QSPI_TMR_EN0                          /*!< QSPI_CTL register triple-mode redundancy alarm enable */
#define QSPI_TMRALM_DTLEN                      QSPI_TMR_EN1                          /*!< QSPI_DTLEN register triple-mode redundancy alarm enable */
#define QSPI_TMRALM_TCFG                       QSPI_TMR_EN2                          /*!< QSPI_TCFG register triple-mode redundancy alarm enable */
#define QSPI_TMRALM_FLUSH                      QSPI_TMR_EN3                          /*!< QSPI_FLUSH register triple-mode redundancy alarm enable */

/* output clock phase selection enum definition */
typedef enum {
    CPDM_OUTPUT_PHASE_SELECTION_0 = 0U,                            /*!< output clock phase = input clock */
    CPDM_OUTPUT_PHASE_SELECTION_1,                                 /*!< output clock phase = input clock + 1 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_2,                                 /*!< output clock phase = input clock + 2 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_3,                                 /*!< output clock phase = input clock + 3 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_4,                                 /*!< output clock phase = input clock + 4 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_5,                                 /*!< output clock phase = input clock + 5 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_6,                                 /*!< output clock phase = input clock + 6 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_7,                                 /*!< output clock phase = input clock + 7 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_8,                                 /*!< output clock phase = input clock + 8 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_9,                                 /*!< output clock phase = input clock + 9 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_10,                                /*!< output clock phase = input clock + 10 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_11,                                /*!< output clock phase = input clock + 11 * UNIT delay */
    CPDM_OUTPUT_PHASE_SELECTION_12,                                /*!< output clock phase = input clock + 12 * UNIT delay */
} cpdm_output_phase_enum;

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check QSPI prescaler */
#define NOT_QSPI_PRESCALER(prescaler)                        ((prescaler) > QSPI_MAX_PRESCALER)
/* check QSPI fifo threshold */
#define NOT_QSPI_FIFO_THREAHOLD(fifo_threshold)              ((fifo_threshold) > QSPI_MAX_FIFO_THREAHOLD)
/* check QSPI sample shift */
#define NOT_QSPI_SAMPLE_SHIFT(sample_shift)                  (((sample_shift) != QSPI_SAMPLE_SHIFTING_NONE) && ((sample_shift) != QSPI_SAMPLE_SHIFTING_HALFCYCLE))
/* check QSPI flash size */
#define NOT_QSPI_FLASH_SIZE(flash_size)                      ((flash_size) > QSPI_MAX_FLASH_SIZE)
/* check QSPI cs high time */
#define NOT_QSPI_CS_HIGH_TIME(cs_high_time)                  (((cs_high_time) != QSPI_CS_HIGH_TIME_1_CYCLE) && ((cs_high_time) != QSPI_CS_HIGH_TIME_2_CYCLE) && \
                                                              ((cs_high_time) != QSPI_CS_HIGH_TIME_3_CYCLE) && ((cs_high_time) != QSPI_CS_HIGH_TIME_4_CYCLE) && \
                                                              ((cs_high_time) != QSPI_CS_HIGH_TIME_5_CYCLE) && ((cs_high_time) != QSPI_CS_HIGH_TIME_6_CYCLE) && \
                                                              ((cs_high_time) != QSPI_CS_HIGH_TIME_7_CYCLE) && ((cs_high_time) != QSPI_CS_HIGH_TIME_8_CYCLE))
/* check QSPI clock mode */
#define NOT_QSPI_CLOCK_MODE(clock_mode)                      (((clock_mode) != QSPI_CLOCK_MODE_LOW) && ((clock_mode) != QSPI_CLOCK_MODE_HIGH))
/* check QSPI instruction mode */
#define NOT_QSPI_INSTRUCTIN_MODE(instruction_mode)           (((instruction_mode) != QSPI_INSTRUCTION_NONE) && ((instruction_mode) != QSPI_INSTRUCTION_1_LINE) && \
                                                              ((instruction_mode) != QSPI_INSTRUCTION_2_LINES) && ((instruction_mode) != QSPI_INSTRUCTION_4_LINES))
/* check QSPI instruction */
#define NOT_QSPI_INSTRUCTIN(instruction)                     ((instruction) > QSPI_MAX_INSTRUCTIN)
/* check QSPI addr mode */
#define NOT_QSPI_ADDR_MODE(addr_mode)                        (((addr_mode) != QSPI_ADDR_NONE) && ((addr_mode) != QSPI_ADDR_1_LINE) && \
                                                              ((addr_mode) != QSPI_ADDR_2_LINES) && ((addr_mode) != QSPI_ADDR_4_LINES))
/* check QSPI addr size */
#define NOT_QSPI_ADDR_SIZE(addr_size)                        (((addr_size) != QSPI_ADDR_8_BITS) && ((addr_size) != QSPI_ADDR_16_BITS) && \
                                                              ((addr_size) != QSPI_ADDR_24_BITS) && ((addr_size) != QSPI_ADDR_32_BITS))
/* check QSPI altebytes mode */
#define NOT_QSPI_ALTEBYTES_MODE(altebytes_mode)              (((altebytes_mode) != QSPI_ALTE_BYTES_NONE) && ((altebytes_mode) != QSPI_ALTE_BYTES_1_LINE) && \
                                                              ((altebytes_mode) != QSPI_ALTE_BYTES_2_LINES) && ((altebytes_mode) != QSPI_ALTE_BYTES_4_LINES))
/* check QSPI altebytes size */
#define NOT_QSPI_ALTEBYTES_SIZE(altebytes_size)              (((altebytes_size) != QSPI_ALTE_BYTES_8_BITS) && ((altebytes_size) != QSPI_ALTE_BYTES_16_BITS) && \
                                                              ((altebytes_size) != QSPI_ALTE_BYTES_24_BITS) && ((altebytes_size) != QSPI_ALTE_BYTES_32_BITS))
/* check QSPI dummycycles */
#define NOT_QSPI_DUMMYCYCLES(dummycycles)                    ((dummycycles) > QSPI_MAX_DUMMYCYCLES)
/* check QSPI data mode */
#define NOT_QSPI_DATA_MODE(data_mode)                        (((data_mode) != QSPI_DATA_NONE) && ((data_mode) != QSPI_DATA_1_LINE) && \
                                                              ((data_mode) != QSPI_DATA_2_LINES) && ((data_mode) != QSPI_DATA_4_LINES))
/* check QSPI sioo mode */
#define NOT_QSPI_SIOO_MODE(sioo_mode)                        (((sioo_mode) != QSPI_SIOO_INST_EVERY_CMD) && ((sioo_mode) != QSPI_SIOO_INST_ONLY_FIRST_CMD))
/* check QSPI trans rate */
#define NOT_QSPI_TRANS_RATE(trans_rate)                      (((trans_rate) != QSPI_SDR_MODE) && ((trans_rate) != QSPI_DDR_MODE))
/* check QSPI trans delay */
#define NOT_QSPI_TRANS_DELAY(trans_delay)                    (((trans_delay) != QSPI_DDR_HOLD_DISABLE) && ((trans_delay) != QSPI_DDR_HOLD_ENABLE))
/* check QSPI functional mode */
#define NOT_QSPI_FUNCTIONAL_MODE(functionalmode)             (((functionalmode) != QSPI_NORMAL_WRITE) && ((functionalmode) != QSPI_NORMAL_READ) && \
                                                              ((functionalmode) != QSPI_READ_POLLING) && ((functionalmode) != QSPI_MEMORY_MAPPED))
/* check QSPI phase */
#define NOT_QSPI_PHASE(phase)                                (((phase)< QSPI_MIN_PHASE) || ((phase) > QSPI_MAX_PHASE))
/* check QSPI number of match value */
#define NOT_QSPI_MATCH_VALUE(match)                          ((match) < QSPI_MAX_MATCH_VALUE)
/* check QSPI number of mask value */
#define NOT_QSPI_MASK_VALUE(mask)                            ((mask) < QSPI_MAX_MASK_VALUE)
/* check QSPI number of clock cycles */
#define NOT_QSPI_NUM_CLK_CYC(interval)                       ((interval) > QSPI_MAX_CLK_CYC)
/* check QSPI statusbytes size */
#define NOT_QSPI_SATUSBYTES_SIZE(statusbytes_size)           ((statusbytes_size) > QSPI_MAX_SATUSBYTES_SIZE)
/* check QSPI match mode */
#define NOT_QSPI_MATCH_MODE(match_mode)                      (((match_mode) != QSPI_MATCH_MODE_AND) && ((match_mode) != QSPI_MATCH_MODE_OR))
/* check QSPI polling stop */
#define NOT_QSPI_POLLING_STOP(polling_stop)                  (((polling_stop) != QSPI_POLLING_STOP_DISABLE) && ((polling_stop) != QSPI_POLLING_STOP_ENABLE))
/* check QSPI timeout */
#define NOT_QSPI_TIMEOUT(timeout)                            ((timeout) < QSPI_MAX_TIMEOUT)
/* check QSPI timeout count */
#define NOT_QSPI_TIMEOUT_COUNT(toen)                         (((toen) != QSPI_TMOUT_DISABLE) && ((toen) != QSPI_TMOUT_ENABLE))
/* check QSPI clock delay value */
#define NOT_QSPI_CLOCK_DELAY(clock_delay)                    ((clock_delay) >CLOCK_DELAY_VALUE_HIGH)
/* check QSPI sample shift1 */
#define NOT_QSPI_SAMPLE_SHIFT1(sample_shift1)                (((sample_shift1) != QSPI_SAMPLE_SHIFTING_NONE) && ((sample_shift1) != QSPI_SAMPLE_SHIFTING_HALFCYCLE))
/* check QSPI sample shift2 */
#define NOT_QSPI_SAMPLE_SHIFT2(sample_shift2)                (((sample_shift2) != QSPI_SHIFTING_NONE) && ((sample_shift2) != QSPI_SHIFTING_1_CYCLE) && \
                                                              ((sample_shift2) != QSPI_SHIFTING_2_CYCLE) && ((sample_shift2) != QSPI_SHIFTING_3_CYCLE) && \
                                                              ((sample_shift2) != QSPI_SHIFTING_4_CYCLE) && ((sample_shift2) != QSPI_SHIFTING_5_CYCLE) && \
                                                              ((sample_shift2) != QSPI_SHIFTING_6_CYCLE) && ((sample_shift2) != QSPI_SHIFTING_7_CYCLE))
/* check QSPI receive clock select */
#define NOT_QSPI_RCKSEL(rcksel)                              (((rcksel) != QSPI_RECEIVE_CLOCK_SCK) && ((rcksel) != QSPI_RECEIVE_CLOCK_DQS))
/* check QSPI CSN clock select */
#define NOT_QSPI_CSN_CLOCK(csn_cycle)                        (((csn_cycle) != QSPI_CSN_1_CYCLE) && ((csn_cycle) != QSPI_CSN_2_CYCLE))
/* check QSPI FLAG CLEAR*/
#define NOT_QSPI_FLAG_CLEAR(flag)                             (((flag) != QSPI_FLAG_TERR) && ((flag) != QSPI_FLAG_TC) && \
                                                              ((flag) != QSPI_FLAG_RPMF) && ((flag) != QSPI_FLAG_TMOUT))
/* check QSPI FLAG */
#define NOT_QSPI_FLAG(flag)                                  (((flag) != QSPI_FLAG_BUSY) && ((flag) != QSPI_FLAG_TERR) && \
                                                              ((flag) != QSPI_FLAG_TC) && ((flag) != QSPI_FLAG_FT) && \
                                                              ((flag) != QSPI_FLAG_RPMF) && ((flag) != QSPI_FLAG_TMOUT))
/* check QSPI INTERRUPT FLAG CLEAR*/
#define NOT_QSPI_INTERRUPT_FLAG_CLEAR(int_flag)               (((int_flag) != QSPI_INT_FLAG_TC)&&((int_flag) != QSPI_INT_FLAG_TERR) && \
                                                               ((int_flag) != QSPI_INT_FLAG_RPMF) && ((int_flag) != QSPI_INT_FLAG_TMOUT))
/* check QSPI INTERRUPT  */
#define NOT_QSPI_INTERRUPT(interrupt)                        (((interrupt) != QSPI_INT_TC) && ((interrupt) != QSPI_INT_FT) && \
                                                              ((interrupt) != QSPI_INT_TERR) && ((interrupt) != QSPI_INT_RPMF) && \
                                                              ((interrupt) != QSPI_INT_TMOUT))
/* check QSPI INTERRUPT FLAG */
#define NOT_QSPI_INTERRUPT_FLAG(int_flag)                    (((int_flag) != QSPI_INT_FLAG_TC) && ((int_flag) != QSPI_INT_FLAG_FT) && \
                                                              ((int_flag) != QSPI_INT_FLAG_TERR) && ((int_flag) != QSPI_INT_FLAG_RPMF) && \
                                                              ((int_flag) != QSPI_INT_FLAG_TMOUT))
/* check CPDM delay step count */
#define NOT_CPDM_DELAY_STEP_COUNT(units)                     ((units) > CPDM_MAX_DELAY_STEP_COUNT)
/* check QSPI TMR alarm status */
#define NOT_QSPI_TMRALARM_STATUS(tmr_alarm)                  (((tmr_alarm) != QSPI_TMRALM_CTL_FLAG) && ((tmr_alarm) != QSPI_TMRALM_DTLEN_FLAG) && \
                                                              ((tmr_alarm) != QSPI_TMRALM_TCFG_FLAG) && ((tmr_alarm) != QSPI_TMRALM_FLUSH_FLAG))
/* check QSPI TMR alarm status clear */
#define NOT_QSPI_TMRALARM_STATUS_CLEAR(tmr_alarm)            ((((tmr_alarm) & 0xFFFFFF55U) != 0U) || ((tmr_alarm) == 0U))
/* check QSPI TMR alarm enable */
#define NOT_QSPI_TMRALARM_EN(tmr_alarm)                      ((((tmr_alarm) & 0xFFFFFFAAU) != 0U) || ((tmr_alarm) == 0U))

#endif
/* function declarations */
/* initialization functions */
/* reset QSPI */
void qspi_deinit(void);
/* initialize the parameters of QSPI init struct with the default values */
void qspi_struct_para_init(qspi_init_struct *init_para);
/* initialize the parameters of QSPI command struct with the default values */
void qspi_cmd_struct_para_init(qspi_command_struct *init_para);
/* initialize the parameters of QSPI read polling struct with the default values */
void qspi_polling_struct_para_init(qspi_polling_struct *init_para);
/* initialize QSPI parameter */
void qspi_init(qspi_init_struct *qspi_struct);
/* enable QSPI */
void qspi_enable(void);
/* disable QSPI */
void qspi_disable(void);
/* enable QSPI DMA */
void qspi_dma_enable(void);
/* disable QSPI DMA */
void qspi_dma_disable(void);

/* application function declarations */
/* configure QSPI command parameters */
void qspi_command_config(qspi_command_struct *cmd);
/* configure QSPI read polling mode */
void qspi_polling_config(qspi_command_struct *cmd, qspi_polling_struct *cfg);
/* configure QSPI memory mapped mode */
void qspi_memorymapped_config(qspi_command_struct *cmd, uint16_t timeout, uint32_t toen);
/* QSPI transmit data function */
void qspi_data_transmit(uint8_t *tdata);
/* QSPI receive data function */
void qspi_data_receive(uint8_t *rdata);
/* abort the current transmission */
void qspi_transmission_abort(void);
/* enable output clock delay */
void qspi_output_clock_delay_enable(void);
/* disable output clock delay */
void qspi_output_clock_delay_disable(void);
/* configure output clock delay */
void qspi_output_clock_delay_config(uint32_t ck_delay);
/* config qspi sample shift */
void qspi_sample_shift_config(uint32_t sample_shift1, uint32_t sample_shift2);
/* select qspi receive clock */
void qspi_receive_clock_sel(uint32_t rcksel);
/* enable delay scan */
void qspi_delay_scan_enable(void);
/* disable delay scan */
void qspi_delay_scan_disable(void);
/* select csn falls and rises 1 or 2 sck cycles */
void qspi_csn_edge_cycle(uint32_t csn_cycle);

/* interrupt & flag functions */
/* get QSPI flag status */
FlagStatus qspi_flag_get(uint32_t flag);
/* clear QSPI flag status */
void qspi_flag_clear(uint32_t flag);
/* enable QSPI interrupt */
void qspi_interrupt_enable(uint32_t interrupt);
/* disable QSPI interrupt */
void qspi_interrupt_disable(uint32_t interrupt);
/* get QSPI interrupt flag status */
FlagStatus qspi_interrupt_flag_get(uint32_t int_flag);
/* clear QSPI interrupt flag status */
void qspi_interrupt_flag_clear(uint32_t int_flag);

/* deinitialization and initialization CPDM functions */
/* enable CPDM */
void cpdm_enable(void);
/* disable CPDM */
void cpdm_disable(void);
/* enable CPDM delay line sample module */
void cpdm_delayline_sample_enable(void);
/* disable CPDM delay line sample module */
void cpdm_delayline_sample_disable(void);

/* CPDM output clock configuration functions */
/* select CPDM output clock phase */
void cpdm_output_clock_phase_select(cpdm_output_phase_enum output_clock_phase);
/* configure CPDM delay step */
void cpdm_delay_step_config(uint8_t delay_step);
/* get delay line length valid flag */
FlagStatus cpdm_delayline_length_valid_flag_get(void);
/* get delay line length */
uint16_t cpdm_delayline_length_get(void);

/* CPDM clock output function */
/* configure CPDM clock output */
ErrStatus cpdm_clock_output(cpdm_output_phase_enum output_clock_phase);

/* QSPI triple mode redundancy (TMR) alarm functions */
/* get QSPI TMR alarm status */
FlagStatus qspi_tmr_alarm_status_get(uint32_t tmr_alarm);
/* clear QSPI TMR alarm status */
void qspi_tmr_alarm_status_clear(uint32_t tmr_alarm);
/* enable QSPI TMR alarm */
void qspi_tmr_alarm_enable(uint32_t tmr_alarm);
/* disable QSPI TMR alarm */
void qspi_tmr_alarm_disable(uint32_t tmr_alarm);

#endif /* GD32A7XX_QSPI_H */