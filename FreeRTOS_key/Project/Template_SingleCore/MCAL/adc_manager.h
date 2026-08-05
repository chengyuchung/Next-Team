#ifndef ADC_MANAGER_H
#define ADC_MANAGER_H

#include <stdint.h>
#include "gd32a7xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : adc_manager（接口头文件）
 * 文件功能 : 对外提供 ADC 采样管理模块的数据类型与 API 声明。
 *
 * 设计约定 :
 *   1) 所有读取接口返回 uint8_t 状态码：1U=成功，0U=失败；
 *   2) 原始采样值统一为 12bit（0~4095，单位 LSB）；
 *   3) 电压换算统一使用 mV（毫伏）。
 *
 * 解耦原则 :
 *   - MCAL 层只使用硬件通道号（ADC_CH_INxx），不包含业务含义；
 *   - 业务逻辑到硬件通道的映射由 BSW/EcuAL 层负责。
 * ============================================================================
 */

/*
 * ADC 硬件通道枚举（与 GD32A7xx ADC 外设通道一一对应）。
 *
 * 命名规则：
 *   - ADC_CH_INxx : 对应 ADC0_INxx 硬件通道
 *   - ADC_CH_MAX  : 通道总数（边界标识）
 *
 * 硬件映射（GD32A7xx）：
 *   - ADC_CH_IN12 : PH8 / ADC0_IN12
 *   - ADC_CH_IN13 : PH7 / ADC0_IN13
 *
 * 注意：
 *   - 增删通道时，需同步修改 adc_manager.c 中的硬件配置表；
 *   - 业务逻辑命名（如 GAS_SENSOR、COOLER_CURRENT）应在 BSW/EcuAL 层定义。
 */
typedef enum {
    ADC_CH_IN12 = 0U,   /* PH8 / ADC0_IN12 */
    ADC_CH_IN13,        /* PH7 / ADC0_IN13 */
    ADC_CH_MAX          /* 通道总数（边界标识） */
} adc_channel_t;

/*
 * ADC 通道到硬件资源的映射配置结构体。
 * 说明：本结构体主要供模块内部配置表使用，放在头文件便于类型复用。
 */
typedef struct {
    adc_channel_t channel;     /* 硬件通道 ID（adc_channel_t） */
    uint32_t gpio_rcu;         /* GPIO 时钟门控 ID（RCU_GPIOx） */
    uint32_t gpio_port;        /* GPIO 端口基址（GPIOx） */
    uint32_t gpio_pin;         /* GPIO 引脚掩码（GPIO_PIN_x） */
    uint32_t adc_channel;      /* ADC 硬件通道号 */
    uint32_t sample_time;      /* ADC 采样时间配置值（厂商库编码） */
    uint8_t routine_rank;      /* 常规序列 Rank（顺序号，从 0 开始） */
} adc_channel_cfg_t;

/*
 * 函数名称 : adc_manager_init
 * 功能描述 : 初始化 ADC 管理模块与底层硬件资源（GPIO/ADC/校准）。
 * 输入参数 : 无。
 * 输出参数 : 无。
 * 返 回 值 : 无。
 * 调用时机 :
 *   - 系统上电初始化阶段调用一次；
 *   - 接口内部具备重复调用保护。
 */
void adc_manager_init(void);

/*
 * 函数名称 : adc_manager_read_raw
 * 功能描述 : 读取指定硬件通道的 ADC 原始 12bit 码值。
 * 输入参数 :
 *   - channel   : 硬件通道 ID（ADC_CH_INxx）。
 * 输出参数 :
 *   - raw_12bit : 输出原始码值，单位 LSB，范围 0~4095。
 * 返 回 值 :
 *   - 1U : 成功；
 *   - 0U : 失败（未初始化、参数非法、通道非法或转换超时）。
 */
uint8_t adc_manager_read_raw(adc_channel_t channel, uint16_t *raw_12bit);

/*
 * 函数名称 : adc_manager_read_mv
 * 功能描述 : 读取指定硬件通道并按参考电压换算输入电压（mV）。
 * 输入参数 :
 *   - channel : 硬件通道 ID（ADC_CH_INxx）；
 *   - vref_mv : ADC 参考电压，单位 mV（典型值 3300）。
 * 输出参数 :
 *   - mv      : 输出电压值，单位 mV。
 * 返 回 值 :
 *   - 1U : 成功；
 *   - 0U : 失败（参数非法或底层读取失败）。
 * 换算关系 :
 *   - mv = raw_12bit * vref_mv / 4095
 */
uint8_t adc_manager_read_mv(adc_channel_t channel, uint16_t vref_mv, uint16_t *mv);

#ifdef __cplusplus
}
#endif

#endif /* ADC_MANAGER_H */
