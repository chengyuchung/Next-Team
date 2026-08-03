/*!
    \file    gd32a7xx_sram_tcm.c
    \brief   ADC driver

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

#include "gd32a7xx_sram_tcm.h"

/* SRAM register bit offset */
#define SRAM_BUFVLD_UBEADDRVLD_OFFSET       ((uint32_t)8U)        /*!< SRAM un-correctable bit error address offset */
#define SRAM_ECCCERR_SRAM1_ECCCDET_OFFSET   ((uint32_t)16U)       /*!< SRAM1 ecc code calculated with check error detected offset */

/* TCM register bit offset */
#define TCM_BUFVLD_UBEADDRVLD_OFFSET        ((uint32_t)26U)       /*!< TCM un-correctable bit error address offset */
#define TCM0_ECCCERR_D0TCM0_ECCCDET_OFFSET  ((uint32_t)16U)       /*!< D0TCM0 of CM7_0 ecc code calculated with check error detected offset */
#define TCM0_ECCCERR_D1TCM0_ECCCDET_OFFSET  ((uint32_t)24U)       /*!< D1TCM0 of CM7_0 ecc code calculated with check error detected offset */
#define TCM1_ECCCERR_D0TCM0_ECCCDET_OFFSET  ((uint32_t)16U)       /*!< D0TCM0 of CM7_1 ecc code calculated with check error detected offset */
#define TCM1_ECCCERR_D1TCM0_ECCCDET_OFFSET  ((uint32_t)24U)       /*!< D1TCM0 of CM7_1 ecc code calculated with check error detected offset */


/*!
    \brief      enable sram0/1 ecc error interrupt (API_ID: 0x0001U)
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        SRAM_INT_CORRECTABLE_ERROR           : SRAM single bit ecc error interrupt
      \arg        SRAM_INT_UNCORRECTABLE_ERROR         : SRAM double bit ecc error interrupt
      \arg        SRAM_INT_ADDRESS_BUFFER_OVERFLOW     : SRAM ecc error address buffer overflow interrupt
      \arg        SRAM_INT_CONTROLLER_REDUNDANCY_CHECK : SRAM controller redundancy check error interrupt
    \param[out] none
    \retval     none
*/
void sram_ecc_interrupt_enable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_INTERRUPT(interrupt)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(1U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SRAM_INTEN |= interrupt;
    }
}

/*!
    \brief      disable sram0/1 ecc error interrupt (API_ID: 0x0002U)
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        SRAM_INT_CORRECTABLE_ERROR           : SRAM single bit ecc error interrupt
      \arg        SRAM_INT_UNCORRECTABLE_ERROR         : SRAM double bit ecc error interrupt
      \arg        SRAM_INT_ADDRESS_BUFFER_OVERFLOW     : SRAM ecc error address buffer overflow interrupt
      \arg        SRAM_INT_CONTROLLER_REDUNDANCY_CHECK : SRAM controller redundancy check error interrupt
    \param[out] none
    \retval     none
*/
void sram_ecc_interrupt_disable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_INTERRUPT(interrupt)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(2U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        SRAM_INTEN &= ~interrupt;
    }
}

/*!
    \brief      get sram0/1 error flag is set or not (API_ID: 0x0003U)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[in]  flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        SRAM_FLAG_CTLERR : controller redundancy check error flag
      \arg        SRAM_FLAG_ECCCERR: ECC single bit correctable error flag
      \arg        SRAM_FLAG_ADDRERR: ECC single bit address error flag
      \arg        SRAM_FLAG_ECCUERR: ECC double bit uncorrectable error flag
      \arg        SRAM_FLAG_EDCERR : EDC after ECC checker error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sram_error_flag_get(uint32_t sram_id, uint32_t flag)
{
    FlagStatus retval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(3U), ERR_PARAM_INVALID);
    } else if(NOT_SRAM_GET_FLAG(flag)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(3U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get flag status */
        if(0U != (SRAM_ERR & (flag << sram_id))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      clear sram0/1 error flag (API_ID: 0x0004U)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[in]  flag: specify clear which flag
                one or more parameters can be selected which are shown as below:
      \arg        SRAM_FLAG_CTLERR : controller redundancy check error flag
      \arg        SRAM_FLAG_ECCCERR: ECC single bit correctable error flag
      \arg        SRAM_FLAG_ADDRERR: ECC single bit address error flag
      \arg        SRAM_FLAG_ECCUERR: ECC double bit uncorrectable error flag
      \arg        SRAM_FLAG_EDCERR : EDC after ECC checker error flag
    \param[out] none
    \retval     none
*/
void sram_error_flag_clear(uint32_t sram_id, uint32_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(4U), ERR_PARAM_INVALID);
    } else if(NOT_SRAM_GET_FLAG(flag)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(4U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* clear flag by writing 1 */
        SRAM_ERR = (flag << sram_id);
    }
}

