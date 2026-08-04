#include "system_state.h"

#include <string.h>

/*
 * 运行时可配置参数定义（通过 CAN 0x20 配置类命令动态修改）
 */
uint16_t g_low_temp_threshold_tenths    = SYSTEM_STATE_DEFAULT_LOW_TEMP_TEMP_C;
uint16_t g_high_temp_threshold_tenths   = SYSTEM_STATE_DEFAULT_HIGH_TEMP_TEMP_C;
uint16_t g_danger_temp_threshold_tenths = SYSTEM_STATE_DEFAULT_DANGER_TEMP_C;
uint8_t g_fallback_confirm_count        = SYSTEM_STATE_DEFAULT_FALLBACK_CONFIRM_COUNT;

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
 *
 * 分区独立状态机说明
 *   4个分区（对应加热片/制冷片编号1-4）各自独立维护一条状态链：
 *   LOW_TEMP - NORMAL - HIGH_TEMP - DANGER。NORMAL 处于链中间，向任一侧
 *   偏离都会离开 NORMAL；回落时只能朝 NORMAL 方向逐级移动，不能跨级。
 *   气体告警(gas_alarm)/压力告警(pressure_alarm)是全局传感器输入，会
 *   同时参与每个分区自己的 has_danger/has_high_temp 判断，因此天然对
 *   4个分区都生效（气体告警使4个分区都进入DANGER；压力告警使4个
 *   分区都至少到HIGH_TEMP）。
 *
 *   s_zone_low_temp_fall_confirm_count[4]
 *       每个分区 LOW_TEMP 回落到 NORMAL 的连续确认计数器。
 *   s_zone_high_temp_fall_confirm_count[4]
 *       每个分区 HIGH_TEMP 回落到 NORMAL 的连续确认计数器。
 *   s_zone_danger_fall_confirm_count[4]
 *       每个分区 DANGER 回落到 HIGH_TEMP 的连续确认计数器。
 *
 * 全局状态归约
 *   s_status.state 是4个分区 zone_state[] 按危险度归约后的结果：
 *   DANGER > HIGH_TEMP > LOW_TEMP > NORMAL，取其中最严重的作为全局状态，
 *   每一轮直接重新计算，不再额外叠加滞回（分区级已经各自做过滞回）。
 *   风扇/水泵/泄压阀/蜂鸣器/点火许可等共享设备统一按这个全局状态驱动。
 */
static system_state_status_t s_status;
static system_state_input_t s_last_input;
static uint8_t s_last_input_valid = 0U;
static uint8_t s_initialized = 0U;

static uint8_t s_zone_low_temp_fall_confirm_count[4] = {0U, 0U, 0U, 0U};
static uint8_t s_zone_high_temp_fall_confirm_count[4] = {0U, 0U, 0U, 0U};
static uint8_t s_zone_danger_fall_confirm_count[4] = {0U, 0U, 0U, 0U};





/*
 * system_state_severity
 *   将状态映射为危险度数值，数值越大越危险：
 *   DANGER(3) > HIGH_TEMP(2) > LOW_TEMP(1) > NORMAL(0)。
 *   仅用于4个分区状态之间的归约比较，不代表状态链本身的温度顺序。
 */
static uint8_t system_state_severity(system_state_t state)
{
    switch(state) {
    case SYSTEM_STATE_DANGER:
        return 3U;
    case SYSTEM_STATE_HIGH_TEMP:
        return 2U;
    case SYSTEM_STATE_LOW_TEMP:
        return 1U;
    case SYSTEM_STATE_NORMAL:
    default:
        return 0U;
    }
}

/*
 * system_state_reduce_zone_states
 *   在4个分区当前状态中取危险度最高的一个，作为全局状态。
 */
static system_state_t system_state_reduce_zone_states(void)
{
    system_state_t worst = s_status.zone_state[0];
    uint8_t i;

    for(i = 1U; i < 4U; i++) {
        if(system_state_severity(s_status.zone_state[i]) > system_state_severity(worst)) {
            worst = s_status.zone_state[i];
        }
    }

    return worst;
}

