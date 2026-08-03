/*!
    \file    gd32a7xx_sent.h
    \brief   definitions for the SENT

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

#ifndef GD32A7XX_SENT_H
#define GD32A7XX_SENT_H

#include "gd32a7xx.h"

/* SENT definitions */
#define SENT                          SENT_BASE

/* registers definitions */
#define SENT_CS                       REG32(SENT+ 0x00000000U)                             /*!< SENT control and status register */
#define SENT_FDIV                     REG32(SENT+ 0x00000004U)                             /*!< SENT fractional divider register */
#define SENT_GINTF                    REG32(SENT+ 0x00000008U)                             /*!< SENT global interrupt flag register */
#define SENT_TS                       REG32(SENT+ 0x0000000CU)                             /*!< SENT time stamp register */
#define SENT_TSPSC                    REG32(SENT+ 0x00000010U)                             /*!< SENT time stamp prescaler register */

#define SENT_CHRDATA(channel)         REG32(((SENT) + 0x100U) + 0x100U * (channel))        /*!< channel x receive data register */
#define SENT_CHPSC(channel)           REG32(((SENT) + 0x104U) + 0x100U * (channel))        /*!< channel x prescaler register */
#define SENT_CHFDIV(channel)          REG32(((SENT) + 0x108U) + 0x100U * (channel))        /*!< channel x fractional divider register */
#define SENT_CHRCTL(channel)          REG32(((SENT) + 0x10CU) + 0x100U * (channel))        /*!< channel x receive control register */
#define SENT_CHRSTAT(channel)         REG32(((SENT) + 0x110U) + 0x100U * (channel))        /*!< channel x receive status register */
#define SENT_CHRSDSTAT(channel)       REG32(((SENT) + 0x114U) + 0x100U * (channel))        /*!< channel x receive serial data and status register */
#define SENT_CHCS(channel)            REG32(((SENT) + 0x118U) + 0x100U * (channel))        /*!< channel x control and status register */
#define SENT_CHSTAT(channel)          REG32(((SENT) + 0x11CU) + 0x100U * (channel))        /*!< channel x status register */
#define SENT_CHSTATCTL(channel)       REG32(((SENT) + 0x120U) + 0x100U * (channel))        /*!< channel x status control register */
#define SENT_CHSTATC(channel)         REG32(((SENT) + 0x124U) + 0x100U * (channel))        /*!< channel x status clear register */
#define SENT_CHINTEN(channel)         REG32(((SENT) + 0x128U) + 0x100U * (channel))        /*!< channel x interrupt enable register */
#define SENT_CHWDGT(channel)          REG32(((SENT) + 0x12CU) + 0x100U * (channel))        /*!< channel x watchdog timer register */
#define SENT_CHTS(channel)            REG32(((SENT) + 0x130U) + 0x100U * (channel))        /*!< channel x receive time stamp register */
#define SENT_CHRDPCFG(channel)        REG32(((SENT) + 0x134U) + 0x100U * (channel))        /*!< channel x receive data position configuration register */

/* bits definitions */
/* SENT_CS */
#define SENT_CS_SENTEN                BIT(0)                              /*!< enable SENT receiver */
#define SENT_CS_SENTF                 BIT(1)                              /*!< SENT status */
#define SENT_CS_SLPEN                 BIT(3)                              /*!< enable SENT sleep mode */

/* SENT_FDIV */
#define SENT_FDIV_STEP                BITS(0,9)                           /*!< step value */
#define SENT_FDIV_DIVMOD              BITS(14,15)                         /*!< fractional divider mode */
#define SENT_FDIV_RVAL                BITS(16,25)                         /*!< result value */

/* SENT_GINTF */
#define SENT_GINTF_CH0GIF             BIT(0)                              /*!< global interrupt flag of channel 0 */
#define SENT_GINTF_CH1GIF             BIT(1)                              /*!< global interrupt flag of channel 1 */
#define SENT_GINTF_CH2GIF             BIT(2)                              /*!< global interrupt flag of channel 2 */
#define SENT_GINTF_CH3GIF             BIT(3)                              /*!< global interrupt flag of channel 3 */
#define SENT_GINTF_CH4GIF             BIT(4)                              /*!< global interrupt flag of channel 4 */
#define SENT_GINTF_CH5GIF             BIT(5)                              /*!< global interrupt flag of channel 5 */

/* SENT_TS */
#define SENT_TS_TS                    BITS(0,31)                          /*!< time stamp */

/* SENT_TSPSC */
#define SENT_TSPSC_TSPSC              BITS(0,19)                          /*!< dividing factor for the time stamp prescaler */

/* SENT_CHxRDATA */
#define SENT_CHXRDATA_DNIB0           BITS(0,3)                           /*!< channel x receive data nibble 0 */
#define SENT_CHXRDATA_DNIB1           BITS(4,7)                           /*!< channel x receive data nibble 1 */
#define SENT_CHXRDATA_DNIB2           BITS(8,11)                          /*!< channel x receive data nibble 2 */
#define SENT_CHXRDATA_DNIB3           BITS(12,15)                         /*!< channel x receive data nibble 3 */
#define SENT_CHXRDATA_DNIB4           BITS(16,19)                         /*!< channel x receive data nibble 4 */
#define SENT_CHXRDATA_DNIB5           BITS(20,23)                         /*!< channel x receive data nibble 5 */
#define SENT_CHXRDATA_DNIB6           BITS(24,27)                         /*!< channel x receive data nibble 6 */
#define SENT_CHXRDATA_DNIB7           BITS(28,31)                         /*!< channel x receive data nibble 7 */

/* SENT_CHxPSC */
#define SENT_CHXPSC_PSC               BITS(0,11)                          /*!< channel x prescaler factor */

/* SENT_CHxFDIV */
#define SENT_CHXFDIV_DIV              BITS(0,15)                          /*!< channel x fractional divider factor */
#define SENT_CHXFDIV_MDIV             BITS(15,31)                         /*!< channel x measured fractional divider factor */

