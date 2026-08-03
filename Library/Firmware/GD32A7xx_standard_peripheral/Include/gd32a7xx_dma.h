/*!
    \file    gd32a7xx_dma.h
    \brief   definitions for the DMA

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

#ifndef GD32A7XX_DMA_H
#define GD32A7XX_DMA_H

#include "gd32a7xx.h"

/* DMA definitions */
#define DMA0                              (DMA_BASE)                      /*!< DMA0 base address */
#define DMA1                              (DMA_BASE + 0x0400U)            /*!< DMA1 base address */

/* DMAMUX definitions */
#define DMAMUX                             DMAMUX_BASE                    /*!< DMA base address */

/* registers definitions */
/* DMA registers definitions */
#define DMA_INTF0(dmax)                    REG32((dmax) + 0x00U)          /*!< DMA interrupt flag register 0 */
#define DMA_INTF1(dmax)                    REG32((dmax) + 0x04U)          /*!< DMA interrupt flag register 1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_INTF2(dmax)                    REG32((dmax) + 0x08U)          /*!< DMA interrupt flag register 2 */
#define DMA_INTF3(dmax)                    REG32((dmax) + 0x0CU)          /*!< DMA interrupt flag register 3 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMA_INTC0(dmax)                    REG32((dmax) + 0x10U)          /*!< DMA interrupt flag clear register 0 */
#define DMA_INTC1(dmax)                    REG32((dmax) + 0x14U)          /*!< DMA interrupt flag clear register 1 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_INTC2(dmax)                    REG32((dmax) + 0x18U)          /*!< DMA interrupt flag clear register 2 */
#define DMA_INTC3(dmax)                    REG32((dmax) + 0x1CU)          /*!< DMA interrupt flag clear register 3 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMA_CH0CTL(dmax)                   REG32((dmax) + 0x20U)          /*!< DMA channel 0 control register */
#define DMA_CH0CNT(dmax)                   REG32((dmax) + 0x24U)          /*!< DMA channel 0 counter register */
#define DMA_CH0PADDR(dmax)                 REG32((dmax) + 0x28U)          /*!< DMA channel 0 peripheral base address register */
#define DMA_CH0M0ADDR(dmax)                REG32((dmax) + 0x2CU)          /*!< DMA channel 0 memory 0 base address register */
#define DMA_CH0M1ADDR(dmax)                REG32((dmax) + 0x30U)          /*!< DMA channel 0 memory 1 base address register */
#define DMA_CH0FCTL(dmax)                  REG32((dmax) + 0x34U)          /*!< DMA channel 0 FIFO control register */
#define DMA_CH0PCRCDATA(dmax)              REG32((dmax) + 0x200U)         /*!< DMA channel 0 peripheral CRC data register */
#define DMA_CH0TOCTL(dmax)                 REG32((dmax) + 0x300U)         /*!< DMA channel 0 transfer timeout monitor control register */
#define DMA_CH0PCADDR(dmax)                REG32((dmax) + 0x350U)         /*!< DMA channel 0 peripheral port current address register */
#define DMA_CH0MCADDR(dmax)                REG32((dmax) + 0x390U)         /*!< DMA channel 0 memory port current address register */
#define DMA_CH1CTL(dmax)                   REG32((dmax) + 0x38U)          /*!< DMA channel 1 control register */
#define DMA_CH1CNT(dmax)                   REG32((dmax) + 0x3CU)          /*!< DMA channel 1 counter register */
#define DMA_CH1PADDR(dmax)                 REG32((dmax) + 0x40U)          /*!< DMA channel 1 peripheral base address register */
#define DMA_CH1M0ADDR(dmax)                REG32((dmax) + 0x44U)          /*!< DMA channel 1 memory 0 base address register */
#define DMA_CH1M1ADDR(dmax)                REG32((dmax) + 0x48U)          /*!< DMA channel 1 memory 1 base address register */
#define DMA_CH1FCTL(dmax)                  REG32((dmax) + 0x4CU)          /*!< DMA channel 1 FIFO control register */
#define DMA_CH1PCRCDATA(dmax)              REG32((dmax) + 0x204U)         /*!< DMA channel 1 peripheral CRC data register */
#define DMA_CH1TOCTL(dmax)                 REG32((dmax) + 0x304U)         /*!< DMA channel 1 transfer timeout monitor control register */
#define DMA_CH1PCADDR(dmax)                REG32((dmax) + 0x354U)         /*!< DMA channel 1 peripheral port current address register */
#define DMA_CH1MCADDR(dmax)                REG32((dmax) + 0x394U)         /*!< DMA channel 1 memory port current address register */
#define DMA_CH2CTL(dmax)                   REG32((dmax) + 0x50U)          /*!< DMA channel 2 control register */
#define DMA_CH2CNT(dmax)                   REG32((dmax) + 0x54U)          /*!< DMA channel 2 counter register */
#define DMA_CH2PADDR(dmax)                 REG32((dmax) + 0x58U)          /*!< DMA channel 2 peripheral base address register */
#define DMA_CH2M0ADDR(dmax)                REG32((dmax) + 0x5CU)          /*!< DMA channel 2 memory 0 base address register */
#define DMA_CH2M1ADDR(dmax)                REG32((dmax) + 0x60U)          /*!< DMA channel 2 memory 1 base address register */
#define DMA_CH2FCTL(dmax)                  REG32((dmax) + 0x64U)          /*!< DMA channel 2 FIFO control register */
#define DMA_CH2PCRCDATA(dmax)              REG32((dmax) + 0x208U)         /*!< DMA channel 2 peripheral CRC data register */
#define DMA_CH2TOCTL(dmax)                 REG32((dmax) + 0x308U)         /*!< DMA channel 2 transfer timeout monitor control register */
#define DMA_CH2PCADDR(dmax)                REG32((dmax) + 0x358U)         /*!< DMA channel 2 peripheral port current address register */
#define DMA_CH2MCADDR(dmax)                REG32((dmax) + 0x398U)         /*!< DMA channel 2 memory port current address register */
#define DMA_CH3CTL(dmax)                   REG32((dmax) + 0x68U)          /*!< DMA channel 3 control register */
#define DMA_CH3CNT(dmax)                   REG32((dmax) + 0x6CU)          /*!< DMA channel 3 counter register */
#define DMA_CH3PADDR(dmax)                 REG32((dmax) + 0x70U)          /*!< DMA channel 3 peripheral base address register */
#define DMA_CH3M0ADDR(dmax)                REG32((dmax) + 0x74U)          /*!< DMA channel 3 memory 0 base address register */
#define DMA_CH3M1ADDR(dmax)                REG32((dmax) + 0x78U)          /*!< DMA channel 3 memory 1 base address register */
#define DMA_CH3FCTL(dmax)                  REG32((dmax) + 0x7CU)          /*!< DMA channel 3 FIFO control register */
#define DMA_CH3PCRCDATA(dmax)              REG32((dmax) + 0x20CU)         /*!< DMA channel 3 peripheral CRC data register */
#define DMA_CH3TOCTL(dmax)                 REG32((dmax) + 0x30CU)         /*!< DMA channel 3 transfer timeout monitor control register */
#define DMA_CH3PCADDR(dmax)                REG32((dmax) + 0x35CU)         /*!< DMA channel 3 peripheral port current address register */
#define DMA_CH3MCADDR(dmax)                REG32((dmax) + 0x39CU)         /*!< DMA channel 3 memory port current address register */
#define DMA_CH4CTL(dmax)                   REG32((dmax) + 0x80U)          /*!< DMA channel 4 control register */
#define DMA_CH4CNT(dmax)                   REG32((dmax) + 0x84U)          /*!< DMA channel 4 counter register */
#define DMA_CH4PADDR(dmax)                 REG32((dmax) + 0x88U)          /*!< DMA channel 4 peripheral base address register */
#define DMA_CH4M0ADDR(dmax)                REG32((dmax) + 0x8CU)          /*!< DMA channel 4 memory 0 base address register */
#define DMA_CH4M1ADDR(dmax)                REG32((dmax) + 0x90U)          /*!< DMA channel 4 memory 1 base address register */
#define DMA_CH4FCTL(dmax)                  REG32((dmax) + 0x94U)          /*!< DMA channel 4 FIFO control register */
#define DMA_CH4PCRCDATA(dmax)              REG32((dmax) + 0x210U)         /*!< DMA channel 4 peripheral CRC data register */
#define DMA_CH4TOCTL(dmax)                 REG32((dmax) + 0x310U)         /*!< DMA channel 4 transfer timeout monitor control register */
#define DMA_CH4PCADDR(dmax)                REG32((dmax) + 0x360U)         /*!< DMA channel 4 peripheral port current address register */
#define DMA_CH4MCADDR(dmax)                REG32((dmax) + 0x3A0U)         /*!< DMA channel 4 memory port current address register */
#define DMA_CH5CTL(dmax)                   REG32((dmax) + 0x98U)          /*!< DMA channel 5 control register */
#define DMA_CH5CNT(dmax)                   REG32((dmax) + 0x9CU)          /*!< DMA channel 5 counter register */
#define DMA_CH5PADDR(dmax)                 REG32((dmax) + 0xA0U)          /*!< DMA channel 5 peripheral base address register */
#define DMA_CH5M0ADDR(dmax)                REG32((dmax) + 0xA4U)          /*!< DMA channel 5 memory 0 base address register */
#define DMA_CH5M1ADDR(dmax)                REG32((dmax) + 0xA8U)          /*!< DMA channel 5 memory 1 base address register */
#define DMA_CH5FCTL(dmax)                  REG32((dmax) + 0xACU)          /*!< DMA channel 5 FIFO control register */
#define DMA_CH5PCRCDATA(dmax)              REG32((dmax) + 0x214U)         /*!< DMA channel 5 peripheral CRC data register */
#define DMA_CH5TOCTL(dmax)                 REG32((dmax) + 0x314U)         /*!< DMA channel 5 transfer timeout monitor control register */
#define DMA_CH5PCADDR(dmax)                REG32((dmax) + 0x364U)         /*!< DMA channel 5 peripheral port current address register */
#define DMA_CH5MCADDR(dmax)                REG32((dmax) + 0x3A4U)         /*!< DMA channel 5 memory port current address register */
#define DMA_CH6CTL(dmax)                   REG32((dmax) + 0xB0U)          /*!< DMA channel 6 control register */
#define DMA_CH6CNT(dmax)                   REG32((dmax) + 0xB4U)          /*!< DMA channel 6 counter register */
#define DMA_CH6PADDR(dmax)                 REG32((dmax) + 0xB8U)          /*!< DMA channel 6 peripheral base address register */
#define DMA_CH6M0ADDR(dmax)                REG32((dmax) + 0xBCU)          /*!< DMA channel 6 memory 0 base address register */
#define DMA_CH6M1ADDR(dmax)                REG32((dmax) + 0xC0U)          /*!< DMA channel 6 memory 1 base address register */
#define DMA_CH6FCTL(dmax)                  REG32((dmax) + 0xC4U)          /*!< DMA channel 6 FIFO control register */
#define DMA_CH6PCRCDATA(dmax)              REG32((dmax) + 0x218U)         /*!< DMA channel 6 peripheral CRC data register */
#define DMA_CH6TOCTL(dmax)                 REG32((dmax) + 0x318U)         /*!< DMA channel 6 transfer timeout monitor control register */
#define DMA_CH6PCADDR(dmax)                REG32((dmax) + 0x368U)         /*!< DMA channel 6 peripheral port current address register */
#define DMA_CH6MCADDR(dmax)                REG32((dmax) + 0x3A8U)         /*!< DMA channel 6 memory port current address register */
#define DMA_CH7CTL(dmax)                   REG32((dmax) + 0xC8U)          /*!< DMA channel 7 control register */
#define DMA_CH7CNT(dmax)                   REG32((dmax) + 0xCCU)          /*!< DMA channel 7 counter register */
#define DMA_CH7PADDR(dmax)                 REG32((dmax) + 0xD0U)          /*!< DMA channel 7 peripheral base address register */
#define DMA_CH7M0ADDR(dmax)                REG32((dmax) + 0xD4U)          /*!< DMA channel 7 memory 0 base address register */
#define DMA_CH7M1ADDR(dmax)                REG32((dmax) + 0xD8U)          /*!< DMA channel 7 memory 1 base address register */
#define DMA_CH7FCTL(dmax)                  REG32((dmax) + 0xDCU)          /*!< DMA channel 7 FIFO control register */
#define DMA_CH7PCRCDATA(dmax)              REG32((dmax) + 0x21CU)         /*!< DMA channel 7 peripheral CRC data register */
#define DMA_CH7TOCTL(dmax)                 REG32((dmax) + 0x31CU)         /*!< DMA channel 7 transfer timeout monitor control register */
#define DMA_CH7PCADDR(dmax)                REG32((dmax) + 0x36CU)         /*!< DMA channel 7 peripheral port current address register */
#define DMA_CH7MCADDR(dmax)                REG32((dmax) + 0x3ACU)         /*!< DMA channel 7 memory port current address register */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_CH8CTL(dmax)                   REG32((dmax) + 0xE0U)          /*!< DMA channel 8 control register */
#define DMA_CH8CNT(dmax)                   REG32((dmax) + 0xE4U)          /*!< DMA channel 8 counter register */
#define DMA_CH8PADDR(dmax)                 REG32((dmax) + 0xE8U)          /*!< DMA channel 8 peripheral base address register */
#define DMA_CH8M0ADDR(dmax)                REG32((dmax) + 0xECU)          /*!< DMA channel 8 memory 0 base address register */
#define DMA_CH8M1ADDR(dmax)                REG32((dmax) + 0xF0U)          /*!< DMA channel 8 memory 1 base address register */
#define DMA_CH8FCTL(dmax)                  REG32((dmax) + 0xF4U)          /*!< DMA channel 8 FIFO control register */
#define DMA_CH8PCRCDATA(dmax)              REG32((dmax) + 0x220U)         /*!< DMA channel 8 peripheral CRC data register */
#define DMA_CH8TOCTL(dmax)                 REG32((dmax) + 0x320U)         /*!< DMA channel 8 transfer timeout monitor control register */
#define DMA_CH8PCADDR(dmax)                REG32((dmax) + 0x370U)         /*!< DMA channel 8 peripheral port current address register */
#define DMA_CH8MCADDR(dmax)                REG32((dmax) + 0x3B0U)         /*!< DMA channel 8 memory port current address register */
#define DMA_CH9CTL(dmax)                   REG32((dmax) + 0xF8U)          /*!< DMA channel 9 control register */
#define DMA_CH9CNT(dmax)                   REG32((dmax) + 0xFCU)          /*!< DMA channel 9 counter register */
#define DMA_CH9PADDR(dmax)                 REG32((dmax) + 0x100U)         /*!< DMA channel 9 peripheral base address register */
#define DMA_CH9M0ADDR(dmax)                REG32((dmax) + 0x104U)         /*!< DMA channel 9 memory 0 base address register */
#define DMA_CH9M1ADDR(dmax)                REG32((dmax) + 0x108U)         /*!< DMA channel 9 memory 1 base address register */
#define DMA_CH9FCTL(dmax)                  REG32((dmax) + 0x10CU)         /*!< DMA channel 9 FIFO control register */
#define DMA_CH9PCRCDATA(dmax)              REG32((dmax) + 0x224U)         /*!< DMA channel 9 peripheral CRC data register */
#define DMA_CH9TOCTL(dmax)                 REG32((dmax) + 0x324U)         /*!< DMA channel 9 transfer timeout monitor control register */
#define DMA_CH9PCADDR(dmax)                REG32((dmax) + 0x374U)         /*!< DMA channel 9 peripheral port current address register */
#define DMA_CH9MCADDR(dmax)                REG32((dmax) + 0x3B4U)         /*!< DMA channel 9 memory port current address register */
#define DMA_CH10CTL(dmax)                  REG32((dmax) + 0x110U)         /*!< DMA channel 10 control register */
#define DMA_CH10CNT(dmax)                  REG32((dmax) + 0x114U)         /*!< DMA channel 10 counter register */
#define DMA_CH10PADDR(dmax)                REG32((dmax) + 0x118U)         /*!< DMA channel 10 peripheral base address register */
#define DMA_CH10M0ADDR(dmax)               REG32((dmax) + 0x11CU)         /*!< DMA channel 10 memory 0 base address register */
#define DMA_CH10M1ADDR(dmax)               REG32((dmax) + 0x120U)         /*!< DMA channel 10 memory 1 base address register */
#define DMA_CH10FCTL(dmax)                 REG32((dmax) + 0x124U)         /*!< DMA channel 10 FIFO control register */
#define DMA_CH10PCRCDATA(dmax)             REG32((dmax) + 0x228U)         /*!< DMA channel 10 peripheral CRC data register */
#define DMA_CH10TOCTL(dmax)                REG32((dmax) + 0x328U)         /*!< DMA channel 10 transfer timeout monitor control register */
#define DMA_CH10PCADDR(dmax)               REG32((dmax) + 0x378U)         /*!< DMA channel 10 peripheral port current address register */
#define DMA_CH10MCADDR(dmax)               REG32((dmax) + 0x3B8U)         /*!< DMA channel 10 memory port current address register */
#define DMA_CH11CTL(dmax)                  REG32((dmax) + 0x128U)         /*!< DMA channel 11 control register */
#define DMA_CH11CNT(dmax)                  REG32((dmax) + 0x12CU)         /*!< DMA channel 11 counter register */
#define DMA_CH11PADDR(dmax)                REG32((dmax) + 0x130U)         /*!< DMA channel 11 peripheral base address register */
#define DMA_CH11M0ADDR(dmax)               REG32((dmax) + 0x134U)         /*!< DMA channel 11 memory 0 base address register */
#define DMA_CH11M1ADDR(dmax)               REG32((dmax) + 0x138U)         /*!< DMA channel 11 memory 1 base address register */
#define DMA_CH11FCTL(dmax)                 REG32((dmax) + 0x13CU)         /*!< DMA channel 11 FIFO control register */
#define DMA_CH11PCRCDATA(dmax)             REG32((dmax) + 0x22CU)         /*!< DMA channel 11 peripheral CRC data register */
#define DMA_CH11TOCTL(dmax)                REG32((dmax) + 0x32CU)         /*!< DMA channel 11 transfer timeout monitor control register */
#define DMA_CH11PCADDR(dmax)               REG32((dmax) + 0x37CU)         /*!< DMA channel 11 peripheral port current address register */
#define DMA_CH11MCADDR(dmax)               REG32((dmax) + 0x3BCU)         /*!< DMA channel 11 memory port current address register */
#define DMA_CH12CTL(dmax)                  REG32((dmax) + 0x140U)         /*!< DMA channel 12 control register */
#define DMA_CH12CNT(dmax)                  REG32((dmax) + 0x144U)         /*!< DMA channel 12 counter register */
#define DMA_CH12PADDR(dmax)                REG32((dmax) + 0x148U)         /*!< DMA channel 12 peripheral base address register */
#define DMA_CH12M0ADDR(dmax)               REG32((dmax) + 0x14CU)         /*!< DMA channel 12 memory 0 base address register */
#define DMA_CH12M1ADDR(dmax)               REG32((dmax) + 0x150U)         /*!< DMA channel 12 memory 1 base address register */
#define DMA_CH12FCTL(dmax)                 REG32((dmax) + 0x154U)         /*!< DMA channel 12 FIFO control register */
#define DMA_CH12PCRCDATA(dmax)             REG32((dmax) + 0x230U)         /*!< DMA channel 12 peripheral CRC data register */
#define DMA_CH12TOCTL(dmax)                REG32((dmax) + 0x330U)         /*!< DMA channel 12 transfer timeout monitor control register */
#define DMA_CH12PCADDR(dmax)               REG32((dmax) + 0x380U)         /*!< DMA channel 12 peripheral port current address register */
#define DMA_CH12MCADDR(dmax)               REG32((dmax) + 0x3C0U)         /*!< DMA channel 12 memory port current address register */
#define DMA_CH13CTL(dmax)                  REG32((dmax) + 0x158U)         /*!< DMA channel 13 control register */
#define DMA_CH13CNT(dmax)                  REG32((dmax) + 0x15CU)         /*!< DMA channel 13 counter register */
#define DMA_CH13PADDR(dmax)                REG32((dmax) + 0x160U)         /*!< DMA channel 13 peripheral base address register */
#define DMA_CH13M0ADDR(dmax)               REG32((dmax) + 0x164U)         /*!< DMA channel 13 memory 0 base address register */
#define DMA_CH13M1ADDR(dmax)               REG32((dmax) + 0x168U)         /*!< DMA channel 13 memory 1 base address register */
#define DMA_CH13FCTL(dmax)                 REG32((dmax) + 0x16CU)         /*!< DMA channel 13 FIFO control register */
#define DMA_CH13PCRCDATA(dmax)             REG32((dmax) + 0x234U)         /*!< DMA channel 13 peripheral CRC data register */
#define DMA_CH13TOCTL(dmax)                REG32((dmax) + 0x334U)         /*!< DMA channel 13 transfer timeout monitor control register */
#define DMA_CH13PCADDR(dmax)               REG32((dmax) + 0x384U)         /*!< DMA channel 13 peripheral port current address register */
#define DMA_CH13MCADDR(dmax)               REG32((dmax) + 0x3C4U)         /*!< DMA channel 13 memory port current address register */
#define DMA_CH14CTL(dmax)                  REG32((dmax) + 0x170U)         /*!< DMA channel 14 control register */
#define DMA_CH14CNT(dmax)                  REG32((dmax) + 0x174U)         /*!< DMA channel 14 counter register */
#define DMA_CH14PADDR(dmax)                REG32((dmax) + 0x178U)         /*!< DMA channel 14 peripheral base address register */
#define DMA_CH14M0ADDR(dmax)               REG32((dmax) + 0x17CU)         /*!< DMA channel 14 memory 0 base address register */
#define DMA_CH14M1ADDR(dmax)               REG32((dmax) + 0x180U)         /*!< DMA channel 14 memory 1 base address register */
#define DMA_CH14FCTL(dmax)                 REG32((dmax) + 0x184U)         /*!< DMA channel 14 FIFO control register */
#define DMA_CH14PCRCDATA(dmax)             REG32((dmax) + 0x238U)         /*!< DMA channel 14 peripheral CRC data register */
#define DMA_CH14TOCTL(dmax)                REG32((dmax) + 0x338U)         /*!< DMA channel 14 transfer timeout monitor control register */
#define DMA_CH14PCADDR(dmax)               REG32((dmax) + 0x388U)         /*!< DMA channel 14 peripheral port current address register */
#define DMA_CH14MCADDR(dmax)               REG32((dmax) + 0x3C8U)         /*!< DMA channel 14 memory port current address register */
#define DMA_CH15CTL(dmax)                  REG32((dmax) + 0x188U)         /*!< DMA channel 15 control register */
#define DMA_CH15CNT(dmax)                  REG32((dmax) + 0x18CU)         /*!< DMA channel 15 counter register */
#define DMA_CH15PADDR(dmax)                REG32((dmax) + 0x190U)         /*!< DMA channel 15 peripheral base address register */
#define DMA_CH15M0ADDR(dmax)               REG32((dmax) + 0x194U)         /*!< DMA channel 15 memory 0 base address register */
#define DMA_CH15M1ADDR(dmax)               REG32((dmax) + 0x198U)         /*!< DMA channel 15 memory 1 base address register */
#define DMA_CH15FCTL(dmax)                 REG32((dmax) + 0x19CU)         /*!< DMA channel 15 FIFO control register */
#define DMA_CH15PCRCDATA(dmax)             REG32((dmax) + 0x23CU)         /*!< DMA channel 15 peripheral CRC data register */
#define DMA_CH15TOCTL(dmax)                REG32((dmax) + 0x33CU)         /*!< DMA channel 15 transfer timeout monitor control register */
#define DMA_CH15PCADDR(dmax)               REG32((dmax) + 0x38CU)         /*!< DMA channel 15 peripheral port current address register */
#define DMA_CH15MCADDR(dmax)               REG32((dmax) + 0x3CCU)         /*!< DMA channel 15 memory port current address register */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMA_CRCIDATA(dmax)                 REG32((dmax) + 0x240U)         /*!< DMA CRC initialization data register */
#define DMA_PCRCCTL(dmax)                  REG32((dmax) + 0x280U)         /*!< DMA peripheral CRC control register */
#define DMA_GCTL(dmax)                     REG32((dmax) + 0x2C0U)         /*!< DMA global control register */
#define DMA_TOINTF(dmax)                   REG32((dmax) + 0x340U)         /*!< DMA timeout flag register  */
#define DMA_TOINTEN(dmax)                  REG32((dmax) + 0x344U)         /*!< DMA timeout interrupt control register */
#define DMA_TFINTF(dmax)                   REG32((dmax) + 0x348U)         /*!< DMA TMR fault flag register   */
#define DMA_TFINTEN(dmax)                  REG32((dmax) + 0x34CU)         /*!< DMA TMR fault interrupt enable register */

