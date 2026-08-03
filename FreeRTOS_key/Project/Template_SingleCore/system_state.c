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
 * 四个状态按温度组成一条链：LOW_TEMP - NORMAL - HIGH_TEMP - DANGER。
 * NORMAL 处于链中间，向任一侧偏离都会离开 NORMAL；回落时只能朝 NORMAL 方向逐级移动。
 *
 *   s_low_temp_fall_confirm_count
 *       LOW_TEMP 回落到 NORMAL 的连续确认计数器。
 *   s_high_temp_fall_confirm_count
 *       HIGH_TEMP 回落到 NORMAL 的连续确认计数器。
 *   s_danger_fall_confirm_count
 *       DANGER 回落到 HIGH_TEMP 的连续确认计数器。
 */
static system_state_status_t s_status;
static system_state_input_t s_last_input;
static uint8_t s_last_input_valid = 0U;
static uint8_t s_initialized = 0U;

static uint8_t s_low_temp_fall_confirm_count = 0U;
static uint8_t s_high_temp_fall_confirm_count = 0U;
static uint8_t s_danger_fall_confirm_count = 0U;





/*
 * system_state_set_next_sample_period
 *   根据当前状态更新下一次温度采样周期。
 *
 *   设计说明：
 *   1) 状态越危险，采样周期越短，这样可以更快捕捉温度变化；
 *   2) NORMAL 统一使用较长的默认周期，用于降低系统负担；
 *   3) LOW_TEMP / HIGH_TEMP / DANGER 则依次提高采样频率，便于更快响应风险升级。
 *
 *   注意：这里仅负责设置“建议采样周期”，真正何时采样仍由外部调度模块决定。
 */
static void system_state_set_next_sample_period(void)
{
    switch(s_status.state) {
    case SYSTEM_STATE_LOW_TEMP:
        s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_LOW_TEMP_SAMPLE_MS;
        break;
    case SYSTEM_STATE_HIGH_TEMP:
        s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_HIGH_TEMP_SAMPLE_MS;
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
 *   3) 对于 NORMAL / LOW_TEMP / HIGH_TEMP / DANGER 这类有效运行状态，
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
       (next == SYSTEM_STATE_LOW_TEMP) ||
       (next == SYSTEM_STATE_HIGH_TEMP) ||
       (next == SYSTEM_STATE_DANGER)) {
        g_system_state_changed_flag = 1U;
    }
}



/*
 * system_state_clear_fall_counters
 *   清空所有回落确认计数器。
 *   当状态发生切换或检测到偏离 NORMAL 的条件时，原有的回落确认信息就不再可信，必须重新累计。
 */
static void system_state_clear_fall_counters(void)
{
    s_low_temp_fall_confirm_count = 0U;
    s_high_temp_fall_confirm_count = 0U;
    s_danger_fall_confirm_count = 0U;
}





/*
 * system_state_has_low_temp
 *   判断当前输入是否满足“低温”条件。
 *   触发来源：
 *     1) 最高温度低于低温阈值（< 15.0°C）。
 */
static uint8_t system_state_has_low_temp(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    return (uint8_t)(input->max_temperature_tenths < (int16_t)SYSTEM_STATE_DEFAULT_LOW_TEMP_TEMP_C);
}

/*
 * system_state_has_high_temp
 *   判断当前输入是否满足“高温预警”条件。
 *   触发来源包括：
 *     1) 最高温度达到高温预警阈值，但尚未达到危险阈值（[27.0°C, 33.0°C)）；
 *     2) 压力异常，需要通过泄压等手段尝试恢复。
 */
static uint8_t system_state_has_high_temp(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    if(input->pressure_alarm != 0U) {
        return 1U;
    }

    return (uint8_t)((input->max_temperature_tenths >= (int16_t)SYSTEM_STATE_DEFAULT_HIGH_TEMP_TEMP_C) &&
                     (input->max_temperature_tenths < (int16_t)SYSTEM_STATE_DEFAULT_DANGER_TEMP_C));
}

