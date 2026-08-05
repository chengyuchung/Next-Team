#ifndef POWER_MANAGER_H
#define POWER_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

void power_manager_init(void);
//void power_manager_prepare_wakeup_source(void);
void power_manager_prepare_for_standby(void);
void power_manager_enter_standby(void);

#ifdef __cplusplus
}
#endif

#endif /* POWER_MANAGER_H */
