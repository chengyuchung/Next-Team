/*!
    \file    gd32a7xx_fmc.c
    \brief   FMC driver

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

#include "gd32a7xx_fmc.h"

/* FMC mask */
#define LOW_8BITS_MASK                  ((uint32_t)0x000000FFU)               /*!< the 0-7 bits mask of a word */
#define HIGH_8BITS_MASK                 ((uint32_t)0x0000FF00U)               /*!< the 8-15 bits mask of a word */
#define LOW_8BITS_MASK1                 ((uint32_t)0x00FF0000U)               /*!< the 16-23 bits mask of a word */
#define HIGH_8BITS_MASK1                ((uint32_t)0xFF000000U)               /*!< the 24-31 bits mask of a word */
#define LOW_16BITS_MASK                 ((uint32_t)0x0000FFFFU)               /*!< the 0-15 bits mask of a word */
#define HIGH_16BITS_MASK                ((uint32_t)0xFFFF0000U)               /*!< the 16-31 bits mask of a word */
#define ECC_FLAG_CLEAR_MASK             ((uint32_t)0xF0100000U)               /*!< the ecc flag clear bit mask*/

/* FMC register bit offset */
#define CTL_CBCMDLEN_OFFSET             ((uint32_t)0x0000001DU)               /*!< CBCMDLEN offset in FMC_CTLx register */
#define OBSTAT_PLEVEL_OFFSET            ((uint32_t)0x00000001U)               /*!< PLEVEL offset in FMC_OBSTAT register */
#define OBSTAT_USER_OFFSET              ((uint32_t)0x00000008U)               /*!< USER offset in FMC_OBSTAT register */
#define OBSTAT_DATA_OFFSET              ((uint32_t)0x00000010U)               /*!< DATA offset in FMC_OBSTAT register */

#define HSMOBSTAT_SPC_OFFSET            ((uint32_t)0x00000018U)               /*!< SPC offset in FMC_HSMOBSTAT register */

/* return the FMC ctl0 state */
static fmc_state_enum fmc_ctl0_state_get(void);
/* return the FMC ctl1 state */
static fmc_state_enum fmc_ctl1_state_get(void);
/* check whether FMC ctl0 is ready or not */
static fmc_state_enum fmc_ctl0_ready_wait(uint32_t timeout);
/* check whether FMC ctl1 is ready or not */
static fmc_state_enum fmc_ctl1_ready_wait(uint32_t timeout);

/*!
    \brief      unlock the control register 0/1 operation (API_ID(0x0001U))
                it is better to used in pairs with fmc_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_unlock(void)
{
    if((0U != (FMC_CTL0 & FMC_CTL0_LK))) {
        /* write the FMC control register 0 key */
        FMC_KEY0 = UNLOCK_KEY0(0U);
        FMC_KEY0 = UNLOCK_KEY1(0U);
    }

    if((0U != (FMC_CTL1 & FMC_CTL1_LK))) {
        /* write the FMC control register 1 key */
        FMC_KEY1 = UNLOCK_KEY0(1U);
        FMC_KEY1 = UNLOCK_KEY1(1U);
    }
}

/*!
    \brief      unlock the control register 0 operation (API_ID(0x0002U))
                it is better to used in pairs with fmc_ctl0_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ctl0_unlock(void)
{
    if((0U != (FMC_CTL0 & FMC_CTL0_LK))) {
        /* write the FMC control register 0 key */
        FMC_KEY0 = UNLOCK_KEY0(0U);
        FMC_KEY0 = UNLOCK_KEY1(0U);
    }
}

/*!
    \brief      unlock the control register 1 operation (API_ID(0x0003U))
                it is better to used in pairs with fmc_ctl1_lock
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ctl1_unlock(void)
{
    if((0U != (FMC_CTL1 & FMC_CTL1_LK))) {
        /* write the FMC control register 1 key */
        FMC_KEY1 = UNLOCK_KEY0(1U);
        FMC_KEY1 = UNLOCK_KEY1(1U);
    }
}

/*!
    \brief      lock the control register 0/1 operation (API_ID(0x0004U))
                it is better to used in pairs with fmc_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_lock(void)
{
    /* set the LK bit in FMC_CTL0 register */
    FMC_CTL0 |= FMC_CTL0_LK;
    /* set the LK bit in FMC_CTL1 register */
    FMC_CTL1 |= FMC_CTL1_LK;
}

/*!
    \brief      lock the control register 0 operation (API_ID(0x0005U))
                it is better to used in pairs with fmc_ctl0_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ctl0_lock(void)
{
    /* set the LK bit in FMC_CTL0 register */
    FMC_CTL0 |= FMC_CTL0_LK;
}

/*!
    \brief      lock the control register 1 operation (API_ID(0x0006U))
                it is better to used in pairs with fmc_ctl1_unlock after an operation
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmc_ctl1_lock(void)
{
    /* set the LK bit in FMC_CTL1 register */
    FMC_CTL1 |= FMC_CTL1_LK;
}

/*!
    \brief      set the wait state counter value (API_ID(0x0007U))
    \param[in]  wscnt: wait state counter value
                only one parameter can be selected which is shown as below:
      \arg        WS_WSCNT_0: 0 wait state added
      \arg        WS_WSCNT_1: 1 wait state added
      \arg        WS_WSCNT_2: 2 wait state added
      \arg        WS_WSCNT_3: 3 wait state added
      \arg        WS_WSCNT_4: 4 wait state added
      \arg        WS_WSCNT_5: 5 wait state added
    \param[out] none
    \retval     none
*/
void fmc_wscnt_set(uint8_t wscnt)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_WS_WSCNT(wscnt)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMC_WS;        /* set the wait state counter value */
        reg &= ~FMC_WS_WSCNT;
        FMC_WS = (reg | wscnt);
    }
}

/*!
    \brief      enable buffer x (API_ID(0x0008U))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_buffer_enable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) |= FMC_BUFECCCS_BUFEN;
    }
}

/*!
    \brief      disable buffer x (API_ID(0x0009U))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_buffer_disable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) &= ~FMC_BUFECCCS_BUFEN;
    }
}

/*!
    \brief      enable buffer x read code buffers (API_ID(0x000AU))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_code_current_buffer_enable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) |= FMC_BUFECCCS_CBUFEN;
    }
}

/*!
    \brief      disable buffer x read code buffers (API_ID(0x000BU))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_code_current_buffer_disable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) &= ~FMC_BUFECCCS_CBUFEN;
    }
}

/*!
    \brief      enable buffer x read data buffers (API_ID(0x000CU))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_data_current_buffer_enable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) |= FMC_BUFECCCS_DBUFEN;
    }
}

/*!
    \brief      disable buffer x read data buffers (API_ID(0x000DU))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_data_current_buffer_disable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) &= ~FMC_BUFECCCS_DBUFEN;
    }
}

/*!
    \brief      enable buffer x code prefetch (API_ID(0x000EU))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_code_prefetch_buffer_enable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) |= FMC_BUFECCCS_CPFEN;
    }
}

/*!
    \brief      disable buffer x code prefetch (API_ID(0x000FU))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_code_prefetch_buffer_disable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) &= ~FMC_BUFECCCS_CPFEN;
    }
}

/*!
    \brief      enable buffer x data prefetch (API_ID(0x0010U))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_data_prefetch_buffer_enable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) |= FMC_BUFECCCS_DPFEN;
    }
}

/*!
    \brief      disable buffer x data prefetch (API_ID(0x0011U))
    \param[in]  index: buffer number index
                only one parameter can be selected which is shown as below:
      \arg        FMC_BUFF_0: buffer 0
      \arg        FMC_BUFF_1: buffer 1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_BUFF_2: buffer 2
      \arg        FMC_BUFF_3: buffer 3
    \param[out] none
    \retval     none
*/
void fmc_data_prefetch_buffer_disable(fmc_buff_enum index)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_BUFFER_INDEX(index)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0011U), ERR_PARAM_INVALID);
    } else
#endif
    {
        FMC_BUFECCCS(index) &= ~FMC_BUFECCCS_DPFEN;
    }
}

/*!
    \brief      check whether area in bank0/bank1/data flash page is blank or not by check blank command (API_ID(0x0012U))
    \param[in]  address: start address to check. the value is in the range of bank0 / bank1 / data flash
    \param[in]  length: the read length is 2^(length + 1) double words, the flash area to be checked must be in one page and should not exceed 2KB boundary
                only one parameter can be selected which is shown as below:
      \arg        FMC_CBCMDLEN_2_DW: check blank command read length is 2 double words (16 bytes)
      \arg        FMC_CBCMDLEN_4_DW: check blank command read length is 4 double words (32 bytes)
      \arg        FMC_CBCMDLEN_8_DW: check blank command read length is 8 double words (64 bytes)
      \arg        FMC_CBCMDLEN_16_DW: check blank command read length is 16 double words (128 bytes)
      \arg        FMC_CBCMDLEN_32_DW: check blank command read length is 32 double words (256 bytes)
      \arg        FMC_CBCMDLEN_64_DW: check blank command read length is 64 double words (512 bytes)
      \arg        FMC_CBCMDLEN_128_DW: check blank command read length is 128 double words (1024 bytes)
      \arg        FMC_CBCMDLEN_256_DW: check blank command read length is 256 double words (2048 bytes)
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_blank_check(uint32_t address, uint8_t length)
{
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE0_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else if(NOT_FMC_VALID_BLANK_ADDRESS_CONFIG(address, length)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else
#endif
    {
        fmc_ctl0_unlock();
        /* start check blank command */
        FMC_ADDR0 = address;
        FMC_CTL0 &= ~FMC_CTL0_CBCMDLEN;
        FMC_CTL0 |= (uint32_t)length << CTL_CBCMDLEN_OFFSET;
        FMC_CTL0 |= FMC_CTL0_CBCMD;
        FMC_CTL0 |= FMC_CTL0_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
        fmc_ctl0_unlock();
        /* reset the CBCMD bit */
        FMC_CTL0 &= ~FMC_CTL0_CBCMD;
        /* lock CTL0 */
        fmc_ctl0_lock();
    }
    return fmc_state;
}

/*!
    \brief      get base address of bank0 (API_ID(0x0013U))
    \param[in]  none
    \param[out] none
    \retval     base address of bank0, 0x08000000 ~ 0x083FFFFF
*/
uint32_t fmc_bank0_base_address_get(void)
{
    uint32_t base_addr;

    if(0U == (FMC_HSMOBSTAT & FMC_HSMOBSTAT_SWAP)) {
        base_addr = BANK0_BASE_ADDRESS + fmc_bank_size_get();
    } else {
        base_addr = BANK0_BASE_ADDRESS;
    }

    return base_addr;
}

/*!
    \brief      get base address of bank1 (API_ID(0x0014U))
    \param[in]  none
    \param[out] none
    \retval     base address of bank, 0x08000000 ~ 0x083FFFFF
*/
uint32_t fmc_bank1_base_address_get(void)
{
    uint32_t base_addr;

    if(0U == (FMC_HSMOBSTAT & FMC_HSMOBSTAT_SWAP)) {
        base_addr = BANK0_BASE_ADDRESS;
    } else {
        base_addr = BANK0_BASE_ADDRESS + fmc_bank_size_get();
    }

    return base_addr;
}

/*!
    \brief      erase bank0/bank1/data flash page (API_ID(0x0015U))
    \param[in]  page_address: target page start address, the value is in the range of bank0 / bank1 / data flash
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE0_ADDRESS(page_address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* wait for the FMC ready */
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            /* unlock CTL0 */
            fmc_ctl0_unlock();
            /* start page erase */
            FMC_ADDR0 = page_address;
            FMC_CTL0 |= FMC_CTL0_PER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl0_unlock();
            /* reset the PER bit */
            FMC_CTL0 &= ~FMC_CTL0_PER;
            /* lock CTL0 */
            fmc_ctl0_lock();
        }
    }
    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      mass erase bank0/bank1/data flash (API_ID(0x0016U))
    \param[in]  area: mass erase area
                only one parameter can be selected which is shown as below:
      \arg        BANK0_AREA: main flash bank0 area
      \arg        BANK1_AREA: main flash bank1 area
      \arg        DATA_FLASH_AREA: data flash area
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_mass_erase(fmc_area_enum area)
{
    uint32_t address = 0U;
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_HOST_AREA(area)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0016U), ERR_PARAM_INVALID);
    } else