/* SENT_CHxRCTL */
#define SENT_CHXRCTL_CHEN             BIT(0)                              /*!< channel enable */
#define SENT_CHXRCTL_IPP              BIT(1)                              /*!< ignore pause pulse */
#define SENT_CHXRCTL_ALTCRCMEN        BIT(2)                              /*!< alternative CRC mode enable */
#define SENT_CHXRCTL_CRCSNIB          BIT(3)                              /*!< whether status and communication nibble is included in CRC calculation of fast channel (signal) data */
#define SENT_CHXRCTL_SDHWPEN          BIT(4)                              /*!< serial data hardware parse enable */
#define SENT_CHXRCTL_SDCRCEN          BIT(5)                              /*!< serial data CRC enable */
#define SENT_CHXRCTL_CRCEN            BIT(6)                              /*!< CRC enable */
#define SENT_CHXRCTL_CSYNCM           BIT(7)                              /*!< consecutive synchronization check mode */
#define SENT_CHXRCTL_DLEN             BITS(12,15)                         /*!< data length */
#define SENT_CHXRCTL_SMCRCM           BIT(16)                             /*!< serial message CRC mode */
#define SENT_CHXRCTL_SMM              BIT(17)                             /*!< serial message mode */
#define SENT_CHXRCTL_FDERRMEN         BIT(18)                             /*!< frequency drift error mode enable */
#define SENT_CHXRCTL_FDCEN            BIT(20)                             /*!< frequency drift check enable */

/* SENT_CHxRSTAT */
#define SENT_CHXRSTAT_CRC             BITS(0,3)                           /*!< CRC nibble */
#define SENT_CHXRSTAT_CHSTAT          BITS(4,5)                           /*!< channel status */
#define SENT_CHXRSTAT_STACOM          BITS(8,11)                          /*!< status and communication nibble */
#define SENT_CHXRSTAT_FCNT            BITS(16,31)                         /*!< counter of a frame, including pause pulse */

/* SENT_CHxRSDSTAT */
#define SENT_CHXRSDSTAT_SDATA         BITS(0,15)                          /*!< serial data */
#define SENT_CHXRSDSTAT_MSGID         BITS(16,23)                         /*!< message ID */
#define SENT_CHXRSDSTAT_SDCRC         BITS(24,29)                         /*!< serial data CRC value */
#define SENT_CHXRSDSTAT_ESDT          BIT(31)                             /*!< enhanced serial data message type */

/* SENT_CHxCS */
#define SENT_CHXCS_INSEL              BITS(0,1)                           /*!< select input x */
#define SENT_CHXCS_DFTTH              BITS(4,7)                           /*!< digital filter timer threshold */
#define SENT_CHXCS_PPL                BIT(9)                              /*!< pulse polarity */
#define SENT_CHXCS_EGCNTC             BIT(10)                             /*!< edge counter clear */
#define SENT_CHXCS_REGNDF             BIT(12)                             /*!< rising edge noise detect flag */
#define SENT_CHXCS_FEGNDF             BIT(13)                             /*!< falling edge noise detect flag */
#define SENT_CHXCS_REGNDFC            BIT(14)                             /*!< rising edge noise detect flag clear */
#define SENT_CHXCS_FEGNDFC            BIT(15)                             /*!< falling edge noise detect flag clear */
#define SENT_CHXCS_EGCNT              BITS(20,27)                         /*!< edge counter */
#define SENT_CHXCS_RSL                BIT(30)                             /*!< receive signal level */

/* SENT_CHxSTAT */
#define SENT_CHXSTAT_RSF              BIT(0)                              /*!< receive success flag */
#define SENT_CHXSTAT_RBNE             BIT(1)                              /*!< receive buffer not empty flag */
#define SENT_CHXSTAT_RXOVERR          BIT(2)                              /*!< receive buffer overflow error flag */
#define SENT_CHXSTAT_FDEVERR          BIT(5)                              /*!< frequency deviation error flag */
#define SENT_CHXSTAT_FDERR            BIT(6)                              /*!< frequency drift error flag */
#define SENT_CHXSTAT_NNIBERR          BIT(7)                              /*!< number of nibbles error flag */
#define SENT_CHXSTAT_NIBVERR          BIT(8)                              /*!< nibble value error flag */
#define SENT_CHXSTAT_CRCERR           BIT(9)                              /*!< CRC error flag */
#define SENT_CHXSTAT_SSDSTERR         BIT(10)                             /*!< short serial data message start bit error flag */
#define SENT_CHXSTAT_SDRBNE           BIT(11)                             /*!< serial data receive buffer not empty flag */
#define SENT_CHXSTAT_SDCRCERR         BIT(12)                             /*!< serial data CRC error flag */
#define SENT_CHXSTAT_WDERR            BIT(13)                             /*!< watchdog error flag */

/* SENT_CHxSTATCTL */
#define SENT_CHxSTATCTL_RSFS          BIT(0)                              /*!< receive success flag set */
#define SENT_CHxSTATCTL_RBNES         BIT(1)                              /*!< receive buffer not empty flag set */
#define SENT_CHxSTATCTL_RXOVERRS      BIT(2)                              /*!< receive buffer overflow error flag set */
#define SENT_CHxSTATCTL_FDEVERRS      BIT(5)                              /*!< frequency deviation error flag set */
#define SENT_CHxSTATCTL_FDERRS        BIT(6)                              /*!< frequency drift error flag set */
#define SENT_CHxSTATCTL_NNIBERRS      BIT(7)                              /*!< number of nibbles error flag set */
#define SENT_CHxSTATCTL_NIBVERRS      BIT(8)                              /*!< nibble value error flag set */
#define SENT_CHxSTATCTL_CRCERRS       BIT(9)                              /*!< CRC error flag set */
#define SENT_CHxSTATCTL_SSDSTERRS     BIT(10)                             /*!< short serial data message start bit error flag set */
#define SENT_CHxSTATCTL_SDRBNES       BIT(11)                             /*!< serial data receive buffer not empty flag set */
#define SENT_CHxSTATCTL_SDCRCERRS     BIT(12)                             /*!< serial data CRC error flag set */
#define SENT_CHxSTATCTL_WDERRS        BIT(13)                             /*!< watchdog error flag set */

