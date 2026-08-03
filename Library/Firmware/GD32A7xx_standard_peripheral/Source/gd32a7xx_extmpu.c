/*!
    \file    gd32a7xx_extmpu.c
    \brief   SYSCFG driver

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

#include "gd32a7xx_extmpu.h"

/*!
    \brief      enable EXTMPU, API ID: 0x0001
    \param[in]  none
    \param[out] none
    \retval     none
*/
void extmpu_enable(void)
{
    /* MERRF will be clear by write 1 */
    EXTMPU_CS0 = EXTMPU_CS0_EXTMPUEN;
}

/*!
    \brief      disable EXTMPU, API ID: 0x0002
    \param[in]  none
    \param[out] none
    \retval     none
*/
void extmpu_disable(void)
{
    EXTMPU_CS0 = 0U;
}

/*!
    \brief      enable EXTMPU region, API ID: 0x0003
    \param[in]  region: specify the region number
                only one parameter can be selected which is shown as below:
      \arg        EXTMPU_REGIONx, (x=0,..,31)
    \param[out] none
    \retval     none
*/
void extmpu_region_enable(uint8_t region)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTMPU_REGION(region)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(3), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        EXTMPU_CTL3(region) |= EXTMPU_CTL3_RVD;
    }
}

/*!
    \brief      disable EXTMPU region, API ID: 0x0004
    \param[in]  region: specify the region number
                only one parameter can be selected which is shown as below:
      \arg        EXTMPU_REGIONx, (x=0,..,31)
    \param[out] none
    \retval     none
*/
void extmpu_region_disable(uint8_t region)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTMPU_REGION(region)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(4), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        EXTMPU_CTL3(region) &= ~EXTMPU_CTL3_RVD;
    }
}

/*!
    \brief      lock EXTMPU control register 0~3 of specific region, API ID: 0x0005
    \param[in]  region: specify the region number
                only one parameter can be selected which is shown as below:
      \arg        EXTMPU_REGIONx, (x=0,..,31)
    \param[out] none
    \retval     none
*/
void extmpu_region_reg_lock(uint8_t region)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTMPU_REGION(region)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(5), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        EXTMPU_CTL3(region) |= EXTMPU_CTL3_RROEN;
    }
}

/*!
    \brief      configure region start address, size and permission, API ID: 0x0006
    \param[in]  region: specify the region number
                only one parameter can be selected which is shown as below:
      \arg        EXTMPU_REGIONx, (x=0,..,31)
    \param[in]  startaddress: specify the start address of the region, must be a multiple of 128 bytes
    \param[in]  size: specify the size of the region, must be a multiple of 128 bytes
    \param[in]  allpermission: specify the permission of all master
    \param[out] none
    \retval     none
*/
void extmpu_region_config(uint8_t region, uint32_t startaddress, uint32_t size, uint32_t allpermission)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTMPU_REGION(region)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(6), ERR_PARAM_INVALID);
    } else if((0U != (startaddress % 128U)) || (0U == startaddress)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(6), ERR_PARAM_OUT_OF_RANGE);
    } else if((0U != (size % 128U)) || (0U == size)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(6), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        EXTMPU_CTL0(region) = startaddress;
        EXTMPU_CTL1(region) = startaddress + size - 1U;
        EXTMPU_CTL2(region) = allpermission;
    }
}

/*!
    \brief      configure region access permission, API ID: 0x0007
    \param[in]  region: specify the region number
                only one parameter can be selected which is shown as below:
      \arg        EXTMPU_REGIONx, (x=0,..,31)
    \param[in]  master_port: specify the master port, 0~5,7,10~12,14
                only one parameter can be selected which is shown as below:
      \arg        MASTER_PORTx, (x=0~5,7,10~12,14)
    \param[in]  permission: specify the permission
                only one parameter can be selected which is shown as below:
      \arg        EXTMPU_ACCESS_FORBIDDEN: access permission forbidden 
      \arg        EXTMPU_ACCESS_READONLY: access permission read only 
      \arg        EXTMPU_ACCESS_WRITEONLY: access permission write only
      \arg        EXTMPU_ACCESS_READWRITE: access permission read write
    \param[out] none
    \retval     none
*/
void extmpu_region_access_permission_config(uint8_t region, uint8_t master_port, uint8_t permission)
{
    uint32_t temp = EXTMPU_CTL2(region);
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTMPU_REGION(region)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(7), ERR_PARAM_INVALID);
    } else if(NOT_EXTMPU_MASTER_PORT(master_port)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(7), ERR_PARAM_INVALID);
    } else if(NOT_EXTMPU_ACCESS_PERMISSION(permission)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(7), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp &= ~(EXTMPU_CTL2_M0AP << ((uint32_t)master_port * 2U));
        temp |= (uint32_t)((uint32_t)permission << ((uint32_t)master_port * 2U));
        EXTMPU_CTL2(region) = temp;
    }
}

/*!
    \brief      get EXTMPU error status, API ID: 0x0008
    \param[in]  none
    \param[out] status
    \retval     the error state returned (SET or RESET)
*/
FlagStatus extmpu_error_status_get(extmpu_error_status *status)
{
    uint32_t master_position = 32U - (uint32_t)__CLZ(EXTMPU_CS0 & EXTMPU_CS0_MERRF);
    FlagStatus retval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(status)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(8), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(master_position == 0U) {
            retval = RESET;
        } else {
            uint32_t einf = EXTMPU_EINF(master_position - 1U);
            uint32_t ergn = EXTMPU_EREG(master_position - 1U);
            status->master = master_position - 1U;
            status->error_address = EXTMPU_EADDR(status->master);
            status->error_type = (einf & EXTMPU_EINF_EATYPE) >> 27U;
            status->error_detail = (einf & 0x06000000U) >> 25U;
            status->region = 32U - (uint32_t)__CLZ(ergn);
            if(status->region == 0U) {
                /* error address not mapped to any region */
                status->region = 0xFFFFFFFFU;
            } else {
                status->region--;
            }
            retval = SET;
        }
    }
    return retval;
}

/*!
    \brief      get EXTMPU overrun flag, API ID: 0x0009
    \param[in]  master_id
                only one parameter can be selected which is shown as below:
      \arg        MASTER_IDx (x=0,1,2,3,4,5,7,10,11,12,14)
    \param[out] none
    \retval     the error state returned (SET or RESET)
*/
FlagStatus extmpu_overrun_flag_get(uint32_t master_id)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTMPU_MASTER_ID(master_id)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(9), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (EXTMPU_CS1 & master_id)) {
            reval = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return reval;
}

/*!
    \brief      clear EXTMPU overrun flag, API ID: 0x000A
    \param[in]  master_id
                only one parameter can be selected which is shown as below:
      \arg        MASTER_IDx (x=0,1,2,3,4,5,7,10,11,12,14)
    \param[out] none
    \retval     none
*/
void extmpu_error_overrun_flag_clear(uint32_t master_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTMPU_MASTER_ID(master_id)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(10), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        EXTMPU_CS0 |= master_id;
    }
}

/*!
    \brief      clear EXTMPU error region information, API ID: 0x000B
    \param[in]  master_id
                only one parameter can be selected which is shown as below:
      \arg        MASTER_IDx (x=0,1,2,3,4,5,7,10,11,12,14)
    \param[out] none
    \retval     none
*/
void extmpu_error_region_info_clear(uint32_t master_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_EXTMPU_MASTER_ID(master_id)) {
        fw_debug_report_err(EXTMPU_MODULE_ID, API_ID(11), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        EXTMPU_CS0 |= master_id;
    }
}
