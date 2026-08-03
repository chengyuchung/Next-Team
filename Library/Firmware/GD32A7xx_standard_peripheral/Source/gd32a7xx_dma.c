/*!
    \file    gd32a7xx_dma.c
    \brief   DMA driver

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

#include "gd32a7xx_dma.h"
#include <stdlib.h>

/* DMA register bit offset */
#define CHXFCTL_FCNT_OFFSET        ((uint32_t)0x00000003U)               /*!< bit offset of FCNT in DMA_CHxFCTL */

/* DMAMUX register bit offset */
#define RM_CHXCFG_NBR_OFFSET       ((uint32_t)0x00000013U)               /*!< bit offset of NBR in DMAMUX_RM_CHXCFG */
#define RG_CHXCFG_NBRG_OFFSET      ((uint32_t)0x00000013U)               /*!< bit offset of NBRG in DMAMUX_RG_CHXCFG */

/* DMA bits mask */
#define DMA_CHXCTL_INT_MASK        ((uint32_t)0x0000001EU)               /*!< DMA_CHXCTL interrupt mask*/

/*!
    \brief      deinitialize DMA a channel registers (API_ID(0x0001U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel is deinitialized
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_deinit(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0001U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable DMA a channel */
        DMA_CHCTL(dma_periph, channelx)     &= ~DMA_CHXCTL_CHEN;
        /* reset DMA channel registers */
        DMA_CHCTL(dma_periph, channelx)      = DMA_CHCTL_RESET_VALUE;
        DMA_CHCNT(dma_periph, channelx)      = DMA_CHCNT_RESET_VALUE;
        DMA_CHPADDR(dma_periph, channelx)    = DMA_CHPADDR_RESET_VALUE;
        DMA_CHM0ADDR(dma_periph, channelx)   = DMA_CHMADDR_RESET_VALUE;
        DMA_CHM1ADDR(dma_periph, channelx)   = DMA_CHMADDR_RESET_VALUE;
        DMA_CHFCTL(dma_periph, channelx)     = DMA_CHFCTL_RESET_VALUE;;
        DMA_CHTOCTL(dma_periph, channelx)    = DMA_CHTOCTL_RESET_VALUE;
        DMA_CHPCRCDATA(dma_periph, channelx) = DMA_CHPCRCDATA_RESET_VALUE;
        DMA_TOINTF(dma_periph)               = DMA_TOINTF_RESET_VALUE;
        DMA_TOINTEN(dma_periph)              = DMA_TOINTEN_RESET_VALUE;
        DMA_TFINTF(dma_periph)               = DMA_TFINTF_RESET_VALUE;
        DMA_TFINTEN(dma_periph)              = DMA_TFINTEN_RESET_VALUE;

        if(channelx < DMA_CH4) {
            DMA_INTC0(dma_periph) |= DMA_FLAG_ADD(DMA_CHINTF_RESET_VALUE, channelx);
        }
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        else if((uint32_t)channelx < ((uint32_t)DMA_CH7 + 1U)) {
#else
        else {
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
            DMA_INTC1(dma_periph) |= DMA_FLAG_ADD(DMA_CHINTF_RESET_VALUE, (uint32_t)channelx - (uint32_t)DMA_CH4);
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        } else if(channelx < DMA_CH12) {
            DMA_INTC2(dma_periph) |= DMA_FLAG_ADD(DMA_CHINTF_RESET_VALUE, (uint32_t)channelx - (uint32_t)DMA_CH8);
        } else {
            DMA_INTC3(dma_periph) |= DMA_FLAG_ADD(DMA_CHINTF_RESET_VALUE, (uint32_t)channelx - (uint32_t)DMA_CH12);
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
        }
    }
}

/*!
    \brief      initialize the DMA single data mode parameters struct with the default values (API_ID(0x0002U))
    \param[in]  init_struct: the initialization data needed to initialize DMA channel
    \param[out] none
    \retval     none
*/
void dma_single_data_para_struct_init(dma_single_data_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the DMA struct with the default values */
        init_struct->request              = DMA_REQUEST_M2M;
        init_struct->periph_addr          = 0U;
        init_struct->periph_inc           = DMA_PERIPH_INCREASE_DISABLE;
        init_struct->memory0_addr         = 0U;
        init_struct->memory_inc           = DMA_MEMORY_INCREASE_DISABLE;
        init_struct->periph_memory_width  = 0U;
        init_struct->periph_addr_circular = DMA_PERIPH_ADDR_CIRCULAR_DISABLE;
        init_struct->memory_addr_circular = DMA_MEMORY_ADDR_CIRCULAR_DISABLE;
        init_struct->direction            = DMA_PERIPH_TO_MEMORY;
        init_struct->number               = 0U;
        init_struct->priority             = DMA_PRIORITY_LOW;
    }
}

/*!
    \brief      initialize the DMA multi data mode parameters struct with the default values (API_ID(0x0003U))
    \param[in]  init_struct: the initialization data needed to initialize DMA channel
    \param[out] none
    \retval     none
*/
void dma_multi_data_para_struct_init(dma_multi_data_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the DMA struct with the default values */
        init_struct->request             = DMA_REQUEST_M2M;
        init_struct->periph_addr         = 0U;
        init_struct->periph_width        = 0U;
        init_struct->periph_inc          = DMA_PERIPH_INCREASE_DISABLE;
        init_struct->memory0_addr        = 0U;
        init_struct->memory_width        = 0U;
        init_struct->memory_inc          = DMA_MEMORY_INCREASE_DISABLE;
        init_struct->memory_burst_width  = 0U;
        init_struct->periph_burst_width  = 0U;
        init_struct->periph_addr_circular = DMA_PERIPH_ADDR_CIRCULAR_DISABLE;
        init_struct->memory_addr_circular = DMA_MEMORY_ADDR_CIRCULAR_DISABLE;
        init_struct->direction           = DMA_PERIPH_TO_MEMORY;
        init_struct->number              = 0U;
        init_struct->priority            = DMA_PRIORITY_LOW;
        init_struct->critical_value      = DMA_FIFO_2_WORD;
    }
}

/*!
    \brief      initialize DMA single data mode (API_ID(0x0004U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel is initialized
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  init_struct: the data needed to initialize DMA single data mode
                  request: DMA_REQUEST_x x is the type of request
                  periph_addr: peripheral base address
                  periph_inc: DMA_PERIPH_INCREASE_ENABLE,DMA_PERIPH_INCREASE_DISABLE,DMA_PERIPH_INCREASE_FIX
                  memory0_addr: memory base address
                  memory_inc: DMA_MEMORY_INCREASE_ENABLE,DMA_MEMORY_INCREASE_DISABLE
                  periph_memory_width: DMA_PERIPH_WIDTH_8BIT, DMA_PERIPH_WIDTH_16BIT, DMA_PERIPH_WIDTH_32BIT, DMA_PERIPH_WIDTH_64BIT
                  periph_addr_circular: DMA_PERIPH_ADDR_CIRCULAR_ENABLE, DMA_PERIPH_ADDR_CIRCULAR_DISABLE
                  memory_addr_circular: DMA_MEMORY_ADDR_CIRCULAR_ENABLE, DMA_MEMORY_ADDR_CIRCULAR_DISABLE
                  direction: DMA_PERIPH_TO_MEMORY, DMA_MEMORY_TO_PERIPH, DMA_MEMORY_TO_MEMORY
                  number: the number of remaining data to be transferred by the DMA
                  priority: DMA_PRIORITY_LOW, DMA_PRIORITY_MEDIUM, DMA_PRIORITY_HIGH, DMA_PRIORITY_ULTRA_HIGH
    \param[out] none
    \retval     none
*/
void dma_single_data_mode_init(uint32_t dma_periph, dma_channel_enum channelx, dma_single_data_parameter_struct *init_struct)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else if(NOT_DMA_REQUEST(init_struct->request)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_INCREASE(init_struct->periph_inc)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_INCREASE(init_struct->memory_inc)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_MEMORY_WIDTH(init_struct->periph_memory_width)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_ADDR_CIRCULAR(init_struct->periph_addr_circular)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_ADDR_CIRCULAR(init_struct->memory_addr_circular)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_TRANSFER_DIRECTION(init_struct->direction)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_NUMBER(init_struct->number)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PRIORITY(init_struct->priority)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* select single data mode */
        DMA_CHFCTL(dma_periph, channelx) &= ~DMA_CHXFCTL_MDMEN;

        /* configure peripheral base address */
        DMA_CHPADDR(dma_periph, channelx) = init_struct->periph_addr;

        /* configure memory base address */
        DMA_CHM0ADDR(dma_periph, channelx) = init_struct->memory0_addr;

        /* configure the number of remaining data to be transferred */
        DMA_CHCNT(dma_periph, channelx) = init_struct->number;

        /* configure peripheral and memory transfer width,channel priority, transfer mode */
        ctl = DMA_CHCTL(dma_periph, channelx);
        ctl &= ~(DMA_CHXCTL_PWIDTH | DMA_CHXCTL_MWIDTH | DMA_CHXCTL_PRIO | DMA_CHXCTL_TM);
        ctl |= (init_struct->periph_memory_width | (init_struct->periph_memory_width << 2) | init_struct->priority |
                init_struct->direction);
        DMA_CHCTL(dma_periph, channelx) = ctl;

        /* configure peripheral increasing mode */
        if(DMA_PERIPH_INCREASE_ENABLE == init_struct->periph_inc) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
        } else if(DMA_PERIPH_INCREASE_DISABLE == init_struct->periph_inc) {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PNAGA;
        } else {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PAIF;
        }

        /* configure memory increasing mode */
        if(DMA_MEMORY_INCREASE_ENABLE == init_struct->memory_inc) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MNAGA;
        } else {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MNAGA;
        }

        /* configure memory increasing mode */
        if(DMA_MEMORY_INCREASE_ENABLE == init_struct->memory_inc) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MNAGA;
        } else {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MNAGA;
        }

        /* configure DMA peripheral address circular mode */
        if(DMA_PERIPH_ADDR_CIRCULAR_ENABLE == init_struct->periph_addr_circular) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PCEN;
        } else {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PCEN;
        }

        /* configure DMA memory address circular mode */
        if(DMA_MEMORY_ADDR_CIRCULAR_ENABLE == init_struct->memory_addr_circular) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MCEN;
        } else {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MCEN;
        }

        /* configure DMA circular mode */
        if((DMA_PERIPH_ADDR_CIRCULAR_ENABLE== init_struct->periph_addr_circular) || \
            (DMA_MEMORY_ADDR_CIRCULAR_ENABLE == init_struct->memory_addr_circular)) {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CMEN;
        } else {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_CMEN;
        }

        if(DMA0 == dma_periph) {
            DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_MUXID;
            DMAMUX_RM_CHXCFG(channelx) |= init_struct->request;
        } else {
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            DMAMUX_RM_CHXCFG((uint32_t)channelx + 16U) &= ~DMAMUX_RM_CHXCFG_MUXID;
            DMAMUX_RM_CHXCFG((uint32_t)channelx + 16U) |= init_struct->request;
#else
            DMAMUX_RM_CHXCFG((uint32_t)channelx + 8U) &= ~DMAMUX_RM_CHXCFG_MUXID;
            DMAMUX_RM_CHXCFG((uint32_t)channelx + 8U) |= init_struct->request;
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
        }
    }
}

