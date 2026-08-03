/*!
    \file    gd32a7xx_qspi.c
    \brief   QSPI driver

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

#include "gd32a7xx_qspi.h"

/* QSPI register bit offset */
#define CTL_FTL_OFFSET                   ((uint32_t)0x00000008U)               /*!< bit offset of FTL in QSPI_CTL */
#define CTL_PSC_OFFSET                   ((uint32_t)0x00000018U)               /*!< bit offset of PSC in QSPI_CTL */
#define DCFG_FMSZ_OFFSET                 ((uint32_t)0x00000010U)               /*!< bit offset of FMSZ in QSPI_DCFG */
#define TCFG_DUMYC_OFFSET                ((uint32_t)0x00000012U)               /*!< bit offset of DUMYC in QSPI_TCFG */
#define CTL_OUTPUT_CK_DELAY_OFFSET       ((uint32_t)0x0000000CU)               /*!< bit offset of OCKDV in QSPI_CTL */

/* CPDM mask */
#define CPDM_CPSEL_MASK                  ((uint32_t)0xFFFFFFF0U)               /*!< CPDM output clock phase seclection mask */
#define CPDM_DLSTCNT_MASK                ((uint32_t)0xFFFF80FFU)               /*!< CPDM delay step count for a uint delay UINT mask */
#define CPDM_DLLENF_MASK                 ((uint32_t)0x80000000U)               /*!< CPDM delay line length valid flag mask */
#define CPDM_DLLEN_MASK                  ((uint32_t)0x0FFF0000U)               /*!< CPDM delay line length mask */

/* CPDM configure */
#define CPDM_DLLEN_OFFSET                ((uint32_t)16U)                       /*!< CPDM delay line length offset */
#define CPDM_DLSTCNT_OFFSET              ((uint32_t)8U)                        /*!< CPDM delay step count for a uint delay UINT offset */
#define CPDM_DLLEN_11                    ((uint32_t)0x08000000U)               /*!< CPDM delay line length bit 11 */
#define CPDM_DLLEN_10                    ((uint32_t)0x04000000U)               /*!< CPDM delay line length bit 10 */
#define CPDM_DLLEN_10_0_MASK             ((uint32_t)0x7FFU)                    /*!< CPDM delay line length bit 10 to bit 0 mask */
#define CPDM_MAX_TIMEOUT                 ((uint32_t)0x0000FFFFU)               /*!< count to judge of CPDM timeout */

/* configure QSPI functional mode */
static void qspi_config(qspi_command_struct *cmd, uint32_t functionalmode);

/*!
    \brief      reset QSPI (API_ID: 0x0001U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_deinit(void)
{
    /* reset QSPI register */
    QSPI_CTL      = 0x00000010U;
    QSPI_DCFG     = 0x001F0000U;
    QSPI_STATC    = 0x00000000U;
    QSPI_DTLEN    = 0x00000000U;
    QSPI_TCFG     = 0x00000000U;
    QSPI_ADDR     = 0x00000000U;
    QSPI_ALTE     = 0x00000000U;
    QSPI_DATA     = 0x00000000U;
    QSPI_STATMK   = 0x00000000U;
    QSPI_STATMATCH = 0x00000000U;
    QSPI_INTERVAL = 0x00000000U;
    QSPI_TMOUT    = 0x00000000U;
    QSPI_FLUSH    = 0x00000000U;
    CPDM_CTL      = 0x00000000U;
    CPDM_CFG      = 0x00000000U;
    /* reset QSPI */
    rcu_periph_reset_enable(RCU_QSPIRST);
    rcu_periph_reset_disable(RCU_QSPIRST);
}

/*!
    \brief      initialize the parameters of QSPI struct with the default values (API_ID: 0x0002U)
    \param[in]  none
    \param[out] init_para: QSPI parameter struct
    \retval     none
*/
void qspi_struct_para_init(qspi_init_struct *init_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_para)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* set the QSPI struct with the default values */
        init_para->clock_mode     = QSPI_CLOCK_MODE_LOW;
        init_para->prescaler      = 3U;
        init_para->fifo_threshold = 16U;
        init_para->sample_shift   = QSPI_SAMPLE_SHIFTING_NONE;
        init_para->flash_size     = 0x1FU;
        init_para->cs_high_time   = QSPI_CS_HIGH_TIME_1_CYCLE;
    }
}

/*!
    \brief      initialize the parameters of QSPI command struct with the default values (API_ID: 0x0003U)
    \param[in]  none
    \param[out] init_para: QSPI command parameter struct
    \retval     none
*/
void qspi_cmd_struct_para_init(qspi_command_struct *init_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_para)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* set the QSPI command struct with the default values */
        init_para->instruction_mode = QSPI_INSTRUCTION_NONE;
        init_para->instruction      = 0U;
        init_para->addr_mode        = QSPI_ADDR_NONE;
        init_para->addr_size        = QSPI_ADDR_8_BITS;
        init_para->addr             = 0U;
        init_para->altebytes_mode   = QSPI_ALTE_BYTES_NONE;
        init_para->altebytes_size   = QSPI_ALTE_BYTES_8_BITS;
        init_para->altebytes        = 0U;
        init_para->dummycycles      = 0U;
        init_para->data_mode        = QSPI_DATA_NONE;
        init_para->data_length      = 0U;
        init_para->sioo_mode        = QSPI_SIOO_INST_EVERY_CMD;
        init_para->trans_rate       = 0U;
        init_para->trans_delay      = 0U;
    }
}

