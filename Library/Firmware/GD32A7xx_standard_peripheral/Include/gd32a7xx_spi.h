/*!
    \file    gd32a7xx_spi.h
    \brief   definitions for the SPI

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

#ifndef GD32A7XX_SPI_H
#define GD32A7XX_SPI_H
#include "gd32a7xx.h"

/* SPIx(x=0,1,2,3,4,5,6,7) definitions */
#define SPI0                           (SPI_BASE + 0x0000F800U)               /*!< SPI0 base adress */
#define SPI1                           (SPI_BASE + 0x00014000U)               /*!< SPI1 base adress */
#define SPI2                           (SPI_BASE + 0x0000AC00U)               /*!< SPI2 base adress */
#define SPI3                           (SPI_BASE + 0x0000B000U)               /*!< SPI3 base adress */
#define SPI4                           (SPI_BASE + 0x00010C00U)               /*!< SPI4 base adress */
#define SPI5                           (SPI_BASE + 0x00011000U)               /*!< SPI5 base adress */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define SPI6                            SPI_BASE                              /*!< SPI6 base adress */
#define SPI7                           (SPI_BASE + 0x00000400U)               /*!< SPI7 base adress */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* I2Sx(x=4,5,6,7) definitions */
#define I2S4                           SPI4                                   /*!< I2S4 base adress */
#define I2S5                           SPI5                                   /*!< I2S5 base adress */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define I2S6                           SPI6                                   /*!< I2S6 base adress */
#define I2S7                           SPI7                                   /*!< I2S7 base adress */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */


/* registers definitions */
#define SPI_CTL0(spix)                  REG32((spix) + 0x00000000U)             /*!< SPI control register 0 */
#define SPI_CTL1(spix)                  REG32((spix) + 0x00000004U)             /*!< SPI control register 1*/
#define SPI_STAT(spix)                  REG32((spix) + 0x00000008U)             /*!< SPI status register */
#define SPI_DATA(spix)                  REG32((spix) + 0x0000000CU)             /*!< SPI data register */
#define SPI_CRCPOLY(spix)               REG32((spix) + 0x00000010U)             /*!< SPI CRC polynomial register */
#define SPI_TCRC(spix)                  REG32((spix) + 0x00000018U)             /*!< SPI transmit CRC register */
#define SPI_I2SCTL(spix)                REG32((spix) + 0x0000001CU)             /*!< SPI I2S control register */
#define SPI_I2SPSC(spix)                REG32((spix) + 0x00000020U)             /*!< SPI I2S clock prescaler register */
#define SPI_MREQCFG(spix)               REG32((spix) + 0x00000028U)             /*!< SPI HREQ configuration register */
#define SPI_CKCFG0(spix)                REG32((spix) + 0x0000002CU)             /*!< SPI clock configuration register 0 */
#define SPI_CKCFG1(spix)                REG32((spix) + 0x00000030U)             /*!< SPI clock configuration register 1 */
#define SPI_CCTL(spix)                  REG32((spix) + 0x00000034U)             /*!< SPI continuous control register */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define SPI_POLCTL(spix)                REG32((spix) + 0x00000038U)             /*!< SPI NSS polarity control register */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define SPI_QCTL(spix)                  REG32((spix) + 0x00000080U)             /*!< SPI quad mode control register(only SPI0 and SPI2) */

/* bits definitions */
/* SPI_CTL0 */
#define SPI_CTL0_CKPH                   BIT(0)                                  /*!< clock phase selection*/
#define SPI_CTL0_CKPL                   BIT(1)                                  /*!< clock polarity selection */
#define SPI_CTL0_MSTMOD                 BIT(2)                                  /*!< master mode enable */
#define SPI_CTL0_SPIEN                  BIT(6)                                  /*!< SPI enable*/
#define SPI_CTL0_LF                     BIT(7)                                  /*!< LSB first mode */
#define SPI_CTL0_SWNSS                  BIT(8)                                  /*!< NSS pin selection in NSS software mode */
#define SPI_CTL0_SWNSSEN                BIT(9)                                  /*!< NSS software mode selection */
#define SPI_CTL0_RO                     BIT(10)                                 /*!< receive only */
#define SPI_CTL0_CRCNT                  BIT(12)                                 /*!< CRC next transfer */
#define SPI_CTL0_CRCEN                  BIT(13)                                 /*!< CRC calculation enable */
#define SPI_CTL0_BDOEN                  BIT(14)                                 /*!< bidirectional transmit output enable*/
#define SPI_CTL0_BDEN                   BIT(15)                                 /*!< bidirectional enable */
#define SPI_CTL0_PSC                    BITS(16,22)                              /*!< master clock prescaler selection */

/* SPI_CTL1 */
#define SPI_CTL1_DMAREN                 BIT(0)                                  /*!< receive buffer DMA enable */
#define SPI_CTL1_DMATEN                 BIT(1)                                  /*!< transmit buffer DMA enable */
#define SPI_CTL1_NSSDRV                 BIT(2)                                  /*!< drive NSS output */
#define SPI_CTL1_NSSP                   BIT(3)                                  /*!< SPI NSS pulse mode enable */
#define SPI_CTL1_TMOD                   BIT(4)                                  /*!< SPI TI mode enable */
#define SPI_CTL1_ERRIE                  BIT(5)                                  /*!< errors interrupt enable */
#define SPI_CTL1_RFDRIE                 BIT(6)                                  /*!< receive fifo data ready interrupt enable */
#define SPI_CTL1_TFAIE                  BIT(7)                                  /*!< transmit fifo available interrupt enable */
#define SPI_CTL1_DZ                     BITS(8,12)                              /*!< data size for transfer (memory size) */
#define SPI_CTL1_NSSPOL                 BIT(15)                                /*!< NSS polarity */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define SPI_CTL1_NSSSEL                 BITS(17,19)                             /*!< SPI NSS select */
#else
#define SPI_CTL1_NSSSEL                 BITS(17,18)                             /*!< SPI NSS select */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define SPI_CTL1_FIFOLBEN               BIT(20)                                 /*!< fifo loopback mode enable */
#define SPI_CTL1_SINGMOD                BIT(21)                                 /*!< single-frame mode enable */
#define SPI_CTL1_TOEN                   BIT(22)                                 /*!< timeout enable */
#define SPI_CTL1_TOIE                   BIT(23)                                 /*!< timeout interrupt enable */
#define SPI_CTL1_TOCFG                  BITS(24,31)                             /*!< timeout configuration */

/* SPI_STAT */
#define SPI_STAT_RFDR                   BIT(0)                                  /*!< reception fifo data ready */
#define SPI_STAT_TFA                    BIT(1)                                  /*!< transmission fifo available */
#define SPI_STAT_I2SCH                  BIT(2)                                  /*!< I2S channel side */
#define SPI_STAT_TXURERR                BIT(3)                                  /*!< I2S transmission underrun error bit */
#define SPI_STAT_CONFERR                BIT(5)                                  /*!< SPI configuration error bit */
#define SPI_STAT_RXORERR                BIT(6)                                  /*!< SPI reception overrun error bit */
#define SPI_STAT_TRANS                  BIT(7)                                  /*!< transmitting on-going bit */
#define SPI_STAT_FERR                   BIT(8)                                  /*!< format error bit */
#define SPI_STAT_RXLVL                  BITS(9,12)                              /*!< refer to the current storage of the rxfifo */
#define SPI_STAT_TXLVL                  BITS(14,17)                             /*!< refer to the current storage of the txfifo */
#define SPI_STAT_TOF                    BIT(19)                                 /*!< SPI idle timeout flag */

/* SPI_I2SCTL */
#define SPI_I2SCTL_CHLEN                BIT(0)                                  /*!< channel length */
#define SPI_I2SCTL_DTLEN                BITS(1,2)                               /*!< data length */
#define SPI_I2SCTL_CKPL                 BIT(3)                                  /*!< idle state clock polarity */
#define SPI_I2SCTL_I2SSTD               BITS(4,5)                               /*!< I2S standard selection */
#define SPI_I2SCTL_PCMSMOD              BIT(7)                                  /*!< PCM frame synchronization mode */
#define SPI_I2SCTL_I2SOPMOD             BITS(8,9)                               /*!< I2S operation mode */
#define SPI_I2SCTL_I2SEN                BIT(10)                                 /*!< I2S enable */
#define SPI_I2SCTL_I2SSEL               BIT(11)                                 /*!< I2S mode selection */

