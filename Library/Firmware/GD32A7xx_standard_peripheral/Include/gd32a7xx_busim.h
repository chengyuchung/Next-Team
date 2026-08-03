/*!
   \file    gd32a7xx_busim.h
   \brief   definitions for the BUSIM

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

#ifndef GD32A7XX_BUSIM_H
#define GD32A7XX_BUSIM_H

#include "gd32a7xx.h"

/* BUSIM definitions */
#define BUSIM                                    BUSIM_BASE                              /*!< BUSIM base address */

/* registers definitions */
#define BUSIM_BMCTL(sp)                          REG32(BUSIM + (0x0010U * (sp)))           /*!< BM contorl register */
#define BUSIM_BMSPCFG(sp)                        REG32(BUSIM + (0x0010U * (sp)) + 0x0004U) /*!< BM slave port priority configuration register */
#define BUSIM_TMRFCS                             REG32(BUSIM + 0x0200U)                    /*!< TMR fault control and status register */

/* bits definitions */
/* BUSIM_CTL */
#define BUSIM_CTL_DMP                            BITS(0,2)                               /*!< default master port */
#define BUSIM_CTL_DMPSEL                         BIT(3)                                  /*!< default master port strategy select */
#define BUSIM_CTL_ARBMOD                         BIT(4)                                  /*!< arbitration mode select */
#define BUSIM_CTL_HPM0EN                         BIT(8)                                  /*!< high priority mode for master port 0 enable bit */
#define BUSIM_CTL_HPM1EN                         BIT(9)                                  /*!< high priority mode for master port 0 enable bit */
#define BUSIM_CTL_HPM2EN                         BIT(10)                                 /*!< high priority mode for master port 0 enable bit */
#define BUSIM_CTL_HPM3EN                         BIT(11)                                 /*!< high priority mode for master port 0 enable bit */
#define BUSIM_CTL_HPM4EN                         BIT(12)                                 /*!< high priority mode for master port 0 enable bit */
#define BUSIM_CTL_HPM5EN                         BIT(13)                                 /*!< high priority mode for master port 0 enable bit */
#define BUSIM_CTL_HPM6EN                         BIT(14)                                 /*!< high priority mode for master port 0 enable bit */
#define BUSIM_CTL_HPM7EN                         BIT(15)                                 /*!< high priority mode for master port 0 enable bit */
#define BUSIM_CTL_ROEN                           BIT(31)                                 /*!< register read-only enable */

/* BUSIM_SPCFG */
#define BUSIM_SPCFG_M0PRIO                       BITS(0,2)                               /*!< priority of master port 0 */
#define BUSIM_SPCFG_M1PRIO                       BITS(4,6)                               /*!< priority of master port 1 */
#define BUSIM_SPCFG_M2PRIO                       BITS(8,10)                              /*!< priority of master port 2 */
#define BUSIM_SPCFG_M3PRIO                       BITS(12,14)                             /*!< priority of master port 3 */
#define BUSIM_SPCFG_M4PRIO                       BITS(16,18)                             /*!< priority of master port 4 */
#define BUSIM_SPCFG_M5PRIO                       BITS(20,22)                             /*!< priority of master port 5 */
#define BUSIM_SPCFG_M6PRIO                       BITS(24,26)                             /*!< priority of master port 6 */
#define BUSIM_SPCFG_M7PRIO                       BITS(28,30)                             /*!< priority of master port 7 */

/* BUSIM_TMRFCS */
#define BUSIM_TMRFCS_TMRERR_IE0                  BIT(0)                                  /*!< TMR error 0 (EXTMPU) output to FMU enable */
#define BUSIM_TMRFCS_TMRERR_IE1                  BIT(1)                                  /*!< TMR error 1 (IMICU) output to FMU enable */
#define BUSIM_TMRFCS_TMRERR_STAT0                BIT(2)                                  /*!< EXTMPU enable register TMR error status */
#define BUSIM_TMRFCS_TMRERR_STAT1                BIT(3)                                  /*!< IMICU enable register TMR error status */