#endif
    {
        switch(area) {
        case BANK0_AREA:
            /* bank0 start address */
            address = fmc_bank0_base_address_get();
            break;
        case BANK1_AREA:
            /* bank1 start address */
            address = fmc_bank1_base_address_get();
            break;
        case DATA_FLASH_AREA:
            /* data flash start address */
            address = HOST_DATA_BASE_ADDRESS;
            break;
        default:
            break;
        }

        /* wait for the FMC ready */
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            /* unlock CTL0 */
            fmc_ctl0_unlock();
            /* write block address */
            FMC_ADDR0 = address;
            /* start chip erase */
            FMC_CTL0 |= FMC_CTL0_MER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl0_unlock();
            /* reset the MER bit */
            FMC_CTL0 &= ~FMC_CTL0_MER;
            /* lock CTL0 */
            fmc_ctl0_lock();
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a double word at the corresponding address in bank0 / bank1 / data flash (API_ID(0x0017U))
    \param[in]  address: address to program, the value is in the range of bank0 / bank1 / data flash
    \param[in]  data: double word to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_doubleword_program(uint32_t address, uint64_t data)
{
    uint32_t data0, data1;
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE0_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0017U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* wait for the FMC ready */
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
        data0 = (uint32_t)(data & 0xFFFFFFFFU);
        data1 = (uint32_t)((data >> 32U) & 0xFFFFFFFFU);

        if(FMC_READY == fmc_state) {
            /* unlock CTL0 */
            fmc_ctl0_unlock();
            /* set the PG bit to start program */
            FMC_CTL0 |= FMC_CTL0_PG;
            __DSB();
            __ISB();
            /* write the data to WDATAL0 and WDATAH0 */
            FMC_WDATL0 = data0;
            FMC_WDATH0 = data1;
            /* write the logic address */
            FMC_ADDR0 = address;
            /* set START bit to launch double program operation to flash */
            FMC_CTL0 |= FMC_CTL0_START;
            __DSB();
            __ISB();
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl0_unlock();
            /* reset the PG bit */
            FMC_CTL0 &= ~FMC_CTL0_PG;
            /* lock CTL0 */
            fmc_ctl0_lock();
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      fast program one row data (64 double-word) starting at the corresponding address in bank0 / bank1 / data flash (API_ID(0x0018U))
    \param[in]  address: address to program, the value is in the range of bank0 / bank1 / data flash
    \param[in]  data: data buffer to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_fast_program(uint32_t address, uint64_t data[])
{
    uint8_t index;
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE0_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0018U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the row (64 double-word) in flash to confirm all data in flash is all 0xFF */
        fmc_state = fmc_blank_check(address, CBCMDLEN_OF_ONE_ROW);

        if(FMC_CBCMDERR == fmc_state) {
            /* flash is not erased */
            fmc_state =  FMC_CBCMDERR;
        } else {
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl0_unlock();
                /* set the FSTPG bit to start program */
                FMC_CTL0 |= FMC_CTL0_FSTPG;

                /* program the row data */
                for(index = 0U; index < DOUBLEWORD_CNT_IN_ROW; index++) {
                    /* write the data to WDATAL0 and WDATAH0 */
                    FMC_WDATL0 = (uint32_t)(data[index] & 0x00000000FFFFFFFFU);
                    FMC_WDATH0 = (uint32_t)(data[index] >> 32U);
                }

                FMC_ADDR0 = address;
                /* set START bit to launch fast program operation to flash */
                FMC_CTL0 |= FMC_CTL0_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl0_unlock();
                /* reset the FSTPG bit */
                FMC_CTL0 &= ~FMC_CTL0_FSTPG;
                /* lock CTL0 */
                fmc_ctl0_lock();
            }
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a double word at the corresponding address in OTP (API_ID(0x0019U))
    \param[in]  address: address to program
    \param[in]  data: double word to write
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_otp_doubleword_program(uint32_t address, uint64_t data)
{
    uint32_t data0, data1;
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE0_OTP_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0019U), ERR_PARAM_INVALID);
    } else
#endif
    {
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
        data0 = (uint32_t)(data & 0xFFFFFFFFU);
        data1 = (uint32_t)((data >> 32U) & 0xFFFFFFFFU);

        if(FMC_READY == fmc_state) {
            fmc_ctl0_unlock();
            /* set the PG bit to start program */
            FMC_CTL0 |= FMC_CTL0_PG;
            /* write the data to WDATAL0 and WDATAH0 */
            FMC_WDATL0 = data0;
            FMC_WDATH0 = data1;
            /* write the logic address */
            FMC_ADDR0 = address;
            /* set START bit to launch double program operation to flash */
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl0_unlock();
            /* reset the PG bit */
            FMC_CTL0 &= ~FMC_CTL0_PG;
            /* lock CTL0 */
            fmc_ctl0_lock();
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      bank0 / bank1 size get (API_ID(0x001AU))
    \param[in]  none
    \param[out] none
    \retval     bank0 / bank1 size get size, 0x00000000 ~ 0x00200000
*/
uint32_t fmc_bank_size_get(void)
{
    uint32_t bank_size;
    uint32_t size_index = (FMC_HSMWP & FMC_HSMWP_HOSTSIZE) >> 30U;

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    uint32_t _bank_size[4] = {512, 1024, 0, 2048};
#else
    uint32_t _bank_size[4] = {256, 512, 0, 1024};
#endif

    /* return HOST bank0 / bank1 size */
    if(0x03U == size_index) {
        bank_size = _bank_size[size_index] * 1024U - hsm_bank_size_get();
    } else {
        bank_size = _bank_size[size_index] * 1024U;
    }

    return bank_size;
}

/*!
    \brief      check whether area in HSM data flash page is blank or not by check blank command (API_ID(0x001BU))
    \param[in]  address: start address to check. the value is in the range of HSM data flash
    \param[in]  length: the read length is 2^(length + 1) double words, the flash area to be checked must be in one page and should not exceed 2KB boundary
                only one parameter can be selected which is shown as below:
      \arg        FMC_CBCMDLEN_2_DW: check blank command read length is 2 double words (16 bytes)
      \arg        FMC_CBCMDLEN_4_DW: check blank command read length is 4 double words (32 bytes)
      \arg        FMC_CBCMDLEN_8_DW: check blank command read length is 8 double words (64 bytes)
      \arg        FMC_CBCMDLEN_16_DW: check blank command read length is 16 double words (128 bytes)
      \arg        FMC_CBCMDLEN_32_DW: check blank command read length is 32 double words (256 bytes)
      \arg        FMC_CBCMDLEN_64_DW: check blank command read length is 64 double words (512 bytes)
      \arg        FMC_CBCMDLEN_128_DW: check blank command read length is 128 double words (1024 bytes)
      \arg        FMC_CBCMDLEN_256_DW: check blank command read length is 256 double words (2048 bytes)
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_hsm_data_blank_check(uint32_t address, uint8_t length)
{
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE1_DATA_FLASH_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x001BU), ERR_PARAM_INVALID);
    } else if(NOT_FMC_VALID_BLANK_ADDRESS_CONFIG(address, length)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x001BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        fmc_ctl1_unlock();
        /* start check blank command */
        FMC_ADDR1 = address;
        FMC_CTL1 &= ~FMC_CTL1_CBCMDLEN;
        FMC_CTL1 |= (uint32_t)length << CTL_CBCMDLEN_OFFSET;
        FMC_CTL1 |= FMC_CTL1_CBCMD;
        FMC_CTL1 |= FMC_CTL1_START;
        /* wait for the FMC ready */
        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
        fmc_ctl1_unlock();
        /* reset the CBCMD bit */
        FMC_CTL1 &= ~FMC_CTL1_CBCMD;
        /* lock CTL1 */
        fmc_ctl1_lock();
    }
    return fmc_state;
}

/*!
    \brief      get base address of HSM bank 0 (API_ID(0x001CU))
    \param[in]  none
    \param[out] none
    \retval     base address of HSM bank 0, 0x08440000 / 0x08480000
*/
uint32_t fmc_hsm_bank0_address_get(void)
{
    uint32_t base_addr;

    if(0U == (FMC_HSMOBSTAT & FMC_HSMOBSTAT_SWAP)) {
        base_addr = HSM_BANK1_ADDRESS;
    } else {
        base_addr = HSM_BANK0_ADDRESS;
    }

    return base_addr;
}

/*!
    \brief      get base address of HSM bank 1 (API_ID(0x001DU))
    \param[in]  none
    \param[out] none
    \retval     base address of HSM bank 1, 0x08440000 / 0x08480000
*/
uint32_t fmc_hsm_bank1_address_get(void)
{
    uint32_t base_addr;

    if(0U == (FMC_HSMOBSTAT & FMC_HSMOBSTAT_SWAP)) {
        base_addr = HSM_BANK0_ADDRESS;
    } else {
        base_addr = HSM_BANK1_ADDRESS;
    }

    return base_addr;
}

/*!
    \brief      erase HSM bank page (API_ID(0x001EU))
    \param[in]  page_address: target page start address, the value is in the range of HSM bank0 / bank1 memory
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_hsm_bank_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state;

    fmc_state = fmc_page_erase(page_address);

    return fmc_state;
}

/*!
    \brief      program a double word at the corresponding address in HSM bank0 / bank1 flash (API_ID(0x001FU))
    \param[in]  address: address to program, the value is in the range of HSM bank0/1 flash
    \param[in]  data: double word to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_hsm_bank_doubleword_program(uint32_t address, uint64_t data)
{
    return fmc_doubleword_program(address, data);
}

/*!
    \brief      fast program one row data (64 double-word) starting at the corresponding address in HSM bank0 / bank1 flash (API_ID(0x0020U))
    \param[in]  address: address to program, the value is in the range of bank0 / bank1 / data flash
    \param[in]  data: data buffer to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_hsm_bank_fast_program(uint32_t address, uint64_t data[])
{
    return fmc_fast_program(address, data);
}

/*!
    \brief      HSM erase data flash page (API_ID(0x0021U))
    \param[in]  page_address: target page start address, the value is in the range of HSM data flash
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_hsm_data_page_erase(uint32_t page_address)
{
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE1_DATA_FLASH_ADDRESS(page_address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0021U), ERR_PARAM_INVALID);
    } else
#endif
    {
        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            /* unlock CTL1 */
            fmc_ctl1_unlock();
            /* start page erase */
            FMC_ADDR1 = page_address;
            FMC_CTL1 |= FMC_CTL1_PER;
            FMC_CTL1 |= FMC_CTL1_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl1_unlock();
            /* reset the PER bit */
            FMC_CTL1 &= ~FMC_CTL1_PER;
            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }
    /* return the FMC state  */
    return fmc_state;
}

/*!
    \brief      program a double word at the corresponding address in HSM data flash (API_ID(0x0022U))
    \param[in]  address: address to program, the value is in the range of HSM data flash
    \param[in]  data: double word to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_hsm_data_doubleword_program(uint32_t address, uint64_t data)
{
    uint32_t data0, data1;
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE1_DATA_FLASH_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0022U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* wait for the FMC ready */
        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
        data0 = (uint32_t)(data & 0xFFFFFFFFU);
        data1 = (uint32_t)((data >> 32U) & 0xFFFFFFFFU);

        if(FMC_READY == fmc_state) {
            /* unlock CTL1 */
            fmc_ctl1_unlock();
            /* set the PG bit to start program */
            FMC_CTL1 |= FMC_CTL1_PG;
            /* write the data to WDATAL1 and WDATAH1 */
            FMC_WDATL1 = data0;
            FMC_WDATH1 = data1;
            /* write the logic address */
            FMC_ADDR1 = address;
            /* set START bit to launch double program operation to flash */
            FMC_CTL1 |= FMC_CTL1_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl1_unlock();
            /* reset the PG bit */
            FMC_CTL1 &= ~FMC_CTL1_PG;
            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      HSM fast program one row data (64 double-word) starting at the corresponding address (API_ID(0x0023U))
    \param[in]  address: address to program, the value is in the range of HSM data flash
    \param[in]  data: data buffer to program
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum fmc_hsm_data_fast_program(uint32_t address, uint64_t data[])
{
    uint8_t index;
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE1_DATA_FLASH_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0023U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the row (64 double-word) in flash to confirm all data in flash is all 0xFF */
        fmc_state = fmc_hsm_data_blank_check(address, CBCMDLEN_OF_ONE_ROW);

        if(FMC_CBCMDERR == fmc_state) {
            /* flash is not erased */
            return FMC_CBCMDERR;
        }

        /* wait for the FMC ready */
        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            fmc_ctl1_unlock();
            /* set the FSTPG bit to start program */
            FMC_CTL1 |= FMC_CTL1_FSTPG;

            /* program the row data */
            for(index = 0U; index < DOUBLEWORD_CNT_IN_ROW; index++) {
                /* write the data to WDATAL1 and WDATAH1 */
                FMC_WDATL1 = (uint32_t)(data[index] & 0x00000000FFFFFFFFU);
                FMC_WDATH1 = (uint32_t)(data[index] >> 32U);
            }

            FMC_ADDR1 = address;
            /* set START bit to launch fast program operation to flash */
            FMC_CTL1 |= FMC_CTL1_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl1_unlock();
            /* reset the FSTPG bit */
            FMC_CTL1 &= ~FMC_CTL1_FSTPG;
            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program a double word at the corresponding address in HSM OTP (API_ID(0x0024U))
    \param[in]  address: address to program
    \param[in]  data: double word to write
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_otp_doubleword_program(uint32_t address, uint64_t data)
{
    uint32_t data0, data1;
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_VALID_INTERFACE1_OTP_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0024U), ERR_PARAM_INVALID);
    } else
