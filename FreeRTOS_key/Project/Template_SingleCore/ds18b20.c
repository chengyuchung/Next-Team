#include "ds18b20.h"
#include <stddef.h>
#include <string.h>

/*
 * ============================================================================
 * 模块名称 : ds18b20
 * 文件功能 : DS18B20 1-Wire 底层驱动 + GD32 平台适配实现
 * 设计目标 :
 *   1) 提供通用 1-Wire 时序读写接口；
 *   2) 通过 GD32 GPIO 适配层管理 4 路独立 DS18B20 通道；
 *   3) 向上层提供“按通道读取温度”的统一接口。
 *
 * 单位约定 :
 *   - 温度返回值：0.1°C（temperature_tenths）；
 *   - 延时参数：us（微秒）；
 *   - GPIO 端口/引脚：由 GD32 平台库定义。
 *
 * 时序说明 :
 *   1-Wire 对延时精度极其敏感（复位 480us、读采样窗口 15us 等）。本实现
 *   使用 Cortex-M7 的 DWT 周期计数器实现精确 us 级延时，而不是不可靠的
 *   空循环；SystemCoreClock 由 CMSIS 系统文件提供（本工程为 160MHz）。
 *
 * DS18B20 命令 :
 *   0xCC = Skip ROM（跳过 ROM，单点/统一寻址）
 *   0x44 = Convert T（启动温度转换，12bit 最长 750ms）
 *   0xBE = Read Scratchpad（读 9 字节暂存器，最后 1 字节为 CRC8）
 * ============================================================================
 */

#define DS18B20_CMD_SKIP_ROM        (0xCCU)
#define DS18B20_CMD_CONVERT_T       (0x44U)
#define DS18B20_CMD_READ_SCRATCH    (0xBEU)
#define DS18B20_SCRATCHPAD_LEN      (9U)
#define DS18B20_CONVERT_TIMEOUT_MS  (800U)   /* 12bit 转换上限 750ms，留余量 */

/* ----------------------------- DWT 精确延时 ----------------------------- */
/* SystemCoreClock 在 CMSIS 系统文件里定义（gd32a7xx.h 间接引入声明）。 */
static uint8_t s_dwt_ready = 0U;

static void ds18b20_dwt_init(void)
{
    volatile uint32_t start;
    volatile uint32_t end;

    /* 打开 trace，解锁并使能 DWT 周期计数器 */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    /* 部分 M7 需要写 LAR 解锁，用绝对地址避免 CMSIS 结构体差异导致编译问题 */
    *((volatile uint32_t *)0xE0001FB0UL) = 0xC5ACCE55UL;
    DWT->CYCCNT = 0U;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    /* 自检：确认计数器真的在走，否则回退到标定空循环 */
    start = DWT->CYCCNT;
    __NOP();
    __NOP();
    __NOP();
    end = DWT->CYCCNT;
    s_dwt_ready = (end != start) ? 1U : 0U;
}

/* ----------------------------- 通用 1-Wire 驱动 ----------------------------- */

/* Maxim/Dallas 1-Wire CRC8 (多项式 X^8+X^5+X^4+1, 0x8C 反射)。 */
static uint8_t ds18b20_crc8(const uint8_t *data, uint8_t len)
{
    uint8_t crc = 0U;
    uint8_t i;
    uint8_t j;

    for(i = 0U; i < len; i++) {
        uint8_t inbyte = data[i];
        for(j = 0U; j < 8U; j++) {
            uint8_t mix = (uint8_t)((crc ^ inbyte) & 0x01U);
            crc >>= 1;
            if(mix != 0U) {
                crc ^= 0x8CU;
            }
            inbyte >>= 1;
        }
    }
    return crc;
}
static void ds18b20_write_one_wire(ds18b20_t *dev, uint8_t level)
{
    if((dev != NULL) && (dev->bus.write_level != NULL)) {
        dev->bus.write_level(level, dev->bus.user_ctx);
    }
}

static uint8_t ds18b20_read_one_wire(ds18b20_t *dev)
{
    if((dev != NULL) && (dev->bus.read_level != NULL)) {
        return dev->bus.read_level(dev->bus.user_ctx);
    }
    return 1U;
}

