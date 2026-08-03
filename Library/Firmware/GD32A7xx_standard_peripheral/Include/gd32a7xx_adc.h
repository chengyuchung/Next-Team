/*!
    \file    gd32a7xx_adc.h
    \brief   definitions for the ADC

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

#ifndef GD32A7XX_ADC_H
#define GD32A7XX_ADC_H

#include "gd32a7xx.h"

/* ADC definitions */
#define ADC0                            ADC_BASE
#define ADC1                            (ADC_BASE + 0x00000800U)
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define ADC2                            (ADC_BASE + 0x00003400U)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* registers definitions */
/* ADC global registers */
#define ADC_CTL(adcx)                   REG32((adcx) + 0x00000000U)                                  /*!< ADC control register */
#define ADC_STAT(adcx)                  REG32((adcx) + 0x00000004U)                                  /*!< ADC status register */
#define ADC_ESTAT(adcx)                 REG32((adcx) + 0x00000008U)                                  /*!< ADC error status register */
#define ADC_WDTx(adcx, x)               REG32((adcx) + (0x0000000CU + (x)*4U))                          /*!< ADC watchdog threshold register(x = 0~3) */
#define ADC_PSMPCFG(adcx)               REG32((adcx) + 0x0000001CU)                                  /*!< ADC presampling time configure register */
#define ADC_CHCFGx(adcx, x)             REG32((adcx) + (0x00000020U + (x)*4U))                          /*!< ADC channel configure register(x = 0~61) */
#define ADC_WDINTF0(adcx)               REG32((adcx) + 0x00000118U)                                  /*!< ADC watchdog interrupt flag register 0 */
#define ADC_WDINTF1(adcx)               REG32((adcx) + 0x0000011CU)                                  /*!< ADC watchdog interrupt flag register 1 */
#define ADC_EDDLY(adcx)                 REG32((adcx) + 0x00000120U)                                  /*!< ADC external decode delay register */
#define ADC_CSDLY(adcx)                 REG32((adcx) + 0x00000124U)                                  /*!< ADC conversion start delay register */
#define ADC_GAINCFG(adcx)               REG32((adcx) + 0x00000128U)                                  /*!< ADC gain configure register */
#define ADC_OFFCFGx(adcx, x)            REG32((adcx) + (0x0000012CU + (x)*4U))                          /*!< ADC offset configure register(x = 0~3) */
#define ADC_SYNCCTL                     REG32(ADC0 + 0x0000013CU)                                    /*!< ADC sync control register(only ADC0) */
/* ADC routine sequence registers */
#define ADC_RCTL(adcx)                  REG32((adcx) + 0x00000200U)                                  /*!< ADC routine sequence control register */
#define ADC_RSTREAM(adcx)               REG32((adcx) + 0x00000204U)                                  /*!< ADC routine sequence stream register */
#define ADC_RCFGx(adcx, x)              REG32((adcx) + (0x00000208U + (x)*4U))                          /*!< ADC routine sequence configure register(x = 0~27) */
#define ADC_RCHINF(adcx)                REG32((adcx) + 0x00000278U)                                  /*!< ADC routine sequence  channel conversion end interrupt flag register */
#define ADC_RCHDATAx(adcx, x)           REG32((adcx) + (0x0000027CU + (x)*4U))                          /*!< ADC routine sequence channel data register(x = 0~27) */
#define ADC_RDATA(adcx)                 REG32((adcx) + 0x000002ECU)                                  /*!< ADC routine sequence data register */
/* ADC inserted sequence registers */
#define ADC_IxCTL(adcx, x)              REG32((adcx) + (0x00000300U + (x)*0x50U))                       /*!< ADC inserted sequence x control register(x = 0~5) */
#define ADC_IxSTREAM(adcx, x)           REG32((adcx) + (0x00000304U + (x)*0x50U))                       /*!< ADC inserted sequence x stream register(x = 0~5) */
#define ADC_IxCFGy(adcx, x, y)          REG32((adcx) + (0x00000308U + (x)*0x50U + (y)*4U))                 /*!< ADC inserted sequence x configure register(x = 0~5, y = 0~3) */
#define ADC_IxCHINTF(adcx, x)           REG32((adcx) + (0x00000318U + (x)*0x50U))                       /*!< ADC inserted sequence x channel conversion end interrupt flag register(x = 0~5) */
#define ADC_IxCHDATAy(adcx, x, y)       REG32((adcx) + (0x0000031CU + (x)*0x50U + (y)*4U))                 /*!< ADC inserted sequence x channel data register y(x = 0~5, y = 0~3) */
#define ADC_IxDATA(adcx, x)             REG32((adcx) + (0x0000032CU + (x)*0x50U))                       /*!< ADC inserted sequence x data register(x = 0~5) */
/* ADC selftest registers */
#define ADC_STSAMPT(adcx)               REG32((adcx) + 0x00000600U)                                  /*!< ADC selftest sample time register */
#define ADC_STINTEN(adcx)               REG32((adcx) + 0x00000604U)                                  /*!< ADC selftest interrupt enable register */
#define ADC_STCFG(adcx)                 REG32((adcx) + 0x00000608U)                                  /*!< ADC selftest configure register */
#define ADC_STSTAT(adcx)                REG32((adcx) + 0x0000060CU)                                  /*!< ADC selftest status register */
#define ADC_STEDATA0(adcx)              REG32((adcx) + 0x00000610U)                                  /*!< ADC selftest error data register 0 */
#define ADC_STEDATA1(adcx)              REG32((adcx) + 0x00000614U)                                  /*!< ADC selftest error data register 1 */
#define ADC_STDATA(adcx)                REG32((adcx) + 0x00000618U)                                  /*!< ADC selftest conversion data register */
#define ADC_SSTWDCFGx(adcx, x)          REG32((adcx) + (0x0000061CU + (x)*4U))                          /*!< ADC watchdog for supply selftest step register(x = 0~2) */
#define ADC_CSTWDCFGx(adcx, x)          REG32((adcx) + (0x00000628U + (x)*4U))                          /*!< ADC watchdog for capacitive selftest step register(x = 0~3) */
#define ADC_DTALTCFG(adcx)              REG32((adcx) + 0x00000638U)                                  /*!< DAC - ADC loop test register */

/* bits definitions */
/* ADC_CTL */
#define ADC_CTL_ADCON                   BIT(0)                                                       /*!< ADC on */
#define ADC_CTL_AVRGEN                  BIT(2)                                                       /*!< averaging function enable */
#define ADC_CTL_AVRGSEL                 BITS(3,5)                                                    /*!< averaging conversion number selection */
#define ADC_CTL_DMA                     BIT(8)                                                       /*!< dma request enable */
#define ADC_CTL_DAL                     BIT(9)                                                       /*!< data alignment */
#define ADC_CTL_OVWIE                   BIT(10)                                                      /*!< sequence overwrite interrupt enable */
#define ADC_CTL_CHOVWIE                 BIT(11)                                                      /*!< channel overwrite interrupt enable */
#define ADC_CTL_OVWEN                   BIT(12)                                                      /*!< overwrite enable */
#define ADC_CTL_DRES                    BITS(13,14)                                                  /*!< ADC data resolution */
#define ADC_CTL_GAINEN                  BIT(15)                                                      /*!< gain mode enable */
#define ADC_CTL_CKAUTO                  BIT(16)                                                      /*!< clock auto off */
#define ADC_CTL_CALMOD                  BIT(18)                                                      /*!< ADC calibration mode */
#define ADC_CTL_CLB                     BIT(19)                                                      /*!< ADC calibration */
#define ADC_CTL_RSTCLB                  BIT(20)                                                      /*!< reset calibration */
#define ADC_CTL_CALNUM                  BITS(21,23)                                                  /*!< calibration times */
#define ADC_CTL_STLK                    BIT(24)                                                      /*!< selftest register lock */
#define ADC_CTL_HPTSVEN                 BIT(30)                                                      /*!< high-precision temperatue sensor enable */
#define ADC_CTL_INREFEN                 BIT(31)                                                      /*!< internal reference voltage enable */

/* ADC_STAT */
#define ADC_STAT_ADCSTAT                BITS(0,2)                                                    /*!< ADC state */
#define ADC_STAT_ACTSQ                  BITS(3,5)                                                    /*!< active sequence status */
#define ADC_STAT_ACTST                  BIT(6)                                                       /*!< active self test status */
#define ADC_STAT_ACTCH                  BITS(8,13)                                                   /*!< active channel status */
#define ADC_STAT_EORC                   BIT(16)                                                      /*!< end of routine sequence conversion */
#define ADC_STAT_EOI0C                  BIT(17)                                                      /*!< end of inserted sequence 0 conversion */
#define ADC_STAT_EOI1C                  BIT(18)                                                      /*!< end of inserted sequence 1 conversion */
#define ADC_STAT_EOI2C                  BIT(19)                                                      /*!< end of inserted sequence 2 conversion */
#define ADC_STAT_EOI3C                  BIT(20)                                                      /*!< end of inserted sequence 3 conversion */
#define ADC_STAT_EOI4C                  BIT(21)                                                      /*!< end of inserted sequence 4 conversion */
#define ADC_STAT_EOI5C                  BIT(22)                                                      /*!< end of inserted sequence 5 conversion */
#define ADC_STAT_EORCHC                 BIT(24)                                                      /*!< end of routine sequence channel conversion */
#define ADC_STAT_EOI0CHC                BIT(25)                                                      /*!< end of inserted sequence 0 channel conversion */
#define ADC_STAT_EOI1CHC                BIT(26)                                                      /*!< end of inserted sequence 1 channel conversion */
#define ADC_STAT_EOI2CHC                BIT(27)                                                      /*!< end of inserted sequence 2 channel conversion */
#define ADC_STAT_EOI3CHC                BIT(28)                                                      /*!< end of inserted sequence 3 channel conversion */
#define ADC_STAT_EOI4CHC                BIT(29)                                                      /*!< end of inserted sequence 4 channel conversion */
#define ADC_STAT_EOI5CHC                BIT(30)                                                      /*!< end of inserted sequence 5 channel conversion */

/* ADC_ESTAT */
#define ADC_ESTAT_RSUSPDF               BIT(0)                                                       /*!< routine sequence suspended flag */
#define ADC_ESTAT_RABORTF               BIT(1)                                                       /*!< routine sequence aborted flag */
#define ADC_ESTAT_RTRGE                 BIT(2)                                                       /*!< routine sequence trigger error */
#define ADC_ESTAT_I0SUSPDF              BIT(4)                                                       /*!< inserted sequence 0 suspended flag */
#define ADC_ESTAT_I0ABORTF              BIT(5)                                                       /*!< inserted sequence 0 aborted flag */
#define ADC_ESTAT_I0TRGE                BIT(6)                                                       /*!< inserted sequence 0 trigger error */
#define ADC_ESTAT_I1SUSPDF              BIT(8)                                                       /*!< inserted sequence 1 suspended flag */
#define ADC_ESTAT_I1ABORTF              BIT(9)                                                       /*!< inserted sequence 1 aborted flag */
#define ADC_ESTAT_I1TRGE                BIT(10)                                                      /*!< inserted sequence 1 trigger error */
#define ADC_ESTAT_I2SUSPDF              BIT(12)                                                      /*!< inserted sequence 2 suspended flag */
#define ADC_ESTAT_I2ABORTF              BIT(13)                                                      /*!< inserted sequence 2 aborted flag */
#define ADC_ESTAT_I2TRGE                BIT(14)                                                      /*!< inserted sequence 2 trigger error */
#define ADC_ESTAT_I3SUSPDF              BIT(16)                                                      /*!< inserted sequence 3 suspended flag */
#define ADC_ESTAT_I3ABORTF              BIT(17)                                                      /*!< inserted sequence 3 aborted flag */
#define ADC_ESTAT_I3TRGE                BIT(18)                                                      /*!< inserted sequence 3 trigger error */
#define ADC_ESTAT_I4SUSPDF              BIT(20)                                                      /*!< inserted sequence 4 suspended flag */
#define ADC_ESTAT_I4ABORTF              BIT(21)                                                      /*!< inserted sequence 4 aborted flag */
#define ADC_ESTAT_I4TRGE                BIT(22)                                                      /*!< inserted sequence 4 trigger error */
#define ADC_ESTAT_I5ABORTF              BIT(25)                                                      /*!< inserted sequence 5 aborted flag */
#define ADC_ESTAT_I5TRGE                BIT(26)                                                      /*!< inserted sequence 5 trigger error */
#define ADC_ESTAT_WDE                   BIT(31)                                                      /*!< analog watchdog event flag */

/* ADC_WDTx(x = 0~3) */
#define ADC_WDT_WDLT                    BITS(0,11)                                                   /*!< low threshold for analog watchdog x */
#define ADC_WDT_WDHT                    BITS(16,27)                                                  /*!< high threshold for analog watchdog x */
#define ADC_WDT_WDEIE                   BIT(31)                                                      /*!< analog watchdog x interrupt enable */

/* ADC_PSMPCFG */
#define ADC_PSMPCFG_PSMP                BITS(0,9)                                                    /*!< ADC channel n presampling time */

/* ADC_CHCFGx(x = 0~61) */
#define ADC_CHCFG_WDMSEL                BITS(0,2)                                                    /*!< analog watchdog mode select */
#define ADC_CHCFG_WDSEL                 BITS(3,4)                                                    /*!< ADC channel x analog watchdog selection */
#define ADC_CHCFG_PSMPEN                BIT(16)                                                      /*!< ADC channel x pre-sample enable */
#define ADC_CHCFG_PSMPVSEL              BIT(17)                                                      /*!< ADC channel x pre-sample voltage select */
#define ADC_CHCFG_DISSMP                BIT(18)                                                      /*!< disable channel x sampling */

