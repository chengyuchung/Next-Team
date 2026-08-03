/*!
   \file    gd32a7xx_extmpu.h
   \brief   definitions for the EXTMPU

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

#ifndef GD32A7XX_EXTMPU_H
#define GD32A7XX_EXTMPU_H

#include "gd32a7xx.h"

/* EXTMPU definitions */
#define EXTMPU                                          EXTMPU_BASE                         /*!< EXTMPU base address */

/* registers definitions */
#define EXTMPU_CS0                                      REG32(EXTMPU + 0x00000000U)         /*!< control and status register 0 */
#define EXTMPU_CS1                                      REG32(EXTMPU + 0x00000004U)         /*!< control and status register 1 */
#define EXTMPU_EADDR(master)                            REG32(EXTMPU + 0x0100U + (0x10U * ((uint32_t)master)))  /*!< error address register */
#define EXTMPU_EINF(master)                             REG32(EXTMPU + 0x0104U + (0x10U * ((uint32_t)master)))  /*!< error information register */
#define EXTMPU_EREG(master)                             REG32(EXTMPU + 0x0108U + (0x10U * ((uint32_t)master)))  /*!< error region register */
#define EXTMPU_CTL0(region)                             REG32(EXTMPU + 0x0200U + (0x10U * ((uint32_t)region)))  /*!< region control register 0 */
#define EXTMPU_CTL1(region)                             REG32(EXTMPU + 0x0204U + (0x10U * ((uint32_t)region)))  /*!< region control register 1 */
#define EXTMPU_CTL2(region)                             REG32(EXTMPU + 0x0208U + (0x10U * ((uint32_t)region)))  /*!< region control register 2 */
#define EXTMPU_CTL3(region)                             REG32(EXTMPU + 0x020CU + (0x10U * ((uint32_t)region)))  /*!< region control register 3 */

/* bits definitions */
/* EXTMPU_CS0 */
#define EXTMPU_CS0_MERRF                                BITS(0,15)                          /*!< error flag of master x */
#define EXTMPU_CS0_EXTMPUEN                             BIT(31)                             /*!< extended MPU enable */

/* EXTMPU_CS1 */
#define EXTMPU_CS1_MOVF                                 BITS(0,15)                          /*!< overrun flag of master x */

/* EXTMPU_EINF */
#define EXTMPU_EINF_ERRD                                BITS(25,26)                         /*!< error detailed information */
#define EXTMPU_EINF_EATYPE                              BIT(27)                             /*!< error access type */

/* EXTMPU_EREG */
#define EXTMPU_EREG_EACINF                              BITS(0,31)                          /*!< error access control information */

/* EXTMPU_CTL0 */
#define EXTMPU_CTL0_SADDR                               BITS(0,31)                          /*!< start address of region */

/* EXTMPU_CTL1 */
#define EXTMPU_CTL1_EADDR                               BITS(0,31)                          /*!< end address of region */

/* EXTMPU_CTL2 */
#define EXTMPU_CTL2_M0AP                                BITS(0,1)                           /*!< master 0 access permission */
#define EXTMPU_CTL2_M1AP                                BITS(2,3)                           /*!< master 1 access permission */
#define EXTMPU_CTL2_M2AP                                BITS(4,5)                           /*!< master 2 access permission */
#define EXTMPU_CTL2_M3AP                                BITS(6,7)                           /*!< master 3 access permission */
#define EXTMPU_CTL2_M4AP                                BITS(8,9)                           /*!< master 4 access permission */
#define EXTMPU_CTL2_M5AP                                BITS(10,11)                         /*!< master 5 access permission */
#define EXTMPU_CTL2_M6AP                                BITS(12,13)                         /*!< master 6 access permission */
#define EXTMPU_CTL2_M7AP                                BITS(14,15)                         /*!< master 7 access permission */
#define EXTMPU_CTL2_M8AP                                BITS(16,17)                         /*!< master 8 access permission */
#define EXTMPU_CTL2_M9AP                                BITS(18,19)                         /*!< master 9 access permission */
#define EXTMPU_CTL2_M10AP                               BITS(20,21)                         /*!< master 10 access permission */
#define EXTMPU_CTL2_M11AP                               BITS(22,23)                         /*!< master 11 access permission */
#define EXTMPU_CTL2_M12AP                               BITS(24,25)                         /*!< master 12 access permission */
#define EXTMPU_CTL2_M13AP                               BITS(26,27)                         /*!< master 13 access permission */
#define EXTMPU_CTL2_M14AP                               BITS(28,29)                         /*!< master 14 access permission */
#define EXTMPU_CTL2_M15AP                               BITS(30,31)                         /*!< master 15 access permission */

