/*!
    \file    gd32a7xx_gpio.c
    \brief   GPIO driver

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

#include "gd32a7xx_gpio.h"

/*!
    \brief      reset GPIO port (API_ID: 0x0001U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[out] none
    \retval     none
*/
void gpio_deinit(uint32_t gpio_periph)
{
    #ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(GPIOA == gpio_periph) {
            GPIO_CTL(GPIOA) = 0xABFFFFFFU;
        }else if(GPIOB == gpio_periph) {
            GPIO_CTL(GPIOB) = 0xFFFFFFBFU;
        }else {
            GPIO_CTL(gpio_periph) = 0xFFFFFFFFU;
        }

        GPIO_OMODE(gpio_periph) = 0x00000000U;
        
        if(GPIOB == gpio_periph) {
            GPIO_OSPD(GPIOB) = 0x000000C0U;
        }else {
            GPIO_OSPD(gpio_periph) = 0x00000000U;
        }

        if(GPIOA == gpio_periph) {
            GPIO_PUD(GPIOA) = 0x64000000U;
        }else {
            GPIO_PUD(gpio_periph) = 0x00000000U;
        }
        
        GPIO_OCTL(gpio_periph) = 0x00000000U;
        GPIO_BOP(gpio_periph) = 0x00000000U;
        GPIO_LOCK(gpio_periph) = 0x00000000U;
        GPIO_AFSEL0(gpio_periph) = 0x00000000U;
        GPIO_AFSEL1(gpio_periph) = 0x00000000U;
        GPIO_BC(gpio_periph) = 0x00000000U;
        GPIO_TG(gpio_periph) = 0x00000000U;

        if(GPIOA == gpio_periph) {
            GPIO_SMCCTL(GPIOA) = 0x00002000U;
        }else if(GPIOB == gpio_periph) {
            GPIO_SMCCTL(GPIOB) = 0x00000008U;
        }else {
            GPIO_SMCCTL(gpio_periph) = 0x00000000U;
        }
        GPIO_IFEN(gpio_periph) = 0x00000000U;
        GPIO_PREN(gpio_periph) = 0x00000000U;
        
        if(GPIOA == gpio_periph) {
            GPIO_SREN(GPIOA) = 0x0000001EU;
        }else if(GPIOB == gpio_periph) {
            GPIO_SREN(GPIOB) = 0x00000001U;
        }else if(GPIOC == gpio_periph) {
            GPIO_SREN(GPIOC) = 0x00000004U;
        }else if(GPIOG == gpio_periph){
            GPIO_SREN(GPIOG) = 0x00000002U;
        }else if(GPIOH == gpio_periph){
            GPIO_SREN(GPIOH) = 0x0000003CU;
        }else {
            GPIO_SREN(gpio_periph) = 0x00000000U;
        }
        GPIO_IFCTL(gpio_periph) = 0x00000000U;
        GPIO_IFSCCTL0(gpio_periph) = 0x00000000U;
        GPIO_IFSCCTL1(gpio_periph) = 0x00000000U;
        
        if(GPIOB == gpio_periph) {
            GPIO_TMRASTAT(GPIOB) = 0x00000040U;
        }else if((GPIOE == gpio_periph) || (GPIOJ == gpio_periph)) {
            GPIO_TMRASTAT(gpio_periph) = 0x00000015U;
        }else if(GPIOK == gpio_periph) {
            GPIO_TMRASTAT(GPIOK) = 0x00000005U;
        }else {
            GPIO_IFSCCTL1(gpio_periph) = 0x00000000U;
        }

        switch(gpio_periph) {
        case GPIOA:
            /* reset GPIOA */
            rcu_periph_reset_enable(RCU_GPIOARST);
            rcu_periph_reset_disable(RCU_GPIOARST);
            break;
        case GPIOB:
            /* reset GPIOB */
            rcu_periph_reset_enable(RCU_GPIOBRST);
            rcu_periph_reset_disable(RCU_GPIOBRST);
            break;
        case GPIOC:
            /* reset GPIOC */
            rcu_periph_reset_enable(RCU_GPIOCRST);
            rcu_periph_reset_disable(RCU_GPIOCRST);
            break;
        case GPIOD:
            /* reset GPIOD */
            rcu_periph_reset_enable(RCU_GPIODRST);
            rcu_periph_reset_disable(RCU_GPIODRST);
            break;
        case GPIOE:
            /* reset GPIOE */
            rcu_periph_reset_enable(RCU_GPIOERST);
            rcu_periph_reset_disable(RCU_GPIOERST);
            break;
        case GPIOF:
            /* reset GPIOF */
            rcu_periph_reset_enable(RCU_GPIOFRST);
            rcu_periph_reset_disable(RCU_GPIOFRST);
            break;
        case GPIOG:
            /* reset GPIOG */
            rcu_periph_reset_enable(RCU_GPIOGRST);
            rcu_periph_reset_disable(RCU_GPIOGRST);
            break;
        case GPIOH:
            /* reset GPIOH */
            rcu_periph_reset_enable(RCU_GPIOHRST);
            rcu_periph_reset_disable(RCU_GPIOHRST);
            break;
        case GPIOI:
            /* reset GPIOI */
            rcu_periph_reset_enable(RCU_GPIOIRST);
            rcu_periph_reset_disable(RCU_GPIOIRST);
            break;
        case GPIOJ:
            /* reset GPIOJ */
            rcu_periph_reset_enable(RCU_GPIOJRST);
            rcu_periph_reset_disable(RCU_GPIOJRST);
            break;
        case GPIOK:
            /* reset GPIOK */
            rcu_periph_reset_enable(RCU_GPIOKRST);
            rcu_periph_reset_disable(RCU_GPIOKRST);
            break;
        case GPIOL:
            /* reset GPIOA */
            rcu_periph_reset_enable(RCU_GPIOLRST);
            rcu_periph_reset_disable(RCU_GPIOLRST);
            break;
        case GPIOM:
            /* reset GPIOM */
            rcu_periph_reset_enable(RCU_GPIOMRST);
            rcu_periph_reset_disable(RCU_GPIOMRST);
            break;
        case GPION:
            /* reset GPION */
            rcu_periph_reset_enable(RCU_GPIONRST);
            rcu_periph_reset_disable(RCU_GPIONRST);
            break;
        default:
            break;
        }
    }
}

