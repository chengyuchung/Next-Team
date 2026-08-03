/*!
    \file    gd32a7xx_exti.h
    \brief   definitions for the EXTI

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

#ifndef GD32A7XX_EXTI_H
#define GD32A7XX_EXTI_H

#include "gd32a7xx.h"

/* EXTI definitions */
#define EXTI                         EXTI_BASE

/* registers definitions */
#define EXTI_INTEN0                   REG32(EXTI + 0x00000000U)      /*!< interrupt enable register 0 */
#define EXTI_EVEN0                    REG32(EXTI + 0x00000004U)      /*!< event enable register 0 */
#define EXTI_RTEN0                    REG32(EXTI + 0x00000008U)      /*!< rising edge trigger enable register 0 */
#define EXTI_FTEN0                    REG32(EXTI + 0x0000000CU)      /*!< falling trigger enable register 0 */
#define EXTI_SWIEV0                   REG32(EXTI + 0x00000010U)      /*!< software interrupt event register 0 */
#define EXTI_PD0                      REG32(EXTI + 0x00000014U)      /*!< pending register 0 */
#define EXTI_INTEN1                   REG32(EXTI + 0x00000018U)      /*!< interrupt enable register 1 */
#define EXTI_EVEN1                    REG32(EXTI + 0x0000001CU)      /*!< event enable register 1 */
#define EXTI_RTEN1                    REG32(EXTI + 0x00000020U)      /*!< rising edge trigger enable register 1 */
#define EXTI_FTEN1                    REG32(EXTI + 0x00000024U)      /*!< falling trigger enable register 1 */
#define EXTI_SWIEV1                   REG32(EXTI + 0x00000028U)      /*!< software interrupt event register 1 */
#define EXTI_PD1                      REG32(EXTI + 0x0000002CU)      /*!< pending register 1 */
#define EXTI_INTEN2                   REG32(EXTI + 0x00000030U)      /*!< interrupt enable register 2 */
#define EXTI_EVEN2                    REG32(EXTI + 0x00000034U)      /*!< event enable register 2 */
#define EXTI_RTEN2                    REG32(EXTI + 0x00000038U)      /*!< rising edge trigger enable register 2 */
#define EXTI_FTEN2                    REG32(EXTI + 0x0000003CU)      /*!< falling trigger enable register 2 */
#define EXTI_SWIEV2                   REG32(EXTI + 0x00000040U)      /*!< software interrupt event register 2 */
#define EXTI_PD2                      REG32(EXTI + 0x00000044U)      /*!< pending register 2 */
#define EXTI_INTEN3                   REG32(EXTI + 0x00000048U)      /*!< interrupt enable register 3 */
#define EXTI_EVEN3                    REG32(EXTI + 0x0000004CU)      /*!< event enable register 3 */
#define EXTI_RTEN3                    REG32(EXTI + 0x00000050U)      /*!< rising edge trigger enable register 3 */
#define EXTI_FTEN3                    REG32(EXTI + 0x00000054U)      /*!< falling trigger enable register 3 */
#define EXTI_SWIEV3                   REG32(EXTI + 0x00000058U)      /*!< software interrupt event register 3 */
#define EXTI_PD3                      REG32(EXTI + 0x0000005CU)      /*!< pending register 3 */

