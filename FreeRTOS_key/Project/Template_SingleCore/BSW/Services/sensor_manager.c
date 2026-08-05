#include "sensor_manager.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : sensor_manager
 * 文件功能 : 传感器数据聚合与缓存管理
 * 
 * 实现说明 :
 *   1) 温度数据缓存：使用互斥锁保护，支持异步采集架构；
 *   2) 压力/气体数据：直接调用 EcuAL 层接口同步读取；
 *   3) 线程安全：所有缓存访问均通过互斥锁保护。
 * ============================================================================
 */

/*
 * 温度缓存结构体
 */
typedef struct {
    temp_result_t result;       /* 最近一次采集结果 */
    uint32_t sample_time_ms;    /* 采集完成时间戳 */
    uint8_t has_sample;         /* 是否已完成过至少一次采集 */
} temp_cache_t;

static temp_cache_t s_temp_cache;
static SemaphoreHandle_t s_temp_cache_mutex = NULL;

uint8_t sensor_manager_init(void)
{
    memset(&s_temp_cache, 0, sizeof(s_temp_cache));
    
    s_temp_cache_mutex = xSemaphoreCreateMutex();
    if(s_temp_cache_mutex == NULL) {
        return 0U;
    }
    
    return 1U;
}

void sensor_manager_store_temperature(const temp_result_t *result, uint32_t sample_time_ms)
{
    if((result == NULL) || (s_temp_cache_mutex == NULL)) {
        return;
    }
    
    if(xSemaphoreTake(s_temp_cache_mutex, portMAX_DELAY) == pdTRUE) {
        s_temp_cache.result = *result;
        s_temp_cache.sample_time_ms = sample_time_ms;
        s_temp_cache.has_sample = 1U;
        (void)xSemaphoreGive(s_temp_cache_mutex);
    }
}

uint8_t sensor_manager_load_temperature(temp_result_t *result, uint32_t *sample_time_ms)
{
    uint8_t has_sample = 0U;
    
    if((result == NULL) || (sample_time_ms == NULL) || (s_temp_cache_mutex == NULL)) {
        return 0U;
    }
    
    if(xSemaphoreTake(s_temp_cache_mutex, portMAX_DELAY) == pdTRUE) {
        *result = s_temp_cache.result;
        *sample_time_ms = s_temp_cache.sample_time_ms;
        has_sample = s_temp_cache.has_sample;
        (void)xSemaphoreGive(s_temp_cache_mutex);
    }
    
    return has_sample;
}

uint8_t sensor_manager_read_pressure(pressure_sensor_data_t *data)
{
    if(data == NULL) {
        return 0U;
    }
    
    return pressure_sensor_read(data);
}

uint8_t sensor_manager_read_gas(gas_sensor_result_t *data)
{
    if(data == NULL) {
        return 0U;
    }
    
    (void)gas_sensor_task();
    return get_gas(data);
}

void sensor_manager_read_all(sensor_data_t *data)
{
    if(data == NULL) {
        return;
    }
    
    memset(data, 0, sizeof(sensor_data_t));
    
    data->temp_has_sample = sensor_manager_load_temperature(
        &data->temperature,
        &data->temp_sample_time_ms
    );
    
    (void)sensor_manager_read_pressure(&data->pressure);
    (void)sensor_manager_read_gas(&data->gas);
}

void sensor_manager_sample_temp_blocking(uint32_t now_ms)
{
    temp_result_t result;
    if(temp_get(&result) != 0U) {
        sensor_manager_store_temperature(&result, now_ms);
    } else {
        memset(&result, 0, sizeof(result));
        sensor_manager_store_temperature(&result, now_ms);
    }
}