/*
 * system_state_zone_apply_outputs
 *   根据分区状态设置该分区的加热片/制冷片使能。
 *   与原整体状态机的对应关系一致：
 *     LOW_TEMP  : 加热片开，制冷片关；
 *     DANGER    : 加热片关，制冷片开；
 *     NORMAL/HIGH_TEMP : 加热片、制冷片均关。
 */
static void system_state_zone_apply_outputs(uint8_t zone_idx, system_state_t state)
{
    switch(state) {
    case SYSTEM_STATE_LOW_TEMP:
        s_status.heater_enable[zone_idx] = 1U;
        s_status.cooler_enable[zone_idx] = 0U;
        break;
    case SYSTEM_STATE_DANGER:
        s_status.heater_enable[zone_idx] = 0U;
        s_status.cooler_enable[zone_idx] = 1U;
        break;
    case SYSTEM_STATE_NORMAL:
    case SYSTEM_STATE_HIGH_TEMP:
    default:
        s_status.heater_enable[zone_idx] = 0U;
        s_status.cooler_enable[zone_idx] = 0U;
        break;
    }
}

/*
 * system_state_apply_global_outputs
 *   根据4个分区归约后的全局状态，驱动风扇/水泵/泄压阀/蜂鸣器/点火许可
 *   这些共享设备。数值与原整体状态机完全一致。
 */
static void system_state_apply_global_outputs(system_state_t state)
{
    switch(state) {
    case SYSTEM_STATE_LOW_TEMP:
        s_status.fan_enable = 0U;
        s_status.fan_duty_percent = 0U;
        s_status.pump_enable = 0U;
        s_status.pump_duty_percent = 0U;
        s_status.gate_enable = 0U;
        s_status.buzzer_enable = 0U;
        s_status.ignition_allowed = 1U;
        break;
    case SYSTEM_STATE_HIGH_TEMP:
        s_status.fan_enable = 1U;
        s_status.fan_duty_percent = 80U;
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 80U;
        s_status.gate_enable = 1U;
        s_status.buzzer_enable = 0U;
        s_status.ignition_allowed = 1U;
        break;
    case SYSTEM_STATE_DANGER:
        s_status.fan_enable = 1U;
        s_status.fan_duty_percent = 100U;
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 100U;
        s_status.gate_enable = 1U;
        s_status.buzzer_enable = 1U;
        s_status.ignition_allowed = 0U;
        break;
    case SYSTEM_STATE_NORMAL:
    default:
        s_status.fan_enable = 1U;
        s_status.fan_duty_percent = 50U;
        s_status.pump_enable = 1U;
        s_status.pump_duty_percent = 50U;
        s_status.gate_enable = 0U;
        s_status.buzzer_enable = 0U;
        s_status.ignition_allowed = 1U;
        break;
    }
}

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
    s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_SAMPLE_MS;
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
    s_status.ignition_allowed = 1U;
    g_system_state_changed_flag = 0U;
}




/*
 * system_state_zone_clear_fall_counters
 *   清空指定分区的所有回落确认计数器。
 *   当该分区状态发生切换或检测到偏离 NORMAL 的条件时，原有的回落确认
 *   信息就不再可信，必须重新累计。
 */
static void system_state_zone_clear_fall_counters(uint8_t zone_idx)
{
    s_zone_low_temp_fall_confirm_count[zone_idx] = 0U;
    s_zone_high_temp_fall_confirm_count[zone_idx] = 0U;
    s_zone_danger_fall_confirm_count[zone_idx] = 0U;
}



/*
 * system_state_zone_has_low_temp
 *   判断指定分区是否满足“低温”条件：该分区温度有效，且低于低温阈值（< 15.0°C）。
 *   分区温度无效时视为不满足（不参与判断，避免传感器故障导致误判）。
 */
static uint8_t system_state_zone_has_low_temp(const system_state_input_t *input, uint8_t zone_idx)
{
    if((input == NULL) || (input->zone_temp_valid[zone_idx] == 0U)) {
        return 0U;
    }

    return (uint8_t)(input->zone_temperature_tenths[zone_idx] < (int16_t)g_low_temp_threshold_tenths);
}

