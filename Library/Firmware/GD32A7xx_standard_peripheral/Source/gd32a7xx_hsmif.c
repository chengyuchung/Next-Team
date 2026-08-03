/*!
    \file    gd32a7xx_hsm_hsmif.c
    \brief   HSMIF driver

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

#include "gd32a7xx_hsmif.h"

#define HSM_RECOVERY_COUNGER_OFF    ((uint8_t)0x10U)
#define HOST_RECOVERY_COUNGER_OFF   ((uint8_t)0x18U)
#define RECOVERY_MODE_COUNTER_MAX   ((uint32_t)0x1FU)
#define HSMIF_REG_RESET_VALUE        ((uint32_t)0x00000000U)

/*!
    \brief      hsmif deinit
    \param[in]  none
    \param[out] none
    \retval     none
*/
void hsmif_deinit(void)
{
    HSMIF_HSMINTEN = HSMIF_REG_RESET_VALUE;
    HSMIF_HSMINTSEL = HSMIF_REG_RESET_VALUE;
    HSMIF_HTSTAT = HSMIF_REG_RESET_VALUE;
    rcu_periph_reset_enable(RCU_HSMIFRST);
    rcu_periph_reset_disable(RCU_HSMIFRST);
}

/*!
    \brief      get hsmif module related ID
    \param[in]  none
    \param[out] hsmif_id: hsmif module related ID
    \retval     none
*/
void hsmif_id_get(hsmif_id_struct *hsmif_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(hsmif_id)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        hsmif_id->numval = (uint32_t)(HSMIF_ID & HSMIF_ID_NUMVAL);
        hsmif_id->typval = (uint32_t)(HSMIF_ID & HSMIF_ID_TYPVAL);
        hsmif_id->revnumval = (uint32_t)(HSMIF_ID & HSMIF_ID_REVNUMVAL);
    }
}
/*!
    \brief      get host filter id
    \param[in]  none
    \param[out] host_id_0: host id for interrupt request 0
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_MASTER_ID_CM7_0
        \arg      HSMIF_MASTER_ID_CM7_1
    \param[out] host_id_1: host id for interrupt request 0
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_MASTER_ID_CM7_0
        \arg      HSMIF_MASTER_ID_CM7_1
    \retval     ControlStatus: ENABLE or DISABLE
*/
ControlStatus hsmif_host_filter_get(uint8_t *host_id_0, uint8_t *host_id_1)
{
    ControlStatus status = DISABLE;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(host_id_0)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else if(NOT_VALID_POINTER(host_id_1)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get host id for interrupt request */
        *host_id_0 = (uint8_t)(HSMIF_HTIDCTL & HSMIF_HTIDCTL_IR0ID);
        *host_id_1 = (uint8_t)((HSMIF_HTIDCTL & HSMIF_HTIDCTL_IR1ID) >> 4);

        /* get host ID enable status */
        if(0U != (HSMIF_HTIDCTL & HSMIF_HTIDCTL_HTIDEN)) {
            status = ENABLE;
        } else {
            status = DISABLE;
        }
    }
    return status;
}
/*!
    \brief      set host status
    \param[in]  status: host status
    \param[out] none
    \retval     none
*/
void hsmif_host_status_set(uint32_t status)
{
    HSMIF_HTSTAT &= ~HSMIF_HTSTAT_STAT;
    HSMIF_HTSTAT = status;
}

/*!
    \brief      get hsm status value
    \param[in]  none
    \param[out] none
    \retval     hsm status value
*/
uint32_t hsmif_hsm_status_get(void)
{
    return HSMIF_HSMSTAT;
}

/*!
    \brief      get host status value
    \param[in]  none
    \param[out] none
    \retval     host status value
*/
uint32_t hsmif_host_status_get(void)
{
    return HSMIF_HTSTAT;
}