/*!
    \brief      initialize DMA multi data mode (API_ID(0x0005U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel is initialized
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  dma_multi_data_parameter_struct: the data needed to initialize DMA multi data mode
                  request: DMA_REQUEST_x x is the type of request
                  periph_addr: peripheral base address
                  periph_width: DMA_PERIPH_WIDTH_8BIT,DMA_PERIPH_WIDTH_16BIT,DMA_PERIPH_WIDTH_32BIT,DMA_PERIPH_WIDTH_64BIT
                  periph_inc: DMA_PERIPH_INCREASE_ENABLE,DMA_PERIPH_INCREASE_DISABLE,DMA_PERIPH_INCREASE_FIX
                  memory0_addr: memory0 base address
                  memory_width: DMA_MEMORY_WIDTH_8BIT,DMA_MEMORY_WIDTH_16BIT,DMA_MEMORY_WIDTH_32BIT,DMA_MEMORY_WIDTH_64BIT
                  memory_inc: DMA_MEMORY_INCREASE_ENABLE,DMA_MEMORY_INCREASE_DISABLE
                  memory_burst_width: DMA_MEMORY_BURST_SINGLE,DMA_MEMORY_BURST_4_BEAT,DMA_MEMORY_BURST_8_BEAT,DMA_MEMORY_BURST_16_BEAT
                  periph_burst_width: DMA_PERIPH_BURST_SINGLE,DMA_PERIPH_BURST_4_BEAT,DMA_PERIPH_BURST_8_BEAT,DMA_PERIPH_BURST_16_BEAT
                  critical_value: DMA_FIFO_2_WORD,DMA_FIFO_4_WORD,DMA_FIFO_6_WORD,DMA_FIFO_8_WORD
                  periph_addr_circular: DMA_PERIPH_ADDR_CIRCULAR_ENABLE, DMA_PERIPH_ADDR_CIRCULAR_DISABLE
                  memory_addr_circular: DMA_MEMORY_ADDR_CIRCULAR_ENABLE, DMA_MEMORY_ADDR_CIRCULAR_DISABLE
                  direction: DMA_PERIPH_TO_MEMORY,DMA_MEMORY_TO_PERIPH,DMA_MEMORY_TO_MEMORY
                  number: the number of remaining data to be transferred by the DMA
                  priority: DMA_PRIORITY_LOW,DMA_PRIORITY_MEDIUM,DMA_PRIORITY_HIGH,DMA_PRIORITY_ULTRA_HIGH
    \param[out] none
    \retval     none
*/
void dma_multi_data_mode_init(uint32_t dma_periph, dma_channel_enum channelx, dma_multi_data_parameter_struct *init_struct)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_POINTER);
    } else if(NOT_DMA_REQUEST(init_struct->request)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_INCREASE(init_struct->periph_inc)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_INCREASE(init_struct->memory_inc)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_WIDTH(init_struct->periph_width)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_WIDTH(init_struct->memory_width)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_BURST_WIDTH(init_struct->memory_burst_width)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_BURST_WIDTH(init_struct->periph_burst_width)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_FIFO_CRITICAL_VALUE(init_struct->critical_value)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_ADDR_CIRCULAR(init_struct->periph_addr_circular)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_ADDR_CIRCULAR(init_struct->memory_addr_circular)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_TRANSFER_DIRECTION(init_struct->direction)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_NUMBER(init_struct->number)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PRIORITY(init_struct->priority)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* select multi data mode and configure FIFO critical value */
        DMA_CHFCTL(dma_periph, channelx) &= ~(DMA_CHXFCTL_FCCV);
        DMA_CHFCTL(dma_periph, channelx) |= (DMA_CHXFCTL_MDMEN | init_struct->critical_value);

        /* configure peripheral base address */
        DMA_CHPADDR(dma_periph, channelx) = init_struct->periph_addr;

        /* configure memory base address */
        DMA_CHM0ADDR(dma_periph, channelx) = init_struct->memory0_addr;

        /* configure the number of remaining data to be transferred */
        DMA_CHCNT(dma_periph, channelx) = init_struct->number;

        /* configure peripheral and memory transfer width,channel priority, transfer mode,peripheral and memory burst transfer width */
        ctl = DMA_CHCTL(dma_periph, channelx);
        ctl &= ~(DMA_CHXCTL_PWIDTH | DMA_CHXCTL_MWIDTH | DMA_CHXCTL_PRIO | DMA_CHXCTL_TM | DMA_CHXCTL_PBURST |
                 DMA_CHXCTL_MBURST);
        ctl |= (init_struct->periph_width | (init_struct->memory_width) | init_struct->priority | init_struct->direction |
                init_struct->memory_burst_width | init_struct->periph_burst_width);
        DMA_CHCTL(dma_periph, channelx) = ctl;

        /* configure peripheral increasing mode */
        if(DMA_PERIPH_INCREASE_ENABLE == init_struct->periph_inc) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
        } else if(DMA_PERIPH_INCREASE_DISABLE == init_struct->periph_inc) {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PNAGA;
        } else {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PAIF;
        }

        /* configure memory increasing mode */
        if(DMA_MEMORY_INCREASE_ENABLE == init_struct->memory_inc) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MNAGA;
        } else {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MNAGA;
        }

        /* configure DMA peripheral address circular mode */
        if(DMA_PERIPH_ADDR_CIRCULAR_ENABLE == init_struct->periph_addr_circular) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PCEN;
        } else {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PCEN;
        }

        /* configure DMA memory address circular mode */
        if(DMA_MEMORY_ADDR_CIRCULAR_ENABLE == init_struct->memory_addr_circular) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MCEN;
        } else {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MCEN;
        }

        /* configure DMA circular mode */
        if((DMA_PERIPH_ADDR_CIRCULAR_ENABLE== init_struct->periph_addr_circular) || \
            (DMA_MEMORY_ADDR_CIRCULAR_ENABLE == init_struct->memory_addr_circular)) {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CMEN;
        } else {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_CMEN;
        }

        if(DMA0 == dma_periph) {
            DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_MUXID;
            DMAMUX_RM_CHXCFG(channelx) |= init_struct->request;
        } else {
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            DMAMUX_RM_CHXCFG((uint32_t)channelx + 16U) &= ~DMAMUX_RM_CHXCFG_MUXID;
            DMAMUX_RM_CHXCFG((uint32_t)channelx + 16U) |= init_struct->request;
#else
            DMAMUX_RM_CHXCFG((uint32_t)channelx + 8U) &= ~DMAMUX_RM_CHXCFG_MUXID;
            DMAMUX_RM_CHXCFG((uint32_t)channelx + 8U) |= init_struct->request;
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
        }
    }
}

/*!
    \brief      set DMA peripheral base address (API_ID(0x0006U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to set peripheral base address
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  address: peripheral base address
    \param[out] none
    \retval     none
*/
void dma_periph_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHPADDR(dma_periph, channelx) = address;
    }
}

/*!
    \brief      set DMA memory base address (API_ID(0x0007U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to set memory base address
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  memory_flag: DMA_MEMORY_x(x=0,1)
    \param[in]  address:memory base address
    \param[out] none
    \retval     none
*/
void dma_memory_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t memory_flag, uint32_t address)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_FLAG(memory_flag)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DMA_MEMORY_1 == memory_flag) {
            DMA_CHM1ADDR(dma_periph, channelx) = address;
        } else {
            DMA_CHM0ADDR(dma_periph, channelx) = address;
        }
    }
}

/*!
    \brief      set the number of remaining data to be transferred by the DMA (API_ID(0x0008U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to set number
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  number: the number of remaining data to be transferred by the DMA
    \param[out] none
    \retval     none
*/
void dma_transfer_number_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t number)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_NUMBER(number)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCNT(dma_periph, channelx) = number;
    }
}

/*!
    \brief      get the number of remaining data to be transferred by the DMA (API_ID(0x0009U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to get number
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     uint32_t: the number of remaining data to be transferred by the DMA
*/
uint32_t dma_transfer_number_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = (uint32_t)DMA_CHCNT(dma_periph, channelx);
    }
    return reval;
}

/*!
    \brief      configure priority level of DMA channel (API_ID(0x000AU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  priority: priority Level of this channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_PRIORITY_LOW: low priority
      \arg        DMA_PRIORITY_MEDIUM: medium priority
      \arg        DMA_PRIORITY_HIGH: high priority
      \arg        DMA_PRIORITY_ULTRA_HIGH: ultra high priority
    \param[out] none
    \retval     none
*/
void dma_priority_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t priority)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PRIORITY(priority)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* acquire DMA_CHxCTL register */
        ctl = DMA_CHCTL(dma_periph, channelx);
        /* assign register */
        ctl &= ~DMA_CHXCTL_PRIO;
        ctl |= priority;
        DMA_CHCTL(dma_periph, channelx) = ctl;
    }
}

/*!
    \brief      configure transfer burst beats of memory (API_ID(0x000BU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  mbeat: transfer burst beats
                only one parameter can be selected which is shown as below:
      \arg        DMA_MEMORY_BURST_SINGLE: memory transfer single burst
      \arg        DMA_MEMORY_BURST_4_BEAT: memory transfer 4-beat burst
      \arg        DMA_MEMORY_BURST_8_BEAT: memory transfer 8-beat burst
      \arg        DMA_MEMORY_BURST_16_BEAT: memory transfer 16-beat burst
    \param[out] none
    \retval     none
*/
void dma_memory_burst_beats_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t mbeat)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_BURST_WIDTH(mbeat)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* acquire DMA_CHxCTL register */
        ctl = DMA_CHCTL(dma_periph, channelx);
        /* assign register */
        ctl &= ~DMA_CHXCTL_MBURST;
        ctl |= mbeat;
        DMA_CHCTL(dma_periph, channelx) = ctl;
    }
}

/*!
    \brief      configure transfer burst beats of peripheral (API_ID(0x000CU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  pbeat: transfer burst beats
                only one parameter can be selected which is shown as below:
      \arg        DMA_PERIPH_BURST_SINGLE: peripheral transfer single burst
      \arg        DMA_PERIPH_BURST_4_BEAT: peripheral transfer 4-beat burst
      \arg        DMA_PERIPH_BURST_8_BEAT: peripheral transfer 8-beat burst
      \arg        DMA_PERIPH_BURST_16_BEAT: peripheral transfer 16-beat burst
    \param[out] none
    \retval     none
*/
void dma_periph_burst_beats_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t pbeat)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_BURST_WIDTH(pbeat)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* acquire DMA_CHxCTL register */
        ctl = DMA_CHCTL(dma_periph, channelx);
        /* assign register */
        ctl &= ~DMA_CHXCTL_PBURST;
        ctl |= pbeat;
        DMA_CHCTL(dma_periph, channelx) = ctl;
    }
}

/*!
    \brief      configure transfer data size of memory (API_ID(0x000DU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  msize: transfer data size of memory
                only one parameter can be selected which is shown as below:
      \arg        DMA_MEMORY_WIDTH_8BIT: transfer data size of memory is 8-bit
      \arg        DMA_MEMORY_WIDTH_16BIT: transfer data size of memory is 16-bit
      \arg        DMA_MEMORY_WIDTH_32BIT: transfer data size of memory is 32-bit
      \arg        DMA_MEMORY_WIDTH_64BIT: transfer data size of memory is 64-bit
    \param[out] none
    \retval     none
*/
void dma_memory_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t msize)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_WIDTH(msize)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* acquire DMA_CHxCTL register */
        ctl = DMA_CHCTL(dma_periph, channelx);
        /* assign register */
        ctl &= ~DMA_CHXCTL_MWIDTH;
        ctl |= msize;
        DMA_CHCTL(dma_periph, channelx) = ctl;
    }
}

/*!
    \brief      configure transfer data size of peripheral (API_ID(0x000EU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  psize: transfer data size of peripheral
                only one parameter can be selected which is shown as below:
      \arg        DMA_PERIPH_WIDTH_8BIT: transfer data size of peripheral is 8-bit
      \arg        DMA_PERIPH_WIDTH_16BIT: transfer data size of peripheral is 16-bit
      \arg        DMA_PERIPH_WIDTH_32BIT: transfer data size of peripheral is 32-bit
      \arg        DMA_PERIPH_WIDTH_64BIT: transfer data size of peripheral is 64-bit
    \param[out] none
    \retval     none
*/
void dma_periph_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t psize)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_WIDTH(psize)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* acquire DMA_CHxCTL register */
        ctl = DMA_CHCTL(dma_periph, channelx);
        /* assign register */
        ctl &= ~DMA_CHXCTL_PWIDTH;
        ctl |= psize;
        DMA_CHCTL(dma_periph, channelx) = ctl;
    }
}

/*!
    \brief      configure memory address generation generation_algorithm (API_ID(0x000FU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  generation_algorithm: the address generation algorithm
                only one parameter can be selected which is shown as below:
      \arg        DMA_MEMORY_INCREASE_ENABLE: next address of memory is increasing address mode
      \arg        DMA_MEMORY_INCREASE_DISABLE: next address of memory is fixed address mode
    \param[out] none
    \retval     none
*/
void dma_memory_address_generation_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t generation_algorithm)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_INCREASE(generation_algorithm)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DMA_MEMORY_INCREASE_ENABLE == generation_algorithm) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MNAGA;
        } else {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MNAGA;
        }
    }
}

/*!
    \brief      configure peripheral address generation_algorithm (API_ID(0x0010U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  generation_algorithm: the address generation algorithm
                only one parameter can be selected which is shown as below:
      \arg        DMA_PERIPH_INCREASE_ENABLE: next address of peripheral is increasing address mode
      \arg        DMA_PERIPH_INCREASE_DISABLE: next address of peripheral is fixed address mode
      \arg        DMA_PERIPH_INCREASE_FIX: increasing steps of peripheral address is fixed
    \param[out] none
    \retval     none
*/
void dma_peripheral_address_generation_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t generation_algorithm)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_PERIPH_INCREASE(generation_algorithm)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DMA_PERIPH_INCREASE_ENABLE == generation_algorithm) {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
        } else if(DMA_PERIPH_INCREASE_DISABLE == generation_algorithm) {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PNAGA;
        } else {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PNAGA;
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PAIF;
        }
    }
}

/*!
    \brief      enable DMA circulation mode (API_ID(0x0011U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0011U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_CMEN;
    }
}

/*!
    \brief      disable DMA circulation mode (API_ID(0x0012U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CMEN;
    }
}

/*!
    \brief      enable DMA channel (API_ID(0x0013U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_channel_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_CHEN;
    }
}

/*!
    \brief      disable DMA channel (API_ID(0x0014U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_channel_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0014U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_CHEN;
    }
}

/*!
    \brief      configure the direction of data transfer on the channel (API_ID(0x0015U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  direction: specify the direction of  data transfer
                only one parameter can be selected which is shown as below:
      \arg        DMA_PERIPH_TO_MEMORY: read from peripheral and write to memory
      \arg        DMA_MEMORY_TO_PERIPH: read from memory and write to peripheral
      \arg        DMA_MEMORY_TO_MEMORY: read from memory and write to memory
    \param[out] none
    \retval     none
*/
void dma_transfer_direction_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t direction)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_TRANSFER_DIRECTION(direction)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* acquire DMA_CHxCTL register */
        ctl = DMA_CHCTL(dma_periph, channelx);
        /* assign register */
        ctl &= ~DMA_CHXCTL_TM;
        ctl |= direction;
        DMA_CHCTL(dma_periph, channelx) = ctl;
    }
}