/*!
    \brief      initialize the parameters of QSPI read polling struct with the default values (API_ID: 0x0004U)
    \param[in]  none
    \param[out] init_para: QSPI read polling parameter struct
    \retval     none
*/
void qspi_polling_struct_para_init(qspi_polling_struct *init_para)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(init_para)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* set the QSPI read polling struct with the default values */
        init_para->match            = 0U;
        init_para->mask             = 0U;
        init_para->interval         = 0U;
        init_para->statusbytes_size = 1;
        init_para->match_mode       = QSPI_MATCH_MODE_AND;
        init_para->polling_stop     = QSPI_POLLING_STOP_DISABLE;
    }
}

/*!
    \brief      initialize QSPI parameter (API_ID: 0x0005U)
    \param[in]  qspi_struct: QSPI parameter initialization stuct members of the structure
                            and the member values are shown as below:
                  prescaler: between 1 and 256
                  fifo_threshold: between 1 and 16
                  sample_shift: QSPI_SAMPLE_SHIFTING_NONE, QSPI_SAMPLE_SHIFTING_HALFCYCLE
                  flash_size: between 0 and 28
                  cs_high_time: QSPI_CS_HIGH_TIME_1_CYCLE, QSPI_CS_HIGH_TIME_2_CYCLE, QSPI_CS_HIGH_TIME_3_CYCLE,
                                QSPI_CS_HIGH_TIME_4_CYCLE, QSPI_CS_HIGH_TIME_5_CYCLE, QSPI_CS_HIGH_TIME_6_CYCLE,
                                QSPI_CS_HIGH_TIME_7_CYCLE, QSPI_CS_HIGH_TIME_8_CYCLE
                  clock_mode: QSPI_CLOCK_MODE_LOW, QSPI_CLOCK_MODE_HIGH
    \param[out] none
    \retval     none
*/
void qspi_init(qspi_init_struct *qspi_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(qspi_struct)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0005U), ERR_PARAM_POINTER);
    } else if(NOT_QSPI_CLOCK_MODE(qspi_struct->clock_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_PRESCALER(qspi_struct->prescaler)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_FIFO_THREAHOLD(qspi_struct->fifo_threshold)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_SAMPLE_SHIFT(qspi_struct->sample_shift)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_FLASH_SIZE(qspi_struct->flash_size)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_CS_HIGH_TIME(qspi_struct->cs_high_time)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* configure prescaler, sample_shift, fifo_threshold */
        QSPI_CTL &= ~(QSPI_CTL_PSC | QSPI_CTL_SSAMPLE | QSPI_CTL_FTL);
        QSPI_CTL |= ((qspi_struct->prescaler - 1U) << CTL_PSC_OFFSET) | qspi_struct->sample_shift | ((
                                                                                                         qspi_struct->fifo_threshold - 1U) << CTL_FTL_OFFSET);

        /* configure flash_size, cs_high_time, clock_mode */
        QSPI_DCFG &= ~((QSPI_DCFG_FMSZ) | QSPI_DCFG_CSHC | QSPI_DCFG_CKMOD);
        QSPI_DCFG |= ((qspi_struct->flash_size << DCFG_FMSZ_OFFSET) | qspi_struct->cs_high_time |
                      qspi_struct->clock_mode);
    }
}

