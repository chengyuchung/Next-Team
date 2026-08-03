/*!
    \file    gd32a712_evb.h
    \brief   definitions for leds, keys and COM ports hardware resources

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

#ifndef GD32A712_EVB_H
#define GD32A712_EVB_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "gd32a7xx.h"
#include <stdio.h>

/* exported types */
typedef enum 
{
    LED1 = 0,
    LED2 = 1,
    LED3 = 2,
    LED4 = 3,
    LED_MAX
}led_typedef_enum;

typedef enum 
{
    KEY_1 = 0,
    KEY_2 = 1,
    KEY_3 = 2,
    KEY_4 = 3,
    KEY_MAX
}key_typedef_enum;

typedef enum 
{
    KEY_MODE_GPIO = 0,
    KEY_MODE_EXTI = 1
}keymode_typedef_enum;

/* eval board low layer led */
#define LED1_PIN                         GPIO_PIN_13
#define LED1_GPIO_PORT                   GPIOE
#define LED1_GPIO_CLK                    RCU_GPIOE

#define LED2_PIN                         GPIO_PIN_12
#define LED2_GPIO_PORT                   GPIOE
#define LED2_GPIO_CLK                    RCU_GPIOE

#define LED3_PIN                         GPIO_PIN_11
#define LED3_GPIO_PORT                   GPIOE
#define LED3_GPIO_CLK                    RCU_GPIOE

#define LED4_PIN                         GPIO_PIN_10
#define LED4_GPIO_PORT                   GPIOE
#define LED4_GPIO_CLK                    RCU_GPIOE

/* eval board low layer button */  
/* KEY_1 push-button */
#define KEY_1_PIN                        GPIO_PIN_13
#define KEY_1_GPIO_PORT                  GPIOC
#define KEY_1_GPIO_CLK                   RCU_GPIOC
#define KEY_1_EXTI_LINE                  EXTI_13
#define KEY_1_EXTI_PORT_SOURCE           EXTI_SOURCE_GPIOC
#define KEY_1_EXTI_PIN_SOURCE            EXTI_SOURCE_PIN13
#define KEY_1_EXTI_IRQn                  EXTI10_15_IRQn

/* KEY_2 push-button */
#define KEY_2_PIN                        GPIO_PIN_3
#define KEY_2_GPIO_PORT                  GPIOL
#define KEY_2_GPIO_CLK                   RCU_GPIOL
#define KEY_2_EXTI_LINE                  EXTI_3
#define KEY_2_EXTI_PORT_SOURCE           EXTI_SOURCE_GPIOL
#define KEY_2_EXTI_PIN_SOURCE            EXTI_SOURCE_PIN3
#define KEY_2_EXTI_IRQn                  EXTI3_IRQn

/* KEY_3 push-button */
#define KEY_3_PIN                        GPIO_PIN_4
#define KEY_3_GPIO_PORT                  GPIOL
#define KEY_3_GPIO_CLK                   RCU_GPIOL
#define KEY_3_EXTI_LINE                  EXTI_4
#define KEY_3_EXTI_PORT_SOURCE           EXTI_SOURCE_GPIOL
#define KEY_3_EXTI_PIN_SOURCE            EXTI_SOURCE_PIN4
#define KEY_3_EXTI_IRQn                  EXTI4_IRQn

/* KEY_4 push-button */
#define KEY_4_PIN                        GPIO_PIN_5
#define KEY_4_GPIO_PORT                  GPIOL
#define KEY_4_GPIO_CLK                   RCU_GPIOL
#define KEY_4_EXTI_LINE                  EXTI_5
#define KEY_4_EXTI_PORT_SOURCE           EXTI_SOURCE_GPIOL
#define KEY_4_EXTI_PIN_SOURCE            EXTI_SOURCE_PIN5
#define KEY_4_EXTI_IRQn                  EXTI5_9_IRQn

/* eval board low layer COM */
#define COMn                             2U

/* definition for COM, connected to LINFLEXD_UART1 */
#define EVAL_COMA                         LINFLEXD_UART1
#define EVAL_COMA_CLK                     RCU_LINFLEXD1

#define EVAL_COMA_TX_PIN                  GPIO_PIN_7
#define EVAL_COMA_RX_PIN                  GPIO_PIN_8

#define EVAL_COMA_GPIO_PORT               GPIOH
#define EVAL_COMA_GPIO_CLK                RCU_GPIOH
#define EVAL_COMA_TX_AF                   GPIO_AF_13
#define EVAL_COMA_RX_AF                   GPIO_AF_13

/* definition for COM, connected to LINFLEXD_UART3 */
#define EVAL_COMB                         LINFLEXD_UART3
#define EVAL_COMB_CLK                     RCU_LINFLEXD3

#define EVAL_COMB_TX_PIN                  GPIO_PIN_8
#define EVAL_COMB_RX_PIN                  GPIO_PIN_7

#define EVAL_COMB_GPIO_PORT               GPIOJ
#define EVAL_COMB_GPIO_CLK                RCU_GPIOJ
#define EVAL_COMB_TX_AF                   GPIO_AF_13
#define EVAL_COMB_RX_AF                   GPIO_AF_13

/* function declarations */
/* configure led GPIO */
void gd_eval_led_init(led_typedef_enum lednum);
/* turn on selected led */
void gd_eval_led_on(led_typedef_enum lednum);
/* turn off selected led */
void gd_eval_led_off(led_typedef_enum lednum);
/* toggle the selected led */
void gd_eval_led_toggle(led_typedef_enum lednum);
/* configure key */
void gd_eval_key_init(key_typedef_enum keynum, keymode_typedef_enum keymode);
/* return the selected key state */
FlagStatus gd_eval_key_state_get(key_typedef_enum keynum);
/* configure COM port */
void gd_eval_com_init(uint32_t com);

#ifdef __cplusplus
}
#endif

#endif /* GD32A712_EVB_H */

