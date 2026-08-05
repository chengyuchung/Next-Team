#ifndef ADC_ECUAL_H
#define ADC_ECUAL_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : adc_ecual
 * 文件功能 : ADC EcuAL 层 - 业务逻辑到硬件通道的映射
 *
 * 设计目标 :
 *   1) 将应用层的业务逻辑名称映射到 MCAL 层的硬件通道号；
 *   2) 解耦 MCAL 层与应用层，MCAL 只知道硬件通道，不知道业务含义；
 *   3) 提供业务逻辑友好的 ADC 读取接口。
 *
 * 架构分层 :
 *   App Layer      → 使用业务逻辑名称 (GAS_SENSOR, COOLER_CURRENT)
 *   BSW/EcuAL      → 映射层 (本模块)
 *   MCAL Layer     → 硬件通道号 (ADC_CH_IN12, ADC_CH_IN13)
 * ============================================================================
 */

/*
 * ADC 业务逻辑通道枚举
 *
 * 说明：
 *   - 应用层使用此枚举访问 ADC，不需要知道具体的硬件通道号；
 *   - 硬件通道映射由本模块的实现文件负责。
 */
typedef enum {
    ADC_ECUAL_CH_GAS_SENSOR = 0U,   /* 气体传感器模拟量输入 */
    ADC_ECUAL_CH_COOLER_CURRENT,    /* 制冷片电流监测 */
    ADC_ECUAL_CH_MAX
} adc_ecual_channel_t;

/*
 * 函数名称 : adc_ecual_read_raw
 * 功能描述 : 读取指定业务通道的 ADC 原始 12bit 码值。
 * 输入参数 :
 *   - channel   : 业务逻辑通道 ID（adc_ecual_channel_t）
 * 输出参数 :
 *   - raw_12bit : 输出原始码值，单位 LSB，范围 0~4095
 * 返 回 值 :
 *   - 1U : 成功
 *   - 0U : 失败（参数非法、硬件读取失败等）
 */
uint8_t adc_ecual_read_raw(adc_ecual_channel_t channel, uint16_t *raw_12bit);

/*
 * 函数名称 : adc_ecual_read_mv
 * 功能描述 : 读取指定业务通道并按参考电压换算输入电压（mV）。
 * 输入参数 :
 *   - channel : 业务逻辑通道 ID（adc_ecual_channel_t）
 *   - vref_mv : ADC 参考电压，单位 mV（典型值 3300）
 * 输出参数 :
 *   - mv      : 输出电压值，单位 mV
 * 返 回 值 :
 *   - 1U : 成功
 *   - 0U : 失败（参数非法或底层读取失败）
 */
uint8_t adc_ecual_read_mv(adc_ecual_channel_t channel, uint16_t vref_mv, uint16_t *mv);

#ifdef __cplusplus
}
#endif

#endif /* ADC_ECUAL_H */