/*!
    \brief      get sram0/1 single bit ecc error address (API_ID: 0x0005U)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[in]  address_index: single bit ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        ECC_CBE_ADDRESS0 : single bit ecc error address index0
      \arg        ECC_CBE_ADDRESS1 : single bit ecc error address index1
      \arg        ECC_CBE_ADDRESS2 : single bit ecc error address index2
      \arg        ECC_CBE_ADDRESS3 : single bit ecc error address index3
    \param[out] none
    \retval     sram0/1 single bit ecc error address
*/
uint32_t sram_ecc_single_bit_address_get(uint32_t sram_id, uint32_t address_index)
{
    uint32_t reg_addr = 0;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(5U), ERR_PARAM_INVALID);
    } else if(NOT_SRAM_ADDRESS_INDEX(address_index)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(5U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(address_index) {
        case ECC_CBE_ADDRESS0:
            reg_addr = SRAM_CBEADDR0(sram_id);
            break;
        case ECC_CBE_ADDRESS1:
            reg_addr = SRAM_CBEADDR1(sram_id);
            break;
        case ECC_CBE_ADDRESS2:
            reg_addr = SRAM_CBEADDR2(sram_id);
            break;
        case ECC_CBE_ADDRESS3:
            reg_addr = SRAM_CBEADDR3(sram_id);
            break;
        default:
            reg_addr = 0;
            break;
        }
    }
    return reg_addr;
}

/*!
    \brief      get sram0/1 double bit ecc error address (API_ID: 0x0006U)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[out] none
    \retval     sram0/1 double bit ecc error address
*/
uint32_t sram_ecc_double_bit_address_get(uint32_t sram_id)
{
    uint32_t reg_addr = 0;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(6U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg_addr = SRAM_UBEADDR(sram_id);
    }
    return reg_addr;
}