/* ADC_WDINTF0 */
#define ADC_WDINTF0_WDIF0               BITS(0,31)                                                   /*!< analog watchdog interrupt flag 0 (for channel n, n = 0~31) */

/* ADC_WDINTF1 */
#define ADC_WDINTF1_WDIF1               BITS(0,29)                                                   /*!< analog watchdog interrupt flag 1 (for channel n, n = 32~61) */

/* ADC_EDDLY */
#define ADC_EDDLY_EDDLY                 BITS(0,15)                                                   /*!< external analog multiplexers decode signals delay time */

/* ADC_CSDLY */
#define ADC_CSDLY_CSDLY                 BITS(0,15)                                                   /*!< the delay from trigger to start conversion */
#define ADC_CSDLY_CSDEN                 BITS(16,22)                                                  /*!< the delay from trigger to start conversion enable */

/* ADC_GAINCFG */
#define ADC_GAINCFG_GAIN                BITS(0,13)                                                   /*!< gain factor */

/* ADC_OFFCFGx(x = 0~3) */
#define ADC_OFFCFG_OFFSET               BITS(0,11)                                                   /*!< offset factor */
#define ADC_OFFCFG_OFFCH                BITS(16,21)                                                  /*!< channel selection for the offset x */
#define ADC_OFFCFG_SIGNEN               BIT(29)                                                      /*!< signed data enable */
#define ADC_OFFCFG_OFFPOS               BIT(30)                                                      /*!< positive offset */
#define ADC_OFFCFG_OFFEN                BIT(31)                                                      /*!< offset x enable */

/* ADC_SYNCCTL */
#define ADC_SYNCCTL_SYNCM               BITS(0,4)                                                    /*!< ADC sync mode */

/* ADC_RCTL */
#define ADC_RCTL_RL                     BITS(0,5)                                                    /*!< routine sequence length */
#define ADC_RCTL_RMODE                  BIT(8)                                                       /*!< routine sequence conversion mode */
#define ADC_RCTL_SWRCST                 BIT(9)                                                       /*!< software start on routine channel */
#define ADC_RCTL_RTRGEIE                BIT(10)                                                      /*!< interrupt enable for RTRGE */
#define ADC_RCTL_RRESTART               BIT(11)                                                      /*!< restart routine sequence when the routine sequence be suspended */
#define ADC_RCTL_RABORT                 BIT(12)                                                      /*!< abort routine sequence current conversion */
#define ADC_RCTL_RDDM                   BIT(13)                                                      /*!< routine sequence DMA disable mode */
#define ADC_RCTL_EORCIE                 BIT(15)                                                      /*!< interrupt enable for EORC */
#define ADC_RCTL_ETMRC                  BITS(16,17)                                                  /*!< external trigger mode for routine sequence */

/* ADC_RSTREAM */
#define ADC_RSTREAM_RSTREAMCNT          BITS(0,15)                                                   /*!< routine sequence stream counter value */
#define ADC_RSTREAM_RSTREAMEN           BIT(16)                                                      /*!< routine sequence stream conversion enable */
#define ADC_RSTREAM_RSTREAMAREN         BIT(17)                                                      /*!< routine sequence stream counter value reload enable */
#define ADC_RSTREAM_RSTREAMIE           BIT(18)                                                      /*!< routine sequence stream interrupt enable */
#define ADC_RSTREAM_RSTREAMF            BIT(31)                                                      /*!< routine sequence stream flag */

/* ADC_RCFGx(x = 0~27) */
#define ADC_RCFG_RSQ                    BITS(0,5)                                                    /*!< the channel number n(n = 0~61) is written to these bits to select a channel as the xth conversion in the routine sequence */
#define ADC_RCFG_RCHIE                  BIT(8)                                                       /*!< routine sequence channel x interrupt enables for RCHIF or EORCHC */
#define ADC_RCFG_RCHDMAEN               BIT(9)                                                       /*!< routine sequence channel x DMA request enable */
#define ADC_RCFG_RSMP                   BITS(16,25)                                                  /*!< routine sequence channel x sample time */

/* ADC_RCHINF */
#define ADC_RCHINF_RCHIF                BITS(0,27)                                                   /*!< routine sequence channel conversion end interrupt flag */

/* ADC_RCHDATAx(x = 0~27) */
#define ADC_RCHDATA_RCHDATA             BITS(0,15)                                                   /*!< routine sequence channel x conversion data */
#define ADC_RCHDATA_RCH                 BITS(16,21)                                                  /*!< routine sequence channel x */
#define ADC_RCHDATA_RCHOVWF             BIT(24)                                                      /*!< routine sequence channel x conversion data overwritten flag */
#define ADC_RCHDATA_RCHAVLB             BIT(25)                                                      /*!< routine sequence channel x conversion data available */

/* ADC_RDATA */
#define ADC_RDATA_RDATA                 BITS(0,15)                                                   /*!< routine sequence conversion result */
#define ADC_RDATA_RSQCH                 BITS(16,21)                                                  /*!< routine sequence channel */
#define ADC_RDATA_ROVWF                 BIT(24)                                                      /*!< routine sequence conversion data overwritten flag */
#define ADC_RDATA_RAVLB                 BIT(25)                                                      /*!< routine sequence conversion data available */
#define ADC_RDATA_RDMAEN                BIT(31)                                                      /*!< routine sequence DMA request enable */

/* ADC_IxCTL(x = 0~5) */
#define ADC_ICTL_IL                     BITS(0,1)                                                    /*!< inserted sequence length */
#define ADC_ICTL_SWICST                 BIT(9)                                                       /*!< software start on inserted channel */
#define ADC_ICTL_ITRGEIE                BIT(10)                                                      /*!< interrupt enable for ITRGE */
#define ADC_ICTL_IRESTART               BIT(11)                                                      /*!< restart inserted sequence m when inserted sequence m be suspended */
#define ADC_ICTL_IABORT                 BIT(12)                                                      /*!< abort inserted sequence m current conversion */
#define ADC_ICTL_IDDM                   BIT(13)                                                      /*!< inserted sequence DMA disable mode */
#define ADC_ICTL_IEOCIE                 BIT(15)                                                      /*!< interrupt enable for EOIC */
#define ADC_ICTL_ETMIC                  BITS(16,17)                                                  /*!< external trigger mode for inserted sequence */

/* ADC_IxSTREAM(x = 0~5) */
#define ADC_ISTREAM_ISTREAMCNT          BITS(0,15)                                                   /*!< inserted sequence stream counter value */
#define ADC_ISTREAM_ISTREAMEN           BIT(16)                                                      /*!< inserted sequence stream conversion enable */
#define ADC_ISTREAM_ISTREAMAREN         BIT(17)                                                      /*!< inserted sequence stream counter value reload enable */
#define ADC_ISTREAM_ISTREAMIE           BIT(18)                                                      /*!< inserted sequence stream interrupt enable */
#define ADC_ISTREAM_ISTREAMF            BIT(31)                                                      /*!< inserted sequence stream flag */

/* ADC_IxCFGy(x = 0~5, y = 0~3) */
#define ADC_ICFG_ISQ                    BITS(0,5)                                                    /*!< the channel number y(y = 0~3) is written to these bits to select a channel as the xth conversion in the inserted sequence */
#define ADC_ICFG_ICHIE                  BIT(8)                                                       /*!< inserted sequence x channel interrupt enable for ICHIF or EOImCHC */
#define ADC_ICFG_ICHDMAEN               BIT(9)                                                       /*!< inserted sequence x channel y DMA request enable */
#define ADC_ICFG_ISMP                   BITS(16,25)                                                  /*!< inserted sequence x channel y sample time */

/* ADC_IxCHINTF(x = 0~5) */
#define ADC_ICHINTF_ICHIF               BITS(0,3)                                                    /*!< inserted sequence x end of channel conversion flag */

/* ADC_IxCHDATAy(x = 0~5) */
#define ADC_ICHDATA_ICHDATA             BITS(0,15)                                                   /*!< inserted sequence x channel y conversion data */
#define ADC_ICHDATA_ICH                 BITS(16,21)                                                  /*!< inserted sequence x channel y */
#define ADC_ICHDATA_ICHOVWF             BIT(24)                                                      /*!< inserted sequence x channel y conversion data overwritten flag */
#define ADC_ICHDATA_ICHAVLB             BIT(25)                                                      /*!< Inserted sequence x channel y conversion data available */

/* ADC_IxDATA(x = 0~5) */
#define ADC_IDATA_IDATA                 BITS(0,15)                                                   /*!< inserted sequence x conversion data */
#define ADC_IDATA_ISQCH                 BITS(16,21)                                                  /*!< inserted sequence x channel */
#define ADC_IDATA_IOVWF                 BIT(24)                                                      /*!< inserted sequence x conversion data overwritten flag */
#define ADC_IDATA_IAVLB                 BIT(25)                                                      /*!< inserted sequence x conversion data available */
#define ADC_IDATA_IDMAEN                BIT(31)                                                      /*!< inserted sequence x DMA request enable */

/* ADC_STSAMPT */
#define ADC_STSAMPT_SSPT                BITS(0,9)                                                    /*!< sampling time for supply selftest step */
#define ADC_STSAMPT_CSPT                BITS(16,25)                                                  /*!< sampling time for capacitive selftest step */

/* ADC_STINTEN */
#define ADC_STINTEN_FMUSSTEIE           BIT(8)                                                       /*!< interrupt enable for supply self test error SSTxE to FMU */
#define ADC_STINTEN_FMUCSTEIE           BIT(9)                                                       /*!< interrupt enable for capacitive self test error CSTE to FMU */
#define ADC_STINTEN_FMUWDTEIE           BIT(10)                                                      /*!< interrupt enable for watchdog timer error WDTE to FMU */
#define ADC_STINTEN_FMUSTODEIE          BIT(11)                                                      /*!< interrupt enable for self test order error STODE to FMU */
#define ADC_STINTEN_STODEIE             BIT(16)                                                      /*!< interrupt enable for STODE */
#define ADC_STINTEN_WDTEIE              BIT(17)                                                      /*!< interrupt enable for WDTE */
#define ADC_STINTEN_CSTEIE              BIT(19)                                                      /*!< interrupt enable for CSTE */
#define ADC_STINTEN_SST0EIE             BIT(20)                                                      /*!< interrupt enable for SST0E */
#define ADC_STINTEN_SST1EIE             BIT(21)                                                      /*!< interrupt enable for SST1E */
#define ADC_STINTEN_SST2EIE             BIT(22)                                                      /*!< interrupt enable for SST2E */
#define ADC_STINTEN_STEOVWIE            BIT(23)                                                      /*!< interrupt enable for STEOVW */
#define ADC_STINTEN_EOSSTCIE            BIT(24)                                                      /*!< interrupt enable for EOSSTC */
#define ADC_STINTEN_EOCSTCIE            BIT(25)                                                      /*!< interrupt enable for EOCSTC */
#define ADC_STINTEN_EOSTCIE             BIT(26)                                                      /*!< interrupt enable for EOSTC */

/* ADC_STCFG */
#define ADC_STCFG_STSSEL                BITS(0,2)                                                    /*!< capacitive and supply steps select in one shot mode */
#define ADC_STCFG_STMSEL                BITS(8,9)                                                    /*!< self test mode select */
#define ADC_STCFG_STEXER                BITS(16,23)                                                  /*!< self test execution rate */
#define ADC_STCFG_STWDT                 BITS(24,26)                                                  /*!< self test watchdog timer */
#define ADC_STCFG_STEN                  BIT(31)                                                      /*!< self test enable */

/* ADC_STSTAT */
#define ADC_STSTAT_CSTESTP              BITS(0,2)                                                    /*!< error step of capacitive self test */
#define ADC_STSTAT_STODE                BIT(16)                                                      /*!< self test step order error */
#define ADC_STSTAT_WDTE                 BIT(17)                                                      /*!< watchdog timer error */
#define ADC_STSTAT_CSTE                 BIT(19)                                                      /*!< capacitive self test error */
#define ADC_STSTAT_SST0E                BIT(20)                                                      /*!< supply self test step 0 error */
#define ADC_STSTAT_SST1E                BIT(21)                                                      /*!< supply self test step 1 error */
#define ADC_STSTAT_SST2E                BIT(22)                                                      /*!< supply self test step 2 error */
#define ADC_STSTAT_STEOVW               BIT(23)                                                      /*!< self test error overwrite */
#define ADC_STSTAT_EOSSTC               BIT(24)                                                      /*!< end of all supply self test steps conversion */
#define ADC_STSTAT_EOCSTC               BIT(25)                                                      /*!< end of all capacitive self test steps conversion */
#define ADC_STSTAT_EOSTC                BIT(26)                                                      /*!< end of self test conversion */

/* ADC_STEDATA0 */
#define ADC_STEDATA0_SST1EDATA          BITS(0,11)                                                   /*!< error data of supply self test step 1 conversion data */
#define ADC_STEDATA0_SST2EDATA          BITS(16,27)                                                  /*!< error data of supply self test step 2 conversion data */

/* ADC_STEDATA1 */
#define ADC_STEDATA1_CSTEDATA           BITS(0,11)                                                   /*!< error data of capacitive self test step conversion data */
#define ADC_STEDATA1_SST0EDATA          BITS(16,27)                                                  /*!< error data of supply self test step 0 conversion data */

