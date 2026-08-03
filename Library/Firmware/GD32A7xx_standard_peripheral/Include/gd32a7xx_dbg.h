/*!
    \file    gd32a7xx_dbg.h
    \brief   definitions for the DBG

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

#ifndef GD32A7XX_DBG_H
#define GD32A7XX_DBG_H

#include "gd32a7xx.h"

/* DBG definitions */
#define DBG                         DBG_BASE                        /*!< DBG base address */

/* registers definitions */
#define DBG_CTL0                    REG32(DBG + 0x00000000U)        /*!< DBG control register 0 */
#define DBG_CTL1                    REG32(DBG + 0x00000004U)        /*!< DBG control register 1 */
#define DBG_CTL2                    REG32(DBG + 0x00000008U)        /*!< DBG control register 2 */

/* bits definitions */
/* DBG_CTL0 */
#define DBG_CTL0_STB_HOLD           BIT(4)                          /*!< keep debugger connection during standby mode */
#define DBG_CTL0_WWDGT0_HOLD        BIT(5)                          /*!< hold WWDGT0 counter when core is halted */
#define DBG_CTL0_WWDGT1_HOLD        BIT(6)                          /*!< hold WWDGT1 counter when core is halted */
#define DBG_CTL0_MFCOM_HOLD         BIT(15)                         /*!< hold MFCOM counter when core is halted */
#define DBG_CTL0_FWDGT0_HOLD        BIT(18)                         /*!< hold FWDGT0 counter when core is halted */
#define DBG_CTL0_FWDGT1_HOLD        BIT(19)                         /*!< hold FWDGT1 counter when core is halted */

/* DBG_CTL1 */
#define DBG_CTL1_TIMER1_HOLD        BIT(0)                          /*!< hold TIMER1 counter when core is halted */
#define DBG_CTL1_TIMER2_HOLD        BIT(1)                          /*!< hold TIMER2 counter when core is halted */
#define DBG_CTL1_TIMER5_HOLD        BIT(4)                          /*!< hold TIMER5 counter when core is halted */
#define DBG_CTL1_TIMER6_HOLD        BIT(5)                          /*!< hold TIMER6 counter when core is halted */
#define DBG_CTL1_I2C0_HOLD          BIT(21)                         /*!< hold I2C0 smbus timeout when core is halted */
#define DBG_CTL1_I2C1_HOLD          BIT(22)                         /*!< hold I2C1 smbus timeout when core is halted */

/* DBG_CTL3 */
#define DBG_CTL2_TIMER0_HOLD        BIT(0)                          /*!< hold TIMER0 counter when core is halted */
#define DBG_CTL2_TIMER7_HOLD        BIT(1)                          /*!< hold TIMER7 counter when core is halted */
#define DBG_CTL2_TIMER19_HOLD       BIT(24)                         /*!< hold TIMER19 counter when core is halted */
#define DBG_CTL2_TIMER20_HOLD       BIT(25)                         /*!< hold TIMER20 counter when core is halted */
#define DBG_CTL2_TIMER60_HOLD       BIT(26)                         /*!< hold TIMER60 counter when core is halted */
#define DBG_CTL2_TIMER61_HOLD       BIT(27)                         /*!< hold TIMER61 counter when core is halted */
#define DBG_CTL2_TIMER62_HOLD       BIT(28)                         /*!< hold TIMER62 counter when core is halted */
#define DBG_CTL2_TIMER63_HOLD       BIT(29)                         /*!< hold TIMER63 counter when core is halted */

/* constants definitions */
/* low power mode with debug*/
#define DBG_LOW_POWER_STANDBY       DBG_CTL0_STB_HOLD               /*!< keep debugger connection during standby mode */

/* define the peripheral debug hold bit position and its register index offset */
#define DBG_REGIDX_BIT(regidx, bitpos)      (((regidx) << 6) | (bitpos))
#define DBG_REG_VAL(periph)                 (REG32(DBG + ((uint32_t)(periph) >> 6)))
#define DBG_BIT_POS(val)                    ((uint32_t)(val) & 0x1FU)

/* register index */
#define DBG_IDX_CTL0             ((uint32_t)0x00000000U)
#define DBG_IDX_CTL1             ((uint32_t)0x00000004U)
#define DBG_IDX_CTL2             ((uint32_t)0x00000008U)

typedef enum
{
    DBG_WWDGT0_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL0, 5U),                   /*!< hold WWDGT0 counter when core is halted */
#ifndef GD32A711X_A712X
    DBG_WWDGT1_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL0, 6U),                   /*!< hold WWDGT1 counter when core is halted */
    DBG_MFCOM_HOLD             = DBG_REGIDX_BIT(DBG_IDX_CTL0, 15U),                  /*!< hold MFCOM counter when core is halted */
#endif
    DBG_FWDGT0_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL0, 18U),                  /*!< hold FWDGT0 counter when core is halted */
#ifndef GD32A711X_A712X
    DBG_FWDGT1_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL0, 19U),                  /*!< hold FWDGT1 counter when core is halted */
#endif
    DBG_TIMER1_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL1, 0U),                   /*!< hold TIMER1 counter when core is halted */
    DBG_TIMER2_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL1, 1U),                   /*!< hold TIMER2 counter when core is halted */
    DBG_TIMER5_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL1, 4U),                   /*!< hold TIMER5 counter when core is halted */
    DBG_TIMER6_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL1, 5U),                   /*!< hold TIMER6 counter when core is halted */
    DBG_I2C0_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL1, 21U),                  /*!< hold I2C0 smbus timeout when core is halted */
    DBG_I2C1_HOLD              = DBG_REGIDX_BIT(DBG_IDX_CTL1, 22U),                  /*!< hold I2C1 smbus timeout when core is halted */
    DBG_TIMER0_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL2, 0U),                   /*!< hold TIMER0 counter when core is halted */
    DBG_TIMER7_HOLD            = DBG_REGIDX_BIT(DBG_IDX_CTL2, 1U),                   /*!< hold TIMER7 counter when core is halted */
    DBG_TIMER19_HOLD           = DBG_REGIDX_BIT(DBG_IDX_CTL2, 24U),                  /*!< hold TIMER19 counter when core is halted */
    DBG_TIMER20_HOLD           = DBG_REGIDX_BIT(DBG_IDX_CTL2, 25U),                  /*!< hold TIMER20 counter when core is halted */
    DBG_TIMER60_HOLD           = DBG_REGIDX_BIT(DBG_IDX_CTL2, 26U),                  /*!< hold TIMER60 counter when core is halted */
    DBG_TIMER61_HOLD           = DBG_REGIDX_BIT(DBG_IDX_CTL2, 27U),                  /*!< hold TIMER61 counter when core is halted */
    DBG_TIMER62_HOLD           = DBG_REGIDX_BIT(DBG_IDX_CTL2, 28U),                  /*!< hold TIMER62 counter when core is halted */
    DBG_TIMER63_HOLD           = DBG_REGIDX_BIT(DBG_IDX_CTL2, 29U),                  /*!< hold TIMER63 counter when core is halted */  
}dbg_periph_enum;

/* function declarations */
/* deinitialize the DBG */
void dbg_deinit(void);
/* enable low power behavior when the core is in debug mode */
void dbg_low_power_enable(void);
/* disable low power behavior when the core is in debug mode */
void dbg_low_power_disable(void);
/* enable peripheral behavior when the core is in debug mode */
void dbg_periph_enable(dbg_periph_enum dbg_periph);
/* disable peripheral behavior when the core is in debug mode */
void dbg_periph_disable(dbg_periph_enum dbg_periph);
    
#endif /* GD32A7XX_DBG_H */
