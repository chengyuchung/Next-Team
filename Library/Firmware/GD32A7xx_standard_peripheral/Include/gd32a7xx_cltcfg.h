/*!
    \file    gd32a7xx_cltcfg.h
    \brief   definitions for the CLTCFG

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

#ifndef GD32A7XX_CLTCFG_H
#define GD32A7XX_CLTCFG_H

#include "gd32a7xx.h"

#define CLTCFG                                CLTCFG_BASE                                  /*!< CLTCFG base address */

/* registers definitions */
#define CLTCFG_SR_STAT0                       REG32((CLTCFG) + 0x00000000U)                /*!< system reset status register 0 */
#define CLTCFG_SR_STAT1                       REG32((CLTCFG) + 0x00000004U)                /*!< system reset status register 1 */
#define CLTCFG_SR_STAT2                       REG32((CLTCFG) + 0x00000008U)                /*!< system reset status register 2 */
#define CLTCFG_SUBSR_STAT0                    REG32((CLTCFG) + 0x0000000CU)                /*!< subsystem reset status register 0 */
#define CLTCFG_SUBSR_STAT1                    REG32((CLTCFG) + 0x00000010U)                /*!< subsystem reset status register 1 */
#define CLTCFG_SUBSR_STAT2                    REG32((CLTCFG) + 0x00000014U)                /*!< subsystem reset status register 2 */
#define CLTCFG_POR_CTL0                       REG32((CLTCFG) + 0x00000018U)                /*!< power-on reset control register 0 */
#define CLTCFG_POR_CTL1                       REG32((CLTCFG) + 0x0000001CU)                /*!< power-on reset control register 1 */
#define CLTCFG_SR_CTL0                        REG32((CLTCFG) + 0x00000020U)                /*!< system reset control reister 0 */
#define CLTCFG_SR_CTL1                        REG32((CLTCFG) + 0x00000024U)                /*!< system reset control reister 1 */
#define CLTCFG_SUBSR_CTL0                     REG32((CLTCFG) + 0x00000028U)                /*!< subsystem reset control reister 0 */
#define CLTCFG_SUBSR_CTL1                     REG32((CLTCFG) + 0x0000002CU)                /*!< subsystem reset control reister 1 */
#define CLTCFG_SUBSR_CTL2                     REG32((CLTCFG) + 0x00000030U)                /*!< subsystem reset control reister 2 */
#define CLTCFG_TMR_CTL                        REG32((CLTCFG) + 0x00000034U)                /*!< triple modular redundancy control register */
#define CLTCFG_TMR_STAT                       REG32((CLTCFG) + 0x00000038U)                /*!< triple modular redundancy status register */
#define CLTCFG_TMR_FC                         REG32((CLTCFG) + 0x0000003CU)                /*!< triple modular redundancy flag clear register */
#define CLTCFG_LC_CS                          REG32((CLTCFG) + 0x00000040U)                /*!< life cycle control and status register */

/* bits definitions */
/* CLTCFG_SR_STAT0 */
#define CLTCFG_SR_STAT0_ISO_STAT              BIT(0)                                       /*!< PMU input isolation state */

/* CLTCFG_SR_STAT1 */
#define CLTCFG_SR_STAT1_RSTPIN_MOD            BIT(0)                                       /*!< the reset pin mode state */

/* CLTCFG_SR_STAT2 */
#define CLTCFG_SR_STAT2_FFIOMOD               BIT(31)                                      /*!< the fatal fault IO mode state */

/* CLTCFG_SUBSR_STAT0 */
#define CLTCFG_SUBSR_STAT0_ENET_CH0_STAT      BIT(0)                                       /*!< enet DMA channel 0 state */
#define CLTCFG_SUBSR_STAT0_ENET_CH1_STAT      BIT(1)                                       /*!< enet DMA channel 1 state */

/* CLTCFG_SUBSR_STAT1 */
#define CLTCFG_SUBSR_STAT1_PWDGEN_STAT        BIT(0)                                       /*!< indicates the POR watchdog status is enabled or disabled in the option bytes */
#define CLTCFG_SUBSR_STAT1_FSRDIS_STAT        BIT(1)                                       /*!< final_step regulator automatic crossover from boot regulation feature support */
#define CLTCFG_SUBSR_STAT1_SRUG               BITS(18,31)                                  /*!< indciactes the information of chip system reset esscalation support for system reset sources as configured in the option bytes */

