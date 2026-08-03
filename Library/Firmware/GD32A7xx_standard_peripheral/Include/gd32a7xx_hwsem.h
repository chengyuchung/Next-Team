/*!
    \file    gd32a7xx_hwsem.h
    \brief   definitions for the HWSEM

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
#ifndef GD32A7XX_HWSEM_H
#define GD32A7XX_HWSEM_H

#include "gd32a7xx.h"

/* HWSEM definitions */
#define HWSEM                      HWSEM_BASE                              /*!< HWSEM base address */

/* registers definitions */
#define HWSEM_CTL(x)               REG32(HWSEM + 0x00000000U + 0x4U * (x)) /*!< HWSEM control register x, x=0..31*/
#define HWSEM_RLK(x)               REG32(HWSEM + 0x00000080U + 0x4U * (x)) /*!< HWSEM read lock register x, x=0..31 */
#define HWSEM_INTEN                REG32(HWSEM + 0x00000100U)              /*!< HWSEM interrupt enable register */
#define HWSEM_INTC                 REG32(HWSEM + 0x00000104U)              /*!< HWSEM interrupt flag clear register */
#define HWSEM_STAT                 REG32(HWSEM + 0x00000108U)              /*!< HWSEM status register */
#define HWSEM_INTF                 REG32(HWSEM + 0x0000010CU)              /*!< HWSEM interrupt flag register */
#define HWSEM_UNLK                 REG32(HWSEM + 0x00000140U)              /*!< HWSEM unlock register */
#define HWSEM_KEY                  REG32(HWSEM + 0x00000144U)              /*!< HWSEM key register */

/* bits definitions */
/* HWSEM_CTL(x) */
#define HWSEM_CTL_PID              BITS(0,7)                               /*!< HWSEM process ID */
#define HWSEM_CTL_MID              BITS(8,11)                              /*!< HWSEM master ID */
#define HWSEM_CTL_LK               BIT(31)                                 /*!< HWSEM lock */

/* HWSEM_RLK(x) */
#define HWSEM_RLK_PID              BITS(0,7)                               /*!< HWSEM read lock register process ID */
#define HWSEM_RLK_MID              BITS(8,11)                              /*!< HWSEM read lock register master ID */
#define HWSEM_RLK_LK               BIT(31)                                 /*!< HWSEM read lock register lock */

/* HWSEM_INTEN */
#define HWSEM_INTEN_SIE(x)         BIT(x)                                  /*!< enable HWSEM interrupt for semaphore x, x=0..31 */

/* HWSEM_INTC */
#define HWSEM_INTC_SIFC(x)         BIT(x)                                  /*!< clear semaphore x flag and interrupt flag, x=0..31 */

/* HWSEM_STAT */
#define HWSEM_STAT_SF(x)           BIT(x)                                  /*!< semaphore x unlock event occurs, x=0..31 */

/* HWSEM_INTF */
#define HWSEM_INTF_SIF(x)          BIT(x)                                  /*!< semaphore x interrupt is pending, x=0..31 */

/* HWSEM_UNLK */
#define HWSEM_UNLK_MID             BITS(8,11)                              /*!< bus master ID to clear */
#define HWSEM_UNLK_KEY             BITS(16,31)                             /*!< HWSEM semaphore unlock key */

/* HWSEM_KEY */
#define HWSEM_KEY_KEY              BITS(16,31)                             /*!< key for unlocking all semaphores of a bus master */

/* constants definitions */
/* hwsem_ctlx register */
#define CTL_PID(regval)          (BITS(0,7) & ((uint32_t)(regval) << 0))   /*!< write value to HWSEM_CTL_PID bit field */
#define GET_CTL_PID(regval)      GET_BITS((regval),0,7)                    /*!< get value of HWSEM_CTL_PID bit field */
#define CTL_MID(regval)          (BITS(8,11) & ((uint32_t)(regval) << 8))  /*!< write value to HWSEM_CTL_MID bit field */
#define GET_CTL_MID(regval)      GET_BITS((regval),8,11)                   /*!< get value of HWSEM_CTL_MID bit field */

/* hwsem_unlk register */
#define UNLK_MID(regval)         (BITS(8,11) & ((uint32_t)(regval) << 8))  /*!< write value to HWSEM_CTL_PID bit field */
#define UNLK_KEY(regval)         (BITS(16,31) & ((uint32_t)(regval) << 16))/*!< write value to HWSEM_CTL_PID bit field */

