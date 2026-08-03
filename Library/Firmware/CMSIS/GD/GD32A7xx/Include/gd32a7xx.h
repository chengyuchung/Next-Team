/*!
    \file    gd32a7xx.h
    \brief   general definitions for GD32A7xx

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

#ifndef GD32A7XX_H
#define GD32A7XX_H

#ifdef __cplusplus
 extern "C" {
#endif 

#if !defined (GD32A711X_A712X) && !defined (GD32A714X) && !defined (GD32A72XX) && !defined (GD32A74XX)
#error "Please select the target GD32A7XX device used in your application (in gd32a7xx.h file)"
#endif /* undefine GD32A7XX tip */

/* define value of high speed crystal oscillator (HXTAL) in Hz */
#if !defined  HXTAL_VALUE
#define HXTAL_VALUE    ((uint32_t)25000000) /*!< value of the external oscillator in Hz */
#endif /* high speed crystal oscillator value */

/* define startup timeout value of high speed crystal oscillator (HXTAL) */
#if !defined  (HXTAL_STARTUP_TIMEOUT)
#define HXTAL_STARTUP_TIMEOUT   ((uint16_t)0x0FFFF)
#endif /* high speed crystal oscillator startup timeout */

/* define value of internal 48MHz RC oscillator (IRC48M) in Hz */
#if !defined  (IRC48M_VALUE) 
#define IRC48M_VALUE  ((uint32_t)48000000)
#endif /* internal 48MHz RC oscillator value */

/* define startup timeout value of internal 48MHz RC oscillator (IRC48M) */
#if !defined  (IRC48M_STARTUP_TIMEOUT)
#define IRC48M_STARTUP_TIMEOUT   ((uint16_t)0x0500)
#endif /* internal 48MHz RC oscillator startup timeout */

/* define value of internal 40KHz RC oscillator(IRC40K) in Hz */
#if !defined  (IRC40K_VALUE) 
#define IRC40K_VALUE  ((uint32_t)40000)
#endif /* internal 40KHz RC oscillator value */

/* define value of low speed crystal oscillator (LXTAL)in Hz */
#if !defined  (LXTAL_VALUE) 
#define LXTAL_VALUE  ((uint32_t)32768)
#endif /* low speed crystal oscillator value */

/* GD32A7xx firmware library version number */
#define GD32A7XX_STDPERIPH_VERSION_MAIN   (0x00) /*!< [31:24] main version */
#define GD32A7XX_STDPERIPH_VERSION_SUB1   (0x01) /*!< [23:16] sub1 version */
#define GD32A7XX_STDPERIPH_VERSION_SUB2   (0x00) /*!< [15:8]  sub2 version */
#define GD32A7XX_STDPERIPH_VERSION_RC     (0x00) /*!< [7:0]  release candidate */ 
#define GD32A7XX_STDPERIPH_VERSION        ((GD32A7XX_STDPERIPH_VERSION_MAIN << 24)\
                                            |(GD32A7XX_STDPERIPH_VERSION_SUB1 << 16)\
                                            |(GD32A7XX_STDPERIPH_VERSION_SUB2 << 8)\
                                            |(GD32A7XX_STDPERIPH_VERSION_RC))

/* configuration of the Cortex-M7 processor and core peripherals                                           */
#define __CM7_REV                 0x0102U   /*!< Core revision r1p2                                        */
#define __SAUREGION_PRESENT       0U        /*!< SAU regions are not present                               */
#define __MPU_PRESENT             1U        /*!< MPU is present                                            */
#define __VTOR_PRESENT            1U        /*!< VTOR is present                                           */
#define __NVIC_PRIO_BITS          4U        /*!< Number of Bits used for Priority Levels                   */
#define __Vendor_SysTickConfig    0U        /*!< Set to 1 if different SysTick Config is used              */
#define __FPU_PRESENT             1U        /*!< FPU present                                               */
#define __DSP_PRESENT             1U        /*!< DSP present                                               */
#define __ICACHE_PRESENT          1U        /*!< CM7 instruction cache present                             */
#define __DCACHE_PRESENT          1U        /*!< CM7 data cache present                                    */