/* CLTCFG_SUBSR_STAT2 */
#define CLTCFG_SUBSR_STAT2_SRUG               BITS(0,17)                                   /*!< indciactes the information of chip system reset esscalation support for system reset sources as configured in the option bytes */

/* CLTCFG_POR_CTL0 */ 
#define CLTCFG_POR_CTL0_CKOUT1_CFG            BIT(3)                                       /*!< clockout standy expose over system reset and subsystem reset */
#define CLTCFG_POR_CTL0_PWD_MONDIS            BIT(8)                                       /*!< disable the standy entry and exit monitor of por watchdog */
#define CLTCFG_POR_CTL0_PWDTO                 BITS(9,10)                                   /*!< configure timeout value of the por watchdog */

/* CLTCFG_POR_CTL1 */
#define CLTCFG_POR_CTL1_FMU_MONDIS            BIT(0)                                       /*!< disable FMU monitor */
#define CLTCFG_POR_CTL1_LOLINT_CFG            BIT(9)                                       /*!< configuation of PLL loss of lock event */

/* CLTCFG_SR_CTL0 */
#define CLTCFG_SR_CTL0_STOSSREN               BIT(13)                                      /*!< enable slow trace over subsystem reset */
#define CLTCFG_SR_CTL0_FTOSSREN               BIT(14)                                      /*!< enable fast trace over subsystem reset */

/* CLTCFG_SR_CTL1 */
#define CLTCFG_SR_CTL1_FRCFG                  BIT(7)                                       /*!< cconfiguration of the the fault reaction state during selftest */

/* CLTCFG_SUBSR_CTL0 */
#define CLTCFG_SUBSR_CTL0_ENET_MODE_SEL       BIT(7)                                       /*!< ENET mode selection */
#define CLTCFG_SUBSR_CTL0_PAD_RET_CFG         BIT(16)                                      /*!< configure the IO state in the standby mode */

/* CLTCFG_SUBSR_CTL1 */
#define CLTCFG_SUBSR_CTL1_ADC0_CH8_DP         BIT(1)                                       /*!< drive pin selection for ADC0 channel 8 */
#define CLTCFG_SUBSR_CTL1_ADC0_CH9_DP         BIT(2)                                       /*!< drive pin selection for ADC0 channel 9 */
#define CLTCFG_SUBSR_CTL1_ADC1_CH14_DP        BIT(3)                                       /*!< drive pin selection for ADC1 channel 14 */
#define CLTCFG_SUBSR_CTL1_ADC1_CH15_DP        BIT(4)                                       /*!< drive pin selection for ADC1 channel 15 */
#define CLTCFG_SUBSR_CTL1_ADC1_CH22_DP        BIT(5)                                       /*!< drive pin selection for ADC1 channel 22 */
#define CLTCFG_SUBSR_CTL1_ADC1_CH23_DP        BIT(6)                                       /*!< drive pin selection for ADC1 channel 23 */
#define CLTCFG_SUBSR_CTL1_ADC2_CH8_DP         BIT(9)                                       /*!< drive pin selection for ADC2 channel 8 */
#define CLTCFG_SUBSR_CTL1_ADC2_CH9_DP         BIT(10)                                      /*!< drive pin selection for ADC2 channel 9 */
#define CLTCFG_SUBSR_CTL1_CORE0_WAIT          BIT(17)                                      /*!< configuration for CM7 core 0 wait mode */
#define CLTCFG_SUBSR_CTL1_CORE1_WAIT          BIT(18)                                      /*!< configuration for CM7 core 1 wait mode */

/* CLTCFG_SUBSR_CTL2 */
#define CLTCFG_SUBSR_CTL2_BTMOD               BIT(0)                                       /*!< SBAF application boot address after standby exit */
#define CLTCFG_SUBSR_CTL2_BTADDR              BITS(1,31)                                   /*!< configure boot mode after exiting from standby */

