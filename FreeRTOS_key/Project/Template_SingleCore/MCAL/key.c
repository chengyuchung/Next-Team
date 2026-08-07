#include "key.h"
#include "gd32a7xx.h"
#include "gd32a712_evb.h"
#include "main.h"

/*
 * ============================================================================
 * 模块名称 : key
 * 文件功能 : 按键 GPIO + EXTI 硬件抽象层实现（回调机制解耦版本）
 * ============================================================================
 */

/* 回调函数注册表：每个按键可以注册一个回调函数和上下文 */
typedef struct {
    key_callback_t callback;
    void *context;
} key_callback_entry_t;

static key_callback_entry_t s_callbacks[KEY_ID_MAX] = {{NULL, NULL}};

/* 保留兼容旧代码的事件标志（不推荐使用） */
volatile uint8_t g_key3_event = 0U;
volatile uint8_t g_key4_event = 0U;

void key_init(void)
{
    /* KEY_1 is no longer used in this project (see gd32a7xx_it.c note).
     * Initialize in GPIO mode only so the pin is in a defined state,
     * no EXTI / NVIC entry for KEY_1. */
    //gd_eval_key_init(KEY_1, KEY_MODE_GPIO);

    /* KEY_3 toggles ignition (PF0). Library sets up EXTI4 / NVIC
     * EXTI4_IRQn automatically when KEY_MODE_EXTI; the ISR in
     * gd32a7xx_it.c now calls key_isr_handler(KEY_ID_3) instead of
     * directly giving ignition_sem. */
    gd_eval_key_init(KEY_3, KEY_MODE_EXTI);

    /* KEY_4 toggles guard / normal mode. Library sets up EXTI5 /
     * NVIC EXTI5_9_IRQn automatically when KEY_MODE_EXTI; the ISR
     * calls key_isr_handler(KEY_ID_4) instead of directly giving
     * guard_key1_sem. */
    gd_eval_key_init(KEY_4, KEY_MODE_EXTI);

    /* CRITICAL: BSP 默认设置按键中断优先级为 2，虽然已经符合 FreeRTOS 要求
     * (>= configMAX_SYSCALL_INTERRUPT_PRIORITY = 2)，但为了确保按键响应优先级，
     * 手动重新设置为优先级 KEY_IRQ_PRIO（与 CAN 同级，确保用户交互能快速响应）。
     * 
     * 注意：优先级 2 已经可以安全调用 xSemaphoreGiveFromISR 等 FreeRTOS API。
     *      数字越小优先级越高，按键需要高优先级以避免被其他中断阻塞。
     *      
     * IMPORTANT: 参考官方 Template_SingleCore demo，key_init() 现在在 init_task 中调用
     *            （即 FreeRTOS 启动后、信号量创建后、回调注册后），所以可以直接使能中断。 */
    nvic_irq_enable(EXTI4_IRQn, KEY_IRQ_PRIO, 0U);
    nvic_irq_enable(EXTI5_9_IRQn, KEY_IRQ_PRIO, 0U);
}

uint8_t key_register_callback(key_id_t key_id, key_callback_t callback, void *context)
{
    if(key_id >= KEY_ID_MAX) {
        return 0U;
    }

    s_callbacks[key_id].callback = callback;
    s_callbacks[key_id].context = context;
    return 1U;
}

void key_isr_handler(key_id_t key_id)
{
    if(key_id >= KEY_ID_MAX) {
        return;
    }

    /* 调用注册的回调函数（如果存在） */
    if(s_callbacks[key_id].callback != NULL) {
        s_callbacks[key_id].callback(key_id, s_callbacks[key_id].context);
    }
}

/* ---- 以下为兼容旧代码保留的接口，不推荐新代码使用 ---- */

void key_task(void)
{
    /* 空实现，保留用于兼容 */
}

uint8_t key_get_event(void)
{
    uint8_t event = KEY_EVENT_NONE;

    if(g_key3_event != 0U) {
        event |= KEY_EVENT_KEY3;
    }
    if(g_key4_event != 0U) {
        event |= KEY_EVENT_KEY4;
    }

    return event;
}

void key_clear_event(uint8_t event_mask)
{
    if((event_mask & KEY_EVENT_KEY3) != 0U) {
        g_key3_event = 0U;
    }
    if((event_mask & KEY_EVENT_KEY4) != 0U) {
        g_key4_event = 0U;
    }
}
