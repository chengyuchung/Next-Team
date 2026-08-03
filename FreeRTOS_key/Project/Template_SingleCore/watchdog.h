#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : watchdog
 * 文件功能 : 独立看门狗/窗口看门狗封装（当前使用 GD32 独立看门狗 FWDGT）
 * 设计目标 :
 *   1) 对外提供统一初始化、喂狗和状态接口；
 *   2) 当主循环卡死时，由硬件看门狗触发复位；
 *   3) 尽量不让上层业务直接接触底层寄存器配置。
 * ============================================================================
 */

/* 看门狗状态。 */
typedef enum {
    WATCHDOG_STATE_IDLE = 0U,
    WATCHDOG_STATE_RUNNING
} watchdog_state_t;

/*
 * 看门狗开关。
 * 说明：
 *   - 0：关闭看门狗，便于调试；
 *   - 1：开启看门狗，进入正式联调/量产前建议打开。
 */
#ifndef WATCHDOG_ENABLE
#define WATCHDOG_ENABLE 0U
#endif

/* 默认超时时间，单位 ms。 */
#ifndef WATCHDOG_DEFAULT_TIMEOUT_MS
#define WATCHDOG_DEFAULT_TIMEOUT_MS 2000U
#endif

/*
 * 初始化看门狗。
 * 若传入 0，则使用 `WATCHDOG_DEFAULT_TIMEOUT_MS`。
 */
void watchdog_init(uint32_t timeout_ms);

/* 喂狗，防止系统在正常运行时复位。 */
void watchdog_feed(void);

/* 获取看门狗当前状态。 */
watchdog_state_t watchdog_get_state(void);

#ifdef __cplusplus
}
#endif

#endif /* WATCHDOG_H */
