/*!
    \file    gd32a7xx_gdap.h
    \brief   definitions for the GD_AP
    
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

#ifndef GD32A7XX_GDAP_H
#define GD32A7XX_GDAP_H

#include "gd32a7xx.h"

/* GD_AP definitions */
#define GD_AP_BASE                                (uint32_t)(DBGSYS_BASE + 0x000010400U)
#define GD_AP                                     GD_AP_BASE                                              /*! GD_AP base address */
#define GD_AP_KEYCHLG_BASE                        (GD_AP) + 0x000000010U                                  /*! GD_AP_KEYCHLG base address */
#define GD_AP_KEYRESP_BASE                        (GD_AP) + 0x000000040U                                  /*! GD_AP_KEYRESP base address */

/* registers definitions */
#define GD_AP_AUTH_STAT                           REG32((GD_AP) + 0x00000000U)                            /*! GD_AP authentication status register */
#define GD_AP_AUTH_CTL                            REG32((GD_AP) + 0x00000004U)                            /*! GD_AP authentication control register */
#define GD_AP_STAT                                REG32((GD_AP) + 0x00000008U)                            /*! GD_AP status register */
#define GD_AP_CTL                                 REG32((GD_AP) + 0x0000000CU)                            /*! GD_AP control register */
#define GD_AP_KEYCHLG(x)                          REG32((uint32_t)((GD_AP_KEYCHLG_BASE) + ((x) << 2U)))   /*! GD_AP key challenge register x */
#define GD_AP_LPCTL0                              REG32((GD_AP) + 0x00000030U)                            /*! GD_AP low power control register 0 */
#define GD_AP_LPCTL1                              REG32((GD_AP) + 0x00000038U)                            /*! GD_AP low power control register 1 */
#define GD_AP_KEYRESP(x)                          REG32((uint32_t)((GD_AP_KEYRESP_BASE) + ((x) << 2U)))   /*! GD_AP key response register x */
#define GD_AP_DBGEN                               REG32((GD_AP) + 0x00000080U)                            /*! GD_AP debug enable register  */
#define GD_AP_RST                                 REG32((GD_AP) + 0x00000090U)                            /*! GD_AP reset register */
#define GD_AP_ID                                  REG32((GD_AP) + 0x000000FCU)                            /*! GD_AP id code register */

/* bits definitions */
/* GD_AP_AUTH_STAT */
#define GD_AP_AUTH_STAT_CHLGRDY                   BIT(0)                                                  /*! challenge ready */
#define GD_AP_AUTH_STAT_CHLGMOD                   BIT(1)                                                  /*! challenge mode status */
#define GD_AP_AUTH_STAT_SWACC                     BIT(3)                                                  /*! debug software access enable */
#define GD_AP_AUTH_STAT_HOST_SAUTH                BIT(29)                                                 /*! host static authentication success */
#define GD_AP_AUTH_STAT_HOST_DAUTH                BIT(30)                                                 /*! host dynamic authentication success, CR is statisfied and allows access to other APs */
#define GD_AP_AUTH_STAT_HSM_DAUTH                 BIT(31)                                                 /*! HSM dynamic authentication status */

/* GD_AP_AUTH_CTL */
#define GD_AP_AUTH_CTL_AUTHREQEN                  BIT(0)                                                  /*! debug authentication request enable */
#define GD_AP_AUTH_CTL_DATRDY                     BIT(1)                                                  /*! indicates the data is ready for static authentication */
#define GD_AP_AUTH_CTL_AUTH_MODSEL                BIT(2)                                                  /*! authentication mode selection */

