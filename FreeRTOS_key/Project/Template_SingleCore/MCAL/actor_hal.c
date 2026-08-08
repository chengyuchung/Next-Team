#include "actor_hal.h"
#include "gd32a7xx.h"
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : actor_hal (Hardware Abstraction Layer)
 * 文件功能 : 热管理执行器 GPIO 硬件抽象层
 * 设计目标 :
 *   1) 统一管理冷却、加热、蜂鸣器、泄压阀、继电器等开关量执行器的 GPIO 控制；
 *   2) 通过"逻辑通道 -> 物理引脚"映射，降低上层业务对板级细节的依赖；
 *   3) 提供高有效/低有效配置，适配不同外部驱动电路。
 *
 * 单位与约定 :
 *   - 逻辑通道：actor_channel_t 枚举值；
 *   - 使能值：1=打开，0=关闭；
 *   - active_level：高有效/低有效，用于适配不同外部驱动电路。
 * ============================================================================
 */

typedef struct {
    uint32_t port;
    uint32_t pin;
} actor_pin_map_t;

/*
 * 模块运行时状态缓存。
 * 说明：
 *   - s_state 保存每个逻辑通道的当前使能值和有效电平；
 *   - s_cfg 保存初始化时传入的默认配置。
 */
static actor_channel_state_t s_state[GPIO_CH_MAX];
static actor_config_t s_cfg;

/*
 * 逻辑通道到物理引脚的固定映射表。
 * 说明：
 *   - 仅保留执行器控制引脚；
 */
static const actor_pin_map_t s_pin_map[GPIO_CH_MAX] = {
    { GPIOF, GPIO_PIN_6 },   /* cooler1    PF6  - 制冷片1 (电池包方向1) */
    { GPIOF, GPIO_PIN_7 },   /* cooler2    PF7  - 制冷片2 (电池包方向2) */
    { GPIOF, GPIO_PIN_8 },   /* cooler3    PF8  - 制冷片3 (电池包方向3) */
    { GPIOF, GPIO_PIN_11 },  /* cooler4    PF11 - 制冷片4 (电池包方向4) */
    { GPIOF, GPIO_PIN_1 },   /* heater1    PF1  - PTC加热片1 (电池包方向1) */
    { GPIOF, GPIO_PIN_2 },   /* heater2    PF2  - PTC加热片2 (电池包方向2) */
    { GPIOF, GPIO_PIN_3 },   /* heater3    PF3  - PTC加热片3 (电池包方向3) */
    { GPIOF, GPIO_PIN_4 },   /* heater4    PF4  - PTC加热片4 (电池包方向4) */
    { GPIOF, GPIO_PIN_9 },   /* buzzer     PF9  */
    { GPIOF, GPIO_PIN_10 },  /* gate       PF10 */
    { GPIOG, GPIO_PIN_0 },   /* relay_pwr  PG0  */
    { GPIOG, GPIO_PIN_2 },   /* led_white  PG2  - 低温白灯 */
    { GPIOG, GPIO_PIN_3 },   /* led_green  PG3  - 正常绿灯 */
    { GPIOG, GPIO_PIN_4 },   /* led_yellow PG4  - 高温黄灯 */
    { GPIOG, GPIO_PIN_5 },   /* led_red    PG5  - 危险红灯 */
};

/*
 * 载入默认配置。
 * 默认策略：
 *   - 所有通道均按高电平有效；
 *   - 上电后默认全部关闭；
 *   - 具体默认开关状态可由上层在初始化时覆盖。
 */
static void actor_apply_default_config(void)
{
    uint8_t i;

    memset(&s_cfg, 0, sizeof(s_cfg));
    for(i = 0U; i < GPIO_CH_MAX; i++) {
        s_cfg.channel_cfg[i].active_level = ACTOR_ACTIVE_HIGH;
        s_cfg.channel_cfg[i].default_enable = 0U;
    }
}

