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
    { GPIOE, GPIO_PIN_3 },   /* MQ9 DO 数字输入 (PE3) */
};

void mq9_mcal_init(void)
{
    uint8_t i;

    /* 使能 GPIOE 时钟 */
    rcu_periph_clock_enable(RCU_GPIOE);

    /* 初始化所有通道为带内部上拉的输入。
     * MQ9 DO 有效电平为低（低电平=气体泄漏），正常状态应为高电平。
     * 加内部上拉是为了兜底：即使传感器未接/接触不良导致引脚
     * 处于浮空状态，也能保证读到确定的高电平（无泄漏），避免因
     * 电平漂移被连续误采到低电平而触发误报（会导致系统误入DANGER）。
     * 传感器正常接入并主动拉低时，内部上拉不会影响该拉低动作。 */
    for(i = 0U; i < MQ9_MCAL_CHANNEL_COUNT; i++) {
        gpio_mode_set(s_mq9_channels[i].gpio_port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, s_mq9_channels[i].gpio_pin);
    }
}

uint8_t mq9_mcal_read_digital_input(uint8_t channel)
{
    if(channel >= MQ9_MCAL_CHANNEL_COUNT) {
        return 0U;
    }

    return (gpio_input_bit_get(s_mq9_channels[channel].gpio_port, s_mq9_channels[channel].gpio_pin) != RESET) ? 1U : 0U;
}
