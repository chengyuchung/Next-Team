#include "system_state.h"

#include <string.h>

/*
 * 外部状态变化标志
 *   由状态机在发生有效状态切换时置位，通常由主循环或上层任务轮询处理。
 *   它只表示“状态已经变化”，不直接代表故障、告警或安全锁定。
 */
extern volatile uint8_t g_system_state_changed_flag;

/*
 * 模块内部状态
 *   s_status
 *       状态机当前对外输出的状态快照。
 *   s_initialized
 *       标记状态机是否已经完成过首次初始化，避免未初始化时直接进入完整判断流程。
 *   s_normal_fall_confirm_count
 *       PRE_WARNING 回落到 NORMAL 的连续确认计数器。
 *   s_warning_fall_confirm_count
 *       WARNING 回落到 PRE_WARNING 的连续确认计数器。
 *   s_danger_fall_confirm_count
 *       DANGER 回落到 WARNING 的连续确认计数器。
 */
static system_state_status_t s_status;
static system_state_input_t s_last_input;
static uint8_t s_last_input_valid = 0U;
static uint8_t s_initialized = 0U;

static uint8_t s_normal_fall_confirm_count = 0U;
static uint8_t s_warning_fall_confirm_count = 0U;
static uint8_t s_danger_fall_confirm_count = 0U;





/*
 * system_state_set_next_sample_period
 *   根据当前状态更新下一次温度采样周期。
 *
 *   设计说明：
 *   1) 状态越危险，采样周期越短，这样可以更快捕捉温度变化；
 *   2) NORMAL 统一使用较长的默认周期，用于降低系统负担；
 *   3) PRE_WARNING / WARNING / DANGER 则依次提高采样频率，便于更快响应风险升级。
 *
 *   注意：这里仅负责设置“建议采样周期”，真正何时采样仍由外部调度模块决定。
 */
static void system_state_set_next_sample_period(void)
{
    switch(s_status.state) {
    case SYSTEM_STATE_PRE_WARNING:
        s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_PRE_WARNING_SAMPLE_MS;
        break;
    case SYSTEM_STATE_WARNING:
        s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_WARNING_SAMPLE_MS;
        break;
    case SYSTEM_STATE_DANGER:
        s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_DANGER_SAMPLE_MS;
        break;
    case SYSTEM_STATE_NORMAL:
    default:
        s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_NORMAL_SAMPLE_MS;
        break;
    }
}





/*
 * system_state_sync_common_outputs
 *   在每次状态机运行开始时，先把输出清理到一个统一的基础态。
 *
 *   这样做的目的有两个：
 *   1) 避免上一轮 task 计算出来的结果残留到下一轮；
 *   2) 让后续状态分支只需要在基础值上按需赋值，逻辑更清楚。
 *
 *   当前函数只负责清零/重置本轮计算相关的通用输出，不负责具体状态判断。
 */
static void system_state_sync_common_outputs(uint32_t now_ms)
{
    uint8_t i;
    s_status.state_changed = 0U;
    s_status.fan_enable = 0U;
    s_status.fan_duty_percent = 0U;
    s_status.pump_enable = 0U;
    s_status.pump_duty_percent = 0U;
    s_status.gate_enable = 0U;
    for(i = 0U; i < 4U; i++) {
        s_status.cooler_enable[i] = 0U;
        s_status.heater_enable[i] = 0U;
    }
    s_status.buzzer_enable = 0U;
    g_system_state_changed_flag = 0U;
}




/*
 * system_state_enter
 *   切换到目标状态。
 *
 *   处理逻辑：
 *   1) 如果目标状态与当前状态相同，则认为本次没有发生状态切换；
 *   2) 如果状态确实发生变化，则更新当前状态，并标记 state_changed；
 *   3) 对于 NORMAL / PRE_WARNING / WARNING / DANGER 这类有效运行状态，
 *      额外置位全局状态变化标志，便于外部模块轮询处理。
 *
 *   参数说明：
 *   next   : 需要切换到的目标状态；
 *   now_ms : 当前系统时间戳。当前版本暂未记录到状态快照中，保留该参数主要用于后续扩展。
 */