/*
 * 写单个 GPIO 物理引脚。
 * 说明：
 *   - 上层只关心"逻辑上是否使能"；
 *   - 这里负责根据 active_level 自动翻转电平。
 */
static void actor_hw_write(actor_channel_t channel, uint8_t enable)
{
    uint8_t drive_high;

    if(channel >= GPIO_CH_MAX) {
        return;
    }

    if(s_state[channel].active_level == ACTOR_ACTIVE_HIGH) {
        drive_high = (enable != 0U) ? 1U : 0U;
    } else {
        drive_high = (enable != 0U) ? 0U : 1U;
    }

    if(drive_high != 0U) {
        gpio_bit_set(s_pin_map[channel].port, s_pin_map[channel].pin);
    } else {
        gpio_bit_reset(s_pin_map[channel].port, s_pin_map[channel].pin);
    }
}

/*
 * 初始化执行器 GPIO。
 * 执行内容：
 *   1) 清空运行状态；
 *   2) 装载默认配置；
 *   3) 使能对应 GPIO 时钟；
 *   4) 将所有逻辑通道配置为推挽输出；
 *   5) 按默认值写入初始输出电平。
 */
void actor_init(const actor_config_t *config)
{
    uint8_t i;

    memset(s_state, 0, sizeof(s_state));
    actor_apply_default_config();

    if(config != NULL) {
        for(i = 0U; i < GPIO_CH_MAX; i++) {
            s_cfg.channel_cfg[i].default_enable = config->channel_cfg[i].default_enable;
        }
    }

    rcu_periph_clock_enable(RCU_GPIOF);
    rcu_periph_clock_enable(RCU_GPIOG);

    for(i = 0U; i < GPIO_CH_MAX; i++) {
        gpio_mode_set(s_pin_map[i].port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, s_pin_map[i].pin);
        gpio_output_options_set(s_pin_map[i].port, GPIO_OTYPE_PP, GPIO_OSPEED_LEVEL_2, s_pin_map[i].pin);

        s_state[i].active_level = s_cfg.channel_cfg[i].active_level;
        s_state[i].enabled = (s_cfg.channel_cfg[i].default_enable != 0U) ? 1U : 0U;
        actor_hw_write((actor_channel_t)i, s_state[i].enabled);
    }
}

/*
 * 设置单个逻辑通道。
 * 说明：
 *   - 用于热管理状态机实时控制某一路执行器或指示灯；
 *   - 会同时更新软件状态和硬件输出。
 */
void actor_set_channel(actor_channel_t channel, uint8_t enable)
{
    if(channel >= GPIO_CH_MAX) {
        return;
    }

    s_state[channel].enabled = (enable != 0U) ? 1U : 0U;
    actor_hw_write(channel, s_state[channel].enabled);
}

/*
 * 读取单个逻辑通道状态。
 * 适合调试或上层做状态镜像同步时使用。
 */
void actor_get_channel(actor_channel_t channel, actor_channel_state_t *state)
{
    if((channel >= GPIO_CH_MAX) || (state == NULL)) {
        return;
    }

    *state = s_state[channel];
}

/*
 * 关闭全部执行器 GPIO。
 * 常用于进入低功耗前的统一收敛处理，避免执行器保持开启。
 */
void actor_set_all_off(void)
{
    uint8_t i;

    for(i = 0U; i < GPIO_CH_MAX; i++) {
        s_state[i].enabled = 0U;
        actor_hw_write((actor_channel_t)i, 0U);
    }
}

/*
 * 执行器 GPIO 自检。
 * 当前实现采用"逐路拉高再拉低"的方式做基础连通性验证。
 * 返回值：
 *   - 1U：自检执行完成；
 *   - 0U：预留失败接口（当前未实现更细粒度诊断）。
 */
uint8_t actor_self_test(void)
{
    uint8_t i;

    for(i = 0U; i < GPIO_CH_MAX; i++) {
        actor_hw_write((actor_channel_t)i, 1U);
        actor_hw_write((actor_channel_t)i, 0U);
    }

    return 1U;
}