/* CLTCFG_TMR_CTL */
#define CLTCFG_TMR_CTL_IOTMREN                BIT(0)                                       /*!< gpio TMR enable */
#define CLTCFG_TMR_CTL_SRTMREN                BIT(1)                                       /*!< system reset TMR enable */
#define CLTCFG_TMR_CTL_BTTMREN                BIT(2)                                       /*!< boot mode TMR enable */
#define CLTCFG_TMR_CTL_WMTMREN                BIT(3)                                       /*!< wait mode TMR enable */
#define CLTCFG_TMR_CTL_SBTMREN                BIT(5)                                       /*!< standby mode TMR enable */
#define CLTCFG_TMR_CTL_WDTMREN                BIT(6)                                       /*!< watch dog TMR enable */

/* CLTCFG_TMR_STAT */
#define CLTCFG_TMR_STAT_IOTMRERR              BIT(0)                                       /*!< gpio TMR error flag bit */
#define CLTCFG_TMR_STAT_SRTMRERR              BIT(1)                                       /*!< system reset TMR error flag bit */
#define CLTCFG_TMR_STAT_BTTMRERR              BIT(2)                                       /*!< boot mode TMR error flag bit */
#define CLTCFG_TMR_STAT_WMTMRERR              BIT(3)                                       /*!< WM TMR error flag bit */
#define CLTCFG_TMR_STAT_SBTMRERR              BIT(5)                                       /*!< standby mode TMR error flag bit */
#define CLTCFG_TMR_STAT_WDTMRERR              BIT(6)                                       /*!< watch dog TMR error flag bit */

/* CLTCFG_TMR_FC */
#define CLTCFG_TMR_FC_IOTMRFC                 BIT(0)                                       /*!< gpio TMR error flag clear bit */
#define CLTCFG_TMR_FC_SRTMRFC                 BIT(1)                                       /*!< system reset TMR error flag clear bit */
#define CLTCFG_TMR_FC_BTTMRFC                 BIT(2)                                       /*!< boot mode TMR error flag clear bit */
#define CLTCFG_TMR_FC_WMTMRFC                 BIT(3)                                       /*!< WM TMR error flag clear bit */
#define CLTCFG_TMR_FC_SBTMRFC                 BIT(5)                                       /*!< standby mode TMR error flag clear bit */
#define CLTCFG_TMR_FC_WDTMRFC                 BIT(6)                                       /*!< watch dog TMR error flag clear bit */

/* CLTCFG_LC_CS */
#define CLTCFG_LC_CS_CLCS                     BITS(0,2)                                    /*!< current life cycle stage */
#define CLTCFG_LC_CS_FLCEN                    BIT(3)                                       /*!< force LC */
#define CLTCFG_LC_CS_RLCS                     BITS(4,6)                                    /*!< real life cycle stage */
#define CLTCFG_LC_CS_FTNLCS                   BITS(8,9)                                    /*!< force to next life cycle stage */

/* constants definitions */
/* ENET dma channel */
typedef enum
{
    ENET_CH0 = 1U,                                                                         /*!< ENET dma channel 0 */
    ENET_CH1                                                                               /*!< ENET dma channel 1 */
} enet_ch_enum;

/* system reset resource of upgrade function */
typedef enum
{
    FMU_REA_FAIL_UPGRADE  = BIT(3),                                                        /*!< the upgrade function of FMU_REA_FAIL reset */
    STCM_REC_FAIL_UPGRADE = BIT(4),                                                        /*!< the upgrade function of STCM_REC_FAIL reset */
    RCTL_SBSRU_UPGRADE    = BIT(6),                                                        /*!< the upgrade function of RCTL_SBSRU reset */
    LOHRST_UPGRADE        = BIT(8),                                                        /*!< the upgrade function of LOHRST reset */
    LOPRST_UPGRADE        = BIT(9),                                                        /*!< the upgrade function of LOPRST reset */
    HSM_SYS_RST_UPGRADE   = BIT(18),                                                       /*!< the upgrade function of HSM_SYS_RST reset */
    SW_SYS_RST_UPGRADE    = BIT(29),                                                       /*!< the upgrade function of SW_SYS_RST reset */
    DBG_SYS_RST_UPGRADE   = BIT(30)                                                        /*!< the upgrade function of DBG_SYS_RST reset */
} srug_enum;