/* define interrupt number */
typedef enum IRQn
{
    /* Cortex-M7 processor exceptions numbers */
    NonMaskableInt_IRQn         = -14,      /*!< non mask-able interrupt                                        */
    HardFault_IRQn              = -13,      /*!< hard-fault interrupt                                           */
    MemoryManagement_IRQn       = -12,      /*!< Cortex-M7 memory management interrupt                          */
    BusFault_IRQn               = -11,      /*!< Cortex-M7 bus fault interrupt                                  */
    UsageFault_IRQn             = -10,      /*!< Cortex-M7 usage fault interrupt                                */
    SVCall_IRQn                 = -5,       /*!< Cortex-M7 sv call interrupt                                    */
    DebugMonitor_IRQn           = -4,       /*!< Cortex-M7 debug monitor interrupt                              */
    PendSV_IRQn                 = -2,       /*!< Cortex-M7 pend sv interrupt                                    */
    SysTick_IRQn                = -1,       /*!< Cortex-M7 system tick interrupt                                */
    /* interrupt numbers */
    WWDGT0_IRQn                 = 0,        /*!< window watchdog 0 interrupt                                    */
    HVD_LVD_IRQn                = 1,        /*!< LVD through EXTI line detect interrupt                         */
    RTC_Alarm_IRQn              = 2,        /*!< RTC Alarm interrupt through EXTI line                          */
    RTC_IRQn                    = 3,        /*!< RTC interrupt                                                  */
    FMC_IRQn                    = 4,        /*!< FMC interrupt                                                  */
    RCU_IRQn                    = 5,        /*!< RCU and CTC interrupt                                          */
    EXTI0_IRQn                  = 6,        /*!< EXTI line 0 interrupts                                         */
    EXTI1_IRQn                  = 7,        /*!< EXTI line 1 interrupts                                         */
    EXTI2_IRQn                  = 8,        /*!< EXTI line 2 interrupts                                         */
    EXTI3_IRQn                  = 9,        /*!< EXTI line 3 interrupts                                         */
    EXTI4_IRQn                  = 10,       /*!< EXTI line 4 interrupts                                         */
    DMA0_Channel0_IRQn          = 11,       /*!< DMA0 channel 0 interrupt                                       */
    DMA0_Channel1_IRQn          = 12,       /*!< DMA0 channel 1 interrupt                                       */
    DMA0_Channel2_IRQn          = 13,       /*!< DMA0 channel 2 interrupt                                       */
    DMA0_Channel3_IRQn          = 14,       /*!< DMA0 channel 3 interrupt                                       */
    DMA0_Channel4_IRQn          = 15,       /*!< DMA0 channel 4 interrupt                                       */
    DMA0_Channel5_IRQn          = 16,       /*!< DMA0 channel 5 interrupt                                       */
    DMA0_Channel6_IRQn          = 17,       /*!< DMA0 channel 6 interrupt                                       */
    ADC0_IRQn                   = 18,       /*!< ADC0_1 interrupts                                              */
    DTM_CAN0_INT0_IRQn          = 19,       /*!< DTM_CAN0 interrupt 0                                           */
    DTM_CAN0_INT1_IRQn          = 20,       /*!< DTM_CAN0 interrupt 1                                           */
#ifdef GD32A711X_A712X
    DTM_CAN0_DMU_IRQn           = 25,       /*!< DTM_CAN0 DMU interrupt                                         */
    TIMER0_BRK_UP_TRG_CMT_IRQn  = 26,       /*!< TIMER0 break, update, trigger and commutation interrupt        */
    TIMER2_IRQn                 = 27,       /*!< TIMER2 interrupt                                               */
    TIMER1_IRQn                 = 28,       /*!< TIMER1 interrupt                                               */
    TIMER19_BRK_UP_TRG_CMT_IRQn = 29,       /*!< TIMER19 break, update, trigger and commutation interrupt       */
    JDC_IRQn                    = 30,       /*!< JDC interrupt to host */
    I2C0_EV_IRQn                = 31,       /*!< I2C0 event interrupt                                           */
    I2C0_ER_IRQn                = 32,       /*!< I2C0 error interrupt                                           */
    I2C1_EV_IRQn                = 33,       /*!< I2C1 event interrupt                                           */
    I2C1_ER_IRQn                = 34,       /*!< I2C1 error interrupt                                           */
    SPI0_IRQn                   = 35,       /*!< SPI0 interrupt                                                 */
    SPI1_IRQn                   = 36,       /*!< SPI1 interrupt                                                 */
    EXTI10_15_IRQn              = 40,       /*!< EXTI line 10 to 15 interrupts                                  */
    EXTI5_9_IRQn                = 41,       /*!< EXTI line 5 to 9 interrupts                                    */
    TAMPER_IRQn                 = 42,       /*!< BKP Tamper interrupt                                           */
    TIMER20_BRK_UP_TRG_CMT_IRQn = 43,       /*!< TIMER20 break, update, trigger and commutation interrupt       */
    EXTI42_101_IRQn             = 44,       /*!< EXTI line 42 to 101 interrupts                                 */
    TIMER7_BRK_UP_TRG_CMT_IRQn  = 45,       /*!< TIMER7 break, update, trigger and commutation interrupt        */
    PLL_LOL_DES_RESET_IRQn      = 46,       /*!< PLL LOL destructive reset interrupt                            */
    DMAMUX_OVR_IRQn             = 47,       /*!< DMAMUX overrun interrupt                                       */
    FPU_WAB_IRQn                = 48,       /*!< CPU FPU interrupt or Write abort interrupt                     */
    CMP0_EXTI_IRQn              = 49,       /*!< CMP0 through EXTI Line detection interrupt                     */
    CMP1_EXTI_IRQn              = 50,       /*!< CMP1 through EXTI Line detection interrupt                     */
    FMU_INIT_IRQn               = 51,       /*!< FMU initializing timeout interrupt                             */
    ADC1_IRQn                   = 52,       /*!< ADC1 interrupt                                                 */
    DAC0_IRQn                   = 54,       /*!< DAC0 global interrupt                                          */
    STCM_IRQn                   = 55,       /*!< STCM illegal triggered during running state                    */
    DMA1_Channel0_IRQn          = 56,       /*!< DMA1 channel 0 interrupt                                       */
    DMA1_Channel1_IRQn          = 57,       /*!< DMA1 channel 1 interrupt                                       */
    DMA1_Channel2_IRQn          = 58,       /*!< DMA1 channel 2 interrupt                                       */
    DMA1_Channel3_IRQn          = 59,       /*!< DMA1 channel 3 interrupt                                       */
    DMA1_Channel4_IRQn          = 60,       /*!< DMA1 channel 4 interrupt                                       */
    DTM_CAN1_INT0_IRQn          = 62,       /*!< DTM_CAN1 interrupt 0                                           */
    DTM_CAN1_INT1_IRQn          = 63,       /*!< DTM_CAN1 interrupt 1                                           */
    DTM_CAN1_DMU_IRQn           = 64,       /*!< DTM_CAN1 DMU interrupt                                         */
    CTI0_IRQn                   = 65,       /*!< CTI Interrupt 0                                                */
    CTI1_IRQn                   = 66,       /*!< CTI Interrupt 1                                                */
    CAN0_ECCERR_IRQn            = 67,       /*!< CAN0 ECC error interrupt                                       */
    CAN1_ECCERR_IRQn            = 68,       /*!< CAN1 ECC error interrupt                                       */
    CAN2_ECCERR_IRQn            = 69,       /*!< CAN2 ECC error interrupt                                       */
    CMP0_IRQn                   = 71,       /*!< CMP0 global interrupt                                          */
    CMP1_IRQn                   = 72,       /*!< CMP1 global interrupt                                          */
    DAC1_IRQn                   = 78,       /*!< DAC1 global interrupt                                          */
    HSM_COM0_IRQn               = 79,       /*!< HSM communication interrupt 0                                  */
    HSM_COM1_IRQn               = 80,       /*!< HSM communication interrupt 1                                  */
    FMU_CAT_IRQn                = 81,       /*!< FMU cation state interrupt request                             */
    RCTL_IRQn                   = 82,       /*!< RCTL interrupt                                                 */
    SPI2_IRQn                   = 84,       /*!< SPI2 global interrupt                                          */
    SPI3_IRQn                   = 85,       /*!< SPI3 global interrupt                                          */
    SPI4_IRQn                   = 86,       /*!< SPI4 global interrupt                                          */
    SPI5_IRQn                   = 87,       /*!< SPI5 global interrupt                                          */
    QSPI_IRQn                   = 90,       /*!< QSPI global interrupt                                          */
    DTM_CAN2_DMU_IRQn           = 94,       /*!< DTM_CAN2_DMU interrupt                                         */
    DTM_CAN3_DMU_IRQn           = 95,       /*!< DTM_CAN3_DMU interrupt                                         */
    DTM_CAN4_DMU_IRQn           = 96,       /*!< DTM_CAN4_DMU interrupt                                         */
    DTM_CAN5_DMU_IRQn           = 97,       /*!< DTM_CAN5_DMU interrupt                                         */
    DTM_CAN6_DMU_IRQn           = 98,       /*!< DTM_CAN6_DMU interrupt                                         */
    DTM_CAN7_DMU_IRQn           = 99,       /*!< DTM_CAN7_DMU interrupt                                         */
    DTM_CAN2_INT0_IRQn          = 100,      /*!< DTM_CAN2 interrupt 0                                           */
    DTM_CAN2_INT1_IRQn          = 101,      /*!< DTM_CAN2 interrupt 1                                           */
    DTM_CAN3_INT0_IRQn          = 102,      /*!< DTM_CAN3 interrupt 0                                           */
    DTM_CAN3_INT1_IRQn          = 103,      /*!< DTM_CAN3 interrupt 1                                           */
    DTM_CAN4_INT0_IRQn          = 104,      /*!< DTM_CAN4 interrupt 0                                           */
    DTM_CAN4_INT1_IRQn          = 105,      /*!< DTM_CAN4 interrupt 1                                           */
    DTM_CAN5_INT0_IRQn          = 106,      /*!< DTM_CAN5 interrupt 0                                           */
    DTM_CAN5_INT1_IRQn          = 107,      /*!< DTM_CAN5 interrupt 1                                           */
    DTM_CAN6_INT0_IRQn          = 108,      /*!< DTM_CAN6 interrupt 0                                           */
    DTM_CAN6_INT1_IRQn          = 109,      /*!< DTM_CAN6 interrupt 1                                           */
    DTM_CAN7_INT0_IRQn          = 110,      /*!< DTM_CAN7 interrupt 0                                           */
    DTM_CAN7_INT1_IRQn          = 111,      /*!< DTM_CAN7 interrupt 1                                           */
    TIMER19_CC0_CC0N_IRQn       = 112,      /*!< TIMER19 capture compare CH0 and MCH0 interrupt                 */
    TIMER19_CC1_CC1N_IRQn       = 113,      /*!< TIMER19 capture compare CH1 and MCH1 interrupt                 */
    TIMER19_CC2_CC2N_IRQn       = 114,      /*!< TIMER19 capture compare CH2 and MCH2 interrupt                 */
    TIMER19_CC3_CC3N_IRQn       = 115,      /*!< TIMER19 capture compare CH3 and MCH3 interrupt                 */
    TIMER20_CC0_CC0N_IRQn       = 116,      /*!< TIMER20 capture compare CH0 and MCH0 interrupt                 */
    TIMER20_CC1_CC1N_IRQn       = 117,      /*!< TIMER20 capture compare CH1 and MCH1 interrupt                 */
    TIMER20_CC2_CC2N_IRQn       = 118,      /*!< TIMER20 capture compare CH2 and MCH2 interrupt                 */
    TIMER20_CC3_CC3N_IRQn       = 119,      /*!< TIMER20 capture compare CH3 and MCH3 interrupt                 */
    TIMER60_CC0_CC0N_IRQn       = 120,      /*!< TIMER60 capture compare CH0 and MCH0 interrupt                 */
    TIMER60_CC1_CC1N_IRQn       = 121,      /*!< TIMER60 capture compare CH1 and MCH1 interrupt                 */
    TIMER60_CC2_CC2N_IRQn       = 122,      /*!< TIMER60 capture compare CH2 and MCH2 interrupt                 */
    TIMER60_CC3_CC3N_IRQn       = 123,      /*!< TIMER60 capture compare CH3 and MCH3 interrupt                 */
    TIMER61_CC0_CC0N_IRQn       = 124,      /*!< TIMER61 capture compare CH0 and MCH0 interrupt                 */
    TIMER61_CC1_CC1N_IRQn       = 125,      /*!< TIMER61 capture compare CH1 and MCH1 interrupt                 */
    TIMER61_CC2_CC2N_IRQn       = 126,      /*!< TIMER61 capture compare CH2 and MCH2 interrupt                 */
    TIMER61_CC3_CC3N_IRQn       = 127,      /*!< TIMER61 capture compare CH3 and MCH3 interrupt                 */
    TIMER62_CC0_CC0N_IRQn       = 128,      /*!< TIMER62 capture compare CH0 and MCH0 interrupt                 */
    TIMER62_CC1_CC1N_IRQn       = 129,      /*!< TIMER62 capture compare CH1 and MCH1 interrupt                 */
    TIMER62_CC2_CC2N_IRQn       = 130,      /*!< TIMER62 capture compare CH2 and MCH2 interrupt                 */
    TIMER62_CC3_CC3N_IRQn       = 131,      /*!< TIMER62 capture compare CH3 and MCH3 interrupt                 */
    TIMER63_CC0_CC0N_IRQn       = 132,      /*!< TIMER64 capture compare CH0 and MCH0 interrupt                 */
    TIMER63_CC1_CC1N_IRQn       = 133,      /*!< TIMER64 capture compare CH1 and MCH1 interrupt                 */
    TIMER63_CC2_CC2N_IRQn       = 134,      /*!< TIMER64 capture compare CH2 and MCH2 interrupt                 */
    TIMER63_CC3_CC3N_IRQn       = 135,      /*!< TIMER64 capture compare CH3 and MCH3 interrupt                 */
    DMA0_Channel7_IRQn          = 136,      /*!< DMA0 Channel7 global interrupt                                 */
    DMA1_Channel5_IRQn          = 145,      /*!< DMA1 Channel5 global interrupt                                 */
    DMA1_Channel6_IRQn          = 146,      /*!< DMA1 Channel6 global interrupt                                 */
    DMA1_Channel7_IRQn          = 147,      /*!< DMA1 Channel7 global interrupt                                 */
    LINFlexD0_IRQn              = 162,      /*!< LINFlexD0 interrupt                                            */
    LINFlexD1_IRQn              = 163,      /*!< LINFlexD1 interrupt                                            */
    LINFlexD2_IRQn              = 164,      /*!< LINFlexD2 interrupt                                            */
    LINFlexD3_IRQn              = 165,      /*!< LINFlexD3 interrupt                                            */
    LINFlexD4_IRQn              = 166,      /*!< LINFlexD4 interrupt                                            */
    LINFlexD5_IRQn              = 167,      /*!< LINFlexD5 interrupt                                            */
    TIMER0_CC0_CC0N_IRQn        = 174,      /*!< TIMER0 Capture Compare CH0 and MCH0 interrupt                  */
    TIMER0_CC1_CC1N_IRQn        = 175,      /*!< TIMER0 Capture Compare CH1 and MCH1 interrupt                  */
    TIMER0_CC2_CC2N_IRQn        = 176,      /*!< TIMER0 Capture Compare CH2 and MCH3 interrupt                  */
    TIMER0_CC3_CC3N_IRQn        = 177,      /*!< TIMER0 Capture Compare CH4 and MCH4 interrupt                  */
    TIMER7_CC0_CC0N_IRQn        = 178,      /*!< TIMER7 Capture Compare CH0 and MCH0 interrupt                  */
    TIMER7_CC1_CC1N_IRQn        = 179,      /*!< TIMER7 Capture Compare CH1 and MCH1 interrupt                  */
    TIMER7_CC2_CC2N_IRQn        = 180,      /*!< TIMER7 Capture Compare CH2 and MCH3 interrupt                  */
    TIMER7_CC3_CC3N_IRQn        = 181,      /*!< TIMER7 Capture Compare CH4 and MCH4 interrupt                  */
    TIMER1_CC0_IRQn             = 182,      /*!< TIMER1 Capture Compare CH0 and MCH0 interrupt                  */
    TIMER1_CC1_IRQn             = 183,      /*!< TIMER1 Capture Compare CH1 and MCH1 interrupt                  */
    TIMER1_CC2_IRQn             = 184,      /*!< TIMER1 Capture Compare CH2 and MCH3 interrupt                  */
    TIMER1_CC3_IRQn             = 185,      /*!< TIMER1 Capture Compare CH4 and MCH4 interrupt                  */
    TIMER2_CC0_IRQn             = 186,      /*!< TIMER2 Capture Compare CH0 and MCH0 interrupt                  */
    TIMER2_CC1_IRQn             = 187,      /*!< TIMER2 Capture Compare CH1 and MCH1 interrupt                  */
    TIMER2_CC2_IRQn             = 188,      /*!< TIMER2 Capture Compare CH2 and MCH3 interrupt                  */
    TIMER2_CC3_IRQn             = 189,      /*!< TIMER2 Capture Compare CH4 and MCH4 interrupt                  */
    FWDGT_IRQn                  = 190,      /*!< FWDGT reset interrupt through EXTI Line detection interrupt    */
    RCU_CK_FAIL_IRQn            = 196,      /*!< RCU clock fail interrupt                                       */
    TIMER60_BRK_UP_TRG_CMT_IRQn = 210,      /*!< TIMER60 Break, update, trigger and commutation, dec interrupt  */
    TIMER61_BRK_UP_TRG_CMT_IRQn = 211,      /*!< TIMER61 Break, update, trigger and commutation, dec interrupt  */
    TIMER62_BRK_UP_TRG_CMT_IRQn = 212,      /*!< TIMER62 Break, update, trigger and commutation, dec interrupt  */
    TIMER63_BRK_UP_TRG_CMT_IRQn = 213,      /*!< TIMER63 Break, update, trigger and commutation, dec interrupt  */
    TIMER5_CH0_UP_IRQn          = 214,      /*!< TIMER5 CH0 update interrupt                                    */
    TIMER5_CH1_UP_IRQn          = 215,      /*!< TIMER5 CH1 update interrupt                                    */
    TIMER5_CH2_UP_IRQn          = 216,      /*!< TIMER5 CH2 update interrupt                                    */
    TIMER5_CH3_UP_IRQn          = 217,      /*!< TIMER5 CH3 update interrupt                                    */
    TIMER6_CH0_UP_IRQn          = 218,      /*!< TIMER6 CH0 update interrupt                                    */
    TIMER6_CH1_UP_IRQn          = 219,      /*!< TIMER6 CH1 update interrupt                                    */
    TIMER6_CH2_UP_IRQn          = 220,      /*!< TIMER6 CH2 update interrupt                                    */
    TIMER6_CH3_UP_IRQn          = 221,      /*!< TIMER6 CH3 update interrupt                                    */
#endif /* GD32A711X_A712X */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    CPU_INT0_IRQn               = 21,       /* Interrupt 0 between CM7_0 and CM7_1                              */
    CPU_INT1_IRQn               = 22,       /* Interrupt 1 between CM7_0 and CM7_1                              */
    CPU_INT2_IRQn               = 23,       /* Interrupt 2 between CM7_0 and CM7_1                              */
    CPU_INT3_IRQn               = 24,       /* Interrupt 3 between CM7_0 and CM7_1                              */
    CAN0_WKUP_IRQn              = 25,       /*!< CAN0 wakeup through EXTI Line detection interrupt              */
    TIMER0_BRK_UP_TRG_CMT_IRQn  = 26,       /*!< TIMER0 break, update, trigger and commutation interrupt        */
    TIMER2_IRQn                 = 27,       /*!< TIMER2 interrupt                                               */
    TIMER1_IRQn                 = 28,       /*!< TIMER1 interrupt                                               */
    TIMER19_BRK_UP_TRG_CMT_IRQn = 29,       /*!< TIMER19 break, update, trigger and commutation interrupt       */
    JDC_IRQn                    = 30,       /*!< JDC interrupt to host                                         */
    I2C0_EV_IRQn                = 31,       /*!< I2C0 event interrupt                                           */
    I2C0_ER_IRQn                = 32,       /*!< I2C0 error interrupt                                           */
    I2C1_EV_IRQn                = 33,       /*!< I2C1 event interrupt                                           */
    I2C1_ER_IRQn                = 34,       /*!< I2C1 error interrupt                                           */
    SPI0_IRQn                   = 35,       /*!< SPI0 interrupt                                                 */
    SPI1_IRQn                   = 36,       /*!< SPI1 interrupt                                                 */
    USART0_IRQn                 = 37,       /*!< USART0 interrupt                                               */
    USART1_IRQn                 = 38,       /*!< USART1 interrupt                                               */
    USART2_IRQn                 = 39,       /*!< USART2 interrupt                                               */
    EXTI10_15_IRQn              = 40,       /*!< EXTI line 10 to 15 interrupts                                  */
    EXTI5_9_IRQn                = 41,       /*!< EXTI line 5 to 9 interrupts                                    */
    TAMPER_IRQn                 = 42,       /*!< BKP Tamper interrupt                                           */
    TIMER20_BRK_UP_TRG_CMT_IRQn = 43,       /*!< TIMER20 break, update, trigger and commutation interrupt       */
    EXTI42_101_IRQn             = 44,       /*!< EXTI line 42 to 101 interrupts                                 */
    TIMER7_BRK_UP_TRG_CMT_IRQn  = 45,       /*!< TIMER7 break, update, trigger and commutation interrupt        */
    PLL_LOL_DES_RESET_IRQn      = 46,       /*!< PLL LOL system reset interrupt                                 */
    DMAMUX_OVR_IRQn             = 47,       /*!< DMAMUX overrun interrupt                                       */
    FPU_WAB_IRQn                = 48,       /*!< CPU FPU interrupt or Write abort interrupt                     */
    CMP0_EXTI_IRQn              = 49,       /*!< CMP0 through EXTI Line detection interrupt                     */
    CMP1_EXTI_IRQn              = 50,       /*!< CMP1 through EXTI Line detection interrupt                     */
    FMU_INIT_IRQn               = 51,       /*!< FMU initializing timeout interrupt                             */
    ADC1_IRQn                   = 52,       /*!< ADC1 interrupt                                                 */
    ADC2_IRQn                   = 53,       /*!< ADC2 interrupt                                                 */
    DAC0_IRQn                   = 54,       /*!< DAC0 global interrupt                                          */
    STCM_IRQn                   = 55,       /*!< STCM illegal triggered during running state                    */
    DMA1_Channel0_IRQn          = 56,       /*!< DMA1 channel 0 interrupt                                       */
    DMA1_Channel1_IRQn          = 57,       /*!< DMA1 channel 1 interrupt                                       */
    DMA1_Channel2_IRQn          = 58,       /*!< DMA1 channel 2 interrupt                                       */
    DMA1_Channel3_IRQn          = 59,       /*!< DMA1 channel 3 interrupt                                       */
    DMA1_Channel4_IRQn          = 60,       /*!< DMA1 channel 4 interrupt                                       */
    WWDGT1_IRQn                 = 61,       /*!< WWDGT1 interrupt                                               */
    CAN1_WKUP_IRQn              = 62,       /*!< CAN1 wakeup through EXTI Line detection interrupt              */
    CAN1_Message_IRQn           = 63,       /*!< CAN1 message buffer interrupt                                  */
    CAN1_IRQn                   = 64,       /*!< CAN1 interrupt                                                 */
    CTI0_IRQn                   = 65,       /*!< CTI Interrupt 0                                                */
    CTI1_IRQn                   = 66,       /*!< CTI Interrupt 1                                                */
    CAN0_ECCERR_IRQn            = 67,       /*!< CAN0 ECC error interrupt                                       */
    CAN1_ECCERR_IRQn            = 68,       /*!< CAN1 ECC error interrupt                                       */
    CAN2_ECCERR_IRQn            = 69,       /*!< CAN2 ECC error interrupt                                       */
    MFCOM_IRQn                  = 70,       /*!< MFCOM interrupt                                                */
    CMP0_IRQn                   = 71,       /*!< CMP0 global interrupt                                          */
    CMP1_IRQn                   = 72,       /*!< CMP1 global interrupt                                          */
    SENT_IRQn                   = 74,       /*!< SENT interrupt                                                 */
    HWSEM_IRQn                  = 75,       /*!< HWSEM global interrupt                                         */
    CAN3_ECCERR_IRQn            = 76,       /*!< CAN3 ECC error interrupt                                       */
    CAN4_ECCERR_IRQn            = 77,       /*!< CAN4 ECC error interrupt                                       */
    DAC1_IRQn                   = 78,       /*!< DAC1 global interrupt                                          */
    HSM_COM0_IRQn               = 79,       /*!< HSM communication interrupt 0                                  */
    HSM_COM1_IRQn               = 80,       /*!< HSM communication interrupt 1                                  */
    FMU_CAT_IRQn                = 81,       /*!< FMU cation timeout interrupt                                   */
    RCTL_IRQn                   = 82,       /*!< RCTL interrupt                                                 */
    IOC_IRQn                    = 83,       /*!< IOC interrupt                                                  */
    SPI2_IRQn                   = 84,       /*!< SPI2 global interrupt                                          */
    SPI3_IRQn                   = 85,       /*!< SPI3 global interrupt                                          */
    SPI4_IRQn                   = 86,       /*!< SPI4 global interrupt                                          */
    SPI5_IRQn                   = 87,       /*!< SPI5 global interrupt                                          */
    SPI6_IRQn                   = 88,       /*!< SPI6 global interrupt                                          */
    SPI7_IRQn                   = 89,       /*!< SPI7 global interrupt                                          */
    QSPI_IRQn                   = 90,       /*!< QUADSPI global interrupt                                       */
    USART3_IRQn                 = 91,       /*!< USART3 interrupt                                               */
    USART4_IRQn                 = 92,       /*!< USART4 interrupt                                               */
    USART5_IRQn                 = 93,       /*!< USART5 interrupt                                               */
    CAN2_WKUP_IRQn              = 94,       /*!< CAN2 wakeup through EXTI Line detection interrupt              */
    CAN3_WKUP_IRQn              = 95,       /*!< CAN3 wakeup through EXTI Line detection interrupt              */
    CAN4_WKUP_IRQn              = 96,       /*!< CAN4 wakeup through EXTI Line detection interrupt              */
    CAN5_WKUP_IRQn              = 97,       /*!< CAN5 wakeup through EXTI Line detection interrupt              */
    CAN6_WKUP_IRQn              = 98,       /*!< CAN6 wakeup through EXTI Line detection interrupt              */
    CAN7_WKUP_IRQn              = 99,       /*!< CAN7 wakeup through EXTI Line detection interrupt              */
    CAN2_Message_IRQn           = 100,      /*!< CAN2 Interrupt for message buffer                              */
    CAN2_IRQn                   = 101,      /*!< CAN2 Interrupt                                                 */
    CAN3_Message_IRQn           = 102,      /*!< CAN3 Interrupt for message buffer                              */
    CAN3_IRQn                   = 103,      /*!< CAN3 Interrupt                                                 */
    CAN4_Message_IRQn           = 104,      /*!< CAN4 Interrupt for message buffer                              */
    CAN4_IRQn                   = 105,      /*!< CAN4 Interrupt                                                 */
    CAN5_Message_IRQn           = 106,      /*!< CAN5 Interrupt for message buffer                              */
    CAN5_IRQn                   = 107,      /*!< CAN5 Interrupt                                                 */
    CAN6_Message_IRQn           = 108,      /*!< CAN6 Interrupt for message buffer                              */
    CAN6_IRQn                   = 109,      /*!< CAN6 Interrupt                                                 */
    CAN7_Message_IRQn           = 110,      /*!< CAN7 Interrupt for message buffer                              */
    CAN7_IRQn                   = 111,      /*!< CAN7 Interrupt                                                 */
    TIMER19_CC0_CC0N_IRQn       = 112,      /*!< TIMER19 capture compare CH0 and MCH0 interrupt                 */
    TIMER19_CC1_CC1N_IRQn       = 113,      /*!< TIMER19 capture compare CH1 and MCH1 interrupt                 */
    TIMER19_CC2_CC2N_IRQn       = 114,      /*!< TIMER19 capture compare CH2 and MCH2 interrupt                 */
    TIMER19_CC3_CC3N_IRQn       = 115,      /*!< TIMER19 capture compare CH3 and MCH3 interrupt                 */
    TIMER20_CC0_CC0N_IRQn       = 116,      /*!< TIMER20 capture compare CH0 and MCH0 interrupt                 */
    TIMER20_CC1_CC1N_IRQn       = 117,      /*!< TIMER20 capture compare CH1 and MCH1 interrupt                 */
    TIMER20_CC2_CC2N_IRQn       = 118,      /*!< TIMER20 capture compare CH2 and MCH2 interrupt                 */
    TIMER20_CC3_CC3N_IRQn       = 119,      /*!< TIMER20 capture compare CH3 and MCH3 interrupt                 */
    TIMER60_CC0_CC0N_IRQn       = 120,      /*!< TIMER60 capture compare CH0 and MCH0 interrupt                 */
    TIMER60_CC1_CC1N_IRQn       = 121,      /*!< TIMER60 capture compare CH1 and MCH1 interrupt                 */
    TIMER60_CC2_CC2N_IRQn       = 122,      /*!< TIMER60 capture compare CH2 and MCH2 interrupt                 */
    TIMER60_CC3_CC3N_IRQn       = 123,      /*!< TIMER60 capture compare CH3 and MCH3 interrupt                 */
    TIMER61_CC0_CC0N_IRQn       = 124,      /*!< TIMER61 capture compare CH0 and MCH0 interrupt                 */
    TIMER61_CC1_CC1N_IRQn       = 125,      /*!< TIMER61 capture compare CH1 and MCH1 interrupt                 */
    TIMER61_CC2_CC2N_IRQn       = 126,      /*!< TIMER61 capture compare CH2 and MCH2 interrupt                 */
    TIMER61_CC3_CC3N_IRQn       = 127,      /*!< TIMER61 capture compare CH3 and MCH3 interrupt                 */
    TIMER62_CC0_CC0N_IRQn       = 128,      /*!< TIMER62 capture compare CH0 and MCH0 interrupt                 */
    TIMER62_CC1_CC1N_IRQn       = 129,      /*!< TIMER62 capture compare CH1 and MCH1 interrupt                 */
    TIMER62_CC2_CC2N_IRQn       = 130,      /*!< TIMER62 capture compare CH2 and MCH2 interrupt                 */
    TIMER62_CC3_CC3N_IRQn       = 131,      /*!< TIMER62 capture compare CH3 and MCH3 interrupt                 */
    TIMER63_CC0_CC0N_IRQn       = 132,      /*!< TIMER64 capture compare CH0 and MCH0 interrupt                 */
    TIMER63_CC1_CC1N_IRQn       = 133,      /*!< TIMER64 capture compare CH1 and MCH1 interrupt                 */
    TIMER63_CC2_CC2N_IRQn       = 134,      /*!< TIMER64 capture compare CH2 and MCH2 interrupt                 */
    TIMER63_CC3_CC3N_IRQn       = 135,      /*!< TIMER64 capture compare CH3 and MCH3 interrupt                 */
    DMA0_Channel7_IRQn          = 136,      /*!< DMA0 Channel7 global interrupt                                 */
    DMA0_Channel8_IRQn          = 137,      /*!< DMA0 Channel8 global interrupt                                 */
    DMA0_Channel9_IRQn          = 138,      /*!< DMA0 Channel9 global interrupt                                 */
    DMA0_Channel10_IRQn         = 139,      /*!< DMA0 Channel10 global interrupt                                */
    DMA0_Channel11_IRQn         = 140,      /*!< DMA0 Channel11 global interrupt                                */
    DMA0_Channel12_IRQn         = 141,      /*!< DMA0 Channel12 global interrupt                                */
    DMA0_Channel13_IRQn         = 142,      /*!< DMA0 Channel13 global interrupt                                */
    DMA0_Channel14_IRQn         = 143,      /*!< DMA0 Channel14 global interrupt                                */
    DMA0_Channel15_IRQn         = 144,      /*!< DMA0 Channel15 global interrupt                                */
    DMA1_Channel5_IRQn          = 145,      /*!< DMA1 Channel5 global interrupt                                 */
    DMA1_Channel6_IRQn          = 146,      /*!< DMA1 Channel6 global interrupt                                 */
    DMA1_Channel7_IRQn          = 147,      /*!< DMA1 Channel7 global interrupt                                 */
    DMA1_Channel8_IRQn          = 148,      /*!< DMA1 Channel8 global interrupt                                 */
    DMA1_Channel9_IRQn          = 149,      /*!< DMA1 Channel9 global interrupt                                 */
    DMA1_Channel10_IRQn         = 150,      /*!< DMA1 Channel10 global interrupt                                */
    DMA1_Channel11_IRQn         = 151,      /*!< DMA1 Channel11 global interrupt                                */
    DMA1_Channel12_IRQn         = 152,      /*!< DMA1 Channel12 global interrupt                                */
    DMA1_Channel13_IRQn         = 153,      /*!< DMA1 Channel13 global interrupt                                */
    DMA1_Channel14_IRQn         = 154,      /*!< DMA1 Channel14 global interrupt                                */
    DMA1_Channel15_IRQn         = 155,      /*!< DMA1 Channel15 global interrupt                                */
    MCMUA_RX_IRQn               = 156,      /*!< MCMUA Receive full interrupt                                     */
    MCMUA_TX_IRQn               = 157,      /*!< MCMUA Transmit empty interrupt                                   */
    MCMUA_NORMAL_IRQn           = 158,      /*!< MCMUA NORMAL purpose interrupt                                  */
    MCMUB_RX_IRQn               = 159,      /*!< MCMUB Receive full interrupt                                     */
    MCMUB_TX_IRQn               = 160,      /*!< MCMUB Transmit empty interrupt                                   */
    MCMUB_NORMAL_IRQn           = 161,      /*!< MCMUB NORMAL purpose interrupt                                  */
    LIN0_IRQn                   = 162,      /*!< LIN0 interrupt                                                 */
    LIN1_IRQn                   = 163,      /*!< LIN1 interrupt                                                 */
    LIN2_IRQn                   = 164,      /*!< LIN2 interrupt                                                 */
    LIN3_IRQn                   = 165,      /*!< LIN3 interrupt                                                 */
    LIN4_IRQn                   = 166,      /*!< LIN4 interrupt                                                 */
    LIN5_IRQn                   = 167,      /*!< LIN5 interrupt                                                 */
    LIN6_IRQn                   = 168,      /*!< LIN6 interrupt                                                 */
    LIN7_IRQn                   = 169,      /*!< LIN7 interrupt                                                 */
    LIN8_IRQn                   = 170,      /*!< LIN8 interrupt                                                 */
    LIN9_IRQn                   = 171,      /*!< LIN9 interrupt                                                 */
    LIN10_IRQn                  = 172,      /*!< LIN10 interrupt                                                */
    LIN11_IRQn                  = 173,      /*!< LIN11 interrupt                                                */
    TIMER0_CC0_CC0N_IRQn        = 174,      /*!< TIMER0 Capture Compare CH0 and MCH0 interrupt                  */
    TIMER0_CC1_CC1N_IRQn        = 175,      /*!< TIMER0 Capture Compare CH1 and MCH1 interrupt                  */
    TIMER0_CC2_CC2N_IRQn        = 176,      /*!< TIMER0 Capture Compare CH2 and MCH3 interrupt                  */
    TIMER0_CC3_CC3N_IRQn        = 177,      /*!< TIMER0 Capture Compare CH4 and MCH4 interrupt                  */
    TIMER7_CC0_CC0N_IRQn        = 178,      /*!< TIMER7 Capture Compare CH0 and MCH0 interrupt                  */
    TIMER7_CC1_CC1N_IRQn        = 179,      /*!< TIMER7 Capture Compare CH1 and MCH1 interrupt                  */
    TIMER7_CC2_CC2N_IRQn        = 180,      /*!< TIMER7 Capture Compare CH2 and MCH3 interrupt                  */
    TIMER7_CC3_CC3N_IRQn        = 181,      /*!< TIMER7 Capture Compare CH4 and MCH4 interrupt                  */
    TIMER1_CC0_IRQn             = 182,      /*!< TIMER1 Capture Compare CH0 and MCH0 interrupt                  */
    TIMER1_CC1_IRQn             = 183,      /*!< TIMER1 Capture Compare CH1 and MCH1 interrupt                  */
    TIMER1_CC2_IRQn             = 184,      /*!< TIMER1 Capture Compare CH2 and MCH3 interrupt                  */
    TIMER1_CC3_IRQn             = 185,      /*!< TIMER1 Capture Compare CH4 and MCH4 interrupt                  */
    TIMER2_CC0_IRQn             = 186,      /*!< TIMER2 Capture Compare CH0 and MCH0 interrupt                  */
    TIMER2_CC1_IRQn             = 187,      /*!< TIMER2 Capture Compare CH1 and MCH1 interrupt                  */
    TIMER2_CC2_IRQn             = 188,      /*!< TIMER2 Capture Compare CH2 and MCH3 interrupt                  */
    TIMER2_CC3_IRQn             = 189,      /*!< TIMER2 Capture Compare CH4 and MCH4 interrupt                  */
    FWDGT_IRQn                  = 190,      /*!< FWDGT reset interrupt through EXTI Line detection interrupt    */
    ETH_IRQn                    = 191,      /*!< Ethernet0 global interrupt                                     */
    ETH_WKUP_IRQn               = 192,      /*!< Ethernet0 wakeup interrupt | Ethernet0 lpi interrupt           */
    ETH_TX_IRQn                 = 193,      /*!< Ethernet0 Tx0 / Tx1 interrupt                                  */
    ETH_RX_IRQn                 = 194,      /*!< Ethernet0 Rx0 / Rx1 interrupt                                  */
    ETH_SAFETY_IRQn             = 195,      /*!< Ethernet0 safety correctable / uncorrectable interrupt         */
    RCU_CK_FAIL_IRQn            = 196,      /*!< RCU clock fail interrupt                                       */
    CAN5_ECCERR_IRQn            = 197,      /*!< CAN5 ECC error interrupt                                       */
    TIMER60_BRK_UP_TRG_CMT_IRQn = 210,      /*!< TIMER60 Break, update, trigger and commutation, dec interrupt  */
    TIMER61_BRK_UP_TRG_CMT_IRQn = 211,      /*!< TIMER61 Break, update, trigger and commutation, dec interrupt  */
    TIMER62_BRK_UP_TRG_CMT_IRQn = 212,      /*!< TIMER62 Break, update, trigger and commutation, dec interrupt  */
    TIMER63_BRK_UP_TRG_CMT_IRQn = 213,      /*!< TIMER63 Break, update, trigger and commutation, dec interrupt  */
    TIMER5_CH0_UP_IRQn          = 214,      /*!< TIMER5 CH0 update interrupt                                    */
    TIMER5_CH1_UP_IRQn          = 215,      /*!< TIMER5 CH1 update interrupt                                    */
    TIMER5_CH2_UP_IRQn          = 216,      /*!< TIMER5 CH2 update interrupt                                    */
    TIMER5_CH3_UP_IRQn          = 217,      /*!< TIMER5 CH3 update interrupt                                    */
    TIMER6_CH0_UP_IRQn          = 218,      /*!< TIMER6 CH0 update interrupt                                    */
    TIMER6_CH1_UP_IRQn          = 219,      /*!< TIMER6 CH1 update interrupt                                    */
    TIMER6_CH2_UP_IRQn          = 220,      /*!< TIMER6 CH2 update interrupt                                    */
    TIMER6_CH3_UP_IRQn          = 221,      /*!< TIMER6 CH3 update interrupt                                    */
    CAN6_ECCERR_IRQn            = 238,      /*!< CAN6 ECC error interrupt                                       */
    CAN7_ECCERR_IRQn            = 239       /*!< CAN7 ECC error interrupt                                       */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)                                      */
} IRQn_Type;

