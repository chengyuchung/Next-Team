/*!
    \file    gd32a7xx_gpio.h
    \brief   definitions for the GPIO

    \version 2025-08-06, V0.1.0, firmware for GD32A7xx
*/

/*
    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#ifndef GD32A7XX_GPIO_H
#define GD32A7XX_GPIO_H

#include "gd32a7xx.h"

/* GPIOx(x=A,B,C,D,E,F) definitions */
#define GPIOA                      (GPIO_BASE + 0x00000000U)       /*!< GPIOA bsae address */
#define GPIOB                      (GPIO_BASE + 0x00000400U)       /*!< GPIOB bsae address */
#define GPIOC                      (GPIO_BASE + 0x00000800U)       /*!< GPIOC bsae address */
#define GPIOD                      (GPIO_BASE + 0x00000C00U)       /*!< GPIOD bsae address */
#define GPIOE                      (GPIO_BASE + 0x00001000U)       /*!< GPIOE bsae address */
#define GPIOF                      (GPIO_BASE + 0x00001400U)       /*!< GPIOF bsae address */
#define GPIOG                      (GPIO_BASE + 0x00001800U)       /*!< GPIOG bsae address */
#define GPIOH                      (GPIO_BASE + 0x00001C00U)       /*!< GPIOH bsae address */
#define GPIOI                      (GPIO_BASE + 0x00002000U)       /*!< GPIOI bsae address */
#define GPIOJ                      (GPIO_BASE + 0x00002400U)       /*!< GPIOJ bsae address */
#define GPIOK                      (GPIO_BASE + 0x00002800U)       /*!< GPIOK bsae address */
#define GPIOL                      (GPIO_BASE + 0x00002C00U)       /*!< GPIOL bsae address */
#define GPIOM                      (GPIO_BASE + 0x00003000U)       /*!< GPIOM bsae address */
#define GPION                      (GPIO_BASE + 0x00003400U)       /*!< GPION bsae address */

/* registers definitions */
#define GPIO_CTL(gpiox)            REG32((gpiox) + 0x00000000U)    /*!< GPIO port control register */
#define GPIO_OMODE(gpiox)          REG32((gpiox) + 0x00000004U)    /*!< GPIO port output mode register */
#define GPIO_OSPD(gpiox)           REG32((gpiox) + 0x00000008U)    /*!< GPIO port output speed register */
#define GPIO_PUD(gpiox)            REG32((gpiox) + 0x0000000CU)    /*!< GPIO port pull-up/pull-down register */
#define GPIO_ISTAT(gpiox)          REG32((gpiox) + 0x00000010U)    /*!< GPIO port input status register */
#define GPIO_OCTL(gpiox)           REG32((gpiox) + 0x00000014U)    /*!< GPIO port output control register */
#define GPIO_BOP(gpiox)            REG32((gpiox) + 0x00000018U)    /*!< GPIO port bit operation register */
#define GPIO_LOCK(gpiox)           REG32((gpiox) + 0x0000001CU)    /*!< GPIO port configuration lock register */
#define GPIO_AFSEL0(gpiox)         REG32((gpiox) + 0x00000020U)    /*!< GPIO alternate function selected register 0 */
#define GPIO_AFSEL1(gpiox)         REG32((gpiox) + 0x00000024U)    /*!< GPIO alternate function selected register 1 */
#define GPIO_BC(gpiox)             REG32((gpiox) + 0x00000028U)    /*!< GPIO bit clear register */
#define GPIO_TG(gpiox)             REG32((gpiox) + 0x0000002CU)    /*!< GPIO port bit toggle register */
#define GPIO_SMCCTL(gpiox)         REG32((gpiox) + 0x00000038U)    /*!< GPIO port safe mode control register */
#define GPIO_IFEN(gpiox)           REG32((gpiox) + 0x0000003CU)    /*!< GPIO port filtering enable register */
#define GPIO_PREN(gpiox)           REG32((gpiox) + 0x00000040U)    /*!< GPIO port retain enable register */
#define GPIO_SREN(gpiox)           REG32((gpiox) + 0x00000044U)    /*!< GPIO port slew rate enable register */
#define GPIO_IFCTL(gpiox)          REG32((gpiox) + 0x00000048U)    /*!< GPIO interrupt filtering control register */
#define GPIO_IFSCCTL0(gpiox)       REG32((gpiox) + 0x0000004CU)    /*!< GPIO interrupt filtering sample counter control register 0 */
#define GPIO_IFSCCTL1(gpiox)       REG32((gpiox) + 0x00000050U)    /*!< GPIO interrupt filtering sample counter control register 1 */
#define GPIO_TMRASTAT(gpiox)       REG32((gpiox) + 0x00000054U)    /*!< GPIO TMR alarm status register */

/* bits definitions */
/* GPIO_CTL */
#define GPIO_CTL_CTL0              BITS(0, 1)                      /*!< pin 0 configuration bits */ 
#define GPIO_CTL_CTL1              BITS(2, 3)                      /*!< pin 1 configuration bits */
#define GPIO_CTL_CTL2              BITS(4, 5)                      /*!< pin 2 configuration bits */
#define GPIO_CTL_CTL3              BITS(6, 7)                      /*!< pin 3 configuration bits */
#define GPIO_CTL_CTL4              BITS(8, 9)                      /*!< pin 4 configuration bits */
#define GPIO_CTL_CTL5              BITS(10, 11)                    /*!< pin 5 configuration bits */
#define GPIO_CTL_CTL6              BITS(12, 13)                    /*!< pin 6 configuration bits */
#define GPIO_CTL_CTL7              BITS(14, 15)                    /*!< pin 7 configuration bits */
#define GPIO_CTL_CTL8              BITS(16, 17)                    /*!< pin 8 configuration bits */
#define GPIO_CTL_CTL9              BITS(18, 19)                    /*!< pin 9 configuration bits */
#define GPIO_CTL_CTL10             BITS(20, 21)                    /*!< pin 10 configuration bits */
#define GPIO_CTL_CTL11             BITS(22, 23)                    /*!< pin 11 configuration bits */
#define GPIO_CTL_CTL12             BITS(24, 25)                    /*!< pin 12 configuration bits */
#define GPIO_CTL_CTL13             BITS(26, 27)                    /*!< pin 13 configuration bits */
#define GPIO_CTL_CTL14             BITS(28, 29)                    /*!< pin 14 configuration bits */
#define GPIO_CTL_CTL15             BITS(30, 31)                    /*!< pin 15 configuration bits */