/* DMAMUX registers definitions */
#define DMAMUX_RM_CH0CFG                   REG32(DMAMUX + 0x00U)          /*!< DMAMUX request multiplexer channel 0 configuration register */
#define DMAMUX_RM_CH1CFG                   REG32(DMAMUX + 0x04U)          /*!< DMAMUX request multiplexer channel 1 configuration register */
#define DMAMUX_RM_CH2CFG                   REG32(DMAMUX + 0x08U)          /*!< DMAMUX request multiplexer channel 2 configuration register */
#define DMAMUX_RM_CH3CFG                   REG32(DMAMUX + 0x0CU)          /*!< DMAMUX request multiplexer channel 3 configuration register */
#define DMAMUX_RM_CH4CFG                   REG32(DMAMUX + 0x10U)          /*!< DMAMUX request multiplexer channel 4 configuration register */
#define DMAMUX_RM_CH5CFG                   REG32(DMAMUX + 0x14U)          /*!< DMAMUX request multiplexer channel 5 configuration register */
#define DMAMUX_RM_CH6CFG                   REG32(DMAMUX + 0x18U)          /*!< DMAMUX request multiplexer channel 6 configuration register */
#define DMAMUX_RM_CH7CFG                   REG32(DMAMUX + 0x1CU)          /*!< DMAMUX request multiplexer channel 7 configuration register */
#define DMAMUX_RM_CH8CFG                   REG32(DMAMUX + 0x20U)          /*!< DMAMUX request multiplexer channel 8 configuration register */
#define DMAMUX_RM_CH9CFG                   REG32(DMAMUX + 0x24U)          /*!< DMAMUX request multiplexer channel 9 configuration register */
#define DMAMUX_RM_CH10CFG                  REG32(DMAMUX + 0x28U)          /*!< DMAMUX request multiplexer channel 10 configuration register */
#define DMAMUX_RM_CH11CFG                  REG32(DMAMUX + 0x2CU)          /*!< DMAMUX request multiplexer channel 11 configuration register */
#define DMAMUX_RM_CH12CFG                  REG32(DMAMUX + 0x30U)          /*!< DMAMUX request multiplexer channel 12 configuration register */
#define DMAMUX_RM_CH13CFG                  REG32(DMAMUX + 0x34U)          /*!< DMAMUX request multiplexer channel 13 configuration register */
#define DMAMUX_RM_CH14CFG                  REG32(DMAMUX + 0x38U)          /*!< DMAMUX request multiplexer channel 14 configuration register */
#define DMAMUX_RM_CH15CFG                  REG32(DMAMUX + 0x3CU)          /*!< DMAMUX request multiplexer channel 15 configuration register */
#define DMAMUX_RM_CH16CFG                  REG32(DMAMUX + 0x40U)          /*!< DMAMUX request multiplexer channel 16 configuration register */
#define DMAMUX_RM_CH17CFG                  REG32(DMAMUX + 0x44U)          /*!< DMAMUX request multiplexer channel 17 configuration register */
#define DMAMUX_RM_CH18CFG                  REG32(DMAMUX + 0x48U)          /*!< DMAMUX request multiplexer channel 18 configuration register */
#define DMAMUX_RM_CH19CFG                  REG32(DMAMUX + 0x4CU)          /*!< DMAMUX request multiplexer channel 19 configuration register */
#define DMAMUX_RM_CH20CFG                  REG32(DMAMUX + 0x50U)          /*!< DMAMUX request multiplexer channel 20 configuration register */
#define DMAMUX_RM_CH21CFG                  REG32(DMAMUX + 0x54U)          /*!< DMAMUX request multiplexer channel 21 configuration register */
#define DMAMUX_RM_CH22CFG                  REG32(DMAMUX + 0x58U)          /*!< DMAMUX request multiplexer channel 22 configuration register */
#define DMAMUX_RM_CH23CFG                  REG32(DMAMUX + 0x5CU)          /*!< DMAMUX request multiplexer channel 23 configuration register */
#define DMAMUX_RM_CH24CFG                  REG32(DMAMUX + 0x60U)          /*!< DMAMUX request multiplexer channel 24 configuration register */
#define DMAMUX_RM_CH25CFG                  REG32(DMAMUX + 0x64U)          /*!< DMAMUX request multiplexer channel 25 configuration register */
#define DMAMUX_RM_CH26CFG                  REG32(DMAMUX + 0x68U)          /*!< DMAMUX request multiplexer channel 26 configuration register */
#define DMAMUX_RM_CH27CFG                  REG32(DMAMUX + 0x6CU)          /*!< DMAMUX request multiplexer channel 27 configuration register */
#define DMAMUX_RM_CH28CFG                  REG32(DMAMUX + 0x70U)          /*!< DMAMUX request multiplexer channel 28 configuration register */
#define DMAMUX_RM_CH29CFG                  REG32(DMAMUX + 0x74U)          /*!< DMAMUX request multiplexer channel 29 configuration register */
#define DMAMUX_RM_CH30CFG                  REG32(DMAMUX + 0x78U)          /*!< DMAMUX request multiplexer channel 30 configuration register */
#define DMAMUX_RM_CH31CFG                  REG32(DMAMUX + 0x7CU)          /*!< DMAMUX request multiplexer channel 31 configuration register */
#define DMAMUX_RM_INTF                     REG32(DMAMUX + 0x80U)          /*!< DMAMUX request multiplexer channel interrupt flag register */
#define DMAMUX_RM_INTC                     REG32(DMAMUX + 0x84U)          /*!< DMAMUX request multiplexer channel interrupt flag clear register */
#define DMAMUX_RG_CH0CFG                   REG32(DMAMUX + 0x100U)         /*!< DMAMUX generator channel 0 configuration register */
#define DMAMUX_RG_CH1CFG                   REG32(DMAMUX + 0x104U)         /*!< DMAMUX generator channel 1 configuration register */
#define DMAMUX_RG_CH2CFG                   REG32(DMAMUX + 0x108U)         /*!< DMAMUX generator channel 2 configuration register */
#define DMAMUX_RG_CH3CFG                   REG32(DMAMUX + 0x10CU)         /*!< DMAMUX generator channel 3 configuration register */
#define DMAMUX_RG_CH4CFG                   REG32(DMAMUX + 0x110U)         /*!< DMAMUX generator channel 4 configuration register */
#define DMAMUX_RG_CH5CFG                   REG32(DMAMUX + 0x114U)         /*!< DMAMUX generator channel 5 configuration register */
#define DMAMUX_RG_CH6CFG                   REG32(DMAMUX + 0x118U)         /*!< DMAMUX generator channel 6 configuration register */
#define DMAMUX_RG_CH7CFG                   REG32(DMAMUX + 0x11CU)         /*!< DMAMUX generator channel 7 configuration register */
#define DMAMUX_RG_INTF                     REG32(DMAMUX + 0x140U)         /*!< DMAMUX generator channel interrupt flag register */
#define DMAMUX_RG_INTC                     REG32(DMAMUX + 0x144U)         /*!< DMAMUX rgenerator channel interrupt flag clear register */

/* bits definitions */
/* DMA_INTF */
#define DMA_INTF_FEEIF                     BIT(0)                         /*!< FIFO error and exception flag */
#define DMA_INTF_SDEIF                     BIT(2)                         /*!< single data mode exception flag */
#define DMA_INTF_TAEIF                     BIT(3)                         /*!< transfer access error flag */
#define DMA_INTF_HTFIF                     BIT(4)                         /*!< half transfer finish flag */
#define DMA_INTF_FTFIF                     BIT(5)                         /*!< full transger finish flag */

/* DMA_INTC */
#define DMA_INTC_FEEIFC                    BIT(0)                         /*!< clear FIFO error and exception flag */
#define DMA_INTC_SDEIFC                    BIT(2)                         /*!< clear single data mode exception flag */
#define DMA_INTC_TAEIFC                    BIT(3)                         /*!< clear single data mode exception flag */
#define DMA_INTC_HTFIFC                    BIT(4)                         /*!< clear half transfer finish flag */
#define DMA_INTC_FTFIFC                    BIT(5)                         /*!< clear full transger finish flag */

/* DMA_CHxCTL,x=0..15 */
#define DMA_CHXCTL_CHEN                    BIT(0)                         /*!< channel x enable */
#define DMA_CHXCTL_SDEIE                   BIT(1)                         /*!< enable bit for channel x single data mode exception interrupt */
#define DMA_CHXCTL_TAEIE                   BIT(2)                         /*!< enable bit for channel x tranfer access error interrupt */
#define DMA_CHXCTL_HTFIE                   BIT(3)                         /*!< enable bit for channel x half transfer finish interrupt */
#define DMA_CHXCTL_FTFIE                   BIT(4)                         /*!< enable bit for channel x full transfer finish interrupt */
#define DMA_CHXCTL_TFCS                    BIT(5)                         /*!< transfer flow controller select */
#define DMA_CHXCTL_TM                      BITS(6,7)                      /*!< transfer mode */
#define DMA_CHXCTL_CMEN                    BIT(8)                         /*!< circulation mode */
#define DMA_CHXCTL_PNAGA                   BIT(9)                         /*!< next address generation algorithm of peripheral */
#define DMA_CHXCTL_MNAGA                   BIT(10)                        /*!< next address generation algorithm of memory */
#define DMA_CHXCTL_PWIDTH                  BITS(11,12)                    /*!< transfer width of peipheral */
#define DMA_CHXCTL_MWIDTH                  BITS(13,14)                    /*!< transfer width of memory */
#define DMA_CHXCTL_PAIF                    BIT(15)                        /*!< peripheral address increment fixed */
#define DMA_CHXCTL_PRIO                    BITS(16,17)                    /*!< priority level */
#define DMA_CHXCTL_SBMEN                   BIT(18)                        /*!< switch-buffer mode enable */
#define DMA_CHXCTL_MBS                     BIT(19)                        /*!< memory buffer select */
#define DMA_CHXCTL_PBURST                  BITS(21,22)                    /*!< transfer burst type of peripheral */
#define DMA_CHXCTL_MBURST                  BITS(23,24)                    /*!< transfer burst type of memory */
#define DMA_CHXCTL_PCEN                    BIT(25)                        /*!< peripheral address circular enable */
#define DMA_CHXCTL_MCEN                    BIT(26)                        /*!< memory address circular enable */

/* DMA_CHxCNT,x=0..15 */
#define DMA_CHXCNT_CNT                     BITS(0,15)                     /*!< transfer counter */
#define DMA_CHXCNT_CCNTEN                  BIT(23)                        /*!< circular mode count enable */
#define DMA_CHXCNT_CCNT                    BITS(24,31)                    /*!< circular mode count */

/* DMA_CHxPADDR,x=0..15 */
#define DMA_CHXPADDR_PADDR                 BITS(0,31)                     /*!< peripheral base address */

/* DMA_CHxM0ADDR,x=0..15 */
#define DMA_CHXM0ADDR_M0ADDR               BITS(0,31)                     /*!< memory 0 base address */

/* DMA_CHxM1ADDR,x=0..15 */
#define DMA_CHXM1ADDR_M1ADDR               BITS(0,31)                     /*!< memory 1 base address */

/* DMA_CHxFCTL,x=0..15 */
#define DMA_CHXFCTL_FCCV                   BITS(0,1)                      /*!< FIFO counter critical value */
#define DMA_CHXFCTL_MDMEN                  BIT(2)                         /*!< multi-data mode enable */
#define DMA_CHXFCTL_FCNT                   BITS(3,5)                      /*!< FIFO counter */
#define DMA_CHXFCTL_FEEIE                  BIT(7)                         /*!< FIFO exception interrupt enable */

/* DMA_CHxCRCDATA, x=0..15 */
#define DMA_CHXPCRCDATA_CRC_PDATA           BITS(0,31)                    /*!< peripheral port data CRC */

/* DMA_CRCIDATA */
#define DMA_CRCIDATA_CRC_IDATA             BITS(0,31)                     /*!< configurable initial CRC data value */

/* DMA_PCRCCTL */
#define DMA_PCRCCTL_RST0                   BIT(0)                         /*!< peripheral data CRC register reset bit of channel 0 */
#define DMA_PCRCCTL_RST1                   BIT(1)                         /*!< peripheral data CRC register reset bit of channel 1 */
#define DMA_PCRCCTL_RST2                   BIT(2)                         /*!< peripheral data CRC register reset bit of channel 2 */
#define DMA_PCRCCTL_RST3                   BIT(3)                         /*!< peripheral data CRC register reset bit of channel 3 */
#define DMA_PCRCCTL_RST4                   BIT(4)                         /*!< peripheral data CRC register reset bit of channel 4 */
#define DMA_PCRCCTL_RST5                   BIT(5)                         /*!< peripheral data CRC register reset bit of channel 5 */
#define DMA_PCRCCTL_RST6                   BIT(6)                         /*!< peripheral data CRC register reset bit of channel 6 */
#define DMA_PCRCCTL_RST7                   BIT(7)                         /*!< peripheral data CRC register reset bit of channel 7 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_PCRCCTL_RST8                   BIT(8)                         /*!< peripheral data CRC register reset bit of channel 8 */
#define DMA_PCRCCTL_RST9                   BIT(9)                         /*!< peripheral data CRC register reset bit of channel 9 */
#define DMA_PCRCCTL_RST10                  BIT(10)                        /*!< peripheral data CRC register reset bit of channel 10 */
#define DMA_PCRCCTL_RST11                  BIT(11)                        /*!< peripheral data CRC register reset bit of channel 11 */
#define DMA_PCRCCTL_RST12                  BIT(12)                        /*!< peripheral data CRC register reset bit of channel 12 */
#define DMA_PCRCCTL_RST13                  BIT(13)                        /*!< peripheral data CRC register reset bit of channel 13 */
#define DMA_PCRCCTL_RST14                  BIT(14)                        /*!< peripheral data CRC register reset bit of channel 14 */
#define DMA_PCRCCTL_RST15                  BIT(15)                        /*!< peripheral data CRC register reset bit of channel 15 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* DMA_GCTL */
#define DMA_GCTL_LPRREN                    BIT(0)                         /*!< enable round-robin for channels with low software priority level */
#define DMA_GCTL_MPRREN                    BIT(1)                         /*!< enable round-robin for channels with medium software priority level */
#define DMA_GCTL_HPRREN                    BIT(2)                         /*!< enable round-robin for channels with high software priority level */
#define DMA_GCTL_UHPRREN                   BIT(3)                         /*!< enable round-robin for channels with ultra high software priority level */

/* DMA_CHxTOCR, x=0..15 */
#define DMA_CHXTOCTL_PEROID                BITS(0,20)                     /*!< timeout threshold value */
#define DMA_CHXTOCTL_CHTOEN                BIT(31)                        /*!< channel transfer timeout monitor enable */

