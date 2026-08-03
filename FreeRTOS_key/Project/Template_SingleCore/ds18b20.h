#ifndef DS18B20_H
#define DS18B20_H

#include <stdint.h>
#include <stddef.h>
#include "gd32a7xx.h"
#include "gd32a7xx_gpio.h"
#include "gd32a7xx_rcu.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : ds18b20 (底层驱动)
 * 文件功能 : DS18B20 1-Wire 协议时序 + GD32 4 路 GPIO 平台适配
 * 层次说明 :
 *   本文件只负责“怎么和某一路 DS18B20 器件通信”，不含任何业务汇总逻辑
 *   （取最高温、故障统计等在 temp_sensor.c/.h 里实现）。
 *
 * 单位约定 :
 *   - 温度返回值：0.1°C（temperature_tenths）
 *   - 延时参数：us（微秒）
 *   - GPIO 端口/引脚：由 GD32 平台库定义
 * ============================================================================
 */

/*
 * DS18B20 底层总线操作接口。
 * 说明：由平台适配层提供 GPIO 方向切换、读写与微秒级延时实现。
 */
typedef struct {
    void (*set_output)(void *user_ctx);                    /* 配置总线为输出模式 */
    void (*set_input)(void *user_ctx);                     /* 配置总线为输入模式 */
    void (*write_level)(uint8_t level, void *user_ctx);    /* 写总线电平：0/1 */
    uint8_t (*read_level)(void *user_ctx);                 /* 读取总线电平：0/1 */
    void (*delay_us)(uint32_t us, void *user_ctx);         /* 微秒级延时 */
    void *user_ctx;                                        /* 平台上下文透传 */
} ds18b20_bus_ops_t;

typedef struct {
    ds18b20_bus_ops_t bus;                                 /* 总线操作集合 */
} ds18b20_t;

/* ------------------------- 通用 1-Wire DS18B20 接口 ------------------------- */
void ds18b20_init(ds18b20_t *dev, const ds18b20_bus_ops_t *ops);
uint8_t ds18b20_reset(ds18b20_t *dev);
void ds18b20_write_bit(ds18b20_t *dev, uint8_t bit);
uint8_t ds18b20_read_bit(ds18b20_t *dev);
void ds18b20_write_byte(ds18b20_t *dev, uint8_t data);
uint8_t ds18b20_read_byte(ds18b20_t *dev);

/* 启动一次温度转换：复位 -> Skip ROM -> Convert T。
 * 返回 1=检测到器件并已发出转换命令，0=总线上无器件。 */
uint8_t ds18b20_start_conversion(ds18b20_t *dev);

/* 等待转换完成（外部供电时轮询状态位，最多等待转换上限时间）。 */
void ds18b20_wait_conversion(ds18b20_t *dev);

/* 读暂存器并做 CRC8 校验，输出温度（0.1°C）。返回 1=成功，0=CRC 失败/断线。 */
uint8_t ds18b20_read_scratchpad_temp(ds18b20_t *dev, int16_t *temperature_tenths);

/* 单器件一次完整读取：启动转换 -> 等待 -> 读结果。返回 1=成功。 */
uint8_t ds18b20_read_temperature(ds18b20_t *dev, int16_t *temperature_tenths);

/* ---------------------------- GD32 平台适配层 ---------------------------- */
#define DS18B20_GD32_CHANNEL_COUNT 4U

typedef enum {
    DS18B20_GD32_CH0 = 0U,                                 /* 通道0：默认映射 GPIOI.9 */
    DS18B20_GD32_CH1,                                      /* 通道1：默认映射 GPIOI.10 */
    DS18B20_GD32_CH2,                                      /* 通道2：默认映射 GPIOI.11 */
    DS18B20_GD32_CH3,                                      /* 通道3：默认映射 GPIOL.0 */
    DS18B20_GD32_CH_MAX                                    /* 通道数量上界（非有效通道） */
} ds18b20_gd32_channel_t;

typedef struct {
    ds18b20_t dev;                                         /* 该通道的 DS18B20 设备实例 */
    ds18b20_bus_ops_t bus_ops;                             /* 该通道的总线适配实现 */
    uint32_t gpio_port;                                    /* GPIO 端口基址 */
    uint32_t gpio_pin;                                     /* GPIO 引脚掩码 */
    uint8_t valid;                                         /* 通道有效位：1=可用 */
} ds18b20_gd32_channel_handle_t;

/* 平台适配初始化：使能 DWT 延时、初始化 4 路 GPIO/总线对象。 */
void ds18b20_gd32_adapter_init(void);

/* 取某一路的设备句柄，供业务层做并行采集（非法通道返回 NULL）。 */
ds18b20_t *ds18b20_gd32_get_device(ds18b20_gd32_channel_t channel);

/* 查询某一路是否有效（已初始化）。 */
uint8_t ds18b20_gd32_channel_valid(ds18b20_gd32_channel_t channel);

/* 按通道读取单路温度（内部走一次完整 convert+read），返回值单位 0.1°C。 */
uint8_t ds18b20_gd32_read_temperature(ds18b20_gd32_channel_t channel, int16_t *temperature_tenths);

#ifdef __cplusplus
}
#endif

#endif /* DS18B20_H */
