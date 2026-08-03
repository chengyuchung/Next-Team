/*!
    \file    gd32a7xx_imicu.c
    \brief   IMICU driver

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

#include "gd32a7xx_imicu.h"

/* IMICU register bit offset */
#define IMICU_EICTL_EDCVAL_OFFSET       ((uint32_t)0U)      /* bit offset of EDCVAL in IMICU_EICTL */
#define IMICU_EICTL_MPID_OFFSET         ((uint32_t)7U)      /* bit offset of MPID in IMICU_EICTL */
#define IMICU_EICTL_SPID_OFFSET         ((uint32_t)11U)     /* bit offset of SPID in IMICU_EICTL */
#define IMICU_EICTL_EDCVAL_DATA_OFFSET  ((uint32_t)16U)     /* bit offset of EDCVAL_DATA in IMICU_EICTL */
#define IMICU_EICTL_MPID_DATA_OFFSET    ((uint32_t)23U)     /* bit offset of MPID_DATA in IMICU_EICTL */
#define IMICU_EICTL_SPID_DATA_OFFSET    ((uint32_t)27U)     /* bit offset of SPID_DATA in IMICU_EICTL */

/*!
    \brief      enable imicu error detection enable (API_ID: 0x0001U)
    \param[in]  bmx: IMICU_BMx(x=1,2)
    \param[in]  port: specify the bus matrix port
                one or more parameters can be selected which is shown as below:
      \arg        IMICU_PORT_Mx(x = 0..7): Master port x
      \arg        IMICU_PORT_Sx(x = 0..7): Slave port x
      \arg        IMICU_PORT_ALL: all Master/Slave ports
    \param[out] none
    \retval     none
*/
void imicu_error_detection_enable(uint32_t bmx, uint32_t port)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_IMICU_BUS_MATRIX(bmx)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else if(NOT_IMICU_PORT(port)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0001U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IMICU_EDCTL(bmx) |= port;
    }
}

/*!
    \brief      disable imicu error detection disable (API_ID: 0x0002U)
    \param[in]  bmx: IMICU_BMx(x=1,2)
    \param[in]  port: specify the bus matrix port
                one or more parameters can be selected which is shown as below:
      \arg        IMICU_PORT_Mx(x = 0..7): Master port x
      \arg        IMICU_PORT_Sx(x = 0..7): Slave port x
      \arg        IMICU_PORT_ALL: all Master/Slave ports
    \param[out] none
    \retval     none
*/
void imicu_error_detection_disable(uint32_t bmx, uint32_t port)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_IMICU_BUS_MATRIX(bmx)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0002U), ERR_PERIPH);
    } else if(NOT_IMICU_PORT(port)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        IMICU_EDCTL(bmx) &= (~port);
    }
}