/* includes */
#include "core_cm7.h"
#include "system_gd32a7xx.h"
#include <stdint.h>
#ifdef FW_DEBUG_ERR_REPORT
#include "gd32a7xx_err_report.h"
#endif /* FW_DEBUG_ERR_REPORT */

/* enum definitions */
typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;
typedef enum {RESET = 0, SET = !RESET} FlagStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/* bit operations */
#define REG64(addr)                  (*(volatile uint64_t *)(uint32_t)(addr))
#define REG32(addr)                  (*(volatile uint32_t *)(uint32_t)(addr))
#define REG16(addr)                  (*(volatile uint16_t *)(uint32_t)(addr))
#define REG8(addr)                   (*(volatile uint8_t *)(uint32_t)(addr))
#define BIT(x)                       ((uint32_t)((uint32_t)0x01U<<(x)))
#define BITS(start, end)             ((0xFFFFFFFFUL << (uint8_t)(start)) & (0xFFFFFFFFUL >> (31U - (uint8_t)(end)))) 
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

/* main flash and SRAM memory map */
#define FLASH_BASE            ((uint32_t)0x08000000U)       /*!< main FLASH base address    */
#define SRAM_BASE             ((uint32_t)0x24000000U)       /*!< SRAM base address          */

/* peripheral memory map */
#define APB1_BUS_BASE         ((uint32_t)0x40000000U)       /*!< apb1 base address          */
#define APB2_BUS_BASE         ((uint32_t)0x4000F000U)       /*!< apb2 base address          */
#define AHB1_BUS_BASE         ((uint32_t)0x40020000U)       /*!< ahb1 base address          */
#define AHB2_BUS_BASE         ((uint32_t)0x48000000U)       /*!< ahb2 base address          */
#define AHB3_BUS_BASE         ((uint32_t)0x50010000U)       /*!< ahb3 base address          */

