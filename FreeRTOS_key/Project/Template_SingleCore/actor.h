#ifndef ACTOR_H
#define ACTOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    GPIO_CH_COOLER = 0,
    GPIO_CH_HEATER,
    GPIO_CH_BUZZER,
    GPIO_CH_GATE,
    GPIO_CH_RELAY_PWR,
    GPIO_CH_MAX
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
