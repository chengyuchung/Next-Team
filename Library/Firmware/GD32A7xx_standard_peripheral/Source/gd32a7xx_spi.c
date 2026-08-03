/*!
    \file    gd32a7xx_spi.c
    \brief   SPI driver

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

#include "gd32a7xx_spi.h"

/* SPI/I2S parameter initialization mask */
#define SPI_INIT_MASK                   ((uint32_t)0x00003040U)
#define I2S_INIT_MASK                   ((uint32_t)0x0000F047U)
#define I2S_FULL_DUPLEX_MASK            ((uint32_t)0x0000F040U)

#define SPI_RXLVL_MASK                  ((uint32_t)0x00001E00U)
#define SPI_TXLVL_MASK                  ((uint32_t)0x0003C000U)
#define SPI_DZ_INIT_MASK                ((uint32_t)0xFFFFE0FFU)

/* default value */
#define SPI_I2SPSC_RESET                ((uint32_t)0x00000002U)  /*!< default value of SPI_I2SPSC register */

/*!
    \brief      reset SPI and I2S (API_ID: 0x0001U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_i2s_deinit(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else
#endif
    {
        /* reset SPI register */
        SPI_CTL0(spi_periph)    = 0x00000000U;
        SPI_CTL1(spi_periph)    = 0x01000700U;
        SPI_STAT(spi_periph)    = 0x00000002U;
        SPI_DATA(spi_periph)    = 0x00000000U;
        SPI_CRCPOLY(spi_periph) = 0x00000107U;
        SPI_I2SCTL(spi_periph)  = 0x00000000U;
        SPI_I2SPSC(spi_periph)  = 0x00000002U;
        SPI_MREQCFG(spi_periph) = 0x00000000U;
        SPI_CKCFG0(spi_periph)  = 0x00000000U;
        SPI_CKCFG1(spi_periph)  = 0x00001003U;
        SPI_CCTL(spi_periph)    = 0x00000000U;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        SPI_POLCTL(spi_periph)  = 0x00000000U;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        SPI_QCTL(spi_periph)    = 0x00000000U;
        switch(spi_periph) {
        case SPI0:
            /* reset SPI0 */
            rcu_periph_reset_enable(RCU_SPI0RST);
            rcu_periph_reset_disable(RCU_SPI0RST);
            break;
        case SPI1:
            /* reset SPI1 */
            rcu_periph_reset_enable(RCU_SPI1RST);
            rcu_periph_reset_disable(RCU_SPI1RST);
            break;
        case SPI2:
            /* reset SPI2 */
            rcu_periph_reset_enable(RCU_SPI2RST);
            rcu_periph_reset_disable(RCU_SPI2RST);
            break;
        case SPI3:
            /* reset SPI3 */
            rcu_periph_reset_enable(RCU_SPI3RST);
            rcu_periph_reset_disable(RCU_SPI3RST);
            break;
        case SPI4:
            /* reset SPI4 */
            rcu_periph_reset_enable(RCU_SPI4RST);
            rcu_periph_reset_disable(RCU_SPI4RST);
            break;
        case SPI5:
            /* reset SPI5 */
            rcu_periph_reset_enable(RCU_SPI5RST);
            rcu_periph_reset_disable(RCU_SPI5RST);
            break;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case SPI6:
            /* reset SPI6 */
            rcu_periph_reset_enable(RCU_SPI6RST);
            rcu_periph_reset_disable(RCU_SPI6RST);
            break;
        case SPI7:
            /* reset SPI7 */
            rcu_periph_reset_enable(RCU_SPI7RST);
            rcu_periph_reset_disable(RCU_SPI7RST);
            break;
#endif /* GD32A72XX or GD32A74XX */
        default :
            break;
        }
    }
}

/*!
    \brief      initialize the parameters of SPI structure with the default values (API_ID: 0x0002U)
    \param[in]  none
    \param[out] spi_struct: the initialized structure spi_parameter_struct pointer
    \retval     none
*/
void spi_struct_para_init(spi_parameter_struct *spi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(spi_struct)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* configure the SPI structure with the default values */
        spi_struct->device_mode          = SPI_SLAVE;
        spi_struct->trans_mode           = SPI_TRANSMODE_FULLDUPLEX;
        spi_struct->nss                  = SPI_NSS_HARD;
        spi_struct->nss_polarity         = SPI_NSS_POLARITY_LOW;
        spi_struct->clock_polarity_phase = SPI_CK_PL_LOW_PH_1EDGE;
        spi_struct->prescale             = SPI_PSC_2;
        spi_struct->endian               = SPI_ENDIAN_MSB;
    }
}

