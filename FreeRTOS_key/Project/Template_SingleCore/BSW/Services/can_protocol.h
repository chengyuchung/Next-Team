#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <stdint.h>
#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : can_protocol
 * 文件功能 : CAN 应用层协议定义（BSW Services 层）
 *
 * 设计目标 :
 *   1) 定义 CAN 帧格式、ID、消息号、数据结构；
 *   2) 提供帧的打包和解包接口；
 *   3) 不包含业务逻辑处理，只负责协议层的数据转换。
 *
 * ============================================================================
 * 协议架构 :
 * ============================================================================
 *   双向通信 ID：
 *     0x188  查询类（双向）：上位机查询请求 + MCU 数据响应
 *     0x189  控制类（双向）：上位机控制命令 + MCU ACK 响应
 *     0x18A  配置类（双向）：上位机配置命令 + MCU ACK 响应
 *
 *   通信方向识别：
 *     Byte0[7:4] = 源节点地址
 *       0x1 (CAN_NODE_HOST) = 上位机发送
 *       0x2 (CAN_NODE_MCU)  = MCU 发送
 *     Byte0[3:0] = 保留（填充 0）
 *
 * ============================================================================
 * 标准帧格式（8字节）:
 * ============================================================================
 *   Byte0: 源节点地址（高4位）+ 保留（低4位）
 *   Byte1: 消息号（查询号/控制号/配置号）
 *   Byte2~7: 数据负载（根据消息号不同而定义）
 *
 * ============================================================================
 * 查询类协议（ID=0x188）:
 * ============================================================================
 * 
 * ┌─────────────────────────────────────────────────────────────────────┐
 * │ 请求帧格式（上位机 → MCU）                                           │
 * ├──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────────────────┤
 * │ Byte │  0   │  1   │  2   │  3   │  4   │  5   │  6   │  7       │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────────┤
 * │ 说明 │ 0x10 │ 消息号│ 0xCC │ 0xCC │ 0xCC │ 0xCC │ 0xCC │ 0xCC     │
 * └──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────────┘
 *   注：查询请求统一使用填充字节 0xCC（CAN_RSVD_FILL）
 *
 * ┌─────────────────────────────────────────────────────────────────────┐
 * │ 响应帧格式（MCU → 上位机）                                           │
 * ├──────┬──────┬──────┬─────────────────────────────────────────────┤
 * │ Byte │  0   │  1   │  2 ~ 7                                      │
 * ├──────┼──────┼──────┼─────────────────────────────────────────────┤
 * │ 说明 │ 0x20 │ 消息号│ 数据负载（根据查询号不同）                   │
 * └──────┴──────┴──────┴─────────────────────────────────────────────┘
 *
 * --- 0x00: 环境数据查询 (CAN_QRY_ENV) ---
 *   响应：
 *     Byte2~3: int16_t 温度（0.1°C，高字节在前）
 *     Byte4~5: int16_t 气压（kPa，高字节在前）
 *     Byte6:   uint8_t 气压报警标志（0=正常，1=报警）
 *     Byte7:   uint8_t 气体泄漏标志（0=正常，1=泄漏）
 *
 * --- 0x01: 执行器状态查询 (CAN_QRY_STA) ---
 *   响应：
 *     Byte2: uint8_t 风扇占空比（0~100%）
 *     Byte3: uint8_t 水泵占空比（0~100%）
 *     Byte4: uint8_t 制冷片状态（0=关，1=开）
 *     Byte5: uint8_t 排气阀状态（0=关，1=开）
 *     Byte6~7: 0xCC（保留）
 *
 * --- 0x02: 系统状态查询 (CAN_QRY_SYS) ---
 *   响应：
 *     Byte2: uint8_t 系统级别（0=NORMAL, 1=HIGH_TEMP, 2=DANGER, 3=SLEEP, 4=MANUAL）
 *     Byte3~7: 0xCC（保留）
 *
 * --- 0x03: 故障状态查询 (CAN_QRY_FLT) ---
 *   响应：
 *     Byte2: uint8_t 气体传感器故障（0=正常，1=故障）
 *     Byte3: uint8_t 制冷片故障（预留，填0）
 *     Byte4: uint8_t 加热片故障（预留，填0）
 *     Byte5: uint8_t 温度传感器故障（预留，填0）
 *     Byte6: uint8_t 风扇故障（预留，填0）
 *     Byte7: 0xCC（保留，或水泵/排气阀/气压传感器故障预留位）
 *
 * --- 0x04~0x07: 分区温度查询 (CAN_QRY_TEMP_CH0~CH3) ---
 *   响应：
 *     Byte2~3: int16_t 温度（0.1°C，高字节在前）
 *     Byte4~7: 0xCC（保留）
 *
 * --- 0x08: 温度阈值查询 (CAN_QRY_THRESHOLD) ---
 *   响应：
 *     Byte2~3: uint16_t 低温阈值（0.1°C，高字节在前）
 *     Byte4~5: uint16_t 高温阈值（0.1°C，高字节在前）
 *     Byte6~7: uint16_t 危险温度阈值（0.1°C，高字节在前）
 *
 * --- 0x09: Guard 睡眠时长查询 (CAN_QRY_GUARD_SLEEP) ---
 *   响应：
 *     Byte2~3: uint16_t 基准值（秒，高字节在前）
 *     Byte4~5: uint16_t 当前自适应值（秒，高字节在前）
 *     Byte6~7: 0xCC（保留）
 *
 * --- 0x0A: Guard 巡检异常处理确认时长查询 (CAN_QRY_GUARD_BUDGET) ---
 *   响应：
 *     Byte2~3: uint16_t 基准值（秒，高字节在前）
 *     Byte4~5: uint16_t 当前自适应值（秒，高字节在前）
 *     Byte6~7: 0xCC（保留）
 *
 * --- 0x0B: 4路分区温度一次性查询 (CAN_QRY_TEMP_ALL) ---
 *   说明：MCU 收到请求后，依次发送 4 帧响应，消息号分别回显 0x04~0x07
 *   每帧格式同单路温度查询（Byte2~3 为温度值，Byte4~7 填充 0xCC）
 *
 * --- 0x0C: ADC 原始值查询 (CAN_QRY_ADC_RAW) ---
 *   响应：
 *     Byte2~3: uint16_t 气体传感器 ADC raw 值（0~4095，高字节在前）
 *     Byte4~5: uint16_t 预留字段（原制冷片电流，0xFFFF=无效）
 *     Byte6~7: 0xCC（保留）
 *
 * --- 0x0D: 气体传感器故障判定区间查询 (CAN_QRY_GAS_THRESHOLD) ---
 *   响应：
 *     Byte2~3: uint16_t 下限值（ADC raw，高字节在前）
 *     Byte4~5: uint16_t 上限值（ADC raw，高字节在前）
 *     Byte6~7: 0xCC（保留）
 *
 * --- 0x0E: 异常升温预警功能状态查询 (CAN_QRY_PREDICT_STATUS) ---
 *   响应：
 *     Byte2:   uint8_t 使能标志（0=关闭，1=开启）
 *     Byte3:   uint8_t 分区0历史累计触发次数（饱和于255）
 *     Byte4:   uint8_t 分区1历史累计触发次数（饱和于255）
 *     Byte5:   uint8_t 分区2历史累计触发次数（饱和于255）
 *     Byte6:   uint8_t 分区3历史累计触发次数（饱和于255）
 *     Byte7:   0xCC（保留）
 *
 * ============================================================================
 * 控制类协议（ID=0x189）:
 * ============================================================================
 *
 * ┌─────────────────────────────────────────────────────────────────────┐
 * │ 命令帧格式（上位机 → MCU）                                           │
 * ├──────┬──────┬──────┬─────────────────────────────────────────────┤
 * │ Byte │  0   │  1   │  2 ~ 7                                      │
 * ├──────┼──────┼──────┼─────────────────────────────────────────────┤
 * │ 说明 │ 0x10 │ 控制号│ 控制参数（根据控制号不同）                   │
 * └──────┴──────┴──────┴─────────────────────────────────────────────┘
 *
 * ┌─────────────────────────────────────────────────────────────────────┐
 * │ ACK 响应帧格式（MCU → 上位机）                                       │
 * ├──────┬──────┬──────┬──────┬─────────────────────────────────────┤
 * │ Byte │  0   │  1   │  2   │  3 ~ 7                              │
 * ├──────┼──────┼──────┼──────┼─────────────────────────────────────┤
 * │ 说明 │ 0x20 │ 控制号│ 结果码│ 0xCC（保留）                        │
 * └──────┴──────┴──────┴──────┴─────────────────────────────────────┘
 *   结果码（Byte2）：
 *     0x00 = CAN_ACK_OK          (命令执行成功)
 *     0x01 = CAN_ACK_REJECTED    (命令被拒绝，当前状态不允许)
 *     0x02 = CAN_ACK_ILLEGAL     (命令参数非法)
 *     0x03 = CAN_ACK_CHECK_FAIL  (校验失败)
 *     0x04 = CAN_ACK_NOT_MANUAL  (非手动模式，不允许执行)
 *
 * --- 0x00: 开机命令 (CAN_CTL_POWER_ON) ---
 *   命令：Byte2~7 填充 0xCC
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x01: 睡眠命令 (CAN_CTL_SLEEP) ---
 *   命令：Byte2~7 填充 0xCC
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x02: 点火命令 (CAN_CTL_IGNITE) ---
 *   命令：Byte2~7 填充 0xCC
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x03: 熄火命令 (CAN_CTL_EXTINGUISH) ---
 *   命令：Byte2~7 填充 0xCC
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x04: 系统复位命令 (CAN_CTL_RESET) ---
 *   命令：
 *     Byte2~3: uint16_t 校验码（必须为 0xA5A5，高字节在前）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码，校验通过后执行复位）
 *
 * --- 0x05: 清除故障命令 (CAN_CTL_CLEAR_FAULT) ---
 *   命令：Byte2~7 填充 0xCC
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x06: 进入手动模式命令 (CAN_CTL_MANUAL_ENTER) ---
 *   命令：Byte2~7 填充 0xCC
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x07: 退出手动模式命令 (CAN_CTL_MANUAL_EXIT) ---
 *   命令：Byte2~7 填充 0xCC
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x08: 蜂鸣器静音命令 (CAN_CTL_BUZZER_MUTE) ---
 *   命令：Byte2~7 填充 0xCC
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x09: 制冷片控制命令 (CAN_CTL_COOLER) ---
 *   命令：
 *     Byte2: uint8_t 开关（0=关闭，1=开启）
 *     Byte3~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x0A: 加热片控制命令 (CAN_CTL_HEATER) ---
 *   命令：
 *     Byte2: uint8_t 开关（0=关闭，1=开启）
 *     Byte3~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x0B: 风扇控制命令 (CAN_CTL_FAN) ---
 *   命令：
 *     Byte2: uint8_t 占空比（0~100%）
 *     Byte3~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x0C: 水泵控制命令 (CAN_CTL_PUMP) ---
 *   命令：
 *     Byte2: uint8_t 占空比（0~100%）
 *     Byte3~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x0D: 排气阀控制命令 (CAN_CTL_GATE) ---
 *   命令：
 *     Byte2: uint8_t 开关（0=关闭，1=开启）
 *     Byte3~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x0E: 异常升温预警功能使能开关 (CAN_CTL_TEMP_PREDICT_ENABLE) ---
 *   命令：
 *     Byte2: uint8_t 使能（0=关闭，1=开启）
 *     Byte3~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * ============================================================================
 * 配置类协议（ID=0x18A）:
 * ============================================================================
 *
 * ┌─────────────────────────────────────────────────────────────────────┐
 * │ 配置命令帧格式（上位机 → MCU）                                       │
 * ├──────┬──────┬──────┬─────────────────────────────────────────────┤
 * │ Byte │  0   │  1   │  2 ~ 7                                      │
 * ├──────┼──────┼──────┼─────────────────────────────────────────────┤
 * │ 说明 │ 0x10 │ 配置号│ 配置参数（根据配置号不同）                   │
 * └──────┴──────┴──────┴─────────────────────────────────────────────┘
 *
 * ┌─────────────────────────────────────────────────────────────────────┐
 * │ ACK 响应帧格式（MCU → 上位机）                                       │
 * ├──────┬──────┬──────┬──────┬─────────────────────────────────────┤
 * │ Byte │  0   │  1   │  2   │  3 ~ 7                              │
 * ├──────┼──────┼──────┼──────┼─────────────────────────────────────┤
 * │ 说明 │ 0x20 │ 配置号│ 结果码│ 0xCC（保留）                        │
 * └──────┴──────┴──────┴──────┴─────────────────────────────────────┘
 *   结果码（Byte2）：同控制类
 *
 * --- 0x00: 高温阈值配置 (CAN_CFG_HIGH_TEMP_THRESHOLD) ---
 *   命令：
 *     Byte2~3: uint16_t 温度值（0.1°C，高字节在前，范围0~1000）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x01: 危险温度阈值配置 (CAN_CFG_DANGER_TEMP_THRESHOLD) ---
 *   命令：
 *     Byte2~3: uint16_t 温度值（0.1°C，高字节在前，范围0~1000）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x02: 低温阈值配置 (CAN_CFG_LOW_TEMP_THRESHOLD) ---
 *   命令：
 *     Byte2~3: uint16_t 温度值（0.1°C，高字节在前，范围0~1000）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x03: 降级确认次数配置 (CAN_CFG_FALLBACK_CONFIRM_COUNT) ---
 *   命令：
 *     Byte2: uint8_t 次数值
 *     Byte3~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x04: Guard 睡眠间隔配置 (CAN_CFG_GUARD_SLEEP_INTERVAL) ---
 *   命令：
 *     Byte2~3: uint16_t 时长（秒，高字节在前）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x05: Guard 异常处理确认时长配置 (CAN_CFG_GUARD_HANDLING_BUDGET) ---
 *   命令：
 *     Byte2~3: uint16_t 时长（秒，高字节在前）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x06: 应用任务周期配置 (CAN_CFG_APP_TASK_PERIOD) ---
 *   命令：
 *     Byte2~3: uint16_t 周期（毫秒，高字节在前）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x07: 气体传感器故障判定下限配置 (CAN_CFG_GAS_SENSOR_RAW_MIN) ---
 *   命令：
 *     Byte2~3: uint16_t ADC raw 值（0~4095，高字节在前）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x08: 气体传感器故障判定上限配置 (CAN_CFG_GAS_SENSOR_RAW_MAX) ---
 *   命令：
 *     Byte2~3: uint16_t ADC raw 值（0~4095，高字节在前）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x09: 单次升温触发 DANGER 阈值配置 (CAN_CFG_RISE_DANGER_THRESHOLD) ---
 *   命令：
 *     Byte2~3: uint16_t 升温值（0.01°C，高字节在前，范围1~200，默认30）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x0A: 单次升温触发 HIGH_TEMP 阈值配置 (CAN_CFG_RISE_HIGH_THRESHOLD) ---
 *   命令：
 *     Byte2~3: uint16_t 升温值（0.01°C，高字节在前，范围1~200，默认15）
 *     Byte4~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x0B: 升温连续确认次数配置 (CAN_CFG_RISE_CONFIRM_COUNT) ---
 *   命令：
 *     Byte2: uint8_t 次数（范围1~10，默认2）
 *     Byte3~7: 0xCC（保留）
 *   响应：ACK（Byte2=结果码）
 *
 * --- 0x0C: 清除升温预警历史触发次数 (CAN_CFG_CLEAR_PREDICT_HISTORY) ---
 *   命令：Byte2~7 填充 0xCC（无参数）
 *   响应：ACK（Byte2=结果码）
 *
 * ============================================================================
 * 主动事件上报（ID=0x189，MCU → 上位机）:
 * ============================================================================
 *   Byte0: 0x20（MCU源地址）
 *   Byte1: 0xF1 (CAN_EVT_MANUAL_EXIT_DANGER) - 手动模式下系统因危险自动退出事件
 *   Byte2~7: 0xCC（保留）
 *
 * ============================================================================
 */