/*!
    \brief      get sram0/1 single bit ecc error address valid status (API_ID: 0x0007U)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[in]  address_index: single bit ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        ECC_CBE_ADDRESS0 : single bit ecc error address index0
      \arg        ECC_CBE_ADDRESS1 : single bit ecc error address index1
      \arg        ECC_CBE_ADDRESS2 : single bit ecc error address index2
      \arg        ECC_CBE_ADDRESS3 : single bit ecc error address index3
    \param[out] none
    \retval     FlagStatus: SET (address valid) or RESET (invalid address)
*/
FlagStatus sram_ecc_single_bit_address_valid_get(uint32_t sram_id, uint32_t address_index)
{
    FlagStatus retval = RESET;
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(7U), ERR_PARAM_INVALID);
    } else if(NOT_SRAM_ADDRESS_INDEX(address_index)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(7U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = sram_id * 0x4U + address_index;
        if(0U != (SRAM_BUFVLD & BIT(bit_pos))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      get sram0/1 double bit ecc error address valid status (API_ID: 0x0008U)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[out] none
    \retval     FlagStatus: SET (address valid) or RESET (invalid address)
*/
FlagStatus sram_ecc_double_bit_address_valid_get(uint32_t sram_id)
{
    FlagStatus retval = RESET;
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(8U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = sram_id + SRAM_BUFVLD_UBEADDRVLD_OFFSET;
        if(0U != (SRAM_BUFVLD & BIT(bit_pos))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      clear sram0/1 single bit ecc error address valid status (API_ID: 0x0009U)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[in]  address_index: single bit ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        ECC_CBE_ADDRESS0 : single bit ecc error address index0
      \arg        ECC_CBE_ADDRESS1 : single bit ecc error address index1
      \arg        ECC_CBE_ADDRESS2 : single bit ecc error address index2
      \arg        ECC_CBE_ADDRESS3 : single bit ecc error address index3
    \param[out] none
    \retval     none
*/
void sram_ecc_single_bit_address_valid_clear(uint32_t sram_id, uint32_t address_index)
{
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(9U), ERR_PARAM_INVALID);
    } else if(NOT_SRAM_ADDRESS_INDEX(address_index)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(9U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = sram_id * 0x4U + address_index;
        /* clear flag by writing 1 */
        SRAM_BUFVLD = BIT(bit_pos);
    }
}

/*!
    \brief      clear sram0/1 double bit ecc error address valid status (API_ID: 0x000AU)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[out] none
    \retval     none
*/
void sram_ecc_double_bit_address_valid_clear(uint32_t sram_id)
{
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(10U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = sram_id + SRAM_BUFVLD_UBEADDRVLD_OFFSET;
        /* clear flag by writing 1 */
        SRAM_BUFVLD = BIT(bit_pos);
    }
}

/*!
    \brief      get sram0/1 single bit ecc error address buffer overflow status (API_ID: 0x000BU)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[out] none
    \retval     FlagStatus: SET (overflow) or RESET (no overflow)
*/
FlagStatus sram_error_address_buffer_overflow_get(uint32_t sram_id)
{
    FlagStatus retval = RESET;
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(11U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = sram_id;
        if(0U != (SRAM_OVF & BIT(bit_pos))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      clear sram0/1 single bit ecc error address buffer overflow status (API_ID: 0x000CU)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[out] none
    \retval     none
*/
void sram_error_address_buffer_overflow_clear(uint32_t sram_id)
{
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(12U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = sram_id;
        /* clear flag by writing 1 */
        SRAM_OVF = BIT(bit_pos);
    }
}

/*!
    \brief      get sram0/1 ecc code of detected ecc error (API_ID: 0x000DU)
    \param[in]  sram_id: SRAM_ID_SRAMx(x=0,1)
    \param[out] none
    \retval     sram0/1 ecc code
*/
uint32_t sram_ecc_code_get(uint32_t sram_id)
{
    uint32_t ecc_code = 0;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_ID(sram_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(13U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(sram_id) {
        case SRAM_ID_SRAM0:
            ecc_code = SRAM_ECCCERR & SRAM_ECCCERR_SRAM0_ECCCDET;
            break;
        case SRAM_ID_SRAM1:
            ecc_code = ((SRAM_ECCCERR & SRAM_ECCCERR_SRAM1_ECCCDET) >> SRAM_ECCCERR_SRAM1_ECCCDET_OFFSET);
            break;
        default:
            ecc_code = 0;
            break;
        }
    }
    return ecc_code;
}

/*!
    \brief      configure sram0/1 write protection (API_ID: 0x000EU)
    \param[in]  wp_page: specify sram0/1 write protection pages
                one or more parameters can be selected which are shown as below:
      \arg        SRAM_WP_SRAM0_Px(x=0..9) : SRAM0 page x write protection bit
      \arg        SRAM_WP_SRAM1_Px(x=0..9) : SRAM1 page x write protection bit
      \arg        SRAM_WP_SRAM0_ALL: SRAM0 all page write protection bit
      \arg        SRAM_WP_SRAM1_ALL: SRAM1 all page write protection bit
      \arg        SRAM_WP_ALL      : SRAM0/1 all page write protection bit
    \param[in]  enable: DISABLE or ENABLE
    \param[out] none
    \retval     none
*/
void sram_write_protect_config(uint32_t wp_page, ControlStatus enable)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_WP_PAGE(wp_page)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(14U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(enable == ENABLE) {
            SRAM_WP |= wp_page;
        } else {
            SRAM_WP &= ~wp_page;
        }
    }
}

/*!
    \brief      get sram0/1 write protection status (API_ID: 0x000FU)
    \param[in]  wp_page: specify sram0/1 write protection pages
                one or more parameters can be selected which are shown as below:
      \arg        SRAM_WP_SRAM0_Px(x=0..9) : SRAM0 page x write protection bit
      \arg        SRAM_WP_SRAM1_Px(x=0..9) : SRAM1 page x write protection bit
      \arg        SRAM_WP_SRAM0_ALL: SRAM0 all page write protection bit
      \arg        SRAM_WP_SRAM1_ALL: SRAM1 all page write protection bit
      \arg        SRAM_WP_ALL      : SRAM0/1 all page write protection bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus sram_write_protection_get(uint32_t wp_page)
{
    FlagStatus retval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_SRAM_WP_PAGE(wp_page)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(15U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (SRAM_WP & wp_page)) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}


/*!
    \brief      enable tcm ecc error interrupt (API_ID: 0x0010U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        TCM_INT_CORRECTABLE_ERROR           : SRAM single bit ecc error interrupt
      \arg        TCM_INT_UNCORRECTABLE_ERROR         : SRAM double bit ecc error interrupt
      \arg        TCM_INT_ADDRESS_BUFFER_OVERFLOW     : SRAM ecc error address buffer overflow interrupt
      \arg        TCM_INT_CONTROLLER_REDUNDANCY_CHECK : SRAM controller redundancy check error interrupt
    \param[out] none
    \retval     none
*/
void tcm_ecc_interrupt_enable(uint32_t tcm_id, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_INTERRUPT(interrupt)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(16U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(tcm_id == TCM_ID_ITCM0 || tcm_id == TCM_ID_D0TCM0 || tcm_id == TCM_ID_D1TCM0) {
            TCM_INTEN |= interrupt;
        } else {
            TCM_INTEN |= (interrupt << 1);
        }
    }
}

/*!
    \brief      disable tcm ecc error interrupt (API_ID: 0x0011U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[in]  interrupt: specify which interrupt to enable
                one or more parameters can be selected which are shown as below:
      \arg        TCM_INT_CORRECTABLE_ERROR           : SRAM single bit ecc error interrupt
      \arg        TCM_INT_UNCORRECTABLE_ERROR         : SRAM double bit ecc error interrupt
      \arg        TCM_INT_ADDRESS_BUFFER_OVERFLOW     : SRAM ecc error address buffer overflow interrupt
      \arg        TCM_INT_CONTROLLER_REDUNDANCY_CHECK : SRAM controller redundancy check error interrupt
    \param[out] none
    \retval     none
*/
void tcm_ecc_interrupt_disable(uint32_t tcm_id, uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_INTERRUPT(interrupt)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(17U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(tcm_id == TCM_ID_ITCM0 || tcm_id == TCM_ID_D0TCM0 || tcm_id == TCM_ID_D1TCM0) {
            TCM_INTEN &= ~interrupt;
        } else {
            TCM_INTEN &= ~((uint32_t)interrupt << 1);
        }
    }
}

/*!
    \brief      get tcm error flag is set or not (API_ID: 0x0012U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[in]  flag: specify get which flag
                only one parameter can be selected which is shown as below:
      \arg        TCM_FLAG_CTLERR : controller redundancy check error flag
      \arg        TCM_FLAG_ECCCERR: ECC single bit correctable error flag
      \arg        TCM_FLAG_ADDRERR: ECC single bit address error flag
      \arg        TCM_FLAG_ECCUERR: ECC double bit uncorrectable error flag
      \arg        TCM_FLAG_EDCERR : EDC after ECC checker error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus tcm_error_flag_get(uint32_t tcm_id, uint32_t flag)
{
    FlagStatus retval = RESET;
    uint32_t bit_offset;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(18U), ERR_PARAM_INVALID);
    } else if(NOT_TCM_GET_FLAG(flag)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(18U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get bit offset of flag */
        if(TCM_FLAG_CTLERR == flag) {
            if(tcm_id <= TCM_ID_D1TCM0) {
                bit_offset = 0;
            } else {
                bit_offset = 1;
            }
        } else {
            bit_offset = tcm_id;
        }
        /* get flag status */
        if(0U != (TCM_ERR & (flag << bit_offset))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      clear tcm error flag (API_ID: 0x0013U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[in]  flag: specify clear which flag
                only one parameter can be selected which is shown as below:
      \arg        TCM_FLAG_CTLERR : controller redundancy check error flag
      \arg        TCM_FLAG_ECCCERR: ECC single bit correctable error flag
      \arg        TCM_FLAG_ADDRERR: ECC single bit address error flag
      \arg        TCM_FLAG_ECCUERR: ECC double bit uncorrectable error flag
      \arg        TCM_FLAG_EDCERR : EDC after ECC checker error flag
    \param[out] none
    \retval     none
*/
void tcm_error_flag_clear(uint32_t tcm_id, uint32_t flag)
{
    uint32_t bit_offset;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(19U), ERR_PARAM_INVALID);
    } else if(NOT_TCM_GET_FLAG(flag)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(19U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* get bit offset of flag */
        if(TCM_FLAG_CTLERR == flag) {
            if(tcm_id <= TCM_ID_D1TCM0) {
                bit_offset = 0;
            } else {
                bit_offset = 1;
            }
        } else {
            bit_offset = tcm_id;
        }
        /* clear flag by writing 1 */
        TCM_ERR = (flag << bit_offset);
    }
}

/*!
    \brief      get tcm single bit ecc error address (API_ID: 0x0014U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[in]  address_index: single bit ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        ECC_CBE_ADDRESS0 : single bit ecc error address index0
      \arg        ECC_CBE_ADDRESS1 : single bit ecc error address index1
      \arg        ECC_CBE_ADDRESS2 : single bit ecc error address index2
      \arg        ECC_CBE_ADDRESS3 : single bit ecc error address index3
    \param[out] none
    \retval     tcm single bit ecc error address
*/
uint32_t tcm_ecc_single_bit_address_get(uint32_t tcm_id, uint32_t address_index)
{
    uint32_t reg_addr = 0;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(20U), ERR_PARAM_INVALID);
    } else if(NOT_TCM_ADDRESS_INDEX(address_index)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(20U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(address_index) {
        case ECC_CBE_ADDRESS0:
            reg_addr = TCM_CBEADDR0(tcm_id);
            break;
        case ECC_CBE_ADDRESS1:
            reg_addr = TCM_CBEADDR1(tcm_id);
            break;
        case ECC_CBE_ADDRESS2:
            reg_addr = TCM_CBEADDR2(tcm_id);
            break;
        case ECC_CBE_ADDRESS3:
            reg_addr = TCM_CBEADDR3(tcm_id);
            break;
        default:
            reg_addr = 0;
            break;
        }
    }
    return reg_addr;
}

/*!
    \brief      get tcm double bit ecc error address (API_ID: 0x0015U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[out] none
    \retval      tcm double bit ecc error address
*/
uint32_t tcm_ecc_double_bit_address_get(uint32_t tcm_id)
{
    uint32_t reg_addr = 0;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(21U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg_addr = TCM_UBEADDR(tcm_id);
    }
    return reg_addr;
}

/*!
    \brief      get tcm single bit ecc error address valid status (API_ID: 0x0016U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[in]  address_index: single bit ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        ECC_CBE_ADDRESS0 : single bit ecc error address index0
      \arg        ECC_CBE_ADDRESS1 : single bit ecc error address index1
      \arg        ECC_CBE_ADDRESS2 : single bit ecc error address index2
      \arg        ECC_CBE_ADDRESS3 : single bit ecc error address index3
    \param[out] none
    \retval     FlagStatus: SET (address valid) or RESET (invalid address)
*/
FlagStatus tcm_ecc_single_bit_address_valid_get(uint32_t tcm_id, uint32_t address_index)
{
    FlagStatus retval = RESET;
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(22U), ERR_PARAM_INVALID);
    } else if(NOT_TCM_ADDRESS_INDEX(address_index)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(22U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = tcm_id * 0x4U + address_index;
        if(0U != (TCM_BUFVLD & BIT(bit_pos))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      get tcm double bit ecc error address valid status (API_ID: 0x0017U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[out] none
    \retval     FlagStatus: SET (address valid) or RESET (invalid address)
*/
FlagStatus tcm_ecc_double_bit_address_valid_get(uint32_t tcm_id)
{
    FlagStatus retval = RESET;
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(23U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = tcm_id + TCM_BUFVLD_UBEADDRVLD_OFFSET;
        if(0U != (TCM_BUFVLD & BIT(bit_pos))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      clear tcm single bit ecc error address valid status (API_ID: 0x0018U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[in]  address_index: single bit ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        ECC_CBE_ADDRESS0 : single bit ecc error address index0
      \arg        ECC_CBE_ADDRESS1 : single bit ecc error address index1
      \arg        ECC_CBE_ADDRESS2 : single bit ecc error address index2
      \arg        ECC_CBE_ADDRESS3 : single bit ecc error address index3
    \param[out] none
    \retval     none
*/
void tcm_ecc_single_bit_address_valid_clear(uint32_t tcm_id, uint32_t address_index)
{
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(24U), ERR_PARAM_INVALID);
    } else if(NOT_TCM_ADDRESS_INDEX(address_index)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(24U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = tcm_id * 0x4U + address_index;
        /* clear flag by writing 1 */
        TCM_BUFVLD = BIT(bit_pos);
    }
}

/*!
    \brief      clear tcm double bit ecc error address valid status (API_ID: 0x0019U)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[out] none
    \retval     none
*/
void tcm_ecc_double_bit_address_valid_clear(uint32_t tcm_id)
{
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(25U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = tcm_id + TCM_BUFVLD_UBEADDRVLD_OFFSET;
        /* clear flag by writing 1 */
        TCM_BUFVLD = BIT(bit_pos);
    }
}

/*!
    \brief      get tcm single bit ecc error address buffer overflow status (API_ID: 0x001AU)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[out] none
    \retval     FlagStatus: SET (overflow) or RESET (no overflow)
*/
FlagStatus tcm_error_address_buffer_overflow_get(uint32_t tcm_id)
{
    FlagStatus retval = RESET;
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(26U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = tcm_id;
        if(0U != (TCM_OVF & BIT(bit_pos))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      clear tcm single bit ecc error address buffer overflow status (API_ID: 0x001BU)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[out] none
    \retval     none
*/
void tcm_error_address_buffer_overflow_clear(uint32_t tcm_id)
{
    uint32_t bit_pos;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(27U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        bit_pos = tcm_id;
        /* clear flag by writing 1 */
        TCM_OVF = BIT(bit_pos);
    }
}

/*!
    \brief      get tcm ecc code of detected ecc error (API_ID: 0x001CU)
    \param[in]  tcm_id: specify tcm id
                only one parameter can be selected which is shown as below:
      \arg        TCM_ID_ITCM0  : ITCM of CM7_0
      \arg        TCM_ID_D0TCM0 : D0TCM of CM7_0
      \arg        TCM_ID_D1TCM0 : D1TCM of CM7_0
      \arg        TCM_ID_ITCM1  : ITCM of CM7_1
      \arg        TCM_ID_D0TCM1 : D0TCM of CM7_1
      \arg        TCM_ID_D1TCM1 : D1TCM of CM7_1
    \param[out] none
    \retval    tcm ecc code
*/
uint32_t tcm_ecc_code_get(uint32_t tcm_id)
{
    uint32_t ecc_code = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_ID(tcm_id)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(28U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch(tcm_id) {
        case TCM_ID_ITCM0:
            ecc_code = TCM0_ECCCERR & TCM0_ECCCERR_ITCM0_ECCCDET;
            break;
        case TCM_ID_D0TCM0:
            ecc_code = ((TCM0_ECCCERR & TCM0_ECCCERR_D0TCM0_ECCCDET) >> TCM0_ECCCERR_D0TCM0_ECCCDET_OFFSET);
            break;
        case TCM_ID_D1TCM0:
            ecc_code = ((TCM0_ECCCERR & TCM0_ECCCERR_D1TCM0_ECCCDET) >> TCM0_ECCCERR_D1TCM0_ECCCDET_OFFSET);
            break;
#if defined(GD32A74XX) || defined(GD32A72XX)
        case TCM_ID_ITCM1:
            ecc_code = (TCM1_ECCCERR & TCM1_ECCCERR_ITCM1_ECCCDET);
            break;
        case TCM_ID_D0TCM1:
            ecc_code = ((TCM1_ECCCERR & TCM1_ECCCERR_D0TCM1_ECCCDET) >> TCM1_ECCCERR_D0TCM0_ECCCDET_OFFSET);
            break;
        case TCM_ID_D1TCM1:
            ecc_code = ((TCM1_ECCCERR & TCM1_ECCCERR_D1TCM1_ECCCDET) >> TCM1_ECCCERR_D1TCM0_ECCCDET_OFFSET);
            break;
#endif /* defined(GD32A74XX) || defined(GD32A72XX) */
        default:
            ecc_code = 0U;
            break;
        }
    }
    return ecc_code;
}

/*!
    \brief      configure tcm write protection (API_ID: 0x001DU)
    \param[in]  wp_page: specify TCM write protection page
                one or more parameters can be selected which are shown as below:
      \arg        TCM_WP_ITCM0_Px(x=0..3) : ITCM of CM7_0 page x write protection bit
      \arg        TCM_WP_ITCM1_Px(x=0..3) : ITCM of CM7_1 page x write protection bit
      \arg        TCM_WP_DTCM0_Px(x=0..7) : DTCM of CM7_0 page x write protection bit
      \arg        TCM_WP_DTCM1_Px(x=0..7) : DTCM of CM7_1 page x write protection bit
      \arg        TCM_WP_ITCM0_ALL: ITCM of CM7_0 all page write protection bit
      \arg        TCM_WP_ITCM1_ALL: ITCM of CM7_1 all page write protection bit
      \arg        TCM_WP_DTCM0_ALL: DTCM of CM7_0 all page write protection bit
      \arg        TCM_WP_DTCM1_ALL: DTCM of CM7_1 all page write protection bit
      \arg        TCM_WP_ALL      : TCM of CM7_0/1 all page write protection bit
    \param[in]  enable: DISABLE or ENABLE
    \param[out] none
    \retval     none
*/
void tcm_write_protect_config(uint32_t wp_page, ControlStatus enable)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_WP_PAGE(wp_page)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(29U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(enable == ENABLE) {
            TCM_WP |= wp_page;
        } else {
            TCM_WP &= ~wp_page;
        }
    }
}

/*!
    \brief      get tcm write protection status (API_ID: 0x001EU)
    \param[in]  wp_page: specify TCM write protection page
                one or more parameters can be selected which are shown as below:
      \arg        TCM_WP_ITCM0_Px(x=0..3) : ITCM of CM7_0 page x write protection bit
      \arg        TCM_WP_ITCM1_Px(x=0..3) : ITCM of CM7_1 page x write protection bit
      \arg        TCM_WP_DTCM0_Px(x=0..7) : DTCM of CM7_0 page x write protection bit
      \arg        TCM_WP_DTCM1_Px(x=0..7) : DTCM of CM7_1 page x write protection bit
      \arg        TCM_WP_ITCM0_ALL: ITCM of CM7_0 all page write protection bit
      \arg        TCM_WP_ITCM1_ALL: ITCM of CM7_1 all page write protection bit
      \arg        TCM_WP_DTCM0_ALL: DTCM of CM7_0 all page write protection bit
      \arg        TCM_WP_DTCM1_ALL: DTCM of CM7_1 all page write protection bit
      \arg        TCM_WP_ALL      : TCM of CM7_0/1 all page write protection bit
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus tcm_write_protection_get(uint32_t wp_page)
{
    FlagStatus retval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_TCM_WP_PAGE(wp_page)) {
        fw_debug_report_err(SRAM_TCM_MODULE_ID, API_ID(30U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (TCM_WP & wp_page)) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}