/* bits definitions */
/* EXTI_INTEN0 */
#define EXTI_INTEN0_INTEN0            BIT(0)                   /*!< interrupt from line 0 */
#define EXTI_INTEN0_INTEN1            BIT(1)                   /*!< interrupt from line 1 */
#define EXTI_INTEN0_INTEN2            BIT(2)                   /*!< interrupt from line 2 */
#define EXTI_INTEN0_INTEN3            BIT(3)                   /*!< interrupt from line 3 */
#define EXTI_INTEN0_INTEN4            BIT(4)                   /*!< interrupt from line 4 */
#define EXTI_INTEN0_INTEN5            BIT(5)                   /*!< interrupt from line 5 */
#define EXTI_INTEN0_INTEN6            BIT(6)                   /*!< interrupt from line 6 */
#define EXTI_INTEN0_INTEN7            BIT(7)                   /*!< interrupt from line 7 */
#define EXTI_INTEN0_INTEN8            BIT(8)                   /*!< interrupt from line 8 */
#define EXTI_INTEN0_INTEN9            BIT(9)                   /*!< interrupt from line 9 */
#define EXTI_INTEN0_INTEN10           BIT(10)                  /*!< interrupt from line 10 */
#define EXTI_INTEN0_INTEN11           BIT(11)                  /*!< interrupt from line 11 */
#define EXTI_INTEN0_INTEN12           BIT(12)                  /*!< interrupt from line 12 */
#define EXTI_INTEN0_INTEN13           BIT(13)                  /*!< interrupt from line 13 */
#define EXTI_INTEN0_INTEN14           BIT(14)                  /*!< interrupt from line 14 */
#define EXTI_INTEN0_INTEN15           BIT(15)                  /*!< interrupt from line 15 */
#define EXTI_INTEN0_INTEN16           BIT(16)                  /*!< interrupt from line 16 */
#define EXTI_INTEN0_INTEN17           BIT(17)                  /*!< interrupt from line 17 */
#define EXTI_INTEN0_INTEN18           BIT(18)                  /*!< interrupt from line 18 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_INTEN0_INTEN19           BIT(19)                  /*!< interrupt from line 19 */
#define EXTI_INTEN0_INTEN20           BIT(20)                  /*!< interrupt from line 20 */
#define EXTI_INTEN0_INTEN21           BIT(21)                  /*!< interrupt from line 21 */
#define EXTI_INTEN0_INTEN22           BIT(22)                  /*!< interrupt from line 22 */
#define EXTI_INTEN0_INTEN23           BIT(23)                  /*!< interrupt from line 23 */
#define EXTI_INTEN0_INTEN24           BIT(24)                  /*!< interrupt from line 24 */
#define EXTI_INTEN0_INTEN25           BIT(25)                  /*!< interrupt from line 25 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_INTEN0_INTEN26           BIT(26)                  /*!< interrupt from line 26 */
#define EXTI_INTEN0_INTEN27           BIT(27)                  /*!< interrupt from line 27 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_INTEN0_INTEN28           BIT(28)                  /*!< interrupt from line 28 */
#define EXTI_INTEN0_INTEN29           BIT(29)                  /*!< interrupt from line 29 */
#define EXTI_INTEN0_INTEN30           BIT(30)                  /*!< interrupt from line 30 */
#define EXTI_INTEN0_INTEN31           BIT(31)                  /*!< interrupt from line 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* EXTI_EVEN0 */
#define EXTI_EVEN0_EVEN0              BIT(0)                   /*!< event from line 0 */
#define EXTI_EVEN0_EVEN1              BIT(1)                   /*!< event from line 1 */
#define EXTI_EVEN0_EVEN2              BIT(2)                   /*!< event from line 2 */
#define EXTI_EVEN0_EVEN3              BIT(3)                   /*!< event from line 3 */
#define EXTI_EVEN0_EVEN4              BIT(4)                   /*!< event from line 4 */
#define EXTI_EVEN0_EVEN5              BIT(5)                   /*!< event from line 5 */
#define EXTI_EVEN0_EVEN6              BIT(6)                   /*!< event from line 6 */
#define EXTI_EVEN0_EVEN7              BIT(7)                   /*!< event from line 7 */
#define EXTI_EVEN0_EVEN8              BIT(8)                   /*!< event from line 8 */
#define EXTI_EVEN0_EVEN9              BIT(9)                   /*!< event from line 9 */
#define EXTI_EVEN0_EVEN10             BIT(10)                  /*!< event from line 10 */
#define EXTI_EVEN0_EVEN11             BIT(11)                  /*!< event from line 11 */
#define EXTI_EVEN0_EVEN12             BIT(12)                  /*!< event from line 12 */
#define EXTI_EVEN0_EVEN13             BIT(13)                  /*!< event from line 13 */
#define EXTI_EVEN0_EVEN14             BIT(14)                  /*!< event from line 14 */
#define EXTI_EVEN0_EVEN15             BIT(15)                  /*!< event from line 15 */
#define EXTI_EVEN0_EVEN16             BIT(16)                  /*!< event from line 16 */
#define EXTI_EVEN0_EVEN17             BIT(17)                  /*!< event from line 17 */
#define EXTI_EVEN0_EVEN18             BIT(18)                  /*!< event from line 18 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_EVEN0_EVEN19             BIT(19)                  /*!< event from line 19 */
#define EXTI_EVEN0_EVEN20             BIT(20)                  /*!< event from line 20 */
#define EXTI_EVEN0_EVEN21             BIT(21)                  /*!< event from line 21 */
#define EXTI_EVEN0_EVEN22             BIT(22)                  /*!< event from line 22 */
#define EXTI_EVEN0_EVEN23             BIT(23)                  /*!< event from line 23 */
#define EXTI_EVEN0_EVEN24             BIT(24)                  /*!< event from line 24 */
#define EXTI_EVEN0_EVEN25             BIT(25)                  /*!< event from line 25 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_EVEN0_EVEN26             BIT(26)                  /*!< event from line 26 */
#define EXTI_EVEN0_EVEN27             BIT(27)                  /*!< event from line 27 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_EVEN0_EVEN28             BIT(28)                  /*!< event from line 28 */
#define EXTI_EVEN0_EVEN29             BIT(29)                  /*!< event from line 29 */
#define EXTI_EVEN0_EVEN30             BIT(30)                  /*!< event from line 30 */
#define EXTI_EVEN0_EVEN31             BIT(31)                  /*!< event from line 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* EXTI_RTEN0 */
#define EXTI_RTEN0_RTEN0              BIT(0)                   /*!< rising edge from line 0 */
#define EXTI_RTEN0_RTEN1              BIT(1)                   /*!< rising edge from line 1 */
#define EXTI_RTEN0_RTEN2              BIT(2)                   /*!< rising edge from line 2 */
#define EXTI_RTEN0_RTEN3              BIT(3)                   /*!< rising edge from line 3 */
#define EXTI_RTEN0_RTEN4              BIT(4)                   /*!< rising edge from line 4 */
#define EXTI_RTEN0_RTEN5              BIT(5)                   /*!< rising edge from line 5 */
#define EXTI_RTEN0_RTEN6              BIT(6)                   /*!< rising edge from line 6 */
#define EXTI_RTEN0_RTEN7              BIT(7)                   /*!< rising edge from line 7 */
#define EXTI_RTEN0_RTEN8              BIT(8)                   /*!< rising edge from line 8 */
#define EXTI_RTEN0_RTEN9              BIT(9)                   /*!< rising edge from line 9 */
#define EXTI_RTEN0_RTEN10             BIT(10)                  /*!< rising edge from line 10 */
#define EXTI_RTEN0_RTEN11             BIT(11)                  /*!< rising edge from line 11 */
#define EXTI_RTEN0_RTEN12             BIT(12)                  /*!< rising edge from line 12 */
#define EXTI_RTEN0_RTEN13             BIT(13)                  /*!< rising edge from line 13 */
#define EXTI_RTEN0_RTEN14             BIT(14)                  /*!< rising edge from line 14 */
#define EXTI_RTEN0_RTEN15             BIT(15)                  /*!< rising edge from line 15 */
#define EXTI_RTEN0_RTEN16             BIT(16)                  /*!< rising edge from line 16 */
#define EXTI_RTEN0_RTEN17             BIT(17)                  /*!< rising edge from line 17 */
#define EXTI_RTEN0_RTEN18             BIT(18)                  /*!< rising edge from line 18 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_RTEN0_RTEN19             BIT(19)                  /*!< rising edge from line 19 */
#define EXTI_RTEN0_RTEN20             BIT(20)                  /*!< rising edge from line 20 */
#define EXTI_RTEN0_RTEN21             BIT(21)                  /*!< rising edge from line 21 */
#define EXTI_RTEN0_RTEN22             BIT(22)                  /*!< rising edge from line 22 */
#define EXTI_RTEN0_RTEN23             BIT(23)                  /*!< rising edge from line 23 */
#define EXTI_RTEN0_RTEN24             BIT(24)                  /*!< rising edge from line 24 */
#define EXTI_RTEN0_RTEN25             BIT(25)                  /*!< rising edge from line 25 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_RTEN0_RTEN26             BIT(26)                  /*!< rising edge from line 26 */
#define EXTI_RTEN0_RTEN27             BIT(27)                  /*!< rising edge from line 27 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_RTEN0_RTEN28             BIT(28)                  /*!< rising edge from line 28 */
#define EXTI_RTEN0_RTEN29             BIT(29)                  /*!< rising edge from line 29 */
#define EXTI_RTEN0_RTEN30             BIT(30)                  /*!< rising edge from line 30 */
#define EXTI_RTEN0_RTEN31             BIT(31)                  /*!< rising edge from line 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* EXTI_FTEN0 */
#define EXTI_FTEN0_FTEN0              BIT(0)                   /*!< falling edge from line 0 */
#define EXTI_FTEN0_FTEN1              BIT(1)                   /*!< falling edge from line 1 */
#define EXTI_FTEN0_FTEN2              BIT(2)                   /*!< falling edge from line 2 */
#define EXTI_FTEN0_FTEN3              BIT(3)                   /*!< falling edge from line 3 */
#define EXTI_FTEN0_FTEN4              BIT(4)                   /*!< falling edge from line 4 */
#define EXTI_FTEN0_FTEN5              BIT(5)                   /*!< falling edge from line 5 */
#define EXTI_FTEN0_FTEN6              BIT(6)                   /*!< falling edge from line 6 */
#define EXTI_FTEN0_FTEN7              BIT(7)                   /*!< falling edge from line 7 */
#define EXTI_FTEN0_FTEN8              BIT(8)                   /*!< falling edge from line 8 */
#define EXTI_FTEN0_FTEN9              BIT(9)                   /*!< falling edge from line 9 */
#define EXTI_FTEN0_FTEN10             BIT(10)                  /*!< falling edge from line 10 */
#define EXTI_FTEN0_FTEN11             BIT(11)                  /*!< falling edge from line 11 */
#define EXTI_FTEN0_FTEN12             BIT(12)                  /*!< falling edge from line 12 */
#define EXTI_FTEN0_FTEN13             BIT(13)                  /*!< falling edge from line 13 */
#define EXTI_FTEN0_FTEN14             BIT(14)                  /*!< falling edge from line 14 */
#define EXTI_FTEN0_FTEN15             BIT(15)                  /*!< falling edge from line 15 */
#define EXTI_FTEN0_FTEN16             BIT(16)                  /*!< falling edge from line 16 */
#define EXTI_FTEN0_FTEN17             BIT(17)                  /*!< falling edge from line 17 */
#define EXTI_FTEN0_FTEN18             BIT(18)                  /*!< falling edge from line 18 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_FTEN0_FTEN19             BIT(19)                  /*!< falling edge from line 19 */
#define EXTI_FTEN0_FTEN20             BIT(20)                  /*!< falling edge from line 20 */
#define EXTI_FTEN0_FTEN21             BIT(21)                  /*!< falling edge from line 21 */
#define EXTI_FTEN0_FTEN22             BIT(22)                  /*!< falling edge from line 22 */
#define EXTI_FTEN0_FTEN23             BIT(23)                  /*!< falling edge from line 23 */
#define EXTI_FTEN0_FTEN24             BIT(24)                  /*!< falling edge from line 24 */
#define EXTI_FTEN0_FTEN25             BIT(25)                  /*!< falling edge from line 25 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_FTEN0_FTEN26             BIT(26)                  /*!< falling edge from line 26 */
#define EXTI_FTEN0_FTEN27             BIT(27)                  /*!< falling edge from line 27 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_FTEN0_FTEN28             BIT(28)                  /*!< falling edge from line 28 */
#define EXTI_FTEN0_FTEN29             BIT(29)                  /*!< falling edge from line 29 */
#define EXTI_FTEN0_FTEN30             BIT(30)                  /*!< falling edge from line 30 */
#define EXTI_FTEN0_FTEN31             BIT(31)                  /*!< falling edge from line 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* EXTI_SWIEV0 */
#define EXTI_SWIEV0_SWIEV0            BIT(0)                   /*!< software interrupt/event request from line 0 */
#define EXTI_SWIEV0_SWIEV1            BIT(1)                   /*!< software interrupt/event request from line 1 */
#define EXTI_SWIEV0_SWIEV2            BIT(2)                   /*!< software interrupt/event request from line 2 */
#define EXTI_SWIEV0_SWIEV3            BIT(3)                   /*!< software interrupt/event request from line 3 */
#define EXTI_SWIEV0_SWIEV4            BIT(4)                   /*!< software interrupt/event request from line 4 */
#define EXTI_SWIEV0_SWIEV5            BIT(5)                   /*!< software interrupt/event request from line 5 */
#define EXTI_SWIEV0_SWIEV6            BIT(6)                   /*!< software interrupt/event request from line 6 */
#define EXTI_SWIEV0_SWIEV7            BIT(7)                   /*!< software interrupt/event request from line 7 */
#define EXTI_SWIEV0_SWIEV8            BIT(8)                   /*!< software interrupt/event request from line 8 */
#define EXTI_SWIEV0_SWIEV9            BIT(9)                   /*!< software interrupt/event request from line 9 */
#define EXTI_SWIEV0_SWIEV10           BIT(10)                  /*!< software interrupt/event request from line 10 */
#define EXTI_SWIEV0_SWIEV11           BIT(11)                  /*!< software interrupt/event request from line 11 */
#define EXTI_SWIEV0_SWIEV12           BIT(12)                  /*!< software interrupt/event request from line 12 */
#define EXTI_SWIEV0_SWIEV13           BIT(13)                  /*!< software interrupt/event request from line 13 */
#define EXTI_SWIEV0_SWIEV14           BIT(14)                  /*!< software interrupt/event request from line 14 */
#define EXTI_SWIEV0_SWIEV15           BIT(15)                  /*!< software interrupt/event request from line 15 */
#define EXTI_SWIEV0_SWIEV16           BIT(16)                  /*!< software interrupt/event request from line 16 */
#define EXTI_SWIEV0_SWIEV17           BIT(17)                  /*!< software interrupt/event request from line 17 */
#define EXTI_SWIEV0_SWIEV18           BIT(18)                  /*!< software interrupt/event request from line 18 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_SWIEV0_SWIEV19           BIT(19)                  /*!< software interrupt/event request from line 19 */
#define EXTI_SWIEV0_SWIEV20           BIT(20)                  /*!< software interrupt/event request from line 20 */
#define EXTI_SWIEV0_SWIEV21           BIT(21)                  /*!< software interrupt/event request from line 21 */
#define EXTI_SWIEV0_SWIEV22           BIT(22)                  /*!< software interrupt/event request from line 22 */
#define EXTI_SWIEV0_SWIEV23           BIT(23)                  /*!< software interrupt/event request from line 23 */
#define EXTI_SWIEV0_SWIEV24           BIT(24)                  /*!< software interrupt/event request from line 24 */
#define EXTI_SWIEV0_SWIEV25           BIT(25)                  /*!< software interrupt/event request from line 25 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_SWIEV0_SWIEV26           BIT(26)                  /*!< software interrupt/event request from line 26 */
#define EXTI_SWIEV0_SWIEV27           BIT(27)                  /*!< software interrupt/event request from line 27 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_SWIEV0_SWIEV28           BIT(28)                  /*!< software interrupt/event request from line 28 */
#define EXTI_SWIEV0_SWIEV29           BIT(29)                  /*!< software interrupt/event request from line 29 */
#define EXTI_SWIEV0_SWIEV30           BIT(30)                  /*!< software interrupt/event request from line 30 */
#define EXTI_SWIEV0_SWIEV31           BIT(31)                  /*!< software interrupt/event request from line 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* EXTI_PD0 */
#define EXTI_PD0_PD0                  BIT(0)                   /*!< interrupt/event pending status from line 0 */
#define EXTI_PD0_PD1                  BIT(1)                   /*!< interrupt/event pending status from line 1 */
#define EXTI_PD0_PD2                  BIT(2)                   /*!< interrupt/event pending status from line 2 */
#define EXTI_PD0_PD3                  BIT(3)                   /*!< interrupt/event pending status from line 3 */
#define EXTI_PD0_PD4                  BIT(4)                   /*!< interrupt/event pending status from line 4 */
#define EXTI_PD0_PD5                  BIT(5)                   /*!< interrupt/event pending status from line 5 */
#define EXTI_PD0_PD6                  BIT(6)                   /*!< interrupt/event pending status from line 6 */
#define EXTI_PD0_PD7                  BIT(7)                   /*!< interrupt/event pending status from line 7 */
#define EXTI_PD0_PD8                  BIT(8)                   /*!< interrupt/event pending status from line 8 */
#define EXTI_PD0_PD9                  BIT(9)                   /*!< interrupt/event pending status from line 9 */
#define EXTI_PD0_PD10                 BIT(10)                  /*!< interrupt/event pending status from line 10 */
#define EXTI_PD0_PD11                 BIT(11)                  /*!< interrupt/event pending status from line 11 */
#define EXTI_PD0_PD12                 BIT(12)                  /*!< interrupt/event pending status from line 12 */
#define EXTI_PD0_PD13                 BIT(13)                  /*!< interrupt/event pending status from line 13 */
#define EXTI_PD0_PD14                 BIT(14)                  /*!< interrupt/event pending status from line 14 */
#define EXTI_PD0_PD15                 BIT(15)                  /*!< interrupt/event pending status from line 15 */
#define EXTI_PD0_PD16                 BIT(16)                  /*!< interrupt/event pending status from line 16 */
#define EXTI_PD0_PD17                 BIT(17)                  /*!< interrupt/event pending status from line 17 */
#define EXTI_PD0_PD18                 BIT(18)                  /*!< interrupt/event pending status from line 18 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_PD0_PD19                 BIT(19)                  /*!< interrupt/event pending status from line 19 */
#define EXTI_PD0_PD20                 BIT(20)                  /*!< interrupt/event pending status from line 20 */
#define EXTI_PD0_PD21                 BIT(21)                  /*!< interrupt/event pending status from line 21 */
#define EXTI_PD0_PD22                 BIT(22)                  /*!< interrupt/event pending status from line 22 */
#define EXTI_PD0_PD23                 BIT(23)                  /*!< interrupt/event pending status from line 23 */
#define EXTI_PD0_PD24                 BIT(24)                  /*!< interrupt/event pending status from line 24 */
#define EXTI_PD0_PD25                 BIT(25)                  /*!< interrupt/event pending status from line 25 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_PD0_PD26                 BIT(26)                  /*!< interrupt/event pending status from line 26 */
#define EXTI_PD0_PD27                 BIT(27)                  /*!< interrupt/event pending status from line 27 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_PD0_PD28                 BIT(28)                  /*!< interrupt/event pending status from line 28 */
#define EXTI_PD0_PD29                 BIT(29)                  /*!< interrupt/event pending status from line 29 */
#define EXTI_PD0_PD30                 BIT(30)                  /*!< interrupt/event pending status from line 30 */
#define EXTI_PD0_PD31                 BIT(31)                  /*!< interrupt/event pending status from line 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* EXTI_INTEN1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_INTEN1_INTEN32            BIT(0)                  /*!< interrupt from line 32 */
#define EXTI_INTEN1_INTEN33            BIT(1)                  /*!< interrupt from line 33 */
#define EXTI_INTEN1_INTEN34            BIT(2)                  /*!< interrupt from line 34 */
#define EXTI_INTEN1_INTEN35            BIT(3)                  /*!< interrupt from line 35 */
#define EXTI_INTEN1_INTEN36            BIT(4)                  /*!< interrupt from line 36 */
#define EXTI_INTEN1_INTEN37            BIT(5)                  /*!< interrupt from line 37 */
#define EXTI_INTEN1_INTEN38            BIT(6)                  /*!< interrupt from line 38 */
#define EXTI_INTEN1_INTEN39            BIT(7)                  /*!< interrupt from line 39 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_INTEN1_INTEN40            BIT(8)                  /*!< interrupt from line 40 */
#define EXTI_INTEN1_INTEN41            BIT(9)                  /*!< interrupt from line 41 */