/* 双向通信 ID（请求和响应共用） */
#define CAN_ID_QUERY             0x188U
#define CAN_ID_CONTROL           0x189U
#define CAN_ID_CONFIG            0x18AU

/* 源节点地址（Byte0 高4位） */
#define CAN_NODE_HOST            0x10U
#define CAN_NODE_MCU             0x20U

/* 兼容旧定义 */
#define CAN_ID_CMD               CAN_ID_QUERY
#define CAN_ID_ACK               CAN_ID_CONTROL
#define CAN_ID_RESEND_REQUEST    0xFFFU

/* 查询类消息号（Byte1），ID=0x188 双向 */
#define CAN_QRY_ENV       0x00U
#define CAN_QRY_STA       0x01U
#define CAN_QRY_SYS       0x02U
#define CAN_QRY_FLT       0x03U
#define CAN_QRY_TEMP_CH0  0x04U  /* 分区温度 - 通道0 */
#define CAN_QRY_TEMP_CH1  0x05U  /* 分区温度 - 通道1 */
#define CAN_QRY_TEMP_CH2  0x06U  /* 分区温度 - 通道2 */
#define CAN_QRY_TEMP_CH3  0x07U  /* 分区温度 - 通道3 */
#define CAN_QRY_THRESHOLD 0x08U  /* 温度阈值查询 */
#define CAN_QRY_GUARD_SLEEP  0x09U  /* guard 睡眠时长查询（基准值 + 当前自适应值） */
#define CAN_QRY_GUARD_BUDGET 0x0AU  /* guard 巡检异常处理后 NORMAL 持续确认时长查询（基准值 + 当前自适应值） */
#define CAN_QRY_TEMP_ALL     0x0BU  /* 4路分区温度一次性查询：MCU依次回复4帧，
                                      * 消息号仍分别回显 CAN_QRY_TEMP_CH0~CH3，
                                      * 帧格式与单路查询完全一致 */
