#ifndef ACTOR_H
#define ACTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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
    GPIO_CH_LED_WHITE = 11,  /* 低温白灯 (PE10) */
    GPIO_CH_LED_GREEN = 12,  /* 正常绿灯 (PE11) */
    GPIO_CH_LED_YELLOW = 13, /* 高温黄灯 (PE12) */
    GPIO_CH_LED_RED = 14,    /* 危险红灯 (PE13) */
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

void actor_init(const actor_config_t *config);
void actor_set_channel(actor_channel_t channel, uint8_t enable);
void actor_get_channel(actor_channel_t channel, actor_channel_state_t *state);
void actor_set_all_off(void);
uint8_t actor_self_test(void);

#ifdef __cplusplus
}
#endif

#endif /* ACTOR_H */
