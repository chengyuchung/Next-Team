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

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x000000800

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

;               /* reset Vector Mapped to at Address 0 */
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__IVT           DCD     0x5AA55AA5                        ; valid IVT header marker 
                DCD     0x00000001                        ; bit0 : M7_0 enable
                DCD     0                                 ; Reserved
                DCD     __Vectors                         ; M7_0 start address
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; lifecycle configure
                SPACE   0x3D8

__Vectors       DCD     __initial_sp                      ; Top of Stack
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
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

;/* reset Handler */
Reset_Handler   PROC
                EXPORT  Reset_Handler                     [WEAK]

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
;                /* Stores DTCM capacity values for SRAM initialization */
                 MOV     R3, R1
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
;                /* Stores ITCM capacity values for SRAM initialization */
                 MOV     R4, R1
;                /* Initialize the ITCM */
                 LDR     R0, =0x00000000
                 ADD     R1, R0, R1
                 MOV     R2, #0x0
ITCMSRAM_INIT    STRD    R2, R2, [ R0 ], #8
                 CMP     R0, R1
                 BNE     ITCMSRAM_INIT

;                /* get the SRAM + DTCM + ITCM size */
                 LDR     R0, =0x1FFFF7E0
                 LDR     R1, [R0]
                 LDR     R0, = 0xFFFF0000
                 AND     R1, R1, R0
                 LSR     R1, R1, #16
                 LSL     R1, R1, #10
;                /* Calculates the DTCM + ITCM byte size */
                 ADD     R3, R4
;                /* Calculates the SRAM byte size */
                 SUB     R1,R3
;                /* Initialize the SRAM */
                 LDR     R0, =0x24000000
                 ADD     R1, R0, R1
                 MOV     R2, #0x0
SRAM_INIT        STRD    R2, R2, [ R0 ], #8
                 CMP     R0, R1
                 BNE     SRAM_INIT

                 IMPORT  SystemInit
                 IMPORT  __main
                 LDR     R0, =SystemInit
                 BLX     R0
                 LDR     R0, =__main
                 BX      R0
                 ENDP

