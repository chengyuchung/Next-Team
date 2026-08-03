#include "adc_manager.h"

#include "gd32a7xx_adc.h"
#include "gd32a7xx_gpio.h"
#include "gd32a7xx_rcu.h"

/*
 * ============================================================================
 * 模块名称 : adc_manager
 * 文件功能 : ADC 统一采样管理（单次触发、轮询取数）
 *
 * 设计目标 :
 *   1) 统一初始化 ADC0 与对应模拟输入 GPIO；
 *   2) 通过“逻辑通道”读取 12bit 原始码值；
 *   3) 支持按参考电压换算 mV；
 *   4) 初始化失败不阻塞主流程，任务可继续运行。
 * ============================================================================
 */

/* ========================================================================== */
/* 配置常量                                                                 */
/* ========================================================================== */

#ifndef ADC_MANAGER_TIMEOUT
#define ADC_MANAGER_TIMEOUT                 100000U
#endif

#ifndef ADC_MANAGER_CHANNEL_COUNT
#define ADC_MANAGER_CHANNEL_COUNT           4U
#endif

#ifndef ADC_MANAGER_SAMPLE_TIME_DEFAULT
/* 采样时间 = 638 cycles × (1/6MHz) ≈ 106.3 μs。
 * 外部电路：R2(33Ω) + VR1(最大500Ω) = 533Ω，串联 C7(10nF) 到 GND。
 * RC 常数 τ = 533Ω × 10nF = 5.33 μs。
 * 638 cycles 充电比例 = 1 - e^(-106.3/5.33) ≈ 99.9999%，满足 12bit 精度。
 * GD32A7xx ADC_RCFG_RSMP 位域范围 0~638。 */
#define ADC_MANAGER_SAMPLE_TIME_DEFAULT     638U
#endif

/* ========================================================================== */
/* 模块状态                                                                  */
/* ========================================================================== */

static uint8_t s_inited = 0U;

/* 逻辑通道 -> 硬件资源映射表。
 * 历史说明：原 MQ9_GAS 通道（PE5/ADC ch4/rank 0）已迁至 DO 数字输入，移除该行后需同步减小
 *           ADC_MANAGER_CHANNEL_COUNT，避免循环越界读到相邻内存。 */
static const adc_manager_channel_cfg_t s_cfg[ADC_MANAGER_CHANNEL_COUNT] = {
    {ADC_MANAGER_CH_FAN_CURRENT,    RCU_GPIOE, GPIOE, GPIO_PIN_6,  3U,  ADC_MANAGER_SAMPLE_TIME_DEFAULT, 0U},
    {ADC_MANAGER_CH_PUMP_CURRENT,   RCU_GPIOB, GPIOB, GPIO_PIN_11, 15U, ADC_MANAGER_SAMPLE_TIME_DEFAULT, 1U},
    {ADC_MANAGER_CH_COOLER_CURRENT, RCU_GPIOH, GPIOH, GPIO_PIN_7,  13U, ADC_MANAGER_SAMPLE_TIME_DEFAULT, 2U},
    {ADC_MANAGER_CH_GATE_CURRENT,   RCU_GPIOH, GPIOH, GPIO_PIN_8,  12U, ADC_MANAGER_SAMPLE_TIME_DEFAULT, 3U}
};

/* ========================================================================== */
/* 内部工具函数                                                              */
/* ========================================================================== */

static const adc_manager_channel_cfg_t *adc_manager_find(adc_manager_channel_t channel)
{
    uint32_t i;

    for(i = 0U; i < ADC_MANAGER_CHANNEL_COUNT; i++) {
        if(s_cfg[i].channel == channel) {
            return &s_cfg[i];
        }
    }

    return NULL;
}

static void adc_manager_gpio_init_one(const adc_manager_channel_cfg_t *cfg)
{
    if(cfg == NULL) {
        return;
    }

    rcu_periph_clock_enable(cfg->gpio_rcu);
    gpio_mode_set(cfg->gpio_port, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, cfg->gpio_pin);
}