/* EXTMPU_CTL3 */
#define EXTMPU_CTL3_RVD                                 BIT(0)                              /*!< region valid */
#define EXTMPU_CTL3_RROEN                               BIT(1)                              /*!< region config read only control */

/* constants definitions */
/* error access detailed information */
#define EXTMPU_ERRD_INSTRUCTION_USER                    ((uint32_t)0U)                      /*!< instruction access in user mode */
#define EXTMPU_ERRD_DATA_USER                           ((uint32_t)1U)                      /*!< data access in user mode */
#define EXTMPU_ERRD_INSTRUCTION_PRIVILEGE               ((uint32_t)2U)                      /*!< instruction access in supervisor mode */
#define EXTMPU_ERRD_DATA_PRIVILEGE                      ((uint32_t)3U)                      /*!< data access in supervisor mode */

/* error access type */
#define EXTMPU_ERRTYPE_READ                             ((uint32_t)0U)                      /*!< error access type read */
#define EXTMPU_ERRTYPE_WRITE                            ((uint32_t)1U)                      /*!< error access type write */

#define EXTMPU_REGION0                                  ((uint8_t)0)                        /*!< EXTMPU region0  */
#define EXTMPU_REGION1                                  ((uint8_t)1)                        /*!< EXTMPU region1  */
#define EXTMPU_REGION2                                  ((uint8_t)2)                        /*!< EXTMPU region2  */
#define EXTMPU_REGION3                                  ((uint8_t)3)                        /*!< EXTMPU region3  */
#define EXTMPU_REGION4                                  ((uint8_t)4)                        /*!< EXTMPU region4  */
#define EXTMPU_REGION5                                  ((uint8_t)5)                        /*!< EXTMPU region5  */
#define EXTMPU_REGION6                                  ((uint8_t)6)                        /*!< EXTMPU region6  */
#define EXTMPU_REGION7                                  ((uint8_t)7)                        /*!< EXTMPU region7  */
#define EXTMPU_REGION8                                  ((uint8_t)8)                        /*!< EXTMPU region8  */
#define EXTMPU_REGION9                                  ((uint8_t)9)                        /*!< EXTMPU region9  */
#define EXTMPU_REGION10                                 ((uint8_t)10)                       /*!< EXTMPU region10 */
#define EXTMPU_REGION11                                 ((uint8_t)11)                       /*!< EXTMPU region11 */
#define EXTMPU_REGION12                                 ((uint8_t)12)                       /*!< EXTMPU region12 */
#define EXTMPU_REGION13                                 ((uint8_t)13)                       /*!< EXTMPU region13 */
#define EXTMPU_REGION14                                 ((uint8_t)14)                       /*!< EXTMPU region14 */
#define EXTMPU_REGION15                                 ((uint8_t)15)                       /*!< EXTMPU region15 */
#define EXTMPU_REGION16                                 ((uint8_t)16)                       /*!< EXTMPU region16 */
#define EXTMPU_REGION17                                 ((uint8_t)17)                       /*!< EXTMPU region17 */
#define EXTMPU_REGION18                                 ((uint8_t)18)                       /*!< EXTMPU region18 */
#define EXTMPU_REGION19                                 ((uint8_t)19)                       /*!< EXTMPU region19 */
#define EXTMPU_REGION20                                 ((uint8_t)20)                       /*!< EXTMPU region20 */
#define EXTMPU_REGION21                                 ((uint8_t)21)                       /*!< EXTMPU region21 */
#define EXTMPU_REGION22                                 ((uint8_t)22)                       /*!< EXTMPU region22 */
#define EXTMPU_REGION23                                 ((uint8_t)23)                       /*!< EXTMPU region23 */
#define EXTMPU_REGION24                                 ((uint8_t)24)                       /*!< EXTMPU region24 */
#define EXTMPU_REGION25                                 ((uint8_t)25)                       /*!< EXTMPU region25 */
#define EXTMPU_REGION26                                 ((uint8_t)26)                       /*!< EXTMPU region26 */
#define EXTMPU_REGION27                                 ((uint8_t)27)                       /*!< EXTMPU region27 */
#define EXTMPU_REGION28                                 ((uint8_t)28)                       /*!< EXTMPU region28 */
#define EXTMPU_REGION29                                 ((uint8_t)29)                       /*!< EXTMPU region29 */
#define EXTMPU_REGION30                                 ((uint8_t)30)                       /*!< EXTMPU region30 */
#define EXTMPU_REGION31                                 ((uint8_t)31)                       /*!< EXTMPU region31 */