/* hwsem_key register */
#define KEY_KEY(regval)          (BITS(16,31) & ((uint32_t)(regval) << 16))/*!< write value to HWSEM_CTL_PID bit field */
#define GET_KEY_KEY(regval)      GET_BITS((regval),16,31)                  /*!< get value of HWSEM_CTL_PID bit field */

/* AHB bus master ID */
#define HWSEM_MASTER_ID_CM7_0           ((uint32_t)0x0EU)                        /*!< core CM7_0 master ID */
#define HWSEM_MASTER_ID_CM7_1           ((uint32_t)0x07U)                        /*!< core CM7_1 master ID */
#define HWSEM_MASTER_ID_HSM_CM23        ((uint32_t)0x04U)                        /*!< core HSM CM23 master ID */
#define HWSEM_MASTER_ID_HSM_DMA         ((uint32_t)0x0CU)                        /*!< core HSM DMA master ID */
#define HWSEM_MASTER_ID_DMA0_MEM        ((uint32_t)0x02U)                        /*!< core DMA0_MEM master ID */
#define HWSEM_MASTER_ID_DMA1_MEM        ((uint32_t)0x03U)                        /*!< core DMA1_MEM master ID */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check semaphore index */
#define HWSEM_SEM_INDEX_HIGH                                ((uint32_t)31U)
#define NOT_HWSEM_SEM_INDEX(index)                          (HWSEM_SEM_INDEX_HIGH < (index))

/* check master id of lock operation */
#define NOT_HWSEM_LOCK_MASTER_ID(master_id)                (((master_id) != HWSEM_MASTER_ID_CM7_0) && \
                                                            ((master_id) != HWSEM_MASTER_ID_CM7_1) && \
                                                            ((master_id) != HWSEM_MASTER_ID_HSM_CM23))
                                                            
/* check master id of unlock operation */
#define NOT_HWSEM_UNLOCK_MASTER_ID(master_id)              (((master_id) != HWSEM_MASTER_ID_CM7_0) && \
                                                            ((master_id) != HWSEM_MASTER_ID_CM7_1) && \
                                                            ((master_id) != HWSEM_MASTER_ID_HSM_CM23))

/* check master id of unlock operation */
#define NOT_HWSEM_UNLOCK_ALL_MASTER_ID(master_id)          (((master_id) != HWSEM_MASTER_ID_CM7_0) && \
                                                            ((master_id) != HWSEM_MASTER_ID_CM7_1) && \
                                                            ((master_id) != HWSEM_MASTER_ID_HSM_CM23) && \
                                                            ((master_id) != HWSEM_MASTER_ID_HSM_DMA) && \
                                                            ((master_id) != HWSEM_MASTER_ID_DMA0_MEM) && \
                                                            ((master_id) != HWSEM_MASTER_ID_DMA1_MEM))
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* lock & unlock functions */
/* try to lock the specific semaphore by writing process ID */
ErrStatus hwsem_write_lock(uint32_t semaphore, uint8_t process, uint32_t master_id);
/* try to release the lock of the semaphore by writing process ID */
void hwsem_write_unlock(uint32_t semaphore, uint8_t process, uint32_t master_id);
/* try to lock the semaphore by reading */
ErrStatus hwsem_read_lock(uint32_t semaphore, uint32_t master_id);
/* unlock all semaphores of the master ID */
void hwsem_write_unlock_all(uint16_t key, uint32_t master_id);

/* get process ID of the specific semaphore */
uint32_t hwsem_process_id_get(uint32_t semaphore);
/* get master ID of the specific semaphore */
uint32_t hwsem_master_id_get(uint32_t semaphore);
/* get the lock status of the semaphore */
FlagStatus hwsem_lock_status_get(uint32_t semaphore);
/* set the key */
void hwsem_key_set(uint16_t key);
/* get the key */
uint16_t hwsem_key_get(void);

/* flag and interrupt functions */
/* get the HWSEM flag status */
FlagStatus hwsem_flag_get(uint32_t semaphore);
/* clear HWSEM flag status */
void hwsem_flag_clear(uint32_t semaphore);
/* get HWSEM interrupt flag status */
FlagStatus hwsem_interrupt_flag_get(uint32_t semaphore);
/* clear HWSEM interrupt flag */
void hwsem_interrupt_flag_clear(uint32_t semaphore);
/* enable HWSEM interrupt */
void hwsem_interrupt_enable(uint32_t semaphore);
/* disable HWSEM interrupt */
void hwsem_interrupt_disable(uint32_t semaphore);

#endif /* GD32A7XX_HWSEM_H */
#endif /* #if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
