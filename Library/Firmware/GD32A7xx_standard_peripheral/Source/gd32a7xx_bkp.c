/*!
    \file    gd32a7xx_bkp.c
    \brief   BKP driver

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

#include "gd32a7xx_bkp.h"

#define TAMPER_FLAG_SHIFT          ((uint8_t)0x08U)

/*!
    \brief      write BKP data register (API_ID(0x0001U))
    \param[in]  register_number: refer to bkp data register number
                only one parameter can be selected which is shown as below:
      \arg        BKP_DATA_x(x = 0..9): BKP data register number x
    \param[in]  data: the data to be write in BKP data register
    \param[out] none
    \retval     none
*/
void bkp_data_write(uint32_t register_number, uint16_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BKP_REGISTER_NUMBER(register_number)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0001U), ERR_PARAM_INVALID);
    }else
#endif
    {
        BKP_DATA0_9(register_number) = data;
    }
}

/*!
    \brief      read BKP data register (API_ID(0x0002U))
    \param[in]  register_number: refer to bkp_data_register_enum
                only one parameter can be selected which is shown as below:
      \arg        BKP_DATA_x(x = 0..9): BKP data register number x
    \param[out] none
    \retval     data of BKP data register
*/
uint16_t bkp_data_read(uint32_t register_number)
{
    uint16_t data = 0;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BKP_REGISTER_NUMBER(register_number)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0002U), ERR_PARAM_INVALID);
    }else
#endif
    {
        data = BKP_DATA0_9(register_number);
    }
    return data;
}

/*!
    \brief      enable RTC clock calibration output (API_ID(0x0003U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_rtc_calibration_output_enable(void)
{
    BKP_OCTL |= (uint16_t)BKP_OCTL_COEN;
}

/*!
    \brief      disable RTC clock calibration output (API_ID(0x0004U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_rtc_calibration_output_disable(void)
{
    BKP_OCTL &= (uint16_t)~BKP_OCTL_COEN;
}

/*!
    \brief      enable RTC alarm or second signal output (API_ID(0x0005U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_rtc_signal_output_enable(void)
{
    BKP_OCTL |= (uint16_t)BKP_OCTL_ASOEN;
}

/*!
    \brief      disable RTC alarm or second signal output (API_ID(0x0006U))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_rtc_signal_output_disable(void)
{
    BKP_OCTL &= (uint16_t)~BKP_OCTL_ASOEN;
}

/*!
    \brief      select RTC output (API_ID(0x0007U))
    \param[in]  output_sel: RTC output selection
                only one parameter can be selected which is shown as below:
      \arg        RTC_OUTPUT_ALARM_PULSE: RTC alarm pulse is selected as the RTC output
      \arg        RTC_OUTPUT_SECOND_PULSE: RTC second pulse is selected as the RTC output
    \param[out] none
    \retval     none
*/
void bkp_rtc_output_select(uint16_t output_sel)
{
    uint16_t ctl ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_RTC_OUTPUT_SEL(output_sel)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    }else
#endif
    {
        ctl = BKP_OCTL;
        ctl &= (uint16_t)~BKP_OCTL_ROSEL;
        ctl |= (output_sel & (uint16_t)BKP_OCTL_ROSEL);
        BKP_OCTL = ctl;
    }
}

/*!
    \brief      select RTC clock output (API_ID(0x0008U))
    \param[in]  clock_sel: RTC clock output selection
                only one parameter can be selected which is shown as below:
      \arg        RTC_CLOCK_DIV_64: RTC clock div 64
      \arg        RTC_CLOCK_DIV_1: RTC clock
    \param[out] none
    \retval     none
*/
void bkp_rtc_clock_output_select(uint16_t clock_sel)
{
    uint16_t ctl;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CLK_OUTPUT_SEL(clock_sel)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0008U), ERR_PARAM_INVALID);
    }else
#endif
    {
        ctl = BKP_OCTL;
        ctl &= (uint16_t)~BKP_OCTL_CCOSEL;
        ctl |= (clock_sel & (uint16_t)BKP_OCTL_CCOSEL);
        BKP_OCTL = ctl;
    }
}

/*!
    \brief      RTC clock calibration direction (API_ID(0x0009U))
    \param[in]  direction: RTC clock calibration direction
                only one parameter can be selected which is shown as below:
      \arg        RTC_CLOCK_SLOWED_DOWN: RTC clock slow down
      \arg        RTC_CLOCK_SPEED_UP: RTC clock speed up
    \param[out] none
    \retval     none
*/
void bkp_rtc_clock_calibration_direction(uint16_t direction)
{
    uint16_t ctl ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CLK_CALIBRATE_DIR(direction)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0009U), ERR_PARAM_INVALID);
    }else