/*!
    \brief      initialize SPI parameter (API_ID: 0x0003U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  spi_struct: SPI parameter initialization stuct members of the structure
                            and the member values are shown as below:
                  device_mode: SPI_MASTER, SPI_SLAVE
                  trans_mode: SPI_TRANSMODE_FULLDUPLEX, SPI_TRANSMODE_RECEIVEONLY,
                              SPI_TRANSMODE_BDRECEIVE, SPI_TRANSMODE_BDTRANSMIT
                  nss: SPI_NSS_SOFT, SPI_NSS_HARD
                  nss_polarity: SPI_NSS_POLARITY_LOW, SPI_NSS_POLARITY_HIGH
                  endian: SPI_ENDIAN_MSB, SPI_ENDIAN_LSB
                  clock_polarity_phase: SPI_CK_PL_LOW_PH_1EDGE, SPI_CK_PL_HIGH_PH_1EDGE
                                        SPI_CK_PL_LOW_PH_2EDGE, SPI_CK_PL_HIGH_PH_2EDGE
                  prescale: SPI_PSC_n (n=2,4,6,8,10,12,14,...256)
    \param[out] none
    \retval     none
*/
void spi_init(uint32_t spi_periph, spi_parameter_struct *spi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(spi_struct)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else if(NOT_SPI_DEVICE_MODE(spi_struct->device_mode)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_TRANS_MODE(spi_struct->trans_mode)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_NSS(spi_struct->nss)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_NSS_POLARITY(spi_struct->nss_polarity)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_ENDIAN(spi_struct->endian)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_CLOCK_POLARITY_PHASE(spi_struct->clock_polarity_phase)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_PRESCALE(spi_struct->prescale)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg0, reg1;
        reg0 = SPI_CTL0(spi_periph);
        reg1 = SPI_CTL1(spi_periph);
        reg0 &= SPI_INIT_MASK;
        reg1 &= (~SPI_CTL1_NSSPOL);

        /* select SPI as master or slave */
        reg0 |= spi_struct->device_mode;
        /* select SPI transfer mode */
        reg0 |= spi_struct->trans_mode;
        /* select SPI NSS use hardware or software */
        reg0 |= spi_struct->nss;
        /* select SPI LSB or MSB */
        reg0 |= spi_struct->endian;
        /* select SPI polarity and phase */
        reg0 |= spi_struct->clock_polarity_phase;
        /* select SPI prescale to adjust transmit speed */
        reg0 |= ((spi_struct->prescale) << 16U);
        /* select NSS polarity as high or low */
        reg1 |= spi_struct->nss_polarity;

        /* prevent master software NSS mode configuration errors */
        if(SPI_MASTER == spi_struct->device_mode && SPI_NSS_POLARITY_HIGH == spi_struct->nss_polarity) {
            reg0 &= (~SPI_CTL0_SWNSS);
        }

        /* write to SPI_CTL0 register */
        SPI_CTL0(spi_periph) = (uint32_t)reg0;
        /* write to SPI_CTL1 register */
        SPI_CTL1(spi_periph) = (uint32_t)reg1;
    }
}

/*!
    \brief      enable SPI (API_ID: 0x0004U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_SPIEN;
    }
}

/*!
    \brief      disable SPI (API_ID: 0x0005U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_SPIEN);
    }
}

/*!
    \brief      initialize I2S parameter (API_ID: 0x0006U)
    \param[in]  i2s_periph: I2Sx(x=4,5,6,7)
    \param[in]  i2s_mode: I2S operation mode
                only one parameter can be selected which is shown as below:
      \arg        I2S_MODE_SLAVETX: I2S slave transmit mode
      \arg        I2S_MODE_SLAVERX: I2S slave receive mode
      \arg        I2S_MODE_MASTERTX: I2S master transmit mode
      \arg        I2S_MODE_MASTERRX: I2S master receive mode
    \param[in]  i2s_standard: I2S standard
                only one parameter can be selected which is shown as below:
      \arg        I2S_STD_PHILIPS: I2S phillips standard
      \arg        I2S_STD_MSB: I2S MSB standard
      \arg        I2S_STD_LSB: I2S LSB standard
      \arg        I2S_STD_PCMSHORT: I2S PCM short standard
      \arg        I2S_STD_PCMLONG: I2S PCM long standard
    \param[in]  i2s_ckpl: I2S idle state clock polarity
                only one parameter can be selected which is shown as below:
      \arg        I2S_CKPL_LOW: I2S clock polarity low level
      \arg        I2S_CKPL_HIGH: I2S clock polarity high level
    \param[out] none
    \retval     none
*/
void i2s_init(uint32_t i2s_periph, uint32_t i2s_mode, uint32_t i2s_standard, uint32_t i2s_ckpl)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_I2S_PERIPH(i2s_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else if(NOT_SPI_I2S_MODE(i2s_mode)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_I2S_STANDARD(i2s_standard)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_I2S_CKPL(i2s_ckpl)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;
        reg = SPI_I2SCTL(i2s_periph);
        reg &= I2S_INIT_MASK;

        /* enable I2S mode */
        reg |= (uint32_t)SPI_I2SCTL_I2SSEL;
        /* select I2S mode */
        reg |= (uint32_t)i2s_mode;
        /* select I2S standard */
        reg |= (uint32_t)i2s_standard;
        /* select I2S polarity */
        reg |= (uint32_t)i2s_ckpl;

        /* write to SPI_I2SCTL register */
        SPI_I2SCTL(i2s_periph) = (uint32_t)reg;
    }
}