/*!
    \brief      config imicu error injection config (API_ID: 0x0003U)
    \param[in]  bmx: IMICU_BMx(x=1,2)
    \param[in]  phase: IMICU phase
               only one parameter can be selected which is shown as below:
      \arg        IMICU_PHASE_CMD :cmd phase, from master to slaver
      \arg        IMICU_PHASE_DATA :data phase, from slaver to master
    \param[in]  mpid: specify the master port id
               only one parameter can be selected which is shown as below:
      \arg        IMICU_MPID_FMC_0  : Master ID of FMC-0
      \arg        IMICU_MPID_FMC_1  : Master ID of FMC-1
      \arg        IMICU_MPID_FMC_2  : Master ID of FMC-2
      \arg        IMICU_MPID_SRAM0  : Master ID of SRAM0
      \arg        IMICU_MPID_SRAM1  : Master ID of SRAM1
      \arg        IMICU_MPID_TCMSRAM: Master ID of TCMSRAM
      \arg        IMICU_MPID_QSPI   : Master ID of QSPI
      \arg        IMICU_MPID_AHB1   : Master ID of AHB1
      \arg        IMICU_MPID_AHB2   : Master ID of AHB2
      \arg        IMICU_MPID_APB1   : Master ID of APB1
      \arg        IMICU_MPID_APB2   : Master ID of APB2
    \param[in]  spid: specify the slave port id
               only one parameter can be selected which is shown as below:
      \arg        IMICU_SPID_AXIM_CM7_0 : Slaver ID of AXIM (CM7_0)
      \arg        IMICU_SPID_AXIM_CM7_1 : Slaver ID of AXIM (CM7_1)
      \arg        IMICU_SPID_DMA0_MEM   : Slaver ID of DMA0_MEM
      \arg        IMICU_SPID_DMA1_MEM   : Slaver ID of DMA1_MEM
      \arg        IMICU_SPID_HSM_CM23   : Slaver ID of HSM_CM23
      \arg        IMICU_SPID_ENET       : Slaver ID of ENET
      \arg        IMICU_SPID_AHBP_CM7_0 : Slaver ID of AHBP (CM7_1)
      \arg        IMICU_SPID_DMA0_PEIRPH: Slaver ID of DMA0_PEIRPH
      \arg        IMICU_SPID_DMA1_PEIRPH: Slaver ID of DMA1_PEIRPH
      \arg        IMICU_SPID_HSM_DMA    : Slaver ID of HSM_DMA (not available when phase is IMICU_PHASE_DATA)
      \arg        IMICU_SPID_AHBP_CM7_1 : Slaver ID of AXIM AHBP (CM7_1)
    \param[in]  edc: specify the calculated EDC code value, 0x00~0x7F
    \param[out] none
    \retval     ErrStatus: SUCCESS-config successful, ERROR-error injection is enabled
*/
ErrStatus imicu_error_injection_config(uint32_t bmx, imicu_phase_enum phase, uint32_t mpid, uint32_t spid, uint32_t edc)
{
    ErrStatus err = ERROR;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_IMICU_BUS_MATRIX(bmx)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_IMICU_PHASE(phase)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_IMICU_MASTER_ID(mpid)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_IMICU_SLAVER_ID(spid)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else if(NOT_IMICU_EDC_CODE(edc)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(phase == IMICU_PHASE_CMD) {
            if(0U != (IMICU_EICTL(bmx) & IMICU_EICTL_EIEN)) {
                err = ERROR;
            } else {
                /* clear edc/mpid/spid */
                IMICU_EICTL(bmx) &= ~IMICU_EICTL_EDCVAL;
                IMICU_EICTL(bmx) &= ~IMICU_EICTL_MPID;
                IMICU_EICTL(bmx) &= ~IMICU_EICTL_SPID;
                /* set edc/mpid/spid */
                IMICU_EICTL(bmx) |= (IMICU_EICTL_EDCVAL & ((uint32_t)edc << IMICU_EICTL_EDCVAL_OFFSET));
                IMICU_EICTL(bmx) |= (IMICU_EICTL_MPID & ((uint32_t)mpid << IMICU_EICTL_MPID_OFFSET));
                IMICU_EICTL(bmx) |= (IMICU_EICTL_SPID & ((uint32_t)spid << IMICU_EICTL_SPID_OFFSET));
                err = SUCCESS;
            }
        } else {
            if(0U != (IMICU_EICTL(bmx) & IMICU_EICTL_EIEN_DATA)) {
                err = ERROR;
            } else {
                /* clear edc/mpid/spid */
                IMICU_EICTL(bmx) &= ~IMICU_EICTL_EDCVAL_DATA;
                IMICU_EICTL(bmx) &= ~IMICU_EICTL_MPID_DATA;
                IMICU_EICTL(bmx) &= ~IMICU_EICTL_SPID_DATA;
                /* set edc/mpid/spid */
                IMICU_EICTL(bmx) |= (IMICU_EICTL_EDCVAL_DATA & ((uint32_t)edc << IMICU_EICTL_EDCVAL_DATA_OFFSET));
                IMICU_EICTL(bmx) |= (IMICU_EICTL_MPID_DATA & ((uint32_t)mpid << IMICU_EICTL_MPID_DATA_OFFSET));
                IMICU_EICTL(bmx) |= (IMICU_EICTL_SPID_DATA & ((uint32_t)spid << IMICU_EICTL_SPID_DATA_OFFSET));
                err = SUCCESS;
            }
        }
    }
    return err;
}

/*!
    \brief      disable imicu error injection disable (API_ID: 0x0004U)
    \param[in]  bmx: IMICU_BMx(x=1,2)
    \param[in]  phase: IMICU phase
               only one parameter can be selected which is shown as below:
      \arg        IMICU_PHASE_CMD :cmd phase, from master to slaver
      \arg        IMICU_PHASE_DATA :data phase, from slaver to master
    \param[out] none
    \retval     none
*/
void imicu_error_injection_enable(uint32_t bmx, imicu_phase_enum phase)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_IMICU_BUS_MATRIX(bmx)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else if(NOT_IMICU_PHASE(phase)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(phase == IMICU_PHASE_CMD) {
            IMICU_EICTL(bmx) |= IMICU_EICTL_EIEN;
        } else {
            IMICU_EICTL(bmx) |= IMICU_EICTL_EIEN_DATA;
        }
    }
}