/* EXTI_EVEN1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_EVEN1_EVEN32              BIT(0)                  /*!< event from line 32 */
#define EXTI_EVEN1_EVEN33              BIT(1)                  /*!< event from line 33 */
#define EXTI_EVEN1_EVEN34              BIT(2)                  /*!< event from line 34 */
#define EXTI_EVEN1_EVEN35              BIT(3)                  /*!< event from line 35 */
#define EXTI_EVEN1_EVEN36              BIT(4)                  /*!< event from line 36 */
#define EXTI_EVEN1_EVEN37              BIT(5)                  /*!< event from line 37 */
#define EXTI_EVEN1_EVEN38              BIT(6)                  /*!< event from line 38 */
#define EXTI_EVEN1_EVEN39              BIT(7)                  /*!< event from line 39 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_EVEN1_EVEN40              BIT(8)                  /*!< event from line 40 */
#define EXTI_EVEN1_EVEN41              BIT(9)                  /*!< event from line 41 */

/* EXTI_RTEN1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_RTEN1_RTEN32              BIT(0)                  /*!< rising edge from line 32 */
#define EXTI_RTEN1_RTEN33              BIT(1)                  /*!< rising edge from line 33 */
#define EXTI_RTEN1_RTEN34              BIT(2)                  /*!< rising edge from line 34 */
#define EXTI_RTEN1_RTEN35              BIT(3)                  /*!< rising edge from line 35 */
#define EXTI_RTEN1_RTEN36              BIT(4)                  /*!< rising edge from line 36 */
#define EXTI_RTEN1_RTEN37              BIT(5)                  /*!< rising edge from line 37 */
#define EXTI_RTEN1_RTEN38              BIT(6)                  /*!< rising edge from line 38 */
#define EXTI_RTEN1_RTEN39              BIT(7)                  /*!< rising edge from line 39 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_RTEN1_RTEN40              BIT(8)                  /*!< rising edge from line 40 */
#define EXTI_RTEN1_RTEN41              BIT(9)                  /*!< rising edge from line 41 */

/* EXTI_FTEN1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_FTEN1_FTEN32              BIT(0)                  /*!< falling edge from line 32 */
#define EXTI_FTEN1_FTEN33              BIT(1)                  /*!< falling edge from line 33 */
#define EXTI_FTEN1_FTEN34              BIT(2)                  /*!< falling edge from line 34 */
#define EXTI_FTEN1_FTEN35              BIT(3)                  /*!< falling edge from line 35 */
#define EXTI_FTEN1_FTEN36              BIT(4)                  /*!< falling edge from line 36 */
#define EXTI_FTEN1_FTEN37              BIT(5)                  /*!< falling edge from line 37 */
#define EXTI_FTEN1_FTEN38              BIT(6)                  /*!< falling edge from line 38 */
#define EXTI_FTEN1_FTEN39              BIT(7)                  /*!< falling edge from line 39 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_FTEN1_FTEN40              BIT(8)                  /*!< falling edge from line 40 */
#define EXTI_FTEN1_FTEN41              BIT(9)                  /*!< falling edge from line 41 */

/* EXTI_SWIEV1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_SWIEV1_SWIEV32            BIT(0)                  /*!< software interrupt/event request from line 32 */
#define EXTI_SWIEV1_SWIEV33            BIT(1)                  /*!< software interrupt/event request from line 33 */
#define EXTI_SWIEV1_SWIEV34            BIT(2)                  /*!< software interrupt/event request from line 34 */
#define EXTI_SWIEV1_SWIEV35            BIT(3)                  /*!< software interrupt/event request from line 35 */
#define EXTI_SWIEV1_SWIEV36            BIT(4)                  /*!< software interrupt/event request from line 36 */
#define EXTI_SWIEV1_SWIEV37            BIT(5)                  /*!< software interrupt/event request from line 37 */
#define EXTI_SWIEV1_SWIEV38            BIT(6)                  /*!< software interrupt/event request from line 38 */
#define EXTI_SWIEV1_SWIEV39            BIT(7)                  /*!< software interrupt/event request from line 39 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_SWIEV1_SWIEV40            BIT(8)                  /*!< software interrupt/event request from line 40 */
#define EXTI_SWIEV1_SWIEV41            BIT(9)                  /*!< software interrupt/event request from line 41 */

/* EXTI_PD1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define EXTI_PD1_PD32                  BIT(0)                  /*!< interrupt/event pending status from line 32 */
#define EXTI_PD1_PD33                  BIT(1)                  /*!< interrupt/event pending status from line 33 */
#define EXTI_PD1_PD34                  BIT(2)                  /*!< interrupt/event pending status from line 34 */
#define EXTI_PD1_PD35                  BIT(3)                  /*!< interrupt/event pending status from line 35 */
#define EXTI_PD1_PD36                  BIT(4)                  /*!< interrupt/event pending status from line 36 */
#define EXTI_PD1_PD37                  BIT(5)                  /*!< interrupt/event pending status from line 37 */
#define EXTI_PD1_PD38                  BIT(6)                  /*!< interrupt/event pending status from line 38 */
#define EXTI_PD1_PD39                  BIT(7)                  /*!< interrupt/event pending status from line 39 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define EXTI_PD1_PD40                  BIT(8)                  /*!< interrupt/event pending status from line 40 */
#define EXTI_PD1_PD41                  BIT(9)                  /*!< interrupt/event pending status from line 41 */