/*!
    \brief      enable QSPI (API_ID: 0x0006U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_enable(void)
{
    QSPI_CTL |= (uint32_t)QSPI_CTL_QSPIEN;
}

/*!
    \brief      disable QSPI (API_ID: 0x0007U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_disable(void)
{
    QSPI_CTL &= (uint32_t)(~QSPI_CTL_QSPIEN);
}

/*!
    \brief      enable QSPI DMA (API_ID: 0x0008U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_dma_enable(void)
{
    QSPI_CTL |= (uint32_t)(QSPI_CTL_DMAEN);
}

/*!
    \brief      disable QSPI DMA (API_ID: 0x0009U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_dma_disable(void)
{
    QSPI_CTL &= (uint32_t)(~QSPI_CTL_DMAEN);
}

/*!
    \brief      configure QSPI command parameters (API_ID: 0x000AU)
    \param[in]  cmd: QSPI command parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  instruction_mode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                    QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  instruction: reference flash commands description
                  addr_mode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  addr_size: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  addr: 0-flash size
                  altebytes_mode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                  QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  altebytes_size: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                  QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  altebytes: 0-0xFFFFFFFF
                  dummycycles: between 0 and 31
                  data_mode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  data_length: 0-0xFFFFFFFF
                  sioo_mode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
                  trans_rate: QSPI_SDR_MODE, QSPI_DDR_MODE
                  trans_delay: QSPI_DDR_HOLD_DISABLE, QSPI_DDR_HOLD_ENABLE
    \param[out] none
    \retval     none
*/
void qspi_command_config(qspi_command_struct *cmd)
{
    uint16_t timeout = QSPI_COMMAND_CONFIG_TOMEOUT;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(cmd)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_POINTER);
    } else if(NOT_QSPI_INSTRUCTIN_MODE(cmd->instruction_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_INSTRUCTIN(cmd->instruction)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ADDR_MODE(cmd->addr_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ADDR_SIZE(cmd->addr_size)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ALTEBYTES_MODE(cmd->altebytes_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ALTEBYTES_SIZE(cmd->altebytes_size)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_DUMMYCYCLES(cmd->dummycycles)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_DATA_MODE(cmd->data_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_SIOO_MODE(cmd->sioo_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_TRANS_RATE(cmd->trans_rate)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_TRANS_DELAY(cmd->trans_delay)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        qspi_disable();
        qspi_enable();

        /* call the configuration function */
        qspi_config(cmd, QSPI_NORMAL_WRITE);

        if(cmd->data_mode == QSPI_DATA_NONE) {
            /* when there is no data phase, the transfer start as soon as the configuration is done
            so wait until TC flag is set to go back in idle state */
            while(((QSPI_STAT & QSPI_FLAG_TC ) == 0U) && (timeout > 0U)){
                timeout--;
            }
            QSPI_STATC = QSPI_STATC_TCC;
        }
    }
}

/*!
    \brief      configure QSPI read polling mode (API_ID: 0x000BU)
    \param[in]  cmd: QSPI command parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  instruction_mode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                    QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  instruction: reference flash commands description
                  addr_mode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  addr_size: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  addr: 0-flash size
                  altebytes_mode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                  QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  altebytes_size: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                  QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  altebytes: 0-0xFFFFFFFF
                  dummycycles: between 0 and 31
                  data_mode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  data_length: 0-0xFFFFFFFF
                  sioo_mode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
                  trans_rate: QSPI_SDR_MODE, QSPI_DDR_MODE
                  trans_delay: QSPI_DDR_HOLD_DISABLE, QSPI_DDR_HOLD_ENABLE
    \param[in]  cfg: read polling struct initialization stuct members of the structure
                             and the member values are shown as below:
                  match: between 0 and 0xFFFFFFFF
                  mask: between 0 and 0xFFFFFFFF
                  interval: between 0 and 0xFFFF
                  statusbytes_size: between 1 and 4
                  match_mode: QSPI_MATCH_MODE_AND, QSPI_MATCH_MODE_OR
                  polling_stop: QSPI_POLLING_STOP_DISABLE,QSPI_POLLING_STOP_ENABLE
    \param[out] none
    \retval     none
*/
void qspi_polling_config(qspi_command_struct *cmd, qspi_polling_struct *cfg)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(cmd)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_POINTER);
    } else if(NOT_VALID_POINTER(cfg)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_POINTER);
    } else if(NOT_QSPI_INSTRUCTIN_MODE(cmd->instruction_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_INSTRUCTIN(cmd->instruction)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ADDR_MODE(cmd->addr_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ADDR_SIZE(cmd->addr_size)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ALTEBYTES_MODE(cmd->altebytes_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ALTEBYTES_SIZE(cmd->altebytes_size)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_DUMMYCYCLES(cmd->dummycycles)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_DATA_MODE(cmd->data_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_SIOO_MODE(cmd->sioo_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_TRANS_RATE(cmd->trans_rate)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_TRANS_DELAY(cmd->trans_delay)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_NUM_CLK_CYC(cfg->interval)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_SATUSBYTES_SIZE(cfg->statusbytes_size)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_MATCH_MODE(cfg->match_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else if(NOT_QSPI_POLLING_STOP(cfg->polling_stop)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* configure the match value */
        QSPI_STATMATCH = cfg->match;
        /* configure the mask value */
        QSPI_STATMK = cfg->mask;
        /* configure the interval cycle */
        QSPI_INTERVAL = cfg->interval;
        /* configure the read polling match mode and read polling mode stop */
        QSPI_CTL &= ~(QSPI_CTL_RPMS | QSPI_CTL_RPMM);
        QSPI_CTL |= (cfg->match_mode | cfg->polling_stop);

        cmd->data_length = cfg->statusbytes_size;
        qspi_config(cmd, QSPI_READ_POLLING);
    }
}

/*!
    \brief      configure QSPI memory mapped mode (API_ID: 0x000CU)
    \param[in]  cmd: QSPI command parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  instruction_mode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                    QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  instruction: reference flash commands description
                  addr_mode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  addr_size: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  addr: 0-flash size
                  altebytes_mode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                  QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  altebytes_size: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                  QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  altebytes: 0-0xFFFFFFFF
                  dummycycles: between 0 and 31
                  data_mode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  data_length: 0-0xFFFFFFFF
                  sioo_mode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
                  trans_rate: QSPI_SDR_MODE, QSPI_DDR_MODE
                  trans_delay: QSPI_DDR_HOLD_DISABLE, QSPI_DDR_HOLD_ENABLE
    \param[in]  timeout: 0-0xFFFF
    \param[in]  toen:
      \arg        QSPI_TMOUT_DISABLE: disable timeout counter
      \arg        QSPI_TMOUT_ENABLE: enable timeout counter
    \param[out] none
    \retval     none
*/
void qspi_memorymapped_config(qspi_command_struct *cmd, uint16_t timeout, uint32_t toen)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(cmd)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_POINTER);
    } else if(NOT_QSPI_INSTRUCTIN_MODE(cmd->instruction_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else if(NOT_QSPI_INSTRUCTIN(cmd->instruction)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ADDR_MODE(cmd->addr_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ADDR_SIZE(cmd->addr_size)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ALTEBYTES_MODE(cmd->altebytes_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_ALTEBYTES_SIZE(cmd->altebytes_size)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_DUMMYCYCLES(cmd->dummycycles)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_DATA_MODE(cmd->data_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_SIOO_MODE(cmd->sioo_mode)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_TRANS_RATE(cmd->trans_rate)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_TRANS_DELAY(cmd->trans_delay)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_TIMEOUT_COUNT(toen)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* enable timeout */
        QSPI_CTL &= ~QSPI_CTL_TMOUTEN;
        QSPI_CTL |= toen;

        if(toen == QSPI_CTL_TMOUTEN) {
            /* configure the timeout value */
            QSPI_TMOUT = timeout;
            QSPI_STATC = QSPI_STATC_TMOUTC;
            /* enable the QSPI timeout interrupt */
            QSPI_CTL |= QSPI_CTL_TMOUTIE;
        }
        qspi_config(cmd, QSPI_MEMORY_MAPPED);
    }
}

/*!
    \brief      QSPI transmit data function (API_ID: 0x000DU)
    \param[in]  tdata: pointer to the data to be transmitted
    \param[out] none
    \retval     none
*/
void qspi_data_transmit(uint8_t *tdata)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(tdata)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000DU), ERR_PARAM_POINTER);
    } else
#endif
    {
        uint32_t tx_cnt;
        uint16_t timeout = QSPI_DATA_TRANSMIT_TOMEOUT;
        tx_cnt = QSPI_DTLEN + 1U;

        qspi_disable();
        QSPI_TCFG = (QSPI_TCFG & ~QSPI_TCFG_FMOD) | QSPI_NORMAL_WRITE;
        qspi_enable();

        while(tx_cnt > 0U) {
            while(((QSPI_STAT & QSPI_FLAG_FT ) == 0U) && (timeout > 0U)){
                timeout--;
            }
            /* transmit data */
            *(uint8_t *)(QSPI + 0x00000020U) = *tdata++;
            tx_cnt--;
        }
    }
}

/*!
    \brief      QSPI receive data function (API_ID: 0x000EU)
    \param[in]  none
    \param[out] rdata: pointer to the data to be received
    \retval     none
*/
void qspi_data_receive(uint8_t *rdata)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(rdata)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x000EU), ERR_PARAM_POINTER);
    } else
#endif
    {
        uint32_t rx_cnt, addr;
        uint16_t timeout = QSPI_DATA_RECEIVE_TOMEOUT;
        rx_cnt = QSPI_DTLEN + 1U;
        addr = QSPI_ADDR;

        qspi_disable();
        QSPI_TCFG = (QSPI_TCFG & ~QSPI_TCFG_FMOD) | QSPI_NORMAL_READ;
        qspi_enable();
        /* start the transfer by re-writing the address in QSPI_ADDR register */
        QSPI_ADDR = addr;

        while(rx_cnt > 0U) {
            while(((QSPI_STAT & (QSPI_FLAG_FT | QSPI_FLAG_TC)) == 0U) && (timeout > 0U)){
                timeout--;
            }
            *rdata++ = *(uint8_t *)(QSPI + 0x00000020U);
            rx_cnt--;
        }
    }
}

/*!
    \brief      abort the current transmission (API_ID: 0x000FU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_transmission_abort(void)
{
    uint16_t timeout = QSPI_DATA_ABORT_TOMEOUT;
    QSPI_CTL |= (uint32_t)(QSPI_CTL_ABORT);
    /* wait abort bit reset */
    while(((QSPI_CTL & QSPI_CTL_ABORT) == QSPI_CTL_ABORT) && (timeout > 0U)){
        timeout--;
    };
}

