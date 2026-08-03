#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <stdint.h>
#include "ds18b20.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : temp_sensor (业务逻辑)
 * 文件功能 : 基于 ds18b20 底层驱动的 4 路温度采集业务层
 * 层次说明 :
 *   本文件只负责“采集策略与结果汇总”：并行启动 4 路转换、统一等待、
 *   逐路读取，向上层同时输出每一路温度、最高温、有效路数与故障位图。
 *   具体的 1-Wire 时序与 GPIO 适配由 ds18b20.c/.h 提供。
 *
 * 单位约定 :
 *   - 温度：0.1°C（tenths）
 *   - 故障位图：bit0~bit3 对应 4 路传感器（1=该路失效）
 * ============================================================================
 */

typedef struct {
    int16_t temperature[DS18B20_GD32_CHANNEL_COUNT];       /* 每一路温度，单位 0.1°C（失效路为 0） */
    uint8_t channel_valid[DS18B20_GD32_CHANNEL_COUNT];     /* 每一路有效标志：1=本次读取成功 */
    int16_t maximum_temperature;                           /* 有效路中的最高温，单位 0.1°C */
    uint8_t valid_count;                                   /* 本次读取成功的路数 */
    uint8_t fault_mask;                                    /* 失效通道位图：bit0~bit3 */
    uint8_t valid;                                         /* 1=至少有一路有效 */
} temp_result_t;

/* 业务层初始化（转调底层平台适配初始化）。 */
void temp_sensor_init(void);

/*
 * 采集 4 路温度。并行启动全部通道转换 -> 等待一次转换时间 -> 逐路读取。
 * 结果写入 *result（含每路温度）。返回值：1=至少一路有效，0=全部失效或入参非法。
 */
uint8_t temp_get(temp_result_t *result);

/* 取最近一次 temp_get 的缓存结果（无需重新采集）。 */
uint8_t temp_get_last(temp_result_t *result);

#ifdef __cplusplus
}
#endif

#endif /* TEMP_SENSOR_H */