/*!
    \brief      set GPIO mode (API_ID: 0x0002U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  mode: gpio pin mode
                only one parameter can be selected which is shown as below:
      \arg        GPIO_MODE_INPUT: input mode
      \arg        GPIO_MODE_OUTPUT: output mode
      \arg        GPIO_MODE_AF: alternate function mode
      \arg        GPIO_MODE_ANALOG: analog mode
    \param[in]  pull_up_down: gpio pin with pull-up or pull-down resistor
                only one parameter can be selected which is shown as below:
      \arg        GPIO_PUPD_NONE: floating mode, no pull-up and pull-down resistors
      \arg        GPIO_PUPD_PULLUP: with pull-up resistor
      \arg        GPIO_PUPD_PULLDOWN:with pull-down resistor
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_mode_set(uint32_t gpio_periph, uint32_t mode, uint32_t pull_up_down, uint32_t pin)
{
    uint16_t i;
    uint32_t ctl, pupd;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0002U), ERR_PERIPH);
    }else if(NOT_GPIO_MODE(mode)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0002U), ERR_PARAM_OUT_OF_RANGE);
    }else if(NOT_GPIO_PULL_MODE(pull_up_down)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0002U), ERR_PARAM_OUT_OF_RANGE);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0002U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ctl = GPIO_CTL(gpio_periph);
        pupd = GPIO_PUD(gpio_periph);

        for(i = 0U; i < 16U; i++) {
            if(0U != ((((uint32_t)1U << i)) & pin)) {
                /* clear the specified pin mode bits */
                ctl &= ~GPIO_MODE_MASK(i);
                /* set the specified pin mode bits */
                ctl |= GPIO_MODE_SET(i, mode);

                /* clear the specified pin pupd bits */
                pupd &= ~GPIO_PUPD_MASK(i);
                /* set the specified pin pupd bits */
                pupd |= GPIO_PUPD_SET(i, pull_up_down);
            }
        }

        GPIO_CTL(gpio_periph) = ctl;
        GPIO_PUD(gpio_periph) = pupd;
    }
}