static void ds18b20_delay(ds18b20_t *dev, uint32_t us)
{
    if((dev != NULL) && (dev->bus.delay_us != NULL)) {
        dev->bus.delay_us(us, dev->bus.user_ctx);
    }
}

void ds18b20_init(ds18b20_t *dev, const ds18b20_bus_ops_t *ops)
{
    if((dev == NULL) || (ops == NULL)) {
        return;
    }
    dev->bus = *ops;
}

uint8_t ds18b20_reset(ds18b20_t *dev)
{
    uint8_t presence = 0U;

    if(dev == NULL) {
        return 0U;
    }

    if(dev->bus.set_output != NULL) {
        dev->bus.set_output(dev->bus.user_ctx);
    }

    ds18b20_write_one_wire(dev, 0U);
    ds18b20_delay(dev, 480U);

    if(dev->bus.set_input != NULL) {
        dev->bus.set_input(dev->bus.user_ctx);
    }
    ds18b20_delay(dev, 70U);

    presence = (uint8_t)(ds18b20_read_one_wire(dev) == 0U ? 1U : 0U);
    ds18b20_delay(dev, 410U);
    return presence;
}

void ds18b20_write_bit(ds18b20_t *dev, uint8_t bit)
{
    if(dev == NULL) {
        return;
    }

    if(dev->bus.set_output != NULL) {
        dev->bus.set_output(dev->bus.user_ctx);
    }

    if(bit != 0U) {
        ds18b20_write_one_wire(dev, 0U);
        ds18b20_delay(dev, 6U);
        ds18b20_write_one_wire(dev, 1U);
        ds18b20_delay(dev, 64U);
    } else {
        ds18b20_write_one_wire(dev, 0U);
        ds18b20_delay(dev, 60U);
        ds18b20_write_one_wire(dev, 1U);
        ds18b20_delay(dev, 10U);
    }
}

uint8_t ds18b20_read_bit(ds18b20_t *dev)
{
    uint8_t bit = 1U;

    if(dev == NULL) {
        return 1U;
    }

    if(dev->bus.set_output != NULL) {
        dev->bus.set_output(dev->bus.user_ctx);
    }

    ds18b20_write_one_wire(dev, 0U);
    ds18b20_delay(dev, 6U);

    if(dev->bus.set_input != NULL) {
        dev->bus.set_input(dev->bus.user_ctx);
    }

    ds18b20_delay(dev, 9U);
    bit = ds18b20_read_one_wire(dev);
    ds18b20_delay(dev, 55U);
    return bit;
}

void ds18b20_write_byte(ds18b20_t *dev, uint8_t data)
{
    uint8_t i;

    if(dev == NULL) {
        return;
    }

    for(i = 0U; i < 8U; i++) {
        ds18b20_write_bit(dev, (uint8_t)(data & 0x01U));
        data >>= 1;
    }
}

uint8_t ds18b20_read_byte(ds18b20_t *dev)
{
    uint8_t i;
    uint8_t data = 0U;

    if(dev == NULL) {
        return 0U;
    }

    for(i = 0U; i < 8U; i++) {
        if(ds18b20_read_bit(dev) != 0U) {
            data |= (uint8_t)(1U << i);
        }
    }
    return data;
}

/* 启动一次温度转换：复位 -> Skip ROM -> Convert T。
 * 返回 1 表示检测到器件并已发出转换命令，0 表示总线上无器件。 */
uint8_t ds18b20_start_conversion(ds18b20_t *dev)
{
    if(dev == NULL) {
        return 0U;
    }

    if(ds18b20_reset(dev) == 0U) {
        return 0U;   /* 无 presence 脉冲：器件缺失或接线断开 */
    }

    ds18b20_write_byte(dev, DS18B20_CMD_SKIP_ROM);
    ds18b20_write_byte(dev, DS18B20_CMD_CONVERT_T);
    return 1U;
}

/* 等待转换完成。外部供电时器件在转换期间持续输出 0，完成后拉高到 1。
 * 通过读时隙轮询该状态位，最多等待 DS18B20_CONVERT_TIMEOUT_MS。 */