#endif
    {
        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
        data0 = (uint32_t)(data & 0xFFFFFFFFU);
        data1 = (uint32_t)((data >> 32U) & 0xFFFFFFFFU);

        if(FMC_READY == fmc_state) {
            fmc_ctl1_unlock();
            /* set the PG bit to start program */
            FMC_CTL1 |= FMC_CTL1_PG;
            /* write the data to WDATAL1 and WDATAH1 */
            FMC_WDATL1 = data0;
            FMC_WDATH1 = data1;
            /* write the logic address */
            FMC_ADDR1 = address;
            /* set START bit to launch double program operation to flash */
            FMC_CTL1 |= FMC_CTL1_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl1_unlock();
            /* reset the PG bit */
            FMC_CTL1 &= ~FMC_CTL1_PG;
            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      HSM system mark LC slot valid field (API_ID(0x0025U))
    \param[in]  address: address to program
                only one parameter can be selected which is shown as below:
      \arg        LC_SLOT0_BASE_ADDRESS: slot0 base address
      \arg        LC_SLOT1_BASE_ADDRESS: slot1 base address
      \arg        LC_SLOT2_BASE_ADDRESS: slot2 base address
      \arg        LC_SLOT3_BASE_ADDRESS: slot3 base address
      \arg        LC_SLOT4_BASE_ADDRESS: slot4 base address
      \arg        LC_IN_FIELD_RECOVER_MODE: IN_FIELD_RECOVER_MODE base address
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_lc_valid_mark(uint32_t address)
{
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_LC_SLOT_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0025U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* program valid field to marked */
        fmc_state = hsm_otp_doubleword_program(address, (uint64_t)LC_MARKED);
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      HSM system mark LC slot invalid field (API_ID(0x0026U))
    \param[in]  address: address to program
                only one parameter can be selected which is shown as below:
      \arg        LC_SLOT0_BASE_ADDRESS: slot0 base address
      \arg        LC_SLOT1_BASE_ADDRESS: slot1 base address
      \arg        LC_SLOT2_BASE_ADDRESS: slot2 base address
      \arg        LC_SLOT3_BASE_ADDRESS: slot3 base address
      \arg        LC_SLOT4_BASE_ADDRESS: slot4 base address
      \arg        LC_IN_FIELD_RECOVER_MODE: IN_FIELD_RECOVER_MODE base address
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_lc_invalid_mark(uint32_t address)
{
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_LC_SLOT_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0026U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* if LC slot is other value, return FMC_PGERR */
        if(REG64(address + 8U) != LC_ERASED) {
            fmc_state =   FMC_PGERR;
        } else {
            /* program invalid field to marked */
            fmc_state = hsm_otp_doubleword_program(address + 8U, (uint64_t)LC_MARKED);
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      HOST dbg disable (API_ID(0x0027U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_host_dbg_disable(void)
{
    /* return the FMC state */
    return hsm_otp_doubleword_program(HOST_DBG_DISABLE_ADDRESS, (uint64_t)0x5A0FA5F0);
}

/*!
    \brief      HSM dbg disable (API_ID(0x0028U))
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_hsm_dbg_disable(void)
{
    /* return the FMC state */
    return hsm_otp_doubleword_program(HSM_DBG_DISABLE_ADDRESS, (uint64_t)0x5A0FA5F0);
}

/*!
    \brief      HOST / HSM debug password configuration in HSM OTP (API_ID(0x0029U))
    \param[in]  address: address to program
                only one parameter can be selected which is shown as below:
      \arg        HOST_DBG_PASSWORD_ADDRESS: HOST password base address
      \arg        HSM_DBG_PASSWORD_ADDRESS: HSM password base address
    \param[in]  data: data buffer to program. data buffer is two double-word
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_debug_password_config(uint32_t address, uint64_t data[])
{
    uint8_t index;
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_DBG_PASSWORD_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0029U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* program the two double-word data */
        for(index = 0U; index < 2U; index++) {
            /* program a double word */
            fmc_state = hsm_otp_doubleword_program(address, data[index]);
            address += 8U;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      HSM cryp key configuration in HSM OTP (API_ID(0x002AU))
    \param[in]  address: address to program
                only one parameter can be selected which is shown as below:
      \arg        CRYP_KEY1_BASE_ADDRESS: cryp key1 base address
      \arg        CRYP_KEY2_BASE_ADDRESS: cryp key2 base address
    \param[in]  data: data buffer to program. data buffer is four double-word
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_cryp_key_config(uint32_t address, uint64_t data[])
{
    uint8_t index;
    fmc_state_enum fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_CRYP_KEY_ADDRESS(address)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x002AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* program the four double-word data */
        for(index = 0U; index < 4U; index++) {
            /* program a double word */
            fmc_state = hsm_otp_doubleword_program(address, data[index]);
            address += 8U;
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      HSM SPC key configuration in HSM OTP (API_ID(0x002BU))
    \param[in]  data: data buffer to program. data buffer is two double-word
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_spc_key_config(uint64_t data[])
{
    uint8_t index;
    uint32_t address = SPC_KEY_BASE_ADDRESS;
    fmc_state_enum  fmc_state = FMC_READY;

    /* program the two double-word data */
    for(index = 0U; index < 2U; index++) {
        /* program a double word */
        fmc_state = hsm_otp_doubleword_program(address, data[index]);
        address += 8U;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      unlock SPC protection with SPC key (API_ID(0x002CU))
    \param[in]  key: Password of unlock SPC
    \param[out] none
    \retval     none
*/
void spc_unlock(uint32_t key[])
{
    uint8_t index;

    /* program the two double-word data */
    for(index = 0U; index < 4U; index++) {
        /* program a double word */
        FMC_SPCKEY = key[index];
    }
}

/*!
    \brief      configure HSM bank0 / bank1 size (API_ID(0x002DU))
    \param[in]  hsm_size: HSM bank0 / bank1 size
                only one parameter can be selected which is shown as below:
      \arg        HSM_BANK_SIZE_NONE: HSM bank size is none
      \arg        HSM_BANK_SIZE_16K: HSM bank size is 16K
      \arg        HSM_BANK_SIZE_32K: HSM bank size is 32K
      \arg        HSM_BANK_SIZE_48K: HSM bank size is 48K
      \arg        HSM_BANK_SIZE_64K: HSM bank size is 64K
      \arg        HSM_BANK_SIZE_80K: HSM bank size is 80K
      \arg        HSM_BANK_SIZE_96K: HSM bank size is 96K
      \arg        HSM_BANK_SIZE_112K: HSM bank size is 112K
      \arg        HSM_BANK_SIZE_128K: HSM bank size is 128K
      \arg        HSM_BANK_SIZE_144K: HSM bank size is 144K
      \arg        HSM_BANK_SIZE_160K: HSM bank size is 160K
      \arg        HSM_BANK_SIZE_176K: HSM bank size is 176K
      \arg        HSM_BANK_SIZE_192K: HSM bank size is 192K
      \arg        HSM_BANK_SIZE_208K: HSM bank size is 208K
      \arg        HSM_BANK_SIZE_224K: HSM bank size is 224K
      \arg        HSM_BANK_SIZE_240K: HSM bank size is 240K
      \arg        HSM_BANK_SIZE_256K: HSM bank size is 256K
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_bank_size_config(uint64_t hsm_size)
{
    fmc_state_enum reval = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_HSM_BANK_SIZE(hsm_size)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x002DU), ERR_PARAM_INVALID);
    } else
#endif
    {
        reval = hsm_otp_doubleword_program(HSM_SIZE_ADDRESS, (uint64_t)hsm_size);
    }
    /* return the FMC state */
    return reval;
}

/*!
    \brief      HSM security enable (API_ID(0x002EU))
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_sec_enable(void)
{
    /* return the FMC state */
    return hsm_otp_doubleword_program(HSM_SEC_ADDRESS, (uint64_t)0xFFFFAA);
}

/*!
    \brief      HSM factory test mode disable (API_ID(0x002FU))
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
fmc_state_enum hsm_factory_disable(void)
{
    /* return the FMC state */
    return hsm_otp_doubleword_program(HSM_SEC_ADDRESS, (uint64_t)0xAAFFFF);
}

/*!
    \brief      HSM bank0 / bank1 size get (API_ID(0x0030U))
    \param[in]  none
    \param[out] none
    \retval     HSM bank0 / bank1 size, 0x00000000 ~ 0x00040000
*/
uint32_t hsm_bank_size_get(void)
{
    uint32_t size_value = (FMC_HSMWP & FMC_HSMWP_HSMSIZE) >> 16U;

    if(0x1FU == size_value) {
        /* 0x1F: HSM bank 0 / bank 1 size is 0 KB */
        size_value = 0U;
    } else if(0x10U <= size_value) {
        /* 0x10-0x1E: HSM bank 0 / bank 1 size is 256KB */
        size_value = 0x40000U;
    } else {
        /* 0x00-0x0F: HSM bank 0 / bank 1 size is HSMSIZE*16K */
        size_value *= 0x4000U;
    }

    return size_value;
}

/*!
    \brief      force to reload the HOST and HSM option bytes (API_ID(0x0031U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ob_reset(void)
{
    /* lock CTL0 */
    fmc_ctl0_unlock();
    /* set the OBRLD bit */
    FMC_CTL0 |= FMC_CTL0_OBRLD;
}

/*!
    \brief      erase the HOST option bytes (API_ID(0x0032U))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum ob_erase(void)
{
    uint32_t temp_spc_user = OB_SPC_USER;
    fmc_state_enum  fmc_state;

    /* check the option bytes security protection value */
    if(OB_OBSTAT_PLEVEL_HIGH == ob_plevel_get()) {
        fmc_state =  FMC_OB_HSPC;
    } else {
        /* wait for the FMC ready */
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            fmc_ctl0_unlock();
            /* write OPT logic address */
            FMC_ADDR0 = OB;
            /* start erase the option bytes */
            FMC_CTL0 |= FMC_CTL0_PER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl0_unlock();
            /* reset the PER bit */
            FMC_CTL0 &= ~FMC_CTL0_PER;

            if(FMC_READY == fmc_state) {
                /* set the PG bit */
                FMC_CTL0 |= FMC_CTL0_PG;
                /* restore the previous security protection configuration */
                FMC_WDATL0 = (temp_spc_user & LOW_8BITS_MASK) | LOW_8BITS_MASK1;
                FMC_WDATH0 = 0xFFFFFFFFU;
                FMC_ADDR0 = OB;
                FMC_CTL0 |= FMC_CTL0_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl0_unlock();
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }

            /* lock CTL0 */
            fmc_ctl0_lock();
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure HOST option bytes write protection (API_ID(0x0033U))
    \param[in]  wp_area: write protection area
                only one parameter can be selected which is shown as below:
      \arg        BANK0_AREA: main flash bank0 write protection area, the valid width of ob_wp is bit 31 to 0
      \arg        BANK1_AREA: main flash bank1 write protection area, the valid width of ob_wp is bit 31 to 0
      \arg        DATA_FLASH_AREA: data flash write protection area, the valid width of ob_wp is bit 7 to 0
    \param[in]  ob_wp: write protection configuration data. Notice that set the bit to 0 if you want to protect
                the corresponding pages. Other bits except the valid should be 1.
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum ob_write_protection_config(fmc_area_enum wp_area, uint32_t ob_wp)
{
    uint32_t i;
    uint32_t op_byte[OB_WORD_CNT] = {0};
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_HOST_AREA(wp_area)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0033U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the option bytes security protection value */
        if(OB_OBSTAT_PLEVEL_HIGH == ob_plevel_get()) {
            fmc_state =  FMC_OB_HSPC;
        } else {
            /* read option bytes */
            for(i = 0U; i < OB_WORD_CNT; i++) {
                op_byte[i] = OP_BYTE(i);
            }

            if(BANK0_AREA == wp_area) {
                /* configure write protection to main flash bank0 area -- 0x1FFFF808 */
                op_byte[2] = (ob_wp & LOW_8BITS_MASK) | ((ob_wp & HIGH_8BITS_MASK) << 8U);
                op_byte[3] = ((ob_wp & LOW_8BITS_MASK1) >> 16U) | ((ob_wp & HIGH_8BITS_MASK1) >> 8U);
            } else if(BANK1_AREA == wp_area) {
                /* configure write protection to main flash bank1 area -- 0x1FFFF810 */
                op_byte[4] = (ob_wp & LOW_8BITS_MASK) | ((ob_wp & HIGH_8BITS_MASK) << 8U);
                op_byte[5] = ((ob_wp & LOW_8BITS_MASK1) >> 16U) | ((ob_wp & HIGH_8BITS_MASK1) >> 8U);
            } else {
                /* configure write protection to HOST data flash area -- 0x1FFFF828 */
                op_byte[10] = (ob_wp & LOW_8BITS_MASK) | HIGH_16BITS_MASK;
            }

            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl0_unlock();
                /* write OPT logic address */
                FMC_ADDR0 = OB;
                /* start erase the option bytes */
                FMC_CTL0 |= FMC_CTL0_PER;
                FMC_CTL0 |= FMC_CTL0_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

                fmc_ctl0_unlock();
                /* reset the PER bit */
                FMC_CTL0 &= ~FMC_CTL0_PER;

                if(FMC_READY == fmc_state) {
                    /* set the PG bit */
                    FMC_CTL0 |= FMC_CTL0_PG;
                    /* write option bytes */
                    for(i = 0U; i < OB_DOUBLEWORD_CNT; i++) {
                        FMC_WDATL0 = op_byte[i * 2U];
                        FMC_WDATH0 = op_byte[i * 2U + 1U];
                        FMC_ADDR0 = OB + i * 8U;
                        FMC_CTL0 |= FMC_CTL0_START;
                        /* wait for the FMC ready */
                        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                        if(FMC_READY != fmc_state) {
                            break;
                        }
                        fmc_ctl0_unlock();
                    }
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                    fmc_ctl0_unlock();
                    /* reset the PG bit */
                    FMC_CTL0 &= ~FMC_CTL0_PG;
                }
            }

            /* lock CTL0 */
            fmc_ctl0_lock();
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure HOST system security protection (API_ID(0x0034U))
    \param[in]  ob_spc: specify security protection code
                only one parameter can be selected which is shown as below:
      \arg        FMC_NSPC: no security protection
      \arg        FMC_LSPC: low security protection
      \arg        FMC_HSPC: high security protection
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum ob_security_protection_config(uint16_t ob_spc)
{
    uint32_t i;
    uint32_t op_byte[OB_WORD_CNT] = {0};
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_SPC_VALUE(ob_spc)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0034U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the option bytes security protection value */
        if(OB_OBSTAT_PLEVEL_HIGH == ob_plevel_get()) {
            fmc_state = FMC_OB_HSPC;
        } else {
            /* read option bytes */
            for(i = 0U; i < OB_WORD_CNT; i++) {
                op_byte[i] = OP_BYTE(i);
            }

            op_byte[0] = ((uint32_t)(ob_spc)) | ((op_byte[0] & HIGH_16BITS_MASK));
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl0_unlock();
                /* write OPT logic address */
                FMC_ADDR0 = OB;
                /* start erase the option bytes */
                FMC_CTL0 |= FMC_CTL0_PER;
                FMC_CTL0 |= FMC_CTL0_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl0_unlock();
                /* reset the PER bit */
                FMC_CTL0 &= ~FMC_CTL0_PER;

                if(FMC_READY == fmc_state) {
                    /* enable the option bytes programming */
                    FMC_CTL0 |= FMC_CTL0_PG;
                    /* write option bytes */
                    for(i = 0U; i < OB_DOUBLEWORD_CNT; i++) {
                        FMC_WDATL0 = op_byte[i * 2U];
                        FMC_WDATH0 = op_byte[i * 2U + 1U];
                        FMC_ADDR0 = OB + i * 8U;
                        FMC_CTL0 |= FMC_CTL0_START;
                        /* wait for the FMC ready */
                        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                        if(FMC_READY != fmc_state) {
                            break;
                        }
                        fmc_ctl0_unlock();
                    }
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                    fmc_ctl0_unlock();
                    /* reset the PG bit */
                    FMC_CTL0 &= ~FMC_CTL0_PG;
                }
            }

            /* lock CTL0 */
            fmc_ctl0_lock();
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program the user HOST option bytes (API_ID(0x0035U))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
                this function can only clear the corresponding bits to be 0 rather than 1.
                the function ob_erase is used to set all the bits to be 1.
    \param[in]  ob_user: user option bytes
                one or more (bitwise OR) parameters can be selected which are shown as below:
      \arg        OB_FWDGT0_HW/OB_FWDGT0_SW: free watchdog 0 mode
      \arg        OB_STDBY_RST/OB_STDBY_NRST: generate a reset or enter standby mode
      \arg        OB_FWDGT1_HW/OB_FWDGT1_SW: free watchdog 1 mode
      \arg        OB_FWDG_STDBY_STOP/OB_FWDG_STDBY_CONT: free watchdog 0/1 stop or continue counting in standby mode
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum ob_user_write(uint16_t ob_user)
{
    uint32_t i;
    uint32_t op_byte[OB_WORD_CNT] = {0};
    uint8_t ob_user_0, ob_user_1, ob_user_temp;
    fmc_state_enum fmc_state;

    /* check the option bytes security protection value */
    if(OB_OBSTAT_PLEVEL_HIGH == ob_plevel_get()) {
        fmc_state =  FMC_OB_HSPC;
    } else {
        ob_user_0 = (uint8_t)(ob_user >> 8U);
        ob_user_1 = (uint8_t)(ob_user & 0xFFU);

        /* read option bytes */
        for(i = 0U; i < OB_WORD_CNT; i++) {
            op_byte[i] = OP_BYTE(i);
        }

        ob_user_temp = (uint8_t)(op_byte[0] >> 16U);
        ob_user_temp |= ob_user_1;
        ob_user_temp &= (uint8_t)(~ob_user_0);
        op_byte[0] = ((uint32_t)ob_user_temp << 16U) | ((op_byte[0] & LOW_16BITS_MASK));
        /* check whether FMC is ready or not */
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            fmc_ctl0_unlock();
            /* write OPT logic address */
            FMC_ADDR0 = OB;
            /* start erase the option bytes */
            FMC_CTL0 |= FMC_CTL0_PER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl0_unlock();
            /* reset the PER bit */
            FMC_CTL0 &= ~FMC_CTL0_PER;

            if(FMC_READY == fmc_state) {
                /* enable the option bytes programming */
                FMC_CTL0 |= FMC_CTL0_PG;
                /* write option bytes */
                for(i = 0U; i < OB_DOUBLEWORD_CNT; i++) {
                    FMC_WDATL0 = op_byte[i * 2U];
                    FMC_WDATH0 = op_byte[i * 2U + 1U];
                    FMC_ADDR0 = OB + i * 8U;
                    FMC_CTL0 |= FMC_CTL0_START;
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                    if(FMC_READY != fmc_state) {
                        break;
                    }
                    fmc_ctl0_unlock();
                }
                /* wait for the FMC ready */
                fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }

        /* lock CTL0 */
        fmc_ctl0_lock();
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program the data HOST option bytes (API_ID(0x0036U))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  ob_data: the data to be programmed, OB_DATA[0:15]
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum ob_data_program(uint16_t ob_data)
{
    uint32_t i;
    uint32_t val;
    uint32_t op_byte[OB_WORD_CNT] = {0};
    fmc_state_enum fmc_state;

    /* check the option bytes security protection value */
    if(OB_OBSTAT_PLEVEL_HIGH == ob_plevel_get()) {
        fmc_state =  FMC_OB_HSPC;
    } else {
        /* read option bytes */
        for(i = 0U; i < OB_WORD_CNT; i++) {
            op_byte[i] = OP_BYTE(i);
        }

        val = (uint32_t)(ob_data & LOW_8BITS_MASK);
        val |= ((uint32_t)ob_data & HIGH_8BITS_MASK) << 8U;
        op_byte[1] = val;
        /* wait for the FMC ready */
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            fmc_ctl0_unlock();
            /* write OPT logic address */
            FMC_ADDR0 = OB;
            /* start erase the option bytes */
            FMC_CTL0 |= FMC_CTL0_PER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl0_unlock();
            /* reset the PER bit */
            FMC_CTL0 &= ~FMC_CTL0_PER;

            if(FMC_READY == fmc_state) {
                /* set the OB0PG bit */
                FMC_CTL0 |= FMC_CTL0_PG;
                /* write option bytes */
                for(i = 0U; i < OB_DOUBLEWORD_CNT; i++) {
                    FMC_WDATL0 = op_byte[i * 2U];
                    FMC_WDATH0 = op_byte[i * 2U + 1U];
                    FMC_ADDR0 = OB + i * 8U;
                    FMC_CTL0 |= FMC_CTL0_START;
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                    if(FMC_READY != fmc_state) {
                        break;
                    }
                    fmc_ctl0_unlock();
                }
                /* wait for the FMC ready */
                fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the OB0PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }

        /* lock CTL0 */
        fmc_ctl0_lock();
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program the cltcfg HOST option bytes (API_ID(0x0037U))
    \param[in]  ob_cltcfg: cltcfg module configuration data, the valid width is bit 47 to 0
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum ob_cltcfg_config(uint64_t ob_cltcfg)
{
    uint32_t i;
    uint32_t op_byte[OB_WORD_CNT] = {0};
    fmc_state_enum  fmc_state;

    /* check the option bytes security protection value */
    if(OB_OBSTAT_PLEVEL_HIGH == ob_plevel_get()) {
        fmc_state = FMC_OB_HSPC;
    } else {
        /* read option bytes */
        for(i = 0U; i < OB_WORD_CNT; i++) {
            op_byte[i] = OP_BYTE(i);
        }

        /* configure CLTCFG data [23:0] -- 0x1FFFF82A */
        op_byte[10] = (uint32_t)(((ob_cltcfg & LOW_8BITS_MASK) << 16) | LOW_8BITS_MASK);
        op_byte[11] = (uint32_t)(((ob_cltcfg & HIGH_8BITS_MASK) >> 8) | (ob_cltcfg & LOW_8BITS_MASK1));
        /* configure CLTCFG data [47:24] -- 0x1FFFF830 */
        op_byte[12] = (uint32_t)(((ob_cltcfg >> 24) & LOW_8BITS_MASK) | (((ob_cltcfg >> 24) &
                                                                          HIGH_8BITS_MASK) << 8));
        op_byte[13] = (uint32_t)(((ob_cltcfg >> 24) & LOW_8BITS_MASK1) >> 16) | HIGH_16BITS_MASK;
        /* wait for the FMC ready */
        fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            fmc_ctl0_unlock();
            /* write OPT logic address */
            FMC_ADDR0 = OB;
            /* start erase the option bytes */
            FMC_CTL0 |= FMC_CTL0_PER;
            FMC_CTL0 |= FMC_CTL0_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl0_unlock();
            /* reset the PER bit */
            FMC_CTL0 &= ~FMC_CTL0_PER;

            if(FMC_READY == fmc_state) {
                /* set the PG bit */
                FMC_CTL0 |= FMC_CTL0_PG;
                /* write option bytes */
                for(i = 0U; i < OB_DOUBLEWORD_CNT; i++) {
                    FMC_WDATL0 = op_byte[i * 2U];
                    FMC_WDATH0 = op_byte[i * 2U + 1U];
                    FMC_ADDR0 = OB + i * 8U;
                    FMC_CTL0 |= FMC_CTL0_START;
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                    if(FMC_READY != fmc_state) {
                        break;
                    }
                    fmc_ctl0_unlock();
                }
                /* wait for the FMC ready */
                fmc_state = fmc_ctl0_ready_wait(FMC_TIMEOUT_COUNT);
                /* reset the PG bit */
                FMC_CTL0 &= ~FMC_CTL0_PG;
            }
        }

        /* lock CTL0 */
        fmc_ctl0_lock();
    }

    /* return the FMC state */
    return fmc_state;
}


/*!
    \brief      get the value of FMC option bytes OB_USER in FMC_OBSTAT register (API_ID(0x0038U))
    \param[in]  none
    \param[out] none
    \retval     the option bytes USER value,0x00-0xFF
*/
uint8_t ob_user_get(void)
{
    return (uint8_t)((FMC_OBSTAT & FMC_OBSTAT_USER) >> OBSTAT_USER_OFFSET);
}

/*!
    \brief      get the value of FMC option bytes OB_DATA in FMC_OBSTAT register (API_ID(0x0039U))
    \param[in]  none
    \param[out] none
    \retval     the option bytes DATA value, 0x0000-0xFFFF
*/
uint16_t ob_data_get(void)
{
    return (uint16_t)((FMC_OBSTAT & FMC_OBSTAT_DATA) >> OBSTAT_DATA_OFFSET);
}

/*!
    \brief      get the value of FMC option bytes BK0WP in FMC_WP0 register (API_ID(0x003AU))
    \param[in]  none
    \param[out] none
    \retval     the option bytes BK0WP value, 0x00000000-0xFFFFFFFF
*/
uint32_t ob_bk0_write_protection_get(void)
{
    return (uint32_t)(FMC_WP0);
}

/*!
    \brief      get the value of FMC option bytes BK1WP in FMC_WP1 register (API_ID(0x003BU))
    \param[in]  none
    \param[out] none
    \retval     the option bytes BK1WP value, 0x00000000-0xFFFFFFFF
*/
uint32_t ob_bk1_write_protection_get(void)
{
    return (uint32_t)(FMC_WP1);
}

/*!
    \brief      get the value of FMC option bytes DFWP in FMC_WP2 register (API_ID(0x003CU))
    \param[in]  none
    \param[out] none
    \retval     the option bytes DFWP value, 0x00-0xFF
*/
uint8_t ob_df_write_protection_get(void)
{
    return (uint8_t)(FMC_WP2);
}

/*!
    \brief      get the value of FMC option bytes security protection level (PLEVEL) in FMC_OBSTAT register (API_ID(0x003DU))
    \param[in]  none
    \param[out] none
    \retval     the value of PLEVEL
      \arg        OB_OBSTAT_PLEVEL_NO: no security protection
      \arg        OB_OBSTAT_PLEVEL_LOW: low security protection
      \arg        OB_OBSTAT_PLEVEL_HIGH: high security protection
*/
uint8_t ob_plevel_get(void)
{
    return (uint8_t)((FMC_OBSTAT & FMC_OBSTAT_PLEVEL) >> OBSTAT_PLEVEL_OFFSET);
}

/*!
    \brief      erase the HSM option bytes (API_ID(0x003EU))
                programmer must ensure FMC & option bytes are both unlocked before calling this function
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
      \arg        FMC_HSMOB_HSPC: FMC HSM system is under high security protection
*/
fmc_state_enum hsm_ob_erase(void)
{
    uint32_t temp_spc_user = OB_HSMSPC;
    fmc_state_enum  fmc_state;

    /* check the option bytes security protection value */
    if(HSM_OBSTAT_PLEVEL_HIGH == hsm_ob_spc_get()) {
        fmc_state =  FMC_HSMOB_HSPC;
    } else {
        /* wait for the FMC ready */
        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

        if(FMC_READY == fmc_state) {
            fmc_ctl1_unlock();
            /* write OPT logic address */
            FMC_ADDR1 = HSM_OB;
            /* start erase the option bytes */
            FMC_CTL1 |= FMC_CTL1_PER;
            FMC_CTL1 |= FMC_CTL1_START;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
            fmc_ctl1_unlock();
            /* reset the PER bit */
            FMC_CTL1 &= ~FMC_CTL1_PER;

            if(FMC_READY == fmc_state) {
                /* set the PG bit */
                FMC_CTL1 |= FMC_CTL1_PG;
                /* restore the previous HSM size and security protection configuration */
                FMC_WDATL1 = (uint32_t)((temp_spc_user << 16) | LOW_16BITS_MASK);
                FMC_WDATH1 = 0xFFFFFFFFU;
                FMC_ADDR1 = HSM_OB;
                FMC_CTL1 |= FMC_CTL1_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl1_unlock();
                /* reset the PG bit */
                FMC_CTL1 &= ~FMC_CTL1_PG;
            }
        }

        /* lock CTL1 */
        fmc_ctl1_lock();
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      initialize the hsm option bytes parameters struct with the default values (API_ID(0x003FU))
    \param[in]  init_struct: the initialization data needed to initialize hsm option bytes
    \param[out] none
    \retval     none
*/
void hsm_ob_para_struct_init(fmc_hsm_opt_parameter_struct *init_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(init_struct)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x003FU), ERR_PARAM_POINTER);
    } else
#endif
    {
        init_struct->ob_hsmuser.hsm_user = 0xFF;
        init_struct->ob_hsmspc = 0xA5;
        init_struct->ob_hsmpfwp = 0xFF;
        init_struct->ob_hsmdfwp = 0xFF;
    }
}

/*!
    \brief      configure HSM option bytes (API_ID(0x0040U))
    \param[in]  hsmob: the data needed to initialize hsm option bytes
                  ob_hsmuser: hsm option bytes hsmuser fields
                  ob_hsmspc: hsm option bytes hsmspc fields
                  ob_hsmpfwp: hsm option bytes hsmpfwp fields
                  ob_hsmdfwp: hsm option bytes hsmdfwp fields
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum hsm_ob_config(fmc_hsm_opt_parameter_struct *hsmob)
{
    uint32_t i;
    uint32_t hsmop_byte[HSM_OB_WORD_CNT] = {0};
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(hsmob)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0040U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* check the HSM option bytes security protection value */
        if(HSM_OBSTAT_PLEVEL_HIGH == hsm_ob_spc_get()) {
            fmc_state =  FMC_HSMOB_HSPC;
        } else {
            /* modify HSM option bytes */
            hsmop_byte[0] = ((uint32_t)(hsmob->ob_hsmuser.hsm_user) | ((uint32_t)hsmob->ob_hsmspc << 16U));
            hsmop_byte[1] = ((uint32_t)(hsmob->ob_hsmpfwp) | ((uint32_t)hsmob->ob_hsmdfwp << 16U));

            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl1_unlock();
                /* write HSM OPT logic address */
                FMC_ADDR1 = HSM_OB;
                /* start erase the option bytes */
                FMC_CTL1 |= FMC_CTL1_PER;
                FMC_CTL1 |= FMC_CTL1_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl1_unlock();
                /* reset the PER bit */
                FMC_CTL1 &= ~FMC_CTL1_PER;

                if(FMC_READY == fmc_state) {
                    /* set the PG bit */
                    FMC_CTL1 |= FMC_CTL1_PG;

                    /* write option bytes */
                    for(i = 0U; i < HSM_OB_DOUBLEWORD_CNT; i++) {
                        FMC_WDATL1 = hsmop_byte[i * 2U];
                        FMC_WDATH1 = hsmop_byte[i * 2U + 1U];
                        FMC_ADDR1 = HSM_OB + i * 8U;
                        FMC_CTL1 |= FMC_CTL1_START;
                        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                        if(FMC_READY != fmc_state) {
                            break;
                        }
                        fmc_ctl1_unlock();
                    }
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PG bit */
                    FMC_CTL1 &= ~FMC_CTL1_PG;
                }
            }

            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure HSM option bytes write protection (API_ID(0x0041U))
    \param[in]  wp_area: write protection area
                only one parameter can be selected which is shown as below:
      \arg        HSM_BANK_AREA: HSM bank0/bank1 write protection area
      \arg        HSM_DATA_AREA: HSM data flash write protection areas
    \param[in]  ob_wp: write protection configuration data. Notice that set the bit to 0 if you want to protect
                the corresponding pages. Other bits except the valid should be 1.
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum hsm_ob_write_protection_config(fmc_area_enum wp_area, uint8_t ob_hsmwp)
{
    uint32_t i;
    uint32_t hsmop_byte[HSM_OB_WORD_CNT] = {0U};
    uint32_t wp_temp;
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_HSM_AREA(wp_area)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0041U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the option bytes security protection value */
        if(HSM_OBSTAT_PLEVEL_HIGH == hsm_ob_spc_get()) {
            fmc_state =  FMC_HSMOB_HSPC;
        } else {
            /* read option bytes */
            for(i = 0U; i < HSM_OB_WORD_CNT; i++) {
                hsmop_byte[i] = HSMOP_BYTE(i);
            }

            if(HSM_BANK_AREA == wp_area) {
                /* configure write protection to HSM Pflash area -- 0x1FFFF884 */
                wp_temp = hsmop_byte[1] & 0xFFFFFF00U;
                hsmop_byte[1] = (wp_temp | ob_hsmwp);
            } else {
                /* configure write protection to HSM Dflash area -- 0x1FFFF886 */
                wp_temp = hsmop_byte[1] & 0xFF00FFFFU;
                hsmop_byte[1] = (wp_temp | (((uint32_t)ob_hsmwp) << 16U));
            }

            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl1_unlock();
                /* write HSM OPT logic address */
                FMC_ADDR1 = HSM_OB;
                /* start erase the option bytes */
                FMC_CTL1 |= FMC_CTL1_PER;
                FMC_CTL1 |= FMC_CTL1_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl1_unlock();
                /* reset the PER bit */
                FMC_CTL1 &= ~FMC_CTL1_PER;

                if(FMC_READY == fmc_state) {
                    /* set the PG bit */
                    FMC_CTL1 |= FMC_CTL1_PG;
                    /* write option bytes */
                    for(i = 0U; i < HSM_OB_DOUBLEWORD_CNT; i++) {
                        FMC_WDATL1 = hsmop_byte[i * 2U];
                        FMC_WDATH1 = hsmop_byte[i * 2U + 1U];
                        FMC_ADDR1 = HSM_OB + i * 8U;
                        FMC_CTL1 |= FMC_CTL1_START;
                        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

                        if(FMC_READY != fmc_state) {
                            break;
                        }
                        fmc_ctl1_unlock();
                    }
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                    fmc_ctl1_unlock();
                    /* reset the PG bit */
                    FMC_CTL1 &= ~FMC_CTL1_PG;
                }
            }

            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure security protection in HSM option bytes (API_ID(0x0042U))
    \param[in]  ob_spc: specify security protection code
                only one parameter can be selected which is shown as below:
      \arg        HSM_NSPC: no security protection
      \arg        HSM_LSPC: low security protection
      \arg        HSM_HSPC: high security protection
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum hsm_ob_security_protection_config(uint16_t ob_hsmspc)
{
    uint32_t i;
    uint32_t hsmop_byte[HSM_OB_WORD_CNT] = {0};
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_HSM_SPC_VALUE(ob_hsmspc)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0042U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the option bytes security protection value */
        if(HSM_OBSTAT_PLEVEL_HIGH == hsm_ob_spc_get()) {
            fmc_state =  FMC_HSMOB_HSPC;
        } else {
            /* read option bytes */
            for(i = 0U; i < HSM_OB_WORD_CNT; i++) {
                hsmop_byte[i] = HSMOP_BYTE(i);
            }

            hsmop_byte[0] = ((uint32_t)((uint32_t)ob_hsmspc << 16U)) | LOW_16BITS_MASK;
            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl1_unlock();
                /* write HSM OPT logic address */
                FMC_ADDR1 = HSM_OB;
                /* start erase the option bytes */
                FMC_CTL1 |= FMC_CTL1_PER;
                FMC_CTL1 |= FMC_CTL1_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl1_unlock();
                /* reset the PER bit */
                FMC_CTL1 &= ~FMC_CTL1_PER;

                if(FMC_READY == fmc_state) {
                    /* set the PG bit */
                    FMC_CTL1 |= FMC_CTL1_PG;
                    /* write option bytes */
                    for(i = 0U; i < HSM_OB_DOUBLEWORD_CNT; i++) {
                        FMC_WDATL1 = hsmop_byte[i * 2U];
                        FMC_WDATH1 = hsmop_byte[i * 2U + 1U];
                        FMC_ADDR1 = HSM_OB + i * 8U;
                        FMC_CTL1 |= FMC_CTL1_START;
                        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                        if(FMC_READY != fmc_state) {
                            break;
                        }
                        fmc_ctl1_unlock();
                    }
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                    fmc_ctl1_unlock();
                    /* reset the PG bit */
                    FMC_CTL1 &= ~FMC_CTL1_PG;
                }
            }

            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure swap in HSM option bytes (API_ID(0x0043U))
    \param[in]  hsmob_swap: user option bytes
                only one parameter parameters can be selected which are shown as below:
      \arg        HSM_OB_SWAP_PFLASH0: bank0 and HSM bank 0 at Pflash0, bank1 and HSM bank 1 at Pflash1
      \arg        HSM_OB_SWAP_PFLASH1: After swap, bank0 and HSM bank 0 at Pflash1, bank1 and HSM bank 1 at Pflash0
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum hsm_ob_swap_config(uint16_t hsmob_swap)
{
    uint32_t i;
    uint32_t hsmop_byte[HSM_OB_WORD_CNT] = {0};
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_HSM_SWAP_VALUE(hsmob_swap)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0043U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the HSM option bytes security protection value */
        if(HSM_OBSTAT_PLEVEL_HIGH == hsm_ob_spc_get()) {
            fmc_state =  FMC_HSMOB_HSPC;
        } else {
            /* read HSM option bytes */
            for(i = 0U; i < HSM_OB_WORD_CNT; i++) {
                hsmop_byte[i] = HSMOP_BYTE(i);
            }

            if(HSM_OB_SWAP_PFLASH1 == hsmob_swap) {
                hsmop_byte[0] &= (uint32_t)(~hsmob_swap);
            } else {
                hsmop_byte[0] |= (uint32_t)((uint32_t)hsmob_swap >> 8U);
            }

            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl1_unlock();
                /* write HSM OPT logic address */
                FMC_ADDR1 = HSM_OB;
                /* start erase the option bytes */
                FMC_CTL1 |= FMC_CTL1_PER;
                FMC_CTL1 |= FMC_CTL1_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl1_unlock();
                /* reset the PER bit */
                FMC_CTL1 &= ~FMC_CTL1_PER;

                if(FMC_READY == fmc_state) {
                    /* set the PG bit */
                    FMC_CTL1 |= FMC_CTL1_PG;

                    /* write option bytes */
                    for(i = 0U; i < HSM_OB_DOUBLEWORD_CNT; i++) {
                        FMC_WDATL1 = hsmop_byte[i * 2U];
                        FMC_WDATH1 = hsmop_byte[i * 2U + 1U];
                        FMC_ADDR1 = HSM_OB + i * 8U;
                        FMC_CTL1 |= FMC_CTL1_START;
                        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                        if(FMC_READY != fmc_state) {
                            break;
                        }
                        fmc_ctl1_unlock();
                    }
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PG bit */
                    FMC_CTL1 &= ~FMC_CTL1_PG;
                }
            }

            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      configure window watchdog in HSM option bytes (API_ID(0x0044U))
    \param[in]  hsmob_user: user option bytes
                only one parameter parameters can be selected which are shown as below:
      \arg        HSM_OB_WWDG_HW: HSM hardware window watchdog
      \arg        HSM_OB_WWDG_SW: HSM software window watchdog
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum hsm_ob_wwdg_config(uint16_t hsmob_wwdg)
{
    uint32_t i;
    uint32_t hsmop_byte[HSM_OB_WORD_CNT] = {0};
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_HSM_WWDG_VALUE(hsmob_wwdg)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0044U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the HSM option bytes security protection value */
        if(HSM_OBSTAT_PLEVEL_HIGH == hsm_ob_spc_get()) {
            fmc_state = FMC_HSMOB_HSPC;
        } else {
            /* read HSM option bytes */
            for(i = 0U; i < HSM_OB_WORD_CNT; i++) {
                hsmop_byte[i] = HSMOP_BYTE(i);
            }

            if(HSM_OB_WWDG_HW == hsmob_wwdg) {
                hsmop_byte[0] &= (uint32_t)(~(hsmob_wwdg >> 8U));
            } else {
                hsmop_byte[0] |= (uint32_t)(hsmob_wwdg);
            }

            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl1_unlock();
                /* write HSM OPT logic address */
                FMC_ADDR1 = HSM_OB;
                /* start erase the option bytes */
                FMC_CTL1 |= FMC_CTL1_PER;
                FMC_CTL1 |= FMC_CTL1_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl1_unlock();
                /* reset the PER bit */
                FMC_CTL1 &= ~FMC_CTL1_PER;

                if(FMC_READY == fmc_state) {
                    /* set the PG bit */
                    FMC_CTL1 |= FMC_CTL1_PG;
                    /* write option bytes */
                    for(i = 0U; i < HSM_OB_DOUBLEWORD_CNT; i++) {
                        FMC_WDATL1 = hsmop_byte[i * 2U];
                        FMC_WDATH1 = hsmop_byte[i * 2U + 1U];
                        FMC_ADDR1 = HSM_OB + i * 8U;
                        FMC_CTL1 |= FMC_CTL1_START;
                        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                        if(FMC_READY != fmc_state) {
                            break;
                        }
                        fmc_ctl1_unlock();
                    }
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PG bit */
                    FMC_CTL1 &= ~FMC_CTL1_PG;
                }
            }

            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      program the user data in HSM option bytes (API_ID(0x0045U))
    \param[in]  hsmob_user: the data to be programmed, OB_HSM_USER[5:0]
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
      \arg        FMC_OB_HSPC: FMC is under high security protection
*/
fmc_state_enum hsm_ob_user_write(uint8_t hsmob_user)
{
    uint32_t i;
    uint32_t hsmop_byte[HSM_OB_WORD_CNT] = {0};
    fmc_state_enum  fmc_state = FMC_READY;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_HSM_HSMUSER_VALUE(hsmob_user)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0045U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* check the HSM option bytes security protection value */
        if(HSM_OBSTAT_PLEVEL_HIGH == hsm_ob_spc_get()) {
            fmc_state = FMC_HSMOB_HSPC;
        } else {
            /* read HSM option bytes */
            for(i = 0U; i < HSM_OB_WORD_CNT; i++) {
                hsmop_byte[i] = HSMOP_BYTE(i);
            }

            hsmop_byte[0] &= ~(0x3FU);
            hsmop_byte[0] |= ((uint32_t)hsmob_user & 0x3FU);

            /* wait for the FMC ready */
            fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);

            if(FMC_READY == fmc_state) {
                fmc_ctl1_unlock();
                /* write HSM OPT logic address */
                FMC_ADDR1 = HSM_OB;
                /* start erase the option bytes */
                FMC_CTL1 |= FMC_CTL1_PER;
                FMC_CTL1 |= FMC_CTL1_START;
                /* wait for the FMC ready */
                fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                fmc_ctl1_unlock();
                /* reset the PER bit */
                FMC_CTL1 &= ~FMC_CTL1_PER;

                if(FMC_READY == fmc_state) {
                    /* set the PG bit */
                    FMC_CTL1 |= FMC_CTL1_PG;
                    /* write option bytes */
                    for(i = 0U; i < HSM_OB_DOUBLEWORD_CNT; i++) {
                        FMC_WDATL1 = hsmop_byte[i * 2U];
                        FMC_WDATH1 = hsmop_byte[i * 2U + 1U];
                        FMC_ADDR1 = HSM_OB + i * 8U;
                        FMC_CTL1 |= FMC_CTL1_START;
                        fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                        if(FMC_READY != fmc_state) {
                            break;
                        }
                        fmc_ctl1_unlock();
                    }
                    /* wait for the FMC ready */
                    fmc_state = fmc_ctl1_ready_wait(FMC_TIMEOUT_COUNT);
                    /* reset the PG bit */
                    FMC_CTL1 &= ~FMC_CTL1_PG;
                }
            }

            /* lock CTL1 */
            fmc_ctl1_lock();
        }
    }
    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      get the value of FMC HSM option bytes HSMPFWP in FMC_HSMWP register (API_ID(0x0046U))
    \param[in]  none
    \param[out] none
    \retval     the option bytes OB_HSMPFWP value (0x00 - 0xFF)
*/
uint8_t hsm_ob_pflash_write_protection_get(void)
{
    return (uint8_t)(FMC_HSMWP & FMC_HSMWP_HSMPFWP);
}

/*!
    \brief      get the value of FMC HSM option bytes HSMDFWP in FMC_HSMWP register (API_ID(0x0047U))
    \param[in]  none
    \param[out] none
    \retval     the option bytes OB_HSMDFWP value (0x00 - 0xFF)
*/
uint8_t hsm_ob_df_write_protection_get(void)
{
    return (uint8_t)((FMC_HSMWP & FMC_HSMWP_HSMDFWP) >> 8U);
}

/*!
    \brief      get the value of HSM option bytes security protection level in FMC_HSMOBSTAT register (API_ID(0x0048U))
    \param[in]  none
    \param[out] none
    \retval     the value of OB_HSMSPC
      \arg        HSM_OBSTAT_PLEVEL_NO: HSM system no security protection
      \arg        HSM_OBSTAT_PLEVEL_LOW: HSM system low security protection
      \arg        HSM_OBSTAT_PLEVEL_HIGH: HSM system high security protection
*/
uint8_t hsm_ob_spc_get(void)
{
    uint8_t spc_val = (uint8_t)((FMC_HSMOBSTAT & FMC_HSMOBSTAT_SPC) >> HSMOBSTAT_SPC_OFFSET);
    uint8_t hsm_ob_plevel;

    if((uint8_t)0xA5 == spc_val) {
        hsm_ob_plevel = HSM_OBSTAT_PLEVEL_NO;
    } else if((uint8_t)0xCC == spc_val) {
        hsm_ob_plevel = HSM_OBSTAT_PLEVEL_HIGH;
    } else {
        hsm_ob_plevel = HSM_OBSTAT_PLEVEL_LOW;
    }
    return hsm_ob_plevel;
}

/*!
    \brief      get the value of HSM option bytes BSWAP in FMC_HSMOBSTAT register (API_ID(0x0049U))
    \param[in]  none
    \param[out] none
    \retval     the value of BSWAP, 0 or 1
*/
uint8_t hsm_ob_swap_get(void)
{
    return (uint8_t)(((FMC_HSMOBSTAT >> 23U) & 0x01U));
}

/*!
    \brief      get FMC flag status (API_ID(0x004AU))
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_STAT0_FLAG_BUSY: flash stat0 busy flag
      \arg        FMC_STAT0_FLAG_PGSERR: flash stat0 program sequence error flag
      \arg        FMC_STAT0_FLAG_PGERR: flash stat0 program error flag
      \arg        FMC_STAT0_FLAG_WPERR: flash stat0 erase/program protection error flag
      \arg        FMC_STAT0_FLAG_END: flash stat0 end of operation flag
      \arg        FMC_STAT0_FLAG_CBCMDERR: flash stat0 checked area by the check blank command is all 0xFF or not flag
      \arg        FMC_STAT0_FLAG_LOADECCERR: uncorrected ECC error when load flag
      \arg        FMC_STAT0_FLAG_COMPERR: flash stat0 complement error flag
      \arg        FMC_STAT0_FLAG_TMRERR: flash stat0 TMR error flag
      \arg        FMC_STAT0_FLAG_RSTERR: flash stat0 POR or system reset during erase/program flag
      \arg        FMC_STAT1_FLAG_BUSY: flash stat1 busy flag
      \arg        FMC_STAT1_FLAG_PGSERR: flash stat1 program sequence error flag
      \arg        FMC_STAT1_FLAG_PGERR: flash stat1 program error flag
      \arg        FMC_STAT1_FLAG_WPERR: flash stat1 erase/program protection error flag
      \arg        FMC_STAT1_FLAG_END: flash stat1 end of operation flag
      \arg        FMC_STAT1_FLAG_CBCMDERR: flash stat1 checked area by the check blank command is all 0xFF or not flag
      \arg        FMC_STAT1_FLAG_TMRERR: flash stat1 TMR error flag
      \arg        FMC_STAT1_FLAG_RSTERR: flash bank1 POR or system reset during erase/program flag
      \arg        FMC_FLAG_OBERR: option bytes 0 error flag
      \arg        FMC_FLAG_HSMOBERR: option bytes 1 read error flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_flag_get(fmc_flag_enum flag)
{
    FlagStatus flag_temp = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_FLAG(flag)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x004AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* get flag */
        if(0U != (FMC_REG_VAL(flag) & BIT(FMC_BIT_POS(flag)))) {
            flag_temp =  SET;
        } else {
            flag_temp =  RESET;
        }
    }
    return flag_temp;
}

/*!
    \brief      clear FMC flag status (API_ID(0x004BU))
    \param[in]  flag: FMC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_STAT0_FLAG_PGSERR: flash stat0 program sequence error flag
      \arg        FMC_STAT0_FLAG_PGERR: flash stat0 program error flag
      \arg        FMC_STAT0_FLAG_WPERR: flash stat0 erase/program protection error flag
      \arg        FMC_STAT0_FLAG_END: flash stat0 end of operation flag
      \arg        FMC_STAT0_FLAG_CBCMDERR: flash stat0 checked area by the check blank command is all 0xFF or not flag
      \arg        FMC_STAT0_FLAG_LOADECCERR: uncorrected ECC error when load flag
      \arg        FMC_STAT0_FLAG_COMPERR: flash stat0 complement error flag
      \arg        FMC_STAT0_FLAG_RSTERR: flash stat0 POR or system reset during erase/program flag
      \arg        FMC_STAT1_FLAG_PGSERR: flash stat1 program sequence error flag
      \arg        FMC_STAT1_FLAG_PGERR: flash stat1 program error flag
      \arg        FMC_STAT1_FLAG_WPERR: flash stat1 erase/program protection error flag
      \arg        FMC_STAT1_FLAG_END: flash stat1 end of operation flag
      \arg        FMC_STAT1_FLAG_CBCMDERR: flash stat1 checked area by the check blank command is all 0xFF or not flag
      \arg        FMC_STAT1_FLAG_RSTERR: flash bank1 POR or system reset during erase/program flag
    \param[out] none
    \retval     none
*/
void fmc_flag_clear(fmc_flag_enum flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_CLEAR_FLAG(flag)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x004BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* clear the flags in STAT0/STAT1 register */
        FMC_REG_VAL(flag) = BIT(FMC_BIT_POS(flag));
    }
}

/*!
    \brief      enable FMC interrupt (API_ID(0x004CU))
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_CTL0_INT_ERR: FMC CTL0 error interrupt
      \arg        FMC_CTL0_INT_END: FMC CTL0 end of operation interrupt
      \arg        FMC_CTL1_INT_ERR: FMC CTL1 error interrupt
      \arg        FMC_CTL1_INT_END: FMC CTL1 end of operation interrupt

    \param[out] none
    \retval     none
*/
void fmc_interrupt_enable(fmc_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_INT(interrupt)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x004CU), ERR_PARAM_INVALID);
    } else
#endif
    {
        fmc_ctl0_unlock();
        /* enable interrupt in CTL0/CTL1 register */
        FMC_REG_VAL(interrupt) |= BIT(FMC_BIT_POS(interrupt));
        fmc_ctl0_lock();
    }
}

/*!
    \brief      disable FMC interrupt (API_ID(0x004DU))
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_CTL0_INT_ERR: FMC CTL0 error interrupt
      \arg        FMC_CTL0_INT_END: FMC CTL0 end of operation interrupt
      \arg        FMC_CTL1_INT_ERR: FMC CTL1 error interrupt
      \arg        FMC_CTL1_INT_END: FMC CTL1 end of operation interrupt

    \param[out] none
    \retval     none
*/
void fmc_interrupt_disable(fmc_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_INT(interrupt)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x004DU), ERR_PARAM_INVALID);
    } else
#endif
    {
        fmc_ctl0_unlock();
        /* disable interrupt in CTL0/CTL1 register */
        FMC_REG_VAL(interrupt) &= ~BIT(FMC_BIT_POS(interrupt));
        fmc_ctl0_lock();
    }
}

/*!
    \brief      get FMC interrupt flag status (API_ID(0x004EU))
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_STAT0_INT_FLAG_PGSERR: flash stat0 program sequence error interrupt flag
      \arg        FMC_STAT0_INT_FLAG_PGERR: flash stat0 program error interrupt flag
      \arg        FMC_STAT0_INT_FLAG_WPERR: flash stat0 erase/program protection error interrupt flag
      \arg        FMC_STAT0_INT_FLAG_END: flash stat0 end of operation interrupt flag
      \arg        FMC_STAT0_INT_FLAG_CBCMDERR: flash stat0 checked area by the check blank command is all 0xFF or not interrupt flag
      \arg        FMC_STAT0_INT_FLAG_COMPERR: complement error flag in stat0 register
      \arg        FMC_STAT0_INT_FLAG_TMRERR: TMR error flag in stat0 register
      \arg        FMC_STAT0_INT_FLAG_RSTERR: flash stat0 POR or system reset during erase/program interrupt flag
      \arg        FMC_STAT1_INT_FLAG_PGSERR: flash stat1 program sequence error interrupt flag
      \arg        FMC_STAT1_INT_FLAG_PGERR: flash stat1 program error interrupt flag
      \arg        FMC_STAT1_INT_FLAG_WPERR: flash stat1 erase/program protection error interrupt flag
      \arg        FMC_STAT1_INT_FLAG_END: flash stat1 end of operation interrupt flag
      \arg        FMC_STAT1_INT_FLAG_CBCMDERR: flash stat1 checked area by the check blank command is all 0xFF or not interrupt flag
      \arg        FMC_STAT1_INT_FLAG_TMRERR: TMR error flag in stat1 register
      \arg        FMC_STAT1_INT_FLAG_RSTERR: flash stat1 POR or system reset during erase/program interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_interrupt_flag_get(fmc_interrupt_flag_enum int_flag)
{
    uint32_t intenable, flagstatus;
    FlagStatus flag_temp = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_INT_FLAG(int_flag)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x004EU), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* get the interrupt enable bit status */
        intenable = (FMC_REG_VAL(int_flag) & BIT(FMC_BIT_POS(int_flag)));
        /* get the corresponding flag bit status */
        flagstatus = (FMC_REG_VAL2(int_flag) & BIT(FMC_BIT_POS2(int_flag)));

        if((0U != flagstatus) && (0U != intenable)) {
            flag_temp = SET;
        } else {
            flag_temp =  RESET;
        }
    }
    return flag_temp;
}

/*!
    \brief      clear FMC interrupt flag status (API_ID(0x004FU))
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_STAT0_INT_FLAG_PGSERR: flash stat0 program sequence error interrupt flag
      \arg        FMC_STAT0_INT_FLAG_PGERR: flash stat0 program error interrupt flag
      \arg        FMC_STAT0_INT_FLAG_WPERR: flash stat0 erase/program protection error interrupt flag
      \arg        FMC_STAT0_INT_FLAG_END: flash stat0 end of operation interrupt flag
      \arg        FMC_STAT0_INT_FLAG_CBCMDERR: flash stat0 checked area by the check blank command is all 0xFF or not interrupt flag
      \arg        FMC_STAT0_INT_FLAG_COMPERR: complement error flag in stat0 register
      \arg        FMC_STAT0_INT_FLAG_RSTERR: flash stat0 POR or system reset during erase/program interrupt flag
      \arg        FMC_STAT1_INT_FLAG_PGSERR: flash stat1 program sequence error interrupt flag
      \arg        FMC_STAT1_INT_FLAG_PGERR: flash stat1 program error interrupt flag
      \arg        FMC_STAT1_INT_FLAG_WPERR: flash stat1 erase/program protection error interrupt flag
      \arg        FMC_STAT1_INT_FLAG_END: flash stat1 end of operation interrupt flag
      \arg        FMC_STAT1_INT_FLAG_CBCMDERR: flash stat1 checked area by the check blank command is all 0xFF or not interrupt flag
      \arg        FMC_STAT1_INT_FLAG_RSTERR: flash stat1 POR or system reset during erase/program interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
void fmc_interrupt_flag_clear(fmc_interrupt_flag_enum int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_INT_CLEAR_FLAG(int_flag)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x004FU), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* clear the interrupt flag in STAT0/STAT1 register */
        FMC_REG_VAL2(int_flag) = BIT(FMC_BIT_POS2(int_flag));
    }
}

/*!
    \brief      get FMC ECC flag status (API_ID(0x0050U))
    \param[in]  flag: FMC ecc flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_BLKFLAG_ECCCOR0: block one bit error detected and correct flag 0
      \arg        FMC_BLKFLAG_ECCCOR1: block one bit error detected and correct flag 1
      \arg        FMC_BLKFLAG_ECCCOR2: block one bit error detected and correct flag 2
      \arg        FMC_BLKFLAG_ECCCOR3: block one bit error detected and correct flag 3
      \arg        FMC_BLKFLAG_ECCAERR: block more than 4 one bit error detected
      \arg        FMC_BLKFLAG_ECCCOROV: block more than 4 one bit error detected
      \arg        FMC_BLKFLAG_ECCEDC: block EDC after ECC checker error flag
      \arg        FMC_BLKFLAG_ECCDET: block two bit errors detect flag
      \arg        FMC_BUFFLAG_ECCCOR0: buffer one bit error detected and correct flag 0
      \arg        FMC_BUFFLAG_ECCCOR1: buffer one bit error detected and correct flag 1
      \arg        FMC_BUFFLAG_ECCCOR2: buffer one bit error detected and correct flag 2
      \arg        FMC_BUFFLAG_ECCCOR3: buffer one bit error detected and correct flag 3
      \arg        FMC_BUFFLAG_ECCAERR: buffer one bit error flag at ECC address
      \arg        FMC_BUFFLAG_ECCCOROV: buffer more than 4 one bit error detected
      \arg        FMC_BUFFLAG_ECCEDC: buffer EDC after ECC checker error flag
      \arg        FMC_BUFFLAG_ECCDET: buffer two bit errors detect flag
      \arg        FMC_FPBFLAG_ECCCOR0: fast program buffer one bit error detected and correct flag 0
      \arg        FMC_FPBFLAG_ECCCOR1: fast program buffer one bit error detected and correct flag 1
      \arg        FMC_FPBFLAG_ECCCOR2: fast program buffer one bit error detected and correct flag 2
      \arg        FMC_FPBFLAG_ECCCOR3: fast program buffer one bit error detected and correct flag 3
      \arg        FMC_FPBFLAG_ECCAERR: fast program buffer ECC address one bit error flag
      \arg        FMC_FPBFLAG_ECCCOROV: fast program buffer more than 4 one bit error detected
      \arg        FMC_FPBFLAG_ECCEDC: fast program buffer EDC after ECC checker error flag
      \arg        FMC_FPBFLAG_ECCDET: fast program buffer two bit errors detect flag
    \param[in]  reg_num: register number, when ecc occurs in fast program buffer, reg_num must be FMC_REG_0
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: ecc occurs in block0, buffer0 or fast program buffer
      \arg        FMC_REG_1: ecc occurs in block1 or buffer1 (Only applicable to GD32A72XX / GD32A74XX when flag is FMC_BUFFLAG_xxx)
      \arg        FMC_REG_2: ecc occurs in block2 or buffer2
      \arg        FMC_REG_3: ecc occurs in block3 or buffer3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_ecc_flag_get(fmc_ecc_flag_enum flag, fmc_register_enum reg_num)
{
    FlagStatus flag_temp = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_ECC_FLAG(flag)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0050U), ERR_PARAM_INVALID);
    } else if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0050U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* get FMC ecc flag */
        if(0U != (FMC_REG_VAL3(flag, reg_num) & BIT(FMC_BIT_POS(flag)))) {
            flag_temp =  SET;
        } else {
            flag_temp = RESET;
        }
    }
    return flag_temp;
}

