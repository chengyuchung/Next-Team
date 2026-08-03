/*!
    \file    gd32a7xx_irm.c
    \brief   IRM driver

    \version 2025-08-06, V0.1.0, firmware for GD32A7xx
*/

/*
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
#include "gd32a7xx_irm.h"

/*!
    \brief      enable IRM (API_ID: 0x0001U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void irm_enable(void)
{
    IRM_CTL |= (uint32_t)IRM_CTL_MONEN;
}

/*!
    \brief      disable IRM (API_ID: 0x0002U)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void irm_disable(void)
{
    IRM_CTL &= (uint32_t)(~IRM_CTL_MONEN);
}

/*!
    \brief      acknowledge a monitored interrupt to IRM (API_ID: 0x0003U)
    \param[in]  irq interrupt vector
    \param[out] none
    \retval     none
*/
void irm_ack_irq(IRQn_Type irq)
{
    IRM_IRN &= ~IRM_IRN_IRQRN;
    IRM_IRN |= (uint32_t)irq;
}

/*!
    \brief      select an interrupt to moitor(x) (API_ID: 0x0004U)
    \param[in]  monitor_id: configured moniyor index
      \arg        IRM_MONITOR0 
      \arg        IRM_MONITOR1
      \arg        IRM_MONITOR2
      \arg        IRM_MONITOR3
    \param[in]  irq��interrupt vector 
    \param[out] none
    \retval     none
*/
void irm_select_irq(irm_monitor_enum monitor_id, IRQn_Type irq)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_IRM_MONITOR_ID(monitor_id)) {
      fw_debug_report_err(IRM_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
      return;
    } else {
      /* do nothing */
    }
#endif /* FW_DEBUG_ERR_REPORT */

    switch(monitor_id){
    case IRM_MONITOR0:
        /* IRM 0 is selected monitor an interrupt */
        IRM_IRQNSEL0 &= ~IRM_IRQNSEL_IRQSELN;
        IRM_IRQNSEL0 |= (uint32_t)irq;
        break;
    case IRM_MONITOR1:
        /* IRM 1 is selected monitor an interrupt */
        IRM_IRQNSEL1 &= ~IRM_IRQNSEL_IRQSELN;
        IRM_IRQNSEL1 |= (uint32_t)irq;
        break;
    case IRM_MONITOR2:
        /* IRM 2 is selected monitor an interrupt */
        IRM_IRQNSEL2 &= ~IRM_IRQNSEL_IRQSELN;
        IRM_IRQNSEL2 |= (uint32_t)irq;
        break;
    case IRM_MONITOR3:
        /* IRM 3 is selected monitor an interrupt */
        IRM_IRQNSEL3 &= ~IRM_IRQNSEL_IRQSELN;
        IRM_IRQNSEL3 |= (uint32_t)irq;
        break;
    default :
        break;
    }
}

#if defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      select cpu interrupt monitor direction (API_ID: 0x0005U)
    \param[in]  monitor_id: configured moniyor index
      \arg        IRM_MONITOR0
      \arg        IRM_MONITOR1
      \arg        IRM_MONITOR2
      \arg        IRM_MONITOR3
    \param[in]  cpu_int_dir ��cpu irq21~irq24 direction is to cpu0 or cpu1
      \arg        IRM_IRQNSEL_CPU0_MONITOR
      \arg        IRM_IRQNSEL_CPU1_MONITOR
    \param[out] none
    \retval     none