/*
 * system_state_zone_has_high_temp
 *   判断指定分区是否满足“高温预警”条件。
 *   触发来源包括：
 *     1) 该分区温度有效，且处于高温预警阈值区间（[27.0°C, 33.0°C)）；
 *     2) 压力异常（全局传感器输入，强制4个分区均至少进入HIGH_TEMP）。
 */
static uint8_t system_state_zone_has_high_temp(const system_state_input_t *input, uint8_t zone_idx)
{
    int16_t zone_temp;

    if(input == NULL) {
        return 0U;
    }

    if(input->pressure_alarm != 0U) {
        return 1U;
    }

    if(input->zone_temp_valid[zone_idx] == 0U) {
        return 0U;
    }

    zone_temp = input->zone_temperature_tenths[zone_idx];
    return (uint8_t)((zone_temp >= (int16_t)g_high_temp_threshold_tenths) &&
                     (zone_temp < (int16_t)g_danger_temp_threshold_tenths));
}

/*
 * system_state_zone_has_danger
 *   判断指定分区是否已达到危险区间。
 *   触发来源包括：
 *     1) 气体泄露告警（全局传感器输入，强制4个分区均进入DANGER）；
 *     2) 该分区温度有效，且达到危险阈值（>= 33.0°C）。
 */
static uint8_t system_state_zone_has_danger(const system_state_input_t *input, uint8_t zone_idx)
{
    if(input == NULL) {
        return 0U;
    }

    if(input->gas_alarm != 0U) {
        return 1U;
    }

    if(input->zone_temp_valid[zone_idx] == 0U) {
        return 0U;
    }

    return (uint8_t)(input->zone_temperature_tenths[zone_idx] >= (int16_t)g_danger_temp_threshold_tenths);
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

    if(*counter < g_fallback_confirm_count) {
        (*counter)++;
    }

    if(*counter >= g_fallback_confirm_count) {
        *counter = clear_counter_value;
        return 1U;
    }

    return 0U;
}

/*
 * system_state_zone_can_fall_from_low_temp
 *   判断指定分区是否满足从 LOW_TEMP 回落到 NORMAL 的条件（该分区温度回升到不再低温）。
 *   温度无效时视为条件不成立（计数器清零，维持在 LOW_TEMP，避免传感器故障误判）。
 */
static uint8_t system_state_zone_can_fall_from_low_temp(const system_state_input_t *input, uint8_t zone_idx)
{
    uint8_t condition_met = 0U;

    if((input != NULL) && (input->zone_temp_valid[zone_idx] != 0U)) {
        condition_met = (uint8_t)(input->zone_temperature_tenths[zone_idx] >=
                                   (int16_t)g_low_temp_threshold_tenths);
    }

    return system_state_handle_fall_confirm(
        condition_met,
        &s_zone_low_temp_fall_confirm_count[zone_idx],
        0U);
}

/*
 * system_state_zone_can_fall_from_high_temp
 *   判断指定分区是否满足从 HIGH_TEMP 回落到 NORMAL 的条件（该分区温度降回安全区间，且压力无异常）。
 */
static uint8_t system_state_zone_can_fall_from_high_temp(const system_state_input_t *input, uint8_t zone_idx)
{
    uint8_t condition_met = 0U;

    if((input != NULL) && (input->zone_temp_valid[zone_idx] != 0U) && (input->pressure_alarm == 0U)) {
        condition_met = (uint8_t)(input->zone_temperature_tenths[zone_idx] <
                                   (int16_t)g_high_temp_threshold_tenths);
    }

    return system_state_handle_fall_confirm(
        condition_met,
        &s_zone_high_temp_fall_confirm_count[zone_idx],
        0U);
}

/*
 * system_state_zone_can_fall_from_danger
 *   判断指定分区是否满足从 DANGER 回落到 HIGH_TEMP 的条件（该分区温度降回危险阈值以下，且无气体告警）。
 */