/* SENT_CHxSTATC */
#define SENT_CHXSTATC_RSFC            BIT(0)                              /*!< receive success flag clear */
#define SENT_CHXSTATC_RBNEC           BIT(1)                              /*!< receive buffer not empty flag clear */
#define SENT_CHXSTATC_RXOVERRC        BIT(2)                              /*!< receive buffer overflow error flag clear */
#define SENT_CHXSTATC_FDEVERRC        BIT(5)                              /*!< frequency deviation error flag clear */
#define SENT_CHXSTATC_FDERRC          BIT(6)                              /*!< frequency drift error flag clear */
#define SENT_CHXSTATC_NNIBERRC        BIT(7)                              /*!< number of nibbles error flag clear */
#define SENT_CHXSTATC_NIBVERRC        BIT(8)                              /*!< nibble value error flag clear */
#define SENT_CHXSTATC_CRCERRC         BIT(9)                              /*!< CRC error flag clear */
#define SENT_CHXSTATC_SSDSTERRC       BIT(10)                             /*!< short serial data message start bit error flag clear */
#define SENT_CHXSTATC_SDRBNEC         BIT(11)                             /*!< serial data receive buffer not empty flag clear */
#define SENT_CHXSTATC_SDCRCERRC       BIT(12)                             /*!< serial data CRC error flag clear */
#define SENT_CHXSTATC_WDERRC          BIT(13)                             /*!< watchdog error flag clear */

/* SENT_CHxINTEN */
#define SENT_CHXINTEN_RSFIE           BIT(0)                              /*!< receive success interrupt enable */
#define SENT_CHXINTEN_RBNEIE          BIT(1)                              /*!< receive buffer not empty interrupt enable */
#define SENT_CHXINTEN_RXOVERRIE       BIT(2)                              /*!< receive buffer overflow error interrupt enable */
#define SENT_CHXINTEN_FDEVERRIE       BIT(5)                              /*!< frequency deviation error interrupt enable */
#define SENT_CHXINTEN_FDERRIE         BIT(6)                              /*!< frequency drift error interrupt enable */
#define SENT_CHXINTEN_NNIBERRIE       BIT(7)                              /*!< number of nibbles error interrupt enable */
#define SENT_CHXINTEN_NIBVERRIE       BIT(8)                              /*!< nibble value error interrupt enable */
#define SENT_CHXINTEN_CRCERRIE        BIT(9)                              /*!< CRC error interrupt enable */
#define SENT_CHXINTEN_SSDSTERRIE      BIT(10)                             /*!< short serial data message start bit error interrupt enable */
#define SENT_CHXINTEN_SDRBNEIE        BIT(11)                             /*!< serial data receive buffer not empty interrupt enable */
#define SENT_CHXINTEN_SDCRCERRIE      BIT(12)                             /*!< serial data CRC error interrupt enable */
#define SENT_CHXINTEN_WDERRIE         BIT(13)                             /*!< watchdog error interrupt enable */

/* SENT_CHxWDGT */
#define SENT_CHXWDGT_THOLD            BITS(0,15)                          /*!< watchdog timer counter threshold value for channel x */

/* SENT_CHxTS */
#define SENT_CHXTS_TS                 BITS(0,31)                          /*!< channel x time stamp */

/* SENT_CHxRDPCFG */
#define SENT_CHXRDPCFG_DNIB0P         BITS(0,2)                           /*!< channel x receive data nibble 0 position */
#define SENT_CHXRDPCFG_DNIB1P         BITS(4,6)                           /*!< channel x receive data nibble 1 position */
#define SENT_CHXRDPCFG_DNIB2P         BITS(8,10)                          /*!< channel x receive data nibble 2 position */
#define SENT_CHXRDPCFG_DNIB3P         BITS(12,14)                         /*!< channel x receive data nibble 3 position */
#define SENT_CHXRDPCFG_DNIB4P         BITS(16,18)                         /*!< channel x receive data nibble 4 position */
#define SENT_CHXRDPCFG_DNIB5P         BITS(20,22)                         /*!< channel x receive data nibble 5 position */
#define SENT_CHXRDPCFG_DNIB6P         BITS(24,26)                         /*!< channel x receive data nibble 6 position */
#define SENT_CHXRDPCFG_DNIB7P         BITS(28,30)                         /*!< channel x receive data nibble 7 position */

/* constants definitions */
/* SENT parameter structure */
typedef struct {
    uint32_t freq_drift_check;                                            /*!< specifies the frequency drift check based on frame length is enable or disable */
    uint32_t freq_drift_error_mode;                                       /*!< specifies the frequency drift error mode is enable or disable */
    uint32_t serial_message_mode;                                         /*!< specifies the serial message mode */
    uint32_t serial_message_crc_mode;                                     /*!< specifies the CRC calculation method for serial message */
    uint32_t data_length;                                                 /*!< specifies the data nibble count of a frame */
    uint32_t cons_sync_check_mode;                                        /*!< specifies the consecutive synchronization check mode */
    uint32_t crc;                                                         /*!< specifies the CRC function is enable or disable */
    uint32_t serial_data_crc;                                             /*!< specifies the serial data CRC function is enable or disable */
    uint32_t serial_data_parse;                                           /*!< specifies the serial data hardware parse is enable or disable */
    uint32_t status_nibble_in_crc;                                        /*!< specifies whether status and communication nibble is included in CRC calculation of fast channel (signal) data */
    uint32_t alter_crc_mode;                                              /*!< specifies the alternative 4-bit parallel CRC calculation is enable or disable*/
    uint32_t ignore_pause;                                                /*!< specifies the pause pulse is ignored or not during synchronization */
    uint32_t pulse_polarity;                                              /*!< specifies the pulse polarity is active low or high */
} sent_parameter_struct;