#define CAN_QRY_ADC_RAW      0x0CU  /* ADC原始raw值查询（气体传感器），
                                      * 用于现场标定 fault_manager 的固定阈值，
                                      * 标定完成后此查询可长期保留，不影响正常运行 */
#define CAN_QRY_GAS_THRESHOLD 0x0DU /* 气体传感器故障判定区间查询（下限+上限），
                                      * 用于核实 CAN_CFG_GAS_SENSOR_RAW_MIN/MAX
                                      * 配置命令是否生效 */
#define CAN_QRY_PREDICT_STATUS 0x0EU /* 异常升温预警功能状态查询：返回使能标志+
                                      * 4个分区历史累计触发次数（饱和于255），
                                      * 用于确认预警功能是否真的在起作用 */

/* 保留字节填充值 */
#define CAN_RSVD_FILL   0xCCU

/* 控制类消息号（Byte1），ID=0x189 双向 */
#define CAN_CTL_POWER_ON     0x00U
#define CAN_CTL_SLEEP        0x01U
#define CAN_CTL_IGNITE       0x02U
#define CAN_CTL_EXTINGUISH   0x03U
#define CAN_CTL_RESET        0x04U
#define CAN_CTL_CLEAR_FAULT  0x05U
#define CAN_CTL_MANUAL_ENTER 0x06U
#define CAN_CTL_MANUAL_EXIT  0x07U
#define CAN_CTL_BUZZER_MUTE  0x08U
#define CAN_CTL_COOLER       0x09U
#define CAN_CTL_HEATER       0x0AU
#define CAN_CTL_FAN          0x0BU
#define CAN_CTL_PUMP         0x0CU
#define CAN_CTL_GATE         0x0DU
#define CAN_CTL_TEMP_PREDICT_ENABLE 0x0EU  /* 异常升温预警功能使能开关 */