/*!
    \brief      set GPIO output type and speed (API_ID: 0x0003U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  otype: gpio pin output mode
                only one parameter can be selected which is shown as below:
      \arg        GPIO_OTYPE_PP: push pull mode
      \arg        GPIO_OTYPE_OD: open drain mode
    \param[in]  speed: gpio pin output max speed
                only one parameter can be selected which is shown as below:
      \arg        GPIO_OSPEED_LEVEL_0: output speed level 0
      \arg        GPIO_OSPEED_LEVEL_1: output speed level 1
      \arg        GPIO_OSPEED_LEVEL_2: output speed level 2
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_output_options_set(uint32_t gpio_periph, uint8_t otype, uint32_t speed, uint32_t pin)
{
    uint16_t i;
    uint32_t ospeed;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    }else if(NOT_GPIO_OTYPE(otype)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    }else if(NOT_GPIO_SPEED(speed)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */

    {
        if(GPIO_OTYPE_OD == otype) {
            GPIO_OMODE(gpio_periph) |= (uint32_t)pin;
        }else {
            GPIO_OMODE(gpio_periph) &= (uint32_t)(~pin);
        }

        /* get the specified pin output speed bits value */
        ospeed = GPIO_OSPD(gpio_periph);

        for(i = 0U; i < 16U; i++) {
            if(0U != (((uint32_t)1U << i) & pin)) {
                /* clear the specified pin output speed bits */
                ospeed &= ~GPIO_OSPEED_MASK(i);
                /* set the specified pin output speed bits */
                ospeed |= GPIO_OSPEED_SET(i, speed);
            }
        }
        GPIO_OSPD(gpio_periph) = ospeed;
    }
}

/*!
    \brief      set GPIO pin bit (API_ID: 0x0004U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_set(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0004U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_BOP(gpio_periph) = (uint32_t)pin;
    }
}

/*!
    \brief      reset GPIO pin bit (API_ID: 0x0005U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0005U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_BC(gpio_periph) = (uint32_t)pin;
    }
}

/*!
    \brief      write data to the specified GPIO pin (API_ID: 0x0006U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[in]  bit_value: SET or RESET
                only one parameter can be selected which is shown as below:
      \arg        RESET: clear the port pin
      \arg        SET: set the port pin
    \param[out] none
    \retval     none
*/
void gpio_bit_write(uint32_t gpio_periph, uint32_t pin, bit_status bit_value)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0006U), ERR_PARAM_OUT_OF_RANGE);
    }else if(NOT_RESET_SET(bit_value)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0006U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(RESET != bit_value) {
            GPIO_BOP(gpio_periph) = (uint32_t)pin;
        }else {
            GPIO_BOP(gpio_periph) = (uint32_t)(pin << 16U);
        }
    }
}

/*!
    \brief      write data to the specified GPIO port (API_ID: 0x0007U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  data: specify the value to be written to the port output control register
    \param[out] none
    \retval     none
*/
void gpio_port_write(uint32_t gpio_periph, uint16_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_OCTL(gpio_periph) = (uint32_t)data;
    }
}

/*!
    \brief      get GPIO pin input status (API_ID: 0x0008U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus gpio_input_bit_get(uint32_t gpio_periph, uint32_t pin)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0008U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((uint32_t)RESET != (GPIO_ISTAT(gpio_periph) & (pin))) {
            reval = SET;
         }else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      get GPIO port input status (API_ID: 0x0009U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[out] none
    \retval     state of GPIO all pins
*/
uint16_t gpio_input_port_get(uint32_t gpio_periph)
{
    uint16_t reval = 0;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = ((uint16_t)GPIO_ISTAT(gpio_periph));
    }
    return reval;
}

/*!
    \brief      get GPIO pin output status (API_ID: 0x000AU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus gpio_output_bit_get(uint32_t gpio_periph, uint32_t pin)
{
    FlagStatus reval = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000AU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if((uint32_t)RESET != (GPIO_OCTL(gpio_periph) & (pin))) {
            reval = SET;
        }else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      get GPIO port output status (API_ID: 0x000BU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[out] none
    \retval     state of GPIO all pins
*/
uint16_t gpio_output_port_get(uint32_t gpio_periph)
{
    uint16_t reval = 0;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        reval = ((uint16_t)GPIO_OCTL(gpio_periph));
    }
    return reval;
}