/* DMA_TOIF */
#define DMA_TOINTF_TOIF0                   BIT(0)                          /*!< transfer timeout flag of channel 0 */
#define DMA_TOINTF_TOIF1                   BIT(1)                          /*!< transfer timeout flag of channel 1 */
#define DMA_TOINTF_TOIF2                   BIT(2)                          /*!< transfer timeout flag of channel 2 */
#define DMA_TOINTF_TOIF3                   BIT(3)                          /*!< transfer timeout flag of channel 3 */
#define DMA_TOINTF_TOIF4                   BIT(4)                          /*!< transfer timeout flag of channel 4 */
#define DMA_TOINTF_TOIF5                   BIT(5)                          /*!< transfer timeout flag of channel 5 */
#define DMA_TOINTF_TOIF6                   BIT(6)                          /*!< transfer timeout flag of channel 6 */
#define DMA_TOINTF_TOIF7                   BIT(7)                          /*!< transfer timeout flag of channel 7 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_TOINTF_TOIF8                   BIT(8)                          /*!< transfer timeout flag of channel 8 */
#define DMA_TOINTF_TOIF9                   BIT(9)                          /*!< transfer timeout flag of channel 9 */
#define DMA_TOINTF_TOIF10                  BIT(10)                         /*!< transfer timeout flag of channel 10 */
#define DMA_TOINTF_TOIF11                  BIT(11)                         /*!< transfer timeout flag of channel 11 */
#define DMA_TOINTF_TOIF12                  BIT(12)                         /*!< transfer timeout flag of channel 12 */
#define DMA_TOINTF_TOIF13                  BIT(13)                         /*!< transfer timeout flag of channel 13 */
#define DMA_TOINTF_TOIF14                  BIT(14)                         /*!< transfer timeout flag of channel 14 */
#define DMA_TOINTF_TOIF15                  BIT(15)                         /*!< transfer timeout flag of channel 15 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* DMA_TOIE */
#define DMA_TOINTEN_TOIE0                  BIT(0)                          /*!< transfer timeout interrupt enable bit of channel 0 */
#define DMA_TOINTEN_TOIE1                  BIT(1)                          /*!< transfer timeout interrupt enable bit of channel 1 */
#define DMA_TOINTEN_TOIE2                  BIT(2)                          /*!< transfer timeout interrupt enable bit of channel 2 */
#define DMA_TOINTEN_TOIE3                  BIT(3)                          /*!< transfer timeout interrupt enable bit of channel 3 */
#define DMA_TOINTEN_TOIE4                  BIT(4)                          /*!< transfer timeout interrupt enable bit of channel 4 */
#define DMA_TOINTEN_TOIE5                  BIT(5)                          /*!< transfer timeout interrupt enable bit of channel 5 */
#define DMA_TOINTEN_TOIE6                  BIT(6)                          /*!< transfer timeout interrupt enable bit of channel 6 */
#define DMA_TOINTEN_TOIE7                  BIT(7)                          /*!< transfer timeout interrupt enable bit of channel 7 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_TOINTEN_TOIE8                  BIT(8)                          /*!< transfer timeout interrupt enable bit of channel 8 */
#define DMA_TOINTEN_TOIE9                  BIT(9)                          /*!< transfer timeout interrupt enable bit of channel 9 */
#define DMA_TOINTEN_TOIE10                 BIT(10)                         /*!< transfer timeout interrupt enable bit of channel 10 */
#define DMA_TOINTEN_TOIE11                 BIT(11)                         /*!< transfer timeout interrupt enable bit of channel 11 */
#define DMA_TOINTEN_TOIE12                 BIT(12)                         /*!< transfer timeout interrupt enable bit of channel 12 */
#define DMA_TOINTEN_TOIE13                 BIT(13)                         /*!< transfer timeout interrupt enable bit of channel 13 */
#define DMA_TOINTEN_TOIE14                 BIT(14)                         /*!< transfer timeout interrupt enable bit of channel 14 */
#define DMA_TOINTEN_TOIE15                 BIT(15)                         /*!< transfer timeout interrupt enable bit of channel 15 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* DMA_TFIF */
#define DMA_TFINTF_TFIF0                   BIT(0)                          /*!< TMR fault flag of channel 0 */
#define DMA_TFINTF_TFIF1                   BIT(1)                          /*!< TMR fault flag of channel 1 */
#define DMA_TFINTF_TFIF2                   BIT(2)                          /*!< TMR fault flag of channel 2 */
#define DMA_TFINTF_TFIF3                   BIT(3)                          /*!< TMR fault flag of channel 3 */
#define DMA_TFINTF_TFIF4                   BIT(4)                          /*!< TMR fault flag of channel 4 */
#define DMA_TFINTF_TFIF5                   BIT(5)                          /*!< TMR fault flag of channel 5 */
#define DMA_TFINTF_TFIF6                   BIT(6)                          /*!< TMR fault flag of channel 6 */
#define DMA_TFINTF_TFIF7                   BIT(7)                          /*!< TMR fault flag of channel 7 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_TFINTF_TFIF8                   BIT(8)                          /*!< TMR fault flag of channel 8 */
#define DMA_TFINTF_TFIF9                   BIT(9)                          /*!< TMR fault flag of channel 9 */
#define DMA_TFINTF_TFIF10                  BIT(10)                         /*!< TMR fault flag of channel 10 */
#define DMA_TFINTF_TFIF11                  BIT(11)                         /*!< TMR fault flag of channel 11 */
#define DMA_TFINTF_TFIF12                  BIT(12)                         /*!< TMR fault flag of channel 12 */
#define DMA_TFINTF_TFIF13                  BIT(13)                         /*!< TMR fault flag of channel 13 */
#define DMA_TFINTF_TFIF14                  BIT(14)                         /*!< TMR fault flag of channel 14 */
#define DMA_TFINTF_TFIF15                  BIT(15)                         /*!< TMR fault flag of channel 15 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* DMA_TFIE */
#define DMA_TFINTEN_TFIE0                  BIT(0)                          /*!< TMR fault interrupt enable bit of channel 0 */
#define DMA_TFINTEN_TFIE1                  BIT(1)                          /*!< TMR fault interrupt enable bit of channel 1 */
#define DMA_TFINTEN_TFIE2                  BIT(2)                          /*!< TMR fault interrupt enable bit of channel 2 */
#define DMA_TFINTEN_TFIE3                  BIT(3)                          /*!< TMR fault interrupt enable bit of channel 3 */
#define DMA_TFINTEN_TFIE4                  BIT(4)                          /*!< TMR fault interrupt enable bit of channel 4 */
#define DMA_TFINTEN_TFIE5                  BIT(5)                          /*!< TMR fault interrupt enable bit of channel 5 */
#define DMA_TFINTEN_TFIE6                  BIT(6)                          /*!< TMR fault interrupt enable bit of channel 6 */
#define DMA_TFINTEN_TFIE7                  BIT(7)                          /*!< TMR fault interrupt enable bit of channel 7 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_TFINTEN_TFIE8                  BIT(8)                          /*!< TMR fault interrupt enable bit of channel 8 */
#define DMA_TFINTEN_TFIE9                  BIT(9)                          /*!< TMR fault interrupt enable bit of channel 9 */
#define DMA_TFINTEN_TFIE10                 BIT(10)                         /*!< TMR fault interrupt enable bit of channel 10 */
#define DMA_TFINTEN_TFIE11                 BIT(11)                         /*!< TMR fault interrupt enable bit of channel 11 */
#define DMA_TFINTEN_TFIE12                 BIT(12)                         /*!< TMR fault interrupt enable bit of channel 12 */
#define DMA_TFINTEN_TFIE13                 BIT(13)                         /*!< TMR fault interrupt enable bit of channel 13 */
#define DMA_TFINTEN_TFIE14                 BIT(14)                         /*!< TMR fault interrupt enable bit of channel 14 */
#define DMA_TFINTEN_TFIE15                 BIT(15)                         /*!< TMR fault interrupt enable bit of channel 15 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* DMA_CHxPCADDR, x=0..15 */
#define DMA_CHXPCADDR_PCADDR               BITS(0,31)                     /*!< peripheral port address pointing to the peripheral port data */

/* DMA_CHxMCADDR, x=0..15 */
#define DMA_CHXMCADDR_MCADDR               BITS(0,31)                     /*!< memory port address pointing to the memory port data */

/* DMAMUX_RM_CHxCFG,x=0..31 */
#define DMAMUX_RM_CHXCFG_MUXID             BITS(0,7)                     /*!< multiplexer input identification */
#define DMAMUX_RM_CHXCFG_SOIE              BIT(8)                        /*!< synchronization overrun interrupt enable */
#define DMAMUX_RM_CHXCFG_EVGEN             BIT(9)                        /*!< event generation enable */
#define DMAMUX_RM_CHXCFG_SYNCEN            BIT(16)                       /*!< synchronization enable */
#define DMAMUX_RM_CHXCFG_SYNCP             BITS(17,18)                   /*!< synchronization input polarity */
#define DMAMUX_RM_CHXCFG_NBR               BITS(19,23)                   /*!< number of DMA requests to forward */
#define DMAMUX_RM_CHXCFG_SYNCID            BITS(24,28)                   /*!< synchronization input identification */

/* DMAMUX_RM_INTF */
#define DMAMUX_RM_INTF_SOIF0               BIT(0)                        /*!< synchronization overrun event flag of request multiplexer channel 0 */
#define DMAMUX_RM_INTF_SOIF1               BIT(1)                        /*!< synchronization overrun event flag of request multiplexer channel 1 */
#define DMAMUX_RM_INTF_SOIF2               BIT(2)                        /*!< synchronization overrun event flag of request multiplexer channel 2 */
#define DMAMUX_RM_INTF_SOIF3               BIT(3)                        /*!< synchronization overrun event flag of request multiplexer channel 3 */
#define DMAMUX_RM_INTF_SOIF4               BIT(4)                        /*!< synchronization overrun event flag of request multiplexer channel 4 */
#define DMAMUX_RM_INTF_SOIF5               BIT(5)                        /*!< synchronization overrun event flag of request multiplexer channel 5 */
#define DMAMUX_RM_INTF_SOIF6               BIT(6)                        /*!< synchronization overrun event flag of request multiplexer channel 6 */
#define DMAMUX_RM_INTF_SOIF7               BIT(7)                        /*!< synchronization overrun event flag of request multiplexer channel 7 */
#define DMAMUX_RM_INTF_SOIF8               BIT(8)                        /*!< synchronization overrun event flag of request multiplexer channel 8 */
#define DMAMUX_RM_INTF_SOIF9               BIT(9)                        /*!< synchronization overrun event flag of request multiplexer channel 9 */
#define DMAMUX_RM_INTF_SOIF10              BIT(10)                       /*!< synchronization overrun event flag of request multiplexer channel 10 */
#define DMAMUX_RM_INTF_SOIF11              BIT(11)                       /*!< synchronization overrun event flag of request multiplexer channel 11 */
#define DMAMUX_RM_INTF_SOIF12              BIT(12)                       /*!< synchronization overrun event flag of request multiplexer channel 12 */
#define DMAMUX_RM_INTF_SOIF13              BIT(13)                       /*!< synchronization overrun event flag of request multiplexer channel 13 */
#define DMAMUX_RM_INTF_SOIF14              BIT(14)                       /*!< synchronization overrun event flag of request multiplexer channel 14 */
#define DMAMUX_RM_INTF_SOIF15              BIT(15)                       /*!< synchronization overrun event flag of request multiplexer channel 15 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMAMUX_RM_INTF_SOIF16              BIT(16)                       /*!< synchronization overrun event flag of request multiplexer channel 16 */
#define DMAMUX_RM_INTF_SOIF17              BIT(17)                       /*!< synchronization overrun event flag of request multiplexer channel 17 */
#define DMAMUX_RM_INTF_SOIF18              BIT(18)                       /*!< synchronization overrun event flag of request multiplexer channel 18 */
#define DMAMUX_RM_INTF_SOIF19              BIT(19)                       /*!< synchronization overrun event flag of request multiplexer channel 19 */
#define DMAMUX_RM_INTF_SOIF20              BIT(20)                       /*!< synchronization overrun event flag of request multiplexer channel 20 */
#define DMAMUX_RM_INTF_SOIF21              BIT(21)                       /*!< synchronization overrun event flag of request multiplexer channel 21 */
#define DMAMUX_RM_INTF_SOIF22              BIT(22)                       /*!< synchronization overrun event flag of request multiplexer channel 22 */
#define DMAMUX_RM_INTF_SOIF23              BIT(23)                       /*!< synchronization overrun event flag of request multiplexer channel 23 */
#define DMAMUX_RM_INTF_SOIF24              BIT(24)                       /*!< synchronization overrun event flag of request multiplexer channel 24 */
#define DMAMUX_RM_INTF_SOIF25              BIT(25)                       /*!< synchronization overrun event flag of request multiplexer channel 25 */
#define DMAMUX_RM_INTF_SOIF26              BIT(26)                       /*!< synchronization overrun event flag of request multiplexer channel 26 */
#define DMAMUX_RM_INTF_SOIF27              BIT(27)                       /*!< synchronization overrun event flag of request multiplexer channel 27 */
#define DMAMUX_RM_INTF_SOIF28              BIT(28)                       /*!< synchronization overrun event flag of request multiplexer channel 28 */
#define DMAMUX_RM_INTF_SOIF29              BIT(29)                       /*!< synchronization overrun event flag of request multiplexer channel 29 */
#define DMAMUX_RM_INTF_SOIF30              BIT(30)                       /*!< synchronization overrun event flag of request multiplexer channel 30 */
#define DMAMUX_RM_INTF_SOIF31              BIT(31)                       /*!< synchronization overrun event flag of request multiplexer channel 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* DMAMUX_RM_INTC */
#define DMAMUX_RM_INTC_SOIFC0              BIT(0)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 0 */
#define DMAMUX_RM_INTC_SOIFC1              BIT(1)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 1 */
#define DMAMUX_RM_INTC_SOIFC2              BIT(2)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 2 */
#define DMAMUX_RM_INTC_SOIFC3              BIT(3)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 3 */
#define DMAMUX_RM_INTC_SOIFC4              BIT(4)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 4 */
#define DMAMUX_RM_INTC_SOIFC5              BIT(5)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 5 */
#define DMAMUX_RM_INTC_SOIFC6              BIT(6)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 6 */
#define DMAMUX_RM_INTC_SOIFC7              BIT(7)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 7 */
#define DMAMUX_RM_INTC_SOIFC8              BIT(8)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 8 */
#define DMAMUX_RM_INTC_SOIFC9              BIT(9)                        /*!< clear bit for synchronization overrun event flag of request multiplexer channel 9 */
#define DMAMUX_RM_INTC_SOIFC10             BIT(10)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 10 */
#define DMAMUX_RM_INTC_SOIFC11             BIT(11)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 11 */
#define DMAMUX_RM_INTC_SOIFC12             BIT(12)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 12 */
#define DMAMUX_RM_INTC_SOIFC13             BIT(13)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 13 */
#define DMAMUX_RM_INTC_SOIFC14             BIT(14)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 14 */
#define DMAMUX_RM_INTC_SOIFC15             BIT(15)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 15 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMAMUX_RM_INTC_SOIFC16             BIT(16)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 16 */
#define DMAMUX_RM_INTC_SOIFC17             BIT(17)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 17 */
#define DMAMUX_RM_INTC_SOIFC18             BIT(18)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 18 */
#define DMAMUX_RM_INTC_SOIFC19             BIT(19)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 19 */
#define DMAMUX_RM_INTC_SOIFC20             BIT(20)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 20 */
#define DMAMUX_RM_INTC_SOIFC21             BIT(21)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 21 */
#define DMAMUX_RM_INTC_SOIFC22             BIT(22)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 22 */
#define DMAMUX_RM_INTC_SOIFC23             BIT(23)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 23 */
#define DMAMUX_RM_INTC_SOIFC24             BIT(24)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 24 */
#define DMAMUX_RM_INTC_SOIFC25             BIT(25)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 25 */
#define DMAMUX_RM_INTC_SOIFC26             BIT(26)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 26 */
#define DMAMUX_RM_INTC_SOIFC27             BIT(27)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 27 */
#define DMAMUX_RM_INTC_SOIFC28             BIT(28)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 28 */
#define DMAMUX_RM_INTC_SOIFC29             BIT(29)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 29 */
#define DMAMUX_RM_INTC_SOIFC30             BIT(30)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 30 */
#define DMAMUX_RM_INTC_SOIFC31             BIT(31)                       /*!< clear bit for synchronization overrun event flag of request multiplexer channel 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* DMAMUX_RG_CHxCFG,x=0..7 */
#define DMAMUX_RG_CHXCFG_TID               BITS(0,5)                     /*!< trigger input identification */
#define DMAMUX_RG_CHXCFG_TOIE              BIT(8)                        /*!< trigger overrun interrupt enable */
#define DMAMUX_RG_CHXCFG_RGEN              BIT(16)                       /*!< DMA request generator channel x enable */
#define DMAMUX_RG_CHXCFG_RGTP              BITS(17,18)                   /*!< DMA request generator trigger polarity */
#define DMAMUX_RG_CHXCFG_NBRG              BITS(19,23)                   /*!< number of DMA requests to be generated */

/* DMAMUX_RG_INTF */
#define DMAMUX_RG_INTF_TOIF0               BIT(0)                        /*!< trigger overrun event flag of request generator channel 0 */
#define DMAMUX_RG_INTF_TOIF1               BIT(1)                        /*!< trigger overrun event flag of request generator channel 1 */
#define DMAMUX_RG_INTF_TOIF2               BIT(2)                        /*!< trigger overrun event flag of request generator channel 2 */
#define DMAMUX_RG_INTF_TOIF3               BIT(3)                        /*!< trigger overrun event flag of request generator channel 3 */
#define DMAMUX_RG_INTF_TOIF4               BIT(4)                        /*!< trigger overrun event flag of request generator channel 4 */
#define DMAMUX_RG_INTF_TOIF5               BIT(5)                        /*!< trigger overrun event flag of request generator channel 5 */
#define DMAMUX_RG_INTF_TOIF6               BIT(6)                        /*!< trigger overrun event flag of request generator channel 6 */
#define DMAMUX_RG_INTF_TOIF7               BIT(7)                        /*!< trigger overrun event flag of request generator channel 7 */

/* DMAMUX_RG_INTC */
#define DMAMUX_RG_INTC_TOIFC0              BIT(0)                        /*!< clear bit for trigger overrun event flag of request generator channel 0 */
#define DMAMUX_RG_INTC_TOIFC1              BIT(1)                        /*!< clear bit for trigger overrun event flag of request generator channel 1 */
#define DMAMUX_RG_INTC_TOIFC2              BIT(2)                        /*!< clear bit for trigger overrun event flag of request generator channel 2 */
#define DMAMUX_RG_INTC_TOIFC3              BIT(3)                        /*!< clear bit for trigger overrun event flag of request generator channel 3 */
#define DMAMUX_RG_INTC_TOIFC4              BIT(4)                        /*!< clear bit for trigger overrun event flag of request generator channel 4 */
#define DMAMUX_RG_INTC_TOIFC5              BIT(5)                        /*!< clear bit for trigger overrun event flag of request generator channel 5 */
#define DMAMUX_RG_INTC_TOIFC6              BIT(6)                        /*!< clear bit for trigger overrun event flag of request generator channel 6 */
#define DMAMUX_RG_INTC_TOIFC7              BIT(7)                        /*!< clear bit for trigger overrun event flag of request generator channel 7 */

/* constants definitions */
/* define the DMAMUX bit position and its register index offset */
#define DMAMUX_REGIDX_BIT(regidx, bitpos) (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos))
#define DMAMUX_REG_VAL(offset)            (REG32(DMAMUX + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U)))
#define DMAMUX_BIT_POS(val)               ((uint32_t)((uint32_t)(val) & 0x1FU))
#define DMAMUX_REGIDX_BIT2(regidx, bitpos, regidx2, bitpos2)   (((uint32_t)(regidx2) << 22U) | (uint32_t)((bitpos2) << 16U) \
                                                                | (((uint32_t)(regidx) << 6U) | (uint32_t)(bitpos)))
#define DMAMUX_REG_VAL2(offset)            (REG32(DMAMUX + ((uint32_t)(offset) >> 22U)))
#define DMAMUX_BIT_POS2(val)               (((uint32_t)(val) & 0x001F0000U) >> 16U)
#define DMAMUX_REG_VAL3(offset)            (REG32(DMAMUX + (((uint32_t)(offset) & 0x0000FFFFU) >> 6U) + 0x4U))

/* register offset */
#define DMAMUX_RM_CH0CFG_REG_OFFSET       ((uint32_t)0x00000000U)                                                      /*!< DMAMUX_RM_CH0CFG register offset */
#define DMAMUX_RM_CH1CFG_REG_OFFSET       ((uint32_t)0x00000004U)                                                      /*!< DMAMUX_RM_CH1CFG register offset */
#define DMAMUX_RM_CH2CFG_REG_OFFSET       ((uint32_t)0x00000008U)                                                      /*!< DMAMUX_RM_CH2CFG register offset */
#define DMAMUX_RM_CH3CFG_REG_OFFSET       ((uint32_t)0x0000000CU)                                                      /*!< DMAMUX_RM_CH3CFG register offset */
#define DMAMUX_RM_CH4CFG_REG_OFFSET       ((uint32_t)0x00000010U)                                                      /*!< DMAMUX_RM_CH4CFG register offset */
#define DMAMUX_RM_CH5CFG_REG_OFFSET       ((uint32_t)0x00000014U)                                                      /*!< DMAMUX_RM_CH5CFG register offset */
#define DMAMUX_RM_CH6CFG_REG_OFFSET       ((uint32_t)0x00000018U)                                                      /*!< DMAMUX_RM_CH6CFG register offset */
#define DMAMUX_RM_CH7CFG_REG_OFFSET       ((uint32_t)0x0000001CU)                                                      /*!< DMAMUX_RM_CH7CFG register offset */
#define DMAMUX_RM_CH8CFG_REG_OFFSET       ((uint32_t)0x00000020U)                                                      /*!< DMAMUX_RM_CH8CFG register offset */
#define DMAMUX_RM_CH9CFG_REG_OFFSET       ((uint32_t)0x00000024U)                                                      /*!< DMAMUX_RM_CH9CFG register offset */
#define DMAMUX_RM_CH10CFG_REG_OFFSET      ((uint32_t)0x00000028U)                                                      /*!< DMAMUX_RM_CH10CFG register offset */
#define DMAMUX_RM_CH11CFG_REG_OFFSET      ((uint32_t)0x0000002CU)                                                      /*!< DMAMUX_RM_CH11CFG register offset */
#define DMAMUX_RM_CH12CFG_REG_OFFSET      ((uint32_t)0x00000030U)                                                      /*!< DMAMUX_RM_CH12CFG register offset */
#define DMAMUX_RM_CH13CFG_REG_OFFSET      ((uint32_t)0x00000034U)                                                      /*!< DMAMUX_RM_CH13CFG register offset */
#define DMAMUX_RM_CH14CFG_REG_OFFSET      ((uint32_t)0x00000038U)                                                      /*!< DMAMUX_RM_CH14CFG register offset */
#define DMAMUX_RM_CH15CFG_REG_OFFSET      ((uint32_t)0x0000003CU)                                                      /*!< DMAMUX_RM_CH15CFG register offset */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMAMUX_RM_CH16CFG_REG_OFFSET      ((uint32_t)0x00000040U)                                                      /*!< DMAMUX_RM_CH16CFG register offset */
#define DMAMUX_RM_CH17CFG_REG_OFFSET      ((uint32_t)0x00000044U)                                                      /*!< DMAMUX_RM_CH17CFG register offset */
#define DMAMUX_RM_CH18CFG_REG_OFFSET      ((uint32_t)0x00000048U)                                                      /*!< DMAMUX_RM_CH18CFG register offset */
#define DMAMUX_RM_CH19CFG_REG_OFFSET      ((uint32_t)0x0000004CU)                                                      /*!< DMAMUX_RM_CH19CFG register offset */
#define DMAMUX_RM_CH20CFG_REG_OFFSET      ((uint32_t)0x00000050U)                                                      /*!< DMAMUX_RM_CH20CFG register offset */
#define DMAMUX_RM_CH21CFG_REG_OFFSET      ((uint32_t)0x00000054U)                                                      /*!< DMAMUX_RM_CH21CFG register offset */
#define DMAMUX_RM_CH22CFG_REG_OFFSET      ((uint32_t)0x00000058U)                                                      /*!< DMAMUX_RM_CH22CFG register offset */
#define DMAMUX_RM_CH23CFG_REG_OFFSET      ((uint32_t)0x0000005CU)                                                      /*!< DMAMUX_RM_CH23CFG register offset */
#define DMAMUX_RM_CH24CFG_REG_OFFSET      ((uint32_t)0x00000060U)                                                      /*!< DMAMUX_RM_CH24CFG register offset */
#define DMAMUX_RM_CH25CFG_REG_OFFSET      ((uint32_t)0x00000064U)                                                      /*!< DMAMUX_RM_CH25CFG register offset */
#define DMAMUX_RM_CH26CFG_REG_OFFSET      ((uint32_t)0x00000068U)                                                      /*!< DMAMUX_RM_CH26CFG register offset */
#define DMAMUX_RM_CH27CFG_REG_OFFSET      ((uint32_t)0x0000006CU)                                                      /*!< DMAMUX_RM_CH27CFG register offset */
#define DMAMUX_RM_CH28CFG_REG_OFFSET      ((uint32_t)0x00000070U)                                                      /*!< DMAMUX_RM_CH28CFG register offset */
#define DMAMUX_RM_CH29CFG_REG_OFFSET      ((uint32_t)0x00000074U)                                                      /*!< DMAMUX_RM_CH29CFG register offset */
#define DMAMUX_RM_CH30CFG_REG_OFFSET      ((uint32_t)0x00000078U)                                                      /*!< DMAMUX_RM_CH30CFG register offset */
#define DMAMUX_RM_CH31CFG_REG_OFFSET      ((uint32_t)0x0000007CU)                                                      /*!< DMAMUX_RM_CH31CFG register offset */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMAMUX_RG_CH0CFG_REG_OFFSET       ((uint32_t)0x00000100U)                                                      /*!< DMAMUX_RG_CH0CFG register offset */
#define DMAMUX_RG_CH1CFG_REG_OFFSET       ((uint32_t)0x00000104U)                                                      /*!< DMAMUX_RG_CH1CFG register offset */
#define DMAMUX_RG_CH2CFG_REG_OFFSET       ((uint32_t)0x00000108U)                                                      /*!< DMAMUX_RG_CH2CFG register offset */
#define DMAMUX_RG_CH3CFG_REG_OFFSET       ((uint32_t)0x0000010CU)                                                      /*!< DMAMUX_RG_CH3CFG register offset */
#define DMAMUX_RG_CH4CFG_REG_OFFSET       ((uint32_t)0x00000110U)                                                      /*!< DMAMUX_RG_CH0CFG register offset */
#define DMAMUX_RG_CH5CFG_REG_OFFSET       ((uint32_t)0x00000114U)                                                      /*!< DMAMUX_RG_CH1CFG register offset */
#define DMAMUX_RG_CH6CFG_REG_OFFSET       ((uint32_t)0x00000118U)                                                      /*!< DMAMUX_RG_CH2CFG register offset */
#define DMAMUX_RG_CH7CFG_REG_OFFSET       ((uint32_t)0x0000011CU)                                                      /*!< DMAMUX_RG_CH3CFG register offset */
#define DMAMUX_RM_INTF_REG_OFFSET         ((uint32_t)0x00000080U)                                                      /*!< DMAMUX_RM_INTF register offset */
#define DMAMUX_RG_INTF_REG_OFFSET         ((uint32_t)0x00000140U)                                                      /*!< DMAMUX_RG_INTF register offset */

