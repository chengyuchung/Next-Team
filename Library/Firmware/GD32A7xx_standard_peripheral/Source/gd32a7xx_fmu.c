/*!
    \file    gd32a7xx_fmu.c
    \brief   FMU driver

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

#include "gd32a7xx_fmu.h"

#define FMU_CFG_INIT_MASK                  ((uint32_t)(0x03FF0FF8U))
#define FMU_CTL_OPR_STAT_MASK              ((uint32_t)(0x000000C0U))
#define FMU_FFIO_CONTROL_STAT_MASK         ((uint32_t)(0x00000030U))
#define FMU_GFP_CONTROL_STAT_MASK          ((uint32_t)(0x00000040U))

#define FMU_WORK_STAT_MASK                 ((uint32_t)(0x00000007U))
#define FMU_FAULTY_STAT_MASK               ((uint32_t)(0x00000008U))
#define FMU_FAKE_FG_MASK                   ((uint32_t)(0x000000FFU))

#define FMU_COMM_LEFT_SHIFT_VAL            ((uint32_t)(0x00000001U))
#define FMU_SOFT_TRIG_FAULT_SNUM           ((uint32_t)(0x00000088U))

/*!
    \brief      initialize the struct parameters of FMU FIO (API_ID(0x0001U))
    \param[in]  none
    \param[out] fmu_fio_struct: init parameter struct, refer to fmu_fio_parameter_struct
    \retval     none
*/
void fmu_fio_para_init(fmu_fio_parameter_struct* fmu_fio_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(fmu_fio_struct)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0001U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure the struct parameters of FMU FIO to the default values */
        fmu_fio_struct->gosen               = FMU_GOS_DISABLE;
        fmu_fio_struct->fosen               = FMU_FOS_DISABLE;
        fmu_fio_struct->foscfg              = FMU_FFIO_CONTRONL_FSM;
        fmu_fio_struct->goscfg              = FMU_GFIO_CONTRONL_FSM;
        fmu_fio_struct->fopre               = FMU_FOPRE_DIV_2;
        fmu_fio_struct->fomcfg              = FMU_FOMCFG_NOTCONSISTENT;
        fmu_fio_struct->gopcfg              = FMU_GOPS_LOW;
        fmu_fio_struct->fopcfg              = FMU_FOPCFG_HIGH1_LOW0;
        fmu_fio_struct->fomset              = FMU_FOMSET_MODE_BI_STABLE;
        fmu_fio_struct->gomset              = FMU_GOMSET_FAULT_OUTPUT_MODE;
    }
}

/*!
    \brief      configure FMU FIO (API_ID(0x0002U))
    \param[in]  fmu_fio_struct: init parameter struct, refer to fmu_parameter_struct, the member values are shown as below:
      \arg        gosen: enable or disable GFIO signal, the value can be FMU_GOS_ENABLE or FMU_GOS_DISABLE
      \arg        fosen: enable or disable FFIO signals, the value can be FMU_FOS_ENABLE or FMU_FOS_DISABLE
      \arg        foscfg: configure FFIO signals, the value can be FMU_FFIO_CONTRONL_FSM, FMU_FFIO_CONTRONL_LOW or FMU_FFIO_CONTRONL_HIGH
      \arg        goscfg: configure GFIO signal, the value can be FMU_GFIO_CONTRONL_FSM, FMU_GFIO_CONTRONL_LOW or FMU_GFIO_CONTRONL_HIGH
      \arg        fopre: configure fatal fault output pin signals time switching clock prescaler, the value can be
                          FMU_FOPRE_DIV_x(x=2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096)
      \arg        fomcfg: configure FFIO signals work mode is consistent with FG fault or not when FMU is in INIT work mode, the value can be
                          FMU_FOMCFG_SAME or FMU_FOMCFG_NOTCONSISTENT
      \arg        gopcfg: configure GFIO signal polarity, the value can be FMU_GOPS_HIGH or FMU_GOPS_LOW
      \arg        fopcfg: configure FFIO signal polarity, the value can be FMU_FOPCFG_HIGH0_LOW1 or FMU_FOPCFG_HIGH1_LOW0
      \arg        fomset: set FFIO signals work mode, the value can be FMU_FOMSET_MODE_BI_STABLE, FMU_FOMSET_MODE_TIME_SWITCHING or FMU_FOMSET_MODE_TESTx(x=0, 1, 2)
      \arg        gomset: set GFIO signal work mode, the value can be FMU_GOMSET_FAULT_OUTPUT_MODE, FMU_GOMSET_MODE_TEST0 or FMU_GOMSET_MODE_TEST1
    \param[out] none
    \retval     none
*/
void fmu_fio_config(fmu_fio_parameter_struct* fmu_fio_struct)
{
    uint32_t reg = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(fmu_fio_struct)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg &= FMU_CFG_INIT_MASK;

        reg |= fmu_fio_struct->gosen;
        reg |= fmu_fio_struct->fosen;
        reg |= fmu_fio_struct->foscfg;
        reg |= fmu_fio_struct->goscfg;
        reg |= fmu_fio_struct->fopre;
        reg |= fmu_fio_struct->fomcfg;
        reg |= fmu_fio_struct->gopcfg;
        reg |= fmu_fio_struct->fopcfg;
        reg |= fmu_fio_struct->fomset;
        reg |= fmu_fio_struct->gomset;

        FMU_CFG = (uint32_t)(reg);
    }
}