/*!
    \brief      DMA switch buffer mode configure (API_ID(0x0016U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  memory1_addr: memory1 base address
    \param[in]  memory_select: memory select
                only one parameter can be selected which is shown as below:
      \arg        DMA_MEMORY_0
      \arg        DMA_MEMORY_1
    \param[out] none
    \retval     none
*/
void dma_switch_buffer_mode_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t memory1_addr, uint32_t memory_select)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0016U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_MEMORY_FLAG(memory_select)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0016U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure memory1 base address */
        DMA_CHM1ADDR(dma_periph, channelx) = memory1_addr;
        if(DMA_MEMORY_0 == memory_select) {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MBS;
        } else {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MBS;
        }
    }
}

/*!
    \brief      DMA using memory get (API_ID(0x0017U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     the using memory
*/
uint32_t dma_using_memory_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    uint32_t reval = DMA_MEMORY_0;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0017U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DMA_CHXCTL_MBS == ((DMA_CHCTL(dma_periph, channelx)) & DMA_CHXCTL_MBS)) {
            reval = DMA_MEMORY_1;
        } else {
            reval = DMA_MEMORY_0;
        }
    }
    return reval;
}

/*!
    \brief      enable dma channel peripheral address circulation function (API_ID(0x0018U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_peripheral_address_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0018U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_PCEN;
    }
}

/*!
    \brief      disable dma channel peripheral address circulation function (API_ID(0x0019U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_peripheral_address_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0019U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_PCEN;
    }
}

/*!
    \brief      enable dma channel memory address circulation function (API_ID(0x001AU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_memory_address_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_MCEN;
    }
}

/*!
    \brief      disable dma channel memory address circulation function (API_ID(0x001BU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_memory_address_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_MCEN;
    }
}

/*!
    \brief      enable dma channel circulation count function (API_ID(0x001CU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_circulation_count_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCNT(dma_periph, channelx) |= DMA_CHXCNT_CCNTEN;
    }
}

/*!
    \brief      disable dma channel circulation count function (API_ID(0x001DU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dma_circulation_count_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCNT(dma_periph, channelx) &= ~DMA_CHXCNT_CCNTEN;
    }
}

/*!
    \brief      configure dma channel circulation count (API_ID(0x001EU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..7)
    \param[in]  count: circulation count
      \arg        0~255
    \param[out] none
    \retval     none
*/
void dma_circulation_count_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t count)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHCNT(dma_periph, channelx) &= ~DMA_CHXCNT_CCNT;
        DMA_CHCNT(dma_periph, channelx) |= (uint32_t)((uint32_t)count << 24U);
    }
}

/*!
    \brief      enable dma priority round robin function (API_ID(0x001FU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  priority: channel priority
      \arg        DMA_RR_PRIORITY_LOW: round-robin for channels with low software priority level
      \arg        DMA_RR_PRIORITY_MEDIUM: round-robin for channels with medium software priority level
      \arg        DMA_RR_PRIORITY_HIGH: round-robin for channels with high software priority level
      \arg        DMA_RR_PRIORITY_ULTRA_HIGH: round-robin for channels with ultra high software priority level
    \param[out] none
    \retval     none
*/
void dma_round_robin_mode_enable(uint32_t dma_periph, uint32_t priority)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    } else if(NOT_DMA_RR_PRIORITY(priority)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x001FU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_GCTL(dma_periph) |= priority;
    }
}

/*!
    \brief      disable dma priority round robin function (API_ID(0x0020U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  priority: channel priority
      \arg        DMA_RR_PRIORITY_LOW: round-robin for channels with low software priority level
      \arg        DMA_RR_PRIORITY_MEDIUM: round-robin for channels with medium software priority level
      \arg        DMA_RR_PRIORITY_HIGH: round-robin for channels with high software priority level
      \arg        DMA_RR_PRIORITY_ULTRA_HIGH: round-robin for channels with ultra high software priority level
    \param[out] none
    \retval     none
*/
void dma_round_robin_mode_disable(uint32_t dma_periph, uint32_t priority)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0020U), ERR_PERIPH);
    } else if(NOT_DMA_RR_PRIORITY(priority)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0020U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_GCTL(dma_periph) &= ~priority;
    }
}

/*!
    \brief      DMA flow controller configure (API_ID(0x0021U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  controller: specify DMA flow controller
                only one parameter can be selected which is shown as below:
      \arg        DMA_FLOW_CONTROLLER_DMA: DMA is the flow controller
      \arg        DMA_FLOW_CONTROLLER_PERI: peripheral is the flow controller
    \param[out] none
    \retval     none
*/
void dma_flow_controller_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t controller)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0021U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0021U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_FLOW_CONTROLLER(controller)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0021U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DMA_FLOW_CONTROLLER_DMA == controller) {
            DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_TFCS;
        } else {
            DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_TFCS;
        }
    }
}

/*!
    \brief      enable DMA switch buffer mode (API_ID(0x0022U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_switch_buffer_mode_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0022U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0022U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* switch buffer mode enable */
        DMA_CHCTL(dma_periph, channelx) |= DMA_CHXCTL_SBMEN;
    }
}

/*!
    \brief      disable DMA switch buffer mode (API_ID(0x0023U))
    \param[in]  dma_periph: DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_switch_buffer_mode_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0023U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0023U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable switch buffer mode */
        DMA_CHCTL(dma_periph, channelx) &= ~DMA_CHXCTL_SBMEN;
    }
}

/*!
    \brief      DMA FIFO status get (API_ID(0x0024U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     the number of data stored in FIFO
                only one parameter can be selected which is shown as below:
      \arg        DMA_FIFO_CNT_0_2_DATA: 0 - 2 words
      \arg        DMA_FIFO_CNT_2_4_WORD: 2 - 4 words
      \arg        DMA_FIFO_CNT_4_6_WORD: 4 - 6 words
      \arg        DMA_FIFO_CNT_6_8_WORD: 6 - 8 words
      \arg        DMA_FIFO_CNT_EMPTY: empty
      \arg        DMA_FIFO_CNT_FULL: full
*/
uint32_t dma_fifo_status_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0024U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0024U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = ((DMA_CHFCTL(dma_periph, channelx) & DMA_CHXFCTL_FCNT) >> CHXFCTL_FCNT_OFFSET);
    }
    return reval;
}

/*!
    \brief      get DMA channel peripheral port CRC value (API_ID(0x0025U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     peripheral port CRC value
*/
uint32_t dma_peripheral_port_crc_value_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0025U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0025U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = DMA_CHPCRCDATA(dma_periph, channelx);
    }
    return reval;
}

/*!
    \brief      set DMA channel peripheral port CRC value (API_ID(0x0026U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  data: specify channel initial crc data value, range 0~0xFFFFFFFF
    \param[out] none
    \retval     none
*/
void dma_peripheral_port_crc_value_set(uint32_t dma_periph, dma_channel_enum channelx, uint32_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0026U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0026U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHPCRCDATA(dma_periph, channelx) = data;
    }
}

/*!
    \brief      set DMA peripheral port initial CRC data (API_ID(0x0027U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  data: peripheral port initial CRC data
    \param[out] none
    \retval     none
*/
void dma_peripheral_port_initial_crc_value_set(uint32_t dma_periph, uint32_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0027U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CRCIDATA(dma_periph) = data;
    }
}

/*!
    \brief      get DMA peripheral port initial CRC value (API_ID(0x0028U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[out] none
    \retval     peripheral port initial CRC value
*/
uint32_t dma_peripheral_port_initial_crc_value_get(uint32_t dma_periph)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0028U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval =  DMA_CRCIDATA(dma_periph);
    }
    return reval;
}

/*!
    \brief      deinit DMA channel peripheral port CRC value (API_ID(0x0029U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_peripheral_port_crc_value_deinit(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0029U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0029U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_PCRCCTL(dma_periph) |= ((uint32_t)1U << channelx);
    }
}

/*!
    \brief      get DMA channel peripheral port current transferred address (API_ID(0x002AU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     peripheral port current transferred address
*/
uint32_t dma_peripheral_port_current_address_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002AU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = DMA_CHPCADDR(dma_periph, channelx);
    }
    return reval;
}

/*!
    \brief      get DMA channel memory port current transferred address (API_ID(0x002BU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     memory port current transferred address
*/
uint32_t dma_memory_port_current_address_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002BU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = DMA_CHMCADDR(dma_periph, channelx);
    }
    return reval;
}

/*!
    \brief      enable DMA channel transfer timeout monitor (API_ID(0x002CU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_transfer_timeout_monitor_enable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002CU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHTOCTL(dma_periph, channelx) |= DMA_CHXTOCTL_CHTOEN;
    }
}

/*!
    \brief      disable DMA channel transfer timeout monitor (API_ID(0x002DU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[out] none
    \retval     none
*/
void dma_transfer_timeout_monitor_disable(uint32_t dma_periph, dma_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002DU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMA_CHTOCTL(dma_periph, channelx) &= ~DMA_CHXTOCTL_CHTOEN;
    }
}

/*!
    \brief      set DMA channel transfer timeout threshold value (API_ID(0x002EU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
\param[in]  threshold_value: specify transfer timeout threshold value(unit:HCLK), min 0x00000000, max 0x1FFFFF
    \param[out] none
    \retval     none
*/
void dma_transfer_timeout_threshold_value_set(uint32_t dma_periph, dma_channel_enum channelx, uint32_t threshold_value)
{
    uint32_t ctl;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002EU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002EU), ERR_PARAM_INVALID);
    } else if(NOT_DMA_TIMEOUT_THRESHOLD(threshold_value)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* acquire DMA_CHxCTL register */
        ctl = DMA_CHTOCTL(dma_periph, channelx);
        /* assign register */
        ctl &= ~DMA_CHXTOCTL_PEROID;
        ctl |= (threshold_value & DMA_CHXTOCTL_PEROID);
        DMA_CHTOCTL(dma_periph, channelx) = ctl;
    }
}

/*!
    \brief      get DMA channel transfer timeout threshold value (API_ID(0x002FU))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  threshold_value: specify transfer timeout threshold value, min 0x00000000, max 0x1FFFFF
    \param[out] none
    \retval     transfer timeout threshold value
*/
uint32_t dma_transfer_timeout_threshold_value_get(uint32_t dma_periph, dma_channel_enum channelx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002FU), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x002FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = (DMA_CHTOCTL(dma_periph, channelx) & DMA_CHXTOCTL_PEROID);
    }
    return reval;
}

/*!
    \brief      get DMA flag is set or not (API_ID(0x0030U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to get flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_FLAG_FEE: FIFO error and exception flag
      \arg        DMA_FLAG_SDE: single data mode exception flag
      \arg        DMA_FLAG_TAE: transfer access error flag
      \arg        DMA_FLAG_HTF: half transfer finish flag
      \arg        DMA_FLAG_FTF: full transfer finish flag
      \arg        DMA_FLAG_TIMEOUT: transfer timeout flag
      \arg        DMA_FLAG_TMR_FAULT: control register TMR fault flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dma_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0030U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0030U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_FLAG(flag)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0030U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DMA_FLAG_TIMEOUT == flag) {
            if(0U != (DMA_TOINTF(dma_periph) & ((uint32_t)1U << (uint32_t)channelx))) {
                reval = SET;
            } else {
                reval = RESET;
            }
        } else if(DMA_FLAG_TMR_FAULT == flag) {
            if(0U != (DMA_TFINTF(dma_periph) & ((uint32_t)1U << (uint32_t)channelx))) {
                reval = SET;
            } else {
                reval = RESET;
            }
        } else {
            if((uint32_t)channelx < (uint32_t)DMA_CH4) {
                if(0U != (DMA_INTF0(dma_periph) & DMA_FLAG_ADD(flag, channelx))) {
                    reval = SET;
                } else {
                    reval = RESET;
                }
            }
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            else if((uint32_t)channelx < (uint32_t)DMA_CH7 + 1U) {
#else
            else {
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
                if(0U != (DMA_INTF1(dma_periph) & DMA_FLAG_ADD(flag, (uint32_t)channelx - (uint32_t)DMA_CH4))) {
                    reval = SET;
                } else {
                    reval = RESET;
                }
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            } else if((uint32_t)channelx < (uint32_t)DMA_CH12) {
                if(0U != (DMA_INTF2(dma_periph) & DMA_FLAG_ADD(flag, (uint32_t)channelx - (uint32_t)DMA_CH8))) {
                    reval = SET;
                } else {
                    reval = RESET;
                }
            } else {
                if((0U != (DMA_INTF3(dma_periph) & DMA_FLAG_ADD(flag, (uint32_t)channelx - (uint32_t)DMA_CH12)))) {
                    reval = SET;
                } else {
                    reval = RESET;
                }
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
            }
        }
    }
    return reval;
}

/*!
    \brief      clear DMA a channel flag (API_ID(0x0031U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to clear flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_FLAG_FEE: FIFO error and exception flag
      \arg        DMA_FLAG_SDE: single data mode exception flag
      \arg        DMA_FLAG_TAE: transfer access error flag
      \arg        DMA_FLAG_HTF: half transfer finish flag
      \arg        DMA_FLAG_FTF: full transfer finish flag
      \arg        DMA_FLAG_TIMEOUT: transfer timeout flag
      \arg        DMA_FLAG_TMR_FAULT: control register TMR fault flag
    \param[out] none
    \retval     none
*/
void dma_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0031U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0031U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_FLAG(flag)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0031U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DMA_FLAG_TIMEOUT == flag) {
            DMA_TOINTF(dma_periph) = ((uint32_t)1U << (uint32_t)channelx);
        } else if(DMA_FLAG_TMR_FAULT == flag) {
            DMA_TFINTF(dma_periph) = ((uint32_t)1U << (uint32_t)channelx);
        } else {
            if((uint32_t)channelx < (uint32_t)DMA_CH4) {
                DMA_INTC0(dma_periph) |= DMA_FLAG_ADD(flag, (uint32_t)channelx);
            }
#if defined (GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            else if((uint32_t)channelx < ((uint32_t)DMA_CH7 + (uint32_t)1U)) {
#else
            else {
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
                DMA_INTC1(dma_periph) |= DMA_FLAG_ADD(flag, (uint32_t)channelx - (uint32_t)DMA_CH4);
#if defined (GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            } else if((uint32_t)channelx < (uint32_t)DMA_CH12) {
                DMA_INTC2(dma_periph) |= DMA_FLAG_ADD(flag, (uint32_t)channelx - (uint32_t)DMA_CH8);
            } else {
                DMA_INTC3(dma_periph) |= DMA_FLAG_ADD(flag, (uint32_t)channelx - (uint32_t)DMA_CH12);
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
            }
        }
    }
}