/* ADC_STDATA */
#define ADC_STDATA_STDATA               BITS(0, 11)                                                  /*!< self test conversion data */
#define ADC_STDATA_STSTP                BITS(16, 20)                                                 /*!< self test step */
#define ADC_STDATA_STOVWF               BIT(24)                                                      /*!< self test conversion data overwritten flag */
#define ADC_STDATA_STAVLB               BIT(25)                                                      /*!< self test conversion data available */

/* ADC_SSTWDCFGx(x = 0~2) */
#define ADC_SSTWDCFG_SSTWDLT            BITS(0,11)                                                   /*!< supply self test step 1/2 watchdog low threshold value */
#define ADC_SSTWDCFG_SSTWDHT            BITS(16,27)                                                  /*!< supply self test step 0/1 watchdog high threshold value */
#define ADC_SSTWDCFG_SSTWDTEN           BIT(30)                                                      /*!< self test watchdog timer enable(only ADC_SSTWDCFG0) */
#define ADC_SSTWDCFG_SSTWDEN            BIT(31)                                                      /*!< supply self test step 0/1/2 watchdog enable */

/* ADC_CSTWDCFGx(x = 0~3) */
#define ADC_CSTWDCFG_CSTWDHT0           BITS(0,7)                                                    /*!< capacitive self test step n(n=x*2) watchdog threshold value */
#define ADC_CSTWDCFG_CSTWDEN0           BIT(15)                                                      /*!< capacitive self test step n(n=x*2) watchdog threshold value */
#define ADC_CSTWDCFG_CSTWDHT1           BITS(16,23)                                                  /*!< capacitive self test step n+1(n=x*2) watchdog threshold value */
#define ADC_CSTWDCFG_CSTWDTEN           BIT(30)                                                      /*!< capacitive self test watchdog timer enable(only for ADC_CSTWDCFG3) */
#define ADC_CSTWDCFG_CSTWDEN1           BIT(31)                                                      /*!< capacitive self test step n+1(n=x*2) watchdog threshold value */

/* ADC_DTALTCFG */
#define ADC_DTALTCFG_LTLT               BITS(0,7)                                                    /*!< DAC - ADC looptest low threshold value */
#define ADC_DTALTCFG_DAC0SEL            BIT(14)                                                      /*!< select DAC0_OUT0 as ADC input in DAC to ADC loop test mode */
#define ADC_DTALTCFG_DAC1SEL            BIT(15)                                                      /*!< select DAC1_OUT0 as ADC input in DAC to ADC loop test mode */
#define ADC_DTALTCFG_LTHT               BITS(16,23)                                                  /*!< DAC - ADC loopt est high threshold value */
#define ADC_DTALTCFG_LTE                BIT(28)                                                      /*!< DAC - ADC loopt est error */
#define ADC_DTALTCFG_LTEIE              BIT(29)                                                      /*!< interrupt enable enable for LTE to FMU */
#define ADC_DTALTCFG_LTEN               BIT(30)                                                      /*!< DAC - ADC loop test enable */

/* constants definitions */
/* ADC sequence channel length definitions */
#define RCTL_RL(regval)                                  (BITS(0,4) & ((uint32_t)(regval) << 0))     /*!< ADC routine sequence channel length */
#define ICTL_IL(regval)                                  (BITS(0,1) & ((uint32_t)(regval) << 0))     /*!< ADC inserted sequence channel length */

/* ADC calibration times */
#define CTL_CALNUM(regval)                               (BITS(21,23) & ((uint32_t)(regval) << 21))  /*!< write value to ADC_CTL_CALNUM bit field */
#define ADC_CALIBRATION_NUM1                             CTL_CALNUM(0)                               /*!< calibration 1 time */
#define ADC_CALIBRATION_NUM3                             CTL_CALNUM(1)                               /*!< calibration 3 times */
#define ADC_CALIBRATION_NUM7                             CTL_CALNUM(2)                               /*!< calibration 7 times */
#define ADC_CALIBRATION_NUM15                            CTL_CALNUM(3)                               /*!< calibration 15 times */
#define ADC_CALIBRATION_NUM31                            CTL_CALNUM(4)                               /*!< calibration 31 times */

/* ADC average conversion number definitions */
#define CTL_AVGSEL(regval)                               (BITS(3,5) & ((uint32_t)(regval) << 3))     /*!< write value to ADC_CTL_AVRGSEL bit field */
#define ADC_AVERAGE_2_CONVERSIONS                        CTL_AVGSEL(0)                               /*!< 2 conversion data average */
#define ADC_AVERAGE_4_CONVERSIONS                        CTL_AVGSEL(1)                               /*!< 4 conversion data average */
#define ADC_AVERAGE_8_CONVERSIONS                        CTL_AVGSEL(2)                               /*!< 8 conversion data average */
#define ADC_AVERAGE_16_CONVERSIONS                       CTL_AVGSEL(3)                               /*!< 16 conversion data average */
#define ADC_AVERAGE_32_CONVERSIONS                       CTL_AVGSEL(4)                               /*!< 32 conversion data average */
#define ADC_AVERAGE_64_CONVERSIONS                       CTL_AVGSEL(5)                               /*!< 64 conversion data average */
#define ADC_AVERAGE_128_CONVERSIONS                      CTL_AVGSEL(6)                               /*!< 128 conversion data average */
#define ADC_AVERAGE_256_CONVERSIONS                      CTL_AVGSEL(7)                               /*!< 256 conversion data average */

/* ADC resolution */
#define CTL_DRES(regval)                                 (BITS(13,14) & ((uint32_t)(regval) << 13))  /*!< write value to ADC_CTL_DRES bit field */
#define ADC_RESOLUTION_12B                               CTL_DRES(0)                                 /*!< 12-bit ADC resolution */
#define ADC_RESOLUTION_10B                               CTL_DRES(1)                                 /*!< 10-bit ADC resolution */
#define ADC_RESOLUTION_8B                                CTL_DRES(2)                                 /*!< 8-bit ADC resolution */
#define ADC_RESOLUTION_6B                                CTL_DRES(3)                                 /*!< 6-bit ADC resolution */

/* ADC idle state clock */
#define ADC_CLOCK_IDLE_STATE_ON                          ((uint32_t)0x00000000U)                     /*!< clock on */
#define ADC_CLOCK_IDLE_STATE_OFF                         ADC_CTL_CKAUTO                              /*!< clock automatic off when the ADC in idle state */

/* ADC data alignment */
#define ADC_DATAALIGN_RIGHT                              ((uint32_t)0x00000000U)                     /*!< LSB alignment */
#define ADC_DATAALIGN_LEFT                               ADC_CTL_DAL                                 /*!< MSB alignment */

/* ADC internal channel definitions */
#define ADC_CHANNEL_INTERNAL_VREFINT                     ADC_CTL_INREFEN                             /*!< internal reference voltage vrefint channel */
#define ADC_CHANNEL_INTERNAL_HP_TEMPSENSOR               ADC_CTL_HPTSVEN                             /*!< high-precision temperature sensor channel */

/* ADC calibration mode */
#define ADC_CALIBRATION_OFFSET_MISMATCH                  ((uint32_t)0x00000000U)                     /*!< ADC calibration offset and mismatch mode */
#define ADC_CALIBRATION_OFFSET                           ADC_CTL_CALMOD                              /*!< ADC calibration offset mode */

/* ADC offset configure */
#define ADC_NEGATIVE_OFFSET                              ((uint32_t)0x00000000U)                     /*!< negative offset */
#define ADC_POSITIVE_OFFSET                              ADC_OFFCFG_OFFPOS                           /*!< positive offset */

/* ADC synchronization mode */
#define SYNCCTL_SYNCM(regval)                            (BITS(0,4) & ((uint32_t)(regval) << 0))     /*!< write value to ADC_SYNCCTL_SYNCM bit field */
#define ADC_MODE_FREE                                    SYNCCTL_SYNCM(0)                            /*!< all the ADCs work independently */
#define ADC_DUAL_ROUTINE_PARALLEL_INSERTED_PARALLEL      SYNCCTL_SYNCM(1)                            /*!< ADC0 and ADC1 work in combined routine parallel + inserted parallel mode */
#define ADC_DUAL_ROUTINE_PARALLEL_ROTATION               SYNCCTL_SYNCM(2)                            /*!< ADC0 and ADC1 work in combined routine parallel + trigger rotation mode */
#define ADC_DUAL_INSERTED_PARALLEL                       SYNCCTL_SYNCM(5)                            /*!< ADC0 and ADC1 work in inserted parallel mode */
#define ADC_DUAL_ROUTINE_PARALLEL                        SYNCCTL_SYNCM(6)                            /*!< ADC0 and ADC1 work in routine parallel mode */
#define ADC_DUAL_FOLLOWUP                                SYNCCTL_SYNCM(7)                            /*!< ADC0 and ADC1 work in follow-up mode */
#define ADC_DUAL_TRRIGGER_ROTATION                       SYNCCTL_SYNCM(9)                            /*!< ADC0 and ADC1 work in trigger rotation mode */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define ADC_ALL_ROUTINE_PARALLEL_INSERTED_PARALLEL       SYNCCTL_SYNCM(17)                           /*!< ADC0, ADC1 and ADC2 work in combined routine parallel + inserted parallel mode */
#define ADC_ALL_ROUTINE_PARALLEL_ROTATION                SYNCCTL_SYNCM(18)                           /*!< ADC0, ADC1 and ADC2 work in combined routine parallel + trigger rotation mode */
#define ADC_ALL_INSERTED_PARALLEL                        SYNCCTL_SYNCM(21)                           /*!< ADC0, ADC1 and ADC2 work in inserted parallel mode */
#define ADC_ALL_ROUTINE_PARALLEL                         SYNCCTL_SYNCM(22)                           /*!< ADC0, ADC1 and ADC2 work in routine parallel mode */
#define ADC_ALL_FOLLOWUP                                 SYNCCTL_SYNCM(23)                           /*!< ADC0, ADC1 and ADC2 work in follow-up mode */
#define ADC_ALL_TRRIGGER_ROTATION                        SYNCCTL_SYNCM(25)                           /*!< ADC0, ADC1 and ADC2 work in trigger rotation mode */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* ADC channel analog watchdog selection */
#define ADC_ANALOG_WATCHDOG0                             ((uint32_t)0x00000000U)                     /*!< analog watchdog 0 */
#define ADC_ANALOG_WATCHDOG1                             ((uint32_t)0x00000001U)                     /*!< analog watchdog 1 */
#define ADC_ANALOG_WATCHDOG2                             ((uint32_t)0x00000002U)                     /*!< analog watchdog 2 */
#define ADC_ANALOG_WATCHDOG3                             ((uint32_t)0x00000003U)                     /*!< analog watchdog 3 */

/* ADC analog watchdog mode selection */
#define CHCFG_WDMSEL(regval)                             (BITS(0,2) & ((uint32_t)(regval) << 0))     /*!< write value to ADC_CHCFG_WDMSEL bit field */
#define ADC_ANALOG_WATCHDOG_DISABLE                      CHCFG_WDMSEL(0)                             /*!< analog watchdog disable */
#define ADC_RESULT_WDLT                                  CHCFG_WDMSEL(1)                             /*!< result <= WDLT */
#define ADC_WDLT_RESULT_WDHT                             CHCFG_WDMSEL(2)                             /*!< WDLT < result <= WDHT */
#define ADC_WDHT_RESULT                                  CHCFG_WDMSEL(3)                             /*!< result > WDHT */
#define ADC_WDLT_RESULT                                  CHCFG_WDMSEL(4)                             /*!< result > WDLT */
#define ADC_WDHT_RESULT_WDLT                             CHCFG_WDMSEL(5)                             /*!< result > WDHT or result <= WDLT */
#define ADC_RESULT_WDHT                                  CHCFG_WDMSEL(6)                             /*!< result <= WDHT */

/* ADC pre-sample voltage selection */
#define ADC_PSMPVSEL_VREFN                               ((uint32_t)0x00000000U)                     /*!< pre-sample voltage select VREFN */
#define ADC_PSMPVSEL_VREFP                               ADC_CHCFG_PSMPVSEL                          /*!< pre-sample voltage select VREFP */

/* ADC pre-sample followed */
#define ADC_NO_CONVERSION_AFTER_PRESAMPLE                ((uint32_t)0x00000000U)                     /*!< channel sampling is not disabled, no conversion for the presampled value after presampling */
#define ADC_PRESAMPLE_FOLLOW_CONVERSION                  ADC_CHCFG_DISSMP                            /*!< channel sampling is disabled, conversion for the presampled value after presampling */

/* ADC sequence definitions */
#define ADC_INSERTED_SEQUENCE_NONE                       ((uint32_t)0x000000FFU)                     /*!< none inserted sequence */
#define ADC_ROUTINE_SEQUENCE                             ((uint32_t)0x00000010U)                     /*!< routine sequence */
#define ADC_INSERTED_SEQUENCE0                           ((uint32_t)0x00000000U)                     /*!< inserted sequence 0 */
#define ADC_INSERTED_SEQUENCE1                           ((uint32_t)0x00000001U)                     /*!< inserted sequence 1 */
#define ADC_INSERTED_SEQUENCE2                           ((uint32_t)0x00000002U)                     /*!< inserted sequence 2 */
#define ADC_INSERTED_SEQUENCE3                           ((uint32_t)0x00000003U)                     /*!< inserted sequence 3 */
#define ADC_INSERTED_SEQUENCE4                           ((uint32_t)0x00000004U)                     /*!< inserted sequence 4 */
#define ADC_INSERTED_SEQUENCE5                           ((uint32_t)0x00000005U)                     /*!< inserted sequence 5 */