/*!
    \brief      get hsm clock division
    \param[in]  none
    \param[out] none
    \retval     hsmif_clk_div_enum: frequency division
        \arg      CLOCK_DIV_1: hsm clock divid 1 from system clock
        \arg      CLOCK_DIV_2: hsm clock divid 2 from system clock
*/
hsmif_clk_div_enum hsmif_clock_div_get(void)
{
    hsmif_clk_div_enum clk_div;

    if(HSMIF_SYSCLK_DIV_1 == (uint32_t)(HSMIF_SYSCTL & HSMIF_SYSCTL_CKDIV)) {
        clk_div = CLOCK_DIV_1;
    } else {
        clk_div = CLOCK_DIV_2;
    }
    return clk_div;
}

/*!
    \brief      get HSM 1:1/1:2 widget state
    \param[in]  none
    \param[out] none
    \retval     ControlStatus: ENABLE or DISABLE
*/
ControlStatus hsmif_clock_widget_get(void)
{
    ControlStatus wid_state;

    if(HSMIF_WIDGET_DISABLE == (uint32_t)(HSMIF_SYSCTL & HSMIF_SYSCTL_HWDT)) {
        wid_state = DISABLE;
    } else {
        wid_state = ENABLE;
    }
    return wid_state;
}

/*!
    \brief      check hsm boot state
    \param[in]  state: boot state
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_SYSSTAT_BOOTOK: Boot success flag
        \arg      HSMIF_SYSSTAT_BOOTFAIL: Boot failure flag
        \arg      HSMIF_SYSSTAT_LBOOTOK: Last boot success flag
        \arg      HSMIF_SYSSTAT_LBOOTFAIL: Last boot failure flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hsmif_boot_state_get(uint32_t state)
{
    FlagStatus flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_BOOT_STATE(state)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (HSMIF_SYSSTAT & state)) {
            flag = SET;
        } else {
            flag = RESET;
        }
    }
    return flag;
}


/*!
    \brief      get recovery mode counter of hsm system or host system
    \param[in]  recovery_counter: recovery counter
                only one parameter can be selected which is shown as below:
        \arg      HSM_RECOVERY_COUNTER: the number of HSM has performed software recovery
        \arg      HOST_RECOVERY_COUNTER: the number of Host has performed software recovery
    \param[out] none
    \retval     recovery mode counter number
*/
uint32_t hsmif_recovery_mode_counter_get(uint32_t recovery_counter)
{
    uint32_t counter = 0;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_COUNTER(recovery_counter)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(HSM_RECOVERY_COUNTER == recovery_counter) {
            counter = (HSMIF_SYSSTAT & HSMIF_SYSSTAT_HSMRNUM) >> HSM_RECOVERY_COUNGER_OFF;
        } else {
            counter = (HSMIF_SYSSTAT & HSMIF_SYSSTAT_HTRNUM) >> HOST_RECOVERY_COUNGER_OFF;
        }
    }
    return counter;
}

/*!
    \brief      get host to hsm interrupt request flag
    \param[in]  host: host number
                only one parameter can be selected which is shown as below:
        \arg      INT_REQ_HOST_0: interrupt request from HOST0
        \arg      INT_REQ_HOST_1: interrupt request from HOST1
    \param[in]  request: interrupt request
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_INT_REQ_x(x = 0..31)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hsmif_host2hsm_interrupt_request_get(uint32_t host, uint32_t request)
{
    FlagStatus flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_HOST_INT_REQ(host)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else if(NOT_HSMIF_HOST_INT_REQ_FACTOR(request)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(host) {
        /* get host0 to hsm interrupt request flag */
        case INT_REQ_HOST_0:
            if(0U != (HSMIF_HTIR0 & request)) {
                flag = SET;
            } else {
                flag = RESET;
            }
            break;
        /* get host1 to hsm interrupt request flag */
        case INT_REQ_HOST_1:
            if(0U != (HSMIF_HTIR1 & request)) {
                flag = SET;
            } else {
                flag = RESET;
            }
            break;
        default:
            break;
        }
    }
    return flag;
}

/*!
    \brief      set host to hsm interrupt flag
    \param[in]  host: host number
                only one parameter can be selected which is shown as below:
        \arg      INT_REQ_HOST_0: interrupt request from HOST0
        \arg      INT_REQ_HOST_1: interrupt request from HOST1
    \param[in]  request: interrupt request
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_INT_REQ_x(x = 0..31)
    \param[out] none
    \retval     none
*/
void hsmif_host2hsm_interrupt_request_set(uint32_t host, uint32_t request)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_HOST_INT_REQ(host)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_HSMIF_HOST_INT_REQ_FACTOR(request)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(INT_REQ_HOST_0 == host) {
            HSMIF_HTIR0 = request;
        } else {
            HSMIF_HTIR1 = request;
        } 
    }
}

