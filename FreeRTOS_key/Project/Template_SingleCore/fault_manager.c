#include "fault_manager.h"
#include "system_state.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : fault_manager
 * 文件功能 : 执行器故障检测与故障码管理实现
 *
 * 设计目标 :
 *   1) 统一维护四路执行器电流故障状态；
 *   2) 通过“连续异常计数”的方式降低瞬时抖动和误判；
 *   3) 为 CAN 故障帧提供统一、稳定的故障状态输出。
 *
 * 设计说明 :
 *   - 仅保留执行器过流/异常检测逻辑；
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
 * 模块内部状态：
 * s_status 保存最终对外输出的故障状态；
 * 其余数组/计数器用于各通道的连续异常统计。
 */
static fault_manager_status_t s_status;
static uint8_t s_fan_current_fault_count;
static uint8_t s_pump_current_fault_count;
static uint8_t s_cooler_current_fault_count;
static uint8_t s_gate_current_fault_count;

/*
 * 0A 基准自学习状态
 *   系统上电后，对 4 路执行器各采样 FAULT_BASELINE_LEARN_COUNT 次，
 *   取平均作为该通道的 0A 偏置 raw。
 *   之后用 (基准 + FAULT_BASELINE_MARGIN) 作为"有电流"判定的最小阈值。
 *   s_baseline_learned 在采集完成后置 1，启用自学习阈值。
 *   注意事项：
 *     - 自学习必须在外围执行器板通电**之前**完成（即执行器未工作时），
 *       任何使能标志被置位前都视为"安全学习期"；
 *     - 如果某通道一直使能，会跳过学习，阈值维持默认值。
 */
static uint16_t s_baseline_fan_raw   = 0U;
static uint16_t s_baseline_pump_raw  = 0U;
static uint16_t s_baseline_cooler_raw= 0U;
static uint16_t s_baseline_gate_raw  = 0U;
static uint32_t s_baseline_acc_fan   = 0U;
static uint32_t s_baseline_acc_pump  = 0U;
static uint32_t s_baseline_acc_cooler= 0U;
static uint32_t s_baseline_acc_gate  = 0U;
static uint16_t s_baseline_samples   = 0U;
static uint8_t  s_baseline_learned   = 0U;

/*
 * 函数名称 : fault_manager_get_threshold
 * 功能描述 : 获取某通道动态计算后的故障判定阈值（基准 + 裕量）。
 * 输入参数 : baseline - 该通道已学习到的 0A 基准 raw。
 * 返回值   : 用于判定的下限阈值；若基准未学习成功，则使用原始宏定义。
 * 说明     : 该函数只在自学习完成后被调用，逻辑简单但集中，方便调整。
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
 * 功能描述 : 在系统上电、外围执行器未使能时累积 ADC 原始值，
 *           用于估算 4 路 ACS712 的 0A 偏置。
 * 说明     :
 *   - 每调用一次，对 4 通道各采样一次并累加；
 *   - 达到 FAULT_BASELINE_LEARN_COUNT 次后取平均，写入 s_baseline_*_raw；
 *   - 学习期间不输出故障，避免被误判；
 *   - 该函数只读不写，调用方需保证执行器都未使能。
 */
static void fault_manager_learn_baseline(void)
{
    uint16_t raw = 0U;

    if(s_baseline_learned != 0U) {
        return;
    }

    if(adc_manager_read_raw(ADC_MANAGER_CH_FAN_CURRENT,    &raw) != 0U) {
        s_baseline_acc_fan += raw;
    }
    if(adc_manager_read_raw(ADC_MANAGER_CH_PUMP_CURRENT,   &raw) != 0U) {
        s_baseline_acc_pump += raw;
    }
    if(adc_manager_read_raw(ADC_MANAGER_CH_COOLER_CURRENT, &raw) != 0U) {
        s_baseline_acc_cooler += raw;
    }
    if(adc_manager_read_raw(ADC_MANAGER_CH_GATE_CURRENT,   &raw) != 0U) {
        s_baseline_acc_gate += raw;
    }

    s_baseline_samples++;
    if(s_baseline_samples >= FAULT_BASELINE_LEARN_COUNT) {
        s_baseline_fan_raw    = (uint16_t)(s_baseline_acc_fan    / FAULT_BASELINE_LEARN_COUNT);
        s_baseline_pump_raw   = (uint16_t)(s_baseline_acc_pump   / FAULT_BASELINE_LEARN_COUNT);
        s_baseline_cooler_raw = (uint16_t)(s_baseline_acc_cooler / FAULT_BASELINE_LEARN_COUNT);
        s_baseline_gate_raw   = (uint16_t)(s_baseline_acc_gate   / FAULT_BASELINE_LEARN_COUNT);
        s_baseline_learned    = 1U;
    }
}