/*!
    \brief      enable QSPI output clock delay (API_ID: 0x0010U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_output_clock_delay_enable(void)
{
    QSPI_CTL |= (uint32_t)QSPI_CTL_OCKDEN;
}

/*!
    \brief      disable QSPI output clock delay (API_ID: 0x0011U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_output_clock_delay_disable(void)
{
    QSPI_CTL &= (uint32_t)(~QSPI_CTL_OCKDEN);
}

/*!
    \brief      configure output clock delay (API_ID: 0x0012U)
    \param[in]  ck_delay: 0~15
    \param[out] none
    \retval     none
*/
void qspi_output_clock_delay_config(uint32_t ck_delay)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_CLOCK_DELAY(ck_delay)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else
#endif
    {
        QSPI_CTL &= (uint32_t)(~QSPI_CTL_OCKDV);
        QSPI_CTL |= (uint32_t)(ck_delay << CTL_OUTPUT_CK_DELAY_OFFSET);
    }
}

/*!
    \brief      config qspi sample shift (API_ID: 0x0013U)
    \param[in]  sample_shift1: QSPI sample shift1, support use with 2
                only one parameter can be selected which are shown as below:
      \arg        QSPI_SAMPLE_SHIFTING_NONE: no shift when sample data
      \arg        QSPI_SAMPLE_SHIFTING_HALFCYCLE: 1/2 sck cycle shift
    \param[in]  sample_shift2: QSPI sample shift2, support use with 1
                only one parameter can be selected which are shown as below:
      \arg        QSPI_SHIFTING_NONE: no shift when sample data
      \arg        QSPI_SHIFTING_1_CYCLE: 1 sck cycle shift
      \arg        QSPI_SHIFTING_2_CYCLE: 2 sck cycle shift
      \arg        QSPI_SHIFTING_3_CYCLE: 3 sck cycle shift
      \arg        QSPI_SHIFTING_4_CYCLE: 4 sck cycle shift
      \arg        QSPI_SHIFTING_5_CYCLE: 5 sck cycle shift
      \arg        QSPI_SHIFTING_6_CYCLE: 6 sck cycle shift
      \arg        QSPI_SHIFTING_7_CYCLE: 7 sck cycle shift
    \param[out] none
    \retval     none
*/
void qspi_sample_shift_config(uint32_t sample_shift1, uint32_t sample_shift2)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_SAMPLE_SHIFT1(sample_shift1)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
    } else if(NOT_QSPI_SAMPLE_SHIFT2(sample_shift2)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
    } else
#endif
    {
        if(QSPI_SAMPLE_SHIFTING_NONE == sample_shift1) {
            QSPI_CTL &= (uint32_t)(~QSPI_CTL_SSAMPLE);
        } else {
            QSPI_CTL |= sample_shift1;
        }

        if(QSPI_SHIFTING_NONE == sample_shift2) {
            QSPI_DCFG &= (uint32_t)(~QSPI_DCFG_RXSFT);
        } else {
            QSPI_DCFG |= sample_shift2;
        }
    }
}

