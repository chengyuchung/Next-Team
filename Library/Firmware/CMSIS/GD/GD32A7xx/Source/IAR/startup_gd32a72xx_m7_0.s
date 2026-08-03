;/*!
;    \file    startup_gd32a7xx.s
;    \brief   start up file
;
;    \version 2025-08-06, V0.1.0, firmware for GD32A7xx
;*/
;
;/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
; * Copyright (c) 2025, GigaDevice Semiconductor Inc.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__IVT   DCD     0x5AA55AA5                       ; valid IVT header marker
        DCD     0x00000003                       ; bit0 : M7_0 enable; bit1 : M7_1 enable
        DCD     0                                ; Reserved
        DCD     __vector_table                   ; M7_0 start address
        DCD     0                                ; Reserved
        DCD     0x08200000                       ; M7_1 start address
        DCD     0                                ; Reserved
        DCD     0                                ; Reserved
        DCD     0                                ; Reserved
        DCD     0                                ; lifecycle configure
        DS8     0x3D8                            ; Allocates space

__vector_table
        DCD     sfe(CSTACK)                       ; Top of Stack
        DCD     Reset_Handler                     ; Reset Handler
        DCD     NMI_Handler                       ; NMI Handler
        DCD     HardFault_Handler                 ; Hard Fault Handler
        DCD     MemManage_Handler                 ; MPU Fault Handler
        DCD     BusFault_Handler                  ; Bus Fault Handler
        DCD     UsageFault_Handler                ; Usage Fault Handler
        DCD     0                                 ; Reserved
        DCD     0                                 ; Reserved
        DCD     0                                 ; Reserved
        DCD     0                                 ; Reserved
        DCD     SVC_Handler                       ; SVCall Handler
        DCD     DebugMon_Handler                  ; Debug Monitor Handler
        DCD     0                                 ; Reserved
        DCD     PendSV_Handler                    ; PendSV Handler
        DCD     SysTick_Handler                   ; SysTick Handler