/*!
    \brief      enable imicu error injection enable (API_ID: 0x0005U)
    \param[in]  bmx: IMICU_BMx(x=1,2)
    \param[in]  phase: IMICU phase
               only one parameter can be selected which is shown as below:
      \arg        IMICU_PHASE_CMD :cmd phase, from master to slaver
      \arg        IMICU_PHASE_DATA :data phase, from slaver to master
    \param[out] none
    \retval     none
*/
void imicu_error_injection_disable(uint32_t bmx, imicu_phase_enum phase)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_IMICU_BUS_MATRIX(bmx)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else if(NOT_IMICU_PHASE(phase)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(phase == IMICU_PHASE_CMD) {
            IMICU_EICTL(bmx) &= ~IMICU_EICTL_EIEN;
        } else {
            IMICU_EICTL(bmx) &= ~IMICU_EICTL_EIEN_DATA;
        }
    }
}

/*!
    \brief      get imicu error flag (API_ID: 0x0006U)
    \param[in]  bmx: IMICU_BMx(x=1,2)
    \param[in]  phase: IMICU phase
               only one parameter can be selected which is shown as below:
      \arg        IMICU_PHASE_CMD :cmd phase, from master to slaver
      \arg        IMICU_PHASE_DATA :data phase, from slaver to master
    \param[out] none
    \retval     FlagStatus:SET or RESET
*/
FlagStatus imicu_error_flag_get(uint32_t bmx, imicu_phase_enum phase)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_IMICU_BUS_MATRIX(bmx)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else if(NOT_IMICU_PHASE(phase)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(phase == IMICU_PHASE_CMD) {
            if(0U != (IMICU_ERRSTAT(bmx) & IMICU_ERRSTAT_EDVF)) {
                reval = SET;
            } else {
                reval = RESET;
            }
        } else {
            if(0U != (IMICU_ERRSTAT(bmx) & IMICU_ERRSTAT_EDVF_DATA)) {
                reval = SET;
            } else {
                reval = RESET;
            }
        }
    }
    return reval;
}

/*!
    \brief      get imicu error status (API_ID: 0x0007U)
    \param[in]  bmx: IMICU_BMx(x=1,2)
    \param[in]  phase: IMICU phase
               only one parameter can be selected which is shown as below:
      \arg        IMICU_PHASE_CMD :cmd phase, from master to slaver
      \arg        IMICU_PHASE_DATA :data phase, from slaver to master
    \param[out] status: error status struct, include mpid, spid, edc and address
                  mpid   : error master port ID
                  spid   : error slave port ID
                  edc    : error EDC code value
    \retval     FlagStatus: the error state (SET or RESET)
*/
FlagStatus imicu_error_status_get(uint32_t bmx, imicu_phase_enum phase, imicu_error_status_struct *status)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_IMICU_BUS_MATRIX(bmx)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else if(NOT_IMICU_PHASE(phase)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else if(NOT_VALID_POINTER(status)) {
        fw_debug_report_err(IMICU_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(phase == IMICU_PHASE_CMD) {
            if(0U != (IMICU_ERRSTAT(bmx) & IMICU_ERRSTAT_EDVF)) {
                status->mpid    = (IMICU_ERRSTAT(bmx) & IMICU_EICTL_MPID) >> IMICU_EICTL_MPID_OFFSET;
                status->spid    = (IMICU_ERRSTAT(bmx) & IMICU_EICTL_SPID) >> IMICU_EICTL_SPID_OFFSET;
                status->edc     = (IMICU_ERRSTAT(bmx) & IMICU_EICTL_EDCVAL) >> IMICU_EICTL_EDCVAL_OFFSET;
                reval = SET;
            } else {
                reval = RESET;
            }
        } else {
            if(0U != (IMICU_ERRSTAT(bmx) & IMICU_ERRSTAT_EDVF_DATA)) {
                status->mpid    = (IMICU_ERRSTAT(bmx) & IMICU_EICTL_MPID_DATA) >> IMICU_EICTL_MPID_DATA_OFFSET;
                status->spid    = (IMICU_ERRSTAT(bmx) & IMICU_EICTL_SPID_DATA) >> IMICU_EICTL_SPID_DATA_OFFSET;
                status->edc     = (IMICU_ERRSTAT(bmx) & IMICU_EICTL_EDCVAL_DATA) >> IMICU_EICTL_EDCVAL_DATA_OFFSET;
                reval = SET;
            } else {
                reval = RESET;
            }
        }
    }
    return reval;
}