/* DMA multi data mode initialize struct */
typedef struct {
    uint32_t request;                                                                                                  /*!< channel input identification */
    uint32_t periph_addr;                                                                                              /*!< peripheral base address */
    uint32_t periph_width;                                                                                             /*!< transfer data size of peripheral */
    uint32_t periph_inc;                                                                                               /*!< peripheral increasing mode */
    uint32_t memory0_addr;                                                                                             /*!< memory 0 base address */
    uint32_t memory_width;                                                                                             /*!< transfer data size of memory */
    uint32_t memory_inc;                                                                                               /*!< memory increasing mode */
    uint32_t memory_burst_width;                                                                                       /*!< memory burst width */
    uint32_t periph_burst_width;                                                                                       /*!< periph burst width */
    uint32_t critical_value;                                                                                           /*!< FIFO critical */
    uint32_t periph_addr_circular;                                                                                     /*!< periph address circular mode */
    uint32_t memory_addr_circular;                                                                                     /*!< memory address circular mode */
    uint32_t direction;                                                                                                /*!< channel data transfer direction */
    uint32_t number;                                                                                                   /*!< channel transfer number */
    uint32_t priority;                                                                                                 /*!< channel priority level */
} dma_multi_data_parameter_struct;

/* DMA single data mode initialize struct */
typedef struct {
    uint32_t request;                                                                                                  /*!< channel input identification */
    uint32_t periph_addr;                                                                                              /*!< peripheral base address */
    uint32_t periph_inc;                                                                                               /*!< peripheral increasing mode */
    uint32_t memory0_addr;                                                                                             /*!< memory 0 base address */
    uint32_t memory_inc;                                                                                               /*!< memory increasing mode */
    uint32_t periph_memory_width;                                                                                      /*!< transfer data size of peripheral */
    uint32_t periph_addr_circular;                                                                                     /*!< periph address circular mode */
    uint32_t memory_addr_circular;                                                                                     /*!< memory address circular mode */
    uint32_t direction;                                                                                                /*!< channel data transfer direction */
    uint32_t number;                                                                                                   /*!< channel transfer number */
    uint32_t priority;                                                                                                 /*!< channel priority level */
} dma_single_data_parameter_struct;

/* DMAMUX request multiplexer synchronization configuration structure */
typedef struct {
    uint32_t sync_id;                                                                                                  /*!< synchronization input identification */
    uint32_t sync_polarity;                                                                                            /*!< synchronization input polarity */
    uint32_t request_number;                                                                                           /*!< number of DMA requests to forward */
} dmamux_sync_parameter_struct;

/* DMAMUX request generator trigger configuration structure */
typedef struct {
    uint32_t trigger_id;                                                                                               /*!< trigger input identification */
    uint32_t trigger_polarity;                                                                                         /*!< DMAMUX request generator trigger polarity */
    uint32_t request_number;                                                                                           /*!< number of DMA requests to be generated */
} dmamux_gen_parameter_struct;

/* DMA channel select */
typedef enum {
    DMA_CH0 = 0U,                                                                                                      /*!< DMA channel 0 */
    DMA_CH1,                                                                                                           /*!< DMA channel 1 */
    DMA_CH2,                                                                                                           /*!< DMA channel 2 */
    DMA_CH3,                                                                                                           /*!< DMA channel 3 */
    DMA_CH4,                                                                                                           /*!< DMA channel 4 */
    DMA_CH5,                                                                                                           /*!< DMA channel 5 */
    DMA_CH6,                                                                                                           /*!< DMA channel 6 */
    DMA_CH7,                                                                                                           /*!< DMA channel 7 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    DMA_CH8,                                                                                                           /*!< DMA channel 8 */
    DMA_CH9,                                                                                                           /*!< DMA channel 9 */
    DMA_CH10,                                                                                                          /*!< DMA channel 10 */
    DMA_CH11,                                                                                                          /*!< DMA channel 11 */
    DMA_CH12,                                                                                                          /*!< DMA channel 12 */
    DMA_CH13,                                                                                                          /*!< DMA channel 13 */
    DMA_CH14,                                                                                                          /*!< DMA channel 14 */
    DMA_CH15                                                                                                           /*!< DMA channel 15 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
} dma_channel_enum;

/* DMAMUX request multiplexer channel */
typedef enum {
    DMAMUX_MUXCH0 = 0U,                                                                                                /*!< DMAMUX request multiplexer channel 0 */
    DMAMUX_MUXCH1,                                                                                                     /*!< DMAMUX request multiplexer channel 1 */
    DMAMUX_MUXCH2,                                                                                                     /*!< DMAMUX request multiplexer channel 2 */
    DMAMUX_MUXCH3,                                                                                                     /*!< DMAMUX request multiplexer channel 3 */
    DMAMUX_MUXCH4,                                                                                                     /*!< DMAMUX request multiplexer channel 4 */
    DMAMUX_MUXCH5,                                                                                                     /*!< DMAMUX request multiplexer channel 5 */
    DMAMUX_MUXCH6,                                                                                                     /*!< DMAMUX request multiplexer channel 6 */
    DMAMUX_MUXCH7,                                                                                                     /*!< DMAMUX request multiplexer channel 7 */
    DMAMUX_MUXCH8,                                                                                                     /*!< DMAMUX request multiplexer channel 8 */
    DMAMUX_MUXCH9,                                                                                                     /*!< DMAMUX request multiplexer channel 9 */
    DMAMUX_MUXCH10,                                                                                                    /*!< DMAMUX request multiplexer channel 10 */
    DMAMUX_MUXCH11,                                                                                                    /*!< DMAMUX request multiplexer channel 11 */
    DMAMUX_MUXCH12,                                                                                                    /*!< DMAMUX request multiplexer channel 12 */
    DMAMUX_MUXCH13,                                                                                                    /*!< DMAMUX request multiplexer channel 13 */
    DMAMUX_MUXCH14,                                                                                                    /*!< DMAMUX request multiplexer channel 14 */
    DMAMUX_MUXCH15,                                                                                                    /*!< DMAMUX request multiplexer channel 15 */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    DMAMUX_MUXCH16,                                                                                                    /*!< DMAMUX request multiplexer channel 16 */
    DMAMUX_MUXCH17,                                                                                                    /*!< DMAMUX request multiplexer channel 17 */
    DMAMUX_MUXCH18,                                                                                                    /*!< DMAMUX request multiplexer channel 18 */
    DMAMUX_MUXCH19,                                                                                                    /*!< DMAMUX request multiplexer channel 19 */
    DMAMUX_MUXCH20,                                                                                                    /*!< DMAMUX request multiplexer channel 20 */
    DMAMUX_MUXCH21,                                                                                                    /*!< DMAMUX request multiplexer channel 21 */
    DMAMUX_MUXCH22,                                                                                                    /*!< DMAMUX request multiplexer channel 22 */
    DMAMUX_MUXCH23,                                                                                                    /*!< DMAMUX request multiplexer channel 23 */
    DMAMUX_MUXCH24,                                                                                                    /*!< DMAMUX request multiplexer channel 24 */
    DMAMUX_MUXCH25,                                                                                                    /*!< DMAMUX request multiplexer channel 25 */
    DMAMUX_MUXCH26,                                                                                                    /*!< DMAMUX request multiplexer channel 26 */
    DMAMUX_MUXCH27,                                                                                                    /*!< DMAMUX request multiplexer channel 27 */
    DMAMUX_MUXCH28,                                                                                                    /*!< DMAMUX request multiplexer channel 28 */
    DMAMUX_MUXCH29,                                                                                                    /*!< DMAMUX request multiplexer channel 29 */
    DMAMUX_MUXCH30,                                                                                                    /*!< DMAMUX request multiplexer channel 30 */
    DMAMUX_MUXCH31                                                                                                     /*!< DMAMUX request multiplexer channel 31 */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
} dmamux_multiplexer_channel_enum;

/* DMAMUX request generator channel */
typedef enum {
    DMAMUX_GENCH0 = 0U,                                                                                                /*!< DMAMUX request generator channel 0 */
    DMAMUX_GENCH1,                                                                                                     /*!< DMAMUX request generator channel 1 */
    DMAMUX_GENCH2,                                                                                                     /*!< DMAMUX request generator channel 2 */
    DMAMUX_GENCH3,                                                                                                     /*!< DMAMUX request generator channel 3 */
    DMAMUX_GENCH4,                                                                                                     /*!< DMAMUX request generator channel 4 */
    DMAMUX_GENCH5,                                                                                                     /*!< DMAMUX request generator channel 5 */
    DMAMUX_GENCH6,                                                                                                     /*!< DMAMUX request generator channel 6 */
    DMAMUX_GENCH7                                                                                                      /*!< DMAMUX request generator channel 7 */
} dmamux_generator_channel_enum;

/* DMAMUX interrupt enable or disable */
typedef enum {
    /* interrupts in CHxCFG register */
    DMAMUX_INT_MUXCH0_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH0CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH1_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH1CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH2_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH2CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH3_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH3CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH4_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH4CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH5_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH5CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH6_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH6CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH7_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH7CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 7 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH8_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH8CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 8 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH9_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH9CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request multiplexer channel 9 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH10_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH10CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 10 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH11_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH11CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 11 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH12_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH12CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 12 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH13_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH13CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 13 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH14_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH14CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 14 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH15_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH15CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 15 synchronization overrun interrupt */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    DMAMUX_INT_MUXCH16_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH16CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 16 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH17_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH17CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 17 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH18_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH18CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 18 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH19_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH19CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 19 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH20_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH20CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 20 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH21_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH21CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 21 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH22_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH22CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 22 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH23_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH23CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 23 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH24_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH24CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 24 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH25_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH25CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 25 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH26_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH26CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 26 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH27_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH27CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 27 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH28_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH28CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 28 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH29_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH29CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 29 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH30_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH30CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 30 synchronization overrun interrupt */
    DMAMUX_INT_MUXCH31_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_CH31CFG_REG_OFFSET, 8U),                                       /*!< DMAMUX request multiplexer channel 31 synchronization overrun interrupt */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    DMAMUX_INT_GENCH0_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH0CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 0 trigger overrun interrupt */
    DMAMUX_INT_GENCH1_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH1CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 1 trigger overrun interrupt */
    DMAMUX_INT_GENCH2_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH2CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 2 trigger overrun interrupt */
    DMAMUX_INT_GENCH3_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH3CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 3 trigger overrun interrupt */
    DMAMUX_INT_GENCH4_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH4CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 4 trigger overrun interrupt */
    DMAMUX_INT_GENCH5_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH5CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 5 trigger overrun interrupt */
    DMAMUX_INT_GENCH6_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH6CFG_REG_OFFSET, 8U),                                        /*!< DMAMUX request generator channel 6 trigger overrun interrupt */
    DMAMUX_INT_GENCH7_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_CH7CFG_REG_OFFSET, 8U)                                         /*!< DMAMUX request generator channel 7 trigger overrun interrupt */
} dmamux_interrupt_enum;

/* DMAMUX flags */
typedef enum {
    /* flags in INTF register */
    DMAMUX_FLAG_MUXCH0_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 0U),                                         /*!< DMAMUX request multiplexer channel 0 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH1_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 1U),                                         /*!< DMAMUX request multiplexer channel 1 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH2_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 2U),                                         /*!< DMAMUX request multiplexer channel 2 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH3_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 3U),                                         /*!< DMAMUX request multiplexer channel 3 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH4_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 4U),                                         /*!< DMAMUX request multiplexer channel 4 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH5_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 5U),                                         /*!< DMAMUX request multiplexer channel 5 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH6_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 6U),                                         /*!< DMAMUX request multiplexer channel 6 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH7_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 7U),                                         /*!< DMAMUX request multiplexer channel 7 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH8_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 8U),                                         /*!< DMAMUX request multiplexer channel 8 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH9_SO  = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 9U),                                         /*!< DMAMUX request multiplexer channel 9 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH10_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 10U),                                        /*!< DMAMUX request multiplexer channel 10 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH11_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 11U),                                        /*!< DMAMUX request multiplexer channel 11 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH12_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 12U),                                        /*!< DMAMUX request multiplexer channel 12 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH13_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 13U),                                        /*!< DMAMUX request multiplexer channel 13 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH14_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 14U),                                        /*!< DMAMUX request multiplexer channel 14 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH15_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 15U),                                        /*!< DMAMUX request multiplexer channel 15 synchronization overrun flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    DMAMUX_FLAG_MUXCH16_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 16U),                                        /*!< DMAMUX request multiplexer channel 16 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH17_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 17U),                                        /*!< DMAMUX request multiplexer channel 17 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH18_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 18U),                                        /*!< DMAMUX request multiplexer channel 18 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH19_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 19U),                                        /*!< DMAMUX request multiplexer channel 19 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH20_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 20U),                                        /*!< DMAMUX request multiplexer channel 20 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH21_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 21U),                                        /*!< DMAMUX request multiplexer channel 21 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH22_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 22U),                                        /*!< DMAMUX request multiplexer channel 22 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH23_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 23U),                                        /*!< DMAMUX request multiplexer channel 23 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH24_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 24U),                                        /*!< DMAMUX request multiplexer channel 24 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH25_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 25U),                                        /*!< DMAMUX request multiplexer channel 25 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH26_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 26U),                                        /*!< DMAMUX request multiplexer channel 26 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH27_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 27U),                                        /*!< DMAMUX request multiplexer channel 27 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH28_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 28U),                                        /*!< DMAMUX request multiplexer channel 28 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH29_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 29U),                                        /*!< DMAMUX request multiplexer channel 29 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH30_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 30U),                                        /*!< DMAMUX request multiplexer channel 30 synchronization overrun flag */
    DMAMUX_FLAG_MUXCH31_SO = DMAMUX_REGIDX_BIT(DMAMUX_RM_INTF_REG_OFFSET, 31U),                                        /*!< DMAMUX request multiplexer channel 31 synchronization overrun flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    DMAMUX_FLAG_GENCH0_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 0U),                                         /*!< DMAMUX request generator channel 0 trigger overrun flag */
    DMAMUX_FLAG_GENCH1_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 1U),                                         /*!< DMAMUX request generator channel 1 trigger overrun flag */
    DMAMUX_FLAG_GENCH2_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 2U),                                         /*!< DMAMUX request generator channel 2 trigger overrun flag */
    DMAMUX_FLAG_GENCH3_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 3U),                                         /*!< DMAMUX request generator channel 3 trigger overrun flag */
    DMAMUX_FLAG_GENCH4_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 4U),                                         /*!< DMAMUX request generator channel 4 trigger overrun flag */
    DMAMUX_FLAG_GENCH5_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 5U),                                         /*!< DMAMUX request generator channel 5 trigger overrun flag */
    DMAMUX_FLAG_GENCH6_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 6U),                                         /*!< DMAMUX request generator channel 6 trigger overrun flag */
    DMAMUX_FLAG_GENCH7_TO  = DMAMUX_REGIDX_BIT(DMAMUX_RG_INTF_REG_OFFSET, 7U)                                          /*!< DMAMUX request generator channel 7 trigger overrun flag */
} dmamux_flag_enum;

/* DMAMUX interrupt flags */
typedef enum {
    /* interrupt flags in INTF register */
    DMAMUX_INT_FLAG_MUXCH0_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 0U, DMAMUX_RM_CH0CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 0 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH1_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 1U, DMAMUX_RM_CH1CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 1 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH2_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 2U, DMAMUX_RM_CH2CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 2 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH3_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 3U, DMAMUX_RM_CH3CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 3 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH4_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 4U, DMAMUX_RM_CH4CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 4 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH5_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 5U, DMAMUX_RM_CH5CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 5 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH6_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 6U, DMAMUX_RM_CH6CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 6 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH7_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 7U, DMAMUX_RM_CH7CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 7 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH8_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 8U, DMAMUX_RM_CH8CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 8 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH9_SO  = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 9U, DMAMUX_RM_CH9CFG_REG_OFFSET, 8U),   /*!< DMAMUX request multiplexer channel 9 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH10_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 10U, DMAMUX_RM_CH10CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 10 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH11_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 11U, DMAMUX_RM_CH11CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 11 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH12_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 12U, DMAMUX_RM_CH12CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 12 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH13_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 13U, DMAMUX_RM_CH13CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 13 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH14_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 14U, DMAMUX_RM_CH14CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 14 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH15_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 15U, DMAMUX_RM_CH15CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 15 synchronization overrun interrupt flag */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
    DMAMUX_INT_FLAG_MUXCH16_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 16U, DMAMUX_RM_CH16CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 16 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH17_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 17U, DMAMUX_RM_CH17CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 17 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH18_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 18U, DMAMUX_RM_CH18CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 18 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH19_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 19U, DMAMUX_RM_CH19CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 19 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH20_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 20U, DMAMUX_RM_CH20CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 20 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH21_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 21U, DMAMUX_RM_CH21CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 21 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH22_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 22U, DMAMUX_RM_CH22CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 22 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH23_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 23U, DMAMUX_RM_CH23CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 23 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH24_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 24U, DMAMUX_RM_CH24CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 24 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH25_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 25U, DMAMUX_RM_CH25CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 25 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH26_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 26U, DMAMUX_RM_CH26CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 26 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH27_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 27U, DMAMUX_RM_CH27CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 27 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH28_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 28U, DMAMUX_RM_CH28CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 28 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH29_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 29U, DMAMUX_RM_CH29CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 29 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH30_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 30U, DMAMUX_RM_CH30CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 30 synchronization overrun interrupt flag */
    DMAMUX_INT_FLAG_MUXCH31_SO = DMAMUX_REGIDX_BIT2(DMAMUX_RM_INTF_REG_OFFSET, 31U, DMAMUX_RM_CH31CFG_REG_OFFSET, 8U), /*!< DMAMUX request multiplexer channel 31 synchronization overrun interrupt flag */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
    DMAMUX_INT_FLAG_GENCH0_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 0U, DMAMUX_RG_CH0CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 0 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH1_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 1U, DMAMUX_RG_CH1CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 1 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH2_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 2U, DMAMUX_RG_CH2CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 2 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH3_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 3U, DMAMUX_RG_CH3CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 3 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH4_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 4U, DMAMUX_RG_CH4CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 4 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH5_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 5U, DMAMUX_RG_CH5CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 5 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH6_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 6U, DMAMUX_RG_CH6CFG_REG_OFFSET, 8U),   /*!< DMAMUX request generator channel 6 trigger overrun interrupt flag */
    DMAMUX_INT_FLAG_GENCH7_TO  = DMAMUX_REGIDX_BIT2(DMAMUX_RG_INTF_REG_OFFSET, 7U, DMAMUX_RG_CH7CFG_REG_OFFSET, 8U)    /*!< DMAMUX request generator channel 7 trigger overrun interrupt flag */
} dmamux_interrupt_flag_enum;

