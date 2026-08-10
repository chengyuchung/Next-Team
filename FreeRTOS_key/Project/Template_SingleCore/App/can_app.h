#ifndef CAN_APP_H
#define CAN_APP_H

#include <stdint.h>
#include "main.h"
#include "can_protocol.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : can_app
 * 文件功能 : CAN 应用层业务逻辑处理
 *
 * 设计目标 :
 *   1) 处理 CAN 查询请求，读取系统状态并上报；
 *   2) 处理 CAN 控制命令，执行相应动作；
 *   3) 处理 CAN 配置命令，修改运行参数；
 *   4) 管理上报标志，实现异步上报机制。
 * ============================================================================
 */

/* CAN 接收事件标志（由中断设置） */
extern volatile uint8_t g_can4_rx_event;

/*
 * 函数名称 : can_app_init
 * 功能描述 : 初始化 CAN 应用层（包括硬件驱动层）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void can_app_init(void);

/*
 * 函数名称 : can_app_handle_query
 * 功能描述 : 处理查询类请求（ID=0x188, Byte0=CAN_NODE_HOST）。
 * 输入参数 :
 *   - msg_id : 查询消息号（CAN_QRY_*）
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 处理成功
 *   - ERROR   : 非法消息号
 */
ErrStatus can_app_handle_query(uint8_t msg_id);

/*
 * 函数名称 : can_app_handle_control
 * 功能描述 : 处理控制类命令（请求帧 Byte0=0x10）。
 * 输入参数 :
 *   - msg_id : 控制消息号（CAN_CTL_*）
 *   - param  : 参数数组（来自 CAN 帧 Byte2~Byte7）
 * 输出参数 : 无
 * 返 回 值 :
 *   - CAN_ACK_OK         : 命令执行成功
 *   - CAN_ACK_REJECTED   : 命令被拒绝
 *   - CAN_ACK_CHECK_FAIL : 校验失败
 *   - CAN_ACK_INVALID    : 非法命令
 */
uint8_t can_app_handle_control(uint8_t msg_id, const uint8_t *param);

/*
 * 函数名称 : can_app_handle_config
 * 功能描述 : 处理配置类命令（请求帧 Byte0=0x30）。
 * 输入参数 :
 *   - msg_id : 配置消息号（CAN_CFG_*）
 *   - param  : 参数数组（来自 CAN 帧 Byte2~Byte7）
 * 输出参数 : 无
 * 返 回 值 :
 *   - CAN_ACK_OK         : 配置成功
 *   - CAN_ACK_REJECTED   : 配置被拒绝
 *   - CAN_ACK_CHECK_FAIL : 校验失败
 *   - CAN_ACK_INVALID    : 非法配置项
 */
uint8_t can_app_handle_config(uint8_t msg_id, const uint8_t *param);

/*
 * 函数名称 : can_app_process_pending_uploads
 * 功能描述 : 处理所有待上报的 CAN 数据（非阻塞）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void can_app_process_pending_uploads(void);

/*
 * 函数名称 : can_app_upload_env
 * 功能描述 : 上报环境数据（温度、压力、告警）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_env(void);

/*
 * 函数名称 : can_app_upload_state
 * 功能描述 : 上报执行器状态（风扇、水泵、制冷片、排气阀）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_state(void);

/*
 * 函数名称 : can_app_upload_system_state
 * 功能描述 : 上报系统状态等级（NORMAL/LOW_TEMP/HIGH_TEMP/DANGER）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_system_state(void);

/*
 * 函数名称 : can_app_upload_fault
 * 功能描述 : 上报故障信息（执行器+传感器故障）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_fault(void);

/*
 * 函数名称 : can_app_upload_temp_mask
 * 功能描述 : 按位掩码上报指定分区的温度（每路各发一帧，各自独立消息号）。
 * 输入参数 :
 *   - ch_mask : bit0~3 分别对应 CH0~CH3，置位表示需要上报该路
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 全部发送成功
 *   - ERROR   : 至少一帧发送失败
 */
ErrStatus can_app_upload_temp_mask(uint8_t ch_mask);

/*
 * 函数名称 : can_app_upload_temp
 * 功能描述 : 上报4路温度详细数据（等价于 can_app_upload_temp_mask(0x0F)）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_temp(void);

/*
 * 函数名称 : can_app_upload_threshold
 * 功能描述 : 上报当前生效的温度阈值配置（低温/高温/危险阈值）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_threshold(void);

/*
 * 函数名称 : can_app_upload_guard_sleep
 * 功能描述 : 上报 guard 睡眠时长（配置基准值 + 自适应算法当前生效值，单位：秒）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_guard_sleep(void);

/*
 * 函数名称 : can_app_upload_guard_budget
 * 功能描述 : 上报 guard 巡检异常处理后 NORMAL 持续确认时长（单位：秒）。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_guard_budget(void);

/*
 * 函数名称 : can_app_upload_adc_raw
 * 功能描述 : 上报气体传感器 ADC 原始值，用于现场标定
 *           fault_manager 固定阈值。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_adc_raw(void);

/*
 * 函数名称 : can_app_upload_gas_threshold
 * 功能描述 : 上报气体传感器故障判定区间（下限+上限），用于核实
 *           CAN_CFG_GAS_SENSOR_RAW_MIN/MAX 配置命令是否生效。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败
 */
ErrStatus can_app_upload_gas_threshold(void);

/*
 * 函数名称 : can_app_upload_predict_status
 * 功能描述 : 上报温度预测功能当前状态（使能标志+4个分区历史累计触发次数），
 *           用于确认预警功能是否真的起作用。
 * 返 回 值 : SUCCESS / ERROR
 */
ErrStatus can_app_upload_predict_status(void);

/* 兼容旧代码的宏定义 */
#define can_handle_query               can_app_handle_query
#define can_upload_env                 can_app_upload_env
#define can_upload_state               can_app_upload_state
#define can_upload_system_state        can_app_upload_system_state
#define can_upload_fault               can_app_upload_fault
#define can_upload_temp                can_app_upload_temp
#define can_upload_threshold           can_app_upload_threshold
#define can_upload_guard_sleep         can_app_upload_guard_sleep
#define can_upload_guard_budget        can_app_upload_guard_budget
#define can_upload_adc_raw             can_app_upload_adc_raw
#define can_process_pending_uploads    can_app_process_pending_uploads

/* 直接暴露协议层函数（用于 ACK 响应） */
#define can_send_control_ack           can_protocol_send_control_ack
#define can_send_config_ack            can_protocol_send_config_ack

#ifdef __cplusplus
}
#endif

#endif /* CAN_APP_H */
