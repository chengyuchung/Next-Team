#include "power_manager.h"
#include "gd32a7xx.h"
#include "gd32a7xx_pmu.h"
#include "gd32a712_evb.h"

void power_manager_init(void)
{
    /* clear PMU sticky flags after reset / wakeup */
    pmu_all_flags_clear();
}

void power_manager_prepare_wakeup_source(void)
{
    /*
     * KEY_4 is used as the standby wakeup trigger (it is also the
     * guard/normal-mode toggle in the running firmware, so a single
     * key serves both purposes).
     * Keep the official demo style EXTI path here.
     */
    gd_eval_key_init(KEY_4, KEY_MODE_EXTI);

    exti_init(EXTI_52, EXTI_INTERRUPT, EXTI_TRIG_RISING);
    exti_interrupt_enable(EXTI_52);
    nvic_irq_enable(EXTI42_101_IRQn, 2U, 0U);
}

static void power_manager_lowpower_clock_config(void)
{
    /* switch system clock to IRC48M first */
    rcu_system_clock_source_config(RCU_CKSYSSRC_IRC48M);
    while(RCU_SCSS_IRC48M != (RCU_CFG0 & RCU_CFG0_SCSS));

    /* turn off PLL & HXTAL */
    rcu_osci_off(RCU_PLL_CK);
    rcu_osci_off(RCU_HXTAL);
}

void power_manager_prepare_for_standby(void)
{
    /* clear PMU flags again before entering standby */
    pmu_all_flags_clear();

    /* reduce power by turning off unnecessary high-speed clock sources */
    power_manager_lowpower_clock_config();
}

void power_manager_enter_standby(void)
{
    power_manager_prepare_wakeup_source();
    power_manager_prepare_for_standby();
    pmu_to_standbymode();
}
