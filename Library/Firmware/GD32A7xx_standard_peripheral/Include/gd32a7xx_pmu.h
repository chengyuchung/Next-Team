/*!
    \file    gd32a7xx_pmu.h
    \brief   definitions for the PMU
    
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

#ifndef GD32A7XX_PMU_H
#define GD32A7XX_PMU_H

#include "gd32a7xx.h"

/* PMU definitions */
#define PMU                           PMU_BASE                      /*!< PMU base address */

/* registers definitions */
#define PMU_LVCS                      REG32((PMU) + 0x00000000U)    /*!< PMU low voltage control and status register */
#define PMU_CFG                       REG32((PMU) + 0x00000004U)    /*!< PMU configuration register */
#define PMU_ABCTL                     REG32((PMU) + 0x00000008U)    /*!< PMU analog BIST control register */
#define PMU_ABSTAT                    REG32((PMU) + 0x0000000CU)    /*!< PMU analog BIST status register */
#define PMU_VID                       REG32((PMU) + 0x00000020U)    /*!< PMU version ID register */
#define PMU_CTLKEY                    REG32((PMU) + 0x00000024U)    /*!< PMU control key register */
#define PMU_MODCFG                    REG32((PMU) + 0x00000028U)    /*!< PMU mode configure register */
#define PMU_MODUPD                    REG32((PMU) + 0x0000002CU)    /*!< PMU mode update register */
#define PMU_MODSTAT                   REG32((PMU) + 0x00000030U)    /*!< PMU mode status register */
#define PMU_C0BTADDR                  REG32((PMU) + 0x00000034U)    /*!< PMU core 0 boot address register */
#define PMU_C1BTADDR                  REG32((PMU) + 0x00000038U)    /*!< PMU core 1 boot address register */
#define PMU_MCID                      REG32((PMU) + 0x0000003CU)    /*!< PMU core ID register */
#define PMU_CUPD                      REG32((PMU) + 0x00000040U)    /*!< PMU core update register */
#define PMU_CTL                       REG32((PMU) + 0x00000048U)    /*!< PMU control register */
#define PMU_TMRERREN                  REG32((PMU) + 0x00000054U)    /*!< PMU TMR error enable register */
#define PMU_TMRERRIF                  REG32((PMU) + 0x00000058U)    /*!< PMU TMR error interrupt register */
#define PMU_TMRERRIFC                 REG32((PMU) + 0x0000005CU)    /*!< PMU TMR error interrupt clear register */

