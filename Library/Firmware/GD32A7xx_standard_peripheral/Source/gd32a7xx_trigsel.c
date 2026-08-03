/*!
    \file    gd32a7xx_trigsel.c
    \brief   TRIGSEL driver

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

#include "gd32a7xx_trigsel.h"

/* TRIGSEL target register redefine */
#define TRIGSEL_TARGET_REG(target_periph)           (REG32(TRIGSEL + ((uint32_t)(target_periph) & BITS(2,31))))            /*!< target peripheral register */
#define TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)  (((uint32_t)(target_periph) & BITS(0,1)) << 3U)                        /*!< bit offset in target peripheral register */
#define TRIGSEL_TARGET_PERIPH_MASK(target_periph)   ((uint32_t)(BITS(0,7) << TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)))  /*!< bit mask in target peripheral register */

/*!
    \brief      set the trigger input signal for target peripheral
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT8: output target peripheral TRIGSEL_OUT8 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT9: output target peripheral TRIGSEL_OUT9 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT10: output target peripheral TRIGSEL_OUT10 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT11: output target peripheral TRIGSEL_OUT11 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT12: output target peripheral TRIGSEL_OUT12 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT13: output target peripheral TRIGSEL_OUT13 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT14: output target peripheral TRIGSEL_OUT14 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT15: output target peripheral TRIGSEL_OUT15 pin
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR0: output target peripheral IOC monitor0 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR1: output target peripheral IOC monitor1 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR2: output target peripheral IOC monitor2 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR3: output target peripheral IOC monitor3 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR4: output target peripheral IOC monitor4 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR5: output target peripheral IOC monitor5 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR6: output target peripheral IOC monitor6 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR7: output target peripheral IOC monitor7 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE0: output target peripheral IOC reference0 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE1: output target peripheral IOC reference1 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE2: output target peripheral IOC reference2 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE3: output target peripheral IOC reference3 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE4: output target peripheral IOC reference4 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE5: output target peripheral IOC reference5 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE6: output target peripheral IOC reference6 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE7: output target peripheral IOC reference7 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN3_EX_TIME_TICK: output target peripheral CAN3_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN4_EX_TIME_TICK: output target peripheral CAN4_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN5_EX_TIME_TICK: output target peripheral CAN5_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN6_EX_TIME_TICK: output target peripheral CAN6_EX_TIME_TICK only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CAN7_EX_TIME_TICK: output target peripheral CAN7_EX_TIME_TICK only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI0: output target peripheral TIMER0_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI0: output target peripheral TIMER1_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI0: output target peripheral TIMER2_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI0: output target peripheral TIMER7_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER19_ITI0: output target peripheral TIMER19_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER20_ITI0: output target peripheral TIMER20_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER60_ITI0: output target peripheral TIMER60_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER61_ITI0: output target peripheral TIMER61_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER62_ITI0: output target peripheral TIMER62_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER63_ITI0: output target peripheral TIMER63_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN3: output target peripheral TIMER0_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN3: output target peripheral TIMER7_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN0: output target peripheral TIMER19_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN1: output target peripheral TIMER19_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN2: output target peripheral TIMER19_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN3: output target peripheral TIMER19_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN0: output target peripheral TIMER20_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN1: output target peripheral TIMER20_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN2: output target peripheral TIMER20_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN3: output target peripheral TIMER20_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN0: output target peripheral TIMER60_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN1: output target peripheral TIMER60_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN2: output target peripheral TIMER60_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN3: output target peripheral TIMER60_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN0: output target peripheral TIMER61_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN1: output target peripheral TIMER61_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN2: output target peripheral TIMER61_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN3: output target peripheral TIMER61_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN0: output target peripheral TIMER62_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN1: output target peripheral TIMER62_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN2: output target peripheral TIMER62_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN3: output target peripheral TIMER62_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN0: output target peripheral TIMER63_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN1: output target peripheral TIMER63_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN2: output target peripheral TIMER63_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN3: output target peripheral TIMER63_BRKIN3
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG0: output target peripheral MFCOM external trigger 0 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG1: output target peripheral MFCOM external trigger 1 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG2: output target peripheral MFCOM external trigger 2 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG3: output target peripheral MFCOM external trigger 3 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CM7_0_RXEV: output target peripheral CM7_0_RXEV
      \arg        TRIGSEL_OUTPUT_CM7_1_RXEV: output target peripheral CM7_1_RXEV
      \arg        TRIGSEL_OUTPUT_DAC0_OUT0_EXTRG: output target peripheral DAC0_OUT0 external trigger
      \arg        TRIGSEL_OUTPUT_DAC1_OUT0_EXTRG: output target peripheral DAC1_OUT0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_ROUTRG : output target peripheral ADC0 routine sequence external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS0TRG: output target peripheral ADC0 inserted sequence 0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS1TRG: output target peripheral ADC0 inserted sequence 1 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS2TRG: output target peripheral ADC0 inserted sequence 2 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS3TRG: output target peripheral ADC0 inserted sequence 3 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS4TRG: output target peripheral ADC0 inserted sequence 4 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS5TRG: output target peripheral ADC0 inserted sequence 5 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_ROUTRG : output target peripheral ADC1 routine sequence external trigger 
      \arg        TRIGSEL_OUTPUT_ADC1_INS0TRG: output target peripheral ADC1 inserted sequence 0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS1TRG: output target peripheral ADC1 inserted sequence 1 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS2TRG: output target peripheral ADC1 inserted sequence 2 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS3TRG: output target peripheral ADC1 inserted sequence 3 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS4TRG: output target peripheral ADC1 inserted sequence 4 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS5TRG: output target peripheral ADC1 inserted sequence 5 external trigger
      \arg        TRIGSEL_OUTPUT_ADC2_ROUTRG : output target peripheral ADC2 routine sequence external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS0TRG: output target peripheral ADC2 inserted sequence 0 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS1TRG: output target peripheral ADC2 inserted sequence 1 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS2TRG: output target peripheral ADC2 inserted sequence 2 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS3TRG: output target peripheral ADC2 inserted sequence 3 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS4TRG: output target peripheral ADC2 inserted sequence 4 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS5TRG: output target peripheral ADC2 inserted sequence 5 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_SPI0_TRIG: output target peripheral SPI0 trigger
      \arg        TRIGSEL_OUTPUT_SPI1_TRIG: output target peripheral SPI1 trigger
      \arg        TRIGSEL_OUTPUT_SPI2_TRIG: output target peripheral SPI2 trigger
      \arg        TRIGSEL_OUTPUT_SPI3_TRIG: output target peripheral SPI3 trigger
      \arg        TRIGSEL_OUTPUT_SPI4_TRIG: output target peripheral SPI4 trigger
      \arg        TRIGSEL_OUTPUT_SPI5_TRIG: output target peripheral SPI5 trigger
      \arg        TRIGSEL_OUTPUT_SPI6_TRIG: output target peripheral SPI6 trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_SPI7_TRIG: output target peripheral SPI7 trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_TIMER_ETI0: output target peripheral TIMER_ETI0
      \arg        TRIGSEL_OUTPUT_TIMER_ETI1: output target peripheral TIMER_ETI1
      \arg        TRIGSEL_OUTPUT_TIMER_ETI2: output target peripheral TIMER_ETI2
      \arg        TRIGSEL_OUTPUT_LINFLEXD0_TRIG: output target peripheral LINFlexD0 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD1_TRIG: output target peripheral LINFlexD1 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD2_TRIG: output target peripheral LINFlexD2 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD3_TRIG: output target peripheral LINFlexD3 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD4_TRIG: output target peripheral LINFlexD4 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD5_TRIG: output target peripheral LINFlexD5 trigger
    \param[in]  trigger_source: trigger source value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_INPUT_0: trigger input source 0
      \arg        TRIGSEL_INPUT_1: trigger input source 1
      \arg        TRIGSEL_INPUT_TRIGSEL_IN0: trigger input source TRIGSEL_IN0 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN1: trigger input source TRIGSEL_IN1 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN2: trigger input source TRIGSEL_IN2 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN3: trigger input source TRIGSEL_IN3 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN4: trigger input source TRIGSEL_IN4 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN5: trigger input source TRIGSEL_IN5 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN6: trigger input source TRIGSEL_IN6 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN7: trigger input source TRIGSEL_IN7 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN8: trigger input source TRIGSEL_IN8 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN9: trigger input source TRIGSEL_IN9 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN10: trigger input source TRIGSEL_IN10 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN11: trigger input source TRIGSEL_IN11 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN12: trigger input source TRIGSEL_IN12 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN13: trigger input source TRIGSEL_IN13 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN14: trigger input source TRIGSEL_IN14 pin
      \arg        TRIGSEL_INPUT_TRIGSEL_IN15: trigger input source TRIGSEL_IN15 pin
      \arg        TRIGSEL_INPUT_TIMER0_TRGO0: trigger input source TIMER0 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER0_CH0: trigger input source TIMER0 CH0 output
      \arg        TRIGSEL_INPUT_TIMER0_CH1: trigger input source TIMER0 CH1 output
      \arg        TRIGSEL_INPUT_TIMER0_CH2: trigger input source TIMER0 CH2 output
      \arg        TRIGSEL_INPUT_TIMER0_CH3: trigger input source TIMER0 CH3 output
      \arg        TRIGSEL_INPUT_TIMER0_MCH0: trigger input source TIMER0 MCH0 output
      \arg        TRIGSEL_INPUT_TIMER0_MCH1: trigger input source TIMER0 MCH1 output
      \arg        TRIGSEL_INPUT_TIMER0_MCH2: trigger input source TIMER0 MCH2 output
      \arg        TRIGSEL_INPUT_TIMER0_MCH3: trigger input source TIMER0 MCH3 output
      \arg        TRIGSEL_INPUT_TIMER7_TRGO0: trigger input source TIMER7 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER7_CH0: trigger input source TIMER7 CH0 output
      \arg        TRIGSEL_INPUT_TIMER7_CH1: trigger input source TIMER7 CH1 output
      \arg        TRIGSEL_INPUT_TIMER7_CH2: trigger input source TIMER7 CH2 output
      \arg        TRIGSEL_INPUT_TIMER7_CH3: trigger input source TIMER7 CH3 output
      \arg        TRIGSEL_INPUT_TIMER7_MCH0: trigger input source TIMER7 MCH0 output
      \arg        TRIGSEL_INPUT_TIMER7_MCH1: trigger input source TIMER7 MCH1 output
      \arg        TRIGSEL_INPUT_TIMER7_MCH2: trigger input source TIMER7 MCH2 output
      \arg        TRIGSEL_INPUT_TIMER7_MCH3: trigger input source TIMER7 MCH3 output
      \arg        TRIGSEL_INPUT_TIMER19_TRGO0: trigger input source TIMER19 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER19_CH0: trigger input source TIMER19 CH0 output
      \arg        TRIGSEL_INPUT_TIMER19_CH1: trigger input source TIMER19 CH1 output
      \arg        TRIGSEL_INPUT_TIMER19_CH2: trigger input source TIMER19 CH2 output
      \arg        TRIGSEL_INPUT_TIMER19_CH3: trigger input source TIMER19 CH3 output
      \arg        TRIGSEL_INPUT_TIMER19_MCH0: trigger input source TIMER19 MCH0 output
      \arg        TRIGSEL_INPUT_TIMER19_MCH1: trigger input source TIMER19 MCH1 output
      \arg        TRIGSEL_INPUT_TIMER19_MCH2: trigger input source TIMER19 MCH2 output
      \arg        TRIGSEL_INPUT_TIMER19_MCH3: trigger input source TIMER19 MCH3 output
      \arg        TRIGSEL_INPUT_TIMER20_TRGO0: trigger input source TIMER20 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER20_CH0: trigger input source TIMER20 CH0 output
      \arg        TRIGSEL_INPUT_TIMER20_CH1: trigger input source TIMER20 CH1 output
      \arg        TRIGSEL_INPUT_TIMER20_CH2: trigger input source TIMER20 CH2 output
      \arg        TRIGSEL_INPUT_TIMER20_CH3: trigger input source TIMER20 CH3 output
      \arg        TRIGSEL_INPUT_TIMER20_MCH0: trigger input source TIMER20 MCH0 output
      \arg        TRIGSEL_INPUT_TIMER20_MCH1: trigger input source TIMER20 MCH1 output
      \arg        TRIGSEL_INPUT_TIMER20_MCH2: trigger input source TIMER20 MCH2 output
      \arg        TRIGSEL_INPUT_TIMER20_MCH3: trigger input source TIMER20 MCH3 output
      \arg        TRIGSEL_INPUT_TIMER60_TRGO0: trigger input source TIMER60 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER60_CH0: trigger input source TIMER60 CH0 output
      \arg        TRIGSEL_INPUT_TIMER60_CH1: trigger input source TIMER60 CH1 output
      \arg        TRIGSEL_INPUT_TIMER60_CH2: trigger input source TIMER60 CH2 output
      \arg        TRIGSEL_INPUT_TIMER60_CH3: trigger input source TIMER60 CH3 output
      \arg        TRIGSEL_INPUT_TIMER60_MCH0: trigger input source TIMER60 MCH0 output
      \arg        TRIGSEL_INPUT_TIMER60_MCH1: trigger input source TIMER60 MCH1 output
      \arg        TRIGSEL_INPUT_TIMER60_MCH2: trigger input source TIMER60 MCH2 output
      \arg        TRIGSEL_INPUT_TIMER60_MCH3: trigger input source TIMER60 MCH3 output
      \arg        TRIGSEL_INPUT_TIMER61_TRGO0: trigger input source TIMER61 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER61_CH0: trigger input source TIMER61 CH0 output
      \arg        TRIGSEL_INPUT_TIMER61_CH1: trigger input source TIMER61 CH1 output
      \arg        TRIGSEL_INPUT_TIMER61_CH2: trigger input source TIMER61 CH2 output
      \arg        TRIGSEL_INPUT_TIMER61_CH3: trigger input source TIMER61 CH3 output
      \arg        TRIGSEL_INPUT_TIMER61_MCH0: trigger input source TIMER61 MCH0 output
      \arg        TRIGSEL_INPUT_TIMER61_MCH1: trigger input source TIMER61 MCH1 output
      \arg        TRIGSEL_INPUT_TIMER61_MCH2: trigger input source TIMER61 MCH2 output
      \arg        TRIGSEL_INPUT_TIMER61_MCH3: trigger input source TIMER61 MCH3 output
      \arg        TRIGSEL_INPUT_TIMER62_TRGO0: trigger input source TIMER62 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER62_CH0: trigger input source TIMER62 CH0 output
      \arg        TRIGSEL_INPUT_TIMER62_CH1: trigger input source TIMER62 CH1 output
      \arg        TRIGSEL_INPUT_TIMER62_CH2: trigger input source TIMER62 CH2 output
      \arg        TRIGSEL_INPUT_TIMER62_CH3: trigger input source TIMER62 CH3 output
      \arg        TRIGSEL_INPUT_TIMER62_MCH0: trigger input source TIMER62 MCH0 output
      \arg        TRIGSEL_INPUT_TIMER62_MCH1: trigger input source TIMER62 MCH1 output
      \arg        TRIGSEL_INPUT_TIMER62_MCH2: trigger input source TIMER62 MCH2 output
      \arg        TRIGSEL_INPUT_TIMER62_MCH3: trigger input source TIMER62 MCH3 output
      \arg        TRIGSEL_INPUT_TIMER63_TRGO0: trigger input source TIMER63 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER63_CH0: trigger input source TIMER63 CH0 output
      \arg        TRIGSEL_INPUT_TIMER63_CH1: trigger input source TIMER63 CH1 output
      \arg        TRIGSEL_INPUT_TIMER63_CH2: trigger input source TIMER63 CH2 output
      \arg        TRIGSEL_INPUT_TIMER63_CH3: trigger input source TIMER63 CH3 output
      \arg        TRIGSEL_INPUT_TIMER63_MCH0: trigger input source TIMER63 MCH0 output
      \arg        TRIGSEL_INPUT_TIMER63_MCH1: trigger input source TIMER63 MCH1 output
      \arg        TRIGSEL_INPUT_TIMER63_MCH2: trigger input source TIMER63 MCH2 output
      \arg        TRIGSEL_INPUT_TIMER63_MCH3: trigger input source TIMER63 MCH3 output
      \arg        TRIGSEL_INPUT_TIMER1_TRGO0: trigger input source TIMER1 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER1_CH0: trigger input source TIMER1 CH0 output
      \arg        TRIGSEL_INPUT_TIMER1_CH1: trigger input source TIMER1 CH1 output
      \arg        TRIGSEL_INPUT_TIMER1_CH2: trigger input source TIMER1 CH2 output
      \arg        TRIGSEL_INPUT_TIMER1_CH3: trigger input source TIMER1 CH3 output
      \arg        TRIGSEL_INPUT_TIMER2_TRGO0: trigger input source TIMER2 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER2_CH0: trigger input source TIMER2 CH0 output
      \arg        TRIGSEL_INPUT_TIMER2_CH1: trigger input source TIMER2 CH1 output
      \arg        TRIGSEL_INPUT_TIMER2_CH2: trigger input source TIMER2 CH2 output
      \arg        TRIGSEL_INPUT_TIMER2_CH3: trigger input source TIMER2 CH3 output
      \arg        TRIGSEL_INPUT_TIMER5_TRGO0: trigger input source TIMER5 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER5_TRGO1: trigger input source TIMER5 TRGO1 output
      \arg        TRIGSEL_INPUT_TIMER5_TRGO2: trigger input source TIMER5 TRGO2 output
      \arg        TRIGSEL_INPUT_TIMER5_TRGO3: trigger input source TIMER5 TRGO3 output
      \arg        TRIGSEL_INPUT_TIMER6_TRGO0: trigger input source TIMER6 TRGO0 output
      \arg        TRIGSEL_INPUT_TIMER6_TRGO1: trigger input source TIMER6 TRGO1 output
      \arg        TRIGSEL_INPUT_TIMER6_TRGO2: trigger input source TIMER6 TRGO2 output
      \arg        TRIGSEL_INPUT_TIMER6_TRGO3: trigger input source TIMER6 TRGO3 output
      \arg        TRIGSEL_INPUT_CMP0_OUT: trigger input source CMP0 output
      \arg        TRIGSEL_INPUT_CMP1_OUT: trigger input source CMP1 output
      \arg        TRIGSEL_INPUT_BKP_TAMPER: trigger input source BKP tamper interrupt flag
      \arg        TRIGSEL_INPUT_RTC_ALARM: trigger input source RTC alarm output
      \arg        TRIGSEL_INPUT_MFCOM_TIMER0_OUT: trigger input source MFCOM TIMER0 output only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_MFCOM_TIMER1_OUT: trigger input source MFCOM TIMER1 output only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_MFCOM_TIMER2_OUT: trigger input source MFCOM TIMER2 output only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_MFCOM_TIMER3_OUT: trigger input source MFCOM TIMER3 output only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_CM7_0_TXEV : trigger input source CM7_0_TXEV
      \arg        TRIGSEL_INPUT_CM7_1_TXEV : trigger input source CM7_1_TXEV only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_CK_OUT0: trigger input source CK_OUT0
      \arg        TRIGSEL_INPUT_TIMER_ETI0 : trigger input source TIMER_ETI0 pin
      \arg        TRIGSEL_INPUT_TIMER_ETI1 : trigger input source TIMER_ETI1 pin
      \arg        TRIGSEL_INPUT_TIMER_ETI2 : trigger input source TIMER_ETI2 pin
      \arg        TRIGSEL_INPUT_CK_OUT1: trigger input source CK_OUT1
      \arg        TRIGSEL_INPUT_DAC0_EOC: trigger input source DAC0_eoc
      \arg        TRIGSEL_INPUT_DAC1_EOC: trigger input source DAC1_eoc
      \arg        TRIGSEL_INPUT_ADC0_EORC: trigger input source end of ADC0 routine sequence conversion
      \arg        TRIGSEL_INPUT_ADC1_EORC: trigger input source end of ADC1 routine sequence conversion
      \arg        TRIGSEL_INPUT_ADC2_EORC  : trigger input source end of ADC2 routine sequence conversion only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC0_ECH: trigger input source end of ADC0 routine/inserted sequence channel conversion
      \arg        TRIGSEL_INPUT_ADC1_ECH: trigger input source end of ADC1 routine/inserted sequence channel conversion
      \arg        TRIGSEL_INPUT_ADC2_ECH: trigger input source end of ADC2 routine/inserted sequence channel conversion only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC0_WD0_OUT: trigger input source ADC0 analog watchdog0 output
      \arg        TRIGSEL_INPUT_ADC0_WD1_OUT: trigger input source ADC0 analog watchdog1 output
      \arg        TRIGSEL_INPUT_ADC0_WD2_OUT: trigger input source ADC0 analog watchdog2 output
      \arg        TRIGSEL_INPUT_ADC0_WD3_OUT: trigger input source ADC0 analog watchdog3 output
      \arg        TRIGSEL_INPUT_ADC1_WD0_OUT: trigger input source ADC1 analog watchdog0 output
      \arg        TRIGSEL_INPUT_ADC1_WD1_OUT: trigger input source ADC1 analog watchdog1 output
      \arg        TRIGSEL_INPUT_ADC1_WD2_OUT: trigger input source ADC1 analog watchdog2 output
      \arg        TRIGSEL_INPUT_ADC1_WD3_OUT: trigger input source ADC1 analog watchdog3 output
      \arg        TRIGSEL_INPUT_ADC2_WD0_OUT: trigger input source ADC2 analog watchdog0 output only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC2_WD1_OUT: trigger input source ADC2 analog watchdog1 output only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC2_WD2_OUT: trigger input source ADC2 analog watchdog2 output only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC2_WD3_OUT: trigger input source ADC2 analog watchdog3 output only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC0_EOI0C: trigger input source end of ADC0 inserted sequence 0 conversion
      \arg        TRIGSEL_INPUT_ADC0_EOI1C: trigger input source end of ADC0 inserted sequence 1 conversion
      \arg        TRIGSEL_INPUT_ADC0_EOI2C: trigger input source end of ADC0 inserted sequence 2 conversion
      \arg        TRIGSEL_INPUT_ADC0_EOI3C: trigger input source end of ADC0 inserted sequence 3 conversion
      \arg        TRIGSEL_INPUT_ADC0_EOI4C: trigger input source end of ADC0 inserted sequence 4 conversion
      \arg        TRIGSEL_INPUT_ADC0_EOI5C: trigger input source end of ADC0 inserted sequence 5 conversion
      \arg        TRIGSEL_INPUT_ADC1_EOI0C: trigger input source end of ADC1 inserted sequence 0 conversion
      \arg        TRIGSEL_INPUT_ADC1_EOI1C: trigger input source end of ADC1 inserted sequence 1 conversion
      \arg        TRIGSEL_INPUT_ADC1_EOI2C: trigger input source end of ADC1 inserted sequence 2 conversion
      \arg        TRIGSEL_INPUT_ADC1_EOI3C: trigger input source end of ADC1 inserted sequence 3 conversion
      \arg        TRIGSEL_INPUT_ADC1_EOI4C: trigger input source end of ADC1 inserted sequence 4 conversion
      \arg        TRIGSEL_INPUT_ADC1_EOI5C: trigger input source end of ADC1 inserted sequence 5 conversion
      \arg        TRIGSEL_INPUT_ADC2_EOI0C: trigger input source end of ADC2 inserted sequence 0 conversion only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC2_EOI1C: trigger input source end of ADC2 inserted sequence 1 conversion only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC2_EOI2C: trigger input source end of ADC2 inserted sequence 2 conversion only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC2_EOI3C: trigger input source end of ADC2 inserted sequence 3 conversion only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC2_EOI4C: trigger input source end of ADC2 inserted sequence 4 conversion only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_ADC2_EOI5C: trigger input source end of ADC2 inserted sequence 5 conversion only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER0_TRGO0_IOC: trigger input source TIMER0 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER7_TRGO0_IOC: trigger input source TIMER7 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER19_TRGO0_IOC: trigger input source TIMER19 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER20_TRGO0_IOC: trigger input source TIMER20 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER60_TRGO0_IOC: trigger input source TIMER60 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER61_TRGO0_IOC: trigger input source TIMER61 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER62_TRGO0_IOC: trigger input source TIMER62 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER63_TRGO0_IOC: trigger input source TIMER63 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER1_TRGO0_IOC: trigger input source TIMER1 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER2_TRGO0_IOC: trigger input source TIMER2 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER5_TRGO0_IOC: trigger input source TIMER5 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER5_TRGO1_IOC: trigger input source TIMER5 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER5_TRGO2_IOC: trigger input source TIMER5 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER5_TRGO3_IOC: trigger input source TIMER5 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER6_TRGO0_IOC: trigger input source TIMER6 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER6_TRGO1_IOC: trigger input source TIMER6 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER6_TRGO2_IOC: trigger input source TIMER6 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_INPUT_TIMER6_TRGO3_IOC: trigger input source TIMER6 TRGO0 signal to IOC only available in GD32A72x and GD32A74x
    \param[out] none
    \retval     none
*/
void trigsel_init(trigsel_periph_enum target_periph, trigsel_source_enum trigger_source)
{
    /* if register write is enabled, set trigger source to target peripheral */
    if (RESET == trigsel_register_lock_get(target_periph)){
        TRIGSEL_TARGET_REG(target_periph) &= ~TRIGSEL_TARGET_PERIPH_MASK(target_periph);
        TRIGSEL_TARGET_REG(target_periph) |= ((uint32_t)trigger_source << TRIGSEL_TARGET_PERIPH_SHIFT(target_periph)) & TRIGSEL_TARGET_PERIPH_MASK(target_periph);
    }
    
}

