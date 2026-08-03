/*!
   \file    gd32a7xx_imicu.h
   \brief   definitions for the IMICU

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

#ifndef GD32A7XX_IMICU_H
#define GD32A7XX_IMICU_H

#include "gd32a7xx.h"

/* IMICU definitions */
#define IMICU_BM1                                   IMICU_BASE
#define IMICU_BM2                                   (IMICU_BASE + 0x00000400U)

/* registers definitions */
#define IMICU_EDCTL(bmx)                            REG32((bmx) + 0x00000000U)      /*!< Error dection control register */
#define IMICU_EICTL(bmx)                            REG32((bmx) + 0x00000004U)      /*!< Error injection control register */
#define IMICU_ERRSTAT(bmx)                          REG32((bmx) + 0x00000008U)      /*!< Error status register */

/* bits definitions */
/* IMICU_EDCTL */
#define IMICU_EDCTL_M7EDCEN                         BIT(16)                         /*!< Master port 7 error detection enable bit */
#define IMICU_EDCTL_M6EDCEN                         BIT(17)                         /*!< Master port 6 error detection enable bit */
#define IMICU_EDCTL_M5EDCEN                         BIT(18)                         /*!< Master port 5 error detection enable bit */
#define IMICU_EDCTL_M4EDCEN                         BIT(19)                         /*!< Master port 4 error detection enable bit */
#define IMICU_EDCTL_M3EDCEN                         BIT(20)                         /*!< Master port 3 error detection enable bit */
#define IMICU_EDCTL_M2EDCEN                         BIT(21)                         /*!< Master port 2 error detection enable bit */
#define IMICU_EDCTL_M1EDCEN                         BIT(22)                         /*!< Master port 1 error detection enable bit */
#define IMICU_EDCTL_M0EDCEN                         BIT(23)                         /*!< Master port 0 error detection enable bit */
#define IMICU_EDCTL_S7EDCEN                         BIT(24)                         /*!< Slave port 7 error detection enable bit */
#define IMICU_EDCTL_S6EDCEN                         BIT(25)                         /*!< Slave port 6 error detection enable bit */
#define IMICU_EDCTL_S5EDCEN                         BIT(26)                         /*!< Slave port 5 error detection enable bit */
#define IMICU_EDCTL_S4EDCEN                         BIT(27)                         /*!< Slave port 4 error detection enable bit */
#define IMICU_EDCTL_S3EDCEN                         BIT(28)                         /*!< Slave port 3 error detection enable bit */
#define IMICU_EDCTL_S2EDCEN                         BIT(29)                         /*!< Slave port 2 error detection enable bit */
#define IMICU_EDCTL_S1EDCEN                         BIT(30)                         /*!< Slave port 1 error detection enable bit */
#define IMICU_EDCTL_S0EDCEN                         BIT(31)                         /*!< Slave port 0 error detection enable bit */

/* IMICU_EICTL */
#define IMICU_EICTL_EDCVAL                          BITS(0,6)                       /*!< Calculated EDC code value */
#define IMICU_EICTL_MPID                            BITS(7,10)                      /*!< Target master port ID */
#define IMICU_EICTL_SPID                            BITS(11,14)                     /*!< Target slave port ID */
#define IMICU_EICTL_EIEN                            BIT(15)                         /*!< Error injection function enable bit */
#define IMICU_EICTL_EDCVAL_DATA                     BITS(16,22)                     /*!< Calculated EDC code value with data phase */
#define IMICU_EICTL_MPID_DATA                       BITS(23,26)                     /*!< Target master port ID with data phase */
#define IMICU_EICTL_SPID_DATA                       BITS(27,30)                     /*!< Target slave port ID with data phase */
#define IMICU_EICTL_EIEN_DATA                       BIT(31)                         /*!< Error injection function enable bit with data phase */