/* SENT frame structure */
typedef struct
{
    uint32_t data;                                                        /*!< the data from last received frame */
    uint32_t timestamp;                                                   /*!< the timestamp of last received frame */
    uint8_t  statusnibble;                                                /*!< the status and communication nibble of last received frame */
    uint8_t  crcnibble;                                                   /*!< the crc nibble of last received frame */
} sent_frame_struct;

/* SENT serial message frame structure */
typedef struct
{
    uint8_t                             crc;                              /*!< the received CRC value */
    uint8_t                             messageid;                        /*!< the received message ID value */
    uint16_t                            serialdata;                       /*!< received serial data value */
    uint8_t                             configbit;                        /*!< the received configuration bit value */
} sent_serialmessage_frame_struct;

/* SENT nibble position enumeration */
typedef enum
{
    SENT_NIBBLE_0 = 0U,                                                   /*!< specifies receive data target nibble pointer to nibble 0  */
    SENT_NIBBLE_1,                                                        /*!< specifies receive data target nibble pointer to nibble 1  */
    SENT_NIBBLE_2,                                                        /*!< specifies receive data target nibble pointer to nibble 2  */
    SENT_NIBBLE_3,                                                        /*!< specifies receive data target nibble pointer to nibble 3  */
    SENT_NIBBLE_4,                                                        /*!< specifies receive data target nibble pointer to nibble 4  */
    SENT_NIBBLE_5,                                                        /*!< specifies receive data target nibble pointer to nibble 5  */
    SENT_NIBBLE_6,                                                        /*!< specifies receive data target nibble pointer to nibble 6  */
    SENT_NIBBLE_7                                                         /*!< specifies receive data target nibble pointer to nibble 7  */
} sent_nibble_position_enum;

/* SENT nibble control structure */
typedef struct
{
    sent_nibble_position_enum           nibble0_position;                 /*!< specifies the received nibble0 control */
    sent_nibble_position_enum           nibble1_position;                 /*!< specifies the received nibble1 control */
    sent_nibble_position_enum           nibble2_position;                 /*!< specifies the received nibble2 control */
    sent_nibble_position_enum           nibble3_position;                 /*!< specifies the received nibble3 control */
    sent_nibble_position_enum           nibble4_position;                 /*!< specifies the received nibble4 control */
    sent_nibble_position_enum           nibble5_position;                 /*!< specifies the received nibble5 control */
    sent_nibble_position_enum           nibble6_position;                 /*!< specifies the received nibble6 control */
    sent_nibble_position_enum           nibble7_position;                 /*!< specifies the received nibble7 control */
} sent_nibble_control_struct;

/* SENT channel select enumeration */
typedef enum 
{
    SENT_CH0 = 0U,                                                        /*!< SENT channel 0 */
    SENT_CH1,                                                             /*!< SENT channel 1 */
    SENT_CH2,                                                             /*!< SENT channel 2 */
    SENT_CH3,                                                             /*!< SENT channel 3 */
    SENT_CH4,                                                             /*!< SENT channel 4 */
    SENT_CH5                                                              /*!< SENT channel 5 */
} sent_channel_enum;  

/* SENT channel input select enumeration */
typedef enum 
{
    SENT_ALTI_INPUT0 = 0U,                                                /*!< SENT input select 0 */
    SENT_ALTI_INPUT1,                                                     /*!< SENT input select 1 */
    SENT_ALTI_INPUT2,                                                     /*!< SENT input select 2 */
    SENT_ALTI_INPUT3                                                      /*!< SENT input select 3 */
} sent_channel_input_enum;

/* define the SENT bit position and its register index offset */
#define SENT_REGIDX_BIT(regidx, bitpos)  (((uint32_t)((regidx) << 6U)) | (uint32_t)(bitpos))
#define SENT_REG_VAL(offset, channelx)   (REG32(SENT + ((0x00000100U * (uint32_t)((channelx) + 0x00000001U)) + ((uint32_t)(((offset) & 0x0000FFFFU) >> 6U)))))
#define SENT_BIT_POS(val)                ((uint32_t)(val) & 0x0000001FU)

/* register offset */
#define SENT_CHSTAT_REG_OFFSET           ((uint32_t)(0x0000001CU))                       /*!< CHSTAT register offset */
#define SENT_CHCS_REG_OFFSET             ((uint32_t)(0x00000018U))                       /*!< CHCS register offset */
#define SENT_CHSTATC_REG_OFFSET          ((uint32_t)(0x00000024U))                       /*!< STATCTL register offset */

/* SENT flags */
typedef enum {
    /* flags in CHSTAT register */
    SENT_FLAG_RSF                = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 0U),          /*!< receive success flag */
    SENT_FLAG_RBNE               = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 1U),          /*!< receive buffer not empty flag */
    SENT_FLAG_RXOVERR            = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 2U),          /*!< receive buffer overflow error flag */
    SENT_FLAG_FDEVERR            = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 5U),          /*!< frequency deviation error flag */
    SENT_FLAG_FDERR              = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 6U),          /*!< frequency drift error flag */
    SENT_FLAG_NNIBERR            = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 7U),          /*!< number of nibbles error flag */
    SENT_FLAG_NIBVERR            = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 8U),          /*!< nibble value error flag */
    SENT_FLAG_CRCERR             = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 9U),          /*!< CRC error flag */
    SENT_FLAG_SSDSTERR           = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 10U),         /*!< short serial data message start bit error flag */
    SENT_FLAG_SDRBNE             = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 11U),         /*!< serial data receive buffer not empty flag */
    SENT_FLAG_SDCRCERR           = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 12U),         /*!< serial data CRC error flag */
    SENT_FLAG_WDERR              = SENT_REGIDX_BIT(SENT_CHSTAT_REG_OFFSET, 13U),         /*!< watchdog error flag */
    /* flags in CHCS register */
    SENT_FLAG_REGNDF             = SENT_REGIDX_BIT(SENT_CHCS_REG_OFFSET, 12U),           /*!< rising edge noise detect flag */
    SENT_FLAG_FEGNDF             = SENT_REGIDX_BIT(SENT_CHCS_REG_OFFSET, 13U),           /*!< falling edge noise detect flag */
    SENT_FLAG_RSL                = SENT_REGIDX_BIT(SENT_CHCS_REG_OFFSET, 30U)            /*!< receive signal level */
} sent_channel_flag_enum;