/*!
    \brief      configure I2S prescaler (API_ID: 0x0007U)
    \param[in]  i2s_periph: I2Sx(x=4,5,6,7)
    \param[in]  i2s_audiosample: I2S audio sample rate
                only one parameter can be selected which is shown as below:
      \arg        I2S_AUDIOSAMPLE_8K: audio sample rate is 8KHz
      \arg        I2S_AUDIOSAMPLE_11K: audio sample rate is 11KHz
      \arg        I2S_AUDIOSAMPLE_16K: audio sample rate is 16KHz
      \arg        I2S_AUDIOSAMPLE_22K: audio sample rate is 22KHz
      \arg        I2S_AUDIOSAMPLE_32K: audio sample rate is 32KHz
      \arg        I2S_AUDIOSAMPLE_44K: audio sample rate is 44KHz
      \arg        I2S_AUDIOSAMPLE_48K: audio sample rate is 48KHz
      \arg        I2S_AUDIOSAMPLE_96K: audio sample rate is 96KHz
      \arg        I2S_AUDIOSAMPLE_192K: audio sample rate is 192KHz
    \param[in]  i2s_frameformat: I2S data length and channel length
                only one parameter can be selected which is shown as below:
      \arg        I2S_FRAMEFORMAT_DT16B_CH16B: I2S data length is 16 bit and channel length is 16 bit
      \arg        I2S_FRAMEFORMAT_DT16B_CH32B: I2S data length is 16 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT24B_CH32B: I2S data length is 24 bit and channel length is 32 bit
      \arg        I2S_FRAMEFORMAT_DT32B_CH32B: I2S data length is 32 bit and channel length is 32 bit
    \param[in]  i2s_mckout: I2S master clock output
                only one parameter can be selected which is shown as below:
      \arg        I2S_MCKOUT_ENABLE: I2S master clock output enable
      \arg        I2S_MCKOUT_DISABLE: I2S master clock output disable
    \param[out] none
    \retval     none
*/
void i2s_psc_config(uint32_t i2s_periph, uint32_t i2s_audiosample, uint32_t i2s_frameformat,
                    uint32_t i2s_mckout)
{
    uint32_t i2sdiv, i2sof, clks, i2sclock;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_I2S_PERIPH(i2s_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else if(NOT_SPI_I2S_AUDIOSAMPLE(i2s_audiosample)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_I2S_FRAMEFORMAT(i2s_frameformat)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else if(NOT_SPI_I2S_MCKOUT(i2s_mckout)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* deinitialize SPI_I2SPSC register */
        SPI_I2SPSC(i2s_periph) = SPI_I2SPSC_RESET;
        /* get system clock */
        i2sclock = rcu_clock_freq_get(CK_SYS);
        /* configure the prescaler depending on the mclk output state, the frame format and audio sample rate */
        if(I2S_MCKOUT_ENABLE == i2s_mckout) {
            clks = (uint32_t)(((i2sclock / 256U) * 10U) / i2s_audiosample);
        } else {
            if(I2S_FRAMEFORMAT_DT16B_CH16B == i2s_frameformat) {
                clks = (uint32_t)(((i2sclock / 32U) * 10U) / i2s_audiosample);
            } else {
                clks = (uint32_t)(((i2sclock / 64U) * 10U) / i2s_audiosample);
            }
        }

        /* remove the floating point */
        clks   = (clks + 5U) / 10U;
        i2sof  = (clks & 0x00000001U);
        i2sdiv = ((clks - i2sof) / 2U);
        i2sof  = (i2sof << 8U);

        /* set the default values */
        if((i2sdiv < 2U) || (i2sdiv > 255U)) {
            i2sdiv = 2U;
            i2sof = 0U;
        }

        /* configure SPI_I2SPSC */
        SPI_I2SPSC(i2s_periph) = (uint32_t)(i2sdiv | i2sof | i2s_mckout);

        /* clear SPI_I2SCTL_DTLEN and SPI_I2SCTL_CHLEN bits */
        SPI_I2SCTL(i2s_periph) &= (uint32_t)(~(SPI_I2SCTL_DTLEN | SPI_I2SCTL_CHLEN));

        /* configure data frame format */
        SPI_I2SCTL(i2s_periph) |= (uint32_t)i2s_frameformat;
    }
}

/*!
    \brief      enable I2S (API_ID: 0x0008U)
    \param[in]  i2s_periph: I2Sx(x=4,5,6,7)
    \param[out] none
    \retval     none
*/
void i2s_enable(uint32_t i2s_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_I2S_PERIPH(i2s_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else
#endif
    {
        SPI_I2SCTL(i2s_periph) |= (uint32_t)SPI_I2SCTL_I2SEN;
    }
}

/*!
    \brief      disable I2S (API_ID: 0x0009U)
    \param[in]  i2s_periph: I2Sx(x=4,5,6,7)
    \param[out] none
    \retval     none
*/
void i2s_disable(uint32_t i2s_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_I2S_PERIPH(i2s_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else
#endif
    {
        SPI_I2SCTL(i2s_periph) &= (uint32_t)(~SPI_I2SCTL_I2SEN);
    }
}

/*!
    \brief      enable SPI NSS output (API_ID: 0x000AU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_nss_output_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_NSSDRV;
    }
}

/*!
    \brief      disable SPI NSS output (API_ID: 0x000BU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_nss_output_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_NSSDRV);
    }
}

/*!
    \brief      SPI NSS pin high level in software mode (API_ID: 0x000CU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_nss_internal_high(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_SWNSS;
    }
}

/*!
    \brief      SPI NSS pin low level in software mode (API_ID: 0x000DU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_nss_internal_low(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_SWNSS);
    }
}


/*!
    \brief      SPI NSS select (API_ID: 0x000EU)
    \param[in]  spi_periph: SPIx(x=0...7)
                spi_nss_id: SPI_NSS_SELECT_x (x = 0~7)
    \param[out] none
    \retval     none
*/
void spi_nss_select(uint32_t spi_periph, uint32_t spi_nss_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    } else if(NOT_SPI_NSS_ID(spi_nss_id)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= (uint32_t)(spi_nss_id);
    }
}

/*!
    \brief      enable SPI DMA send or receive (API_ID: 0x000FU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  spi_dma: SPI DMA mode
                only one parameter can be selected which is shown as below:
      \arg        SPI_DMA_TRANSMIT: SPI transmit data using DMA
      \arg        SPI_DMA_RECEIVE: SPI receive data using DMA
    \param[out] none
    \retval     none
*/
void spi_dma_enable(uint32_t spi_periph, uint8_t spi_dma)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    } else if(NOT_SPI_DMA_MODE(spi_dma)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(SPI_DMA_TRANSMIT == spi_dma) {
            SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_DMATEN;
        } else {
            SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_DMAREN;
        }
    }
}

/*!
    \brief      disable SPI DMA send or receive (API_ID: 0x0010U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  spi_dma: SPI DMA mode
                only one parameter can be selected which is shown as below:
      \arg        SPI_DMA_TRANSMIT: SPI transmit data using DMA
      \arg        SPI_DMA_RECEIVE: SPI receive data using DMA
    \param[out] none
    \retval     none
*/
void spi_dma_disable(uint32_t spi_periph, uint8_t spi_dma)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    } else if(NOT_SPI_DMA_MODE(spi_dma)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(SPI_DMA_TRANSMIT == spi_dma) {
            SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_DMATEN);
        } else {
            SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_DMAREN);
        }
    }
}

