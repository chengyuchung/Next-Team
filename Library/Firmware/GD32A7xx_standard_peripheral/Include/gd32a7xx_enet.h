/*!
    \file    gd32a7xx_enet.h
    \brief   definitions for the ENET

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

#ifndef GD32A7XX_ENET_H
#define GD32A7XX_ENET_H

#include "gd32a7xx.h"
#include <stdlib.h>

//#define DMACH0_USE_ENHANCED_MODE    1
//#define DMACH1_USE_ENHANCED_MODE    1
#define IF_USE_EXTERNPHY_LIB             0
#if (1 == IF_USE_EXTERNPHY_LIB)
#include "phy.h"
#endif

#ifndef ENET_RXBUF_NUM
#define ENET_RXBUF_NUM                   ((uint32_t)4U)                          /*!< ethernet Rx DMA descriptor number */
#endif

#ifndef ENET_TXBUF_NUM
#define ENET_TXBUF_NUM                   ((uint32_t)4U)                         /*!< ethernet Tx DMA descriptor number */
#endif

#ifndef ENET_RXBUF_SIZE
#define ENET_RXBUF_SIZE                  ENET_MAX_FRAME_SIZE                    /*!< ethernet receive buffer size */
#endif

#ifndef ENET_TXBUF_SIZE
#define ENET_TXBUF_SIZE                  ENET_MAX_FRAME_SIZE                    /*!< ethernet transmit buffer size */
#endif

#ifndef _PHY_H_
#define DP83848                          0
#define LAN8700                          1
#define YT8512                           2
#define PHY_TYPE                         DP83848

#ifndef YT8010A
#define PHY_ADDRESS                      ((uint16_t)0x1FU)                         /*!< phy address determined by the hardware */
#else
#define PHY_ADDRESS                      ((uint16_t)0x2U)                         /*!< phy address determined by the hardware */
#endif

/* PHY read write timeouts */
#define PHY_READ_TO                      ((uint32_t)0x0004FFFFU)                /*!< PHY read timeout */
#define PHY_WRITE_TO                     ((uint32_t)0x0004FFFFU)                /*!< PHY write timeout */

/* PHY delay */
#define PHY_RESETDELAY                   ((uint32_t)0x008FFFFFU)                /*!< PHY reset delay */
#define PHY_CONFIGDELAY                  ((uint32_t)0x00FFFFFFU)                /*!< PHY configure delay */

/* PHY register address */
#define PHY_REG_BCR                      0U                                     /*!< tranceiver basic control register */
#define PHY_REG_BSR                      1U                                     /*!< tranceiver basic status register */

/* PHY basic control register */
#define PHY_RESET                        ((uint16_t)0x8000)                     /*!< PHY reset */
#define PHY_LOOPBACK                     ((uint16_t)0x4000)                     /*!< enable phy loop-back mode */
#define PHY_FULLDUPLEX_100M              ((uint16_t)0x2100)                     /*!< configure speed to 100 Mbit/s and the full-duplex mode */
#define PHY_HALFDUPLEX_100M              ((uint16_t)0x2000)                     /*!< configure speed to 100 Mbit/s and the half-duplex mode */
#define PHY_FULLDUPLEX_10M               ((uint16_t)0x0100)                     /*!< configure speed to 10 Mbit/s and the full-duplex mode */
#define PHY_HALFDUPLEX_10M               ((uint16_t)0x0000)                     /*!< configure speed to 10 Mbit/s and the half-duplex mode */
#define PHY_AUTONEGOTIATION              ((uint16_t)0x1000)                     /*!< enable auto-negotiation function */
#define PHY_RESTART_AUTONEGOTIATION      ((uint16_t)0x0200)                     /*!< restart auto-negotiation function */
#define PHY_POWERDOWN                    ((uint16_t)0x0800)                     /*!< enable the power down mode */
#define PHY_ISOLATE                      ((uint16_t)0x0400)                     /*!< isolate PHY from MII */

/* PHY basic status register */
#define PHY_AUTONEGO_COMPLETE            ((uint16_t)0x0020)                     /*!< auto-negotioation process completed */
#define PHY_LINKED_STATUS                ((uint16_t)0x0004)                     /*!< valid link established */
#define PHY_JABBER_DETECTION             ((uint16_t)0x0002)                     /*!< jabber condition detected */

#if(PHY_TYPE == LAN8700)
#define PHY_SR                           31U                                    /*!< tranceiver status register */
#define PHY_SPEED_STATUS                 ((uint16_t)0x0004)                     /*!< configured information of speed: 10Mbit/s */
#define PHY_DUPLEX_STATUS                ((uint16_t)0x0010)                     /*!< configured information of duplex: full-duplex */
#elif(PHY_TYPE == DP83848)
#define PHY_SR                           16U                                    /*!< tranceiver status register */
#define PHY_SPEED_STATUS                 ((uint16_t)0x0002)                     /*!< configured information of speed: 10Mbit/s */
#define PHY_DUPLEX_STATUS                ((uint16_t)0x0004)                     /*!< configured information of duplex: full-duplex */
#elif(PHY_TYPE == YT8512)
#define PHY_SR                           17U
#define PHY_SPEED_STATUS                 ((uint16_t)0x4000)                     /*!< configured information of speed: 10Mbit/s */
#define PHY_DUPLEX_STATUS                ((uint16_t)0x2000)                     /*!< configured information of duplex: full-duplex */
#endif /* PHY_TYPE */

#endif /* _PHY_H_ */
/* ENET definitions */
#define ENET                          ENET_BASE                                        /*!< ENET base address */

/* registers definitions */
#define ENET_MAC_CONFIGURATION                  REG32((ENET) + 0x00000000U)            /*!< ethernet MAC configuration register */
#define ENET_MAC_EXT_CONFIGURATION              REG32((ENET) + 0x00000004U)            /*!< ethernet MAC extended configuration register */
#define ENET_MAC_PACKET_FILTER                  REG32((ENET) + 0x00000008U)            /*!< ethernet MAC packet filter register */
#define ENET_MAC_WATCHDOG_TIMEOUT               REG32((ENET) + 0x0000000CU)            /*!< ethernet MAC watchdog timeout register */
#define ENET_MAC_HASH_TABLE_REG0                REG32((ENET) + 0x00000010U)            /*!< ethernet MAC hash table register 0 */
#define ENET_MAC_HASH_TABLE_REG1                REG32((ENET) + 0x00000014U)            /*!< ethernet MAC hash table register 1 */
#define ENET_MAC_VLAN_TAG_CTRL                  REG32((ENET) + 0x00000050U)            /*!< ethernet MAC vlan tag control register */
#define ENET_MAC_VLAN_TAG_DATA                  REG32((ENET) + 0x00000054U)            /*!< ethernet MAC vlan tag data register */
#define ENET_MAC_VLAN_TAG_FILTERx               REG32((ENET) + 0x00000054U)            /*!< ethernet MAC vlan tag filter register */
#define ENET_MAC_VLAN_HASH_TABLE                REG32((ENET) + 0x00000058U)            /*!< ethernet MAC vlan hash table register */
#define ENET_MAC_VLAN_INCL                      REG32((ENET) + 0x00000060U)            /*!< ethernet MAC Tx queue vlan inclusion register */
#define ENET_MAC_VLAN_INCLx                     REG32((ENET) + 0x00000060U)            /*!< ethernet MAC Tx queue x vlan inclusion register */
#define ENET_MAC_INNER_VLAN_INCL                REG32((ENET) + 0x00000064U)            /*!< ethernet MAC inner vlan tag inclusion or replacement register */
#define ENET_MAC_Q0_TX_FLOW_CTRL                REG32((ENET) + 0x00000070U)            /*!< ethernet MAC queue 0 transmit flow control register */
#define ENET_MAC_RX_FLOW_CTRL                   REG32((ENET) + 0x00000090U)            /*!< ethernet MAC receive flow control register */
#define ENET_MAC_RXQ_CTRL4                      REG32((ENET) + 0x00000094U)            /*!< ethernet MAC receive queue control 4 register */
#define ENET_MAC_RXQ_CTRL0                      REG32((ENET) + 0x000000A0U)            /*!< ethernet MAC receive queue control 0 register */
#define ENET_MAC_RXQ_CTRL1                      REG32((ENET) + 0x000000A4U)            /*!< ethernet MAC receive queue control 1 register */
#define ENET_MAC_RXQ_CTRL2                      REG32((ENET) + 0x000000A8U)            /*!< ethernet MAC receive queue control 2 register */
#define ENET_MAC_INTERRUPT_STATUS               REG32((ENET) + 0x000000B0U)            /*!< ethernet MAC interrupt status register */
#define ENET_MAC_INTERRUPT_ENABLE               REG32((ENET) + 0x000000B4U)            /*!< ethernet MAC interrupt enable register */
#define ENET_MAC_RX_TX_STATUS                   REG32((ENET) + 0x000000B8U)            /*!< ethernet MAC receive transmit status register */
#define ENET_MAC_PMT_CONTROL_STATUS             REG32((ENET) + 0x000000C0U)            /*!< ethernet MAC PMT control and status register */
#define ENET_MAC_RWK_PACKET_FILTER              REG32((ENET) + 0x000000C4U)            /*!< ethernet MAC remote wakeup filter register */
#define ENET_MAC_RWK_FILTERi_BYTE_MASK          REG32((ENET) + 0x000000C4U)            /*!< ethernet MAC remote wakeup filter byte mask register */
#define ENET_MAC_RWK_FILTER0123_COMMAND         REG32((ENET) + 0x000000C4U)            /*!< ethernet MAC remote wakeup filter command register */
#define ENET_MAC_RWK_FILTER0123_OFFSET          REG32((ENET) + 0x000000C4U)            /*!< ethernet MAC remote wakeup filter offset register */
#define ENET_MAC_RWK_FILTERi_CRC                REG32((ENET) + 0x000000C4U)            /*!< ethernet MAC remote wakeup filter crc register */
#define ENET_MAC_LPI_CONTROL_STATUS             REG32((ENET) + 0x000000D0U)            /*!< ethernet MAC LPI control and status register */
#define ENET_MAC_LPI_TIMERS_CONTROL             REG32((ENET) + 0x000000D4U)            /*!< ethernet MAC LPI timers control register */
#define ENET_MAC_LPI_ENTRY_TIMER                REG32((ENET) + 0x000000D4U)            /*!< ethernet MAC LPI timers control register */
#define ENET_MAC_1US_TIC_COUNTER                REG32((ENET) + 0x000000DCU)            /*!< ethernet MAC 1us tic counter register */
#define ENET_MAC_VERSION                        REG32((ENET) + 0x00000110U)            /*!< ethernet MAC version register */
#define ENET_MAC_DEBUG                          REG32((ENET) + 0x00000114U)            /*!< ethernet MAC debug register */
#define ENET_MAC_HW_FEATURE0                    REG32((ENET) + 0x0000011CU)            /*!< ethernet MAC hardware feature 0 register */
#define ENET_MAC_HW_FEATURE1                    REG32((ENET) + 0x00000120U)            /*!< ethernet MAC hardware feature 1 register */
#define ENET_MAC_HW_FEATURE2                    REG32((ENET) + 0x00000124U)            /*!< ethernet MAC hardware feature 2 register */
#define ENET_MAC_HW_FEATURE3                    REG32((ENET) + 0x00000128U)            /*!< ethernet MAC hardware feature 3 register */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS       REG32((ENET) + 0x00000140U)            /*!< ethernet MAC DPP FSM interrupt status register */
#define ENET_MAC_FSM_CONTROL                    REG32((ENET) + 0x00000148U)            /*!< ethernet MAC FSM control register */
#define ENET_MAC_FSM_ACT_TIMER                  REG32((ENET) + 0x0000014CU)            /*!< ethernet MAC FSM act timer register */
#define ENET_MAC_MDIO_ADDRESS                   REG32((ENET) + 0x00000200U)            /*!< ethernet MAC MDIO address register */
#define ENET_MAC_MDIO_DATA                      REG32((ENET) + 0x00000204U)            /*!< ethernet MAC MDIO data register */
#define ENET_MAC_ARP_ADDRESS                    REG32((ENET) + 0x00000210U)            /*!< ethernet MAC ARP adress register */
#define ENET_MAC_CSR_SW_CTRL                    REG32((ENET) + 0x00000230U)            /*!< ethernet MAC CSR software control register */
#define ENET_MAC_FPE_CTRL_STS                   REG32((ENET) + 0x00000234U)            /*!< ethernet MAC FPE control and status register */
#define ENET_MAC_PRESN_TIME_NS                  REG32((ENET) + 0x00000240U)            /*!< ethernet MAC presentation time in ns register */
#define ENET_MAC_PRESN_TIME_UPDT                REG32((ENET) + 0x00000244U)            /*!< ethernet MAC presentation time update register */
#define ENET_MAC_ADDRESS0_HIGH                  REG32((ENET) + 0x00000300U)            /*!< ethernet MAC address0 low register */
#define ENET_MAC_ADDRESS0_LOW                   REG32((ENET) + 0x00000304U)            /*!< ethernet MAC address0 high register */
#define ENET_MAC_ADDRESS1_HIGH                  REG32((ENET) + 0x00000308U)            /*!< ethernet MAC address1 low register */
#define ENET_MAC_ADDRESS1_LOW                   REG32((ENET) + 0x0000030CU)            /*!< ethernet MAC address1 low register */
#define ENET_MAC_ADDRESS2_HIGH                  REG32((ENET) + 0x00000310U)            /*!< ethernet MAC address2 high register */
#define ENET_MAC_ADDRESS2_LOW                   REG32((ENET) + 0x00000314U)            /*!< ethernet MAC address2 low register */
#define ENET_MMC_CONTROL                        REG32((ENET) + 0x00000700U)            /*!< ethernet MMC control register */
#define ENET_MMC_RX_INTERRUPT                   REG32((ENET) + 0x00000704U)            /*!< ethernet MMC receive interrupt register */
#define ENET_MMC_TX_INTERRUPT                   REG32((ENET) + 0x00000708U)            /*!< ethernet MMC transmit interrupt register */
#define ENET_MMC_RX_INTERRUPT_MASK              REG32((ENET) + 0x0000070CU)            /*!< ethernet MMC receive interrupt mask register */
#define ENET_MMC_TX_INTERRUPT_MASK              REG32((ENET) + 0x00000710U)            /*!< ethernet MMC transmit interrupt mask register */
#define ENET_TX_OCTET_COUNT_GOOD_BAD            REG32((ENET) + 0x00000714U)            /*!< ethernet transmit octet count good bad register */
#define ENET_TX_PACKET_COUNT_GOOD_BAD           REG32((ENET) + 0x00000718U)            /*!< ethernet transmit packet count good bad register */
#define ENET_TX_BROADCAST_PACKETS_GOOD          REG32((ENET) + 0x0000071CU)            /*!< ethernet transmit broadcast packets good register */
#define ENET_TX_MULTICAST_PACKETS_GOOD          REG32((ENET) + 0x00000720U)            /*!< ethernet transmit multicast packets good register */
#define ENET_TX_64OCTET_PACKETS_GOOD_BAD        REG32((ENET) + 0x00000724U)            /*!< ethernet transmit 64 octet packets good bad register */
#define ENET_TX_65TO127OCTET_PACKETS_GOOD_BAD   REG32((ENET) + 0x00000728U)            /*!< ethernet transmit 65 to 127 octet packets good bad register */
#define ENET_TX_128TO255OCTET_PACKETS_GOOD_BAD  REG32((ENET) + 0x0000072CU)            /*!< ethernet transmit 128 to 255 octet packets good bad register */
#define ENET_TX_256TO511OCTET_PACKETS_GOOD_BAD  REG32((ENET) + 0x00000730U)            /*!< ethernet transmit 256 to 511 octet packets good bad register */
#define ENET_TX_512TO1023OCTET_PACKETS_GOOD_BAD REG32((ENET) + 0x00000734U)            /*!< ethernet transmit 512 to 1023 octet packets good bad register */
#define ENET_TX_1024TOMAXOCTET_PACKETS_GOOD_BAD REG32((ENET) + 0x00000738U)            /*!< ethernet transmit 1024 to max octet packets good bad register */
#define ENET_TX_UNICAST_PACKETS_GOOD_BAD        REG32((ENET) + 0x0000073CU)            /*!< ethernet transmit unicast packets good bad register */
#define ENET_TX_MULTICAST_PACKETS_GOOD_BAD      REG32((ENET) + 0x00000740U)            /*!< ethernet transmit multicast packets good bad register */
#define ENET_TX_BROADCAST_PACKETS_GOOD_BAD      REG32((ENET) + 0x00000744U)            /*!< ethernet transmit broadcast packets good bad register */
#define ENET_TX_UNDERFLOW_ERROR_PACKETS         REG32((ENET) + 0x00000748U)            /*!< ethernet transmit underflow error packets register */
#define ENET_TX_SINGLE_COLLISION_GOOD_PACKETS   REG32((ENET) + 0x0000074CU)            /*!< ethernet transmit single collision good packets register */
#define ENET_TX_MULTIPLE_COLLISION_GOOD_PACKETS REG32((ENET) + 0x00000750U)            /*!< ethernet transmit multiple collision good packets register */
#define ENET_TX_DEFERRED_PACKETS                REG32((ENET) + 0x00000754U)            /*!< ethernet transmit deferred packets register */
#define ENET_TX_LATE_COLLISION_PACKETS          REG32((ENET) + 0x00000758U)            /*!< ethernet transmit late collision packets register */
#define ENET_TX_EXCESSIVE_COLLISION_PACKETS     REG32((ENET) + 0x0000075CU)            /*!< ethernet transmit excessive collision packets register */
#define ENET_TX_CARRIER_ERROR_PACKETS           REG32((ENET) + 0x00000760U)            /*!< ethernet transmit carrier error packets register */
#define ENET_TX_OCTET_COUNT_GOOD                REG32((ENET) + 0x00000764U)            /*!< ethernet transmit octet count good register */
#define ENET_TX_PACKET_COUNT_GOOD               REG32((ENET) + 0x00000768U)            /*!< ethernet transmit packet count good register */
#define ENET_TX_EXCESSIVE_DEFERRAL_ERROR        REG32((ENET) + 0x0000076CU)            /*!< ethernet transmit excessive deferral error register */
#define ENET_TX_PAUSE_PACKETS                   REG32((ENET) + 0x00000770U)            /*!< ethernet transmit pause packets register */
#define ENET_TX_VLAN_PACKETS_GOOD               REG32((ENET) + 0x00000774U)            /*!< ethernet transmit vlan packets good register */
#define ENET_TX_OSIZE_PACKETS_GOOD              REG32((ENET) + 0x00000778U)            /*!< ethernet transmit oversize packets good register */
#define ENET_RX_PACKETS_COUNT_GOOD_BAD          REG32((ENET) + 0x00000780U)            /*!< ethernet receive packet count good bad register */
#define ENET_RX_OCTET_COUNT_GOOD_BAD            REG32((ENET) + 0x00000784U)            /*!< ethernet receive octet count good bad register */
#define ENET_RX_OCTET_COUNT_GOOD                REG32((ENET) + 0x00000788U)            /*!< ethernet receive octet count good register */
#define ENET_RX_BROADCAST_PACKETS_GOOD          REG32((ENET) + 0x0000078CU)            /*!< ethernet receive broadcast packets good register */
#define ENET_RX_MULTICAST_PACKETS_GOOD          REG32((ENET) + 0x00000790U)            /*!< ethernet receive multicast packets good register */
#define ENET_RX_CRC_ERROR_PACKETS               REG32((ENET) + 0x00000794U)            /*!< ethernet receive crc error packets register */
#define ENET_RX_ALIGNMENT_ERROR_PACKETS         REG32((ENET) + 0x00000798U)            /*!< ethernet receive alignment error packets register */
#define ENET_RX_RUNT_ERROR_PACKETS              REG32((ENET) + 0x0000079CU)            /*!< ethernet receive runt error packets register */
#define ENET_RX_JABBER_ERROR_PACKETS            REG32((ENET) + 0x000007A0U)            /*!< ethernet receive jabber error packets register */
#define ENET_RX_UNDERSIZE_PACKETS_GOOD          REG32((ENET) + 0x000007A4U)            /*!< ethernet receive undersize packets good register */
#define ENET_RX_OVERSIZE_PACKETS_GOOD           REG32((ENET) + 0x000007A8U)            /*!< ethernet receive oversize packets good register */
#define ENET_RX_64OCTET_PACKETS_GOOD_BAD        REG32((ENET) + 0x000007ACU)            /*!< ethernet receive 64 octet packets good bad register */
#define ENET_RX_65TO127OCTET_PACKETS_GOOD_BAD   REG32((ENET) + 0x000007B0U)            /*!< ethernet receive 65 to 127 octet packets good bad register */
#define ENET_RX_128TO255OCTET_PACKETS_GOOD_BAD  REG32((ENET) + 0x000007B4U)            /*!< ethernet receive 128 to 255 octet packets good bad register */
#define ENET_RX_256TO511OCTET_PACKETS_GOOD_BAD  REG32((ENET) + 0x000007B8U)            /*!< ethernet receive 256 to 511 octet packets good bad register */
#define ENET_RX_512TO1023OCTET_PACKETS_GOOD_BAD REG32((ENET) + 0x000007BCU)            /*!< ethernet receive 512 to 1023 octet packets good bad register */
#define ENET_RX_1024TOMAXOCTET_PACKETS_GOOD_BAD REG32((ENET) + 0x000007C0U)            /*!< ethernet receive 1024 to max octet packets good bad register */
#define ENET_RX_UNICAST_PACKETS_GOOD            REG32((ENET) + 0x000007C4U)            /*!< ethernet receive unicast packets good register */
#define ENET_RX_LENGTH_ERROR_PACKETS            REG32((ENET) + 0x000007C8U)            /*!< ethernet receive length error packets register */
#define ENET_RX_OUT_OF_RANGE_TYPE_PACKETS       REG32((ENET) + 0x000007CCU)            /*!< ethernet receive out of range type packets register */
#define ENET_RX_PAUSE_PACKETS                   REG32((ENET) + 0x000007D0U)            /*!< ethernet receive pause packets register */
#define ENET_RX_FIFO_OVERFLOW_PACKETS           REG32((ENET) + 0x000007D4U)            /*!< ethernet receive fifo overflow packets register */
#define ENET_RX_VLAN_PACKETS_GOOD_BAD           REG32((ENET) + 0x000007D8U)            /*!< ethernet receive vlan packets good bad register */
#define ENET_RX_WATCHDOG_ERROR_PACKETS          REG32((ENET) + 0x000007DCU)            /*!< ethernet receive watchdog error packets register */
#define ENET_RX_ERROR_PACKETS                   REG32((ENET) + 0x000007E0U)            /*!< ethernet receive error packets register */
#define ENET_RX_CONTROL_PACKETS_GOOD            REG32((ENET) + 0x000007E4U)            /*!< ethernet receive control packets good register */
#define ENET_TX_LPI_USEC_CNTR                   REG32((ENET) + 0x000007ECU)            /*!< ethernet transmit LPI microseconds counter register */
#define ENET_TX_LPI_TRAN_CNTR                   REG32((ENET) + 0x000007F0U)            /*!< ethernet transmit LPI transition counter register */
#define ENET_RX_LPI_USEC_CNTR                   REG32((ENET) + 0x000007F4U)            /*!< ethernet receive LPI microseconds counter register */
#define ENET_RX_LPI_TRAN_CNTR                   REG32((ENET) + 0x000007F8U)            /*!< ethernet receive LPI transition counter register */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK          REG32((ENET) + 0x00000800U)            /*!< ethernet MMC IPC receive interrupt mask register */
#define ENET_MMC_IPC_RX_INTERRUPT               REG32((ENET) + 0x00000808U)            /*!< ethernet MMC IPC receive interrupt register */
#define ENET_RXIPV4_GOOD_PACKETS                REG32((ENET) + 0x00000810U)            /*!< ethernet receive ipv4 good packets register */
#define ENET_RXIPV4_HEADER_ERROR_PACKETS        REG32((ENET) + 0x00000814U)            /*!< ethernet receive ipv4 header error packets register */
#define ENET_RXIPV4_NO_PAYLOAD_PACKETS          REG32((ENET) + 0x00000818U)            /*!< ethernet receive ipv4 no payload packets register */
#define ENET_RXIPV4_FRAGMENTED_PACKETS          REG32((ENET) + 0x0000081CU)            /*!< ethernet receive ipv4 fragmented packets register */
#define ENET_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS REG32((ENET) + 0x00000820U)            /*!< ethernet receive ipv4 udp checksum disabled packets register */
#define ENET_RXIPV6_GOOD_PACKETS                REG32((ENET) + 0x00000824U)            /*!< ethernet receive ipv6 good packets register */
#define ENET_RXIPV6_HEADER_ERROR_PACKETS        REG32((ENET) + 0x00000828U)            /*!< ethernet receive ipv6 header error packets register */
#define ENET_RXIPV6_NO_PAYLOAD_PACKETS          REG32((ENET) + 0x0000082CU)            /*!< ethernet receive ipv6 no payload packets register */
#define ENET_RXUDP_GOOD_PACKETS                 REG32((ENET) + 0x00000830U)            /*!< ethernet receive udp good packets register */
#define ENET_RXUDP_ERROR_PACKETS                REG32((ENET) + 0x00000834U)            /*!< ethernet receive udp error packets register */
#define ENET_RXTCP_GOOD_PACKETS                 REG32((ENET) + 0x00000838U)            /*!< ethernet receive tcp good packets register */
#define ENET_RXTCP_ERROR_PACKETS                REG32((ENET) + 0x0000083CU)            /*!< ethernet receive tcp error packets register */
#define ENET_RXICMP_GOOD_PACKETS                REG32((ENET) + 0x00000840U)            /*!< ethernet receive icmp good packets register */
#define ENET_RXICMP_ERROR_PACKETS               REG32((ENET) + 0x00000844U)            /*!< ethernet receive icmp error packets register */
#define ENET_RXIPV4_GOOD_OCTETS                 REG32((ENET) + 0x00000850U)            /*!< ethernet receive ipv4 good octets register */
#define ENET_RXIPV4_HEADER_ERROR_OCTETS         REG32((ENET) + 0x00000854U)            /*!< ethernet receive ipv4 header error octets register */
#define ENET_RXIPV4_NO_PAYLOAD_OCTETS           REG32((ENET) + 0x00000858U)            /*!< ethernet receive ipv4 no payload octets register */
#define ENET_RXIPV4_FRAGMENTED_OCTETS           REG32((ENET) + 0x0000085CU)            /*!< ethernet receive ipv4 fragmented octets register */
#define ENET_RXIPV4_UDP_CHECKSUM_DISABLED_OCTETS REG32((ENET) + 0x00000860U)            /*!< ethernet receive ipv4 udp checksum disabled octets register */
#define ENET_RXIPV6_GOOD_OCTETS                 REG32((ENET) + 0x00000864U)            /*!< ethernet receive ipv6 good octets register */
#define ENET_RXIPV6_HEADER_ERROR_OCTETS         REG32((ENET) + 0x00000868U)            /*!< ethernet receive ipv6 header error octets register */
#define ENET_RXIPV6_NO_PAYLOAD_OCTETS           REG32((ENET) + 0x0000086CU)            /*!< ethernet receive ipv6 no payload octets register */
#define ENET_RXUDP_GOOD_OCTETS                  REG32((ENET) + 0x00000870U)            /*!< ethernet receive udp good octets register */
#define ENET_RXUDP_ERROR_OCTETS                 REG32((ENET) + 0x00000874U)            /*!< ethernet receive udp error octets register */
#define ENET_RXTCP_GOOD_OCTETS                  REG32((ENET) + 0x00000878U)            /*!< ethernet receive tcp good octets register */
#define ENET_RXTCP_ERROR_OCTETS                 REG32((ENET) + 0x0000087CU)            /*!< ethernet receive tcp error octets register */
#define ENET_RXICMP_GOOD_OCTETS                 REG32((ENET) + 0x00000880U)            /*!< ethernet receive icmp good octets register */
#define ENET_RXICMP_ERROR_OCTETS                REG32((ENET) + 0x00000884U)            /*!< ethernet receive icmp error octets register */
#define ENET_MMC_FPE_TX_INTERRUPT               REG32((ENET) + 0x000008A0U)            /*!< ethernet MMC FPE transmit interrupt register */
#define ENET_MMC_FPE_TX_INTERRUPT_MASK          REG32((ENET) + 0x000008A4U)            /*!< ethernet MMC FPE transmit interrupt mask register */
#define ENET_MMC_FPE_TX_FRAGMENT_CNTR           REG32((ENET) + 0x000008A8U)            /*!< ethernet MMC FPE transmit fragment counter register */
#define ENET_MMC_TX_HOLD_REQ_CNTR               REG32((ENET) + 0x000008ACU)            /*!< ethernet MMC FPE hold request counter register */
#define ENET_MMC_FPE_RX_INTERRUPT               REG32((ENET) + 0x000008C0U)            /*!< ethernet MMC FPE receive interrupt register */
#define ENET_MMC_FPE_RX_INTERRUPT_MASK          REG32((ENET) + 0x000008C4U)            /*!< ethernet MMC FPE receive interrupt mask register */
#define ENET_MMC_RX_PACKETS_ASSEMBLY_ERR_CNTR   REG32((ENET) + 0x000008C8U)            /*!< ethernet MMC receive packets assembly error counter register */
#define ENET_MMC_RX_PACKETS_SMD_ERR_CNTR        REG32((ENET) + 0x000008CCU)            /*!< ethernet MMC receive packets SMD error counter register */
#define ENET_MMC_RX_PACKETS_ASSEMBLY_OK_CNTR    REG32((ENET) + 0x000008D0U)            /*!< ethernet MMC receive packets assembly ok counter register */
#define ENET_MMC_RX_FPE_FRAGMENT_CNTR           REG32((ENET) + 0x000008D4U)            /*!< ethernet MMC receive FPE fragment counter register */
#define ENET_MAC_L3_L4_CONTROL0                 REG32((ENET) + 0x00000900U)            /*!< ethernet MAC layer 3 and layer 4 control register, x = 0,1,2,3 */
#define ENET_MAC_LAYER4_ADDRESS0                REG32((ENET) + 0x00000904U)            /*!< ethernet MAC layer 4 address register 0 */
#define ENET_MAC_LAYER3_ADDR0_REG0              REG32((ENET) + 0x00000910U)            /*!< ethernet MAC layer 3 address 0 register 0 */
#define ENET_MAC_LAYER3_ADDR1_REG0              REG32((ENET) + 0x00000914U)            /*!< ethernet MAC layer 3 address 1 register 0 */
#define ENET_MAC_LAYER3_ADDR2_REG0              REG32((ENET) + 0x00000918U)            /*!< ethernet MAC layer 3 address 2 register 0 */
#define ENET_MAC_LAYER3_ADDR3_REG0              REG32((ENET) + 0x0000091CU)            /*!< ethernet MAC layer 3 address 3 register 0 */
#define ENET_MAC_L3_L4_CONTROL1                 REG32((ENET) + 0x00000930U)            /*!< ethernet MAC layer 3 and layer 4 control register 1 */
#define ENET_MAC_LAYER4_ADDRESS1                REG32((ENET) + 0x00000934U)            /*!< ethernet MAC layer 4 address register 1 */
#define ENET_MAC_LAYER3_ADDR0_REG1              REG32((ENET) + 0x00000940U)            /*!< ethernet MAC layer 3 address 0 register 1 */
#define ENET_MAC_LAYER3_ADDR1_REG1              REG32((ENET) + 0x00000944U)            /*!< ethernet MAC layer 3 address 1 register 1 */
#define ENET_MAC_LAYER3_ADDR2_REG1              REG32((ENET) + 0x00000948U)            /*!< ethernet MAC layer 3 address 2 register 1 */
#define ENET_MAC_LAYER3_ADDR3_REG1              REG32((ENET) + 0x0000094CU)            /*!< ethernet MAC layer 3 address 3 register 1 */
#define ENET_MAC_L3_L4_CONTROL2                 REG32((ENET) + 0x00000960U)            /*!< ethernet MAC layer 3 and layer 4 control register 2 */
#define ENET_MAC_LAYER4_ADDRESS2                REG32((ENET) + 0x00000964U)            /*!< ethernet MAC layer 4 address register 2 */
#define ENET_MAC_LAYER3_ADDR0_REG2              REG32((ENET) + 0x00000970U)            /*!< ethernet MAC layer 3 address 0 register 2 */
#define ENET_MAC_LAYER3_ADDR1_REG2              REG32((ENET) + 0x00000974U)            /*!< ethernet MAC layer 3 address 1 register 2 */
#define ENET_MAC_LAYER3_ADDR2_REG2              REG32((ENET) + 0x00000978U)            /*!< ethernet MAC layer 3 address 2 register 2 */
#define ENET_MAC_LAYER3_ADDR3_REG2              REG32((ENET) + 0x0000097CU)            /*!< ethernet MAC layer 3 address 3 register 2 */
#define ENET_MAC_L3_L4_CONTROL3                 REG32((ENET) + 0x00000990U)            /*!< ethernet MAC layer 3 and layer 4 control register 3 */
#define ENET_MAC_LAYER4_ADDRESS3                REG32((ENET) + 0x00000994U)            /*!< ethernet MAC layer 4 address register 3 */
#define ENET_MAC_LAYER3_ADDR0_REG3              REG32((ENET) + 0x000009A0U)            /*!< ethernet MAC layer 3 address 0 register 3 */
#define ENET_MAC_LAYER3_ADDR1_REG3              REG32((ENET) + 0x000009A4U)            /*!< ethernet MAC layer 3 address 1 register 3 */
#define ENET_MAC_LAYER3_ADDR2_REG3              REG32((ENET) + 0x000009A8U)            /*!< ethernet MAC layer 3 address 2 register 3 */
#define ENET_MAC_LAYER3_ADDR3_REG3              REG32((ENET) + 0x000009ACU)            /*!< ethernet MAC layer 3 address 3 register 3 */
#define ENET_MAC_INDIR_ACCESS_CTRL              REG32((ENET) + 0x00000A70U)            /*!< ethernet MAC indirect access control register */
#define ENET_MAC_INDIR_ACCESS_DATA              REG32((ENET) + 0x00000A74U)            /*!< ethernet MAC indirect access data register */
#define ENET_MAC_TMRQ_REGSx                     REG32((ENET) + 0x00000A74U)            /*!< ethernet MAC type match receive queue number register */
#define ENET_MAC_TIMESTAMP_CONTROL              REG32((ENET) + 0x00000B00U)            /*!< ethernet MAC timestamp control register */
#define ENET_MAC_SUB_SECOND_INCREMENT           REG32((ENET) + 0x00000B04U)            /*!< ethernet MAC timestamp control register */
#define ENET_MAC_SYSTEM_TIME_SECONDS            REG32((ENET) + 0x00000B08U)            /*!< ethernet MAC system time sencond register */
#define ENET_MAC_SYSTEM_TIME_NANOSECONDS        REG32((ENET) + 0x00000B0CU)            /*!< ethernet MAC system time nanosencond register */
#define ENET_MAC_SYSTEM_TIME_SECONDS_UPDATE     REG32((ENET) + 0x00000B10U)            /*!< ethernet MAC system time sencond update register */
#define ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE REG32((ENET) + 0x00000B14U)            /*!< ethernet MAC system time nanosencond update register */
#define ENET_MAC_TIMESTAMP_ADDEND               REG32((ENET) + 0x00000B18U)            /*!< ethernet MAC timestamp addend register */
#define ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS REG32((ENET) + 0x00000B1CU)           /*!< ethernet MAC system time higher word sencond register */
#define ENET_MAC_TIMESTAMP_STATUS               REG32((ENET) + 0x00000B20U)            /*!< ethernet MAC timestamp status register */
#define ENET_MAC_RX_DOMAIN_TIME_INCR            REG32((ENET) + 0x00000B24U)            /*!< ethernet MAC receive domain time increment register */
#define ENET_MAC_TX_DOMAIN_TIME_INCR            REG32((ENET) + 0x00000B28U)            /*!< ethernet MAC transmit domain time increment register */
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS REG32((ENET) + 0x00000B30U)           /*!< ethernet MAC transmit timestamp status nanoseconds register */
#define ENET_MAC_TX_TIMESTAMP_STATUS_SECONDS    REG32((ENET) + 0x00000B34U)            /*!< ethernet MAC transmit timestamp status seconds register */
#define ENET_MAC_TIMESTAMP_INGRESS_ASYM_CORR    REG32((ENET) + 0x00000B50U)            /*!< ethernet MAC timestamp ingress asymmetry correction register */
#define ENET_MAC_TIMESTAMP_EGRESS_ASYM_CORR     REG32((ENET) + 0x00000B54U)            /*!< ethernet MAC timestamp egress asymmetry correction register */
#define ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND REG32((ENET) + 0x00000B58U)         /*!< ethernet MAC timestamp ingress correction nanoseconds register */
#define ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND REG32((ENET) + 0x00000B5CU)          /*!< ethernet MAC timestamp egress correction nanoseconds register */
#define ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC REG32((ENET) + 0x00000B60U)         /*!< ethernet MAC timestamp ingress correction subnanoseconds register */
#define ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC REG32((ENET) + 0x00000B64U)          /*!< ethernet MAC timestamp egress correction subnanoseconds register */
#define ENET_MAC_TIMESTAMP_INGRESS_LATENCY    REG32((ENET) + 0x00000B68U)              /*!< ethernet MAC timestamp ingress latency register */
#define ENET_MAC_TIMESTAMP_EGRESS_LATENCY     REG32((ENET) + 0x00000B6CU)              /*!< ethernet MAC timestamp egress latency correction register */
#define ENET_MAC_PPS_CONTROL                  REG32((ENET) + 0x00000B70U)              /*!< ethernet MAC PPS control register */
#define ENET_MAC_PPS0_TARGET_TIME_SECONDS     REG32((ENET) + 0x00000B80U)              /*!< ethernet MAC PPS 0 target time seconds register */
#define ENET_MAC_PPS0_TARGET_TIME_NANOSECONDS REG32((ENET) + 0x00000B84U)              /*!< ethernet MAC PPS 0 target time nanoseconds register */
#define ENET_MAC_PPS0_INTERVAL                REG32((ENET) + 0x00000B88U)              /*!< ethernet MAC PPS 0 interval register */
#define ENET_MAC_PPS0_WIDTH                   REG32((ENET) + 0x00000B8CU)              /*!< ethernet MAC PPS 0 width register */
#define ENET_MAC_PPS1_TARGET_TIME_SECONDS     REG32((ENET) + 0x00000B90U)              /*!< ethernet MAC PPS 1 target time seconds register */
#define ENET_MAC_PPS1_TARGET_TIME_NANOSECONDS REG32((ENET) + 0x00000B94U)              /*!< ethernet MAC PPS 1 target time nanoseconds register */
#define ENET_MAC_PPS1_INTERVAL                REG32((ENET) + 0x00000B98U)              /*!< ethernet MAC PPS 1 interval register */
#define ENET_MAC_PPS1_WIDTH                   REG32((ENET) + 0x00000B9CU)              /*!< ethernet MAC PPS 1 width register */
#define ENET_MAC_PPS2_TARGET_TIME_SECONDS     REG32((ENET) + 0x00000BA0U)              /*!< ethernet MAC PPS 2 target time seconds register */
#define ENET_MAC_PPS2_TARGET_TIME_NANOSECONDS REG32((ENET) + 0x00000BA4U)              /*!< ethernet MAC PPS 2 target time nanoseconds register */
#define ENET_MAC_PPS2_INTERVAL                REG32((ENET) + 0x00000BA8U)              /*!< ethernet MAC PPS 2 interval register */
#define ENET_MAC_PPS2_WIDTH                   REG32((ENET) + 0x00000BACU)              /*!< ethernet MAC PPS 2 width register */
#define ENET_MAC_PPS3_TARGET_TIME_SECONDS     REG32((ENET) + 0x00000BB0U)              /*!< ethernet MAC PPS 3 target time seconds register */
#define ENET_MAC_PPS3_TARGET_TIME_NANOSECONDS REG32((ENET) + 0x00000BB4U)              /*!< ethernet MAC PPS 3 target time nanoseconds register */
#define ENET_MAC_PPS3_INTERVAL                REG32((ENET) + 0x00000BB8U)              /*!< ethernet MAC PPS 3 interval register */
#define ENET_MAC_PPS3_WIDTH                   REG32((ENET) + 0x00000BBCU)              /*!< ethernet MAC PPS 3 width register */
#define ENET_MTL_OPERATION_MODE               REG32((ENET) + 0x00000C00U)              /*!< ethernet MTL operation mode register */
#define ENET_MTL_DBG_CTL                      REG32((ENET) + 0x00000C08U)              /*!< ethernet MTL debug control register */
#define ENET_MTL_DBG_STS                      REG32((ENET) + 0x00000C0CU)              /*!< ethernet MTL debug status register */
#define ENET_MTL_FIFO_DEBUG_DATA              REG32((ENET) + 0x00000C10U)              /*!< ethernet MTL debug status register */
#define ENET_MTL_INTERRUPT_STATUS             REG32((ENET) + 0x00000C20U)              /*!< ethernet MTL interrupt status register */
#define ENET_MTL_RXQ_DMA_MAP0                 REG32((ENET) + 0x00000C30U)              /*!< ethernet MTL receive queue and dma channel map 0 register */
#define ENET_MTL_TBS_CTRL                     REG32((ENET) + 0x00000C40U)              /*!< ethernet MTL TBS control register */
#define ENET_MTL_EST_CONTROL                  REG32((ENET) + 0x00000C50U)              /*!< ethernet MTL EST control register */
#define ENET_MTL_EST_EXT_CONTROL              REG32((ENET) + 0x00000C54U)              /*!< ethernet MTL EST extention control register */
#define ENET_MTL_EST_STATUS                   REG32((ENET) + 0x00000C58U)              /*!< ethernet MTL EST status register */
#define ENET_MTL_EST_SCH_ERROR                REG32((ENET) + 0x00000C60U)              /*!< ethernet MTL EST schedule error register */
#define ENET_MTL_EST_FRM_SIZE_ERROR           REG32((ENET) + 0x00000C64U)              /*!< ethernet MTL EST frame size error register */
#define ENET_MTL_EST_FRM_SIZE_CAPTURE         REG32((ENET) + 0x00000C68U)              /*!< ethernet MTL EST frame size capture register */
#define ENET_MTL_EST_INTR_ENABLE              REG32((ENET) + 0x00000C70U)              /*!< ethernet MTL EST interrupt enable register */
#define ENET_MTL_EST_GCL_CONTROL              REG32((ENET) + 0x00000C80U)              /*!< ethernet MTL EST GCL control register */
#define ENET_MTL_EST_GCL_DATA                 REG32((ENET) + 0x00000C84U)              /*!< ethernet MTL EST GCL data register */
#define ENET_MTL_FPE_CTRL_STS                 REG32((ENET) + 0x00000C90U)              /*!< ethernet MTL EST FPE control and status register */
#define ENET_MTL_FPE_ADVANCE                  REG32((ENET) + 0x00000C94U)              /*!< ethernet MTL EST FPE advance register */
#define ENET_MTL_RXP_CONTROL_STATUS           REG32((ENET) + 0x00000CA0U)              /*!< ethernet MTL receive parser control and status register */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS REG32((ENET) + 0x00000CA4U)              /*!< ethernet MTL receive parser interrupt control and status register */
#define ENET_MTL_RXP_DROP_CNT                 REG32((ENET) + 0x00000CA8U)              /*!< ethernet MTL receive parser drop counter register */
#define ENET_MTL_RXP_ERROR_CNT                REG32((ENET) + 0x00000CACU)              /*!< ethernet MTL receive parser error counter register */
#define ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS REG32((ENET) + 0x00000CB0U)           /*!< ethernet MTL receive parser indirect access control and status register */
#define ENET_MTL_RXP_INDIRECT_ACC_DATA        REG32((ENET) + 0x00000CB4U)              /*!< ethernet MTL receive parser indirect access data register */
#define ENET_MTL_RXP_BYPASS_CNT               REG32((ENET) + 0x00000CB8U)              /*!< ethernet MTL receive parser bypass counter register */
#define ENET_MTL_ECC_CONTROL                  REG32((ENET) + 0x00000CC0U)              /*!< ethernet MTL ECC control register */
#define ENET_MTL_SAFETY_INTERRUPT_STATUS      REG32((ENET) + 0x00000CC4U)              /*!< ethernet MTL safety interrupt status register */
#define ENET_MTL_ECC_INTERRUPT_ENABLE         REG32((ENET) + 0x00000CC8U)              /*!< ethernet MTL ECC interrupt enable register */
#define ENET_MTL_ECC_INTERRUPT_STATUS         REG32((ENET) + 0x00000CCCU)              /*!< ethernet MTL ECC interrupt status register */
#define ENET_MTL_ECC_ERR_STS_RCTL             REG32((ENET) + 0x00000CD0U)              /*!< ethernet MTL ECC error status and control register */
#define ENET_MTL_ECC_ERR_ADDR_STATUS          REG32((ENET) + 0x00000CD4U)              /*!< ethernet MTL ECC error address status register */
#define ENET_MTL_ECC_ERR_CNTR_STATUS          REG32((ENET) + 0x00000CD8U)              /*!< ethernet MTL ECC error counter status register */
#define ENET_MTL_DPP_CONTROL                  REG32((ENET) + 0x00000CE0U)              /*!< ethernet MTL DPP control register */
#define ENET_MTL_DPP_ECC_EIC                  REG32((ENET) + 0x00000CE4U)              /*!< ethernet MTL DPP and ECC error injection register */
#define ENET_MTL_TXQ0_OPERATION_MODE          REG32((ENET) + 0x00000D00U)              /*!< ethernet MTL transmit queue 0 operation mode register */
#define ENET_MTL_TXQ0_UNDERFLOW               REG32((ENET) + 0x00000D04U)              /*!< ethernet MTL transmit queue 0 underflow register */
#define ENET_MTL_TXQ0_DEBUG                   REG32((ENET) + 0x00000D08U)              /*!< ethernet MTL transmit queue 0 debug register */
#define ENET_MTL_TXQ0_ETS_STATUS              REG32((ENET) + 0x00000D14U)              /*!< ethernet MTL transmit queue 0 ETS status register */
#define ENET_MTL_TXQ0_QUANTUM_WEIGHT          REG32((ENET) + 0x00000D18U)              /*!< ethernet MTL transmit queue 0 quantum weight register */
#define ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS  REG32((ENET) + 0x00000D2CU)              /*!< ethernet MTL queue 0 interrupt control and status register */
#define ENET_MTL_RXQ0_OPERATION_MODE          REG32((ENET) + 0x00000D30U)              /*!< ethernet MTL receive queue 0 operation mode register */
#define ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT REG32((ENET) + 0x00000D34U)           /*!< ethernet MTL receive queue 0 missed packet overflow counter register */
#define ENET_MTL_RXQ0_DEBUG                   REG32((ENET) + 0x00000D38U)              /*!< ethernet MTL receive queue 0 debug register */
#define ENET_MTL_RXQ0_CONTROL                 REG32((ENET) + 0x00000D3CU)              /*!< ethernet MTL receive queue 0 control register */
#define ENET_MTL_TXQ1_OPERATION_MODE          REG32((ENET) + 0x00000D40U)              /*!< ethernet MTL transmit queue 1 operation mode register */
#define ENET_MTL_TXQ1_UNDERFLOW               REG32((ENET) + 0x00000D44U)              /*!< ethernet MTL transmit queue 1 underflow register */
#define ENET_MTL_TXQ1_DEBUG                   REG32((ENET) + 0x00000D48U)              /*!< ethernet MTL transmit queue 1 debug register */
#define ENET_MTL_TXQ1_ETS_CONTROL             REG32((ENET) + 0x00000D50U)              /*!< ethernet MTL transmit queue 1 ETS control register */
#define ENET_MTL_TXQ1_ETS_STATUS              REG32((ENET) + 0x00000D54U)              /*!< ethernet MTL transmit queue 1 ETS status register */
#define ENET_MTL_TXQ1_QUANTUM_WEIGHT          REG32((ENET) + 0x00000D58U)              /*!< ethernet MTL transmit queue 1 quantum weight register */
#define ENET_MTL_TXQ1_SENDSLOPECREDIT         REG32((ENET) + 0x00000D5CU)              /*!< ethernet MTL transmit queue 1 send slope credit register */
#define ENET_MTL_TXQ1_HICREDIT                REG32((ENET) + 0x00000D60U)              /*!< ethernet MTL transmit queue 1 high credit register */
#define ENET_MTL_TXQ1_LOCREDIT                REG32((ENET) + 0x00000D64U)              /*!< ethernet MTL transmit queue 1 low credit register */
#define ENET_MTL_Q1_INTERRUPT_CONTROL_STATUS  REG32((ENET) + 0x00000D6CU)              /*!< ethernet MTL queue 1 interrupt control and status register */
#define ENET_MTL_RXQ1_OPERATION_MODE          REG32((ENET) + 0x00000D70U)              /*!< ethernet MTL receive queue 1 operation mode register */
#define ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT REG32((ENET) + 0x00000D74U)           /*!< ethernet MTL receive queue 1 missed packet overflow counter register */
#define ENET_MTL_RXQ1_DEBUG                   REG32((ENET) + 0x00000D78U)              /*!< ethernet MTL receive queue 1 debug register */
#define ENET_MTL_RXQ1_CONTROL                 REG32((ENET) + 0x00000D7CU)              /*!< ethernet MTL receive queue 1 control register */
#define ENET_DMA_MODE                         REG32((ENET) + 0x00001000U)              /*!< ethernet DMA mode register */
#define ENET_DMA_SYSBUS_MODE                  REG32((ENET) + 0x00001004U)              /*!< ethernet DMA sysbus mode register */
#define ENET_DMA_INTERRUPT_STATUS             REG32((ENET) + 0x00001008U)              /*!< ethernet DMA interrupt status register */
#define ENET_DMA_DEBUG_STATUS0                REG32((ENET) + 0x0000100CU)              /*!< ethernet DMA debug status 0 register */
#define ENET_DMA_TBS_CTRL0                    REG32((ENET) + 0x00001050U)              /*!< ethernet DMA TBS control 0 register */
#define ENET_DMA_SAFETY_INTERRUPT_STATUS      REG32((ENET) + 0x00001080U)              /*!< ethernet DMA safety interrupt status register */
#define ENET_DMA_CH0_CONTROL                  REG32((ENET) + 0x00001100U)              /*!< ethernet DMA channel 0 control register */
#define ENET_DMA_CH0_TX_CONTROL               REG32((ENET) + 0x00001104U)              /*!< ethernet DMA channel 0 transmit control register */
#define ENET_DMA_CH0_RX_CONTROL               REG32((ENET) + 0x00001108U)              /*!< ethernet DMA channel 0 receive control register */
#define ENET_DMA_CH0_TXDESC_ADDRESS           REG32((ENET) + 0x00001114U)              /*!< ethernet DMA channel 0 transmit descriptor address register */
#define ENET_DMA_CH0_RXDESC_ADDRESS           REG32((ENET) + 0x0000111CU)              /*!< ethernet DMA channel 0 receive descriptor address register */
#define ENET_DMA_CH0_TXDESC_TAIL_POINTER      REG32((ENET) + 0x00001120U)              /*!< ethernet DMA channel 0 transmit descriptor tail pointer register */
#define ENET_DMA_CH0_RXDESC_TAIL_POINTER      REG32((ENET) + 0x00001128U)              /*!< ethernet DMA channel 0 receive descriptor tail pointer register */
#define ENET_DMA_CH0_TXDESC_RING_LENGTH       REG32((ENET) + 0x0000112CU)              /*!< ethernet DMA channel 0 transmit descriptor ring length register */
#define ENET_DMA_CH0_RX_CONTROL2              REG32((ENET) + 0x00001130U)              /*!< ethernet DMA channel 0 receive control 2 register */
#define ENET_DMA_CH0_INTERRUPT_ENABLE         REG32((ENET) + 0x00001134U)              /*!< ethernet DMA channel 0 interrupt enable register */
#define ENET_DMA_CH0_RX_INTERRUPT_WATCHDOG_TIMER REG32((ENET) + 0x00001138U)           /*!< ethernet DMA channel 0 receive interrupt watchdog timer register */
#define ENET_DMA_CH0_SLOT_FUNCTION_CONTROL_STATUS REG32((ENET) + 0x0000113CU)          /*!< ethernet DMA channel 0 slot function control status register */
#define ENET_DMA_CH0_CURRENT_APP_TXDESC       REG32((ENET) + 0x00001144U)              /*!< ethernet DMA channel 0 current application transmit descriptor register */
#define ENET_DMA_CH0_CURRENT_APP_RXDESC       REG32((ENET) + 0x0000114CU)              /*!< ethernet DMA channel 0 current application receive descriptor register */
#define ENET_DMA_CH0_CURRENT_APP_TXBUFFER     REG32((ENET) + 0x00001154U)              /*!< ethernet DMA channel 0 current application transmit buffer register */
#define ENET_DMA_CH0_CURRENT_APP_RXBUFFER     REG32((ENET) + 0x0000115CU)              /*!< ethernet DMA channel 0 current application transmit buffer register */
#define ENET_DMA_CH0_STATUS                   REG32((ENET) + 0x00001160U)              /*!< ethernet DMA channel 0 status register */
#define ENET_DMA_CH0_MISS_FRAME_CNT           REG32((ENET) + 0x00001164U)              /*!< ethernet DMA channel 0 miss frame counter register */
#define ENET_DMA_CH0_RXP_ACCEPT_CNT           REG32((ENET) + 0x00001168U)              /*!< ethernet DMA channel 0 receive parser accept counter register */

#define ENET_DMA_CH1_CONTROL                  REG32((ENET) + 0x00001180U)              /*!< ethernet DMA channel 1 control register */
#define ENET_DMA_CH1_TX_CONTROL               REG32((ENET) + 0x00001184U)              /*!< ethernet DMA channel 1 transmit control register */
#define ENET_DMA_CH1_RX_CONTROL               REG32((ENET) + 0x00001188U)              /*!< ethernet DMA channel 1 receive control register */
#define ENET_DMA_CH1_TXDESC_ADDRESS           REG32((ENET) + 0x00001194U)              /*!< ethernet DMA channel 1 transmit descriptor address register */
#define ENET_DMA_CH1_RXDESC_ADDRESS           REG32((ENET) + 0x0000119CU)              /*!< ethernet DMA channel 1 receive descriptor address register */
#define ENET_DMA_CH1_TXDESC_TAIL_POINTER      REG32((ENET) + 0x000011A0U)              /*!< ethernet DMA channel 1 transmit descriptor tail pointer register */
#define ENET_DMA_CH1_RXDESC_TAIL_POINTER      REG32((ENET) + 0x000011A8U)              /*!< ethernet DMA channel 1 receive descriptor tail pointer register */
#define ENET_DMA_CH1_TXDESC_RING_LENGTH       REG32((ENET) + 0x000011ACU)              /*!< ethernet DMA channel 1 transmit descriptor ring length register */
#define ENET_DMA_CH1_RX_CONTROL2              REG32((ENET) + 0x000011B0U)              /*!< ethernet DMA channel 1 receive control 2 register */
#define ENET_DMA_CH1_INTERRUPT_ENABLE         REG32((ENET) + 0x000011B4U)              /*!< ethernet DMA channel 1 interrupt enable register */
#define ENET_DMA_CH1_RX_INTERRUPT_WATCHDOG_TIMER REG32((ENET) + 0x000011B8U)           /*!< ethernet DMA channel 1 receive interrupt watchdog timer register */
#define ENET_DMA_CH1_SLOT_FUNCTION_CONTROL_STATUS REG32((ENET) + 0x000011BCU)          /*!< ethernet DMA channel 1 slot function control status register */
#define ENET_DMA_CH1_CURRENT_APP_TXDESC       REG32((ENET) + 0x000011C4U)              /*!< ethernet DMA channel 1 current application transmit descriptor register */
#define ENET_DMA_CH1_CURRENT_APP_RXDESC       REG32((ENET) + 0x000011CCU)              /*!< ethernet DMA channel 1 current application receive descriptor register */
#define ENET_DMA_CH1_CURRENT_APP_TXBUFFER     REG32((ENET) + 0x000011D4U)              /*!< ethernet DMA channel 1 current application transmit buffer register, */
#define ENET_DMA_CH1_CURRENT_APP_RXBUFFER     REG32((ENET) + 0x000011DCU)              /*!< ethernet DMA channel 1 current application transmit buffer register */
#define ENET_DMA_CH1_STATUS                   REG32((ENET) + 0x000011E0U)              /*!< ethernet DMA channel 1 status register */
#define ENET_DMA_CH1_MISS_FRAME_CNT           REG32((ENET) + 0x000011E4U)              /*!< ethernet DMA channel 1 miss frame counter register */
#define ENET_DMA_CH1_RXP_ACCEPT_CNT           REG32((ENET) + 0x000011E8U)              /*!< ethernet DMA channel 1 receive parser accept counter register */

/* bits definitions */
/* ENET_MAC_CONFIGURATION */
#define ENET_MAC_CONFIGURATION_RE                               BIT(0)                 /*!< receiver enable */
#define ENET_MAC_CONFIGURATION_TE                               BIT(1)                 /*!< transmitter enable */
#define ENET_MAC_CONFIGURATION_PRELEN                           BITS(2,3)              /*!< preamble length for transmit packets */
#define ENET_MAC_CONFIGURATION_DC                               BIT(4)                 /*!< deferral check */
#define ENET_MAC_CONFIGURATION_BL                               BITS(5,6)              /*!< back-off limit */
#define ENET_MAC_CONFIGURATION_DR                               BIT(8)                 /*!< retry disable */
#define ENET_MAC_CONFIGURATION_DCRS                             BIT(9)                 /*!< disable carrier sense during transmission */
#define ENET_MAC_CONFIGURATION_DO                               BIT(10)                /*!< disable Receive Own */
#define ENET_MAC_CONFIGURATION_ECRSFD                           BIT(11)                /*!< enable carrier sense before transmission in full-duplex mode */
#define ENET_MAC_CONFIGURATION_LM                               BIT(12)                /*!< loopback mode */
#define ENET_MAC_CONFIGURATION_DM                               BIT(13)                /*!< duplex mode */
#define ENET_MAC_CONFIGURATION_FES                              BIT(14)                /*!< fast Ethernet speed */
#define ENET_MAC_CONFIGURATION_JE                               BIT(16)                /*!< jumbo packet enable */
#define ENET_MAC_CONFIGURATION_JD                               BIT(17)                /*!< fast ethernet speed */
#define ENET_MAC_CONFIGURATION_WD                               BIT(19)                /*!< watchdog disable */
#define ENET_MAC_CONFIGURATION_ACS                              BIT(20)                /*!< automatic pad or CRC stripping */
#define ENET_MAC_CONFIGURATION_CST                              BIT(21)                /*!< CRC stripping for type packets */
#define ENET_MAC_CONFIGURATION_S2KP                             BIT(22)                /*!< IEEE 802.3as support for 2K Packets */
#define ENET_MAC_CONFIGURATION_GPSLCE                           BIT(23)                /*!< giant packet size limit control enable */
#define ENET_MAC_CONFIGURATION_IPG                              BITS(24,26)            /*!< Inter-packet gap */
#define ENET_MAC_CONFIGURATION_IPC                              BIT(27)                /*!< IP frame checksum offload */
#define ENET_MAC_CONFIGURATION_SARC                             BITS(28,30)            /*!< source address insertion or replacement control */
#define ENET_MAC_CONFIGURATION_ARPEN                            BIT(31)                /*!< ARP offload enable */

/* ENET_MAC_EXT_CONFIGURATION */
#define ENET_MAC_EXT_CONFIGURATION_GPSL                         BITS(0,13)             /*!< giant packet size limit */
#define ENET_MAC_EXT_CONFIGURATION_DCRCC                        BIT(16)                /*!< disable CRC checking for received packets */
#define ENET_MAC_EXT_CONFIGURATION_SPEN                         BIT(17)                /*!< slow protocol detection enable */
#define ENET_MAC_EXT_CONFIGURATION_USP                          BIT(18)                /*!< unicast slow protocol packet detect */
#define ENET_MAC_EXT_CONFIGURATION_PDC                          BIT(19)                /*!< packet duplication control */
#define ENET_MAC_EXT_CONFIGURATION_EIPGEN                       BIT(24)                /*!< extended inter-packet gap enable */
#define ENET_MAC_EXT_CONFIGURATION_EIPG                         BITS(25,29)            /*!< extended inter-packet gap */
#define ENET_MAC_EXT_CONFIGURATION_APDIM                        BIT(30)                /*!< ARP packet drop if IP address mismatch */

/* ENET_MAC_PACKET_FILTER */
#define ENET_MAC_PACKET_FILTER_PR                               BIT(0)                /*!< promiscuous mode */
#define ENET_MAC_PACKET_FILTER_HUC                              BIT(1)                /*!< hash unicast filter */
#define ENET_MAC_PACKET_FILTER_HMC                              BIT(2)                /*!< hash multicast filter */
#define ENET_MAC_PACKET_FILTER_DAIF                             BIT(3)                /*!< destination address inverse filtering */
#define ENET_MAC_PACKET_FILTER_PM                               BIT(4)                /*!< multicast filter disable */
#define ENET_MAC_PACKET_FILTER_DBF                              BIT(5)                /*!< disable Broadcast Packets */
#define ENET_MAC_PACKET_FILTER_PCF                              BITS(6,7)             /*!< pass control packets */
#define ENET_MAC_PACKET_FILTER_SAIF                             BIT(8)                /*!< source address inverse filtering */
#define ENET_MAC_PACKET_FILTER_SAF                              BIT(9)                /*!< source address filter */
#define ENET_MAC_PACKET_FILTER_HPF                              BIT(10)               /*!< hash or perfect filter */
#define ENET_MAC_PACKET_FILTER_VTFE                             BIT(16)               /*!< VLAN tag filter enable */
#define ENET_MAC_PACKET_FILTER_IPFE                             BIT(20)               /*!< layer 3 and layer 4 filter enable */
#define ENET_MAC_PACKET_FILTER_DNTU                             BIT(21)               /*!< drop non-TCP/UDP over IP packets */
#define ENET_MAC_PACKET_FILTER_RA                               BIT(31)               /*!< receive all */

/* ENET_MAC_WATCHDOG_TIMEOUT */
#define ENET_MAC_WATCHDOG_TIMEOUT_WTO                           BITS(0,3)             /*!< watchdog timeout */
#define ENET_MAC_WATCHDOG_TIMEOUT_PWE                           BIT(8)                /*!< programmable watchdog enable */
#define ENET_MAC_WATCHDOG_TIMEOUT_JTO                           BITS(16,19)           /*!< jabber timeout */
#define ENET_MAC_WATCHDOG_TIMEOUT_PJE                           BIT(24)               /*!< programmable jabber enable */

/* ENET_MAC_HASH_TABLE_REG0 */
#define ENET_MAC_HASH_TABLE_REG0_HT31T0                         BITS(0,31)            /*!< MAC hash table first 32 bits */

/* ENET_MAC_HASH_TABLE_REG1 */
#define ENET_MAC_HASH_TABLE_REG1_HT63T32                        BITS(0,31)            /*!< MAC hash table second 32 bits */

/* ENET_MAC_VLAN_TAG_CTRL */
#define ENET_MAC_VLAN_TAG_CTRL_OB                               BIT(0)                /*!< operation busy */
#define ENET_MAC_VLAN_TAG_CTRL_CT                               BIT(1)                /*!< command type */
#define ENET_MAC_VLAN_TAG_CTRL_OFS                              BITS(2,3)             /*!< offset */
#define ENET_MAC_VLAN_TAG_CTRL_ETV                              BIT(16)               /*!< 12-bit VLAN tag comparison */
#define ENET_MAC_VLAN_TAG_CTRL_VTIM                             BIT(17)               /*!< VLAN tag inverse match enable */
#define ENET_MAC_VLAN_TAG_CTRL_ESVL                             BIT(18)               /*!< enable S-VLAN */
#define ENET_MAC_VLAN_TAG_CTRL_ERSVLM                           BIT(19)               /*!< enable receive S-VLAN match for VLAN hash filtering */
#define ENET_MAC_VLAN_TAG_CTRL_DOVLTC                           BIT(20)               /*!< disable VLAN type check for VLAN hash filtering */
#define ENET_MAC_VLAN_TAG_CTRL_EVLS                             BITS(21,22)           /*!< enable VLAN tag stripping on receive */
#define ENET_MAC_VLAN_TAG_CTRL_EVLRXS                           BIT(24)               /*!< enable VLAN tag in rx status */
#define ENET_MAC_VLAN_TAG_CTRL_VTHM                             BIT(25)               /*!< VLAN Tag hash table match enable */
#define ENET_MAC_VLAN_TAG_CTRL_EDVLP                            BIT(26)               /*!< enable double VLAN processing */
#define ENET_MAC_VLAN_TAG_CTRL_ERIVLT                           BIT(27)               /*!< enable inner VLAN tag comparison */
#define ENET_MAC_VLAN_TAG_CTRL_EIVLS                            BITS(28,29)           /*!< enable inner VLAN tag stripping on receive */
#define ENET_MAC_VLAN_TAG_CTRL_EIVLRXS                          BIT(31)               /*!< enable Inner VLAN tag in Rx status */

/* ENET_MAC_VLAN_TAG_DATA */
#define ENET_MAC_VLAN_TAG_DATA_VID                              BITS(0,15)            /*!< VLAN tag ID */
#define ENET_MAC_VLAN_TAG_DATA_VEN                              BIT(16)               /*!< VLAN tag enable */
#define ENET_MAC_VLAN_TAG_DATA_ETV                              BIT(17)               /*!< 12bits or 16bits VLAN comparison */
#define ENET_MAC_VLAN_TAG_DATA_DOVLTC                           BIT(18)               /*!< disable VLAN type comparison */
#define ENET_MAC_VLAN_TAG_DATA_ERSVLM                           BIT(19)               /*!< enable S-VLAN match for received frames */
#define ENET_MAC_VLAN_TAG_DATA_ERIVLT                           BIT(20)               /*!< enable inner VLAN tag comparison */
#define ENET_MAC_VLAN_TAG_DATA_DMACHEN                          BIT(24)               /*!< DMA channel number enable */
#define ENET_MAC_VLAN_TAG_DATA_DMACHN                           BIT(25)               /*!< DMA channel number */

/* ENET_MAC_VLAN_TAG_FILTERx */
#define ENET_MAC_VLAN_TAG_FILTERx_VID                          BITS(0,15)            /*!< VLAN tag ID */
#define ENET_MAC_VLAN_TAG_FILTERx_VEN                          BIT(16)               /*!< VLAN tag enable */
#define ENET_MAC_VLAN_TAG_FILTERx_ETV                          BIT(17)               /*!< 12bits or 16bits VLAN comparison */
#define ENET_MAC_VLAN_TAG_FILTERx_DOVLTC                       BIT(18)               /*!< disable VLAN type comparison */
#define ENET_MAC_VLAN_TAG_FILTERx_ERSVLM                       BIT(19)               /*!< enable S-VLAN match for received frames */
#define ENET_MAC_VLAN_TAG_FILTERx_ERIVLT                       BIT(20)               /*!< enable inner VLAN tag comparison */
#define ENET_MAC_VLAN_TAG_FILTERx_DMACHEN                      BIT(24)               /*!< DMA channel number enable */
#define ENET_MAC_VLAN_TAG_FILTERx_DMACHN                       BIT(25)               /*!< DMA channel number */

/* ENET_MAC_VLAN_HASH_TABLE */
#define ENET_MAC_VLAN_HASH_TABLE_VLHT                          BITS(0,15)            /*!< VLAN hash table */

/* ENET_MAC_VLAN_INCL */
#define ENET_MAC_VLAN_INCL_VLT                                 BITS(0,15)            /*!< VLAN tag for transmit packets */
#define ENET_MAC_VLAN_INCL_VLC                                 BITS(16,17)           /*!< VLAN tag control in transmit packets */
#define ENET_MAC_VLAN_INCL_VLP                                 BIT(18)               /*!< VLAN priority control */
#define ENET_MAC_VLAN_INCL_CSVL                                BIT(19)               /*!< C-VLAN or S-VLAN */
#define ENET_MAC_VLAN_INCL_VLTI                                BIT(20)               /*!< VLAN tag input */
#define ENET_MAC_VLAN_INCL_CBTI                                BIT(21)               /*!< channel based tag insertion */
#define ENET_MAC_VLAN_INCL_ADDR                                BIT(24)               /*!< address */
#define ENET_MAC_VLAN_INCL_RDWR                                BIT(30)               /*!< read write control */
#define ENET_MAC_VLAN_INCL_BUSY                                BIT(31)               /*!< busy */

/* ENET_MAC_VLAN_INCLx */
#define ENET_MAC_VLAN_INCLx_VLT                                BITS(0,15)            /*!< VLAN tag for transmit packets */
#define ENET_MAC_VLAN_INCLx_CSVL                               BIT(19)               /*!< C-VLAN or S-VLAN */

/* ENET_MAC_INNER_VLAN_INCL */
#define ENET_MAC_INNER_VLAN_INCL_VLT                           BITS(0,15)            /*!< VLAN tag for transmit packets */
#define ENET_MAC_INNER_VLAN_INCL_VLC                           BITS(16,17)           /*!< VLAN tag control in transmit packets */
#define ENET_MAC_INNER_VLAN_INCL_VLP                           BIT(18)               /*!< VLAN priority control */
#define ENET_MAC_INNER_VLAN_INCL_CSVL                          BIT(19)               /*!< C-VLAN or S-VLAN */
#define ENET_MAC_INNER_VLAN_INCL_VLTI                          BIT(20)               /*!< VLAN tag input */

/* ENET_MAC_Q0_TX_FLOW_CTRL */
#define ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA                       BIT(0)                /*!< flow control busy / back pressure activate */
#define ENET_MAC_Q0_TX_FLOW_CTRL_TFE                           BIT(1)                /*!< transmit flow control enable */
#define ENET_MAC_Q0_TX_FLOW_CTRL_PLT                           BITS(4,6)             /*!< pause low threshold */
#define ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ                          BIT(7)                /*!< disable zero-quanta pause */
#define ENET_MAC_Q0_TX_FLOW_CTRL_PT                            BITS(16,31)           /*!< pause time */


/* ENET_MAC_RX_FLOW_CTRL */
#define ENET_MAC_RX_FLOW_CTRL_RFE                              BIT(0)                /*!< receive flow control enable */
#define ENET_MAC_RX_FLOW_CTRL_UP                               BIT(1)                /*!< unicast pause packet detect */

/* ENET_MAC_RXQ_CTRL4 */
#define ENET_MAC_RXQ_CTRL4_UFFQE                               BIT(0)                /*!< unicast address filter fail packets queuing enable */
#define ENET_MAC_RXQ_CTRL4_UFFQ                                BIT(1)                /*!< unicast address filter fail packets queue */
#define ENET_MAC_RXQ_CTRL4_MFFQE                               BIT(8)                /*!< multicast address filter fail packets queuing enable */
#define ENET_MAC_RXQ_CTRL4_MFFQ                                BIT(9)                /*!< multicast address filter fail packets queue */
#define ENET_MAC_RXQ_CTRL4_VFFQE                               BIT(16)               /*!< VLAN tag filter fail packets queuing enable */
#define ENET_MAC_RXQ_CTRL4_VFFQ                                BIT(17)               /*!< VLAN tag filter fail packets queue */
#define ENET_MAC_RXQ_CTRL4_UDC                                 BIT(31)               /*!< unicast packet duplication control */

/* ENET_MAC_RXQ_CTRL0 */
#define ENET_MAC_RXQ_CTRL0_RXQ0EN                              BITS(0,1)             /*!< receive queue 0 enable */
#define ENET_MAC_RXQ_CTRL0_RXQ1EN                              BITS(2,3)             /*!< receive queue 1 enable */

/* ENET_MAC_RXQ_CTRL1 */
#define ENET_MAC_RXQ_CTRL1_AVCPQ                               BITS(0,2)             /*!< AV untagged control packets queue */
#define ENET_MAC_RXQ_CTRL1_PTPQ                                BITS(4,6)             /*!< PTP packets queue */
#define ENET_MAC_RXQ_CTRL1_UPQ                                 BITS(12,14)           /*!< untagged packet queue */
#define ENET_MAC_RXQ_CTRL1_MCBCQ                               BITS(16,18)           /*!< multicast and broadcast queue */
#define ENET_MAC_RXQ_CTRL1_MCBCQEN                             BIT(20)               /*!< multicast and broadcast queue enable */
#define ENET_MAC_RXQ_CTRL1_TACPQE                              BIT(21)               /*!< tagged AV control packets queuing enable */
#define ENET_MAC_RXQ_CTRL1_TPQC                                BITS(22,23)           /*!< tagged PTP over ethernet packets queuing control */
#define ENET_MAC_RXQ_CTRL1_FPRQ                                BITS(24,26)           /*!< frame preemption residue queue */
#define ENET_MAC_RXQ_CTRL1_OMCBCQ                              BIT(28)               /*!< over-riding MC-BC queue priority select */
#define ENET_MAC_RXQ_CTRL1_TBRQE                               BIT(29)               /*!< type field based Rx queuing enable */

/* ENET_MAC_RXQ_CTRL2 */
#define ENET_MAC_RXQ_CTRL2_PSRQ0                               BITS(0,7)             /*!< priorities selected in the receive queue 0 */
#define ENET_MAC_RXQ_CTRL2_PSRQ1                               BITS(8,15)            /*!< priorities selected in the receive queue 1 */

/* ENET_MAC_INTERRUPT_STATUS */
#define ENET_MAC_INTERRUPT_STATUS_PHYIS                        BIT(3)                /*!< PHY interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_PMTIS                        BIT(4)                /*!< PMT interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_LPIIS                        BIT(5)                /*!< LPI interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_MMCIS                        BIT(8)                /*!< MMC interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_MMCRXIS                      BIT(9)                /*!< MMC receive interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_MMCTXIS                      BIT(10)               /*!< MMC transmit interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_MMCRXIPIS                    BIT(11)               /*!< MMC receive checksum offload interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_TSIS                         BIT(12)               /*!< timestamp interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_TXSTSIS                      BIT(13)               /*!< transmit interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_RXSTSIS                      BIT(14)               /*!< receive interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_FPEIS                        BIT(17)               /*!< frame preemption interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_MDIOIS                       BIT(18)               /*!< MDIO transmit interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_MFTIS                        BIT(19)               /*!< MMC FPE transmit interrupt status */
#define ENET_MAC_INTERRUPT_STATUS_MFRIS                        BIT(20)               /*!< MMC FPE receive interrupt status */

/* ENET_MAC_INTERRUPT_ENABLE */
#define ENET_MAC_INTERRUPT_ENABLE_PHYIE                        BIT(3)                /*!< PHY interrupt enable */
#define ENET_MAC_INTERRUPT_ENABLE_PMTIE                        BIT(4)                /*!< PMT interrupt enable */
#define ENET_MAC_INTERRUPT_ENABLE_LPIIE                        BIT(5)                /*!< LPI interrupt enable */
#define ENET_MAC_INTERRUPT_ENABLE_TSIE                         BIT(12)               /*!< timestamp interrupt enable */
#define ENET_MAC_INTERRUPT_ENABLE_TXSTSIE                      BIT(13)               /*!< transmit interrupt enable */
#define ENET_MAC_INTERRUPT_ENABLE_RXSTSIE                      BIT(14)               /*!< receive interrupt enable */
#define ENET_MAC_INTERRUPT_ENABLE_FPEIE                        BIT(17)               /*!< frame preemption interrupt enable */
#define ENET_MAC_INTERRUPT_ENABLE_MDIOIE                       BIT(18)               /*!< MDIO transmit interrupt enable */

/* ENET_MAC_RX_TX_STATUS */
#define ENET_MAC_RX_TX_STATUS_TJT                              BIT(0)                /*!< transmit jabber timeout */
#define ENET_MAC_RX_TX_STATUS_NCARR                            BIT(1)                /*!< no carrier */
#define ENET_MAC_RX_TX_STATUS_LCARR                            BIT(2)                /*!< loss of carrier */
#define ENET_MAC_RX_TX_STATUS_EXDEF                            BIT(3)                /*!< excessive deferral */
#define ENET_MAC_RX_TX_STATUS_LCOL                             BIT(4)                /*!< late collision */
#define ENET_MAC_RX_TX_STATUS_EXCOL                            BIT(5)                /*!< excessive collisions */
#define ENET_MAC_RX_TX_STATUS_RWT                              BIT(8)                /*!< receive watchdog timeout */

/* ENET_MAC_PMT_CONTROL_STATUS */
#define ENET_MAC_PMT_CONTROL_STATUS_PWRDWN                     BIT(0)                /*!< power down */
#define ENET_MAC_PMT_CONTROL_STATUS_MGKPKTEN                   BIT(1)                /*!< magic packet enable */
#define ENET_MAC_PMT_CONTROL_STATUS_RWKPKTEN                   BIT(2)                /*!< wakeup frame enable */
#define ENET_MAC_PMT_CONTROL_STATUS_MGKPRCVD                   BIT(5)                /*!< magic packet received */
#define ENET_MAC_PMT_CONTROL_STATUS_RWKPRCVD                   BIT(6)                /*!< remote wake-up packet received */
#define ENET_MAC_PMT_CONTROL_STATUS_GLBLUCAST                  BIT(9)                /*!< global unicast */
#define ENET_MAC_PMT_CONTROL_STATUS_RWKPFE                     BIT(10)               /*!< remote wake-up packet forwarding enable */
#define ENET_MAC_PMT_CONTROL_STATUS_RWKPTR                     BITS(24,28)           /*!< remote wake-up FIFO pointer */
#define ENET_MAC_PMT_CONTROL_STATUS_RWKFILTRST                 BIT(31)               /*!< remote wake-up packet filter register pointer reset */

/* ENET_MAC_RWK_PACKET_FILTER */
#define ENET_MAC_RWK_PACKET_FILTER_WKUPFRMFTR                  BITS(0,31)            /*!< RWK packet filter */

/* ENET_MAC_RWK_FILTERi_BYTE_MASK */
#define ENET_MAC_RWK_FILTERi_BYTE_MASK_Filter0_Byte_Mask       BITS(0,31)            /*!< filter0 32-bit mask */

/* ENET_MAC_RWK_FILTER0123_COMMAND */
#define ENET_MAC_RWK_FILTER0123_COMMAND_Filter0_Command        BITS(0,3)             /*!< filter0 command */
#define ENET_MAC_RWK_FILTER0123_COMMAND_Filter1_Command        BITS(8,11)            /*!< filter1 command */
#define ENET_MAC_RWK_FILTER0123_COMMAND_Filter2_Command        BITS(16,19)           /*!< filter2 command */
#define ENET_MAC_RWK_FILTER0123_COMMAND_Filter3_Command        BITS(24,27)           /*!< filter3 command */

/* ENET_MAC_RWK_FILTER0123_OFFSET */
#define ENET_MAC_RWK_FILTER0123_OFFSET_Filter0_Offset          BITS(0,7)             /*!< filter0 offset */
#define ENET_MAC_RWK_FILTER0123_OFFSET_Filter1_Offset          BITS(8,15)            /*!< filter1 offset */
#define ENET_MAC_RWK_FILTER0123_OFFSET_Filter2_Offset          BITS(16,23)           /*!< filter2 offset */
#define ENET_MAC_RWK_FILTER0123_OFFSET_Filter3_Offset          BITS(24,31)           /*!< filter3 offset */

/* ENET_MAC_RWK_FILTERi_CRC */
#define ENET_MAC_RWK_FILTERi_CRC_Filter0_CRC                   BITS(0,15)             /*!< filter0 CRC-16 */
#define ENET_MAC_RWK_FILTERi_CRC_Filter1_CRC                   BITS(16,31)            /*!< filter1 CRC-16 */

/* ENET_MAC_LPI_CONTROL_STATUS */
#define ENET_MAC_LPI_CONTROL_STATUS_TLPIEN                     BIT(0)                 /*!< transmit LPI entry */
#define ENET_MAC_LPI_CONTROL_STATUS_TLPIEX                     BIT(1)                 /*!< transmit LPI exit */
#define ENET_MAC_LPI_CONTROL_STATUS_RLPIEN                     BIT(2)                 /*!< receive LPI entry */
#define ENET_MAC_LPI_CONTROL_STATUS_RLPIEX                     BIT(3)                 /*!< receive LPI exit */
#define ENET_MAC_LPI_CONTROL_STATUS_TLPIST                     BIT(8)                 /*!< transmit LPI state */
#define ENET_MAC_LPI_CONTROL_STATUS_RLPIST                     BIT(9)                 /*!< receive LPI state */
#define ENET_MAC_LPI_CONTROL_STATUS_LPIEN                      BIT(16)                /*!< LPI enable */
#define ENET_MAC_LPI_CONTROL_STATUS_PLS                        BIT(17)                /*!< PHY link status */
#define ENET_MAC_LPI_CONTROL_STATUS_LPITXA                     BIT(19)                /*!< LPI Tx automate */
#define ENET_MAC_LPI_CONTROL_STATUS_LPIATE                     BIT(20)                /*!< LPI timer enable */
#define ENET_MAC_LPI_CONTROL_STATUS_LPITCSE                    BIT(21)                /*!< LPI Tx clock stop enable */

/* ENET_MAC_LPI_TIMERS_CONTROL */
#define ENET_MAC_LPI_TIMERS_CONTROL_TWT                        BITS(0,15)             /*!< LPI TW timer */
#define ENET_MAC_LPI_TIMERS_CONTROL_LST                        BITS(16,25)            /*!< LPI LS timer */

/* ENET_MAC_LPI_ENTRY_TIMER */
#define ENET_MAC_LPI_ENTRY_TIMER_LPIET                         BITS(3,19)             /*!< LPI entry timer */

/* ENET_MAC_1US_TIC_COUNTER */
#define ENET_MAC_1US_TIC_COUNTER_TIC_1US_CNTR                  BITS(0,11)             /*!< 1US tic counter */

/* ENET_MAC_VERSION */
#define ENET_MAC_VERSION_IPVER                                 BITS(0,7)              /*!< IP version */
#define ENET_MAC_VERSION_CFGVER                                BITS(8,15)             /*!< IP configuration version */

/* ENET_MAC_DEBUG */
#define ENET_MAC_DEBUG_RPESTS                                  BIT(0)                 /*!< MAC MII receive protocol engine status */
#define ENET_MAC_DEBUG_RFCFCSTS                                BITS(1,2)              /*!< reset on read */
#define ENET_MAC_DEBUG_TPESTS                                  BIT(16)                /*!< MAC MII transmit protocol engine status */
#define ENET_MAC_DEBUG_TFCSTS                                  BITS(17,18)            /*!< MAC transmit packet controller status */

/* ENET_MAC_HW_FEATURE0 */
#define ENET_MAC_HW_FEATURE0_MIISEL                            BIT(0)                 /*!< 10 or 100 mbps support */
#define ENET_MAC_HW_FEATURE0_HDSEL                             BIT(2)                 /*!< half-duplex support */
#define ENET_MAC_HW_FEATURE0_VLHASH                            BIT(4)                 /*!< VLAN hash filter selected */
#define ENET_MAC_HW_FEATURE0_SMASEL                            BIT(5)                 /*!< SMA (MDIO) interface */
#define ENET_MAC_HW_FEATURE0_RWKSEL                            BIT(6)                 /*!< PMT remote wake-up packet enable */
#define ENET_MAC_HW_FEATURE0_MGKSEL                            BIT(7)                 /*!< PMT magic packet enable */
#define ENET_MAC_HW_FEATURE0_MMCSEL                            BIT(8)                 /*!< RMON module enable */
#define ENET_MAC_HW_FEATURE0_ARPOFFSEL                         BIT(9)                 /*!< ARP Offload Enabled */
#define ENET_MAC_HW_FEATURE0_TSSEL                             BIT(12)                /*!< IEEE 1588-2008 timestamp enabled */
#define ENET_MAC_HW_FEATURE0_EEESEL                            BIT(13)                /*!< energy efficient ethernet enabled */
#define ENET_MAC_HW_FEATURE0_TXCOESEL                          BIT(14)                /*!< transmit checksum offload enabled */
#define ENET_MAC_HW_FEATURE0_RXCOESEL                          BIT(16)                /*!< receive checksum offload */
#define ENET_MAC_HW_FEATURE0_ADDMACADRSEL                      BITS(18,22)            /*!< MAC addresses 1-31 selected */
#define ENET_MAC_HW_FEATURE0_MACADR32SEL                       BIT(23)                /*!< MAC addresses 32-63 selected */
#define ENET_MAC_HW_FEATURE0_MACADR64SEL                       BIT(24)                /*!< MAC addresses 64-127 selected */
#define ENET_MAC_HW_FEATURE0_TSSTSSEL                          BITS(25,26)            /*!< timestamp system time source */
#define ENET_MAC_HW_FEATURE0_SAVLANINS                         BIT(27)                /*!< source address or VLAN insertion enable */
#define ENET_MAC_HW_FEATURE0_ACTPHYSEL                         BITS(28,31)            /*!< active phy selected */

/* ENET_MAC_HW_FEATURE1 */
#define ENET_MAC_HW_FEATURE1_RXFIFOSIZE                        BITS(0,4)              /*!< MTL receive FIFO size */
#define ENET_MAC_HW_FEATURE1_SPRAM                             BIT(5)                 /*!< single port RAM enable */
#define ENET_MAC_HW_FEATURE1_TXFIFOSIZE                        BITS(6,10)             /*!< MTL transmit FIFO size */
#define ENET_MAC_HW_FEATURE1_OSTEN                             BIT(11)                /*!< one-Step timestamping enable */
#define ENET_MAC_HW_FEATURE1_PTOEN                             BIT(12)                /*!< PTP offload enable */
#define ENET_MAC_HW_FEATURE1_ADVTHWORD                         BIT(13)                /*!< IEEE 1588 high word register enable */
#define ENET_MAC_HW_FEATURE1_ADDR64                            BITS(14,15)            /*!< address width */
#define ENET_MAC_HW_FEATURE1_DCBEN                             BIT(16)                /*!< DCB feature enable */
#define ENET_MAC_HW_FEATURE1_SPHEN                             BIT(17)                /*!< PTP offload enable */
#define ENET_MAC_HW_FEATURE1_TSOEN                             BIT(18)                /*!< TCP segmentation offload enable */
#define ENET_MAC_HW_FEATURE1_DBGMEMA                           BIT(19)                /*!< DMA debug registers enable */
#define ENET_MAC_HW_FEATURE1_AVSEL                             BIT(20)                /*!< AV feature enable */
#define ENET_MAC_HW_FEATURE1_RAVSEL                            BIT(21)                /*!< Rx side only AV feature enable */
#define ENET_MAC_HW_FEATURE1_POUOST                            BIT(22)                /*!< one step for PTP over UDP/IP feature enable */
#define ENET_MAC_HW_FEATURE1_HASHTBLSZ                         BITS(24,25)            /*!< hash table size */
#define ENET_MAC_HW_FEATURE1_L3L4FNUM                          BITS(27,30)            /*!< total number of L3 or L4 filters */

/* ENET_MAC_HW_FEATURE2 */
#define ENET_MAC_HW_FEATURE2_RXQCNT                            BITS(0,3)              /*!< number of MTL receive queues */
#define ENET_MAC_HW_FEATURE2_TXQCNT                            BITS(6,9)              /*!< number of MTL transmit queues */
#define ENET_MAC_HW_FEATURE2_RXCHCNT                           BITS(12,15)            /*!< number of DMA receive channels */
#define ENET_MAC_HW_FEATURE2_RDCSZ                             BITS(16,17)            /*!< Rx DMA descriptor cache size in terms of 16-bytes descriptors */
#define ENET_MAC_HW_FEATURE2_TXCHCNT                           BITS(18,21)            /*!< number of DMA transmit channels */
#define ENET_MAC_HW_FEATURE2_TDCSZ                             BITS(22,23)            /*!< Tx DMA descriptor cache size in terms of 16-bytes descriptors */
#define ENET_MAC_HW_FEATURE2_PPSOUTNUM                         BITS(24,26)            /*!< number of PPS outputs */
#define ENET_MAC_HW_FEATURE2_AUXSNAPNUM                        BITS(28,30)            /*!< number of auxiliary snapshot inputs */

/* ENET_MAC_HW_FEATURE3 */
#define ENET_MAC_HW_FEATURE3_NRVF                              BITS(0,2)              /*!< number of extended VLAN tag filters enabled */
#define ENET_MAC_HW_FEATURE3_CBTISEL                           BIT(4)                 /*!< queue / Channel based VLAN tag insertion on Tx enable */
#define ENET_MAC_HW_FEATURE3_DVLAN                             BIT(5)                 /*!< double VLAN tag processing selected */
#define ENET_MAC_HW_FEATURE3_PDUPSEL                           BIT(9)                 /*!< broadcast / Multicast packet duplication */
#define ENET_MAC_HW_FEATURE3_FRPSEL                            BIT(10)                /*!< flexible receive parser selected */
#define ENET_MAC_HW_FEATURE3_FRPBS                             BITS(11,12)            /*!< flexible receive parser buffer size */
#define ENET_MAC_HW_FEATURE3_FRPES                             BITS(13,14)            /*!< flexible receive parser table entries size */
#define ENET_MAC_HW_FEATURE3_ESTSEL                            BIT(16)                /*!< enhancements to scheduled traffic enable */
#define ENET_MAC_HW_FEATURE3_ESTDEP                            BITS(17,19)            /*!< depth of the gate control list */
#define ENET_MAC_HW_FEATURE3_ESTWID                            BITS(20,21)            /*!< width of the time interval field in the gate control list */
#define ENET_MAC_HW_FEATURE3_FPESEL                            BIT(26)                /*!< frame preemption enable */
#define ENET_MAC_HW_FEATURE3_TBSSEL                            BIT(27)                /*!< time based scheduling enable */
#define ENET_MAC_HW_FEATURE3_ASP                               BITS(28,29)            /*!< automotive safety package */

/* ENET_MAC_DPP_FSM_INTERRUPT_STATUS */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_ATPES                BIT(0)                 /*!< application transmit interface parity checker error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_RDPES                BIT(2)                 /*!< read descriptor parity checker error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_MPES                 BIT(3)                 /*!< MTL data path parity checker error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_MTSPES               BIT(4)                 /*!< MTL TX status data path parity checker error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_ARPES                BIT(5)                 /*!< application receive interface data path parity error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_CWPES                BIT(6)                 /*!< CSR Write data path parity checker error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_TTES                 BIT(8)                 /*!< Tx FSM timeout error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_RTES                 BIT(9)                 /*!< Rx FSM timeout error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_ATES                 BIT(11)                /*!< APP FSM timeout error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_PTES                 BIT(12)                /*!< PTP FSM timeout error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_MSTTES               BIT(16)                /*!< master read / write timeout error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_FSMPES               BIT(24)                /*!< FSM state parity error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_MTBUPES              BIT(25)                /*!< MAC TBU data path parity checker error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_MTFCPES              BIT(26)                /*!< MAC TFC data path parity checker error status */
#define ENET_MAC_DPP_FSM_INTERRUPT_STATUS_MRWCPES              BIT(27)                /*!< MTL RWC data path parity checker error Status */

/* ENET_MAC_FSM_CONTROL */
#define ENET_MAC_FSM_CONTROL_TMOUTEN                           BIT(0)                 /*!< FSM timeout feature */
#define ENET_MAC_FSM_CONTROL_PRTYEN                            BIT(1)                 /*!< FSM parity feature */
#define ENET_MAC_FSM_CONTROL_TTEIN                             BIT(8)                 /*!< Tx FSM timeout error injection */
#define ENET_MAC_FSM_CONTROL_RTEIN                             BIT(9)                 /*!< Rx FSM timeout error injection */
#define ENET_MAC_FSM_CONTROL_CTEIN                             BIT(10)                /*!< CSR FSM timeout error injection */
#define ENET_MAC_FSM_CONTROL_ATEIN                             BIT(11)                /*!< APP FSM timeout error jnjection */
#define ENET_MAC_FSM_CONTROL_PTEIN                             BIT(12)                /*!< PTP FSM timeout error injection */
#define ENET_MAC_FSM_CONTROL_TPEIN                             BIT(16)                /*!< Tx FSM parity error injection */
#define ENET_MAC_FSM_CONTROL_RPEIN                             BIT(17)                /*!< Rx FSM parity error injection */
#define ENET_MAC_FSM_CONTROL_CPEIN                             BIT(18)                /*!< CSR FSM one hot protection error injection */
#define ENET_MAC_FSM_CONTROL_APEIN                             BIT(19)                /*!< APP FSM parity error injection */
#define ENET_MAC_FSM_CONTROL_PPEIN                             BIT(20)                /*!< PTP FSM parity error injection */
#define ENET_MAC_FSM_CONTROL_TLGRNML                           BIT(24)                /*!< Tx large/normal mode select */
#define ENET_MAC_FSM_CONTROL_RLGRNML                           BIT(25)                /*!< Rx large/normal mode select */
#define ENET_MAC_FSM_CONTROL_CLGRNML                           BIT(26)                /*!< CSR large/normal mode select */
#define ENET_MAC_FSM_CONTROL_ALGRNML                           BIT(27)                /*!< APP large/normal mode select */
#define ENET_MAC_FSM_CONTROL_PLGRNML                           BIT(28)                /*!< PTP large/normal mode select */

/* ENET_MAC_FSM_ACT_TIMER */
#define ENET_MAC_FSM_ACT_TIMER_TMR                             BITS(0,9)              /*!< CSR clocks for 1us tic */
#define ENET_MAC_FSM_ACT_TIMER_NTMRMD                          BITS(16,19)            /*!< normal mode timeout value */
#define ENET_MAC_FSM_ACT_TIMER_LTMRMD                          BITS(20,23)            /*!< large mode timeout value */

/* ENET_MAC_MDIO_ADDRESS */
#define ENET_MAC_MDIO_ADDRESS_GB                               BIT(0)                 /*!< busy */
#define ENET_MAC_MDIO_ADDRESS_C45E                             BIT(1)                 /*!< Clause 45 phy enable */
#define ENET_MAC_MDIO_ADDRESS_GOC_0                            BIT(2)                 /*!< operation command 0 */
#define ENET_MAC_MDIO_ADDRESS_GOC_1                            BIT(3)                 /*!< operation command 1 */
#define ENET_MAC_MDIO_ADDRESS_SKAP                             BIT(4)                 /*!< skip address packet */
#define ENET_MAC_MDIO_ADDRESS_CR                               BITS(8,11)             /*!< CSR clock range */
#define ENET_MAC_MDIO_ADDRESS_NTC                              BITS(12,14)            /*!< number of trailing clocks */
#define ENET_MAC_MDIO_ADDRESS_RDA                              BITS(16,20)            /*!< PHY register */
#define ENET_MAC_MDIO_ADDRESS_PA                               BITS(21,25)            /*!< PHY address */
#define ENET_MAC_MDIO_ADDRESS_BTB                              BIT(26)                /*!< back to back transactions */
#define ENET_MAC_MDIO_ADDRESS_PSE                              BIT(27)                /*!< preamble suppression enable */

/* ENET_MAC_MDIO_DATA */
#define ENET_MAC_MDIO_DATA_GD                                  BITS(0,15)            /*!< PHY data */
#define ENET_MAC_MDIO_DATA_RA                                  BITS(16,31)           /*!< register address */

/* ENET_MAC_ARP_ADDRESS */
#define ENET_MAC_ARP_ADDRESS_ARPPA                             BITS(0,31)            /*!< ARP protocol address */

/* ENET_MAC_CSR_SW_CTRL */
#define ENET_MAC_CSR_SW_CTRL_RCWE                              BIT(0)                /*!< register clear on write 1 enable */
#define ENET_MAC_CSR_SW_CTRL_SEEN                              BIT(8)                /*!< slave error response enable */

/* ENET_MAC_FPE_CTRL_STS */
#define ENET_MAC_FPE_CTRL_STS_EFPE                            BIT(0)                /*!< enable Tx frame preemption */
#define ENET_MAC_FPE_CTRL_STS_SVER                            BIT(1)                /*!< send verify mPacket */
#define ENET_MAC_FPE_CTRL_STS_SRSP                            BIT(2)                /*!< send respond mPacket */
#define ENET_MAC_FPE_CTRL_STS_ARV                             BIT(3)                /*!< auto generate respond mPacket on receiving verify mPacket */
#define ENET_MAC_FPE_CTRL_STS_RVER                            BIT(16)               /*!< received verify frame */
#define ENET_MAC_FPE_CTRL_STS_RRSP                            BIT(17)               /*!< received respond frame */
#define ENET_MAC_FPE_CTRL_STS_TVER                            BIT(18)               /*!< transmitted verify frame */
#define ENET_MAC_FPE_CTRL_STS_TRSP                            BIT(19)               /*!< transmitted respond frame */

/* ENET_MAC_PRESN_TIME_NS */
#define ENET_MAC_PRESN_TIME_NS_MPTN                            BITS(0,31)            /*!< MAC 1722 presentation time in ns */

/* ENET_MAC_PRESN_TIME_UPDT */
#define ENET_MAC_PRESN_TIME_UPDT_MPTU                          BITS(0,31)            /*!< MAC 1722 presentation time update */

/* ENET_MAC_ADDRESS0_HIGH */
#define ENET_MAC_ADDRESS0_HIGH_ADDRHI                          BITS(0,15)            /*!< MAC Address0[47:32] */
#define ENET_MAC_ADDRESS0_HIGH_DCS                             BITS(16,17)           /*!< DMA channel select */
#define ENET_MAC_ADDRESS0_HIGH_AE                              BIT(31)               /*!< Address enable */

/* ENET_MAC_ADDRESS0_LOW */
#define ENET_MAC_ADDRESS0_LOW_ADDRLO                           BITS(0,31)            /*!< MAC Address0[31:0] */

/* ENET_MAC_ADDRESS1_HIGH */
#define ENET_MAC_ADDRESS1_HIGH_ADDRHI                          BITS(0,15)            /*!< MAC Address1[47:32] */
#define ENET_MAC_ADDRESS1_HIGH_DCS                             BITS(16,17)           /*!< DMA channel select */
#define ENET_MAC_ADDRESS1_HIGH_MBC                             BITS(24,29)           /*!< mask byte */
#define ENET_MAC_ADDRESS1_HIGH_SA                              BIT(30)               /*!< source address filter bit */
#define ENET_MAC_ADDRESS1_HIGH_AE                              BIT(31)               /*!< address filter enable */

/* ENET_MAC_ADDRESS1_LOW */
#define ENET_MAC_ADDRESS1_LOW_ADDRLO                           BITS(0,31)            /*!< MAC address1[31:0] */

/* ENET_MAC_ADDRESS2_HIGH */
#define ENET_MAC_ADDRESS2_HIGH_ADDRHI                          BITS(0,15)            /*!< MAC Address2[47:32] */
#define ENET_MAC_ADDRESS2_HIGH_DCS                             BITS(16,17)           /*!< DMA channel select */
#define ENET_MAC_ADDRESS2_HIGH_MBC                             BITS(24,29)           /*!< mask byte */
#define ENET_MAC_ADDRESS2_HIGH_SA                              BIT(30)               /*!< source address filter bit */
#define ENET_MAC_ADDRESS2_HIGH_AE                              BIT(31)               /*!< address filter enable */

/* ENET_MAC_ADDRESS2_LOW */
#define ENET_MAC_ADDRESS2_LOW_ADDRLO                           BITS(0,31)            /*!< MAC address2[31:0] */

/* ENET_MMC_CONTROL */
#define ENET_MMC_CONTROL_CNTRST                                BIT(0)                /*!< counters reset */
#define ENET_MMC_CONTROL_CNTSTOPRO                             BIT(1)                /*!< counter stop rollover */
#define ENET_MMC_CONTROL_RSTONRD                               BIT(2)                /*!< reset on read */
#define ENET_MMC_CONTROL_CNTFREEZ                              BIT(3)                /*!< MMC counter freeze */
#define ENET_MMC_CONTROL_CNTPRST                               BIT(4)                /*!< counters preset */
#define ENET_MMC_CONTROL_CNTPRSTLVL                            BIT(5)                /*!< full-half preset */
#define ENET_MMC_CONTROL_UCDBC                                 BIT(8)                /*!< update MMC counters for dropped broadcast packets */

/* ENET_MMC_RX_INTERRUPT */
#define ENET_MMC_RX_INTERRUPT_RXGBPKTIS                        BIT(0)                /*!< MMC receive good bad packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXGBOCTIS                        BIT(1)                /*!< MMC receive good bad octet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXGOCTIS                         BIT(2)                /*!< MMC receive good octet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXBCGPIS                         BIT(3)                /*!< MMC receive broadcast good packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXMCGPIS                         BIT(4)                /*!< MMC receive multicast good packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXCRCERPIS                       BIT(5)                /*!< MMC receive CRC error packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXALGNERPIS                      BIT(6)                /*!< MMC receive alignment error packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXRUNTPIS                        BIT(7)                /*!< MMC receive runt packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXJABERPIS                       BIT(8)                /*!< MMC receive jabber error packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXUSIZEGPIS                      BIT(9)                /*!< MMC receive undersize good packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXOSIZEGPIS                      BIT(10)               /*!< MMC receive oversize good packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RX64OCTGBPIS                     BIT(11)               /*!< MMC receive 64 octet good bad packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RX65T127OCTGBPIS                 BIT(12)               /*!< MMC receive 65 to 127 octet good bad packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RX128T255OCTGBPIS                BIT(13)               /*!< MMC receive 128 to 255 octet good bad packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RX256T511OCTGBPIS                BIT(14)               /*!< MMC receive 256 to 511 octet good bad packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RX512T1023OCTGBPIS               BIT(15)               /*!< MMC receive 512 to 1023 octet good bad packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RX1024TMAXOCTGBPIS               BIT(16)               /*!< MMC receive 1024 to maximum octet good bad packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXUCGPIS                         BIT(17)               /*!< MMC receive unicast good packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXLENERPIS                       BIT(18)               /*!< MMC receive length error packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXORANGEPIS                      BIT(19)               /*!< MMC receive out of range error packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXPAUSPIS                        BIT(20)               /*!< MMC receive pause packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXFOVPIS                         BIT(21)               /*!< MMC receive FIFO overflow packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXVLANGBPIS                      BIT(22)               /*!< MMC receive VLAN good bad packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXWDOGPIS                        BIT(23)               /*!< MMC receive watchdog error packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXRCVERRPIS                      BIT(24)               /*!< MMC receive error packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXCTRLPIS                        BIT(25)               /*!< MMC receive control packet counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXLPIUSCIS                       BIT(26)               /*!< MMC receive LPI microsecond counter interrupt status */
#define ENET_MMC_RX_INTERRUPT_RXLPITRCIS                       BIT(27)               /*!< MMC receive LPI transition counter interrupt status */

/* ENET_MMC_TX_INTERRUPT */
#define ENET_MMC_TX_INTERRUPT_TXGBOCTIS                        BIT(0)                /*!< MMC transmit good bad octet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXGBPKTIS                        BIT(1)                /*!< MMC transmit good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXBCGPIS                         BIT(2)                /*!< MMC transmit broadcast good packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXMCGPIS                         BIT(3)                /*!< MMC transmit multicast good packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TX64OCTGBPIS                     BIT(4)                /*!< MMC transmit 64 octet good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TX65T127OCTGBPIS                 BIT(5)                /*!< MMC transmit 65 to 127 octet good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TX128T255OCTGBPIS                BIT(6)                /*!< MMC transmit 128 to 255 octet good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TX256T511OCTGBPIS                BIT(7)                /*!< MMC transmit 256 to 511 octet good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TX512T1023OCTGBPIS               BIT(8)                /*!< MMC transmit 512 to 1023 octet good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TX1024TMAXOCTGBPIS               BIT(9)                /*!< MMC transmit 1024 to Maximum octet good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXUCGBPIS                        BIT(10)               /*!< MMC transmit unicast good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXMCGBPIS                        BIT(11)               /*!< MMC transmit multicast good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXBCGBPIS                        BIT(12)               /*!< MMC transmit broadcast good bad packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXUFLOWERPIS                     BIT(13)               /*!< MMC transmit underflow error packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXSCOLGPIS                       BIT(14)               /*!< MMC transmit single collision good packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXMCOLGPIS                       BIT(15)               /*!< MMC transmit multiple collision good packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXDEFPIS                         BIT(16)               /*!< MMC transmit deferred packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXLATCOLPIS                      BIT(17)               /*!< MMC transmit late collision packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXEXCOLPIS                       BIT(18)               /*!< MMC transmit excessive collision packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXCARERPIS                       BIT(19)               /*!< MMC transmit carrier error packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXGOCTIS                         BIT(20)               /*!< MMC transmit good octet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXGPKTIS                         BIT(21)               /*!< MMC transmit good packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXEXDEFPIS                       BIT(22)               /*!< MMC transmit excessive deferral packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXPAUSPIS                        BIT(23)               /*!< MMC transmit pause packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXVLANGPIS                       BIT(24)               /*!< MMC transmit VLAN good packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXOSIZEGPIS                      BIT(25)               /*!< MMC transmit oversize good packet counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXLPIUSCIS                       BIT(26)               /*!< MMC transmit LPI microsecond counter interrupt status */
#define ENET_MMC_TX_INTERRUPT_TXLPITRCIS                       BIT(27)               /*!< MMC transmit LPI transition counter interrupt status */

/* ENET_MMC_RX_INTERRUPT_MASK */
#define ENET_MMC_RX_INTERRUPT_MASK_RXGBPKTIM                        BIT(0)                /*!< MMC receive good bad packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXGBOCTIM                        BIT(1)                /*!< MMC receive good bad octet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXGOCTIM                         BIT(2)                /*!< MMC receive good octet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXBCGPIM                         BIT(3)                /*!< MMC receive broadcast good packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXMCGPIM                         BIT(4)                /*!< MMC receive multicast good packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXCRCERPIM                       BIT(5)                /*!< MMC receive CRC error packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXALGNERPIM                      BIT(6)                /*!< MMC receive alignment error packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXRUNTPIM                        BIT(7)                /*!< MMC receive runt packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXJABERPIM                       BIT(8)                /*!< MMC receive jabber error packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXUSIZEGPIM                      BIT(9)                /*!< MMC receive undersize good packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXOSIZEGPIM                      BIT(10)               /*!< MMC receive oversize good packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RX64OCTGBPIM                     BIT(11)               /*!< MMC receive 64 octet good bad packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RX65T127OCTGBPIM                 BIT(12)               /*!< MMC receive 65 to 127 octet good bad packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RX128T255OCTGBPIM                BIT(13)               /*!< MMC receive 128 to 255 octet good bad packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RX256T511OCTGBPIM                BIT(14)               /*!< MMC receive 256 to 511 octet good bad packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RX512T1023OCTGBPIM               BIT(15)               /*!< MMC receive 512 to 1023 octet good bad packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RX1024TMAXOCTGBPIM               BIT(16)               /*!< MMC receive 1024 to maximum octet good bad packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXUCGPIM                         BIT(17)               /*!< MMC receive unicast good packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXLENERPIM                       BIT(18)               /*!< MMC receive length error packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXORANGEPIM                      BIT(19)               /*!< MMC receive out of range error packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXPAUSPIM                        BIT(20)               /*!< MMC receive pause packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXFOVPIM                         BIT(21)               /*!< MMC receive FIFO overflow packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXVLANGBPIM                      BIT(22)               /*!< MMC receive VLAN good bad packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXWDOGPIM                        BIT(23)               /*!< MMC receive watchdog error packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXRCVERRPIM                      BIT(24)               /*!< MMC receive error packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXCTRLPIM                        BIT(25)               /*!< MMC receive control packet counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXLPIUSCIM                       BIT(26)               /*!< MMC receive LPI microsecond counter interrupt mask */
#define ENET_MMC_RX_INTERRUPT_MASK_RXLPITRCIM                       BIT(27)               /*!< MMC receive LPI transition counter interrupt mask */

/* ENET_MMC_TX_INTERRUPT_MASK */
#define ENET_MMC_TX_INTERRUPT_MASK_TXGBOCTIM                        BIT(0)                /*!< MMC transmit good bad octet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXGBPKTIM                        BIT(1)                /*!< MMC transmit good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXBCGPIM                         BIT(2)                /*!< MMC transmit broadcast good packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXMCGPIM                         BIT(3)                /*!< MMC transmit multicast good packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TX64OCTGBPIM                     BIT(4)                /*!< MMC transmit 64 octet good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TX65T127OCTGBPIM                 BIT(5)                /*!< MMC transmit 65 to 127 octet good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TX128T255OCTGBPIM                BIT(6)                /*!< MMC transmit 128 to 255 octet good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TX256T511OCTGBPIM                BIT(7)                /*!< MMC transmit 256 to 511 octet good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TX512T1023OCTGBPIM               BIT(8)                /*!< MMC transmit 512 to 1023 octet good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TX1024TMAXOCTGBPIM               BIT(9)                /*!< MMC transmit 1024 to Maximum octet good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXUCGBPIM                        BIT(10)               /*!< MMC transmit unicast good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXMCGBPIM                        BIT(11)               /*!< MMC transmit multicast good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXBCGBPIM                        BIT(12)               /*!< MMC transmit broadcast good bad packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXUFLOWERPIM                     BIT(13)               /*!< MMC transmit underflow error packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXSCOLGPIM                       BIT(14)               /*!< MMC transmit single collision good packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXMCOLGPIM                       BIT(15)               /*!< MMC transmit multiple collision good packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXDEFPIM                         BIT(16)               /*!< MMC transmit deferred packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXLATCOLPIM                      BIT(17)               /*!< MMC transmit late collision packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXEXCOLPIM                       BIT(18)               /*!< MMC transmit excessive collision packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXCARERPIM                       BIT(19)               /*!< MMC transmit carrier error packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXGOCTIM                         BIT(20)               /*!< MMC transmit good octet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXGPKTIM                         BIT(21)               /*!< MMC transmit good packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXEXDEFPIM                       BIT(22)               /*!< MMC transmit excessive deferral packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXPAUSPIM                        BIT(23)               /*!< MMC transmit pause packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXVLANGPIM                       BIT(24)               /*!< MMC transmit VLAN good packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXOSIZEGPIM                      BIT(25)               /*!< MMC transmit oversize good packet counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXLPIUSCIM                       BIT(26)               /*!< MMC transmit LPI microsecond counter interrupt mask */
#define ENET_MMC_TX_INTERRUPT_MASK_TXLPITRCIM                       BIT(27)               /*!< MMC transmit LPI transition counter interrupt mask */

/* ENET_TX_OCTET_COUNT_GOOD_BAD */
#define ENET_TX_OCTET_COUNT_GOOD_BAD_TXOCTGB                        BITS(0,31)            /*!< transmit octet count good bad */

/* ENET_TX_PACKET_COUNT_GOOD_BAD */
#define ENET_TX_PACKET_COUNT_GOOD_BAD_TXPKTGB                       BITS(0,31)            /*!< transmit packet count good bad */

/* ENET_TX_BROADCAST_PACKETS_GOOD */
#define ENET_TX_BROADCAST_PACKETS_GOOD_TXBCASTG                     BITS(0,31)            /*!< transmit broadcast packets good */

/* ENET_TX_MULTICAST_PACKETS_GOOD */
#define ENET_TX_MULTICAST_PACKETS_GOOD_TXMCASTG                     BITS(0,31)            /*!< transmit multicast packets good */

/* ENET_TX_64OCTET_PACKETS_GOOD_BAD */
#define ENET_TX_64OCTET_PACKETS_GOOD_BAD_TX64OCTGB                  BITS(0,31)            /*!< transmit 64 octets packets good bad */

/* ENET_TX_65TO127OCTET_PACKETS_GOOD_BAD */
#define ENET_TX_65TO127OCTET_PACKETS_GOOD_BAD_TX65_127OCTGB         BITS(0,31)            /*!< transmit 65 to 127 octets packets good bad */

/* ENET_TX_128TO255OCTET_PACKETS_GOOD_BAD */
#define ENET_TX_128TO255OCTET_PACKETS_GOOD_BAD_TX128_255OCTGB       BITS(0,31)            /*!< transmit 128 to 255 octets packets good bad */

/* ENET_TX_256TO511OCTET_PACKETS_GOOD_BAD */
#define ENET_TX_256TO511OCTET_PACKETS_GOOD_BAD_TX256_511OCTGB      BITS(0,31)            /*!< transmit 256 to 511 octets packets good bad */

/* ENET_TX_512TO1023OCTET_PACKETS_GOOD_BAD */
#define ENET_TX_512TO1023OCTET_PACKETS_GOOD_BAD_TX512_1023OCTGB    BITS(0,31)            /*!< transmit 512 to 1023 octets packets good bad */

/* ENET_TX_1024TOMAXOCTET_PACKETS_GOOD_BAD */
#define ENET_TX_1024TOMAXOCTET_PACKETS_GOOD_BAD_TX1024_MAXOCTGB    BITS(0,31)            /*!< transmit 1024 to max octets packets good bad */

/* ENET_TX_UNICAST_PACKETS_GOOD_BAD */
#define ENET_TX_UNICAST_PACKETS_GOOD_BAD_TXUCASTGB                 BITS(0,31)            /*!< transmit unicast packets good bad */

/* ENET_TX_MULTICAST_PACKETS_GOOD_BAD */
#define ENET_TX_MULTICAST_PACKETS_GOOD_BAD_TXMCASTGB               BITS(0,31)            /*!< transmit multicast packets good bad */

/* ENET_TX_BROADCAST_PACKETS_GOOD_BAD */
#define ENET_TX_BROADCAST_PACKETS_GOOD_BAD_TXBCASTGB               BITS(0,31)            /*!< transmit broadcast packets good bad */

/* ENET_TX_UNDERFLOW_ERROR_PACKETS */
#define ENET_TX_UNDERFLOW_ERROR_PACKETS_TXUNDRFLW                  BITS(0,31)            /*!< transmit underflow error packets */

/* ENET_TX_SINGLE_COLLISION_GOOD_PACKETS */
#define ENET_TX_SINGLE_COLLISION_GOOD_PACKETS_TXSNGLCOLG           BITS(0,31)            /*!< transmit single collision good packets */

/* ENET_TX_MULTIPLE_COLLISION_GOOD_PACKETS */
#define ENET_TX_MULTIPLE_COLLISION_GOOD_PACKETS_TXMULTCOLG         BITS(0,31)            /*!< transmit multiple collision good packets */

/* ENET_TX_DEFERRED_PACKETS */
#define ENET_TX_DEFERRED_PACKETS_TXDEFRD                           BITS(0,31)            /*!< transmit deferred packets */

/* ENET_TX_LATE_COLLISION_PACKETS */
#define ENET_TX_LATE_COLLISION_PACKETS_TXLATECOL                   BITS(0,31)            /*!< transmit late collision packets */

/* ENET_TX_EXCESSIVE_COLLISION_PACKETS */
#define ENET_TX_EXCESSIVE_COLLISION_PACKETS_TXEXSCOL               BITS(0,31)            /*!< transmit excessive collision packets */

/* ENET_TX_CARRIER_ERROR_PACKETS */
#define ENET_TX_CARRIER_ERROR_PACKETS_TXCARR                       BITS(0,31)            /*!< transmit carrier error packets */

/* ENET_TX_OCTET_COUNT_GOOD */
#define ENET_TX_OCTET_COUNT_GOOD_TXOCTG                            BITS(0,31)            /*!< transmit octet count good */

/* ENET_TX_PACKET_COUNT_GOOD */
#define ENET_TX_PACKET_COUNT_GOOD_TXPKTG                           BITS(0,31)            /*!< transmit packet count good */

/* ENET_TX_EXCESSIVE_DEFERRAL_ERROR */
#define ENET_TX_EXCESSIVE_DEFERRAL_ERROR_TXEXSDEF                  BITS(0,31)            /*!< transmit excessive deferral error */

/* ENET_TX_PAUSE_PACKETS */
#define ENET_TX_PAUSE_PACKETS_TXPAUSE                              BITS(0,31)            /*!< transmit pause packets */

/* ENET_TX_VLAN_PACKETS_GOOD */
#define ENET_TX_VLAN_PACKETS_GOOD_TXVLANG                          BITS(0,31)            /*!< transmit VLAN packets good */

/* ENET_TX_OSIZE_PACKETS_GOOD */
#define ENET_TX_OSIZE_PACKETS_GOOD_TXOSIZG                         BITS(0,31)            /*!< transmit oversize packets good */

/* ENET_RX_PACKETS_COUNT_GOOD_BAD */
#define ENET_RX_PACKETS_COUNT_GOOD_BAD_RXPKTGB                     BITS(0,31)            /*!< receive packets count good bad */

/* ENET_RX_OCTET_COUNT_GOOD_BAD */
#define ENET_RX_OCTET_COUNT_GOOD_BAD_RXOCTGB                       BITS(0,31)            /*!< receive octet count good bad */

/* ENET_RX_OCTET_COUNT_GOOD */
#define ENET_RX_OCTET_COUNT_GOOD_RXOCTG                            BITS(0,31)            /*!< receive octet count good */

/* ENET_RX_BROADCAST_PACKETS_GOOD */
#define ENET_RX_BROADCAST_PACKETS_GOOD_RXBCASTG                    BITS(0,31)            /*!< receive broadcast packets good */

/* ENET_RX_MULTICAST_PACKETS_GOOD */
#define ENET_RX_MULTICAST_PACKETS_GOOD_RXMCASTG                    BITS(0,31)            /*!< receive multicast packets good */

/* ENET_RX_CRC_ERROR_PACKETS */
#define ENET_RX_CRC_ERROR_PACKETS_RXCRCERR                         BITS(0,31)            /*!< receive crc error packets */

/* ENET_RX_ALIGNMENT_ERROR_PACKETS */
#define ENET_RX_ALIGNMENT_ERROR_PACKETS_RXALGNERR                  BITS(0,31)            /*!< receive alignment error packets */

/* ENET_RX_RUNT_ERROR_PACKETS */
#define ENET_RX_RUNT_ERROR_PACKETS_RXRUNTERR                       BITS(0,31)            /*!< receive runt error packets */

/* ENET_RX_JABBER_ERROR_PACKETS */
#define ENET_RX_JABBER_ERROR_PACKETS_RXJABERR                      BITS(0,31)            /*!< receive jabber error packets */

/* ENET_RX_UNDERSIZE_PACKETS_GOOD */
#define ENET_RX_UNDERSIZE_PACKETS_GOOD_RXUNDERSZG                  BITS(0,31)            /*!< receive undersize packets good */

/* ENET_RX_OVERSIZE_PACKETS_GOOD */
#define ENET_RX_OVERSIZE_PACKETS_GOOD_RXOVERSZG                    BITS(0,31)            /*!< receive oversize packets good */

/* ENET_RX_64OCTET_PACKETS_GOOD_BAD */
#define ENET_RX_64OCTET_PACKETS_GOOD_BAD_RX64OCTGB                 BITS(0,31)            /*!< receive 64 octets packets god bad */

/* ENET_RX_65TO127OCTET_PACKETS_GOOD_BAD */
#define ENET_RX_65TO127OCTET_PACKETS_GOOD_BAD_RX65_127OCTGB        BITS(0,31)            /*!< receive 65-127 octets packets good bad bad */

/* ENET_RX_128TO255OCTET_PACKETS_GOOD_BAD */
#define ENET_RX_128TO255OCTET_PACKETS_GOOD_BAD_RX128_255OCTGB      BITS(0,31)            /*!< receive 128-255 octets packets good bad bad */

/* ENET_RX_256TO511OCTET_PACKETS_GOOD_BAD */
#define ENET_RX_256TO511OCTET_PACKETS_GOOD_BAD_RX256_511OCTGB      BITS(0,31)            /*!< receive 256-511 octets packets good bad bad */

/* ENET_RX_512TO1023OCTET_PACKETS_GOOD_BAD */
#define ENET_RX_512TO1023OCTET_PACKETS_GOOD_BAD_RX512_1023OCTGB    BITS(0,31)            /*!< receive 512-1023 octets packets good bad bad */

/* ENET_RX_1024TOMAXOCTET_PACKETS_GOOD_BAD */
#define ENET_RX_1024TOMAXOCTET_PACKETS_GOOD_BAD_RX1024_MAXOCTGB    BITS(0,31)            /*!< receive 1024 to max octets packets good bad bad */

/* ENET_RX_UNICAST_PACKETS_GOOD */
#define ENET_RX_UNICAST_PACKETS_GOOD_RXUCASTG                      BITS(0,31)            /*!< receive unicast packets good */

/* ENET_RX_LENGTH_ERROR_PACKETS */
#define ENET_RX_LENGTH_ERROR_PACKETS_RXLENERR                      BITS(0,31)            /*!< receive length error packets */

/* ENET_RX_OUT_OF_RANGE_TYPE_PACKETS */
#define ENET_RX_OUT_OF_RANGE_TYPE_PACKETS_RXOUTOFRNG               BITS(0,31)            /*!< receive out of range type packets */

/* ENET_RX_PAUSE_PACKETS */
#define ENET_RX_PAUSE_PACKETS_RXPAUSEPKT                           BITS(0,31)            /*!< receive pause packets */

/* ENET_RX_FIFO_OVERFLOW_PACKETS */
#define ENET_RX_FIFO_OVERFLOW_PACKETS_RXFIFOOVFL                   BITS(0,31)            /*!< receive FIFO overflow packets */

/* ENET_RX_VLAN_PACKETS_GOOD_BAD */
#define ENET_RX_VLAN_PACKETS_GOOD_BAD_RXVLANPKTGB                  BITS(0,31)            /*!< receive VLAN packets god bad */

/* ENET_RX_WATCHDOG_ERROR_PACKETS */
#define ENET_RX_WATCHDOG_ERROR_PACKETS_RXWDGERR                    BITS(0,31)            /*!< receive watchdog error packets */

/* ENET_RX_ERROR_PACKETS */
#define ENET_RX_ERROR_PACKETS_RXRCVERR                             BITS(0,31)            /*!< receive error packets */

/* ENET_RX_CONTROL_PACKETS_GOOD */
#define ENET_RX_CONTROL_PACKETS_GOOD_RXCTRLG                      BITS(0,31)            /*!< receive control packets good */

/* ENET_TX_LPI_USEC_CNTR */
#define ENET_TX_LPI_USEC_CNTR_TXLPIUSC                            BITS(0,31)            /*!< transmit LPI microseconds counter */

/* ENET_TX_LPI_TRAN_CNTR */
#define ENET_TX_LPI_TRAN_CNTR_TXLPITRC                            BITS(0,31)            /*!< transmit LPI transition counter */

/* ENET_RX_LPI_USEC_CNTR */
#define ENET_RX_LPI_USEC_CNTR_RXLPIUSC                            BITS(0,31)            /*!< receive LPI microseconds counter */

/* ENET_RX_LPI_TRAN_CNTR */
#define ENET_RX_LPI_TRAN_CNTR_RXLPITRC                            BITS(0,31)            /*!< receive LPI transition counter */

/* ENET_MMC_IPC_RX_INTERRUPT_MASK */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GPIM                 BIT(0)                /*!< MMC receive IPV4 good packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HERPIM               BIT(1)                /*!< MMC receive IPV4 header error packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYPIM             BIT(2)                /*!< MMC receive IPV4 no payload packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGPIM              BIT(3)                /*!< MMC receive IPV4 fragmented packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLPIM             BIT(4)                /*!< MMC receive IPV4 UDP checksum disabled packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GPIM                 BIT(5)                /*!< MMC receive IPV6 good packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HERPIM               BIT(6)                /*!< MMC receive IPV6 header error packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYPIM             BIT(7)                /*!< MMC receive IPV6 no payload packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGPIM                  BIT(8)                /*!< MMC receive UDP good packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXUDPERPIM                 BIT(9)                /*!< MMC receive UDP error packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGPIM                  BIT(10)               /*!< MMC receive TCP good packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXTCPERPIM                 BIT(11)               /*!< MMC receive TCP error packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGPIM                 BIT(12)               /*!< MMC receive ICMP good packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXICMPERPIM                BIT(13)               /*!< MMC receive ICMP error packet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4GOIM                 BIT(16)               /*!< MMC receive IPV4 good octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4HEROIM               BIT(17)               /*!< MMC receive IPV4 good octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4NOPAYOIM             BIT(18)               /*!< MMC receive IPV4 no payload octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4FRAGOIM              BIT(19)               /*!< MMC receive IPV4 fragmented octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV4UDSBLOIM             BIT(20)               /*!< MMC receive IPV4 UDP checksum disabled octett counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6GOIM                 BIT(21)               /*!< MMC receive IPV6 good octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6HEROIM               BIT(22)               /*!< MMC receive IPV6 header error octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXIPV6NOPAYOIM             BIT(23)               /*!< MMC receive IPV6 no payload octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXUDPGOIM                  BIT(24)               /*!< MMC receive UDP good octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXUDPEROIM                 BIT(25)               /*!< MMC receive UDP error octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXTCPGOIM                  BIT(26)               /*!< MMC receive TCP good octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXTCPEROIM                 BIT(27)               /*!< MMC receive TCP error octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXICMPGOIM                 BIT(28)               /*!< MMC receive ICMP good octet counter interrupt mask */
#define ENET_MMC_IPC_RX_INTERRUPT_MASK_RXICMPEROIM                BIT(29)               /*!< MMC receive ICMP error octet counter interrupt mask */

/* ENET_MMC_IPC_RX_INTERRUPT */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4GPIS                 BIT(0)                /*!< MMC receive IPV4 good packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4HERPIS               BIT(1)                /*!< MMC receive IPV4 header error packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYPIS             BIT(2)                /*!< MMC receive IPV4 no payload packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGPIS              BIT(3)                /*!< MMC receive IPV4 fragmented packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLPIS             BIT(4)                /*!< MMC receive IPV4 UDP checksum disabled packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV6GPIS                 BIT(5)                /*!< MMC receive IPV6 good packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV6HERPIS               BIT(6)                /*!< MMC receive IPV6 header error packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYPIS             BIT(7)                /*!< MMC receive IPV6 no payload packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXUDPGPIS                  BIT(8)                /*!< MMC receive UDP good packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXUDPERPIS                 BIT(9)                /*!< MMC receive UDP error packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXTCPGPIS                  BIT(10)               /*!< MMC receive TCP good packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXTCPERPIS                 BIT(11)               /*!< MMC receive TCP error packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXICMPGPIS                 BIT(12)               /*!< MMC receive ICMP good packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXICMPERPIS                BIT(13)               /*!< MMC receive ICMP error packet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4GOIS                 BIT(16)               /*!< MMC receive IPV4 good octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4HEROIS               BIT(17)               /*!< MMC receive IPV4 good octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4NOPAYOIS             BIT(18)               /*!< MMC receive IPV4 no payload octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4FRAGOIS              BIT(19)               /*!< MMC receive IPV4 fragmented octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV4UDSBLOIS             BIT(20)               /*!< MMC receive IPV4 UDP checksum disabled octett counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV6GOIS                 BIT(21)               /*!< MMC receive IPV6 good octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV6HEROIS               BIT(22)               /*!< MMC receive IPV6 header error octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXIPV6NOPAYOIS             BIT(23)               /*!< MMC receive IPV6 no payload octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXUDPGOIS                  BIT(24)               /*!< MMC receive UDP good octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXUDPEROIS                 BIT(25)               /*!< MMC receive UDP error octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXTCPGOIS                  BIT(26)               /*!< MMC receive TCP good octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXTCPEROIS                 BIT(27)               /*!< MMC receive TCP error octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXICMPGOIS                 BIT(28)               /*!< MMC receive ICMP good octet counter interrupt status */
#define ENET_MMC_IPC_RX_INTERRUPT_RXICMPEROIS                BIT(29)               /*!< MMC receive ICMP error octet counter interrupt status */

/* ENET_RXIPV4_GOOD_PACKETS */
#define ENET_RXIPV4_GOOD_PACKETS_RXIPV4GDPKT                 BITS(0,31)            /*!< receive ipv4 good packets */

/* ENET_RXIPV4_HEADER_ERROR_PACKETS */
#define ENET_RXIPV4_HEADER_ERROR_PACKETS_RXIPV4HDRERRPKT     BITS(0,31)            /*!< receive ipv4 header errors packets */

/* ENET_RXIPV4_NO_PAYLOAD_PACKETS */
#define ENET_RXIPV4_NO_PAYLOAD_PACKETS_RXIPV4NOPAYPKT        BITS(0,31)            /*!< receive ipv4 no payload packets */

/* ENET_RXIPV4_FRAGMENTED_PACKETS */
#define ENET_RXIPV4_FRAGMENTED_PACKETS_RXIPV4FRAGPKT         BITS(0,31)            /*!< receive fragmented ipv4 packets */

/* ENET_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS */
#define ENET_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_RXIPV4UDSBLPKT BITS(0,31)        /*!< receive ipv4 udp checksum disable packets */

/* ENET_RXIPV6_GOOD_PACKETS */
#define ENET_RXIPV6_GOOD_PACKETS_RXIPV6GDPKT                 BITS(0,31)            /*!< receive ipv6 good packets */

/* ENET_RXIPV6_HEADER_ERROR_PACKETS */
#define ENET_RXIPV6_HEADER_ERROR_PACKETS_RXIPV6HDRERRPKT     BITS(0,31)            /*!< receive ipv6 header errors packets */

/* ENET_RXIPV6_NO_PAYLOAD_PACKETS */
#define ENET_RXIPV6_NO_PAYLOAD_PACKETS_RXIPV6NOPAYPKT        BITS(0,31)            /*!< receive ipv6 no payload packets */

/* ENET_RXUDP_GOOD_PACKETS */
#define ENET_RXUDP_GOOD_PACKETS_RXUDPGDPKT                   BITS(0,31)            /*!< receive udp packets good */

/* ENET_RXUDP_ERROR_PACKETS */
#define ENET_RXUDP_ERROR_PACKETS_RXUDPERRPKT                 BITS(0,31)            /*!< receive udp checksum errors packets */

/* ENET_RXTCP_GOOD_PACKETS */
#define ENET_RXTCP_GOOD_PACKETS_RXTCPGDPKT                   BITS(0,31)            /*!< receive tcp packets good */

/* ENET_RXTCP_ERROR_PACKETS */
#define ENET_RXTCP_ERROR_PACKETS_RXTCPERRPKT                 BITS(0,31)            /*!< receive tcp checksum errors packets */

/* ENET_RXICMP_GOOD_PACKETS */
#define ENET_RXICMP_GOOD_PACKETS_RXICMPGDPKT                 BITS(0,31)            /*!< receive icmp packets good */

/* ENET_RXICMP_ERROR_PACKETS */
#define ENET_RXICMP_ERROR_PACKETS_RXICMPERRPKT               BITS(0,31)            /*!< receive icmp checksum errors packets */

/* ENET_RXIPV4_GOOD_OCTETS */
#define ENET_RXIPV4_GOOD_OCTETS_RXIPV4GDOCT                  BITS(0,31)            /*!< receive ipv4 good octets */

/* ENET_RXIPV4_HEADER_ERROR_OCTETS */
#define ENET_RXIPV4_HEADER_ERROR_OCTETS_RXIPV4HDRERROCT      BITS(0,31)            /*!< receive ipv4 header errors octets */

/* ENET_RXIPV4_NO_PAYLOAD_OCTETS */
#define ENET_RXIPV4_NO_PAYLOAD_OCTETS_RXIPV4NOPAYOCT         BITS(0,31)            /*!< receive ipv4 no payload octets */

/* ENET_RXIPV4_FRAGMENTED_OCTETS */
#define ENET_RXIPV4_FRAGMENTED_OCTETS_RXIPV4FRAGOCT          BITS(0,31)            /*!< receive fragmented ipv4 octets */

/* ENET_RXIPV4_UDP_CHECKSUM_DISABLED_OCTETS */
#define ENET_RXIPV4_UDP_CHECKSUM_DISABLED_OCTETS_RXIPV4UDSBLOCT BITS(0,31)            /*!< receive ipv4 udp checksum disable octets */

/* ENET_RXIPV6_GOOD_OCTETS */
#define ENET_RXIPV6_GOOD_OCTETS_RXIPV6GDOCT                  BITS(0,31)            /*!< receive ipv6 good octets */

/* ENET_RXIPV6_HEADER_ERROR_OCTETS */
#define ENET_RXIPV6_HEADER_ERROR_OCTETS_RXIPV6HDRERROCT      BITS(0,31)            /*!< receive ipv6 header errors octets */

/* ENET_RXIPV6_NO_PAYLOAD_OCTETS */
#define ENET_RXIPV6_NO_PAYLOAD_OCTETS_RXIPV6NOPAYOCT         BITS(0,31)            /*!< receive ipv6 no payload octets */

/* ENET_RXUDP_GOOD_OCTETS */
#define ENET_RXUDP_GOOD_OCTETS_RXUDPGDOCT                   BITS(0,31)            /*!< receive udp good octets */

/* ENET_RXUDP_ERROR_OCTETS */
#define ENET_RXUDP_ERROR_OCTETS_RXUDPERROCT                 BITS(0,31)            /*!< receive udp checksum errors octets */

/* ENET_RXTCP_GOOD_OCTETS */
#define ENET_RXTCP_GOOD_OCTETS_RXTCPGDOCT                   BITS(0,31)            /*!< receive tcp good octets */

/* ENET_RXTCP_ERROR_OCTETS */
#define ENET_RXTCP_ERROR_OCTETS_RXTCPERROCT                 BITS(0,31)            /*!< receive tcp checksum errors octets */

/* ENET_RXICMP_GOOD_OCTETS */
#define ENET_RXICMP_GOOD_OCTETS_RXICMPGDOCT                 BITS(0,31)            /*!< receive icmp good octets */

/* ENET_RXICMP_ERROR_PACKETS */
#define ENET_RXICMP_ERROR_OCTETS_RXICMPERROCT               BITS(0,31)            /*!< receive icmp checksum errors octets */

/* ENET_MMC_FPE_TX_INTERRUPT */
#define ENET_MMC_FPE_TX_INTERRUPT_FCIS                      BIT(0)                /*!< MMC Tx FPE fragment counter interrupt status */
#define ENET_MMC_FPE_TX_INTERRUPT_HRCIS                     BIT(1)                /*!< MMC Tx hold request counter interrupt status */

/* ENET_MMC_FPE_TX_INTERRUPT_MASK */
#define ENET_MMC_FPE_TX_INTERRUPT_MASK_FCIM                 BIT(0)                /*!< MMC Tx FPE fragment counter interrupt mask */
#define ENET_MMC_FPE_TX_INTERRUPT_MASK_HRCIM                BIT(1)                /*!< MMC Tx hold request counter interrupt mask */

/* ENET_MMC_FPE_TX_FRAGMENT_CNTR */
#define ENET_MMC_FPE_TX_FRAGMENT_CNTR_TXFFC                 BITS(0,31)            /*!< Tx FPE fragment counter */

/* ENET_MMC_TX_HOLD_REQ_CNTR */
#define ENET_MMC_TX_HOLD_REQ_CNTR_TXHRC                    BITS(0,31)             /*!< Tx hold request counter */

/* ENET_MMC_FPE_RX_INTERRUPT */
#define ENET_MMC_FPE_RX_INTERRUPT_PAECIS                    BIT(0)                /*!< MMC Rx packet assembly error counter interrupt status */
#define ENET_MMC_FPE_RX_INTERRUPT_PSECIS                    BIT(1)                /*!< MMC Rx packet SMD error counter interrupt status */
#define ENET_MMC_FPE_RX_INTERRUPT_PAOCIS                    BIT(2)                /*!< MMC Rx packet assembly ok counter interrupt status */
#define ENET_MMC_FPE_RX_INTERRUPT_FCIS                      BIT(3)                /*!< MMC Rx FPE fragment counter interrupt status */

/* ENET_MMC_FPE_RX_INTERRUPT_MASK */
#define ENET_MMC_FPE_RX_INTERRUPT_MASK_PAECIM               BIT(0)                /*!< MMC Rx packet assembly error counter interrupt mask */
#define ENET_MMC_FPE_RX_INTERRUPT_MASK_PSECIM               BIT(1)                /*!< MMC Rx packet SMD error counter interrupt mask */
#define ENET_MMC_FPE_RX_INTERRUPT_MASK_PAOCIM               BIT(2)                /*!< MMC Rx packet assembly ok counter interrupt mask */
#define ENET_MMC_FPE_RX_INTERRUPT_MASK_FCIM                 BIT(3)                /*!< MMC Rx FPE fragment counter interrupt mask */

/* ENET_MMC_RX_PACKETS_ASSEMBLY_ERR_CNTR */
#define ENET_MMC_RX_PACKETS_ASSEMBLY_ERR_CNTR_PAEC          BITS(0,31)             /*!< MMC receive packet assembly error counter */

/* ENET_MMC_RX_PACKETS_SMD_ERR_CNTR */
#define ENET_MMC_RX_PACKETS_SMD_ERR_CNTR_PSEC               BITS(0,31)             /*!< MMC receive packet SMD error counter */

/* ENET_MMC_RX_PACKETS_ASSEMBLY_OK_CNTR */
#define ENET_MMC_RX_PACKETS_ASSEMBLY_OK_CNTR_PAOC           BITS(0,31)             /*!< MMC receive packet assembly ok counter */

/* ENET_MMC_RX_FPE_FRAGMENT_CNTR */
#define ENET_MMC_RX_FPE_FRAGMENT_CNTR_FFC                   BITS(0,31)             /*!< MMC receive FPE fragment counter */

/* ENET_MAC_L3_L4_CONTROL */
#define ENET_MAC_L3_L4_CONTROL_L3PEN0                       BIT(0)                /*!< layer 3 protocol enable */
#define ENET_MAC_L3_L4_CONTROL_L3SAM0                       BIT(2)                /*!< layer 3 IP SA match enable */
#define ENET_MAC_L3_L4_CONTROL_L3SAIM0                      BIT(3)                /*!< layer 3 IP SA inverse match enable */
#define ENET_MAC_L3_L4_CONTROL_L3DAM0                       BIT(4)                /*!< layer 3 IP DA match enable */
#define ENET_MAC_L3_L4_CONTROL_L3DAIM0                      BIT(5)                /*!< layer 3 IP DA inverse match enable */
#define ENET_MAC_L3_L4_CONTROL_L3HSBM0                      BITS(6,10)            /*!< layer 3 IP SA higher bits match */
#define ENET_MAC_L3_L4_CONTROL_L3HDBM0                      BITS(11,15)           /*!< layer 3 IP DA higher bits match */
#define ENET_MAC_L3_L4_CONTROL_L4PEN0                       BIT(16)               /*!< layer 4 protocol enable */
#define ENET_MAC_L3_L4_CONTROL_L4SPM0                       BIT(18)               /*!< layer 4 source port match enable */
#define ENET_MAC_L3_L4_CONTROL_L4SPIM0                      BIT(19)               /*!< layer 4 source port inverse match enable */
#define ENET_MAC_L3_L4_CONTROL_L4DPM0                       BIT(20)               /*!< layer 4 destination port match enable */
#define ENET_MAC_L3_L4_CONTROL_L4DPIM0                      BIT(21)               /*!< layer 4 destination port inverse match enable */
#define ENET_MAC_L3_L4_CONTROL_DMCHN0                       BIT(24)               /*!< DMA channel number */
#define ENET_MAC_L3_L4_CONTROL_DMCHEN0                      BIT(28)               /*!< DMA channel select enable */

/* ENET_MAC_LAYER4_ADDRESS */
#define ENET_MAC_LAYER4_ADDRESS_L4SP0                       BITS(0,15)            /*!< layer 4 source port number field */
#define ENET_MAC_LAYER4_ADDRESS_L4DP0                       BITS(16,31)           /*!< layer 4 destination port number field */

/* ENET_MAC_LAYER3_ADDR0_REG */
#define ENET_MAC_LAYER3_ADDR0_REG_L3A00                     BITS(0,31)            /*!< layer 3 address 0 field */

/* ENET_MAC_LAYER3_ADDR1_REG */
#define ENET_MAC_LAYER3_ADDR1_REG_L3A10                     BITS(0,31)            /*!< layer 3 address 1 field */

/* ENET_MAC_LAYER3_ADDR2_REG */
#define ENET_MAC_LAYER3_ADDR2_REG_L3A20                     BITS(0,31)            /*!< layer 3 address 2 field */

/* ENET_MAC_LAYER3_ADDR3_REG */
#define ENET_MAC_LAYER3_ADDR3_REG_L3A30                     BITS(0,31)            /*!< layer 3 address 3 field */

/* ENET_MAC_INDIR_ACCESS_CTRL */
#define ENET_MAC_INDIR_ACCESS_CTRL_OB                       BIT(0)                /*!< operation busy */
#define ENET_MAC_INDIR_ACCESS_CTRL_COM                      BIT(1)                /*!< command type */
#define ENET_MAC_INDIR_ACCESS_CTRL_AUTO                     BIT(5)                /*!< auto increment */
#define ENET_MAC_INDIR_ACCESS_CTRL_AOFF                     BITS(8,15)            /*!< address offset */
#define ENET_MAC_INDIR_ACCESS_CTRL_MSEL                     BITS(16,19)           /*!< mode select */
#define ENET_MAC_INDIR_ACCESS_CTRL_SNPS_R                   BIT(31)               /*!< testable: untestable */

/* ENET_MAC_INDIR_ACCESS_DATA */
#define ENET_MAC_INDIR_ACCESS_DATA_DATA                     BITS(0,31)            /*!< MAC indirect access data */

/* ENET_MAC_TMRQ_REGS */
#define ENET_MAC_TMRQ_REGS_TYP                              BITS(0,15)            /*!< type field value */
#define ENET_MAC_TMRQ_REGS_TMRQ                             BITS(16,18)           /*!< type match Rx queue number */
#define ENET_MAC_TMRQ_REGS_PFEX                             BIT(20)               /*!< preemption or express packet */

/* ENET_MAC_TIMESTAMP_CONTROL */
#define MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(regval)           (BITS(16,17) & ((uint32_t)(regval) << 16))    /*!< write value to ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL bit field */

#define ENET_MAC_TIMESTAMP_CONTROL_TSENA                    BIT(0)                /*!< enable timestamp */
#define ENET_MAC_TIMESTAMP_CONTROL_TSCFUPDT                 BIT(1)                /*!< fine or coarse timestamp update */
#define ENET_MAC_TIMESTAMP_CONTROL_TSINIT                   BIT(2)                /*!< initialize timestam */
#define ENET_MAC_TIMESTAMP_CONTROL_TSUPDT                   BIT(3)                /*!< update timestamp */
#define ENET_MAC_TIMESTAMP_CONTROL_TSADDREG                 BIT(5)                /*!< update addend register */
#define ENET_MAC_TIMESTAMP_CONTROL_PTGE                     BIT(6)                /*!< presentation time generation enable */
#define ENET_MAC_TIMESTAMP_CONTROL_TSENALL                  BIT(8)                /*!< enable timestamp for all packets */
#define ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR                BIT(9)                /*!< timestamp digital or binary rollover control */
#define ENET_MAC_TIMESTAMP_CONTROL_TSVER2ENA                BIT(10)               /*!< enable PTP packet processing for version 2 format */
#define ENET_MAC_TIMESTAMP_CONTROL_TSIPENA                  BIT(11)               /*!< enable processing of PTP over ethernet packets */
#define ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA                BIT(12)               /*!< enable processing of PTP packets sent over IPv6-UDP */
#define ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA                BIT(13)               /*!< enable processing of PTP packets sent over IPv4-UDP */
#define ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA                BIT(14)               /*!< enable timestamp snapshot for event messages */
#define ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA                BIT(15)               /*!< enable snapshot for messages relevant to master */
#define ENET_MAC_TIMESTAMP_CONTROL_SNAPTYPSEL                BITS(16,17)           /*!< Select PTP packets for taking snapshots */
#define ENET_MAC_TIMESTAMP_CONTROL_TSENMACADDR              BIT(18)               /*!< enable MAC address for PTP packet filtering */
#define ENET_MAC_TIMESTAMP_CONTROL_TXTSSTSM                 BIT(24)               /*!< transmit timestamp status mode */
#define ENET_MAC_TIMESTAMP_CONTROL_AV8021ASMEN              BIT(28)               /*!< AV 802.1AS mode enable */

/* ENET_MAC_SUB_SECOND_INCREMENT */
#define ENET_MAC_SUB_SECOND_INCREMENT_SNSINC                BITS(8,15)            /*!< sub-nanosecond increment value */
#define ENET_MAC_SUB_SECOND_INCREMENT_SSINC                 BITS(16,23)           /*!< sub-second increment value */

/* ENET_MAC_SYSTEM_TIME_SECONDS */
#define ENET_MAC_SYSTEM_TIME_SECONDS_TSS                    BITS(0,31)            /*!< timestamp second */

/* ENET_MAC_SYSTEM_TIME_NANOSECONDS */
#define ENET_MAC_SYSTEM_TIME_NANOSECONDS_TSSS               BITS(0,30)            /*!< timestamp sub second */

/* ENET_MAC_SYSTEM_TIME_SECONDS_UPDATE */
#define ENET_MAC_SYSTEM_TIME_SECONDS_UPDATE_TSS             BITS(0,31)            /*!< timestamp second */

/* ENET_MAC_SYSTEM_TIME_NANOSECONDS */
#define ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS        BITS(0,30)            /*!< timestamp sub second */
#define ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB      BIT(31)               /*!< add or subtract time */

/* ENET_MAC_TIMESTAMP_ADDEND */
#define ENET_MAC_TIMESTAMP_ADDEND_TSAR                      BITS(0,31)            /*!< timestamp addend register */

/* ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS */
#define ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR      BITS(0,15)            /*!< timestamp higher word register */

/* ENET_MAC_TIMESTAMP_STATUS */
#define ENET_MAC_TIMESTAMP_STATUS_TSSOVF                    BIT(0)                /*!< timestamp seconds overflow */
#define ENET_MAC_TIMESTAMP_STATUS_TSTARGT0                  BIT(1)                /*!< timestamp target timereached */
#define ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR0                BIT(3)                /*!< timestamp target time error */
#define ENET_MAC_TIMESTAMP_STATUS_TSTARGT1                  BIT(4)                /*!< timestamp target timereached for target time PPS1 */
#define ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR1                BIT(5)                /*!< timestamp target time error */
#define ENET_MAC_TIMESTAMP_STATUS_TSTARGT2                  BIT(6)                /*!< timestamp target timereached for target time PPS2 */
#define ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR2                BIT(7)                /*!< timestamp target time error */
#define ENET_MAC_TIMESTAMP_STATUS_TSTARGT3                  BIT(8)                /*!< timestamp target timereached for target time PPS3 */
#define ENET_MAC_TIMESTAMP_STATUS_TSTRGTERR3                BIT(9)                /*!< timestamp target time error */
#define ENET_MAC_TIMESTAMP_STATUS_TXTSSIS                   BIT(15)               /*!< Tx timestamp status interrupt status */

/* ENET_MAC_RX_DOMAIN_TIME_INCR */
#define ENET_MAC_RX_DOMAIN_TIME_INCR_RXSNS                  BITS(8,15)            /*!< receive domain time increment value in sub-nanoseconds */
#define ENET_MAC_RX_DOMAIN_TIME_INCR_RXNS                   BITS(16,31)           /*!< receive domain time increment value in nanoseconds */

/* ENET_MAC_TX_DOMAIN_TIME_INCR */
#define ENET_MAC_TX_DOMAIN_TIME_INCR_TXSNS                  BITS(8,15)            /*!< transmit domain time increment value in sub-nanoseconds */
#define ENET_MAC_TX_DOMAIN_TIME_INCR_TXNS                   BITS(16,31)           /*!< transmit domain time increment value in nanoseconds */

/* ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS */
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO    BITS(0,30)            /*!< transmit timestamp status low */
#define ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS   BIT(31)               /*!< transmit timestamp status missed */

/* ENET_MAC_TX_TIMESTAMP_STATUS_SECONDS */
#define ENET_MAC_TX_TIMESTAMP_STATUS_SECONDS_TXTSSHI        BITS(0,31)            /*!< transmit timestamp status high */

/* ENET_MAC_TIMESTAMP_INGRESS_ASYM_CORR */
#define ENET_MAC_TIMESTAMP_INGRESS_ASYM_CORR_OSTIAC         BITS(0,31)            /*!< one-step timestamp ingress asymmetry correction */

/* ENET_MAC_TIMESTAMP_EGRESS_ASYM_CORR */
#define ENET_MAC_TIMESTAMP_EGRESS_ASYM_CORR_OSTEAC          BITS(0,31)            /*!< one-step timestamp egress asymmetry correction */

/* ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECONDS */
#define ENET_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_TSIC    BITS(0,31)             /*!< timestamp ingress correction */

/* ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECONDS */
#define ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_TSEC     BITS(0,31)             /*!< timestamp egress correction */

/* ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC */
#define ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS  BITS(0,31)            /*!< timestamp ingress correction, sub-nanoseconds */

/* ENET_MAC_TIMESTAMP_EGRESS_CORR_NANOSECONDS */
#define ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS   BITS(0,31)            /*!< timestamp egress correction, sub-nanoseconds */

/* ENET_MAC_TIMESTAMP_INGRESS_LATENCY */
#define ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS           BITS(8,15)            /*!< ingress timestamp latency, in nanoseconds */
#define ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS            BITS(16,27)           /*!< ingress timestamp latency, in sub-nanoseconds */

/* ENET_MAC_TIMESTAMP_EGRESS_LATENCY */
#define ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS           BITS(8,15)             /*!< egress timestamp latency, in nanoseconds */
#define ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS            BITS(16,27)            /*!< egress timestamp latency, in sub-nanoseconds */

/* ENET_MAC_PPS_CONTROL */
#define ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD                BITS(0,3)     /*!< PPS output frequency control, flexible PPS output control or presentation time control */
#define ENET_MAC_PPS_CONTROL_PPSEN0                BIT(4)                /*!< flexible PPS output mode enable */
#define ENET_MAC_PPS_CONTROL_TRGTMODSEL0           BITS(5,6)             /*!< target time register mode for PPS0 output */
#define ENET_MAC_PPS_CONTROL_MCGREN0               BIT(7)                /*!< MCGR mode enable for PPS0 output */
#define ENET_MAC_PPS_CONTROL_PPSCMD1               BITS(8,11)            /*!< flexible PPS1 output control */
#define ENET_MAC_PPS_CONTROL_TRGTMODSEL1           BITS(13,14)           /*!< target time register mode for PPS1 output */
#define ENET_MAC_PPS_CONTROL_MCGREN1               BIT(15)               /*!< MCGR mode enable for PPS1 output */
#define ENET_MAC_PPS_CONTROL_PPSCMD2               BITS(16,19)           /*!< flexible PPS2 output control */
#define ENET_MAC_PPS_CONTROL_TRGTMODSEL2           BITS(21,22)           /*!< target time register mode for PPS2 output */
#define ENET_MAC_PPS_CONTROL_MCGREN2               BIT(23)               /*!< MCGR mode enable for PPS2 output */
#define ENET_MAC_PPS_CONTROL_PPSCMD3               BITS(24,27)           /*!< flexible PPS3 output control */
#define ENET_MAC_PPS_CONTROL_TIMESEL               BIT(28)               /*!< time select */
#define ENET_MAC_PPS_CONTROL_TRGTMODSEL3           BITS(29,30)           /*!< target time register mode for PPS3 output */
#define ENET_MAC_PPS_CONTROL_MCGREN3               BIT(31)               /*!< MCGR mode enable for PPS3 output */

/* ENET_MAC_PPS_TARGET_TIME_SECONDS */
#define ENET_MAC_PPS_TARGET_TIME_SECONDS_TSTRH0            BITS(0,31)            /*!< PPS target time seconds register */

/* ENET_MAC_PPS_TARGET_TIME_NANOSECONDS */
#define ENET_MAC_PPS_TARGET_TIME_NANOSECONDS_TTSL0         BITS(0,30)            /*!< target time low for PPS register */
#define ENET_MAC_PPS_TARGET_TIME_NANOSECONDS_TRGTBUSY0     BIT(31)               /*!< PPS target time register busy */

/* ENET_MAC_PPS_INTERVAL */
#define ENET_MAC_PPS_INTERVAL_PPSINT0                      BITS(0,31)            /*!< PPS output signal interval */

/* ENET_MAC_PPS_WIDTH */
#define ENET_MAC_PPS_WIDTH_PPSWIDTH0                       BITS(0,31)            /*!< PPS output signal width */

/* ENET_MTL_OPERATION_MODE */
#define ENET_MTL_OPERATION_MODE_DTXSTS                     BIT(1)                /*!< drop transmit status */
#define ENET_MTL_OPERATION_MODE_RAA                        BIT(2)                /*!< receive arbitration algorithm */
#define ENET_MTL_OPERATION_MODE_SCHALG                     BITS(5,6)             /*!< Tx scheduling algorithm */
#define ENET_MTL_OPERATION_MODE_CNTPRST                    BIT(8)                /*!< counters preset */
#define ENET_MTL_OPERATION_MODE_CNTCLR                     BIT(9)                /*!< counters reset */
#define ENET_MTL_OPERATION_MODE_RXPED                      BIT(14)               /*!< Rx parser software error/incomplete parsing packet drop enable */
#define ENET_MTL_OPERATION_MODE_FRPE                       BIT(15)               /*!< flexible Rx parser enable */

/* ENET_MTL_DBG_CTL */
#define ENET_MTL_DBG_CTL_FDBGEN                            BIT(0)                /*!< FIFO debug access enable */
#define ENET_MTL_DBG_CTL_DBGMOD                            BIT(1)                /*!< debug mode access to FIFO */
#define ENET_MTL_DBG_CTL_BYTEEN                            BITS(2,3)             /*!< byte enables */
#define ENET_MTL_DBG_CTL_PKTSTATE                          BITS(5,6)             /*!< encoded packet state */
#define ENET_MTL_DBG_CTL_RSTAL                             BIT(8)                /*!< reset all pointers */
#define ENET_MTL_DBG_CTL_RSTSEL                            BIT(9)                /*!< reset pointers of selected FIFO */
#define ENET_MTL_DBG_CTL_FIFORDEN                          BIT(10)               /*!< FIFO read enable */
#define ENET_MTL_DBG_CTL_FIFOWREN                          BIT(11)               /*!< FIFO write enable */
#define ENET_MTL_DBG_CTL_FIFOSEL                           BITS(12,13)           /*!< FIFO selected for access */
#define ENET_MTL_DBG_CTL_PKTIE                             BIT(14)               /*!< receive packet available interrupt status enable */
#define ENET_MTL_DBG_CTL_STSIE                             BIT(15)               /*!< transmit status available interrupt status enable */
#define ENET_MTL_DBG_CTL_EIEE                              BIT(16)               /*!< ECC inject error enable for Tx, Rx memories */
#define ENET_MTL_DBG_CTL_EIAEE                             BIT(17)               /*!< ECC inject address error for Tx, Rx memories */
#define ENET_MTL_DBG_CTL_EIEC                              BIT(18)               /*!< ECC inject error control for Tx, Rx memories */

/* ENET_MTL_DBG_STS */
#define ENET_MTL_DBG_STS_FIFOBUSY                          BIT(0)                /*!< FIFO busy */
#define ENET_MTL_DBG_STS_PKTSTATE                          BITS(1,2)             /*!< encoded packet state */
#define ENET_MTL_DBG_STS_BYTEEN                            BITS(3,4)             /*!< byte enables */
#define ENET_MTL_DBG_STS_PKTI                              BIT(8)                /*!< receive packet available interrupt status */
#define ENET_MTL_DBG_STS_STSI                              BIT(9)                /*!< transmit status available interrupt status */
#define ENET_MTL_DBG_STS_LOCR                              BITS(15,31)           /*!< remaining l ocations in the FIFO */

/* ENET_MTL_FIFO_DEBUG_DATA */
#define ENET_MTL_FIFO_DEBUG_DATA_FDBGDATA                  BITS(0,31)            /*!< FIFO debug data */

/* ENET_MTL_INTERRUPT_STATUS */
#define ENET_MTL_INTERRUPT_STATUS_Q0IS                     BIT(0)                /*!< queue 0 interrupt status */
#define ENET_MTL_INTERRUPT_STATUS_Q1IS                     BIT(1)                /*!< queue 1 interrupt status */
#define ENET_MTL_INTERRUPT_STATUS_DBGIS                    BIT(17)               /*!< debug interrupt status */
#define ENET_MTL_INTERRUPT_STATUS_ESTIS                    BIT(18)               /*!< EST (TAS- 802.1Qbv) interrupt status */
#define ENET_MTL_INTERRUPT_STATUS_MTLPIS                   BIT(23)               /*!< MTL Rx parser interrupt status */

/* ENET_MTL_RXQ_DMA_MAP0 */
#define ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH                     BIT(0)                /*!< queue 0 mapped to DMA channel */
#define ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH                     BIT(4)                /*!< queue 0 enabled for DA-based DMA channel selection */
#define ENET_MTL_RXQ_DMA_MAP0_Q1MDMACH                     BIT(8)                /*!< queue 1 mapped to DMA channel */
#define ENET_MTL_RXQ_DMA_MAP0_Q1DDMACH                     BIT(12)               /*!< queue 1 enabled for DA-based DMA channel selection */

/* ENET_MTL_TBS_CTRL */
#define ENET_MTL_TBS_CTRL_ESTM                             BIT(0)                /*!< EST offset mode */
#define ENET_MTL_TBS_CTRL_LEOV                             BIT(1)                /*!< launch expiry offset valid */
#define ENET_MTL_TBS_CTRL_LEGOS                            BITS(4,6)             /*!< launch expiry GSN off */
#define ENET_MTL_TBS_CTRL_LEOS                             BITS(8,31)            /*!< launch expiry offset */

/* ENET_MTL_EST_CONTROL */
#define ENET_MTL_EST_CONTROL_EEST                          BIT(0)                /*!< enable EST */
#define ENET_MTL_EST_CONTROL_SSWL                          BIT(1)                /*!< switch to S/W owned list */
#define ENET_MTL_EST_CONTROL_QHLBF                         BIT(3)                /*!< quick assertion of HLBF error */
#define ENET_MTL_EST_CONTROL_DDBF                          BIT(4)                /*!< do not drop frames during frame size error */
#define ENET_MTL_EST_CONTROL_DFBS                          BIT(5)                /*!< drop frames causing scheduling error */
#define ENET_MTL_EST_CONTROL_LCSE                          BITS(6,7)             /*!< loop count to report scheduling error */
#define ENET_MTL_EST_CONTROL_TILS                          BITS(8,10)            /*!< time interval left shift amount */
#define ENET_MTL_EST_CONTROL_CTOV                          BITS(12,23)           /*!< current time offset value */
#define ENET_MTL_EST_CONTROL_PTOV                          BITS(24,31)           /*!< PTP time offset value */

/* ENET_MTL_EST_EXT_CONTROL */
#define ENET_MTL_EST_EXT_CONTROL_OVHD                      BITS(0,5)             /*!< overhead bytes value */

/* ENET_MTL_EST_STATUS */
#define ENET_MTL_EST_STATUS_SWLC                          BIT(0)                /*!< switch to S/W owned list complete */
#define ENET_MTL_EST_STATUS_BTRE                          BIT(1)                /*!< BTR error */
#define ENET_MTL_EST_STATUS_HLBF                          BIT(2)                /*!< head-of-line blocking due to frame size */
#define ENET_MTL_EST_STATUS_HLBS                          BIT(3)                /*!< head-of-line blocking due to scheduling */
#define ENET_MTL_EST_STATUS_CGCE                          BIT(4)                /*!< constant gate control error */
#define ENET_MTL_EST_STATUS_SWOL                          BIT(7)                /*!< S/W owned list */
#define ENET_MTL_EST_STATUS_BTR                           BITS(8,15)            /*!< BTR error loop count */
#define ENET_MTL_EST_STATUS_CGSN                          BITS(16,19)           /*!< current GCL slot number */

/* ENET_MTL_EST_SCH_ERROR */
#define ENET_MTL_EST_SCH_ERROR_SEQN                       BITS(0,1)             /*!< schedule error queue number */

/* ENET_MTL_EST_FRM_SIZE_ERROR */
#define ENET_MTL_EST_FRM_SIZE_ERROR_FEQN                  BITS(0,1)             /*!< frame size error queue number */

/* ENET_MTL_EST_FRM_SIZE_CAPTURE */
#define ENET_MTL_EST_FRM_SIZE_CAPTURE_HBFS                BITS(0,14)            /*!< frame size of HLBF */
#define ENET_MTL_EST_FRM_SIZE_CAPTURE_HBFQ                BIT(16)               /*!< queue number of HLBF */

/* ENET_MTL_EST_INTR_ENABLE */
#define ENET_MTL_EST_INTR_ENABLE_IECC                     BIT(0)                /*!< interrupt enable for switch list */
#define ENET_MTL_EST_INTR_ENABLE_IEBE                     BIT(1)                /*!< interrupt enable for BTR Error */
#define ENET_MTL_EST_INTR_ENABLE_IEHF                     BIT(2)                /*!< interrupt enable for HLBF */
#define ENET_MTL_EST_INTR_ENABLE_IEHS                     BIT(3)                /*!< interrupt enable for HLBS */
#define ENET_MTL_EST_INTR_ENABLE_CGCE                     BIT(4)                /*!< interrupt enable for CGCE */

/* ENET_MTL_EST_GCL_CONTROL */
#define ENET_MTL_EST_GCL_CONTROL_SRWO                     BIT(0)                /*!< start read/write operation */
#define ENET_MTL_EST_GCL_CONTROL_R1W0                     BIT(1)                /*!< read '1', write '0' */
#define ENET_MTL_EST_GCL_CONTROL_GCRR                     BIT(2)                /*!< gate control related registers */
#define ENET_MTL_EST_GCL_CONTROL_DBGM                     BIT(4)                /*!< debug mode */
#define ENET_MTL_EST_GCL_CONTROL_DBGB                     BIT(5)                /*!< debug mode bank select */
#define ENET_MTL_EST_GCL_CONTROL_ADDR                     BITS(8,15)            /*!< gate control list address or related registers address */
#define ENET_MTL_EST_GCL_CONTROL_ESTEIEE                  BIT(21)               /*!< EST ECC inject error enable */
#define ENET_MTL_EST_GCL_CONTROL_ESTEIAEE                 BIT(22)               /*!< EST ECC inject address error enable */
#define ENET_MTL_EST_GCL_CONTROL_ESTEIEC                  BIT(23)               /*!< ECC inject error control for EST memory */

/* ENET_MTL_EST_GCL_DATA */
#define ENET_MTL_EST_GCL_DATA_GCD                         BITS(0,31)            /*!< gate control data */

/* ENET_MTL_FPE_CTRL_STS */
#define ENET_MTL_FPE_CTRL_STS_AFSZ                        BITS(0,1)             /*!< additional fragment size */
#define ENET_MTL_FPE_CTRL_STS_LBHT                        BIT(7)                /*!< level based hold transition */
#define ENET_MTL_FPE_CTRL_STS_PEC                         BITS(8,9)             /*!< preemption classification */
#define ENET_MTL_FPE_CTRL_STS_HRS                         BIT(28)               /*!< hold/release status */

/* ENET_MTL_FPE_ADVANCE */
#define ENET_MTL_FPE_ADVANCE_HADV                         BITS(0,15)            /*!< hold advance */
#define ENET_MTL_FPE_ADVANCE_RADV                         BITS(16,31)           /*!< release advance */

/* ENET_MTL_RXP_CONTROL_STATUS */
#define ENET_MTL_RXP_CONTROL_STATUS_NVE                   BITS(0,7)             /*!< number of valid entry address/index in the instruction table */
#define ENET_MTL_RXP_CONTROL_STATUS_NPE                   BITS(16,23)           /*!< number of parsable entries in the instruction table */
#define ENET_MTL_RXP_CONTROL_STATUS_ELIRS                 BIT(30)               /*!< enable last instruction in Rx status */
#define ENET_MTL_RXP_CONTROL_STATUS_RXPI                  BIT(31)               /*!< RX parser in idle state */

/* ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIS     BIT(0)                /*!< number of valid entry address/index overflow interrupt status */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIS     BIT(1)                /*!< number of parsable entries overflow interrupt status */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIS      BIT(2)                /*!< frame offset overflow interrupt status */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIS      BIT(3)                /*!< packet dropped due to RF interrupt status */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS_NVEOVIE     BIT(16)               /*!< number of valid entries overflow interrupt enable */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS_NPEOVIE     BIT(17)               /*!< number of parsable entries overflow interrupt enable */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS_FOOVIE      BIT(18)               /*!< frame offset overflow interrupt enable */
#define ENET_MTL_RXP_INTERRUPT_CONTROL_STATUS_PDRFIE      BIT(19)               /*!< packet drop due to RF interrupt enable */

/* ENET_MTL_RXP_DROP_CNT */
#define ENET_MTL_RXP_DROP_CNT_RXPDC                       BITS(0,30)            /*!< Rx parser drop count */
#define ENET_MTL_RXP_DROP_CNT_RXPDCOVF                    BIT(31)               /*!< Rx parser drop counter overflow */

/* ENET_MTL_RXP_ERROR_CNT */
#define ENET_MTL_RXP_ERROR_CNT_RXPEC                       BITS(0,30)           /*!< Rx parser error count */
#define ENET_MTL_RXP_ERROR_CNT_RXPECOVF                    BIT(31)              /*!< Rx parser error counter overflow */

/* ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS */
#define ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR      BITS(0,7)            /*!< FRP instruction table offset address */
#define ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN     BIT(16)              /*!< read write control */
#define ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIEE   BIT(20)              /*!< ECC inject error enable for Rx parser memory */
#define ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIAEE  BIT(21)              /*!< ECC inject address error enable for Rx parser memory */
#define ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIEC   BIT(22)              /*!< ECC inject error control for Rx parser memory */
#define ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY BIT(31)              /*!< FRP instruction table access busy */

/* ENET_MTL_RXP_INDIRECT_ACC_DATA */
#define ENET_MTL_RXP_INDIRECT_ACC_DATA_DATA                BITS(0,31)           /*!< FRP instruction table write/read data */

/* ENET_MTL_RXP_BYPASS_CNT */
#define ENET_MTL_RXP_BYPASS_CNT_RXPBC                      BITS(0,30)           /*!< Rx parser bypass count */
#define ENET_MTL_RXP_BYPASS_CNT_RXPBCOF                    BIT(31)              /*!< Rx parser bypass counter overflow */

/* ENET_MTL_ECC_CONTROL */
#define ENET_MTL_ECC_CONTROL_MTXEE                         BIT(0)               /*!< MTL Tx FIFO ECC enable */
#define ENET_MTL_ECC_CONTROL_MRXEE                         BIT(1)               /*!< MTL Rx FIFO ECC enable */
#define ENET_MTL_ECC_CONTROL_MESTEE                        BIT(2)               /*!< MTL EST ECC enable */
#define ENET_MTL_ECC_CONTROL_MRXPEE                        BIT(3)               /*!< MTL Rx Parser ECC enable */
#define ENET_MTL_ECC_CONTROL_MEEAO                         BIT(8)               /*!< MTL ECC error address status over-ride */

/* ENET_MTL_SAFETY_INTERRUPT_STATUS */
#define ENET_MTL_SAFETY_INTERRUPT_STATUS_MECIS             BIT(0)               /*!< MTL ECC correctable error interrupt status */
#define ENET_MTL_SAFETY_INTERRUPT_STATUS_MEUIS             BIT(1)               /*!< MTL ECC unCorrectable error interrupt status */

/* ENET_MTL_ECC_INTERRUPT_ENABLE */
#define ENET_MTL_ECC_INTERRUPT_ENABLE_TXCEIE               BIT(0)               /*!< Tx memory correctable error interrupt enable */
#define ENET_MTL_ECC_INTERRUPT_ENABLE_RXCEIE               BIT(4)               /*!< Rx memory correctable error interrupt enable */
#define ENET_MTL_ECC_INTERRUPT_ENABLE_ECEIE                BIT(8)               /*!< EST memory correctable error interrupt enable */
#define ENET_MTL_ECC_INTERRUPT_ENABLE_RPCEIE               BIT(12)              /*!< Rx parser memory correctable error interrupt enable */

/* ENET_MTL_ECC_INTERRUPT_STATUS */
#define ENET_MTL_ECC_INTERRUPT_STATUS_TXCES                BIT(0)               /*!< MTL Tx memory correctable error status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_TXAMS                BIT(1)               /*!< MTL Tx memory address mismatch status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_TXUES                BIT(2)               /*!< MTL Tx memory unCorrectable error status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_RXCES                BIT(4)               /*!< MTL Rx memory Correctable error status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_RXAMS                BIT(5)               /*!< MTL Rx memory address mismatch status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_RXUES                BIT(6)               /*!< MTL Rx memory unCorrectable error status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_ECES                 BIT(8)               /*!< MTL EST memory correctable error status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_EAMS                 BIT(9)               /*!< MTL EST memory address mismatch status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_EUES                 BIT(10)              /*!< MTL EST memory unCorrectable error status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_RPCES                BIT(12)              /*!< MTL Rx parser memory correctable error status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_RPAMS                BIT(13)              /*!< MTL Rx parser memory address mismatch status */
#define ENET_MTL_ECC_INTERRUPT_STATUS_RPUES                BIT(14)              /*!< Rx parser memory unCorrectable error status */

/* ENET_MTL_ECC_ERR_STS_RCTL */
#define ENET_MTL_ECC_ERR_STS_RCTL_EESRE                    BIT(0)               /*!< MTL ECC error status read enable */
#define ENET_MTL_ECC_ERR_STS_RCTL_EMS                      BITS(1,3)            /*!< MTL ECC memory selection */
#define ENET_MTL_ECC_ERR_STS_RCTL_CCES                     BIT(4)               /*!< clear correctable error status */
#define ENET_MTL_ECC_ERR_STS_RCTL_CUES                     BIT(5)               /*!< clear unCorrectable error status */

/* ENET_MTL_ECC_ERR_ADDR_STATUS */
#define ENET_MTL_ECC_ERR_ADDR_STATUS_ECEAS                 BITS(0,15)           /*!< MTL ECC correctable error address status */
#define ENET_MTL_ECC_ERR_ADDR_STATUS_EUEAS                 BITS(16,31)          /*!< MTL ECC uncorrectable error address status */

/* ENET_MTL_ECC_ERR_CNTR_STATUS */
#define ENET_MTL_ECC_ERR_CNTR_STATUS_ECECS                 BITS(0,7)            /*!< MTL ECC correctable error counter status */
#define ENET_MTL_ECC_ERR_CNTR_STATUS_EUECS                 BITS(16,19)          /*!< MTL ECC uncorrectable error counter status */

/* ENET_MTL_DPP_CONTROL */
#define ENET_MTL_DPP_CONTROL_EDPP                          BIT(0)               /*!< enable data path parity protection */
#define ENET_MTL_DPP_CONTROL_OPE                           BIT(1)               /*!< odd parity enable */
#define ENET_MTL_DPP_CONTROL_EPSI                          BIT(2)               /*!< enable parity on slave interface port */
#define ENET_MTL_DPP_CONTROL_IPETID                        BIT(4)               /*!< insert parity error in Tx interface data parity checker */
#define ENET_MTL_DPP_CONTROL_IPETRD                        BIT(6)               /*!< insert parity error in DMA Tx/Rx descriptor parity checker */
#define ENET_MTL_DPP_CONTROL_IPEMTF                        BIT(7)               /*!< insert parity error in MTL Tx FIFO write data parity checker */
#define ENET_MTL_DPP_CONTROL_IPEMTS                        BIT(8)               /*!< insert parity error in MTL Tx status FIFO parity checker */
#define ENET_MTL_DPP_CONTROL_IPERID                        BIT(9)               /*!< insert parity error in RX interface data parity checker */
#define ENET_MTL_DPP_CONTROL_IPEMTBU                       BIT(13)              /*!< insert parity error in MAC TBU data parity checker */
#define ENET_MTL_DPP_CONTROL_IPEMTFC                       BIT(14)              /*!< insert parity error in MAC TFC data parity checker */
#define ENET_MTL_DPP_CONTROL_IPEMRWC                       BIT(15)              /*!< insert parity error in MTL RWC data parity checker */

/* ENET_MTL_DPP_ECC_EIC */
#define ENET_MTL_DPP_ECC_EIC_BLEI                          BITS(0,7)            /*!< bit location of error injection */
#define ENET_MTL_DPP_ECC_EIC_EIM                           BIT(16)              /*!< error injection mode */

/* ENET_MTL_TXQ0_OPERATION_MODE */
#define ENET_MTL_TXQ0_OPERATION_MODE_FTQ                   BIT(0)               /*!< flush transmit queue */
#define ENET_MTL_TXQ0_OPERATION_MODE_TSF                   BIT(1)               /*!< transmit store-and-forward */
#define ENET_MTL_TXQ0_OPERATION_MODE_TXQEN                 BITS(2,3)            /*!< transmit queue enable */
#define ENET_MTL_TXQ0_OPERATION_MODE_TTC                   BITS(4,6)            /*!< transmit threshold control */
#define ENET_MTL_TXQ0_OPERATION_MODE_TQS                   BITS(16,20)          /*!< transmit queue size */

/* ENET_MTL_TXQ0_UNDERFLOW */
#define ENET_MTL_TXQ0_UNDERFLOW_UFFRMCNT                   BITS(0,10)           /*!< underflow packet counter */
#define ENET_MTL_TXQ0_UNDERFLOW_UFCNTOVF                   BIT(11)              /*!< overflow bit for underflow packet counter */

/* ENET_MTL_TXQ0_DEBUG */
#define ENET_MTL_TXQ0_DEBUG_TXQPAUSED                      BIT(0)               /*!< transmit queue in pause */
#define ENET_MTL_TXQ0_DEBUG_TRCSTS                         BITS(1,2)            /*!< MTL Tx queue read controller status */
#define ENET_MTL_TXQ0_DEBUG_TWCSTS                         BIT(3)               /*!< MTL Tx queue write controller status */
#define ENET_MTL_TXQ0_DEBUG_TXQSTS                         BIT(4)               /*!< MTL Tx queue not empty status */
#define ENET_MTL_TXQ0_DEBUG_TXSTSFSTS                      BIT(5)               /*!< MTL Tx status FIFO full status */
#define ENET_MTL_TXQ0_DEBUG_PTXQ                           BITS(16,18)          /*!< number of packets in the transmit queue */
#define ENET_MTL_TXQ0_DEBUG_STXSTSF                        BITS(20,22)          /*!< number of status words in Tx status FIFO of queue */

/* ENET_MTL_TXQ0_EST_STATUS */
#define ENET_MTL_TXQ0_ETS_STATUS_ABS                       BITS(0,23)           /*!< average bits per slot */

/* ENET_MTL_TXQ0_QUANTUM_WEIGHT */
#define ENET_MTL_TXQ0_QUANTUM_WEIGHT_ISCQW                 BITS(0,20)           /*!< weights */

/* ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS */
#define ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TQU           BIT(0)               /*!< transmit queue underflow interrupt status */
#define ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIS        BIT(1)               /*!< average bits per slot interrupt status */
#define ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_TXUIE         BIT(8)               /*!< transmit queue underflow interrupt enable */
#define ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_ABPSIE        BIT(9)               /*!< average bits per slot interrupt enable */
#define ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOVFIS       BIT(16)              /*!< receive queue overflow interrupt status */
#define ENET_MTL_Q0_INTERRUPT_CONTROL_STATUS_RXOIE         BIT(24)              /*!< receive queue overflow interrupt enable */

/* ENET_MTL_RXQ0_OPERATION_MODE */
#define ENET_MTL_RXQ0_OPERATION_MODE_RTC                   BITS(0,1)            /*!< receive queue threshold control */
#define ENET_MTL_RXQ0_OPERATION_MODE_FUP                   BIT(3)               /*!< forward undersized good packets */
#define ENET_MTL_RXQ0_OPERATION_MODE_FEP                   BIT(4)               /*!< forward error packets */
#define ENET_MTL_RXQ0_OPERATION_MODE_RSF                   BIT(5)               /*!< receive queue store and forward */
#define ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF            BIT(6)               /*!< disable dropping of TCP/IP checksum error packets */
#define ENET_MTL_RXQ0_OPERATION_MODE_EHFC                  BIT(7)               /*!< enable hardware flow control */
#define ENET_MTL_RXQ0_OPERATION_MODE_RFA                   BITS(8,11)           /*!< threshold for activating flow control */
#define ENET_MTL_RXQ0_OPERATION_MODE_RFD                   BITS(14,17)          /*!< threshold for deactivating flow control */
#define ENET_MTL_RXQ0_OPERATION_MODE_RQS                   BITS(20,24)          /*!< receive queue size */

/* ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT */
#define ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT BITS(0,10)           /*!< overflow packet counter */
#define ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFCNTOVF BIT(11)              /*!< overflow counter overflow */
#define ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MFCNT     BITS(16,26)          /*!< missed packet counter */
#define ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISCNTOVF BIT(27)              /*!< missed packet counter overflow */

/* ENET_MTL_RXQ0_DEBUG */
#define ENET_MTL_RXQ0_DEBUG_RWCSTS                         BIT(0)               /*!< MTL Rx queue write controller active status */
#define ENET_MTL_RXQ0_DEBUG_RRCSTS                         BITS(1,2)            /*!< MTL Rx queue read controller state */
#define ENET_MTL_RXQ0_DEBUG_RXQSTS                         BITS(4,5)            /*!< MTL Rx queue fill-level status */
#define ENET_MTL_RXQ0_DEBUG_PRXQ                           BITS(16,29)          /*!< number of packets in receive queue */

/* ENET_MTL_RXQ0_CONTROL */
#define ENET_MTL_RXQ0_CONTROL_RXQ_WEGT                     BITS(0,2)            /*!< receive queue weight */
#define ENET_MTL_RXQ0_CONTROL_RXQ_FRM_ARBIT                BIT(3)               /*!< receive queue packet arbitration */

/* ENET_MTL_TXQ1_OPERATION_MODE */
#define ENET_MTL_TXQ1_OPERATION_MODE_FTQ                   BIT(0)               /*!< flush transmit queue */
#define ENET_MTL_TXQ1_OPERATION_MODE_TSF                   BIT(1)               /*!< transmit store-and-forward */
#define ENET_MTL_TXQ1_OPERATION_MODE_TXQEN                 BITS(2,3)            /*!< transmit queue enable */
#define ENET_MTL_TXQ1_OPERATION_MODE_TTC                   BITS(4,6)            /*!< transmit threshold control */
#define ENET_MTL_TXQ1_OPERATION_MODE_TQS                   BITS(16,20)          /*!< transmit queue size */

/* ENET_MTL_TXQ1_UNDERFLOW */
#define ENET_MTL_TXQ1_UNDERFLOW_UFFRMCNT                   BITS(0,10)           /*!< underflow packet counter */
#define ENET_MTL_TXQ1_UNDERFLOW_UFCNTOVF                   BIT(11)              /*!< overflow bit for underflow packet counter */

/* ENET_MTL_TXQ1_DEBUG */
#define ENET_MTL_TXQ1_DEBUG_TXQPAUSED                      BIT(0)               /*!< transmit queue in pause */
#define ENET_MTL_TXQ1_DEBUG_TRCSTS                         BITS(1,2)            /*!< MTL Tx queue read controller status */
#define ENET_MTL_TXQ1_DEBUG_TWCSTS                         BIT(3)               /*!< MTL Tx queue write controller status */
#define ENET_MTL_TXQ1_DEBUG_TXQSTS                         BIT(4)               /*!< MTL Tx queue not empty status */
#define ENET_MTL_TXQ1_DEBUG_TXSTSFSTS                      BIT(5)               /*!< MTL Tx status FIFO full status */
#define ENET_MTL_TXQ1_DEBUG_PTXQ                           BITS(16,18)          /*!< number of packets in the transmit queue */
#define ENET_MTL_TXQ1_DEBUG_STXSTSF                        BITS(20,22)          /*!< number of status words in Tx status FIFO of queue */

/* ENET_MTL_TXQ1_ETS_CONTROL */
#define ENET_MTL_TXQ1_ETS_CONTROL_AVALG                    BIT(2)               /*!< AV algorithm */
#define ENET_MTL_TXQ1_ETS_CONTROL_CC                       BIT(3)               /*!< credit control */
#define ENET_MTL_TXQ1_ETS_CONTROL_SLC                      BITS(4,6)            /*!< slot count */

/* ENET_MTL_TXQ1_ETS_STATUS */
#define ENET_MTL_TXQ1_ETS_STATUS_ABS                       BITS(0,23)           /*!< average bits per slot */

/* ENET_MTL_TXQ1_QUANTUM_WEIGHT */
#define ENET_MTL_TXQ1_QUANTUM_WEIGHT_ISCQW                 BITS(0,20)           /*!< weights */

/* ENET_MTL_TXQ1_SENDSLOPECREDIT */
#define ENET_MTL_TXQ1_SENDSLOPECREDIT_SSC                  BITS(0,13)           /*!< sendSlopeCredit value */

/* ENET_MTL_TXQ1_HICREDIT */
#define ENET_MTL_TXQ1_HICREDIT_HC                          BITS(0,28)           /*!< hiCredit value */

/* ENET_MTL_TXQ1_LOCREDIT */
#define ENET_MTL_TXQ1_LOCREDIT_LC                          BITS(0,28)           /*!< loCredit value */

/* ENET_MTL_Q1_INTERRUPT_CONTROL_STATUS */
#define ENET_MTL_Q1_INTERRUPT_CONTROL_STATUS_TQU           BIT(0)               /*!< transmit queue underflow interrupt status */
#define ENET_MTL_Q1_INTERRUPT_CONTROL_STATUS_ABPSIS        BIT(1)               /*!< average bits per slot interrupt status */
#define ENET_MTL_Q1_INTERRUPT_CONTROL_STATUS_TXUIE         BIT(8)               /*!< transmit queue underflow interrupt enable */
#define ENET_MTL_Q1_INTERRUPT_CONTROL_STATUS_ABPSIE        BIT(9)               /*!< average bits per slot interrupt enable */
#define ENET_MTL_Q1_INTERRUPT_CONTROL_STATUS_RXOVFIS       BIT(16)              /*!< receive queue overflow interrupt status */
#define ENET_MTL_Q1_INTERRUPT_CONTROL_STATUS_RXOIE         BIT(24)              /*!< receive queue overflow interrupt enable */

/* ENET_MTL_RXQ1_OPERATION_MODE */
#define ENET_MTL_RXQ1_OPERATION_MODE_RTC                   BITS(0,1)            /*!< receive queue threshold control */
#define ENET_MTL_RXQ1_OPERATION_MODE_FUP                   BIT(3)               /*!< forward undersized good packets */
#define ENET_MTL_RXQ1_OPERATION_MODE_FEP                   BIT(4)               /*!< forward error packets */
#define ENET_MTL_RXQ1_OPERATION_MODE_RSF                   BIT(5)               /*!< receive queue store and forward */
#define ENET_MTL_RXQ1_OPERATION_MODE_DIS_TCP_EF            BIT(6)               /*!< disable dropping of TCP/IP checksum error packets */
#define ENET_MTL_RXQ1_OPERATION_MODE_EHFC                  BIT(7)               /*!< enable hardware flow control */
#define ENET_MTL_RXQ1_OPERATION_MODE_RFA                   BITS(8,11)           /*!< threshold for activating flow control */
#define ENET_MTL_RXQ1_OPERATION_MODE_RFD                   BITS(14,17)          /*!< threshold for deactivating flow control */
#define ENET_MTL_RXQ1_OPERATION_MODE_RQS                   BITS(20,24)          /*!< receive queue size */

/* ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT */
#define ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT BITS(0,10)           /*!< overflow packet counter */
#define ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_OVFCNTOVF BIT(11)              /*!< overflow counter overflow */
#define ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_MFCNT     BITS(16,26)          /*!< missed packet counter */
#define ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_MISCNTOVF BIT(27)              /*!< missed packet counter overflow */

/* ENET_MTL_RXQ1_DEBUG */
#define ENET_MTL_RXQ1_DEBUG_RWCSTS                         BIT(0)               /*!< MTL Rx queue write controller active status */
#define ENET_MTL_RXQ1_DEBUG_RRCSTS                         BITS(1,2)            /*!< MTL Rx queue read controller state */
#define ENET_MTL_RXQ1_DEBUG_RXQSTS                         BITS(4,5)            /*!< MTL Rx queue fill-level status */
#define ENET_MTL_RXQ1_DEBUG_PRXQ                           BITS(16,29)          /*!< number of packets in receive queue */

/* ENET_MTL_RXQ1_CONTROL */
#define ENET_MTL_RXQ1_CONTROL_RXQ_WEGT                     BITS(0,2)            /*!< receive queue weight */
#define ENET_MTL_RXQ1_CONTROL_RXQ_FRM_ARBIT                BIT(3)               /*!< receive queue packet arbitration */

/* ENET_DMA_MODE */
#define ENET_DMA_MODE_SWR                                  BIT(0)               /*!< software reset */
#define ENET_DMA_MODE_DA                                   BIT(1)               /*!< DMA Tx or Rx arbitration scheme */
#define ENET_DMA_MODE_TAA                                  BITS(2,4)            /*!< transmit arbitration algorithm */
#define ENET_DMA_MODE_TXPR                                 BIT(11)              /*!< transmit priority */
#define ENET_DMA_MODE_PR                                   BITS(12,14)          /*!< priority ratio */
#define ENET_DMA_MODE_INTM                                 BITS(16,17)          /*!< interrupt mode */

/* ENET_DMA_SYSBUS_MODE */
#define ENET_DMA_SYSBUS_MODE_FB                            BIT(0)               /*!< fixed burst length */
#define ENET_DMA_SYSBUS_MODE_AAL                           BIT(12)              /*!< address-aligned beats */
#define ENET_DMA_SYSBUS_MODE_MB                            BIT(14)              /*!< mixed burst */
#define ENET_DMA_SYSBUS_MODE_RB                            BIT(15)              /*!< rebuild INCRx burst */

/* ENET_DMA_INTERRUPT_STATUS */
#define ENET_DMA_INTERRUPT_STATUS_DC0IS                    BIT(0)               /*!< DMA channel 0 interrupt status */
#define ENET_DMA_INTERRUPT_STATUS_DC1IS                    BIT(1)               /*!< DMA channel 1 interrupt status */
#define ENET_DMA_INTERRUPT_STATUS_MTLIS                    BIT(16)              /*!< MTL interrupt status */
#define ENET_DMA_INTERRUPT_STATUS_MACIS                    BIT(17)              /*!< MAC interrupt status */

/* ENET_DMA_DEBUG_STATUS0 */
#define ENET_DMA_DEBUG_STATUS0_AXWHSTS                     BIT(0)               /*!< AHB master status */
#define ENET_DMA_DEBUG_STATUS0_RPS0                        BITS(8,11)           /*!< DMA channel 0 receive process state */
#define ENET_DMA_DEBUG_STATUS0_TPS0                        BITS(12,15)          /*!< DMA channel 0 transmit process state */
#define ENET_DMA_DEBUG_STATUS0_RPS1                        BITS(16,19)          /*!< DMA channel 1 receive process state */
#define ENET_DMA_DEBUG_STATUS0_TPS1                        BITS(20,23)          /*!< DMA channel 1 transmit process state */

/* ENET_DMA_TBS_CTRL0 */
#define ENET_DMA_TBS_CTRL0_FTOV                            BIT(0)               /*!< fetch time offset valid */
#define ENET_DMA_TBS_CTRL0_FGOS                            BITS(4,6)            /*!< fetch GSN offset */
#define ENET_DMA_TBS_CTRL0_FTOS                            BITS(8,31)           /*!< fetch time offset */

/* ENET_DMA_SAFETY_INTERRUPT_STATUS */
#define ENET_DMA_SAFETY_INTERRUPT_STATUS_DECIS             BIT(0)               /*!< DMA ECC correctable error interrupt status */
#define ENET_DMA_SAFETY_INTERRUPT_STATUS_DEUIS             BIT(1)               /*!< DMA ECC uncorrectable error interrupt status */
#define ENET_DMA_SAFETY_INTERRUPT_STATUS_MSCIS             BIT(28)              /*!< MTL safety correctable error interrupt status */
#define ENET_DMA_SAFETY_INTERRUPT_STATUS_MSUIS             BIT(29)              /*!< MTL safety uncorrectable error interrupt status */
#define ENET_DMA_SAFETY_INTERRUPT_STATUS_MCSIS             BIT(31)              /*!< MAC safety uncorrectable error interrupt status */

/* ENET_DMA_CH_CONTROL */
#define ENET_DMA_CH_CONTROL_PBLx8                          BIT(16)              /*!< 8xPBL mode */
#define ENET_DMA_CH_CONTROL_DSL                            BITS(18,20)          /*!< descriptor skip length */

/* ENET_DMA_CH_TX_CONTROL */
#define ENET_DMA_CH_TX_CONTROL_ST                          BIT(0)               /*!< start or stop transmission command */
#define ENET_DMA_CH_TX_CONTROL_TCW                         BITS(1,3)            /*!< transmit channel weight */
#define ENET_DMA_CH_TX_CONTROL_OSF                         BIT(4)               /*!< operate on second packet */
#define ENET_DMA_CH_TX_CONTROL_TxPBL                       BITS(16,21)          /*!< transmit programmable burst length */
#define ENET_DMA_CH_TX_CONTROL_DESE                        BIT(28)              /*!< enhanced descriptor enable */

/* ENET_DMA_CH_RX_CONTROL */
#define ENET_DMA_CH_RX_CONTROL_SR                          BIT(0)               /*!< start or stop receive */
#define ENET_DMA_CH_RX_CONTROL_RBSZ                        BITS(1,14)           /*!< receive buffer size */
#define ENET_DMA_CH_RX_CONTROL_RxPBL                       BITS(16,22)          /*!< receive programmable burst length */
#define ENET_DMA_CH_RX_CONTROL_RPF                         BIT(31)              /*!< Rx packet flush */

/* ENET_DMA_CH_TXDESC_ADDRESS */
#define ENET_DMA_CH_TXDESC_ADDRESS_TDESLA                  BITS(3,31)           /*!< start of transmit list */

/* ENET_DMA_CH_RXDESC_ADDRESS */
#define ENET_DMA_CH_RXDESC_ADDRESS_RDESLA                  BITS(3,31)           /*!< start of receive list */

/* ENET_DMA_CH_TXDESC_TAIL_POINTER */
#define ENET_DMA_CH_TXDESC_TAIL_POINTER_TDTP               BITS(3,31)           /*!< transmit descriptor tail pointer */

/* ENET_DMA_CH_RXDESC_TAIL_POINTER */
#define ENET_DMA_CH_RXDESC_TAIL_POINTER_RDTP               BITS(3,31)           /*!< receive descriptor tail pointer */

/* ENET_DMA_CH_TXDESC_RING_LENGTH */
#define ENET_DMA_CH_TXDESC_RING_LENGTH_TDRL                BITS(0,9)           /*!< transmit descriptor ring length */

/* ENET_DMA_CH_RX_CONTROL2 */
#define ENET_DMA_CH_RX_CONTROL2_RDRL                       BITS(0,9)           /*!< receive descriptor ring length */
#define ENET_DMA_CH_RX_CONTROL2_ARBS                       BITS(17,23)         /*!< alternate receive buffer size */

/* ENET_DMA_CH_INTERRUPT_ENABLE */
#define ENET_DMA_CH_INTERRUPT_ENABLE_TIE                   BIT(0)               /*!< transmit interrupt enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_TXSE                  BIT(1)               /*!< transmit stopped enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_TBUE                  BIT(2)               /*!< transmit buffer unavailable enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_RIE                   BIT(6)               /*!< receive interrupt enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_RBUE                  BIT(7)               /*!< receive buffer unavailable enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_RSE                   BIT(8)               /*!< receive stopped enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_RWTE                  BIT(9)               /*!< receive watchdog timeout enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_ETIE                  BIT(10)              /*!< early transmit interrupt enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_ERIE                  BIT(11)              /*!< early receive interrupt enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_FBEE                  BIT(12)              /*!< fatal bus error enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_CDEE                  BIT(13)              /*!< context descriptor error enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_AIE                   BIT(14)              /*!< abnormal interrupt summary enable */
#define ENET_DMA_CH_INTERRUPT_ENABLE_NIE                   BIT(15)              /*!< normal interrupt summary enable */

/* ENET_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER */
#define ENET_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWT        BITS(0,7)            /*!< receive interrupt watchdog timer count */
#define ENET_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWTU     BITS(16,17)          /*!< receive interrupt watchdog timer count units */

/* ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS */
#define ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_ESC       BIT(0)               /*!< enable slot comparison */
#define ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_ASC      BIT(1)               /*!< advance slot check */
#define ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_SIV       BITS(4,15)           /*!< slot interval value */
#define ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_RSN       BITS(16,19)          /*!< reference slot number */

/* ENET_DMA_CH_CURRENT_APP_TXDESC */
#define ENET_DMA_CH_CURRENT_APP_TXDESC_CURTDESAPTR         BITS(0,31)           /*!< application transmit descriptor address pointer */

/* ENET_DMA_CH_CURRENT_APP_RXDESC */
#define ENET_DMA_CH_CURRENT_APP_RXDESC_CURRDESAPTR         BITS(0,31)           /*!< application receive descriptor address pointer */

/* ENET_DMA_CH_CURRENT_APP_TXBUFFER */
#define ENET_DMA_CH_CURRENT_APP_TXBUFFER_CURTBUFAPTR       BITS(0,31)           /*!< application transmit buffer address pointer */

/* ENET_DMA_CH_CURRENT_APP_RXBUFFER */
#define ENET_DMA_CH_CURRENT_APP_RXBUFFER_CURRBUFAPTR       BITS(0,31)           /*!< application receive buffer address pointer */

/* ENET_DMA_CH_STATUS */
#define ENET_DMA_CH_STATUS_TI                              BIT(0)               /*!< transmit interrupt */
#define ENET_DMA_CH_STATUS_TPS                             BIT(1)               /*!< transmit process stopped */
#define ENET_DMA_CH_STATUS_TBU                             BIT(2)               /*!< transmit buffer unavailable status */
#define ENET_DMA_CH_STATUS_RI                              BIT(6)               /*!< receive interrupt */
#define ENET_DMA_CH_STATUS_RBU                             BIT(7)               /*!< receive buffer unavailable status */
#define ENET_DMA_CH_STATUS_RPS                             BIT(8)               /*!< receive process stopped */
#define ENET_DMA_CH_STATUS_RWT                             BIT(9)               /*!< receive watchdog timeout */
#define ENET_DMA_CH_STATUS_ETI                             BIT(10)              /*!< early transmit interrupt */
#define ENET_DMA_CH_STATUS_ERI                             BIT(11)              /*!< early receive interrupt */
#define ENET_DMA_CH_STATUS_FBE                             BIT(12)              /*!< fatal bus error */
#define ENET_DMA_CH_STATUS_CDE                             BIT(13)              /*!< context descriptor error */
#define ENET_DMA_CH_STATUS_AIS                             BIT(14)              /*!< abnormal interrupt summary */
#define ENET_DMA_CH_STATUS_NIS                             BIT(15)              /*!< normal interrupt summary */
#define ENET_DMA_CH_STATUS_TEB                             BITS(16,18)          /*!< Tx DMA error */
#define ENET_DMA_CH_STATUS_REB                             BITS(19,21)          /*!< Rx DMA error */

/* ENET_DMA_CH_MISS_FRAME_CNT */
#define ENET_DMA_CH_MISS_FRAME_CNT_MSFC                    BITS(0,10)           /*!< dropped packet counters */
#define ENET_DMA_CH_MISS_FRAME_CNT_MFCO                    BIT(15)              /*!< overflow status of the MFC counter */

/* ENET_DMA_CH_RXP_ACCEPT_CNT */
#define ENET_DMA_CH_RXP_ACCEPT_CNT_RXPAC                   BITS(0,30)           /*!< Rx parser accept counter */
#define ENET_DMA_CH_RXP_ACCEPT_CNT_RXPACOF                 BIT(31)              /*!< Rx parser accept counter overflow */

#ifdef ENHANCED_NORMAL_DESCRIPTOR
/* ENET DMA Tx enhanced normal descriptor ETDES4 */
#define ENET_NORMAL_ETDES4_LT                              BITS(0,7)           /*!< launch time[24:31] */
#define ENET_NORMAL_ETDES4_GSN                             BITS(8,11)          /*!< GCL slot number */
#define ENET_NORMAL_ETDES4_LTV                             BIT(31)             /*!< launch time valid */

/* ENET DMA Tx enhanced normal descriptor ETDES4 */
#define ENET_NORMAL_ETDES5_LT                              BITS(8,31)           /*!< launch time[0:23] */
#endif /* ENHANCED_NORMAL_DESCRIPTOR */

/* ENET DMA Tx normal descriptor TDES0 (read format) */
#define ENET_NORMAL_TDES0_RF_BUF1AP                        BITS(0,31)           /*!< buffer 1 address pointer */

/* ENET DMA Tx normal descriptor TDES1 (read format) */
#define ENET_NORMAL_TDES1_RF_BUF2AP                        BITS(0,31)           /*!< buffer 2 address pointer */

/* ENET DMA Tx normal descriptor TDES2 (read format) */
#define ENET_NORMAL_TDES2_RF_B1L                           BITS(0,13)           /*!< buffer 1 length */
#define ENET_NORMAL_TDES2_RF_VTIR                          BITS(14,15)          /*!< VLAN tag insertion or replacement */
#define ENET_NORMAL_TDES2_RF_B2L                           BITS(16,29)          /*!< buffer 2 length */
#define ENET_NORMAL_TDES2_RF_TTSE                          BIT(30)              /*!< transmit timestamp enable */
#define ENET_NORMAL_TDES2_RF_IOC                           BIT(31)              /*!< interrupt on completion */

/* ENET DMA Tx normal descriptor TDES3 (read format) */
#define ENET_NORMAL_TDES3_RF_FL                            BITS(0,14)           /*!< frame length */
#define ENET_NORMAL_TDES3_RF_CIC                           BITS(16,17)          /*!< checksum insertion control */
#define ENET_NORMAL_TDES3_RF_SLOTNUM                       BITS(19,22)          /*!< slot number control bits in AV mode */
#define ENET_NORMAL_TDES3_RF_SAIC                          BITS(23,25)          /*!< SA insertion control */
#define ENET_NORMAL_TDES3_RF_CPC                           BITS(26,27)          /*!< CRC pad control */
#define ENET_NORMAL_TDES3_RF_LD                            BIT(28)              /*!< last descriptor */
#define ENET_NORMAL_TDES3_RF_FD                            BIT(29)              /*!< first descriptor */
#define ENET_NORMAL_TDES3_RF_CTXT                          BIT(30)              /*!< context type */
#define ENET_NORMAL_TDES3_RF_OWN                           BIT(31)              /*!< own bit */

/* ENET DMA Tx normal descriptor TDES0 (write-back format) */
#define ENET_NORMAL_TDES0_WF_TTSL                          BITS(0,31)           /*!< transmit packet timestamp low */

/* ENET DMA Tx normal descriptor TDES1 (write-back format) */
#define ENET_NORMAL_TDES1_WF_TTSH                          BITS(0,31)           /*!< transmit packet timestamp high */

/* ENET DMA Tx normal descriptor TDES3 (write-back format) */
#define ENET_NORMAL_TDES3_WF_IHE                           BIT(0)              /*!< IP header error */
#define ENET_NORMAL_TDES3_WF_DB                            BIT(1)              /*!< deferred */
#define ENET_NORMAL_TDES3_WF_UF                            BIT(2)              /*!< underflow error */
#define ENET_NORMAL_TDES3_WF_ED                            BIT(3)              /*!< excessive deferral */
#define ENET_NORMAL_TDES3_WF_CC                            BITS(4,7)           /*!< collision countr */
#define ENET_NORMAL_TDES3_WF_EC                            BIT(8)              /*!< excessive collision */
#define ENET_NORMAL_TDES3_WF_LC                            BIT(9)              /*!< late collision */
#define ENET_NORMAL_TDES3_WF_NC                            BIT(10)             /*!< no carrier */
#define ENET_NORMAL_TDES3_WF_LOC                           BIT(11)             /*!< loss of carrier */
#define ENET_NORMAL_TDES3_WF_PCE                           BIT(12)             /*!< payload checksum error */
#define ENET_NORMAL_TDES3_WF_FF                            BIT(13)             /*!< packet flushed */
#define ENET_NORMAL_TDES3_WF_JT                            BIT(14)             /*!< jabber timeout */
#define ENET_NORMAL_TDES3_WF_ES                            BIT(15)             /*!< error summary */
#define ENET_NORMAL_TDES3_WF_TTSS                          BIT(17)             /*!< Tx timestamp status */
#define ENET_NORMAL_TDES3_WF_DE                            BIT(23)             /*!< descriptor error */
#define ENET_NORMAL_TDES3_WF_LD                            BIT(28)              /*!< last descriptor */
#define ENET_NORMAL_TDES3_WF_FD                            BIT(29)              /*!< first descriptor */
#define ENET_NORMAL_TDES3_WF_CTXT                          BIT(30)              /*!< context type */
#define ENET_NORMAL_TDES3_WF_OWN                           BIT(31)              /*!< own bit */

/* ENET DMA Tx context descriptor TDES0 */
#define ENET_CONTEXT_TDES0_TTSL                            BITS(0,31)           /*!< transmit packet timestamp low */

/* ENET DMA Tx context descriptor TDES1 */
#define ENET_CONTEXT_TDES1_TTSH                            BITS(0,31)           /*!< transmit packet timestamp high */

/* ENET DMA Tx context descriptor TDES2 */
#define ENET_CONTEXT_TDES2_IVT                             BITS(16,31)          /*!< inner VLAN tag */

/* ENET DMA Tx enhanced descriptor ETDES0 */
#define ENET_ENHANCED_ETDES0_LTV                           BIT(31)              /*!< launch time valid */
#define ENET_ENHANCED_ETDES0_GSN                           BITS(8,11)           /*!< GCL slot number */
#define ENET_ENHANCED_ETDES0_LT_HIGH                       BITS(0,7)            /*!< launch time[24:31] */

/* ENET DMA Tx enhanced descriptor ETDES1 */
#define ENET_ENHANCED_ETDES1_LT_LOW                        BITS(8,31)            /*!< launch time[24:31] */

/* ENET DMA Tx context descriptor TDES3 */
#define ENET_CONTEXT_TDES3_VT                              BITS(0,15)           /*!< VLAN tag */
#define ENET_CONTEXT_TDES3_VLTV                            BIT(16)              /*!< VLAN tag */
#define ENET_CONTEXT_TDES3_IVLTV                           BIT(17)              /*!< inner VLAN tag valid */
#define ENET_CONTEXT_TDES3_IVTIR                           BITS(18,19)          /*!< inner VLAN tag insert or replace */
#define ENET_CONTEXT_TDES3_CDE                             BIT(23)              /*!< context descriptor error */
#define ENET_CONTEXT_TDES3_TC                              BIT(26)              /*!< one-step timestamp correction input */
#define ENET_CONTEXT_TDES3_OSTC                            BIT(27)              /*!< one-step timestamp correction enable */
#define ENET_CONTEXT_TDES3_CTXT                            BIT(30)              /*!< context type */
#define ENET_CONTEXT_TDES3_OWN                             BIT(31)              /*!< own bit */

/* ENET DMA Rx normal descriptor RDES0 (read format) */
#define ENET_NORMAL_RDES0_RF_BUF1AP                        BITS(0,31)           /*!< buffer 1 address pointer */

/* ENET DMA Rx normal descriptor RDES2 (read format) */
#define ENET_NORMAL_RDES2_RF_BUF2AP                        BITS(0,31)           /*!< buffer 2 address pointer */

/* ENET DMA Rx normal descriptor RDES3 (read format) */
#define ENET_NORMAL_RDES3_RF_BUF1V                         BIT(24)              /*!< buffer 1 address valid */
#define ENET_NORMAL_RDES3_RF_BUF2V                         BIT(25)              /*!< buffer 2 address valid */
#define ENET_NORMAL_RDES3_RF_IOC                           BIT(30)              /*!< interrupt enabled on completion */
#define ENET_NORMAL_RDES3_RF_OWN                           BIT(31)              /*!< own bit */

/* ENET DMA Rx normal descriptor RDES0 (write-back format) */
#define ENET_NORMAL_RDES0_WF_OVT                           BITS(0,15)           /*!< outer VLAN tag */
#define ENET_NORMAL_RDES0_WF_IVT                           BITS(16,31)          /*!< inner VLAN tag */

/* ENET DMA Rx normal descriptor RDES1 (write-back format) */
#define ENET_NORMAL_RDES1_WF_PT                            BITS(0,2)            /*!< payload type */
#define ENET_NORMAL_RDES1_WF_IPHE                          BIT(3)               /*!< IP header error */
#define ENET_NORMAL_RDES1_WF_IPV4                          BIT(4)               /*!< IPV4 header present */
#define ENET_NORMAL_RDES1_WF_IPV6                          BIT(5)               /*!< IPv6 header present */
#define ENET_NORMAL_RDES1_WF_IPCB                          BIT(6)               /*!< IP checksum bypassed */
#define ENET_NORMAL_RDES1_WF_IPCE                          BIT(7)               /*!< IP payload error */
#define ENET_NORMAL_RDES1_WF_PMT                           BITS(8,11)           /*!< PTP message type */
#define ENET_NORMAL_RDES1_WF_PFT                           BIT(12)              /*!< PTP packet type */
#define ENET_NORMAL_RDES1_WF_PV                            BIT(13)              /*!< PTP version */
#define ENET_NORMAL_RDES1_WF_TSA                           BIT(14)              /*!< timestamp available */
#define ENET_NORMAL_RDES1_WF_TD                            BIT(15)              /*!< timestamp dropped */
#define ENET_NORMAL_RDES1_WF_OPC                           BITS(16,31)          /*!< OAM sub-type code, or MAC control packet opcode */

/* ENET DMA Rx normal descriptor RDES2 (write-back format) */
#define ENET_NORMAL_RDES2_WF_ARPNR                         BIT(10)              /*!< ARP reply not generated */
#define ENET_NORMAL_RDES2_WF_RXPS                          BITS(11,13)          /*!< Rx Parser Status */
#define ENET_NORMAL_RDES2_WF_ITS                           BIT(14)              /*!< inner VLAN tag filter status */
#define ENET_NORMAL_RDES2_WF_OTS                           BIT(15)              /*!< outer VLAN tag filter status */
#define ENET_NORMAL_RDES2_WF_SAF                           BIT(16)              /*!< SA address filter fail */
#define ENET_NORMAL_RDES2_WF_DAF                           BIT(17)              /*!< destination address filter fail */
#define ENET_NORMAL_RDES2_WF_HF                            BIT(18)              /*!< hash filter status */
#define ENET_NORMAL_RDES2_WF_MADRM                         BITS(19,26)          /*!< MAC address match or hash value */
#define ENET_NORMAL_RDES2_WF_L3FM                          BIT(27)              /*!< layer 3 filter match */
#define ENET_NORMAL_RDES2_WF_L4FM                          BIT(28)              /*!< layer 4 filter match */
#define ENET_NORMAL_RDES2_WF_L3L4FM                        BITS(29,31)          /*!< layer 3 and layer 4 filter number matched */

/* ENET DMA Rx normal descriptor RDES3 (write-back format) */
#define ENET_NORMAL_RDES3_WF_PL                            BITS(0,14)           /*!< packet length */
#define ENET_NORMAL_RDES3_WF_ES                            BIT(15)              /*!< error summary */
#define ENET_NORMAL_RDES3_WF_LT                            BITS(16,18)          /*!< length/type field */
#define ENET_NORMAL_RDES3_WF_DE                            BIT(19)              /*!< dribble bit error */
#define ENET_NORMAL_RDES3_WF_RE                            BIT(20)              /*!< receive error */
#define ENET_NORMAL_RDES3_WF_OE                            BIT(21)              /*!< overflow error */
#define ENET_NORMAL_RDES3_WF_RWT                           BIT(22)              /*!< receive watchdog timeout */
#define ENET_NORMAL_RDES3_WF_GP                            BIT(23)              /*!< giant packet */
#define ENET_NORMAL_RDES3_WF_CE                            BIT(24)              /*!< CRC error */
#define ENET_NORMAL_RDES3_WF_RS0V                          BIT(25)              /*!< receive status RDES0 valid */
#define ENET_NORMAL_RDES3_WF_RS1V                          BIT(26)              /*!< receive status RDES1 valid */
#define ENET_NORMAL_RDES3_WF_RS2V                          BIT(27)              /*!< receive status RDES2 valid */
#define ENET_NORMAL_RDES3_WF_LD                            BIT(28)              /*!< last descriptor */
#define ENET_NORMAL_RDES3_WF_FD                            BIT(29)              /*!< first descriptor */
#define ENET_NORMAL_RDES3_WF_CTXT                          BIT(30)              /*!< context type */
#define ENET_NORMAL_RDES3_WF_OWN                           BIT(31)              /*!< own bit */

/* ENET DMA Rx context descriptor RDES0 */
#define ENET_CONTEXT_RDES0_RTSL                            BITS(0,31)           /*!< receive packet timestamp low */

/* ENET DMA Rx context descriptor RDES1 */
#define ENET_CONTEXT_RDES1_RTSH                            BITS(0,31)           /*!< receive packet timestamp high */

/* ENET DMA Rx context descriptor RDES3 */
#define ENET_CONTEXT_RDES3_DE                              BIT(29)              /*!< descriptor error */
#define ENET_CONTEXT_RDES3_CTXT                            BIT(30)              /*!< context type */
#define ENET_CONTEXT_RDES3_OWN                             BIT(31)              /*!< own bit */

/* ENET clock range judgement */
#define ENET_RANGE(apb1, n, m)           (((apb1) >= (n))&&((apb1) < (m)))

/* MAC_MDIO_ADDRESS register value */
#define MAC_MDIO_ADDRESS_CR(regval)                   (BITS(8,11) & ((uint32_t)(regval) << 8))       /*!< write value to MAC_MDIO_ADDRESS_CR bit field */
#define ENET_MDC_APB1_DIV42                            MAC_MDIO_ADDRESS_CR(0)                            /*!< HCLK:60-100 MHz; MDC clock= HCLK/42 */
#define ENET_MDC_APB1_DIV62                            MAC_MDIO_ADDRESS_CR(1)                            /*!< HCLK:100-150 MHz; MDC clock= HCLK/62 */
#define ENET_MDC_APB1_DIV16                            MAC_MDIO_ADDRESS_CR(2)                            /*!< HCLK:20-35 MHz; MDC clock= HCLK/16 */
#define ENET_MDC_APB1_DIV26                            MAC_MDIO_ADDRESS_CR(3)                            /*!< HCLK:35-60 MHz; MDC clock= HCLK/26 */
#define ENET_MDC_APB1_DIV102                           MAC_MDIO_ADDRESS_CR(4)                            /*!< HCLK:150-240 MHz; MDC clock= HCLK/102 */


/* MAC configuration register value */
#define MAC_CONFIGURATION_SARC(regval)            (BITS(28,29) & ((uint32_t)(regval) << 28))       /*!< write value to ENET_MAC_CONFIGURATION_SARC bit field */
#define ENET_SARC_INTERNAL_SIGNAL                  MAC_CONFIGURATION_SARC(0)                       /*!< internal input signals control the SA field generation */
#define ENET_SARC_ADDR0_INSERT                     MAC_CONFIGURATION_SARC(2)                       /*!< contents of MAC addr-0 inserted in SA field */
#define ENET_SARC_ADDR0_REPLACE                    MAC_CONFIGURATION_SARC(3)                       /*!< contents of MAC addr-0 replaces in SA field */
#define ENET_SARC_ADDR1_INSERT                     MAC_CONFIGURATION_SARC(6)                       /*!< contents of MAC addr-1 inserted in SA field */
#define ENET_SARC_ADDR1_REPLACE                    MAC_CONFIGURATION_SARC(7)                       /*!< contents of MAC addr-1 replaces in SA field */

#define MAC_CONFIGURATION_IPG(regval)             (BITS(24,26) & ((uint32_t)(regval) << 24))       /*!< write value to ENET_MAC_CONFIGURATION_IPG bit field */
#define ENET_INTERPACKETGAP_96BIT                  MAC_CONFIGURATION_IPG(0)                        /*!< 96 bit times inter-packet gap */
#define ENET_INTERPACKETGAP_88BIT                  MAC_CONFIGURATION_IPG(1)                        /*!< 88 bit times inter-packet gap */
#define ENET_INTERPACKETGAP_80BIT                  MAC_CONFIGURATION_IPG(2)                        /*!< 80 bit times inter-packet gap */
#define ENET_INTERPACKETGAP_72BIT                  MAC_CONFIGURATION_IPG(3)                        /*!< 72 bit times inter-packet gap */
#define ENET_INTERPACKETGAP_64BIT                  MAC_CONFIGURATION_IPG(4)                        /*!< 64 bit times inter-packet gap */
#define ENET_INTERPACKETGAP_56BIT                  MAC_CONFIGURATION_IPG(5)                        /*!< 56 bit times inter-packet gap */
#define ENET_INTERPACKETGAP_48BIT                  MAC_CONFIGURATION_IPG(6)                        /*!< 48 bit times inter-packet gap */
#define ENET_INTERPACKETGAP_40BIT                  MAC_CONFIGURATION_IPG(7)                        /*!< 40 bit times inter-packet gap */

#define MAC_CONFIGURATION_BL(regval)              (BITS(5,6) & ((uint32_t)(regval) << 5))          /*!< write value to ENET_MAC_CONFIGURATION_BL bit field */
#define ENET_BACKOFFLIMIT_10                       MAC_CONFIGURATION_BL(0)                         /*!< min (n, 10) */
#define ENET_BACKOFFLIMIT_8                        MAC_CONFIGURATION_BL(1)                         /*!< min (n, 8) */
#define ENET_BACKOFFLIMIT_4                        MAC_CONFIGURATION_BL(2)                         /*!< min (n, 4) */
#define ENET_BACKOFFLIMIT_1                        MAC_CONFIGURATION_BL(3)                         /*!< min (n, 1) */

#define MAC_CONFIGURATION_PRELEN(regval)           (BITS(2,3) & ((uint32_t)(regval) << 2))          /*!< write value to ENET_MAC_CONFIGURATION_PRELEN bit field */
#define ENET_PREAMBLE_LENGTH_7BYTE                 MAC_CONFIGURATION_PRELEN(0)                     /*!< 7 bytes of preamble */
#define ENET_PREAMBLE_LENGTH_5BYTE                 MAC_CONFIGURATION_PRELEN(1)                     /*!< 5 bytes of preamble */
#define ENET_PREAMBLE_LENGTH_3BYTE                 MAC_CONFIGURATION_PRELEN(2)                     /*!< 3 bytes of preamble */

#define ENET_ARP_OFFLOAD_ENABLE                    ENET_MAC_CONFIGURATION_ARPEN                    /*!< the MAC can recognize an incoming ARP request packet and schedules the ARP packet for transmission */
#define ENET_ARP_OFFLOAD_DISABLE                   ((uint32_t)0x00000000U)                         /*!< the MAC receiver does not recognize any ARP packet */

#define ENET_CHECKSUMOFFLOAD_ENABLE                ENET_MAC_CONFIGURATION_IPC                      /*!< IP header/payload checksum checking is enabled */
#define ENET_CHECKSUMOFFLOAD_DISABLE               ((uint32_t)0x00000000U)                         /*!< IP header/payload checksum checking is disabled */

#define ENET_GIANT_PACKET_LIMIT_ENABLE        ENET_MAC_CONFIGURATION_GPSLCE                   /*!< giant packet size limit control is enabled */
#define ENET_GIANT_PACKET_LIMIT_DISABLE       ((uint32_t)0x00000000U)                         /*!< giant packet size limit control is disabled */

#define ENET_2KMAX_PACKET_ENABLE             ENET_MAC_CONFIGURATION_S2KP                     /*!< Support up to 2K packet is enabled */
#define ENET_2KMAX_PACKET_DISABLE            ((uint32_t)0x00000000U)                         /*!< Support up to 2K packet is disabled */

#define ENET_TYPEPACKET_CRC_STRIP_ENABLE           ENET_MAC_CONFIGURATION_CST                      /*!< FCS field(last 4 bytes) of frame will be dropped before forwarding */
#define ENET_TYPEPACKET_CRC_STRIP_DISABLE          ((uint32_t)0x00000000U)                         /*!< FCS field(last 4 bytes) of frame will not be dropped before forwarding */
#define ENET_TYPEFRAME_CRC_DROP                     ENET_MAC_CONFIGURATION_CST                             /*!< the function of the MAC strips the Pad/FCS field on received frames */

#define ENET_AUTO_PADCRC_STRIP_ENABLE              ENET_MAC_CONFIGURATION_ACS                       /*!< the MAC strips the Pad/FCS field on received packets */
#define ENET_AUTO_PADCRC_STRIP_DISABLE             ((uint32_t)0x00000000U)                          /*!< the MAC forwards all received frames without modify it */
#define ENET_AUTO_PADCRC_DROP                     ENET_MAC_CONFIGURATION_ACS                             /*!< the function of the MAC strips the Pad/FCS field on received frames */

#define ENET_WATCHDOG_ENABLE                      ((uint32_t)0x00000000U)                           /*!< the MAC allows no more than 2048 bytes of the packet being received */
#define ENET_WATCHDOG_DISABLE                      ENET_MAC_CONFIGURATION_WD                        /*!< the MAC disables the watchdog timer on the receiver, and can receive packets of up to 16383 bytes */

#define ENET_JABBER_ENABLE                        ((uint32_t)0x00000000U)                           /*!< the maximum transmission byte is 2048 */
#define ENET_JABBER_DISABLE                        ENET_MAC_CONFIGURATION_JD                        /*!< the maximum transmission byte can be 16383 */

#define ENET_JUMBO_PACKET_ENABLE                         ((uint32_t)0x00000000U)                           /*!< the MAC allows jumbo packets of 9018 bytes (9022 bytes for VLAN tagged packets) */
#define ENET_JUMBO_PACKET_DISABLE                         ENET_MAC_CONFIGURATION_JE                        /*!< the MAC does not allows jumbo packets */

#define ENET_SPEEDMODE_10M                        ((uint32_t)0x00000000U)                           /*!< 10 Mbit/s */
#define ENET_SPEEDMODE_100M                        ENET_MAC_CONFIGURATION_FES                       /*!< 100 Mbit/s  */

#define ENET_MODE_FULLDUPLEX                       ENET_MAC_CONFIGURATION_DM                        /*!< full-duplex mode enable */
#define ENET_MODE_HALFDUPLEX                      ((uint32_t)0x00000000U)                           /*!< half-duplex mode enable */

#define ENET_LOOPBACKMODE_ENABLE                   ENET_MAC_CONFIGURATION_LM                        /*!< the MAC operates in loopback mode at the MII */
#define ENET_LOOPBACKMODE_DISABLE                 ((uint32_t)0x00000000U)                           /*!< the MAC operates in normal mode */

#define ENET_FULLDUPLEX_CARRIERSENSE_ENABLE        ENET_MAC_CONFIGURATION_ECRSFD                    /*!< the MAC transmitter checks the CRS signal before packet transmission in the full-duplex mode */
#define ENET_FULLDUPLEX_CARRIERSENSE_DISABLE      ((uint32_t)0x00000000U)                           /*!< the MAC transmitter ignores the status of the CRS signal */

#define ENET_RECEIVEOWN_ENABLE                    ((uint32_t)0x00000000U)                           /*!< the packets that transmitting from PHY are all received by MAC */
#define ENET_RECEIVEOWN_DISABLE                    ENET_MAC_CONFIGURATION_DO                        /*!< receiving frames from PHY is disabled by MAC */

#define ENET_CARRIERSENSE_ENABLE                  ((uint32_t)0x00000000U)                           /*!< the MAC transmitter generates errors because of carrier sense and aborts the transmission */
#define ENET_CARRIERSENSE_DISABLE                  ENET_MAC_CONFIGURATION_DCRS                      /*!< the MAC transmitter ignores the MII CRS signal during frame transmission in half-duplex mode */

#define ENET_RETRYTRANSMISSION_ENABLE              ((uint32_t)0x00000000U)                           /*!< the MAC retries based on the settings of the BL field*/
#define ENET_RETRYTRANSMISSION_DISABLE              ENET_MAC_CONFIGURATION_DR                        /*!< the MAC attempts only 1 transmission */

#define ENET_DEFERRALCHECK_ENABLE                  ENET_MAC_CONFIGURATION_DC                        /*!< the deferral check function is enabled in the MAC */
#define ENET_DEFERRALCHECK_DISABLE                 ((uint32_t)0x00000000U)                          /*!< the deferral check function is disabled */

/* ENET_MTL_RXQ0_OPERATION_MODE register value */
#define ENET_RXQ0_FORWARD_ERRFRAMES_ENABLE               (ENET_MTL_RXQ0_OPERATION_MODE_FEP << 2)    /*!< the forward error packets function is enabled in queue0 */
#define ENET_RXQ0_FORWARD_ERRFRAMES_DISABLE              ((uint32_t)0x00000000U)                    /*!< the forward error packets function is disabled in queue0 */
#define ENET_RXQ0_FORWARD_ERRFRAMES                      (ENET_MTL_RXQ0_OPERATION_MODE_FEP << 2)    /*!< the function that all frame received with error except runt error are forwarded to memory */

#define ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES_ENABLE      (ENET_MTL_RXQ0_OPERATION_MODE_FUP << 2)    /*!< the forward undersized good packets function is enabled in queue0 */
#define ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES_DISABLE     ((uint32_t)0x00000000U)                    /*!< the forward undersized good packets function is disabled in queue0 */
#define ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES             (ENET_MTL_RXQ0_OPERATION_MODE_FUP << 2)    /*!< the function that forwarding undersized good frames */

#define ENET_RXQ1_FORWARD_ERRFRAMES_ENABLE                ENET_MTL_RXQ1_OPERATION_MODE_FEP          /*!< the forward error packets function is enabled in queue1 */
#define ENET_RXQ1_FORWARD_ERRFRAMES_DISABLE               ((uint32_t)0x00000000U)                   /*!< the forward error packets function is disabled in queue1 */
#define ENET_RXQ1_FORWARD_ERRFRAMES                       ENET_MTL_RXQ1_OPERATION_MODE_FEP          /*!< the function that all frame received with error except runt error are forwarded to memory */

#define ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES_ENABLE       ENET_MTL_RXQ1_OPERATION_MODE_FUP          /*!< the forward undersized good packets function is enabled in queue1 */
#define ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES_DISABLE      ((uint32_t)0x00000000U)                   /*!< the forward undersized good packets function is disabled in queue1 */
#define ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES              ENET_MTL_RXQ1_OPERATION_MODE_FUP          /*!< the function that forwarding undersized good frames */

/* MAC extended configuration register value */
#define MAC_EXT_CONFIGURATION_EIPG(regval)        (BITS(25,29) & ((uint32_t)(regval) << 25))        /*!< write value to ENET_MAC_EXT_CONFIGURATION_EIPG bit field */

#define MAC_EXT_CONFIGURATION_GPSL(regval)        (BITS(0,13) & ((uint32_t)(regval) << 0))          /*!< write value to ENET_MAC_EXT_CONFIGURATION_GPSL bit field */

/* MAC packet filter register value */
#define MAC_PACKET_FILTER_PCF(regval)              (BITS(6,7) & ((uint32_t)(regval) << 6))          /*!< write value to ENET_MAC_EXT_CONFIGURATION_EIPG bit field */
#define ENET_CONTROL_PACKET_PREVENT_ALL            MAC_PACKET_FILTER_PCF(0)                         /*!< MAC filters all control packets from reaching the application */
#define ENET_CONTROL_PACKET_PREVENT_PAUSEFRAME     MAC_PACKET_FILTER_PCF(1)                         /*!< MAC forwards all control packets except pause packets to the application even if they fail the address filter */
#define ENET_CONTROL_PACKET_FORWARD_ALL            MAC_PACKET_FILTER_PCF(2)                         /*!< MAC forwards all control packets to the application even if they fail the address filter */
#define ENET_CONTROL_PACKET_FORWARD_PASS_FILTER    MAC_PACKET_FILTER_PCF(3)                         /*!< MAC forwards the control packets that pass the address filter */

#define ENET_RECEIVE_ALL_ENABLE                    ENET_MAC_PACKET_FILTER_RA                        /*!< the MAC receiver always checks the CRC field in the received packets */
#define ENET_RECEIVE_ALL_DISABLE                   ((uint32_t)0x00000000U)                          /*!< the MAC receiver does not check the CRC field in the received packets */

#define ENET_DROP_NONTCPUDP_ENABLE                 ENET_MAC_PACKET_FILTER_DNTU                      /*!< the MAC drops the non-TCP or UDP over IP packets */
#define ENET_DROP_NONTCPUDP_DISABLE                ((uint32_t)0x00000000U)                          /*!< the MAC forwards all non-TCP or UDP over IP packets */

#define ENET_L3L4_FILTER_ENABLE                    ENET_MAC_PACKET_FILTER_IPFE                      /*!< the MAC drops packets that do not match the enabled Layer 3 and Layer 4 filters */
#define ENET_L3L4_FILTER_DISABLE                   ((uint32_t)0x00000000U)                          /*!< the MAC forwards all packets irrespective of the match status of the Layer 3 and Layer 4 fields */
#define ENET_L3L4_FILTER                           ENET_MAC_PACKET_FILTER_IPFE                      /*!< filter Layer 3 and Layer 4 filters function */

#define ENET_VLAN_FILTER_ENABLE                    ENET_MAC_PACKET_FILTER_VTFE                      /*!< VLAN tag filter is enabled */
#define ENET_VLAN_FILTER_DISABLE                   ((uint32_t)0x00000000U)                          /*!< VLAN tag filter is disabled */
#define ENET_VLAN_FILTER                           ENET_MAC_PACKET_FILTER_VTFE                      /*!< filter VLAN tag function */

#define ENET_SRC_FILTER_NORMAL_ENABLE              ENET_MAC_PACKET_FILTER_SAF                                  /*!< filter source address */
#define ENET_SRC_FILTER_INVERSE_ENABLE             (ENET_MAC_PACKET_FILTER_SAF | ENET_MAC_PACKET_FILTER_SAIF)  /*!< inverse source address filtering result */
#define ENET_SRC_FILTER_DISABLE                    ((uint32_t)0x00000000U)                                     /*!< source address function in filter disable */
#define ENET_SRC_FILTER                            ENET_MAC_PACKET_FILTER_SAF                                  /*!< filter source address function */
#define ENET_SRC_FILTER_INVERSE                    ENET_MAC_PACKET_FILTER_SAIF                                 /*!< inverse source address filtering result function */

#define ENET_BROADCASTFRAMES_ENABLE                ((uint32_t)0x00000000U)                          /*!< the address filters pass all received broadcast frames */
#define ENET_BROADCASTFRAMES_DISABLE               ENET_MAC_PACKET_FILTER_DBF                       /*!< the address filters filter all incoming broadcast frames */
#define ENET_BROADCASTFRAMES_FILTER                ENET_MAC_PACKET_FILTER_DBF                       /*!< filter all incoming broadcast frames function */

#define ENET_DEST_FILTER_INVERSE_ENABLE            ENET_MAC_PACKET_FILTER_DAIF                      /*!< inverse DA filtering result */
#define ENET_DEST_FILTER_INVERSE_DISABLE           ((uint32_t)0x00000000U)                          /*!< not inverse DA filtering result */
#define ENET_DEST_FILTER_INVERSE                   ENET_MAC_PACKET_FILTER_DAIF                      /*!< inverse DA filtering result function */

#define ENET_PROMISCUOUS_ENABLE                    ENET_MAC_PACKET_FILTER_PR                        /*!< promiscuous mode enabled */
#define ENET_PROMISCUOUS_DISABLE                   ((uint32_t)0x00000000U)                          /*!< promiscuous mode disabled */

#define ENET_MULTICAST_FILTER_HASH_OR_PERFECT     (ENET_MAC_PACKET_FILTER_HMC | ENET_MAC_PACKET_FILTER_HPF)     /*!< pass multicast frames that match either the perfect or the hash filtering */
#define ENET_MULTICAST_FILTER_HASH                ENET_MAC_PACKET_FILTER_HMC                                    /*!< pass multicast frames that match the hash filtering */
#define ENET_MULTICAST_FILTER_PERFECT             ((uint32_t)0x00000000U)                                       /*!< pass multicast frames that match the perfect filtering */
#define ENET_MULTICAST_FILTER_NONE                ENET_MAC_PACKET_FILTER_PM                                     /*!< all multicast frames are passed */
#define ENET_MULTICAST_FILTER_PASS                ENET_MAC_PACKET_FILTER_PM                                     /*!< pass all multicast frames function */
#define ENET_MULTICAST_FILTER_HASH_MODE           ENET_MAC_PACKET_FILTER_HMC                                    /*!< HASH multicast filter function */
#define ENET_FILTER_MODE_EITHER                   ENET_MAC_PACKET_FILTER_HPF                                    /*!< HASH or perfect filter function */

#define ENET_UNICAST_FILTER_EITHER                (ENET_MAC_PACKET_FILTER_HUC | ENET_MAC_PACKET_FILTER_HPF)     /*!< pass unicast frames that match either the perfect or the hash filtering */
#define ENET_UNICAST_FILTER_HASH                  ENET_MAC_PACKET_FILTER_HUC                                    /*!< pass unicast frames that match the hash filtering */
#define ENET_UNICAST_FILTER_PERFECT               ((uint32_t)0x00000000U)                                       /*!< pass unicast frames that match the perfect filtering */
#define ENET_UNICAST_FILTER_HASH_MODE             ENET_MAC_PACKET_FILTER_HUC                                    /*!< HASH unicast filter function */

/* MAC watchdog timeout register value */
#define MAC_WATCHDOG_TIMEOUT_JTO(regval)          (BITS(16,19) & ((uint32_t)(regval) << 16))                    /*!< write value to ENET_MAC_WATCHDOG_TIMEOUT_JTO bit field */
#define ENET_JABBER_TIMEOUT_2KB                   MAC_WATCHDOG_TIMEOUT_JTO(0)                                   /*!< 2KB */
#define ENET_JABBER_TIMEOUT_3KB                   MAC_WATCHDOG_TIMEOUT_JTO(1)                                   /*!< 3KB */
#define ENET_JABBER_TIMEOUT_4KB                   MAC_WATCHDOG_TIMEOUT_JTO(2)                                   /*!< 4KB */
#define ENET_JABBER_TIMEOUT_5KB                   MAC_WATCHDOG_TIMEOUT_JTO(3)                                   /*!< 5KB */
#define ENET_JABBER_TIMEOUT_6KB                   MAC_WATCHDOG_TIMEOUT_JTO(4)                                   /*!< 6KB */
#define ENET_JABBER_TIMEOUT_7KB                   MAC_WATCHDOG_TIMEOUT_JTO(5)                                   /*!< 7KB */
#define ENET_JABBER_TIMEOUT_8KB                   MAC_WATCHDOG_TIMEOUT_JTO(6)                                   /*!< 8KB */
#define ENET_JABBER_TIMEOUT_9KB                   MAC_WATCHDOG_TIMEOUT_JTO(7)                                   /*!< 9KB */
#define ENET_JABBER_TIMEOUT_10KB                  MAC_WATCHDOG_TIMEOUT_JTO(8)                                   /*!< 10KB */
#define ENET_JABBER_TIMEOUT_11KB                  MAC_WATCHDOG_TIMEOUT_JTO(9)                                   /*!< 11KB */
#define ENET_JABBER_TIMEOUT_12KB                  MAC_WATCHDOG_TIMEOUT_JTO(10)                                  /*!< 12KB */
#define ENET_JABBER_TIMEOUT_13KB                  MAC_WATCHDOG_TIMEOUT_JTO(11)                                  /*!< 13KB */
#define ENET_JABBER_TIMEOUT_14KB                  MAC_WATCHDOG_TIMEOUT_JTO(12)                                  /*!< 14KB */
#define ENET_JABBER_TIMEOUT_15KB                  MAC_WATCHDOG_TIMEOUT_JTO(13)                                  /*!< 15KB */
#define ENET_JABBER_TIMEOUT_16KB                  MAC_WATCHDOG_TIMEOUT_JTO(14)                                  /*!< 16KB */

#define MAC_WATCHDOG_TIMEOUT_WTO(regval)          (BITS(0,3) & ((uint32_t)(regval) << 0))                       /*!< write value to ENET_MAC_WATCHDOG_TIMEOUT_WTO bit field */
#define ENET_WATCHDOG_TIMEOUT_2KB                 MAC_WATCHDOG_TIMEOUT_WTO(0)                                   /*!< 2KB */
#define ENET_WATCHDOG_TIMEOUT_3KB                 MAC_WATCHDOG_TIMEOUT_WTO(1)                                   /*!< 3KB */
#define ENET_WATCHDOG_TIMEOUT_4KB                 MAC_WATCHDOG_TIMEOUT_WTO(2)                                   /*!< 4KB */
#define ENET_WATCHDOG_TIMEOUT_5KB                 MAC_WATCHDOG_TIMEOUT_WTO(3)                                   /*!< 5KB */
#define ENET_WATCHDOG_TIMEOUT_6KB                 MAC_WATCHDOG_TIMEOUT_WTO(4)                                   /*!< 6KB */
#define ENET_WATCHDOG_TIMEOUT_7KB                 MAC_WATCHDOG_TIMEOUT_WTO(5)                                   /*!< 7KB */
#define ENET_WATCHDOG_TIMEOUT_8KB                 MAC_WATCHDOG_TIMEOUT_WTO(6)                                   /*!< 8KB */
#define ENET_WATCHDOG_TIMEOUT_9KB                 MAC_WATCHDOG_TIMEOUT_WTO(7)                                   /*!< 9KB */
#define ENET_WATCHDOG_TIMEOUT_10KB                MAC_WATCHDOG_TIMEOUT_WTO(8)                                   /*!< 10KB */
#define ENET_WATCHDOG_TIMEOUT_11KB                MAC_WATCHDOG_TIMEOUT_WTO(9)                                   /*!< 11KB */
#define ENET_WATCHDOG_TIMEOUT_12KB                MAC_WATCHDOG_TIMEOUT_WTO(10)                                  /*!< 12KB */
#define ENET_WATCHDOG_TIMEOUT_13KB                MAC_WATCHDOG_TIMEOUT_WTO(11)                                  /*!< 13KB */
#define ENET_WATCHDOG_TIMEOUT_14KB                MAC_WATCHDOG_TIMEOUT_WTO(12)                                  /*!< 14KB */
#define ENET_WATCHDOG_TIMEOUT_15KB                MAC_WATCHDOG_TIMEOUT_WTO(13)                                  /*!< 15KB */
#define ENET_WATCHDOG_TIMEOUT_16KB                MAC_WATCHDOG_TIMEOUT_WTO(14)                                  /*!< 16KB */

#define ENET_PROGRAMMABLE_JABBER_ENABLE           ENET_MAC_WATCHDOG_TIMEOUT_PJE                                 /*!< programmable jabber is enabled */
#define ENET_PROGRAMMABLE_JABBER_DISABLE          ((uint32_t)0x00000000U)                                       /*!< programmable jabber is disabled */

#define ENET_PROGRAMMABLE_WATCHDOG_ENABLE         ENET_MAC_WATCHDOG_TIMEOUT_PWE                                 /*!< programmable watchdog is enabled */
#define ENET_PROGRAMMABLE_WATCHDOG_DISABLE        ((uint32_t)0x00000000U)                                       /*!< programmable watchdog is disabled */

/* MAC vlan tag control register value */
#define MAC_VLAN_TAG_CTRL_EIVLS(regval)           (BITS(28,29) & ((uint32_t)(regval) << 28))                   /*!< write value to ENET_MAC_VLAN_TAG_CTRL_EIVLS bit field */
#define ENET_INVLANSTRIP_DISABLE                  MAC_VLAN_TAG_CTRL_EIVLS(0)                                   /*!< do not strip */
#define ENET_INVLANSTRIP_PASS                     MAC_VLAN_TAG_CTRL_EIVLS(1)                                   /*!< strip if VLAN filter passes */
#define ENET_INVLANSTRIP_NOPASS                   MAC_VLAN_TAG_CTRL_EIVLS(2)                                   /*!< strip if VLAN filter fails */
#define ENET_INVLANSTRIP_ENABLE                   MAC_VLAN_TAG_CTRL_EIVLS(3)                                   /*!< always strip */

#define MAC_VLAN_TAG_CTRL_EVLS(regval)            (BITS(21,22) & ((uint32_t)(regval) << 21))                    /*!< write value to ENET_MAC_VLAN_TAG_CTRL_EVLS bit field */
#define ENET_OUTVLANSTRIP_DISABLE                 MAC_VLAN_TAG_CTRL_EVLS(0)                                     /*!< do not strip */
#define ENET_OUTVLANSTRIP_PASS                    MAC_VLAN_TAG_CTRL_EVLS(1)                                     /*!< strip if VLAN filter passes */
#define ENET_OUTVLANSTRIP_NOPASS                  MAC_VLAN_TAG_CTRL_EVLS(2)                                     /*!< strip if VLAN filter fails */
#define ENET_OUTVLANSTRIP_ENABLE                  MAC_VLAN_TAG_CTRL_EVLS(3)                                     /*!< always strip */

#define MAC_VLAN_TAG_CTRL_OFS(regval)             (BITS(2,3) & ((uint32_t)(regval) << 2)) << 19                 /*!< write value to ENET_MAC_VLAN_TAG_CTRL_OFS bit field */
#define MAC_VLAN_TAG_FILTER0                      MAC_VLAN_TAG_CTRL_OFS(0)                                      /*!< MAC vlan tag filter 0 */
#define MAC_VLAN_TAG_FILTER1                      MAC_VLAN_TAG_CTRL_OFS(1)                                      /*!< MAC vlan tag filter 1 */
#define MAC_VLAN_TAG_FILTER2                      MAC_VLAN_TAG_CTRL_OFS(2)                                      /*!< MAC vlan tag filter 2 */
#define MAC_VLAN_TAG_FILTER3                      MAC_VLAN_TAG_CTRL_OFS(3)                                      /*!< MAC vlan tag filter 3 */

#define ENET_RXINVLAN_ENABLE                      ENET_MAC_VLAN_TAG_CTRL_EIVLRXS                                /*!< the MAC provides the inner VLAN tag in the Rx status */
#define ENET_RXINVLAN_DISABLE                     ((uint32_t)0x00000000U)                                       /*!< the MAC does not provide the inner VLAN tag in Rx status */

#define ENET_INVLANCOMPARISON_ENABLE              ENET_MAC_VLAN_TAG_CTRL_ERIVLT                                 /*!< inner VLAN tag is enabled */
#define ENET_INVLANCOMPARISON_DISABLE             ((uint32_t)0x00000000U)                                       /*!< inner VLAN tag is disabled */

#define ENET_DOUBLEVLAN_ENABLE                    ENET_MAC_VLAN_TAG_CTRL_EDVLP                                  /*!< MAC enables processing of up to two VLAN tags on Tx and Rx (if present) */
#define ENET_DOUBLEVLAN_DISABLE                   ((uint32_t)0x00000000U)                                       /*!< the MAC enables processing of up to one VLAN tag on Tx and Rx (if present) */

#define ENET_VLANHASHMATCH_ENABLE                 ENET_MAC_VLAN_TAG_CTRL_VTHM                                   /*!< VLAN tag hash table match is enabled */
#define ENET_VLANHASHMATCH_DISABLE                ((uint32_t)0x00000000U)                                       /*!< VLAN tag hash table match is disabled */

#define ENET_RXOUTVLAN_ENABLE                     ENET_MAC_VLAN_TAG_CTRL_EVLRXS                                 /*!< the MAC provides the VLAN tag in the Rx status */
#define ENET_RXOUTVLAN_DISABLE                    ((uint32_t)0x00000000U)                                       /*!< the MAC does not provide the VLAN tag in Rx status */

#define ENET_VLANTYPECHECK_ENABLE                 ((uint32_t)0x00000000U)                                       /*!< VLAN type check is enabled */
#define ENET_VLANTYPECHECK_DISABLE                ENET_MAC_VLAN_TAG_CTRL_DOVLTC                                 /*!< VLAN type check is disabled */

#define ENET_SVLANHASHMATCH_ENABLE                ENET_MAC_VLAN_TAG_CTRL_ERSVLM                                 /*!< receive S-VLAN match is enabled */
#define ENET_SVLANHASHMATCH_DISABLE               ((uint32_t)0x00000000U)                                       /*!< receive S-VLAN match is disabled */

#define ENET_SVLAN_ENABLE                         (ENET_MAC_VLAN_TAG_CTRL_ESVL| ENET_MAC_VLAN_TAG_CTRL_ERSVLM)  /*!< the MAC transmitter and receiver consider the S-VLAN packets (Type = 0x88A8) as valid VLAN tagged packets */
#define ENET_SVLAN_DISABLE                        ((uint32_t)0x00000000U)                                       /*!< the MAC transmitter and receiver consider the S-VLAN packets (Type = 0x88A8) as invalid VLAN tagged packets */

#define ENET_VLANINVERSEMATCH_ENABLE              ENET_MAC_VLAN_TAG_CTRL_VTIM                                   /*!< VLAN tag inverse match is enabled */
#define ENET_VLANINVERSEMATCH_DISABLE             ((uint32_t)0x00000000U)                                       /*!< VLAN tag inverse match is disabled */

#define ENET_VLANTAGHASHCOMPARISON_12BIT          ENET_MAC_VLAN_TAG_CTRL_ETV                                    /*!< only low 12 bits of the VLAN tag in received frame are used for comparison */
#define ENET_VLANTAGHASHCOMPARISON_16BIT          ((uint32_t)0x00000000U)                                       /*!< all 16 bits of the VLAN tag in received frame are used for comparison */

#define ENET_VLANTAG_FILTER_REG_READ              ENET_MAC_VLAN_TAG_CTRL_CT                                     /*!< read operation */
#define ENET_VLANTAG_FILTER_REG_WRITE             ((uint32_t)0x00000000U)                                       /*!< write operation */

/* MAC vlan tag data register value */
#define MAC_VLAN_TAG_DATA_VID(regval)            (BITS(0,15) & ((uint32_t)(regval) << 0))                       /*!< VLAN tag ID */

/* MAC vlan hash table register value */
#define MAC_VLAN_HASH_TABLE(regval)              (BITS(0,15) & ((uint32_t)(regval) << 0))                       /*!< VLAN hash table */

/* MAC Q0 tx flow control register value */
#define MAC_Q0_TX_FLOW_CTRL_PT(regval)           (BITS(16,31) & ((uint32_t)(regval) << 16))                     /*!< write value to ENET_MAC_Q0_TX_FLOW_CTRL_PT bit field */

#define MAC_Q0_TX_FLOW_CTRL_PLT(regval)          (BITS(4,6) & ((uint32_t)(regval) << 4))                        /*!< write value to ENET_MAC_Q0_TX_FLOW_CTRL_PLT bit field */
#define ENET_PAUSETIME_MINUS4                    MAC_Q0_TX_FLOW_CTRL_PLT(0)                                     /*!< pause time minus 4 slot times */
#define ENET_PAUSETIME_MINUS28                   MAC_Q0_TX_FLOW_CTRL_PLT(1)                                     /*!< pause time minus 28 slot times */
#define ENET_PAUSETIME_MINUS36                   MAC_Q0_TX_FLOW_CTRL_PLT(2)                                     /*!< pause time minus 36 slot times */
#define ENET_PAUSETIME_MINUS144                  MAC_Q0_TX_FLOW_CTRL_PLT(3)                                     /*!< pause time minus 144 slot times */
#define ENET_PAUSETIME_MINUS256                  MAC_Q0_TX_FLOW_CTRL_PLT(4)                                     /*!< pause time minus 256 slot times */
#define ENET_PAUSETIME_MINUS256_2                MAC_Q0_TX_FLOW_CTRL_PLT(5)                                     /*!< pause time minus 256 slot times */

#define ENET_ZERO_QUANTA_PAUSE_ENABLE            ((uint32_t)0x00000000U)                                        /*!< enable the automatic zero-quanta generation function */
#define ENET_ZERO_QUANTA_PAUSE_DISABLE           ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ                                  /*!< disable the automatic zero-quanta generation function */
#define ENET_ZERO_QUANTA_PAUSE                   ENET_MAC_Q0_TX_FLOW_CTRL_DZPQ                                  /*!< the automatic zero-quanta generation function */

#define ENET_TX_FLOWCONTROL_ENABLE               ENET_MAC_Q0_TX_FLOW_CTRL_TFE                                   /*!< enable the flow control operation in the MAC */
#define ENET_TX_FLOWCONTROL_DISABLE              ((uint32_t)0x00000000U)                                        /*!< disable the flow control operation in the MAC */
#define ENET_TX_FLOWCONTROL                      ENET_MAC_Q0_TX_FLOW_CTRL_TFE                                   /*!< the flow control operation in the MAC */

#define ENET_BACK_PRESSURE_ENABLE                ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA                               /*!< enable the back pressure operation in the MAC */
#define ENET_BACK_PRESSURE_DISABLE               ((uint32_t)0x00000000U)                                        /*!< disable the back pressure operation in the MAC */
#define ENET_BACK_PRESSURE                       ENET_MAC_Q0_TX_FLOW_CTRL_FCB_BPA                               /*!< the back pressure operation in the MAC */

/* MAC receive flow control register value */
#define ENET_MAC0_AND_UNIQUE_ADDRESS_PAUSEDETECT (ENET_MAC_RX_FLOW_CTRL_UP << 8)                                /*!< besides the unique multicast address, MAC also use the MAC0 address to detect pause frame */
#define ENET_UNIQUE_PAUSEDETECT                  ((uint32_t)0x00000000U)                                        /*!< only the unique multicast address for pause frame which is specified in IEEE802.3 can be detected */

#define ENET_RX_FLOWCONTROL_ENABLE               (ENET_MAC_RX_FLOW_CTRL_RFE << 8)                               /*!< enable decoding function for the received pause frame and process it */
#define ENET_RX_FLOWCONTROL_DISABLE              ((uint32_t)0x00000000U)                                        /*!< decode function for pause frame is disabled */
#define ENET_RX_FLOWCONTROL                      ENET_RX_FLOWCONTROL_ENABLE                                      /*!< decoding function for the received pause frame and process it */

/* ENET_MAC_RXQ_CTRL4 register value */
#define MAC_UNICAST_ADDRESS_FLITER_FAIL                 ENET_MAC_RXQ_CTRL4_UFFQE                                /*!< unicast address filter fail packets queuing enable */
#define MAC_MULTICAST_ADDRESS_FLITER_FAIL               ENET_MAC_RXQ_CTRL4_MFFQE                                /*!< multicast address filter fail packets queuing enable */
#define MAC_VLAN_TAG_FLITER_FAIL                        ENET_MAC_RXQ_CTRL4_VFFQE                                /*!< VLAN tag filter fail packets queuing enable */
#define MAC_UNICAST_ADDRESS_FLITER_FAIL_QUEUE(regval)   (BIT(1) & ((uint32_t)(regval) << 1))                    /*!< unicast address filter fail packets queue */
#define MAC_MULTICAST_ADDRESS_FLITER_FAIL_QUEUE(regval) (BIT(9) & ((uint32_t)(regval) << 9))                    /*!< multicast address filter fail packets queue */
#define MAC_VLAN_TAG_FLITER_FAIL_QUEUE(regval)          (BIT(17) & ((uint32_t)(regval) << 17))                  /*!< VLAN tag filter fail packets queue */


/* ENET_MAC_RXQ_CTRL1 register value */
#define MAC_RXQ_CTRL1_MCBCQEN(regval)                  (BIT(20) & ((uint32_t)(regval) << 20))                /*!< multicast and broadcast queue enable */
#define MAC_RXQ_CTRL1_TACPQE(regval)                   (BIT(21) & ((uint32_t)(regval) << 21))                /*!< tagged AV control packets queuing enable */
#define MAC_RXQ_CTRL1_TPQC(regval)                     (BITS(22,23) & ((uint32_t)(regval) << 22))            /*!< tagged PTP over ethernet packets queuing control */
#define MAC_RXQ_CTRL1_OMCBCQ(regval)                   (BIT(28) & ((uint32_t)(regval) << 28))                /*!< over-riding MC-BC queue priority select */
#define MAC_RXQ_CTRL1_TBRQE(regval)                    (BIT(29) & ((uint32_t)(regval) << 29))                /*!< type field based Rx queuing enable */

#define MAC_RXQ_MCBC_PRIORITY_ENABLE          MAC_RXQ_CTRL1_MCBCQEN(1)              /*!< multicast and broadcast queue enable */
#define MAC_RXQ_MCBC_PRIORITY_DISABLE         ~MAC_RXQ_MCBC_PRIORITY_ENABLE         /*!< multicast and broadcast queue disable */

#define MAC_RXQ_PTPOE_AS_GENERIC_VLAN         ~MAC_RXQ_CTRL1_TPQC(3)                /*!< VLAN Tagged PTPoE packets are routed as generic VLAN Tagged packet */
#define MAC_RXQ_PTPOE_TO_PTPQ                 MAC_RXQ_CTRL1_TPQC(1)                 /*!< VLAN Tagged PTPoE packets are routed to Rx Queue specified by PTPQ field */
#define MAC_RXQ_PTPOE_TO_PSRQ                 MAC_RXQ_CTRL1_TPQC(2)                 /*!< VLAN Tagged PTPoE packets are routed to only AV enabled Rx Queues based on PSRQ */

#define MAC_AV_TAG_PACKET_QUEUE_ENABLE        MAC_RXQ_CTRL1_TACPQE(1)               /*!< tagged AV control packets queuing enable */
#define MAC_AV_TAG_PACKET_QUEUE_DISABLE       ~MAC_AV_TAG_PACKET_QUEUE_ENABLE       /*!< tagged AV control packets queuing disable */

#define MAC_RXQ_MCBC_PRIORITY_OVER_ENABLE     MAC_RXQ_CTRL1_OMCBCQ(1)               /*!< over-riding MC-BC queue priority select enable */
#define MAC_RXQ_MCBC_PRIORITY_OVER_DISABLE    ~MAC_RXQ_MCBC_PRIORITY_OVER_ENABLE    /*!< over-riding MC-BC queue priority select disable */

#define MAC_RXQ_TYPE_BASED_ENABLE             MAC_RXQ_CTRL1_TBRQE(1)                /*!< type field based Rx queuing enable */
#define MAC_RXQ_TYPE_BASED_DISABLE            ~MAC_RXQ_TYPE_BASED_ENABLE            /*!< type field based Rx queuing disable */

/* MAC PMT control and status register value */
#define ENET_PMT_FLAG_RWKFILTRST                  MAC_PMT_CONTROL_STATUS_RWKFILTRST                              /*!< remote wake-up packet filter register pointer reset */
#define ENET_PMT_WAKE_UP_PACKET_FORWARDING        MAC_PMT_CONTROL_STATUS_RWKPFE                                  /*!< enable remote wake-up Packet Forwarding enabled */
#define ENET_PMT_FLAG_RWKPRCVD                    MAC_PMT_CONTROL_STATUS_RWKPRCVD                                /*!< wakeup frame received */
#define ENET_PMT_FLAG_MGKPRCVD                    MAC_PMT_CONTROL_STATUS_MGKPRCVD                                /*!< magic packet received */
#define ENET_PMT_POWER_DOWN                       MAC_PMT_CONTROL_STATUS_PWRDWN                                  /*!< power down mode */
#define ENET_PMT_MAGIC_PACKET_FRAME               MAC_PMT_CONTROL_STATUS_RWKPKTEN                                /*!< enable a wakeup event due to magic packet reception */
#define ENET_PMT_WAKE_UP_FRAME                    MAC_PMT_CONTROL_STATUS_MGKPKTEN                                /*!< enable a wakeup event due to wakeup frame reception */
#define ENET_PMT_GLOBAL_UNICAST                   MAC_PMT_CONTROL_STATUS_GLBLUCAST                               /*!< any received unicast frame passed filter is considered to be a wakeup frame */

/* MAC PMT control and status register value */
#define ENET_LPI_TXCLOCK_STOP                     ENET_MAC_LPI_CONTROL_STATUS_LPITCSE                            /*!< stop LPI Tx clock */
#define ENET_LPI_TX_AUTOMATE                      ENET_MAC_LPI_CONTROL_STATUS_LPITXA                             /*!< LPI Tx automate */

#define ENET_PHY_LINK_UP                          ENET_MAC_LPI_CONTROL_STATUS_PLS                                /*!< the link is considered to be okay (UP) */
#define ENET_PHY_LINK_DOWN                        ((uint32_t)0x00000000U)                                        /*!< the link is considered to be down */

#define ENET_LPI_STATE_ENTER                      ENET_MAC_LPI_CONTROL_STATUS_LPIEN                              /*!< it instructs the MAC transmitter to enter the LPI state */
#define ENET_LPI_STATE_EXIT                       ((uint32_t)0x00000000U)                                        /*!< it instructs the MAC to exit the LPI state and resume normal transmission */

#define ENET_RX_LPI_STATE_DETECTED                ENET_MAC_LPI_CONTROL_STATUS_RLPIST                             /*!< receive LPI state detected */
#define ENET_TX_LPI_STATE_DETECTED                ENET_MAC_LPI_CONTROL_STATUS_TLPIST                             /*!< transmit LPI state detected */
#define ENET_RX_LPI_EXIT_DETECTED                 ENET_MAC_LPI_CONTROL_STATUS_RLPIEX                             /*!< receive LPI exit detected */
#define ENET_RX_LPI_ENTRY_DETECTED                ENET_MAC_LPI_CONTROL_STATUS_RLPIEN                             /*!< receive LPI entry detected */
#define ENET_TX_LPI_EXIT_DETECTED                 ENET_MAC_LPI_CONTROL_STATUS_TLPIEX                             /*!< transmit LPI exit detected */
#define ENET_TX_LPI_ENTRY_DETECTED                ENET_MAC_LPI_CONTROL_STATUS_TLPIEN                             /*!< transmit LPI entry detected */

/* MAC LPI timers control register value */
#define MAC_LPI_TIMERS_CONTROL_LST(regval)        (BITS(16,25) & ((uint32_t)(regval) << 16))                     /*!< write value to ENET_MAC_LPI_TIMERS_CONTROL_LST bit field */
#define MAC_LPI_TIMERS_CONTROL_TWT(regval)        (BITS(0,15) & ((uint32_t)(regval) << 0))                       /*!< write value to ENET_MAC_LPI_TIMERS_CONTROL_TWT bit field */

/* MAC LPI entry timer register value */
#define MAC_LPI_ENTRY_TIMER_LPIET(regval)         (BITS(3,19) & ((uint32_t)(regval) << 3))                       /*!< write value to ENET_MAC_LPI_ENTRY_TIMER_LPIET bit field */

/* MAC 1 microsecond tic counter register value */
#define MAC_1US_TIC_COUNTER_TIC_1US_CNTR(regval)  (BITS(0,11) & ((uint32_t)(regval) << 0))                       /*!< write value to ENET_MAC_1US_TIC_COUNTER_TIC_1US_CNTR bit field */

/* MAC debug register value */
#define ENET_MAC_TRANSMITTER_STATUS                     ENET_MAC_DEBUG_TFCSTS                         /*!< status of MAC transmitter */
#define ENET_MAC_TX_PROTOCOL_ENGINE_STATUS_DETECTED     ENET_MAC_DEBUG_TPESTS                         /*!< it indicates that the MAC MII transmit protocol engine is actively transmitting data, and it is not in the idle state */
#define ENET_RX_CONTROLLER_FIFO_STATUS                  ENET_MAC_DEBUG_RFCFCSTS                       /*!< MAC receive packet controller FIFO status */
#define ENET_MAC_RX_PROTOCOL_ENGINE_STATUS_DETECTED     ENET_MAC_DEBUG_RPESTS                         /*!< it indicates that the MAC MII receive protocol engine is actively receiving data, and it is not in the idle state. */

#define GET_MAC_DEBUG_RPESTS(regval)                    GET_BITS((regval),1,2)                        /*!< get value of ENET_MAC_DEBUG_RPESTS bit field */

#define GET_MAC_DEBUG_TPESTS(regval)                    GET_BITS((regval),17,18)                      /*!< get value of ENET_MAC_DEBUG_TPESTS bit field */

/* MAC FSM control register value */
#define ENET_PTP_DOMAIN_LARGE_MODE                      ENET_MAC_FSM_CONTROL_PLGRNML                  /*!< large mode tic generation is used for PTP domain */
#define ENET_PTP_DOMAIN_NORMAL_MODE                     ((uint32_t)0x00000000U)                       /*!< large mode tic generation is used for PTP domain */

#define ENET_APP_DOMAIN_LARGE_MODE                      ENET_MAC_FSM_CONTROL_ALGRNML                  /*!< large mode tic generation is used for APP domain */
#define ENET_APP_DOMAIN_NORMAL_MODE                     ((uint32_t)0x00000000U)                       /*!< large mode tic generation is used for APP domain */

#define ENET_CSR_DOMAIN_LARGE_MODE                      ENET_MAC_FSM_CONTROL_CLGRNML                  /*!< large mode tic generation is used for CSR domain */
#define ENET_CSR_DOMAIN_NORMAL_MODE                     ((uint32_t)0x00000000U)                       /*!< large mode tic generation is used for CSR domain */

#define ENET_RX_DOMAIN_LARGE_MODE                       ENET_MAC_FSM_CONTROL_RLGRNML                  /*!< large mode tic generation is used for Rx domain */
#define ENET_RX_DOMAIN_NORMAL_MODE                      ((uint32_t)0x00000000U)                       /*!< large mode tic generation is used for Rx domain */

#define ENET_TX_DOMAIN_LARGE_MODE                       ENET_MAC_FSM_CONTROL_TLGRNML                  /*!< large mode tic generation is used for Tx domain */
#define ENET_TX_DOMAIN_NORMAL_MODE                      ((uint32_t)0x00000000U)                       /*!< large mode tic generation is used for Tx domain */

#define ENET_PTP_FSM_PARITY_ERROR_INJECTION_ENABLE      ENET_MAC_FSM_CONTROL_PPEIN                    /*!< PTP FSM parity error injection is enabled */
#define ENET_PTP_FSM_PARITY_ERROR_INJECTION_DISABLE     ((uint32_t)0x00000000U)                       /*!< PTP FSM parity error injection is disabled */

#define ENET_APP_FSM_PARITY_ERROR_INJECTION_ENABLE      ENET_MAC_FSM_CONTROL_APEIN                    /*!< APP FSM parity error injection is enabled */
#define ENET_APP_FSM_PARITY_ERROR_INJECTION_DISABLE     ((uint32_t)0x00000000U)                       /*!< APP FSM parity error injection is disabled */

#define ENET_CSR_FSM_ONEHOTPROTECTION_ERROR_INJECTION_ENABLE  ENET_MAC_FSM_CONTROL_CPEIN                    /*!< CSR FSM one hot protection error injection is enabled */
#define ENET_CSR_FSM_ONEHOTPROTECTION_ERROR_INJECTION_DISABLE ((uint32_t)0x00000000U)                       /*!< CSR FSM one hot protection error injection is disabled */

#define ENET_RX_FSM_PARITY_ERROR_INJECTION_ENABLE       ENET_MAC_FSM_CONTROL_RPEIN                    /*!< Rx FSM parity error injection is enabled */
#define ENET_RX_FSM_PARITY_ERROR_INJECTION_DISABLE      ((uint32_t)0x00000000U)                       /*!< Rx FSM parity error injection is disabled */

#define ENET_TX_FSM_PARITY_ERROR_INJECTION_ENABLE       ENET_MAC_FSM_CONTROL_TPEIN                    /*!< Tx FSM parity error injection is enabled */
#define ENET_TX_FSM_PARITY_ERROR_INJECTION_DISABLE      ((uint32_t)0x00000000U)                       /*!< Tx FSM parity error injection is disabled */

#define ENET_PTP_FSM_TIMEOUT_ERROR_INJECTION_ENABLE     ENET_MAC_FSM_CONTROL_PTEIN                    /*!< PTP FSM timeout error injection is enabled */
#define ENET_PTP_FSM_TIMEOUT_ERROR_INJECTION_DISABLE    ((uint32_t)0x00000000U)                       /*!< PTP FSM timeout error injection is disabled */

#define ENET_APP_FSM_TIMEOUT_ERROR_INJECTION_ENABLE     ENET_MAC_FSM_CONTROL_ATEIN                    /*!< APP FSM timeout error injection is enabled */
#define ENET_APP_FSM_TIMEOUT_ERROR_INJECTION_DISABLE    ((uint32_t)0x00000000U)                       /*!< APP FSM timeout error injection is disabled */

#define ENET_CSR_FSM_TIMEOUT_ERROR_INJECTION_ENABLE     ENET_MAC_FSM_CONTROL_CTEIN                    /*!< CSR FSM timeout error injection is enabled */
#define ENET_CSR_FSM_TIMEOUT_ERROR_INJECTION_DISABLE    ((uint32_t)0x00000000U)                       /*!< CSR FSM timeout error injection is disabled */

#define ENET_RX_FSM_TIMEOUT_ERROR_INJECTION_ENABLE      ENET_MAC_FSM_CONTROL_RTEIN                    /*!< Rx FSM timeout error injection is enabled */
#define ENET_RX_FSM_TIMEOUT_ERROR_INJECTION_DISABLE     ((uint32_t)0x00000000U)                       /*!< Rx FSM timeout error injection is disabled */

#define ENET_TX_FSM_TIMEOUT_ERROR_INJECTION_ENABLE      ENET_MAC_FSM_CONTROL_TTEIN                    /*!< Tx FSM timeout error injection is enabled */
#define ENET_TX_FSM_TIMEOUT_ERROR_INJECTION_DISABLE     ((uint32_t)0x00000000U)                       /*!< Tx FSM timeout error injection is disabled */



#define ENET_FSM_PARITY_FEATURE_ENABLE                  ENET_MAC_FSM_CONTROL_PRTYEN                   /*!< FSM parity feature is enabled */
#define ENET_FSM_PARITY_FEATURE_DISABLE                 ((uint32_t)0x00000000U)                       /*!< FSM parity feature is disabled */

#define ENET_FSM_TIMEOUT_FEATURE_ENABLE                 ENET_MAC_FSM_CONTROL_TMOUTEN                  /*!< FSM timeout feature is enabled */
#define ENET_FSM_TIMEOUT_FEATURE_DISABLE                ((uint32_t)0x00000000U)                       /*!< FSM timeout feature is disabled */

/* MAC FSM ACT timer register value */
#define MAC_FSM_ACT_TIMER_LTMRMD(regval)                (BITS(20,23) & ((uint32_t)(regval) << 20))    /*!< write value to ENET_MAC_FSM_ACT_TIMER_LTMRMD bit field */
#define ENET_FSM_LARGE_MODE_TIMEOUT_DISABLE             MAC_FSM_ACT_TIMER_LTMRMD(0)                   /*!< timer disabled */
#define ENET_FSM_LARGE_MODE_TIMEOUT_1US                 MAC_FSM_ACT_TIMER_LTMRMD(1)                   /*!< 1us */
#define ENET_FSM_LARGE_MODE_TIMEOUT_4MS                 MAC_FSM_ACT_TIMER_LTMRMD(2)                   /*!< 1.024ms (~4ms) */
#define ENET_FSM_LARGE_MODE_TIMEOUT_16MS                MAC_FSM_ACT_TIMER_LTMRMD(3)                   /*!< 16.384ms (~16ms) */
#define ENET_FSM_LARGE_MODE_TIMEOUT_64MS                MAC_FSM_ACT_TIMER_LTMRMD(4)                   /*!< 65.536ms (~64ms) */
#define ENET_FSM_LARGE_MODE_TIMEOUT_256MS               MAC_FSM_ACT_TIMER_LTMRMD(5)                   /*!< 262.144ms (~256ms) */
#define ENET_FSM_LARGE_MODE_TIMEOUT_1SEC                MAC_FSM_ACT_TIMER_LTMRMD(6)                   /*!< 1.048sec (~1sec) */
#define ENET_FSM_LARGE_MODE_TIMEOUT_4SEC                MAC_FSM_ACT_TIMER_LTMRMD(7)                   /*!< 4.194sec (~4sec) */
#define ENET_FSM_LARGE_MODE_TIMEOUT_16SEC               MAC_FSM_ACT_TIMER_LTMRMD(8)                   /*!< 16.777sec (~16sec) */
#define ENET_FSM_LARGE_MODE_TIMEOUT_32SEC               MAC_FSM_ACT_TIMER_LTMRMD(9)                   /*!< 33.554sec (~32sec) */
#define ENET_FSM_LARGE_MODE_TIMEOUT_64SEC               MAC_FSM_ACT_TIMER_LTMRMD(10)                  /*!< 67.108sec (~64sec) */

/* MAC FSM ACT timer register value */
#define MAC_FSM_ACT_TIMER_NTMRMD(regval)                (BITS(16,19) & ((uint32_t)(regval) << 16))    /*!< write value to ENET_MAC_FSM_ACT_TIMER_NTMRMD bit field */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_DISABLE             MAC_FSM_ACT_TIMER_NTMRMD(0)                   /*!< timer disabled */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_1US                 MAC_FSM_ACT_TIMER_NTMRMD(1)                   /*!< 1us */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_4MS                 MAC_FSM_ACT_TIMER_NTMRMD(2)                   /*!< 1.024ms (~4ms) */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_16MS                MAC_FSM_ACT_TIMER_NTMRMD(3)                   /*!< 16.384ms (~16ms) */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_64MS                MAC_FSM_ACT_TIMER_NTMRMD(4)                   /*!< 65.536ms (~64ms) */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_256MS               MAC_FSM_ACT_TIMER_NTMRMD(5)                   /*!< 262.144ms (~256ms) */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_1SEC                MAC_FSM_ACT_TIMER_NTMRMD(6)                   /*!< 1.048sec (~1sec) */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_4SEC                MAC_FSM_ACT_TIMER_NTMRMD(7)                   /*!< 4.194sec (~4sec) */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_16SEC               MAC_FSM_ACT_TIMER_NTMRMD(8)                   /*!< 16.777sec (~16sec) */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_32SEC               MAC_FSM_ACT_TIMER_NTMRMD(9)                   /*!< 33.554sec (~32sec) */
#define ENET_FSM_NORMAL_MODE_TIMEOUT_64SEC               MAC_FSM_ACT_TIMER_NTMRMD(10)                  /*!< 67.108sec (~64sec) */

#define MAC_FSM_ACT_TIMER_TIMEOUT(regval)                (BITS(0,3) & ((uint32_t)(regval) << 0))       /*!< set timeout value */
#define ENET_FSM_TIMEOUT_DISABLE                         MAC_FSM_ACT_TIMER_TIMEOUT(0)                   /*!< timer disabled */
#define ENET_FSM_TIMEOUT_1US                             MAC_FSM_ACT_TIMER_TIMEOUT(1)                   /*!< 1us */
#define ENET_FSM_TIMEOUT_4MS                             MAC_FSM_ACT_TIMER_TIMEOUT(2)                   /*!< 1.024ms (~4ms) */
#define ENET_FSM_TIMEOUT_16MS                            MAC_FSM_ACT_TIMER_TIMEOUT(3)                   /*!< 16.384ms (~16ms) */
#define ENET_FSM_TIMEOUT_64MS                            MAC_FSM_ACT_TIMER_TIMEOUT(4)                   /*!< 65.536ms (~64ms) */
#define ENET_FSM_TIMEOUT_256MS                           MAC_FSM_ACT_TIMER_TIMEOUT(5)                   /*!< 262.144ms (~256ms) */
#define ENET_FSM_TIMEOUT_1SEC                            MAC_FSM_ACT_TIMER_TIMEOUT(6)                   /*!< 1.048sec (~1sec) */
#define ENET_FSM_TIMEOUT_4SEC                            MAC_FSM_ACT_TIMER_TIMEOUT(7)                   /*!< 4.194sec (~4sec) */
#define ENET_FSM_TIMEOUT_16SEC                           MAC_FSM_ACT_TIMER_TIMEOUT(8)                   /*!< 16.777sec (~16sec) */
#define ENET_FSM_TIMEOUT_32SEC                           MAC_FSM_ACT_TIMER_TIMEOUT(9)                   /*!< 33.554sec (~32sec) */
#define ENET_FSM_TIMEOUT_64SEC                           MAC_FSM_ACT_TIMER_TIMEOUT(10)                  /*!< 67.108sec (~64sec) */

#define MAC_FSM_ACT_TIMER_TMR(regval)                   (BITS(0,9) & ((uint32_t)(regval) << 0))         /*!< write value to ENET_MAC_FSM_ACT_TIMER_TMR bit field */

#define MAC_MDIO_ADDRESS_GOC(regval)                     (BITS(2,3) & ((uint32_t)(regval) << 2))       /*!< write value to ENET_MAC_MDIO_ADDRESS_GOC bit field */
#define ENET_MDIO_OPERATION_WRITE                        MAC_MDIO_ADDRESS_GOC(1)                       /*!< write */
#define ENET_MDIO_POSTREAD_INCREMENT_ADDRESS             MAC_MDIO_ADDRESS_GOC(2)                       /*!< post read increment address for Clause 45 PHY */
#define ENET_MDIO_OPERATION_READ                         MAC_MDIO_ADDRESS_GOC(3)                       /*!< read */

#define MAC_MDIO_ADDRESS_NTC(regval)                    (BITS(12,14) & ((uint32_t)(regval) << 12))     /*!< write value to ENET_MAC_MDIO_ADDRESS_NTC bit field */

#define MAC_MDIO_ADDRESS_RDA(regval)                    (BITS(16,20) & ((uint32_t)(regval) << 16))     /*!< write value to ENET_MAC_MDIO_ADDRESS_RDA bit field */

#define MAC_MDIO_ADDRESS_PA(regval)                     (BITS(21,25) & ((uint32_t)(regval) << 21))     /*!< write value to ENET_MAC_MDIO_ADDRESS_PA bit field */

#define ENET_PHY_CLAUSE_45                              ENET_MAC_MDIO_ADDRESS_C45E                    /*!< Clause 45 PHY is enabled */
#define ENET_PHY_CLAUSE_22                              ((uint32_t)0x00000000U)                       /*!< Clause 22 PHY is enabled */

/* MAC MDIO data register value */
#define MAC_MDIO_DATA_GD(regval)                        (BITS(0,15) & ((uint32_t)(regval) << 0))       /*!< write value to ENET_MAC_MDIO_ADDRESS_GD bit field */

#define MAC_MDIO_DATA_RA(regval)                        (BITS(16,31) & ((uint32_t)(regval) << 16))      /*!< write value to ENET_MAC_MDIO_ADDRESS_RA bit field */

/* MAC ARP address register value */
#define MAC_ARP_ADDRESS_ARPPA(regval)               (BITS(0,31) & ((uint32_t)(regval) << 0))       /*!< write value to ENET_MAC_MAC_ARP_ADDRESS_ARPPA bit field */

/* MAC CSR software control register value */
#define ENET_SLAVE_ERROR_RESPONSE_ENABLE                ENET_MAC_CSR_SW_CTRL_SEEN                      /*!< the MAC responds with Slave Error for accesses to reserved registers in CSR space. */
#define ENET_SLAVE_ERROR_RESPONSE_DISABLE               ((uint32_t)0x00000000U)                        /*!< the MAC responds with Okay response to any register accessed from CSR space */

#define ENET_REGISTER_CLEAR_ON_WRITE_1                  ENET_MAC_CSR_SW_CTRL_RCWE                      /*!< the access mode of some register fields changes to Clear on Write 1, the application needs to set that respective bit to 1 to clear it */
#define ENET_REGISTER_CLEAR_ON_READ                     ((uint32_t)0x00000000U)                        /*!< the access mode of these register fields remain as Clear on Read */

/* MAC FPE control STS register value */
#define ENET_TRANSMITTED_RESPOND_FRAME                  ENET_MAC_FPE_CTRL_STS_TRSP                     /*!< transmitted respond frame */
#define ENET_TRANSMITTED_VERIFY_FRAME                   ENET_MAC_FPE_CTRL_STS_TVER                     /*!< transmitted verify frame */
#define ENET_RECEIVED_RESPOND_FRAME                     ENET_MAC_FPE_CTRL_STS_RRSP                     /*!< received respond frame */
#define ENET_RECEIVED_VERIFY_FRAME                      ENET_MAC_FPE_CTRL_STS_RVER                     /*!< received verify frame */
#define ENET_SEND_RESPOND_FRAME                         ENET_MAC_FPE_CTRL_STS_SRSP                     /*!< send respond frame */
#define ENET_SEND_VERIFY_FRAME                          ENET_MAC_FPE_CTRL_STS_SVER                     /*!< send verify frame */

#define ENET_AUTOGENERATE_RESPOND_MPACKET_ENABLE        ENET_MAC_FPE_CTRL_STS_ARV                      /*!< autogenerate respond mPacket on receiving verify mPacket is enabled */
#define ENET_AUTOGENERATE_RESPOND_MPACKET_DISABLE       ((uint32_t)0x00000000U)                        /*!< autogenerate respond mPacket on receiving verify mPacket is disable */
#define ENET_AUTOGENERATE_RESPOND_MPACKET               ENET_MAC_FPE_CTRL_STS_ARV           

#define ENET_TX_FRAME_PREEMPTION_ENABLE                 ENET_MAC_FPE_CTRL_STS_EFPE                     /*!< Tx frame preemption is enabled */
#define ENET_TX_FRAME_PREEMPTION_DISABLE                ((uint32_t)0x00000000U)                               /*!< Tx frame preemption is disable */
#define ENET_TX_FRAME_PREEMPTION                        ENET_MAC_FPE_CTRL_STS_EFPE
/* MAC presentation time register value */
#define MAC_PRESN_TIME_NS_MPTN(regval)                  (BITS(0,31) & ((uint32_t)(regval) << 0))       /*!< write value to ENET_MAC_PRESN_TIME_NS_MPTN bit field */

/* MAC pesentation time update register value */
#define MAC_PRESN_TIME_UPDT_MPTU(regval)                (BITS(0,31) & ((uint32_t)(regval) << 0))       /*!< write value to ENET_MAC_PRESN_TIME_UPDT_MPTU bit field */

/* MAC address 0 high register value */
#define MAC_ADDR0H_ADDRH(regval)                        (BITS(0,15) & ((uint32_t)(regval) << 0))      /*!< write value to ENET_MAC_ADDRESS0_HIGH_ADDRH bit field */

/* MAC addressx high register value, x = 1,2 */
#define MAC_ADDR12H_ADDR12H(regval)                     (BITS(0,15) & ((uint32_t)(regval) << 0))      /*!< write value to ENET_MAC_ADDRESSx_ADDRH(x=1,2) bit field */

#define ENET_ADDRESS_MASK_NONE                          ((uint32_t)0x00000000)                        /*!< do not mask any bytes */
#define ENET_ADDRESS_MASK_BYTE0                         BIT(24)                                       /*!< low register bits [7:0] */
#define ENET_ADDRESS_MASK_BYTE1                         BIT(25)                                       /*!< low register bits [15:8] */
#define ENET_ADDRESS_MASK_BYTE2                         BIT(26)                                       /*!< low register bits [23:16] */
#define ENET_ADDRESS_MASK_BYTE3                         BIT(27)                                       /*!< low register bits [31:24] */
#define ENET_ADDRESS_MASK_BYTE4                         BIT(28)                                       /*!< high register bits [7:0] */
#define ENET_ADDRESS_MASK_BYTE5                         BIT(29)                                       /*!< high register bits [15:8] */

#define ENET_ADDRESS_FILTER_SA                          BIT(30)                                       /*!< use MAC address[47:0] is to compare with the SA fields of the received frame */
#define ENET_ADDRESS_FILTER_DA                         ((uint32_t)0x00000000)                         /*!< use MAC address[47:0] is to compare with the DA fields of the received frame */

/* MMC control register value */
#define ENET_MMC_DROPPED_BROADCAST_UPDATE         ENET_MMC_CONTROL_UCDBC                             /*!< update MMC counters for dropped broadcast packets */
#define ENET_MMC_COUNTER_STOP_ROLLOVER            ENET_MMC_CONTROL_CNTSTOPRO                         /*!< counter stop rollover */
#define ENET_MMC_RESET_ON_READ                    ENET_MMC_CONTROL_RSTONRD                           /*!< reset on read */
#define ENET_MMC_COUNTERS_FREEZE                  ENET_MMC_CONTROL_CNTFREEZ                          /*!< MMC counter freeze */

/* MAC layer 3 layer 4 control register value */
#define MAC_L3_L4_CONTROL_L3HDBM0(regval)              (BITS(11,15) & ((uint32_t)(regval) << 11))     /*!< write value to ENET_MAC_L3_L4_CONTROL_L3HDBM0 bit field */

#define MAC_L3_L4_CONTROL_L3HSBM0(regval)              (BITS(6,10) & ((uint32_t)(regval) << 6))       /*!< write value to ENET_MAC_L3_L4_CONTROL_L3HSBM0 bit field */

#define MAC_L3_L4_CONTROL_DMCHN0(regval)               (BIT(24) & ((uint32_t)(regval) << 24))         /*!< write value to ENET_MAC_L3_L4_CONTROL_DMCHN0 bit field */

#define ENET_L3L4FILTER_DMA_CHANNEL_SELECT              ENET_MAC_L3_L4_CONTROL_DMCHEN0                /*!< enable the selection of the DMA channel number for the packet that is passed by L3_L4 filter */
#define ENET_L3L4FILTER_DMA_CHANNEL_1                   ENET_MAC_L3_L4_CONTROL_DMCHN0                 /*!< selects the DMA Channel 1 to which the packet passed by this filter is routed */
#define ENET_L3L4FILTER_DMA_CHANNEL_0                   ((uint32_t)0x00000000)                        /*!< selects the DMA Channel 0 to which the packet passed by this filter is routed */

#define ENET_L4_DEST_PORT_NORMAL_MATCH                  ENET_MAC_L3_L4_CONTROL_L4DPM0                                       /*!< the layer 4 destination port number field is configurated for matching */
#define ENET_L4_DEST_PORT_INVERSE_MATCH                (ENET_MAC_L3_L4_CONTROL_L4DPM0 | ENET_MAC_L3_L4_CONTROL_L4DPIM0)     /*!< the layer 4 destination port number field is configurated for inverse matching */
#define ENET_L4_DEST_PORT_MATCH_DISABLE                ((uint32_t)0x00000000)                                               /*!< the MAC ignores the layer 4 destination port number field for matching */

#define ENET_L4_SRC_PORT_NORMAL_MATCH            ENET_MAC_L3_L4_CONTROL_L4SPM0                                       /*!< the layer 4 source port number field is configurated for matching */
#define ENET_L4_SRC_PORT_INVERSE_MATCH           (ENET_MAC_L3_L4_CONTROL_L4SPM0 | ENET_MAC_L3_L4_CONTROL_L4SPIM0)    /*!< the layer 4 source port number field is configurated for inverse matching */
#define ENET_L4_SRC_PORT_MATCH_DISABLE                  ((uint32_t)0x00000000)                                              /*!< the MAC ignores the layer 4 source port number field for matching */

#define ENET_L4_PROTOCOL_MATCH_UDP                      ENET_MAC_L3_L4_CONTROL_L4PEN0                 /*!< the source and destination port number fields of UDP packets are used for matching */


#define ENET_L3_DEST_IPADDR_NORMAL_MATCH                ENET_MAC_L3_L4_CONTROL_L3DAM0                                      /*!< the layer 3 IP destination address field is configurated for matching */
#define ENET_L3_DEST_IPADDR_INVERSE_MATCH              (ENET_MAC_L3_L4_CONTROL_L3DAM0 | ENET_MAC_L3_L4_CONTROL_L3DAIM0)    /*!< the layer 3 IP destination address field is configurated for inverse matching */
#define ENET_L3_DEST_IPADDR_MATCH_DISABLE              ((uint32_t)0x00000000)                                              /*!< the MAC ignores the layer 4 destination port number field for matching */

#define ENET_L3_SRC_IPADDR_NORMAL_MATCH                ENET_MAC_L3_L4_CONTROL_L3SAM0                                       /*!< the Layer 3 IP source address field is configurated for matching */
#define ENET_L3_SRC_IPADDR_INVERSE_MATCH              (ENET_MAC_L3_L4_CONTROL_L3SAM0 | ENET_MAC_L3_L4_CONTROL_L3SAIM0)     /*!< the layer 3 IP source address field is configurated for inverse matching */
#define ENET_L3_SRC_IPADDR_MATCH_DISABLE              ((uint32_t)0x00000000)                                               /*!< the MAC ignores the layer 3 IP source address field for matching */

#define ENET_L3_PROTOCOL_MATCH_IPV6                   ENET_MAC_L3_L4_CONTROL_L3PEN0                                        /*!< the layer 3 IP source or destination address matching is configurated for IPv6 packets */
#define ENET_L3_PROTOCOL_MATCH_IPV4                   ((uint32_t)0x00000000)                                               /*!< the layer 3 IP source or destination address matching is configurated for IPv4 packets */


/* MAC layer 4 address register value */
#define MAC_LAYER4_ADDRESS_L4DP0(regval)               (BITS(16,31) & ((uint32_t)(regval) << 16))               /*!< write value to ENET_MAC_LAYER4_ADDRESS_L4DP0 bit field */

#define MAC_LAYER4_ADDRESS_L4SP0(regval)               (BITS(0,15) & ((uint32_t)(regval) << 0))                 /*!< write value to ENET_MAC_LAYER4_ADDRESS_L4SP0 bit field */

/* MAC indirect access control register value */
#define MAC_INDIR_ACCESS_CTRL_MSEL(regval)              (BITS(16,19) & ((uint32_t)(regval) << 16))               /*!< write value to ENET_MAC_INDIR_ACCESS_CTRL_MSEL bit field */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REGS                MAC_INDIR_ACCESS_CTRL_MSE(0)                             /*!< MAC_TMRQ_Regs */

#define MAC_INDIR_ACCESS_CTRL_AOFF(regval)             (BITS(8,15) & ((uint32_t)(regval) << 8))                 /*!< write value to ENET_MAC_INDIR_ACCESS_CTRL_AOFF bit field */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REG0                MAC_INDIR_ACCESS_CTRL_AOFF(0)                            /*!< MAC_TMRQ_Reg0 */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REG1                MAC_INDIR_ACCESS_CTRL_AOFF(1)                            /*!< MAC_TMRQ_Reg1 */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REG2                MAC_INDIR_ACCESS_CTRL_AOFF(2)                            /*!< MAC_TMRQ_Reg2 */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REG3                MAC_INDIR_ACCESS_CTRL_AOFF(3)                            /*!< MAC_TMRQ_Reg3 */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REG4                MAC_INDIR_ACCESS_CTRL_AOFF(4)                            /*!< MAC_TMRQ_Reg4 */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REG5                MAC_INDIR_ACCESS_CTRL_AOFF(5)                            /*!< MAC_TMRQ_Reg5 */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REG6                MAC_INDIR_ACCESS_CTRL_AOFF(6)                            /*!< MAC_TMRQ_Reg6 */
#define ENET_INDIR_ACCESS_MAC_TMRQ_REG7                MAC_INDIR_ACCESS_CTRL_AOFF(7)                            /*!< MAC_TMRQ_Reg7 */

#define ENET_ADDR_OFFSET_AUTO_INCREMENT                ENET_MAC_INDIR_ACCESS_CTRL_AUTO                          /*!< AOFF is incremented by 1 */
#define ENET_INDIR_ACCESS_READ                         ENET_MAC_INDIR_ACCESS_CTRL_COM                           /*!< read operation */
#define ENET_INDIR_ACCESS_WRITE                        ((uint32_t)0x00000000)                                   /*!< write operation */
#define ENET_INDIR_ACCESS_BUSY                         ENET_MAC_INDIR_ACCESS_CTRL_OB                            /*!< operation busy */



/* MAC type match recieve queue number register value */
#define MAC_TMRQ_REGS_PFEX(regval)                    (BIT(20) & ((uint32_t)(regval) << 20))                   /*!< write value to ENET_MAC_TMRQ_REGS_PFEX bit field */

#define MAC_TMRQ_REGS_TMRQ(regval)                    (BITS(16,18) & ((uint32_t)(regval) << 16))               /*!< write value to ENET_MAC_TMRQ_REGS_TMRQ bit field */

#define MAC_TMRQ_REGS_TYP(regval)                     (BITS(0,15) & ((uint32_t)(regval) << 0))                 /*!< write value to ENET_MAC_TMRQ_REGS_TYP bit field */

/* MAC_Timestamp_Control register value */
#define ENET_RXTX_TIMESTAMP                           ENET_MAC_TIMESTAMP_CONTROL_TSENA                          /*!< enable timestamp function for transmit and receive frames */
#define ENET_PRESENTATION_TIMESTAMP                   ENET_MAC_TIMESTAMP_CONTROL_PTGE                           /*!< enable presentation time generation function */
#define ENET_ALL_RX_TIMESTAMP                         ENET_MAC_TIMESTAMP_CONTROL_TSENALL                        /*!< all received frames are taken snapshot */
#define ENET_NONTYPE_FRAME_SNAPSHOT                   ENET_MAC_TIMESTAMP_CONTROL_TSIPENA                        /*!< take snapshot when received non type frame */
#define ENET_IPV6_FRAME_SNAPSHOT                      ENET_MAC_TIMESTAMP_CONTROL_TSIPV6ENA                      /*!< take snapshot for IPv6 frame */
#define ENET_IPV4_FRAME_SNAPSHOT                      ENET_MAC_TIMESTAMP_CONTROL_TSIPV4ENA                      /*!< take snapshot for IPv4 frame */
#define ENET_PTP_FRAME_USE_MACADDRESS_FILTER          ENET_MAC_TIMESTAMP_CONTROL_TSENMACADDR                    /*!< enable MAC address to filter the PTP frame */
#define ENET_TX_TIMESTAMP_OVERWRITE                   ENET_MAC_TIMESTAMP_CONTROL_TXTSSTSM                    /*!< enable transmit timestamp status mode */
#define ENET_AV8021_AS_MODE                           ENET_MAC_TIMESTAMP_CONTROL_AV8021ASMEN                    /*!< enable AV 802.1AS mode-  the MAC processes only untagged PTP over Ethernet packets */


/* MAC_Sub_Second_Increment register value */
#define PTP_SUB_SECOND_INCREMENT_SSINC(regval)        (BITS(16,23) & ((uint32_t)(regval) << 16))           /*!< write value to MAC_PTP_SUB_SECOND_INCREMENT_SSINC bit field */
#define PTP_SUB_SECOND_INCREMENT_SNSINC(regval)       (BITS(8,15) & ((uint32_t)(regval) << 8))             /*!< write value to MAC_PTP_SUB_SECOND_INCREMENT_SNSINC bit field */

/* MAC_System_Time_Nanoseconds register value */
#define GET_PTP_SYSTIME_TSSSS(regval)                  GET_BITS((uint32_t)(regval),0,30)                   /*!< get value of ENET_MAC_SYSTEM_TIME_NANOSECONDS_TSSS bit field */

/* MAC_System_Time_Nanoseconds_Update register value */
#define MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS(regval)     (BITS(0,30) & ((uint32_t)(regval) << 0))       /*!< write value to ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_TSSS bit field */

#define ENET_PTP_ADD_TO_TIME                      ((uint32_t)0x00000000)                                   /*!< timestamp update value is added to system time */
#define ENET_PTP_SUBSTRACT_FROM_TIME              ENET_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_ADDSUB           /*!< timestamp update value is subtracted from system time */

/* MAC system time higher word in seconds register value */
#define MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR(regval)   (BITS(0,15) & ((uint32_t)(regval) << 0))          /*!< write value to ENET_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_TSHWR bit field */

/* MAC receive clock domain time increment value register value */
#define MAC_RX_DOMAIN_TIME_INCR_RXSNS(regval)               (BITS(8,15) & ((uint32_t)(regval) << 8))          /*!< write value to ENET_MAC_RX_DOMAIN_TIME_INCR_RXSNS bit field */

#define MAC_RX_DOMAIN_TIME_INCR_RXNS(regval)                (BITS(16,31) & ((uint32_t)(regval) << 31))        /*!< write value to ENET_MAC_RX_DOMAIN_TIME_INCR_RXNS bit field */

/* MAC receive clock domain time increment value register value */
#define MAC_TX_DOMAIN_TIME_INCR_TXSNS(regval)               (BITS(8,15) & ((uint32_t)(regval) << 8))          /*!< write value to ENET_MAC_TX_DOMAIN_TIME_INCR_TXSNS bit field */

#define MAC_TX_DOMAIN_TIME_INCR_TXNS(regval)                (BITS(16,31) & ((uint32_t)(regval) << 31))        /*!< write value to ENET_MAC_TX_DOMAIN_TIME_INCR_TXNS bit field */

/* MAC transmit timestamp status in nanoseconds register value */
#define GET_TX_TIMESTAMP_STATUS_LOW(regval)                 GET_BITS((uint32_t)(regval),0,30)                 /*!< get value of ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSLO bit field */

#define ENET_TX_TIMESTAMP_STATUS_MISSED                     ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_TXTSSMIS /*!< enable timestamp function for transmit and receive frames */

/* MAC timestamp ingress correction in subnanoseconds register value */
#define MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS(regval) (BITS(8,15) & ((uint32_t)(regval) << 8))          /*!< write value to ENET_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_TSICSNS bit field */

/* MAC timestamp egress correction in subnanoseconds register value */
#define MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS(regval) (BITS(8,15) & ((uint32_t)(regval) << 8))          /*!< write value to ENET_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_TSECSNS bit field */

/* MAC timestamp ingress latency register value */
#define MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS(regval)       (BITS(8,15) & ((uint32_t)(regval) << 8))           /*!< write value to ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLSNS bit field */

#define MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS(regval)         (BITS(16,27) & ((uint32_t)(regval) << 16))         /*!< write value to ENET_MAC_TIMESTAMP_INGRESS_LATENCY_ITLNS bit field */

/* MAC timestamp egress latency register value */
#define MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS(regval)       (BITS(8,15) & ((uint32_t)(regval) << 8))           /*!< write value to ENET_MAC_TIMESTAMP_EGRESS_LATENCY_ETLSNS bit field */

#define MAC_TIMESTAMP_EGRESS_LATENCY_ETLNS(regval)         (BITS(16,27) & ((uint32_t)(regval) << 16))         /*!< write value to ENET_TIMESTAMP_EGRESS_LATENCY_ETLNS bit field */

/* MAC PPS control register value */
#define MAC_PPS_CONTROL_PPSCTRL_PPSCMD(regval)     (BITS(0,3) & ((uint32_t)(regval) << 0))                    /*!< write value to ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD bit field */
#define ENET_PPSOFC_1HZ                            MAC_PPS_CONTROL_PPSCTRL_PPSCMD(0)                          /*!< PPS output 1Hz frequency */
#define ENET_PPSOFC_2HZ                            MAC_PPS_CONTROL_PPSCTRL_PPSCMD(1)                          /*!< PPS output 2Hz frequency */
#define ENET_PPSOFC_4HZ                            MAC_PPS_CONTROL_PPSCTRL_PPSCMD(2)                          /*!< PPS output 4Hz frequency */
#define ENET_PPSOFC_8HZ                            MAC_PPS_CONTROL_PPSCTRL_PPSCMD(3)                          /*!< PPS output 8Hz frequency */
#define ENET_PPSOFC_16HZ                           MAC_PPS_CONTROL_PPSCTRL_PPSCMD(4)                          /*!< PPS output 16Hz frequency */
#define ENET_PPSOFC_32HZ                           MAC_PPS_CONTROL_PPSCTRL_PPSCMD(5)                          /*!< PPS output 32Hz frequency */
#define ENET_PPSOFC_64HZ                           MAC_PPS_CONTROL_PPSCTRL_PPSCMD(6)                          /*!< PPS output 64Hz frequency */
#define ENET_PPSOFC_128HZ                          MAC_PPS_CONTROL_PPSCTRL_PPSCMD(7)                          /*!< PPS output 128Hz frequency */
#define ENET_PPSOFC_256HZ                          MAC_PPS_CONTROL_PPSCTRL_PPSCMD(8)                          /*!< PPS output 256Hz frequency */
#define ENET_PPSOFC_512HZ                          MAC_PPS_CONTROL_PPSCTRL_PPSCMD(9)                          /*!< PPS output 512Hz frequency */
#define ENET_PPSOFC_1024HZ                         MAC_PPS_CONTROL_PPSCTRL_PPSCMD(10)                         /*!< PPS output 1024Hz frequency */
#define ENET_PPSOFC_2048HZ                         MAC_PPS_CONTROL_PPSCTRL_PPSCMD(11)                         /*!< PPS output 2048Hz frequency */
#define ENET_PPSOFC_4096HZ                         MAC_PPS_CONTROL_PPSCTRL_PPSCMD(12)                         /*!< PPS output 4096Hz frequency */
#define ENET_PPSOFC_8192HZ                         MAC_PPS_CONTROL_PPSCTRL_PPSCMD(13)                         /*!< PPS output 8192Hz frequency */
#define ENET_PPSOFC_16384HZ                        MAC_PPS_CONTROL_PPSCTRL_PPSCMD(14)                         /*!< PPS output 16384Hz frequency */
#define ENET_PPSOFC_32768HZ                        MAC_PPS_CONTROL_PPSCTRL_PPSCMD(15)                         /*!< PPS output 32768Hz frequency */

#define ENET_FLEXIBLE_PPS0_START_SINGLE_PULSE       MAC_PPS_CONTROL_PPSCTRL_PPSCMD(1)                          /*!< generates single pulse rising at the start point */
#define ENET_FLEXIBLE_PPS0_START_PULSE_TRAIN        MAC_PPS_CONTROL_PPSCTRL_PPSCMD(2)                          /*!< generates the train of pulses rising at the start point */
#define ENET_FLEXIBLE_PPS0_CANCEL_START             MAC_PPS_CONTROL_PPSCTRL_PPSCMD(3)                          /*!< cancels the start single pulse and start pulse train commands */
#define ENET_FLEXIBLE_PPS0_STOP_PULSE_TRAIN_AT_TIME MAC_PPS_CONTROL_PPSCTRL_PPSCMD(4)                          /*!< stops the train of pulses after the time programmed in the Target Time registers elapses */
#define ENET_FLEXIBLE_PPS0_STOP_PULSE_TRAIN_NOW     MAC_PPS_CONTROL_PPSCTRL_PPSCMD(5)                          /*!< immediately stops the train of pulses  */
#define ENET_FLEXIBLE_PPS0_CANCEL_STOP_PULSE_TRAIN  MAC_PPS_CONTROL_PPSCTRL_PPSCMD(6)                          /*!< cancels the stop pulse train at time command if the programmed stop time has not elapsed */

#define ENET_MCGR0_OPERATION_NONE                   MAC_PPS_CONTROL_PPSCTRL_PPSCMD(0)                          /*!< MCGR operation is not carried out */
#define ENET_MCGR0_CAPTURE_RISING                   MAC_PPS_CONTROL_PPSCTRL_PPSCMD(1)                          /*!< capture the presentation time at the rising edge */
#define ENET_MCGR0_CAPTURE_FALLING                  MAC_PPS_CONTROL_PPSCTRL_PPSCMD(2)                          /*!< capture the presentation time at the falling edge */
#define ENET_MCGR0_CAPTURE_BOTH                     MAC_PPS_CONTROL_PPSCTRL_PPSCMD(3)                          /*!< capture the presentation time at both edges */
#define ENET_MCGR0_OUTPUT_TOGGLE                    MAC_PPS_CONTROL_PPSCTRL_PPSCMD(9)                          /*!< toggle output on compare */
#define ENET_MCGR0_OUTPUT_LOW                       MAC_PPS_CONTROL_PPSCTRL_PPSCMD(10)                         /*!< pulse output low on compare for one PTP-clock cycle */
#define ENET_MCGR0_OUTPUT_HIGH                      MAC_PPS_CONTROL_PPSCTRL_PPSCMD(11)                         /*!< pulse output high on compare for one PTP-clock cycle */

#define MAC_PPS_CONTROL_TRGTMODSEL0(regval)       (BITS(5,6) & ((uint32_t)(regval) << 5))                     /*!< write value to ENET_MAC_PPS_CONTROL_TRGTMODSEL0 bit field */
#define ENET_PPS0_GENERATE_INT_ONLY               MAC_PPS_CONTROL_TRGTMODSEL0(0)                              /*!< target time registers are programmed only for generating the interrupt event */
#define ENET_PPS0_MCGR_INT_ENBALE                 MAC_PPS_CONTROL_TRGTMODSEL0(1)                              /*!< enables MCGR interrupt */
#define ENET_PPS0_GENERATE_INT_AND_OUTPUT         MAC_PPS_CONTROL_TRGTMODSEL0(2)                              /*!< target time registers are programmed for generating the interrupt event and starting or stopping the PPS output signal generation */
#define ENET_PPS0_GENERATE_OUTPUT_ONLY            MAC_PPS_CONTROL_TRGTMODSEL0(3)                              /*!< target time registers are programmed only for starting or stopping the PPS output signal generation */

#define MAC_PPS_CONTROL_PPSCMD1(regval)              (BITS(8,11) & ((uint32_t)(regval) << 8))                    /*!< write value to ENET_MAC_PPS_CONTROL_PPSCMD1 bit field */

#define ENET_FLEXIBLE_PPS1_START_SINGLE_PULSE         MAC_PPS_CONTROL_PPSCMD1(1)                              /*!< generates single pulse rising at the start point */
#define ENET_FLEXIBLE_PPS1_START_PULSE_TRAIN          MAC_PPS_CONTROL_PPSCMD1(2)                              /*!< generates the train of pulses rising at the start point */
#define ENET_FLEXIBLE_PPS1_CANCEL_START               MAC_PPS_CONTROL_PPSCMD1(3)                              /*!< cancels the start single pulse and start pulse train commands */
#define ENET_FLEXIBLE_PPS1_STOP_PULSE_TRAIN_AT_TIME   MAC_PPS_CONTROL_PPSCMD1(4)                              /*!< stops the train of pulses after the time programmed in the Target Time registers elapses */
#define ENET_FLEXIBLE_PPS1_STOP_PULSE_TRAIN_NOW       MAC_PPS_CONTROL_PPSCMD1(5)                              /*!< immediately stops the train of pulses  */
#define ENET_FLEXIBLE_PPS1_CANCEL_STOP_PULSE_TRAIN    MAC_PPS_CONTROL_PPSCMD1(6)                              /*!< cancels the stop pulse train at time command if the programmed stop time has not elapsed */

#define ENET_MCGR1_OPERATION_NONE                     MAC_PPS_CONTROL_PPSCMD1(0)                              /*!< MCGR operation is not carried out */
#define ENET_MCGR1_CAPTURE_RISING                     MAC_PPS_CONTROL_PPSCMD1(1)                             /*!< capture the presentation time at the rising edge */
#define ENET_MCGR1_CAPTURE_FALLING                    MAC_PPS_CONTROL_PPSCMD1(2)                              /*!< capture the presentation time at the falling edge */
#define ENET_MCGR1_CAPTURE_BOTH                       MAC_PPS_CONTROL_PPSCMD1(3)                              /*!< capture the presentation time at both edges */
#define ENET_MCGR1_OUTPUT_TOGGLE                      MAC_PPS_CONTROL_PPSCMD1(9)                             /*!< toggle output on compare */
#define ENET_MCGR1_OUTPUT_LOW                         MAC_PPS_CONTROL_PPSCMD1(10)                             /*!< pulse output low on compare for one PTP-clock cycle */
#define ENET_MCGR1_OUTPUT_HIGH                        MAC_PPS_CONTROL_PPSCMD1(11)                             /*!< pulse output high on compare for one PTP-clock cycle */

#define MAC_PPS_CONTROL_TRGTMODSEL1(regval)           (BITS(13,14) & ((uint32_t)(regval) << 13))                 /*!< write value to ENET_MAC_PPS_CONTROL_TRGTMODSEL1 bit field */
#define ENET_PPS1_GENERATE_INT_ONLY                   MAC_PPS_CONTROL_TRGTMODSEL1(0)                          /*!< target time registers are programmed only for generating the interrupt event */
#define ENET_PPS1_MCGR_INT_ENBALE                     MAC_PPS_CONTROL_TRGTMODSEL1(1)                          /*!< enables MCGR interrupt */
#define ENET_PPS1_GENERATE_INT_AND_OUTPUT             MAC_PPS_CONTROL_TRGTMODSEL1(2)                          /*!< target time registers are programmed for generating the interrupt event and starting or stopping the PPS output signal generation */
#define ENET_PPS1_GENERATE_OUTPUT_ONLY                MAC_PPS_CONTROL_TRGTMODSEL1(3)                          /*!< target time registers are programmed only for starting or stopping the PPS output signal generation */

#define MAC_PPS_CONTROL_PPSCMD2(regval)              (BITS(16,19) & ((uint32_t)(regval) << 16))               /*!< write value to ENET_MAC_PPS_CONTROL_PPSCMD2 bit field */

#define ENET_FLEXIBLE_PPS2_START_SINGLE_PULSE         MAC_PPS_CONTROL_PPSCMD2(1)                              /*!< generates single pulse rising at the start point */
#define ENET_FLEXIBLE_PPS2_START_PULSE_TRAIN          MAC_PPS_CONTROL_PPSCMD2(2)                              /*!< generates the train of pulses rising at the start point */
#define ENET_FLEXIBLE_PPS2_CANCEL_START               MAC_PPS_CONTROL_PPSCMD2(3)                              /*!< cancels the start single pulse and start pulse train commands */
#define ENET_FLEXIBLE_PPS2_STOP_PULSE_TRAIN_AT_TIME   MAC_PPS_CONTROL_PPSCMD2(4)                              /*!< stops the train of pulses after the time programmed in the Target Time registers elapses */
#define ENET_FLEXIBLE_PPS2_STOP_PULSE_TRAIN_NOW       MAC_PPS_CONTROL_PPSCMD2(5)                              /*!< immediately stops the train of pulses  */
#define ENET_FLEXIBLE_PPS2_CANCEL_STOP_PULSE_TRAIN    MAC_PPS_CONTROL_PPSCMD2(6)                              /*!< cancels the stop pulse train at time command if the programmed stop time has not elapsed */

#define ENET_MCGR2_OPERATION_NONE                     MAC_PPS_CONTROL_PPSCMD2(0)                              /*!< MCGR operation is not carried out */
#define ENET_MCGR2_CAPTURE_RISING                     MAC_PPS_CONTROL_PPSCMD2(1)                              /*!< capture the presentation time at the rising edge */
#define ENET_MCGR2_CAPTURE_FALLING                    MAC_PPS_CONTROL_PPSCMD2(2)                              /*!< capture the presentation time at the falling edge */
#define ENET_MCGR2_CAPTURE_BOTH                       MAC_PPS_CONTROL_PPSCMD2(3)                              /*!< capture the presentation time at both edges */
#define ENET_MCGR2_OUTPUT_TOGGLE                      MAC_PPS_CONTROL_PPSCMD2(9)                              /*!< toggle output on compare */
#define ENET_MCGR2_OUTPUT_LOW                         MAC_PPS_CONTROL_PPSCMD2(10)                             /*!< pulse output low on compare for one PTP-clock cycle */
#define ENET_MCGR2_OUTPUT_HIGH                        MAC_PPS_CONTROL_PPSCMD2(11)                             /*!< pulse output high on compare for one PTP-clock cycle */

#define MAC_PPS_CONTROL_TRGTMODSEL2(regval)           (BITS(21,22) & ((uint32_t)(regval) << 21))              /*!< write value to ENET_MAC_PPS_CONTROL_TRGTMODSEL2 bit field */
#define ENET_PPS2_GENERATE_INT_ONLY                   MAC_PPS_CONTROL_TRGTMODSEL2(0)                          /*!< target time registers are programmed only for generating the interrupt event */
#define ENET_PPS2_MCGR_INT_ENBALE                     MAC_PPS_CONTROL_TRGTMODSEL2(1)                          /*!< enables MCGR interrupt */
#define ENET_PPS2_GENERATE_INT_AND_OUTPUT             MAC_PPS_CONTROL_TRGTMODSEL2(2)                          /*!< target time registers are programmed for generating the interrupt event and starting or stopping the PPS output signal generation */
#define ENET_PPS2_GENERATE_OUTPUT_ONLY                MAC_PPS_CONTROL_TRGTMODSEL2(3)                          /*!< target time registers are programmed only for starting or stopping the PPS output signal generation */

#define MAC_PPS_CONTROL_PPSCMD3(regval)              (BITS(24,27) & ((uint32_t)(regval) << 24))               /*!< write value to ENET_MAC_PPS_CONTROL_PPSCMD3 bit field */

#define ENET_FLEXIBLE_PPS3_START_SINGLE_PULSE         MAC_PPS_CONTROL_PPSCMD3(1)                              /*!< generates single pulse rising at the start point */
#define ENET_FLEXIBLE_PPS3_START_PULSE_TRAIN          MAC_PPS_CONTROL_PPSCMD3(2)                              /*!< generates the train of pulses rising at the start point */
#define ENET_FLEXIBLE_PPS3_CANCEL_START               MAC_PPS_CONTROL_PPSCMD3(3)                              /*!< cancels the start single pulse and start pulse train commands */
#define ENET_FLEXIBLE_PPS3_STOP_PULSE_TRAIN_AT_TIME   MAC_PPS_CONTROL_PPSCMD3(4)                              /*!< stops the train of pulses after the time programmed in the Target Time registers elapses */
#define ENET_FLEXIBLE_PPS3_STOP_PULSE_TRAIN_NOW       MAC_PPS_CONTROL_PPSCMD3(5)                              /*!< immediately stops the train of pulses  */
#define ENET_FLEXIBLE_PPS3_CANCEL_STOP_PULSE_TRAIN    MAC_PPS_CONTROL_PPSCMD3(6)                              /*!< cancels the stop pulse train at time command if the programmed stop time has not elapsed */

#define ENET_MCGR3_OPERATION_NONE                     MAC_PPS_CONTROL_PPSCMD3(0)                              /*!< MCGR operation is not carried out */
#define ENET_MCGR3_CAPTURE_RISING                     MAC_PPS_CONTROL_PPSCMD3(1)                             /*!< capture the presentation time at the rising edge */
#define ENET_MCGR3_CAPTURE_FALLING                    MAC_PPS_CONTROL_PPSCMD3(2)                              /*!< capture the presentation time at the falling edge */
#define ENET_MCGR3_CAPTURE_BOTH                       MAC_PPS_CONTROL_PPSCMD3(3)                              /*!< capture the presentation time at both edges */
#define ENET_MCGR3_OUTPUT_TOGGLE                      MAC_PPS_CONTROL_PPSCMD3(9)                             /*!< toggle output on compare */
#define ENET_MCGR3_OUTPUT_LOW                         MAC_PPS_CONTROL_PPSCMD3(10)                             /*!< pulse output low on compare for one PTP-clock cycle */
#define ENET_MCGR3_OUTPUT_HIGH                        MAC_PPS_CONTROL_PPSCMD3(11)                             /*!< pulse output high on compare for one PTP-clock cycle */

#define MAC_PPS_CONTROL_TRGTMODSEL3(regval)           (BITS(29,30) & ((uint32_t)(regval) << 29))              /*!< write value to ENET_MAC_PPS_CONTROL_TRGTMODSEL3 bit field */
#define ENET_PPS3_GENERATE_INT_ONLY                   MAC_PPS_CONTROL_TRGTMODSEL3(0)                          /*!< target time registers are programmed only for generating the interrupt event */
#define ENET_PPS3_MCGR_INT_ENBALE                     MAC_PPS_CONTROL_TRGTMODSEL3(1)                          /*!< enables MCGR interrupt */
#define ENET_PPS3_GENERATE_INT_AND_OUTPUT             MAC_PPS_CONTROL_TRGTMODSEL3(2)                          /*!< target time registers are programmed for generating the interrupt event and starting or stopping the PPS output signal generation */
#define ENET_PPS3_GENERATE_OUTPUT_ONLY                MAC_PPS_CONTROL_TRGTMODSEL3(3)                          /*!< target time registers are programmed only for starting or stopping the PPS output signal generation */

#define ENET_FLEXIBLE_PPS_OUTPUT_MODE                 ENET_MAC_PPS_CONTROL_PPSEN0                             /*!< flexible PPS output mode */
#define ENET_PPS_OUTPUT_MODE                          ((uint32_t)0x00000000)                                  /*!< PPS output mode */
#define ENET_PPS0_MCGR_MODE                           ENET_MAC_PPS_CONTROL_MCGREN0                            /*!< 0th PPS instance is enabled to operate in MCGR mode */
#define ENET_PPS0_NORMAL_MODE                         ((uint32_t)0x00000000)                                  /*!< 0th PPS instance is enabled to operate in PPS mode */
#define ENET_PPS1_MCGR_MODE                           ENET_MAC_PPS_CONTROL_MCGREN1                            /*!< 1th PPS instance is enabled to operate in MCGR mode */
#define ENET_PPS1_NORMAL_MODE                         ((uint32_t)0x00000000)                                  /*!< 1th PPS instance is enabled to operate in PPS mode */
#define ENET_PPS2_MCGR_MODE                           ENET_MAC_PPS_CONTROL_MCGREN2                            /*!< 2th PPS instance is enabled to operate in MCGR mode */
#define ENET_PPS2_NORMAL_MODE                         ((uint32_t)0x00000000)                                  /*!< 2th PPS instance is enabled to operate in PPS mode */
#define ENET_PPS3_MCGR_MODE                           ENET_MAC_PPS_CONTROL_MCGREN3                            /*!< 3th PPS instance is enabled to operate in MCGR mode */
#define ENET_PPS3_NORMAL_MODE                         ((uint32_t)0x00000000)                                  /*!< 3th PPS instance is enabled to operate in PPS mode */
#define ENET_MCGR_CAPTURE_PTP_TIME                    ENET_MAC_PPS_CONTROL_TIMESEL                            /*!< 64 bit PTP time is used to capture time at MCGR trigger[0] input */
#define ENET_MCGR_CAPTURE_PRESENTATION_TIME           ((uint32_t)0x00000000)                                  /*!< presentation time is used to capture time at trigger input, maintaining backward compatibility */

/* MAC PPS target time in nanoseconds register value */
#define MAC_PPS_TARGET_TIME_NANOSECONDS_TTSL0(regval) (BITS(0,30) & ((uint32_t)(regval) << 0))                 /*!< write value to ENET_MAC_PPS_TARGET_TIME_NANOSECONDS_TTSL0 bit field */

#define ENET_PPS_TARGET_TIME_REG_BUSY                 ENET_MAC_PPS_TARGET_TIME_NANOSECONDS_TRGTBUSY0           /*!< PPS Target Time Register Busy is detected */

/* MTL operation mode register value */
#define MTL_OPERATION_MODE_SCHALG(regval)             (BITS(5,6) & ((uint32_t)(regval) << 5))                 /*!< write value to ENET_MTL_OPERATION_MODE_SCHALG bit field */
#define ENET_TX_SCHEDULING_ALGO_WRR                    MTL_OPERATION_MODE_SCHALG(0)                           /*!< WRR algorithm */
#define ENET_TX_SCHEDULING_ALGO_SP                     MTL_OPERATION_MODE_SCHALG(3)                           /*!< Strict priority algorithm */

#define MTL_OPERATION_MODE_RAA(regval)                (BIT(2) & ((uint32_t)(regval) << 2))                    /*!< write value to MTL_OPERATION_MODE_RAA bit field */

#define ENET_TX_STATUS_DROP                           ENET_MTL_OPERATION_MODE_DTXSTS                          /*!< Tx packet status received from the MAC is dropped in the MTL */
#define ENET_TX_STATUS_FORWARD                        ((uint32_t)0x00000000)                                  /*!< Tx packet status received from the MAC is forwarded to the application */
#define ENET_RXQ_ARBITRATION_WSP                      ENET_MTL_OPERATION_MODE_RAA                             /*!< weighted strict priority */
#define ENET_RXQ_ARBITRATION_SP                       ((uint32_t)0x00000000)                                  /*!< strict priority. Queue 0 has the lowest priority and the last queue has the highest priority */
#define ENET_MTL_COUNTER_PRESET                       ENET_MTL_OPERATION_MODE_CNTPRST                         /*!< counters Preset is enabled */
#define ENET_MTL_COUNTER_RESET                        ENET_MTL_OPERATION_MODE_CNTCLR                          /*!< all counters are reset */
#define ENET_RX_PARSE_ERR_DROP                        ENET_MTL_OPERATION_MODE_RXPED                           /*!< flexible Rx parser, packet drop in case software error is enabled */
#define ENET_RX_PARSER_ENABLE                         ENET_MTL_OPERATION_MODE_FRPE                            /*!< flexible Rx parser is enabled */
#define ENET_RX_PARSER_DISABLE                        ((uint32_t)0x00000000)                                  /*!< flexible Rx parser is disabled */

/* MTL debug control register value */
#define MTL_DBG_CTL_BYTEEN(regval)                   (BITS(2,3) & ((uint32_t)(regval) << 2))                 /*!< write value to ENET_MTL_DBG_CTL_BYTEEN bit field */
#define ENET_BYTE0_VALID                             MTL_DBG_CTL_BYTEEN(0)                                   /*!< byte 0 valid */
#define ENET_BYTE0_BYTE1_VALID                       MTL_DBG_CTL_BYTEEN(1)                                   /*!< byte 0 valid */
#define ENET_BYTE0_BYTE1_BYTE2_VALID                 MTL_DBG_CTL_BYTEEN(2)                                   /*!< byte 0, byte 1, and byte 2 are valid */
#define ENET_ALL_FOUR_BYTES_VALID                    MTL_DBG_CTL_BYTEEN(3)                                   /*!< all four bytes are valid */

#define MTL_DBG_CTL_PKTSTATE(regval)                 (BITS(5,6) & ((uint32_t)(regval) << 5))                 /*!< write value to ENET_MTL_DBG_CTL_PKTSTATE bit field */
#define ENET_WRITE_PACKET_DATA_TO_TXFIFO             MTL_DBG_CTL_PKTSTATE(0)                                 /*!< write the packet data to the Tx FIFO */
#define ENET_WRITE_CONTROL_WORD_TO_TXFIFO            MTL_DBG_CTL_PKTSTATE(1)                                 /*!< write the control word to the Tx FIFO */
#define ENET_WRITE_SOP_DATA_TO_TXFIFO                MTL_DBG_CTL_PKTSTATE(2)                                 /*!< write the SOP data to the Tx FIFO */
#define ENET_WRITE_EOP_DATA_TO_TXFIFO                MTL_DBG_CTL_PKTSTATE(3)                                 /*!< write the EOP data to the Tx FIFO */
#define ENET_WRITE_PACKET_DATA_TO_RXFIFO             MTL_DBG_CTL_PKTSTATE(0)                                 /*!< write the packet data to the Rx FIFO */
#define ENET_WRITE_NORMAL_WORD_TO_RXFIFO             MTL_DBG_CTL_PKTSTATE(1)                                 /*!< write the normal status to the Rx FIFO */
#define ENET_WRITE_LAST_STATUS_TO_RXFIFO             MTL_DBG_CTL_PKTSTATE(2)                                 /*!< write the last status to the Rx FIFO */
#define ENET_WRITE_EOP_DATA_TO_RXFIFO                MTL_DBG_CTL_PKTSTATE(3)                                 /*!< write the EOP data to the Rx FIFO */

#define MTL_DBG_CTL_FIFOSEL(regval)                  (BITS(12,13) & ((uint32_t)(regval) << 12))              /*!< write value to ENET_MTL_DBG_CTL_FIFOSEL bit field */
#define ENET_DBG_ACCESS_TXFIFO                       MTL_DBG_CTL_FIFOSEL(0)                                  /*!< the Tx FIFO selected for debug access */
#define ENET_DBG_ACCESS_TXSTATUSFIFO                 MTL_DBG_CTL_FIFOSEL(1)                                  /*!< the Tx Status FIFO selected for debug access */
#define ENET_DBG_ACCESS_RXFIFO                       MTL_DBG_CTL_FIFOSEL(3)                                  /*!< the Rx FIFO selected for debug access */

#define ENET_FIFO_DBG_ACCESS_ENABLE                  ENET_MTL_DBG_CTL_FDBGEN                                 /*!< FIFO debug access is enabled */
#define ENET_FIFO_DBG_ACCESS_DISABLE                 ((uint32_t)0x00000000)                                  /*!< FIFO debug access is disabled */
#define ENET_DBG_NORMAL_ACCESS_FIFO                  ENET_MTL_DBG_CTL_DBGMOD                                 /*!< indicates that the current access to the FIFO is read, write, and debug access */
#define ENET_DBG_SLAVE_ACCESS_FIFO                   ((uint32_t)0x00000000)                                  /*!< indicates that the current access to the FIFO is slave access bypassing the DMA */
#define ENET_DBG_ALL_POINTERS_RESET                  ENET_MTL_DBG_CTL_RSTALL                                 /*!< the pointers of all FIFOs are reset when FIFO Debug Access is enabled */
#define ENET_DBG_SELECTED_POINTERS_RESET             ENET_MTL_DBG_CTL_RSTSEL                                 /*!< the pointers of the currently-selected FIFO are reset when FIFO debug access is enabled */
#define ENET_DBG_FIFO_READ                           ENET_MTL_DBG_CTL_FIFORDEN                               /*!< it enables the read operation on selected FIFO when FIFO debug access is enabled */
#define ENET_DBG_FIFO_WRITE                          ENET_MTL_DBG_CTL_FIFOWREN                               /*!< it enables the write operation on selected FIFO when FIFO debug access is enabled */
#define ENET_MTL_INSERT_ECC_ERR_1BIT                 ENET_MTL_DBG_CTL_EIEE                                   /*!< ECC inject 1-bit error for Tx, Rx memories */
#define ENET_MTL_INSERT_ECC_ERR_2BIT                 ENET_MTL_DBG_CTL_EIEE | ENET_MTL_DBG_CTL_EIEC           /*!< ECC inject 2-bit error for Tx, Rx memories */
#define ENET_MTL_INSERT_ECC_ADDR_ERR_1BIT            ENET_MTL_DBG_CTL_EIAEE                                  /*!< ECC inject 1-bit address error for Tx, Rx memories */
#define ENET_MTL_INSERT_ECC_ADDR_ERR_2BIT            ENET_MTL_DBG_CTL_EIAEE | ENET_MTL_DBG_CTL_EIEC          /*!< ECC inject 2-bit address error for Tx, Rx memories */

/* MTL receive queue and DMA channel mapping 0 register value */
#define ENET_RXQ0_MAPPED_TO_DMACH1                   ENET_MTL_RXQ_DMA_MAP0_Q0MDMACH                          /*!< the routing of the packet received in Queue 0 to the DMA channel 1 */
#define ENET_RXQ0_MAPPED_TO_DMACH0                   ((uint32_t)0x00000000)                                  /*!< the routing of the packet received in Queue 0 to the DMA channel 0 */
#define ENET_RXQ0_DMACHSEL_BASED_DA                  ENET_MTL_RXQ_DMA_MAP0_Q0DDMACH                          /*!< queue 0 enabled for DA-based DMA channel selection */
#define ENET_RXQ1_MAPPED_TO_DMACH1                   ENET_MTL_RXQ_DMA_MAP0_Q1MDMACH                          /*!< the routing of the packet received in Queue 1 to the DMA channel 1 */
#define ENET_RXQ1_MAPPED_TO_DMACH0                   ((uint32_t)0x00000000)                                  /*!< the routing of the packet received in Queue 1 to the DMA channel 0 */
#define ENET_RXQ1_DMACHSEL_BASED_DA                  ENET_MTL_RXQ_DMA_MAP0_Q1DDMACH                          /*!< queue 1 enabled for DA-based DMA channel selection */

/* MTL TBS control register value */
#define MTL_TBS_CTRL_LEGOS(regval)                   (BITS(4,6) & ((uint32_t)(regval) << 4))                 /*!< write value to ENET_MTL_TBS_CTRL_LEGOS bit field */

#define MTL_TBS_CTRL_LEOS(regval)                    (BITS(8,31) & ((uint32_t)(regval) << 8))                /*!< write value to ENET_MTL_TBS_CTRL_LEOS bit field */

#define MTL_TBS_CTRL_ESTM(regval)                    (BIT(0) & ((uint32_t)(regval) << 0))                    /*!< write value to ENET_MTL_TBS_CTRL_ESTM bit field */

#define ENET_TBS_NORMAL_ABSOLUTE_MODE                MTL_TBS_CTRL_ESTM(1)                                    /*!< the launch time value used in time based scheduling is interpreted as an EST offset value */
#define ENET_TBS_EST_OFFSET_MODE                     MTL_TBS_CTRL_ESTM(0)                                    /*!< the launch time value is used as an absolute value */
#define ENET_TBS_LAUNCH_EXPIRY_OFFSET_VALID          ENET_MTL_TBS_CTRL_LEOV                                  /*!< the LEOS field is valid */

/* MTL EST control register value */
#define MTL_EST_CONTROL_LCSE(regval)                 (BITS(6,7) & ((uint32_t)(regval) << 6))                 /*!< write value to ENET_MTL_EST_CONTROL_LCSE bit field */
#define ENET_GCL_INTERATE_4                          MTL_EST_CONTROL_LCSE(0)                                 /*!< 4 of GCL list iterations before reporting an HLBS error */
#define ENET_GCL_INTERATE_8                          MTL_EST_CONTROL_LCSE(1)                                 /*!< 8 of GCL list iterations before reporting an HLBS error */
#define ENET_GCL_INTERATE_16                         MTL_EST_CONTROL_LCSE(2)                                 /*!< 16 of GCL list iterations before reporting an HLBS error */
#define ENET_GCL_INTERATE_32                         MTL_EST_CONTROL_LCSE(3)                                 /*!< 32 of GCL list iterations before reporting an HLBS error */

#define MTL_EST_CONTROL_TILS(regval)                 (BITS(8,10) & ((uint32_t)(regval) << 8))                /*!< write value to ENET_MTL_EST_CONTROL_TILS bit field */
#define ENET_GCL_TIME_INTERVAL_LEFT_SHIFT_0          MTL_EST_CONTROL_TILS(0)                                 /*!< left shift 0 for the programmed Time Interval values */
#define ENET_GCL_TIME_INTERVAL_LEFT_SHIFT_1          MTL_EST_CONTROL_TILS(1)                                 /*!< left shift 1 for the programmed Time Interval values */
#define ENET_GCL_TIME_INTERVAL_LEFT_SHIFT_2          MTL_EST_CONTROL_TILS(2)                                 /*!< left shift 2 for the programmed Time Interval values */
#define ENET_GCL_TIME_INTERVAL_LEFT_SHIFT_7          MTL_EST_CONTROL_TILS(4)                                 /*!< left shift 7 for the programmed Time Interval values */

#define MTL_EST_CONTROL_CTOV(regval)                 (BITS(12,23) & ((uint32_t)(regval) << 12))              /*!< write value to ENET_MTL_EST_CONTROL_CTOV bit field */

#define MTL_EST_CONTROL_PTOV(regval)                 (BITS(24,31) & ((uint32_t)(regval) << 24))              /*!< write value to ENET_MTL_EST_CONTROL_PTOV bit field */

#define ENET_EST_ENABLE                              ENET_MTL_EST_CONTROL_EEST                               /*!< EST is enabled */
#define ENET_EST_DISABLE                             ((uint32_t)0x00000000)                                  /*!< EST is disabled */
#define ENET_OWNED_GCL_LIST_SWITCH                   ENET_MTL_EST_CONTROL_SSWL                               /*!< the software has programmed that list that it currently owns */
#define ENET_QUICK_ASSERT_HLBF_ERR_ENABLE            ENET_MTL_EST_CONTROL_QHLBF                              /*!< time window for head-of-line blocking due to frame size error is 1 to 2 loop count of GCL list */
#define ENET_QUICK_ASSERT_HLBF_ERR_DISABLE          ((uint32_t)0x00000000)                                   /*!< time window for head-of-line blocking due to frame size error is 2 to 3 loop count of GCL list */
#define ENET_EST_DONT_DROP_SIZE_ERR_FRAME            ENET_MTL_EST_CONTROL_DDBF                               /*!< frames are not being dropped during Head-of-Line blocking due to Frame Size Error */
#define ENET_EST_DROP_SIZE_ERR_FRAME                 ((uint32_t)0x00000000)                                  /*!< frames are dropped during Head-of-Line blocking due to Frame Size Error */
#define ENET_EST_DROP_SCHEDULING_ERR_FRAME           ENET_MTL_EST_CONTROL_DFBS                               /*!< drop frames causing scheduling error */
#define ENET_EST_DONT_DROP_SCHEDULING_ERR_FRAME     ((uint32_t)0x00000000)                                   /*!< drop frames causing scheduling error */

/* MTL EST extend control register value */
#define MTL_EST_EXT_CONTROL_OVHD(regval)             (BITS(0,5) & ((uint32_t)(regval) << 0))                 /*!< write value to ENET_MTL_EST_EXT_CONTROL_OVHD bit field */

/* MTL EST status register value */
#define GET_CURRENT_GCL_NUM(regval)                        GET_BITS((uint32_t)(regval),16,19)                      /*!< get value of ENET_MTL_EST_STATUS_CGSN bit field */
#define GET_BTR_ERROR_LOOP_COUNT(regval)                   GET_BITS((uint32_t)(regval),8,15)                      /*!< get value of ENET_MTL_EST_STATUS_BTRL bit field */

/* MTL EST schedule error register value */
#define MTL_EST_SCH_ERROR_SEQN(regval)               (BITS(0,1) & ((uint32_t)(regval) << 0))                 /*!< write value to ENET_MTL_EST_SCH_ERROR_SEQN bit field */
#define ENET_EST_SCHEDULE_ERR_Q0                     MTL_EST_SCH_ERROR_SEQN(1)                               /*!< queue 0 that have experienced error/timeout */
#define ENET_EST_SCHEDULE_ERR_Q1                     MTL_EST_SCH_ERROR_SEQN(2)                               /*!< queue 1 that have experienced error/timeou */

/* MTL EST frame size error register value */
#define MTL_EST_FRM_SIZE_ERROR_FEQN(regval)          (BITS(0,1) & ((uint32_t)(regval) << 0))                 /*!< write value to ENET_MTL_EST_FRM_SIZE_ERROR_FEQN bit field */
#define ENET_EST_FRAME_SIZE_ERR_Q0                    MTL_EST_FRM_SIZE_ERROR_FEQN(1)                         /*!< queue 0 that have experienced frame size error */
#define ENET_EST_FRAME_SIZE_ERR_Q1                    MTL_EST_FRM_SIZE_ERROR_FEQN(2)                         /*!< queue 1 that have experienced frame size error */

/* MTL EST frame size capture register value */
#define GET_HLBF_FRAME_SIZE(regval)                   GET_BITS((uint32_t)(regval),0,14)                      /*!< get value of ENET_MTL_EST_FRM_SIZE_CAPTURE_HBFS bit field */

#define ENET_Q0_FISRT_EXPERIENCING_HLBF               ((uint32_t)0x00000000)                                 /*!< queue 0 first experiencing HLBF error */
#define ENET_Q1_FISRT_EXPERIENCING_HLBF               ENET_MTL_EST_CONTROL_HBFQ                              /*!< queue 1 first experiencing HLBF error */

/* MTL EST GCL control register value */
#define MTL_EST_GCL_CONTROL_ADDR(regval)              (BITS(8,15) & ((uint32_t)(regval) << 8))                     /*!< write value to ENET_MTL_EST_GCL_CONTROL_ADDR bit field */
#define ENET_GCL_BTR_LOW                              MTL_EST_GCL_CONTROL_ADDR(0) | ENET_MTL_EST_GCL_CONTROL_GCRR  /*!< BTR low (31:0) */
#define ENET_GCL_BTR_HIGH                             MTL_EST_GCL_CONTROL_ADDR(1) | ENET_MTL_EST_GCL_CONTROL_GCRR  /*!< BTR high (63:31) */
#define ENET_GCL_CTR_LOW                              MTL_EST_GCL_CONTROL_ADDR(2) | ENET_MTL_EST_GCL_CONTROL_GCRR  /*!< CTR low (31:0) */
#define ENET_GCL_CTR_HIGH                             MTL_EST_GCL_CONTROL_ADDR(3) | ENET_MTL_EST_GCL_CONTROL_GCRR  /*!< CTR high (39:32) */
#define ENET_GCL_TER                                  MTL_EST_GCL_CONTROL_ADDR(4) | ENET_MTL_EST_GCL_CONTROL_GCRR  /*!< TER (22:0)(26:0)(30:0) */
#define ENET_GCL_LLR                                  MTL_EST_GCL_CONTROL_ADDR(5) | ENET_MTL_EST_GCL_CONTROL_GCRR  /*!< LLR (5:0)(6:0)(7:0)(8:0)(9:0) */

#define ENET_GCL_READ_WRITE_START                     ENET_MTL_EST_GCL_CONTROL_SRWO                                /*!< the start / progress of a read / write operation */
#define ENET_GCL_READ                                 ENET_MTL_EST_GCL_CONTROL_R1W0                                /*!< read operation */
#define ENET_GCL_WRITE                                ((uint32_t)0x00000000)                                       /*!< write operation */
#define ENET_GCL_DBG_MODE_ENABLE                      ENET_MTL_EST_GCL_CONTROL_DBGM                                /*!< debug mode is enabled */
#define ENET_GCL_DBG_MODE_DISABLE                     ((uint32_t)0x00000000)                                       /*!< debug mode is disabled */
#define ENET_GCL_DBG_MODE_BANK1                       ENET_MTL_EST_GCL_CONTROL_DBGB                                /*!< r / w in debug mode should be directed to Bank 1 */
#define ENET_GCL_DBG_MODE_BANK0                       ((uint32_t)0x00000000)                                       /*!< r / w in debug mode should be directed to Bank 0 */
#define ENET_EST_INSERT_ECC_ERR_1BIT                  ENET_MTL_EST_GCL_CONTROL_ESTEIEE                                        /*!< ECC inject 1-bit error for EST */
#define ENET_EST_INSERT_ECC_ERR_2BIT                  ENET_MTL_EST_GCL_CONTROL_ESTEIEE | ENET_MTL_EST_GCL_CONTROL_ESTEIEC     /*!< ECC inject 2-bit error for EST */
#define ENET_EST_INSERT_ECC_ADDR_ERR_1BIT             ENET_MTL_EST_GCL_CONTROL_ESTEIAEE                                       /*!< ECC inject 1-bit address error for EST */
#define ENET_EST_INSERT_ECC_ADDR_ERR_2BIT             ENET_MTL_EST_GCL_CONTROL_ESTEIAEE | ENET_MTL_EST_GCL_CONTROL_ESTEIEC    /*!< ECC inject 2-bit address error for EST */

/* MTL FPE control status register value */
#define MTL_FPE_CTRL_STS_AFSZ(regval)                (BITS(0,1) & ((uint32_t)(regval) << 0)) << 4U           /*!< write value to ENET_MTL_FPE_CTRL_STS_AFSZ bit field */
#define ENET_FPE_ADD_FRAG_SIZE_64B                    MTL_FPE_CTRL_STS_AFSZ(0)                               /*!< the minimum non-final fragment size is 64 bytes */
#define ENET_FPE_ADD_FRAG_SIZE_128B                   MTL_FPE_CTRL_STS_AFSZ(1)                               /*!< the minimum non-final fragment size is 128 bytes */
#define ENET_FPE_ADD_FRAG_SIZE_192B                   MTL_FPE_CTRL_STS_AFSZ(2)                               /*!< the minimum non-final fragment size is 192 bytes */
#define ENET_FPE_ADD_FRAG_SIZE_256B                   MTL_FPE_CTRL_STS_AFSZ(3)                               /*!< the minimum non-final fragment size is 256 bytes */

#define MTL_FPE_CTRL_STS_PEC(regval)                 (BITS(8,9) & ((uint32_t)(regval) << 8)) << 4U           /*!< write value to ENET_MTL_FPE_CTRL_STS_PEC bit field */
#define ENET_FPE_Q0_AS_PREEMPTABLE                   MTL_FPE_CTRL_STS_PEC(1)                                 /*!< the queue 0 must be classified as preemptable */
#define ENET_FPE_Q1_AS_PREEMPTABLE                   MTL_FPE_CTRL_STS_PEC(2)                                 /*!< the queue 1 must be classified as preemptable */

#define ENET_GCL_LEVEL_BASED_HOLD_TRANSITION_ENABLE         ENET_MTL_FPE_CTRL_STS_LBHT << 4U                 /*!< enable hold operation in second row of EST GCL if hold request is set in second GCL row for first loop of new GCL */
#define ENET_GCL_LEVEL_BASED_HOLD_TRANSITION_DISABLE        ((uint32_t)0x00000000)                           /*!< disable hold operation in second row of EST GCL if hold request is set in second GCL row for first loop of new GCL */

#define ENET_PMAC_HOLD_STATE                         ENET_MTL_FPE_CTRL_STS_HRS                               /*!< indicates a Set-and-Hold-MAC operation was last executed and the pMAC is in Hold State */
#define ENET_PMAC_RELEASE_STATE                      ((uint32_t)0x00000000)                                  /*!< indicates a Set-and-Hold-MAC operation was last executed and the pMAC is in Release State */

/* MTL FPE Advance register value */
#define GET_HOLD_ADVANCE(regval)                     GET_BITS((uint32_t)(regval),0,15)                      /*!< get value of ENET_MTL_FPE_ADVANCE_HADV bit field */
#define GET_RELEASE_ADVANCE(regval)                  GET_BITS((uint32_t)(regval),16,31)                     /*!< get value of ENET_MTL_FPE_ADVANCE_RADV bit field */

/* MTL FPE Advance register value */
#define MTL_HOLD_ADVANCE(regval)                    (BITS(0,15) & ((uint32_t)(regval) << 0))                      /*!< write value of ENET_MTL_FPE_ADVANCE_HADV bit field */
#define MTL_RELEASE_ADVANCE(regval)                 (BITS(16,31) & ((uint32_t)(regval) << 16))                     /*!< write value of ENET_MTL_FPE_ADVANCE_RADV bit field */

/* MTL Rx parser control status register value */
#define MTL_RXP_CONTROL_STATUS_NVE(regval)           (BITS(0,7) & ((uint32_t)(regval) << 0))                /*!< write value to ENET_MTL_RXP_CONTROL_STATUS_NVE bit field */

#define MTL_RXP_CONTROL_STATUS_NPE(regval)           (BITS(16,23) & ((uint32_t)(regval) << 16))             /*!< write value to ENET_MTL_RXP_CONTROL_STATUS_NPE bit field */

#define ENET_LAST_INSTRUCTION_IN_RXSTATUS            ENET_MTL_RXP_CONTROL_STATUS_ELIRS                      /*!< RDES2[31:16] indicates the index of the last instruction excecuted in Rx Parse */
#define ENET_RXPARSER_IN_IDLE_STATE                  ENET_MTL_RXP_CONTROL_STATUS_RXPI                       /*!< RX Parser in Idle state */

/* MTL Rx parser indirect access control and status register value */
#define MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR(regval)   (BITS(0,7) & ((uint32_t)(regval) << 0))          /*!< write value to ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_ADDR bit field */

#define ENET_RXP_MEM_WRITE                           ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN         /*!< indicates the write operation to the Rx parser memory */
#define ENET_RXP_MEM_READ                            ((uint32_t)0x00000000)                                 /*!< indicates the read operation to the Rx parser memory */
#define ENET_RXP_INSERT_ECC_ERR_1BIT                 (ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIEE | ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIEC)      /*!< ECC inject 1-bit error for Rx parser memory */
#define ENET_RXP_INSERT_ECC_ERR_2BIT                 ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIEE       /*!< ECC inject 2-bit error for Rx parser memory */
#define ENET_RXP_INSERT_ECC_ADDR_ERR_1BIT            (ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIAEE | ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIEC)                                                        /*!< ECC inject 1-bit address error for Rx parser memory */
#define ENET_RXP_INSERT_ECC_ADDR_ERR_2BIT            ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_RXPEIAEE      /*!< ECC inject 2-bit address error for Rx parser memory */
#define ENET_RXP_MEM_WRITE_READ_START                ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_STARTBUSY     /*!< indicates the write operation to the Rx parser memory */

/* MTL Rx parser indirect access control and status register value */
#define ENET_MTL_TXFIFO_ECC_ENABLE                   ENET_MTL_ECC_CONTROL_MTXEE                             /*!< enables the ECC feature for MTL Tx FIFO memory */
#define ENET_MTL_TXFIFO_ECC_DISABLE                  ((uint32_t)0x00000000)                                 /*!< disables the ECC feature for MTL Tx FIFO memory */
#define ENET_MTL_RXFIFO_ECC_ENABLE                   ENET_MTL_ECC_CONTROL_MRXEE                             /*!< enables the ECC feature for MTL Rx FIFO memory */
#define ENET_MTL_RXFIFO_ECC_DISABLE                  ((uint32_t)0x00000000)                                 /*!< disables the ECC feature for MTL Rx FIFO memory */
#define ENET_MTL_EST_ECC_ENABLE                      ENET_MTL_ECC_CONTROL_MESTEE                            /*!< enables the ECC feature for EST memory */
#define ENET_MTL_EST_ECC_DISABLE                     ((uint32_t)0x00000000)                                 /*!< disables the ECC feature for EST memory */
#define ENET_MTL_RXP_ECC_ENABLE                      ENET_MTL_ECC_CONTROL_MRXPEE                            /*!< enables the ECC feature for Rx parser memory */
#define ENET_MTL_RXP_ECC_DISABLE                     ((uint32_t)0x00000000)                                 /*!< disables the ECC feature for Rx parser memory */
#define ENET_MTL_EXX_ERR_ADDR_STATUS_OVERRIDE_ENABLE ENET_MTL_ECC_CONTROL_MEEAO                             /*!< MTL ECC error address status over-ride is enabled */
#define ENET_MTL_EXX_ERR_ADDR_STATUS_OVERRIDE_DISABLE ((uint32_t)0x00000000)                                /*!< MTL ECC error address status over-ride is enabled */

/* MTL ECC error status rctl register value */
#define MTL_ECC_ERR_STS_RCTL_EMS(regval)              (BITS(1,3) & ((uint32_t)(regval) << 1))                 /*!< write value to ENET_MTL_ECC_ERR_STS_RCTL_EMS bit field */
#define ENET_MTL_ECC_SELECT_TX_MEM                    MTL_ECC_ERR_STS_RCTL_EMS(0)                             /*!< MTL Tx memory */
#define ENET_MTL_ECC_SELECT_RX_MEM                    MTL_ECC_ERR_STS_RCTL_EMS(1)                             /*!< MTL Rx memory */
#define ENET_MTL_ECC_SELECT_EST_MEM                   MTL_ECC_ERR_STS_RCTL_EMS(2)                             /*!< MTL EST memory */
#define ENET_MTL_ECC_SELECT_RXP_MEM                   MTL_ECC_ERR_STS_RCTL_EMS(3)                             /*!< MTL RXP memory */

#define ENET_MTL_ECC_ERR_STATUS_READ_ENABLE           ENET_MTL_ECC_ERR_STS_RCTL_EESRE                                          /*!< MTL ECC error status read enable */
#define ENET_MTL_UNCORRECTABLE_ERR_STATUS_CLEAR       (ENET_MTL_ECC_ERR_STS_RCTL_EESRE|ENET_MTL_ECC_ERR_STS_RCTL_CUES)         /*!< clear unCorrectable error status */
#define ENET_MTL_CORRECTABLE_ERR_STATUS_CLEAR         (ENET_MTL_ECC_ERR_STS_RCTL_EESRE|ENET_MTL_ECC_ERR_STS_RCTL_CCES)         /*!< clear Correctable error status */

/* ENET_MTL_ECC_ERR_ADDR_STATUS */
#define GET_UNCORRECTABLE_ERR_ADDRESS(regval)         GET_BITS((uint32_t)(regval),0,15)                       /*!< get value of ENET_MTL_ECC_ERR_ADDR_STATUS_ECEAS bit field */
#define GET_CORRECTABLE_ERR_ADDRESS(regval)           GET_BITS((uint32_t)(regval),16,31)                      /*!< get value of ENET_MTL_ECC_ERR_ADDR_STATUS_EUEAS bit field */

#define ENET_MTL_UNCORRECTABLE_ERR_ADDRESS            ENET_MTL_ECC_ERR_ADDR_STATUS_ECEAS                      /*!< MTL ECC correctable error address status */
#define ENET_MTL_CORRECTABLE_ERR_ADDRESS              ENET_MTL_ECC_ERR_ADDR_STATUS_EUEAS                      /*!< MTL ECC uncorrectable error address status */

/* ENET_MTL_ECC_ERR_CNTR_STATUS */
#define GET_UNCORRECTABLE_ERR_COUNT(regval)           GET_BITS((uint32_t)(regval),16,19)                        /*!< get value of ENET_MTL_ECC_ERR_CNTR_STATUS_ECECS bit field */
#define GET_CORRECTABLE_ERR_COUNT(regval)             GET_BITS((uint32_t)(regval),0,7)                      /*!< get value of ENET_MTL_ECC_ERR_CNTR_STATUS_EUECS bit field */

#define ENET_MTL_UNCORRECTABLE_ERR_COUNT              ENET_MTL_ECC_ERR_CNTR_STATUS_ECECS                      /*!< MTL ECC correctable error counter status */
#define ENET_MTL_CORRECTABLE_ERR_COUNT                ENET_MTL_ECC_ERR_CNTR_STATUS_EUECS                      /*!< MTL ECC uncorrectable error counter status */


/* MTL data parity protection control register value */
#define ENET_DATA_PATH_PARITY_PROTECTION_ENABLE       ENET_MTL_DPP_CONTROL_EDPP                               /*!< data path parity protection is enabled */
#define ENET_DATA_PATH_PARITY_PROTECTION_DISABLE      ((uint32_t)0x00000000)                                  /*!< data path parity protection is disabled */
#define ENET_DPP_ODD_PARITY_ENABLE                    ENET_MTL_DPP_CONTROL_OPE                                /*!< odd parity is enabled */
#define ENET_DPP_ODD_PARITY_DISABLE                   ((uint32_t)0x00000000)                                  /*!< odd parity is disabled */
#define ENET_DPP_PARITY_ON_SLAVE_INTERFACE_ENABLE     ENET_MTL_DPP_CONTROL_EPSI                               /*!< parity on slave interface port is enabled  */
#define ENET_DPP_PARITY_ON_SLAVE_INTERFACE_DISABLE    ((uint32_t)0x00000000)                                  /*!< parity on slave interface port is disabled  */
#define ENET_DPP_IPETID_ENABLE                        ENET_MTL_DPP_CONTROL_IPETID                             /*!< insert parity error in Tx interface data parity checker is enabled */
#define ENET_DPP_IPETID_DISABLE                       ((uint32_t)0x00000000)                                  /*!< insert parity error in Tx interface data parity checker is disabled */
#define ENET_DPP_IPETRD_ENABLE                        ENET_MTL_DPP_CONTROL_IPETRD                             /*!< insert parity error in DMA Tx/Rx descriptor parity checker is enabled */
#define ENET_DPP_IPETRD_DISABLE                       ((uint32_t)0x00000000)                                  /*!< insert parity error in DMA Tx/Rx descriptor parity checker is disabled */
#define ENET_DPP_IPEMTF_ENABLE                        ENET_MTL_DPP_CONTROL_IPEMTF                             /*!< insert parity error in MTL Tx FIFO write data parity checker is enabled */
#define ENET_DPP_IPEMTF_DISABLE                       ((uint32_t)0x00000000)                                  /*!< insert parity error in MTL Tx FIFO write data parity checker is disabled */
#define ENET_DPP_IPEMTS_ENABLE                        ENET_MTL_DPP_CONTROL_IPEMTS                             /*!< insert parity error in MTL Tx Status FIFO parity checker is enabled */
#define ENET_DPP_IPEMTS_DISABLE                       ((uint32_t)0x00000000)                                  /*!< insert parity error in MTL Tx Status FIFO parity checker is disabled */
#define ENET_DPP_IPERID_ENABLE                        ENET_MTL_DPP_CONTROL_IPERID                             /*!< insert parity error in RX interface data parity checker is enabled */
#define ENET_DPP_IPERID_DISABLE                       ((uint32_t)0x00000000)                                  /*!< insert parity error in RX interface data parity checker is disabled */
#define ENET_DPP_IPEMTBU_ENABLE                       ENET_MTL_DPP_CONTROL_IPEMTBU                            /*!< insert parity error in MAC TBU data parity checker is enabled */
#define ENET_DPP_IPEMTBU_DISABLE                      ((uint32_t)0x00000000)                                  /*!< insert parity error in MAC TBU data parity checker is disabled */
#define ENET_DPP_IPEMTFC_ENABLE                       ENET_MTL_DPP_CONTROL_IPEMTFC                            /*!< insert parity error in MAC TFC data parity checker is enabled */
#define ENET_DPP_IPEMTFC_DISABLE                      ((uint32_t)0x00000000)                                  /*!< insert parity error in MAC TFC data parity checker is disabled */
#define ENET_DPP_IPEMRWC_ENABLE                       ENET_MTL_DPP_CONTROL_IPEMRWC                            /*!< insert parity error in MTL RWC data parity checker is enabled */
#define ENET_DPP_IPEMRWC_DISABLE                      ((uint32_t)0x00000000)                                  /*!< insert parity error in MTL RWC data parity checker is disabled */

/* MTL ECC/DPP error injection register value */
#define MTL_DPP_ECC_EIC_BLEI(regval)                   (BITS(0,7) & ((uint32_t)(regval) << 0))                /*!< write value to ENET_MTL_DPP_ECC_EIC_BLEI bit field */

#define ENET_ERR_INJTECTION_ON_ECC_PARITY              ENET_MTL_DPP_ECC_EIC_EIM                               /*!< indicate error injection on ECC/Parity bits */
#define ENET_ERR_INJTECTION_ON_DATA                    ((uint32_t)0x00000000)                                 /*!< indicate error injection on data */

/* MTL transmit queue operation mode register value */
#define MTL_TXQ_OPERATION_MODE_TTC(regval)            (BITS(4,6) & ((uint32_t)(regval) << 4))                 /*!< write value to ENET_MTL_TXQ_OPERATION_MODE_TTC bit field */
#define ENET_TX_THRESHOLD_32BYTES                     MTL_TXQ_OPERATION_MODE_TTC(0)                           /*!< threshold level is 32 Bytes */
#define ENET_TX_THRESHOLD_64BYTES                     MTL_TXQ_OPERATION_MODE_TTC(1)                           /*!< threshold level is 64 Bytes */
#define ENET_TX_THRESHOLD_96BYTES                     MTL_TXQ_OPERATION_MODE_TTC(2)                           /*!< threshold level is 96 Bytes */
#define ENET_TX_THRESHOLD_128BYTES                    MTL_TXQ_OPERATION_MODE_TTC(3)                           /*!< threshold level is 128 Bytes */
#define ENET_TX_THRESHOLD_192BYTES                    MTL_TXQ_OPERATION_MODE_TTC(4)                           /*!< threshold level is 192 Bytes */
#define ENET_TX_THRESHOLD_256BYTES                    MTL_TXQ_OPERATION_MODE_TTC(5)                           /*!< threshold level is 256 Bytes */
#define ENET_TX_THRESHOLD_284BYTES                    MTL_TXQ_OPERATION_MODE_TTC(6)                           /*!< threshold level is 284 Bytes */
#define ENET_TX_THRESHOLD_512BYTES                    MTL_TXQ_OPERATION_MODE_TTC(7)                           /*!< threshold level is 512 Bytes */

#define MTL_TXQ_OPERATION_MODE_TQS(regval)            (BITS(16,20) & ((uint32_t)(regval) << 16))              /*!< write value to ENET_MTL_TXQ_OPERATION_MODE_TQS bit field */
#define ENET_TXQ_SIZE_256BYTES                        MTL_TXQ_OPERATION_MODE_TQS(0)                           /*!< the size of the queue is 256 bytes */
#define ENET_TXQ_SIZE_512BYTES                        MTL_TXQ_OPERATION_MODE_TQS(1)                           /*!< the size of the queue is 512 bytes */
#define ENET_TXQ_SIZE_768BYTES                        MTL_TXQ_OPERATION_MODE_TQS(2)                           /*!< the size of the queue is 768 bytes */
#define ENET_TXQ_SIZE_1024BYTES                       MTL_TXQ_OPERATION_MODE_TQS(3)                           /*!< the size of the queue is 1024 bytes */
#define ENET_TXQ_SIZE_1280BYTES                       MTL_TXQ_OPERATION_MODE_TQS(4)                           /*!< the size of the queue is 1280 bytes */
#define ENET_TXQ_SIZE_1536BYTES                       MTL_TXQ_OPERATION_MODE_TQS(5)                           /*!< the size of the queue is 1536 bytes */
#define ENET_TXQ_SIZE_1792BYTES                       MTL_TXQ_OPERATION_MODE_TQS(6)                           /*!< the size of the queue is 1792 bytes */
#define ENET_TXQ_SIZE_2048BYTES                       MTL_TXQ_OPERATION_MODE_TQS(7)                           /*!< the size of the queue is 2048 bytes */
#define ENET_TXQ_SIZE_2304BYTES                       MTL_TXQ_OPERATION_MODE_TQS(8)                           /*!< the size of the queue is 2304 bytes */
#define ENET_TXQ_SIZE_2560BYTES                       MTL_TXQ_OPERATION_MODE_TQS(9)                           /*!< the size of the queue is 2560 bytes */
#define ENET_TXQ_SIZE_2816BYTES                       MTL_TXQ_OPERATION_MODE_TQS(10)                          /*!< the size of the queue is 2816 bytes */
#define ENET_TXQ_SIZE_3072BYTES                       MTL_TXQ_OPERATION_MODE_TQS(11)                          /*!< the size of the queue is 3072 bytes */
#define ENET_TXQ_SIZE_3328BYTES                       MTL_TXQ_OPERATION_MODE_TQS(12)                          /*!< the size of the queue is 3328 bytes */
#define ENET_TXQ_SIZE_3584BYTES                       MTL_TXQ_OPERATION_MODE_TQS(13)                          /*!< the size of the queue is 3584 bytes */
#define ENET_TXQ_SIZE_3840BYTES                       MTL_TXQ_OPERATION_MODE_TQS(14)                          /*!< the size of the queue is 3840 bytes */
#define ENET_TXQ_SIZE_4096BYTES                       MTL_TXQ_OPERATION_MODE_TQS(15)                          /*!< the size of the queue is 4096 bytes */
#define ENET_TXQ_SIZE_4352BYTES                       MTL_TXQ_OPERATION_MODE_TQS(16)                          /*!< the size of the queue is 4352 bytes */
#define ENET_TXQ_SIZE_4608BYTES                       MTL_TXQ_OPERATION_MODE_TQS(17)                          /*!< the size of the queue is 4608 bytes */
#define ENET_TXQ_SIZE_4864BYTES                       MTL_TXQ_OPERATION_MODE_TQS(18)                          /*!< the size of the queue is 4864 bytes */
#define ENET_TXQ_SIZE_5120BYTES                       MTL_TXQ_OPERATION_MODE_TQS(19)                          /*!< the size of the queue is 5120 bytes */
#define ENET_TXQ_SIZE_5376BYTES                       MTL_TXQ_OPERATION_MODE_TQS(20)                          /*!< the size of the queue is 5376 bytes */
#define ENET_TXQ_SIZE_5632BYTES                       MTL_TXQ_OPERATION_MODE_TQS(21)                          /*!< the size of the queue is 5632 bytes */
#define ENET_TXQ_SIZE_5888BYTES                       MTL_TXQ_OPERATION_MODE_TQS(22)                          /*!< the size of the queue is 5888 bytes */
#define ENET_TXQ_SIZE_6144BYTES                       MTL_TXQ_OPERATION_MODE_TQS(23)                          /*!< the size of the queue is 6144 bytes */
#define ENET_TXQ_SIZE_6400BYTES                       MTL_TXQ_OPERATION_MODE_TQS(24)                          /*!< the size of the queue is 6400 bytes */
#define ENET_TXQ_SIZE_6656BYTES                       MTL_TXQ_OPERATION_MODE_TQS(25)                          /*!< the size of the queue is 6656 bytes */
#define ENET_TXQ_SIZE_6912BYTES                       MTL_TXQ_OPERATION_MODE_TQS(26)                          /*!< the size of the queue is 6912 bytes */
#define ENET_TXQ_SIZE_7168BYTES                       MTL_TXQ_OPERATION_MODE_TQS(27)                          /*!< the size of the queue is 7168 bytes */
#define ENET_TXQ_SIZE_7424BYTES                       MTL_TXQ_OPERATION_MODE_TQS(28)                          /*!< the size of the queue is 7424 bytes */
#define ENET_TXQ_SIZE_7680BYTES                       MTL_TXQ_OPERATION_MODE_TQS(29)                          /*!< the size of the queue is 7680 bytes */
#define ENET_TXQ_SIZE_7936BYTES                       MTL_TXQ_OPERATION_MODE_TQS(30)                          /*!< the size of the queue is 7936 bytes */
#define ENET_TXQ_SIZE_8192BYTES                       MTL_TXQ_OPERATION_MODE_TQS(31)                          /*!< the size of the queue is 8192 bytes */


#define ENET_TX_MODE_STOREFORWARD                     ENET_MTL_TXQ0_OPERATION_MODE_TSF                        /*!< TxFIFO operates in store-and-forward mode */
#define ENET_TX_MODE_CUTTHROUGH                       ((uint32_t)0x00000000)                                  /*!< TxFIFO operates in cut-through mode */

/* MTL transmit queue underflow counter register value */
#define GET_UNDERFLOW_PACKET_COUNTER(regval)          GET_BITS((uint32_t)(regval),0,10)                       /*!< get value of ENET_MTL_TXQ0_UNDERFLOW_UFFRMCNT bit field */

#define ENET_TX_UNDERFLOW_PACKET_COUNTER_OVERFLOW     ENET_MTL_TXQ0_UNDERFLOW_UFCNTOVF                        /*!< overflow detected for underflow packet */

/* MTL transmit queue debug register value */
#define GET_TXQ_PACKETS_NUMBER(regval)                GET_BITS((uint32_t)(regval),16,18)                      /*!< get value of ENET_MTL_TXQ0_DEBUG_PTXQ bit field */
#define GET_TXQ_STATUS_WORD_NUMBER(regval)            GET_BITS((uint32_t)(regval),20,22)                      /*!< get value of ENET_MTL_TXQ0_DEBUG_STXSTSF bit field */

#define ENET_TXQ_STATUS_FIFO_FULL_DETECT              ENET_MTL_TXQ1_DEBUG_TXSTSFSTS                            /*!< MTL Tx status FIFO full status is detected */
#define ENET_TXQ_STATUS_FIFO_FULL_NOT_DETECT          ((uint32_t)0x00000000)                                  /*!< MTL Tx status FIFO full status is not detected */

#define ENET_TXQ_STATUS_FIFO_NOT_EMPTY_DETECT         ENET_MTL_TXQ1_DEBUG_TXQSTS                               /*!< MTL Tx status FIFO not empty status is detected */
#define ENET_TXQ_STATUS_FIFO_NOT_EMPTY_NOT_DETECT     ((uint32_t)0x00000000)                                  /*!< MTL Tx status not empty full status is not detected */

#define ENET_TXQ_WRITE_CONTROL_DETECT                 ENET_MTL_TXQ1_DEBUG_TWCSTS                               /*!< MTL Tx queue write controller status is detected */
#define ENET_TXQ_WRITE_CONTROL_NOT_DETECT             ((uint32_t)0x00000000)                                  /*!< MTL Tx queue write controller status is not detected */

#define MTL_TXQ_DEBUG_TRCSTS(regval)                  (BITS(1,2) & ((uint32_t)(regval) << 1))                 /*!< write value to ENET_MTL_TXQ_DEBUG_TRCSTS bit field */
#define ENET_TXQ_READ_CONTROLLER_STATE_IDLE           MTL_TXQ_DEBUG_TRCSTS(0)                                 /*!< Tx queue read controller in idle state */
#define ENET_TXQ_READ_CONTROLLER_STATE_READ           MTL_TXQ_DEBUG_TRCSTS(1)                                 /*!< Tx queue read controller in read state */
#define ENET_TXQ_READ_CONTROLLER_STATE_WAITING        MTL_TXQ_DEBUG_TRCSTS(2)                                 /*!< Tx queue read controller is waiting for pending Tx status from the MAC transmitter */
#define ENET_TXQ_READ_CONTROLLER_STATE_FLUSHING       MTL_TXQ_DEBUG_TRCSTS(3)                                 /*!< Tx queue read controller is flushing the Tx queue because of the packet abort request from the MAC */

#define ENET_TXQ_IN_PAUSE_DETECT                     ENET_MTL_TXQ1_DEBUG_TXQPAUSED                                 /*!< MTL Tx queue in pause status is detected */
#define ENET_TXQ_IN_PAUSE_NOT_DETECT                ((uint32_t)0x00000000)                                        /*!< MTL Tx queue in pause status is not detected */
/* MTL transmit queue underflow counter register value */
#define GET_AVER_BITS(regval)                         GET_BITS((uint32_t)(regval),0,23)                       /*!< get value of ENET_MTL_TXQ_EST_STATUS_ABS bit field */

/* MTL transmit queue quantum weight register value */
#define MTL_TXQ_QUANTUM_ISCQW(regval)                (BITS(0,20) & ((uint32_t)(regval) << 0))                 /*!< write value to ENET_MTL_TXQ_QUANTUM_ISCQW bit field */

/* MTL receive queue operation mode register value */
#define MTL_RXQ_OPERATION_MODE_RTC(regval)           (BITS(0,1) & ((uint32_t)(regval) << 0))                  /*!< write value to ENET_DMA_CTL_RTHC bit field */
#define ENET_RX_THRESHOLD_64BYTES                     MTL_RXQ_OPERATION_MODE_RTC(0)                           /*!< threshold level is 64 Bytes */
#define ENET_RX_THRESHOLD_32BYTES                     MTL_RXQ_OPERATION_MODE_RTC(1)                           /*!< threshold level is 32 Bytes */
#define ENET_RX_THRESHOLD_96BYTES                     MTL_RXQ_OPERATION_MODE_RTC(2)                           /*!< threshold level is 96 Bytes */
#define ENET_RX_THRESHOLD_128BYTES                    MTL_RXQ_OPERATION_MODE_RTC(3)                           /*!< threshold level is 128 Bytes */

#define MTL_RXQ_OPERATION_MODE_RFA(regval)            (BITS(8,11) & ((uint32_t)(regval) << 8))                /*!< write value to ENET_MTL_RXQ_OPERATION_MODE_RFA bit field */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_1K           MTL_RXQ_OPERATION_MODE_RFA(0)                           /*!< full minus 1 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_1_5K         MTL_RXQ_OPERATION_MODE_RFA(1)                           /*!< full minus 1.5 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_2K           MTL_RXQ_OPERATION_MODE_RFA(2)                           /*!< full minus 2 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_2_5K         MTL_RXQ_OPERATION_MODE_RFA(3)                           /*!< full minus 2.5 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_3K           MTL_RXQ_OPERATION_MODE_RFA(4)                           /*!< full minus 3 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_3_5K         MTL_RXQ_OPERATION_MODE_RFA(5)                           /*!< full minus 3.5 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_4K           MTL_RXQ_OPERATION_MODE_RFA(6)                           /*!< full minus 4 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_4_5K         MTL_RXQ_OPERATION_MODE_RFA(7)                           /*!< full minus 4.5 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_5K           MTL_RXQ_OPERATION_MODE_RFA(8)                           /*!< full minus 5 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_5_5K         MTL_RXQ_OPERATION_MODE_RFA(9)                           /*!< full minus 5.5 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_6K           MTL_RXQ_OPERATION_MODE_RFA(10)                           /*!< full minus 6 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_6_5K         MTL_RXQ_OPERATION_MODE_RFA(11)                           /*!< full minus 6.5 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_7K           MTL_RXQ_OPERATION_MODE_RFA(12)                           /*!< full minus 7 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_7_5K         MTL_RXQ_OPERATION_MODE_RFA(13)                           /*!< full minus 7.5 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_8K           MTL_RXQ_OPERATION_MODE_RFA(14)                           /*!< full minus 8 KB */
#define ENET_ACTIVE_THRESHOLD_FULL_MINUS_8_5K         MTL_RXQ_OPERATION_MODE_RFA(15)                           /*!< full minus 8.5 KB */

#define MTL_RXQ_OPERATION_MODE_RFD(regval)            (BITS(14,17) & ((uint32_t)(regval) << 14))              /*!< write value to ENET_MAC_FCTH_RFD bit field */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_1K         MTL_RXQ_OPERATION_MODE_RFD(0)                           /*!< full minus 1 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_1_5K       MTL_RXQ_OPERATION_MODE_RFD(1)                           /*!< full minus 1.5 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_2K         MTL_RXQ_OPERATION_MODE_RFD(2)                           /*!< full minus 2 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_2_5K       MTL_RXQ_OPERATION_MODE_RFD(3)                           /*!< full minus 2.5 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_3K         MTL_RXQ_OPERATION_MODE_RFD(4)                           /*!< full minus 3 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_3_5K       MTL_RXQ_OPERATION_MODE_RFD(5)                           /*!< full minus 3.5 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_4K         MTL_RXQ_OPERATION_MODE_RFD(6)                           /*!< full minus 4 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_4_5K       MTL_RXQ_OPERATION_MODE_RFD(7)                           /*!< full minus 4.5 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_5K         MTL_RXQ_OPERATION_MODE_RFD(8)                           /*!< full minus 5 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_5_5K       MTL_RXQ_OPERATION_MODE_RFD(9)                           /*!< full minus 5.5 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_6K         MTL_RXQ_OPERATION_MODE_RFD(10)                           /*!< full minus 6 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_6_5K       MTL_RXQ_OPERATION_MODE_RFD(11)                           /*!< full minus 6.5 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_7K         MTL_RXQ_OPERATION_MODE_RFD(12)                           /*!< full minus 7 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_7_5K       MTL_RXQ_OPERATION_MODE_RFD(13)                           /*!< full minus 7.5 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_8K         MTL_RXQ_OPERATION_MODE_RFD(14)                           /*!< full minus 8 KB */
#define ENET_DEACTIVE_THRESHOLD_FULL_MINUS_8_5K       MTL_RXQ_OPERATION_MODE_RFD(15)                           /*!< full minus 8.5 KB */

#define MTL_RXQ_OPERATION_MODE_RQS(regval)            (BITS(20,24) & ((uint32_t)(regval) << 20))              /*!< write value to ENET_MTL_RXQ_OPERATION_MODE_RQS bit field */
#define ENET_RXQ_SIZE_256BYTES                        MTL_RXQ_OPERATION_MODE_RQS(0)                           /*!< the size of the queue is 256 bytes */
#define ENET_RXQ_SIZE_512BYTES                        MTL_RXQ_OPERATION_MODE_RQS(1)                           /*!< the size of the queue is 512 bytes */
#define ENET_RXQ_SIZE_768BYTES                        MTL_RXQ_OPERATION_MODE_RQS(2)                           /*!< the size of the queue is 768 bytes */
#define ENET_RXQ_SIZE_1024BYTES                       MTL_RXQ_OPERATION_MODE_RQS(3)                           /*!< the size of the queue is 1024 bytes */
#define ENET_RXQ_SIZE_1280BYTES                       MTL_RXQ_OPERATION_MODE_RQS(4)                           /*!< the size of the queue is 1280 bytes */
#define ENET_RXQ_SIZE_1536BYTES                       MTL_RXQ_OPERATION_MODE_RQS(5)                           /*!< the size of the queue is 1536 bytes */
#define ENET_RXQ_SIZE_1792BYTES                       MTL_RXQ_OPERATION_MODE_RQS(6)                           /*!< the size of the queue is 1792 bytes */
#define ENET_RXQ_SIZE_2048BYTES                       MTL_RXQ_OPERATION_MODE_RQS(7)                           /*!< the size of the queue is 2048 bytes */
#define ENET_RXQ_SIZE_2304BYTES                       MTL_RXQ_OPERATION_MODE_RQS(8)                           /*!< the size of the queue is 2304 bytes */
#define ENET_RXQ_SIZE_2560BYTES                       MTL_RXQ_OPERATION_MODE_RQS(9)                           /*!< the size of the queue is 2560 bytes */
#define ENET_RXQ_SIZE_2816BYTES                       MTL_RXQ_OPERATION_MODE_RQS(10)                          /*!< the size of the queue is 2816 bytes */
#define ENET_RXQ_SIZE_3072BYTES                       MTL_RXQ_OPERATION_MODE_RQS(11)                          /*!< the size of the queue is 3072 bytes */
#define ENET_RXQ_SIZE_3328BYTES                       MTL_RXQ_OPERATION_MODE_RQS(12)                          /*!< the size of the queue is 3328 bytes */
#define ENET_RXQ_SIZE_3584BYTES                       MTL_RXQ_OPERATION_MODE_RQS(13)                          /*!< the size of the queue is 3584 bytes */
#define ENET_RXQ_SIZE_3840BYTES                       MTL_RXQ_OPERATION_MODE_RQS(14)                          /*!< the size of the queue is 3840 bytes */
#define ENET_RXQ_SIZE_4096BYTES                       MTL_RXQ_OPERATION_MODE_RQS(15)                          /*!< the size of the queue is 4096 bytes */
#define ENET_RXQ_SIZE_4352BYTES                       MTL_RXQ_OPERATION_MODE_RQS(16)                          /*!< the size of the queue is 4352 bytes */
#define ENET_RXQ_SIZE_4608BYTES                       MTL_RXQ_OPERATION_MODE_RQS(17)                          /*!< the size of the queue is 4608 bytes */
#define ENET_RXQ_SIZE_4864BYTES                       MTL_RXQ_OPERATION_MODE_RQS(18)                          /*!< the size of the queue is 4864 bytes */
#define ENET_RXQ_SIZE_5120BYTES                       MTL_RXQ_OPERATION_MODE_RQS(19)                          /*!< the size of the queue is 5120 bytes */
#define ENET_RXQ_SIZE_5376BYTES                       MTL_RXQ_OPERATION_MODE_RQS(20)                          /*!< the size of the queue is 5376 bytes */
#define ENET_RXQ_SIZE_5632BYTES                       MTL_RXQ_OPERATION_MODE_RQS(21)                          /*!< the size of the queue is 5632 bytes */
#define ENET_RXQ_SIZE_5888BYTES                       MTL_RXQ_OPERATION_MODE_RQS(22)                          /*!< the size of the queue is 5888 bytes */
#define ENET_RXQ_SIZE_6144BYTES                       MTL_RXQ_OPERATION_MODE_RQS(23)                          /*!< the size of the queue is 6144 bytes */
#define ENET_RXQ_SIZE_6400BYTES                       MTL_RXQ_OPERATION_MODE_RQS(24)                          /*!< the size of the queue is 6400 bytes */
#define ENET_RXQ_SIZE_6656BYTES                       MTL_RXQ_OPERATION_MODE_RQS(25)                          /*!< the size of the queue is 6656 bytes */
#define ENET_RXQ_SIZE_6912BYTES                       MTL_RXQ_OPERATION_MODE_RQS(26)                          /*!< the size of the queue is 6912 bytes */
#define ENET_RXQ_SIZE_7168BYTES                       MTL_RXQ_OPERATION_MODE_RQS(27)                          /*!< the size of the queue is 7168 bytes */
#define ENET_RXQ_SIZE_7424BYTES                       MTL_RXQ_OPERATION_MODE_RQS(28)                          /*!< the size of the queue is 7424 bytes */
#define ENET_RXQ_SIZE_7680BYTES                       MTL_RXQ_OPERATION_MODE_RQS(29)                          /*!< the size of the queue is 7680 bytes */
#define ENET_RXQ_SIZE_7936BYTES                       MTL_RXQ_OPERATION_MODE_RQS(30)                          /*!< the size of the queue is 7936 bytes */
#define ENET_RXQ_SIZE_8192BYTES                       MTL_RXQ_OPERATION_MODE_RQS(31)                          /*!< the size of the queue is 8192 bytes */

#define ENET_FORWARD_UNDERSZ_GOODFRAMES_ENABLE        ENET_MTL_RXQ0_OPERATION_MODE_FUP                        /*!< forward undersized good frames */
#define ENET_FORWARD_UNDERSZ_GOODFRAMES_DISABLE       ((uint32_t)0x00000000)                                  /*!< RxFIFO drops all frames whose length is less than 64 bytes */
#define ENET_FORWARD_UNDERSZ_GOODFRAMES               ENET_MTL_RXQ0_OPERATION_MODE_FUP                        /*!< the function that forwarding undersized good frames */


#define ENET_FORWARD_ERRFRAMES_ENABLE                 ENET_MTL_RXQ0_OPERATION_MODE_FEP                        /*!< all frame received with error except runt error are forwarded to memory */
#define ENET_FORWARD_ERRFRAMES_DISABLE                ((uint32_t)0x00000000)                                  /*!< RxFIFO drop error frame */
#define ENET_FORWARD_ERRFRAMES                        ENET_MTL_RXQ0_OPERATION_MODE_FEP                        /*!< the function that all frame received with error except runt error are forwarded to memory */

#define ENET_RX_MODE_STOREFORWARD                     ENET_MTL_RXQ0_OPERATION_MODE_RSF                        /*!< RxFIFO operates in store-and-forward mode */
#define ENET_RX_MODE_CUTTHROUGH                       ((uint32_t)0x00000000)                                  /*!< RxFIFO operates in cut-through mode */

#define ENET_TCPIP_CKSUMERROR_ACCEPT                  ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF                 /*!< Rx frame with only payload error but no other errors will not be dropped */
#define ENET_TCPIP_CKSUMERROR_DROP                   ((uint32_t)0x00000000)                                   /*!< all error frames will be dropped when FEP = 0 */

#define ENET_RXQ0_HARDWARE_FLOW_CONTROL_ENABLE       (ENET_MTL_RXQ0_OPERATION_MODE_EHFC << 3U)                /*!< rxq0 hardware flow control is enabled */
#define ENET_RXQ0_HARDWARE_FLOW_CONTROL_DISABLE      ((uint32_t)0x00000000)                                   /*!< rxq0 hardware flow control is disabled */
#define ENET_RXQ1_HARDWARE_FLOW_CONTROL_ENABLE       (ENET_MTL_RXQ0_OPERATION_MODE_EHFC << 4U)                /*!< rxq1 hardware flow control is enabled */
#define ENET_RXQ1_HARDWARE_FLOW_CONTROL_DISABLE      ((uint32_t)0x00000000)                                   /*!< rxq1 hardware flow control is disabled */

#define ENET_HARDWARE_FLOW_CONTROL                    ENET_MTL_RXQ0_OPERATION_MODE_EHFC                       /*!< hardware flow control */

/* MTL receive queue missed frame overflow counter register value */
#define GET_OVERFLOW_PACKET_COUNTER(regval)           GET_BITS((uint32_t)(regval),0,10)                       /*!< get value of ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFPKTCNT bit field */

#define ENET_RX_OVERFLOW_COUNTER_OVERFLOW             ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_OVFCNTOVF      /*!< overflow counter overflow detected */

#define GET_MISSED_PACKET_COUNTER(regval)             GET_BITS((uint32_t)(regval),16,26)                      /*!< get value of ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MFCNT bit field */

#define ENET_RX_MISSED_COUNTER_OVERFLOW               ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_MISCNTOVF      /*!< missed packet counter overflow detected */

/* MTL receive queue debug register value */
#define GET_RXQ_PACKETS_NUMBER(regval)                GET_BITS((uint32_t)(regval),16,29)                      /*!< get value of ENET_MTL_RXQ0_DEBUG_PRXQ bit field */

#define GET_RXQ_FILL_LEVEL(regval)                   (BITS(4,5) & ((uint32_t)(regval) << 4))                  /*!< get value of ENET_MTL_RXQ0_DEBUG_RXQSTS bit field */
#define ENET_RXQ_EMPTY                               ((uint32_t)0x00000000)                                   /*!< Rx queue empty */
#define ENET_RXQ_FILL_BELOW_DEACTIVATE_THRESHOLD     BIT(4)                                                   /*!< Rx queue fill-level below flow-control deactivate threshold */
#define ENET_RXQ_FILL_ABOVE_ACTIVATE_THRESHOLD       BIT(5)                                                   /*!< Rx queue fill-level above flow-control activate threshold */
#define ENET_RXQ_FULL                                BIT(4) | BIT(5)                                          /*!< Rx queue full */

#define GET_RXQ_READ_CONTROLLER_STATE(regval)        (BITS(1,2) & ((uint32_t)(regval) << 1))                  /*!< get value of ENET_MTL_RXQ0_DEBUG_RRCSTS bit field */
#define ENET_RXQ_READ_CONTROLLER_IDLE                ((uint32_t)0x00000000)                                   /*!< idle state */
#define ENET_RXQ_READ_CONTROLLER_READING_DATA        BIT(1)                                                   /*!< reading packet data */
#define ENET_RXQ_READ_CONTROLLER_READING_STATUS      BIT(2)                                                   /*!< reading packet status (or timestamp */
#define ENET_RXQ_READ_CONTROLLER_FLUSHING            BIT(1) | BIT(2)                                          /*!< flushing the packet data and status */

#define ENET_RXQ_WRITE_CONTROLLER_ACTIVE             ENET_MTL_RXQ0_DEBUG_RWCSTS                               /*!< indicates that the MTL Rx queue write controller is active */
#define ENET_RXQ_WRITE_CONTROLLER_INACTIVE           ((uint32_t)0x00000000)                                   /*!< indicates that the MTL Rx queue write controller is inactive */

/* MTL receive queue control register value */
#define MTL_RXQ_CONTROL_RXQ_WEGT(regval)             (BITS(0,2) & ((uint32_t)(regval) << 0))                  /*!< write value to ENET_MTL_RXQ_CONTROL_RXQ_WEGT bit field */

#define MTL_RXQ_PACKET_ARBITRATION(regval)           (BIT(3) & ((uint32_t)(regval) << 3))                     /*!< receive queue packet arbitration config */

/* MTL transmit queue 1 ETS control register value */
#define MTL_TXQ1_EST_CONTROL_SLC(regval)             (BITS(4,6) & ((uint32_t)(regval) << 4))                  /*!< write value to ENET_MTL_TXQ1_EST_CONTROL_SLC bit field */
#define ENET_CBS_1SLOT                               MTL_TXQ1_EST_CONTROL_SLC(0)                              /*!< 1 slot */
#define ENET_CBS_2SLOT                               MTL_TXQ1_EST_CONTROL_SLC(1)                              /*!< 2 slot */
#define ENET_CBS_4SLOT                               MTL_TXQ1_EST_CONTROL_SLC(2)                              /*!< 4 slot */
#define ENET_CBS_8SLOT                               MTL_TXQ1_EST_CONTROL_SLC(3)                              /*!< 8 slot */
#define ENET_CBS_16SLOT                              MTL_TXQ1_EST_CONTROL_SLC(4)                              /*!< 16 slot */

#define ENET_TXQ1_CREDIT_CONTROL_ENABLE              ENET_MTL_TXQ1_ETS_CONTROL_CC                             /*!< credit control is enable */
#define ENET_TXQ1_CREDIT_CONTROL_DISABLE             ~ENET_TXQ1_CREDIT_CONTROL_ENABLE                         /*!< credit control is disabled */
#define ENET_TXQ1_CREDIT_CONTROL                     ENET_MTL_TXQ1_ETS_CONTROL_CC                             /*!< the accumulated credit is not reset to zero when there is positive credit and no packet to transmit in Channel 1 */

#define ENET_TXQ1_AV_ALGO_ENABLE                     ENET_MTL_TXQ1_ETS_CONTROL_AVALG                         /*!< CBS algorithm is enable */
#define ENET_TXQ1_AV_ALGO_DISABLE                    ~ENET_TXQ1_AV_ALGO_ENABLE                                  /*!< CBS algorithm is disabled */
#define ENET_TXQ1_AV_ALGO                            ENET_MTL_TXQ1_ETS_CONTROL_AVALG                         /*!< when queue 1 is programmed for AV, this field configures the scheduling algorithm for this queue */

/* MTL transmit queue 1 sendSlopeCredit register value */
#define MTL_TXQ1_SENDSLOPECREDIT_SSC(regval)         (BITS(0,13) & ((uint32_t)(regval) << 0))                /*!< write value to ENET_MTL_TXQ1_SENDSLOPECREDIT_SSC bit field */

/* MTL transmit queue 1 high credit register value */
#define MTL_TXQ1_HICREDIT_HC(regval)                 (BITS(0,28) & ((uint32_t)(regval) << 0))                /*!< write value to ENET_MTL_TXQ1_HICREDIT_HC bit field */

/* MTL transmit queue 1 sendSlopeCredit register value */
#define MTL_TXQ1_LOCREDIT_LC(regval)                 (BITS(0,28) & ((uint32_t)(regval) << 0))                /*!< write value to ENET_MTL_TXQ1_LOCREDIT_LC bit field */

/* DMA mode register value */
#define DMA_MODE_TAA(regval)                         (BITS(2,4) & ((uint32_t)(regval) << 2))                 /*!< write value to ENET_DMA_MODE_TAA bit field */
#define ENET_TX_CHANNEL_ARBITRATION_FP               DMA_MODE_TAA(0)                                         /*!< select the fixed priority arbitration algorithm for the transmit side */
#define ENET_TX_CHANNEL_ARBITRATION_WSP              DMA_MODE_TAA(1)                                         /*!< select the weighted strict priority arbitration algorithm for the transmit side */
#define ENET_TX_CHANNEL_ARBITRATION_WRR              DMA_MODE_TAA(2)                                         /*!< select the weighted round-robin arbitration algorithm for the transmit side */

#define DMA_MODE_TXPR(regval)                     (BIT(11) & ((uint32_t)(regval) << 11))       /*!< write value to DMA_MODE_TXPR bit field */

#define DMA_MODE_PR(regval)                         (BITS(12,14) & ((uint32_t)(regval) << 12))               /*!< write value to ENET_DMA_MODE_TAA bit field */
#define ENET_ARBITRATION_RXTX_1_1                   DMA_MODE_PR(0)                                           /*!< receive and transmit priority ratio is 1:1 */
#define ENET_ARBITRATION_RXTX_2_1                   DMA_MODE_PR(1)                                           /*!< receive and transmit priority ratio is 2:1 */
#define ENET_ARBITRATION_RXTX_3_1                   DMA_MODE_PR(2)                                           /*!< receive and transmit priority ratio is 3:1 */
#define ENET_ARBITRATION_RXTX_4_1                   DMA_MODE_PR(3)                                           /*!< receive and transmit priority ratio is 4:1 */
#define ENET_ARBITRATION_RXTX_5_1                   DMA_MODE_PR(4)                                           /*!< receive and transmit priority ratio is 5:1 */
#define ENET_ARBITRATION_RXTX_6_1                   DMA_MODE_PR(5)                                           /*!< receive and transmit priority ratio is 6:1 */
#define ENET_ARBITRATION_RXTX_7_1                   DMA_MODE_PR(6)                                           /*!< receive and transmit priority ratio is 7:1 */
#define ENET_ARBITRATION_RXTX_8_1                   DMA_MODE_PR(7)                                           /*!< receive and transmit priority ratio is 8:1 */
#define ENET_ARBITRATION_TXRX_1_1                   (DMA_MODE_PR(0) | ENET_DMA_MODE_TXPR)                    /*!< transmit and receive priority ratio is 1:1 */
#define ENET_ARBITRATION_TXRX_2_1                   (DMA_MODE_PR(1) | ENET_DMA_MODE_TXPR)                    /*!< transmit and receive priority ratio is 2:1 */
#define ENET_ARBITRATION_TXRX_3_1                   (DMA_MODE_PR(2) | ENET_DMA_MODE_TXPR)                    /*!< transmit and receive priority ratio is 3:1 */
#define ENET_ARBITRATION_TXRX_4_1                   (DMA_MODE_PR(3) | ENET_DMA_MODE_TXPR)                    /*!< transmit and receive priority ratio is 4:1 */
#define ENET_ARBITRATION_TXRX_5_1                   (DMA_MODE_PR(4) | ENET_DMA_MODE_TXPR)                    /*!< transmit and receive priority ratio is 5:1 */
#define ENET_ARBITRATION_TXRX_6_1                   (DMA_MODE_PR(5) | ENET_DMA_MODE_TXPR)                    /*!< transmit and receive priority ratio is 6:1 */
#define ENET_ARBITRATION_TXRX_7_1                   (DMA_MODE_PR(6) | ENET_DMA_MODE_TXPR)                    /*!< transmit and receive priority ratio is 7:1 */
#define ENET_ARBITRATION_TXRX_8_1                   (DMA_MODE_PR(7) | ENET_DMA_MODE_TXPR)                    /*!< transmit and receive priority ratio is 8:1 */
#define ENET_ARBITRATION_TXPRIORRX                  ENET_DMA_MODE_TXPR                                       /*!< TxDMA has higher priority than RxDMA */

#define DMA_MODE_INTM(regval)                       (BITS(16,17) & ((uint32_t)(regval) << 16))               /*!< write value to ENET_DMA_MODE_INTM bit field */
#define ENET_INTERRUPT_MODE0                        DMA_MODE_INTM(0)                                         /*!< interrupt mode 0 */
#define ENET_INTERRUPT_MODE1                        DMA_MODE_INTM(1)                                         /*!< interrupt mode 1 */
#define ENET_INTERRUPT_MODE2                        DMA_MODE_INTM(2)                                         /*!< interrupt mode 2 */

#define ENET_TXRX_FP                                ENET_DMA_MODE_DA                                         /*!< fixed priority */
#define ENET_TXRX_WRR                               ((uint32_t)0x00000000)                                   /*!< weighted round-robin */

/* DMA system bus mode register value */
#define ENET_FIXED_BURST_ENABLE                     ENET_DMA_SYSBUS_MODE_FB                                  /*!< AHB can only use SINGLE/INCR4/INCR8/INCR16 during start of normal burst transfers */
#define ENET_FIXED_BURST_DISABLE                    ((uint32_t)0x00000000)                                   /*!< AHB can use SINGLE/INCR burst transfer operations */

#define ENET_ADDRESS_ALIGN_ENABLE                   ENET_DMA_SYSBUS_MODE_AAL                                 /*!< enabled address-aligned */
#define ENET_ADDRESS_ALIGN_DISABLE                  ((uint32_t)0x00000000)                                   /*!< disable address-aligned */

#define ENET_MIXED_BURST_ENABLE                     ENET_DMA_SYSBUS_MODE_MB                                  /*!< AHB master interface transfer burst length greater than 16 with INCR */
#define ENET_MIXED_BURST_DISABLE                    ((uint32_t)0x00000000)                                   /*!< AHB master interface only transfer fixed burst length with 16 and below */

#define ENET_REBUILD_INCRx_BURST_ENABLE             ENET_DMA_SYSBUS_MODE_RB                                  /*!< rebuild INCRx Burst is enabled */
#define ENET_REBUILD_INCRx_BURST_DISABLE            ((uint32_t)0x00000000)                                   /*!< rebuild INCRx Burst is disabled */

/* DMA debug status 0 register value */
#define GET_RXDMACH0_PROCESS_STATE(regval)          (BITS(8,11) & ((uint32_t)(regval) << 8))                 /*!< get value of ENET_DMA_DEBUG_STATUS0_RPS0 bit field */
#define ENET_RXCH0_STATE_STOPPED                    ((uint32_t)0x00000000)                                   /*!< reset or stop rx command issued */
#define ENET_RXCH0_STATE_FETCHING                   BIT(8)                                                   /*!< fetching the Rx descriptor */
#define ENET_RXCH0_STATE_WAITING                    (BIT(8)|BIT(9))                                          /*!< waiting for receive packet */
#define ENET_RXCH0_STATE_SUSPENDED                  BIT(10)                                                  /*!< Rx descriptor unavailable */
#define ENET_RXCH0_STATE_CLOSING                    (BIT(8)|BIT(10))                                         /*!< closing receive descriptor */
#define ENET_RXCH0_STATE_WRITING                    (BIT(9)|BIT(10))                                         /*!< writing timestamp */
#define ENET_RXCH0_STATE_QUEUING                    (BIT(8)|BIT(9)|BIT(10))                                  /*!< transferring the receive packet data from recevie buffer to host memory */

#define GET_TXDMACH0_PROCESS_STATE(regval)          (BITS(12,15) & ((uint32_t)(regval) << 12))               /*!< get value of ENET_DMA_DEBUG_STATUS0_TPS0 bit field */
#define ENET_TXCH0_STATE_STOPPED                    ((uint32_t)0x00000000)                                   /*!< reset or stop Tx Command issued  */
#define ENET_TXCH0_STATE_FETCHING                   BIT(12)                                                  /*!< fetching the Tx descriptor */
#define ENET_TXCH0_STATE_WAITING                    BIT(13)                                                  /*!< waiting for status */
#define ENET_TXCH0_STATE_READING                    (BIT(12)|BIT(13))                                        /*!< reading the data from host memory buffer and queuing it to transmit buffer */
#define ENET_TXCH0_STATE_WRITING                    BIT(14)                                                  /*!< writing timestamp */
#define ENET_TXCH0_STATE_SUSPENDED                  (BIT(13)|BIT(14))                                        /*!< Tx descriptor unavailabe or transmit buffer underflow */
#define ENET_TXCH0_STATE_CLOSING                    (BIT(12)|BIT(13)|BIT(14))                                /*!< closing Tx descriptor */

#define GET_RXDMACH1_PROCESS_STATE(regval)          (BITS(16,19) & ((uint32_t)(regval) << 16))               /*!< get value of ENET_DMA_DEBUG_STATUS0_RPS1 bit field */
#define ENET_RXCH1_STATE_STOPPED                    ((uint32_t)0x00000000)                                   /*!< reset or stop rx command issued */
#define ENET_RXCH1_STATE_FETCHING                   BIT(16)                                                  /*!< fetching the Rx descriptor */
#define ENET_RXCH1_STATE_WAITING                    (BIT(16)|BIT(17))                                        /*!< waiting for receive packet */
#define ENET_RXCH1_STATE_SUSPENDED                  BIT(18)                                                  /*!< Rx descriptor unavailable */
#define ENET_RXCH1_STATE_CLOSING                    (BIT(16)|BIT(18))                                        /*!< closing receive descriptor */
#define ENET_RXCH1_STATE_WRITING                    (BIT(17)|BIT(18))                                        /*!< writing timestamp */
#define ENET_RXCH1_STATE_QUEUING                    (BIT(16)|BIT(17)|BIT(18))                                /*!< transferring the receive packet data from recevie buffer to host memory */

#define GET_TXDMACH1_PROCESS_STATE(regval)          (BITS(20,23) & ((uint32_t)(regval) << 20))               /*!< get value of ENET_DMA_DEBUG_STATUS0_TPS1 bit field */
#define ENET_TXCH1_STATE_STOPPED                    ((uint32_t)0x00000000)                                   /*!< reset or stop Tx Command issued  */
#define ENET_TXCH1_STATE_FETCHING                   BIT(20)                                                  /*!< fetching the Tx descriptor */
#define ENET_TXCH1_STATE_WAITING                    BIT(21)                                                  /*!< waiting for status */
#define ENET_TXCH1_STATE_READING                    (BIT(20)|BIT(21))                                        /*!< reading the data from host memory buffer and queuing it to transmit buffer */
#define ENET_TXCH1_STATE_WRITING                    BIT(22)                                                  /*!< writing timestamp */
#define ENET_TXCH1_STATE_SUSPENDED                  (BIT(21)|BIT(22))                                        /*!< Tx descriptor unavailabe or transmit buffer underflow */
#define ENET_TXCH1_STATE_CLOSING                    (BIT(21)|BIT(22)|BIT(23))                                /*!< closing Tx descriptor */

/* DMA TBS control 0 register value */
#define DMA_TBS_CTRL0_FGOS(regval)                  (BITS(4,6) & ((uint32_t)(regval) << 4))                  /*!< write value to ENET_DMA_TBS_CTRL0_FGOS bit field */

#define DMA_TBS_CTRL0_FTOS(regval)                  (BITS(8,31) & ((uint32_t)(regval) << 8))                 /*!< write value to ENET_DMA_TBS_CTRL0_FTOS bit field */

#define ENET_FETCH_TIME_OFFSET_VALID                 ENET_DMA_TBS_CTRL0_FTOV                                 /*!< the FTOS field is valid */

/* DMA channel control register value */
#define DMA_CH_CONTROL_DSL(regval)                   (BITS(18,20) & ((uint32_t)(regval) << 18))       /*!< write value to ENET_DMA_CH_CONTROL_DSL bit field */
#define GET_DMA_CH_CONTROL_DSL(regval)               GET_BITS((regval),18,20)                         /*!< get value of ENET_DMA_CH_CONTROL_DSL bit field */
#define ENET_DMA_CH_PBLx8_ENABLE                     ENET_DMA_CTL_DTCERFD                             /*!< 8xPBL mode is enabled */
#define ENET_DMA_CH_PBLx8_DISABLE                    ((uint32_t)0x00000000)                           /*!< 8xPBL mode is disabled */

/* DMA channel transmit control register value */
#define DMA_CH_TX_CONTROL_TxPBL(regval)           ((BITS(16,21) & ((uint32_t)(regval) << 16))>>8)                     /*!< write value to DMA_CH_TX_CONTROL_TxPBL bit field */
#define ENET_PGBL_1BEAT                           DMA_CH_TX_CONTROL_TxPBL(1)                                          /*!< maximum number of beats is 1 */
#define ENET_PGBL_2BEAT                           DMA_CH_TX_CONTROL_TxPBL(2)                                          /*!< maximum number of beats is 2 */
#define ENET_PGBL_4BEAT                           DMA_CH_TX_CONTROL_TxPBL(4)                                          /*!< maximum number of beats is 4 */
#define ENET_PGBL_8BEAT                           DMA_CH_TX_CONTROL_TxPBL(8)                                          /*!< maximum number of beats is 8 */
#define ENET_PGBL_16BEAT                          DMA_CH_TX_CONTROL_TxPBL(16)                                         /*!< maximum number of beats is 16 */
#define ENET_PGBL_32BEAT                          DMA_CH_TX_CONTROL_TxPBL(32)                                         /*!< maximum number of beats is 32 */
#define ENET_PGBL_8xPGBL_8BEAT                    (DMA_CH_TX_CONTROL_TxPBL(1)|(ENET_DMA_CH_CONTROL_PBLx8<<7))         /*!< maximum number of beats is 4 */
#define ENET_PGBL_8xPGBL_16BEAT                   (DMA_CH_TX_CONTROL_TxPBL(2)|(ENET_DMA_CH_CONTROL_PBLx8<<7))         /*!< maximum number of beats is 8 */
#define ENET_PGBL_8xPGBL_32BEAT                   (DMA_CH_TX_CONTROL_TxPBL(4)|(ENET_DMA_CH_CONTROL_PBLx8<<7))         /*!< maximum number of beats is 16 */
#define ENET_PGBL_8xPGBL_64BEAT                   (DMA_CH_TX_CONTROL_TxPBL(8)|(ENET_DMA_CH_CONTROL_PBLx8<<7))         /*!< maximum number of beats is 32 */
#define ENET_PGBL_8xPGBL_128BEAT                  (DMA_CH_TX_CONTROL_TxPBL(16)|(ENET_DMA_CH_CONTROL_PBLx8<<7))        /*!< maximum number of beats is 64 */
#define ENET_PGBL_8xPGBL_256BEAT                  (DMA_CH_TX_CONTROL_TxPBL(32)|(ENET_DMA_CH_CONTROL_PBLx8<<7))        /*!< maximum number of beats is 128 */

#define DMA_CH_TX_WEIGHT(regval)                       (BITS(1,3) & ((uint32_t)(regval) << 1))          /*!< write value to DMA_CH_TX_CONTROL_TCW bit field */
#define ENET_SECONDFRAME_OPT_ENABLE                    BIT(4)                                           /*!< TxDMA controller operate on second frame mode enable*/
#define ENET_SECONDFRAME_OPT_DISABLE                   ((uint32_t)0x00000000)                           /*!< TxDMA controller operate on second frame mode disable */
#define ENET_SECONDFRAME_OPT                           ENET_SECONDFRAME_OPT_ENABLE                      /*!< TxDMA controller operate on second frame function */
#define ENET_ENHANCED_DESCRIPTOR                       BIT(28)                                          /*!< enhanced mode descriptor */
#define ENET_NORMAL_DESCRIPTOR                        ((uint32_t)0x00000000U)                           /*!< normal mode descriptor */

/* DMA channel receive control register value */
#define ENET_FLUSH_RXFRAME_ENABLE                 BIT(31)                                                             /*!< RxDMA flushes all frames */
#define ENET_FLUSH_RXFRAME_DISABLE                ((uint32_t)0x00000000)                                              /*!< RxDMA does not flush any frames */
#define ENET_FLUSH_RXFRAME                        ENET_FLUSH_RXFRAME_ENABLE                                           /*!< RxDMA flushes frames function */

#define DMA_CH_RX_CONTROL_RxPBL(regval)           (BITS(16,22) & ((uint32_t)(regval) << 16))                          /*!< write value to DMA_CH_RX_CONTROL_RxPBL bit field */
#define ENET_RXDP_1BEAT                           DMA_CH_RX_CONTROL_RxPBL(1)                                          /*!< maximum number of beats 1 */
#define ENET_RXDP_2BEAT                           DMA_CH_RX_CONTROL_RxPBL(2)                                          /*!< maximum number of beats 2 */
#define ENET_RXDP_4BEAT                           DMA_CH_RX_CONTROL_RxPBL(4)                                          /*!< maximum number of beats 4 */
#define ENET_RXDP_8BEAT                           DMA_CH_RX_CONTROL_RxPBL(8)                                          /*!< maximum number of beats 8 */
#define ENET_RXDP_16BEAT                          DMA_CH_RX_CONTROL_RxPBL(16)                                         /*!< maximum number of beats 16 */
#define ENET_RXDP_32BEAT                          DMA_CH_RX_CONTROL_RxPBL(32)                                         /*!< maximum number of beats 32 */
#define ENET_RXDP_8xPGBL_8BEAT                    (DMA_CH_RX_CONTROL_RxPBL(1)|(ENET_DMA_CH_CONTROL_PBLx8<<7))         /*!< maximum number of beats 4 */
#define ENET_RXDP_8xPGBL_16BEAT                   (DMA_CH_RX_CONTROL_RxPBL(2)|(ENET_DMA_CH_CONTROL_PBLx8<<7))         /*!< maximum number of beats 8 */
#define ENET_RXDP_8xPGBL_32BEAT                   (DMA_CH_RX_CONTROL_RxPBL(4)|(ENET_DMA_CH_CONTROL_PBLx8<<7))         /*!< maximum number of beats 16 */
#define ENET_RXDP_8xPGBL_64BEAT                   (DMA_CH_RX_CONTROL_RxPBL(8)|(ENET_DMA_CH_CONTROL_PBLx8<<7))         /*!< maximum number of beats 32 */
#define ENET_RXDP_8xPGBL_128BEAT                  (DMA_CH_RX_CONTROL_RxPBL(16)|(ENET_DMA_CH_CONTROL_PBLx8<<7))        /*!< maximum number of beats 64 */
#define ENET_RXDP_8xPGBL_256BEAT                  (DMA_CH_RX_CONTROL_RxPBL(32)|(ENET_DMA_CH_CONTROL_PBLx8<<7))        /*!< maximum number of beats 128 */  
#define DMA_CH_RX_CONTROL_RBSZ(regval)                (BITS(1,14) & ((uint32_t)(regval) << 1))                        /*!< write value to DMA_CH_RX_CONTROL_RBSZ bit field */

/* DMA channel transmit descriptor ring length register value */
#define DMA_CH_TXDESC_RING_LENGTH_TDRL(regval)        (BITS(0,9) & ((uint32_t)(regval) << 0))           /*!< write value to ENET_DMA_CH0_TXDESC_RING_LENGTH_TDRL bit field */

/* DMA channel receive control 2 register value */
#define DMA_CH_RX_CONTROL2_RDRL(regval)               (BITS(0,9) & ((uint32_t)(regval) << 0))           /*!< write value to ENET_DMA_CH0_RX_CONTROL2_RDRL bit field */
#define DMA_CH_RX_CONTROL2_ARBS(regval)               (BITS(17,23) & ((uint32_t)(regval) << 17))        /*!< write value to ENET_DMA_CH0_RX_CONTROL2_ARBS bit field */

/* DMA channel receive interrupt watchdog timer register value */
#define DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWT(regval) (BITS(0,7) & ((uint32_t)(regval) << 0))          /*!< write value to ENET_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWT bit field */

#define DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWTU(regval)   (BITS(16,17) & ((uint32_t)(regval) << 16))          /*!< write value to ENET_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWTU bit field */
#define ENET_RX_INT_WATCHDOG_TIMER_COUNT_256              DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWTU(0)          /*!< 256 system clock cycles corresponding to one unit in RWT field */
#define ENET_RX_INT_WATCHDOG_TIMER_COUNT_512              DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWTU(1)          /*!< 512 system clock cycles corresponding to one unit in RWT field */
#define ENET_RX_INT_WATCHDOG_TIMER_COUNT_1024             DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWTU(2)          /*!< 1024 system clock cycles corresponding to one unit in RWT field */
#define ENET_RX_INT_WATCHDOG_TIMER_COUNT_2048             DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_RWTU(3)          /*!< 2048 system clock cycles corresponding to one unit in RWT field */

/* DMA channel slot function control status register value */
#define GET_REF_SLOT_NUMBER(regval)                      GET_BITS((regval),16,19)         /*!< get value of ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_RSN bit field */
#define DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_SIV(regval) (BITS(4,15) & ((uint32_t)(regval) << 4))           /*!< write value to ENET_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_SIV bit field */

#define ENET_DMA_ADVANCE_SLOT_CHECK_ENABLE               BIT(1)                                           /*!< advance slot check is enabled */
#define ENET_DMA_ADVANCE_SLOT_CHECK_DISABLE              (uint32_t)0x00000000)                            /*!< advance slot check is disable */
#define ENET_DMA_ADVANCE_SLOT_CHECK                      ENET_DMA_ADVANCE_SLOT_CHECK_ENABLE               /*!< advance slot check function */

#define ENET_DMA_SLOT_COMPARISON_ENABLE                  BIT(0)                                           /*!< slot comparison is enabled */
#define ENET_DMA_SLOT_COMPARISON_DISABLE                 (uint32_t)0x00000000)                            /*!< slot comparison is disable */
#define ENET_DMA_SLOT_COMPARISON                         ENET_DMA_SLOT_COMPARISON_ENABLE                  /*!< slot comparison function */

/* DMA channel miss frame counter register value */
#define GET_DMA_CH_MISS_FRAME_CNT_MFC(regval)           GET_BITS((regval),0,10)                           /*!< get value of ENET_DMA_CH(#i)_MISS_FRAME_CNT_MFC bit field */

#define ENET_DMA_CH_MFC_COUNTER_OVERFLOW                BIT(15)                                           /*!< miss frame counter overflow occurred */

/* DMA channel receive parser accept counter register value */
#define GET_DMA_CH_RXP_ACCEPT_CNT_RXPAC(regval)         GET_BITS((regval),0,30)                           /*!< get value of ENET_DMA_CH(#i)_RXP_ACCEPT_CNT_RXPAC bit field */

#define ENET_RXP_ACCEPT_COUNTER_OVERFLOW                BIT(31)                                           /*!< Rx parser accept counter overflow occurred */

/* define bit position and its register index offset */
#define ENET_REGIDX_BIT(regidx, bitpos)  (((uint32_t)(regidx) << 6) | (uint32_t)(bitpos))
#define ENET_REG_VAL(periph)             (REG32(ENET + ((uint32_t)(periph) >> 6)))
#define ENET_BIT_POS(val)                ((uint32_t)(val) & 0x1FU)

/* register offset */
#define DMA_CH0_TDTADDR_REG_OFFSET           ((uint16_t)0x1114U)                                /*!< DMA channel 0 transmit descriptor table address register offset */
#define DMA_CH1_TDTADDR_REG_OFFSET           ((uint16_t)0x1194U)                                /*!< DMA channel 1 transmit descriptor table address register offset */
#define DMA_CH0_TDTAIL_REG_OFFSET            ((uint16_t)0x1120U)                                /*!< DMA channel 0 transmit descriptor tail pointer address register offset */
#define DMA_CH1_TDTAIL_REG_OFFSET            ((uint16_t)0x11A0U)                                /*!< DMA channel 1 transmit descriptor tail pointer  address register offset */
#define DMA_CH0_CTDADDR_REG_OFFSET           ((uint16_t)0x1144U)                                /*!< DMA channel 0 current transmit descriptor address register offset */
#define DMA_CH1_CTDADDR_REG_OFFSET           ((uint16_t)0x11C4U)                                /*!< DMA channel 1 current transmit descriptor address register offset */
#define DMA_CH0_CTBADDR_REG_OFFSET           ((uint16_t)0x1154U)                                /*!< DMA channel 0 current transmit buffer address register offset */
#define DMA_CH1_CTBADDR_REG_OFFSET           ((uint16_t)0x11D4U)                                /*!< DMA channel 1 current transmit buffer address register offset */

#define DMA_CH0_RDTADDR_REG_OFFSET           ((uint16_t)0x111CU)                                /*!< DMA channel 0 receive descriptor table address register offset */
#define DMA_CH1_RDTADDR_REG_OFFSET           ((uint16_t)0x119CU)                                /*!< DMA channel 1 receive descriptor table address register offset */
#define DMA_CH0_RDTAIL_REG_OFFSET            ((uint16_t)0x1128U)                                /*!< DMA channel 0 receive descriptor tail pointer address register offset */
#define DMA_CH1_RDTAIL_REG_OFFSET            ((uint16_t)0x11A8U)                                /*!< DMA channel 1 receive descriptor tail pointer  address register offset */
#define DMA_CH0_CRDADDR_REG_OFFSET           ((uint16_t)0x114CU)                                /*!< DMA channel 0 current receive descriptor address register offset */
#define DMA_CH1_CRDADDR_REG_OFFSET           ((uint16_t)0x11CCU)                                /*!< DMA channel 1 current receive descriptor address register offset */
#define DMA_CH0_CRBADDR_REG_OFFSET           ((uint16_t)0x115CU)                                /*!< DMA channel 0 current receive buffer address register offset */
#define DMA_CH1_CRBADDR_REG_OFFSET           ((uint16_t)0x11DCU)                                /*!< DMA channel 1 current receive buffer address register offset */

#define MAC_INTERRUPT_STATUS_REG_OFFSET          ((uint16_t)0x00B0U)                                /*!<MAC interrupt status register offset */
#define MAC_INTERRUPT_ENABLE_REG_OFFSET          ((uint16_t)0x00B4U)                                /*!< MAC interrupts enable register offset */
#define MAC_RX_TX_STATUS_REG_OFFSET              ((uint16_t)0x00B8U)                                /*!< The receive transmit satus register offset */
#define MAC_PMT_CONTROL_STATUS_REG_OFFSET        ((uint16_t)0x00C0U)                                /*!< MAC PMT control and status register offset */
#define MAC_LPI_CONTROL_STATUS_REG_OFFSET        ((uint16_t)0x00D0U)                                /*!< MAC LPI control and status register offset */
#define MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET  ((uint16_t)0x0140U)                                /*!< MAC DPP FSM interrupt status register offset */
#define MAC_FPE_CTRL_STS_REG_OFFSET              ((uint16_t)0x0234U)                                /*!< MAC FPE control status register offset */
#define MAC_TIMESTAMP_STATUS_REG_OFFSET          ((uint16_t)0x0B20U)                                /*!< MAC timestamp status register offset */
#define MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_REG_OFFSET   ((uint16_t)0x0B30U)                        /*!< MAC transmit timestamp status in nanoseconds register offset */
#define MTL_DBG_STS_REG_OFFSET                   ((uint16_t)0x0C0CU)                                /*!< MTL debug status register offset */

#define MMC_RX_INTERRUPT_REG_OFFSET                ((uint16_t)0x0704U)                              /*!< MMC receive interrupts enable register offset */
#define MMC_TX_INTERRUPT_REG_OFFSET                ((uint16_t)0x0708U)                              /*!< MMC transimit interrupts enable register offset */
#define MMC_RX_INTERRUPT_MASK_REG_OFFSET           ((uint16_t)0x070CU)                              /*!< MMC transimit interrupts mask register offset */
#define MMC_TX_INTERRUPT_MASK_REG_OFFSET           ((uint16_t)0x0710U)                              /*!< MMC transimit interrupts mask register offset */

#define MMC_TX_OCTET_COUNT_GOOD_BAD_REG_OFFSET               ((uint16_t)0x0714U)            /*!< ethernet transmit octet count good bad register offset */
#define MMC_TX_PACKET_COUNT_GOOD_BAD_REG_OFFSET              ((uint16_t)0x0718U)            /*!< ethernet transmit packet count good bad register offset */
#define MMC_TX_BROADCAST_PACKETS_GOOD_REG_OFFSET             ((uint16_t)0x071CU)            /*!< ethernet transmit broadcast packets good register offset */
#define MMC_TX_MULTICAST_PACKETS_GOOD_REG_OFFSET             ((uint16_t)0x0720U)            /*!< ethernet transmit multicast packets good register offset */
#define MMC_TX_64OCTETS_PACKETS_GOOD_BAD_REG_OFFSET          ((uint16_t)0x0724U)            /*!< ethernet transmit 64 octet packets good bad register offset */
#define MMC_TX_65TO127OCTET_PACKETS_GOOD_BAD_REG_OFFSET      ((uint16_t)0x0728U)            /*!< ethernet transmit 65 to 127 octet packets good bad register offset */
#define MMC_TX_128TO255OCTET_PACKETS_GOOD_BAD_REG_OFFSET     ((uint16_t)0x072CU)            /*!< ethernet transmit 128 to 255 octet packets good bad register offset */
#define MMC_TX_256TO511OCTET_PACKETS_GOOD_BAD_REG_OFFSET     ((uint16_t)0x0730U)            /*!< ethernet transmit 256 to 511 octet packets good bad register offset */
#define MMC_TX_512TO1023OCTET_PACKETS_GOOD_BAD_REG_OFFSET    ((uint16_t)0x0734U)            /*!< ethernet transmit 512 to 1023 octet packets good bad register offset */
#define MMC_TX_1024TOMAXOCTET_PACKETS_GOOD_BAD_REG_OFFSET    ((uint16_t)0x0738U)            /*!< ethernet transmit 1024 to max octet packets good bad register offset */
#define MMC_TX_UNICAST_PACKETS_GOOD_BAD_REG_OFFSET           ((uint16_t)0x073CU)            /*!< ethernet transmit unicast packets good bad register offset */
#define MMC_TX_MULTICAST_PACKETS_GOOD_BAD_REG_OFFSET         ((uint16_t)0x0740U)            /*!< ethernet transmit multicast packets good bad register offset */
#define MMC_TX_BROADCAST_PACKETS_GOOD_BAD_REG_OFFSET         ((uint16_t)0x0744U)            /*!< ethernet transmit broadcast packets good bad register offset */
#define MMC_TX_UNDERFLOW_ERROR_PACKETS_REG_OFFSET            ((uint16_t)0x0748U)            /*!< ethernet transmit underflow error packets register offset */
#define MMC_TX_SINGLE_COLLISION_GOOD_PACKETS_REG_OFFSET      ((uint16_t)0x074CU)            /*!< ethernet transmit single collision good packets register offset */
#define MMC_TX_MULTIPLE_COLLISION_GOOD_PACKETS_REG_OFFSET    ((uint16_t)0x0750U)            /*!< ethernet transmit multiple collision good packets register offset */
#define MMC_TX_DEFERRED_PACKETS_REG_OFFSET                   ((uint16_t)0x0754U)            /*!< ethernet transmit deferred packets register offset */
#define MMC_TX_LATE_COLLISION_PACKETS_REG_OFFSET             ((uint16_t)0x0758U)            /*!< ethernet transmit late collision packets register offset */
#define MMC_TX_EXCESSIVE_COLLISION_PACKETS_REG_OFFSET        ((uint16_t)0x075CU)            /*!< ethernet transmit excessive collision packets register offset */
#define MMC_TX_CARRIER_ERROR_PACKETS_REG_OFFSET              ((uint16_t)0x0760U)            /*!< ethernet transmit carrier error packets register offset */
#define MMC_TX_OCTET_COUNT_GOOD_REG_OFFSET                   ((uint16_t)0x0764U)            /*!< ethernet transmit octet count good register offset */
#define MMC_TX_PACKET_COUNT_GOOD_REG_OFFSET                  ((uint16_t)0x0768U)            /*!< ethernet transmit packet count good register offset */
#define MMC_TX_EXCESSIVE_DEFERRAL_ERROR_REG_OFFSET           ((uint16_t)0x076CU)            /*!< ethernet transmit excessive deferral error register offset */
#define MMC_TX_PAUSE_PACKETS_REG_OFFSET                      ((uint16_t)0x0770U)            /*!< ethernet transmit pause packets register offset */
#define MMC_TX_VLAN_PACKETS_GOOD_REG_OFFSET                  ((uint16_t)0x0774U)            /*!< ethernet transmit vlan packets good register offset */
#define MMC_TX_OSIZE_PACKETS_GOOD_REG_OFFSET                 ((uint16_t)0x0778U)            /*!< ethernet transmit oversize packets good register offset */
#define MMC_RX_PACKETS_COUNT_GOOD_BAD_REG_OFFSET             ((uint16_t)0x0780U)            /*!< ethernet receive packet count good bad register offset */
#define MMC_RX_OCTET_COUNT_GOOD_BAD_REG_OFFSET               ((uint16_t)0x0784U)            /*!< ethernet receive octet count good bad register offset */
#define MMC_RX_OCTET_COUNT_GOOD_REG_OFFSET                   ((uint16_t)0x0788U)            /*!< ethernet receive octet count good register offset */
#define MMC_RX_BROADCAST_PACKETS_GOOD_REG_OFFSET             ((uint16_t)0x078CU)            /*!< ethernet receive broadcast packets good register offset */
#define MMC_RX_MULTICAST_PACKETS_GOOD_REG_OFFSET             ((uint16_t)0x0790U)            /*!< ethernet receive multicast packets good register offset */
#define MMC_RX_CRC_ERROR_PACKETS_REG_OFFSET                  ((uint16_t)0x0794U)            /*!< ethernet receive crc error packets register offset */
#define MMC_RX_ALIGNMENT_ERROR_PACKETS_REG_OFFSET            ((uint16_t)0x0798U)            /*!< ethernet receive alignment error packets register offset */
#define MMC_RX_RUNT_ERROR_PACKETS_REG_OFFSET                 ((uint16_t)0x079CU)            /*!< ethernet receive runt error packets register offset */
#define MMC_RX_JABBER_ERROR_PACKETS_REG_OFFSET               ((uint16_t)0x07A0U)            /*!< ethernet receive jabber error packets register offset */
#define MMC_RX_UNDERSIZE_PACKETS_GOOD_REG_OFFSET             ((uint16_t)0x07A4U)            /*!< ethernet receive undersize packets good register offset */
#define MMC_RX_OVERSIZE_PACKETS_GOOD_REG_OFFSET              ((uint16_t)0x07A8U)            /*!< ethernet receive oversize packets good register offset */
#define MMC_RX_64OCTET_PACKETS_GOOD_BAD_REG_OFFSET           ((uint16_t)0x07ACU)            /*!< ethernet receive 64 octet packets good bad register offset */
#define MMC_RX_65TO127OCTET_PACKETS_GOOD_BAD_REG_OFFSET      ((uint16_t)0x07B0U)            /*!< ethernet receive 65 to 127 octet packets good bad register offset */
#define MMC_RX_128TO255OCTET_PACKETS_GOOD_BAD_REG_OFFSET     ((uint16_t)0x07B4U)            /*!< ethernet receive 128 to 255 octet packets good bad register offset */
#define MMC_RX_256TO511OCTET_PACKETS_GOOD_BAD_REG_OFFSET     ((uint16_t)0x07B8U)            /*!< ethernet receive 256 to 511 octet packets good bad register offset */
#define MMC_RX_512TO1023OCTET_PACKETS_GOOD_BAD_REG_OFFSET    ((uint16_t)0x07BCU)            /*!< ethernet receive 512 to 1023 octet packets good bad register offset */
#define MMC_RX_1024TOMAXOCTET_PACKETS_GOOD_BAD_REG_OFFSET    ((uint16_t)0x07C0U)            /*!< ethernet receive 1024 to max octet packets good bad register offset */
#define MMC_RX_UNICAST_PACKETS_GOOD_REG_OFFSET               ((uint16_t)0x07C4U)            /*!< ethernet receive unicast packets good register offset */
#define MMC_RX_LENGTH_ERROR_PACKETS_REG_OFFSET               ((uint16_t)0x07C8U)            /*!< ethernet receive length error packets register offset */
#define MMC_RX_OUT_OF_RANGE_TYPE_PACKETS_REG_OFFSET          ((uint16_t)0x07CCU)            /*!< ethernet receive out of range type packets register offset */
#define MMC_RX_PAUSE_PACKETS_REG_OFFSET                      ((uint16_t)0x07D0U)            /*!< ethernet receive pause packets register offset */
#define MMC_RX_FIFO_OVERFLOW_PACKETS_REG_OFFSET              ((uint16_t)0x07D4U)            /*!< ethernet receive fifo overflow packets register offset */
#define MMC_RX_VLAN_PACKETS_GOOD_BAD_REG_OFFSET              ((uint16_t)0x07D8U)            /*!< ethernet receive vlan packets good bad register offset */
#define MMC_RX_WATCHDOG_ERROR_PACKETS_REG_OFFSET             ((uint16_t)0x07DCU)            /*!< ethernet receive watchdog error packets register offset */
#define MMC_RX_ERROR_PACKETS_REG_OFFSET                      ((uint16_t)0x07E0U)            /*!< ethernet receive error packets register offset */
#define MMC_RX_CONTROL_PACKETS_GOOD_REG_OFFSET               ((uint16_t)0x07E4U)            /*!< ethernet receive control packets good register offset */

#define ENET_TX_LPI_USEC_CNTR_REG_OFFSET                     ((uint16_t)0x07ECU)            /*!< ethernet transmit LPI microseconds counter register offset */
#define ENET_TX_LPI_TRAN_CNTR_REG_OFFSET                     ((uint16_t)0x07F0U)            /*!< ethernet transmit LPI transition counter register offset */
#define ENET_RX_LPI_USEC_CNTR_REG_OFFSET                     ((uint16_t)0x07F4U)            /*!< ethernet receive LPI microseconds counter register offset */
#define ENET_RX_LPI_TRAN_CNTR_REG_OFFSET                     ((uint16_t)0x07F8U)            /*!< ethernet receive LPI transition counter register offset */
#define MMC_RXIPV4_GOOD_PACKETS_REG_OFFSET                   ((uint16_t)0x0810U)            /*!< ethernet receive ipv4 good packets register */
#define MMC_RXIPV4_HEADER_ERROR_PACKETS_REG_OFFSET           ((uint16_t)0x0814U)            /*!< ethernet receive ipv4 header error packets register */
#define MMC_RXIPV4_NO_PAYLOAD_PACKETS_REG_OFFSET             ((uint16_t)0x0818U)            /*!< ethernet receive ipv4 no payload packets register */
#define MMC_RXIPV4_FRAGMENTED_PACKETS_REG_OFFSET             ((uint16_t)0x081CU)            /*!< ethernet receive ipv4 fragmented packets register */
#define MMC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_REG_OFFSET  ((uint16_t)0x0820U)            /*!< ethernet receive ipv4 udp checksum disabled packets register */
#define MMC_RXIPV6_GOOD_PACKETS_REG_OFFSET                   ((uint16_t)0x0824U)            /*!< ethernet receive ipv6 good packets register */
#define MMC_RXIPV6_HEADER_ERROR_PACKETS_REG_OFFSET           ((uint16_t)0x0828U)            /*!< ethernet receive ipv6 header error packets register */
#define MMC_RXIPV6_NO_PAYLOAD_PACKETS_REG_OFFSET             ((uint16_t)0x082CU)            /*!< ethernet receive ipv6 no payload packets register */
#define MMC_RXUDP_GOOD_PACKETS_REG_OFFSET                    ((uint16_t)0x0830U)            /*!< ethernet receive udp good packets register */
#define MMC_RXUDP_ERROR_PACKETS_REG_OFFSET                   ((uint16_t)0x0834U)            /*!< ethernet receive udp error packets register */
#define MMC_RXTCP_GOOD_PACKETS_REG_OFFSET                    ((uint16_t)0x0838U)            /*!< ethernet receive tcp good packets register */
#define MMC_RXTCP_ERROR_PACKETS_REG_OFFSET                   ((uint16_t)0x083CU)            /*!< ethernet receive tcp error packets register */
#define MMC_RXICMP_GOOD_PACKETS_REG_OFFSET                   ((uint16_t)0x0840U)            /*!< ethernet receive icmp good packets register */
#define MMC_RXICMP_ERROR_PACKETS_REG_OFFSET                  ((uint16_t)0x0844U)            /*!< ethernet receive icmp error packets register */
#define MMC_RXIPV4_GOOD_OCTETS_REG_OFFSET                    ((uint16_t)0x0850U)            /*!< ethernet receive ipv4 good octets register */
#define MMC_RXIPV4_HEADER_ERROR_OCTETS_REG_OFFSET            ((uint16_t)0x0854U)            /*!< ethernet receive ipv4 header error octets register */
#define MMC_RXIPV4_NO_PAYLOAD_OCTETS_REG_OFFSET              ((uint16_t)0x0858U)            /*!< ethernet receive ipv4 no payload octets register */
#define MMC_RXIPV4_FRAGMENTED_OCTETS_REG_OFFSET              ((uint16_t)0x085CU)            /*!< ethernet receive ipv4 fragmented octets register */
#define MMC_RXIPV4_UDP_CHECKSUM_DISABLED_OCTETS_REG_OFFSET   ((uint16_t)0x0860U)            /*!< ethernet receive ipv4 udp checksum disabled octets register */
#define MMC_RXIPV6_GOOD_OCTETS_REG_OFFSET                    ((uint16_t)0x0864U)            /*!< ethernet receive ipv6 good octets register */
#define MMC_RXIPV6_HEADER_ERROR_OCTETS_REG_OFFSET            ((uint16_t)0x0868U)            /*!< ethernet receive ipv6 header error octets register */
#define MMC_RXIPV6_NO_PAYLOAD_OCTETS_REG_OFFSET              ((uint16_t)0x086CU)            /*!< ethernet receive ipv6 no payload octets register */
#define MMC_RXUDP_GOOD_OCTETS_REG_OFFSET                     ((uint16_t)0x0870U)            /*!< ethernet receive udp good octets register */
#define MMC_RXUDP_ERROR_OCTETS_REG_OFFSET                    ((uint16_t)0x0874U)            /*!< ethernet receive udp error octets register */
#define MMC_RXTCP_GOOD_OCTETS_REG_OFFSET                     ((uint16_t)0x0878U)            /*!< ethernet receive tcp good octets register */
#define MMC_RXTCP_ERROR_OCTETS_REG_OFFSET                    ((uint16_t)0x087CU)            /*!< ethernet receive tcp error octets register */
#define MMC_RXICMP_GOOD_OCTETS_REG_OFFSET                    ((uint16_t)0x0880U)            /*!< ethernet receive icmp good octets register */
#define MMC_RXICMP_ERROR_OCTETS_REG_OFFSET                   ((uint16_t)0x0884U)            /*!< ethernet receive icmp error octets register */
#define MMC_MMC_FPE_TX_FRAGMENT_CNTR_REG_OFFSET              ((uint16_t)0x08A8U)            /*!< ethernet MMC FPE transmit fragment counter register */
#define MMC_MMC_TX_HOLD_REQ_CNTR_REG_OFFSET                  ((uint16_t)0x08ACU)            /*!< ethernet MMC FPE hold request counter register */
#define MMC_RX_PACKETS_ASSEMBLY_ERR_CNTR_REG_OFFSET          ((uint16_t)0x08C8U)            /*!< ethernet MMC receive packets assembly error counter register */
#define MMC_RX_PACKETS_SMD_ERR_CNTR_REG_OFFSET               ((uint16_t)0x08CCU)            /*!< ethernet MMC receive packets SMD error counter register */
#define MMC_RX_PACKETS_ASSEMBLY_OK_CNTR_REG_OFFSET           ((uint16_t)0x08D0U)            /*!< ethernet MMC receive packets assembly ok counter register */
#define MMC_RX_FPE_FRAGMENT_CNTR_REG_OFFSET                  ((uint16_t)0x08D4U)            /*!< ethernet MMC receive FPE fragment counter register */

#define MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET                 ((uint16_t)0x0800U)            /*!< MTL FPE transimit interrupts mask register offset */
#define MMC_IPC_RX_INTERRUPT_REG_OFFSET                      ((uint16_t)0x0808U)            /*!< MTL FPE transimit interrupts mask register offset */

#define MMC_FPE_TX_INTERRUPT_REG_OFFSET                      ((uint16_t)0x08A0U)            /*!< MMC transmit FPE fragment counter interrupt status register offset */
#define MMC_FPE_TX_INTERRUPT_MASK_REG_OFFSET                 ((uint16_t)0x08A4U)            /*!< MTL FPE transimit interrupts mask register offset */
#define MMC_FPE_RX_INTERRUPT_REG_OFFSET                      ((uint16_t)0x08C0U)            /*!< MMC receive packet assembly error counter interrupt register offset */
#define MMC_FPE_RX_INTERRUPT_MASK_REG_OFFSET                 ((uint16_t)0x08C4U)            /*!< MMC FPE receive interrupt mask register offset */
#define MTL_DBG_CTL_REG_OFFSET                               ((uint16_t)0x0C08U)            /*!<MTL debug control register offset */
#define MTL_INTERRUPT_STATUS_REG_OFFSET                      ((uint16_t)0x0C20U)            /*!< MTL interrupt status register offset */
#define MTL_EST_STATUS_REG_OFFSET                            ((uint16_t)0x0C58U)            /*!< MTL EST status register offset */
#define MTL_FPE_CTRL_STS_REG_OFFSET                          ((uint16_t)0x0C90U)            /*!< MTL FPE control status register offset */
#define MTL_RXP_CONTROL_STATUS_REG_OFFSET                    ((uint16_t)0x0CA0U)            /*!< MTL Rx parser control status register offset */
#define MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET          ((uint16_t)0x0CA4U)            /*!< MTL Rx parser control status register offset */
#define MTL_SAFETY_INTERRUPT_STATUS_REG_OFFSET               ((uint16_t)0x0CC4U)            /*!< MTL Rx parser control status register offset */
#define MTL_ECC_INTERRUPT_ENABLE_REG_OFFSET                  ((uint16_t)0x0CC8U)            /*!< MTL ECC interrupt enable register offset */
#define MTL_ECC_INTERRUPT_STATUS_REG_OFFSET                  ((uint16_t)0x0CCCU)            /*!< MTL ECC interrupt status register offset */
#define MTL_EST_INTERRUPT_ENABLE_REG_OFFSET                  ((uint16_t)0x0C70U)            /*!< MTL EST interrupts enable register offset */
#define MTL_TXQ0_UNDERFLOW_REG_OFFSET                        ((uint16_t)0x0D04U)            /*!< MTL transmit queue 0 underflow counter register offset */
#define MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_REG_OFFSET       ((uint16_t)0x0D34U)            /*!< MTL receive queue 0 missed frame overflow counter register offset */
#define MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET           ((uint16_t)0x0D2CU)            /*!< MTL queue 0 interrupts enable and status register offset */
#define MTL_TXQ1_UNDERFLOW_REG_OFFSET                        ((uint16_t)0x0D44U)            /*!< MTL transmit queue 1 underflow counter register offset */
#define MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_REG_OFFSET       ((uint16_t)0x0D74U)            /*!< MTL receive queue 1 missed frame overflow counter register offset */
#define MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET           ((uint16_t)0x0D6CU)            /*!< MTL queue 1 interrupts enable and status register offset */
#define DMA_INTERRUPT_STATUS_REG_OFFSET                      ((uint16_t)0x1008U)            /*!< DMA interrupt status register offset */
#define DMA_SAFETY_INTERRUPT_STATUS_REG_OFFSET               ((uint16_t)0x1080U)            /*!< DDMA safety interrupt status register offset */
#define DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET                  ((uint16_t)0x1134U)            /*!< DMA channel 0 interrupt enable register offset */
#define DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET                  ((uint16_t)0x11B4U)            /*!< DMA channel 1 interrupt enable register offset */

#define DMA_CH0_STATUS_REG_OFFSET           ((uint16_t)0x1160U)                             /*!< DMA channel 0 status register offset */
#define DMA_CH0_MISS_FRAME_CNT_REG_OFFSET   ((uint16_t)0x1164U)                             /*!< DMA channel 0 miss frame counter register offset */
#define DMA_CH0_RXP_ACCEPT_CNT_REG_OFFSET   ((uint16_t)0x1168U)                             /*!< DMA channel 0 receive parser accept counter register offset */
#define DMA_CH1_STATUS_REG_OFFSET           ((uint16_t)0x11E0U)                             /*!< DMA channel 1 status register offset */
#define DMA_CH1_MISS_FRAME_CNT_REG_OFFSET   ((uint16_t)0x11E4U)                             /*!< DMA channel 1 miss frame counter register offset */
#define DMA_CH1_RXP_ACCEPT_CNT_REG_OFFSET   ((uint16_t)0x11E8U)                             /*!< DMA channel 1 receive parser accept counter register offset */

/* define MAC address configuration and reference address */
#define ENET_SET_MACADDRH(p)                 (((uint32_t)(p)[5] << 8) | (uint32_t)(p)[4])
#define ENET_SET_MACADDRL(p)                 (((uint32_t)(p)[3] << 24) | ((uint32_t)(p)[2] << 16) | ((uint32_t)(p)[1] << 8) | (uint32_t)(p)[0])
#define ENET_SET_IPV4ADDR(p)                 (((uint32_t)(p)[3] << 24) | ((uint32_t)(p)[2] << 16) | ((uint32_t)(p)[1] << 8) | (uint32_t)(p)[0])
#define ENET_SET_IPV6ADDR(p)                 (((uint32_t)(p)[3] << 24) | ((uint32_t)(p)[2] << 16) | ((uint32_t)(p)[1] << 8) | (uint32_t)(p)[0])
#define ENET_ADDRH_BASE                      ((ENET) + 0x300U)
#define ENET_ADDRL_BASE                      ((ENET) + 0x304U)
#define ENET_GET_MACADDR(offset, n)          ((uint8_t)((REG32((ENET_ADDRL_BASE + (offset)) - (((n) / 4U) * 4U)) >> (8U * ((n) % 4U))) & 0xFFU))

typedef enum {
    CVLAN = 0U,         /*!< C-VLAN */
    SVLAN = 1U          /*!< S-VLAN */
} enet_vlantype_enum;

/* ENET status flag get */
typedef enum {
    /* MAC_RX_TX_STATUS register */
    ENET_MAC_RX_TX_STATUS_FLAG_TJT                   = ENET_REGIDX_BIT(MAC_RX_TX_STATUS_REG_OFFSET, 0U),         /*!< transmit jabber timeout status flag */
    ENET_MAC_RX_TX_STATUS_FLAG_NCARR                 = ENET_REGIDX_BIT(MAC_RX_TX_STATUS_REG_OFFSET, 1U),         /*!< no carrier status flag */
    ENET_MAC_RX_TX_STATUS_FLAG_LCARR                 = ENET_REGIDX_BIT(MAC_RX_TX_STATUS_REG_OFFSET, 2U),         /*!< loss of carrier status flag */
    ENET_MAC_RX_TX_STATUS_FLAG_EXDEF                 = ENET_REGIDX_BIT(MAC_RX_TX_STATUS_REG_OFFSET, 3U),         /*!< excessive deferral status flag */
    ENET_MAC_RX_TX_STATUS_FLAG_LCOL                  = ENET_REGIDX_BIT(MAC_RX_TX_STATUS_REG_OFFSET, 4U),         /*!< late collision status flag */
    ENET_MAC_RX_TX_STATUS_FLAG_EXCOL                 = ENET_REGIDX_BIT(MAC_RX_TX_STATUS_REG_OFFSET, 5U),         /*!< excessive collisions status flag */
    ENET_MAC_RX_TX_STATUS_FLAG_RWT                   = ENET_REGIDX_BIT(MAC_RX_TX_STATUS_REG_OFFSET, 8U),         /*!< receive watchdog timeout status flag */
    
    /* MAC_PMT_CONTROL_STATUS register */
    ENET_MAC_PMT_CONTROL_STATUS_FLAG_MGKPRCVD        = ENET_REGIDX_BIT(MAC_PMT_CONTROL_STATUS_REG_OFFSET, 5U),   /*!< magic packet received flag */
    ENET_MAC_PMT_CONTROL_STATUS_FLAG_RWKPRCVD        = ENET_REGIDX_BIT(MAC_PMT_CONTROL_STATUS_REG_OFFSET, 6U),   /*!< remote wake-pp packet received flag */
    
    /* MAC_LPI_CONTROL_STATUS register */
    ENET_MAC_LPI_CONTROL_STATUS_FLAG_TLPIEN          = ENET_REGIDX_BIT(MAC_LPI_CONTROL_STATUS_REG_OFFSET, 0U),   /*!< transmit LPI entry flag */
    ENET_MAC_LPI_CONTROL_STATUS_FLAG_TLPIEX          = ENET_REGIDX_BIT(MAC_LPI_CONTROL_STATUS_REG_OFFSET, 1U),   /*!< transmit LPI exit flag */
    ENET_MAC_LPI_CONTROL_STATUS_FLAG_RLPIEN          = ENET_REGIDX_BIT(MAC_LPI_CONTROL_STATUS_REG_OFFSET, 2U),   /*!< receive LPI entry flag */
    ENET_MAC_LPI_CONTROL_STATUS_FLAG_RLPIEX          = ENET_REGIDX_BIT(MAC_LPI_CONTROL_STATUS_REG_OFFSET, 3U),   /*!< receive LPI exit flag */
    ENET_MAC_LPI_CONTROL_STATUS_FLAG_TLPIST          = ENET_REGIDX_BIT(MAC_LPI_CONTROL_STATUS_REG_OFFSET, 8U),   /*!< transmit LPI state flag */
    ENET_MAC_LPI_CONTROL_STATUS_FLAG_RLPIST          = ENET_REGIDX_BIT(MAC_LPI_CONTROL_STATUS_REG_OFFSET, 9U),   /*!< receive LPI state flag */
    ENET_MAC_LPI_CONTROL_STATUS_FLAG_PLS             = ENET_REGIDX_BIT(MAC_LPI_CONTROL_STATUS_REG_OFFSET, 17U),  /*!< PHY link status flag */
    
    /* MAC_FPE_CTRL_STS register */
    ENET_MAC_FPE_CTRL_STS_FLAG_RVER                  = ENET_REGIDX_BIT(MAC_FPE_CTRL_STS_REG_OFFSET, 16U),        /*!< received verify frame flag */
    ENET_MAC_FPE_CTRL_STS_FLAG_RRSP                  = ENET_REGIDX_BIT(MAC_FPE_CTRL_STS_REG_OFFSET, 17U),        /*!< received respond frame flag */
    ENET_MAC_FPE_CTRL_STS_FLAG_TVER                  = ENET_REGIDX_BIT(MAC_FPE_CTRL_STS_REG_OFFSET, 18U),        /*!< transmitted verify frame flag */
    ENET_MAC_FPE_CTRL_STS_FLAG_TRSP                  = ENET_REGIDX_BIT(MAC_FPE_CTRL_STS_REG_OFFSET, 19U),        /*!< transmitted respond frame flag */
    
    /* MAC_TIMESTAMP_STATUS register */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSSOVF            = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 0U),     /*!< timestamp seconds overflow flag */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTARGT0          = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 1U),     /*!< timestamp target time reached flag for target time PPS0 */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTRGTERR0        = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 3U),     /*!< timestamp target time error flag for target time PPS0 */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTARGT1          = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 4U),     /*!< timestamp target time reached flag for target time PPS1 */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTRGTERR1        = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 5U),     /*!< timestamp target time error flag for target time PPS1 */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTARGT2          = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 6U),     /*!< timestamp target time reached flag for target time PPS2 */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTRGTERR2        = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 7U),     /*!< timestamp target time error flag for target time PPS2 */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTARGT3          = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 8U),     /*!< timestamp target time reached flag for target time PPS3 */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TSTRGTERR3        = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 9U),     /*!< timestamp target time error flag for target time PPS3 */
    ENET_MAC_TIMESTAMP_STATUS_FLAG_TXTSSIS           = ENET_REGIDX_BIT(MAC_TIMESTAMP_STATUS_REG_OFFSET, 15U),    /*!< Tx timestamp status interrupt status flag */
    
    /* MAC_TX_TIMESTAMP_STATUS_NANOSECONDS register */
    ENET_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_FLAG_TXTSSMIS  = ENET_REGIDX_BIT(MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_REG_OFFSET, 31U),    /*!< transmit timestamp status missed status flag */
    
    /* MTL_DBG_STS register */
    ENET_MTL_DBG_STS_FLAG_PKTI                       = ENET_REGIDX_BIT(MTL_DBG_CTL_REG_OFFSET, 8U),         /*!< receive packet available interrupt status flag */
    ENET_MTL_DBG_STS_FLAG_STSI                       = ENET_REGIDX_BIT(MTL_DBG_CTL_REG_OFFSET, 9U),         /*!< transmit status available interrupt status flag */
    /* MTL_EST_STATUS register */
    ENET_MTL_EST_STATUS_FLAG_SWLC                    = ENET_REGIDX_BIT(MTL_EST_STATUS_REG_OFFSET, 0U),         /*!< switch to S/W owned list complete flag */
    ENET_MTL_EST_STATUS_FLAG_BTRE                    = ENET_REGIDX_BIT(MTL_EST_STATUS_REG_OFFSET, 1U),         /*!< BTR error flag */
    ENET_MTL_EST_STATUS_FLAG_HLBF                    = ENET_REGIDX_BIT(MTL_EST_STATUS_REG_OFFSET, 2U),         /*!< Head-Of-Line blocking due to frame size flag */
    ENET_MTL_EST_STATUS_FLAG_HLBS                    = ENET_REGIDX_BIT(MTL_EST_STATUS_REG_OFFSET, 3U),         /*!< Head-Of-Line blocking due to scheduling flag */
    ENET_MTL_EST_STATUS_FLAG_CGCE                    = ENET_REGIDX_BIT(MTL_EST_STATUS_REG_OFFSET, 4U),         /*!< constant gate control error flag */
    /* MTL_FPE_CTRL_STS register */
    ENET_MTL_FPE_CTRL_STS_FLAG_HRS                   = ENET_REGIDX_BIT(MTL_FPE_CTRL_STS_REG_OFFSET, 28U),        /*!< hold/release status flag */
    /* MTL_RXP_CONTROL_STATUS register */
    ENET_MTL_RXP_CONTROL_STATUS_FLAG_RXPI            = ENET_REGIDX_BIT(MTL_FPE_CTRL_STS_REG_OFFSET, 31U),        /*!< RX parser in idle state flag */
    /* MTL_TXQ0_UNDERFLOW_REG_OFFSET register */
    ENET_MTL_TXQ0_UNDERFLOW_FLAG_UFCNTOVF            = ENET_REGIDX_BIT(MTL_TXQ0_UNDERFLOW_REG_OFFSET, 11U),        /*!< underflow packet counter overflow flag */
    /* MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_REG_OFFSET register */
    ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_FLAG_OVFCNTOVF  = ENET_REGIDX_BIT(MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_REG_OFFSET, 11U),        /*!< overflow counter overflow flag */
    ENET_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_FLAG_MISCNTOVF  = ENET_REGIDX_BIT(MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_REG_OFFSET, 27U),        /*!< missed packet counter overflow flag */
    /* MTL_TXQ0_UNDERFLOW_REG_OFFSET register */
    ENET_MTL_TXQ1_UNDERFLOW_FLAG_UFCNTOVF            = ENET_REGIDX_BIT(MTL_TXQ1_UNDERFLOW_REG_OFFSET, 11U),        /*!< underflow packet counter overflow flag */
    /* MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_REG_OFFSET register */
    ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_FLAG_OVFCNTOVF  = ENET_REGIDX_BIT(MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_REG_OFFSET, 11U),        /*!< overflow counter overflow flag */
    ENET_MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_FLAG_MISCNTOVF  = ENET_REGIDX_BIT(MTL_RXQ1_MISSED_PACKET_OVERFLOW_CNT_REG_OFFSET, 27U),        /*!< missed packet counter overflow flag */
    /* DMA_CH0_STATUS register */
    ENET_DMA_CH0_FLAG_TI            = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 0U),     /*!< channel 0 transmit status flag */
    ENET_DMA_CH0_FLAG_TPS           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 1U),     /*!< channel 0 transmit process stopped status flag */
    ENET_DMA_CH0_FLAG_TBU           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 2U),     /*!< channel 0 transmit buffer unavailable status flag */
    ENET_DMA_CH0_FLAG_RI            = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 6U),     /*!< channel 0 receive status flag */
    ENET_DMA_CH0_FLAG_RBU           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 7U),     /*!< channel 0 receive buffer unavailable status flag */
    ENET_DMA_CH0_FLAG_RPS           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 8U),     /*!< channel 0 receive process stopped status flag */
    ENET_DMA_CH0_FLAG_RWT           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 9U),     /*!< channel 0 receive watchdog timeout status flag */
    ENET_DMA_CH0_FLAG_ETI           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 10U),    /*!< channel 0 early transmit status flag */
    ENET_DMA_CH0_FLAG_ERIE          = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 11U),    /*!< channel 0 early receive status flag */
    ENET_DMA_CH0_FLAG_FBE           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 12U),    /*!< channel 0 fatal bus error status flag */
    ENET_DMA_CH0_FLAG_CDE           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 13U),    /*!< channel 0 context descriptor error status flag */
    ENET_DMA_CH0_FLAG_AIE           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 14U),    /*!< channel 0 abnormal interrupt summary flag */
    ENET_DMA_CH0_FLAG_NIS           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 15U),    /*!< channel 0 normal interrupt summary flag */
    /* DMA_CH0_MISS_FRAME_CNT register */
    ENET_DMA_CH0_MISS_FRAME_CNT_FLAG_MFCO       = ENET_REGIDX_BIT(DMA_CH0_MISS_FRAME_CNT_REG_OFFSET, 15U),     /*!< overflow status of the MFC counter flag */
    /* DMA_CH1_MISS_FRAME_CNT register */
    ENET_DMA_CH0_RXP_ACCEPT_CNT_FLAG_RXPACOF    = ENET_REGIDX_BIT(DMA_CH0_RXP_ACCEPT_CNT_REG_OFFSET, 31U),     /*!< Rx parser accept counter overflow flag */
    /* DMA_CH1_STATUS register */
    ENET_DMA_CH1_FLAG_TI            = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 0U),     /*!< channel 1 transmit status flag */
    ENET_DMA_CH1_FLAG_TPS           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 1U),     /*!< channel 1 transmit process stopped status flag */
    ENET_DMA_CH1_FLAG_TBU           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 2U),     /*!< channel 1 transmit buffer unavailable status flag */
    ENET_DMA_CH1_FLAG_RI            = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 6U),     /*!< channel 1 receive status flag */
    ENET_DMA_CH1_FLAG_RBU           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 7U),     /*!< channel 1 receive buffer unavailable status flag */
    ENET_DMA_CH1_FLAG_RPS           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 8U),     /*!< channel 1 receive process stopped status flag */
    ENET_DMA_CH1_FLAG_RWT           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 9U),     /*!< channel 1 receive watchdog timeout status flag */
    ENET_DMA_CH1_FLAG_ETI           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 10U),    /*!< channel 1 early transmit status flag */
    ENET_DMA_CH1_FLAG_ERIE          = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 11U),    /*!< channel 1 early receive status flag */
    ENET_DMA_CH1_FLAG_FBE           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 12U),    /*!< channel 1 fatal bus error status flag */
    ENET_DMA_CH1_FLAG_CDE           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 13U),    /*!< channel 1 context descriptor error status flag */
    ENET_DMA_CH1_FLAG_AIE           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 14U),    /*!< channel 1 abnormal interrupt summary flag */
    ENET_DMA_CH1_FLAG_NIS           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 15U),    /*!< channel 1 normal interrupt summary flag */
    /* DMA_CH1_MISS_FRAME_CNT register */
    ENET_DMA_CH1_MISS_FRAME_CNT_FLAG_MFCO       = ENET_REGIDX_BIT(DMA_CH1_MISS_FRAME_CNT_REG_OFFSET, 15U),     /*!< overflow status of the MFC counter flag */
    /* DMA_CH1_MISS_FRAME_CNT register */
    ENET_DMA_CH1_RXP_ACCEPT_CNT_FLAG_RXPACOF    = ENET_REGIDX_BIT(DMA_CH1_RXP_ACCEPT_CNT_REG_OFFSET, 31U),     /*!< Rx parser accept counter overflow flag */
}enet_flag_enum;

/* ENET stutus flag clear */
typedef enum
{
    /* MTL_EST_STATUS register */
    ENET_MTL_EST_STATUS_FLAG_CGCE_CLR                    = ENET_REGIDX_BIT(MAC_FPE_CTRL_STS_REG_OFFSET, 4U),         /*!< constant gate control error flag */
    /* MTL_DBG_STS register */
    ENET_MTL_DBG_STS_FLAG_PKTI_CLR      = ENET_REGIDX_BIT(MTL_DBG_CTL_REG_OFFSET, 8U),    /*!< receive packet available interrupt status flag */
    ENET_MTL_DBG_STS_FLAG_STSI_CLR      = ENET_REGIDX_BIT(MTL_DBG_CTL_REG_OFFSET, 9U),    /*!< transmit status available interrupt status flag */
    /* DMA_CH0_STATUS register */
    ENET_DMA_CH0_FLAG_TI_CLR            = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 0U),     /*!< channel 0 transmit status flag */
    ENET_DMA_CH0_FLAG_TPS_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 1U),     /*!< channel 0 transmit process stopped status flag */
    ENET_DMA_CH0_FLAG_TBU_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 2U),     /*!< channel 0 transmit buffer unavailable status flag */
    ENET_DMA_CH0_FLAG_RI_CLR            = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 6U),     /*!< channel 0 receive status flag */
    ENET_DMA_CH0_FLAG_RBU_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 7U),     /*!< channel 0 receive buffer unavailable status flag */
    ENET_DMA_CH0_FLAG_RPS_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 8U),     /*!< channel 0 receive process stopped status flag */
    ENET_DMA_CH0_FLAG_RWT_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 9U),     /*!< channel 0 receive watchdog timeout status flag */
    ENET_DMA_CH0_FLAG_ETI_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 10U),    /*!< channel 0 early transmit status flag */
    ENET_DMA_CH0_FLAG_ERIE_CLR          = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 11U),    /*!< channel 0 early receive status flag */
    ENET_DMA_CH0_FLAG_FBE_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 12U),    /*!< channel 0 fatal bus error status flag */
    ENET_DMA_CH0_FLAG_CDE_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 13U),    /*!< channel 0 context descriptor error status flag */
    ENET_DMA_CH0_FLAG_AIE_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 14U),    /*!< channel 0 abnormal interrupt summary flag */
    ENET_DMA_CH0_FLAG_NIS_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 15U),    /*!< channel 0 normal interrupt summary flag */
    /* DMA_CH1_STATUS register */
    ENET_DMA_CH1_FLAG_TI_CLR            = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 0U),     /*!< channel 1 transmit status flag */
    ENET_DMA_CH1_FLAG_TPS_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 1U),     /*!< channel 1 transmit process stopped status flag */
    ENET_DMA_CH1_FLAG_TBU_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 2U),     /*!< channel 1 transmit buffer unavailable status flag */
    ENET_DMA_CH1_FLAG_RI_CLR            = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 6U),     /*!< channel 1 receive status flag */
    ENET_DMA_CH1_FLAG_RBU_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 7U),     /*!< channel 1 receive buffer unavailable status flag */
    ENET_DMA_CH1_FLAG_RPS_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 8U),     /*!< channel 1 receive process stopped status flag */
    ENET_DMA_CH1_FLAG_RWT_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 9U),     /*!< channel 1 receive watchdog timeout status flag */
    ENET_DMA_CH1_FLAG_ETI_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 10U),    /*!< channel 1 early transmit status flag */
    ENET_DMA_CH1_FLAG_ERIE_CLR          = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 11U),    /*!< channel 1 early receive status flag */
    ENET_DMA_CH1_FLAG_FBE_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 12U),    /*!< channel 1 fatal bus error status flag */
    ENET_DMA_CH1_FLAG_CDE_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 13U),    /*!< channel 1 context descriptor error status flag */
    ENET_DMA_CH1_FLAG_AIE_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 14U),    /*!< channel 1 abnormal interrupt summary flag */
    ENET_DMA_CH1_FLAG_NIS_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 15U),    /*!< channel 1 normal interrupt summary flag */
} enet_flag_clear_enum;

/* ENET interrupt enable/disable */
typedef enum
{
    /* MAC_INTERRUPT_ENABLE register */
    ENET_MAC_INT_PHYIE              = ENET_REGIDX_BIT(MAC_INTERRUPT_ENABLE_REG_OFFSET, 3U),    /*!< PHY interrupt enable */
    ENET_MAC_INT_PMTIE              = ENET_REGIDX_BIT(MAC_INTERRUPT_ENABLE_REG_OFFSET, 4U),    /*!< PMT interrupt enable */
    ENET_MAC_INT_LPIIE              = ENET_REGIDX_BIT(MAC_INTERRUPT_ENABLE_REG_OFFSET, 5U),    /*!< LPI interrupt enable */
    ENET_MAC_INT_TSIE               = ENET_REGIDX_BIT(MAC_INTERRUPT_ENABLE_REG_OFFSET, 12U),   /*!< timestamp interrupt enable */
    ENET_MAC_INT_TXSTSIE            = ENET_REGIDX_BIT(MAC_INTERRUPT_ENABLE_REG_OFFSET, 13U),   /*!< transmit status interrupt enable */
    ENET_MAC_INT_RXSTSIE            = ENET_REGIDX_BIT(MAC_INTERRUPT_ENABLE_REG_OFFSET, 14U),   /*!< receive status interrupt enable */
    ENET_MAC_INT_FPEIE              = ENET_REGIDX_BIT(MAC_INTERRUPT_ENABLE_REG_OFFSET, 17U),   /*!< frame preemption interrupt enable */
    ENET_MAC_INT_MDIOIE             = ENET_REGIDX_BIT(MAC_INTERRUPT_ENABLE_REG_OFFSET, 18U),   /*!< MDIO interrupt enable */
    
    /* MMC_RX_INTERRUPT_MASK register */
    ENET_MMC_RX_INT_RXGBPKTIM    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 0U),                 /*!< MMC receive good bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RXGBOCTIM    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 1U),                 /*!< MMC receive good bad octet counter interrupt mask */
    ENET_MMC_RX_INT_RXGOCTIM     = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 2U),                 /*!< MMC receive good octet counter interrupt mask */
    ENET_MMC_RX_INT_RXBCGPIM     = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 3U),                 /*!< MMC receive broadcast good packet counter interrupt mask */
    ENET_MMC_RX_INT_RXMCGPIM     = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 4U),                 /*!< MMC receive multicast good packet counter interrupt mask */
    ENET_MMC_RX_INT_RXCRCERPIM   = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 5U),                 /*!< MMC receive crc error packet counter interrupt mask */
    ENET_MMC_RX_INT_RXALGNERPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 6U),                 /*!< MMC receive alignment error packet counter interrupt mask */
    ENET_MMC_RX_INT_RXRUNTPIM    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 7U),                 /*!< MMC receive runt packet counter interrupt mask */
    ENET_MMC_RX_INT_RXJABERPIM   = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 8U),                 /*!< MMC receive jabber error packet counter interrupt mask */
    ENET_MMC_RX_INT_RXUSIZEGPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 9U),                 /*!< MMC receive undersize good packet counter interrupt mask */
    ENET_MMC_RX_INT_RXOSIZEGPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 10U),                /*!< MMC receive oversize good packet counter interrupt mask */
    ENET_MMC_RX_INT_RX64OCTGBPIM = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 11U),                /*!< MMC receive 64 octet good bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RX65T127OCTGBPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 12U),           /*!< MMC receive 65 to 127 octet good bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RX128T255OCTGBPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 13U),          /*!< MMC receive 128 to 255 octet good bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RX256T511OCTGBPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 14U),          /*!< MMC receive 256 to 511 octet good bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RX512T1023OCTGBPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 15U),         /*!< MMC receive 512 to 1023 octet good bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RX1024TMAXOCTGBPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 16U),         /*!< MMC receive 1024 to maximum octet good bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RXUCGPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 17U),                   /*!< MMC receive unicast good packet counter interrupt mask */
    ENET_MMC_RX_INT_RXLENERPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 18U),                 /*!< MMC receive length error packet counter interrupt mask */
    ENET_MMC_RX_INT_RXORANGEPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 19U),                /*!< MMC receive out of range error packet counter interrupt mask */
    ENET_MMC_RX_INT_RXPAUSPIM    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 20U),                /*!< MMC receive pause counter interrupt mask */
    ENET_MMC_RX_INT_RXFOVPIM     = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 21U),                /*!< MMC receive FIFO overflow packet counter interrupt mask */
    ENET_MMC_RX_INT_RXVLANGBPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 22U),                /*!< MMC receive VLAN good bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RXWDOGPIM    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 23U),                /*!< MMC receive watchdog error bad packet counter interrupt mask */
    ENET_MMC_RX_INT_RXRCVERRPIM  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 24U),                /*!< MMC receive error packet counter interrupt mask */
    ENET_MMC_RX_INT_RXCTRLPIM    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 25U),                /*!< MMC receive control packet counter interrupt mask */
    ENET_MMC_RX_INT_RXLPIUSCIM   = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 26U),                /*!< MMC receive LPI microsecond counter interrupt mask */
    ENET_MMC_RX_INT_RXLPITRCIM   = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_MASK_REG_OFFSET, 27U),                /*!< MMC receive LPI transition counter interrupt mask */
    
    /* MMC_TX_INTERRUPT_MASK register */
    ENET_MMC_TX_INT_TXGBOCTIM    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 0U),                 /*!< MMC transmit good bad octet counter interrupt mask */
    ENET_MMC_TX_INT_TXGBPKTIM    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 1U),                 /*!< MMC transmit good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TXBCGPIM     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 2U),                 /*!< MMC transmit broadcast good packet counter interrupt mask */
    ENET_MMC_TX_INT_TXMCGPIM     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 3U),                 /*!< MMC transmit multicast good packet counter interrupt mask */
    ENET_MMC_TX_INT_TX64OCTGBPIM  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 4U),                /*!< MMC transmit 64 Octet good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TX65T127OCTGBPIM  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 5U),            /*!< MMC transmit 65 to 127 octet good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TX128T255OCTGBPIM = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 6U),            /*!< MMC transmit 128 to 255 octet good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TX256T511OCTGBPIM = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 7U),            /*!< MMC transmit 256 to 511 octet good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TX512T1023OCTGBPIM  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 8U),          /*!< MMC transmit 512 to 1023 octet good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TX1024TMAXOCTGBPIM  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 9U),          /*!< MMC transmit 1024 to maximum octet good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TXUCGBPIM    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 10U),                /*!< MMC transmit unicast good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TXMCGBPIM    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 11U),                /*!< MMC transmit multicast good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TXBCGBPIM    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 12U),                /*!< MMC transmit broadcast good bad packet counter interrupt mask */
    ENET_MMC_TX_INT_TXUFLOWERPIM = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 13U),                /*!< MMC transmit underflow error packet counter interrupt mask */
    ENET_MMC_TX_INT_TXSCOLGPIM   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 14U),                /*!< MMC transmit single collision good packet counter interrupt mask */
    ENET_MMC_TX_INT_TXMCOLGPIM   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 15U),                /*!< MMC transmit multiple collision good packet counter interrupt mask */
    ENET_MMC_TX_INT_TXDEFPIM     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 16U),                /*!< MMC transmit deferred packet counter interrupt mask */
    ENET_MMC_TX_INT_TXLATCOLPIM  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 17U),                /*!< MMC transmit late collision packet counter interrupt mask */
    ENET_MMC_TX_INT_TXEXCOLPIM   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 18U),                /*!< MMC transmit excessive collision packet counter interrupt mask */
    ENET_MMC_TX_INT_TXCARERPIM   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 19U),                /*!< MMC transmit carrier error packet counter interrupt mask */
    ENET_MMC_TX_INT_TXGOCTIM     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 20U),                /*!< MMC transmit good octet counter interrupt mask */
    ENET_MMC_TX_INT_TXGPKTIM     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 21U),                /*!< MMC transmit good packet counter interrupt mask */
    ENET_MMC_TX_INT_TXEXDEFPIM   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 22U),                /*!< MMC transmit excessive deferral packet counter interrupt mask */
    ENET_MMC_TX_INT_TXPAUSPIM    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 24U),                /*!< MMC transmit VLAN good packet counter interrupt mask */
    ENET_MMC_TX_INT_TXOSIZEGPIM  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 25U),                /*!< MMC transmit oversize good packet counter interrupt mask */
    ENET_MMC_TX_INT_TXLPIUSCIM   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 26U),                /*!< MMC transmit LPI microsecond counter interrupt mask */
    ENET_MMC_TX_INT_TXLPITRCIM   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_MASK_REG_OFFSET, 27U),                /*!< MMC transmit LPI transition counter interrupt mask */
    
    /* MMC_IPC_RX_INTERRUPT_MASK register */
    ENET_MMC_IPC_RX_INT_RXIPV4GPIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 0U),      /*!< MMC receive IPV4 good packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4HERPIM    = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 1U),      /*!< MMC receive IPV4 header error packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4NOPAYPIM  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 2U),      /*!< MMC receive IPV4 no payload packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4FRAGPIM   = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 3U),      /*!< MMC receive IPV4 fragmented packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4UDSBLPIM  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 4U),      /*!< MMC receive IPV4 UDP checksum disabled packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV6GPIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 5U),      /*!< MMC receive IPV6 good packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV6HERPIM    = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 6U),      /*!< MMC receive IPV6 header error packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV6NOPAYPIM  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 7U),      /*!< MMC receive IPV6 no payload packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXUDPGPIM       = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 8U),      /*!< MMC receive UDP good packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXUDPERPIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 9U),      /*!< MMC receive UDP error packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXTCPGPIM       = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 10U),     /*!< MMC receive TCP good packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXTCPERPIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 11U),     /*!< MMC receive TCP error packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXICMPGPIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 12U),     /*!< MMC receive ICMP good packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXICMPERPIM     = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 13U),     /*!< MMC receive ICMP error packet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4GOIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 16U),      /*!< MMC receive IPV4 good octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4HEROIM    = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 17U),      /*!< MMC receive IPV4 header error octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4NOPAYOIM  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 18U),      /*!< MMC receive IPV4 no payload octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4FRAGOIM   = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 19U),      /*!< MMC receive IPV4 fragmented octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV4UDSBLOIM  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 20U),      /*!< MMC receive IPV4 UDP checksum disabled octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV6GOIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 21U),      /*!< MMC receive IPV6 good octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV6HEROIM    = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 22U),      /*!< MMC receive IPV6 header error octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXIPV6NOPAYOIM  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 23U),      /*!< MMC receive IPV6 no payload octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXUDPGOIM       = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 24U),      /*!< MMC receive UDP good octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXUDPEROIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 25U),      /*!< MMC receive UDP error octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXTCPGOIM       = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 26U),      /*!< MMC receive TCP good octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXTCPEROIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 27U),      /*!< MMC receive TCP error octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXICMPGOIM      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 28U),      /*!< MMC receive ICMP good octet counter interrupt mask */
    ENET_MMC_IPC_RX_INT_RXICMPEROIM     = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_MASK_REG_OFFSET, 29U),      /*!< MMC receive ICMP error octet counter interrupt mask */
    
    /* MMC_FPE_TX_INTERRUPT_MASK register */
    ENET_MMC_FPE_TX_INT_FCIM            = ENET_REGIDX_BIT(MMC_FPE_TX_INTERRUPT_MASK_REG_OFFSET, 0U),       /*!< MMC Tx FPE fragment counter interrupt mask */
    ENET_MMC_FPE_TX_INT_HRCIM           = ENET_REGIDX_BIT(MMC_FPE_TX_INTERRUPT_MASK_REG_OFFSET, 1U),       /*!< MMC Tx hold request counter interrupt mask */
    
    /* MMC_FPE_TX_INTERRUPT_MASK register */
    ENET_MMC_FPE_RX_INT_PAECIM          = ENET_REGIDX_BIT(MMC_FPE_RX_INTERRUPT_MASK_REG_OFFSET, 0U),       /*!< MMC Rx packet assembly error counter interrupt mask */
    ENET_MMC_FPE_RX_INT_PSECIM          = ENET_REGIDX_BIT(MMC_FPE_RX_INTERRUPT_MASK_REG_OFFSET, 1U),       /*!< MMC Rx packet SMD error counter interrupt mask */
    ENET_MMC_FPE_RX_INT_PAOCIM          = ENET_REGIDX_BIT(MMC_FPE_RX_INTERRUPT_MASK_REG_OFFSET, 2U),       /*!< MMC Rx packet assembly OK counter interrupt mask */
    ENET_MMC_FPE_RX_INT_FCIM            = ENET_REGIDX_BIT(MMC_FPE_RX_INTERRUPT_MASK_REG_OFFSET, 3U),       /*!< MMC Rx FPE fragment counter interrupt mask */
    
    
    /* MTL_EST_INTERRUPT_ENABLE register */ 
    ENET_MTL_EST_INT_CGCEIE         = ENET_REGIDX_BIT(MTL_EST_INTERRUPT_ENABLE_REG_OFFSET, 4U), /*!< the constant gate control error interrupt enable */
    ENET_MTL_EST_INT_IEHSIE         = ENET_REGIDX_BIT(MTL_EST_INTERRUPT_ENABLE_REG_OFFSET, 3U), /*!< interrupt enable for HLBS */
    ENET_MTL_EST_INT_IEHFIE         = ENET_REGIDX_BIT(MTL_EST_INTERRUPT_ENABLE_REG_OFFSET, 2U), /*!< interrupt enable for HLBF */
    ENET_MTL_EST_INT_IEBEIE         = ENET_REGIDX_BIT(MTL_EST_INTERRUPT_ENABLE_REG_OFFSET, 1U), /*!< interrupt enable for BTR error */
    ENET_MTL_EST_INT_IECCIE         = ENET_REGIDX_BIT(MTL_EST_INTERRUPT_ENABLE_REG_OFFSET, 0U), /*!< interrupt enable for switch enable */
    /* MTL_RXP_INTERRUPT_CONTROL_STATUS register */ 
    ENET_MTL_RXP_INT_NVEOVIE        = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 16U), /*!< number of valid entries overflow interrupt enable */
    ENET_MTL_RXP_INT_NPEOVIE        = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 17U), /*!< number of parsable entries overflow interrupt enable */
    ENET_MTL_RXP_INT_FOOVIE         = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 18U), /*!< frame offset overflow interrupt enable */
    ENET_MTL_RXP_INT_PDRFIE         = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 19U), /*!< packet drop due to RF interrupt enable */
    
    /* MTL_ECC_INTERRUPT_ENABLE register */ 
    ENET_MTL_ECC_INT_RPCEIE         = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_ENABLE_REG_OFFSET, 12U), /*!< Rx parser memory correctable error interrupt enable */
    ENET_MTL_ECC_INT_ECEIE          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_ENABLE_REG_OFFSET, 8U), /*!< EST memory correctable error interrupt enable */
    ENET_MTL_ECC_INT_RXCEIE         = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_ENABLE_REG_OFFSET, 4U), /*!< Rx memory correctable error interrupt enable */
    ENET_MTL_ECC_INT_TXCEIE         = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_ENABLE_REG_OFFSET, 0U), /*!< Tx memory correctable error interrupt enable */
    /* MTL_Q0_INTERRUPT_CONTROL_STATUS register */
    ENET_MTL_Q0_INT_RXOIE           = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 24U), /*!< receive queue 0 overflow interrupt enable */
    ENET_MTL_Q0_INT_ABPSIE          = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 9U), /*!< queue 0 average bits per slot interrupt enable */
    ENET_MTL_Q0_INT_TXUIE           = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 8U), /*!< transmit queue 0 underflow interrupt enable */
    /* MTL_Q1_INTERRUPT_CONTROL_STATUS register */
    ENET_MTL_Q1_INT_RXOIE           = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 24U), /*!< receive queue 1 overflow interrupt enable */
    ENET_MTL_Q1_INT_ABPSIE          = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 9U), /*!< queue 1 average bits per slot interrupt enable */
    ENET_MTL_Q1_INT_TXUIE           = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 8U), /*!< transmit queue 1 underflow interrupt enable */
    /* DMA_CH0_INTERRRUPT_ENABLE register */
    ENET_DMA_CH0_INT_TIE                = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 0U),    /*!< channel 0 transmit interrupt enable */
    ENET_DMA_CH0_INT_TXSEIE             = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 1U),    /*!< channel 0 transmit process stopped interrupt enable */
    ENET_DMA_CH0_INT_TBUEIE             = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 2U),    /*!< channel 0 transmit buffer unavailable interrupt enable */
    ENET_DMA_CH0_INT_RIE                = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 6U),    /*!< channel 0 receive interrupt enable */
    ENET_DMA_CH0_INT_RBUEIE             = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 7U),    /*!< channel 0 receive buffer unavailable interrupt enable */
    ENET_DMA_CH0_INT_RSEIE              = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 8U),    /*!< channel 0 receive process stopped interrupt enable */
    ENET_DMA_CH0_INT_RWTEIE             = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 9U),    /*!< channel 0 receive watchdog timeout interrupt enable */
    ENET_DMA_CH0_INT_ETIE               = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 10U),   /*!< channel 0 early transmit interrupt enable */
    ENET_DMA_CH0_INT_ERIE               = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 11U),   /*!< channel 0 early receive interrupt enable */
    ENET_DMA_CH0_INT_FBEEIE             = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 12U),   /*!< channel 0 fatal bus error interrupt enable */
    ENET_DMA_CH0_INT_CDEEIE             = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 13U),   /*!< channel 0 the descriptor error interrupt enable */
    ENET_DMA_CH0_INT_AIE                = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 14U),   /*!< channel 0 abnormal interrupt summary enable */
    ENET_DMA_CH0_INT_NIE                = ENET_REGIDX_BIT(DMA_CH0_INTERRUPT_ENABLE_REG_OFFSET, 15U),   /*!< channel 0 normal interrupt summary enable */
    /* DMA_CH1_INTERRRUPT_ENABLE register */
    ENET_DMA_CH1_INT_TIE                = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 0U),    /*!< channel 1 transmit interrupt enable */
    ENET_DMA_CH1_INT_TXSEIE             = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 1U),    /*!< channel 1 transmit process stopped interrupt enable */
    ENET_DMA_CH1_INT_TBUEIE             = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 2U),    /*!< channel 1 transmit buffer unavailable interrupt enable */
    ENET_DMA_CH1_INT_RIE                = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 6U),    /*!< channel 1 receive interrupt enable */
    ENET_DMA_CH1_INT_RBUEIE             = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 7U),    /*!< channel 1 receive buffer unavailable interrupt enable */
    ENET_DMA_CH1_INT_RSEIE              = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 8U),    /*!< channel 1 receive process stopped interrupt enable */
    ENET_DMA_CH1_INT_RWTEIE             = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 9U),    /*!< channel 1 receive watchdog timeout interrupt enable */
    ENET_DMA_CH1_INT_ETIE               = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 10U),   /*!< channel 1 early transmit interrupt enable */
    ENET_DMA_CH1_INT_ERIE               = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 11U),   /*!< channel 1 early receive interrupt enable */
    ENET_DMA_CH1_INT_FBEEIE             = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 12U),   /*!< channel 1 fatal bus error interrupt enable */
    ENET_DMA_CH1_INT_CDEEIE             = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 13U),   /*!< channel 1 the descriptor error interrupt enable */
    ENET_DMA_CH1_INT_AIE                = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 14U),   /*!< channel 1 abnormal interrupt summary enable */
    ENET_DMA_CH1_INT_NIE                = ENET_REGIDX_BIT(DMA_CH1_INTERRUPT_ENABLE_REG_OFFSET, 15U),   /*!< channel 1 normal interrupt summary enable */
} enet_int_enum;

/* ENET interrupt flag get */
typedef enum
{
    /* MAC_INTERRUPT_STATUS register */
    ENET_MAC_INT_FLAG_PHYIS           = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 3U),     /*!< PHY interrupt status flag */
    ENET_MAC_INT_FLAG_PMTIS           = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 4U),     /*!< PMT interrupt status flag */
    ENET_MAC_INT_FLAG_LPIIS           = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 5U),     /*!< LPI Interrupt status flag */
    ENET_MAC_INT_FLAG_MMCIS           = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 8U),     /*!< MMC Interrupt status flag */
    ENET_MAC_INT_FLAG_MMCRXIS         = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 9U),     /*!< MMC receive interrupt status flag */
    ENET_MAC_INT_FLAG_MMCTXIS         = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 10U),    /*!< MMC transmit interrupt status flag */
    ENET_MAC_INT_FLAG_MMCRXIPIS       = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 11U),    /*!< MMC receive checksum offload interrupt status flag */
    ENET_MAC_INT_FLAG_TSIS            = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 12U),    /*!< timestamp interrupt status flag */
    ENET_MAC_INT_FLAG_TXSTSIS         = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 13U),    /*!< transmit status flag */
    ENET_MAC_INT_FLAG_RXSTSIS         = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 14U),    /*!< receive status interrupt flag */
    ENET_MAC_INT_FLAG_FPEIS           = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 17U),    /*!< frame preemption interrupt status flag */
    ENET_MAC_INT_FLAG_MDIOIS          = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 18U),    /*!< MDIO interrupt status flag */
    ENET_MAC_INT_FLAG_MFTIS           = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 19U),    /*!< MMC FPE transmit interrupt status flag */
    ENET_MAC_INT_FLAG_MFEIS           = ENET_REGIDX_BIT(MAC_INTERRUPT_STATUS_REG_OFFSET, 20U),    /*!< MMC FPE receive Interrupt status flag */
    
    /* MAC_DPP_FSM_INTERRUPT_STATUS register */
    ENET_MAC_DPP_FSM_INT_FLAG_ATPES   = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 0U),     /*!< application transmit interface parity checker status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_RDPES   = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 2U),     /*!< read descriptor parity checker error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_MPES    = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 3U),     /*!< MTL data path parity checker error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_MTSPES  = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 4U),     /*!< MTL Tx status data path parity checker error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_ARPES   = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 5U),     /*!< application receive interface data path parity error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_CWPES   = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 6U),     /*!< CSR write data path parity checker error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_TTES    = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 8U),     /*!< Tx FSM timeout Error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_RTES    = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 9U),     /*!< application transmit interface parity checker status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_ATES    = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 11U),    /*!< APP FSM timeout error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_PTES    = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 12U),    /*!< PTP FSM timeout error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_MSTTES  = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 16U),    /*!< master read / write timeout error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_FSMPES  = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 24U),    /*!< FSM state parity error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_MTBUPES = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 25U),    /*!< MAC TBU data path parity checker error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_MTFCPES = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 26U),    /*!< MAC TFC data path parity checker error status flag */
    ENET_MAC_DPP_FSM_INT_FLAG_MRWCPES = ENET_REGIDX_BIT(MAC_DPP_FSM_INTERRUPT_STATUS_REG_OFFSET, 27U),    /*!< MTL RWC data path parity checker error status flag */
    
    /* MMC_RX_INTERRUPT register */
    ENET_MMC_RX_INT_FLAG_RXGBPKTIS    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 0U),                 /*!< MMC receive good bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXGBOCTIS    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 1U),                 /*!< MMC receive good bad octet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXGOCTIS     = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 2U),                 /*!< MMC receive good octet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXBCGPIS     = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 3U),                 /*!< MMC receive broadcast good packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXMCGPIS     = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 4U),                 /*!< MMC receive multicast good packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXCRCERPIS   = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 5U),                 /*!< MMC receive crc error packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXALGNERPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 6U),                 /*!< MMC receive alignment error packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXRUNTPIS    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 7U),                 /*!< MMC receive runt packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXJABERPIS   = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 8U),                 /*!< MMC receive jabber error packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXUSIZEGPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 9U),                 /*!< MMC receive undersize good packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXOSIZEGPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 10U),                /*!< MMC receive oversize good packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RX64OCTGBPIS = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 11U),                /*!< MMC receive 64 octet good bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RX65T127OCTGBPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 12U),           /*!< MMC receive 65 to 127 octet good bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RX128T255OCTGBPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 13U),          /*!< MMC receive 128 to 255 octet good bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RX256T511OCTGBPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 14U),          /*!< MMC receive 256 to 511 octet good bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RX512T1023OCTGBPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 15U),         /*!< MMC receive 512 to 1023 octet good bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RX1024TMAXOCTGBPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 16U),         /*!< MMC receive 1024 to maximum octet good bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXUCGPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 17U),                   /*!< MMC receive unicast good packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXLENERPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 18U),                 /*!< MMC receive length error packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXORANGEPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 19U),                /*!< MMC receive out of range error packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXPAUSPIS    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 20U),                /*!< MMC receive pause counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXFOVPIS     = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 21U),                /*!< MMC receive FIFO overflow packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXVLANGBPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 22U),                /*!< MMC receive VLAN good bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXWDOGPIS    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 23U),                /*!< MMC receive watchdog error bad packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXRCVERRPIS  = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 24U),                /*!< MMC receive error packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXCTRLPIS    = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 25U),                /*!< MMC receive control packet counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXLPIUSCIS   = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 26U),                /*!< MMC receive LPI microsecond counter interrupt status flag */
    ENET_MMC_RX_INT_FLAG_RXLPITRCIS   = ENET_REGIDX_BIT(MMC_RX_INTERRUPT_REG_OFFSET, 27U),                /*!< MMC receive LPI transition counter interrupt status flag */
    
    /* MMC_TX_INTERRUPT register */
    ENET_MMC_TX_INT_FLAG_TXGBOCTIS    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 0U),                 /*!< MMC transmit good bad octet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXGBPKTIS    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 1U),                 /*!< MMC transmit good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXBCGPIS     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 2U),                 /*!< MMC transmit broadcast good packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXMCGPIS     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 3U),                 /*!< MMC transmit multicast good packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TX64OCTGBPIS  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 4U),                /*!< MMC transmit 64 Octet good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TX65T127OCTGBPIS  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 5U),            /*!< MMC transmit 65 to 127 octet good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TX128T255OCTGBPIS = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 6U),            /*!< MMC transmit 128 to 255 octet good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TX256T511OCTGBPIS = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 7U),            /*!< MMC transmit 256 to 511 octet good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TX512T1023OCTGBPIS  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 8U),          /*!< MMC transmit 512 to 1023 octet good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TX1024TMAXOCTGBPIS  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 9U),          /*!< MMC transmit 1024 to maximum octet good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXUCGBPIS    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 10U),                /*!< MMC transmit unicast good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXMCGBPIS    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 11U),                /*!< MMC transmit multicast good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXBCGBPIS    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 12U),                /*!< MMC transmit broadcast good bad packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXUFLOWERPIS = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 13U),                /*!< MMC transmit underflow error packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXSCOLGPIS   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 14U),                /*!< MMC transmit single collision good packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXMCOLGPIS   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 15U),                /*!< MMC transmit multiple collision good packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXDEFPIS     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 16U),                /*!< MMC transmit deferred packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXLATCOLPIS  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 17U),                /*!< MMC transmit late collision packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXEXCOLPIS   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 18U),                /*!< MMC transmit excessive collision packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXCARERPIS   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 19U),                /*!< MMC transmit carrier error packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXGOCTIS     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 20U),                /*!< MMC transmit good octet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXGPKTIS     = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 21U),                /*!< MMC transmit good packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXEXDEFPIS   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 22U),                /*!< MMC transmit excessive deferral packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXPAUSPIS    = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 23U),                /*!< MMC transmit pause packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXVLANGPIS   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 24U),                /*!< MMC transmit VLAN good packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXOSIZEGPIS  = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 25U),                /*!< MMC transmit oversize good packet counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXLPIUSCIS   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 26U),                /*!< MMC transmit LPI microsecond counter interrupt status flag */
    ENET_MMC_TX_INT_FLAG_TXLPITRCIS   = ENET_REGIDX_BIT(MMC_TX_INTERRUPT_REG_OFFSET, 27U),                /*!< MMC transmit LPI transition counter interrupt status flag */
    
    /* MMC_IPC_RX_INTERRUPT register */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4GPIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 0U),      /*!< MMC receive IPV4 good packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4HERPIS    = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 1U),      /*!< MMC receive IPV4 header error packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4NOPAYPIS  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 2U),      /*!< MMC receive IPV4 no payload packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4FRAGPIS   = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 3U),      /*!< MMC receive IPV4 fragmented packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4UDSBLPIS  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 4U),      /*!< MMC receive IPV4 UDP checksum disabled packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV6GPIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 5U),      /*!< MMC receive IPV6 good packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV6HERPIS    = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 6U),      /*!< MMC receive IPV6 header error packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV6NOPAYPIS  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 7U),      /*!< MMC receive IPV6 no payload packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXUDPGPIS       = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 8U),      /*!< MMC receive UDP good packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXUDPERPIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 9U),      /*!< MMC receive UDP error packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXTCPGPIS       = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 10U),     /*!< MMC receive TCP good packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXTCPERPIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 11U),     /*!< MMC receive TCP error packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXICMPGPIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 12U),     /*!< MMC receive ICMP good packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXICMPERPIS     = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 13U),     /*!< MMC receive ICMP error packet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4GOIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 16U),      /*!< MMC receive IPV4 good octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4HEROIS    = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 17U),      /*!< MMC receive IPV4 header error octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4NOPAYOIS  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 18U),      /*!< MMC receive IPV4 no payload octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4FRAGOIS   = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 19U),      /*!< MMC receive IPV4 fragmented octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV4UDSBLOIS  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 20U),      /*!< MMC receive IPV4 UDP checksum disabled octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV6GOIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 21U),      /*!< MMC receive IPV6 good octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV6HEROIS    = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 22U),      /*!< MMC receive IPV6 header error octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXIPV6NOPAYOIS  = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 23U),      /*!< MMC receive IPV6 no payload octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXUDPGOIS       = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 24U),      /*!< MMC receive UDP good octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXUDPEROIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 25U),      /*!< MMC receive UDP error octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXTCPGOIS       = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 26U),      /*!< MMC receive TCP good octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXTCPEROIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 27U),      /*!< MMC receive TCP error octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXICMPGOIS      = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 28U),      /*!< MMC receive ICMP good octet counter interrupt status flag */
    ENET_MMC_IPC_RX_INT_FLAG_RXICMPEROIS     = ENET_REGIDX_BIT(MMC_IPC_RX_INTERRUPT_REG_OFFSET, 29U),      /*!< MMC receive ICMP error octet counter interrupt status flag */
    
    /* MMC_FPE_TX_INTERRUPT register */
    ENET_MMC_FPE_TX_INT_FLAG_FCIS            = ENET_REGIDX_BIT(MMC_FPE_TX_INTERRUPT_REG_OFFSET, 0U),       /*!< MMC Tx FPE fragment counter interrupt status flag */
    ENET_MMC_FPE_TX_INT_FLAG_HRCIS           = ENET_REGIDX_BIT(MMC_FPE_TX_INTERRUPT_REG_OFFSET, 1U),       /*!< MMC Tx hold request counter interrupt status flag */
    
    /* MMC_FPE_RX_INTERRUPT register */
    ENET_MMC_FPE_RX_INT_FLAG_PAECIS          = ENET_REGIDX_BIT(MMC_FPE_RX_INTERRUPT_REG_OFFSET, 0U),       /*!< MMC Rx packet assembly error counter interrupt status flag */
    ENET_MMC_FPE_RX_INT_FLAG_PSECIS          = ENET_REGIDX_BIT(MMC_FPE_RX_INTERRUPT_REG_OFFSET, 1U),       /*!< MMC Rx packet SMD error counter interrupt status flag */
    ENET_MMC_FPE_RX_INT_FLAG_PAOCIS          = ENET_REGIDX_BIT(MMC_FPE_RX_INTERRUPT_REG_OFFSET, 2U),       /*!< MMC Rx packet assembly OK counter interrupt status flag */
    ENET_MMC_FPE_RX_INT_FLAG_FCIS            = ENET_REGIDX_BIT(MMC_FPE_RX_INTERRUPT_REG_OFFSET, 3U),       /*!< MMC Rx FPE fragment counter interrupt status flag */
    /* MTL_INTERRUPT_STATUS register */
    ENET_MTL_INT_FLAG_Q0IS                   = ENET_REGIDX_BIT(MTL_INTERRUPT_STATUS_REG_OFFSET, 0U),       /*!< queue 0 interrupt status flag */
    ENET_MTL_INT_FLAG_Q1IS                   = ENET_REGIDX_BIT(MTL_INTERRUPT_STATUS_REG_OFFSET, 1U),       /*!< queue 1 interrupt status flag */
    ENET_MTL_INT_FLAG_DBGIS                  = ENET_REGIDX_BIT(MTL_INTERRUPT_STATUS_REG_OFFSET, 17U),      /*!< debug interrupt status flag */
    ENET_MTL_INT_FLAG_ESTIS                  = ENET_REGIDX_BIT(MTL_INTERRUPT_STATUS_REG_OFFSET, 18U),      /*!< EST (TAS- 802.1Qbv) interrupt status flag */
    ENET_MTL_INT_FLAG_MTLPIS                 = ENET_REGIDX_BIT(MTL_INTERRUPT_STATUS_REG_OFFSET, 23U),      /*!< MTL Rx parser interrupt status flag */
    /* MTL_RXP_INTERRUPT_CONTROL_STATUS register */ 
    ENET_MTL_RXP_INT_FLAG_NVEOVIS        = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 0U), /*!< number of valid entries overflow interrupt status flag */
    ENET_MTL_RXP_INT_FLAG_NPEOVIS        = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 1U), /*!< number of parsable entries overflow interrupt status flag */
    ENET_MTL_RXP_INT_FLAG_FOOVIS         = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 2U), /*!< frame offset overflow interrupt status flag */
    ENET_MTL_RXP_INT_FLAG_PDRFIS         = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 3U), /*!< packet drop due to RF interrupt status flag */
    /* MTL_SAFETY_INTERRUPT_STATUS_REG_OFFSET register */
    ENET_MTL_SAFETY_INT_FLAG_MECIS       = ENET_REGIDX_BIT(MTL_SAFETY_INTERRUPT_STATUS_REG_OFFSET, 0U),     /*!< MTL ECC correctable error interrupt status flag */
    ENET_MTL_SAFETY_INT_FLAG_MEUIS       = ENET_REGIDX_BIT(MTL_SAFETY_INTERRUPT_STATUS_REG_OFFSET, 1U),     /*!< MTL ECC uncorrectable error interrupt status flag */
    /* MTL_ECC_INTERRUPT_STATUS_REG_OFFSET register */
    ENET_MTL_ECC_INT_FLAG_TXCES          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 0U),        /*!< MTL Tx memory correctable error status flag */
    ENET_MTL_ECC_INT_FLAG_TXAMS          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 1U),        /*!< MTL Tx memory address mismatch status flag */
    ENET_MTL_ECC_INT_FLAG_TXUES          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 2U),        /*!< MTL Tx memory uncorrectable error status flag */
    ENET_MTL_ECC_INT_FLAG_RXCES          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 4U),        /*!< MTL Rx memory correctable error status flag */
    ENET_MTL_ECC_INT_FLAG_RXAMS          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 5U),        /*!< MTL Rx memory address mismatch status flag */
    ENET_MTL_ECC_INT_FLAG_RXUES          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 6U),        /*!< MTL Rx memory uncorrectable error status flag */
    ENET_MTL_ECC_INT_FLAG_ECES           = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 8U),        /*!< MTL EST correctable error status flag */
    ENET_MTL_ECC_INT_FLAG_EAMS           = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 9U),        /*!< MTL EST address mismatch status flag */
    ENET_MTL_ECC_INT_FLAG_EUES           = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 10U),       /*!< MTL EST uncorrectable error status flag */
    ENET_MTL_ECC_INT_FLAG_RPCES          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 12U),       /*!< MTL Rx Parser memory correctable error status flag */
    ENET_MTL_ECC_INT_FLAG_RPAMS          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 13U),       /*!< MTL Rx Parser memory address mismatch status flag */
    ENET_MTL_ECC_INT_FLAG_RPUES          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 14U),       /*!< MTL Rx Parser memory uncorrectable error status flag */
    /* MTL_Q0_INTERRUPT_CONTROL_STATUS register */ 
    ENET_MTL_Q0_INT_FLAG_RXOVFIS           = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 16U), /*!< receive queue 0 overflow status flag */
    ENET_MTL_Q0_INT_FLAG_ABPSIS            = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 1U),  /*!< queue 0 average bits per slot status flag */
    ENET_MTL_Q0_INT_FLAG_TQU               = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 0U),  /*!< transmit queue 0 underflow status flag */
    /* MTL_Q1_INTERRUPT_CONTROL_STATUS register */
    ENET_MTL_Q1_INT_FLAG_RXOVFIS           = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 16U), /*!< receive queue 1 overflow status flag */
    ENET_MTL_Q1_INT_FLAG_ABPSIS            = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 1U),  /*!< queue 1 average bits per slot status flag */
    ENET_MTL_Q1_INT_FLAG_TQU               = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 0U),  /*!< transmit queue 1 underflow status flag */
    /* DMA_INTERRUPT_STATUS register */
    ENET_DMA_INT_FLAG_DC0IS              = ENET_REGIDX_BIT(DMA_INTERRUPT_STATUS_REG_OFFSET, 0U),            /*!< DMA channel 0 interrupt status flag */
    ENET_DMA_INT_FLAG_DC1IS              = ENET_REGIDX_BIT(DMA_INTERRUPT_STATUS_REG_OFFSET, 1U),            /*!< DMA channel 1 interrupt status flag */
    ENET_DMA_INT_FLAG_MTLIS              = ENET_REGIDX_BIT(DMA_INTERRUPT_STATUS_REG_OFFSET, 16U),           /*!< MTL interrupt status flag */
    ENET_DMA_INT_FLAG_MACIS              = ENET_REGIDX_BIT(DMA_INTERRUPT_STATUS_REG_OFFSET, 17U),           /*!< MAC interrupt status flag */
    /* DMA_SAFETY_INTERRUPT_STATUS register */
    ENET_DMA_SAFETY_INT_FLAG_DECIS       = ENET_REGIDX_BIT(DMA_SAFETY_INTERRUPT_STATUS_REG_OFFSET, 0U),            /*!< DMA ECC correctable error interrupt status flag */
    ENET_DMA_SAFETY_INT_FLAG_DEUIS       = ENET_REGIDX_BIT(DMA_SAFETY_INTERRUPT_STATUS_REG_OFFSET, 1U),            /*!< DMA ECC uncorrectable error interrupt status flag */
    ENET_DMA_SAFETY_INT_FLAG_MSCIS       = ENET_REGIDX_BIT(DMA_SAFETY_INTERRUPT_STATUS_REG_OFFSET, 28U),           /*!< MTL safety correctable error interrupt status flag */
    ENET_DMA_SAFETY_INT_FLAG_MSUIS       = ENET_REGIDX_BIT(DMA_SAFETY_INTERRUPT_STATUS_REG_OFFSET, 29U),           /*!< MTL safety uncorrectable error interrupt status flag */
    ENET_DMA_SAFETY_INT_FLAG_MCSIS       = ENET_REGIDX_BIT(DMA_SAFETY_INTERRUPT_STATUS_REG_OFFSET, 31U),           /*!< MAC safety uncorrectable error interrupt status flag */
    /* DMA_CH0_STATUS register */
    ENET_DMA_CH0_INT_FLAG_TI            = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 0U),     /*!< channel 0 transmit status flag */
    ENET_DMA_CH0_INT_FLAG_TPS           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 1U),     /*!< channel 0 transmit process stopped status flag */
    ENET_DMA_CH0_INT_FLAG_TBU           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 2U),     /*!< channel 0 transmit buffer unavailable status flag */
    ENET_DMA_CH0_INT_FLAG_RI            = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 6U),     /*!< channel 0 receive status flag */
    ENET_DMA_CH0_INT_FLAG_RBU           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 7U),     /*!< channel 0 receive buffer unavailable status flag */
    ENET_DMA_CH0_INT_FLAG_RPS           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 8U),     /*!< channel 0 receive process stopped status flag */
    ENET_DMA_CH0_INT_FLAG_RWT           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 9U),     /*!< channel 0 receive watchdog timeout status flag */
    ENET_DMA_CH0_INT_FLAG_ETI           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 10U),    /*!< channel 0 early transmit status flag */
    ENET_DMA_CH0_INT_FLAG_ERIE          = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 11U),    /*!< channel 0 early receive status flag */
    ENET_DMA_CH0_INT_FLAG_FBE           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 12U),    /*!< channel 0 fatal bus error status flag */
    ENET_DMA_CH0_INT_FLAG_CDE           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 13U),    /*!< channel 0 context descriptor error status flag */
    ENET_DMA_CH0_INT_FLAG_AIE           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 14U),    /*!< channel 0 abnormal interrupt summary flag */
    ENET_DMA_CH0_INT_FLAG_NIS           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 15U),    /*!< channel 0 normal interrupt summary flag */
    /* DMA_CH1_STATUS register */
    ENET_DMA_CH1_INT_FLAG_TI            = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 0U),     /*!< channel 1 transmit status flag */
    ENET_DMA_CH1_INT_FLAG_TPS           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 1U),     /*!< channel 1 transmit process stopped status flag */
    ENET_DMA_CH1_INT_FLAG_TBU           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 2U),     /*!< channel 1 transmit buffer unavailable status flag */
    ENET_DMA_CH1_INT_FLAG_RI            = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 6U),     /*!< channel 1 receive status flag */
    ENET_DMA_CH1_INT_FLAG_RBU           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 7U),     /*!< channel 1 receive buffer unavailable status flag */
    ENET_DMA_CH1_INT_FLAG_RPS           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 8U),     /*!< channel 1 receive process stopped status flag */
    ENET_DMA_CH1_INT_FLAG_RWT           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 9U),     /*!< channel 1 receive watchdog timeout status flag */
    ENET_DMA_CH1_INT_FLAG_ETI           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 10U),    /*!< channel 1 early transmit status flag */
    ENET_DMA_CH1_INT_FLAG_ERIE          = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 11U),    /*!< channel 1 early receive status flag */
    ENET_DMA_CH1_INT_FLAG_FBE           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 12U),    /*!< channel 1 fatal bus error status flag */
    ENET_DMA_CH1_INT_FLAG_CDE           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 13U),    /*!< channel 1 context descriptor error status flag */
    ENET_DMA_CH1_INT_FLAG_AIE           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 14U),    /*!< channel 1 abnormal interrupt summary flag */
    ENET_DMA_CH1_INT_FLAG_NIS           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 15U),    /*!< channel 1 normal interrupt summary flag */
} enet_int_flag_enum;

/* ENET interrupt flag clear */
typedef enum
{
    
    /* MTL_RXP_INTERRUPT_CONTROL_STATUS register */ 
    ENET_MTL_RXP_INT_FLAG_NVEOVIS_CLR        = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 0U), /*!< number of valid entries overflow interrupt status flag */
    ENET_MTL_RXP_INT_FLAG_NPEOVIS_CLR        = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 1U), /*!< number of parsable entries overflow interrupt status flag */
    ENET_MTL_RXP_INT_FLAG_FOOVIS_CLR         = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 2U), /*!< frame offset overflow interrupt status flag */
    ENET_MTL_RXP_INT_FLAG_PDRFIS_CLR         = ENET_REGIDX_BIT(MTL_RXP_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 3U), /*!< packet drop due to RF interrupt status flag */

    /* MTL_ECC_INTERRUPT_STATUS_REG_OFFSET register */
    ENET_MTL_ECC_INT_FLAG_TXCES_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 0U),        /*!< MTL Tx memory correctable error status flag */
    ENET_MTL_ECC_INT_FLAG_TXAMS_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 1U),        /*!< MTL Tx memory address mismatch status flag */
    ENET_MTL_ECC_INT_FLAG_TXUES_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 2U),        /*!< MTL Tx memory uncorrectable error status flag */
    ENET_MTL_ECC_INT_FLAG_RXCES_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 4U),        /*!< MTL Rx memory correctable error status flag */
    ENET_MTL_ECC_INT_FLAG_RXAMS_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 5U),        /*!< MTL Rx memory address mismatch status flag */
    ENET_MTL_ECC_INT_FLAG_RXUES_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 6U),        /*!< MTL Rx memory uncorrectable error status flag */
    ENET_MTL_ECC_INT_FLAG_ECES_CLR           = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 8U),        /*!< MTL EST correctable error status flag */
    ENET_MTL_ECC_INT_FLAG_EAMS_CLR           = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 9U),        /*!< MTL EST address mismatch status flag */
    ENET_MTL_ECC_INT_FLAG_EUES_CLR           = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 10U),       /*!< MTL EST uncorrectable error status flag */
    ENET_MTL_ECC_INT_FLAG_RPCES_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 12U),       /*!< MTL Rx Parser memory correctable error status flag */
    ENET_MTL_ECC_INT_FLAG_RPAMS_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 13U),       /*!< MTL Rx Parser memory address mismatch status flag */
    ENET_MTL_ECC_INT_FLAG_RPUES_CLR          = ENET_REGIDX_BIT(MTL_ECC_INTERRUPT_STATUS_REG_OFFSET, 14U),       /*!< MTL Rx Parser memory uncorrectable error status flag */
    /* MTL_Q0_INTERRUPT_CONTROL_STATUS register */ 
    ENET_MTL_Q0_INT_FLAG_RXOVFIS_CLR         = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 16U), /*!< receive queue 0 overflow status flag */
    ENET_MTL_Q0_INT_FLAG_ABPSIS_CLR          = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 1U),  /*!< queue 0 average bits per slot status flag */
    ENET_MTL_Q0_INT_FLAG_TQU_CLR             = ENET_REGIDX_BIT(MTL_Q0_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 0U),  /*!< transmit queue 0 underflow status flag */
    /* MTL_Q1_INTERRUPT_CONTROL_STATUS register */
    ENET_MTL_Q1_INT_FLAG_RXOVFIS_CLR         = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 16U), /*!< receive queue 1 overflow status flag */
    ENET_MTL_Q1_INT_FLAG_ABPSIS_CLR          = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 1U),  /*!< queue 1 average bits per slot status flag */
    ENET_MTL_Q1_INT_FLAG_TQU_CLR             = ENET_REGIDX_BIT(MTL_Q1_INTERRUPT_CONTROL_STATUS_REG_OFFSET, 0U),  /*!< transmit queue 1 underflow status flag */
    /* DMA_CH0_STATUS register */
    ENET_DMA_CH0_INT_FLAG_TI_CLR            = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 0U),     /*!< channel 0 transmit status flag */
    ENET_DMA_CH0_INT_FLAG_TPS_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 1U),     /*!< channel 0 transmit process stopped status flag */
    ENET_DMA_CH0_INT_FLAG_TBU_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 2U),     /*!< channel 0 transmit buffer unavailable status flag */
    ENET_DMA_CH0_INT_FLAG_RI_CLR            = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 6U),     /*!< channel 0 receive status flag */
    ENET_DMA_CH0_INT_FLAG_RBU_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 7U),     /*!< channel 0 receive buffer unavailable status flag */
    ENET_DMA_CH0_INT_FLAG_RPS_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 8U),     /*!< channel 0 receive process stopped status flag */
    ENET_DMA_CH0_INT_FLAG_RWT_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 9U),     /*!< channel 0 receive watchdog timeout status flag */
    ENET_DMA_CH0_INT_FLAG_ETI_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 10U),    /*!< channel 0 early transmit status flag */
    ENET_DMA_CH0_INT_FLAG_ERIE_CLR          = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 11U),    /*!< channel 0 early receive status flag */
    ENET_DMA_CH0_INT_FLAG_FBE_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 12U),    /*!< channel 0 fatal bus error status flag */
    ENET_DMA_CH0_INT_FLAG_CDE_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 13U),    /*!< channel 0 context descriptor error status flag */
    ENET_DMA_CH0_INT_FLAG_AIE_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 14U),    /*!< channel 0 abnormal interrupt summary flag */
    ENET_DMA_CH0_INT_FLAG_NIS_CLR           = ENET_REGIDX_BIT(DMA_CH0_STATUS_REG_OFFSET, 15U),    /*!< channel 0 normal interrupt summary flag */
    /* DMA_CH1_STATUS register */
    ENET_DMA_CH1_INT_FLAG_TI_CLR            = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 0U),     /*!< channel 1 transmit status flag */
    ENET_DMA_CH1_INT_FLAG_TPS_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 1U),     /*!< channel 1 transmit process stopped status flag */
    ENET_DMA_CH1_INT_FLAG_TBU_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 2U),     /*!< channel 1 transmit buffer unavailable status flag */
    ENET_DMA_CH1_INT_FLAG_RI_CLR            = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 6U),     /*!< channel 1 receive status flag */
    ENET_DMA_CH1_INT_FLAG_RBU_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 7U),     /*!< channel 1 receive buffer unavailable status flag */
    ENET_DMA_CH1_INT_FLAG_RPS_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 8U),     /*!< channel 1 receive process stopped status flag */
    ENET_DMA_CH1_INT_FLAG_RWT_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 9U),     /*!< channel 1 receive watchdog timeout status flag */
    ENET_DMA_CH1_INT_FLAG_ETI_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 10U),    /*!< channel 1 early transmit status flag */
    ENET_DMA_CH1_INT_FLAG_ERIE_CLR          = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 11U),    /*!< channel 1 early receive status flag */
    ENET_DMA_CH1_INT_FLAG_FBE_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 12U),    /*!< channel 1 fatal bus error status flag */
    ENET_DMA_CH1_INT_FLAG_CDE_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 13U),    /*!< channel 1 context descriptor error status flag */
    ENET_DMA_CH1_INT_FLAG_AIE_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 14U),    /*!< channel 1 abnormal interrupt summary flag */
    ENET_DMA_CH1_INT_FLAG_NIS_CLR           = ENET_REGIDX_BIT(DMA_CH1_STATUS_REG_OFFSET, 15U),    /*!< channel 1 normal interrupt summary flag */
} enet_int_flag_clear_enum;

/* ENET MAC addresses */
typedef enum {
    ENET_MAC_ADDRESS0               = ((uint32_t)0x00000000),                       /*!< MAC address0 */
    ENET_MAC_ADDRESS1               = ((uint32_t)0x00000008),                       /*!< MAC address1 */
    ENET_MAC_ADDRESS2               = ((uint32_t)0x00000010)                        /*!< MAC address2 */
} enet_macaddress_enum;
/* descriptor information */
typedef enum {
    TXDESC_COLLISION_COUNT,                                                         /*!< the number of collisions occurred before the frame was transmitted */
    TXDESC_BUFFER_1_ADDR,                                                           /*!< transmit frame buffer 1 address */
    TXDESC_BUFFER_2_ADDR,                                                           /*!< transmit frame buffer 2 address */
    RXDESC_FRAME_LENGTH,                                                            /*!< the byte length of the received frame that was transferred to the buffer */
    RXDESC_BUFFER_1_ADDR,                                                           /*!< receive frame buffer 1 address */
    RXDESC_BUFFER_2_ADDR                                                            /*!< receive frame buffer 2 address */
} enet_descstate_enum;

typedef enum {
    ENET_TX_LPI_USEC_COUNTER_VAL             = ENET_TX_LPI_USEC_CNTR_REG_OFFSET,    /*!< transmit LPI microseconds counter */
    ENET_TX_LPI_TRAN_COUNTER_VAL             = ENET_TX_LPI_TRAN_CNTR_REG_OFFSET,    /*!< transmit LPI transition counter */
    ENET_RX_LPI_USEC_COUNTER_VAL             = ENET_RX_LPI_USEC_CNTR_REG_OFFSET,    /*!< receive LPI microseconds counter */
    ENET_RX_LPI_TRAN_COUNTER_VAL             = ENET_RX_LPI_TRAN_CNTR_REG_OFFSET     /*!< receive LPI transition counter */
} enet_lpi_counter_enum;

/* MMC counters preset mode */
typedef enum {
    ENET_MMC_PRESET_NONE            = 0U,                                                            /*!< do not preset MMC counter */
    ENET_MMC_PRESET_HALF            = ENET_MMC_CONTROL_CNTPRST,                                      /*!< preset all MMC counters to almost-half(0x7FFF FFF0) value */
    ENET_MMC_PRESET_FULL            = ENET_MMC_CONTROL_CNTPRST | ENET_MMC_CONTROL_CNTPRSTLVL         /*!< preset all MMC counters to almost-full(0xFFFF FFF0) value */
} enet_mmc_preset_enum;

/* MMC counters enum */
typedef enum {
    ENET_MMC_TX_OCTET_COUNT_GOOD_BAD               = MMC_TX_OCTET_COUNT_GOOD_BAD_REG_OFFSET,             /*!< ethernet transmit octet count good bad counter */
    ENET_MMC_TX_PACKET_COUNT_GOOD_BAD              = MMC_TX_PACKET_COUNT_GOOD_BAD_REG_OFFSET,            /*!< ethernet transmit packet count good bad counter */
    ENET_MMC_TX_BROADCAST_PACKETS_GOOD             = MMC_TX_BROADCAST_PACKETS_GOOD_REG_OFFSET,           /*!< ethernet transmit broadcast packets good counter */
    ENET_MMC_TX_MULTICAST_PACKETS_GOOD             = MMC_TX_MULTICAST_PACKETS_GOOD_REG_OFFSET,           /*!< ethernet transmit multicast packets good counter */
    ENET_MMC_TX_64OCTETS_PACKETS_GOOD_BAD          = MMC_TX_64OCTETS_PACKETS_GOOD_BAD_REG_OFFSET,        /*!< ethernet transmit 64 octet packets good bad counter */
    ENET_MMC_TX_65TO127OCTETS_PACKETS_GOOD_BAD     = MMC_TX_65TO127OCTET_PACKETS_GOOD_BAD_REG_OFFSET,    /*!< ethernet transmit 65 to 127 octet packets good bad counter */
    ENET_MMC_TX_128TO255OCTETS_PACKETS_GOOD_BAD    = MMC_TX_128TO255OCTET_PACKETS_GOOD_BAD_REG_OFFSET,   /*!< ethernet transmit 128 to 255 octet packets good bad counter */
    ENET_MMC_TX_256TO511OCTETS_PACKETS_GOOD_BAD    = MMC_TX_256TO511OCTET_PACKETS_GOOD_BAD_REG_OFFSET,   /*!< ethernet transmit 256 to 511 octet packets good bad counter */
    ENET_MMC_TX_512TO1023OCTETS_PACKETS_GOOD_BAD   = MMC_TX_512TO1023OCTET_PACKETS_GOOD_BAD_REG_OFFSET,  /*!< ethernet transmit 512 to 1023 octet packets good bad counter */
    ENET_MMC_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD   = MMC_TX_1024TOMAXOCTET_PACKETS_GOOD_BAD_REG_OFFSET,  /*!< ethernet transmit 1024 to max octet packets good bad counter */
    ENET_MMC_TX_UNICAST_PACKETS_GOOD_BAD           = MMC_TX_UNICAST_PACKETS_GOOD_BAD_REG_OFFSET,         /*!< ethernet transmit unicast packets good bad counter */
    ENET_MMC_TX_MULTICAST_PACKETS_GOOD_BAD         = MMC_TX_MULTICAST_PACKETS_GOOD_BAD_REG_OFFSET,       /*!< ethernet transmit multicast packets good bad counter */
    ENET_MMC_TX_BROADCAST_PACKETS_GOOD_BAD         = MMC_TX_BROADCAST_PACKETS_GOOD_BAD_REG_OFFSET,       /*!< ethernet transmit broadcast packets good bad counter */
    ENET_MMC_TX_UNDERFLOW_ERROR_PACKETS            = MMC_TX_UNDERFLOW_ERROR_PACKETS_REG_OFFSET,          /*!< ethernet transmit underflow error packets counter */
    ENET_MMC_TX_SINGLE_COLLISION_GOOD_PACKETS      = MMC_TX_SINGLE_COLLISION_GOOD_PACKETS_REG_OFFSET,    /*!< ethernet transmit single collision good packets counter */
    ENET_MMC_TX_MULTIPLE_COLLISION_GOOD_PACKETS    = MMC_TX_MULTIPLE_COLLISION_GOOD_PACKETS_REG_OFFSET,  /*!< ethernet transmit multiple collision good packets counter */
    ENET_MMC_TX_DEFERRED_PACKETS                   = MMC_TX_DEFERRED_PACKETS_REG_OFFSET,                 /*!< ethernet transmit deferred packets counter */
    ENET_MMC_TX_LATE_COLLISION_PACKETS             = MMC_TX_LATE_COLLISION_PACKETS_REG_OFFSET,           /*!< ethernet transmit late collision packets counter */
    ENET_MMC_TX_EXCESSIVE_COLLISION_PACKETS        = MMC_TX_EXCESSIVE_COLLISION_PACKETS_REG_OFFSET,      /*!< ethernet transmit excessive collision packets counter */
    ENET_MMC_TX_CARRIER_ERROR_PACKETS              = MMC_TX_CARRIER_ERROR_PACKETS_REG_OFFSET,            /*!< ethernet transmit carrier error packets counter */
    ENET_MMC_TX_OCTET_COUNT_GOOD                   = MMC_TX_OCTET_COUNT_GOOD_REG_OFFSET,                 /*!< ethernet transmit octet count good counter */
    ENET_MMC_TX_PACKET_COUNT_GOOD                  = MMC_TX_PACKET_COUNT_GOOD_REG_OFFSET,                /*!< ethernet transmit packet count good counter */
    ENET_MMC_TX_EXCESSIVE_DEFERRAL_ERROR           = MMC_TX_EXCESSIVE_DEFERRAL_ERROR_REG_OFFSET,         /*!< ethernet transmit excessive deferral error counter */
    ENET_MMC_TX_PAUSE_PACKETS                      = MMC_TX_PAUSE_PACKETS_REG_OFFSET,                    /*!< ethernet transmit pause packets counter */
    ENET_MMC_TX_VLAN_PACKETS_GOOD                  = MMC_TX_VLAN_PACKETS_GOOD_REG_OFFSET,                /*!< ethernet transmit vlan packets good counter */
    ENET_MMC_TX_OSIZE_PACKETS_GOOD                 = MMC_TX_OSIZE_PACKETS_GOOD_REG_OFFSET,               /*!< ethernet transmit oversize packets good counter */
    ENET_MMC_RX_PACKETS_COUNT_GOOD_BAD             = MMC_RX_PACKETS_COUNT_GOOD_BAD_REG_OFFSET,           /*!< ethernet receive packet count good bad counter */
    ENET_MMC_RX_OCTET_COUNT_GOOD_BAD               = MMC_RX_OCTET_COUNT_GOOD_BAD_REG_OFFSET,             /*!< ethernet receive octet count good bad counter */
    ENET_MMC_RX_OCTET_COUNT_GOOD                   = MMC_RX_OCTET_COUNT_GOOD_REG_OFFSET,                 /*!< ethernet receive octet count good counter */
    ENET_MMC_RX_BROADCAST_PACKETS_GOOD             = MMC_RX_BROADCAST_PACKETS_GOOD_REG_OFFSET,           /*!< ethernet receive broadcast packets good counter */
    ENET_MMC_RX_MULTICAST_PACKETS_GOOD             = MMC_RX_MULTICAST_PACKETS_GOOD_REG_OFFSET,           /*!< ethernet receive multicast packets good counter */
    ENET_MMC_RX_CRC_ERROR_PACKETS                  = MMC_RX_CRC_ERROR_PACKETS_REG_OFFSET,                /*!< ethernet receive crc error packets counter */
    ENET_MMC_RX_ALIGNMENT_ERROR_PACKETS            = MMC_RX_ALIGNMENT_ERROR_PACKETS_REG_OFFSET,          /*!< ethernet receive alignment error packets counter */
    ENET_MMC_RX_RUNT_ERROR_PACKETS                 = MMC_RX_RUNT_ERROR_PACKETS_REG_OFFSET,               /*!< ethernet receive runt error packets counter */
    ENET_MMC_RX_JABBER_ERROR_PACKETS               = MMC_RX_JABBER_ERROR_PACKETS_REG_OFFSET,             /*!< ethernet receive jabber error packets counter */
    ENET_MMC_RX_UNDERSIZE_PACKETS_GOOD             = MMC_RX_UNDERSIZE_PACKETS_GOOD_REG_OFFSET,           /*!< ethernet receive undersize packets good counter */
    ENET_MMC_RX_OVERSIZE_PACKETS_GOOD              = MMC_RX_OVERSIZE_PACKETS_GOOD_REG_OFFSET,            /*!< ethernet receive oversize packets good counter */
    ENET_MMC_RX_64OCTETS_PACKETS_GOOD_BAD          = MMC_RX_64OCTET_PACKETS_GOOD_BAD_REG_OFFSET,         /*!< ethernet receive 64 octet packets good bad counter */
    ENET_MMC_RX_65TO127OCTETS_PACKETS_GOOD_BAD     = MMC_RX_65TO127OCTET_PACKETS_GOOD_BAD_REG_OFFSET,    /*!< ethernet receive 65 to 127 octet packets good bad counter */
    ENET_MMC_RX_128TO255OCTETS_PACKETS_GOOD_BAD    = MMC_RX_128TO255OCTET_PACKETS_GOOD_BAD_REG_OFFSET,   /*!< ethernet receive 128 to 255 octet packets good bad counter */
    ENET_MMC_RX_256TO511OCTETS_PACKETS_GOOD_BAD    = MMC_RX_256TO511OCTET_PACKETS_GOOD_BAD_REG_OFFSET,   /*!< ethernet receive 256 to 511 octet packets good bad counter */
    ENET_MMC_RX_512TO1023OCTETS_PACKETS_GOOD_BAD   = MMC_RX_512TO1023OCTET_PACKETS_GOOD_BAD_REG_OFFSET,  /*!< ethernet receive 512 to 1023 octet packets good bad counter */
    ENET_MMC_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD   = MMC_RX_1024TOMAXOCTET_PACKETS_GOOD_BAD_REG_OFFSET,  /*!< ethernet receive 1024 to max octet packets good bad counter */
    ENET_MMC_RX_UNICAST_PACKETS_GOOD               = MMC_RX_UNICAST_PACKETS_GOOD_REG_OFFSET,             /*!< ethernet receive unicast packets good counter */
    ENET_MMC_RX_LENGTH_ERROR_PACKETS               = MMC_RX_LENGTH_ERROR_PACKETS_REG_OFFSET,             /*!< ethernet receive length error packets counter */
    ENET_MMC_RX_OUT_OF_RANGE_TYPE_PACKETS          = MMC_RX_OUT_OF_RANGE_TYPE_PACKETS_REG_OFFSET,        /*!< ethernet receive out of range type packets counter */
    ENET_MMC_RX_PAUSE_PACKETS                      = MMC_RX_PAUSE_PACKETS_REG_OFFSET,                    /*!< ethernet receive pause packets counter */
    ENET_MMC_RX_FIFO_OVERFLOW_PACKETS              = MMC_RX_FIFO_OVERFLOW_PACKETS_REG_OFFSET,            /*!< ethernet receive fifo overflow packets counter */
    ENET_MMC_RX_VLAN_PACKETS_GOOD_BAD              = MMC_RX_VLAN_PACKETS_GOOD_BAD_REG_OFFSET,            /*!< ethernet receive vlan packets good bad counter */
    ENET_MMC_RX_WATCHDOG_ERROR_PACKETS             = MMC_RX_WATCHDOG_ERROR_PACKETS_REG_OFFSET,           /*!< ethernet receive watchdog error packets counter */
    ENET_MMC_RX_RECEIVE_ERROR_PACKETS              = MMC_RX_ERROR_PACKETS_REG_OFFSET,                    /*!< ethernet receive error packets counter */
    ENET_MMC_RX_CONTROL_PACKETS_GOOD               = MMC_RX_CONTROL_PACKETS_GOOD_REG_OFFSET,             /*!< ethernet receive control packets good counter */
    ENET_MMC_TX_LPI_USEC_CNTR                      = ENET_TX_LPI_USEC_CNTR_REG_OFFSET,                    /*!< ethernet transmit LPI microseconds counter register offset */
    ENET_MMC_TX_LPI_TRAN_CNTR                      = ENET_TX_LPI_TRAN_CNTR_REG_OFFSET,                    /*!< ethernet transmit LPI transition counter register offset */
    ENET_MMC_RX_LPI_USEC_CNTR                      = ENET_RX_LPI_USEC_CNTR_REG_OFFSET,                    /*!< ethernet receive LPI microseconds counter register offset */
    ENET_MMC_RX_LPI_TRAN_CNTR                      = ENET_RX_LPI_TRAN_CNTR_REG_OFFSET,                    /*!< ethernet receive LPI transition counter register offset */
    ENET_MMC_RXIPV4_GOOD_PACKETS                   = MMC_RXIPV4_GOOD_PACKETS_REG_OFFSET,                  /*!< ethernet receive ipv4 good packets register */
    ENET_MMC_RXIPV4_HEADER_ERROR_PACKETS           = MMC_RXIPV4_HEADER_ERROR_PACKETS_REG_OFFSET,          /*!< ethernet receive ipv4 header error packets register */
    ENET_MMC_RXIPV4_NO_PAYLOAD_PACKETS             = MMC_RXIPV4_NO_PAYLOAD_PACKETS_REG_OFFSET,            /*!< ethernet receive ipv4 no payload packets register */
    ENET_MMC_RXIPV4_FRAGMENTED_PACKETS             = MMC_RXIPV4_FRAGMENTED_PACKETS_REG_OFFSET,            /*!< ethernet receive ipv4 fragmented packets register */
    ENET_MMC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS  = MMC_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_REG_OFFSET, /*!< ethernet receive ipv4 udp checksum disabled packets register */
    ENET_MMC_RXIPV6_GOOD_PACKETS                   = MMC_RXIPV6_GOOD_PACKETS_REG_OFFSET,                  /*!< ethernet receive ipv6 good packets register */
    ENET_MMC_RXIPV6_HEADER_ERROR_PACKETS           = MMC_RXIPV6_HEADER_ERROR_PACKETS_REG_OFFSET,          /*!< ethernet receive ipv6 header error packets register */
    ENET_MMC_RXIPV6_NO_PAYLOAD_PACKETS             = MMC_RXIPV6_NO_PAYLOAD_PACKETS_REG_OFFSET,            /*!< ethernet receive ipv6 no payload packets register */
    ENET_MMC_RXUDP_GOOD_PACKETS                    = MMC_RXUDP_GOOD_PACKETS_REG_OFFSET,                   /*!< ethernet receive udp good packets register */
    ENET_MMC_RXUDP_ERROR_PACKETS                   = MMC_RXUDP_ERROR_PACKETS_REG_OFFSET,                  /*!< ethernet receive udp error packets register */
    ENET_MMC_RXTCP_GOOD_PACKETS                    = MMC_RXTCP_GOOD_PACKETS_REG_OFFSET,                   /*!< ethernet receive tcp good packets register */
    ENET_MMC_RXTCP_ERROR_PACKETS                   = MMC_RXTCP_ERROR_PACKETS_REG_OFFSET,                  /*!< ethernet receive tcp error packets register */
    ENET_MMC_RXICMP_GOOD_PACKETS                   = MMC_RXICMP_GOOD_PACKETS_REG_OFFSET,                  /*!< ethernet receive icmp good packets register */
    ENET_MMC_RXICMP_ERROR_PACKETS                  = MMC_RXICMP_ERROR_PACKETS_REG_OFFSET,                 /*!< ethernet receive icmp error packets register */
    ENET_MMC_RXIPV4_GOOD_OCTETS                    = MMC_RXIPV4_GOOD_OCTETS_REG_OFFSET,                   /*!< ethernet receive ipv4 good octets register */
    ENET_MMC_RXIPV4_HEADER_ERROR_OCTETS            = MMC_RXIPV4_HEADER_ERROR_OCTETS_REG_OFFSET,           /*!< ethernet receive ipv4 header error octets register */
    ENET_MMC_RXIPV4_NO_PAYLOAD_OCTETS              = MMC_RXIPV4_NO_PAYLOAD_OCTETS_REG_OFFSET,             /*!< ethernet receive ipv4 no payload octets register */
    ENET_MMC_RXIPV4_FRAGMENTED_OCTETS              = MMC_RXIPV4_FRAGMENTED_OCTETS_REG_OFFSET,             /*!< ethernet receive ipv4 fragmented octets register */
    ENET_MMC_RXIPV4_UDP_CHECKSUM_DISABLED_OCTETS   = MMC_RXIPV4_UDP_CHECKSUM_DISABLED_OCTETS_REG_OFFSET,  /*!< ethernet receive ipv4 udp checksum disabled octets register */
    ENET_MMC_RXIPV6_GOOD_OCTETS                    = MMC_RXIPV6_GOOD_OCTETS_REG_OFFSET,                   /*!< ethernet receive ipv6 good octets register */
    ENET_MMC_RXIPV6_HEADER_ERROR_OCTETS            = MMC_RXIPV6_HEADER_ERROR_OCTETS_REG_OFFSET,           /*!< ethernet receive ipv6 header error octets register */
    ENET_MMC_RXIPV6_NO_PAYLOAD_OCTETS              = MMC_RXIPV6_NO_PAYLOAD_OCTETS_REG_OFFSET,             /*!< ethernet receive ipv6 no payload octets register */
    ENET_MMC_RXUDP_GOOD_OCTETS                     = MMC_RXUDP_GOOD_OCTETS_REG_OFFSET,                    /*!< ethernet receive udp good octets register */
    ENET_MMC_RXUDP_ERROR_OCTETS                    = MMC_RXUDP_ERROR_OCTETS_REG_OFFSET,                   /*!< ethernet receive udp error octets register */
    ENET_MMC_RXTCP_GOOD_OCTETS                     = MMC_RXTCP_GOOD_OCTETS_REG_OFFSET,                    /*!< ethernet receive tcp good octets register */
    ENET_MMC_RXTCP_ERROR_OCTETS                    = MMC_RXTCP_ERROR_OCTETS_REG_OFFSET,                   /*!< ethernet receive tcp error octets register */
    ENET_MMC_RXICMP_GOOD_OCTETS                    = MMC_RXICMP_GOOD_OCTETS_REG_OFFSET,                   /*!< ethernet receive icmp good octets register */
    ENET_MMC_RXICMP_ERROR_OCTETS                   = MMC_RXICMP_ERROR_OCTETS_REG_OFFSET,                  /*!< ethernet receive icmp error octets register */
    ENET_MMC_MMC_FPE_TX_FRAGMENT                   = MMC_MMC_FPE_TX_FRAGMENT_CNTR_REG_OFFSET,             /*!< ethernet MMC FPE transmit fragment counter register */
    ENET_MMC_MMC_TX_HOLD_REQ                       = MMC_MMC_TX_HOLD_REQ_CNTR_REG_OFFSET,                 /*!< ethernet MMC FPE hold request counter register */
    ENET_MMC_RX_PACKETS_ASSEMBLY_ERR               = MMC_RX_PACKETS_ASSEMBLY_ERR_CNTR_REG_OFFSET,         /*!< ethernet MMC receive packets assembly error counter register */
    ENET_MMC_RX_PACKETS_SMD_ERR                    = MMC_RX_PACKETS_SMD_ERR_CNTR_REG_OFFSET,              /*!< ethernet MMC receive packets SMD error counter register */
    ENET_MMC_RX_PACKETS_ASSEMBLY_OK                = MMC_RX_PACKETS_ASSEMBLY_OK_CNTR_REG_OFFSET,          /*!< ethernet MMC receive packets assembly ok counter register */
    ENET_MMC_RX_FPE_FRAGMENT                       = MMC_RX_FPE_FRAGMENT_CNTR_REG_OFFSET                  /*!< ethernet MMC receive FPE fragment counter register */
} enet_mmc_counter_enum;

/* current RX/TX descriptor/buffer/descriptor table address get */
typedef enum {
    ENET_CH0_RX_DESC_TABLE              = DMA_CH0_RDTADDR_REG_OFFSET,                       /*!< DMA channel 0 RX descriptor table */
    ENET_CH1_RX_DESC_TABLE              = DMA_CH1_RDTADDR_REG_OFFSET,                       /*!< DMA channel 1 RX descriptor table */
    ENET_CH0_RX_DESC_TAIL               = DMA_CH0_RDTAIL_REG_OFFSET,                        /*!< DMA channel 0 RX descriptor tail pointer */
    ENET_CH1_RX_DESC_TAIL               = DMA_CH1_RDTAIL_REG_OFFSET,                        /*!< DMA channel 1 RX descriptor tail pointer */
    ENET_CH0_RX_CURRENT_DESC            = DMA_CH0_CRDADDR_REG_OFFSET,                       /*!< DMA channel 0  current RX descriptor */
    ENET_CH1_RX_CURRENT_DESC            = DMA_CH1_CRDADDR_REG_OFFSET,                       /*!< DMA channel 1 current RX descriptor */
    ENET_CH0_RX_CURRENT_BUFFER          = DMA_CH0_CRBADDR_REG_OFFSET,                       /*!< DMA channel 0 current RX buffer */
    ENET_CH1_RX_CURRENT_BUFFER          = DMA_CH1_CRBADDR_REG_OFFSET,                       /*!< DMA channel 1 current RX buffer */
    ENET_CH0_TX_DESC_TABLE              = DMA_CH0_TDTADDR_REG_OFFSET,                       /*!< DMA channel 0 TX descriptor table */
    ENET_CH1_TX_DESC_TABLE              = DMA_CH1_TDTADDR_REG_OFFSET,                       /*!< DMA channel 1 TX descriptor table */
    ENET_CH0_TX_DESC_TAIL               = DMA_CH0_TDTAIL_REG_OFFSET,                        /*!< DMA channel 0 TX descriptor tail pointer */
    ENET_CH1_TX_DESC_TAIL               = DMA_CH1_TDTAIL_REG_OFFSET,                        /*!< DMA channel 1 TX descriptor tail pointer */
    ENET_CH0_TX_CURRENT_DESC            = DMA_CH0_CTDADDR_REG_OFFSET,                       /*!< DMA channel 0 current TX descriptor */
    ENET_CH1_TX_CURRENT_DESC            = DMA_CH1_CTDADDR_REG_OFFSET,                       /*!< DMA channel 1 current TX descriptor */
    ENET_CH0_TX_CURRENT_BUFFER          = DMA_CH0_CTBADDR_REG_OFFSET,                       /*!< DMA channel 0 current TX buffer */
    ENET_CH1_TX_CURRENT_BUFFER          = DMA_CH1_CTBADDR_REG_OFFSET,                       /*!< DMA channel 1 current TX buffer */
} enet_desc_reg_enum;

/* phy mode and mac loopback configurations */
typedef enum {
    ENET_AUTO_NEGOTIATION           = 0x01U,                                                         /*!< PHY auto negotiation */
    ENET_100M_FULLDUPLEX            = (ENET_MAC_CONFIGURATION_FES | ENET_MAC_CONFIGURATION_DM),      /*!< 100Mbit/s, full-duplex */
    ENET_100M_HALFDUPLEX            = ENET_MAC_CONFIGURATION_FES,                                    /*!< 100Mbit/s, half-duplex */
    ENET_10M_FULLDUPLEX             = ENET_MAC_CONFIGURATION_DM,                                     /*!< 10Mbit/s, full-duplex */
    ENET_10M_HALFDUPLEX             = (uint32_t)0x00000000U,                                         /*!< 10Mbit/s, half-duplex */
    ENET_LOOPBACKMODE               = (ENET_MAC_CONFIGURATION_LM | ENET_MAC_CONFIGURATION_DM)        /*!< MAC in loopback mode at the MII */
} enet_mediamode_enum;
/* IP frame checksum function */
typedef enum {
    ENET_NO_AUTOCHECKSUM                = (uint32_t)0x00000000U,                             /*!< disable IP frame checksum function */
    ENET_AUTOCHECKSUM_DROP_FAILFRAMES   = ENET_MAC_CONFIGURATION_IPC,                        /*!< enable IP frame checksum function */
    ENET_AUTOCHECKSUM_ACCEPT_FAILFRAMES = (ENET_MAC_CONFIGURATION_IPC | ENET_MTL_RXQ0_OPERATION_MODE_DIS_TCP_EF | ENET_MTL_RXQ1_OPERATION_MODE_DIS_TCP_EF) /*!< enable IP frame checksum function, and the received frame
                                                                                                                                                                with only payload error but no other errors will not be dropped */
} enet_chksumconf_enum;

typedef enum {
    DMA_TX_OVER_RX   = 0U,                    /*!< Tx DMA has priority over the Rx DMA */
    DMA_RX_OVER_TX = 1U                       /*!< Rx DMA has priority over the Tx DMA */
} enet_dmapriority_enum;

typedef enum {
    ARBITRATION_RXTX_1_1 = ENET_ARBITRATION_RXTX_1_1,                   /*!< receive and transmit priority ratio is 1:1*/
    ARBITRATION_RXTX_2_1 = ENET_ARBITRATION_RXTX_2_1,                   /*!< receive and transmit priority ratio is 2:1*/
    ARBITRATION_RXTX_3_1 = ENET_ARBITRATION_RXTX_3_1,                   /*!< receive and transmit priority ratio is 3:1*/
    ARBITRATION_RXTX_4_1 = ENET_ARBITRATION_RXTX_4_1,                   /*!< receive and transmit priority ratio is 4:1*/
    ARBITRATION_RXTX_5_1 = ENET_ARBITRATION_RXTX_5_1,                   /*!< receive and transmit priority ratio is 5:1*/
    ARBITRATION_RXTX_6_1 = ENET_ARBITRATION_RXTX_6_1,                   /*!< receive and transmit priority ratio is 6:1*/
    ARBITRATION_RXTX_7_1 = ENET_ARBITRATION_RXTX_7_1,                   /*!< receive and transmit priority ratio is 7:1*/
    ARBITRATION_RXTX_8_1 = ENET_ARBITRATION_RXTX_8_1,                   /*!< receive and transmit priority ratio is 8:1*/
    ARBITRATION_TXRX_1_1 = ENET_ARBITRATION_TXRX_1_1,                   /*!< transmit and receive priority ratio is 1:1*/
    ARBITRATION_TXRX_2_1 = ENET_ARBITRATION_TXRX_2_1,                   /*!< transmit and receive priority ratio is 2:1*/
    ARBITRATION_TXRX_3_1 = ENET_ARBITRATION_TXRX_3_1,                   /*!< transmit and receive priority ratio is 3:1*/
    ARBITRATION_TXRX_4_1 = ENET_ARBITRATION_TXRX_4_1,                   /*!< transmit and receive priority ratio is 4:1*/
    ARBITRATION_TXRX_5_1 = ENET_ARBITRATION_TXRX_5_1,                   /*!< transmit and receive priority ratio is 5:1*/
    ARBITRATION_TXRX_6_1 = ENET_ARBITRATION_TXRX_6_1,                   /*!< transmit and receive priority ratio is 6:1*/
    ARBITRATION_TXRX_7_1 = ENET_ARBITRATION_TXRX_7_1,                   /*!< transmit and receive priority ratio is 7:1*/
    ARBITRATION_TXRX_8_1 = ENET_ARBITRATION_TXRX_8_1                    /*!< transmit and receive priority ratio is 8:1*/
} enet_dmapriorityratio_enum;

/* received frame filter function */
typedef enum {
    ENET_PROMISCUOUS_MODE           = ENET_MAC_PACKET_FILTER_PR,                             /*!< promiscuous mode enabled */
    ENET_RECEIVEALL                 = (int32_t)ENET_MAC_PACKET_FILTER_RA,                    /*!< all received frame are forwarded to application */
    ENET_BROADCAST_FRAMES_PASS      = (uint32_t)0x00000000U,                                 /*!< the address filters pass all received broadcast frames */
    ENET_BROADCAST_FRAMES_DROP      = ENET_MAC_PACKET_FILTER_DBF                             /*!< the address filters filter all incoming broadcast frames */
} enet_frmrecept_enum;

/* received frame filter function */
typedef enum {
    ENET_MISMATCH_ARP_PACKET_DROP_ENABLE = 0U,           /*!< packet for which target protocol address does not match IPv4 address is dropped in the MTL layer */
    ENET_MISMATCH_ARP_PACKET_DROP_DISABLE,               /*!< when target protocol address does not match, packet is forwarded to MTL maintaining backward compatibility */
    ENET_PACKET_DUPLICATION_ENABLE,                      /*!< the received packet with multicast/broadcast destination address is routed to multiple receive DMA channels */
    ENET_PACKET_DUPLICATION_DISABLE,                     /*!< the received packet with multicast/broadcast destination address is not routed to multiple receive DMA channels */
    ENET_USP_PACKET_DETECT_ENABLE,                       /*!< the MAC detects the slow protocol packets with unicast address of the station */
    ENET_USP_PACKET_DETECT_DISABLE,                      /*!< the MAC detects only slow protocol packets with the slow protocol multicast address specified in the IEEE 802.3-2015, Section 5 */
    ENET_SLOW_PROTOCOL_DETECT_ENABLE,                    /*!< MAC processes the slow protocol packets (Ether Type 0x8809) and provides the slow protocol sub-type and code fields in Rx status */
    ENET_SLOW_PROTOCOL_DETECT_DISABLE,                   /*!< the MAC forwards all error-free slow protocol packets to the application. The MAC considers such packets as normal Type packets */
    ENET_CRC_CHECK_ENABLE,                               /*!< the MAC receiver always checks the CRC field in the received packets */
    ENET_CRC_CHECK_DISABLE                               /*!< the MAC receiver does not check the CRC field in the received packets */
} enet_extend_macconfig_enum;

/* function option, used for ENET initialization */
typedef enum {
    FORWARD_OPTION                  = BIT(0),                                       /*!< configure the frame forward related parameters */
    DMABUS_OPTION                   = BIT(1),                                       /*!< configure the DMA bus mode related parameters */
    DMACH0_MAXBURST_OPTION          = BIT(2),                                       /*!< configure the DMA channel 0 max burst related parameters */
    DMACH1_MAXBURST_OPTION          = BIT(3),                                       /*!< configure the DMA channel 1 max burst related parameters */
    DMA_ARBITRATION_OPTION          = BIT(4),                                       /*!< configure the DMA arbitration related parameters */
    TX0STORE_OPTION                 = BIT(5),                                       /*!< configure the transmit queue 0 store forward mode related parameters */
    RX0STORE_OPTION                 = BIT(6),                                       /*!< configure the receive queue 0 store forward mode related parameters */
    TX1STORE_OPTION                 = BIT(7),                                       /*!< configure the transmit queue 1 store forward mode related parameters */
    RX1STORE_OPTION                 = BIT(8),                                       /*!< configure the receive queue 1 store forward mode related parameters */
    VLAN_CONFIG_OPTION              = BIT(9),                                       /*!< configure the VLAN tag related parameters */
    VLAN_COMPARISON_OPTION          = BIT(10),                                      /*!< configure the VLAN tag related parameters */
    VLAN_INSERT_OPTION              = BIT(11),                                      /*!< configure the VLAN tag insertion or replacement related parameters */
    INNERVLAN_INSERT_OPTION         = BIT(12),                                      /*!< configure the INNER VLAN tag insertion or replacement related parameters */
    FLOWCTL_OPTION                  = BIT(13),                                      /*!< configure the flow control related parameters */
    HASHH_OPTION                    = BIT(14),                                      /*!< configure the hash list high 32-bit related parameters */
    HASHL_OPTION                    = BIT(15),                                      /*!< configure the hash list low 32-bit related parameters */
    FILTER_OPTION                   = BIT(16),                                      /*!< configure the frame filter control related parameters */
    HALFDUPLEX_OPTION               = BIT(17),                                      /*!< configure the halfduplex related parameters */
    FULLDUPLEX_OPTION               = BIT(18),                                      /*!< configure the fullduplex related parameters */
    PACKETSIZE_OPTION               = BIT(19),                                      /*!< configure the packet size related parameters */
    TIMER_OPTION                    = BIT(20),                                      /*!< configure the frame timer related parameters */
    MACCONTROL_OPTION               = BIT(21),                                      /*!< configure the frame timer related parameters */
    INTERFRAMEGAP_OPTION            = BIT(22),                                      /*!< configure the inter frame gap related parameters */
    ECCCONTROL_OPTION               = BIT(23),                                      /*!< configure the ECC control related parameters */
    DPPCONTROL_OPTION               = BIT(24),                                      /*!< configure the DPP control related parameters */
    FSMCONTROL_OPTION               = BIT(25),                                      /*!< configure the FSM control related parameters */
    ESTCONTROL_OPTION               = BIT(26),                                      /*!< configure the EST control related parameters */
    FPECONTROL_OPTION               = BIT(27)                                       /*!< configure the FPE control related parameters */
} enet_option_enum;

typedef enum {
    MTL0 = 0U,                          /*!< MAC transaction layer 0 */
    MTL1 = 1U                           /*!< MAC transaction layer 1 */
} enet_mtl_enum;

typedef enum {
    RMII_MODE = 0U,                     /*!< MAC PHY interface in RMII mode */
    MII_MODE = 1U                       /*!< MAC PHY interface in MII mode */
} enet_modetype_enum;

typedef enum {
    MAC_LAYER_SPEED_10M = 0U,           /*!< MAC PHY interface in 10M speed */
    MAC_LAYER_SPEED_100M = 1U           /*!< MAC PHY interface in 100M speed */
} enet_speedtype_enum;

typedef enum {
    ENET_HALF_DUPLEX = 0U,             /*!< MAC PHY interface in half-duplex mode */
    ENET_FULL_DUPLEX = 1U              /*!< MAC PHY interface in full-duplex mode */
} enet_duplextype_enum;


typedef enum {
    DMA_MISS_FRAME_COUNT = 0U,         /*!< missed frame counter */
    DMA_ACCEPT_FRAME_COUNT = 1U        /*!< received frame counter */
} enet_dmacounter_enum;

typedef enum {
    RXQ0 = 0U,                        /*!< receive queue channel 0 */
    RXQ1 = 1U                         /*!< receive queue channel 1 */
} enet_rxq_enum;

typedef enum {
    PREEMPTION_PACKET = 0U,                     /*!< preemption packet */
    EXPRESS_PACKET = 1U                         /*!< express packet */
} enet_packet_type_enum;

typedef enum {
    TXQ0 = 0U,                        /*!< transmit queue 0 */
    TXQ1 = 1U                         /*!< transmit queue 1 */
} enet_txq_enum;


typedef enum {
    DMACH0 = 0U,                      /*!< DMA channel 0 */
    DMACH1 = 1U                       /*!< DMA channel 1 */
} enet_dmach_enum;

typedef enum {
    PARSABLE_ENTRY = 0U,              /*!< parsable entries in the Instruction table */
    VALID_ENTRY = 1U                  /*!< valid entries in the Instruction table */
} enet_entry_type_enum;

typedef enum {
    MTL_PAESER_BYPASS_COUNTER = 0U,              /*!< parsable bypass counter */
    MTL_PAESER_ERROR_COUNTER = 1U,               /*!< parsable error counter */
    MTL_PAESER_DROP_COUNTER = 2U                 /*!< parsable drop counter */
} enet_parser_counter_enum;

/* structure for initialization of the ENET  */
typedef struct {
    uint32_t option_enable;                                                         /*!< select which function to configure */
    uint32_t forward_frame;                                                         /*!< frame forward related parameters */
    uint32_t dmabus_mode;                                                           /*!< DMA bus mode related parameters */
    uint32_t dmach0_maxburst;                                                       /*!< DMA channel 0 max burst related parameters */
    uint32_t dmach1_maxburst;                                                       /*!< DMA channel 1 max burst related parameters */
    uint32_t dma_arbitration;                                                       /*!< DMA Tx and Rx arbitration related parameters */
    uint32_t tx0store_forward_mode;                                                 /*!< transmit queue 0 store forward mode related parameters */
    uint32_t rx0store_forward_mode;                                                 /*!< receive queue 0 store forward mode related parameters */
    uint32_t tx1store_forward_mode;                                                 /*!< transmit queue 1 store forward mode related parameters */
    uint32_t rx1store_forward_mode;                                                 /*!< receive queue 1 store forward mode related parameters */
    uint32_t dma_function;                                                          /*!< DMA control related parameters */
    uint32_t vlan_config;                                                           /*!< VLAN tag related parameters */
    uint32_t vlan_compare;                                                          /*!< VLAN tag filter related parameters */
    uint32_t vlan_insert;                                                           /*!< VLAN tag insertion related parameters */
    uint32_t innervlan_insert;                                                      /*!< INNER VLAN tag insertion related parameters */
    uint32_t flow_control;                                                          /*!< flow control related parameters */
    uint32_t hashtable_high;                                                        /*!< hash list high 32-bit related parameters */
    uint32_t hashtable_low;                                                         /*!< hash list low 32-bit related parameters */
    uint32_t framesfilter_mode;                                                     /*!< frame filter control related parameters */
    uint32_t halfduplex_param;                                                      /*!< halfduplex related parameters */
    uint32_t fullduplex_param;                                                      /*!< halfduplex related parameters */
    uint32_t packetsize_config;                                                     /*!< halfduplex related parameters */
    uint32_t timer_config;                                                          /*!< frame timer related parameters */
    uint32_t maccontrol_param;                                                      /*!< halfduplex related parameters */
    uint32_t interframegap;                                                         /*!< inter frame gap related parameters */
    uint32_t ecccontrol;                                                            /*!< ecc control related parameters */
    uint32_t dppcontrol;                                                            /*!< dpp control related parameters */
    uint32_t fsmcontrol;                                                            /*!< fsm control related parameters */
    uint32_t estcontrol;                                                            /*!< est control related parameters */
    uint32_t fpecontrol;                                                            /*!< fpe control related parameters */
} enet_initpara_struct;

/* receive queue enable configuration */
typedef enum {
    QUE_OP_MODE_DISABLE        = 0U,                                             /*!< Queue not enabled */
    QUE_OP_MODE_AVB_ENABLE     = 1U,                                             /*!< Queue enabled for Audio-Video Bridging */
    QUE_OP_MODE_ENABLE         = 2U                                              /*!< Queue enabled for Data Center Bridging or Generic Traffic */
} enet_queopmode_enum;

/* L3/L4 filter selection */
typedef enum {
    L3L4_FILTER0      = 0U,                                   /*!< L3/L4 filter 0 */
    L3L4_FILTER1      = 1U,                                   /*!< L3/L4 filter 1 */
    L3L4_FILTER2      = 2U,                                   /*!< L3/L4 filter 2 */
    L3L4_FILTER3      = 3U                                    /*!< L3/L4 filter 3 */
} enet_l3l4_filter_enum;


/* PPS selection */
typedef enum {
    PPS0      = 0U,                                   /*!< pulse-per-second output 0 */
    PPS1      = 1U,                                   /*!< pulse-per-second output 1 */
    PPS2      = 2U,                                   /*!< pulse-per-second output 2 */
    PPS3      = 3U                                    /*!< pulse-per-second output 3 */
} enet_pps_enum;

/* MCGR selection */
typedef enum {
    MCGR0      = 0U,                                  /*!< media clock generation and recovery 0 */
    MCGR1      = 1U,                                  /*!< media clock generation and recovery 1 */
    MCGR2      = 2U,                                  /*!< media clock generation and recovery 2 */
    MCGR3      = 3U                                   /*!< media clock generation and recovery 3 */
} enet_mcgr_enum;

/* the Tx scheduling algorithm */
typedef enum {
    STRICT_PRIORITY_TX        = ENET_TX_SCHEDULING_ALGO_SP,                     /*!< SP arbitration mode */
    WEIGHTED_ROUND_ROBIN      = ENET_TX_SCHEDULING_ALGO_WRR                     /*!< WRR arbitration mode */
} enet_txqalgotype_enum;

/* the Rx scheduling algorithm */
typedef enum {
    STRICT_PRIORITY_RX            =  MTL_OPERATION_MODE_RAA(0U),               /*!< SP arbitration mode */
    WEIGHTED_STRICT_PRIORITY      =  MTL_OPERATION_MODE_RAA(1U)                /*!< WRR arbitration mode */
} enet_rxqalgotype_enum;

/* the DMA transmit arbitration algorithm */
typedef enum {
    FIXED_PRIORITY_DMA_TX             = ENET_TX_CHANNEL_ARBITRATION_FP,                /*!< FP arbitration mode */
    WEIGHTED_STRICT_PRIORITY_DMA_TX   = ENET_TX_CHANNEL_ARBITRATION_WSP,               /*!< weighted strict priority arbitration mode */
    WEIGHTED_ROUND_ROBIN_DMA_TX       = ENET_TX_CHANNEL_ARBITRATION_WRR                /*!< WRR arbitration mode */
} enet_dmaalgotype_enum;

/* the DMA scheduling algorithm */
typedef enum {
    FIXED_PRIORITY_DMA_SCHEME            = ENET_TXRX_FP,                         /*!< FP arbitration scheme */
    WEIGHTED_ROUND_ROBIN_DMA_SCHEME      = ENET_TXRX_WRR                         /*!< WRR arbitration scheme */
} enet_dmaarbi_scheme_enum;

/* Tx threshold level configuration */
typedef enum {
    TX_THRESHOLD_32BYTES      = 0U,                   /*!< threshold level is 32 Bytes */
    TX_THRESHOLD_64BYTES      = 1U,                   /*!< threshold level is 64 Bytes */
    TX_THRESHOLD_96BYTES      = 2U,                   /*!< threshold level is 96 Bytes */
    TX_THRESHOLD_128BYTES     = 3U,                   /*!< threshold level is 128 Bytes */
    TX_THRESHOLD_192BYTES     = 4U,                   /*!< threshold level is 192 Bytes */
    TX_THRESHOLD_256BYTES     = 5U,                   /*!< threshold level is 256 Bytes */
    TX_THRESHOLD_284BYTES     = 6U,                   /*!< threshold level is 284 Bytes */
    TX_THRESHOLD_512BYTES     = 7U                    /*!< threshold level is 512 Bytes */
} enet_txqthresholdtype_enum;

/* TxFIFO operation mode */
typedef enum {
    TX_MODE_CUTTHROUGH      = 0U,                     /*!< TxFIFO operates in cut-through mode */
    TX_MODE_STOREFORWARD    = 1U                      /*!< TxFIFO operates in store-and-forward mode */
} enet_txqmodetype_enum;

/* LPI timer selection */
typedef enum {
    LPI_LS_TIMER      = 0U,                           /*!< specifie the minimum time (in milliseconds) for which the link status from the PHY should be up */
    LPI_TW_TIMER      = 1U,                           /*!< specifies the minimum time (in microseconds) for which the MAC waits after it stops transmitting the LPI pattern to the PHY */
    LPI_ENTRY_TIMER   = 2U                            /*!< specifies the time in microseconds the MAC waits to enter LPI mode */
} enet_lpitimer_enum;

/* select the FSM and Interface Timeout type */
typedef enum {
    ENET_LARGE_MODE_TIMEOUT           = 0U,           /*!< Large Mode Timeout Value */
    ENET_NORMAL_MODE_TIMEOUT          = 1U,           /*!< Normal Mode Timeout Value */
    ENET_CSR_CLOCK_VAL                = 2U            /*!< CSR Clocks for 1us Tic */
} enet_fsmtimeout_enum;

/* Rx threshold level configuration */
typedef enum {
    RX_THRESHOLD_32BYTES     = 0U,                   /*!< threshold level is 32 Bytes */
    RX_THRESHOLD_64BYTES     = 1U,                   /*!< threshold level is 64 Bytes */
    RX_THRESHOLD_96BYTES     = 2U,                   /*!< threshold level is 96 Bytes */
    RX_THRESHOLD_128BYTES    = 3U                    /*!< threshold level is 128 Bytes */
} enet_rxqthresholdtype_enum;

/* RxFIFO operation mode */
typedef enum {
    RX_MODE_CUTTHROUGH      = 0U,                    /*!< RxFIFO operates in cut-through mode */
    RX_MODE_STOREFORWARD    = 1U                     /*!< RxFIFO operates in store-and-forward mode */
} enet_rxqmodetype_enum;

/* PHY operation direction select */
typedef enum {
    ENET_PHY_READ           = 0U,                    /*!< read PHY */
    ENET_PHY_WRITE          = 1U                     /*!< write PHY */
} enet_phydirection_enum;

/* ENET initialization related parameters */
typedef enum {
    ENET_MAC_INIT_STRUCT          = 0U,               /*!< ENET MAC initiliaze parameters struct */
    ENET_DMA_CH0_INIT_STRUCT      = 1U,               /*!< ENET DMA channel 0 initiliaze parameters struct */
    ENET_DMA_CH1_INIT_STRUCT      = 2U,               /*!< ENET DMA channel 0 initiliaze parameters struct */
    ENET_MTL0_INIT_STRUCT         = 3U,               /*!< ENET MTL0 initiliaze parameters struct */
    ENET_MTL1_INIT_STRUCT         = 4U,               /*!< ENET MTL1 initiliaze parameters struct */
    ENET_TXQ1_CBS_INIT_STRUCT     = 5U,               /*!< ENET TX queue1 CBS initiliaze parameters struct */
    ENET_PHY_CFG_INIT_STRUCT      = 6U,               /*!< ENET PHY config initiliaze parameters struct */
    ENET_EST_CFG_INIT_STRUCT      = 7U,               /*!< ENET EST config initiliaze parameters struct */
    ENET_GCL_CFG_INIT_STRUCT      = 8U,               /*!< ENET GCL config initiliaze parameters struct */
    ENET_FPE_CFG_INIT_STRUCT      = 9U                /*!< ENET FPE config initiliaze parameters struct */
} enet_struct_type_enum;

/* ENET initialization related parameters */
typedef enum {
    INT_MODE0      = ENET_INTERRUPT_MODE0,            /*!< interrupt mode 0 */
    INT_MODE1      = ENET_INTERRUPT_MODE1,            /*!< interrupt mode 1 */
    INT_MODE2      = ENET_INTERRUPT_MODE2,            /*!< interrupt mode 2 */
} enet_dma_intmode_enum;

/* ENET one-step timestamp related parameters */
typedef enum {
    TIMESTAMP_EGRESS      = 0U,                       /*!< timestamp egress */
    TIMESTAMP_INGRESS     = 1U                        /*!< timestamp ingress */
} enet_timestamp_type_enum;

typedef enum {
    LATENCY_NANOSECOND      = 0U,                     /*!< timestamp egress */
    LATENCY_SUBNANOSECOND   = 1U                      /*!< timestamp ingress */
} enet_timestamp_latency_enum;

/* ENET initialization related parameters */
typedef enum {
    MAC_AV_TAG_PACKET_QUEUE          = 0U,            /*!< AV untagged control packets queue */
    MAC_PTP_PACKET_QUEUE             = 4U,            /*!< PTP packets queue */
    MAC_UNTAGGED_PACKET_QUEUE        = 12U,           /*!< untagged packet queue */
    MAC_MULTI_BROAD_PACKET_QUEUE     = 16U,           /*!< multicast and broadcast queue */
    MAC_FPE_RESIDUE_PACKET_QUEUE     = 24U            /*!< frame preemption residue queue */
} enet_frame_type_enum;

/* ENET MTL GCL list related parameters */
typedef enum {
    GCL_LIST0          = 0U,                          /*!< Gate control list number 0 */
    GCL_LIST1          = 1U                           /*!< Gate control list number 1 */
} enet_gcl_enum;

/* ENET MTL EST error related parameters */
typedef enum {
    SCHEDULE_ERROR          = 0U,                     /*!< schedule error */
    FRAME_SIZE_ERROR        = 1U                      /*!< frame size error */
} enet_est_error_enum;

/* structure for phy configuration */
typedef struct {
    uint8_t PhyAddr;                                  /*!< the phy address */
    uint16_t RegAddr;                                 /*!< the phy register address */
    uint16_t DevAddr;                                 /*!< the device address */
    uint16_t PhyValue;                                /*!< the value of phy */
} enet_phyconfig_struct;

/* structure for EST configuration */
typedef struct {
    uint32_t BTRinsecond;                            /*!< the second value of base time */
    uint32_t BTRinnanosecond;                        /*!< the nanosecond value of base time */
    uint32_t CTRinsecond;                            /*!< the second value of cycle time */
    uint32_t CTRinnanosecond;                        /*!< the nanosecond value of cycle time */
    uint32_t TERtime;                                /*!< the value of extension time */
    uint16_t LLRdepth;                               /*!< the value of list length */
} enet_ESTConfig_struct;

/* structure for FPE configuration */
typedef struct {
    ControlStatus FPEenable;                         /*!< configure the FPE function to make it possible */
    uint32_t Relasetime;                             /*!< the value of relase time */
    uint16_t Holdtime;                               /*!< the value of hold time */
} enet_FPEConfig_struct;

/* structure for FPE configuration */
typedef struct {
    uint8_t Ctrlconfig;                              /*!< configure the gate control */
    uint32_t Ethtimeinterval;                        /*!< the value of time interval */
} enet_GCLConfig_struct;

/* structure for CBS configuration */
typedef struct {
    uint32_t IdleSlopeCredit;                        /*!< the value of idleSlopeCredit */
    uint32_t SendSlopeCredit;                        /*!< the value of sendSlopeCredit, */
    uint32_t loCredit;                               /*!< the value of loCredit */
    uint32_t HiCredit;                               /*!< the value of hiCredit */
    ControlStatus CreditControl;                     /*!< the configuration of Credit control */
} enet_cbs_config_struct;

/* structure for MTL configuration */
typedef struct {
    enet_txqalgotype_enum TxqAlgo;                   /*!< the Tx scheduling algorithm */
    enet_txqthresholdtype_enum Txqthreshold;         /*!< the threshold of Tx queue */
    enet_txqmodetype_enum Txqforwardmode;            /*!< the forward mode of Tx queue */
    uint32_t Txweight;                               /*!< the weight of Tx queue */
    uint32_t Txprioritysel;                          /*!< the priority selection of Tx queue */
    enet_queopmode_enum Txqmode;                     /*!< the mode of Tx queue */
    enet_rxqalgotype_enum RxqAlgo;                   /*!< the Rx scheduling algorithm */
    enet_rxqthresholdtype_enum Rxqthreshold;         /*!< the threshold of Rx queue */
    enet_rxqmodetype_enum Rxqforwardmode;            /*!< the forward mode of Rx queue */
    uint32_t Rxweight;                               /*!< the weight of Rx queue */
    uint32_t Rxprioritysel;                          /*!< the priority selection of Rx queue */
    enet_queopmode_enum Rxqmode;                     /*!< the mode of Rx queue */
    enet_dmach_enum dmachsel;                        /*!< the DMA channel selection of queue */
} enet_mtl_config_struct;

/* structure for DMA configuration */
typedef struct {
    enet_dma_intmode_enum interruptmode;             /*!< the DMA interrupt mode */
    uint8_t addrbeats;                               /*!< the configuration of address beats */
    uint32_t burstlength;                            /*!< the burst length */
    uint32_t bufsize;                                /*!< the buffer size */
    enet_dmapriorityratio_enum priorityratio;        /*!< the DMA priority ratio */
    enet_dmaalgotype_enum DmaTxAlgo;                 /*!< the Tx scheduling algorithm */
    enet_dmaarbi_scheme_enum DmaScheme;              /*!< the threshold of Tx queue */
} enet_dma_config_struct;

/* structure for MAC configuration */
typedef struct {
    enet_speedtype_enum Speedstatus;                 /*!< the speed selection of MAC PHY interface */
    enet_duplextype_enum Duplexstatus;               /*!< the duplex selection of MAC PHY interface */
    uint32_t MacConfig;                              /*!< the configuration of MAC */
    uint32_t FilterConfig;                           /*!< the configuration of MAC filter */
    uint32_t Txqflowctrl;                            /*!< the configuration of TXQ0 flow control */
} enet_mac_config_struct;                     

/* structure for ENET DMA desciptors */
typedef struct {
    uint32_t DES0;                                   /*!< the ENET DMA desciptors 0 */
    uint32_t DES1;                                   /*!< the ENET DMA desciptors 1 */
    uint32_t DES2;                                   /*!< the ENET DMA desciptors 2 */
    uint32_t DES3;                                   /*!< the ENET DMA desciptors 3 */
    uint32_t buffer_address;                         /*!< store the buffer address */
    uint32_t bkp_info;                               /*!< backup infomation */
} enet_descriptors_struct;

/* structure for ENET DMA enhanced desciptors */
typedef struct {
    uint32_t ETDES0;                                 /*!< the ENET DMA enhanced desciptors 0 */
    uint32_t ETDES1;                                 /*!< the ENET DMA enhanced desciptors 1 */
    uint32_t ETDES2;                                 /*!< the ENET DMA enhanced desciptors 2 */
    uint32_t ETDES3;                                 /*!< the ENET DMA enhanced desciptors 3 */
    uint32_t DES0;                                   /*!< the ENET DMA desciptors 0 */
    uint32_t DES1;                                   /*!< the ENET DMA desciptors 1 */
    uint32_t DES2;                                   /*!< the ENET DMA desciptors 2 */
    uint32_t DES3;                                   /*!< the ENET DMA desciptors 3 */
    uint32_t buffer_address;
    uint32_t reversed;
} enet_tbs_enhanced_descriptors_struct;

/* dma direction select */
typedef enum {
    ENET_DMA_TX      = ENET_DMA_DEBUG_STATUS0_TPS0,  /*!< DMA transmit direction */
    ENET_DMA_RX      = ENET_DMA_DEBUG_STATUS0_RPS0   /*!< DMA receive direction */
} enet_dmadirection_enum;

/* mtl receive queue debug related stste select */
typedef enum {
    RXQ_FILL_LEVEL_STATE          = ENET_MTL_RXQ0_DEBUG_RXQSTS,                  /*!< MTL Rx queue fill-level status */
    RXQ_READ_CONTROLLER_STATE     = ENET_MTL_RXQ0_DEBUG_RRCSTS,                  /*!< MTL Rx queue read controller state */
    RXQ_WRITE_CONTROLLER_STATE    = ENET_MTL_RXQ0_DEBUG_RWCSTS                   /*!< MTL Rx queue write controller active status */
} enet_mtl_rxq_state_enum;

/* mtl transmit queue debug related stste select */
typedef enum {
    TXQ_FIFO_FULL_STATE           = ENET_MTL_TXQ0_DEBUG_TXSTSFSTS,               /*!< MTL Tx status FIFO full status */
    TXQ_NOT_EMPTY_STATE           = ENET_MTL_TXQ0_DEBUG_TXQSTS,                  /*!< MTL Tx queue not empty status */
    TXQ_WRITE_CONTROLLER_STATE    = ENET_MTL_TXQ0_DEBUG_TWCSTS,                  /*!< MTL Tx queue write controller status */
    TXQ_READ_CONTROLLER_STATE     = ENET_MTL_TXQ0_DEBUG_TRCSTS,                  /*!< MTL Tx queue read controller status */
    TXQ_IN_PAUSE_STATE            = ENET_MTL_TXQ0_DEBUG_TXQPAUSED                /*!< transmit queue in pause */
} enet_mtl_txq_state_enum;


/* register group value get */

typedef enum {
    ALL_MAC_REG                     = 0U,                                            /*!< MAC register group */
    ALL_MTL_REG                     = 190U,                                          /*!< MTL register group */
    ALL_MTL_Q0_REG                  = 224U,                                          /*!< MTL queue 0 register group */
    ALL_MTL_Q1_REG                  = 234U,                                          /*!< MTL queue 1 register group */
    ALL_DMA_REG                     = 248U,                                          /*!< DMA register group */
    ALL_DMA_CH0_REG                 = 254U,                                          /*!< DMA channel 0 register group */
    ALL_DMA_CH1_REG                 = 273U,                                          /*!< DMA channel 1 register group */
} enet_registers_type_enum;

typedef enum {
    ENET_CKNT_END_TO_END_0                            = MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(0),      /*!< type of end-to-end transparent clock node type for timestamp */
    ENET_CKNT_ORDINARY_BOUNDARY_SLAVE                 = MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(0)\
            | ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA,                                               /*!< type of ordinary or boundary slave clock node type for timestamp */
    ENET_CKNT_ORDINARY_BOUNDARY_MASTER                = MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(0) \
            | ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA \
            | ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA,                                               /*!< type of ordinary or boundary master clock node type for timestamp */
    ENET_CKNT_END_TO_END_PEER_DELAY                   = MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(1),      /*!< type of End-to-End Transparent with support for peer delay clock node type for timestamp */
    ENET_CKNT_ORDINARY_BOUNDARY_SLAVE_PEER_TO_PEER    = MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(1)\
            | ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA,                                               /*!< type of Ordinary or Boundary Slave with support for peer delay mechanism or Peer to Peer Transpare clock node type for timestamp */
    ENET_CKNT_ORDINARY_BOUNDARY_MASTER_PEER_DELAY     = MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(1) \
            | ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA \
            | ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA,                                                /*!< type of Ordinary or BoundaryMaster with support for peer delay clock node type for timestamp */
    ENET_CKNT_END_TO_END              = MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(2),                       /*!< type of end-to-end transparent clock node type for timestamp */
    ENET_CKNT_PEER_TO_PEER            = MAC_TIMESTAMP_CONTROL_SNAPTYPSEL(3),                       /*!< type of peer-to-peer transparent clock node type for timestamp */
    ENET_PTP_SYSTIME_INIT             = ENET_MAC_TIMESTAMP_CONTROL_TSINIT,                         /*!< timestamp initialize */
    ENET_PTP_SYSTIME_UPDATE           = ENET_MAC_TIMESTAMP_CONTROL_TSUPDT,                         /*!< timestamp update */
    ENET_PTP_ADDEND_UPDATE            = ENET_MAC_TIMESTAMP_CONTROL_TSADDREG,                       /*!< addend register update */
    ENET_PTP_FINEMODE                 = (int32_t)(ENET_MAC_TIMESTAMP_CONTROL_TSCFUPDT | BIT(31)),  /*!< the system timestamp uses the fine method for updating */
    ENET_PTP_COARSEMODE               = ENET_MAC_TIMESTAMP_CONTROL_TSCFUPDT,                       /*!< the system timestamp uses the coarse method for updating */
    ENET_SUBSECOND_DIGITAL_ROLLOVER   = (int32_t)(ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR | BIT(31)), /*!< digital rollover mode */
    ENET_SUBSECOND_BINARY_ROLLOVER    = ENET_MAC_TIMESTAMP_CONTROL_TSCTRLSSR,                      /*!< binary rollover mode */
    ENET_SNOOPING_PTP_VERSION_2       = (int32_t)(ENET_MAC_TIMESTAMP_CONTROL_TSVER2ENA | BIT(31)), /*!< version 2 */
    ENET_SNOOPING_PTP_VERSION_1       = ENET_MAC_TIMESTAMP_CONTROL_TSVER2ENA,                      /*!< version 1 */
    ENET_EVENT_TYPE_MESSAGES_SNAPSHOT = (int32_t)(ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA | BIT(31)), /*!< only event type messages are taken snapshot */
    ENET_ALL_TYPE_MESSAGES_SNAPSHOT   = (ENET_MAC_TIMESTAMP_CONTROL_TSEVNTENA | BIT(30)),          /*!< all type messages are taken snapshot except announce, management and signaling message */
    ENET_MASTER_NODE_MESSAGE_SNAPSHOT = (int32_t)(ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA | BIT(31)), /*!< snapshot is only take for master node message */
    ENET_SLAVE_NODE_MESSAGE_SNAPSHOT  = ENET_MAC_TIMESTAMP_CONTROL_TSMSTRENA,                      /*!< snapshot is only taken for slave node message */
} enet_ptp_function_enum;

/* structure of PTP system time */
typedef struct {
    uint32_t secondHi;                                                              /*!< The 16 leastmost significant bits of the 48 bits second of system time */
    uint32_t second;                                                                /*!< The 32 least significant bits of the 48 bits second of system time */
    uint32_t subsecond;                                                             /*!< subsecond of system time */
} enet_ptp_systime_struct;

/* ENET remote wake-up frame register (MAC_RWK_Packet_Filter) length */
#define ENET_WAKEUP_PACKET_REGISTER_LENGTH                8U                        /*!< remote wake-up frame register (MAC_RWK_Packet_Filter) length */

/* MAC_PMT_CONTROL_STATUS register value */
#define GET_MAC_PMT_CONTROL_RWKPTR(regval)       GET_BITS((uint32_t)(regval),24,28)             /*!< get value of MAC_PMT_CONTROL_STATUS_RWKPTR bit field */
#define MAC_PMT_CONTROL_RWKFILTRST               ENET_MAC_PMT_CONTROL_STATUS_RWKFILTRST         /*!< wakeup frame filter register poniter reset */
#define MAC_PMT_STATUS_RWKPRCVD                  ENET_MAC_PMT_CONTROL_STATUS_RWKPRCVD           /*!< wakeup frame received */
#define MAC_PMT_STATUS_MGKPRCVD                  ENET_MAC_PMT_CONTROL_STATUS_MGKPRCVD           /*!< magic packet received */
#define MAC_PMT_POWER_DOWN                       ENET_MAC_PMT_CONTROL_STATUS_PWRDWN             /*!< power down mode */
#define MAC_PMT_MAGIC_PACKET_FRAME               ENET_MAC_PMT_CONTROL_STATUS_MGKPKTEN           /*!< enable a wakeup event due to magic packet reception */
#define MAC_PMT_WAKE_UP_FRAME                    ENET_MAC_PMT_CONTROL_STATUS_RWKPKTEN           /*!< enable a wakeup event due to wakeup frame reception */
#define MAC_PMT_WAKE_UP_FRAME_FORWARD            ENET_MAC_PMT_CONTROL_STATUS_RWKPFE             /*!< enable remote wakeup frame forwarding */
#define MAC_PMT_GLOBAL_UNICAST                   ENET_MAC_PMT_CONTROL_STATUS_GLBLUCAST          /*!< any received unicast frame passed filter is considered to be a wakeup frame */

/* MAC_LPI_Control_Status register value */
#define ENET_LPI_TXCLK_STOP_ENABLE                ENET_MAC_LPI_CONTROL_STATUS_LPITCSE           /*!< LPI Tx clock stop is enabled */
#define ENET_LPI_TXCLK_STOP_DISABLE               ((uint32_t)0x00000000U)                       /*!< LPI Tx clock stop is disabled */
#define ENET_LPI_TXCLK_STOP                       ENET_LPI_TXCLK_STOP_ENABLE                    /*!< LPI Tx clock stop is enabled */
#define ENET_LPI_TIMER_ENABLE                     ENET_MAC_LPI_CONTROL_STATUS_LPIATE            /*!< LPI timer is enabled */
#define ENET_LPI_TIMER_DISABLE                    ((uint32_t)0x00000000U)                       /*!< LPI timer is disabled */
#define ENET_LPI_TIMER                            ENET_LPI_TIMER_ENABLE                         /*!< LPI timer is enabled */
#define ENET_LPI_TXAUTOMATE_ENABLE                ENET_MAC_LPI_CONTROL_STATUS_LPITXA            /*!< LPI Tx automate is enabled */
#define ENET_LPI_TXAUTOMATE_DISABLE               ((uint32_t)0x00000000U)                       /*!< LPI Tx automate is disabled */
#define ENET_LPI_TXAUTOMATE                       ENET_LPI_TXAUTOMATE_ENABLE                    /*!< LPI Tx automate is enabled */
#define ENET_LPI_PHYLINK_UP                       ENET_MAC_LPI_CONTROL_STATUS_PLS               /*!< link is okay (UP) */
#define ENET_LPI_PHYLINK_DOWN                     ((uint32_t)0x00000000U)                       /*!< link is down */
#define ENET_LPI_ENABLE                           ENET_MAC_LPI_CONTROL_STATUS_LPIEN             /*!< it instructs the MAC transmitter to enter the LPI state */
#define ENET_LPI_DISABLE                          ((uint32_t)0x00000000U)                       /*!< it instructs the MAC to exit the LPI state and resume normal transmission */
#define ENET_LPI_TRANSMIT_AUTO_ENTRY              (ENET_MAC_LPI_CONTROL_STATUS_LPIEN|ENET_LPI_TXAUTOMATE_ENABLE)          /*!< the MAC enters the LPI mode only after all outstanding packetsand pending packets have been transmitted */
#define ENET_LPI_TRANSMIT_AUTO_ENTRY_WITH_TIMER   (ENET_MAC_LPI_CONTROL_STATUS_LPIATE | ENET_MAC_LPI_CONTROL_STATUS_LPIEN|ENET_LPI_TXAUTOMATE_ENABLE)      /*!< the MAC transmitter enters LPI state only when the complete MAC TX data path is IDLE for a period indicated by the MAC_LPI_Entry_Timer register */

#define ENET_LPI_RX_STATE             ENET_MAC_LPI_CONTROL_STATUS_RLPIST                            /*!< receive LPI state */
#define ENET_LPI_TX_STATE             ENET_MAC_LPI_CONTROL_STATUS_TLPIST                            /*!< transmit LPI state */
#define ENET_LPI_RX_EXIT              ENET_MAC_LPI_CONTROL_STATUS_RLPIEX                            /*!< receive LPI exit */
#define ENET_LPI_RX_ENTRY             ENET_MAC_LPI_CONTROL_STATUS_RLPIEN                            /*!< receive LPI entry */
#define ENET_LPI_TX_EXIT              ENET_MAC_LPI_CONTROL_STATUS_TLPIEX                            /*!< transmit LPI exit */
#define ENET_LPI_TX_ENTRY             ENET_MAC_LPI_CONTROL_STATUS_TLPIEN                            /*!< transmit LPI entry */

/* MAC_VLAN_TAG_DATA register value */
#define ENET_VLANTAGCOMPARISON_INNER              ENET_MAC_VLAN_TAG_DATA_ERIVLT                  /*!< enable inner VLAN tag comparison */
#define ENET_VLANTAGCOMPARISON_OUTER              ((uint32_t)0x00000000U)                        /*!< enable outer VLAN tag comparison */
#define ENET_SVLANTAGMATCH_ENABLE                 ENET_MAC_VLAN_TAG_DATA_ERSVLM                  /*!< enable S-VLAN match for received frames */
#define ENET_SVLANTAGMATCH_DISABLE                ((uint32_t)0x00000000U)                        /*!< disable S-VLAN match for received frames */
#define ENET_VLANTYPECOMPARISON_ENABLE            ((uint32_t)0x00000000U)                        /*!< enable VLAN type comparison */
#define ENET_VLANTYPECOMPARISON_DISABLE           ENET_MAC_VLAN_TAG_DATA_DOVLTC                  /*!< disable VLAN type comparison */
#define ENET_VLANTAGCOMPARISON_12BIT              ENET_MAC_VLAN_TAG_DATA_ETV                     /*!< only low 12 bits of the VLAN tag are used for comparison */
#define ENET_VLANTAGCOMPARISON_16BIT              ((uint32_t)0x00000000U)                        /*!< all 16 bits of the VLAN tag are used for comparison */
#define ENET_VLANTAGCOMPARISON_ENABLE             ENET_MAC_VLAN_TAG_DATA_VEN                     /*!< VLAN tag enable */
#define ENET_VLANTAGCOMPARISON_DISABLE            ((uint32_t)0x00000000U)                        /*!< VLAN tag disable */



/* MAC_VLAN_INCL register value */
#define MAC_VLAN_INCL_VLT(regval)                        (BITS(0,15) & ((uint32_t)(regval) << 0))
#define MAC_VLAN_INCL_VLC(regval)                        (BITS(16,17) & ((uint32_t)(regval) << 16))
#define ENET_VLANTAG_INSERT_CHANNEL_BASED_ENABNLE        ENET_MAC_VLAN_INCL_CBTI                            /*!< outer VLAN tag is inserted for every packets transmitted by the MAC.*/
#define ENET_VLANTAG_INSERT_CHANNEL_BASED_DISABNLE       ((uint32_t)0x00000000U)                            /*!< outer VLAN operation is based on the setting of VLTI, VLP, VLC and VLT fields of this register*/
#define ENET_VLANTAG_FROM_DES                            ENET_MAC_VLAN_INCL_VLTI                            /*!< VLAN Tag Input is enabled */
#define ENET_VLANTAG_FROM_REG                            ((uint32_t)0x00000000U)                            /*!< VLAN Tag Input is disabled */
#define ENET_VLANTAG_INSERT_REPLACE_SVLAN                ENET_MAC_VLAN_INCL_CSVL                            /*!< C-VLAN type (0x8100) is inserted or replaced */
#define ENET_VLANTAG_INSERT_REPLACE_CVLAN                ((uint32_t)0x00000000U)                            /*!< S-VLAN type (0x88A8) is inserted or replaced */
#define ENET_VLANTAG_PRIORITY_ENABLE                     ENET_MAC_VLAN_INCL_VLP                             /*!< VLAN Priority Control is enabled */
#define ENET_VLANTAG_PRIORITY_DISABLE                    ((uint32_t)0x00000000U)                            /*!< VLAN Priority Control is disabled */
#define ENET_VLANTAG_NO_OPERATIOM                        MAC_VLAN_INCL_VLC(0)                               /*!< No VLAN tag deletion, insertion, or replacement */
#define ENET_VLANTAG_DELETION                            MAC_VLAN_INCL_VLC(1)                               /*!< VLAN tag deletion */
#define ENET_VLANTAG_INSERTATION                         MAC_VLAN_INCL_VLC(2)                               /*!< VLAN tag insertion */
#define ENET_VLANTAG_REPLACEMENT                         MAC_VLAN_INCL_VLC(3)                               /*!< VLAN tag replacement */

/* MAC_INNER_VLAN_INCL register value */
#define MAC_INNER_VLAN_TAG_DATA_VID(regval)              (BITS(0,15) & ((uint32_t)(regval) << 0))           /*!< VLAN tag ID */

#define MAC_INNER_VLAN_INCL_VLC(regval)                  (BITS(16,17) & ((uint32_t)(regval) << 16))
#define ENET_INNER_VLANTAG_FROM_DES                       ENET_MAC_INNER_VLAN_INCL_VLTI                     /*!< Inner VLAN Tag Input is enabled */
#define ENET_INNER_VLANTAG_FROM_REG                      ((uint32_t)0x00000000U)                            /*!< Inner VLAN Tag Input is disabled */
#define ENET_INNER_VLANTAG_INSERT_REPLACE_SVLAN           ENET_MAC_INNER_VLAN_INCL_CSVL                     /*!< Inner C-VLAN type (0x8100) is inserted or replaced */
#define ENET_INNER_VLANTAG_INSERT_REPLACE_CVLAN          ((uint32_t)0x00000000U)                            /*!< Inner S-VLAN type (0x88A8) is inserted or replaced */
#define ENET_INNER_VLANTAG_PRIORITY_ENABLE                ENET_MAC_INNER_VLAN_INCL_VLP                      /*!< Inner VLAN Priority Control is enabled */
#define ENET_INNER_VLANTAG_PRIORITY_DISABLE              ((uint32_t)0x00000000U)                            /*!< Inner VLAN Priority Control is disabled */
#define ENET_INNER_VLANTAG_NO_OPERATIOM                   MAC_INNER_VLAN_INCL_VLC(0)                        /*!< No Inner VLAN tag deletion, insertion, or replacement */
#define ENET_INNER_VLANTAG_DELETION                       MAC_INNER_VLAN_INCL_VLC(1)                        /*!< Inner VLAN tag deletion */
#define ENET_INNER_VLANTAG_INSERTATION                    MAC_INNER_VLAN_INCL_VLC(2)                        /*!< Inner VLAN tag insertion */
#define ENET_INNER_VLANTAG_REPLACEMENT                    MAC_INNER_VLAN_INCL_VLC(3)                        /*!< Inner VLAN tag replacement */

/* MAC_CONFIGURATION register value */
#define MAC_CONFIGURATION_FES(regval)                     (BIT(14) & ((uint32_t)(regval) << 14))            /*!< write value to MAC_CONFIGURATION_FES bit field */
#define MAC_CONFIGURATION_DM(regval)                      (BIT(13) & ((uint32_t)(regval) << 13))            /*!< write value to MAC_CONFIGURATION_FDM bit field */

/* MTL_RXQ_OPERATION_MODE register value */
#define MTL_RXQ_OPERATION_MODE_RSF(regval)                      (BIT(5) & ((uint32_t)(regval) << 5))        /*!< write value to MTL_TXQ_OPERATION_MODE_RSF bit field */


/* MTL_TXQ_OPERATION_MODE register value */
#define MTL_TXQ_OPERATION_MODE_TXQEN(regval)      (BITS(2,3) & ((uint32_t)(regval) << 2U))
#define MTL_TXQ_OPERATION_MODE_TSF(regval)        (BIT(1) & ((uint32_t)(regval) << 1))                      /*!< write value to MTL_TXQ_OPERATION_MODE_TSF bit field */


#define MAC_RXQ_CTRL0_RXQ0EN(regval)              (BITS(0,1) & ((uint32_t)(regval) << 0U))                  /*!< write value to MAC_RXQ_CTRL0_RXQ0EN bit field */
#define MAC_RXQ_CTRL0_RXQ1EN(regval)              (BITS(2,3) & ((uint32_t)(regval) << 2U))                  /*!< write value to MAC_RXQ_CTRL0_RXQ1EN bit field */
#define MAC_RXQ_CTRL2_PSRQ0(regval)               (BITS(0,7) & ((uint32_t)(regval) << 0U))                  /*!< write value to MAC_RXQ_CTRL2_PSRQ0 bit field */
#define MAC_RXQ_CTRL2_PSRQ1(regval)               (BITS(8,15) & ((uint32_t)(regval) << 8U))                 /*!< write value to MAC_RXQ_CTRL2_PSRQ1 bit field */

/* DMA_DEBUG_STATUS0 register value */
#define ENET_RX_STATE_STOPPED                     ((uint32_t)0x00000000)                        /*!< reset or stop rx command issued */
#define ENET_RX_STATE_FETCHING                    BIT(8)                                        /*!< fetching the Rx descriptor */
#define ENET_RX_STATE_WAITING                     (BIT(8)|BIT(9))                               /*!< waiting for receive packet */
#define ENET_RX_STATE_SUSPENDED                   BIT(10)                                       /*!< Rx descriptor unavailable */
#define ENET_RX_STATE_CLOSING                     (BIT(8)|BIT(10))                              /*!< closing receive descriptor */
#define ENET_RX_STATE_WRITING                     (BIT(9)|BIT(10))                              /*!< writing timestamp */
#define ENET_RX_STATE_QUEUING                     (BIT(8)|BIT(9)|BIT(10))                       /*!< transferring the receive packet data from recevie buffer to host memory */

#define ENET_TX_STATE_STOPPED                     ((uint32_t)0x00000000)                        /*!< reset or stop Tx Command issued  */
#define ENET_TX_STATE_FETCHING                    BIT(12)                                       /*!< fetching the Tx descriptor */
#define ENET_TX_STATE_WAITING                     BIT(13)                                       /*!< waiting for status */
#define ENET_TX_STATE_READING                     (BIT(12)|BIT(13))                             /*!< reading the data from host memory buffer and queuing it to transmit buffer */
#define ENET_TX_STATE_WRITING                     BIT(14)                                       /*!< writing timestamp */
#define ENET_TX_STATE_SUSPENDED                   (BIT(13)|BIT(14))                             /*!< Tx descriptor unavailabe or transmit buffer underflow */
#define ENET_TX_STATE_CLOSING                     (BIT(12)|BIT(13)|BIT(14))                     /*!< closing Tx descriptor */

/* ENET_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS register value */
#define MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_WRRDN           BIT(16)                             /*!< read write control */

/* ENET register mask value */
#define ENET_MMC_PRESET_MASK                      (~(ENET_MMC_CONTROL_CNTPRST | ENET_MMC_CONTROL_CNTPRSTLVL ))    /*!< ENET_MMC_CONTROL preset mask */
/* DMA_SYSBUS_MODE register value */
#define DMA_SYSBUS_MODE_AAL(regval)               (BIT(12) & ((uint32_t)(regval) << 12))                          /*!< write value to DMA_SYSBUS_MODE_AAL bit field */

/* mtl receive parser count related register value */
#define GET_PARSER_OVERFLOW_FLAG(regval)            (BIT(31) & ((uint32_t)(regval))) >> 31U    /*!< get receive parser overflow flag */
#define GET_PARSER_COUNT(regval)                    GET_BITS((uint32_t)(regval), 0U, 30U)      /*!< get receive parser count */

/* dma_mfbocnt register value */
#define GET_DMA_CH_MISS_FRAME_CNT_MSFC(regval)               GET_BITS((regval),0,10)           /*!< get value of ENET_DMA_CH(#i)_MISS_FRAME_CNT_MSFC bit field */

/* dma tx descriptor tdes2 register value */
#define TDES2_B1L(regval)                        (BITS(0,13) & ((uint32_t)(regval) << 0))      /*!< write value to ENET DMA TDES2 B1L bit field */

#define TDES2_B2L(regval)                        (BITS(16,29) & ((uint32_t)(regval) << 29))    /*!< write value to ENET DMA TDES2 B2L bit field */
/* dma tx descriptor tdes3 register value */
#define TDES3_CC(regval)                        (BITS(4,7) & ((uint32_t)(regval) << 4))        /*!< write value to ENET DMA TDES3 CC bit field */
#define GET_TDES3_COCNT(regval)                   GET_BITS((regval),4,7)                       /*!< get value of ENET DMA TDES3 CC bit field */

#define TDES3_CIC(regval)                        (BITS(16,17) & ((uint32_t)(regval) << 16))    /*!< write value to ENET DMA TDES3 CIC bit field */
#define ENET_CHECKSUM_DISABLE                     TDES3_CIC(0)                                 /*!< checksum insertion disabled */
#define ENET_CHECKSUM_IPV4HEADER                  TDES3_CIC(1)                                 /*!< only IP header checksum calculation and insertion are enabled */
#define ENET_CHECKSUM_TCPUDPICMP_SEGMENT          TDES3_CIC(2)                                 /*!< TCP/UDP/ICMP checksum insertion calculated but pseudo-header */
#define ENET_CHECKSUM_TCPUDPICMP_FULL             TDES3_CIC(3)                                 /*!< TCP/UDP/ICMP checksum insertion fully calculated */

#define TDES3_SAIC(regval)                        (BITS(23,25) & ((uint32_t)(regval) << 23))   /*!< write value to ENET DMA TDES3 SAIC bit field */
#define ENET_NO_SA_INCLUDE                        TDES3_SAIC(0)                                /*!< do not include the source address */
#define ENET_MAC0_SA_INCLUDE_INSERT               TDES3_SAIC(1)                                /*!< include or insert the source MAC Address 0 */
#define ENET_MAC0_SA_REPLACE                      TDES3_SAIC(2)                                /*!< replace the source MAC Address 0 */
#define ENET_MAC1_SA_INCLUDE_INSERT               TDES3_SAIC(5)                                /*!< include or insert the source MAC Address 1 */
#define ENET_MAC1_SA_REPLACE                      TDES3_SAIC(6)                                /*!< replace the source MAC Address 1 */

#define TDES3_CPC(regval)                        (BITS(26,27) & ((uint32_t)(regval) << 26))    /*!< write value to ENET DMA TDES3 CPC bit field */
#define ENET_CRC_PAD_INSERT                 TDES3_CPC(0)                                       /*!< CRC and pad insertion */
#define ENET_CRC_INSERT                     TDES3_CPC(1)                                       /*!< CRC insertion */
#define ENET_CRC_INSERT_DISABLE             TDES3_CPC(2)                                       /*!< disable CRC Insertion */
#define ENET_CRC_REPLACE                    TDES3_CPC(3)                                       /*!< CRC replacement */

/* dma rx descriptor rdes3 register value */
#define RDES3_PL(regval)                        (BITS(0,14) & ((uint32_t)(regval) << 0))       /*!< write value to ENET DMA RDES0 FRML bit field */
#define GET_RDES3_PL(regval)                    GET_BITS((regval),0,14)                        /*!< get value of ENET DMA RDES0 FRML bit field */


#define ETH_DMATXDESC_SIZE                        ((uint32_t)0x00000018U)                       /*!< TxDMA descriptor size */
#define ETH_DMARXDESC_SIZE                        ((uint32_t)0x00000018U)                       /*!< RxDMA descriptor size */
#define ENET_ENHANCED_DMATXDESC_SIZE              ((uint32_t)0x00000028U)                       /*!< enhanced TxDMA descriptor size */

/* ENET frame size */
#define ENET_MAX_FRAME_SIZE                       1528U                                         /*!< header + frame_extra + payload + CRC */

/* ENET delay timeout */
#define ENET_DELAY_TO                             ((uint32_t)0x00FFFFFFU)                       /*!< ENET delay timeout */
#define ENET_RESET_TO                             ((uint32_t)0x000004FFU)                       /*!< ENET reset timeout */
#define PHY_DELAY_TO                              ((uint32_t)0x000FFFFFU)                       /*!< ENET delay timeout */

/* ENET MAC version */
#define MAC_VERSION                               ((uint32_t)0x00001053U)                       /*!< ENET delay timeout */

/* the reset value of ENET registers */
#define ENET_RESET_VALUE                          ((uint32_t)0x00000000U)                       /*!< the reset value of register */

/* ENNT operation timeout */
#define ENET_OPERATION_TIMEROUT                   ((uint32_t)0x00FFFFFFU)                       /*!< ENET software operation delay timeout */
#define ENET_SWR_DELAY_TO                         ((uint32_t)0x00000FFFU)                       /*!< ENET software reset delay timeout */

/* parameter check definitions */
#ifdef FW_DEBUG_ERR_REPORT

/* check ENET forward options */
#define ENET_FORWARD_OPTION_BITS                               (ENET_AUTO_PADCRC_STRIP_ENABLE | ENET_TYPEPACKET_CRC_STRIP_ENABLE | ENET_RXQ0_FORWARD_ERRFRAMES_ENABLE | \
                                                               ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES_ENABLE | ENET_RXQ1_FORWARD_ERRFRAMES_ENABLE | \
                                                               ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES_ENABLE )
#define NOT_ENET_FORWARD_OPTION(para)                          ((uint32_t)0x0U != ((para)&(~ENET_FORWARD_OPTION_BITS)))

/* check ENET dma bus options */
#define ENET_DMABUS_OPTION_BITS                               (ENET_ADDRESS_ALIGN_ENABLE | ENET_FIXED_BURST_ENABLE | ENET_MIXED_BURST_ENABLE)
#define NOT_ENET_DMABUS_OPTION(para)                          ((uint32_t)0x0U != ((para)&(~ENET_DMABUS_OPTION_BITS)))

/* check ENET dma channel maxburst options */
#define ENET_DMACH_MAXBURST_OPTION_BITS                        (BITS(16,22) | (ENET_DMA_CH_CONTROL_PBLx8<<7) | (BITS(16,21)>>8))
#define NOT_ENET_DMACH_MAXBURST_OPTION(para)                    ((uint32_t)0x0U != ((para)&(~ENET_DMACH_MAXBURST_OPTION_BITS)))

/* check ENET dma arbitration options */
#define NOT_ENET_DMA_ARBITRATION_OPTION(para)                 (((para) != ENET_ARBITRATION_RXTX_1_1) && ((para) != ENET_ARBITRATION_RXTX_2_1) && \
                                                              ((para) != ENET_ARBITRATION_RXTX_3_1) && ((para) != ENET_ARBITRATION_RXTX_4_1) && ((para) != ENET_ARBITRATION_RXTX_5_1) && \
                                                              ((para) != ENET_ARBITRATION_RXTX_6_1) && ((para) != ENET_ARBITRATION_RXTX_7_1) && ((para) != ENET_ARBITRATION_RXTX_8_1) && \
                                                              ((para) != ENET_ARBITRATION_TXRX_1_1) && ((para) != ENET_ARBITRATION_TXRX_2_1) && ((para) != ENET_ARBITRATION_TXRX_3_1) && \
                                                              ((para) != ENET_ARBITRATION_TXRX_4_1) && ((para) != ENET_ARBITRATION_TXRX_5_1) && ((para) != ENET_ARBITRATION_TXRX_6_1) && \
                                                              ((para) != ENET_ARBITRATION_TXRX_7_1) && ((para) != ENET_ARBITRATION_TXRX_8_1))

/* check ENET Tx store-forward options */
#define ENET_TXSTORE_OPTION_BITS                              (ENET_TX_MODE_STOREFORWARD | (BITS(4,6)))
#define NOT_ENET_TXSTORE_OPTION(para)                         ((uint32_t)0x0U != ((para)&(~ENET_TXSTORE_OPTION_BITS)))

/* check ENET Rx store-forward options */
#define ENET_RXSTORE_OPTION_BITS                              (ENET_RX_MODE_STOREFORWARD | (BITS(0,1)))
#define NOT_ENET_RXSTORE_OPTION(para)                         ((uint32_t)0x0U != ((para)&(~ENET_RXSTORE_OPTION_BITS)))

/* check ENET vlan configure options */
#define ENET_VLAN_CONFIG_OPTION_BITS                          (ENET_RXINVLAN_ENABLE | BITS(28,29) | ENET_INVLANCOMPARISON_ENABLE | \
                                                              ENET_DOUBLEVLAN_ENABLE | ENET_VLANHASHMATCH_ENABLE | ENET_RXOUTVLAN_ENABLE | \
                                                              BITS(21,22) | ENET_VLANTYPECHECK_DISABLE | ENET_SVLANHASHMATCH_ENABLE | ENET_SVLAN_ENABLE | \
                                                              ENET_VLANINVERSEMATCH_ENABLE | ENET_VLANTAGHASHCOMPARISON_12BIT)
#define NOT_ENET_VLAN_CONFIG_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_VLAN_CONFIG_OPTION_BITS)))

/* check ENET vlan comparision options */
#define ENET_VLAN_COMPARISON_OPTION_BITS                      (ENET_VLANTAGCOMPARISON_INNER | ENET_SVLANTAGMATCH_ENABLE | ENET_VLANTYPECOMPARISON_DISABLE | \
                                                              ENET_VLANTAGCOMPARISON_12BIT | ENET_VLANTAGCOMPARISON_ENABLE | BITS(0,15))
#define NOT_ENET_VLAN_COMPARISON_OPTION(para)                 ((uint32_t)0x0U != ((para)&(~ENET_VLAN_COMPARISON_OPTION_BITS)))

/* check ENET vlan insert options */
/* check ENET vlan insert options */
#define ENET_VLAN_INSERT_OPTION_BITS                          BITS(0, 20)
#define NOT_ENET_VLAN_INSERT_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_VLAN_INSERT_OPTION_BITS)))

/* check ENET inner vlan insert options */
#define ENET_INNERVLAN_INSERT_OPTION_BITS                     BITS(0, 20)
#define NOT_ENET_INNERVLAN_INSERT_OPTION(para)                ((uint32_t)0x0U != ((para)&(~ENET_INNERVLAN_INSERT_OPTION_BITS)))

/* check ENET flowctl options */
#define ENET_FLOWCTL_OPTION_BITS                              (ENET_ZERO_QUANTA_PAUSE_DISABLE | BITS(4,6) | ENET_MAC0_AND_UNIQUE_ADDRESS_PAUSEDETECT)
#define NOT_ENET_FLOWCTL_OPTION(para)                         ((uint32_t)0x0U != ((para)&(~ENET_FLOWCTL_OPTION_BITS)))

/* check ENET filter options */
#define ENET_FILTER_OPTION_BITS                              (ENET_SRC_FILTER_NORMAL_ENABLE | ENET_SRC_FILTER_INVERSE_ENABLE | ENET_DEST_FILTER_INVERSE_ENABLE | \
                                                              ENET_MULTICAST_FILTER_HASH_OR_PERFECT | ENET_MULTICAST_FILTER_HASH | ENET_MULTICAST_FILTER_NONE | \
                                                              ENET_MULTICAST_FILTER_PASS | ENET_DROP_NONTCPUDP_ENABLE | ENET_VLAN_FILTER_ENABLE | ENET_L3L4_FILTER_ENABLE | \
                                                              ENET_UNICAST_FILTER_EITHER | ENET_UNICAST_FILTER_HASH | BITS(6,7))
#define NOT_ENET_FILTER_OPTION(para)                         ((uint32_t)0x0U != ((para)&(~ENET_FILTER_OPTION_BITS)))

/* check ENET halfduplex options */
#define ENET_HALFDUPLEX_OPTION_BITS                          (ENET_CARRIERSENSE_DISABLE | ENET_RECEIVEOWN_DISABLE | ENET_RETRYTRANSMISSION_DISABLE | \
                                                             BITS(5,6) | ENET_DEFERRALCHECK_ENABLE)
#define NOT_ENET_HALFDUPLEX_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_HALFDUPLEX_OPTION_BITS)))

/* check ENET fullduplex options */
#define ENET_FULLDUPLEX_OPTION_BITS                          (ENET_FULLDUPLEX_CARRIERSENSE_ENABLE | BITS(2,3))
#define NOT_ENET_FULLDUPLEX_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_FULLDUPLEX_OPTION_BITS)))

/* check ENET packet size options */
#define ENET_PACKETSIZE_OPTION_BITS                          (ENET_2KMAX_PACKET_ENABLE | ENET_JUMBO_PACKET_DISABLE | ENET_GIANT_PACKET_LIMIT_ENABLE)
#define NOT_ENET_PACKETSIZE_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_PACKETSIZE_OPTION_BITS)))

/* check ENET timer options */
#define ENET_TIMER_OPTION_BITS                               (ENET_WATCHDOG_DISABLE | ENET_JABBER_DISABLE)
#define NOT_ENET_TIMER_OPTION(para)                          ((uint32_t)0x0U != ((para)&(~ENET_TIMER_OPTION_BITS)))

/* check ENET mac control options */
#define ENET_MACCONTROL_OPTION_BITS                          (ENET_ARP_OFFLOAD_ENABLE | BITS(28,29))
#define NOT_ENET_MACCONTROL_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_MACCONTROL_OPTION_BITS)))

/* check ENET inter frame gap options */
#define ENET_INTERFRAMEGAP_OPTION_BITS                       (BITS(24,26))
#define NOT_ENET_INTERFRAMEGAP_OPTION(para)                  ((uint32_t)0x0U != ((para)&(~ENET_INTERFRAMEGAP_OPTION_BITS)))

/* check ENET ecc control options */
#define ENET_ECCCONTROL_OPTION_BITS                          (ENET_MTL_TXFIFO_ECC_ENABLE | ENET_MTL_RXFIFO_ECC_ENABLE | ENET_MTL_EST_ECC_ENABLE | \
                                                             ENET_MTL_RXP_ECC_ENABLE | ENET_MTL_EXX_ERR_ADDR_STATUS_OVERRIDE_ENABLE)
#define NOT_ENET_ECCCONTROL_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_ECCCONTROL_OPTION_BITS)))

/* check ENET dpp control options */
#define ENET_DPPCONTROL_OPTION_BITS                          (ENET_DATA_PATH_PARITY_PROTECTION_ENABLE | ENET_DPP_ODD_PARITY_ENABLE | ENET_DPP_PARITY_ON_SLAVE_INTERFACE_ENABLE | \
                                                             ENET_DPP_IPETID_ENABLE | ENET_DPP_IPETRD_ENABLE | ENET_DPP_IPEMTF_ENABLE | \
                                                             ENET_DPP_IPEMTS_ENABLE | ENET_DPP_IPERID_ENABLE | ENET_DPP_IPEMTBU_ENABLE | \
                                                             ENET_DPP_IPEMTFC_ENABLE | ENET_DPP_IPEMRWC_ENABLE)
#define NOT_ENET_DPPCONTROL_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_DPPCONTROL_OPTION_BITS)))

/* check ENET fsm control options */
#define ENET_FSMCONTROL_OPTION_BITS                          (ENET_PTP_DOMAIN_LARGE_MODE | ENET_APP_DOMAIN_LARGE_MODE | ENET_CSR_DOMAIN_LARGE_MODE | \
                                                             ENET_RX_DOMAIN_LARGE_MODE | ENET_TX_DOMAIN_LARGE_MODE | ENET_PTP_FSM_PARITY_ERROR_INJECTION_ENABLE | \
                                                             ENET_APP_FSM_PARITY_ERROR_INJECTION_ENABLE | ENET_CSR_FSM_ONEHOTPROTECTION_ERROR_INJECTION_ENABLE | ENET_RX_FSM_PARITY_ERROR_INJECTION_ENABLE | \
                                                             ENET_TX_FSM_PARITY_ERROR_INJECTION_ENABLE | ENET_PTP_FSM_TIMEOUT_ERROR_INJECTION_ENABLE | ENET_APP_FSM_TIMEOUT_ERROR_INJECTION_ENABLE | \
                                                             ENET_CSR_FSM_TIMEOUT_ERROR_INJECTION_ENABLE | ENET_RX_FSM_TIMEOUT_ERROR_INJECTION_ENABLE | ENET_TX_FSM_TIMEOUT_ERROR_INJECTION_ENABLE | \
                                                             ENET_FSM_PARITY_FEATURE_ENABLE | ENET_FSM_TIMEOUT_FEATURE_ENABLE)
#define NOT_ENET_FSMCONTROL_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_FSMCONTROL_OPTION_BITS)))

/* check ENET est control options */
#define ENET_ESTCONTROL_OPTION_BITS                          (ENET_MTL_EST_CONTROL_EEST | ENET_MTL_EST_CONTROL_SSWL | ENET_MTL_EST_CONTROL_QHLBF | \
                                                             ENET_MTL_EST_CONTROL_DDBF | ENET_MTL_EST_CONTROL_DFBS | ENET_MTL_EST_CONTROL_LCSE | \
                                                             ENET_MTL_EST_CONTROL_TILS | ENET_MTL_EST_CONTROL_CTOV | ENET_MTL_EST_CONTROL_PTOV)
#define NOT_ENET_ESTCONTROL_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_ESTCONTROL_OPTION_BITS)))

/* check ENET fpe control options */
#define ENET_FPECONTROL_OPTION_BITS                          (ENET_GCL_LEVEL_BASED_HOLD_TRANSITION_ENABLE | (ENET_MTL_FPE_CTRL_STS_PEC << 4U) | (ENET_MTL_FPE_CTRL_STS_AFSZ << 4U))
#define NOT_ENET_FPECONTROL_OPTION(para)                     ((uint32_t)0x0U != ((para)&(~ENET_FPECONTROL_OPTION_BITS)))

/* check ENET buffer size value */
#define BUFSIZE_HIGH_VAL                                      ENET_RXBUF_SIZE
#define NOT_ENET_BUFSIZE(bufsize)                             (BUFSIZE_HIGH_VAL < (bufsize))

/* check ENET IP checksum configuration */
#define NOT_ENET_CHECKSUM(checksum)                           (((checksum) != ENET_CHECKSUM_DISABLE) && ((checksum) != ENET_CHECKSUM_IPV4HEADER) && \
                                                              ((checksum) != ENET_CHECKSUM_TCPUDPICMP_SEGMENT) && ((checksum) != ENET_CHECKSUM_TCPUDPICMP_FULL))

/* check ENET transmit source address control */
#define NOT_ENET_TXSRCADDR_CONTROL(control)                   (((control) != ENET_NO_SA_INCLUDE) && ((control) != ENET_MAC0_SA_INCLUDE_INSERT) && \
                                                              ((control) != ENET_MAC0_SA_REPLACE) && ((control) != ENET_MAC1_SA_INCLUDE_INSERT)&& \
                                                              ((control) != ENET_MAC1_SA_REPLACE))

/* check ENET transmit crc / pad control */
#define NOT_ENET_TXCRCPAD_CONTROL(control)                    (((control) != ENET_CRC_PAD_INSERT) && ((control) != ENET_CRC_INSERT) && \
                                                              ((control) != ENET_CRC_INSERT_DISABLE) && ((control) != ENET_CRC_REPLACE))

/* check ENET extend packet gap value */
#define EXT_PACKET_GAP_HIGH_VAL                              ((uint32_t)2144U)
#define EXT_PACKET_GAP_LOW_VAL                               ((uint32_t)104U)
#define NOT_EXT_PACKET_GAP_VALUE(packet_gap)                 ((EXT_PACKET_GAP_HIGH_VAL < (packet_gap)) || (EXT_PACKET_GAP_LOW_VAL > (packet_gap)))

/* check ENET giant packet size value */
#define GIANT_PACKET_SIZE_HIGH_VAL                           ((uint32_t)0x3FFFU)
#define NOT_GIANT_PACKET_SIZE_VALUE(size)                    (GIANT_PACKET_SIZE_HIGH_VAL < (size))

/* check ENET jabber programmable timeout */
#define NOT_ENET_JABBER_TIMEOUT(val)                         (((val) != ENET_JABBER_TIMEOUT_2KB) && ((val) != ENET_JABBER_TIMEOUT_3KB) && \
                                                             ((val) != ENET_JABBER_TIMEOUT_4KB) && ((val) != ENET_JABBER_TIMEOUT_5KB) && \
                                                             ((val) != ENET_JABBER_TIMEOUT_6KB) && ((val) != ENET_JABBER_TIMEOUT_7KB) && \
                                                             ((val) != ENET_JABBER_TIMEOUT_8KB) && ((val) != ENET_JABBER_TIMEOUT_9KB) && \
                                                             ((val) != ENET_JABBER_TIMEOUT_10KB) && ((val) != ENET_JABBER_TIMEOUT_11KB) && \
                                                             ((val) != ENET_JABBER_TIMEOUT_12KB) && ((val) != ENET_JABBER_TIMEOUT_13KB) && \
                                                             ((val) != ENET_JABBER_TIMEOUT_14KB) && ((val) != ENET_JABBER_TIMEOUT_15KB) && \
                                                             ((val) != ENET_JABBER_TIMEOUT_16KB))

/* check ENET watchdog programmable timeout */
#define NOT_ENET_WATCHDOG_TIMEOUT(val)                       (((val) != ENET_WATCHDOG_TIMEOUT_2KB) && ((val) != ENET_WATCHDOG_TIMEOUT_3KB) && \
                                                             ((val) != ENET_WATCHDOG_TIMEOUT_4KB) && ((val) != ENET_WATCHDOG_TIMEOUT_5KB) && \
                                                             ((val) != ENET_WATCHDOG_TIMEOUT_6KB) && ((val) != ENET_WATCHDOG_TIMEOUT_7KB) && \
                                                             ((val) != ENET_WATCHDOG_TIMEOUT_8KB) && ((val) != ENET_WATCHDOG_TIMEOUT_9KB) && \
                                                             ((val) != ENET_WATCHDOG_TIMEOUT_10KB) && ((val) != ENET_WATCHDOG_TIMEOUT_11KB) && \
                                                             ((val) != ENET_WATCHDOG_TIMEOUT_12KB) && ((val) != ENET_WATCHDOG_TIMEOUT_13KB) && \
                                                             ((val) != ENET_WATCHDOG_TIMEOUT_14KB) && ((val) != ENET_WATCHDOG_TIMEOUT_15KB) && \
                                                             ((val) != ENET_WATCHDOG_TIMEOUT_16KB))

/* check ENET mac register number */
#define MAC_REG_NUM_HIGH_VAL                                  ((uint32_t)190U)
#define NOT_ENET_MAC_REG_NUM(num)                             (MAC_REG_NUM_HIGH_VAL < (num))

/* check ENET mtl register number */
#define MTL_REG_NUM_HIGH_VAL                                  ((uint32_t)34U)
#define NOT_ENET_MTL_REG_NUM(num)                            (MTL_REG_NUM_HIGH_VAL < (num))

/* check ENET mtl queue 0 register number */
#define MTL_Q0_REG_NUM_HIGH_VAL                               ((uint32_t)10U)
#define NOT_ENET_MTL_Q0_REG_NUM(num)                          (MTL_Q0_REG_NUM_HIGH_VAL < (num))

/* check ENET mtl queue 1 register number */
#define MTL_Q1_REG_NUM_HIGH_VAL                               ((uint32_t)14U)
#define NOT_ENET_MTL_Q1_REG_NUM(num)                          (MTL_Q1_REG_NUM_HIGH_VAL < (num))

/* check ENET dma register number */
#define DMA_REG_NUM_HIGH_VAL                                  ((uint32_t)6U)
#define NOT_ENET_DMA_REG_NUM(num)                             (DMA_REG_NUM_HIGH_VAL < (num))

/* check ENET dma channel 0 register number */
#define DMA_CH0_REG_NUM_HIGH_VAL                              ((uint32_t)19U)
#define NOT_ENET_DMA_CH0_REG_NUM(num)                         (DMA_CH0_REG_NUM_HIGH_VAL < (num))

/* check ENET dma channel 1 register number */
#define DMA_CH1_REG_NUM_HIGH_VAL                              ((uint32_t)19U)
#define NOT_ENET_DMA_CH1_REG_NUM(num)                         (DMA_CH1_REG_NUM_HIGH_VAL < (num))

/* check ENET mac address mask */
#define NOT_ENET_ADDR_MASK(addr_mask)                        ((uint32_t)0x0U != ((addr_mask)&(~ENET_MAC_ADDRESS1_HIGH_MBC)))

/* check ENET mac filter type */
#define NOT_ENET_MAC_FILTER_TYPE(filter_type)                (((filter_type) != ENET_ADDRESS_FILTER_SA) && ((filter_type) != ENET_ADDRESS_FILTER_DA))

/* check ENET forward feature */
#define NOT_ENET_FORWARD_FEATURE(feature)                    (((feature) != ENET_AUTO_PADCRC_DROP) && ((feature) != ENET_TYPEFRAME_CRC_DROP) && \
                                                             ((feature) != ENET_RXQ0_FORWARD_ERRFRAMES) && ((feature) != ENET_RXQ0_FORWARD_UNDERSZ_GOODFRAMES) && \
                                                             ((feature) != ENET_RXQ1_FORWARD_ERRFRAMES) && ((feature) != ENET_RXQ1_FORWARD_UNDERSZ_GOODFRAMES))

/* check ENET filter feature */
#define ENET_FILTER_BITS                                     (ENET_L3L4_FILTER | ENET_VLAN_FILTER | ENET_SRC_FILTER | ENET_SRC_FILTER_INVERSE | \
                                                              ENET_BROADCASTFRAMES_FILTER | ENET_DEST_FILTER_INVERSE | ENET_MULTICAST_FILTER_PASS | \
                                                              ENET_MULTICAST_FILTER_HASH_MODE | ENET_UNICAST_FILTER_HASH_MODE | ENET_FILTER_MODE_EITHER)
#define NOT_ENET_FILTER_FEATURE(feature)                     ((uint32_t)0x0U != ((feature)&(~ENET_FILTER_BITS)) || ((uint32_t)0U == (feature)))

/* check the type of filter fail packet */
#define NOT_ENET_FILTER_FAIL_PACKET_TYPE(type)               (((type) != MAC_UNICAST_ADDRESS_FLITER_FAIL) && ((type) != MAC_MULTICAST_ADDRESS_FLITER_FAIL) && \
                                                             ((type) != MAC_VLAN_TAG_FLITER_FAIL))

/* check normal packets queue related configuration */
#define NOT_ENET_PACKET_QUEUE_CFG(config)                    (((config) != MAC_RXQ_MCBC_PRIORITY_ENABLE) && ((config) != MAC_RXQ_MCBC_PRIORITY_DISABLE) && \
                                                             ((config) != MAC_RXQ_PTPOE_AS_GENERIC_VLAN) && ((config) != MAC_RXQ_PTPOE_TO_PTPQ) && \
                                                             ((config) != MAC_RXQ_PTPOE_TO_PSRQ) && ((config) != MAC_AV_TAG_PACKET_QUEUE_ENABLE) && \
                                                             ((config) != MAC_AV_TAG_PACKET_QUEUE_DISABLE) && ((config) != MAC_RXQ_MCBC_PRIORITY_OVER_ENABLE) && \
                                                             ((config) != MAC_RXQ_MCBC_PRIORITY_OVER_DISABLE) && ((config) != MAC_RXQ_TYPE_BASED_ENABLE) && \
                                                             ((config) != MAC_RXQ_TYPE_BASED_DISABLE))

/* check normal packets queue related configuration */
#define NOT_ENET_FSM_TIMEOUT_VALUE(val)                      (((val) != ENET_FSM_TIMEOUT_DISABLE) && ((val) != ENET_FSM_TIMEOUT_1US) && \
                                                             ((val) != ENET_FSM_TIMEOUT_4MS) && ((val) != ENET_FSM_TIMEOUT_16MS) && \
                                                             ((val) != ENET_FSM_TIMEOUT_64MS) && ((val) != ENET_FSM_TIMEOUT_256MS) && \
                                                             ((val) != ENET_FSM_TIMEOUT_1SEC) && ((val) != ENET_FSM_TIMEOUT_4SEC) && \
                                                             ((val) != ENET_FSM_TIMEOUT_16SEC) && ((val) != ENET_FSM_TIMEOUT_32SEC) && \
                                                             ((val) != ENET_FSM_TIMEOUT_64SEC))

/* check ENET pauseframe detect */
#define NOT_ENET_PAUSEFRAME_DETECT(detect)                   (((detect) != ENET_MAC0_AND_UNIQUE_ADDRESS_PAUSEDETECT) && ((detect) != ENET_UNIQUE_PAUSEDETECT))

/* check ENET pause threshold */
#define NOT_ENET_PAUSE_THRESHOLD(pause_threshold)            (((pause_threshold) != ENET_PAUSETIME_MINUS4) && ((pause_threshold) != ENET_PAUSETIME_MINUS28) && \
                                                             ((pause_threshold) != ENET_PAUSETIME_MINUS36) && ((pause_threshold) != ENET_PAUSETIME_MINUS144) && \
                                                             ((pause_threshold) != ENET_PAUSETIME_MINUS256) && ((pause_threshold) != ENET_PAUSETIME_MINUS256_2))

/* check ENET deactive threshold */
#define NOT_ENET_DEACTIVE_THRESHOLD(deactive)                (((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_1K) && ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_1_5K) && \
                                                             ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_2K) && ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_2_5K) && \
                                                             ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_3K) && ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_3_5K) && \
                                                             ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_4K) && ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_4_5K) && \
                                                             ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_5K) && ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_5_5K) && \
                                                             ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_6K) && ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_6_5K) && \
                                                             ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_7K) && ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_7_5K) && \
                                                             ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_8K) && ((deactive) != ENET_DEACTIVE_THRESHOLD_FULL_MINUS_8_5K))

/* check ENET active threshold */
#define NOT_ENET_ACTIVE_THRESHOLD(active)                    (((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_1K) && ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_1_5K) && \
                                                             ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_2K) && ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_2_5K) && \
                                                             ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_3K) && ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_3_5K) && \
                                                             ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_4K) && ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_4_5K) && \
                                                             ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_5K) && ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_5_5K) && \
                                                             ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_6K) && ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_6_5K) && \
                                                             ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_7K) && ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_7_5K) && \
                                                             ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_8K) && ((active) != ENET_ACTIVE_THRESHOLD_FULL_MINUS_8_5K))

/* check ENET flow control feature */
#define NOT_ENET_FLOWCONTROL_FEATURE(feature)                (((feature) != ENET_ZERO_QUANTA_PAUSE) && ((feature) != ENET_TX_FLOWCONTROL) && \
                                                             ((feature) != ENET_RX_FLOWCONTROL) && ((feature) != ENET_BACK_PRESSURE))

/* check ENET frame preemption feature */
#define NOT_ENET_FRAMEPREEMPTION_FEATURE(feature)            (((feature) != ENET_SEND_RESPOND_FRAME) && ((feature) != ENET_SEND_VERIFY_FRAME) && \
                                                             ((feature) != ENET_AUTOGENERATE_RESPOND_MPACKET) && \
                                                             ((feature) != ENET_TX_FRAME_PREEMPTION))

#define NOT_ENET_FRAMEPREEMPTION_FEATURE1(feature)            (((feature) != ENET_AUTOGENERATE_RESPOND_MPACKET) && \
                                                             ((feature) != ENET_TX_FRAME_PREEMPTION))

/* check ENET dma slot interval value */
#define DMA_SLOT_INTERVAL_HIGH_VAL                           ((uint32_t)0xFFFU)
#define NOT_DMA_SLOT_INTERVAL_VALUE(slot_interval)           (DMA_SLOT_INTERVAL_HIGH_VAL < (slot_interval))

/* check dma slot function */
#define ENET_DMA_SLOT_FUNCTION_BITS                          (ENET_DMA_ADVANCE_SLOT_CHECK | ENET_DMA_SLOT_COMPARISON)
#define NOT_DMA_SLOT_FUNCTION(function)                      ((0U != ((function)&(~ENET_DMA_SLOT_FUNCTION_BITS))) || ((uint32_t)0U == (function)))

/* check watchdog timer count units */
#define NOT_ENET_WATCHDOG_TIMER_COUNT_UNIT(count_uint)       (((count_uint) != ENET_RX_INT_WATCHDOG_TIMER_COUNT_256) && ((count_uint) != ENET_RX_INT_WATCHDOG_TIMER_COUNT_512) && \
                                                             ((count_uint) != ENET_RX_INT_WATCHDOG_TIMER_COUNT_1024) && ((count_uint) != ENET_RX_INT_WATCHDOG_TIMER_COUNT_2048))

/* check the value of watchdog timer count */
#define DMA_ALTER_RXBUF_SIZE_HIGH_VAL                        ((uint32_t)0x3F8U)
#define NOT_DMA_ALTER_RXBUF_SIZE(size)                       (DMA_ALTER_RXBUF_SIZE_HIGH_VAL < (size))

/* check MAC_TMRQ_Regs selection */
#define NOT_ENET_MAC_TMRQ_REG_NUM(reg_num)                   (((reg_num) != ENET_INDIR_ACCESS_MAC_TMRQ_REG0) && ((reg_num) != ENET_INDIR_ACCESS_MAC_TMRQ_REG1) && \
                                                             ((reg_num) != ENET_INDIR_ACCESS_MAC_TMRQ_REG2) && ((reg_num) != ENET_INDIR_ACCESS_MAC_TMRQ_REG3) && \
                                                             ((reg_num) != ENET_INDIR_ACCESS_MAC_TMRQ_REG4) && ((reg_num) != ENET_INDIR_ACCESS_MAC_TMRQ_REG5) && \
                                                             ((reg_num) != ENET_INDIR_ACCESS_MAC_TMRQ_REG6) && ((reg_num) != ENET_INDIR_ACCESS_MAC_TMRQ_REG7))
/* check the packet type selection */
#define PACKET_TYPE_LOW_VAL                                  ((uint32_t)0x600U)
#define NOT_PACKET_TYPE(type)                                (PACKET_TYPE_LOW_VAL > (type))

/* check the tbs mode */
#define NOT_ENET_TBS_MODE(mode)                              (((mode) != ENET_TBS_NORMAL_ABSOLUTE_MODE) && ((mode) != ENET_TBS_EST_OFFSET_MODE))

/* check the launch expiry offset */
#define LAUNCH_EXPIRY_OFFSET_HIGH_VAL                        ((uint32_t)0xFFFFFFU)
#define NOT_LAUNCH_EXPIRY_OFFSET(offset)                     (LAUNCH_EXPIRY_OFFSET_HIGH_VAL < (offset))

/* check the launch expiry offset */
#define LAUNCH_EXPIRY_GSN_OFFSET_HIGH_VAL                     ((uint32_t)0x7U)
#define NOT_LAUNCH_EXPIRY_GSN_OFFSET(gsn_offset)              (LAUNCH_EXPIRY_GSN_OFFSET_HIGH_VAL < (gsn_offset))

/* check the fetch offset */
#define FETCH_OFFSET_HIGH_VAL                                 ((uint32_t)0xFFFFFFU)
#define NOT_FETCH_OFFSET(offset)                              (LAUNCH_EXPIRY_OFFSET_HIGH_VAL < (offset))

/* check the fetch gsn offset */
#define FETCH_GSN_OFFSET_HIGH_VAL                             ((uint32_t)0x7U)
#define NOT_FETCH_GSN_OFFSET(gsn_offset)                      (FETCH_GSN_OFFSET_HIGH_VAL < (gsn_offset))

/* check ENET mtl transmit queue ets configuration */

/* check ENET mtl transmit queue ets configuration */
#define NOT_ENET_TXQ1_ETS_CFG(cfg)                          (((cfg) != ENET_CBS_1SLOT) && ((cfg) != ENET_CBS_2SLOT) && \
                                                            ((cfg) != ENET_CBS_4SLOT) && ((cfg) != ENET_CBS_8SLOT) && \
                                                            ((cfg) != ENET_CBS_16SLOT) && ((cfg) != ENET_TXQ1_CREDIT_CONTROL_ENABLE) && \
                                                            ((cfg) != ENET_TXQ1_CREDIT_CONTROL_DISABLE) && ((cfg) != ENET_TXQ1_AV_ALGO_ENABLE) && \
                                                            ((cfg) != ENET_TXQ1_AV_ALGO_DISABLE))

/* check the fetch gsn offset */
#define OVERHEAD_BYTES_HIGH_VAL                               ((uint32_t)0x3FU)
#define NOT_OVERHEAD_BYTES_VALUE(val)                         (OVERHEAD_BYTES_HIGH_VAL < (val))

/* check the filter register selection */
#define NOT_ENET_MAC_VLAN_TAG_FILTER(filter)                  (((filter) != MAC_VLAN_TAG_FILTER0) && ((filter) != MAC_VLAN_TAG_FILTER1) && \
                                                              ((filter) != MAC_VLAN_TAG_FILTER2) && ((filter) != MAC_VLAN_TAG_FILTER3))

/* check ENET pmt feature */
#define NOT_ENET_VLAN_FILTER_FEATURE(feature)                 (((feature) != ENET_VLANTAGCOMPARISON_INNER) && ((feature) != ENET_SVLANTAGMATCH_ENABLE) && \
                                                              ((feature) != ENET_VLANTYPECOMPARISON_DISABLE) && ((feature) != ENET_VLANTAGCOMPARISON_12BIT) && \
                                                              ((feature) != ENET_VLANTAGCOMPARISON_ENABLE))

/* check ENET transmit algorithm type */
#define NOT_ENET_TX_ALGO_TYPE(SchedAlgo)                     (((SchedAlgo) != STRICT_PRIORITY_TX) && ((SchedAlgo) != WEIGHTED_ROUND_ROBIN))

/* check ENET mtl transmit queue weight */
#define MTL_TXQ_WEIGHT_HIGH_VAL                                ((uint8_t)0x64U)
#define NOT_ENET_MTL_TXQ_WEIGHT(weight)                        (MTL_TXQ_WEIGHT_HIGH_VAL < (weight))


/* check ENET mtl receive queue weight */
#define MTL_RXQ_WEIGHT_HIGH_VAL                                ((uint8_t)0x7U)
#define NOT_ENET_MTL_RXQ_WEIGHT(weight)                        (MTL_RXQ_WEIGHT_HIGH_VAL < (weight))

/* check ENET idleSlope credit */
#define IDLE_SLOPE_CREDIT_HIGH_VAL                             ((uint32_t)0x1000U)
#define NOT_ENET_IDLE_SLOPE_CREDIT(credit)                     (IDLE_SLOPE_CREDIT_HIGH_VAL < (credit))

/* check ENET sendSlope credit */
#define SEND_SLOPE_CREDIT_HIGH_VAL                             ((uint32_t)0x1000U)
#define NOT_ENET_SEND_SLOPE_CREDIT(credit)                     (SEND_SLOPE_CREDIT_HIGH_VAL < (credit))

/* check ENET hiSlope credit */
#define HIGH_SLOPE_CREDIT_HIGH_VAL                             ((uint32_t)0x08000000U)
#define NOT_ENET_HIGH_SLOPE_CREDIT(credit)                     (HIGH_SLOPE_CREDIT_HIGH_VAL < (credit))

/* check ENET loSlope credit */
#define LOW_SLOPE_CREDIT_HIGH_VAL                              ((uint32_t)0x18000000U)
#define NOT_ENET_LOW_SLOPE_CREDIT(credit)                      (LOW_SLOPE_CREDIT_HIGH_VAL < (credit))

/* check ENET mtl queue size */
#define NOT_ENET_TXQ_SIZE(size)                              (((size) != ENET_TXQ_SIZE_256BYTES) && ((size) != ENET_TXQ_SIZE_512BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_768BYTES) && ((size) != ENET_TXQ_SIZE_1024BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_1280BYTES) && ((size) != ENET_TXQ_SIZE_1536BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_1792BYTES) && ((size) != ENET_TXQ_SIZE_2048BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_2304BYTES) && ((size) != ENET_TXQ_SIZE_2560BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_2816BYTES) && ((size) != ENET_TXQ_SIZE_3072BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_3328BYTES) && ((size) != ENET_TXQ_SIZE_3584BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_3840BYTES) && ((size) != ENET_TXQ_SIZE_4096BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_4352BYTES) && ((size) != ENET_TXQ_SIZE_4608BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_4864BYTES) && ((size) != ENET_TXQ_SIZE_5120BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_5376BYTES) && ((size) != ENET_TXQ_SIZE_5632BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_5888BYTES) && ((size) != ENET_TXQ_SIZE_6144BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_6400BYTES) && ((size) != ENET_TXQ_SIZE_6656BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_6912BYTES) && ((size) != ENET_TXQ_SIZE_7168BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_7424BYTES) && ((size) != ENET_TXQ_SIZE_7680BYTES) && \
                                                               ((size) != ENET_TXQ_SIZE_7936BYTES) && ((size) != ENET_TXQ_SIZE_8192BYTES))
                                                               
#define NOT_ENET_RXQ_SIZE(size)                              (((size) != ENET_RXQ_SIZE_256BYTES) && ((size) != ENET_RXQ_SIZE_512BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_768BYTES) && ((size) != ENET_RXQ_SIZE_1024BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_1280BYTES) && ((size) != ENET_RXQ_SIZE_1536BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_1792BYTES) && ((size) != ENET_RXQ_SIZE_2048BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_2304BYTES) && ((size) != ENET_RXQ_SIZE_2560BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_2816BYTES) && ((size) != ENET_RXQ_SIZE_3072BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_3328BYTES) && ((size) != ENET_RXQ_SIZE_3584BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_3840BYTES) && ((size) != ENET_RXQ_SIZE_4096BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_4352BYTES) && ((size) != ENET_RXQ_SIZE_4608BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_4864BYTES) && ((size) != ENET_RXQ_SIZE_5120BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_5376BYTES) && ((size) != ENET_RXQ_SIZE_5632BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_5888BYTES) && ((size) != ENET_RXQ_SIZE_6144BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_6400BYTES) && ((size) != ENET_RXQ_SIZE_6656BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_6912BYTES) && ((size) != ENET_RXQ_SIZE_7168BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_7424BYTES) && ((size) != ENET_RXQ_SIZE_7680BYTES) && \
                                                               ((size) != ENET_RXQ_SIZE_7936BYTES) && ((size) != ENET_RXQ_SIZE_8192BYTES))

/* check the TER value */
#define TER_REG_HIGH_VAL                                     ((uint32_t)0x7FFFFFFFU)
#define NOT_TER_REG_VAL(value)                               (TER_REG_HIGH_VAL < (value))
/* check ENET gcl length */
#define GCL_LENGTH_HIGH_VAL                                    ((uint32_t)127U)
#define NOT_ENET_GCL_LENGTH(length)                            (GCL_LENGTH_HIGH_VAL < (length))

/* check ENET Rx parser entry number */
#define ENTRY_NUMBER_HIGH_VAL                                  ((uint32_t)63U)
#define NOT_ENET_ENTRY_NUMBER(number)                          (ENTRY_NUMBER_HIGH_VAL < (number))

/* check the related configuration of L3_L4 filter */
#define NOT_ENET_L3_L4_FILTER_CFG(function)                    (((function) != ENET_L4_DEST_PORT_NORMAL_MATCH) && ((function) != ENET_L4_DEST_PORT_INVERSE_MATCH) && \
                                                               ((function) != ENET_L4_SRC_PORT_NORMAL_MATCH) && ((function) != ENET_L4_SRC_PORT_INVERSE_MATCH) && \
                                                               ((function) != ENET_L4_PROTOCOL_MATCH_UDP) && ((function) != ENET_L3_DEST_IPADDR_NORMAL_MATCH) && \
                                                               ((function) != ENET_L3_DEST_IPADDR_INVERSE_MATCH) && ((function) != ENET_L3_SRC_IPADDR_NORMAL_MATCH) && \
                                                               ((function) != ENET_L3_SRC_IPADDR_INVERSE_MATCH) && ((function) != ENET_L3_PROTOCOL_MATCH_IPV6))

/* check ENET descriptor flag get */
#define ENET_DESC_FLAG_GET_BITS                                (ENET_NORMAL_TDES3_WF_IHE | ENET_NORMAL_TDES3_WF_DB | ENET_NORMAL_TDES3_WF_UF | \
                                                               ENET_NORMAL_TDES3_WF_ED | ENET_NORMAL_TDES3_WF_EC | \
                                                               ENET_NORMAL_TDES3_WF_LC | ENET_NORMAL_TDES3_WF_NC | \
                                                               ENET_NORMAL_TDES3_WF_LOC | ENET_NORMAL_TDES3_WF_PCE | \
                                                               ENET_NORMAL_TDES3_WF_FF | ENET_NORMAL_TDES3_WF_JT | \
                                                               ENET_NORMAL_TDES3_WF_ES | ENET_NORMAL_TDES3_WF_TTSS | \
                                                               ENET_NORMAL_TDES3_WF_DE | ENET_NORMAL_TDES3_WF_FD | \
                                                               ENET_NORMAL_TDES3_WF_CTXT | ENET_NORMAL_TDES3_WF_LD | \
                                                               ENET_NORMAL_TDES3_WF_OWN | ENET_NORMAL_RDES3_WF_RWT | \
                                                               ENET_NORMAL_RDES3_WF_OE | ENET_NORMAL_RDES3_WF_RE | \
                                                               ENET_NORMAL_RDES3_WF_RS0V | ENET_NORMAL_RDES3_WF_RS1V | \
                                                               ENET_NORMAL_RDES3_WF_RS2V | ENET_NORMAL_RDES3_WF_CE | \
                                                               ENET_NORMAL_RDES3_WF_DE )
#define NOT_ENET_DESC_FLAG_GET(para)                          ((uint32_t)0x0U != ((para)&(~ENET_DESC_FLAG_GET_BITS)))

/* check ENET descriptor flag clear */
#define ENET_DESC_FLAG_SET_BITS                                (ENET_NORMAL_TDES3_RF_FD | ENET_NORMAL_TDES3_RF_LD | ENET_NORMAL_TDES3_RF_CTXT | \
                                                               ENET_NORMAL_TDES3_RF_OWN | ENET_NORMAL_RDES3_RF_BUF1V | ENET_NORMAL_RDES3_RF_BUF2V)
#define NOT_ENET_DESC_FLAG_SET(para)                          ((uint32_t)0x0U != ((para)&(~ENET_DESC_FLAG_SET_BITS)))

/* check ENET dma feature */
#define ENET_DMA_FEATURE_BITS                                  (ENET_FLUSH_RXFRAME | ENET_SECONDFRAME_OPT)
#define NOT_ENET_DMA_FEATURE(feature)                          (((uint32_t)0x0U != ((feature)&(~ENET_DMA_FEATURE_BITS))) || ((uint32_t)0U != (feature)))

/* check ENET pmt feature */
#define ENET_PMT_ENABLE_BITS                                   (MAC_PMT_POWER_DOWN | MAC_PMT_MAGIC_PACKET_FRAME | MAC_PMT_WAKE_UP_FRAME | \
                                                               MAC_PMT_WAKE_UP_FRAME_FORWARD | MAC_PMT_GLOBAL_UNICAST)
#define NOT_ENET_PMT_ENABLE_FEATURE(feature)                   (((uint32_t)0x0U != ((feature)&(~ENET_PMT_ENABLE_BITS))) || ((uint32_t)0U != (feature)))

#define ENET_PMT_DISABLE_BITS                                  (MAC_PMT_MAGIC_PACKET_FRAME | MAC_PMT_WAKE_UP_FRAME | \
                                                               MAC_PMT_GLOBAL_UNICAST)
#define NOT_ENET_PMT_DISABLE_FEATURE(feature)                  (((uint32_t)0x0U != ((feature)&(~ENET_PMT_DISABLE_BITS))) || ((uint32_t)0U != (feature)))

/* check ENET 1us tick */
#define US_TICK_HIGH_VAL                                       ((uint32_t)0xFFFU)
#define NOT_ENET_US_TICK(tick)                                 (US_TICK_HIGH_VAL < (tick))

/* check ENET lpi timer value */
#define LPI_LS_TIMER_HIGH_VAL                                  ((uint32_t)0x3FFU)
#define NOT_ENET_LPI_LS_TIMER_VALUE(val)                       (LPI_LS_TIMER_HIGH_VAL < (val))

#define LPI_TW_TIMER_HIGH_VAL                                  ((uint32_t)0xFFFFU)
#define NOT_ENET_LPI_TW_TIMER_VALUE(val)                       (LPI_TW_TIMER_HIGH_VAL < (val))

#define LPI_ENTRY_TIMER_HIGH_VAL                               ((uint32_t)0xFFFFFU)
#define NOT_ENET_LPI_ENTRY_TIMER_VALUE(val)                    (LPI_ENTRY_TIMER_HIGH_VAL < (val))

/* check ENET lpi feature */
#define NOT_ENET_LPI_FEATURE(feature)                          (((feature) != ENET_LPI_TXCLK_STOP) && ((feature) != ENET_LPI_TIMER) && \
                                                               ((feature) != ENET_LPI_TXAUTOMATE) && ((feature) != ENET_LPI_PHYLINK_UP) && \
                                                               ((feature) != ENET_LPI_ENABLE) && ((feature) != ENET_LPI_TRANSMIT_AUTO_ENTRY) && \
                                                               ((feature) != ENET_LPI_TRANSMIT_AUTO_ENTRY_WITH_TIMER))

/* check ENET lpi status */
#define NOT_ENET_LPI_STATUS(state)                             (((state) != ENET_LPI_RX_STATE) && ((state) != ENET_LPI_TX_STATE) && \
                                                               ((state) != ENET_LPI_RX_EXIT) && ((state) != ENET_LPI_RX_ENTRY) && \
                                                               ((state) != ENET_LPI_TX_EXIT) && ((state) != ENET_LPI_TX_ENTRY))

/* check ENET mmc feature */
#define ENET_MMC_FEATURE_BITS                                  (ENET_MMC_DROPPED_BROADCAST_UPDATE | ENET_MMC_COUNTER_STOP_ROLLOVER | ENET_MMC_RESET_ON_READ | \
                                                               ENET_MMC_COUNTERS_FREEZE)
#define NOT_ENET_MMC_FEATURE(feature)                          (((uint32_t)0x0U != ((feature)&(~ENET_MMC_FEATURE_BITS))) || (0U == (feature)))

/* check ENET ptp feature */
#define NOT_ENET_PTP_FEATURE(feature)                          (((0x00000000U != (0xEEFBC6BE & (feature)))) || (0U == (feature)))

/* check ENET ptp sign */
#define NOT_ENET_PTP_SIGN(sign)                                (((sign) != ENET_PTP_ADD_TO_TIME) && ((sign) != ENET_PTP_SUBSTRACT_FROM_TIME))

/* check ENET ptp nanosecond value */

#define NANOSECOND_HIGH_VAL                                    ((uint32_t)0x7FFFFFFFU)
#define NOT_ENET_NANOSECOND_VALUE(val)                         (NANOSECOND_HIGH_VAL < (val))

/* check ENET pps output frequece */
#define NOT_ENET_PPS_FREQ(freq)                                (((freq) != ENET_PPSOFC_1HZ) && ((freq) != ENET_PPSOFC_2HZ) && \
                                                               ((freq) != ENET_PPSOFC_4HZ) && ((freq) != ENET_PPSOFC_8HZ) && \
                                                               ((freq) != ENET_PPSOFC_16HZ) && ((freq) != ENET_PPSOFC_32HZ) && \
                                                               ((freq) != ENET_PPSOFC_64HZ) && ((freq) != ENET_PPSOFC_128HZ) && \
                                                               ((freq) != ENET_PPSOFC_256HZ) && ((freq) != ENET_PPSOFC_512HZ) && \
                                                               ((freq) != ENET_PPSOFC_1024HZ) && ((freq) != ENET_PPSOFC_2048HZ) && \
                                                               ((freq) != ENET_PPSOFC_4096HZ) && ((freq) != ENET_PPSOFC_8192HZ) && \
                                                               ((freq) != ENET_PPSOFC_16384HZ) && ((freq) != ENET_PPSOFC_32768HZ))

/* check ENET pps command */
#define NOT_ENET_PPS_COMMAND(command)                          (((command) != ENET_FLEXIBLE_PPS0_START_SINGLE_PULSE) && ((command) != ENET_FLEXIBLE_PPS0_START_PULSE_TRAIN) && \
                                                               ((command) != ENET_FLEXIBLE_PPS0_CANCEL_START) && ((command) != ENET_FLEXIBLE_PPS0_STOP_PULSE_TRAIN_AT_TIME) && \
                                                               ((command) != ENET_FLEXIBLE_PPS0_STOP_PULSE_TRAIN_NOW) && ((command) != ENET_FLEXIBLE_PPS0_CANCEL_STOP_PULSE_TRAIN) && \
                                                               ((command) != ENET_FLEXIBLE_PPS1_START_SINGLE_PULSE) && ((command) != ENET_FLEXIBLE_PPS1_START_PULSE_TRAIN) && \
                                                               ((command) != ENET_FLEXIBLE_PPS1_CANCEL_START) && ((command) != ENET_FLEXIBLE_PPS1_STOP_PULSE_TRAIN_AT_TIME) && \
                                                               ((command) != ENET_FLEXIBLE_PPS1_STOP_PULSE_TRAIN_NOW) && ((command) != ENET_FLEXIBLE_PPS1_CANCEL_STOP_PULSE_TRAIN) && \
                                                               ((command) != ENET_FLEXIBLE_PPS2_START_SINGLE_PULSE) && ((command) != ENET_FLEXIBLE_PPS2_START_PULSE_TRAIN) && \
                                                               ((command) != ENET_FLEXIBLE_PPS2_CANCEL_START) && ((command) != ENET_FLEXIBLE_PPS2_STOP_PULSE_TRAIN_AT_TIME) && \
                                                               ((command) != ENET_FLEXIBLE_PPS2_STOP_PULSE_TRAIN_NOW) && ((command) != ENET_FLEXIBLE_PPS2_CANCEL_STOP_PULSE_TRAIN) && \
                                                               ((command) != ENET_FLEXIBLE_PPS3_START_SINGLE_PULSE) && ((command) != ENET_FLEXIBLE_PPS3_START_PULSE_TRAIN) && \
                                                               ((command) != ENET_FLEXIBLE_PPS3_CANCEL_START) && ((command) != ENET_FLEXIBLE_PPS3_STOP_PULSE_TRAIN_AT_TIME) && \
                                                               ((command) != ENET_FLEXIBLE_PPS3_STOP_PULSE_TRAIN_NOW) && ((command) != ENET_FLEXIBLE_PPS3_CANCEL_STOP_PULSE_TRAIN))

/* check ENET mcgr mode */
#define ENET_MCGR_MODE_BITS                                    (ENET_MAC_PPS_CONTROL_PPSCTRL_PPSCMD | ENET_MAC_PPS_CONTROL_PPSCMD1 | ENET_MAC_PPS_CONTROL_PPSCMD2 | \
                                                               ENET_MAC_PPS_CONTROL_PPSCMD3 )
#define NOT_ENET_MCGR_MODE(para)                               ((uint32_t)0x0U != ((para)&(~ENET_MCGR_MODE_BITS)))

/* check ENET asym latency value */
#define ASYM_LATENCY_NANOSECOND_HIGH_VAL                       ((uint16_t)0xFFFU)
#define NOT_ASYM_LATENCY_NANOSECOND_VALUE(val)                 (ASYM_LATENCY_NANOSECOND_HIGH_VAL < (val))

/* check ENET ecc memory */
#define NOT_ENET_ECC_MEMORY(memory)                            (((memory) != ENET_MTL_ECC_SELECT_TX_MEM) && ((memory) != ENET_MTL_ECC_SELECT_RX_MEM) && \
                                                               ((memory) != ENET_MTL_ECC_SELECT_EST_MEM) && ((memory) != ENET_MTL_ECC_SELECT_RXP_MEM))

/* check the ecc error status related configuration */
#define NOT_ENET_ECC_ERR_STATUS_CFG(config)                    (((config) != ENET_MTL_ECC_ERR_STATUS_READ_ENABLE) && ((config) != ENET_MTL_UNCORRECTABLE_ERR_STATUS_CLEAR) && \
                                                               ((config) != ENET_MTL_CORRECTABLE_ERR_STATUS_CLEAR))

/* check the ecc error status related configuration */
#define NOT_ENET_ECC_ERR_ADDRESS(type)                         (((type) != ENET_MTL_UNCORRECTABLE_ERR_ADDRESS) && ((type) != ENET_MTL_CORRECTABLE_ERR_ADDRESS))

/* check the ecc error count related configuration */
#define NOT_ENET_ECC_ERR_COUNT(type)                           (((type) != ENET_MTL_UNCORRECTABLE_ERR_COUNT) && ((type) != ENET_MTL_CORRECTABLE_ERR_COUNT))
/* check the mtl error injection mode */
#define NOT_ENET_MTL_ERR_INJECTION_MODE(mode)                  (((mode) != ENET_ERR_INJTECTION_ON_ECC_PARITY) && ((mode) != ENET_ERR_INJTECTION_ON_DATA))

/* check the MTL error injection configuration */
#define NOT_ENET_MTL_ERR_INJECTION_CFG(config)                 (((config) != ENET_RXP_INSERT_ECC_ERR_1BIT) && ((config) != ENET_RXP_INSERT_ECC_ERR_2BIT) && \
                                                               ((config) != ENET_RXP_INSERT_ECC_ADDR_ERR_1BIT) && ((config) != ENET_RXP_INSERT_ECC_ADDR_ERR_2BIT))

#endif /* FW_DEBUG_ERR_REPORT */
/* global transmit and receive descriptors pointers */
extern enet_descriptors_struct  *dma_current_txdesc;
extern enet_descriptors_struct  *dma_current_rxdesc;
/* structure pointer of enhanced descriptor for TBS */
extern enet_tbs_enhanced_descriptors_struct  *dma_current_tbs_txdesc;

/* global transmit and receive descriptors pointers */
extern enet_descriptors_struct  *dma_current_txdesc1;
extern enet_descriptors_struct  *dma_current_rxdesc1;
/* structure pointer of enhanced descriptor for TBS */
extern enet_tbs_enhanced_descriptors_struct  *dma_current_tbs_txdesc1;

extern enet_descriptors_struct  txdesc_tab[ENET_TXBUF_NUM];                       /*!< ENET TxDMA descriptor */
extern enet_tbs_enhanced_descriptors_struct  tbs_txdesc_tab[ENET_TXBUF_NUM];      /*!< ENET TxDMA enhanced descriptor */
extern enet_descriptors_struct  rxdesc_tab[ENET_RXBUF_NUM];                       /*!< ENET RxDMA descriptor */
extern uint8_t rx_buff[ENET_RXBUF_NUM][ENET_RXBUF_SIZE];                          /*!< ENET receive buffer */
extern uint8_t tx_buff[ENET_TXBUF_NUM][ENET_TXBUF_SIZE];                          /*!< ENET transmit buffer */

extern enet_descriptors_struct  txdesc_tab1[ENET_TXBUF_NUM];                      /*!< ENET TxDMA descriptor */
extern enet_tbs_enhanced_descriptors_struct  tbs_txdesc_tab1[ENET_TXBUF_NUM];     /*!< ENET TxDMA enhanced descriptor */
extern enet_descriptors_struct  rxdesc_tab1[ENET_RXBUF_NUM];                      /*!< ENET RxDMA descriptor */
extern uint8_t rx_buff1[ENET_RXBUF_NUM][ENET_RXBUF_SIZE];                         /*!< ENET receive buffer */
extern uint8_t tx_buff1[ENET_TXBUF_NUM][ENET_TXBUF_SIZE];                         /*!< ENET transmit buffer */

/* function declarations */
/* main function */
/* deinitialize the ENET module */
void enet_deinit(void);
/* configure the parameters which are usually less cared for initialization */
void enet_initpara_config(enet_option_enum option, uint32_t para);
/* initialize ENET parameter structure with a default value */
void enet_struct_para_init(enet_struct_type_enum type, void *p_struct);
/* initialize ENET MAC module */
void enet_mac_init(enet_mac_config_struct *Config);
/* initialize ENET DMA module */
void enet_dma_init(enet_dmach_enum dmach, enet_dma_config_struct *Config);
/* initialize ENET MTL module */
void enet_mtl_init(enet_mtl_enum Instance, enet_mtl_config_struct *Config);
/* initialize ENET peripheral with generally concerned parameters and the less cared parameters */
ErrStatus enet_init(enet_mediamode_enum mediamode, enet_chksumconf_enum checksum, enet_frmrecept_enum recept);
/* reset all core internal registers located in CLK_TX and CLK_RX */
ErrStatus enet_software_reset(void);
/* check receive frame valid and return frame size */
uint32_t enet_rxframe_size_get(enet_dmach_enum dmach);
/* initialize the dma tx/rx descriptors's parameters in ring mode */
void enet_descriptors_ring_init(enet_dmach_enum dmach, enet_dmadirection_enum direction);

/* handle current received frame data to application buffer */
ErrStatus enet_frame_receive(enet_dmach_enum dmach, uint8_t *buffer, uint32_t bufsize);
/* handle current received frame but without data copy to application buffer */
#define ENET_NOCOPY_FRAME_RECEIVE(dmach)         enet_frame_receive(dmach, NULL, 0U)
/* handle application buffer data to transmit it */
ErrStatus enet_frame_transmit(enet_dmach_enum dmach, uint8_t *buffer, uint32_t length);
/* handle current transmit frame but without data copy from application buffer */
#define ENET_NOCOPY_FRAME_TRANSMIT(dmach, len)     enet_frame_transmit(dmach, NULL, (len))

ErrStatus enet_frame_transmit_tbs(enet_dmach_enum dmach, uint8_t *buffer, uint32_t length, uint32_t launch_time, uint32_t gsn_num);
/* configure the transmit IP frame checksum offload calculation and insertion */
void enet_transmit_checksum_config(enet_descriptors_struct *desc, uint32_t checksum);
/* configure MAC to add or replace the Source Address field in the Ethernet packet */
void enet_transmit_sourceaddr_insert_config(enet_descriptors_struct *desc, uint32_t control);
/* configure the CRC and pad insertion for Tx packet */
void enet_transmit_crc_pad_config(enet_descriptors_struct *desc, uint32_t control);
/* configure MAC address */
void enet_mac_address_set(enet_macaddress_enum mac_addr, uint8_t paddr[]);
/* get MAC address */
void enet_mac_address_get(enet_macaddress_enum mac_addr, uint8_t paddr[]);
/* configure ARP IP address */
void enet_arp_ip_address_set(uint8_t ipaddr[]);
/* get the ENET MAC/MSC/PTP/DMA status flag */
FlagStatus enet_flag_get(enet_flag_enum enet_flag);
/* clear the ENET DMA status flag */
void enet_flag_clear(enet_flag_clear_enum enet_flag);
/* enable ENET MAC/MSC/DMA interrupt */
void enet_interrupt_enable(enet_int_enum enet_int);
/* disable ENET MAC/MSC/DMA interrupt */
void enet_interrupt_disable(enet_int_enum enet_int);
/* get ENET MAC/MSC/DMA interrupt flag */
FlagStatus enet_interrupt_flag_get(enet_int_flag_enum int_flag);
/* clear ENET DMA interrupt flag */
void enet_interrupt_flag_clear(enet_int_flag_clear_enum int_flag_clear);

/* MAC function */
/* enable the Tx MAC */
void enet_tx_mac_enable(void);
/* disable the Tx MAC */
void enet_tx_mac_disable(void);
/* enable the Rx MAC */
void enet_rx_mac_enable(void);
/* disable the Rx MAC */
void enet_rx_mac_disable(void);
/* set the MAC extended configuration */
void enet_mac_extend_config(enet_extend_macconfig_enum func);
/* set the MAC extend Inter-Packet Gap */
void enet_mac_extend_gap_set(uint32_t packet_gap);
/* set the MAC giant packet size limit */
void enet_mac_giant_packetsize_set(uint32_t size);
/* set the MAC jabber programmable timeout */
void enet_mac_jabber_timeout_set(uint32_t val);
/* set the MAC watchdog programmable timeout */
void enet_mac_watchdog_timeout_set(uint32_t val);
/* check the mac version */
ErrStatus enet_mac_version_check(void);
/* put registers value into the application buffer */
void enet_registers_get(enet_registers_type_enum type, uint32_t *preg, uint32_t num);
/* set the mode and priority for Rx queue */
void enet_rxq_mode_set(enet_rxq_enum enet_rxq, enet_queopmode_enum queuemode, uint8_t priosel);
/* enable the MAC address filter */
void enet_address_filter_enable(enet_macaddress_enum mac_addr);
/* disable the MAC address filter */
void enet_address_filter_disable(enet_macaddress_enum mac_addr);
/* configure the MAC address filter */
void enet_address_filter_config(enet_macaddress_enum mac_addr, uint32_t addr_mask, uint32_t filter_type);
/* PHY interface configuration (configure SMI clock and reset PHY chip) */
ErrStatus enet_phy_config(void);
/* get PHY interface mode */
enet_modetype_enum enet_phy_interface_get(void);
/* write to/read from a PHY register */
ErrStatus enet_phy_write_read(enet_phyconfig_struct *ConfigInfo, enet_phydirection_enum direction, ControlStatus Clause45Enable);
/* enable the loopback function of phy chip */
ErrStatus enet_phyloopback_enable(void);
/* disable the loopback function of phy chip */
ErrStatus enet_phyloopback_disable(void);
/* enable ENET forward feature */
void enet_forward_feature_enable(uint32_t feature);
/* disable ENET forward feature */
void enet_forward_feature_disable(uint32_t feature);
/* enable ENET fliter feature */
void enet_fliter_feature_enable(uint32_t feature);
/* disable ENET fliter feature */
void enet_fliter_feature_disable(uint32_t feature);
/* set the filter fail packets queue */
void enet_fliterfail_queue_set(enet_rxq_enum enet_rxq, uint32_t type);
/* set the normal packets queue */
void enet_normal_frame_queue_set(enet_rxq_enum enet_rxq, enet_frame_type_enum type);
/* set the normal packets queue related configuration */
void enet_normal_frame_queue_config(uint32_t config);
/* set the the FSM and interface timeout values */
void enet_fsm_timeout_set(enet_fsmtimeout_enum type, uint32_t val);

/* flow control function */
/* start the Rx DMA */
void enet_rx_dma_start(enet_dmach_enum dmach);
/* start the Tx DMA */
void enet_tx_dma_start(enet_dmach_enum dmach);
/* generate the pause frame, ENET will send pause frame after enable transmit flow control */
ErrStatus enet_pauseframe_generate(void);
/* configure the pause frame detect type */
void enet_pauseframe_detect_config(uint32_t detect);
/* configure the pause frame parameters */
void enet_pauseframe_config(uint16_t pausetime, uint32_t pause_threshold);
/* configure the threshold of the flow control(deactive and active threshold) */
void enet_flowcontrol_threshold_config(enet_rxq_enum rxq, uint32_t deactive, uint32_t active);
/* enable ENET flow control feature */
void enet_flowcontrol_feature_enable(uint32_t feature);
/* disable ENET flow control feature */
void enet_flowcontrol_feature_disable(uint32_t feature);
/* config ENET frame preemption feature */
void enet_framepreemption_feature_enable(uint32_t feature);
/* disable ENET frame preemption feature */
void enet_framepreemption_feature_disable(uint32_t feature);

/* DMA function */
/* get the dma transmit/receive process state */
uint32_t enet_dmaprocess_state_get(enet_dmach_enum dmach, enet_dmadirection_enum direction);
/* start/stop the DMA transmission/reception */
void enet_dmaprocess_config(enet_dmach_enum dmach, enet_dmadirection_enum direction, ControlStatus status);
/* check and recover the Rx process */
void enet_rxprocess_check_recovery(enet_dmach_enum dmach);
/* get the transmit/receive address of current descriptor, or current buffer, or descriptor table */
uint32_t enet_dma_desc_address_get(enet_desc_reg_enum addr_get);
/* get the Tx or Rx descriptor information */
uint32_t enet_desc_information_get(enet_descriptors_struct *desc, enet_descstate_enum info_get);
/* get the number of missed frames during receiving */
void enet_missed_frame_counter_get(enet_dmach_enum dmach, uint32_t *rxdma_received, uint32_t *rxdma_drop);
/* get the overflow status of missed/received frame counter */
FlagStatus enet_counter_overflow_status_get(enet_dmach_enum dmach, enet_dmacounter_enum counter);
/* get the DMA slot number value */
uint16_t enet_dma_slot_value_get(enet_dmach_enum dmach);
/* set the DMA slot interval value */
void enet_dma_slot_interval_set(enet_dmach_enum dmach, uint16_t slot_interval);
/* set the DMA slot check related function parameters */
void enet_dma_slot_config(enet_dmach_enum dmach, uint32_t function, ControlStatus status);
/* set the watchdog timeout for receive interrupt from the DMA */
void enet_dma_rxinterrupt_watchdog_timer_set(enet_dmach_enum dmach, uint32_t count_uint, uint8_t count_val);
/* set the DMA alternate receive buffer size */
void enet_rxbuf_alternate_size_set(enet_dmach_enum dmach, uint16_t size);

/* MTL function */
/* set the algorithm for Tx scheduling */
void enet_schedalg_set(enet_txqalgotype_enum SchedAlgo);
/* set the weight for Tx queue */
void enet_txq_weight_set(enet_txq_enum enet_txq, uint32_t weight);
/* set the weight for Rx queue */
void enet_rxq_weight_set(enet_rxq_enum enet_rxq, uint32_t weight);
/* config the arbitration for Rx queue */
void enet_rxq_packet_arbitration_config(enet_rxq_enum enet_rxq, ControlStatus status);
/* enable dynamic mapping for Rx queue */
void enet_dynamic_mapping_set(enet_rxq_enum enet_rxq);
/* set the type, associated queue number and paket type */
ErrStatus enet_rxq_type_match_set(uint16_t reg_num, enet_rxq_enum enet_rxq, uint16_t typ_val, enet_packet_type_enum packet_type);
/* set the credit value for Tx queue 1 */
void enet_txq1_credit_set(enet_cbs_config_struct creditval);
/* set the mode and size for Tx queue */
void enet_txq_mode_size_set(enet_txq_enum enet_txq, enet_queopmode_enum queuemode, uint32_t queuesize);
/* set the size for Rx queue */
void enet_rxq_size_set(enet_rxq_enum enet_rxq, uint32_t queuesize);
/* select the dma channel for Rx queue */
void enet_rxq_dma_select(enet_rxq_enum enet_rxq, enet_dmach_enum dmach);
/* set the base time of GCL */
void enet_est_gcl_basetime_set(uint32_t second, uint32_t nanosecond);
/* get the base time of GCL */
void enet_est_gcl_basetime_get(enet_ESTConfig_struct *time_struct);
/* set the cycle time of GCL */
void enet_est_gcl_cycletime_set(uint8_t second, uint32_t nanosecond);
/* get the cycle time of GCL */
void enet_est_gcl_cycletime_get(enet_ESTConfig_struct *time_struct);
/* set the extension time of GCL */
void enet_est_gcl_extensiontime_set(uint32_t nanosecond);
/* get the extension time of GCL */
void enet_est_gcl_extensiontime_get(enet_ESTConfig_struct *time_struct);
/* set the length of GCL */
void enet_est_gcl_length_set(uint32_t length);
/* get the length of GCL */
void enet_est_gcl_length_get(enet_ESTConfig_struct *time_struct);
/* set the related parameter of GCL */
void enet_est_gcl_para_set(uint8_t addr, enet_GCLConfig_struct *gcl_struct);
/* get the related parameter of GCL */
void enet_est_gcl_para_get(uint8_t addr, enet_GCLConfig_struct *gcl_struct);
/* enable switching to S/W owned list */
void enet_est_gcl_switch_enable(void);
/* get the S/W owned list */
enet_gcl_enum enet_gcl_softwore_list_get(void);
/* get the current gcl slot number */
uint8_t enet_gcl_current_slot_get(void);
/* get the BTR error loop count */
uint8_t enet_btr_error_loop_get(void);
/* clear the queue number that have experienced error */
void enet_est_error_queue_clear(enet_est_error_enum err, enet_txq_enum enet_txq);
/* get the queue number that have experienced error */
FlagStatus enet_est_error_queue_satus_get(enet_est_error_enum err, enet_txq_enum enet_txq);
/* get the first queue number experience HLBF error */
enet_txq_enum enet_est_first_error_queue_get(void);
/* get the frame size of the first queue which experience HLBF error */
uint16_t enet_est_error_framesize_get(void);

/* config FPE related parameter */
void enet_fpe_advance_time_set(enet_FPEConfig_struct *fpe_struct);
/* get FPE related parameter */
void enet_fpe_advance_time_get(enet_FPEConfig_struct *fpe_struct);
/* set the launch expiry time */
void enet_launch_expiry_time_set(uint32_t mode, uint32_t offset, uint32_t gsn_offset);
/* set the fetch time */
void enet_fetch_time_set(uint32_t mode, uint32_t offset, uint32_t gsn_offset);
/* get the transmit queue debug state state */
uint32_t enet_txq_debug_state_get(enet_txq_enum enet_txq, enet_mtl_txq_state_enum state);
/* get the count of transmit queue packets */
uint32_t enet_txq_packet_count_get(enet_txq_enum enet_txq);
/* get the number of transmit queue status word */
uint32_t enet_txq_status_word_num_get(enet_txq_enum enet_txq);
/* get the receive queue debug state state */
uint32_t enet_rxq_debug_state_get(enet_rxq_enum enet_rxq, enet_mtl_rxq_state_enum state);
/* get the count of receive queue packets */
uint32_t enet_rxq_packet_count_get(enet_rxq_enum enet_rxq);
/* get the number of average bits per slot */
uint32_t enet_slot_average_bits_get(enet_txq_enum enet_txq);
/* config the transmit queue 1 ETS control related parameter */
void enet_txq1_ets_control(uint32_t config);
/* set the overhead bytes value */
void enet_overhead_value_set(uint8_t val);

/* special enhanced mode function */
/* configure descriptor to work in enhanced mode */
void enet_desc_select_enhanced_mode(enet_dmach_enum dmach);


/* configure descriptor to work in normal mode */
void enet_desc_select_normal_mode(enet_dmach_enum dmach);
/* configure enhanced descriptor  */
void enet_tbs_descriptors_ring_init(enet_dmach_enum dmach);
/* receive a packet data with timestamp values to application buffer, when the DMA is in normal mode */
ErrStatus enet_ptpframe_receive_normal_mode(enet_dmach_enum dmach, uint8_t *buffer, uint32_t bufsize, uint32_t timestamp[]);
/* handle current received frame but without data copy to application buffer in PTP normal mode */
#define ENET_NOCOPY_PTPFRAME_RECEIVE_NORMAL_MODE(dmach, ptr)             enet_ptpframe_receive_normal_mode(dmach, NULL, 0U, (ptr))
/* send data with timestamp values in application buffer as a transmit packet, when the DMA is in normal mode */
ErrStatus enet_ptpframe_transmit_normal_mode(enet_dmach_enum dmach, uint8_t *buffer, uint32_t length, uint32_t timestamp[]);
/* handle current transmit frame but without data copy from application buffer in PTP normal mode */
#define ENET_NOCOPY_PTPFRAME_TRANSMIT_NORMAL_MODE(dmach, len, ptr)       enet_ptpframe_transmit_normal_mode(dmach, NULL, (len), (ptr))

/* VLAN tag function */
/* compute the CRC of a hardware address */
uint32_t enet_crc_compute(uint8_t *mac, uint8_t size);
/* bitwise reversal on a 32 bit value */
uint32_t enet_value_reverse(uint32_t val);
/* set the vlan filter dma selection */
void enet_vlantag_filter_dmach_select(uint32_t filter, enet_dmach_enum dmach);
/* set up vlan filter feature */
void enet_vlantag_filter_feature_set(uint32_t filter, uint32_t feature);
/* set up vlan filter tag ID */
void enet_vlantag_filter_vid_set(uint32_t filter, uint32_t val);
/* add an address entry to the hash table filter */
void enet_add_dstaddr_hashfilter(uint8_t *macaddr);
/* remove an address entry to the hash table filter */
void enet_remove_dstaddr_hashfilter(uint8_t *macaddr);
/* add a vlan tag entry to the hash table filter */
void enet_add_vlantag_hashtable(uint32_t tagval);
/* remove a vlan tag entry to the hash table filter */
void enet_remove_vlantag_hashtable(uint32_t tagval);

/* flexible Rx parser function */
/* enable flexible Rx parser */
void enet_parser_enable(void);
/* disable flexible Rx parser */
void enet_parser_disable(void);
/* set the number of entries in the Instruction table */
void enet_parser_entry_number_set(enet_entry_type_enum type, uint32_t value);
/* config the instruction table entry */
void enet_parser_table_entry_config(uint32_t *value, uint8_t addr);
/* get the value of instruction table entry */
void enet_parser_table_entry_get(uint32_t *value, uint32_t addr);
/* get MTL parser overflow flag */
FlagStatus enet_parser_overflow_flag_get(enet_parser_counter_enum counter);
/* get MTL parser related count */
uint32_t enet_parser_count_get(enet_parser_counter_enum counter);

/* L3/L4 filter function */
/* select the DMA channel number for the packet that is passed by this L3_L4 filter */
void enet_l3l4_filter_dmach_select(enet_l3l4_filter_enum filter, enet_dmach_enum dmach);
/* config the L3_L4 filter related function */
void enet_l3l4_filter_config(enet_l3l4_filter_enum filter, uint32_t function, ControlStatus status);
/* set the L4 filter port number */
void enet_l4_port_num_set(enet_l3l4_filter_enum filter, uint16_t src_port, uint16_t dst_port);
/* configure L3 filter IPv4 address */
void enet_l3_ipv4_address_set(enet_l3l4_filter_enum filter, uint8_t src_ipaddr[], uint8_t dst_ipaddr[]);
/* configure L3 filter IPv6 address */
void enet_l3_ipv6_address_set(enet_l3l4_filter_enum filter, uint32_t ipaddr[]);

/* descriptor function */
/* get the bit flag of ENET dma descriptor */
FlagStatus enet_desc_flag_get(enet_descriptors_struct *desc, uint32_t desc_flag);
/* set the bit flag of ENET dma tx descriptor */
void enet_desc_flag_set(enet_descriptors_struct *desc, uint32_t desc_flag);
/* clear the bit flag of ENET dma tx descriptor */
void enet_desc_flag_clear(enet_descriptors_struct *desc, uint32_t desc_flag);
/* drop current receive frame */
void enet_rxframe_drop(enet_dmach_enum dmach);
/* enable DMA feature */
void enet_dma_feature_enable(enet_dmach_enum dmach, uint32_t feature);
/* disable DMA feature */
void enet_dma_feature_disable(enet_dmach_enum dmach, uint32_t feature);

/* PMT function */
/* wakeup packet filter register pointer reset */
void enet_pmt_filter_register_pointer_reset(void);
/* get the current value of the wakeup Packet Filter register pointer */
uint32_t enet_pmt_filter_register_pointer_get(void);
/* set the remote wakeup packet registers */
void enet_pmt_filter_config(uint32_t pdata[]);
/* enable wakeup management features */
void enet_pmt_feature_enable(uint32_t feature);
/* disable wakeup management features */
void enet_pmt_feature_disable(uint32_t feature);

/* EEE function */
/* set this counter so that the number of clock cycles of CSR clock is 1us */
void enet_eee_ustick_set(uint32_t tick);
/* set the value of LPI ralated timers */
void enet_eee_lpi_timer_set(enet_lpitimer_enum type, uint32_t val);
/* enable energy efficient ethernet features */
void enet_eee_lpi_feature_enable(uint32_t feature);
/* disable energy efficient ethernet features */
void enet_eee_lpi_feature_disable(uint32_t feature);
/* get lpi state */
FlagStatus enet_lpi_status_get(uint16_t state);
/* get LPI related counter */
uint32_t enet_lpi_counters_get(enet_lpi_counter_enum counter);

/* MMC function */
/* reset the MAC statistics counters */
void enet_mmc_counters_reset(void);
/* enable the MAC statistics counter features */
void enet_mmc_feature_enable(uint32_t feature);
/* disable the MAC statistics counter features */
void enet_mmc_feature_disable(uint32_t feature);
/* configure MAC statistics counters preset mode */
void enet_mmc_counters_preset_config(enet_mmc_preset_enum mode);
/* get MAC statistics counter */
uint32_t enet_mmc_counters_get(enet_mmc_counter_enum counter);

/* PTP function */
/* enable the PTP features */
void enet_ptp_feature_enable(uint32_t feature);
/* disable the PTP features */
void enet_ptp_feature_disable(uint32_t feature);
/* configure the PTP timestamp function */
ErrStatus enet_ptp_timestamp_function_config(enet_ptp_function_enum func);
/* configure the PTP system time subsecond and nanosubsecond increment value */
void enet_ptp_subsecond_increment_config(uint8_t subsecond, uint8_t nanosubsecond);
/* adjusting the PTP clock frequency only in fine update mode */
void enet_ptp_timestamp_addend_config(uint32_t add);
/* initializing or adding/subtracting to second of the PTP system time */
void enet_ptp_timestamp_update_config(uint32_t sign, uint16_t secondHi, uint32_t second, uint32_t subsecond);
/* get the PTP current system time */
void enet_ptp_system_time_get(enet_ptp_systime_struct *systime_struct);
/* configure the PPS output frequency */
void enet_ptp_pps_output_frequency_config(uint32_t freq);
/* configure the PPS single pulse output */
void enet_flexible_pps_singlepulse_output(enet_pps_enum pps, uint32_t second, uint32_t nanosubsecond, uint32_t width, ControlStatus interrupt);
/* configure the PPS train pulse output */
void enet_flexible_pps_trainpulse_output(enet_pps_enum pps, uint32_t second, uint32_t nanosubsecond, uint32_t width, uint32_t interval,
        ControlStatus interrupt);
/* configure the PPS output related command */
void enet_flexible_pps_command_config(enet_pps_enum pps, uint32_t stopsecond, uint32_t stopnanosubsecond, uint32_t command);
/* set the value of presentation time */
void enet_mcgr_present_time_set(enet_mcgr_enum mcgr, uint32_t seconds);
/* set the value of current presentation time */
uint32_t enet_mcgr_current_present_time_get(void);
/* configure the update value of presentation time */
void enet_mcgr_present_time_update(uint32_t nanosubsecond);
/* configure the mcgr related command */
void enet_mcgr_media_clock_config(enet_mcgr_enum mcgr, uint32_t mode);
/* set the timestamp asymmetry correction value */
void enet_timestamp_asym_correction_set(enet_timestamp_type_enum type, uint32_t val);
/* set the timestamp correction value */
void enet_timestamp_correction_value_set(enet_timestamp_type_enum type, uint32_t nanosecond, uint8_t nanosubsecond);
/* get the timestamp latency value */
uint16_t enet_timestamp_asym_latency_get(enet_timestamp_type_enum type, enet_timestamp_latency_enum latency);

/* VLAN Inclusion function */
/* writing to the per queue/channel VLAN inclusion */
void enet_queue_based_vlan_write(enet_vlantype_enum vlantype, uint16_t vlantag, enet_txq_enum queue);
/* read the type of the queue/channel VLAN */
enet_vlantype_enum enet_queue_based_vlan_type_read(enet_txq_enum queue);
/* read the vlan tag of the queue/channel VLAN */
uint16_t enet_queue_based_vlan_tagvid_read(enet_txq_enum queue);

/* ECC error function */
/* select the MTL ECC memory */
void enet_ecc_memory_select(uint32_t memory);
/* set the ECC error status related configuration */
void enet_ecc_status_clear_read(uint32_t config);
/* get the MTL ECC error address */
uint16_t enet_ecc_error_address_get(uint32_t type);
/* get the MTL ECC error counter */
uint16_t enet_ecc_error_count_get(uint32_t type);
/* set the MTL error injection mode */
void enet_error_injection_mode_set(uint32_t mode);
/* get the bit location of error injection */
uint16_t enet_error_injection_location_get(void);
/* set the MTL error injection configuration */
void enet_error_injection_config(uint32_t config);
#ifndef USE_DELAY
static void enet_delay(uint32_t ncount);
#endif
#endif /* GD32A7XX_ENET_H */
