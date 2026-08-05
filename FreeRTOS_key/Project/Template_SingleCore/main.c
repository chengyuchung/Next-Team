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

#include "can.h"
#include "watchdog.h"
#include "bmp280.h"
#include "temp_sensor.h"
#include "adc_manager.h"
#include "mq9.h"
#include "motor_pwm_gd32.h"
#include "relay_power.h"
#include "actor.h"
#include "key.h"
#include "power_manager.h"
#include "system_state.h"
#include "fault_manager.h"

/* ---- ignition output GPIO --------------------------------------------- */
#define IGNITION_GPIO_RCU    RCU_GPIOF
#define IGNITION_GPIO_PORT   GPIOF
#define IGNITION_GPIO_PIN    GPIO_PIN_0

/* ---- CAN4 RX interrupt priority (MUST be >= configMAX_SYSCALL_INTERRUPT_PRIORITY) */
#define CAN4_RX_IRQ_PRIO     5U
#define IGNITION_IRQ_PRIO    5U

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

    /* KEY_1 (GPIO only, no EXTI - intentionally unused now);
     * KEY_3 (EXTI_4, IRQ EXTI4)       = ignition toggle (PF0);
     * KEY_4 (EXTI_5, IRQ EXTI5_9)     = guard / normal mode toggle,
     *                                    also drives relay_power along
     *                                    with the mode. */
    key_init();

    /* legacy ignition-button EXTI (EXTI52 -> EXTI42_101 IRQ).
     * The pin itself is still initialised so the line stays in a
     * defined state, but its ISR no longer drives ignition - that
     * role belongs to KEY_3 (EXTI4 -> ignition_sem). */
    exti_init(EXTI_52, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    exti_interrupt_enable(EXTI_52);
    nvic_irq_enable(EXTI42_101_IRQn, IGNITION_IRQ_PRIO, 0U);

    /* wake-up event line */
    exti_init(EXTI_47, EXTI_EVENT, EXTI_TRIG_RISING);

    ignition_gpio_init();

    can_gpio_config();
    can_config(DTM_CAN4, 1000U);
    can_enable_rx_interrupt(DTM_CAN4, CAN4_RX_IRQ_PRIO);

    (void)bmp280_init(BMP280_I2C_ADDR_0X76);

    /* 4路DS18B20：分区测温，每路对应一个加热/制冷分区 */
    temp_sensor_init();

    /* adc_manager_init();  // TODO: re-enable once power-up hang is resolved */

    mq9_init(NULL);

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
    gd_eval_led_init(LED1);
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
    } else {
        gpio_bit_reset(IGNITION_GPIO_PORT, IGNITION_GPIO_PIN);
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