/*!
    \brief      set GPIO alternate function (API_ID: 0x000CU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  alt_func_num: GPIO pin af function, please refer to specific device datasheet
                only one parameter can be selected which is shown as below:
      \arg        GPIO_AF_x(x = 0..15)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_af_set(uint32_t gpio_periph, uint32_t alt_func_num, uint32_t pin)
{
    uint16_t i;
    uint32_t afrl, afrh;
    
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    }else if(NOT_GPIO_AF(alt_func_num)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000CU), ERR_PARAM_OUT_OF_RANGE);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000CU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        afrl = GPIO_AFSEL0(gpio_periph);
        afrh = GPIO_AFSEL1(gpio_periph);

        for(i = 0U; i < 8U; i++) {
            if( 0U != (((uint32_t)1U << i) & pin)) {
                /* clear the specified pin alternate function bits */
                afrl &= ~GPIO_AFR_MASK(i);
                afrl |= GPIO_AFR_SET(i, alt_func_num);
            }
        }

        for(i = 8U; i < 16U; i++) {
            if (0U != (((uint32_t)1U << i) & pin)) {
                /* clear the specified pin alternate function bits */
                afrh &= ~GPIO_AFR_MASK(i - 8U);
                afrh |= GPIO_AFR_SET(i - 8U, alt_func_num);
            }
        }

        GPIO_AFSEL0(gpio_periph) = afrl;
        GPIO_AFSEL1(gpio_periph) = afrh;
    }
}

/*!
    \brief      lock GPIO pin bit (API_ID: 0x000DU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_pin_lock(uint32_t gpio_periph, uint32_t pin)
{
    uint32_t lock = 0x00010000U;
    lock |= pin;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000DU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        /* lock key writing sequence: write 1->write 0->write 1->read 0->read 1 */
        GPIO_LOCK(gpio_periph) = (uint32_t)lock;
        GPIO_LOCK(gpio_periph) = (uint32_t)pin;
        GPIO_LOCK(gpio_periph) = (uint32_t)lock;
        GPIO_LOCK(gpio_periph);
        GPIO_LOCK(gpio_periph);
    }
}

/*!
    \brief      toggle GPIO pin status (API_ID: 0x000EU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_bit_toggle(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000EU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_TG(gpio_periph) = (uint32_t)pin;
    }
}

/*!
    \brief      toggle GPIO port status (API_ID: 0x000FU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[out] none
    \retval     none
*/
void gpio_port_toggle(uint32_t gpio_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_TG(gpio_periph) = 0x0000FFFFU;
    }
}

/*!
    \brief      enable GPIO pin safe mode (API_ID: 0x0010U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_safe_mode_enable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0010U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_SMCCTL(gpio_periph) |= (uint32_t)pin;
    }
}

/*!
    \brief      disable GPIO pin safe mode (API_ID: 0x0011U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_safe_mode_disable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0011U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_SMCCTL(gpio_periph) &= (uint32_t)(~pin);
    }
}

/*!
    \brief      enable GPIO pin input filter (API_ID: 0x0012U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_port_filter_enable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0012U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_IFEN(gpio_periph) |= (uint32_t)pin;
    }
}

/*!
    \brief      disable GPIO pin input filter (API_ID: 0x0013U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_port_filter_disable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0013U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_IFEN(gpio_periph) &= (uint32_t)(~pin);
    }
}

/*!
    \brief      enable GPIO pin pad retaining (API_ID: 0x0014U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_port_retain_enable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0014U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_PREN(gpio_periph) |= (uint32_t)pin;
    }
}

/*!
    \brief      disable GPIO pin pad retaining (API_ID: 0x0015U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_port_retain_disable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0015U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_PREN(gpio_periph) &= (uint32_t)(~pin);
    }
}

/*!
    \brief      enable GPIO pin slew rate (API_ID: 0x0016U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_slew_enable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0016U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_SREN(gpio_periph) |= (uint32_t)pin;
    }
}

/*!
    \brief      disable GPIO pin slew rate (API_ID: 0x0017U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_slew_disable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0017U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_SREN(gpio_periph) &= (uint32_t)(~pin);
    }
}

/*!
    \brief      enable GPIO pin digital glitch filter on the interrupt pad input (API_ID: 0x0018U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_int_filt_enable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0018U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_IFCTL(gpio_periph) |= (uint32_t)pin;
    }
}

/*!
    \brief      disable GPIO pin digital glitch filter on the interrupt pad input (API_ID: 0x0019U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[out] none
    \retval     none
*/
void gpio_int_filt_disable(uint32_t gpio_periph, uint32_t pin)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0019U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_IFCTL(gpio_periph) &= (uint32_t)(~pin);
    }
}