static uint8_t system_state_zone_can_fall_from_danger(const system_state_input_t *input, uint8_t zone_idx)
{
    uint8_t condition_met = 0U;

    if((input != NULL) && (input->zone_temp_valid[zone_idx] != 0U) && (input->gas_alarm == 0U)) {
        condition_met = (uint8_t)(input->zone_temperature_tenths[zone_idx] <
                                   (int16_t)g_danger_temp_threshold_tenths);
    }

    return system_state_handle_fall_confirm(
        condition_met,
        &s_zone_danger_fall_confirm_count[zone_idx],
        0U);
}

/*
 * system_state_zone_task
 *   单个分区的独立状态机。
 *   逻辑与原整体状态机完全一致，只是判断依据换成该分区自己的
 *   has_danger_i/has_high_i/has_low_i，计数器也是该分区独立的一份。
 *   处理完成后立即根据分区状态刷新该分区的加热片/制冷片使能。
 */
static void system_state_zone_task(uint8_t zone_idx, const system_state_input_t *input,
                                    uint8_t has_danger_i, uint8_t has_high_i, uint8_t has_low_i)
{
    switch(s_status.zone_state[zone_idx]) {
    case SYSTEM_STATE_NORMAL:
        if(has_danger_i != 0U) {
            system_state_zone_clear_fall_counters(zone_idx);
            s_status.zone_state[zone_idx] = SYSTEM_STATE_DANGER;
        } else if(has_high_i != 0U) {
            system_state_zone_clear_fall_counters(zone_idx);
            s_status.zone_state[zone_idx] = SYSTEM_STATE_HIGH_TEMP;
        } else if(has_low_i != 0U) {
            system_state_zone_clear_fall_counters(zone_idx);
            s_status.zone_state[zone_idx] = SYSTEM_STATE_LOW_TEMP;
        }
        break;

    case SYSTEM_STATE_LOW_TEMP:
        if(has_danger_i != 0U) {
            /* 温度骤升或气体告警：跨级快速切换到 DANGER，不额外延迟 */
            system_state_zone_clear_fall_counters(zone_idx);
            s_status.zone_state[zone_idx] = SYSTEM_STATE_DANGER;
        } else if(has_high_i != 0U) {
            /* 压力异常或温度骤升：跨级快速切换到 HIGH_TEMP，不额外延迟 */
            system_state_zone_clear_fall_counters(zone_idx);
            s_status.zone_state[zone_idx] = SYSTEM_STATE_HIGH_TEMP;
        } else if(has_low_i != 0U) {
            s_zone_low_temp_fall_confirm_count[zone_idx] = 0U;
        } else if(system_state_zone_can_fall_from_low_temp(input, zone_idx) != 0U) {
            s_status.zone_state[zone_idx] = SYSTEM_STATE_NORMAL;
            system_state_zone_clear_fall_counters(zone_idx);
        }
        break;

    case SYSTEM_STATE_HIGH_TEMP:
        if(has_danger_i != 0U) {
            system_state_zone_clear_fall_counters(zone_idx);
            s_status.zone_state[zone_idx] = SYSTEM_STATE_DANGER;
        } else if(has_low_i != 0U) {
            /* 温度骤降：跨级快速切换到 LOW_TEMP，不额外延迟 */
            system_state_zone_clear_fall_counters(zone_idx);
            s_status.zone_state[zone_idx] = SYSTEM_STATE_LOW_TEMP;
        } else if(has_high_i != 0U) {
            s_zone_high_temp_fall_confirm_count[zone_idx] = 0U;
        } else if(system_state_zone_can_fall_from_high_temp(input, zone_idx) != 0U) {
            s_status.zone_state[zone_idx] = SYSTEM_STATE_NORMAL;
            system_state_zone_clear_fall_counters(zone_idx);
        }
        break;

    case SYSTEM_STATE_DANGER:
    default:
        if(has_danger_i != 0U) {
            s_zone_danger_fall_confirm_count[zone_idx] = 0U;
        } else if(system_state_zone_can_fall_from_danger(input, zone_idx) != 0U) {
            /* 回落只能逐级进行：DANGER 只能先降到 HIGH_TEMP，不允许跳过 */
            s_status.zone_state[zone_idx] = SYSTEM_STATE_HIGH_TEMP;
            system_state_zone_clear_fall_counters(zone_idx);
        }
        break;
    }

    system_state_zone_apply_outputs(zone_idx, s_status.zone_state[zone_idx]);
}

