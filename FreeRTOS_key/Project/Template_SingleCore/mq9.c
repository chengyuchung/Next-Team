#include "mq9.h"

#include <string.h>
#include "gd32a7xx.h"

/*
 * ============================================================================
 * 模块名称 : mq9
 * 文件功能 : MQ9 DO 数字输入告警判定实现
 *
 * 设计说明 :
 *   - 不再依赖 adc_manager，纯数字输入判定；
 *   - 1 个数字输入通道（PE3, 浮空输入），与 actor.c 的"映射表 + 统一 init
 *     循环"风格保持一致；
 *   - 通过连续确认/解除计数降低瞬时抖动误报；
 *   - 电平判定按 alarm_active_high 决定有效极性（高电平有效 / 低电平有效）。
 * ============================================================================
 */

#define MQ9_DEFAULT_ALARM_ACTIVE_HIGH     0U
#define MQ9_DEFAULT_ALARM_CONFIRM_COUNT   3U
#define MQ9_DEFAULT_ALARM_CLEAR_COUNT     5U
#define MQ9_DEFAULT_SAMPLE_INTERVAL_MS    1000U
#define MQ9_DEFAULT_STARTUP_GUARD_MS      50U

#define MQ9_CH_MAX                         1U

typedef struct {
    uint32_t port;
    uint32_t pin;
} mq9_pin_map_t;

static const mq9_pin_map_t s_pin_map[MQ9_CH_MAX] = {
    { GPIOE, GPIO_PIN_3 },                 /* MQ9 DO 数字输入 (PE3, 浮空输入) */
};

static mq9_config_t s_cfg;
static mq9_status_t s_status;
static uint8_t s_alarm_confirm_count;
static uint8_t s_alarm_clear_count;
static uint32_t s_startup_guard_remaining_ms;

static void mq9_apply_defaults(void)
{
    memset(&s_cfg, 0, sizeof(s_cfg));
    s_cfg.alarm_active_high = MQ9_DEFAULT_ALARM_ACTIVE_HIGH;
    s_cfg.alarm_confirm_count = MQ9_DEFAULT_ALARM_CONFIRM_COUNT;
    s_cfg.alarm_clear_count = MQ9_DEFAULT_ALARM_CLEAR_COUNT;
    s_cfg.sample_interval_ms = MQ9_DEFAULT_SAMPLE_INTERVAL_MS;
}

static void mq9_set_config_internal(const mq9_config_t *config)
{
    if(config == NULL) {
        mq9_apply_defaults();
        return;
    }

    s_cfg = *config;
    if(s_cfg.alarm_confirm_count == 0U) s_cfg.alarm_confirm_count = MQ9_DEFAULT_ALARM_CONFIRM_COUNT;
    if(s_cfg.alarm_clear_count == 0U)   s_cfg.alarm_clear_count   = MQ9_DEFAULT_ALARM_CLEAR_COUNT;
    if(s_cfg.sample_interval_ms == 0U)   s_cfg.sample_interval_ms  = MQ9_DEFAULT_SAMPLE_INTERVAL_MS;
}

void mq9_init(const mq9_config_t *config)
{
    uint8_t i;

    memset(&s_status, 0, sizeof(s_status));
    s_alarm_confirm_count = 0U;
    s_alarm_clear_count = 0U;
    mq9_apply_defaults();
    mq9_set_config_internal(config);

    rcu_periph_clock_enable(RCU_GPIOE);

    for(i = 0U; i < MQ9_CH_MAX; i++) {
        gpio_mode_set(s_pin_map[i].port, GPIO_MODE_INPUT, GPIO_PUPD_NONE, s_pin_map[i].pin);
    }

    /* 启动保护期：刚上电的若干 ms 内 MQ9 模块外部上拉会把 PE3 拉到 VCC，
     * 误触发高电平报警计数。保护期内 s_status.ready=0，get_gas 报告 valid=0，
     * 上层状态机据此忽略告警，避免开机/模块断电瞬间误报。 */
    s_startup_guard_remaining_ms = MQ9_DEFAULT_STARTUP_GUARD_MS;
    s_status.ready = 0U;
}

uint8_t mq9_task(void)
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

    level_observed = 0U;
    for(i = 0U; i < MQ9_CH_MAX; i++) {
        if(gpio_input_bit_get(s_pin_map[i].port, s_pin_map[i].pin) != RESET) {
            level_observed = 1U;
            break;
        }
    }
    s_status.level = level_observed;

    level_active = (s_cfg.alarm_active_high != 0U)
                   ? (s_status.level != 0U)
                   : (s_status.level == 0U);

    if(level_active != 0U) {
        if(s_alarm_confirm_count < 0xFFU) {
            s_alarm_confirm_count++;
        }
        s_alarm_clear_count = 0U;
        if(s_alarm_confirm_count >= s_cfg.alarm_confirm_count) {
            s_status.alarm = 1U;
        }
    } else {
        if(s_alarm_clear_count < 0xFFU) {
            s_alarm_clear_count++;
        }
        s_alarm_confirm_count = 0U;
        if(s_alarm_clear_count >= s_cfg.alarm_clear_count) {
            s_status.alarm = 0U;
        }
    }

    return 1U;
}

uint8_t get_gas(mq9_result_t *result)
{
    if(result == NULL) {
        return 0U;
    }

    result->valid = s_status.ready;
    result->alarm = s_status.alarm;
    return 1U;
}

uint8_t mq9_get_alarm(void)
{
    return s_status.alarm;
}
