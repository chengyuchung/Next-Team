#include "bmp280.h"
#include "i2c.h"
#include <stddef.h>

/* ============================================================================
 * 模块名称 : MCAL - BMP280 驱动层实现
 * 说明     :
 *   1) 纯硬件操作：I2C 读写、数据补偿计算
 *   2) 移除所有业务逻辑：LED 指示、报警判断
 *   3) 使用标准错误码返回，不再依赖 0/1 约定
 * ============================================================================
 */

/* ---- 配置参数 ----------------------------------------------------------- */
#define BMP280_OSRS_T_1X          1U    /* 温度过采样 x1 */
#define BMP280_OSRS_P_1X          1U    /* 压力过采样 x1 */
#define BMP280_MODE_NORMAL        3U    /* 正常模式（持续测量）*/
#define BMP280_T_SB_1000_MS       5U    /* 待机时间 1000ms */
#define BMP280_FILTER_OFF         0U    /* 滤波器关闭 */
#define BMP280_SPI3W_DISABLE      0U    /* 禁用 SPI 3线模式 */

#define BMP280_CTRL_MEAS_VALUE    ((uint8_t)((BMP280_OSRS_T_1X << 5) | (BMP280_OSRS_P_1X << 2) | BMP280_MODE_NORMAL))
#define BMP280_CONFIG_VALUE       ((uint8_t)((BMP280_T_SB_1000_MS << 5) | (BMP280_FILTER_OFF << 2) | BMP280_SPI3W_DISABLE))

#define BMP280_I2C_TIMEOUT_COUNT  50000U

/* ---- 内部状态 ----------------------------------------------------------- */
static uint8_t s_initialized = 0U;
static uint8_t s_device_addr = BMP280_I2C_ADDR_0X76;
static bmp280_calib_t s_calib;
static int32_t s_t_fine = 0;  /* 温度补偿中间变量 */

/* ---- 内部函数声明 ------------------------------------------------------- */
static bmp280_status_t bmp280_wait_flag(uint32_t flag, FlagStatus expected);
static bmp280_status_t bmp280_write_reg(uint8_t reg, uint8_t data);
static bmp280_status_t bmp280_read_regs(uint8_t reg, uint8_t *buf, uint16_t len);
static bmp280_status_t bmp280_read_chip_id(uint8_t *chip_id);
static bmp280_status_t bmp280_read_calib(void);
static bmp280_status_t bmp280_read_raw(uint8_t *buf, uint16_t len);
static int32_t bmp280_compensate_temperature(int32_t adc_T);
static uint32_t bmp280_compensate_pressure(int32_t adc_P);

/* ============================================================================
 * 函数名称 : bmp280_wait_flag
 * 功能描述 : 等待 I2C 标志位
 * ============================================================================
 */
static bmp280_status_t bmp280_wait_flag(uint32_t flag, FlagStatus expected)
{
    uint32_t timeout = BMP280_I2C_TIMEOUT_COUNT;

    while(timeout-- > 0U) {
        if(i2c_flag_get(I2CX, flag) == expected) {
            return BMP280_OK;
        }
    }

    return BMP280_ERR_I2C_TIMEOUT;
}

/* ============================================================================
 * 函数名称 : bmp280_write_reg
 * 功能描述 : 写单个寄存器
 * ============================================================================
 */
static bmp280_status_t bmp280_write_reg(uint8_t reg, uint8_t data)
{
    bmp280_status_t status;

    i2c_master_addressing(I2CX, (uint32_t)(s_device_addr << 1), I2C_MASTER_TRANSMIT);
    i2c_transfer_byte_number_config(I2CX, 2U);
    i2c_automatic_end_enable(I2CX);

    status = bmp280_wait_flag(I2C_FLAG_I2CBSY, RESET);
    if(status != BMP280_OK) {
        return status;
    }

    i2c_start_on_bus(I2CX);

    status = bmp280_wait_flag(I2C_FLAG_TBE, SET);
    if(status != BMP280_OK) {
        return status;
    }
    i2c_data_transmit(I2CX, reg);

    status = bmp280_wait_flag(I2C_FLAG_TI, SET);
    if(status != BMP280_OK) {
        return status;
    }
    i2c_data_transmit(I2CX, data);

    status = bmp280_wait_flag(I2C_FLAG_STPDET, SET);
    if(status != BMP280_OK) {
        return status;
    }
    i2c_flag_clear(I2CX, I2C_FLAG_STPDET);

    return BMP280_OK;
}

/* ============================================================================
 * 函数名称 : bmp280_read_regs
 * 功能描述 : 连续读取多个寄存器
 * ============================================================================
 */
static bmp280_status_t bmp280_read_regs(uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    bmp280_status_t status;

    if((buf == NULL) || (len == 0U)) {
        return BMP280_ERR_PARAM;
    }

    i2c_master_addressing(I2CX, (uint32_t)(s_device_addr << 1), I2C_MASTER_TRANSMIT);
    i2c_transfer_byte_number_config(I2CX, 1U);
    i2c_automatic_end_disable(I2CX);

    status = bmp280_wait_flag(I2C_FLAG_I2CBSY, RESET);
    if(status != BMP280_OK) {
        return status;
    }

    i2c_start_on_bus(I2CX);

    status = bmp280_wait_flag(I2C_FLAG_TBE, SET);
    if(status != BMP280_OK) {
        return status;
    }
    i2c_data_transmit(I2CX, reg);

    status = bmp280_wait_flag(I2C_FLAG_TC, SET);
    if(status != BMP280_OK) {
        return status;
    }

    i2c_master_addressing(I2CX, (uint32_t)(s_device_addr << 1), I2C_MASTER_RECEIVE);
    i2c_transfer_byte_number_config(I2CX, (uint8_t)len);
    i2c_automatic_end_enable(I2CX);
    i2c_start_on_bus(I2CX);

    for(i = 0U; i < len; i++) {
        status = bmp280_wait_flag(I2C_FLAG_RBNE, SET);
        if(status != BMP280_OK) {
            return status;
        }
        buf[i] = i2c_data_receive(I2CX);
    }

    status = bmp280_wait_flag(I2C_FLAG_STPDET, SET);
    if(status != BMP280_OK) {
        return status;
    }
    i2c_flag_clear(I2CX, I2C_FLAG_STPDET);

    return BMP280_OK;
}

/* ============================================================================
 * 函数名称 : bmp280_read_chip_id
 * 功能描述 : 读取芯片 ID
 * ============================================================================
 */
static bmp280_status_t bmp280_read_chip_id(uint8_t *chip_id)
{
    if(chip_id == NULL) {
        return BMP280_ERR_PARAM;
    }
    return bmp280_read_regs(BMP280_REG_CHIPID, chip_id, 1U);
}

/* ============================================================================
 * 函数名称 : bmp280_read_calib
 * 功能描述 : 读取温度/压力校准参数
 * ============================================================================
 */
static bmp280_status_t bmp280_read_calib(void)
{
    uint8_t buf[24];
    bmp280_status_t status;

    status = bmp280_read_regs(0x88U, buf, 24U);
    if(status != BMP280_OK) {
        return status;
    }

    s_calib.dig_T1 = (uint16_t)(((uint16_t)buf[1] << 8) | buf[0]);
    s_calib.dig_T2 = (int16_t)(((uint16_t)buf[3] << 8) | buf[2]);
    s_calib.dig_T3 = (int16_t)(((uint16_t)buf[5] << 8) | buf[4]);
    s_calib.dig_P1 = (uint16_t)(((uint16_t)buf[7] << 8) | buf[6]);
    s_calib.dig_P2 = (int16_t)(((uint16_t)buf[9] << 8) | buf[8]);
    s_calib.dig_P3 = (int16_t)(((uint16_t)buf[11] << 8) | buf[10]);
    s_calib.dig_P4 = (int16_t)(((uint16_t)buf[13] << 8) | buf[12]);
    s_calib.dig_P5 = (int16_t)(((uint16_t)buf[15] << 8) | buf[14]);
    s_calib.dig_P6 = (int16_t)(((uint16_t)buf[17] << 8) | buf[16]);
    s_calib.dig_P7 = (int16_t)(((uint16_t)buf[19] << 8) | buf[18]);
    s_calib.dig_P8 = (int16_t)(((uint16_t)buf[21] << 8) | buf[20]);
    s_calib.dig_P9 = (int16_t)(((uint16_t)buf[23] << 8) | buf[22]);

    return BMP280_OK;
}