/*!
    \brief      get the trigger input signal for target peripheral
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT8: output target peripheral TRIGSEL_OUT8 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT9: output target peripheral TRIGSEL_OUT9 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT10: output target peripheral TRIGSEL_OUT10 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT11: output target peripheral TRIGSEL_OUT11 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT12: output target peripheral TRIGSEL_OUT12 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT13: output target peripheral TRIGSEL_OUT13 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT14: output target peripheral TRIGSEL_OUT14 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT15: output target peripheral TRIGSEL_OUT15 pin
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR0: output target peripheral IOC monitor0 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR1: output target peripheral IOC monitor1 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR2: output target peripheral IOC monitor2 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR3: output target peripheral IOC monitor3 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR4: output target peripheral IOC monitor4 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR5: output target peripheral IOC monitor5 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR6: output target peripheral IOC monitor6 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR7: output target peripheral IOC monitor7 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE0: output target peripheral IOC reference0 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE1: output target peripheral IOC reference1 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE2: output target peripheral IOC reference2 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE3: output target peripheral IOC reference3 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE4: output target peripheral IOC reference4 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE5: output target peripheral IOC reference5 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE6: output target peripheral IOC reference6 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE7: output target peripheral IOC reference7 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN3_EX_TIME_TICK: output target peripheral CAN3_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN4_EX_TIME_TICK: output target peripheral CAN4_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN5_EX_TIME_TICK: output target peripheral CAN5_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN6_EX_TIME_TICK: output target peripheral CAN6_EX_TIME_TICK only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CAN7_EX_TIME_TICK: output target peripheral CAN7_EX_TIME_TICK only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI0: output target peripheral TIMER0_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI0: output target peripheral TIMER1_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI0: output target peripheral TIMER2_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI0: output target peripheral TIMER7_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER19_ITI0: output target peripheral TIMER19_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER20_ITI0: output target peripheral TIMER20_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER60_ITI0: output target peripheral TIMER60_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER61_ITI0: output target peripheral TIMER61_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER62_ITI0: output target peripheral TIMER62_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER63_ITI0: output target peripheral TIMER63_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN3: output target peripheral TIMER0_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN3: output target peripheral TIMER7_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN0: output target peripheral TIMER19_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN1: output target peripheral TIMER19_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN2: output target peripheral TIMER19_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN3: output target peripheral TIMER19_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN0: output target peripheral TIMER20_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN1: output target peripheral TIMER20_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN2: output target peripheral TIMER20_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN3: output target peripheral TIMER20_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN0: output target peripheral TIMER60_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN1: output target peripheral TIMER60_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN2: output target peripheral TIMER60_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN3: output target peripheral TIMER60_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN0: output target peripheral TIMER61_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN1: output target peripheral TIMER61_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN2: output target peripheral TIMER61_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN3: output target peripheral TIMER61_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN0: output target peripheral TIMER62_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN1: output target peripheral TIMER62_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN2: output target peripheral TIMER62_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN3: output target peripheral TIMER62_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN0: output target peripheral TIMER63_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN1: output target peripheral TIMER63_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN2: output target peripheral TIMER63_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN3: output target peripheral TIMER63_BRKIN3
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG0: output target peripheral MFCOM external trigger 0 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG1: output target peripheral MFCOM external trigger 1 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG2: output target peripheral MFCOM external trigger 2 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG3: output target peripheral MFCOM external trigger 3 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CM7_0_RXEV: output target peripheral CM7_0_RXEV
      \arg        TRIGSEL_OUTPUT_CM7_1_RXEV: output target peripheral CM7_1_RXEV
      \arg        TRIGSEL_OUTPUT_DAC0_OUT0_EXTRG: output target peripheral DAC0_OUT0 external trigger
      \arg        TRIGSEL_OUTPUT_DAC1_OUT0_EXTRG: output target peripheral DAC1_OUT0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_ROUTRG : output target peripheral ADC0 routine sequence external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS0TRG: output target peripheral ADC0 inserted sequence 0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS1TRG: output target peripheral ADC0 inserted sequence 1 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS2TRG: output target peripheral ADC0 inserted sequence 2 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS3TRG: output target peripheral ADC0 inserted sequence 3 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS4TRG: output target peripheral ADC0 inserted sequence 4 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS5TRG: output target peripheral ADC0 inserted sequence 5 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_ROUTRG : output target peripheral ADC1 routine sequence external trigger 
      \arg        TRIGSEL_OUTPUT_ADC1_INS0TRG: output target peripheral ADC1 inserted sequence 0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS1TRG: output target peripheral ADC1 inserted sequence 1 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS2TRG: output target peripheral ADC1 inserted sequence 2 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS3TRG: output target peripheral ADC1 inserted sequence 3 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS4TRG: output target peripheral ADC1 inserted sequence 4 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS5TRG: output target peripheral ADC1 inserted sequence 5 external trigger
      \arg        TRIGSEL_OUTPUT_ADC2_ROUTRG : output target peripheral ADC2 routine sequence external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS0TRG: output target peripheral ADC2 inserted sequence 0 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS1TRG: output target peripheral ADC2 inserted sequence 1 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS2TRG: output target peripheral ADC2 inserted sequence 2 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS3TRG: output target peripheral ADC2 inserted sequence 3 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS4TRG: output target peripheral ADC2 inserted sequence 4 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS5TRG: output target peripheral ADC2 inserted sequence 5 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_SPI0_TRIG: output target peripheral SPI0 trigger
      \arg        TRIGSEL_OUTPUT_SPI1_TRIG: output target peripheral SPI1 trigger
      \arg        TRIGSEL_OUTPUT_SPI2_TRIG: output target peripheral SPI2 trigger
      \arg        TRIGSEL_OUTPUT_SPI3_TRIG: output target peripheral SPI3 trigger
      \arg        TRIGSEL_OUTPUT_SPI4_TRIG: output target peripheral SPI4 trigger
      \arg        TRIGSEL_OUTPUT_SPI5_TRIG: output target peripheral SPI5 trigger
      \arg        TRIGSEL_OUTPUT_SPI6_TRIG: output target peripheral SPI6 trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_SPI7_TRIG: output target peripheral SPI7 trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_TIMER_ETI0: output target peripheral TIMER_ETI0
      \arg        TRIGSEL_OUTPUT_TIMER_ETI1: output target peripheral TIMER_ETI1
      \arg        TRIGSEL_OUTPUT_TIMER_ETI2: output target peripheral TIMER_ETI2
      \arg        TRIGSEL_OUTPUT_LINFLEXD0_TRIG: output target peripheral LINFlexD0 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD1_TRIG: output target peripheral LINFlexD1 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD2_TRIG: output target peripheral LINFlexD2 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD3_TRIG: output target peripheral LINFlexD3 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD4_TRIG: output target peripheral LINFlexD4 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD5_TRIG: output target peripheral LINFlexD5 trigger
    \param[out] none
    \retval  trigger_source: trigger source value(0~218)
*/
trigsel_source_enum trigsel_trigger_source_get(trigsel_periph_enum target_periph)
{
    trigsel_source_enum trigger_source;
    uint32_t trigger_sourcetemp;

    trigger_sourcetemp = (TRIGSEL_TARGET_REG(target_periph) & TRIGSEL_TARGET_PERIPH_MASK(target_periph)) >> TRIGSEL_TARGET_PERIPH_SHIFT(target_periph);
    trigger_source = (trigsel_source_enum)(trigger_sourcetemp);

    return trigger_source;
}

