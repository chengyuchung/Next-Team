/*!
    \file    gd32a7xx_linflexd_lin.c
    \brief   LINFLEXD LIN driver

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

#include "gd32a7xx_linflexd_lin.h"

#define LINFlexD_IFMI_IFMI_MASK                                 (0x1FU)
#define LINFlexD_LINCR1_BF_MASK                                 (0x80U)
#define BAUDRATE_FRACTION_WIDTH                                 (0x04U)
#define LINFlexD_BIDR_SIZE_OFFSET                               (0x0AU)
#define LINFlexD_BIDR_ID_MASK                                   (0x3FU)
#define LINFLEXD_LIN_DELAY                                      (0xFFFFU)                /* infinite loop delay count */
#define DEFAULT_BAUDRATE                                        (19200U)                 /* default baud rate value */
#define DEFAULT_RES_TIMEOUT_VALUE                               (0x10U)                  /* default response timeout value */
#define DEFAULT_HEAD_TIMEOUT_VALUE                              (0x2FU)                  /* default head timeout value */
#define DEFAULT_FILTER_COUNT_VALUE                              (0x0U)                   /* default filter value */
#define DEFAULT_NUM_CLASSICID_VALUE                             (0x0U)                   /* default number of classic ID value */

/*!
    \brief      reset LIN Peripheral (API_ID(0x0001U))
    \param[in]  linflexdx: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     ErrStatus:SUCCESS or ERROR
*/
ErrStatus linflexd_deinit(uint32_t lin_periph)
{
    ErrStatus reval = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t timeout_cnt;
        /* enter initialization mode */
        linflexd_lin_enter_init_mode(lin_periph);
        /* load delay count */
        timeout_cnt = LINFLEXD_LIN_DELAY;
        while ((linflexd_lin_get_state(lin_periph) != LINFlexD_STATE_INIT_MODE)  && (0U != timeout_cnt)) {
            timeout_cnt--;
        }
        if(linflexd_lin_get_state(lin_periph) != LINFlexD_STATE_INIT_MODE){
            /* set error status */
            reval = ERROR;
        } else {
            /* reset LINFlexD_LIN register */
            LINFLEXD_LINIER(lin_periph)      = 0x00000000U;
            LINFLEXD_LINSR(lin_periph)       = 0x00080327U;
            LINFLEXD_LINESR(lin_periph)      = 0x0000FF81U;
            LINFLEXD_LINTCSR(lin_periph)     = 0x00000200U;
            LINFLEXD_LINOCR(lin_periph)      = 0x0000FFFFU;
            LINFLEXD_LINTOCR(lin_periph)     = 0x00000E2CU;
            LINFLEXD_LINFBRR(lin_periph)     = 0x00000000U;
            LINFLEXD_LINIBRR(lin_periph)     = 0x00000000U;
            LINFLEXD_LINCFR(lin_periph)      = 0x00000000U;
            LINFLEXD_LINCR2(lin_periph)      = 0x00006000U;
            LINFLEXD_BIDR(lin_periph)        = 0x00000000U;
            LINFLEXD_BDRL(lin_periph)        = 0x00000000U;
            LINFLEXD_BDRM(lin_periph)        = 0x00000000U;
            LINFLEXD_IFER(lin_periph)        = 0x00000000U;
            LINFLEXD_IFMR(lin_periph)        = 0x00000000U;
            for(uint32_t i=0;i<=15U;i++){
                LINFLEXD_IFCR(lin_periph, i) = 0x00000000U;
            }
            LINFLEXD_GCR(lin_periph)         = 0x00000000U;
            LINFLEXD_DMATXE(lin_periph)      = 0x00000000U;
            LINFLEXD_DMARXE(lin_periph)      = 0x00000000U;
            LINFLEXD_LIN_STCTL(lin_periph)   = 0x00000000U;
            LINFLEXD_LINCR1(lin_periph)      = 0x00000081U;
            LINFLEXD_LINCR1(lin_periph)      = 0x00000082U;
            
        switch(lin_periph){
        case LINFLEXD_LIN0:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN0 */
            rcu_periph_reset_enable(RCU_LINFLEXD0RST);
            rcu_periph_reset_disable(RCU_LINFLEXD0RST);
            break;
        case LINFLEXD_LIN1:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN1 */
            rcu_periph_reset_enable(RCU_LINFLEXD1RST);
            rcu_periph_reset_disable(RCU_LINFLEXD1RST);
            break;
        case LINFLEXD_LIN2:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN2 */
            rcu_periph_reset_enable(RCU_LINFLEXD2RST);
            rcu_periph_reset_disable(RCU_LINFLEXD2RST);
            break;
        case LINFLEXD_LIN3:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN3 */
            rcu_periph_reset_enable(RCU_LINFLEXD3RST);
            rcu_periph_reset_disable(RCU_LINFLEXD3RST);
            break;
        case LINFLEXD_LIN4:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN4 */
            rcu_periph_reset_enable(RCU_LINFLEXD4RST);
            rcu_periph_reset_disable(RCU_LINFLEXD4RST);
            break;
        case LINFLEXD_LIN5:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN5 */
            rcu_periph_reset_enable(RCU_LINFLEXD5RST);
            rcu_periph_reset_disable(RCU_LINFLEXD5RST);
            break;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
        case LINFLEXD_LIN6:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN6 */
            rcu_periph_reset_enable(RCU_LINFLEXD6RST);
            rcu_periph_reset_disable(RCU_LINFLEXD6RST);
            break;
        case LINFLEXD_LIN7:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN7 */
            rcu_periph_reset_enable(RCU_LINFLEXD7RST);
            rcu_periph_reset_disable(RCU_LINFLEXD7RST);
            break;
        case LINFLEXD_LIN8:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN8 */
            rcu_periph_reset_enable(RCU_LINFLEXD8RST);
            rcu_periph_reset_disable(RCU_LINFLEXD8RST);
            break;
        case LINFLEXD_LIN9:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN9 */
            rcu_periph_reset_enable(RCU_LINFLEXD9RST);
            rcu_periph_reset_disable(RCU_LINFLEXD9RST);
            break;
        case LINFLEXD_LIN10:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN10 */
            rcu_periph_reset_enable(RCU_LINFLEXD10RST);
            rcu_periph_reset_disable(RCU_LINFLEXD10RST);
            break;
        case LINFLEXD_LIN11:
            /* perform software reset */
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
            /* reset LIN11 */
            rcu_periph_reset_enable(RCU_LINFLEXD11RST);
            rcu_periph_reset_disable(RCU_LINFLEXD11RST);
            break;
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
        default:
            break;
              }
         }
    }
    return reval;
}

