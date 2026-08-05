#include "adc_ecual.h"
#include "adc_manager.h"

/*
 * ============================================================================
 * 模块名称 : adc_ecual
 * 文件功能 : ADC EcuAL 层实现 - 业务逻辑到硬件通道的映射
 * ============================================================================
 */

/*
 * 业务逻辑通道到硬件通道的映射表
 *
 * 硬件映射（GD32A7xx）：
 *   - ADC_ECUAL_CH_GAS_SENSOR      → ADC_CH_IN12 (PH8)
 *   - ADC_ECUAL_CH_COOLER_CURRENT  → ADC_CH_IN13 (PH7)
 *
 * 修改说明：
 *   - 如果硬件接线变更，只需修改此映射表，应用层代码无需改动；
 *   - MCAL 层也无需改动，保持硬件抽象的稳定性。
 */
typedef struct {
    adc_ecual_channel_t ecual_channel;  /* 业务逻辑通道 */
    adc_channel_t       hw_channel;     /* 硬件通道 */
} adc_ecual_mapping_t;

static const adc_ecual_mapping_t s_mapping[] = {
    {ADC_ECUAL_CH_GAS_SENSOR,     ADC_CH_IN12},  /* 气体传感器 -> PH8/ADC0_IN12 */
    {ADC_ECUAL_CH_COOLER_CURRENT, ADC_CH_IN13}   /* 制冷片电流 -> PH7/ADC0_IN13 */
};

#define ADC_ECUAL_MAPPING_COUNT (sizeof(s_mapping) / sizeof(s_mapping[0]))

/*
 * 内部函数：查找业务通道对应的硬件通道
 */
static uint8_t adc_ecual_find_hw_channel(adc_ecual_channel_t channel, adc_channel_t *hw_channel)
{
    uint32_t i;

    if(hw_channel == NULL) {
        return 0U;
    }

    for(i = 0U; i < ADC_ECUAL_MAPPING_COUNT; i++) {
        if(s_mapping[i].ecual_channel == channel) {
            *hw_channel = s_mapping[i].hw_channel;
            return 1U;
        }
    }

    return 0U;
}

/*
 * 对外接口实现
 */
uint8_t adc_ecual_read_raw(adc_ecual_channel_t channel, uint16_t *raw_12bit)
{
    adc_channel_t hw_channel;

    if(raw_12bit == NULL) {
        return 0U;
    }

    if(adc_ecual_find_hw_channel(channel, &hw_channel) == 0U) {
        return 0U;
    }

    return adc_manager_read_raw(hw_channel, raw_12bit);
}

uint8_t adc_ecual_read_mv(adc_ecual_channel_t channel, uint16_t vref_mv, uint16_t *mv)
{
    adc_channel_t hw_channel;

    if(mv == NULL) {
        return 0U;
    }

    if(adc_ecual_find_hw_channel(channel, &hw_channel) == 0U) {
        return 0U;
    }

    return adc_manager_read_mv(hw_channel, vref_mv, mv);
}