/* SPI_I2SPSC */
#define SPI_I2SPSC_DIV                  BITS(0,7)                               /*!< dividing factor for the prescaler */
#define SPI_I2SPSC_OF                   BIT(8)                                  /*!< odd factor for the prescaler */
#define SPI_I2SPSC_MCKOEN               BIT(9)                                  /*!< I2S MCK output enable */

/* SPI_MREQCFG */
#define SPI_MREQCFG_MREQEN              BIT(0)                                  /*!< host request enable */
#define SPI_MREQCFG_MREQPL              BIT(1)                                  /*!< host request polarity */
#define SPI_MREQCFG_MREQSEL             BIT(2)                                  /*!< host request select */
#define SPI_MREQCFG_MREQDIR             BIT(3)                                  /*!< configure the direction of SPI_HREQ pin */

/* SPI_CKCFG0 */
#define SPI_CKCFG0_NSSSCK               BITS(0,7)                               /*!< minimum delay from NSS active to SCK active */
#define SPI_CKCFG0_SCKNSS               BITS(8,15)                              /*!< minimum delay from SCK inactive to NSS inactive */
#define SPI_CKCFG0_NSSNSS               BITS(16,23)                             /*!< minimum delay from NSS inactive to NSS active */

/* SPI_CKCFG1 */
#define SPI_CKCFG1_SAMPDLY              BITS(0,11)                              /*!< master receive data sampling delay */
#define SPI_CKCFG1_SAMPDLYEN            BIT(12)                                 /*!< master receive data sampling delay enabled */

/* SPI_CCTL */
#define SPI_CCTL_FRAMLEN                BITS(0,15)                              /*!< continuous transmission frame count */
#define SPI_CCTL_HCEN                   BIT(16)                                 /*!< hardware continuous frame mode enable */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* SPI_POLCTL */
#define SPI_POLCTL_NSSPOLS              BITS(0,7)                               /*!< polarity of each NSS pin */
#define SPI_POLCTL_NSSPOLMOD            BIT(8)                                  /*!< NSS polarity mode selection */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* SPI_QCTL(only available in SPI0/2) */
#define SPI_QCTL_QMOD                   BIT(0)                                  /*!< quad-SPI mode enable */
#define SPI_QCTL_QRD                    BIT(1)                                  /*!< quad-SPI mode read select */

/* constants definitions */
/* SPI and I2S parameter struct definitions */
typedef struct {
    uint32_t device_mode;                                                       /*!< SPI master or slave */
    uint32_t trans_mode;                                                        /*!< SPI transtype */
    uint32_t nss;                                                               /*!< SPI NSS control by handware or software */
    uint32_t nss_polarity;                                                      /*!< SPI NSS polarity */
    uint32_t endian;                                                            /*!< SPI big endian or little endian */
    uint32_t clock_polarity_phase;                                              /*!< SPI clock phase and polarity */
    uint32_t prescale;                                                          /*!< SPI prescale factor */
} spi_parameter_struct;

/* SPI mode definitions */
#define SPI_MASTER                      (SPI_CTL0_MSTMOD | SPI_CTL0_SWNSS)      /*!< SPI as master */
#define SPI_SLAVE                       ((uint32_t)0x00000000U)                 /*!< SPI as slave */

/* SPI bidirectional transfer direction */
#define SPI_BIDIRECTIONAL_TRANSMIT      SPI_CTL0_BDOEN                          /*!< SPI work in transmit-only mode */
#define SPI_BIDIRECTIONAL_RECEIVE       (~SPI_CTL0_BDOEN)                       /*!< SPI work in receive-only mode */

/* SPI transmit type */
#define SPI_TRANSMODE_FULLDUPLEX        ((uint32_t)0x00000000U)                 /*!< SPI receive and send data at fullduplex communication */
#define SPI_TRANSMODE_RECEIVEONLY       SPI_CTL0_RO                             /*!< SPI only receive data */
#define SPI_TRANSMODE_BDRECEIVE         SPI_CTL0_BDEN                           /*!< bidirectional receive data */
#define SPI_TRANSMODE_BDTRANSMIT        (SPI_CTL0_BDEN | SPI_CTL0_BDOEN)        /*!< bidirectional transmit data*/

/* SPI NSS control mode */
#define SPI_NSSSEL(regval)              (BITS(17,19) & ((uint32_t)(regval) << 17U))
#define SPI_NSS_SOFT                    SPI_CTL0_SWNSSEN                        /*!< SPI NSS control by software */
#define SPI_NSS_HARD                    ((uint32_t)0x00000000U)                 /*!< SPI NSS control by hardware */

/* SPI NSS polarity */
#define SPI_NSS_POLARITY_LOW            ((uint32_t)0x00000000U)                 /*!< SPI NSS polarity is low */
#define SPI_NSS_POLARITY_HIGH           SPI_CTL1_NSSPOL                         /*!< SPI NSS polarity is high */

/* SPI transmit way */
#define SPI_ENDIAN_MSB                  ((uint32_t)0x00000000U)                 /*!< SPI transmit way is big endian: transmit MSB first */
#define SPI_ENDIAN_LSB                  SPI_CTL0_LF                             /*!< SPI transmit way is little endian: transmit LSB first */

/* SPI clock phase and polarity */
#define SPI_CK_PL_LOW_PH_1EDGE          ((uint32_t)0x00000000U)                 /*!< SPI clock polarity is low level and phase is first edge */
#define SPI_CK_PL_HIGH_PH_1EDGE         SPI_CTL0_CKPL                           /*!< SPI clock polarity is high level and phase is first edge */
#define SPI_CK_PL_LOW_PH_2EDGE          SPI_CTL0_CKPH                           /*!< SPI clock polarity is low level and phase is second edge */
#define SPI_CK_PL_HIGH_PH_2EDGE         (SPI_CTL0_CKPL | SPI_CTL0_CKPH)         /*!< SPI clock polarity is high level and phase is second edge */

/* SPI clock prescaler factor */
#define SPI_PSC_2                       ((uint32_t)0x00000000U)                 /*!< SPI clock prescaler factor is 2 */
#define SPI_PSC_4                       ((uint32_t)0x00000001U)                 /*!< SPI clock prescaler factor is 4 */
#define SPI_PSC_6                       ((uint32_t)0x00000002U)                 /*!< SPI clock prescaler factor is 6 */
#define SPI_PSC_8                       ((uint32_t)0x00000003U)                 /*!< SPI clock prescaler factor is 8 */
#define SPI_PSC_10                      ((uint32_t)0x00000004U)                 /*!< SPI clock prescaler factor is 10 */
#define SPI_PSC_12                      ((uint32_t)0x00000005U)                 /*!< SPI clock prescaler factor is 12 */
#define SPI_PSC_14                      ((uint32_t)0x00000006U)                 /*!< SPI clock prescaler factor is 14 */
#define SPI_PSC_16                      ((uint32_t)0x00000007U)                 /*!< SPI clock prescaler factor is 16 */
#define SPI_PSC_18                      ((uint32_t)0x00000008U)                 /*!< SPI clock prescaler factor is 18 */
#define SPI_PSC_20                      ((uint32_t)0x00000009U)                 /*!< SPI clock prescaler factor is 20 */
#define SPI_PSC_22                      ((uint32_t)0x0000000AU)                 /*!< SPI clock prescaler factor is 22 */
#define SPI_PSC_24                      ((uint32_t)0x0000000BU)                 /*!< SPI clock prescaler factor is 24 */
#define SPI_PSC_26                      ((uint32_t)0x0000000CU)                 /*!< SPI clock prescaler factor is 26 */
#define SPI_PSC_28                      ((uint32_t)0x0000000DU)                 /*!< SPI clock prescaler factor is 28 */
#define SPI_PSC_30                      ((uint32_t)0x0000000EU)                 /*!< SPI clock prescaler factor is 30 */
#define SPI_PSC_32                      ((uint32_t)0x0000000FU)                 /*!< SPI clock prescaler factor is 32 */
#define SPI_PSC_34                      ((uint32_t)0x00000010U)                 /*!< SPI clock prescaler factor is 34 */
#define SPI_PSC_36                      ((uint32_t)0x00000011U)                 /*!< SPI clock prescaler factor is 36 */
#define SPI_PSC_38                      ((uint32_t)0x00000012U)                 /*!< SPI clock prescaler factor is 38 */
#define SPI_PSC_40                      ((uint32_t)0x00000013U)                 /*!< SPI clock prescaler factor is 40 */
#define SPI_PSC_42                      ((uint32_t)0x00000014U)                 /*!< SPI clock prescaler factor is 42 */
#define SPI_PSC_44                      ((uint32_t)0x00000015U)                 /*!< SPI clock prescaler factor is 44 */
#define SPI_PSC_46                      ((uint32_t)0x00000016U)                 /*!< SPI clock prescaler factor is 46 */
#define SPI_PSC_48                      ((uint32_t)0x00000017U)                 /*!< SPI clock prescaler factor is 48 */
#define SPI_PSC_50                      ((uint32_t)0x00000018U)                 /*!< SPI clock prescaler factor is 50 */
#define SPI_PSC_52                      ((uint32_t)0x00000019U)                 /*!< SPI clock prescaler factor is 52 */
#define SPI_PSC_54                      ((uint32_t)0x0000001AU)                 /*!< SPI clock prescaler factor is 54 */
#define SPI_PSC_56                      ((uint32_t)0x0000001BU)                 /*!< SPI clock prescaler factor is 56 */
#define SPI_PSC_58                      ((uint32_t)0x0000001CU)                 /*!< SPI clock prescaler factor is 58 */
#define SPI_PSC_60                      ((uint32_t)0x0000001DU)                 /*!< SPI clock prescaler factor is 60 */
#define SPI_PSC_62                      ((uint32_t)0x0000001EU)                 /*!< SPI clock prescaler factor is 62 */
#define SPI_PSC_64                      ((uint32_t)0x0000001FU)                 /*!< SPI clock prescaler factor is 64 */
#define SPI_PSC_66                      ((uint32_t)0x00000020U)                 /*!< SPI clock prescaler factor is 66 */
#define SPI_PSC_68                      ((uint32_t)0x00000021U)                 /*!< SPI clock prescaler factor is 68 */
#define SPI_PSC_70                      ((uint32_t)0x00000022U)                 /*!< SPI clock prescaler factor is 70 */
#define SPI_PSC_72                      ((uint32_t)0x00000023U)                 /*!< SPI clock prescaler factor is 72 */
#define SPI_PSC_74                      ((uint32_t)0x00000024U)                 /*!< SPI clock prescaler factor is 74 */
#define SPI_PSC_76                      ((uint32_t)0x00000025U)                 /*!< SPI clock prescaler factor is 76 */
#define SPI_PSC_78                      ((uint32_t)0x00000026U)                 /*!< SPI clock prescaler factor is 78 */
#define SPI_PSC_80                      ((uint32_t)0x00000027U)                 /*!< SPI clock prescaler factor is 80 */
#define SPI_PSC_82                      ((uint32_t)0x00000028U)                 /*!< SPI clock prescaler factor is 82 */
#define SPI_PSC_84                      ((uint32_t)0x00000029U)                 /*!< SPI clock prescaler factor is 84 */
#define SPI_PSC_86                      ((uint32_t)0x0000002AU)                 /*!< SPI clock prescaler factor is 86 */
#define SPI_PSC_88                      ((uint32_t)0x0000002BU)                 /*!< SPI clock prescaler factor is 88 */
#define SPI_PSC_90                      ((uint32_t)0x0000002CU)                 /*!< SPI clock prescaler factor is 90 */
#define SPI_PSC_92                      ((uint32_t)0x0000002DU)                 /*!< SPI clock prescaler factor is 92 */
#define SPI_PSC_94                      ((uint32_t)0x0000002EU)                 /*!< SPI clock prescaler factor is 94 */
#define SPI_PSC_96                      ((uint32_t)0x0000002FU)                 /*!< SPI clock prescaler factor is 96 */
#define SPI_PSC_98                      ((uint32_t)0x00000030U)                 /*!< SPI clock prescaler factor is 98 */
#define SPI_PSC_100                     ((uint32_t)0x00000031U)                 /*!< SPI clock prescaler factor is 100 */
#define SPI_PSC_102                     ((uint32_t)0x00000032U)                 /*!< SPI clock prescaler factor is 102 */
#define SPI_PSC_104                     ((uint32_t)0x00000033U)                 /*!< SPI clock prescaler factor is 104 */
#define SPI_PSC_106                     ((uint32_t)0x00000034U)                 /*!< SPI clock prescaler factor is 106 */
#define SPI_PSC_108                     ((uint32_t)0x00000035U)                 /*!< SPI clock prescaler factor is 108 */
#define SPI_PSC_110                     ((uint32_t)0x00000036U)                 /*!< SPI clock prescaler factor is 110 */
#define SPI_PSC_112                     ((uint32_t)0x00000037U)                 /*!< SPI clock prescaler factor is 112 */
#define SPI_PSC_114                     ((uint32_t)0x00000038U)                 /*!< SPI clock prescaler factor is 114 */
#define SPI_PSC_116                     ((uint32_t)0x00000039U)                 /*!< SPI clock prescaler factor is 116 */
#define SPI_PSC_118                     ((uint32_t)0x0000003AU)                 /*!< SPI clock prescaler factor is 118 */
#define SPI_PSC_120                     ((uint32_t)0x0000003BU)                 /*!< SPI clock prescaler factor is 120 */
#define SPI_PSC_122                     ((uint32_t)0x0000003CU)                 /*!< SPI clock prescaler factor is 122 */
#define SPI_PSC_124                     ((uint32_t)0x0000003DU)                 /*!< SPI clock prescaler factor is 124 */
#define SPI_PSC_126                     ((uint32_t)0x0000003EU)                 /*!< SPI clock prescaler factor is 126 */
#define SPI_PSC_128                     ((uint32_t)0x0000003FU)                 /*!< SPI clock prescaler factor is 128 */
#define SPI_PSC_130                     ((uint32_t)0x00000040U)                 /*!< SPI clock prescaler factor is 130 */
#define SPI_PSC_132                     ((uint32_t)0x00000041U)                 /*!< SPI clock prescaler factor is 132 */
#define SPI_PSC_134                     ((uint32_t)0x00000042U)                 /*!< SPI clock prescaler factor is 134 */
#define SPI_PSC_136                     ((uint32_t)0x00000043U)                 /*!< SPI clock prescaler factor is 136 */
#define SPI_PSC_138                     ((uint32_t)0x00000044U)                 /*!< SPI clock prescaler factor is 138 */
#define SPI_PSC_140                     ((uint32_t)0x00000045U)                 /*!< SPI clock prescaler factor is 140 */
#define SPI_PSC_142                     ((uint32_t)0x00000046U)                 /*!< SPI clock prescaler factor is 142 */
#define SPI_PSC_144                     ((uint32_t)0x00000047U)                 /*!< SPI clock prescaler factor is 144 */
#define SPI_PSC_146                     ((uint32_t)0x00000048U)                 /*!< SPI clock prescaler factor is 146 */
#define SPI_PSC_148                     ((uint32_t)0x00000049U)                 /*!< SPI clock prescaler factor is 148 */
#define SPI_PSC_150                     ((uint32_t)0x0000004AU)                 /*!< SPI clock prescaler factor is 150 */
#define SPI_PSC_152                     ((uint32_t)0x0000004BU)                 /*!< SPI clock prescaler factor is 152 */
#define SPI_PSC_154                     ((uint32_t)0x0000004CU)                 /*!< SPI clock prescaler factor is 154 */
#define SPI_PSC_156                     ((uint32_t)0x0000004DU)                 /*!< SPI clock prescaler factor is 156 */
#define SPI_PSC_158                     ((uint32_t)0x0000004EU)                 /*!< SPI clock prescaler factor is 158 */
#define SPI_PSC_160                     ((uint32_t)0x0000004FU)                 /*!< SPI clock prescaler factor is 160 */
#define SPI_PSC_162                     ((uint32_t)0x00000050U)                 /*!< SPI clock prescaler factor is 162 */
#define SPI_PSC_164                     ((uint32_t)0x00000051U)                 /*!< SPI clock prescaler factor is 164 */
#define SPI_PSC_166                     ((uint32_t)0x00000052U)                 /*!< SPI clock prescaler factor is 166 */
#define SPI_PSC_168                     ((uint32_t)0x00000053U)                 /*!< SPI clock prescaler factor is 168 */
#define SPI_PSC_170                     ((uint32_t)0x00000054U)                 /*!< SPI clock prescaler factor is 170 */
#define SPI_PSC_172                     ((uint32_t)0x00000055U)                 /*!< SPI clock prescaler factor is 172 */
#define SPI_PSC_174                     ((uint32_t)0x00000056U)                 /*!< SPI clock prescaler factor is 174 */
#define SPI_PSC_176                     ((uint32_t)0x00000057U)                 /*!< SPI clock prescaler factor is 176 */
#define SPI_PSC_178                     ((uint32_t)0x00000058U)                 /*!< SPI clock prescaler factor is 178 */
#define SPI_PSC_180                     ((uint32_t)0x00000059U)                 /*!< SPI clock prescaler factor is 180 */
#define SPI_PSC_182                     ((uint32_t)0x0000005AU)                 /*!< SPI clock prescaler factor is 182 */
#define SPI_PSC_184                     ((uint32_t)0x0000005BU)                 /*!< SPI clock prescaler factor is 184 */
#define SPI_PSC_186                     ((uint32_t)0x0000005CU)                 /*!< SPI clock prescaler factor is 186 */
#define SPI_PSC_188                     ((uint32_t)0x0000005DU)                 /*!< SPI clock prescaler factor is 188 */
#define SPI_PSC_190                     ((uint32_t)0x0000005EU)                 /*!< SPI clock prescaler factor is 190 */
#define SPI_PSC_192                     ((uint32_t)0x0000005FU)                 /*!< SPI clock prescaler factor is 192 */
#define SPI_PSC_194                     ((uint32_t)0x00000060U)                 /*!< SPI clock prescaler factor is 194 */
#define SPI_PSC_196                     ((uint32_t)0x00000061U)                 /*!< SPI clock prescaler factor is 196 */
#define SPI_PSC_198                     ((uint32_t)0x00000062U)                 /*!< SPI clock prescaler factor is 198 */
#define SPI_PSC_200                     ((uint32_t)0x00000063U)                 /*!< SPI clock prescaler factor is 200 */
#define SPI_PSC_202                     ((uint32_t)0x00000064U)                 /*!< SPI clock prescaler factor is 202 */
#define SPI_PSC_204                     ((uint32_t)0x00000065U)                 /*!< SPI clock prescaler factor is 204 */
#define SPI_PSC_206                     ((uint32_t)0x00000066U)                 /*!< SPI clock prescaler factor is 206 */
#define SPI_PSC_208                     ((uint32_t)0x00000067U)                 /*!< SPI clock prescaler factor is 208 */
#define SPI_PSC_210                     ((uint32_t)0x00000068U)                 /*!< SPI clock prescaler factor is 210 */
#define SPI_PSC_212                     ((uint32_t)0x00000069U)                 /*!< SPI clock prescaler factor is 212 */
#define SPI_PSC_214                     ((uint32_t)0x0000006AU)                 /*!< SPI clock prescaler factor is 214 */
#define SPI_PSC_216                     ((uint32_t)0x0000006BU)                 /*!< SPI clock prescaler factor is 216 */
#define SPI_PSC_218                     ((uint32_t)0x0000006CU)                 /*!< SPI clock prescaler factor is 218 */
#define SPI_PSC_220                     ((uint32_t)0x0000006DU)                 /*!< SPI clock prescaler factor is 220 */
#define SPI_PSC_222                     ((uint32_t)0x0000006EU)                 /*!< SPI clock prescaler factor is 222 */
#define SPI_PSC_224                     ((uint32_t)0x0000006FU)                 /*!< SPI clock prescaler factor is 224 */
#define SPI_PSC_226                     ((uint32_t)0x00000070U)                 /*!< SPI clock prescaler factor is 226 */
#define SPI_PSC_228                     ((uint32_t)0x00000071U)                 /*!< SPI clock prescaler factor is 228 */
#define SPI_PSC_230                     ((uint32_t)0x00000072U)                 /*!< SPI clock prescaler factor is 230 */
#define SPI_PSC_232                     ((uint32_t)0x00000073U)                 /*!< SPI clock prescaler factor is 232 */
#define SPI_PSC_234                     ((uint32_t)0x00000074U)                 /*!< SPI clock prescaler factor is 234 */
#define SPI_PSC_236                     ((uint32_t)0x00000075U)                 /*!< SPI clock prescaler factor is 236 */
#define SPI_PSC_238                     ((uint32_t)0x00000076U)                 /*!< SPI clock prescaler factor is 238 */
#define SPI_PSC_240                     ((uint32_t)0x00000077U)                 /*!< SPI clock prescaler factor is 240 */
#define SPI_PSC_242                     ((uint32_t)0x00000078U)                 /*!< SPI clock prescaler factor is 242 */
#define SPI_PSC_244                     ((uint32_t)0x00000079U)                 /*!< SPI clock prescaler factor is 244 */
#define SPI_PSC_246                     ((uint32_t)0x0000007AU)                 /*!< SPI clock prescaler factor is 246 */
#define SPI_PSC_248                     ((uint32_t)0x0000007BU)                 /*!< SPI clock prescaler factor is 248 */
#define SPI_PSC_250                     ((uint32_t)0x0000007CU)                 /*!< SPI clock prescaler factor is 250 */
#define SPI_PSC_252                     ((uint32_t)0x0000007DU)                 /*!< SPI clock prescaler factor is 252 */
#define SPI_PSC_254                     ((uint32_t)0x0000007EU)                 /*!< SPI clock prescaler factor is 254 */
#define SPI_PSC_256                     ((uint32_t)0x0000007FU)                 /*!< SPI clock prescaler factor is 256 */