/*!
    \brief      initialize LIN peripheral parameter structure (API_ID(0x0002U))
    \param[in]  initpara: pointer to linflexd_lin_parameter_struct structure
    \param[out] none
    \retval     none
*/
void linflexd_lin_struct_para_init(linflexd_lin_parameter_struct *initpara)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        initpara->baudRate = DEFAULT_BAUDRATE;
        initpara->ismaster = LINFlexD_MASTER;
        initpara->breakLength = LINFlexD_BREAK_13_BIT;
        initpara->autobaudEnable = SET;
        initpara->responseTimeoutValue = DEFAULT_RES_TIMEOUT_VALUE;
        initpara->headerTimeoutValue = DEFAULT_HEAD_TIMEOUT_VALUE;
        initpara->filterCount = DEFAULT_FILTER_COUNT_VALUE;
        initpara->slaveFilterCfgPtr = NULL;
        initpara->classicID = NULL;
        initpara->numOfClassicID = DEFAULT_NUM_CLASSICID_VALUE;
        initpara->linStatecaputure = LINFLEXD_STATE_CAPTURE_ENABLE;
        initpara->checksumCalculaton = LINFLEXD_CHECKSUM_CALC_ENABLE;
        initpara->checksumField = LINFLEXD_CHECKSUM_FIELD_ENABLE;
        initpara->automaticWakeUp = LINFLEXD_WAKEUP_HARDWARE_CLEAR;
        initpara->bypassFilter = BYPASS_LINFLEXD_FILTER_ENABLE;
        initpara->slaveSyncLength = LINFLEXD_SLAVE_BREAK_10_BIT;
        initpara->receiverBufferLock = LINFLEXD_RECEIVER_BUFFER_LOCKED;
    }

}

/*!
    \brief      initialize LIN peripheral (API_ID(0x0003U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  initpara: LIN parameter initialization struct, members and values:
                  baudRate              : LIN communication baudrate (uint32_t)
                  ismaster              : LINFlexD_SLAVE, LINFlexD_MASTER
                  breakLength           : LINFlexD_BREAK_10_BIT, LINFlexD_BREAK_11_BIT, ..., LINFlexD_BREAK_50_BIT
                  autobaudEnable        : SET, RESET
                  responseTimeoutValue  : 0x00~0x0F
                  headerTimeoutValue    : 0x00~0x7F
                  filterCount           : 0~15
                  slaveFilterCfgPtr     : pointer to linflexd_lin_id_filter_struct array
                  classicID             : pointer to uint8_t array of classic checksum IDs
                  numOfClassicID        : number of classic checksum IDs (uint8_t)
                  linStatecaputure      : LINFLEXD_STATE_CAPTURE_DISABLE , LINFLEXD_STATE_CAPTURE_ENABLE
                  checksumCalculaton    : LINFLEXD_CHECKSUM_CALC_ENABLE , LINFLEXD_CHECKSUM_CALC_DISABLE
                  checksumField         : LINFLEXD_CHECKSUM_FIELD_ENABLE , LINFLEXD_CHECKSUM_FIELD_DISABLE
                  automaticWakeUp       : LINFLEXD_AUTOSYNC_DISABLE , LINFLEXD_AUTOSYNC_ENABLE
                  bypassFilter          : BYPASS_LINFLEXD_FILTER_DISABLE , BYPASS_LINFLEXD_FILTER_ENABLE
                  slaveSyncLength       : LINFLEXD_SLAVE_BREAK_11_BIT , LINFLEXD_SLAVE_BREAK_10_BIT
                  receiverBufferLock    : LINFLEXD_RECEIVER_BUFFER_NORMAL , LINFLEXD_RECEIVER_BUFFER_LOCKED
    \param[out]  none
    \retval      ErrStatus:SUCCESS or ERROR
*/
ErrStatus linflexd_lin_init(uint32_t lin_periph, linflexd_lin_parameter_struct *initpara)
{
    ErrStatus reval = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(initpara)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg;
        uint32_t timeout_cnt;
        timeout_cnt = 0xFFFFU;
        /* enter init mode */
        linflexd_lin_enter_init_mode(lin_periph);
        /* enter init mode */
        while ((linflexd_lin_get_state(lin_periph) != LINFlexD_STATE_INIT_MODE)  && (0U != timeout_cnt)) {
            timeout_cnt--;
        }
        if(linflexd_lin_get_state(lin_periph) != LINFlexD_STATE_INIT_MODE){
            /* set error status */
            reval = ERROR;
        } else {
            /* lin init */
            /* configure LIN state capture */
            LINFLEXD_LINCR1(lin_periph) &= ~(LINFLEXD_LINCR1_NLSE);
            LINFLEXD_LINCR1(lin_periph) |= (LINFLEXD_LINCR1_NLSE & initpara->linStatecaputure);
            /* configure LIN automatic wake up */
            LINFLEXD_LINCR1(lin_periph) &= ~(LINFLEXD_LINCR1_AUTOWU);
            LINFLEXD_LINCR1(lin_periph) |= (LINFLEXD_LINCR1_AUTOWU & initpara->automaticWakeUp);
            /* configure LIN bypass filter */
            LINFLEXD_LINCR1(lin_periph) &= ~(LINFLEXD_LINCR1_BF);
            LINFLEXD_LINCR1(lin_periph) |= (LINFLEXD_LINCR1_BF & initpara->bypassFilter);
            /* configure LIN slave sync length */
            LINFLEXD_LINCR1(lin_periph) &= ~(LINFLEXD_LINCR1_SSBL);
            LINFLEXD_LINCR1(lin_periph) |= (LINFLEXD_LINCR1_SSBL & initpara->slaveSyncLength);
            /* configure LIN receiver buffer lock */
            LINFLEXD_LINCR1(lin_periph) &= ~(LINFLEXD_LINCR1_RBLM);
            LINFLEXD_LINCR1(lin_periph) |= (LINFLEXD_LINCR1_RBLM & initpara->receiverBufferLock);
            /* configure LIN checksum calculaton */
            LINFLEXD_LINCR1(lin_periph) &= ~(LINFLEXD_LINCR1_CCD);
            LINFLEXD_LINCR1(lin_periph) |= (LINFLEXD_LINCR1_CCD & initpara->checksumCalculaton);
            /* configure LIN checksum field */
            LINFLEXD_LINCR1(lin_periph) &= ~(LINFLEXD_LINCR1_CFD);
            LINFLEXD_LINCR1(lin_periph) |= (LINFLEXD_LINCR1_CFD & initpara->checksumField);
                
            /* set break length */
            reg = LINFLEXD_LINCR1(lin_periph);
            reg &= ~LINFLEXD_LINCR1_MBL;
            reg |= ((uint32_t)initpara->breakLength << 8U) & LINFLEXD_LINCR1_MBL;
            LINFLEXD_LINCR1(lin_periph) = reg;
            if(initpara->ismaster == LINFlexD_MASTER) {
                linflexd_lin_master_mode_enable(lin_periph);
            } else {
                linflexd_lin_master_mode_disable(lin_periph);
            }
            
            /* configure filter if needed */
            if((initpara->filterCount > 0U) && (initpara->slaveFilterCfgPtr != NULL)) {
                linflexd_lin_config_id_filter(lin_periph, initpara->filterCount, initpara->slaveFilterCfgPtr);
            } else {
                /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
            }
            
            /* set timeout value */
            linflexd_lin_timeout_disable(lin_periph);
            linflexd_lin_set_timeout_value(lin_periph, initpara->responseTimeoutValue, initpara->headerTimeoutValue);
             /* if autobaud is enabled */
            if ((initpara->autobaudEnable==SET) && (initpara->ismaster == LINFlexD_SLAVE))
            {
                /* always detect LIN Break from Master */
                linflexd_lin_auto_sync_enable(lin_periph);
            }
            
            /* set baudrate */
            linflexd_lin_baudrate_set(lin_periph, initpara->baudRate);
            /* Disable Idle on Bit Error */
            linflexd_lin_idle_bit_error_disable(lin_periph);
            /* exit init mode */
            linflexd_lin_enter_normal_mode(lin_periph);
        }
    }
    return reval;
}