void ds18b20_wait_conversion(ds18b20_t *dev)
{
    uint32_t waited_us = 0U;
    const uint32_t timeout_us = (uint32_t)DS18B20_CONVERT_TIMEOUT_MS * 1000U;

    if(dev == NULL) {
        return;
    }

    while(waited_us < timeout_us) {
        if(ds18b20_read_bit(dev) != 0U) {
            break;   /* 转换完成 */
        }
        /* read_bit 本身约占 70us，这里再补足到 ~1ms 粒度 */
        ds18b20_delay(dev, 930U);
        waited_us += 1000U;
    }
}

/* 读取 9 字节暂存器，做 CRC8 校验，并把原始寄存器值换算成 0.1°C。
 * 返回 1=CRC 通过，temperature_tenths 输出温度；0=CRC 失败/断线。 */
uint8_t ds18b20_read_scratchpad_temp(ds18b20_t *dev, int16_t *temperature_tenths)
{
    uint8_t scratch[DS18B20_SCRATCHPAD_LEN];
    uint8_t i;
    int16_t raw;

    if((dev == NULL) || (temperature_tenths == NULL)) {
        return 0U;
    }

    if(ds18b20_reset(dev) == 0U) {
        return 0U;
    }

    ds18b20_write_byte(dev, DS18B20_CMD_SKIP_ROM);
    ds18b20_write_byte(dev, DS18B20_CMD_READ_SCRATCH);

    for(i = 0U; i < DS18B20_SCRATCHPAD_LEN; i++) {
        scratch[i] = ds18b20_read_byte(dev);
    }

    /* 断线常读出全 0xFF 或全 0x00，两者都无法通过 CRC，直接判失效 */
    if(ds18b20_crc8(scratch, 8U) != scratch[8]) {
        return 0U;
    }

    raw = (int16_t)(((uint16_t)scratch[1] << 8) | scratch[0]);
    /* 12bit 分辨率：1 LSB = 1/16 °C，换算到 0.1°C */
    *temperature_tenths = (int16_t)(((int32_t)raw * 10L) / 16L);
    return 1U;
}

uint8_t ds18b20_read_temperature(ds18b20_t *dev, int16_t *temperature_tenths)
{
    if((dev == NULL) || (temperature_tenths == NULL)) {
        return 0U;
    }

    if(ds18b20_start_conversion(dev) == 0U) {
        return 0U;
    }

    ds18b20_wait_conversion(dev);

    return ds18b20_read_scratchpad_temp(dev, temperature_tenths);
}

/* ----------------------------- GD32 平台适配层 ----------------------------- */
static ds18b20_gd32_channel_handle_t s_channels[DS18B20_GD32_CHANNEL_COUNT];

static void ds18b20_gd32_set_output(void *user_ctx)
{
    ds18b20_gd32_channel_handle_t *ch = (ds18b20_gd32_channel_handle_t *)user_ctx;
    if(ch == NULL) {
        return;
    }

    gpio_mode_set(ch->gpio_port, GPIO_MODE_OUTPUT, GPIO_PUPD_PULLUP, ch->gpio_pin);
    gpio_output_options_set(ch->gpio_port, GPIO_OTYPE_OD, GPIO_OSPEED_LEVEL_2, ch->gpio_pin);
}

static void ds18b20_gd32_set_input(void *user_ctx)
{
    ds18b20_gd32_channel_handle_t *ch = (ds18b20_gd32_channel_handle_t *)user_ctx;
    if(ch == NULL) {
        return;
    }

    gpio_mode_set(ch->gpio_port, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, ch->gpio_pin);
}

static void ds18b20_gd32_write_level(uint8_t level, void *user_ctx)
{
    ds18b20_gd32_channel_handle_t *ch = (ds18b20_gd32_channel_handle_t *)user_ctx;
    if((ch == NULL) || (ch->gpio_port == 0U)) {
        return;
    }

    if(level != 0U) {
        gpio_bit_set(ch->gpio_port, ch->gpio_pin);
    } else {
        gpio_bit_reset(ch->gpio_port, ch->gpio_pin);
    }
}