;               /* external interrupts handler */
        DCD     WWDGT0_IRQHandler                 ; 16:Window Watchdog 0 interrupt
        DCD     HVD_LVD_IRQHandler                ; 17:LVD/HVD through EXTI Line detect interrupt
        DCD     RTC_Alarm_IRQHandler              ; 18:RTC Alarm interrupt through EXTI Line interrupt
        DCD     RTC_IRQHandler                    ; 19:RTC global interrupt
        DCD     FMC_IRQHandler                    ; 20:FMC global interrupt
        DCD     RCU_IRQHandler                    ; 21:RCU clock ready interrupt
        DCD     EXTI0_IRQHandler                  ; 22:EXTI Line 0 interrupt
        DCD     EXTI1_IRQHandler                  ; 23:EXTI Line 1 interrupt
        DCD     EXTI2_IRQHandler                  ; 24:EXTI Line 2 interrupt
        DCD     EXTI3_IRQHandler                  ; 25:EXTI Line 3 interrupt
        DCD     EXTI4_IRQHandler                  ; 26:EXTI Line 4 interrupt
        DCD     DMA0_Channel0_IRQHandler          ; 27:DMA0 Channel0 global interrupt
        DCD     DMA0_Channel1_IRQHandler          ; 28:DMA0 Channel1 global interrupt
        DCD     DMA0_Channel2_IRQHandler          ; 29:DMA0 Channel2 global interrupt
        DCD     DMA0_Channel3_IRQHandler          ; 30:DMA0 Channel3 global interrupt
        DCD     DMA0_Channel4_IRQHandler          ; 31:DMA0 Channel4 global interrupt
        DCD     DMA0_Channel5_IRQHandler          ; 32:DMA0 Channel5 global interrupt
        DCD     DMA0_Channel6_IRQHandler          ; 33:DMA0 Channel6 global interrupt
        DCD     ADC0_IRQHandler                   ; 34:ADC0 interrupt
        DCD     CAN0_Message_IRQHandler           ; 35:CAN0 interrupt for message buffer
        DCD     CAN0_IRQHandler                   ; 36:CAN0 interrupt
        DCD     CPU_INT0_IRQHandler               ; 37:Interrupt0 between CM7_0 and CM7_1
        DCD     CPU_INT1_IRQHandler               ; 38:Interrupt1 between CM7_0 and CM7_1
        DCD     CPU_INT2_IRQHandler               ; 39:Interrupt2 between CM7_0 and CM7_1
        DCD     CPU_INT3_IRQHandler               ; 40:Interrupt3 between CM7_0 and CM7_1
        DCD     CAN0_WKUP_IRQHandler              ; 41:CAN0 wakeup through EXTI Line detection interrupt
        DCD     TIMER0_BRK_UP_TRG_CMT_IRQHandler  ; 42:TIMER0 Break Update Trigger and Commutation
        DCD     TIMER2_IRQHandler                 ; 43:TIMER2 update, trigger and commutation, dec interrupt
        DCD     TIMER1_IRQHandler                 ; 44:TIMER1 update, trigger and commutation, dec interrupt
        DCD     TIMER19_BRK_UP_TRG_CMT_IRQHandler ; 45:TIMER19 Break Update Trigger and Commutation
        DCD     JDC_IRQHandler                    ; 46:JDC interrupt to host
        DCD     I2C0_EV_IRQHandler                ; 47:I2C0 Event interrupt
        DCD     I2C0_ER_IRQHandler                ; 48:I2C0 Error interrupt
        DCD     I2C1_EV_IRQHandler                ; 49:I2C1 Event interrupt
        DCD     I2C1_ER_IRQHandler                ; 50:I2C1 Error interrupt
        DCD     SPI0_IRQHandler                   ; 51:SPI0 global interrupt
        DCD     SPI1_IRQHandler                   ; 52:SPI1 global interrupt
        DCD     USART0_IRQHandler                 ; 53:USART0 interrupt
        DCD     USART1_IRQHandler                 ; 54:USART1 interrupt
        DCD     USART2_IRQHandler                 ; 55:USART2 interrupt
        DCD     EXTI10_15_IRQHandler              ; 56:EXTI Line10-15 interrupt
        DCD     EXTI5_9_IRQHandler                ; 57:EXTI Line5-9 interrupt
        DCD     TAMPER_IRQHandler                 ; 58:BKP Tamper interrupt
        DCD     TIMER20_BRK_UP_TRG_CMT_IRQHandler ; 59:TIMER20 Break, update, trigger and commutation, dec interrupt
        DCD     EXTI42_101_IRQHandler             ; 60:EXTI Line42-101 interrupts
        DCD     TIMER7_BRK_UP_TRG_CMT_IRQHandler  ; 61:TIMER7 Break, update, trigger and commutation, dec interrupt
        DCD     PLL_LOL_DES_RESET_IRQHandler      ; 62:PLL LOL system reset interrupt
        DCD     DMAMUX_OVR_IRQHandler             ; 63:DMAMUX overrun interrupt
        DCD     FPU_WAB_IRQHandler                ; 64:CPU FPU interrupt or Write abort interrupt
        DCD     CMP0_EXTI_IRQHandler              ; 65:CMP0 through EXTI Line detection interrupt
        DCD     CMP1_EXTI_IRQHandler              ; 66:CMP1 through EXTI Line detection interrupt
        DCD     FMU_INIT_IRQHandler               ; 67:FMU initializing timeout interrupt
        DCD     ADC1_IRQHandler                   ; 68:ADC1 interrupt
        DCD     ADC2_IRQHandler                   ; 69:ADC2 interrupt
        DCD     DAC0_IRQHandler                   ; 70:DAC0 global interrupt
        DCD     STCM_IRQHandler                   ; 71:TCM illegal triggered during running state
        DCD     DMA1_Channel0_IRQHandler          ; 72:DMA1 Channel0 global interrupt
        DCD     DMA1_Channel1_IRQHandler          ; 73:DMA1 Channel1 global interrupt
        DCD     DMA1_Channel2_IRQHandler          ; 74:DMA1 Channel2 global interrupt
        DCD     DMA1_Channel3_IRQHandler          ; 75:DMA1 Channel3 global interrupt
        DCD     DMA1_Channel4_IRQHandler          ; 76:DMA1 Channel4 global interruptDMA1 Channel4
        DCD     WWDGT1_IRQHandler                 ; 77:Window Watchdog 1 Timer1
        DCD     CAN1_WKUP_IRQHandler              ; 78:CAN1 wakeup through EXTI Line detection interrupt
        DCD     CAN1_Message_IRQHandler           ; 79:CAN1 interrupt for message buffer
        DCD     CAN1_IRQHandler                   ; 80:CAN1 interrupt
        DCD     CTI0_IRQHandler                   ; 81:CTI interrupt 0
        DCD     CTI1_IRQHandler                   ; 82:CTI interrupt 1
        DCD     CAN0_ECCERR_IRQHandler            ; 83:CAN0 ECC error interrupt
        DCD     CAN1_ECCERR_IRQHandler            ; 84:CAN1 ECC error interrupt
        DCD     CAN2_ECCERR_IRQHandler            ; 85:CAN2 ECC error interrupt
        DCD     MFCOM_IRQHandler                  ; 86:MFCOM interrupt
        DCD     CMP0_IRQHandler                   ; 87:CMP0 global interrupt
        DCD     CMP1_IRQHandler                   ; 88:CMP1 global interrupt
        DCD     0                                 ; 89:Reserved
        DCD     SENT_IRQHandler                   ; 90:SENT interrupt
        DCD     HWSEM_IRQHandler                  ; 91:HWSEM global interrupt
        DCD     CAN3_ECCERR_IRQHandler            ; 92:CAN3 ECC error interrupt
        DCD     CAN4_ECCERR_IRQHandler            ; 93:CAN4 ECC error interrupt
        DCD     DAC1_IRQHandler                   ; 94:DAC1 global interrupt
        DCD     HSM_COM0_IRQHandler               ; 95:HSM communication interrupt 0
        DCD     HSM_COM1_IRQHandler               ; 96:HSM communication interrupt 1
        DCD     FMU_CAT_IRQHandler                ; 97:FMU cation state interrupt
        DCD     RCTL_IRQHandler                   ; 98:RCTL interrupt
        DCD     IOC_IRQHandler                    ; 99:IOC interrupt
        DCD     SPI2_IRQHandler                   ; 100:SPI2 global interrupt
        DCD     SPI3_IRQHandler                   ; 101:SPI3 global interrupt
        DCD     SPI4_IRQHandler                   ; 102:SPI4 global interrupt
        DCD     SPI5_IRQHandler                   ; 103:SPI5 global interrupt
        DCD     SPI6_IRQHandler                   ; 104:SPI6 global interrupt
        DCD     SPI7_IRQHandler                   ; 105:SPI7 global interrupt
        DCD     QSPI_IRQHandler                   ; 106:QSPI global interrupt
        DCD     USART3_IRQHandler                 ; 107:USART3 interrupt
        DCD     USART4_IRQHandler                 ; 108:USART4 interrupt
        DCD     USART5_IRQHandler                 ; 109:USART5 interrupt
        DCD     CAN2_WKUP_IRQHandler              ; 110:CAN2 wakeup through EXTI Line detection interrupt
        DCD     CAN3_WKUP_IRQHandler              ; 111:CAN3 wakeup through EXTI Line detection interrupt
        DCD     CAN4_WKUP_IRQHandler              ; 112:CAN4 wakeup through EXTI Line detection interrupt
        DCD     CAN5_WKUP_IRQHandler              ; 113:CAN5 wakeup through EXTI Line detection interrupt
        DCD     CAN6_WKUP_IRQHandler              ; 114:CAN6 wakeup through EXTI Line detection interrupt
        DCD     CAN7_WKUP_IRQHandler              ; 115:CAN7 wakeup through EXTI Line detection interrupt
        DCD     CAN2_Message_IRQHandler           ; 116:CAN2 interrupt for message buffer
        DCD     CAN2_IRQHandler                   ; 117:CAN2 interrupt
        DCD     CAN3_Message_IRQHandler           ; 118:CAN3 interrupt for message buffer
        DCD     CAN3_IRQHandler                   ; 119:CAN3 interrupt
        DCD     CAN4_Message_IRQHandler           ; 120:CAN4 interrupt for message buffer
        DCD     CAN4_IRQHandler                   ; 121:CAN4 interrupt
        DCD     CAN5_Message_IRQHandler           ; 122:CAN5 interrupt for message buffer
        DCD     CAN5_IRQHandler                   ; 123:CAN5 interrupt
        DCD     CAN6_Message_IRQHandler           ; 124:CAN6 interrupt for message buffer
        DCD     CAN6_IRQHandler                   ; 125:CAN6 interrupt
        DCD     CAN7_Message_IRQHandler           ; 126:CAN7 interrupt for message buffer
        DCD     CAN7_IRQHandler                   ; 127:CAN7 interrupt
        DCD     TIMER19_CC0_CC0N_IRQHandler       ; 128:TIMER19 capture compare CH0 and MCH0 interrupt
        DCD     TIMER19_CC1_CC1N_IRQHandler       ; 129:TIMER19 capture compare CH1 and MCH1 interrupt
        DCD     TIMER19_CC2_CC2N_IRQHandler       ; 130:TIMER19 capture compare CH2 and MCH2 interrupt
        DCD     TIMER19_CC3_CC3N_IRQHandler       ; 131:TIMER19 capture compare CH3 and MCH3 interrupt
        DCD     TIMER20_CC0_CC0N_IRQHandler       ; 132:TIMER20 capture compare CH0 and MCH0 interrupt
        DCD     TIMER20_CC1_CC1N_IRQHandler       ; 133:TIMER20 capture compare CH1 and MCH1 interrupt
        DCD     TIMER20_CC2_CC2N_IRQHandler       ; 134:TIMER20 capture compare CH2 and MCH2 interrupt
        DCD     TIMER20_CC3_CC3N_IRQHandler       ; 135:TIMER20 capture compare CH3 and MCH3 interrupt
        DCD     TIMER60_CC0_CC0N_IRQHandler       ; 136:TIMER60 capture compare CH0 and MCH0 interrupt
        DCD     TIMER60_CC1_CC1N_IRQHandler       ; 137:TIMER60 capture compare CH1 and MCH1 interrupt
        DCD     TIMER60_CC2_CC2N_IRQHandler       ; 138:TIMER60 capture compare CH2 and MCH2 interrupt
        DCD     TIMER60_CC3_CC3N_IRQHandler       ; 139:TIMER60 capture compare CH3 and MCH3 interrupt
        DCD     TIMER61_CC0_CC0N_IRQHandler       ; 140:TIMER61 capture compare CH0 and MCH0 interrupt
        DCD     TIMER61_CC1_CC1N_IRQHandler       ; 141:TIMER61 capture compare CH1 and MCH1 interrupt
        DCD     TIMER61_CC2_CC2N_IRQHandler       ; 142:TIMER61 capture compare CH2 and MCH2 interrupt
        DCD     TIMER61_CC3_CC3N_IRQHandler       ; 143:TIMER61 capture compare CH3 and MCH3 interrupt
        DCD     TIMER62_CC0_CC0N_IRQHandler       ; 144:TIMER62 capture compare CH0 and MCH0 interrupt
        DCD     TIMER62_CC1_CC1N_IRQHandler       ; 145:TIMER62 capture compare CH1 and MCH1 interrupt
        DCD     TIMER62_CC2_CC2N_IRQHandler       ; 146:TIMER62 capture compare CH2 and MCH2 interrupt
        DCD     TIMER62_CC3_CC3N_IRQHandler       ; 147:TIMER62 capture compare CH3 and MCH3 interrupt
        DCD     TIMER63_CC0_CC0N_IRQHandler       ; 148:TIMER63 capture compare CH0 and MCH0 interrupt
        DCD     TIMER63_CC1_CC1N_IRQHandler       ; 149:TIMER63 capture compare CH1 and MCH1 interrupt
        DCD     TIMER63_CC2_CC2N_IRQHandler       ; 150:TIMER63 capture compare CH2 and MCH2 interrupt
        DCD     TIMER63_CC3_CC3N_IRQHandler       ; 151:TIMER63 capture compare CH3 and MCH3 interrupt
        DCD     DMA0_Channel7_IRQHandler          ; 152:DMA0_Channel 7 interrupt
        DCD     DMA0_Channel8_IRQHandler          ; 153:DMA0_Channel 8 interrupt
        DCD     DMA0_Channel9_IRQHandler          ; 154:DMA0_Channel 9 interrupt
        DCD     DMA0_Channel10_IRQHandler         ; 155:DMA0_Channel 10 interrupt
        DCD     DMA0_Channel11_IRQHandler         ; 156:DMA0_Channel 11 interrupt
        DCD     DMA0_Channel12_IRQHandler         ; 157:DMA0_Channel 12 interrupt
        DCD     DMA0_Channel13_IRQHandler         ; 158:DMA0_Channel 13 interrupt
        DCD     DMA0_Channel14_IRQHandler         ; 159:DMA0_Channel 14 interrupt
        DCD     DMA0_Channel15_IRQHandler         ; 160:DMA0_Channel 15 interrupt
        DCD     DMA1_Channel5_IRQHandler          ; 161:DMA1_Channel 5 interrupt
        DCD     DMA1_Channel6_IRQHandler          ; 162:DMA1_Channel 6 interrupt
        DCD     DMA1_Channel7_IRQHandler          ; 163:DMA1_Channel 7 interrupt
        DCD     DMA1_Channel8_IRQHandler          ; 164:DMA1_Channel 8 interrupt
        DCD     DMA1_Channel9_IRQHandler          ; 165:DMA1_Channel 9 interrupt
        DCD     DMA1_Channel10_IRQHandler         ; 166:DMA1_Channel 10 interrupt
        DCD     DMA1_Channel11_IRQHandler         ; 167:DMA1_Channel 11 interrupt
        DCD     DMA1_Channel12_IRQHandler         ; 168:DMA1_Channel 12 interrupt
        DCD     DMA1_Channel13_IRQHandler         ; 169:DMA1_Channel 13 interrupt
        DCD     DMA1_Channel14_IRQHandler         ; 170:DMA1_Channel 14 interrupt
        DCD     DMA1_Channel15_IRQHandler         ; 171:DMA1_Channel 15 interrupt
        DCD     MCMUA_RX_IRQHandler               ; 172:MCMUA Receive full interrupt
        DCD     MCMUA_TX_IRQHandler               ; 173:MCMUA Transmit empty interrupt
        DCD     MCMUA_NORMAL_IRQHandler           ; 174:MCMUA General purpose interrupt
        DCD     MCMUB_RX_IRQHandler               ; 175:MCMUB Receive full interrupt
        DCD     MCMUB_TX_IRQHandler               ; 176:MCMUB Transmit empty interrupt
        DCD     MCMUB_NORMAL_IRQHandler           ; 177:MCMUB General purpose interrupt
        DCD     LIN0_IRQHandler                   ; 178:LIN0 interrupt
        DCD     LIN1_IRQHandler                   ; 179:LIN1 interrupt
        DCD     LIN2_IRQHandler                   ; 180:LIN2 interrupt
        DCD     LIN3_IRQHandler                   ; 181:LIN3 interrupt
        DCD     LIN4_IRQHandler                   ; 182:LIN4 interrupt
        DCD     LIN5_IRQHandler                   ; 183:LIN5 interrupt
        DCD     LIN6_IRQHandler                   ; 184:LIN6 interrupt
        DCD     LIN7_IRQHandler                   ; 185:LIN7 interrupt
        DCD     LIN8_IRQHandler                   ; 186:LIN8 interrupt
        DCD     LIN9_IRQHandler                   ; 187:LIN9 interrupt
        DCD     LIN10_IRQHandler                  ; 188:LIN10 interrupt
        DCD     LIN11_IRQHandler                  ; 189:LIN11 interrupt
        DCD     TIMER0_CC0_CC0N_IRQHandler        ; 190:TIMER0 capture compare CH0 and MCH0 interrupt
        DCD     TIMER0_CC1_CC1N_IRQHandler        ; 191:TIMER0 capture compare CH1 and MCH1 interrupt
        DCD     TIMER0_CC2_CC2N_IRQHandler        ; 192:TIMER0 capture compare CH2 and MCH2 interrupt
        DCD     TIMER0_CC3_CC3N_IRQHandler        ; 193:TIMER0 capture compare CH3 and MCH3 interrupt
        DCD     TIMER7_CC0_CC0N_IRQHandler        ; 194:TIMER7 capture compare CH0 and MCH0 interrupt
        DCD     TIMER7_CC1_CC1N_IRQHandler        ; 195:TIMER7 capture compare CH1 and MCH1 interrupt
        DCD     TIMER7_CC2_CC2N_IRQHandler        ; 196:TIMER7 capture compare CH2 and MCH2 interrupt
        DCD     TIMER7_CC3_CC3N_IRQHandler        ; 197:TIMER7 capture compare CH3 and MCH3 interrupt
        DCD     TIMER1_CC0_IRQHandler             ; 198:TIMER1 capture compare CH0 interrupt
        DCD     TIMER1_CC1_IRQHandler             ; 199:TIMER1 capture compare CH1 interrupt
        DCD     TIMER1_CC2_IRQHandler             ; 200:TIMER1 capture compare CH2 interrupt
        DCD     TIMER1_CC3_IRQHandler             ; 201:TIMER1 capture compare CH3 interrupt
        DCD     TIMER2_CC0_IRQHandler             ; 202:TIMER2 capture compare CH0 interrupt
        DCD     TIMER2_CC1_IRQHandler             ; 203:TIMER2 capture compare CH1 interrupt
        DCD     TIMER2_CC2_IRQHandler             ; 204:TIMER2 capture compare CH2 interrupt
        DCD     TIMER2_CC3_IRQHandler             ; 205:TIMER2 capture compare CH3 interrupt
        DCD     FWDGT_IRQHandler                  ; 206:FWDGT reset interrupt through EXTI Line detection interrupt
        DCD     ETH_IRQHandler                    ; 207:Ethernet global interrupt
        DCD     ETH_WKUP_IRQHandler               ; 208:Ethernet wakeup or LPI interrupt
        DCD     ETH_TX_IRQHandler                 ; 209:Ethernet Tx0/1 interrupt
        DCD     ETH_RX_IRQHandler                 ; 210:Ethernet Rx0/1 interrupt
        DCD     ETH_SAFETY_IRQHandler             ; 211:Ethernet0 safety correctable/uncorrectable interrupt
        DCD     RCU_CK_FAIL_IRQHandler            ; 212:RCU clock fail interrupt
        DCD     CAN5_ECCERR_IRQHandler            ; 213:CAN5 ECC error interrupt
        DCD     0                                 ; 214:Reserved
        DCD     0                                 ; 215:Reserved
        DCD     0                                 ; 216:Reserved
        DCD     0                                 ; 217:Reserved
        DCD     0                                 ; 218:Reserved
        DCD     0                                 ; 219:Reserved
        DCD     0                                 ; 220:Reserved
        DCD     0                                 ; 221:Reserved
        DCD     0                                 ; 222:Reserved
        DCD     0                                 ; 223:Reserved
        DCD     0                                 ; 224:Reserved
        DCD     0                                 ; 225:Reserved
        DCD     TIMER60_BRK_UP_TRG_CMT_IRQHandler ; 226:TIMER60 Break, update, trigger and commutation, dec interrupt
        DCD     TIMER61_BRK_UP_TRG_CMT_IRQHandler ; 227:TIMER61 Break, update, trigger and commutation, dec interrupt
        DCD     TIMER62_BRK_UP_TRG_CMT_IRQHandler ; 228:TIMER62 Break, update, trigger and commutation, dec interrupt
        DCD     TIMER63_BRK_UP_TRG_CMT_IRQHandler ; 229:TIMER63 Break, update, trigger and commutation, dec interrupt
        DCD     TIMER5_CH0_UP_IRQHandler          ; 230:TIMER5 channel 0 upate interrupt
        DCD     TIMER5_CH1_UP_IRQHandler          ; 231:TIMER5 channel 1 upate interrupt
        DCD     TIMER5_CH2_UP_IRQHandler          ; 232:TIMER5 channel 2 upate interrupt
        DCD     TIMER5_CH3_UP_IRQHandler          ; 233:TIMER5 channel 3 upate interrupt
        DCD     TIMER6_CH0_UP_IRQHandler          ; 234:TIMER6 channel 0 upate interrupt
        DCD     TIMER6_CH1_UP_IRQHandler          ; 235:TIMER6 channel 1 upate interrupt
        DCD     TIMER6_CH2_UP_IRQHandler          ; 236:TIMER6 channel 2 upate interrupt
        DCD     TIMER6_CH3_UP_IRQHandler          ; 237:TIMER6 channel 3 upate interrupt
        DCD     0                                 ; 238:Reserved
        DCD     0                                 ; 239:Reserved
        DCD     0                                 ; 240:Reserved
        DCD     0                                 ; 241:Reserved
        DCD     0                                 ; 242:Reserved
        DCD     0                                 ; 243:Reserved
        DCD     0                                 ; 244:Reserved
        DCD     0                                 ; 245:Reserved
        DCD     0                                 ; 246:Reserved
        DCD     0                                 ; 247:Reserved
        DCD     0                                 ; 248:Reserved
        DCD     0                                 ; 249:Reserved
        DCD     0                                 ; 250:Reserved
        DCD     0                                 ; 251:Reserved
        DCD     0                                 ; 252:Reserved
        DCD     0                                 ; 253:Reserved
        DCD     CAN6_ECCERR_IRQHandler            ; 254:CAN6 ECC error interrupt
        DCD     CAN7_ECCERR_IRQHandler            ; 255:CAN7 ECC error interrupt
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
;                /* Enable SYSCFG clock to get DTCM and ITCM information */
                 LDR     R0, =0x49001018
                 LDR     R2, [R0]
                 ORR     R2, #0x01
                 STR     R2, [R0]

