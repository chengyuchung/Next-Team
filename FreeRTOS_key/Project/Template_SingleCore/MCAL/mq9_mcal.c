#include "mq9_mcal.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : mq9_mcal
 * 文件功能 : MQ9 可燃气体传感器 MCAL 层 - GPIO 硬件封装
 * ============================================================================
 */

/* MQ9 GPIO 配置表 */
static const mq9_mcal_channel_config_t s_mq9_channels[MQ9_MCAL_CHANNEL_COUNT] = {
    { GPIOE, GPIO_PIN_3 },   /* MQ9 DO 数字输入 (PE3, 浮空输入) */
};

void mq9_mcal_init(void)
{
    uint8_t i;

    /* 使能 GPIOE 时钟 */
    rcu_periph_clock_enable(RCU_GPIOE);

    /* 初始化所有通道为浮空输入 */
    for(i = 0U; i < MQ9_MCAL_CHANNEL_COUNT; i++) {
        gpio_mode_set(s_mq9_channels[i].gpio_port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, s_mq9_channels[i].gpio_pin);
    }
}

uint8_t mq9_mcal_read_digital_input(uint8_t channel)
{
    if(channel >= MQ9_MCAL_CHANNEL_COUNT) {
        return 0U;
    }

    return (gpio_input_bit_get(s_mq9_channels[channel].gpio_port, s_mq9_channels[channel].gpio_pin) != RESET) ? 1U : 0U;
}
