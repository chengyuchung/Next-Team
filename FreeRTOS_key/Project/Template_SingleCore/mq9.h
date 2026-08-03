#ifndef MQ9_H
#define MQ9_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : mq9
 * 文件功能 : MQ9 可燃气体传感器数字告警封装（DO 数字输入版）
 *
 * 职责边界 :
 *   1) 封装 MQ9 DO 数字输入的初始化与轮询；
 *   2) 提供气体告警判定接口，屏蔽上层对 GPIO 细节的依赖；
 *   3) 内部保留连续确认/解除计数，抑制输入抖动。
 *
 * 历史变更 :
 *   - 早期版本曾以 AO 模拟量 + adc_manager 作为采样输入；
 *   - 当前版本已切换为 DO 数字输入，相关字段/接口已清理。
 *
 * 单位约定 :
 *   - 时间值：ms（毫秒）。
 * ============================================================================
 */

/* MQ9 传感器运行配置（DO 数字输入版）。 */
typedef struct {
    uint8_t alarm_active_high;            /* DO 有效电平：1=高电平报警，0=低电平报警 */
    uint8_t alarm_confirm_count;          /* 连续有效确认次数 */
    uint8_t alarm_clear_count;            /* 连续无效解除次数 */
    uint32_t sample_interval_ms;          /* 建议采样周期（ms） */
} mq9_config_t;

/* MQ9 运行状态。 */
typedef struct {
    uint8_t ready;                        /* 就绪位：1=已就绪 */
    uint8_t alarm;                        /* 告警位：1=报警 */
    uint8_t level;                        /* 最近一次 DO 原始电平（0/1） */
} mq9_status_t;

/* MQ9 对外结果。 */
typedef struct {
    uint8_t valid;                        /* 1=有效 */
    uint8_t alarm;                        /* 1=气体泄露报警 */
} mq9_result_t;

/* 初始化 MQ9 模块。config 为 NULL 时使用默认配置。 */
void mq9_init(const mq9_config_t *config);

/* 轮询一次 MQ9，更新内部状态。 */
uint8_t mq9_task(void);

/* 获取气体检查结果：有效标志 + 报警标志。 */
uint8_t get_gas(mq9_result_t *result);

/* 直接读取当前气体告警位。 */
uint8_t mq9_get_alarm(void);

#ifdef __cplusplus
}
#endif

#endif /* MQ9_H */