/* DMA channel flag shift */
#define DMA_FLAG_ADD(flag,channel)        ((uint32_t)((flag) << ((((uint32_t)((uint32_t)(channel) & 0x03U) * 6U)) + ((uint32_t)(((uint32_t)(channel) & 0x03U) >> 1U) & 0x01U) * 4U)))

/* DMA_register address */
#define DMA_CHCTL(dma,channel)            REG32(((dma) + 0x20U) + 0x18U * (uint32_t)(channel))                                   /*!< DMA channel CHXCTL register  */
#define DMA_CHCNT(dma,channel)            REG32(((dma) + 0x24U) + 0x18U * (uint32_t)(channel))                                   /*!< DMA channel CHXCNT register */
#define DMA_CHPADDR(dma,channel)          REG32(((dma) + 0x28U) + 0x18U * (uint32_t)(channel))                                   /*!< DMA channel CHXPADDR register */
#define DMA_CHM0ADDR(dma,channel)         REG32(((dma) + 0x2CU) + 0x18U * (uint32_t)(channel))                                   /*!< DMA channel CHXM0ADDR register */
#define DMA_CHM1ADDR(dma,channel)         REG32(((dma) + 0x30U) + 0x18U * (uint32_t)(channel))                                   /*!< DMA channel CHXM1ADDR register */
#define DMA_CHFCTL(dma,channel)           REG32(((dma) + 0x34U) + 0x18U * (uint32_t)(channel))                                   /*!< DMA channel CHXMADDR register */
#define DMA_CHPCRCDATA(dma,channel)       REG32(((dma) + 0x200U) + 0x04U * (uint32_t)(channel))                                  /*!< DMA channel CHXPCRCDATA register */
#define DMA_CHTOCTL(dma,channel)          REG32(((dma) + 0x300U) + 0x04U * (uint32_t)(channel))                                  /*!< DMA channel CHXTOCTL register */
#define DMA_CHPCADDR(dma,channel)         REG32(((dma) + 0x350U) + 0x04U * (uint32_t)(channel))                                  /*!< DMA channel CHXPCADDR register */
#define DMA_CHMCADDR(dma,channel)         REG32(((dma) + 0x390U) + 0x04U * (uint32_t)(channel))                                  /*!< DMA channel CHXMCADDR register */

/* DMAMUX_RM_CHxCFG base address */
#define DMAMUX_RM_CHXCFG_BASE             (DMAMUX)                                                                     /*!< the base address of DMAMUX request multiplexer channel CHxCFG register */

/* DMAMUX request multiplexer channel shift bit */
#define DMAMUX_RM_CHXCFG(channel)         REG32(DMAMUX_RM_CHXCFG_BASE + 0x04U * (uint32_t)(channel))                   /*!< the address of DMAMUX request multiplexer channel CHxCFG register */

/* DMAMUX_RG_CHxCFG base address */
#define DMAMUX_RG_CHXCFG_BASE             (DMAMUX + 0x100U)                                                            /*!< the base address of DMAMUX channel request generator CHxCFG register */

/* DMAMUX request generator channel shift bit */
#define DMAMUX_RG_CHXCFG(channel)         REG32(DMAMUX_RG_CHXCFG_BASE + 0x04U * (uint32_t)(channel))                   /*!< the address of DMAMUX channel request generator CHxCFG register */

/* burst type of memory */
#define CHCTL_MBURST(regval)              (BITS(23,24) & ((uint32_t)(regval) << 23U))
#define DMA_MEMORY_BURST_SINGLE           CHCTL_MBURST(0)                                                              /*!< single burst */
#define DMA_MEMORY_BURST_4_BEAT           CHCTL_MBURST(1)                                                              /*!< 4-beat burst */
#define DMA_MEMORY_BURST_8_BEAT           CHCTL_MBURST(2)                                                              /*!< 8-beat burst */
#define DMA_MEMORY_BURST_16_BEAT          CHCTL_MBURST(3)                                                              /*!< 16-beat burst */

/* burst type of peripheral */
#define CHCTL_PBURST(regval)              (BITS(21,22) & ((uint32_t)(regval) << 21U))
#define DMA_PERIPH_BURST_SINGLE           CHCTL_PBURST(0)                                                              /*!< single burst */
#define DMA_PERIPH_BURST_4_BEAT           CHCTL_PBURST(1)                                                              /*!< 4-beat burst */
#define DMA_PERIPH_BURST_8_BEAT           CHCTL_PBURST(2)                                                              /*!< 8-beat burst */
#define DMA_PERIPH_BURST_16_BEAT          CHCTL_PBURST(3)                                                              /*!< 16-beat burst */

/* channel priority level */
#define CHCTL_PRIO(regval)                (BITS(16,17) & ((uint32_t)(regval) << 16U))
#define DMA_PRIORITY_LOW                  CHCTL_PRIO(0)                                                                /*!< low priority */
#define DMA_PRIORITY_MEDIUM               CHCTL_PRIO(1)                                                                /*!< medium priority */
#define DMA_PRIORITY_HIGH                 CHCTL_PRIO(2)                                                                /*!< high priority */
#define DMA_PRIORITY_ULTRA_HIGH           CHCTL_PRIO(3)                                                                /*!< ultra high priority */

/* transfer data width of memory */
#define CHCTL_MWIDTH(regval)              (BITS(13,14) & ((uint32_t)(regval) << 13U))
#define DMA_MEMORY_WIDTH_8BIT             CHCTL_MWIDTH(0)                                                              /*!< transfer data width of memory is 8-bit */
#define DMA_MEMORY_WIDTH_16BIT            CHCTL_MWIDTH(1)                                                              /*!< transfer data width of memory is 16-bit */
#define DMA_MEMORY_WIDTH_32BIT            CHCTL_MWIDTH(2)                                                              /*!< transfer data width of memory is 32-bit */
#define DMA_MEMORY_WIDTH_64BIT            CHCTL_MWIDTH(3)                                                              /*!< transfer data width of memory is 64-bit */

/* transfer data width of peripheral */
#define CHCTL_PWIDTH(regval)              (BITS(11,12) & ((uint32_t)(regval) << 11U))
#define DMA_PERIPH_WIDTH_8BIT             CHCTL_PWIDTH(0)                                                              /*!< transfer data width of peripheral is 8-bit */
#define DMA_PERIPH_WIDTH_16BIT            CHCTL_PWIDTH(1)                                                              /*!< transfer data width of peripheral is 16-bit */
#define DMA_PERIPH_WIDTH_32BIT            CHCTL_PWIDTH(2)                                                              /*!< transfer data width of peripheral is 32-bit */
#define DMA_PERIPH_WIDTH_64BIT            CHCTL_PWIDTH(3)                                                              /*!< transfer data width of peripheral is 64-bit */

/* channel transfer mode */
#define CHCTL_TM(regval)                  (BITS(6,7) & ((uint32_t)(regval) << 6U))
#define DMA_PERIPH_TO_MEMORY              CHCTL_TM(0)                                                                  /*!< read from peripheral and write to memory */
#define DMA_MEMORY_TO_PERIPH              CHCTL_TM(1)                                                                  /*!< read from memory and write to peripheral */
#define DMA_MEMORY_TO_MEMORY              CHCTL_TM(2)                                                                  /*!< read from memory and write to memory */

/* FIFO counter critical value */
#define CHFCTL_FCCV(regval)               (BITS(0,1) & ((uint32_t)(regval) << 0U))
#define DMA_FIFO_2_WORD                   CHFCTL_FCCV(0)                                                               /*!< critical value two words */
#define DMA_FIFO_4_WORD                   CHFCTL_FCCV(1)                                                               /*!< critical value four words */
#define DMA_FIFO_6_WORD                   CHFCTL_FCCV(2)                                                               /*!< critical value six words */
#define DMA_FIFO_8_WORD                   CHFCTL_FCCV(3)                                                               /*!< critical value four words */

/* FIFO counter */
#define DMA_FIFO_CNT_0_2_DATA             ((uint32_t)0x00000000U)                                                      /*!< 0 - 2 words */
#define DMA_FIFO_CNT_2_4_WORD             ((uint32_t)0x00000001U)                                                      /*!< 2 - 4 words */
#define DMA_FIFO_CNT_4_6_WORD             ((uint32_t)0x00000002U)                                                      /*!< 4 - 6 words */
#define DMA_FIFO_CNT_6_8_WORD             ((uint32_t)0x00000003U)                                                      /*!< 6 - 8 words */
#define DMA_FIFO_CNT_EMPTY                ((uint32_t)0x00000004U)                                                      /*!< empty */
#define DMA_FIFO_CNT_FULL                 ((uint32_t)0x00000005U)                                                      /*!< full */

/* memory select */
#define DMA_MEMORY_0                      ((uint32_t)0x00000000U)                                                      /*!< select memory 0 */
#define DMA_MEMORY_1                      ((uint32_t)0x00000001U)                                                      /*!< select memory 1 */

/* DMA periph address circular mod */
#define DMA_PERIPH_ADDR_CIRCULAR_ENABLE    ((uint32_t)0x00000000U)                                                     /*!< periph address circular mode enable */
#define DMA_PERIPH_ADDR_CIRCULAR_DISABLE   ((uint32_t)0x00000001U)                                                     /*!< periph address circular mode disable */

/* DMA memory address circular mod */
#define DMA_MEMORY_ADDR_CIRCULAR_ENABLE    ((uint32_t)0x00000000U)                                                     /*!< memory address circular mode enable */
#define DMA_MEMORY_ADDR_CIRCULAR_DISABLE   ((uint32_t)0x00000001U)                                                     /*!< memory address circular mode disable */

/* DMA flow controller select */
#define DMA_FLOW_CONTROLLER_DMA           ((uint32_t)0x00000000U)                                                      /*!< DMA is the flow controler */
#define DMA_FLOW_CONTROLLER_PERI          ((uint32_t)0x00000001U)                                                      /*!< peripheral is the flow controler */

/* peripheral increasing mode */
#define DMA_PERIPH_INCREASE_ENABLE        ((uint32_t)0x00000000U)                                                      /*!< next address of peripheral is increasing address mode */
#define DMA_PERIPH_INCREASE_DISABLE       ((uint32_t)0x00000001U)                                                      /*!< next address of peripheral is fixed address mode */
#define DMA_PERIPH_INCREASE_FIX           ((uint32_t)0x00000002U)                                                      /*!< next address of peripheral is increasing fixed */

/* memory increasing mode */
#define DMA_MEMORY_INCREASE_ENABLE        ((uint32_t)0x00000000U)                                                      /*!< next address of memory is increasing address mode */
#define DMA_MEMORY_INCREASE_DISABLE       ((uint32_t)0x00000001U)                                                      /*!< next address of memory is fixed address mode */

/* FIFO status */
#define DMA_FIFO_STATUS_NODATA            ((uint32_t)0x00000000U)                                                      /*!< the data in the FIFO less than 2 word */
#define DMA_FIFO_STATUS_2_WORD            ((uint32_t)0x00000001U)                                                      /*!< the data in the FIFO more than 2 word, less than 4 words */
#define DMA_FIFO_STATUS_4_WORD            ((uint32_t)0x00000002U)                                                      /*!< the data in the FIFO more than 4 word, less than 6 words */
#define DMA_FIFO_STATUS_6_WORD            ((uint32_t)0x00000003U)                                                      /*!< the data in the FIFO more than 6 word, less than 8 words */
#define DMA_FIFO_STATUS_EMPTY             ((uint32_t)0x00000004U)                                                      /*!< the data in the FIFO is empty */
#define DMA_FIFO_STATUS_FULL              ((uint32_t)0x00000005U)                                                      /*!< the data in the FIFO is full */

/* DMA reset value */
#define DMA_CHCTL_RESET_VALUE             ((uint32_t)0x06000000U)                                                      /*!< the reset value of DMA channel CHXCTL register */
#define DMA_CHCNT_RESET_VALUE             ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXCNT register */
#define DMA_CHPADDR_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXPADDR register */
#define DMA_CHMADDR_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXMADDR register */
#define DMA_CHINTF_RESET_VALUE            ((uint32_t)0x0000003DU)                                                      /*!< clear DMA channel CHXINTFS register */
#define DMA_CHFCTL_RESET_VALUE            ((uint32_t)0x00000021U)                                                      /*!< the reset value of DMA channel CHXFCTL register */
#define DMA_CHPCRCDATA_RESET_VALUE        ((uint32_t)0xFFFFFFFFU)                                                      /*!< the reset value of DMA channel CHXPCRCDATA register */
#define DMA_CHTOCTL_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXTOCTL register */
#define DMA_CHPCADDR_RESET_VALUE          ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXPCADDR register */
#define DMA_CHMCADDR_RESET_VALUE          ((uint32_t)0x00000000U)                                                      /*!< the reset value of DMA channel CHXMCADDR register */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_TOINTF_RESET_VALUE            ((uint32_t)0x0000FFFFU)                                                      /*!< the reset value of timeout interrupt flag register */
#define DMA_TOINTEN_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of timeout interrupt enable register */
#define DMA_TFINTF_RESET_VALUE            ((uint32_t)0x0000FFFFU)                                                      /*!< the reset value of TMR fault interrupt flag register */
#define DMA_TFINTEN_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of TMR fault interrupt enable register */
#else
#define DMA_TOINTF_RESET_VALUE            ((uint32_t)0x000000FFU)                                                      /*!< the reset value of timeout interrupt flag register */
#define DMA_TOINTEN_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of timeout interrupt enable register */
#define DMA_TFINTF_RESET_VALUE            ((uint32_t)0x000000FFU)                                                      /*!< the reset value of TMR fault interrupt flag register */
#define DMA_TFINTEN_RESET_VALUE           ((uint32_t)0x00000000U)                                                      /*!< the reset value of TMR fault interrupt enable register */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */

/* DMA_INTF register */
/* interrupt flag bits */
#define DMA_INT_FLAG_FEE                  DMA_INTF_FEEIF                                                               /*!< FIFO error and exception flag */
#define DMA_INT_FLAG_SDE                  DMA_INTF_SDEIF                                                               /*!< single data mode exception flag */
#define DMA_INT_FLAG_TAE                  DMA_INTF_TAEIF                                                               /*!< transfer access error flag */
#define DMA_INT_FLAG_HTF                  DMA_INTF_HTFIF                                                               /*!< half transfer finish flag */
#define DMA_INT_FLAG_FTF                  DMA_INTF_FTFIF                                                               /*!< full transfer finish flag */
#define DMA_INT_FLAG_TIMEOUT              BIT(30)                                                                      /*!< transfer timeout flag */
#define DMA_INT_FLAG_TMR_FAULT            BIT(31)                                                                      /*!< control register TMR fault flag */

/* flag bits */
#define DMA_FLAG_FEE                      DMA_INTF_FEEIF                                                               /*!< FIFO error and exception flag */
#define DMA_FLAG_SDE                      DMA_INTF_SDEIF                                                               /*!< single data mode exception flag */
#define DMA_FLAG_TAE                      DMA_INTF_TAEIF                                                               /*!< transfer access error flag */
#define DMA_FLAG_HTF                      DMA_INTF_HTFIF                                                               /*!< half transfer finish flag */
#define DMA_FLAG_FTF                      DMA_INTF_FTFIF                                                               /*!< full transfer finish flag */
#define DMA_FLAG_TIMEOUT                  BIT(30)                                                                      /*!< transfer timeout flag */
#define DMA_FLAG_TMR_FAULT                BIT(31)                                                                      /*!< control register TMR fault flag */

/*timeout interrupt bits*/
#define DMA_TOINTEN_TOIE                  BIT(30)                                                                      /*!< transfer timeout interrupt enable */
#define DMA_TFINTEN_TFIE                  BIT(31)                                                                      /*!< control register TMR fault interrupt enable */

/* DMA interrupt */
#define DMA_INT_SDE                       DMA_CHXCTL_SDEIE                                                             /*!< single data mode exception interrupt */
#define DMA_INT_TAE                       DMA_CHXCTL_TAEIE                                                             /*!< tranfer access error interrupt */
#define DMA_INT_HTF                       DMA_CHXCTL_HTFIE                                                             /*!< half transfer finish interrupt */
#define DMA_INT_FTF                       DMA_CHXCTL_FTFIE                                                             /*!< full transfer finish interrupt */
#define DMA_INT_FEE                       DMA_CHXFCTL_FEEIE                                                            /*!< FIFO exception interrupt */
#define DMA_INT_TIMEOUT                   DMA_TOINTEN_TOIE                                                             /*!< transfer timeout interrupt */
#define DMA_INT_TMR                       DMA_TFINTEN_TFIE                                                             /*!< TMR fault interrupt */

