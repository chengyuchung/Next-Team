#ifndef MOTOR_PWM_GD32_H
#define MOTOR_PWM_GD32_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    PWM_FAN = 0,
    PWM_PUMP,
    PWM_CH_MAX
} pwm_channel_t;

typedef struct {
    uint8_t enabled;
    uint8_t duty_percent;
    uint16_t period;
    uint16_t pulse;
} pwm_channel_state_t;

void pwm_gd32_init(uint32_t pwm_freq_hz);
void pwm_set_duty_percent(pwm_channel_t ch, uint8_t duty_percent);
void pwm_set_enable(pwm_channel_t ch, uint8_t enable);
void pwm_get_state(pwm_channel_t ch, pwm_channel_state_t *state);

#ifdef __cplusplus
}
#endif

#endif /* MOTOR_PWM_GD32_H */