/*!
    \brief      lock the trigger register
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT8: output target peripheral TRIGSEL_OUT8 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT9: output target peripheral TRIGSEL_OUT9 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT10: output target peripheral TRIGSEL_OUT10 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT11: output target peripheral TRIGSEL_OUT11 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT12: output target peripheral TRIGSEL_OUT12 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT13: output target peripheral TRIGSEL_OUT13 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT14: output target peripheral TRIGSEL_OUT14 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT15: output target peripheral TRIGSEL_OUT15 pin
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR0: output target peripheral IOC monitor0 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR1: output target peripheral IOC monitor1 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR2: output target peripheral IOC monitor2 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR3: output target peripheral IOC monitor3 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR4: output target peripheral IOC monitor4 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR5: output target peripheral IOC monitor5 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR6: output target peripheral IOC monitor6 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR7: output target peripheral IOC monitor7 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE0: output target peripheral IOC reference0 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE1: output target peripheral IOC reference1 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE2: output target peripheral IOC reference2 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE3: output target peripheral IOC reference3 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE4: output target peripheral IOC reference4 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE5: output target peripheral IOC reference5 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE6: output target peripheral IOC reference6 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE7: output target peripheral IOC reference7 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN3_EX_TIME_TICK: output target peripheral CAN3_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN4_EX_TIME_TICK: output target peripheral CAN4_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN5_EX_TIME_TICK: output target peripheral CAN5_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN6_EX_TIME_TICK: output target peripheral CAN6_EX_TIME_TICK only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CAN7_EX_TIME_TICK: output target peripheral CAN7_EX_TIME_TICK only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI0: output target peripheral TIMER0_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI0: output target peripheral TIMER1_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI0: output target peripheral TIMER2_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI0: output target peripheral TIMER7_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER19_ITI0: output target peripheral TIMER19_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER20_ITI0: output target peripheral TIMER20_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER60_ITI0: output target peripheral TIMER60_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER61_ITI0: output target peripheral TIMER61_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER62_ITI0: output target peripheral TIMER62_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER63_ITI0: output target peripheral TIMER63_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN3: output target peripheral TIMER0_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN3: output target peripheral TIMER7_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN0: output target peripheral TIMER19_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN1: output target peripheral TIMER19_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN2: output target peripheral TIMER19_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN3: output target peripheral TIMER19_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN0: output target peripheral TIMER20_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN1: output target peripheral TIMER20_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN2: output target peripheral TIMER20_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN3: output target peripheral TIMER20_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN0: output target peripheral TIMER60_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN1: output target peripheral TIMER60_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN2: output target peripheral TIMER60_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN3: output target peripheral TIMER60_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN0: output target peripheral TIMER61_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN1: output target peripheral TIMER61_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN2: output target peripheral TIMER61_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN3: output target peripheral TIMER61_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN0: output target peripheral TIMER62_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN1: output target peripheral TIMER62_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN2: output target peripheral TIMER62_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN3: output target peripheral TIMER62_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN0: output target peripheral TIMER63_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN1: output target peripheral TIMER63_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN2: output target peripheral TIMER63_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN3: output target peripheral TIMER63_BRKIN3
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG0: output target peripheral MFCOM external trigger 0 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG1: output target peripheral MFCOM external trigger 1 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG2: output target peripheral MFCOM external trigger 2 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG3: output target peripheral MFCOM external trigger 3 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CM7_0_RXEV: output target peripheral CM7_0_RXEV
      \arg        TRIGSEL_OUTPUT_CM7_1_RXEV: output target peripheral CM7_1_RXEV
      \arg        TRIGSEL_OUTPUT_DAC0_OUT0_EXTRG: output target peripheral DAC0_OUT0 external trigger
      \arg        TRIGSEL_OUTPUT_DAC1_OUT0_EXTRG: output target peripheral DAC1_OUT0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_ROUTRG : output target peripheral ADC0 routine sequence external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS0TRG: output target peripheral ADC0 inserted sequence 0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS1TRG: output target peripheral ADC0 inserted sequence 1 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS2TRG: output target peripheral ADC0 inserted sequence 2 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS3TRG: output target peripheral ADC0 inserted sequence 3 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS4TRG: output target peripheral ADC0 inserted sequence 4 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS5TRG: output target peripheral ADC0 inserted sequence 5 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_ROUTRG : output target peripheral ADC1 routine sequence external trigger 
      \arg        TRIGSEL_OUTPUT_ADC1_INS0TRG: output target peripheral ADC1 inserted sequence 0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS1TRG: output target peripheral ADC1 inserted sequence 1 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS2TRG: output target peripheral ADC1 inserted sequence 2 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS3TRG: output target peripheral ADC1 inserted sequence 3 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS4TRG: output target peripheral ADC1 inserted sequence 4 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS5TRG: output target peripheral ADC1 inserted sequence 5 external trigger
      \arg        TRIGSEL_OUTPUT_ADC2_ROUTRG : output target peripheral ADC2 routine sequence external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS0TRG: output target peripheral ADC2 inserted sequence 0 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS1TRG: output target peripheral ADC2 inserted sequence 1 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS2TRG: output target peripheral ADC2 inserted sequence 2 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS3TRG: output target peripheral ADC2 inserted sequence 3 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS4TRG: output target peripheral ADC2 inserted sequence 4 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS5TRG: output target peripheral ADC2 inserted sequence 5 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_SPI0_TRIG: output target peripheral SPI0 trigger
      \arg        TRIGSEL_OUTPUT_SPI1_TRIG: output target peripheral SPI1 trigger
      \arg        TRIGSEL_OUTPUT_SPI2_TRIG: output target peripheral SPI2 trigger
      \arg        TRIGSEL_OUTPUT_SPI3_TRIG: output target peripheral SPI3 trigger
      \arg        TRIGSEL_OUTPUT_SPI4_TRIG: output target peripheral SPI4 trigger
      \arg        TRIGSEL_OUTPUT_SPI5_TRIG: output target peripheral SPI5 trigger
      \arg        TRIGSEL_OUTPUT_SPI6_TRIG: output target peripheral SPI6 trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_SPI7_TRIG: output target peripheral SPI7 trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_TIMER_ETI0: output target peripheral TIMER_ETI0
      \arg        TRIGSEL_OUTPUT_TIMER_ETI1: output target peripheral TIMER_ETI1
      \arg        TRIGSEL_OUTPUT_TIMER_ETI2: output target peripheral TIMER_ETI2
      \arg        TRIGSEL_OUTPUT_LINFLEXD0_TRIG: output target peripheral LINFlexD0 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD1_TRIG: output target peripheral LINFlexD1 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD2_TRIG: output target peripheral LINFlexD2 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD3_TRIG: output target peripheral LINFlexD3 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD4_TRIG: output target peripheral LINFlexD4 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD5_TRIG: output target peripheral LINFlexD5 trigger
    \param[out] none
    \retval     none
*/
void trigsel_register_lock_set(trigsel_periph_enum target_periph)
{
    /*!< lock target peripheral register */
    TRIGSEL_TARGET_REG(target_periph) |= TRIGSEL_TARGET_LK;
}

