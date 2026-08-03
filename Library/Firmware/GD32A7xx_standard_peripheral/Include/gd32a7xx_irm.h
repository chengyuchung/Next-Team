/*!
    \file    gd32a7xx_irm.h
    \brief   definitions for the IRM
    
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

#ifndef GD32A7XX_IRM_H
#define GD32A7XX_IRM_H

#include "gd32a7xx.h"

/* IRM definitions */
#define IRM                                  IRM_BASE                                                /*!< IRM base address */
#define IRM_RCTL_BASE                        (IRM_BASE + 0x00000048U)                                /*!< IRM_STATUS base address */
                                        
/* registers definitions */                                                                          
#define IRM_CTL                              REG32((IRM) + 0x00000000U)                              /*!< IRM control register */
#define IRM_IRN                              REG32((IRM) + 0x00000004U)                              /*!< IRM response register */
#define IRM_IRQNSEL0                         REG32((IRM) + 0x00000008U)                              /*!< IRM IRQ select register0 */
#define IRM_IRQNSEL1                         REG32((IRM) + 0x00000018U)                              /*!< IRM IRQ select register1 */
#define IRM_IRQNSEL2                         REG32((IRM) + 0x00000028U)                              /*!< IRM IRQ select register2 */
#define IRM_IRQNSEL3                         REG32((IRM) + 0x00000038U)                              /*!< IRM IRQ select register3 */
#define IRM_CKTH0                            REG32((IRM) + 0x0000000CU)                              /*!< IRM clock threshold register0 */
#define IRM_CKTH1                            REG32((IRM) + 0x0000001CU)                              /*!< IRM clock threshold register1 */
#define IRM_CKTH2                            REG32((IRM) + 0x0000002CU)                              /*!< IRM clock threshold register2 */
#define IRM_CKTH3                            REG32((IRM) + 0x0000003CU)                              /*!< IRM clock threshold register3 */
#define IRM_CKCNT0                           REG32((IRM) + 0x00000010U)                              /*!< IRM clock counter register0 */
#define IRM_CKCNT1                           REG32((IRM) + 0x00000020U)                              /*!< IRM clock counter register1 */
#define IRM_CKCNT2                           REG32((IRM) + 0x00000030U)                              /*!< IRM clock counter register2 */
#define IRM_CKCNT3                           REG32((IRM) + 0x00000040U)                              /*!< IRM clock counter register3 */
#define IRM_CMPO0                            REG32((IRM) + 0x00000014U)                              /*!< IRM comparsion output register0 */
#define IRM_CMPO1                            REG32((IRM) + 0x00000024U)                              /*!< IRM comparsion output register1 */
#define IRM_CMPO2                            REG32((IRM) + 0x00000034U)                              /*!< IRM comparsion output register2 */
#define IRM_CMPO3                            REG32((IRM) + 0x00000044U)                              /*!< IRM comparsion output register3 */
#define IRM_RCTL(x)                          REG16((uint32_t)(IRM_RCTL_BASE + (uint32_t)((x) << 1))) /*!< IRM routing control register */

/* bits definitions */                                                                      
/* IRM_CTL */                                                                               
#define IRM_CTL_MONEN                        BIT(0)                                                  /*!< IRM monitor enable */
                                          
/* IRM_IRN */                                                                                       
#define IRM_IRN_IRQRN                        BITS(0,7)                                               /*!< IRM writes the number for interrupt response from the ISR */
                                          
/* IRM_IRQNSEL(x) */                                                                                     
#define IRM_IRQNSEL_IRQSELN                  BITS(0,7)                                               /*!< IRM select interrupt request number to monitor*/

#if defined (GD32A72XX) || defined (GD32A74XX)
#define IRM_IRQNSEL_CPUTOCPU_INT_DIR         BIT(8)                                                  /*!< IRM select IRQ21~IRQ24 interrupt direction to monitor */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* IRM_CKTH(x) */                                                                           
#define IRM_CKTH_MCT                         BITS(0,23)                                              /*!< IRM maximum clock threshold */
                                           
/* IRM_CKCNT(x) */                                                                                      
#define IRM_CKCNT_CLKCNT                     BITS(0,23)                                              /*!< IRM clock cycle counter */
                                           
/* IRM_CMPO(x) */                                                                                      
#define IRM_CMPO_CMPOR                       BIT(0)                                                  /*!< IRM staus */

