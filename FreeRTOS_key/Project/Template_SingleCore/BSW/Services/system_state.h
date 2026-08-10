#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * =============================================================================
 * 模块名称 : system_state
 * 文件功能 : 车辆热管理系统状态机
 *
 * 模块定位
 *   本模块负责对外部输入进行统一裁决，输出当前系统应处于的状态，
 *   并给出与状态相关的基础控制结果。它不负责单独的故障诊断、
 *   告警生成、执行器细节控制或通信协议细节，这些工作应由对应模块完成。
 *
 * 设计目标
 *   1) 用一个清晰、稳定的状态机描述系统处于什么风险等级；
 *   2) 只围绕"最高温度"做核心温度判断，因为它最能代表最危险的局部热点；
 *   3) 通过清晰的滞回和连续确认机制，避免状态在阈值附近频繁抖动；
 *   4) 所有阈值采用宏定义，便于调试阶段直接修改并重新编译验证。
 *
 * 状态定义（按温度由低到高严格排列成一条链）
 *   - LOW_TEMP  : 低温状态，最高温度低于 15.0°C；
 *   - NORMAL    : 正常运行状态，最高温度处于 [15.0°C, 27.0°C) 安全区间；
 *   - HIGH_TEMP : 高温预警状态，最高温度处于 [27.0°C, 33.0°C) 区间，需要持续关注；
 *   - DANGER    : 危险状态，最高温度达到 33.0°C 及以上，需要优先保证安全。
 *
 *   四个状态按温度严格排成一条链：LOW_TEMP - NORMAL - HIGH_TEMP - DANGER。
 *   NORMAL 是链中间的安全区间，向两侧（变冷或变热）偏离都会离开 NORMAL。
 *
 * 状态迁移原则
 *   1) 远离 NORMAL 的切换（进入 LOW_TEMP，或从 NORMAL/HIGH_TEMP 升级）可以快速发生，不额外延迟；
 *   2) 回落（向 NORMAL 靠近）必须逐级进行，不能越级回退；
 *   3) 回落时引入温度滞回与连续确认，避免噪声导致状态来回跳变；
 *   4) 上电后状态机始终运行，初始化只是启动过程，不作为业务状态。
 * =============================================================================
 */

/*
 * 默认阈值与采样周期说明
 *   - 温度阈值单位为 0.1°C；
 *   - 采样周期单位为毫秒（ms）；
 *   - 这些宏定义是当前版本的主要调试入口，状态机逻辑直接使用它们。
 *
 * 阈值含义（四个状态按温度由低到高排列）
 *   - LOW_TEMP_TEMP_C
 *       低温阈值：最高温度低于该值时进入 LOW_TEMP；
 *   - HIGH_TEMP_TEMP_C
 *       高温阈值：最高温度达到该值（且低于危险阈值）时进入 HIGH_TEMP；
 *   - DANGER_TEMP_C
 *       危险阈值：最高温度达到该值时进入 DANGER；
 *   - *_SAMPLE_MS
 *       不同状态下建议的温度采样周期，状态越危险，采样越频繁。
 */
#define SYSTEM_STATE_DEFAULT_LOW_TEMP_TEMP_C           150U /* 低温阈值：低于 15.0°C 进入低温状态。 */
#define SYSTEM_STATE_DEFAULT_HIGH_TEMP_TEMP_C          350U /* 高温阈值：达到 27.0°C 进入高温预警状态。 */
#define SYSTEM_STATE_DEFAULT_DANGER_TEMP_C             400U /* 危险阈值：达到 33.0°C 进入危险状态。 */
/*
 * 统一采样周期说明
 *   DS18B20 采用并行转换策略（启动4路 → 等待750ms → 读取数据），
 *   4路完整读取约需 788ms。为保证稳定可靠，采样周期设为 1000ms，
 *   留有约 200ms 余量。
 *   温度是惯性大的物理量，1秒采样一次对于电池包热管理完全足够，
 *   不必随危险等级动态调整采样频率。
 */
#define SYSTEM_STATE_DEFAULT_SAMPLE_MS             1000U /* 统一采样周期 1s */
#define SYSTEM_STATE_DEFAULT_FALLBACK_CONFIRM_COUNT      5U    /* 回落确认次数，需连续满足条件才允许降级。 */

/*
 * 运行时可配置参数（通过 CAN 0x20 配置类命令动态修改）
 *   初始化为默认值，可在运行时通过 CAN 命令修改
 */
extern uint16_t g_low_temp_threshold_tenths;    /* 低温阈值，单位 0.1°C */
extern uint16_t g_high_temp_threshold_tenths;   /* 高温阈值，单位 0.1°C */
extern uint16_t g_danger_temp_threshold_tenths; /* 危险阈值，单位 0.1°C */
extern uint8_t g_fallback_confirm_count;        /* 回落确认次数 */

