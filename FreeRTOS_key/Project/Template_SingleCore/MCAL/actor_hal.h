#ifndef ACTOR_HAL_H
#define ACTOR_HAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : actor_hal (Hardware Abstraction Layer)
 * 文件功能 : 热管理执行器 GPIO 硬件抽象层
 * 
 * 设计目标 :
 *   - 提供逻辑通道到物理引脚的映射
 *   - 隔离硬件细节（GPIO端口、引脚、有效电平）
 *   - 为上层业务提供统一的执行器控制接口
 * ============================================================================
 */

typedef enum {
    GPIO_CH_COOLER1 = 0,     /* 制冷片1 (PF6) */
    GPIO_CH_COOLER2 = 1,     /* 制冷片2 (PF7) */
    GPIO_CH_COOLER3 = 2,     /* 制冷片3 (PF8) */
    GPIO_CH_COOLER4 = 3,     /* 制冷片4 (PF11) */
    GPIO_CH_HEATER1 = 4,     /* PTC加热片1 (PF1) */
    GPIO_CH_HEATER2 = 5,     /* PTC加热片2 (PF2) */
    GPIO_CH_HEATER3 = 6,     /* PTC加热片3 (PF3) */
    GPIO_CH_HEATER4 = 7,     /* PTC加热片4 (PF4) */
    GPIO_CH_BUZZER = 8,      /* 蜂鸣器 */
    GPIO_CH_GATE = 9,        /* 泄压阀 */
    GPIO_CH_RELAY_PWR = 10,  /* 继电器电源 */
    GPIO_CH_LED_WHITE = 11,  /* 低温白灯 (PG2) */
    GPIO_CH_LED_GREEN = 12,  /* 正常绿灯 (PG3) */
    GPIO_CH_LED_YELLOW = 13, /* 高温黄灯 (PG4) */
    GPIO_CH_LED_RED = 14,    /* 危险红灯 (PG5) */
    GPIO_CH_MAX = 15
} actor_channel_t;

typedef enum {
    ACTOR_ACTIVE_HIGH = 1,
    ACTOR_ACTIVE_LOW = 0
} actor_active_level_t;

typedef struct {
    uint8_t enabled;
    actor_active_level_t active_level;
    uint8_t default_enable;
} actor_channel_cfg_t;

typedef struct {
    uint8_t enabled;
    actor_active_level_t active_level;
} actor_channel_state_t;

typedef struct {
    actor_channel_cfg_t channel_cfg[GPIO_CH_MAX];
} actor_config_t;

/*
 * 函数名称 : actor_init
 * 功能描述 : 初始化执行器 GPIO 硬件。
 * 输入参数 :
 *   - config : 可选配置（NULL=使用默认配置）
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void actor_init(const actor_config_t *config);

/*
 * 函数名称 : actor_set_channel
 * 功能描述 : 设置单个执行器通道开关状态。
 * 输入参数 :
 *   - channel : 逻辑通道号
 *   - enable  : 1=打开，0=关闭
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void actor_set_channel(actor_channel_t channel, uint8_t enable);

/*
 * 函数名称 : actor_get_channel
 * 功能描述 : 读取单个通道状态。
 * 输入参数 :
 *   - channel : 逻辑通道号
 * 输出参数 :
 *   - state   : 通道状态输出
 * 返 回 值 : 无
 */
void actor_get_channel(actor_channel_t channel, actor_channel_state_t *state);

/*
 * 函数名称 : actor_set_all_off
 * 功能描述 : 关闭所有执行器。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void actor_set_all_off(void);

/*
 * 函数名称 : actor_self_test
 * 功能描述 : 执行器自检（逐路拉高再拉低）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - 1U : 自检完成
 *   - 0U : 自检失败（预留）
 */
uint8_t actor_self_test(void);

#ifdef __cplusplus
}
#endif

#endif /* ACTOR_HAL_H */