/* GD_AP_STAT */
#define GD_AP_STAT_SYSRST                         BIT(1)                                                  /*! system reset state */
#define GD_AP_STAT_SUBSYSRST                      BIT(2)                                                  /*! subsystem reset state */
#define GD_AP_STAT_HSM_DBGCON                     BIT(3)                                                  /*! HSM debug connect status */
#define GD_AP_STAT_HOST_DBGCON                    BIT(4)                                                  /*! HOST debug connect status */
#define GD_AP_STAT_CM7_0_HALT                     BIT(12)                                                 /*! MCU entry debug mode, core CM7_0 is haltd */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define GD_AP_STAT_CM7_1_HALT                     BIT(13)                                                 /*! MCU entry debug mode, core CM7_1 is haltd */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define GD_AP_STAT_CM23_HALT                      BIT(15)                                                 /*! MCU entry debug mode, core CM23 is haltd */
#define GD_AP_STAT_CM23_DBG_RSTART                BIT(27)                                                 /*! core CM23 debug restarted */
#define GD_AP_STAT_CM7_0_DBG_RSTART               BIT(28)                                                 /*! core CM7_0 debug restarted */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define GD_AP_STAT_CM7_1_DBG_RSTART               BIT(29)                                                 /*! core CM7_1 debug restarted */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* GD_AP_CTL */
#define GD_AP_CTL_SYSRSTEN                        BIT(4)                                                  /*! system reset enable */
#define GD_AP_CTL_SUBSYSRSTEN                     BIT(5)                                                  /*! subsystem reset enable */
#define GD_AP_CTL_CM23_DBGREQEN                   BIT(7)                                                  /*! core CM23 debug request enable */ 
#define GD_AP_CTL_CM7_0_DBGREQEN                  BIT(8)                                                  /*! core CM7_0 debug request enable */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define GD_AP_CTL_CM7_1_DBGREQEN                  BIT(9)                                                  /*! core CM7_1 debug request enable */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define GD_AP_CTL_PORWDGTEN                       BIT(15)                                                 /*! power watchdog */
#define GD_AP_CTL_TPIUOVRDEN                      BIT(20)                                                 /*! TPIU override enable */
#define GD_AP_CTL_SWOOVRDEN                       BIT(22)                                                 /*! SWO override enable */
#define GD_AP_CTL_CM23_DBG_RSTARTEN               BIT(27)                                                 /*! core CM23 debug restarted enable */
#define GD_AP_CTL_CM7_0_DBG_RSTARTEN              BIT(28)                                                 /*! core CM7_0 debug restarted enable */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define GD_AP_CTL_CM7_1_DBG_RSTARTEN              BIT(29)                                                 /*! core CM7_1 debug restarted enable */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define GD_AP_CTL_TRACE_CLKEN                     BIT(31)                                                 /*! trace clock enable */

/* GD_AP_KEYCHLG(x) */
#define GD_AP_KEYCHLG_KEYCHLG                     BITS(0,31)                                              /*! debug enablement key challenge */

/* GD_AP_LPCTL0 */
#define GD_AP_LPCTL0_LPDBGEN                      BIT(0)                                                  /*! low power debug mode enable */

/* GD_AP_LPCTL1 */
#define GD_AP_LPCTL1_WAITRST                      BIT(0)                                                  /*! support for wait NRST pin */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define GD_AP_LPCTL1_RST_BLK                      BIT(1)                                                  /*! reset block */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* DBGSYS_KEYRESP(x) */
#define GD_AP_KEYRSEP_KEYRESP                     BITS(0,31)                                              /*! debug enablement key response */

/* GD_AP_DBGEN */
#define GD_AP_CM23_DBGEN                          BIT(2)                                                  /*! core CM23 debug enable */
#define GD_AP_CM23_NIDEN                          BIT(3)                                                  /*! core CM23 non-invasive debug enable */
#define GD_AP_CM7_COMP_DBGEN                      BIT(4)                                                  /*! CM7 subsysterm, ITM, ETM and CTI compoment debug enable */
#define GD_AP_CM7_COMP_NIDEN                      BIT(5)                                                  /*! CM7 subsysterm, ITM, ETM and CTI compoment non-invasive debug enable */
#define GD_AP_CM7_CORE_DBGEN                      BIT(28)                                                 /*! core CM7 debug enable */
#define GD_AP_CM7_CORE_NIDEN                      BIT(29)                                                 /*! core CM7 non-invasive debug enable */