/*!
    \brief      set GPIO port external interrupt qualification sampling period (API_ID: 0x001AU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  sampling_period: sampling period, 0 - 15
    \param[out] none
    \retval     none
*/
void gpio_int_filt_sampling_period_set(uint32_t gpio_periph, uint8_t sampling_period)
{
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    }else if(NOT_SAMPLING_PERIOD(sampling_period)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001AU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        GPIO_IFCTL(gpio_periph) &= (uint32_t)(~GPIO_IFCTL_IQSP);
        GPIO_IFCTL(gpio_periph) |= (uint32_t)((uint32_t)sampling_period << (32U - 4U));
    }
}

/*!
    \brief      set GPIO pin external interrupt filter counter (API_ID: 0x001BU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  pin: GPIO pin
                one or more parameters can be selected which are shown as below:
      \arg        GPIO_PIN_x(x=0..15), GPIO_PIN_ALL
    \param[in]  counter: sampling period, 0 - 15

    \param[out] none
    \retval     none
*/
void gpio_int_filt_sample_counter_set(uint32_t gpio_periph, uint32_t pin, uint8_t counter)
{
    uint16_t i;
    uint32_t ifc_splcntl, ifc_splcnth;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    }else if(NOT_GPIO_PIN(pin)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001BU), ERR_PARAM_OUT_OF_RANGE);
    }else if(NOT_FLITER_COUNTER(counter)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001BU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        ifc_splcntl = GPIO_IFSCCTL0(gpio_periph);
        ifc_splcnth = GPIO_IFSCCTL1(gpio_periph);

        for(i = 0U; i < 8U; i++) {
            if (0U != (((uint32_t)1U << i) & pin)) {
                ifc_splcntl &= ~GPIO_IFSCTL_SPLCNT_MASK(i);
                ifc_splcntl |= GPIO_IFSCTL_SPLCNT_SET(i, counter);
            }
        }

        for(i = 8U; i < 16U; i++) {
            if(0U != (((uint32_t)1U << i) & pin)) {
                ifc_splcnth &= ~GPIO_IFSCTL_SPLCNT_MASK(i - 8U);
                ifc_splcnth |= GPIO_IFSCTL_SPLCNT_SET(i - 8U, counter);
            }
        }

        GPIO_IFSCCTL0(gpio_periph) = ifc_splcntl;
        GPIO_IFSCCTL1(gpio_periph) = ifc_splcnth;
    }
}

/*!
    \brief      get GPIO TMR alarm status (API_ID: 0x001CU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  tmr_alarm: tmr alarm status
                only one parameter can be selected which is shown as below:
        \arg      GPIO_TMRASTAT_PXFFIO0
        \arg      GPIO_TMRASTAT_PXFFIO1
        \arg      GPIO_TMRASTAT_PXGFP
        \arg      GPIO_TMRASTAT_PXRESET
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus gpio_tmr_alarm_status_get(uint32_t gpio_periph, uint32_t tmr_alarm)
{
    FlagStatus reval = RESET;
    uint32_t tmralm;

#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    }else if(NOT_TMRALARM_STATUS(tmr_alarm)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001CU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        tmralm = GPIO_TMRASTAT(gpio_periph);

        if((uint32_t)RESET != (tmralm & tmr_alarm)) {
            reval = SET;
        }else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear GPIO port TMR alarm status (API_ID: 0x001DU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  tmr_alarm: tmr alarm status
                only one parameter can be selected which is shown as below:
        \arg      GPIO_TMRASTAT_PXFFIO0
        \arg      GPIO_TMRASTAT_PXFFIO1
        \arg      GPIO_TMRASTAT_PXGFIO
        \arg      GPIO_TMRASTAT_PXRESET
    \param[out] none
    \retval     none
*/
void gpio_tmr_alarm_status_clear(uint32_t gpio_periph, uint32_t tmr_alarm)
{
    uint32_t tmralm;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    }else if(NOT_TMRALARM_STATUS(tmr_alarm)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001DU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        tmralm = GPIO_TMRASTAT(gpio_periph);
        tmralm |= tmr_alarm;
        GPIO_TMRASTAT(gpio_periph) = tmralm;
    }
}

