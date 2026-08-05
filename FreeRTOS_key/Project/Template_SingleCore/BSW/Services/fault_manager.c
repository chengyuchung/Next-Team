#include "fault_manager.h"
#include "system_state.h"
#include "adc_ecual.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : fault_manager
 * 文件功能 : 执行器故障检测与故障码管理实现
 *
 * 设计目标 :
 *   1) 监测制冷片的单路电流（PH7 / ADC0_IN13）；
 *   2) 通过"连续异常计数"的方式降低瞬时抖动和误判；
 *   3) 为系统提供统一、稳定的故障状态输出。
 *
 * 设计说明 :
 *   - 制冷片电流监测 : PH7 / ADC0_IN13（单路电流，非4路总和）
 *   - 加热片电流监测 : 硬件未接入，暂不支持故障检测
 *   - PH8 / ADC0_IN12 为气体传感器模拟量输入，不用于电流检测
 *   - 未使能时直接认为正常；
 *   - 使能后基于 ADC 原始值窗口判断，并采用连续异常计数确认。
 * ============================================================================
 */

/*
 * 执行器故障确认阈值：
 * 连续异常达到该次数后，才真正置位对应故障位。
 * 这样可以过滤偶发采样毛刺或单次抖动。
 */
#ifndef FAULT_CURRENT_SAMPLE_COUNT
#define FAULT_CURRENT_SAMPLE_COUNT 3U
#endif

/*
 * 0A 基准自学习参数
 */
#ifndef FAULT_BASELINE_LEARN_COUNT
#define FAULT_BASELINE_LEARN_COUNT 10U
#endif

#ifndef FAULT_BASELINE_MARGIN
#define FAULT_BASELINE_MARGIN 50U
#endif

#ifndef FAULT_BASELINE_MAX_RAW
#define FAULT_BASELINE_MAX_RAW 4095U
#endif

/*
 * 模块内部状态：
 * s_status 保存最终对外输出的故障状态；
 * 其余计数器用于各通道的连续异常统计。
 */
static fault_manager_status_t s_status;
static uint8_t s_cooler_fault_count;

/*
 * 0A 基准自学习状态
 *   系统上电后，对制冷片电流采样 FAULT_BASELINE_LEARN_COUNT 次，
 *   取平均作为该通道的 0A 偏置 raw。
 *   之后用 (基准 + FAULT_BASELINE_MARGIN) 作为"有电流"判定的最小阈值。
 *   
 *   注意：加热片电流硬件未接入，不进行自学习。
 */
static uint16_t s_baseline_cooler_raw = 0U;
static uint32_t s_baseline_acc_cooler = 0U;
static uint16_t s_baseline_samples    = 0U;
static uint8_t  s_baseline_learned    = 0U;

/*
 * 函数名称 : fault_manager_get_threshold
 * 功能描述 : 获取某通道动态计算后的故障判定阈值（基准 + 裕量）。
 * 输入参数 : baseline - 该通道已学习到的 0A 基准 raw。
 * 返回值   : 用于判定的下限阈值。
 */
static uint16_t fault_manager_get_threshold(uint16_t baseline)
{
    uint32_t thr = (uint32_t)baseline + (uint32_t)FAULT_BASELINE_MARGIN;
    if(thr > FAULT_BASELINE_MAX_RAW) {
        thr = FAULT_BASELINE_MAX_RAW;
    }
    return (uint16_t)thr;
}

/*
 * 函数名称 : fault_manager_learn_baseline
 * 功能描述 : 在系统上电、执行器未使能时累积 ADC 原始值，
 *           用于估算制冷片电流传感器的 0A 偏置。
 * 说明     :
 *   - 每调用一次，对制冷片通道采样一次并累加；
 *   - 达到 FAULT_BASELINE_LEARN_COUNT 次后取平均；
 *   - 学习期间不输出故障，避免被误判。
 *   - 加热片电流硬件未接入，不进行学习。
 */
static void fault_manager_learn_baseline(void)
{
    uint16_t raw = 0U;

    if(s_baseline_learned != 0U) {
        return;
    }

    if(adc_ecual_read_raw(ADC_ECUAL_CH_COOLER_CURRENT, &raw) != 0U) {
        s_baseline_acc_cooler += raw;
    }

    s_baseline_samples++;
    if(s_baseline_samples >= FAULT_BASELINE_LEARN_COUNT) {
        s_baseline_cooler_raw = (uint16_t)(s_baseline_acc_cooler / FAULT_BASELINE_LEARN_COUNT);
        s_baseline_learned    = 1U;
    }
}