/* IMICU_ERRSTAT */
#define IMICU_ERRSTAT_EDCVAL                        BITS(0,6)                       /*!< Calculated EDC code value */
#define IMICU_ERRSTAT_MPID                          BITS(7,10)                      /*!< Target master port ID */
#define IMICU_ERRSTAT_SPID                          BITS(11,14)                     /*!< Target slave port ID */
#define IMICU_ERRSTAT_EDVF                          BIT(15)                         /*!< Error detected valid flag */
#define IMICU_ERRSTAT_EDCVAL_DATA                   BITS(16,22)                     /*!< Calculated EDC code value with data phase */
#define IMICU_ERRSTAT_MPID_DATA                     BITS(23,26)                     /*!< Target master port ID with data phase */
#define IMICU_ERRSTAT_SPID_DATA                     BITS(27,30)                     /*!< Target slave port ID with data phase */
#define IMICU_ERRSTAT_EDVF_DATA                     BIT(31)                         /*!< Error detected valid flag with data phase */

/* constants definitions */
/* Bus matrix port define */
#define IMICU_PORT_M0                               IMICU_EDCTL_M0EDCEN            /*!< Master port 0 (FMC-0 of BM1, AHB1 of BM2) */
#define IMICU_PORT_M1                               IMICU_EDCTL_M1EDCEN            /*!< Master port 1 (FMC-1 of BM1, AHB2 of BM2) */
#define IMICU_PORT_M2                               IMICU_EDCTL_M2EDCEN            /*!< Master port 2 (FMC-2 of BM1, APB1 of BM2) */
#define IMICU_PORT_M3                               IMICU_EDCTL_M3EDCEN            /*!< Master port 3 (SRAM0 of BM1, APB2 of BM2) */
#define IMICU_PORT_M4                               IMICU_EDCTL_M4EDCEN            /*!< Master port 4 (SRAM1 of BM1, reserved of BM2) */
#define IMICU_PORT_M5                               IMICU_EDCTL_M5EDCEN            /*!< Master port 5 (TCMSRAM of BM1, reserved of BM2) */
#define IMICU_PORT_M6                               IMICU_EDCTL_M6EDCEN            /*!< Master port 6 (QSPI of BM1, reserved of BM2) */
#define IMICU_PORT_M7                               IMICU_EDCTL_M7EDCEN            /*!< Master port 7 (BM1toBM2 of BM1, reserved of BM2 for GD32A72xxx/GD32A74xxx devices) \
                                                                                       (reserved of BM1, reserved of BM2 for GD32A71xxx devices) */
#define IMICU_PORT_S0                               IMICU_EDCTL_S0EDCEN            /*!< Slave port 0 (CM7_0 of BM1, BM1toBM2 of BM2) */
#define IMICU_PORT_S1                               IMICU_EDCTL_S1EDCEN            /*!< Slave port 1 (CM7_1 of BM1, DMA0_MEM of BM2) */
#define IMICU_PORT_S2                               IMICU_EDCTL_S2EDCEN            /*!< Slave port 2 (DMA0_MEM of BM1, DMA1MEM of BM2) */
#define IMICU_PORT_S3                               IMICU_EDCTL_S3EDCEN            /*!< Slave port 3 (DMA1_MEM of BM1, AHBP(CM7_0) of BM2) */
#define IMICU_PORT_S4                               IMICU_EDCTL_S4EDCEN            /*!< Slave port 4 (HSM of BM1, AHBP(CM7_1) of BM2) */
#define IMICU_PORT_S5                               IMICU_EDCTL_S5EDCEN            /*!< Slave port 5 (ENET of BM1, DMA0_PERI of BM2) */
#define IMICU_PORT_S6                               IMICU_EDCTL_S6EDCEN            /*!< Slave port 6 (DMA0_PERI of BM1, DMA1_PERI of BM2) */
#define IMICU_PORT_S7                               IMICU_EDCTL_S7EDCEN            /*!< Slave port 7 (DMA1_PERI of BM1, reserved of BM2) */
#define IMICU_PORT_ALL                              ((uint32_t)0xFFFF0000U)         /*!< All ports */

