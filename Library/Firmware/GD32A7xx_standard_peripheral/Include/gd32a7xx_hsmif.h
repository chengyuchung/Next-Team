/*!
    \file    gd32a7xx_hsm_hsmif.h
    \brief   definitions for the HSM_HSMIF

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

#ifndef GD32A7XX_HSM_HSMIF_H
#define GD32A7XX_HSM_HSMIF_H

#include "gd32a7xx.h"

/* HSM_RCU definitions */
#define HSMIF                       HSMIF_BASE                                  /*!< HSMIF base address */

/* registers definitions */
#define HSMIF_ID                    REG32(HSMIF + 0x00000000U)                  /*!< identifier register */
#define HSMIF_HTIDCTL               REG32(HSMIF + 0x00000004U)                  /*!< Host identifier control register */
#define HSMIF_HTIR0                 REG32(HSMIF + 0x00000010U)                  /*!< Host interrupt request register0 */
#define HSMIF_HTIR1                 REG32(HSMIF + 0x00000018U)                  /*!< Host interrupt request register1 */
#define HSMIF_HSMIR                 REG32(HSMIF + 0x00000020U)                  /*!< HSM interrupt request register */
#define HSMIF_HSMINTEN              REG32(HSMIF + 0x00000024U)                  /*!< HSM interrupt enable register */
#define HSMIF_HSMINTSEL             REG32(HSMIF + 0x00000028U)                  /*!< HSM interrupt select register */
#define HSMIF_HSMSTAT               REG32(HSMIF + 0x00000040U)                  /*!< HSM status register */
#define HSMIF_HTSTAT                REG32(HSMIF + 0x00000048U)                  /*!< Host status register */
#define HSMIF_SYSCTL                REG32(HSMIF + 0x000000A0U)                  /*!< System control register */
#define HSMIF_SYSSTAT               REG32(HSMIF + 0x000000A4U)                  /*!< System status register */
#define HSMIF_IRMINTF(x)            REG32(HSMIF + 0x000000B0U + 0x04U * (x))    /*!< IRM interrupt flag register x */

/* bits definitions */
/* HSMIF_ID */
#define HSMIF_ID_NUMVAL             BITS(16, 31)             /*!< the value of the ID number */
#define HSMIF_ID_TYPVAL             BITS(8, 15)              /*!< the value of the type */
#define HSMIF_ID_REVNUMVAL          BITS(0, 7)               /*!< the value of the type revision number */

/* HSMIF_HTIDCTL */
#define HSMIF_HTIDCTL_HTIDEN        BIT(31)                  /*!< Host ID enable */
#define HSMIF_HTIDCTL_IR1ID         BITS(4, 7)               /*!< interrupt request 1 ID */
#define HSMIF_HTIDCTL_IR0ID         BITS(0, 3)               /*!< interrupt request 1 ID */

/* HSMIF_HTIR0 */
#define HSMIF_HTIR0_INTRF           BITS(0, 31)              /*!< interrupt request flag by Host0 to HSM */

/* HSMIF_HTIR1 */
#define HSMIF_HTIR1_INTRF           BITS(0, 31)              /*!< interrupt request flag by Host1 to HSM */

/* HSMIF_HSMIR */
#define HSHIF_HSMIR_INTRF           BITS(0, 31)              /*!< interrupt request flag by HSM to Host */

/* HSMIF_HSMINTEN */
#define HSMIF_HSMINTEN_IE           BITS(0, 31)              /*!< interrupt enable by HSM to Host */

/* HSMIF_HSMINTSEL */
#define HSMIF_HSMINTSEL_IS          BITS(0, 31)              /*!< interrupt select */

/* HSMIF_HSMSTAT */
#define HSMIF_HSMSTAT_STAT          BITS(0, 31)              /*!< HSM status */

/* HSMIF_HTSTAT */
#define HSMIF_HTSTAT_STAT           BITS(0, 31)              /*!< Host status */

/* HSMIF_SYSCTL */
#define HSMIF_SYSCTL_HWDT               BIT(30)              /*!< HSM 1:1/1:2 widget */
#define HSMIF_SYSCTL_CKDIV              BIT(31)              /*!< clock division */

/* HSMIF_SYSSTAT */
#define HSMIF_SYSSTAT_BS                BIT(8)               /*!< Boot success flag */
#define HSMIF_SYSSTAT_BF                BIT(9)               /*!< Boot failure flag */
#define HSMIF_SYSSTAT_LBS               BIT(10)              /*!< Last boot success flag */
#define HSMIF_SYSSTAT_LBF               BIT(11)              /*!< Last boot failure flag */
#define HSMIF_SYSSTAT_HSMRNUM           BITS(16, 20)         /*!< the number of HSM has performed software recovery */
#define HSMIF_SYSSTAT_HTRNUM            BITS(24, 28)         /*!< the number of Host has performed software recovery */

