#ifndef MAIN_H
#define MAIN_H

#include "gd32a7xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CPU cache */
void cache_enable(void);

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