/*!
    \brief      initialize the parameters of FMU structure with the default values (API_ID(0x0003U))
    \param[in]  none
    \param[out] fmu_struct: the initialized structure fmu_parameter_struct pointer
    \retval     none
*/
void fmu_para_init(fmu_parameter_struct* fmu_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(fmu_struct)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        fmu_struct->recovery_type                = FMU_SW_RECOVERY;
        fmu_struct->sub_rst                      = DISABLE;
        fmu_struct->fault_group_en               = DISABLE;
        fmu_struct->caution_timeout_en           = DISABLE;
        fmu_struct->caution_timeout_value        = FMU_CAUTION_TIMEOUT_INIT_VALUE;
        fmu_struct->init_timeout_value           = FMU_INIT_TIMEOUT_INIT_VALUE;
        fmu_struct->faultout_timer_value         = FMU_FAULTOUT_TIME_INIT_VALUE;
        fmu_struct->caution_int_en               = DISABLE;
        fmu_struct->nmi_en                       = DISABLE;
        fmu_struct->ffio_output_en               = DISABLE;
        fmu_struct->gfio_output_en               = DISABLE;
        fmu_struct->gpo_en                       = DISABLE;
    }
}

/*!
    \brief      configure FMU parameter (API_ID(0x0004U))
    \param[in]  fmu_struct: initialization stuct, refer to fmu_parameter_struct, the member values are shown as below:
      \arg        recovery_type: fault recovery type, the value can be FMU_HW_RECOVERY or FMU_SW_RECOVERY
      \arg        sub_rst: configure fault group subsystem reset, the value can be ENABLE or DISABLE
      \arg        fault_group_en: configure fault group, the value can be ENABLE or DISABLE
      \arg        caution_timeout_en: configure fault group CAUTION  work mode timeout, the value can be ENABLE or DISABLE
      \arg        caution_timeout_value:fault group CAUTION  work mode timeout value, the value can be 0 ~ 0XFFFFFFFFU
      \arg        init_timeout_value: INIT work mode timeout value, the value can be 0 ~ 0X7U
      \arg        faultout_timer_value: fault output (FFIO) timer value, the value can be 0 ~ 0X1FFFU
      \arg        caution_int_en: configure CAUTION work mode interrupt request, the value can be ENABLE or DISABLE
      \arg        nmi_en: configure NMI request, the value can be ENABLE or DISABLE
      \arg        ffp_output_en: configure FFIO signals, the value can be ENABLE or DISABLE
      \arg        gfp_output_en: configure GFIO signal, the value can be ENABLE or DISABLE
      \arg        gpo_en: configure FAULT work mode holding timer output (GPO), the value can be ENABLE or DISABLE
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x (x=0 ~ 11)
    \param[out] none
    \retval     none
*/
void fmu_config(fmu_parameter_struct* fmu_struct, uint16_t fault_group_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_VALID_POINTER(fmu_struct)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0004U), ERR_PARAM_POINTER);
    } else if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* configure FMU fault group recovery type */
        fmu_fg_recovery_type_config(fmu_struct->recovery_type, fault_group_id);
        
        /* configure FMU fault group subsystem reset reaction */
        fmu_fault_reaction_config(FMU_FRETN_SUBRST2RCU, fault_group_id, fmu_struct->sub_rst);

        /* configure FMU fault group subsystem reset reaction */
        fmu_fault_reaction_config(FMU_FRETN_CAUINT2CPU, fault_group_id, fmu_struct->caution_int_en);

        /* configure FMU fault group NMI reaction */
        fmu_fault_reaction_config(FMU_FRETN_NMI2CPU, fault_group_id, fmu_struct->nmi_en);

        /* configure FMU fault group FFIO output reaction */
        fmu_fault_reaction_config(FMU_FRETN_FFIO, fault_group_id, fmu_struct->ffio_output_en);

        /* configure FMU fault group GFIO output reaction */
        fmu_fault_reaction_config(FMU_FRETN_GFIO, fault_group_id, fmu_struct->gfio_output_en);

        /* configure FMU fault group GFIO output reaction */
        fmu_fault_reaction_config(FMU_FRETN_GPO, fault_group_id, fmu_struct->gpo_en);

        /* configure FMU timers value */
        fmu_timer_config(FMU_INIT_TIMEROUT, fmu_struct->init_timeout_value);
        fmu_timer_config(FMU_CAUTION_TIMEROUT, fmu_struct->caution_timeout_value);
        fmu_timer_config(FMU_FAULT_OUTPUT_TIMER, fmu_struct->faultout_timer_value);

        /* configure FMU FG CAUTION timerout enable or disable */
        if(ENABLE == fmu_struct->caution_timeout_en) {
            fmu_caution_timeout_enable(fault_group_id);
        } else {
            fmu_caution_timeout_disable(fault_group_id);
        }

        /* gpo_en FMU FG enable or disable */
        if(ENABLE == fmu_struct->fault_group_en) {
            fmu_fg_enable(fault_group_id);
        } else {
            fmu_fg_disable(fault_group_id);
        }
    }
}

/*!
    \brief      execute FMU operation (API_ID(0x0005U))
    \param[in]  operation_type: execute operation type, refer to fmu_operation_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_TRAN_INIT_WORK_MODE: FMU execute operation that transform to INIT work mode 
      \arg        FMU_TRAN_NORMAL_WORK_MODE: FMU execute operation that transform to CAUTION work mode
      \arg        FMU_CLR_HOLDING_STATUS_REGS: FMU execute operation that clear the hold status register
      \arg        FMU_CLR_OPERATION: FMU execute operation that clear operation status
      \arg        FMU_NO_EXE_OPERATION: FMU no execute operation
    \param[out] none
    \retval     none
*/
void fmu_operation_execute(fmu_operation_enum operation_type)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_OPTYPE(operation_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMU_CTL;
        reg &= ~FMU_CTL_EOP;

        switch(operation_type){
        /* FMU unlock operation1 and excute operation will which transform FMU to INIT work mode */
        case FMU_TRAN_INIT_WORK_MODE:
            reg |= FMU_TO_INIT_WORK_MODE;
            FMU_CTLKEY = FMU_EOP1_KEY_U32;
            FMU_CTL = reg;
            break;
        /* FMU unlock operation2 and excute operation will which transform FMU to NORMAL work mode */
        case FMU_TRAN_NORMAL_WORK_MODE:
            reg |= FMU_TO_NORMAL_WORK_MODE;
            FMU_CTLKEY = FMU_EOP2_KEY_U32;
            FMU_CTL = reg;
            break;
        /* FMU excute operation which will clear the hold status registers */
        case FMU_CLR_HOLDING_STATUS_REGS:
            reg |= FMU_CLR_HOLD_STATUS_REGS;
            FMU_CTL = reg;
            break;
        /* FMU excute operation which will set opeartion status is idle */
        case FMU_CLR_OPERATION:
            reg |= FMU_CLR_OPERATION_STATUS;
            FMU_CTL = reg;
            break;
        /* FMU default no excute operation */
        case FMU_NO_EXE_OPERATION:
            reg |= FMU_NO_OPERATION;
            FMU_CTL = reg;
            break;
        default :
            break;
        }
    }
}