/*
 * 温度异常升温预警配置参数（简化版）
 *   DS18B20 采样周期固定（约 1s），直接用相邻两帧温度差判断升温过快。
 *   g_temp_prediction_enable          : 预警功能使能，1=开启，0=关闭
 *   g_temp_rise_danger_threshold      : 触发 DANGER 的单次升温阈值，单位 0.01°C（默认 30 = 0.30°C）
 *   g_temp_rise_high_threshold        : 触发 HIGH_TEMP 的单次升温阈值，单位 0.01°C（默认 15 = 0.15°C）
 *   g_temp_rise_confirm_count         : 连续确认次数（连续 N 次超过阈值才触发）
 */
extern uint8_t g_temp_prediction_enable;        /* 预警功能使能，1=开启，0=关闭 */
extern uint16_t g_temp_rise_danger_threshold;   /* DANGER 升温阈值，单位 0.01°C，默认 30 (0.30°C) */
extern uint16_t g_temp_rise_high_threshold;     /* HIGH_TEMP 升温阈值，单位 0.01°C，默认 15 (0.15°C) */
extern uint8_t g_temp_rise_confirm_count;       /* 连续确认次数，默认 2 */

/*
 * 制冷片轮转配置参数
 *   DANGER 状态下多路制冷片需要工作时，为避免电池供电不足，
 *   每次只驱动一路，按固定间隔循环切换。
 *   g_cooler_rotate_interval_ms : 轮转切换间隔（毫秒），默认 5000ms（5秒）。
 *                                 设为 0 表示禁用轮转（恢复全开）。
 */
#define SYSTEM_STATE_DEFAULT_COOLER_ROTATE_MS    1000U
extern uint32_t g_cooler_rotate_interval_ms;

/*
 * system_state_t
 *   状态机当前状态枚举。
 *   该枚举用于描述系统当前所处的风险等级，以及状态机迁移方向。
 */
typedef enum {
    SYSTEM_STATE_NORMAL = 0,
    SYSTEM_STATE_LOW_TEMP,
    SYSTEM_STATE_HIGH_TEMP,
    SYSTEM_STATE_DANGER
} system_state_t;

/*
 * system_state_status_t
 *   状态机输出结构体。
 *
 * 说明
 *   这是状态机最终对外提供的结果快照。外部模块应直接读取这个结构体，
 *   而不要自行重新推导状态机内部判断逻辑。
 *
 * 字段说明
 *   state
 *       当前状态机状态，用于表示系统正处于哪个风险等级；
 *   state_changed
 *       本次调用中是否发生了状态切换。若发生状态跳变，则为 1，否则为 0；
 *   fan_enable
 *       风扇使能标志。由状态机给出基础裁决，具体执行方式由执行器模块完成；
 *   pump_enable
 *       水泵使能标志。由状态机给出基础裁决，具体执行方式由执行器模块完成；
 *   gate_enable
 *       泄压阀使能标志。用于执行泄压动作，具体执行方式由执行器模块完成；
 *   cooler_enable[4]
 *       制冷片使能数组。对应电池包4个方向的独立控温；
 *   heater_enable[4]
 *       PTC加热片使能数组。对应电池包4个方向的独立控温；
 *       统一加热模式下4路同时响应；分区模式下可独立控制；
 *   zone_state[4]
 *       每个分区（对应加热片/制冷片编号1-4）各自独立判断出的风险等级。
 *       heater_enable[i] / cooler_enable[i] 由 zone_state[i] 独立驱动；
 *       state 字段则是4个分区归约后的全局等级，供风扇/水泵/泄压阀/
 *       蜂鸣器/点火许可等共享设备使用；
 *   buzzer_enable
 *       蜂鸣器使能，用于告警提示；
 *   ignition_allowed
 *       点火许可标志。除 DANGER 外均为 1（允许按键正常控制点火）；
 *       DANGER 状态下强制为 0，外部模块必须据此将点火输出强制拉低，
 *       并且忽略此时的点火切换请求；
 *   next_temperature_sample_interval_ms
 *       下次建议的温度采样周期。状态越危险，采样周期越短。
 */