/* advanced peripheral bus 1 memory map */
#define TIMER_BASE            (APB1_BUS_BASE + 0x00000000U) /*!< TIMER base address         */
#define CLTCFG_BASE           (APB1_BUS_BASE + 0x00002400U) /*!< CLTCFG base address        */
#define RTC_BASE              (APB1_BUS_BASE + 0x00002800U) /*!< RTC base address           */
#define WWDGT_BASE            (APB1_BUS_BASE + 0x00002C00U) /*!< WWDGT base address         */
#define FWDGT_BASE            (APB1_BUS_BASE + 0x00003000U) /*!< FWDGT base address         */
#define SPI_BASE              (APB1_BUS_BASE + 0x00003800U) /*!< SPI base address           */
#define I2C_BASE              (APB1_BUS_BASE + 0x00005400U) /*!< I2C base address           */
#define BKP_BASE              (APB1_BUS_BASE + 0x00006C00U) /*!< BKP base address           */
#define PMU_BASE              (APB1_BUS_BASE + 0x00007000U) /*!< PMU base address           */
#define DAC_BASE              (APB1_BUS_BASE + 0x00007400U) /*!< DAC base address           */
#if  defined(GD32A714X) || defined(GD32A72XX) || defined (GD32A74XX)
#define SENT_BASE             (APB1_BUS_BASE + 0x00006000U) /*!< SENT base address          */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define LINFLEXD_BASE         (APB1_BUS_BASE + 0x00008800U) /*!< LIN base address           */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define ENET_BASE             (APB1_BUS_BASE + 0x0000A000U) /*!< ENET base address          */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define JDC_BASE              (APB1_BUS_BASE + 0x0000EC00U) /*!< JDC base address           */