/* GPIO_OMODE */
#define GPIO_OMODE_OM0             BIT(0)                          /*!< pin 0 output mode bit */
#define GPIO_OMODE_OM1             BIT(1)                          /*!< pin 1 output mode bit */
#define GPIO_OMODE_OM2             BIT(2)                          /*!< pin 2 output mode bit */
#define GPIO_OMODE_OM3             BIT(3)                          /*!< pin 3 output mode bit */
#define GPIO_OMODE_OM4             BIT(4)                          /*!< pin 4 output mode bit */
#define GPIO_OMODE_OM5             BIT(5)                          /*!< pin 5 output mode bit */
#define GPIO_OMODE_OM6             BIT(6)                          /*!< pin 6 output mode bit */
#define GPIO_OMODE_OM7             BIT(7)                          /*!< pin 7 output mode bit */
#define GPIO_OMODE_OM8             BIT(8)                          /*!< pin 8 output mode bit */
#define GPIO_OMODE_OM9             BIT(9)                          /*!< pin 9 output mode bit */
#define GPIO_OMODE_OM10            BIT(10)                         /*!< pin 10 output mode bit */
#define GPIO_OMODE_OM11            BIT(11)                         /*!< pin 11 output mode bit */
#define GPIO_OMODE_OM12            BIT(12)                         /*!< pin 12 output mode bit */
#define GPIO_OMODE_OM13            BIT(13)                         /*!< pin 13 output mode bit */
#define GPIO_OMODE_OM14            BIT(14)                         /*!< pin 14 output mode bit */
#define GPIO_OMODE_OM15            BIT(15)                         /*!< pin 15 output mode bit */

/* GPIO_OSPD */
#define GPIO_OSPD_OSPD0            BITS(0,1)                       /*!< pin 0 output max speed bits */
#define GPIO_OSPD_OSPD1            BIT(2)                          /*!< pin 1 output max speed bits */
#define GPIO_OSPD_OSPD2            BIT(4)                          /*!< pin 2 output max speed bits */
#define GPIO_OSPD_OSPD3            BITS(6,7)                       /*!< pin 3 output max speed bits */
#define GPIO_OSPD_OSPD4            BIT(8)                          /*!< pin 4 output max speed bits */
#define GPIO_OSPD_OSPD5            BITS(10,11)                     /*!< pin 5 output max speed bits */
#define GPIO_OSPD_OSPD6            BIT(12)                         /*!< pin 6 output max speed bits */
#define GPIO_OSPD_OSPD7            BIT(14)                         /*!< pin 7 output max speed bits */
#define GPIO_OSPD_OSPD8            BIT(16)                         /*!< pin 8 output max speed bits */
#define GPIO_OSPD_OSPD9            BIT(18)                         /*!< pin 9 output max speed bits */
#define GPIO_OSPD_OSPD10           BIT(20)                         /*!< pin 10 output max speed bits */
#define GPIO_OSPD_OSPD11           BIT(22)                         /*!< pin 11 output max speed bits */
#define GPIO_OSPD_OSPD12           BIT(24)                         /*!< pin 12 output max speed bits */
#define GPIO_OSPD_OSPD13           BIT(26)                         /*!< pin 13 output max speed bits */
#define GPIO_OSPD_OSPD14           BIT(28)                         /*!< pin 14 output max speed bits */
#define GPIO_OSPD_OSPD15           BIT(30)                         /*!< pin 15 output max speed bits */

/* GPIO_PUD */
#define GPIO_PUD_PUD0              BITS(0, 1)                      /*!< pin 0 pull-up or pull-down bits */
#define GPIO_PUD_PUD1              BITS(2, 3)                      /*!< pin 1 pull-up or pull-down bits */
#define GPIO_PUD_PUD2              BITS(4, 5)                      /*!< pin 2 pull-up or pull-down bits */
#define GPIO_PUD_PUD3              BITS(6, 7)                      /*!< pin 3 pull-up or pull-down bits */
#define GPIO_PUD_PUD4              BITS(8, 9)                      /*!< pin 4 pull-up or pull-down bits */
#define GPIO_PUD_PUD5              BITS(10, 11)                    /*!< pin 5 pull-up or pull-down bits */
#define GPIO_PUD_PUD6              BITS(12, 13)                    /*!< pin 6 pull-up or pull-down bits */
#define GPIO_PUD_PUD7              BITS(14, 15)                    /*!< pin 7 pull-up or pull-down bits */
#define GPIO_PUD_PUD8              BITS(16, 17)                    /*!< pin 8 pull-up or pull-down bits */
#define GPIO_PUD_PUD9              BITS(18, 19)                    /*!< pin 9 pull-up or pull-down bits */
#define GPIO_PUD_PUD10             BITS(20, 21)                    /*!< pin 10 pull-up or pull-down bits */
#define GPIO_PUD_PUD11             BITS(22, 23)                    /*!< pin 11 pull-up or pull-down bits */
#define GPIO_PUD_PUD12             BITS(24, 25)                    /*!< pin 12 pull-up or pull-down bits */
#define GPIO_PUD_PUD13             BITS(26, 27)                    /*!< pin 13 pull-up or pull-down bits */
#define GPIO_PUD_PUD14             BITS(28, 29)                    /*!< pin 14 pull-up or pull-down bits */
#define GPIO_PUD_PUD15             BITS(30, 31)                    /*!< pin 15 pull-up or pull-down bits */

/* GPIO_ISTAT */
#define GPIO_ISTAT_ISTAT0          BIT(0)                          /*!< pin 0 input status */
#define GPIO_ISTAT_ISTAT1          BIT(1)                          /*!< pin 1 input status */
#define GPIO_ISTAT_ISTAT2          BIT(2)                          /*!< pin 2 input status */
#define GPIO_ISTAT_ISTAT3          BIT(3)                          /*!< pin 3 input status */
#define GPIO_ISTAT_ISTAT4          BIT(4)                          /*!< pin 4 input status */
#define GPIO_ISTAT_ISTAT5          BIT(5)                          /*!< pin 5 input status */
#define GPIO_ISTAT_ISTAT6          BIT(6)                          /*!< pin 6 input status */
#define GPIO_ISTAT_ISTAT7          BIT(7)                          /*!< pin 7 input status */
#define GPIO_ISTAT_ISTAT8          BIT(8)                          /*!< pin 8 input status */
#define GPIO_ISTAT_ISTAT9          BIT(9)                          /*!< pin 9 input status */
#define GPIO_ISTAT_ISTAT10         BIT(10)                         /*!< pin 10 input status */
#define GPIO_ISTAT_ISTAT11         BIT(11)                         /*!< pin 11 input status */
#define GPIO_ISTAT_ISTAT12         BIT(12)                         /*!< pin 12 input status */
#define GPIO_ISTAT_ISTAT13         BIT(13)                         /*!< pin 13 input status */
#define GPIO_ISTAT_ISTAT14         BIT(14)                         /*!< pin 14 input status */
#define GPIO_ISTAT_ISTAT15         BIT(15)                         /*!< pin 15 input status */