/* SPI APB bus size */
#define SPI_BUS_SIZE(regval)             (BITS(13,14) & ((uint32_t)(regval) << 13U))
#define SPI_BUS_SIZE_BYTE                 SPI_BUS_SIZE(0)                       /*!< access APB bus size to FIFO is byte */
#define SPI_BUS_SIZE_HALFWORD             SPI_BUS_SIZE(1)                       /*!< access APB bus size to FIFO is half-word */
#define SPI_BUS_SIZE_WORD                 SPI_BUS_SIZE(2)                       /*!< access APB bus size to FIFO is word access */

/* SPI NSS select */
#define SPI_NSS_SELECT(regval)           (BITS(17,19) & ((uint32_t)(regval) << 17U))
#define SPI_NSS_SELECT_0                 SPI_NSS_SELECT(0)                       /*!< SPI NSS select 0 */
#define SPI_NSS_SELECT_1                 SPI_NSS_SELECT(1)                       /*!< SPI NSS select 1 */
#define SPI_NSS_SELECT_2                 SPI_NSS_SELECT(2)                       /*!< SPI NSS select 2 */
#define SPI_NSS_SELECT_3                 SPI_NSS_SELECT(3)                       /*!< SPI NSS select 3 */
#define SPI_NSS_SELECT_4                 SPI_NSS_SELECT(4)                       /*!< SPI NSS select 4 */
#define SPI_NSS_SELECT_5                 SPI_NSS_SELECT(5)                       /*!< SPI NSS select 5 */
#define SPI_NSS_SELECT_6                 SPI_NSS_SELECT(6)                       /*!< SPI NSS select 6 */
#define SPI_NSS_SELECT_7                 SPI_NSS_SELECT(7)                       /*!< SPI NSS select 7 */