/* advanced peripheral bus 2 memory map */
#define ADC_BASE              (APB2_BUS_BASE + 0x00000000U) /*!< ADC base address           */
#define SYSCFG_BASE           (APB2_BUS_BASE + 0x00001000U) /*!< SYSCFG base address        */
#define EXTI_BASE             (APB2_BUS_BASE + 0x00001400U) /*!< EXTI base address          */
#define TRIGSEL_BASE          (APB2_BUS_BASE + 0x00003000U) /*!< TRIGSEL base address       */
#define CMP_BASE              (APB2_BUS_BASE + 0x00007C00U) /*!< CMP base address           */
#define CAN_BASE              (APB2_BUS_BASE + 0x00009000U) /*!< CAN base address           */

/* advanced high performance bus 1 memory map */
#define FMU_BASE              (AHB1_BUS_BASE + 0x00003400U) /*!< FMU base address           */
#define IRM_BASE              (AHB1_BUS_BASE + 0x00003800U) /*!< IRM base address           */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define IOC_BASE              (AHB1_BUS_BASE + 0x00003C00U) /*!< IOC base address           */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define MTC_BASE              (AHB1_BUS_BASE + 0x00004400U) /*!< MTC base address           */
#define STCM_BASE             (AHB1_BUS_BASE + 0x00005000U) /*!< STCM base address          */
#define REGPRT_BASE           (AHB1_BUS_BASE + 0x00018000U) /*!< REGPRT base address        */
#define DBGSYS_BASE           (AHB1_BUS_BASE + 0x00220000U) /*!< DBGSYS base address        */