/*!
    \brief      FMU read current operation status (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     fmu_operation_status_enum: FMU_OPS_IDLE, FMU_OPS_ONGOING, FMU_OPS_NOTSUCCESS, FMU_OPS_SUCCESS
*/
fmu_operation_status_enum fmu_operation_status_read(void)
{
    uint32_t reg;
    fmu_operation_status_enum result = FMU_OPS_IDLE;
    reg = FMU_CTL;
    reg &= FMU_CTL_OPR_STAT_MASK;

    switch(reg){
    /* FMU current operation status is idle */
    case FMU_OPSTAT_IDLE:
        result = FMU_OPS_IDLE;
        break;
    /* FMU current operation status is on going */
    case FMU_OPSTAT_ONGOING:
        result = FMU_OPS_ONGOING;
        break;
    /* FMU current operation status is not success */
    case FMU_OPSTAT_NOTSUCCESS:
        result = FMU_OPS_NOTSUCCESS;
        break;
    /* FMU current operation status is success */
    case FMU_OPSTAT_SUCCESS:
        result = FMU_OPS_SUCCESS;
        break;
    /* FMU default operation status is idle */
    default:
        break;
    }

    return result;
}

/*!
    \brief      unlock FMU (API_ID(0x0007U))
    \param[in]  lock_type: FMU lock type, refer to fmu_lock_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_LOCK_EOP1: EOP1 lock
      \arg        FMU_LOCK_EOP2: EOP2 lock 
      \arg        FMU_LOCK_FG_STAT: FG status lock
      \arg        FMU_LOCK_TRANS_TEMP: INIT work mode transition temporary lock
    \param[out] none
    \retval     none
*/
void fmu_unlock(fmu_lock_type_enum lock_type)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_LKTYPE(lock_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch (lock_type) {
        /* unlock EOP1 */
        case FMU_LOCK_EOP1:
            FMU_CTLKEY = (uint32_t)FMU_EOP1_KEY_U32;
            break;

        /* unlock EOP2 */
        case FMU_LOCK_EOP2:
            FMU_CTLKEY = (uint32_t)FMU_EOP2_KEY_U32;
            break;

        /* unlock FG status */
        case FMU_LOCK_FG_STAT:
            FMU_FGKEY = (uint32_t)FMU_FG_KEY_UNLOCK_U32;
            break;

        /* unlock INIT work mode transition temporary */
        case FMU_LOCK_TRANS_TEMP:
            FMU_TCLOCK = (uint32_t)FMU_TEMP_UNLOCK_KEY_U32; 
            break;

        default:
            break;
        }
    }
}

/*!
    \brief      lock FMU (API_ID(0x0008U))
    \param[in]  lock_type: FMU lock type, refer to fmu_lock_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_LOCK_TRANS_TEMP: INIT work mode transition temporary lock
      \arg        FMU_LOCK_TRANS_PERM: INIT work mode transition permanent lock
    \param[out] none
    \retval     none
*/
void fmu_lock(fmu_lock_type_enum lock_type)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_LKTYPE_LK(lock_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch (lock_type) {
        /* lock INIT work mode transition temporary */
        case FMU_LOCK_TRANS_TEMP:
            FMU_TCLOCK = FMU_TEMP_LOCK_KEY_U32;
            break;

        /* lock INIT work mode transition permanent */
        case FMU_LOCK_TRANS_PERM:
            FMU_PCLOCK = FMU_PERM_LOCK_KEY_U32;
            break;

        default:
            break;
        }
    }
}

/*!
    \brief      configure FMU recovery type (API_ID(0x0009U))
    \param[in]  recovery_type: FMU fault recovery type
                only one parameter can be selected which is shown as below:
      \arg        FMU_HW_RECOVERY: hardware recoverable
      \arg        FMU_SW_RECOVERY: software recoverable
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x (x=0 ~ 11)
    \param[out] none
    \retval     none
*/
void fmu_fg_recovery_type_config(uint16_t recovery_type, uint16_t fault_group_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_RECOVERY_TYPE(recovery_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    }  else if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if (FMU_SW_RECOVERY == recovery_type) {
            FMU_FGCFG |= (uint32_t)(FMU_COMM_LEFT_SHIFT_VAL << fault_group_id);
        } else {
            FMU_FGCFG &= ~((uint32_t)(FMU_COMM_LEFT_SHIFT_VAL << fault_group_id));
        }
    }
}

