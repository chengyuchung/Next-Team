/*!
    \file    gd32a7xx_hwsem.c
    \brief   HWSEM driver

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
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#include "gd32a7xx_hwsem.h"

/*!
    \brief      try to lock the specific semaphore by writing process ID (API_ID: 0x0001U)
    \param[in]  semaphore: semaphore index 0 - 31
    \param[in]  process: the process to lock the semaphore, 0 - 0xFF
    \param[in]  master_id: the master id of AHB
                only one parameter can be selected which is shown as below:
      \arg        HWSEM_MASTER_ID_CM7_0 :core CM7_0 master ID
      \arg        HWSEM_MASTER_ID_CM7_1 :core CM7_1 master ID
      \arg        HWSEM_MASTER_ID_HSM_CM23 :core HSM CM23 master ID
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_write_lock(uint32_t semaphore, uint8_t process, uint32_t master_id)
{
    uint32_t temp_mid;
    uint32_t temp_pid;
    ErrStatus retval = ERROR;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0001U), ERR_PARAM_INVALID);
    } else if(NOT_HWSEM_LOCK_MASTER_ID(master_id)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0001U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* try to lock the semaphore */
        HWSEM_CTL(semaphore) = (uint32_t)(HWSEM_CTL_LK | CTL_MID(master_id) | CTL_PID(process));

        /* read the control register to confirm the semaphore is locked by target process or not */
        temp_mid = (uint32_t)(GET_CTL_MID(HWSEM_CTL(semaphore)));
        temp_pid = (uint32_t)(GET_CTL_PID(HWSEM_CTL(semaphore)));
        if((master_id == temp_mid) && (process == temp_pid)) {
            retval = SUCCESS;
        } else {
            retval = ERROR;
        }
    }
    return retval;
}

/*!
    \brief      try to release the lock of the semaphore by writing process ID (API_ID: 0x0002U)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[in]  process: the process to unlock the semaphore, 0 - 0xFF 
    \param[in]  master_id: the master id of AHB
                only one parameter can be selected which is shown as below:
      \arg        HWSEM_MASTER_ID_CM7_0 :core CM7_0 master ID
      \arg        HWSEM_MASTER_ID_CM7_1 :core CM7_1 master ID
      \arg        HWSEM_MASTER_ID_HSM_CM23 :core HSM CM23 master ID
    \param[out] none
    \retval     none
*/
void hwsem_write_unlock(uint32_t semaphore, uint8_t process, uint32_t master_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else if(NOT_HWSEM_UNLOCK_MASTER_ID(master_id)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HWSEM_CTL(semaphore) = (uint32_t)(CTL_MID(master_id) | CTL_PID(process));
    }
}

/*!
    \brief      try to lock the semaphore by reading (API_ID: 0x0003U)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[in]  master_id: the master id of AHB
                only one parameter can be selected which is shown as below:
      \arg        HWSEM_MASTER_ID_CM7_0 :core CM7_0 master ID
      \arg        HWSEM_MASTER_ID_CM7_1 :core CM7_1 master ID
      \arg        HWSEM_MASTER_ID_HSM_CM23 :core HSM CM23 master ID
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
*/
ErrStatus hwsem_read_lock(uint32_t semaphore, uint32_t master_id)
{
    ErrStatus retval = ERROR;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_HWSEM_LOCK_MASTER_ID(master_id)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((uint32_t)(HWSEM_CTL_LK | CTL_MID(master_id)) == HWSEM_RLK(semaphore)) {
            retval = SUCCESS;
        } else {
            retval = ERROR;
        }
    }
    return retval;
}