/* EXTI_INTEN2 */
#define EXTI_INTEN2_INTEN42            BIT(0)                   /*!< interrupt from line 42 */
#define EXTI_INTEN2_INTEN43            BIT(1)                   /*!< interrupt from line 43 */
#define EXTI_INTEN2_INTEN44            BIT(2)                   /*!< interrupt from line 44 */
#define EXTI_INTEN2_INTEN45            BIT(3)                   /*!< interrupt from line 45 */
#define EXTI_INTEN2_INTEN46            BIT(4)                   /*!< interrupt from line 46 */
#define EXTI_INTEN2_INTEN47            BIT(5)                   /*!< interrupt from line 47 */
#define EXTI_INTEN2_INTEN48            BIT(6)                   /*!< interrupt from line 48 */
#define EXTI_INTEN2_INTEN49            BIT(7)                   /*!< interrupt from line 49 */
#define EXTI_INTEN2_INTEN50            BIT(8)                   /*!< interrupt from line 50 */
#define EXTI_INTEN2_INTEN51            BIT(9)                   /*!< interrupt from line 51 */
#define EXTI_INTEN2_INTEN52            BIT(10)                  /*!< interrupt from line 52 */
#define EXTI_INTEN2_INTEN53            BIT(11)                  /*!< interrupt from line 53 */
#define EXTI_INTEN2_INTEN54            BIT(12)                  /*!< interrupt from line 54 */
#define EXTI_INTEN2_INTEN55            BIT(13)                  /*!< interrupt from line 55 */
#define EXTI_INTEN2_INTEN56            BIT(14)                  /*!< interrupt from line 56 */
#define EXTI_INTEN2_INTEN57            BIT(15)                  /*!< interrupt from line 57 */
#define EXTI_INTEN2_INTEN58            BIT(16)                  /*!< interrupt from line 58 */
#define EXTI_INTEN2_INTEN59            BIT(17)                  /*!< interrupt from line 59 */
#define EXTI_INTEN2_INTEN60            BIT(18)                  /*!< interrupt from line 60 */
#define EXTI_INTEN2_INTEN61            BIT(19)                  /*!< interrupt from line 61 */
#define EXTI_INTEN2_INTEN62            BIT(20)                  /*!< interrupt from line 62 */
#define EXTI_INTEN2_INTEN63            BIT(21)                  /*!< interrupt from line 63 */
#define EXTI_INTEN2_INTEN64            BIT(22)                  /*!< interrupt from line 64 */
#define EXTI_INTEN2_INTEN65            BIT(23)                  /*!< interrupt from line 65 */
#define EXTI_INTEN2_INTEN66            BIT(24)                  /*!< interrupt from line 66 */
#define EXTI_INTEN2_INTEN67            BIT(25)                  /*!< interrupt from line 67 */
#define EXTI_INTEN2_INTEN68            BIT(26)                  /*!< interrupt from line 68 */
#define EXTI_INTEN2_INTEN69            BIT(27)                  /*!< interrupt from line 69 */
#define EXTI_INTEN2_INTEN70            BIT(28)                  /*!< interrupt from line 70 */
#define EXTI_INTEN2_INTEN71            BIT(29)                  /*!< interrupt from line 71 */
#define EXTI_INTEN2_INTEN72            BIT(30)                  /*!< interrupt from line 72 */
#define EXTI_INTEN2_INTEN73            BIT(31)                  /*!< interrupt from line 73 */

/* EXTI_EVEN2 */
#define EXTI_EVEN2_EVEN42              BIT(0)                   /*!< event from line 42 */
#define EXTI_EVEN2_EVEN43              BIT(1)                   /*!< event from line 43 */
#define EXTI_EVEN2_EVEN44              BIT(2)                   /*!< event from line 44 */
#define EXTI_EVEN2_EVEN45              BIT(3)                   /*!< event from line 45 */
#define EXTI_EVEN2_EVEN46              BIT(4)                   /*!< event from line 46 */
#define EXTI_EVEN2_EVEN47              BIT(5)                   /*!< event from line 47 */
#define EXTI_EVEN2_EVEN48              BIT(6)                   /*!< event from line 48 */
#define EXTI_EVEN2_EVEN49              BIT(7)                   /*!< event from line 49 */
#define EXTI_EVEN2_EVEN50              BIT(8)                   /*!< event from line 50 */
#define EXTI_EVEN2_EVEN51              BIT(9)                   /*!< event from line 51 */
#define EXTI_EVEN2_EVEN52              BIT(10)                  /*!< event from line 52 */
#define EXTI_EVEN2_EVEN53              BIT(11)                  /*!< event from line 53 */
#define EXTI_EVEN2_EVEN54              BIT(12)                  /*!< event from line 54 */
#define EXTI_EVEN2_EVEN55              BIT(13)                  /*!< event from line 55 */
#define EXTI_EVEN2_EVEN56              BIT(14)                  /*!< event from line 56 */
#define EXTI_EVEN2_EVEN57              BIT(15)                  /*!< event from line 57 */
#define EXTI_EVEN2_EVEN58              BIT(16)                  /*!< event from line 58 */
#define EXTI_EVEN2_EVEN59              BIT(17)                  /*!< event from line 59 */
#define EXTI_EVEN2_EVEN60              BIT(18)                  /*!< event from line 60 */
#define EXTI_EVEN2_EVEN61              BIT(19)                  /*!< event from line 61 */
#define EXTI_EVEN2_EVEN62              BIT(20)                  /*!< event from line 62 */
#define EXTI_EVEN2_EVEN63              BIT(21)                  /*!< event from line 63 */
#define EXTI_EVEN2_EVEN64              BIT(22)                  /*!< event from line 64 */
#define EXTI_EVEN2_EVEN65              BIT(23)                  /*!< event from line 65 */
#define EXTI_EVEN2_EVEN66              BIT(24)                  /*!< event from line 66 */
#define EXTI_EVEN2_EVEN67              BIT(25)                  /*!< event from line 67 */
#define EXTI_EVEN2_EVEN68              BIT(26)                  /*!< event from line 68 */
#define EXTI_EVEN2_EVEN69              BIT(27)                  /*!< event from line 69 */
#define EXTI_EVEN2_EVEN70              BIT(28)                  /*!< event from line 70 */
#define EXTI_EVEN2_EVEN71              BIT(29)                  /*!< event from line 71 */
#define EXTI_EVEN2_EVEN72              BIT(30)                  /*!< event from line 72 */
#define EXTI_EVEN2_EVEN73              BIT(31)                  /*!< event from line 73 */

/* EXTI_RTEN2 */
#define EXTI_RTEN2_RTEN42              BIT(0)                   /*!< rising edge from line 42 */
#define EXTI_RTEN2_RTEN43              BIT(1)                   /*!< rising edge from line 43 */
#define EXTI_RTEN2_RTEN44              BIT(2)                   /*!< rising edge from line 44 */
#define EXTI_RTEN2_RTEN45              BIT(3)                   /*!< rising edge from line 45 */
#define EXTI_RTEN2_RTEN46              BIT(4)                   /*!< rising edge from line 46 */
#define EXTI_RTEN2_RTEN47              BIT(5)                   /*!< rising edge from line 47 */
#define EXTI_RTEN2_RTEN48              BIT(6)                   /*!< rising edge from line 48 */
#define EXTI_RTEN2_RTEN49              BIT(7)                   /*!< rising edge from line 49 */
#define EXTI_RTEN2_RTEN50              BIT(8)                   /*!< rising edge from line 50 */
#define EXTI_RTEN2_RTEN51              BIT(9)                   /*!< rising edge from line 51 */
#define EXTI_RTEN2_RTEN52              BIT(10)                  /*!< rising edge from line 52 */
#define EXTI_RTEN2_RTEN53              BIT(11)                  /*!< rising edge from line 53 */
#define EXTI_RTEN2_RTEN54              BIT(12)                  /*!< rising edge from line 54 */
#define EXTI_RTEN2_RTEN55              BIT(13)                  /*!< rising edge from line 55 */
#define EXTI_RTEN2_RTEN56              BIT(14)                  /*!< rising edge from line 56 */
#define EXTI_RTEN2_RTEN57              BIT(15)                  /*!< rising edge from line 57 */
#define EXTI_RTEN2_RTEN58              BIT(16)                  /*!< rising edge from line 58 */
#define EXTI_RTEN2_RTEN59              BIT(17)                  /*!< rising edge from line 59 */
#define EXTI_RTEN2_RTEN60              BIT(18)                  /*!< rising edge from line 60 */
#define EXTI_RTEN2_RTEN61              BIT(19)                  /*!< rising edge from line 61 */
#define EXTI_RTEN2_RTEN62              BIT(20)                  /*!< rising edge from line 62 */
#define EXTI_RTEN2_RTEN63              BIT(21)                  /*!< rising edge from line 63 */
#define EXTI_RTEN2_RTEN64              BIT(22)                  /*!< rising edge from line 64 */
#define EXTI_RTEN2_RTEN65              BIT(23)                  /*!< rising edge from line 65 */
#define EXTI_RTEN2_RTEN66              BIT(24)                  /*!< rising edge from line 66 */
#define EXTI_RTEN2_RTEN67              BIT(25)                  /*!< rising edge from line 67 */
#define EXTI_RTEN2_RTEN68              BIT(26)                  /*!< rising edge from line 68 */
#define EXTI_RTEN2_RTEN69              BIT(27)                  /*!< rising edge from line 69 */
#define EXTI_RTEN2_RTEN70              BIT(28)                  /*!< rising edge from line 70 */
#define EXTI_RTEN2_RTEN71              BIT(29)                  /*!< rising edge from line 71 */
#define EXTI_RTEN2_RTEN72              BIT(30)                  /*!< rising edge from line 72 */
#define EXTI_RTEN2_RTEN73              BIT(31)                  /*!< rising edge from line 73 */