/* IRM_RCTL(x) */
#define IRM_RCTL_CM7_0                       BIT(0)                                                  /*!< IRM enable Cortex-M7_0 interrupt steering */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define IRM_RCTL_CM7_1                       BIT(1)                                                  /*!< IRM enable Cortex-M7_1 interrupt steering  */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define IRM_RCTL_HSM                         BIT(2)                                                  /*!< IRM enable HSM core interrupt steering  */
#define IRM_RCTL_LOCK                        BIT(15)                                                 /*!< IRM lock the routing of the corresponding interrupt request */

/* IRM_CKTHx threshold value */
#define IRM_CKTH_THRESHOLD_VALUE             (uint32_t)0xFFFFFDU                                     /*!<  IRM_CKTHx register maximum programming value */

#if defined (GD32A72XX) || defined (GD32A74XX)
/* IRM cpu interrupt direction definition */
#define IRM_IRQNSEL_CPU0_MONITOR             (uint32_t)(0x00000000U)                                 /*!< IRQ21~IRQ24 to cpu 0 direction can be montior */
#define IRM_IRQNSEL_CPU1_MONITOR             (uint32_t)(0x00000100U)                                 /*!< IRQ21~IRQ24 to cpu 1 direction can be montior */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* constants definitions */
typedef enum
{
    IRM_MONITOR0,
    IRM_MONITOR1,
    IRM_MONITOR2,
    IRM_MONITOR3
} irm_monitor_enum;

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check monitor id parameter */
#define NOT_IRM_MONITOR_ID(monitorx)                                                               (((monitorx) != IRM_MONITOR0) && \
                                                                                                   ((monitorx) != IRM_MONITOR1) && \
                                                                                                   ((monitorx) != IRM_MONITOR2) && \
                                                                                                   ((monitorx) != IRM_MONITOR3))

#if defined (GD32A72XX) || defined (GD32A74XX)
/* check cpu interrupt direction parameter */
#define NOT_CPU_DIRECTION(direction)                                                               (((direction) != IRM_IRQNSEL_CPU0_MONITOR) && \
                                                                                                   ((direction) != IRM_IRQNSEL_CPU1_MONITOR))
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* check latency parameter */                                                  
#define LATENCY_INVALID(latency)                                                                   ((latency) > IRM_CKTH_THRESHOLD_VALUE) 
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* IRM configuration functions */
/* enable the IRM  */
void irm_enable(void);
/* disable the IRM  */
void irm_disable(void);
/* IRM acknowledge a moitored interrupt */
void irm_ack_irq(IRQn_Type irq);
/* IRM select a interrupt to moitor */
void irm_select_irq(irm_monitor_enum monitor_id, IRQn_Type irq);

#if defined (GD32A72XX) || defined (GD32A74XX)
/* IRM select cpu interrupt monitor direction */
void irm_cpu_int_direction(irm_monitor_enum monitor_id, uint32_t cpu_int_dir);
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* IRM set a maximum  latency for selected interrupt */
void irm_set_latency(irm_monitor_enum monitor_id, uint32_t latency);
/* IRM reset the clock counter for a monitor */
void irm_reset_ck_cnt(irm_monitor_enum monitor_id);
/* IRM read the clock counter for a monitor */
uint32_t irm_clk_cnt(irm_monitor_enum monitor_id);
/* IRM read the status of a monitor */
FlagStatus irm_get_status(irm_monitor_enum monitor_id);

/* IRM routing control configuration functions */
/* IRM enable Cortex-M7_0 interrupt steering */
void irm_rctl_enable_cpu0(IRQn_Type irq);
/* IRM disable Cortex-M7_0 interrupt steering */
void irm_rctl_disable_cpu0(IRQn_Type irq);
/* IRM enable Cortex-M7_1 interrupt steering */

#if defined (GD32A72XX) || defined (GD32A74XX)
void irm_rctl_enable_cpu1(IRQn_Type irq);
/* IRM disable Cortex-M7_1 interrupt steering */
void irm_rctl_disable_cpu1(IRQn_Type irq);
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* IRM enable HSM core interrupt steering */
void irm_rctl_enable_hsm(IRQn_Type irq);
/* IRM disable HSM core interrupt steering */
void irm_rctl_disable_hsm(IRQn_Type irq);
/* IRM lock the routing of the corresponding interrupt request */
void irm_rctl_lock(IRQn_Type irq);
/* IRM unlock the routing of the corresponding interrupt request */
void irm_rctl_unlock(IRQn_Type irq);

#endif /* GD32A7XX_IRM_H */