/* bits definitions */
/* PMU_LVCS */
#define PMU_LVCS_VAHVDF               BIT(0)                        /*!< VDDA domain HVD flag on in NCM */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_LVCS_VBHVDF               BIT(1)                        /*!< VDDB domain HVD flag on in NCM */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_LVCS_V25HVDF              BIT(2)                        /*!< V25 domain HVD flag on in NCM */
#define PMU_LVCS_V11HVDF              BIT(3)                        /*!< V11 domain HVD flag on in NCM */
#define PMU_LVCS_V5ALVDF              BIT(4)                        /*!< VDDA domain 5V LVD flag on in NCM */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_LVCS_V15LVDF              BIT(5)                        /*!< V15 domain LVD flag on in NCM */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_LVCS_TMP0F                BIT(6)                        /*!< temperature monitor 0 interrupt flag */
#define PMU_LVCS_TMP1F                BIT(7)                        /*!< temperature monitor 1 interrupt flag */
#define PMU_LVCS_VAHVDSTAT            BIT(8)                        /*!< VDDA domain HVD status on in NCM */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_LVCS_VBHVDSTAT            BIT(9)                        /*!< VDDB domain HVD status on in NCM */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_LVCS_V25HVDSTAT           BIT(10)                       /*!< V25 domain HVD status on in NCM */
#define PMU_LVCS_V11HVDSTAT           BIT(11)                       /*!< V11 domain HVD status on in NCM */
#define PMU_LVCS_V5ALVDSTAT           BIT(12)                       /*!< VDDA domain 5V LVD status in NCM */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_LVCS_V15LVDSTAT           BIT(13)                       /*!< V15 domain LVD status in NCM */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_LVCS_TPM0O                BIT(14)                       /*!< temperature monitor 0 output */
#define PMU_LVCS_TPM1O                BIT(15)                       /*!< temperature monitor 1 output */
#define PMU_LVCS_VALVRNF              BIT(16)                       /*!< VDDA domain Low voltage reset flag in NCM */
#define PMU_LVCS_VALVRNLF             BIT(17)                       /*!< VDDA domain Low voltage reset flag (NCM or LCM) */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_LVCS_VBLVRNF              BIT(18)                       /*!< VDDB domain Low voltage reset flag in NCM */
#define PMU_LVCS_VBLVRNLF             BIT(19)                       /*!< VDDB domain Low voltage reset flag (NCM or LCM) */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_LVCS_V25LVRNF             BIT(20)                       /*!< V25 domain Low voltage reset flag in NCM */
#define PMU_LVCS_V25LVRNLF            BIT(21)                       /*!< V25 domain Low voltage reset flag (NCM or LCM) */
#define PMU_LVCS_V11LVRNF             BIT(22)                       /*!< V11 domain Low voltage reset flag in NCM */
#define PMU_LVCS_V11LVRNLF            BIT(23)                       /*!< V11 domain Low voltage reset flag (NCM or LCM) */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_LVCS_V15HVDF              BIT(26)                       /*!< 1.5V domain HVD flag on in NCM */
#define PMU_LVCS_V15HVDSTAT           BIT(27)                       /*!< 1.5V domain HVD status in NCM */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_LVCS_IRC48MSTB            BIT(28)                       /*!< IRC48M stabilization status */
#define PMU_LVCS_IRC40KSTB            BIT(29)                       /*!< IRC40K stabilization status */
#define PMU_LVCS_PORF                 BIT(31)                       /*!< POR flag */

/* PMU_CFG */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_CFG_FSREN                 BIT(0)                        /*!< final step regulator enable */
#define PMU_CFG_FSRCTLEN              BIT(1)                        /*!< final step regulator base control enable bit */
#define PMU_CFG_FREC                  BIT(2)                        /*!< fast recovery from LPM enable bit */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_CFG_V25LVRDEN             BIT(3)                        /*!< V25 domain LVR detection enable bit during LCM */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_CFG_VBLVRDEN              BIT(4)                        /*!< VDDB LVR detection enable bit during LCM */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_CFG_TMPIE                 BIT(7)                        /*!< temperature detect interrupt enable */
#define PMU_CFG_HVDIE                 BIT(8)                        /*!< high voltage detect interrupt enable */
#define PMU_CFG_LVDIE                 BIT(9)                        /*!< low voltage detects interrupt enable */
#define PMU_CFG_TEMP0EN               BIT(10)                       /*!< TEMP0 enable */
#define PMU_CFG_TEMP0SEL              BIT(11)                       /*!< high temperature monitoring level selection */
#define PMU_CFG_TEMP1EN               BIT(12)                       /*!< TEMP1 enable */
#define PMU_CFG_TEMP1SEL              BIT(13)                       /*!< high temperature monitoring level selection */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_CFG_FSRATO                BIT(16)                       /*!< final step regulator auto turn over bit */
#define PMU_CFG_FSRSTAT               BIT(17)                       /*!< final step regulator status bit */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_CFG_STBIRC48MCTL          BIT(19)                       /*!< control whether IRC48M is on in standby mode */
#define PMU_CFG_STBIRC40KCTL          BIT(20)                       /*!< control whether IRC40K is on in standby mode */
#define PMU_CFG_VALVRCTL              BIT(23)                       /*!< control VDDA LVR */

/* PMU_ABCTL */
#define PMU_ABCTL_ABEN                BIT(0)                        /*!< analog BIST enable signal */