/*!
    \brief      set the baud rate of the LIN module (API_ID(0x0004U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  baudval: baudrate value
    \param[out] none
    \retval     none
    \note       This function may contain scenarios leading to an infinite loop.
                Modify it according to the actual usage requirements.
*/
void linflexd_lin_baudrate_set(uint32_t lin_periph, uint32_t baudval)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else if(NOT_LINFLEXD_LIN_BAUDRATE(baudval)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t uclk;
        float prescaler, fraction, floatNumerator;
        uint32_t mantissa, fractionDenominator;
        uint8_t fractionNumerator;
        uint8_t init_mode_entered = 0U;
        uint32_t timeout_cnt;
        timeout_cnt = 0xFFFFU;
        
        /* get LIN peripheral clock frequency, user should implement this function as needed */
        uclk = rcu_clock_freq_get(CK_LINFLEXD);
        /* Compute divider and fraction */
        prescaler = (float)uclk / ((float)baudval * 16.0f); 
        mantissa = (uint32_t)prescaler;
        fraction = prescaler - (float)mantissa;
        fractionDenominator = ((uint32_t)1U << (uint32_t)BAUDRATE_FRACTION_WIDTH); 
        floatNumerator = (fraction * (float)fractionDenominator) + 0.5f;
        fractionNumerator = (uint8_t)floatNumerator;
        
        if(fractionNumerator == fractionDenominator) {
            fractionNumerator = 0U;
            mantissa++;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
        
        /* Enter init mode if not already */
        if((linflexd_lin_get_state (lin_periph) != LINFlexD_STATE_INIT_MODE)) {
            linflexd_lin_enter_init_mode(lin_periph);
            while ((linflexd_lin_get_state(lin_periph) != LINFlexD_STATE_INIT_MODE)  && (0U != timeout_cnt)) {
                timeout_cnt--;
            }
            init_mode_entered = 1U;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
        
        /* Set baudrate registers */
        linflexd_lin_set_integer_baudrate(lin_periph,mantissa);
        linflexd_lin_set_fractional_baudrate(lin_periph,fractionNumerator);
        
        /* Restore normal mode if we entered init mode */
        if(init_mode_entered == 1U) {
            linflexd_lin_enter_normal_mode(lin_periph);
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
}

/*!
    \brief      set integer part of LIN baudrate register (API_ID(0x0005U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  ibr: integer baudrate value
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_integer_baudrate(uint32_t lin_periph, uint32_t ibr)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t regValTemp = LINFLEXD_LINIBRR(lin_periph);
        regValTemp &= ~LINFLEXD_LINIBRR_IBR;
        regValTemp |= (ibr & (LINFLEXD_LINIBRR_IBR));
        LINFLEXD_LINIBRR(lin_periph) = regValTemp;
    }
}

/*!
    \brief      set fractional part of LIN baudrate register (API_ID(0x0006U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  fbr: fractional baudrate value
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_fractional_baudrate(uint32_t lin_periph, uint8_t fbr)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t regValTemp = LINFLEXD_LINFBRR(lin_periph);
        regValTemp &= ~LINFLEXD_LINFBRR_FBR;
        regValTemp |= (fbr & (LINFLEXD_LINFBRR_FBR) );
        LINFLEXD_LINFBRR(lin_periph) = regValTemp;
    }
}

/*!
    \brief      LIN transmit data  (API_ID(0x0007U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  data: pointer to data buffer
    \param[in]  size: data length (1~8)
    \param[out] none
    \retval     none
*/
void linflexd_lin_data_transmit(uint32_t lin_periph, uint8_t *data, uint8_t size)
{
    uint8_t i ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(data)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0007U), ERR_PARAM_POINTER);
    } else if(NOT_LINFLEXD_LIN_DATA_LENGTH_SIZE(size)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t tmp_val[2] = {0U};
        uint32_t data_32b ;
        
        if(size <= 4U) {
            for(i = 0U; i < size; i++) {
                data_32b = data[i];
                tmp_val[0] |= (data_32b << (8U * i));
            }
            LINFLEXD_BDRL(lin_periph) = tmp_val[0];
        } else {
            /* first 4 bytes */
            tmp_val[0] = ((uint32_t)data[0]) |
                         ((uint32_t)data[1] << 8U) |
                         ((uint32_t)data[2] << 16U) |
                         ((uint32_t)data[3] << 24U);
            /* remaining bytes */
            for(i = 4U; i < size; i++) {
                data_32b = data[i];
                tmp_val[1] |= (data_32b << (8U * (i - 4U)));
            }
            LINFLEXD_BDRL(lin_periph) = tmp_val[0];
            LINFLEXD_BDRM(lin_periph) = tmp_val[1];
        }
    }
}