/* EXTI_FTEN2 */
#define EXTI_FTEN2_FTEN42              BIT(0)                   /*!< falling edge from line 42 */
#define EXTI_FTEN2_FTEN43              BIT(1)                   /*!< falling edge from line 43 */
#define EXTI_FTEN2_FTEN44              BIT(2)                   /*!< falling edge from line 44 */
#define EXTI_FTEN2_FTEN45              BIT(3)                   /*!< falling edge from line 45 */
#define EXTI_FTEN2_FTEN46              BIT(4)                   /*!< falling edge from line 46 */
#define EXTI_FTEN2_FTEN47              BIT(5)                   /*!< falling edge from line 47 */
#define EXTI_FTEN2_FTEN48              BIT(6)                   /*!< falling edge from line 48 */
#define EXTI_FTEN2_FTEN49              BIT(7)                   /*!< falling edge from line 49 */
#define EXTI_FTEN2_FTEN50              BIT(8)                   /*!< falling edge from line 50 */
#define EXTI_FTEN2_FTEN51              BIT(9)                   /*!< falling edge from line 51 */
#define EXTI_FTEN2_FTEN52              BIT(10)                  /*!< falling edge from line 52 */
#define EXTI_FTEN2_FTEN53              BIT(11)                  /*!< falling edge from line 53 */
#define EXTI_FTEN2_FTEN54              BIT(12)                  /*!< falling edge from line 54 */
#define EXTI_FTEN2_FTEN55              BIT(13)                  /*!< falling edge from line 55 */
#define EXTI_FTEN2_FTEN56              BIT(14)                  /*!< falling edge from line 56 */
#define EXTI_FTEN2_FTEN57              BIT(15)                  /*!< falling edge from line 57 */
#define EXTI_FTEN2_FTEN58              BIT(16)                  /*!< falling edge from line 58 */
#define EXTI_FTEN2_FTEN59              BIT(17)                  /*!< falling edge from line 59 */
#define EXTI_FTEN2_FTEN60              BIT(18)                  /*!< falling edge from line 60 */
#define EXTI_FTEN2_FTEN61              BIT(19)                  /*!< falling edge from line 61 */
#define EXTI_FTEN2_FTEN62              BIT(20)                  /*!< falling edge from line 62 */
#define EXTI_FTEN2_FTEN63              BIT(21)                  /*!< falling edge from line 63 */
#define EXTI_FTEN2_FTEN64              BIT(22)                  /*!< falling edge from line 64 */
#define EXTI_FTEN2_FTEN65              BIT(23)                  /*!< falling edge from line 65 */
#define EXTI_FTEN2_FTEN66              BIT(24)                  /*!< falling edge from line 66 */
#define EXTI_FTEN2_FTEN67              BIT(25)                  /*!< falling edge from line 67 */
#define EXTI_FTEN2_FTEN68              BIT(26)                  /*!< falling edge from line 68 */
#define EXTI_FTEN2_FTEN69              BIT(27)                  /*!< falling edge from line 69 */
#define EXTI_FTEN2_FTEN70              BIT(28)                  /*!< falling edge from line 70 */
#define EXTI_FTEN2_FTEN71              BIT(29)                  /*!< falling edge from line 71 */
#define EXTI_FTEN2_FTEN72              BIT(30)                  /*!< falling edge from line 72 */
#define EXTI_FTEN2_FTEN73              BIT(31)                  /*!< falling edge from line 73 */

/* EXTI_SWIEV2 */
#define EXTI_SWIEV2_SWIEV42            BIT(0)                   /*!< software interrupt/event request from line 42 */
#define EXTI_SWIEV2_SWIEV43            BIT(1)                   /*!< software interrupt/event request from line 43 */
#define EXTI_SWIEV2_SWIEV44            BIT(2)                   /*!< software interrupt/event request from line 44 */
#define EXTI_SWIEV2_SWIEV45            BIT(3)                   /*!< software interrupt/event request from line 45 */
#define EXTI_SWIEV2_SWIEV46            BIT(4)                   /*!< software interrupt/event request from line 46 */
#define EXTI_SWIEV2_SWIEV47            BIT(5)                   /*!< software interrupt/event request from line 47 */
#define EXTI_SWIEV2_SWIEV48            BIT(6)                   /*!< software interrupt/event request from line 48 */
#define EXTI_SWIEV2_SWIEV49            BIT(7)                   /*!< software interrupt/event request from line 49 */
#define EXTI_SWIEV2_SWIEV50            BIT(8)                   /*!< software interrupt/event request from line 50 */
#define EXTI_SWIEV2_SWIEV51            BIT(9)                   /*!< software interrupt/event request from line 51 */
#define EXTI_SWIEV2_SWIEV52            BIT(10)                  /*!< software interrupt/event request from line 52 */
#define EXTI_SWIEV2_SWIEV53            BIT(11)                  /*!< software interrupt/event request from line 53 */
#define EXTI_SWIEV2_SWIEV54            BIT(12)                  /*!< software interrupt/event request from line 54 */
#define EXTI_SWIEV2_SWIEV55            BIT(13)                  /*!< software interrupt/event request from line 55 */
#define EXTI_SWIEV2_SWIEV56            BIT(14)                  /*!< software interrupt/event request from line 56 */
#define EXTI_SWIEV2_SWIEV57            BIT(15)                  /*!< software interrupt/event request from line 57 */
#define EXTI_SWIEV2_SWIEV58            BIT(16)                  /*!< software interrupt/event request from line 58 */
#define EXTI_SWIEV2_SWIEV59            BIT(17)                  /*!< software interrupt/event request from line 59 */
#define EXTI_SWIEV2_SWIEV60            BIT(18)                  /*!< software interrupt/event request from line 60 */
#define EXTI_SWIEV2_SWIEV61            BIT(19)                  /*!< software interrupt/event request from line 61 */
#define EXTI_SWIEV2_SWIEV62            BIT(20)                  /*!< software interrupt/event request from line 62 */
#define EXTI_SWIEV2_SWIEV63            BIT(21)                  /*!< software interrupt/event request from line 63 */
#define EXTI_SWIEV2_SWIEV64            BIT(22)                  /*!< software interrupt/event request from line 64 */
#define EXTI_SWIEV2_SWIEV65            BIT(23)                  /*!< software interrupt/event request from line 65 */
#define EXTI_SWIEV2_SWIEV66            BIT(24)                  /*!< software interrupt/event request from line 66 */
#define EXTI_SWIEV2_SWIEV67            BIT(25)                  /*!< software interrupt/event request from line 67 */
#define EXTI_SWIEV2_SWIEV68            BIT(26)                  /*!< software interrupt/event request from line 68 */
#define EXTI_SWIEV2_SWIEV69            BIT(27)                  /*!< software interrupt/event request from line 69 */
#define EXTI_SWIEV2_SWIEV70            BIT(28)                  /*!< software interrupt/event request from line 70 */
#define EXTI_SWIEV2_SWIEV71            BIT(29)                  /*!< software interrupt/event request from line 71 */
#define EXTI_SWIEV2_SWIEV72            BIT(30)                  /*!< software interrupt/event request from line 72 */
#define EXTI_SWIEV2_SWIEV73            BIT(31)                  /*!< software interrupt/event request from line 73 */

/* EXTI_PD2 */
#define EXTI_PD2_PD42                  BIT(0)                   /*!< interrupt/event pending status from line 42 */
#define EXTI_PD2_PD43                  BIT(1)                   /*!< interrupt/event pending status from line 43 */
#define EXTI_PD2_PD44                  BIT(2)                   /*!< interrupt/event pending status from line 44 */
#define EXTI_PD2_PD45                  BIT(3)                   /*!< interrupt/event pending status from line 45 */
#define EXTI_PD2_PD46                  BIT(4)                   /*!< interrupt/event pending status from line 46 */
#define EXTI_PD2_PD47                  BIT(5)                   /*!< interrupt/event pending status from line 47 */
#define EXTI_PD2_PD48                  BIT(6)                   /*!< interrupt/event pending status from line 48 */
#define EXTI_PD2_PD49                  BIT(7)                   /*!< interrupt/event pending status from line 49 */
#define EXTI_PD2_PD50                  BIT(8)                   /*!< interrupt/event pending status from line 50 */
#define EXTI_PD2_PD51                  BIT(9)                   /*!< interrupt/event pending status from line 51 */
#define EXTI_PD2_PD52                  BIT(10)                  /*!< interrupt/event pending status from line 52 */
#define EXTI_PD2_PD53                  BIT(11)                  /*!< interrupt/event pending status from line 53 */
#define EXTI_PD2_PD54                  BIT(12)                  /*!< interrupt/event pending status from line 54 */
#define EXTI_PD2_PD55                  BIT(13)                  /*!< interrupt/event pending status from line 55 */
#define EXTI_PD2_PD56                  BIT(14)                  /*!< interrupt/event pending status from line 56 */
#define EXTI_PD2_PD57                  BIT(15)                  /*!< interrupt/event pending status from line 57 */
#define EXTI_PD2_PD58                  BIT(16)                  /*!< interrupt/event pending status from line 58 */
#define EXTI_PD2_PD59                  BIT(17)                  /*!< interrupt/event pending status from line 59 */
#define EXTI_PD2_PD60                  BIT(18)                  /*!< interrupt/event pending status from line 60 */
#define EXTI_PD2_PD61                  BIT(19)                  /*!< interrupt/event pending status from line 61 */
#define EXTI_PD2_PD62                  BIT(20)                  /*!< interrupt/event pending status from line 62 */
#define EXTI_PD2_PD63                  BIT(21)                  /*!< interrupt/event pending status from line 63 */
#define EXTI_PD2_PD64                  BIT(22)                  /*!< interrupt/event pending status from line 64 */
#define EXTI_PD2_PD65                  BIT(23)                  /*!< interrupt/event pending status from line 65 */
#define EXTI_PD2_PD66                  BIT(24)                  /*!< interrupt/event pending status from line 66 */
#define EXTI_PD2_PD67                  BIT(25)                  /*!< interrupt/event pending status from line 67 */
#define EXTI_PD2_PD68                  BIT(26)                  /*!< interrupt/event pending status from line 68 */
#define EXTI_PD2_PD69                  BIT(27)                  /*!< interrupt/event pending status from line 69 */
#define EXTI_PD2_PD70                  BIT(28)                  /*!< interrupt/event pending status from line 70 */
#define EXTI_PD2_PD71                  BIT(29)                  /*!< interrupt/event pending status from line 71 */
#define EXTI_PD2_PD72                  BIT(30)                  /*!< interrupt/event pending status from line 72 */
#define EXTI_PD2_PD73                  BIT(31)                  /*!< interrupt/event pending status from line 73 */

