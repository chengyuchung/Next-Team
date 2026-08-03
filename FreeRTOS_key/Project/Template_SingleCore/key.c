#include "key.h"
#include "gd32a7xx.h"
#include "gd32a712_evb.h"

volatile uint8_t g_key3_event = 0U;
volatile uint8_t g_key4_event = 0U;

void key_init(void)
{
    /* KEY_1 is no longer used in this project (see gd32a7xx_it.c note).
     * Initialize in GPIO mode only so the pin is in a defined state,
     * no EXTI / NVIC entry for KEY_1. */
    gd_eval_key_init(KEY_1, KEY_MODE_GPIO);

    /* KEY_3 toggles ignition (PF0). Library sets up EXTI4 / NVIC
     * EXTI4_IRQn automatically when KEY_MODE_EXTI; the ISR in
     * gd32a7xx_it.c feeds ignition_sem. */
    gd_eval_key_init(KEY_3, KEY_MODE_EXTI);

    /* KEY_4 toggles guard / normal mode. Library sets up EXTI5 /
     * NVIC EXTI5_9_IRQn automatically when KEY_MODE_EXTI; the ISR
     * feeds guard_key1_sem. */
    gd_eval_key_init(KEY_4, KEY_MODE_EXTI);
}

/* NOTE: EXTI4_IRQHandler  (KEY_3) and EXTI5_9_IRQHandler (KEY_4) live
 *       in gd32a7xx_it.c to keep every interrupt vector in one place
 *       and to avoid multiple-definition link errors. KEY_3 gives
 *       ignition_sem directly from the ISR, KEY_4 gives
 *       guard_key1_sem; neither goes through the KEY_EVENT_* flags.
 *       The g_key4_event flag and the key_get_event / key_clear_event
 *       helpers are kept for backward compatibility but are no longer
 *       set anywhere - consumers will simply see KEY_EVENT_NONE. */

void key_task(void)
{
}

uint8_t key_get_event(void)
{
    uint8_t event = KEY_EVENT_NONE;

    if(g_key4_event != 0U) {
        event |= KEY_EVENT_KEY4;
    }

    return event;
}

void key_clear_event(uint8_t event_mask)
{
    if((event_mask & KEY_EVENT_KEY4) != 0U) {
        g_key4_event = 0U;
    }
}