/* region access permission */
#define EXTMPU_ACCESS_FORBIDDEN                         ((uint8_t)0x00U)                    /*!< access permission forbidden */
#define EXTMPU_ACCESS_READONLY                          ((uint8_t)0x01U)                    /*!< access permission read only */
#define EXTMPU_ACCESS_WRITEONLY                         ((uint8_t)0x02U)                    /*!< access permission write only */
#define EXTMPU_ACCESS_READWRITE                         ((uint8_t)0x03U)                    /*!< access permission read write */

#define MASTER_PORT0                                    ((uint32_t)0U)                      /*!< master port0  */
#define MASTER_PORT1                                    ((uint32_t)1U)                      /*!< master port1  */
#define MASTER_PORT2                                    ((uint32_t)2U)                      /*!< master port2  */
#define MASTER_PORT3                                    ((uint32_t)3U)                      /*!< master port3  */
#define MASTER_PORT4                                    ((uint32_t)4U)                      /*!< master port4  */
#define MASTER_PORT5                                    ((uint32_t)5U)                      /*!< master port5  */
#define MASTER_PORT7                                    ((uint32_t)7U)                      /*!< master port7  */
#define MASTER_PORT10                                   ((uint32_t)10U)                     /*!< master port10 */
#define MASTER_PORT11                                   ((uint32_t)11U)                     /*!< master port11 */
#define MASTER_PORT12                                   ((uint32_t)12U)                     /*!< master port12 */
#define MASTER_PORT14                                   ((uint32_t)14U)                     /*!< master port14 */

#define MASTER_ID0                                      BIT(0)                              /*!< master ID0  */
#define MASTER_ID1                                      BIT(1)                              /*!< master ID1  */
#define MASTER_ID2                                      BIT(2)                              /*!< master ID2  */
#define MASTER_ID3                                      BIT(3)                              /*!< master ID3  */
#define MASTER_ID4                                      BIT(4)                              /*!< master ID4  */
#define MASTER_ID5                                      BIT(5)                              /*!< master ID5  */
#define MASTER_ID7                                      BIT(7)                              /*!< master ID7  */
#define MASTER_ID10                                     BIT(10)                             /*!< master ID10 */
#define MASTER_ID11                                     BIT(11)                             /*!< master ID11 */
#define MASTER_ID12                                     BIT(12)                             /*!< master ID12 */
#define MASTER_ID14                                     BIT(14)                             /*!< master ID14 */

/* EXTMPU error status parameter struct definitions */
typedef struct {
    uint32_t master;                                    /*!< master */
    uint32_t region;                                    /*!< region */
    uint32_t error_address;                             /*!< error address */
    uint32_t error_type;                                /*!< error access type */
    uint32_t error_detail;                              /*!< error detailed information */
} extmpu_error_status;

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