/*!
    \brief      configure FMU fault reaction (API_ID(0x000AU))
    \param[in]  reaction_type: FMU fault reaction type, refer to fmu_fretn_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_FRETN_CAUINT2CPU: CAUTION work mode interrupt request
      \arg        FMU_FRETN_SUBRST2RCU: FG subsystem reset reaction 
      \arg        FMU_FRETN_NMI2CPU: FG FAULT work mode NMI interrupt request
      \arg        FMU_FRETN_FFIO: FG FFIO pin output
      \arg        FMU_FRETN_GFIO: FG GFIO pin output
      \arg        FMU_FRETN_GPO: FAULT work status holding timer output
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x(x=0 ~ 11)
    \param[in]  new_value: ENABLE or DISABLE
                only one parameter can be selected which is shown as below:
      \arg        ENABLE: enable reaction
      \arg        DISABLE: disable reaction
    \param[out] none
    \retval     none
*/
void fmu_fault_reaction_config(fmu_fretn_type_enum reaction_type, uint16_t fault_group_id, ControlStatus new_value)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_REACTION_TYPE(reaction_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else if(NOT_FMU_CONTROL_STATUS(new_value)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000AU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch (reaction_type) {
        /* configure subsystem reset */
        case FMU_FRETN_CAUINT2CPU:
            if (ENABLE == new_value) {
                FMU_CMINTREN |= (uint32_t)(FMU_CMI_ENABLE << fault_group_id);
            } else {
                FMU_CMINTREN &= ~((uint32_t)(FMU_CMI_ENABLE << fault_group_id));
            }
            break;

        /* configure subsystem reset */
        case FMU_FRETN_SUBRST2RCU:
            if (ENABLE == new_value) {
                FMU_FGSUBSRCFG |= (uint32_t)(FMU_SUB_RST_ENABLE << ((uint32_t)fault_group_id*2U));
            } else {
                FMU_FGSUBSRCFG &= ~((uint32_t)(FMU_SUB_RST_DISABLE << ((uint32_t)fault_group_id*2U)));
            }
            break;

        /* configure NMI to cpu */
        case FMU_FRETN_NMI2CPU:
            if (ENABLE == new_value) {
                FMU_FMNMIINTREN |= (uint32_t)(FMU_NMI_ENABLE << fault_group_id);
            } else {
                FMU_FMNMIINTREN &= ~((uint32_t)(FMU_NMI_ENABLE << fault_group_id));
            }
            break;

        /* configure FFIO */
        case FMU_FRETN_FFIO:
            if (ENABLE == new_value) {
                FMU_FPOEN |= (uint32_t)(FMU_PINOUT_ENABLE << fault_group_id);
            } else {
                FMU_FPOEN &= ~((uint32_t)(FMU_PINOUT_ENABLE << fault_group_id));
            }
            break;
        
        /* configure GFIO */
        case FMU_FRETN_GFIO:
            if (ENABLE == new_value) {
                FMU_GPOEN |= (uint32_t)(FMU_PINOUT_ENABLE << fault_group_id);
            } else {
                FMU_GPOEN &= ~((uint32_t)(FMU_PINOUT_ENABLE << fault_group_id));
            }
            break;
        
        /* configure GPO */
        case FMU_FRETN_GPO:
            if (ENABLE == new_value) {
                FMU_FHTOEN |= (uint32_t)(FMU_HOLD_TIMER_ENABLE << fault_group_id);
            } else {
                FMU_FHTOEN &= ~((uint32_t)(FMU_HOLD_TIMER_ENABLE << fault_group_id));
            }
            break;
        
        default:
            break;
        }
    }
}

/*!
    \brief      configure FMU timer (API_ID(0x000BU))
    \param[in]  tim_type: FMU timer type, refer to fmu_tim_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_CAUTION_TIMEROUT: FG CAUTION work mode timerout value
      \arg        FMU_INIT_TIMEROUT: FG INIT work mode timerout value
      \arg        FMU_FAULT_OUTPUT_TIMER: FG FAULT work mode timer
    \param[in]  tim_value: the vaule write to timer
    \param[out] none
    \retval     none
*/
void fmu_timer_config(fmu_tim_type_enum tim_type, uint32_t tim_value)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_TIMTYPE(tim_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch (tim_type){
        case FMU_CAUTION_TIMEROUT:
            FMU_FGCMTVAL = tim_value;
            break;
        case FMU_INIT_TIMEROUT:
#ifdef FW_DEBUG_ERR_REPORT
            /* check parameter */
            if(NOT_FMU_TIMER_IMT_LENGTH(tim_value)) {
                fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000BU), ERR_PARAM_OUT_OF_RANGE);
            } else
#endif /* FW_DEBUG_ERR_REPORT */
            {
                FMU_IMTVAL = tim_value;
            }
            break;
        case FMU_FAULT_OUTPUT_TIMER:
#ifdef FW_DEBUG_ERR_REPORT
            /* check parameter */
            if(NOT_FMU_TIMER_FOT_LENGTH(tim_value)) {
                fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000BU), ERR_PARAM_OUT_OF_RANGE);
            } else
#endif /* FW_DEBUG_ERR_REPORT */
            {
                FMU_FOT = tim_value;
            }
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      configure FMU FIO (API_ID(0x000CU))
    \param[in]  fault_pin: FMU fault pin
                only one parameter can be selected which is shown as below:
      \arg        FMU_FFPO_0: FFIO output pin 0
      \arg        FMU_FFPO_1: FFIO output pin 1
      \arg        FMU_GFPO: GFIO output pin
    \param[in]  output_value: SET or RESET
                only one parameter can be selected which is shown as below:
      \arg        RESET: the output value is low level
      \arg        SET: the output value is high level
    \param[out] none
    \retval     none
*/
void fmu_fio_output_config(uint32_t fault_pin, fio_status output_value)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FO(fault_pin)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else if(NOT_FIO_STATUS(output_value)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(RESET != output_value) {
            FMU_FPCTL |= (uint32_t)fault_pin;
        } else {
            FMU_FPCTL &= (uint32_t)(~fault_pin);
        }
    }
}

