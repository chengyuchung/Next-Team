/*!
    \file    gd32a7xx_trigsel.h
    \brief   definitions for the TRIGSEL

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

#ifndef GD32A7XX_TRIGSEL_H
#define GD32A7XX_TRIGSEL_H

#include "gd32a7xx.h"

/* TRIGSEL definitions */
#define TRIGSEL                                     TRIGSEL_BASE                          /*!< TRIGSEL base address */

/* register definitions */
#define TRIGSEL_EXTOUT_0                            REG32((TRIGSEL) + 0x00000000U)        /*!< TRIGSEL trigger selection for EXTOUT register 0 */
#define TRIGSEL_EXTOUT_1                            REG32((TRIGSEL) + 0x00000004U)        /*!< TRIGSEL trigger selection for EXTOUT register 1 */
#define TRIGSEL_EXTOUT_2                            REG32((TRIGSEL) + 0x00000008U)        /*!< TRIGSEL trigger selection for EXTOUT register 2 */
#define TRIGSEL_EXTOUT_3                            REG32((TRIGSEL) + 0x0000000CU)        /*!< TRIGSEL trigger selection for EXTOUT register 3 */
#define TRIGSEL_EXTOUT_4                            REG32((TRIGSEL) + 0x00000010U)        /*!< TRIGSEL trigger selection for EXTOUT register 4 */
#define TRIGSEL_EXTOUT_5                            REG32((TRIGSEL) + 0x00000014U)        /*!< TRIGSEL trigger selection for EXTOUT register 5 */
#define TRIGSEL_EXTOUT_6                            REG32((TRIGSEL) + 0x00000018U)        /*!< TRIGSEL trigger selection for EXTOUT register 6 */
#define TRIGSEL_EXTOUT_7                            REG32((TRIGSEL) + 0x0000001CU)        /*!< TRIGSEL trigger selection for EXTOUT register 7 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define TRIGSEL_IOC_0                               REG32((TRIGSEL) + 0x00000020U)        /*!< TRIGSEL trigger selection for IOC register 0 */
#define TRIGSEL_IOC_1                               REG32((TRIGSEL) + 0x00000024U)        /*!< TRIGSEL trigger selection for IOC register 1 */
#define TRIGSEL_IOC_2                               REG32((TRIGSEL) + 0x00000028U)        /*!< TRIGSEL trigger selection for IOC register 2 */
#define TRIGSEL_IOC_3                               REG32((TRIGSEL) + 0x0000002CU)        /*!< TRIGSEL trigger selection for IOC register 3 */
#define TRIGSEL_IOC_4                               REG32((TRIGSEL) + 0x00000030U)        /*!< TRIGSEL trigger selection for IOC register 4 */
#define TRIGSEL_IOC_5                               REG32((TRIGSEL) + 0x00000034U)        /*!< TRIGSEL trigger selection for IOC register 5 */
#define TRIGSEL_IOC_6                               REG32((TRIGSEL) + 0x00000038U)        /*!< TRIGSEL trigger selection for IOC register 6 */
#define TRIGSEL_IOC_7                               REG32((TRIGSEL) + 0x0000003CU)        /*!< TRIGSEL trigger selection for IOC register 7 */
#define TRIGSEL_CAN_0                               REG32((TRIGSEL) + 0x00000040U)        /*!< TRIGSEL trigger selection for CAN register 0 */
#define TRIGSEL_CAN_1                               REG32((TRIGSEL) + 0x00000044U)        /*!< TRIGSEL trigger selection for CAN register 1 */
#define TRIGSEL_CAN_2                               REG32((TRIGSEL) + 0x00000048U)        /*!< TRIGSEL trigger selection for CAN register 2 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define TRIGSEL_TIMER0ITI0                          REG32((TRIGSEL) + 0x0000005CU)        /*!< TRIGSEL trigger selection for TIMER0_ITI0 register */
#define TRIGSEL_TIMER1ITI0                          REG32((TRIGSEL) + 0x00000060U)        /*!< TRIGSEL trigger selection for TIMER1_ITI0 register */
#define TRIGSEL_TIMER2ITI0                          REG32((TRIGSEL) + 0x00000064U)        /*!< TRIGSEL trigger selection for TIMER2_ITI0 register */
#define TRIGSEL_TIMER7ITI0                          REG32((TRIGSEL) + 0x00000068U)        /*!< TRIGSEL trigger selection for TIMER7_ITI0 register */
#define TRIGSEL_TIMER19ITI0                         REG32((TRIGSEL) + 0x0000006CU)        /*!< TRIGSEL trigger selection for TIMER19_ITI0 register */
#define TRIGSEL_TIMER20ITI0                         REG32((TRIGSEL) + 0x00000070U)        /*!< TRIGSEL trigger selection for TIMER20_ITI0 register */
#define TRIGSEL_TIMER60ITI0                         REG32((TRIGSEL) + 0x00000074U)        /*!< TRIGSEL trigger selection for TIMER60_ITI0 register */
#define TRIGSEL_TIMER61ITI0                         REG32((TRIGSEL) + 0x00000078U)        /*!< TRIGSEL trigger selection for TIMER61_ITI0 register */
#define TRIGSEL_TIMER62ITI0                         REG32((TRIGSEL) + 0x0000007CU)        /*!< TRIGSEL trigger selection for TIMER62_ITI0 register */
#define TRIGSEL_TIMER63ITI0                         REG32((TRIGSEL) + 0x00000080U)        /*!< TRIGSEL trigger selection for TIMER63_ITI0 register */
#define TRIGSEL_TIMER0BRKIN_0                       REG32((TRIGSEL) + 0x00000084U)        /*!< TRIGSEL trigger selection for TIMER0_BRKIN register 0 */
#define TRIGSEL_TIMER0BRKIN_1                       REG32((TRIGSEL) + 0x00000084U)        /*!< TRIGSEL trigger selection for TIMER0_BRKIN register 1 */
#define TRIGSEL_TIMER7BRKIN_0                       REG32((TRIGSEL) + 0x0000008CU)        /*!< TRIGSEL trigger selection for TIMER7_BRKIN register 0 */
#define TRIGSEL_TIMER7BRKIN_1                       REG32((TRIGSEL) + 0x00000090U)        /*!< TRIGSEL trigger selection for TIMER7_BRKIN register 1 */
#define TRIGSEL_TIMER19BRKIN_0                      REG32((TRIGSEL) + 0x00000094U)        /*!< TRIGSEL trigger selection for TIMER19_BRKIN register 0 */
#define TRIGSEL_TIMER19BRKIN_1                      REG32((TRIGSEL) + 0x00000098U)        /*!< TRIGSEL trigger selection for TIMER19_BRKIN register 1 */
#define TRIGSEL_TIMER20BRKIN_0                      REG32((TRIGSEL) + 0x0000009CU)        /*!< TRIGSEL trigger selection for TIMER20_BRKIN register 0 */
#define TRIGSEL_TIMER20BRKIN_1                      REG32((TRIGSEL) + 0x000000A0U)        /*!< TRIGSEL trigger selection for TIMER20_BRKIN register 1 */
#define TRIGSEL_TIMER60BRKIN_0                      REG32((TRIGSEL) + 0x000000A4U)        /*!< TRIGSEL trigger selection for TIMER60_BRKIN register 0 */
#define TRIGSEL_TIMER60BRKIN_1                      REG32((TRIGSEL) + 0x000000A8U)        /*!< TRIGSEL trigger selection for TIMER60_BRKIN register 1 */
#define TRIGSEL_TIMER61BRKIN_0                      REG32((TRIGSEL) + 0x000000ACU)        /*!< TRIGSEL trigger selection for TIMER61_BRKIN register 0 */
#define TRIGSEL_TIMER61BRKIN_1                      REG32((TRIGSEL) + 0x000000B0U)        /*!< TRIGSEL trigger selection for TIMER61_BRKIN register 1 */
#define TRIGSEL_TIMER62BRKIN_0                      REG32((TRIGSEL) + 0x000000B4U)        /*!< TRIGSEL trigger selection for TIMER62_BRKIN register 0 */
#define TRIGSEL_TIMER62BRKIN_1                      REG32((TRIGSEL) + 0x000000B8U)        /*!< TRIGSEL trigger selection for TIMER62_BRKIN register 1 */
#define TRIGSEL_TIMER63BRKIN_0                      REG32((TRIGSEL) + 0x000000BCU)        /*!< TRIGSEL trigger selection for TIMER62_BRKIN register 0 */
#define TRIGSEL_TIMER63BRKIN_1                      REG32((TRIGSEL) + 0x000000C0U)        /*!< TRIGSEL trigger selection for TIMER62_BRKIN register 1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define TRIGSEL_MFCOM_0                             REG32((TRIGSEL) + 0x000000C4U)        /*!< TRIGSEL trigger selection for MFCOM register 0 */
#define TRIGSEL_MFCOM_1                             REG32((TRIGSEL) + 0x000000C8U)        /*!< TRIGSEL trigger selection for MFCOM register 1 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define TRIGSEL_CM7                                 REG32((TRIGSEL) + 0x000000CCU)        /*!< TRIGSEL trigger selection for CM7 register */
#define TRIGSEL_DAC                                 REG32((TRIGSEL) + 0x000000D0U)        /*!< TRIGSEL trigger selection for DAC register */
#define TRIGSEL_ADC0ROUTRG                          REG32((TRIGSEL) + 0x000000D4U)        /*!< TRIGSEL trigger selection for ADC0_ROUTRG register */
#define TRIGSEL_ADC0INSTRG_0                        REG32((TRIGSEL) + 0x000000D8U)        /*!< TRIGSEL trigger selection for ADC0_INSTRG register 0 */
#define TRIGSEL_ADC0INSTRG_1                        REG32((TRIGSEL) + 0x000000DCU)        /*!< TRIGSEL trigger selection for ADC0_INSTRG register 1 */
#define TRIGSEL_ADC1ROUTRG                          REG32((TRIGSEL) + 0x000000E0U)        /*!< TRIGSEL trigger selection for ADC1_ROUTRG register */
#define TRIGSEL_ADC1INSTRG_0                        REG32((TRIGSEL) + 0x000000E4U)        /*!< TRIGSEL trigger selection for ADC1_INSTRG register 0 */
#define TRIGSEL_ADC1INSTRG_1                        REG32((TRIGSEL) + 0x000000E8U)        /*!< TRIGSEL trigger selection for ADC1_INSTRG register 1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define TRIGSEL_ADC2ROUTRG                          REG32((TRIGSEL) + 0x000000ECU)        /*!< TRIGSEL trigger selection for ADC2_ROUTRG register */
#define TRIGSEL_ADC2INSTRG_0                        REG32((TRIGSEL) + 0x000000F0U)        /*!< TRIGSEL trigger selection for ADC2_INSTRG register 0 */
#define TRIGSEL_ADC2INSTRG_1                        REG32((TRIGSEL) + 0x000000F4U)        /*!< TRIGSEL trigger selection for ADC2_INSTRG register 1 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define TRIGSEL_SPI_0                               REG32((TRIGSEL) + 0x000000F8U)        /*!< TRIGSEL trigger selection for SPI register 0 */
#define TRIGSEL_SPI_1                               REG32((TRIGSEL) + 0x000000FCU)        /*!< TRIGSEL trigger selection for SPI register 1 */
#define TRIGSEL_SPI_2                               REG32((TRIGSEL) + 0x00000100U)        /*!< TRIGSEL trigger selection for SPI register 2 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define TRIGSEL_SPI_3                               REG32((TRIGSEL) + 0x00000104U)        /*!< TRIGSEL trigger selection for SPI register 3 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define TRIGSEL_TIMERETI                            REG32((TRIGSEL) + 0x00000108U)        /*!< TRIGSEL trigger selection for TIMETR_ETI register */
#if defined(GD32A711X_A712X)
#define TRIGSEL_LINFLEXD_0                          REG32((TRIGSEL) + 0x0000010CU)        /*!< TRIGSEL trigger selection for TRIGSEL_LINFLEXD register 0 */
#define TRIGSEL_LINFLEXD_1                          REG32((TRIGSEL) + 0x00000110U)        /*!< TRIGSEL trigger selection for TRIGSEL_LINFLEXD register 1 */
#define TRIGSEL_LINFLEXD_2                          REG32((TRIGSEL) + 0x00000114U)        /*!< TRIGSEL trigger selection for TRIGSEL_LINFLEXD register 2 */
#endif /* defined(GD32A711X_A712X) */

/* bits definitions */
#define TRIGSEL_TARGET_INSEL0                       BITS(0, 7)                            /*!< trigger input source selection for output0 */
#define TRIGSEL_TARGET_INSEL1                       BITS(8, 15)                           /*!< trigger input source selection for output1 */
#define TRIGSEL_TARGET_INSEL2                       BITS(16, 23)                          /*!< trigger input source selection for output2 */
#define TRIGSEL_TARGET_LK                           BIT(31)                               /*!< TRIGSEL register lock */

/* constants definitions */
/* trigger source definitions */
typedef enum
{
    TRIGSEL_INPUT_0                                 = ((uint8_t)0x00U),                   /*!< trigger input source 0 */
    TRIGSEL_INPUT_1                                 = ((uint8_t)0x01U),                   /*!< trigger input source 1 */
    TRIGSEL_INPUT_TRIGSEL_IN0                       = ((uint8_t)0x02U),                   /*!< trigger input source TRIGSEL_IN0 pin */
    TRIGSEL_INPUT_TRIGSEL_IN1                       = ((uint8_t)0x03U),                   /*!< trigger input source TRIGSEL_IN1 pin */
    TRIGSEL_INPUT_TRIGSEL_IN2                       = ((uint8_t)0x04U),                   /*!< trigger input source TRIGSEL_IN2 pin */
    TRIGSEL_INPUT_TRIGSEL_IN3                       = ((uint8_t)0x05U),                   /*!< trigger input source TRIGSEL_IN3 pin */
    TRIGSEL_INPUT_TRIGSEL_IN4                       = ((uint8_t)0x06U),                   /*!< trigger input source TRIGSEL_IN4 pin */
    TRIGSEL_INPUT_TRIGSEL_IN5                       = ((uint8_t)0x07U),                   /*!< trigger input source TRIGSEL_IN5 pin */
    TRIGSEL_INPUT_TRIGSEL_IN6                       = ((uint8_t)0x08U),                   /*!< trigger input source TRIGSEL_IN6 pin */
    TRIGSEL_INPUT_TRIGSEL_IN7                       = ((uint8_t)0x09U),                   /*!< trigger input source TRIGSEL_IN7 pin */
    TRIGSEL_INPUT_TRIGSEL_IN8                       = ((uint8_t)0x0AU),                   /*!< trigger input source TRIGSEL_IN8 pin */
    TRIGSEL_INPUT_TRIGSEL_IN9                       = ((uint8_t)0x0BU),                   /*!< trigger input source TRIGSEL_IN9 pin */
    TRIGSEL_INPUT_TRIGSEL_IN10                      = ((uint8_t)0x0CU),                   /*!< trigger input source TRIGSEL_IN10 pin */
    TRIGSEL_INPUT_TRIGSEL_IN11                      = ((uint8_t)0x0DU),                   /*!< trigger input source TRIGSEL_IN11 pin */
    TRIGSEL_INPUT_TRIGSEL_IN12                      = ((uint8_t)0x0EU),                   /*!< trigger input source TRIGSEL_IN12 pin */
    TRIGSEL_INPUT_TRIGSEL_IN13                      = ((uint8_t)0x0FU),                   /*!< trigger input source TRIGSEL_IN13 pin */
    TRIGSEL_INPUT_TRIGSEL_IN14                      = ((uint8_t)0x10U),                   /*!< trigger input source TRIGSEL_IN14 pin */
    TRIGSEL_INPUT_TRIGSEL_IN15                      = ((uint8_t)0x11U),                   /*!< trigger input source TRIGSEL_IN15 pin */
    TRIGSEL_INPUT_TIMER0_TRGO0                      = ((uint8_t)0x12U),                   /*!< trigger input source TIMER0 TRGO0 output */
    TRIGSEL_INPUT_TIMER0_CH0                        = ((uint8_t)0x13U),                   /*!< trigger input source TIMER0 CH0 output */
    TRIGSEL_INPUT_TIMER0_CH1                        = ((uint8_t)0x14U),                   /*!< trigger input source TIMER0 CH1 output */
    TRIGSEL_INPUT_TIMER0_CH2                        = ((uint8_t)0x15U),                   /*!< trigger input source TIMER0 CH2 output */
    TRIGSEL_INPUT_TIMER0_CH3                        = ((uint8_t)0x16U),                   /*!< trigger input source TIMER0 CH3 output */
    TRIGSEL_INPUT_TIMER0_MCH0                       = ((uint8_t)0x17U),                   /*!< trigger input source TIMER0 MCH0 output */
    TRIGSEL_INPUT_TIMER0_MCH1                       = ((uint8_t)0x18U),                   /*!< trigger input source TIMER0 MCH1 output */
    TRIGSEL_INPUT_TIMER0_MCH2                       = ((uint8_t)0x19U),                   /*!< trigger input source TIMER0 MCH2 output */
    TRIGSEL_INPUT_TIMER0_MCH3                       = ((uint8_t)0x1AU),                   /*!< trigger input source TIMER0 MCH3 output */
    TRIGSEL_INPUT_TIMER7_TRGO0                      = ((uint8_t)0x1BU),                   /*!< trigger input source TIMER7 TRGO0 output */
    TRIGSEL_INPUT_TIMER7_CH0                        = ((uint8_t)0x1CU),                   /*!< trigger input source TIMER7 CH0 output */
    TRIGSEL_INPUT_TIMER7_CH1                        = ((uint8_t)0x1DU),                   /*!< trigger input source TIMER7 CH1 output */
    TRIGSEL_INPUT_TIMER7_CH2                        = ((uint8_t)0x1EU),                   /*!< trigger input source TIMER7 CH2 output */
    TRIGSEL_INPUT_TIMER7_CH3                        = ((uint8_t)0x1FU),                   /*!< trigger input source TIMER7 CH3 output */
    TRIGSEL_INPUT_TIMER7_MCH0                       = ((uint8_t)0x20U),                   /*!< trigger input source TIMER7 MCH0 output */
    TRIGSEL_INPUT_TIMER7_MCH1                       = ((uint8_t)0x21U),                   /*!< trigger input source TIMER7 MCH1 output */
    TRIGSEL_INPUT_TIMER7_MCH2                       = ((uint8_t)0x22U),                   /*!< trigger input source TIMER7 MCH2 output */
    TRIGSEL_INPUT_TIMER7_MCH3                       = ((uint8_t)0x23U),                   /*!< trigger input source TIMER7 MCH3 output */
    TRIGSEL_INPUT_TIMER19_TRGO0                     = ((uint8_t)0x24U),                   /*!< trigger input source TIMER19 TRGO0 output */
    TRIGSEL_INPUT_TIMER19_CH0                       = ((uint8_t)0x25U),                   /*!< trigger input source TIMER19 CH0 output */
    TRIGSEL_INPUT_TIMER19_CH1                       = ((uint8_t)0x26U),                   /*!< trigger input source TIMER19 CH1 output */
    TRIGSEL_INPUT_TIMER19_CH2                       = ((uint8_t)0x27U),                   /*!< trigger input source TIMER19 CH2 output */
    TRIGSEL_INPUT_TIMER19_CH3                       = ((uint8_t)0x28U),                   /*!< trigger input source TIMER19 CH3 output */
    TRIGSEL_INPUT_TIMER19_MCH0                      = ((uint8_t)0x29U),                   /*!< trigger input source TIMER19 MCH0 output */
    TRIGSEL_INPUT_TIMER19_MCH1                      = ((uint8_t)0x2AU),                   /*!< trigger input source TIMER19 MCH1 output */
    TRIGSEL_INPUT_TIMER19_MCH2                      = ((uint8_t)0x2BU),                   /*!< trigger input source TIMER19 MCH2 output */
    TRIGSEL_INPUT_TIMER19_MCH3                      = ((uint8_t)0x2CU),                   /*!< trigger input source TIMER19 MCH3 output */
    TRIGSEL_INPUT_TIMER20_TRGO0                     = ((uint8_t)0x2DU),                   /*!< trigger input source TIMER20 TRGO0 output */
    TRIGSEL_INPUT_TIMER20_CH0                       = ((uint8_t)0x2EU),                   /*!< trigger input source TIMER20 CH0 output */
    TRIGSEL_INPUT_TIMER20_CH1                       = ((uint8_t)0x2FU),                   /*!< trigger input source TIMER20 CH1 output */
    TRIGSEL_INPUT_TIMER20_CH2                       = ((uint8_t)0x30U),                   /*!< trigger input source TIMER20 CH2 output */
    TRIGSEL_INPUT_TIMER20_CH3                       = ((uint8_t)0x31U),                   /*!< trigger input source TIMER20 CH3 output */
    TRIGSEL_INPUT_TIMER20_MCH0                      = ((uint8_t)0x32U),                   /*!< trigger input source TIMER20 MCH0 output */
    TRIGSEL_INPUT_TIMER20_MCH1                      = ((uint8_t)0x33U),                   /*!< trigger input source TIMER20 MCH1 output */
    TRIGSEL_INPUT_TIMER20_MCH2                      = ((uint8_t)0x34U),                   /*!< trigger input source TIMER20 MCH2 output */
    TRIGSEL_INPUT_TIMER20_MCH3                      = ((uint8_t)0x35U),                   /*!< trigger input source TIMER20 MCH3 output */
    TRIGSEL_INPUT_TIMER60_TRGO0                     = ((uint8_t)0x36U),                   /*!< trigger input source TIMER60 TRGO0 output */
    TRIGSEL_INPUT_TIMER60_CH0                       = ((uint8_t)0x37U),                   /*!< trigger input source TIMER60 CH0 output */
    TRIGSEL_INPUT_TIMER60_CH1                       = ((uint8_t)0x38U),                   /*!< trigger input source TIMER60 CH1 output */
    TRIGSEL_INPUT_TIMER60_CH2                       = ((uint8_t)0x39U),                   /*!< trigger input source TIMER60 CH2 output */
    TRIGSEL_INPUT_TIMER60_CH3                       = ((uint8_t)0x3AU),                   /*!< trigger input source TIMER60 CH3 output */
    TRIGSEL_INPUT_TIMER60_MCH0                      = ((uint8_t)0x3BU),                   /*!< trigger input source TIMER60 MCH0 output */
    TRIGSEL_INPUT_TIMER60_MCH1                      = ((uint8_t)0x3CU),                   /*!< trigger input source TIMER60 MCH1 output */
    TRIGSEL_INPUT_TIMER60_MCH2                      = ((uint8_t)0x3DU),                   /*!< trigger input source TIMER60 MCH2 output */
    TRIGSEL_INPUT_TIMER60_MCH3                      = ((uint8_t)0x3EU),                   /*!< trigger input source TIMER60 MCH3 output */
    TRIGSEL_INPUT_TIMER61_TRGO0                     = ((uint8_t)0x3FU),                   /*!< trigger input source TIMER61 TRGO0 output */
    TRIGSEL_INPUT_TIMER61_CH0                       = ((uint8_t)0x40U),                   /*!< trigger input source TIMER61 CH0 output */
    TRIGSEL_INPUT_TIMER61_CH1                       = ((uint8_t)0x41U),                   /*!< trigger input source TIMER61 CH1 output */
    TRIGSEL_INPUT_TIMER61_CH2                       = ((uint8_t)0x42U),                   /*!< trigger input source TIMER61 CH2 output */
    TRIGSEL_INPUT_TIMER61_CH3                       = ((uint8_t)0x43U),                   /*!< trigger input source TIMER61 CH3 output */
    TRIGSEL_INPUT_TIMER61_MCH0                      = ((uint8_t)0x44U),                   /*!< trigger input source TIMER61 MCH0 output */
    TRIGSEL_INPUT_TIMER61_MCH1                      = ((uint8_t)0x45U),                   /*!< trigger input source TIMER61 MCH1 output */
    TRIGSEL_INPUT_TIMER61_MCH2                      = ((uint8_t)0x46U),                   /*!< trigger input source TIMER61 MCH2 output */
    TRIGSEL_INPUT_TIMER61_MCH3                      = ((uint8_t)0x47U),                   /*!< trigger input source TIMER61 MCH3 output */
    TRIGSEL_INPUT_TIMER62_TRGO0                     = ((uint8_t)0x48U),                   /*!< trigger input source TIMER62 TRGO0 output */
    TRIGSEL_INPUT_TIMER62_CH0                       = ((uint8_t)0x49U),                   /*!< trigger input source TIMER62 CH0 output */
    TRIGSEL_INPUT_TIMER62_CH1                       = ((uint8_t)0x4AU),                   /*!< trigger input source TIMER62 CH1 output */
    TRIGSEL_INPUT_TIMER62_CH2                       = ((uint8_t)0x4BU),                   /*!< trigger input source TIMER62 CH2 output */
    TRIGSEL_INPUT_TIMER62_CH3                       = ((uint8_t)0x4CU),                   /*!< trigger input source TIMER62 CH3 output */
    TRIGSEL_INPUT_TIMER62_MCH0                      = ((uint8_t)0x4DU),                   /*!< trigger input source TIMER62 MCH0 output */
    TRIGSEL_INPUT_TIMER62_MCH1                      = ((uint8_t)0x4EU),                   /*!< trigger input source TIMER62 MCH1 output */
    TRIGSEL_INPUT_TIMER62_MCH2                      = ((uint8_t)0x4FU),                   /*!< trigger input source TIMER62 MCH2 output */
    TRIGSEL_INPUT_TIMER62_MCH3                      = ((uint8_t)0x50U),                   /*!< trigger input source TIMER62 MCH3 output */
    TRIGSEL_INPUT_TIMER63_TRGO0                     = ((uint8_t)0x51U),                   /*!< trigger input source TIMER63 TRGO0 output */
    TRIGSEL_INPUT_TIMER63_CH0                       = ((uint8_t)0x52U),                   /*!< trigger input source TIMER63 CH0 output */
    TRIGSEL_INPUT_TIMER63_CH1                       = ((uint8_t)0x53U),                   /*!< trigger input source TIMER63 CH1 output */
    TRIGSEL_INPUT_TIMER63_CH2                       = ((uint8_t)0x54U),                   /*!< trigger input source TIMER63 CH2 output */
    TRIGSEL_INPUT_TIMER63_CH3                       = ((uint8_t)0x55U),                   /*!< trigger input source TIMER63 CH3 output */
    TRIGSEL_INPUT_TIMER63_MCH0                      = ((uint8_t)0x56U),                   /*!< trigger input source TIMER63 MCH0 output */
    TRIGSEL_INPUT_TIMER63_MCH1                      = ((uint8_t)0x57U),                   /*!< trigger input source TIMER63 MCH1 output */
    TRIGSEL_INPUT_TIMER63_MCH2                      = ((uint8_t)0x58U),                   /*!< trigger input source TIMER63 MCH2 output */
    TRIGSEL_INPUT_TIMER63_MCH3                      = ((uint8_t)0x59U),                   /*!< trigger input source TIMER63 MCH3 output */
    TRIGSEL_INPUT_TIMER1_TRGO0                      = ((uint8_t)0x5AU),                   /*!< trigger input source TIMER1 TRGO0 output */
    TRIGSEL_INPUT_TIMER1_CH0                        = ((uint8_t)0x5BU),                   /*!< trigger input source TIMER1 CH0 output */
    TRIGSEL_INPUT_TIMER1_CH1                        = ((uint8_t)0x5CU),                   /*!< trigger input source TIMER1 CH1 output */
    TRIGSEL_INPUT_TIMER1_CH2                        = ((uint8_t)0x5DU),                   /*!< trigger input source TIMER1 CH2 output */
    TRIGSEL_INPUT_TIMER1_CH3                        = ((uint8_t)0x5EU),                   /*!< trigger input source TIMER1 CH3 output */
    TRIGSEL_INPUT_TIMER2_TRGO0                      = ((uint8_t)0x5FU),                   /*!< trigger input source TIMER2 TRGO0 output */
    TRIGSEL_INPUT_TIMER2_CH0                        = ((uint8_t)0x60U),                   /*!< trigger input source TIMER2 CH0 output */
    TRIGSEL_INPUT_TIMER2_CH1                        = ((uint8_t)0x61U),                   /*!< trigger input source TIMER2 CH1 output */
    TRIGSEL_INPUT_TIMER2_CH2                        = ((uint8_t)0x62U),                   /*!< trigger input source TIMER2 CH2 output */
    TRIGSEL_INPUT_TIMER2_CH3                        = ((uint8_t)0x63U),                   /*!< trigger input source TIMER2 CH3 output */
    TRIGSEL_INPUT_TIMER5_TRGO0                      = ((uint8_t)0x64U),                   /*!< trigger input source TIMER5 TRGO0 output */
    TRIGSEL_INPUT_TIMER5_TRGO1                      = ((uint8_t)0x65U),                   /*!< trigger input source TIMER5 TRGO1 output */
    TRIGSEL_INPUT_TIMER5_TRGO2                      = ((uint8_t)0x66U),                   /*!< trigger input source TIMER5 TRGO2 output */
    TRIGSEL_INPUT_TIMER5_TRGO3                      = ((uint8_t)0x67U),                   /*!< trigger input source TIMER5 TRGO3 output */
    TRIGSEL_INPUT_TIMER6_TRGO0                      = ((uint8_t)0x69U),                   /*!< trigger input source TIMER6 TRGO0 output */
    TRIGSEL_INPUT_TIMER6_TRGO1                      = ((uint8_t)0x6AU),                   /*!< trigger input source TIMER6 TRGO1 output */
    TRIGSEL_INPUT_TIMER6_TRGO2                      = ((uint8_t)0x6BU),                   /*!< trigger input source TIMER6 TRGO2 output */
    TRIGSEL_INPUT_TIMER6_TRGO3                      = ((uint8_t)0x6CU),                   /*!< trigger input source TIMER6 TRGO3 output */
    TRIGSEL_INPUT_CMP0_OUT                          = ((uint8_t)0x6EU),                   /*!< trigger input source CMP0 output */
    TRIGSEL_INPUT_CMP1_OUT                          = ((uint8_t)0x6FU),                   /*!< trigger input source CMP1 output */
    TRIGSEL_INPUT_BKP_TAMPER                        = ((uint8_t)0x70U),                   /*!< trigger input source BKP tamper interrupt flag */
    TRIGSEL_INPUT_RTC_ALARM                         = ((uint8_t)0x71U),                   /*!< trigger input source RTC alarm output */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_INPUT_MFCOM_TIMER0_OUT                  = ((uint8_t)0x72U),                   /*!< trigger input source MFCOM TIMER0 output */
    TRIGSEL_INPUT_MFCOM_TIMER1_OUT                  = ((uint8_t)0x73U),                   /*!< trigger input source MFCOM TIMER1 output */
    TRIGSEL_INPUT_MFCOM_TIMER2_OUT                  = ((uint8_t)0x74U),                   /*!< trigger input source MFCOM TIMER2 output */
    TRIGSEL_INPUT_MFCOM_TIMER3_OUT                  = ((uint8_t)0x75U),                   /*!< trigger input source MFCOM TIMER3 output */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_INPUT_CM7_0_TXEV                        = ((uint8_t)0x76U),                   /*!< trigger input source CM7_0_TXEV */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_INPUT_CM7_1_TXEV                        = ((uint8_t)0x77U),                   /*!< trigger input source CM7_1_TXEV */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_INPUT_CK_OUT0                           = ((uint8_t)0x78U),                   /*!< trigger input source CK_OUT0 */
    TRIGSEL_INPUT_TIMER_ETI0                        = ((uint8_t)0x79U),                   /*!< trigger input source TIMER_ETI0 pin */
    TRIGSEL_INPUT_TIMER_ETI1                        = ((uint8_t)0x7AU),                   /*!< trigger input source TIMER_ETI1 pin */
    TRIGSEL_INPUT_TIMER_ETI2                        = ((uint8_t)0x7BU),                   /*!< trigger input source TIMER_ETI2 pin */
    TRIGSEL_INPUT_CK_OUT1                           = ((uint8_t)0x7CU),                   /*!< trigger input source CK_OUT1 */
    TRIGSEL_INPUT_DAC0_EOC                          = ((uint8_t)0xA3U),                   /*!< trigger input source DAC0_eoc */
    TRIGSEL_INPUT_DAC1_EOC                          = ((uint8_t)0xA4U),                   /*!< trigger input source DAC1_eoc */
    TRIGSEL_INPUT_ADC0_EORC                         = ((uint8_t)0xA5U),                   /*!< trigger input source end of ADC0 routine sequence conversion */
    TRIGSEL_INPUT_ADC1_EORC                         = ((uint8_t)0xA6U),                   /*!< trigger input source end of ADC1 routine sequence conversion */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_INPUT_ADC2_EORC                         = ((uint8_t)0xA7U),                   /*!< trigger input source end of ADC2 routine sequence conversion */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_INPUT_ADC0_ECH                          = ((uint8_t)0xA8U),                   /*!< trigger input source end of ADC0 routine/inserted sequence channel conversion */
    TRIGSEL_INPUT_ADC1_ECH                          = ((uint8_t)0xA9U),                   /*!< trigger input source end of ADC1 routine/inserted sequence channel conversion */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_INPUT_ADC2_ECH                          = ((uint8_t)0xAAU),                   /*!< trigger input source end of ADC2 routine/inserted sequence channel conversion */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_INPUT_ADC0_WD0_OUT                      = ((uint8_t)0xABU),                   /*!< trigger input source ADC0 analog watchdog0 output */
    TRIGSEL_INPUT_ADC0_WD1_OUT                      = ((uint8_t)0xACU),                   /*!< trigger input source ADC0 analog watchdog1 output */
    TRIGSEL_INPUT_ADC0_WD2_OUT                      = ((uint8_t)0xADU),                   /*!< trigger input source ADC0 analog watchdog2 output */
    TRIGSEL_INPUT_ADC0_WD3_OUT                      = ((uint8_t)0xAEU),                   /*!< trigger input source ADC0 analog watchdog3 output */
    TRIGSEL_INPUT_ADC1_WD0_OUT                      = ((uint8_t)0xAFU),                   /*!< trigger input source ADC1 analog watchdog0 output */
    TRIGSEL_INPUT_ADC1_WD1_OUT                      = ((uint8_t)0xB0U),                   /*!< trigger input source ADC1 analog watchdog1 output */
    TRIGSEL_INPUT_ADC1_WD2_OUT                      = ((uint8_t)0xB1U),                   /*!< trigger input source ADC1 analog watchdog2 output */
    TRIGSEL_INPUT_ADC1_WD3_OUT                      = ((uint8_t)0xB2U),                   /*!< trigger input source ADC1 analog watchdog3 output */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_INPUT_ADC2_WD0_OUT                      = ((uint8_t)0xB3U),                   /*!< trigger input source ADC2 analog watchdog0 output */
    TRIGSEL_INPUT_ADC2_WD1_OUT                      = ((uint8_t)0xB4U),                   /*!< trigger input source ADC2 analog watchdog1 output */
    TRIGSEL_INPUT_ADC2_WD2_OUT                      = ((uint8_t)0xB5U),                   /*!< trigger input source ADC2 analog watchdog2 output */
    TRIGSEL_INPUT_ADC2_WD3_OUT                      = ((uint8_t)0xB6U),                   /*!< trigger input source ADC2 analog watchdog3 output */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_INPUT_ADC0_EOI0C                        = ((uint8_t)0xB7U),                   /*!< trigger input source end of ADC0 inserted sequence 0 conversion */
    TRIGSEL_INPUT_ADC0_EOI1C                        = ((uint8_t)0xB8U),                   /*!< trigger input source end of ADC0 inserted sequence 1 conversion */
    TRIGSEL_INPUT_ADC0_EOI2C                        = ((uint8_t)0xB9U),                   /*!< trigger input source end of ADC0 inserted sequence 2 conversion */
    TRIGSEL_INPUT_ADC0_EOI3C                        = ((uint8_t)0xBAU),                   /*!< trigger input source end of ADC0 inserted sequence 3 conversion */
    TRIGSEL_INPUT_ADC0_EOI4C                        = ((uint8_t)0xBBU),                   /*!< trigger input source end of ADC0 inserted sequence 4 conversion */
    TRIGSEL_INPUT_ADC0_EOI5C                        = ((uint8_t)0xBCU),                   /*!< trigger input source end of ADC0 inserted sequence 5 conversion */
    TRIGSEL_INPUT_ADC1_EOI0C                        = ((uint8_t)0xBDU),                   /*!< trigger input source end of ADC1 inserted sequence 0 conversion */
    TRIGSEL_INPUT_ADC1_EOI1C                        = ((uint8_t)0xBEU),                   /*!< trigger input source end of ADC1 inserted sequence 1 conversion */
    TRIGSEL_INPUT_ADC1_EOI2C                        = ((uint8_t)0xBFU),                   /*!< trigger input source end of ADC1 inserted sequence 2 conversion */
    TRIGSEL_INPUT_ADC1_EOI3C                        = ((uint8_t)0xC0U),                   /*!< trigger input source end of ADC1 inserted sequence 3 conversion */
    TRIGSEL_INPUT_ADC1_EOI4C                        = ((uint8_t)0xC1U),                   /*!< trigger input source end of ADC1 inserted sequence 4 conversion */
    TRIGSEL_INPUT_ADC1_EOI5C                        = ((uint8_t)0xC2U),                   /*!< trigger input source end of ADC1 inserted sequence 5 conversion */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_INPUT_ADC2_EOI0C                        = ((uint8_t)0xC3U),                   /*!< trigger input source end of ADC2 inserted sequence 0 conversion */
    TRIGSEL_INPUT_ADC2_EOI1C                        = ((uint8_t)0xC4U),                   /*!< trigger input source end of ADC2 inserted sequence 1 conversion */
    TRIGSEL_INPUT_ADC2_EOI2C                        = ((uint8_t)0xC5U),                   /*!< trigger input source end of ADC2 inserted sequence 2 conversion */
    TRIGSEL_INPUT_ADC2_EOI3C                        = ((uint8_t)0xC6U),                   /*!< trigger input source end of ADC2 inserted sequence 3 conversion */
    TRIGSEL_INPUT_ADC2_EOI4C                        = ((uint8_t)0xC7U),                   /*!< trigger input source end of ADC2 inserted sequence 4 conversion */
    TRIGSEL_INPUT_ADC2_EOI5C                        = ((uint8_t)0xC8U),                   /*!< trigger input source end of ADC2 inserted sequence 5 conversion */
    TRIGSEL_INPUT_TIMER0_TRGO0_IOC                  = ((uint8_t)0xC9U),                   /*!< trigger input source TIMER0 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER7_TRGO0_IOC                  = ((uint8_t)0xCAU),                   /*!< trigger input source TIMER7 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER19_TRGO0_IOC                 = ((uint8_t)0xCBU),                   /*!< trigger input source TIMER19 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER20_TRGO0_IOC                 = ((uint8_t)0xCCU),                   /*!< trigger input source TIMER20 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER60_TRGO0_IOC                 = ((uint8_t)0xCDU),                   /*!< trigger input source TIMER60 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER61_TRGO0_IOC                 = ((uint8_t)0xCEU),                   /*!< trigger input source TIMER61 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER62_TRGO0_IOC                 = ((uint8_t)0xCFU),                   /*!< trigger input source TIMER62 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER63_TRGO0_IOC                 = ((uint8_t)0xD0U),                   /*!< trigger input source TIMER63 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER1_TRGO0_IOC                  = ((uint8_t)0xD1U),                   /*!< trigger input source TIMER1 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER2_TRGO0_IOC                  = ((uint8_t)0xD2U),                   /*!< trigger input source TIMER2 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER5_TRGO0_IOC                  = ((uint8_t)0xD3U),                   /*!< trigger input source TIMER5 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER5_TRGO1_IOC                  = ((uint8_t)0xD4U),                   /*!< trigger input source TIMER5 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER5_TRGO2_IOC                  = ((uint8_t)0xD5U),                   /*!< trigger input source TIMER5 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER5_TRGO3_IOC                  = ((uint8_t)0xD6U),                   /*!< trigger input source TIMER5 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER6_TRGO0_IOC                  = ((uint8_t)0xD7U),                   /*!< trigger input source TIMER6 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER6_TRGO1_IOC                  = ((uint8_t)0xD8U),                   /*!< trigger input source TIMER6 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER6_TRGO2_IOC                  = ((uint8_t)0xD9U),                   /*!< trigger input source TIMER6 TRGO0 signal to IOC */
    TRIGSEL_INPUT_TIMER6_TRGO3_IOC                  = ((uint8_t)0xDAU),                   /*!< trigger input source TIMER6 TRGO0 signal to IOC */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
}trigsel_source_enum;