/*!
    \brief      LIN receive data (API_ID(0x0008U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] data: pointer to data buffer
    \param[in]  size: data length (1~8)
    \retval     none
*/
void linflexd_lin_data_receive(uint32_t lin_periph, uint8_t *data, uint8_t size)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(data)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0008U), ERR_PARAM_POINTER);
    } else if(NOT_LINFLEXD_LIN_DATA_LENGTH_SIZE(size)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint8_t i ;
        uint32_t tmp_val[2] = {0U};
        
        tmp_val[0] = LINFLEXD_BDRL(lin_periph);
        tmp_val[1] = LINFLEXD_BDRM(lin_periph);
        
        if(size <= 4U) {
            for(i = 0U; i < size; i++) {
                data[i] = (uint8_t)((tmp_val[0] >> (i * 8U)) & 0xFFU);
            }
        } else {
            /* first 4 bytes */
            data[0] = (uint8_t)(tmp_val[0] & 0xFFU);
            data[1] = (uint8_t)((tmp_val[0] >> 8U) & 0xFFU);
            data[2] = (uint8_t)((tmp_val[0] >> 16U) & 0xFFU);
            data[3] = (uint8_t)((tmp_val[0] >> 24U) & 0xFFU);
            /* remaining bytes */
            for(i = 4U; i < size; i++) {
                data[i] = (uint8_t)((tmp_val[1] >> ((i - 4U) * 8U)) & 0xFFU);
            }
        }
    }
}

/*!
    \brief      get LIN checksum (API_ID(0x0009U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     uint8_t: checksum value
*/
uint8_t linflexd_lin_get_checksum(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
        return 0U;
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        return (uint8_t)(LINFLEXD_LINCFR(lin_periph) & 0xFFU);
    }
}

/*!
    \brief      LIN module enters initialization mode (API_ID(0x000AU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_enter_init_mode(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR1(lin_periph) &= ~LINFLEXD_LINCR1_SLEEP;
        LINFLEXD_LINCR1(lin_periph) |= LINFLEXD_LINCR1_INIT;
    }
}

/*!
    \brief      LIN module enters normal operation mode (API_ID(0x000BU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_enter_normal_mode(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR1(lin_periph) &= ~LINFLEXD_LINCR1_SLEEP;
        LINFLEXD_LINCR1(lin_periph) &= ~LINFLEXD_LINCR1_INIT;
    }
}

/*!
    \brief      set LIN module to enter or exit sleep mode (API_ID(0x000CU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  enable: 1 to enter sleep, 0 to exit sleep
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_sleep_mode(uint32_t lin_periph, uint8_t enable)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != enable) {
            LINFLEXD_LINCR1(lin_periph) |= LINFLEXD_LINCR1_SLEEP;
        } else {
            LINFLEXD_LINCR1(lin_periph) &= ~LINFLEXD_LINCR1_SLEEP;
        }
    }
}

/*!
    \brief      get LIN module sleep mode (API_ID(0x000DU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus linflexd_lin_get_sleep_mode(uint32_t lin_periph)
{
    FlagStatus ret = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (LINFLEXD_LINCR1(lin_periph) & LINFLEXD_LINCR1_SLEEP)) {
            ret = SET;
        } else {
            ret = RESET;
        }
    }
    return ret;
}

/*!
    \brief      enable LIN module auto synchronization (API_ID(0x000EU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_auto_sync_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR1(lin_periph) |= LINFLEXD_LINCR1_LASE;
    }
}

/*!
    \brief      disable LIN module auto synchronization (API_ID(0x000FU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_auto_sync_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
      LINFLEXD_LINCR1(lin_periph) &= ~LINFLEXD_LINCR1_LASE;
    }
}

/*!
    \brief      enable LIN module loopback mode (API_ID(0x0010U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_loopback_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg;
        reg = LINFLEXD_LINCR1(lin_periph);
        /* enter loopback mode */
        reg |= LINFLEXD_LINCR1_LBKM;
        LINFLEXD_LINCR1(lin_periph) = reg;
    }
}

/*!
    \brief      disable LIN module loopback mode (API_ID(0x0011U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_loopback_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg;
        reg = LINFLEXD_LINCR1(lin_periph);
        /* exit loopback mode */
        reg &= ~LINFLEXD_LINCR1_LBKM;
        LINFLEXD_LINCR1(lin_periph) = reg;
    }
}

/*!
    \brief      configure LIN module transfer direction (API_ID(0x0012U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  dir: transfer direction, refer to linflexd_lin_direction_enum
                    only one parameter can be selected which is shown as below:
      \arg        LINFlexD_RX: receive frames in LIN
      \arg        LINFlexD_TX: transmit frames in LIN
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_direction(uint32_t lin_periph, linflexd_lin_direction_enum dir)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(LINFlexD_TX == dir) {
            LINFLEXD_BIDR(lin_periph) |= LINFLEXD_BIDR_DIR;
        } else {
            LINFLEXD_BIDR(lin_periph) &= ~LINFLEXD_BIDR_DIR;
        }
    }
}

/*!
    \brief      configure LIN module transfer data length (API_ID(0x0013U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  size: data length (0~8)
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_data_length(uint32_t lin_periph, uint32_t size)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_BIDR(lin_periph) &= ~LINFLEXD_BIDR_DFL;
        LINFLEXD_BIDR(lin_periph) |= ((uint32_t)(size-1U) << LINFlexD_BIDR_SIZE_OFFSET) & LINFLEXD_BIDR_DFL;
    }
}

/*!
    \brief      configure LIN module identifier filter (API_ID(0x0014U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  id: 0x0-0x3F
    \param[in]  size: data length 0-8
    \param[in]  dir
                only one parameter can be selected which is shown as below:
      \arg        LINFlexD_RX: receive frames in LIN
      \arg        LINFlexD_TX: transmit frames in LIN
    \param[in]  ccs
                only one parameter can be selected which is shown as below:
      \arg        LIN_ENHANCED_CHECKSUM: enhanced checksum
      \arg        LIN_CLASSIC_CHECKSUM: classic checksum
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_bidr(uint32_t lin_periph, uint8_t id, uint32_t size, linflexd_lin_direction_enum dir, linflexd_lin_checksum_enum ccs)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t reg = 0U;
        reg |= ((uint32_t)id & 0x3FU);
        reg |= ((uint32_t)ccs << 8U) & LINFLEXD_BIDR_CCS;
        reg |= ((uint32_t)dir << 9U) & LINFLEXD_BIDR_DIR;
        reg |= ((uint32_t)(size-1U) << 10U) & LINFLEXD_BIDR_DFL;
        LINFLEXD_BIDR(lin_periph) = reg;
    }
}

/*!
    \brief      enable header transfer request (API_ID(0x0015U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_header_request_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) |= LINFLEXD_LINCR2_HTRQ;
    }
}

/*!
    \brief      enable data transfer request (API_ID(0x0016U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_data_request_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) |= LINFLEXD_LINCR2_DTRQ;
    }
}

/*!
    \brief      enable LIN module wakeup request (API_ID(0x0017U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_wakeup_request_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
     {
         LINFLEXD_LINCR2(lin_periph) |= LINFLEXD_LINCR2_WURQ;
     }
}

/*!
    \brief      config LINFlexD_LIN auto wakeup hardware to clear the SLEEP bit (API_ID(0x0018U))
    \param[in]  lin_periph: LINFLEXD_LINx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_autowake_hw_clear(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;
        reg = LINFLEXD_LINCR1(lin_periph);
        /* set hardware clear SLEEP bit */
        reg |= LINFLEXD_LINCR1_AUTOWU;
        LINFLEXD_LINCR1(lin_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_LIN auto wakeup software to clear the SLEEP bit (API_ID(0x0019U))
    \param[in]  lin_periph: LINFLEXD_LINx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_autowake_sw_clear(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;
        reg = LINFLEXD_LINCR1(lin_periph);
        /* set software clear SLEEP bit */
        reg &= ~LINFLEXD_LINCR1_AUTOWU;
        LINFLEXD_LINCR1(lin_periph) = reg;
    }
}

/*!
    \brief      enable LIN module data discard request (API_ID(0x001AU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_data_discard_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) |= LINFLEXD_LINCR2_DDRQ;
    }
}

/*!
    \brief      enable idle on bit error for LIN module (API_ID(0x001BU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_idle_bit_error_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) |= LINFLEXD_LINCR2_IOBE;
    }
}

/*!
    \brief      disable idle on bit error for LIN module (API_ID(0x001CU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_idle_bit_error_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) &= ~LINFLEXD_LINCR2_IOBE;
    }
}

/*!
    \brief      enable idle on parity error for LIN module (API_ID(0x001DU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_idle_parity_error_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) |= LINFLEXD_LINCR2_IOPE;
    }
}

/*!
    \brief      disable idle on parity error for LIN module (API_ID(0x001EU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_idle_parity_error_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) &= ~LINFLEXD_LINCR2_IOPE;
    }
}

/*!
    \brief      enable LIN module transfer abort request (API_ID(0x001FU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_transfer_abort_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) |= LINFLEXD_LINCR2_ABRQ;
    }
}

/*!
    \brief      get LIN transfer abort status (API_ID(0x0020U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     uint8_t: 1 if abort requested, 0 otherwise
*/
uint8_t linflexd_lin_get_transfer_abort(uint32_t lin_periph)
{
    uint8_t ret = 0U ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0020U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (LINFLEXD_LINCR2(lin_periph) & LINFLEXD_LINCR2_ABRQ)) {
            ret = 1U;
        } else {
            ret = 0U;
        }
    }
    return ret;
}

/*!
    \brief      set ID in LIN BIDR register (API_ID(0x0021U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  id: 0x0-0x3F
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_bidr_id(uint32_t lin_periph, uint8_t id)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0021U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_BIDR(lin_periph) = (LINFLEXD_BIDR(lin_periph) & ~LINFLEXD_BIDR_ID) | ((uint32_t)id & 0x3FU);
    }
}

/*!
    \brief      get ID in LIN BIDR register (API_ID(0x0022U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     uint8_t: ID value
*/
uint8_t linflexd_lin_get_bidr_id(uint32_t lin_periph)
{
    uint8_t temp = 0U;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0022U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        temp = (uint8_t)(LINFLEXD_BIDR(lin_periph) & LINFlexD_BIDR_ID_MASK);
    }
    return temp;
}

/*!
    \brief      enable LIN master mode (API_ID(0x0023U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_master_mode_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0023U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR1(lin_periph) |= LINFLEXD_LINCR1_MME;
    }
}

/*!
    \brief      disable LIN master mode (API_ID(0x0024U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_master_mode_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0024U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR1(lin_periph) &= ~LINFLEXD_LINCR1_MME;
    }
}

/*!
    \brief      get current working state of LIN (API_ID(0x0025U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     linflexd_lin_hw_state_enum: LIN hardware state
*/
linflexd_lin_hw_state_enum linflexd_lin_get_state(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0025U), ERR_PERIPH);
        return LINFlexD_STATE_IDLE_MODE;
    }
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t state = (LINFLEXD_LINSR(lin_periph) & LINFLEXD_LINSR_LINS) >> 12U;
        return (linflexd_lin_hw_state_enum)state;
    }
}

/*!
    \brief      enable timeout (API_ID(0x0026U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_timeout_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0026U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINTCSR(lin_periph) &= ~ LINFLEXD_LINTCSR_MODE;
        LINFLEXD_LINTCSR(lin_periph) = (LINFLEXD_LINTCSR_IOT | LINFLEXD_LINTCSR_TOCE);
    }
}

/*!
    \brief      disable timeout (API_ID(0x0027U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_timeout_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0027U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINTCSR(lin_periph) &= ~ (LINFLEXD_LINTCSR_IOT | LINFLEXD_LINTCSR_TOCE);
        LINFLEXD_LINTCSR(lin_periph) = LINFLEXD_LINTCSR_MODE;
    }
}

/*!
    \brief      set timeout value (API_ID(0x0028U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  responseTimeout:  timeout value:0x00-0x0F
    \param[in]  headerTimeout: header timeout value:0x00-0x7F
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_timeout_value(uint32_t lin_periph, uint8_t responseTimeout, uint8_t headerTimeout)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0028U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINTOCR(lin_periph) = ((uint32_t)responseTimeout << 8U) | ((uint32_t)headerTimeout & 0x7FU);
    }
}

/*!
    \brief      set oc value (API_ID(0x0029U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  oc1: output compare value 1:0xFFU
    \param[in]  oc2: output compare value 2:0xFFU
    \param[out] none
    \retval     none
*/
void linflexd_lin_set_oc_value(uint32_t lin_periph, uint8_t oc1, uint8_t oc2)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0029U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINOCR(lin_periph) = ((uint32_t)oc2 << 8U) | ((uint32_t)oc1 & 0xFFU);
    }
}

/*!
    \brief      configure LIN identifier filter (API_ID(0x002AU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  filterCount: number of filters
    \param[in]  config: pointer to linflexd_lin_id_filter_struct array
                and the member values are shown as below:
                filterEnable: SET, RESET
                maskEnable: 0U,1U
                dataFieldLength: 0-7
                direction: LINFlexD_RX, LINFlexD_TX
                checksumType: LIN_ENHANCED_CHECKSUM, LIN_CLASSIC_CHECKSUM
                id: 0x0-0x3F
                data:LIN Data pointer
    \param[out] none
    \retval     none
*/
void linflexd_lin_config_id_filter(uint32_t lin_periph, uint8_t filtercount, linflexd_lin_id_filter_struct *config)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x002AU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        uint32_t i,ifer = 0U, ifmr = 0U;
        for(i = 0U; i < filtercount; i++) {
            if (SET==config[i].filterEnable) {
            ifer |= ((uint32_t)1U << i); 
            ifmr |= (uint32_t)config[i].maskEnable << (i / 2U);
            LINFLEXD_IFCR(lin_periph, i) = ((uint32_t)((config[i].dataFieldLength)-1U) << 10U) |
                                           ((uint32_t)(config[i].direction) << 9U) |
                                           ((uint32_t)(config[i].checksumType) << 8U) |
                                           ((uint32_t)(config[i].id) & 0x3FU);
            LINFLEXD_LINCR1(lin_periph) &= ~LINFlexD_LINCR1_BF_MASK;
            } else {
                /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
            }
        }
        LINFLEXD_IFER(lin_periph) |= ifer;
        LINFLEXD_IFMR(lin_periph) |= ifmr;
    }
}

/*!
    \brief      get identifier filter match index (API_ID(0x002BU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     uint8_t: filter match index
*/
uint8_t linflexd_lin_get_filter_match_index(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x002BU), ERR_PERIPH);
        return 0U;
    }
#endif /* FW_DEBUG_ERR_REPORT */
    {
        return (uint8_t)(LINFLEXD_IFMI(lin_periph) & LINFlexD_IFMI_IFMI_MASK);
    }
}

/*!
    \brief      set byte order msb enable for LIN data transmission (API_ID(0x002CU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_tx_order_msb_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x002CU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_TDFBM;
    }
}

/*!
    \brief      set byte order msb disable for LIN data transmission (API_ID(0x002DU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_tx_order_msb_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x002DU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_GCR(lin_periph) &= ~ LINFLEXD_GCR_TDFBM;
    }
}

/*!
    \brief      set byte order msb enable for LIN data reception (API_ID(0x002EU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_rx_order_msb_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x002EU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_RDFBM;
    }
}

/*!
    \brief      set byte order msb disable for LIN data reception (API_ID(0x002FU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_rx_order_msb_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x002FU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_GCR(lin_periph) &= ~ LINFLEXD_GCR_RDFBM;
    }
}

/*!
    \brief      configure number of stop bits for LIN (API_ID(0x0030U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  stopBits: 0 for 1 stop bit, 1 for 2 stop bits
    \param[out] none
    \retval     none
*/
void linflexd_lin_stop_bit_config(uint32_t lin_periph, uint8_t stopBits)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0030U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != stopBits) {
            LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_STOP;
        } else {
            LINFLEXD_GCR(lin_periph) &= ~LINFLEXD_GCR_STOP;
        }
    }
}

/*!
    \brief      perform software reset on LIN module enable (API_ID(0x0031U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_soft_reset_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0031U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_GCR(lin_periph) |= LINFLEXD_GCR_SR;
    }
}

/*!
    \brief      perform software reset on LIN module disable (API_ID(0x0032U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_soft_reset_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0032U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_GCR(lin_periph) &= ~LINFLEXD_GCR_SR;
    }
}

/*!
    \brief      enable LIN signal inversion function (API_ID(0x0033U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_inversion_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0033U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_GCR(lin_periph) |= (LINFLEXD_GCR_TDLIS | LINFLEXD_GCR_RDLIS);
    }
}

/*!
    \brief      disable LIN signal inversion function (API_ID(0x0034U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_inversion_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0034U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_GCR(lin_periph) &= ~(LINFLEXD_GCR_TDLIS | LINFLEXD_GCR_RDLIS);
    }
}

/*!
    \brief      Two Bit delimiter enable for LIN module (API_ID(0x0035U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void linflexd_lin_two_bit_delimiter_enable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0035U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) &= ~LINFLEXD_LINCR2_TBDE;
        LINFLEXD_LINCR2(lin_periph) |= LINFLEXD_LINCR2_TBDE;
    }
    
}

/*!
    \brief      Two Bit delimiter disnable for LIN module (API_ID(0x0036U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  none
    \param[out] none
    \retval     none
*/
void linflexd_lin_two_bit_delimiter_disable(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0036U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINCR2(lin_periph) &= ~LINFLEXD_LINCR2_TBDE;
    }
    
}

/*!
    \brief      set LIN module to enter STOP request (API_ID(0x0037U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     none
*/
void linflexd_lin_stop_request_set(uint32_t lin_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0037U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LIN_STCTL(lin_periph) |= LINFLEXD_LIN_STCTL_STOP;
    }
}

/*!
    \brief      get LIN module STOP request acknowledge status (API_ID(0x0038U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[out] none
    \retval     uint8_t: 1 if acknowledged, 0 otherwise
*/
uint8_t linflexd_lin_stop_ack_get(uint32_t lin_periph)
{
    uint8_t ret = 0U ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0038U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (LINFLEXD_LIN_STCTL(lin_periph) & LINFLEXD_LIN_STCTL_ACK)) {
            ret = 1U;
        } else {
            ret = 0U;
        }
    }
    return ret;
}

/*!
    \brief      enable DMA TX function for LIN (API_ID(0x0039U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  lin_dma_channel: LINFLEXD_DMATX_CHANNELx(x=0..15)
    \param[out] none
    \retval     none
*/
void linflexd_lin_dma_tx_enable(uint32_t lin_periph,linflexd_dma_tx_channel_enum lin_dma_channel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0039U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_DMATXE(lin_periph) |= (uint32_t)lin_dma_channel;
    }
}

/*!
    \brief      disable DMA TX function for LIN (API_ID(0x003AU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  lin_dma_channel: LINFLEXD_DMATX_CHANNELx(x=0..15)
    \param[out] none
    \retval     none
*/
void linflexd_lin_dma_tx_disable(uint32_t lin_periph,linflexd_dma_tx_channel_enum lin_dma_channel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x003AU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_DMATXE(lin_periph) &= ~(uint32_t)lin_dma_channel;
    }
}

/*!
    \brief      enable DMA RX function for LIN (API_ID(0x003BU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  lin_dma_channel: LINFLEXD_DMARX_CHANNELx(x=0..15)
    \param[out] none
    \retval     none
*/
void linflexd_lin_dma_rx_enable(uint32_t lin_periph,linflexd_dma_rx_channel_enum lin_dma_channel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x003BU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_DMARXE(lin_periph) |= (uint32_t)lin_dma_channel;
    }
}

/*!
    \brief      disable DMA RX function for LIN (API_ID(0x003CU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  lin_dma_channel: LINFLEXD_DMARX_CHANNELx(x=0..15)
    \param[out] none
    \retval     none
*/
void linflexd_lin_dma_rx_disable(uint32_t lin_periph,linflexd_dma_rx_channel_enum lin_dma_channel)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x003CU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_DMARXE(lin_periph) &= ~(uint32_t)lin_dma_channel;
    }
}

/*!
    \brief      get LIN status flag (API_ID(0x003DU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  flag: status flag(s) to get
                only one parameter can be selected which is shown as below:
    \arg        LINFLEXD_FLAG_HRF          :header received flag 
    \arg        LINFLEXD_FLAG_DTF          :data transmission completed flag 
    \arg        LINFLEXD_FLAG_DRF          :data reception completed flag 
    \arg        LINFLEXD_FLAG_WUF          :wakeup flag 
    \arg        LINFLEXD_FLAG_RXBUSY       :receiver busy flag 
    \arg        LINFLEXD_FLAG_DRBNE        :data reception buffer not empty flag 
    \arg        LINFLEXD_FLAG_RMB          :release message buffer 
    \arg        LINFLEXD_FLAG_AUTOSYNC_COMP:autosynchronization complete 
    \arg        LINFLEXD_FLAG_NF           :noise flag 
    \arg        LINFLEXD_FLAG_BOF          :buffer overrun flag 
    \arg        LINFLEXD_FLAG_FEF          :framing error flag 
    \arg        LINFLEXD_FLAG_IDPEF        :ID parity error flag  
    \arg        LINFLEXD_FLAG_SDEF         :break delimiter error flag
    \arg        LINFLEXD_FLAG_SFEF         :sync field error flag 
    \arg        LINFLEXD_FLAG_CEF          :checksum error flag 
    \arg        LINFLEXD_FLAG_BEF          :bit error flag 
    \arg        LINFLEXD_FLAG_OCF          :output compare flag 
    \arg        LINFLEXD_FLAG_SZF          :stuck at zero flag 
    \param[out] none
    \retval     uint32_t: status flag
*/
FlagStatus linflexd_lin_flag_get(uint32_t lin_periph, linflexd_flag_enum flag)
{
    FlagStatus reval = RESET ;
    
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x003DU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        if(0U != (LINFLEXD_REG_VAL(lin_periph, flag) & BIT(LINFLEXD_BIT_POS(flag)))) {
            reval = SET;
        } else {
            reval = RESET;
        }
    }
    return reval;
}

/*!
    \brief      clear LIN status flag (API_ID(0x003EU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  flag: status flag(s) to clear
                only one parameter can be selected which is shown as below:
    \arg        LINFLEXD_FLAG_HRF          :header received flag 
    \arg        LINFLEXD_FLAG_DTF          :data transmission completed flag 
    \arg        LINFLEXD_FLAG_DRF          :data reception completed flag 
    \arg        LINFLEXD_FLAG_WUF          :wakeup flag 
    \arg        LINFLEXD_FLAG_RXBUSY       :receiver busy flag 
    \arg        LINFLEXD_FLAG_DRBNE        :data reception buffer not empty flag 
    \arg        LINFLEXD_FLAG_RMB          :release message buffer 
    \arg        LINFLEXD_FLAG_AUTOSYNC_COMP:autosynchronization complete 
    \arg        LINFLEXD_FLAG_NF           :noise flag 
    \arg        LINFLEXD_FLAG_BOF          :buffer overrun flag 
    \arg        LINFLEXD_FLAG_FEF          :framing error flag 
    \arg        LINFLEXD_FLAG_IDPEF        :ID parity error flag  
    \arg        LINFLEXD_FLAG_SDEF         :break delimiter error flag
    \arg        LINFLEXD_FLAG_SFEF         :sync field error flag 
    \arg        LINFLEXD_FLAG_CEF          :checksum error flag 
    \arg        LINFLEXD_FLAG_BEF          :bit error flag 
    \arg        LINFLEXD_FLAG_OCF          :output compare flag 
    \arg        LINFLEXD_FLAG_SZF          :stuck at zero flag 
    \param[out] none
    \retval     none
*/
void linflexd_lin_flag_clear(uint32_t lin_periph, linflexd_flag_enum flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x003EU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_REG_VAL(lin_periph, flag) = BIT(LINFLEXD_BIT_POS((uint32_t)flag));
    }
}

/*!
    \brief      enable interrupt (API_ID(0x003FU))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  interrupt: linflexd interrupt
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_INT_HRIE  header received interrupt
      \arg        LINFLEXD_INT_DTIE  data transmitted interrupt
      \arg        LINFLEXD_INT_DRIE  data reception complete interrupt
      \arg        LINFLEXD_INT_TOIE  timeout interrupt
      \arg        LINFLEXD_INT_WUIE  wakeup interrupt
      \arg        LINFLEXD_INT_LSIE  LIN state interrupt
      \arg        LINFLEXD_INT_BOIE  buffer overrun interrupt
      \arg        LINFLEXD_INT_FEIE  frame error interrupt
      \arg        LINFLEXD_INT_HEIE  header error interrupt
      \arg        LINFLEXD_INT_CEIE  checksum error interrupt
      \arg        LINFLEXD_INT_BEIE  bit error interrupt
      \arg        LINFLEXD_INT_OCIE  output compare interrupt
      \arg        LINFLEXD_INT_SZIE  stuck at zero interrupt
    \param[out] none
    \retval     none
*/
void linflexd_lin_interrupt_enable(uint32_t lin_periph, linflexd_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x003FU), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINIER(lin_periph) |= (uint32_t)interrupt;
    }
}

/*!
    \brief      disable interrupt (API_ID(0x0040U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  interrupt: linflexd interrupt

                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_INT_HRIE  header received interrupt
      \arg        LINFLEXD_INT_DTIE  data transmitted interrupt
      \arg        LINFLEXD_INT_DRIE  data reception complete interrupt
      \arg        LINFLEXD_INT_TOIE  timeout interrupt
      \arg        LINFLEXD_INT_WUIE  wakeup interrupt
      \arg        LINFLEXD_INT_LSIE  LIN state interrupt
      \arg        LINFLEXD_INT_BOIE  buffer overrun interrupt
      \arg        LINFLEXD_INT_FEIE  frame error interrupt
      \arg        LINFLEXD_INT_HEIE  header error interrupt
      \arg        LINFLEXD_INT_CEIE  checksum error interrupt
      \arg        LINFLEXD_INT_BEIE  bit error interrupt
      \arg        LINFLEXD_INT_OCIE  output compare interrupt
      \arg        LINFLEXD_INT_SZIE  stuck at zero interrupt
    \param[out] none
    \retval     none
*/
void linflexd_lin_interrupt_disable(uint32_t lin_periph, linflexd_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0040U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_LINIER(lin_periph) &= ~(uint32_t)interrupt;
    }
}

/*!
    \brief      get LIN interrupt flag status (API_ID(0x0041U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  flag: interrupt flag(s) to get
                only one parameter can be selected which is shown as below:
    \arg        LINFLEXD_INT_FLAG_HRF     :header received interrupt and flag 
    \arg        LINFLEXD_INT_FLAG_DTF     :data transmission completed interrupt and flag
    \arg        LINFLEXD_INT_FLAG_DRF     :data reception completed interrupt and flag 
    \arg        LINFLEXD_INT_FLAG_WUF     :wakeup interrupt and flag 
    \arg        LINFLEXD_INT_FLAG_BOF     :buffer overrun interrupt and flag
    \arg        LINFLEXD_INT_FLAG_FEF     :framing error interrupt and flag
    \arg        LINFLEXD_INT_FLAG_IDPEF   :ID parity error interrupt and flag
    \arg        LINFLEXD_INT_FLAG_SDEF    :Sync Break delimiter error interrupt and flag
    \arg        LINFLEXD_INT_FLAG_SFEF    :Sync field error interrupt and flag
    \arg        LINFLEXD_INT_FLAG_CEF     :checksum error interrupt and flag 
    \arg        LINFLEXD_INT_FLAG_BEF     :bit error interrupt and flag 
    \arg        LINFLEXD_INT_FLAG_OCF     :output compare interrupt and flag
    \arg        LINFLEXD_INT_FLAG_SZF     :stuck at zero interrupt and flag
    \param[out] none
    \retval     uint32_t: interrupt flag status
*/
FlagStatus linflexd_lin_interrupt_flag_get(uint32_t lin_periph, linflexd_interrupt_flag_enum flag)
{
    FlagStatus reval = RESET ;
    uint32_t intenable, flagstatus;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0041U), ERR_PERIPH);
    }else
#endif /* FW_DEBUG_ERR_REPORT */
    {

        /* get the interrupt enable bit status */
        intenable = (LINFLEXD_REG_VAL2(lin_periph,flag) & BIT(LINFLEXD_BIT_POS2(flag)));
        /* get the corresponding flag bit status */
        flagstatus = (LINFLEXD_REG_VAL(lin_periph,flag) & BIT(LINFLEXD_BIT_POS(flag)));

        if((0U != flagstatus) && (0U != intenable)) {
            reval = SET;
        } else {
            /* this code is written to avoid MISRA 15.7 (no 'else' at end of 'if ... else if' chain) */
        }
    }
    return reval;
}

/*!
    \brief      clear LIN interrupt flag (API_ID(0x0042U))
    \param[in]  lin_periph: LINFLEXDx(x=0..11)
    \param[in]  flag: interrupt flag(s) to clear
                only one parameter can be selected which is shown as below:
    \arg           LINFLEXD_INT_FLAG_HRF        :header received interrupt and flag 
    \arg           LINFLEXD_INT_FLAG_DTF        :data transmission completed interrupt and flag 
    \arg           LINFLEXD_INT_FLAG_DRF        :data reception completed interrupt and flag
    \arg           LINFLEXD_INT_FLAG_WUF        :wakeup interrupt and flag 
    \arg           LINFLEXD_INT_FLAG_BOF        :buffer overrun interrupt and flag
    \arg           LINFLEXD_INT_FLAG_FEF        :framing error interrupt and flag
    \arg           LINFLEXD_INT_FLAG_IDPEF      :ID parity error interrupt and flag
    \arg           LINFLEXD_INT_FLAG_SDEF       :Sync Break delimiter error interrupt and flag
    \arg           LINFLEXD_INT_FLAG_SFEF       :Sync field error interrupt and flag
    \arg           LINFLEXD_INT_FLAG_CEF        :checksum error interrupt and flag 
    \arg           LINFLEXD_INT_FLAG_BEF        :bit error interrupt and flag 
    \arg           LINFLEXD_INT_FLAG_OCF        :output compare interrupt and flag
    \arg           LINFLEXD_INT_FLAG_SZF        :stuck at zero interrupt and flag
    \param[out] none
    \retval     none
*/
void linflexd_lin_interrupt_flag_clear(uint32_t lin_periph, linflexd_interrupt_flag_enum flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_LIN_PERIPH(lin_periph)) {
        fw_debug_report_err(LIN_MODULE_ID, API_ID(0x0042U), ERR_PERIPH);
    } else
#endif /* FW_DEBUG_ERR_REPORT */
    {
        LINFLEXD_REG_VAL(lin_periph, flag) = BIT(LINFLEXD_BIT_POS((uint32_t)flag));
    }
}