/*!
    \brief      get the trigger register lock status
    \param[in]  target_periph: target peripheral value
                only one parameter can be selected which is shown as below:
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT0: output target peripheral TRIGSEL_OUT0 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT1: output target peripheral TRIGSEL_OUT1 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT2: output target peripheral TRIGSEL_OUT2 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT3: output target peripheral TRIGSEL_OUT3 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT4: output target peripheral TRIGSEL_OUT4 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT5: output target peripheral TRIGSEL_OUT5 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT6: output target peripheral TRIGSEL_OUT6 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT7: output target peripheral TRIGSEL_OUT7 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT8: output target peripheral TRIGSEL_OUT8 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT9: output target peripheral TRIGSEL_OUT9 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT10: output target peripheral TRIGSEL_OUT10 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT11: output target peripheral TRIGSEL_OUT11 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT12: output target peripheral TRIGSEL_OUT12 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT13: output target peripheral TRIGSEL_OUT13 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT14: output target peripheral TRIGSEL_OUT14 pin
      \arg        TRIGSEL_OUTPUT_TRIGSEL_OUT15: output target peripheral TRIGSEL_OUT15 pin
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR0: output target peripheral IOC monitor0 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR1: output target peripheral IOC monitor1 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR2: output target peripheral IOC monitor2 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR3: output target peripheral IOC monitor3 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR4: output target peripheral IOC monitor4 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR5: output target peripheral IOC monitor5 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR6: output target peripheral IOC monitor6 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_MONITOR7: output target peripheral IOC monitor7 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE0: output target peripheral IOC reference0 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE1: output target peripheral IOC reference1 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE2: output target peripheral IOC reference2 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE3: output target peripheral IOC reference3 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE4: output target peripheral IOC reference4 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE5: output target peripheral IOC reference5 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE6: output target peripheral IOC reference6 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_IOC_REFERENCE7: output target peripheral IOC reference7 signal only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK: output target peripheral CAN0_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK: output target peripheral CAN1_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK: output target peripheral CAN2_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN3_EX_TIME_TICK: output target peripheral CAN3_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN4_EX_TIME_TICK: output target peripheral CAN4_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN5_EX_TIME_TICK: output target peripheral CAN5_EX_TIME_TICK
      \arg        TRIGSEL_OUTPUT_CAN6_EX_TIME_TICK: output target peripheral CAN6_EX_TIME_TICK only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CAN7_EX_TIME_TICK: output target peripheral CAN7_EX_TIME_TICK only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_TIMER0_ITI0: output target peripheral TIMER0_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER1_ITI0: output target peripheral TIMER1_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER2_ITI0: output target peripheral TIMER2_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER7_ITI0: output target peripheral TIMER7_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER19_ITI0: output target peripheral TIMER19_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER20_ITI0: output target peripheral TIMER20_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER60_ITI0: output target peripheral TIMER60_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER61_ITI0: output target peripheral TIMER61_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER62_ITI0: output target peripheral TIMER62_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER63_ITI0: output target peripheral TIMER63_ITI0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN0: output target peripheral TIMER0_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN1: output target peripheral TIMER0_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN2: output target peripheral TIMER0_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER0_BRKIN3: output target peripheral TIMER0_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN0: output target peripheral TIMER7_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN1: output target peripheral TIMER7_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN2: output target peripheral TIMER7_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER7_BRKIN3: output target peripheral TIMER7_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN0: output target peripheral TIMER19_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN1: output target peripheral TIMER19_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN2: output target peripheral TIMER19_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER19_BRKIN3: output target peripheral TIMER19_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN0: output target peripheral TIMER20_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN1: output target peripheral TIMER20_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN2: output target peripheral TIMER20_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER20_BRKIN3: output target peripheral TIMER20_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN0: output target peripheral TIMER60_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN1: output target peripheral TIMER60_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN2: output target peripheral TIMER60_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER60_BRKIN3: output target peripheral TIMER60_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN0: output target peripheral TIMER61_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN1: output target peripheral TIMER61_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN2: output target peripheral TIMER61_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER61_BRKIN3: output target peripheral TIMER61_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN0: output target peripheral TIMER62_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN1: output target peripheral TIMER62_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN2: output target peripheral TIMER62_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER62_BRKIN3: output target peripheral TIMER62_BRKIN3
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN0: output target peripheral TIMER63_BRKIN0
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN1: output target peripheral TIMER63_BRKIN1
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN2: output target peripheral TIMER63_BRKIN2
      \arg        TRIGSEL_OUTPUT_TIMER63_BRKIN3: output target peripheral TIMER63_BRKIN3
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG0: output target peripheral MFCOM external trigger 0 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG1: output target peripheral MFCOM external trigger 1 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG2: output target peripheral MFCOM external trigger 2 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_MFCOM_TRIG3: output target peripheral MFCOM external trigger 3 only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_CM7_0_RXEV: output target peripheral CM7_0_RXEV
      \arg        TRIGSEL_OUTPUT_CM7_1_RXEV: output target peripheral CM7_1_RXEV
      \arg        TRIGSEL_OUTPUT_DAC0_OUT0_EXTRG: output target peripheral DAC0_OUT0 external trigger
      \arg        TRIGSEL_OUTPUT_DAC1_OUT0_EXTRG: output target peripheral DAC1_OUT0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_ROUTRG : output target peripheral ADC0 routine sequence external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS0TRG: output target peripheral ADC0 inserted sequence 0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS1TRG: output target peripheral ADC0 inserted sequence 1 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS2TRG: output target peripheral ADC0 inserted sequence 2 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS3TRG: output target peripheral ADC0 inserted sequence 3 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS4TRG: output target peripheral ADC0 inserted sequence 4 external trigger
      \arg        TRIGSEL_OUTPUT_ADC0_INS5TRG: output target peripheral ADC0 inserted sequence 5 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_ROUTRG : output target peripheral ADC1 routine sequence external trigger 
      \arg        TRIGSEL_OUTPUT_ADC1_INS0TRG: output target peripheral ADC1 inserted sequence 0 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS1TRG: output target peripheral ADC1 inserted sequence 1 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS2TRG: output target peripheral ADC1 inserted sequence 2 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS3TRG: output target peripheral ADC1 inserted sequence 3 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS4TRG: output target peripheral ADC1 inserted sequence 4 external trigger
      \arg        TRIGSEL_OUTPUT_ADC1_INS5TRG: output target peripheral ADC1 inserted sequence 5 external trigger
      \arg        TRIGSEL_OUTPUT_ADC2_ROUTRG : output target peripheral ADC2 routine sequence external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS0TRG: output target peripheral ADC2 inserted sequence 0 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS1TRG: output target peripheral ADC2 inserted sequence 1 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS2TRG: output target peripheral ADC2 inserted sequence 2 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS3TRG: output target peripheral ADC2 inserted sequence 3 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS4TRG: output target peripheral ADC2 inserted sequence 4 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_ADC2_INS5TRG: output target peripheral ADC2 inserted sequence 5 external trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_SPI0_TRIG: output target peripheral SPI0 trigger
      \arg        TRIGSEL_OUTPUT_SPI1_TRIG: output target peripheral SPI1 trigger
      \arg        TRIGSEL_OUTPUT_SPI2_TRIG: output target peripheral SPI2 trigger
      \arg        TRIGSEL_OUTPUT_SPI3_TRIG: output target peripheral SPI3 trigger
      \arg        TRIGSEL_OUTPUT_SPI4_TRIG: output target peripheral SPI4 trigger
      \arg        TRIGSEL_OUTPUT_SPI5_TRIG: output target peripheral SPI5 trigger
      \arg        TRIGSEL_OUTPUT_SPI6_TRIG: output target peripheral SPI6 trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_SPI7_TRIG: output target peripheral SPI7 trigger only available in GD32A72x and GD32A74x
      \arg        TRIGSEL_OUTPUT_TIMER_ETI0: output target peripheral TIMER_ETI0
      \arg        TRIGSEL_OUTPUT_TIMER_ETI1: output target peripheral TIMER_ETI1
      \arg        TRIGSEL_OUTPUT_TIMER_ETI2: output target peripheral TIMER_ETI2
      \arg        TRIGSEL_OUTPUT_LINFLEXD0_TRIG: output target peripheral LINFlexD0 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD1_TRIG: output target peripheral LINFlexD1 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD2_TRIG: output target peripheral LINFlexD2 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD3_TRIG: output target peripheral LINFlexD3 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD4_TRIG: output target peripheral LINFlexD4 trigger
      \arg        TRIGSEL_OUTPUT_LINFLEXD5_TRIG: output target peripheral LINFlexD5 trigger
    \param[out] none
    \retval     SET or RESET
*/
FlagStatus trigsel_register_lock_get(trigsel_periph_enum target_periph)
{
    FlagStatus reval;

    if(0U != (TRIGSEL_TARGET_REG(target_periph) & TRIGSEL_TARGET_LK)){
        reval = SET;
    } else {
        reval = RESET;
    }
    
    return reval;
}