/* ADC sequence conversion mode */
#define ADC_ONE_SHOT_MODE                                ((uint32_t)0x00000000U)                     /*!< one-shot mode */
#define ADC_CONTINUOUS_MODE                              ADC_RCTL_RMODE                              /*!< continuous mode (only for routine sequence) */

/* ADC recovery sequence way */
#define ADC_RESUME_SEQUENCE                              ((uint32_t)0x00000000U)                     /*!< resume sequence conversion */
#define ADC_RESTART_SEQUENCE                             ADC_RCTL_RRESTART                           /*!< restart sequence conversion */

/* abort sequences current conversion */
#define ADC_SEQUENCE_PROCEED                             ((uint32_t)0x00000000U)                     /*!< adc sequence conversion proceeds */
#define ADC_SEQUENCE_ABORT                               ADC_RCTL_RABORT                             /*!< adc sequence conversion aborted */

/* ADC external trigger definitions */
#define RISCTL_ETMRC(regval)                             (BITS(16,17) & ((uint32_t)(regval) << 16)) /*!< write value to ADC_RCTL/ICTL_ETMRC bit field */
#define ADC_EXTERNAL_TRIGGER_DISABLE                     RISCTL_ETMRC(0)                            /*!< external trigger disable */
#define ADC_EXTERNAL_TRIGGER_RISING_EDGE                 RISCTL_ETMRC(1)                            /*!< rising edge of external trigger */
#define ADC_EXTERNAL_TRIGGER_FALLING_EDGE                RISCTL_ETMRC(2)                            /*!< falling edge of external trigger */
#define ADC_EXTERNAL_TRIGGER_RISING_FALLING_EDGE         RISCTL_ETMRC(3)                            /*!< rising and falling edge of external trigger */

/* delay time from trigger to start conversion enable */
#define CSDLY_CSDEN(regval)                              (BITS(16,22) & ((uint32_t)(regval) << 16))  /*!< write value to ADC_CSDLY_CSDEN bit field */
#define ADC_ALL_TRIGGER_DELAY_DISABLE                    CSDLY_CSDEN(0)                              /*!< all sequences trigger delay disable */
#define ADC_ROUTINE_SEQUENCE_TRIGGER_DELAY               CSDLY_CSDEN(1)                              /*!< routine sequence trigger delay enable */
#define ADC_INSERTED_SEQUENCE0_TRIGGER_DELAY             CSDLY_CSDEN(2)                              /*!< inserted sequence 0 trigger delay enable */
#define ADC_INSERTED_SEQUENCE1_TRIGGER_DELAY             CSDLY_CSDEN(4)                              /*!< inserted sequence 1 trigger delay enable */
#define ADC_INSERTED_SEQUENCE2_TRIGGER_DELAY             CSDLY_CSDEN(8)                              /*!< inserted sequence 2 trigger delay enable */
#define ADC_INSERTED_SEQUENCE3_TRIGGER_DELAY             CSDLY_CSDEN(16)                             /*!< inserted sequence 3 trigger delay enable */
#define ADC_INSERTED_SEQUENCE4_TRIGGER_DELAY             CSDLY_CSDEN(32)                             /*!< inserted sequence 4 trigger delay enable */
#define ADC_INSERTED_SEQUENCE5_TRIGGER_DELAY             CSDLY_CSDEN(64)                             /*!< inserted sequence 5 trigger delay enable */

/* ADC flag definitions */
#define ADC_FLAG_ACTST                                   ADC_STAT_ACTST                              /*!< self test ongoing flag */
#define ADC_FLAG_EORC                                    ADC_STAT_EORC                               /*!< end of routine sequence conversion flag */
#define ADC_FLAG_EOI0C                                   ADC_STAT_EOI0C                              /*!< end of inserted sequence 0 conversion flag */
#define ADC_FLAG_EOI1C                                   ADC_STAT_EOI1C                              /*!< end of inserted sequence 1 conversion flag */
#define ADC_FLAG_EOI2C                                   ADC_STAT_EOI2C                              /*!< end of inserted sequence 2 conversion flag */
#define ADC_FLAG_EOI3C                                   ADC_STAT_EOI3C                              /*!< end of inserted sequence 3 conversion flag */
#define ADC_FLAG_EOI4C                                   ADC_STAT_EOI4C                              /*!< end of inserted sequence 4 conversion flag */
#define ADC_FLAG_EOI5C                                   ADC_STAT_EOI5C                              /*!< end of inserted sequence 5 conversion flag */
#define ADC_FLAG_EORCHC                                  ADC_STAT_EORCHC                             /*!< end of routine sequence channel conversion flag */
#define ADC_FLAG_EOI0CHC                                 ADC_STAT_EOI0CHC                            /*!< end of inserted sequence 0 channel conversion flag */
#define ADC_FLAG_EOI1CHC                                 ADC_STAT_EOI1CHC                            /*!< end of inserted sequence 1 channel conversion flag */
#define ADC_FLAG_EOI2CHC                                 ADC_STAT_EOI2CHC                            /*!< end of inserted sequence 2 channel conversion flag */
#define ADC_FLAG_EOI3CHC                                 ADC_STAT_EOI3CHC                            /*!< end of inserted sequence 3 channel conversion flag */
#define ADC_FLAG_EOI4CHC                                 ADC_STAT_EOI4CHC                            /*!< end of inserted sequence 4 channel conversion flag */
#define ADC_FLAG_EOI5CHC                                 ADC_STAT_EOI5CHC                            /*!< end of inserted sequence 5 channel conversion flag */

/* ADC error flag definitions */
#define ADC_FLAG_RSUSPDF                                 ADC_ESTAT_RSUSPDF                           /*!< routine sequence suspended flag */
#define ADC_FLAG_RABORTF                                 ADC_ESTAT_RABORTF                           /*!< routine sequence aborted flag */
#define ADC_FLAG_RTRGE                                   ADC_ESTAT_RTRGE                             /*!< routine sequence trigger error flag */
#define ADC_FLAG_I0SUSPDF                                ADC_ESTAT_I0SUSPDF                          /*!< inserted sequence 0 suspended flag */
#define ADC_FLAG_I0ABORTF                                ADC_ESTAT_I0ABORTF                          /*!< inserted sequence 0 aborted flag */
#define ADC_FLAG_I0TRGE                                  ADC_ESTAT_I0TRGE                            /*!< inserted sequence 0 trigger error flag */
#define ADC_FLAG_I1SUSPDF                                ADC_ESTAT_I1SUSPDF                          /*!< inserted sequence 1 suspended flag */
#define ADC_FLAG_I1ABORTF                                ADC_ESTAT_I1ABORTF                          /*!< inserted sequence 1 aborted flag */
#define ADC_FLAG_I1TRGE                                  ADC_ESTAT_I1TRGE                            /*!< inserted sequence 1 trigger error flag */
#define ADC_FLAG_I2SUSPDF                                ADC_ESTAT_I2SUSPDF                          /*!< inserted sequence 2 suspended flag */
#define ADC_FLAG_I2ABORTF                                ADC_ESTAT_I2ABORTF                          /*!< inserted sequence 2 aborted flag */
#define ADC_FLAG_I2TRGE                                  ADC_ESTAT_I2TRGE                            /*!< inserted sequence 2 trigger error flag */
#define ADC_FLAG_I3SUSPDF                                ADC_ESTAT_I3SUSPDF                          /*!< inserted sequence 3 suspended flag */
#define ADC_FLAG_I3ABORTF                                ADC_ESTAT_I3ABORTF                          /*!< inserted sequence 3 aborted flag */
#define ADC_FLAG_I3TRGE                                  ADC_ESTAT_I3TRGE                            /*!< inserted sequence 3 trigger error flag */
#define ADC_FLAG_I4SUSPDF                                ADC_ESTAT_I4SUSPDF                          /*!< inserted sequence 4 suspended flag */
#define ADC_FLAG_I4ABORTF                                ADC_ESTAT_I4ABORTF                          /*!< inserted sequence 4 aborted flag */
#define ADC_FLAG_I4TRGE                                  ADC_ESTAT_I4TRGE                            /*!< inserted sequence 4 trigger error flag */
#define ADC_FLAG_I5ABORTF                                ADC_ESTAT_I5ABORTF                          /*!< inserted sequence 5 aborted flag */
#define ADC_FLAG_I5TRGE                                  ADC_ESTAT_I5TRGE                            /*!< inserted sequence 5 trigger error flag */
#define ADC_FLAG_WDE                                     ADC_ESTAT_WDE                               /*!< analog watchdog flag */
#define ADC_FLAG_LTE                                     ADC_DTALTCFG_LTE                            /*!< DAC - ADC loop test error flag */

/* ADC interrupt flag definitions */
#define ADC_INT_FLAG_EORC                                ((uint32_t)0x00000000U)                     /*!< end of routine sequence conversion interrupt flag */
#define ADC_INT_FLAG_EOI0C                               ((uint32_t)0x00000001U)                     /*!< end of inserted sequence 0 conversion interrupt flag */
#define ADC_INT_FLAG_EOI1C                               ((uint32_t)0x00000002U)                     /*!< end of inserted sequence 1 conversion interrupt flag */
#define ADC_INT_FLAG_EOI2C                               ((uint32_t)0x00000003U)                     /*!< end of inserted sequence 2 conversion interrupt flag */
#define ADC_INT_FLAG_EOI3C                               ((uint32_t)0x00000004U)                     /*!< end of inserted sequence 3 conversion interrupt flag */
#define ADC_INT_FLAG_EOI4C                               ((uint32_t)0x00000005U)                     /*!< end of inserted sequence 4 conversion interrupt flag */
#define ADC_INT_FLAG_EOI5C                               ((uint32_t)0x00000006U)                     /*!< end of inserted sequence 5 conversion interrupt flag */
#define ADC_INT_FLAG_EORCHC                              ((uint32_t)0x00000007U)                     /*!< end of routine sequence channel conversion interrupt flag */
#define ADC_INT_FLAG_EOI0CHC                             ((uint32_t)0x00000008U)                     /*!< end of inserted sequence 0 channel conversion interrupt flag */
#define ADC_INT_FLAG_EOI1CHC                             ((uint32_t)0x00000009U)                     /*!< end of inserted sequence 1 channel conversion interrupt flag */
#define ADC_INT_FLAG_EOI2CHC                             ((uint32_t)0x0000000AU)                     /*!< end of inserted sequence 2 channel conversion interrupt flag */
#define ADC_INT_FLAG_EOI3CHC                             ((uint32_t)0x0000000BU)                     /*!< end of inserted sequence 3 channel conversion interrupt flag */
#define ADC_INT_FLAG_EOI4CHC                             ((uint32_t)0x0000000CU)                     /*!< end of inserted sequence 4 channel conversion interrupt flag */
#define ADC_INT_FLAG_EOI5CHC                             ((uint32_t)0x0000000DU)                     /*!< end of inserted sequence 5 channel conversion interrupt flag */
#define ADC_INT_FLAG_RTRGE                               ((uint32_t)0x0000000EU)                     /*!< routine sequence trigger error interrupt flag */
#define ADC_INT_FLAG_I0TRGE                              ((uint32_t)0x0000000FU)                     /*!< inserted sequence 0 trigger error interrupt flag */
#define ADC_INT_FLAG_I1TRGE                              ((uint32_t)0x00000010U)                     /*!< inserted sequence 1 trigger error interrupt flag */
#define ADC_INT_FLAG_I2TRGE                              ((uint32_t)0x00000011U)                     /*!< inserted sequence 2 trigger error interrupt flag */
#define ADC_INT_FLAG_I3TRGE                              ((uint32_t)0x00000012U)                     /*!< inserted sequence 3 trigger error interrupt flag */
#define ADC_INT_FLAG_I4TRGE                              ((uint32_t)0x00000013U)                     /*!< inserted sequence 4 trigger error interrupt flag */
#define ADC_INT_FLAG_I5TRGE                              ((uint32_t)0x00000014U)                     /*!< inserted sequence 5 trigger error interrupt flag */
#define ADC_INT_FLAG_LTE                                 ((uint32_t)0x00000015U)                     /*!< DAC - ADC loop test error interrupt flag */

/* ADC state definitions */
#define STAT_ADCSTAT(regval)                             (BITS(0,2) & ((uint32_t)(regval) << 0))     /*!< write value to ADC_STAT_ADCSTAT bit field */
#define ADC_STATE_IDLE                                   STAT_ADCSTAT(0)                             /*!< ADC not working */
#define ADC_STATE_WAIT                                   STAT_ADCSTAT(1)                             /*!< ADC in conversion start delay state */
#define ADC_STATE_PSAMP                                  STAT_ADCSTAT(2)                             /*!< ADC in presampling state */
#define ADC_STATE_EDDLY                                  STAT_ADCSTAT(3)                             /*!< ADC in external decode signals delay state */
#define ADC_STATE_SAMP                                   STAT_ADCSTAT(4)                             /*!< ADC in sampling state */
#define ADC_STATE_CONV                                   STAT_ADCSTAT(5)                             /*!< ADC in converting state */

