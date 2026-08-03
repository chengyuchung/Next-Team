/*!
    \file    gd32a7xx_linflexd_uart.c
    \brief   LINFlexD_UART driver

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
#include "gd32a7xx_linflexd_uart.h"

#define DEFAULT_BAUDRATE            115200U                /* default baud rate value */
#define DEFAULT_OSR                 16U                    /* the OSR value of default */
#define BAUDRATE_FRACTION_WIDTH     4U                     /* the fraction baudrate width */
#define LINFLEXD_UART_DELAY         0x8FFFFU               /* infinite loop delay count */

/*!
    \brief      reset LINFlexD_UART (API_ID(0x0001U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
ErrStatus linflexd_uart_deinit(uint32_t linflexd_uart_periph)
{
    ErrStatus reval = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0001U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t timeout_cnt;
        /* enter initialization mode */
        linflexd_uart_initmode_enter(linflexd_uart_periph);
        /* load delay count */
        timeout_cnt = LINFLEXD_UART_DELAY;
        while ((linflexd_uart_state_get(linflexd_uart_periph) != LINFLEXD_UART_STATE_INIT_MODE)  && (0U != timeout_cnt)) {
            timeout_cnt--;
        }
        
        if(linflexd_uart_state_get(linflexd_uart_periph) != LINFLEXD_UART_STATE_INIT_MODE){
            /* set error status */
            reval = ERROR;
        } else {
            /* reset LINFlexD_UART register */
            LINFLEXD_UART_LINIER(linflexd_uart_periph)      = 0x00000000U;
            LINFLEXD_UART_LINSR(linflexd_uart_periph)       = 0x00080327U;
            LINFLEXD_UART_LINESR(linflexd_uart_periph)      = 0x0000FF81U;
            LINFLEXD_UART_UARTCR(linflexd_uart_periph)      = 0x00000000U;
            LINFLEXD_UART_UARTSR(linflexd_uart_periph)      = 0x0000C7AFU;
            LINFLEXD_UART_LINTCSR(linflexd_uart_periph)     = 0x00000200U;
            LINFLEXD_UART_LINOCR(linflexd_uart_periph)      = 0x0000FFFFU;
            LINFLEXD_UART_LINTOCR(linflexd_uart_periph)     = 0x00000E2CU;
            LINFLEXD_UART_LINFBRR(linflexd_uart_periph)     = 0x00000000U;
            LINFLEXD_UART_LINIBRR(linflexd_uart_periph)     = 0x00000000U;
            LINFLEXD_UART_LINCFR(linflexd_uart_periph)      = 0x00000000U;
            LINFLEXD_UART_LINCR2(linflexd_uart_periph)      = 0x00006000U;
            LINFLEXD_UART_BIDR(linflexd_uart_periph)        = 0x00000000U;
            LINFLEXD_UART_BDRL(linflexd_uart_periph)        = 0x00000000U;
            LINFLEXD_UART_BDRM(linflexd_uart_periph)        = 0x00000000U;
            LINFLEXD_UART_IFER(linflexd_uart_periph)        = 0x00000000U;
            LINFLEXD_UART_IFMR(linflexd_uart_periph)        = 0x00000000U;
            for(uint32_t i=0U;i<=15U;i++){
                LINFLEXD_UART_IFCR(linflexd_uart_periph, i) = 0x00000000U;
            }
            LINFLEXD_UART_GCR(linflexd_uart_periph)         = 0x00000000U;
            LINFLEXD_UART_UARTPTO(linflexd_uart_periph)     = 0x00000FFFU;
            LINFLEXD_UART_DMATXE(linflexd_uart_periph)      = 0x00000000U;
            LINFLEXD_UART_DMARXE(linflexd_uart_periph)      = 0x00000000U;
            LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph)   = 0x00000000U;
            LINFLEXD_UART_LINCR1(linflexd_uart_periph)      = 0x00000081U;
            LINFLEXD_UART_LINCR1(linflexd_uart_periph)      = 0x00000082U;

            switch(linflexd_uart_periph) {
            case LINFLEXD_UART0:
                /* reset LINFLEXD_UART0 */
                rcu_periph_reset_enable(RCU_LINFLEXD0RST);
                rcu_periph_reset_disable(RCU_LINFLEXD0RST);
                break;
            case LINFLEXD_UART1:
                /* reset LINFLEXD_UART1 */
                rcu_periph_reset_enable(RCU_LINFLEXD1RST);
                rcu_periph_reset_disable(RCU_LINFLEXD1RST);
                break;
            case LINFLEXD_UART2:
                /* reset LINFLEXD_UART2 */
                rcu_periph_reset_enable(RCU_LINFLEXD2RST);
                rcu_periph_reset_disable(RCU_LINFLEXD2RST);
                break;
            case LINFLEXD_UART3:
                /* reset LINFLEXD_UART3 */
                rcu_periph_reset_enable(RCU_LINFLEXD3RST);
                rcu_periph_reset_disable(RCU_LINFLEXD3RST);
                break;
            case LINFLEXD_UART4:
                /* reset LINFLEXD_UART4 */
                rcu_periph_reset_enable(RCU_LINFLEXD4RST);
                rcu_periph_reset_disable(RCU_LINFLEXD4RST);
                break;
            case LINFLEXD_UART5:
                /* reset LINFLEXD_UART5 */
                rcu_periph_reset_enable(RCU_LINFLEXD5RST);
                rcu_periph_reset_disable(RCU_LINFLEXD5RST);
                break;
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
            case LINFLEXD_UART6:
                /* reset LINFLEXD_UART6 */
                rcu_periph_reset_enable(RCU_LINFLEXD6RST);
                rcu_periph_reset_disable(RCU_LINFLEXD6RST);
                break;
            case LINFLEXD_UART7:
                /* reset LINFLEXD_UART7 */
                rcu_periph_reset_enable(RCU_LINFLEXD7RST);
                rcu_periph_reset_disable(RCU_LINFLEXD7RST);
                break;
            case LINFLEXD_UART8:
                /* reset LINFLEXD_UART8 */
                rcu_periph_reset_enable(RCU_LINFLEXD8RST);
                rcu_periph_reset_disable(RCU_LINFLEXD8RST);
                break;
            case LINFLEXD_UART9:
                /* reset LINFLEXD_UART9 */
                rcu_periph_reset_enable(RCU_LINFLEXD9RST);
                rcu_periph_reset_disable(RCU_LINFLEXD9RST);
                break;
            case LINFLEXD_UART10:
                /* reset LINFLEXD_UART10 */
                rcu_periph_reset_enable(RCU_LINFLEXD10RST);
                rcu_periph_reset_disable(RCU_LINFLEXD10RST);
                break;
            case LINFLEXD_UART11:
                /* reset LINFLEXD_UART11 */
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
    \brief      initialize the parameters of LINFlexD_UART struct with default values (API_ID(0x0002U))
    \param[in]  linflexd_uart_struct: pointer to a linflexd_uart_parameter_struct structure, which contains 
                                    the configuration information for the specified LINFlexD_UART peripheral, 
                                    and the member values are shown as below:
                baudrate:       baud rate
                parityenable:   parity control - ENABLE/DISABLE
                paritytype:     always 0/always 1/even/odd
                stopbitscount:  number of stop bits, 1 stop bit/2 stop bits/3 stop bits (only for receiver)
                wordlength:     number of bits per transmitted/received word
                txmodetype:     type of LINFlexD_UART tx transfer (buffer/fifo)
                rxmodetype:     type of LINFlexD_UART rx transfer (buffer/fifo)
    \param[out] none
    \retval     none
*/
void linflexd_uart_struct_para_init(linflexd_uart_parameter_struct *linflexd_uart_struct)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_VALID_POINTER(linflexd_uart_struct)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0002U), ERR_PARAM_POINTER);
    } else