/* I2S audio sample rate */
#define I2S_AUDIOSAMPLE_8K              ((uint32_t)8000U)                       /*!< I2S audio sample rate is 8KHz */
#define I2S_AUDIOSAMPLE_11K             ((uint32_t)11025U)                      /*!< I2S audio sample rate is 11KHz */
#define I2S_AUDIOSAMPLE_16K             ((uint32_t)16000U)                      /*!< I2S audio sample rate is 16KHz */
#define I2S_AUDIOSAMPLE_22K             ((uint32_t)22050U)                      /*!< I2S audio sample rate is 22KHz */
#define I2S_AUDIOSAMPLE_32K             ((uint32_t)32000U)                      /*!< I2S audio sample rate is 32KHz */
#define I2S_AUDIOSAMPLE_44K             ((uint32_t)44100U)                      /*!< I2S audio sample rate is 44KHz */
#define I2S_AUDIOSAMPLE_48K             ((uint32_t)48000U)                      /*!< I2S audio sample rate is 48KHz */
#define I2S_AUDIOSAMPLE_96K             ((uint32_t)96000U)                      /*!< I2S audio sample rate is 96KHz */
#define I2S_AUDIOSAMPLE_192K            ((uint32_t)192000U)                     /*!< I2S audio sample rate is 192KHz */

/* I2S frame format */
#define I2SCTL_DTLEN(regval)            (BITS(1,2) & ((uint32_t)(regval) << 1U))
#define I2S_FRAMEFORMAT_DT16B_CH16B     I2SCTL_DTLEN(0)                         /*!< I2S data length is 16 bit and channel length is 16 bit */
#define I2S_FRAMEFORMAT_DT16B_CH32B     (I2SCTL_DTLEN(0) | SPI_I2SCTL_CHLEN)    /*!< I2S data length is 16 bit and channel length is 32 bit */
#define I2S_FRAMEFORMAT_DT24B_CH32B     (I2SCTL_DTLEN(1) | SPI_I2SCTL_CHLEN)    /*!< I2S data length is 24 bit and channel length is 32 bit */
#define I2S_FRAMEFORMAT_DT32B_CH32B     (I2SCTL_DTLEN(2) | SPI_I2SCTL_CHLEN)    /*!< I2S data length is 32 bit and channel length is 32 bit */

/* I2S master clock output */
#define I2S_MCKOUT_DISABLE              ((uint32_t)0x00000000U)                 /*!< I2S master clock output disable */
#define I2S_MCKOUT_ENABLE               SPI_I2SPSC_MCKOEN                       /*!< I2S master clock output enable */

/* I2S operation mode */
#define I2SCTL_I2SOPMOD(regval)         (BITS(8,9) & ((uint32_t)(regval) << 8U))
#define I2S_MODE_SLAVETX                I2SCTL_I2SOPMOD(0)                      /*!< I2S slave transmit mode */
#define I2S_MODE_SLAVERX                I2SCTL_I2SOPMOD(1)                      /*!< I2S slave receive mode */
#define I2S_MODE_MASTERTX               I2SCTL_I2SOPMOD(2)                      /*!< I2S master transmit mode */
#define I2S_MODE_MASTERRX               I2SCTL_I2SOPMOD(3)                      /*!< I2S master receive mode */

/* I2S standard */
#define I2SCTL_I2SSTD(regval)           (BITS(4,5) & ((uint32_t)(regval) << 4U))
#define I2S_STD_PHILIPS                 I2SCTL_I2SSTD(0)                        /*!< I2S philips standard */
#define I2S_STD_MSB                     I2SCTL_I2SSTD(1)                        /*!< I2S MSB standard */
#define I2S_STD_LSB                     I2SCTL_I2SSTD(2)                        /*!< I2S LSB standard */
#define I2S_STD_PCMSHORT                I2SCTL_I2SSTD(3)                        /*!< I2S PCM short standard */
#define I2S_STD_PCMLONG                 (I2SCTL_I2SSTD(3) | SPI_I2SCTL_PCMSMOD) /*!< I2S PCM long standard */

/* I2S clock polarity */
#define I2S_CKPL_LOW                    ((uint32_t)0x00000000U)                 /*!< I2S clock polarity low level */
#define I2S_CKPL_HIGH                   SPI_I2SCTL_CKPL                         /*!< I2S clock polarity high level */

/* SPI DMA constants definitions */
#define SPI_DMA_TRANSMIT                ((uint8_t)0x00U)                        /*!< SPI transmit data use DMA */
#define SPI_DMA_RECEIVE                 ((uint8_t)0x01U)                        /*!< SPI receive data use DMA */

/* SPI CRC constants definitions */
#define SPI_CRC_TX                      ((uint8_t)0x00U)                        /*!< SPI transmit CRC value */
#define SPI_CRC_RX                      ((uint8_t)0x01U)                        /*!< SPI receive CRC value */

/* SPI/I2S interrupt enable/disable constants definitions */
#define SPI_I2S_INT_TFA                 SPI_CTL1_TFAIE                          /*!< transmission fifo available interrupt enable */
#define SPI_I2S_INT_RFDR                SPI_CTL1_RFDRIE                         /*!< reception fifo data ready interrupt enable */
#define SPI_I2S_INT_ERR                 SPI_CTL1_ERRIE                          /*!< error interrupt */
#define SPI_INT_TO                      SPI_CTL1_TOIE                           /*!< timeout interrupt */

/* SPI/I2S interrupt flag constants definitions */
#define SPI_I2S_INT_FLAG_TFA            ((uint8_t)0x00U)                        /*!< transmit buffer empty interrupt flag */
#define SPI_I2S_INT_FLAG_RFDR           ((uint8_t)0x01U)                        /*!< receive buffer not empty interrupt flag */
#define SPI_I2S_INT_FLAG_RXORERR        ((uint8_t)0x02U)                        /*!< overrun interrupt flag */
#define SPI_I2S_INT_FLAG_TXURERR        ((uint8_t)0x05U)                        /*!< underrun error interrupt flag */
#define SPI_INT_FLAG_TOF                ((uint8_t)0x04U)                        /*!< timeout interrupt flag */
#define SPI_INT_FLAG_CONFERR            ((uint8_t)0x03U)                        /*!< config error interrupt flag */
#define SPI_I2S_INT_FLAG_FERR           ((uint8_t)0x06U)                        /*!< format error interrupt flag */

/* SPI/I2S flag definitions */
#define SPI_FLAG_RFDR                   SPI_STAT_RFDR                           /*!< reception fifo data ready flag */
#define SPI_FLAG_TFA                    SPI_STAT_TFA                            /*!< transmission fifo available flag */
#define SPI_FLAG_TXURERR                SPI_STAT_TXURERR                        /*!< underrun error flag */
#define SPI_FLAG_CONFERR                SPI_STAT_CONFERR                        /*!< mode config error flag */
#define SPI_FLAG_RXORERR                SPI_STAT_RXORERR                        /*!< receive overrun error flag */
#define SPI_FLAG_TRANS                  SPI_STAT_TRANS                          /*!< transmit on-going flag */
#define SPI_FLAG_FERR                   SPI_STAT_FERR                           /*!< format error flag */
#define SPI_FLAG_TOF                    SPI_STAT_TOF                            /*!< timeout flag */

/* SPI flag definitions */
#define I2S_FLAG_RFDR                   SPI_STAT_RFDR                           /*!< reception fifo data ready flag */
#define I2S_FLAG_TFA                    SPI_STAT_TFA                            /*!< transmission fifo available flag */
#define I2S_FLAG_CH                     SPI_STAT_I2SCH                          /*!< channel side flag */
#define I2S_FLAG_TXURERR                SPI_STAT_TXURERR                        /*!< underrun error flag */
#define I2S_FLAG_RXORERR                SPI_STAT_RXORERR                        /*!< overrun error flag */
#define I2S_FLAG_TRANS                  SPI_STAT_TRANS                          /*!< transmit on-going flag */
#define I2S_FLAG_FERR                   SPI_STAT_FERR                           /*!< format error flag */