/* DMAMUX request multiplexer channel input identification */
#define RM_CHXCFG_MUXID(regval)           (BITS(0,7) & ((uint32_t)(regval) << 0U))                                     /*!< multiplexer input identification */
#define DMA_REQUEST_M2M                   RM_CHXCFG_MUXID(0U)                                                          /*!< memory to memory transfer */
#define DMA_REQUEST_GENERATOR0            RM_CHXCFG_MUXID(1U)                                                          /*!< DMAMUX request generator 0 */
#define DMA_REQUEST_GENERATOR1            RM_CHXCFG_MUXID(2U)                                                          /*!< DMAMUX request generator 1 */
#define DMA_REQUEST_GENERATOR2            RM_CHXCFG_MUXID(3U)                                                          /*!< DMAMUX request generator 2 */
#define DMA_REQUEST_GENERATOR3            RM_CHXCFG_MUXID(4U)                                                          /*!< DMAMUX request generator 3 */
#define DMA_REQUEST_GENERATOR4            RM_CHXCFG_MUXID(5U)                                                          /*!< DMAMUX request generator 4 */
#define DMA_REQUEST_GENERATOR5            RM_CHXCFG_MUXID(6U)                                                          /*!< DMAMUX request generator 5 */
#define DMA_REQUEST_GENERATOR6            RM_CHXCFG_MUXID(7U)                                                          /*!< DMAMUX request generator 6 */
#define DMA_REQUEST_GENERATOR7            RM_CHXCFG_MUXID(8U)                                                          /*!< DMAMUX request generator 7 */
#define DMA_REQUEST_DAC0                  RM_CHXCFG_MUXID(12U)                                                         /*!< DMAMUX DAC0 request */
#define DMA_REQUEST_DAC1                  RM_CHXCFG_MUXID(13U)                                                         /*!< DMAMUX DAC1 request */
#define DMA_REQUEST_TIMER5_UP0            RM_CHXCFG_MUXID(14U)                                                         /*!< DMAMUX TIMER5 UP0 request */
#define DMA_REQUEST_TIMER6_UP0            RM_CHXCFG_MUXID(15U)                                                         /*!< DMAMUX TIMER6 UP0 request */
#define DMA_REQUEST_SPI0_RX               RM_CHXCFG_MUXID(16U)                                                         /*!< DMAMUX SPI0 RX request */
#define DMA_REQUEST_SPI0_TX               RM_CHXCFG_MUXID(17U)                                                         /*!< DMAMUX SPI0 TX request */
#define DMA_REQUEST_SPI1_RX               RM_CHXCFG_MUXID(18U)                                                         /*!< DMAMUX SPI1 RX request */
#define DMA_REQUEST_SPI1_TX               RM_CHXCFG_MUXID(19U)                                                         /*!< DMAMUX SPI1 TX request */
#define DMA_REQUEST_SPI2_RX               RM_CHXCFG_MUXID(20U)                                                         /*!< DMAMUX SPI2 RX request */
#define DMA_REQUEST_SPI2_TX               RM_CHXCFG_MUXID(21U)                                                         /*!< DMAMUX SPI2 TX request */
#define DMA_REQUEST_SPI3_RX               RM_CHXCFG_MUXID(22U)                                                         /*!< DMAMUX SPI3 RX request */
#define DMA_REQUEST_SPI3_TX               RM_CHXCFG_MUXID(23U)                                                         /*!< DMAMUX SPI3 TX request */
#define DMA_REQUEST_SPI4_I2S_RX           RM_CHXCFG_MUXID(24U)                                                         /*!< DMAMUX SPI4 I2S RX request */
#define DMA_REQUEST_SPI4_I2S_TX           RM_CHXCFG_MUXID(25U)                                                         /*!< DMAMUX SPI4 I2S TX request */
#define DMA_REQUEST_SPI5_I2S_RX           RM_CHXCFG_MUXID(26U)                                                         /*!< DMAMUX SPI5 I2S RX request */
#define DMA_REQUEST_SPI5_I2S_TX           RM_CHXCFG_MUXID(27U)                                                         /*!< DMAMUX SPI5 I2S TX request */
#define DMA_REQUEST_I2C0_RX               RM_CHXCFG_MUXID(28U)                                                         /*!< DMAMUX I2C0 RX request */
#define DMA_REQUEST_I2C0_TX               RM_CHXCFG_MUXID(29U)                                                         /*!< DMAMUX I2C0 TX request */
#define DMA_REQUEST_I2C1_RX               RM_CHXCFG_MUXID(30U)                                                         /*!< DMAMUX I2C1 RX request */
#define DMA_REQUEST_I2C1_TX               RM_CHXCFG_MUXID(31U)                                                         /*!< DMAMUX I2C1 TX request */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_REQUEST_SPI6_I2S_RX           RM_CHXCFG_MUXID(32U)                                                         /*!< DMAMUX SPI6 I2S RX request */
#define DMA_REQUEST_SPI6_I2S_TX           RM_CHXCFG_MUXID(33U)                                                         /*!< DMAMUX SPI6 I2S TX request */
#define DMA_REQUEST_SPI7_I2S_RX           RM_CHXCFG_MUXID(34U)                                                         /*!< DMAMUX SPI7 I2S RX request */
#define DMA_REQUEST_SPI7_I2S_TX           RM_CHXCFG_MUXID(35U)                                                         /*!< DMAMUX SPI7 I2S TX request */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMA_REQUEST_LINFLEXD0_RX          RM_CHXCFG_MUXID(48U)                                                         /*!< DMAMUX LINFLEXD0 RX request */
#define DMA_REQUEST_LINFLEXD0_TX          RM_CHXCFG_MUXID(49U)                                                         /*!< DMAMUX LINFLEXD0 TX request */
#define DMA_REQUEST_LINFLEXD1_RX          RM_CHXCFG_MUXID(50U)                                                         /*!< DMAMUX LINFLEXD1 RX request */
#define DMA_REQUEST_LINFLEXD1_TX          RM_CHXCFG_MUXID(51U)                                                         /*!< DMAMUX LINFLEXD1 TX request */
#define DMA_REQUEST_LINFLEXD2_RX          RM_CHXCFG_MUXID(52U)                                                         /*!< DMAMUX LINFLEXD2 RX request */
#define DMA_REQUEST_LINFLEXD2_TX          RM_CHXCFG_MUXID(53U)                                                         /*!< DMAMUX LINFLEXD2 TX request */
#define DMA_REQUEST_LINFLEXD3_RX          RM_CHXCFG_MUXID(54U)                                                         /*!< DMAMUX LINFLEXD3 RX request */
#define DMA_REQUEST_LINFLEXD3_TX          RM_CHXCFG_MUXID(55U)                                                         /*!< DMAMUX LINFLEXD3 TX request */
#define DMA_REQUEST_LINFLEXD4_RX          RM_CHXCFG_MUXID(56U)                                                         /*!< DMAMUX LINFLEXD4 RX request */
#define DMA_REQUEST_LINFLEXD4_TX          RM_CHXCFG_MUXID(57U)                                                         /*!< DMAMUX LINFLEXD4 TX request */
#define DMA_REQUEST_LINFLEXD5_RX          RM_CHXCFG_MUXID(58U)                                                         /*!< DMAMUX LINFLEXD5 RX request */
#define DMA_REQUEST_LINFLEXD5_TX          RM_CHXCFG_MUXID(59U)                                                         /*!< DMAMUX LINFLEXD5 TX request */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_REQUEST_LINFLEXD6_RX          RM_CHXCFG_MUXID(60U)                                                         /*!< DMAMUX LINFLEXD6 RX request */
#define DMA_REQUEST_LINFLEXD6_TX          RM_CHXCFG_MUXID(61U)                                                         /*!< DMAMUX LINFLEXD6 TX request */
#define DMA_REQUEST_LINFLEXD7_RX          RM_CHXCFG_MUXID(62U)                                                         /*!< DMAMUX LINFLEXD7 RX request */
#define DMA_REQUEST_LINFLEXD7_TX          RM_CHXCFG_MUXID(63U)                                                         /*!< DMAMUX LINFLEXD7 TX request */
#define DMA_REQUEST_LINFLEXD8_RX          RM_CHXCFG_MUXID(64U)                                                         /*!< DMAMUX LINFLEXD8 RX request */
#define DMA_REQUEST_LINFLEXD8_TX          RM_CHXCFG_MUXID(65U)                                                         /*!< DMAMUX LINFLEXD8 TX request */
#define DMA_REQUEST_LINFLEXD9_RX          RM_CHXCFG_MUXID(66U)                                                         /*!< DMAMUX LINFLEXD9 RX request */
#define DMA_REQUEST_LINFLEXD9_TX          RM_CHXCFG_MUXID(67U)                                                         /*!< DMAMUX LINFLEXD9 TX request */
#define DMA_REQUEST_LINFLEXD10_RX         RM_CHXCFG_MUXID(68U)                                                         /*!< DMAMUX LINFLEXD10 RX request */
#define DMA_REQUEST_LINFLEXD10_TX         RM_CHXCFG_MUXID(69U)                                                         /*!< DMAMUX LINFLEXD10 TX request */
#define DMA_REQUEST_LINFLEXD11_RX         RM_CHXCFG_MUXID(70U)                                                         /*!< DMAMUX LINFLEXD11 RX request */
#define DMA_REQUEST_LINFLEXD11_TX         RM_CHXCFG_MUXID(71U)                                                         /*!< DMAMUX LINFLEXD11 TX request */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMA_REQUEST_TIMER0_CH0            RM_CHXCFG_MUXID(72U)                                                         /*!< DMAMUX TIMER0 CH0 request */
#define DMA_REQUEST_TIMER0_CH1            RM_CHXCFG_MUXID(73U)                                                         /*!< DMAMUX TIMER0 CH1 request */
#define DMA_REQUEST_TIMER0_CH2            RM_CHXCFG_MUXID(74U)                                                         /*!< DMAMUX TIMER0 CH2 request */
#define DMA_REQUEST_TIMER0_CH3            RM_CHXCFG_MUXID(75U)                                                         /*!< DMAMUX TIMER0 CH3 request */
#define DMA_REQUEST_TIMER0_CH0N           RM_CHXCFG_MUXID(76U)                                                         /*!< DMAMUX TIMER0 CH0N request */
#define DMA_REQUEST_TIMER0_CH1N           RM_CHXCFG_MUXID(77U)                                                         /*!< DMAMUX TIMER0 CH1N request */
#define DMA_REQUEST_TIMER0_CH2N           RM_CHXCFG_MUXID(78U)                                                         /*!< DMAMUX TIMER0 CH2N request */
#define DMA_REQUEST_TIMER0_CH3N           RM_CHXCFG_MUXID(79U)                                                         /*!< DMAMUX TIMER0 CH3N request */
#define DMA_REQUEST_TIMER0_UP             RM_CHXCFG_MUXID(80U)                                                         /*!< DMAMUX TIMER0 UP request */
#define DMA_REQUEST_TIMER0_TRG            RM_CHXCFG_MUXID(81U)                                                         /*!< DMAMUX TIMER0 TRG request */
#define DMA_REQUEST_TIMER0_CMT            RM_CHXCFG_MUXID(82U)                                                         /*!< DMAMUX TIMER0 CMT request */
#define DMA_REQUEST_TIMER7_CH0            RM_CHXCFG_MUXID(83U)                                                         /*!< DMAMUX TIMER7 CH0 request */
#define DMA_REQUEST_TIMER7_CH1            RM_CHXCFG_MUXID(84U)                                                         /*!< DMAMUX TIMER7 CH1 request */
#define DMA_REQUEST_TIMER7_CH2            RM_CHXCFG_MUXID(85U)                                                         /*!< DMAMUX TIMER7 CH2 request */
#define DMA_REQUEST_TIMER7_CH3            RM_CHXCFG_MUXID(86U)                                                         /*!< DMAMUX TIMER7 CH3 request */
#define DMA_REQUEST_TIMER7_CH0N           RM_CHXCFG_MUXID(87U)                                                         /*!< DMAMUX TIMER7 CH0N request */
#define DMA_REQUEST_TIMER7_CH1N           RM_CHXCFG_MUXID(88U)                                                         /*!< DMAMUX TIMER7 CH1N request */
#define DMA_REQUEST_TIMER7_CH2N           RM_CHXCFG_MUXID(89U)                                                         /*!< DMAMUX TIMER7 CH2N request */
#define DMA_REQUEST_TIMER7_CH3N           RM_CHXCFG_MUXID(90U)                                                         /*!< DMAMUX TIMER7 CH3N request */
#define DMA_REQUEST_TIMER7_UP             RM_CHXCFG_MUXID(91U)                                                         /*!< DMAMUX TIMER7 UP request */
#define DMA_REQUEST_TIMER7_TRG            RM_CHXCFG_MUXID(92U)                                                         /*!< DMAMUX TIMER7 TRG request */
#define DMA_REQUEST_TIMER7_CMT            RM_CHXCFG_MUXID(93U)                                                         /*!< DMAMUX TIMER7 CMT request */
#define DMA_REQUEST_TIMER19_CH0           RM_CHXCFG_MUXID(94U)                                                         /*!< DMAMUX TIMER19 CH0 request */
#define DMA_REQUEST_TIMER19_CH1           RM_CHXCFG_MUXID(95U)                                                         /*!< DMAMUX TIMER19 CH1 request */
#define DMA_REQUEST_TIMER19_CH2           RM_CHXCFG_MUXID(96U)                                                         /*!< DMAMUX TIMER19 CH2 request */
#define DMA_REQUEST_TIMER19_CH3           RM_CHXCFG_MUXID(97U)                                                         /*!< DMAMUX TIMER19 CH3 request */
#define DMA_REQUEST_TIMER19_CH0N          RM_CHXCFG_MUXID(98U)                                                         /*!< DMAMUX TIMER19 CH0N request */
#define DMA_REQUEST_TIMER19_CH1N          RM_CHXCFG_MUXID(99U)                                                         /*!< DMAMUX TIMER19 CH1N request */
#define DMA_REQUEST_TIMER19_CH2N          RM_CHXCFG_MUXID(100U)                                                        /*!< DMAMUX TIMER19 CH2N request */
#define DMA_REQUEST_TIMER19_CH3N          RM_CHXCFG_MUXID(101U)                                                        /*!< DMAMUX TIMER19 CH3N request */
#define DMA_REQUEST_TIMER19_UP            RM_CHXCFG_MUXID(102U)                                                        /*!< DMAMUX TIMER19 UP request */
#define DMA_REQUEST_TIMER19_TRG           RM_CHXCFG_MUXID(103U)                                                        /*!< DMAMUX TIMER19 TRG request */
#define DMA_REQUEST_TIMER19_CMT           RM_CHXCFG_MUXID(104U)                                                        /*!< DMAMUX TIMER19 CMT request */
#define DMA_REQUEST_TIMER20_CH0           RM_CHXCFG_MUXID(105U)                                                        /*!< DMAMUX TIMER20 CH0 request */
#define DMA_REQUEST_TIMER20_CH1           RM_CHXCFG_MUXID(106U)                                                        /*!< DMAMUX TIMER20 CH1 request */
#define DMA_REQUEST_TIMER20_CH2           RM_CHXCFG_MUXID(107U)                                                        /*!< DMAMUX TIMER20 CH2 request */
#define DMA_REQUEST_TIMER20_CH3           RM_CHXCFG_MUXID(108U)                                                        /*!< DMAMUX TIMER20 CH3 request */
#define DMA_REQUEST_TIMER20_CH0N          RM_CHXCFG_MUXID(109U)                                                        /*!< DMAMUX TIMER20 CH0N request */
#define DMA_REQUEST_TIMER20_CH1N          RM_CHXCFG_MUXID(110U)                                                        /*!< DMAMUX TIMER20 CH1N request */
#define DMA_REQUEST_TIMER20_CH2N          RM_CHXCFG_MUXID(111U)                                                        /*!< DMAMUX TIMER20 CH2N request */
#define DMA_REQUEST_TIMER20_CH3N          RM_CHXCFG_MUXID(112U)                                                        /*!< DMAMUX TIMER20 CH3N request */
#define DMA_REQUEST_TIMER20_UP            RM_CHXCFG_MUXID(113U)                                                        /*!< DMAMUX TIMER20 UP request */
#define DMA_REQUEST_TIMER20_TRG           RM_CHXCFG_MUXID(114U)                                                        /*!< DMAMUX TIMER20 TRG request */
#define DMA_REQUEST_TIMER20_CMT           RM_CHXCFG_MUXID(115U)                                                        /*!< DMAMUX TIMER20 CMT request */
#define DMA_REQUEST_TIMER60_CH0           RM_CHXCFG_MUXID(116U)                                                        /*!< DMAMUX TIMER60 CH0 request */
#define DMA_REQUEST_TIMER60_CH1           RM_CHXCFG_MUXID(117U)                                                        /*!< DMAMUX TIMER60 CH1 request */
#define DMA_REQUEST_TIMER60_CH2           RM_CHXCFG_MUXID(118U)                                                        /*!< DMAMUX TIMER60 CH2 request */
#define DMA_REQUEST_TIMER60_CH3           RM_CHXCFG_MUXID(119U)                                                        /*!< DMAMUX TIMER60 CH3 request */
#define DMA_REQUEST_TIMER60_CH0N          RM_CHXCFG_MUXID(120U)                                                        /*!< DMAMUX TIMER60 CH0N request */
#define DMA_REQUEST_TIMER60_CH1N          RM_CHXCFG_MUXID(121U)                                                        /*!< DMAMUX TIMER60 CH1N request */
#define DMA_REQUEST_TIMER60_CH2N          RM_CHXCFG_MUXID(122U)                                                        /*!< DMAMUX TIMER60 CH2N request */
#define DMA_REQUEST_TIMER60_CH3N          RM_CHXCFG_MUXID(123U)                                                        /*!< DMAMUX TIMER60 CH3N request */
#define DMA_REQUEST_TIMER60_UP            RM_CHXCFG_MUXID(124U)                                                        /*!< DMAMUX TIMER60 UP request */
#define DMA_REQUEST_TIMER60_TRG           RM_CHXCFG_MUXID(125U)                                                        /*!< DMAMUX TIMER60 TRG request */
#define DMA_REQUEST_TIMER60_CMT           RM_CHXCFG_MUXID(126U)                                                        /*!< DMAMUX TIMER60 CMT request */
#define DMA_REQUEST_TIMER61_CH0           RM_CHXCFG_MUXID(127U)                                                        /*!< DMAMUX TIMER61 CH0 request */
#define DMA_REQUEST_TIMER61_CH1           RM_CHXCFG_MUXID(128U)                                                        /*!< DMAMUX TIMER61 CH1 request */
#define DMA_REQUEST_TIMER61_CH2           RM_CHXCFG_MUXID(129U)                                                        /*!< DMAMUX TIMER61 CH2 request */
#define DMA_REQUEST_TIMER61_CH3           RM_CHXCFG_MUXID(130U)                                                        /*!< DMAMUX TIMER61 CH3 request */
#define DMA_REQUEST_TIMER61_CH0N          RM_CHXCFG_MUXID(131U)                                                        /*!< DMAMUX TIMER61 CH0N request */
#define DMA_REQUEST_TIMER61_CH1N          RM_CHXCFG_MUXID(132U)                                                        /*!< DMAMUX TIMER61 CH1N request */
#define DMA_REQUEST_TIMER61_CH2N          RM_CHXCFG_MUXID(133U)                                                        /*!< DMAMUX TIMER61 CH2N request */
#define DMA_REQUEST_TIMER61_CH3N          RM_CHXCFG_MUXID(134U)                                                        /*!< DMAMUX TIMER61 CH3N request */
#define DMA_REQUEST_TIMER61_UP            RM_CHXCFG_MUXID(135U)                                                        /*!< DMAMUX TIMER61 UP request */
#define DMA_REQUEST_TIMER61_TRG           RM_CHXCFG_MUXID(136U)                                                        /*!< DMAMUX TIMER61 TRG request */
#define DMA_REQUEST_TIMER61_CMT           RM_CHXCFG_MUXID(137U)                                                        /*!< DMAMUX TIMER61 CMT request */
#define DMA_REQUEST_TIMER62_CH0           RM_CHXCFG_MUXID(138U)                                                        /*!< DMAMUX TIMER62 CH0 request */
#define DMA_REQUEST_TIMER62_CH1           RM_CHXCFG_MUXID(139U)                                                        /*!< DMAMUX TIMER62 CH1 request */
#define DMA_REQUEST_TIMER62_CH2           RM_CHXCFG_MUXID(140U)                                                        /*!< DMAMUX TIMER62 CH2 request */
#define DMA_REQUEST_TIMER62_CH3           RM_CHXCFG_MUXID(141U)                                                        /*!< DMAMUX TIMER62 CH3 request */
#define DMA_REQUEST_TIMER62_CH0N          RM_CHXCFG_MUXID(142U)                                                        /*!< DMAMUX TIMER62 CH0N request */
#define DMA_REQUEST_TIMER62_CH1N          RM_CHXCFG_MUXID(143U)                                                        /*!< DMAMUX TIMER62 CH1N request */
#define DMA_REQUEST_TIMER62_CH2N          RM_CHXCFG_MUXID(144U)                                                        /*!< DMAMUX TIMER62 CH2N request */
#define DMA_REQUEST_TIMER62_CH3N          RM_CHXCFG_MUXID(145U)                                                        /*!< DMAMUX TIMER62 CH3N request */
#define DMA_REQUEST_TIMER62_UP            RM_CHXCFG_MUXID(146U)                                                        /*!< DMAMUX TIMER62 UP request */
#define DMA_REQUEST_TIMER62_TRG           RM_CHXCFG_MUXID(147U)                                                        /*!< DMAMUX TIMER62 TRG request */
#define DMA_REQUEST_TIMER62_CMT           RM_CHXCFG_MUXID(148U)                                                        /*!< DMAMUX TIMER62 CMT request */
#define DMA_REQUEST_TIMER63_CH0           RM_CHXCFG_MUXID(149U)                                                        /*!< DMAMUX TIMER63 CH0 request */
#define DMA_REQUEST_TIMER63_CH1           RM_CHXCFG_MUXID(150U)                                                        /*!< DMAMUX TIMER63 CH1 request */
#define DMA_REQUEST_TIMER63_CH2           RM_CHXCFG_MUXID(151U)                                                        /*!< DMAMUX TIMER63 CH2 request */
#define DMA_REQUEST_TIMER63_CH3           RM_CHXCFG_MUXID(152U)                                                        /*!< DMAMUX TIMER63 CH3 request */
#define DMA_REQUEST_TIMER63_CH0N          RM_CHXCFG_MUXID(153U)                                                        /*!< DMAMUX TIMER63 CH0N request */
#define DMA_REQUEST_TIMER63_CH1N          RM_CHXCFG_MUXID(154U)                                                        /*!< DMAMUX TIMER63 CH1N request */
#define DMA_REQUEST_TIMER63_CH2N          RM_CHXCFG_MUXID(155U)                                                        /*!< DMAMUX TIMER63 CH2N request */
#define DMA_REQUEST_TIMER63_CH3N          RM_CHXCFG_MUXID(156U)                                                        /*!< DMAMUX TIMER63 CH3N request */
#define DMA_REQUEST_TIMER63_UP            RM_CHXCFG_MUXID(157U)                                                        /*!< DMAMUX TIMER63 UP request */
#define DMA_REQUEST_TIMER63_TRG           RM_CHXCFG_MUXID(158U)                                                        /*!< DMAMUX TIMER63 TRG request */
#define DMA_REQUEST_TIMER63_CMT           RM_CHXCFG_MUXID(159U)                                                        /*!< DMAMUX TIMER63 CMT request */
#define DMA_REQUEST_TIMER1_CH0            RM_CHXCFG_MUXID(160U)                                                        /*!< DMAMUX TIMER1 CH0 request */
#define DMA_REQUEST_TIMER1_CH1            RM_CHXCFG_MUXID(161U)                                                        /*!< DMAMUX TIMER1 CH1 request */
#define DMA_REQUEST_TIMER1_CH2            RM_CHXCFG_MUXID(162U)                                                        /*!< DMAMUX TIMER1 CH2 request */
#define DMA_REQUEST_TIMER1_CH3            RM_CHXCFG_MUXID(163U)                                                        /*!< DMAMUX TIMER1 CH3 request */
#define DMA_REQUEST_TIMER1_UP             RM_CHXCFG_MUXID(164U)                                                        /*!< DMAMUX TIMER1 UP request */
#define DMA_REQUEST_TIMER1_TRG            RM_CHXCFG_MUXID(165U)                                                        /*!< DMAMUX TIMER1 TRG request */
#define DMA_REQUEST_TIMER2_CH0            RM_CHXCFG_MUXID(166U)                                                        /*!< DMAMUX TIMER2 CH0 request */
#define DMA_REQUEST_TIMER2_CH1            RM_CHXCFG_MUXID(167U)                                                        /*!< DMAMUX TIMER2 CH1 request */
#define DMA_REQUEST_TIMER2_CH2            RM_CHXCFG_MUXID(168U)                                                        /*!< DMAMUX TIMER2 CH2 request */
#define DMA_REQUEST_TIMER2_CH3            RM_CHXCFG_MUXID(169U)                                                        /*!< DMAMUX TIMER2 CH3 request */
#define DMA_REQUEST_TIMER2_UP             RM_CHXCFG_MUXID(170U)                                                        /*!< DMAMUX TIMER2 UP request */
#define DMA_REQUEST_TIMER2_TRG            RM_CHXCFG_MUXID(171U)                                                        /*!< DMAMUX TIMER2 TRG request */
#define DMA_REQUEST_QSPI                  RM_CHXCFG_MUXID(172U)                                                        /*!< DMAMUX QSPI request */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_REQUEST_MFCOM_SSTAT0          RM_CHXCFG_MUXID(173U)                                                        /*!< DMAMUX MFCOM SSTAT0 request */
#define DMA_REQUEST_MFCOM_SSTAT1          RM_CHXCFG_MUXID(174U)                                                        /*!< DMAMUX MFCOM SSTAT1 request */
#define DMA_REQUEST_MFCOM_SSTAT2          RM_CHXCFG_MUXID(175U)                                                        /*!< DMAMUX MFCOM SSTAT2 request */
#define DMA_REQUEST_MFCOM_SSTAT3          RM_CHXCFG_MUXID(176U)                                                        /*!< DMAMUX MFCOM SSTAT3 request */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMA_REQUEST_DTM_CAN0_RX0          RM_CHXCFG_MUXID(177U)                                                        /*!< DMAMUX DTM_CAN0_RX0 request */
#define DMA_REQUEST_DTM_CAN0_RX1          RM_CHXCFG_MUXID(178U)                                                        /*!< DMAMUX DTM_CAN0_RX1 request */
#define DMA_REQUEST_DTM_CAN0_TX           RM_CHXCFG_MUXID(179U)                                                        /*!< DMAMUX DTM_CAN0_TX request */
#define DMA_REQUEST_DTM_CAN0_TXE          RM_CHXCFG_MUXID(180U)                                                        /*!< DMAMUX DTM_CAN0_TXE request */
#define DMA_REQUEST_DTM_CAN1_RX0          RM_CHXCFG_MUXID(181U)                                                        /*!< DMAMUX DTM_CAN1_RX0 request */
#define DMA_REQUEST_DTM_CAN1_RX1          RM_CHXCFG_MUXID(182U)                                                        /*!< DMAMUX DTM_CAN1_RX1 request */
#define DMA_REQUEST_DTM_CAN1_TX           RM_CHXCFG_MUXID(183U)                                                        /*!< DMAMUX DTM_CAN1_TX request */
#define DMA_REQUEST_DTM_CAN1_TXE          RM_CHXCFG_MUXID(184U)                                                        /*!< DMAMUX DTM_CAN1_TXE request */
#define DMA_REQUEST_ADC0_ROUTINE          RM_CHXCFG_MUXID(185U)                                                        /*!< DMAMUX ADC0 ROUTINE request */
#define DMA_REQUEST_ADC0_INSERTED0        RM_CHXCFG_MUXID(186U)                                                        /*!< DMAMUX ADC0 INSERTED0 request */
#define DMA_REQUEST_ADC0_INSERTED1        RM_CHXCFG_MUXID(187U)                                                        /*!< DMAMUX ADC0 INSERTED1 request */
#define DMA_REQUEST_ADC0_INSERTED2        RM_CHXCFG_MUXID(188U)                                                        /*!< DMAMUX ADC0 INSERTED2 request */
#define DMA_REQUEST_ADC0_INSERTED3        RM_CHXCFG_MUXID(189U)                                                        /*!< DMAMUX ADC0 INSERTED3 request */
#define DMA_REQUEST_ADC0_INSERTED4        RM_CHXCFG_MUXID(190U)                                                        /*!< DMAMUX ADC0 INSERTED4 request */
#define DMA_REQUEST_ADC0_INSERTED5        RM_CHXCFG_MUXID(191U)                                                        /*!< DMAMUX ADC0 INSERTED5 request */
#define DMA_REQUEST_ADC1_ROUTINE          RM_CHXCFG_MUXID(192U)                                                        /*!< DMAMUX ADC1 ROUTINE request */
#define DMA_REQUEST_ADC1_INSERTED0        RM_CHXCFG_MUXID(193U)                                                        /*!< DMAMUX ADC1 INSERTED0 request */
#define DMA_REQUEST_ADC1_INSERTED1        RM_CHXCFG_MUXID(194U)                                                        /*!< DMAMUX ADC1 INSERTED1 request */
#define DMA_REQUEST_ADC1_INSERTED2        RM_CHXCFG_MUXID(195U)                                                        /*!< DMAMUX ADC1 INSERTED2 request */
#define DMA_REQUEST_ADC1_INSERTED3        RM_CHXCFG_MUXID(196U)                                                        /*!< DMAMUX ADC1 INSERTED3 request */
#define DMA_REQUEST_ADC1_INSERTED4        RM_CHXCFG_MUXID(197U)                                                        /*!< DMAMUX ADC1 INSERTED4 request */
#define DMA_REQUEST_ADC1_INSERTED5        RM_CHXCFG_MUXID(198U)                                                        /*!< DMAMUX ADC1 INSERTED5 request */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_REQUEST_ADC2_ROUTINE          RM_CHXCFG_MUXID(199U)                                                        /*!< DMAMUX ADC2 ROUTINE request */
#define DMA_REQUEST_ADC2_INSERTED0        RM_CHXCFG_MUXID(200U)                                                        /*!< DMAMUX ADC2 INSERTED0 request */
#define DMA_REQUEST_ADC2_INSERTED1        RM_CHXCFG_MUXID(201U)                                                        /*!< DMAMUX ADC2INSERTED1 request */
#define DMA_REQUEST_ADC2_INSERTED2        RM_CHXCFG_MUXID(202U)                                                        /*!< DMAMUX ADC2INSERTED2 request */
#define DMA_REQUEST_ADC2_INSERTED3        RM_CHXCFG_MUXID(203U)                                                        /*!< DMAMUX ADC2INSERTED3 request */
#define DMA_REQUEST_ADC2_INSERTED4        RM_CHXCFG_MUXID(204U)                                                        /*!< DMAMUX ADC2INSERTED4 request */
#define DMA_REQUEST_ADC2_INSERTED5        RM_CHXCFG_MUXID(205U)                                                        /*!< DMAMUX ADC2INSERTED5 request */
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMA_REQUEST_TIMER5_UP1            RM_CHXCFG_MUXID(206U)                                                        /*!< DMAMUX TIMER5 UP1 request */
#define DMA_REQUEST_TIMER5_UP2            RM_CHXCFG_MUXID(207U)                                                        /*!< DMAMUX TIMER5 UP2 request */
#define DMA_REQUEST_TIMER5_UP3            RM_CHXCFG_MUXID(208U)                                                        /*!< DMAMUX TIMER5 UP3 request */
#define DMA_REQUEST_TIMER6_UP1            RM_CHXCFG_MUXID(209U)                                                        /*!< DMAMUX TIMER6 UP1 request */
#define DMA_REQUEST_TIMER6_UP2            RM_CHXCFG_MUXID(210U)                                                        /*!< DMAMUX TIMER6 UP2 request */
#define DMA_REQUEST_TIMER6_UP3            RM_CHXCFG_MUXID(211U)                                                        /*!< DMAMUX TIMER6 UP3 request */
#define DMA_REQUEST_DTM_CAN2_RX0          RM_CHXCFG_MUXID(212U)                                                        /*!< DMAMUX DTM_CAN2_RX0 request */
#define DMA_REQUEST_DTM_CAN2_RX1          RM_CHXCFG_MUXID(213U)                                                        /*!< DMAMUX DTM_CAN2_RX1 request */
#define DMA_REQUEST_DTM_CAN2_TX           RM_CHXCFG_MUXID(214U)                                                        /*!< DMAMUX DTM_CAN2_TX request */
#define DMA_REQUEST_DTM_CAN2_TXE          RM_CHXCFG_MUXID(215U)                                                        /*!< DMAMUX DTM_CAN2_TXE request */
#define DMA_REQUEST_DTM_CAN3_RX0          RM_CHXCFG_MUXID(216U)                                                        /*!< DMAMUX DTM_CAN3_RX0 request */
#define DMA_REQUEST_DTM_CAN3_RX1          RM_CHXCFG_MUXID(217U)                                                        /*!< DMAMUX DTM_CAN3_RX1 request */
#define DMA_REQUEST_DTM_CAN3_TX           RM_CHXCFG_MUXID(218U)                                                        /*!< DMAMUX DTM_CAN3_TX request */
#define DMA_REQUEST_DTM_CAN3_TXE          RM_CHXCFG_MUXID(219U)                                                        /*!< DMAMUX DTM_CAN3_TXE request */
#define DMA_REQUEST_DTM_CAN4_RX0          RM_CHXCFG_MUXID(220U)                                                        /*!< DMAMUX DTM_CAN4_RX0 request */
#define DMA_REQUEST_DTM_CAN4_RX1          RM_CHXCFG_MUXID(221U)                                                        /*!< DMAMUX DTM_CAN4_RX1 request */
#define DMA_REQUEST_DTM_CAN4_TX           RM_CHXCFG_MUXID(222U)                                                        /*!< DMAMUX DTM_CAN4_TX request */
#define DMA_REQUEST_DTM_CAN4_TXE          RM_CHXCFG_MUXID(223U)                                                        /*!< DMAMUX DTM_CAN4_TXE request */
#define DMA_REQUEST_DTM_CAN5_RX0          RM_CHXCFG_MUXID(224U)                                                        /*!< DMAMUX DTM_CAN5_RX0 request */
#define DMA_REQUEST_DTM_CAN5_RX1          RM_CHXCFG_MUXID(225U)                                                        /*!< DMAMUX DTM_CAN5_RX1 request */
#define DMA_REQUEST_DTM_CAN5_TX           RM_CHXCFG_MUXID(226U)                                                        /*!< DMAMUX DTM_CAN5_TX request */
#define DMA_REQUEST_DTM_CAN5_TXE          RM_CHXCFG_MUXID(227U)                                                        /*!< DMAMUX DTM_CAN5_TXE request */
#define DMA_REQUEST_DTM_CAN6_RX0          RM_CHXCFG_MUXID(228U)                                                        /*!< DMAMUX DTM_CAN6_RX0 request */
#define DMA_REQUEST_DTM_CAN6_RX1          RM_CHXCFG_MUXID(229U)                                                        /*!< DMAMUX DTM_CAN6_RX1 request */
#define DMA_REQUEST_DTM_CAN6_TX           RM_CHXCFG_MUXID(230U)                                                        /*!< DMAMUX DTM_CAN6_TX request */
#define DMA_REQUEST_DTM_CAN6_TXE          RM_CHXCFG_MUXID(231U)                                                        /*!< DMAMUX DTM_CAN6_TXE request */
#define DMA_REQUEST_DTM_CAN7_RX0          RM_CHXCFG_MUXID(232U)                                                        /*!< DMAMUX DTM_CAN7_RX0 request */
#define DMA_REQUEST_DTM_CAN7_RX1          RM_CHXCFG_MUXID(233U)                                                        /*!< DMAMUX DTM_CAN7_RX1 request */
#define DMA_REQUEST_DTM_CAN7_TX           RM_CHXCFG_MUXID(234U)                                                        /*!< DMAMUX DTM_CAN7_TX request */
#define DMA_REQUEST_DTM_CAN7_TXE          RM_CHXCFG_MUXID(235U)                                                        /*!< DMAMUX DTM_CAN7_TXE request */