;/* dummy Exception Handlers */
NMI_Handler     PROC
                EXPORT  NMI_Handler                       [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                 [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                 [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                  [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler                [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                       [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                  [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler                    [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler                   [WEAK]
                B       .
                ENDP

Default_Handler PROC
;               /* external interrupts handler */
                EXPORT  WWDGT0_IRQHandler                   [WEAK]
                EXPORT  HVD_LVD_IRQHandler                  [WEAK]
                EXPORT  RTC_Alarm_IRQHandler                [WEAK]
                EXPORT  RTC_IRQHandler                      [WEAK]
                EXPORT  FMC_IRQHandler                      [WEAK]
                EXPORT  RCU_IRQHandler                      [WEAK]
                EXPORT  EXTI0_IRQHandler                    [WEAK]
                EXPORT  EXTI1_IRQHandler                    [WEAK]
                EXPORT  EXTI2_IRQHandler                    [WEAK]
                EXPORT  EXTI3_IRQHandler                    [WEAK]
                EXPORT  EXTI4_IRQHandler                    [WEAK]
                EXPORT  DMA0_Channel0_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel1_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel2_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel3_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel4_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel5_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel6_IRQHandler            [WEAK]
                EXPORT  ADC0_IRQHandler                     [WEAK]
                EXPORT  CAN0_Message_IRQHandler             [WEAK]
                EXPORT  CAN0_IRQHandler                     [WEAK]
                EXPORT  CPU_INT0_IRQHandler                 [WEAK]
                EXPORT  CPU_INT1_IRQHandler                 [WEAK]
                EXPORT  CPU_INT2_IRQHandler                 [WEAK]
                EXPORT  CPU_INT3_IRQHandler                 [WEAK]
                EXPORT  CAN0_WKUP_IRQHandler                [WEAK]
                EXPORT  TIMER0_BRK_UP_TRG_CMT_IRQHandler    [WEAK]
                EXPORT  TIMER2_IRQHandler                   [WEAK]
                EXPORT  TIMER1_IRQHandler                   [WEAK]
                EXPORT  TIMER19_BRK_UP_TRG_CMT_IRQHandler   [WEAK]
                EXPORT  JDC_IRQHandler                      [WEAK]
                EXPORT  I2C0_EV_IRQHandler                  [WEAK]
                EXPORT  I2C0_ER_IRQHandler                  [WEAK]
                EXPORT  I2C1_EV_IRQHandler                  [WEAK]
                EXPORT  I2C1_ER_IRQHandler                  [WEAK]
                EXPORT  SPI0_IRQHandler                     [WEAK]
                EXPORT  SPI1_IRQHandler                     [WEAK]
                EXPORT  USART0_IRQHandler                   [WEAK]
                EXPORT  USART1_IRQHandler                   [WEAK]
                EXPORT  USART2_IRQHandler                   [WEAK]
                EXPORT  EXTI10_15_IRQHandler                [WEAK]
                EXPORT  EXTI5_9_IRQHandler                  [WEAK]
                EXPORT  TAMPER_IRQHandler                   [WEAK]
                EXPORT  TIMER20_BRK_UP_TRG_CMT_IRQHandler   [WEAK]
                EXPORT  EXTI42_101_IRQHandler               [WEAK]
                EXPORT  TIMER7_BRK_UP_TRG_CMT_IRQHandler    [WEAK]
                EXPORT  PLL_LOL_DES_RESET_IRQHandler        [WEAK]
                EXPORT  DMAMUX_OVR_IRQHandler               [WEAK]
                EXPORT  FPU_WAB_IRQHandler                  [WEAK]
                EXPORT  CMP0_EXTI_IRQHandler                [WEAK]
                EXPORT  CMP1_EXTI_IRQHandler                [WEAK]
                EXPORT  FMU_INIT_IRQHandler                 [WEAK]
                EXPORT  ADC1_IRQHandler                     [WEAK]
                EXPORT  ADC2_IRQHandler                     [WEAK]
                EXPORT  DAC0_IRQHandler                     [WEAK]
                EXPORT  STCM_IRQHandler                     [WEAK]
                EXPORT  DMA1_Channel0_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler            [WEAK]
                EXPORT  WWDGT1_IRQHandler                   [WEAK]
                EXPORT  CAN1_WKUP_IRQHandler                [WEAK]
                EXPORT  CAN1_Message_IRQHandler             [WEAK]
                EXPORT  CAN1_IRQHandler                     [WEAK]
                EXPORT  CTI0_IRQHandler                     [WEAK]
                EXPORT  CTI1_IRQHandler                     [WEAK]
                EXPORT  CAN0_ECCERR_IRQHandler              [WEAK]
                EXPORT  CAN1_ECCERR_IRQHandler              [WEAK]
                EXPORT  CAN2_ECCERR_IRQHandler              [WEAK]
                EXPORT  MFCOM_IRQHandler                    [WEAK]
                EXPORT  CMP0_IRQHandler                     [WEAK]
                EXPORT  CMP1_IRQHandler                     [WEAK]
                EXPORT  SENT_IRQHandler                     [WEAK]
                EXPORT  HWSEM_IRQHandler                    [WEAK]
                EXPORT  CAN3_ECCERR_IRQHandler              [WEAK]
                EXPORT  CAN4_ECCERR_IRQHandler              [WEAK]
                EXPORT  DAC1_IRQHandler                     [WEAK]
                EXPORT  HSM_COM0_IRQHandler                 [WEAK]
                EXPORT  HSM_COM1_IRQHandler                 [WEAK]
                EXPORT  FMU_CAT_IRQHandler                  [WEAK]
                EXPORT  RCTL_IRQHandler                     [WEAK]
                EXPORT  IOC_IRQHandler                      [WEAK]
                EXPORT  SPI2_IRQHandler                     [WEAK]
                EXPORT  SPI3_IRQHandler                     [WEAK]
                EXPORT  SPI4_IRQHandler                     [WEAK]
                EXPORT  SPI5_IRQHandler                     [WEAK]
                EXPORT  SPI6_IRQHandler                     [WEAK]
                EXPORT  SPI7_IRQHandler                     [WEAK]
                EXPORT  QSPI_IRQHandler                     [WEAK]
                EXPORT  USART3_IRQHandler                   [WEAK]
                EXPORT  USART4_IRQHandler                   [WEAK]
                EXPORT  USART5_IRQHandler                   [WEAK]
                EXPORT  CAN2_WKUP_IRQHandler                [WEAK]
                EXPORT  CAN3_WKUP_IRQHandler                [WEAK]
                EXPORT  CAN4_WKUP_IRQHandler                [WEAK]
                EXPORT  CAN5_WKUP_IRQHandler                [WEAK]
                EXPORT  CAN6_WKUP_IRQHandler                [WEAK]
                EXPORT  CAN7_WKUP_IRQHandler                [WEAK]
                EXPORT  CAN2_Message_IRQHandler             [WEAK]
                EXPORT  CAN2_IRQHandler                     [WEAK]
                EXPORT  CAN3_Message_IRQHandler             [WEAK]
                EXPORT  CAN3_IRQHandler                     [WEAK]
                EXPORT  CAN4_Message_IRQHandler             [WEAK]
                EXPORT  CAN4_IRQHandler                     [WEAK]
                EXPORT  CAN5_Message_IRQHandler             [WEAK]
                EXPORT  CAN5_IRQHandler                     [WEAK]
                EXPORT  CAN6_Message_IRQHandler             [WEAK]
                EXPORT  CAN6_IRQHandler                     [WEAK]
                EXPORT  CAN7_Message_IRQHandler             [WEAK]
                EXPORT  CAN7_IRQHandler                     [WEAK]
                EXPORT  TIMER19_CC0_CC0N_IRQHandler         [WEAK]
                EXPORT  TIMER19_CC1_CC1N_IRQHandler         [WEAK]
                EXPORT  TIMER19_CC2_CC2N_IRQHandler         [WEAK]
                EXPORT  TIMER19_CC3_CC3N_IRQHandler         [WEAK]
                EXPORT  TIMER20_CC0_CC0N_IRQHandler         [WEAK]
                EXPORT  TIMER20_CC1_CC1N_IRQHandler         [WEAK]
                EXPORT  TIMER20_CC2_CC2N_IRQHandler         [WEAK]
                EXPORT  TIMER20_CC3_CC3N_IRQHandler         [WEAK]
                EXPORT  TIMER60_CC0_CC0N_IRQHandler         [WEAK]
                EXPORT  TIMER60_CC1_CC1N_IRQHandler         [WEAK]
                EXPORT  TIMER60_CC2_CC2N_IRQHandler         [WEAK]
                EXPORT  TIMER60_CC3_CC3N_IRQHandler         [WEAK]
                EXPORT  TIMER61_CC0_CC0N_IRQHandler         [WEAK]
                EXPORT  TIMER61_CC1_CC1N_IRQHandler         [WEAK]
                EXPORT  TIMER61_CC2_CC2N_IRQHandler         [WEAK]
                EXPORT  TIMER61_CC3_CC3N_IRQHandler         [WEAK]
                EXPORT  TIMER62_CC0_CC0N_IRQHandler         [WEAK]
                EXPORT  TIMER62_CC1_CC1N_IRQHandler         [WEAK]
                EXPORT  TIMER62_CC2_CC2N_IRQHandler         [WEAK]
                EXPORT  TIMER62_CC3_CC3N_IRQHandler         [WEAK]
                EXPORT  TIMER63_CC0_CC0N_IRQHandler         [WEAK]
                EXPORT  TIMER63_CC1_CC1N_IRQHandler         [WEAK]
                EXPORT  TIMER63_CC2_CC2N_IRQHandler         [WEAK]
                EXPORT  TIMER63_CC3_CC3N_IRQHandler         [WEAK]
                EXPORT  DMA0_Channel7_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel8_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel9_IRQHandler            [WEAK]
                EXPORT  DMA0_Channel10_IRQHandler           [WEAK]
                EXPORT  DMA0_Channel11_IRQHandler           [WEAK]
                EXPORT  DMA0_Channel12_IRQHandler           [WEAK]
                EXPORT  DMA0_Channel13_IRQHandler           [WEAK]
                EXPORT  DMA0_Channel14_IRQHandler           [WEAK]
                EXPORT  DMA0_Channel15_IRQHandler           [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel8_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel9_IRQHandler            [WEAK]
                EXPORT  DMA1_Channel10_IRQHandler           [WEAK]
                EXPORT  DMA1_Channel11_IRQHandler           [WEAK]
                EXPORT  DMA1_Channel12_IRQHandler           [WEAK]
                EXPORT  DMA1_Channel13_IRQHandler           [WEAK]
                EXPORT  DMA1_Channel14_IRQHandler           [WEAK]
                EXPORT  DMA1_Channel15_IRQHandler           [WEAK]
                EXPORT  MCMUA_RX_IRQHandler                 [WEAK]
                EXPORT  MCMUA_TX_IRQHandler                 [WEAK]
                EXPORT  MCMUA_NORMAL_IRQHandler             [WEAK]
                EXPORT  MCMUB_RX_IRQHandler                 [WEAK]
                EXPORT  MCMUB_TX_IRQHandler                 [WEAK]
                EXPORT  MCMUB_NORMAL_IRQHandler             [WEAK]
                EXPORT  LIN0_IRQHandler                     [WEAK]
                EXPORT  LIN1_IRQHandler                     [WEAK]
                EXPORT  LIN2_IRQHandler                     [WEAK]
                EXPORT  LIN3_IRQHandler                     [WEAK]
                EXPORT  LIN4_IRQHandler                     [WEAK]
                EXPORT  LIN5_IRQHandler                     [WEAK]
                EXPORT  LIN6_IRQHandler                     [WEAK]
                EXPORT  LIN7_IRQHandler                     [WEAK]
                EXPORT  LIN8_IRQHandler                     [WEAK]
                EXPORT  LIN9_IRQHandler                     [WEAK]
                EXPORT  LIN10_IRQHandler                    [WEAK]
                EXPORT  LIN11_IRQHandler                    [WEAK]
                EXPORT  TIMER0_CC0_CC0N_IRQHandler          [WEAK]
                EXPORT  TIMER0_CC1_CC1N_IRQHandler          [WEAK]
                EXPORT  TIMER0_CC2_CC2N_IRQHandler          [WEAK]
                EXPORT  TIMER0_CC3_CC3N_IRQHandler          [WEAK]
                EXPORT  TIMER7_CC0_CC0N_IRQHandler          [WEAK]
                EXPORT  TIMER7_CC1_CC1N_IRQHandler          [WEAK]
                EXPORT  TIMER7_CC2_CC2N_IRQHandler          [WEAK]
                EXPORT  TIMER7_CC3_CC3N_IRQHandler          [WEAK]
                EXPORT  TIMER1_CC0_IRQHandler               [WEAK]
                EXPORT  TIMER1_CC1_IRQHandler               [WEAK]
                EXPORT  TIMER1_CC2_IRQHandler               [WEAK]
                EXPORT  TIMER1_CC3_IRQHandler               [WEAK]
                EXPORT  TIMER2_CC0_IRQHandler               [WEAK]
                EXPORT  TIMER2_CC1_IRQHandler               [WEAK]
                EXPORT  TIMER2_CC2_IRQHandler               [WEAK]
                EXPORT  TIMER2_CC3_IRQHandler               [WEAK]
                EXPORT  FWDGT_IRQHandler                    [WEAK]
                EXPORT  ETH_IRQHandler                      [WEAK]
                EXPORT  ETH_WKUP_IRQHandler                 [WEAK]
                EXPORT  ETH_TX_IRQHandler                   [WEAK]
                EXPORT  ETH_RX_IRQHandler                   [WEAK]
                EXPORT  ETH_SAFETY_IRQHandler               [WEAK]
                EXPORT  RCU_CK_FAIL_IRQHandler              [WEAK]
                EXPORT  CAN5_ECCERR_IRQHandler              [WEAK]
                EXPORT  TIMER60_BRK_UP_TRG_CMT_IRQHandler   [WEAK]
                EXPORT  TIMER61_BRK_UP_TRG_CMT_IRQHandler   [WEAK]
                EXPORT  TIMER62_BRK_UP_TRG_CMT_IRQHandler   [WEAK]
                EXPORT  TIMER63_BRK_UP_TRG_CMT_IRQHandler   [WEAK]
                EXPORT  TIMER5_CH0_UP_IRQHandler            [WEAK]
                EXPORT  TIMER5_CH1_UP_IRQHandler            [WEAK]
                EXPORT  TIMER5_CH2_UP_IRQHandler            [WEAK]
                EXPORT  TIMER5_CH3_UP_IRQHandler            [WEAK]
                EXPORT  TIMER6_CH0_UP_IRQHandler            [WEAK]
                EXPORT  TIMER6_CH1_UP_IRQHandler            [WEAK]
                EXPORT  TIMER6_CH2_UP_IRQHandler            [WEAK]
                EXPORT  TIMER6_CH3_UP_IRQHandler            [WEAK]
                EXPORT  CAN6_ECCERR_IRQHandler              [WEAK]
                EXPORT  CAN7_ECCERR_IRQHandler              [WEAK]

;/* external interrupts handler */
WWDGT0_IRQHandler
HVD_LVD_IRQHandler
RTC_Alarm_IRQHandler
RTC_IRQHandler
FMC_IRQHandler
RCU_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA0_Channel0_IRQHandler
DMA0_Channel1_IRQHandler
DMA0_Channel2_IRQHandler
DMA0_Channel3_IRQHandler
DMA0_Channel4_IRQHandler
DMA0_Channel5_IRQHandler
DMA0_Channel6_IRQHandler
ADC0_IRQHandler
CAN0_Message_IRQHandler
CAN0_IRQHandler
CPU_INT0_IRQHandler
CPU_INT1_IRQHandler
CPU_INT2_IRQHandler
CPU_INT3_IRQHandler
CAN0_WKUP_IRQHandler
TIMER0_BRK_UP_TRG_CMT_IRQHandler
TIMER2_IRQHandler
TIMER1_IRQHandler
TIMER19_BRK_UP_TRG_CMT_IRQHandler
JDC_IRQHandler
I2C0_EV_IRQHandler
I2C0_ER_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
EXTI10_15_IRQHandler
EXTI5_9_IRQHandler
TAMPER_IRQHandler
TIMER20_BRK_UP_TRG_CMT_IRQHandler 
EXTI42_101_IRQHandler
TIMER7_BRK_UP_TRG_CMT_IRQHandler
PLL_LOL_DES_RESET_IRQHandler
DMAMUX_OVR_IRQHandler
FPU_WAB_IRQHandler
CMP0_EXTI_IRQHandler
CMP1_EXTI_IRQHandler
FMU_INIT_IRQHandler
ADC1_IRQHandler
ADC2_IRQHandler
DAC0_IRQHandler
STCM_IRQHandler
DMA1_Channel0_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
WWDGT1_IRQHandler
CAN1_WKUP_IRQHandler
CAN1_Message_IRQHandler
CAN1_IRQHandler
CTI0_IRQHandler
CTI1_IRQHandler
CAN0_ECCERR_IRQHandler
CAN1_ECCERR_IRQHandler
CAN2_ECCERR_IRQHandler
MFCOM_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
SENT_IRQHandler
HWSEM_IRQHandler
CAN3_ECCERR_IRQHandler
CAN4_ECCERR_IRQHandler
DAC1_IRQHandler
HSM_COM0_IRQHandler
HSM_COM1_IRQHandler
FMU_CAT_IRQHandler
RCTL_IRQHandler
IOC_IRQHandler
SPI2_IRQHandler
SPI3_IRQHandler
SPI4_IRQHandler
SPI5_IRQHandler
SPI6_IRQHandler
SPI7_IRQHandler
QSPI_IRQHandler
USART3_IRQHandler
USART4_IRQHandler
USART5_IRQHandler
CAN2_WKUP_IRQHandler
CAN3_WKUP_IRQHandler
CAN4_WKUP_IRQHandler
CAN5_WKUP_IRQHandler
CAN6_WKUP_IRQHandler
CAN7_WKUP_IRQHandler
CAN2_Message_IRQHandler
CAN2_IRQHandler
CAN3_Message_IRQHandler
CAN3_IRQHandler
CAN4_Message_IRQHandler
CAN4_IRQHandler
CAN5_Message_IRQHandler
CAN5_IRQHandler
CAN6_Message_IRQHandler
CAN6_IRQHandler
CAN7_Message_IRQHandler
CAN7_IRQHandler
TIMER19_CC0_CC0N_IRQHandler
TIMER19_CC1_CC1N_IRQHandler
TIMER19_CC2_CC2N_IRQHandler
TIMER19_CC3_CC3N_IRQHandler
TIMER20_CC0_CC0N_IRQHandler
TIMER20_CC1_CC1N_IRQHandler
TIMER20_CC2_CC2N_IRQHandler
TIMER20_CC3_CC3N_IRQHandler
TIMER60_CC0_CC0N_IRQHandler
TIMER60_CC1_CC1N_IRQHandler
TIMER60_CC2_CC2N_IRQHandler
TIMER60_CC3_CC3N_IRQHandler
TIMER61_CC0_CC0N_IRQHandler
TIMER61_CC1_CC1N_IRQHandler
TIMER61_CC2_CC2N_IRQHandler
TIMER61_CC3_CC3N_IRQHandler
TIMER62_CC0_CC0N_IRQHandler
TIMER62_CC1_CC1N_IRQHandler
TIMER62_CC2_CC2N_IRQHandler
TIMER62_CC3_CC3N_IRQHandler
TIMER63_CC0_CC0N_IRQHandler
TIMER63_CC1_CC1N_IRQHandler
TIMER63_CC2_CC2N_IRQHandler
TIMER63_CC3_CC3N_IRQHandler
DMA0_Channel7_IRQHandler
DMA0_Channel8_IRQHandler
DMA0_Channel9_IRQHandler
DMA0_Channel10_IRQHandler
DMA0_Channel11_IRQHandler
DMA0_Channel12_IRQHandler
DMA0_Channel13_IRQHandler
DMA0_Channel14_IRQHandler
DMA0_Channel15_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
DMA1_Channel8_IRQHandler
DMA1_Channel9_IRQHandler
DMA1_Channel10_IRQHandler
DMA1_Channel11_IRQHandler
DMA1_Channel12_IRQHandler
DMA1_Channel13_IRQHandler
DMA1_Channel14_IRQHandler
DMA1_Channel15_IRQHandler
MCMUA_RX_IRQHandler
MCMUA_TX_IRQHandler
MCMUA_NORMAL_IRQHandler
MCMUB_RX_IRQHandler
MCMUB_TX_IRQHandler
MCMUB_NORMAL_IRQHandler
LIN0_IRQHandler
LIN1_IRQHandler
LIN2_IRQHandler
LIN3_IRQHandler
LIN4_IRQHandler
LIN5_IRQHandler
LIN6_IRQHandler
LIN7_IRQHandler
LIN8_IRQHandler
LIN9_IRQHandler
LIN10_IRQHandler
LIN11_IRQHandler
TIMER0_CC0_CC0N_IRQHandler
TIMER0_CC1_CC1N_IRQHandler
TIMER0_CC2_CC2N_IRQHandler
TIMER0_CC3_CC3N_IRQHandler
TIMER7_CC0_CC0N_IRQHandler
TIMER7_CC1_CC1N_IRQHandler
TIMER7_CC2_CC2N_IRQHandler
TIMER7_CC3_CC3N_IRQHandler
TIMER1_CC0_IRQHandler
TIMER1_CC1_IRQHandler
TIMER1_CC2_IRQHandler
TIMER1_CC3_IRQHandler
TIMER2_CC0_IRQHandler
TIMER2_CC1_IRQHandler
TIMER2_CC2_IRQHandler
TIMER2_CC3_IRQHandler
FWDGT_IRQHandler
ETH_IRQHandler
ETH_WKUP_IRQHandler
ETH_TX_IRQHandler
ETH_RX_IRQHandler
ETH_SAFETY_IRQHandler
RCU_CK_FAIL_IRQHandler
CAN5_ECCERR_IRQHandler
TIMER60_BRK_UP_TRG_CMT_IRQHandler
TIMER61_BRK_UP_TRG_CMT_IRQHandler
TIMER62_BRK_UP_TRG_CMT_IRQHandler
TIMER63_BRK_UP_TRG_CMT_IRQHandler
TIMER5_CH0_UP_IRQHandler
TIMER5_CH1_UP_IRQHandler
TIMER5_CH2_UP_IRQHandler
TIMER5_CH3_UP_IRQHandler
TIMER6_CH0_UP_IRQHandler
TIMER6_CH1_UP_IRQHandler
TIMER6_CH2_UP_IRQHandler
TIMER6_CH3_UP_IRQHandler
CAN6_ECCERR_IRQHandler
CAN7_ECCERR_IRQHandler
                B       .
                ENDP

                ALIGN

; user Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF

                END