/* SENT flags clear */
typedef enum {
    /* flags clear in CHSTAT register */
    SENT_FLAG_RSFC               = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 0U),       /*!< receive success flag clear */
    SENT_FLAG_RBNEC              = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 1U),       /*!< receive buffer not empty flag clear */
    SENT_FLAG_RXOVERRC           = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 2U),       /*!< receive buffer overflow error flag clear */
    SENT_FLAG_FDEVERRC           = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 5U),       /*!< frequency deviation error flag clear */
    SENT_FLAG_FDERRC             = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 6U),       /*!< frequency drift error flag clear */
    SENT_FLAG_NNIBERRC           = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 7U),       /*!< number of nibbles error flag clear */
    SENT_FLAG_NIBVERRC           = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 8U),       /*!< nibble value error flag clear */
    SENT_FLAG_CRCERRC            = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 9U),       /*!< CRC error flag clear */
    SENT_FLAG_SSDSTERRC          = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 10U),      /*!< short serial data message start bit error flag clear */
    SENT_FLAG_SDRBNEC            = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 11U),      /*!< serial data receive buffer not empty flag flag clear */
    SENT_FLAG_SDCRCERRC          = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 12U),      /*!< serial data CRC error flag clear */
    SENT_FLAG_WDERRC             = SENT_REGIDX_BIT(SENT_CHSTATC_REG_OFFSET, 13U),      /*!< watchdog error flag clear */
    /* flags clear in CHCS register */
    SENT_FLAG_REGNDFC            = SENT_REGIDX_BIT(SENT_CHCS_REG_OFFSET, 14U),           /*!< rising edge noise detect flag clear */
    SENT_FLAG_FEGNDFC            = SENT_REGIDX_BIT(SENT_CHCS_REG_OFFSET, 15U)            /*!< falling edge noise detect flag clear */
} sent_channel_flag_clear_enum;

/* frequency drift check */
#define SENT_FREQ_DRIFT_CHECK_ENABLE                    SENT_CHXRCTL_FDCEN           /*!< frequency drift check based on frame length is enable */
#define SENT_FREQ_DRIFT_CHECK_DISABLE                   ((uint32_t)0x00000000U)      /*!< frequency drift check based on frame length is disaable */

/* frequency drift error mode */
#define SENT_FREQ_DRIFT_ERROR_ENABLE                    SENT_CHXRCTL_FDERRMEN        /*!< frequency drift error mode is enable */
#define SENT_FREQ_DRIFT_ERROR_DISABLE                   ((uint32_t)0x00000000U)      /*!< frequency drift error mode is disable */

/* serial message mode */
#define SENT_ENHANCED_SERIAL_MESSAGE                    SENT_CHXRCTL_SMM             /*!< enhanced serial message */
#define SENT_SHORT_SERIAL_MESSAGE                       ((uint32_t)0x00000000U)      /*!< short serial message */

/* serial message CRC mode */
#define SENT_SERIAL_MESSAGE_AUGMENTATION_CRC            SENT_CHXRCTL_SMCRCM          /*!< CRC mode is augmentation mode */
#define SENT_SERIAL_MESSAGE_NORMAL_CRC                  ((uint32_t)0x00000000U)      /*!< CRC mode is normal mode */

/* data length */
#define CHXRCTL_DATALEN(regval)                         (BITS(12,15) & ((uint32_t)(regval) << 12U))
#define SENT_DATALEN_0_NIBBLE                           CHXRCTL_DATALEN(0)           /*!< 0 data nibble */
#define SENT_DATALEN_1_NIBBLE                           CHXRCTL_DATALEN(1)           /*!< 1 data nibble */
#define SENT_DATALEN_2_NIBBLE                           CHXRCTL_DATALEN(2)           /*!< 2 data nibble */
#define SENT_DATALEN_3_NIBBLE                           CHXRCTL_DATALEN(3)           /*!< 3 data nibble */
#define SENT_DATALEN_4_NIBBLE                           CHXRCTL_DATALEN(4)           /*!< 4 data nibble */
#define SENT_DATALEN_5_NIBBLE                           CHXRCTL_DATALEN(5)           /*!< 5 data nibble */
#define SENT_DATALEN_6_NIBBLE                           CHXRCTL_DATALEN(6)           /*!< 6 data nibble */
#define SENT_DATALEN_7_NIBBLE                           CHXRCTL_DATALEN(7)           /*!< 7 data nibble */
#define SENT_DATALEN_8_NIBBLE                           CHXRCTL_DATALEN(8)           /*!< 8 data nibble */

/* consecutive synchronization check mode */
#define SENT_CONS_SYNC_CHECK_AFTER                      SENT_CHXRCTL_CSYNCM          /*!< check the synchronization/calibration pulse deviation between the current frame and the next frame */
#define SENT_CONS_SYNC_CHECK_BEFORE                     ((uint32_t)0x00000000U)      /*!< check the synchronization/calibration pulse deviation between the current frame and the previous frame */

/* CRC enable */
#define SENT_CRC_ENABLE                                 SENT_CHXRCTL_CRCEN           /*!< enable CRC function */
#define SENT_CRC_DISABLE                                ((uint32_t)0x00000000U)      /*!< disable CRC function */

