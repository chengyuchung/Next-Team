#include "ignition_control.h"
#include "App/thermal_control.h"
#include "BSW/Services/can_protocol.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

/*
 * ============================================================================
 * 模块名称 : ignition_control
 * 文件功能 : 点火控制业务逻辑
 * 
 * 实现说明 :
 *   1) 封装点火任务逻辑（阻塞等待信号量 + 安全检查 + 切换点火状态）；
 *   2) 提供 CAN 命令处理接口（ignite/extinguish）；
 *   3) 集成 thermal_control 的点火锁定检查。
 * ============================================================================
 */

/* 点火信号量（由 KEY_3 按键 ISR 触发） */
static SemaphoreHandle_t s_ignition_sem = NULL;

void ignition_control_init(SemaphoreHandle_t ignition_sem)
{
    s_ignition_sem = ignition_sem;
}

void ignition_control_task(void *pvParameters)
{
    (void)pvParameters;

    for( ;; ) {
        if(xSemaphoreTake(s_ignition_sem, portMAX_DELAY) == pdTRUE) {
            /* DANGER 状态下点火被锁定，忽略此次按键请求，
             * 保证点火始终保持在强制关闭状态。 */
            if(thermal_control_is_ignition_locked() == 0U) {
                ignition_set((uint8_t)!ignition_get());
            }
        }
    }
}

uint8_t ignition_control_handle_ignite(void)
{
    /* DANGER 锁定时禁止打火 */
    if(thermal_control_is_ignition_locked() != 0U) {
        return CAN_ACK_REJECTED;
    }
    ignition_set(1U);
    return CAN_ACK_OK;
}

uint8_t ignition_control_handle_extinguish(void)
{
    ignition_set(0U);
    return CAN_ACK_OK;
}