/* constants definitions */
#define BUSIM_DEFAULTMASTER_M0                   ((uint32_t)0x00000000U)                 /*!< default access the slave port by the master port M0 */
#define BUSIM_DEFAULTMASTER_M1                   ((uint32_t)0x00000001U)                 /*!< default access the slave port by the master port M1 */
#define BUSIM_DEFAULTMASTER_M2                   ((uint32_t)0x00000002U)                 /*!< default access the slave port by the master port M2 */
#define BUSIM_DEFAULTMASTER_M3                   ((uint32_t)0x00000003U)                 /*!< default access the slave port by the master port M3 */
#define BUSIM_DEFAULTMASTER_M4                   ((uint32_t)0x00000004U)                 /*!< default access the slave port by the master port M4 */
#define BUSIM_DEFAULTMASTER_M5                   ((uint32_t)0x00000005U)                 /*!< default access the slave port by the master port M5 */
#define BUSIM_DEFAULTMASTER_M6                   ((uint32_t)0x00000006U)                 /*!< default access the slave port by the master port M6 */
#define BUSIM_DEFAULTMASTER_M7                   ((uint32_t)0x00000007U)                 /*!< default access the slave port by the master port M7 */
#define BUSIM_DEFAULTMASTER_LAST                 BUSIM_CTL_DMPSEL                        /*!< default master port strategy select */

#define BUSIM_BM1_MASTER0                        ((uint32_t)0U)                          /*!< bus matrix1 master 0 */
#define BUSIM_BM1_MASTER1                        ((uint32_t)4U)                          /*!< bus matrix1 master 1 */
#define BUSIM_BM1_MASTER2                        ((uint32_t)8U)                          /*!< bus matrix1 master 2 */
#define BUSIM_BM1_MASTER3                        ((uint32_t)12U)                         /*!< bus matrix1 master 3 */
#define BUSIM_BM1_MASTER4                        ((uint32_t)16U)                         /*!< bus matrix1 master 4 */
#define BUSIM_BM1_MASTER5                        ((uint32_t)20U)                         /*!< bus matrix1 master 5 */
#define BUSIM_BM1_MASTER6                        ((uint32_t)24U)                         /*!< bus matrix1 master 6 */
#define BUSIM_BM1_MASTER7                        ((uint32_t)28U)                         /*!< bus matrix1 master 7 */
#define BUSIM_BM2_MASTER0                        ((uint32_t)0U)                          /*!< bus matrix2 master 0 */
#define BUSIM_BM2_MASTER1                        ((uint32_t)4U)                          /*!< bus matrix2 master 1 */
#define BUSIM_BM2_MASTER2                        ((uint32_t)8U)                          /*!< bus matrix2 master 2 */
#define BUSIM_BM2_MASTER3                        ((uint32_t)12U)                         /*!< bus matrix2 master 3 */
#define BUSIM_BM2_MASTER4                        ((uint32_t)16U)                         /*!< bus matrix2 master 4 */
#define BUSIM_BM2_MASTER5                        ((uint32_t)20U)                         /*!< bus matrix2 master 5 */
#define BUSIM_BM2_MASTER6                        ((uint32_t)24U)                         /*!< bus matrix2 master 6 */

#define BUSIM_MASTER_PORT0                       ((uint32_t)0U)                          /*!< master port 0 */
#define BUSIM_MASTER_PORT1                       ((uint32_t)1U)                          /*!< master port 1 */
#define BUSIM_MASTER_PORT2                       ((uint32_t)2U)                          /*!< master port 2 */
#define BUSIM_MASTER_PORT3                       ((uint32_t)3U)                          /*!< master port 3 */
#define BUSIM_MASTER_PORT4                       ((uint32_t)4U)                          /*!< master port 4 */
#define BUSIM_MASTER_PORT5                       ((uint32_t)5U)                          /*!< master port 5 */
#define BUSIM_MASTER_PORT6                       ((uint32_t)6U)                          /*!< master port 6 */
#define BUSIM_MASTER_PORT7                       ((uint32_t)7U)                          /*!< master port 7 */