/*
 * 函数名称 : fault_manager_init
 * 功能描述 : 初始化故障管理模块。
 * 说明     : 当前实现直接复位全部故障状态与计数器，确保上电后处于干净状态。
 */
void fault_manager_init(void)
{
    fault_manager_reset();
}

/*
 * 函数名称 : fault_manager_reset
 * 功能描述 : 清空所有故障状态和内部计数器。
 * 说明     :
 *   - 清空 s_status，保证所有故障位恢复为 0；
 *   - 清空各通道连续失败计数，避免旧故障在复位后残留；
 *   - 该函数适合在系统初始化、故障恢复或重新进入运行前调用。
 */
void fault_manager_reset(void)
{
    memset(&s_status, 0, sizeof(s_status));
    s_fan_current_fault_count = 0U;
    s_pump_current_fault_count = 0U;
    s_cooler_current_fault_count = 0U;
    s_gate_current_fault_count = 0U;
    s_baseline_fan_raw    = 0U;
    s_baseline_pump_raw   = 0U;
    s_baseline_cooler_raw = 0U;
    s_baseline_gate_raw   = 0U;
    s_baseline_acc_fan    = 0U;
    s_baseline_acc_pump   = 0U;
    s_baseline_acc_cooler = 0U;
    s_baseline_acc_gate   = 0U;
    s_baseline_samples    = 0U;
    s_baseline_learned    = 0U;
}

/*
 * 函数名称 : fault_manager_get_act_fault
 * 功能描述 : 获取四路执行器的故障状态。
 * 输入参数 :
 *   - fan_fault    : 风扇故障输出指针；
 *   - pump_fault   : 水泵故障输出指针；
 *   - cooler_fault : 制冷片故障输出指针；
 *   - gate_fault   : 排气阀故障输出指针。
 * 说明     :
 *   - 函数内部先读取状态机输出，判断四路执行器是否使能；
 *   - 未使能时直接输出 0U，并清零对应连续异常计数；
 *   - 使能时读取 ADC 原始值，沿用“连续多次异常才判故障”的逻辑。
 */
void fault_manager_get_act_fault(uint8_t *fan_fault, uint8_t *pump_fault, uint8_t *cooler_fault, uint8_t *gate_fault)
{
    system_state_status_t status;
    uint16_t raw = 0U;
    uint8_t  any_enabled;

    system_state_get_status(&status);

    /*
     * 0A 基准自学习期：
     *   - 4 路执行器全部未使能时，每次调用都对 4 通道采样并累计；
     *   - 累计满 FAULT_BASELINE_LEARN_COUNT 次后取平均，得到 0A 偏置；
     *   - 自学习期间所有故障输出 0（认为系统正常，不报故障）。
     */
    any_enabled = (uint8_t)(status.fan_enable | status.pump_enable |
                            status.cooling_enable | status.gate_enable);
    if(s_baseline_learned == 0U) {
        if(any_enabled == 0U) {
            fault_manager_learn_baseline();
            if(fan_fault    != NULL) { *fan_fault    = 0U; }
            if(pump_fault   != NULL) { *pump_fault   = 0U; }
            if(cooler_fault != NULL) { *cooler_fault = 0U; }
            if(gate_fault   != NULL) { *gate_fault   = 0U; }
            return;
        }
        /* 执行器已经使能但自学习还没完成 → 用当前单次值兜底，立即结束学习 */
        if(adc_manager_read_raw(ADC_MANAGER_CH_FAN_CURRENT,    &raw) == 0U) { raw = 0U; }
        s_baseline_fan_raw = raw;
        if(adc_manager_read_raw(ADC_MANAGER_CH_PUMP_CURRENT,   &raw) == 0U) { raw = 0U; }
        s_baseline_pump_raw = raw;
        if(adc_manager_read_raw(ADC_MANAGER_CH_COOLER_CURRENT, &raw) == 0U) { raw = 0U; }
        s_baseline_cooler_raw = raw;
        if(adc_manager_read_raw(ADC_MANAGER_CH_GATE_CURRENT,   &raw) == 0U) { raw = 0U; }
        s_baseline_gate_raw = raw;
        s_baseline_learned  = 1U;
    }

    if(fan_fault != NULL) {
        if(status.fan_enable == 0U) {
            s_fan_current_fault_count = 0U;
            *fan_fault = 0U;
        } else if(adc_manager_read_raw(ADC_MANAGER_CH_FAN_CURRENT, &raw) != 0U) {
            if(raw >= fault_manager_get_threshold(s_baseline_fan_raw)) {
                s_fan_current_fault_count = 0U;
                *fan_fault = 0U;
            } else {
                if(s_fan_current_fault_count < 255U) {
                    s_fan_current_fault_count++;
                }
                *fan_fault = (s_fan_current_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
            }
        } else {
            if(s_fan_current_fault_count < 255U) {
                s_fan_current_fault_count++;
            }
            *fan_fault = (s_fan_current_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
        }
    }

    if(pump_fault != NULL) {
        if(status.pump_enable == 0U) {
            s_pump_current_fault_count = 0U;
            *pump_fault = 0U;
        } else if(adc_manager_read_raw(ADC_MANAGER_CH_PUMP_CURRENT, &raw) != 0U) {
            if(raw >= fault_manager_get_threshold(s_baseline_pump_raw)) {
                s_pump_current_fault_count = 0U;
                *pump_fault = 0U;
            } else {
                if(s_pump_current_fault_count < 255U) {
                    s_pump_current_fault_count++;
                }
                *pump_fault = (s_pump_current_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
            }
        } else {
            if(s_pump_current_fault_count < 255U) {
                s_pump_current_fault_count++;
            }
            *pump_fault = (s_pump_current_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
        }
    }

    if(cooler_fault != NULL) {
        if(status.cooling_enable == 0U) {
            s_cooler_current_fault_count = 0U;
            *cooler_fault = 0U;
        } else if(adc_manager_read_raw(ADC_MANAGER_CH_COOLER_CURRENT, &raw) != 0U) {
            if(raw >= fault_manager_get_threshold(s_baseline_cooler_raw)) {
                s_cooler_current_fault_count = 0U;
                *cooler_fault = 0U;
            } else {
                if(s_cooler_current_fault_count < 255U) {
                    s_cooler_current_fault_count++;
                }
                *cooler_fault = (s_cooler_current_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
            }
        } else {
            if(s_cooler_current_fault_count < 255U) {
                s_cooler_current_fault_count++;
            }
            *cooler_fault = (s_cooler_current_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
        }
    }

    if(gate_fault != NULL) {
        if(status.gate_enable == 0U) {
            s_gate_current_fault_count = 0U;
            *gate_fault = 0U;
        } else if(adc_manager_read_raw(ADC_MANAGER_CH_GATE_CURRENT, &raw) != 0U) {
            if(raw >= fault_manager_get_threshold(s_baseline_gate_raw)) {
                s_gate_current_fault_count = 0U;
                *gate_fault = 0U;
            } else {
                if(s_gate_current_fault_count < 255U) {
                    s_gate_current_fault_count++;
                }
                *gate_fault = (s_gate_current_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
            }
        } else {
            if(s_gate_current_fault_count < 255U) {
                s_gate_current_fault_count++;
            }
            *gate_fault = (s_gate_current_fault_count >= FAULT_CURRENT_SAMPLE_COUNT) ? 1U : 0U;
        }
    }
}

/*
 * 函数名称 : fault_manager_get_status
 * 功能描述 : 获取当前所有故障状态快照。
 * 输入参数 :
 *   - status : 输出指针，非 NULL 时写入当前故障状态。
 * 说明     :
 *   - 该接口主要用于 CAN 上报等需要读取故障状态的模块；
 *   - 仅做结构体拷贝，不改变任何内部状态。
 */
void fault_manager_get_status(fault_manager_status_t *status)
{
    if(status != NULL) {
        *status = s_status;
    }
}