/*!
    \brief      SPI transmit data (API_ID: 0x0011U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  data: 32-bit data
    \param[out] none
    \retval     none
*/
void spi_i2s_data_transmit(uint32_t spi_periph, uint32_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else
#endif
    {
        SPI_DATA(spi_periph) = (uint32_t)data;
    }
}

/*!
    \brief      SPI receive data (API_ID: 0x0012U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     32-bit data
*/
uint32_t spi_i2s_data_receive(uint32_t spi_periph)
{
    uint32_t reval = 0U ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else
#endif
    {
        reval = ((uint32_t)SPI_DATA(spi_periph));
    }
    return reval;
}

/*!
    \brief      configure SPI bidirectional transfer direction (API_ID: 0x0013U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  transfer_direction: SPI transfer direction
                only one parameter can be selected which is shown as below:
      \arg        SPI_BIDIRECTIONAL_TRANSMIT: SPI work in transmit-only mode
      \arg        SPI_BIDIRECTIONAL_RECEIVE: SPI work in receive-only mode
    \param[out] none
    \retval     none
*/
void spi_bidirectional_transfer_config(uint32_t spi_periph, uint32_t transfer_direction)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    } else if(NOT_SPI_TRANS_DIR(transfer_direction)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(SPI_BIDIRECTIONAL_TRANSMIT == transfer_direction) {
            /* set the transmit only mode */
            SPI_CTL0(spi_periph) |= (uint32_t)SPI_BIDIRECTIONAL_TRANSMIT;
        } else {
            /* set the receive only mode */
            SPI_CTL0(spi_periph) &= SPI_BIDIRECTIONAL_RECEIVE;
        }
    }
}

/*!
    \brief      clear SPI/I2S format error flag status (API_ID: 0x0014U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  flag: SPI/I2S frame format error flag
      \arg        SPI_FLAG_FERR: only for SPI work in TI mode
      \arg        I2S_FLAG_FERR: for I2S
    \param[out] none
    \retval     none
*/
void spi_i2s_format_error_clear(uint32_t spi_periph, uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    } else if(NOT_SPI_FRAME_FORMAT_ERROR_FLAG(flag)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0014U), ERR_PARAM_INVALID);
    } else
#endif
    {
        SPI_STAT(spi_periph) &= (uint32_t)(~flag);
    }
}

/*!
    \brief      set the data size for transfer (API_ID: 0x0015U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  data_size: data size
      \arg        SPI_DATA_SIZEn (n=1...32)
    \param[out] none
    \retval     none
*/
void spi_i2s_data_size(uint32_t spi_periph, uint8_t data_size)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    } else if(NOT_SPI_DATA_SIZE(data_size)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = SPI_CTL1(spi_periph);
        reg &= SPI_DZ_INIT_MASK;
        reg |= (((uint32_t)data_size) << 8U);

        SPI_CTL1(spi_periph) = reg;
    }
}

/*!
    \brief      FIFO loopback mode enable (API_ID: 0x0016U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_i2s_fifo_loopback_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= SPI_CTL1_FIFOLBEN;
    }
}

/*!
    \brief      FIFO loopback mode disable (API_ID: 0x0017U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_i2s_fifo_loopback_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_FIFOLBEN);
    }
}

/*!
    \brief      RXFIFO current word number (API_ID: 0x0018U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     32-bit data
*/
uint32_t spi_i2s_read_rxlvl_words(uint32_t spi_periph)
{
    uint32_t reval = 0U ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg = 0U;
        reg |= SPI_STAT(spi_periph);
        reg &= SPI_RXLVL_MASK;
        reg = reg >> 9;

        reval = ((uint32_t) reg);
    }
    return reval;
}

