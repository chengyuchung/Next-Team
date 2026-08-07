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
#include "gd32a712_evb.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "can_app.h"
#include "app_tasks.h"  /* can_rx_frame_t */
#include "key.h"        /* key_isr_handler */

/* ============================================================
 *  Externs from user modules (defined in main.c / key.c / can.c)
 * ============================================================ */

/* IPC created by the init task */
extern QueueHandle_t     can4_rx_queue;

/* guard mode flag from app_tasks.c */
extern volatile uint8_t s_guard_mode_active;

/* 
 * guard_key1_sem_give_from_isr
 *   提供给 CAN ISR 使用的接口，用于在 guard 模式下唤醒 guard_task。
 *   由 app_tasks.c 实现，避免 ISR 直接访问内部信号量。
 */
extern void guard_key1_sem_give_from_isr(void);

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
 *           via a callback registered by the application layer.
 *           
 *  解耦改进：中断处理不再直接操作 ignition_sem，而是调用
 *           MCAL 层的 key_isr_handler()，由回调机制通知应用层。
 *           
 *  NOTE: 按照官方 demo 规范（03_EXTI_Key_Interrupt_mode），
 *        先执行中断处理逻辑，后清除中断标志位，避免中断丢失。
 *        
 *  DEBUG: KEY_3 按下时 LED2 短暂点亮 50ms，用于调试按键响应
 *         （需要配合任务层延时后熄灭，这里仅在中断中点亮）
 * ============================================================ */
void EXTI4_IRQHandler(void)
{
    if(RESET != exti_interrupt_flag_get(EXTI_4)) {
        key_isr_handler(KEY_ID_3);
        exti_interrupt_flag_clear(EXTI_4);
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
 *           app_task suspended). 
 *           
 *  解耦改进：中断处理不再直接操作 guard_key1_sem，而是调用
 *           MCAL 层的 key_isr_handler()，由回调机制通知应用层。
 *           
 *  NOTE: 按照官方 demo 规范（03_EXTI_Key_Interrupt_mode），
 *        先执行中断处理逻辑，后清除中断标志位，避免中断丢失。
 * ============================================================ */
void EXTI5_9_IRQHandler(void)
{
    if(RESET != exti_interrupt_flag_get(EXTI_5)) {
        key_isr_handler(KEY_ID_4);
        exti_interrupt_flag_clear(EXTI_5);
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
        if(s_guard_mode_active != 0U) {
            guard_key1_sem_give_from_isr();
        }
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}