#endif
    {
        /* configure the structure with default value */
        linflexd_uart_struct->baudrate = DEFAULT_BAUDRATE;
        linflexd_uart_struct->parityenable = DISABLE;
        linflexd_uart_struct->stopbitscount = LINFLEXD_UART_ONE_STOP_BIT;
        linflexd_uart_struct->wordlength = LINFLEXD_UART_8_BITS;
        linflexd_uart_struct->txmodetype = LINFLEXD_UART_TXRX_BUFFER_MODE;
        linflexd_uart_struct->rxmodetype = LINFLEXD_UART_TXRX_BUFFER_MODE;
    }
}

/*!
    \brief      initialize LINFlexD_UART parameter (API_ID(0x0003U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  linflexd_uart_struct: pointer to a linflexd_uart_parameter_struct structure, which contains 
                                    the configuration information for the specified LINFlexD_UART peripheral, 
                                    and the member values are shown as below:
                baudrate:       baud rate
                parityenable:   parity control - ENABLE/DISABLE
                paritytype:     always 0/always 1/even/odd
                stopbitscount:  number of stop bits, 1 stop bit/2 stop bits/3 stop bits (only for receiver)
                wordlength:     number of bits per transmitted/received word
                txmodetype:     type of LINFlexD_UART tx transfer (buffer/fifo)
                rxmodetype:     type of LINFlexD_UART rx transfer (buffer/fifo)
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
ErrStatus linflexd_uart_init(uint32_t linflexd_uart_periph, linflexd_uart_parameter_struct *linflexd_uart_struct)
{
    ErrStatus reval = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0003U), ERR_PERIPH);
    } else if(NOT_VALID_POINTER(linflexd_uart_struct)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0003U), ERR_PARAM_POINTER);
    } else if(NOT_LINFLEXD_UART_BAUDRATE(linflexd_uart_struct->baudrate)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0003U), ERR_PARAM_OUT_OF_RANGE);
    } else
#endif
    {
        uint32_t timeout_cnt;
        /* enter initialization mode */
        linflexd_uart_initmode_enter(linflexd_uart_periph);
        /* load delay count */
        timeout_cnt = LINFLEXD_UART_DELAY;
        while ((linflexd_uart_state_get(linflexd_uart_periph) != LINFLEXD_UART_STATE_INIT_MODE)  && (0U != timeout_cnt)) {
            timeout_cnt--;
        }
        
        if(linflexd_uart_state_get(linflexd_uart_periph) != LINFLEXD_UART_STATE_INIT_MODE){
            /* set error status */
            reval = ERROR;
        } else {
            /* set LINFlexD_UART mode */
            linflexd_uart_mode_set(linflexd_uart_periph, LINFLEXD_UART_MODE);

            /* set baudrate */
            reval = linflexd_uart_baudrate_set(linflexd_uart_periph, linflexd_uart_struct->baudrate);

            /* set LINFlexD_UART word length */
            linflexd_uart_wordlength_set(linflexd_uart_periph, linflexd_uart_struct->wordlength);
            linflexd_uart_txdatafieldlength_set(linflexd_uart_periph, (uint8_t)((uint8_t)linflexd_uart_struct->wordlength >> 1U));
            linflexd_uart_rxdatafieldlength_set(linflexd_uart_periph, (uint8_t)((uint8_t)linflexd_uart_struct->wordlength >> 1U));

            if(DISABLE == linflexd_uart_struct->parityenable){
                /* disable parity control */
                linflexd_uart_paritycontrol_disable(linflexd_uart_periph);
            } else {
                /* enable and set parity control */
                linflexd_uart_paritycontrol_enable(linflexd_uart_periph);
                linflexd_uart_paritytype_set(linflexd_uart_periph, linflexd_uart_struct->paritytype);
            }
            /* set stop bits count */
            linflexd_uart_rxstopbitscount_set(linflexd_uart_periph, linflexd_uart_struct->stopbitscount);
            linflexd_uart_txstopbitscount_set(linflexd_uart_periph, linflexd_uart_struct->stopbitscount);

            /* enable FIFO mode for DMA communication, or buffer mode for other communication */
            linflexd_uart_txmode_set(linflexd_uart_periph, linflexd_uart_struct->txmodetype);
            linflexd_uart_rxmode_set(linflexd_uart_periph, linflexd_uart_struct->rxmodetype);

            /* enter normal mode */
            linflexd_uart_normalmode_enter(linflexd_uart_periph);
        }
    }
    return reval;
}

/*!
    \brief      LINFlexD_UART enter init mode (API_ID(0x0004U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_initmode_enter(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0004U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* exit sleep mode */
        reg &= ~(LINFLEXD_UART_LINCR1_SLEEP);
        /* enter init mode */
        reg |= LINFLEXD_UART_LINCR1_INIT;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART enter normal mode (API_ID(0x0005U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_normalmode_enter(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0005U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* exit sleep mode */
        reg &= ~(LINFLEXD_UART_LINCR1_SLEEP);
        /* exit init mode */
        reg &= ~(LINFLEXD_UART_LINCR1_INIT);
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      enable LINFlexD_UART sleep mode (API_ID(0x0006U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_sleepmode_enable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0006U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* enter sleep mode */
        reg |= LINFLEXD_UART_LINCR1_SLEEP;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      disable LINFlexD_UART sleep mode (API_ID(0x0007U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_sleepmode_disable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0007U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* exit sleep mode */
        reg &= ~LINFLEXD_UART_LINCR1_SLEEP;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      get LINFlexD_UART sleep mode (API_ID(0x0008U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     sleepmode: RESET, sleep mode disabled; SET, sleep mode enabled
*/
FlagStatus linflexd_uart_sleepmode_get(uint32_t linflexd_uart_periph)
{
    FlagStatus sleepmode = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0008U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* check sleep mode bit */
        sleepmode = ((reg & LINFLEXD_UART_LINCR1_SLEEP) != 0x0U) ? SET : RESET;
    }
    return sleepmode;
}

/*!
    \brief      enable LINFlexD_UART receiver buffer locked mode (API_ID(0x0009U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_receiverbufferlocked_enable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0009U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* enter receiver buffer locked mode */
        reg |= LINFLEXD_UART_LINCR1_RBLM;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      disable LINFlexD_UART receiver buffer locked mode (API_ID(0x000AU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_receiverbufferlocked_disable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x000AU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* exit receiver buffer locked mode */
        reg &= ~LINFLEXD_UART_LINCR1_RBLM;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      enable LINFlexD_UART loopback mode (API_ID(0x000BU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_loopback_enable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x000BU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* enter loopback mode */
        reg |= LINFLEXD_UART_LINCR1_LBKM;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      disable LINFlexD_UART loopback mode (API_ID(0x000CU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_loopback_disable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x000CU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* exit loopback mode */
        reg &= ~LINFLEXD_UART_LINCR1_LBKM;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_UART auto wakeup hardware to clear the SLEEP bit (API_ID(0x000DU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_autowake_hw_clear(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x000DU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* set hardware clear SLEEP bit */
        reg |= LINFLEXD_UART_LINCR1_AUTOWU;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_UART auto wakeup software to clear the SLEEP bit (API_ID(0x000EU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_autowake_sw_clear(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x000EU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR1(linflexd_uart_periph);
        /* set software clear SLEEP bit */
        reg &= ~LINFLEXD_UART_LINCR1_AUTOWU;
        LINFLEXD_UART_LINCR1(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART integer baudrate set (API_ID(0x000FU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  ibr: integer baud rate
    \param[out] none
    \retval     none
*/
void linflexd_uart_integer_baudrate_set(uint32_t linflexd_uart_periph, uint32_t ibr)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x000FU), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_IBR(ibr)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x000FU), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINIBRR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_LINIBRR_IBR);
        /* set integer baud rate */
        reg |= ibr;
        LINFLEXD_UART_LINIBRR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART fractional baudrate set (API_ID(0x0010U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  fbr: fractional baud rate
    \param[out] none
    \retval     none
*/
void linflexd_uart_fractional_baudrate_set(uint32_t linflexd_uart_periph, uint8_t fbr)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0010U), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_FBR(fbr)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0010U), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINFBRR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_LINFBRR_FBR);
        reg |= fbr;
        LINFLEXD_UART_LINFBRR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      configure LINFlexD_UART baudrate value (API_ID(0x0011U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  baudval: baudrate value
    \param[out] none
    \retval     ErrStatus: SUCCESS or ERROR
    \note       This function includes timeout exit scenarios.
                Modify according to the user's actual usage scenarios.
*/
ErrStatus linflexd_uart_baudrate_set(uint32_t linflexd_uart_periph, uint32_t baudval)
{
    ErrStatus reval = SUCCESS;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0011U), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_BAUDRATE(baudval)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0011U), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t uclk;
        float prescaler;
        float fraction;
        uint32_t mantissa;
        uint32_t fractionDenominator;
        uint8_t fractionNumerator;
        uint32_t timeout_cnt;
        FlagStatus initstatus = RESET;

        /* get the clock frequency of LINFLEXD_UART */
        uclk = rcu_clock_freq_get(CK_LINFLEXD); 

        /* compute the values for baudrate divider mantissa and fraction */
        prescaler = (float)uclk / ((float)baudval * (float)DEFAULT_OSR);
        mantissa = (uint32_t)prescaler;
        fraction = prescaler - (float)mantissa;
        fractionDenominator = ((uint32_t)1U << (uint32_t)BAUDRATE_FRACTION_WIDTH);
        float floatNumerator = ((float)fraction * (float)fractionDenominator) + (float)0.5F;
        fractionNumerator = (uint8_t)(floatNumerator);

        if(fractionNumerator == fractionDenominator)
        {
            fractionNumerator = 0U;
            mantissa++;
        }

        if(linflexd_uart_state_get(linflexd_uart_periph) != LINFLEXD_UART_STATE_INIT_MODE)
        {
            /* request init mode and wait until the mode entry is complete */
            linflexd_uart_initmode_enter(linflexd_uart_periph);
            /* load delay count */
            timeout_cnt = LINFLEXD_UART_DELAY;
            while ((linflexd_uart_state_get(linflexd_uart_periph) != LINFLEXD_UART_STATE_INIT_MODE) && (0U != timeout_cnt)) {
                timeout_cnt--;
            }
            
            if(linflexd_uart_state_get(linflexd_uart_periph) == LINFLEXD_UART_STATE_INIT_MODE) {
                /* record init status */
                initstatus = SET;
            } else {
                /* record init status */
                initstatus = RESET;
                /* timeout, record the error status */
                reval = ERROR;
            }
        }
        
        /* write the computed values to registers */
        linflexd_uart_integer_baudrate_set(linflexd_uart_periph, mantissa);
        linflexd_uart_fractional_baudrate_set(linflexd_uart_periph, fractionNumerator);

        if(SET == initstatus)
        {
            /* enter normal mode */
            linflexd_uart_normalmode_enter(linflexd_uart_periph);
        }
    }
    return reval;
}

/*!
    \brief      LINFlexD_UART mode (LIN/UART) set (API_ID(0x0012U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: LINFlexD mode - LINFLEXD_LIN_MODE/LINFLEXD_UART_MODE
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_LIN_MODE: LIN mode
      \arg        LINFLEXD_UART_MODE: UART mode
    \param[out] none
    \retval     none
*/
void linflexd_uart_mode_set(uint32_t linflexd_uart_periph, linflexd_uart_mode_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0012U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_UART);
        /* set LINFlexD_UART mode */
        reg |= (uint32_t)mode;
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART current state get (API_ID(0x0013U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     state: current LINFlexD state
*/
linflexd_uart_state_enum linflexd_uart_state_get(uint32_t linflexd_uart_periph)
{
    linflexd_uart_state_enum state = LINFLEXD_UART_STATE_SLEEP_MODE;
    
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0013U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;
        uint32_t val;

        reg = LINFLEXD_UART_LINSR(linflexd_uart_periph);
        val = (reg & LINFLEXD_UART_LINSR_LINS) >> 12U;
        /* get LINFlexD_UART state */
        state = (linflexd_uart_state_enum)val;
    }
    return state;
}

/*!
    \brief      LINFlexD_UART word length set (API_ID(0x0014U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  length: the word length
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_7_BITS: 7 bits
      \arg        LINFLEXD_UART_8_BITS: 8 bits
      \arg        LINFLEXD_UART_15_BITS: 15 bits
      \arg        LINFLEXD_UART_16_BITS: 16 bits
    \param[out] none
    \retval     none
*/
void linflexd_uart_wordlength_set(uint32_t linflexd_uart_periph, linflexd_uart_word_length_enum length)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0014U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* set word length WL0 */
        reg &= ~(LINFLEXD_UART_UARTCR_WL0);
        reg |= ((uint32_t)length & 1U) << 1U;
        /* set word length WL1 */
        reg &= ~(LINFLEXD_UART_UARTCR_WL1);
        reg |= (((uint32_t)length >> 1U) & 1U) << 7U;
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      get LINFlexD_UART word length (API_ID(0x0015U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     length: the word length
*/
linflexd_uart_word_length_enum linflexd_uart_wordlength_get(uint32_t linflexd_uart_periph)
{
    linflexd_uart_word_length_enum wordlength = LINFLEXD_UART_7_BITS;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0015U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;
        uint8_t wl0;
        uint8_t wl1;
        
        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* extract WL0 (right shift 1 bit: low bit) */
        wl0 = (uint8_t)((reg & LINFLEXD_UART_UARTCR_WL0) >> 1U);
        /* extract WL1 (right shift 7 bit: high bit) */
        wl1 = (uint8_t)((reg & LINFLEXD_UART_UARTCR_WL1) >> 7U);
        /* get word length */
        if((0U == wl1) && (0U == wl0)){
            wordlength = LINFLEXD_UART_7_BITS;
        } else if((0U == wl1) && (1U == wl0)){
            wordlength = LINFLEXD_UART_8_BITS;
        } else if((1U == wl1) && (0U == wl0)){
            wordlength = LINFLEXD_UART_15_BITS;
        } else if((1U == wl1) && (1U == wl0)){
            wordlength = LINFLEXD_UART_16_BITS;
        } else{
        }
    }
    return wordlength;
}

/*!
    \brief      enable LINFlexD_UART parity bit (API_ID(0x0016U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_paritycontrol_enable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0016U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* enter parity control mode */
        reg |= LINFLEXD_UART_UARTCR_PCE;
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      disable LINFlexD_UART parity bit (API_ID(0x0017U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_paritycontrol_disable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0017U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* exit parity control mode */
        reg &= ~(LINFLEXD_UART_UARTCR_PCE);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART parity type set (API_ID(0x0018U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  paritytype: the type of parity.(odd/even/always 0/always 1), should be called only when the module is in init mode
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_PARITY_EVEN: even parity
      \arg        LINFLEXD_UART_PARITY_ODD: odd parity
      \arg        LINFLEXD_UART_PARITY_ALWAYS_0: always 0
      \arg        LINFLEXD_UART_PARITY_ALWAYS_1: always 1
    \param[out] none
    \retval     none
*/
void linflexd_uart_paritytype_set(uint32_t linflexd_uart_periph, linflexd_uart_parity_type_enum paritytype)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0018U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg |= LINFLEXD_UART_UARTCR_PCE;
        /* set parity control pc0 */
        reg &= ~(LINFLEXD_UART_UARTCR_PC0);
        reg |= ((uint32_t)paritytype & 1U) << 3U;
        /* set parity control pc1 */
        reg &= ~(LINFLEXD_UART_UARTCR_PC1);
        reg |= (((uint32_t)paritytype >> 1U) & 1U) << 6U;
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      configure LINFlexD_UART transmitter (API_ID(0x0019U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  txconfig: enable or disable LINFlexD_UART transmitter
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_TRANSMIT_ENABLE: enable LINFlexD_UART transmission
      \arg        LINFLEXD_UART_TRANSMIT_DISABLE: disable LINFlexD_UART transmission
    \param[out] none
    \retval     none
*/
void linflexd_uart_transmitter_config(uint32_t linflexd_uart_periph, uint32_t txconfig)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0019U), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_TRANSMITTER_CONFIG(txconfig)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0019U), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_TXEN);
        reg |= txconfig;
        /* configure transfer enable */
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      configure LINFlexD_UART receiver (API_ID(0x001AU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  rxconfig: enable or disable LINFlexD_UART receiver
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_RECEIVE_ENABLE: enable LINFlexD_UART reception
      \arg        LINFLEXD_UART_RECEIVE_DISABLE: disable LINFlexD_UART reception
    \param[out] none
    \retval     none
*/
void linflexd_uart_receiver_config(uint32_t linflexd_uart_periph, uint32_t rxconfig)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001AU), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_RECEIVER_CONFIG(rxconfig)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001AU), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_RXEN);
        reg |= rxconfig;
        /* configure receiver enable */
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART transmitter mode (FIFO/Buffer) (API_ID(0x001BU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: the mode of transmitter (FIFO/Buffer)
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_TXRX_BUFFER_MODE: buffer mode
      \arg        LINFLEXD_UART_TXRX_FIFO_MODE: FIFO mode
    \param[out] none
    \retval     none
*/
void linflexd_uart_txmode_set(uint32_t linflexd_uart_periph, linflexd_uart_txrx_mode_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001BU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_TFBM);
        /* set transmitter mode */
        reg |= (((uint32_t)mode) << 8U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART receiver mode (FIFO/Buffer) (API_ID(0x001CU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: the mode of receiver (FIFO/Buffer)
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_TXRX_BUFFER_MODE: buffer mode
      \arg        LINFLEXD_UART_TXRX_FIFO_MODE: FIFO mode
    \param[out] none
    \retval     none
*/
void linflexd_uart_rxmode_set(uint32_t linflexd_uart_periph, linflexd_uart_txrx_mode_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001CU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_RFBM);
        /* set receiver mode */
        reg |= (((uint32_t)mode) << 9U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART receiver data field length (API_ID(0x001DU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  length: data field length/FIFO depth
    \param[out] none
    \retval     none
*/
void linflexd_uart_rxdatafieldlength_set(uint32_t linflexd_uart_periph, uint8_t length)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001DU), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_RXTX_FIELDLENGTH(length)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001DU), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_RDFL_RFC);
        /* set receiver data field length */
        reg |= ((uint32_t)length << 10U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART transmitter data field length (API_ID(0x001EU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  length: data field length/FIFO depth.
    \param[out] none
    \retval     none
*/
void linflexd_uart_txdatafieldlength_set(uint32_t linflexd_uart_periph, uint8_t length)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001EU), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_RXTX_FIELDLENGTH(length)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001EU), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_TDFL_TFC);
        reg |= ((uint32_t)length << 13U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      flush the data register of LINFlexD_UART receive FIFO (API_ID(0x001FU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_rxfifo_flush(uint32_t linflexd_uart_periph) 
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x001FU), ERR_PERIPH);
    } else
#endif
    {
        volatile const uint8_t *fifoBase;

        /* get the address of the FIFO */
        fifoBase = (volatile const uint8_t *)(&LINFLEXD_UART_BDRM(linflexd_uart_periph));

        /* four dummy reads to flush the FIFO contents - discard the read values */
        (void)(*fifoBase);
        (void)(*fifoBase);
        (void)(*fifoBase);
        (void)(*fifoBase);
    }
}

/*!
    \brief      set LINFlexD_UART number of stop bits for Rx, the stop bits of TX and RX should be kept consistent (API_ID(0x0020U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  stopbitscount: number of stop bits
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_ONE_STOP_BIT: 1 stop bit
      \arg        LINFLEXD_UART_TWO_STOP_BITS: 2 stop bits
      \arg        LINFLEXD_UART_THREE_STOP_BITS: 3 stop bits
    \param[out] none
    \retval     none
*/
void linflexd_uart_rxstopbitscount_set(uint32_t linflexd_uart_periph, linflexd_uart_stop_bits_count_enum stopbitscount)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0020U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_SBUR);
        /* set rx stop bits count */
        reg |= ((uint32_t)stopbitscount << 17U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART number of stop bits for Tx, the stop bits of TX and RX should be kept consistent (API_ID(0x0021U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  stopbitscount: number of stop bits
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_ONE_STOP_BIT: 1 stop bit
      \arg        LINFLEXD_UART_TWO_STOP_BITS: 2 stop bits
    \param[out] none
    \retval     none
*/
void linflexd_uart_txstopbitscount_set(uint32_t linflexd_uart_periph, linflexd_uart_stop_bits_count_enum stopbitscount)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0021U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_GCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_GCR_STOP);
        /* set tx stop bits count */
        reg |= ((uint32_t)stopbitscount << 1U);
        LINFLEXD_UART_GCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART monitors the idle state of the reception line (API_ID(0x0022U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_idle_receive_line_monitor(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0022U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* set monitor idle state */
        reg |= LINFLEXD_UART_UARTCR_MIS;
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART monitors the number of bits to be received (API_ID(0x0023U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_number_receive_bits_monitor(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0023U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* set monitor idle state */
        reg &= ~(LINFLEXD_UART_UARTCR_MIS);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART reset mode of the timeout counter (API_ID(0x0024U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: timeout counter reset mode
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_TIMEOUT_SW_HANDLE: Timeout must be handled by software
      \arg        LINFLEXD_UART_TIMEOUT_DISABLE_AFTER_FRAMES: Timeout is disabled after receiving the configured number of data frames
    \param[out] none
    \retval     none
*/
void linflexd_uart_timeout_resetmode_set(uint32_t linflexd_uart_periph, linflexd_uart_timeout_control_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0024U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_DTU);
        /* set timeout reset mode */
        reg |= ((uint32_t)mode << 19U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART value of the timeout counter (API_ID(0x0025U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  value: timeout counter value
    \param[out] none
    \retval     none
*/
void linflexd_uart_idle_timeoutvalue_set(uint32_t linflexd_uart_periph, uint32_t value)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0025U), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_TIMEOUT_VALUE(value)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0025U), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTPTO(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTPTO_PTO);
        /* set idle timeout value */
        reg |= value;
        LINFLEXD_UART_UARTPTO(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      enable LINFlexD_UART special word length mode (API_ID(0x0026U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_specialwordlength_enable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0026U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* enter special word length mode */
        reg |= LINFLEXD_UART_UARTCR_WLS;
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      disable LINFlexD_UART special word length mode (API_ID(0x0027U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_specialwordlength_disable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0027U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* exit special word length mode */
        reg &= ~(LINFLEXD_UART_UARTCR_WLS);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART number of expected frame (API_ID(0x0028U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  framecount: number of expected frames
    \param[out] none
    \retval     none
*/
void linflexd_uart_expect_framenumber_set(uint32_t linflexd_uart_periph, uint8_t framecount)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0028U), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_EXPECTED_FRAME_COUNT(framecount)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0028U), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_NEF);
        /* set number of expected frames */
        reg |= ((uint32_t)framecount << 20U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      enable LINFlexD_UART reduced oversampling (API_ID(0x0029U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_reducedoversampling_enable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0029U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* enter reduced oversampling mode */
        reg |= LINFLEXD_UART_UARTCR_ROSE;
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      disable LINFlexD_UART reduced oversampling (API_ID(0x002AU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_reducedoversampling_disable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x002AU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        /* exit reduced oversampling mode */
        reg &= ~(LINFLEXD_UART_UARTCR_ROSE);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART over sampling rate (API_ID(0x002BU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  osrcount: number of over sampling rate, for proper functionality, only can take values 4, 5, 6, and 8
    \param[out] none
    \retval     none
*/
void linflexd_uart_oversamplingrate_set(uint32_t linflexd_uart_periph, uint8_t osrcount)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x002BU), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_OSRCOUNT(osrcount)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x002BU), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_OSR);
        /* set over sampling rate */
        reg |= ((uint32_t)osrcount << 24U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART configurable sample points (API_ID(0x002CU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  cspcount: number of configurable sample points, only can take values 2, 3, 4, and 5
    \param[out] none
    \retval     none
*/
void linflexd_uart_samplepoint_set(uint32_t linflexd_uart_periph, uint8_t cspcount)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x002CU), ERR_PERIPH);
    } else if(NOT_LINFLEXD_UART_CSPCOUNT(cspcount)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x002CU), ERR_PARAM_INVALID);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_UARTCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_UARTCR_CSP);
        /* set configurable sample points */
        reg |= ((uint32_t)cspcount << 28U);
        LINFLEXD_UART_UARTCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_UART transmit data first bit MSB (API_ID(0x002DU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: transmit data first bit mode
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_DATAFIRST_MSB: MSB first
      \arg        LINFLEXD_UART_DATAFIRST_LSB: LSB first
    \param[out] none
    \retval     none
*/
void linflexd_uart_transmit_datafirst_config(uint32_t linflexd_uart_periph, linflexd_uart_datafirst_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x002DU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_GCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_GCR_TDFBM);
        /* set transmitter data first bit */
        reg |= ((uint32_t)mode << 5U);
        LINFLEXD_UART_GCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_UART received data first bit MSB (API_ID(0x002EU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: received data first bit mode
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_DATAFIRST_MSB: MSB first
      \arg        LINFLEXD_UART_DATAFIRST_LSB: LSB first
    \param[out] none
    \retval     none
*/
void linflexd_uart_receive_datafirst_config(uint32_t linflexd_uart_periph, linflexd_uart_datafirst_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x002EU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_GCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_GCR_RDFBM);
        /* set receiver data first bit */
        reg |= ((uint32_t)mode << 4U);
        LINFLEXD_UART_GCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_UART transmit data invert (API_ID(0x002FU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: transmit invert mode
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_TXRX_INVERT_DISABLE: TX/RX data/pin level not inversion
      \arg        LINFLEXD_UART_TXRX_INVERT_ENABLE: TX/RX data/pin level inversion
    \param[out] none
    \retval     none
*/
void linflexd_uart_transmitdata_invert_config(uint32_t linflexd_uart_periph, linflexd_uart_txrx_invert_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x002FU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_GCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_GCR_TDLIS);
        /* set transmit data invert */
        reg |= ((uint32_t)mode << 3U);
        LINFLEXD_UART_GCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_UART receive data invert (API_ID(0x0030U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: receive invert mode
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_TXRX_INVERT_DISABLE: TX/RX data/pin level not inversion
      \arg        LINFLEXD_UART_TXRX_INVERT_ENABLE: TX/RX data/pin level inversion
    \param[out] none
    \retval     none
*/
void linflexd_uart_receivedata_invert_config(uint32_t linflexd_uart_periph, linflexd_uart_txrx_invert_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0030U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_GCR(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_GCR_RDLIS);
        /* set receive data invert */
        reg |= ((uint32_t)mode << 2U);
        LINFLEXD_UART_GCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_UART transmit pin invert (API_ID(0x0031U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: transmit invert mode
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_TXRX_INVERT_DISABLE: TX/RX data/pin level not inversion
      \arg        LINFLEXD_UART_TXRX_INVERT_ENABLE: TX/RX data/pin level inversion
    \param[out] none
    \retval     none
*/
void linflexd_uart_transmitpin_invert_config(uint32_t linflexd_uart_periph, linflexd_uart_txrx_invert_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0031U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_LIN_STCTL_TX_INV);
        /* set transmit pin invert */
        reg |= ((uint32_t)mode << 4U);
        LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      config LINFlexD_UART receive pin invert (API_ID(0x0032U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: receive invert mode
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_TXRX_INVERT_DISABLE: TX/RX data/pin level not inversion
      \arg        LINFLEXD_UART_TXRX_INVERT_ENABLE: TX/RX data/pin level inversion
    \param[out] none
    \retval     none
*/
void linflexd_uart_receivepin_invert_config(uint32_t linflexd_uart_periph, linflexd_uart_txrx_invert_enum mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0032U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_LIN_STCTL_RX_INV);
        /* set receive pin invert */
        reg |= ((uint32_t)mode << 5U);
        LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART soft reset (API_ID(0x0033U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_soft_reset(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0033U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_GCR(linflexd_uart_periph);
        /* set soft reset */
        reg |= LINFLEXD_UART_GCR_SR;
        LINFLEXD_UART_GCR(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART abort the current transmission (API_ID(0x0034U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_abort_request(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0034U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LINCR2(linflexd_uart_periph);
        /* set abort request */
        reg |= LINFLEXD_UART_LINCR2_ABRQ;
        LINFLEXD_UART_LINCR2(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      enable or disable LINFlexD_UART terminate the transmission (API_ID(0x0035U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  mode: ENABLE/DISABLE
    \param[out] none
    \retval     none
*/
void linflexd_uart_terminate_transmit(uint32_t linflexd_uart_periph, ControlStatus mode)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0035U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph);
        reg &= ~LINFLEXD_UART_LIN_STCTL_STOP;
        /* set stop bit */
        reg |= (uint32_t)mode;
        LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      LINFlexD_UART stop state get (API_ID(0x0036U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus linflexd_uart_stop_get(uint32_t linflexd_uart_periph)
{
    FlagStatus stopstate = RESET;
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0036U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph);
        /* check stop ack bit */
        stopstate = ((reg & LINFLEXD_UART_LIN_STCTL_ACK) != 0x0U) ? SET : RESET;
    }
    return stopstate;
}

/*!
    \brief      LINFlexD_UART transmit the tx data by byte (API_ID(0x0037U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  data: data byte
    \param[out] none
    \retval     none
*/
void linflexd_uart_byte_transmit(uint32_t linflexd_uart_periph, uint8_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0037U), ERR_PERIPH);
    } else
#endif
    {
        LINFLEXD_UART_BDRL(linflexd_uart_periph) = data;
    }
}

/*!
    \brief      LINFlexD_UART transmit the tx data by halfword (API_ID(0x0038U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  data: data half-word
    \param[out] none
    \retval     none
*/
void linflexd_uart_halfword_transmit(uint32_t linflexd_uart_periph, uint16_t data)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0038U), ERR_PERIPH);
    } else
#endif
    {
        LINFLEXD_UART_BDRL(linflexd_uart_periph) = data;
    }
}

/*!
    \brief      LINFlexD_UART receive the rx data by byte (API_ID(0x0039U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     data: data byte
*/
uint8_t linflexd_uart_byte_receive(uint32_t linflexd_uart_periph)
{
    uint8_t data = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0039U), ERR_PERIPH);
    } else
#endif
    {
        data = (uint8_t)LINFLEXD_UART_BDRM(linflexd_uart_periph);
    }
    return data;
}

/*!
    \brief      LINFlexD_UART receive the rx data by halfword (API_ID(0x003AU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     data: data half-word
*/
uint16_t linflexd_uart_halfword_receive(uint32_t linflexd_uart_periph)
{
    uint16_t data = 0U;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x003AU), ERR_PERIPH);
    } else
#endif
    {
        data = (uint16_t)LINFLEXD_UART_BDRM(linflexd_uart_periph);
    }
    return data;
}

/*!
    \brief      enable LINFlexD_UART tx dma channel (API_ID(0x003BU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_tx_dma_enable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x003BU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_DMATXE(linflexd_uart_periph);
        reg |= LINFLEXD_UART_DMATXE_DTE0;
        LINFLEXD_UART_DMATXE(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      disable LINFlexD_UART tx dma channel (API_ID(0x003CU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_tx_dma_disable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x003CU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_DMATXE(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_DMATXE_DTE0);
        LINFLEXD_UART_DMATXE(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      enable LINFlexD_UART rx dma channel (API_ID(0x003DU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_rx_dma_enable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x003DU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_DMARXE(linflexd_uart_periph);
        reg |= LINFLEXD_UART_DMARXE_DRE0;
        LINFLEXD_UART_DMARXE(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      disable LINFlexD_UART rx dma channel (API_ID(0x003EU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[out] none
    \retval     none
*/
void linflexd_uart_rx_dma_disable(uint32_t linflexd_uart_periph)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x003EU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_DMARXE(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_DMARXE_DRE0);
        LINFLEXD_UART_DMARXE(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      set LINFlexD_UART byte size for transmission on the IPS bus (API_ID(0x003FU))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  size: ips size type
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_IPS_DATA_WORD: 4 bytes
      \arg        LINFLEXD_UART_IPS_DATA_BYTE: 1 byte
      \arg        LINFLEXD_UART_IPS_DATA_HALFWORD: 2 bytes
    \param[out] none
    \retval     none
*/
void linflexd_uart_ips_size_set(uint32_t linflexd_uart_periph, linflexd_uart_ips_sizetype_enum size)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x003FU), ERR_PERIPH);
    } else
#endif
    {
        uint32_t reg;

        reg = LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph);
        reg &= ~(LINFLEXD_UART_LIN_STCTL_SIZE);
        reg |= ((uint32_t)size << 2U);
        LINFLEXD_UART_LIN_STCTL(linflexd_uart_periph) = reg;
    }
}

/*!
    \brief      return LINFlexD_UART flag (API_ID(0x0040U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  flag: linflexd_uart status flag
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_FLAG_NF: noise flag
      \arg        LINFLEXD_UART_FLAG_DTF_TFF: data transmission completed flag/ Tx FIFO full flag
      \arg        LINFLEXD_UART_FLAG_DRF_RFE: data reception completed flag / Rx FIFO empty flag
      \arg        LINFLEXD_UART_FLAG_TO: timeout flag
      \arg        LINFLEXD_UART_FLAG_RFNE: receive FIFO not empty flag
      \arg        LINFLEXD_UART_FLAG_WUF: wakeup flag
      \arg        LINFLEXD_UART_FLAG_RDI: receiver input state flag
      \arg        LINFLEXD_UART_FLAG_BOF: FIFO / buffer overrun flag
      \arg        LINFLEXD_UART_FLAG_FEF: frame error flag
      \arg        LINFLEXD_UART_FLAG_RMB: release message buffer flag
      \arg        LINFLEXD_UART_FLAG_PE0: parity error 0 flag
      \arg        LINFLEXD_UART_FLAG_PE1: parity error 1 flag
      \arg        LINFLEXD_UART_FLAG_PE2: parity error 2 flag
      \arg        LINFLEXD_UART_FLAG_PE3: parity error 3 flag
      \arg        LINFLEXD_UART_FLAG_OCF: output compare flag
      \arg        LINFLEXD_UART_FLAG_SZF: stuck at zero flag
    \param[out] none
    \retval     SET - UART status flag set, RESET - UART status flag reset
*/
FlagStatus linflexd_uart_flag_get(uint32_t linflexd_uart_periph, linflexd_uart_flag_enum flag)
{
    FlagStatus status = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0040U), ERR_PERIPH);
    } else
#endif
    {
        if(0U != (LINFLEXD_UART_REG_VAL(linflexd_uart_periph, flag) & BIT(LINFLEXD_UART_BIT_POS(flag)))) {
            status = SET;
        } else {
            status = RESET;
        }
    }
    return status;
}

/*!
    \brief      clear LINFlexD_UART interrupt flag (API_ID(0x0041U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  flag: linflexd_uart status flag
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_FLAG_NF: noise flag
      \arg        LINFLEXD_UART_FLAG_DTF_TFF: data transmission completed flag/ Tx FIFO full flag
      \arg        LINFLEXD_UART_FLAG_DRF_RFE: data reception completed flag / Rx FIFO empty flag
      \arg        LINFLEXD_UART_FLAG_TO: timeout flag
      \arg        LINFLEXD_UART_FLAG_RFNE: receive FIFO not empty flag
      \arg        LINFLEXD_UART_FLAG_WUF: wakeup flag
      \arg        LINFLEXD_UART_FLAG_RDI: receiver input state flag
      \arg        LINFLEXD_UART_FLAG_BOF: FIFO / buffer overrun flag
      \arg        LINFLEXD_UART_FLAG_FEF: frame error flag
      \arg        LINFLEXD_UART_FLAG_RMB: release message buffer flag
      \arg        LINFLEXD_UART_FLAG_PE0: parity error 0 flag
      \arg        LINFLEXD_UART_FLAG_PE1: parity error 1 flag
      \arg        LINFLEXD_UART_FLAG_PE2: parity error 2 flag
      \arg        LINFLEXD_UART_FLAG_PE3: parity error 3 flag
      \arg        LINFLEXD_UART_FLAG_OCF: output compare flag
      \arg        LINFLEXD_UART_FLAG_SZF: stuck at zero flag
    \param[out] none
    \retval     none
*/
void linflexd_uart_flag_clear(uint32_t linflexd_uart_periph, linflexd_uart_flag_enum flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0041U), ERR_PERIPH);
    } else
#endif
    {
        LINFLEXD_UART_UARTSR(linflexd_uart_periph) |= BIT(LINFLEXD_UART_BIT_POS(flag));
    }
}

/*!
    \brief      enable LINFlexD_UART interrupt (API_ID(0x0042U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  interrupt: linflexd_uart interrupt source
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_INT_DTF: data transmitted interrupt
      \arg        LINFLEXD_UART_INT_DRF: data reception complete interrupt
      \arg        LINFLEXD_UART_INT_TO: timeout interrupt
      \arg        LINFLEXD_UART_INT_WUF: wakeup interrupt
      \arg        LINFLEXD_UART_INT_BOF: buffer overrun interrupt
      \arg        LINFLEXD_UART_INT_FEF: frame error interrupt
      \arg        LINFLEXD_UART_INT_OCF: output compare interrupt
      \arg        LINFLEXD_UART_INT_SZF: stuck at zero interrupt
    \param[out] none
    \retval     none
*/
void linflexd_uart_interrupt_enable(uint32_t linflexd_uart_periph, linflexd_uart_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0042U), ERR_PERIPH);
    } else
#endif
    {
        LINFLEXD_UART_REG_VAL(linflexd_uart_periph, interrupt) |= BIT(LINFLEXD_UART_BIT_POS(interrupt));
    }
}

/*!
    \brief      disable LINFlexD_UART interrupt (API_ID(0x0043U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  interrupt: linflexd_uart interrupt source
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_INT_DTF: data transmitted interrupt
      \arg        LINFLEXD_UART_INT_DRF: data reception complete interrupt
      \arg        LINFLEXD_UART_INT_TO: timeout interrupt
      \arg        LINFLEXD_UART_INT_WUF: wakeup interrupt
      \arg        LINFLEXD_UART_INT_BOF: buffer overrun interrupt
      \arg        LINFLEXD_UART_INT_FEF: frame error interrupt
      \arg        LINFLEXD_UART_INT_OCF: output compare interrupt
      \arg        LINFLEXD_UART_INT_SZF: stuck at zero interrupt
    \param[out] none
    \retval     none
*/
void linflexd_uart_interrupt_disable(uint32_t linflexd_uart_periph, linflexd_uart_interrupt_enum interrupt)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0043U), ERR_PERIPH);
    } else
#endif
    {
        LINFLEXD_UART_REG_VAL(linflexd_uart_periph, interrupt) &= ~BIT(LINFLEXD_UART_BIT_POS(interrupt));
    }
}

/*!
    \brief      get LINFlexD_UART interrupt flag (API_ID(0x0044U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  int_flag: linflexd_uart interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_INT_FLAG_DTF: data transmission completed interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_DRF: data reception completed interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_TO: timeout interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_WU: wakeup interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_BOF: buffer overrun interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_FEF: framing error interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_OCF: output compare interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_SZF: stuck at zero interrupt and flag
    \param[out] none
    \retval     FlagStatus: SET or RESET
*/
FlagStatus linflexd_uart_interrupt_flag_get(uint32_t linflexd_uart_periph, linflexd_uart_interrupt_flag_enum int_flag)
{
    FlagStatus status = RESET;

#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0044U), ERR_PERIPH);
    } else
#endif
    {
        uint32_t intenable, flagstatus;
        /* get the interrupt enable bit status */
        intenable = (LINFLEXD_UART_REG_VAL(linflexd_uart_periph, int_flag) & BIT(LINFLEXD_UART_BIT_POS(int_flag)));
        /* get the corresponding flag bit status */
        flagstatus = (LINFLEXD_UART_REG_VAL2(linflexd_uart_periph, int_flag) & BIT(LINFLEXD_UART_BIT_POS2(int_flag)));

        if((0U != flagstatus) && (0U != intenable)) {
            status = SET;
        } else {
            status = RESET;
        }
    }
    return status;
}

/*!
    \brief      clear LINFlexD_UART interrupt flag (API_ID(0x0045U))
    \param[in]  linflexd_uart_periph: LINFLEXD_UARTx(x=0,1,...,11)
    \param[in]  int_flag: linflexd_uart interrupt flag
                only one parameter can be selected which is shown as below:
      \arg        LINFLEXD_UART_INT_FLAG_DTF: data transmission completed interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_DRF: data reception completed interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_TO: timeout interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_WUF: wakeup interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_BOF: buffer overrun interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_FEF: framing error interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_OCF: output compare interrupt and flag
      \arg        LINFLEXD_UART_INT_FLAG_SZF: stuck at zero interrupt and flag
    \param[out] none
    \retval     none
*/
void linflexd_uart_interrupt_flag_clear(uint32_t linflexd_uart_periph, linflexd_uart_interrupt_flag_enum int_flag)
{
#ifdef FW_DEBUG_ERR_REPORT
    if(NOT_LINFLEXD_UART_PERIPH(linflexd_uart_periph)) {
        fw_debug_report_err(LINFLEXD_UART_MODULE_ID, API_ID(0x0045U), ERR_PERIPH);
    } else
#endif
    {
       LINFLEXD_UART_UARTSR(linflexd_uart_periph) |= BIT(LINFLEXD_UART_BIT_POS2(int_flag));
    }
}
