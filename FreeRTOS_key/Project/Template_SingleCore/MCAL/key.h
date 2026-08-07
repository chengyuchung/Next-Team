#ifndef KEY_H
#define KEY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : key
 * 文件功能 : 按键 GPIO + EXTI 硬件抽象层
 * 设计目标 :
 *   1) 提供按键硬件初始化接口（GPIO + EXTI 配置）；
 *   2) 通过回调机制向上层通知按键事件，解除与 FreeRTOS/应用层的耦合；
 *   3) MCAL 层不再直接操作信号量、队列等 RTOS 对象。
 * ============================================================================
 */

/* 按键 ID 定义（对应硬件按键编号） */
typedef enum {
    KEY_ID_1 = 0U,
    KEY_ID_3 = 1U,
    KEY_ID_4 = 2U,
    KEY_ID_MAX
} key_id_t;

/* 按键事件类型（用于事件标志轮询机制，保留兼容旧接口） */
typedef enum {
    KEY_EVENT_NONE = 0U,
    KEY_EVENT_KEY1 = (1U << 0),
    KEY_EVENT_KEY3 = (1U << 1),
    KEY_EVENT_KEY4 = (1U << 2),
} key_event_t;

/*
 * 按键回调函数类型
 *   key_id : 触发中断的按键 ID
 *   context : 注册时传入的用户上下文指针（可用于传递信号量句柄等）
 * 注意：回调函数在中断上下文中执行，必须遵循 ISR 安全规则。
 */
typedef void (*key_callback_t)(key_id_t key_id, void *context);

/*
 * key_init
 *   初始化所有按键的 GPIO 和 EXTI 配置，使能 EXTI 中断。
 *   
 *   安全调用顺序（推荐）：
 *     1) 创建信号量/队列等 IPC 资源
 *     2) 注册按键回调函数（key_register_callback）
 *     3) 调用 key_init() 使能中断
 *   
 *   这样可以确保中断触发时回调函数和 IPC 资源都已准备好。
 */
void key_init(void);

/*
 * key_register_callback
 *   为指定按键注册中断回调函数。
 *   参数：
 *     key_id   : 按键 ID（KEY_ID_3 / KEY_ID_4）
 *     callback : 中断触发时调用的回调函数（NULL 表示取消注册）
 *     context  : 用户上下文指针，会原样传递给回调函数
 *   返回值：
 *     1 = 注册成功
 *     0 = 参数非法或按键 ID 超出范围
 */
uint8_t key_register_callback(key_id_t key_id, key_callback_t callback, void *context);

/*
 * key_isr_handler
 *   按键中断统一入口，由 gd32a7xx_it.c 中的 EXTI ISR 调用。
 *   MCAL 内部函数，应用层不应直接调用。
 */
void key_isr_handler(key_id_t key_id);

/* ---- 以下接口保留用于兼容旧代码，不推荐新代码使用 ---- */
void key_task(void);
uint8_t key_get_event(void);
void key_clear_event(uint8_t event_mask);

#ifdef __cplusplus
}
#endif

#endif /* KEY_H */