/* GD_AP_RST */
#define GD_AP_CM7_0_RST                           BIT(25)                                                 /*! core CM7_0 reset release */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define GD_AP_CM7_1_RST                           BIT(26)                                                 /*! core CM7_1 reset release */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* GD_AP_ID */
#define GD_AP_ID_ID_CODE                          BITS(0,31)                                              /*! GD AP ID code */

/* constants definitions */
/* authentication target */
typedef enum
{
    HOST_AUTH = 0,                                                                                        /*! HOST authentication */
    HSM_AUTH                                                                                              /*! HSM authentication */
}gd_ap_auth_traget_enum;

/* authentication mode */
typedef enum
{
    DYNAMIC_AUTH = 0,                                                                                     /*! dynamic authentication mode */
    STATIC_AUTH                                                                                           /*! static authentication mode */
}gd_ap_auth_mode_enum;

/* reset type */
typedef enum
{
    SYSTEM_RESET = 0,                                                                                     /*! system reset */
    SUBSYSTEM_RESET                                                                                       /*! subsystem reset */
}gd_ap_reset_type_enum;

/* core select */
typedef enum
{
    CORE_CM7_0 = 0,                                                                                       /*! core CM7_0 */
#if defined (GD32A72XX) || defined (GD32A74XX)
    CORE_CM7_1,                                                                                           /*! core CM7_1 */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
    CORE_CM23                                                                                             /*! core CM23 */
}gd_ap_target_core_enum;

/* exit reset mode select */
typedef enum
{
    EXIT_RESET_NORMAL = 0,                                                                                /*! normal exit reset */
    EXIT_RESET_WAIT                                                                                       /*! on exiting standby mode, RCTL waits until the debugger writes */
}gd_ap_exit_reset_mode_enum;

/* reset entry mode select */
typedef enum
{
    ENTRY_RESET_NORMAL = 0,                                                                               /*! normal entry reset */
    ENTRY_RESET_BLOCK                                                                                     /*! PMU will waiting for TPIU flush done signal then generating low power entry sequence */
}gd_ap_entry_reset_mode_enum;

/* GD_AP static/dynamic authentication flag  */
#define GD_AP_HOST_SAUTH_FLAG                                GD_AP_AUTH_STAT_HOST_SAUTH                   /*!< HOST static authentication flag */
#define GD_AP_HOST_DAUTH_FLAG                                GD_AP_AUTH_STAT_HOST_DAUTH                   /*!< HOST dynamic authentication flag */
#define GD_AP_HSM_DAUTH_FLAG                                 GD_AP_AUTH_STAT_HSM_DAUTH                    /*!< HSM dynamic authentication flag */

/* GD_AP debug enable or diable */
#define CORE_CM23_DEBUG                                      GD_AP_CM23_DBGEN                             /*!< core CM23 debug enable */
#define CORE_CM23_NON_INVASIVE_DEBUG                         GD_AP_CM23_NIDEN                             /*!< core CM23 non-invasive debug enable */
#define CORE_CM7_COMPOMENT_DEBUG                             GD_AP_CM7_COMP_DBGEN                         /*!< CM7 subsysterm, ITM, ETM and CTI compoment debug enable */
#define CORE_CM7_COMPOMENT_NON_INVASIVE_DEBUG                GD_AP_CM7_COMP_NIDEN                         /*!< CM7 subsysterm, ITM, ETM and CTI compoment non-invasive debug enable */
#define CORE_CM7_DEBUG                                       GD_AP_CM7_CORE_DBGEN                         /*!< core CM7 debug enable */
#define CORE_CM7_NON_INVASIVE_DEBUG                          GD_AP_CM7_CORE_NIDEN                         /*!< core CM7 non-invasive debug enable */

