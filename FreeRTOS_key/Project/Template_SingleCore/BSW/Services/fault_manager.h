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
 *   1) 监测气体传感器的 ADC 输出值（PD11 / ADC0_IN9）；
 *   2) 统一维护故障计数、故障锁存与故障位图；
 *   3) 为 system_state 与 CAN 上报提供统一的故障结果。
 *
 * 单位与约定 :
 *   - ADC 采样值：ADC raw（0~4095）；
 *   - 故障输出：1=故障，0=正常；
 *   - 位图：bit0 起始的故障组合掩码。
 *
 * 硬件通道说明（2026-08-09）：
 *   - 气体传感器 : PD11 / ADC0_IN9（MQ9 模拟量输出，正常工作时 raw 在固定区间）
 * ============================================================================
 */

#ifndef FAULT_GAS_SENSOR_SAMPLE_COUNT
#define FAULT_GAS_SENSOR_SAMPLE_COUNT 3U
#endif

/*
 * 气体传感器故障判定阈值（区间，ADC raw，0~4095）。
 *
 * 判定逻辑：raw 在 [下限, 上限] 区间内 = 正常工作；
 *          raw 超出此区间 = 故障（传感器离线/异常/接线问题）。
 *
 * 现场标定数据（2026-08-09，经 CAN_QRY_ADC_RAW 查询实测）：
 *   - 正常工作时：raw 稳定在 2421~2448 之间波动（受 PH7 串扰影响，待接入
 *     真实 MQ9 模拟量后需重新标定）
 * 若后续更换气体传感器型号或调整接线，需重新测量并更新此区间。
 *
 * 运行时可通过 CAN 配置命令（0x18A/0x07、0x18A/0x08）动态修改，配置立即生效。
 */
#ifndef FAULT_GAS_SENSOR_RAW_MIN
#define FAULT_GAS_SENSOR_RAW_MIN 2416U
#endif

#ifndef FAULT_GAS_SENSOR_RAW_MAX
#define FAULT_GAS_SENSOR_RAW_MAX 2448U
#endif

/* 运行时可配置的全局变量（由 CAN 配置命令修改） */
extern uint16_t g_gas_sensor_raw_min;
extern uint16_t g_gas_sensor_raw_max;

typedef struct {
    uint8_t gas_sensor_fault;      /* 气体传感器故障（0=正常，1=故障） */
    uint8_t cooler_fault_rsvd;     /* 制冷片故障（预留，始终为0） */
    uint8_t heater_fault_rsvd;     /* 加热片故障（预留，始终为0） */
    uint8_t temp_sensor_fault_rsvd;/* 温度传感器故障（预留，始终为0） */
    uint8_t fan_fault_rsvd;        /* 风扇故障（预留，始终为0） */
    uint8_t pump_fault_rsvd;       /* 水泵故障（预留，始终为0） */
    uint8_t gate_fault_rsvd;       /* 排气阀故障（预留，始终为0） */
    uint8_t press_sensor_fault_rsvd; /* 气压传感器故障（预留，始终为0） */
} fault_manager_status_t;

void fault_manager_init(void);
void fault_manager_reset(void);
void fault_manager_update(void);
void fault_manager_get_status(fault_manager_status_t *status);

#ifdef __cplusplus
}
#endif

#endif /* FAULT_MANAGER_H */