/* 系统复位校验码 */
#define CAN_CTL_RESET_MAGIC  0xA5A5U

/* 配置类消息号（Byte1），ID=0x18A 双向
 * 0x00~0x02 三个温度阈值配置：Byte[2,3] = uint16_t，高字节在前，
 * 单位 0.1°C（与 CAN_QRY_THRESHOLD 查询响应格式一致），取值范围 0~1000。 */
#define CAN_CFG_HIGH_TEMP_THRESHOLD     0x00U
#define CAN_CFG_DANGER_TEMP_THRESHOLD   0x01U
#define CAN_CFG_LOW_TEMP_THRESHOLD      0x02U
#define CAN_CFG_FALLBACK_CONFIRM_COUNT  0x03U
#define CAN_CFG_GUARD_SLEEP_INTERVAL    0x04U
#define CAN_CFG_GUARD_HANDLING_BUDGET   0x05U
#define CAN_CFG_APP_TASK_PERIOD         0x06U
#define CAN_CFG_GAS_SENSOR_RAW_MIN      0x07U  /* 气体传感器故障判定下限（ADC raw，0~4095） */
#define CAN_CFG_GAS_SENSOR_RAW_MAX      0x08U  /* 气体传感器故障判定上限（ADC raw，0~4095） */
#define CAN_CFG_RISE_DANGER_THRESHOLD   0x09U  /* 单次采样升温触发DANGER的阈值，Byte[2,3] uint16_t，
                                                * 高字节在前，单位0.01°C，范围1~200，默认30（=0.30°C）*/