/* HSMIF_IRMINTF */
#define HSMIF_IRMINTF_IRMIF(x)          BIT(x)               /*!< IRM interrupt flag */

/* structure of ID related configuration */
typedef struct {
    uint32_t numval;                                         /*!< the value of the ID number */
    uint32_t typval;                                         /*!< the value of the type */
    uint32_t revnumval;                                      /*!< the value of the type revision number */
} hsmif_id_struct;

/* clock division definition */
typedef enum {
    CLOCK_DIV_2                         = 0U,                /*!< hsm clock divid 2 from system clock */
    CLOCK_DIV_1                         = 1U                 /*!< hsm clock divid 1 from system clock */
} hsmif_clk_div_enum;

/* constants definitions */
/* HSMIF_ID register bit definitions */
#define HSMIF_MASTER_ID_CM7_0           ((uint8_t)0x0EU)               /*!< Host 0 ID */
#define HSMIF_MASTER_ID_CM7_1           ((uint8_t)0x07U)               /*!< Host 1 ID */

/* interrupt request definitions */
#define INT_REQ_HOST_0                  ((uint8_t)0x00U)               /*!< interrupt request from Host 0 */
#define INT_REQ_HOST_1                  ((uint8_t)0x01U)               /*!< interrupt request from Host 1 */
#define HOST_INT_LINE_0                 ((uint8_t)0x00U)               /*!< Host interrupt 0 line */
#define HOST_INT_LINE_1                 ((uint8_t)0x01U)               /*!< Host interrupt 1 line */

/* interrupt request definitions */
#define HSMIF_INT_REQ_0                 BIT(0)                          /*!< interrupt request 0 */
#define HSMIF_INT_REQ_1                 BIT(1)                          /*!< interrupt request 1 */
#define HSMIF_INT_REQ_2                 BIT(2)                          /*!< interrupt request 2 */
#define HSMIF_INT_REQ_3                 BIT(3)                          /*!< interrupt request 3 */
#define HSMIF_INT_REQ_4                 BIT(4)                          /*!< interrupt request 4 */
#define HSMIF_INT_REQ_5                 BIT(5)                          /*!< interrupt request 5 */
#define HSMIF_INT_REQ_6                 BIT(6)                          /*!< interrupt request 6 */
#define HSMIF_INT_REQ_7                 BIT(7)                          /*!< interrupt request 7 */
#define HSMIF_INT_REQ_8                 BIT(8)                          /*!< interrupt request 8 */
#define HSMIF_INT_REQ_9                 BIT(9)                          /*!< interrupt request 9 */
#define HSMIF_INT_REQ_10                BIT(10)                         /*!< interrupt request 10 */
#define HSMIF_INT_REQ_11                BIT(11)                         /*!< interrupt request 11 */
#define HSMIF_INT_REQ_12                BIT(12)                         /*!< interrupt request 12 */
#define HSMIF_INT_REQ_13                BIT(13)                         /*!< interrupt request 13 */
#define HSMIF_INT_REQ_14                BIT(14)                         /*!< interrupt request 14 */
#define HSMIF_INT_REQ_15                BIT(15)                         /*!< interrupt request 15 */
#define HSMIF_INT_REQ_16                BIT(16)                         /*!< interrupt request 16 */
#define HSMIF_INT_REQ_17                BIT(17)                         /*!< interrupt request 17 */
#define HSMIF_INT_REQ_18                BIT(18)                         /*!< interrupt request 18 */
#define HSMIF_INT_REQ_19                BIT(19)                         /*!< interrupt request 19 */
#define HSMIF_INT_REQ_20                BIT(20)                         /*!< interrupt request 20 */
#define HSMIF_INT_REQ_21                BIT(21)                         /*!< interrupt request 21 */
#define HSMIF_INT_REQ_22                BIT(22)                         /*!< interrupt request 22 */
#define HSMIF_INT_REQ_23                BIT(23)                         /*!< interrupt request 23 */
#define HSMIF_INT_REQ_24                BIT(24)                         /*!< interrupt request 24 */
#define HSMIF_INT_REQ_25                BIT(25)                         /*!< interrupt request 25 */
#define HSMIF_INT_REQ_26                BIT(26)                         /*!< interrupt request 26 */
#define HSMIF_INT_REQ_27                BIT(27)                         /*!< interrupt request 27 */
#define HSMIF_INT_REQ_28                BIT(28)                         /*!< interrupt request 28 */
#define HSMIF_INT_REQ_29                BIT(29)                         /*!< interrupt request 29 */
#define HSMIF_INT_REQ_30                BIT(30)                         /*!< interrupt request 30 */
#define HSMIF_INT_REQ_31                BIT(31)                         /*!< interrupt request 31 */

