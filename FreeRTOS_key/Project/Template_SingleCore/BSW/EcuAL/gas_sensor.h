#ifndef GAS_SENSOR_H
#define GAS_SENSOR_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : gas_sensor
 * 文件功能 : MQ9 气体传感器 ECUAL 层 - 业务逻辑封装
 * 层次说明 :
 *   本文件封装 MCAL 层的 GPIO 读取，提供气体报警判定、抖动抑制等业务逻辑
 *   具体 GPIO 操作由 ../../MCAL/mq9_mcal.c/.h 提供
 * ============================================================================
 */

/* 气体传感器配置 */
typedef struct {
    uint8_t alarm_active_high;          /* DO 有效电平：1=高电平报警，0=低电平报警 */
    uint8_t alarm_confirm_count;        /* 连续有效确认次数 */
    uint8_t alarm_clear_count;          /* 连续无效解除次数 */
    uint32_t sample_interval_ms;        /* 建议采样周期（ms） */
} gas_sensor_config_t;

/* 气体传感器状态 */
typedef struct {
    uint8_t ready;                      /* 就绪位：1=已就绪 */
    uint8_t alarm;                      /* 告警位：1=报警 */
    uint8_t level;                      /* 最近一次 DO 原始电平（0/1） */
} gas_sensor_status_t;

/* 气体传感器结果 */
typedef struct {
    uint8_t valid;                      /* 1=有效 */
    uint8_t alarm;                      /* 1=气体泄露报警 */
} gas_sensor_result_t;

/* 默认配置 */
#define GAS_SENSOR_DEFAULT_ALARM_ACTIVE_HIGH     0U
#define GAS_SENSOR_DEFAULT_ALARM_CONFIRM_COUNT   3U
#define GAS_SENSOR_DEFAULT_ALARM_CLEAR_COUNT     5U
#define GAS_SENSOR_DEFAULT_SAMPLE_INTERVAL_MS    1000U
#define GAS_SENSOR_DEFAULT_STARTUP_GUARD_MS       50U

/* 气体传感器 ECUAL 层初始化 */
void gas_sensor_init(const gas_sensor_config_t *config);

/* 轮询一次气体传感器，更新内部状态 */
uint8_t gas_sensor_task(void);

/* 获取气体检测结果 */
uint8_t get_gas(gas_sensor_result_t *result);

/* 直接读取当前气体告警位 */
uint8_t gas_sensor_get_alarm(void);

#ifdef __cplusplus
}
#endif

#endif /* GAS_SENSOR_H */