/*!
    \brief      get FMU fault IO signal input status (API_ID(0x000DU))
    \param[in]  fault_pin: FMU fault pin
                only one parameter can be selected which is shown as below:
      \arg        FMU_FFPI_0: FFIO input pin 0
      \arg        FMU_FFPI_1: FFIO input pin 1
      \arg        FMU_GFPI: GFIO input pin
    \param[out] none
    \retval     fio_status: FMU fault pin input status (SET or RESET)
*/
fio_status fmu_fio_input_get(uint32_t fault_pin)
{
    uint32_t reg;
    fio_status reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FI(fault_pin)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMU_FPCTL;

        switch(fault_pin){
        /* FMU FFpin0 and FFpin input status are low */
        case FMU_FFPI_0:
            reg &= FMU_FFPI_0;
            break;
        /* FMU FFpin0 input status is low and FFpin input status is high */
        case FMU_FFPI_1:
            reg &= FMU_FFPI_1;
            break;
        /* FMU FFpin0 input status is high and FFpin input status is low */
        case FMU_GFPI:
            reg &= FMU_GFPI;
            break;
        /* FMU FFpin0 and FFpin default input statuss are low */
        default:
            break;
        }

        /*get fault pin input status */
        if(0U != reg) {
            reval =  SET;
        } else {
            reval =  RESET;
        }
    }

    return reval;
}

/*!
    \brief      read FMU FFIO signal control status (API_ID(0x000EU))
    \param[in]  none 
    \param[out] none
    \retval     fmu_ffio_status_enum: FMU control status
*/
fmu_ffio_status_enum fmu_ffio_status_read(void)
{
    uint32_t reg;
    fmu_ffio_status_enum reval = FFIO_STATUS_LOW0_LOW1;
    reg = FMU_STAT;
    reg &= FMU_FFIO_CONTROL_STAT_MASK;

    switch(reg) {
    /* FMU FFpin0 and FFpin input status are low */
    case FMU_FFIO_LOW0_LOW1:
        reval = FFIO_STATUS_LOW0_LOW1;
        break;
    /* FMU FFpin0 input status is low and FFpin input status is high */
    case FMU_FFIO_LOW0_HIGH1:
        reval = FFIO_STATUS_LOW0_HIGH1;
        break;
    /* FMU FFpin0 input status is high and FFpin input status is low */
    case FMU_FFIO_HIGH0_LOW1:
        reval = FFIO_STATUS_HIGH0_LOW1;
        break;
    /* FMU FFpin0 and FFpin input statuss are high */
    case FMU_FFIO_HIGH0_HIGH1:
        reval = FFIO_STATUS_HIGH0_HIGH1;
        break;
    /* FMU FFpin0 and FFpin default input statuss are low */
    default:
        break;
    }

    return reval;
}

/*!
    \brief      read FMU GFpin signal control status (API_ID(0x000FU))
    \param[in]  none 
    \param[out] none
    \retval     fio_status: SET or RESET
*/
fio_status fmu_gfio_status_read(void)
{
    uint32_t reg;
    fio_status reval = RESET;
    reg = FMU_STAT;
    reg &= FMU_GFP_CONTROL_STAT_MASK;

    if(0U != reg) {
        /* FMU GFpin current input status is high */
        reval = SET;
    } else {
    }

    return reval;
}

/*!
    \brief      get FMU status (API_ID(0x0010U))
    \param[in]  none 
    \param[out] none
    \retval     fmu_faulty_status_enum: FMU_NO_FAULTY or FMU_IN_FAULTY
*/
fmu_faulty_status_enum fmu_status_get(void)
{
    uint32_t reg;
    fmu_faulty_status_enum reval = FMU_NO_FAULTY;

    reg = FMU_STAT;
    reg &= FMU_FAULTY_STAT_MASK;

    if(0U != reg) {
        /* FMU status is faulty */
        reval = FMU_IN_FAULTY;
    } else {
        /* FMU status is no faulty */
    }

    return reval;
}

/*!
    \brief      read FMU current work mode (API_ID(0x0011U))
    \param[in]  none 
    \param[out] none
    \retval     fmu_status_enum: FMU_STATUS_NORMAL, FMU_STATUS_INIT, FMU_STATUS_CAUTION, FMU_STATUS_FAULT
*/
fmu_status_enum fmu_workmode_read(void)
{
    uint32_t reg;
    fmu_status_enum reval = FMU_STATUS_NORMAL;
    reg = FMU_STAT;
    reg &= FMU_WORK_STAT_MASK;
    
    switch(reg){
    /* FMU current status is NORMAL status */
    case FMU_NORMAL_STATUS:
        reval = FMU_STATUS_NORMAL;
        break;
    /* FMU current status is INIT status */
    case FMU_INIT_STATUS:
        reval = FMU_STATUS_INIT;
        break;
    /* FMU current status is CAUTION status */
    case FMU_CAUTION_STATUS:
        reval = FMU_STATUS_CAUTION;
        break;
    /* FMU current status is FAULT status */
    case FMU_FAULT_STATUS:
        reval = FMU_STATUS_FAULT;
        break;
    /* FMU default status is NORMAL status */
    default:
        break;
    }

    return reval;
}

/*!
    \brief      injection FMU fake FG fault (API_ID(0x0012U))
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x(x=0 ~ 11)
    \param[out] none
    \retval     none
*/
void fmu_ff_injection(uint32_t fault_group_id)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMU_FFGNCFG;
        reg &= ~FMU_FAKE_FG_MASK;
        reg |= (uint32_t)fault_group_id;
        FMU_FFGNCFG = reg;
    }
}

