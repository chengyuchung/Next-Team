/*!
    \file    main.c
    \brief   thermal management application on FreeRTOS (GD32A7xx)

    \version 2025-08-06, V0.1.0, firmware for GD32A7xx
    \note    Ported from the bare-metal super-loop (Core/Src/main.c) onto the
             FreeRTOS single-core template.

             main.c 只负责最小启动流程与板级外设初始化：
               main()      : 设置 NVIC 分组 -> 创建 init_task -> 启动调度器；
               board_init(): 所有外设的一次性上电初始化（由 init_task 调用）；
               ignition_*  : 点火输出 (PF0) 的 GPIO 控制。

             全部 FreeRTOS 应用任务（init/app/guard/ignition/can_rx）及其辅助
             函数集中在 app_tasks.c 中，通过 app_tasks_start() 启动。
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.
    All rights reserved. (BSD-3-Clause, see original template header.)
*/

#include "gd32a7xx.h"
#include "gd32a712_evb.h"

#include "FreeRTOS.h"
#include "task.h"

#include "main.h"
#include "app_tasks.h"

#include "can_app.h"
#include "watchdog.h"
#include "BSW/EcuAL/pressure_sensor.h"
#include "BSW/EcuAL/temp_sensor.h"
#include "MCAL/adc_manager.h"
#include "BSW/EcuAL/gas_sensor.h"
#include "motor_pwm_gd32.h"
#include "relay_power.h"
#include "MCAL/actor_hal.h"
#include "key.h"
#include "BSW/Services/system_state.h"
#include "BSW/Services/fault_manager.h"

/* ---- ignition output GPIO --------------------------------------------- */
#define IGNITION_GPIO_RCU    RCU_GPIOF
#define IGNITION_GPIO_PORT   GPIOF
#define IGNITION_GPIO_PIN    GPIO_PIN_0

/* ---- module-local state ----------------------------------------------- */
static uint8_t s_ignition_on = 0U;

/* ---- forward declarations --------------------------------------------- */
static void led_init(void);
static void ignition_gpio_init(void);

/* ============================================================
 *  main : set NVIC grouping, spawn init task, start scheduler
 * ============================================================ */
int main(void)
{

    
    /* 4 bits pre-emption priority, 0 bit sub-priority (required by FreeRTOS port) */
    nvic_priority_group_set(NVIC_PRIGROUP_PRE4_SUB0);

    app_tasks_start();

    vTaskStartScheduler();

    /* only reached if the kernel could not start */
    while(1) {
    }
}

/* ============================================================
 *  board_init : all the peripheral setup that used to live at the
 *               top of the bare-metal main(). Called by init_task.
 * ============================================================ */
void board_init(void)
{
    cache_enable();

    led_init();

    rcu_periph_clock_enable(RCU_PMU);

    /* 注意：按键初始化已移到 init_task 中，在 FreeRTOS 启动后执行，
     * 这样可以确保信号量和回调函数都已准备好再使能中断。
     * 参考官方 Template_SingleCore demo 的做法。 */

    /* EXTI_47 是用于 FreeRTOS tickless idle 低功耗模式的唤醒事件线。
     * 如果不需要 tickless idle 功能，可以注释掉这一行。 */
    /* exti_init(EXTI_47, EXTI_EVENT, EXTI_TRIG_RISING); */

    ignition_gpio_init();

    can_app_init();

    (void)pressure_sensor_init(0x76U);

    /* 4路DS18B20：分区测温，每路对应一个加热/制冷分区 */
    temp_sensor_init();

    /* adc_manager_init();  // TODO: re-enable once power-up hang is resolved */

    gas_sensor_init(NULL);

    pwm_gd32_init(20000U);

    relay_power_init(0U);

    {
        actor_config_t gpio_cfg = {0};
        actor_init(&gpio_cfg);
    }

    system_state_init();

#if WATCHDOG_ENABLE
    watchdog_init(WATCHDOG_DEFAULT_TIMEOUT_MS);
#endif
}

static void led_init(void)
{
    /* 初始化所有 LED */
    gd_eval_led_init(LED1);
    gd_eval_led_init(LED2);
    gd_eval_led_init(LED3);
    gd_eval_led_init(LED4);
    
    /* 上电时测试所有 LED：全部点亮 1 秒，然后全部熄灭
     * 这样可以验证 LED 硬件是否正常 */
    gd_eval_led_on(LED1);
    gd_eval_led_on(LED2);
    gd_eval_led_on(LED3);
    gd_eval_led_on(LED4);
    
    /* 简单延时 1 秒（粗略延时，仅用于测试） */
    for(volatile uint32_t i = 0; i < 20000000; i++) {
        __NOP();
    }
    
    /* 全部熄灭 */
    gd_eval_led_off(LED1);
    gd_eval_led_off(LED2);
    gd_eval_led_off(LED3);
    gd_eval_led_off(LED4);
}

static void ignition_gpio_init(void)
{
    rcu_periph_clock_enable(IGNITION_GPIO_RCU);
    gpio_mode_set(IGNITION_GPIO_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, IGNITION_GPIO_PIN);
    gpio_output_options_set(IGNITION_GPIO_PORT, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, IGNITION_GPIO_PIN);
    gpio_bit_reset(IGNITION_GPIO_PORT, IGNITION_GPIO_PIN);
}

void ignition_set(uint8_t on)
{
    s_ignition_on = (on != 0U) ? 1U : 0U;
    if(s_ignition_on != 0U) {
        gpio_bit_set(IGNITION_GPIO_PORT, IGNITION_GPIO_PIN);
        gd_eval_led_on(LED3);   /* LED3 亮表示点火已打开 */
    } else {
        gpio_bit_reset(IGNITION_GPIO_PORT, IGNITION_GPIO_PIN);
        gd_eval_led_off(LED3);  /* LED3 灭表示点火已关闭 */
    }
}

uint8_t ignition_get(void)
{
    return s_ignition_on;
}

void cache_enable(void)
{
    SCB_EnableICache();
    SCB_EnableDCache();
}
