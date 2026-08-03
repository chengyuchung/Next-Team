/*!
    \file    gd32a7xx_libopt.h
    \brief   library optional for gd32a7xx

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

#ifndef GD32A7XX_LIBOPT_H
#define GD32A7XX_LIBOPT_H

#include "gd32a7xx_syscfg.h"
#include "gd32a7xx_busim.h"
#include "gd32a7xx_extmpu.h"
#include "gd32a7xx_prpu.h"
#include "gd32a7xx_imicu.h"
#include "gd32a7xx_sram_tcm.h"
#include "gd32a7xx_fmc.h"
#include "gd32a7xx_pmu.h"
#include "gd32a7xx_bkp.h"
#include "gd32a7xx_rcu.h"
#include "gd32a7xx_exti.h"
#include "gd32a7xx_trigsel.h"
#include "gd32a7xx_gpio.h"
#include "gd32a7xx_crc.h"
#include "gd32a7xx_dma.h"
#include "gd32a7xx_dbg.h"
#include "gd32a7xx_adc.h"
#include "gd32a7xx_dac.h"
#include "gd32a7xx_fwdgt.h"
#include "gd32a7xx_wwdgt.h"
#include "gd32a7xx_rtc.h"
#include "gd32a7xx_timer.h"
#include "gd32a7xx_linflexd_uart.h"
#include "gd32a7xx_linflexd_lin.h"
#include "gd32a7xx_i2c.h"
#include "gd32a7xx_spi.h"
#include "gd32a7xx_qspi.h"
#include "gd32a7xx_can.h"
#include "gd32a7xx_cmp.h"
#include "gd32a7xx_misc.h"
#include "gd32a7xx_stcm.h"
#include "gd32a7xx_mtc.h"
#include "gd32a7xx_irm.h"
#include "gd32a7xx_cltcfg.h"
#include "gd32a7xx_fmu.h"
#include "gd32a7xx_jdc.h"
#include "gd32a7xx_gdap.h"
#if defined(GD32A714X) || defined(GD32A72XX) || defined(GD32A74XX)
#include "gd32a7xx_mfcom.h"
#include "gd32a7xx_sent.h"
#include "gd32a7xx_enet.h"
#include "gd32a7xx_hwsem.h"
#include "gd32a7xx_mcmu.h"
#include "gd32a7xx_ioc.h"
#endif /* defined(GD32A714X) || defined(GD32A72XX) || defined(GD32A74XX) */

#endif /* GD32A7XX_LIBOPT_H */