/*!
    \brief      get DMA interrupt flag is set or not (API_ID(0x0032U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to get interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  interrupt: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_INT_FLAG_FEE: FIFO error and exception flag
      \arg        DMA_INT_FLAG_SDE: single data mode exception flag
      \arg        DMA_INT_FLAG_TAE: transfer access error flag
      \arg        DMA_INT_FLAG_HTF: half transfer finish flag
      \arg        DMA_INT_FLAG_FTF: full transfer finish flag
      \arg        DMA_INT_FLAG_TIMEOUT: transfer timeout flag
      \arg        DMA_INT_FLAG_TMR_FAULT: control register TMR fault flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dma_interrupt_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0032U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0032U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_INTERRUPT_FLAG(interrupt)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0032U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t interrupt_enable = 0U, interrupt_flag = 0U;
        uint32_t channel_flag_offset = (uint32_t)channelx;
        if(DMA_INT_FLAG_TIMEOUT == interrupt) {
            interrupt_flag = DMA_TOINTF(dma_periph) & ((uint32_t)1U << (uint32_t)channelx);
            interrupt_enable = DMA_TOINTEN(dma_periph) & ((uint32_t)1U << (uint32_t)channelx);
        } else if(DMA_INT_FLAG_TMR_FAULT == interrupt) {
            interrupt_flag = DMA_TFINTF(dma_periph) & ((uint32_t)1U << (uint32_t)channelx);
            interrupt_enable = DMA_TFINTEN(dma_periph) & ((uint32_t)1U << (uint32_t)channelx);
        } else {
            if(channelx < DMA_CH4) {
                switch(interrupt) {
                case DMA_INTF_FEEIF:
                    interrupt_flag = DMA_INTF0(dma_periph) & DMA_FLAG_ADD(interrupt, channelx);
                    interrupt_enable = DMA_CHFCTL(dma_periph, channelx) & DMA_CHXFCTL_FEEIE;
                    break;
                case DMA_INTF_SDEIF:
                    interrupt_flag = DMA_INTF0(dma_periph) & DMA_FLAG_ADD(interrupt, channelx);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_SDEIE;
                    break;
                case DMA_INTF_TAEIF:
                    interrupt_flag = DMA_INTF0(dma_periph) & DMA_FLAG_ADD(interrupt, channelx);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_TAEIE;
                    break;
                case DMA_INTF_HTFIF:
                    interrupt_flag = DMA_INTF0(dma_periph) & DMA_FLAG_ADD(interrupt, channelx);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_HTFIE;
                    break;
                case DMA_INTF_FTFIF:
                    interrupt_flag = (DMA_INTF0(dma_periph) & DMA_FLAG_ADD(interrupt, channelx));
                    interrupt_enable = (DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_FTFIE);
                    break;
                default:
                    break;
                }
            }
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            else if((uint32_t)channelx < ((uint32_t)DMA_CH7 + 1U)) {
#else
            else {
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
                channel_flag_offset -= (uint32_t)DMA_CH4;
                switch(interrupt) {
                case DMA_INTF_FEEIF:
                    interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHFCTL(dma_periph, channelx) & DMA_CHXFCTL_FEEIE;
                    break;
                case DMA_INTF_SDEIF:
                    interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_SDEIE;
                    break;
                case DMA_INTF_TAEIF:
                    interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_TAEIE;
                    break;
                case DMA_INTF_HTFIF:
                    interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_HTFIE;
                    break;
                case DMA_INTF_FTFIF:
                    interrupt_flag = DMA_INTF1(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_FTFIE;
                    break;
                default:
                    break;
                }
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            } else if(channelx < DMA_CH12) {
                channel_flag_offset -= (uint32_t)DMA_CH8;
                switch(interrupt) {
                case DMA_INTF_FEEIF:
                    interrupt_flag = DMA_INTF2(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHFCTL(dma_periph, channelx) & DMA_CHXFCTL_FEEIE;
                    break;
                case DMA_INTF_SDEIF:
                    interrupt_flag = DMA_INTF2(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_SDEIE;
                    break;
                case DMA_INTF_TAEIF:
                    interrupt_flag = DMA_INTF2(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_TAEIE;
                    break;
                case DMA_INTF_HTFIF:
                    interrupt_flag = DMA_INTF2(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_HTFIE;
                    break;
                case DMA_INTF_FTFIF:
                    interrupt_flag = DMA_INTF2(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_FTFIE;
                    break;
                default:
                    break;
                }
            } else {
                channel_flag_offset -= (uint32_t)DMA_CH12;
                switch(interrupt) {
                case DMA_INTF_FEEIF:
                    interrupt_flag = DMA_INTF3(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHFCTL(dma_periph, channelx) & DMA_CHXFCTL_FEEIE;
                    break;
                case DMA_INTF_SDEIF:
                    interrupt_flag = DMA_INTF3(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_SDEIE;
                    break;
                case DMA_INTF_TAEIF:
                    interrupt_flag = DMA_INTF3(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_TAEIE;
                    break;
                case DMA_INTF_HTFIF:
                    interrupt_flag = DMA_INTF3(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_HTFIE;
                    break;
                case DMA_INTF_FTFIF:
                    interrupt_flag = DMA_INTF3(dma_periph) & DMA_FLAG_ADD(interrupt, channel_flag_offset);
                    interrupt_enable = DMA_CHCTL(dma_periph, channelx) & DMA_CHXCTL_FTFIE;
                    break;
                default:
                    break;
                }
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
            }
        }
        if((0U != interrupt_flag) && (0U != interrupt_enable)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear DMA a channel interrupt flag (API_ID(0x0033U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel to clear interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  interrupt: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        DMA_INT_FLAG_FEE: FIFO error and exception flag
      \arg        DMA_INT_FLAG_SDE: single data mode exception flag
      \arg        DMA_INT_FLAG_TAE: transfer access error flag
      \arg        DMA_INT_FLAG_HTF: half transfer finish flag
      \arg        DMA_INT_FLAG_FTF: full transfer finish flag
      \arg        DMA_INT_FLAG_TIMEOUT: transfer timeout flag
      \arg        DMA_INT_FLAG_TMR_FAULT: control register TMR fault flag
    \param[out] none
    \retval     none
*/
void dma_interrupt_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0033U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0033U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_INTERRUPT_FLAG(interrupt)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0033U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(DMA_INT_FLAG_TIMEOUT == interrupt) {
            DMA_TOINTF(dma_periph) = ((uint32_t)1U << (uint32_t)channelx);
        } else if(DMA_INT_FLAG_TMR_FAULT == interrupt) {
            DMA_TFINTF(dma_periph) = ((uint32_t)1U << (uint32_t)channelx);
        } else {
            if((uint32_t)channelx < (uint32_t)DMA_CH4) {
                DMA_INTC0(dma_periph) |= DMA_FLAG_ADD(interrupt, channelx);
            }
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            else if((uint32_t)channelx < ((uint32_t)DMA_CH7 + 1U)) {
#else
            else {
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
                DMA_INTC1(dma_periph) |= DMA_FLAG_ADD(interrupt, ((uint32_t)channelx - (uint32_t)DMA_CH4));
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            } else if((uint32_t)channelx < (uint32_t)DMA_CH12) {
                DMA_INTC2(dma_periph) |= DMA_FLAG_ADD(interrupt, ((uint32_t)channelx - (uint32_t)DMA_CH8));
            } else {
                DMA_INTC3(dma_periph) |= DMA_FLAG_ADD(interrupt, ((uint32_t)channelx - (uint32_t)DMA_CH12));
#endif /* GD32A714X or GD32A72XX or GD32A74XX */
            }
        }
    }
}

/*!
    \brief      enable DMA interrupt (API_ID(0x0034U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        DMA_INT_SDE: single data mode exception interrupt enable
      \arg        DMA_INT_TAE: transfer access error interrupt enable
      \arg        DMA_INT_HTF: half transfer finish interrupt enable
      \arg        DMA_INT_FTF: full transfer finish interrupt enable
      \arg        DMA_INT_FEE: FIFO exception interrupt enable
      \arg        DMA_INT_TIMEOUT: transfer timeout interrupt enable
      \arg        DMA_INT_TMR: control register TMR fault interrupt enable
    \param[out] none
    \retval     none
*/
void dma_interrupt_enable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0034U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0034U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_INTERRUPT(interrupt)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0034U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* enable timeout interrupt */
        if(DMA_INT_TIMEOUT == (interrupt & DMA_INT_TIMEOUT)) {
            DMA_TOINTEN(dma_periph) |= ((uint32_t)1U << (uint32_t)channelx);
        }

        /* enable control register TMR fault interrupt */
        if(DMA_INT_TMR == (interrupt & DMA_INT_TMR)) {
            DMA_TFINTEN(dma_periph) |= ((uint32_t)1U << (uint32_t)channelx);
        }

        if(DMA_CHXFCTL_FEEIE != (DMA_CHXFCTL_FEEIE & interrupt)) {
            /* enable DMA_INT_SDE or DMA_INT_TAE or DMA_INT_HTF or DMA_INT_FTF interrupt */
            DMA_CHCTL(dma_periph, channelx) |= (interrupt & DMA_CHXCTL_INT_MASK);
        } else {
            /* enable DMA_INT_SDE or DMA_INT_TAE or DMA_INT_HTF or DMA_INT_FTF or DMA_INT_FEE interrupt */
            DMA_CHFCTL(dma_periph, channelx) |= DMA_CHXFCTL_FEEIE;
            DMA_CHCTL(dma_periph, channelx) |= (interrupt & DMA_CHXCTL_INT_MASK);
        }
    }
}

/*!
    \brief      disable DMA interrupt (API_ID(0x0035U))
    \param[in]  dma_periph: DMAx(x=0,1)
      \arg        DMAx(x=0,1)
    \param[in]  channelx: specify which DMA channel
                only one parameter can be selected which is shown as below:
      \arg        DMA_CHx(x=0..15)
    \param[in]  interrupt: specify which interrupt to disable
                one or more parameters can be selected which are shown as below:
      \arg        DMA_INT_SDE: single data mode exception interrupt enable
      \arg        DMA_INT_TAE: transfer access error interrupt enable
      \arg        DMA_INT_HTF: half transfer finish interrupt enable
      \arg        DMA_INT_FTF: full transfer finish interrupt enable
      \arg        DMA_INT_FEE: FIFO exception interrupt enable
      \arg        DMA_INT_TIMEOUT: transfer timeout interrupt enable
      \arg        DMA_INT_TMR: control register TMR fault interrupt enable
    \param[out] none
    \retval     none
*/
void dma_interrupt_disable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_PERIPH(dma_periph)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0035U), ERR_PERIPH);
    } else if(NOT_DMA_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0035U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_INTERRUPT(interrupt)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0035U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable timeout interrupt */
        if(DMA_INT_TIMEOUT == (interrupt & DMA_INT_TIMEOUT)) {
            DMA_TOINTEN(dma_periph) &= ~(1U << (uint32_t)channelx);
        }

        /* disable control register TMR fault interrupt */
        if(DMA_INT_TMR == (interrupt & DMA_INT_TMR)) {
            DMA_TFINTEN(dma_periph) &= ~(1U << (uint32_t)channelx);
        }

        if(DMA_CHXFCTL_FEEIE != (DMA_CHXFCTL_FEEIE & interrupt)) {
            /* disable DMA_INT_SDE or DMA_INT_TAE or DMA_INT_HTF or DMA_INT_FTF interrupt */
            DMA_CHCTL(dma_periph, channelx) &= ~(interrupt & DMA_CHXCTL_INT_MASK);
        } else {
            /* disable DMA_INT_SDE or DMA_INT_TAE or DMA_INT_HTF or DMA_INT_FTF or DMA_INT_FEE interrupt */
            DMA_CHFCTL(dma_periph, channelx) &= ~DMA_CHXFCTL_FEEIE;
            DMA_CHCTL(dma_periph, channelx) &= ~(interrupt & DMA_CHXCTL_INT_MASK);
        }
    }
}