/*!
    \brief      TXFIFO current word number (API_ID: 0x0019U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     32-bit data
*/
uint32_t spi_i2s_read_txlvl_words(uint32_t spi_periph)
{
    uint32_t reval = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg = 0U;
        reg |= SPI_STAT(spi_periph);
        reg &= SPI_TXLVL_MASK;
        reg = reg >> 14;

        reval = ((uint32_t) reg);
    }
    return reval;
}

/*!
    \brief      set SPI CRC polynomial (API_ID: 0x001AU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  crc_poly: CRC polynomial value
    \param[out] none
    \retval     none
*/
void spi_crc_polynomial_set(uint32_t spi_periph, uint32_t crc_poly)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    } else
#endif
    {
        /* enable SPI CRC */
        SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCEN;

        /* set SPI CRC polynomial */
        SPI_CRCPOLY(spi_periph) = (uint32_t)crc_poly;
    }
}

/*!
    \brief      get SPI CRC polynomial (API_ID: 0x001BU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     CRC polynomial
*/
uint32_t spi_crc_polynomial_get(uint32_t spi_periph)
{
    uint32_t reval = 0U ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    } else
#endif
    {
        reval = ((uint32_t)SPI_CRCPOLY(spi_periph));
    }
    return reval;
}

/*!
    \brief      turn on CRC function (API_ID: 0x001CU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_crc_on(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCEN;
    }
}

/*!
    \brief      turn off CRC function (API_ID: 0x001DU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_crc_off(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL0(spi_periph) &= (uint32_t)(~SPI_CTL0_CRCEN);
    }
}

/*!
    \brief      SPI next data is CRC value (API_ID: 0x001EU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_crc_next(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL0(spi_periph) |= (uint32_t)SPI_CTL0_CRCNT;
    }
}

/*!
    \brief      get SPI CRC send value (API_ID: 0x001FU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     CRC value
*/
uint32_t spi_tx_crc_get(uint32_t spi_periph)
{
    uint32_t reval = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    } else
#endif
    {
        reval = ((uint32_t)(SPI_TCRC(spi_periph)));
    }
    return reval;
}

/*!
    \brief      enable SPI TI mode (API_ID: 0x0020U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_ti_mode_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0020U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_TMOD;
    }
}

/*!
    \brief      disable SPI TI mode (API_ID: 0x0021U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_ti_mode_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0021U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_TMOD);
    }
}

/*!
    \brief      enable SPI NSS pulse mode (API_ID: 0x0022U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_nssp_mode_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0022U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_NSSP;
    }
}

/*!
    \brief      disable SPI NSS pulse mode (API_ID: 0x0023U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_nssp_mode_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0023U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_NSSP);
    }
}

/*!
    \brief      enable quad wire SPI (API_ID: 0x0024U)
    \param[in]  spi_periph: SPIx(x=0/2)
    \param[out] none
    \retval     none
*/
void spi_quad_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QUAD_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0024U), ERR_PERIPH);
    } else
#endif
    {
        SPI_QCTL(spi_periph) |= (uint32_t)SPI_QCTL_QMOD;
    }
}

/*!
    \brief      disable quad wire SPI (API_ID: 0x0025U)
    \param[in]  spi_periph: SPIx(x=0/2)
    \param[out] none
    \retval     none
*/
void spi_quad_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QUAD_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0025U), ERR_PERIPH);
    } else
#endif
    {
        SPI_QCTL(spi_periph) &= (uint32_t)(~SPI_QCTL_QMOD);
    }
}

/*!
    \brief      enable quad wire SPI write (API_ID: 0x0026U)
    \param[in]  spi_periph: SPIx(x=0/2)
    \param[out] none
    \retval     none
*/
void spi_quad_write_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QUAD_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0026U), ERR_PERIPH);
    } else
#endif
    {
        SPI_QCTL(spi_periph) &= (uint32_t)(~SPI_QCTL_QRD);
    }
}

/*!
    \brief      enable quad wire SPI read (API_ID: 0x0027U)
    \param[in]  spi_periph: SPIx(x=0/2)
    \param[out] none
    \retval     none
*/
void spi_quad_read_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QUAD_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0027U), ERR_PERIPH);
    } else
#endif
    {
        SPI_QCTL(spi_periph) |= (uint32_t)SPI_QCTL_QRD;
    }
}

/*!
    \brief      get SPI and I2S flag status (API_ID: 0x0028U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  flag: SPI/I2S flag status
                only one parameter can be selected which is shown as below:
      \arg        SPI_FLAG_RFDR:   reception fifo data ready flag
      \arg        SPI_FLAG_TFA:    transmission fifo available flag
      \arg        SPI_FLAG_TXURERR: underrun error flag
      \arg        SPI_FLAG_CONFERR: mode config error flag
      \arg        SPI_FLAG_RXORERR: receive overrun error flag
      \arg        SPI_FLAG_TRANS:  transmit on-going flag
      \arg        SPI_FLAG_FERR:   format error flag
      \arg        SPI_FLAG_TOF:    timeout flag
      \arg        I2S_FLAG_RFDR: reception fifo data ready flag
      \arg        I2S_FLAG_TFA: transmission fifo available flag
      \arg        I2S_FLAG_CH: channel side flag
      \arg        I2S_FLAG_TXURERR: underrun error flag
      \arg        I2S_FLAG_RXORERR: overrun error flag
      \arg        I2S_FLAG_TRANS: transmit on-going flag
      \arg        I2S_FLAG_FERR: format error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus spi_i2s_flag_get(uint32_t spi_periph, uint32_t flag)
{
    FlagStatus reval = RESET ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0028U), ERR_PERIPH);
    } else if(NOT_SPI_I2S_FLAG_STATUS(flag)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0028U), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(0U != (SPI_STAT(spi_periph) & flag)) {
            reval = SET;
        }
    }
    return reval;
}
/*!
    \brief      enable SPI and I2S interrupt (API_ID: 0x0029U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  interrupt: SPI/I2S interrupt
                only one parameter can be selected which is shown as below:
      \arg        SPI_I2S_INT_TFA: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RFDR: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_ERR: configuration error,reception overrun error,
                                   transmission underrun error and format error interrupt
      \arg        SPI_INT_TO: timeout interrupt
    \param[out] none
    \retval     none
*/
void spi_i2s_interrupt_enable(uint32_t spi_periph, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0029U), ERR_PERIPH);
    } else if(NOT_SPI_I2S_INTERRUPT(interrupt)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0029U), ERR_PARAM_INVALID);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= interrupt;
    }
}

/*!
    \brief      disable SPI and I2S interrupt (API_ID: 0x002AU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  interrupt: SPI/I2S interrupt
                only one parameter can be selected which is shown as below:
      \arg        SPI_I2S_INT_TFA: transmit buffer empty interrupt
      \arg        SPI_I2S_INT_RFDR: receive buffer not empty interrupt
      \arg        SPI_I2S_INT_ERR: configuration error,reception overrun error,
                                   transmission underrun error and format error interrupt
      \arg        SPI_INT_TO: timeout interrupt
    \param[out] none
    \retval     none
*/
void spi_i2s_interrupt_disable(uint32_t spi_periph, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x002AU), ERR_PERIPH);
    } else if(NOT_SPI_I2S_INTERRUPT(interrupt)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x002AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= ~interrupt;
    }
}

/*!
    \brief      get SPI and I2S interrupt flag status (API_ID: 0x002BU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  interrupt: SPI/I2S interrupt flag status
                only one parameter can be selected which is shown as below:
      \arg        SPI_I2S_INT_FLAG_TFA: transmit buffer empty interrupt flag
      \arg        SPI_I2S_INT_FLAG_RFDR: receive buffer not empty interrupt flag
      \arg        SPI_I2S_INT_FLAG_RXORERR: overrun interrupt flag
      \arg        SPI_I2S_INT_FLAG_TXURERR: underrun error interrupt flag
      \arg        SPI_INT_FLAG_TOF: timeout interrupt flag
      \arg        SPI_INT_FLAG_CONFERR: config error interrupt flag
      \arg        SPI_I2S_INT_FLAG_FERR: format error interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus spi_i2s_interrupt_flag_get(uint32_t spi_periph, uint8_t interrupt)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x002BU), ERR_PERIPH);
    } else if(NOT_SPI_I2S_INTERRUPT_FLAG_STATUS(interrupt)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x002BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg1 = SPI_STAT(spi_periph);
        uint32_t reg2 = SPI_CTL1(spi_periph);

        switch(interrupt) {
            /* SPI/I2S transmit buffer empty interrupt */
            case SPI_I2S_INT_FLAG_TFA:
            reg1 = reg1 & SPI_STAT_TFA;
            reg2 = reg2 & SPI_CTL1_TFAIE;
            break;
            /* SPI/I2S receive buffer not empty interrupt */
            case SPI_I2S_INT_FLAG_RFDR:
            reg1 = reg1 & SPI_STAT_RFDR;
            reg2 = reg2 & SPI_CTL1_RFDRIE;
            break;
            /* SPI/I2S overrun interrupt */
            case SPI_I2S_INT_FLAG_RXORERR:
            reg1 = reg1 & SPI_STAT_RXORERR;
            reg2 = reg2 & SPI_CTL1_ERRIE;
            break;
            /* SPI/I2S underrun error interrupt */
            case SPI_I2S_INT_FLAG_TXURERR:
            reg1 = reg1 & SPI_STAT_TXURERR;
            reg2 = reg2 & SPI_CTL1_ERRIE;
            break;
            /* SPI timeout interrupt */
            case SPI_INT_FLAG_TOF:
            reg1 = reg1 & SPI_STAT_TOF;
            reg2 = reg2 & SPI_CTL1_TOIE;
            break;
            /* SPI config error interrupt */
            case SPI_INT_FLAG_CONFERR:
            reg1 = reg1 & SPI_STAT_CONFERR;
            reg2 = reg2 & SPI_CTL1_ERRIE;
            break;
            /* SPI/I2S format error interrupt */
            case SPI_I2S_INT_FLAG_FERR:
            reg1 = reg1 & SPI_STAT_FERR;
            reg2 = reg2 & SPI_CTL1_ERRIE;
            break;
            default:
            break;
        }
        /*get SPI/I2S interrupt flag status */
        if((0U != reg1) && (0U != reg2)) {
            reval = SET;
        }
    }
    return reval;
}

