#include "adc_manager.h"

#include "gd32a7xx_adc.h"
#include "gd32a7xx_gpio.h"
#include "gd32a7xx_rcu.h"

#include "FreeRTOS.h"
#include "task.h"

/*
 * ============================================================================
 * 模块名称 : adc_manager
 * 文件功能 : ADC 统一采样管理（单次触发、轮询取数）
 *
 * 设计目标 :
 *   1) 统一初始化 ADC0 与对应模拟输入 GPIO；
 *   2) 通过"硬件通道号"读取 12bit 原始码值；
 *   3) 支持按参考电压换算 mV；
 *   4) 初始化失败不阻塞主流程，任务可继续运行。
 *
 * 解耦原则 :
 *   - 本模块只知道硬件通道号（ADC_CH_INxx），不包含业务含义；
 *   - 业务逻辑到硬件通道的映射由 BSW/EcuAL 层负责。
 * ============================================================================
 */

/* ========================================================================== */
/* 配置常量                                                                 */
/* ========================================================================== */

#ifndef ADC_MANAGER_TIMEOUT
#define ADC_MANAGER_TIMEOUT                 100000U
#endif

#ifndef ADC_MANAGER_CHANNEL_COUNT
#define ADC_MANAGER_CHANNEL_COUNT           2U
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
static uint8_t s_calibration_failed = 0U;

/* 硬件通道配置表（ADC_CH_INxx -> GPIO + ADC 硬件资源）
 * 
 * 硬件映射（2026-08-05 解耦版本）：
 *   - ADC_CH_IN12 : PH8 / ADC0_IN12
 *   - ADC_CH_IN13 : PH7 / ADC0_IN13
 *
 * 业务含义由 BSW/EcuAL 层定义，MCAL 层不关心具体应用。
 */
static const adc_channel_cfg_t s_cfg[ADC_MANAGER_CHANNEL_COUNT] = {
    {ADC_CH_IN12, RCU_GPIOH, GPIOH, GPIO_PIN_8, 12U, ADC_MANAGER_SAMPLE_TIME_DEFAULT, 0U},  /* PH8 - ADC0_IN12 */
    {ADC_CH_IN13, RCU_GPIOH, GPIOH, GPIO_PIN_7, 13U, ADC_MANAGER_SAMPLE_TIME_DEFAULT, 1U}   /* PH7 - ADC0_IN13 */
};

/* ========================================================================== */
/* 内部工具函数                                                              */
/* ========================================================================== */

static const adc_channel_cfg_t *adc_manager_find(adc_channel_t channel)
{
    uint32_t i;

    for(i = 0U; i < ADC_MANAGER_CHANNEL_COUNT; i++) {
        if(s_cfg[i].channel == channel) {
            return &s_cfg[i];
        }
    }

    return NULL;
}

static void adc_manager_gpio_init_one(const adc_channel_cfg_t *cfg)
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
    const adc_channel_cfg_t *cfg;

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

static uint8_t adc_manager_apply_calibration(void)
{
    /* 偏移校准可提升静态精度。调用前必须已 adc_enable() 并稳定，
     * 否则 adc_calibration_enable() 会长时间轮询超时（见 adc_manager_init）。
     * 校准次数与官方 07_ADC0_ADC1_Routine_Parallel_mode demo（同芯片系列）
     * 保持一致，取 7 次以提升校准结果稳定性。 */
    adc_calibration_mode_config(ADC0, ADC_CALIBRATION_OFFSET);
    adc_calibration_number(ADC0, ADC_CALIBRATION_NUM7);
    return adc_calibration_enable(ADC0);
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
     * 本工程系统时钟为 160MHz PLL（见 system_gd32a71xx_a74xx.c 中
     * __SYSTEM_CLOCK_160M_PLL_HXTAL，AHB 分频 DIV1），即 HCLK = 160MHz。
     * 取 HCLK / 10 = 16MHz，正好落在推荐值，与官方 07_ADC0_ADC1_Routine_
     * Parallel_mode demo（同为 160MHz 主频）使用的分频一致。
     *   - RCU_ADCSRC_HCLK : HCLK（160MHz）
     *   - RCU_ADCSRC_SYS  : CK_SYS（160MHz）
     *   - RCU_ADCSRC_PLLP : PLL P 分频（可提供更高频率）
     */
    rcu_adc_clock_config(RCU_ADCSRC_HCLK, RCU_CKADC_DIV10);

    adc_deinit(ADC0);

    adc_manager_apply_common_config();
    adc_manager_apply_channel_config();

    /* 单次转换模式：每次软件触发执行一次常规序列转换。 */
    adc_routine_sequence_conversion_mode_config(ADC0, ADC_ONE_SHOT_MODE);

    /* 关键顺序（参考官方 06_ADC_Temperature_Vrefint /
     * 07_ADC0_ADC1_Routine_Parallel_mode demo）：
     * 必须先 adc_enable() 让 ADC 模拟部分上电，稳定一小段时间后才能校准。
     * 之前的实现在 adc_enable() 之前就调用校准，此时 ADCON 尚未置位，
     * 校准的 RSTCLB/CLB 硬件位可能永远不会被清零，adc_calibration_enable()
     * 内部的超时轮询（约 1600 万次循环）因此长时间空转，
     * 这就是之前观察到的"上电卡死"现象的根因。 */
    adc_enable(ADC0);

    /* 等待 ADC 模拟部分稳定。init_task 在 vTaskStartScheduler() 之后运行，
     * tick 已经启动，用 vTaskDelay() 让出 CPU 而不是裸自旋。 */
    vTaskDelay(pdMS_TO_TICKS(1U));

    if(adc_manager_apply_calibration() == 0U) {
        /* 校准失败：ADC 仍可用，但精度无法保证，记录状态供上层排查。 */
        s_calibration_failed = 1U;
    }

    s_inited = 1U;
}

uint8_t adc_manager_read_raw(adc_channel_t channel, uint16_t *raw_12bit)
{
    uint32_t timeout = ADC_MANAGER_TIMEOUT;
    const adc_channel_cfg_t *cfg;

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

uint8_t adc_manager_read_mv(adc_channel_t channel, uint16_t vref_mv, uint16_t *mv)
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

uint8_t adc_manager_calibration_ok(void)
{
    return (s_calibration_failed == 0U) ? 1U : 0U;
}