static void adc_manager_apply_common_config(void)
{
    adc_mode_config(ADC_MODE_FREE);
    adc_data_alignment_config(ADC0, ADC_DATAALIGN_RIGHT);
    adc_resolution_config(ADC0, ADC_RESOLUTION_12B);

    /* 官方库要求：先配序列长度，再配每个 Rank。 */
    adc_channel_length_config(ADC0, ADC_ROUTINE_SEQUENCE, ADC_MANAGER_CHANNEL_COUNT);
}

static void adc_manager_apply_channel_config(void)
{
    uint32_t i;
    const adc_manager_channel_cfg_t *cfg;

    for(i = 0U; i < ADC_MANAGER_CHANNEL_COUNT; i++) {
        cfg = &s_cfg[i];
        adc_manager_gpio_init_one(cfg);
        adc_sequence_channel_config(ADC0,
                                    ADC_ROUTINE_SEQUENCE,
                                    cfg->routine_rank,
                                    cfg->adc_channel,
                                    cfg->sample_time);
    }
}

static void adc_manager_apply_calibration(void)
{
    /* 偏移校准可提升静态精度。 */
    adc_calibration_mode_config(ADC0, ADC_CALIBRATION_OFFSET);
    (void)adc_calibration_enable(ADC0);
}

/* ========================================================================== */
/* 对外接口                                                                  */
/* ========================================================================== */

void adc_manager_init(void)
{
    if(s_inited != 0U) {
        return;
    }

    /* ADC0 外设时钟使能。必须在调用 rcu_adc_clock_config 之前使能。 */
    rcu_periph_clock_enable(RCU_ADC0);

    /* 配置 ADC 时钟源与预分频。
     * 参考手册建议：f_ADC 推荐 16MHz，最低 1MHz，最高 60MHz（保证精度）。
     * 系统时钟源为 RCU_CKSYSSRC_IRC48M（48MHz），HCLK = 48MHz。
     * 取 HCLK / 8 = 6MHz，在允许范围内（满足 1~16MHz），虽低于推荐值 16MHz，
     *   但更低的 f_ADC 有利于提升采样精度。
     * 若需要接近 16MHz，可改为切换到 PLL 时钟源。
     *   - RCU_ADCSRC_HCLK : HCLK（48MHz）
     *   - RCU_ADCSRC_SYS  : CK_SYS（48MHz）
     *   - RCU_ADCSRC_PLLP : PLL P 分频（可提供更高频率）
     */
    rcu_adc_clock_config(RCU_ADCSRC_HCLK, RCU_CKADC_DIV8);

    adc_deinit(ADC0);

    adc_manager_apply_common_config();
    adc_manager_apply_channel_config();

    /* 单次转换模式：每次软件触发执行一次常规序列转换。 */
    adc_routine_sequence_conversion_mode_config(ADC0, ADC_ONE_SHOT_MODE);

    adc_manager_apply_calibration();

    adc_enable(ADC0);
    s_inited = 1U;
}

uint8_t adc_manager_read_raw(adc_manager_channel_t channel, uint16_t *raw_12bit)
{
    uint32_t timeout = ADC_MANAGER_TIMEOUT;
    const adc_manager_channel_cfg_t *cfg;

    if((s_inited == 0U) || (raw_12bit == NULL)) {
        return 0U;
    }

    cfg = adc_manager_find(channel);
    if(cfg == NULL) {
        return 0U;
    }

    adc_flag_clear(ADC0, ADC_FLAG_EORC);
    adc_sequence_software_trigger_enable(ADC0, ADC_ROUTINE_SEQUENCE);

    while((adc_flag_get(ADC0, ADC_FLAG_EORC) == RESET) && (timeout != 0U)) {
        timeout--;
    }

    if(timeout == 0U) {
        return 0U;
    }

    *raw_12bit = adc_sequence_data_read(ADC0, ADC_ROUTINE_SEQUENCE) & 0x0FFFU;
    (void)cfg;
    return 1U;
}

uint8_t adc_manager_read_mv(adc_manager_channel_t channel, uint16_t vref_mv, uint16_t *mv)
{
    uint16_t raw;
    uint32_t value_mv;

    if((mv == NULL) || (vref_mv == 0U)) {
        return 0U;
    }

    if(adc_manager_read_raw(channel, &raw) == 0U) {
        return 0U;
    }

    value_mv = ((uint32_t)raw * (uint32_t)vref_mv) / 4095U;
    *mv = (uint16_t)value_mv;
    return 1U;
}
