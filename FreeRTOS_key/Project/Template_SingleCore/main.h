#ifndef MAIN_H
#define MAIN_H

#include "gd32a7xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 看门狗使能开关（app_tasks.c 的 app_task 也会引用） */
#define WATCHDOG_ENABLE      0U

/* CPU cache */
void cache_enable(void);

/* 板级外设一次性初始化（在 main.c 定义，由 app_tasks.c 的 init_task 调用） */
void board_init(void);

/* ignition output control (defined in main.c) */
void ignition_set(uint8_t on);
uint8_t ignition_get(void);

/* 运行时可配置参数（通过 CAN 0x20 配置类命令动态修改） */
extern uint32_t g_guard_sleep_interval_ms;
extern uint32_t g_guard_handling_budget_ms;
extern uint32_t g_app_task_period_ms;

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */
