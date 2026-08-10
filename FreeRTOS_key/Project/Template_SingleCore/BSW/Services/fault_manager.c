#include "fault_manager.h"
#include "adc_ecual.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : fault_manager
 * 文件功能 : 气体传感器故障检测与故障码管理实现
 *
 * 设计目标 :
 *   1) 监测气体传感器的 ADC 输出值（PD11 / ADC0_IN9）；
 *   2) 通过"连续异常计数"的方式降低瞬时抖动和误判；
 *   3) 为系统提供统一、稳定的故障状态输出。
 *
 * 设计说明 :
 *   - 气体传感器监测 : PD11 / ADC0_IN9（MQ9 模拟量输出）
 *   - 采用区间判断：raw 在 [2421, 2448] 内视为正常，超出视为故障；
 *   - 连续异常计数确认，避免单次采样毛刺误判。
 * ============================================================================
 */

/*
 * 运行时可配置的阈值（初始值来自头文件宏定义，可通过 CAN 配置命令动态修改）
 */
uint16_t g_gas_sensor_raw_min = FAULT_GAS_SENSOR_RAW_MIN;
uint16_t g_gas_sensor_raw_max = FAULT_GAS_SENSOR_RAW_MAX;

/*
 * 模块内部状态：
 * s_status 保存最终对外输出的故障状态；
 * s_gas_fault_count 用于气体传感器连续异常统计。
 */
static fault_manager_status_t s_status;
static uint8_t s_gas_fault_count;

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
    s_gas_fault_count = 0U;
}

/*
 * 函数名称 : fault_manager_update
 * 功能描述 : 更新气体传感器故障检测状态（需在控制周期内周期性调用）。
 * 说明     :
 *   - 读取 ADC 原始值，判断是否在正常区间 [2421, 2448]；
 *   - 超出区间时累加连续异常计数，连续 3 次异常才确认故障；
 *   - 恢复正常时立即清零计数并解除故障。
 */
void fault_manager_update(void)
{
    uint16_t raw = 0U;
    uint8_t gas_result;

    if(adc_ecual_read_raw(ADC_ECUAL_CH_GAS_SENSOR, &raw) != 0U) {
        /* 区间判断：在 [g_gas_sensor_raw_min, g_gas_sensor_raw_max] 内视为正常。
         * 使用运行时变量而非固定宏，支持通过 CAN 配置命令动态调整。 */
        if((raw >= g_gas_sensor_raw_min) && (raw <= g_gas_sensor_raw_max)) {
            s_gas_fault_count = 0U;
            gas_result = 0U;
        } else {
            /* 超出区间，累加异常计数 */
            if(s_gas_fault_count < 255U) {
                s_gas_fault_count++;
            }
            gas_result = (s_gas_fault_count >= FAULT_GAS_SENSOR_SAMPLE_COUNT) ? 1U : 0U;
        }
    } else {
        /* ADC 读取失败也视为异常 */
        if(s_gas_fault_count < 255U) {
            s_gas_fault_count++;
        }
        gas_result = (s_gas_fault_count >= FAULT_GAS_SENSOR_SAMPLE_COUNT) ? 1U : 0U;
    }

    s_status.gas_sensor_fault = gas_result;
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