/*!
    \brief      clear FMC ECC flag status (API_ID(0x0051U))
    \param[in]  flag: FMC ECC flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_BLKFLAG_ECCCOR0: block one bit error detected and correct flag 0
      \arg        FMC_BLKFLAG_ECCCOR1: block one bit error detected and correct flag 1
      \arg        FMC_BLKFLAG_ECCCOR2: block one bit error detected and correct flag 2
      \arg        FMC_BLKFLAG_ECCCOR3: block one bit error detected and correct flag 3
      \arg        FMC_BLKFLAG_ECCCOR3: block one bit error flag at ECC address
      \arg        FMC_BLKFLAG_ECCAERR: block more than 4 one bit error detected
      \arg        FMC_BLKFLAG_ECCEDC: block EDC after ECC checker error flag
      \arg        FMC_BLKFLAG_ECCDET: block two bit errors detect flag
      \arg        FMC_BUFFLAG_ECCCOR0: buffer one bit error detected and correct flag 0
      \arg        FMC_BUFFLAG_ECCCOR1: buffer one bit error detected and correct flag 1
      \arg        FMC_BUFFLAG_ECCCOR2: buffer one bit error detected and correct flag 2
      \arg        FMC_BUFFLAG_ECCCOR3: buffer one bit error detected and correct flag 3
      \arg        FMC_BUFFLAG_ECCAERR: buffer one bit error flag at ECC address
      \arg        FMC_BUFFLAG_ECCCOROV: buffer more than 4 one bit error detected
      \arg        FMC_BUFFLAG_ECCEDC: buffer EDC after ECC checker error flag
      \arg        FMC_BUFFLAG_ECCDET: buffer two bit errors detect flag
      \arg        FMC_FPBFLAG_ECCCOR0: fast program buffer one bit error detected and correct flag 0
      \arg        FMC_FPBFLAG_ECCCOR1: fast program buffer one bit error detected and correct flag 1
      \arg        FMC_FPBFLAG_ECCCOR2: fast program buffer one bit error detected and correct flag 2
      \arg        FMC_FPBFLAG_ECCCOR3: fast program buffer one bit error detected and correct flag 3
      \arg        FMC_FPBFLAG_ECCAERR: fast program buffer ECC address one bit error flag
      \arg        FMC_FPBFLAG_ECCCOROV: fast program buffer more than 4 one bit error detected
      \arg        FMC_FPBFLAG_ECCEDC: fast program buffer EDC after ECC checker error flag
      \arg        FMC_FPBFLAG_ECCDET: fast program buffer two bit errors detect flag
    \param[in]  reg_num: register number, when ecc occurs in fast program buffer, reg_num must be FMC_REG_0
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: ecc occurs in block0, buffer0 or fast program buffer
      \arg        FMC_REG_1: ecc occurs in block1 or buffer1 (Only applicable to GD32A72XX / GD32A74XX when flag is FMC_BUFFLAG_xxx)
      \arg        FMC_REG_2: ecc occurs in block2 or buffer2
      \arg        FMC_REG_3: ecc occurs in block3 or buffer3
    \param[out] none
    \retval     none
*/
void fmc_ecc_flag_clear(fmc_ecc_flag_enum flag, fmc_register_enum reg_num)
{
    uint32_t reg_temp;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_ECC_FLAG(flag)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0051U), ERR_PARAM_INVALID);
    } else if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0051U), ERR_PARAM_INVALID);
    } else