/* configuration of clockout standby expose over system reset and subsystem reset */
typedef enum
{
    CKOUT1_NOT_AVAILABLE,                                                                  /*!< The CKOUT1 function is not available while system reset or subsystem reset on PM4 */
    CKOUT1_AVAILABLE                                                                       /*!< The CKOUT1 function is available while system reset or subsystem reset on PM4 */
} ckout_valid_enum;

/* power watchdog timeout value */
typedef enum
{
    POR_WDG_TIMEOUT_06_25 = (uint32_t)0x00 << 9U,                                          /*!< power watchdog timeout value = 06.25ms */
    POR_WDG_TIMEOUT_12_50 = (uint32_t)0x01 << 9U,                                          /*!< power watchdog timeout value = 12.50ms */
    POR_WDG_TIMEOUT_25_00 = (uint32_t)0x02 << 9U,                                          /*!< power watchdog timeout value = 25.00ms */
    POR_WDG_TIMEOUT_50_00 = (uint32_t)0x03 << 9U                                           /*!< power watchdog timeout value = 50.00ms */
} porwdg_timeout_enum;

/* configuration of PLL loss of lock event */
typedef enum
{
    GENERATE_A_SYS_RST = (uint32_t)0x00 << 9U,                                             /*!< generate a system reset if PLL loss of lock event occurs */
    GENERATE_AN_INT    = (uint32_t)0x01 << 9U                                              /*!< generate an interrupt if PLL loss of lock event occurs */
} lol_cfg_enum;

/* FFIO state configuration during selftest */
typedef enum
{
    CHANGE_TO_HIGH_Z_STATE = (uint32_t)0x00 << 7U,                                         /*!< FFIO will change to high Z during selftest when device is under reset */
    REMAIN_IN_FAULT_STATE  = (uint32_t)0x01 << 7U                                          /*!< FFIO will remain in fault state during selftest when device is under reset */
} ffio_state_enum;

/* ENET mode */
typedef enum
{
    ENET_MII_MODE  = (uint32_t)0x00 << 7U,                                                 /*!< mii mode */
    ENET_RMII_MODE = (uint32_t)0x01 << 7U                                                  /*!< rmii mode */
} enet_mode_enum;