static uint8_t ds18b20_gd32_read_level(void *user_ctx)
{
    ds18b20_gd32_channel_handle_t *ch = (ds18b20_gd32_channel_handle_t *)user_ctx;
    if((ch == NULL) || (ch->gpio_port == 0U)) {
        return 1U;
    }

    return (gpio_input_bit_get(ch->gpio_port, ch->gpio_pin) != RESET) ? 1U : 0U;
}

static void ds18b20_gd32_delay_us(uint32_t us, void *user_ctx)
{
    (void)user_ctx;

    if(us == 0U) {
        return;
    }

    if(s_dwt_ready != 0U) {
        /* 精确路径：用 DWT 周期计数器等待 us*(SystemCoreClock/1e6) 个周期。
         * 无符号减法天然处理计数器回绕。 */
        uint32_t cycles_per_us = SystemCoreClock / 1000000U;
        uint32_t target = us * cycles_per_us;
        uint32_t start = DWT->CYCCNT;

        while((DWT->CYCCNT - start) < target) {
            /* busy wait */
        }
    } else {
        /* 回退路径：按 160MHz 粗略标定的空循环（每次迭代约若干周期）。
         * 只在 DWT 不可用时使用，精度较差但可保证程序不卡死。 */
        volatile uint32_t i;
        uint32_t loops = us * (SystemCoreClock / 1000000U) / 4U;
        for(i = 0U; i < loops; i++) {
            __NOP();
        }
    }
}

void ds18b20_gd32_adapter_init(void)
{
    static const struct {
        uint32_t port;
        uint32_t pin;
    } cfg[DS18B20_GD32_CHANNEL_COUNT] = {
        { GPIOI, GPIO_PIN_9 },
        { GPIOI, GPIO_PIN_10 },
        { GPIOI, GPIO_PIN_11 },
        { GPIOL, GPIO_PIN_0 },
    };

    uint8_t i;

    memset(s_channels, 0, sizeof(s_channels));

    /* 使能 DWT 周期计数器，供精确 us 级延时使用 */
    ds18b20_dwt_init();

    rcu_periph_clock_enable(RCU_GPIOI);
    rcu_periph_clock_enable(RCU_GPIOL);

    for(i = 0U; i < DS18B20_GD32_CHANNEL_COUNT; i++) {
        s_channels[i].gpio_port = cfg[i].port;
        s_channels[i].gpio_pin = cfg[i].pin;
        s_channels[i].valid = 1U;
        s_channels[i].bus_ops.set_output = ds18b20_gd32_set_output;
        s_channels[i].bus_ops.set_input = ds18b20_gd32_set_input;
        s_channels[i].bus_ops.write_level = ds18b20_gd32_write_level;
        s_channels[i].bus_ops.read_level = ds18b20_gd32_read_level;
        s_channels[i].bus_ops.delay_us = ds18b20_gd32_delay_us;
        s_channels[i].bus_ops.user_ctx = &s_channels[i];
        ds18b20_init(&s_channels[i].dev, &s_channels[i].bus_ops);
        ds18b20_gd32_set_input(&s_channels[i]);
    }
}

ds18b20_t *ds18b20_gd32_get_device(ds18b20_gd32_channel_t channel)
{
    if((channel >= DS18B20_GD32_CH_MAX) || (s_channels[channel].valid == 0U)) {
        return NULL;
    }
    return &s_channels[channel].dev;
}

uint8_t ds18b20_gd32_channel_valid(ds18b20_gd32_channel_t channel)
{
    if(channel >= DS18B20_GD32_CH_MAX) {
        return 0U;
    }
    return s_channels[channel].valid;
}

uint8_t ds18b20_gd32_read_temperature(ds18b20_gd32_channel_t channel, int16_t *temperature_tenths)
{
    if((channel >= DS18B20_GD32_CH_MAX) || (temperature_tenths == NULL) || (s_channels[channel].valid == 0U)) {
        return 0U;
    }

    return ds18b20_read_temperature(&s_channels[channel].dev, temperature_tenths);
}