/* target peripheral definitions */
typedef enum
{
    TRIGSEL_OUTPUT_TRIGSEL_OUT0                     = ((uint8_t)0x00U),                   /*!< output target peripheral TRIGSEL_OUT0 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT1                     = ((uint8_t)0x01U),                   /*!< output target peripheral TRIGSEL_OUT1 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT2                     = ((uint8_t)0x04U),                   /*!< output target peripheral TRIGSEL_OUT2 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT3                     = ((uint8_t)0x05U),                   /*!< output target peripheral TRIGSEL_OUT3 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT4                     = ((uint8_t)0x08U),                   /*!< output target peripheral TRIGSEL_OUT4 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT5                     = ((uint8_t)0x09U),                   /*!< output target peripheral TRIGSEL_OUT5 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT6                     = ((uint8_t)0x0CU),                   /*!< output target peripheral TRIGSEL_OUT6 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT7                     = ((uint8_t)0x0DU),                   /*!< output target peripheral TRIGSEL_OUT7 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT8                     = ((uint8_t)0x10U),                   /*!< output target peripheral TRIGSEL_OUT8 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT9                     = ((uint8_t)0x11U),                   /*!< output target peripheral TRIGSEL_OUT9 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT10                    = ((uint8_t)0x14U),                   /*!< output target peripheral TRIGSEL_OUT10 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT11                    = ((uint8_t)0x15U),                   /*!< output target peripheral TRIGSEL_OUT11 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT12                    = ((uint8_t)0x18U),                   /*!< output target peripheral TRIGSEL_OUT12 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT13                    = ((uint8_t)0x19U),                   /*!< output target peripheral TRIGSEL_OUT13 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT14                    = ((uint8_t)0x1CU),                   /*!< output target peripheral TRIGSEL_OUT14 pin */
    TRIGSEL_OUTPUT_TRIGSEL_OUT15                    = ((uint8_t)0x1DU),                   /*!< output target peripheral TRIGSEL_OUT15 pin */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_OUTPUT_IOC_MONITOR0                     = ((uint8_t)0x20U),                   /*!< output target peripheral IOC monitor0 signal */
    TRIGSEL_OUTPUT_IOC_MONITOR1                     = ((uint8_t)0x21U),                   /*!< output target peripheral IOC monitor1 signal */
    TRIGSEL_OUTPUT_IOC_MONITOR2                     = ((uint8_t)0x24U),                   /*!< output target peripheral IOC monitor2 signal */
    TRIGSEL_OUTPUT_IOC_MONITOR3                     = ((uint8_t)0x25U),                   /*!< output target peripheral IOC monitor3 signal */
    TRIGSEL_OUTPUT_IOC_MONITOR4                     = ((uint8_t)0x28U),                   /*!< output target peripheral IOC monitor4 signal */
    TRIGSEL_OUTPUT_IOC_MONITOR5                     = ((uint8_t)0x29U),                   /*!< output target peripheral IOC monitor5 signal */
    TRIGSEL_OUTPUT_IOC_MONITOR6                     = ((uint8_t)0x2CU),                   /*!< output target peripheral IOC monitor6 signal */
    TRIGSEL_OUTPUT_IOC_MONITOR7                     = ((uint8_t)0x2DU),                   /*!< output target peripheral IOC monitor7 signal */
    TRIGSEL_OUTPUT_IOC_REFERENCE0                   = ((uint8_t)0x30U),                   /*!< output target peripheral IOC reference0 signal */
    TRIGSEL_OUTPUT_IOC_REFERENCE1                   = ((uint8_t)0x31U),                   /*!< output target peripheral IOC reference1 signal */
    TRIGSEL_OUTPUT_IOC_REFERENCE2                   = ((uint8_t)0x34U),                   /*!< output target peripheral IOC reference2 signal */
    TRIGSEL_OUTPUT_IOC_REFERENCE3                   = ((uint8_t)0x35U),                   /*!< output target peripheral IOC reference3 signal */
    TRIGSEL_OUTPUT_IOC_REFERENCE4                   = ((uint8_t)0x38U),                   /*!< output target peripheral IOC reference4 signal */
    TRIGSEL_OUTPUT_IOC_REFERENCE5                   = ((uint8_t)0x39U),                   /*!< output target peripheral IOC reference5 signal */
    TRIGSEL_OUTPUT_IOC_REFERENCE6                   = ((uint8_t)0x3CU),                   /*!< output target peripheral IOC reference6 signal */
    TRIGSEL_OUTPUT_IOC_REFERENCE7                   = ((uint8_t)0x3DU),                   /*!< output target peripheral IOC reference7 signal */
    TRIGSEL_OUTPUT_CAN0_EX_TIME_TICK                = ((uint8_t)0x40U),                   /*!< output target peripheral CAN0_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN1_EX_TIME_TICK                = ((uint8_t)0x41U),                   /*!< output target peripheral CAN1_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN2_EX_TIME_TICK                = ((uint8_t)0x42U),                   /*!< output target peripheral CAN2_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN3_EX_TIME_TICK                = ((uint8_t)0x44U),                   /*!< output target peripheral CAN3_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN4_EX_TIME_TICK                = ((uint8_t)0x45U),                   /*!< output target peripheral CAN4_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN5_EX_TIME_TICK                = ((uint8_t)0x46U),                   /*!< output target peripheral CAN5_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN6_EX_TIME_TICK                = ((uint8_t)0x48U),                   /*!< output target peripheral CAN6_EX_TIME_TICK */
    TRIGSEL_OUTPUT_CAN7_EX_TIME_TICK                = ((uint8_t)0x49U),                   /*!< output target peripheral CAN7_EX_TIME_TICK */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_OUTPUT_TIMER0_ITI0                      = ((uint8_t)0x5CU),                   /*!< output target peripheral TIMER0_ITI0 */
    TRIGSEL_OUTPUT_TIMER1_ITI0                      = ((uint8_t)0x60U),                   /*!< output target peripheral TIMER1_ITI0 */
    TRIGSEL_OUTPUT_TIMER2_ITI0                      = ((uint8_t)0x64U),                   /*!< output target peripheral TIMER2_ITI0 */
    TRIGSEL_OUTPUT_TIMER7_ITI0                      = ((uint8_t)0x68U),                   /*!< output target peripheral TIMER7_ITI0 */
    TRIGSEL_OUTPUT_TIMER19_ITI0                     = ((uint8_t)0x6CU),                   /*!< output target peripheral TIMER19_ITI0 */
    TRIGSEL_OUTPUT_TIMER20_ITI0                     = ((uint8_t)0x70U),                   /*!< output target peripheral TIMER20_ITI0 */
    TRIGSEL_OUTPUT_TIMER60_ITI0                     = ((uint8_t)0x74U),                   /*!< output target peripheral TIMER60_ITI0 */
    TRIGSEL_OUTPUT_TIMER61_ITI0                     = ((uint8_t)0x78U),                   /*!< output target peripheral TIMER61_ITI0 */
    TRIGSEL_OUTPUT_TIMER62_ITI0                     = ((uint8_t)0x7CU),                   /*!< output target peripheral TIMER62_ITI0 */
    TRIGSEL_OUTPUT_TIMER63_ITI0                     = ((uint8_t)0x80U),                   /*!< output target peripheral TIMER63_ITI0 */
    TRIGSEL_OUTPUT_TIMER0_BRKIN0                    = ((uint8_t)0x84U),                   /*!< output target peripheral TIMER0_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER0_BRKIN1                    = ((uint8_t)0x85U),                   /*!< output target peripheral TIMER0_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER0_BRKIN2                    = ((uint8_t)0x88U),                   /*!< output target peripheral TIMER0_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER0_BRKIN3                    = ((uint8_t)0x89U),                   /*!< output target peripheral TIMER0_BRKIN3 */
    TRIGSEL_OUTPUT_TIMER7_BRKIN0                    = ((uint8_t)0x8CU),                   /*!< output target peripheral TIMER7_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER7_BRKIN1                    = ((uint8_t)0x8DU),                   /*!< output target peripheral TIMER7_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER7_BRKIN2                    = ((uint8_t)0x90U),                   /*!< output target peripheral TIMER7_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER7_BRKIN3                    = ((uint8_t)0x91U),                   /*!< output target peripheral TIMER7_BRKIN3 */
    TRIGSEL_OUTPUT_TIMER19_BRKIN0                   = ((uint8_t)0x94U),                   /*!< output target peripheral TIMER19_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER19_BRKIN1                   = ((uint8_t)0x95U),                   /*!< output target peripheral TIMER19_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER19_BRKIN2                   = ((uint8_t)0x98U),                   /*!< output target peripheral TIMER19_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER19_BRKIN3                   = ((uint8_t)0x99U),                   /*!< output target peripheral TIMER19_BRKIN3 */
    TRIGSEL_OUTPUT_TIMER20_BRKIN0                   = ((uint8_t)0x9CU),                   /*!< output target peripheral TIMER20_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER20_BRKIN1                   = ((uint8_t)0x9DU),                   /*!< output target peripheral TIMER20_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER20_BRKIN2                   = ((uint8_t)0xA0U),                   /*!< output target peripheral TIMER20_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER20_BRKIN3                   = ((uint8_t)0xA1U),                   /*!< output target peripheral TIMER20_BRKIN3 */
    TRIGSEL_OUTPUT_TIMER60_BRKIN0                   = ((uint8_t)0xA4U),                   /*!< output target peripheral TIMER60_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER60_BRKIN1                   = ((uint8_t)0xA5U),                   /*!< output target peripheral TIMER60_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER60_BRKIN2                   = ((uint8_t)0xA8U),                   /*!< output target peripheral TIMER60_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER60_BRKIN3                   = ((uint8_t)0xA9U),                   /*!< output target peripheral TIMER60_BRKIN3 */
    TRIGSEL_OUTPUT_TIMER61_BRKIN0                   = ((uint8_t)0xACU),                   /*!< output target peripheral TIMER61_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER61_BRKIN1                   = ((uint8_t)0xADU),                   /*!< output target peripheral TIMER61_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER61_BRKIN2                   = ((uint8_t)0xB0U),                   /*!< output target peripheral TIMER61_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER61_BRKIN3                   = ((uint8_t)0xB1U),                   /*!< output target peripheral TIMER61_BRKIN3 */
    TRIGSEL_OUTPUT_TIMER62_BRKIN0                   = ((uint8_t)0xB4U),                   /*!< output target peripheral TIMER62_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER62_BRKIN1                   = ((uint8_t)0xB5U),                   /*!< output target peripheral TIMER62_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER62_BRKIN2                   = ((uint8_t)0xB8U),                   /*!< output target peripheral TIMER62_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER62_BRKIN3                   = ((uint8_t)0xB9U),                   /*!< output target peripheral TIMER62_BRKIN3 */
    TRIGSEL_OUTPUT_TIMER63_BRKIN0                   = ((uint8_t)0xBCU),                   /*!< output target peripheral TIMER63_BRKIN0 */
    TRIGSEL_OUTPUT_TIMER63_BRKIN1                   = ((uint8_t)0xBDU),                   /*!< output target peripheral TIMER63_BRKIN1 */
    TRIGSEL_OUTPUT_TIMER63_BRKIN2                   = ((uint8_t)0xC0U),                   /*!< output target peripheral TIMER63_BRKIN2 */
    TRIGSEL_OUTPUT_TIMER63_BRKIN3                   = ((uint8_t)0xC1U),                   /*!< output target peripheral TIMER63_BRKIN3 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_OUTPUT_MFCOM_TRIG0                      = ((uint8_t)0xC4U),                   /*!< output target peripheral MFCOM external trigger 0 */
    TRIGSEL_OUTPUT_MFCOM_TRIG1                      = ((uint8_t)0xC5U),                   /*!< output target peripheral MFCOM external trigger 1 */
    TRIGSEL_OUTPUT_MFCOM_TRIG2                      = ((uint8_t)0xC8U),                   /*!< output target peripheral MFCOM external trigger 2 */
    TRIGSEL_OUTPUT_MFCOM_TRIG3                      = ((uint8_t)0xC9U),                   /*!< output target peripheral MFCOM external trigger 3 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_OUTPUT_CM7_0_RXEV                       = ((uint8_t)0xCCU),                   /*!< output target peripheral CM7_0_RXEV */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_OUTPUT_CM7_1_RXEV                       = ((uint8_t)0xCDU),                   /*!< output target peripheral CM7_1_RXEV */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_OUTPUT_DAC0_OUT0_EXTRG                  = ((uint8_t)0xD0U),                   /*!< output target peripheral DAC0_OUT0 external trigger */
    TRIGSEL_OUTPUT_DAC1_OUT0_EXTRG                  = ((uint8_t)0xD1U),                   /*!< output target peripheral DAC1_OUT0 external trigger */
    TRIGSEL_OUTPUT_ADC0_ROUTRG                      = ((uint8_t)0xD4U),                   /*!< output target peripheral ADC0 routine sequence external trigger */
    TRIGSEL_OUTPUT_ADC0_INS0TRG                     = ((uint8_t)0xD8U),                   /*!< output target peripheral ADC0 inserted sequence 0 external trigger */
    TRIGSEL_OUTPUT_ADC0_INS1TRG                     = ((uint8_t)0xD9U),                   /*!< output target peripheral ADC0 inserted sequence 1 external trigger */
    TRIGSEL_OUTPUT_ADC0_INS2TRG                     = ((uint8_t)0xDAU),                   /*!< output target peripheral ADC0 inserted sequence 2 external trigger */
    TRIGSEL_OUTPUT_ADC0_INS3TRG                     = ((uint8_t)0xDCU),                   /*!< output target peripheral ADC0 inserted sequence 3 external trigger */
    TRIGSEL_OUTPUT_ADC0_INS4TRG                     = ((uint8_t)0xDDU),                   /*!< output target peripheral ADC0 inserted sequence 4 external trigger */
    TRIGSEL_OUTPUT_ADC0_INS5TRG                     = ((uint8_t)0xDEU),                   /*!< output target peripheral ADC0 inserted sequence 5 external trigger */
    TRIGSEL_OUTPUT_ADC1_ROUTRG                      = ((uint8_t)0xE0U),                   /*!< output target peripheral ADC1 routine sequence external trigger  */
    TRIGSEL_OUTPUT_ADC1_INS0TRG                     = ((uint8_t)0xE4U),                   /*!< output target peripheral ADC1 inserted sequence 0 external trigger */
    TRIGSEL_OUTPUT_ADC1_INS1TRG                     = ((uint8_t)0xE5U),                   /*!< output target peripheral ADC1 inserted sequence 1 external trigger */
    TRIGSEL_OUTPUT_ADC1_INS2TRG                     = ((uint8_t)0xE6U),                   /*!< output target peripheral ADC1 inserted sequence 2 external trigger */
    TRIGSEL_OUTPUT_ADC1_INS3TRG                     = ((uint8_t)0xE8U),                   /*!< output target peripheral ADC1 inserted sequence 3 external trigger */
    TRIGSEL_OUTPUT_ADC1_INS4TRG                     = ((uint8_t)0xE9U),                   /*!< output target peripheral ADC1 inserted sequence 4 external trigger */
    TRIGSEL_OUTPUT_ADC1_INS5TRG                     = ((uint8_t)0xEAU),                   /*!< output target peripheral ADC1 inserted sequence 5 external trigger */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_OUTPUT_ADC2_ROUTRG                      = ((uint8_t)0xECU),                   /*!< output target peripheral ADC2 routine sequence external trigger */
    TRIGSEL_OUTPUT_ADC2_INS0TRG                     = ((uint8_t)0xF0U),                   /*!< output target peripheral ADC2 inserted sequence 0 external trigger */
    TRIGSEL_OUTPUT_ADC2_INS1TRG                     = ((uint8_t)0xF1U),                   /*!< output target peripheral ADC2 inserted sequence 1 external trigger */
    TRIGSEL_OUTPUT_ADC2_INS2TRG                     = ((uint8_t)0xF2U),                   /*!< output target peripheral ADC2 inserted sequence 2 external trigger */
    TRIGSEL_OUTPUT_ADC2_INS3TRG                     = ((uint8_t)0xF4U),                   /*!< output target peripheral ADC2 inserted sequence 3 external trigger */
    TRIGSEL_OUTPUT_ADC2_INS4TRG                     = ((uint8_t)0xF5U),                   /*!< output target peripheral ADC2 inserted sequence 4 external trigger */
    TRIGSEL_OUTPUT_ADC2_INS5TRG                     = ((uint8_t)0xF6U),                   /*!< output target peripheral ADC2 inserted sequence 5 external trigger */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_OUTPUT_SPI0_TRIG                        = ((uint8_t)0xF8U),                   /*!< output target peripheral SPI0 trigger */
    TRIGSEL_OUTPUT_SPI1_TRIG                        = ((uint8_t)0xF9U),                   /*!< output target peripheral SPI1 trigger */
    TRIGSEL_OUTPUT_SPI2_TRIG                        = ((uint8_t)0xFCU),                   /*!< output target peripheral SPI2 trigger */
    TRIGSEL_OUTPUT_SPI3_TRIG                        = ((uint8_t)0xFDU),                   /*!< output target peripheral SPI3 trigger */
    TRIGSEL_OUTPUT_SPI4_TRIG                        = ((uint16_t)0x100U),                 /*!< output target peripheral SPI4 trigger */
    TRIGSEL_OUTPUT_SPI5_TRIG                        = ((uint16_t)0x101U),                 /*!< output target peripheral SPI5 trigger */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    TRIGSEL_OUTPUT_SPI6_TRIG                        = ((uint16_t)0x104U),                 /*!< output target peripheral SPI6 trigger */
    TRIGSEL_OUTPUT_SPI7_TRIG                        = ((uint16_t)0x105U),                 /*!< output target peripheral SPI7 trigger */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    TRIGSEL_OUTPUT_TIMER_ETI0                       = ((uint16_t)0x108U),                 /*!< output target peripheral TIMER_ETI0 */
    TRIGSEL_OUTPUT_TIMER_ETI1                       = ((uint16_t)0x109U),                 /*!< output target peripheral TIMER_ETI1 */
    TRIGSEL_OUTPUT_TIMER_ETI2                       = ((uint16_t)0x10AU),                 /*!< output target peripheral TIMER_ETI2 */
#if defined(GD32A711X_A712X)
    TRIGSEL_OUTPUT_LINFLEXD0_TRIG                   = ((uint16_t)0x10CU),                 /*!< output target peripheral LINFlexD0 trigger */
    TRIGSEL_OUTPUT_LINFLEXD1_TRIG                   = ((uint16_t)0x10DU),                 /*!< output target peripheral LINFlexD1 trigger */
    TRIGSEL_OUTPUT_LINFLEXD2_TRIG                   = ((uint16_t)0x110U),                 /*!< output target peripheral LINFlexD2 trigger */
    TRIGSEL_OUTPUT_LINFLEXD3_TRIG                   = ((uint16_t)0x111U),                 /*!< output target peripheral LINFlexD3 trigger */
    TRIGSEL_OUTPUT_LINFLEXD4_TRIG                   = ((uint16_t)0x114U),                 /*!< output target peripheral LINFlexD4 trigger */
    TRIGSEL_OUTPUT_LINFLEXD5_TRIG                   = ((uint16_t)0x115U),                 /*!< output target peripheral LINFlexD5 trigger */
#endif /* defined(GD32A711X_A712X) */
}trigsel_periph_enum;

/* function declarations */
/* set the trigger input signal for target peripheral */
void trigsel_init(trigsel_periph_enum target_periph, trigsel_source_enum trigger_source);
/* get the trigger input signal for target peripheral */
trigsel_source_enum trigsel_trigger_source_get(trigsel_periph_enum target_periph);
/* lock the trigger register */
void trigsel_register_lock_set(trigsel_periph_enum target_periph);
/* get the trigger register lock status */
FlagStatus trigsel_register_lock_get(trigsel_periph_enum target_periph);

#endif /* GD32A7XX_TRIGSEL_H */