static void system_state_enter(system_state_t next, uint32_t now_ms)
{
    if(s_status.state == next) {
        s_status.state_changed = 0U;
        return;
    }

    s_status.state = next;
    s_status.state_changed = 1U;

    if((next == SYSTEM_STATE_NORMAL) ||
       (next == SYSTEM_STATE_PRE_WARNING) ||
       (next == SYSTEM_STATE_WARNING) ||
       (next == SYSTEM_STATE_DANGER)) {
        g_system_state_changed_flag = 1U;
    }
}



/*
 * system_state_clear_fall_counters
 *   清空所有降级确认计数器。
 *   当状态发生切换或检测到更高风险时，原有的回落确认信息就不再可信，必须重新累计。
 */
static void system_state_clear_fall_counters(void)
{
    s_normal_fall_confirm_count = 0U;
    s_warning_fall_confirm_count = 0U;
    s_danger_fall_confirm_count = 0U;
}





/*
 * system_state_has_pre_warning
 *   判断当前输入是否满足“预警”条件。
 *   触发来源：
 *     1) 最高温度进入预警区间，但尚未达到危险阈值；
 */
static uint8_t system_state_has_pre_warning(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    return (uint8_t)((input->max_temperature_tenths >= (int16_t)SYSTEM_STATE_DEFAULT_PRE_WARNING_TEMP_C) &&
                     (input->max_temperature_tenths < (int16_t)SYSTEM_STATE_DEFAULT_WARNING_TEMP_C));
}

/*
 * system_state_has_warning
 *   判断当前输入是否满足“警告”条件。
 *   触发来源包括：
 *     1) 最高温度进入警告区间，但尚未达到最高危险阈值；
 *     2) 压力异常，需要通过泄压等手段尝试恢复。
 */
static uint8_t system_state_has_warning(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    if(input->pressure_alarm != 0U) {
        return 1U;
    }

    return (uint8_t)((input->max_temperature_tenths >= (int16_t)SYSTEM_STATE_DEFAULT_WARNING_TEMP_C) &&
                     (input->max_temperature_tenths < (int16_t)SYSTEM_STATE_DEFAULT_DANGER_TEMP_C));
}

/*
 * system_state_has_danger
 *   判断当前输入是否已达到最高危险区间。
 *   触发来源包括：
 *     1) 气体泄露告警；
 *     2) 最高温度进入最高危险区间。
 *
 *   一旦满足任一条件，应立即进入 DANGER。
 */
static uint8_t system_state_has_danger(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    if(input->gas_alarm != 0U) {
        return 1U;
    }

    return (uint8_t)(input->max_temperature_tenths >= (int16_t)SYSTEM_STATE_DEFAULT_DANGER_TEMP_C);
}

/*
 * system_state_handle_fall_confirm
 *   处理回落确认计数。
 *   当基础回落条件持续成立时进行计数；当条件被打断时清零。
 *   只有连续满足确认次数阈值，才返回 1，表示允许进入目标状态。
 */
static uint8_t system_state_handle_fall_confirm(uint8_t condition_met,
                                                uint8_t *counter,
                                                uint8_t clear_counter_value)
{
    if(counter == NULL) {
        return 0U;
    }

    if(condition_met == 0U) {
        *counter = 0U;
        return 0U;
    }

    if(*counter < SYSTEM_STATE_DEFAULT_FALLBACK_CONFIRM_COUNT) {
        (*counter)++;
    }

    if(*counter >= SYSTEM_STATE_DEFAULT_FALLBACK_CONFIRM_COUNT) {
        *counter = clear_counter_value;
        return 1U;
    }

    return 0U;
}

/*
 * system_state_can_fall_to_normal
 *   判断是否满足从 PRE_WARNING 回落到 NORMAL 的条件。
 *   该函数内部已经包含连续确认逻辑，调用方只需关注最终是否允许回落。
 */
