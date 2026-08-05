#ifndef ECUAL_PRESSURE_SENSOR_H
#define ECUAL_PRESSURE_SENSOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 模块名称 : ECUAL - 压力传感器抽象层
 * 文件功能 : 封装 BMP280 驱动，提供应用层友好的接口
 * 说明     :
 *   1) 隐藏底层驱动细节（MCAL/bmp280）
 *   2) 添加业务逻辑：报警阈值判断、故障处理
 *   3) 统一传感器接口规范（valid/alarm 标志）
 * ============================================================================
 */

/* ---- 报警阈值配置 ------------------------------------------------------- */
#define PRESSURE_ALARM_LOW_PA     90000L   /* 低压报警阈值 (90 kPa) */
#define PRESSURE_ALARM_HIGH_PA    110000L  /* 高压报警阈值 (110 kPa) */

/* ---- 传感器数据结构 ----------------------------------------------------- */
typedef struct {
    int32_t temperature_centi_c;  /* 温度 (0.01°C)，例如 2534 表示 25.34°C */
    int32_t pressure_pa;          /* 压力 (Pa)，例如 101325 表示 101.325 kPa */
    uint8_t valid;                /* 1=数据有效，0=读取失败 */
    uint8_t alarm;                /* 1=压力超限报警，0=正常 */
} pressure_sensor_data_t;

/* ---- 接口函数 ----------------------------------------------------------- */

/**
 * @brief  初始化压力传感器
 * @param  dev_addr_7bit: I2C 设备地址 (0x76 或 0x77)
 * @return 1=成功，0=失败
 * @note   前提：I2C 总线已完成初始化
 */
uint8_t pressure_sensor_init(uint8_t dev_addr_7bit);

/**
 * @brief  读取压力传感器数据（带报警判断）
 * @param  out: 输出数据结构指针
 * @return 1=成功，0=失败
 */
uint8_t pressure_sensor_read(pressure_sensor_data_t *out);

/**
 * @brief  获取初始化状态
 * @return 1=已初始化，0=未初始化
 */
uint8_t pressure_sensor_is_ready(void);

#ifdef __cplusplus
}
#endif

#endif /* ECUAL_PRESSURE_SENSOR_H */
