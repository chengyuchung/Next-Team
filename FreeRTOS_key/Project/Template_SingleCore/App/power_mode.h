#ifndef POWER_MODE_H
#define POWER_MODE_H

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : power_mode
 * 文件功能 : 低功耗模式管理（Guard 巡检模式）
 * 
 * 设计目标 :
 *   1) 封装 guard 模式的进入/退出逻辑；
 *   2) 管理 app_task 和 temp_task 的挂起/恢复；
 *   3) 控制继电器电源和执行器状态；
 *   4) 提供 guard_task 实现（巡检+长睡眠+tickless idle）。
 * 
 * 架构说明 :
 *   - Guard 模式：低功耗巡检模式，app_task 挂起，定期唤醒采样
 *   - Normal 模式：正常工作模式，app_task 运行，实时控制
 *   - 模式切换：通过 KEY_4 或 CAN 命令触发
 * ============================================================================
 */

/*
 * 函数名称 : power_mode_init
 * 功能描述 : 初始化低功耗模式管理模块。
 * 输入参数 :
 *   - app_task_handle  : app_task 句柄（用于挂起/恢复）
 *   - temp_task_handle : temp_task 句柄（用于挂起/恢复）
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void power_mode_init(TaskHandle_t app_task_handle, TaskHandle_t temp_task_handle);

/*
 * 函数名称 : power_mode_enter_guard
 * 功能描述 : 进入 guard 模式（低功耗巡检模式）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 : 无
 * 
 * 执行流程 :
 *   1. 挂起 app_task 和 temp_task
 *   2. 关闭继电器电源（relay_power_off）
 *   3. 关闭所有执行器（风扇/水泵/制冷/加热/点火）
 *   4. 设置 guard 模式标志
 */
void power_mode_enter_guard(void);

/*
 * 函数名称 : power_mode_exit_guard
 * 功能描述 : 退出 guard 模式，恢复正常工作模式。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 : 无
 * 
 * 执行流程 :
 *   1. 清除点火状态（防止 guard 期间积累的按键效果）
 *   2. 开启继电器电源（relay_power_on）
 *   3. 清除 guard 模式标志
 *   4. 恢复 app_task 和 temp_task
 */
void power_mode_exit_guard(void);

/*
 * 函数名称 : power_mode_is_guard_active
 * 功能描述 : 查询当前是否处于 guard 模式。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - 1U : guard 模式激活
 *   - 0U : 正常工作模式
 * 
 * 注意事项 :
 *   - 此函数可能在 ISR 上下文调用（CAN RX 中断需要判断是否唤醒 guard_task）
 */
uint8_t power_mode_is_guard_active(void);

#ifdef __cplusplus
}
#endif

#endif /* POWER_MODE_H */
