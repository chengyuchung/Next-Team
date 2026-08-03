/*!
    \file    gd32a7xx_jdc.c
    \brief   JDC driver

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

#include "gd32a7xx_jdc.h"

/*!
    \brief      jdc write output data (API_ID: 0x0001U)
    \param[in]  data: specify the data send to JTAG
    \param[out] none
    \retval     none
*/
void jdc_jout_write(uint32_t data)
{
    JDC_JOUT_APB_DATA = data;
}

/*!
    \brief      jdc read input data (API_ID: 0x0002U)
    \param[in]  none
    \param[out] none
    \retval     data from JTAG
*/
uint32_t jdc_jin_read(void)
{
    return JDC_JIN_APB_DATA;
}

/*!
    \brief      get jdc flag (API_ID: 0x0003U)
    \param[in]  flag
                only one parameter can be selected which is shown as below:
      \arg        JDC_INT_FLAG_JOUT: the JOUTSET bit is cleared by tool reading JDC_JOUT_DATA register interrupt flag
      \arg        JDC_RDY_FLAG_JOUT: JOUT set
      \arg        JDC_INT_FLAG_JIN: the new data is written to the JDC_JIN_APB_DATA register interrupt flag
      \arg        JDC_RDY_FLAG_JIN: JIN set
    \param[out] none
    \retval     flag state, SET or RESET
*/
FlagStatus jdc_flag_get(uint32_t flag)
{
    FlagStatus ret_flag = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_JDC_FLAG(flag)) {
        fw_debug_report_err(JDC_MODULE_ID, API_ID(0x0003U), ERR_PARAM_INVALID);
    }else
#endif
    {
        if(0U != (JDC_STAT & flag)){
            ret_flag = SET;
        }
    }
    return ret_flag;
}

/*!
    \brief      enable jdc interrupt (API_ID: 0x0004U)
    \param[in]  interrupt:
                only one parameter can be selected which is shown as below:
      \arg        JDC_INT_JOUT: JOUT interrupt enable
      \arg        JDC_INT_JIN: JIN interrupt enable
    \param[out] none
    \retval     none
*/
void jdc_interrupt_enable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_JDC_INT(interrupt)) {
        fw_debug_report_err(JDC_MODULE_ID, API_ID(0x0004U), ERR_PARAM_INVALID);
    }else
#endif
    {
        JDC_INTEN |= interrupt;
    }
}

/*!
    \brief      disable jdc interrupt (API_ID: 0x0005U)
    \param[in]  interrupt:
                only one parameter can be selected which is shown as below:
      \arg        JDC_INT_JOUT: JOUT interrupt disable
      \arg        JDC_INT_JIN: JIN interrupt disable
    \param[out] none
    \retval     none
*/
void jdc_interrupt_disable(uint32_t interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_JDC_INT(interrupt)) {
        fw_debug_report_err(JDC_MODULE_ID, API_ID(0x0005U), ERR_PARAM_INVALID);
    }else
#endif
    {
        JDC_INTEN &= ~interrupt;
    }
}

/*!
    \brief      get JDC interrupt flag (API_ID: 0x0006U)
    \param[in]  int_flag
                only one parameter can be selected which is shown as below:
      \arg        JDC_INT_FLAG_JOUT: the JOUTSET bit is cleared by tool reading JDC_JOUT_DATA register interrupt flag
      \arg        JDC_INT_FLAG_JIN: the new data is written to the JDC_JIN_APB_DATA register interrupt flag
    \param[out] none
    \retval     none
*/
FlagStatus jdc_interrupt_flag_get(uint32_t int_flag)
{
    FlagStatus ret_flag = RESET;
    uint32_t intenable, flagstatus;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_JDC_INT_FLAG(int_flag)) {
        fw_debug_report_err(JDC_MODULE_ID, API_ID(0x0006U), ERR_PARAM_INVALID);
    }else
#endif
    {
        /* get the interrupt enable bit status */
        intenable = JDC_INTEN;
        /* get the corresponding flag bit status */
        flagstatus = JDC_STAT;

        if(0U != (intenable & flagstatus & int_flag)){
            ret_flag =  SET;
        }
    }
    return ret_flag;
}

/*!
    \brief      clear JDC interrupt flag (API_ID: 0x0007U)
    \param[in]  int_flag
                only one parameter can be selected which is shown as below:
      \arg        JDC_INT_FLAG_JOUT: the JOUTSET bit is cleared by tool reading JDC_JOUT_DATA register interrupt flag
      \arg        JDC_INT_FLAG_JIN: the new data is written to the JDC_JIN_APB_DATA register interrupt flag
    \param[out] none
    \retval     none
*/
void jdc_interrupt_flag_clear(uint32_t int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_JDC_INT_FLAG(int_flag)) {
        fw_debug_report_err(JDC_MODULE_ID, API_ID(0x0007U), ERR_PARAM_INVALID);
    }else
#endif
    {
        /* clear by write 1*/
        JDC_STAT = int_flag;
    }
}