/* ADC channel drive pin */
typedef enum
{
    ADC0_CH8_DP_PC6   = (uint32_t)(CLTCFG_SUBSR_CTL1_ADC0_CH8_DP << 16U),                                     /*!< select the default PC6 as drive pin */
    ADC0_CH8_DP_PD13  = (uint32_t)((CLTCFG_SUBSR_CTL1_ADC0_CH8_DP << 16U)  | CLTCFG_SUBSR_CTL1_ADC0_CH8_DP),  /*!< select the PD13 as drive pin */
    ADC0_CH9_DP_PG7   = (uint32_t)(CLTCFG_SUBSR_CTL1_ADC0_CH9_DP << 16U),                                     /*!< select the default PG7 as drive pin */
    ADC0_CH9_DP_PD11  = (uint32_t)((CLTCFG_SUBSR_CTL1_ADC0_CH9_DP << 16U)  | CLTCFG_SUBSR_CTL1_ADC0_CH9_DP),  /*!< select the PD11 as drive pin */
    ADC1_CH14_DP_PA15 = (uint32_t)(CLTCFG_SUBSR_CTL1_ADC1_CH14_DP << 16U),                                    /*!< select the default PA15 as drive pin */
    ADC1_CH14_DP_PJ5  = (uint32_t)((CLTCFG_SUBSR_CTL1_ADC1_CH14_DP << 16U) | CLTCFG_SUBSR_CTL1_ADC1_CH14_DP), /*!< select the PJ5 as drive pin */
    ADC1_CH15_DP_PA13 = (uint32_t)(CLTCFG_SUBSR_CTL1_ADC1_CH15_DP << 16U),                                    /*!< select the default PA13 as drive pin */
    ADC1_CH15_DP_PB11 = (uint32_t)((CLTCFG_SUBSR_CTL1_ADC1_CH15_DP << 16U) | CLTCFG_SUBSR_CTL1_ADC1_CH15_DP), /*!< select the PB11 as drive pin */
    ADC1_CH22_DP_PG6  = (uint32_t)(CLTCFG_SUBSR_CTL1_ADC1_CH22_DP << 16U),                                    /*!< select the default PG6 as drive pin */
    ADC1_CH22_DP_PA9  = (uint32_t)((CLTCFG_SUBSR_CTL1_ADC1_CH22_DP << 16U) | CLTCFG_SUBSR_CTL1_ADC1_CH22_DP), /*!< select the PA9 as drive pin */
    ADC1_CH23_DP_PG8  = (uint32_t)(CLTCFG_SUBSR_CTL1_ADC1_CH23_DP << 16U),                                    /*!< select the default PG8 as drive pin */
    ADC1_CH23_DP_PA11 = (uint32_t)((CLTCFG_SUBSR_CTL1_ADC1_CH23_DP << 16U) | CLTCFG_SUBSR_CTL1_ADC1_CH23_DP), /*!< select the PA11 as drive pin */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    ADC2_CH8_DP_PL2   = (uint32_t)(CLTCFG_SUBSR_CTL1_ADC2_CH8_DP << 16U),                                     /*!< select the default PL2 as drive pin */
    ADC2_CH8_DP_PD13  = (uint32_t)((CLTCFG_SUBSR_CTL1_ADC2_CH8_DP << 16U)  | CLTCFG_SUBSR_CTL1_ADC2_CH8_DP),  /*!< select the PD13 as drive pin */
    ADC2_CH9_DP_PC13  = (uint32_t)(CLTCFG_SUBSR_CTL1_ADC2_CH9_DP << 16U),                                     /*!< select the default PC13 as drive pin */
    ADC2_CH9_DP_PD11  = (uint32_t)((CLTCFG_SUBSR_CTL1_ADC2_CH9_DP << 16U)  | CLTCFG_SUBSR_CTL1_ADC2_CH9_DP)   /*!< select the PD11 as drive pin */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
} drive_pin_enum;

/* core wait mode */
typedef enum
{
    CORE_0_WAIT_DIS = (uint32_t)CLTCFG_SUBSR_CTL1_CORE0_WAIT,                                                 /*!< disable CM7 core 0 wait mode */
    CORE_0_WAIT_EN  = (uint32_t)(CLTCFG_SUBSR_CTL1_CORE0_WAIT | (CLTCFG_SUBSR_CTL1_CORE0_WAIT >> 16U)),       /*!< put CM7 core 0 into wait mode by CPUWAIT */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    CORE_1_WAIT_DIS = (uint32_t)CLTCFG_SUBSR_CTL1_CORE1_WAIT,                                                 /*!< disable CM7 core 1 wait mode */
    CORE_1_WAIT_EN  = (uint32_t)(CLTCFG_SUBSR_CTL1_CORE1_WAIT | (CLTCFG_SUBSR_CTL1_CORE1_WAIT >> 16U))        /*!< put CM7 core 1 into wait mode by CPUWAIT */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
} wait_mode_enum;

/* boot mode */
typedef enum
{
    NORMAL_BOOT_MODE = 0U,                                                                                    /*!< normal boot mode */
    FAST_BOOT_MODE                                                                                            /*!< fast boot mode */
} boot_mode_enum;

/* tmr modul */
typedef enum
{
    TMR_GPIO         = (uint32_t)CLTCFG_TMR_CTL_IOTMREN,                                                      /*!< gpio tmr */
    TMR_SYSTEM_RESET = (uint32_t)CLTCFG_TMR_CTL_SRTMREN,                                                      /*!< system reset tmr */
    TMR_BOOT_MODE    = (uint32_t)CLTCFG_TMR_CTL_BTTMREN,                                                      /*!< boot mode tmr */
    TMR_WAIT_MODE    = (uint32_t)CLTCFG_TMR_CTL_WMTMREN,                                                      /*!< wait mode tmr */
    TMR_STANDBY_MODE = (uint32_t)CLTCFG_TMR_CTL_SBTMREN,                                                      /*!< standby mode tmr */
    TMR_WATCHDOG     = (uint32_t)CLTCFG_TMR_CTL_WDTMREN                                                       /*!< watchdog tmr */
} tmr_modul_enum;

/* tmr error flag */
typedef enum
{
    TMR_FLAG_IOTMRERR = (uint32_t)CLTCFG_TMR_STAT_IOTMRERR,                                                   /*!< gpio tmr error flag */
    TMR_FLAG_SRTMRERR = (uint32_t)CLTCFG_TMR_STAT_SRTMRERR,                                                   /*!< system reset tmr error flag */
    TMR_FLAG_BTTMRERR = (uint32_t)CLTCFG_TMR_STAT_BTTMRERR,                                                   /*!< boot mode tmr error flag */
    TMR_FLAG_WMTMRERR = (uint32_t)CLTCFG_TMR_STAT_WMTMRERR,                                                   /*!< wait mode tmr error flag */
    TMR_FLAG_SBTMRERR = (uint32_t)CLTCFG_TMR_STAT_SBTMRERR,                                                   /*!< standby mode tmr error flag */
    TMR_FLAG_WDTMRERR = (uint32_t)CLTCFG_TMR_STAT_WDTMRERR                                                    /*!< watchdog tmr error flag */
} tmr_err_enum;

/* life cycle */
typedef enum
{
    LC_FA                = (uint32_t)0U,                                                                      /*!< failure analysis */
    LC_UNKNOWN_STATE     = (uint32_t)1U,                                                                      /*!< unknown life cycle state */
    LC_OEM_PRODUCTION    = (uint32_t)2U,                                                                      /*!< OEM production */
    LC_CUSTOMER_DELIVERY = (uint32_t)3U,                                                                      /*!< customer delivery */
    LC_GD_PRODUCTION     = (uint32_t)6U,                                                                      /*!< GD production */
    LC_IN_FIELD          = (uint32_t)7U                                                                       /*!< in field */
} lc_enum;

/* update step number */
typedef enum
{
    LC_TEMP_NO_FORCE_UPDATE = (uint32_t)0U << 8U,                                                             /*!< no force update */
    LC_TEMP_UPDATE_NEXT_ONE = (uint32_t)1U << 8U,                                                             /*!< one step update */
    LC_TEMP_UPDATE_NEXT_TWO = (uint32_t)2U << 8U                                                              /*!< two steps update */
} lc_update_step_enum;

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check ENET dma channel */
#define NOT_ENET_CHANNEL(channel)                            ((ENET_CH0 != (channel)) && (ENET_CH1 != (channel)))

/* check system reset upgrade resource */
#define NOT_SRUG_RESOURCE(srug)                              (((srug) != FMU_REA_FAIL_UPGRADE) && ((srug) != STCM_REC_FAIL_UPGRADE) && \
                                                              ((srug) != RCTL_SBSRU_UPGRADE)   && ((srug) != LOHRST_UPGRADE)        && \
                                                              ((srug) != LOPRST_UPGRADE)       &&  ((srug) != HSM_SYS_RST_UPGRADE)   && \
                                                              ((srug) != SW_SYS_RST_UPGRADE)   && ((srug) != DBG_SYS_RST_UPGRADE))

/* check clock out configuration */
#define NOT_CKOUT_CONFIG(config)                             ((CKOUT1_NOT_AVAILABLE != (config)) && (CKOUT1_AVAILABLE != (config)))

/* check POR watchdog timeout value */
#define NOT_TIMEOUT_VALUE(timeout)                           (POR_WDG_TIMEOUT_50_00 < (timeout))

/* check PLL loss of lock event configuration */
#define NOT_LOL_CONFIG(config)                               ((GENERATE_A_SYS_RST != (config)) && (GENERATE_AN_INT != (config)))

/* check FFIO state configuration */
#define NOT_FFIO_CONFIG(state)                               ((CHANGE_TO_HIGH_Z_STATE != (state)) && (REMAIN_IN_FAULT_STATE != (state)))

/* check ENET mode configuration */
#define NOT_ENET_MODE(mode)                                  ((ENET_MII_MODE != (mode)) && (ENET_RMII_MODE != (mode)))

/* check ADC channel drive pin */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_ADC_DRIVE_PIN(pin_sel)                           (((pin_sel) != ADC0_CH8_DP_PC6)   && ((pin_sel) != ADC0_CH8_DP_PD13)  && \
                                                              ((pin_sel) != ADC0_CH9_DP_PG7)   && ((pin_sel) != ADC0_CH9_DP_PD11)  && \
                                                              ((pin_sel) != ADC1_CH14_DP_PA15) && ((pin_sel) != ADC1_CH14_DP_PJ5)  && \
                                                              ((pin_sel) != ADC1_CH15_DP_PA13) && ((pin_sel) != ADC1_CH15_DP_PB11) && \
                                                              ((pin_sel) != ADC1_CH22_DP_PG6)  && ((pin_sel) != ADC1_CH22_DP_PA9)  && \
                                                              ((pin_sel) != ADC1_CH23_DP_PG8)  && ((pin_sel) != ADC1_CH23_DP_PA11) && \
                                                              ((pin_sel) != ADC2_CH8_DP_PL2)   && ((pin_sel) != ADC2_CH8_DP_PD13)  && \
                                                              ((pin_sel) != ADC2_CH9_DP_PC13)  && ((pin_sel) != ADC2_CH9_DP_PD11))
#else
#define NOT_ADC_DRIVE_PIN(pin_sel)                           (((pin_sel) != ADC0_CH8_DP_PC6)   && ((pin_sel) != ADC0_CH8_DP_PD13)  && \
                                                              ((pin_sel) != ADC0_CH9_DP_PG7)   && ((pin_sel) != ADC0_CH9_DP_PD11)  && \
                                                              ((pin_sel) != ADC1_CH14_DP_PA15) && ((pin_sel) != ADC1_CH14_DP_PJ5)  && \
                                                              ((pin_sel) != ADC1_CH15_DP_PA13) && ((pin_sel) != ADC1_CH15_DP_PB11) && \
                                                              ((pin_sel) != ADC1_CH22_DP_PG6)  && ((pin_sel) != ADC1_CH22_DP_PA9)  && \
                                                              ((pin_sel) != ADC1_CH23_DP_PG8)  && ((pin_sel) != ADC1_CH23_DP_PA11))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* check wait mode configuration */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_WAIT_MODE_CONFIG(config)                         (((config) != CORE_0_WAIT_DIS) && ((config) != CORE_0_WAIT_EN) && \
                                                              ((config) != CORE_1_WAIT_DIS) && ((config) != CORE_1_WAIT_EN))
#else
#define NOT_WAIT_MODE_CONFIG(config)                         (((config) != CORE_0_WAIT_DIS) && ((config) != CORE_0_WAIT_EN))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* check boot mode configuration */
#define NOT_BOOT_MODE(mode)                                  ((NORMAL_BOOT_MODE != (mode)) && (FAST_BOOT_MODE != (mode)))

/* check boot address configuration */
#define NOT_FAST_BOOT_ADDR(addr)                             (0x7FFFFFFFU < (uint32_t)addr)

/* check TMR modul */
#define NOT_TMR_MODUL(modul)                                 (((modul) != TMR_GPIO)         && ((modul) != TMR_SYSTEM_RESET) && \
                                                              ((modul) != TMR_BOOT_MODE)    && ((modul) != TMR_WAIT_MODE)    && \
                                                              ((modul) != TMR_STANDBY_MODE) && ((modul) != TMR_WATCHDOG))

/* check TMR error flag */
#define NOT_TMR_ERR_FLAG(err_flag)                           (((err_flag) != TMR_FLAG_IOTMRERR) && ((err_flag) != TMR_FLAG_SRTMRERR) && \
                                                              ((err_flag) != TMR_FLAG_BTTMRERR) && ((err_flag) != TMR_FLAG_WMTMRERR) && \
                                                              ((err_flag) != TMR_FLAG_SBTMRERR) && ((err_flag) != TMR_FLAG_WDTMRERR))