/* ============================================================================
 * 函数名称 : bmp280_read_raw
 * 功能描述 : 读取原始压力/温度数据（6字节）
 * ============================================================================
 */
static bmp280_status_t bmp280_read_raw(uint8_t *buf, uint16_t len)
{
    if((buf == NULL) || (len == 0U)) {
        return BMP280_ERR_PARAM;
    }
    return bmp280_read_regs(0xF7U, buf, len);
}

/* ============================================================================
 * 函数名称 : bmp280_compensate_temperature
 * 功能描述 : 温度补偿算法（来自 Bosch 官方数据手册）
 * 返回值   : 温度 (0.01°C)
 * ============================================================================
 */
static int32_t bmp280_compensate_temperature(int32_t adc_T)
{
    int32_t var1, var2, T;

    var1 = ((((adc_T >> 3) - ((int32_t)s_calib.dig_T1 << 1))) * ((int32_t)s_calib.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)s_calib.dig_T1)) * ((adc_T >> 4) - ((int32_t)s_calib.dig_T1))) >> 12) *
            ((int32_t)s_calib.dig_T3)) >> 14;
    s_t_fine = var1 + var2;
    T = (s_t_fine * 5 + 128) >> 8;

    return T;
}

/* ============================================================================
 * 函数名称 : bmp280_compensate_pressure
 * 功能描述 : 压力补偿算法（来自 Bosch 官方数据手册）
 * 返回值   : 压力 (Pa)
 * ============================================================================
 */
static uint32_t bmp280_compensate_pressure(int32_t adc_P)
{
    int64_t var1, var2, p;

    var1 = ((int64_t)s_t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)s_calib.dig_P6;
    var2 = var2 + ((var1 * (int64_t)s_calib.dig_P5) << 17);
    var2 = var2 + (((int64_t)s_calib.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)s_calib.dig_P3) >> 8) + ((var1 * (int64_t)s_calib.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1) * ((int64_t)s_calib.dig_P1)) >> 33;

    if(var1 == 0) {
        return 0U;
    }

    p = 1048576 - adc_P;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)s_calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)s_calib.dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)s_calib.dig_P7) << 4);

    return (uint32_t)(p >> 8);
}

/* ============================================================================
 * 公共接口实现
 * ============================================================================
 */

bmp280_status_t bmp280_init(uint8_t dev_addr_7bit)
{
    uint8_t chip_id = 0U;
    bmp280_status_t status;

    s_device_addr = dev_addr_7bit;
    s_initialized = 0U;

    status = bmp280_read_chip_id(&chip_id);
    if(status != BMP280_OK) {
        return status;
    }

    if(chip_id != BMP280_CHIP_ID_EXPECTED) {
        return BMP280_ERR_CHIP_ID;
    }

    status = bmp280_write_reg(0xF4U, BMP280_CTRL_MEAS_VALUE);
    if(status != BMP280_OK) {
        return status;
    }

    status = bmp280_write_reg(0xF5U, BMP280_CONFIG_VALUE);
    if(status != BMP280_OK) {
        return status;
    }

    status = bmp280_read_calib();
    if(status != BMP280_OK) {
        return status;
    }

    s_initialized = 1U;
    return BMP280_OK;
}

bmp280_status_t bmp280_read(bmp280_raw_data_t *out)
{
    uint8_t raw[6];
    int32_t adc_T, adc_P;
    bmp280_status_t status;

    if(out == NULL) {
        return BMP280_ERR_PARAM;
    }

    if(s_initialized == 0U) {
        return BMP280_ERR_NOT_INIT;
    }

    status = bmp280_read_raw(raw, 6U);
    if(status != BMP280_OK) {
        out->temperature_centi_c = 0;
        out->pressure_pa = 0;
        return status;
    }

    adc_P = ((int32_t)raw[0] << 12) | ((int32_t)raw[1] << 4) | ((int32_t)raw[2] >> 4);
    adc_T = ((int32_t)raw[3] << 12) | ((int32_t)raw[4] << 4) | ((int32_t)raw[5] >> 4);

    out->temperature_centi_c = bmp280_compensate_temperature(adc_T);
    out->pressure_pa = (int32_t)bmp280_compensate_pressure(adc_P);

    return BMP280_OK;
}

uint8_t bmp280_is_initialized(void)
{
    return s_initialized;
}