/*!
    \brief      read FMU transition FG (API_ID(0x0013U))
    \param[in]  trans_type: FMU work mode transition type, refer to fmu_trans_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_TRANS_N2C: FMU work mode transition type is NORMAL to CAUTION
      \arg        FMU_TRANS_C2F: FMU work mode transition type is CAUTION to FAULT
      \arg        FMU_TRANS_N2F: FMU work mode transition type is NORMAL to FAULT
      \arg        FMU_TRANS_F2C: FMU work mode transition type is FAULT to CAUTION
    \param[out] none
    \retval     uint32_t: FMU transition FG (0 ~ 0X7FF)
*/
uint32_t fmu_trans_fg_read(fmu_trans_type_enum trans_type)
{
    uint32_t trans_fg = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_TRANS_TYPE(trans_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch (trans_type) {
        /* lock INIT work mode transition temporary */
        case FMU_TRANS_N2C:
            trans_fg = ((uint32_t)FMU_NTCHSTAT);
            break;

        /* lock INIT work mode transition permanent */
        case FMU_TRANS_C2F:
            trans_fg = ((uint32_t)FMU_CTFHSTAT);
            break;
        
        /* lock INIT work mode transition temporary */
        case FMU_TRANS_N2F:
            trans_fg = ((uint32_t)FMU_NTFHSTAT);
            break;

        /* lock INIT work mode transition permanent */
        case FMU_TRANS_F2C:
            trans_fg = ((uint32_t)FMU_FTCHSTAT);
            break;

        default:
            break;
        }
    }

    return trans_fg;
}

/*!
    \brief      read FMU counter (API_ID(0x0014U))
    \param[in]  cnt_type: FMU counter type, refer to fmu_cnt_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_CAUTION_WORK_MODE_CNT: FG CAUTION work mode counter
      \arg        FMU_INIT_WORK_MODE_CNT: FG INIT work mode counter
      \arg        FMU_FF_OUTPUT_CNT: fatal fault output counter
      \arg        FMU_GF_OUTPUT_CNT: general fault output counter
    \param[out] none
    \retval     uint32_t: value of counter (0 ~ 0XFFFFFFFF)
*/
uint32_t fmu_counter_read(fmu_cnt_type_enum cnt_type)
{
    uint32_t cnt = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_CNT_TYPE(cnt_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0014U), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch (cnt_type){
        case FMU_CAUTION_WORK_MODE_CNT:
            cnt = (uint32_t)FMU_CMCNT;
            break;
        case FMU_INIT_WORK_MODE_CNT:
            cnt = (uint32_t)FMU_IMCNT;
            break;
        case FMU_FF_OUTPUT_CNT:
            cnt = (uint32_t)FMU_FOCNT;
            break;
        case FMU_GF_OUTPUT_CNT:
            cnt = (uint32_t)FMU_GOCNT;
            break;
        default:
            break;
        }
    }

    return cnt;
}

/*!
    \brief      configure FMU TMR error output (API_ID(0x0015U))
    \param[in]  tmr_error_type: FMU TMR error type, refer to fmu_tmr_error_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_TME0_DBGEN: enable TMR error output 0
      \arg        FMU_TME1_FOS_GOS_ENCFG: enable TMR error output 1
      \arg        FMU_TME2_FG_ENCFG: enable TMR error output 2
    \param[in]  new_value: ENABLE or DISABLE
                only one parameter can be selected which is shown as below:
      \arg        ENABLE: enable TMR error output
      \arg        DISABLE: disable TMR error output
    \param[out] none
    \retval     none
*/
void fmu_tmr_error_output_config(fmu_tmr_error_type_enum tmr_error_type, ControlStatus new_value)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_TMR_ERR_TYPE(tmr_error_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else if(NOT_FMU_CONTROL_STATUS(new_value)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0015U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch (tmr_error_type) {
        /* configure TMR error output 0 */
        case FMU_TME0_DBGEN:
            if (ENABLE == new_value) {
                FMU_TMRES |= FMU_TMRES_TMREN0;
            } else {
                FMU_TMRES &= ~(FMU_TMRES_TMREN0);
            }
            break;

        /* configure TMR error output 1 */
        case FMU_TME1_FOS_GOS_ENCFG:
            if (ENABLE == new_value) {
                FMU_TMRES |= FMU_TMRES_TMREN1;
            } else {
                FMU_TMRES &= ~(FMU_TMRES_TMREN1);
            }
            break;

        /* configure TMR error output 2 */
        case FMU_TME2_FG_ENCFG:
            if (ENABLE == new_value) {
                FMU_TMRES |= FMU_TMRES_TMREN2;
            } else {
                FMU_TMRES &= ~(FMU_TMRES_TMREN2);
            }
            break;

        default:
            break;
        }
    }
}

/*!
    \brief      get FMU fault flag (API_ID(0x0016U))
    \param[out] none
    \retval     uint32_t: FMU fault flag, 0 ~ 0X7FF
*/
uint32_t fmu_fault_flag_get(void)
{
    uint32_t reg;
    reg = FMU_FGSTAT;

    return reg;
}

/*!
    \brief      clear FMU FG status (if SW recoverable) (API_ID(0x0017U))
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x(x=0 ~ 11)
    \param[out] none
    \retval     none
*/
void fmu_fg_status_clear(uint16_t fault_group_id)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0017U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMU_FGSTAT;

        FMU_FGKEY = (uint32_t)FMU_FG_KEY_UNLOCK_U32;
        reg |= (uint32_t)(FMU_COMM_LEFT_SHIFT_VAL << fault_group_id);
        FMU_FGSTAT = reg;
    }
}

/*!
    \brief      get FMU group fault status (API_ID(0x0018U))
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x(x=0 ~ 11)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus fmu_fg_status_get(uint16_t fault_group_id)
{
    uint32_t reg;
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0018U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = (uint32_t)(FMU_COMM_LEFT_SHIFT_VAL << fault_group_id);
        reg &= FMU_FGSTAT;

        if(0U != reg) {
            /* FMU group status is faulty */
            reval =  SET;
        } else {
            /* FMU group status is no faulty */
            reval =  RESET;
        }
    }

    return reval;
}