/* ADC interrupt definitions */
#define ADC_INT_RTRGEIE                                  ((uint32_t)0x00000000U)                     /*!< routine sequence trigger error interrupt */
#define ADC_INT_EORCIE                                   ((uint32_t)0x00000001U)                     /*!< routine sequence end conversion interrupt */
#define ADC_INT_RSTREAMIE                                ((uint32_t)0x00000002U)                     /*!< routine sequence stream mode interrupt */
#define ADC_INT_ITRGEIE                                  ((uint32_t)0x00000003U)                     /*!< inserted sequence trigger error interrupt */
#define ADC_INT_IEOCIE                                   ((uint32_t)0x00000004U)                     /*!< inserted sequence end conversion interrupt */
#define ADC_INT_ISTREAMIE                                ((uint32_t)0x00000005U)                     /*!< inserted sequence stream mode interrupt */
#define ADC_INT_ANALOG_WATCHDOG0                         ((uint32_t)0x00000006U)                     /*!< analog watchdog 0 interrupt */
#define ADC_INT_ANALOG_WATCHDOG1                         ((uint32_t)0x00000007U)                     /*!< analog watchdog 1 interrupt */
#define ADC_INT_ANALOG_WATCHDOG2                         ((uint32_t)0x00000008U)                     /*!< analog watchdog 2 interrupt */
#define ADC_INT_ANALOG_WATCHDOG3                         ((uint32_t)0x00000009U)                     /*!< analog watchdog 3 interrupt */
#define ADC_INT_LOOPTEST                                 ((uint32_t)0x0000000AU)                     /*!< DAC to ADC loop test error interrupt */
#define ADC_INT_OVERWRITE                                ((uint32_t)0x0000000BU)                     /*!< sequence overwrite interrupt */
#define ADC_INT_CHOVERWRITE                              ((uint32_t)0x0000000CU)                     /*!< channel overwrite interrupt interrupt */

/* ADC self test step definitions */
#define STCFG_STSSEL(regval)                             (BITS(0,2) & ((uint32_t)(regval) << 0))     /*!< write value to ADC_STCFG_STSSEL bit field */
#define ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP0             STCFG_STSSEL(0)                             /*!< for supply or capacitive self test step 0 */
#define ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP1             STCFG_STSSEL(1)                             /*!< for supply or capacitive self test step 1 */
#define ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP2             STCFG_STSSEL(2)                             /*!< for supply or capacitive self test step 2 */
#define ADC_SELFTEST_CAPACITIVE_STEP3                    STCFG_STSSEL(3)                             /*!< for capacitive self test step 3 */
#define ADC_SELFTEST_CAPACITIVE_STEP4                    STCFG_STSSEL(4)                             /*!< for capacitive self test step 4 */
#define ADC_SELFTEST_CAPACITIVE_STEP5                    STCFG_STSSEL(5)                             /*!< for capacitive self test step 5 */
#define ADC_SELFTEST_CAPACITIVE_STEP6                    STCFG_STSSEL(6)                             /*!< for capacitive self test step 6 */
#define ADC_SELFTEST_CAPACITIVE_STEP7                    STCFG_STSSEL(7)                             /*!< for capacitive self test step 7 */

/* ADC self test mode definitions */
#define STCFG_STMSEL(regval)                             (BITS(8,9) & ((uint32_t)(regval) << 8))     /*!< write value to ADC_STCFG_STMSEL bit field */
#define ADC_SELFTEST_SUPPLY                              STCFG_STMSEL(0)                             /*!< supply self test */
#define ADC_SELFTEST_CAPACITIVE                          STCFG_STMSEL(2)                             /*!< capacitive self test */
#define ADC_SELFTEST_SUPPLY_CAPACITIVE                   STCFG_STMSEL(3)                             /*!< supply and capacitive self test */

/* ADC self test error data definitions */
#define ADC_SELFTEST_SUPPLY_STEP0_DATA                   ((uint32_t)0x00000000U)                     /*!< error data of supply self test step 0 */
#define ADC_SELFTEST_SUPPLY_STEP1_DATA                   ((uint32_t)0x00000001U)                     /*!< error data of supply self test step 1 */
#define ADC_SELFTEST_SUPPLY_STEP2_DATA                   ((uint32_t)0x00000002U)                     /*!< error data of supply self test step 2 */
#define ADC_SELFTEST_CAPACITIVE_STEP_DATA                ((uint32_t)0x00000003U)                     /*!< error data of capacitive self test step */

/* ADC self test watchdog timer definitions */
#define STCFG_STWDT(regval)                              (BITS(24,26) & ((uint32_t)(regval) << 24))  /*!< write value to ADC_STCFG_STWDT bit field */
#define ADC_SELFTEST_TIME_0_1MS                          STCFG_STWDT(0)                              /*!< about 0.1ms at 15MHz ADC clock frequency */
#define ADC_SELFTEST_TIME_0_5MS                          STCFG_STWDT(1)                              /*!< about 0.5ms at 15MHz ADC clock frequency */
#define ADC_SELFTEST_TIME_1MS                            STCFG_STWDT(2)                              /*!< about 1ms at 15MHz ADC clock frequency */
#define ADC_SELFTEST_TIME_2MS                            STCFG_STWDT(3)                              /*!< about 2ms at 15MHz ADC clock frequency */
#define ADC_SELFTEST_TIME_5MS                            STCFG_STWDT(4)                              /*!< about 5ms at 15MHz ADC clock frequency */
#define ADC_SELFTEST_TIME_10MS                           STCFG_STWDT(5)                              /*!< about 10ms at 15MHz ADC clock frequency */
#define ADC_SELFTEST_TIME_20MS                           STCFG_STWDT(6)                              /*!< about 20ms at 15MHz ADC clock frequency */
#define ADC_SELFTEST_TIME_50MS                           STCFG_STWDT(7)                              /*!< about 50ms at 15MHz ADC clock frequency */

/* ADC self test register lock */
#define ADC_SELFTEST_REGISTER_UNLOCK                     ((uint32_t)0x00000000U)                     /*!< self test registers unlock */
#define ADC_SELFTEST_REGISTER_LOCK                       ADC_CTL_STLK                                /*!< self test registers lock */

/* DAC-ADC looptest definitions */
#define NO_DAC_SELECT                                    ((uint32_t)0x00000000U)                     /*!< do not select DAC */
#define DAC0_SELECT                                      ADC_DTALTCFG_DAC0SEL                        /*!< select DAC0_OUT0 as ADC input */
#define DAC1_SELECT                                      ADC_DTALTCFG_DAC1SEL                        /*!< select DAC1_OUT0 as ADC input */

/* ADC self test flag definitions */
#define ADC_SELFTEST_FLAG_STODE                          ADC_STSTAT_STODE                            /*!< self test step order error flag */
#define ADC_SELFTEST_FLAG_WDTE                           ADC_STSTAT_WDTE                             /*!< self test watchdog timer error flag */
#define ADC_SELFTEST_FLAG_CSTE                           ADC_STSTAT_CSTE                             /*!< self test capacitive error flag */
#define ADC_SELFTEST_FLAG_SSTE0                          ADC_STSTAT_SST0E                            /*!< self test supply step 0 error flag */
#define ADC_SELFTEST_FLAG_SSTE1                          ADC_STSTAT_SST1E                            /*!< self test supply step 1 error flag */
#define ADC_SELFTEST_FLAG_SSTE2                          ADC_STSTAT_SST2E                            /*!< self test supply step 2 error flag */
#define ADC_SELFTEST_FLAG_STEOVW                         ADC_STSTAT_STEOVW                           /*!< self test error overwrtie flag (SST2E, SST1E, SST0E, CERR bit)  */
#define ADC_SELFTEST_FLAG_EOSSTC                         ADC_STSTAT_EOSSTC                           /*!< end of all supply self test steps conversion flag */
#define ADC_SELFTEST_FLAG_EOCSTC                         ADC_STSTAT_EOCSTC                           /*!< end of all capacitive self test steps conversion */
#define ADC_SELFTEST_FLAG_EOSTC                          ADC_STSTAT_EOSTC                            /*!< end of self test conversion */

/* ADC self test interrupt definitions */
#define ADC_SELFTEST_INT_FMUSSTEIE                       ADC_STINTEN_FMUSSTEIE                       /*!< interrupt for supply self test error SSTxE to FMU */
#define ADC_SELFTEST_INT_FMUCSTEIE                       ADC_STINTEN_FMUCSTEIE                       /*!< interrupt for capacitive self test error CSTE to FMU */
#define ADC_SELFTEST_INT_FMUWDTEIE                       ADC_STINTEN_FMUWDTEIE                       /*!< interrupt for watchdog timer error WDTE to FMU */
#define ADC_SELFTEST_INT_FMUSTODEIE                      ADC_STINTEN_FMUSTODEIE                      /*!< interrupt for self test sequence error STODE to FMU */
#define ADC_SELFTEST_INT_STODEIE                         ADC_STINTEN_STODEIE                         /*!< interrupt for self test step order error */
#define ADC_SELFTEST_INT_WDTEIE                          ADC_STINTEN_WDTEIE                          /*!< interrupt for watchdog timer error */
#define ADC_SELFTEST_INT_CSTEIE                          ADC_STINTEN_CSTEIE                          /*!< interrupt for capacitive self test error */
#define ADC_SELFTEST_INT_SSTEIE0                         ADC_STINTEN_SST0EIE                         /*!< interrupt for supply self test step 0 error */
#define ADC_SELFTEST_INT_SSTEIE1                         ADC_STINTEN_SST1EIE                         /*!< interrupt for supply self test step 1 error */
#define ADC_SELFTEST_INT_SSTEIE2                         ADC_STINTEN_SST2EIE                         /*!< interrupt for supply self test step 2 error */
#define ADC_SELFTEST_INT_STEOVWIE                        ADC_STINTEN_STEOVWIE                        /*!< interrupt for self test error(SERR2, SERR1, SERR0, CERR) be overwrite */
#define ADC_SELFTEST_INT_EOSSTCIE                        ADC_STINTEN_EOSSTCIE                        /*!< interrupt for all supply selftest end */
#define ADC_SELFTEST_INT_EOCSTCIE                        ADC_STINTEN_EOCSTCIE                        /*!< interrupt for all capacitive self test end */
#define ADC_SELFTEST_INT_EOSTCIE                         ADC_STINTEN_EOSTCIE                         /*!< interrupt for all self test end */

/* ADC self test interrupt flag definitions */
#define ADC_SELFTEST_INT_FLAG_STODE                      ADC_STSTAT_STODE                            /*!< self test step order interrupt flag */
#define ADC_SELFTEST_INT_FLAG_WDTE                       ADC_STSTAT_WDTE                             /*!< self test watchdog timer error interrupt flag */
#define ADC_SELFTEST_INT_FLAG_CSTE                       ADC_STSTAT_CSTE                             /*!< self test capacitive error interrupt flag */
#define ADC_SELFTEST_INT_FLAG_SSTE0                      ADC_STSTAT_SST0E                            /*!< self test supply step 0 error interrupt flag */
#define ADC_SELFTEST_INT_FLAG_SSTE1                      ADC_STSTAT_SST1E                            /*!< self test supply step 1 error interrupt flag */
#define ADC_SELFTEST_INT_FLAG_SSTE2                      ADC_STSTAT_SST2E                            /*!< self test supply step 2 error interrupt flag */
#define ADC_SELFTEST_INT_FLAG_STEOVW                     ADC_STSTAT_STEOVW                           /*!< self test error overwrtie interrupt flag (SST2E, SST1E, SST0E, CERR bit)  */
#define ADC_SELFTEST_INT_FLAG_EOSSTC                     ADC_STSTAT_EOSSTC                           /*!< end of all supply self test steps conversion interrupt flag */
#define ADC_SELFTEST_INT_FLAG_EOCSTC                     ADC_STSTAT_EOCSTC                           /*!< end of all capacitive self test steps conversion interrupt flag */
#define ADC_SELFTEST_INT_FLAG_EOSTC                      ADC_STSTAT_EOSTC                            /*!< end of self test conversion interrupt flag */

/* the reset value of ADC registers */
#define ADC_RESET_VALUE                                  ((uint32_t)0x00000000U)                     /*!< the reset value of register */
#define ADC_STAT_RESET_VALUE                             ((uint32_t)0x00003F00U)                     /*!< the reset value of ADC_STAT register */
#define ADC_SSTWDCFG0_RESET_VALUE                        ((uint32_t)0x00100000U)                     /*!< the reset value of ADC_SSTWDCFG0 register */
#define ADC_SSTWDCFG1_RESET_VALUE                        ((uint32_t)0x07680348U)                     /*!< the reset value of ADC_SSTWDCFG1 register */
#define ADC_SSTWDCFG2_RESET_VALUE                        ((uint32_t)0x00000FEFU)                     /*!< the reset value of ADC_SSTWDCFG2 register */
#define ADC_CSTWDCFGx_RESET_VALUE                        ((uint32_t)0x00300030U)                     /*!< the reset value of ADC_CSTWDCFGx(x = 0..2) register */
#define ADC_CSTWDCFG3_RESET_VALUE                        ((uint32_t)0x000C0018U)                     /*!< the reset value of ADC_CSTWDCFG3 register */


/* constants definitions */
/* break parameter struct definitions */
typedef struct {
    uint32_t time;                                                              /*!< ADC presample time, it can be 0~638 */
    uint32_t volselect;                                                         /*!< voltage select */
    uint32_t follow;                                                            /*!< controls whether to convert the presampled value after presampling */
    ControlStatus enable;                                                       /*!< presample enable  */
} adc_presample_parameter_struct;
/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check peripherals */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_ADC_periph(adc_periph)                       (((adc_periph) != ADC0) && ((adc_periph) != ADC1) && ((adc_periph) != ADC2))
#else
#define NOT_ADC_periph(adc_periph)                       (((adc_periph) != ADC0) && ((adc_periph) != ADC1))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* check data alignment */
#define NOT_ADC_DATA_ALIGNMENT(data_alignment)           (((data_alignment) != ADC_DATAALIGN_RIGHT) && ((data_alignment) != ADC_DATAALIGN_LEFT))