*/
void irm_cpu_int_direction(irm_monitor_enum monitor_id, uint32_t cpu_int_dir)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_IRM_MONITOR_ID(monitor_id)) {
      fw_debug_report_err(IRM_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
      return;
    } else if(NOT_CPU_DIRECTION(cpu_int_dir)) {
      fw_debug_report_err(IRM_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
      return;
    } else {
      /* do nothing */
    }
#endif /* FW_DEBUG_ERR_REPORT */

    switch(monitor_id){
    case IRM_MONITOR0:
        /* IRM 0 is selected monitor an interrupt */
        IRM_IRQNSEL0 &= ~IRM_IRQNSEL_CPUTOCPU_INT_DIR;
        IRM_IRQNSEL0 |= cpu_int_dir;
        break;
    case IRM_MONITOR1:
        /* IRM 1 is selected monitor an interrupt */
        IRM_IRQNSEL1 &= ~IRM_IRQNSEL_CPUTOCPU_INT_DIR;
        IRM_IRQNSEL1 |= cpu_int_dir;
        break;
    case IRM_MONITOR2:
        /* IRM 2 is selected monitor an interrupt */
        IRM_IRQNSEL2 &= ~IRM_IRQNSEL_CPUTOCPU_INT_DIR;
        IRM_IRQNSEL2 |= cpu_int_dir;
        break;
    case IRM_MONITOR3:
        /* IRM 3 is selected monitor an interrupt */
        IRM_IRQNSEL3 &= ~IRM_IRQNSEL_CPUTOCPU_INT_DIR;
        IRM_IRQNSEL3 |= cpu_int_dir;
        break;
    default :
        break;
    }
}
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      set a maximum clock threshold for selected interrupt (API_ID: 0x0006U)
    \param[in]  monitor_id: configured moniyor index
      \arg        IRM_MONITOR0 
      \arg        IRM_MONITOR1
      \arg        IRM_MONITOR2
      \arg        IRM_MONITOR3
    \param[in]  set monitor clock maximum latency
    \retval     none
*/
void irm_set_latency(irm_monitor_enum monitor_id, uint32_t latency)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_IRM_MONITOR_ID(monitor_id)) {
      fw_debug_report_err(IRM_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
      return;
    } else if(LATENCY_INVALID(latency)) {
      fw_debug_report_err(IRM_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
      return;
    } else {
      /* do nothing */
    }
#endif /* FW_DEBUG_ERR_REPORT */

    switch(monitor_id){
    case IRM_MONITOR0:
        /* IRM 0 is selected monitor an interrupt */
        IRM_CKTH0 &= ~IRM_CKTH_MCT;
        IRM_CKTH0 |= (uint32_t)latency;
        break;
    case IRM_MONITOR1:
        /* IRM 1 is selected monitor an interrupt */
        IRM_CKTH1 &= ~IRM_CKTH_MCT;
        IRM_CKTH1 |= (uint32_t)latency;
        break;
    case IRM_MONITOR2:
        /* IRM 2 is selected monitor an interrupt */
        IRM_CKTH2 &= ~IRM_CKTH_MCT;
        IRM_CKTH2 |= (uint32_t)latency;
        break;
    case IRM_MONITOR3:
        /* IRM 3 is selected monitor an interrupt */
        IRM_CKTH3 &= ~IRM_CKTH_MCT;
        IRM_CKTH3 |= (uint32_t)latency;
        break;
    default :
        break;
    }
}

/*!
    \brief      reset the clock counter for a monitor (API_ID: 0x0007U)
    \param[in]  monitor_id: configured moniyor index
      \arg        IRM_MONITOR0 
      \arg        IRM_MONITOR1
      \arg        IRM_MONITOR2
      \arg        IRM_MONITOR3
    \retval     none
*/
void irm_reset_ck_cnt(irm_monitor_enum monitor_id)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_IRM_MONITOR_ID(monitor_id)) {
      fw_debug_report_err(IRM_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
      return;
    }
#endif /* FW_DEBUG_ERR_REPORT */

    switch(monitor_id){
    case IRM_MONITOR0:
        /* reset the IRM_MONITOR0 clock counter */
        IRM_CKCNT0 &= (uint32_t)~IRM_CKCNT_CLKCNT;
        break;
    case IRM_MONITOR1:
        /* reset the IRM_MONITOR1 clock counter */
        IRM_CKCNT1 &= (uint32_t)~IRM_CKCNT_CLKCNT;
        break;
    case IRM_MONITOR2:
        /* reset the IRM_MONITOR2 clock counter */
        IRM_CKCNT2 &= (uint32_t)~IRM_CKCNT_CLKCNT;
        break;
    case IRM_MONITOR3:
        /* reset the IRM_MONITOR3 clock counter */
        IRM_CKCNT3 &= (uint32_t)~IRM_CKCNT_CLKCNT;
        break;
    default :
        break;
    }
}