/* SPI data size */
#define SPI_DATA_SIZE1                  ((uint8_t)0x07U)                        /*!< data size 8 bit*/
#define SPI_DATA_SIZE2                  ((uint8_t)0x07U)                        /*!< data size 8 bit*/
#define SPI_DATA_SIZE3                  ((uint8_t)0x07U)                        /*!< data size 8 bit*/
#define SPI_DATA_SIZE4                  ((uint8_t)0x03U)                        /*!< data size 4 bit*/
#define SPI_DATA_SIZE5                  ((uint8_t)0x04U)                        /*!< data size 5 bit*/
#define SPI_DATA_SIZE6                  ((uint8_t)0x05U)                        /*!< data size 6 bit*/
#define SPI_DATA_SIZE7                  ((uint8_t)0x06U)                        /*!< data size 7 bit*/
#define SPI_DATA_SIZE8                  ((uint8_t)0x07U)                        /*!< data size 8 bit*/
#define SPI_DATA_SIZE9                  ((uint8_t)0x08U)                        /*!< data size 9 bit*/
#define SPI_DATA_SIZE10                 ((uint8_t)0x09U)                        /*!< data size 10 bit*/
#define SPI_DATA_SIZE11                 ((uint8_t)0x0AU)                        /*!< data size 11 bit*/
#define SPI_DATA_SIZE12                 ((uint8_t)0x0BU)                        /*!< data size 12 bit*/
#define SPI_DATA_SIZE13                 ((uint8_t)0x0CU)                        /*!< data size 13 bit*/
#define SPI_DATA_SIZE14                 ((uint8_t)0x0DU)                        /*!< data size 14 bit*/
#define SPI_DATA_SIZE15                 ((uint8_t)0x0EU)                        /*!< data size 15 bit*/
#define SPI_DATA_SIZE16                 ((uint8_t)0x0FU)                        /*!< data size 16 bit*/
#define SPI_DATA_SIZE17                 ((uint8_t)0x10U)                        /*!< data size 17 bit*/
#define SPI_DATA_SIZE18                 ((uint8_t)0x11U)                        /*!< data size 18 bit*/
#define SPI_DATA_SIZE19                 ((uint8_t)0x12U)                        /*!< data size 19 bit*/
#define SPI_DATA_SIZE20                 ((uint8_t)0x13U)                        /*!< data size 20 bit*/
#define SPI_DATA_SIZE21                 ((uint8_t)0x14U)                        /*!< data size 21 bit*/
#define SPI_DATA_SIZE22                 ((uint8_t)0x15U)                        /*!< data size 22 bit*/
#define SPI_DATA_SIZE23                 ((uint8_t)0x16U)                        /*!< data size 23 bit*/
#define SPI_DATA_SIZE24                 ((uint8_t)0x17U)                        /*!< data size 24 bit*/
#define SPI_DATA_SIZE25                 ((uint8_t)0x18U)                        /*!< data size 25 bit*/
#define SPI_DATA_SIZE26                 ((uint8_t)0x19U)                        /*!< data size 26 bit*/
#define SPI_DATA_SIZE27                 ((uint8_t)0x1AU)                        /*!< data size 27 bit*/
#define SPI_DATA_SIZE28                 ((uint8_t)0x1BU)                        /*!< data size 28 bit*/
#define SPI_DATA_SIZE29                 ((uint8_t)0x1CU)                        /*!< data size 29 bit*/
#define SPI_DATA_SIZE30                 ((uint8_t)0x1DU)                        /*!< data size 30 bit*/
#define SPI_DATA_SIZE31                 ((uint8_t)0x1EU)                        /*!< data size 31 bit*/
#define SPI_DATA_SIZE32                 ((uint8_t)0x1FU)                        /*!< data size 32 bit*/

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* SPI NSS pin definitions */
#define SPI_NSS_PIN_0                   BIT(0)                                  /*!< NSS pin 0 */
#define SPI_NSS_PIN_1                   BIT(1)                                  /*!< NSS pin 1 */
#define SPI_NSS_PIN_2                   BIT(2)                                  /*!< NSS pin 2 */
#define SPI_NSS_PIN_3                   BIT(3)                                  /*!< NSS pin 3 */
#define SPI_NSS_PIN_4                   BIT(4)                                  /*!< NSS pin 4 */
#define SPI_NSS_PIN_5                   BIT(5)                                  /*!< NSS pin 5 */
#define SPI_NSS_PIN_6                   BIT(6)                                  /*!< NSS pin 6 */
#define SPI_NSS_PIN_7                   BIT(7)                                  /*!< NSS pin 7 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check SPI peripherals */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_SPI_PERIPH(periph)                               (((periph) != SPI0) && ((periph) != SPI1) && ((periph) != SPI2) && \
                                                              ((periph) != SPI3) && ((periph) != SPI4) && ((periph) != SPI5) && \
                                                              ((periph) != SPI6) && ((periph) != SPI7))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#ifdef GD32A711X_A712X
#define NOT_SPI_PERIPH(periph)                               (((periph) != SPI0) && ((periph) != SPI1) && ((periph) != SPI2) && \
                                                              ((periph) != SPI3) && ((periph) != SPI4) && ((periph) != SPI5))
#endif /* GD32A711X_A712X */                                       
/* check quad SPI peripherals */
#define NOT_QUAD_SPI_PERIPH(periph)                          (((periph) != SPI0) && ((periph) != SPI2))
/* check I2S peripherals */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_I2S_PERIPH(periph)                               (((periph) != I2S4) && ((periph) != I2S5) && \
                                                              ((periph) != I2S6) && ((periph) != I2S7))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#ifdef GD32A711X_A712X
#define NOT_I2S_PERIPH(periph)                               (((periph) != I2S4) && ((periph) != I2S5))
#endif /* GD32A711X_A712X */                                       
/* check SPI device mode */
#define NOT_SPI_DEVICE_MODE(device_mode)                     (((device_mode) != SPI_MASTER) && ((device_mode) != SPI_SLAVE))
/* check SPI trans mode */
#define NOT_SPI_TRANS_MODE(trans_mode)                       (((trans_mode) != SPI_TRANSMODE_FULLDUPLEX) && ((trans_mode) != SPI_TRANSMODE_RECEIVEONLY) && \
                                                              ((trans_mode) != SPI_TRANSMODE_BDRECEIVE) && ((trans_mode) != SPI_TRANSMODE_BDTRANSMIT))
/* check SPI nss */
#define NOT_SPI_NSS(nss)                                     (((nss) != SPI_NSS_SOFT) && ((nss) != SPI_NSS_HARD))
/* check SPI nss polarity */
#define NOT_SPI_NSS_POLARITY(nss_polarity)                   (((nss_polarity) != SPI_NSS_POLARITY_LOW) && ((nss_polarity) != SPI_NSS_POLARITY_HIGH))
/* check SPI endian */
#define NOT_SPI_ENDIAN(endian)                               (((endian) != SPI_ENDIAN_MSB) && ((endian) != SPI_ENDIAN_LSB))
/* check SPI clock polarity phase */
#define NOT_SPI_CLOCK_POLARITY_PHASE(clock_polarity_phase)  (((clock_polarity_phase) != SPI_CK_PL_LOW_PH_1EDGE) && ((clock_polarity_phase) != SPI_CK_PL_HIGH_PH_1EDGE) && \
                                                              ((clock_polarity_phase) != SPI_CK_PL_LOW_PH_2EDGE) && ((clock_polarity_phase) != SPI_CK_PL_HIGH_PH_2EDGE))
/* check SPI clock prescaler */
#define NOT_SPI_PRESCALE(prescale)                           ((prescale) > ((uint32_t)0x0000007FU))
/* check SPI i2s mode */
#define NOT_SPI_I2S_MODE(i2s_mode)                           (((i2s_mode) != I2S_MODE_SLAVETX) && ((i2s_mode) != I2S_MODE_SLAVERX) && \
                                                              ((i2s_mode) != I2S_MODE_MASTERTX) && ((i2s_mode) != I2S_MODE_MASTERRX))