/* EXTI_INTEN3 */
#define EXTI_INTEN3_INTEN74            BIT(0)                   /*!< interrupt from line 74 */
#define EXTI_INTEN3_INTEN75            BIT(1)                   /*!< interrupt from line 75 */
#define EXTI_INTEN3_INTEN76            BIT(2)                   /*!< interrupt from line 76 */
#define EXTI_INTEN3_INTEN77            BIT(3)                   /*!< interrupt from line 77 */
#define EXTI_INTEN3_INTEN78            BIT(4)                   /*!< interrupt from line 78 */
#define EXTI_INTEN3_INTEN79            BIT(5)                   /*!< interrupt from line 79 */
#define EXTI_INTEN3_INTEN80            BIT(6)                   /*!< interrupt from line 80 */
#define EXTI_INTEN3_INTEN81            BIT(7)                   /*!< interrupt from line 81 */
#define EXTI_INTEN3_INTEN82            BIT(8)                   /*!< interrupt from line 82 */
#define EXTI_INTEN3_INTEN83            BIT(9)                   /*!< interrupt from line 83 */
#define EXTI_INTEN3_INTEN84            BIT(10)                  /*!< interrupt from line 84 */
#define EXTI_INTEN3_INTEN85            BIT(11)                  /*!< interrupt from line 85 */
#define EXTI_INTEN3_INTEN86            BIT(12)                  /*!< interrupt from line 86 */
#define EXTI_INTEN3_INTEN87            BIT(13)                  /*!< interrupt from line 87 */
#define EXTI_INTEN3_INTEN88            BIT(14)                  /*!< interrupt from line 88 */
#define EXTI_INTEN3_INTEN89            BIT(15)                  /*!< interrupt from line 89 */
#define EXTI_INTEN3_INTEN90            BIT(16)                  /*!< interrupt from line 90 */
#define EXTI_INTEN3_INTEN91            BIT(17)                  /*!< interrupt from line 91 */
#define EXTI_INTEN3_INTEN92            BIT(18)                  /*!< interrupt from line 92 */
#define EXTI_INTEN3_INTEN93            BIT(19)                  /*!< interrupt from line 93 */
#define EXTI_INTEN3_INTEN94            BIT(20)                  /*!< interrupt from line 94 */
#define EXTI_INTEN3_INTEN95            BIT(21)                  /*!< interrupt from line 95 */
#define EXTI_INTEN3_INTEN96            BIT(22)                  /*!< interrupt from line 96 */
#define EXTI_INTEN3_INTEN97            BIT(23)                  /*!< interrupt from line 97 */
#define EXTI_INTEN3_INTEN98            BIT(24)                  /*!< interrupt from line 98 */
#define EXTI_INTEN3_INTEN99            BIT(25)                  /*!< interrupt from line 99 */
#define EXTI_INTEN3_INTEN100           BIT(26)                  /*!< interrupt from line 100 */
#define EXTI_INTEN3_INTEN101           BIT(27)                  /*!< interrupt from line 101 */

/* EXTI_EVEN3 */
#define EXTI_EVEN3_EVEN74             BIT(0)                   /*!< event from line 74 */
#define EXTI_EVEN3_EVEN75             BIT(1)                   /*!< event from line 75 */
#define EXTI_EVEN3_EVEN76             BIT(2)                   /*!< event from line 76 */
#define EXTI_EVEN3_EVEN77             BIT(3)                   /*!< event from line 77 */
#define EXTI_EVEN3_EVEN78             BIT(4)                   /*!< event from line 78 */
#define EXTI_EVEN3_EVEN79             BIT(5)                   /*!< event from line 79 */
#define EXTI_EVEN3_EVEN80             BIT(6)                   /*!< event from line 80 */
#define EXTI_EVEN3_EVEN81             BIT(7)                   /*!< event from line 81 */
#define EXTI_EVEN3_EVEN82             BIT(8)                   /*!< event from line 82 */
#define EXTI_EVEN3_EVEN83             BIT(9)                   /*!< event from line 83 */
#define EXTI_EVEN3_EVEN84             BIT(10)                  /*!< event from line 84 */
#define EXTI_EVEN3_EVEN85             BIT(11)                  /*!< event from line 85 */
#define EXTI_EVEN3_EVEN86             BIT(12)                  /*!< event from line 86 */
#define EXTI_EVEN3_EVEN87             BIT(13)                  /*!< event from line 87 */
#define EXTI_EVEN3_EVEN88             BIT(14)                  /*!< event from line 88 */
#define EXTI_EVEN3_EVEN89             BIT(15)                  /*!< event from line 89 */
#define EXTI_EVEN3_EVEN90             BIT(16)                  /*!< event from line 90 */
#define EXTI_EVEN3_EVEN91             BIT(17)                  /*!< event from line 91 */
#define EXTI_EVEN3_EVEN92             BIT(18)                  /*!< event from line 92 */
#define EXTI_EVEN3_EVEN93             BIT(19)                  /*!< event from line 93 */
#define EXTI_EVEN3_EVEN94             BIT(20)                  /*!< event from line 94 */
#define EXTI_EVEN3_EVEN95             BIT(21)                  /*!< event from line 95 */
#define EXTI_EVEN3_EVEN96             BIT(22)                  /*!< event from line 96 */
#define EXTI_EVEN3_EVEN97             BIT(23)                  /*!< event from line 97 */
#define EXTI_EVEN3_EVEN98             BIT(24)                  /*!< event from line 98 */
#define EXTI_EVEN3_EVEN99             BIT(25)                  /*!< event from line 99 */
#define EXTI_EVEN3_EVEN100            BIT(26)                  /*!< event from line 100 */
#define EXTI_EVEN3_EVEN101            BIT(27)                  /*!< event from line 101 */

/* EXTI_RTEN3 */
#define EXTI_RTEN3_RTEN74             BIT(0)                   /*!< rising edge from line 74 */
#define EXTI_RTEN3_RTEN75             BIT(1)                   /*!< rising edge from line 75 */
#define EXTI_RTEN3_RTEN76             BIT(2)                   /*!< rising edge from line 76 */
#define EXTI_RTEN3_RTEN77             BIT(3)                   /*!< rising edge from line 77 */
#define EXTI_RTEN3_RTEN78             BIT(4)                   /*!< rising edge from line 78 */
#define EXTI_RTEN3_RTEN79             BIT(5)                   /*!< rising edge from line 79 */
#define EXTI_RTEN3_RTEN80             BIT(6)                   /*!< rising edge from line 80 */
#define EXTI_RTEN3_RTEN81             BIT(7)                   /*!< rising edge from line 81 */
#define EXTI_RTEN3_RTEN82             BIT(8)                   /*!< rising edge from line 82 */
#define EXTI_RTEN3_RTEN83             BIT(9)                   /*!< rising edge from line 83 */
#define EXTI_RTEN3_RTEN84             BIT(10)                  /*!< rising edge from line 84 */
#define EXTI_RTEN3_RTEN85             BIT(11)                  /*!< rising edge from line 85 */
#define EXTI_RTEN3_RTEN86             BIT(12)                  /*!< rising edge from line 86 */
#define EXTI_RTEN3_RTEN87             BIT(13)                  /*!< rising edge from line 87 */
#define EXTI_RTEN3_RTEN88             BIT(14)                  /*!< rising edge from line 88 */
#define EXTI_RTEN3_RTEN89             BIT(15)                  /*!< rising edge from line 89 */
#define EXTI_RTEN3_RTEN90             BIT(16)                  /*!< rising edge from line 90 */
#define EXTI_RTEN3_RTEN91             BIT(17)                  /*!< rising edge from line 91 */
#define EXTI_RTEN3_RTEN92             BIT(18)                  /*!< rising edge from line 92 */
#define EXTI_RTEN3_RTEN93             BIT(19)                  /*!< rising edge from line 93 */
#define EXTI_RTEN3_RTEN94             BIT(20)                  /*!< rising edge from line 94 */
#define EXTI_RTEN3_RTEN95             BIT(21)                  /*!< rising edge from line 95 */
#define EXTI_RTEN3_RTEN96             BIT(22)                  /*!< rising edge from line 96 */
#define EXTI_RTEN3_RTEN97             BIT(23)                  /*!< rising edge from line 97 */
#define EXTI_RTEN3_RTEN98             BIT(24)                  /*!< rising edge from line 98 */
#define EXTI_RTEN3_RTEN99             BIT(25)                  /*!< rising edge from line 99 */
#define EXTI_RTEN3_RTEN100            BIT(26)                  /*!< rising edge from line 100 */
#define EXTI_RTEN3_RTEN101            BIT(27)                  /*!< rising edge from line 101 */

