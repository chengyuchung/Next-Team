#include "bmp280.h"
#include "i2c.h"
#include "gd32a712_evb.h"
/*
 * 迁移目标：
 * 1) 保留官方示例里的初始化参数；
 * 2) 迁移 BMP280 的寄存器写入/读取通用接口；
 * 3) 继续把官方示例里的 readTrim() 迁移进来。
 *
 * 官方示例（BME280_I2C.ino）里初始化的核心参数是：
 * - osrs_t / osrs_p / mode -> ctrl_meas(0xF4)
 * - t_sb / filter / spi3w_en -> config(0xF5)
 *
 * 说明：BMP280 没有湿度通道，所以不迁移 ctrl_hum(0xF2)。
 */
extern void rcu_config(void);
extern void gpio_config(void);
extern void i2c_config(void);

#define BMP280_REG_CTRL_HUM       0xF2U
#define BMP280_REG_CTRL_MEAS      0xF4U
#define BMP280_REG_CONFIG         0xF5U
#define BMP280_REG_CALIB_START    0x88U

#define BMP280_OSRS_T_1X          1U
#define BMP280_OSRS_P_1X          1U
#define BMP280_MODE_NORMAL        3U
#define BMP280_T_SB_1000_MS       5U
#define BMP280_FILTER_OFF         0U
#define BMP280_SPI3W_DISABLE      0U

#define BMP280_CTRL_MEAS_VALUE    ((uint8_t)((BMP280_OSRS_T_1X << 5) | (BMP280_OSRS_P_1X << 2) | BMP280_MODE_NORMAL))
#define BMP280_CONFIG_VALUE       ((uint8_t)((BMP280_T_SB_1000_MS << 5) | (BMP280_FILTER_OFF << 2) | BMP280_SPI3W_DISABLE))

static uint8_t s_inited = 0U;
static uint8_t s_bmp280_addr = BMP280_I2C_ADDR_0X76;
static bmp280_calib_data_t s_calib;

#define BMP280_I2C_TIMEOUT_COUNT    50000U

static uint8_t bmp280_wait_flag(uint32_t flag, FlagStatus expected)
{
    uint32_t timeout = BMP280_I2C_TIMEOUT_COUNT;

    while(timeout-- > 0U) {
        if(i2c_flag_get(I2CX, flag) == expected) {
            return 1U;
        }
    }

    return 0U;
}

static uint8_t bmp280_write_reg(uint8_t reg, uint8_t data)
{
    i2c_master_addressing(I2CX, (uint32_t)(s_bmp280_addr << 1), I2C_MASTER_TRANSMIT);
    i2c_transfer_byte_number_config(I2CX, 2U);
    i2c_automatic_end_enable(I2CX);

    if(bmp280_wait_flag(I2C_FLAG_I2CBSY, RESET) == 0U) {
        return 0U;
    }

    i2c_start_on_bus(I2CX);

    if(bmp280_wait_flag(I2C_FLAG_TBE, SET) == 0U) {
        return 0U;
    }
    i2c_data_transmit(I2CX, reg);

    if(bmp280_wait_flag(I2C_FLAG_TI, SET) == 0U) {
        return 0U;
    }
    i2c_data_transmit(I2CX, data);

    if(bmp280_wait_flag(I2C_FLAG_STPDET, SET) == 0U) {
        return 0U;
    }
    i2c_flag_clear(I2CX, I2C_FLAG_STPDET);

    return 1U;
}

static uint8_t bmp280_read_regs(uint8_t reg, uint8_t *buf, uint16_t len)
{
    uint16_t i;

    if((buf == 0) || (len == 0U)) {
        return 0U;
    }

    /* 先发送寄存器地址 */
    i2c_master_addressing(I2CX, (uint32_t)(s_bmp280_addr << 1), I2C_MASTER_TRANSMIT);
    i2c_transfer_byte_number_config(I2CX, 1U);
    i2c_automatic_end_disable(I2CX);

    if(bmp280_wait_flag(I2C_FLAG_I2CBSY, RESET) == 0U) {
        return 0U;
    }

    i2c_start_on_bus(I2CX);

    if(bmp280_wait_flag(I2C_FLAG_TBE, SET) == 0U) {
        return 0U;
    }
    i2c_data_transmit(I2CX, reg);

    if(bmp280_wait_flag(I2C_FLAG_TC, SET) == 0U) {
        return 0U;
    }

    /* 再切换为接收方向，连续读取数据 */
    i2c_master_addressing(I2CX, (uint32_t)(s_bmp280_addr << 1), I2C_MASTER_RECEIVE);
    i2c_transfer_byte_number_config(I2CX, (uint8_t)len);
    i2c_automatic_end_enable(I2CX);
    i2c_start_on_bus(I2CX);

    for(i = 0U; i < len; i++) {
        if(bmp280_wait_flag(I2C_FLAG_RBNE, SET) == 0U) {
            return 0U;
        }
        buf[i] = i2c_data_receive(I2CX);
    }

    if(bmp280_wait_flag(I2C_FLAG_STPDET, SET) == 0U) {
        return 0U;
    }
    i2c_flag_clear(I2CX, I2C_FLAG_STPDET);

    return 1U;
}

