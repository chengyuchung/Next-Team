#ifndef BMP280_H
#define BMP280_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : bmp280
 * 文件功能 : BMP280 压力/温度传感器驱动接口定义
 * 说明     :
 *   1) 提供 BMP280 初始化、温度读取、压力读取接口；
 *   2) 输出真实工程量：温度(°C) 与压力(Pa)；
 *   3) 底层通过 GD32 I2C 通信实现。
 * ============================================================================
 */

#define BMP280_I2C_ADDR_0X76        0x76U
#define BMP280_I2C_ADDR_0X77        0x77U
#define BMP280_CHIP_ID_EXPECTED     0x58U

#define BMP280_PRESSURE_ALARM_LOW_PA    90000L
#define BMP280_PRESSURE_ALARM_HIGH_PA   110000L

/* BMP280 寄存器定义 */
enum {
    BMP280_REGISTER_DIG_T1        = 0x88,
    BMP280_REGISTER_DIG_T2        = 0x8A,
    BMP280_REGISTER_DIG_T3        = 0x8C,
    BMP280_REGISTER_DIG_P1        = 0x8E,
    BMP280_REGISTER_DIG_P2        = 0x90,
    BMP280_REGISTER_DIG_P3        = 0x92,
    BMP280_REGISTER_DIG_P4        = 0x94,
    BMP280_REGISTER_DIG_P5        = 0x96,
    BMP280_REGISTER_DIG_P6        = 0x98,
    BMP280_REGISTER_DIG_P7        = 0x9A,
    BMP280_REGISTER_DIG_P8        = 0x9C,
    BMP280_REGISTER_DIG_P9        = 0x9E,
    BMP280_REGISTER_CHIPID        = 0xD0,
    BMP280_REGISTER_RESET         = 0xE0,
    BMP280_REGISTER_CONTROL       = 0xF4,
    BMP280_REGISTER_CONFIG        = 0xF5,
    BMP280_REGISTER_PRESSUREDATA  = 0xF7,
    BMP280_REGISTER_TEMPDATA      = 0xFA
};

typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
} bmp280_calib_data_t;

typedef struct {
    int32_t temperature_centi_c;  /* 温度（0.01°C） */
    int32_t pressure_pa;          /* 压力（Pa） */
    uint8_t valid;                /* 1=有效 */
    uint8_t alarm;                /* 1=压力超限报警 */
} bmp280_data_t;

/* 初始化传感器并读取校准参数。 */
uint8_t bmp280_init(uint8_t dev_addr_7bit);

/* 读取一次压力、有效标志与警报标志。 */
uint8_t pressure_get(bmp280_data_t *out);

/* 兼容旧接口名。 */
uint8_t bmp280_read_once(bmp280_data_t *out);

#ifdef __cplusplus
}
#endif

#endif /* BMP280_H */
