/*!
    \file    gd32a7xx_it.c
    \brief   interrupt service routines

    \version 2025-08-06, V0.1.0, firmware for GD32A7xx
    \note    Merged: FreeRTOS template (Template_SingleCore) + Thermal_Management project
            - FreeRTOS kernel takes over SVC / PendSV / SysTick via port.c aliases.
              DO NOT define those handlers here.
            - EXTI4        : KEY_3 -> ignition_sem (binary semaphore; ignition toggle)
            - EXTI10_15    : KEY_1 -> DISABLED (GPIO mode only)
            - EXTI5_9      : KEY_4 -> guard_key1_sem (toggle guard / low-power patrol mode)
            - EXTI42_101   : legacy ignition EXTI (EXTI52) -> stub, only clears flag
            - DTM_CAN4_INT0 : CAN4 RX -> can4_rx_queue
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

#include "gd32a7xx_it.h"
#include "gd32a7xx_libopt.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "can.h"
#include "app_tasks.h"  /* can_rx_frame_t */

/* ============================================================
 *  Externs from user modules (defined in main.c / key.c / can.c)
 * ============================================================ */
extern volatile uint8_t g_key4_event;

/* IPC created by the init task */
extern SemaphoreHandle_t ignition_sem;
extern SemaphoreHandle_t guard_key1_sem;
extern QueueHandle_t     can4_rx_queue;

/* guard mode flag from main.c, read by ISRs to know whether to
 * additionally wake guard_task on external events */
extern volatile uint8_t s_guard_mode_active;

/* ============================================================
 *  Cortex-M Fault Handlers (default: trap)
 * ============================================================ */

/*!
    \brief      this function handles NMI exception
*/
void NMI_Handler(void)
{
    while(1) {
    }
}

/*!
    \brief      this function handles HardFault exception
*/
void HardFault_Handler(void)
{
    while(1) {
    }
}

/*!
    \brief      this function handles MemManage exception
*/
void MemManage_Handler(void)
{
    while(1) {
    }
}

/*!
    \brief      this function handles BusFault exception
*/
void BusFault_Handler(void)
{
    while(1) {
    }
}

/*!
    \brief      this function handles UsageFault exception
*/
void UsageFault_Handler(void)
{
    while(1) {
    }
}

/*!
    \brief      this function handles DebugMon exception
*/
void DebugMon_Handler(void)
{
    while(1) {
    }
}

/* NOTE: SVC_Handler / PendSV_Handler / SysTick_Handler are intentionally
 *       omitted. FreeRTOS port.c supplies them through macro aliases
 *       defined in FreeRTOSConfig.h (vPortSVCHandler, xPortPendSVHandler,
 *       xPortSysTickHandler). Defining them here will cause multiple-
 *       definition link errors.
 */

/* ============================================================
 *  KEY_3  -> ignition toggle
 *  Project: KEY_3 toggles the ignition output (PF0). It does NOT
 *           wake guard mode; only KEY_4 and CAN RX are allowed to
 *           exit guard mode. The toggle is performed in ignition_task
 *           (not in the ISR), via ignition_sem. KEY_3 in guard mode
 *           is effectively a no-op while tickless idle is running -
 *           the EXTI still fires, but it has no effect on the relay
 *           because relay_power is forced OFF by guard_enter().
 * ============================================================ */
