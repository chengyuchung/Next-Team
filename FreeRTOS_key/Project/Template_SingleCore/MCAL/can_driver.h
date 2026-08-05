#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ============================================================================
 * 模块名称 : can_driver
 * 文件功能 : CAN 硬件驱动层（MCAL 层）
 *
 * 设计目标 :
 *   1) 封装 CAN 硬件初始化（GPIO、时钟、外设配置）；
 *   2) 提供底层收发接口（标准帧、扩展帧）；
 *   3) 不包含任何协议或应用层逻辑。
 *
 * 解耦原则 :
 *   - MCAL 层只知道硬件资源，不知道 CAN 报文的业务含义；
 *   - 协议层和应用层通过调用本模块接口完成通信。
 * ============================================================================
 */

/*
 * 函数名称 : can_driver_gpio_config
 * 功能描述 : 初始化 CAN 相关的 GPIO 和时钟。
 * 输入参数 : 无
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void can_driver_gpio_config(void);

/*
 * 函数名称 : can_driver_config
 * 功能描述 : 配置指定 CAN 控制器的参数（波特率、滤波器等）。
 * 输入参数 :
 *   - dtm_canx      : CAN 控制器编号（DTM_CAN0~DTM_CAN7）
 *   - baudrate_khz  : 波特率，单位 kHz（如 500 表示 500kbps）
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void can_driver_config(can_dtm_canx_enum dtm_canx, uint32_t baudrate_khz);

/*
 * 函数名称 : can_driver_send_std_frame
 * 功能描述 : 发送标准帧（11bit ID）。
 * 输入参数 :
 *   - dtm_canx : CAN 控制器编号
 *   - std_id   : 标准帧 ID（11bit）
 *   - data     : 数据缓冲区指针
 *   - len      : 数据长度（0~8）
 * 输出参数 : 无
 * 返 回 值 :
 *   - SUCCESS : 发送成功
 *   - ERROR   : 发送失败（邮箱满或参数错误）
 */
ErrStatus can_driver_send_std_frame(can_dtm_canx_enum dtm_canx, uint32_t std_id, uint8_t *data, uint8_t len);

/*
 * 函数名称 : can_driver_enable_rx_interrupt
 * 功能描述 : 使能 CAN 接收中断。
 * 输入参数 :
 *   - dtm_canx       : CAN 控制器编号
 *   - irqn_priority  : 中断优先级
 * 输出参数 : 无
 * 返 回 值 : 无
 */
void can_driver_enable_rx_interrupt(can_dtm_canx_enum dtm_canx, uint8_t irqn_priority);

#ifdef __cplusplus
}
#endif

#endif /* CAN_DRIVER_H */
