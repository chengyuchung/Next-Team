#ifndef IGNITION_CONTROL_H
#define IGNITION_CONTROL_H

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : ignition_control
 * 文件功能 : 点火控制业务逻辑
 * 
 * 设计目标 :
 *   1) 封装点火请求的处理逻辑（按键、CAN 命令）；
 *   2) 集成安全检查（Guard 模式、DANGER 状态锁定）；
 *   3) 提供统一的点火控制接口。
 * 
 * 架构说明 :
 *   - 点火请求来源：KEY_3 按键（通过信号量）、CAN 命令
 *   - 安全保护：
 *     * Guard 模式下禁止点火（继电器断电，PF0 无意义）
 *     * DANGER 状态下禁止点火（热管理安全边界）
 *   - 硬件控制：通过 main.h 的 ignition_set/get 操作 GPIO
 * ============================================================================
 */

/*
 * 函数名称 : ignition_control_init
 * 功能描述 : 初始化点火控制模块。
 * 输入参数 :
 *   - ignition_sem : 点火信号量句柄（由 KEY_3 按键触发）
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void ignition_control_init(SemaphoreHandle_t ignition_sem);

/*
 * 函数名称 : ignition_control_task
 * 功能描述 : 点火控制任务入口函数。
 * 输入参数 :
 *   - pvParameters : FreeRTOS 任务参数（未使用）
 * 输出参数 : 无
 * 返 回 值 : 无
 * 
 * 执行流程 :
 *   1. 阻塞等待点火信号量（KEY_3 按键触发）
 *   2. 检查点火锁定状态：
 *      - Guard 模式下禁止点火（继电器断电，PF0 无意义）
 *      - DANGER 状态下禁止点火（热管理安全边界）
 *   3. 如果未锁定，则切换点火状态
 */
void ignition_control_task(void *pvParameters);

/*
 * 函数名称 : ignition_control_handle_ignite
 * 功能描述 : 处理点火请求（CAN 命令）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - CAN_ACK_OK : 点火成功
 *   - CAN_ACK_REJECTED : 点火被拒绝（Guard 模式或 DANGER 状态锁定）
 * 
 * 注意事项 :
 *   - 此函数在 can_rx_task 上下文调用
 */
uint8_t ignition_control_handle_ignite(void);

/*
 * 函数名称 : ignition_control_handle_extinguish
 * 功能描述 : 处理熄火请求（CAN 命令）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - CAN_ACK_OK : 熄火成功
 */
uint8_t ignition_control_handle_extinguish(void);

#ifdef __cplusplus
}
#endif

#endif /* IGNITION_CONTROL_H */