/* GPIO_OCTL */
#define GPIO_OCTL_OCTL0            BIT(0)                          /*!< pin 0 output bit */
#define GPIO_OCTL_OCTL1            BIT(1)                          /*!< pin 1 output bit */
#define GPIO_OCTL_OCTL2            BIT(2)                          /*!< pin 2 output bit */
#define GPIO_OCTL_OCTL3            BIT(3)                          /*!< pin 3 output bit */
#define GPIO_OCTL_OCTL4            BIT(4)                          /*!< pin 4 output bit */
#define GPIO_OCTL_OCTL5            BIT(5)                          /*!< pin 5 output bit */
#define GPIO_OCTL_OCTL6            BIT(6)                          /*!< pin 6 output bit */
#define GPIO_OCTL_OCTL7            BIT(7)                          /*!< pin 7 output bit */
#define GPIO_OCTL_OCTL8            BIT(8)                          /*!< pin 8 output bit */
#define GPIO_OCTL_OCTL9            BIT(9)                          /*!< pin 9 output bit */
#define GPIO_OCTL_OCTL10           BIT(10)                         /*!< pin 10 output bit */
#define GPIO_OCTL_OCTL11           BIT(11)                         /*!< pin 11 output bit */
#define GPIO_OCTL_OCTL12           BIT(12)                         /*!< pin 12 output bit */
#define GPIO_OCTL_OCTL13           BIT(13)                         /*!< pin 13 output bit */
#define GPIO_OCTL_OCTL14           BIT(14)                         /*!< pin 14 output bit */
#define GPIO_OCTL_OCTL15           BIT(15)                         /*!< pin 15 output bit */

/* GPIO_BOP */
#define GPIO_BOP_BOP0              BIT(0)                          /*!< pin 0 set bit */
#define GPIO_BOP_BOP1              BIT(1)                          /*!< pin 1 set bit */
#define GPIO_BOP_BOP2              BIT(2)                          /*!< pin 2 set bit */
#define GPIO_BOP_BOP3              BIT(3)                          /*!< pin 3 set bit */
#define GPIO_BOP_BOP4              BIT(4)                          /*!< pin 4 set bit */
#define GPIO_BOP_BOP5              BIT(5)                          /*!< pin 5 set bit */
#define GPIO_BOP_BOP6              BIT(6)                          /*!< pin 6 set bit */
#define GPIO_BOP_BOP7              BIT(7)                          /*!< pin 7 set bit */
#define GPIO_BOP_BOP8              BIT(8)                          /*!< pin 8 set bit */
#define GPIO_BOP_BOP9              BIT(9)                          /*!< pin 9 set bit */
#define GPIO_BOP_BOP10             BIT(10)                         /*!< pin 10 set bit */
#define GPIO_BOP_BOP11             BIT(11)                         /*!< pin 11 set bit */
#define GPIO_BOP_BOP12             BIT(12)                         /*!< pin 12 set bit */
#define GPIO_BOP_BOP13             BIT(13)                         /*!< pin 13 set bit */
#define GPIO_BOP_BOP14             BIT(14)                         /*!< pin 14 set bit */
#define GPIO_BOP_BOP15             BIT(15)                         /*!< pin 15 set bit */
#define GPIO_BOP_CR0               BIT(16)                         /*!< pin 0 clear bit */
#define GPIO_BOP_CR1               BIT(17)                         /*!< pin 1 clear bit */
#define GPIO_BOP_CR2               BIT(18)                         /*!< pin 2 clear bit */
#define GPIO_BOP_CR3               BIT(19)                         /*!< pin 3 clear bit */
#define GPIO_BOP_CR4               BIT(20)                         /*!< pin 4 clear bit */
#define GPIO_BOP_CR5               BIT(21)                         /*!< pin 5 clear bit */
#define GPIO_BOP_CR6               BIT(22)                         /*!< pin 6 clear bit */
#define GPIO_BOP_CR7               BIT(23)                         /*!< pin 7 clear bit */
#define GPIO_BOP_CR8               BIT(24)                         /*!< pin 8 clear bit */
#define GPIO_BOP_CR9               BIT(25)                         /*!< pin 9 clear bit */
#define GPIO_BOP_CR10              BIT(26)                         /*!< pin 10 clear bit */
#define GPIO_BOP_CR11              BIT(27)                         /*!< pin 11 clear bit */
#define GPIO_BOP_CR12              BIT(28)                         /*!< pin 12 clear bit */
#define GPIO_BOP_CR13              BIT(29)                         /*!< pin 13 clear bit */
#define GPIO_BOP_CR14              BIT(30)                         /*!< pin 14 clear bit */
#define GPIO_BOP_CR15              BIT(31)                         /*!< pin 15 clear bit */

/* GPIO_LOCK */
#define GPIO_LOCK_LK0              BIT(0)                          /*!< pin 0 lock bit */
#define GPIO_LOCK_LK1              BIT(1)                          /*!< pin 1 lock bit */
#define GPIO_LOCK_LK2              BIT(2)                          /*!< pin 2 lock bit */
#define GPIO_LOCK_LK3              BIT(3)                          /*!< pin 3 lock bit */
#define GPIO_LOCK_LK4              BIT(4)                          /*!< pin 4 lock bit */
#define GPIO_LOCK_LK5              BIT(5)                          /*!< pin 5 lock bit */
#define GPIO_LOCK_LK6              BIT(6)                          /*!< pin 6 lock bit */
#define GPIO_LOCK_LK7              BIT(7)                          /*!< pin 7 lock bit */
#define GPIO_LOCK_LK8              BIT(8)                          /*!< pin 8 lock bit */
#define GPIO_LOCK_LK9              BIT(9)                          /*!< pin 9 lock bit */
#define GPIO_LOCK_LK10             BIT(10)                         /*!< pin 10 lock bit */
#define GPIO_LOCK_LK11             BIT(11)                         /*!< pin 11 lock bit */
#define GPIO_LOCK_LK12             BIT(12)                         /*!< pin 12 lock bit */
#define GPIO_LOCK_LK13             BIT(13)                         /*!< pin 13 lock bit */
#define GPIO_LOCK_LK14             BIT(14)                         /*!< pin 14 lock bit */
#define GPIO_LOCK_LK15             BIT(15)                         /*!< pin 15 lock bit */
#define GPIO_LOCK_LKK              BIT(16)                         /*!< pin sequence lock key */

