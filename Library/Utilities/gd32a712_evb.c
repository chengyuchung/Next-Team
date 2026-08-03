/*!
    \file    gd32a712_evb.c
    \brief   demo functions to manage leds, keys, COM ports

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

#include "gd32a712_evb.h"

uint32_t eval_com = EVAL_COMA;

/* private variables */
static const uint32_t GPIO_PORT[LED_MAX]       = {LED1_GPIO_PORT,
                                                  LED2_GPIO_PORT,
                                                  LED3_GPIO_PORT,
                                                  LED4_GPIO_PORT};

static const uint32_t GPIO_PIN[LED_MAX]        = {LED1_PIN,
                                                  LED2_PIN,
                                                  LED3_PIN,
                                                  LED4_PIN};

static const rcu_periph_enum COM_CLK[COMn]     = {EVAL_COMA_CLK, 
                                                  EVAL_COMB_CLK};

static const uint32_t COM_TX_PIN[COMn]         = {EVAL_COMA_TX_PIN,
                                                  EVAL_COMB_TX_PIN};

static const uint32_t COM_RX_PIN[COMn]         = {EVAL_COMA_RX_PIN,
                                                  EVAL_COMB_RX_PIN};

static const rcu_periph_enum GPIO_CLK[LED_MAX] = {LED1_GPIO_CLK,
                                                  LED2_GPIO_CLK,
                                                  LED3_GPIO_CLK,
                                                  LED4_GPIO_CLK};

static const uint32_t KEY_PORT[KEY_MAX]        = {KEY_1_GPIO_PORT, 
                                                  KEY_2_GPIO_PORT,
                                                  KEY_3_GPIO_PORT, 
                                                  KEY_4_GPIO_PORT};

static const uint32_t KEY_PIN[KEY_MAX]         = {KEY_1_PIN, 
                                                  KEY_2_PIN,
                                                  KEY_3_PIN, 
                                                  KEY_4_PIN};

static const rcu_periph_enum KEY_CLK[KEY_MAX]  = {KEY_1_GPIO_CLK, 
                                                  KEY_2_GPIO_CLK,
                                                  KEY_3_GPIO_CLK, 
                                                  KEY_4_GPIO_CLK};

static const exti_line_enum KEY_EXTI_LINE[KEY_MAX] = {KEY_1_EXTI_LINE,
                                                      KEY_2_EXTI_LINE,
                                                      KEY_3_EXTI_LINE,
                                                      KEY_4_EXTI_LINE};

static const uint8_t KEY_PORT_SOURCE[KEY_MAX]      = {KEY_1_EXTI_PORT_SOURCE,
                                                      KEY_2_EXTI_PORT_SOURCE,
                                                      KEY_3_EXTI_PORT_SOURCE,
                                                      KEY_4_EXTI_PORT_SOURCE};

static const uint8_t KEY_PIN_SOURCE[KEY_MAX]       = {KEY_1_EXTI_PIN_SOURCE,
                                                      KEY_2_EXTI_PIN_SOURCE,
                                                      KEY_3_EXTI_PIN_SOURCE,
                                                      KEY_4_EXTI_PIN_SOURCE};

static const uint8_t KEY_IRQn[KEY_MAX]             = {KEY_1_EXTI_IRQn, 
                                                      KEY_2_EXTI_IRQn,
                                                      KEY_3_EXTI_IRQn,
                                                      KEY_4_EXTI_IRQn};

/* eval board low layer private functions */
/*!
    \brief      configure led GPIO
    \param[in]  lednum: specify the led to be configured
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_init(led_typedef_enum lednum)
{
    /* enable the led clock */
    rcu_periph_clock_enable(GPIO_CLK[lednum]);
    /* configure led GPIO port */ 
    gpio_mode_set(GPIO_PORT[lednum], GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN[lednum]);
    gpio_output_options_set(GPIO_PORT[lednum], GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN[lednum]);

    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn on selected led
    \param[in]  lednum: specify the led to be turned on
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_on(led_typedef_enum lednum)
{
    GPIO_BOP(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      turn off selected led
    \param[in]  lednum: specify the led to be turned off
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_off(led_typedef_enum lednum)
{
    GPIO_BC(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      toggle selected led
    \param[in]  lednum: specify the led to be toggled
      \arg        LED1
      \arg        LED2
      \arg        LED3
      \arg        LED4
    \param[out] none
    \retval     none
*/
void gd_eval_led_toggle(led_typedef_enum lednum)
{
    GPIO_TG(GPIO_PORT[lednum]) = GPIO_PIN[lednum];
}

/*!
    \brief      configure key
    \param[in]  keynum: specify the key to be configured
      \arg        KEY_1: user key 1
      \arg        KEY_2: user key 2
      \arg        KEY_3: user key 3
      \arg        KEY_4: user key 4
    \param[in]  keymode: specify button mode
      \arg        KEY_MODE_GPIO: key will be used as simple IO
      \arg        KEY_MODE_EXTI: key will be connected to EXTI line with interrupt
    \param[out] none
    \retval     none
*/
void gd_eval_key_init(key_typedef_enum keynum, keymode_typedef_enum keymode)
{
    /* enable the key clock */
    rcu_periph_clock_enable(RCU_SYSCFG);
    rcu_periph_clock_enable(KEY_CLK[keynum]);
    /* configure button pin as input */
    gpio_mode_set(KEY_PORT[keynum], GPIO_MODE_INPUT, GPIO_PUPD_NONE, KEY_PIN[keynum]);

    if (keymode == KEY_MODE_EXTI) {
        /* enable and set key EXTI interrupt to the lowest priority */
        nvic_irq_enable((IRQn_Type)KEY_IRQn[keynum], 2U, 0U);

        /* connect key EXTI line to key GPIO pin */
        syscfg_exti_line_config(KEY_PORT_SOURCE[keynum], KEY_PIN_SOURCE[keynum]);

        /* configure key EXTI line */
        exti_init(KEY_EXTI_LINE[keynum], EXTI_INTERRUPT, EXTI_TRIG_RISING);
        exti_interrupt_flag_clear(KEY_EXTI_LINE[keynum]);
    }
}

/*!
    \brief      return the selected key state
    \param[in]  keynum: specify the key to be checked
      \arg        KEY_1: user key 1
      \arg        KEY_2: user key 2
      \arg        KEY_3: user key 3
      \arg        KEY_4: user key 4
    \param[out] none
    \retval     the key's GPIO pin value
*/
FlagStatus gd_eval_key_state_get(key_typedef_enum keynum)
{
    return gpio_input_bit_get(KEY_PORT[keynum], KEY_PIN[keynum]);
}

/*!
    \brief      configure COM port
    \param[in]  com: COM on the board
      \arg        EVAL_COMA: COMA on the board
      \arg        EVAL_COMB: COMB on the board
    \param[out] none
    \retval     none
*/
void gd_eval_com_init(uint32_t com)
{
    uint32_t COM_ID;
    linflexd_uart_parameter_struct initpara;

    eval_com = com;

    /* enable COM GPIO clock */
    rcu_periph_clock_enable(EVAL_COMA_GPIO_CLK);
    rcu_periph_clock_enable(EVAL_COMB_GPIO_CLK);

    if(EVAL_COMA == com){
        COM_ID  = 0U;
    } else {
        COM_ID  = 1U;
    }
    /* enable USART clock */
    rcu_periph_clock_enable(COM_CLK[COM_ID]);
    rcu_linflexd_clock_config(RCU_LINFLEXDSRC_CKSYS, 4U);
    if(EVAL_COMA == com){
        /* connect port to LINFlexD_UART1_Tx */
        gpio_af_set(EVAL_COMA_GPIO_PORT, EVAL_COMA_TX_AF, COM_TX_PIN[COM_ID]);
        /* connect port to LINFlexD_UART1_Rx */
        gpio_af_set(EVAL_COMA_GPIO_PORT, EVAL_COMA_RX_AF, COM_RX_PIN[COM_ID]);
        /* configure LINFlexD_UART1 Tx as alternate function push-pull */
        gpio_mode_set(EVAL_COMA_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_TX_PIN[COM_ID]);
        gpio_output_options_set(EVAL_COMA_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, COM_TX_PIN[COM_ID]);
        /* configure LINFlexD_UART1 Rx as alternate function push-pull */
        gpio_mode_set(EVAL_COMA_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_RX_PIN[COM_ID]);
        gpio_output_options_set(EVAL_COMA_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, COM_RX_PIN[COM_ID]);
    } else {
        /* connect port to LINFlexD_UART3_Tx */
        gpio_af_set(EVAL_COMB_GPIO_PORT, EVAL_COMB_TX_AF, COM_TX_PIN[COM_ID]);
        /* connect port to LINFlexD_UART3_Rx */
        gpio_af_set(EVAL_COMB_GPIO_PORT, EVAL_COMB_RX_AF, COM_RX_PIN[COM_ID]);
        /* configure LINFlexD_UART3 Tx as alternate function push-pull */
        gpio_mode_set(EVAL_COMB_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_TX_PIN[COM_ID]);
        gpio_output_options_set(EVAL_COMB_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, COM_TX_PIN[COM_ID]);
        /* configure LINFlexD_UART3 Rx as alternate function push-pull */
        gpio_mode_set(EVAL_COMB_GPIO_PORT, GPIO_MODE_AF, GPIO_PUPD_PULLUP, COM_RX_PIN[COM_ID]);
        gpio_output_options_set(EVAL_COMB_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, COM_RX_PIN[COM_ID]);
    }
    /* LINFlexD_UART configure */
    linflexd_uart_struct_para_init(&initpara);
    linflexd_uart_init(com, &initpara);
    /* enable transmitter and receiver */
    linflexd_uart_receiver_config(com, LINFLEXD_UART_RECEIVE_ENABLE);
    linflexd_uart_transmitter_config(com, LINFLEXD_UART_TRANSMIT_ENABLE);
}

#ifdef GD_ECLIPSE_GCC
/* retarget the C library printf function to the USART, in Eclipse GCC environment */
int __io_putchar(int ch)
{
    linflexd_uart_byte_transmit(eval_com, (uint8_t) ch );
    while(RESET == linflexd_uart_flag_get(eval_com, LINFLEXD_UART_FLAG_DTF_TFF));
    linflexd_uart_flag_clear(eval_com, LINFLEXD_UART_FLAG_DTF_TFF);
    return ch;
}
#elif (defined (__ICCARM__) && (__VER__ >= 9000000))
#include <LowLevelIOInterface.h>

#pragma module_name = "?__write"

int MyLowLevelPutchar(int x)
{
    linflexd_uart_byte_transmit(eval_com, (uint8_t) x);
    while (RESET == linflexd_uart_flag_get(eval_com, LINFLEXD_UART_FLAG_DTF_TFF));
    linflexd_uart_flag_clear(eval_com, LINFLEXD_UART_FLAG_DTF_TFF);
     return x;
 
}

/* retarget the C library printf function to the USART, in IAR __VER__ >= 9000000 environment */
size_t __write(int handle, const unsigned char * buffer, size_t size)
{
  /* Remove the #if #endif pair to enable the implementation */
#if 1
  size_t nChars = 0;

  if (buffer == 0)
  {
    /*
     * This means that we should flush internal buffers.  Since we
     * don't we just return.  (Remember, "handle" == -1 means that all
     * handles should be flushed.)
     */
    return 0;
  }

  /* This template only writes to "standard out" and "standard err",
   * for all other file handles it returns failure. */
  if (handle != _LLIO_STDOUT && handle != _LLIO_STDERR)
  {
    return _LLIO_ERROR;
  }

  for (/* Empty */; size != 0; --size)
  {
    if (MyLowLevelPutchar(*buffer++) < 0)
    {
      return _LLIO_ERROR;
    }

    ++nChars;
  }

  return nChars;

#else

  /* Always return error code when implementation is disabled. */
  return _LLIO_ERROR;

#endif

}
#else
/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
    linflexd_uart_byte_transmit(eval_com, (uint8_t)ch);
    while(RESET == linflexd_uart_flag_get(eval_com, LINFLEXD_UART_FLAG_DTF_TFF));
    linflexd_uart_flag_clear(eval_com, LINFLEXD_UART_FLAG_DTF_TFF);
    return ch;
}
#endif /* GD_ECLIPSE_GCC */