#endif
    {
        reg_temp = FMC_REG_VAL3(flag, reg_num) & (~ECC_FLAG_CLEAR_MASK);
        if(0U != (BIT(FMC_BIT_POS(flag)) & 0xF0000U)) {
            FMC_REG_VAL3(flag, reg_num) = (reg_temp | FMC_ECCCOR_CLEAR);
        } else {
            /* clear the flags in register */
            FMC_REG_VAL3(flag, reg_num) = (reg_temp | BIT(FMC_BIT_POS(flag)));
        }
    }
}

/*!
    \brief      enable FMC ECC interrupt (API_ID(0x0052U))
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_BLK_INT_ECCCOR: block one bit error correct interrupt
      \arg        FMC_BLK_INT_ECCDET: block two bits error interrupt
      \arg        FMC_BLK_INT_ECCCORV: block more than 4 one bit error detect interrupt
      \arg        FMC_BUF_INT_ECCCOR: buffer one bit error correct interrupt
      \arg        FMC_BUF_INT_ECCDET: buffer two bits error interrupt
      \arg        FMC_BUF_INT_ECCCORV: buffer more than 4 one bit error detect interrupt
      \arg        FMC_FPB_INT_ECCCOR: fast program buffer one bit error correct interrupt
      \arg        FMC_FPB_INT_ECCDET: fast program buffer two bits error interrupt
      \arg        FMC_FPB_INT_ECCCORV: fast program buffer more than 4 one bit error detect interrupt
    \param[in]  reg_num: register number, when ecc occurs in fast program buffer, reg_num must be FMC_REG_0
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: ecc occurs in block0, buffer0 or fast program buffer
      \arg        FMC_REG_1: ecc occurs in block1 or buffer1 (Only applicable to GD32A72XX / GD32A74XX when flag is FMC_BUF_INT_xxx)
      \arg        FMC_REG_2: ecc occurs in block2 or buffer2
      \arg        FMC_REG_3: ecc occurs in block3 or buffer3
    \param[out] none
    \retval     none
*/
void fmc_ecc_interrupt_enable(fmc_ecc_interrupt_enum interrupt, fmc_register_enum reg_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_ECC_INT(interrupt)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0052U), ERR_PARAM_INVALID);
    } else if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0052U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* enable interrupt in CTL0/CTL1 register */
        FMC_REG_VAL3(interrupt, reg_num) |= BIT(FMC_BIT_POS(interrupt));
    }
}