/*!
    \brief      SPI configure the SPI_MREQCFG direction is output (API_ID: 0x002CU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_hr_output(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x002CU), ERR_PERIPH);
    } else
#endif
    {
        SPI_MREQCFG(spi_periph) |= SPI_MREQCFG_MREQDIR;
    }
}

/*!
    \brief      SPI configure the SPI_MREQCFG direction is input (API_ID: 0x002DU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_hr_input(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x002DU), ERR_PERIPH);
    } else
#endif
    {
        SPI_MREQCFG(spi_periph) &= (~SPI_MREQCFG_MREQDIR);
    }
}

/*!
    \brief      SPI host request input is the SPI_MREQCFG pin (API_ID: 0x002EU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_hrsel_pin(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x002EU), ERR_PERIPH);
    } else
#endif
    {
        SPI_MREQCFG(spi_periph) &= (~SPI_MREQCFG_MREQSEL);
    }
}

/*!
    \brief      host request input is the input trigger (API_ID: 0x002FU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_hrsel_trigger(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x002FU), ERR_PERIPH);
    } else
#endif
    {
        SPI_MREQCFG(spi_periph) |= SPI_MREQCFG_MREQSEL;
    }
}

/*!
    \brief      SPI configures the polarity of the host request pin or trigger as active high (API_ID: 0x0030U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_hr_high(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0030U), ERR_PERIPH);
    } else
#endif
    {
        SPI_MREQCFG(spi_periph) &= (~SPI_MREQCFG_MREQPL);
    }
}

/*!
    \brief      SPI configures the polarity of the host request pin or trigger as active low (API_ID: 0x0031U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_hr_low(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0031U), ERR_PERIPH);
    } else
#endif
    {
        SPI_MREQCFG(spi_periph) |= SPI_MREQCFG_MREQPL;
    }
}

/*!
    \brief      SPI master request enable (API_ID: 0x0032U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_hr_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0032U), ERR_PERIPH);
    } else
#endif
    {
        SPI_MREQCFG(spi_periph) |= SPI_MREQCFG_MREQEN;
    }
}

/*!
    \brief      SPI master request disable (API_ID: 0x0033U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_hr_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0033U), ERR_PERIPH);
    } else
#endif
    {
        SPI_MREQCFG(spi_periph) &= (~SPI_MREQCFG_MREQEN);
    }
}

/*!
    \brief      Configure NSS polarity as active high (API_ID: 0x0034U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_nss_polarity_high(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0034U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= (uint32_t)SPI_CTL1_NSSPOL;
    }
}

/*!
    \brief      Configure NSS polarity as active low (API_ID: 0x0035U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_nss_polarity_low(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0035U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_NSSPOL);
    }
}

/*!
    \brief      Configure minimum delay from NSS inactive to NSS active (API_ID: 0x0036U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  delay: 0-0xFF, delay range is 1*SCK to 256*SCK
    \param[out] none
    \retval     none
*/
void spi_nssnss_delay(uint32_t spi_periph, uint8_t delay)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0036U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CKCFG0(spi_periph) &= (uint32_t)(~SPI_CKCFG0_NSSNSS);
        SPI_CKCFG0(spi_periph) |= ((uint32_t)delay << 16U);
    }
}

/*!
    \brief      Configure minimum delay from SCK inactive to NSS inactive (API_ID: 0x0037U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  delay: 0-0xFF, delay range is 1*SCK to 256*SCK
    \param[out] none
    \retval     none
*/
void spi_scknss_delay(uint32_t spi_periph, uint8_t delay)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0037U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CKCFG0(spi_periph) &= (uint32_t)(~SPI_CKCFG0_SCKNSS);
        SPI_CKCFG0(spi_periph) |= ((uint32_t)delay << 8U);
    }
}

/*!
    \brief      Configure minimum delay from NSS active to SCK active (API_ID: 0x0038U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  delay: 0-0xFF, delay range is 1*SCK to 256*SCK
    \param[out] none
    \retval     none
*/
void spi_nsssck_delay(uint32_t spi_periph, uint8_t delay)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0038U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CKCFG0(spi_periph) &= (uint32_t)(~SPI_CKCFG0_NSSSCK);
        SPI_CKCFG0(spi_periph) |= ((uint32_t)delay << 0U);
    }
}

/*!
    \brief      Enable SPI sampling delay (API_ID: 0x0039U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_sample_delay_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0039U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CKCFG1(spi_periph) |= SPI_CKCFG1_SAMPDLYEN;
    }
}

/*!
    \brief      Disable SPI sampling delay (API_ID: 0x003AU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_sample_delay_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x003AU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CKCFG1(spi_periph) &= (uint32_t)(~SPI_CKCFG1_SAMPDLYEN);
    }
}

/*!
    \brief      Configure SPI sampling delay compensation time (API_ID: 0x003BU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  delay: 0-0x0FFF, delay range is 1*CK_SPI to 4096*SCK_SPI
    \param[out] none
    \retval     none
*/
void spi_sample_delay_config(uint32_t spi_periph, uint16_t delay)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x003BU), ERR_PERIPH);
    } else if (NOT_SPI_SAMPLE_DELAY_NUM(delay)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x003BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        SPI_CKCFG1(spi_periph) &= (uint32_t)(~SPI_CKCFG1_SAMPDLY);
        SPI_CKCFG1(spi_periph) |= ((uint32_t)delay << 0U);
    }
}

