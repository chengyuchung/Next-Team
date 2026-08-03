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
                DCD     DTM_CAN0_INT0_IRQHandler          ; 35:DTM_CAN0 Interrupt 0
                DCD     DTM_CAN0_INT1_IRQHandler          ; 36:DTM_CAN0 Interrupt 1
                DCD     0                                 ; 37:Reserved
                DCD     0                                 ; 38:Reserved
                DCD     0                                 ; 39:Reserved
                DCD     0                                 ; 40:Reserved
                DCD     DTM_CAN0_DMU_IRQHandler           ; 41:DTM_CAN0 DMU interrupt
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
                DCD     0                                 ; 53:Reserved
                DCD     0                                 ; 54:Reserved
                DCD     0                                 ; 55:Reserved
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
                DCD     0                                 ; 69:Reserved
                DCD     DAC0_IRQHandler                   ; 70:DAC0 global interrupt
                DCD     STCM_IRQHandler                   ; 71:STCM illegal triggered during running state
                DCD     DMA1_Channel0_IRQHandler          ; 72:DMA1 Channel0 global interrupt
                DCD     DMA1_Channel1_IRQHandler          ; 73:DMA1 Channel1 global interrupt
                DCD     DMA1_Channel2_IRQHandler          ; 74:DMA1 Channel2 global interrupt
                DCD     DMA1_Channel3_IRQHandler          ; 75:DMA1 Channel3 global interrupt
                DCD     DMA1_Channel4_IRQHandler          ; 76:DMA1 Channel4 global interrupt
                DCD     0                                 ; 77:Reserved
                DCD     DTM_CAN1_INT0_IRQHandler          ; 78:DTM_CAN1 Interrupt0
                DCD     DTM_CAN1_INT1_IRQHandler          ; 79:DTM_CAN1 Interrupt1
                DCD     DTM_CAN1_DMU_IRQHandler           ; 80:DTM_CAN1 DMU interrupt
                DCD     CTI0_IRQHandler                   ; 81:CTI interrupt 0
                DCD     CTI1_IRQHandler                   ; 81:CTI interrupt 1
                DCD     CAN0_ECCERR_IRQHandler            ; 83:CAN0 ECC error interrupt
                DCD     CAN1_ECCERR_IRQHandler            ; 84:CAN1 ECC error interrupt
                DCD     CAN2_ECCERR_IRQHandler            ; 85:CAN2 ECC error interrupt
                DCD     0                                 ; 86:Reserved
                DCD     CMP0_IRQHandler                   ; 87:CMP0 global interrupt
                DCD     CMP1_IRQHandler                   ; 88:CMP1 global interrupt
                DCD     0                                 ; 89:Reserved
                DCD     0                                 ; 90:Reserved
                DCD     0                                 ; 91:Reserved
                DCD     0                                 ; 92:Reserved
                DCD     0                                 ; 93:Reserved
                DCD     DAC1_IRQHandler                   ; 94:DAC1 global interrupt
                DCD     HSM_COM0_IRQHandler               ; 95:HSM communication interrupt 0
                DCD     HSM_COM1_IRQHandler               ; 96:HSM communication interrupt 1
                DCD     FMU_CAT_IRQHandler                ; 97:FMU cation state interrupt
                DCD     RCTL_IRQHandler                   ; 98:RCTL interrupt
                DCD     0                                 ; 99:Reserved
                DCD     SPI2_IRQHandler                   ; 100:SPI2 global interrupt
                DCD     SPI3_IRQHandler                   ; 101:SPI3 global interrupt
                DCD     SPI4_IRQHandler                   ; 102:SPI4 global interrupt
                DCD     SPI5_IRQHandler                   ; 103:SPI5 global interrupt
                DCD     0                                 ; 104:Reserved
                DCD     0                                 ; 105:Reserved
                DCD     QSPI_IRQHandler                   ; 106:QSPI global interrupt
                DCD     0                                 ; 107:Reserved
                DCD     0                                 ; 108:Reserved
                DCD     0                                 ; 109:Reserved
                DCD     DTM_CAN2_DMU_IRQHandler           ; 110:DTM_CAN2_DMU interrupt
                DCD     DTM_CAN3_DMU_IRQHandler           ; 111:DTM_CAN3_DMU interrupt
                DCD     DTM_CAN4_DMU_IRQHandler           ; 112:DTM_CAN4_DMU interrupt
                DCD     DTM_CAN5_DMU_IRQHandler           ; 113:DTM_CAN5_DMU interrupt
                DCD     DTM_CAN6_DMU_IRQHandler           ; 112:DTM_CAN6_DMU interrupt
                DCD     DTM_CAN7_DMU_IRQHandler           ; 113:DTM_CAN7_DMU interrupt
                DCD     DTM_CAN2_INT0_IRQHandler          ; 116:DTM_CAN2 interrupt 0
                DCD     DTM_CAN2_INT1_IRQHandler          ; 117:DTM_CAN2 interrupt 1
                DCD     DTM_CAN3_INT0_IRQHandler          ; 118:DTM_CAN3 interrupt 0
                DCD     DTM_CAN3_INT1_IRQHandler          ; 119:DTM_CAN3 interrupt 1
                DCD     DTM_CAN4_INT0_IRQHandler          ; 120:DTM_CAN4 interrupt 0
                DCD     DTM_CAN4_INT1_IRQHandler          ; 121:DTM_CAN4 interrupt 1
                DCD     DTM_CAN5_INT0_IRQHandler          ; 122:DTM_CAN5 interrupt 0
                DCD     DTM_CAN5_INT1_IRQHandler          ; 123:DTM_CAN5 interrupt 1
                DCD     DTM_CAN6_INT0_IRQHandler          ; 124:DTM_CAN6 interrupt 0
                DCD     DTM_CAN6_INT1_IRQHandler          ; 125:DTM_CAN6 interrupt 1
                DCD     DTM_CAN7_INT0_IRQHandler          ; 126:DTM_CAN7 interrupt 0
                DCD     DTM_CAN7_INT1_IRQHandler          ; 127:DTM_CAN7 interrupt 1
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
                DCD     DMA0_Channel7_IRQHandler          ; 152:DMA0 Channel 7 global interrupt
                DCD     0                                 ; 153:Reserved
                DCD     0                                 ; 154:Reserved
                DCD     0                                 ; 155:Reserved
                DCD     0                                 ; 156:Reserved
                DCD     0                                 ; 157:Reserved
                DCD     0                                 ; 158:Reserved
                DCD     0                                 ; 159:Reserved
                DCD     0                                 ; 160:Reserved
                DCD     DMA1_Channel5_IRQHandler          ; 161:DMA1 Channel5 global interrupt
                DCD     DMA1_Channel6_IRQHandler          ; 162:DMA1 Channel6 global interrupt
                DCD     DMA1_Channel7_IRQHandler          ; 163:DMA1 Channel7 global interrupt
                DCD     0                                 ; 164:Reserved
                DCD     0                                 ; 165:Reserved
                DCD     0                                 ; 166:Reserved
                DCD     0                                 ; 167:Reserved
                DCD     0                                 ; 168:Reserved
                DCD     0                                 ; 169:Reserved
                DCD     0                                 ; 170:Reserved
                DCD     0                                 ; 171:Reserved
                DCD     0                                 ; 172:Reserved
                DCD     0                                 ; 173:Reserved
                DCD     0                                 ; 174:Reserved
                DCD     0                                 ; 175:Reserved
                DCD     0                                 ; 176:Reserved
                DCD     0                                 ; 177:Reserved
                DCD     LINFlexD0_IRQHandler              ; 178:LINFlexD0 Interrupt
                DCD     LINFlexD1_IRQHandler              ; 179:LINFlexD1 Interrupt
                DCD     LINFlexD2_IRQHandler              ; 180:LINFlexD2 Interrupt
                DCD     LINFlexD3_IRQHandler              ; 181:LINFlexD3 Interrupt
                DCD     LINFlexD4_IRQHandler              ; 182:LINFlexD4 Interrupt
                DCD     LINFlexD5_IRQHandler              ; 183:LINFlexD5 Interrupt
                DCD     0                                 ; 184:Reserved
                DCD     0                                 ; 185:Reserved
                DCD     0                                 ; 186:Reserved
                DCD     0                                 ; 187:Reserved
                DCD     0                                 ; 188:Reserved
                DCD     0                                 ; 189:Reserved
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
                DCD     0                                 ; 207:Reserved
                DCD     0                                 ; 208:Reserved
                DCD     0                                 ; 209:Reserved
                DCD     0                                 ; 210:Reserved
                DCD     0                                 ; 211:Reserved
                DCD     RCU_CK_FAIL_IRQHandler            ; 212:RCU clock fail interrupt
                DCD     0                                 ; 213:Reserved
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
                DCD     TIMER5_CH0_UP_IRQHandler          ; 230:TIMER5 channel 0 update interrupt
                DCD     TIMER5_CH1_UP_IRQHandler          ; 231:TIMER5 channel 1 update interrupt
                DCD     TIMER5_CH2_UP_IRQHandler          ; 232:TIMER5 channel 2 update interrupt
                DCD     TIMER5_CH3_UP_IRQHandler          ; 233:TIMER5 channel 3 update interrupt
                DCD     TIMER6_CH0_UP_IRQHandler          ; 234:TIMER6 channel 0 update interrupt
                DCD     TIMER6_CH1_UP_IRQHandler          ; 235:TIMER6 channel 1 update interrupt
                DCD     TIMER6_CH2_UP_IRQHandler          ; 236:TIMER6 channel 2 update interrupt
                DCD     TIMER6_CH3_UP_IRQHandler          ; 237:TIMER6 channel 3 update interrupt
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
                DCD     0                                 ; 254:Reserved
                DCD     0                                 ; 255:Reserved
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

