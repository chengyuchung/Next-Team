#ifndef APP_TASKS_H
#define APP_TASKS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Compact queue element for the CAN4 RX queue.
 * can_receive_message_struct holds a 64-byte data[] array (CAN-FD size),
 * but the application only ever uses classic 8-byte frames.
 * Using this trimmed struct saves ~60 bytes per queue slot (8 slots → 480 B).
 */
typedef struct {
    uint32_t id;          /* 11-bit (standard) or 29-bit (extended) ID */
    uint8_t  xtd;         /* 0 = standard frame, 1 = extended frame */
    uint8_t  data_bytes;  /* actual payload length (0-8) */
    uint8_t  data[8];     /* payload, classic CAN only */
} can_rx_frame_t;

/*
 * =============================================================================
 * 模块名称 : app_tasks
 * 文件功能 : FreeRTOS 应用层任务集中管理
 *
 * 模块定位
 *   本模块把原先散落在 main.c 里的全部应用任务（初始化/主控/巡检/点火/CAN）
 *   及其辅助函数集中到一起，让 main.c 只负责最小启动流程与板级外设初始化。
 *
 *   任务清单：
 *     - init_task    : 一次性板级初始化 + 创建 IPC 与其余任务，随后自删除；
 *     - app_task     : 正常运行模式下的周期控制循环（状态机 + CAN 上报）；
 *     - guard_task   : 低功耗巡检模式（睡眠/巡检交替）；
 *     - ignition_task: 响应 KEY_3 点火切换；
 *     - can_rx_task  : 解析 CAN 请求帧（查询/控制/配置）。
 *
 *   IPC 对象（can4_rx_queue）与 guard 模式标志 s_guard_mode_active 在本模块
 *   定义。信号量（s_ignition_sem / s_guard_key1_sem）通过回调机制解耦，
 *   不再暴露给 ISR 直接访问。
 * =============================================================================
 */

/*
 * app_tasks_start
 *   创建 init_task。应在 main() 里 vTaskStartScheduler() 之前调用。
 *   init_task 会完成板级初始化、创建 IPC 与其余任务，然后进入 guard 模式
 *   并删除自身。
 */
void app_tasks_start(void);

/*
 * app_tasks_get_guard_current_sleep_ms
 *   查询 guard_task 自适应长睡眠算法当前实际生效的睡眠时长（毫秒）。
 *   与 g_guard_sleep_interval_ms（配置基准值）不同：本值会随巡检结果
 *   动态缩短/放大（见 app_tasks.c 的 guard_adjust_sleep_interval()）。
 *   供 CAN 查询响应（CAN_QRY_GUARD_SLEEP）读取，仅读不写。
 */
uint32_t app_tasks_get_guard_current_sleep_ms(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_TASKS_H */