/* GD_AP state */
#define SYSTEM_RESET_FLAG                                    GD_AP_STAT_SYSRST                            /*!< MCU is in system reset state */
#define SUBSYSTEM_RESET_FLAG                                 GD_AP_STAT_SUBSYSRST                         /*!< MCU is in subsystem reset state */
#define HSM_DEBUG_CONNECT_FALG                               GD_AP_STAT_HSM_DBGCON                        /*!< HSM debug connect state */
#define HOST_DEBUG_CONNECT_FALG                              GD_AP_STAT_HOST_DBGCON                       /*!< HOST debug connect state */
#define CM7_0_HALT_FLAG                                      GD_AP_STAT_CM7_0_HALT                        /*!< core CM7_0 is halted state */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define CM7_1_HALT_FLAG                                      GD_AP_STAT_CM7_1_HALT                        /*!< core CM7_1 is halted state */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define CM23_HALT_FLAG                                       GD_AP_STAT_CM23_HALT                         /*!< core CM23 is halted state */
#define CM7_0_DEBUG_RESTART_FLAG                             GD_AP_STAT_CM7_0_DBG_RSTART                  /*!< core CM7_0 debug restarted state */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define CM7_1_DEBUG_RESTART_FLAG                             GD_AP_STAT_CM7_1_DBG_RSTART                  /*!< core CM7_1 debug restarted state */
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#define CM23_DEBUG_RESTART_FLAG                              GD_AP_STAT_CM23_DBG_RSTART                   /*!< core CM23 debug restarted state */

#ifdef FW_DEBUG_ERR_REPORT
/* check authentication state */
#define NOT_GD_AP_AUTH_FLAG(auth_flag)                       (((auth_flag) != GD_AP_HOST_SAUTH_FLAG) && ((auth_flag) != GD_AP_HOST_DAUTH_FLAG) && \
                                                             ((auth_flag) != GD_AP_HSM_DAUTH_FLAG))
/* check gd_ap core debug */
#define NOT_GD_AP_CORE_DEBUG(debug)                          (((debug) != CORE_CM23_DEBUG)          &&  ((debug) != CORE_CM23_NON_INVASIVE_DEBUG) && \
                                                             ((debug) != CORE_CM7_COMPOMENT_DEBUG)  &&  ((debug) != CORE_CM7_COMPOMENT_NON_INVASIVE_DEBUG) && \
                                                             ((debug) != CORE_CM7_DEBUG)            &&  ((debug) != CORE_CM7_NON_INVASIVE_DEBUG))
/* check gd_ap flag */
#if defined (GD32A72XX) || defined (GD32A74XX)
#define NOT_GD_AP_FLAG(flag)                                 (((flag) != SYSTEM_RESET_FLAG)         &&  ((flag) != SUBSYSTEM_RESET_FLAG) && \
                                                             ((flag) != HSM_DEBUG_CONNECT_FALG)     &&  ((flag) != HOST_DEBUG_CONNECT_FALG) && \
                                                             ((flag) != CM7_0_HALT_FLAG)            &&  ((flag) != CM7_1_HALT_FLAG) && \
                                                             ((flag) != CM23_HALT_FLAG)             &&  ((flag) != CM7_0_DEBUG_RESTART_FLAG) && \
                                                             ((flag) != CM7_1_DEBUG_RESTART_FLAG)   &&  ((flag) != CM23_DEBUG_RESTART_FLAG))