/* advanced high performance bus 2 memory map */
#define GPIO_BASE             (AHB2_BUS_BASE + 0x00000000U) /*!< GPIO base address          */
#define DMA_BASE              (AHB2_BUS_BASE + 0x01000000U) /*!< DMA base address           */
#define DMAMUX_BASE           (AHB2_BUS_BASE + 0x01000800U) /*!< DMAMUX base address        */
#define SRAMC_BASE            (AHB2_BUS_BASE + 0x01000C00U) /*!< SRAMC base address         */
#define RCU_BASE              (AHB2_BUS_BASE + 0x01001000U) /*!< RCU base address           */
#define QSPI_BASE             (AHB2_BUS_BASE + 0x01001400U) /*!< QSPI base address          */
#define FMC_BASE              (AHB2_BUS_BASE + 0x01002000U) /*!< FMC base address           */
#define CRC_BASE              (AHB2_BUS_BASE + 0x01003000U) /*!< CRC base address           */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define MFCOM_BASE            (AHB2_BUS_BASE + 0x01003400U) /*!< MFCOM base address         */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define RMU_BASE              (AHB2_BUS_BASE + 0x01003C00U) /*!< RMU base address           */
#define TCMREG_BASE           (AHB2_BUS_BASE + 0x01004000U) /*!< TCMREG base address        */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define MCMU_BASE             (AHB2_BUS_BASE + 0x01008000U) /*!< MCMU base address          */
#define HWSEM_BASE            (AHB2_BUS_BASE + 0x01008800U) /*!< HWSEM base address         */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define HSMIF_BASE            (AHB2_BUS_BASE + 0x01008C00U) /*!< HSMIF base address         */
#define BUSIM_BASE            (AHB2_BUS_BASE + 0x01009000U) /*!< BUSIM base address         */
#define IMICU_BASE            (AHB2_BUS_BASE + 0x01009400U) /*!< IMICU base address         */
#define EXTMPU_BASE           (AHB2_BUS_BASE + 0x0100A000U) /*!< EXTMPU base address        */

