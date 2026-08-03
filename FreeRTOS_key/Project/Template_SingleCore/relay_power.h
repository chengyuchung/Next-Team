#ifndef RELAY_POWER_H
#define RELAY_POWER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * 继电器电源控制模块。
 * 约定：
 *   - 高电平：继电器导通，电源接通；
 *   - 低电平：继电器断开，电源切断。
 */
void relay_power_init(uint8_t default_enable);
void relay_power_set(uint8_t enable);
uint8_t relay_power_get(void);
static inline void relay_power_on(void) { relay_power_set(1U); }
static inline void relay_power_off(void) { relay_power_set(0U); }

#ifdef __cplusplus
}
#endif

#endif /* RELAY_POWER_H */