/*!
    \brief      initialize the parameters of DMAMUX synchronization mode structure with the default values (API_ID(0x0036U))
    \param[in]  none
    \param[out] init_struct: the initialization data needed to initialize DMAMUX request multiplexer channel synchronization mode
    \retval     none
*/
void dmamux_sync_struct_para_init(dmamux_sync_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0036U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the DMAMUX synchronization struct with the default values */
        init_struct->sync_id        = DMAMUX_SYNC_EVT0_OUT;
        init_struct->sync_polarity  = DMAMUX_SYNC_RISING;
        init_struct->request_number = 1U;
    }
}

/*!
    \brief      initialize DMAMUX request multiplexer channel synchronization mode (API_ID(0x0037U))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is initialized
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[in]  init_struct: the data needed to initialize DMAMUX request multiplexer channel
                  sync_id: DMAMUX_SYNC_EXTI0, DMAMUX_SYNC_EXTI1, DMAMUX_SYNC_EXTI2, DMAMUX_SYNC_EXTI3, DMAMUX_SYNC_EXTI4, DMAMUX_SYNC_EXTI5, DMAMUX_SYNC_EXTI6,
                           DMAMUX_SYNC_EXTI7, DMAMUX_SYNC_EXTI8, DMAMUX_SYNC_EXTI9, DMAMUX_SYNC_EXTI10, DMAMUX_SYNC_EXTI11, DMAMUX_SYNC_EXTI12, DMAMUX_SYNC_EXTI13,
                           DMAMUX_SYNC_EXTI14, DMAMUX_SYNC_EXTI15, DMAMUX_SYNC_EVT0_OUT, DMAMUX_SYNC_EVT1_OUT, DMAMUX_SYNC_EVT2_OUT, DMAMUX_SYNC_EVT3_OUT, DMAMUX_SYNC_EVT4_OUT,
                           DMAMUX_SYNC_EVT5_OUT, DMAMUX_SYNC_EVT6_OUT, DMAMUX_SYNC_EVT7_OUT, DMAMUX_SYNC_TIMER1_TRGO
                  sync_polarity: DMAMUX_SYNC_NO_EVENT, DMAMUX_SYNC_RISING, DMAMUX_SYNC_FALLING, DMAMUX_SYNC_RISING_FALLING
                  request_number: the number of DMA request that will be authorized after a sync event, from 1 to 32
    \param[out] none
    \retval     none
*/
void dmamux_synchronization_init(dmamux_multiplexer_channel_enum channelx, dmamux_sync_parameter_struct *init_struct)
{
    uint32_t cfg;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0037U), ERR_PARAM_INVALID);
    } else if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0037U), ERR_PARAM_POINTER);
    } else if(NOT_DMAMUX_SYNC_ID(init_struct->sync_id)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0037U), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_SYNC_POLARITY(init_struct->sync_polarity)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0037U), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_REQUEST_NUMBER(init_struct->request_number)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0037U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable synchronization mode and event generation for DMA request forward number configuration */
        DMAMUX_RM_CHXCFG(channelx) &= ~(DMAMUX_RM_CHXCFG_SYNCEN | DMAMUX_RM_CHXCFG_EVGEN | DMAMUX_RM_CHXCFG_SOIE);

        /* configure synchronization input identification, synchronization input polarity, number of DMA requests to forward */
        cfg = DMAMUX_RM_CHXCFG(channelx);
        cfg &= ~(DMAMUX_RM_CHXCFG_SYNCID | DMAMUX_RM_CHXCFG_NBR | DMAMUX_RM_CHXCFG_SYNCP);
        cfg |= (init_struct->sync_polarity | (init_struct->sync_id) | RM_CHXCFG_NBR(init_struct->request_number - 1U));
        DMAMUX_RM_CHXCFG(channelx) = cfg;
    }
}

/*!
    \brief      enable synchronization mode (API_ID(0x0038U))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[out] none
    \retval     none
*/
void dmamux_synchronization_enable(dmamux_multiplexer_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0038U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RM_CHXCFG(channelx) |= DMAMUX_RM_CHXCFG_SYNCEN;
    }
}

/*!
    \brief      disable synchronization mode (API_ID(0x0039U))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[out] none
    \retval     none
*/
void dmamux_synchronization_disable(dmamux_multiplexer_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0039U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RM_CHXCFG(channelx) &= (~DMAMUX_RM_CHXCFG_SYNCEN);
    }
}
/*!
    \brief      enable event generation (API_ID(0x003AU))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[out] none
    \retval     none
*/
void dmamux_event_generation_enable(dmamux_multiplexer_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RM_CHXCFG(channelx) |= DMAMUX_RM_CHXCFG_EVGEN;
    }
}

/*!
    \brief      disable event generation (API_ID(0x003BU))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[out] none
    \retval     none
*/
void dmamux_event_generation_disable(dmamux_multiplexer_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RM_CHXCFG(channelx) &= (~DMAMUX_RM_CHXCFG_EVGEN);
    }
}

/*!
    \brief      initialize the parameters of DMAMUX request generator structure with the default values (API_ID(0x003CU))
    \param[in]  init_struct: the initialization data needed to initialize DMAMUX request generator channel
    \param[out] none
    \retval     none
*/
void dmamux_gen_struct_para_init(dmamux_gen_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* set the DMAMUX request generator structure with the default values */
        init_struct->trigger_id        = DMAMUX_TRIGGER_EXTI0;
        init_struct->trigger_polarity  = DMAMUX_GEN_RISING;
        init_struct->request_number    = 1U;
    }
}

/*!
    \brief      initialize DMAMUX request generator channel (API_ID(0x003DU))
    \param[in]  channelx: specify which DMAMUX request generator channel is initialized
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[in]  init_struct: the data needed to initialize DMAMUX request generator channel
                  trigger_id: DMAMUX_TRIGGER_EXTI0, DMAMUX_TRIGGER_EXTI1, DMAMUX_TRIGGER_EXTI2, DMAMUX_TRIGGER_EXTI3, DMAMUX_TRIGGER_EXTI4, DMAMUX_TRIGGER_EXTI5,
                              DMAMUX_TRIGGER_EXTI6, DMAMUX_TRIGGER_EXTI7, DMAMUX_TRIGGER_EXTI8, DMAMUX_TRIGGER_EXTI9, DMAMUX_TRIGGER_EXTI10, DMAMUX_TRIGGER_EXTI11,
                              DMAMUX_TRIGGER_EXTI12, DMAMUX_TRIGGER_EXTI13, DMAMUX_TRIGGER_EXTI14, DMAMUX_TRIGGER_EXTI15, DMAMUX_TRIGGER_EVT0_OUT, DMAMUX_TRIGGER_EVT1_OUT,
                              DMAMUX_TRIGGER_EVT2_OUT, DMAMUX_TRIGGER_EVT3_OUT, DMAMUX_TRIGGER_EVT4_OUT, DMAMUX_TRIGGER_EVT5_OUT, DMAMUX_TRIGGER_EVT6_OUT, DMAMUX_TRIGGER_EVT7_OUT,
                              DMAMUX_TRIGGER_TIMER1_TRGO
                  trigger_polarity: DMAMUX_GEN_NO_EVENT, DMAMUX_GEN_RISING, DMAMUX_GEN_FALLING, DMAMUX_GEN_RISING_FALLING
                  request_number: the number of DMA request that will be generated after a signal event, from 1 to 32
    \param[out] none
    \retval     none
*/
void dmamux_request_generator_init(dmamux_generator_channel_enum channelx, dmamux_gen_parameter_struct *init_struct)
{
    uint32_t cfg;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_GENERATOR_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003DU), ERR_PARAM_INVALID);
    } else if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003DU), ERR_PARAM_POINTER);
    } else if(NOT_DMAMUX_TRIGGER_ID(init_struct->trigger_id)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003DU), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_TRIGGER_POLARITY(init_struct->trigger_polarity)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003DU), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_REQUEST_NUMBER(init_struct->request_number)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* disable DMAMUX request generator channel for DMA request generation number configuration */
        DMAMUX_RG_CHXCFG(channelx) &= ~(DMAMUX_RG_CHXCFG_RGEN | DMAMUX_RG_CHXCFG_TOIE);

        /* configure trigger input identification, trigger polarity, number of DMA requests to be generated */
        cfg = DMAMUX_RG_CHXCFG(channelx);
        cfg &= ~(DMAMUX_RG_CHXCFG_TID | DMAMUX_RG_CHXCFG_NBRG | DMAMUX_RG_CHXCFG_RGTP);
        cfg |= (RG_CHXCFG_NBRG(init_struct->request_number - 1U) | init_struct->trigger_id | init_struct->trigger_polarity);
        DMAMUX_RG_CHXCFG(channelx) = cfg;
    }
}

/*!
    \brief      enable DMAMUX request generator channel (API_ID(0x003EU))
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dmamux_request_generator_channel_enable(dmamux_generator_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_GENERATOR_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RG_CHXCFG(channelx) |= DMAMUX_RG_CHXCFG_RGEN;
    }
}

/*!
    \brief      disable DMAMUX request generator channel (API_ID(0x003FU))
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[out] none
    \retval     none
*/
void dmamux_request_generator_channel_disable(dmamux_generator_channel_enum channelx)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_GENERATOR_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x003FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RG_CHXCFG(channelx) &= (~DMAMUX_RG_CHXCFG_RGEN);
    }
}

/*!
    \brief      configure synchronization input polarity (API_ID(0x0040U))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[in]  polarity: synchronization input polarity
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_SYNC_NO_EVENT: no event detection
      \arg        DMAMUX_SYNC_RISING: rising edge
      \arg        DMAMUX_SYNC_FALLING: falling edge
      \arg        DMAMUX_SYNC_RISING_FALLING: rising and falling edges
    \param[out] none
    \retval     none
*/
void dmamux_synchronization_polarity_config(dmamux_multiplexer_channel_enum channelx, uint32_t polarity)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0040U), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_SYNC_POLARITY(polarity)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0040U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_SYNCP;
        DMAMUX_RM_CHXCFG(channelx) |= polarity;
    }
}

/*!
    \brief      configure number of DMA requests to forward (API_ID(0x0041U))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[in]  number: DMA requests number to forward
      \arg        1 - 32
    \param[out] none
    \retval     none
*/
void dmamux_request_forward_number_config(dmamux_multiplexer_channel_enum channelx, uint32_t number)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0041U), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_REQUEST_NUMBER(number)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0041U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_NBR;
        DMAMUX_RM_CHXCFG(channelx) |= ((number - 1U) << RM_CHXCFG_NBR_OFFSET);
    }
}

/*!
    \brief      configure synchronization input identification (API_ID(0x0042U))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[in]  id: synchronization input identification
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_SYNC_EXTI0      : synchronization input is EXTI0
      \arg        DMAMUX_SYNC_EXTI1      : synchronization input is EXTI1
      \arg        DMAMUX_SYNC_EXTI2      : synchronization input is EXTI2
      \arg        DMAMUX_SYNC_EXTI3      : synchronization input is EXTI3
      \arg        DMAMUX_SYNC_EXTI4      : synchronization input is EXTI4
      \arg        DMAMUX_SYNC_EXTI5      : synchronization input is EXTI5
      \arg        DMAMUX_SYNC_EXTI6      : synchronization input is EXTI6
      \arg        DMAMUX_SYNC_EXTI7      : synchronization input is EXTI7
      \arg        DMAMUX_SYNC_EXTI8      : synchronization input is EXTI8
      \arg        DMAMUX_SYNC_EXTI9      : synchronization input is EXTI9
      \arg        DMAMUX_SYNC_EXTI10     : synchronization input is EXTI10
      \arg        DMAMUX_SYNC_EXTI11     : synchronization input is EXTI11
      \arg        DMAMUX_SYNC_EXTI12     : synchronization input is EXTI12
      \arg        DMAMUX_SYNC_EXTI13     : synchronization input is EXTI13
      \arg        DMAMUX_SYNC_EXTI14     : synchronization input is EXTI14
      \arg        DMAMUX_SYNC_EXTI15     : synchronization input is EXTI15
      \arg        DMAMUX_SYNC_EVT0_OUT   : synchronization input is Evt0_out
      \arg        DMAMUX_SYNC_EVT1_OUT   : synchronization input is Evt1_out
      \arg        DMAMUX_SYNC_EVT2_OUT   : synchronization input is Evt2_out
      \arg        DMAMUX_SYNC_EVT3_OUT   : synchronization input is Evt3_out
      \arg        DMAMUX_SYNC_EVT4_OUT   : synchronization input is Evt4_out
      \arg        DMAMUX_SYNC_EVT5_OUT   : synchronization input is Evt5_out
      \arg        DMAMUX_SYNC_EVT6_OUT   : synchronization input is Evt6_out
      \arg        DMAMUX_SYNC_EVT7_OUT   : synchronization input is Evt7_out
      \arg        DMAMUX_SYNC_TIMER1_TRGO: synchronization input is TIMER1_TRGO
    \param[out] none
    \retval     none
*/
void dmamux_sync_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0042U), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_SYNC_ID(id)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0042U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_SYNCID;
        DMAMUX_RM_CHXCFG(channelx) |= id;
    }
}

