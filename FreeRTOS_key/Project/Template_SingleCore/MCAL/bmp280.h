#ifndef MCAL_BMP280_H
#define MCAL_BMP280_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================
 * 模块名称 : MCAL - BMP280 驱动层
 * 文件功能 : BMP280 气压/温度传感器硬件驱动接口（MCAL 层）
 * 说明     :
 *   1) 纯硬件操作，不包含业务逻辑（报警判断、LED 指示等）
 *   2) 返回原始物理量：温度 (0.01°C)、压力 (Pa)
 *   3) 依赖 I2C 总线驱动（i2c.c）
 *   4) 上层（ECUAL）负责报警阈值判断和故障处理
 * ============================================================================
 */

/* ---- 硬件配置常量 -------------------------------------------------------- */
#define BMP280_I2C_ADDR_0X76        0x76U
#define BMP280_I2C_ADDR_0X77        0x77U
#define BMP280_CHIP_ID_EXPECTED     0x58U

/* ---- 寄存器地址 --------------------------------------------------------- */
enum {
    BMP280_REG_DIG_T1         = 0x88,
    BMP280_REG_DIG_T2         = 0x8A,
    BMP280_REG_DIG_T3         = 0x8C,
    BMP280_REG_DIG_P1         = 0x8E,
    BMP280_REG_DIG_P2         = 0x90,
    BMP280_REG_DIG_P3         = 0x92,
    BMP280_REG_DIG_P4         = 0x94,
    BMP280_REG_DIG_P5         = 0x96,
    BMP280_REG_DIG_P6         = 0x98,
    BMP280_REG_DIG_P7         = 0x9A,
    BMP280_REG_DIG_P8         = 0x9C,
    BMP280_REG_DIG_P9         = 0x9E,
    BMP280_REG_CHIPID         = 0xD0,
    BMP280_REG_RESET          = 0xE0,
    BMP280_REG_CONTROL        = 0xF4,
    BMP280_REG_CONFIG         = 0xF5,
    BMP280_REG_PRESSUREDATA   = 0xF7,
    BMP280_REG_TEMPDATA       = 0xFA
};

/* ---- 错误码 ------------------------------------------------------------- */
typedef enum {
    BMP280_OK = 0,           /* 成功 */
    BMP280_ERR_PARAM,        /* 参数错误 */
    BMP280_ERR_NOT_INIT,     /* 未初始化 */
    BMP280_ERR_I2C_TIMEOUT,  /* I2C 超时 */
    BMP280_ERR_CHIP_ID,      /* 芯片 ID 不匹配 */
    BMP280_ERR_CALIB         /* 校准参数读取失败 */
} bmp280_status_t;

/* ---- 校准参数结构体 ------------------------------------------------------ */
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
} bmp280_calib_t;

/* ---- 原始测量数据（物理量） ----------------------------------------------- */
typedef struct {
    int32_t temperature_centi_c;  /* 温度 (0.01°C)，例如 2534 表示 25.34°C */
    int32_t pressure_pa;          /* 压力 (Pa)，例如 101325 表示 101325 Pa */
} bmp280_raw_data_t;

/* ---- 驱动接口 ----------------------------------------------------------- */

/**
 * @brief  初始化 BMP280 传感器
 * @param  dev_addr_7bit: I2C 7位设备地址 (0x76 或 0x77)
 * @return bmp280_status_t 错误码
 * @note   前提：I2C 总线已由 i2c_config() 初始化完成
 */
bmp280_status_t bmp280_init(uint8_t dev_addr_7bit);

/**
 * @brief  读取温度和压力（物理量）
 * @param  out: 输出结构体指针
 * @return bmp280_status_t 错误码
 */
bmp280_status_t bmp280_read(bmp280_raw_data_t *out);

/**
 * @brief  获取初始化状态
 * @return 1=已初始化，0=未初始化
 */
uint8_t bmp280_is_initialized(void);

#ifdef __cplusplus
}
#endif

#endif /* MCAL_BMP280_H */