#define BUSIM_BM1_SLAVE0                         ((uint32_t)0x00000000U)                 /*!< bus matrix1 slave 0 */
#define BUSIM_BM1_SLAVE1                         ((uint32_t)0x00000001U)                 /*!< bus matrix1 slave 1 */
#define BUSIM_BM1_SLAVE2                         ((uint32_t)0x00000002U)                 /*!< bus matrix1 slave 2 */
#define BUSIM_BM1_SLAVE3                         ((uint32_t)0x00000003U)                 /*!< bus matrix1 slave 3 */
#define BUSIM_BM1_SLAVE4                         ((uint32_t)0x00000004U)                 /*!< bus matrix1 slave 4 */
#define BUSIM_BM2_SLAVE0                         ((uint32_t)0x00000008U)                 /*!< bus matrix2 slave 0 */
#define BUSIM_BM2_SLAVE1                         ((uint32_t)0x00000009U)                 /*!< bus matrix2 slave 1 */
#define BUSIM_BM2_SLAVE2                         ((uint32_t)0x0000000AU)                 /*!< bus matrix2 slave 2 */
#define BUSIM_BM2_SLAVE3                         ((uint32_t)0x0000000BU)                 /*!< bus matrix2 slave 3 */

#define PRIORITY_L1                              ((uint32_t)0x00000000U)                 /*!< master has L1 priority on associated slave port */
#define PRIORITY_L2                              ((uint32_t)0x00000001U)                 /*!< master has L1 priority on associated slave port */
#define PRIORITY_L3                              ((uint32_t)0x00000002U)                 /*!< master has L1 priority on associated slave port */
#define PRIORITY_L4                              ((uint32_t)0x00000003U)                 /*!< master has L1 priority on associated slave port */
#define PRIORITY_L5                              ((uint32_t)0x00000004U)                 /*!< master has L1 priority on associated slave port */
#define PRIORITY_L6                              ((uint32_t)0x00000005U)                 /*!< master has L1 priority on associated slave port */
#define PRIORITY_L7                              ((uint32_t)0x00000006U)                 /*!< master has L1 priority on associated slave port */
#define PRIORITY_L8                              ((uint32_t)0x00000007U)                 /*!< master has L1 priority on associated slave port */

#define BUSIM_ARBITRATION_ROUNDROBIN             ((uint32_t)0x00000000U)                 /*!< fixed priority mode */
#define BUSIM_ARBITRATION_FIXED                  BUSIM_CTL_ARBMOD                        /*!< round-robin priority mode */

#define BUSIM_TMRERR_EXTMPU                      BUSIM_TMRFCS_TMRERR_IE0                 /*!< TMR error 0 (EXTMPU) output to FMU */
#define BUSIM_TMRERR_IMICU                       BUSIM_TMRFCS_TMRERR_IE1                 /*!< TMR error 1 (IMICU) output to FMU */

#define BUSIM_TMRERR_FLAG_EXTMPU                 BUSIM_TMRFCS_TMRERR_STAT0               /*!< EXTMPU enable register TMR error status */
#define BUSIM_TMRERR_FLAG_IMICU                  BUSIM_TMRFCS_TMRERR_STAT1               /*!< IMICU enable register TMR error status */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

#define NOT_BUSIM_BM_SLAVE(slaveport)            (((slaveport) != BUSIM_BM1_SLAVE0) && ((slaveport) != BUSIM_BM1_SLAVE1) && \
                                                 ((slaveport) != BUSIM_BM1_SLAVE2) && ((slaveport) != BUSIM_BM1_SLAVE3) && \
                                                 ((slaveport) != BUSIM_BM1_SLAVE4) && ((slaveport) != BUSIM_BM2_SLAVE0) && \
                                                 ((slaveport) != BUSIM_BM2_SLAVE1) && ((slaveport) != BUSIM_BM2_SLAVE2) && \
                                                 ((slaveport) != BUSIM_BM2_SLAVE3))

#define NOT_BUSIM_ARBITRATION(aribitration)      (((aribitration) != BUSIM_ARBITRATION_FIXED)      && ((aribitration) != BUSIM_ARBITRATION_ROUNDROBIN))