/*!
    \brief      configure multiplexer input identification (API_ID(0x0043U))
    \param[in]  channelx: specify which DMAMUX request multiplexer channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_MUXCHx(x=0..31)
    \param[in]  id: input DMA request identification
                only one parameter can be selected which is shown as below:
      \arg        DMA_REQUEST_M2M: memory to memory transfer
      \arg        DMA_REQUEST_GENERATOR0: DMAMUX request generator 0
      \arg        DMA_REQUEST_GENERATOR1: MAMUX request generator 1
      \arg        DMA_REQUEST_GENERATOR2: MAMUX request generator 2
      \arg        DMA_REQUEST_GENERATOR3: MAMUX request generator 3
      \arg        DMA_REQUEST_GENERATOR4: MAMUX request generator 4
      \arg        DMA_REQUEST_GENERATOR5: MAMUX request generator 5
      \arg        DMA_REQUEST_GENERATOR6: MAMUX request generator 6
      \arg        DMA_REQUEST_GENERATOR7: MAMUX request generator 7
      \arg        DMA_REQUEST_DAC0: DMAMUX DAC0 request
      \arg        DMA_REQUEST_DAC1: DMAMUX DAC1 request
      \arg        DMA_REQUEST_TIMER5_UP0: DMAMUX TIMER5 UP0 request
      \arg        DMA_REQUEST_TIMER6_UP0: DMAMUX TIMER6 UP0 request
      \arg        DMA_REQUEST_SPI0_RX: DMAMUX SPI0 RX request
      \arg        DMA_REQUEST_SPI0_TX: DMAMUX SPI0 TX request
      \arg        DMA_REQUEST_SPI1_RX: DMAMUX SPI1 RX request
      \arg        DMA_REQUEST_SPI1_TX: DMAMUX SPI1 TX request
      \arg        DMA_REQUEST_SPI2_RX: DMAMUX SPI2 RX request
      \arg        DMA_REQUEST_SPI2_TX: DMAMUX SPI2 TX request
      \arg        DMA_REQUEST_SPI3_RX: DMAMUX SPI3 RX request
      \arg        DMA_REQUEST_SPI3_TX: DMAMUX SPI3 TX request
      \arg        DMA_REQUEST_SPI4_I2S_RX: DMAMUX SPI4 I2S RX request
      \arg        DMA_REQUEST_SPI4_I2S_TX: DMAMUX SPI4 I2S TX request
      \arg        DMA_REQUEST_SPI5_I2S_RX: DMAMUX SPI5 I2S RX request
      \arg        DMA_REQUEST_SPI5_I2S_TX: DMAMUX SPI5 I2S TX request
      \arg        DMA_REQUEST_I2C0_RX: DMAMUX I2C0 RX request
      \arg        DMA_REQUEST_I2C0_TX: DMAMUX I2C0 TX request
      \arg        DMA_REQUEST_I2C1_RX: DMAMUX I2C1 RX request
      \arg        DMA_REQUEST_I2C1_TX: DMAMUX I2C1 TX request
      \arg        DMA_REQUEST_SPI6_I2S_RX: DMAMUX SPI6 I2S RX request
      \arg        DMA_REQUEST_SPI6_I2S_TX: DMAMUX SPI6 I2S TX request
      \arg        DMA_REQUEST_SPI7_I2S_RX: DMAMUX SPI7 I2S RX request
      \arg        DMA_REQUEST_SPI7_I2S_TX: DMAMUX SPI7 I2S TX request
      \arg        DMA_REQUEST_LINFLEXD0_RX: DMAMUX LINFLEXD0 RX request
      \arg        DMA_REQUEST_LINFLEXD0_TX: DMAMUX LINFLEXD0 TX request
      \arg        DMA_REQUEST_LINFLEXD1_RX: DMAMUX LINFLEXD1 RX request
      \arg        DMA_REQUEST_LINFLEXD1_TX: DMAMUX LINFLEXD1 TX request
      \arg        DMA_REQUEST_LINFLEXD2_RX: DMAMUX LINFLEXD2 RX request
      \arg        DMA_REQUEST_LINFLEXD2_TX: DMAMUX LINFLEXD2 TX request
      \arg        DMA_REQUEST_LINFLEXD3_RX: DMAMUX LINFLEXD3 RX request
      \arg        DMA_REQUEST_LINFLEXD3_TX: DMAMUX LINFLEXD3 TX request
      \arg        DMA_REQUEST_LINFLEXD4_RX: DMAMUX LINFLEXD4 RX request
      \arg        DMA_REQUEST_LINFLEXD4_TX: DMAMUX LINFLEXD4 TX request
      \arg        DMA_REQUEST_LINFLEXD5_RX: DMAMUX LINFLEXD5 RX request
      \arg        DMA_REQUEST_LINFLEXD5_TX: DMAMUX LINFLEXD5 TX request
      \arg        DMA_REQUEST_LINFLEXD6_RX: DMAMUX LINFLEXD6 RX request
      \arg        DMA_REQUEST_LINFLEXD6_TX: DMAMUX LINFLEXD6 TX request
      \arg        DMA_REQUEST_LINFLEXD7_RX: DMAMUX LINFLEXD7 RX request
      \arg        DMA_REQUEST_LINFLEXD7_TX: DMAMUX LINFLEXD7 TX request
      \arg        DMA_REQUEST_LINFLEXD8_RX: DMAMUX LINFLEXD8 RX request
      \arg        DMA_REQUEST_LINFLEXD8_TX: DMAMUX LINFLEXD8 TX request
      \arg        DMA_REQUEST_LINFLEXD9_RX: DMAMUX LINFLEXD9 RX request
      \arg        DMA_REQUEST_LINFLEXD9_TX: DMAMUX LINFLEXD9 TX request
      \arg        DMA_REQUEST_LINFLEXD10_RX: DMAMUX LINFLEXD10 RX request
      \arg        DMA_REQUEST_LINFLEXD10_TX: DMAMUX LINFLEXD10 TX request
      \arg        DMA_REQUEST_LINFLEXD11_RX: DMAMUX LINFLEXD11 RX request
      \arg        DMA_REQUEST_LINFLEXD11_TX: DMAMUX LINFLEXD11 TX request
      \arg        DMA_REQUEST_TIMER0_CH0: DMAMUX TIMER0 CH0 request
      \arg        DMA_REQUEST_TIMER0_CH1: DMAMUX TIMER0 CH1 request
      \arg        DMA_REQUEST_TIMER0_CH2: DMAMUX TIMER0 CH2 request
      \arg        DMA_REQUEST_TIMER0_CH3: DMAMUX TIMER0 CH3 request
      \arg        DMA_REQUEST_TIMER0_CH0N: DMAMUX TIMER0 CH0N request
      \arg        DMA_REQUEST_TIMER0_CH1N: DMAMUX TIMER0 CH1N request
      \arg        DMA_REQUEST_TIMER0_CH2N: DMAMUX TIMER0 CH2N request
      \arg        DMA_REQUEST_TIMER0_CH3N: DMAMUX TIMER0 CH3N request
      \arg        DMA_REQUEST_TIMER0_UP: DMAMUX TIMER0 UP request
      \arg        DMA_REQUEST_TIMER0_TRG: DMAMUX TIMER0 TRG request
      \arg        DMA_REQUEST_TIMER0_CMT: DMAMUX TIMER0 CMT request
      \arg        DMA_REQUEST_TIMER7_CH0: DMAMUX TIMER7 CH0 request
      \arg        DMA_REQUEST_TIMER7_CH1: DMAMUX TIMER7 CH1 request
      \arg        DMA_REQUEST_TIMER7_CH2: DMAMUX TIMER7 CH2 request
      \arg        DMA_REQUEST_TIMER7_CH3: DMAMUX TIMER7 CH3 request
      \arg        DMA_REQUEST_TIMER7_CH0N: DMAMUX TIMER7 CH0N request
      \arg        DMA_REQUEST_TIMER7_CH1N: DMAMUX TIMER7 CH1N request
      \arg        DMA_REQUEST_TIMER7_CH2N: DMAMUX TIMER7 CH2N request
      \arg        DMA_REQUEST_TIMER7_CH3N: DMAMUX TIMER7 CH3N request
      \arg        DMA_REQUEST_TIMER7_TRG: DMAMUX TIMER7 TRG request
      \arg        DMA_REQUEST_TIMER7_UP: DMAMUX TIMER7 UP request
      \arg        DMA_REQUEST_TIMER7_CMT: DMAMUX TIMER7 CMT request
      \arg        DMA_REQUEST_TIMER19_CH0: DMAMUX TIMER19 CH0 request
      \arg        DMA_REQUEST_TIMER19_CH1: DMAMUX TIMER19 CH1 request
      \arg        DMA_REQUEST_TIMER19_CH2: DMAMUX TIMER19 CH2 request
      \arg        DMA_REQUEST_TIMER19_CH3: DMAMUX TIMER19 CH3 request
      \arg        DMA_REQUEST_TIMER19_CH0N: DMAMUX TIMER19 CH0N request
      \arg        DMA_REQUEST_TIMER19_CH1N: DMAMUX TIMER19 CH1N request
      \arg        DMA_REQUEST_TIMER19_CH2N: DMAMUX TIMER19 CH2N request
      \arg        DMA_REQUEST_TIMER19_CH3N: DMAMUX TIMER19 CH3N request
      \arg        DMA_REQUEST_TIMER19_UP: DMAMUX TIMER19 UP request
      \arg        DMA_REQUEST_TIMER19_TRG: DMAMUX TIMER19 TRG request
      \arg        DMA_REQUEST_TIMER19_CMT: DMAMUX TIMER19 CMT request
      \arg        DMA_REQUEST_TIMER20_CH0: DMAMUX TIMER20 CH0 request
      \arg        DMA_REQUEST_TIMER20_CH1: DMAMUX TIMER20 CH1 request
      \arg        DMA_REQUEST_TIMER20_CH2: DMAMUX TIMER20 CH2 request
      \arg        DMA_REQUEST_TIMER20_CH3: DMAMUX TIMER20 CH3 request
      \arg        DMA_REQUEST_TIMER20_CH0N: DMAMUX TIMER20 CH0N request
      \arg        DMA_REQUEST_TIMER20_CH1N: DMAMUX TIMER20 CH1N request
      \arg        DMA_REQUEST_TIMER20_CH2N: DMAMUX TIMER20 CH2N request
      \arg        DMA_REQUEST_TIMER20_CH3N: DMAMUX TIMER20 CH3N request
      \arg        DMA_REQUEST_TIMER20_UP: DMAMUX TIMER20 UP request
      \arg        DMA_REQUEST_TIMER20_TRG: DMAMUX TIMER20 TRG request
      \arg        DMA_REQUEST_TIMER20_CMT: DMAMUX TIMER20 CMT request
      \arg        DMA_REQUEST_TIMER60_CH0: DMAMUX TIMER60 CH0 request
      \arg        DMA_REQUEST_TIMER60_CH1: DMAMUX TIMER60 CH1 request
      \arg        DMA_REQUEST_TIMER60_CH2: DMAMUX TIMER60 CH2 request
      \arg        DMA_REQUEST_TIMER60_CH3: DMAMUX TIMER60 CH3 request
      \arg        DMA_REQUEST_TIMER60_CH0N: DMAMUX TIMER60 CH0N request
      \arg        DMA_REQUEST_TIMER60_CH1N: DMAMUX TIMER60 CH1N request
      \arg        DMA_REQUEST_TIMER60_CH2N: DMAMUX TIMER60 CH2N request
      \arg        DMA_REQUEST_TIMER60_CH3N: DMAMUX TIMER60 CH3N request
      \arg        DMA_REQUEST_TIMER60_UP: DMAMUX TIMER60 UP request
      \arg        DMA_REQUEST_TIMER60_TRG: DMAMUX TIMER60 TRG request
      \arg        DMA_REQUEST_TIMER60_CMT: DMAMUX TIMER60 CMT request
      \arg        DMA_REQUEST_TIMER61_CH0: DMAMUX TIMER61 CH0 request
      \arg        DMA_REQUEST_TIMER61_CH1: DMAMUX TIMER61 CH1 request
      \arg        DMA_REQUEST_TIMER61_CH2: DMAMUX TIMER61 CH2 request
      \arg        DMA_REQUEST_TIMER61_CH3: DMAMUX TIMER61 CH3 request
      \arg        DMA_REQUEST_TIMER61_CH0N: DMAMUX TIMER61 CH0N request
      \arg        DMA_REQUEST_TIMER61_CH1N: DMAMUX TIMER61 CH1N request
      \arg        DMA_REQUEST_TIMER61_CH2N: DMAMUX TIMER61 CH2N request
      \arg        DMA_REQUEST_TIMER61_CH3N: DMAMUX TIMER61 CH3N request
      \arg        DMA_REQUEST_TIMER61_UP: DMAMUX TIMER61 UP request
      \arg        DMA_REQUEST_TIMER61_TRG: DMAMUX TIMER61 TRG request
      \arg        DMA_REQUEST_TIMER61_CMT: DMAMUX TIMER61 CMT request
      \arg        DMA_REQUEST_TIMER62_CH0: DMAMUX TIMER62 CH0 request
      \arg        DMA_REQUEST_TIMER62_CH1: DMAMUX TIMER62 CH1 request
      \arg        DMA_REQUEST_TIMER62_CH2: DMAMUX TIMER62 CH2 request
      \arg        DMA_REQUEST_TIMER62_CH3: DMAMUX TIMER62 CH3 request
      \arg        DMA_REQUEST_TIMER62_CH0N: DMAMUX TIMER62 CH0N request
      \arg        DMA_REQUEST_TIMER62_CH1N: DMAMUX TIMER62 CH1N request
      \arg        DMA_REQUEST_TIMER62_CH2N: DMAMUX TIMER62 CH2N request
      \arg        DMA_REQUEST_TIMER62_CH3N: DMAMUX TIMER62 CH3N request
      \arg        DMA_REQUEST_TIMER62_UP: DMAMUX TIMER62 UP request
      \arg        DMA_REQUEST_TIMER62_TRG: DMAMUX TIMER62 TRG request
      \arg        DMA_REQUEST_TIMER62_CMT: DMAMUX TIMER62 CMT request
      \arg        DMA_REQUEST_TIMER63_CH0: DMAMUX TIMER63 CH0 request
      \arg        DMA_REQUEST_TIMER63_CH1: DMAMUX TIMER63 CH1 request
      \arg        DMA_REQUEST_TIMER63_CH2: DMAMUX TIMER63 CH2 request
      \arg        DMA_REQUEST_TIMER63_CH3: DMAMUX TIMER63 CH3 request
      \arg        DMA_REQUEST_TIMER63_CH0N: DMAMUX TIMER63 CH0N request
      \arg        DMA_REQUEST_TIMER63_CH1N: DMAMUX TIMER63 CH1N request
      \arg        DMA_REQUEST_TIMER63_CH2N: DMAMUX TIMER63 CH2N request
      \arg        DMA_REQUEST_TIMER63_CH3N: DMAMUX TIMER63 CH3N request
      \arg        DMA_REQUEST_TIMER63_UP: DMAMUX TIMER63 UP request
      \arg        DMA_REQUEST_TIMER63_TRG: DMAMUX TIMER63 TRG request
      \arg        DMA_REQUEST_TIMER63_CMT: DMAMUX TIMER63 CMT request
      \arg        DMA_REQUEST_TIMER1_CH0: DMAMUX TIMER1 CH0 request
      \arg        DMA_REQUEST_TIMER1_CH1: DMAMUX TIMER1 CH1 request
      \arg        DMA_REQUEST_TIMER1_CH2: DMAMUX TIMER1 CH2 request
      \arg        DMA_REQUEST_TIMER1_CH3: DMAMUX TIMER1 CH3 request
      \arg        DMA_REQUEST_TIMER1_UP: DMAMUX TIMER1 UP request
      \arg        DMA_REQUEST_TIMER1_TRG: DMAMUX TIMER1 TRG request
      \arg        DMA_REQUEST_TIMER2_CH0: DMAMUX TIMER2 CH0 request
      \arg        DMA_REQUEST_TIMER2_CH1: DMAMUX TIMER2 CH1 request
      \arg        DMA_REQUEST_TIMER2_CH2: DMAMUX TIMER2 CH2 request
      \arg        DMA_REQUEST_TIMER2_CH3: DMAMUX TIMER2 CH3 request
      \arg        DMA_REQUEST_TIMER2_UP: DMAMUX TIMER2 UP request
      \arg        DMA_REQUEST_TIMER2_TRG: DMAMUX TIMER2 TRG request
      \arg        DMA_REQUEST_QSPI: DMAMUX QSPI request
      \arg        DMA_REQUEST_MFCOM0: DMAMUX MFCOM0 request
      \arg        DMA_REQUEST_MFCOM1: DMAMUX MFCOM1 request
      \arg        DMA_REQUEST_MFCOM2: DMAMUX MFCOM2 request
      \arg        DMA_REQUEST_MFCOM3: DMAMUX MFCOM3 request
      \arg        DMA_REQUEST_DTM_CAN0_RX0: DMAMUX DTM_CAN0_RX0 request
      \arg        DMA_REQUEST_DTM_CAN0_RX1: DMAMUX DTM_CAN0_RX1 request
      \arg        DMA_REQUEST_DTM_CAN0_TX: DMAMUX DTM_CAN0_TX request
      \arg        DMA_REQUEST_DTM_CAN0_TXE: DMAMUX DTM_CAN0_TXE request
      \arg        DMA_REQUEST_DTM_CAN1_RX0: DMAMUX DTM_CAN1_RX0 request
      \arg        DMA_REQUEST_DTM_CAN1_RX1: DMAMUX DTM_CAN1_RX1 request
      \arg        DMA_REQUEST_DTM_CAN1_TX: DMAMUX DTM_CAN1_TX request
      \arg        DMA_REQUEST_DTM_CAN1_TXE: DMAMUX DTM_CAN1_TXE request
      \arg        DMA_REQUEST_ADC0ROUTINE: DMAMUX ADC0ROUTINE request
      \arg        DMA_REQUEST_ADC0INSERTED0: DMAMUX ADC0INSERTED0 request
      \arg        DMA_REQUEST_ADC0INSERTED1: DMAMUX ADC0INSERTED1 request
      \arg        DMA_REQUEST_ADC0INSERTED2: DMAMUX ADC0INSERTED2 request
      \arg        DMA_REQUEST_ADC0INSERTED3: DMAMUX ADC0INSERTED3 request
      \arg        DMA_REQUEST_ADC0INSERTED4: DMAMUX ADC0INSERTED4 request
      \arg        DMA_REQUEST_ADC0INSERTED5: DMAMUX ADC0INSERTED5 request
      \arg        DMA_REQUEST_ADC1ROUTINE: DMAMUX ADC1ROUTINE request
      \arg        DMA_REQUEST_ADC1INSERTED0: DMAMUX ADC1INSERTED0 request
      \arg        DMA_REQUEST_ADC1INSERTED1: DMAMUX ADC1INSERTED1 request
      \arg        DMA_REQUEST_ADC1INSERTED2: DMAMUX ADC1INSERTED2 request
      \arg        DMA_REQUEST_ADC1INSERTED3: DMAMUX ADC1INSERTED3 request
      \arg        DMA_REQUEST_ADC1INSERTED4: DMAMUX ADC1INSERTED4 request
      \arg        DMA_REQUEST_ADC1INSERTED5: DMAMUX ADC1INSERTED5 request
      \arg        DMA_REQUEST_ADC2ROUTINE: DMAMUX ADC2ROUTINE request
      \arg        DMA_REQUEST_ADC2INSERTED0: DMAMUX ADC2INSERTED0 request
      \arg        DMA_REQUEST_ADC2INSERTED1: DMAMUX ADC2INSERTED1 request
      \arg        DMA_REQUEST_ADC2INSERTED2: DMAMUX ADC2INSERTED2 request
      \arg        DMA_REQUEST_ADC2INSERTED3: DMAMUX ADC2INSERTED3 request
      \arg        DMA_REQUEST_ADC2INSERTED4: DMAMUX ADC2INSERTED4 request
      \arg        DMA_REQUEST_ADC2INSERTED5: DMAMUX ADC2INSERTED5 request
      \arg        DMA_REQUEST_TIMER5_UP1: DMAMUX TIMER5 UP1 request
      \arg        DMA_REQUEST_TIMER5_UP2: DMAMUX TIMER5 UP2 request
      \arg        DMA_REQUEST_TIMER5_UP3: DMAMUX TIMER5 UP3 request
      \arg        DMA_REQUEST_TIMER6_UP1: DMAMUX TIMER6 UP1 request
      \arg        DMA_REQUEST_TIMER6_UP2: DMAMUX TIMER6 UP2 request
      \arg        DMA_REQUEST_TIMER6_UP3: DMAMUX TIMER6 UP3 request
      \arg        DMA_REQUEST_DTM_CAN2_RX0: DMAMUX DTM_CAN2_RX0 request
      \arg        DMA_REQUEST_DTM_CAN2_RX1: DMAMUX DTM_CAN2_RX1 request
      \arg        DMA_REQUEST_DTM_CAN2_TX: DMAMUX DTM_CAN2_TX request
      \arg        DMA_REQUEST_DTM_CAN2_TXE: DMAMUX DTM_CAN2_TXE request
      \arg        DMA_REQUEST_DTM_CAN3_RX0: DMAMUX DTM_CAN3_RX0 request
      \arg        DMA_REQUEST_DTM_CAN3_RX1: DMAMUX DTM_CAN3_RX1 request
      \arg        DMA_REQUEST_DTM_CAN3_TX: DMAMUX DTM_CAN3_TX request
      \arg        DMA_REQUEST_DTM_CAN3_TXE: DMAMUX DTM_CAN3_TXE request
      \arg        DMA_REQUEST_DTM_CAN4_RX0: DMAMUX DTM_CAN4_RX0 request
      \arg        DMA_REQUEST_DTM_CAN4_RX1: DMAMUX DTM_CAN4_RX1 request
      \arg        DMA_REQUEST_DTM_CAN4_TX: DMAMUX DTM_CAN4_TX request
      \arg        DMA_REQUEST_DTM_CAN4_TXE: DMAMUX DTM_CAN4_TXE request
      \arg        DMA_REQUEST_DTM_CAN5_RX0: DMAMUX DTM_CAN5_RX0 request
      \arg        DMA_REQUEST_DTM_CAN5_RX1: DMAMUX DTM_CAN5_RX1 request
      \arg        DMA_REQUEST_DTM_CAN5_TX: DMAMUX DTM_CAN5_TX request
      \arg        DMA_REQUEST_DTM_CAN5_TXE: DMAMUX DTM_CAN5_TXE request
      \arg        DMA_REQUEST_DTM_CAN6_RX0: DMAMUX DTM_CAN6_RX0 request
      \arg        DMA_REQUEST_DTM_CAN6_RX1: DMAMUX DTM_CAN6_RX1 request
      \arg        DMA_REQUEST_DTM_CAN6_TX: DMAMUX DTM_CAN6_TX request
      \arg        DMA_REQUEST_DTM_CAN6_TXE: DMAMUX DTM_CAN6_TXE request
      \arg        DMA_REQUEST_DTM_CAN7_RX0: DMAMUX DTM_CAN7_RX0 request
      \arg        DMA_REQUEST_DTM_CAN7_RX1: DMAMUX DTM_CAN7_RX1 request
      \arg        DMA_REQUEST_DTM_CAN7_TX: DMAMUX DTM_CAN7_TX request
      \arg        DMA_REQUEST_DTM_CAN7_TXE: DMAMUX DTM_CAN7_TXE request
    \param[out] none
    \retval     none
*/
void dmamux_request_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_MULTIPLEXER_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0043U), ERR_PARAM_INVALID);
    } else if(NOT_DMA_REQUEST(id)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0043U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RM_CHXCFG(channelx) &= ~DMAMUX_RM_CHXCFG_MUXID;
        DMAMUX_RM_CHXCFG(channelx) |= id;
    }
}