;/* reset Handler */
Reset_Handler   PROC
                EXPORT  Reset_Handler                     [WEAK]
                IMPORT  |Image$$RW_IRAM1$$RW$$Base|

;If the actual size of SRAM used exceeds 32K, users need to modify the size to be greater than or equal to the actual size in use.
                 LDR     R0, =|Image$$RW_IRAM1$$RW$$Base|
                 ADD     R1, R0, #0x8000       ;Default SRAM size 32K
                 LDR     R2, =0x0
SRAM_INIT        STRD    R2, R2, [ R0 ] , #8
                 CMP     R0, R1
                 BNE     SRAM_INIT

;If the actual size of ITCMSRAM used exceeds 32K, users need to modify the size to be greater than or equal to the actual size in use.
                 LDR     R0, =0x00000000
                 ADD     R1, R0, #0x8000      ;Default ITCMSRAM size 32K
                 LDR     R2, =0x0
ITCMSRAM_INIT    STRD    R2, R2, [ R0 ] , #8
                 CMP     R0, R1
                 BNE     ITCMSRAM_INIT

;If the actual size of DTCMSRAM used exceeds 32K, users need to modify the size to be greater than or equal to the actual size in use.
                 LDR     R0, =0x20000000
                 ADD     R1, R0, #0x8000      ;Default DTCMSRAM size 32K
                 LDR     R2, =0x0