/*!
    \brief      select receive clock (API_ID: 0x0014U)
    \param[in]  rcksel: receive clock select
                only one parameter can be selected which is shown as below:
      \arg        QSPI_RECEIVE_CLOCK_SCK
      \arg        QSPI_RECEIVE_CLOCK_DQS
    \param[out] none
    \retval     none
*/
void qspi_receive_clock_sel(uint32_t rcksel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_RCKSEL(rcksel)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    } else
#endif
    {
        if(QSPI_RECEIVE_CLOCK_SCK == rcksel) {
            QSPI_DCFG &= (uint32_t)(~QSPI_DCFG_RCKSEL);
        } else {
            QSPI_DCFG |= rcksel;
        }
    }
}

/*!
    \brief      enable QSPI delay scan (API_ID: 0x0015U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_delay_scan_enable(void)
{
    QSPI_DCFG |= (uint32_t)QSPI_DCFG_DLYSCEN;
}

/*!
    \brief      disable QSPI delay scan (API_ID: 0x0016U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void qspi_delay_scan_disable(void)
{
    QSPI_DCFG &= (uint32_t)(~QSPI_DCFG_DLYSCEN);
}

/*!
    \brief      csn falls and rises 1 or 2 sck cycles select (API_ID: 0x0017U)
    \param[in]  csn_cycle: receive clock select
                only one parameter can be selected which are shown as below:
      \arg        QSPI_CSN_1_CYCLE: csn falls and rises 1 sck cycle
      \arg        QSPI_CSN_2_CYCLE: csn falls and rises 2 sck cycle
    \param[out] none
    \retval     none
*/
void qspi_csn_edge_cycle(uint32_t csn_cycle)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_CSN_CLOCK(csn_cycle)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    } else
#endif
    {
        if(QSPI_CSN_1_CYCLE == csn_cycle) {
            QSPI_DCFG &= (uint32_t)(~QSPI_DCFG_CSNCKM);
        } else {
            QSPI_DCFG |= csn_cycle;
        }
    }
}

/*!
    \brief      get QSPI flag status (API_ID: 0x0018U)
    \param[in]  flag: QSPI flag
                only one parameter can be selected which are shown as below:
      \arg        QSPI_FLAG_BUSY: busy flag
      \arg        QSPI_FLAG_TERR: transfer error flag
      \arg        QSPI_FLAG_TC: transfer complete flag
      \arg        QSPI_FLAG_FT: FIFO threshold flag
      \arg        QSPI_FLAG_RPMF: read polling match flag
      \arg        QSPI_FLAG_TMOUT: timeout flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus qspi_flag_get(uint32_t flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_FLAG(flag)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else 
#endif
    {
        if((uint32_t)RESET != (QSPI_STAT & flag)) {
            reval = SET;
        }
    }
    return reval;
}

/*!
    \brief      clear QSPI flag status (API_ID: 0x0019U)
    \param[in]  flag: QSPI flag
                only one parameter can be selected which are shown as below:
      \arg        QSPI_FLAG_TERR: transfer error flag
      \arg        QSPI_FLAG_TC: transfer complete flag
      \arg        QSPI_FLAG_RPMF: read polling match flag
      \arg        QSPI_FLAG_TMOUT: timeout flag
    \param[out] none
    \retval     none
*/
void qspi_flag_clear(uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_FLAG_CLEAR(flag)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else
#endif
    {
        QSPI_STATC |= (uint32_t)flag;
    }
}

/*!
    \brief      enable QSPI interrupt (API_ID: 0x001AU)
    \param[in]  interrupt: QSPI interrupt
                only one parameter can be selected which is shown as below:
      \arg        QSPI_INT_TC: transfer complete interrupt
      \arg        QSPI_INT_FT: FIFO threshold interrupt
      \arg        QSPI_INT_TERR: transfer error interrupt
      \arg        QSPI_INT_RPMF: read polling match interrupt
      \arg        QSPI_INT_TMOUT: timeout interrupt
    \param[out] none
    \retval     none
*/
void qspi_interrupt_enable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_INTERRUPT(interrupt)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    } else
#endif
    {
        QSPI_CTL |= (uint32_t)interrupt;
    }
}

/*!
    \brief      disable QSPI interrupt (API_ID: 0x001BU)
    \param[in]  interrupt: QSPI interrupt
                only one parameter can be selected which is shown as below:
      \arg        QSPI_INT_TC: transfer complete interrupt
      \arg        QSPI_INT_FT: FIFO threshold interrupt
      \arg        QSPI_INT_TERR: transfer error interrupt
      \arg        QSPI_INT_RPMF: read polling match interrupt
      \arg        QSPI_INT_TMOUT: timeout interrupt
    \param[out] none
    \retval     none
*/
void qspi_interrupt_disable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_INTERRUPT(interrupt)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    } else
#endif
    {
        QSPI_CTL &= ~(uint32_t)interrupt;
    }
}