/*!
    \brief      unlock all semaphores of the master ID (API_ID: 0x0004U)
    \param[in]  key: key value, 0 - 0xFFFF
    \param[in]  master_id: the master id of AHB
                only one parameter can be selected which is shown as below:
      \arg        HWSEM_MASTER_ID_CM7_0 :core CM7_0 master ID
      \arg        HWSEM_MASTER_ID_CM7_1 :core CM7_1 master ID
      \arg        HWSEM_MASTER_ID_HSM_CM23 :core HSM CM23 master ID
      \arg        HWSEM_MASTER_ID_HSM_DMA :core HSM DMA master ID
      \arg        HWSEM_MASTER_ID_DMA0_MEM :core DMA0_MEM master ID
      \arg        HWSEM_MASTER_ID_DMA1_MEM :core DMA1_MEM master ID
    \param[out] none
    \retval     none
*/
void hwsem_write_unlock_all(uint16_t key, uint32_t master_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_UNLOCK_ALL_MASTER_ID(master_id)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HWSEM_UNLK = UNLK_KEY(key) | UNLK_MID(master_id);
    }
}

/*!
    \brief      get process ID of the specific semaphore (API_ID: 0x0005U)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     uint32_t: process ID of semaphore
*/
uint32_t hwsem_process_id_get(uint32_t semaphore)
{
    uint32_t retval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        retval = (uint32_t)(GET_CTL_PID(HWSEM_CTL(semaphore)));
    }
    return retval;
}

/*!
    \brief      get master ID of the specific semaphore (API_ID: 0x0006U)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     uint32_t: master ID of semaphore
*/
uint32_t hwsem_master_id_get(uint32_t semaphore)
{
    uint32_t retval = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        retval = (uint32_t)(GET_CTL_MID(HWSEM_CTL(semaphore)));
    }
    return retval;
}

/*!
    \brief      get the lock status of the semaphore (API_ID: 0x0007U)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_lock_status_get(uint32_t semaphore)
{
    FlagStatus retval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (HWSEM_CTL(semaphore) & HWSEM_CTL_LK)) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      set the key (API_ID: 0x0008U)
    \param[in]  key: key value, 0 - 0xFFFF
    \param[out] none
    \retval     none
*/
void hwsem_key_set(uint16_t key)
{
    HWSEM_KEY = KEY_KEY(key);
}

/*!
    \brief      get the key (API_ID: 0x0009U)
    \param[in]  none
    \param[out] none
    \retval     uint16_t: key to unlock all semaphores
*/
uint16_t hwsem_key_get(void)
{
    return ((uint16_t)GET_KEY_KEY(HWSEM_KEY));
}

/*!
    \brief      get the HWSEM flag status (API_ID: 0x000AU)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_flag_get(uint32_t semaphore)
{
    FlagStatus retval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (HWSEM_STAT & HWSEM_STAT_SF(semaphore))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      clear HWSEM flag status (API_ID: 0x000BU)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     none
*/
void hwsem_flag_clear(uint32_t semaphore)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HWSEM_INTC = HWSEM_INTC_SIFC(semaphore);
    }
}

/*!
    \brief      get HWSEM interrupt flag status (API_ID: 0x000CU)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus hwsem_interrupt_flag_get(uint32_t semaphore)
{
    FlagStatus retval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (HWSEM_INTF & HWSEM_INTF_SIF(semaphore))) {
            retval = SET;
        } else {
            retval = RESET;
        }
    }
    return retval;
}

/*!
    \brief      clear HWSEM interrupt flag (API_ID: 0x000DU)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_flag_clear(uint32_t semaphore)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HWSEM_INTC = HWSEM_INTC_SIFC(semaphore);
    }
}

/*!
    \brief      enable HWSEM interrupt (API_ID: 0x000EU)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_enable(uint32_t semaphore)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x000EU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HWSEM_INTEN |= HWSEM_INTEN_SIE(semaphore);
    }
}

/*!
    \brief      disable HWSEM interrupt (API_ID: 0x000FU)
    \param[in]  semaphore: semaphore index, 0 - 31
    \param[out] none
    \retval     none
*/
void hwsem_interrupt_disable(uint32_t semaphore)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_HWSEM_SEM_INDEX(semaphore)) {
        fw_debug_report_err(HWSEM_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        HWSEM_INTEN &= ~HWSEM_INTEN_SIE(semaphore);
    }
}
#endif /* #if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
