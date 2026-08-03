#include "relay_power.h"
#include "gd32a7xx.h"
#include "gd32a7xx_gpio.h"
#include "gd32a7xx_rcu.h"

/*
 * 继电器电源控制模块实现。
 *
 * 当前硬件定义：
 *   - 控制引脚：PG0
 *   - 输出高电平：继电器导通，电源接通
 *   - 输出低电平：继电器断开，电源切断
 */
static uint8_t s_relay_power_enable = 0U;

void relay_power_init(uint8_t default_enable)
{
    rcu_periph_clock_enable(RCU_GPIOG);
    gpio_mode_set(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO_PIN_0);
    gpio_output_options_set(GPIOG, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, GPIO_PIN_0);

    relay_power_set(default_enable);
}

void relay_power_set(uint8_t enable)
{
    s_relay_power_enable = (enable != 0U) ? 1U : 0U;

    if(s_relay_power_enable != 0U) {
        gpio_bit_set(GPIOG, GPIO_PIN_0);
    } else {
        gpio_bit_reset(GPIOG, GPIO_PIN_0);
    }
}

uint8_t relay_power_get(void)
{
    return s_relay_power_enable;
}