/*
 * system_state_has_danger
 *   判断当前输入是否已达到危险区间。
 *   触发来源包括：
 *     1) 气体泄露告警；
 *     2) 最高温度达到危险阈值（>= 33.0°C）。
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
 * system_state_can_fall_from_low_temp
 *   判断是否满足从 LOW_TEMP 回落到 NORMAL 的条件（温度回升到不再低温）。
 *   该函数内部已经包含连续确认逻辑，调用方只需关注最终是否允许回落。
 */
static uint8_t system_state_can_fall_from_low_temp(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    return system_state_handle_fall_confirm(
        (uint8_t)(input->max_temperature_tenths >= (int16_t)SYSTEM_STATE_DEFAULT_LOW_TEMP_TEMP_C),
        &s_low_temp_fall_confirm_count,
        0U);
}

/*
 * system_state_can_fall_from_high_temp
 *   判断是否满足从 HIGH_TEMP 回落到 NORMAL 的条件（温度降回安全区间，且压力无异常）。
 *   该函数内部已经包含连续确认逻辑，调用方只需关注最终是否允许回落。
 */
static uint8_t system_state_can_fall_from_high_temp(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    return system_state_handle_fall_confirm(
        (uint8_t)((input->max_temperature_tenths < (int16_t)SYSTEM_STATE_DEFAULT_HIGH_TEMP_TEMP_C) &&
                  (input->pressure_alarm == 0U)),
        &s_high_temp_fall_confirm_count,
        0U);
}

/*
 * system_state_can_fall_from_danger
 *   判断是否满足从 DANGER 回落到 HIGH_TEMP 的条件（温度降回危险阈值以下，且无气体告警）。
 *   该函数内部已经包含连续确认逻辑，调用方只需关注最终是否允许回落。
 */