/*!
    \brief      read the clock counter for a monitor (API_ID: 0x0008U)
    \param[in]  monitor_id: configured moniyor index
      \arg        IRM_MONITOR0 
      \arg        IRM_MONITOR1
      \arg        IRM_MONITOR2
      \arg        IRM_MONITOR3
    \retval     none
*/
uint32_t irm_clk_cnt(irm_monitor_enum monitor_id)
{
   uint32_t reval = 0;

#ifdef FW_DEBUG_ERR_REPORT
   if(NOT_IRM_MONITOR_ID(monitor_id)) {
      fw_debug_report_err(IRM_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
      switch(monitor_id){
      case IRM_MONITOR0:
          /* IRM 0 is selected monitor an interrupt */
          reval = (uint32_t)IRM_CKCNT0;
          break;
      case IRM_MONITOR1:
          /* IRM 1 is selected monitor an interrupt */
          reval = (uint32_t)IRM_CKCNT1;
          break;
      case IRM_MONITOR2:
          /* IRM 2 is selected monitor an interrupt */
          reval = (uint32_t)IRM_CKCNT2;
          break;
      case IRM_MONITOR3:
          /* IRM 3 is selected monitor an interrupt */
          reval = (uint32_t)IRM_CKCNT3;
          break;
      default:
        /* Can't reach this, this code is writen to avoid 
        * MISRAC2012-Rule-16.4(Every switch statement shall have a default label) */
          break;
      }
    }
   return reval;
}

/*!
    \brief      get the comparsion result between clock threshold and clock counter (API_ID: 0x0009U)
    \param[in]  monitor_id: configured moniyor index
      \arg        IRM_MONITOR0 
      \arg        IRM_MONITOR1
      \arg        IRM_MONITOR2
      \arg        IRM_MONITOR3
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus irm_get_status(irm_monitor_enum monitor_id)
{
    FlagStatus reval = RESET;
 
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_IRM_MONITOR_ID(monitor_id)) {
      fw_debug_report_err(IRM_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
      switch(monitor_id){
      case IRM_MONITOR0:
          /* IRM 0 status flag*/
          if(0U != (IRM_CMPO0 & IRM_CMPO_CMPOR)) {
              reval = SET;
          }
          break;
      case IRM_MONITOR1:
          /* IRM 1 status flag*/
          if(0U != (IRM_CMPO1 & IRM_CMPO_CMPOR)) {
              reval = SET;
          }
          break;
      case IRM_MONITOR2:
          /* IRM 2 status flag*/
          if(0U != (IRM_CMPO2 & IRM_CMPO_CMPOR)) {
              reval = SET;
          }
          break;
      case IRM_MONITOR3:
          /* IRM 3 status flag*/
          if(0U != (IRM_CMPO3 & IRM_CMPO_CMPOR)) {
              reval = SET;
          }
          break;
      default :
          break;
      }
    }
    
    return reval;
}

/*!
    \brief      enable Cortex-M7_0 interrupt routing (API_ID: 0x000AU)
    \param[in]  irq: irq vector
    \param[out] none
    \retval     none
*/
void irm_rctl_enable_cpu0(IRQn_Type irq)
{
    IRM_RCTL((uint32_t)irq) |= ((uint16_t)IRM_RCTL_CM7_0);
}

/*!
    \brief      disable Cortex-M7_0 interrupt routing (API_ID: 0x000BU)
    \param[in]  irq: irq vector
    \param[out] none
    \retval     none
*/
void irm_rctl_disable_cpu0(IRQn_Type irq)
{
    IRM_RCTL((uint32_t)irq) &= (uint16_t)(~IRM_RCTL_CM7_0);
}

#if defined (GD32A72XX) || defined (GD32A74XX)
/*!
    \brief      enable Cortex-M7_1 interrupt routing (API_ID: 0x000CU)
    \param[in]  irq: irq vector
    \param[out] none
    \retval     none
*/
void irm_rctl_enable_cpu1(IRQn_Type irq)
{
    IRM_RCTL((uint32_t)irq) |= (uint16_t)IRM_RCTL_CM7_1;
}

/*!
    \brief      disable Cortex-M7_1 interrupt routing (API_ID: 0x000DU)
    \param[in]  irq: irq vector
    \param[out] none
    \retval     none
*/
void irm_rctl_disable_cpu1(IRQn_Type irq)
{
    IRM_RCTL((uint32_t)irq) &= (uint16_t)(~IRM_RCTL_CM7_1);
}
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/*!
    \brief      enable HSM interrupt routing (API_ID: 0x000EU)
    \param[in]  irq: irq vector
    \param[out] none
    \retval     none
*/
void irm_rctl_enable_hsm(IRQn_Type irq)
{
    IRM_RCTL((uint32_t)irq) |= (uint16_t)IRM_RCTL_HSM;
}

/*!
    \brief      disable HSM interrupt routing (API_ID: 0x000FU)
    \param[in]  irq: irq vector
    \param[out] none
    \retval     none
*/
void irm_rctl_disable_hsm(IRQn_Type irq)
{
    IRM_RCTL((uint32_t)irq) &= (uint16_t)(~IRM_RCTL_HSM);
}

/*!
    \brief      lock write interrupt routing register (API_ID: 0x0010U)
    \param[in]  irq: irq vector
    \param[out] none
    \retval     none
*/
void irm_rctl_lock(IRQn_Type irq)
{
    IRM_RCTL((uint32_t)irq) |= (uint16_t)IRM_RCTL_LOCK;
}

/*!
    \brief      unlock write interrupt routing register (API_ID: 0x0011U)
    \param[in]  irq: irq vector
    \param[out] none
    \retval     none
*/
void irm_rctl_unlock(IRQn_Type irq)
{
    IRM_RCTL((uint32_t)irq) &= (uint16_t)(~IRM_RCTL_LOCK);
}