static uint8_t system_state_can_fall_to_normal(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    return system_state_handle_fall_confirm(
        (uint8_t)(input->max_temperature_tenths < (int16_t)(SYSTEM_STATE_DEFAULT_PRE_WARNING_TEMP_C - SYSTEM_STATE_DEFAULT_CLEAR_HYSTERESIS_C)),
        &s_normal_fall_confirm_count,
        0U);
}

/*
 * system_state_can_fall_to_pre_warning_from_warning
 *   判断是否满足从 WARNING 回落到 PRE_WARNING 的条件。
 *   该函数内部已经包含连续确认逻辑，调用方只需关注最终是否允许回落。
 */
static uint8_t system_state_can_fall_to_pre_warning_from_warning(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    return system_state_handle_fall_confirm(
        (uint8_t)(input->max_temperature_tenths < (int16_t)(SYSTEM_STATE_DEFAULT_WARNING_TEMP_C - SYSTEM_STATE_DEFAULT_CLEAR_HYSTERESIS_C)),
        &s_warning_fall_confirm_count,
        0U);
}

/*
 * system_state_can_fall_to_warning_from_danger
 *   判断是否满足从 DANGER 回落到 WARNING 的条件。
 *   该函数内部已经包含连续确认逻辑，调用方只需关注最终是否允许回落。
 */
static uint8_t system_state_can_fall_to_warning_from_danger(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    return system_state_handle_fall_confirm(
        (uint8_t)(input->max_temperature_tenths < (int16_t)(SYSTEM_STATE_DEFAULT_DANGER_TEMP_C - SYSTEM_STATE_DEFAULT_CLEAR_HYSTERESIS_C)),
        &s_danger_fall_confirm_count,
        0U);
}

/*
 * system_state_init
 *   完成状态机的首次初始化。
 *   初始化后系统会处于 NORMAL 状态，并准备好默认配置和输出快照。
 */
void system_state_init(void)
{
    memset(&s_status, 0, sizeof(s_status));
    memset(&s_last_input, 0, sizeof(s_last_input));
    s_status.state = SYSTEM_STATE_NORMAL;
    s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_NORMAL_SAMPLE_MS;
    s_last_input_valid = 0U;
    s_initialized = 1U;
    system_state_clear_fall_counters();
}

/**
 * @brief 重置系统状态到初始默认值。
 *
 * 该函数将全局系统状态结构体清零，并重新初始化关键成员变量，
 * 包括设置初始状态、启用系统、配置默认采样间隔以及标记系统已初始化。
 * 同时，它还会清除相关的故障计数器。
 *
 * @param void 无参数
 * @return void 无返回值
 */
void system_state_reset(void)
{
    /* 清零整个系统状态结构体 */
    memset(&s_status, 0, sizeof(s_status));
    memset(&s_last_input, 0, sizeof(s_last_input));

    /* 初始化关键状态字段 */
    s_status.state = SYSTEM_STATE_NORMAL;
    s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_NORMAL_SAMPLE_MS;

    /* 标记系统已完成初始化 */
    s_last_input_valid = 0U;
    s_initialized = 1U;

    /* 清除故障计数器 */
    system_state_clear_fall_counters();
}


