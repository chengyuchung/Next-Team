#include "gas_sensor.h"
#include "../../MCAL/mq9_mcal.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : gas_sensor
 * 文件功能 : MQ9 气体传感器 ECUAL 层 - 业务逻辑封装
 * 层次说明 :
 *   本文件封装 MCAL 层的 GPIO 读取，提供气体报警判定、抖动抑制等业务逻辑
 * ============================================================================
 */

#define GAS_SENSOR_CHANNEL_MAX  1U

static gas_sensor_config_t s_config;
static gas_sensor_status_t s_status;
static uint8_t s_alarm_confirm_count;
static uint8_t s_alarm_clear_count;
static uint32_t s_startup_guard_remaining_ms;

static void gas_sensor_apply_defaults(void)
{
    memset(&s_config, 0, sizeof(s_config));
    s_config.alarm_active_high = GAS_SENSOR_DEFAULT_ALARM_ACTIVE_HIGH;
    s_config.alarm_confirm_count = GAS_SENSOR_DEFAULT_ALARM_CONFIRM_COUNT;
    s_config.alarm_clear_count = GAS_SENSOR_DEFAULT_ALARM_CLEAR_COUNT;
    s_config.sample_interval_ms = GAS_SENSOR_DEFAULT_SAMPLE_INTERVAL_MS;
}

static void gas_sensor_set_config_internal(const gas_sensor_config_t *config)
{
    if(config == NULL) {
        gas_sensor_apply_defaults();
        return;
    }

    s_config = *config;
    if(s_config.alarm_confirm_count == 0U) s_config.alarm_confirm_count = GAS_SENSOR_DEFAULT_ALARM_CONFIRM_COUNT;
    if(s_config.alarm_clear_count == 0U)   s_config.alarm_clear_count   = GAS_SENSOR_DEFAULT_ALARM_CLEAR_COUNT;
    if(s_config.sample_interval_ms == 0U) s_config.sample_interval_ms  = GAS_SENSOR_DEFAULT_SAMPLE_INTERVAL_MS;
}

void gas_sensor_init(const gas_sensor_config_t *config)
{
    memset(&s_status, 0, sizeof(s_status));
    s_alarm_confirm_count = 0U;
    s_alarm_clear_count = 0U;
    gas_sensor_apply_defaults();
    gas_sensor_set_config_internal(config);

    /* 初始化 MCAL 层 GPIO */
    mq9_mcal_init();

    /* 启动保护期：刚上电的若干 ms 内 MQ9 模块外部上拉会把 PE3 拉到 VCC，
     * 误触发高电平报警计数。保护期内 s_status.ready=0，get_gas 报告 valid=0，
     * 上层状态机据此忽略告警，避免开机/模块断电瞬间误报。 */
    s_startup_guard_remaining_ms = GAS_SENSOR_DEFAULT_STARTUP_GUARD_MS;
    s_status.ready = 0U;
}

uint8_t gas_sensor_task(void)
{
    uint8_t level_active;
    uint8_t level_observed;
    uint8_t i;

    if(s_startup_guard_remaining_ms > 0U) {
        s_startup_guard_remaining_ms--;
        s_status.level = 0U;
        s_status.alarm = 0U;
        s_status.ready = 0U;
        s_alarm_confirm_count = 0U;
        s_alarm_clear_count = 0U;
        return 1U;
    }
    s_status.ready = 1U;

    /* 读取 MCAL 层的 GPIO 电平 */
    level_observed = 0U;
    for(i = 0U; i < GAS_SENSOR_CHANNEL_MAX; i++) {
        if(mq9_mcal_read_digital_input(i) != 0U) {
            level_observed = 1U;
            break;
        }
    }
    s_status.level = level_observed;

    /* 根据配置判断是否激活报警 */
    level_active = (s_config.alarm_active_high != 0U)
                   ? (s_status.level != 0U)
                   : (s_status.level == 0U);

    /* 抖动抑制逻辑 */
    if(level_active != 0U) {
        if(s_alarm_confirm_count < 0xFFU) {
            s_alarm_confirm_count++;
        }
        s_alarm_clear_count = 0U;
        if(s_alarm_confirm_count >= s_config.alarm_confirm_count) {
            s_status.alarm = 1U;
        }
    } else {
        if(s_alarm_clear_count < 0xFFU) {
            s_alarm_clear_count++;
        }
        s_alarm_confirm_count = 0U;
        if(s_alarm_clear_count >= s_config.alarm_clear_count) {
            s_status.alarm = 0U;
        }
    }

    return 1U;
}

uint8_t get_gas(gas_sensor_result_t *result)
{
    if(result == NULL) {
        return 0U;
    }

    result->valid = s_status.ready;
    result->alarm = s_status.alarm;
    return 1U;
}

uint8_t gas_sensor_get_alarm(void)
{
    return s_status.alarm;
}