/* Master ID */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define IMICU_MPID_FMC_0            ((uint32_t)0U)          /*!< Master ID of FMC-0 */
#define IMICU_MPID_FMC_1            ((uint32_t)1U)          /*!< Master ID of FMC-1 */
#define IMICU_MPID_FMC_2            ((uint32_t)2U)          /*!< Master ID of FMC-2 */
#define IMICU_MPID_SRAM0            ((uint32_t)3U)          /*!< Master ID of SRAM0 */
#define IMICU_MPID_SRAM1            ((uint32_t)4U)          /*!< Master ID of SRAM1 */
#define IMICU_MPID_TCMSRAM          ((uint32_t)5U)          /*!< Master ID of TCMSRAM */
#define IMICU_MPID_QSPI             ((uint32_t)6U)          /*!< Master ID of QSPI */
#define IMICU_MPID_AHB1             ((uint32_t)8U)          /*!< Master ID of AHB1 */
#define IMICU_MPID_AHB2             ((uint32_t)9U)          /*!< Master ID of AHB2 */
#define IMICU_MPID_APB1             ((uint32_t)10U)         /*!< Master ID of APB1 */
#define IMICU_MPID_APB2             ((uint32_t)11U)         /*!< Master ID of APB2 */
#elif defined(GD32A711X_A712X)
#define IMICU_MPID_FMC_0            ((uint32_t)0U)          /*!< Master ID of FMC-0 */
#define IMICU_MPID_FMC_2            ((uint32_t)2U)          /*!< Master ID of FMC-2 */
#define IMICU_MPID_SRAM0            ((uint32_t)3U)          /*!< Master ID of SRAM0 */
#define IMICU_MPID_TCMSRAM          ((uint32_t)5U)          /*!< Master ID of TCMSRAM */
#define IMICU_MPID_QSPI             ((uint32_t)6U)          /*!< Master ID of QSPI */
#define IMICU_MPID_AHB1             ((uint32_t)8U)          /*!< Master ID of AHB1 */
#define IMICU_MPID_AHB2             ((uint32_t)9U)          /*!< Master ID of AHB2 */
#define IMICU_MPID_APB1             ((uint32_t)10U)         /*!< Master ID of APB1 */
#define IMICU_MPID_APB2             ((uint32_t)11U)         /*!< Master ID of APB2 */
#else
#endif

/* Slaver ID */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define IMICU_SPID_AXIM_CM7_0       ((uint32_t)0U)          /*!< Slaver ID of AXIM (CM7_0) */
#define IMICU_SPID_AXIM_CM7_1       ((uint32_t)1U)          /*!< Slaver ID of AXIM (CM7_1) */
#define IMICU_SPID_DMA0_MEM         ((uint32_t)2U)          /*!< Slaver ID of DMA0_MEM */
#define IMICU_SPID_DMA1_MEM         ((uint32_t)3U)          /*!< Slaver ID of DMA1_MEM */
#define IMICU_SPID_HSM_CM23         ((uint32_t)4U)          /*!< Slaver ID of HSM_CM23 */
#define IMICU_SPID_ENET             ((uint32_t)5U)          /*!< Slaver ID of ENET */
#define IMICU_SPID_AHBP_CM7_0       ((uint32_t)7U)          /*!< Slaver ID of AHBP (CM7_1) */
#define IMICU_SPID_DMA0_PEIRPH      ((uint32_t)10U)         /*!< Slaver ID of DMA0_PEIRPH */
#define IMICU_SPID_DMA1_PEIRPH      ((uint32_t)11U)         /*!< Slaver ID of DMA1_PEIRPH */
#define IMICU_SPID_HSM_DMA          ((uint32_t)12U)         /*!< Slaver ID of HSM_DMA */
#define IMICU_SPID_AHBP_CM7_1       ((uint32_t)14U)         /*!< Slaver ID of AXIM AHBP (CM7_1) */
#elif defined(GD32A711X_A712X)
#define IMICU_SPID_AXIM_CM7_0       ((uint32_t)0U)          /*!< Slaver ID of AXIM (CM7_0) */
#define IMICU_SPID_DMA0_MEM         ((uint32_t)2U)          /*!< Slaver ID of DMA0_MEM */
#define IMICU_SPID_DMA1_MEM         ((uint32_t)3U)          /*!< Slaver ID of DMA1_MEM */
#define IMICU_SPID_HSM_CM23         ((uint32_t)4U)          /*!< Slaver ID of HSM_CM23 */
#define IMICU_SPID_DMA0_PEIRPH      ((uint32_t)10U)         /*!< Slaver ID of DMA0_PEIRPH */
#define IMICU_SPID_DMA1_PEIRPH      ((uint32_t)11U)         /*!< Slaver ID of DMA1_PEIRPH */
#define IMICU_SPID_HSM_DMA          ((uint32_t)12U)         /*!< Slaver ID of HSM_DMA */
#define IMICU_SPID_AHBP_CM7_0       ((uint32_t)14U)         /*!< Slaver ID of AXIM AHBP (CM7_0) */
#else
#endif