#define NOT_BUSIM_BM_MASTER(masterport)          (((masterport) != BUSIM_BM1_MASTER0) && ((masterport) != BUSIM_BM1_MASTER1) && \
                                                 ((masterport) != BUSIM_BM1_MASTER2) && ((masterport) != BUSIM_BM1_MASTER3) && \
                                                 ((masterport) != BUSIM_BM1_MASTER4) && ((masterport) != BUSIM_BM1_MASTER5) && \
                                                 ((masterport) != BUSIM_BM1_MASTER6) && ((masterport) != BUSIM_BM1_MASTER7))

#define NOT_BUSIM_PRIORITY(priority)             (((priority) != PRIORITY_L1) && ((priority) != PRIORITY_L2) && \
                                                 ((priority) != PRIORITY_L3) && ((priority) != PRIORITY_L4) && \
                                                 ((priority) != PRIORITY_L5) && ((priority) != PRIORITY_L6) && \
                                                 ((priority) != PRIORITY_L7) && ((priority) != PRIORITY_L8))

#define NOT_BUSIM_MASTER_PORT(master_port)       (((master_port) != BUSIM_MASTER_PORT0) && ((master_port) != BUSIM_MASTER_PORT1) && \
                                                 ((master_port) != BUSIM_MASTER_PORT2) && ((master_port) != BUSIM_MASTER_PORT3) && \
                                                 ((master_port) != BUSIM_MASTER_PORT4) && ((master_port) != BUSIM_MASTER_PORT5) && \
                                                 ((master_port) != BUSIM_MASTER_PORT6) && ((master_port) != BUSIM_MASTER_PORT7))

#define NOT_BUSIM_DEFAULT_MASTER(defaultmaster)  (((defaultmaster) != BUSIM_DEFAULTMASTER_M0)   && ((defaultmaster) != BUSIM_DEFAULTMASTER_M1) && \
                                                 ((defaultmaster) != BUSIM_DEFAULTMASTER_M2)   && ((defaultmaster) != BUSIM_DEFAULTMASTER_M3) && \
                                                 ((defaultmaster) != BUSIM_DEFAULTMASTER_M4)   && ((defaultmaster) != BUSIM_DEFAULTMASTER_M5) && \
                                                 ((defaultmaster) != BUSIM_DEFAULTMASTER_M6)   && ((defaultmaster) != BUSIM_DEFAULTMASTER_M7) && \
                                                 ((defaultmaster) != BUSIM_DEFAULTMASTER_LAST))

#define NOT_BUSIM_TMRERR(tmrerr)                 (((tmrerr) != BUSIM_TMRERR_EXTMPU) && ((tmrerr) != BUSIM_TMRERR_IMICU))

#define NOT_BUSIM_TMRERR_FLAG(tmrerr_flag)       (((tmrerr_flag) != BUSIM_TMRERR_FLAG_EXTMPU) && ((tmrerr_flag) != BUSIM_TMRERR_FLAG_IMICU))

#endif /* FW_DEBUG_ERR_REPORT */


/* function declarations */
/* configure arbitration mode */
void busim_arbitration_config(uint32_t slaveport, uint32_t aribitration);
/* configure fixed priority */
void busim_fixed_priority_config(uint32_t slaveport, uint32_t masterport, uint32_t priority);
/* enable highest priority mode */
void busim_highest_priority_enable(uint32_t slaveport, uint32_t master_port);
/* disable highest priority mode */
void busim_highest_priority_disable(uint32_t slaveport, uint32_t master_port);
/* configure default access the slave port by the master port which is the last master accessed or determined by DMP[2:0] */
void busim_default_master_access_config(uint32_t slaveport, uint32_t defaultmaster);
/* lock BUSIM control and slave port priority configuration register */
void busim_reg_lock(uint32_t slaveport);

/* enable BUSIM TMR error */
void busim_tmr_error_enable(uint32_t tmerr);
/* disable BUSIM TMR error */
void busim_tmr_error_disable(uint32_t tmerr);
/* get TMR error interrupt flag */
FlagStatus busim_tmr_error_flag_get(uint32_t tmrerr_flag);
/* clear TMR error interrupt flag */
void busim_tmr_error_flag_clear(uint32_t tmrerr_flag);

#endif /* GD32A7XX_BUSIM_H */