/*!
    \brief      get FMU FG trigger source status (API_ID(0x0019U))
    \param[in]  trigger_source_num: FMU FG trigger source number(0 ~ 0X9F)
    \param[out] none
    \retval     FlagStatus: trigger source status (SET or RESET)
*/
FlagStatus fmu_fg_trigger_source_status_get(uint8_t trigger_source_num)
{
    FlagStatus reval = RESET;
    uint32_t reg, temp_val;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FAKE_FG_VALUE(trigger_source_num)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0019U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMU_FGTSSTAT((uint32_t)trigger_source_num / 32U);
        temp_val = BIT(trigger_source_num % 32U);
        if(0U != (reg & temp_val)) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }

    return reval;
}

/*!
    \brief      clear FMU FG trigger source status (API_ID(0x001AU))
    \param[in]  trigger_source_num: FMU FG trigger source number(0 ~ 0X9F)
    \param[out] none
    \retval     none
*/
void fmu_fg_trigger_source_status_clear(uint8_t trigger_source_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FAKE_FG_VALUE(trigger_source_num)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x001AU), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FGTSSTAT((uint32_t)trigger_source_num / 32U) |= BIT(trigger_source_num % 32U);
    }
}

/*!
    \brief      get FMU TMR error output status (API_ID(0x001BU))
    \param[in]  tmr_error_type: FMU TMR error type, refer to fmu_tmr_error_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_TME0_DBGEN: enable TMR error output 0
      \arg        FMU_TME1_FOS_GOS_ENCFG: enable TMR error output 1
      \arg        FMU_TME2_FG_ENCFG: enable TMR error output 2
    \param[out] none
    \retval     FlagStatus: FMU TMR error output status (SET or RESET)
*/
FlagStatus fmu_tmr_error_status_get(fmu_tmr_error_type_enum tmr_error_type)
{
    uint32_t reg;
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_TMR_ERR_TYPE(tmr_error_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x001BU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMU_TMRES;

        switch(tmr_error_type){
        /* get TMR error output status 0 */
        case FMU_TME0_DBGEN:
            reg &= FMU_TMRES_TMRS0;
            break;
        /* get TMR error output status 1 */
        case FMU_TME1_FOS_GOS_ENCFG:
            reg &= FMU_TMRES_TMRS1;
            break;
        /* get TMR error output status 2 */
        case FMU_TME2_FG_ENCFG:
            reg &= FMU_TMRES_TMRS2;
            break;

        default:
            break;
        }

        /* get fault pin input status */
        if(0U != reg) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }

    return reval;
}

/*!
    \brief      clear FMU TMR error output status (API_ID(0x001CU))
    \param[in]  tmr_error_type: FMU TMR error type, refer to fmu_tmr_error_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_TME0_DBGEN: enable TMR error output 0
      \arg        FMU_TME1_FOS_GOS_ENCFG: enable TMR error output 1
      \arg        FMU_TME2_FG_ENCFG: enable TMR error output 2
    \param[out] none
    \retval     none
*/
void fmu_tmr_error_status_clear(fmu_tmr_error_type_enum tmr_error_type)
{
    uint32_t reg;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_TMR_ERR_TYPE(tmr_error_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x001CU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMU_TMRES;

        switch(tmr_error_type){
        /* clear TMR error output status 0 */
        case FMU_TME0_DBGEN:
            reg |= FMU_TMRES_TMRS0;
            break;
        /* clear TMR error output status 1 */
        case FMU_TME1_FOS_GOS_ENCFG:
            reg |= FMU_TMRES_TMRS1;
            break;
        /* clear TMR error output status 2 */
        case FMU_TME2_FG_ENCFG:
            reg |= FMU_TMRES_TMRS2;
            break;

        default:
            break;
        }

        FMU_TMRES = reg;
    }
}

/*!
    \brief      enable FMU debug mode (API_ID(0x001DU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmu_dbg_enable(void)
{
    FMU_CTL |= (uint32_t)FMU_CTL_DBGEN;
}

/*!
    \brief      disable FMU debug mode (API_ID(0x001EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmu_dbg_disable(void)
{
    FMU_CTL &= (uint32_t)(~FMU_CTL_DBGEN);
}

/*!
    \brief      enabled FMU FG (API_ID(0x001FU))
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x(x=0 ~ 11)
    \param[out] none
    \retval     none
*/
void fmu_fg_enable(uint16_t fault_group_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x001FU), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FGEN |= (uint32_t)(FMU_COMM_LEFT_SHIFT_VAL << fault_group_id);
    }
}

/*!
    \brief      disabled FMU FG (API_ID(0x0020U))
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x(x=0 ~ 11)
    \param[out] none
    \retval     none
*/
void fmu_fg_disable(uint16_t fault_group_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0020U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FGEN &= ~(uint32_t)(FMU_COMM_LEFT_SHIFT_VAL << fault_group_id);
    }
}

/*!
    \brief      enable FMU CAUTION timeout (API_ID(0x0021U))
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x(x=0 ~ 11)
    \param[out] none
    \retval     none
*/
void fmu_caution_timeout_enable(uint16_t fault_group_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0021U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FGCMTEN |= (uint32_t)(FMU_COMM_LEFT_SHIFT_VAL << fault_group_id);
    }
}

/*!
    \brief      disable FMU CAUTION timeout (API_ID(0x0022U))
    \param[in]  fault_group_id: fault group id
                only one parameter can be selected which is shown as below:
      \arg        FAULT_GROUP_ID_x: FAULT_GROUP_ID_x (x=0 ~ 11)
    \param[out] none
    \retval     none
*/
void fmu_caution_timeout_disable(uint16_t fault_group_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FG(fault_group_id)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0022U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FGCMTEN &= ~(uint32_t)(FMU_COMM_LEFT_SHIFT_VAL << fault_group_id);
    }
}