/* check ADC resolution */
#define NOT_ADC_RESOLUTION(resolution)                   (((resolution) != ADC_RESOLUTION_12B) && ((resolution) != ADC_RESOLUTION_10B) && \
                                                         ((resolution) != ADC_RESOLUTION_8B)   && ((resolution) != ADC_RESOLUTION_6B))

/* check ADC modes */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_ADC_mode(mode)                               (((mode) != ADC_MODE_FREE)                     && ((mode) != ADC_DUAL_ROUTINE_PARALLEL_INSERTED_PARALLEL) && \
                                                         ((mode) != ADC_DUAL_ROUTINE_PARALLEL_ROTATION) && ((mode) != ADC_DUAL_INSERTED_PARALLEL) && \
                                                         ((mode) != ADC_DUAL_ROUTINE_PARALLEL)          && ((mode) != ADC_DUAL_FOLLOWUP) && \
                                                         ((mode) != ADC_DUAL_TRRIGGER_ROTATION)         && ((mode) != ADC_ALL_ROUTINE_PARALLEL_INSERTED_PARALLEL) && \
                                                         ((mode) != ADC_ALL_ROUTINE_PARALLEL_ROTATION)  && ((mode) != ADC_ALL_INSERTED_PARALLEL) && \
                                                         ((mode) != ADC_ALL_ROUTINE_PARALLEL)           && ((mode) != ADC_ALL_FOLLOWUP) && ((mode) != ADC_ALL_TRRIGGER_ROTATION))
#else
#define NOT_ADC_mode(mode)                               (((mode) != ADC_MODE_FREE)                     && ((mode) != ADC_DUAL_ROUTINE_PARALLEL_INSERTED_PARALLEL) && \
                                                         ((mode) != ADC_DUAL_ROUTINE_PARALLEL_ROTATION) && ((mode) != ADC_DUAL_INSERTED_PARALLEL) && \
                                                         ((mode) != ADC_DUAL_ROUTINE_PARALLEL)          && ((mode) != ADC_DUAL_FOLLOWUP) && \
                                                         ((mode) != ADC_DUAL_TRRIGGER_ROTATION))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* check internal channels */
#define NOT_ADC_INTERNAL_CHANNEL(internal_channel)       (((internal_channel) != ADC_CHANNEL_INTERNAL_VREFINT) && ((internal_channel) != ADC_CHANNEL_INTERNAL_HP_TEMPSENSOR))

/* check ENABLE and DISABLE */
#define NOT_ADC_ENABLE_DISABLE(newvalue)                 (((newvalue) != ENABLE)  && ((newvalue) != DISABLE))

/* check ADC calibration mode */
#define NOT_ADC_CALIBRATION_MODE(clb_mode)               (((clb_mode) != ADC_CALIBRATION_OFFSET_MISMATCH) && ((clb_mode) != ADC_CALIBRATION_OFFSET))

/* check calibration number */
#define NOT_ADC_CALIBRATION_NUMBER(cal_num)              (((cal_num) != ADC_CALIBRATION_NUM1) && ((cal_num) != ADC_CALIBRATION_NUM3) && \
                                                         ((cal_num) != ADC_CALIBRATION_NUM7)  && ((cal_num) != ADC_CALIBRATION_NUM15) && \
                                                         ((cal_num) != ADC_CALIBRATION_NUM31))

/* check ADC sequences */
#define NOT_ADC_SEQUENCE(adc_sequence)                   (((adc_sequence) != ADC_ROUTINE_SEQUENCE)  && ((adc_sequence) != ADC_INSERTED_SEQUENCE0) && \
                                                         ((adc_sequence) != ADC_INSERTED_SEQUENCE1) && ((adc_sequence) != ADC_INSERTED_SEQUENCE2) && \
                                                         ((adc_sequence) != ADC_INSERTED_SEQUENCE3) && ((adc_sequence) != ADC_INSERTED_SEQUENCE4) && \
                                                         ((adc_sequence) != ADC_INSERTED_SEQUENCE5))

/* check ADC inserted sequences */
#define NOT_ADC_INSERTED_SEQUENCE(inserted_sequence)     (((inserted_sequence) != ADC_INSERTED_SEQUENCE_NONE)  && ((inserted_sequence) != ADC_INSERTED_SEQUENCE0) && \
                                                         ((inserted_sequence) != ADC_INSERTED_SEQUENCE1) && ((inserted_sequence) != ADC_INSERTED_SEQUENCE2) && \
                                                         ((inserted_sequence) != ADC_INSERTED_SEQUENCE3) && ((inserted_sequence) != ADC_INSERTED_SEQUENCE4) && \
                                                         ((inserted_sequence) != ADC_INSERTED_SEQUENCE5))

/* check routine sequence rank */
#define ADC_ROUTINE_RANK_HIGH                            ((uint32_t)0x0000001BU)
#define NOT_ADC_SEQUENCE_RANK(rank)                      (ADC_ROUTINE_RANK_HIGH < (rank))

/* check average number */
#define NOT_ADC_AVERAGE_NUMBER(aver_num)                 (((aver_num) != ADC_AVERAGE_2_CONVERSIONS)  && ((aver_num) != ADC_AVERAGE_4_CONVERSIONS)  && \
                                                         ((aver_num) != ADC_AVERAGE_8_CONVERSIONS)   && ((aver_num) != ADC_AVERAGE_16_CONVERSIONS) && \
                                                         ((aver_num) != ADC_AVERAGE_32_CONVERSIONS)  && ((aver_num) != ADC_AVERAGE_64_CONVERSIONS) && \
                                                         ((aver_num) != ADC_AVERAGE_128_CONVERSIONS) && ((aver_num) != ADC_AVERAGE_256_CONVERSIONS))

/* check auto clock configure */
#define NOT_ADC_AUTO_CLOCK(ack_cfg)                      (((ack_cfg) != ADC_CLOCK_IDLE_STATE_ON) && ((ack_cfg) != ADC_CLOCK_IDLE_STATE_OFF))

/* check external decode signals delay */
#define ADC_DECODE_SIGNAL_DELAY_HIGH                     ((uint32_t)0x0000FFFFU)
#define NOT_ADC_DECODE_SIGNAL_DELAY(external_delay)      (ADC_DECODE_SIGNAL_DELAY_HIGH < (external_delay))

/* check start conversion delay */
#define ADC_START_CONVERSION_DELAY_HIGH                  ((uint32_t)0x0000FFFFU)
#define NOT_ADC_START_CONVERSION_DELAY(cs_delay)         (ADC_START_CONVERSION_DELAY_HIGH < (cs_delay))

/* check start conversion delay enable sequence */
#define NOT_ADC_DELAY_ENABLE_SEQUENCE(cs_sequence)       (((cs_sequence) != ADC_ROUTINE_SEQUENCE_TRIGGER_DELAY)  && ((cs_sequence) != ADC_INSERTED_SEQUENCE0_TRIGGER_DELAY) && \
                                                         ((cs_sequence) != ADC_INSERTED_SEQUENCE1_TRIGGER_DELAY) && ((cs_sequence) != ADC_INSERTED_SEQUENCE2_TRIGGER_DELAY) && \
                                                         ((cs_sequence) != ADC_INSERTED_SEQUENCE3_TRIGGER_DELAY) && ((cs_sequence) != ADC_INSERTED_SEQUENCE4_TRIGGER_DELAY) && \
                                                         ((cs_sequence) != ADC_INSERTED_SEQUENCE5_TRIGGER_DELAY))

/* check start conversion delay disable sequence */
#define NOT_ADC_DELAY_DISABLE_SEQUENCE(cs_sequence)      (((cs_sequence) != ADC_ROUTINE_SEQUENCE_TRIGGER_DELAY)  && ((cs_sequence) != ADC_INSERTED_SEQUENCE0_TRIGGER_DELAY) && \
                                                         ((cs_sequence) != ADC_INSERTED_SEQUENCE1_TRIGGER_DELAY) && ((cs_sequence) != ADC_INSERTED_SEQUENCE2_TRIGGER_DELAY) && \
                                                         ((cs_sequence) != ADC_INSERTED_SEQUENCE3_TRIGGER_DELAY) && ((cs_sequence) != ADC_INSERTED_SEQUENCE4_TRIGGER_DELAY) && \
                                                         ((cs_sequence) != ADC_INSERTED_SEQUENCE5_TRIGGER_DELAY) && ((cs_sequence) != ADC_ALL_TRIGGER_DELAY_DISABLE))

/* check recovery sequence conversion */
#define NOT_ADC_RECOVERY_CONVERSION(adc_resel)           (((adc_resel) != ADC_RESUME_SEQUENCE) && ((adc_resel) != ADC_RESTART_SEQUENCE))

/* check gain factor */
#define ADC_GAIN_FACTOR_HIGH                             ((uint32_t)0x00003FFFU)
#define NOT_ADC_GAIN_FACTOR(gain_factor)                 (ADC_GAIN_FACTOR_HIGH < (gain_factor))

/* check offset number */
#define ADC_OFFSET_NUMBER_HIGH                           ((uint32_t)0x00000003U)
#define NOT_ADC_OFFSET_NUMBER(off_num)                   (ADC_OFFSET_NUMBER_HIGH < (off_num))

/* check offset factor */
#define ADC_OFFSET_FACTOR_HIGH                           ((uint32_t)0x00000FFFU)
#define NOT_ADC_OFFSET_FACTOR(off_factor)                (ADC_OFFSET_FACTOR_HIGH < (off_factor))

/* check offset channel */
#define ADC_OFFSET_CHANNEL_HIGH                          ((uint32_t)0x0000003DU)
#define NOT_ADC_OFFSET_CHANNEL(off_ch)                   (ADC_OFFSET_CHANNEL_HIGH < (off_ch))

/* check offset positive or negative */
#define NOT_ADC_OFFSET_POSITIVE(off_pos)                 (((off_pos) != ADC_NEGATIVE_OFFSET) && ((off_pos) != ADC_POSITIVE_OFFSET))

/* check ADC channel */
#define ADC_CHANNEL_HIGH                                 ((uint32_t)0x0000003DU)
#define NOT_ADC_CHANNEL(adc_channel)                     (ADC_CHANNEL_HIGH < (adc_channel))
#define NOT_ADC_WATCHDOG_CHANNEL(adc_channel)            ((ADC_CHANNEL_HIGH < (adc_channel)) && (0xFFFFFFFFU != (adc_channel)))

/* check sample/presample/selftest time */
#define ADC_SAMPLE_TIME_HIGH                             ((uint32_t)0x0000027EU)
#define NOT_ADC_SAMPLE_TIME(sample_time)                 (ADC_SAMPLE_TIME_HIGH < (sample_time))

/* check routine sequence conversion mode */
#define NOT_ADC_ROUTINE_MODE(adc_mode)                   (((adc_mode) != ADC_ONE_SHOT_MODE) && ((adc_mode) != ADC_CONTINUOUS_MODE))

/* check external trigger */
#define NOT_ADC_TRIGGER(adc_trigger)                     (((adc_trigger) != ADC_EXTERNAL_TRIGGER_DISABLE)     && ((adc_trigger) != ADC_EXTERNAL_TRIGGER_RISING_EDGE) && \
                                                         ((adc_trigger) != ADC_EXTERNAL_TRIGGER_FALLING_EDGE) && ((adc_trigger) != ADC_EXTERNAL_TRIGGER_RISING_FALLING_EDGE))

/* check voltage select */
#define NOT_ADC_VOLTAGE_SELECT(vol_select)               (((vol_select) != ADC_PSMPVSEL_VREFN) && ((vol_select) != ADC_PSMPVSEL_VREFP))

/* check whether to convert the presampled value after presampling */
#define NOT_ADC_CONVERSION_AFTER_PRESAMPLE(follow)       (((follow) != ADC_NO_CONVERSION_AFTER_PRESAMPLE) && ((follow) != ADC_PRESAMPLE_FOLLOW_CONVERSION))

/* check analog watchdog */
#define NOT_ADC_ANALOG_WATCHDOG(awd_sel)                 (((awd_sel) != ADC_ANALOG_WATCHDOG0) && ((awd_sel) != ADC_ANALOG_WATCHDOG1) && \
                                                         ((awd_sel) != ADC_ANALOG_WATCHDOG2)  && ((awd_sel) != ADC_ANALOG_WATCHDOG3))

/* check analog watchdog event */
#define NOT_ADC_ANALOG_WATCHDOG_EVENT(awd_event)         (((awd_event) != ADC_ANALOG_WATCHDOG_DISABLE) && ((awd_event) != ADC_RESULT_WDLT) && \
                                                         ((awd_event) != ADC_WDLT_RESULT_WDHT)         && ((awd_event) != ADC_WDHT_RESULT) && \
                                                         ((awd_event) != ADC_WDLT_RESULT)              && ((awd_event) != ADC_WDHT_RESULT_WDLT) && ((awd_event) != ADC_RESULT_WDHT))

/* check analog watchdog high/low threshold */
#define ADC_WATCHDOG_THRESHOLD_HIGH                      ((uint32_t)0x00000FFFU)
#define NOT_ADC_WATCHDOG_THRESHOLD(threshold)            (ADC_WATCHDOG_THRESHOLD_HIGH < (threshold))

/* check stream counter value */
#define ADC_STREAM_COUNTER_VALUE_LOW                     ((uint32_t)0x00000001U)
#define ADC_STREAM_COUNTER_VALUE_HIGH                    ((uint32_t)0x00010000U)
#define NOT_ADC_STREAM_COUNTER_VALUE(counter)            ((ADC_STREAM_COUNTER_VALUE_LOW > (counter)) || (ADC_STREAM_COUNTER_VALUE_HIGH < (counter)))


