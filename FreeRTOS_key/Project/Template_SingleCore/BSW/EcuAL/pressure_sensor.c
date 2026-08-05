#include "pressure_sensor.h"
#include "../../MCAL/bmp280.h"
#include <stddef.h>

/* ============================================================================
 * 模块名称 : ECUAL - 压力传感器抽象层实现
 * 说明     :
 *   1) 调用 MCAL 层驱动 (bmp280)
 *   2) 添加业务逻辑：报警阈值判断
 *   3) 将驱动层错误码转换为应用层 valid 标志
 * ============================================================================
 */

uint8_t pressure_sensor_init(uint8_t dev_addr_7bit)
{
    bmp280_status_t status;

    status = bmp280_init(dev_addr_7bit);
    return (status == BMP280_OK) ? 1U : 0U;
}

uint8_t pressure_sensor_read(pressure_sensor_data_t *out)
{
    bmp280_raw_data_t raw;
    bmp280_status_t status;

    if(out == NULL) {
        return 0U;
    }

    status = bmp280_read(&raw);
    if(status != BMP280_OK) {
        out->temperature_centi_c = 0;
        out->pressure_pa = 0;
        out->valid = 0U;
        out->alarm = 0U;
        return 0U;
    }

    out->temperature_centi_c = raw.temperature_centi_c;
    out->pressure_pa = raw.pressure_pa;
    out->valid = 1U;

    /* 报警阈值判断（业务逻辑） */
    out->alarm = (uint8_t)(((out->pressure_pa < PRESSURE_ALARM_LOW_PA) ||
                            (out->pressure_pa > PRESSURE_ALARM_HIGH_PA)) ? 1U : 0U);

    return 1U;
}

uint8_t pressure_sensor_is_ready(void)
{
    return bmp280_is_initialized();
}