/*!
    \brief      get QSPI interrupt flag status (API_ID: 0x001CU)
    \param[in]  int_flag: QSPI interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        QSPI_INT_FLAG_TERR: transfer error flag
      \arg        QSPI_INT_FLAG_TC: transfer complete flag
      \arg        QSPI_INT_FLAG_FT: FIFO threshold flag
      \arg        QSPI_INT_FLAG_RPMF: read polling match flag
      \arg        QSPI_INT_FLAG_TMOUT: timeout flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus qspi_interrupt_flag_get(uint32_t int_flag)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_INTERRUPT_FLAG(int_flag)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg1 = QSPI_STAT;
        uint32_t reg2 = QSPI_CTL;

        switch(int_flag) {
            /* QSPI transfer error interrupt flag */
            case QSPI_INT_FLAG_TERR:
                reg1 = reg1 & QSPI_STAT_TERR;
                reg2 = reg2 & QSPI_CTL_TERRIE;
                break;
            /* QSPI transfer complete interrupt flag */
            case QSPI_INT_FLAG_TC:
                reg1 = reg1 & QSPI_STAT_TC;
                reg2 = reg2 & QSPI_CTL_TCIE;
                break;
            /* QSPI FIFO threshold interrupt flag */
            case QSPI_INT_FLAG_FT:
                reg1 = reg1 & QSPI_STAT_FT;
                reg2 = reg2 & QSPI_CTL_FTIE;
                break;
            /* QSPI status match interrupt flag */
            case QSPI_INT_FLAG_RPMF:
                reg1 = reg1 & QSPI_STAT_RPMF;
                reg2 = reg2 & QSPI_CTL_RPMFIE;
                break;
            /* QSPI timeout interrupt flag */
            case QSPI_INT_FLAG_TMOUT:
                reg1 = reg1 & QSPI_STAT_TMOUT;
                reg2 = reg2 & QSPI_CTL_TMOUTIE;
                break;
            default :
                break;
        }
        /* get QSPI interrupt flag status */
        if((reg1 != 0U) && (reg2 != 0U)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear QSPI interrupt flag status (API_ID: 0x001DU)
    \param[in]  int_flag: QSPI interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        QSPI_INT_FLAG_TERR: transfer error flag
      \arg        QSPI_INT_FLAG_TC: transfer complete flag
      \arg        QSPI_INT_FLAG_RPMF: read polling match flag
      \arg        QSPI_INT_FLAG_TMOUT: timeout flag
    \param[out] none
    \retval     none
*/
void qspi_interrupt_flag_clear(uint32_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_QSPI_INTERRUPT_FLAG_CLEAR(int_flag)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    } else
#endif
    {
        QSPI_STATC |= (uint32_t)int_flag;
    }
}

/*!
    \brief      configure QSPI functional mode
    \param[in]  cmd: QSPI command parameter initialization stuct members of the structure
                             and the member values are shown as below:
                  instruction_mode: QSPI_INSTRUCTION_NONE, QSPI_INSTRUCTION_1_LINE,
                                    QSPI_INSTRUCTION_2_LINES, QSPI_INSTRUCTION_4_LINES
                  instruction: reference flash commands description
                  addr_mode: QSPI_ADDR_NONE, QSPI_ADDR_1_LINE, QSPI_ADDR_2_LINES, QSPI_ADDR_4_LINES
                  addr_size: QSPI_ADDR_8_BITS, QSPI_ADDR_16_BITS, QSPI_ADDR_24_BITS, QSPI_ADDR_32_BITS
                  addr: 0-flash size
                  altebytes_mode: QSPI_ALTE_BYTES_NONE, QSPI_ALTE_BYTES_1_LINE,
                                  QSPI_ALTE_BYTES_2_LINES, QSPI_ALTE_BYTES_4_LINES
                  altebytes_size: QSPI_ALTE_BYTES_8_BITS, QSPI_ALTE_BYTES_16_BITS,
                                  QSPI_ALTE_BYTES_24_BITS, QSPI_ALTE_BYTES_32_BITS
                  altebytes: 0-0xFFFFFFFF
                  dummycycles: between 0 and 31
                  data_mode: QSPI_DATA_NONE, QSPI_DATA_1_LINE, QSPI_DATA_2_LINES, QSPI_DATA_4_LINES
                  data_length: 0-0xFFFFFFFF
                  sioo_mode: QSPI_SIOO_INST_EVERY_CMD, QSPI_SIOO_INST_ONLY_FIRST_CMD
                  trans_rate: QSPI_SDR_MODE, QSPI_DDR_MODE
                  trans_delay: QSPI_DDR_HOLD_DISABLE, QSPI_DDR_HOLD_ENABLE
    \param[in]  functionalmode: QSPI functional mode select
                only one parameter can be selected which is shown as below:
      \arg        QSPI_NORMAL_WRITE
      \arg        QSPI_NORMAL_READ
      \arg        QSPI_READ_POLLING
      \arg        QSPI_MEMORY_MAPPED
    \param[out] none
    \retval     none
*/
static void qspi_config(qspi_command_struct *cmd, uint32_t functionalmode)
{
    if((cmd->data_mode != QSPI_DATA_NONE) && (functionalmode != QSPI_MEMORY_MAPPED)) {
        /* configure QSPI_DTLEN register with the number of data to read or write */
        QSPI_DTLEN = cmd->data_length - 1U;
    }

    if(cmd->altebytes_mode != QSPI_ALTE_BYTES_NONE) {
        /* configure QSPI_ALTE register with alternate bytes value */
        QSPI_ALTE = cmd->altebytes;
    }
    if((cmd->data_mode != QSPI_DATA_NONE) || (cmd->altebytes_mode != QSPI_ALTE_BYTES_NONE) || \
            (cmd->addr_mode != QSPI_ADDR_NONE) || (cmd->instruction_mode != QSPI_INSTRUCTION_NONE)) {

        QSPI_TCFG = cmd->data_mode | (cmd->dummycycles << TCFG_DUMYC_OFFSET) | cmd->sioo_mode |
                    cmd->altebytes_size | cmd->altebytes_mode |
                    cmd->addr_size | cmd->addr_mode | cmd->instruction_mode |
                    cmd->instruction | cmd->trans_rate | cmd->trans_delay | functionalmode;
    }

    if((cmd->addr_mode != QSPI_ADDR_NONE) && (functionalmode != QSPI_MEMORY_MAPPED)) {
        /* configure QSPI_ADDR register with address value */
        QSPI_ADDR = cmd->addr;
    }
}

