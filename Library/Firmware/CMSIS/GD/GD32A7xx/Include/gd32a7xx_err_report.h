/*!
    \file    gd32a7xx_report_err.h
    \brief   Reporting Error driver

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
#ifndef ERR_REPORT_H
#define ERR_REPORT_H

#include <stdint.h>

/* define the size of the error report buffer */
#define ERR_REPORT_BUFFER_SIZE          2U

/* define the unique identifier of peripherals */
#define SYSCFG_MODULE_ID                                  ((uint8_t)0x01U)               /*!< SYSCFG module ID */
#define BUSIM_MODULE_ID                                   ((uint8_t)0x02U)               /*!< BUSIM module ID */
#define EXTMPU_MODULE_ID                                  ((uint8_t)0x03U)               /*!< EXTMPU module ID */
#define PRPU_MODULE_ID                                    ((uint8_t)0x04U)               /*!< PRPU module ID */
#define IMICU_MODULE_ID                                   ((uint8_t)0x05U)               /*!< IMICU module ID */
#define SRAM_TCM_MODULE_ID                                ((uint8_t)0x06U)               /*!< SRAM and TCM module ID */
#define FMC_MODULE_ID                                     ((uint8_t)0x07U)               /*!< FMC module ID */
#define PMU_MODULE_ID                                     ((uint8_t)0x08U)               /*!< PMU module ID */
#define BKP_MODULE_ID                                     ((uint8_t)0x09U)               /*!< BKP module ID */
#define RCU_MODULE_ID                                     ((uint8_t)0x0AU)               /*!< RCU module ID */
#define EXTI_MODULE_ID                                    ((uint8_t)0x0BU)               /*!< EXTI module ID */
#define TRIGSEL_MODULE_ID                                 ((uint8_t)0x0CU)               /*!< TRIGSEL module ID */
#define GPIO_MODULE_ID                                    ((uint8_t)0x0DU)               /*!< GPIO module ID */
#define MFCOM_MODULE_ID                                   ((uint8_t)0x0EU)               /*!< MFCOM module ID */
#define CRC_MODULE_ID                                     ((uint8_t)0x0FU)               /*!< CRC module ID */
#define DMA_DMAMUX_MODULE_ID                              ((uint8_t)0x10U)               /*!< DMA and DMAMUX module ID */
#define DBG_MODULE_ID                                     ((uint8_t)0x11U)               /*!< DBG module ID */
#define ADC_MODULE_ID                                     ((uint8_t)0x12U)               /*!< ADC module ID */
#define DAC_MODULE_ID                                     ((uint8_t)0x13U)               /*!< DAC module ID */
#define FWDGT_MODULE_ID                                   ((uint8_t)0x14U)               /*!< FWDGT module ID */
#define WWDGT_MODULE_ID                                   ((uint8_t)0x15U)               /*!< WWDGT module ID */
#define RTC_MODULE_ID                                     ((uint8_t)0x16U)               /*!< RTC module ID */
#define TIMER_MODULE_ID                                   ((uint8_t)0x17U)               /*!< TIMER module ID */
#define LINFLEXD_UART_MODULE_ID                           ((uint8_t)0x18U)               /*!< USART module ID */
#define LIN_MODULE_ID                                     ((uint8_t)0x19U)               /*!< LIN module ID */
#define I2C_MODULE_ID                                     ((uint8_t)0x1AU)               /*!< I2C module ID */
#define SPI_MODULE_ID                                     ((uint8_t)0x1BU)               /*!< SPI module ID */
#define QSPI_MODULE_ID                                    ((uint8_t)0x1CU)               /*!< QSPI module ID */
#define CAN_MODULE_ID                                     ((uint8_t)0x1DU)               /*!< CAN module ID */
#define SENT_MODULE_ID                                    ((uint8_t)0x1EU)               /*!< SENT module ID */
#define ENET_MODULE_ID                                    ((uint8_t)0x1FU)               /*!< ENET module ID */
#define CMP_MODULE_ID                                     ((uint8_t)0x20U)               /*!< CMP module ID */
#define HWSEM_MODULE_ID                                   ((uint8_t)0x21U)               /*!< HWSEM module ID */
#define MCMU_MODULE_ID                                    ((uint8_t)0x22U)               /*!< MCMU module ID */
#define STCM_MODULE_ID                                    ((uint8_t)0x23U)               /*!< STCM module ID */
#define MTC_MODULE_ID                                     ((uint8_t)0x24U)               /*!< MTC module ID */
#define IRM_MODULE_ID                                     ((uint8_t)0x25U)               /*!< IRM module ID */
#define IOC_MODULE_ID                                     ((uint8_t)0x26U)               /*!< IOC module ID */
#define CLTCFG_MODULE_ID                                  ((uint8_t)0x27U)               /*!< CLTCFG module ID */
#define FMU_MODULE_ID                                     ((uint8_t)0x28U)               /*!< FMU module ID */
#define GD_AP_MODULE_ID                                   ((uint8_t)0x29U)              /*!< GD_AP module ID */
#define MISC_MODULE_ID                                    ((uint8_t)0x2AU)               /*!< MISC module ID */
#define HSMIF_MODULE_ID                                   ((uint8_t)0x2BU)               /*!< HSM HSMIF module ID */
#define JDC_MODULE_ID                                     ((uint8_t)0x2CU)               /*!< JDC module ID */

/* define the unique identifier of error type */
#define ERR_PERIPH                                        ((uint8_t)0x01U)               /*!< peripheral error */
#define ERR_PARAM_POINTER                                 ((uint8_t)0x02U)               /*!< invalid pointer */
#define ERR_PARAM_OUT_OF_RANGE                            ((uint8_t)0x03U)               /*!< out of range */
#define ERR_PARAM_INVALID                                 ((uint8_t)0x04U)               /*!< invalid parameter */

/* define the unique identifier of API */
#define API_ID(x)                                         ((uint16_t)(x))               /*!< API ID */

/* definitions for parameter checking */
#define NOT_VALID_POINTER(x)                              ((void *) 0 == (x))           /*!< check the invalid pointer */

/* defining the structure to store the parameters of Report Error function */
typedef struct {
    /* module ID where the error occurred */
    uint16_t moduleid;
    /* API ID associated with the error */
    uint16_t apiid;
    /* error ID indicating the specific error type */
    uint8_t errid;
} err_report_struct;

/* declare external arrays and variables for error reporting */
extern err_report_struct err_report_buffer[ERR_REPORT_BUFFER_SIZE];
/* index to track the next available position in the error report buffer */
extern uint8_t err_report_buff_index;

/* reporting errors in debug mode */
void fw_debug_report_err(uint16_t moduleid, uint16_t apiid, uint8_t errid);

#endif /* ERR_REPORT_H */