#define NOT_EXTMPU_REGION(region)                       (((region) != EXTMPU_REGION0)  && ((region) != EXTMPU_REGION1) && \
                                                        ((region) != EXTMPU_REGION2)  && ((region) != EXTMPU_REGION3) && \
                                                        ((region) != EXTMPU_REGION4)  && ((region) != EXTMPU_REGION5) && \
                                                        ((region) != EXTMPU_REGION6)  && ((region) != EXTMPU_REGION7) && \
                                                        ((region) != EXTMPU_REGION8)  && ((region) != EXTMPU_REGION9) && \
                                                        ((region) != EXTMPU_REGION10) && ((region) != EXTMPU_REGION11) && \
                                                        ((region) != EXTMPU_REGION12) && ((region) != EXTMPU_REGION13) && \
                                                        ((region) != EXTMPU_REGION14) && ((region) != EXTMPU_REGION15) && \
                                                        ((region) != EXTMPU_REGION16) && ((region) != EXTMPU_REGION17) && \
                                                        ((region) != EXTMPU_REGION18) && ((region) != EXTMPU_REGION19) && \
                                                        ((region) != EXTMPU_REGION20) && ((region) != EXTMPU_REGION21) && \
                                                        ((region) != EXTMPU_REGION22) && ((region) != EXTMPU_REGION23) && \
                                                        ((region) != EXTMPU_REGION24) && ((region) != EXTMPU_REGION25) && \
                                                        ((region) != EXTMPU_REGION26) && ((region) != EXTMPU_REGION27) && \
                                                        ((region) != EXTMPU_REGION28) && ((region) != EXTMPU_REGION29) && \
                                                        ((region) != EXTMPU_REGION30) && ((region) != EXTMPU_REGION31))

#define NOT_EXTMPU_MASTER_PORT(master_port)             (((master_port) != MASTER_PORT0)  && ((master_port) != MASTER_PORT1) && \
                                                        ((master_port) != MASTER_PORT2)  && ((master_port) != MASTER_PORT3) && \
                                                        ((master_port) != MASTER_PORT4)  && ((master_port) != MASTER_PORT5) && \
                                                        ((master_port) != MASTER_PORT7)  && ((master_port) != MASTER_PORT10) && \
                                                        ((master_port) != MASTER_PORT11) && ((master_port) != MASTER_PORT12) && \
                                                        ((master_port) != MASTER_PORT14))

#define NOT_EXTMPU_ACCESS_PERMISSION(permission)        (((permission) != EXTMPU_ACCESS_FORBIDDEN) && ((permission) != EXTMPU_ACCESS_READONLY) && \
                                                        ((permission) != EXTMPU_ACCESS_WRITEONLY) && ((permission) != EXTMPU_ACCESS_READWRITE))

#define NOT_EXTMPU_MASTER_ID(master_id)                 (((master_id) != MASTER_ID0)  && ((master_id) != MASTER_ID1) && \
                                                        ((master_id) != MASTER_ID2)  && ((master_id) != MASTER_ID3) && \
                                                        ((master_id) != MASTER_ID4)  && ((master_id) != MASTER_ID5) && \
                                                        ((master_id) != MASTER_ID7)  && ((master_id) != MASTER_ID10) && \
                                                        ((master_id) != MASTER_ID11) && ((master_id) != MASTER_ID12) && \
                                                        ((master_id) != MASTER_ID14))

#endif /* FW_DEBUG_ERR_REPORT */


/* function declarations */
/* enable EXTMPU */
void extmpu_enable(void);
/* disable EXTMPU */
void extmpu_disable(void);

/* enable EXTMPU region */
void extmpu_region_enable(uint8_t region);
/* disable EXTMPU region */
void extmpu_region_disable(uint8_t region);
/* lock EXTMPU control register 0~3 of specific region */
void extmpu_region_reg_lock(uint8_t region);

/* configure region start address, size and permission */
void extmpu_region_config(uint8_t region, uint32_t startaddress, uint32_t size, uint32_t allpermission);
/* configure region access permission */
void extmpu_region_access_permission_config(uint8_t region, uint8_t master_port, uint8_t permission);

/* get EXTMPU error status */
FlagStatus extmpu_error_status_get(extmpu_error_status *status);
/* get EXTMPU overrun flag */
FlagStatus extmpu_overrun_flag_get(uint32_t master_id);
/* clear EXTMPU overrun flag */
void extmpu_error_overrun_flag_clear(uint32_t master_id);
/* clear EXTMPU error information */
void extmpu_error_region_info_clear(uint32_t master_id);

#endif /* GD32A7XX_EXTMPU_H */