/*!
    \brief      enable CPDM (API_ID: 0x001EU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cpdm_enable(void)
{
    /* enable CPDM */
    CPDM_CTL |= (uint32_t)CPDM_CTL_CPDMEN;
}

/*!
    \brief      disable CPDM (API_ID: 0x001FU)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cpdm_disable(void)
{
    /* disable CPDM */
    CPDM_CTL &= ~(uint32_t)CPDM_CTL_CPDMEN;
}

/*!
    \brief      enable CPDM delay line sample module (API_ID: 0x0020U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cpdm_delayline_sample_enable(void)
{
    /* enable CPDM delay line sample module */
    CPDM_CTL |= (uint32_t)CPDM_CTL_DLSEN;
}

/*!
    \brief      disable CPDM delay line sample module (API_ID: 0x0021U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void cpdm_delayline_sample_disable(void)
{
    /* disable CPDM delay line sample module */
    CPDM_CTL &= ~(uint32_t)CPDM_CTL_DLSEN;
}

/*!
    \brief      select CPDM output clock phase (API_ID: 0x0022U)
    \param[in]  output_clock_phase: the output clock phase, refer to cpdm_output_phase_enum
                only one parameter can be selected which is shown as below:
      \arg        CPDM_OUTPUT_PHASE_SELECTION_0: output clock phase = input clock
      \arg        CPDM_OUTPUT_PHASE_SELECTION_1: output clock phase = input clock + 1 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_2: output clock phase = input clock + 2 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_3: output clock phase = input clock + 3 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_4: output clock phase = input clock + 4 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_5: output clock phase = input clock + 5 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_6: output clock phase = input clock + 6 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_7: output clock phase = input clock + 7 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_8: output clock phase = input clock + 8 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_9: output clock phase = input clock + 9 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_10: output clock phase = input clock + 10 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_11: output clock phase = input clock + 11 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_12: output clock phase = input clock + 12 * UNIT delay
    \param[out] none
    \retval     none
*/
void cpdm_output_clock_phase_select(cpdm_output_phase_enum output_clock_phase)
{
    uint32_t reg;

    reg = CPDM_CFG;
    reg &= CPDM_CPSEL_MASK;
    /* select CPDM output clock phase */
    reg |= (uint32_t)output_clock_phase;
    CPDM_CFG = reg;
}

/*!
    \brief      configure CPDM delay step (API_ID: 0x0023U)
    \param[in]  delay_step: 0 ~ 127
    \param[out] none
    \retval     none
*/
void cpdm_delay_step_config(uint8_t delay_step)
{
    uint32_t reg;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CPDM_DELAY_STEP_COUNT(delay_step)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0023U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        reg = CPDM_CFG;
        reg &= CPDM_DLSTCNT_MASK;
        /* configure delay step */
        reg |= ((uint32_t)delay_step << CPDM_DLSTCNT_OFFSET);
        CPDM_CFG = reg;
    }
}

/*!
    \brief      get delay line length valid flag (API_ID: 0x0024U)
    \param[in]  none
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus cpdm_delayline_length_valid_flag_get(void)
{
    uint32_t reg;
    FlagStatus reval;

    reg = CPDM_CFG;
    if(CPDM_DLLENF_MASK == (reg & CPDM_DLLENF_MASK)) {
        reval = SET;
    } else {
        reval = RESET;
    }

    return reval;
}

/*!
    \brief      get delay line length (API_ID: 0x0025U)
    \param[in]  none
    \param[out] none
    \retval     the value of delay line length, 0x00~0xFFF
*/
uint16_t cpdm_delayline_length_get(void)
{
    return (uint16_t)((CPDM_CFG & CPDM_DLLEN_MASK) >> CPDM_DLLEN_OFFSET);
}

/*!
    \brief      configure CPDM clock output (API_ID: 0x0026U)
    \param[in]  output_clock_phase: the output clock phase, refer to cpdm_output_phase_enum
                only one parameter can be selected which is shown as below:
      \arg        CPDM_OUTPUT_PHASE_SELECTION_0: output clock phase = input clock
      \arg        CPDM_OUTPUT_PHASE_SELECTION_1: output clock phase = input clock + 1 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_2: output clock phase = input clock + 2 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_3: output clock phase = input clock + 3 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_4: output clock phase = input clock + 4 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_5: output clock phase = input clock + 5 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_6: output clock phase = input clock + 6 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_7: output clock phase = input clock + 7 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_8: output clock phase = input clock + 8 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_9: output clock phase = input clock + 9 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_10: output clock phase = input clock + 10 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_11: output clock phase = input clock + 11 * UNIT delay
      \arg        CPDM_OUTPUT_PHASE_SELECTION_12: output clock phase = input clock + 12 * UNIT delay
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus cpdm_clock_output(cpdm_output_phase_enum output_clock_phase)
{
    ErrStatus reval = SUCCESS;
    uint32_t reg;
    uint32_t reg_cfg;
    uint32_t delay_count;
    uint32_t timeout = 0U;

    /* enable CPDM and delay line sample module */
    CPDM_CTL = 0U;
    CPDM_CTL = CPDM_CTL_CPDMEN | CPDM_CTL_DLSEN;
    /* configure CPDM output clock phase to the max value (12) */
    reg = CPDM_CFG;
    reg &= CPDM_CPSEL_MASK;
    reg |= CPDM_MAX_PHASE;
    CPDM_CFG = (uint32_t)reg;

    for(delay_count = 0U; delay_count <= CPDM_MAX_DELAY_STEP_COUNT; delay_count++) {
        reg = CPDM_CFG;
        reg &= CPDM_DLSTCNT_MASK;
        /* configure delay line step count */
        reg |= (delay_count << CPDM_DLSTCNT_OFFSET);
        CPDM_CFG = (uint32_t)reg;

        /* Wait for the delay line length to be valid */
        while(CPDM_CFG_DLLENF != (CPDM_CFG & CPDM_CFG_DLLENF)) {
            timeout++;
            if(timeout > CPDM_MAX_TIMEOUT)
            {
                timeout = 0;
                reval = ERROR;
                break;
            }
        }
        if(ERROR == reval) {
            break;
        }

        reg_cfg = CPDM_CFG;
        if((((reg_cfg >> CPDM_DLLEN_OFFSET) & CPDM_DLLEN_10_0_MASK) > 0U) &&
                ((CPDM_DLLEN_11 != (reg_cfg & CPDM_DLLEN_11)) || (CPDM_DLLEN_10 != (reg_cfg & CPDM_DLLEN_10)))) {
            break;
        }
    }

    if(delay_count > CPDM_MAX_DELAY_STEP_COUNT) {
        /* delay line length is not valid */
        reval = ERROR;
    }

    if (SUCCESS == reval) {
        /* enable CPDM and delay line sample module */
        CPDM_CTL = 0U;
        CPDM_CTL = CPDM_CTL_CPDMEN | CPDM_CTL_DLSEN;
        /* select the output clock phase */
        reg = CPDM_CFG;
        reg &= CPDM_CPSEL_MASK;
        reg |= (uint32_t)output_clock_phase;
        CPDM_CFG = (uint32_t)reg;
        /* disable delay line sample module */
        CPDM_CTL = CPDM_CTL_CPDMEN;
    }

    return reval;
}