/*!
    \brief      enable injection FMU fake FG (API_ID(0x0023U))
    \param[in]  none 
    \param[out] none
    \retval     none
*/
void fmu_ff_inject_enable(void)
{
    uint32_t reg;

    reg = FMU_FFGNCFG;
    reg &= ~FMU_FFGNCFG_FFGEN;
    reg |= (uint32_t)FMU_FAKE_FG_ENABLE;

    FMU_FFGNCFG = reg;
}

/*!
    \brief      disable injection FMU fake FG (API_ID(0x0024U))
    \param[in]  none 
    \param[out] none
    \retval     none
*/
void fmu_ff_inject_disable(void)
{
    uint32_t reg;
    
    reg = FMU_FFGNCFG;
    reg &= ~FMU_FFGNCFG_FFGEN;
    reg |= (uint32_t)FMU_FAKE_FG_DISABLE;

    FMU_FFGNCFG = reg;
}

/*!
    \brief      enable FMU FG trigger source (API_ID(0x0025U))
    \param[in]  trigger_source_num: FMU FG trigger source number(0 ~ 0X9F)
    \param[out] none
    \retval     none
*/
void fmu_fg_trigger_source_enable(uint8_t trigger_source_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FAKE_FG_VALUE(trigger_source_num)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0025U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FGTSEN((uint32_t)trigger_source_num / 32U) |= BIT(trigger_source_num % 32U);
    }
}

/*!
    \brief      disable FMU FG trigger source (API_ID(0x0026U))
    \param[in]  trigger_source_num: FMU FG trigger source number(0 ~ 0X9F)
    \param[out] none
    \retval     none
*/
void fmu_fg_trigger_source_disable(uint8_t trigger_source_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_FAKE_FG_VALUE(trigger_source_num)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0026U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FGTSEN((uint32_t)trigger_source_num / 32U) &= ~(BIT(trigger_source_num % 32U));
    }
}

/*!
    \brief      enable FMU software triggered fault (API_ID(0x0027U))
    \param[in]  soft_trig_fault_num: FMU software triggered fault number(0X88 ~ 0X9F)
    \param[out] none
    \retval     none
*/
void fmu_fg_soft_trig_fault_enable(uint8_t soft_trig_fault_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_SOFT_TRI_VALUE(soft_trig_fault_num)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0027U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FG_SWTEN((soft_trig_fault_num-FMU_SOFT_TRIG_FAULT_SNUM)/8U) |= BIT(((soft_trig_fault_num-FMU_SOFT_TRIG_FAULT_SNUM) % 8U)*2U);
    }
}

/*!
    \brief      disable FMU software triggered fault (API_ID(0x0028U))
    \param[in]  soft_trig_fault_num: FMU software triggered fault number(0X88 ~ 0X9F)
    \param[out] none
    \retval     none
*/
void fmu_fg_soft_trig_fault_disable(uint8_t soft_trig_fault_num)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_SOFT_TRI_VALUE(soft_trig_fault_num)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x0028U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        FMU_FG_SWTEN((soft_trig_fault_num-FMU_SOFT_TRIG_FAULT_SNUM)/8U) &= ~(1U << (((soft_trig_fault_num-FMU_SOFT_TRIG_FAULT_SNUM) % 8U)*2U));
    }
}

/*!
    \brief      enable FMU INIT status timeout interrupt (API_ID(0x0029U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmu_init_timeout_irq_enable(void)
{
    FMU_IMTINTREN |= (uint32_t)FMU_IMTINTREN_INITTIE;
}

/*!
    \brief      disable FMU INIT status timeout interrupt (API_ID(0x002AU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void fmu_init_timeout_irq_disable(void)
{
    FMU_IMTINTREN &= (uint32_t)(~FMU_IMTINTREN_INITTIE);
}

/*!
    \brief      get FMU current interrupt status (API_ID(0x002BU))
    \param[in]  int_type: interrupt type, refer to fmu_int_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_INT_INIT: INIT timeout interrupt is pending
      \arg        FMU_INT_CAUTION: CAUTION timeout interrupt is pending
      \arg        FMU_INT_NMI: NMI interrupt 
    \param[out] none
    \retval     FlagStatus: interrupt flag status (SET or RESET)
*/
FlagStatus fmu_interrupt_flag_get(fmu_int_type_enum int_type)
{
    uint32_t reg;
    FlagStatus reval = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_INT_TYPE(int_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x002BU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reg = FMU_INTRPD;

        switch(int_type){
        /* FMU INIT timeout interrupt is pending */
        case FMU_INT_INIT:
            reg &= FMU_INTRPD_INITINTRPD;
            break;
        /* FMU CAUTION timeout interrupt is pending */
        case FMU_INT_CAUTION:
            reg &= FMU_INTRPD_CAUINTRPD;
            break;
        /* FMU NMI is pending */
        case FMU_INT_NMI:
            reg &= FMU_INTRPD_NMIINTRPD;
            break;
        /* FMU default no interrupt is pending */
        default:
            break;
        }

        /* get flag status */
        if(0U != reg) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }

    return reval;
}

/*!
    \brief      clear FMU interrupt flag (API_ID(0x002CU))
    \param[in]  int_type: interrupt type, refer to fmu_int_type_enum
                only one parameter can be selected which is shown as below:
      \arg        FMU_INT_INIT: INIT timeout interrupt is pending
    \param[out] none
    \retval     none
*/
void fmu_interrupt_flag_clear(fmu_int_type_enum int_type)
{

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_FMU_INT_TYPE_CLEAR(int_type)) {
        fw_debug_report_err(FMU_MODULE_ID, API_ID(0x002CU), ERR_PARAM_POINTER);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        switch (int_type){
        case FMU_INT_INIT:
            FMU_INTRPD |= FMU_INIT_INT_PEND;
            break;
        default:
            break;
        }
    }
}