/*
 * system_state_init
 *   完成状态机的首次初始化。
 *   初始化后系统会处于 NORMAL 状态，并准备好默认配置和输出快照。
 */
void system_state_init(void)
{
    uint8_t i;

    memset(&s_status, 0, sizeof(s_status));
    memset(&s_last_input, 0, sizeof(s_last_input));
    s_status.state = SYSTEM_STATE_NORMAL;
    s_status.ignition_allowed = 1U;
    s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_SAMPLE_MS;
    for(i = 0U; i < 4U; i++) {
        s_status.zone_state[i] = SYSTEM_STATE_NORMAL;
        system_state_zone_clear_fall_counters(i);
    }
    s_last_input_valid = 0U;
    s_initialized = 1U;
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
    uint8_t i;

    /* 清零整个系统状态结构体 */
    memset(&s_status, 0, sizeof(s_status));
    memset(&s_last_input, 0, sizeof(s_last_input));

    /* 初始化关键状态字段 */
    s_status.state = SYSTEM_STATE_NORMAL;
    s_status.ignition_allowed = 1U;
    s_status.next_temperature_sample_interval_ms = SYSTEM_STATE_DEFAULT_SAMPLE_MS;

    /* 4个分区状态与各自的回落确认计数器一并复位 */
    for(i = 0U; i < 4U; i++) {
        s_status.zone_state[i] = SYSTEM_STATE_NORMAL;
        system_state_zone_clear_fall_counters(i);
    }

    /* 标记系统已完成初始化 */
    s_last_input_valid = 0U;
    s_initialized = 1U;
}


void system_state_task(const system_state_input_t *input)
{
    system_state_t old_global_state;
    system_state_t new_global_state;
    uint8_t zone_idx;

    if(s_initialized == 0U) {
        system_state_init();
    }

    if(input != NULL) {
        s_last_input = *input;
        s_last_input_valid = 1U;
    }

    system_state_sync_common_outputs((input != NULL) ? input->now_ms : 0U);

    if(input == NULL) {
        system_state_apply_global_outputs(s_status.state);
        system_state_set_next_sample_period();
        return;
    }

    old_global_state = s_status.state;

    /*
     * 4个分区各自独立跑一遍状态机：
     *   - 每个分区依据自己的 zone_temperature_tenths[i]/zone_temp_valid[i] 判断；
     *   - gas_alarm/pressure_alarm 是全局传感器输入，会同时参与每个分区的判断；
     *   - 分区状态迁移完成后立即刷新该分区的 heater_enable[i]/cooler_enable[i]。
     */
    for(zone_idx = 0U; zone_idx < 4U; zone_idx++) {
        uint8_t has_danger_i = system_state_zone_has_danger(input, zone_idx);
        uint8_t has_high_i = (uint8_t)(!has_danger_i && system_state_zone_has_high_temp(input, zone_idx));
        uint8_t has_low_i = (uint8_t)(!has_danger_i && !has_high_i &&
                                        system_state_zone_has_low_temp(input, zone_idx));

        system_state_zone_task(zone_idx, input, has_danger_i, has_high_i, has_low_i);
    }

    /*
     * 全局状态归约：取4个分区中危险度最高的作为全局状态，
     * 驱动风扇/水泵/泄压阀/蜂鸣器/点火许可等共享设备。
     */
    new_global_state = system_state_reduce_zone_states();
    s_status.state = new_global_state;
    s_status.state_changed = (uint8_t)(new_global_state != old_global_state);
    if((s_status.state_changed != 0U) &&
       ((new_global_state == SYSTEM_STATE_NORMAL) ||
        (new_global_state == SYSTEM_STATE_LOW_TEMP) ||
        (new_global_state == SYSTEM_STATE_HIGH_TEMP) ||
        (new_global_state == SYSTEM_STATE_DANGER))) {
        g_system_state_changed_flag = 1U;
    }

    system_state_apply_global_outputs(new_global_state);
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



