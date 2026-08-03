#include "temp_sensor.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : temp_sensor (业务逻辑)
 * 文件功能 : 基于 ds18b20 底层驱动的 4 路温度采集业务层
 * 采集策略 :
 *   4 路是各自独立的 1-Wire 总线，采用“并行转换”降低总耗时：
 *     阶段1  逐路发出 Convert T（约几 ms）
 *     阶段2  只等待一次转换时间（约 750ms），而非串行等 4 次
 *     阶段3  逐路读暂存器 + CRC 校验，得到每一路温度
 *   最坏情况总耗时约 0.8s，而不是 3s。
 * ============================================================================
 */

static temp_result_t s_last_result;

void temp_sensor_init(void)
{
    memset(&s_last_result, 0, sizeof(s_last_result));
    ds18b20_gd32_adapter_init();
}

uint8_t temp_get(temp_result_t *result)
{
    uint8_t started[DS18B20_GD32_CHANNEL_COUNT];
    ds18b20_t *dev;
    int16_t temp;
    int16_t max_temp = 0;
    uint8_t i;
    uint8_t valid_count = 0U;
    uint8_t fault_mask = 0U;

    if(result == NULL) {
        return 0U;
    }

    memset(result, 0, sizeof(*result));

    /* 阶段 1：并行启动全部有效通道的温度转换。 */
    for(i = 0U; i < DS18B20_GD32_CHANNEL_COUNT; i++) {
        dev = ds18b20_gd32_get_device((ds18b20_gd32_channel_t)i);
        if(dev != NULL) {
            started[i] = ds18b20_start_conversion(dev);
        } else {
            started[i] = 0U;
        }
        if(started[i] == 0U) {
            fault_mask |= (uint8_t)(1U << i);
        }
    }

    /* 阶段 2：只等待一次转换时间。任取一路已启动的通道轮询即可，
     * 其余通道此时也已并行完成转换。 */
    for(i = 0U; i < DS18B20_GD32_CHANNEL_COUNT; i++) {
        if(started[i] != 0U) {
            ds18b20_wait_conversion(ds18b20_gd32_get_device((ds18b20_gd32_channel_t)i));
            break;
        }
    }

    /* 阶段 3：逐路读取暂存器并做 CRC 校验，记录每一路温度。 */
    for(i = 0U; i < DS18B20_GD32_CHANNEL_COUNT; i++) {
        if(started[i] == 0U) {
            continue;
        }

        dev = ds18b20_gd32_get_device((ds18b20_gd32_channel_t)i);
        if((dev != NULL) && (ds18b20_read_scratchpad_temp(dev, &temp) != 0U)) {
            result->temperature[i] = temp;
            result->channel_valid[i] = 1U;
            if(valid_count == 0U) {
                max_temp = temp;
            } else if(temp > max_temp) {
                max_temp = temp;
            }
            valid_count++;
        } else {
            fault_mask |= (uint8_t)(1U << i);
        }
    }

    result->valid_count = valid_count;
    result->fault_mask = fault_mask;
    result->valid = (uint8_t)(valid_count > 0U ? 1U : 0U);
    result->maximum_temperature = (valid_count > 0U) ? max_temp : 0;

    s_last_result = *result;
    return result->valid;
}

uint8_t temp_get_last(temp_result_t *result)
{
    if(result == NULL) {
        return 0U;
    }
    *result = s_last_result;
    return s_last_result.valid;
}