/*!
    \brief      configure trigger input polarity (API_ID(0x0044U))
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[in]  polarity: trigger input polarity
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GEN_NO_EVENT: no event detection
      \arg        DMAMUX_GEN_RISING: rising edge
      \arg        DMAMUX_GEN_FALLING: falling edge
      \arg        DMAMUX_GEN_RISING_FALLING: rising and falling edges
    \param[out] none
    \retval     none
*/
void dmamux_trigger_polarity_config(dmamux_generator_channel_enum channelx, uint32_t polarity)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_GENERATOR_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0044U), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_TRIGGER_POLARITY(polarity)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0044U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RG_CHXCFG(channelx) &= ~DMAMUX_RG_CHXCFG_RGTP;
        DMAMUX_RG_CHXCFG(channelx) |= polarity;
    }
}

/*!
    \brief      configure number of DMA requests to be generated (API_ID(0x0045U))
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[in]  number: DMA requests number to be generated
      \arg        1 - 32
    \param[out] none
    \retval     none
*/
void dmamux_request_generate_number_config(dmamux_generator_channel_enum channelx, uint32_t number)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_GENERATOR_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0045U), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_REQUEST_NUMBER(number)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0045U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RG_CHXCFG(channelx) &= ~DMAMUX_RG_CHXCFG_NBRG;
        DMAMUX_RG_CHXCFG(channelx) |= ((number - 1U) << RG_CHXCFG_NBRG_OFFSET);
    }
}