/*!
    \brief      disable FMC ECC interrupt (API_ID(0x0053U))
    \param[in]  interrupt: the FMC interrupt source
                only one parameter can be selected which is shown as below:
      \arg        FMC_BLK_INT_ECCCOR: block one bit error correct interrupt
      \arg        FMC_BLK_INT_ECCDET: block two bits error interrupt
      \arg        FMC_BLK_INT_ECCCORV: block more than 4 one bit error detect interrupt
      \arg        FMC_BUF_INT_ECCCOR: buffer one bit error correct interrupt
      \arg        FMC_BUF_INT_ECCDET: buffer two bits error interrupt
      \arg        FMC_BUF_INT_ECCCORV: buffer more than 4 one bit error detect interrupt
      \arg        FMC_FPB_INT_ECCCOR: fast program buffer one bit error correct interrupt
      \arg        FMC_FPB_INT_ECCDET: fast program buffer two bits error interrupt
      \arg        FMC_FPB_INT_ECCCORV: fast program buffer more than 4 one bit error detect interrupt
    \param[in]  reg_num: register number, when ecc occurs in fast program buffer, reg_num must be FMC_REG_0
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: ecc occurs in block0, buffer0 or fast program buffer
      \arg        FMC_REG_1: ecc occurs in block1 or buffer1 (Only applicable to GD32A72XX / GD32A74XX when flag is FMC_BUF_INT_xxx)
      \arg        FMC_REG_2: ecc occurs in block2 or buffer2
      \arg        FMC_REG_3: ecc occurs in block3 or buffer3
    \param[out] none
    \retval     none
*/
void fmc_ecc_interrupt_disable(fmc_ecc_interrupt_enum interrupt, fmc_register_enum reg_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_ECC_INT(interrupt)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0053U), ERR_PARAM_INVALID);
    } else if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0053U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* disable interrupt in CTL0/CTL1 register */
        FMC_REG_VAL3(interrupt, reg_num) &= ~BIT(FMC_BIT_POS(interrupt));
    }
}