void EXTI4_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(RESET != exti_interrupt_flag_get(EXTI_4)) {
        exti_interrupt_flag_clear(EXTI_4);

        if(NULL != ignition_sem) {
            xSemaphoreGiveFromISR(ignition_sem, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}

/* ============================================================
 *  KEY_1  (PA13, EXTI13) - intentionally unused
 *  KEY_1 is no longer the "power" key; that role belongs to KEY_3
 *  now. The EXTI line is configured as GPIO by gd_eval_key_init()
 *  so this vector should never fire. The handler is kept as a
 *  defensive stub in case a stray external trigger arrives: clear
 *  the pending bit but do nothing else.
 * ============================================================ */
void EXTI10_15_IRQHandler(void)
{
    if(RESET != exti_interrupt_flag_get(EXTI_13)) {
        exti_interrupt_flag_clear(EXTI_13);
    }
}

/* ============================================================
 *  KEY_4  -> toggle guard (low-power patrol) mode
 *  Project: KEY_4 is the power-on/power-off key. Pressed once it
 *           exits guard mode (relay_power_on(), app_task resumed);
 *           pressed again it re-enters guard mode (relay_power_off(),
 *           app_task suspended). We give guard_key1_sem
 *           unconditionally - guard_task's state machine already
 *           tracks s_guard_mode_active, so the same signal works
 *           for "enter" and "exit". KEY_4 no longer drives the
 *           relay directly; the relay follows guard mode.
 *           KEY_4 also wakes the system from tickless idle while in
 *           guard mode (same as CAN RX).
 * ============================================================ */
void EXTI5_9_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    if(RESET != exti_interrupt_flag_get(EXTI_5)) {
        exti_interrupt_flag_clear(EXTI_5);

        if(NULL != guard_key1_sem) {
            xSemaphoreGiveFromISR(guard_key1_sem, &xHigherPriorityTaskWoken);
            portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
        }
    }
}

/* ============================================================
 *  Legacy Ignition EXTI  (EXTI52, IRQ: EXTI42_101)
 *  Project: ignition is now driven by KEY_3 (EXTI4 -> ignition_sem),
 *           so this external pin is no longer used to toggle
 *           ignition. We keep the EXTI initialised (so the line
 *           stays in a defined state) but the ISR is intentionally
 *           reduced to "clear the pending flag, do nothing else".
 *           Do NOT toggle ignition here.
 * ============================================================ */
void EXTI42_101_IRQHandler(void)
{
    if(SET == exti_interrupt_flag_get(EXTI_52)) {
        exti_interrupt_flag_clear(EXTI_52);
    }
}

/* ============================================================
 *  CAN4 RX (DTM_CAN4 INT0 line)
 *  Project: enqueue the received frame, let a task parse it.
 *           Do NOT call can_handle_cmd() inside the ISR.
 *           If guard mode is active, the RX itself is treated as
 *           a wake event (any incoming traffic implies the bus
 *           wants the device responsive again).
 *  Queue element type is can_receive_message_struct, matching
 *  can4_rx_queue created in main.c / consumed by can_rx_task.
 * ============================================================ */
void DTM_CAN4_INT0_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    can_receive_message_struct raw;
    can_rx_frame_t rx_frame;

    if(can_interrupt_flag_get(DTM_CAN4, CAN_INT_FLAG_RFIFO0_NEW)) {
        can_interrupt_flag_clear(DTM_CAN4, CAN_INT_FLAG_RFIFO0_NEW);

        can_struct_para_init(CAN_RX_MESSAGE_STRUCT, &raw);
        can_message_receive(DTM_CAN4, CAN_RXFIFO0, &raw);

        /* Copy only the fields the application needs into the compact frame */
        rx_frame.id         = raw.id;
        rx_frame.xtd        = (raw.xtd != (uint32_t)CAN_FF_STANDARD) ? 1U : 0U;
        rx_frame.data_bytes = (raw.data_bytes > 8U) ? 8U : (uint8_t)raw.data_bytes;
        {
            uint8_t i;
            for(i = 0U; i < rx_frame.data_bytes; i++) {
                rx_frame.data[i] = raw.data[i];
            }
        }

        if(NULL != can4_rx_queue) {
            xQueueSendFromISR(can4_rx_queue, &rx_frame, &xHigherPriorityTaskWoken);
        }
        if((NULL != guard_key1_sem) && (s_guard_mode_active != 0U)) {
            xSemaphoreGiveFromISR(guard_key1_sem, &xHigherPriorityTaskWoken);
        }
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}