/* GPIO_AFSEL0 */
#define GPIO_AFSEL0_SEL0           BITS(0, 3)                      /*!< pin 0 alternate function selected */
#define GPIO_AFSEL0_SEL1           BITS(4, 7)                      /*!< pin 1 alternate function selected */
#define GPIO_AFSEL0_SEL2           BITS(8, 11)                     /*!< pin 2 alternate function selected */
#define GPIO_AFSEL0_SEL3           BITS(12, 15)                    /*!< pin 3 alternate function selected */
#define GPIO_AFSEL0_SEL4           BITS(16, 19)                    /*!< pin 4 alternate function selected */
#define GPIO_AFSEL0_SEL5           BITS(20, 23)                    /*!< pin 5 alternate function selected */
#define GPIO_AFSEL0_SEL6           BITS(24, 27)                    /*!< pin 6 alternate function selected */
#define GPIO_AFSEL0_SEL7           BITS(28, 31)                    /*!< pin 7 alternate function selected */

/* GPIO_AFSEL1 */
#define GPIO_AFSEL1_SEL8           BITS(0, 3)                      /*!< pin 8 alternate function selected */
#define GPIO_AFSEL1_SEL9           BITS(4, 7)                      /*!< pin 9 alternate function selected */
#define GPIO_AFSEL1_SEL10          BITS(8, 11)                     /*!< pin 10 alternate function selected */
#define GPIO_AFSEL1_SEL11          BITS(12, 15)                    /*!< pin 11 alternate function selected */
#define GPIO_AFSEL1_SEL12          BITS(16, 19)                    /*!< pin 12 alternate function selected */
#define GPIO_AFSEL1_SEL13          BITS(20, 23)                    /*!< pin 13 alternate function selected */
#define GPIO_AFSEL1_SEL14          BITS(24, 27)                    /*!< pin 14 alternate function selected */
#define GPIO_AFSEL1_SEL15          BITS(28, 31)                    /*!< pin 15 alternate function selected */

/* GPIO_BC */
#define GPIO_BC_CR0                BIT(0)                          /*!< pin 0 clear bit */
#define GPIO_BC_CR1                BIT(1)                          /*!< pin 1 clear bit */
#define GPIO_BC_CR2                BIT(2)                          /*!< pin 2 clear bit */
#define GPIO_BC_CR3                BIT(3)                          /*!< pin 3 clear bit */
#define GPIO_BC_CR4                BIT(4)                          /*!< pin 4 clear bit */
#define GPIO_BC_CR5                BIT(5)                          /*!< pin 5 clear bit */
#define GPIO_BC_CR6                BIT(6)                          /*!< pin 6 clear bit */
#define GPIO_BC_CR7                BIT(7)                          /*!< pin 7 clear bit */
#define GPIO_BC_CR8                BIT(8)                          /*!< pin 8 clear bit */
#define GPIO_BC_CR9                BIT(9)                          /*!< pin 9 clear bit */
#define GPIO_BC_CR10               BIT(10)                         /*!< pin 10 clear bit */
#define GPIO_BC_CR11               BIT(11)                         /*!< pin 11 clear bit */
#define GPIO_BC_CR12               BIT(12)                         /*!< pin 12 clear bit */
#define GPIO_BC_CR13               BIT(13)                         /*!< pin 13 clear bit */
#define GPIO_BC_CR14               BIT(14)                         /*!< pin 14 clear bit */
#define GPIO_BC_CR15               BIT(15)                         /*!< pin 15 clear bit */

/* GPIO_TG */
#define GPIO_TG_TG0                BIT(0)                          /*!< pin 0 toggle bit */
#define GPIO_TG_TG1                BIT(1)                          /*!< pin 1 toggle bit */
#define GPIO_TG_TG2                BIT(2)                          /*!< pin 2 toggle bit */
#define GPIO_TG_TG3                BIT(3)                          /*!< pin 3 toggle bit */
#define GPIO_TG_TG4                BIT(4)                          /*!< pin 4 toggle bit */
#define GPIO_TG_TG5                BIT(5)                          /*!< pin 5 toggle bit */
#define GPIO_TG_TG6                BIT(6)                          /*!< pin 6 toggle bit */
#define GPIO_TG_TG7                BIT(7)                          /*!< pin 7 toggle bit */
#define GPIO_TG_TG8                BIT(8)                          /*!< pin 8 toggle bit */
#define GPIO_TG_TG9                BIT(9)                          /*!< pin 9 toggle bit */
#define GPIO_TG_TG10               BIT(10)                         /*!< pin 10 toggle bit */
#define GPIO_TG_TG11               BIT(11)                         /*!< pin 11 toggle bit */
#define GPIO_TG_TG12               BIT(12)                         /*!< pin 12 toggle bit */
#define GPIO_TG_TG13               BIT(13)                         /*!< pin 13 toggle bit */
#define GPIO_TG_TG14               BIT(14)                         /*!< pin 14 toggle bit */
#define GPIO_TG_TG15               BIT(15)                         /*!< pin 15 toggle bit */

/* GPIO_SMCCTL */
#define GPIO_SMCCTL_SMC0           BIT(0)                          /*!< pin 0 safe mode control */
#define GPIO_SMCCTL_SMC1           BIT(1)                          /*!< pin 1 safe mode control */
#define GPIO_SMCCTL_SMC2           BIT(2)                          /*!< pin 2 safe mode control */
#define GPIO_SMCCTL_SMC3           BIT(3)                          /*!< pin 3 safe mode control */
#define GPIO_SMCCTL_SMC4           BIT(4)                          /*!< pin 4 safe mode control */
#define GPIO_SMCCTL_SMC5           BIT(5)                          /*!< pin 5 safe mode control */
#define GPIO_SMCCTL_SMC6           BIT(6)                          /*!< pin 6 safe mode control */
#define GPIO_SMCCTL_SMC7           BIT(7)                          /*!< pin 7 safe mode control */
#define GPIO_SMCCTL_SMC8           BIT(8)                          /*!< pin 8 safe mode control */
#define GPIO_SMCCTL_SMC9           BIT(9)                          /*!< pin 9 safe mode control */
#define GPIO_SMCCTL_SMC10          BIT(10)                         /*!< pin 10 safe mode control */
#define GPIO_SMCCTL_SMC11          BIT(11)                         /*!< pin 11 safe mode control */
#define GPIO_SMCCTL_SMC12          BIT(12)                         /*!< pin 12 safe mode control */
#define GPIO_SMCCTL_SMC13          BIT(13)                         /*!< pin 13 safe mode control */
#define GPIO_SMCCTL_SMC14          BIT(14)                         /*!< pin 14 safe mode control */
#define GPIO_SMCCTL_SMC15          BIT(15)                         /*!< pin 15 safe mode control */

/* GPIO_IFEN */
#define GPIO_IFEN_IFE0             BIT(0)                          /*!< pin 0 input filter enable */
#define GPIO_IFEN_IFE1             BIT(1)                          /*!< pin 1 input filter enable */
#define GPIO_IFEN_IFE2             BIT(2)                          /*!< pin 2 input filter enable */
#define GPIO_IFEN_IFE3             BIT(3)                          /*!< pin 3 input filter enable */
#define GPIO_IFEN_IFE4             BIT(4)                          /*!< pin 4 input filter enable */
#define GPIO_IFEN_IFE5             BIT(5)                          /*!< pin 5 input filter enable */
#define GPIO_IFEN_IFE6             BIT(6)                          /*!< pin 6 input filter enable */
#define GPIO_IFEN_IFE7             BIT(7)                          /*!< pin 7 input filter enable */
#define GPIO_IFEN_IFE8             BIT(8)                          /*!< pin 8 input filter enable */
#define GPIO_IFEN_IFE9             BIT(9)                          /*!< pin 9 input filter enable */
#define GPIO_IFEN_IFE10            BIT(10)                         /*!< pin 10 input filter enable */
#define GPIO_IFEN_IFE11            BIT(11)                         /*!< pin 11 input filter enable */
#define GPIO_IFEN_IFE12            BIT(12)                         /*!< pin 12 input filter enable */
#define GPIO_IFEN_IFE13            BIT(13)                         /*!< pin 13 input filter enable */
#define GPIO_IFEN_IFE14            BIT(14)                         /*!< pin 14 input filter enable */
#define GPIO_IFEN_IFE15            BIT(15)                         /*!< pin 15 input filter enable */

/* GPIO_PREN */
#define GPIO_PREN_PKE0             BIT(0)                          /*!< pin 0 pad retain enable */
#define GPIO_PREN_PKE1             BIT(1)                          /*!< pin 1 pad retain enable */
#define GPIO_PREN_PKE2             BIT(2)                          /*!< pin 2 pad retain enable */
#define GPIO_PREN_PKE3             BIT(3)                          /*!< pin 3 pad retain enable */
#define GPIO_PREN_PKE4             BIT(4)                          /*!< pin 4 pad retain enable */
#define GPIO_PREN_PKE5             BIT(5)                          /*!< pin 5 pad retain enable */
#define GPIO_PREN_PKE6             BIT(6)                          /*!< pin 6 pad retain enable */
#define GPIO_PREN_PKE7             BIT(7)                          /*!< pin 7 pad retain enable */
#define GPIO_PREN_PKE8             BIT(8)                          /*!< pin 8 pad retain enable */
#define GPIO_PREN_PKE9             BIT(9)                          /*!< pin 9 pad retain enable */
#define GPIO_PREN_PKE10            BIT(10)                         /*!< pin 10 pad retain enable */
#define GPIO_PREN_PKE11            BIT(11)                         /*!< pin 11 pad retain enable */
#define GPIO_PREN_PKE12            BIT(12)                         /*!< pin 12 pad retain enable */
#define GPIO_PREN_PKE13            BIT(13)                         /*!< pin 13 pad retain enable */
#define GPIO_PREN_PKE14            BIT(14)                         /*!< pin 14 pad retain enable */
#define GPIO_PREN_PKE15            BIT(15)                         /*!< pin 15 pad retain enable */

/* GPIO_SREN */
#define GPIO_SREN_SRE0             BIT(0)                          /*!< pin 0 slew rate enable */
#define GPIO_SREN_SRE1             BIT(1)                          /*!< pin 1 slew rate enable */
#define GPIO_SREN_SRE2             BIT(2)                          /*!< pin 2 slew rate enable */
#define GPIO_SREN_SRE3             BIT(3)                          /*!< pin 3 slew rate enable */
#define GPIO_SREN_SRE4             BIT(4)                          /*!< pin 4 slew rate enable */
#define GPIO_SREN_SRE5             BIT(5)                          /*!< pin 5 slew rate enable */
#define GPIO_SREN_SRE6             BIT(6)                          /*!< pin 6 slew rate enable */
#define GPIO_SREN_SRE7             BIT(7)                          /*!< pin 7 slew rate enable */
#define GPIO_SREN_SRE8             BIT(8)                          /*!< pin 8 slew rate enable */
#define GPIO_SREN_SRE9             BIT(9)                          /*!< pin 9 slew rate enable */
#define GPIO_SREN_SRE10            BIT(10)                         /*!< pin 10 slew rate enable */
#define GPIO_SREN_SRE11            BIT(11)                         /*!< pin 11 slew rate enable */
#define GPIO_SREN_SRE12            BIT(12)                         /*!< pin 12 slew rate enable */
#define GPIO_SREN_SRE13            BIT(13)                         /*!< pin 13 slew rate enable */
#define GPIO_SREN_SRE14            BIT(14)                         /*!< pin 14 slew rate enable */
#define GPIO_SREN_SRE15            BIT(15)                         /*!< pin 15 slew rate enable */

/* GPIO_IFCTL */
#define GPIO_IFCTL_IQSP            BITS(28, 31)                    /*!< externale interrupt qualification sampling period for GPIO0 to GPIO15 */
#define GPIO_IFCTL_EIFE0           BIT(0)                          /*!< pin 0 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE1           BIT(1)                          /*!< pin 1 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE2           BIT(2)                          /*!< pin 2 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE3           BIT(3)                          /*!< pin 3 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE4           BIT(4)                          /*!< pin 4 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE5           BIT(5)                          /*!< pin 5 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE6           BIT(6)                          /*!< pin 6 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE7           BIT(7)                          /*!< pin 7 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE8           BIT(8)                          /*!< pin 8 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE9           BIT(9)                          /*!< pin 9 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE10          BIT(10)                         /*!< pin 10 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE11          BIT(11)                         /*!< pin 11 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE12          BIT(12)                         /*!< pin 12 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE13          BIT(13)                         /*!< pin 13 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE14          BIT(14)                         /*!< pin 14 enables digital glitch filter on the interrupt pad input */
#define GPIO_IFCTL_EIFE15          BIT(15)                         /*!< pin 15 enables digital glitch filter on the interrupt pad input */


/* GPIO_IFSCTL0 */
#define GPIO_IFSCTL0_IFSC0         BITS(0, 3)                      /*!< pin 0 maximum interrupt filter counter setting */
#define GPIO_IFSCTL0_IFSC1         BITS(4, 7)                      /*!< pin 1 maximum interrupt filter counter setting */
#define GPIO_IFSCTL0_IFSC2         BITS(8, 11)                     /*!< pin 2 maximum interrupt filter counter setting */
#define GPIO_IFSCTL0_IFSC3         BITS(12, 15)                    /*!< pin 3 maximum interrupt filter counter setting */
#define GPIO_IFSCTL0_IFSC4         BITS(16, 19)                    /*!< pin 4 maximum interrupt filter counter setting */
#define GPIO_IFSCTL0_IFSC5         BITS(20, 23)                    /*!< pin 5 maximum interrupt filter counter setting */
#define GPIO_IFSCTL0_IFSC6         BITS(24, 27)                    /*!< pin 6 maximum interrupt filter counter setting */
#define GPIO_IFSCTL0_IFSC7         BITS(28, 31)                    /*!< pin 7 maximum interrupt filter counter setting */

/* GPIO_IFSCTL1 */
#define GPIO_IFSCTL1_IFSC8         BITS(0, 3)                      /*!< pin 8 maximum interrupt filter counter setting */
#define GPIO_IFSCTL1_IFSC9         BITS(4, 7)                      /*!< pin 9 maximum interrupt filter counter setting */
#define GPIO_IFSCTL1_IFSC10        BITS(8, 11)                     /*!< pin 10 maximum interrupt filter counter setting */
#define GPIO_IFSCTL1_IFSC11        BITS(12, 15)                    /*!< pin 11 maximum interrupt filter counter setting */
#define GPIO_IFSCTL1_IFSC12        BITS(16, 19)                    /*!< pin 12 maximum interrupt filter counter setting */
#define GPIO_IFSCTL1_IFSC13        BITS(20, 23)                    /*!< pin 13 maximum interrupt filter counter setting */
#define GPIO_IFSCTL1_IFSC14        BITS(24, 27)                    /*!< pin 14 maximum interrupt filter counter setting */
#define GPIO_IFSCTL1_IFSC15        BITS(28, 31)                    /*!< pin 15 maximum interrupt filter counter setting */

/* GPIO_TMRALRMSTAT */
#define GPIO_TMRASTAT_PXFFIO0MSK   BIT(0)                          /*!< FFP0 port mode configuration TMR alarm mask */
#define GPIO_TMRASTAT_PXFFIO0      BIT(1)                          /*!< FFIO0 port mode configuration TMR error alarm */
#define GPIO_TMRASTAT_PXFFIO1MSK   BIT(2)                          /*!< FFIO1 port mode configuration TMR alarm error mask */
#define GPIO_TMRASTAT_PXFFIO1      BIT(3)                          /*!< FFIO1 port mode configuration TMR error alarm */
#define GPIO_TMRASTAT_PXGFIOMSK    BIT(4)                          /*!< GFIO port mode configuration TMR alarm error mask */
#define GPIO_TMRASTAT_PXGFIO       BIT(5)                          /*!< GFIO port mode configuration TMR error alarm */
#define GPIO_TMRASTAT_PXRESETMSK   BIT(6)                          /*!< RESET port mode configuration TMR error alarm mask */
#define GPIO_TMRASTAT_PXRESET      BIT(7)                          /*!< RESET port mode configuration TMR error alarm */

/* constants definitions */
typedef FlagStatus bit_status;

/* output mode definitions */
#define CTL_CLTR(regval)           (BITS(0,1) & ((uint32_t)(regval) << 0))
#define GPIO_MODE_INPUT            CTL_CLTR(0)                     /*!< input mode */
#define GPIO_MODE_OUTPUT           CTL_CLTR(1)                     /*!< output mode */
#define GPIO_MODE_AF               CTL_CLTR(2)                     /*!< alternate function mode */
#define GPIO_MODE_ANALOG           CTL_CLTR(3)                     /*!< analog mode */

/* pull-up/pull-down value definitions */
#define PUD_PUPD(regval)           (BITS(0, 1) & ((uint32_t)(regval) << 0))
#define GPIO_PUPD_NONE             PUD_PUPD(0)                     /*!< floating mode, no pull-up and pull-down resistors */
#define GPIO_PUPD_PULLUP           PUD_PUPD(1)                     /*!< with pull-up resistor */
#define GPIO_PUPD_PULLDOWN         PUD_PUPD(2)                     /*!< with pull-down resistor */

/* GPIO pin definitions */
#define GPIO_PIN_0                 BIT(0)                          /*!< GPIO pin 0 */
#define GPIO_PIN_1                 BIT(1)                          /*!< GPIO pin 1 */
#define GPIO_PIN_2                 BIT(2)                          /*!< GPIO pin 2 */
#define GPIO_PIN_3                 BIT(3)                          /*!< GPIO pin 3 */
#define GPIO_PIN_4                 BIT(4)                          /*!< GPIO pin 4 */
#define GPIO_PIN_5                 BIT(5)                          /*!< GPIO pin 5 */
#define GPIO_PIN_6                 BIT(6)                          /*!< GPIO pin 6 */
#define GPIO_PIN_7                 BIT(7)                          /*!< GPIO pin 7 */
#define GPIO_PIN_8                 BIT(8)                          /*!< GPIO pin 8 */
#define GPIO_PIN_9                 BIT(9)                          /*!< GPIO pin 9 */
#define GPIO_PIN_10                BIT(10)                         /*!< GPIO pin 10 */
#define GPIO_PIN_11                BIT(11)                         /*!< GPIO pin 11 */
#define GPIO_PIN_12                BIT(12)                         /*!< GPIO pin 12 */
#define GPIO_PIN_13                BIT(13)                         /*!< GPIO pin 13 */
#define GPIO_PIN_14                BIT(14)                         /*!< GPIO pin 14 */
#define GPIO_PIN_15                BIT(15)                         /*!< GPIO pin 15 */
#define GPIO_PIN_ALL               BITS(0, 15)                     /*!< GPIO pin all */