;                /* get the DTCM size */
                 LDR     R0, =0x40010254
                 LDR     R2, [R0]
                 LDR     R0, = 0xFF000000
                 AND     R2, R2, R0
                 LSR     R2, R2, #24
                 ADD     R2, #8
                 MOV     R1, #1
;                /* Calculates the DTCM byte size */
                 LSL     R1, R1, R2
;                /* Initialize the DTCM */
                 LDR     R0, =0x20000000
                 ADD     R1, R0, R1
                 MOV     R2, #0x0
DTCMSRAM_INIT    STRD    R2, R2, [ R0 ], #8
                 CMP     R0, R1
                 BNE     DTCMSRAM_INIT

;                /* get the ITCM size */
                 LDR     R0, =0x40010254
                 LDR     R2, [R0]
                 LDR     R0, = 0x00FF0000
                 AND     R2, R2, R0
                 LSR     R2, R2, #16
                 ADD     R2, #8
                 MOV     R1, #1
;                /* Calculates the ITCM byte size */
                 LSL     R1, R1, R2
;                /* Initialize the ITCM */
                 LDR     R0, =0x00000000
                 ADD     R1, R0, R1
                 MOV     R2, #0x0
ITCMSRAM_INIT    STRD    R2, R2, [ R0 ], #8
                 CMP     R0, R1
                 BNE     ITCMSRAM_INIT

;If the actual size of SRAM used exceeds 32K, users need to modify the size to be greater than or equal to the actual size in use.
                 LDR     R0, = 0x24000000    ;SRAM base address  for M7_0
                 ADD     R1, R0, #0x8000     ;Default SRAM size 32K
                 LDR     R2, =0x0
SRAM_INIT        STRD    R2, R2, [ R0 ] , #8
                 CMP     R0, R1
                 BNE     SRAM_INIT

                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__iar_program_start
                 BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDGT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDGT0_IRQHandler
        B WWDGT0_IRQHandler

        PUBWEAK HVD_LVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HVD_LVD_IRQHandler
        B HVD_LVD_IRQHandler

        PUBWEAK RTC_Alarm_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Alarm_IRQHandler
        B RTC_Alarm_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK FMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_IRQHandler
        B FMC_IRQHandler

        PUBWEAK RCU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_IRQHandler
        B RCU_IRQHandler

        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler

        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler

        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler

        PUBWEAK DMA0_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel0_IRQHandler
        B DMA0_Channel0_IRQHandler

        PUBWEAK DMA0_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel1_IRQHandler
        B DMA0_Channel1_IRQHandler

        PUBWEAK DMA0_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel2_IRQHandler
        B DMA0_Channel2_IRQHandler

        PUBWEAK DMA0_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel3_IRQHandler
        B DMA0_Channel3_IRQHandler

        PUBWEAK DMA0_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel4_IRQHandler
        B DMA0_Channel4_IRQHandler

        PUBWEAK DMA0_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel5_IRQHandler
        B DMA0_Channel5_IRQHandler

        PUBWEAK DMA0_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel6_IRQHandler
        B DMA0_Channel6_IRQHandler

        PUBWEAK ADC0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC0_IRQHandler
        B ADC0_IRQHandler

        PUBWEAK CAN0_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_Message_IRQHandler
        B CAN0_Message_IRQHandler

        PUBWEAK CAN0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_IRQHandler
        B CAN0_IRQHandler

        PUBWEAK CPU_INT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPU_INT0_IRQHandler
        B CPU_INT0_IRQHandler

        PUBWEAK CPU_INT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPU_INT1_IRQHandler
        B CPU_INT1_IRQHandler

        PUBWEAK CPU_INT2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPU_INT2_IRQHandler
        B CPU_INT2_IRQHandler

        PUBWEAK CPU_INT3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CPU_INT3_IRQHandler
        B CPU_INT3_IRQHandler

        PUBWEAK CAN0_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_WKUP_IRQHandler
        B CAN0_WKUP_IRQHandler

        PUBWEAK TIMER0_BRK_UP_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_BRK_UP_TRG_CMT_IRQHandler
        B TIMER0_BRK_UP_TRG_CMT_IRQHandler

        PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler

        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler

        PUBWEAK TIMER19_BRK_UP_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_BRK_UP_TRG_CMT_IRQHandler
        B TIMER19_BRK_UP_TRG_CMT_IRQHandler

        PUBWEAK JDC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