void system_state_task(const system_state_input_t *input)
{
    uint32_t now_ms;
    uint8_t has_pre_warning;
    uint8_t has_warning;
    uint8_t has_danger;
    uint8_t i;

    if(s_initialized == 0U) {
        system_state_init();
    }

    if(input != NULL) {
        s_last_input = *input;
        s_last_input_valid = 1U;
    }

    now_ms = (input != NULL) ? input->now_ms : 0U;
    system_state_sync_common_outputs(now_ms);

    if(input == NULL) {
        system_state_set_next_sample_period();
        return;
    }

    /*
     * 预先计算各风险等级条件：
     *   - 气体泄露直接进入最高危险，判定由 system_state_has_danger() 统一负责；
     *   - 压力异常归入警告，判定由 system_state_has_warning() 统一负责；
     *   - 温度按门槛分级进入预警/警告/危险。
     */
    has_danger = system_state_has_danger(input);
    has_warning = (uint8_t)(!has_danger && system_state_has_warning(input));
    has_pre_warning = (uint8_t)(!has_danger && !has_warning &&
                                system_state_has_pre_warning(input));

    switch(s_status.state) {
    case SYSTEM_STATE_NORMAL:
        s_status.fan_enable = 0U;
        s_status.fan_duty_percent = 0U;
        s_status.pump_enable = 0U;
        s_status.pump_duty_percent = 0U;
        s_status.gate_enable = 0U;
        /* NORMAL: 4个PTC加热片全部开启，制冷片关闭 */
        for(i = 0U; i < 4U; i++) {
            s_status.cooler_enable[i] = 0U;
            s_status.heater_enable[i] = 1U;
        }
        s_status.buzzer_enable = 0U;
        if(has_danger != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_DANGER, now_ms);
        } else if(has_warning != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_WARNING, now_ms);
        } else if(has_pre_warning != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_PRE_WARNING, now_ms);
        }
        break;

    case SYSTEM_STATE_PRE_WARNING:
        s_status.fan_enable = 1;
        s_status.fan_duty_percent = 80U;
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 80U;
        s_status.gate_enable = 0U;
        /* PRE_WARNING: 关闭所有PTC加热片，启动4路制冷 */
        for(i = 0U; i < 4U; i++) {
            s_status.cooler_enable[i] = 1U;
            s_status.heater_enable[i] = 0U;
        }
        s_status.buzzer_enable = 0U;
        if(has_danger != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_DANGER, now_ms);
        } else if(has_warning != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_WARNING, now_ms);
        } else if(system_state_can_fall_to_normal(input) != 0U) {
            system_state_enter(SYSTEM_STATE_NORMAL, now_ms);
            system_state_clear_fall_counters();
        }
        break;

    case SYSTEM_STATE_WARNING:
        s_status.fan_enable = 1U;
        s_status.fan_duty_percent = 80U;
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 80U;
        s_status.gate_enable = 1U;
        /* WARNING: 4路制冷片全开，PTC加热片全开（混合控温策略） */
        for(i = 0U; i < 4U; i++) {
            s_status.cooler_enable[i] = 1U;
            s_status.heater_enable[i] = 1U;
        }
        s_status.buzzer_enable = 0U;
        if(has_danger != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_DANGER, now_ms);
        } else if(has_warning != 0U) {
            s_warning_fall_confirm_count = 0U;
        } else if(system_state_can_fall_to_pre_warning_from_warning(input) != 0U) {
            system_state_enter(SYSTEM_STATE_PRE_WARNING, now_ms);
            system_state_clear_fall_counters();
        }
        break;

    case SYSTEM_STATE_DANGER:
    default:
        s_status.fan_enable = 1U;
        s_status.fan_duty_percent = 100U;
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 100U;
        s_status.gate_enable = 1U;
        /* DANGER: 4路制冷片全开，关闭所有PTC加热片，全力制冷+泄压 */
        for(i = 0U; i < 4U; i++) {
            s_status.cooler_enable[i] = 1U;
            s_status.heater_enable[i] = 0U;
        }
        s_status.buzzer_enable = 1U;
        if(has_danger != 0U) {
            s_danger_fall_confirm_count = 0U;
        } else if(system_state_can_fall_to_warning_from_danger(input) != 0U) {
            system_state_enter(SYSTEM_STATE_WARNING, now_ms);
            system_state_clear_fall_counters();
        }
        break;
    }

    system_state_set_next_sample_period();
}

void system_state_get_status(system_state_status_t *status)
{
    if(status != NULL) {
        *status = s_status;
    }
}

void system_state_get_input(system_state_input_t *input)
{
    if((input != NULL) && (s_last_input_valid != 0U)) {
        *input = s_last_input;
    } else if(input != NULL) {
        memset(input, 0, sizeof(*input));
    }
}

system_state_t system_state_get_state(void)
{
    return s_status.state;
}