typedef struct {
    system_state_t state;
    uint8_t state_changed;
    uint8_t fan_enable;
    uint8_t fan_duty_percent;
    uint8_t pump_enable;
    uint8_t pump_duty_percent;
    uint8_t gate_enable;
    uint8_t cooler_enable[4];     /* 制冷片1-4独立使能 */
    uint8_t heater_enable[4];     /* PTC加热片1-4独立使能 */
    system_state_t zone_state[4]; /* 分区1-4各自独立的风险等级 */
    uint8_t buzzer_enable;
    uint8_t ignition_allowed;     /* 点火许可，DANGER 状态下强制为0 */
    uint32_t next_temperature_sample_interval_ms;
    uint8_t predictive_alarm;     /* 温度异常升温预警标志：任一分区升温过快（仅本轮有效，瞬时） */
    uint8_t zone_predictive[4];   /* 各分区预警触发标志，1=该分区触发异常升温预警（仅本轮有效，瞬时） */
    uint8_t zone_predict_trigger_count[4]; /* 各分区历史累计触发次数（饱和于255），
                                            * 只在"未触发→触发"的跳变时刻+1，用于故障回溯；
                                            * 可通过 CAN 配置命令 CAN_CFG_CLEAR_PREDICT_HISTORY 清零。 */
} system_state_status_t;

/*
 * system_state_input_t
 *   状态机输入结构体。
 *
 * 说明
 *   调用方在调用 system_state_task() 前，应将当前时刻与状态判断相关的输入
 *   整理到该结构体中，再一次性传入状态机。
 *
 * 字段说明
 *   gas_alarm / pressure_alarm
 *       外部报警输入。通常由专门的检测模块给出，状态机只负责根据它们
 *       决定是否进入更高风险等级；
 *   pressure_valid
 *       压力数据整体是否有效。若为无效，则状态机不执行压力相关判断；
 *   zone_temperature_tenths[4]
 *       4个分区各自的温度，单位为 0.1°C。下标i对应加热片(i+1)/制冷片(i+1)所在分区，
 *       即 zone_temperature_tenths[i] 与 heater_enable[i]/cooler_enable[i] 是同一分区；
 *   zone_temp_valid[4]
 *       4个分区各自的温度是否有效。若某分区无效，状态机对该分区维持上一次的
 *       zone_state[i]（沿用最后一次已知状态），不因传感器故障而误判；
 *   temp_sensor_valid_count
 *       有效温度点数量（0-4）。当前版本未直接参与决策，但保留用于后续一致性判断；
 *   temperature_valid
 *       温度数据整体是否有效（至少一路有效）。若为无效，则状态机不执行温度风险判断，只维持基础状态；
 *   now_ms
 *       当前系统时间戳，单位为毫秒。用于状态切换时的时间基准和采样周期管理；
 *   temp_sample_time_ms
 *       温度样本的实际采集时间戳。异步采集架构下，温度由独立任务约每秒刷新一次，
 *       而状态机可能被高频调用（如 20ms）。温度变化率必须基于"两次真实采样之间的
 *       时间差"计算，因此这里单独携带采样时刻，而非用 now_ms；
 *   temp_sample_fresh
 *       标记本帧温度是否为新采集的样本。仅当为 1 时状态机才更新温度变化率，
 *       避免同一份缓存被反复计算导致 dt 过小、斜率失真；
 *   ignition_on
 *       点火/系统运行许可。它不会决定状态机是否运行，但可作为后续保护逻辑的输入。
 */
typedef struct {
    uint8_t gas_valid;
    uint8_t gas_alarm;
    uint8_t pressure_alarm;
    int32_t pressure_pa;
    uint8_t pressure_valid;
    int16_t zone_temperature_tenths[4];
    uint8_t zone_temp_valid[4];
    uint8_t temp_sensor_valid_count;
    uint8_t temp_sensor_fault_mask;
    uint8_t temperature_valid;
    uint32_t now_ms;
    uint32_t temp_sample_time_ms;  /* 温度样本的实际采集时间戳（由采集任务打点）。
                                    * 用于温度变化率计算：只有该时间戳变化才认为是新样本，
                                    * 与状态机自身的调用频率(now_ms)解耦，避免高频调用污染斜率。 */
    uint8_t temp_sample_fresh;     /* 1=本次输入携带的是一帧新温度样本；0=沿用上一帧缓存。 */
    uint8_t ignition_on;
} system_state_input_t;

/*
 * 对外接口说明
 *   system_state_init()
 *       完成状态机的初始化；
 *   system_state_reset()
 *       将状态机恢复到初始状态；
 *   system_state_task()
 *       输入一次状态快照并更新状态机；
 *   system_state_get_status()
 *       读取状态机输出快照；
 *   system_state_get_state()
 *       读取当前状态；
 */
void system_state_init(void);
void system_state_reset(void);
void system_state_clear_predict_history(void);  /* 仅清除历史触发次数，不复位状态机 */
void system_state_task(const system_state_input_t *input);
void system_state_get_status(system_state_status_t *status);
void system_state_get_input(system_state_input_t *input);
system_state_t system_state_get_state(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_STATE_H */