/* check SPI i2s standard */
#define NOT_SPI_I2S_STANDARD(i2s_standard)                   (((i2s_standard) != I2S_STD_PHILIPS) && ((i2s_standard) != I2S_STD_MSB) && \
                                                              ((i2s_standard) != I2S_STD_LSB) && ((i2s_standard) != I2S_STD_PCMSHORT) && \
                                                              ((i2s_standard) != I2S_STD_PCMLONG))
/* check SPI i2s ckpl */
#define NOT_SPI_I2S_CKPL(i2s_ckpl)                           (((i2s_ckpl) != I2S_CKPL_LOW) && ((i2s_ckpl) != I2S_CKPL_HIGH))
/* check SPI i2s audiosample */
#define NOT_SPI_I2S_AUDIOSAMPLE(i2s_audiosample)             (((i2s_audiosample) != I2S_AUDIOSAMPLE_8K) && ((i2s_audiosample) != I2S_AUDIOSAMPLE_11K) && \
                                                              ((i2s_audiosample) != I2S_AUDIOSAMPLE_16K) && ((i2s_audiosample) != I2S_AUDIOSAMPLE_22K) && \
                                                              ((i2s_audiosample) != I2S_AUDIOSAMPLE_32K)&& ((i2s_audiosample) != I2S_AUDIOSAMPLE_44K) && \
                                                              ((i2s_audiosample) != I2S_AUDIOSAMPLE_48K)&& ((i2s_audiosample) != I2S_AUDIOSAMPLE_96K) && \
                                                              ((i2s_audiosample) != I2S_AUDIOSAMPLE_192K))
/* check SPI i2s frameformat */
#define NOT_SPI_I2S_FRAMEFORMAT(i2s_frameformat)             (((i2s_frameformat) != I2S_FRAMEFORMAT_DT16B_CH16B) && ((i2s_frameformat) != I2S_FRAMEFORMAT_DT16B_CH32B) && \
                                                              ((i2s_frameformat) != I2S_FRAMEFORMAT_DT24B_CH32B) && ((i2s_frameformat) != I2S_FRAMEFORMAT_DT32B_CH32B))
/* check SPI i2s mckout */
#define NOT_SPI_I2S_MCKOUT(i2s_mckout)                       (((i2s_mckout) != I2S_MCKOUT_ENABLE) && ((i2s_mckout) != I2S_MCKOUT_DISABLE))
/* check SPI nss id */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_SPI_NSS_ID(spi_nss_id)                           ((spi_nss_id) != (SPI_NSS_SELECT_0) && (spi_nss_id) != (SPI_NSS_SELECT_1) && \
                                                              (spi_nss_id) != (SPI_NSS_SELECT_2) && (spi_nss_id) != (SPI_NSS_SELECT_3) && \
                                                              (spi_nss_id) != (SPI_NSS_SELECT_4) && (spi_nss_id) != (SPI_NSS_SELECT_5) && \
                                                              (spi_nss_id) != (SPI_NSS_SELECT_6) && (spi_nss_id) != (SPI_NSS_SELECT_7))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#ifdef GD32A711X_A712X
#define NOT_SPI_NSS_ID(spi_nss_id)                           ((spi_nss_id) != (SPI_NSS_SELECT_0) && (spi_nss_id) != (SPI_NSS_SELECT_1) && \
                                                              (spi_nss_id) != (SPI_NSS_SELECT_2) && (spi_nss_id) != (SPI_NSS_SELECT_3))
#endif /* GD32A711X_A712X */
/* check SPI dma mode */
#define NOT_SPI_DMA_MODE(spi_dma)                            (((spi_dma) != SPI_DMA_TRANSMIT) && ((spi_dma) != SPI_DMA_RECEIVE))
/* check SPI transfer direction */
#define NOT_SPI_TRANS_DIR(transfer_direction)                (((transfer_direction) != SPI_BIDIRECTIONAL_TRANSMIT) && ((transfer_direction) != SPI_BIDIRECTIONAL_RECEIVE))
/* check SPI/I2S frame format error flag */
#define NOT_SPI_FRAME_FORMAT_ERROR_FLAG(flag)                (((flag) != SPI_FLAG_FERR))
/* check SPI data size */
#define NOT_SPI_DATA_SIZE(size)                              (((size) != SPI_DATA_SIZE4) && ((size) != SPI_DATA_SIZE5) && ((size) != SPI_DATA_SIZE6) && \
                                                              ((size) != SPI_DATA_SIZE7) && ((size) != SPI_DATA_SIZE8) && ((size) != SPI_DATA_SIZE9) && \
                                                              ((size) != SPI_DATA_SIZE10) && ((size) != SPI_DATA_SIZE11) && ((size) != SPI_DATA_SIZE12) && \
                                                              ((size) != SPI_DATA_SIZE13) && ((size) != SPI_DATA_SIZE14) && ((size) != SPI_DATA_SIZE15) && \
                                                              ((size) != SPI_DATA_SIZE16) && ((size) != SPI_DATA_SIZE17) && ((size) != SPI_DATA_SIZE18) && \
                                                              ((size) != SPI_DATA_SIZE19) && ((size) != SPI_DATA_SIZE20) && ((size) != SPI_DATA_SIZE21) && \
                                                              ((size) != SPI_DATA_SIZE22) && ((size) != SPI_DATA_SIZE23) && ((size) != SPI_DATA_SIZE24) && \
                                                              ((size) != SPI_DATA_SIZE25) && ((size) != SPI_DATA_SIZE26) && ((size) != SPI_DATA_SIZE27) && \
                                                              ((size) != SPI_DATA_SIZE28) && ((size) != SPI_DATA_SIZE29) && ((size) != SPI_DATA_SIZE30) && \
                                                              ((size) != SPI_DATA_SIZE31) && ((size) != SPI_DATA_SIZE32))
/* check SPI/I2S flag status */
#define NOT_SPI_I2S_FLAG_STATUS(flag)                        (((flag) != SPI_FLAG_RFDR) && ((flag) != SPI_FLAG_TFA) && \
                                                              ((flag) != SPI_FLAG_TXURERR) && ((flag) != SPI_FLAG_CONFERR) && \
                                                              ((flag) != SPI_FLAG_RXORERR) && ((flag) != SPI_FLAG_TRANS) && \
                                                              ((flag) != SPI_FLAG_FERR) && ((flag) != SPI_FLAG_TOF) && \
                                                              ((flag) != I2S_FLAG_CH))
/* check SPI/I2S interrupt */
#define NOT_SPI_I2S_INTERRUPT(interrupt)                     (((interrupt) != SPI_I2S_INT_TFA) && ((interrupt) != SPI_I2S_INT_RFDR) && \
                                                              ((interrupt) != SPI_I2S_INT_ERR) && ((interrupt) != SPI_INT_TO))
/* check SPI/I2S interrupt flag status */
#define NOT_SPI_I2S_INTERRUPT_FLAG_STATUS(flag)              (((flag) != SPI_I2S_INT_FLAG_TFA) && ((flag) != SPI_I2S_INT_FLAG_RFDR) && \
                                                              ((flag) != SPI_I2S_INT_FLAG_RXORERR) && ((flag) != SPI_I2S_INT_FLAG_TXURERR) && \
                                                              ((flag) != SPI_INT_FLAG_TOF) && ((flag) != SPI_INT_FLAG_CONFERR) && \
                                                              ((flag) != SPI_I2S_INT_FLAG_FERR))
/* check SPI sample delay */
#define NOT_SPI_SAMPLE_DELAY_NUM(delay)                      ((delay) > ((uint16_t)0x0FFFU))
/* check SPI NSS pin */
#define NOT_SPI_NSS_PIN(nss_pin)                             ((nss_pin) > ((uint32_t)0x000000FFU))

#endif

/* function declarations */
/* SPI deinitialization and initialization functions */
/* reset SPI and I2S */
void spi_i2s_deinit(uint32_t spi_periph);
/* initialize the parameters of SPI structure with the default values */
void spi_struct_para_init(spi_parameter_struct *spi_struct);
/* initialize SPI parameters */
void spi_init(uint32_t spi_periph, spi_parameter_struct *spi_struct);
/* enable SPI */
void spi_enable(uint32_t spi_periph);
/* disable SPI */
void spi_disable(uint32_t spi_periph);