/* check life cycle update step number */
#define NOT_UPDATE_STEP_NUM(update_step)                     (((update_step) != LC_TEMP_NO_FORCE_UPDATE) && ((update_step) != LC_TEMP_UPDATE_NEXT_ONE) && \
                                                              ((update_step) != LC_TEMP_UPDATE_NEXT_TWO))

#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* clear system reset status functions */
/* get PMU input isolation state */
FlagStatus cltcfg_iso_state_get(void);
/* clear PMU input isolation state */
ErrStatus cltcfg_iso_state_clear(void);
/* get reset pin mode */
FlagStatus cltcfg_reset_pin_mode_get(void);
/* get fatal fault IO mode */
FlagStatus cltcfg_ffio_mode_get(void);

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* get the specified ENET DMA transfer channel state */
FlagStatus cltcfg_enet_ch_state_get(enet_ch_enum channel);
/* clear the specified ENET DMA transfer channel state */
ErrStatus cltcfg_enet_ch_state_clear(enet_ch_enum channel);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* get the power watch dog state */
ControlStatus cltcfg_porwdg_status_get(void);
/* get the final-step regulator state */
ControlStatus cltcfg_fs_status_get(void);
/* get the system reset upgrade state */
FlagStatus cltcfg_sysrst_upgrade_get(srug_enum sysrst_ug);

/* configure the clock out function availability */
void cltcfg_ckout_standby_config(ckout_valid_enum config);
/* enable the the power watchdog monitor */
void cltcfg_porwdg_monitor_enable(void);
/* disable the the power watchdog monitor */
void cltcfg_porwdg_monitor_disable(void);
/* power watchdog timeout value configuration */
void cltcfg_porwdg_timeout_config(porwdg_timeout_enum timeout);
/* enable the FMU monitor */
void cltcfg_fmu_monitor_enable(void);
/* disable the FMU monitor */
void cltcfg_fmu_monitor_disable(void);
/* configure whether to generate an interrupt or a reset after PLL loss of lock event occurs */
void cltcfg_pll_lol_config(lol_cfg_enum config);

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* enable slow trace over subsystem reset */
void cltcfg_slow_trace_enable(void);
/* disable slow trace over subsystem reset */
void cltcfg_slow_trace_disable(void);
/* enable fast trace over subsystem reset */
void cltcfg_fast_trace_enable(void);
/* disable fast trace over subsystem reset */
void cltcfg_fast_trace_disable(void);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* configure the fault reaction state during selftest */
void cltcfg_fault_reaction_config(ffio_state_enum state);

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* select the ENET mode */
void cltcfg_enet_mode_select(enet_mode_enum mode);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* enable IO retaing function before standy entry */
void cltcfg_io_retain_enable(void);
/* disable IO retaing function after standy exit */
void cltcfg_io_retain_disable(void);
/* ADC channel pin selection */
void cltcfg_adc_drive_pin_select(drive_pin_enum pin_sel);
/* configure CM7 core wait mode */
void cltcfg_core_wait_mode_config(wait_mode_enum config);
/* configure boot mode */
void cltcfg_boot_mode_config(boot_mode_enum mode);
/* configure boot address after exiting from standby */
void cltcfg_boot_address_config(uint32_t boot_addr);

/* enable the triple modular redundancy function of specified modul */
void cltcfg_tmr_enable(tmr_modul_enum modul);
/* disable the triple modular redundancy function of specified modul */
void cltcfg_tmr_disable(tmr_modul_enum modul);
/* get the triple modular redundancy error flag of specified modul */
FlagStatus cltcfg_tmr_error_flag_get(tmr_err_enum err_flag);
/* clear the triple modular redundancy error flag of specified modul */
void cltcfg_tmr_error_flag_clear(tmr_err_enum err_flag);

/* get current chip life cycle */
lc_enum cltcfg_current_lc_get(void);
/* get real chip life cycle */
lc_enum cltcfg_real_lc_get(void);
/* enable force life cycle */
void cltcfg_force_lc_enable(void);
/* disable force life cycle */
void cltcfg_force_lc_disable(void);
/* provide provisions for a temporary life cycle update */
ErrStatus cltcfg_temporary_lc_config(lc_update_step_enum update_step);

#endif /* GD32A7XX_CLTCFG_H */