/*
 * 函数名称 : fault_manager_init
 * 功能描述 : 初始化故障管理模块。
 */
void fault_manager_init(void)
{
    fault_manager_reset();
}

/*
 * 函数名称 : fault_manager_reset
 * 功能描述 : 清空所有故障状态和内部计数器。
 */
void fault_manager_reset(void)
{
    memset(&s_status, 0, sizeof(s_status));
    s_cooler_fault_count = 0U;
    s_baseline_cooler_raw = 0U;
    s_baseline_acc_cooler = 0U;
    s_baseline_samples    = 0U;
    s_baseline_learned    = 0U;
}

/*
 * 函数名称 : fault_manager_get_act_fault
 * 功能描述 : 获取执行器的故障状态。
 * 输入参数 :
 *   - heater_fault : 加热片故障输出指针（硬件未接入，始终输出 0）
 *   - cooler_fault : 制冷片故障输出指针（PH7/ADC0_IN13单路电流）
 * 说明     :
 *   - 函数内部先读取状态机输出，判断执行器是否使能；
 *   - 未使能时直接输出 0U，并清零对应连续异常计数；
 *   - 使能时读取 ADC 原始值，沿用"连续多次异常才判故障"的逻辑。
 *   - 加热片电流硬件未接入，heater_fault 始终输出 0。
 */
void fault_manager_get_act_fault(uint8_t *heater_fault, uint8_t *cooler_fault)
{
    system_state_status_t status;
    uint16_t raw = 0U;
    uint8_t any_cooler_enabled;
    uint8_t any_enabled;

    system_state_get_status(&status);

    /* 计算制冷片的使能状态（任意一路使能即为使能） */
    any_cooler_enabled = (uint8_t)(status.cooler_enable[0] | status.cooler_enable[1] |
                                   status.cooler_enable[2] | status.cooler_enable[3]);
    any_enabled = any_cooler_enabled;

    /*
     * 0A 基准自学习期：
     *   - 制冷片未使能时，每次调用都对制冷片通道采样并累计；
     *   - 累计满 FAULT_BASELINE_LEARN_COUNT 次后取平均，得到 0A 偏置；
     *   - 自学习期间所有故障输出 0（认为系统正常，不报故障）。
     */
    if(s_baseline_learned == 0U) {
        if(any_enabled == 0U) {
            fault_manager_learn_baseline();
            if(heater_fault != NULL) { *heater_fault = 0U; }
            if(cooler_fault != NULL) { *cooler_fault = 0U; }
            return;
        }
        /* 执行器已经使能但自学习还没完成 → 用当前单次值兜底，立即结束学习 */
        if(adc_ecual_read_raw(ADC_ECUAL_CH_COOLER_CURRENT, &raw) == 0U) { raw = 0U; }
        s_baseline_cooler_raw = raw;
        s_baseline_learned = 1U;
    }

    /* 加热片故障检测：硬件未接入，始终输出 0 */
    if(heater_fault != NULL) {
        *heater_fault = 0U;
    }

    /* 制冷片故障检测（单路电流） */
    if(cooler_fault != NULL) {
        if(any_cooler_enabled == 0U) {
            s_cooler_fault_count = 0U;
            *cooler_fault = 0U;
        } else if(adc_ecual_read_raw(ADC_ECUAL_CH_COOLER_CURRENT, &raw) != 0U) {
            if(raw >= fault_manager_get_threshold(s_baseline_cooler_raw)) {
                s_cooler_fault_count = 0U;
                *cooler_fault = 0U;
            } else {
                if(s_cooler_fault_count < 255U) {
                    s_cooler_fault_count++;
                }
                *cooler_fault = (s_cooler_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
            }
        } else {
            /* ADC读取失败也视为异常 */
            if(s_cooler_fault_count < 255U) {
                s_cooler_fault_count++;
            }
            *cooler_fault = (s_cooler_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
        }
    }
}

/*
 * 函数名称 : fault_manager_get_status
 * 功能描述 : 获取当前所有故障状态快照。
 * 输入参数 :
 *   - status : 输出指针，非 NULL 时写入当前故障状态。
 */
void fault_manager_get_status(fault_manager_status_t *status)
{
    if(status != NULL) {
        *status = s_status;
    }
}