/* GPIO mode configuration values */
#define GPIO_MODE_SET(n, mode)     ((uint32_t)((uint32_t)(mode) << (2U * (n))))
#define GPIO_MODE_MASK(n)          ((uint32_t)((uint32_t)0x3U << (2U * (n))))

/* GPIO pull-up/pull-down values */
#define GPIO_PUPD_SET(n, pupd)     ((uint32_t)((uint32_t)(pupd) << (2U * (n))))
#define GPIO_PUPD_MASK(n)          ((uint32_t)((uint32_t)(0x3U) << (2U * (n))))

/* GPIO output speed values */
#define GPIO_OSPEED_SET(n, speed)  ((uint32_t)((uint32_t)(speed) << (2U * (n))))
#define GPIO_OSPEED_MASK(n)        ((uint32_t)((uint32_t)(0x3U) << (2U * (n))))

/* GPIO output type definitions*/
#define GPIO_OTYPE_PP              ((uint8_t)(0x00U))              /*!< push pull mode */
#define GPIO_OTYPE_OD              ((uint8_t)(0x01U))              /*!< open drain mode */

/* GPIO output max speed value definitions*/
#define OSPD_OSPD0(regval)         (BITS(0, 1) & ((uint32_t)(regval) << 0))
#define GPIO_OSPEED_LEVEL_0        OSPD_OSPD0(0)                   /*!< output speed level 0 */
#define GPIO_OSPEED_LEVEL_1        OSPD_OSPD0(1)                   /*!< output speed level 1 */
#define GPIO_OSPEED_LEVEL_2        OSPD_OSPD0(2)                   /*!< output speed level 2 */

/* GPIO alternate function values */
#define GPIO_AFR_SET(n, af)        ((uint32_t)((uint32_t)(af) << (4U * (n))))
#define GPIO_AFR_MASK(n)           ((uint32_t)((uint32_t)(0xFU) << (4U * (n))))

/* GPIO alternate function value difinitions*/
#define AF(regval)                 (BITS(0, 3) & ((uint32_t)(regval) << 0)) 
#define GPIO_AF_0                  AF(0)                           /*!< alternate function 0 selected */
#define GPIO_AF_1                  AF(1)                           /*!< alternate function 1 selected */
#define GPIO_AF_2                  AF(2)                           /*!< alternate function 2 selected */
#define GPIO_AF_3                  AF(3)                           /*!< alternate function 3 selected */
#define GPIO_AF_4                  AF(4)                           /*!< alternate function 4 selected */
#define GPIO_AF_5                  AF(5)                           /*!< alternate function 5 selected */
#define GPIO_AF_6                  AF(6)                           /*!< alternate function 6 selected */
#define GPIO_AF_7                  AF(7)                           /*!< alternate function 7 selected */
#define GPIO_AF_8                  AF(8)                           /*!< alternate function 8 selected */
#define GPIO_AF_9                  AF(9)                           /*!< alternate function 9 selected */
#define GPIO_AF_10                 AF(10)                           /*!< alternate function 10 selected */
#define GPIO_AF_11                 AF(11)                           /*!< alternate function 11 selected */
#define GPIO_AF_12                 AF(12)                           /*!< alternate function 12 selected */
#define GPIO_AF_13                 AF(13)                           /*!< alternate function 13 selected */
#define GPIO_AF_14                 AF(14)                           /*!< alternate function 14 selected */
#define GPIO_AF_15                 AF(15)                           /*!< alternate function 15 selected */

/* GPIO external interrupt sample counter value */
#define GPIO_IFSCTL_SPLCNT_SET(n, splcnt)  ((uint32_t)((uint32_t)(splcnt) << (4U * (n))))
#define GPIO_IFSCTL_SPLCNT_MASK(n)         ((uint32_t)((uint32_t)(0xFU) << (4U * (n))))

/* GPIO TMR alarm value definitions*/
#define GPIO_TMRASTAT_ERROR_ALL      (GPIO_TMRASTAT_PXFFIO0 | GPIO_TMRASTAT_PXFFIO1 | GPIO_TMRASTAT_PXGFIO | GPIO_TMRASTAT_PXRESET)
#define GPIO_TMRASTAT_MASK_ALL       (GPIO_TMRASTAT_PXFFIO0MSK | GPIO_TMRASTAT_PXFFIO1MSK | GPIO_TMRASTAT_PXGFIOMSK | GPIO_TMRASTAT_PXRESETMSK)

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check peripherals */
#define NOT_GPIO_PERIPH(periph)                 (((periph) != GPIOA) && \
                                                 ((periph) != GPIOB) && \
                                                 ((periph) != GPIOC) && \
                                                 ((periph) != GPIOD) && \
                                                 ((periph) != GPIOE) && \
                                                 ((periph) != GPIOF) && \
                                                 ((periph) != GPIOG) && \
                                                 ((periph) != GPIOH) && \
                                                 ((periph) != GPIOI) && \
                                                 ((periph) != GPIOJ) && \
                                                 ((periph) != GPIOK) && \
                                                 ((periph) != GPIOL) && \
                                                 ((periph) != GPIOM) && \
                                                 ((periph) != GPION))

/* check GPIO pin modes */
#define NOT_GPIO_MODE(mode)                     (((mode) != GPIO_MODE_INPUT)  && \
                                                 ((mode) != GPIO_MODE_OUTPUT) && \
                                                 ((mode) != GPIO_MODE_AF) && \
                                                 ((mode) != GPIO_MODE_ANALOG))

/* check GPIO pin pull modes */
#define NOT_GPIO_PULL_MODE(pull_up_down)        (((pull_up_down) != GPIO_PUPD_NONE)   && \
                                                 ((pull_up_down) != GPIO_PUPD_PULLUP) && \
                                                 ((pull_up_down) != GPIO_PUPD_PULLDOWN))

/* check GPIO pin */
#define NOT_GPIO_PIN(pin)                       (((pin) == 0x00000000U) || ((pin) > 0x0000FFFFU))

/* check GPIO pin output mode */
#define NOT_GPIO_OTYPE(otype)                   (((otype) != GPIO_OTYPE_PP) && \
                                                 ((otype) != GPIO_OTYPE_OD))

/* check GPIO pin speed */
#define NOT_GPIO_SPEED(speed)                   (((speed) != GPIO_OSPEED_LEVEL_0) && \
                                                 ((speed) != GPIO_OSPEED_LEVEL_1) && \
                                                 ((speed) != GPIO_OSPEED_LEVEL_2))

/* check reset and set value */
#define NOT_RESET_SET(value)                    (((value) != RESET)  && \
                                                 ((value) != SET))