/*!
    \brief      get GPIO port TMR alarm mask status (API_ID: 0x001EU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  tmr_alarm: tmr alarm mask
                only one parameter can be selected which is shown as below:
        \arg      GPIO_TMRASTAT_PXFFIO0MSK
        \arg      GPIO_TMRASTAT_PXFFIO1MSK
        \arg      GPIO_TMRASTAT_PXGFIOMSK
        \arg      GPIO_TMRASTAT_PXRESETMSK
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus gpio_tmr_alarm_mask_status_get(uint32_t gpio_periph, uint32_t tmr_alarm)
{
    FlagStatus reval = RESET;
    uint32_t tmralm;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    }else if(NOT_TMRALARM_MASK(tmr_alarm)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001EU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        tmralm = GPIO_TMRASTAT(gpio_periph);
        if((uint32_t)RESET != (tmralm & tmr_alarm)) {
            reval = RESET;
        }else {
            reval = SET;
        }
    }
    return reval;
}

/*!
    \brief      enable mask GPIO port TMR alarm (API_ID: 0x001FU)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  tmr_alarm: tmr alarm mask
                only one parameter can be selected which is shown as below:
        \arg      GPIO_TMRASTAT_PXFFIO0MSK
        \arg      GPIO_TMRASTAT_PXFFIO1MSK
        \arg      GPIO_TMRASTAT_PXGFIOMSK
        \arg      GPIO_TMRASTAT_PXRESETMSK
    \param[out] none
    \retval     none
*/
void gpio_tmr_alarm_mask_enable(uint32_t gpio_periph, uint32_t tmr_alarm)
{
    uint32_t tmralm;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    }else if(NOT_TMRALARM_MASK(tmr_alarm)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x001FU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        tmralm = GPIO_TMRASTAT(gpio_periph);
        tmralm &= (0xFFFF0000U | GPIO_TMRASTAT_MASK_ALL);
        tmralm &= ~tmr_alarm;
        GPIO_TMRASTAT(gpio_periph) = tmralm;
    }
}

/*!
    \brief      disable mask GPIO port TMR alarm (API_ID: 0x0020U)
    \param[in]  gpio_periph: GPIOx(x = A,B,C..N)
                only one parameter can be selected which is shown as below:
      \arg        GPIOx(x = A,B,C..N)
    \param[in]  tmr_alarm: tmr alarm mask
                only one parameter can be selected which is shown as below:
        \arg      GPIO_TMRASTAT_PXFFIO0MSK
        \arg      GPIO_TMRASTAT_PXFFIO1MSK
        \arg      GPIO_TMRASTAT_PXGFIOMSK
        \arg      GPIO_TMRASTAT_PXRESETMSK
    \param[out] none
    \retval     none
*/
void gpio_tmr_alarm_mask_disable(uint32_t gpio_periph, uint32_t tmr_alarm)
{
    uint32_t tmralm;
#ifdef FW_DEBUG_ERR_REPORT
    /* check parameter */
    if(NOT_GPIO_PERIPH(gpio_periph)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0020U), ERR_PERIPH);
    }else if(NOT_TMRALARM_MASK(tmr_alarm)) {
        fw_debug_report_err(GPIO_MODULE_ID, API_ID(0x0020U), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        tmralm = GPIO_TMRASTAT(gpio_periph);
        tmralm &= (0xFFFF0000U | GPIO_TMRASTAT_MASK_ALL);
        tmralm |= tmr_alarm;
        GPIO_TMRASTAT(gpio_periph) = tmralm;
    }
}