JDC_IRQHandler
        B JDC_IRQHandler

        PUBWEAK I2C0_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_EV_IRQHandler
        B I2C0_EV_IRQHandler

        PUBWEAK I2C0_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_ER_IRQHandler
        B I2C0_ER_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler

        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK USART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART0_IRQHandler
        B USART0_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK EXTI10_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI10_15_IRQHandler
        B EXTI10_15_IRQHandler

        PUBWEAK EXTI5_9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI5_9_IRQHandler
        B EXTI5_9_IRQHandler

        PUBWEAK TAMPER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMPER_IRQHandler
        B TAMPER_IRQHandler

        PUBWEAK TIMER20_BRK_UP_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER20_BRK_UP_TRG_CMT_IRQHandler
        B TIMER20_BRK_UP_TRG_CMT_IRQHandler

        PUBWEAK EXTI42_101_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI42_101_IRQHandler
        B EXTI42_101_IRQHandler

        PUBWEAK TIMER7_BRK_UP_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_BRK_UP_TRG_CMT_IRQHandler
        B TIMER7_BRK_UP_TRG_CMT_IRQHandler

        PUBWEAK PLL_LOL_DES_RESET_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PLL_LOL_DES_RESET_IRQHandler
        B PLL_LOL_DES_RESET_IRQHandler

        PUBWEAK DMAMUX_OVR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMAMUX_OVR_IRQHandler
        B DMAMUX_OVR_IRQHandler

        PUBWEAK FPU_WAB_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_WAB_IRQHandler
        B FPU_WAB_IRQHandler

        PUBWEAK CMP0_EXTI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP0_EXTI_IRQHandler
        B CMP0_EXTI_IRQHandler

        PUBWEAK CMP1_EXTI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP1_EXTI_IRQHandler
        B CMP1_EXTI_IRQHandler

        PUBWEAK FMU_INIT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMU_INIT_IRQHandler
        B FMU_INIT_IRQHandler

        PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC1_IRQHandler
        B ADC1_IRQHandler

        PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC2_IRQHandler
        B ADC2_IRQHandler

        PUBWEAK DAC0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC0_IRQHandler
        B DAC0_IRQHandler

        PUBWEAK STCM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
STCM_IRQHandler
        B STCM_IRQHandler

        PUBWEAK DMA1_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel0_IRQHandler
        B DMA1_Channel0_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler

        PUBWEAK DMA1_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel2_IRQHandler
        B DMA1_Channel2_IRQHandler

        PUBWEAK DMA1_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel3_IRQHandler
        B DMA1_Channel3_IRQHandler

        PUBWEAK DMA1_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel4_IRQHandler
        B DMA1_Channel4_IRQHandler

        PUBWEAK WWDGT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDGT1_IRQHandler
        B WWDGT1_IRQHandler

        PUBWEAK CAN1_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_WKUP_IRQHandler
        B CAN1_WKUP_IRQHandler

        PUBWEAK CAN1_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Message_IRQHandler
        B CAN1_Message_IRQHandler

        PUBWEAK CAN1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_IRQHandler
        B CAN1_IRQHandler

        PUBWEAK CTI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CTI0_IRQHandler
        B CTI0_IRQHandler

        PUBWEAK CTI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CTI1_IRQHandler
        B CTI1_IRQHandler

        PUBWEAK CAN0_ECCERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_ECCERR_IRQHandler
        B CAN0_ECCERR_IRQHandler

        PUBWEAK CAN1_ECCERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_ECCERR_IRQHandler
        B CAN1_ECCERR_IRQHandler

        PUBWEAK CAN2_ECCERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_ECCERR_IRQHandler
        B CAN2_ECCERR_IRQHandler

        PUBWEAK MFCOM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MFCOM_IRQHandler
        B MFCOM_IRQHandler

        PUBWEAK CMP0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP0_IRQHandler
        B CMP0_IRQHandler

        PUBWEAK CMP1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP1_IRQHandler
        B CMP1_IRQHandler

        PUBWEAK BUS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
BUS_IRQHandler
        B BUS_IRQHandler

        PUBWEAK SENT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SENT_IRQHandler
        B SENT_IRQHandler

        PUBWEAK HWSEM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HWSEM_IRQHandler
        B HWSEM_IRQHandler

        PUBWEAK CAN3_ECCERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN3_ECCERR_IRQHandler
        B CAN3_ECCERR_IRQHandler

        PUBWEAK CAN4_ECCERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN4_ECCERR_IRQHandler
        B CAN4_ECCERR_IRQHandler

        PUBWEAK DAC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DAC1_IRQHandler
        B DAC1_IRQHandler

        PUBWEAK HSM_COM0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HSM_COM0_IRQHandler
        B HSM_COM0_IRQHandler

        PUBWEAK HSM_COM1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HSM_COM1_IRQHandler
        B HSM_COM1_IRQHandler

        PUBWEAK FMU_CAT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMU_CAT_IRQHandler
        B FMU_CAT_IRQHandler

        PUBWEAK RCTL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCTL_IRQHandler
        B RCTL_IRQHandler

        PUBWEAK IOC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IOC_IRQHandler
        B IOC_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI3_IRQHandler
        B SPI3_IRQHandler

        PUBWEAK SPI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI4_IRQHandler
        B SPI4_IRQHandler

        PUBWEAK SPI5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI5_IRQHandler
        B SPI5_IRQHandler

        PUBWEAK SPI6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI6_IRQHandler
        B SPI6_IRQHandler

        PUBWEAK SPI7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI7_IRQHandler
        B SPI7_IRQHandler

        PUBWEAK QSPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
QSPI_IRQHandler
        B QSPI_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_IRQHandler
        B USART3_IRQHandler

        PUBWEAK USART4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART4_IRQHandler
        B USART4_IRQHandler

        PUBWEAK USART5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART5_IRQHandler
        B USART5_IRQHandler

        PUBWEAK CAN2_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_WKUP_IRQHandler
        B CAN2_WKUP_IRQHandler

        PUBWEAK CAN3_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN3_WKUP_IRQHandler
        B CAN3_WKUP_IRQHandler

        PUBWEAK CAN4_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN4_WKUP_IRQHandler
        B CAN4_WKUP_IRQHandler

        PUBWEAK CAN5_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN5_WKUP_IRQHandler
        B CAN5_WKUP_IRQHandler

        PUBWEAK CAN6_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN6_WKUP_IRQHandler
        B CAN6_WKUP_IRQHandler

        PUBWEAK CAN7_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN7_WKUP_IRQHandler
        B CAN7_WKUP_IRQHandler

        PUBWEAK CAN2_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Message_IRQHandler
        B CAN2_Message_IRQHandler

        PUBWEAK CAN2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_IRQHandler
        B CAN2_IRQHandler

        PUBWEAK CAN3_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN3_Message_IRQHandler
        B CAN3_Message_IRQHandler

        PUBWEAK CAN3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN3_IRQHandler
        B CAN3_IRQHandler

        PUBWEAK CAN4_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN4_Message_IRQHandler
        B CAN4_Message_IRQHandler

        PUBWEAK CAN4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN4_IRQHandler
        B CAN4_IRQHandler

        PUBWEAK CAN5_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN5_Message_IRQHandler
        B CAN5_Message_IRQHandler

        PUBWEAK CAN5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN5_IRQHandler
        B CAN5_IRQHandler

        PUBWEAK CAN6_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN6_Message_IRQHandler
        B CAN6_Message_IRQHandler

        PUBWEAK CAN6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN6_IRQHandler
        B CAN6_IRQHandler

        PUBWEAK CAN7_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN7_Message_IRQHandler
        B CAN7_Message_IRQHandler

        PUBWEAK CAN7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN7_IRQHandler
        B CAN7_IRQHandler

        PUBWEAK TIMER19_CC0_CC0N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_CC0_CC0N_IRQHandler
        B TIMER19_CC0_CC0N_IRQHandler

        PUBWEAK TIMER19_CC1_CC1N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_CC1_CC1N_IRQHandler
        B TIMER19_CC1_CC1N_IRQHandler

        PUBWEAK TIMER19_CC2_CC2N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_CC2_CC2N_IRQHandler
        B TIMER19_CC2_CC2N_IRQHandler

        PUBWEAK TIMER19_CC3_CC3N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER19_CC3_CC3N_IRQHandler
        B TIMER19_CC3_CC3N_IRQHandler

        PUBWEAK TIMER20_CC0_CC0N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER20_CC0_CC0N_IRQHandler
        B TIMER20_CC0_CC0N_IRQHandler

        PUBWEAK TIMER20_CC1_CC1N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER20_CC1_CC1N_IRQHandler
        B TIMER20_CC1_CC1N_IRQHandler

        PUBWEAK TIMER20_CC2_CC2N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER20_CC2_CC2N_IRQHandler
        B TIMER20_CC2_CC2N_IRQHandler

        PUBWEAK TIMER20_CC3_CC3N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER20_CC3_CC3N_IRQHandler
        B TIMER20_CC3_CC3N_IRQHandler

        PUBWEAK TIMER60_CC0_CC0N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER60_CC0_CC0N_IRQHandler
        B TIMER60_CC0_CC0N_IRQHandler

        PUBWEAK TIMER60_CC1_CC1N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER60_CC1_CC1N_IRQHandler
        B TIMER60_CC1_CC1N_IRQHandler

        PUBWEAK TIMER60_CC2_CC2N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER60_CC2_CC2N_IRQHandler
        B TIMER60_CC2_CC2N_IRQHandler

        PUBWEAK TIMER60_CC3_CC3N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER60_CC3_CC3N_IRQHandler
        B TIMER60_CC3_CC3N_IRQHandler

        PUBWEAK TIMER61_CC0_CC0N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER61_CC0_CC0N_IRQHandler
        B TIMER61_CC0_CC0N_IRQHandler

        PUBWEAK TIMER61_CC1_CC1N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER61_CC1_CC1N_IRQHandler
        B TIMER61_CC1_CC1N_IRQHandler

        PUBWEAK TIMER61_CC2_CC2N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER61_CC2_CC2N_IRQHandler
        B TIMER61_CC2_CC2N_IRQHandler

        PUBWEAK TIMER61_CC3_CC3N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER61_CC3_CC3N_IRQHandler
        B TIMER61_CC3_CC3N_IRQHandler

        PUBWEAK TIMER62_CC0_CC0N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER62_CC0_CC0N_IRQHandler
        B TIMER62_CC0_CC0N_IRQHandler

        PUBWEAK TIMER62_CC1_CC1N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER62_CC1_CC1N_IRQHandler
        B TIMER62_CC1_CC1N_IRQHandler

        PUBWEAK TIMER62_CC2_CC2N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER62_CC2_CC2N_IRQHandler
        B TIMER62_CC2_CC2N_IRQHandler

        PUBWEAK TIMER62_CC3_CC3N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER62_CC3_CC3N_IRQHandler
        B TIMER62_CC3_CC3N_IRQHandler

        PUBWEAK TIMER63_CC0_CC0N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER63_CC0_CC0N_IRQHandler
        B TIMER63_CC0_CC0N_IRQHandler

        PUBWEAK TIMER63_CC1_CC1N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER63_CC1_CC1N_IRQHandler
        B TIMER63_CC1_CC1N_IRQHandler

        PUBWEAK TIMER63_CC2_CC2N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER63_CC2_CC2N_IRQHandler
        B TIMER63_CC2_CC2N_IRQHandler

        PUBWEAK TIMER63_CC3_CC3N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER63_CC3_CC3N_IRQHandler
        B TIMER63_CC3_CC3N_IRQHandler

        PUBWEAK DMA0_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel7_IRQHandler
        B DMA0_Channel7_IRQHandler

        PUBWEAK DMA0_Channel8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel8_IRQHandler
        B DMA0_Channel8_IRQHandler

        PUBWEAK DMA0_Channel9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel9_IRQHandler
        B DMA0_Channel9_IRQHandler

        PUBWEAK DMA0_Channel10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel10_IRQHandler
        B DMA0_Channel10_IRQHandler

        PUBWEAK DMA0_Channel11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel11_IRQHandler
        B DMA0_Channel11_IRQHandler

        PUBWEAK DMA0_Channel12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel12_IRQHandler
        B DMA0_Channel12_IRQHandler

        PUBWEAK DMA0_Channel13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel13_IRQHandler
        B DMA0_Channel13_IRQHandler

        PUBWEAK DMA0_Channel14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel14_IRQHandler
        B DMA0_Channel14_IRQHandler

        PUBWEAK DMA0_Channel15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel15_IRQHandler
        B DMA0_Channel15_IRQHandler

        PUBWEAK DMA1_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel5_IRQHandler
        B DMA1_Channel5_IRQHandler

        PUBWEAK DMA1_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel6_IRQHandler
        B DMA1_Channel6_IRQHandler

        PUBWEAK DMA1_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel7_IRQHandler
        B DMA1_Channel7_IRQHandler

        PUBWEAK DMA1_Channel8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel8_IRQHandler
        B DMA1_Channel8_IRQHandler

        PUBWEAK DMA1_Channel9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel9_IRQHandler
        B DMA1_Channel9_IRQHandler

        PUBWEAK DMA1_Channel10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel10_IRQHandler
        B DMA1_Channel10_IRQHandler

        PUBWEAK DMA1_Channel11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel11_IRQHandler
        B DMA1_Channel11_IRQHandler

        PUBWEAK DMA1_Channel12_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel12_IRQHandler
        B DMA1_Channel12_IRQHandler

        PUBWEAK DMA1_Channel13_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel13_IRQHandler
        B DMA1_Channel13_IRQHandler

        PUBWEAK DMA1_Channel14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel14_IRQHandler
        B DMA1_Channel14_IRQHandler

        PUBWEAK DMA1_Channel15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel15_IRQHandler
        B DMA1_Channel15_IRQHandler

        PUBWEAK MCMUA_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MCMUA_RX_IRQHandler
        B MCMUA_RX_IRQHandler

        PUBWEAK MCMUA_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MCMUA_TX_IRQHandler
        B MCMUA_TX_IRQHandler

        PUBWEAK MCMUA_NORMAL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MCMUA_NORMAL_IRQHandler
        B MCMUA_NORMAL_IRQHandler

        PUBWEAK MCMUB_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MCMUB_RX_IRQHandler
        B MCMUB_RX_IRQHandler

        PUBWEAK MCMUB_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MCMUB_TX_IRQHandler
        B MCMUB_TX_IRQHandler

        PUBWEAK MCMUB_NORMAL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MCMUB_NORMAL_IRQHandler
        B MCMUB_NORMAL_IRQHandler

        PUBWEAK LIN0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN0_IRQHandler
        B LIN0_IRQHandler

        PUBWEAK LIN1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN1_IRQHandler
        B LIN1_IRQHandler

        PUBWEAK LIN2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN2_IRQHandler
        B LIN2_IRQHandler

        PUBWEAK LIN3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN3_IRQHandler
        B LIN3_IRQHandler

        PUBWEAK LIN4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN4_IRQHandler
        B LIN4_IRQHandler

        PUBWEAK LIN5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN5_IRQHandler
        B LIN5_IRQHandler

        PUBWEAK LIN6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN6_IRQHandler
        B LIN6_IRQHandler

        PUBWEAK LIN7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN7_IRQHandler
        B LIN7_IRQHandler

        PUBWEAK LIN8_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN8_IRQHandler
        B LIN8_IRQHandler

        PUBWEAK LIN9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN9_IRQHandler
        B LIN9_IRQHandler

        PUBWEAK LIN10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN10_IRQHandler
        B LIN10_IRQHandler

        PUBWEAK LIN11_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LIN11_IRQHandler
        B LIN11_IRQHandler

        PUBWEAK TIMER0_CC0_CC0N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_CC0_CC0N_IRQHandler
        B TIMER0_CC0_CC0N_IRQHandler

        PUBWEAK TIMER0_CC1_CC1N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_CC1_CC1N_IRQHandler
        B TIMER0_CC1_CC1N_IRQHandler

        PUBWEAK TIMER0_CC2_CC2N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_CC2_CC2N_IRQHandler
        B TIMER0_CC2_CC2N_IRQHandler

        PUBWEAK TIMER0_CC3_CC3N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_CC3_CC3N_IRQHandler
        B TIMER0_CC3_CC3N_IRQHandler

        PUBWEAK TIMER7_CC0_CC0N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_CC0_CC0N_IRQHandler
        B TIMER7_CC0_CC0N_IRQHandler

        PUBWEAK TIMER7_CC1_CC1N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_CC1_CC1N_IRQHandler
        B TIMER7_CC1_CC1N_IRQHandler

        PUBWEAK TIMER7_CC2_CC2N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_CC2_CC2N_IRQHandler
        B TIMER7_CC2_CC2N_IRQHandler

        PUBWEAK TIMER7_CC3_CC3N_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_CC3_CC3N_IRQHandler
        B TIMER7_CC3_CC3N_IRQHandler

        PUBWEAK TIMER1_CC0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_CC0_IRQHandler
        B TIMER1_CC0_IRQHandler

        PUBWEAK TIMER1_CC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_CC1_IRQHandler
        B TIMER1_CC1_IRQHandler

        PUBWEAK TIMER1_CC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_CC2_IRQHandler
        B TIMER1_CC2_IRQHandler

        PUBWEAK TIMER1_CC3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_CC3_IRQHandler
        B TIMER1_CC3_IRQHandler

        PUBWEAK TIMER2_CC0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_CC0_IRQHandler
        B TIMER2_CC0_IRQHandler

        PUBWEAK TIMER2_CC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_CC1_IRQHandler
        B TIMER2_CC1_IRQHandler

        PUBWEAK TIMER2_CC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_CC2_IRQHandler
        B TIMER2_CC2_IRQHandler

        PUBWEAK TIMER2_CC3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_CC3_IRQHandler
        B TIMER2_CC3_IRQHandler

        PUBWEAK FWDGT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FWDGT_IRQHandler
        B FWDGT_IRQHandler

        PUBWEAK ETH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_IRQHandler
        B ETH_IRQHandler

        PUBWEAK ETH_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_WKUP_IRQHandler
        B ETH_WKUP_IRQHandler

        PUBWEAK ETH_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_TX_IRQHandler
        B ETH_TX_IRQHandler

        PUBWEAK ETH_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_RX_IRQHandler
        B ETH_RX_IRQHandler

        PUBWEAK ETH_SAFETY_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_SAFETY_IRQHandler
        B ETH_SAFETY_IRQHandler

        PUBWEAK RCU_CK_FAIL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_CK_FAIL_IRQHandler
        B RCU_CK_FAIL_IRQHandler

        PUBWEAK CAN5_ECCERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN5_ECCERR_IRQHandler
        B CAN5_ECCERR_IRQHandler

        PUBWEAK TIMER60_BRK_UP_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER60_BRK_UP_TRG_CMT_IRQHandler
        B TIMER60_BRK_UP_TRG_CMT_IRQHandler

        PUBWEAK TIMER61_BRK_UP_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER61_BRK_UP_TRG_CMT_IRQHandler
        B TIMER61_BRK_UP_TRG_CMT_IRQHandler

        PUBWEAK TIMER62_BRK_UP_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER62_BRK_UP_TRG_CMT_IRQHandler
        B TIMER62_BRK_UP_TRG_CMT_IRQHandler

        PUBWEAK TIMER63_BRK_UP_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER63_BRK_UP_TRG_CMT_IRQHandler
        B TIMER63_BRK_UP_TRG_CMT_IRQHandler

        PUBWEAK TIMER5_CH0_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_CH0_UP_IRQHandler
        B TIMER5_CH0_UP_IRQHandler

        PUBWEAK TIMER5_CH1_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_CH1_UP_IRQHandler
        B TIMER5_CH1_UP_IRQHandler

        PUBWEAK TIMER5_CH2_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_CH2_UP_IRQHandler
        B TIMER5_CH2_UP_IRQHandler

        PUBWEAK TIMER5_CH3_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_CH3_UP_IRQHandler
        B TIMER5_CH3_UP_IRQHandler

        PUBWEAK TIMER6_CH0_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER6_CH0_UP_IRQHandler
        B TIMER6_CH0_UP_IRQHandler

        PUBWEAK TIMER6_CH1_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER6_CH1_UP_IRQHandler
        B TIMER6_CH1_UP_IRQHandler

        PUBWEAK TIMER6_CH2_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER6_CH2_UP_IRQHandler
        B TIMER6_CH2_UP_IRQHandler

        PUBWEAK TIMER6_CH3_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER6_CH3_UP_IRQHandler
        B TIMER6_CH3_UP_IRQHandler

        PUBWEAK CAN6_ECCERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN6_ECCERR_IRQHandler
        B CAN6_ECCERR_IRQHandler

        PUBWEAK CAN7_ECCERR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN7_ECCERR_IRQHandler
        B CAN7_ECCERR_IRQHandler

        END