/*!
    \brief      get QSPI TMR alarm status (API_ID: 0x0027U)
    \param[in]  tmr_alarm: tmr alarm status
                only one parameter can be selected which is shown as below:
        \arg      QSPI_TMRALM_CTL_FLAG
        \arg      QSPI_TMRALM_DTLEN_FLAG
        \arg      QSPI_TMRALM_TCFG_FLAG
        \arg      QSPI_TMRALM_FLUSH_FLAG
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus qspi_tmr_alarm_status_get(uint32_t tmr_alarm)
{
    FlagStatus reval = RESET;
    uint32_t tmralm;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_QSPI_TMRALARM_STATUS(tmr_alarm)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0027U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* read current TMR register value */
        tmralm = QSPI_TMR;

        /* check if the specified alarm flag is set */
        if((uint32_t)RESET != (tmralm & tmr_alarm)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear QSPI TMR alarm status (API_ID: 0x0028U)
    \param[in]  tmr_alarm: tmr alarm status
                one or more parameters can be selected which are shown as below:
        \arg      QSPI_TMRALM_CTL_FLAG
        \arg      QSPI_TMRALM_DTLEN_FLAG
        \arg      QSPI_TMRALM_TCFG_FLAG
        \arg      QSPI_TMRALM_FLUSH_FLAG
    \param[out] none
    \retval     none
*/
void qspi_tmr_alarm_status_clear(uint32_t tmr_alarm)
{
    uint32_t tmralm;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_QSPI_TMRALARM_STATUS_CLEAR(tmr_alarm)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0028U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* read current TMR register value */
        tmralm = QSPI_TMR;
        
        /* set the specified alarm bits to clear status flags */
        tmralm |= tmr_alarm;
        
        /* write back to TMR register */
        QSPI_TMR = tmralm;
    }
}

/*!
    \brief      enable QSPI TMR alarm (API_ID: 0x0029U)
    \param[in]  tmr_alarm: tmr alarm mask
                one or more parameters can be selected which are shown as below:
        \arg      QSPI_TMRALM_CTL
        \arg      QSPI_TMRALM_DTLEN
        \arg      QSPI_TMRALM_TCFG
        \arg      QSPI_TMRALM_FLUSH
    \param[out] none
    \retval     none
*/
void qspi_tmr_alarm_enable(uint32_t tmr_alarm)
{
    uint32_t tmralm;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_QSPI_TMRALARM_EN(tmr_alarm)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x0029U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* read current TMR register value */
        tmralm = QSPI_TMR;
        tmralm &= ~(QSPI_TMR_ST0 | QSPI_TMR_ST1 | QSPI_TMR_ST2 | QSPI_TMR_ST3);
        
        /* enable the specified TMR alarms by setting their bits */
        tmralm |= tmr_alarm;
        
        /* write back to TMR register */
        QSPI_TMR = tmralm;
    }
}

/*!
    \brief      disable QSPI TMR alarm (API_ID: 0x002AU)
    \param[in]  tmr_alarm: tmr alarm mask
                one or more parameters can be selected which are shown as below:
        \arg      QSPI_TMRALM_CTL
        \arg      QSPI_TMRALM_DTLEN
        \arg      QSPI_TMRALM_TCFG
        \arg      QSPI_TMRALM_FLUSH
    \param[out] none
    \retval     none
*/
void qspi_tmr_alarm_disable(uint32_t tmr_alarm)
{
    uint32_t tmralm;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_QSPI_TMRALARM_EN(tmr_alarm)) {
        fw_debug_report_err(QSPI_MODULE_ID, API_ID(0x002AU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* read current TMR register value */
        tmralm = QSPI_TMR;
        tmralm &= ~(QSPI_TMR_ST0 | QSPI_TMR_ST1 | QSPI_TMR_ST2 | QSPI_TMR_ST3);
        
        /* disable the specified TMR alarms by clearing their bits */
        tmralm &= ~tmr_alarm;
        
        /* write back to TMR register */
        QSPI_TMR = tmralm;
    }
}