/* PMU_ABSTAT */
#define PMU_ABSTAT_V11RUNAB           BIT(0)                        /*!< V11 RUN ABIST test status */
#define PMU_ABSTAT_V11STBAB           BIT(1)                        /*!< V11 STANDBY ABIST test status */
#define PMU_ABSTAT_V25AB              BIT(2)                        /*!< V25 BIST test status */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_ABSTAT_VBAB               BIT(3)                        /*!< VDDB BIST test status */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_ABSTAT_VAAB               BIT(4)                        /*!< VDDA BIST test status */
#define PMU_ABSTAT_TEMP0AB            BIT(5)                        /*!< high temperature 0 ABIST */
#define PMU_ABSTAT_TEMP1AB            BIT(6)                        /*!< high temperature 1 ABIST */
#define PMU_ABSTAT_HVDV11AB           BIT(8)                        /*!< HVD V11 ABIST test flag */
#define PMU_ABSTAT_HVDV25AB           BIT(9)                        /*!< HVD V25 ABIST test flag */
#define PMU_ABSTAT_HVDVAAB            BIT(10)                       /*!< HVD VDDA ABIST test flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_ABSTAT_HVDVBAB            BIT(11)                       /*!< HVD VDDB ABIST test flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* PMU_VID */
#define PMU_VID_FRA                   BIT(0)                        /*!< final step regulator availability */
#define PMU_VID_MAJVN                 BITS(28,31)                   /*!< major version number */

/* PMU_CTLKEY */
#define PMU_CTLKEY_CTLKEY             BITS(0,15)                    /*!< control key */

/* PMU_MODECFG */
#define PMU_MODCFG_SRSTR              BIT(0)                        /*!< system reset request */
#define PMU_MODCFG_SSRSTR             BIT(1)                        /*!< subsystem reset request */
#define PMU_MODCFG_STBR               BIT(15)                       /*!< standby request */

/* PMU_MODUPD */
#define PMU_MODUPD_MODUPD             BIT(0)                        /*!< mode update */

/* PMU_MODSTAT */
#define PMU_MODSTAT_PREMOD            BITS(0,1)                     /*!< previous mode */

/* PMU_C0BTADDR */
#define PMU_C0BTADDR_C0BTADDR         BITS(0,31)                    /*!< core 0 boot address */

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* PMU_C1BTADDR */
#define PMU_C1BTADDR_C1BTADDR         BITS(0,31)                    /*!< core 1 boot address */

/* PMU_MCID */
#define PMU_MCID_MCID                 BIT(0)                        /*!< main core ID */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* PMU_MODUPD */
#define PMU_CUPD_CUPD                 BIT(0)                        /*!< core update */

/* PMU_CTL */
#define PMU_CTL_BKPWEN                BIT(17)                       /*!< write protection enable for backup domain */

/* PMU_TMRERREN */
#define PMU_TMRERREN_HVDEN            BIT(0)                        /*!< HVD TMR error interrupt enable */
#define PMU_TMRERREN_LVDEN            BIT(1)                        /*!< LVD TMR error interrupt enable */
#define PMU_TMRERREN_TEMPEN           BIT(2)                        /*!< temperature interrupt enable */
#define PMU_TMRERREN_LVREN            BIT(3)                        /*!< LVR TMR error interrupt enable */
#define PMU_TMRERREN_PORFEN           BIT(4)                        /*!< PORF TMR error interrupt enable */
#define PMU_TMRERREN_FSREN            BIT(5)                        /*!< FSR interrupt enable */
#define PMU_TMRERREN_FSRCTLEN         BIT(6)                        /*!< FSRCTL interrupt enable */
#define PMU_TMRERREN_HVDIE            BIT(7)                        /*!< HVD interrupt enable */
#define PMU_TMRERREN_LVDIE            BIT(8)                        /*!< LVD interrupt enable */
#define PMU_TMRERREN_TEMPENEN         BIT(9)                        /*!< temperature enable interrupt enable */
#define PMU_TMRERREN_FSRATOEN         BIT(10)                       /*!< FSRATO interrupt enable */
#define PMU_TMRERREN_ABENEN           BIT(12)                       /*!< ABIST interrupt enable */
#define PMU_TMRERREN_ABEN             BIT(13)                       /*!< ABIST TMR error interrupt enable */
#define PMU_TMRERREN_TKEYEN           BIT(14)                       /*!< test key TMR error interrupt enable */
#define PMU_TMRERREN_MODUPDEN         BIT(15)                       /*!< mode update TMR error interrupt enable */
#define PMU_TMRERREN_CUPDEN           BIT(16)                       /*!< core update TMR error interrupt enable */

