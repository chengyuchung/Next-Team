/*!
    \file    gd32a7xx_enet.c
    \brief   ENET driver

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

#include "gd32a7xx_enet.h"

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)

#define ENET_BUFFER_LENGTH                          (128U)
#define MTL_TX_FIFO_SIZE                            ENET_TXQ_SIZE_4096BYTES
#define MTL_RX_FIFO_SIZE                            ENET_RXQ_SIZE_4096BYTES
#define GCL_GATE_CONTROL_OFFSET                     (24U)
#define MMC_INTERRUPT_MASK_VALUE                    (0xFFFFFFFU)
#define MMC_IPC_INTERRUPT_MASK_VALUE                (0x3FFF3FFFU)
#define MAC_ADDR_HIGH_MASK                          (0xFFFF0000U)
#define EIPG_BIT_TIMES_STEP                         (8U)
#define EIPG_BIT_TIMES_START_VAL                    (104U)
#define EIPG_BIT_TIMES_POSITION                     (3U)
#define WRITE_BACK_DELAY                            (0xFFU)

#if defined   (__CC_ARM)                                    /*!< ARM compiler */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x24048000"))) enet_descriptors_struct  txdesc_tab[ENET_TXBUF_NUM]                  ;  /*!< ENET TxDMA descriptor */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x24048078"))) enet_tbs_enhanced_descriptors_struct  tbs_txdesc_tab[ENET_TXBUF_NUM] ;  /*!< ENET TxDMA enhanced descriptor */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x24048140"))) enet_descriptors_struct  rxdesc_tab[ENET_RXBUF_NUM]                  ;  /*!< ENET RxDMA descriptor */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x240481B8"))) uint8_t rx_buff[ENET_RXBUF_NUM][ENET_RXBUF_SIZE]                     ;  /*!< ENET receive buffer */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x24049F90"))) uint8_t tx_buff[ENET_TXBUF_NUM][ENET_TXBUF_SIZE]                     ;  /*!< ENET transmit buffer */

 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404BD68"))) enet_descriptors_struct  txdesc_tab1[ENET_TXBUF_NUM]                 ;  /*!< ENET TxDMA descriptor */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404BDE0"))) enet_tbs_enhanced_descriptors_struct  tbs_txdesc_tab1[ENET_TXBUF_NUM];  /*!< ENET TxDMA enhanced descriptor */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404BEA8"))) enet_descriptors_struct  rxdesc_tab1[ENET_RXBUF_NUM]                 ;  /*!< ENET RxDMA descriptor */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404BF20"))) uint8_t rx_buff1[ENET_RXBUF_NUM][ENET_RXBUF_SIZE]                    ;  /*!< ENET receive buffer */
 __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404DCF8"))) uint8_t tx_buff1[ENET_TXBUF_NUM][ENET_TXBUF_SIZE]                    ;  /*!< ENET transmit buffer */

#elif defined ( __ICCARM__ )                                            /*!< IAR compiler */
#pragma data_alignment=8
#pragma location=0x24048000
enet_descriptors_struct  txdesc_tab[ENET_TXBUF_NUM];                    /*!< ENET TxDMA descriptor */
#pragma data_alignment=8
#pragma location=0x24048078
enet_tbs_enhanced_descriptors_struct  tbs_txdesc_tab[ENET_TXBUF_NUM];   /*!< ENET TxDMA enhanced descriptor */
#pragma data_alignment=8
#pragma location=0x24048140
enet_descriptors_struct  rxdesc_tab[ENET_RXBUF_NUM];                    /*!< ENET RxDMA descriptor */
#pragma data_alignment=8
#pragma location=0x240481B8
uint8_t rx_buff[ENET_RXBUF_NUM][ENET_RXBUF_SIZE];                       /*!< ENET receive buffer */
#pragma data_alignment=8
#pragma location=0x24049F90
uint8_t tx_buff[ENET_TXBUF_NUM][ENET_TXBUF_SIZE];                       /*!< ENET transmit buffer */

#pragma data_alignment=8
#pragma location=0x2404BD68
enet_descriptors_struct  txdesc_tab1[ENET_TXBUF_NUM];                   /*!< ENET TxDMA descriptor */
#pragma data_alignment=8
#pragma location=0x2404BDE0
enet_tbs_enhanced_descriptors_struct  tbs_txdesc_tab1[ENET_TXBUF_NUM];  /*!< ENET TxDMA enhanced descriptor */
#pragma data_alignment=8
#pragma location=0x2404BEA8
enet_descriptors_struct  rxdesc_tab1[ENET_RXBUF_NUM];                   /*!< ENET RxDMA descriptor */
#pragma data_alignment=8
#pragma location=0x2404BF20
uint8_t rx_buff1[ENET_RXBUF_NUM][ENET_RXBUF_SIZE];                      /*!< ENET receive buffer */
#pragma data_alignment=8
#pragma location=0x2404DCF8
uint8_t tx_buff1[ENET_TXBUF_NUM][ENET_TXBUF_SIZE];                      /*!< ENET transmit buffer */

#elif defined (__GNUC__)        /* GNU Compiler */
enet_descriptors_struct  txdesc_tab[ENET_TXBUF_NUM]                   __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x24048000")));  /*!< ENET TxDMA descriptor */
enet_tbs_enhanced_descriptors_struct  tbs_txdesc_tab[ENET_TXBUF_NUM]  __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x24048078")));  /*!< ENET TxDMA enhanced descriptor */
enet_descriptors_struct  rxdesc_tab[ENET_RXBUF_NUM]                   __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x24048140")));  /*!< ENET RxDMA descriptor */
uint8_t rx_buff[ENET_RXBUF_NUM][ENET_RXBUF_SIZE]                      __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x240481B8")));  /*!< ENET receive buffer */
uint8_t tx_buff[ENET_TXBUF_NUM][ENET_TXBUF_SIZE]                      __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x24049F90")));  /*!< ENET transmit buffer */

enet_descriptors_struct  txdesc_tab1[ENET_TXBUF_NUM]                  __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404BD68")));  /*!< ENET TxDMA descriptor */
enet_tbs_enhanced_descriptors_struct  tbs_txdesc_tab1[ENET_TXBUF_NUM] __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404BDE0")));  /*!< ENET TxDMA enhanced descriptor */
enet_descriptors_struct  rxdesc_tab1[ENET_RXBUF_NUM]                  __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404BEA8")));  /*!< ENET RxDMA descriptor */
uint8_t rx_buff1[ENET_RXBUF_NUM][ENET_RXBUF_SIZE]                     __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404BF20")));  /*!< ENET receive buffer */
uint8_t tx_buff1[ENET_TXBUF_NUM][ENET_TXBUF_SIZE]                     __attribute__((aligned(8))) __attribute__((section(".ARM.__at_0x2404DCF8")));  /*!< ENET transmit buffer */

#endif /* __CC_ARM */


/* global transmit and receive descriptors pointers */
enet_descriptors_struct  *dma_current_txdesc = NULL;
enet_descriptors_struct  *dma_current_rxdesc = NULL;
/* structure pointer of enhanced descriptor for TBS */
enet_tbs_enhanced_descriptors_struct  *dma_current_tbs_txdesc = NULL;


/* global transmit and receive descriptors pointers */
enet_descriptors_struct  *dma_current_txdesc1 = NULL;
enet_descriptors_struct  *dma_current_rxdesc1 = NULL;
/* structure pointer of enhanced descriptor for TBS */
enet_tbs_enhanced_descriptors_struct  *dma_current_tbs_txdesc1 = NULL;

/* init structure parameters for ENET initialization */
static enet_initpara_struct enet_initpara = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
static uint32_t enet_unknow_err = 0U;
/* array of register offset for debug information get */
static const uint16_t enet_reg_tab[] = {
    0x0000, 0x0004, 0x0008, 0x000C, 0x0010, 0x0014, 0x0050, 0x0054, 0x0058, 0x0060, 0x0064,

    0x0070, 0x0090, 0x0094, 0x00A0, 0x00A4, 0x00A8, 0x00B0, 0x00B4, 0x00B8, 0x00C0, 0x00C4,

    0x00D0, 0x00D4, 0x00D8, 0x00DC, 0x0110, 0x0114, 0x011C, 0x0120, 0x0124, 0x0128, 0x0140,

    0x0148, 0x014C, 0x0200, 0x0204, 0x0210, 0x0230, 0x0234, 0x0240, 0x0244, 0x0300, 0x0304,

    0x0308, 0x030C, 0x0310, 0x0314, 0x0700, 0x0704, 0x0708, 0x070C, 0x0710, 0x0714, 0x0718,

    0x071C, 0x0720, 0x0724, 0x0728, 0x072C, 0x0730, 0x0734, 0x0738, 0x073C, 0x0740, 0x0744,

    0x0748, 0x074C, 0x0750, 0x0754, 0x0758, 0x075C, 0x0760, 0x0764, 0x0768, 0x076C, 0x0770,

    0x0774, 0x0778, 0x0780, 0x0784, 0x0788, 0x078C, 0x0790, 0x0794, 0x0798, 0x079C, 0x07A0,

    0x07A4, 0x07A8, 0x07AC, 0x07B0, 0x07B4, 0x07B8, 0x07BC, 0x07C0, 0x07C4, 0x07C8, 0x07CC,

    0x07D0, 0x07D4, 0x07D8, 0x07DC, 0x07E0, 0x07E4, 0x07EC, 0x07F0, 0x07F4, 0x07F8, 0x0800,

    0x0808, 0x0810, 0x0814, 0x0818, 0x081C, 0x0820, 0x0824, 0x0828, 0x082C, 0x0830, 0x0834,

    0x0838, 0x083C, 0x0840, 0x0844, 0x0850, 0x0854, 0x0858, 0x085C, 0x0860, 0x0864, 0x0868,

    0x086C, 0x0870, 0x0874, 0x0878, 0x087C, 0x0880, 0x0884, 0x08A0, 0x08A4, 0x08A8, 0x08AC,

    0x08C0, 0x08C4, 0x08C8, 0x08CC, 0x08D0, 0x08D4, 0x0900, 0x0904, 0x0910, 0x0914, 0x0918,

    0x091C, 0x0930, 0x0934, 0x0940, 0x0944, 0x0948, 0x094C, 0x0960, 0x0964, 0x0970, 0x0974,

    0x0978, 0x097C, 0x0990, 0x0994, 0x09A0, 0x09A4, 0x09A8, 0x09AC, 0x0A70, 0x0A74, 0x0B00,

    0x0B04, 0x0B08, 0x0B0C, 0x0B10, 0x0B14, 0x0B18, 0x0B1C, 0x0B20, 0x0B24, 0x0B28, 0x0B30,

    0x0B34, 0x0B50, 0x0B54, 0x0B58, 0x0B5C, 0x0B60, 0x0B64, 0x0B68, 0x0B6C, 0x0B70, 0x0B80,

    0x0B84, 0x0B88, 0x0B8C, 0x0B90, 0x0B94, 0x0B98, 0x0B9C, 0x0BA0, 0x0BA4, 0x0BA8, 0x0BAC,

    0x0BB0, 0x0BB4, 0x0BB8, 0x0BBC, 0x0C00, 0x0C08, 0x0C0C, 0x0C10, 0x0C20, 0x0C30, 0x0C40, 

    0x0C50, 0x0C54, 0x0C58, 0x0C60, 0x0C64, 0x0C68, 0x0C70, 0x0C80, 0x0C84, 0x0C90, 0x0C94,

    0x0CA0, 0x0CA4, 0x0CA8, 0x0CAC, 0x0CB0, 0x0CB4, 0x0CB8, 0x0CC0, 0x0CC4, 0x0CC8, 0x0CCC,

    0x0CD0, 0x0CD4, 0x0CD8, 0x0CE0, 0x0CE4, 0x0D00, 0x0D04, 0x0D08, 0x0D14, 0x0D18, 0x0D2C,

    0x0D30, 0x0D34, 0x0D38, 0x0D3C, 0x0D40, 0x0D44, 0x0D48, 0x0D50, 0x0D54, 0x0D58, 0x0D5C,

    0x0D60, 0x0D64, 0x0D6C, 0x0D70, 0x0D74, 0x0D78, 0x0D7C, 0x1000, 0x1004, 0x1008, 0x100C,

    0x1050, 0x1080, 0x1100, 0x1104, 0x1108, 0x1114, 0x111C, 0x1120, 0x1128, 0x112C, 0x1130,

    0x1134, 0x1138, 0x113C, 0x1144, 0x114C, 0x1154, 0x115C, 0x1160, 0x1164, 0x1168, 0x1180,

    0x1184, 0x1188, 0x1194, 0x119C, 0x11A0, 0x11A8, 0x11AC, 0x11B0, 0x11B4, 0x11B8, 0x11BC,

    0x11C4, 0x11CC, 0x11D4, 0x11DC, 0x11E0, 0x11E4, 0x11E8
};

/* ENET registers reset value */
static const uint32_t enet_reg_reset_value[] = {
    0x00008000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x03E80000, 0x00000000, 0x00000000, 0x00001053, 0x00000000, 0x0A0973F5, 0x211829A6, 0x04041041, 0x6C370E31, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x8000FFFF, 0xFFFFFFFF,

    0x0000FFFF, 0xFFFFFFFF, 0x0000FFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000018, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x803F003F, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,

    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};
#ifdef USE_DELAY
/* user can provide more timing precise ENET_DELAY_ function */
#define ENET_DELAY(x)                              delay_ms(x)
#else
/* insert a delay time */
static void enet_delay(uint32_t ncount);
/* default ENET_DELAY_ function with less precise timing */
#define ENET_DELAY(x)                              enet_delay(x)
#endif

/*!
    \brief      deinitialize the ENET module
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_deinit(void)
{
    uint32_t offset, limit;
    offset = 0U;

    limit = sizeof(enet_reg_tab) / sizeof(uint16_t);

    for(; offset < limit; offset++) {
        REG32((ENET) + enet_reg_tab[offset]) = enet_reg_reset_value[offset];
    }
    rcu_periph_reset_enable(RCU_ENETRST);
    rcu_periph_reset_disable(RCU_ENETRST);
}


/*!
    \brief    configure the parameters which are usually less cared for initialization
                note -- this function must be called before enet_init(), otherwise
                configuration will be no effect
    \param[in]  option: different function option, which is related to several parameters,
                only one parameter can be selected which is shown as below, refer to enet_option_enum
      \arg        FORWARD_OPTION: choose to configure the frame forward related parameters
      \arg        DMABUS_OPTION: choose to configure the DMA bus mode related parameters
      \arg        DMACH0_MAXBURST_OPTION: choose to configure the DMA channel 0 max burst related parameters
      \arg        DMACH1_MAXBURST_OPTION: choose to configure the DMA channel 1 max burst related parameters
      \arg        DMA_ARBITRATION_OPTION: choose to configure the DMA arbitration related parameters
      \arg        TX0STORE_OPTION: configure the transmit queue 0 store forward mode related parameters
      \arg        RX0STORE_OPTION: configure the receive queue 0 store forward mode related parameters
      \arg        TX1STORE_OPTION: configure the transmit queue 1 store forward mode related parameters
      \arg        RX1STORE_OPTION: configure the receive queue 1 store forward mode related parameters
      \arg        VLAN_CONFIG_OPTION: configure the VLAN tag related parameters
      \arg        VLAN_COMPARISON_OPTION: configure the VLAN tag related parameters
      \arg        VLAN_INSERT_OPTION: configure the VLAN tag insertion or replacement related parameters
      \arg        INNERVLAN_INSERT_OPTION : configure the INNER VLAN tag insertion or replacement related parameters
      \arg        FLOWCTL_OPTION: configure the flow control related parameters
      \arg        HASHH_OPTION: configure the hash list high 32-bit related parameters
      \arg        HASHL_OPTION: configure the hash list low 32-bit related parameters
      \arg        FILTER_OPTION: configure the frame filter control related parameters
      \arg        HALFDUPLEX_OPTION: configure the halfduplex related parameters
      \arg        FULLDUPLEX_OPTION: configure the fullduplex related parameters
      \arg        PACKETSIZE_OPTION: configure the packet size related parameters
      \arg        TIMER_OPTION: configure the frame timer related parameters
      \arg        MACCONTROL_OPTION: configure the frame timer related parameters
      \arg        INTERFRAMEGAP_OPTION: configure the inter frame gap related parameters
      \arg        ECCCONTROL_OPTION: configure the ECC control related parameters
      \arg        DPPCONTROL_OPTION: configure the DPP control related parameters
      \arg        FSMCONTROL_OPTION: configure the FSM control related parameters
      \arg        ESTCONTROL_OPTION: configure the EST control related parameters
      \arg        FPECONTROL_OPTION: configure the FPE control related parameters
    \param[in]  para: the related parameters according to the option
                all the related parameters should be configured which are shown as below
                      FORWARD_OPTION related parameters:
                      -  ENET_AUTO_PADCRC_STRIP_ENABLE/ ENET_AUTO_PADCRC_STRIP_DISABLE ;
                      -  ENET_TYPEPACKET_CRC_STRIP_ENABLE/ ENET_TYPEPACKET_CRC_STRIP_DISABLE ;
                      -  ENET_RXQ0_FORWARD_ERRFRAMES_ENABLE/ ENET_RXQ0_FORWARD_ERRFRAMES_DISABLE ;
                      -  ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES_ENABLE/ ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES_DISABLE ;
                      -  ENET_RXQ1_FORWARD_ERRFRAMES_ENABLE/ ENET_RXQ1_FORWARD_ERRFRAMES_DISABLE ;
                      -  ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES_ENABLE/ ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES_DISABLE .
                      DMABUS_OPTION related parameters:
                      -  ENET_ADDRESS_ALIGN_ENABLE/ ENET_ADDRESS_ALIGN_DISABLE ;
                      -  ENET_FIXED_BURST_ENABLE/ ENET_FIXED_BURST_DISABLE ;
                      -  ENET_MIXED_BURST_ENABLE/ ENET_MIXED_BURST_DISABLE ;
                      DMACH0_MAXBURST_OPTION related parameters:  
                      -  ENET_RXDP_1BEAT/ ENET_RXDP_2BEAT/ ENET_RXDP_4BEAT/
                         ENET_RXDP_8BEAT/ ENET_RXDP_16BEAT/ ENET_RXDP_32BEAT/
                         ENET_RXDP_8xPGBL_8BEAT/ ENET_RXDP_8xPGBL_16BEAT/
                         ENET_RXDP_8xPGBL_32BEAT/ ENET_RXDP_8xPGBL_64BEAT/
                         ENET_RXDP_8xPGBL_128BEAT/ ENET_RXDP_8xPGBL_256BEAT;
                      -  ENET_PGBL_1BEAT/ ENET_PGBL_2BEAT/ ENET_PGBL_4BEAT/
                         ENET_PGBL_8BEAT/ ENET_PGBL_16BEAT/ ENET_PGBL_32BEAT/
                         ENET_PGBL_8xPGBL_8BEAT/ ENET_PGBL_8xPGBL_16BEAT/
                         ENET_PGBL_8xPGBL_32BEAT/ ENET_PGBL_8xPGBL_64BEAT/
                         ENET_PGBL_8xPGBL_128BEAT/ ENET_PGBL_8xPGBL_256BEAT;
                      DMACH1_MAXBURST_OPTION related parameters:  
                      -  ENET_RXDP_1BEAT/ ENET_RXDP_2BEAT/ ENET_RXDP_4BEAT/
                         ENET_RXDP_8BEAT/ ENET_RXDP_16BEAT/ ENET_RXDP_32BEAT/
                         ENET_RXDP_8xPGBL_8BEAT/ ENET_RXDP_8xPGBL_16BEAT/
                         ENET_RXDP_8xPGBL_32BEAT/ ENET_RXDP_8xPGBL_64BEAT/
                         ENET_RXDP_8xPGBL_128BEAT/ ENET_RXDP_8xPGBL_256BEAT;
                      -  ENET_PGBL_1BEAT/ ENET_PGBL_2BEAT/ ENET_PGBL_4BEAT/
                         ENET_PGBL_8BEAT/ ENET_PGBL_16BEAT/ ENET_PGBL_32BEAT/
                         ENET_PGBL_8xPGBL_8BEAT/ ENET_PGBL_8xPGBL_16BEAT/
                         ENET_PGBL_8xPGBL_32BEAT/ ENET_PGBL_8xPGBL_64BEAT/
                         ENET_PGBL_8xPGBL_128BEAT/ ENET_PGBL_8xPGBL_256BEAT;
                      DMA_ARBITRATION_OPTION related parameters:
                      -  ENET_ARBITRATION_RXTX_1_1 / ENET_ARBITRATION_RXTX_2_1 / ENET_ARBITRATION_RXTX_3_1 \
                         / ENET_ARBITRATION_RXTX_4_1 / ENET_ARBITRATION_RXTX_5_1 / ENET_ARBITRATION_RXTX_6_1 \
                         / ENET_ARBITRATION_RXTX_7_1 / ENET_ARBITRATION_RXTX_8_1 / ENET_ARBITRATION_TXRX_1_1 \
                         / ENET_ARBITRATION_TXRX_2_1 / ENET_ARBITRATION_TXRX_3_1 / ENET_ARBITRATION_TXRX_4_1 \
                         / ENET_ARBITRATION_TXRX_5_1 / ENET_ARBITRATION_TXRX_6_1 / ENET_ARBITRATION_TXRX_7_1 \
                         / ENET_ARBITRATION_TXRX_8_1.
                      TX0STORE_OPTION related parameters:
                      -  ENET_TX_MODE_STOREFORWARD/ ENET_TX_MODE_CUTTHROUGH ;
                      -  ENET_TX_THRESHOLD_32BYTES/ ENET_TX_THRESHOLD_64BYTES/
                         ENET_TX_THRESHOLD_96BYTES/ ENET_TX_THRESHOLD_128BYTES/
                         ENET_TX_THRESHOLD_192BYTES/ ENET_TX_THRESHOLD_256BYTES/
                         ENET_TX_THRESHOLD_284BYTES/ ENET_TX_THRESHOLD_512BYTES.
                      RX0STORE_OPTION related parameters:
                      -  ENET_RX_MODE_STOREFORWARD/ ENET_RX_MODE_CUTTHROUGH ;
                      -  ENET_RX_THRESHOLD_32BYTES/ ENET_RX_THRESHOLD_64BYTES/
                         ENET_RX_THRESHOLD_96BYTES/ ENET_RX_THRESHOLD_128BYTES ;
                      TX1STORE_OPTION related parameters:
                      -  ENET_TX_MODE_STOREFORWARD/ ENET_TX_MODE_CUTTHROUGH ;
                      -  ENET_TX_THRESHOLD_32BYTES/ ENET_TX_THRESHOLD_64BYTES/
                         ENET_TX_THRESHOLD_96BYTES/ ENET_TX_THRESHOLD_128BYTES/
                         ENET_TX_THRESHOLD_192BYTES/ ENET_TX_THRESHOLD_256BYTES/
                         ENET_TX_THRESHOLD_284BYTES/ ENET_TX_THRESHOLD_512BYTES.
                      RX1STORE_OPTION related parameters:
                      -  ENET_RX_MODE_STOREFORWARD/ ENET_RX_MODE_CUTTHROUGH ;
                      -  ENET_RX_THRESHOLD_32BYTES/ ENET_RX_THRESHOLD_64BYTES/
                         ENET_RX_THRESHOLD_96BYTES/ ENET_RX_THRESHOLD_128BYTES ;
                      VLAN_CONFIG_OPTION related parameters:
                      -  ENET_RXINVLAN_ENABLE/ ENET_RXINVLAN_DISABLE ;
                      -  ENET_INVLANSTRIP_DISABLE/ ENET_INVLANSTRIP_PASS ;
                      -  ENET_INVLANSTRIP_NOPASS/ ENET_INVLANSTRIP_ENABLE ;
                      -  ENET_INVLANCOMPARISON_ENABLE/ ENET_INVLANCOMPARISON_DISABLE ;
                      -  ENET_DOUBLEVLAN_ENABLE/ ENET_DOUBLEVLAN_DISABLE ;
                      -  ENET_VLANHASHMATCH_ENABLE/ ENET_VLANHASHMATCH_DISABLE ;
                      -  ENET_RXOUTVLAN_ENABLE/ ENET_RXOUTVLAN_DISABLE ;
                      -  ENET_OUTVLANSTRIP_DISABLE/ ENET_OUTVLANSTRIP_PASS ;
                      -  ENET_OUTVLANSTRIP_NOPASS/ ENET_OUTVLANSTRIP_ENABLE ;
                      -  ENET_VLANTYPECHECK_ENABLE/ ENET_VLANTYPECHECK_DISABLE ;
                      -  ENET_SVLANHASHMATCH_ENABLE/ ENET_SVLANHASHMATCH_DISABLE ;
                      -  ENET_SVLAN_ENABLE/ ENET_SVLAN_DISABLE ;
                      -  ENET_VLANINVERSEMATCH_ENABLE/ ENET_VLANINVERSEMATCH_DISABLE ;
                      -  ENET_VLANTAGHASHCOMPARISON_12BIT/ ENET_VLANTAGHASHCOMPARISON_16BIT ;
                      VLAN_COMPARISON_OPTION related parameters:
                      -  MAC_VLAN_TAG_FILTER0 / MAC_VLAN_TAG_FILTER1 /
                         MAC_VLAN_TAG_FILTER2 / MAC_VLAN_TAG_FILTER3;
                      -  ENET_VLANTAGCOMPARISON_INNER/ ENET_VLANTAGCOMPARISON_OUTER ;
                      -  ENET_SVLANTAGMATCH_ENABLE/ ENET_SVLANTAGMATCH_DISABLE ;
                      -  ENET_VLANTYPECOMPARISON_ENABLE/ ENET_VLANTYPECOMPARISON_DISABLE;
                      -  ENET_VLANTAGCOMPARISON_12BIT/ ENET_VLANTAGCOMPARISON_16BIT;
                      -  ENET_VLANTAGCOMPARISON_ENABLE/ ENET_VLANTAGCOMPARISON_DISABLE ;
                      -  MAC_VLAN_TAG_DATA_VID(regval);
                      VLAN_INSERT_OPTION related parameters:
                      -  ENET_VLANTAG_FROM_DES / ENET_VLANTAG_FROM_REG ;
                      -  ENET_VLANTAG_INSERT_REPLACE_SVLAN / ENET_VLANTAG_INSERT_REPLACE_CVLAN ;
                      -  ENET_VLANTAG_PRIORITY_ENABLE/ ENET_VLANTAG_PRIORITY_DISABLE ;
                      -  ENET_VLANTAG_NO_OPERATIOM/ ENET_VLANTAG_DELETION /
                         ENET_VLANTAG_INSERTATION/ ENET_VLANTAG_REPLACEMENT ;
                      INNERVLAN_INSERT_OPTION related parameters:
                      -  ENET_INNER_VLANTAG_FROM_DES / ENET_INNER_VLANTAG_FROM_REG ;
                      -  ENET_INNER_VLANTAG_INSERT_REPLACE_SVLAN / ENET_INNER_VLANTAG_INSERT_REPLACE_CVLAN ;
                      -  ENET_INNER_VLANTAG_PRIORITY_ENABLE/ ENET_INNER_VLANTAG_PRIORITY_DISABLE ;
                      -  ENET_INNER_VLANTAG_NO_OPERATIOM/ ENET_INNER_VLANTAG_DELETION /
                         ENET_INNER_VLANTAG_INSERTATION/ ENET_INNER_VLANTAG_REPLACEMENT ;
                      -  MAC_INNER_VLAN_TAG_DATA_VID(regval)
                      FLOWCTL_OPTION related parameters:
                      -  MAC_Q0_TX_FLOW_CTRL_PT(regval) ;
                      -  ENET_ZERO_QUANTA_PAUSE_ENABLE/ ENET_ZERO_QUANTA_PAUSE_DISABLE ;
                         ENET_PAUSETIME_MINUS4/ ENET_PAUSETIME_MINUS28/
                         ENET_PAUSETIME_MINUS36/ ENET_PAUSETIME_MINUS144/
                         ENET_PAUSETIME_MINUS256/ENET_PAUSETIME_MINUS256_2 ;
                      -  ENET_MAC0_AND_UNIQUE_ADDRESS_PAUSEDETECT/ ENET_UNIQUE_PAUSEDETECT ;
                      -  ENET_RX_FLOWCONTROL_ENABLE/ ENET_RX_FLOWCONTROL_DISABLE ;
                      -  ENET_TX_FLOWCONTROL_ENABLE/ ENET_TX_FLOWCONTROL_DISABLE ;
                      -  ENET_RXQ0_HARDWARE_FLOW_CONTROL_ENABLE/ ENET_RXQ0_HARDWARE_FLOW_CONTROL_DISABLE ;
                      -  ENET_RXQ1_HARDWARE_FLOW_CONTROL_ENABLE/ ENET_RXQ1_HARDWARE_FLOW_CONTROL_DISABLE ;
                      HASHH_OPTION related parameters:
                      -  0x0~0xFFFF FFFFU
                      HASHL_OPTION related parameters:
                      -  0x0~0xFFFF FFFFU
                      FILTER_OPTION related parameters:
                      -  ENET_SRC_FILTER_NORMAL_ENABLE/ ENET_SRC_FILTER_INVERSE_ENABLE/
                         ENET_SRC_FILTER_DISABLE ;
                      -  ENET_DEST_FILTER_INVERSE_ENABLE/ ENET_DEST_FILTER_INVERSE_DISABLE ;
                      -  ENET_MULTICAST_FILTER_HASH_OR_PERFECT/ ENET_MULTICAST_FILTER_HASH/
                         ENET_MULTICAST_FILTER_PERFECT/ ENET_MULTICAST_FILTER_NONE/
                         ENET_MULTICAST_FILTER_PASS;
                      -  ENET_DROP_NONTCPUDP_ENABLE/ENET_DROP_NONTCPUDP_DISABLE;
                      -  ENET_VLAN_FILTER_ENABLE/ENET_VLAN_FILTER_DISABLE;
                      -  ENET_L3L4_FILTER_ENABLE/ENET_L3L4_FILTER_DISABLE;
                      -  ENET_UNICAST_FILTER_EITHER/ ENET_UNICAST_FILTER_HASH/
                         ENET_UNICAST_FILTER_PERFECT ;
                      -  ENET_PCF_PREVENT_ALL/ ENET_PCF_PREVENT_PAUSEFRAME/
                         ENET_PCF_FORWARD_ALL/ ENET_PCF_FORWARD_FILTERED .
                      HALFDUPLEX_OPTION related parameters:
                      -  ENET_CARRIERSENSE_ENABLE/ ENET_CARRIERSENSE_DISABLE
                      -  ENET_RECEIVEOWN_ENABLE/ ENET_RECEIVEOWN_DISABLE ;
                      -  ENET_RETRYTRANSMISSION_ENABLE/ ENET_RETRYTRANSMISSION_DISABLE
                      -  ENET_BACKOFFLIMIT_10/ ENET_BACKOFFLIMIT_8/
                         ENET_BACKOFFLIMIT_4/ ENET_BACKOFFLIMIT_1 ;
                      -  ENET_DEFERRALCHECK_ENABLE/ ENET_DEFERRALCHECK_DISABLE
                      FULLDUPLEX_OPTION related parameters:
                      -  ENET_FULLDUPLEX_CARRIERSENSE_ENABLE/ ENET_FULLDUPLEX_CARRIERSENSE_DISABLE ;
                      -  ENET_PREAMBLE_LENGTH_7BYTE/ ENET_PREAMBLE_LENGTH_5BYTE/
                         ENET_PREAMBLE_LENGTH_3BYTE;
                      PACKETSIZE_OPTION related parameters:
                      -  ENET_2KMAX_PACKET_ENABLE/ ENET_2KMAX_PACKET_DISABLE ;
                      -  ENET_JUMBO_PACKET_ENABLE/ ENET_JUMBO_PACKET_DISABLE ;
                      -  ENET_GIANT_PACKET_LIMIT_ENABLE/ ENET_GIANT_PACKET_LIMIT_DISABLE ;
                      TIMER_OPTION related parameters:
                      -  ENET_WATCHDOG_ENABLE/ ENET_WATCHDOG_DISABLE ;
                      -  ENET_JABBER_ENABLE/ ENET_JABBER_DISABLE ;
                      MACCONTROL_OPTION related parameters:
                      -  ENET_ARP_OFFLOAD_ENABLE/ ENET_ARP_OFFLOAD_DISABLE ;
                      -  ENET_SARC_INTERNAL_SIGNAL/ ENET_SARC_ADDR0_INSERT/
                         ENET_SARC_ADDR0_REPLACE/ ENET_SARC_ADDR1_INSERT/ 
                         ENET_SARC_ADDR1_REPLACE;
                      INTERFRAMEGAP_OPTION related parameters:
                      -  ENET_INTERPACKETGAP_96BIT/ ENET_INTERPACKETGAP_88BIT/
                         ENET_INTERPACKETGAP_80BIT/ ENET_INTERPACKETGAP_72BIT/
                         ENET_INTERPACKETGAP_64BIT/ ENET_INTERPACKETGAP_56BIT/
                         ENET_INTERPACKETGAP_48BIT/ ENET_INTERPACKETGAP_40BIT ;
                      ECCCONTROL_OPTION related parameters:
                      -  ENET_MTL_TXFIFO_ECC_ENABLE/ ENET_MTL_TXFIFO_ECC_DISABLE ;
                      -  ENET_MTL_RXFIFO_ECC_ENABLE/ ENET_MTL_RXFIFO_ECC_DISABLE ;
                      -  ENET_RETRYTRANSMISSION_ENABLE/ ENET_RETRYTRANSMISSION_DISABLE ;
                      -  ENET_MTL_EST_ECC_ENABLE/ ENET_MTL_EST_ECC_DISABLE;
                      -  ENET_MTL_RXP_ECC_ENABLE/ ENET_MTL_RXP_ECC_DISABLE;
                      -  ENET_MTL_EST_ECC_ENABLE/ ENET_MTL_EST_ECC_DISABLE.
                      DPPCONTROL_OPTION related parameters:
                      -  ENET_DATA_PATH_PARITY_PROTECTION_ENABLE/ ENET_DATA_PATH_PARITY_PROTECTION_DISABLE ;
                      -  ENET_DPP_ODD_PARITY_ENABLE/ ENET_DPP_ODD_PARITY_DISABLE ;
                      -  ENET_DPP_PARITY_ON_SLAVE_INTERFACE_ENABLE/ ENET_DPP_ODD_PARITY_DISABLE ;
                      -  ENET_DPP_IPETID_ENABLE/ ENET_DPP_IPETID_DISABLE ;
                      -  ENET_DPP_IPETRD_ENABLE/ ENET_DPP_IPETRD_DISABLE ;
                      -  ENET_DPP_IPEMTF_ENABLE/ ENET_DPP_IPEMTF_DISABLE ;
                      -  ENET_DPP_IPEMTS_ENABLE/ ENET_DPP_IPEMTS_DISABLE ;
                      -  ENET_DPP_IPERID_ENABLE/ ENET_DPP_IPERID_DISABLE ;
                      -  ENET_DPP_IPEMTBU_ENABLE/ ENET_DPP_IPEMTBU_DISABLE ;
                      -  ENET_DPP_IPEMTFC_ENABLE/ ENET_DPP_IPEMTFC_DISABLE ;
                      -  ENET_DPP_IPEMRWC_ENABLE/ ENET_DPP_IPEMRWC_DISABLE ;
                      FSMCONTROL_OPTION related parameters:
                      -  ENET_PTP_DOMAIN_LARGE_MODE/ ENET_PTP_DOMAIN_NORMAL_MODE ;
                      -  ENET_APP_DOMAIN_LARGE_MODE/ ENET_APP_DOMAIN_NORMAL_MODE ;
                      -  ENET_CSR_DOMAIN_LARGE_MODE/ ENET_CSR_DOMAIN_NORMAL_MODE ;
                      -  ENET_RX_DOMAIN_LARGE_MODE/ ENET_RX_DOMAIN_NORMAL_MODE ;
                      -  ENET_TX_DOMAIN_LARGE_MODE/ ENET_TX_DOMAIN_NORMAL_MODE ;
                      -  ENET_PTP_FSM_PARITY_ERROR_INJECTION_ENABLE/ ENET_PTP_FSM_PARITY_ERROR_INJECTION_DISABLE ;
                      -  ENET_APP_FSM_PARITY_ERROR_INJECTION_ENABLE/ ENET_APP_FSM_PARITY_ERROR_INJECTION_DISABLE ;
                      -  ENET_CSR_FSM_ONEHOTPROTECTION_ERROR_INJECTION_ENABLE/ ENET_CSR_FSM_ONEHOTPROTECTION_ERROR_INJECTION_DISABLE ;
                      -  ENET_RX_FSM_PARITY_ERROR_INJECTION_ENABLE/ ENET_RX_FSM_PARITY_ERROR_INJECTION_DISABLE ;
                      -  ENET_TX_FSM_PARITY_ERROR_INJECTION_ENABLE/ ENET_TX_FSM_PARITY_ERROR_INJECTION_DISABLE ;
                      -  ENET_PTP_FSM_TIMEOUT_ERROR_INJECTION_ENABLE/ ENET_PTP_FSM_TIMEOUT_ERROR_INJECTION_DISABLE ;
                      -  ENET_APP_FSM_TIMEOUT_ERROR_INJECTION_ENABLE/ ENET_APP_FSM_TIMEOUT_ERROR_INJECTION_DISABLE ;
                      -  ENET_CSR_FSM_TIMEOUT_ERROR_INJECTION_ENABLE/ ENET_CSR_FSM_TIMEOUT_ERROR_INJECTION_DISABLE ;
                      -  ENET_RX_FSM_TIMEOUT_ERROR_INJECTION_ENABLE/ ENET_RX_FSM_TIMEOUT_ERROR_INJECTION_DISABLE ;
                      -  ENET_TX_FSM_TIMEOUT_ERROR_INJECTION_ENABLE/ ENET_TX_FSM_TIMEOUT_ERROR_INJECTION_DISABLE ;
                      -  ENET_PTP_FSM_TIMEOUT_ERROR_INJECTION_ENABLE/ ENET_PTP_FSM_TIMEOUT_ERROR_INJECTION_DISABLE ;
                      -  ENET_FSM_PARITY_FEATURE_ENABLE/ ENET_FSM_PARITY_FEATURE_DISABLE ;
                      -  ENET_FSM_TIMEOUT_FEATURE_ENABLE/ ENET_FSM_TIMEOUT_FEATURE_DISABLE ;
                      ESTCONTROL_OPTION related parameters:
                      -  ENET_EST_ENABLE/ ENET_EST_DISABLE ;
                      -  ENET_QUICK_ASSERT_HLBF_ERR_ENABLE / ENET_QUICK_ASSERT_HLBF_ERR_DISABLE;
                      -  ENET_EST_DONT_DROP_SIZE_ERR_FRAME / ENET_EST_DROP_SIZE_ERR_FRAME;
                      -  ENET_EST_DROP_SCHEDULING_ERR_FRAME / ENET_EST_DONT_DROP_SCHEDULING_ERR_FRAME;
                      -  ENET_GCL_INTERATE_4 / ENET_GCL_INTERATE_8 /
                         ENET_GCL_INTERATE_16 / ENET_GCL_INTERATE_32;
                      -  ENET_GCL_TIME_INTERVAL_LEFT_SHIFT_0/ ENET_GCL_TIME_INTERVAL_LEFT_SHIFT_1/
                         ENET_GCL_TIME_INTERVAL_LEFT_SHIFT_2/ ENET_GCL_TIME_INTERVAL_LEFT_SHIFT_7;
                      -  MTL_EST_CONTROL_CTOV(regval);
                      -  MTL_EST_CONTROL_PTOV(regval);
                      FPECONTROL_OPTION related parameters:
                      -  ENET_GCL_LEVEL_BASED_HOLD_TRANSITION_ENABLE / ENET_GCL_LEVEL_BASED_HOLD_TRANSITION_DISABLE;
                      -  ENET_FPE_Q0_AS_PREEMPTABLE/ ENET_FPE_Q1_AS_PREEMPTABLE;
                      -  ENET_FPE_ADD_FRAG_SIZE_64B/ ENET_FPE_ADD_FRAG_SIZE_128B /
                         ENET_FPE_ADD_FRAG_SIZE_192B / ENET_FPE_ADD_FRAG_SIZE_256B;
    \param[out] none
    \retval     none
*/
void enet_initpara_config(enet_option_enum option, uint32_t para)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if((FORWARD_OPTION == option) && NOT_ENET_FORWARD_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((DMABUS_OPTION == option) && NOT_ENET_DMABUS_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((DMACH0_MAXBURST_OPTION == option || DMACH1_MAXBURST_OPTION == option) && NOT_ENET_DMACH_MAXBURST_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((DMA_ARBITRATION_OPTION == option) && NOT_ENET_DMA_ARBITRATION_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((TX0STORE_OPTION == option || TX1STORE_OPTION == option) && NOT_ENET_TXSTORE_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((RX0STORE_OPTION == option || RX1STORE_OPTION == option) && NOT_ENET_RXSTORE_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((VLAN_CONFIG_OPTION == option) && NOT_ENET_VLAN_CONFIG_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((VLAN_COMPARISON_OPTION == option) && NOT_ENET_VLAN_COMPARISON_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((VLAN_INSERT_OPTION == option) && NOT_ENET_VLAN_INSERT_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((INNERVLAN_INSERT_OPTION == option) && NOT_ENET_INNERVLAN_INSERT_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((FLOWCTL_OPTION == option) && NOT_ENET_FLOWCTL_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((FILTER_OPTION == option) && NOT_ENET_FILTER_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((HALFDUPLEX_OPTION == option) && NOT_ENET_HALFDUPLEX_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((PACKETSIZE_OPTION == option) && NOT_ENET_PACKETSIZE_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((TIMER_OPTION == option) && NOT_ENET_TIMER_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((MACCONTROL_OPTION == option) && NOT_ENET_MACCONTROL_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((INTERFRAMEGAP_OPTION == option) && NOT_ENET_INTERFRAMEGAP_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((ECCCONTROL_OPTION == option) && NOT_ENET_ECCCONTROL_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((DPPCONTROL_OPTION == option) && NOT_ENET_DPPCONTROL_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((FSMCONTROL_OPTION == option) && NOT_ENET_FSMCONTROL_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((ESTCONTROL_OPTION == option) && NOT_ENET_ESTCONTROL_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if((FPECONTROL_OPTION== option) && NOT_ENET_FPECONTROL_OPTION(para)) {
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(option) {
        case FORWARD_OPTION:
            /* choose to configure forward_frame, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)FORWARD_OPTION;
            enet_initpara.forward_frame = para;
            break;
        case DMABUS_OPTION:
            /* choose to configure dmabus_mode, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)DMABUS_OPTION;
            enet_initpara.dmabus_mode = para;
            break;
        case DMACH0_MAXBURST_OPTION:
            /* choose to configure dmach0_maxburst, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)DMACH0_MAXBURST_OPTION;
            enet_initpara.dmach0_maxburst = para;
            break;
        case DMACH1_MAXBURST_OPTION:
            /* choose to configure dmach1_maxburst, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)DMACH1_MAXBURST_OPTION;
            enet_initpara.dmach1_maxburst = para;
            break;
        case DMA_ARBITRATION_OPTION:
            /* choose to configure dma_arbitration, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)DMA_ARBITRATION_OPTION;
            enet_initpara.dma_arbitration = para;
            break;
        case TX0STORE_OPTION:
            /* choose to configure store_forward_mode, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)TX0STORE_OPTION;
            enet_initpara.tx0store_forward_mode = para;
            break;
        case RX0STORE_OPTION:
            /* choose to configure store_forward_mode, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)RX0STORE_OPTION;
            enet_initpara.rx0store_forward_mode = para;
            break;
        case TX1STORE_OPTION:
            /* choose to configure store_forward_mode, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)TX1STORE_OPTION;
            enet_initpara.tx1store_forward_mode = para;
            break;
        case RX1STORE_OPTION:
            /* choose to configure store_forward_mode, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)RX1STORE_OPTION;
            enet_initpara.rx1store_forward_mode = para;
            break;
        case VLAN_CONFIG_OPTION:
            /* choose to configure vlan_config, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)VLAN_CONFIG_OPTION;
            enet_initpara.vlan_config = para;
            break;
        case VLAN_COMPARISON_OPTION:
            /* choose to configure vlan_config, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)VLAN_COMPARISON_OPTION;
            enet_initpara.vlan_compare = para;
            break;
        case VLAN_INSERT_OPTION:
            /* choose to configure vlan_config, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)VLAN_INSERT_OPTION;
            enet_initpara.vlan_insert = para;
            break;
        case INNERVLAN_INSERT_OPTION:
            /* choose to configure vlan_config, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)INNERVLAN_INSERT_OPTION;
            enet_initpara.innervlan_insert = para;
            break;
        case FLOWCTL_OPTION:
            /* choose to configure flow_control, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)FLOWCTL_OPTION;
            enet_initpara.flow_control = para;
            break;
        case HASHH_OPTION:
            /* choose to configure hashtable_high, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)HASHH_OPTION;
            enet_initpara.hashtable_high = para;
            break;
        case HASHL_OPTION:
            /* choose to configure hashtable_low, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)HASHL_OPTION;
            enet_initpara.hashtable_low = para;
            break;
        case FILTER_OPTION:
            /* choose to configure framesfilter_mode, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)FILTER_OPTION;
            enet_initpara.framesfilter_mode = para;
            break;
        case HALFDUPLEX_OPTION:
            /* choose to configure halfduplex_param, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)HALFDUPLEX_OPTION;
            enet_initpara.halfduplex_param = para;
            break;
        case FULLDUPLEX_OPTION:
            /* choose to configure halfduplex_param, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)FULLDUPLEX_OPTION;
            enet_initpara.fullduplex_param = para;
            break;
        case PACKETSIZE_OPTION:
            /* choose to configure halfduplex_param, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)PACKETSIZE_OPTION;
            enet_initpara.packetsize_config = para;
            break;
        case TIMER_OPTION:
            /* choose to configure timer_config, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)TIMER_OPTION;
            enet_initpara.timer_config = para;
            break;
        case MACCONTROL_OPTION:
            /* choose to configure timer_config, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)MACCONTROL_OPTION;
            enet_initpara.maccontrol_param = para;
            break;
        case INTERFRAMEGAP_OPTION:
            /* choose to configure interframegap, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)INTERFRAMEGAP_OPTION;
            enet_initpara.interframegap = para;
            break;
        case ECCCONTROL_OPTION:
            /* choose to configure ecccontrol, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)ECCCONTROL_OPTION;
            enet_initpara.ecccontrol = para;
            break;
        case DPPCONTROL_OPTION:
            /* choose to configure dppcontrol, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)DPPCONTROL_OPTION;
            enet_initpara.dppcontrol = para;
            break;
        case FSMCONTROL_OPTION:
            /* choose to configure fsmcontrol, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)FSMCONTROL_OPTION;
            enet_initpara.fsmcontrol = para;
            break;
        case ESTCONTROL_OPTION:
            /* choose to configure fsmcontrol, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)ESTCONTROL_OPTION;
            enet_initpara.estcontrol = para;
            break;
        case FPECONTROL_OPTION:
            /* choose to configure fsmcontrol, and save the configuration parameters */
            enet_initpara.option_enable |= (uint32_t)FPECONTROL_OPTION;
            enet_initpara.fpecontrol = para;
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      initialize ENET parameter structure with a default value
    \param[in]  type: the type of ENET parameter struct
                only one parameter can be selected which is shown as below:
      \arg        ENET_MTL0_INIT_STRUCT: the ENET MTL0 initial struct
      \arg        ENET_MTL1_INIT_STRUCT: the ENET MTL1 initial struct
      \arg        ENET_DMA_CH0_INIT_STRUCT: the ENET DMA channel0 initial struct
      \arg        ENET_DMA_CH0_INIT_STRUCT: the ENET DMA channel1 initial struct
      \arg        ENET_MAC_INIT_STRUCT: the ENET MAC initial struct
      \arg        ENET_TXQ1_CBS_INIT_STRUCT: the ENET MAC initial struct
      \arg        ENET_PHY_CFG_INIT_STRUCT: the ENET PHY config initial struct
      \arg        ENET_EST_CFG_INIT_STRUCT: the ENET EST config initial struct
      \arg        ENET_FPE_CFG_INIT_STRUCT: the ENET FPE config initial struct
    \param[in]  p_struct: the pointer of the specific struct
    \param[out] none
    \retval     none
*/
void enet_struct_para_init(enet_struct_type_enum type, void *p_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(p_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
     {
    /* get type of the struct */
    switch(type) {
    /* used for enet_init() */
    case ENET_MTL0_INIT_STRUCT:
        ((enet_mtl_config_struct *)p_struct)->TxqAlgo = WEIGHTED_ROUND_ROBIN;
        ((enet_mtl_config_struct *)p_struct)->Txqthreshold = TX_THRESHOLD_32BYTES;
        ((enet_mtl_config_struct *)p_struct)->Txqforwardmode = TX_MODE_STOREFORWARD;
        ((enet_mtl_config_struct *)p_struct)->Txweight = 0x1U;
        ((enet_mtl_config_struct *)p_struct)->Txprioritysel = 0;
        ((enet_mtl_config_struct *)p_struct)->Txqmode = QUE_OP_MODE_ENABLE;
        ((enet_mtl_config_struct *)p_struct)->RxqAlgo = WEIGHTED_STRICT_PRIORITY;
        ((enet_mtl_config_struct *)p_struct)->Rxqthreshold = RX_THRESHOLD_32BYTES;
        ((enet_mtl_config_struct *)p_struct)->Rxqforwardmode = RX_MODE_STOREFORWARD;
        ((enet_mtl_config_struct *)p_struct)->Rxweight = 1;
        ((enet_mtl_config_struct *)p_struct)->Rxprioritysel = 0;
        ((enet_mtl_config_struct *)p_struct)->Rxqmode = QUE_OP_MODE_ENABLE;
        ((enet_mtl_config_struct *)p_struct)->dmachsel = DMACH0;
        break;
    case ENET_MTL1_INIT_STRUCT:
        ((enet_mtl_config_struct *)p_struct)->TxqAlgo = WEIGHTED_ROUND_ROBIN;
        ((enet_mtl_config_struct *)p_struct)->Txqthreshold = TX_THRESHOLD_32BYTES;
        ((enet_mtl_config_struct *)p_struct)->Txqforwardmode = TX_MODE_STOREFORWARD;
        ((enet_mtl_config_struct *)p_struct)->Txweight = 0x1U;
        ((enet_mtl_config_struct *)p_struct)->Txprioritysel = 0;
        ((enet_mtl_config_struct *)p_struct)->Txqmode = QUE_OP_MODE_ENABLE;
        ((enet_mtl_config_struct *)p_struct)->RxqAlgo = WEIGHTED_STRICT_PRIORITY;
        ((enet_mtl_config_struct *)p_struct)->Rxqthreshold = RX_THRESHOLD_32BYTES;
        ((enet_mtl_config_struct *)p_struct)->Rxqforwardmode = RX_MODE_STOREFORWARD;
        ((enet_mtl_config_struct *)p_struct)->Rxweight = 1;
        ((enet_mtl_config_struct *)p_struct)->Rxprioritysel = 0;
        ((enet_mtl_config_struct *)p_struct)->Rxqmode = QUE_OP_MODE_ENABLE;
        ((enet_mtl_config_struct *)p_struct)->dmachsel = DMACH1;
        break;
    case ENET_DMA_CH0_INIT_STRUCT:
        ((enet_dma_config_struct *)p_struct)->interruptmode = INT_MODE0;
        ((enet_dma_config_struct *)p_struct)->addrbeats = 1;
        ((enet_dma_config_struct *)p_struct)->burstlength = 64;
        ((enet_dma_config_struct *)p_struct)->bufsize = ENET_RXBUF_SIZE;
        ((enet_dma_config_struct *)p_struct)->priorityratio = ARBITRATION_RXTX_1_1;
        ((enet_dma_config_struct *)p_struct)->DmaTxAlgo = FIXED_PRIORITY_DMA_TX;
        ((enet_dma_config_struct *)p_struct)->DmaScheme = FIXED_PRIORITY_DMA_SCHEME;
        break;
    case ENET_DMA_CH1_INIT_STRUCT:
        ((enet_dma_config_struct *)p_struct)->interruptmode = INT_MODE0;
        ((enet_dma_config_struct *)p_struct)->addrbeats = 1;
        ((enet_dma_config_struct *)p_struct)->burstlength = 32;
        ((enet_dma_config_struct *)p_struct)->bufsize = ENET_RXBUF_SIZE;
        ((enet_dma_config_struct *)p_struct)->priorityratio = ARBITRATION_RXTX_1_1;
        ((enet_dma_config_struct *)p_struct)->DmaTxAlgo = FIXED_PRIORITY_DMA_TX;
        ((enet_dma_config_struct *)p_struct)->DmaScheme = FIXED_PRIORITY_DMA_SCHEME;
        break;
    case ENET_MAC_INIT_STRUCT:                             
        ((enet_mac_config_struct *)p_struct)->Speedstatus = MAC_LAYER_SPEED_100M;
        ((enet_mac_config_struct *)p_struct)->Duplexstatus = ENET_FULL_DUPLEX;
        ((enet_mac_config_struct *)p_struct)->MacConfig = ENET_TYPEPACKET_CRC_STRIP_DISABLE | ENET_AUTO_PADCRC_STRIP_DISABLE | ENET_WATCHDOG_ENABLE \
                | ENET_JABBER_ENABLE | ENET_JUMBO_PACKET_ENABLE | ENET_LOOPBACKMODE_DISABLE | ENET_ARP_OFFLOAD_ENABLE\
                | ENET_CARRIERSENSE_DISABLE | ENET_RECEIVEOWN_DISABLE | ENET_FULLDUPLEX_CARRIERSENSE_ENABLE \
                | ENET_RETRYTRANSMISSION_ENABLE | ENET_DEFERRALCHECK_DISABLE | ENET_BACKOFFLIMIT_10 | ENET_PREAMBLE_LENGTH_7BYTE \
                | ENET_2KMAX_PACKET_DISABLE | ENET_GIANT_PACKET_LIMIT_DISABLE | ENET_CHECKSUMOFFLOAD_DISABLE \
                | ENET_INTERPACKETGAP_96BIT;
        ((enet_mac_config_struct *)p_struct)->FilterConfig = ENET_L3L4_FILTER_DISABLE \
                | ENET_CONTROL_PACKET_PREVENT_PAUSEFRAME | ENET_RECEIVE_ALL_DISABLE | ENET_DROP_NONTCPUDP_DISABLE \
                | ENET_BROADCASTFRAMES_ENABLE | ENET_MULTICAST_FILTER_PASS | ENET_DEST_FILTER_INVERSE_DISABLE \
                | ENET_PROMISCUOUS_DISABLE | ENET_VLAN_FILTER_DISABLE;
        ((enet_mac_config_struct *)p_struct)->Txqflowctrl = MAC_Q0_TX_FLOW_CTRL_PT(0) | ENET_ZERO_QUANTA_PAUSE_DISABLE \
                | ENET_PAUSETIME_MINUS4 | ENET_TX_FLOWCONTROL_DISABLE | ENET_BACK_PRESSURE_DISABLE;
        break;
    case ENET_TXQ1_CBS_INIT_STRUCT:
        ((enet_cbs_config_struct *)p_struct)->IdleSlopeCredit = 0;
        ((enet_cbs_config_struct *)p_struct)->SendSlopeCredit = 0;
        ((enet_cbs_config_struct *)p_struct)->loCredit = 0;
        ((enet_cbs_config_struct *)p_struct)->HiCredit = 0;
        ((enet_cbs_config_struct *)p_struct)->CreditControl = DISABLE;
        break;
    case ENET_PHY_CFG_INIT_STRUCT:
        ((enet_phyconfig_struct *)p_struct)->PhyAddr = 0;
        ((enet_phyconfig_struct *)p_struct)->RegAddr = 0;
        ((enet_phyconfig_struct *)p_struct)->DevAddr = 0;
        ((enet_phyconfig_struct *)p_struct)->PhyValue = 0;
        break;
    case ENET_EST_CFG_INIT_STRUCT:
        ((enet_ESTConfig_struct *)p_struct)->BTRinsecond = 0;
        ((enet_ESTConfig_struct *)p_struct)->BTRinnanosecond = 0;
        ((enet_ESTConfig_struct *)p_struct)->CTRinsecond = 0;
        ((enet_ESTConfig_struct *)p_struct)->CTRinnanosecond = 0;
        ((enet_ESTConfig_struct *)p_struct)->TERtime = 0;
        ((enet_ESTConfig_struct *)p_struct)->LLRdepth = 0;
        break;
     case ENET_GCL_CFG_INIT_STRUCT:
        ((enet_GCLConfig_struct *)p_struct)->Ctrlconfig = 0;
        ((enet_GCLConfig_struct *)p_struct)->Ethtimeinterval = 0;
        break;
    case ENET_FPE_CFG_INIT_STRUCT:
        ((enet_FPEConfig_struct *)p_struct)->FPEenable = DISABLE;
        ((enet_FPEConfig_struct *)p_struct)->Relasetime = 0;
        ((enet_FPEConfig_struct *)p_struct)->Holdtime = 0;
        break;
    default:
        break;
    }
}
}

/*!
    \brief      initialize ENET MAC
    \param[in]  Config: pointer to a enet_mac_config_struct structure which contains
                parameters of MAC config
                members of the structure and the member values are shown as below:
                  Speedstatus: MAC_LAYER_SPEED_10M / MAC_LAYER_SPEED_100M
                  Duplexstatus: ENET_HALF_DUPLEX / ENET_FULL_DUPLEX
                  MacConfig: MAC related config information
                      -  ENET_ARP_OFFLOAD_ENABLE/ ENET_ARP_OFFLOAD_DISABLE
                      -  ENET_SARC_INTERNAL_SIGNAL/ ENET_SARC_ADDR0_INSERT/
                         ENET_SARC_ADDR0_REPLACE/ ENET_SARC_ADDR1_INSERT/ 
                         ENET_SARC_ADDR1_REPLACE;
                      -  ENET_CHECKSUMOFFLOAD_ENABLE / ENET_CHECKSUMOFFLOAD_DISABLE
                      -  ENET_INTERPACKETGAP_96BIT/ ENET_INTERPACKETGAP_88BIT/
                         ENET_INTERPACKETGAP_80BIT/ ENET_INTERPACKETGAP_72BIT/
                         ENET_INTERPACKETGAP_64BIT/ ENET_INTERPACKETGAP_56BIT/
                         ENET_INTERPACKETGAP_48BIT/ ENET_INTERPACKETGAP_40BIT
                      -  ENET_GIANT_PACKET_LIMIT_ENABLE/ ENET_GIANT_PACKET_LIMIT_DISABLE
                      -  ENET_2KMAX_PACKET_ENABLE/ ENET_2KMAX_PACKET_DISABLE
                      -  ENET_TYPEPACKET_CRC_STRIP_ENABLE/ ENET_TYPEPACKET_CRC_STRIP_DISABLE
                      -  ENET_AUTO_PADCRC_STRIP_ENABLE/ ENET_AUTO_PADCRC_STRIP_DISABLE
                      -  ENET_WATCHDOG_ENABLE/ ENET_WATCHDOG_DISABLE
                      -  ENET_JABBER_ENABLE/ ENET_JABBER_DISABLE
                      -  ENET_JUMBO_PACKET_ENABLE/ ENET_JUMBO_PACKET_DISABLE ;
                      -  ENET_FULLDUPLEX_CARRIERSENSE_ENABLE/ ENET_FULLDUPLEX_CARRIERSENSE_DISABLE
                      -  ENET_RECEIVEOWN_ENABLE/ ENET_RECEIVEOWN_DISABLE ;
                      -  ENET_CARRIERSENSE_ENABLE/ ENET_CARRIERSENSE_DISABLE
                      -  ENET_RETRYTRANSMISSION_ENABLE/ ENET_RETRYTRANSMISSION_DISABLE
                      -  ENET_BACKOFFLIMIT_10/ ENET_BACKOFFLIMIT_8/
                         ENET_BACKOFFLIMIT_4/ ENET_BACKOFFLIMIT_1 ;
                      -  ENET_DEFERRALCHECK_ENABLE/ ENET_DEFERRALCHECK_DISABLE
                      -  ENET_PREAMBLE_LENGTH_7BYTE/ ENET_PREAMBLE_LENGTH_5BYTE/
                         ENET_PREAMBLE_LENGTH_3BYTE;
                  FilterConfig: MAC filter related config information
                      -  ENET_PROMISCUOUS_ENABLE / ENET_PROMISCUOUS_DISABLE
                      -  ENET_RECEIVE_ALL_ENABLE / ENET_RECEIVE_ALL_DISABLE
                      -  ENET_BROADCASTFRAMES_ENABLE / ENET_BROADCASTFRAMES_DISABLE
                      -  ENET_SRC_FILTER_NORMAL_ENABLE/ ENET_SRC_FILTER_INVERSE_ENABLE/
                         ENET_SRC_FILTER_DISABLE ;
                      -  ENET_DEST_FILTER_INVERSE_ENABLE/ ENET_DEST_FILTER_INVERSE_DISABLE ;
                      -  ENET_MULTICAST_FILTER_HASH_OR_PERFECT/ ENET_MULTICAST_FILTER_HASH/
                         ENET_MULTICAST_FILTER_PERFECT/ ENET_MULTICAST_FILTER_NONE/
                         ENET_MULTICAST_FILTER_PASS;
                      -  ENET_DROP_NONTCPUDP_ENABLE/ENET_DROP_NONTCPUDP_DISABLE;
                      -  ENET_VLAN_FILTER_ENABLE/ENET_VLAN_FILTER_DISABLE;
                      -  ENET_L3L4_FILTER_ENABLE/ENET_L3L4_FILTER_DISABLE;
                      -  ENET_UNICAST_FILTER_EITHER/ ENET_UNICAST_FILTER_HASH/
                         ENET_UNICAST_FILTER_PERFECT ;
                      -  ENET_PCF_PREVENT_ALL/ ENET_PCF_PREVENT_PAUSEFRAME/
                         ENET_PCF_FORWARD_ALL/ ENET_PCF_FORWARD_FILTERED .
                  Txqflowctrl: TXQ0 flow control related config information
                      -  MAC_Q0_TX_FLOW_CTRL_PT(regval) ;
                      -  ENET_ZERO_QUANTA_PAUSE_ENABLE/ ENET_ZERO_QUANTA_PAUSE_DISABLE ;
                         ENET_PAUSETIME_MINUS4/ ENET_PAUSETIME_MINUS28/
                         ENET_PAUSETIME_MINUS36/ ENET_PAUSETIME_MINUS144/
                         ENET_PAUSETIME_MINUS256/ENET_PAUSETIME_MINUS256_2 ;
                      -  ENET_MAC0_AND_UNIQUE_ADDRESS_PAUSEDETECT/ ENET_UNIQUE_PAUSEDETECT ;
                      -  ENET_RX_FLOWCONTROL_ENABLE/ ENET_RX_FLOWCONTROL_DISABLE ;
                      -  ENET_TX_FLOWCONTROL_ENABLE/ ENET_TX_FLOWCONTROL_DISABLE ;
                      -  ENET_RXQ0_HARDWARE_FLOW_CONTROL_ENABLE/ ENET_RXQ0_HARDWARE_FLOW_CONTROL_DISABLE ;
                      -  ENET_RXQ1_HARDWARE_FLOW_CONTROL_ENABLE/ ENET_RXQ1_HARDWARE_FLOW_CONTROL_DISABLE ;
    \param[out] none
    \retval     none
*/
void enet_mac_init(enet_mac_config_struct *Config)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
   if(NOT_VALID_POINTER(Config)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
     {
    ENET_MAC_Q0_TX_FLOW_CTRL = Config->Txqflowctrl;

    /* Set MAC packet filter. */
    ENET_MAC_PACKET_FILTER = Config->FilterConfig;

    ENET_MAC_CONFIGURATION = Config->MacConfig | MAC_CONFIGURATION_FES(Config->Speedstatus) | MAC_CONFIGURATION_DM(Config->Duplexstatus);
    
    /* MMC */
    /* disable MMC Rx interrupt */
    ENET_MMC_RX_INTERRUPT_MASK |= MMC_INTERRUPT_MASK_VALUE;

    /* disable MMC Tx interrupt */
    ENET_MMC_TX_INTERRUPT_MASK |= MMC_INTERRUPT_MASK_VALUE;
    
    /* disable MMC FPE Tx interrupt */
    ENET_MMC_FPE_TX_INTERRUPT_MASK |= (ENET_MMC_FPE_TX_INTERRUPT_MASK_HRCIM | ENET_MMC_FPE_TX_INTERRUPT_MASK_FCIM);
    
    /* disable MMC FPE Rx interrupt */
    ENET_MMC_FPE_RX_INTERRUPT_MASK |= (ENET_MMC_FPE_RX_INTERRUPT_MASK_FCIM | ENET_MMC_FPE_RX_INTERRUPT_MASK_PAOCIM \
                                       | ENET_MMC_FPE_RX_INTERRUPT_MASK_PSECIM | ENET_MMC_FPE_RX_INTERRUPT_MASK_PAECIM);
    
    /* disable MMC IPC Rx interrupt */
    ENET_MMC_IPC_RX_INTERRUPT_MASK |= MMC_IPC_INTERRUPT_MASK_VALUE;

}
}

/*!
    \brief      initialize ENET DMA
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  Config: pointer to a enet_dma_config_struct structure which contains
                parameters of DMA config
                members of the structure and the member values are shown as below:
                  interruptmode: DMA interrupt mode
                  burstlength: the burst length,must be 1,2,4,8,16,32,64,128,256
                  bufsize: the buffer size
                  priorityratio: ARBITRATION_RXTX_1_1 / ARBITRATION_RXTX_2_1 / ARBITRATION_RXTX_3_1 \
                                 / ARBITRATION_RXTX_4_1 / ARBITRATION_RXTX_5_1 / ARBITRATION_RXTX_6_1 \
                                 / ARBITRATION_RXTX_7_1 / ARBITRATION_RXTX_8_1 / ARBITRATION_TXRX_1_1 \
                                 / ARBITRATION_TXRX_2_1 / ARBITRATION_TXRX_3_1 / ARBITRATION_TXRX_4_1 \
                                 / ARBITRATION_TXRX_5_1 / ARBITRATION_TXRX_6_1 / ARBITRATION_TXRX_7_1 \
                                 / ARBITRATION_TXRX_8_1
                  DmaTxAlgo: FIXED_PRIORITY_DMA_TX / WEIGHTED_STRICT_PRIORITY_DMA_TX / WEIGHTED_ROUND_ROBIN_DMA_TX;
                  DmaScheme: FIXED_PRIORITY_DMA_SCHEME / WEIGHTED_ROUND_ROBIN_DMA_SCHEME;
    \param[out] none
    \retval     none
*/
void enet_dma_init(enet_dmach_enum dmach,
                        enet_dma_config_struct *Config)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
   if(NOT_VALID_POINTER(Config)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0005U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
        /* Initialize the global DMA registers. */
        ENET_DMA_MODE = ((uint32_t)Config->interruptmode) | ((uint32_t)Config->priorityratio) | ((uint32_t)Config->DmaScheme) | ((uint32_t)Config->DmaTxAlgo);

        ENET_DMA_SYSBUS_MODE = DMA_SYSBUS_MODE_AAL(Config->addrbeats) | ENET_DMA_SYSBUS_MODE_FB;
        switch(dmach) {
        case DMACH0:
            if(32U < Config->burstlength) {
                ENET_DMA_CH0_CONTROL = DMA_CH_CONTROL_DSL(1) | ENET_DMA_CH_CONTROL_PBLx8;
                Config->burstlength = (uint32_t)(Config->burstlength / 8U);
            } else {
                ENET_DMA_CH0_CONTROL = DMA_CH_CONTROL_DSL(1);
            }
#ifdef DMACH0_USE_ENHANCED_MODE
            enet_desc_select_enhanced_mode(DMACH0);
#else
            enet_desc_select_normal_mode(DMACH0);
#endif /* DMACH0_USE_ENHANCED_MODE */
            ENET_DMA_CH0_TX_CONTROL |= (DMA_CH_TX_CONTROL_TxPBL((uint32_t)Config->burstlength) << 8);


            ENET_DMA_CH0_RX_CONTROL = DMA_CH_RX_CONTROL_RxPBL((uint32_t)Config->burstlength) | DMA_CH_RX_CONTROL_RBSZ(((
                                          uint32_t)Config->bufsize));
            break;
        case DMACH1:
            /* Initialize the global DMA registers. */
            if(32U < Config->burstlength) {
                ENET_DMA_CH1_CONTROL = DMA_CH_CONTROL_DSL(1) | ENET_DMA_CH_CONTROL_PBLx8;
            } else {
                ENET_DMA_CH1_CONTROL = DMA_CH_CONTROL_DSL(1);
            }
#ifdef DMACH1_USE_ENHANCED_MODE
            enet_desc_select_enhanced_mode(DMACH1);
#else
            enet_desc_select_normal_mode(DMACH1);
#endif /* DMACH0_USE_ENHANCED_MODE */
            ENET_DMA_CH1_TX_CONTROL |= DMA_CH_TX_CONTROL_TxPBL((uint32_t)Config->burstlength);

            ENET_DMA_CH1_RX_CONTROL = DMA_CH_RX_CONTROL_RxPBL((uint32_t)Config->burstlength) | DMA_CH_RX_CONTROL_RBSZ(((
                                          uint32_t)Config->bufsize));
            break;

        default:
            break;
        }
}
}

/*!
    \brief      initialize ENET MTL
    \param[in]  Instance: choose the MTL process which users want to check, refer to enet_mtl_enum
                only one parameter can be selected which is shown as below
      \arg        MTL0: MTL channel 0
      \arg        MTL1: MTL channel 1
    \param[in]  Config: pointer to a enet_mtl_config_struct structure which contains
                parameters of MTL config
                members of the structure and the member values are shown as below:
                  TxqAlgo: STRICT_PRIORITY_TX / WEIGHTED_ROUND_ROBIN
                  Txqthreshold: TX_THRESHOLD_32BYTES / TX_THRESHOLD_64BYTES / TX_THRESHOLD_96BYTES \
                                 /TX_THRESHOLD_128BYTES / TX_THRESHOLD_192BYTES / TX_THRESHOLD_256BYTES \
                                 / TX_THRESHOLD_284BYTES / TX_THRESHOLD_512BYTES
                  Txqforwardmode: TX_MODE_CUTTHROUGH / TX_MODE_STOREFORWARD
                  Txweight: the weight of transmit queue
                  Txprioritysel: the priority of transmit queue
                  Txqmode: QUE_OP_MODE_DISABLE / QUE_OP_MODE_AVB_ENABLE /QUE_OP_MODE_ENABLE
                  RxqAlgo: STRICT_PRIORITY_RX / WEIGHTED_STRICT_PRIORITY
                  Rxqthreshold: RX_THRESHOLD_32BYTES / RX_THRESHOLD_64BYTES / RX_THRESHOLD_96BYTES / RX_THRESHOLD_128BYTES
                  Rxqforwardmode: RX_MODE_CUTTHROUGH / RX_MODE_STOREFORWARD
                  Rxweight: the weight of receive queue
                  Rxprioritysel: the priority of receive queue
                  Rxqmode: QUE_OP_MODE_DISABLE / QUE_OP_MODE_AVB_ENABLE /QUE_OP_MODE_ENABLE
                  dmachsel: DMACH0 / DMACH1
    \param[out] none
    \retval     none
*/
void enet_mtl_init(enet_mtl_enum Instance, enet_mtl_config_struct *Config)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
   if(NOT_VALID_POINTER(Config)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0006U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(Instance) {
    case MTL0: 
        /* Set the global Tx Scheduling Algorithm affecting Tx Queues 0 */
        ENET_MTL_OPERATION_MODE = (uint32_t)(Config->TxqAlgo);
        if(Config->TxqAlgo == WEIGHTED_ROUND_ROBIN) {
            enet_txq_weight_set(TXQ0, Config->Txweight);
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        ENET_MTL_TXQ0_OPERATION_MODE = MTL_TXQ_OPERATION_MODE_TSF((uint32_t)(Config->Txqforwardmode)) | MTL_TXQ_OPERATION_MODE_TTC((uint32_t)(
                                           Config->Txqthreshold));
        enet_txq_mode_size_set(TXQ0, Config->Txqmode, MTL_TX_FIFO_SIZE);


        enet_rxq_weight_set(RXQ0, Config->Rxweight);
        ENET_MTL_OPERATION_MODE |= (uint32_t)(Config->RxqAlgo);
        ENET_MTL_RXQ0_OPERATION_MODE = MTL_RXQ_OPERATION_MODE_RSF((uint32_t)(Config->Rxqforwardmode)) | MTL_RXQ_OPERATION_MODE_RTC((uint32_t)(
                                           Config->Rxqthreshold));
        enet_rxq_dma_select(RXQ0, DMACH0);
        enet_rxq_size_set(RXQ0, MTL_RX_FIFO_SIZE);
        enet_rxq_mode_set(RXQ0, Config->Rxqmode, (uint8_t)Config->Rxprioritysel);
        break;
    case MTL1: 
        /* Set the global Tx Scheduling Algorithm affecting Tx Queues 1*/
        ENET_MTL_OPERATION_MODE = (uint32_t)(Config->TxqAlgo);
        if(Config->TxqAlgo == WEIGHTED_ROUND_ROBIN) {
            enet_txq_weight_set(TXQ1, Config->Txweight);
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        ENET_MTL_TXQ1_OPERATION_MODE = MTL_TXQ_OPERATION_MODE_TSF((uint32_t)(Config->Txqforwardmode)) | MTL_TXQ_OPERATION_MODE_TTC((uint32_t)(
                                           Config->Txqthreshold));
        /* Enable the Tx Queue in the given mode and set its size  */
        enet_txq_mode_size_set(TXQ1, Config->Txqmode, MTL_TX_FIFO_SIZE);

        enet_rxq_weight_set(RXQ1, Config->Rxweight);
        ENET_MTL_OPERATION_MODE |= (uint32_t)(Config->RxqAlgo);
        ENET_MTL_RXQ1_OPERATION_MODE = MTL_RXQ_OPERATION_MODE_RSF((uint32_t)(Config->Rxqforwardmode)) | MTL_RXQ_OPERATION_MODE_RTC((uint32_t)(
                                           Config->Rxqthreshold));
        /* Set 1:1 mapping between Rx Queues and Rx DMA Channels */
        enet_rxq_dma_select(RXQ1, DMACH1);
        /* Set the size of the Rx Queue */
        enet_rxq_size_set(RXQ1, MTL_RX_FIFO_SIZE);
        enet_rxq_mode_set(RXQ1, Config->Rxqmode, (uint8_t)Config->Rxprioritysel);
        break;
    default: 
        break;
    }
    }
}

/*!
    \brief      initialize ENET peripheral with generally concerned parameters and the less cared
                parameters
    \param[in]  mediamode: PHY mode and mac loopback configurations, only one parameter can be selected
                           which is shown as below, refer to enet_mediamode_enum
      \arg        ENET_AUTO_NEGOTIATION: PHY auto negotiation
      \arg        ENET_100M_FULLDUPLEX: 100Mbit/s, full-duplex
      \arg        ENET_100M_HALFDUPLEX: 100Mbit/s, half-duplex
      \arg        ENET_10M_FULLDUPLEX: 10Mbit/s, full-duplex
      \arg        ENET_10M_HALFDUPLEX: 10Mbit/s, half-duplex
      \arg        ENET_LOOPBACKMODE: MAC in loopback mode
    \param[in]  checksum: IP frame checksum offload function, only one parameter can be selected
                          which is shown as below, refer to enet_chksumconf_enum
      \arg        ENET_NO_AUTOCHECKSUM: disable IP frame checksum function
      \arg        ENET_AUTOCHECKSUM_DROP_FAILFRAMES: enable IP frame checksum function
      \arg        ENET_AUTOCHECKSUM_ACCEPT_FAILFRAMES: enable IP frame checksum function, and the received frame
                                                       with only payload error but no other errors will not be dropped
    \param[in]  recept: frame filter function, only one parameter can be selected
                          which is shown as below, refer to enet_frmrecept_enum
      \arg        ENET_PROMISCUOUS_MODE: promiscuous mode enabled
      \arg        ENET_RECEIVEALL: all received frame are forwarded to application
      \arg        ENET_BROADCAST_FRAMES_PASS: the address filters pass all received broadcast frames
      \arg        ENET_BROADCAST_FRAMES_DROP: the address filters filter all incoming broadcast frames
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus enet_init(enet_mediamode_enum mediamode, enet_chksumconf_enum checksum, enet_frmrecept_enum recept)
{
    uint32_t reg_value, reg_temp, temp;
    uint32_t media_temp;
    uint32_t timeout = 0U;
    uint32_t optimeout = ENET_OPERATION_TIMEROUT;
    ErrStatus phy_state, enet_state = ERROR;
    enet_phyconfig_struct phy_config = {PHY_ADDRESS, PHY_REG_BSR, 0, 0};

    /* PHY interface configuration, configure SMI clock and reset PHY chip */
    if(ERROR == enet_phy_config()) {
        ENET_DELAY(PHY_RESETDELAY);
        if(ERROR == enet_phy_config()) {
            return enet_state;
        }
    }

    /* 1st, configure mediamode */
    media_temp = (uint32_t)mediamode;
    /* if is PHY auto negotiation */
    if((uint32_t)ENET_AUTO_NEGOTIATION == media_temp) {
        /* wait for PHY_LINKED_STATUS bit be set */
        do {
            phy_state = enet_phy_write_read(&phy_config, ENET_PHY_READ, DISABLE);
            phy_config.PhyValue &= PHY_LINKED_STATUS;
            timeout++;
        } while(((uint16_t)RESET == phy_config.PhyValue) && (timeout < PHY_READ_TO));
        /* return ERROR due to timeout */
        if(PHY_READ_TO == timeout) {
            return enet_state;
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        
        if(SUCCESS != phy_state) {
            /* return ERROR due to write timeout */
            return enet_state;
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        /* reset timeout counter */
        timeout = 0U;

        /* enable auto-negotiation */
        phy_config.PhyValue = PHY_AUTONEGOTIATION;
        phy_config.RegAddr = PHY_REG_BCR;
        phy_state = enet_phy_write_read(&phy_config, ENET_PHY_WRITE, DISABLE);
        if(SUCCESS != phy_state) {
            /* return ERROR due to write timeout */
            return enet_state;
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        phy_config.RegAddr = PHY_REG_BSR;
        /* wait for the PHY_AUTONEGO_COMPLETE bit be set */
        do {
            phy_state = enet_phy_write_read(&phy_config, ENET_PHY_READ, DISABLE);
            phy_config.PhyValue &= PHY_AUTONEGO_COMPLETE;
            timeout++;
        } while(((uint16_t)RESET == phy_config.PhyValue) && (timeout < (uint32_t)PHY_READ_TO));
        /* return ERROR due to timeout */
        if(PHY_READ_TO == timeout) {
            return enet_state;
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        if(SUCCESS != phy_state) {
            /* return ERROR due to write timeout */
            return enet_state;
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        phy_config.RegAddr = PHY_SR;
        /* read the result of the auto-negotiation */
        phy_state = enet_phy_write_read(&phy_config, ENET_PHY_READ, DISABLE);
        if(SUCCESS != phy_state) {
            /* return ERROR due to write timeout */
            return enet_state;
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        /* configure the duplex mode of MAC following the auto-negotiation result */
        if((uint16_t)RESET != (phy_config.PhyValue & PHY_DUPLEX_STATUS)) {
            media_temp = ENET_MODE_FULLDUPLEX;
        } else {
            media_temp = ENET_MODE_HALFDUPLEX;
        }
#if(PHY_TYPE == YT8512)
        /* configure the communication speed of MAC following the auto-negotiation result */
        if((uint16_t)RESET != (phy_config.PhyValue & PHY_SPEED_STATUS)) {
            media_temp |= ENET_SPEEDMODE_100M;
        } else {
            media_temp |= ENET_SPEEDMODE_10M;
        }
#else
        /* configure the communication speed of MAC following the auto-negotiation result */
        if((uint16_t)RESET != (phy_config.PhyValue & PHY_SPEED_STATUS)) {
            media_temp |= ENET_SPEEDMODE_10M;
        } else {
            media_temp |= ENET_SPEEDMODE_100M;
        }
#endif /* PHY_TYPE == YT8512 */
    } else {
        phy_config.PhyValue = (uint16_t)((media_temp & ENET_MAC_CONFIGURATION_DM) >> 3U);
        phy_config.PhyValue |= (uint16_t)((media_temp & ENET_MAC_CONFIGURATION_FES) >> 1U);
        phy_state = enet_phy_write_read(&phy_config, ENET_PHY_WRITE, DISABLE);
        if(SUCCESS != phy_state) {
            /* return ERROR due to write timeout */
            return enet_state;
        } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
        /* PHY configuration need some time */
        ENET_DELAY(PHY_CONFIGDELAY);
    }
    /* after configuring the PHY, use mediamode to configure registers */
    reg_value = ENET_MAC_CONFIGURATION;
    /* configure ENET_MAC_CFG register */
    reg_value &= (~(ENET_MAC_CONFIGURATION_FES | ENET_MAC_CONFIGURATION_DM | ENET_MAC_CONFIGURATION_LM));
    reg_value |= media_temp;
    ENET_MAC_CONFIGURATION = reg_value;

    /* 2st, configure checksum */
    if((uint32_t)RESET != ((uint32_t)checksum & ENET_CHECKSUMOFFLOAD_ENABLE)) {
        ENET_MAC_CONFIGURATION |= ENET_CHECKSUMOFFLOAD_ENABLE;

        reg_value = ENET_MTL_RXQ0_OPERATION_MODE;
        /* configure ENET_MTL_RXQ0_OPERATION_MODE register */
        reg_value &= ~ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF;
        reg_value |= ((uint32_t)checksum & ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF);
        ENET_MTL_RXQ0_OPERATION_MODE = reg_value;

        reg_value = ENET_MTL_RXQ1_OPERATION_MODE;
        /* configure ENET_MTL_RXQ1_OPERATION_MODE register */
        reg_value &= ~ENET_MTL_RXQ1_OPERATION_MODE_DIS_TCP_EF;
        reg_value |= ((uint32_t)checksum & ENET_MTL_RXQ1_OPERATION_MODE_DIS_TCP_EF);
        ENET_MTL_RXQ1_OPERATION_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* 3rd, configure recept */
    ENET_MAC_PACKET_FILTER |= (uint32_t)recept;

    /* 4th, configure different function options */
    /* configure forward_frame related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)FORWARD_OPTION)) {
        reg_temp = enet_initpara.forward_frame;

        reg_value = ENET_MAC_CONFIGURATION;
        temp = reg_temp;
        /* configure ENET_MAC_CONFIGURATION register */
        reg_value &= (~(ENET_MAC_CONFIGURATION_CST | ENET_MAC_CONFIGURATION_ACS));
        temp &= (ENET_MAC_CONFIGURATION_CST | ENET_MAC_CONFIGURATION_ACS);
        reg_value |= temp;
        ENET_MAC_CONFIGURATION = reg_value;

        reg_value = ENET_MTL_RXQ0_OPERATION_MODE;
        temp = reg_temp;
        /* configure ENET_MTL_RXQ0_OPERATION_MODE register */
        reg_value &= (~(ENET_MTL_RXQ0_OPERATION_MODE_FEP | ENET_MTL_RXQ0_OPERATION_MODE_FUP));
        temp &= ((ENET_MTL_RXQ0_OPERATION_MODE_FEP | ENET_MTL_RXQ0_OPERATION_MODE_FUP) << 2U);
        reg_value |= (temp >> 2U);
        ENET_MTL_RXQ0_OPERATION_MODE = reg_value;

        reg_value = ENET_MTL_RXQ1_OPERATION_MODE;
        temp = reg_temp;
        /* configure ENET_MTL_RXQ1_OPERATION_MODE register */
        reg_value &= (~(ENET_MTL_RXQ1_OPERATION_MODE_FEP | ENET_MTL_RXQ1_OPERATION_MODE_FUP));
        temp &= (ENET_MTL_RXQ1_OPERATION_MODE_FEP | ENET_MTL_RXQ1_OPERATION_MODE_FUP);
        reg_value |= temp;
        ENET_MTL_RXQ1_OPERATION_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure dmabus_mode related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)DMABUS_OPTION)) {
        temp = enet_initpara.dmabus_mode;

        reg_value = ENET_DMA_SYSBUS_MODE;
        /* configure ENET_DMA_SYSBUS_MODE register */
        reg_value &= ~(ENET_DMA_SYSBUS_MODE_AAL | ENET_DMA_SYSBUS_MODE_FB \
                       | ENET_DMA_SYSBUS_MODE_MB);
        reg_value |= temp;
        ENET_DMA_SYSBUS_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure dmach0_maxburst related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)DMACH0_MAXBURST_OPTION)) {
        reg_temp = enet_initpara.dmach0_maxburst;

        reg_value = ENET_DMA_CH0_RX_CONTROL;
        temp = reg_temp;
        /* configure ENET_DMA_CH0_RX_CONTROL register */
        reg_value &= ~ENET_DMA_CH_RX_CONTROL_RxPBL;
        temp &= ENET_DMA_CH_RX_CONTROL_RxPBL;
        reg_value |= temp;
        ENET_DMA_CH0_RX_CONTROL = reg_value;
    
        reg_value = ENET_DMA_CH0_TX_CONTROL;
        temp = reg_temp;
        /* configure ENET_DMA_CH0_TX_CONTROL register */
        reg_value &= ~ENET_DMA_CH_TX_CONTROL_TxPBL;
        temp &= (ENET_DMA_CH_TX_CONTROL_TxPBL >> 8);
        reg_value |= (temp << 8);
        ENET_DMA_CH0_TX_CONTROL = reg_value;
    
        reg_value = ENET_DMA_CH0_CONTROL;
        temp = reg_temp;
        /* configure ENET_DMA_CH0_CONTROL register */
        reg_value &= ~ENET_DMA_CH_CONTROL_PBLx8;
        temp &= (BIT(15) | BIT(23));
        if((uint32_t)SET == (temp & BIT(15)) || (uint32_t)SET == (temp & BIT(23))){
           reg_value |= ENET_DMA_CH_CONTROL_PBLx8;
        }
        ENET_DMA_CH0_CONTROL = reg_value;

    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure dmach1_maxburst related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)DMACH1_MAXBURST_OPTION)) {
        reg_temp = enet_initpara.dmach1_maxburst;

        reg_value = ENET_DMA_CH1_RX_CONTROL;
        temp = reg_temp;
        /* configure ENET_DMA_CH1_RX_CONTROL register */
        reg_value &= ~ENET_DMA_CH_RX_CONTROL_RxPBL;
        temp &= ENET_DMA_CH_RX_CONTROL_RxPBL;
        reg_value |= temp;
        ENET_DMA_CH1_RX_CONTROL = reg_value;
    
        reg_value = ENET_DMA_CH1_TX_CONTROL;
        temp = reg_temp;
        /* configure ENET_DMA_CH1_TX_CONTROL register */
        reg_value &= ~ENET_DMA_CH_TX_CONTROL_TxPBL;
        temp &= (ENET_DMA_CH_TX_CONTROL_TxPBL >> 8);
        reg_value |= (temp << 8);
        ENET_DMA_CH1_TX_CONTROL = reg_value;
    
        reg_value = ENET_DMA_CH1_CONTROL;
        temp = reg_temp;
        /* configure ENET_DMA_CH1_CONTROL register */
        reg_value &= ~ENET_DMA_CH_CONTROL_PBLx8;
        temp &= (BIT(15) | BIT(23));
        if((uint32_t)SET == (temp & BIT(15)) || (uint32_t)SET == (temp & BIT(23))){
           reg_value |= ENET_DMA_CH_CONTROL_PBLx8;
        }
        ENET_DMA_CH1_CONTROL = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    
    /* configure dma_arbitration related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)DMA_ARBITRATION_OPTION)) {
        temp = enet_initpara.dma_arbitration;

        reg_value = ENET_DMA_MODE;
        /* configure ENET_DMA_MODE register */
        reg_value &= ~(ENET_DMA_MODE_PR | ENET_DMA_MODE_TXPR);
        reg_value |= temp;
        ENET_DMA_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure store_forward_mode related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)TX0STORE_OPTION)) {
        temp = enet_initpara.tx0store_forward_mode;

        reg_value = ENET_MTL_TXQ0_OPERATION_MODE;
        /* configure ENET_MTL_TXQ0_OPERATION_MODE register */
        reg_value &= ~(ENET_MTL_TXQ0_OPERATION_MODE_TTC | ENET_MTL_TXQ0_OPERATION_MODE_TSF);
        reg_value |= temp;
        ENET_MTL_TXQ0_OPERATION_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    /* configure store_forward_mode related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)RX0STORE_OPTION)) {
        temp = enet_initpara.rx0store_forward_mode;

        reg_value = ENET_MTL_RXQ0_OPERATION_MODE;
        /* configure ENET_MTL_RXQ0_OPERATION_MODE register */
        reg_value &= ~(ENET_MTL_RXQ0_OPERATION_MODE_RTC | ENET_MTL_RXQ0_OPERATION_MODE_RSF);
        reg_value |= temp;
        ENET_MTL_RXQ0_OPERATION_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)TX1STORE_OPTION)) {
        temp = enet_initpara.tx1store_forward_mode;

        reg_value = ENET_MTL_TXQ1_OPERATION_MODE;
        /* configure ENET_MTL_TXQ1_OPERATION_MODE register */
        reg_value &= ~(ENET_MTL_TXQ1_OPERATION_MODE_TTC | ENET_MTL_TXQ1_OPERATION_MODE_TSF);
        reg_value |= temp;
        ENET_MTL_TXQ1_OPERATION_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    /* configure store_forward_mode related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)RX1STORE_OPTION)) {
        temp = enet_initpara.rx1store_forward_mode;

        reg_value = ENET_MTL_RXQ1_OPERATION_MODE;
        /* configure ENET_MTL_RXQ1_OPERATION_MODE register */
        reg_value &= ~(ENET_MTL_RXQ1_OPERATION_MODE_RTC | ENET_MTL_RXQ1_OPERATION_MODE_RSF);
        reg_value |= temp;
        ENET_MTL_RXQ1_OPERATION_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure vlan_config related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)VLAN_CONFIG_OPTION)) {
        reg_temp = enet_initpara.vlan_config;

        reg_value = ENET_MAC_VLAN_TAG_CTRL;
        /* configure ENET_MAC_VLT register */
        reg_value &= ~(ENET_MAC_VLAN_TAG_CTRL_EIVLRXS | ENET_MAC_VLAN_TAG_CTRL_EIVLS | ENET_MAC_VLAN_TAG_CTRL_ERIVLT | ENET_MAC_VLAN_TAG_CTRL_EDVLP |
                       ENET_MAC_VLAN_TAG_CTRL_VTHM | ENET_MAC_VLAN_TAG_CTRL_EVLRXS
                       | ENET_MAC_VLAN_TAG_CTRL_EVLS | ENET_MAC_VLAN_TAG_CTRL_DOVLTC | ENET_MAC_VLAN_TAG_CTRL_ERSVLM | ENET_MAC_VLAN_TAG_CTRL_ESVL |
                       ENET_MAC_VLAN_TAG_CTRL_VTIM | ENET_MAC_VLAN_TAG_CTRL_ETV);
        reg_value |= reg_temp;
        ENET_MAC_VLAN_TAG_CTRL = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    /* configure vlan_config related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)VLAN_COMPARISON_OPTION)) {
        reg_temp = enet_initpara.vlan_compare;
        temp = reg_temp;
        reg_value = ENET_MAC_VLAN_TAG_DATA;
        /* configure ENET_MAC_VLAN_TAG_DATA register */
        reg_value &= ~(ENET_MAC_VLAN_TAG_DATA_VID | ENET_MAC_VLAN_TAG_DATA_VEN | ENET_MAC_VLAN_TAG_DATA_ETV | ENET_MAC_VLAN_TAG_DATA_DOVLTC |
                       ENET_MAC_VLAN_TAG_DATA_ERSVLM | ENET_MAC_VLAN_TAG_DATA_ERIVLT);
        reg_value |= temp;
        ENET_MAC_VLAN_TAG_DATA = reg_value;
        
        reg_value = ENET_MAC_VLAN_TAG_CTRL;
        reg_value &= ~(ENET_MAC_VLAN_TAG_CTRL_OFS | ENET_MAC_VLAN_TAG_CTRL_CT);
        temp &= (ENET_MAC_VLAN_TAG_CTRL_OFS << 19);
        reg_value |= (temp >> 19);
        ENET_MAC_VLAN_TAG_CTRL = reg_value | ENET_MAC_VLAN_TAG_CTRL_OB;
        while(((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OB))&& ((uint32_t)RESET < optimeout)) {
           optimeout --;
        }
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    /* configure vlan_config related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)VLAN_INSERT_OPTION)) {
        reg_temp = enet_initpara.vlan_insert;

        reg_value = ENET_MAC_VLAN_INCL;
        /* configure ENET_MAC_VLAN_INCL register */
        reg_value &= ~(ENET_MAC_VLAN_INCL_VLTI | ENET_MAC_VLAN_INCL_CSVL | ENET_MAC_VLAN_INCL_VLP | ENET_MAC_VLAN_INCL_VLC);
        reg_value |= reg_temp;
        ENET_MAC_VLAN_INCL = reg_value;
    }
    /* configure vlan_config related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)INNERVLAN_INSERT_OPTION)) {
        reg_temp = enet_initpara.innervlan_insert;

        reg_value = ENET_MAC_INNER_VLAN_INCL;
        /* configure ENET_MAC_INNER_VLAN_INCL register */
        reg_value &= ~(ENET_MAC_INNER_VLAN_INCL_VLTI | ENET_MAC_INNER_VLAN_INCL_CSVL | ENET_MAC_INNER_VLAN_INCL_VLP |
                       ENET_MAC_INNER_VLAN_INCL_VLC); 
        reg_value |= reg_temp;
        ENET_MAC_INNER_VLAN_INCL = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    /* configure flow_control related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)FLOWCTL_OPTION)) {
        reg_temp = enet_initpara.flow_control;

        reg_value = ENET_MAC_Q0_TX_FLOW_CTRL;
        temp = reg_temp;
        /* configure MAC_Q0_TX_FLOW_CTRL register */
        reg_value &= ~(ENET_MAC_Q0_TX_FLOW_CTRL_PT | ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ | ENET_MAC_Q0_TX_FLOW_CTRL_PLT \
                       | ENET_MAC_Q0_TX_FLOW_CTRL_TFE | ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA);
        temp &= (ENET_MAC_Q0_TX_FLOW_CTRL_PT | ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ | ENET_MAC_Q0_TX_FLOW_CTRL_PLT \
                 | ENET_MAC_Q0_TX_FLOW_CTRL_TFE | ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA);
        reg_value |= temp;
        ENET_MAC_Q0_TX_FLOW_CTRL = reg_value;

        reg_value = ENET_MAC_RX_FLOW_CTRL;
        temp = reg_temp;
        /* configure MAC_RX_FLOW_CTRL register */
        reg_value &= ~(ENET_MAC_RX_FLOW_CTRL_UP | ENET_MAC_RX_FLOW_CTRL_RFE);
        temp &= ((ENET_MAC_RX_FLOW_CTRL_UP | ENET_MAC_RX_FLOW_CTRL_RFE) << 8);
        reg_value |= (temp >> 8);
        ENET_MAC_RX_FLOW_CTRL = reg_value;

        reg_value = ENET_MTL_RXQ0_OPERATION_MODE;
        temp = reg_temp;
        /* configure ENET_MTL_RXQ0_OPERATION_MODE register */
        reg_value &= ~ENET_MTL_RXQ0_OPERATION_MODE_EHFC;
        temp &= (ENET_MTL_RXQ0_OPERATION_MODE_EHFC << 3);
        reg_value |= (temp >> 3);
        ENET_MTL_RXQ0_OPERATION_MODE = reg_value;
        
        reg_value = ENET_MTL_RXQ1_OPERATION_MODE;
        temp = reg_temp;
        /* configure ENET_MTL_RXQ1_OPERATION_MODE register */
        reg_value &= ~ENET_MTL_RXQ1_OPERATION_MODE_EHFC;
        temp &= (ENET_MTL_RXQ1_OPERATION_MODE_EHFC << 4);
        reg_value |= (temp >> 4);
        ENET_MTL_RXQ1_OPERATION_MODE = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure hashtable_high related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)HASHH_OPTION)) {
        ENET_MAC_HASH_TABLE_REG0 = enet_initpara.hashtable_high;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure hashtable_low related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)HASHL_OPTION)) {
        ENET_MAC_HASH_TABLE_REG1 = enet_initpara.hashtable_low;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure framesfilter_mode related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)FILTER_OPTION)) {
        reg_temp = enet_initpara.framesfilter_mode;

        reg_value = ENET_MAC_PACKET_FILTER;
        /* configure ENET_MAC_PACKET_FILTER register */
        reg_value &= ~(ENET_MAC_PACKET_FILTER_DNTU | ENET_MAC_PACKET_FILTER_IPFE | ENET_MAC_PACKET_FILTER_VTFE \
                       | ENET_MAC_PACKET_FILTER_HPF | ENET_MAC_PACKET_FILTER_SAF | ENET_MAC_PACKET_FILTER_SAIF \
                       | ENET_MAC_PACKET_FILTER_PCF | ENET_MAC_PACKET_FILTER_DBF | ENET_MAC_PACKET_FILTER_PM \
                       | ENET_MAC_PACKET_FILTER_DAIF | ENET_MAC_PACKET_FILTER_HMC | ENET_MAC_PACKET_FILTER_HUC);
        reg_value |= reg_temp;
        ENET_MAC_PACKET_FILTER = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure halfduplex_param related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)HALFDUPLEX_OPTION)) {
        reg_temp = enet_initpara.halfduplex_param;

        reg_value = ENET_MAC_CONFIGURATION;
        /* configure ENET_MAC_CONFIGURATION register */
        reg_value &= ~(ENET_MAC_CONFIGURATION_DCRS | ENET_MAC_CONFIGURATION_DO | ENET_MAC_CONFIGURATION_DR \
                       | ENET_MAC_CONFIGURATION_BL | ENET_MAC_CONFIGURATION_DC);
        reg_value |= reg_temp;
        ENET_MAC_CONFIGURATION = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure fullduplex_param related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)FULLDUPLEX_OPTION)) {
        reg_temp = enet_initpara.fullduplex_param;

        reg_value = ENET_MAC_CONFIGURATION;
        /* configure ENET_MAC_CONFIGURATION register */
        reg_value &= ~(ENET_MAC_CONFIGURATION_ECRSFD | ENET_MAC_CONFIGURATION_PRELEN);
        reg_value |= reg_temp;
        ENET_MAC_CONFIGURATION = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure packet size related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)PACKETSIZE_OPTION)) {
        reg_temp = enet_initpara.packetsize_config;

        reg_value = ENET_MAC_CONFIGURATION;
        /* configure ENET_MAC_CONFIGURATION register */
        reg_value &= ~(ENET_MAC_CONFIGURATION_S2KP | ENET_MAC_CONFIGURATION_JE | ENET_MAC_CONFIGURATION_GPSLCE);
        reg_value |= reg_temp;
        ENET_MAC_CONFIGURATION = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure timer_config related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)TIMER_OPTION)) {
        reg_temp = enet_initpara.timer_config;

        reg_value = ENET_MAC_CONFIGURATION;
        /* configure ENET_MAC_CONFIGURATION register */
        reg_value &= ~(ENET_MAC_CONFIGURATION_WD | ENET_MAC_CONFIGURATION_JD);
        reg_value |= reg_temp;
        ENET_MAC_CONFIGURATION = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }


    /* configure mac control related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)MACCONTROL_OPTION)) {
        reg_temp = enet_initpara.maccontrol_param;

        reg_value = ENET_MAC_CONFIGURATION;
        /* configure ENET_MAC_CONFIGURATION register */
        reg_value &= ~(ENET_MAC_CONFIGURATION_ARPEN | ENET_MAC_CONFIGURATION_SARC);
        reg_value |= reg_temp;
        ENET_MAC_CONFIGURATION = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure interframegap related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)INTERFRAMEGAP_OPTION)) {
        reg_temp = enet_initpara.interframegap;

        reg_value = ENET_MAC_CONFIGURATION;
        /* configure ENET_MAC_CONFIGURATION register */
        reg_value &= ~ENET_MAC_CONFIGURATION_IPG;
        reg_value |= reg_temp;
        ENET_MAC_CONFIGURATION = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure ecccontrol related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)ECCCONTROL_OPTION)) {
        reg_temp = enet_initpara.ecccontrol;

        reg_value = ENET_MTL_ECC_CONTROL;
        /* configure ENET_MTL_ECC_CONTROL register */
        reg_value &= ~(ENET_MTL_ECC_CONTROL_MEEAO | ENET_MTL_ECC_CONTROL_MRXPEE | ENET_MTL_ECC_CONTROL_MESTEE | ENET_MTL_ECC_CONTROL_MRXEE |
                       ENET_MTL_ECC_CONTROL_MTXEE);
        reg_value |= reg_temp;
        ENET_MTL_ECC_CONTROL = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure dppcontrol related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)DPPCONTROL_OPTION)) {
        reg_temp = enet_initpara.dppcontrol;

        reg_value = ENET_MTL_DPP_CONTROL;
        /* configure ENET_MTL_DPP_CONTROL register */
        reg_value &= ~(ENET_MTL_DPP_CONTROL_EDPP | ENET_MTL_DPP_CONTROL_OPE | ENET_MTL_DPP_CONTROL_EPSI);
        reg_value |= reg_temp;
        ENET_MTL_DPP_CONTROL = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure fsmcontrol related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)FSMCONTROL_OPTION)) {
        reg_temp = enet_initpara.fsmcontrol;

        reg_value = ENET_MAC_FSM_CONTROL;
        /* configure ENET_MAC_FSM_CONTROL register */
        reg_value &= 0x0000U;
        reg_value |= reg_temp;
        ENET_MAC_FSM_CONTROL = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    /* configure estcontrol related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)ESTCONTROL_OPTION)) {
        reg_temp = enet_initpara.estcontrol;

        reg_value = ENET_MTL_EST_CONTROL;
        /* configure ENET_MTL_EST_CONTROL register */
        reg_value &= 0x0000U;
        reg_value |= reg_temp;
        ENET_MTL_EST_CONTROL = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

    /* configure estcontrol related registers */
    if((uint32_t)RESET != (enet_initpara.option_enable & (uint32_t)FPECONTROL_OPTION)) {
        reg_temp = enet_initpara.fpecontrol;

        reg_value = ENET_MAC_FPE_CTRL_STS;
        temp = reg_temp;
        /* configure ENET_MAC_FPE_CTRL_STS register */
        reg_value &= ~(ENET_MAC_FPE_CTRL_STS_ARV | ENET_MAC_FPE_CTRL_STS_EFPE);
        temp &= (ENET_MAC_FPE_CTRL_STS_ARV | ENET_MAC_FPE_CTRL_STS_EFPE);
        reg_value |= temp;
        ENET_MAC_FPE_CTRL_STS = reg_value;
        
        reg_value = ENET_MTL_FPE_CTRL_STS;
        temp = reg_temp;
        /* configure ENET_MTL_FPE_CTRL_STS register */
        reg_value &= ~(ENET_MTL_FPE_CTRL_STS_AFSZ | ENET_MTL_FPE_CTRL_STS_LBHT | ENET_MTL_FPE_CTRL_STS_PEC);
        temp &= ((ENET_MTL_FPE_CTRL_STS_AFSZ | ENET_MTL_FPE_CTRL_STS_LBHT | ENET_MTL_FPE_CTRL_STS_PEC) << 4U);
        reg_value |= (temp >> 4U);
        ENET_MTL_FPE_CTRL_STS = reg_value;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    enet_state = SUCCESS;

    return enet_state;

}
/*!
    \brief      Software Reset
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_software_reset(void)
{
    uint32_t timeout = 0U;
    ErrStatus enet_state;
    uint32_t dma_flag;

    /* software reset */
    ENET_DMA_MODE |= ENET_DMA_MODE_SWR;
    __DSB();
    __ISB();
    __DMB();
    /* wait for reset operation complete */
    do {
        dma_flag = (ENET_DMA_MODE & ENET_DMA_MODE_SWR);
        timeout++;
    } while(((uint32_t)RESET != dma_flag) && (ENET_SWR_DELAY_TO != timeout));

    /* reset operation complete */
    if((uint32_t)RESET == (ENET_DMA_MODE & ENET_DMA_MODE_SWR)) {
        enet_state = SUCCESS;
    } else {
        enet_state = ERROR;
    }
    return enet_state;
}

/*!
    \brief    check receive frame valid and return frame size
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     size of received frame: 0x0 - 0x3FFF
*/
uint32_t enet_rxframe_size_get(enet_dmach_enum dmach)
{
    uint32_t size = 0U;
    uint32_t des3_status, des1_status;

    switch(dmach) {
    case DMACH0: 
    /* get rdes3 information of current RxDMA descriptor */
    des3_status = dma_current_rxdesc->DES3;

    /* if the desciptor is owned by DMA */
    if((uint32_t)RESET != (des3_status & ENET_NORMAL_RDES3_WF_OWN)) {
        return 0U;
    }

    /* if has any error, or the frame uses two or more descriptors */
    if((((uint32_t)RESET) != (des3_status & ENET_NORMAL_RDES3_WF_ES)) ||
            (((uint32_t)RESET) == (des3_status & ENET_NORMAL_RDES3_WF_LD)) ||
            (((uint32_t)RESET) == (des3_status & ENET_NORMAL_RDES3_WF_FD))) {
        /* drop current receive frame */
        enet_rxframe_drop(DMACH0);
        return 1U;
    }
    des1_status = dma_current_rxdesc->DES1;
    /* if has other error, or the frame uses two or more descriptors */
    if((((uint32_t)RESET) != (des1_status & ENET_NORMAL_RDES1_WF_IPCE)) ||
            (((uint32_t)RESET) != (des1_status & ENET_NORMAL_RDES1_WF_IPHE))) {
        /* drop current receive frame */
        enet_rxframe_drop(DMACH0);
        return 1U;
    }
    /* if CPU owns current descriptor, no error occured, the frame uses only one descriptor */
    if((((uint32_t)RESET) == (des3_status & ENET_NORMAL_RDES3_WF_OWN)) &&
            (((uint32_t)RESET) == (des3_status & ENET_NORMAL_RDES3_WF_ES)) &&
            (((uint32_t)RESET) != (des3_status & ENET_NORMAL_RDES3_WF_FD)) &&
            (((uint32_t)RESET) != (des3_status & ENET_NORMAL_RDES3_WF_LD))) {
        /* get the size of the received data including CRC */
        size = GET_RDES3_PL(des3_status);
        /* substract the CRC size */
        size = size - 4U;

        /* if is a type frame, and CRC is not included in forwarding frame */
        if(((uint32_t)RESET != (ENET_MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_CST)) && ((uint32_t)RESET != (des3_status & ENET_NORMAL_RDES3_WF_LT))) {
            size = size + 4U;
        }
    } else {
        enet_unknow_err++;
        enet_rxframe_drop(DMACH0);

        return 1U;
    }
    break;
    case DMACH1: 
    /* get rdes0 information of current RxDMA descriptor */
    des3_status = dma_current_rxdesc1->DES3;

    /* if the desciptor is owned by DMA */
    if((uint32_t)RESET != (des3_status & ENET_NORMAL_RDES3_WF_OWN)) {
        return 0U;
    }

    /* if has any error, or the frame uses two or more descriptors */
    if((((uint32_t)RESET) != (des3_status & ENET_NORMAL_RDES3_WF_ES)) ||
            (((uint32_t)RESET) == (des3_status & ENET_NORMAL_RDES3_WF_LD)) ||
            (((uint32_t)RESET) == (des3_status & ENET_NORMAL_RDES3_WF_FD))) {
        /* drop current receive frame */
        enet_rxframe_drop(DMACH1);
        return 1U;
    }
    des1_status = dma_current_rxdesc1->DES1;
    /* if has other error, or the frame uses two or more descriptors */
    if((((uint32_t)RESET) != (des1_status & ENET_NORMAL_RDES1_WF_IPCE)) ||
            (((uint32_t)RESET) != (des1_status & ENET_NORMAL_RDES1_WF_IPHE))) {
        /* drop current receive frame */
        enet_rxframe_drop(DMACH1);
        return 1U;
    }

    /* if CPU owns current descriptor, no error occured, the frame uses only one descriptor */
    if((((uint32_t)RESET) == (des3_status & ENET_NORMAL_RDES3_WF_OWN)) &&
            (((uint32_t)RESET) == (des3_status & ENET_NORMAL_RDES3_WF_ES)) &&
            (((uint32_t)RESET) != (des3_status & ENET_NORMAL_RDES3_WF_FD)) &&
            (((uint32_t)RESET) != (des3_status & ENET_NORMAL_RDES3_WF_LD))) {
        /* get the size of the received data including CRC */
        size = GET_RDES3_PL(des3_status);
        /* substract the CRC size */
        size = size - 4U;

        /* if is a type frame, and CRC is not included in forwarding frame */
        if(((uint32_t)RESET != (ENET_MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_CST)) && ((uint32_t)RESET != (des3_status & ENET_NORMAL_RDES3_WF_LT))) {
            size = size + 4U;
        }
    } else {
        enet_unknow_err++;
        enet_rxframe_drop(DMACH1);

        return 1U;
    }
    break;
    default:
       break;
    }
    /* return packet size */
    return size;
}


/*!
    \brief    initialize the DMA Tx/Rx descriptors's parameters in ring mode
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  direction: the descriptors which users want to init, refer to enet_dmadirection_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_DMA_TX: DMA Tx descriptors
      \arg        ENET_DMA_RX: DMA Rx descriptors
    \param[out] none
    \retval     none
*/
void enet_descriptors_ring_init(enet_dmach_enum dmach, enet_dmadirection_enum direction)
{
    uint32_t num, count, maxsize;
    uint32_t desc_status = 0U;
    enet_descriptors_struct *desc;
    enet_descriptors_struct *desc_tab;
    uint8_t *buf;

    switch(dmach) {
    case DMACH0: 
    /* if want to initialize DMA Tx descriptors */
    if(ENET_DMA_TX == direction) {
        /* save a copy of the DMA Tx descriptors */
        desc_tab = txdesc_tab;
        buf = &tx_buff[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        dma_current_txdesc = desc_tab;
        
        ENET_DMA_CH0_TXDESC_RING_LENGTH = (ENET_TXBUF_NUM - 1U);
        ENET_DMA_CH0_TXDESC_ADDRESS = (uint32_t)txdesc_tab;
        ENET_DMA_CH0_TXDESC_TAIL_POINTER = (uint32_t)txdesc_tab;
    } else {
        /* if want to initialize DMA Rx descriptors */
        /* save a copy of the DMA Rx descriptors */
        desc_tab = rxdesc_tab;
        buf = &rx_buff[0][0];
        count = ENET_RXBUF_NUM;
        maxsize = ENET_RXBUF_SIZE;

        /* enable receiving */
        desc_status = ENET_NORMAL_RDES3_RF_OWN;

        dma_current_rxdesc = desc_tab;
        
        ENET_DMA_CH0_RX_CONTROL2 = (ENET_RXBUF_NUM - 1U);
        ENET_DMA_CH0_RXDESC_ADDRESS = (uint32_t)rxdesc_tab;
        ENET_DMA_CH0_RXDESC_TAIL_POINTER = (uint32_t)&rxdesc_tab[(ENET_RXBUF_NUM - 1U)];
    }

    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->DES0 = (uint32_t)(&buf[num * maxsize]);
        desc->DES3 = desc_status;
        desc->buffer_address = desc->DES0;
        if(ENET_DMA_RX == direction) {
            /* configure receive descriptor 3 */
            desc->DES3 |= ENET_NORMAL_RDES3_RF_BUF1V;
        }
    }
    break;
    case DMACH1: 
    /* if want to initialize DMA Tx descriptors */
    if(ENET_DMA_TX == direction) {
        /* save a copy of the DMA Tx descriptors */
        desc_tab = txdesc_tab1;
        buf = &tx_buff1[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        dma_current_txdesc1 = desc_tab;
        
        ENET_DMA_CH1_TXDESC_RING_LENGTH = (ENET_TXBUF_NUM - 1U);
        ENET_DMA_CH1_TXDESC_ADDRESS = (uint32_t)txdesc_tab1;
        ENET_DMA_CH1_TXDESC_TAIL_POINTER = (uint32_t)txdesc_tab1;
    } else {
        /* if want to initialize DMA Rx descriptors */
        /* save a copy of the DMA Rx descriptors */
        desc_tab = rxdesc_tab1;
        buf = &rx_buff1[0][0];
        count = ENET_RXBUF_NUM;
        maxsize = ENET_RXBUF_SIZE;

        /* enable receiving */
        desc_status = ENET_NORMAL_RDES3_RF_OWN;

        dma_current_rxdesc1 = desc_tab;
        ENET_DMA_CH1_RX_CONTROL2 = (ENET_RXBUF_NUM - 1U);
        ENET_DMA_CH1_RXDESC_ADDRESS = (uint32_t)rxdesc_tab1;
        ENET_DMA_CH1_RXDESC_TAIL_POINTER = (uint32_t)&rxdesc_tab1[(ENET_RXBUF_NUM - 1U)];
    }

    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->DES0 = (uint32_t)(&buf[num * maxsize]);
        desc->DES3 = desc_status;
        desc->buffer_address = desc->DES0;
        if(ENET_DMA_RX == direction) {
            /* configure receive descriptor 3 */
            desc->DES3 |= ENET_NORMAL_RDES3_RF_BUF1V;
        }
    }
    break;
    default:
       break;
    }
}


/*!
    \brief    handle current received frame data to application buffer
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  bufsize: the size of buffer which is the parameter in function
    \param[out] buffer: pointer to the received frame data
                note -- if the input is NULL, user should copy data in application by himself
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_frame_receive(enet_dmach_enum dmach, uint8_t *buffer, uint32_t bufsize)
{
    uint32_t offset, size;
    ErrStatus recv_status;
    recv_status = ERROR;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_BUFSIZE(bufsize)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x000BU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0: 
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_OWN)) {
        return recv_status;
    }

    /* if buffer pointer is null, indicates that users has copied data in application */
    if(NULL != buffer) {
        /* if no error occurs, and the frame uses only one descriptor */
        if((((uint32_t)RESET) == (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_ES)) &&
                (((uint32_t)RESET) != (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_LD)) &&
                (((uint32_t)RESET) != (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_FD))) {
            /* get the frame length except CRC */
            size = dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_PL;
            size = size - 4U;

            /* if is a type frame, and CRC is not included in forwarding frame */
            if(((uint32_t)RESET != (ENET_MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_CST)) && ((uint32_t)RESET != (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_LT))) {
                size = size + 4U;
            } else {
                /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }

            /* to avoid situation that the frame size exceeds the buffer length */
            if(size > bufsize) {
                return recv_status;
            } else {
                /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }

            /* copy data from Rx buffer to application buffer */
            for(offset = 0U; offset < size; offset++) {
                (*(buffer + offset)) = (*(__IO uint8_t *)(uint32_t)((dma_current_rxdesc->buffer_address) + offset));
            }

        } else {
            /* return ERROR */
            return recv_status;
        }
    } else {
    
    }
    /* enable reception, descriptor is owned by DMA */
    dma_current_rxdesc->DES3 = ENET_NORMAL_RDES3_WF_OWN;
    dma_current_rxdesc->DES0 = (uint32_t)dma_current_rxdesc->buffer_address;
    dma_current_rxdesc->DES3 |= ENET_NORMAL_RDES3_RF_BUF1V;
    
    /* If the receive interrupt is enabled, the IOC bit needs to be set */
    if((uint32_t)RESET != (ENET_DMA_CH0_INTERRUPT_ENABLE & ENET_DMA_CH_INTERRUPT_ENABLE_RIE)) {
        dma_current_rxdesc->DES3 |= ENET_NORMAL_RDES3_RF_IOC;
    }

    /* check Rx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_CH0_STATUS & ENET_DMA_CH_STATUS_RBU)) {
        /* clear RBU flag */
        ENET_DMA_CH0_STATUS &= ~ENET_DMA_CH_STATUS_RBU;
    }
    __DSB();
    __ISB();
    __DMB();
   
    /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
    /* ring mode */
     if((enet_descriptors_struct *)(uint32_t)&rxdesc_tab[(ENET_RXBUF_NUM - 1U)] == dma_current_rxdesc) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_rxdesc = (enet_descriptors_struct *)(ENET_DMA_CH0_RXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_rxdesc = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_rxdesc + ETH_DMARXDESC_SIZE);
    }
    ENET_DMA_CH0_RXDESC_TAIL_POINTER = (uint32_t)&rxdesc_tab[ENET_RXBUF_NUM];
    break;
    case DMACH1: 
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_OWN)) {
        return recv_status;
    }

    /* if buffer pointer is null, indicates that users has copied data in application */
    if(NULL != buffer) {
        /* if no error occurs, and the frame uses only one descriptor */
        if((((uint32_t)RESET) == (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_ES)) &&
                (((uint32_t)RESET) != (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_LD)) &&
                (((uint32_t)RESET) != (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_FD))) {
            /* get the frame length except CRC */
            size = dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_PL;
            size = size - 4U;

            /* if is a type frame, and CRC is not included in forwarding frame */
            if(((uint32_t)RESET != (ENET_MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_CST)) && ((uint32_t)RESET != (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_LT))) {
                size = size + 4U;
            } else {
                /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }

            /* to avoid situation that the frame size exceeds the buffer length */
            if(size > bufsize) {
                return recv_status;
            } else {
                /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }

            /* copy data from Rx buffer to application buffer */
            for(offset = 0U; offset < size; offset++) {
                (*(buffer + offset)) = (*(__IO uint8_t *)(uint32_t)((dma_current_rxdesc1->buffer_address) + offset));
            }

        } else {
            /* return ERROR */
            return recv_status;
        }
    } else {
    
    }
    /* enable reception, descriptor is owned by DMA */
    dma_current_rxdesc1->DES3 = ENET_NORMAL_RDES3_WF_OWN;
    dma_current_rxdesc1->DES0 = dma_current_rxdesc1->buffer_address;
    dma_current_rxdesc1->DES3 |= ENET_NORMAL_RDES3_RF_BUF1V;
    
    /* If the receive interrupt is enabled, the IOC bit needs to be set */
    if((uint32_t)RESET != (ENET_DMA_CH1_INTERRUPT_ENABLE & ENET_DMA_CH_INTERRUPT_ENABLE_RIE)) {
        dma_current_rxdesc1->DES3 |= ENET_NORMAL_RDES3_RF_IOC;
    }
    
    /* check Rx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_CH1_STATUS & ENET_DMA_CH_STATUS_RBU)) {
        /* clear RBU flag */
        ENET_DMA_CH1_STATUS &= ~ENET_DMA_CH_STATUS_RBU;
    }
    __DSB();
    __ISB();
    __DMB();

    /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
    /* ring mode */
    if((enet_descriptors_struct *)(uint32_t)&rxdesc_tab1[(ENET_RXBUF_NUM - 1U)] == dma_current_rxdesc1) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_rxdesc1 = (enet_descriptors_struct *)(ENET_DMA_CH1_RXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_rxdesc1 = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_rxdesc1 + ETH_DMARXDESC_SIZE);
    }
    ENET_DMA_CH1_RXDESC_TAIL_POINTER = (uint32_t)&rxdesc_tab1[ENET_RXBUF_NUM];

    break;
    default:
       break;
    }
    recv_status = SUCCESS;
}
    return recv_status;
}

/*!
    \brief    handle application buffer data to transmit it
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  buffer: pointer to the frame data to be transmitted,
                note -- if the input is NULL, user should handle the data in application by himself
    \param[in]  length: the length of frame data to be transmitted
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_frame_transmit(enet_dmach_enum dmach, uint8_t *buffer, uint32_t length)
{
    uint32_t offset;
    ErrStatus status;
    status = ERROR;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_BUFSIZE(length)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x000CU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{

    switch(dmach) {
    case DMACH0: 
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_txdesc->DES3 & ENET_NORMAL_TDES3_WF_OWN)) {
        return status;
    }

#ifndef FW_DEBUG_ERR_REPORT
    /* only frame length no more than ENET_MAX_FRAME_SIZE is allowed */
    if(length > ENET_MAX_FRAME_SIZE) {
        return status;
    } else {
    
    }
#endif /* FW_DEBUG_ERR_REPORT */

    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0U; offset < length; offset++) {
            (*(__IO uint8_t *)(uint32_t)((dma_current_txdesc->DES0) + offset)) = (*(buffer + offset));
        }
    }

    /* set the frame length */
    dma_current_txdesc->DES2 = length;
    /* set the segment of frame, frame is transmitted in one descriptor */
    dma_current_txdesc->DES3 |= ENET_NORMAL_TDES3_WF_FD | ENET_NORMAL_TDES3_WF_LD;
    /* enable the DMA transmission */
    dma_current_txdesc->DES3 |= ENET_NORMAL_TDES3_WF_OWN;
    __DSB();
    __ISB();
    __DMB();

    /* check Tx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_CH0_STATUS & ENET_DMA_CH_STATUS_TBU)) {
        /* clear TBU flag */
        ENET_DMA_CH0_STATUS &= ~ENET_DMA_CH_STATUS_TBU;
    }
    ENET_DMA_CH0_TXDESC_TAIL_POINTER = (uint32_t)dma_current_txdesc + sizeof(enet_descriptors_struct);

    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table*/
    /* ring mode */
    if((enet_descriptors_struct *)(ENET_DMA_CH0_TXDESC_ADDRESS + (ENET_TXBUF_NUM-1U) * sizeof(enet_descriptors_struct)) <= dma_current_txdesc) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_txdesc = (enet_descriptors_struct *)(ENET_DMA_CH0_TXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_txdesc = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_txdesc + ETH_DMATXDESC_SIZE);
    }

    break;
    case DMACH1: 
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_txdesc1->DES3 & ENET_NORMAL_TDES3_WF_OWN)) {
        return status;
    }

#ifndef FW_DEBUG_ERR_REPORT
    /* only frame length no more than ENET_MAX_FRAME_SIZE is allowed */
    if(length > ENET_MAX_FRAME_SIZE) {
        return status;
    } else {
    
    }
#endif /* FW_DEBUG_ERR_REPORT */

    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0U; offset < length; offset++) {
            (*(__IO uint8_t *)(uint32_t)((dma_current_txdesc1->DES0) + offset)) = (*(buffer + offset));
        }
    }

    /* set the frame length */
    dma_current_txdesc1->DES2 = length;
    /* set the segment of frame, frame is transmitted in one descriptor */
    dma_current_txdesc1->DES3 |= ENET_NORMAL_TDES3_WF_FD | ENET_NORMAL_TDES3_WF_LD;
    /* enable the DMA transmission */
    dma_current_txdesc1->DES3 |= ENET_NORMAL_TDES3_WF_OWN;
    __DSB();
    __ISB();
    __DMB();

    /* check Tx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_CH1_STATUS & ENET_DMA_CH_STATUS_TBU)) {
        /* clear TBU flag */
        ENET_DMA_CH1_STATUS &= ~ENET_DMA_CH_STATUS_TBU;
    }
    ENET_DMA_CH1_TXDESC_TAIL_POINTER = (uint32_t)dma_current_txdesc1 + sizeof(enet_descriptors_struct);
    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table*/
    /* ring mode */
    if((enet_descriptors_struct *)(ENET_DMA_CH1_TXDESC_ADDRESS + (ENET_TXBUF_NUM-1U) * sizeof(enet_descriptors_struct)) <= dma_current_txdesc1) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_txdesc1= (enet_descriptors_struct *)(ENET_DMA_CH1_TXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_txdesc1 = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_txdesc1 + ETH_DMATXDESC_SIZE);
    }
    break;
    default:
       break;
    }
    status = SUCCESS;
}
    return status;
}


/*!
    \brief    configure the transmit IP frame checksum offload calculation and insertion
    \param[in]  desc: the descriptor pointer which users want to configure, refer to enet_descriptors_struct
    \param[in]  checksum: IP frame checksum configuration
                only one parameter can be selected which is shown as below
      \arg        ENET_CHECKSUM_DISABLE: checksum insertion disabled
      \arg        ENET_CHECKSUM_IPV4HEADER: only IP header checksum calculation and insertion are enabled
      \arg        ENET_CHECKSUM_TCPUDPICMP_SEGMENT: TCP/UDP/ICMP checksum insertion calculated but pseudo-header
      \arg        ENET_CHECKSUM_TCPUDPICMP_FULL: TCP/UDP/ICMP checksum insertion fully calculated
    \param[out] none
    \retval     none
*/
void enet_transmit_checksum_config(enet_descriptors_struct *desc, uint32_t checksum)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(desc)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x000DU), ERR_PARAM_POINTER);
    } else if(NOT_ENET_CHECKSUM(checksum)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    desc->DES3 &= ~ENET_NORMAL_TDES3_RF_CIC;
    desc->DES3 |= checksum;
}
}

/*!
    \brief    configure MAC to add or replace the Source Address field in the Ethernet packet
    \param[in]  desc: the descriptor pointer which users want to configure, refer to enet_descriptors_struct
    \param[in]  control: SA insertion Control
                only one parameter can be selected which is shown as below
      \arg        ENET_NO_SA_INCLUDE: do not include the source address
      \arg        ENET_MAC0_SA_INCLUDE_INSERT: include or insert the source MAC Address 0
      \arg        ENET_MAC0_SA_REPLACE: replace the source MAC Address 0
      \arg        ENET_MAC1_SA_INCLUDE_INSERT: include or insert the source MAC Address 1
      \arg        ENET_MAC1_SA_REPLACE: replace the source MAC Address 1
    \param[out] none
    \retval     none
*/
void enet_transmit_sourceaddr_insert_config(enet_descriptors_struct *desc, uint32_t control)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(desc)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x000EU), ERR_PARAM_POINTER);
    } else if(NOT_ENET_TXSRCADDR_CONTROL(control)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    desc->DES3 &= ~ENET_NORMAL_TDES3_RF_SAIC;
    desc->DES3 |= control;
}
}

/*!
    \brief    configure the CRC and pad insertion for Tx packet
    \param[in]  desc: the descriptor pointer which users want to configure, refer to enet_descriptors_struct
    \param[in]  control: CRC and pad control configuration
                only one parameter can be selected which is shown as below
      \arg        ENET_CRC_PAD_INSERT: CRC and pad insertion
      \arg        ENET_CRC_INSERT: CRC insertion
      \arg        ENET_CRC_INSERT_DISABLE: disable CRC Insertion
      \arg        ENET_CRC_REPLACE: CRC replacement
    \param[out] none
    \retval     none
*/
void enet_transmit_crc_pad_config(enet_descriptors_struct *desc, uint32_t control)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(desc)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x000FU), ERR_PARAM_POINTER);
    } else if(NOT_ENET_TXCRCPAD_CONTROL(control)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    desc->DES3 &= ~ENET_NORMAL_TDES3_RF_CPC;
    desc->DES3 |= control;
}
}

/*!
    \brief    configure MAC address
    \param[in]  mac_addr: select which MAC address will be set, refer to enet_macaddress_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MAC_ADDRESS0: set MAC address 0
      \arg        ENET_MAC_ADDRESS1: set MAC address 1
      \arg        ENET_MAC_ADDRESS2: set MAC address 2
    \param[in]  paddr: the buffer pointer which stores the MAC address
                  (little-ending store, such as MAC address is aa:bb:cc:dd:ee:22, the buffer is {22, ee, dd, cc, bb, aa})
    \param[out] none
    \retval     none
*/
void enet_mac_address_set(enet_macaddress_enum mac_addr, uint8_t paddr[])
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(paddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0010U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    REG32(ENET_ADDRH_BASE + (uint32_t)mac_addr) &= MAC_ADDR_HIGH_MASK;
    REG32(ENET_ADDRH_BASE + (uint32_t)mac_addr) |= ENET_SET_MACADDRH(paddr);
    REG32(ENET_ADDRL_BASE + (uint32_t)mac_addr) = ENET_SET_MACADDRL(paddr);
}
}

/*!
    \brief    get MAC address
    \param[in]  mac_addr: select which MAC address will be get, refer to enet_macaddress_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MAC_ADDRESS0: get MAC address 0
      \arg        ENET_MAC_ADDRESS1: get MAC address 1
      \arg        ENET_MAC_ADDRESS2: get MAC address 2
    \param[out] paddr: the buffer pointer which is stored the MAC address
                  (little-ending store, such as mac address is aa:bb:cc:dd:ee:22, the buffer is {22, ee, dd, cc, bb, aa})
    \retval     none
*/

void enet_mac_address_get(enet_macaddress_enum mac_addr, uint8_t paddr[])
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(paddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0011U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    paddr[0] = ENET_GET_MACADDR((uint32_t)mac_addr, 0U);
    paddr[1] = ENET_GET_MACADDR((uint32_t)mac_addr, 1U);
    paddr[2] = ENET_GET_MACADDR((uint32_t)mac_addr, 2U);
    paddr[3] = ENET_GET_MACADDR((uint32_t)mac_addr, 3U);
    paddr[4] = ENET_GET_MACADDR((uint32_t)mac_addr, 4U);
    paddr[5] = ENET_GET_MACADDR((uint32_t)mac_addr, 5U);
}
}

/*!
    \brief    configure ARP IP address
    \param[in]  ipaddr: the buffer pointer which stores the IPV4 address
                  (little-ending store, such as ip address is 10.50.3.140, the buffer is {140, 3, 50, 10})
    \param[out] none
    \retval     none
*/
void enet_arp_ip_address_set(uint8_t ipaddr[])
{
    uint32_t arp_ipaddr;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(ipaddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0012U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    arp_ipaddr = ENET_SET_IPV4ADDR(ipaddr);
    ENET_MAC_ARP_ADDRESS = MAC_ARP_ADDRESS_ARPPA(arp_ipaddr);
}
}

/*!
    \brief    get the ENET MAC/MTL/DMA status flag
    \param[in]  enet_flag: ENET status flag, refer to enet_flag_enum,
                only one parameter can be selected which is shown as below
      \arg        ENET_MAC_RX_TX_STATUS_FLAG_TJT: transmit jabber timeout status flag
      \arg        ENET_MAC_RX_TX_STATUS_FLAG_NCARR: no carrier status flag
      \arg        ENET_MAC_RX_TX_STATUS_FLAG_LCARR: loss of carrier status flag
      \arg        ENET_MAC_RX_TX_STATUS_FLAG_EXDEF: excessive deferral status flag
      \arg        ENET_MAC_RX_TX_STATUS_FLAG_LCOL: late collision status flag
      \arg        ENET_MAC_RX_TX_STATUS_FLAG_EXCOL: excessive collisions status flag
      \arg        ENET_MAC_RX_TX_STATUS_FLAG_RWT: receive watchdog timeout status flag
      \arg        ENET_MAC_PMT_CONTROL_STATUS_FLAG_MGKPRCVD: magic packet received flag
      \arg        ENET_MAC_PMT_CONTROL_STATUS_FLAG_RWKPRCVD: remote wake-pp packet received flag
      \arg        ENET_MAC_LPI_CONTROL_STATUS_FLAG_TLPIEN: transmit LPI entry flag
      \arg        ENET_MAC_LPI_CONTROL_STATUS_FLAG_TLPIEX: transmit LPI exit flag
      \arg        ENET_MAC_LPI_CONTROL_STATUS_FLAG_RLPIEN: receive LPI entry flag
      \arg        ENET_MAC_LPI_CONTROL_STATUS_FLAG_RLPIEX: receive LPI exit flag
      \arg        ENET_MAC_LPI_CONTROL_STATUS_FLAG_TLPIST: transmit LPI state flag
      \arg        ENET_MAC_LPI_CONTROL_STATUS_FLAG_RLPIST: receive LPI state flag
      \arg        ENET_MAC_LPI_CONTROL_STATUS_FLAG_PLS: PHY link status flag
      \arg        ENET_MAC_FPE_CTRL_STS_FLAG_RVER: received verify frame flag
      \arg        ENET_MAC_FPE_CTRL_STS_FLAG_RRSP: received respond frame flag
      \arg        ENET_MAC_FPE_CTRL_STS_FLAG_TVER: transmitted verify frame flag
      \arg        ENET_MAC_FPE_CTRL_STS_FLAG_TRSP: transmitted respond frame flag
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSSOVF: timestamp seconds overflow flag
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTARGT0: timestamp target time reached flag for target time PPS0
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTRGTERR0: timestamp target time error flag for target time PPS0
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTARGT1: timestamp target time reached flag for target time PPS1
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTRGTERR1: timestamp target time error flag for target time PPS1
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTARGT2: timestamp target time reached flag for target time PPS2
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTRGTERR2: timestamp target time error flag for target time PPS2
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTARGT3: timestamp target time reached flag for target time PPS3
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTRGTERR3: timestamp target time error flag for target time PPS3
      \arg        ENET_MAC_TIMESTAMP_STATUS_FLAG_TXTSSIS: Tx timestamp status interrupt status flag
      \arg        ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_FLAG_TXTSSIS: transmit timestamp status missed status flag
      \arg        ENET_MTL_DBG_STS_FLAG_PKTI: receive packet available interrupt status flag
      \arg        ENET_MTL_DBG_STS_FLAG_STSI: transmit status available interrupt status flag
      \arg        ENET_MTL_EST_STATUS_FLAG_SWLC: switch to S/W owned list complete flag
      \arg        ENET_MTL_EST_STATUS_FLAG_BTRE: BTR error flag
      \arg        ENET_MTL_EST_STATUS_FLAG_HLBF: Head-Of-Line blocking due to frame size flag
      \arg        ENET_MTL_EST_STATUS_FLAG_HLBS: Head-Of-Line blocking due to scheduling flag
      \arg        ENET_MTL_EST_STATUS_FLAG_CGCE: constant gate control error flag
      \arg        ENET_MTL_FPE_CTRL_STS_FLAG_HRS: hold/release status flag
      \arg        ENET_MTL_RXP_CONTROL_STATUS_FLAG_RXPI: RX parser in idle state flag
      \arg        ENET_MTL_TXQ0_UNDERFLOW_FLAG_UFCNTOVF: underflow packet counter overflow flag
      \arg        ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_FLAG_OVFCNTOVF: overflow counter overflow flag
      \arg        ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_FLAG_MISCNTOVF: missed packet counter overflow flag
      \arg        ENET_MTL_TXQ1_UNDERFLOW_FLAG_UFCNTOVF: underflow packet counter overflow flag
      \arg        ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_FLAG_OVFCNTOVF: overflow counter overflow flag
      \arg        ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_FLAG_MISCNTOVF: missed packet counter overflow flag
      \arg        ENET_DMA_CH0_FLAG_TI: channel 0 transmit status flag
      \arg        ENET_DMA_CH0_FLAG_TPS: channel 0 transmit process stopped status flag
      \arg        ENET_DMA_CH0_FLAG_TBU: channel 0 transmit buffer unavailable status flag
      \arg        ENET_DMA_CH0_FLAG_RI: channel 0 receive status flag
      \arg        ENET_DMA_CH0_FLAG_RBU: channel 0 receive buffer unavailable status flag
      \arg        ENET_DMA_CH0_FLAG_RPS: channel 0 receive process stopped status flag
      \arg        ENET_DMA_CH0_FLAG_RWT: channel 0 receive watchdog timeout status flag
      \arg        ENET_DMA_CH0_FLAG_ETI: channel 0 early transmit status flag
      \arg        ENET_DMA_CH0_FLAG_ERIE: channel 0 early receive status flag
      \arg        ENET_DMA_CH0_FLAG_FBE: channel 0 fatal bus error status flag
      \arg        ENET_DMA_CH0_FLAG_CDE: channel 0 context descriptor error status flag
      \arg        ENET_DMA_CH0_FLAG_AIE: channel 0 abnormal interrupt summary flag
      \arg        ENET_DMA_CH0_FLAG_NIS: channel 0 normal interrupt summary flag
      \arg        ENET_DMA_CH0_MISS_FRAME_CNT_FLAG_MFCO: overflow status of the MFC counter flag
      \arg        ENET_DMA_CH0_RXP_ACCEPT_CNT_FLAG_RXPACOF: Rx parser accept counter overflow flag
      \arg        ENET_DMA_CH1_FLAG_TI: channel 1 transmit status flag
      \arg        ENET_DMA_CH1_FLAG_TPS: channel 1 transmit process stopped status flag
      \arg        ENET_DMA_CH1_FLAG_TBU: channel 1 transmit buffer unavailable status flag
      \arg        ENET_DMA_CH1_FLAG_RI: channel 1 receive status flag
      \arg        ENET_DMA_CH1_FLAG_RBU: channel 1 receive buffer unavailable status flag
      \arg        ENET_DMA_CH1_FLAG_RPS: channel 1 receive process stopped status flag
      \arg        ENET_DMA_CH1_FLAG_RWT: channel 1 receive watchdog timeout status flag
      \arg        ENET_DMA_CH1_FLAG_ETI: channel 1 early transmit status flag
      \arg        ENET_DMA_CH1_FLAG_ERIE: channel 1 early receive status flag
      \arg        ENET_DMA_CH1_FLAG_FBE: channel 1 fatal bus error status flag
      \arg        ENET_DMA_CH1_FLAG_CDE: channel 1 context descriptor error status flag
      \arg        ENET_DMA_CH1_FLAG_AIE: channel 1 abnormal interrupt summary flag
      \arg        ENET_DMA_CH1_FLAG_NIS: channel 1 normal interrupt summary flag
      \arg        ENET_DMA_CH1_MISS_FRAME_CNT_FLAG_MFCO: overflow status of the MFC counter flag
      \arg        ENET_DMA_CH1_RXP_ACCEPT_CNT_FLAG_RXPACOF: Rx parser accept counter overflow flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus enet_flag_get(enet_flag_enum enet_flag)
{
    FlagStatus flag;
    if((uint32_t)RESET != (ENET_REG_VAL(enet_flag) & BIT(ENET_BIT_POS(enet_flag)))) {
        flag = SET;
    } else {
        flag = RESET;
    }
    return flag;
}

/*!
    \brief    clear the ENET MTL/DMA status flag
    \param[in]  enet_flag: ENET DMA flag clear, refer to enet_flag_clear_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MTL_EST_STATUS_FLAG_CGCE_CLR: constant gate control error flag
      \arg        ENET_MTL_DBG_STS_FLAG_PKTI_CLR: receive packet available interrupt status flag
      \arg        ENET_MTL_DBG_STS_FLAG_STSI_CLR: transmit status available interrupt status flag
      \arg        ENET_DMA_CH0_FLAG_TI_CLR: channel 0 transmit status flag
      \arg        ENET_DMA_CH0_FLAG_TPS_CLR: channel 0 transmit process stopped status flag
      \arg        ENET_DMA_CH0_FLAG_TBU_CLR: channel 0 transmit buffer unavailable status flag
      \arg        ENET_DMA_CH0_FLAG_RI_CLR: channel 0 receive status flag
      \arg        ENET_DMA_CH0_FLAG_RBU_CLR: channel 0 receive buffer unavailable status flag
      \arg        ENET_DMA_CH0_FLAG_RPS_CLR: channel 0 receive process stopped status flag
      \arg        ENET_DMA_CH0_FLAG_RWT_CLR: channel 0 receive watchdog timeout status flag
      \arg        ENET_DMA_CH0_FLAG_ETI_CLR: channel 0 early transmit status flag
      \arg        ENET_DMA_CH0_FLAG_ERIE_CLR: channel 0 early receive status flag
      \arg        ENET_DMA_CH0_FLAG_FBE_CLR: channel 0 fatal bus error status flag
      \arg        ENET_DMA_CH0_FLAG_CDE_CLR: channel 0 context descriptor error status flag
      \arg        ENET_DMA_CH0_FLAG_AIE_CLR: channel 0 abnormal interrupt summary flag
      \arg        ENET_DMA_CH0_FLAG_NIS_CLR: channel 0 normal interrupt summary flag
      \arg        ENET_DMA_CH1_FLAG_TI_CLR: channel 1 transmit status flag
      \arg        ENET_DMA_CH1_FLAG_TPS_CLR: channel 1 transmit process stopped status flag
      \arg        ENET_DMA_CH1_FLAG_TBU_CLR: channel 1 transmit buffer unavailable status flag
      \arg        ENET_DMA_CH1_FLAG_RI_CLR: channel 1 receive status flag
      \arg        ENET_DMA_CH1_FLAG_RBU_CLR: channel 1 receive buffer unavailable status flag
      \arg        ENET_DMA_CH1_FLAG_RPS_CLR: channel 1 receive process stopped status flag
      \arg        ENET_DMA_CH1_FLAG_RWT_CLR: channel 1 receive watchdog timeout status flag
      \arg        ENET_DMA_CH1_FLAG_ETI_CLR: channel 1 early transmit status flag
      \arg        ENET_DMA_CH1_FLAG_ERIE_CLR: channel 1 early receive status flag
      \arg        ENET_DMA_CH1_FLAG_FBE_CLR: channel 1 fatal bus error status flag
      \arg        ENET_DMA_CH1_FLAG_CDE_CLR: channel 1 context descriptor error status flag
      \arg        ENET_DMA_CH1_FLAG_AIE_CLR: channel 1 abnormal interrupt summary flag
      \arg        ENET_DMA_CH1_FLAG_NIS_CLR: channel 1 normal interrupt summary flag
    \param[out] none
    \retval     none
*/
void enet_flag_clear(enet_flag_clear_enum enet_flag)
{
    /* write 1 to the corresponding bit, to clear it */
    ENET_REG_VAL(enet_flag) = BIT(ENET_BIT_POS(enet_flag));
}

/*!
    \brief    enable ENET MAC/MMC/MTL/DMA interrupt
    \param[in]  enet_int: ENET interrupt,, refer to enet_int_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MAC_INT_PHYIE: PHY interrupt enable
      \arg        ENET_MAC_INT_PMTIE: PMT interrupt enable
      \arg        ENET_MAC_INT_LPIIE: LPI interrupt enable
      \arg        ENET_MAC_INT_TSIE: timestamp interrupt enable
      \arg        ENET_MAC_INT_TXSTSIE: transmit status interrupt enable
      \arg        ENET_MAC_INT_RXSTSIE: receive status interrupt enable
      \arg        ENET_MAC_INT_FPEIE: frame preemption interrupt enable
      \arg        ENET_MAC_INT_MDIOIE: MDIO interrupt enable
      \arg        ENET_MMC_RX_INT_RXGBPKTIM: MMC receive good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXGBOCTIM: MMC receive good bad octet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXGOCTIM: MMC receive good octet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXBCGPIM: MMC receive broadcast good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXMCGPIM: MMC receive multicast good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXCRCERPIM: MMC receive crc error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXALGNERPIM: MMC receive alignment error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXRUNTPIM: MMC receive runt packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXJABERPIM: MMC receive jabber error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXUSIZEGPIM: MMC receive undersize good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXOSIZEGPIM: MMC receive oversize good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX64OCTGBPIM: MMC receive 64 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX65T127OCTGBPIM: MMC receive 65 to 127 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX128T255OCTGBPIM: MMC receive 128 to 255 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX256T511OCTGBPIM: MMC receive 256 to 511 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX512T1023OCTGBPIM: MMC receive 512 to 1023 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX1024TMAXOCTGBPIM: MMC receive 1024 to maximum octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXUCGPIM: MMC receive unicast good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXLENERPIM: MMC receive length error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXORANGEPIM: MMC receive out of range error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXPAUSPIM: MMC receive pause counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXFOVPIM: MMC receive FIFO overflow packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXVLANGBPIM: MMC receive VLAN good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXWDOGPIM: MMC receive watchdog error bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXRCVERRPIM: MMC receive error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXCTRLPIM: MMC receive control packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXLPIUSCIM: MMC receive LPI microsecond counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXLPITRCIM: MMC receive LPI transition counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXGBOCTIM: MMC transmit good bad octet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXGBPKTIM: MMC transmit good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXBCGPIM: MMC transmit broadcast good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXMCGPIM: MMC transmit multicast good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX64OCTGBPIM: MMC transmit 64 Octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX65T127OCTGBPIM: MMC transmit 65 to 127 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX128T255OCTGBPIM: MMC transmit 128 to 255 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX256T511OCTGBPIM: MMC transmit 256 to 511 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX512T1023OCTGBPIM: MMC transmit 512 to 1023 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX1024TMAXOCTGBPIM: MMC transmit 1024 to maximum octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXUCGBPIM: MMC transmit unicast good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXMCGBPIM: MMC transmit multicast good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXBCGBPIM: MMC transmit broadcast good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXUFLOWERPIM: MMC transmit underflow error packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXSCOLGPIM: MMC transmit single collision good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXMCOLGPIM: MMC transmit multiple collision good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXDEFPIM: MMC transmit deferred packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXLATCOLPIM: MMC transmit late collision packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXEXCOLPIM: MMC transmit excessive collision packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXCARERPIM: MMC transmit carrier error packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXGOCTIM: MMC transmit good octet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXGPKTIM: MMC transmit good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXEXDEFPIM: MMC transmit excessive deferral packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXPAUSPIM: MMC transmit VLAN good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXOSIZEGPIM: MMC transmit oversize good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXLPIUSCIM: MMC transmit LPI microsecond counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXLPITRCIM: MMC transmit LPI transition counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4GPIM: MMC receive IPV4 good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4HERPIM: MMC receive IPV4 header error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4NOPAYPIM: MMC receive IPV4 no payload packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4FRAGPIM: MMC receive IPV4 fragmented packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4UDSBLPIM: MMC receive IPV4 UDP checksum disabled packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6GPIM: MMC receive IPV6 good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6HERPIM: MMC receive IPV6 header error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6NOPAYPIM: MMC receive IPV6 no payload packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXUDPGPIM: MMC receive UDP good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXUDPERPIM: MMC receive UDP error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXTCPGPIM: MMC receive TCP good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXTCPERPIM: MMC receive TCP error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXICMPGPIM: MMC receive ICMP good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXICMPERPIM: MMC receive ICMP error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4GOIM: MMC receive IPV4 good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4HEROIM: MMC receive IPV4 header error octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4NOPAYOIM: MMC receive IPV4 no payload octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4FRAGOIM: MMC receive IPV4 fragmented octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4UDSBLOIM: MMC receive IPV4 UDP checksum disabled octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6GOIM: MMC receive IPV6 good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6HEROIM: MMC receive IPV6 header error octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6NOPAYOIM: MMC receive IPV6 no payload octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXUDPGOIM: MMC receive UDP good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXUDPEROIM: MMC receive UDP error octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXTCPGOIM: MMC receive TCP good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXTCPEROIM: MMC receive TCP error octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXICMPGOIM: MMC receive ICMP good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXICMPEROIM: MMC receive ICMP error octet counter interrupt mask
      \arg        ENET_MMC_FPE_TX_INT_FCIM: MMC Tx FPE fragment counter interrupt mask
      \arg        ENET_MMC_FPE_TX_INT_HRCIM: MMC Tx hold request counter interrupt mask
      \arg        ENET_MMC_FPE_RX_INT_PAECIM: MMC Rx packet assembly error counter interrupt mask
      \arg        ENET_MMC_FPE_RX_INT_PSECIM: MMC Rx packet SMD error counter interrupt mask
      \arg        ENET_MMC_FPE_RX_INT_PAOCIM: MMC Rx packet assembly OK counter interrupt mask
      \arg        ENET_MMC_FPE_RX_INT_FCIM: MMC Rx FPE fragment counter interrupt mask
      \arg        ENET_MTL_EST_INT_CGCEIE: the constant gate control error interrupt enable
      \arg        ENET_MTL_EST_INT_IEHSIE: interrupt enable for HLBS
      \arg        ENET_MTL_EST_INT_IEHFIE: interrupt enable for HLBF
      \arg        ENET_MTL_EST_INT_IEBEIE: interrupt enable for BTR error
      \arg        ENET_MTL_EST_INT_IECCIE: interrupt enable for switch enable
      \arg        ENET_MTL_RXP_INT_NVEOVIE: number of valid entries overflow interrupt enable
      \arg        ENET_MTL_RXP_INT_NPEOVIE: number of parsable entries overflow interrupt enable
      \arg        ENET_MTL_RXP_INT_FOOVIE: frame offset overflow interrupt enable
      \arg        ENET_MTL_RXP_INT_PDRFIE: packet drop due to RF interrupt enable
      \arg        ENET_MTL_ECC_INT_RPCEIE: Rx parser memory correctable error interrupt enable
      \arg        ENET_MTL_ECC_INT_ECEIE: EST memory correctable error interrupt enable
      \arg        ENET_MTL_ECC_INT_RXCEIE: Rx memory correctable error interrupt enable
      \arg        ENET_MTL_ECC_INT_TXCEIE: Tx memory correctable error interrupt enable
      \arg        ENET_MTL_Q0_INT_RXOIE: receive queue 0 overflow interrupt enable
      \arg        ENET_MTL_Q0_INT_ABPSIE: queue 0 average bits per slot interrupt enable
      \arg        ENET_MTL_Q0_INT_TXUIE: transmit queue 0 underflow interrupt enable
      \arg        ENET_MTL_Q1_INT_RXOIE: receive queue 1 overflow interrupt enable
      \arg        ENET_MTL_Q1_INT_ABPSIE: queue 1 average bits per slot interrupt enable
      \arg        ENET_MTL_Q1_INT_TXUIE: transmit queue 1 underflow interrupt enable
      \arg        ENET_DMA_CH0_INT_TIE: channel 0 transmit interrupt enable
      \arg        ENET_DMA_CH0_INT_TXSEIE: channel 0 transmit process stopped interrupt enable
      \arg        ENET_DMA_CH0_INT_TBUEIE: channel 0 transmit buffer unavailable interrupt enable
      \arg        ENET_DMA_CH0_INT_RIE: channel 0 receive interrupt enable
      \arg        ENET_DMA_CH0_INT_RBUEIE: channel 0 receive buffer unavailable interrupt enable
      \arg        ENET_DMA_CH0_INT_RSEIE: channel 0 receive process stopped interrupt enable
      \arg        ENET_DMA_CH0_INT_RWTEIE: channel 0 receive watchdog timeout interrupt enable
      \arg        ENET_DMA_CH0_INT_ETIE: channel 0 early transmit interrupt enable
      \arg        ENET_DMA_CH0_INT_ERIE: channel 0 early receive interrupt enable
      \arg        ENET_DMA_CH0_INT_FBEEIE: channel 0 fatal bus error interrupt enable
      \arg        ENET_DMA_CH0_INT_CDEEIE: channel 0 the descriptor error interrupt enable
      \arg        ENET_DMA_CH0_INT_AIE: channel 0 abnormal interrupt summary enable
      \arg        ENET_DMA_CH0_INT_NIE: channel 0 normal interrupt summary enable
      \arg        ENET_DMA_CH1_INT_TIE: channel 1 transmit interrupt enable
      \arg        ENET_DMA_CH1_INT_TXSEIE: channel 1 transmit process stopped interrupt enable
      \arg        ENET_DMA_CH1_INT_TBUEIE: channel 1 transmit buffer unavailable interrupt enable
      \arg        ENET_DMA_CH1_INT_RIE: channel 1 receive interrupt enable
      \arg        ENET_DMA_CH1_INT_RBUEIE: channel 1 receive buffer unavailable interrupt enable
      \arg        ENET_DMA_CH1_INT_RSEIE: channel 1 receive process stopped interrupt enable
      \arg        ENET_DMA_CH1_INT_RWTEIE: channel 1 receive watchdog timeout interrupt enable
      \arg        ENET_DMA_CH1_INT_ETIE: channel 1 early transmit interrupt enable
      \arg        ENET_DMA_CH1_INT_ERIE: channel 1 early receive interrupt enable
      \arg        ENET_DMA_CH1_INT_FBEEIE: channel 1 fatal bus error interrupt enable
      \arg        ENET_DMA_CH1_INT_CDEEIE: channel 1 the descriptor error interrupt enable
      \arg        ENET_DMA_CH1_INT_AIE: channel 1 abnormal interrupt summary enable
      \arg        ENET_DMA_CH1_INT_NIE: channel 1 normal interrupt summary enable
    \param[out] none
    \retval     none
*/
void enet_interrupt_enable(enet_int_enum enet_int)
{
    uint32_t reg_type;
    reg_type = ((uint32_t)enet_int >> 6U);
    if((reg_type == MMC_RX_INTERRUPT_MASK_REG_OFFSET) || (reg_type == MMC_TX_INTERRUPT_MASK_REG_OFFSET) || (reg_type == MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET) || \
      (reg_type == MMC_FPE_TX_INTERRUPT_MASK_REG_OFFSET) || (reg_type == MMC_FPE_RX_INTERRUPT_MASK_REG_OFFSET)){
      /* INTMSK register interrupt */
      ENET_REG_VAL(enet_int) &= ~BIT(ENET_BIT_POS(enet_int));
      } else {
        /* INTEN register interrupt */
        ENET_REG_VAL(enet_int) |= BIT(ENET_BIT_POS(enet_int));
      }
}

/*!
    \brief    disable ENET MAC/MMC/MTL/DMA interrupt
    \param[in]  enet_int: ENET interrupt,, refer to enet_int_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MAC_INT_PHYIE: PHY interrupt enable
      \arg        ENET_MAC_INT_PMTIE: PMT interrupt enable
      \arg        ENET_MAC_INT_LPIIE: LPI interrupt enable
      \arg        ENET_MAC_INT_TSIE: timestamp interrupt enable
      \arg        ENET_MAC_INT_TXSTSIE: transmit status interrupt enable
      \arg        ENET_MAC_INT_RXSTSIE: receive status interrupt enable
      \arg        ENET_MAC_INT_FPEIE: frame preemption interrupt enable
      \arg        ENET_MAC_INT_MDIOIE: MDIO interrupt enable
      \arg        ENET_MMC_RX_INT_RXGBPKTIM: MMC receive good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXGBOCTIM: MMC receive good bad octet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXGOCTIM: MMC receive good octet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXBCGPIM: MMC receive broadcast good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXMCGPIM: MMC receive multicast good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXCRCERPIM: MMC receive crc error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXALGNERPIM: MMC receive alignment error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXRUNTPIM: MMC receive runt packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXJABERPIM: MMC receive jabber error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXUSIZEGPIM: MMC receive undersize good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXOSIZEGPIM: MMC receive oversize good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX64OCTGBPIM: MMC receive 64 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX65T127OCTGBPIM: MMC receive 65 to 127 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX128T255OCTGBPIM: MMC receive 128 to 255 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX256T511OCTGBPIM: MMC receive 256 to 511 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX512T1023OCTGBPIM: MMC receive 512 to 1023 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RX1024TMAXOCTGBPIM: MMC receive 1024 to maximum octet good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXUCGPIM: MMC receive unicast good packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXLENERPIM: MMC receive length error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXORANGEPIM: MMC receive out of range error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXPAUSPIM: MMC receive pause counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXFOVPIM: MMC receive FIFO overflow packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXVLANGBPIM: MMC receive VLAN good bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXWDOGPIM: MMC receive watchdog error bad packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXRCVERRPIM: MMC receive error packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXCTRLPIM: MMC receive control packet counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXLPIUSCIM: MMC receive LPI microsecond counter interrupt mask
      \arg        ENET_MMC_RX_INT_RXLPITRCIM: MMC receive LPI transition counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXGBOCTIM: MMC transmit good bad octet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXGBPKTIM: MMC transmit good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXBCGPIM: MMC transmit broadcast good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXMCGPIM: MMC transmit multicast good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX64OCTGBPIM: MMC transmit 64 Octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX65T127OCTGBPIM: MMC transmit 65 to 127 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX128T255OCTGBPIM: MMC transmit 128 to 255 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX256T511OCTGBPIM: MMC transmit 256 to 511 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX512T1023OCTGBPIM: MMC transmit 512 to 1023 octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TX1024TMAXOCTGBPIM: MMC transmit 1024 to maximum octet good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXUCGBPIM: MMC transmit unicast good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXMCGBPIM: MMC transmit multicast good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXBCGBPIM: MMC transmit broadcast good bad packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXUFLOWERPIM: MMC transmit underflow error packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXSCOLGPIM: MMC transmit single collision good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXMCOLGPIM: MMC transmit multiple collision good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXDEFPIM: MMC transmit deferred packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXLATCOLPIM: MMC transmit late collision packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXEXCOLPIM: MMC transmit excessive collision packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXCARERPIM: MMC transmit carrier error packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXGOCTIM: MMC transmit good octet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXGPKTIM: MMC transmit good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXEXDEFPIM: MMC transmit excessive deferral packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXPAUSPIM: MMC transmit VLAN good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXOSIZEGPIM: MMC transmit oversize good packet counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXLPIUSCIM: MMC transmit LPI microsecond counter interrupt mask
      \arg        ENET_MMC_TX_INT_TXLPITRCIM: MMC transmit LPI transition counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4GPIM: MMC receive IPV4 good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4HERPIM: MMC receive IPV4 header error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4NOPAYPIM: MMC receive IPV4 no payload packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4FRAGPIM: MMC receive IPV4 fragmented packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4UDSBLPIM: MMC receive IPV4 UDP checksum disabled packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6GPIM: MMC receive IPV6 good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6HERPIM: MMC receive IPV6 header error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6NOPAYPIM: MMC receive IPV6 no payload packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXUDPGPIM: MMC receive UDP good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXUDPERPIM: MMC receive UDP error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXTCPGPIM: MMC receive TCP good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXTCPERPIM: MMC receive TCP error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXICMPGPIM: MMC receive ICMP good packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXICMPERPIM: MMC receive ICMP error packet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4GOIM: MMC receive IPV4 good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4HEROIM: MMC receive IPV4 header error octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4NOPAYOIM: MMC receive IPV4 no payload octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4FRAGOIM: MMC receive IPV4 fragmented octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV4UDSBLOIM: MMC receive IPV4 UDP checksum disabled octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6GOIM: MMC receive IPV6 good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6HEROIM: MMC receive IPV6 header error octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXIPV6NOPAYOIM: MMC receive IPV6 no payload octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXUDPGOIM: MMC receive UDP good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXUDPEROIM: MMC receive UDP error octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXTCPGOIM: MMC receive TCP good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXTCPEROIM: MMC receive TCP error octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXICMPGOIM: MMC receive ICMP good octet counter interrupt mask
      \arg        ENET_MMC_IPC_RX_INT_RXICMPEROIM: MMC receive ICMP error octet counter interrupt mask
      \arg        ENET_MMC_FPE_TX_INT_FCIM: MMC Tx FPE fragment counter interrupt mask
      \arg        ENET_MMC_FPE_TX_INT_HRCIM: MMC Tx hold request counter interrupt mask
      \arg        ENET_MMC_FPE_RX_INT_PAECIM: MMC Rx packet assembly error counter interrupt mask
      \arg        ENET_MMC_FPE_RX_INT_PSECIM: MMC Rx packet SMD error counter interrupt mask
      \arg        ENET_MMC_FPE_RX_INT_PAOCIM: MMC Rx packet assembly OK counter interrupt mask
      \arg        ENET_MMC_FPE_RX_INT_FCIM: MMC Rx FPE fragment counter interrupt mask
      \arg        ENET_MTL_EST_INT_CGCEIE: the constant gate control error interrupt enable
      \arg        ENET_MTL_EST_INT_IEHSIE: interrupt enable for HLBS
      \arg        ENET_MTL_EST_INT_IEHFIE: interrupt enable for HLBF
      \arg        ENET_MTL_EST_INT_IEBEIE: interrupt enable for BTR error
      \arg        ENET_MTL_EST_INT_IECCIE: interrupt enable for switch enable
      \arg        ENET_MTL_RXP_INT_NVEOVIE: number of valid entries overflow interrupt enable
      \arg        ENET_MTL_RXP_INT_NPEOVIE: number of parsable entries overflow interrupt enable
      \arg        ENET_MTL_RXP_INT_FOOVIE: frame offset overflow interrupt enable
      \arg        ENET_MTL_RXP_INT_PDRFIE: packet drop due to RF interrupt enable
      \arg        ENET_MTL_ECC_INT_RPCEIE: Rx parser memory correctable error interrupt enable
      \arg        ENET_MTL_ECC_INT_ECEIE: EST memory correctable error interrupt enable
      \arg        ENET_MTL_ECC_INT_RXCEIE: Rx memory correctable error interrupt enable
      \arg        ENET_MTL_ECC_INT_TXCEIE: Tx memory correctable error interrupt enable
      \arg        ENET_MTL_Q0_INT_RXOIE: receive queue 0 overflow interrupt enable
      \arg        ENET_MTL_Q0_INT_ABPSIE: queue 0 average bits per slot interrupt enable
      \arg        ENET_MTL_Q0_INT_TXUIE: transmit queue 0 underflow interrupt enable
      \arg        ENET_MTL_Q1_INT_RXOIE: receive queue 1 overflow interrupt enable
      \arg        ENET_MTL_Q1_INT_ABPSIE: queue 1 average bits per slot interrupt enable
      \arg        ENET_MTL_Q1_INT_TXUIE: transmit queue 1 underflow interrupt enable
      \arg        ENET_DMA_CH0_INT_TIE: channel 0 transmit interrupt enable
      \arg        ENET_DMA_CH0_INT_TXSEIE: channel 0 transmit process stopped interrupt enable
      \arg        ENET_DMA_CH0_INT_TBUEIE: channel 0 transmit buffer unavailable interrupt enable
      \arg        ENET_DMA_CH0_INT_RIE: channel 0 receive interrupt enable
      \arg        ENET_DMA_CH0_INT_RBUEIE: channel 0 receive buffer unavailable interrupt enable
      \arg        ENET_DMA_CH0_INT_RSEIE: channel 0 receive process stopped interrupt enable
      \arg        ENET_DMA_CH0_INT_RWTEIE: channel 0 receive watchdog timeout interrupt enable
      \arg        ENET_DMA_CH0_INT_ETIE: channel 0 early transmit interrupt enable
      \arg        ENET_DMA_CH0_INT_ERIE: channel 0 early receive interrupt enable
      \arg        ENET_DMA_CH0_INT_FBEEIE: channel 0 fatal bus error interrupt enable
      \arg        ENET_DMA_CH0_INT_CDEEIE: channel 0 the descriptor error interrupt enable
      \arg        ENET_DMA_CH0_INT_AIE: channel 0 abnormal interrupt summary enable
      \arg        ENET_DMA_CH0_INT_NIE: channel 0 normal interrupt summary enable
      \arg        ENET_DMA_CH1_INT_TIE: channel 1 transmit interrupt enable
      \arg        ENET_DMA_CH1_INT_TXSEIE: channel 1 transmit process stopped interrupt enable
      \arg        ENET_DMA_CH1_INT_TBUEIE: channel 1 transmit buffer unavailable interrupt enable
      \arg        ENET_DMA_CH1_INT_RIE: channel 1 receive interrupt enable
      \arg        ENET_DMA_CH1_INT_RBUEIE: channel 1 receive buffer unavailable interrupt enable
      \arg        ENET_DMA_CH1_INT_RSEIE: channel 1 receive process stopped interrupt enable
      \arg        ENET_DMA_CH1_INT_RWTEIE: channel 1 receive watchdog timeout interrupt enable
      \arg        ENET_DMA_CH1_INT_ETIE: channel 1 early transmit interrupt enable
      \arg        ENET_DMA_CH1_INT_ERIE: channel 1 early receive interrupt enable
      \arg        ENET_DMA_CH1_INT_FBEEIE: channel 1 fatal bus error interrupt enable
      \arg        ENET_DMA_CH1_INT_CDEEIE: channel 1 the descriptor error interrupt enable
      \arg        ENET_DMA_CH1_INT_AIE: channel 1 abnormal interrupt summary enable
      \arg        ENET_DMA_CH1_INT_NIE: channel 1 normal interrupt summary enable
    \param[out] none
    \retval     none
*/
void enet_interrupt_disable(enet_int_enum enet_int)
{
    uint32_t reg_type;
    reg_type = ((uint32_t)enet_int >> 6U);
    if((reg_type == MMC_RX_INTERRUPT_MASK_REG_OFFSET) || (reg_type == MMC_TX_INTERRUPT_MASK_REG_OFFSET) || (reg_type == MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET) || \
      (reg_type == MMC_FPE_TX_INTERRUPT_MASK_REG_OFFSET) || (reg_type == MMC_FPE_RX_INTERRUPT_MASK_REG_OFFSET)){
      /* INTMSK register interrupt */
      ENET_REG_VAL(enet_int) |= BIT(ENET_BIT_POS(enet_int));
      } else {
        /* INTEN register interrupt */
        ENET_REG_VAL(enet_int) &= ~ BIT(ENET_BIT_POS(enet_int));
      }
}

/*!
    \brief    get ENET MAC/MMC/MTL/DMA interrupt flag
    \param[in]  int_flag: ENET interrupt flag, refer to enet_int_flag_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_DMA_CH0_INT_FLAG_TI: channel 0 transmit status flag
      \arg        ENET_MAC_INT_FLAG_PHYIS: PHY interrupt status flag
      \arg        ENET_MAC_INT_FLAG_PMTIS: PMT interrupt status flag
      \arg        ENET_MAC_INT_FLAG_LPIIS: LPI Interrupt status flag
      \arg        ENET_MAC_INT_FLAG_MMCIS: MMC Interrupt status flag
      \arg        ENET_MAC_INT_FLAG_MMCRXIS: MMC receive interrupt status flag
      \arg        ENET_MAC_INT_FLAG_MMCTXIS: MMC transmit interrupt status flag
      \arg        ENET_MAC_INT_FLAG_MMCRXIPIS: MMC receive checksum offload interrupt status flag
      \arg        ENET_MAC_INT_FLAG_TSIS: timestamp interrupt status flag
      \arg        ENET_MAC_INT_FLAG_TXSTSIS: transmit status flag
      \arg        ENET_MAC_INT_FLAG_RXSTSIS: receive status interrupt flag
      \arg        ENET_MAC_INT_FLAG_FPEIS: frame preemption interrupt status flag
      \arg        ENET_MAC_INT_FLAG_MDIOIS: MDIO interrupt status flag
      \arg        ENET_MAC_INT_FLAG_MFTIS: MMC FPE transmit interrupt status flag
      \arg        ENET_MAC_INT_FLAG_MFEIS: MMC FPE receive Interrupt status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_ATPES: application transmit interface parity checker status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_RDPES: read descriptor parity checker error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_MPES: MTL data path parity checker error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_MTSPES: MTL Tx status data path parity checker error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_ARPES: application receive interface data path parity error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_CWPES: CSR write data path parity checker error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_TTES: Tx FSM timeout Error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_RTES: application transmit interface parity checker status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_ATES: APP FSM timeout error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_PTES: PTP FSM timeout error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_MSTTES: master read / write timeout error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_FSMPES: FSM state parity error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_MTBUPES: MAC TBU data path parity checker error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_MTFCPES: MAC TFC data path parity checker error status flag
      \arg        ENET_MAC_DPP_FSM_INT_FLAG_MRWCPES: MTL RWC data path parity checker error status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXGBPKTIS: MMC receive good bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXGBOCTIS: MMC receive good bad octet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXGOCTIS: MMC receive good octet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXBCGPIS: MMC receive broadcast good packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXMCGPIS: MMC receive multicast good packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXCRCERPIS: MMC receive crc error packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXALGNERPIS: MMC receive alignment error packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXRUNTPIS: MMC receive runt packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXJABERPIS: MMC receive jabber error packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXUSIZEGPIS: MMC receive undersize good packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXOSIZEGPIS: MMC receive oversize good packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RX64OCTGBPIS: MMC receive 64 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RX65T127OCTGBPIS: MMC receive 65 to 127 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RX128T255OCTGBPIS: MMC receive 128 to 255 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RX256T511OCTGBPIS: MMC receive 256 to 511 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RX512T1023OCTGBPIS: MMC receive 512 to 1023 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RX1024TMAXOCTGBPIS: MMC receive 1024 to maximum octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXUCGPIS: MMC receive unicast good packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXLENERPIS: MMC receive length error packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXORANGEPIS: MMC receive out of range error packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXPAUSPIS: MMC receive pause counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXFOVPIS: MMC receive FIFO overflow packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXVLANGBPIS: MMC receive VLAN good bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXWDOGPIS: MMC receive watchdog error bad packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXRCVERRPIS: MMC receive error packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXCTRLPIS: MMC receive control packet counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXLPIUSCIS: MMC receive LPI microsecond counter interrupt status flag
      \arg        ENET_MMC_RX_INT_FLAG_RXLPITRCIS: MMC receive LPI transition counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXGBOCTIS: MMC transmit good bad octet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXGBPKTIS: MMC transmit good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXBCGPIS: MMC transmit broadcast good packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXMCGPIS: MMC transmit multicast good packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TX64OCTGBPIS: MMC transmit 64 Octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TX65T127OCTGBPIS: MMC transmit 65 to 127 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TX128T255OCTGBPIS: MMC transmit 128 to 255 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TX256T511OCTGBPIS: MMC transmit 256 to 511 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TX512T1023OCTGBPIS: MMC transmit 512 to 1023 octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TX1024TMAXOCTGBPIS: MMC transmit 1024 to maximum octet good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXUCGBPIS: MMC transmit unicast good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXMCGBPIS: MMC transmit multicast good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXBCGBPIS: MMC transmit broadcast good bad packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXUFLOWERPIS: MMC transmit underflow error packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXSCOLGPIS: MMC transmit single collision good packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXMCOLGPIS: MMC transmit multiple collision good packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXDEFPIS: MMC transmit deferred packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXLATCOLPIS: MMC transmit late collision packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXEXCOLPIS: MMC transmit excessive collision packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXCARERPIS: MMC transmit carrier error packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXGOCTIS: MMC transmit good octet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXGPKTIS: MMC transmit good packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXEXDEFPIS: MMC transmit excessive deferral packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXPAUSPIS: MMC transmit pause packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXVLANGPIS: MMC transmit VLAN good packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXOSIZEGPIS: MMC transmit oversize good packet counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXLPIUSCIS: MMC transmit LPI microsecond counter interrupt status flag
      \arg        ENET_MMC_TX_INT_FLAG_TXLPITRCIS: MMC transmit LPI transition counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4GPIS: MMC receive IPV4 good packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4HERPIS: MMC receive IPV4 header error packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4NOPAYPIS: MMC receive IPV4 no payload packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4FRAGPIS: MMC receive IPV4 fragmented packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4UDSBLPIS: MMC receive IPV4 UDP checksum disabled packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV6GPIS: MMC receive IPV6 good packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV6HERPIS: MMC receive IPV6 header error packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV6NOPAYPIS: MMC receive IPV6 no payload packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXUDPGPIS: MMC receive UDP good packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXUDPERPIS: MMC receive UDP error packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXTCPGPIS: MMC receive TCP good packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXTCPERPIS: MMC receive TCP error packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXICMPGPIS: MMC receive ICMP good packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXICMPERPIS: MMC receive ICMP error packet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4GOIS: MMC receive IPV4 good octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4HEROIS: MMC receive IPV4 header error octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4NOPAYOIS: MMC receive IPV4 no payload octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4FRAGOIS: MMC receive IPV4 fragmented octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV4UDSBLOIS: MMC receive IPV4 UDP checksum disabled octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV6GOIS: MMC receive IPV6 good octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV6HEROIS: MMC receive IPV6 header error octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXIPV6NOPAYOIS: MMC receive IPV6 no payload octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXUDPGOIS: MMC receive UDP good octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXUDPEROIS: MMC receive UDP error octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXTCPGOIS: MMC receive TCP good octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXTCPEROIS: MMC receive TCP error octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXICMPGOIS: MMC receive ICMP good octet counter interrupt status flag
      \arg        ENET_MMC_IPC_RX_INT_FLAG_RXICMPEROIS: MMC receive ICMP error octet counter interrupt status flag
      \arg        ENET_MMC_FPE_TX_INT_FLAG_FCIS: MMC Tx FPE fragment counter interrupt status flag
      \arg        ENET_MMC_FPE_TX_INT_FLAG_HRCIS: MMC Tx hold request counter interrupt status flag
      \arg        ENET_MMC_FPE_RX_INT_FLAG_PAECIS: MMC Rx packet assembly error counter interrupt status flag
      \arg        ENET_MMC_FPE_RX_INT_FLAG_PSECIS: MMC Rx packet SMD error counter interrupt status flag
      \arg        ENET_MMC_FPE_RX_INT_FLAG_PAOCIS: MMC Rx packet assembly OK counter interrupt status flag
      \arg        ENET_MMC_FPE_RX_INT_FLAG_FCIS: MMC Rx FPE fragment counter interrupt status flag
      \arg        ENET_MTL_INT_FLAG_Q0IS: queue 0 interrupt status flag
      \arg        ENET_MTL_INT_FLAG_Q1IS: queue 1 interrupt status flag
      \arg        ENET_MTL_INT_FLAG_DBGIS: debug interrupt status flag
      \arg        ENET_MTL_INT_FLAG_ESTIS: EST (TAS- 802.1Qbv) interrupt status flag
      \arg        ENET_MTL_INT_FLAG_MTLPIS: MTL Rx parser interrupt status flag
      \arg        ENET_MTL_RXP_INT_FLAG_NVEOVIS: number of valid entries overflow interrupt status flag
      \arg        ENET_MTL_RXP_INT_FLAG_NPEOVIS: number of parsable entries overflow interrupt status flag
      \arg        ENET_MTL_RXP_INT_FLAG_FOOVIS: frame offset overflow interrupt status flag
      \arg        ENET_MTL_RXP_INT_FLAG_PDRFIS: packet drop due to RF interrupt status flag
      \arg        ENET_MTL_SAFETY_INT_FLAG_MECIS: MTL ECC correctable error interrupt status flag
      \arg        ENET_MTL_SAFETY_INT_FLAG_MEUIS: MTL ECC uncorrectable error interrupt status flag
      \arg        ENET_MTL_ECC_INT_FLAG_TXCES: MTL Tx memory correctable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_TXAMS: MTL Tx memory address mismatch status flag
      \arg        ENET_MTL_ECC_INT_FLAG_TXUES: MTL Tx memory uncorrectable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RXCES: MTL Rx memory correctable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RXAMS: MTL Rx memory address mismatch status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RXUES: MTL Rx memory uncorrectable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_ECES: MTL EST correctable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_EAMS: MTL EST address mismatch status flag
      \arg        ENET_MTL_ECC_INT_FLAG_EUES: MTL EST uncorrectable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RPCES: MTL Rx Parser memory correctable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RPAMS: MTL Rx Parser memory address mismatch status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RPUES: MTL Rx Parser memory uncorrectable error status flag
      \arg        ENET_MTL_Q0_INT_FLAG_RXOVFIS: receive queue 0 overflow status flag
      \arg        ENET_MTL_Q0_INT_FLAG_ABPSIS: queue 0 average bits per slot status flag
      \arg        ENET_MTL_Q0_INT_FLAG_TQU: transmit queue 0 underflow status flag
      \arg        ENET_MTL_Q1_INT_FLAG_RXOVFIS: receive queue 1 overflow status flag
      \arg        ENET_MTL_Q1_INT_FLAG_ABPSIS: queue 1 average bits per slot status flag
      \arg        ENET_MTL_Q1_INT_FLAG_TQU: transmit queue 1 underflow status flag
      \arg        ENET_DMA_INT_FLAG_DC0IS: DMA channel 0 interrupt status flag
      \arg        ENET_DMA_INT_FLAG_DC1IS: DMA channel 1 interrupt status flag
      \arg        ENET_DMA_INT_FLAG_MTLIS: MTL interrupt status flag
      \arg        ENET_DMA_INT_FLAG_MACIS: MAC interrupt status flag
      \arg        ENET_DMA_SAFETY_INT_FLAG_DECIS: DMA ECC correctable error interrupt status flag
      \arg        ENET_DMA_SAFETY_INT_FLAG_DEUIS: DMA ECC uncorrectable error interrupt status flag
      \arg        ENET_DMA_SAFETY_INT_FLAG_MSCIS: MTL safety correctable error interrupt status flag
      \arg        ENET_DMA_SAFETY_INT_FLAG_MSUIS: MTL safety uncorrectable error interrupt status flag
      \arg        ENET_DMA_SAFETY_INT_FLAG_MCSIS: MAC safety uncorrectable error interrupt status flag
      \arg        ENET_DMA_CH0_INT_FLAG_TI: channel 0 transmit status flag
      \arg        ENET_DMA_CH0_INT_FLAG_TPS: channel 0 transmit process stopped status flag
      \arg        ENET_DMA_CH0_INT_FLAG_TBU: channel 0 transmit buffer unavailable status flag
      \arg        ENET_DMA_CH0_INT_FLAG_RI: channel 0 receive status flag
      \arg        ENET_DMA_CH0_INT_FLAG_RBU: channel 0 receive buffer unavailable status flag
      \arg        ENET_DMA_CH0_INT_FLAG_RPS: channel 0 receive process stopped status flag
      \arg        ENET_DMA_CH0_INT_FLAG_RWT: channel 0 receive watchdog timeout status flag
      \arg        ENET_DMA_CH0_INT_FLAG_ETI: channel 0 early transmit status flag
      \arg        ENET_DMA_CH0_INT_FLAG_ERIE: channel 0 early receive status flag
      \arg        ENET_DMA_CH0_INT_FLAG_FBE: channel 0 fatal bus error status flag
      \arg        ENET_DMA_CH0_INT_FLAG_CDE: channel 0 context descriptor error status flag
      \arg        ENET_DMA_CH0_INT_FLAG_AIE: channel 0 abnormal interrupt summary flag
      \arg        ENET_DMA_CH0_INT_FLAG_NIS: channel 0 normal interrupt summary flag
      \arg        ENET_DMA_CH1_INT_FLAG_TI: channel 1 transmit status flag
      \arg        ENET_DMA_CH1_INT_FLAG_TPS: channel 1 transmit process stopped status flag
      \arg        ENET_DMA_CH1_INT_FLAG_TBU: channel 1 transmit buffer unavailable status flag
      \arg        ENET_DMA_CH1_INT_FLAG_RI: channel 1 receive status flag
      \arg        ENET_DMA_CH1_INT_FLAG_RBU: channel 1 receive buffer unavailable status flag
      \arg        ENET_DMA_CH1_INT_FLAG_RPS: channel 1 receive process stopped status flag
      \arg        ENET_DMA_CH1_INT_FLAG_RWT: channel 1 receive watchdog timeout status flag
      \arg        ENET_DMA_CH1_INT_FLAG_ETI: channel 1 early transmit status flag
      \arg        ENET_DMA_CH1_INT_FLAG_ERIE: channel 1 early receive status flag
      \arg        ENET_DMA_CH1_INT_FLAG_FBE: channel 1 fatal bus error status flag
      \arg        ENET_DMA_CH1_INT_FLAG_CDE: channel 1 context descriptor error status flag
      \arg        ENET_DMA_CH1_INT_FLAG_AIE: channel 1 abnormal interrupt summary flag
      \arg        ENET_DMA_CH1_INT_FLAG_NIS: channel 1 normal interrupt summary flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus enet_interrupt_flag_get(enet_int_flag_enum int_flag)
{
    FlagStatus flag;

    if((uint32_t)RESET != (ENET_REG_VAL(int_flag) & BIT(ENET_BIT_POS(int_flag)))) {
        flag = SET;
    } else {
        flag = RESET;
    }
    return flag;
}

/*!
    \brief    clear ENET MTL/DMA interrupt flag
    \param[in]  int_flag_clear: clear ENET interrupt flag, refer to enet_int_flag_clear_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MTL_RXP_INT_FLAG_NVEOVIS_CLR: number of valid entries overflow interrupt status flag
      \arg        ENET_MTL_RXP_INT_FLAG_NPEOVIS_CLR: number of parsable entries overflow interrupt status
      \arg        ENET_MTL_RXP_INT_FLAG_FOOVIS_CLR: frame offset overflow interrupt status flag
      \arg        ENET_MTL_RXP_INT_FLAG_PDRFIS_CLR: packet drop due to RF interrupt status flag
      \arg        ENET_MTL_ECC_INT_FLAG_TXCES_CLR: MTL Tx memory correctable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_TXAMS_CLR: MTL Tx memory address mismatch status flag
      \arg        ENET_MTL_ECC_INT_FLAG_TXUES_CLR: MTL Tx memory uncorrectable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RXCES_CLR: MTL Rx memory correctable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RXAMS_CLR: MTL Rx memory address mismatch status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RXUES_CLR: MTL Rx memory uncorrectable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_ECES_CLR: MTL EST correctable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_EAMS_CLR: MTL EST address mismatch status flag
      \arg        ENET_MTL_ECC_INT_FLAG_EUES_CLR: MTL EST uncorrectable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RPCES_CLR: MTL Rx Parser memory correctable error status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RPAMS_CLR: MTL Rx Parser memory address mismatch status flag
      \arg        ENET_MTL_ECC_INT_FLAG_RPUES_CLR: MTL Rx Parser memory uncorrectable error status flag
      \arg        ENET_MTL_Q0_INT_FLAG_RXOVFIS_CLR: receive queue 0 overflow status flag
      \arg        ENET_MTL_Q0_INT_FLAG_ABPSIS_CLR: queue 0 average bits per slot status flag
      \arg        ENET_MTL_Q0_INT_FLAG_TQU_CLR: transmit queue 0 underflow status flag
      \arg        ENET_MTL_Q1_INT_FLAG_RXOVFIS_CLR: receive queue 1 overflow status flag
      \arg        ENET_MTL_Q1_INT_FLAG_ABPSIS_CLR: queue 1 average bits per slot status flag
      \arg        ENET_MTL_Q1_INT_FLAG_TQU_CLR: transmit queue 1 underflow status flag
      \arg        ENET_DMA_CH0_INT_FLAG_TI_CLR: channel 0 transmit status flag
      \arg        ENET_DMA_CH0_INT_FLAG_TPS_CLR: channel 0 transmit process stopped status flag
      \arg        ENET_DMA_CH0_INT_FLAG_TBU_CLR: channel 0 transmit buffer unavailable status flag
      \arg        ENET_DMA_CH0_INT_FLAG_RI_CLR: channel 0 receive status flag
      \arg        ENET_DMA_CH0_INT_FLAG_RBU_CLR: channel 0 receive buffer unavailable status flag
      \arg        ENET_DMA_CH0_INT_FLAG_RPS_CLR: channel 0 receive process stopped status flag
      \arg        ENET_DMA_CH0_INT_FLAG_RWT_CLR: channel 0 receive watchdog timeout status flag
      \arg        ENET_DMA_CH0_INT_FLAG_ETI_CLR: channel 0 early transmit status flag
      \arg        ENET_DMA_CH0_INT_FLAG_ERIE_CLR: channel 0 early receive status flag
      \arg        ENET_DMA_CH0_INT_FLAG_FBE_CLR: channel 0 fatal bus error status flag
      \arg        ENET_DMA_CH0_INT_FLAG_CDE_CLR: channel 0 context descriptor error status flag
      \arg        ENET_DMA_CH0_INT_FLAG_AIE_CLR: channel 0 abnormal interrupt summary flag
      \arg        ENET_DMA_CH0_INT_FLAG_NIS_CLR: channel 0 normal interrupt summary flag
      \arg        ENET_DMA_CH1_INT_FLAG_TI_CLR: channel 1 transmit status flag
      \arg        ENET_DMA_CH1_INT_FLAG_TPS_CLR: channel 1 transmit process stopped status flag
      \arg        ENET_DMA_CH1_INT_FLAG_TBU_CLR: channel 1 transmit buffer unavailable status flag
      \arg        ENET_DMA_CH1_INT_FLAG_RI_CLR: channel 1 receive status flag
      \arg        ENET_DMA_CH1_INT_FLAG_RBU_CLR: channel 1 receive buffer unavailable status flag
      \arg        ENET_DMA_CH1_INT_FLAG_RPS_CLR: channel 1 receive process stopped status flag
      \arg        ENET_DMA_CH1_INT_FLAG_RWT_CLR: channel 1 receive watchdog timeout status flag
      \arg        ENET_DMA_CH1_INT_FLAG_ETI_CLR: channel 1 early transmit status flag
      \arg        ENET_DMA_CH1_INT_FLAG_ERIE_CLR: channel 1 early receive status flag
      \arg        ENET_DMA_CH1_INT_FLAG_FBE_CLR: channel 1 fatal bus error status flag
      \arg        ENET_DMA_CH1_INT_FLAG_CDE_CLR: channel 1 context descriptor error status flag
      \arg        ENET_DMA_CH1_INT_FLAG_AIE_CLR: channel 1 abnormal interrupt summary flag
      \arg        ENET_DMA_CH1_INT_FLAG_NIS_CLR: channel 1 normal interrupt summary flag
    \param[out] none
    \retval     none
*/
void enet_interrupt_flag_clear(enet_int_flag_clear_enum int_flag_clear)
{
    uint32_t reg_type;
    reg_type = ((uint32_t)int_flag_clear >> 6U);
    if(reg_type == MTL_ECC_INTERRUPT_STATUS_REG_OFFSET){
        /* MTL_ECC_INTERRUPT_STATUS register */
        ENET_REG_VAL(int_flag_clear) &= ~BIT(ENET_BIT_POS(int_flag_clear));
    } else {
        /* write 1 to the corresponding bit in other register, to clear it */
        ENET_REG_VAL(int_flag_clear) = BIT(ENET_BIT_POS(int_flag_clear));
    }
}

/*!
    \brief      enable the Tx MAC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_tx_mac_enable(void)
{
    ENET_MAC_CONFIGURATION |= ENET_MAC_CONFIGURATION_TE;
}

/*!
    \brief      disable the Tx MAC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_tx_mac_disable(void)
{
    ENET_MAC_CONFIGURATION &= ~ENET_MAC_CONFIGURATION_TE;
}

/*!
    \brief      enable the Rx MAC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_rx_mac_enable(void)
{
    ENET_MAC_CONFIGURATION |= ENET_MAC_CONFIGURATION_RE;
}

/*!
    \brief      disable the Rx MAC
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_rx_mac_disable(void)
{
    ENET_MAC_CONFIGURATION &= ~ENET_MAC_CONFIGURATION_RE;
}

/*!
    \brief    set the MAC extend configuration
    \param[in]  func: the function of MAC extend configuration
                only one parameter can be selected which are shown as below
      \arg        ENET_MISMATCH_ARP_PACKET_DROP_ENABLE: packet for which target protocol address does not match IPv4 address is dropped in the MTL layer
      \arg        ENET_MISMATCH_ARP_PACKET_DROP_DISABLE: when target protocol address does not match, packet is forwarded to MTL maintaining backward compatibility
      \arg        ENET_PACKET_DUPLICATION_ENABLE: the received packet with multicast/broadcast destination address is routed to multiple receive DMA channels
      \arg        ENET_PACKET_DUPLICATION_DISABLE: the received packet with multicast/broadcast destination address is not routed to multiple receive DMA channels
      \arg        ENET_USP_PACKET_DETECT_ENABLE: the MAC detects the slow protocol packets with unicast address of the station
      \arg        ENET_USP_PACKET_DETECT_DISABLE: the MAC detects only slow protocol packets with the slow protocol multicast address specified in the IEEE 802.3-2015, Section 5
      \arg        ENET_SLOW_PROTOCOL_DETECT_ENABLE: MAC processes the slow protocol packets (Ether Type 0x8809) and provides the slow protocol sub-type and code fields in Rx status
      \arg        ENET_SLOW_PROTOCOL_DETECT_DISABLE: the MAC forwards all error-free slow protocol packets to the application. The MAC considers such packets as normal Type packets
      \arg        ENET_CRC_CHECK_ENABLE: the MAC receiver always checks the CRC field in the received packets
      \arg        ENET_CRC_CHECK_DISABLE: the MAC receiver does not check the CRC field in the received packets
    \param[out] none
    \retval     none
*/
void enet_mac_extend_config(enet_extend_macconfig_enum func)
{
    /* inverted or not the specified siginal */
    switch(func) {
    case ENET_MISMATCH_ARP_PACKET_DROP_ENABLE:
        ENET_MAC_EXT_CONFIGURATION |= ENET_MAC_EXT_CONFIGURATION_APDIM;
        break;
    case ENET_PACKET_DUPLICATION_ENABLE:
        ENET_MAC_EXT_CONFIGURATION |= ENET_MAC_EXT_CONFIGURATION_PDC;
        break;
    case ENET_USP_PACKET_DETECT_ENABLE:
        ENET_MAC_EXT_CONFIGURATION |= ENET_MAC_EXT_CONFIGURATION_USP;
        break;
    case ENET_SLOW_PROTOCOL_DETECT_ENABLE:
        ENET_MAC_EXT_CONFIGURATION |= ENET_MAC_EXT_CONFIGURATION_SPEN;
        break;
    case ENET_CRC_CHECK_ENABLE:
        ENET_MAC_EXT_CONFIGURATION &= ~ENET_MAC_EXT_CONFIGURATION_DCRCC;
        break;
    case ENET_MISMATCH_ARP_PACKET_DROP_DISABLE:
        ENET_MAC_EXT_CONFIGURATION &= ~ENET_MAC_EXT_CONFIGURATION_APDIM;
        break;
    case ENET_PACKET_DUPLICATION_DISABLE:
        ENET_MAC_EXT_CONFIGURATION &= ~ENET_MAC_EXT_CONFIGURATION_PDC;
        break;
    case ENET_USP_PACKET_DETECT_DISABLE:
        ENET_MAC_EXT_CONFIGURATION &= ~ENET_MAC_EXT_CONFIGURATION_USP;
        break;
    case ENET_SLOW_PROTOCOL_DETECT_DISABLE:
        ENET_MAC_EXT_CONFIGURATION &= ~ENET_MAC_EXT_CONFIGURATION_SPEN;
        break;
    case ENET_CRC_CHECK_DISABLE:
        ENET_MAC_EXT_CONFIGURATION |= ENET_MAC_EXT_CONFIGURATION_DCRCC;
        break;
    default:
        break;
    }
}

/*!
    \brief      set the MAC extend Inter-Packet Gap
    \param[in]  packet_gap: the Inter-Packet Gap, must greater than 96 bit times in steps of 8 bit times: {EIPG, IPG}:
                104 - 2144
    \param[out] none
    \retval     none
*/
void enet_mac_extend_gap_set(uint32_t packet_gap)
{
    uint8_t bit_times;
    uint32_t ipg_val, eipg_val;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
if(NOT_EXT_PACKET_GAP_VALUE(packet_gap)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x001EU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* calculate the values corresponding to the IPG and EIPG fields */
    bit_times = (uint8_t)((packet_gap - EIPG_BIT_TIMES_START_VAL) / EIPG_BIT_TIMES_STEP);
    ipg_val = (uint32_t)(bit_times & BITS(0,2));
    eipg_val = (uint32_t)((bit_times & BITS(3,7)) >> EIPG_BIT_TIMES_POSITION);

    /* Set the appropriate register */
    ENET_MAC_CONFIGURATION &= ~ENET_MAC_CONFIGURATION_IPG;
    ENET_MAC_CONFIGURATION |= MAC_CONFIGURATION_IPG(ipg_val);
    ENET_MAC_EXT_CONFIGURATION &= ~ENET_MAC_EXT_CONFIGURATION_EIPG;
    ENET_MAC_EXT_CONFIGURATION |= MAC_EXT_CONFIGURATION_EIPG(eipg_val);
}
}

/*!
    \brief      set the MAC giant packet size limit
    \param[in]  size: the giant packet size,must be greater than or equal to 1,518 bytes. Any other programmed value is considered as 1,518 bytes.
                0 - 0x3FFF;
    \param[out] none
    \retval     none
*/
void enet_mac_giant_packetsize_set(uint32_t size)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
if(NOT_GIANT_PACKET_SIZE_VALUE(size)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x001FU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* set GPSLCE bit of ENET_MAC_CONFIGURATION register */
    ENET_MAC_CONFIGURATION |= ENET_MAC_CONFIGURATION_GPSLCE;
    
    /* set GPSL fields of MAC_EXT_CONFIGURATION register */
    ENET_MAC_EXT_CONFIGURATION &= ~ENET_MAC_EXT_CONFIGURATION_GPSL;
    ENET_MAC_EXT_CONFIGURATION |= MAC_EXT_CONFIGURATION_GPSL(size);
}
}

/*!
    \brief      set the MAC jabber programmable timeout
    \param[in]  val: the timeout value
                only one parameters can be selected which are shown as below
      \arg        ENET_JABBER_TIMEOUT_2KB: 2KB
      \arg        ENET_JABBER_TIMEOUT_3KB: 3KB
      \arg        ENET_JABBER_TIMEOUT_4KB: 4KB
      \arg        ENET_JABBER_TIMEOUT_5KB: 5KB
      \arg        ENET_JABBER_TIMEOUT_6KB: 6KB
      \arg        ENET_JABBER_TIMEOUT_7KB: 7KB
      \arg        ENET_JABBER_TIMEOUT_8KB: 8KB
      \arg        ENET_JABBER_TIMEOUT_9KB: 9KB
      \arg        ENET_JABBER_TIMEOUT_10KB: 10KB
      \arg        ENET_JABBER_TIMEOUT_11KB: 11KB
      \arg        ENET_JABBER_TIMEOUT_12KB: 12KB
      \arg        ENET_JABBER_TIMEOUT_13KB: 13KB
      \arg        ENET_JABBER_TIMEOUT_14KB: 14KB
      \arg        ENET_JABBER_TIMEOUT_15KB: 15KB
      \arg        ENET_JABBER_TIMEOUT_16KB: 16KB
    \param[out] none
    \retval     none
*/
void enet_mac_jabber_timeout_set(uint32_t val)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
if(NOT_ENET_JABBER_TIMEOUT(val)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0020U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* clear JD bit of ENET_MAC_CONFIGURATION register */
    ENET_MAC_CONFIGURATION &= ~ENET_MAC_CONFIGURATION_JD;
    
    /* set JTO fields and PJE bit of MAC_WATCHDOG_TIMEOUT register */
    ENET_MAC_WATCHDOG_TIMEOUT &= ~ENET_MAC_WATCHDOG_TIMEOUT_JTO;
    ENET_MAC_WATCHDOG_TIMEOUT |= val | ENET_MAC_WATCHDOG_TIMEOUT_PJE;
}
}

/*!
    \brief      set the MAC watchdog programmable timeout
    \param[in]  val: the timeout value
                only one parameters can be selected which are shown as below
      \arg        ENET_WATCHDOG_TIMEOUT_2KB: 2KB
      \arg        ENET_WATCHDOG_TIMEOUT_3KB: 3KB
      \arg        ENET_WATCHDOG_TIMEOUT_4KB: 4KB
      \arg        ENET_WATCHDOG_TIMEOUT_5KB: 5KB
      \arg        ENET_WATCHDOG_TIMEOUT_6KB: 6KB
      \arg        ENET_WATCHDOG_TIMEOUT_7KB: 7KB
      \arg        ENET_WATCHDOG_TIMEOUT_8KB: 8KB
      \arg        ENET_WATCHDOG_TIMEOUT_9KB: 9KB
      \arg        ENET_WATCHDOG_TIMEOUT_10KB: 10KB
      \arg        ENET_WATCHDOG_TIMEOUT_11KB: 11KB
      \arg        ENET_WATCHDOG_TIMEOUT_12KB: 12KB
      \arg        ENET_WATCHDOG_TIMEOUT_13KB: 13KB
      \arg        ENET_WATCHDOG_TIMEOUT_14KB: 14KB
      \arg        ENET_WATCHDOG_TIMEOUT_15KB: 15KB
      \arg        ENET_WATCHDOG_TIMEOUT_16KB: 16KB
    \param[out] none
    \retval     none
*/
void enet_mac_watchdog_timeout_set(uint32_t val)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
if(NOT_ENET_WATCHDOG_TIMEOUT(val)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0021U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* clear WD bit of ENET_MAC_CONFIGURATION register */
    ENET_MAC_CONFIGURATION &= ~ENET_MAC_CONFIGURATION_WD;

    /* set WTO fields and PWE bit of MAC_WATCHDOG_TIMEOUT register */
    ENET_MAC_WATCHDOG_TIMEOUT &= ~ENET_MAC_WATCHDOG_TIMEOUT_WTO;
    ENET_MAC_WATCHDOG_TIMEOUT |= val | ENET_MAC_WATCHDOG_TIMEOUT_PWE;
}
}

/*!
    \brief      check the mac version
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_mac_version_check(void)
{
    uint32_t version;
    ErrStatus status;

    version = ENET_MAC_VERSION;
    if(MAC_VERSION == version){
        status = SUCCESS;
    } else {
        status = ERROR;
    }
    return status;
}

/*!
    \brief    put registers value into the application buffer
    \param[in]  type: register type which will be get, refer to enet_registers_type_enum,
                only one parameter can be selected which is shown as below
      \arg        ALL_MAC_REG: get the registers within the offset scope between ENET_MAC_CONFIGURATION and ENET_MAC_PPS3_WIDTH
      \arg        ALL_MTL_REG: get the registers within the offset scope between ENET_MTL_OPERATION_MODE and ENET_MTL_DPP_ECC_EIC
      \arg        ALL_MTL_Q0_REG: get the registers within the offset scope between ENET_MTL_TXQ0_OPERATION_MODE and ENET_MTL_RXQ0_CONTROL
      \arg        ALL_MTL_Q1_REG: get the registers within the offset scope between ENET_MTL_TXQ1_OPERATION_MODE and ENET_MTL_RXQ1_CONTROL
      \arg        ALL_DMA_REG: get the registers within the offset scope between ENET_DMA_MODE and ENET_DMA_MODE
      \arg        ALL_DMA_CH0_REG: get the registers within the offset scope between ENET_DMA_CH0_CONTROL and ENET_DMA_CH0_RXP_ACCEPT_CNT
      \arg        ALL_DMA_CH1_REG: get the registers within the offset scope between ENET_DMA_CH1_CONTROL and ENET_DMA_CH1_RXP_ACCEPT_CNT
    \param[in]  num: the number of registers that the user want to get
    \param[out] preg: the application buffer pointer for storing the register value
    \retval     none
*/
void enet_registers_get(enet_registers_type_enum type, uint32_t *preg,
                        uint32_t num)
{
    uint32_t offset, max;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(preg)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0023U), ERR_PARAM_POINTER);
    } else if((ALL_MAC_REG == type) && NOT_ENET_MAC_REG_NUM(num)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else if((ALL_MTL_REG == type) && NOT_ENET_MTL_REG_NUM(num)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else if((ALL_MTL_Q0_REG == type) && NOT_ENET_MTL_Q0_REG_NUM(num)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else if((ALL_MTL_Q1_REG == type) && NOT_ENET_MTL_Q1_REG_NUM(num)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else if((ALL_DMA_REG == type) && NOT_ENET_DMA_REG_NUM(num)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else if((ALL_DMA_CH0_REG == type) && NOT_ENET_DMA_CH0_REG_NUM(num)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else if((ALL_DMA_CH1_REG == type) && NOT_ENET_DMA_CH1_REG_NUM(num)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    offset = (uint32_t)type;
    max = (uint32_t)type + num;

    for(; offset < max; offset++) {
        /* get value of the corresponding register */
        *preg = REG32((ENET) + enet_reg_tab[offset]);
        preg++;
    }
}
}

/*!
    \brief      set the mode and priority for Rx queue
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  queuemode: the mode of receive queue
      \arg        QUE_OP_MODE_DISABLE: queue not enabled
      \arg        QUE_OP_MODE_AVB_ENABLE: queue enabled for AV
      \arg        QUE_OP_MODE_ENABLE: queue enabled for Generic
    \param[in]  priosel: the priorities assigned to Rx queue
    \param[out] none
    \retval     none
*/
void enet_rxq_mode_set(enet_rxq_enum enet_rxq, enet_queopmode_enum queuemode, uint8_t priosel)
{
    switch(enet_rxq) {
    case RXQ0:
        /* set the mode for Rx queue 0 */
        ENET_MAC_RXQ_CTRL0 |= MAC_RXQ_CTRL0_RXQ0EN((uint32_t)queuemode);
        /* set the priority for Rx queue 0 */
        ENET_MAC_RXQ_CTRL2 |= MAC_RXQ_CTRL2_PSRQ0((uint8_t)priosel);
        break;
    case RXQ1:
        /* set the mode for Rx queue 1 */
        ENET_MAC_RXQ_CTRL0 |= MAC_RXQ_CTRL0_RXQ1EN((uint32_t)queuemode);
        /* set the priority for Rx queue 1 */
        ENET_MAC_RXQ_CTRL2 |= MAC_RXQ_CTRL2_PSRQ1((uint8_t)priosel);
        break;
    default:
        break;
    }
}

/*!
    \brief    enable the MAC address filter
    \param[in]  mac_addr: select which MAC address will be enable, refer to enet_macaddress_enum
      \arg        ENET_MAC_ADDRESS1: enable MAC address 1 filter
      \arg        ENET_MAC_ADDRESS2: enable MAC address 2 filter
    \param[out] none
    \retval     none
*/
void enet_address_filter_enable(enet_macaddress_enum mac_addr)
{
    REG32(ENET_ADDRH_BASE + (uint32_t)mac_addr) |= ENET_MAC_ADDRESS1_HIGH_AE;
}

/*!
    \brief    disable the MAC address filter
    \param[in]  mac_addr: select which MAC address will be disable, refer to enet_macaddress_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MAC_ADDRESS1: disable MAC address 1 filter
      \arg        ENET_MAC_ADDRESS2: disable MAC address 2 filter
    \param[out] none
    \retval     none
*/
void enet_address_filter_disable(enet_macaddress_enum mac_addr)
{
    REG32(ENET_ADDRH_BASE + (uint32_t)mac_addr) &= ~ENET_MAC_ADDRESS1_HIGH_AE;
}

/*!
    \brief    configure the MAC address filter
              note: this function must be called before the enet_mac_address_set and enet_address_filter_enable functions
    \param[in]  mac_addr: select which MAC address will be configured, refer to enet_macaddress_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MAC_ADDRESS1: configure MAC address 1 filter
      \arg        ENET_MAC_ADDRESS2: configure MAC address 2 filter
    \param[in]  addr_mask: select which MAC address bytes will be mask
                one or more parameters can be selected which are shown as below
      \arg        ENET_ADDRESS_MASK_NONE:  do not mask any bytes
      \arg        ENET_ADDRESS_MASK_BYTE0: mask ENET_MAC_ADDRESS1_LOW[7:0] bits
      \arg        ENET_ADDRESS_MASK_BYTE1: mask ENET_MAC_ADDRESS1_LOW[15:8] bits
      \arg        ENET_ADDRESS_MASK_BYTE2: mask ENET_MAC_ADDRESS1_LOW[23:16] bits
      \arg        ENET_ADDRESS_MASK_BYTE3: mask ENET_MAC_ADDRESS1_LOW[31:24] bits
      \arg        ENET_ADDRESS_MASK_BYTE4: mask ENET_MAC_ADDRESS1_HIGH[7:0] bits
      \arg        ENET_ADDRESS_MASK_BYTE5: mask ENET_MAC_ADDRESS1_HIGH[15:8] bits
    \param[in]  filter_type: select which MAC address filter type will be selected
                only one parameter can be selected which is shown as below
      \arg        ENET_ADDRESS_FILTER_SA: The MAC address is used to compared with the SA field of the received frame
      \arg        ENET_ADDRESS_FILTER_DA: The MAC address is used to compared with the DA field of the received frame
    \param[out] none
    \retval     none
*/
void enet_address_filter_config(enet_macaddress_enum mac_addr, uint32_t addr_mask, uint32_t filter_type)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
   if(NOT_ENET_ADDR_MASK(addr_mask)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0027U), ERR_PARAM_INVALID);
    } else if(NOT_ENET_MAC_FILTER_TYPE(filter_type)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0027U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* get the address filter register value which is to be configured */
    reg = REG32(ENET_ADDRH_BASE + (uint32_t)mac_addr);

    /* clear and configure the address filter register */
    reg &= ~(ENET_MAC_ADDRESS1_HIGH_MBC | ENET_MAC_ADDRESS1_HIGH_SA);
    reg |= (addr_mask | filter_type);
    REG32(ENET_ADDRH_BASE + (uint32_t)mac_addr) = reg;
}
}

/*!
    \brief    PHY interface configuration (configure SMA clock and reset PHY chip)
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_phy_config(void)
{
    uint32_t apb1clk;
    uint32_t reg;
    ErrStatus enet_state = ERROR;
    enet_phyconfig_struct phy_config = {PHY_ADDRESS, PHY_REG_BCR, 0, 0};

    /* clear the previous MDC clock */
    reg = ENET_MAC_MDIO_ADDRESS;
    reg &= ~ENET_MAC_MDIO_ADDRESS_CR;

    /* get the APB1 frequency */
    apb1clk = rcu_clock_freq_get(CK_APB1);

    /* configure MDC clock according to APB1 frequency range */
    if(ENET_RANGE(apb1clk, 20000000U, 35000000U)) {
        reg |= ENET_MDC_APB1_DIV16;
    } else if(ENET_RANGE(apb1clk, 35000000U, 60000000U)) {
        reg |= ENET_MDC_APB1_DIV26;
    } else if(ENET_RANGE(apb1clk, 60000000U, 100000000U)) {
        reg |= ENET_MDC_APB1_DIV42;
    } else if(ENET_RANGE(apb1clk, 100000000U, 150000000U)) {
        reg |= ENET_MDC_APB1_DIV62;
    } else if((ENET_RANGE(apb1clk, 150000000U, 160000000U)) || (160000000U == apb1clk)) {
        reg |= ENET_MDC_APB1_DIV102;
    } else {
        return enet_state;
    }

    ENET_MAC_MDIO_ADDRESS = reg;

    /* reset PHY */
    phy_config.PhyValue = PHY_RESET;
    if(ERROR == enet_phy_write_read(&phy_config, ENET_PHY_WRITE, DISABLE)) {
        return enet_state;
    }
    /* PHY reset need some time */
    ENET_DELAY(ENET_DELAY_TO);

    /* check whether PHY reset is complete */
    if(ERROR == enet_phy_write_read(&phy_config, ENET_PHY_READ, DISABLE)) {
        return enet_state;
    }

    /* PHY reset complete */
    if((uint16_t)RESET == (phy_config.PhyValue & PHY_RESET)) {
        enet_state = SUCCESS;
    }

    return enet_state;
}

/*!
    \brief      get the phy interface mode
    \param[in]  none
    \param[out] none
    \retval     enet_modetype_enum: RMII_MODE or MII_MODE
*/
enet_modetype_enum enet_phy_interface_get(void)
{
    enet_modetype_enum phy_mode;

    /* get the PHY configuration to update it */
    if((uint32_t)RESET == (ENET_MAC_HW_FEATURE0 & ENET_MAC_HW_FEATURE0_ACTPHYSEL)) {
        phy_mode = MII_MODE;
    } else {
        phy_mode = RMII_MODE;
    }

    return phy_mode;
}

/*!
    \brief    write to / read from a PHY register
    \param[in]  ConfigInfo: Contains information about the PHY to read or write to
    \param[in]  direction: phy operation diretion, refer to enet_phydirection_enum
      \arg        ENET_PHY_WRITE: write data to phy register
      \arg        ENET_PHY_READ:  read data from phy register
    \param[in]  Clause45Enable: Clause 45 PHY enable
      \arg        ENABLE: Clause 45 capable PHY is connected to MDIO
      \arg        DISABLE: Clause 22 capable PHY is connected to MDIO
    \param[out] ConfigInfo: 
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_phy_write_read(enet_phyconfig_struct *ConfigInfo,
                              enet_phydirection_enum direction,
                              ControlStatus Clause45Enable)
{
    ErrStatus enet_state = ERROR;
    uint32_t timeout = 0U;
    uint32_t phy_flag;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(ConfigInfo)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x002AU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_MDIO_ADDRESS &= ~(ENET_MAC_MDIO_ADDRESS_GB | ENET_MAC_MDIO_ADDRESS_PA | ENET_MAC_MDIO_ADDRESS_RDA | ENET_MAC_MDIO_ADDRESS_GOC_0 |
                               ENET_MAC_MDIO_ADDRESS_GOC_1 | ENET_MAC_MDIO_ADDRESS_C45E);


    /* if do the write operation, write value to the register */
    if(ENABLE == Clause45Enable) {
        ENET_MAC_MDIO_ADDRESS |= ENET_MAC_MDIO_ADDRESS_C45E | MAC_MDIO_ADDRESS_PA(ConfigInfo->PhyAddr) | MAC_MDIO_ADDRESS_RDA((uint32_t)ConfigInfo->DevAddr);
    } else {
        ENET_MAC_MDIO_ADDRESS |= MAC_MDIO_ADDRESS_PA(ConfigInfo->PhyAddr) | MAC_MDIO_ADDRESS_RDA(ConfigInfo->RegAddr);
    }
    /* if do the write operation, write value to the register */
    if(ENET_PHY_WRITE == direction) {
        if(ENABLE == Clause45Enable) {
            ENET_MAC_MDIO_DATA = MAC_MDIO_DATA_RA(ConfigInfo->RegAddr) | MAC_MDIO_DATA_GD(ConfigInfo->PhyValue);
        } else {
            ENET_MAC_MDIO_DATA = MAC_MDIO_DATA_GD(ConfigInfo->PhyValue);
        }
        ENET_MAC_MDIO_ADDRESS |= ENET_MAC_MDIO_ADDRESS_GOC_0;
    } else {
    /* if do the read operation, get value from the register */
        if(ENABLE == Clause45Enable) {
            ENET_MAC_MDIO_DATA |= MAC_MDIO_DATA_RA(ConfigInfo->RegAddr);
        } 
        ENET_MAC_MDIO_ADDRESS |= ENET_MAC_MDIO_ADDRESS_GOC_0 | ENET_MAC_MDIO_ADDRESS_GOC_1;
    }
    
    ENET_MAC_MDIO_ADDRESS |= ENET_MAC_MDIO_ADDRESS_GB;

    /* Wait for completion */
    do {
        phy_flag = (ENET_MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_GB);
        timeout++;
    } while(((uint32_t)RESET != phy_flag) && (ENET_DELAY_TO != timeout));

    /* write/read operation complete */
    if((uint32_t)RESET == (ENET_MAC_MDIO_ADDRESS & ENET_MAC_MDIO_ADDRESS_GB)) {
        enet_state = SUCCESS;
    }

    /* if do the read operation, get value from the register */
    if(ENET_PHY_READ == direction) {

        ConfigInfo->PhyValue = (uint16_t)ENET_MAC_MDIO_DATA;
    }
}
    return enet_state;
}

/*!
    \brief    enable the loopback function of PHY chip
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus enet_phyloopback_enable(void)
{
    ErrStatus phy_state;
    enet_phyconfig_struct phy_config = {PHY_ADDRESS, PHY_REG_BCR, 0, 0};

    /* get the PHY configuration to update it */
    phy_state = enet_phy_write_read(&phy_config, ENET_PHY_READ, DISABLE);
    if(ERROR != phy_state){
    /* enable the PHY loopback mode */
    phy_config.PhyValue |= PHY_LOOPBACK;
    /* update the PHY control register with the new configuration */
    phy_state = enet_phy_write_read(&phy_config, ENET_PHY_WRITE, DISABLE);
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    ENET_DELAY(PHY_DELAY_TO);

    return phy_state;
}

/*!
    \brief    disable the loopback function of PHY chip
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus enet_phyloopback_disable(void)
{
    ErrStatus phy_state;
    enet_phyconfig_struct phy_config = {PHY_ADDRESS, PHY_REG_BCR, 0, 0};

    /* get the PHY configuration to update it */
    phy_state = enet_phy_write_read(&phy_config, ENET_PHY_READ, DISABLE);
    if(ERROR != phy_state){
    /* disable the PHY loopback mode */
    phy_config.PhyValue &= (uint16_t)~PHY_LOOPBACK;

    /* update the PHY control register with the new configuration */
    phy_state = enet_phy_write_read(&phy_config, ENET_PHY_WRITE, DISABLE);
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    return phy_state;
}

/*!
    \brief    enable ENET forward feature
    \param[in]  feature: the feature of ENET forward mode
                only one parameter can be selected which are shown as below
      \arg        ENET_AUTO_PADCRC_DROP: the function of the MAC strips the Pad/FCS field on received frames
      \arg        ENET_TYPEFRAME_CRC_DROP: the function that FCS field(last 4 bytes) of frame will be dropped before forwarding
      \arg        ENET_RXQ0_FORWARD_ERRFRAMES: the forward error packets function is enabled in queue 0
      \arg        ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES: the forward undersized good packets function is enabled in queue 0
      \arg        ENET_RXQ1_FORWARD_ERRFRAMES: the forward error packets function is enabled in queue 1
      \arg        ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES:  the forward undersized good packets function is enabled in queue 1
    \param[out] none
    \retval     none
*/
void enet_forward_feature_enable(uint32_t feature)
{
    uint32_t mask;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FORWARD_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x002DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{

    mask = (feature & (~(ENET_RXQ0_FORWARD_ERRFRAMES | ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES | ENET_RXQ1_FORWARD_ERRFRAMES |
                         ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES)));
    ENET_MAC_CONFIGURATION |= mask;

    mask = (feature & (~(ENET_AUTO_PADCRC_DROP | ENET_TYPEFRAME_CRC_DROP | ENET_RXQ1_FORWARD_ERRFRAMES | ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES)));
    ENET_MTL_RXQ0_OPERATION_MODE |= (mask >> 2);

    mask = (feature & (~(ENET_AUTO_PADCRC_DROP | ENET_TYPEFRAME_CRC_DROP | ENET_RXQ0_FORWARD_ERRFRAMES | ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES)));
    ENET_MTL_RXQ1_OPERATION_MODE |= mask;
}
}

/*!
    \brief    disable ENET forward feature
    \param[in]  feature: the feature of ENET forward mode
                only one parameter can be selected which are shown as below
      \arg        ENET_AUTO_PADCRC_DROP: the function of the MAC strips the Pad/FCS field on received frames
      \arg        ENET_TYPEFRAME_CRC_DROP: the function that FCS field(last 4 bytes) of frame will be dropped before forwarding
      \arg        ENET_RXQ0_FORWARD_ERRFRAMES: the forward error packets function is enabled in queue 0
      \arg        ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES: the forward undersized good packets function is enabled in queue 0
      \arg        ENET_RXQ1_FORWARD_ERRFRAMES: the forward error packets function is enabled in queue 1
      \arg        ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES:  the forward undersized good packets function is enabled in queue 1
    \param[out] none
    \retval     none
*/
void enet_forward_feature_disable(uint32_t feature)
{
    uint32_t mask;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FORWARD_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x002EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    mask = (feature & (~(ENET_RXQ0_FORWARD_ERRFRAMES | ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES | ENET_RXQ1_FORWARD_ERRFRAMES |
                         ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES)));
    ENET_MAC_CONFIGURATION &= ~mask;

    mask = (feature & (~(ENET_AUTO_PADCRC_DROP | ENET_TYPEFRAME_CRC_DROP | ENET_RXQ1_FORWARD_ERRFRAMES | ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES)));
    ENET_MTL_RXQ0_OPERATION_MODE &= ~(mask >> 2);

    mask = (feature & (~(ENET_AUTO_PADCRC_DROP | ENET_TYPEFRAME_CRC_DROP | ENET_RXQ0_FORWARD_ERRFRAMES | ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES)));
    ENET_MTL_RXQ1_OPERATION_MODE &= ~mask;
}
}

/*!
    \brief      enable ENET fliter feature
    \param[in]  feature: the feature of ENET fliter mode
                one or more parameters can be selected which are shown as below
      \arg        ENET_L3L4_FILTER: filter  Layer 3 and Layer 4 filters function
      \arg        ENET_VLAN_FILTER: filter VLAN tag function
      \arg        ENET_SRC_FILTER: filter source address function
      \arg        ENET_SRC_FILTER_INVERSE: inverse source address filtering result function
      \arg        ENET_BROADCASTFRAMES_FILTER: filter all incoming broadcast frames function
      \arg        ENET_DEST_FILTER_INVERSE: inverse DA filtering result function
      \arg        ENET_MULTICAST_FILTER_PASS: pass all multicast frames function
      \arg        ENET_MULTICAST_FILTER_HASH_MODE: HASH multicast filter function
      \arg        ENET_UNICAST_FILTER_HASH_MODE: HASH unicast filter function
      \arg        ENET_FILTER_MODE_EITHER: HASH or perfect filter function
    \param[out] none
    \retval     none
*/
void enet_fliter_feature_enable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FILTER_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x002FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_PACKET_FILTER |= feature;
}
}

/*!
    \brief    disable ENET fliter feature
    \param[in]  feature: the feature of ENET fliter mode
                one or more parameters can be selected which are shown as below
      \arg        ENET_L3L4_FILTER: filter  Layer 3 and Layer 4 filters function
      \arg        ENET_VLAN_FILTER: filter VLAN tag function
      \arg        ENET_SRC_FILTER: filter source address function
      \arg        ENET_SRC_FILTER_INVERSE: inverse source address filtering result function
      \arg        ENET_BROADCASTFRAMES_FILTER: filter all incoming broadcast frames function
      \arg        ENET_DEST_FILTER_INVERSE: inverse DA filtering result function
      \arg        ENET_MULTICAST_FILTER_PASS: pass all multicast frames function
      \arg        ENET_MULTICAST_FILTER_HASH_MODE: HASH multicast filter function
      \arg        ENET_UNICAST_FILTER_HASH_MODE: HASH unicast filter function
      \arg        ENET_FILTER_MODE_EITHER: HASH or perfect filter function
    \param[out] none
    \retval     none
*/
void enet_fliter_feature_disable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FILTER_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0030U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_PACKET_FILTER &= ~feature;
}
}

/*!
    \brief      set the filter fail packets queue
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  type: the type of filter fail packet
                only one parameter can be selected which are shown as below
      \arg        MAC_UNICAST_ADDRESS_FLITER_FAIL: unicast address filter fail packets queuing enable
      \arg        MAC_MULTICAST_ADDRESS_FLITER_FAIL: multicast address filter fail packets queuing enable
      \arg        MAC_VLAN_TAG_FLITER_FAIL: VLAN tag filter fail packets queuing enable
    \param[out] none
    \retval     none
*/
void enet_fliterfail_queue_set(enet_rxq_enum enet_rxq, uint32_t type)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FILTER_FAIL_PACKET_TYPE(type)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0031U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(type) {
    case MAC_UNICAST_ADDRESS_FLITER_FAIL:
        ENET_MAC_RXQ_CTRL4 |= type;
        ENET_MAC_RXQ_CTRL4 |= MAC_UNICAST_ADDRESS_FLITER_FAIL_QUEUE(enet_rxq);
        break;
    case MAC_MULTICAST_ADDRESS_FLITER_FAIL:
        ENET_MAC_RXQ_CTRL4 |= type;
        ENET_MAC_RXQ_CTRL4 |= MAC_MULTICAST_ADDRESS_FLITER_FAIL_QUEUE(enet_rxq);
        break;
    case MAC_VLAN_TAG_FLITER_FAIL:
        ENET_MAC_RXQ_CTRL4 |= type;
        ENET_MAC_RXQ_CTRL4 |= MAC_VLAN_TAG_FLITER_FAIL_QUEUE(enet_rxq);
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the normal packets queue
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  type: the type of packet
                only one parameter can be selected which are shown as below
      \arg        MAC_AV_TAG_PACKET_QUEUE: AV untagged control packets queue
      \arg        MAC_PTP_PACKET_QUEUE: PTP packets queue
      \arg        MAC_UNTAGGED_PACKET_QUEUE: untagged packet queue
      \arg        MAC_MULTI_BROAD_PACKET_QUEUE: multicast and broadcast queue
      \arg        MAC_FPE_RESIDUE_PACKET_QUEUE: frame preemption residue queue
    \param[out] none
    \retval     none
*/
void enet_normal_frame_queue_set(enet_rxq_enum enet_rxq, enet_frame_type_enum type)
{
    if(MAC_FPE_RESIDUE_PACKET_QUEUE == type){
        if(RXQ1==enet_rxq) {
            ENET_MAC_RXQ_CTRL1 |= (uint32_t)((uint32_t)enet_rxq << (uint32_t)type);
        } else {
            /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
        }
    } else {
        ENET_MAC_RXQ_CTRL1 |= (uint32_t)((uint32_t)enet_rxq << (uint32_t)type);
    }
}

/*!
    \brief      set the normal packets queue related configuration
    \param[in]  config: the related configuration of packet queue
                only one parameter can be selected which are shown as below
      \arg        MAC_RXQ_MCBC_PRIORITY_ENABLE: multicast and broadcast queue enable
      \arg        MAC_RXQ_MCBC_PRIORITY_DISABLE: multicast and broadcast queue disable
      \arg        MAC_RXQ_PTPOE_AS_GENERIC_VLAN: VLAN Tagged PTPoE packets are routed as generic VLAN Tagged packet
      \arg        MAC_RXQ_PTPOE_TO_PTPQ: VLAN Tagged PTPoE packets are routed to Rx Queue specified by PTPQ field
      \arg        MAC_RXQ_PTPOE_TO_PSRQ: VLAN Tagged PTPoE packets are routed to only AV enabled Rx Queues based on PSRQ
      \arg        MAC_AV_TAG_PACKET_QUEUE_ENABLE: tagged AV control packets queuing enable
      \arg        MAC_AV_TAG_PACKET_QUEUE_DISABLE: tagged AV control packets queuing disable
      \arg        MAC_RXQ_MCBC_PRIORITY_OVER_ENABLE: over-riding MC-BC queue priority select enable
      \arg        MAC_RXQ_MCBC_PRIORITY_OVER_DISABLE: over-riding MC-BC queue priority select disable
      \arg        MAC_RXQ_TYPE_BASED_ENABLE: type field based Rx queuing enable
      \arg        MAC_RXQ_TYPE_BASED_DISABLE: type field based Rx queuing disable
    \param[out] none
    \retval     none
*/
void enet_normal_frame_queue_config(uint32_t config)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_PACKET_QUEUE_CFG(config)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0033U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(config) {
    case MAC_RXQ_MCBC_PRIORITY_ENABLE:
    case MAC_RXQ_PTPOE_TO_PTPQ:
    case MAC_RXQ_PTPOE_TO_PSRQ:
    case MAC_AV_TAG_PACKET_QUEUE_ENABLE:
    case MAC_RXQ_MCBC_PRIORITY_OVER_ENABLE:
    case MAC_RXQ_TYPE_BASED_ENABLE:
        ENET_MAC_RXQ_CTRL1 |= config;
        break;
    case MAC_RXQ_MCBC_PRIORITY_DISABLE:
    case MAC_RXQ_PTPOE_AS_GENERIC_VLAN:
    case MAC_AV_TAG_PACKET_QUEUE_DISABLE:
    case MAC_RXQ_MCBC_PRIORITY_OVER_DISABLE:
    case MAC_RXQ_TYPE_BASED_DISABLE:
        ENET_MAC_RXQ_CTRL1 &= config;
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the the FSM and interface timeout values
    \param[in]  type: the related type of the FSM and interface timeout
                one parameter can be selected which are shown as below
      \arg         ENET_LARGE_MODE_TIMEOUT: Large Mode Timeout Value
      \arg         ENET_NORMAL_MODE_TIMEOUT: Normal Mode Timeout Value
      \arg         ENET_CSR_CLOCK_VAL: CSR Clocks for 1us Tic
    \param[in]  val: the FSM and interface timeout values
                one parameter can be selected which are shown as below
      \arg         ENET_FSM_TIMEOUT_DISABLE: timer disabled
      \arg         ENET_FSM_TIMEOUT_1US: 1us
      \arg         ENET_FSM_TIMEOUT_4MS: 1.024ms (~4ms)
      \arg         ENET_FSM_TIMEOUT_16MS: 16.384ms (~16ms)
      \arg         ENET_FSM_TIMEOUT_64MS: 65.536ms (~64ms)
      \arg         ENET_FSM_TIMEOUT_256MS: 262.144ms (~256ms)
      \arg         ENET_FSM_TIMEOUT_1SEC: 1.048sec (~1sec)
      \arg         ENET_FSM_TIMEOUT_4SEC: 4.194sec (~4sec)
      \arg         ENET_FSM_TIMEOUT_16SEC: 16.777sec (~16sec)
      \arg         ENET_FSM_TIMEOUT_32SEC: 33.554sec (~32sec)
      \arg         ENET_FSM_TIMEOUT_64SEC: 67.108sec (~64sec)

    \param[out] none
    \retval     none
*/
void enet_fsm_timeout_set(enet_fsmtimeout_enum type, uint32_t val)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FSM_TIMEOUT_VALUE(val)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0034U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(type) {
    case ENET_LARGE_MODE_TIMEOUT:
        ENET_MAC_FSM_ACT_TIMER &= ~ENET_MAC_FSM_ACT_TIMER_LTMRMD;
        ENET_MAC_FSM_ACT_TIMER |= MAC_FSM_ACT_TIMER_LTMRMD(val);
        break;
    case ENET_NORMAL_MODE_TIMEOUT:
        ENET_MAC_FSM_ACT_TIMER &= ~ENET_MAC_FSM_ACT_TIMER_NTMRMD;
        ENET_MAC_FSM_ACT_TIMER |= MAC_FSM_ACT_TIMER_NTMRMD(val);
        break;
    case ENET_CSR_CLOCK_VAL:
        ENET_MAC_FSM_ACT_TIMER &= ~ENET_MAC_FSM_ACT_TIMER_TMR;
        ENET_MAC_FSM_ACT_TIMER |= MAC_FSM_ACT_TIMER_TMR(val);
        break;
    default:
        break;
    }
}
}

/*!
    \brief      start the Rx DMA
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_rx_dma_start(enet_dmach_enum dmach)
{
    if(DMACH0 == dmach) {
        ENET_DMA_CH0_RX_CONTROL |= ENET_DMA_CH_RX_CONTROL_SR;
    } else {
        ENET_DMA_CH1_RX_CONTROL |= ENET_DMA_CH_RX_CONTROL_SR;
    }
}

/*!
    \brief      start the Tx DMA
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_tx_dma_start(enet_dmach_enum dmach)
{

    if(DMACH0 == dmach) {
        ENET_DMA_CH0_TX_CONTROL |= ENET_DMA_CH_TX_CONTROL_ST;
    } else {
        ENET_DMA_CH1_TX_CONTROL |= ENET_DMA_CH_TX_CONTROL_ST;
    }
}

/*!
    \brief    generate the pause frame, ENET will send pause frame after enable transmit flow control
                this function only use in full-dulex mode
    \param[in]  none
    \param[out] none
    \retval     ErrStatus: ERROR or SUCCESS
*/
ErrStatus enet_pauseframe_generate(void)
{
    ErrStatus enet_state = ERROR;
    uint32_t temp;

    /* in full-duplex mode, must make sure this bit is 0 before writing register */
    temp = ENET_MAC_Q0_TX_FLOW_CTRL & ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA;
    if((uint32_t)RESET == temp) {
        ENET_MAC_Q0_TX_FLOW_CTRL |= ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA;
        enet_state = SUCCESS;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }
    return enet_state;
}

/*!
    \brief    configure the pause frame detect type
    \param[in]  detect: pause frame detect type
                only one parameter can be selected which is shown as below
      \arg        ENET_MAC0_AND_UNIQUE_ADDRESS_PAUSEDETECT: besides the unique multicast address, MAC can also
                                                            use the MAC0 address to detecting pause frame
      \arg        ENET_UNIQUE_PAUSEDETECT: only the unique multicast address for pause frame which is specified
                                           in IEEE802.3 can be detected
    \param[out] none
    \retval     none
*/
void enet_pauseframe_detect_config(uint32_t detect)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_PAUSEFRAME_DETECT(detect)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0038U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_RX_FLOW_CTRL &= ~ENET_MAC_RX_FLOW_CTRL_UP;
    ENET_MAC_RX_FLOW_CTRL |= (detect >> 8);
}
}

/*!
    \brief    configure the pause frame parameters
    \param[in]  pausetime: pause time in transmit pause control frame
    \param[in]  pause_threshold: the threshold of the pause timer for retransmitting frames automatically
                this value must make sure to be less than configured pause time
                only one parameter can be selected which is shown as below
      \arg        ENET_PAUSETIME_MINUS4: pause time minus 4 slot times
      \arg        ENET_PAUSETIME_MINUS28: pause time minus 28 slot times
      \arg        ENET_PAUSETIME_MINUS36: pause time minus 36 slot times
      \arg        ENET_PAUSETIME_MINUS144: pause time minus 144 slot times
      \arg        ENET_PAUSETIME_MINUS256: pause time minus 256 slot times
      \arg        ENET_PAUSETIME_MINUS256_2: pause time minus 256 slot times
    \param[out] none
    \retval     none
*/
void enet_pauseframe_config(uint16_t pausetime, uint32_t pause_threshold)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_PAUSE_THRESHOLD(pause_threshold)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0039U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_Q0_TX_FLOW_CTRL &= ~(ENET_MAC_Q0_TX_FLOW_CTRL_PT | ENET_MAC_Q0_TX_FLOW_CTRL_PLT);
    ENET_MAC_Q0_TX_FLOW_CTRL |= (MAC_Q0_TX_FLOW_CTRL_PT(pausetime) | pause_threshold);
}
}

/*!
    \brief    configure the threshold of the flow control(deactive and active threshold)
    \param[in]  rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  deactive: the threshold of the deactive flow control
                this value should always be less than active flow control value
                only one parameter can be selected which is shown as below
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_1K: threshold level is full minus 1 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_1_5K: threshold level is full minus 1.5 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_2K: threshold level is full minus 2 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_2_5K: threshold level is full minus 2.5 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_3K: threshold level is full minus 3 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_3_5K: threshold level is full minus 3.5 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_4K: threshold level is full minus 4 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_4_5K: threshold level is full minus 4.5 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_5K: threshold level is full minus 5 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_5_5K: threshold level is full minus 5.5 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_6K: threshold level is full minus 6 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_6_5K: threshold level is full minus 6.5 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_7K: threshold level is full minus 7 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_7_5K: threshold level is full minus 7.5 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_8K: threshold level is full minus 8 KB
      \arg        ENET_DEACTIVE_THRESHOLD_FULL_MINUS_8_5K: threshold level is full minus 8.5 KB
    \param[in]  active: the threshold of the active flow control
                only one parameter can be selected which is shown as below
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_1K: threshold level is full minus 1 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_1_5K: threshold level is full minus 1.5 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_2K: threshold level is full minus 2 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_2_5K: threshold level is full minus 2.5 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_3K: threshold level is full minus 3 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_3_5K: threshold level is full minus 3.5 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_4K: threshold level is full minus 4 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_4_5K: threshold level is full minus 4.5 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_5K: threshold level is full minus 5 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_5_5K: threshold level is full minus 5.5 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_6K: threshold level is full minus 6 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_6_5K: threshold level is full minus 6.5 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_7K: threshold level is full minus 7 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_7_5K: threshold level is full minus 7.5 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_8K: threshold level is full minus 8 KB
      \arg        ENET_ACTIVE_THRESHOLD_FULL_MINUS_8_5K: threshold level is full minus 8.5 KB
    \param[out] none
    \retval     none
*/
void enet_flowcontrol_threshold_config(enet_rxq_enum rxq, uint32_t deactive, uint32_t active)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_DEACTIVE_THRESHOLD(deactive)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x003AU), ERR_PARAM_INVALID);
    } else if(NOT_ENET_ACTIVE_THRESHOLD(active)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x003AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(rxq) {
    case RXQ0:
        ENET_MTL_RXQ0_OPERATION_MODE &= ~(ENET_MTL_RXQ0_OPERATION_MODE_RFD | ENET_MTL_RXQ0_OPERATION_MODE_RFA);
        ENET_MTL_RXQ0_OPERATION_MODE |= (deactive | active);
        break;
    case RXQ1:
        ENET_MTL_RXQ1_OPERATION_MODE &= ~(ENET_MTL_RXQ1_OPERATION_MODE_RFD | ENET_MTL_RXQ1_OPERATION_MODE_RFA);
        ENET_MTL_RXQ1_OPERATION_MODE |= (deactive | active);
        break;
    default:
        break;
    }
}
}

/*!
    \brief    enable ENET flow control feature
    \param[in]  feature: the feature of ENET flow control mode
                only one parameter can be selected which are shown as below
      \arg        ENET_ZERO_QUANTA_PAUSE: the automatic zero-quanta generation function
      \arg        ENET_TX_FLOWCONTROL: the flow control operation in the MAC
      \arg        ENET_RX_FLOWCONTROL: decoding function for the received pause frame and process it
      \arg        ENET_BACK_PRESSURE: back pressure operation in the MAC(only use in half-dulex mode)
    \param[out] none
    \retval     none
*/
void enet_flowcontrol_feature_enable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FLOWCONTROL_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x003BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if((uint32_t)RESET != (feature & ENET_RX_FLOWCONTROL)) {
        ENET_MAC_RX_FLOW_CTRL |= (feature >> 8);
    } else {
        if((uint32_t)RESET != (feature & ENET_ZERO_QUANTA_PAUSE)) {
            ENET_MAC_Q0_TX_FLOW_CTRL &= ~ENET_ZERO_QUANTA_PAUSE;
        }
        feature &= ~ENET_ZERO_QUANTA_PAUSE;
        ENET_MAC_Q0_TX_FLOW_CTRL |= feature;
    }
}
}

/*!
    \brief    disable ENET flow control feature
    \param[in]  feature: the feature of ENET flow control mode
                only one parameter can be selected which are shown as below
      \arg        ENET_ZERO_QUANTA_PAUSE: the automatic zero-quanta generation function
      \arg        ENET_TX_FLOWCONTROL: the flow control operation in the MAC
      \arg        ENET_RX_FLOWCONTROL: decoding function for the received pause frame and process it
      \arg        ENET_BACK_PRESSURE: back pressure operation in the MAC(only use in half-dulex mode)
    \param[out] none
    \retval     none
*/
void enet_flowcontrol_feature_disable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FLOWCONTROL_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x003CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if((uint32_t)RESET != (feature & ENET_RX_FLOWCONTROL)) {
        ENET_MAC_RX_FLOW_CTRL &= ~(feature >> 8);
    } else {
        if((uint32_t)RESET != (feature & ENET_ZERO_QUANTA_PAUSE)) {
            ENET_MAC_Q0_TX_FLOW_CTRL |= ENET_ZERO_QUANTA_PAUSE;
        }
        feature &= ~ENET_ZERO_QUANTA_PAUSE;
        ENET_MAC_Q0_TX_FLOW_CTRL &= ~feature;
    }
}
}

/*!
    \brief    config ENET frame preemption feature
    \param[in]  feature: the feature of ENET frame preemption
                only one parameter can be selected which are shown as below
      \arg        ENET_SEND_RESPOND_FRAME: send respond frame
      \arg        ENET_SEND_VERIFY_FRAME: send verify frame
      \arg        ENET_AUTOGENERATE_RESPOND_MPACKET: autogenerate respond mPacket on receiving verify mPacket is enabled
      \arg        ENET_TX_FRAME_PREEMPTION: Tx frame preemption is enabled
    \param[out] none
    \retval     none
*/
void enet_framepreemption_feature_enable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FRAMEPREEMPTION_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x003DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_FPE_CTRL_STS |= feature;
}
}

/*!
    \brief    disable ENET frame preemption feature
    \param[in]  feature: the feature of ENET frame preemption
                only one parameter can be selected which are shown as below
      \arg        ENET_AUTOGENERATE_RESPOND_MPACKET: autogenerate respond mPacket on receiving verify mPacket is disable
      \arg        ENET_TX_FRAME_PREEMPTION: Tx frame preemption is disable
    \param[out] none
    \retval     none
*/
void enet_framepreemption_feature_disable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_FRAMEPREEMPTION_FEATURE1(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x003EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_FPE_CTRL_STS &= ~feature;
}
}

/*!
    \brief      get the dma transmit/receive process state
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  direction: choose the direction of dma process which users want to check, refer to enet_dmadirection_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_DMA_TX: dma transmit process
      \arg        ENET_DMA_RX: dma receive process
    \param[out] none
    \retval     state of dma process, the value range shows below:
                  ENET_RX_STATE_STOPPED, ENET_RX_STATE_FETCHING, ENET_RX_STATE_WAITING,
                  ENET_RX_STATE_SUSPENDED, ENET_RX_STATE_CLOSING, ENET_RX_STATE_WRITING, ENET_RX_STATE_QUEUING,
                  ENET_TX_STATE_STOPPED, ENET_TX_STATE_FETCHING, ENET_TX_STATE_WAITING,
                  ENET_TX_STATE_READING, ENET_TX_STATE_SUSPENDED, ENET_TX_STATE_WRITING, ENET_TX_STATE_CLOSING
*/
uint32_t enet_dmaprocess_state_get(enet_dmach_enum dmach, enet_dmadirection_enum direction)
{
    uint32_t reval;
    reval = 0U;

    switch(dmach) {
    case DMACH0:
        reval = (uint32_t)(ENET_DMA_DEBUG_STATUS0 & (uint32_t)direction);
        break;
    case DMACH1:
        reval = (uint32_t)((ENET_DMA_DEBUG_STATUS0 & ((uint32_t)direction) << 8U) >> 8U);
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief      start/stop the DMA transmission/reception
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  direction: choose the direction of DMA process which users want to resume, refer to enet_dmadirection_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_DMA_TX: DMA transmit process
      \arg        ENET_DMA_RX: DMA receive process
    \param[in]  status: the status of dma Tx/Rx channel
                only one parameter can be selected which is shown as below:
      \arg        ENABLE: start the DMA transmission/reception
      \arg        DISABLE: stop the DMA transmission/reception
    \param[out] none
    \retval     none
*/
void enet_dmaprocess_config(enet_dmach_enum dmach, enet_dmadirection_enum direction, ControlStatus status)
{
    switch(dmach) {
    case DMACH0:
         if(ENET_DMA_TX == direction) {
            ENET_DMA_CH0_TX_CONTROL &= ~ENET_DMA_CH_TX_CONTROL_ST;
            ENET_DMA_CH0_TX_CONTROL |= (uint32_t)status;
        } else {
            ENET_DMA_CH0_RX_CONTROL &= ~ENET_DMA_CH_RX_CONTROL_SR;
            ENET_DMA_CH0_RX_CONTROL |= (uint32_t)status;
        }
        break;
    case DMACH1:
        if(ENET_DMA_TX == direction) {
            ENET_DMA_CH1_TX_CONTROL &= ~ENET_DMA_CH_TX_CONTROL_ST;
            ENET_DMA_CH1_TX_CONTROL |= (uint32_t)status;
        } else {
            ENET_DMA_CH1_RX_CONTROL &= ~ENET_DMA_CH_RX_CONTROL_SR;
            ENET_DMA_CH1_RX_CONTROL |= (uint32_t)status;
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      check and recover the Rx process
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_rxprocess_check_recovery(enet_dmach_enum dmach)
{
    uint32_t status;

    if(DMACH0 == dmach) {
        /* get DAV information of current RxDMA descriptor */
        status = dma_current_rxdesc->DES3;
        status &= ENET_NORMAL_RDES3_WF_OWN;
        /* if current descriptor is owned by DMA, but the descriptor address mismatches with
        receive descriptor address pointer updated by RxDMA controller */
        if((ENET_DMA_CH0_CURRENT_APP_RXDESC != ((uint32_t)dma_current_rxdesc)) &&
                (ENET_NORMAL_RDES3_WF_OWN == status)) {
            dma_current_rxdesc = (enet_descriptors_struct *)ENET_DMA_CH0_CURRENT_APP_RXDESC;
        }
    } else {
        /* get DAV information of current RxDMA descriptor */
        status = dma_current_rxdesc1->DES3;
        status &= ENET_NORMAL_RDES3_WF_OWN;
        /* if current descriptor is owned by DMA, but the descriptor address mismatches with
        receive descriptor address pointer updated by RxDMA controller */
        if((ENET_DMA_CH1_CURRENT_APP_RXDESC != ((uint32_t)dma_current_rxdesc1)) &&
                (ENET_NORMAL_RDES3_WF_OWN == status)) {
            dma_current_rxdesc1 = (enet_descriptors_struct *)ENET_DMA_CH1_CURRENT_APP_RXDESC;
        }
    }
}

/*!
    \brief    get the transmit/receive address of current descriptor, or current buffer, or descriptor table
    \param[in]  addr_get: choose the address which users want to get, refer to enet_desc_reg_enum
                only one parameter can be selected which is shown as below
    \arg        ENET_CH0_RX_DESC_TABLE: DMA channel 0 RX descriptor table
    \arg        ENET_CH1_RX_DESC_TABLE: DMA channel 1 RX descriptor table
    \arg        ENET_CH0_RX_DESC_TAIL: DMA channel 0 RX descriptor tail pointer
    \arg        ENET_CH1_RX_DESC_TAIL: DMA channel 1 RX descriptor tail pointer
    \arg        ENET_CH0_RX_CURRENT_DESC: DMA channel 0  current RX descriptor
    \arg        ENET_CH1_RX_CURRENT_DESC: DMA channel 1 current RX descriptor
    \arg        ENET_CH0_RX_CURRENT_BUFFER: DMA channel 0 current RX buffer
    \arg        ENET_CH1_RX_CURRENT_BUFFER: DMA channel 1 current RX buffer
    \arg        ENET_CH0_TX_DESC_TABLE: DMA channel 0 TX descriptor table
    \arg        ENET_CH1_TX_DESC_TABLE: DMA channel 1 TX descriptor table
    \arg        ENET_CH0_TX_DESC_TAIL: DMA channel 0 TX descriptor tail pointer
    \arg        ENET_CH1_TX_DESC_TAIL: DMA channel 1 TX descriptor tail pointer
    \arg        ENET_CH0_TX_CURRENT_DESC: DMA channel 0 current TX descriptor
    \arg        ENET_CH1_TX_CURRENT_DESC: DMA channel 1 current TX descriptor
    \arg        ENET_CH0_TX_CURRENT_BUFFER: DMA channel 0 current TX buffer
    \arg        ENET_CH1_TX_CURRENT_BUFFER: DMA channel 1 current TX buffer
    \param[out] none
    \retval     address value
*/
uint32_t enet_dma_desc_address_get(enet_desc_reg_enum addr_get)
{
    uint32_t reval;

    reval = REG32((ENET) + (uint32_t)addr_get);

    return reval;
}

/*!
    \brief    get the Tx or Rx descriptor information
    \param[in]  desc: the descriptor pointer which users want to get information
    \param[in]  info_get: the descriptor information type which is selected, refer to enet_descstate_enum
                only one parameter can be selected which is shown as below
      \arg        RXDESC_FRAME_LENGTH: the byte length of the received frame that was transferred to the buffer
      \arg        TXDESC_COLLISION_COUNT: the number of collisions occurred before the frame was transmitted
      \arg        RXDESC_BUFFER_1_ADDR: the buffer1 address of the Rx frame
      \arg        RXDESC_BUFFER_2_ADDR: the buffer2 address of the Rx frame
      \arg        TXDESC_BUFFER_1_ADDR: the buffer1 address of the Tx frame
      \arg        TXDESC_BUFFER_2_ADDR: the buffer2 address of the Tx frame
    \param[out] none
    \retval     descriptor information, if value is 0xFFFFFFFFU, means the false input parameter
*/
uint32_t enet_desc_information_get(enet_descriptors_struct *desc, enet_descstate_enum info_get)
{
    uint32_t reval = 0xFFFFFFFFU;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(desc)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0043U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(info_get) {
    case RXDESC_FRAME_LENGTH:
        reval = GET_RDES3_PL(desc->DES3);
        if(reval > 4U) {
            reval = reval - 4U;
        } else {
            reval = 0U;
        }

        break;
    case RXDESC_BUFFER_1_ADDR:
        reval = desc->buffer_address;
        break;
    case RXDESC_BUFFER_2_ADDR:
        reval = desc->DES1;
        break;
    case TXDESC_BUFFER_1_ADDR:
        reval = desc->buffer_address;
        break;
    case TXDESC_BUFFER_2_ADDR:
        reval = desc->DES1;
        break;
    case TXDESC_COLLISION_COUNT:
        reval = GET_TDES3_COCNT(desc->DES3);
        break;
    default:
        break;
    }
}
    return reval;

}

/*!
    \brief    get the number of missed/received frames during receiving
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] rxdma_received: pointer to the number of frames received by the Rx paeser
    \param[out] rxdma_drop: pointer to the number of frames missed by the RxDMA controller
    \retval     none
*/
void enet_missed_frame_counter_get(enet_dmach_enum dmach, uint32_t *rxdma_received, uint32_t *rxdma_drop)
{
    uint32_t temp_counter;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(rxdma_received)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0044U), ERR_PARAM_POINTER);
    } else if(NOT_VALID_POINTER(rxdma_drop)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0044U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0:
        temp_counter = ENET_DMA_CH0_MISS_FRAME_CNT;
        *rxdma_drop = GET_DMA_CH_MISS_FRAME_CNT_MSFC(temp_counter);
        temp_counter = ENET_DMA_CH0_RXP_ACCEPT_CNT;
        *rxdma_received = GET_DMA_CH_RXP_ACCEPT_CNT_RXPAC(temp_counter);
        break;
    case DMACH1:
        temp_counter = ENET_DMA_CH1_MISS_FRAME_CNT;
        *rxdma_drop = GET_DMA_CH_MISS_FRAME_CNT_MSFC(temp_counter);
        temp_counter = ENET_DMA_CH1_RXP_ACCEPT_CNT;
        *rxdma_received = GET_DMA_CH_RXP_ACCEPT_CNT_RXPAC(temp_counter);
        break;
    default:
        break;
    }
}
}

/*!
    \brief      get the overflow status of missed/received frame counter
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  counter: choose the counter of dma
                only one parameter can be selected which is shown as below, refer to enet_dmacounter_enum
      \arg        DMA_MISS_FRAME_COUNT: missed frame counter
      \arg        DMA_ACCEPT_FRAME_COUNT: received frame counter
    \retval     FlagStatus: SET or RESET
*/
FlagStatus enet_counter_overflow_status_get(enet_dmach_enum dmach, enet_dmacounter_enum counter)
{
    uint32_t temp_counter;
    FlagStatus flag;
    flag = RESET;

    switch(dmach) {
    case DMACH0:
        if(DMA_MISS_FRAME_COUNT == counter) {
            temp_counter = ENET_DMA_CH0_MISS_FRAME_CNT;
            if((uint32_t)RESET != (temp_counter & ENET_DMA_CH_MISS_FRAME_CNT_MFCO)){
                flag = SET;
            } else {
            /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }
        } else {
            temp_counter = ENET_DMA_CH0_RXP_ACCEPT_CNT;
            if((uint32_t)RESET != (temp_counter & ENET_DMA_CH_RXP_ACCEPT_CNT_RXPACOF)){
                flag = SET;
            } else {
            /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }
        }
        break;
    case DMACH1:
        if(DMA_MISS_FRAME_COUNT == counter) {
            temp_counter = ENET_DMA_CH1_MISS_FRAME_CNT;
            if((uint32_t)RESET != (temp_counter & ENET_DMA_CH_MISS_FRAME_CNT_MFCO)){
                flag = SET;
            } else {
            /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }
        } else {
            temp_counter = ENET_DMA_CH1_RXP_ACCEPT_CNT;
            if((uint32_t)RESET != (temp_counter & ENET_DMA_CH_RXP_ACCEPT_CNT_RXPACOF)){
                flag = SET;
            } else {
            /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }
        }
        break;
    default:
        break;
    }
    return flag;
}

/*!
    \brief      get the DMA slot number value
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] slot_num: the slot number value
    \retval     none
*/
uint16_t enet_dma_slot_value_get(enet_dmach_enum dmach)
{
    uint16_t slot_num = 0;

    switch(dmach) {
    case DMACH0:
            slot_num = (uint16_t)GET_REF_SLOT_NUMBER(ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS);
        break;
    case DMACH1:
            slot_num = (uint16_t)GET_REF_SLOT_NUMBER(ENET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS);
        break;
    default:
        break;
    }
    return slot_num;
}

/*!
    \brief      set the DMA slot check related value parameters
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  slot_interval: the slot interval value
    \param[out] none
    \retval     none
*/
void enet_dma_slot_interval_set(enet_dmach_enum dmach, uint16_t slot_interval)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_SLOT_INTERVAL_VALUE(slot_interval)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0047U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0:
            ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS &= ~ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_SIV;
            ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS |= DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_SIV(slot_interval);
        break;
    case DMACH1:
            ENET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS &= ~ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_SIV;
            ENET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS |= DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_SIV(slot_interval);
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the DMA slot check related fuction parameters
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  function: the related function
                one or more parameters can be selected which is shown as below
      \arg        ENET_DMA_ADVANCE_SLOT_CHECK: advance slot check function
      \arg        ENET_DMA_SLOT_COMPARISON: slot comparison function
    \param[in]  status: select whether the DMA slot check related fuction is enabled or disabled
                only one parameter can be selected which is shown as below:
      \arg        ENABLE: enable
      \arg        DISABLE: disable
    \param[out] none
    \retval     none
*/
void enet_dma_slot_config(enet_dmach_enum dmach, uint32_t function, ControlStatus status)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_SLOT_FUNCTION(function)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0048U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0:
        if(ENABLE == status) {
            ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS |= function;
        } else {
            ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS &= ~function;
        }
        break;
    case DMACH1:
        if(ENABLE == status) {
            ENET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS |= function;
        } else {
            ENET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS &= ~function;
        }
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the watchdog timeout for receive interrupt from the DMA
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  count_uint: the value of watchdog timer count units
                only one parameter can be selected which is shown as below
      \arg        ENET_RX_INT_WATCHDOG_TIMER_COUNT_256: 256 system clock cycles corresponding to one unit in RWT field
      \arg        ENET_RX_INT_WATCHDOG_TIMER_COUNT_512: 512 system clock cycles corresponding to one unit in RWT field
      \arg        ENET_RX_INT_WATCHDOG_TIMER_COUNT_1024: 1024 system clock cycles corresponding to one unit in RWT field
      \arg        ENET_RX_INT_WATCHDOG_TIMER_COUNT_2048: 2048 system clock cycles corresponding to one unit in RWT field
    \param[in]  count_val: the value of watchdog timer count
                           0-0xFF
    \param[out] none
    \retval     none
*/
void enet_dma_rxinterrupt_watchdog_timer_set(enet_dmach_enum dmach, uint32_t count_uint, uint8_t count_val)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_WATCHDOG_TIMER_COUNT_UNIT(count_uint)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0049U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0:
            ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER = count_uint | count_val;
        break;
    case DMACH1:
            ENET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER = count_uint | count_val;
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the DMA alternate receive buffer size
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  size: the DMA alternate receive buffer size
                           0-0x3F8
    \param[out] none
    \retval     none
*/
void enet_rxbuf_alternate_size_set(enet_dmach_enum dmach, uint16_t size)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_DMA_ALTER_RXBUF_SIZE(size)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x004AU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0:
            ENET_DMA_CH0_RX_CONTROL2 &= ~ENET_DMA_CH_RX_CONTROL2_ARBS;
            ENET_DMA_CH0_RX_CONTROL2 |= DMA_CH_RX_CONTROL2_ARBS(size);
        break;
    case DMACH1:
            ENET_DMA_CH1_RX_CONTROL2 &= ~ENET_DMA_CH_RX_CONTROL2_ARBS;
            ENET_DMA_CH1_RX_CONTROL2 |= DMA_CH_RX_CONTROL2_ARBS(size);
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the algorithm for Tx scheduling
    \param[in]  SchedAlgo: Tx scheduling algorithm
                only one parameter can be selected which is shown as below
      \arg        STRICT_PRIORITY_TX: strict priority algorithm
      \arg        WEIGHTED_ROUND_ROBIN: WRR algorithmt
    \param[out] none
    \retval     none
*/
void enet_schedalg_set(enet_txqalgotype_enum SchedAlgo)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_TX_ALGO_TYPE(SchedAlgo)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x004BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_OPERATION_MODE &= ~ENET_MTL_OPERATION_MODE_SCHALG;
    ENET_MTL_OPERATION_MODE |= (uint32_t)SchedAlgo;
}
}

/*!
    \brief      set the weight for Tx queue
    \param[in]  enet_txq: transmit queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1
    \param[in]  weight: the weight for this queue
    \param[out] none
    \retval     none
*/
void enet_txq_weight_set(enet_txq_enum enet_txq, uint32_t weight)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_MTL_TXQ_WEIGHT(weight)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x004CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(enet_txq) {
    case TXQ0:
        ENET_MTL_TXQ0_QUANTUM_WEIGHT = weight;
        break;
    case TXQ1:
        ENET_MTL_TXQ1_QUANTUM_WEIGHT = weight;
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the weight for Rx queue
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  weight: the weight for this queue
    \param[out] none
    \retval     none
*/
void enet_rxq_weight_set(enet_rxq_enum enet_rxq, uint32_t weight)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_MTL_RXQ_WEIGHT(weight)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x004DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(enet_rxq) {
    case RXQ0:
        ENET_MTL_RXQ0_CONTROL &= ~ENET_MTL_RXQ0_CONTROL_RXQ_WEGT ;
        ENET_MTL_RXQ0_CONTROL |= weight & ENET_MTL_RXQ0_CONTROL_RXQ_WEGT;
        break;
    case RXQ1:
        ENET_MTL_RXQ1_CONTROL &= ~ENET_MTL_RXQ0_CONTROL_RXQ_WEGT ;
        ENET_MTL_RXQ1_CONTROL |= weight & ENET_MTL_RXQ0_CONTROL_RXQ_WEGT;
        break;
    default:
        break;
    }
}
}

/*!
    \brief      config the arbitration for Rx queue
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  status: enable or disable
      \arg        ENABLE: enable
      \arg        DISABLE: disable

    \param[out] none
    \retval     none
*/
void enet_rxq_packet_arbitration_config(enet_rxq_enum enet_rxq, ControlStatus status)
{

    switch(enet_rxq) {
    case RXQ0:
        ENET_MTL_RXQ0_CONTROL &= ~ENET_MTL_RXQ0_CONTROL_RXQ_FRM_ARBIT;
        ENET_MTL_RXQ0_CONTROL |= MTL_RXQ_PACKET_ARBITRATION(status);
        break;
    case RXQ1:
        ENET_MTL_RXQ1_CONTROL &= ~ENET_MTL_RXQ1_CONTROL_RXQ_FRM_ARBIT;
        ENET_MTL_RXQ1_CONTROL |= MTL_RXQ_PACKET_ARBITRATION(status);
        break;
    default:
        break;
    }
}

/*!
    \brief      enable dynamic mapping for Rx queue
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[out] none
    \retval     none
*/
void enet_dynamic_mapping_set(enet_rxq_enum enet_rxq)
{
    switch(enet_rxq) {
    case RXQ0:
        ENET_MTL_RXQ_DMA_MAP0 |= ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH;
        break;
    case RXQ1:
        ENET_MTL_RXQ_DMA_MAP0 |= ENET_MTL_RXQ_DMA_MAP0_Q1DDMACH;
        break;
    default:
        break;
    }
}

/*!
    \brief      set the type, associated queue number and paket type
    \param[in]  reg_num: MAC_TMRQ_Regs selection
                only one parameter can be selected which is shown as below
      \arg        ENET_INDIR_ACCESS_MAC_TMRQ_REG0: MAC_TMRQ_Reg0
      \arg        ENET_INDIR_ACCESS_MAC_TMRQ_REG1: MAC_TMRQ_Reg1
      \arg        ENET_INDIR_ACCESS_MAC_TMRQ_REG2: MAC_TMRQ_Reg2
      \arg        ENET_INDIR_ACCESS_MAC_TMRQ_REG3: MAC_TMRQ_Reg3
      \arg        ENET_INDIR_ACCESS_MAC_TMRQ_REG4: MAC_TMRQ_Reg4
      \arg        ENET_INDIR_ACCESS_MAC_TMRQ_REG5: MAC_TMRQ_Reg5
      \arg        ENET_INDIR_ACCESS_MAC_TMRQ_REG6: MAC_TMRQ_Reg6
      \arg        ENET_INDIR_ACCESS_MAC_TMRQ_REG7: MAC_TMRQ_Reg7
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  typ_val: the type value of packet
    \param[in]  packet_type: packet type selection
                only one parameter can be selected which is shown as below
      \arg        PREEMPTION_PACKET: preemption packet
      \arg        EXPRESS_PACKET: express packet
    \param[out] none
    \retval     none
*/
ErrStatus enet_rxq_type_match_set(uint16_t reg_num, enet_rxq_enum enet_rxq, uint16_t typ_val, enet_packet_type_enum packet_type)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
    ErrStatus status = ERROR;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_MAC_TMRQ_REG_NUM(reg_num)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0050U), ERR_PARAM_INVALID);
    } else if(NOT_PACKET_TYPE(typ_val)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0050U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_INDIR_ACCESS_DATA &= ~ENET_MAC_INDIR_ACCESS_DATA_DATA;
    ENET_MAC_INDIR_ACCESS_DATA = MAC_TMRQ_REGS_TYP(typ_val) | MAC_TMRQ_REGS_TMRQ(enet_rxq) | MAC_TMRQ_REGS_PFEX(packet_type);
    
    ENET_MAC_INDIR_ACCESS_CTRL &= ~(ENET_MAC_INDIR_ACCESS_CTRL_COM | ENET_MAC_INDIR_ACCESS_CTRL_MSEL | ENET_MAC_INDIR_ACCESS_CTRL_AOFF | ENET_MAC_INDIR_ACCESS_CTRL_AUTO);
    ENET_MAC_INDIR_ACCESS_CTRL = MAC_INDIR_ACCESS_CTRL_MSEL(0) | reg_num | ENET_MAC_INDIR_ACCESS_CTRL_OB;
    
    while(((uint32_t)RESET != (ENET_MAC_INDIR_ACCESS_CTRL & ENET_MAC_INDIR_ACCESS_CTRL_OB))&& (0U < timeout)) {
        timeout --;
    }
    if((uint32_t)RESET == (ENET_MAC_INDIR_ACCESS_CTRL & ENET_MAC_INDIR_ACCESS_CTRL_OB)){
        status = SUCCESS;
    } else {
        status = ERROR;
    }
}
    return status;
}

/*!
    \brief      set the credit value for Tx queue 1
    \param[in]  creditval: pointer to a enet_cbs_config_struct structure which contains
                parameters of MTL credit related config
                members of the structure and the member values are shown as below:
                  IdleSlopeCredit: the idleSlopeCredit value required for the credit-based shaper algorithm for Queue 1
                  SendSlopeCredit: the SendSlopeCredit value required for the credit-based shaper algorithm for Queue 1
                  HiCredit: the HiCredit value required for the credit-based shaper algorithm for Queue 1
                  loCredit: the loCredit value required for the credit-based shaper algorithm for Queue 1
    \param[out] none
    \retval     none
*/
void enet_txq1_credit_set(enet_cbs_config_struct creditval)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_IDLE_SLOPE_CREDIT(creditval.IdleSlopeCredit)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0051U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ENET_SEND_SLOPE_CREDIT(creditval.SendSlopeCredit)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0051U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ENET_HIGH_SLOPE_CREDIT(creditval.HiCredit)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0051U), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ENET_LOW_SLOPE_CREDIT(creditval.loCredit)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0051U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_TXQ1_QUANTUM_WEIGHT = (uint32_t)creditval.IdleSlopeCredit;
    ENET_MTL_TXQ1_SENDSLOPECREDIT = (uint32_t)creditval.SendSlopeCredit;
    ENET_MTL_TXQ1_HICREDIT        = (uint32_t)creditval.HiCredit;
    ENET_MTL_TXQ1_LOCREDIT        = (uint32_t)creditval.loCredit;
}
}

/*!
    \brief      set the mode and size for Tx queue
    \param[in]  enet_txq: transmit queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1
    \param[in]  queuemode: the mode of transmit queue
                only one parameter can be selected which is shown as below
      \arg        QUE_OP_MODE_DISABLE: the transmit queues are disabled
      \arg        QUE_OP_MODE_AVB_ENABLE: the transmit queues are enabled in AV mode
      \arg        QUE_OP_MODE_ENABLE: the transmit queues are enabled
    \param[in]  queuesize: the size of the allocated transmit queues
      \arg        ENET_TXQ_SIZE_256BYTES: the size of the queue is 256 bytes
      \arg        ENET_TXQ_SIZE_512BYTES: the size of the queue is 512 bytes
      \arg        ENET_TXQ_SIZE_768BYTES: the size of the queue is 768 bytes
      \arg        ENET_TXQ_SIZE_1024BYTES: the size of the queue is 1024 bytes
      \arg        ENET_TXQ_SIZE_1280BYTES: the size of the queue is 1280 bytes
      \arg        ENET_TXQ_SIZE_1536BYTES: the size of the queue is 1536 bytes
      \arg        ENET_TXQ_SIZE_1792BYTES: the size of the queue is 1792 bytes
      \arg        ENET_TXQ_SIZE_2048BYTES: the size of the queue is 2048 bytes
      \arg        ENET_TXQ_SIZE_2304BYTES: the size of the queue is 2304 bytes
      \arg        ENET_TXQ_SIZE_2560BYTES: the size of the queue is 2560 bytes
      \arg        ENET_TXQ_SIZE_2816BYTES: the size of the queue is 2816 bytes
      \arg        ENET_TXQ_SIZE_3072BYTES: the size of the queue is 3072 bytes
      \arg        ENET_TXQ_SIZE_3328BYTES: the size of the queue is 3328 bytes
      \arg        ENET_TXQ_SIZE_3584BYTES: the size of the queue is 3584 bytes
      \arg        ENET_TXQ_SIZE_3840BYTES: the size of the queue is 3840 bytes
      \arg        ENET_TXQ_SIZE_4096BYTES: the size of the queue is 4096 bytes
      \arg        ENET_TXQ_SIZE_4352BYTES: the size of the queue is 4352 bytes
      \arg        ENET_TXQ_SIZE_4608BYTES: the size of the queue is 4608 bytes
      \arg        ENET_TXQ_SIZE_4864BYTES: the size of the queue is 4864 bytes
      \arg        ENET_TXQ_SIZE_5120BYTES: the size of the queue is 5120 bytes
      \arg        ENET_TXQ_SIZE_5376BYTES: the size of the queue is 5376 bytes
      \arg        ENET_TXQ_SIZE_5632BYTES: the size of the queue is 5632 bytes
      \arg        ENET_TXQ_SIZE_5888BYTES: the size of the queue is 5888 bytes
      \arg        ENET_TXQ_SIZE_6144BYTES: the size of the queue is 6144 bytes
      \arg        ENET_TXQ_SIZE_6400BYTES: the size of the queue is 6400 bytes
      \arg        ENET_TXQ_SIZE_6656BYTES: the size of the queue is 6656 bytes
      \arg        ENET_TXQ_SIZE_6912BYTES: the size of the queue is 6912 bytes
      \arg        ENET_TXQ_SIZE_7168BYTES: the size of the queue is 7168 bytes
      \arg        ENET_TXQ_SIZE_7424BYTES: the size of the queue is 7424 bytes
      \arg        ENET_TXQ_SIZE_7680BYTES: the size of the queue is 7680 bytes
      \arg        ENET_TXQ_SIZE_7936BYTES: the size of the queue is 7936 bytes
      \arg        ENET_TXQ_SIZE_8192BYTES: the size of the queue is 8192 bytes
    \param[out] none
    \retval     none
*/
void enet_txq_mode_size_set(enet_txq_enum enet_txq, enet_queopmode_enum queuemode,
                            uint32_t queuesize)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_TXQ_SIZE(queuesize)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0052U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(enet_txq) {
    case TXQ0:
        ENET_MTL_TXQ0_OPERATION_MODE &= ~(ENET_MTL_TXQ0_OPERATION_MODE_TXQEN | ENET_MTL_TXQ0_OPERATION_MODE_TQS);
        ENET_MTL_TXQ0_OPERATION_MODE |= MTL_TXQ_OPERATION_MODE_TXQEN((uint32_t)queuemode) | queuesize;
        break;
    case TXQ1:
        ENET_MTL_TXQ1_OPERATION_MODE &= ~(ENET_MTL_TXQ1_OPERATION_MODE_TXQEN | ENET_MTL_TXQ1_OPERATION_MODE_TQS);
        ENET_MTL_TXQ1_OPERATION_MODE |= MTL_TXQ_OPERATION_MODE_TXQEN((uint32_t)queuemode) | queuesize;
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the size for Rx queue
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  queuesize: the size of the allocated receive queues
      \arg        ENET_RXQ_SIZE_256BYTES: the size of the queue is 256 bytes
      \arg        ENET_RXQ_SIZE_512BYTES: the size of the queue is 512 bytes
      \arg        ENET_RXQ_SIZE_768BYTES: the size of the queue is 768 bytes
      \arg        ENET_RXQ_SIZE_1024BYTES: the size of the queue is 1024 bytes
      \arg        ENET_RXQ_SIZE_1280BYTES: the size of the queue is 1280 bytes
      \arg        ENET_RXQ_SIZE_1536BYTES: the size of the queue is 1536 bytes
      \arg        ENET_RXQ_SIZE_1792BYTES: the size of the queue is 1792 bytes
      \arg        ENET_RXQ_SIZE_2048BYTES: the size of the queue is 2048 bytes
      \arg        ENET_RXQ_SIZE_2304BYTES: the size of the queue is 2304 bytes
      \arg        ENET_RXQ_SIZE_2560BYTES: the size of the queue is 2560 bytes
      \arg        ENET_RXQ_SIZE_2816BYTES: the size of the queue is 2816 bytes
      \arg        ENET_RXQ_SIZE_3072BYTES: the size of the queue is 3072 bytes
      \arg        ENET_RXQ_SIZE_3328BYTES: the size of the queue is 3328 bytes
      \arg        ENET_RXQ_SIZE_3584BYTES: the size of the queue is 3584 bytes
      \arg        ENET_RXQ_SIZE_3840BYTES: the size of the queue is 3840 bytes
      \arg        ENET_RXQ_SIZE_4096BYTES: the size of the queue is 4096 bytes
      \arg        ENET_RXQ_SIZE_4352BYTES: the size of the queue is 4352 bytes
      \arg        ENET_RXQ_SIZE_4608BYTES: the size of the queue is 4608 bytes
      \arg        ENET_RXQ_SIZE_4864BYTES: the size of the queue is 4864 bytes
      \arg        ENET_RXQ_SIZE_5120BYTES: the size of the queue is 5120 bytes
      \arg        ENET_RXQ_SIZE_5376BYTES: the size of the queue is 5376 bytes
      \arg        ENET_RXQ_SIZE_5632BYTES: the size of the queue is 5632 bytes
      \arg        ENET_RXQ_SIZE_5888BYTES: the size of the queue is 5888 bytes
      \arg        ENET_RXQ_SIZE_6144BYTES: the size of the queue is 6144 bytes
      \arg        ENET_RXQ_SIZE_6400BYTES: the size of the queue is 6400 bytes
      \arg        ENET_RXQ_SIZE_6656BYTES: the size of the queue is 6656 bytes
      \arg        ENET_RXQ_SIZE_6912BYTES: the size of the queue is 6912 bytes
      \arg        ENET_RXQ_SIZE_7168BYTES: the size of the queue is 7168 bytes
      \arg        ENET_RXQ_SIZE_7424BYTES: the size of the queue is 7424 bytes
      \arg        ENET_RXQ_SIZE_7680BYTES: the size of the queue is 7680 bytes
      \arg        ENET_RXQ_SIZE_7936BYTES: the size of the queue is 7936 bytes
      \arg        ENET_RXQ_SIZE_8192BYTES: the size of the queue is 8192 bytes
    \param[out] none
    \retval     none
*/
void enet_rxq_size_set(enet_rxq_enum enet_rxq, uint32_t queuesize)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_RXQ_SIZE(queuesize)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0053U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{

    switch(enet_rxq) {
    case RXQ0:
        ENET_MTL_RXQ0_OPERATION_MODE &= ~ENET_MTL_RXQ0_OPERATION_MODE_RQS;
        ENET_MTL_RXQ0_OPERATION_MODE |= queuesize ;
        break;
    case RXQ1:
        ENET_MTL_RXQ1_OPERATION_MODE &= ~ENET_MTL_RXQ1_OPERATION_MODE_RQS;
        ENET_MTL_RXQ1_OPERATION_MODE |= queuesize ;
        break;
    default:
        break;
    }
}
}

/*!
    \brief      select the Rx dma channel for Rx queue
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_rxq_dma_select(enet_rxq_enum enet_rxq, enet_dmach_enum dmach)
{

    switch(enet_rxq) {
    case RXQ0:
        ENET_MTL_RXQ_DMA_MAP0 &= ~ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH;
        ENET_MTL_RXQ_DMA_MAP0 |= (uint32_t)dmach ;
        break;
    case RXQ1:
        ENET_MTL_RXQ_DMA_MAP0 &= ~ENET_MTL_RXQ_DMA_MAP0_Q1MDMACH;
        ENET_MTL_RXQ_DMA_MAP0 |= (uint32_t)((uint32_t)dmach << 8U);
        break;
    default:
        break;
    }
}

/*!
    \brief      set the base time of GCL
    \param[in]  second: the second of BTR time
    \param[in]  nanosecond: the nanosecond of BTR time
    \param[out] none
    \retval     none
*/
void enet_est_gcl_basetime_set(uint32_t second, uint32_t nanosecond)
{
    uint32_t stimeout, nstimeout;
    stimeout = ENET_OPERATION_TIMEROUT, nstimeout = ENET_OPERATION_TIMEROUT;

    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_R1W0;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_DATA = (uint32_t)(nanosecond & ENET_MTL_EST_GCL_DATA_GCD);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_BTR_LOW;
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO))&& (0U < stimeout)) {
        stimeout --;
    }

    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_DATA = (uint32_t)(second & ENET_MTL_EST_GCL_DATA_GCD);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_BTR_HIGH;
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < nstimeout)) {
        nstimeout --;
    }
}

/*!
    \brief      get the base time of GCL
    \param[in]  none
    \param[out] time_struct: pointer to a enet_ESTConfig_struct structure which contains
                parameters of GCL
                members of the structure and the member values are shown as below:
                  BTRinnanosecond: 0x0 - 0xFFFF FFFF
                  BTRinsecond: 0x0 - 0xFFFF FFFF
    \retval     none
*/
void enet_est_gcl_basetime_get(enet_ESTConfig_struct *time_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(time_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0056U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    uint32_t stimeout = ENET_OPERATION_TIMEROUT, nstimeout = ENET_OPERATION_TIMEROUT;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_CONTROL |= (ENET_GCL_BTR_LOW | ENET_MTL_EST_GCL_CONTROL_R1W0);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < nstimeout)) {
        nstimeout --;
    }
    time_struct->BTRinnanosecond = (uint32_t)(ENET_MTL_EST_GCL_DATA & ENET_MTL_EST_GCL_DATA_GCD);


    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_CONTROL |= (ENET_GCL_BTR_HIGH | ENET_MTL_EST_GCL_CONTROL_R1W0);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < stimeout)) {
        stimeout --;
    }
    time_struct->BTRinsecond = (uint32_t)(ENET_MTL_EST_GCL_DATA & ENET_MTL_EST_GCL_DATA_GCD);
}
}

/*!
    \brief      set the cycle time of GCL
    \param[in]  second: the second of CTR time
    \param[in]  nanosecond: the nanosecond of CTR time
    \param[out] none
    \retval     none
*/
void enet_est_gcl_cycletime_set(uint8_t second, uint32_t nanosecond)
{
    uint32_t stimeout = ENET_OPERATION_TIMEROUT, nstimeout = ENET_OPERATION_TIMEROUT;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_R1W0;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_DATA = (uint32_t)(nanosecond & ENET_MTL_EST_GCL_DATA_GCD);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_CTR_LOW;
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < nstimeout)) {
        nstimeout --;
    }

    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_DATA = (uint8_t)(second & ENET_MTL_EST_GCL_DATA_GCD);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_CTR_HIGH;
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < stimeout)) {
        stimeout --;
    }
}

/*!
    \brief      get the cycle time of GCL
    \param[in]  none
    \param[out] time_struct: pointer to a enet_ESTConfig_struct structure which contains
                parameters of GCL
                members of the structure and the member values are shown as below:
                  CTRinnanosecond: 0x0 - 0xFFFF FFFF
                  CTRinsecond: 0x0 - 0xFFFF FFFF
    \retval     none
*/
void enet_est_gcl_cycletime_get(enet_ESTConfig_struct *time_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(time_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0058U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    uint32_t stimeout = ENET_OPERATION_TIMEROUT, nstimeout = ENET_OPERATION_TIMEROUT;

    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_CONTROL |= (ENET_GCL_CTR_LOW | ENET_MTL_EST_GCL_CONTROL_R1W0);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < nstimeout)) {
        nstimeout --;
    }
    time_struct->CTRinnanosecond = (uint32_t)(ENET_MTL_EST_GCL_DATA & ENET_MTL_EST_GCL_DATA_GCD);


    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_CONTROL |= (ENET_GCL_CTR_HIGH | ENET_MTL_EST_GCL_CONTROL_R1W0);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < stimeout)) {
        stimeout --;
    }
    time_struct->CTRinsecond = (uint32_t)(ENET_MTL_EST_GCL_DATA & ENET_MTL_EST_GCL_DATA_GCD);
}
}

/*!
    \brief      set the extension time of GCL
    \param[in]  second: the second of TER time
    \param[in]  nanosecond: the nanosecond of TER time
    \param[out] none
    \retval     none
*/
void enet_est_gcl_extensiontime_set(uint32_t nanosecond)
{
     uint32_t timeout = ENET_OPERATION_TIMEROUT;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TER_REG_VAL(nanosecond)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0059U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_R1W0;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_DATA = (uint32_t)(nanosecond & BITS(0, 30));
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_TER;
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < timeout)) {
        timeout --;
    }
}
}

/*!
    \brief      get the extension time of GCL
    \param[in]  none
    \param[out] time_struct: pointer to a enet_ESTConfig_struct structure which contains
                parameters of GCL
                members of the structure and the member values are shown as below:
                  TERtime: 0x0 - 0x3FFF FFFF
    \retval     none
*/
void enet_est_gcl_extensiontime_get(enet_ESTConfig_struct *time_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(time_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x005AU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_CONTROL |= (ENET_GCL_TER | ENET_MTL_EST_GCL_CONTROL_R1W0);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < timeout)) {
        timeout --;
    }
    time_struct->TERtime = (uint32_t)(ENET_MTL_EST_GCL_DATA & BITS(0, 30));

}
}

/*!
    \brief      set the length of GCL
    \param[in]  length: the gcl length
    \param[out] none
    \retval     none
*/
void enet_est_gcl_length_set(uint32_t length)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_GCL_LENGTH(length)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x005BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_R1W0;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_DATA = (uint32_t)(length & BITS(0, 7));
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_LLR;
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < timeout)) {
        timeout --;
    }
}
}

/*!
    \brief      get the length of GCL
    \param[in]  none
    \param[out] time_struct: pointer to a enet_ESTConfig_struct structure which contains
                parameters of GCL
                members of the structure and the member values are shown as below:
                  LLRdepth: 0x0 - 0xFF
    \retval     none
*/
void enet_est_gcl_length_get(enet_ESTConfig_struct *time_struct)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(time_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x005CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_CONTROL |= (ENET_GCL_LLR | ENET_MTL_EST_GCL_CONTROL_R1W0);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < timeout)) {
        timeout --;
    }
    time_struct->LLRdepth = (uint16_t)(ENET_MTL_EST_GCL_DATA & BITS(0, 7));
}
}

/*!
    \brief      set the related parameter of GCL
    \param[in]  addr: the gcl address
    \param[in]  gcl_struct: pointer to a enet_GCLConfig_struct structure which contains
                parameters of GCL
                members of the structure and the member values are shown as below:
                  Ctrlconfig: 0x0 - 0x3
                  Ethtimeinterval: 0x0 - 0xFF FFFF
    \param[out] none
    \retval     none
*/
void enet_est_gcl_para_set(uint8_t addr, enet_GCLConfig_struct *gcl_struct)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(gcl_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x005DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_R1W0;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_GCRR;
    ENET_MTL_EST_GCL_DATA = (uint32_t)(((uint32_t)(gcl_struct->Ctrlconfig) << GCL_GATE_CONTROL_OFFSET) | gcl_struct->Ethtimeinterval);
    ENET_MTL_EST_GCL_CONTROL |= MTL_EST_GCL_CONTROL_ADDR(addr);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < timeout)) {
        timeout --;
    }
}
}

/*!
    \brief      get the related parameter of GCL
    \param[in]  addr: the gcl address
    \param[out] gcl_struct: pointer to a enet_GCLConfig_struct structure which contains
                parameters of GCL
                members of the structure and the member values are shown as below:
                  Ctrlconfig: 0x0 - 0x3
                  Ethtimeinterval: 0x0 - 0xFF FFFF
    \retval     none
*/
void enet_est_gcl_para_get(uint8_t addr, enet_GCLConfig_struct *gcl_struct)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(gcl_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x005EU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_ADDR;
    ENET_MTL_EST_GCL_CONTROL &= ~ENET_MTL_EST_GCL_CONTROL_GCRR;
    ENET_MTL_EST_GCL_CONTROL |= (MTL_EST_GCL_CONTROL_ADDR(addr) | ENET_MTL_EST_GCL_CONTROL_R1W0);
    ENET_MTL_EST_GCL_CONTROL |= ENET_GCL_READ_WRITE_START;
    while(((uint32_t)RESET != (ENET_MTL_EST_GCL_CONTROL & ENET_MTL_EST_GCL_CONTROL_SRWO)) && (0U < timeout)) {
        timeout --;
    }
    gcl_struct->Ctrlconfig = (uint8_t)((ENET_MTL_EST_GCL_DATA & BITS(24, 25)) >> GCL_GATE_CONTROL_OFFSET);
    gcl_struct->Ethtimeinterval = (uint32_t)(ENET_MTL_EST_GCL_DATA & BITS(0, 19));
}
}

/*!
    \brief      enable switching to S/W owned list
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_est_gcl_switch_enable(void)
{
    ENET_MTL_EST_CONTROL |= (uint32_t)(ENET_MTL_EST_CONTROL_EEST | ENET_MTL_EST_CONTROL_SSWL);
}

/*!
    \brief      get the S/W owned list
    \param[in]  none
    \param[out] none
    \retval     enet_gcl_enum: GCL_LIST0 or GCL_LIST1
*/
enet_gcl_enum enet_gcl_softwore_list_get(void)
{
    enet_gcl_enum list_num;
    if((uint32_t)RESET != (ENET_MTL_EST_STATUS & ENET_MTL_EST_STATUS_SWOL))
    {
       list_num = GCL_LIST1;
    } else {
       list_num = GCL_LIST0;
    }
    return list_num;
}

/*!
    \brief      get the current gcl slot number
    \param[in]  none
    \param[out] none
    \retval     slot_num: the current gcl slot number
*/
uint8_t enet_gcl_current_slot_get(void)
{
    uint8_t slot_num;
    slot_num = (uint8_t)GET_CURRENT_GCL_NUM(ENET_MTL_EST_STATUS);
    return slot_num;
}

/*!
    \brief      get the BTR error loop count
    \param[in]  none
    \param[out] none
    \retval     err_cnt: the BTR error loop count
*/
uint8_t enet_btr_error_loop_get(void)
{
    uint8_t err_cnt;
    err_cnt = (uint8_t)GET_BTR_ERROR_LOOP_COUNT(ENET_MTL_EST_STATUS);
    return err_cnt;
}

/*!
    \brief      clear the queue number that have experienced error
    \param[in]  err: experienced error selection
                only one parameter can be selected which is shown as below
      \arg        SCHEDULE_ERROR: schedule error
      \arg        FRAME_SIZE_ERROR: frame size error
    \param[in]  enet_txq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1
    \param[out] none
    \retval     none
*/
void enet_est_error_queue_clear(enet_est_error_enum err, enet_txq_enum enet_txq)
{

    switch(err) {
    case SCHEDULE_ERROR:
        if(TXQ0 == enet_txq)
        {
            ENET_MTL_EST_SCH_ERROR &= ~ENET_MTL_EST_SCH_ERROR_SEQN;
            ENET_MTL_EST_SCH_ERROR |= ENET_EST_SCHEDULE_ERR_Q0;
        } else {
            ENET_MTL_EST_SCH_ERROR &= ~ENET_MTL_EST_SCH_ERROR_SEQN;
            ENET_MTL_EST_SCH_ERROR |= ENET_EST_SCHEDULE_ERR_Q1;
        }
        break;
    case FRAME_SIZE_ERROR:
        if(TXQ0 == enet_txq)
        {
            ENET_MTL_EST_FRM_SIZE_ERROR &= ~ENET_MTL_EST_FRM_SIZE_ERROR_FEQN;
            ENET_MTL_EST_FRM_SIZE_ERROR |= ENET_EST_FRAME_SIZE_ERR_Q0;
        } else {
            ENET_MTL_EST_FRM_SIZE_ERROR &= ~ENET_MTL_EST_FRM_SIZE_ERROR_FEQN;
            ENET_MTL_EST_FRM_SIZE_ERROR |= ENET_EST_FRAME_SIZE_ERR_Q1;
        }
        break;
    default:
        break;
    }
}

/*!
    \brief      check whether the queue experienced an error
    \param[in]  err: experienced error selection
                only one parameter can be selected which is shown as below
      \arg        SCHEDULE_ERROR: schedule error
      \arg        FRAME_SIZE_ERROR: frame size error
    \param[in]  enet_txq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1
    \param[out] none
    \retval     FlagStatus: RESET / SET
*/
FlagStatus enet_est_error_queue_satus_get(enet_est_error_enum err, enet_txq_enum enet_txq)
{
    FlagStatus status = RESET;

    switch(err) {
    case SCHEDULE_ERROR:
        if(TXQ0 == enet_txq)
        {
            if((uint32_t)RESET !=(ENET_MTL_EST_SCH_ERROR & ENET_EST_SCHEDULE_ERR_Q0)) {
                status = SET;
            } else {
                status = RESET;
            }
        } else {
            if((uint32_t)RESET !=(ENET_MTL_EST_SCH_ERROR & ENET_EST_SCHEDULE_ERR_Q1)) {
                status = SET;
            } else {
                status = RESET;
            }
        }
        break;
    case FRAME_SIZE_ERROR:
        if(TXQ0 == enet_txq)
        {
            if((uint32_t)RESET !=(ENET_MTL_EST_FRM_SIZE_ERROR & ENET_EST_FRAME_SIZE_ERR_Q0)) {
                status = SET;
            } else {
                status = RESET;
            }
        } else {
            if((uint32_t)RESET !=(ENET_MTL_EST_FRM_SIZE_ERROR & ENET_EST_FRAME_SIZE_ERR_Q1)) {
                status = SET;
            } else {
                status = RESET;
            }
        }
        break;
    default:
        break;
    }
    return status;
}

/*!
    \brief      get the first queue number experience HLBF error
    \param[in]  none
    \param[out] none
    \retval     enet_txq: TXQ0 / TXQ1
*/
enet_txq_enum enet_est_first_error_queue_get(void)
{
    enet_txq_enum  enet_txq;
    if((uint32_t)RESET == (ENET_MTL_EST_FRM_SIZE_CAPTURE & ENET_MTL_EST_FRM_SIZE_CAPTURE_HBFQ)) {
        enet_txq = TXQ0;
    } else {
        enet_txq = TXQ1;
    }
    return enet_txq;
}

/*!
    \brief      get the frame size of the first queue which experience HLBF error
    \param[in]  none
    \param[out] none
    \retval     size: the frame size
*/
uint16_t enet_est_error_framesize_get(void)
{
    uint16_t size;
    size = (uint16_t)GET_HLBF_FRAME_SIZE(ENET_MTL_EST_FRM_SIZE_CAPTURE);
    return size;
}

/*!
    \brief      config FPE related parameter
    \param[in]  fpe_struct: pointer to a enet_FPEConfig_struct structure which contains
                parameters of FPE
                members of the structure and the member values are shown as below:
                  FPEenable: 0x0 - 0x1
                  Holdtime: 0x0 - 0xFFFF
                  Holdtime: 0x0 - 0xFFFF
    \param[out] none
    \retval     none
*/
void enet_fpe_advance_time_set(enet_FPEConfig_struct *fpe_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(fpe_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0067U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_FPE_CTRL_STS &= ~ENET_MAC_FPE_CTRL_STS_EFPE;
    ENET_MAC_FPE_CTRL_STS |= (uint32_t)fpe_struct->FPEenable;
    ENET_MTL_FPE_ADVANCE = (uint32_t)(MTL_HOLD_ADVANCE(fpe_struct->Holdtime) | MTL_RELEASE_ADVANCE(fpe_struct->Relasetime));
}
}

/*!
    \brief      get FPE related parameter
    \param[in]  none
    \param[out] fpe_struct: pointer to a enet_FPEConfig_struct structure which contains
                parameters of GCL
                members of the structure and the member values are shown as below:
                  FPEenable: 0x0 - 0x1
                  Holdtime: 0x0 - 0xFFFF
                  Holdtime: 0x0 - 0xFFFF
    \retval     none
*/
void enet_fpe_advance_time_get(enet_FPEConfig_struct *fpe_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(fpe_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0068U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if((uint32_t)RESET != (ENET_MAC_FPE_CTRL_STS & ENET_MAC_FPE_CTRL_STS_EFPE)){
        fpe_struct->FPEenable = ENABLE;
    } else {
        fpe_struct->FPEenable = DISABLE;
    }
    fpe_struct->Holdtime = (uint16_t)GET_HOLD_ADVANCE(ENET_MTL_FPE_ADVANCE);
    fpe_struct->Relasetime = GET_RELEASE_ADVANCE(ENET_MTL_FPE_ADVANCE);
}
}

/*!
    \brief      set the launch expiry time
    \param[in]  mode: the launch expiry time mode
                only one parameter can be selected which is shown as below
      \arg        ENET_TBS_NORMAL_ABSOLUTE_MODE: the launch time value used in time based scheduling is interpreted as an EST offset value
      \arg        ENET_TBS_EST_OFFSET_MODE: the launch time value is used as an absolute value
    \param[in]  offset: the launch expiry offset
    \param[in]  gsn_offset: the launch expiry gsn offset
    \param[out] none
    \retval     none
*/
void enet_launch_expiry_time_set(uint32_t mode, uint32_t offset, uint32_t gsn_offset)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_TBS_MODE(mode)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0069U), ERR_PARAM_INVALID);
    } else if(NOT_LAUNCH_EXPIRY_OFFSET(offset)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0069U), ERR_PARAM_INVALID);
    } else if(NOT_LAUNCH_EXPIRY_GSN_OFFSET(gsn_offset)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0067U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if(ENET_TBS_NORMAL_ABSOLUTE_MODE == mode) {
        ENET_MTL_TBS_CTRL &= ~(ENET_MTL_TBS_CTRL_ESTM | ENET_MTL_TBS_CTRL_LEOS);
        ENET_MTL_TBS_CTRL |= MTL_TBS_CTRL_LEOS(offset);
    } else {
        ENET_MTL_TBS_CTRL &= ~(ENET_MTL_TBS_CTRL_ESTM | ENET_MTL_TBS_CTRL_LEOS | ENET_MTL_TBS_CTRL_LEOV | ENET_MTL_TBS_CTRL_LEGOS);
        ENET_MTL_TBS_CTRL |= ENET_MTL_TBS_CTRL_ESTM | ENET_MTL_TBS_CTRL_LEOV;
        ENET_MTL_TBS_CTRL |= MTL_TBS_CTRL_LEOS(offset)| MTL_TBS_CTRL_LEGOS(gsn_offset);
    }
}
}

/*!
    \brief      set the fetch time
    \param[in]  mode: the fetch time mode
                only one parameter can be selected which is shown as below
      \arg        ENET_TBS_NORMAL_ABSOLUTE_MODE: the launch time value used in time based scheduling is interpreted as an EST offset value
      \arg        ENET_TBS_EST_OFFSET_MODE: the launch time value is used as an absolute value
    \param[in]  offset: the fetch offset
    \param[in]  gsn_offset: the fetch gsn offset
    \param[out] none
    \retval     none
*/
void enet_fetch_time_set(uint32_t mode, uint32_t offset, uint32_t gsn_offset)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_TBS_MODE(mode)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x006AU), ERR_PARAM_INVALID);
    } else if(NOT_FETCH_OFFSET(offset)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x006AU), ERR_PARAM_INVALID);
    } else if(NOT_FETCH_GSN_OFFSET(gsn_offset)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x006AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if(ENET_TBS_NORMAL_ABSOLUTE_MODE == mode) {
        ENET_MTL_TBS_CTRL &= ~ENET_MTL_TBS_CTRL_ESTM;
        ENET_DMA_TBS_CTRL0 &= ~ENET_DMA_TBS_CTRL0_FTOS;
        ENET_DMA_TBS_CTRL0 |= DMA_TBS_CTRL0_FTOS(offset) | ENET_DMA_TBS_CTRL0_FTOV;
    } else {
        ENET_DMA_TBS_CTRL0 &= ~(ENET_DMA_TBS_CTRL0_FTOV | ENET_DMA_TBS_CTRL0_FTOS | ENET_DMA_TBS_CTRL0_FGOS);
        ENET_MTL_TBS_CTRL |= ENET_MTL_TBS_CTRL_ESTM;
        ENET_DMA_TBS_CTRL0 |= DMA_TBS_CTRL0_FTOS(offset)| DMA_TBS_CTRL0_FGOS(gsn_offset) | ENET_DMA_TBS_CTRL0_FTOV;
    }
}
}

/*!
    \brief    get the transmit queue debug state
    \param[in]  enet_txq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1
    \param[in]  state: choose the state of transmit queue debug which users want to check, refer to enet_mtl_txq_state_enum
                only one parameter can be selected which is shown as below
      \arg            TXQ_FIFO_FULL_STATE: MTL Tx status FIFO full status
      \arg            TXQ_NOT_EMPTY_STATE: MTL Tx queue not empty status
      \arg            TXQ_WRITE_CONTROLLER_STATE: MTL Tx queue write controller status
      \arg            TXQ_READ_CONTROLLER_STATE: MTL Tx queue read controller status
      \arg            TXQ_IN_PAUSE_STATE: transmit queue in pause
    \param[out] none
    \retval     transmit queue debug state, the value range shows below:
                  ENET_TXQ_STATUS_FIFO_FULL_DETECT, ENET_TXQ_STATUS_FIFO_FULL_NOT_DETECT,
                  ENET_TXQ_STATUS_FIFO_NOT_EMPTY_DETECT, ENET_TXQ_STATUS_FIFO_NOT_EMPTY_NOT_DETECT,
                  ENET_TXQ_WRITE_CONTROL_DETECT, ENET_TXQ_STATUS_FIFO_NOT_EMPTY_NOT_DETECT,
                  ENET_TXQ_READ_CONTROLLER_STATE_IDLE, ENET_TXQ_READ_CONTROLLER_STATE_READ,ENET_TXQ_READ_CONTROLLER_STATE_WAITING,ENET_TXQ_READ_CONTROLLER_STATE_FLUSHING,
                  ENET_TXQ_IN_PAUSE_DETECT, ENET_TXQ_IN_PAUSE_NOT_DETECT
*/
uint32_t enet_txq_debug_state_get(enet_txq_enum enet_txq, enet_mtl_txq_state_enum state)
{
    uint32_t reval;
    reval = 0U;

     switch(enet_txq) {
    case TXQ0:
    reval = (uint32_t)(ENET_MTL_TXQ0_DEBUG & (uint32_t)state);
        break;
    case TXQ1:
    reval = (uint32_t)(ENET_MTL_TXQ1_DEBUG & (uint32_t)state);
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief     get the count of transmit queue packets
    \param[in]  enet_txq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1

    \param[out] none
    \retval     reval: the number of transmit queue packets
*/
uint32_t enet_txq_packet_count_get(enet_txq_enum enet_txq)
{
    uint32_t reval;
    reval = 0;

    switch(enet_txq) {
    case TXQ0:
    reval = (uint32_t)GET_TXQ_PACKETS_NUMBER(ENET_MTL_TXQ0_DEBUG);
        break;
    case TXQ1:
    reval = (uint32_t)GET_TXQ_PACKETS_NUMBER(ENET_MTL_TXQ1_DEBUG);
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief     get the number of transmit queue status word
    \param[in]  enet_txq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1

    \param[out] none
    \retval     reval: the number of transmit queue status word
*/
uint32_t enet_txq_status_word_num_get(enet_txq_enum enet_txq)
{
    uint32_t reval;
    reval = 0U;

    switch(enet_txq) {
    case TXQ0:
    reval = (uint32_t)GET_TXQ_STATUS_WORD_NUMBER(ENET_MTL_TXQ0_DEBUG);
        break;
    case TXQ1:
    reval = (uint32_t)GET_TXQ_STATUS_WORD_NUMBER(ENET_MTL_TXQ1_DEBUG);
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief    get the receive queue debug state
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1
    \param[in]  state: choose the state of receive queue debug which users want to check, refer to enet_mtl_rxq_state_enum
                only one parameter can be selected which is shown as below
      \arg            RXQ_FILL_LEVEL_STATE: MTL Rx queue fill-level status
      \arg            RXQ_READ_CONTROLLER_STATE: MTL Rx queue read controller state
      \arg            RXQ_WRITE_CONTROLLER_STATE: MTL Rx queue write controller active status
    \param[out] none
    \retval     state of receive queue debug, the value range shows below:
                  ENET_RXQ_EMPTY, ENET_RXQ_FILL_BELOW_DEACTIVATE_THRESHOLD, ENET_RXQ_FILL_ABOVE_ACTIVATE_THRESHOLD, ENET_RXQ_FULL,
                  ENET_RXQ_READ_CONTROLLER_IDLE, ENET_RXQ_READ_CONTROLLER_READING_DATA, ENET_RXQ_READ_CONTROLLER_READING_STATUS,ENET_RXQ_READ_CONTROLLER_FLUSHING,
                  ENET_RXQ_WRITE_CONTROLLER_ACTIVE, ENET_RXQ_WRITE_CONTROLLER_INACTIVE,
*/
uint32_t enet_rxq_debug_state_get(enet_rxq_enum enet_rxq, enet_mtl_rxq_state_enum state)
{
    uint32_t reval;
    reval = 0U;

    switch(enet_rxq) {
    case RXQ0:
    reval = (uint32_t)(ENET_MTL_RXQ0_DEBUG & (uint32_t)state);
        break;
    case RXQ1:
    reval = (uint32_t)(ENET_MTL_RXQ1_DEBUG & (uint32_t)state);
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief     get the count of receive queue packets
    \param[in]  enet_rxq: receive queue selection
                only one parameter can be selected which is shown as below
      \arg        RXQ0: receive queue 0
      \arg        RXQ1: receive queue 1

    \param[out] none
    \retval     reval: the number of receive queue packets
*/
uint32_t enet_rxq_packet_count_get(enet_rxq_enum enet_rxq)
{
    uint32_t reval;
    reval = 0U;

    switch(enet_rxq) {
    case RXQ0:
    reval = (uint32_t)GET_RXQ_PACKETS_NUMBER(ENET_MTL_RXQ0_DEBUG);
        break;
    case RXQ1:
    reval = (uint32_t)GET_RXQ_PACKETS_NUMBER(ENET_MTL_RXQ1_DEBUG);
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief     get the number of average bits per slot
    \param[in]  enet_txq: transmit queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1

    \param[out] none
    \retval     reval: the number of average bits per slot
*/
uint32_t enet_slot_average_bits_get(enet_txq_enum enet_txq)
{
    uint32_t reval;
    reval = 0U;
    switch(enet_txq) {
    case TXQ0:
    reval = (uint32_t)GET_AVER_BITS(ENET_MTL_TXQ0_ETS_STATUS);
        break;
    case TXQ1:
    reval = (uint32_t)GET_AVER_BITS(ENET_MTL_TXQ1_ETS_STATUS);
        break;
    default:
        break;
    }
    return reval;
}

/*!
    \brief     config the transmit queue 1 ETS control related parameter
    \param[in]  config: the ets configuration of transmit queue 1
                 only one parameter can be selected which is shown as below
      \arg        ENET_CBS_1SLOT: 1 slot
      \arg        ENET_CBS_2SLOT: 2 slot
      \arg        ENET_CBS_4SLOT: 4 slot
      \arg        ENET_CBS_8SLOT: 8 slot
      \arg        ENET_CBS_16SLOT: 16 slot
      \arg        ENET_TXQ1_CREDIT_CONTROL_ENABLE: credit control is enable
      \arg        ENET_TXQ1_CREDIT_CONTROL_DISABLE: credit control is disabled
      \arg        ENET_TXQ1_AV_ALGO_ENABLE: CBS algorithm is enable
      \arg        ENET_TXQ1_AV_ALGO_DISABLE: CBS algorithm is disabled
    \param[out] none
    \retval     none
*/
void enet_txq1_ets_control(uint32_t config)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_TXQ1_ETS_CFG(config)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0071U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch (config) {
        case ENET_TXQ1_CREDIT_CONTROL_ENABLE:
        case ENET_TXQ1_AV_ALGO_ENABLE:
            ENET_MTL_TXQ1_ETS_CONTROL |= config;
            break;
        case ENET_TXQ1_CREDIT_CONTROL_DISABLE:
        case ENET_TXQ1_AV_ALGO_DISABLE:
            ENET_MTL_TXQ1_ETS_CONTROL &= config;
            break;
        case ENET_CBS_1SLOT:
        case ENET_CBS_2SLOT:
        case ENET_CBS_4SLOT:
        case ENET_CBS_8SLOT:
        case ENET_CBS_16SLOT:
            ENET_MTL_TXQ1_ETS_CONTROL &= ~ENET_MTL_TXQ1_ETS_CONTROL_SLC;
            ENET_MTL_TXQ1_ETS_CONTROL |= config;
            break;
        default:
            break;
    }
}
}

/*!
    \brief      set the overhead bytes value
    \param[in]  val: the overhead bytes value(0x00 - 0x3F)
    \param[out] none
    \retval     none
*/
void enet_overhead_value_set(uint8_t val)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_OVERHEAD_BYTES_VALUE(val)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0072U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_EST_EXT_CONTROL &= ~ENET_MTL_EST_EXT_CONTROL_OVHD;
    ENET_MTL_EST_EXT_CONTROL = val;
}
}

/*!
    \brief    configure descriptor to work in enhanced mode
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_desc_select_enhanced_mode(enet_dmach_enum dmach)
{
    if(DMACH0 == dmach) {
        ENET_DMA_CH0_TX_CONTROL |= ENET_DMA_CH_TX_CONTROL_DESE;
    } else {
        ENET_DMA_CH1_TX_CONTROL |= ENET_DMA_CH_TX_CONTROL_DESE;
    }
}

/*!
    \brief    configure descriptor to work in normal mode
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_desc_select_normal_mode(enet_dmach_enum dmach)
{

    if(DMACH0 == dmach) {
        ENET_DMA_CH0_TX_CONTROL &= ~ ENET_DMA_CH_TX_CONTROL_DESE;
    } else {
        ENET_DMA_CH1_TX_CONTROL &= ~ ENET_DMA_CH_TX_CONTROL_DESE;
    }
}

/*!
    \brief    initialize the DMA Tx enhanced descriptors's parameters in ring mode
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_tbs_descriptors_ring_init(enet_dmach_enum dmach)
{
    uint32_t num, count, maxsize;
    uint32_t desc_status = 0U;
    enet_tbs_enhanced_descriptors_struct *desc;
    enet_tbs_enhanced_descriptors_struct *desc_tab;
    uint8_t *buf;

    switch(dmach) {
    case DMACH0: 

        /* save a copy of the DMA Tx descriptors */
        desc_tab = tbs_txdesc_tab;
        buf = &tx_buff[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        dma_current_tbs_txdesc = desc_tab;
        ENET_DMA_CH0_TXDESC_RING_LENGTH = (ENET_TXBUF_NUM - 1U);
        ENET_DMA_CH0_TXDESC_ADDRESS = (uint32_t)tbs_txdesc_tab;
        ENET_DMA_CH0_TXDESC_TAIL_POINTER = (uint32_t)tbs_txdesc_tab;
     
    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->DES0 = (uint32_t)(&buf[num * maxsize]);
        desc->DES3 = desc_status;
        desc->buffer_address = desc->DES0;
    }
    break;
    case DMACH1: 

        /* save a copy of the DMA Tx descriptors */
        desc_tab = tbs_txdesc_tab1;
        buf = &tx_buff1[0][0];
        count = ENET_TXBUF_NUM;
        maxsize = ENET_TXBUF_SIZE;

        dma_current_tbs_txdesc1 = desc_tab;
    
        ENET_DMA_CH1_TXDESC_RING_LENGTH = (ENET_TXBUF_NUM - 1U);
        ENET_DMA_CH1_TXDESC_ADDRESS = (uint32_t)tbs_txdesc_tab1;
        ENET_DMA_CH1_TXDESC_TAIL_POINTER = (uint32_t)tbs_txdesc_tab1;
    /* configure each descriptor */
    for(num = 0U; num < count; num++) {
        /* get the pointer to the next descriptor of the descriptor table */
        desc = desc_tab + num;

        /* configure descriptors */
        desc->DES0 = (uint32_t)(&buf[num * maxsize]);
        desc->DES3 = desc_status;
        desc->buffer_address = desc->DES0;
    }
    break;
    default:
       break;
    }
}

/*!
    \brief    receive a packet data with timestamp values to application buffer, when the DMA is in normal mode
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  bufsize: the size of buffer which is the parameter in function
    \param[out] buffer: pointer to the application buffer
                note -- if the input is NULL, user should copy data in application by himself
    \param[out] timestamp: pointer to the table which stores the timestamp high and low
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_ptpframe_receive_normal_mode(enet_dmach_enum dmach, uint8_t *buffer, uint32_t bufsize, uint32_t timestamp[])
{
    uint32_t offset, size;
    ErrStatus status;
    enet_descriptors_struct *dma_context_rxdesc;
    status = ERROR;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_BUFSIZE(bufsize)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0076U), ERR_PARAM_INVALID);
    } else if(NOT_VALID_POINTER(timestamp)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0076U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0: 
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_OWN)) {
        return status;
    }
     /* get the context descriptor with timestamp information */
     if((enet_descriptors_struct *)(uint32_t)&rxdesc_tab[(ENET_RXBUF_NUM - 1U)] == dma_current_rxdesc) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_context_rxdesc = (enet_descriptors_struct *)(ENET_DMA_CH0_RXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_context_rxdesc = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_rxdesc + ETH_DMARXDESC_SIZE);
    }
    
    /* if buffer pointer is null, indicates that users has copied data in application */
    if(NULL != buffer) {
        /* if no error occurs, and the frame uses only one descriptor */
        if((((uint32_t)RESET) == (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_ES)) &&
                (((uint32_t)RESET) != (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_LD)) &&
                (((uint32_t)RESET) != (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_FD))) {
            /* get the frame length except CRC */
            size = dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_PL;
            size = size - 4U;

            /* if is a type frame, and CRC is not included in forwarding frame */
            if(((uint32_t)RESET != (ENET_MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_CST)) && ((uint32_t)RESET != (dma_current_rxdesc->DES3 & ENET_NORMAL_RDES3_WF_LT))) {
                size = size + 4U;
            } else {
              /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }

            /* to avoid situation that the frame size exceeds the buffer length */
            if(size > bufsize) {
                return status;
            } else {
              /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }

            /* copy data from Rx buffer to application buffer */
            for(offset = 0U; offset < size; offset++) {
                (*(buffer + offset)) = (*(__IO uint8_t *)(uint32_t)((dma_current_rxdesc->buffer_address) + offset));
            }

        } else {
            /* return ERROR */
            return status;
        }
    }

    /* copy the timestamp from the context descriptor. */
    timestamp[0] = dma_context_rxdesc->DES0;
    timestamp[1] = dma_context_rxdesc->DES1;
    
    dma_current_rxdesc->DES0 = dma_current_rxdesc->buffer_address;
    dma_current_rxdesc->DES1 = dma_current_rxdesc->bkp_info;
    
    dma_context_rxdesc->DES0 = dma_context_rxdesc->buffer_address;
    dma_context_rxdesc->DES1 = dma_context_rxdesc->bkp_info;

    /* enable reception, descriptor is owned by DMA */
    dma_current_rxdesc->DES3 = ENET_NORMAL_RDES3_WF_OWN | ENET_NORMAL_RDES3_RF_BUF1V;
    dma_context_rxdesc->DES3 = ENET_NORMAL_RDES3_WF_OWN | ENET_NORMAL_RDES3_RF_BUF1V;
    
    /* If the receive interrupt is enabled, the IOC bit needs to be set */
    if((uint32_t)RESET != (ENET_DMA_CH0_INTERRUPT_ENABLE & ENET_DMA_CH_INTERRUPT_ENABLE_RIE)) {
        dma_current_rxdesc->DES3 |= ENET_NORMAL_RDES3_RF_IOC;
        dma_context_rxdesc->DES3 |= ENET_NORMAL_RDES3_RF_IOC;
    }
    __DMB();
    
    /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
    /* ring mode */
    if((enet_descriptors_struct *)(uint32_t)&rxdesc_tab[(ENET_RXBUF_NUM - 1U)] == dma_context_rxdesc) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_rxdesc = (enet_descriptors_struct *)(ENET_DMA_CH0_RXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_rxdesc = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_context_rxdesc + ETH_DMARXDESC_SIZE);
    }
    ENET_DMA_CH0_RXDESC_TAIL_POINTER = (uint32_t)&rxdesc_tab[(ENET_RXBUF_NUM)];
    break;
    
    case DMACH1: 
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_OWN)) {
        return status;
    }
     /* get the context descriptor with timestamp information */
     if((enet_descriptors_struct *)(uint32_t)&rxdesc_tab1[(ENET_RXBUF_NUM - 1U)] == dma_current_rxdesc1) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_context_rxdesc = (enet_descriptors_struct *)(ENET_DMA_CH1_RXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_context_rxdesc = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_rxdesc1 + ETH_DMARXDESC_SIZE);
    }
    
    /* if buffer pointer is null, indicates that users has copied data in application */
    if(NULL != buffer) {
        /* if no error occurs, and the frame uses only one descriptor */
        if((((uint32_t)RESET) == (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_ES)) &&
                (((uint32_t)RESET) != (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_LD)) &&
                (((uint32_t)RESET) != (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_FD))) {
            /* get the frame length except CRC */
            size = dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_PL;
            size = size - 4U;

            /* if is a type frame, and CRC is not included in forwarding frame */
            if(((uint32_t)RESET != (ENET_MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_CST)) && ((uint32_t)RESET != (dma_current_rxdesc1->DES3 & ENET_NORMAL_RDES3_WF_LT))) {
                size = size + 4U;
            } else {
              /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }

            /* to avoid situation that the frame size exceeds the buffer length */
            if(size > bufsize) {
                return status;
            } else {
              /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
            }

            /* copy data from Rx buffer to application buffer */
            for(offset = 0U; offset < size; offset++) {
                (*(buffer + offset)) = (*(__IO uint8_t *)(uint32_t)((dma_current_rxdesc1->buffer_address) + offset));
            }

        } else {
            /* return ERROR */
            return status;
        }
    }

    /* copy the timestamp from the context descriptor. */
    timestamp[0] = dma_context_rxdesc->DES0;
    timestamp[1] = dma_context_rxdesc->DES1;
    
    dma_current_rxdesc1->DES0 = dma_current_rxdesc1->buffer_address;
    dma_current_rxdesc1->DES1 = dma_current_rxdesc1->bkp_info;
    
    dma_context_rxdesc->DES0 = dma_context_rxdesc->buffer_address;
    dma_context_rxdesc->DES1 = dma_context_rxdesc->bkp_info;

    /* enable reception, descriptor is owned by DMA */
    dma_current_rxdesc1->DES3 = ENET_NORMAL_RDES3_WF_OWN | ENET_NORMAL_RDES3_RF_BUF1V;
    dma_context_rxdesc->DES3 = ENET_NORMAL_RDES3_WF_OWN | ENET_NORMAL_RDES3_RF_BUF1V;
    
    /* If the receive interrupt is enabled, the IOC bit needs to be set */
    if((uint32_t)RESET != (ENET_DMA_CH1_INTERRUPT_ENABLE & ENET_DMA_CH_INTERRUPT_ENABLE_RIE)) {
        dma_current_rxdesc1->DES3 |= ENET_NORMAL_RDES3_RF_IOC;
        dma_context_rxdesc->DES3 |= ENET_NORMAL_RDES3_RF_IOC;
    }
    __DMB();
    
    /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
    /* ring mode */
    if((enet_descriptors_struct *)(uint32_t)&rxdesc_tab1[(ENET_RXBUF_NUM - 1U)] == dma_context_rxdesc) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_rxdesc1 = (enet_descriptors_struct *)(ENET_DMA_CH1_RXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_rxdesc1 = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_context_rxdesc + ETH_DMARXDESC_SIZE);
    }
    ENET_DMA_CH1_RXDESC_TAIL_POINTER = (uint32_t)&rxdesc_tab1[(ENET_RXBUF_NUM)];
    break;
    default:
       break;
    }
    status = SUCCESS;
}
    return status;
}

/*!
    \brief    send data with timestamp values in application buffer as a transmit packet, when the DMA is in normal mode
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  buffer: pointer on the application buffer
                note -- if the input is NULL, user should copy data in application by himself
    \param[in]  length: the length of frame data to be transmitted
    \param[out] timestamp: pointer to the table which stores the timestamp high and low
                note -- if the input is NULL, timestamp is ignored
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_ptpframe_transmit_normal_mode(enet_dmach_enum dmach, uint8_t *buffer, uint32_t length, uint32_t timestamp[])
{
    uint32_t offset, timeout;
    uint32_t tdes3_own_flag;
    ErrStatus status;
    status = ERROR;
    timeout = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_BUFSIZE(length)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0077U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0: 
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_txdesc->DES3 & ENET_NORMAL_TDES3_WF_OWN)) {
        return status;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

#ifndef FW_DEBUG_ERR_REPORT
    /* only frame length no more than ENET_MAX_FRAME_SIZE is allowed */
    if(length > ENET_MAX_FRAME_SIZE) {
        return status;
    } else {
    
    }
#endif /* FW_DEBUG_ERR_REPORT */
    
    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0U; offset < length; offset++) {
            (*(__IO uint8_t *)(uint32_t)((dma_current_txdesc->buffer_address) + offset)) = (*(buffer + offset));
        }
    }

    /* set the frame length */
    dma_current_txdesc->DES2 = length | ENET_NORMAL_TDES2_RF_TTSE;
    /* set the segment of frame, frame is transmitted in one descriptor */
    dma_current_txdesc->DES3 |= ENET_NORMAL_TDES3_WF_FD | ENET_NORMAL_TDES3_WF_LD;
    /* enable the DMA transmission */
    dma_current_txdesc->DES3 |= ENET_NORMAL_TDES3_WF_OWN;
    /* if timestamp pointer is null, indicates that users don't care timestamp in application */
    dma_current_txdesc->DES0 = dma_current_txdesc->buffer_address ;
    dma_current_txdesc->DES1 = dma_current_txdesc->bkp_info;
    __DMB();
    /* check Tx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_CH0_STATUS & ENET_DMA_CH_STATUS_TBU)) {
        /* clear TBU flag */
        ENET_DMA_CH0_STATUS &= ~ENET_DMA_CH_STATUS_TBU;
    }
    ENET_DMA_CH0_TXDESC_TAIL_POINTER = (uint32_t)dma_current_txdesc + sizeof(enet_descriptors_struct);  
    
    if(NULL != timestamp) {
        /* wait for own bit to be clear, a timestamp was captured */
        do {
            tdes3_own_flag = (dma_current_txdesc->DES3 & ENET_NORMAL_TDES3_WF_OWN);
            timeout++;
        } while(((uint32_t)RESET != tdes3_own_flag) && (timeout < ENET_DELAY_TO));

        /* return ERROR due to timeout */
        if(ENET_DELAY_TO == timeout) {
            return status;
        }

         /* clear the ENET_NORMAL_TDES3_WF_TTSS flag */
        dma_current_txdesc->DES3 &= ~ENET_NORMAL_TDES3_WF_TTSS;
        /* get the timestamp value of the transmit frame */
        timestamp[0] = dma_current_txdesc->DES0;
        timestamp[1] = dma_current_txdesc->DES1;
    }

    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table*/
    /* ring mode */
    if((enet_descriptors_struct *)(ENET_DMA_CH0_TXDESC_ADDRESS + (ENET_TXBUF_NUM - 1U) * sizeof(enet_descriptors_struct)) <= dma_current_txdesc) {
        /* if is the last descriptor in table, the next descriptor is the table header */
       dma_current_txdesc = (enet_descriptors_struct *)(ENET_DMA_CH0_TXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
       dma_current_txdesc = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_txdesc + ETH_DMATXDESC_SIZE);
    }

    break;
    case DMACH1: 
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_txdesc1->DES3 & ENET_NORMAL_TDES3_WF_OWN)) {
        return status;
    } else {
        /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'is ... else if' chain) */
    }

#ifndef FW_DEBUG_ERR_REPORT
    /* only frame length no more than ENET_MAX_FRAME_SIZE is allowed */
    if(length > ENET_MAX_FRAME_SIZE) {
        return status;
    } else {
    
    }
#endif /* FW_DEBUG_ERR_REPORT */
    
    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0U; offset < length; offset++) {
            (*(__IO uint8_t *)(uint32_t)((dma_current_txdesc1->buffer_address) + offset)) = (*(buffer + offset));
        }
    }

    /* set the frame length */
    dma_current_txdesc1->DES2 = length | ENET_NORMAL_TDES2_RF_TTSE;
    /* set the segment of frame, frame is transmitted in one descriptor */
    dma_current_txdesc1->DES3 |= ENET_NORMAL_TDES3_WF_FD | ENET_NORMAL_TDES3_WF_LD;
    /* enable the DMA transmission */
    dma_current_txdesc1->DES3 |= ENET_NORMAL_TDES3_WF_OWN;
    /* if timestamp pointer is null, indicates that users don't care timestamp in application */
    dma_current_txdesc1->DES0 = dma_current_txdesc1->buffer_address ;
    dma_current_txdesc1->DES1 = dma_current_txdesc1->bkp_info;
    __DMB();
    /* check Tx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_CH1_STATUS & ENET_DMA_CH_STATUS_TBU)) {
        /* clear TBU flag */
        ENET_DMA_CH1_STATUS &= ~ENET_DMA_CH_STATUS_TBU;
    }
    ENET_DMA_CH1_TXDESC_TAIL_POINTER = (uint32_t)dma_current_txdesc1 + sizeof(enet_descriptors_struct);  
    
    if(NULL != timestamp) {
        /* wait for own bit to be clear, a timestamp was captured */
        do {
            tdes3_own_flag = (dma_current_txdesc1->DES3 & ENET_NORMAL_TDES3_WF_OWN);
            timeout++;
        } while(((uint32_t)RESET != tdes3_own_flag) && (timeout < ENET_DELAY_TO));

        /* return ERROR due to timeout */
        if(ENET_DELAY_TO == timeout) {
            return status;
        }

         /* clear the ENET_NORMAL_TDES3_WF_TTSS flag */
        dma_current_txdesc1->DES3 &= ~ENET_NORMAL_TDES3_WF_TTSS;
        /* get the timestamp value of the transmit frame */
        timestamp[0] = dma_current_txdesc1->DES0;
        timestamp[1] = dma_current_txdesc1->DES1;
    }

    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table*/
    /* ring mode */
    if((enet_descriptors_struct *)(ENET_DMA_CH1_TXDESC_ADDRESS + (ENET_TXBUF_NUM - 1U) * sizeof(enet_descriptors_struct)) <= dma_current_txdesc1) {
        /* if is the last descriptor in table, the next descriptor is the table header */
       dma_current_txdesc1 = (enet_descriptors_struct *)(ENET_DMA_CH1_TXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
       dma_current_txdesc1 = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_txdesc1 + ETH_DMATXDESC_SIZE);
    }

    break;
    default:
       break;
    }
    status = SUCCESS;
}
    return status;
}

#if defined (DMACH0_USE_ENHANCED_MODE) || (DMACH1_USE_ENHANCED_MODE)

/*!
    \brief    handle application buffer data to transmit it based on TBS function
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  buffer: pointer to the frame data to be transmitted,
                note -- if the input is NULL, user should handle the data in application by himself
    \param[in]  length: the length of frame data to be transmitted
    \param[in]  launch_time: launch time associated with the packet
    \param[in]  gsn_num: GCL slot number associated with the packet
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_frame_transmit_tbs(enet_dmach_enum dmach, uint8_t *buffer, uint32_t length, uint32_t launch_time, uint32_t gsn_num)
{
    uint32_t offset;
    ErrStatus status;
    status = ERROR;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_BUFSIZE(length)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0078U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{

    switch(dmach) {
    case DMACH0: 
#ifdef DMACH0_USE_ENHANCED_MODE
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_tbs_txdesc->DES3 & ENET_NORMAL_TDES3_WF_OWN)) {
        return status;
    }

#ifndef FW_DEBUG_ERR_REPORT
    /* only frame length no more than ENET_MAX_FRAME_SIZE is allowed */
    if(length > ENET_MAX_FRAME_SIZE) {
        return status;
    } else {
    
    }
#endif /* FW_DEBUG_ERR_REPORT */

    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0U; offset < length; offset++) {
            (*(__IO uint8_t *)(uint32_t)((dma_current_tbs_txdesc->DES0) + offset)) = (*(buffer + offset));
        }
    }

    /* set the launch time */
    dma_current_tbs_txdesc->ETDES0 = (launch_time >> 24);
    dma_current_tbs_txdesc->ETDES1 = (launch_time << 8);
    dma_current_tbs_txdesc->ETDES0 |= (gsn_num << 8) | ENET_ENHANCED_ETDES0_LTV;

    /* set the frame length */
    dma_current_tbs_txdesc->DES2 = length;
    /* set the segment of frame, frame is transmitted in one descriptor */
    dma_current_tbs_txdesc->DES3 |= ENET_NORMAL_TDES3_WF_FD | ENET_NORMAL_TDES3_WF_LD;
    /* enable the DMA transmission */
    dma_current_tbs_txdesc->DES3 |= ENET_NORMAL_TDES3_WF_OWN;
    __DSB();
    __ISB();
    __DMB();

    /* check Tx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_CH0_STATUS & ENET_DMA_CH_STATUS_TBU)) {
        /* clear TBU flag */
        ENET_DMA_CH0_STATUS &= ~ENET_DMA_CH_STATUS_TBU;
    }
    ENET_DMA_CH0_TXDESC_TAIL_POINTER = (uint32_t)dma_current_tbs_txdesc + sizeof(enet_tbs_enhanced_descriptors_struct);

    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table*/
    /* ring mode */
    if((enet_tbs_enhanced_descriptors_struct *)(ENET_DMA_CH0_TXDESC_ADDRESS + (ENET_TXBUF_NUM-1U) * sizeof(enet_tbs_enhanced_descriptors_struct)) <= dma_current_tbs_txdesc) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_tbs_txdesc = (enet_tbs_enhanced_descriptors_struct *)(ENET_DMA_CH0_TXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_tbs_txdesc = (enet_tbs_enhanced_descriptors_struct *)(uint32_t)((uint32_t)dma_current_tbs_txdesc + ENET_ENHANCED_DMATXDESC_SIZE);
    }
 #endif /* DMACH0_USE_ENHANCED_MODE */
    break;

    case DMACH1:
#ifdef DMACH1_USE_ENHANCED_MODE
    /* the descriptor is busy due to own by the DMA */
    if((uint32_t)RESET != (dma_current_tbs_txdesc1->DES3 & ENET_NORMAL_TDES3_WF_OWN)) {
        return status;
    }

#ifndef FW_DEBUG_ERR_REPORT
    /* only frame length no more than ENET_MAX_FRAME_SIZE is allowed */
    if(length > ENET_MAX_FRAME_SIZE) {
        return status;
    } else {
    
    }
#endif /* FW_DEBUG_ERR_REPORT */

    /* if buffer pointer is null, indicates that users has handled data in application */
    if(NULL != buffer) {
        /* copy frame data from application buffer to Tx buffer */
        for(offset = 0U; offset < length; offset++) {
            (*(__IO uint8_t *)(uint32_t)((dma_current_tbs_txdesc1->DES0) + offset)) = (*(buffer + offset));
        }
    }

    /* set the launch time */
    dma_current_tbs_txdesc1->ETDES0 = (launch_time >> 24);
    dma_current_tbs_txdesc1->ETDES1 = (launch_time << 8);
    dma_current_tbs_txdesc1->ETDES0 |= (gsn_num << 8) | ENET_ENHANCED_ETDES0_LTV;

    /* set the frame length */
    dma_current_tbs_txdesc1->DES2 = length;
    /* set the segment of frame, frame is transmitted in one descriptor */
    dma_current_tbs_txdesc1->DES3 |= ENET_NORMAL_TDES3_WF_FD | ENET_NORMAL_TDES3_WF_LD;
    /* enable the DMA transmission */
    dma_current_tbs_txdesc1->DES3 |= ENET_NORMAL_TDES3_WF_OWN;
    __DSB();
    __ISB();
    __DMB();

    /* check Tx buffer unavailable flag status */
    if((uint32_t)RESET != (ENET_DMA_CH1_STATUS & ENET_DMA_CH_STATUS_TBU)) {
        /* clear TBU flag */
        ENET_DMA_CH1_STATUS &= ~ENET_DMA_CH_STATUS_TBU;
    }
    ENET_DMA_CH1_TXDESC_TAIL_POINTER = (uint32_t)dma_current_tbs_txdesc1 + sizeof(enet_tbs_enhanced_descriptors_struct);

    /* update the current TxDMA descriptor pointer to the next decriptor in TxDMA decriptor table*/
    /* ring mode */
    if((enet_tbs_enhanced_descriptors_struct *)(ENET_DMA_CH1_TXDESC_ADDRESS + (ENET_TXBUF_NUM-1U) * sizeof(enet_tbs_enhanced_descriptors_struct)) <= dma_current_tbs_txdesc1) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_tbs_txdesc1 = (enet_tbs_enhanced_descriptors_struct *)(ENET_DMA_CH1_TXDESC_ADDRESS);
    } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_tbs_txdesc1 = (enet_tbs_enhanced_descriptors_struct *)(uint32_t)((uint32_t)dma_current_tbs_txdesc1 + ENET_ENHANCED_DMATXDESC_SIZE);
    }
#endif /* DMACH1_USE_ENHANCED_MODE */
    break;
    default:
       break;
    }
    status = SUCCESS;
}
    return status;
}
#endif /* defined(DMACH0_USE_ENHANCED_MODE || DMACH1_USE_ENHANCED_MODE) */

/*!
    \brief      compute the CRC of a hardware address
    \param[in]  mac: the hardware addresss
    \param[in]  size: the size of mac address
    \param[out] none
    \retval     crc_val: the result of crc value
*/
uint32_t enet_crc_compute(uint8_t *macaddr, uint8_t size)
{
    uint32_t crc_val;
    uint32_t i, j;
    crc_val = 0xFFFFFFFFUL;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(macaddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0079U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    for(i = 0; i < size; i++) {
        crc_val = crc_val ^ macaddr[i];
        for(j = 0; j < 8U; j++) {
            if((crc_val & 0x1U) != 0U) {
                crc_val = (crc_val >> 1U) ^ 0xEDB88320U;
            } else {
                crc_val = (crc_val >> 1U);
            }
        }
    }
}
    return ~crc_val;
}

/*!
    \brief      bitwise reversal on a 32 bit value
    \param[in]  val: the 32 bit value
    \param[out] none
    \retval     rev_val: the result of bitwise reversal
*/
uint32_t enet_value_reverse(uint32_t val)
{
    uint32_t rev_val = 0U;
    uint32_t i;
    for(i = 0U; i < 32U; i++) {
        if((uint32_t)RESET != (val & ((uint32_t)1U << (i & 0x1FU)))) {
            rev_val |= (uint32_t)((uint32_t)1U << ((uint32_t)31U - i));
        }
    }
    return rev_val;
}

/*!
    \brief      set the vlan filter dma selection
    \param[in]  filter: the filter register selection
                only one parameter can be selected which is shown as below
      \arg        MAC_VLAN_TAG_FILTER0: filter register 0
      \arg        MAC_VLAN_TAG_FILTER1: filter register 1
      \arg        MAC_VLAN_TAG_FILTER2: filter register 2
      \arg        MAC_VLAN_TAG_FILTER3: filter register 3
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_vlantag_filter_dmach_select(uint32_t filter, enet_dmach_enum dmach)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT, reg_val;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_MAC_VLAN_TAG_FILTER(filter)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x007BU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* read vlan tag filterx value */
    ENET_MAC_VLAN_TAG_CTRL &= ~ENET_MAC_VLAN_TAG_CTRL_OFS;
    ENET_MAC_VLAN_TAG_CTRL |= ENET_MAC_VLAN_TAG_CTRL_CT;
    ENET_MAC_VLAN_TAG_CTRL |= (filter >> 19U) | ENET_MAC_VLAN_TAG_CTRL_OB;
    while(((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OB))&& (0U < timeout)) {
        timeout --;
    }
    reg_val = ENET_MAC_VLAN_TAG_DATA;
    reg_val &= ~ENET_MAC_VLAN_TAG_DATA_DMACHN;
    reg_val |= ((uint32_t)dmach << 25U) | ENET_MAC_VLAN_TAG_DATA_DMACHEN;
    
    timeout = ENET_OPERATION_TIMEROUT;
    /* write vlan tag filterx  */
    ENET_MAC_VLAN_TAG_DATA = reg_val;
    ENET_MAC_VLAN_TAG_CTRL &= ~ENET_MAC_VLAN_TAG_CTRL_CT;
    ENET_MAC_VLAN_TAG_CTRL |= (filter >> 19U) | ENET_MAC_VLAN_TAG_CTRL_OB;
    while(((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OB))&& (0U < timeout)) {
        timeout --;
    }
}
}

/*!
    \brief      set up vlan filter feature
    \param[in]  filter: the filter register selection
                only one parameter can be selected which is shown as below
      \arg        MAC_VLAN_TAG_FILTER0: filter register 0
      \arg        MAC_VLAN_TAG_FILTER1: filter register 1
      \arg        MAC_VLAN_TAG_FILTER2: filter register 2
      \arg        MAC_VLAN_TAG_FILTER3: filter register 3
    \param[in]  feature: the vlan filter feature need to write
                only one parameter can be selected which is shown as below
      \arg        ENET_VLANTAGCOMPARISON_INNER: enable inner VLAN tag comparison
      \arg        ENET_SVLANTAGMATCH_ENABLE: enable S-VLAN match for received frames
      \arg        ENET_VLANTAGCOMPARISON_12BIT: 12-bit VLAN comparison
      \arg        ENET_VLANTAGCOMPARISON_ENABLE: VLAN tag enable
      \arg        ENET_VLANTYPECOMPARISON_DISABLE: disable VLAN type comparison
    \param[out] none
    \retval     none
*/
void enet_vlantag_filter_feature_set(uint32_t filter, uint32_t feature)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT, reg_val;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_MAC_VLAN_TAG_FILTER(filter)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x007CU), ERR_PARAM_POINTER);
    } else if(NOT_ENET_VLAN_FILTER_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x007CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* read vlan tag filterx value */
    ENET_MAC_VLAN_TAG_CTRL &= ~ENET_MAC_VLAN_TAG_CTRL_OFS;
    ENET_MAC_VLAN_TAG_CTRL |= ENET_MAC_VLAN_TAG_CTRL_CT;
    ENET_MAC_VLAN_TAG_CTRL |= (filter >> 19U) | ENET_MAC_VLAN_TAG_CTRL_OB;
    while(((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OB))&& (0U < timeout)) {
        timeout --;
    }
    reg_val = ENET_MAC_VLAN_TAG_DATA;
    reg_val |= feature;
    
    timeout = ENET_OPERATION_TIMEROUT;
    /* write vlan tag filterx  */
    ENET_MAC_VLAN_TAG_DATA = reg_val;
    ENET_MAC_VLAN_TAG_CTRL &= ~(ENET_MAC_VLAN_TAG_CTRL_CT);
    ENET_MAC_VLAN_TAG_CTRL |= (filter >> 19U) | ENET_MAC_VLAN_TAG_CTRL_OB;
    while(((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OB))&& (0U < timeout)) {
        timeout --;
    }
    
}
}

/*!
    \brief      set up vlan filter tag ID
    \param[in]  filter: the filter register selection
                only one parameter can be selected which is shown as below
      \arg        MAC_VLAN_TAG_FILTER0: filter register 0
      \arg        MAC_VLAN_TAG_FILTER1: filter register 1
      \arg        MAC_VLAN_TAG_FILTER2: filter register 2
      \arg        MAC_VLAN_TAG_FILTER3: filter register 3
    \param[in]  val: the vlan filter tag ID
    \param[out] none
    \retval     none
*/
void enet_vlantag_filter_vid_set(uint32_t filter, uint32_t val)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT, reg_val;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_MAC_VLAN_TAG_FILTER(filter)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x007DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* read vlan tag filterx value */
    ENET_MAC_VLAN_TAG_CTRL &= ~ENET_MAC_VLAN_TAG_CTRL_OFS;
    ENET_MAC_VLAN_TAG_CTRL |= ENET_MAC_VLAN_TAG_CTRL_CT;
    ENET_MAC_VLAN_TAG_CTRL |= (filter >> 19U) | ENET_MAC_VLAN_TAG_CTRL_OB;
    while(((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OB))&& (0U < timeout)) {
        timeout --;
    }
    reg_val = ENET_MAC_VLAN_TAG_DATA;
    reg_val &= ~ENET_MAC_VLAN_TAG_DATA_VID;
    reg_val |= val;
    
    timeout = ENET_OPERATION_TIMEROUT;
    /* write vlan tag filterx  */
    ENET_MAC_VLAN_TAG_DATA = reg_val;
    ENET_MAC_VLAN_TAG_CTRL &= ~ENET_MAC_VLAN_TAG_CTRL_CT ;
    ENET_MAC_VLAN_TAG_CTRL |= (filter >> 19U) | ENET_MAC_VLAN_TAG_CTRL_OB;
    while(((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_OB))&& (0U < timeout)) {
        timeout --;
    }
}
}

/*!
    \brief      add an address entry to the hash table filter
    \param[in]  macaddr: the hardware address
    \param[out] none
    \retval     none
*/
void enet_add_dstaddr_hashfilter(uint8_t *macaddr)
{
    uint32_t crc_val;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(macaddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x007EU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    crc_val = enet_crc_compute(macaddr, 6U);

    if((uint32_t)RESET == ((enet_value_reverse(crc_val) >> 0x1FU) & 1U)) {
        ENET_MAC_HASH_TABLE_REG0 |= (uint32_t)((uint32_t)1U << ((enet_value_reverse(crc_val) >> 0x1AU) & 0x1FU));
    } else {
        ENET_MAC_HASH_TABLE_REG1 |= (uint32_t)((uint32_t)1U << ((enet_value_reverse(crc_val) >> 0x1AU) & 0x1FU));
    }
}
}

/*!
    \brief      remove an address entry to the hash table filter
    \param[in]  macaddr: the hardware addresss
    \param[out] none
    \retval     none
*/
void enet_remove_dstaddr_hashfilter(uint8_t *macaddr)
{
    uint32_t crc_val;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(macaddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x007FU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    crc_val = enet_crc_compute(macaddr, 6U);

    if((uint32_t)RESET == ((enet_value_reverse(crc_val) >> 0x1FU) & 1U)) {
        ENET_MAC_HASH_TABLE_REG0 &= ~(1U << ((enet_value_reverse(crc_val) >> 0x1AU) & 0x1FU));
    } else {
        ENET_MAC_HASH_TABLE_REG1 &= ~(1U << ((enet_value_reverse(crc_val) >> 0x1AU) & 0x1FU));
    }
}
}

/*!
    \brief      add a vlan tag entry to the hash table filter
    \param[in]  tagval: the vlan tag value
    \param[out] none
    \retval     none
*/
void enet_add_vlantag_hashtable(uint32_t tagval)
{
    uint32_t index, crc_val;

    crc_val = enet_crc_compute((uint8_t *)&tagval, 2);

    index = (enet_value_reverse(crc_val) & BITS(28, 31)) >> 28U;


    if((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_ETV)) {
        index = index - 1UL;
    }

    ENET_MAC_VLAN_HASH_TABLE |= ((uint32_t)1U << (index & 0x1FU));
}

/*!
    \brief      remove a vlan tag entry to the hash table filter
    \param[in]  tagval: the vlan tag value
    \param[out] none
    \retval     none
*/
void enet_remove_vlantag_hashtable(uint32_t tagval)
{
    uint32_t index, crc_val;
    crc_val = enet_crc_compute((uint8_t *)&tagval, 2);
    index = (enet_value_reverse(crc_val) & BITS(28, 31)) >> 28U;


    if((uint32_t)RESET != (ENET_MAC_VLAN_TAG_CTRL & ENET_MAC_VLAN_TAG_CTRL_ETV)) {
        index = index - 1UL;
    }

    ENET_MAC_VLAN_HASH_TABLE &= ~((uint32_t)1U << (index & 0xFU));
}

/*!
    \brief      enable flexible Rx parser
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_parser_enable(void)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;

    uint32_t temp_state;
    ENET_MAC_CONFIGURATION &= ~ENET_MAC_CONFIGURATION_RE;
    do {
        temp_state = ENET_MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_RE;
        timeout --;
    } while(((uint32_t)RESET != temp_state) && (0U < timeout)) ;

    ENET_MTL_OPERATION_MODE |= ENET_MTL_OPERATION_MODE_FRPE;
    ENET_MAC_CONFIGURATION |= ENET_MAC_CONFIGURATION_RE;
}

/*!
    \brief      disable flexible Rx parser
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_parser_disable(void)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
    uint32_t temp_state;
    ENET_MAC_CONFIGURATION &= ~ENET_MAC_CONFIGURATION_RE;
    do {
        temp_state = ENET_MAC_CONFIGURATION & ENET_MAC_CONFIGURATION_RE;
        timeout --;
    } while(((uint32_t)RESET != temp_state) && (0U < timeout)) ;

    ENET_MTL_OPERATION_MODE &= ~ENET_MTL_OPERATION_MODE_FRPE;

    ENET_MAC_CONFIGURATION |= ENET_MAC_CONFIGURATION_RE;
}

/*!
    \brief    set the number of entries in the Instruction table
    \param[in]  type: choose the type of entry in the instruction table which users want to check, refer to enet_entry_type_enum
                only one parameter can be selected which is shown as below
      \arg        PARSABLE_ENTRY: parsable entries in the Instruction table
      \arg        VALID_ENTRY: valid entries in the instruction table
    \param[in]  value: the value of entries number
    \param[out] none
    \retval     none
*/
void enet_parser_entry_number_set(enet_entry_type_enum type, uint32_t value)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_ENTRY_NUMBER(value)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0084U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(type) {
    case PARSABLE_ENTRY:
        ENET_MTL_RXP_CONTROL_STATUS &= ~ENET_MTL_RXP_CONTROL_STATUS_NPE;
        ENET_MTL_RXP_CONTROL_STATUS |= MTL_RXP_CONTROL_STATUS_NPE(value);
        break;
    case VALID_ENTRY:
        ENET_MTL_RXP_CONTROL_STATUS &= ~ENET_MTL_RXP_CONTROL_STATUS_NVE;
        ENET_MTL_RXP_CONTROL_STATUS |= MTL_RXP_CONTROL_STATUS_NVE(value);
        break;
    default:
        break;
    }
}
}

/*!
    \brief      config the instruction table entry
    \param[in]  value: the value of instruction table
    \param[in]  addr: the offset address of instruction table
    \param[out] none
    \retval     none
*/
void enet_parser_table_entry_config(uint32_t *value, uint8_t addr)
{
    uint32_t i;
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(value)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0085U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    for(i = 0; i < 4U; i++) {
        /* wait until STARTBUSY bit is clear */
        while((((uint32_t)RESET != (ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS & ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY))) && (0U < timeout)) {
            timeout --;
        }
        ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS = MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR(addr) | ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN;
        ENET_MTL_RXP_INDIRECT_ACC_DATA = value[i];
        ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS |= ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY;
        addr += 1U;
    }
}
}

/*!
    \brief      get the value of instruction table
    \param[in]  addr: the offset address of instruction table
    \param[out] value: the value of instruction table
    \retval     none
*/
void enet_parser_table_entry_get(uint32_t *value, uint32_t addr)
{
    uint32_t i;
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(value)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0086U), ERR_PARAM_POINTER);
    } else if(NOT_ENET_ENTRY_NUMBER(addr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0086U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{

    for(i = 0; i < 4U; i++) {
       
        ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS = MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR(addr);
        ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS &= ~ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN;
        ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS |= ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY;
            /* wait until BUSY bit is clear */
        while(((uint32_t)RESET != (ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS & ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY)) && (0U < timeout)) {
            timeout --;
        }
        value[i] = ENET_MTL_RXP_INDIRECT_ACC_DATA;

        addr += 1U;
    }
}
}

/*!
    \brief    get MTL parser overflow flag
    \param[in]  counter: choose the parser counter, refer to enet_parser_counter_enum
                only one parameter can be selected which is shown as below
      \arg            MTL_PAESER_BYPASS_COUNTER: parsable bypass counter
      \arg            MTL_PAESER_ERROR_COUNTER: parsable error counter
      \arg            MTL_PAESER_DROP_COUNTER: parsable drop counter
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus enet_parser_overflow_flag_get(enet_parser_counter_enum counter)
{
    FlagStatus flag = RESET;
    switch(counter) {
    case MTL_PAESER_BYPASS_COUNTER:
        if((uint32_t)RESET != GET_PARSER_OVERFLOW_FLAG(ENET_MTL_RXP_BYPASS_CNT)) {
            flag = SET;
        } else {
            flag = RESET;
        }
        break;
    case MTL_PAESER_ERROR_COUNTER:
        if((uint32_t)RESET != GET_PARSER_OVERFLOW_FLAG(ENET_MTL_RXP_ERROR_CNT)) {
            flag = SET;
        } else {
            flag = RESET;
        }
        break;
    case MTL_PAESER_DROP_COUNTER:
        if((uint32_t)RESET != GET_PARSER_OVERFLOW_FLAG(ENET_MTL_RXP_DROP_CNT)) {
            flag = SET;
        } else {
            flag = RESET;
        }
        break;
    default:
        break;
    }
    return flag;
}

/*!
    \brief    get MTL parser related count
    \param[in]  counter: choose the parser counter, refer to enet_parser_counter_enum
                only one parameter can be selected which is shown as below
      \arg            MTL_PAESER_BYPASS_COUNTER: parsable bypass counter
      \arg            MTL_PAESER_ERROR_COUNTER: parsable error counter
      \arg            MTL_PAESER_DROP_COUNTER: parsable drop counter
    \param[out] none
    \retval     cnt_val: the value of MTL parser related counter
*/
uint32_t enet_parser_count_get(enet_parser_counter_enum counter)
{
    uint32_t cnt_val;
    cnt_val = 0U;

    switch(counter) {
    case MTL_PAESER_BYPASS_COUNTER:
        cnt_val = GET_PARSER_COUNT(ENET_MTL_RXP_BYPASS_CNT);
        break;
    case MTL_PAESER_ERROR_COUNTER:
        cnt_val = GET_PARSER_COUNT(ENET_MTL_RXP_ERROR_CNT);
        break;
    case MTL_PAESER_DROP_COUNTER:
        cnt_val = GET_PARSER_COUNT(ENET_MTL_RXP_DROP_CNT);
        break;
    default:
        break;
    }
    return cnt_val;
}

/*!
    \brief    select the DMA channel number for the packet that is passed by this L3_L4 filter
    \param[in]  filter: choose the channel number for the packet that is passed by this L3_L4 filter, refer to enet_l3l4_filter_enum
                only one parameter can be selected which is shown as below
      \arg            L3L4_FILTER0: L3/L4 filter 0
      \arg            L3L4_FILTER1: L3/L4 filter 1
      \arg            L3L4_FILTER2: L3/L4 filter 2
      \arg            L3L4_FILTER3: L3/L4 filter 3
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_l3l4_filter_dmach_select(enet_l3l4_filter_enum filter, enet_dmach_enum dmach)
{
    switch(filter) {
    case L3L4_FILTER0:
        ENET_MAC_L3_L4_CONTROL0 |= ENET_MAC_L3_L4_CONTROL_DMCHEN0;
        ENET_MAC_L3_L4_CONTROL0 |= MAC_L3_L4_CONTROL_DMCHN0(dmach);
        break;
    case L3L4_FILTER1:
        ENET_MAC_L3_L4_CONTROL1 |= ENET_MAC_L3_L4_CONTROL_DMCHEN0;
        ENET_MAC_L3_L4_CONTROL1 |= MAC_L3_L4_CONTROL_DMCHN0(dmach);
        break;
    case L3L4_FILTER2:
        ENET_MAC_L3_L4_CONTROL2 |= ENET_MAC_L3_L4_CONTROL_DMCHEN0;
        ENET_MAC_L3_L4_CONTROL2 |= MAC_L3_L4_CONTROL_DMCHN0(dmach);
        break;
    case L3L4_FILTER3:
        ENET_MAC_L3_L4_CONTROL3 |= ENET_MAC_L3_L4_CONTROL_DMCHEN0;
        ENET_MAC_L3_L4_CONTROL3 |= MAC_L3_L4_CONTROL_DMCHN0(dmach);
        break;
    default:
        break;
    }
}

/*!
    \brief    config the L3_L4 filter related function
    \param[in]  filter: choose the channel number for the packet that is passed by this L3_L4 filter, refer to enet_l3l4_filter_enum
                only one parameter can be selected which is shown as below
      \arg            L3L4_FILTER0: L3/L4 filter 0
      \arg            L3L4_FILTER1: L3/L4 filter 1
      \arg            L3L4_FILTER2: L3/L4 filter 2
      \arg            L3L4_FILTER3: L3/L4 filter 3
    \param[in]  function: the related configuration of L3_L4 filter
                only one parameter can be selected which is shown as below
      \arg            ENET_L4_DEST_PORT_NORMAL_MATCH: the layer 4 destination port number field is configurated for matching
      \arg            ENET_L4_DEST_PORT_INVERSE_MATCH: the layer 4 destination port number field is configurated for inverse matching
      \arg            ENET_L4_SRC_PORT_NORMAL_MATCH_ENABLE: the layer 4 source port number field is configurated for matching
      \arg            ENET_L4_SRC_PORT_INVERSE_MATCH_ENABLE: the layer 4 source port number field is configurated for inverse matching
      \arg            ENET_L4_PROTOCOL_MATCH_UDP: the source and destination port number fields of UDP packets are used for matching
      \arg            ENET_L3_DEST_IPADDR_NORMAL_MATCH: the layer 3 IP destination address field is configurated for matching
      \arg            ENET_L3_DEST_IPADDR_INVERSE_MATCH: the layer 3 IP destination address field is configurated for inverse matching
      \arg            ENET_L3_SRC_IPADDR_NORMAL_MATCH: the Layer 3 IP source address field is configurated for matching
      \arg            ENET_L3_SRC_IPADDR_INVERSE_MATCH: the layer 3 IP source address field is configurated for inverse matching
      \arg            ENET_L3_PROTOCOL_MATCH_IPV6: the layer 3 IP source or destination address matching is configurated for IPv6 packets
    \param[in]  status: the status of L3L4_FILTERx
                only one parameter can be selected which is shown as below:
      \arg        ENABLE: enable
      \arg        DISABLE: disable
    \param[out] none
    \retval     none
*/
void enet_l3l4_filter_config(enet_l3l4_filter_enum filter, uint32_t function, ControlStatus status)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_L3_L4_FILTER_CFG(function)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x008AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if(ENABLE == status) {
    switch(filter) {
    case L3L4_FILTER0:
        ENET_MAC_L3_L4_CONTROL0 |= function;
        break;
    case L3L4_FILTER1:
        ENET_MAC_L3_L4_CONTROL1 |= function;
        break;
    case L3L4_FILTER2:
        ENET_MAC_L3_L4_CONTROL2 |= function;
        break;
    case L3L4_FILTER3:
        ENET_MAC_L3_L4_CONTROL3 |= function;
        break;
    default:
        break;
    }
    } else {
        switch(filter) {
    case L3L4_FILTER0:
        ENET_MAC_L3_L4_CONTROL0 &= ~function;
        break;
    case L3L4_FILTER1:
        ENET_MAC_L3_L4_CONTROL1 &= ~function;
        break;
    case L3L4_FILTER2:
        ENET_MAC_L3_L4_CONTROL2 &= ~function;
        break;
    case L3L4_FILTER3:
        ENET_MAC_L3_L4_CONTROL3 &= ~function;
        break;
    default:
        break;
    }
    }
}
}

/*!
    \brief     set the L4 filter port number
    \param[in]  filter: choose the channel number for the packet that is passed by this L3_L4 filter, refer to enet_l3l4_filter_enum
                only one parameter can be selected which is shown as below
      \arg            L3L4_FILTER0: L3/L4 filter 0
      \arg            L3L4_FILTER1: L3/L4 filter 1
      \arg            L3L4_FILTER2: L3/L4 filter 2
      \arg            L3L4_FILTER3: L3/L4 filter 3
    \param[in]  src_port: the source port number of L4 filter
    \param[in]  dst_port: the destinstion port number of L4 filter
    \param[out] none
    \retval     none
*/
void enet_l4_port_num_set(enet_l3l4_filter_enum filter, uint16_t src_port, uint16_t dst_port)
{
    switch(filter) {
    case L3L4_FILTER0:
        ENET_MAC_LAYER4_ADDRESS0 = MAC_LAYER4_ADDRESS_L4DP0(dst_port)|MAC_LAYER4_ADDRESS_L4SP0(src_port);
        break;
    case L3L4_FILTER1:
        ENET_MAC_LAYER4_ADDRESS1 = MAC_LAYER4_ADDRESS_L4DP0(dst_port)|MAC_LAYER4_ADDRESS_L4SP0(src_port);
        break;
    case L3L4_FILTER2:
        ENET_MAC_LAYER4_ADDRESS2 = MAC_LAYER4_ADDRESS_L4DP0(dst_port)|MAC_LAYER4_ADDRESS_L4SP0(src_port);
        break;
    case L3L4_FILTER3:
        ENET_MAC_LAYER4_ADDRESS3 = MAC_LAYER4_ADDRESS_L4DP0(dst_port)|MAC_LAYER4_ADDRESS_L4SP0(src_port);
        break;
    default:
        break;
    }
}

/*!
    \brief     configure L3 filter IPv4 address
    \param[in]  filter: choose the channel number for the packet that is passed by this L3_L4 filter, refer to enet_l3l4_filter_enum
                only one parameter can be selected which is shown as below
      \arg            L3L4_FILTER0: L3/L4 filter 0
      \arg            L3L4_FILTER1: L3/L4 filter 1
      \arg            L3L4_FILTER2: L3/L4 filter 2
      \arg            L3L4_FILTER3: L3/L4 filter 3
    \param[in]  src_ipaddr: the source ipaddr of L3 filter
    \param[in]  dst_ipaddr: the destinstion ipaddr of L3 filter
    \param[out] none
    \retval     none
*/
void enet_l3_ipv4_address_set(enet_l3l4_filter_enum filter, uint8_t src_ipaddr[], uint8_t dst_ipaddr[])
{
    uint32_t src_ip, dst_ip;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(src_ipaddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x008CU), ERR_PARAM_POINTER);
    } else if(NOT_VALID_POINTER(dst_ipaddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x008CU), ERR_PARAM_POINTER);
    } else 
#endif /* FW_DEBUG_ERR_REPORT */
{
    src_ip = ENET_SET_IPV4ADDR(src_ipaddr);
    dst_ip = ENET_SET_IPV4ADDR(dst_ipaddr);
    switch(filter) {
    case L3L4_FILTER0:
        ENET_MAC_LAYER3_ADDR0_REG0 = src_ip;
        ENET_MAC_LAYER3_ADDR1_REG0 = dst_ip;
        break;
    case L3L4_FILTER1:
        ENET_MAC_LAYER3_ADDR0_REG1 = src_ip;
        ENET_MAC_LAYER3_ADDR1_REG1 = dst_ip;
        break;
    case L3L4_FILTER2:
        ENET_MAC_LAYER3_ADDR0_REG2 = src_ip;
        ENET_MAC_LAYER3_ADDR1_REG2 = dst_ip;
        break;
    case L3L4_FILTER3:
        ENET_MAC_LAYER3_ADDR0_REG3 = src_ip;
        ENET_MAC_LAYER3_ADDR1_REG3 = dst_ip;
        break;
    default:
        break;
    }
}
}

/*!
    \brief     configure L3 filter IPv6 address
    \param[in]  filter: choose the channel number for the packet that is passed by this L3_L4 filter, refer to enet_l3l4_filter_enum
                only one parameter can be selected which is shown as below
      \arg            L3L4_FILTER0: L3/L4 filter 0
      \arg            L3L4_FILTER1: L3/L4 filter 1
      \arg            L3L4_FILTER2: L3/L4 filter 2
      \arg            L3L4_FILTER3: L3/L4 filter 3
    \param[in]  ipaddr: the ipv6 addr of L3 filter
    \param[out] none
    \retval     none
*/
void enet_l3_ipv6_address_set(enet_l3l4_filter_enum filter, uint32_t ipaddr[])
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(ipaddr)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x008DU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(filter) {
    case L3L4_FILTER0:
        ENET_MAC_LAYER3_ADDR0_REG0 = ipaddr[0];
        ENET_MAC_LAYER3_ADDR1_REG0 = ipaddr[1];
        ENET_MAC_LAYER3_ADDR2_REG0 = ipaddr[2];
        ENET_MAC_LAYER3_ADDR3_REG0 = ipaddr[3];
        break;
    case L3L4_FILTER1:
        ENET_MAC_LAYER3_ADDR0_REG1 = ipaddr[0];
        ENET_MAC_LAYER3_ADDR1_REG1 = ipaddr[1];
        ENET_MAC_LAYER3_ADDR2_REG1 = ipaddr[2];
        ENET_MAC_LAYER3_ADDR3_REG1 = ipaddr[3];
        break;
    case L3L4_FILTER2:
        ENET_MAC_LAYER3_ADDR0_REG2 = ipaddr[0];
        ENET_MAC_LAYER3_ADDR1_REG2 = ipaddr[1];
        ENET_MAC_LAYER3_ADDR2_REG2 = ipaddr[2];
        ENET_MAC_LAYER3_ADDR3_REG2 = ipaddr[3];
        break;
    case L3L4_FILTER3:
        ENET_MAC_LAYER3_ADDR0_REG3 = ipaddr[0];
        ENET_MAC_LAYER3_ADDR1_REG3 = ipaddr[1];
        ENET_MAC_LAYER3_ADDR2_REG3 = ipaddr[2];
        ENET_MAC_LAYER3_ADDR3_REG3 = ipaddr[3];
        break;
    default:
        break;
    }
}
}

/*!
    \brief    get the bit flag of ENET DMA descriptor
    \param[in]  desc: the descriptor pointer which users want to get flag
    \param[in]  desc_flag: the bit flag of ENET DMA descriptor
                only one parameter can be selected which is shown as below
      \arg        ENET_NORMAL_TDES3_WF_IHE: IP header error
      \arg        ENET_NORMAL_TDES3_WF_DB: deferred
      \arg        ENET_NORMAL_TDES3_WF_UF: underflow error
      \arg        ENET_NORMAL_TDES3_WF_ED: excessive deferral
      \arg        ENET_NORMAL_TDES3_WF_EC: excessive collision
      \arg        ENET_NORMAL_TDES3_WF_LC: late collision
      \arg        ENET_NORMAL_TDES3_WF_NC: no carrier
      \arg        ENET_NORMAL_TDES3_WF_LOC: loss of carrier
      \arg        ENET_NORMAL_TDES3_WF_PCE: IP payload checksum error
      \arg        ENET_NORMAL_TDES3_WF_FF: frame flushed
      \arg        ENET_NORMAL_TDES3_WF_JT: jabber timeout
      \arg        ENET_NORMAL_TDES3_WF_ES: error summary
      \arg        ENET_NORMAL_TDES3_WF_TTSS: transmit timestamp status
      \arg        ENET_NORMAL_TDES3_WF_DE: descriptor error
      \arg        ENET_NORMAL_TDES3_WF_FD: first segment
      \arg        ENET_NORMAL_TDES3_WF_LD: last segment
      \arg        ENET_NORMAL_TDES3_WF_CTXT: context type
      \arg        ENET_NORMAL_TDES3_WF_OWN: own bit
      \arg        ENET_NORMAL_RDES3_WF_ES: error summary
      \arg        ENET_NORMAL_RDES3_WF_DE: dribble bit error
      \arg        ENET_NORMAL_RDES3_WF_RE: receive error
      \arg        ENET_NORMAL_RDES3_WF_OE: overflow error
      \arg        ENET_NORMAL_RDES3_WF_RWT: receive watchdog timeout
      \arg        ENET_NORMAL_RDES3_WF_GP: giant packet
      \arg        ENET_NORMAL_RDES3_WF_CE: CRC error
      \arg        ENET_NORMAL_RDES3_WF_RS0V: receive status RDES0 valid
      \arg        ENET_NORMAL_RDES3_WF_RS1V: receive status RDES1 valid
      \arg        ENET_NORMAL_RDES3_WF_RS2V: receive status RDES2 valid
      \arg        ENET_NORMAL_RDES3_WF_LD: last descriptor
      \arg        ENET_NORMAL_RDES3_WF_FD: first descriptor
      \arg        ENET_NORMAL_RDES3_WF_CTXT: context type
      \arg        ENET_NORMAL_RDES3_WF_OWN: own bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus enet_desc_flag_get(enet_descriptors_struct *desc, uint32_t desc_flag)
{
    FlagStatus enet_flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(desc)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x008EU), ERR_PARAM_POINTER);
    } else if(NOT_ENET_DESC_FLAG_GET(desc_flag)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x008EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if((uint32_t)RESET != (desc->DES3 & desc_flag)) {
        enet_flag = SET;
    } else {
    
    }
}
    return enet_flag;
}

/*!
    \brief    set the bit flag of ENET DMA descriptor
    \param[in]  desc: the descriptor pointer which users want to set flag
    \param[in]  desc_flag: the bit flag of ENET DMA descriptor
                only one parameter can be selected which is shown as below
      \arg        ENET_NORMAL_TDES3_RF_FD: first segment
      \arg        ENET_NORMAL_TDES3_RF_LD: last segment
      \arg        ENET_NORMAL_TDES3_RF_CTXT: context type
      \arg        ENET_NORMAL_TDES3_RF_OWN: own bit
      \arg        ENET_NORMAL_RDES3_RF_OWN: descriptor available
      \arg        ENET_NORMAL_RDES3_RF_IOC: interrupt on completion
      \arg        ENET_NORMAL_RDES3_RF_BUF1V: buffer 1 address valid
      \arg        ENET_NORMAL_RDES3_RF_BUF2V: buffer 2 address valid
    \param[out] none
    \retval     none
*/
void enet_desc_flag_set(enet_descriptors_struct *desc, uint32_t desc_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(desc)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x008FU), ERR_PARAM_POINTER);
    } else if(NOT_ENET_DESC_FLAG_SET(desc_flag)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x008FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    desc->DES3 |= desc_flag;
}
}

/*!
    \brief    clear the bit flag of ENET DMA descriptor
    \param[in]  desc: the descriptor pointer which users want to clear flag
    \param[in]  desc_flag: the bit flag of ENET DMA descriptor
                only one parameter can be selected which is shown as below
      \arg        ENET_NORMAL_TDES3_RF_FD: first segment
      \arg        ENET_NORMAL_TDES3_RF_LD: last segment
      \arg        ENET_NORMAL_TDES3_RF_CTXT: context type
      \arg        ENET_NORMAL_TDES3_RF_OWN: own bit
      \arg        ENET_NORMAL_RDES3_RF_OWN: descriptor available
      \arg        ENET_NORMAL_RDES3_RF_IOC: interrupt on completion
      \arg        ENET_NORMAL_RDES3_RF_BUF1V: buffer 1 address valid
      \arg        ENET_NORMAL_RDES3_RF_BUF2V: buffer 2 address valid
    \param[out] none
    \retval     none
*/
void enet_desc_flag_clear(enet_descriptors_struct *desc, uint32_t desc_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(desc)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0090U), ERR_PARAM_POINTER);
    } else if(NOT_ENET_DESC_FLAG_SET(desc_flag)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0090U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    desc->DES3 &= ~desc_flag;
}
}

/*!
    \brief    drop current receive frame
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[out] none
    \retval     none
*/
void enet_rxframe_drop(enet_dmach_enum dmach)
{

    switch(dmach) {
    /* enable reception, descriptor is owned by DMA */
    case DMACH0:
        dma_current_rxdesc->DES3 = ENET_NORMAL_RDES3_WF_OWN;
        dma_current_rxdesc->DES0 = (uint32_t)dma_current_rxdesc->buffer_address;
        dma_current_rxdesc->DES3 |= ENET_NORMAL_RDES3_RF_BUF1V;
    
        /* If the receive interrupt is enabled, the IOC bit needs to be set */
        if((uint32_t)RESET != (ENET_DMA_CH0_INTERRUPT_ENABLE & ENET_DMA_CH_INTERRUPT_ENABLE_RIE)) {
            dma_current_rxdesc->DES3 |= ENET_NORMAL_RDES3_RF_IOC;
        }
        __DSB();
        __ISB();
        __DMB();

        /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
        /* ring mode */
        if((enet_descriptors_struct *)(uint32_t)&rxdesc_tab[(ENET_RXBUF_NUM - 1U)] == dma_current_rxdesc) {
        /* if is the last descriptor in table, the next descriptor is the table header */
        dma_current_rxdesc = (enet_descriptors_struct *)(ENET_DMA_CH0_RXDESC_ADDRESS);
        } else {
        /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
        dma_current_rxdesc = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_rxdesc + ETH_DMARXDESC_SIZE);
        }
        ENET_DMA_CH0_RXDESC_TAIL_POINTER = (uint32_t)&rxdesc_tab[ENET_RXBUF_NUM];
        break;

    case DMACH1:
        dma_current_rxdesc1->DES3 = ENET_NORMAL_RDES3_WF_OWN;
        dma_current_rxdesc1->DES0 = (uint32_t)dma_current_rxdesc1->buffer_address;
        dma_current_rxdesc1->DES3 |= ENET_NORMAL_RDES3_RF_BUF1V;
    
        /* If the receive interrupt is enabled, the IOC bit needs to be set */
        if((uint32_t)RESET != (ENET_DMA_CH1_INTERRUPT_ENABLE & ENET_DMA_CH_INTERRUPT_ENABLE_RIE)) {
            dma_current_rxdesc1->DES3 |= ENET_NORMAL_RDES3_RF_IOC;
        }
        __DSB();
        __ISB();
        __DMB();

        /* update the current RxDMA descriptor pointer to the next decriptor in RxDMA decriptor table */
        /* ring mode */
        if((enet_descriptors_struct *)(uint32_t)&rxdesc_tab1[(ENET_RXBUF_NUM - 1U)] == dma_current_rxdesc1) {
            /* if is the last descriptor in table, the next descriptor is the table header */
            dma_current_rxdesc1 = (enet_descriptors_struct *)(ENET_DMA_CH1_RXDESC_ADDRESS);
        } else {
                /* the next descriptor is the current address, add the descriptor size, and descriptor skip length */
                dma_current_rxdesc1 = (enet_descriptors_struct *)(uint32_t)((uint32_t)dma_current_rxdesc1 + ETH_DMARXDESC_SIZE);
        }
        ENET_DMA_CH1_RXDESC_TAIL_POINTER = (uint32_t)&rxdesc_tab1[ENET_RXBUF_NUM];
        break;
    default:
        break;
    }
}

/*!
    \brief    enable DMA feature
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  feature: the feature of DMA mode
                one or more parameters can be selected which are shown as below
      \arg        ENET_FLUSH_RXFRAME: RxDMA does flushes frames function
      \arg        ENET_SECONDFRAME_OPT: TxDMA controller operate on second frame function
    \param[out] none
    \retval     none
*/
void enet_dma_feature_enable(enet_dmach_enum dmach, uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_DMA_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0092U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0:
        if(ENET_FLUSH_RXFRAME == feature) {
            ENET_DMA_CH0_RX_CONTROL |= ENET_DMA_CH_RX_CONTROL_RPF;
        } else {
            ENET_DMA_CH0_TX_CONTROL |= ENET_DMA_CH_TX_CONTROL_OSF;
        }
        break;
    case DMACH1:
        if(ENET_FLUSH_RXFRAME == feature) {
            ENET_DMA_CH1_RX_CONTROL |= ENET_DMA_CH_RX_CONTROL_RPF;
        } else {
            ENET_DMA_CH1_TX_CONTROL |= ENET_DMA_CH_TX_CONTROL_OSF;
        }
        break;
    default:
        break;
    }
}
}

/*!
    \brief    disable DMA feature
    \param[in]  dmach: choose the channel of dma process which users want to check, refer to enet_dmach_enum
                only one parameter can be selected which is shown as below
      \arg        DMACH0: dma channel 0
      \arg        DMACH1: dma channel 1
    \param[in]  feature: the feature of DMA mode
                one or more parameters can be selected which are shown as below
      \arg        ENET_FLUSH_RXFRAME: RxDMA does flushes frames function
      \arg        ENET_SECONDFRAME_OPT: TxDMA controller operate on second frame function
    \param[out] none
    \retval     none
*/
void enet_dma_feature_disable(enet_dmach_enum dmach, uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_ENET_DMA_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0093U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(dmach) {
    case DMACH0:
        if(ENET_FLUSH_RXFRAME == feature) {
            ENET_DMA_CH0_RX_CONTROL &= ~ ENET_DMA_CH_RX_CONTROL_RPF;
        } else {
            ENET_DMA_CH0_TX_CONTROL &= ~ ENET_DMA_CH_TX_CONTROL_OSF;
        }
        break;
    case DMACH1:
        if(ENET_FLUSH_RXFRAME == feature) {
            ENET_DMA_CH1_RX_CONTROL &= ~ ENET_DMA_CH_RX_CONTROL_RPF;
        } else {
            ENET_DMA_CH1_TX_CONTROL &= ~ ENET_DMA_CH_TX_CONTROL_OSF;
        }
        break;
    default:
        break;
    }
}
}

/*!
    \brief    wakeup packet filter register pointer reset
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_pmt_filter_register_pointer_reset(void)
{
    ENET_MAC_PMT_CONTROL_STATUS |= ENET_MAC_PMT_CONTROL_STATUS_RWKFILTRST;
}

/*!
    \brief    get the current value of the wakeup Packet Filter register pointer
    \param[in]  none
    \param[out] none
    \retval     wkp_pointer: the register current pointer
*/
uint32_t enet_pmt_filter_register_pointer_get(void)
{
    uint32_t wkp_pointer;

    wkp_pointer = (uint32_t)GET_MAC_PMT_CONTROL_RWKPTR(ENET_MAC_PMT_CONTROL_STATUS);
    return wkp_pointer;
}

/*!
    \brief    set the remote wakeup packet registers
    \param[in]  pdata: pointer to buffer data which is written to remote wakeup packet registers (8 words total)
    \param[out] none
    \retval     none
*/
void enet_pmt_filter_config(uint32_t pdata[])
{
    uint32_t num;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(pdata)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0096U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    enet_pmt_filter_register_pointer_reset();
    /* configure ENET_MAC_RWFF register */
    for(num = 0U; num < ENET_WAKEUP_PACKET_REGISTER_LENGTH; num++) {
        ENET_MAC_RWK_PACKET_FILTER = pdata[num];
    }
}
}

/*!
    \brief    enable wakeup management features
    \param[in]  feature: the wake up type which is selected
                one or more parameters can be selected which are shown as below
      \arg        MAC_PMT_POWER_DOWN: power down mode
      \arg        MAC_PMT_MAGIC_PACKET_FRAME: enable a wakeup event due to magic packet reception
      \arg        MAC_PMT_WAKE_UP_FRAME: enable a wakeup event due to wakeup frame reception
      \arg        MAC_PMT_WAKE_UP_FRAME_FORWARD: enable remote wakeup frame forwarding
      \arg        MAC_PMT_GLOBAL_UNICAST: any received unicast frame passed filter is considered to be a wakeup frame
    \param[out] none
    \retval     none
*/
void enet_pmt_feature_enable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_PMT_ENABLE_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0097U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_PMT_CONTROL_STATUS |= feature;
}
}

/*!
    \brief    disable wakeup management features
    \param[in]  feature: the wake up type which is selected
                one or more parameters can be selected which are shown as below
      \arg        MAC_PMT_MAGIC_PACKET_FRAME: enable a wakeup event due to magic packet reception
      \arg        MAC_PMT_WAKE_UP_FRAME: enable a wakeup event due to wakeup frame reception
      \arg        MAC_PMT_GLOBAL_UNICAST: any received unicast frame passed filter is considered to be a wakeup frame
    \param[out] none
    \retval     none
*/
void enet_pmt_feature_disable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_PMT_DISABLE_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0098U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_PMT_CONTROL_STATUS &= (~feature);
}
}

/*!
    \brief      set this counter so that the number of clock cycles of CSR clock is 1us
    \param[in]  tick: the tick counter value(0 - 0xFFF)
    \param[out] none
    \retval     none
*/
void enet_eee_ustick_set(uint32_t tick)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_US_TICK(tick)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x0099U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_1US_TIC_COUNTER = (uint32_t)(tick & ENET_MAC_1US_TIC_COUNTER_TIC_1US_CNTR);
}
}

/*!
    \brief      set the value of LPI ralated timers
    \param[in]  type: choose the timer type, refer to enet_lpitimer_enum
                only one parameter can be selected which is shown as below
      \arg        LPI_LS_TIMER: lpi ls timer
      \arg        LPI_TW_TIMER: lpi tw timer
      \arg        LPI_ENTRY_TIMER: lpi entry timer
    \param[in]  val: the timer value(in milliseconds)
    \param[out] none
    \retval     none
*/
void enet_eee_lpi_timer_set(enet_lpitimer_enum type, uint32_t val)
{
    uint32_t entry_val;
#ifdef FW_DEBUG_ERR_REPORT
    if((type == LPI_LS_TIMER)&& NOT_ENET_LPI_LS_TIMER_VALUE(val)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x009AU), ERR_PARAM_OUT_OF_RANGE);
    } else if((type == LPI_TW_TIMER)&& NOT_ENET_LPI_TW_TIMER_VALUE(val)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x009AU), ERR_PARAM_OUT_OF_RANGE);
    } else if((type == LPI_ENTRY_TIMER)&& NOT_ENET_LPI_ENTRY_TIMER_VALUE(val)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x009AU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    entry_val = val / 8U;
    switch(type) {
    case(LPI_TW_TIMER):
        ENET_MAC_LPI_TIMERS_CONTROL &= ~ENET_MAC_LPI_TIMERS_CONTROL_TWT;
        ENET_MAC_LPI_TIMERS_CONTROL |= MAC_LPI_TIMERS_CONTROL_TWT(val);
        break;
    case(LPI_LS_TIMER):
        ENET_MAC_LPI_TIMERS_CONTROL &= ~ENET_MAC_LPI_TIMERS_CONTROL_LST;
        ENET_MAC_LPI_TIMERS_CONTROL |= MAC_LPI_TIMERS_CONTROL_LST(val);
        break;
    case(LPI_ENTRY_TIMER):
        ENET_MAC_LPI_ENTRY_TIMER &= ~ENET_MAC_LPI_ENTRY_TIMER_LPIET;
        ENET_MAC_LPI_ENTRY_TIMER |= MAC_LPI_ENTRY_TIMER_LPIET(entry_val);
        break;
    default:
        break;
    }
}
}

/*!
    \brief    enable energy efficient ethernet features
    \param[in]  feature: the wake up type which is selected
                only one parameter can be selected which are shown as below
      \arg        ENET_LPI_TXCLK_STOP: LPI Tx Clock Stop Enable
      \arg        ENET_LPI_TIMER: LPI Timer Enable
      \arg        ENET_LPI_TXAUTOMATE: LPI Tx Automate
      \arg        ENET_LPI_PHYLINK_UP: PHY Link Status Enable
      \arg        ENET_LPI_ENABLE: LPI Enable
      \arg        ENET_LPI_TRANSMIT_AUTO_ENTRY: the MAC enters the LPI mode only after all outstanding packetsand pending packets have been transmitted
      \arg        ENET_LPI_TRANSMIT_AUTO_ENTRY_WITH_TIMER: the MAC transmitter enters LPI state only when the complete MAC TX data path is IDLE for a period indicated by the MAC_LPI_Entry_Timer register
    \param[out] none
    \retval     none
*/
void enet_eee_lpi_feature_enable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_LPI_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x009BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_LPI_CONTROL_STATUS |= feature;
}
}

/*!
    \brief    disable energy efficient ethernet features
    \param[in]  feature: the wake up type which is selected
                only one parameter can be selected which are shown as below
      \arg        ENET_LPI_TXCLK_STOP: LPI Tx clock stop enable
      \arg        ENET_LPI_TIMER: LPI timer enable
      \arg        ENET_LPI_TXAUTOMATE: LPI Tx automate
      \arg        ENET_LPI_PHYLINK_UP: phy link status enable
      \arg        ENET_LPI_ENABLE: LPI enable
      \arg        ENET_LPI_TRANSMIT_AUTO_ENTRY: the MAC enters the LPI mode only after all outstanding packetsand pending packets have been transmitted
      \arg        ENET_LPI_TRANSMIT_AUTO_ENTRY_WITH_TIMER: the MAC transmitter enters LPI state only when the complete MAC TX data path is IDLE for a period indicated by the MAC_LPI_Entry_Timer register
    \param[out] none
    \retval     none
*/
void enet_eee_lpi_feature_disable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_LPI_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x009CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_LPI_CONTROL_STATUS &= (~feature);
}
}

/*!
    \brief      get lpi state
    \param[in]  state: lpi state
      \arg        ENET_LPI_RX_STATE: receive LPI state
      \arg        ENET_LPI_TX_STATE: transmit LPI state
      \arg        ENET_LPI_RX_EXIT: receive LPI exit
      \arg        ENET_LPI_RX_ENTRY: receive LPI entry
      \arg        ENET_LPI_TX_EXIT: transmit LPI exit
      \arg        ENET_LPI_TX_ENTRY: transmit LPI entry
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus enet_lpi_status_get(uint16_t state)
{
    FlagStatus flag;
    flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_LPI_STATUS(state)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x009DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if(0U != (ENET_MAC_LPI_CONTROL_STATUS & state)) {
        flag = SET;
    } else {
        flag = RESET;
    }
}
    return flag;
}

/*!
    \brief    get LPI related counter
    \param[in]  counter: MSC counters which is selected, refer to enet_lpi_counter_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_TX_LPI_USEC_COUNTER_VAL: transmit LPI microseconds counter
      \arg        ENET_TX_LPI_TRAN_COUNTER_VAL: transmit LPI transition counter
      \arg        ENET_RX_LPI_USEC_COUNTER_VAL: receive LPI microseconds counter
      \arg        ENET_RX_LPI_TRAN_COUNTER_VAL: receive LPI transition counter
    \param[out] none
    \retval     the LPI counter value
*/
uint32_t enet_lpi_counters_get(enet_lpi_counter_enum counter)
{
    uint32_t reval;

    reval = REG32((ENET + (uint32_t)counter));

    return reval;
}

/*!
    \brief    reset the MAC statistics counters
    \param[in]  none
    \param[out] none
    \retval     none
*/
void enet_mmc_counters_reset(void)
{
    /* reset all counters */
    ENET_MMC_CONTROL |= ENET_MMC_CONTROL_CNTRST;
}

/*!
    \brief    enable the MAC statistics counter features
    \param[in]  feature: the feature of MAC statistics counter
                one or more parameters can be selected which are shown as below
      \arg        ENET_MMC_DROPPED_BROADCAST_UPDATE: update MMC counters for dropped broadcast packets
      \arg        ENET_MMC_COUNTER_STOP_ROLLOVER: counter stop rollover
      \arg        ENET_MMC_RESET_ON_READ: reset on read
      \arg        ENET_MMC_COUNTERS_FREEZE: MMC counter freeze
    \param[out] none
    \retval     none
*/
void enet_mmc_feature_enable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_MMC_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00A0U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MMC_CONTROL |= feature;
}
}

/*!
    \brief    disable the MAC statistics counter features
    \param[in]  feature: the feature of MAC statistics counter
                one or more parameters can be selected which are shown as below
      \arg        ENET_MMC_DROPPED_BROADCAST_UPDATE: update MMC counters for dropped broadcast packets
      \arg        ENET_MSC_COUNTER_STOP_ROLLOVER: counter stop rollover
      \arg        ENET_MSC_RESET_ON_READ: reset on read
      \arg        ENET_MSC_COUNTERS_FREEZE: MSC counter freeze
    \param[out] none
    \retval     none
*/
void enet_mmc_feature_disable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_MMC_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00A1U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MMC_CONTROL &= (~feature);
}
}

/*!
    \brief    configure MAC statistics counters preset mode
    \param[in]  mode: MMC counters preset mode, refer to enet_mmc_preset_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MMC_PRESET_NONE: do not preset MMC counter
      \arg        ENET_MMC_PRESET_HALF: preset all MMC counters to almost-half(0x7FFF FFF0) value
      \arg        ENET_MMC_PRESET_FULL: preset all MMC counters to almost-full(0xFFFF FFF0) value
    \param[out] none
    \retval     none
*/
void enet_mmc_counters_preset_config(enet_mmc_preset_enum mode)
{
    ENET_MMC_CONTROL &= ENET_MMC_PRESET_MASK;
    ENET_MMC_CONTROL |= (uint32_t)mode;
}

/*!
    \brief    get MAC statistics counter
    \param[in]  counter: MSC counters which is selected, refer to enet_mmc_counter_enum
                only one parameter can be selected which is shown as below
      \arg        ENET_MMC_TX_OCTET_COUNT_GOOD_BAD: ethernet transmit octet count good bad counter
      \arg        ENET_MMC_TX_PACKET_COUNT_GOOD_BAD:  ethernet transmit packet count good bad counter
      \arg        ENET_MMC_TX_BROADCAST_PACKETS_GOOD: ethernet transmit broadcast packets good counter
      \arg        ENET_MMC_TX_MULTICAST_PACKETS_GOOD: ethernet transmit multicast packets good counter
      \arg        ENET_MMC_TX_64OCTETS_PACKETS_GOOD_BAD: ethernet transmit 64 octet packets good bad counter
      \arg        ENET_MMC_TX_65TO127OCTETS_PACKETS_GOOD_BAD: ethernet transmit 65 to 127 octet packets good bad counter
      \arg        ENET_MMC_TX_128TO255OCTETS_PACKETS_GOOD_BAD: ethernet transmit 128 to 255 octet packets good bad counter
      \arg        ENET_MMC_TX_256TO511OCTETS_PACKETS_GOOD_BAD: ethernet transmit 256 to 511 octet packets good bad counter
      \arg        ENET_MMC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD: ethernet transmit 512 to 1023 octet packets good bad counter
      \arg        ENET_MMC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD: ethernet transmit 1024 to max octet packets good bad counter
      \arg        ENET_MMC_TX_UNICAST_PACKETS_GOOD_BAD: ethernet transmit unicast packets good bad counter
      \arg        ENET_MMC_TX_MULTICAST_PACKETS_GOOD_BAD: ethernet transmit multicast packets good bad counter
      \arg        ENET_MMC_TX_BROADCAST_PACKETS_GOOD_BAD: ethernet transmit broadcast packets good bad counter
      \arg        ENET_MMC_TX_UNDERFLOW_ERROR_PACKETS: ethernet transmit underflow error packets counter
      \arg        ENET_MMC_TX_SINGLE_COLLISION_GOOD_PACKETS: ethernet transmit single collision good packets counter
      \arg        ENET_MMC_TX_MULTIPLE_COLLISION_GOOD_PACKETS: ethernet transmit multiple collision good packets counter
      \arg        ENET_MMC_TX_DEFERRED_PACKETS: ethernet transmit deferred packets counter
      \arg        ENET_MMC_TX_LATE_COLLISION_PACKETS: ethernet transmit late collision packets counter
      \arg        ENET_MMC_TX_EXCESSIVE_COLLISION_PACKETS: ethernet transmit excessive collision packets counter
      \arg        ENET_MMC_TX_CARRIER_ERROR_PACKETS: ethernet transmit carrier error packets counter
      \arg        ENET_MMC_TX_OCTET_COUNT_GOOD: ethernet transmit octet count good counter
      \arg        ENET_MMC_TX_PACKET_COUNT_GOOD: ethernet transmit packet count good counter
      \arg        ENET_MMC_TX_EXCESSIVE_DEFERRAL_ERROR: ethernet transmit excessive deferral error counter
      \arg        ENET_MMC_TX_PAUSE_PACKETS: ethernet transmit pause packets counter
      \arg        ENET_MMC_TX_VLAN_PACKETS_GOOD: ethernet transmit vlan packets good counter
      \arg        ENET_MMC_TX_OSIZE_PACKETS_GOOD: ethernet transmit oversize packets good counter
      \arg        ENET_MMC_RX_PACKETS_COUNT_GOOD_BAD: ethernet receive packet count good bad counter
      \arg        ENET_MMC_RX_OCTET_COUNT_GOOD_BAD: ethernet receive octet count good bad counter
      \arg        ENET_MMC_RX_OCTET_COUNT_GOOD: ethernet receive octet count good counter
      \arg        ENET_MMC_RX_BROADCAST_PACKETS_GOOD: ethernet receive broadcast packets good counter
      \arg        ENET_MMC_RX_MULTICAST_PACKETS_GOOD: ethernet receive multicast packets good counter
      \arg        ENET_MMC_RX_CRC_ERROR_PACKETS: ethernet receive crc error packets counter
      \arg        ENET_MMC_RX_ALIGNMENT_ERROR_PACKETS: ethernet receive alignment error packets counter
      \arg        ENET_MMC_RX_RUNT_ERROR_PACKETS: ethernet receive runt error packets counter
      \arg        ENET_MMC_RX_JABBER_ERROR_PACKETS: ethernet receive jabber error packets counter
      \arg        ENET_MMC_RX_UNDERSIZE_PACKETS_GOOD: ethernet receive undersize packets good counter
      \arg        ENET_MMC_RX_OVERSIZE_PACKETS_GOOD: ethernet receive oversize packets good counter
      \arg        ENET_MMC_RX_64OCTETS_PACKETS_GOOD_BAD: ethernet receive 64 octet packets good bad counter
      \arg        ENET_MMC_RX_65TO127OCTETS_PACKETS_GOOD_BAD: ethernet receive 65 to 127 octet packets good bad counter
      \arg        ENET_MMC_RX_128TO255OCTETS_PACKETS_GOOD_BAD: ethernet receive 128 to 255 octet packets good bad counter
      \arg        ENET_MMC_RX_256TO511OCTETS_PACKETS_GOOD_BAD: ethernet receive 256 to 511 octet packets good bad counter
      \arg        ENET_MMC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD: ethernet receive 512 to 1023 octet packets good bad counter
      \arg        ENET_MMC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD: ethernet receive 1024 to max octet packets good bad counter
      \arg        ENET_MMC_RX_UNICAST_PACKETS_GOOD: ethernet receive unicast packets good counter
      \arg        ENET_MMC_RX_LENGTH_ERROR_PACKETS: ethernet receive length error packets counter
      \arg        ENET_MMC_RX_OUT_OF_RANGE_TYPE_PACKETS: ethernet receive out of range type packets counter
      \arg        ENET_MMC_RX_PAUSE_PACKETS: ethernet receive pause packets counter
      \arg        ENET_MMC_RX_FIFO_OVERFLOW_PACKETS: ethernet receive fifo overflow packets counter
      \arg        ENET_MMC_RX_VLAN_PACKETS_GOOD_BAD: ethernet receive vlan packets good bad counter
      \arg        ENET_MMC_RX_WATCHDOG_ERROR_PACKETS: ethernet receive watchdog error packets counter
      \arg        ENET_MMC_RX_RECEIVE_ERROR_PACKETS: ethernet receive error packets counter
      \arg        ENET_MMC_RX_CONTROL_PACKETS_GOOD: ethernet receive control packets good counter
      \arg        ENET_MMC_TX_LPI_USEC_CNTR: ethernet transmit LPI microseconds counter
      \arg        ENET_MMC_TX_LPI_TRAN_CNTR: ethernet transmit LPI transition counter
      \arg        ENET_MMC_RX_LPI_USEC_CNTR: ethernet receive LPI microseconds counter
      \arg        ENET_MMC_RX_LPI_TRAN_CNTR: ethernet receive LPI transition counter
      \arg        ENET_MMC_RXIPV4_GOOD_PACKETS: ethernet receive ipv4 good packets counter
      \arg        ENET_MMC_RXIPV4_HEADER_ERROR_PACKETS: ethernet receive ipv4 header error packets counter
      \arg        ENET_MMC_RXIPV4_NO_PAYLOAD_PACKETS: ethernet receive ipv4 no payload packets counter
      \arg        ENET_MMC_RXIPV4_FRAGMENTED_PACKETS: ethernet receive ipv4 fragmented packets counter
      \arg        ENET_MMC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS: ethernet receive ipv4 udp checksum disabled packets counter
      \arg        ENET_MMC_RXIPV6_GOOD_PACKETS: ethernet receive ipv6 good packets counter
      \arg        ENET_MMC_RXIPV6_HEADER_ERROR_PACKETS: ethernet receive ipv6 header error packets counter
      \arg        ENET_MMC_RXIPV6_NO_PAYLOAD_PACKETS: ethernet receive ipv6 no payload packets counter
      \arg        ENET_MMC_RXUDP_GOOD_PACKETS: ethernet receive udp good packets counter
      \arg        ENET_MMC_RXUDP_ERROR_PACKETS: ethernet receive udp error packets counter
      \arg        ENET_MMC_RXTCP_GOOD_PACKETS: ethernet receive tcp good packets counter
      \arg        ENET_MMC_RXTCP_ERROR_PACKETS: ethernet receive tcp error packets counter
      \arg        ENET_MMC_RXICMP_GOOD_PACKETS: ethernet receive icmp good packets counter
      \arg        ENET_MMC_RXICMP_ERROR_PACKETS: ethernet receive icmp error packets counter
      \arg        ENET_MMC_RXIPV4_GOOD_OCTETS: ethernet receive ipv4 good octets counter
      \arg        ENET_MMC_RXIPV4_HEADER_ERROR_OCTETS: ethernet receive ipv4 header error octets counter
      \arg        ENET_MMC_RXIPV4_NO_PAYLOAD_OCTETS: ethernet receive ipv4 no payload octets counter
      \arg        ENET_MMC_RXIPV4_FRAGMENTED_OCTETS: ethernet receive ipv4 fragmented octets counter
      \arg        ENET_MMC_RXIPV4_UDP_CHECKSUM_DISABLED_OCTETS: ethernet receive ipv4 udp checksum disabled octets counter
      \arg        ENET_MMC_RXIPV6_GOOD_OCTETS: ethernet receive ipv6 good octets counter
      \arg        ENET_MMC_RXIPV6_HEADER_ERROR_OCTETS: ethernet receive ipv6 header error octets counter
      \arg        ENET_MMC_RXIPV6_NO_PAYLOAD_OCTETS: ethernet receive ipv6 no payload octets counter
      \arg        ENET_MMC_RXUDP_GOOD_OCTETS: ethernet receive udp good octets counter
      \arg        ENET_MMC_RXUDP_ERROR_OCTETS: ethernet receive udp error octets counter
      \arg        ENET_MMC_RXTCP_GOOD_OCTETS: ethernet receive tcp good octets counter
      \arg        ENET_MMC_RXTCP_ERROR_OCTETS: ethernet receive tcp error octets counter
      \arg        ENET_MMC_RXICMP_GOOD_OCTETS: ethernet receive icmp good octets counter
      \arg        ENET_MMC_RXICMP_ERROR_OCTETS: ethernet receive icmp error octets counter
      \arg        ENET_MMC_MMC_FPE_TX_FRAGMENT: ethernet MMC FPE transmit fragment counter
      \arg        ENET_MMC_MMC_TX_HOLD_REQ: ethernet MMC FPE hold request counter
      \arg        ENET_MMC_RX_PACKETS_ASSEMBLY_ERR: ethernet MMC receive packets assembly error counter
      \arg        ENET_MMC_RX_PACKETS_SMD_ERR: ethernet MMC receive packets SMD error counter
      \arg        ENET_MMC_RX_PACKETS_ASSEMBLY_OK: ethernet MMC receive packets assembly ok counter
      \arg        ENET_MMC_RX_FPE_FRAGMENT: ethernet MMC receive FPE fragment counter
    \param[out] none
    \retval     the MMC counter value
*/
uint32_t enet_mmc_counters_get(enet_mmc_counter_enum counter)
{
    uint32_t reval;
    reval = REG32((ENET + (uint32_t)counter));
    return reval;
}

/*!
    \brief      enable the PTP features
    \param[in]  feature: the feature of ENET PTP mode
                one or more parameters can be selected which are shown as below
      \arg        ENET_RXTX_TIMESTAMP: timestamp function for transmit and receive frames
      \arg        ENET_PRESENTATION_TIMESTAMP: presentation time generation function
      \arg        ENET_ALL_RX_TIMESTAMP: all received frames are taken snapshot
      \arg        ENET_NONTYPE_FRAME_SNAPSHOT: take snapshot when received non type frame
      \arg        ENET_IPV6_FRAME_SNAPSHOT: take snapshot for IPv6 frame
      \arg        ENET_IPV4_FRAME_SNAPSHOT: take snapshot for IPv4 frame
      \arg        ENET_PTP_FRAME_USE_MACADDRESS_FILTER: use MAC address to filter the PTP frame
      \arg        ENET_TX_TIMESTAMP_OVERWRITE:  transmit timestamp status mode
      \arg        ENET_AV8021_AS_MODE: AV 802.1AS mode-  the MAC processes only untagged PTP over Ethernet packets
    \param[out] none
    \retval     none
*/
void enet_ptp_feature_enable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_PTP_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00A4U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_TIMESTAMP_CONTROL |= feature;
}
}

/*!
    \brief      disable the PTP features
    \param[in]  feature: the feature of ENET PTP mode
                one or more parameters can be selected which are shown as below
      \arg        ENET_RXTX_TIMESTAMP: timestamp function for transmit and receive frames
      \arg        ENET_PRESENTATION_TIMESTAMP: presentation time generation function
      \arg        ENET_ALL_RX_TIMESTAMP: all received frames are taken snapshot
      \arg        ENET_NONTYPE_FRAME_SNAPSHOT: take snapshot when received non type frame
      \arg        ENET_IPV6_FRAME_SNAPSHOT: take snapshot for IPv6 frame
      \arg        ENET_IPV4_FRAME_SNAPSHOT: take snapshot for IPv4 frame
      \arg        ENET_PTP_FRAME_USE_MACADDRESS_FILTER: use MAC address to filter the PTP frame
      \arg        ENET_TX_TIMESTAMP_OVERWRITE:  transmit timestamp status mode
      \arg        ENET_AV8021_AS_MODE: AV 802.1AS mode-  the MAC processes only untagged PTP over Ethernet packets
    \param[out] none
    \retval     none
*/
void enet_ptp_feature_disable(uint32_t feature)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_PTP_FEATURE(feature)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00A5U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_TIMESTAMP_CONTROL &= ~feature;
}
}

/*!
    \brief    configure the PTP timestamp function
    \param[in]  func: the function of PTP timestamp
                only one parameter can be selected which is shown as below
      \arg        ENET_CKNT_END_TO_END_0: type of end-to-end transparent clock node type for timestamp
      \arg        ENET_CKNT_ORDINARY_BOUNDARY_SLAVE: type of ordinary or boundary slave clock node type for timestamp
      \arg        ENET_CKNT_ORDINARY_BOUNDARY_MASTER: type of ordinary or boundary master clock node type for timestamp
      \arg        ENET_CKNT_END_TO_END_PEER_DELAY: type of End-to-End Transparent with support for peer delay clock node type for timestamp
      \arg        ENET_CKNT_ORDINARY_BOUNDARY_SLAVE_PEER_TO_PEER: type of Ordinary or Boundary Slave with support for peer delay mechanism or Peer to Peer Transpare clock node type for timestamp
      \arg        ENET_CKNT_ORDINARY_BOUNDARY_MASTER_PEER_DELAY: type of Ordinary or BoundaryMaster with support for peer delay clock node type for timestamp
      \arg        ENET_CKNT_END_TO_END: type of end-to-end transparent clock node type for timestamp
      \arg        ENET_CKNT_PEER_TO_PEER: type of peer-to-peer transparent clock node type for timestamp
      \arg        ENET_PTP_ADDEND_UPDATE: addend register update
      \arg        ENET_PTP_SYSTIME_UPDATE: timestamp update
      \arg        ENET_PTP_SYSTIME_INIT: timestamp initialize
      \arg        ENET_PTP_FINEMODE: the system timestamp uses the fine method for updating
      \arg        ENET_PTP_COARSEMODE: the system timestamp uses the coarse method for updating
      \arg        ENET_SUBSECOND_DIGITAL_ROLLOVER: digital rollover mode
      \arg        ENET_SUBSECOND_BINARY_ROLLOVER: binary rollover mode
      \arg        ENET_SNOOPING_PTP_VERSION_2: version 2
      \arg        ENET_SNOOPING_PTP_VERSION_1: version 1
      \arg        ENET_EVENT_TYPE_MESSAGES_SNAPSHOT: only event type messages are taken snapshot
      \arg        ENET_ALL_TYPE_MESSAGES_SNAPSHOT: all type messages are taken snapshot except announce,
                                                   management and signaling message
      \arg        ENET_MASTER_NODE_MESSAGE_SNAPSHOT: snapshot is only take for master node message
      \arg        ENET_SLAVE_NODE_MESSAGE_SNAPSHOT: snapshot is only taken for slave node message
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus enet_ptp_timestamp_function_config(enet_ptp_function_enum func)
{
    uint32_t temp_config, temp_state, timeout;
    ErrStatus enet_state;
    timeout = 0U;

    enet_state = SUCCESS;
    switch(func) {
    case ENET_CKNT_END_TO_END_0:
    case ENET_CKNT_END_TO_END_PEER_DELAY:
        ENET_MAC_TIMESTAMP_CONTROL &= ~(ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL | ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA);
        ENET_MAC_TIMESTAMP_CONTROL |= (uint32_t)func;
        break;
    case ENET_CKNT_ORDINARY_BOUNDARY_SLAVE:
    case ENET_CKNT_ORDINARY_BOUNDARY_MASTER:
    case ENET_CKNT_ORDINARY_BOUNDARY_SLAVE_PEER_TO_PEER:
    case ENET_CKNT_ORDINARY_BOUNDARY_MASTER_PEER_DELAY:
        ENET_MAC_TIMESTAMP_CONTROL &= ~(ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL | ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA | ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA);
        ENET_MAC_TIMESTAMP_CONTROL |= (uint32_t)func;
        break;
    case ENET_CKNT_END_TO_END:
    case ENET_CKNT_PEER_TO_PEER:
        ENET_MAC_TIMESTAMP_CONTROL &= ~ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL;
        ENET_MAC_TIMESTAMP_CONTROL |= (uint32_t)func;
        break;
    case ENET_ALL_TYPE_MESSAGES_SNAPSHOT:
        ENET_MAC_TIMESTAMP_CONTROL &= ~ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA;
        break;
    case ENET_PTP_ADDEND_UPDATE:
        /* this bit must be read as zero before application set it */
        do {
            temp_state = ENET_MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSADDREG;
            timeout++;
        } while(((uint32_t)RESET != temp_state) && (timeout < ENET_DELAY_TO));
        /* return ERROR due to timeout */
        if(ENET_DELAY_TO == timeout) {
            enet_state = ERROR;
        } else {
            ENET_MAC_TIMESTAMP_CONTROL |= ENET_MAC_TIMESTAMP_CONTROL_TSADDREG;
        }
        break;
    case ENET_PTP_SYSTIME_UPDATE:
        /* both the TSUPDT and TSINIT bits must be read as zero before application set this bit */
        do {
            temp_state = ENET_MAC_TIMESTAMP_CONTROL & (ENET_MAC_TIMESTAMP_CONTROL_TSUPDT | ENET_MAC_TIMESTAMP_CONTROL_TSINIT);
            timeout++;
        } while(((uint32_t)RESET != temp_state) && (timeout < ENET_DELAY_TO));
        /* return ERROR due to timeout */
        if(ENET_DELAY_TO == timeout) {
            enet_state = ERROR;
        } else {
            ENET_MAC_TIMESTAMP_CONTROL |= ENET_MAC_TIMESTAMP_CONTROL_TSUPDT;
        }
        break;
    case ENET_PTP_SYSTIME_INIT:
        /* this bit must be read as zero before application set it */
        do {
            temp_state = ENET_MAC_TIMESTAMP_CONTROL & ENET_MAC_TIMESTAMP_CONTROL_TSINIT;
            timeout++;
        } while(((uint32_t)RESET != temp_state) && (timeout < ENET_DELAY_TO));
        /* return ERROR due to timeout */
        if(ENET_DELAY_TO == timeout) {
            enet_state = ERROR;
        } else {
            ENET_MAC_TIMESTAMP_CONTROL |= ENET_MAC_TIMESTAMP_CONTROL_TSINIT;
        }
        break;
    default:
        temp_config = (uint32_t)func & (~BIT(31));
        if((uint32_t)RESET != ((uint32_t)func & BIT(31))) {
            ENET_MAC_TIMESTAMP_CONTROL |= temp_config;
        } else {
            ENET_MAC_TIMESTAMP_CONTROL &= ~temp_config;
        }
        break;
    }
    return enet_state;
}

/*!
    \brief    configure system time subsecond increment value
    \param[in]  subsecond: the value will be added to the subsecond value of system time(0x0 - 0xFF)
    \param[in]  nanosubsecond: the value will be added to the nanosubsecond value of system time(0x0 - 0xFF)
    \param[out] none
    \retval     none
*/
void enet_ptp_subsecond_increment_config(uint8_t subsecond, uint8_t nanosubsecond)
{
    ENET_MAC_SUB_SECOND_INCREMENT = PTP_SUB_SECOND_INCREMENT_SSINC(subsecond) | PTP_SUB_SECOND_INCREMENT_SNSINC(nanosubsecond);
}

/*!
    \brief    adjusting the clock frequency only in fine update mode
    \param[in]  add: the value will be added to the accumulator register to achieve time synchronization
    \param[out] none
    \retval     none
*/
void enet_ptp_timestamp_addend_config(uint32_t add)
{
    ENET_MAC_TIMESTAMP_ADDEND = add;
}

/*!
    \brief    initialize or add/subtract to second of the system time
    \param[in]  sign: timestamp update positive or negative sign
                only one parameter can be selected which is shown as below
      \arg        ENET_PTP_ADD_TO_TIME: timestamp update value is added to system time
      \arg        ENET_PTP_SUBSTRACT_FROM_TIME: timestamp update value is subtracted from system time
    \param[in]  secondHi: initializing or adding/subtracting to second of the system time
    \param[in]  second: initializing or adding/subtracting to second of the system time
    \param[in]  subsecond: the current subsecond of the system time
                with 0.46 ns accuracy if required accuracy is 20 ns
    \param[out] none
    \retval     none
*/
void enet_ptp_timestamp_update_config(uint32_t sign, uint16_t secondHi, uint32_t second, uint32_t subsecond)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_PTP_SIGN(sign)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00A9U), ERR_PARAM_INVALID);
    } else if(NOT_ENET_NANOSECOND_VALUE(subsecond)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00A9U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS = secondHi;
    ENET_MAC_SYSTEM_TIME_SECONDS_UPDATE = second;
    ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE = sign | MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(subsecond);
}
}

/*!
    \brief    get the current system time
    \param[in]  none
    \param[out] systime_struct: pointer to a enet_ptp_systime_struct structure which contains
                parameters of PTP system time
                members of the structure and the member values are shown as below:
                  Hisecond: 0x0 - 0xFFFF
                  second: 0x0 - 0xFFFF FFFF
                  subsecond: 0x0 - 0x7FFF FFFF
    \retval     none
*/
void enet_ptp_system_time_get(enet_ptp_systime_struct *systime_struct)
{
    uint32_t temp_hisec, temp_sec, temp_subs;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(systime_struct)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00AAU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    /* get the value of sysytem time registers */
    temp_hisec = (uint32_t)ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS;
    temp_sec = (uint32_t)ENET_MAC_SYSTEM_TIME_SECONDS;
    temp_subs = (uint32_t)ENET_MAC_SYSTEM_TIME_NANOSECONDS;

    /* get sysytem time and construct the enet_ptp_systime_struct structure */
    systime_struct->secondHi = temp_hisec;
    systime_struct->second = temp_sec;
    systime_struct->subsecond = GET_PTP_SYSTIME_TSSSS(temp_subs);
}
}

/*!
    \brief      configure the PPS output frequency
    \param[in]  freq: PPS output frequency,
                only one parameter can be selected which is shown as below
      \arg        ENET_PPSOFC_1HZ: PPS output 1Hz frequency
      \arg        ENET_PPSOFC_2HZ: PPS output 2Hz frequency
      \arg        ENET_PPSOFC_4HZ: PPS output 4Hz frequency
      \arg        ENET_PPSOFC_8HZ: PPS output 8Hz frequency
      \arg        ENET_PPSOFC_16HZ: PPS output 16Hz frequency
      \arg        ENET_PPSOFC_32HZ: PPS output 32Hz frequency
      \arg        ENET_PPSOFC_64HZ: PPS output 64Hz frequency
      \arg        ENET_PPSOFC_128HZ: PPS output 128Hz frequency
      \arg        ENET_PPSOFC_256HZ: PPS output 256Hz frequency
      \arg        ENET_PPSOFC_512HZ: PPS output 512Hz frequency
      \arg        ENET_PPSOFC_1024HZ: PPS output 1024Hz frequency
      \arg        ENET_PPSOFC_2048HZ: PPS output 2048Hz frequency
      \arg        ENET_PPSOFC_4096HZ: PPS output 4096Hz frequency
      \arg        ENET_PPSOFC_8192HZ: PPS output 8192Hz frequency
      \arg        ENET_PPSOFC_16384HZ: PPS output 16384Hz frequency
      \arg        ENET_PPSOFC_32768HZ: PPS output 32768Hz frequency
    \param[out] none
    \retval     none
*/
void enet_ptp_pps_output_frequency_config(uint32_t freq)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_PPS_FREQ(freq)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00ABU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD;
    ENET_MAC_PPS_CONTROL |= freq;
}
}

/*!
    \brief      configure the PPS single pulse output
    \param[in]  pps: choose the channel of pps out which users want to check, refer to enet_pps_enum
                only one parameter can be selected which is shown as below
      \arg        PPS0: PPS 0
      \arg        PPS1: PPS 1
      \arg        PPS2: PPS 2
      \arg        PPS3: PPS 3
    \param[in]  second: the second of start time
    \param[in]  nanosubsecond: the nanosecond of start time
    \param[in]  width: the width of pluse
    \param[in]  interrupt: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void enet_flexible_pps_singlepulse_output(enet_pps_enum pps, uint32_t second, uint32_t nanosubsecond, uint32_t width, ControlStatus interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_NANOSECOND_VALUE(nanosubsecond)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00ACU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS_OUTPUT_MODE;
    switch(pps) {
    case PPS0:

        ENET_MAC_PPS_CONTROL &= ~(ENET_MAC_PPS_CONTROL_TRGTMODSEL0 | ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD);
        if(ENABLE == interrupt) {
            ENET_MAC_PPS_CONTROL |= ENET_PPS0_GENERATE_INT_AND_OUTPUT;
        } else {
            ENET_MAC_PPS_CONTROL |= ENET_PPS0_GENERATE_OUTPUT_ONLY;
        }
        ENET_MAC_PPS0_TARGET_TIME_SECONDS = second;
        ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS = nanosubsecond;
        ENET_MAC_PPS0_WIDTH = width;
        ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS0_START_SINGLE_PULSE;
        break;
    case PPS1:

        ENET_MAC_PPS_CONTROL &= ~(ENET_MAC_PPS_CONTROL_TRGTMODSEL1 | ENET_MAC_PPS_CONTROL_PPSCMD1);
        if(ENABLE == interrupt) {
            ENET_MAC_PPS_CONTROL |= ENET_PPS1_GENERATE_INT_AND_OUTPUT;
        } else {
            ENET_MAC_PPS_CONTROL |= ENET_PPS1_GENERATE_OUTPUT_ONLY;
        }
        ENET_MAC_PPS1_TARGET_TIME_SECONDS = second;
        ENET_MAC_PPS1_TARGET_TIME_NANOSECONDS = nanosubsecond;
        ENET_MAC_PPS1_WIDTH = width;
        ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS1_START_SINGLE_PULSE;
        break;
    case PPS2:

        ENET_MAC_PPS_CONTROL &= ~(ENET_MAC_PPS_CONTROL_TRGTMODSEL2 | ENET_MAC_PPS_CONTROL_PPSCMD2);
        if(ENABLE == interrupt) {
            ENET_MAC_PPS_CONTROL |= ENET_PPS2_GENERATE_INT_AND_OUTPUT;
        } else {
            ENET_MAC_PPS_CONTROL |= ENET_PPS2_GENERATE_OUTPUT_ONLY;
        }
        ENET_MAC_PPS2_TARGET_TIME_SECONDS = second;
        ENET_MAC_PPS2_TARGET_TIME_NANOSECONDS = nanosubsecond;
        ENET_MAC_PPS2_WIDTH = width;
        ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS2_START_SINGLE_PULSE;
        break;
    case PPS3:

        ENET_MAC_PPS_CONTROL &= ~(ENET_MAC_PPS_CONTROL_TRGTMODSEL3 | ENET_MAC_PPS_CONTROL_PPSCMD3);
        if(ENABLE == interrupt) {
            ENET_MAC_PPS_CONTROL |= ENET_PPS3_GENERATE_INT_AND_OUTPUT;
        } else {
            ENET_MAC_PPS_CONTROL |= ENET_PPS3_GENERATE_OUTPUT_ONLY;
        }
        ENET_MAC_PPS3_TARGET_TIME_SECONDS = second;
        ENET_MAC_PPS3_TARGET_TIME_NANOSECONDS = nanosubsecond;
        ENET_MAC_PPS3_WIDTH = width;
        ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS3_START_SINGLE_PULSE;
        break;
    default:
        break;
    }
    
}
}

/*!
    \brief      configure the PPS train pulse output
    \param[in]  pps: choose the channel of pps out which users want to check, refer to enet_pps_enum
                only one parameter can be selected which is shown as below
      \arg        PPS0: PPS 0
      \arg        PPS1: PPS 1
      \arg        PPS0: PPS 2
      \arg        PPS1: PPS 3
    \param[in]  second: the second of start time
    \param[in]  nanosubsecond: the nanosecond of start time
    \param[in]  width: the width of pluse
    \param[in]  interval: the interval of pluse
    \param[in]  interrupt: ENABLE or DISABLE
    \param[out] none
    \retval     none
*/
void enet_flexible_pps_trainpulse_output(enet_pps_enum pps, uint32_t second, uint32_t nanosubsecond, uint32_t width, uint32_t interval,
        ControlStatus interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_NANOSECOND_VALUE(nanosubsecond)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00ADU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS_OUTPUT_MODE;
    switch(pps) {
    case PPS0:
        ENET_MAC_PPS_CONTROL &= ~(ENET_MAC_PPS_CONTROL_TRGTMODSEL0 | ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD);
        if(ENABLE == interrupt) {
            ENET_MAC_PPS_CONTROL |= ENET_PPS0_GENERATE_INT_AND_OUTPUT;
        } else {
            ENET_MAC_PPS_CONTROL |= ENET_PPS0_GENERATE_OUTPUT_ONLY;
        }
        ENET_MAC_PPS0_TARGET_TIME_SECONDS = second;
        ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS = nanosubsecond;
        ENET_MAC_PPS0_INTERVAL = interval;
        ENET_MAC_PPS0_WIDTH = width;
        ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS0_START_PULSE_TRAIN;
        break;

    case PPS1:
        ENET_MAC_PPS_CONTROL &= ~(ENET_MAC_PPS_CONTROL_TRGTMODSEL1 | ENET_MAC_PPS_CONTROL_PPSCMD1);
        if(ENABLE == interrupt) {
            ENET_MAC_PPS_CONTROL |= ENET_PPS1_GENERATE_INT_AND_OUTPUT;
        } else {
            ENET_MAC_PPS_CONTROL |= ENET_PPS1_GENERATE_OUTPUT_ONLY;
        }
        ENET_MAC_PPS1_TARGET_TIME_SECONDS = second;
        ENET_MAC_PPS1_TARGET_TIME_NANOSECONDS = nanosubsecond;
        ENET_MAC_PPS1_WIDTH = width;
        ENET_MAC_PPS1_INTERVAL = interval;
        ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS1_START_PULSE_TRAIN;
        break;

    case PPS2:
        ENET_MAC_PPS_CONTROL &= ~(ENET_MAC_PPS_CONTROL_TRGTMODSEL2 | ENET_MAC_PPS_CONTROL_PPSCMD2);
        if(ENABLE == interrupt) {
            ENET_MAC_PPS_CONTROL |= ENET_PPS2_GENERATE_INT_AND_OUTPUT;
        } else {
            ENET_MAC_PPS_CONTROL |= ENET_PPS2_GENERATE_OUTPUT_ONLY;
        }
        ENET_MAC_PPS2_TARGET_TIME_SECONDS = second;
        ENET_MAC_PPS2_TARGET_TIME_NANOSECONDS = nanosubsecond;
        ENET_MAC_PPS2_WIDTH = width;
        ENET_MAC_PPS2_INTERVAL = interval;
        ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS2_START_PULSE_TRAIN;
        break;

    case PPS3:
        ENET_MAC_PPS_CONTROL &= ~(ENET_MAC_PPS_CONTROL_TRGTMODSEL3 | ENET_MAC_PPS_CONTROL_PPSCMD3);
        if(ENABLE == interrupt) {
            ENET_MAC_PPS_CONTROL |= ENET_PPS3_GENERATE_INT_AND_OUTPUT;
        } else {
            ENET_MAC_PPS_CONTROL |= ENET_PPS3_GENERATE_OUTPUT_ONLY;
        }
        ENET_MAC_PPS3_TARGET_TIME_SECONDS = second;
        ENET_MAC_PPS3_TARGET_TIME_NANOSECONDS = nanosubsecond;
        ENET_MAC_PPS3_WIDTH = width;
        ENET_MAC_PPS3_INTERVAL = interval;
        ENET_MAC_PPS_CONTROL |= ENET_FLEXIBLE_PPS3_START_PULSE_TRAIN;
        break;
    default:
        break;
    }
}
}

/*!
    \brief      configure the PPS output related command
    \param[in]  pps: choose the channel of pps out which users want to check, refer to enet_pps_enum
                only one parameter can be selected which is shown as below
      \arg        PPS0: PPS 0
      \arg        PPS1: PPS 1
      \arg        PPS0: PPS 2
      \arg        PPS1: PPS 3
    \param[in]  stopsecond: the second of stop time, only be useful when the command is configured as ENET_FLEXIBLE_PPSx_STOP_PULSE_TRAIN_AT_TIME(x = 0, 1, 2, 3)
    \param[in]  stopnanosubsecond: the nanosecond of stop time, only be useful when the command is configured as ENET_FLEXIBLE_PPSx_STOP_PULSE_TRAIN_AT_TIME(x = 0, 1, 2, 3)
    \param[in]  command: PPS output command,
                only one parameter can be selected which is shown as below
      \arg        ENET_FLEXIBLE_PPS0_START_SINGLE_PULSE: generates single pulse rising at the start point
      \arg        ENET_FLEXIBLE_PPS0_START_PULSE_TRAIN: generates the train of pulses rising at the start point
      \arg        ENET_FLEXIBLE_PPS0_CANCEL_START: cancels the start single pulse and start pulse train commands
      \arg        ENET_FLEXIBLE_PPS0_STOP_PULSE_TRAIN_AT_TIME: stops the train of pulses after the time programmed in the Target Time registers elapses
      \arg        ENET_FLEXIBLE_PPS0_STOP_PULSE_TRAIN_NOW: immediately stops the train of pulses
      \arg        ENET_FLEXIBLE_PPS0_CANCEL_STOP_PULSE_TRAIN: cancels the stop pulse train at time command if the programmed stop time has not elapsed

      \arg        ENET_FLEXIBLE_PPS1_START_SINGLE_PULSE: generates single pulse rising at the start point
      \arg        ENET_FLEXIBLE_PPS1_START_PULSE_TRAIN: generates the train of pulses rising at the start point
      \arg        ENET_FLEXIBLE_PPS1_CANCEL_START: cancels the start single pulse and start pulse train commands
      \arg        ENET_FLEXIBLE_PPS1_STOP_PULSE_TRAIN_AT_TIME: stops the train of pulses after the time programmed in the Target Time registers elapses
      \arg        ENET_FLEXIBLE_PPS1_STOP_PULSE_TRAIN_NOW: immediately stops the train of pulses
      \arg        ENET_FLEXIBLE_PPS1_CANCEL_STOP_PULSE_TRAIN: cancels the stop pulse train at time command if the programmed stop time has not elapsed

      \arg        ENET_FLEXIBLE_PPS2_START_SINGLE_PULSE: generates single pulse rising at the start point
      \arg        ENET_FLEXIBLE_PPS2_START_PULSE_TRAIN: generates the train of pulses rising at the start point
      \arg        ENET_FLEXIBLE_PPS2_CANCEL_START: cancels the start single pulse and start pulse train commands
      \arg        ENET_FLEXIBLE_PPS2_STOP_PULSE_TRAIN_AT_TIME: stops the train of pulses after the time programmed in the Target Time registers elapses
      \arg        ENET_FLEXIBLE_PPS2_STOP_PULSE_TRAIN_NOW: immediately stops the train of pulses
      \arg        ENET_FLEXIBLE_PPS2_CANCEL_STOP_PULSE_TRAIN: cancels the stop pulse train at time command if the programmed stop time has not elapsed

      \arg        ENET_FLEXIBLE_PPS3_START_SINGLE_PULSE: generates single pulse rising at the start point
      \arg        ENET_FLEXIBLE_PPS3_START_PULSE_TRAIN: generates the train of pulses rising at the start point
      \arg        ENET_FLEXIBLE_PPS3_CANCEL_START: cancels the start single pulse and start pulse train commands
      \arg        ENET_FLEXIBLE_PPS3_STOP_PULSE_TRAIN_AT_TIME: stops the train of pulses after the time programmed in the Target Time registers elapses
      \arg        ENET_FLEXIBLE_PPS3_STOP_PULSE_TRAIN_NOW: immediately stops the train of pulses
      \arg        ENET_FLEXIBLE_PPS3_CANCEL_STOP_PULSE_TRAIN: cancels the stop pulse train at time command if the programmed stop time has not elapsed
    \param[out] none
    \retval     none
*/
void enet_flexible_pps_command_config(enet_pps_enum pps, uint32_t stopsecond, uint32_t stopnanosubsecond, uint32_t command)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_NANOSECOND_VALUE(stopnanosubsecond)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00AEU), ERR_PARAM_OUT_OF_RANGE);
    } else if(NOT_ENET_PPS_COMMAND(command)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00AEU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(pps) {
    case PPS0:
        ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD;
        if(ENET_FLEXIBLE_PPS0_STOP_PULSE_TRAIN_AT_TIME == command) {
            ENET_MAC_PPS0_TARGET_TIME_SECONDS = stopsecond;
            ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS = stopnanosubsecond;
            ENET_MAC_PPS_CONTROL |= command;
        } else {
            ENET_MAC_PPS_CONTROL |= command;
        }
        break;
    case PPS1:
        ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCMD1;
        if(ENET_FLEXIBLE_PPS1_STOP_PULSE_TRAIN_AT_TIME == command) {
            ENET_MAC_PPS1_TARGET_TIME_SECONDS = stopsecond;
            ENET_MAC_PPS1_TARGET_TIME_NANOSECONDS = stopnanosubsecond;
            ENET_MAC_PPS_CONTROL |= command;
        } else {
            ENET_MAC_PPS_CONTROL |= command;
        }
        break;
    case PPS2:
        ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCMD2;
        if(ENET_FLEXIBLE_PPS2_STOP_PULSE_TRAIN_AT_TIME == command) {
            ENET_MAC_PPS2_TARGET_TIME_SECONDS = stopsecond;
            ENET_MAC_PPS2_TARGET_TIME_NANOSECONDS = stopnanosubsecond;
            ENET_MAC_PPS_CONTROL |= command;
        } else {
            ENET_MAC_PPS_CONTROL |= command;
        }
        break;
    case PPS3:
        ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCMD3;
        if(ENET_FLEXIBLE_PPS3_STOP_PULSE_TRAIN_AT_TIME == command) {
            ENET_MAC_PPS3_TARGET_TIME_SECONDS = stopsecond;
            ENET_MAC_PPS3_TARGET_TIME_NANOSECONDS = stopnanosubsecond;
            ENET_MAC_PPS_CONTROL |= command;
        } else {
            ENET_MAC_PPS_CONTROL |= command;
        }
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the value of presentation time
    \param[in]  mcgr: choose the instances of media clock which users want to check, refer to enet_mcgr_enum
                only one parameter can be selected which is shown as below
      \arg        MCGR0: MCGR 0
      \arg        MCGR1: MCGR 1
      \arg        MCGR0: MCGR 2
      \arg        MCGR1: MCGR 3
    \param[in]  seconds: the time seconds value
    \param[out] none
    \retval     none
*/
void enet_mcgr_present_time_set(enet_mcgr_enum mcgr, uint32_t seconds)
{
    switch(mcgr) {
    case MCGR0:
        ENET_MAC_PPS0_TARGET_TIME_SECONDS = seconds;
        break;
    case MCGR1:
        ENET_MAC_PPS1_TARGET_TIME_SECONDS = seconds;
        break;
    case MCGR2:
        ENET_MAC_PPS2_TARGET_TIME_SECONDS = seconds;
        break;
    case MCGR3:
        ENET_MAC_PPS3_TARGET_TIME_SECONDS = seconds;
        break;
    default:
        break;
    }
}

/*!
    \brief      set the value of current presentation time
    \param[in]  nanoseconds: the time nanoseconds value
    \param[out] none
    \retval     none
*/
uint32_t enet_mcgr_current_present_time_get(void)
{
    return ENET_MAC_PRESN_TIME_NS;
}

/*!
    \brief     configure the update value of presentation time
    \param[in]  nanosubsecond: the value will be updated to the nanosubsecond value of presentation time(0x00000000 - 0xFFFFFFFF)
    \param[out] none
    \retval     none
*/
void enet_mcgr_present_time_update(uint32_t nanosubsecond)
{
    ENET_MAC_PRESN_TIME_UPDT = MAC_PRESN_TIME_UPDT_MPTU(nanosubsecond);
}

/*!
    \brief      configure the mcgr related command
    \param[in]  pps: choose the instances of media clock which users want to check, refer to enet_mcgr_enum
                only one parameter can be selected which is shown as below
      \arg        MCGR0: MCGR 0
      \arg        MCGR1: MCGR 1
      \arg        MCGR0: MCGR 2
      \arg        MCGR1: MCGR 3
    \param[in]  mode: the mode of media clock,
                only one parameter can be selected which is shown as below
      \arg        ENET_MCGR0_OPERATION_NONE: MCGR operation is not carried out
      \arg        ENET_MCGR0_CAPTURE_RISING: capture the presentation time at the rising edge
      \arg        ENET_MCGR0_CAPTURE_FALLING: capture the presentation time at the falling edge
      \arg        ENET_MCGR0_CAPTURE_BOTH: capture the presentation time at both edgesenen
      \arg        ENET_MCGR0_OUTPUT_TOGGLE: toggle output on compare
      \arg        ENET_MCGR0_OUTPUT_LOW: pulse output low on compare for one PTP-clock cycle
      \arg        ENET_MCGR0_OUTPUT_HIGH: pulse output high on compare for one PTP-clock cycle

      \arg        ENET_MCGR1_OPERATION_NONE: MCGR operation is not carried out
      \arg        ENET_MCGR1_CAPTURE_RISING: capture the presentation time at the rising edge
      \arg        ENET_MCGR1_CAPTURE_FALLING: capture the presentation time at the falling edge
      \arg        ENET_MCGR1_CAPTURE_BOTH: capture the presentation time at both edgesenen
      \arg        ENET_MCGR1_OUTPUT_TOGGLE: toggle output on compare
      \arg        ENET_MCGR1_OUTPUT_LOW: pulse output low on compare for one PTP-clock cycle
      \arg        ENET_MCGR1_OUTPUT_HIGH: pulse output high on compare for one PTP-clock cycle

      \arg        ENET_MCGR2_OPERATION_NONE: MCGR operation is not carried out
      \arg        ENET_MCGR2_CAPTURE_RISING: capture the presentation time at the rising edge
      \arg        ENET_MCGR0_CAPTURE_FALLING: capture the presentation time at the falling edge
      \arg        ENET_MCGR0_CAPTURE_BOTH: capture the presentation time at both edgesenen
      \arg        ENET_MCGR0_OUTPUT_TOGGLE: toggle output on compare
      \arg        ENET_MCGR0_OUTPUT_LOW: pulse output low on compare for one PTP-clock cycle
      \arg        ENET_MCGR0_OUTPUT_HIGH: pulse output high on compare for one PTP-clock cycle

      \arg        ENET_MCGR0_OPERATION_NONE: MCGR operation is not carried out
      \arg        ENET_MCGR0_CAPTURE_RISING: capture the presentation time at the rising edge
      \arg        ENET_MCGR0_CAPTURE_FALLING: capture the presentation time at the falling edge
      \arg        ENET_MCGR0_CAPTURE_BOTH: capture the presentation time at both edgesenen
      \arg        ENET_MCGR0_OUTPUT_TOGGLE: toggle output on compare
      \arg        ENET_MCGR0_OUTPUT_LOW: pulse output low on compare for one PTP-clock cycle
      \arg        ENET_MCGR0_OUTPUT_HIGH: pulse output high on compare for one PTP-clock cycle
    \param[out] none
    \retval     none
*/
void enet_mcgr_media_clock_config(enet_mcgr_enum mcgr, uint32_t mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_MCGR_MODE(mode)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00B2U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    switch(mcgr) {
    case MCGR0:
        ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD;
        ENET_MAC_PPS_CONTROL |= (mode | ENET_MAC_PPS_CONTROL_MCGREN0);
        break;
    case MCGR1:
        ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCMD1;
        ENET_MAC_PPS_CONTROL |= (mode | ENET_MAC_PPS_CONTROL_MCGREN1);
        break;
    case MCGR2:
        ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCMD2;
        ENET_MAC_PPS_CONTROL |= (mode | ENET_MAC_PPS_CONTROL_MCGREN2);
        break;
    case MCGR3:
        ENET_MAC_PPS_CONTROL &= ~ENET_MAC_PPS_CONTROL_PPSCMD3;
        ENET_MAC_PPS_CONTROL |= (mode | ENET_MAC_PPS_CONTROL_MCGREN3);
        break;
    default:
        break;
    }
}
}

/*!
    \brief      set the timestamp asymmetry correction value
    \param[in]  type: timestamp type selection
                only one parameter can be selected which is shown as below
      \arg        TIMESTAMP_EGRESS: timestamp egress
      \arg        TIMESTAMP_INGRESS: timestamp ingress
    \param[in]  val: the asymmetry correction value(0x0 - 0xFFFFFFFF)
    \param[out] none
    \retval     none
*/
void enet_timestamp_asym_correction_set(enet_timestamp_type_enum type, uint32_t val)
{
    switch(type) {
    case TIMESTAMP_EGRESS:
        ENET_MAC_TIMESTAMP_EGRESS_ASYM_CORR &= ~ENET_MAC_TIMESTAMP_EGRESS_ASYM_CORR_OSTEAC;
        ENET_MAC_TIMESTAMP_EGRESS_ASYM_CORR = val;
        break;
    case TIMESTAMP_INGRESS:
        ENET_MAC_TIMESTAMP_INGRESS_ASYM_CORR &= ~ENET_MAC_TIMESTAMP_INGRESS_ASYM_CORR_OSTIAC;
        ENET_MAC_TIMESTAMP_INGRESS_ASYM_CORR = val;
        break;
    default:
        break;
    }
}

/*!
    \brief      set the timestamp correction value
    \param[in]  type: timestamp type selection
                only one parameter can be selected which is shown as below
      \arg        TIMESTAMP_EGRESS: timestamp egress
      \arg        TIMESTAMP_INGRESS: timestamp ingress
    \param[in]  nanosecond: the time nanoseconds value(0x0000 - 0xFFFFFFFF)
    \param[in]  nanosubsecond: the time nanosubsecond value(0x00 - 0xFF)
    \param[out] none
    \retval     none
*/
void enet_timestamp_correction_value_set(enet_timestamp_type_enum type, uint32_t nanosecond, uint8_t nanosubsecond)
{
    switch(type) {
    case TIMESTAMP_EGRESS:
        ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND &= ~ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC;
        ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND = nanosecond;
        ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC &= ~ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS;
        ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC = MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS(nanosubsecond);
        break;
    case TIMESTAMP_INGRESS:
        ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND &= ~ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC;
        ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND = nanosecond;
        ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC &= ~ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS;
        ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC = MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS(nanosubsecond);
        break;
    default:
        break;
    }
}

/*!
    \brief      set the timestamp latency value
    \param[in]  type: timestamp type selection
                only one parameter can be selected which is shown as below
      \arg        TIMESTAMP_EGRESS: timestamp egress
      \arg        TIMESTAMP_INGRESS: timestamp ingress
    \param[in]  latency: the nanosecond or subnanosecond portion of the latency selection
      \arg        LATENCY_NANOSECOND: nanosecond
      \arg        LATENCY_SUBNANOSECOND: subnanosecond
    \param[out] none
    \retval     uint16_t: the latency value
*/
uint16_t enet_timestamp_asym_latency_get(enet_timestamp_type_enum type, enet_timestamp_latency_enum latency)
{
    uint16_t ret_val = 0;
    switch(type) {
    case TIMESTAMP_EGRESS:
        if(LATENCY_NANOSECOND ==  latency) {
            ret_val = (uint16_t)((ENET_MAC_TIMESTAMP_EGRESS_LATENCY & ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS) >> 16);
        } else {
            ret_val = (uint16_t)((ENET_MAC_TIMESTAMP_EGRESS_LATENCY & ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS) >> 8);
        }
        break;
    case TIMESTAMP_INGRESS:
        if(LATENCY_NANOSECOND ==  latency) {
            ret_val = (uint16_t)((ENET_MAC_TIMESTAMP_INGRESS_LATENCY & ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS) >> 16);
        } else {
            ret_val = (uint16_t)((ENET_MAC_TIMESTAMP_INGRESS_LATENCY & ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS) >> 8);
        }
        break;
    default:
        break;
    }
    return ret_val;
}

/*!
    \brief     writing to the per queue/channel VLAN inclusion
    \param[in]  enet_vlantype_enum: vlan type selection
                only one parameter can be selected which is shown as below
      \arg        CVLAN: C-VLAN
      \arg        SVLAN: S-VLAN
    \param[in]  vlantag: the value will be updated to the VLAN tag(0x0000 - 0xFFFF)
    \param[in]  enet_txq: transmit queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1
    \param[out] none
    \retval     none
*/
void enet_queue_based_vlan_write(enet_vlantype_enum vlantype, uint16_t vlantag, enet_txq_enum queue)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;

    /* wait until BUSY bit is clear */
    while(((ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_BUSY) != (uint32_t)RESET) && (0U < timeout)) {
        timeout --;
    }
     ENET_MAC_VLAN_INCL |= ENET_MAC_VLAN_INCL_CBTI;

    while((ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_CBTI) == 0U){
    };
     ENET_MAC_VLAN_INCL |= ((uint32_t)queue << 24);
     ENET_MAC_VLAN_INCL |= ENET_MAC_VLAN_INCL_RDWR;
     ENET_MAC_VLAN_INCL &= ~(ENET_MAC_VLAN_INCL_CSVL | ENET_MAC_VLAN_INCL_VLT);

     ENET_MAC_VLAN_INCL |= (((uint32_t)vlantype << 19) | MAC_VLAN_INCL_VLT(vlantag));

    /* wait until BUSY bit is clear */
    timeout = ENET_OPERATION_TIMEROUT;
    while(((ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_BUSY) != (uint32_t)RESET) && (0U < timeout)) {
        timeout --;
    }
    ENET_MAC_VLAN_INCL &= ~ENET_MAC_VLAN_INCL_RDWR;
}

/*!
    \brief     read the type of the queue/channel VLAN
    \param[in]  enet_txq: transmit queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1
    \param[out] none
    \retval     enet_vlantype_enum: CVLAN or SVLAN
*/
enet_vlantype_enum enet_queue_based_vlan_type_read(enet_txq_enum queue)
{
    uint32_t timeout = ENET_OPERATION_TIMEROUT;
    enet_vlantype_enum vlantype;

/* wait until BUSY bit is clear */
    while(((ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_BUSY) != (uint32_t)RESET) && (0U < timeout)) {
        timeout --;
    }
    ENET_MAC_VLAN_INCL |= ENET_MAC_VLAN_INCL_CBTI;

    if(TXQ0 == queue) {
        ENET_MAC_VLAN_INCL &= ~ENET_MAC_VLAN_INCL_ADDR;
    } else {
        ENET_MAC_VLAN_INCL |= ENET_MAC_VLAN_INCL_ADDR;
    }
    ENET_MAC_VLAN_INCL &= ~ENET_MAC_VLAN_INCL_RDWR;
    /* wait until BUSY bit is clear */
    timeout = ENET_OPERATION_TIMEROUT;
    while(((ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_BUSY) != (uint32_t)RESET) && (0U < timeout)) {
        timeout --;
    }
    if((uint32_t)RESET != (ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_CSVL)){
        vlantype = SVLAN;
    } else {
        vlantype = CVLAN;
    }
    return vlantype;
}

/*!
    \brief     read the vlan tag of the queue/channel VLAN
    \param[in]  enet_txq: transmit queue selection
                only one parameter can be selected which is shown as below
      \arg        TXQ0: transmit queue 0
      \arg        TXQ1: transmit queue 1
    \param[out] none
    \retval     vlantag: vlan tag
*/
uint16_t enet_queue_based_vlan_tagvid_read(enet_txq_enum queue)
{
    uint16_t vlantag;

    while((ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_BUSY) != (uint32_t)RESET){
    };
    ENET_MAC_VLAN_INCL |= ENET_MAC_VLAN_INCL_CBTI;

    if(TXQ0 == queue) {
        ENET_MAC_VLAN_INCL &= ~ENET_MAC_VLAN_INCL_ADDR;
    } else {
        ENET_MAC_VLAN_INCL |= ENET_MAC_VLAN_INCL_ADDR;
    }
    ENET_MAC_VLAN_INCL &= ~ENET_MAC_VLAN_INCL_RDWR;
    /* wait until BUSY bit is clear */
    while((ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_BUSY) != (uint32_t)RESET) {
    }
    vlantag = (uint16_t)(ENET_MAC_VLAN_INCL & ENET_MAC_VLAN_INCL_VLT);
    
    return vlantag;
}

/*!
    \brief     select the MTL ECC memory
    \param[in]  memory: the memory type
                only one parameter can be selected which is shown as below
      \arg        ENET_MTL_ECC_SELECT_TX_MEM: MTL Tx memory
      \arg        ENET_MTL_ECC_SELECT_RX_MEM: MTL Rx memory
      \arg        ENET_MTL_ECC_SELECT_EST_MEM: MTL EST memory
      \arg        ENET_MTL_ECC_SELECT_RXP_MEM: MTL RXP memory
    \param[out] none
    \retval     none
*/
void enet_ecc_memory_select(uint32_t memory)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_ECC_MEMORY(memory)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00B9U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_ECC_ERR_STS_RCTL &= ~ENET_MTL_ECC_ERR_STS_RCTL_EMS;
    ENET_MTL_ECC_ERR_STS_RCTL |= memory;
}
}

/*!
    \brief     set the ECC error status related configuration
    \param[in]  config: the ECC error status related configuration
                only one parameter can be selected which is shown as below
      \arg        ENET_MTL_ECC_ERR_STATUS_READ_ENABLE: MTL ECC error status read enable
      \arg        ENET_MTL_UNCORRECTABLE_ERR_STATUS_CLEAR: clear unCorrectable error status
      \arg        ENET_MTL_CORRECTABLE_ERR_STATUS_CLEAR: clear Correctable error status
    \param[out] none
    \retval     none
*/
void enet_ecc_status_clear_read(uint32_t config)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_ECC_ERR_STATUS_CFG(config)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00BAU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_ECC_ERR_STS_RCTL &= ~(ENET_MTL_ECC_ERR_STS_RCTL_EESRE|ENET_MTL_ECC_ERR_STS_RCTL_CCES|ENET_MTL_ECC_ERR_STS_RCTL_CUES);
    ENET_MTL_ECC_ERR_STS_RCTL |= config;
}
}

/*!
    \brief     get the MTL ECC error address
    \param[in]  type: the type of error address status
                only one parameter can be selected which is shown as below
      \arg        ENET_MTL_UNCORRECTABLE_ERR_ADDRESS: MTL ECC uncorrectable error address status
      \arg        ENET_MTL_CORRECTABLE_ERR_ADDRESS: MTL ECC correctable error address status
    \param[out] none
    \retval     err_addr: the MTL ECC error address
*/
uint16_t enet_ecc_error_address_get(uint32_t type)
{
    uint16_t err_addr;
    err_addr = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_ECC_ERR_ADDRESS(type)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00BBU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if(ENET_MTL_UNCORRECTABLE_ERR_ADDRESS == type) {
        err_addr = (uint16_t)GET_UNCORRECTABLE_ERR_ADDRESS(ENET_MTL_ECC_ERR_ADDR_STATUS);
    } else {
        err_addr = (uint16_t)GET_CORRECTABLE_ERR_ADDRESS(ENET_MTL_ECC_ERR_ADDR_STATUS);
    }
}
    return err_addr;
}

/*!
    \brief     get the MTL ECC error counter
    \param[in]  type: the type of error address counter
                only one parameter can be selected which is shown as below
      \arg        ENET_MTL_UNCORRECTABLE_ERR_COUNT: MTL ECC uncorrectable error counter status
      \arg        ENET_MTL_CORRECTABLE_ERR_COUNT: MTL ECC correctable error counter status
    \param[out] none
    \retval     err_cnt: the MTL ECC error counter
*/
uint16_t enet_ecc_error_count_get(uint32_t type)
{
    uint16_t err_cnt;
    err_cnt = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_ECC_ERR_COUNT(type)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00BCU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    if(ENET_MTL_UNCORRECTABLE_ERR_COUNT == type) {
        err_cnt = (uint16_t)GET_UNCORRECTABLE_ERR_COUNT(ENET_MTL_ECC_ERR_CNTR_STATUS);
    } else {
        err_cnt = (uint16_t)GET_CORRECTABLE_ERR_COUNT(ENET_MTL_ECC_ERR_CNTR_STATUS);
    }

}
    return err_cnt;
}

/*!
    \brief     set the MTL error injection mode
    \param[in]  mode: the MTL error injection mode
                only one parameter can be selected which is shown as below
      \arg        ENET_ERR_INJTECTION_ON_ECC_PARITY: indicate error injection on ECC/Parity bits
      \arg        ENET_ERR_INJTECTION_ON_DATA: indicate error injection on data
    \param[out] none
    \retval     none
*/
void enet_error_injection_mode_set(uint32_t mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_MTL_ERR_INJECTION_MODE(mode)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00BDU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_DPP_ECC_EIC &= ~ENET_MTL_DPP_ECC_EIC_EIM;
    ENET_MTL_DPP_ECC_EIC |= mode;
}
}

/*!
    \brief     get the bit location of error injection
    \param[in]  none
    \param[out] none
    \retval     bit_location: the bit location of error injection
*/
uint16_t enet_error_injection_location_get(void)
{
    uint16_t bit_location;
    bit_location = (uint16_t)MTL_DPP_ECC_EIC_BLEI(ENET_MTL_DPP_ECC_EIC);
    return bit_location;
}

/*!
    \brief     set the MTL error injection configuration
    \param[in]  mode: the MTL error injection configuration
                only one parameter can be selected which is shown as below
      \arg        ENET_RXP_INSERT_ECC_ERR_1BIT: ECC inject 1-bit error for Rx parser memory
      \arg        ENET_RXP_INSERT_ECC_ERR_2BIT: ECC inject 2-bit error for Rx parser memory
      \arg        ENET_RXP_INSERT_ECC_ADDR_ERR_1BIT: ECC inject 1-bit address error for Rx parser memory
      \arg        ENET_RXP_INSERT_ECC_ADDR_ERR_2BIT: ECC inject 2-bit address error for Rx parser memory
    \param[out] none
    \retval     none
*/
void enet_error_injection_config(uint32_t config)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_ENET_MTL_ERR_INJECTION_CFG(config)){
        fw_debug_report_err(ENET_MODULE_ID, API_ID(0x00BFU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
{
    ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS &= ~(ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIEC|ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIAEE|ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIEE);
    ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS |= config;
}
}

#ifndef USE_DELAY
/*!
    \brief    insert a delay time
    \param[in]  ncount: specifies the delay time length
    \param[out] none
    \param[out] none
*/
static void enet_delay(uint32_t ncount)
{
    __IO uint32_t delay_time;
    delay_time = ncount;
    while(delay_time != 0U){
        delay_time--;
    }
}
#endif /* USE_DELAY */

#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