/* error injection phase */
typedef enum {
    IMICU_PHASE_CMD = 0U,               /*!< cmd phase, from master to slaver */
    IMICU_PHASE_DATA                    /*!< data phase, from slaver to master */
} imicu_phase_enum;

/* IMICU error status parameter struct definitions */
typedef struct {
    uint32_t    mpid;                   /*!< error master port ID */
    uint32_t    spid;                   /*!< error slave port ID */
    uint32_t    edc;                    /*!< error EDC code value */
} imicu_error_status_struct;

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check peripherals */
#define NOT_IMICU_BUS_MATRIX(bm)         (((bm) != IMICU_BM1) && ((bm) != IMICU_BM2))

/* check imicu port */
#define NOT_IMICU_PORT(port)             (((port) != IMICU_PORT_M0)   && \
                                          ((port) != IMICU_PORT_M1)   && \
                                          ((port) != IMICU_PORT_M2)   && \
                                          ((port) != IMICU_PORT_M3)   && \
                                          ((port) != IMICU_PORT_M4)   && \
                                          ((port) != IMICU_PORT_M5)   && \
                                          ((port) != IMICU_PORT_M6)   && \
                                          ((port) != IMICU_PORT_M7)   && \
                                          ((port) != IMICU_PORT_S0)   && \
                                          ((port) != IMICU_PORT_S1)   && \
                                          ((port) != IMICU_PORT_S2)   && \
                                          ((port) != IMICU_PORT_S3)   && \
                                          ((port) != IMICU_PORT_S4)   && \
                                          ((port) != IMICU_PORT_S5)   && \
                                          ((port) != IMICU_PORT_S6)   && \
                                          ((port) != IMICU_PORT_S7)   && \
                                          ((port) != IMICU_PORT_ALL))

/* check imicu slaver id */
#if defined(GD32A714X) || defined(GD32A72XX) || defined(GD32A74XX)
#define NOT_IMICU_SLAVER_ID(mpid)        (((mpid) != IMICU_SPID_AXIM_CM7_0 )   && \
                                          ((mpid) != IMICU_SPID_AXIM_CM7_1 )   && \
                                          ((mpid) != IMICU_SPID_DMA0_MEM   )   && \
                                          ((mpid) != IMICU_SPID_DMA1_MEM   )   && \
                                          ((mpid) != IMICU_SPID_HSM_CM23   )   && \
                                          ((mpid) != IMICU_SPID_ENET       )   && \
                                          ((mpid) != IMICU_SPID_AHBP_CM7_0 )   && \
                                          ((mpid) != IMICU_SPID_DMA0_PEIRPH)   && \
                                          ((mpid) != IMICU_SPID_DMA1_PEIRPH)   && \
                                          ((mpid) != IMICU_SPID_AHBP_CM7_1 ))