/* PMU_TMRERRIF */
#define PMU_TMRERRIF_HVDIF            BIT(0)                        /*!< HVD TMR error interrupt enable flag */
#define PMU_TMRERRIF_LVDIF            BIT(1)                        /*!< LVD TMR error interrupt enable flag */
#define PMU_TMRERRIF_TEMPIF           BIT(2)                        /*!< temperature interrupt enable flag */
#define PMU_TMRERRIF_LVRIF            BIT(3)                        /*!< LVR TMR error interrupt enable flag */
#define PMU_TMRERRIF_PORFIF           BIT(4)                        /*!< PORF TMR error interrupt enable flag */
#define PMU_TMRERRIF_FSRIF            BIT(5)                        /*!< FSR interrupt enable flag */
#define PMU_TMRERRIF_FSRCTLIF         BIT(6)                        /*!< FSRCTL interrupt enable flag */
#define PMU_TMRERRIF_HVDIEIF          BIT(7)                        /*!< HVD interrupt enable flag */
#define PMU_TMRERRIF_LVDIEIF          BIT(8)                        /*!< LVD interrupt enable flag */
#define PMU_TMRERRIF_TEMPENIF         BIT(9)                        /*!< temperature enable interrupt enable flag */
#define PMU_TMRERRIF_FSRATOIF         BIT(10)                       /*!< FSRATO interrupt enable flag */
#define PMU_TMRERRIF_ABENIF           BIT(12)                       /*!< ABIST interrupt enable flag */
#define PMU_TMRERRIF_ABIF             BIT(13)                       /*!< ABIST TMR error interrupt enable flag */
#define PMU_TMRERRIF_TKEYIF           BIT(14)                       /*!< test key TMR error interrupt enable flag */
#define PMU_TMRERRIF_MODUPDIF         BIT(15)                       /*!< mode update TMR error interrupt enable flag */
#define PMU_TMRERRIF_CUPDIF           BIT(16)                       /*!< core update TMR error interrupt enable flag */

/* PMU_TMRERRIFC */
#define PMU_TMRERRIFC_HVDIFC          BIT(0)                        /*!< HVD TMR error interrupt enable flag clear */
#define PMU_TMRERRIFC_LVDIFC          BIT(1)                        /*!< LVD TMR error interrupt enable flag clear */
#define PMU_TMRERRIFC_TEMPIFC         BIT(2)                        /*!< temperature interrupt enable flag clear */
#define PMU_TMRERRIFC_LVRIFC          BIT(3)                        /*!< LVR TMR error interrupt enable flag clear */
#define PMU_TMRERRIFC_PORFIFC         BIT(4)                        /*!< PORF TMR error interrupt enable flag clear */
#define PMU_TMRERRIFC_FSRIFC          BIT(5)                        /*!< FSR interrupt enable flag clear */
#define PMU_TMRERRIFC_FSRCTLIFC       BIT(6)                        /*!< FSRCTL interrupt enable flag clear */
#define PMU_TMRERRIFC_HVDIEIFC        BIT(7)                        /*!< HVD interrupt enable flag clear */
#define PMU_TMRERRIFC_LVDIEIFC        BIT(8)                        /*!< LVD interrupt enable flag clear */
#define PMU_TMRERRIFC_TEMPENIFC       BIT(9)                        /*!< temperature enable interrupt enable flag clear */
#define PMU_TMRERRIFC_FSRATOIFC       BIT(10)                       /*!< FSRATO interrupt enable flag clear */
#define PMU_TMRERRIFC_ABENIFC         BIT(12)                       /*!< ABIST interrupt enable flag clear */
#define PMU_TMRERRIFC_ABIFC           BIT(13)                       /*!< ABIST TMR error interrupt enable flag clear */
#define PMU_TMRERRIFC_TKEYIFC         BIT(14)                       /*!< test key TMR error interrupt enable flag clear */
#define PMU_TMRERRIFC_MODUPDIFC       BIT(15)                       /*!< mode update TMR error interrupt enable flag clear */
#define PMU_TMRERRIFC_CUPDIFC         BIT(16)                       /*!< core update TMR error interrupt enable flag clear */

/* constants definitions */
/* PMU voltage domain */
#define PMU_V25_DOMAIN                ((uint32_t)0x00000000U)       /*!< V25 domain */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_VDDB_DOMAIN               ((uint32_t)0x00000001U)       /*!< VDDB domain */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* PMU temperature monitor */
#define PMU_TEMPERATURE_MONITOR_0     ((uint32_t)0x00000000U)       /*!< temperature monitor 0 */
#define PMU_TEMPERATURE_MONITOR_1     ((uint32_t)0x00000001U)       /*!< temperature monitor 1 */

/* PMU temperature monitoring level */
#define PMU_TEMPERATURE_LEVEL_145     ((uint32_t)0x00000000U)       /*!< temperature threshold around 145 */
#define PMU_TEMPERATURE_LEVEL_155     ((uint32_t)0x00000001U)       /*!< temperature threshold around 155 */

/* PMU standby mode clock source */
#define PMU_CLK_IRC48M                ((uint32_t)0x00000000U)       /*!< clock source IRC48M */
#define PMU_CLK_IRC40K                ((uint32_t)0x00000001U)       /*!< clock source IRC40K */

/* PMU command constants definitions */
#define WFI_CMD                       ((uint8_t)0x00U)              /*!< use WFI command */
#define WFE_CMD                       ((uint8_t)0x01U)              /*!< use WFE command */

/* PMU control key value */
#define PMU_CTL_KEY_VLE               ((uint32_t)0x00005AF0U)       /*!< control key value */

/* PMU core no select */
#define PMU_CORE_ID_0                 ((uint32_t)0x00000000U)       /*!< select core 0 */
#define PMU_CORE_ID_1                 ((uint32_t)0x00000001U)       /*!< select core 1 */

/* PMU previous mode */
#define PMU_PRE_MODE_RESET            ((uint32_t)0x00000000U)       /*!< previous mode was reset (any reset) */
#define PMU_PRE_MODE_STANDBY          ((uint32_t)0x00000001U)       /*!< previous mode was standby mode */

/* define the PMU bit position and its register index offset */
#define PMU_REGIDX_BIT(regidx, bitpos) (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define PMU_REG_VAL(offset)            (REG32(PMU + ((uint32_t)(offset) >> 6U)))
#define PMU_BIT_POS(val)               ((uint32_t)(val) & 0x0000001FU)

/* register offset */
#define LVCS_REG_OFFSET                ((uint32_t)0x00000000U)                            /*!< LVCS register offset */
#define CFG_REG_OFFSET                 ((uint32_t)0x00000004U)                            /*!< CFG register offset */
#define ABSTAT_REG_OFFSET              ((uint32_t)0x0000000CU)                            /*!< ABSTAT register offset */

/* PMU interrupt enable or disable */
#define PMU_INT_HVD                    PMU_CFG_HVDIE                                      /*!< high voltage detect interrupt enable */
#define PMU_INT_LVD                    PMU_CFG_LVDIE                                      /*!< low voltage detect interrupt enable */
#define PMU_INT_TMP                    PMU_CFG_TMPIE                                      /*!< temperature monitor detect interrupt enable */

/* PMU interrupt flag */
#define PMU_INT_FLAG_VAHVD             PMU_LVCS_VAHVDF                                    /*!< VDDA domain HVD interrupt flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_INT_FLAG_VBHVD             PMU_LVCS_VBHVDF                                    /*!< VDDB domain HVD interrupt flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_INT_FLAG_V25HVD            PMU_LVCS_V25HVDF                                   /*!< V25 domain HVD interrupt flag */
#define PMU_INT_FLAG_V11HVD            PMU_LVCS_V11HVDF                                   /*!< V11 domain HVD interrupt flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_INT_FLAG_V15HVD            PMU_LVCS_V15HVDF                                   /*!< V15 domain HVD interrupt flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_INT_FLAG_V5ALVD            PMU_LVCS_V5ALVDF                                   /*!< VDDA domain 5V LVD interrupt flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define PMU_INT_FLAG_V15LVD            PMU_LVCS_V15LVDF                                   /*!< V15 domain LVD interrupt flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define PMU_INT_FLAG_TMP0              PMU_LVCS_TMP0F                                     /*!< temperature monitor 0 interrupt flag */
#define PMU_INT_FLAG_TMP1              PMU_LVCS_TMP1F                                     /*!< temperature monitor 1 interrupt flag */

/* PMU flags */  
typedef enum {
    /* flags in LVCS register */
    PMU_FLAG_VAHVDF                 = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 0U),                /*!< VDDA domain HVD flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    PMU_FLAG_VBHVDF                 = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 1U),                /*!< VDDB domain HVD flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    PMU_FLAG_V25HVDF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 2U),                /*!< V25 domain HVD flag */
    PMU_FLAG_V11HVDF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 3U),                /*!< V11 domain HVD flag */
    PMU_FLAG_V5ALVDF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 4U),                /*!< VDDA domain 5V LVD flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    PMU_FLAG_V15LVDF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 5U),                /*!< V15 domain LVD flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    PMU_FLAG_TMP0IF                 = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 6U),                /*!< temperature monitor 0 interrupt flag */
    PMU_FLAG_TMP1IF                 = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 7U),                /*!< temperature monitor 1 interrupt flag */
    PMU_FLAG_VAHVDSF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 8U),                /*!< VDDA domain HVD status flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    PMU_FLAG_VBHVDSF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 9U),                /*!< VDDB domain HVD status  flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    PMU_FLAG_V25HVDSF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 10U),               /*!< V25 domain HVD status flag */
    PMU_FLAG_V11HVDSF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 11U),               /*!< V11 domain HVD status flag */
    PMU_FLAG_V5ALVDSF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 12U),               /*!< VDDA domain 5V LVD status flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    PMU_FLAG_V15LVDSF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 13U),               /*!< V15 domain LVD status flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    PMU_FLAG_TPM0OF                 = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 14U),               /*!< temperature monitor 0 output flag */
    PMU_FLAG_TPM1OF                 = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 15U),               /*!< temperature monitor 1 output flag */
    PMU_FLAG_VALVRNF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 16U),               /*!< VDDA domain LVR NCM flag */
    PMU_FLAG_VALVRNLF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 17U),               /*!< VDDA domain LVR NCM or LCM flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    PMU_FLAG_VBLVRNF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 18U),               /*!< VDDB domain LVR NCM flag */
    PMU_FLAG_VBLVRNLF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 19U),               /*!< VDDB domain LVR NCM or LCM flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    PMU_FLAG_V25LVRNF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 20U),               /*!< V25 domain LVR NCM flag */
    PMU_FLAG_V25LVRNLF              = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 21U),               /*!< V25 domain LVR NCM or LCM flag */
    PMU_FLAG_V11LVRNF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 22U),               /*!< V11 domain LVR NCM flag */
    PMU_FLAG_V11LVRNLF              = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 23U),               /*!< V11 domain LVR NCM or LCM flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    PMU_FLAG_V15HVDF                = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 26U),               /*!< V15 domain HVD flag */
    PMU_FLAG_V15HVDSF               = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 27U),               /*!< V15 domain HVD status flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    PMU_FLAG_IRC48MSTBF             = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 28U),               /*!< IRC48M stabilization status flag */
    PMU_FLAG_IRC40KSTBF             = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 29U),               /*!< IRC40K stabilization status flag */
    PMU_FLAG_PORF                   = PMU_REGIDX_BIT(LVCS_REG_OFFSET, 31U),               /*!< POR flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    /* flag in CFG register */
    PMU_FLAG_FSRSF                  = PMU_REGIDX_BIT(CFG_REG_OFFSET, 17U),                /*!< final step regulator status flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    /* flags in ABSTAT register */
    PMU_FLAG_V11RUNABF              = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 0U),              /*!< V11 RUN ABIST test flag */
    PMU_FLAG_V11STBABF              = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 1U),              /*!< V11 STANDBY ABIST test flag */
    PMU_FLAG_V25ABF                 = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 2U),              /*!< V25 BIST test flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    PMU_FLAG_VBABF                  = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 3U),              /*!< VDDB BIST test flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    PMU_FLAG_VAABF                  = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 4U),              /*!< VDDA BIST test flag */
    PMU_FLAG_TEMP0ABF               = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 5U),              /*!< high temperature 0 flag */
    PMU_FLAG_TEMP1ABF               = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 6U),              /*!< high temperature 1 flag */
    PMU_FLAG_HVDV11ABF              = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 8U),              /*!< HVD V11 ABIST test flag */
    PMU_FLAG_HVDV25ABF              = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 9U),              /*!< HVD V25 ABIST test flag */
    PMU_FLAG_HVDVAABF               = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 10U),             /*!< HVD VDDA ABIST test flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    PMU_FLAG_HVDVBABF               = PMU_REGIDX_BIT(ABSTAT_REG_OFFSET, 11U),             /*!< HVD VDDB ABIST test flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
} pmu_flag_enum;

#ifdef FW_DEBUG_ERR_REPORT
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_PMU_DOMAIN(pmu_domain) (((pmu_domain) != PMU_V25_DOMAIN) && ((pmu_domain) != PMU_VDDB_DOMAIN)) 
#else
#define NOT_PMU_DOMAIN(pmu_domain) ((pmu_domain) != PMU_V25_DOMAIN) 
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define NOT_PMU_TEMPERATURE_MONITOR(temp_monitor) (((temp_monitor) != PMU_TEMPERATURE_MONITOR_0) && ((temp_monitor) != PMU_TEMPERATURE_MONITOR_1)) 
#define NOT_PMU_TEMPERATURE_LEVEL(temp_level) (((temp_level) != PMU_TEMPERATURE_LEVEL_145) && ((temp_level) != PMU_TEMPERATURE_LEVEL_155)) 
#define NOT_PMU_CLK_SOURCE(clk_src) (((clk_src) != PMU_CLK_IRC48M) && ((clk_src) != PMU_CLK_IRC40K))
#define NOT_CONTROL_STATUS(state) (((state) != ENABLE) && ((state) != DISABLE)) 
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_CORE_ID(core_id) (((core_id) != PMU_CORE_ID_0) && ((core_id) != PMU_CORE_ID_1)) 
#else
#define NOT_CORE_ID(core_id) ((core_id) != PMU_CORE_ID_0) 
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

#define NOT_BOOT_ADDR(boot_addr) (((boot_addr) >= 0U) && ((boot_addr) <= 0xFFFFFFFFU)) 
#define NOT_SLEEPMODE_CMD(sleepmode_cmd) (((sleepmode_cmd) != WFI_CMD) && ((sleepmode_cmd) != WFE_CMD)) 

#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_PMU_INTERRUPT(int_flag) (((int_flag) != PMU_INT_FLAG_VAHVD) && ((int_flag) != PMU_INT_FLAG_V25HVD) && ((int_flag) != PMU_INT_FLAG_V11HVD) && \
                                     ((int_flag) != PMU_INT_FLAG_V15LVD) && ((int_flag) != PMU_INT_FLAG_V15HVD) && ((int_flag) != PMU_INT_FLAG_VBHVD) && \
                                     ((int_flag) != PMU_INT_FLAG_V5ALVD) && ((int_flag) != PMU_INT_FLAG_TMP0) && ((int_flag) != PMU_INT_FLAG_TMP1))
#else
#define NOT_PMU_INTERRUPT(int_flag) (((int_flag) != PMU_INT_FLAG_VAHVD) && ((int_flag) != PMU_INT_FLAG_V25HVD) && ((int_flag) != PMU_INT_FLAG_V11HVD) && \
                                     ((int_flag) != PMU_INT_FLAG_V5ALVD)  && ((int_flag) != PMU_INT_FLAG_TMP0) && ((int_flag) != PMU_INT_FLAG_TMP1))
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define NOT_PMU_INTERRUPT_ENABLE(interrupt) (((interrupt) != PMU_INT_HVD) && ((interrupt) != PMU_INT_LVD)&& ((interrupt) != PMU_INT_TMP))
#endif

/* function declarations */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* enable final step regulator */
void pmu_run_ldo_enable(void);
/* disable final step regulator */
void pmu_run_ldo_disable(void);
/* enable final step regulator auto truns over */
void pmu_run_ldo_auto_switch_enable(void);
/* disable final step regulator auto truns over */
void pmu_run_ldo_auto_switch_disable(void);
/* enable final step regulator base control */
void pmu_base_control_enable(void);
/* disable final step regulator base control */
void pmu_base_control_disable(void);
/* disable final step regulator and final step regulator base control simultaneously */
void pmu_run_ldo_and_base_control_disable(void);
/* enable fast recovery from LCM */
void pmu_fast_recovery_enable(void);
/* disable fast recovery from LCM */
void pmu_fast_recovery_disable(void);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
/* enable PMU LVD */
void pmu_lvd_enable(uint32_t pmu_domain);
/* disable PMU LVD */
void pmu_lvd_disable(uint32_t pmu_domain);
/* enable temperature monitor */
void pmu_temperature_monitor_enable(uint32_t temp_monitor);
/* disable temperature monitor */
void pmu_temperature_monitor_disable(uint32_t temp_monitor);
/* select temperature monitor threshold */
void pmu_temperature_level_select(uint32_t temp_monitor, uint32_t temp_level);
/* set clock state when enter standby mode*/
void pmu_standby_clock_state_set(uint32_t clk_src, ControlStatus state);

/* start PMU analog BIST */
void pmu_analog_bist_start(void);
/* write PMU control key */
void pmu_control_key_write(void);
/* enable PMU mode update */
void pmu_mode_update_enable(void);
/* request system reset */
void pmu_system_reset_request(void);
/* request subsystem reset */
void pmu_subsystem_reset_request(void);
/* set PMU core boot address */
void pmu_core_boot_address_set(uint32_t core_id, uint32_t boot_addr);
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
/* set PMU main core id */
void pmu_main_core_id_set(uint32_t core_id);
/* get PMU main core id */
uint32_t pmu_main_core_id_get(void);
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
/* enable PMU core update */
void pmu_core_update_enable(void);

/* set PMU mode */
/* PMU work in standby mode */
void pmu_to_standbymode(void);
/* get previous mode */
uint32_t pmu_previous_mode_get(void);

/* backup related functions */
/* enable write access to the registers in backup domain */
void pmu_backup_write_enable(void);
/* disable write access to the registers in backup domain */
void pmu_backup_write_disable(void);

/* interrupt and flag functions */
/* clear all LVCS register flags */
void pmu_all_flags_clear(void);
/* get PMU flag */
FlagStatus pmu_flag_get(pmu_flag_enum flag);
/* clear PMU flag */
void pmu_flag_clear(pmu_flag_enum flag);
/* get PMU interrupt flag */
FlagStatus pmu_interrupt_flag_get(uint32_t int_flag);
/* clear PMU interrupt flag */
void pmu_interrupt_flag_clear(uint32_t int_flag);
/* enable the PMU interrupt */
void pmu_interrupt_enable(uint32_t interrupt);
/* disable the PMU interrupt */
void pmu_interrupt_disable(uint32_t interrupt);

#endif /* GD32A7XX_PMU_H */
