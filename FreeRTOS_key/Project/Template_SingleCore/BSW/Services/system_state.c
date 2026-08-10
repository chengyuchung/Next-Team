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
 * 温度异常升温预警配置参数（简化版）
 *   DS18B20 采样周期固定（约 1s），直接用相邻两帧温度差判断升温过快，
 *   不再需要时间戳与 EMA 平滑。
 *   阈值单位 0.01°C，可检测细微温度变化。
 */
uint8_t g_temp_prediction_enable        = 1U;   /* 默认开启 */
uint16_t g_temp_rise_danger_threshold   = 30U;  /* 单次升温 >= 0.30°C 视为异常，直接判 DANGER 级别 */
uint16_t g_temp_rise_high_threshold     = 15U;  /* 单次升温 >= 0.15°C 视为偏快，判 HIGH_TEMP 级别 */
uint8_t g_temp_rise_confirm_count       = 2U;   /* 连续 2 帧都超过阈值才触发，过滤单点噪声 */

/*
 * 制冷片轮转配置参数
 */
uint32_t g_cooler_rotate_interval_ms = SYSTEM_STATE_DEFAULT_COOLER_ROTATE_MS;

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
 * 制冷片轮转状态
 *   气体告警触发 DANGER 时，4路制冷片同时需要工作，但电池功率不足以全开。
 *   轮转策略：每次只允许一路处于开启状态，按 DANGER 分区的编号顺序循环，
 *   每隔 g_cooler_rotate_interval_ms 切换到下一路。
 *
 *   s_cooler_rotate_slot  : 当前轮转槽位（0-3，对应制冷片1-4）
 *   s_cooler_rotate_last_ms : 上次切换时的时间戳（来自 input->now_ms）
 */
static uint8_t  s_cooler_rotate_slot   = 0U;
static uint32_t s_cooler_rotate_last_ms = 0U;

/*
 * 温度异常升温预警历史数据（简化版）
 *
 *   DS18B20 采样周期恒定（约1s），不需要基于时间戳计算变化率，
 *   只需比较"当前帧"与"上一帧"的温度差即可判断升温是否过快。
 *   为避免单点噪声（例如某次读数抖动）误触发，要求连续
 *   g_temp_rise_confirm_count 帧都超过阈值才真正触发预警。
 *
 *   s_zone_prev_temp[i]        : 分区 i 上一帧样本温度，单位 0.1°C
 *   s_zone_prev_valid[i]       : 分区 i 上一帧样本是否有效
 *   s_zone_rise_danger_count[i]: 分区 i 连续超过 DANGER 升温阈值的帧数
 *   s_zone_rise_high_count[i]  : 分区 i 连续超过 HIGH_TEMP 升温阈值的帧数
 */
static int16_t s_zone_prev_temp[4] = {0, 0, 0, 0};
static uint8_t s_zone_prev_valid[4] = {0U, 0U, 0U, 0U};
static uint8_t s_zone_rise_danger_count[4] = {0U, 0U, 0U, 0U};
static uint8_t s_zone_rise_high_count[4] = {0U, 0U, 0U, 0U};




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
 *     LOW_TEMP  : 加热片开，制冷片关；
 *     HIGH_TEMP : 加热片关，制冷片关（仅告警，不主动制冷）；
 *     DANGER    : 加热片关，制冷片开；
 *     NORMAL    : 加热片、制冷片均关。
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
    case SYSTEM_STATE_HIGH_TEMP:
    case SYSTEM_STATE_NORMAL:
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
 *   注意：这里仅负责设置"建议采样周期"，真正何时采样仍由外部调度模块决定。
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
    s_status.predictive_alarm = 0U;
    for(i = 0U; i < 4U; i++) {
        s_status.zone_predictive[i] = 0U;
    }
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
 *   判断指定分区是否满足"低温"条件：该分区温度有效，且低于低温阈值（< 15.0°C）。
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
 *   判断指定分区是否满足"高温预警"条件。
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
 * system_state_update_temp_delta
 *   在收到一帧新温度样本时，更新全部 4 个分区的温度变化量（简化版）。
 *
 *   DS18B20 采样周期固定（约 1s），无需时间戳，直接计算
 *   ΔT = T_current - T_prev（单位 0.1°C）。
 *   同时更新连续超阈计数器，用于异常升温预警。
 */