#elif defined(GD32A711X_A712X)
#define NOT_IMICU_SLAVER_ID(mpid)        (((mpid) != IMICU_SPID_AXIM_CM7_0 )   && \
                                          ((mpid) != IMICU_SPID_DMA0_MEM   )   && \
                                          ((mpid) != IMICU_SPID_DMA1_MEM   )   && \
                                          ((mpid) != IMICU_SPID_HSM_CM23   )   && \
                                          ((mpid) != IMICU_SPID_AHBP_CM7_0 )   && \
                                          ((mpid) != IMICU_SPID_DMA0_PEIRPH)   && \
                                          ((mpid) != IMICU_SPID_DMA1_PEIRPH))
#else
#endif

/* check imicu master id */
#if defined(GD32A714X) || defined(GD32A72XX) || defined(GD32A74XX)
#define NOT_IMICU_MASTER_ID(spid)        (((spid) != IMICU_MPID_FMC_0  )   && \
                                          ((spid) != IMICU_MPID_FMC_1  )   && \
                                          ((spid) != IMICU_MPID_FMC_2  )   && \
                                          ((spid) != IMICU_MPID_SRAM0  )   && \
                                          ((spid) != IMICU_MPID_SRAM1  )   && \
                                          ((spid) != IMICU_MPID_TCMSRAM)   && \
                                          ((spid) != IMICU_MPID_QSPI   )   && \
                                          ((spid) != IMICU_MPID_AHB1   )   && \
                                          ((spid) != IMICU_MPID_AHB2   )   && \
                                          ((spid) != IMICU_MPID_APB1   )   && \
                                          ((spid) != IMICU_MPID_APB2   ))
#elif defined(GD32A711X_A712X)
#define NOT_IMICU_MASTER_ID(spid)        (((spid) != IMICU_MPID_FMC_0  )   && \
                                          ((spid) != IMICU_MPID_FMC_2  )   && \
                                          ((spid) != IMICU_MPID_SRAM0  )   && \
                                          ((spid) != IMICU_MPID_TCMSRAM)   && \
                                          ((spid) != IMICU_MPID_QSPI   )   && \
                                          ((spid) != IMICU_MPID_AHB1   )   && \
                                          ((spid) != IMICU_MPID_AHB2   )   && \
                                          ((spid) != IMICU_MPID_APB1   )   && \
                                          ((spid) != IMICU_MPID_APB2   ))
#else
#endif

/* check imicu phase */
#define NOT_IMICU_PHASE(phase)           (((phase) != IMICU_PHASE_CMD)   && \
                                          ((phase) != IMICU_PHASE_DATA))

/* check the range of EDC code value  */
#define IMICU_EDC_CODE_HIGH              ((uint32_t)0x7FU)
#define NOT_IMICU_EDC_CODE(edc)          ((edc) > IMICU_EDC_CODE_HIGH)
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* enable imicu error detection */
void imicu_error_detection_enable(uint32_t bmx, uint32_t port);
/* disable imicu error detection */
void imicu_error_detection_disable(uint32_t bmx, uint32_t port);

/* config imicu error injection */
ErrStatus imicu_error_injection_config(uint32_t bmx, imicu_phase_enum phase, uint32_t mpid, uint32_t spid, uint32_t edc);
/* enable imicu error injection */
void imicu_error_injection_enable(uint32_t bmx, imicu_phase_enum phase);
/* disable imicu error injection */
void imicu_error_injection_disable(uint32_t bmx, imicu_phase_enum phase);

/* get error flags */
FlagStatus imicu_error_flag_get(uint32_t bmx, imicu_phase_enum phase);
/* get error status */
FlagStatus imicu_error_status_get(uint32_t bmx, imicu_phase_enum phase, imicu_error_status_struct *status);

#endif /* GD32A7XX_IMICU_H */