static uint8_t bmp280_read_chip_id(uint8_t *chip_id)
{
    if(chip_id == 0) {
        return 0U;
    }
    return bmp280_read_regs(BMP280_REGISTER_CHIPID, chip_id, 1U);
}

static uint8_t bmp280_read_trim(void)
{
    uint8_t buf[24];

    if(bmp280_read_regs(BMP280_REG_CALIB_START, buf, 24U) == 0U) {
        return 0U;
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

    return 1U;
}

typedef struct {
    int32_t temperature_centi_c;
    int32_t pressure_pa;
} bmp280_raw_data_t;

static int32_t s_t_fine = 0;

static uint8_t bmp280_read_data(uint8_t *buf, uint16_t len)
{
    if((buf == 0) || (len == 0U)) {
        return 0U;
    }

    /*
     * 对应官方示例 readData() 的 BMP280 版本：
     * 从 0xF7 开始连续读取原始压力/温度数据。
     * BMP280 只有压力和温度，没有湿度字段，因此这里读取 6 字节即可。
     */
    return bmp280_read_regs(0xF7U, buf, len);
}

static int32_t bmp280_compensate_temperature(int32_t adc_T)
{
    int32_t var1;
    int32_t var2;
    int32_t T;

    var1 = ((((adc_T >> 3) - ((int32_t)s_calib.dig_T1 << 1))) * ((int32_t)s_calib.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)s_calib.dig_T1)) * ((adc_T >> 4) - ((int32_t)s_calib.dig_T1))) >> 12) *
            ((int32_t)s_calib.dig_T3)) >> 14;
    s_t_fine = var1 + var2;
    T = (s_t_fine * 5 + 128) >> 8;

    return T;
}

static uint32_t bmp280_compensate_pressure(int32_t adc_P)
{
    int64_t var1;
    int64_t var2;
    int64_t p;

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

uint8_t bmp280_init(uint8_t dev_addr_7bit)
{
    uint8_t chip_id = 0U;

    s_bmp280_addr = dev_addr_7bit;
    s_inited = 0U;

    /* 按官方 demo 的顺序完成 I2C 初始化 */
    rcu_config();
    gpio_config();
    i2c_config();
    
    /* 先读 CHIP ID，确认器件存在且地址正确 */
    if(bmp280_read_chip_id(&chip_id) == 0U) {
       gd_eval_led_on(LED4);
        return 0U;
    }
    if(chip_id != BMP280_CHIP_ID_EXPECTED) {
        gd_eval_led_on(LED4);
        return 0U;
    }

    /* 写入官方示例里的关键配置寄存器 */
    if(bmp280_write_reg(BMP280_REG_CTRL_MEAS, BMP280_CTRL_MEAS_VALUE) == 0U) {
        return 0U;
    }
    if(bmp280_write_reg(BMP280_REG_CONFIG, BMP280_CONFIG_VALUE) == 0U) {
        return 0U;
    }

    /* 读取温度/压力校准参数 */
    if(bmp280_read_trim() == 0U) {
        return 0U;
    }

    s_inited = 1U;
    return 1U;
}

uint8_t pressure_get(bmp280_data_t *out)
{
    uint8_t raw[6];
    int32_t adc_T;
    int32_t adc_P;

    if((out == 0) || (s_inited == 0U)) {
        return 0U;
    }

    if(bmp280_read_data(raw, 6U) == 0U) {
        out->temperature_centi_c = 0;
        out->pressure_pa = 0;
        out->valid = 0U;
        out->alarm = 0U;
        return 0U;
    }

    adc_P = ((int32_t)raw[0] << 12) | ((int32_t)raw[1] << 4) | ((int32_t)raw[2] >> 4);
    adc_T = ((int32_t)raw[3] << 12) | ((int32_t)raw[4] << 4) | ((int32_t)raw[5] >> 4);

    out->temperature_centi_c = bmp280_compensate_temperature(adc_T);
    out->pressure_pa = (int32_t)bmp280_compensate_pressure(adc_P);
    out->valid = 1U;
    out->alarm = (uint8_t)(((out->pressure_pa < BMP280_PRESSURE_ALARM_LOW_PA) ||
                            (out->pressure_pa > BMP280_PRESSURE_ALARM_HIGH_PA)) ? 1U : 0U);

    return 1U;
}

uint8_t bmp280_read_once(bmp280_data_t *out)
{
    return pressure_get(out);
}