/* check selftest mode */
#define NOT_ADC_SELFTEST_MODE(adc_selftest)               (((adc_selftest) != ADC_SELFTEST_SUPPLY) && ((adc_selftest) != ADC_SELFTEST_CAPACITIVE) && \
                                                          ((adc_selftest) != ADC_SELFTEST_SUPPLY_CAPACITIVE))

/* check supply/capacitive selftest mode */
#define NOT_ADC_SELFTEST_MODE_SUP_CAP(adc_selftest)       (((adc_selftest) != ADC_SELFTEST_SUPPLY) && ((adc_selftest) != ADC_SELFTEST_CAPACITIVE))

/* check selftest steps   */
#define NOT_ADC_SELFTEST_STEP(st_step)                   (((st_step) != ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP0) && ((st_step) != ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP1) && \
                                                         ((st_step) != ADC_SELFTEST_SUPPLY_CAPACITIVE_STEP2)  && ((st_step) != ADC_SELFTEST_CAPACITIVE_STEP3) && \
                                                         ((st_step) != ADC_SELFTEST_CAPACITIVE_STEP4)         && ((st_step) != ADC_SELFTEST_CAPACITIVE_STEP5) && \
                                                         ((st_step) != ADC_SELFTEST_CAPACITIVE_STEP6)         && ((st_step) != ADC_SELFTEST_CAPACITIVE_STEP7))

/* check self test execute rate */
#define ADC_SELFTEST_RATE_LOW                            ((uint32_t)0x00000001U)
#define ADC_SELFTEST_RATE_HIGH                           ((uint32_t)0x00000100U)
#define NOT_ADC_SELFTEST_RATE(st_rate)                   ((ADC_SELFTEST_RATE_LOW > (st_rate)) || (ADC_SELFTEST_RATE_HIGH < (st_rate)))


/* check selftest step data */
#define NOT_ADC_SELFTEST_STEP_DATA(st_data)              (((st_data) != ADC_SELFTEST_SUPPLY_STEP0_DATA) && ((st_data) != ADC_SELFTEST_SUPPLY_STEP1_DATA) && \
                                                         ((st_data) != ADC_SELFTEST_SUPPLY_STEP2_DATA)  && ((st_data) != ADC_SELFTEST_CAPACITIVE_STEP_DATA))

/* check selftest high/low threshold */
#define ADC_SELFTEST_THRESHOLD_HIGH                      ((uint32_t)0x00000FFFU)
#define NOT_ADC_SELFTEST_THRESHOLD(threshold)            (ADC_SELFTEST_THRESHOLD_HIGH < (threshold))

/* check self test safe time */
#define NOT_ADC_SELFTEST_SAFE_TIME(st_time)              (((st_time) != ADC_SELFTEST_TIME_0_1MS) && ((st_time) != ADC_SELFTEST_TIME_0_5MS) && \
                                                         ((st_time) != ADC_SELFTEST_TIME_1MS)    && ((st_time) != ADC_SELFTEST_TIME_2MS)   && \
                                                         ((st_time) != ADC_SELFTEST_TIME_5MS)    && ((st_time) != ADC_SELFTEST_TIME_10MS)  && \
                                                         ((st_time) != ADC_SELFTEST_TIME_20MS)   && ((st_time) != ADC_SELFTEST_TIME_50MS))

/* check self test registers lock state */
#define NOT_ADC_SELFTEST_LOCK(state)                     (((state) != ADC_SELFTEST_REGISTER_UNLOCK) && ((state) != ADC_SELFTEST_REGISTER_LOCK))

/* check loop test threshold value */
#define ADC_LOOPTEST_THRESHOLD_HIGH                      ((uint32_t)0x000000FFU)
#define NOT_ADC_LOOPTEST_THRESHOLD(threshold)            (ADC_LOOPTEST_THRESHOLD_HIGH < (threshold))

/* check loop test DAC select */
#define NOT_ADC_LOOPTEST_DAC(dac_select)                 (((dac_select) != NO_DAC_SELECT) && ((dac_select) != DAC0_SELECT) && ((dac_select) != DAC1_SELECT))

/* check ADC current state */
#define NOT_ADC_STATE(state)                             (((state) != ADC_STATE_IDLE) && ((state) != ADC_STATE_WAIT)  && \
                                                         ((state) != ADC_STATE_PSAMP) && ((state) != ADC_STATE_EDDLY) && \
                                                         ((state) != ADC_STATE_SAMP)  && ((state) != ADC_STATE_CONV))

/* check ADC flags */
#define NOT_ADC_FLAG(flag)                               (((flag) != ADC_FLAG_ACTST)  && ((flag) != ADC_FLAG_EORC)  && \
                                                         ((flag) != ADC_FLAG_EOI0C)   && ((flag) != ADC_FLAG_EOI1C) && \
                                                         ((flag) != ADC_FLAG_EOI2C)   && ((flag) != ADC_FLAG_EOI3C) && \
                                                         ((flag) != ADC_FLAG_EOI4C)   && ((flag) != ADC_FLAG_EOI5C) && \
                                                         ((flag) != ADC_FLAG_EORCHC)  && ((flag) != ADC_FLAG_EOI0CHC) && \
                                                         ((flag) != ADC_FLAG_EOI1CHC) && ((flag) != ADC_FLAG_EOI2CHC) && \
                                                         ((flag) != ADC_FLAG_EOI3CHC) && ((flag) != ADC_FLAG_EOI4CHC) && \
                                                         ((flag) != ADC_FLAG_EOI5CHC))


/* check ADC error flags  */
#define NOT_ADC_ERROR_FLAG(error_flag)                   (((error_flag) != ADC_FLAG_RSUSPDF) && ((error_flag) != ADC_FLAG_RABORTF)  && \
                                                         ((error_flag) != ADC_FLAG_RTRGE)    && ((error_flag) != ADC_FLAG_I0SUSPDF) && \
                                                         ((error_flag) != ADC_FLAG_I0ABORTF) && ((error_flag) != ADC_FLAG_I0TRGE)   && \
                                                         ((error_flag) != ADC_FLAG_I1SUSPDF) && ((error_flag) != ADC_FLAG_I1ABORTF) && \
                                                         ((error_flag) != ADC_FLAG_I1TRGE)   && ((error_flag) != ADC_FLAG_I2SUSPDF) && \
                                                         ((error_flag) != ADC_FLAG_I2ABORTF) && ((error_flag) != ADC_FLAG_I2TRGE)   && \
                                                         ((error_flag) != ADC_FLAG_I3SUSPDF) && ((error_flag) != ADC_FLAG_I3ABORTF) && \
                                                         ((error_flag) != ADC_FLAG_I3TRGE)   && ((error_flag) != ADC_FLAG_I4SUSPDF) && \
                                                         ((error_flag) != ADC_FLAG_I4ABORTF) && ((error_flag) != ADC_FLAG_I4TRGE)   && \
                                                         ((error_flag) != ADC_FLAG_I5ABORTF) && ((error_flag) != ADC_FLAG_I5TRGE)   && \
                                                         ((error_flag) != ADC_FLAG_WDE)      && ((error_flag) != ADC_FLAG_LTE))


/* check ADC interrupt */
#define NOT_ADC_INTERRUPT(interrupt)                     (((interrupt) != ADC_INT_RTRGEIE)         && ((interrupt) != ADC_INT_EORCIE)          && \
                                                         ((interrupt) != ADC_INT_RSTREAMIE)        && ((interrupt) != ADC_INT_ITRGEIE)         && \
                                                         ((interrupt) != ADC_INT_IEOCIE)           && ((interrupt) != ADC_INT_ISTREAMIE)       && \
                                                         ((interrupt) != ADC_INT_ANALOG_WATCHDOG0) && ((interrupt) != ADC_INT_ANALOG_WATCHDOG1) && \
                                                         ((interrupt) != ADC_INT_ANALOG_WATCHDOG2) && ((interrupt) != ADC_INT_ANALOG_WATCHDOG3) && \
                                                         ((interrupt) != ADC_INT_LOOPTEST)         && ((interrupt) != ADC_INT_OVERWRITE)        && \
                                                         ((interrupt) != ADC_INT_CHOVERWRITE))

/* check ADC interrupt flags */
#define NOT_ADC_INTERRUPT_FLAG(int_flag)                 (((int_flag) != ADC_INT_FLAG_EORC)   && ((int_flag) != ADC_INT_FLAG_EOI0C)   && \
                                                         ((int_flag) != ADC_INT_FLAG_EOI1C)   && ((int_flag) != ADC_INT_FLAG_EOI2C)   && \
                                                         ((int_flag) != ADC_INT_FLAG_EOI3C)   && ((int_flag) != ADC_INT_FLAG_EOI4C)   && \
                                                         ((int_flag) != ADC_INT_FLAG_EOI5C)   && ((int_flag) != ADC_INT_FLAG_EORCHC)  && \
                                                         ((int_flag) != ADC_INT_FLAG_EOI0CHC) && ((int_flag) != ADC_INT_FLAG_EOI1CHC) && \
                                                         ((int_flag) != ADC_INT_FLAG_EOI2CHC) && ((int_flag) != ADC_INT_FLAG_EOI3CHC) && \
                                                         ((int_flag) != ADC_INT_FLAG_EOI4CHC) && ((int_flag) != ADC_INT_FLAG_EOI5CHC) && \
                                                         ((int_flag) != ADC_INT_FLAG_RTRGE)   && ((int_flag) != ADC_INT_FLAG_I0TRGE)  && \
                                                         ((int_flag) != ADC_INT_FLAG_I1TRGE)  && ((int_flag) != ADC_INT_FLAG_I2TRGE)  && \
                                                         ((int_flag) != ADC_INT_FLAG_I3TRGE)  && ((int_flag) != ADC_INT_FLAG_I4TRGE)  && \
                                                         ((int_flag) != ADC_INT_FLAG_I5TRGE)  && ((int_flag) != ADC_INT_FLAG_LTE))


/* check ADC ADC self test flags */
#define NOT_ADC_SELFTEST_FLAG(flag)                      (((flag) != ADC_SELFTEST_FLAG_STODE) && ((flag) != ADC_SELFTEST_FLAG_WDTE)   && \
                                                         ((flag) != ADC_SELFTEST_FLAG_CSTE)   && ((flag) != ADC_SELFTEST_FLAG_SSTE0)  && \
                                                         ((flag) != ADC_SELFTEST_FLAG_SSTE1)  && ((flag) != ADC_SELFTEST_FLAG_SSTE2)  && \
                                                         ((flag) != ADC_SELFTEST_FLAG_STEOVW) && ((flag) != ADC_SELFTEST_FLAG_EOSSTC) && \
                                                         ((flag) != ADC_SELFTEST_FLAG_EOCSTC) && ((flag) != ADC_SELFTEST_FLAG_EOSTC))

/* check ADC selftest interrupt */
#define NOT_ADC_SELFTEST_INTERRUPT(interrupt)            (((interrupt) != ADC_SELFTEST_INT_FMUSSTEIE) && ((interrupt) != ADC_SELFTEST_INT_FMUCSTEIE)  && \
                                                         ((interrupt) != ADC_SELFTEST_INT_FMUWDTEIE)  && ((interrupt) != ADC_SELFTEST_INT_FMUSTODEIE) && \
                                                         ((interrupt) != ADC_SELFTEST_INT_STODEIE)    && ((interrupt) != ADC_SELFTEST_INT_WDTEIE)     && \
                                                         ((interrupt) != ADC_SELFTEST_INT_CSTEIE)     && ((interrupt) != ADC_SELFTEST_INT_SSTEIE0)    && \
                                                         ((interrupt) != ADC_SELFTEST_INT_SSTEIE1)    && ((interrupt) != ADC_SELFTEST_INT_SSTEIE2)    && \
                                                         ((interrupt) != ADC_SELFTEST_INT_STEOVWIE)   && ((interrupt) != ADC_SELFTEST_INT_EOSSTCIE)   && \
                                                         ((interrupt) != ADC_SELFTEST_INT_EOCSTCIE)   && ((interrupt) != ADC_SELFTEST_INT_EOSTCIE))

/* check ADC selftest interrupt flags */
#define NOT_ADC_SELFTEST_INTERRUPT_FLAG(int_flag)        (((int_flag) != ADC_SELFTEST_INT_FLAG_STODE) && ((int_flag) != ADC_SELFTEST_INT_FLAG_WDTE)   && \
                                                         ((int_flag) != ADC_SELFTEST_INT_FLAG_CSTE)   && ((int_flag) != ADC_SELFTEST_INT_FLAG_SSTE0)  && \
                                                         ((int_flag) != ADC_SELFTEST_INT_FLAG_SSTE1)  && ((int_flag) != ADC_SELFTEST_INT_FLAG_SSTE2)  && \
                                                         ((int_flag) != ADC_SELFTEST_INT_FLAG_STEOVW) && ((int_flag) != ADC_SELFTEST_INT_FLAG_EOSSTC) && \
                                                         ((int_flag) != ADC_SELFTEST_INT_FLAG_EOCSTC) && ((int_flag) != ADC_SELFTEST_INT_FLAG_EOSTC))
#endif /* FW_DEBUG_ERR_REPORT */

/* calibration timeout */
#define ADC_CALIBRATION_TIMEROUT                         ((uint32_t)0x00FFFFFFU)

