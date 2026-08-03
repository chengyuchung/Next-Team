/*!
   \file    gd32a7xx_jdc.h
   \brief   definitions for the JDC

    \version 2025-08-06, V0.1.0, firmware for GD32A7xx
*/

/*
    Copyright (c) 2025, GigaDevice Semiconductor Inc.

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

#ifndef GD32A7XX_JDC_H
#define GD32A7XX_JDC_H

#include "gd32a7xx.h"

/* IMICU definitions */
#define JDC                                              JDC_BASE

/* registers definitions */
#define JDC_INTEN                                        REG32(JDC + 0x00000000U)           /*! JDC interrupt enable register base address */
#define JDC_STAT                                         REG32(JDC + 0x00000004U)           /*! JDC status register */
#define JDC_JOUT_APB_DATA                                REG32(JDC + 0x00000008U)           /*! JDC JOUT APB data register */
#define JDC_JIN_APB_DATA                                 REG32(JDC + 0x0000000CU)           /*! JDC JIN APB data register */

/* bits definitions */
/* JDC_INTEN */
#define JDC_INTEN_JOUTIE                                 BIT(0)                             /*! JOUT interrupt enable */
#define JDC_INTEN_JINIE                                  BIT(16)                            /*! JIN interrupt enable */

/* JDC_STAT */
#define JDC_STAT_JOUTIF                                  BIT(0)                             /*! the JOUTSET bit is cleared by tool reading JDC_JOUT_DATA register interrupt flag */
#define JDC_STAT_JOUTSET                                 BIT(2)                             /*! JOUT set */
#define JDC_STAT_JINIF                                   BIT(16)                            /*! The new data is written to the JDC_JIN_APB_DATA register interrupt flag */
#define JDC_STAT_JINSET                                  BIT(18)                            /*! JIN set */

/* constants definitions */
#define JDC_INT_JOUT                                     JDC_INTEN_JOUTIE                   /*! JOUT interrupt enable */
#define JDC_INT_JIN                                      JDC_INTEN_JINIE                    /*! JIN interrupt enable */

#define JDC_INT_FLAG_JOUT                                JDC_STAT_JOUTIF                    /*! the JOUTSET bit is cleared by tool reading JDC_JOUT_DATA register interrupt flag */
#define JDC_RDY_FLAG_JOUT                                JDC_STAT_JOUTSET                   /*! JOUT set */
#define JDC_INT_FLAG_JIN                                 JDC_STAT_JINIF                     /*! the new data is written to the JDC_JIN_APB_DATA register interrupt flag */
#define JDC_RDY_FLAG_JIN                                 JDC_STAT_JINSET                    /*! JIN set */

/* check JDC flag */
#define NOT_JDC_FLAG(flag)                   (((flag) != JDC_INT_FLAG_JOUT) && ((flag) != JDC_RDY_FLAG_JOUT) && \
                                              ((flag) != JDC_INT_FLAG_JIN)  && ((flag) != JDC_RDY_FLAG_JIN))

/* check JDC interrupt */
#define NOT_JDC_INT(interrupt)               (((interrupt) != JDC_INT_JOUT) && ((interrupt) != JDC_INT_JIN))

/* check JDC interrupt flag */
#define NOT_JDC_INT_FLAG(int_flag)           (((int_flag) != JDC_INT_FLAG_JOUT) && ((int_flag) != JDC_INT_FLAG_JIN))

/* function declarations */
/* jdc write output data */
void jdc_jout_write(uint32_t data);
/* jdc read input data */
uint32_t jdc_jin_read(void);
/* get jdc flag */
FlagStatus jdc_flag_get(uint32_t flag);
/* enable jdc interrupt */
void jdc_interrupt_enable(uint32_t interrupt);
/* disable jdc interrupt */
void jdc_interrupt_disable(uint32_t interrupt);
/* get jdc interrupt flag */
FlagStatus jdc_interrupt_flag_get(uint32_t int_flag);
/* clear jdc interrupt flag */
void jdc_interrupt_flag_clear(uint32_t int_flag);
#endif /* GD32A7XX_JDC_H */