/*!
    \brief      enable hsm to host interrupt request
    \param[in]  request: interrupt request
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_INT_REQ_x(x = 0..31)
    \param[out] none
    \retval     none
*/
void hsmif_hsm2host_interrupt_request_enable(uint32_t request)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_HOST_INT_REQ_FACTOR(request)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HSMIF_HSMINTEN |= request;
    }
}

/*!
    \brief      disable hsm to host interrupt request
    \param[in]  request: interrupt request
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_INT_REQ_x(x = 0..31)
    \param[out] none
    \retval     none
*/
void hsmif_hsm2host_interrupt_request_disable(uint32_t request)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_HOST_INT_REQ_FACTOR(request)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HSMIF_HSMINTEN &= ~request;
    }
}
/*!
    \brief      hsm to host interrupt mapping
    \param[in]  host_int_line:
                only one parameter can be selected which is shown as below:
        \arg      HOST_INT_LINE_0: HOST interrupt 0 line
        \arg      HOST_INT_LINE_1: HOST interrupt 1 line
    \param[in]  request: interrupt request
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_INT_REQ_x(x = 0..31)
    \param[out] none
    \retval     none
*/
void hsmif_hsm2host_interrupt_select(uint32_t host_int_line, uint32_t request)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_HOST_INT_LINE(host_int_line)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else if(NOT_HSMIF_HOST_INT_REQ_FACTOR(request)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(HOST_INT_LINE_0 == host_int_line) {
            HSMIF_HSMINTSEL &= ~request;
        } else {
            HSMIF_HSMINTSEL |= request;
        }
    }
}
/*!
    \brief      get hsm to host interrupt request flag
    \param[in]  request: interrupt request
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_INT_REQ_x(x = 0..31)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hsmif_hsm2host_interrupt_request_get(uint32_t request)
{
    FlagStatus flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_HOST_INT_REQ_FACTOR(request)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (HSMIF_HSMIR & request)) {
            flag = SET;
        } else {
            flag = RESET;
        }
    }
    return flag;
}

/*!
    \brief      clear hsm to host interrupt request flag
    \param[in]  request: interrupt request
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_INT_REQ_x(x = 0..31)
    \param[out] none
    \retval     none
*/
void hsmif_hsm2host_interrupt_request_clear(uint32_t request)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_HOST_INT_REQ_FACTOR(request)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x0011U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HSMIF_HSMIR = request;
    }
}

/*!
    \brief      get irm interrupt flag status
    \param[in]  irm_group: IRM group
                only one parameter can be selected which is shown as below:
        \arg      HSMIF_IRM_GROUP0: IRM group 0
        \arg      HSMIF_IRM_GROUP1: IRM group 1
        \arg      HSMIF_IRM_GROUP2: IRM group 2
        \arg      HSMIF_IRM_GROUP3: IRM group 3
        \arg      HSMIF_IRM_GROUP4: IRM group 4
        \arg      HSMIF_IRM_GROUP5: IRM group 5
        \arg      HSMIF_IRM_GROUP6: IRM group 6
        \arg      HSMIF_IRM_GROUP7: IRM group 7
    \param[in]  irm_flag
        \arg      HSMIF_IRM_INTF(x)(x=0...31): IRM interrupt flag x
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hsmif_irm_interrupt_flag_get(uint32_t irm_group, uint32_t irm_flag)
{
    FlagStatus flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_HSMIF_IRM_GROUP(irm_group)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else if(NOT_HSMIF_IRM_INT_FLAG_FACTOR(irm_flag)) {
        fw_debug_report_err(HSMIF_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get IRM interrupt flag status */
        if(0U != (HSMIF_IRMINTF(irm_group) & irm_flag)) {
            flag = SET;
        }
    }
    return flag;
}