/* DMAMUX request generator trigger input identification */
#define RG_CHXCFG_TID(regval)             (BITS(0,5) & ((uint32_t)(regval) << 0U))                                     /*!< trigger input identification */
#define DMAMUX_TRIGGER_EXTI0              RG_CHXCFG_TID(0U)                                                            /*!< trigger input is EXTI0 */
#define DMAMUX_TRIGGER_EXTI1              RG_CHXCFG_TID(1U)                                                            /*!< trigger input is EXTI1 */
#define DMAMUX_TRIGGER_EXTI2              RG_CHXCFG_TID(2U)                                                            /*!< trigger input is EXTI2 */
#define DMAMUX_TRIGGER_EXTI3              RG_CHXCFG_TID(3U)                                                            /*!< trigger input is EXTI3 */
#define DMAMUX_TRIGGER_EXTI4              RG_CHXCFG_TID(4U)                                                            /*!< trigger input is EXTI4 */
#define DMAMUX_TRIGGER_EXTI5              RG_CHXCFG_TID(5U)                                                            /*!< trigger input is EXTI5 */
#define DMAMUX_TRIGGER_EXTI6              RG_CHXCFG_TID(6U)                                                            /*!< trigger input is EXTI6 */
#define DMAMUX_TRIGGER_EXTI7              RG_CHXCFG_TID(7U)                                                            /*!< trigger input is EXTI7 */
#define DMAMUX_TRIGGER_EXTI8              RG_CHXCFG_TID(8U)                                                            /*!< trigger input is EXTI8 */
#define DMAMUX_TRIGGER_EXTI9              RG_CHXCFG_TID(9U)                                                            /*!< trigger input is EXTI9 */
#define DMAMUX_TRIGGER_EXTI10             RG_CHXCFG_TID(10U)                                                           /*!< trigger input is EXTI10 */
#define DMAMUX_TRIGGER_EXTI11             RG_CHXCFG_TID(11U)                                                           /*!< trigger input is EXTI11 */
#define DMAMUX_TRIGGER_EXTI12             RG_CHXCFG_TID(12U)                                                           /*!< trigger input is EXTI12 */
#define DMAMUX_TRIGGER_EXTI13             RG_CHXCFG_TID(13U)                                                           /*!< trigger input is EXTI13 */
#define DMAMUX_TRIGGER_EXTI14             RG_CHXCFG_TID(14U)                                                           /*!< trigger input is EXTI14 */
#define DMAMUX_TRIGGER_EXTI15             RG_CHXCFG_TID(15U)                                                           /*!< trigger input is EXTI15 */
#define DMAMUX_TRIGGER_EVT0_OUT           RG_CHXCFG_TID(16U)                                                           /*!< trigger input is Evt0_out */
#define DMAMUX_TRIGGER_EVT1_OUT           RG_CHXCFG_TID(17U)                                                           /*!< trigger input is Evt1_out */
#define DMAMUX_TRIGGER_EVT2_OUT           RG_CHXCFG_TID(18U)                                                           /*!< trigger input is Evt2_out */
#define DMAMUX_TRIGGER_EVT3_OUT           RG_CHXCFG_TID(19U)                                                           /*!< trigger input is Evt3_out */
#define DMAMUX_TRIGGER_EVT4_OUT           RG_CHXCFG_TID(20U)                                                           /*!< trigger input is Evt4_out */
#define DMAMUX_TRIGGER_EVT5_OUT           RG_CHXCFG_TID(21U)                                                           /*!< trigger input is Evt5_out */
#define DMAMUX_TRIGGER_EVT6_OUT           RG_CHXCFG_TID(22U)                                                           /*!< trigger input is Evt6_out */
#define DMAMUX_TRIGGER_EVT7_OUT           RG_CHXCFG_TID(23U)                                                           /*!< trigger input is Evt7_out */
#define DMAMUX_TRIGGER_TIMER1_TRGO        RG_CHXCFG_TID(24U)                                                           /*!< trigger input is TIMER1 TRGO */

/* DMAMUX request generator trigger polarity */
#define RG_CHXCFG_RGTP(regval)            (BITS(17,18) & ((uint32_t)(regval) << 17U))                                  /*!< DMA request generator trigger polarity */
#define DMAMUX_GEN_NO_EVENT               RG_CHXCFG_RGTP(0U)                                                           /*!< no event detection */
#define DMAMUX_GEN_RISING                 RG_CHXCFG_RGTP(1U)                                                           /*!< rising edge */
#define DMAMUX_GEN_FALLING                RG_CHXCFG_RGTP(2U)                                                           /*!< falling edge */
#define DMAMUX_GEN_RISING_FALLING         RG_CHXCFG_RGTP(3U)                                                           /*!< rising and falling edges */

/* number of DMA requests to be generated */
#define RG_CHXCFG_NBRG(regval)            (BITS(19,23) & ((uint32_t)(regval) << 19U))                                  /*!< number of DMA requests to be generated */

/* DMAMUX request multiplexer channel synchronization input identification */
#define RM_CHXCFG_SYNCID(regval)          (BITS(24,28) & ((uint32_t)(regval) << 24U))                                  /*!< synchronization input identification */
#define DMAMUX_SYNC_EXTI0                 RM_CHXCFG_SYNCID(0U)                                                         /*!< synchronization input is EXTI0 */
#define DMAMUX_SYNC_EXTI1                 RM_CHXCFG_SYNCID(1U)                                                         /*!< synchronization input is EXTI1 */
#define DMAMUX_SYNC_EXTI2                 RM_CHXCFG_SYNCID(2U)                                                         /*!< synchronization input is EXTI2 */
#define DMAMUX_SYNC_EXTI3                 RM_CHXCFG_SYNCID(3U)                                                         /*!< synchronization input is EXTI3 */
#define DMAMUX_SYNC_EXTI4                 RM_CHXCFG_SYNCID(4U)                                                         /*!< synchronization input is EXTI4 */
#define DMAMUX_SYNC_EXTI5                 RM_CHXCFG_SYNCID(5U)                                                         /*!< synchronization input is EXTI5 */
#define DMAMUX_SYNC_EXTI6                 RM_CHXCFG_SYNCID(6U)                                                         /*!< synchronization input is EXTI6 */
#define DMAMUX_SYNC_EXTI7                 RM_CHXCFG_SYNCID(7U)                                                         /*!< synchronization input is EXTI7 */
#define DMAMUX_SYNC_EXTI8                 RM_CHXCFG_SYNCID(8U)                                                         /*!< synchronization input is EXTI8 */
#define DMAMUX_SYNC_EXTI9                 RM_CHXCFG_SYNCID(9U)                                                         /*!< synchronization input is EXTI9 */
#define DMAMUX_SYNC_EXTI10                RM_CHXCFG_SYNCID(10U)                                                        /*!< synchronization input is EXTI10 */
#define DMAMUX_SYNC_EXTI11                RM_CHXCFG_SYNCID(11U)                                                        /*!< synchronization input is EXTI11 */
#define DMAMUX_SYNC_EXTI12                RM_CHXCFG_SYNCID(12U)                                                        /*!< synchronization input is EXTI12 */
#define DMAMUX_SYNC_EXTI13                RM_CHXCFG_SYNCID(13U)                                                        /*!< synchronization input is EXTI13 */
#define DMAMUX_SYNC_EXTI14                RM_CHXCFG_SYNCID(14U)                                                        /*!< synchronization input is EXTI14 */
#define DMAMUX_SYNC_EXTI15                RM_CHXCFG_SYNCID(15U)                                                        /*!< synchronization input is EXTI15 */
#define DMAMUX_SYNC_EVT0_OUT              RM_CHXCFG_SYNCID(16U)                                                        /*!< synchronization input is Evt0_out */
#define DMAMUX_SYNC_EVT1_OUT              RM_CHXCFG_SYNCID(17U)                                                        /*!< synchronization input is Evt1_out */
#define DMAMUX_SYNC_EVT2_OUT              RM_CHXCFG_SYNCID(18U)                                                        /*!< synchronization input is Evt2_out */
#define DMAMUX_SYNC_EVT3_OUT              RM_CHXCFG_SYNCID(19U)                                                        /*!< synchronization input is Evt3_out */
#define DMAMUX_SYNC_EVT4_OUT              RM_CHXCFG_SYNCID(20U)                                                        /*!< synchronization input is Evt4_out */
#define DMAMUX_SYNC_EVT5_OUT              RM_CHXCFG_SYNCID(21U)                                                        /*!< synchronization input is Evt5_out */
#define DMAMUX_SYNC_EVT6_OUT              RM_CHXCFG_SYNCID(22U)                                                        /*!< synchronization input is Evt6_out */
#define DMAMUX_SYNC_EVT7_OUT              RM_CHXCFG_SYNCID(23U)                                                        /*!< synchronization input is Evt7_out */
#define DMAMUX_SYNC_TIMER1_TRGO           RM_CHXCFG_SYNCID(24U)                                                        /*!< synchronization input is TIMER1_TRGO */

/* DMAMUX request multiplexer synchronization input polarity */
#define RM_CHXCFG_SYNCP(regval)           (BITS(17,18) & ((uint32_t)(regval) << 17U))                                  /*!< synchronization input polarity */
#define DMAMUX_SYNC_NO_EVENT              RM_CHXCFG_SYNCP(0U)                                                          /*!< no event detection */
#define DMAMUX_SYNC_RISING                RM_CHXCFG_SYNCP(1U)                                                          /*!< rising edge */
#define DMAMUX_SYNC_FALLING               RM_CHXCFG_SYNCP(2U)                                                          /*!< falling edge */
#define DMAMUX_SYNC_RISING_FALLING        RM_CHXCFG_SYNCP(3U)                                                          /*!< rising and falling edges */

/* number of DMA requests to forward */
#define RM_CHXCFG_NBR(regval)            (BITS(19,23) & ((uint32_t)(regval) << 19U))                                   /*!< number of DMA requests to forward */

#define DMA_RR_PRIORITY_LOW               DMA_GCTL_LPRREN                                                              /*!< round-robin for channels with low software priority level */
#define DMA_RR_PRIORITY_MEDIUM            DMA_GCTL_MPRREN                                                              /*!< round-robin for channels with medium software priority level */
#define DMA_RR_PRIORITY_HIGH              DMA_GCTL_HPRREN                                                              /*!< round-robin for channels with high software priority level */
#define DMA_RR_PRIORITY_ULTRA_HIGH        DMA_GCTL_UHPRREN                                                             /*!< round-robin for channels with ultra high software priority level */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT
/* check peripherals */
#define NOT_DMA_PERIPH(periph)                               (((periph) != DMA0) && ((periph) != DMA1))
/* check DMA channel */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_CHANNEL_HIGH                                     DMA_CH15
#else
#define DMA_CHANNEL_HIGH                                     DMA_CH7
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define NOT_DMA_CHANNEL(channels)                            (DMA_CHANNEL_HIGH < (channels))

/* check DMA request */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMA_REQUEST_HIGH                                     RM_CHXCFG_MUXID(211U)
#else
#define DMA_REQUEST_HIGH                                     RM_CHXCFG_MUXID(235U)
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define NOT_DMA_REQUEST(request)                             (DMA_REQUEST_HIGH < (request))
/* check DMA periph increase algorithm */
#define NOT_DMA_PERIPH_INCREASE(periph_inc)                  (((periph_inc) != DMA_PERIPH_INCREASE_ENABLE) && ((periph_inc) != DMA_PERIPH_INCREASE_DISABLE) && \
                                                              ((periph_inc) != DMA_PERIPH_INCREASE_FIX))