/*!
    \brief      get FMC ECC interrupt flag status (API_ID(0x0054U))
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_BLK_INT_FLAG_ECCCOR0: block one bit error detected and correct interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCCOR1: block one bit error detected and correct interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCCOR2: block one bit error detected and correct interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCCOR3: block one bit error detected and correct interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCAERR: block one bit error flag at ECC address
      \arg        FMC_BLK_INT_FLAG_ECCCOROV: block more than 4 one bit error detected interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCEDC: block EDC after ECC checker error interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCDET: block two bit errors detect flag interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCCOR0: buffer one bit error detected and correct interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCCOR1: buffer one bit error detected and correct interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCCOR2: buffer one bit error detected and correct interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCCOR3: buffer one bit error detected and correct interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCAERR: buffer one bit error flag at ECC address
      \arg        FMC_BUF_INT_FLAG_ECCCOROV: buffer more than 4 one bit error detected interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCEDC: buffer EDC after ECC checker error interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCDET: buffer two bit errors detect flag interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCCOR0: fast program buffer one bit error detected and correct interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCCOR1: fast program buffer one bit error detected and correct interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCCOR2: fast program buffer one bit error detected and correct interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCCOR3: fast program buffer one bit error detected and correct interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCAERR: fast program buffer one bit error flag at ECC address
      \arg        FMC_FPB_INT_FLAG_ECCCOROV: fast program buffer more than 4 one bit error detected interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCEDC: fast program buffer EDC after ECC checker error interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCDET: fast program buffer two bit errors detect flag interrupt flag
    \param[in]  reg_num: register number, when ecc occurs in fast program buffer, reg_num must be FMC_REG_0
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: ecc occurs in block0, buffer0 or fast program buffer
      \arg        FMC_REG_1: ecc occurs in block1 or buffer1 (Only applicable to GD32A72XX / GD32A74XX when flag is FMC_BUF_INT_FLAG_xxx)
      \arg        FMC_REG_2: ecc occurs in block2 or buffer2
      \arg        FMC_REG_3: ecc occurs in block3 or buffer3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmc_ecc_interrupt_flag_get(fmc_ecc_interrupt_flag_enum int_flag, fmc_register_enum reg_num)
{
    uint32_t intenable, flagstatus;
    FlagStatus flag_temp = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_ECC_INT_FLAG(int_flag)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0054U), ERR_PARAM_INVALID);
    } else if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0054U), ERR_PARAM_INVALID);
    } else
#endif
    {
        /* get the ECC interrupt enable bit status */
        intenable = (FMC_REG_VAL3(int_flag, reg_num) & BIT(FMC_BIT_POS(int_flag)));
        /* get the corresponding flag bit status */
        flagstatus = (FMC_REG_VAL4(int_flag, reg_num) & BIT(FMC_BIT_POS2(int_flag)));

        if((0U != flagstatus) && (0u != intenable)) {
            flag_temp = SET;
        } else {
            flag_temp = RESET;
        }
    }
    return flag_temp;
}