/* serial data CRC enable */
#define SENT_SERIAL_DATA_CRC_ENABLE                     SENT_CHXRCTL_SDCRCEN         /*!< enable serial data CRC function */
#define SENT_SERIAL_DATA_CRC_DISABLE                    ((uint32_t)0x00000000U)      /*!< disable serial data CRC function */

/* serial data parse mode */
#define SENT_SERIAL_DATA_HARDWARE_PARSE                 SENT_CHXRCTL_SDHWPEN         /*!< serial data hardware parse mode */
#define SENT_SERIAL_DATA_SOFTWARE_PARSE                 ((uint32_t)0x00000000U)      /*!< serial data software parse mode */

/* status and communication nibble is included in CRC calculation or not */
#define SENT_STATUS_NIBBLE_IN_CRC                       SENT_CHXRCTL_CRCSNIB         /*!< status and communication nibble is included in CRC calculation */
#define SENT_STATUS_NIBBLE_NOT_IN_CRC                   ((uint32_t)0x00000000U)      /*!< status and communication nibble is not included in CRC calculation*/

/* alternative CRC mode */
#define SENT_PARALLEL_CRC                               SENT_CHXRCTL_ALTCRCMEN       /*!< alternative 4-bit parallel CRC mode */
#define SENT_STANDARD_CRC                               ((uint32_t)0x00000000U)      /*!< standard CRC mode */

/* ignore pause pulse */
#define SENT_IGNORE_PAUSE                               SENT_CHXRCTL_IPP             /*!< ignore pause pulse */
#define SENT_NOT_IGNORE_PAUSE                           ((uint32_t)0x00000000U)      /*!< not ignore pause pulse */

/* pulse polarity */
#define SENT_PULSE_POLARITY_HIGH                        SENT_CHXCS_PPL               /*!< pulse polarity is active high */
#define SENT_PULSE_POLARITY_LOW                         ((uint32_t)0x00000000U)      /*!< pulse polarity is active low */

/* fractional divider mode */
#define SENT_CLOCKDIVIDERMODE_OFF                       ((uint32_t)0x00000000U)      /*!< disable fractional divider */
#define SENT_CLOCKDIVIDERMODE_NORMAL                    ((uint32_t)0x00000001U)      /*!< normal divider mode */
#define SENT_CLOCKDIVIDERMODE_FRACTIONAL                ((uint32_t)0x00000002U)      /*!< fractional divider mode*/

/* define the SENT channel status */
#define SENT_CH_STOP                                    ((uint32_t)(0x00000000U))    /*!< channel is disabled */
#define SENT_CH_INIT                                    ((uint32_t)(0x00000010U))    /*!< channel is enabled, but synchronization/calibration pulse  has not been received */
#define SENT_CH_RUN                                     ((uint32_t)(0x00000020U))    /*!< channel is enabled and the synchronization/calibration pulse received was out of the correct frequency range or had frequency drift and was out of range. */
#define SENT_CH_SYNC                                    ((uint32_t)(0x00000030U))    /*!< Channel is enabled and synchronization/calibration pulse received is valid and in the synchronization state */

#define SENT_INT_RSF                                    SENT_CHXINTEN_RSFIE          /*!< receive success interrupt enable */
#define SENT_INT_RBNE                                   SENT_CHXINTEN_RBNEIE         /*!< receive buffer not empty interrupt enable */
#define SENT_INT_RXOVERR                                SENT_CHXINTEN_RXOVERRIE      /*!< receive buffer overflow error interrupt enable */
#define SENT_INT_FDEVERR                                SENT_CHXINTEN_FDEVERRIE      /*!< frequency deviation error interrupt enable */
#define SENT_INT_FDERR                                  SENT_CHXINTEN_FDERRIE        /*!< frequency drift error interrupt enable */
#define SENT_INT_NNIBERR                                SENT_CHXINTEN_NNIBERRIE      /*!< number of nibbles error interrupt enable */
#define SENT_INT_NIBVERR                                SENT_CHXINTEN_NIBVERRIE      /*!< nibble value error interrupt enable */
#define SENT_INT_CRCERR                                 SENT_CHXINTEN_CRCERRIE       /*!< CRC error interrupt enable */
#define SENT_INT_SSDSTERR                               SENT_CHXINTEN_SSDSTERRIE     /*!< short serial data message start bit error interrupt enable */
#define SENT_INT_SDRBNE                                 SENT_CHXINTEN_SDRBNEIE       /*!< serial data receive buffer not empty interrupt enable */
#define SENT_INT_SDCRCERR                               SENT_CHXINTEN_SDCRCERRIE     /*!< serial data CRC error interrupt enable */
#define SENT_INT_WDERR                                  SENT_CHXINTEN_WDERRIE        /*!< watchdog error interrupt enable */

#define SENT_INT_FLAG_RSF                               SENT_CHXSTAT_RSF             /*!< receive success interrupt flag */
#define SENT_INT_FLAG_RBNE                              SENT_CHXSTAT_RBNE            /*!< receive buffer not empty interrupt flag */
#define SENT_INT_FLAG_RXOVERR                           SENT_CHXSTAT_RXOVERR         /*!< receive buffer overflow error interrupt flag */
#define SENT_INT_FLAG_FDEVERR                           SENT_CHXSTAT_FDEVERR         /*!< frequency deviation error interrupt flag */
#define SENT_INT_FLAG_FDERR                             SENT_CHXSTAT_FDERR           /*!< frequency drift error interrupt flag */
#define SENT_INT_FLAG_NNIBERR                           SENT_CHXSTAT_NNIBERR         /*!< number of nibbles error interrupt flag */
#define SENT_INT_FLAG_NIBVERR                           SENT_CHXSTAT_NIBVERR         /*!< nibble value error interrupt flag */
#define SENT_INT_FLAG_CRCERR                            SENT_CHXSTAT_CRCERR          /*!< CRC error interrupt flag */
#define SENT_INT_FLAG_SSDSTERR                          SENT_CHXSTAT_SSDSTERR        /*!< short serial data message start bit error interrupt flag */
#define SENT_INT_FLAG_SDRBNE                            SENT_CHXSTAT_SDRBNE          /*!< serial data receive buffer not empty flag interrupt flag */
#define SENT_INT_FLAG_SDCRCERR                          SENT_CHXSTAT_SDCRCERR        /*!< serial data CRC error interrupt flag */
#define SENT_INT_FLAG_WDERR                             SENT_CHXSTAT_WDERR           /*!< watchdog error interrupt flag */
   