/* function declarations */
/* initialization configure */
/* reset ADC */
void adc_deinit(uint32_t adc_periph);
/* enable ADC interface */
void adc_enable(uint32_t adc_periph);
/* disable ADC interface */
void adc_disable(uint32_t adc_periph);
/* configure ADC data alignment */
void adc_data_alignment_config(uint32_t adc_periph, uint32_t data_alignment);
/* configure ADC resolution */
void adc_resolution_config(uint32_t adc_periph, uint32_t resolution);
/* configure the ADC mode */
void adc_mode_config(uint32_t mode);
/* configure ADC internal channels */
void adc_internal_channel_config(uint32_t adc_periph, uint32_t internal_channel, ControlStatus newvalue);
/* ADC calibration mode configure */
void adc_calibration_mode_config(uint32_t adc_periph, uint32_t clb_mode);
/* configure ADC calibration number */
void adc_calibration_number(uint32_t adc_periph, uint32_t cal_num);
/* ADC calibration and reset calibration */
ErrStatus adc_calibration_enable(uint32_t adc_periph);

/* DMA configure */
/* enable DMA request */
void adc_dma_mode_enable(uint32_t adc_periph);
/* disable DMA request */
void adc_dma_mode_disable(uint32_t adc_periph);
/* enable ADC sequence DMA request */
void adc_sequence_dma_enable(uint32_t adc_periph, uint32_t adc_sequence);
/* disable ADC sequence DMA request */
void adc_sequence_dma_disable(uint32_t adc_periph, uint32_t adc_sequence);
/* enable ADC sequence channel dma request */
void adc_sequence_channel_dma_enable(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* disable ADC sequence channel dma request */
void adc_sequence_channel_dma_disable(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* when DMA=1, the DMA engine issues a request at end of each conversion */
void adc_dma_request_after_last_enable(uint32_t adc_periph, uint32_t adc_sequence);
/* the DMA engine is disabled after the end of transfer signal from DMA controller is detected  */
void adc_dma_request_after_last_disable(uint32_t adc_periph, uint32_t adc_sequence);

/* ADC special function functions */
/* configure ADC average mode */
void adc_average_config(uint32_t adc_periph, ControlStatus newvalue);
/* configure ADC average number */
void adc_average_number_config(uint32_t adc_periph, uint32_t aver_num);
/* configure ADC overwrite mode */
void adc_overwrite_config(uint32_t adc_periph, ControlStatus newvalue);
/* configure ADC clock in idle */
void adc_auto_clock_config(uint32_t adc_periph, uint32_t ack_cfg);
/* configure the ADC external analog multiplexers decode signals delay */
void adc_external_decode_signals_delay_config(uint32_t adc_periph, uint32_t external_delay);
/* configure the ADC convert start delay */
void adc_convert_start_delay_config(uint32_t adc_periph, uint32_t cs_delay);
/* enable the ADC convert start delay sequence */
void adc_convert_start_delay_enable(uint32_t adc_periph, uint32_t cs_sequence);
/* disable the ADC convert start delay sequence */
void adc_convert_start_delay_disable(uint32_t adc_periph, uint32_t cs_sequence);
/* configure ADC restart or resume sequence when this sequence be suspended */
void adc_restart_resume_sequence_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t adc_resel);
/* abort ADC current sequence conversion */
void adc_sequence_abort(uint32_t adc_periph, uint32_t adc_sequence);

/* ADC gain and offset mode functions */
/* configure ADC gain */
void adc_gain_config(uint32_t adc_periph, ControlStatus newvalue);
/* configure ADC gain factor */
void adc_gain_factor_config(uint32_t adc_periph, uint32_t gain_factor);
/* configure ADC offset y mode */
void adc_offset_config(uint32_t adc_periph, uint32_t off_num, ControlStatus newvalue);
/* configure the ADC offset function parameters */
void adc_offset_parameter_config(uint32_t adc_periph, uint32_t off_num, uint32_t off_factor, uint32_t off_ch, uint32_t off_pos);
/* configure ADC data signed mode */
void adc_signed_data_configure(uint32_t adc_periph, uint32_t off_num, ControlStatus newvalue);

/* ADC channel configuration functions */
/* configure the length of routine sequence or inserted sequence */
void adc_channel_length_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t length);
/* configure ADC sequence channel */
void adc_sequence_channel_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank, uint32_t adc_channel, uint32_t sample_time);
/* configure the routine sequence conversion mode */
void adc_routine_sequence_conversion_mode_config(uint32_t adc_periph, uint32_t adc_mode);
/* configure ADC external trigger mode for channel */
void adc_external_trigger_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t adc_trigger);
/* enable ADC sequence software trigger */
void adc_sequence_software_trigger_enable(uint32_t adc_periph, uint32_t adc_sequence);
/* configure ADC channel pre-sample function */
void adc_channel_presample_config(uint32_t adc_periph, uint32_t adc_channel, adc_presample_parameter_struct *presamplepara);

/* get channel data */
/* read ADC sequence channel data register */
uint16_t adc_channel_data_read(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* read ADC sequence data register */
uint16_t adc_sequence_data_read(uint32_t adc_periph, uint32_t adc_sequence);

/* ADC analog watchdog functions */
/* configure ADC channel analog watchdog events */
void adc_channel_analog_watchdog_event_config(uint32_t adc_periph, uint32_t adc_channel, uint32_t awd_sel, uint32_t awd_event);
/* configure the ADC analog watchdog threshold value */
void adc_watchdog_threshold_config(uint32_t adc_periph, uint32_t awd_sel, uint32_t low_value, uint32_t high_value);

/* ADC stream mode functions */
/* configure ADC sequence stream mode */
void adc_stream_mode_config(uint32_t adc_periph, uint32_t adc_sequence, ControlStatus newvalue);
/* configure ADC sequence stream counter value */
void adc_stream_counter_value_config(uint32_t adc_periph, uint32_t adc_sequence, uint32_t counter);
/* configure ADC sequence stream mode reload */
void adc_stream_mode_reload_config(uint32_t adc_periph, uint32_t adc_sequence, ControlStatus newvalue);

/* ADC selftest functions */
/* configure ADC self test */
void adc_selftest_configure(uint32_t adc_periph, ControlStatus newvalue);
/* configure the self test capacitive and supply sample time */
void adc_selftest_sample_time_config(uint32_t adc_periph, uint32_t adc_selftest, uint32_t ssamp, uint32_t csamp);
/* select the capacitive and supply self test steps in one shot mode */
void adc_selftest_step_select_in_oneshot_mode(uint32_t adc_periph, uint32_t st_step);
/* configure the self test mode */
void adc_selftest_mode_config(uint32_t adc_periph, uint32_t adc_selftest);
/* configure the self test execution rate in continous mode */
void adc_selftest_rate_config(uint32_t adc_periph, uint32_t st_rate);
/* read the self test error data */
uint32_t adc_selftest_error_data_read(uint32_t adc_periph, uint32_t st_data);
/* read the self test data */
uint32_t adc_selftest_data_read(uint32_t adc_periph);
/* get the self test capacitive occurred error step */
uint32_t adc_selftest_capacitive_error_step_get(uint32_t adc_periph);
/* get the self test which step converted result */
uint32_t adc_selftest_converted_step_get(uint32_t adc_periph);
/* get the status of  self test previous conversion data whether was overwritten without read */
FlagStatus adc_selftest_overwrite_status_get(uint32_t adc_periph);
/* get the status of  self test whether new conversion data is available */
FlagStatus adc_selftest_conversion_data_available_get(uint32_t adc_periph);
/* configure the self test analog watchdog threshold value */
void adc_selftest_analog_watchdog_step_threshold_config(uint32_t adc_periph, uint32_t st_sel, uint32_t st_step, uint32_t low_thl, uint32_t high_thl);
/* configure the self test watchdog */
void adc_selftest_analog_watchdog_config(uint32_t adc_periph, uint32_t st_sel, uint32_t st_step, ControlStatus newvalue);
/* configure the self test watchdog timer safe time */
void adc_selftest_watchdog_timer_safe_time_config(uint32_t adc_periph, uint32_t st_time);
/* configure the self test watchdog timer */
void adc_selftest_watchdog_timer_config(uint32_t adc_periph, uint32_t st_sel, ControlStatus newvalue);
/* configure the self test registers lock state */
void adc_selftest_config_lock(uint32_t adc_periph, uint32_t state);

/* ADC loop test functions */
/* configure DAC to ADC loop test */
void adc_dac_looptest_config(uint32_t adc_periph, ControlStatus newvalue);
/* configure the DAC to ADC loop test threshold value */
void adc_dac_looptest_threshold_config(uint32_t adc_periph, uint32_t low_thl, uint32_t high_thl);
/* select which DAC used to loop test */
void adc_dac_looptest_dac_select(uint32_t adc_periph, uint32_t dac_select);

/* get ADC state functions */
/* get the ADC current state */
FlagStatus adc_current_state_get(uint32_t adc_periph, uint32_t state);
/* get the ADC current active sequence */
uint32_t adc_active_sequence_get(uint32_t adc_periph);
/* get the ADC which channel in conversion */
uint32_t adc_active_channel_get(uint32_t adc_periph);
/* get which channel converted this conversion data in channel register */
uint32_t adc_channel_converted_channel_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* get whether the previous conversion data was overwritten without read in channel register */
FlagStatus adc_channel_overwrite_status_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* get whether the new conversion data is available in channel register */
FlagStatus adc_channel_conversion_data_available_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* get which channel converted this conversion data in sequence register */
uint32_t adc_sequence_converted_channel_get(uint32_t adc_periph, uint32_t adc_sequence);
/* get whether the previous conversion data was overwritten without read in sequence register */
FlagStatus adc_sequence_overwrite_status_get(uint32_t adc_periph, uint32_t adc_sequence);
/* get whether the new conversion data is available in sequence register */
FlagStatus adc_sequence_conversion_data_available_get(uint32_t adc_periph, uint32_t adc_sequence);

/* flag and interrupt functions */
/* get ADC flag */
FlagStatus adc_flag_get(uint32_t adc_periph, uint32_t flag);
/* get ADC error flag */
FlagStatus adc_error_flag_get(uint32_t adc_periph, uint32_t error_flag);
/* clear ADC flag */
void adc_flag_clear(uint32_t adc_periph, uint32_t flag);
/* clear ADC error flag */
void adc_error_flag_clear(uint32_t adc_periph, uint32_t error_flag);
/* enable ADC interrupt */
void adc_interrupt_enable(uint32_t adc_periph, uint32_t inserted_sequence, uint32_t interrupt);
/* disable ADC interrupt */
void adc_interrupt_disable(uint32_t adc_periph, uint32_t inserted_sequence, uint32_t interrupt);
/* get ADC interrupt flag */
FlagStatus adc_interrupt_flag_get(uint32_t adc_periph, uint32_t int_flag);
/* clear ADC interrupt flag */
void adc_interrupt_flag_clear(uint32_t adc_periph, uint32_t int_flag);

/* get ADC sequence channel end of conversion flag */
FlagStatus adc_channel_flag_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* clear ADC sequence channel end of conversion flag */
void adc_channel_flag_clear(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* enable ADC sequence channel end of conversion interrupt */
void adc_channel_interrupt_enable(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* disable ADC sequence channel end of conversion interrupt */
void adc_channel_interrupt_disable(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* get ADC sequence channel end of conversion interrupt flag */
FlagStatus adc_channel_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* clear ADC sequence channel end of conversion interrupt flag */
void adc_channel_interrupt_flag_clear(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);

/* get the ADC stream conversion complete flag */
FlagStatus adc_stream_flag_get(uint32_t adc_periph, uint32_t adc_sequence);
/* clear the ADC stream conversion complete flag */
void adc_stream_flag_clear(uint32_t adc_periph, uint32_t adc_sequence);
/* get the ADC stream conversion complete interrupt flag */
FlagStatus adc_stream_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_sequence);
/* clear the ADC stream conversion complete interrupt flag */
void adc_stream_interrupt_flag_clear(uint32_t adc_periph, uint32_t adc_sequence);

/* get ADC self test flag */
FlagStatus adc_selftest_flag_get(uint32_t adc_periph, uint32_t flag);
/* clear ADC selftest flag */
void adc_selftest_flag_clear(uint32_t adc_periph, uint32_t flag);
/* enable ADC self test interrupt */
void adc_selftest_interrupt_enable(uint32_t adc_periph, uint32_t interrupt);
/* disable ADC self test interrupt */
void adc_selftest_interrupt_disable(uint32_t adc_periph, uint32_t interrupt);
/* get ADC self test interrupt flag */
FlagStatus adc_selftest_interrupt_flag_get(uint32_t adc_periph, uint32_t int_flag);
/* clear ADC selftest interrupt flag */
void adc_selftest_interrupt_flag_clear(uint32_t adc_periph, uint32_t int_flag);

/* get ADC channel analog watchdog flag */
FlagStatus adc_channel_analog_watchdog_flag_get(uint32_t adc_periph, uint32_t adc_channel);
/* clear ADC channel analog watchdog flag */
void adc_channel_analog_watchdog_flag_clear(uint32_t adc_periph, uint32_t adc_channel);
/* get ADC channel analog watchdog interrupt flag */
FlagStatus adc_channel_analog_watchdog_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_channel);
/* clear ADC channel analog watchdog interrupt flag */
void adc_channel_analog_watchdog_interrupt_flag_clear(uint32_t adc_periph, uint32_t adc_channel);

/* get ADC sequence channel overwrite interrupt flag */
FlagStatus adc_channel_overwrite_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_sequence, uint32_t rank);
/* get the ADC sequence interrupt overwrite flag */
FlagStatus adc_overwrite_interrupt_flag_get(uint32_t adc_periph, uint32_t adc_sequence);
#endif /* GD32A7XX_ADC_H */