/*!
    \brief      configure trigger input identification (API_ID(0x0046U))
    \param[in]  channelx: specify which DMAMUX request generator channel is configured
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_GENCHx(x=0..7)
    \param[in]  id: trigger input identification
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_TRIGGER_EXTI0      : trigger input is EXTI0
      \arg        DMAMUX_TRIGGER_EXTI1      : trigger input is EXTI1
      \arg        DMAMUX_TRIGGER_EXTI2      : trigger input is EXTI2
      \arg        DMAMUX_TRIGGER_EXTI3      : trigger input is EXTI3
      \arg        DMAMUX_TRIGGER_EXTI4      : trigger input is EXTI4
      \arg        DMAMUX_TRIGGER_EXTI5      : trigger input is EXTI5
      \arg        DMAMUX_TRIGGER_EXTI6      : trigger input is EXTI6
      \arg        DMAMUX_TRIGGER_EXTI7      : trigger input is EXTI7
      \arg        DMAMUX_TRIGGER_EXTI8      : trigger input is EXTI8
      \arg        DMAMUX_TRIGGER_EXTI9      : trigger input is EXTI9
      \arg        DMAMUX_TRIGGER_EXTI10     : trigger input is EXTI10
      \arg        DMAMUX_TRIGGER_EXTI11     : trigger input is EXTI11
      \arg        DMAMUX_TRIGGER_EXTI12     : trigger input is EXTI12
      \arg        DMAMUX_TRIGGER_EXTI13     : trigger input is EXTI13
      \arg        DMAMUX_TRIGGER_EXTI14     : trigger input is EXTI14
      \arg        DMAMUX_TRIGGER_EXTI15     : trigger input is EXTI15
      \arg        DMAMUX_TRIGGER_EVT0_OUT   : trigger input is Evt0_out
      \arg        DMAMUX_TRIGGER_EVT1_OUT   : trigger input is Evt1_out
      \arg        DMAMUX_TRIGGER_EVT2_OUT   : trigger input is Evt2_out
      \arg        DMAMUX_TRIGGER_EVT3_OUT   : trigger input is Evt3_out
      \arg        DMAMUX_TRIGGER_EVT4_OUT   : trigger input is Evt4_out
      \arg        DMAMUX_TRIGGER_EVT5_OUT   : trigger input is Evt5_out
      \arg        DMAMUX_TRIGGER_EVT6_OUT   : trigger input is Evt6_out
      \arg        DMAMUX_TRIGGER_EVT7_OUT   : trigger input is Evt7_out
                  DMAMUX_TRIGGER_TIMER1_TRGO: trigger input is TIMER1 TRGO
    \param[out] none
    \retval     none
*/
void dmamux_trigger_id_config(dmamux_generator_channel_enum channelx, uint32_t id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_GENERATOR_CHANNEL(channelx)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0046U), ERR_PARAM_INVALID);
    } else if(NOT_DMAMUX_TRIGGER_ID(id)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0046U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_RG_CHXCFG(channelx) &= ~DMAMUX_RG_CHXCFG_TID;
        DMAMUX_RG_CHXCFG(channelx) |= id;
    }
}

/*!
    \brief      get DMAMUX flag (API_ID(0x0047U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_FLAG_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH16_SO: DMAMUX request multiplexer channel 16 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH17_SO: DMAMUX request multiplexer channel 17 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH18_SO: DMAMUX request multiplexer channel 18 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH19_SO: DMAMUX request multiplexer channel 19 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH20_SO: DMAMUX request multiplexer channel 20 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH21_SO: DMAMUX request multiplexer channel 21 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH22_SO: DMAMUX request multiplexer channel 22 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH23_SO: DMAMUX request multiplexer channel 23 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH24_SO: DMAMUX request multiplexer channel 24 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH25_SO: DMAMUX request multiplexer channel 25 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH26_SO: DMAMUX request multiplexer channel 26 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH27_SO: DMAMUX request multiplexer channel 27 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH28_SO: DMAMUX request multiplexer channel 28 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH29_SO: DMAMUX request multiplexer channel 29 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH30_SO: DMAMUX request multiplexer channel 30 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH31_SO: DMAMUX request multiplexer channel 31 synchronization overrun flag
      \arg        DMAMUX_FLAG_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dmamux_flag_get(dmamux_flag_enum flag)
{
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_FLAG(flag)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0047U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (DMAMUX_REG_VAL(flag) & BIT(DMAMUX_BIT_POS(flag)))) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear DMAMUX flag (API_ID(0x0048U))
    \param[in]  flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_FLAG_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH16_SO: DMAMUX request multiplexer channel 16 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH17_SO: DMAMUX request multiplexer channel 17 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH18_SO: DMAMUX request multiplexer channel 18 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH19_SO: DMAMUX request multiplexer channel 19 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH20_SO: DMAMUX request multiplexer channel 20 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH21_SO: DMAMUX request multiplexer channel 21 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH22_SO: DMAMUX request multiplexer channel 22 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH23_SO: DMAMUX request multiplexer channel 23 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH24_SO: DMAMUX request multiplexer channel 24 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH25_SO: DMAMUX request multiplexer channel 25 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH26_SO: DMAMUX request multiplexer channel 26 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH27_SO: DMAMUX request multiplexer channel 27 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH28_SO: DMAMUX request multiplexer channel 28 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH29_SO: DMAMUX request multiplexer channel 29 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH30_SO: DMAMUX request multiplexer channel 30 synchronization overrun flag
      \arg        DMAMUX_FLAG_MUXCH31_SO: DMAMUX request multiplexer channel 31 synchronization overrun flag
      \arg        DMAMUX_FLAG_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun flag
      \arg        DMAMUX_FLAG_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun flag
    \param[out] none
    \retval     none
*/
void dmamux_flag_clear(dmamux_flag_enum flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_FLAG(flag)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0048U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_REG_VAL3(flag) = BIT(DMAMUX_BIT_POS(flag));
    }
}

/*!
    \brief      enable DMAMUX interrupt (API_ID(0x0049U))
    \param[in]  interrupt: specify which interrupt to enable
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_INT_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH16_SO: DMAMUX request multiplexer channel 16 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH17_SO: DMAMUX request multiplexer channel 17 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH18_SO: DMAMUX request multiplexer channel 18 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH19_SO: DMAMUX request multiplexer channel 19 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH20_SO: DMAMUX request multiplexer channel 20 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH21_SO: DMAMUX request multiplexer channel 21 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH22_SO: DMAMUX request multiplexer channel 22 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH23_SO: DMAMUX request multiplexer channel 23 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH24_SO: DMAMUX request multiplexer channel 24 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH25_SO: DMAMUX request multiplexer channel 25 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH26_SO: DMAMUX request multiplexer channel 26 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH27_SO: DMAMUX request multiplexer channel 27 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH28_SO: DMAMUX request multiplexer channel 28 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH29_SO: DMAMUX request multiplexer channel 29 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH30_SO: DMAMUX request multiplexer channel 30 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH31_SO: DMAMUX request multiplexer channel 31 synchronization overrun interrupt
      \arg        DMAMUX_INT_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun interrupt
    \param[out] none
    \retval     none
*/
void dmamux_interrupt_enable(dmamux_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_INTERRUPT(interrupt)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x0049U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_REG_VAL(interrupt) |= BIT(DMAMUX_BIT_POS(interrupt));
    }
}

/*!
    \brief      disable DMAMUX interrupt (API_ID(0x004AU))
    \param[in]  interrupt: specify which interrupt to disable
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_INT_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH16_SO: DMAMUX request multiplexer channel 16 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH17_SO: DMAMUX request multiplexer channel 17 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH18_SO: DMAMUX request multiplexer channel 18 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH19_SO: DMAMUX request multiplexer channel 19 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH20_SO: DMAMUX request multiplexer channel 20 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH21_SO: DMAMUX request multiplexer channel 21 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH22_SO: DMAMUX request multiplexer channel 22 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH23_SO: DMAMUX request multiplexer channel 23 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH24_SO: DMAMUX request multiplexer channel 24 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH25_SO: DMAMUX request multiplexer channel 25 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH26_SO: DMAMUX request multiplexer channel 26 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH27_SO: DMAMUX request multiplexer channel 27 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH28_SO: DMAMUX request multiplexer channel 28 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH29_SO: DMAMUX request multiplexer channel 29 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH30_SO: DMAMUX request multiplexer channel 30 synchronization overrun interrupt
      \arg        DMAMUX_INT_MUXCH31_SO: DMAMUX request multiplexer channel 31 synchronization overrun interrupt
      \arg        DMAMUX_INT_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun interrupt
      \arg        DMAMUX_INT_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun interrupt
    \param[out] none
    \retval     none
*/
void dmamux_interrupt_disable(dmamux_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_INTERRUPT(interrupt)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x004AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_REG_VAL(interrupt) &= ~BIT(DMAMUX_BIT_POS(interrupt));
    }
}

/*!
    \brief      get DMAMUX interrupt flag (API_ID(0x004BU))
    \param[in]  int_flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_INT_FLAG_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH16_SO: DMAMUX request multiplexer channel 16 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH17_SO: DMAMUX request multiplexer channel 17 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH18_SO: DMAMUX request multiplexer channel 18 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH19_SO: DMAMUX request multiplexer channel 19 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH20_SO: DMAMUX request multiplexer channel 20 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH21_SO: DMAMUX request multiplexer channel 21 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH22_SO: DMAMUX request multiplexer channel 22 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH23_SO: DMAMUX request multiplexer channel 23 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH24_SO: DMAMUX request multiplexer channel 24 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH25_SO: DMAMUX request multiplexer channel 25 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH26_SO: DMAMUX request multiplexer channel 26 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH27_SO: DMAMUX request multiplexer channel 27 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH28_SO: DMAMUX request multiplexer channel 28 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH29_SO: DMAMUX request multiplexer channel 29 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH30_SO: DMAMUX request multiplexer channel 30 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH31_SO: DMAMUX request multiplexer channel 31 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus dmamux_interrupt_flag_get(dmamux_interrupt_flag_enum int_flag)
{
    FlagStatus reval = RESET;
    uint32_t intenable, flagstatus;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_INTERRUPT_FLAG(int_flag)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x004BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get the interrupt enable bit status */
        intenable = (DMAMUX_REG_VAL2(int_flag) & BIT(DMAMUX_BIT_POS2(int_flag)));
        /* get the corresponding flag bit status */
        flagstatus = (DMAMUX_REG_VAL(int_flag) & BIT(DMAMUX_BIT_POS(int_flag)));

        if((0U != flagstatus) && (0U != intenable)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear DMAMUX interrupt flag (API_ID(0x004CU))
    \param[in]  int_flag: flag type
                only one parameter can be selected which is shown as below:
      \arg        DMAMUX_INT_FLAG_MUXCH0_SO: DMAMUX request multiplexer channel 0 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH1_SO: DMAMUX request multiplexer channel 1 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH2_SO: DMAMUX request multiplexer channel 2 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH3_SO: DMAMUX request multiplexer channel 3 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH4_SO: DMAMUX request multiplexer channel 4 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH5_SO: DMAMUX request multiplexer channel 5 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH6_SO: DMAMUX request multiplexer channel 6 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH7_SO: DMAMUX request multiplexer channel 7 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH8_SO: DMAMUX request multiplexer channel 8 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH9_SO: DMAMUX request multiplexer channel 9 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH10_SO: DMAMUX request multiplexer channel 10 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH11_SO: DMAMUX request multiplexer channel 11 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH12_SO: DMAMUX request multiplexer channel 12 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH13_SO: DMAMUX request multiplexer channel 13 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH14_SO: DMAMUX request multiplexer channel 14 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH15_SO: DMAMUX request multiplexer channel 15 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH16_SO: DMAMUX request multiplexer channel 16 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH17_SO: DMAMUX request multiplexer channel 17 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH18_SO: DMAMUX request multiplexer channel 18 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH19_SO: DMAMUX request multiplexer channel 19 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH20_SO: DMAMUX request multiplexer channel 20 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH21_SO: DMAMUX request multiplexer channel 21 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH22_SO: DMAMUX request multiplexer channel 22 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH23_SO: DMAMUX request multiplexer channel 23 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH24_SO: DMAMUX request multiplexer channel 24 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH25_SO: DMAMUX request multiplexer channel 25 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH26_SO: DMAMUX request multiplexer channel 26 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH27_SO: DMAMUX request multiplexer channel 27 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH28_SO: DMAMUX request multiplexer channel 28 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH29_SO: DMAMUX request multiplexer channel 29 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH30_SO: DMAMUX request multiplexer channel 30 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_MUXCH31_SO: DMAMUX request multiplexer channel 31 synchronization overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH0_TO: DMAMUX request generator channel 0 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH1_TO: DMAMUX request generator channel 1 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH2_TO: DMAMUX request generator channel 2 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH3_TO: DMAMUX request generator channel 3 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH4_TO: DMAMUX request generator channel 4 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH5_TO: DMAMUX request generator channel 5 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH6_TO: DMAMUX request generator channel 6 trigger overrun interrupt flag
      \arg        DMAMUX_INT_FLAG_GENCH7_TO: DMAMUX request generator channel 7 trigger overrun interrupt flag
    \param[out] none
    \retval     none
*/
void dmamux_interrupt_flag_clear(dmamux_interrupt_flag_enum int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMAMUX_INTERRUPT_FLAG(int_flag)) {
        fw_debug_report_err(DMA_DMAMUX_MODULE_ID, API_ID(0x004CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        DMAMUX_REG_VAL3(int_flag) = BIT(DMAMUX_BIT_POS(int_flag));
    }
}
