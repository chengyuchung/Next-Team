#ifndef THERMAL_CONTROL_H
#define THERMAL_CONTROL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : thermal_control
 * 文件功能 : 热管理控制业务逻辑
 * 
 * 设计目标 :
 *   1) 封装传感器数据采集、状态机更新、执行器控制的完整流程；
 *   2) 与任务调度解耦，提供独立的控制周期接口；
 *   3) 支持手动模式与自动模式切换。
 * 
 * 架构说明 :
 *   - 传感器数据采集：通过 sensor_manager 聚合多源传感器
 *   - 状态机更新：调用 system_state 模块驱动温控状态机
 *   - 执行器控制：通过 actor_hal / motor_pwm_gd32 控制硬件
 * ============================================================================
 */

/*
 * 函数名称 : thermal_control_init
 * 功能描述 : 初始化热管理控制模块。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void thermal_control_init(void);

/*
 * 函数名称 : thermal_control_set_manual_mode
 * 功能描述 : 设置手动/自动模式。
 * 输入参数 :
 *   - enable : 1=手动模式，0=自动模式
 * 输出参数 : 无
 * 返 回 值 : 无
 * 
 * 注意事项 :
 *   - 手动模式下不覆盖执行器（风扇/水泵/制冷/加热/蜂鸣/泄压阀）；
 *   - DANGER 状态下会强制退出手动模式（安全兜底）。
 */
void thermal_control_set_manual_mode(uint8_t enable);

/*
 * 函数名称 : thermal_control_get_manual_mode
 * 功能描述 : 获取当前手动/自动模式状态。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - 1U : 手动模式
 *   - 0U : 自动模式
 */
uint8_t thermal_control_get_manual_mode(void);

/*
 * 函数名称 : thermal_control_update
 * 功能描述 : 执行一次完整的热管理控制周期。
 * 输入参数 :
 *   - now_ms : 当前时间戳（毫秒）
 * 输出参数 : 无
 * 返 回 值 : 无
 * 
 * 执行流程 :
 *   1. 从 sensor_manager 读取传感器数据
 *   2. 组装状态机输入结构
 *   3. 调用 system_state_task 更新状态机
 *   4. 根据状态机输出控制执行器
 */
void thermal_control_update(uint32_t now_ms);

/*
 * 函数名称 : thermal_control_is_ignition_locked
 * 功能描述 : 查询点火是否被锁定（DANGER 状态强制锁定）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - 1U : 点火锁定（禁止点火）
 *   - 0U : 点火解锁（允许点火）
 */
uint8_t thermal_control_is_ignition_locked(void);

#ifdef __cplusplus
}
#endif

#endif /* THERMAL_CONTROL_H */
