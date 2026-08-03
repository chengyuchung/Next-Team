#ifndef MAIN_H
#define MAIN_H

#include "gd32a7xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* CPU cache */
void cache_enable(void);

/* ignition output control (defined in main.c) */
void ignition_set(uint8_t on);
uint8_t ignition_get(void);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */
