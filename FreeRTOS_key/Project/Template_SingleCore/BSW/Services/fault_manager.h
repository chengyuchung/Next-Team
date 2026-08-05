#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include <stdint.h>
#include "../../MCAL/adc_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : fault_manager
 * 文件功能 : 故障检测与故障码管理
 * 设计目标 :
 *   1) 监测加热片1和制冷片1的单路电流（非4路总和）；
 *   2) 统一维护故障计数、故障锁存与故障位图；
 *   3) 为 system_state 与 CAN 上报提供统一的故障结果。
 *
 * 单位与约定 :
 *   - 电流采样值：ADC raw（0~4095）；
 *   - 故障输出：1=故障，0=正常；
 *   - 位图：bit0 起始的故障组合掩码。
 *
 * 硬件通道说明（2026-08-03）：
 *   - 加热片1电流 : PH8 / ADC0_IN12（单路电流监测）
 *   - 制冷片1电流 : PH7 / ADC0_IN13（单路电流监测）
 * ============================================================================
 */

#ifndef FAULT_CURRENT_SAMPLE_COUNT
#define FAULT_CURRENT_SAMPLE_COUNT 3U
#endif

/*
 * 0A 基准自学习参数
 *   故障阈值 = 运行时采集的 0A 基准 raw + 下列裕量。
 *   这样即使 2 个 ACS712 模块之间存在批次/偏置差异，也能在运行时自适应。
 */
#ifndef FAULT_BASELINE_LEARN_COUNT
#define FAULT_BASELINE_LEARN_COUNT   10U     /* 开机后采样次数，取平均得到 0A 基准 */
#endif
#ifndef FAULT_BASELINE_MARGIN
#define FAULT_BASELINE_MARGIN         50U    /* 阈值在基准上加 50 raw */
#endif
#ifndef FAULT_BASELINE_MAX_RAW
#define FAULT_BASELINE_MAX_RAW     4095U     /* 自学习上限保护，防止越界 */
#endif

typedef struct {
    uint8_t heater_current_fault;  /* 加热片1电流故障（单路） */
    uint8_t cooler_current_fault;  /* 制冷片1电流故障（单路） */
} fault_manager_status_t;

void fault_manager_init(void);
void fault_manager_reset(void);
void fault_manager_get_act_fault(uint8_t *heater_fault, uint8_t *cooler_fault);
void fault_manager_get_status(fault_manager_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* FAULT_MANAGER_H */
