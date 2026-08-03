#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include <stdint.h>
#include "app_config.h"
#include "adc_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : fault_manager
 * 文件功能 : 故障检测与故障码管理
 * 设计目标 :
 *   1) 将执行器过流、传感器异常、通信异常等诊断逻辑从业务状态机中拆分出来；
 *   2) 统一维护故障计数、故障锁存与故障位图；
 *   3) 为 system_state 与 CAN 上报提供统一的故障结果。
 *
 * 单位与约定 :
 *   - 电流采样值：ADC raw（0~4095）；
 *   - 故障输出：1=故障，0=正常；
 *   - 位图：bit0 起始的故障组合掩码。
 * ============================================================================
 */

#ifndef FAULT_TEMP_MAX_COUNT
#define FAULT_TEMP_MAX_COUNT 3U
#endif
#ifndef FAULT_CURRENT_SAMPLE_COUNT
#define FAULT_CURRENT_SAMPLE_COUNT 3U
#endif
#ifndef FAULT_GAS_MIN_RAW
#define FAULT_GAS_MIN_RAW 50U
#endif
#ifndef FAULT_GAS_MAX_RAW
#define FAULT_GAS_MAX_RAW 3800U
#endif
#ifndef FAULT_FAN_MIN_RAW
#define FAULT_FAN_MIN_RAW 50U
#endif
#ifndef FAULT_FAN_MAX_RAW
#define FAULT_FAN_MAX_RAW 3800U
#endif
#ifndef FAULT_PUMP_MIN_RAW
#define FAULT_PUMP_MIN_RAW 50U
#endif
#ifndef FAULT_PUMP_MAX_RAW
#define FAULT_PUMP_MAX_RAW 3800U
#endif
#ifndef FAULT_COOLER_MIN_RAW
#define FAULT_COOLER_MIN_RAW 50U
#endif
#ifndef FAULT_COOLER_MAX_RAW
#define FAULT_COOLER_MAX_RAW 3800U
#endif
#ifndef FAULT_GATE_MIN_RAW
#define FAULT_GATE_MIN_RAW 50U
#endif
#ifndef FAULT_GATE_MAX_RAW
#define FAULT_GATE_MAX_RAW 3800U
#endif

/*
 * 0A 基准自学习参数
 *   故障阈值 = 运行时采集的 0A 基准 raw + 下列裕量。
 *   这样即使 4 个 ACS712 模块之间存在批次/偏置差异，也能在运行时自适应。
 */
#ifndef FAULT_BASELINE_LEARN_COUNT
#define FAULT_BASELINE_LEARN_COUNT   16U     /* 开机后采样次数，取平均得到 0A 基准 */
#endif
#ifndef FAULT_BASELINE_MARGIN
#define FAULT_BASELINE_MARGIN         10U    /* 阈值在基准上加 10 raw ≈ +40mV ≈ +0.2A */
#endif
#ifndef FAULT_BASELINE_MAX_RAW
#define FAULT_BASELINE_MAX_RAW     3800U     /* 自学习上限保护，防止越界 */
#endif

typedef struct {
    uint8_t fan_current_fault;
    uint8_t pump_current_fault;
    uint8_t cooler_current_fault;
    uint8_t gate_current_fault;
} fault_manager_status_t;

void fault_manager_init(void);
void fault_manager_reset(void);
void fault_manager_get_act_fault(uint8_t *fan_fault, uint8_t *pump_fault, uint8_t *cooler_fault, uint8_t *gate_fault);
void fault_manager_get_status(fault_manager_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* FAULT_MANAGER_H */