static void system_state_update_temp_delta(const system_state_input_t *input)
{
    uint8_t zone_idx;
    int16_t current_temp;
    int16_t delta;

    if(input == NULL) {
        return;
    }

    for(zone_idx = 0U; zone_idx < 4U; zone_idx++) {
        if(input->zone_temp_valid[zone_idx] == 0U) {
            /* 本帧无效：清除历史基准和计数器，等下次有效帧重建 */
            s_zone_prev_valid[zone_idx] = 0U;
            s_zone_rise_danger_count[zone_idx] = 0U;
            s_zone_rise_high_count[zone_idx] = 0U;
            continue;
        }

        current_temp = input->zone_temperature_tenths[zone_idx];

        if(s_zone_prev_valid[zone_idx] == 0U) {
            /* 首帧有效样本：只建立基准，不计算差值 */
            s_zone_prev_temp[zone_idx] = current_temp;
            s_zone_prev_valid[zone_idx] = 1U;
            s_zone_rise_danger_count[zone_idx] = 0U;
            s_zone_rise_high_count[zone_idx] = 0U;
            continue;
        }

        delta = (int16_t)(current_temp - s_zone_prev_temp[zone_idx]);

        /* 更新输出快照（供 CAN 上报查看） */
        s_status.zone_temp_delta[zone_idx] = delta;

        /* 更新异常升温连续计数器
         * delta 单位是 0.1°C，阈值单位是 0.01°C，需要将 delta * 10 后比较 */
        if((delta * 10) >= (int16_t)g_temp_rise_danger_threshold) {
            if(s_zone_rise_danger_count[zone_idx] < 0xFFU) {
                s_zone_rise_danger_count[zone_idx]++;
            }
        } else {
            s_zone_rise_danger_count[zone_idx] = 0U;
        }

        if((delta * 10) >= (int16_t)g_temp_rise_high_threshold) {
            if(s_zone_rise_high_count[zone_idx] < 0xFFU) {
                s_zone_rise_high_count[zone_idx]++;
            }
        } else {
            s_zone_rise_high_count[zone_idx] = 0U;
        }

        s_zone_prev_temp[zone_idx] = current_temp;
    }
}

/*
 * system_state_zone_predict_danger
 *   判断指定分区是否满足"异常急速升温→DANGER级别"预警条件。
 *
 * 规则：预警功能开启，且连续 g_temp_rise_confirm_count 帧升温量
 *       均超过 g_temp_rise_danger_threshold（单位 0.01°C，默认 30 = 0.30°C/帧）。
 *
 * 返回值
 *   1 = 触发预警，需提前升级到 DANGER
 *   0 = 未触发
 */
static uint8_t system_state_zone_predict_danger(const system_state_input_t *input, uint8_t zone_idx)
{
    if((g_temp_prediction_enable == 0U) || (input == NULL) || (zone_idx >= 4U)) {
        return 0U;
    }

    if(input->zone_temp_valid[zone_idx] == 0U) {
        return 0U;
    }

    return (uint8_t)(s_zone_rise_danger_count[zone_idx] >= g_temp_rise_confirm_count);
}

/*
 * system_state_zone_predict_high_temp
 *   判断指定分区是否满足"升温偏快→HIGH_TEMP级别"预警条件。
 *
 * 规则：预警功能开启，且连续 g_temp_rise_confirm_count 帧升温量
 *       均超过 g_temp_rise_high_threshold（单位 0.01°C，默认 15 = 0.15°C/帧）。
 *
 * 返回值
 *   1 = 触发预警，需提前升级到 HIGH_TEMP
 *   0 = 未触发
 */
static uint8_t system_state_zone_predict_high_temp(const system_state_input_t *input, uint8_t zone_idx)
{
    if((g_temp_prediction_enable == 0U) || (input == NULL) || (zone_idx >= 4U)) {
        return 0U;
    }

    if(input->zone_temp_valid[zone_idx] == 0U) {
        return 0U;
    }

    return (uint8_t)(s_zone_rise_high_count[zone_idx] >= g_temp_rise_confirm_count);

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
 * system_state_cooler_rotate_apply
 *   制冷片轮转后处理（仅在 gas_alarm 时生效）。
 *
 *   逻辑：
 *     1) 如果没有 gas_alarm，或者轮转间隔配置为 0，直接返回（不干预正常输出）。
 *     2) 统计当前 cooler_enable[] 中有多少路需要开启（处于 DANGER 的分区）。
 *     3) 如果需要开的路数 <= 1，不需要轮转，直接返回。
 *     4) 按时间戳判断是否到了切换时刻，若到了则把 s_cooler_rotate_slot 推进到
 *        下一个"应该开"的分区（跳过不需要开的分区）。
 *     5) 最终只保留 s_cooler_rotate_slot 对应那一路，其余全部关闭。
 */