DTCMSRAM_INIT    STRD    R2, R2, [ R0 ] , #8
                 CMP     R0, R1
                 BNE     DTCMSRAM_INIT

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
                EXPORT  WWDGT0_IRQHandler                    [WEAK]
                EXPORT  HVD_LVD_IRQHandler                   [WEAK]
                EXPORT  RTC_Alarm_IRQHandler                 [WEAK]
                EXPORT  RTC_IRQHandler                       [WEAK]
                EXPORT  FMC_IRQHandler                       [WEAK]
                EXPORT  RCU_IRQHandler                       [WEAK]
                EXPORT  EXTI0_IRQHandler                     [WEAK]
                EXPORT  EXTI1_IRQHandler                     [WEAK]
                EXPORT  EXTI2_IRQHandler                     [WEAK]
                EXPORT  EXTI3_IRQHandler                     [WEAK]
                EXPORT  EXTI4_IRQHandler                     [WEAK]
                EXPORT  DMA0_Channel0_IRQHandler             [WEAK]
                EXPORT  DMA0_Channel1_IRQHandler             [WEAK]
                EXPORT  DMA0_Channel2_IRQHandler             [WEAK]
                EXPORT  DMA0_Channel3_IRQHandler             [WEAK]
                EXPORT  DMA0_Channel4_IRQHandler             [WEAK]
                EXPORT  DMA0_Channel5_IRQHandler             [WEAK]
                EXPORT  DMA0_Channel6_IRQHandler             [WEAK]
                EXPORT  ADC0_IRQHandler                      [WEAK]
                EXPORT  DTM_CAN0_INT0_IRQHandler             [WEAK]
                EXPORT  DTM_CAN0_INT1_IRQHandler             [WEAK]
                EXPORT  DTM_CAN0_DMU_IRQHandler              [WEAK]
                EXPORT  TIMER0_BRK_UP_TRG_CMT_IRQHandler     [WEAK]
                EXPORT  TIMER2_IRQHandler                    [WEAK]
                EXPORT  TIMER1_IRQHandler                    [WEAK]
                EXPORT  TIMER19_BRK_UP_TRG_CMT_IRQHandler    [WEAK]
                EXPORT  JDC_IRQHandler                       [WEAK]
                EXPORT  I2C0_EV_IRQHandler                   [WEAK]
                EXPORT  I2C0_ER_IRQHandler                   [WEAK]
                EXPORT  I2C1_EV_IRQHandler                   [WEAK]
                EXPORT  I2C1_ER_IRQHandler                   [WEAK]
                EXPORT  SPI0_IRQHandler                      [WEAK]
                EXPORT  SPI1_IRQHandler                      [WEAK]
                EXPORT  EXTI10_15_IRQHandler                 [WEAK]
                EXPORT  EXTI5_9_IRQHandler                   [WEAK]
                EXPORT  TAMPER_IRQHandler                    [WEAK]
                EXPORT  TIMER20_BRK_UP_TRG_CMT_IRQHandler    [WEAK]
                EXPORT  EXTI42_101_IRQHandler                [WEAK]
                EXPORT  TIMER7_BRK_UP_TRG_CMT_IRQHandler     [WEAK]
                EXPORT  PLL_LOL_DES_RESET_IRQHandler         [WEAK]
                EXPORT  DMAMUX_OVR_IRQHandler                [WEAK]
                EXPORT  FPU_WAB_IRQHandler                   [WEAK]
                EXPORT  CMP0_EXTI_IRQHandler                 [WEAK]
                EXPORT  CMP1_EXTI_IRQHandler                 [WEAK]
                EXPORT  FMU_INIT_IRQHandler                  [WEAK]
                EXPORT  ADC1_IRQHandler                      [WEAK]
                EXPORT  DAC0_IRQHandler                      [WEAK]
                EXPORT  STCM_IRQHandler                      [WEAK]
                EXPORT  DMA1_Channel0_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler             [WEAK]
                EXPORT  DTM_CAN1_INT0_IRQHandler             [WEAK]
                EXPORT  DTM_CAN1_INT1_IRQHandler             [WEAK]
                EXPORT  DTM_CAN1_DMU_IRQHandler              [WEAK]
                EXPORT  CTI0_IRQHandler                      [WEAK]
                EXPORT  CTI1_IRQHandler                      [WEAK]
                EXPORT  CAN0_ECCERR_IRQHandler               [WEAK]
                EXPORT  CAN1_ECCERR_IRQHandler               [WEAK]
                EXPORT  CAN2_ECCERR_IRQHandler               [WEAK]
                EXPORT  CMP0_IRQHandler                      [WEAK]
                EXPORT  CMP1_IRQHandler                      [WEAK]
                EXPORT  DAC1_IRQHandler                      [WEAK]
                EXPORT  HSM_COM0_IRQHandler                  [WEAK]
                EXPORT  HSM_COM1_IRQHandler                  [WEAK]
                EXPORT  FMU_CAT_IRQHandler                   [WEAK]
                EXPORT  RCTL_IRQHandler                      [WEAK]
                EXPORT  SPI2_IRQHandler                      [WEAK]
                EXPORT  SPI3_IRQHandler                      [WEAK]
                EXPORT  SPI4_IRQHandler                      [WEAK]
                EXPORT  SPI5_IRQHandler                      [WEAK]
                EXPORT  QSPI_IRQHandler                      [WEAK]
                EXPORT  DTM_CAN2_DMU_IRQHandler              [WEAK]
                EXPORT  DTM_CAN3_DMU_IRQHandler              [WEAK]
                EXPORT  DTM_CAN4_DMU_IRQHandler              [WEAK]
                EXPORT  DTM_CAN5_DMU_IRQHandler              [WEAK]
                EXPORT  DTM_CAN6_DMU_IRQHandler              [WEAK]
                EXPORT  DTM_CAN7_DMU_IRQHandler              [WEAK]
                EXPORT  DTM_CAN2_INT0_IRQHandler             [WEAK]
                EXPORT  DTM_CAN2_INT1_IRQHandler             [WEAK]
                EXPORT  DTM_CAN3_INT0_IRQHandler             [WEAK]
                EXPORT  DTM_CAN3_INT1_IRQHandler             [WEAK]
                EXPORT  DTM_CAN4_INT0_IRQHandler             [WEAK]
                EXPORT  DTM_CAN4_INT1_IRQHandler             [WEAK]
                EXPORT  DTM_CAN5_INT0_IRQHandler             [WEAK]
                EXPORT  DTM_CAN5_INT1_IRQHandler             [WEAK]
                EXPORT  DTM_CAN6_INT0_IRQHandler             [WEAK]
                EXPORT  DTM_CAN6_INT1_IRQHandler             [WEAK]
                EXPORT  DTM_CAN7_INT0_IRQHandler             [WEAK]
                EXPORT  DTM_CAN7_INT1_IRQHandler             [WEAK]
                EXPORT  TIMER19_CC0_CC0N_IRQHandler          [WEAK]
                EXPORT  TIMER19_CC1_CC1N_IRQHandler          [WEAK]
                EXPORT  TIMER19_CC2_CC2N_IRQHandler          [WEAK]
                EXPORT  TIMER19_CC3_CC3N_IRQHandler          [WEAK]
                EXPORT  TIMER20_CC0_CC0N_IRQHandler          [WEAK]
                EXPORT  TIMER20_CC1_CC1N_IRQHandler          [WEAK]
                EXPORT  TIMER20_CC2_CC2N_IRQHandler          [WEAK]
                EXPORT  TIMER20_CC3_CC3N_IRQHandler          [WEAK]
                EXPORT  TIMER60_CC0_CC0N_IRQHandler          [WEAK]
                EXPORT  TIMER60_CC1_CC1N_IRQHandler          [WEAK]
                EXPORT  TIMER60_CC2_CC2N_IRQHandler          [WEAK]
                EXPORT  TIMER60_CC3_CC3N_IRQHandler          [WEAK]
                EXPORT  TIMER61_CC0_CC0N_IRQHandler          [WEAK]
                EXPORT  TIMER61_CC1_CC1N_IRQHandler          [WEAK]
                EXPORT  TIMER61_CC2_CC2N_IRQHandler          [WEAK]
                EXPORT  TIMER61_CC3_CC3N_IRQHandler          [WEAK]
                EXPORT  TIMER62_CC0_CC0N_IRQHandler          [WEAK]
                EXPORT  TIMER62_CC1_CC1N_IRQHandler          [WEAK]
                EXPORT  TIMER62_CC2_CC2N_IRQHandler          [WEAK]
                EXPORT  TIMER62_CC3_CC3N_IRQHandler          [WEAK]
                EXPORT  TIMER63_CC0_CC0N_IRQHandler          [WEAK]
                EXPORT  TIMER63_CC1_CC1N_IRQHandler          [WEAK]
                EXPORT  TIMER63_CC2_CC2N_IRQHandler          [WEAK]
                EXPORT  TIMER63_CC3_CC3N_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel7_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler             [WEAK]
                EXPORT  LINFlexD0_IRQHandler                 [WEAK]
                EXPORT  LINFlexD1_IRQHandler                 [WEAK]
                EXPORT  LINFlexD2_IRQHandler                 [WEAK]
                EXPORT  LINFlexD3_IRQHandler                 [WEAK]
                EXPORT  LINFlexD4_IRQHandler                 [WEAK]
                EXPORT  LINFlexD5_IRQHandler                 [WEAK]
                EXPORT  TIMER0_CC0_CC0N_IRQHandler           [WEAK]
                EXPORT  TIMER0_CC1_CC1N_IRQHandler           [WEAK]
                EXPORT  TIMER0_CC2_CC2N_IRQHandler           [WEAK]
                EXPORT  TIMER0_CC3_CC3N_IRQHandler           [WEAK]
                EXPORT  TIMER7_CC0_CC0N_IRQHandler           [WEAK]
                EXPORT  TIMER7_CC1_CC1N_IRQHandler           [WEAK]
                EXPORT  TIMER7_CC2_CC2N_IRQHandler           [WEAK]
                EXPORT  TIMER7_CC3_CC3N_IRQHandler           [WEAK]
                EXPORT  TIMER1_CC0_IRQHandler                [WEAK]
                EXPORT  TIMER1_CC1_IRQHandler                [WEAK]
                EXPORT  TIMER1_CC2_IRQHandler                [WEAK]
                EXPORT  TIMER1_CC3_IRQHandler                [WEAK]
                EXPORT  TIMER2_CC0_IRQHandler                [WEAK]
                EXPORT  TIMER2_CC1_IRQHandler                [WEAK]
                EXPORT  TIMER2_CC2_IRQHandler                [WEAK]
                EXPORT  TIMER2_CC3_IRQHandler                [WEAK]
                EXPORT  FWDGT_IRQHandler                     [WEAK]
                EXPORT  RCU_CK_FAIL_IRQHandler               [WEAK]
                EXPORT  TIMER60_BRK_UP_TRG_CMT_IRQHandler    [WEAK]
                EXPORT  TIMER61_BRK_UP_TRG_CMT_IRQHandler    [WEAK]
                EXPORT  TIMER62_BRK_UP_TRG_CMT_IRQHandler    [WEAK]
                EXPORT  TIMER63_BRK_UP_TRG_CMT_IRQHandler    [WEAK]
                EXPORT  TIMER5_CH0_UP_IRQHandler             [WEAK]
                EXPORT  TIMER5_CH1_UP_IRQHandler             [WEAK]
                EXPORT  TIMER5_CH2_UP_IRQHandler             [WEAK]
                EXPORT  TIMER5_CH3_UP_IRQHandler             [WEAK]
                EXPORT  TIMER6_CH0_UP_IRQHandler             [WEAK]
                EXPORT  TIMER6_CH1_UP_IRQHandler             [WEAK]
                EXPORT  TIMER6_CH2_UP_IRQHandler             [WEAK]
                EXPORT  TIMER6_CH3_UP_IRQHandler             [WEAK]
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
DTM_CAN0_INT0_IRQHandler
DTM_CAN0_INT1_IRQHandler
DTM_CAN0_DMU_IRQHandler
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
DAC0_IRQHandler
STCM_IRQHandler
DMA1_Channel0_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
DTM_CAN1_INT0_IRQHandler
DTM_CAN1_INT1_IRQHandler
DTM_CAN1_DMU_IRQHandler
CTI0_IRQHandler
CTI1_IRQHandler
CAN0_ECCERR_IRQHandler
CAN1_ECCERR_IRQHandler
CAN2_ECCERR_IRQHandler
CMP0_IRQHandler
CMP1_IRQHandler
DAC1_IRQHandler
HSM_COM0_IRQHandler
HSM_COM1_IRQHandler
FMU_CAT_IRQHandler
RCTL_IRQHandler
SPI2_IRQHandler
SPI3_IRQHandler
SPI4_IRQHandler
SPI5_IRQHandler
QSPI_IRQHandler
DTM_CAN2_DMU_IRQHandler
DTM_CAN3_DMU_IRQHandler
DTM_CAN4_DMU_IRQHandler
DTM_CAN5_DMU_IRQHandler
DTM_CAN6_DMU_IRQHandler
DTM_CAN7_DMU_IRQHandler
DTM_CAN2_INT0_IRQHandler
DTM_CAN2_INT1_IRQHandler
DTM_CAN3_INT0_IRQHandler
DTM_CAN3_INT1_IRQHandler
DTM_CAN4_INT0_IRQHandler
DTM_CAN4_INT1_IRQHandler
DTM_CAN5_INT0_IRQHandler
DTM_CAN5_INT1_IRQHandler
DTM_CAN6_INT0_IRQHandler
DTM_CAN6_INT1_IRQHandler
DTM_CAN7_INT0_IRQHandler
DTM_CAN7_INT1_IRQHandler
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
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
LINFlexD0_IRQHandler
LINFlexD1_IRQHandler
LINFlexD2_IRQHandler
LINFlexD3_IRQHandler
LINFlexD4_IRQHandler
LINFlexD5_IRQHandler
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
RCU_CK_FAIL_IRQHandler
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