/* check GPIO pin AF */
#define NOT_GPIO_AF(alt_func_num)               (((alt_func_num) != GPIO_AF_0) && \
                                                 ((alt_func_num) != GPIO_AF_1) && \
                                                 ((alt_func_num) != GPIO_AF_2) && \
                                                 ((alt_func_num) != GPIO_AF_3) && \
                                                 ((alt_func_num) != GPIO_AF_4) && \
                                                 ((alt_func_num) != GPIO_AF_5) && \
                                                 ((alt_func_num) != GPIO_AF_6) && \
                                                 ((alt_func_num) != GPIO_AF_7) && \
                                                 ((alt_func_num) != GPIO_AF_8) && \
                                                 ((alt_func_num) != GPIO_AF_9) && \
                                                 ((alt_func_num) != GPIO_AF_10) && \
                                                 ((alt_func_num) != GPIO_AF_11) && \
                                                 ((alt_func_num) != GPIO_AF_12) && \
                                                 ((alt_func_num) != GPIO_AF_13) && \
                                                 ((alt_func_num) != GPIO_AF_14) && \
                                                 ((alt_func_num) != GPIO_AF_15))

/* check external interrupt sampling period */
#define NOT_SAMPLING_PERIOD(iqsp)                (0x0FU < (iqsp))

/* check maximum interrupt filter counter */
#define NOT_FLITER_COUNTER(counter)              (0x0FU < (counter))

/* check TMR alarm status */
#define NOT_TMRALARM_STATUS(alarm)               (((alarm) != GPIO_TMRASTAT_PXFFIO0) && \
                                                  ((alarm) != GPIO_TMRASTAT_PXFFIO1) && \
                                                  ((alarm) != GPIO_TMRASTAT_PXGFIO) && \
                                                  ((alarm) != GPIO_TMRASTAT_PXRESET))

/* check TMR alarm mask status */
#define NOT_TMRALARM_MASK(alarm_msk)             (((alarm_msk) != GPIO_TMRASTAT_PXFFIO0MSK) && \
                                                  ((alarm_msk) != GPIO_TMRASTAT_PXFFIO1MSK) && \
                                                  ((alarm_msk) != GPIO_TMRASTAT_PXGFIOMSK) && \
                                                  ((alarm_msk) != GPIO_TMRASTAT_PXRESETMSK))

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */

/* reset GPIO port */
void gpio_deinit(uint32_t gpio_periph);
/* set GPIO mode */
void gpio_mode_set(uint32_t gpio_periph, uint32_t mode, uint32_t pull_up_down, uint32_t pin);
/* set GPIO output type and speed */
void gpio_output_options_set(uint32_t gpio_periph, uint8_t otype, uint32_t speed, uint32_t pin);

/* set GPIO pin bit */
void gpio_bit_set(uint32_t gpio_periph, uint32_t pin);
/* reset GPIO pin bit */
void gpio_bit_reset(uint32_t gpio_periph, uint32_t pin);
/* write data to the specified GPIO pin */
void gpio_bit_write(uint32_t gpio_periph, uint32_t pin, bit_status bit_value);
/* write data to the specified GPIO port */
void gpio_port_write(uint32_t gpio_periph, uint16_t data);
/* get GPIO pin input status */
FlagStatus gpio_input_bit_get(uint32_t gpio_periph, uint32_t pin);
/* get GPIO port input status */
uint16_t gpio_input_port_get(uint32_t gpio_periph);
/* get GPIO pin output status */
FlagStatus gpio_output_bit_get(uint32_t gpio_periph, uint32_t pin);
/* get GPIO port output status */
uint16_t gpio_output_port_get(uint32_t gpio_periph);
/* set GPIO alternate function */
void gpio_af_set(uint32_t gpio_periph, uint32_t alt_func_num, uint32_t pin);
/* lock GPIO pin bit */
void gpio_pin_lock(uint32_t gpio_periph, uint32_t pin);
/* toggle GPIO pin status */
void gpio_bit_toggle(uint32_t gpio_periph, uint32_t pin);
/* toggle GPIO port status */
void gpio_port_toggle(uint32_t gpio_periph);

/* enable GPIO port safe mode */
void gpio_safe_mode_enable(uint32_t gpio_periph, uint32_t pin);
/* disable GPIO port safe mode */
void gpio_safe_mode_disable(uint32_t gpio_periph, uint32_t pin);
/* enable GPIO port filtering */
void gpio_port_filter_enable(uint32_t gpio_periph, uint32_t pin);
/* disable GPIO port filtering */
void gpio_port_filter_disable(uint32_t gpio_periph, uint32_t pin);
/* enable GPIO port retain */
void gpio_port_retain_enable(uint32_t gpio_periph, uint32_t pin);
/* disable GPIO port retain */
void gpio_port_retain_disable(uint32_t gpio_periph, uint32_t pin);
/* enable GPIO slew rate */
void gpio_slew_enable(uint32_t gpio_periph, uint32_t pin);
/* disable GPIO slew rate */
void gpio_slew_disable(uint32_t gpio_periph, uint32_t pin);
/* enable GPIO interrupt filtering control */
void gpio_int_filt_enable(uint32_t gpio_periph, uint32_t pin);
/* disable GPIO interrupt filtering control */
void gpio_int_filt_disable(uint32_t gpio_periph, uint32_t pin);
/* set GPIO interrupt filtering sampling period*/
void gpio_int_filt_sampling_period_set(uint32_t gpio_periph, uint8_t sampling_period);
/* set GPIO interrupt filtering sampling counter*/
void gpio_int_filt_sample_counter_set(uint32_t gpio_periph, uint32_t pin, uint8_t counter);

/* get GPIO port TMR alarm status*/
FlagStatus gpio_tmr_alarm_status_get(uint32_t gpio_periph, uint32_t tmr_alarm);
/* clear GPIO port TMR alarm status */
void gpio_tmr_alarm_status_clear(uint32_t gpio_periph, uint32_t tmr_alarm);
/* get GPIO port TMR alarm mask status */
FlagStatus gpio_tmr_alarm_mask_status_get(uint32_t gpio_periph, uint32_t tmr_alarm);
/* enable mask GPIO port TMR alarm */
void gpio_tmr_alarm_mask_enable(uint32_t gpio_periph, uint32_t tmr_alarm);
/* clear mask GPIO port TMR alarm status */
void gpio_tmr_alarm_mask_disable(uint32_t gpio_periph, uint32_t tmr_alarm);

#endif /* GD32A7XX_GPIO_H */