/*!
    \brief      Enable SPI bus idle timeout (API_ID: 0x003CU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_idle_timeout_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x003CU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= SPI_CTL1_TOEN;
    }
}

/*!
    \brief      Disable SPI bus idle timeout (API_ID: 0x003DU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_idle_timeout_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x003DU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_TOEN);
    }
}

/*!
    \brief      Configure SPI bus idle timeout threshold (API_ID: 0x003EU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  threshold: 0-0xFF, timeout threshold value range is 1*SCK to 256*SCK
    \param[out] none
    \retval     none
*/
void spi_idle_threshold_config(uint32_t spi_periph, uint8_t threshold)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x003EU), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_TOCFG);
        SPI_CTL1(spi_periph) |= ((uint32_t)threshold << 24U);
    }
}

/*!
    \brief      Clear SPI idle timeout flag (API_ID: 0x003FU)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_timeout_flag_clear(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x003FU), ERR_PERIPH);
    } else
#endif
    {
        SPI_STAT(spi_periph) &= (uint32_t)(~SPI_STAT_TOF);
    }
}

/*!
    \brief      Clear SPI idle timeout interrupt flag (API_ID: 0x0040U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_timeout_interrupt_flag_clear(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0040U), ERR_PERIPH);
    } else
#endif
    {
        SPI_STAT(spi_periph) &= (uint32_t)(~SPI_STAT_TOF);
    }
}

/*!
    \brief      Enable SPI hardware single-frame mode (API_ID: 0x0041U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_single_frame_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0041U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) |= SPI_CTL1_SINGMOD;
    }
}

/*!
    \brief      Disable SPI hardware single-frame mode (API_ID: 0x0042U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_single_frame_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0042U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CTL1(spi_periph) &= (uint32_t)(~SPI_CTL1_SINGMOD);
    }
}

/*!
    \brief      Enable SPI hardware continuous-frame mode (API_ID: 0x0043U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_continuous_frame_enable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0043U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CCTL(spi_periph) |= SPI_CCTL_HCEN;
    }
}

/*!
    \brief      Disable SPI hardware continuous-frame mode (API_ID: 0x0044U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[out] none
    \retval     none
*/
void spi_continuous_frame_disable(uint32_t spi_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CCTL(spi_periph) &= (uint32_t)(~SPI_CCTL_HCEN);
    }
}

/*!
    \brief      Configure SPI hardware continuous-frame length (API_ID: 0x0045U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  length: 0-0xFFFF, frame length range is 1 frame to 65536 frames
    \param[out] none
    \retval     none
*/
void spi_continuous_frame_length_config(uint32_t spi_periph, uint16_t length)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0045U), ERR_PERIPH);
    } else
#endif
    {
        SPI_CCTL(spi_periph) &= (uint32_t)(~SPI_CCTL_FRAMLEN);
        SPI_CCTL(spi_periph) |= ((uint32_t)length << 0U);
    }
}

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      Configure multiple NSS pins polarity as active high (API_ID: 0x0046U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  nss_pin: NSS pin
                one or more parameters can be selected which are shown as below:
      \arg        SPI_NSS_PIN_0: NSS pin 0
      \arg        SPI_NSS_PIN_1: NSS pin 1
      \arg        SPI_NSS_PIN_2: NSS pin 2
      \arg        SPI_NSS_PIN_3: NSS pin 3
      \arg        SPI_NSS_PIN_4: NSS pin 4
      \arg        SPI_NSS_PIN_5: NSS pin 5
      \arg        SPI_NSS_PIN_6: NSS pin 6
      \arg        SPI_NSS_PIN_7: NSS pin 7
    \param[out] none
    \retval     none
*/
void spi_multi_nss_polarity_high(uint32_t spi_periph, uint32_t nss_pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0046U), ERR_PERIPH);
    } else if (NOT_SPI_NSS_PIN(nss_pin)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0046U), ERR_PARAM_INVALID);
    } else
#endif
    {
        SPI_POLCTL(spi_periph) |= (uint32_t)SPI_POLCTL_NSSPOLMOD;
        SPI_POLCTL(spi_periph) |= (uint32_t)nss_pin;
    }
}

/*!
    \brief      Configure multiple NSS pins polarity as active low (API_ID: 0x0047U)
    \param[in]  spi_periph: SPIx(x=0...7)
    \param[in]  nss_pin: NSS pin mask
                one or more parameters can be selected which are shown as below:
      \arg        SPI_NSS_PIN_0: NSS pin 0
      \arg        SPI_NSS_PIN_1: NSS pin 1
      \arg        SPI_NSS_PIN_2: NSS pin 2
      \arg        SPI_NSS_PIN_3: NSS pin 3
      \arg        SPI_NSS_PIN_4: NSS pin 4
      \arg        SPI_NSS_PIN_5: NSS pin 5
      \arg        SPI_NSS_PIN_6: NSS pin 6
      \arg        SPI_NSS_PIN_7: NSS pin 7
    \param[out] none
    \retval     none
*/
void spi_multi_nss_polarity_low(uint32_t spi_periph, uint32_t nss_pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    if (NOT_SPI_PERIPH(spi_periph)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0047U), ERR_PERIPH);
    } else if (NOT_SPI_NSS_PIN(nss_pin)) {
        fw_debug_report_err(SPI_MODULE_ID, API_ID(0x0047U), ERR_PARAM_INVALID);
    } else
#endif
    {
        SPI_POLCTL(spi_periph) |= (uint32_t)SPI_POLCTL_NSSPOLMOD;
        SPI_POLCTL(spi_periph) &= (uint32_t)(~nss_pin);
    }
}
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
