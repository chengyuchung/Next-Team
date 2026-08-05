#ifndef MQ9_MCAL_H
#define MQ9_MCAL_H

#include <stdint.h>
#include "gd32a7xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : mq9_mcal
 * 文件功能 : MQ9 可燃气体传感器 MCAL 层 - GPIO 硬件封装
 * 层次说明 :
 *   本文件只负责 GPIO 初始化和数字输入读取，不含任何业务逻辑
 *   （报警判定、抖动抑制等在 BSW/EcuAL/gas_sensor.c 里实现）
 * ============================================================================
 */

/* MQ9 通道配置 */
typedef struct {
    uint32_t gpio_port;    /* GPIO 端口 */
    uint32_t gpio_pin;     /* GPIO 引脚 */
} mq9_mcal_channel_config_t;

/* MQ9 通道数量 */
#define MQ9_MCAL_CHANNEL_COUNT  1U

/* MQ9 MCAL 初始化 - 初始化 GPIO */
void mq9_mcal_init(void);

/* 读取指定通道的 DO 电平 - 返回 0 或 1 */
uint8_t mq9_mcal_read_digital_input(uint8_t channel);

#ifdef __cplusplus
}
#endif

#endif /* MQ9_MCAL_H */