static uint8_t system_state_can_fall_from_danger(const system_state_input_t *input)
{
    if(input == NULL) {
        return 0U;
    }

    return system_state_handle_fall_confirm(
        (uint8_t)((input->max_temperature_tenths < (int16_t)SYSTEM_STATE_DEFAULT_DANGER_TEMP_C) &&
                  (input->gas_alarm == 0U)),
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
    uint8_t has_low_temp;
    uint8_t has_high_temp;
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
     * 预先计算各风险等级条件（四者互斥，同一时刻最多一个为真）：
     *   - has_danger    : 气体泄露，或最高温度 >= 33.0°C；
     *   - has_high_temp : 压力异常，或最高温度处于 [27.0°C, 33.0°C)；
     *   - has_low_temp  : 最高温度 < 15.0°C；
     *   - 均不满足时，代表温度处于 [15.0°C, 27.0°C) 安全区间（NORMAL）。
     */
    has_danger = system_state_has_danger(input);
    has_high_temp = (uint8_t)(!has_danger && system_state_has_high_temp(input));
    has_low_temp = (uint8_t)(!has_danger && !has_high_temp &&
                                system_state_has_low_temp(input));

    switch(s_status.state) {
    case SYSTEM_STATE_NORMAL:
        /* NORMAL: 正常运行状态 */
        s_status.fan_enable = 1U;
        s_status.fan_duty_percent = 50U;        /* 风扇 50% 占空比 */
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 50U;       /* 水泵 50% 占空比 */
        s_status.gate_enable = 0U;              /* 排气阀关闭 */
        /* 关闭所有 PTC 加热片，关闭所有制冷片 */
        for(i = 0U; i < 4U; i++) {
            s_status.heater_enable[i] = 0U;
            s_status.cooler_enable[i] = 0U;
        }
        s_status.buzzer_enable = 0U;            /* 蜂鸣器关闭 */
        if(has_danger != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_DANGER, now_ms);
        } else if(has_high_temp != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_HIGH_TEMP, now_ms);
        } else if(has_low_temp != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_LOW_TEMP, now_ms);
        }
        break;

    case SYSTEM_STATE_LOW_TEMP:
        /* LOW_TEMP: 低温状态 */
        s_status.fan_enable = 0U;
        s_status.fan_duty_percent = 0U;         /* 风扇关闭 */
        s_status.pump_enable = 0U;
        s_status.pump_duty_percent = 0U;        /* 水泵关闭 */
        s_status.gate_enable = 0U;              /* 排气阀关闭 */
        /* 启动 4 路 PTC 加热片，关闭所有制冷片 */
        for(i = 0U; i < 4U; i++) {
            s_status.heater_enable[i] = 1U;
            s_status.cooler_enable[i] = 0U;
        }
        s_status.buzzer_enable = 0U;            /* 蜂鸣器关闭 */
        if(has_danger != 0U) {
            /* 温度骤升或气体告警：跨级快速切换到 DANGER，不额外延迟 */
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_DANGER, now_ms);
        } else if(has_high_temp != 0U) {
            /* 压力异常或温度骤升：跨级快速切换到 HIGH_TEMP，不额外延迟 */
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_HIGH_TEMP, now_ms);
        } else if(has_low_temp != 0U) {
            s_low_temp_fall_confirm_count = 0U;
        } else if(system_state_can_fall_from_low_temp(input) != 0U) {
            system_state_enter(SYSTEM_STATE_NORMAL, now_ms);
            system_state_clear_fall_counters();
        }
        break;

    case SYSTEM_STATE_HIGH_TEMP:
        /* HIGH_TEMP: 高温预警状态 */
        s_status.fan_enable = 1U;
        s_status.fan_duty_percent = 80U;        /* 风扇 80% 占空比 */
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 80U;       /* 水泵 80% 占空比 */
        s_status.gate_enable = 1U;              /* 打开排气阀泄压 */
        /* 关闭所有 PTC 加热片，关闭所有制冷片 */
        for(i = 0U; i < 4U; i++) {
            s_status.heater_enable[i] = 0U;
            s_status.cooler_enable[i] = 0U;
        }
        s_status.buzzer_enable = 0U;            /* 蜂鸣器关闭 */
        if(has_danger != 0U) {
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_DANGER, now_ms);
        } else if(has_low_temp != 0U) {
            /* 温度骤降：跨级快速切换到 LOW_TEMP，不额外延迟 */
            system_state_clear_fall_counters();
            system_state_enter(SYSTEM_STATE_LOW_TEMP, now_ms);
        } else if(has_high_temp != 0U) {
            s_high_temp_fall_confirm_count = 0U;
        } else if(system_state_can_fall_from_high_temp(input) != 0U) {
            system_state_enter(SYSTEM_STATE_NORMAL, now_ms);
            system_state_clear_fall_counters();
        }
        break;

    case SYSTEM_STATE_DANGER:
    default:
        /* DANGER: 危险紧急状态 */
        s_status.fan_enable = 1U;
        s_status.fan_duty_percent = 100U;       /* 风扇 100% 全速运行 */
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 100U;      /* 水泵 100% 全速运行 */
        s_status.gate_enable = 1U;              /* 打开排气阀泄压 */
        /* 关闭所有 PTC 加热片，全开 4 路 TEC 制冷片强制降温 */
        for(i = 0U; i < 4U; i++) {
            s_status.heater_enable[i] = 0U;
            s_status.cooler_enable[i] = 1U;
        }
        s_status.buzzer_enable = 1U;            /* 开启蜂鸣器报警 */
        if(has_danger != 0U) {
            s_danger_fall_confirm_count = 0U;
        } else if(system_state_can_fall_from_danger(input) != 0U) {
            /* 回落只能逐级进行：DANGER 只能先降到 HIGH_TEMP，不允许跳过 */
            system_state_enter(SYSTEM_STATE_HIGH_TEMP, now_ms);
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



