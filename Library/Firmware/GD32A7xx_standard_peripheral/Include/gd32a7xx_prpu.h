/*!
   \file    gd32a7xx_prpu.h
   \brief   definitions for the PRPU

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

#ifndef GD32A7XX_PRPU_H
#define GD32A7XX_PRPU_H

#include "gd32a7xx.h"

/* PRPU definitions */
#define PRPU                       REGPRT_BASE                      /*!< PRPU register base address */

/* registers definitions */
#define PRPU_LKPROT(x)             REG32(PRPU + 0x00000004U * (x))  /*!< Peripheral lock protection register */

/* constants definitions */
#define PRPU_UNLOCK_KEY            ((uint32_t)0x00A1B2C4U)          /*!< unlock key */
#define PRPU_LOCK_KEY              ((uint32_t)0xFFFFFFFFU)          /*!< lock key */

/* protected peripheral definitions */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PRPU_FMU                   ((uint32_t)0x00U)                /*!< peripheral number of FMU        */
#define PRPU_IRM                   ((uint32_t)0x01U)                /*!< peripheral number of IRM        */
#define PRPU_IOC                   ((uint32_t)0x02U)                /*!< peripheral number of IOC        */
#define PRPU_STCM                  ((uint32_t)0x03U)                /*!< peripheral number of STCM       */
#define PRPU_MTC                   ((uint32_t)0x04U)                /*!< peripheral number of MTC        */
#define PRPU_DMA0                  ((uint32_t)0x05U)                /*!< peripheral number of DMA0       */
#define PRPU_DMA1                  ((uint32_t)0x06U)                /*!< peripheral number of DMA1       */
#define PRPU_SRAM_REG              ((uint32_t)0x07U)                /*!< peripheral number of SRAM_REG   */
#define PRPU_FMC                   ((uint32_t)0x08U)                /*!< peripheral number of FMC        */
#define PRPU_CRC                   ((uint32_t)0x09U)                /*!< peripheral number of CRC        */
#define PRPU_GPIOA                 ((uint32_t)0x0AU)                /*!< peripheral number of GPIOA      */
#define PRPU_GPIOB                 ((uint32_t)0x0BU)                /*!< peripheral number of GPIOB      */
#define PRPU_GPIOC                 ((uint32_t)0x0CU)                /*!< peripheral number of GPIOC      */
#define PRPU_GPIOD                 ((uint32_t)0x0DU)                /*!< peripheral number of GPIOD      */
#define PRPU_GPIOE                 ((uint32_t)0x0EU)                /*!< peripheral number of GPIOE      */
#define PRPU_GPIOF                 ((uint32_t)0x0FU)                /*!< peripheral number of GPIOF      */
#define PRPU_GPIOG                 ((uint32_t)0x10U)                /*!< peripheral number of GPIOG      */
#define PRPU_GPIOH                 ((uint32_t)0x11U)                /*!< peripheral number of GPIOH      */
#define PRPU_GPIOI                 ((uint32_t)0x12U)                /*!< peripheral number of GPIOI      */
#define PRPU_GPIOJ                 ((uint32_t)0x13U)                /*!< peripheral number of GPIOJ      */
#define PRPU_GPIOK                 ((uint32_t)0x14U)                /*!< peripheral number of GPIOK      */
#define PRPU_GPIOL                 ((uint32_t)0x15U)                /*!< peripheral number of GPIOL      */
#define PRPU_GPIOM                 ((uint32_t)0x16U)                /*!< peripheral number of GPIOM      */
#define PRPU_GPION                 ((uint32_t)0x17U)                /*!< peripheral number of GPION      */
#define PRPU_DMAMUX                ((uint32_t)0x18U)                /*!< peripheral number of DMAMUX     */
#define PRPU_RCU_CCTL              ((uint32_t)0x19U)                /*!< peripheral number of RCU_CCTL   */
#define PRPU_QSPI_REG              ((uint32_t)0x1AU)                /*!< peripheral number of QSPI_REG   */
#define PRPU_MFCOM                 ((uint32_t)0x1BU)                /*!< peripheral number of MFCOM      */
#define PRPU_TCM_REG               ((uint32_t)0x1CU)                /*!< peripheral number of TCM_REG    */
#define PRPU_MCMU_MCMUA            ((uint32_t)0x1DU)                /*!< peripheral number of MCMU_MCMUA */
#define PRPU_MCMU_MCMUB            ((uint32_t)0x1EU)                /*!< peripheral number of MCMU_MCMUB */
#define PRPU_HWSEM                 ((uint32_t)0x1FU)                /*!< peripheral number of HWSEM      */
#define PRPU_HSMIF                 ((uint32_t)0x20U)                /*!< peripheral number of HSMIF      */
#define PRPU_RCU_RCTL              ((uint32_t)0x21U)                /*!< peripheral number of RCU_RCTL   */
#define PRPU_TIMER2                ((uint32_t)0x22U)                /*!< peripheral number of TIMER2     */
#define PRPU_WWDGT0                ((uint32_t)0x23U)                /*!< peripheral number of WWDGT0     */
#define PRPU_DAC0                  ((uint32_t)0x24U)                /*!< peripheral number of DAC0       */
#define PRPU_DAC1                  ((uint32_t)0x25U)                /*!< peripheral number of DAC1       */
#define PRPU_WWDGT1                ((uint32_t)0x26U)                /*!< peripheral number of WWDGT1     */
#define PRPU_TIMER20               ((uint32_t)0x27U)                /*!< peripheral number of TIMER20    */
#define PRPU_TIMER60               ((uint32_t)0x28U)                /*!< peripheral number of TIMER60    */
#define PRPU_TIMER6                ((uint32_t)0x29U)                /*!< peripheral number of TIMER6     */
#define PRPU_RTC                   ((uint32_t)0x2AU)                /*!< peripheral number of RTC        */
#define PRPU_SPI6                  ((uint32_t)0x2BU)                /*!< peripheral number of SPI6/I2S6  */
#define PRPU_SPI7                  ((uint32_t)0x2CU)                /*!< peripheral number of SPI7/I2S7  */
#define PRPU_USART3                ((uint32_t)0x2DU)                /*!< peripheral number of USART3     */
#define PRPU_USART4                ((uint32_t)0x2EU)                /*!< peripheral number of USART4     */
#define PRPU_I2C0                  ((uint32_t)0x2FU)                /*!< peripheral number of I2C0       */
#define PRPU_I2C1                  ((uint32_t)0x30U)                /*!< peripheral number of I2C1       */
#define PRPU_TIMER61               ((uint32_t)0x31U)                /*!< peripheral number of TIMER61    */
#define PRPU_TIMER63               ((uint32_t)0x32U)                /*!< peripheral number of TIMER63    */
#define PRPU_SENT                  ((uint32_t)0x33U)                /*!< peripheral number of SENT       */
#define PRPU_LINFLEXD6             ((uint32_t)0x34U)                /*!< peripheral number of LINFlexD6  */
#define PRPU_LINFLEXD7             ((uint32_t)0x35U)                /*!< peripheral number of LINFlexD7  */
#define PRPU_LINFLEXD8             ((uint32_t)0x36U)                /*!< peripheral number of LINFlexD8  */
#define PRPU_LINFLEXD9             ((uint32_t)0x37U)                /*!< peripheral number of LINFlexD9  */
#define PRPU_LINFLEXD10            ((uint32_t)0x38U)                /*!< peripheral number of LINFlexD10 */
#define PRPU_LINFLEXD11            ((uint32_t)0x39U)                /*!< peripheral number of LINFlexD11 */
#define PRPU_FWDGT1                ((uint32_t)0x3AU)                /*!< peripheral number of FWDGT1     */
#define PRPU_SPI2                  ((uint32_t)0x3BU)                /*!< peripheral number of SPI2       */
#define PRPU_SPI3                  ((uint32_t)0x3CU)                /*!< peripheral number of SPI3       */
#define PRPU_FWDGT0                ((uint32_t)0x3DU)                /*!< peripheral number of FWDGT0     */
#define PRPU_CLTCFG                ((uint32_t)0x3EU)                /*!< peripheral number of CLTCFG     */
#define PRPU_PMU                   ((uint32_t)0x3FU)                /*!< peripheral number of PMU        */
#define PRPU_ADC0                  ((uint32_t)0x40U)                /*!< peripheral number of ADC0       */
#define PRPU_ADC1                  ((uint32_t)0x41U)                /*!< peripheral number of ADC1       */
#define PRPU_ADC2                  ((uint32_t)0x42U)                /*!< peripheral number of ADC2       */
#define PRPU_TIMER1                ((uint32_t)0x43U)                /*!< peripheral number of TIMER1     */
#define PRPU_SYSCFG                ((uint32_t)0x44U)                /*!< peripheral number of SYSCFG     */
#define PRPU_LINFLEXD0             ((uint32_t)0x45U)                /*!< peripheral number of LINFlexD0  */
#define PRPU_LINFLEXD1             ((uint32_t)0x46U)                /*!< peripheral number of LINFlexD1  */
#define PRPU_LINFLEXD2             ((uint32_t)0x47U)                /*!< peripheral number of LINFlexD2  */
#define PRPU_LINFLEXD3             ((uint32_t)0x48U)                /*!< peripheral number of LINFlexD3  */
#define PRPU_LINFLEXD4             ((uint32_t)0x49U)                /*!< peripheral number of LINFlexD4  */
#define PRPU_LINFLEXD5             ((uint32_t)0x4AU)                /*!< peripheral number of LINFlexD5  */
#define PRPU_TRIGSEL               ((uint32_t)0x4BU)                /*!< peripheral number of TRIGSEL    */
#define PRPU_TIMER0                ((uint32_t)0x4CU)                /*!< peripheral number of TIMER0     */
#define PRPU_SPI0                  ((uint32_t)0x4DU)                /*!< peripheral number of SPI0       */
#define PRPU_TIMER7                ((uint32_t)0x4EU)                /*!< peripheral number of TIMER7     */
#define PRPU_USART0                ((uint32_t)0x4FU)                /*!< peripheral number of USART0     */
#define PRPU_USART1                ((uint32_t)0x50U)                /*!< peripheral number of USART1     */
#define PRPU_USART2                ((uint32_t)0x51U)                /*!< peripheral number of USART2     */
#define PRPU_SPI4                  ((uint32_t)0x52U)                /*!< peripheral number of SPI4/I2S4  */
#define PRPU_SPI5                  ((uint32_t)0x53U)                /*!< peripheral number of SPI5/I2S5  */
#define PRPU_TIMER19               ((uint32_t)0x54U)                /*!< peripheral number of TIMER19    */
#define PRPU_TIMER5                ((uint32_t)0x55U)                /*!< peripheral number of TIMER5     */
#define PRPU_TIMER62               ((uint32_t)0x56U)                /*!< peripheral number of TIMER62    */
#define PRPU_USART5                ((uint32_t)0x57U)                /*!< peripheral number of USART5     */
#define PRPU_SPI1                  ((uint32_t)0x58U)                /*!< peripheral number of SPI1       */
#define PRPU_CAN0                  ((uint32_t)0x59U)                /*!< peripheral number of CAN0       */
#define PRPU_CAN1                  ((uint32_t)0x5AU)                /*!< peripheral number of CAN1       */
#define PRPU_CAN2                  ((uint32_t)0x5BU)                /*!< peripheral number of CAN2       */
#define PRPU_CAN3                  ((uint32_t)0x5CU)                /*!< peripheral number of CAN3       */
#define PRPU_CAN4                  ((uint32_t)0x5DU)                /*!< peripheral number of CAN4       */
#define PRPU_CAN5                  ((uint32_t)0x5EU)                /*!< peripheral number of CAN5       */
#define PRPU_CAN6                  ((uint32_t)0x5FU)                /*!< peripheral number of CAN6       */
#define PRPU_CAN7                  ((uint32_t)0x60U)                /*!< peripheral number of CAN7       */
#define PRPU_EXTI                  ((uint32_t)0x61U)                /*!< peripheral number of EXTI       */
#define PRPU_CMP1                  ((uint32_t)0x62U)                /*!< peripheral number of CMP1       */
#define PRPU_CMP0                  ((uint32_t)0x63U)                /*!< peripheral number of CMP0       */
#define PRPU_ENET                  ((uint32_t)0x64U)                /*!< peripheral number of ENET       */
#define PRPU_BKP                   ((uint32_t)0x65U)                /*!< peripheral number of BKP        */
#define PRPU_HOST_JDC              ((uint32_t)0x66U)                /*!< peripheral number of HOST_JDC   */
#define PRPU_DBGSYS                ((uint32_t)0x67U)                /*!< peripheral number of DBGSYS     */
#define PRPU_CPDM                  ((uint32_t)0x68U)                /*!< peripheral number of CPDM       */
#else /* defined(GD32A71XX) */
#define PRPU_FMU                   ((uint32_t)0x00U)                /*!< peripheral number of FMU        */
#define PRPU_IRM                   ((uint32_t)0x01U)                /*!< peripheral number of IRM        */
#define PRPU_STCM                  ((uint32_t)0x03U)                /*!< peripheral number of STCM       */
#define PRPU_MTC                   ((uint32_t)0x04U)                /*!< peripheral number of MTC        */
#define PRPU_DMA0                  ((uint32_t)0x05U)                /*!< peripheral number of DMA0       */
#define PRPU_DMA1                  ((uint32_t)0x06U)                /*!< peripheral number of DMA1       */
#define PRPU_SRAM_REG              ((uint32_t)0x07U)                /*!< peripheral number of SRAM_REG   */
#define PRPU_FMC                   ((uint32_t)0x08U)                /*!< peripheral number of FMC        */
#define PRPU_CRC                   ((uint32_t)0x09U)                /*!< peripheral number of CRC        */
#define PRPU_GPIOA                 ((uint32_t)0x0AU)                /*!< peripheral number of GPIOA      */
#define PRPU_GPIOB                 ((uint32_t)0x0BU)                /*!< peripheral number of GPIOB      */
#define PRPU_GPIOC                 ((uint32_t)0x0CU)                /*!< peripheral number of GPIOC      */
#define PRPU_GPIOD                 ((uint32_t)0x0DU)                /*!< peripheral number of GPIOD      */
#define PRPU_GPIOE                 ((uint32_t)0x0EU)                /*!< peripheral number of GPIOE      */
#define PRPU_GPIOF                 ((uint32_t)0x0FU)                /*!< peripheral number of GPIOF      */
#define PRPU_GPIOG                 ((uint32_t)0x10U)                /*!< peripheral number of GPIOG      */
#define PRPU_GPIOH                 ((uint32_t)0x11U)                /*!< peripheral number of GPIOH      */
#define PRPU_GPIOI                 ((uint32_t)0x12U)                /*!< peripheral number of GPIOI      */
#define PRPU_GPIOJ                 ((uint32_t)0x13U)                /*!< peripheral number of GPIOJ      */
#define PRPU_GPIOK                 ((uint32_t)0x14U)                /*!< peripheral number of GPIOK      */
#define PRPU_GPIOL                 ((uint32_t)0x15U)                /*!< peripheral number of GPIOL      */
#define PRPU_GPIOM                 ((uint32_t)0x16U)                /*!< peripheral number of GPIOM      */
#define PRPU_GPION                 ((uint32_t)0x17U)                /*!< peripheral number of GPION      */
#define PRPU_DMAMUX                ((uint32_t)0x18U)                /*!< peripheral number of DMAMUX     */
#define PRPU_RCU_CCTL              ((uint32_t)0x19U)                /*!< peripheral number of RCU_CCTL   */
#define PRPU_QSPI_REG              ((uint32_t)0x1AU)                /*!< peripheral number of QSPI_REG   */
#define PRPU_TCM_REG               ((uint32_t)0x1CU)                /*!< peripheral number of TCM_REG    */
#define PRPU_HSMIF                 ((uint32_t)0x20U)                /*!< peripheral number of HSMIF      */
#define PRPU_RCU_RCTL              ((uint32_t)0x21U)                /*!< peripheral number of RCU_RCTL   */
#define PRPU_TIMER2                ((uint32_t)0x22U)                /*!< peripheral number of TIMER2     */
#define PRPU_WWDGT0                ((uint32_t)0x23U)                /*!< peripheral number of WWDGT0     */
#define PRPU_DAC0                  ((uint32_t)0x24U)                /*!< peripheral number of DAC0       */
#define PRPU_DAC1                  ((uint32_t)0x25U)                /*!< peripheral number of DAC1       */
#define PRPU_TIMER20               ((uint32_t)0x27U)                /*!< peripheral number of TIMER20    */
#define PRPU_TIMER60               ((uint32_t)0x28U)                /*!< peripheral number of TIMER60    */
#define PRPU_TIMER6                ((uint32_t)0x29U)                /*!< peripheral number of TIMER6     */
#define PRPU_RTC                   ((uint32_t)0x2AU)                /*!< peripheral number of RTC        */
#define PRPU_I2C0                  ((uint32_t)0x2FU)                /*!< peripheral number of I2C0       */
#define PRPU_I2C1                  ((uint32_t)0x30U)                /*!< peripheral number of I2C1       */
#define PRPU_TIMER61               ((uint32_t)0x31U)                /*!< peripheral number of TIMER61    */
#define PRPU_TIMER63               ((uint32_t)0x32U)                /*!< peripheral number of TIMER63    */
#define PRPU_SPI2                  ((uint32_t)0x3BU)                /*!< peripheral number of SPI2       */
#define PRPU_SPI3                  ((uint32_t)0x3CU)                /*!< peripheral number of SPI3       */
#define PRPU_FWDGT0                ((uint32_t)0x3DU)                /*!< peripheral number of FWDGT0     */
#define PRPU_CLTCFG                ((uint32_t)0x3EU)                /*!< peripheral number of CLTCFG     */
#define PRPU_PMU                   ((uint32_t)0x3FU)                /*!< peripheral number of PMU        */
#define PRPU_ADC0                  ((uint32_t)0x40U)                /*!< peripheral number of ADC0       */
#define PRPU_ADC1                  ((uint32_t)0x41U)                /*!< peripheral number of ADC1       */
#define PRPU_TIMER1                ((uint32_t)0x43U)                /*!< peripheral number of TIMER1     */
#define PRPU_SYSCFG                ((uint32_t)0x44U)                /*!< peripheral number of SYSCFG     */
#define PRPU_LINFLEXD0             ((uint32_t)0x45U)                /*!< peripheral number of LINFlexD0  */
#define PRPU_LINFLEXD1             ((uint32_t)0x46U)                /*!< peripheral number of LINFlexD1  */
#define PRPU_LINFLEXD2             ((uint32_t)0x47U)                /*!< peripheral number of LINFlexD2  */
#define PRPU_LINFLEXD3             ((uint32_t)0x48U)                /*!< peripheral number of LINFlexD3  */
#define PRPU_LINFLEXD4             ((uint32_t)0x49U)                /*!< peripheral number of LINFlexD4  */
#define PRPU_LINFLEXD5             ((uint32_t)0x4AU)                /*!< peripheral number of LINFlexD5  */
#define PRPU_TRIGSEL               ((uint32_t)0x4BU)                /*!< peripheral number of TRIGSEL    */
#define PRPU_TIMER0                ((uint32_t)0x4CU)                /*!< peripheral number of TIMER0     */
#define PRPU_SPI0                  ((uint32_t)0x4DU)                /*!< peripheral number of SPI0       */
#define PRPU_TIMER7                ((uint32_t)0x4EU)                /*!< peripheral number of TIMER7     */
#define PRPU_SPI4                  ((uint32_t)0x52U)                /*!< peripheral number of SPI4/I2S4  */
#define PRPU_SPI5                  ((uint32_t)0x53U)                /*!< peripheral number of SPI5/I2S5  */
#define PRPU_TIMER19               ((uint32_t)0x54U)                /*!< peripheral number of TIMER19    */
#define PRPU_TIMER5                ((uint32_t)0x55U)                /*!< peripheral number of TIMER5     */
#define PRPU_TIMER62               ((uint32_t)0x56U)                /*!< peripheral number of TIMER62    */
#define PRPU_SPI1                  ((uint32_t)0x58U)                /*!< peripheral number of SPI1       */
#define PRPU_CAN0_CLUSTER          ((uint32_t)0x59U)                /*!< peripheral number of CAN0 cluster */
#define PRPU_CAN1_CLUSTER          ((uint32_t)0x5AU)                /*!< peripheral number of CAN1 cluster */
#define PRPU_CAN2_CLUSTER          ((uint32_t)0x5BU)                /*!< peripheral number of CAN2 cluster */
#define PRPU_EXTI                  ((uint32_t)0x61U)                /*!< peripheral number of EXTI       */
#define PRPU_CMP1                  ((uint32_t)0x62U)                /*!< peripheral number of CMP1       */
#define PRPU_CMP0                  ((uint32_t)0x63U)                /*!< peripheral number of CMP0       */
#define PRPU_BKP                   ((uint32_t)0x65U)                /*!< peripheral number of BKP        */
#define PRPU_HOST_JDC              ((uint32_t)0x66U)                /*!< peripheral number of HOST_JDC   */
#define PRPU_DBGSYS                ((uint32_t)0x67U)                /*!< peripheral number of DBGSYS     */
#define PRPU_CPDM                  ((uint32_t)0x68U)                /*!< peripheral number of CPDM       */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check protected peripheral */
#define PRPU_PROTECTED_PERIPH_HIGH            ((uint32_t)0x68U)
#define NOT_PRPU_PROTECTED_PERIPH(ch)         (PRPU_PROTECTED_PERIPH_HIGH < (ch))

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* lock peripheral registers */
void prpu_periph_lock(uint32_t periph);
/* unlock peripheral registers */
void prpu_periph_unlock(uint32_t periph);
/* get Peripheral registers lock state */
FlagStatus prpu_periph_state_get(uint32_t periph);

#endif /* GD32A7XX_PRPU_H */
