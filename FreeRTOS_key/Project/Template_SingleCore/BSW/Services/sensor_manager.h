#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <stdint.h>
#include "BSW/EcuAL/temp_sensor.h"
#include "BSW/EcuAL/pressure_sensor.h"
#include "BSW/EcuAL/gas_sensor.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : sensor_manager
 * 文件功能 : 传感器数据聚合与缓存管理
 * 
 * 设计目标 :
 *   1) 统一管理多传感器（温度、压力、气体）的数据采集和缓存；
 *   2) 提供线程安全的缓存读写接口（基于 FreeRTOS 互斥锁）；
 *   3) 支持异步采集架构（采集任务与消费任务解耦）。
 * 
 * 架构说明 :
 *   - 温度采集：由专门的 temp_task 周期性刷新缓存（~1秒）
 *   - 压力/气体：由上层业务在需要时同步读取
 *   - 缓存机制：避免阻塞控制循环（温度采集约 750-800ms）
 * ============================================================================
 */

/*
 * 传感器数据聚合结构体
 */
typedef struct {
    /* 温度数据 */
    temp_result_t temperature;
    uint32_t temp_sample_time_ms;
    uint8_t temp_has_sample;
    
    /* 压力数据 */
    pressure_sensor_data_t pressure;
    
    /* 气体数据 */
    gas_sensor_result_t gas;
} sensor_data_t;

/*
 * 函数名称 : sensor_manager_init
 * 功能描述 : 初始化传感器管理模块（创建互斥锁等）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - 1U : 初始化成功
 *   - 0U : 初始化失败
 */
uint8_t sensor_manager_init(void);

/*
 * 函数名称 : sensor_manager_store_temperature
 * 功能描述 : 存储温度采集结果到缓存（线程安全）。
 * 输入参数 :
 *   - result         : 温度采集结果
 *   - sample_time_ms : 采集完成时间戳
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void sensor_manager_store_temperature(const temp_result_t *result, uint32_t sample_time_ms);

/*
 * 函数名称 : sensor_manager_load_temperature
 * 功能描述 : 从缓存读取温度数据（线程安全）。
 * 输入参数 : 无
 * 输出参数 :
 *   - result         : 温度采集结果
 *   - sample_time_ms : 采集完成时间戳
 * 返 回 值 :
 *   - 1U : 缓存中有有效数据
 *   - 0U : 缓存为空（尚未完成首次采集）
 */
uint8_t sensor_manager_load_temperature(temp_result_t *result, uint32_t *sample_time_ms);

/*
 * 函数名称 : sensor_manager_read_pressure
 * 功能描述 : 读取压力传感器数据（同步读取）。
 * 输入参数 : 无
 * 输出参数 :
 *   - data : 压力传感器数据
 * 返 回 值 :
 *   - 1U : 读取成功
 *   - 0U : 读取失败
 */
uint8_t sensor_manager_read_pressure(pressure_sensor_data_t *data);

/*
 * 函数名称 : sensor_manager_read_gas
 * 功能描述 : 读取气体传感器数据（同步读取）。
 * 输入参数 : 无
 * 输出参数 :
 *   - data : 气体传感器数据
 * 返 回 值 :
 *   - 1U : 读取成功
 *   - 0U : 读取失败
 */
uint8_t sensor_manager_read_gas(gas_sensor_result_t *data);

/*
 * 函数名称 : sensor_manager_read_all
 * 功能描述 : 一次性读取所有传感器数据（组合接口）。
 * 输入参数 : 无
 * 输出参数 :
 *   - data : 传感器数据聚合结构
 * 返 回 值 : 无
 */
void sensor_manager_read_all(sensor_data_t *data);

/*
 * 函数名称 : sensor_manager_sample_temp_blocking
 * 功能描述 : 同步采集温度并写入缓存（guard 模式专用）。
 * 输入参数 :
 *   - now_ms : 当前时间戳（毫秒）
 * 输出参数 : 无
 * 返 回 值 : 无
 * 
 * 注意事项 :
 *   - 此函数在 guard 模式下由 guard_task 调用（temp_task 已挂起）
 *   - 执行同步温度采集（约 750ms），然后写入缓存
 *   - 如果采集失败，写入全零数据
 */
void sensor_manager_sample_temp_blocking(uint32_t now_ms);

#ifdef __cplusplus
}
#endif

#endif /* SENSOR_MANAGER_H */