#define CAN_CFG_RISE_HIGH_THRESHOLD     0x0AU  /* 单次采样升温触发HIGH_TEMP的阈值，Byte[2,3] uint16_t，
                                                * 高字节在前，单位0.01°C，范围1~200，默认15（=0.15°C）*/
#define CAN_CFG_RISE_CONFIRM_COUNT      0x0BU  /* 连续确认次数，Byte2 = uint8_t，范围1~10，默认2 */
#define CAN_CFG_CLEAR_PREDICT_HISTORY   0x0CU  /* 清除4个分区的升温预警历史累计触发次数，
                                                * 无需参数（Byte2~7忽略），仅清计数，
                                                * 不影响状态机当前运行状态 */

/* ACK 响应结果码（Byte2） */
#define CAN_ACK_OK          0x00U
#define CAN_ACK_REJECTED    0x01U
#define CAN_ACK_ILLEGAL     0x02U
#define CAN_ACK_CHECK_FAIL  0x03U
#define CAN_ACK_NOT_MANUAL  0x04U

/* 主动事件标识（Byte1 特殊值） */
#define CAN_EVT_MANUAL_EXIT_DANGER 0xF1U

/* 查询类数据响应格式 */
typedef struct {
    int16_t temperature;
    int16_t pressure_kpa;
    uint8_t press_alarm;
    uint8_t gas_leak;
} can_env_data_t;