/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check frequency drift check parameter */
#define NOT_SENT_FREQ_DRIFT_CHECK(newvalue)             (((newvalue) != SENT_FREQ_DRIFT_CHECK_ENABLE) && ((newvalue) != SENT_FREQ_DRIFT_CHECK_DISABLE))

/* check frequency drift error mode parameter */
#define NOT_SENT_FREQ_DRIFT_ERROR(newvalue)             (((newvalue) != SENT_FREQ_DRIFT_ERROR_ENABLE) && ((newvalue) != SENT_FREQ_DRIFT_ERROR_DISABLE))

/* check serial message mode parameter */
#define NOT_SENT_SERIAL_MSG_MODE(mode)                  (((mode) != SENT_SHORT_SERIAL_MESSAGE) && ((mode) != SENT_ENHANCED_SERIAL_MESSAGE))

/* check serial message CRC mode parameter */
#define NOT_SENT_SERIAL_MSG_CRC_MODE(mode)              (((mode) != SENT_SERIAL_MESSAGE_AUGMENTATION_CRC) && ((mode) != SENT_SERIAL_MESSAGE_NORMAL_CRC))

/* check data length parameter */
#define NOT_SENT_DATA_LENGTH(length)                    (((length) != SENT_DATALEN_0_NIBBLE) && ((length) != SENT_DATALEN_1_NIBBLE) && ((length) != SENT_DATALEN_2_NIBBLE) && \
                                                        ((length) != SENT_DATALEN_3_NIBBLE) && ((length) != SENT_DATALEN_4_NIBBLE) && ((length) != SENT_DATALEN_5_NIBBLE) && \
                                                        ((length) != SENT_DATALEN_6_NIBBLE) && ((length) != SENT_DATALEN_7_NIBBLE) && ((length) != SENT_DATALEN_8_NIBBLE))

/* check consecutive synchronization check mode parameter */
#define NOT_SENT_CONS_SYNC_CHECK(mode)                  (((mode) != SENT_CONS_SYNC_CHECK_BEFORE) && ((mode) != SENT_CONS_SYNC_CHECK_AFTER))

/* check CRC enable parameter */
#define NOT_SENT_CRC(newvalue)                          (((newvalue) != SENT_CRC_ENABLE) && ((newvalue) != SENT_CRC_DISABLE))

/* check serial data CRC enable parameter */
#define NOT_SENT_SERIAL_DATA_CRC(newvalue)              (((newvalue) != SENT_SERIAL_DATA_CRC_ENABLE) && ((newvalue) != SENT_SERIAL_DATA_CRC_DISABLE))

/* check serial data parse mode parameter */
#define NOT_SENT_SERIAL_DATA_PARSE(mode)                (((mode) != SENT_SERIAL_DATA_HARDWARE_PARSE) && ((mode) != SENT_SERIAL_DATA_SOFTWARE_PARSE))

/* check status and communication nibble is included in CRC calculation or not parameter */
#define NOT_SENT_STATUS_NIBBLE_IN_CRC(mode)             (((mode) != SENT_STATUS_NIBBLE_IN_CRC) && ((mode) != SENT_STATUS_NIBBLE_NOT_IN_CRC))

/* check alternative CRC mode parameter */
#define NOT_SENT_ALTER_CRC(crc)                         (((crc) != SENT_PARALLEL_CRC) && ((crc) != SENT_STANDARD_CRC))

/* check ignore pause pulse or not parameter */
#define NOT_SENT_IGNORE_PAUSE(mode)                     (((mode) != SENT_IGNORE_PAUSE) && ((mode) != SENT_NOT_IGNORE_PAUSE))

/* check pulse polarity parameter */
#define NOT_SENT_PULSE_POLARITY(polarity)               (((polarity) != SENT_PULSE_POLARITY_HIGH) && ((polarity) != SENT_PULSE_POLARITY_LOW))

/* check fractional divider mode parameter */
#define NOT_SENT_CLOCK_DIVIDER_MODE(mode)               (((mode) != SENT_CLOCKDIVIDERMODE_OFF) && ((mode) != SENT_CLOCKDIVIDERMODE_NORMAL) && ((mode) != SENT_CLOCKDIVIDERMODE_FRACTIONAL))

/* check step value parameter */
#define SENT_CLOCK_STEP_HIGH_VALUE                      ((uint32_t)0x000003FFU)
#define NOT_SENT_CLOCK_STEP(stepvalue)                  (SENT_CLOCK_STEP_HIGH_VALUE < (stepvalue))

/* check frequency drift check parameter */
#define SENT_CHANNEL_TICK_LOW_VALUE                     ((double)0.00000004)
#define SENT_CHANNEL_TICK_HIGH_VALUE                    ((double)0.001024)
#define NOT_SENT_CHANNEL_TICK(tick_unit)                ((SENT_CHANNEL_TICK_LOW_VALUE > (tick_unit)) || (SENT_CHANNEL_TICK_HIGH_VALUE < (tick_unit)))

/* check digital filter timer threshold parameter */
#define SENT_CHANNEL_FILTER_TH_HIGH_VALUE               ((uint32_t)0x0000000FU)
#define NOT_SENT_CHANNEL_FILTER_TH(threshold)           (SENT_CHANNEL_FILTER_TH_HIGH_VALUE < (threshold))