/* check memory increase algorithm*/
#define NOT_DMA_MEMORY_INCREASE(memory_inc)                  (((memory_inc) != DMA_MEMORY_INCREASE_ENABLE) && ((memory_inc) != DMA_MEMORY_INCREASE_DISABLE))
/* check DMA periph and memory width */
#define NOT_DMA_PERIPH_MEMORY_WIDTH(periph_memory_width)     (((periph_memory_width) != DMA_PERIPH_WIDTH_8BIT) && ((periph_memory_width) != DMA_PERIPH_WIDTH_16BIT) && \
                                                              ((periph_memory_width) != DMA_PERIPH_WIDTH_32BIT) && ((periph_memory_width) != DMA_PERIPH_WIDTH_64BIT))
/* check DMA periph address circular mode */
#define NOT_DMA_PERIPH_ADDR_CIRCULAR(periph_addr_circular)   (((periph_addr_circular) != DMA_PERIPH_ADDR_CIRCULAR_ENABLE) && ((periph_addr_circular) != DMA_PERIPH_ADDR_CIRCULAR_DISABLE))
/* check DMA memory address circular mode */
#define NOT_DMA_MEMORY_ADDR_CIRCULAR(memory_addr_circular)   (((memory_addr_circular) != DMA_MEMORY_ADDR_CIRCULAR_ENABLE) && ((memory_addr_circular) != DMA_MEMORY_ADDR_CIRCULAR_DISABLE))
/* check DMA transfer direction */
#define NOT_DMA_TRANSFER_DIRECTION(direction)                (((direction) != DMA_PERIPH_TO_MEMORY) && ((direction) != DMA_MEMORY_TO_PERIPH) && \
                                                              ((direction) != DMA_MEMORY_TO_MEMORY))
/* check DMA number of remaining data to be transferred */
#define DMA_NUMBER_HIGH                                      (65535U)
#define NOT_DMA_NUMBER(number)                               (DMA_NUMBER_HIGH < (number))
/* check DMA priority */
#define NOT_DMA_PRIORITY(priority)                           (((priority) != DMA_PRIORITY_LOW) && ((priority) != DMA_PRIORITY_MEDIUM) && \
                                                              ((priority) != DMA_PRIORITY_HIGH) && ((priority) != DMA_PRIORITY_ULTRA_HIGH))
/* check DMA periph width */
#define NOT_DMA_PERIPH_WIDTH(periph_width)                   (((periph_width) != DMA_PERIPH_WIDTH_8BIT) && ((periph_width) != DMA_PERIPH_WIDTH_16BIT) && \
                                                              ((periph_width) != DMA_PERIPH_WIDTH_32BIT) && ((periph_width) != DMA_PERIPH_WIDTH_64BIT))
/* check DMA memory width */
#define NOT_DMA_MEMORY_WIDTH(memory_width)                   (((memory_width) != DMA_MEMORY_WIDTH_8BIT)  && ((memory_width) != DMA_MEMORY_WIDTH_16BIT) && \
                                                              ((memory_width) != DMA_MEMORY_WIDTH_32BIT) && ((memory_width) != DMA_MEMORY_WIDTH_64BIT))
/* check DMA memory burst width */
#define NOT_DMA_MEMORY_BURST_WIDTH(memory_burst_width)       (((memory_burst_width) != DMA_MEMORY_BURST_SINGLE)  && ((memory_burst_width) != DMA_MEMORY_BURST_4_BEAT) && \
                                                              ((memory_burst_width) != DMA_MEMORY_BURST_8_BEAT)  && ((memory_burst_width) != DMA_MEMORY_BURST_16_BEAT))
/* check DMA periph burst width */
#define NOT_DMA_PERIPH_BURST_WIDTH(periph_burst_width)       (((periph_burst_width) != DMA_PERIPH_BURST_SINGLE)  && ((periph_burst_width) != DMA_PERIPH_BURST_4_BEAT) && \
                                                              ((periph_burst_width) != DMA_PERIPH_BURST_8_BEAT)  && ((periph_burst_width) != DMA_PERIPH_BURST_16_BEAT))
/* check DMA FIFO critical value */
#define NOT_DMA_FIFO_CRITICAL_VALUE(critical_value)          (((critical_value) != DMA_FIFO_2_WORD) && ((critical_value) != DMA_FIFO_4_WORD) && \
                                                              ((critical_value) != DMA_FIFO_6_WORD) && ((critical_value) != DMA_FIFO_8_WORD))
/* check DMA memory flag */
#define NOT_DMA_MEMORY_FLAG(memory_flag)                     (((memory_flag) != DMA_MEMORY_0)  && ((memory_flag) != DMA_MEMORY_1))
/* check DMA flow controller */
#define NOT_DMA_FLOW_CONTROLLER(controller)                  (((controller) != DMA_FLOW_CONTROLLER_DMA)  && ((controller) != DMA_FLOW_CONTROLLER_PERI))
/* check DMA transfer timeout threshold */
#define DMA_TIMEOUT_THRESHOLD_HIGH                           (0x1FFFFFU)
#define NOT_DMA_TIMEOUT_THRESHOLD(threshold)                 ((DMA_TIMEOUT_THRESHOLD_HIGH < (threshold)))
/* check DMA flag */
#define NOT_DMA_FLAG(flag)                                   (((flag) != DMA_FLAG_FEE) && ((flag) != DMA_FLAG_SDE) && \
                                                              ((flag) != DMA_FLAG_TAE) && ((flag) != DMA_FLAG_HTF) && \
                                                              ((flag) != DMA_FLAG_FTF) && ((flag) != DMA_FLAG_TIMEOUT) && \
                                                              ((flag) != DMA_FLAG_TMR_FAULT))
/* check DMA interrupt flag */
#define NOT_DMA_INTERRUPT_FLAG(interrupt_flag)               (((interrupt_flag) != DMA_INT_FLAG_FEE) && ((interrupt_flag) != DMA_INT_FLAG_SDE) && \
                                                              ((interrupt_flag) != DMA_INT_FLAG_TAE) && ((interrupt_flag) != DMA_INT_FLAG_HTF) && \
                                                              ((interrupt_flag) != DMA_INT_FLAG_FTF) && ((interrupt_flag) != DMA_INT_FLAG_TIMEOUT) && \
                                                              ((interrupt_flag) != DMA_INT_FLAG_TMR_FAULT))
/* check DMA interrupt */
#define NOT_DMA_INTERRUPT(interrupt)                         (((interrupt) != DMA_INT_SDE)  && ((interrupt) != DMA_INT_TAE) && \
                                                              ((interrupt) != DMA_INT_HTF)  && ((interrupt) != DMA_INT_FTF) && \
                                                              ((interrupt) != DMA_INT_FEE) && ((interrupt) != DMA_INT_TIMEOUT) && \
                                                              ((interrupt) != DMA_INT_TMR))
/* check DMAMUX multiplexer channel */
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMAMUX_CHANNEL_HIGH                                  DMAMUX_MUXCH31
#else
#define DMAMUX_CHANNEL_HIGH                                  DMAMUX_MUXCH15
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define NOT_DMAMUX_MULTIPLEXER_CHANNEL(channels)             ((uint32_t)DMAMUX_CHANNEL_HIGH < ((uint32_t)channels))
/* check DMAMUX generator channel */
#define DMAMUX_GENERATOR_CHANNEL_HIGH                        DMAMUX_GENCH7
#define NOT_DMAMUX_GENERATOR_CHANNEL(channels)               ((uint32_t)DMAMUX_GENERATOR_CHANNEL_HIGH < ((uint32_t)channels))
/* check DMAMUX sync_id */
#define DMAMUX_SYNC_ID_HIGH                                  DMAMUX_SYNC_TIMER1_TRGO
#define NOT_DMAMUX_SYNC_ID(sync_id)                          (DMAMUX_SYNC_ID_HIGH < (sync_id))
/* check DMAMUX sync_polarity */
#define NOT_DMAMUX_SYNC_POLARITY(sync_polarity)              (((sync_polarity) != DMAMUX_SYNC_NO_EVENT)       && ((sync_polarity) != DMAMUX_SYNC_RISING) && \
                                                              ((sync_polarity) != DMAMUX_SYNC_FALLING)        && ((sync_polarity) != DMAMUX_SYNC_RISING_FALLING))
/* check DMAMUX request number */
#define DMAMUX_REQUEST_NUMBER_LOW                            (1U)
#define DMAMUX_REQUEST_NUMBER_HIGH                           (32U)
#define NOT_DMAMUX_REQUEST_NUMBER(request_number)            ((DMAMUX_REQUEST_NUMBER_HIGH < (request_number)) || (DMAMUX_REQUEST_NUMBER_LOW > (request_number)))

/* check DMAMUX trigger_id */
#define DMAMUX_TRIGGER_ID_HIGH                               DMAMUX_TRIGGER_TIMER1_TRGO
#define NOT_DMAMUX_TRIGGER_ID(trigger_id)                    (DMAMUX_TRIGGER_ID_HIGH < (trigger_id))
/* check DMAMUX trigger_polarity */
#define NOT_DMAMUX_TRIGGER_POLARITY(trigger_polarity)        (((trigger_polarity) != DMAMUX_GEN_NO_EVENT) && ((trigger_polarity) != DMAMUX_GEN_RISING) && \
                                                              ((trigger_polarity) != DMAMUX_GEN_FALLING) && ((trigger_polarity) != DMAMUX_GEN_RISING_FALLING))
/* check DMAMUX flag */
#define DMAMUX_FLAG_LOW0                                     DMAMUX_FLAG_MUXCH0_SO
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMAMUX_FLAG_HIGH0                                    DMAMUX_FLAG_MUXCH31_SO
#else
#define DMAMUX_FLAG_HIGH0                                    DMAMUX_FLAG_MUXCH15_SO
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMAMUX_FLAG_LOW1                                     DMAMUX_FLAG_GENCH0_TO
#define DMAMUX_FLAG_HIGH1                                    DMAMUX_FLAG_GENCH7_TO
#define NOT_DMAMUX_FLAG(flag)                                (((DMAMUX_FLAG_HIGH0 < (flag)) || (DMAMUX_FLAG_LOW0 > (flag))) && \
                                                              (((DMAMUX_FLAG_HIGH1 < (flag)) || (DMAMUX_FLAG_LOW1 > (flag)))))
/* check DMAMUX interrupt */
#define DMAMUX_INTERRUPT_LOW0                                DMAMUX_INT_MUXCH0_SO
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMAMUX_INTERRUPT_HIGH0                               DMAMUX_INT_MUXCH31_SO
#else
#define DMAMUX_INTERRUPT_HIGH0                               DMAMUX_INT_MUXCH15_SO
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMAMUX_INTERRUPT_LOW1                                DMAMUX_INT_GENCH0_TO
#define DMAMUX_INTERRUPT_HIGH1                               DMAMUX_INT_GENCH1_TO
#define NOT_DMAMUX_INTERRUPT(interrupt)                      (((DMAMUX_INTERRUPT_HIGH0 < (interrupt)) || (DMAMUX_INTERRUPT_LOW0 > (interrupt))) && \
                                                              (((DMAMUX_INTERRUPT_HIGH1 < (interrupt)) || (DMAMUX_INTERRUPT_LOW1 > (interrupt)))))
/* check DMAMUX interrupt flag */
#define DMAMUX_INTERRUPT_FLAG_LOW0                           DMAMUX_INT_FLAG_MUXCH0_SO
#if defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX)
#define DMAMUX_INTERRUPT_FLAG_HIGH0                          DMAMUX_INT_FLAG_MUXCH31_SO
#else
#define DMAMUX_INTERRUPT_FLAG_HIGH0                          DMAMUX_INT_FLAG_MUXCH15_SO
#endif /* defined(GD32A714X) || defined (GD32A72XX) || defined (GD32A74XX) */
#define DMAMUX_INTERRUPT_FLAG_LOW1                           DMAMUX_INT_FLAG_GENCH0_TO
#define DMAMUX_INTERRUPT_FLAG_HIGH1                          DMAMUX_INT_FLAG_GENCH7_TO
#define NOT_DMAMUX_INTERRUPT_FLAG(interrupt_flag)            (((DMAMUX_INTERRUPT_FLAG_HIGH0 < (interrupt_flag)) || (DMAMUX_INTERRUPT_FLAG_LOW0 > (interrupt_flag))) && \
                                                              (((DMAMUX_INTERRUPT_FLAG_HIGH1 < (interrupt_flag)) || (DMAMUX_INTERRUPT_FLAG_LOW1 > (interrupt_flag)))))
/* check DMA priority */
#define NOT_DMA_RR_PRIORITY(priority)                         (((priority) != DMA_RR_PRIORITY_LOW) && ((priority) != DMA_RR_PRIORITY_MEDIUM) && \
                                                               ((priority) != DMA_RR_PRIORITY_HIGH) && ((priority) != DMA_RR_PRIORITY_ULTRA_HIGH))
#endif /* FW_DEBUG_ERR_REPORT */

/* function declarations */
/* DMA deinitialization and initialization functions */
/* deinitialize DMA a channel registers */
void dma_deinit(uint32_t dma_periph, dma_channel_enum channelx);
/* initialize the DMA single data mode parameters struct with the default values */
void dma_single_data_para_struct_init(dma_single_data_parameter_struct *init_struct);
/* initialize the DMA multi data mode parameters struct with the default values */
void dma_multi_data_para_struct_init(dma_multi_data_parameter_struct *init_struct);
/* initialize DMA single data mode */
void dma_single_data_mode_init(uint32_t dma_periph, dma_channel_enum channelx, dma_single_data_parameter_struct *init_struct);
/* initialize DMA multi data mode */
void dma_multi_data_mode_init(uint32_t dma_periph, dma_channel_enum channelx, dma_multi_data_parameter_struct *init_struct);

/* DMA configuration functions */
/* set DMA peripheral base address */
void dma_periph_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t address);
/* set DMA memory base address */
void dma_memory_address_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t memory_flag, uint32_t address);

/* set the number of remaining data to be transferred by the DMA */
void dma_transfer_number_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t number);
/* get the number of remaining data to be transferred by the DMA */
uint32_t dma_transfer_number_get(uint32_t dma_periph, dma_channel_enum channelx);

/* configure priority level of DMA channel */
void dma_priority_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t priority);

/* configure transfer burst beats of memory */
void dma_memory_burst_beats_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t mbeat);
/* configure transfer burst beats of peripheral */
void dma_periph_burst_beats_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t pbeat);
/* configure transfer data size of memory */
void dma_memory_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t msize);
/* configure transfer data size of peripheral */
void dma_periph_width_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t psize);

/* configure memory address generation generation_algorithm */
void dma_memory_address_generation_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t generation_algorithm);
/* configure peripheral address generation_algorithm */
void dma_peripheral_address_generation_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t generation_algorithm);

/* enable DMA circulation mode */
void dma_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA circulation mode */
void dma_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable DMA channel */
void dma_channel_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA channel */
void dma_channel_disable(uint32_t dma_periph, dma_channel_enum channelx);

/* configure the direction of data transfer on the channel */
void dma_transfer_direction_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t direction);

/* DMA switch buffer mode configure */
void dma_switch_buffer_mode_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t memory1_addr, uint32_t memory_select);
/* DMA using memory get */
uint32_t dma_using_memory_get(uint32_t dma_periph, dma_channel_enum channelx);

/* enable dma channel peripheral address circulation function */
void dma_peripheral_address_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable dma channel peripheral address circulation function */
void dma_peripheral_address_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable dma channel memory address circulation function */
void dma_memory_address_circulation_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable dma channel memory address circulation function */
void dma_memory_address_circulation_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* enable dma channel circulation count function */
void dma_circulation_count_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable dma channel circulation count function */
void dma_circulation_count_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* configure dma channel circulation count */
void dma_circulation_count_config(uint32_t dma_periph, dma_channel_enum channelx, uint8_t count);
/* enable dma priority round robin function */
void dma_round_robin_mode_enable(uint32_t dma_periph, uint32_t priority);
/* disable dma priority round robin function */
void dma_round_robin_mode_disable(uint32_t dma_periph, uint32_t priority);

/* DMA flow controller configure */
void dma_flow_controller_config(uint32_t dma_periph, dma_channel_enum channelx, uint32_t controller);
/* enable DMA switch buffer mode */
void dma_switch_buffer_mode_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA switch buffer mode */
void dma_switch_buffer_mode_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* DMA FIFO status get */
uint32_t dma_fifo_status_get(uint32_t dma_periph, dma_channel_enum channelx);

/* get DMA channel peripheral port CRC value */
uint32_t dma_peripheral_port_crc_value_get(uint32_t dma_periph, dma_channel_enum channelx);
/* set DMA channel peripheral port CRC value */
void dma_peripheral_port_crc_value_set(uint32_t dma_periph, dma_channel_enum channelx, uint32_t data);
/* set DMA peripheral port initial CRC data */
void dma_peripheral_port_initial_crc_value_set(uint32_t dma_periph, uint32_t data);
/* get DMA peripheral port initial CRC value */
uint32_t dma_peripheral_port_initial_crc_value_get(uint32_t dma_periph);
/* deinit DMA channel peripheral port CRC value */
void dma_peripheral_port_crc_value_deinit(uint32_t dma_periph, dma_channel_enum channelx);
/* get DMA channel peripheral port current transferred address */
uint32_t dma_peripheral_port_current_address_get(uint32_t dma_periph, dma_channel_enum channelx);
/* get DMA channel memory port current transferred address */
uint32_t dma_memory_port_current_address_get(uint32_t dma_periph, dma_channel_enum channelx);

/* enable DMA channel transfer timeout monitor */
void dma_transfer_timeout_monitor_enable(uint32_t dma_periph, dma_channel_enum channelx);
/* disable DMA channel transfer timeout monitor */
void dma_transfer_timeout_monitor_disable(uint32_t dma_periph, dma_channel_enum channelx);
/* set DMA channel transfer timeout threshold value */
void dma_transfer_timeout_threshold_value_set(uint32_t dma_periph, dma_channel_enum channelx, uint32_t threshold_value);
/* get DMA channel transfer timeout threshold value */
uint32_t dma_transfer_timeout_threshold_value_get(uint32_t dma_periph, dma_channel_enum channelx);

/* flag and interrupt functions */
/* get DMA flag is set or not */
FlagStatus dma_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* clear DMA a channel flag */
void dma_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t flag);
/* get DMA interrupt flag is set or not */
FlagStatus dma_interrupt_flag_get(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt);
/* clear DMA a channel interrupt flag */
void dma_interrupt_flag_clear(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt);
/* enable DMA interrupt */
void dma_interrupt_enable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt);
/* disable DMA interrupt */
void dma_interrupt_disable(uint32_t dma_periph, dma_channel_enum channelx, uint32_t interrupt);

/* DMAMUX functions */
/* DMAMUX request multiplexer functions */
/* initialize the parameters of DMAMUX synchronization mode structure with the default values */
void dmamux_sync_struct_para_init(dmamux_sync_parameter_struct *init_struct);
/* initialize DMAMUX request multiplexer channel synchronization mode */
void dmamux_synchronization_init(dmamux_multiplexer_channel_enum channelx, dmamux_sync_parameter_struct *init_struct);
/* enable synchronization mode */
void dmamux_synchronization_enable(dmamux_multiplexer_channel_enum channelx);
/* disable synchronization mode */
void dmamux_synchronization_disable(dmamux_multiplexer_channel_enum channelx);
/* enable event generation */
void dmamux_event_generation_enable(dmamux_multiplexer_channel_enum channelx);
/* disable event generation */
void dmamux_event_generation_disable(dmamux_multiplexer_channel_enum channelx);

/* DMAMUX request generator functions */
/* initialize the parameters of DMAMUX request generator structure with the default values */
void dmamux_gen_struct_para_init(dmamux_gen_parameter_struct *init_struct);
/* initialize DMAMUX request generator channel */
void dmamux_request_generator_init(dmamux_generator_channel_enum channelx, dmamux_gen_parameter_struct *init_struct);
/* enable DMAMUX request generator channel */
void dmamux_request_generator_channel_enable(dmamux_generator_channel_enum channelx);
/* disable DMAMUX request generator channel */
void dmamux_request_generator_channel_disable(dmamux_generator_channel_enum channelx);

/* DMAMUX configuration functions */
/* configure synchronization input polarity */
void dmamux_synchronization_polarity_config(dmamux_multiplexer_channel_enum channelx, uint32_t polarity);
/* configure number of DMA requests to forward */
void dmamux_request_forward_number_config(dmamux_multiplexer_channel_enum channelx, uint32_t number);
/* configure synchronization input identification */
void dmamux_sync_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id);
/* configure multiplexer input identification */
void dmamux_request_id_config(dmamux_multiplexer_channel_enum channelx, uint32_t id);
/* configure trigger input polarity */
void dmamux_trigger_polarity_config(dmamux_generator_channel_enum channelx, uint32_t polarity);
/* configure number of DMA requests to be generated */
void dmamux_request_generate_number_config(dmamux_generator_channel_enum channelx, uint32_t number);
/* configure trigger input identification */
void dmamux_trigger_id_config(dmamux_generator_channel_enum channelx, uint32_t id);

/* DMAMUX interrupt and flag functions */
/* get DMAMUX flag */
FlagStatus dmamux_flag_get(dmamux_flag_enum flag);
/* clear DMAMUX flag */
void dmamux_flag_clear(dmamux_flag_enum flag);
/* enable DMAMUX interrupt */
void dmamux_interrupt_enable(dmamux_interrupt_enum interrupt);
/* disable DMAMUX interrupt */
void dmamux_interrupt_disable(dmamux_interrupt_enum interrupt);
/* get DMAMUX interrupt flag */
FlagStatus dmamux_interrupt_flag_get(dmamux_interrupt_flag_enum int_flag);
/* clear DMAMUX interrupt flag */
void dmamux_interrupt_flag_clear(dmamux_interrupt_flag_enum int_flag);

#endif /* GD32A7XX_DMA_H */