/* software recovery bit definitions */
#define HSM_RECOVERY_COUNTER            HSMIF_SYSSTAT_HSMRNUM           /*!< the number of HSM has performed software recovery */
#define HOST_RECOVERY_COUNTER           HSMIF_SYSSTAT_HTRNUM            /*!< the number of Host has performed software recovery */

/* system boot related definitions */
#define HSMIF_SYSSTAT_BOOTOK            HSMIF_SYSSTAT_BS                /*!< Boot success flag */
#define HSMIF_SYSSTAT_BOOTFAIL          HSMIF_SYSSTAT_BF                /*!< Boot failure flag */
#define HSMIF_SYSSTAT_LBOOTOK           HSMIF_SYSSTAT_LBS               /*!< Last boot success flag */
#define HSMIF_SYSSTAT_LBOOTFAIL         HSMIF_SYSSTAT_LBF               /*!< Last boot failure flag */

/* IRM group and interrupt definitions */
#define HSMIF_IRM_GROUP0        ((uint32_t)0x00000000U)                 /*!< IRM group 0 */
#define HSMIF_IRM_GROUP1        ((uint32_t)0x00000001U)                 /*!< IRM group 1 */
#define HSMIF_IRM_GROUP2        ((uint32_t)0x00000002U)                 /*!< IRM group 2 */
#define HSMIF_IRM_GROUP3        ((uint32_t)0x00000003U)                 /*!< IRM group 3 */
#define HSMIF_IRM_GROUP4        ((uint32_t)0x00000004U)                 /*!< IRM group 4 */
#define HSMIF_IRM_GROUP5        ((uint32_t)0x00000005U)                 /*!< IRM group 5 */
#define HSMIF_IRM_GROUP6        ((uint32_t)0x00000006U)                 /*!< IRM group 6 */
#define HSMIF_IRM_GROUP7        ((uint32_t)0x00000007U)                 /*!< IRM group 7 */
#define HSMIF_IRM_INTF(x)       BIT(x)                                  /*!< IRM interrupt flag x */

/* system control definitions */
#define HSMIF_WIDGET_ENABLE     ((uint32_t)0x00000000U)                 /*!< HSM 1:1/1:2 widget is enable */
#define HSMIF_WIDGET_DISABLE    HSMIF_SYSCTL_HWDT                       /*!< HSM 1:1/1:2 widget is siasble */
#define HSMIF_SYSCLK_DIV_2      ((uint32_t)0x00000000U)                 /*!< the clock division is 2 */
#define HSMIF_SYSCLK_DIV_1      HSMIF_SYSCTL_CKDIV                      /*!< the clock division is 1 */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check HOST ID */
#define NOT_HSMIF_HOSTID(host_id)                        (((host_id) != HSMIF_MASTER_ID_CM7_0) && ((host_id) != HSMIF_MASTER_ID_CM7_1))

/* check hsm boot state */
#define NOT_HSMIF_BOOT_STATE(state)                      (((state) != HSMIF_SYSSTAT_BOOTOK) && ((state) != HSMIF_SYSSTAT_BOOTFAIL) && \
                                                         ((state) != HSMIF_SYSSTAT_LBOOTOK)  && ((state) != HSMIF_SYSSTAT_LBOOTFAIL))
                                                         
/* check recovery mode counter */
#define NOT_HSMIF_COUNTER(recovery_counter)              (((recovery_counter) != HSM_RECOVERY_COUNTER) && ((recovery_counter) != HOST_RECOVERY_COUNTER))

/* check HOST interrupt request */
#define NOT_HSMIF_HOST_INT_REQ(host_req)                 (((host_req) != INT_REQ_HOST_0) && ((host_req) != INT_REQ_HOST_1))


/* check HOST interrupt line */
#define NOT_HSMIF_HOST_INT_LINE(host_line)               (((host_line) != HOST_INT_LINE_0) && ((host_line) != HOST_INT_LINE_1))

/* check host interrupt request */
#define NOT_HSMIF_HOST_INT_REQ_FACTOR(request_factor)              (((request_factor) != HSMIF_INT_REQ_0)  && ((request_factor) != HSMIF_INT_REQ_1) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_2) && ((request_factor) != HSMIF_INT_REQ_3) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_4) && ((request_factor) != HSMIF_INT_REQ_5) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_6) && ((request_factor) != HSMIF_INT_REQ_7) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_8) && ((request_factor) != HSMIF_INT_REQ_9) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_10) && ((request_factor) != HSMIF_INT_REQ_11) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_12) && ((request_factor) != HSMIF_INT_REQ_13) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_14) && ((request_factor) != HSMIF_INT_REQ_15) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_16) && ((request_factor) != HSMIF_INT_REQ_17) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_18) && ((request_factor) != HSMIF_INT_REQ_19) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_20) && ((request_factor) != HSMIF_INT_REQ_21) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_22) && ((request_factor) != HSMIF_INT_REQ_23) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_24) && ((request_factor) != HSMIF_INT_REQ_25) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_26) && ((request_factor) != HSMIF_INT_REQ_27) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_28) && ((request_factor) != HSMIF_INT_REQ_29) && \
                                                                   ((request_factor) != HSMIF_INT_REQ_30) && ((request_factor) != HSMIF_INT_REQ_31))