typedef struct {
    int16_t temperature[4];
} can_temp_data_t;

typedef struct {
    uint8_t fan_duty;
    uint8_t pump_duty;
    uint8_t cooler_on;
    uint8_t gate_on;
} can_state_data_t;

typedef struct {
    uint8_t level;
    uint8_t reserved[7];
} can_system_state_data_t;

typedef struct {
    uint8_t gas_sensor;      /* 气体传感器故障（0=正常，1=故障） */
    uint8_t cooler_rsvd;     /* 制冷片故障（预留，填0） */
    uint8_t heater_rsvd;     /* 加热片故障（预留，填0） */
    uint8_t temp_sensor_rsvd;/* 温度传感器故障（预留，填0） */
    uint8_t fan_rsvd;        /* 风扇故障（预留，填0） */
    uint8_t pump_rsvd;       /* 水泵故障（预留，填0） */
    uint8_t gate_rsvd;       /* 排气阀故障（预留，填0） */
    uint8_t press_sensor_rsvd; /* 气压传感器故障（预留，填0） */
} can_fault_data_t;

typedef struct {
    uint16_t low_temp_threshold_tenths;
    uint16_t high_temp_threshold_tenths;
    uint16_t danger_temp_threshold_tenths;
} can_threshold_data_t;

typedef struct {
    uint16_t base_seconds;      /* 配置的基准值（g_guard_sleep_interval_ms / 1000） */
    uint16_t current_seconds;   /* 自适应算法当前实际生效的睡眠时长（秒） */
} can_guard_sleep_data_t;