/* EXTI_FTEN3 */
#define EXTI_FTEN3_FTEN74             BIT(0)                   /*!< falling edge from line 74 */
#define EXTI_FTEN3_FTEN75             BIT(1)                   /*!< falling edge from line 75 */
#define EXTI_FTEN3_FTEN76             BIT(2)                   /*!< falling edge from line 76 */
#define EXTI_FTEN3_FTEN77             BIT(3)                   /*!< falling edge from line 77 */
#define EXTI_FTEN3_FTEN78             BIT(4)                   /*!< falling edge from line 78 */
#define EXTI_FTEN3_FTEN79             BIT(5)                   /*!< falling edge from line 79 */
#define EXTI_FTEN3_FTEN80             BIT(6)                   /*!< falling edge from line 80 */
#define EXTI_FTEN3_FTEN81             BIT(7)                   /*!< falling edge from line 81 */
#define EXTI_FTEN3_FTEN82             BIT(8)                   /*!< falling edge from line 82 */
#define EXTI_FTEN3_FTEN83             BIT(9)                   /*!< falling edge from line 83 */
#define EXTI_FTEN3_FTEN84             BIT(10)                  /*!< falling edge from line 84 */
#define EXTI_FTEN3_FTEN85             BIT(11)                  /*!< falling edge from line 85 */
#define EXTI_FTEN3_FTEN86             BIT(12)                  /*!< falling edge from line 86 */
#define EXTI_FTEN3_FTEN87             BIT(13)                  /*!< falling edge from line 87 */
#define EXTI_FTEN3_FTEN88             BIT(14)                  /*!< falling edge from line 88 */
#define EXTI_FTEN3_FTEN89             BIT(15)                  /*!< falling edge from line 89 */
#define EXTI_FTEN3_FTEN90             BIT(16)                  /*!< falling edge from line 90 */
#define EXTI_FTEN3_FTEN91             BIT(17)                  /*!< falling edge from line 91 */
#define EXTI_FTEN3_FTEN92             BIT(18)                  /*!< falling edge from line 92 */
#define EXTI_FTEN3_FTEN93             BIT(19)                  /*!< falling edge from line 93 */
#define EXTI_FTEN3_FTEN94             BIT(20)                  /*!< falling edge from line 94 */
#define EXTI_FTEN3_FTEN95             BIT(21)                  /*!< falling edge from line 95 */
#define EXTI_FTEN3_FTEN96             BIT(22)                  /*!< falling edge from line 96 */
#define EXTI_FTEN3_FTEN97             BIT(23)                  /*!< falling edge from line 97 */
#define EXTI_FTEN3_FTEN98             BIT(24)                  /*!< falling edge from line 98 */
#define EXTI_FTEN3_FTEN99             BIT(25)                  /*!< falling edge from line 99 */
#define EXTI_FTEN3_FTEN100            BIT(26)                  /*!< falling edge from line 100 */
#define EXTI_FTEN3_FTEN101            BIT(27)                  /*!< falling edge from line 101 */

/* EXTI_SWIEV3 */
#define EXTI_SWIEV3_SWIEV74           BIT(0)                   /*!< software interrupt/event request from line 74 */
#define EXTI_SWIEV3_SWIEV75           BIT(1)                   /*!< software interrupt/event request from line 75 */
#define EXTI_SWIEV3_SWIEV76           BIT(2)                   /*!< software interrupt/event request from line 76 */
#define EXTI_SWIEV3_SWIEV77           BIT(3)                   /*!< software interrupt/event request from line 77 */
#define EXTI_SWIEV3_SWIEV78           BIT(4)                   /*!< software interrupt/event request from line 78 */
#define EXTI_SWIEV3_SWIEV79           BIT(5)                   /*!< software interrupt/event request from line 79 */
#define EXTI_SWIEV3_SWIEV80           BIT(6)                   /*!< software interrupt/event request from line 80 */
#define EXTI_SWIEV3_SWIEV81           BIT(7)                   /*!< software interrupt/event request from line 81 */
#define EXTI_SWIEV3_SWIEV82           BIT(8)                   /*!< software interrupt/event request from line 82 */
#define EXTI_SWIEV3_SWIEV83           BIT(9)                   /*!< software interrupt/event request from line 83 */
#define EXTI_SWIEV3_SWIEV84           BIT(10)                  /*!< software interrupt/event request from line 84 */
#define EXTI_SWIEV3_SWIEV85           BIT(11)                  /*!< software interrupt/event request from line 85 */
#define EXTI_SWIEV3_SWIEV86           BIT(12)                  /*!< software interrupt/event request from line 86 */
#define EXTI_SWIEV3_SWIEV87           BIT(13)                  /*!< software interrupt/event request from line 87 */
#define EXTI_SWIEV3_SWIEV88           BIT(14)                  /*!< software interrupt/event request from line 88 */
#define EXTI_SWIEV3_SWIEV89           BIT(15)                  /*!< software interrupt/event request from line 89 */
#define EXTI_SWIEV3_SWIEV90           BIT(16)                  /*!< software interrupt/event request from line 90 */
#define EXTI_SWIEV3_SWIEV91           BIT(17)                  /*!< software interrupt/event request from line 91 */
#define EXTI_SWIEV3_SWIEV92           BIT(18)                  /*!< software interrupt/event request from line 92 */
#define EXTI_SWIEV3_SWIEV93           BIT(19)                  /*!< software interrupt/event request from line 93 */
#define EXTI_SWIEV3_SWIEV94           BIT(20)                  /*!< software interrupt/event request from line 94 */
#define EXTI_SWIEV3_SWIEV95           BIT(21)                  /*!< software interrupt/event request from line 95 */
#define EXTI_SWIEV3_SWIEV96           BIT(22)                  /*!< software interrupt/event request from line 96 */
#define EXTI_SWIEV3_SWIEV97           BIT(23)                  /*!< software interrupt/event request from line 97 */
#define EXTI_SWIEV3_SWIEV98           BIT(24)                  /*!< software interrupt/event request from line 98 */
#define EXTI_SWIEV3_SWIEV99           BIT(25)                  /*!< software interrupt/event request from line 99 */
#define EXTI_SWIEV3_SWIEV100          BIT(26)                  /*!< software interrupt/event request from line 100 */
#define EXTI_SWIEV3_SWIEV101          BIT(27)                  /*!< software interrupt/event request from line 101 */

/* EXTI_PD3 */
#define EXTI_PD3_PD74                 BIT(0)                   /*!< interrupt/event pending status from line 74 */
#define EXTI_PD3_PD75                 BIT(1)                   /*!< interrupt/event pending status from line 75 */
#define EXTI_PD3_PD76                 BIT(2)                   /*!< interrupt/event pending status from line 76 */
#define EXTI_PD3_PD77                 BIT(3)                   /*!< interrupt/event pending status from line 77 */
#define EXTI_PD3_PD78                 BIT(4)                   /*!< interrupt/event pending status from line 78 */
#define EXTI_PD3_PD79                 BIT(5)                   /*!< interrupt/event pending status from line 79 */
#define EXTI_PD3_PD80                 BIT(6)                   /*!< interrupt/event pending status from line 80 */
#define EXTI_PD3_PD81                 BIT(7)                   /*!< interrupt/event pending status from line 81 */
#define EXTI_PD3_PD82                 BIT(8)                   /*!< interrupt/event pending status from line 82 */
#define EXTI_PD3_PD83                 BIT(9)                   /*!< interrupt/event pending status from line 83 */
#define EXTI_PD3_PD84                 BIT(10)                  /*!< interrupt/event pending status from line 84 */
#define EXTI_PD3_PD85                 BIT(11)                  /*!< interrupt/event pending status from line 85 */
#define EXTI_PD3_PD86                 BIT(12)                  /*!< interrupt/event pending status from line 86 */
#define EXTI_PD3_PD87                 BIT(13)                  /*!< interrupt/event pending status from line 87 */
#define EXTI_PD3_PD88                 BIT(14)                  /*!< interrupt/event pending status from line 88 */
#define EXTI_PD3_PD89                 BIT(15)                  /*!< interrupt/event pending status from line 89 */
#define EXTI_PD3_PD90                 BIT(16)                  /*!< interrupt/event pending status from line 90 */
#define EXTI_PD3_PD91                 BIT(17)                  /*!< interrupt/event pending status from line 91 */
#define EXTI_PD3_PD92                 BIT(18)                  /*!< interrupt/event pending status from line 92 */
#define EXTI_PD3_PD93                 BIT(19)                  /*!< interrupt/event pending status from line 93 */
#define EXTI_PD3_PD94                 BIT(20)                  /*!< interrupt/event pending status from line 94 */
#define EXTI_PD3_PD95                 BIT(21)                  /*!< interrupt/event pending status from line 95 */
#define EXTI_PD3_PD96                 BIT(22)                  /*!< interrupt/event pending status from line 96 */
#define EXTI_PD3_PD97                 BIT(23)                  /*!< interrupt/event pending status from line 97 */
#define EXTI_PD3_PD98                 BIT(24)                  /*!< interrupt/event pending status from line 98 */
#define EXTI_PD3_PD99                 BIT(25)                  /*!< interrupt/event pending status from line 99 */
#define EXTI_PD3_PD100                BIT(26)                  /*!< interrupt/event pending status from line 100 */
#define EXTI_PD3_PD101                BIT(27)                  /*!< interrupt/event pending status from line 101 */

/* constants definitions */
/* define the EXTI bit position and its register group index offset */
#define EXTI_GROUPIDX_BIT(groupidx, bit)        (((uint32_t)(groupidx) << 8) | (uint32_t)(bit))                
#define EXTI_REG_VAL(linex)                     (EXTI + ((uint32_t)(linex) >> 8))              
#define EXTI_BIT_POS(linex)                     BIT((linex) & 0x1FU)                                          

/* define the EXTI register groups*/
#define EXTI_GROUP0_OFFSET                      (0x00U)                                             /*!< the index offset of EXTI group0 */
#define EXTI_GROUP1_OFFSET                      (0x18U)                                             /*!< the index offset of EXTI group1 */
#define EXTI_GROUP2_OFFSET                      (0x30U)                                             /*!< the index offset of EXTI group2 */
#define EXTI_GROUP3_OFFSET                      (0x48U)                                             /*!< the index offset of EXTI group3 */

/* define the registers in the group*/
#define EXTI_INTEN(exti_group)                   REG32((uint32_t)(exti_group) + 0x00000000U)        /*!< the index offset of register INTEN in the register group */
#define EXTI_EVEN(exti_group)                    REG32((uint32_t)(exti_group) + 0x00000004U)        /*!< the index offset of register EVEN in the register group */
#define EXTI_RTEN(exti_group)                    REG32((uint32_t)(exti_group) + 0x00000008U)        /*!< the index offset of register RTEN in the register group */
#define EXTI_FTEN(exti_group)                    REG32((uint32_t)(exti_group) + 0x0000000CU)        /*!< the index offset of register FTEN in the register group */
#define EXTI_SWIEV(exti_group)                   REG32((uint32_t)(exti_group) + 0x00000010U)        /*!< the index offset of register SWIEV in the register group */
#define EXTI_PD(exti_group)                      REG32((uint32_t)(exti_group) + 0x00000014U)        /*!< the index offset of register PD in the register group */

/* EXTI line number */
typedef enum
{
    EXTI_0      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 0U),    /*!< EXTI line 0 */
    EXTI_1      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 1U),    /*!< EXTI line 1 */
    EXTI_2      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 2U),    /*!< EXTI line 2 */
    EXTI_3      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 3U),    /*!< EXTI line 3 */
    EXTI_4      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 4U),    /*!< EXTI line 4 */
    EXTI_5      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 5U),    /*!< EXTI line 5 */
    EXTI_6      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 6U),    /*!< EXTI line 6 */
    EXTI_7      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 7U),    /*!< EXTI line 7 */
    EXTI_8      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 8U),    /*!< EXTI line 8 */
    EXTI_9      = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 9U),    /*!< EXTI line 9 */
    EXTI_10     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 10U),   /*!< EXTI line 10 */
    EXTI_11     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 11U),   /*!< EXTI line 11 */
    EXTI_12     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 12U),   /*!< EXTI line 12 */
    EXTI_13     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 13U),   /*!< EXTI line 13 */
    EXTI_14     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 14U),   /*!< EXTI line 14 */
    EXTI_15     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 15U),   /*!< EXTI line 15 */
    EXTI_16     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 16U),   /*!< EXTI line 16 */
    EXTI_17     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 17U),   /*!< EXTI line 17 */
    EXTI_18     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 18U),   /*!< EXTI line 18 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    EXTI_19     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 19U),   /*!< EXTI line 19 */
    EXTI_20     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 20U),   /*!< EXTI line 20 */
    EXTI_21     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 21U),   /*!< EXTI line 21 */
    EXTI_22     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 22U),   /*!< EXTI line 22 */
    EXTI_23     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 23U),   /*!< EXTI line 23 */
    EXTI_24     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 24U),   /*!< EXTI line 24 */
    EXTI_25     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 25U),   /*!< EXTI line 25 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    EXTI_26     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 26U),   /*!< EXTI line 26 */
    EXTI_27     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 27U),   /*!< EXTI line 27 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    EXTI_28     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 28U),   /*!< EXTI line 28 */
    EXTI_29     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 29U),   /*!< EXTI line 29 */
    EXTI_30     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 30U),   /*!< EXTI line 30 */
    EXTI_31     = EXTI_GROUPIDX_BIT(EXTI_GROUP0_OFFSET, 31U),   /*!< EXTI line 31 */
    EXTI_32     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 0U),    /*!< EXTI line 32 */
    EXTI_33     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 1U),    /*!< EXTI line 33 */
    EXTI_34     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 2U),    /*!< EXTI line 34 */
    EXTI_35     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 3U),    /*!< EXTI line 35 */
    EXTI_36     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 4U),    /*!< EXTI line 36 */
    EXTI_37     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 5U),    /*!< EXTI line 37 */
    EXTI_38     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 6U),    /*!< EXTI line 38 */
    EXTI_39     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 7U),    /*!< EXTI line 39 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    EXTI_40     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 8U),    /*!< EXTI line 40 */
    EXTI_41     = EXTI_GROUPIDX_BIT(EXTI_GROUP1_OFFSET, 9U),    /*!< EXTI line 41 */
    EXTI_42     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 0U),    /*!< EXTI line 42 */
    EXTI_43     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 1U),    /*!< EXTI line 43 */
    EXTI_44     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 2U),    /*!< EXTI line 44 */
    EXTI_45     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 3U),    /*!< EXTI line 45 */
    EXTI_46     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 4U),    /*!< EXTI line 46 */
    EXTI_47     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 5U),    /*!< EXTI line 47 */
    EXTI_48     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 6U),    /*!< EXTI line 48 */
    EXTI_49     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 7U),    /*!< EXTI line 49 */
    EXTI_50     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 8U),    /*!< EXTI line 50 */
    EXTI_51     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 9U),    /*!< EXTI line 51 */
    EXTI_52     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 10U),   /*!< EXTI line 52 */
    EXTI_53     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 11U),   /*!< EXTI line 53 */
    EXTI_54     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 12U),   /*!< EXTI line 54 */
    EXTI_55     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 13U),   /*!< EXTI line 55 */
    EXTI_56     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 14U),   /*!< EXTI line 56 */
    EXTI_57     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 15U),   /*!< EXTI line 57 */
    EXTI_58     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 16U),   /*!< EXTI line 58 */
    EXTI_59     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 17U),   /*!< EXTI line 59 */
    EXTI_60     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 18U),   /*!< EXTI line 60 */
    EXTI_61     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 19U),   /*!< EXTI line 61 */
    EXTI_62     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 20U),   /*!< EXTI line 62 */
    EXTI_63     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 21U),   /*!< EXTI line 63 */
    EXTI_64     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 22U),   /*!< EXTI line 64 */
    EXTI_65     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 23U),   /*!< EXTI line 65 */
    EXTI_66     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 24U),   /*!< EXTI line 66 */
    EXTI_67     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 25U),   /*!< EXTI line 67 */
    EXTI_68     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 26U),   /*!< EXTI line 68 */
    EXTI_69     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 27U),   /*!< EXTI line 69 */
    EXTI_70     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 28U),   /*!< EXTI line 70 */
    EXTI_71     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 29U),   /*!< EXTI line 71 */
    EXTI_72     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 30U),   /*!< EXTI line 72 */
    EXTI_73     = EXTI_GROUPIDX_BIT(EXTI_GROUP2_OFFSET, 31U),   /*!< EXTI line 73 */
    EXTI_74     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 0U),    /*!< EXTI line 74 */
    EXTI_75     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 1U),    /*!< EXTI line 75 */
    EXTI_76     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 2U),    /*!< EXTI line 76 */
    EXTI_77     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 3U),    /*!< EXTI line 77 */
    EXTI_78     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 4U),    /*!< EXTI line 78 */
    EXTI_79     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 5U),    /*!< EXTI line 79 */
    EXTI_80     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 6U),    /*!< EXTI line 80 */
    EXTI_81     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 7U),    /*!< EXTI line 81 */
    EXTI_82     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 8U),    /*!< EXTI line 82 */
    EXTI_83     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 9U),    /*!< EXTI line 83 */
    EXTI_84     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 10U),   /*!< EXTI line 84 */
    EXTI_85     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 11U),   /*!< EXTI line 85 */
    EXTI_86     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 12U),   /*!< EXTI line 86 */
    EXTI_87     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 13U),   /*!< EXTI line 87 */
    EXTI_88     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 14U),   /*!< EXTI line 88 */
    EXTI_89     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 15U),   /*!< EXTI line 89 */
    EXTI_90     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 16U),   /*!< EXTI line 90 */
    EXTI_91     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 17U),   /*!< EXTI line 91 */
    EXTI_92     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 18U),   /*!< EXTI line 92 */
    EXTI_93     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 19U),   /*!< EXTI line 93 */
    EXTI_94     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 20U),   /*!< EXTI line 94 */
    EXTI_95     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 21U),   /*!< EXTI line 95 */
    EXTI_96     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 22U),   /*!< EXTI line 96 */
    EXTI_97     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 23U),   /*!< EXTI line 97 */
    EXTI_98     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 24U),   /*!< EXTI line 98 */
    EXTI_99     = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 25U),   /*!< EXTI line 99 */
    EXTI_100    = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 26U),   /*!< EXTI line 100 */
    EXTI_101    = EXTI_GROUPIDX_BIT(EXTI_GROUP3_OFFSET, 27U)    /*!< EXTI line 101 */
} exti_line_enum;

/* external interrupt and event */
typedef enum
{
    EXTI_INTERRUPT   = 0U,                                      /*!< EXTI interrupt mode */
    EXTI_EVENT                                                  /*!< EXTI event mode */
} exti_mode_enum;
 
/* interrupt trigger mode */
typedef enum
{
    EXTI_TRIG_RISING = 0U,                                      /*!< EXTI rising edge trigger */
    EXTI_TRIG_FALLING,                                          /*!< EXTI falling edge trigger */
    EXTI_TRIG_BOTH,                                             /*!< EXTI rising and falling edge trigger */
    EXTI_TRIG_NONE                                              /*!< without rising edge or falling edge trigger */
} exti_trig_type_enum;

/* function declarations */
/* initialization, EXTI lines configuration functions */
/* deinitialize the EXTI */
void exti_deinit(void);
/* initialize the EXTI line x */
void exti_init(exti_line_enum linex, exti_mode_enum mode, exti_trig_type_enum trig_type);
/* enable the interrupts from EXTI line x */
void exti_interrupt_enable(exti_line_enum linex);
/* disable the interrupts from EXTI line x */
void exti_interrupt_disable(exti_line_enum linex);
/* enable the events from EXTI line x */
void exti_event_enable(exti_line_enum linex);
/* disable the events from EXTI line x */
void exti_event_disable(exti_line_enum linex);
/* enable the software interrupt event from EXTI line x */
void exti_software_interrupt_enable(exti_line_enum linex);
/* disable the software interrupt event from EXTI line x */
void exti_software_interrupt_disable(exti_line_enum linex);

/* interrupt & flag functions */
/* get EXTI line x pending flag */
FlagStatus exti_flag_get(exti_line_enum linex);
/* clear EXTI line x pending flag */
void exti_flag_clear(exti_line_enum linex);
/* get EXTI line x interrupt pending flag */
FlagStatus exti_interrupt_flag_get(exti_line_enum linex);
/* clear EXTI line x interrupt pending flag */
void exti_interrupt_flag_clear(exti_line_enum linex);

#endif /* GD32A7XX_EXTI_H */