/* I2S initialization functions */
/* initialize I2S parameter */
void i2s_init(uint32_t i2s_periph, uint32_t i2s_mode, uint32_t i2s_standard, uint32_t i2s_ckpl);
/* configure I2S prescaler */
void i2s_psc_config(uint32_t i2s_periph, uint32_t i2s_audiosample, uint32_t i2s_frameformat,
                    uint32_t i2s_mckout);
/* enable I2S */
void i2s_enable(uint32_t i2s_periph);
/* disable I2S */
void i2s_disable(uint32_t i2s_periph);

/* NSS functions */
/* enable SPI NSS output */
void spi_nss_output_enable(uint32_t spi_periph);
/* disable SPI NSS output */
void spi_nss_output_disable(uint32_t spi_periph);
/* SPI NSS pin high level in software mode */
void spi_nss_internal_high(uint32_t spi_periph);
/* SPI NSS pin low level in software mode */
void spi_nss_internal_low(uint32_t spi_periph);
/* SPI NSS select */
void spi_nss_select(uint32_t spi_periph, uint32_t spi_nss_id);

/* DMA functions */
/* enable SPI DMA */
void spi_dma_enable(uint32_t spi_periph, uint8_t spi_dma);
/* disable SPI DMA */
void spi_dma_disable(uint32_t spi_periph, uint8_t spi_dma);

/* SPI/I2S transfer functions */
/* SPI transmit data */
void spi_i2s_data_transmit(uint32_t spi_periph, uint32_t data);
/* SPI receive data */
uint32_t spi_i2s_data_receive(uint32_t spi_periph);
/* configure SPI bidirectional transfer direction */
void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction);
/* clear TI Mode Format Error flag status */
void spi_i2s_format_error_clear(uint32_t spi_periph, uint32_t flag);

/* SPI data size */
void spi_i2s_data_size(uint32_t spi_periph, uint8_t data_size);
/* SPI fifo loopback mode enable */
void spi_i2s_fifo_loopback_enable(uint32_t spi_periph);
/* SPI fifo loopback mode disable */
void spi_i2s_fifo_loopback_disable(uint32_t spi_periph);

/* RXFIFO current words number */
uint32_t spi_i2s_read_rxlvl_words(uint32_t spi_periph);
/* TXFIFO current words number */
uint32_t spi_i2s_read_txlvl_words(uint32_t spi_periph);

/* SPI CRC functions */
/* set SPI CRC polynomial */
void spi_crc_polynomial_set(uint32_t spi_periph, uint32_t crc_poly);
/* get SPI CRC polynomial */
uint32_t spi_crc_polynomial_get(uint32_t spi_periph);
/* turn on SPI CRC function */
void spi_crc_on(uint32_t spi_periph);
/* turn off SPI CRC function */
void spi_crc_off(uint32_t spi_periph);
/* SPI next data is CRC value */
void spi_crc_next(uint32_t spi_periph);
/* get SPI CRC send value */
uint32_t spi_tx_crc_get(uint32_t spi_periph);

/* SPI TI mode functions */
/* enable SPI TI mode */
void spi_ti_mode_enable(uint32_t spi_periph);
/* disable SPI TI mode */
void spi_ti_mode_disable(uint32_t spi_periph);

/* SPI NSS pulse mode functions */
/* enable SPI NSS pulse mode */
void spi_nssp_mode_enable(uint32_t spi_periph);
/* disable SPI NSS pulse mode */
void spi_nssp_mode_disable(uint32_t spi_periph);

/* quad wire SPI functions */
/* enable quad wire SPI */
void spi_quad_enable(uint32_t spi_periph);
/* disable quad wire SPI */
void spi_quad_disable(uint32_t spi_periph);
/* enable quad wire SPI write */
void spi_quad_write_enable(uint32_t spi_periph);
/* enable quad wire SPI read */
void spi_quad_read_enable(uint32_t spi_periph);

/* flag and interrupt functions */
/* get SPI and I2S flag status */
FlagStatus spi_i2s_flag_get(uint32_t spi_periph, uint32_t flag);
/* enable SPI and I2S interrupt */
void spi_i2s_interrupt_enable(uint32_t spi_periph, uint32_t interrupt);
/* disable SPI and I2S interrupt */
void spi_i2s_interrupt_disable(uint32_t spi_periph, uint32_t interrupt);
/* get SPI and I2S interrupt status */
FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph, uint8_t interrupt);

/* SPI host request configuration functions */
/* SPI configure the SPI_HREQ direction is output */
void spi_hr_output(uint32_t spi_periph);
/* SPI configure the SPI_HREQ direction is input */
void spi_hr_input(uint32_t spi_periph);

/* SPI host request input is the SPI_HREQ pin */
void spi_hrsel_pin(uint32_t spi_periph);
/* SPI host request input is the input trigger */
void spi_hrsel_trigger(uint32_t spi_periph);

/* SPI configures the polatity of the host request pin or trigger is active high */
void spi_hr_high(uint32_t spi_periph);
/* SPI configures the polatity of the host request pin or trigger is active loe */
void spi_hr_low(uint32_t spi_periph);

/* SPI configure host request is enabled */
void spi_hr_enable(uint32_t spi_periph);
/* SPI configure host request is disabled */
void spi_hr_disable(uint32_t spi_periph);

/* NSS polarity configuration */
/* Configure NSS polarity as active high */
void spi_nss_polarity_high(uint32_t spi_periph);
/* Configure NSS polarity as active low */
void spi_nss_polarity_low(uint32_t spi_periph);

/* SPI control signal timing configuration */
/* Configure minimum delay from NSS inactive to NSS active */
void spi_nssnss_delay(uint32_t spi_periph, uint8_t delay);
/* Configure minimum delay from SCK inactive to NSS inactive */
void spi_scknss_delay(uint32_t spi_periph, uint8_t delay);
/* Configure minimum delay from NSS active to SCK active */
void spi_nsssck_delay(uint32_t spi_periph, uint8_t delay);

/* SPI sampling delay function */
/* Enable SPI sampling delay */
void spi_sample_delay_enable(uint32_t spi_periph);
/* Disable SPI sampling delay */
void spi_sample_delay_disable(uint32_t spi_periph);
/* Configure SPI sampling delay compensation time */
void spi_sample_delay_config(uint32_t spi_periph, uint16_t delay);

/* SPI bus idle timeout function */
/* Enable SPI bus idle timeout */
void spi_idle_timeout_enable(uint32_t spi_periph);
/* Disable SPI bus idle timeout */
void spi_idle_timeout_disable(uint32_t spi_periph);
/* Configure SPI bus idle timeout threshold */
void spi_idle_threshold_config(uint32_t spi_periph, uint8_t threshold);
/* Clear SPI idle timeout flag */
void spi_timeout_flag_clear(uint32_t spi_periph);
/* Clear SPI idle timeout interrupt flag */
void spi_timeout_interrupt_flag_clear(uint32_t spi_periph);

/* SPI hardware mode configuration */
/* Enable SPI hardware single-frame mode */
void spi_single_frame_enable(uint32_t spi_periph);
/* Disable SPI hardware single-frame mode */
void spi_single_frame_disable(uint32_t spi_periph);
/* Enable SPI hardware continuous-frame mode */
void spi_continuous_frame_enable(uint32_t spi_periph);
/* Disable SPI hardware continuous-frame mode */
void spi_continuous_frame_disable(uint32_t spi_periph);
/* Configure SPI hardware continuous-frame length */
void spi_continuous_frame_length_config(uint32_t spi_periph, uint16_t length);

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* NSS pin polarity independent configuration function */
/* Configure multiple NSS pins polarity as active high */
void spi_multi_nss_polarity_high(uint32_t spi_periph, uint32_t nss_pin);
/* Configure multiple NSS pins polarity as active low */
void spi_multi_nss_polarity_low(uint32_t spi_periph, uint32_t nss_pin);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#endif /* GD32A7XX_SPI_H */