static void system_state_cooler_rotate_apply(const system_state_input_t *input)
{
    uint8_t i;
    uint8_t danger_mask = 0U;   /* 哪些分区的制冷片当前应该开 */
    uint8_t danger_count = 0U;
    uint32_t elapsed_ms;
    uint8_t next_slot;

    if((input == NULL) || (input->gas_alarm == 0U)) {
        return;
    }

    if(g_cooler_rotate_interval_ms == 0U) {
        return;  /* 轮转禁用，恢复全开 */
    }

    /* 收集当前需要开的分区掩码 */
    for(i = 0U; i < 4U; i++) {
        if(s_status.cooler_enable[i] != 0U) {
            danger_mask |= (uint8_t)(1U << i);
            danger_count++;
        }
    }

    if(danger_count <= 1U) {
        return;  /* 只有 0 或 1 路需要开，无需轮转 */
    }

    /* 判断是否到了切换时刻（处理 32 位溢出） */
    elapsed_ms = input->now_ms - s_cooler_rotate_last_ms;
    if(elapsed_ms >= g_cooler_rotate_interval_ms) {
        /* 从当前槽位往后找下一个需要开的分区 */
        next_slot = s_cooler_rotate_slot;
        for(i = 0U; i < 4U; i++) {
            next_slot = (uint8_t)((next_slot + 1U) % 4U);
            if((danger_mask & (uint8_t)(1U << next_slot)) != 0U) {
                break;
            }
        }
        s_cooler_rotate_slot    = next_slot;
        s_cooler_rotate_last_ms = input->now_ms;
    } else {
        /* 未到切换时刻：确保当前槽位在需要开的分区里，
         * 如果不在（例如刚进入 gas_alarm，槽位对应的分区恰好不在 DANGER），
         * 则找第一个需要开的分区作为初始槽位。 */
        if((danger_mask & (uint8_t)(1U << s_cooler_rotate_slot)) == 0U) {
            for(i = 0U; i < 4U; i++) {
                if((danger_mask & (uint8_t)(1U << i)) != 0U) {
                    s_cooler_rotate_slot    = i;
                    s_cooler_rotate_last_ms = input->now_ms;
                    break;
                }
            }
        }
    }

    /* 只保留轮转槽位对应那一路，其余关闭 */
    for(i = 0U; i < 4U; i++) {
        if(i != s_cooler_rotate_slot) {
            s_status.cooler_enable[i] = 0U;
        }
    }
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

    /* 初始化温度异常升温预警历史数据 */
    for(i = 0U; i < 4U; i++) {
        s_zone_prev_temp[i] = 0;
        s_zone_prev_valid[i] = 0U;
        s_zone_rise_danger_count[i] = 0U;
        s_zone_rise_high_count[i] = 0U;
    }

    /* 复位制冷片轮转状态 */
    s_cooler_rotate_slot    = 0U;
    s_cooler_rotate_last_ms = 0U;

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

    /* 清空温度异常升温预警历史数据 */
    for(i = 0U; i < 4U; i++) {
        s_zone_prev_temp[i] = 0;
        s_zone_prev_valid[i] = 0U;
        s_zone_rise_danger_count[i] = 0U;
        s_zone_rise_high_count[i] = 0U;
    }

    /* 复位制冷片轮转状态 */
    s_cooler_rotate_slot    = 0U;
    s_cooler_rotate_last_ms = 0U;

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
     * 升温异常检测：仅在收到一帧新温度样本时推进历史。
     * 异步采集下 app_task 以 20ms 高频调用本状态机，但温度约 1s 才刷新一次，
     * 用 temp_sample_fresh 过滤掉重复缓存，保证温度差基于真实采样间隔（DS18B20 固定约1s）。
     */
    if(input->temp_sample_fresh != 0U) {
        system_state_update_temp_delta(input);
    }

    /*
     * 4个分区各自独立跑一遍状态机：
     *   - 每个分区依据自己的 zone_temperature_tenths[i]/zone_temp_valid[i] 判断；
     *   - gas_alarm/pressure_alarm 是全局传感器输入，会同时参与每个分区的判断；
     *   - 分区状态迁移完成后立即刷新该分区的 heater_enable[i]/cooler_enable[i]。
     *   - 融合温度趋势预测：如果预测将突破阈值，提前升级状态
     */
    for(zone_idx = 0U; zone_idx < 4U; zone_idx++) {
        uint8_t has_danger_actual = system_state_zone_has_danger(input, zone_idx);
        uint8_t has_high_actual = (uint8_t)(!has_danger_actual && system_state_zone_has_high_temp(input, zone_idx));
        uint8_t has_low_i = (uint8_t)(!has_danger_actual && !has_high_actual &&
                                        system_state_zone_has_low_temp(input, zone_idx));

        uint8_t predict_danger = system_state_zone_predict_danger(input, zone_idx);
        uint8_t predict_high = (uint8_t)(!predict_danger && system_state_zone_predict_high_temp(input, zone_idx));

        uint8_t has_danger_i = (uint8_t)(has_danger_actual || predict_danger);
        uint8_t has_high_i = (uint8_t)(has_high_actual || predict_high);

        if((predict_danger != 0U) || (predict_high != 0U)) {
            s_status.zone_predictive[zone_idx] = 1U;
            s_status.predictive_alarm = 1U;
        }

        system_state_zone_task(zone_idx, input, has_danger_i, has_high_i, has_low_i);
    }

    /*
     * 全局状态归约：取4个分区中危险度最高的作为全局状态，
     * 驱动风扇/水泵/泄压阀/蜂鸣器/点火许可等共享设备。
     */
    new_global_state = system_state_reduce_zone_states();
    s_status.state = new_global_state;
    s_status.state_changed = (uint8_t)(new_global_state != old_global_state);

    /*
     * 制冷片轮转后处理：仅在 gas_alarm 时生效。
     * 4个分区状态机已经把 cooler_enable[] 按各自状态设置完毕，
     * 这里再做一次过滤，确保气体告警时最多只有一路制冷片同时工作。
     */
    system_state_cooler_rotate_apply(input);

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