#endif
    {
        ctl = BKP_OCTL;
        ctl &= (uint16_t)~BKP_OCTL_CALDIR;
        ctl |= (direction & (uint16_t)BKP_OCTL_CALDIR);
        BKP_OCTL = ctl;
    }
}

/*!
    \brief      set RTC clock calibration value (API_ID(0x000AU)) 
    \param[in]  value: RTC clock calibration value
                only one parameter can be selected which is shown as below:
      \arg        0x00 - 0x7F
    \param[out] none
    \retval     none
*/
void bkp_rtc_calibration_value_set(uint8_t value)
{
    uint16_t ctl;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_CLK_CALIBRATE_VALUE(value)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x000AU), ERR_PARAM_OUT_OF_RANGE);
    }else
#endif
    {
        ctl = BKP_OCTL;
        ctl &= (uint16_t)~BKP_OCTL_RCCV;
        ctl |= ((uint16_t)OCTL_RCCV(value) & (uint16_t)BKP_OCTL_RCCV);
        BKP_OCTL = ctl;
    }
}

/*!
    \brief      enable tamper pin detection (API_ID(0x000BU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_tamper_detection_enable(void)
{
    BKP_TPCTL |= (uint16_t)BKP_TPCTL_TPEN;
}

/*!
    \brief      disable tamper pin detection (API_ID(0x000CU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_tamper_detection_disable(void)
{
    BKP_TPCTL &= (uint16_t)~BKP_TPCTL_TPEN;
}

/*!
    \brief      set tamper pin active level (API_ID(0x000DU))
    \param[in]  level: tamper active level
                only one parameter can be selected which is shown as below:
      \arg        TAMPER_PIN_ACTIVE_HIGH: the tamper pin is active high
      \arg        TAMPER_PIN_ACTIVE_LOW: the tamper pin is active low
    \param[out] none
    \retval     none
*/
void bkp_tamper_active_level_set(uint16_t level)
{
        uint16_t ctl ;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_TAMPER_ACTIVE_LEVEL(level)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x000DU), ERR_PARAM_INVALID);
    }else
#endif
    {
        ctl = BKP_TPCTL;
        ctl &= (uint16_t)~BKP_TPCTL_TPAL;
        ctl |= (level & (uint16_t)BKP_TPCTL_TPAL);
        BKP_TPCTL = ctl;
    }
}

/*!
    \brief      enable tamper pin interrupt (API_ID(0x000EU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_tamper_interrupt_enable(void)
{
    BKP_TPCS |= (uint16_t)BKP_TPCS_TPIE;
}

/*!
    \brief      disable tamper pin interrupt (API_ID(0x000FU))
    \param[in]  none
    \param[out] none
    \retval     none
*/
void bkp_tamper_interrupt_disable(void)
{
    BKP_TPCS &= (uint16_t)~BKP_TPCS_TPIE;
}

/*!
    \brief      get bkp flag state (API_ID(0x0010U))
    \param[in]  flag:
      \arg        BKP_FLAG_TAMPER: tamper event flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus bkp_flag_get(uint16_t flag)
{
    FlagStatus status = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BKP_FLAG(flag)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    }else
#endif
    {
        if(0U != (BKP_TPCS & flag)){
            status = SET;
        }else{
            status = RESET;
        }
    }
    return status;
}

/*!
    \brief      clear BKP flag state (API_ID(0x0011U))
    \param[in]  flag:
      \arg        BKP_FLAG_TAMPER: tamper event flag
    \param[out] none
    \retval     none
*/
void bkp_flag_clear(uint16_t flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BKP_FLAG(flag)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0011U), ERR_PARAM_INVALID);
        return ;
    }else
#endif
    {
        BKP_TPCS |= (uint16_t)(flag >> TAMPER_FLAG_SHIFT);
    }
}

/*!
    \brief      get BKP interrupt flag state (API_ID(0x0012U))
    \param[in]  int_flag
      \arg        BKP_INT_FLAG_TAMPER: tamper interrupt flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus bkp_interrupt_flag_get(uint16_t int_flag)
{
    FlagStatus status = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BKP_INT_FLAG(int_flag)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0012U), ERR_PARAM_INVALID);
    }else
#endif
    {
        if(0U != (BKP_TPCS & int_flag)){
            status = SET;
        }else{
            status = RESET;
        }
    }
    return status;
}

/*!
    \brief      clear BKP interrupt flag state (API_ID(0x0013U))
    \param[in]  int_flag:
      \arg        BKP_INT_FLAG_TAMPER: tamper interrupt flag
    \param[out] none
    \retval     none
*/
void bkp_interrupt_flag_clear(uint16_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_BKP_INT_FLAG(int_flag)){
        fw_debug_report_err(BKP_MODULE_ID, API_ID(0x0013U), ERR_PARAM_INVALID);
        return;
    }else
#endif
    {
        BKP_TPCS |= (uint16_t)(int_flag >> TAMPER_FLAG_SHIFT);
    }
}