/* advanced high performance bus 3 memory map */
#define SM2_BASE              (AHB3_BUS_BASE + 0x00010800U) /*!< SM2 base address           */
#define SM3_BASE              (AHB3_BUS_BASE + 0x00010C00U) /*!< SM3 base address           */
#define SM4_BASE              (AHB3_BUS_BASE + 0x00011000U) /*!< SM4 base address           */
#define PKCAU_BASE            (AHB3_BUS_BASE + 0x00011400U) /*!< PKCAU base address         */
#define CAU_BASE              (AHB3_BUS_BASE + 0x00050000U) /*!< CAU base address           */
#define HAU_BASE              (AHB3_BUS_BASE + 0x00050400U) /*!< HAU base address           */
#define TRNG_BASE             (AHB3_BUS_BASE + 0x00050800U) /*!< TRNG base address          */

/* option byte and debug memory map */
#define OB_BASE               ((uint32_t)0x1FFF8800U)       /*!< OB base address            */

#define DBG_BASE              ((uint32_t)0xE00E1000U)       /*!< DBG base address           */

/* define marco USE_STDPERIPH_DRIVER */
#if !defined  USE_STDPERIPH_DRIVER
#define USE_STDPERIPH_DRIVER
#endif 
#ifdef USE_STDPERIPH_DRIVER
#include "gd32a7xx_libopt.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef __cplusplus
}
#endif

#endif /* GD32A7XX_H */