/* check IRM group */
#define NOT_HSMIF_IRM_GROUP(irm_group)                             (((irm_group) != HSMIF_IRM_GROUP0)  && ((irm_group) != HSMIF_IRM_GROUP1) && \
                                                                   ((irm_group) != HSMIF_IRM_GROUP2) && ((irm_group) != HSMIF_IRM_GROUP3) && \
                                                                   ((irm_group) != HSMIF_IRM_GROUP4) && ((irm_group) != HSMIF_IRM_GROUP5) && \
                                                                   ((irm_group) != HSMIF_IRM_GROUP6) && ((irm_group) != HSMIF_IRM_GROUP7))

/* check IRM interrupt flag factor */
#define NOT_HSMIF_IRM_INT_FLAG_FACTOR(irm_flag)                   (((irm_flag) != HSMIF_IRM_INTF(0))  && ((irm_flag) != HSMIF_IRM_INTF(1)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(2)) && ((irm_flag) != HSMIF_IRM_INTF(3)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(4)) && ((irm_flag) != HSMIF_IRM_INTF(5)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(6)) && ((irm_flag) != HSMIF_IRM_INTF(7)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(8)) && ((irm_flag) != HSMIF_IRM_INTF(9)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(10)) && ((irm_flag) != HSMIF_IRM_INTF(11)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(12)) && ((irm_flag) != HSMIF_IRM_INTF(13)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(14)) && ((irm_flag) != HSMIF_IRM_INTF(15)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(16)) && ((irm_flag) != HSMIF_IRM_INTF(17)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(18)) && ((irm_flag) != HSMIF_IRM_INTF(19)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(20)) && ((irm_flag) != HSMIF_IRM_INTF(21)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(22)) && ((irm_flag) != HSMIF_IRM_INTF(23)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(24)) && ((irm_flag) != HSMIF_IRM_INTF(25)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(26)) && ((irm_flag) != HSMIF_IRM_INTF(27)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(28)) && ((irm_flag) != HSMIF_IRM_INTF(29)) && \
                                                                   ((irm_flag) != HSMIF_IRM_INTF(30)) && ((irm_flag) != HSMIF_IRM_INTF(31)))

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* communication function */
/* hsmif deinit */
void hsmif_deinit(void);
/* get hsmif module related ID */
void hsmif_id_get(hsmif_id_struct *hsmif_id);
/* get Host filter ID */
ControlStatus hsmif_host_filter_get(uint8_t* host_id_0, uint8_t* host_id_1);
/* set host status value*/
void hsmif_host_status_set(uint32_t status);
/* get hsm status value */
uint32_t hsmif_hsm_status_get(void);
/* get host status value */
uint32_t hsmif_host_status_get(void);


/* system control configuration */
/* get hsm clock division */
hsmif_clk_div_enum hsmif_clock_div_get(void);
/* get HSM 1:1/1:2 widget state */
ControlStatus hsmif_clock_widget_get(void);
/* check hsm boot state */
FlagStatus hsmif_boot_state_get(uint32_t state);
/* get recovery mode counter of hsm system or host system */
uint32_t hsmif_recovery_mode_counter_get(uint32_t recovery_counter);

/* interrupt & flag functions */
/* host to hsm interrupt */
/* get host to hsm interrupt request flag */
FlagStatus hsmif_host2hsm_interrupt_request_get(uint32_t host, uint32_t request);
/* set host to hsm interrupt request flag */
void hsmif_host2hsm_interrupt_request_set(uint32_t host, uint32_t request);

/* hsm to host interrupt */
/* enable hsm to host interrupt request */
void hsmif_hsm2host_interrupt_request_enable(uint32_t request);
/* disable hsm to host interrupt request */
void hsmif_hsm2host_interrupt_request_disable(uint32_t request);
/* hsm to host interrupt mapping */
void hsmif_hsm2host_interrupt_select(uint32_t host_int_line, uint32_t request);
/* get hsm to host interrupt request flag */
FlagStatus hsmif_hsm2host_interrupt_request_get(uint32_t request);
/* clear hsm to host interrupt request flag */
void hsmif_hsm2host_interrupt_request_clear(uint32_t request);


/* irm interrupt */
/* get irm interrupt flag status */
FlagStatus hsmif_irm_interrupt_flag_get(uint32_t irm_group, uint32_t irm_flag);

#endif /* GD32A7XX_HSM_HSMIF_H */