/* check time stamp prescaler parameter */
#define SENT_TIMESTAMP_PRESCALER_HIGH_VALUE             ((uint32_t)0x000FFFFFU)
#define NOT_SENT_TIMESTAMP_PRESCALER(psc)               (SENT_TIMESTAMP_PRESCALER_HIGH_VALUE < (psc))

/* check interrupt parameter */
#define NOT_SENT_INTERRUPT(interrupt)                   (((interrupt) != SENT_INT_RSF)     && ((interrupt) != SENT_INT_RBNE) && \
                                                        ((interrupt) != SENT_INT_RXOVERR)  && ((interrupt) != SENT_INT_FDEVERR) && \
                                                        ((interrupt) != SENT_INT_FDERR)    && ((interrupt) != SENT_INT_NNIBERR) && \
                                                        ((interrupt) != SENT_INT_NIBVERR)  && ((interrupt) != SENT_INT_CRCERR) && \
                                                        ((interrupt) != SENT_INT_SSDSTERR) && ((interrupt) != SENT_INT_SDRBNE) && \
                                                        ((interrupt) != SENT_INT_SDCRCERR) && ((interrupt) != SENT_INT_WDERR))
 /* check interrupt flag parameter */
#define NOT_SENT_INT_FLAG(int_flag)                     (((int_flag) != SENT_INT_FLAG_RSF)     && ((int_flag) != SENT_INT_FLAG_RBNE) && \
                                                        ((int_flag) != SENT_INT_FLAG_RXOVERR)  && ((int_flag) != SENT_INT_FLAG_FDEVERR) && \
                                                        ((int_flag) != SENT_INT_FLAG_FDERR)    && ((int_flag) != SENT_INT_FLAG_NNIBERR) && \
                                                        ((int_flag) != SENT_INT_FLAG_NIBVERR)  && ((int_flag) != SENT_INT_FLAG_CRCERR) && \
                                                        ((int_flag) != SENT_INT_FLAG_SSDSTERR) && ((int_flag) != SENT_INT_FLAG_SDRBNE) && \
                                                        ((int_flag) != SENT_INT_FLAG_SDCRCERR) && ((int_flag) != SENT_INT_FLAG_WDERR))
                                              
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* initialization functions */
/* reset SENT */
void sent_deinit(void);
/* initialize the parameters of SENT structure with the default values */
void sent_struct_para_init(sent_parameter_struct *sent_struct);
/* initialize SENT parameters */
void sent_init(sent_channel_enum channelx, sent_parameter_struct *sent_struct);
/* enable SENT */
void sent_enable(void);
/* disable SENT */
void sent_disable(void);
/* enable SENT sleep mode */
void sent_sleep_enable(void);
/* disable SENT sleep mode */
void sent_sleep_disable(void);

/* application function declarations */
/* get SENT state */
ControlStatus sent_state_get(void);
/* enable SENT channel x */
void sent_channel_enable(sent_channel_enum channelx);
/* disable SENT channel x */
void sent_channel_disable(sent_channel_enum channelx);
/* get SENT channel x state */
uint32_t sent_channel_state_get(sent_channel_enum channelx);
/* select SENT channel x input */
void sent_channel_input_select(sent_channel_enum channelx, sent_channel_input_enum inputx);
/* configure SENT module clock */
void sent_module_clock_config(uint32_t dividermode, uint32_t stepvalue);
/* configure SENT ticks clock */
void sent_channel_tick_clock_config(sent_channel_enum channelx, double tick_unit);
/* set SENT filter threshold */
void sent_filter_threshold_set(sent_channel_enum channelx, uint32_t threshold);
/* configure SENT channel data nibble storage position */
void sent_data_nibble_pos_config(sent_channel_enum channelx, sent_nibble_control_struct *data);
/* configure SENT timestamp prescaler */
void sent_timestamp_prescaler_config(uint32_t psc);
/* get SENT current timestamp */
uint32_t sent_timestamp_get(void);
/* set SENT watchdog threshold */
void sent_watchdog_threshold_set(sent_channel_enum channelx, uint16_t threshold);
/* SENT receive data nibble */
uint32_t sent_receive_data(sent_channel_enum channelx);
/* SENT receive frame */
void sent_receive_frame(sent_channel_enum channelx, sent_frame_struct *frame);
/* SENT receive serial message */
void sent_receive_serial_message(sent_channel_enum channelx, sent_serialmessage_frame_struct *message);
/* get the falling edge count occurring on the selected SENT input pin */
uint8_t sent_input_edge_count_get(sent_channel_enum channelx);
/* clear the falling edge count occurring on the selected SENT input pin */
void sent_input_edge_count_clear(sent_channel_enum channelx);
/* get SENT frame length */
double sent_get_frame_length(sent_channel_enum channelx);
/* get SENT synchronization pulse length */
double sent_get_sync_length(sent_channel_enum channelx);

/* interrupt & flag functions */
/* set SENT channel flag status */
void sent_channel_flag_set(sent_channel_enum channelx, sent_channel_flag_enum flag);
/* get SENT channel flag */
FlagStatus sent_channel_flag_get(sent_channel_enum channelx, sent_channel_flag_enum flag);
/* clear SENT channel status */
void sent_channel_flag_clear(sent_channel_enum channelx, sent_channel_flag_clear_enum flag);
/* enable SENT channel interrupt */
void sent_channel_interrupt_enable(sent_channel_enum channelx, uint32_t interrupt);
/* disable SENT channel interrupt */
void sent_channel_interrupt_disable(sent_channel_enum channelx, uint32_t interrupt);
/* get SENT channel interrupt and flag status */
FlagStatus sent_channel_interrupt_flag_get(sent_channel_enum channelx, uint32_t int_flag);
/* get SENT channel global interrupt and flag status */
FlagStatus sent_channel_global_interrupt_flag_get(sent_channel_enum channelx);
/* clear SENT  channel interrupt flag */
void sent_channel_interrupt_flag_clear(sent_channel_enum channelx, uint32_t int_flag);

#endif /* GD32A7XX_SENT_H */ 
