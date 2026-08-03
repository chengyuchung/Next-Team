#ifndef KEY_H
#define KEY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    KEY_EVENT_NONE = 0U,
    KEY_EVENT_KEY1 = (1U << 0),
    KEY_EVENT_KEY3 = (1U << 1),
    KEY_EVENT_KEY4 = (1U << 2),
} key_event_t;

void key_init(void);
void key_task(void);
uint8_t key_get_event(void);
void key_clear_event(uint8_t event_mask);

#ifdef __cplusplus
}
#endif

#endif /* KEY_H */