/*!
    \brief      clear FMC ECC interrupt flag status (API_ID(0x0055U))
    \param[in]  flag: FMC interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        FMC_BLK_INT_FLAG_ECCCOR0: block one bit error detected and correct interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCCOR1: block one bit error detected and correct interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCCOR2: block one bit error detected and correct interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCCOR3: block one bit error detected and correct interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCAERR: block one bit error flag at ECC address
      \arg        FMC_BLK_INT_FLAG_ECCCOROV: block more than 4 one bit error detected interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCEDC: block EDC after ECC checker error interrupt flag
      \arg        FMC_BLK_INT_FLAG_ECCDET: block two bit errors detect flag interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCCOR0: buffer one bit error detected and correct interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCCOR1: buffer one bit error detected and correct interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCCOR2: buffer one bit error detected and correct interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCCOR3: buffer one bit error detected and correct interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCAERR: buffer one bit error flag at ECC address
      \arg        FMC_BUF_INT_FLAG_ECCCOROV: buffer more than 4 one bit error detected interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCEDC: buffer EDC after ECC checker error interrupt flag
      \arg        FMC_BUF_INT_FLAG_ECCDET: buffer two bit errors detect flag interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCCOR0: fast program buffer one bit error detected and correct interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCCOR1: fast program buffer one bit error detected and correct interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCCOR2: fast program buffer one bit error detected and correct interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCCOR3: fast program buffer one bit error detected and correct interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCAERR: fast program buffer one bit error flag at ECC address
      \arg        FMC_FPB_INT_FLAG_ECCCOROV: fast program buffer more than 4 one bit error detected interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCEDC: fast program buffer EDC after ECC checker error interrupt flag
      \arg        FMC_FPB_INT_FLAG_ECCDET: fast program buffer two bit errors detect flag interrupt flag
    \param[in]  reg_num: register number, when ecc occurs in fast program buffer, reg_num must be FMC_REG_0
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: ecc occurs in block0, buffer0 or fast program buffer
      \arg        FMC_REG_1: ecc occurs in block1 or buffer1 (Only applicable to GD32A72XX / GD32A74XX when flag is FMC_BUF_INT_FLAG_xxx)
      \arg        FMC_REG_2: ecc occurs in block2 or buffer2
      \arg        FMC_REG_3: ecc occurs in block3 or buffer3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
void fmc_ecc_interrupt_flag_clear(fmc_ecc_interrupt_flag_enum int_flag, fmc_register_enum reg_num)
{
    uint32_t reg_temp;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_ECC_INT_FLAG(int_flag)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0055U), ERR_PARAM_INVALID);
    } else if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0055U), ERR_PARAM_INVALID);
    } else
#endif
    {
        reg_temp = FMC_REG_VAL4(int_flag, reg_num) & (~ECC_FLAG_CLEAR_MASK);
        if(0U != ((BIT(FMC_BIT_POS2(int_flag)) & 0xF0000U))) {
            FMC_REG_VAL4(int_flag, reg_num) = (reg_temp | FMC_ECCCOR_CLEAR);
        } else {
            /* clear the interrupt flag in ECC register */
            FMC_REG_VAL4(int_flag, reg_num) = (reg_temp | BIT(FMC_BIT_POS2(int_flag)));
        }
    }
}

/*!
    \brief      get FMC block correctable ecc error address (API_ID(0x0056U))
    \param[in]  reg_num: register number
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: ecc occurs in block0
      \arg        FMC_REG_1: ecc occurs in block1
      \arg        FMC_REG_2: ecc occurs in block2
      \arg        FMC_REG_3: ecc occurs in block3
    \param[in]  address_idx: the correctable ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        CECC_ADDR0: FMC correctable ECC address 0
      \arg        CECC_ADDR1: FMC correctable ECC address 1
      \arg        CECC_ADDR2: FMC correctable ECC address 2
      \arg        CECC_ADDR3: FMC correctable ECC address 3
    \param[out] none
    \retval     FMC block ecc address, 0x000000 ~ 0x3FFFFF
*/
uint32_t fmc_block_cecc_address_get(fmc_register_enum reg_num, fmc_cecc_addr_enum address_idx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0056U), ERR_PARAM_INVALID);
    } else if(NOT_CECC_ADDR(address_idx)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0056U), ERR_PARAM_INVALID);
    } else
#endif
    {
        reval = REG32((uint32_t)(FMC + 0x68U + 0x04U * ((uint32_t)address_idx)  + 0x100U * (uint32_t)(reg_num)));
    }
    return reval;
}

/*!
    \brief      get FMC block uncorrectable ecc error address (API_ID(0x0057U))
    \param[in]  reg_num: register number
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: uncorrectable ecc occurs in block0
      \arg        FMC_REG_1: uncorrectable ecc occurs in block1
      \arg        FMC_REG_2: uncorrectable ecc occurs in block2
      \arg        FMC_REG_3: uncorrectable ecc occurs in block3
    \param[out] none
    \retval     FMC block ecc address, 0x000000 ~ 0x3FFFFF
*/
uint32_t fmc_block_ucecc_address_get(fmc_register_enum reg_num)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0057U), ERR_PARAM_INVALID);
    } else
#endif
    {
        reval = (uint32_t)FMC_BLKUCECCADDR(reg_num);
    }
    return reval;
}

/*!
    \brief      get FMC buffer correctable ecc error address (API_ID(0x0058U))
    \param[in]  reg_num: register number
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: ecc occurs in buffer0
      \arg        FMC_REG_1: ecc occurs in buffer1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_REG_2: ecc occurs in buffer2
      \arg        FMC_REG_3: ecc occurs in buffer3
    \param[in]  address_idx: the correctable ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        CECC_ADDR0: FMC correctable ECC address 0
      \arg        CECC_ADDR1: FMC correctable ECC address 1
      \arg        CECC_ADDR2: FMC correctable ECC address 2
      \arg        CECC_ADDR3: FMC correctable ECC address 3
    \param[out] none
    \retval     FMC block ecc address, 0x000000 ~ 0xFFFFFF
*/
uint32_t fmc_buffer_cecc_address_get(fmc_register_enum reg_num, fmc_cecc_addr_enum address_idx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0058U), ERR_PARAM_INVALID);
    } else if(NOT_CECC_ADDR(address_idx)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0058U), ERR_PARAM_INVALID);
    } else
#endif
    {
        reval =  REG32((uint32_t)(FMC + 0x88U + 0x04U * (uint32_t)(address_idx)  + 0x100U * (uint32_t)(reg_num)));
    }
    return reval;
}

/*!
    \brief      get FMC buffer uncorrectable ecc error address (API_ID(0x0059U))
    \param[in]  reg_num: register number
                only one parameter can be selected which is shown as below:
      \arg        FMC_REG_0: uncorrectable ecc occurs in buffer0
      \arg        FMC_REG_1: uncorrectable ecc occurs in buffer1 (Only applicable to GD32A72XX / GD32A74XX)
      \arg        FMC_REG_2: uncorrectable ecc occurs in buffer2
      \arg        FMC_REG_3: uncorrectable ecc occurs in buffer3
    \param[out] none
    \retval     FMC block ecc address, 0x000000 ~ 0xFFFFFF
*/
uint32_t fmc_buffer_ucecc_address_get(fmc_register_enum reg_num)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_REG_NUM(reg_num)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x0059U), ERR_PARAM_INVALID);
    } else
#endif
    {
        reval = (uint32_t)FMC_BUFUCECCADDR(reg_num);
    }
    return reval;
}


/*!
    \brief      get FMC fast program buffer correctable ecc error address (API_ID(0x005AU))
    \param[in]  address_idx: the correctable ecc error address index
                only one parameter can be selected which is shown as below:
      \arg        CECC_ADDR0: FMC correctable ECC address 0
      \arg        CECC_ADDR1: FMC correctable ECC address 1
      \arg        CECC_ADDR2: FMC correctable ECC address 2
      \arg        CECC_ADDR3: FMC correctable ECC address 3
    \param[out] none
    \retval     FMC block ecc address, 0x000 ~ 0x3FF
*/
uint32_t fmc_fpb_cecc_address_get(fmc_cecc_addr_enum address_idx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_CECC_ADDR(address_idx)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x005AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        reval = REG32((uint32_t)((FMC) + 0x000000A8U + 0x04U * (uint32_t)(address_idx)));
    }
    return reval;
}

/*!
    \brief      get FMC fast program buffer uncorrectable ecc error address (API_ID(0x005BU))
    \param[in]  none
    \param[out] none
    \retval     FMC block ecc address, 0x000 ~ 0x3FF
*/
uint32_t fmc_fpb_ucecc_address_get(void)
{
    return (uint32_t)FMC_FPB_UCECCADDR;
}

/*!
    \brief      get PID (API_ID(0x005CU))
    \param[in]  pidx: pid index
                only one parameter can be selected which is shown as below:
      \arg        FMC_PID_0: PID0 index
      \arg        FMC_PID_1: PID1 index
    \param[out] none
    \retval     FMC block ecc address, 0x00000000 ~ 0xFFFFFFFF
*/
uint32_t fmc_pid_get(uint32_t pidx)
{
    uint32_t reval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMC_PID_INDEX(pidx)) {
        fw_debug_report_err(FMC_MODULE_ID, API_ID(0x005CU), ERR_PARAM_INVALID);
    } else
#endif
    {
        reval = REG32((FMC) + 0x000000D0U + 0x04U * pidx);
    }
    return reval;
}

/*!
    \brief      return the FMC ctl0 state
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR: program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_LOADECCERR: uncorrected ECC error when load
      \arg        FMC_COMPERR: complement error in writing data
      \arg        FMC_TMERR: TMR error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
static fmc_state_enum fmc_ctl0_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_BUSY)) {
        fmc_state = FMC_BUSY;
    } else {
        if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_WPERR)) {
            fmc_state = FMC_WPERR;
        } else if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_PGERR)) {
            fmc_state = FMC_PGERR;
        } else if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_PGSERR)) {
            fmc_state = FMC_PGSERR;
        } else if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_CBCMDERR)) {
            fmc_state = FMC_CBCMDERR;
        } else if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_LOADECCERR)) {
            fmc_state = FMC_LOADECCERR;
        } else if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_COMPERR)) {
            fmc_state = FMC_COMPERR;
        } else if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_TMRERR)) {
            fmc_state = FMC_TMRERR;
        } else if((uint32_t)0x00U != (FMC_STAT0 & FMC_STAT0_RSTERR)) {
            fmc_state = FMC_RSTERR;
        } else {
            /* illegal parameters */
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      return the FMC ctl1 state
    \param[in]  none
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_TMERR: TMR error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
static fmc_state_enum fmc_ctl1_state_get(void)
{
    fmc_state_enum fmc_state = FMC_READY;

    if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_BUSY)) {
        fmc_state = FMC_BUSY;
    } else {
        if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_WPERR)) {
            fmc_state = FMC_WPERR;
        } else if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_PGERR)) {
            fmc_state = FMC_PGERR;
        } else if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_PGSERR)) {
            fmc_state = FMC_PGSERR;
        } else if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_CBCMDERR)) {
            fmc_state = FMC_CBCMDERR;
        } else if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_TMRERR)) {
            fmc_state = FMC_TMRERR;
        } else if((uint32_t)0x00U != (FMC_STAT1 & FMC_STAT1_RSTERR)) {
            fmc_state = FMC_RSTERR;
        } else {
            /* This code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC ctl0 is ready or not
    \param[in]  timeout: timeout count
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_LOADECCERR: uncorrected ECC error when load
      \arg        FMC_COMPERR: complement error in writing data
      \arg        FMC_TMERR: TMR error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
static fmc_state_enum fmc_ctl0_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state;

    /* wait for FMC ready */
    do {
        /* get FMC state */
        fmc_state = fmc_ctl0_state_get();
        timeout--;
    } while((FMC_BUSY == fmc_state) && (0U != timeout));

    if(FMC_BUSY == fmc_state) {
        fmc_state = FMC_TOERR;
    }

    /* return the FMC state */
    return fmc_state;
}

/*!
    \brief      check whether FMC ctl1 is ready or not
    \param[in]  timeout: timeout count
    \param[out] none
    \retval     state of FMC, refer to fmc_state_enum
      \arg        FMC_READY: the operation has been completed
      \arg        FMC_BUSY: the operation is in progress
      \arg        FMC_PGSERR:  program sequence error
      \arg        FMC_PGERR: program error
      \arg        FMC_WPERR: erase/program protection error
      \arg        FMC_TOERR: timeout error
      \arg        FMC_CBCMDERR: the checked area not blank error
      \arg        FMC_TMERR: TMR error
      \arg        FMC_RSTERR: POR or system reset during flash erase/program error
*/
static fmc_state_enum fmc_ctl1_ready_wait(uint32_t timeout)
{
    fmc_state_enum fmc_state;

    /* wait for FMC ready */
    do {
        /* get FMC state */
        fmc_state = fmc_ctl1_state_get();
        timeout--;
    } while((FMC_BUSY == fmc_state) && (0U != timeout));

    if(FMC_BUSY == fmc_state) {
        fmc_state = FMC_TOERR;
    }

    /* return the FMC state */
    return fmc_state;
}