typedef struct {
    uint16_t base_seconds;      /* 配置的基准值（g_guard_handling_budget_ms / 1000） */
    uint16_t current_seconds;   /* 自适应算法当前实际生效的确认时长（秒），只增不减 */
} can_guard_budget_data_t;

typedef struct {
    uint16_t gas_sensor_raw;    /* 气体传感器 ADC 原始值（PD11/ADC0_IN9，0~4095） */
    uint16_t reserved_raw;      /* 预留字段（原制冷片电流通道已移除，0xFFFF=无效） */
} can_adc_raw_data_t;

typedef struct {
    uint16_t raw_min;   /* 气体传感器故障判定下限（ADC raw，0~4095） */
    uint16_t raw_max;   /* 气体传感器故障判定上限（ADC raw，0~4095） */
} can_gas_threshold_data_t;

typedef struct {
    uint8_t enable;                       /* 预警功能使能，1=开启，0=关闭 */
    uint8_t zone_trigger_count[4];         /* 各分区历史累计触发次数（饱和于255） */
} can_predict_status_data_t;

/*
 * CAN 协议层接口 - 查询类响应发送
 */
ErrStatus can_protocol_send_env_response(uint8_t msg_id, int16_t temp_tenths, int16_t pressure_kpa, uint8_t press_alarm, uint8_t gas_leak);
ErrStatus can_protocol_send_state_response(uint8_t msg_id, uint8_t fan_duty, uint8_t pump_duty, uint8_t cooler_on, uint8_t gate_on);
ErrStatus can_protocol_send_system_state_response(uint8_t msg_id, uint8_t level);
ErrStatus can_protocol_send_fault_response(uint8_t gas_sensor, uint8_t cooler_rsvd, uint8_t heater_rsvd, uint8_t temp_sensor_rsvd, uint8_t fan_rsvd, uint8_t pump_rsvd, uint8_t gate_rsvd, uint8_t press_sensor_rsvd);
ErrStatus can_protocol_send_temp_ch_response(uint8_t msg_id, int16_t temp_tenths);
ErrStatus can_protocol_send_threshold_response(uint8_t msg_id, uint16_t low_temp, uint16_t high_temp, uint16_t danger_temp);
ErrStatus can_protocol_send_guard_sleep_response(uint16_t base_seconds, uint16_t current_seconds);
ErrStatus can_protocol_send_guard_budget_response(uint16_t base_seconds, uint16_t current_seconds);
ErrStatus can_protocol_send_adc_raw_response(uint16_t gas_sensor_raw, uint16_t reserved_raw);
ErrStatus can_protocol_send_gas_threshold_response(uint16_t raw_min, uint16_t raw_max);
ErrStatus can_protocol_send_predict_status_response(uint8_t enable, const uint8_t zone_trigger_count[4]);

/*
 * CAN 协议层接口 - 控制类/配置类 ACK 响应
 */
ErrStatus can_protocol_send_control_ack(uint8_t msg_id, uint8_t result);
ErrStatus can_protocol_send_config_ack(uint8_t msg_id, uint8_t result);

#ifdef __cplusplus
}
#endif

#endif /* CAN_PROTOCOL_H */