#else 
#define NOT_GD_AP_FLAG(flag)                                 (((flag) != SYSTEM_RESET_FLAG)         &&  ((flag) != SUBSYSTEM_RESET_FLAG) && \
                                                             ((flag) != HSM_DEBUG_CONNECT_FALG)     &&  ((flag) != HOST_DEBUG_CONNECT_FALG) && \
                                                             ((flag) != CM7_0_HALT_FLAG)            &&  ((flag) != CM23_HALT_FLAG)          &&  \
                                                             ((flag) != CM7_0_DEBUG_RESTART_FLAG)   &&  ((flag) != CM23_DEBUG_RESTART_FLAG))
                                                             
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* GD_AP authentication functions */
/* configure debug authentication mode */
void gd_ap_authentication_target_config(gd_ap_auth_traget_enum auth_target);
/* configure the data is ready for static authentication */
void gd_ap_authentication_ready_config(void);
/* enable debug authentication request */
void gd_ap_authentication_request_enable(void); 
/* disable debug authentication request */
void gd_ap_authentication_request_disable(void);
/* get the key challenge value */
void gd_ap_key_challenge_value_get(uint32_t key_challenge[]);
/* configure the key response value */
void gd_ap_key_response_value_config(uint32_t key_response[]);
/* get challenge ready flag */
FlagStatus gd_ap_challenge_reday_state_get(void);
/* get current challenge mode */
gd_ap_auth_mode_enum gd_ap_challenge_mode_state_get(void);
/* get current host static authentication and host/hsm dynamic authentication status */
FlagStatus gd_ap_authentiction_state_get(uint32_t auth_flag);

/* GD_AP core reset/debug/trace functions */
/* enable ystem reset or subsystem reset */
void gd_ap_reset_enable(gd_ap_reset_type_enum rst_type);
/* disable system reset or subsystem reset */
void gd_ap_reset_disable(gd_ap_reset_type_enum rst_type);
/* enable core debug request */
void gd_ap_core_debug_request_enable(gd_ap_target_core_enum target_core);
/* disable core debug request */
void gd_ap_core_debug_request_disable(gd_ap_target_core_enum target_core);
/* enable power watchdog */
void gd_ap_power_watchdog_enable(void);
/* disable power watchdog */
void gd_ap_power_watchdog_disable(void);
/* enable tpiu override */
void gd_ap_tpiu_override_enable(void);
/* disable tpiu override */
void gd_ap_tpiu_override_disable(void);
/* enable swo override */
void gd_ap_swo_override_enable(void);
/* disable swo override */
void gd_ap_swo_override_disable(void);
/* enable core debug restarted */
void gd_ap_debug_restart_enable(gd_ap_target_core_enum target_core);
/* disable core debug restarted */
void gd_ap_debug_restart_disable(gd_ap_target_core_enum target_core);
/* enable trace clock */
void gd_ap_trace_clock_enable(void);
/* disable trace clock */
void gd_ap_trace_clock_disable(void);
/* enable low power debug mode */
void gd_ap_low_power_enable(void);
/* disable low power debug mode */
void gd_ap_low_power_disable(void);

/* on exiting standby mode, waiting until the debugger write to allow it to exit reset */
void gd_ap_wait_reset_config(gd_ap_exit_reset_mode_enum exit_reset_mode);
#if defined (GD32A72XX) || defined (GD32A74XX)
/* TPIU flush trigger reset operation or prevented reset operation after TPIU is enabled */
void gd_ap_reset_block_config(gd_ap_entry_reset_mode_enum entry_reset_mode);
#endif /* defined (GD32A72XX) || defined (GD32A74XX) */

/* enable debug function */
void gd_ap_debug_enable(uint32_t debug);
/* disable debug function */
void gd_ap_debug_disable(uint32_t debug);
/*  target core entry reset state */
void gd_ap_entry_reset_config(gd_ap_target_core_enum target_core);
/*  target core exit reset state */
void gd_ap_exit_reset_config(gd_ap_target_core_enum target_core);

/* get gd_ap idcode */
uint32_t gd_ap_idcode_value_get(void);

/* get gd_ap flag */
/* get debug software access flag */
FlagStatus gd_ap_debug_software_access_state_get(void);
/* get gd_ap flag */
FlagStatus gd_ap_flag_get(uint32_t flag);
#endif /* GD32A7XX_GDAP_H */
