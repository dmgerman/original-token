multiline_comment|/*&n; * INET&t;&t;An implementation of the TCP/IP protocol suite for the LINUX&n; *&t;&t;operating system.  INET is implemented using the  BSD Socket&n; *&t;&t;interface as the means of communication with the user level.&n; *&n; *&t;&t;Definitions for the DP8390 Network Interface Controller.&n; *&n; * Version:&t;$Id: dp8390.h,v 0.8.4.1 1992/11/10 00:17:18 waltje Exp $&n; *&n; * Authors:&t;Original taken from the 386BSD operating system.&n; *&t;&t;Ross Biro, &lt;bir7@leland.Stanford.Edu&gt;&n; *&t;&t;Fred N. van Kempen, &lt;waltje@uWalt.NL.Mugnet.ORG&gt;&n; *&n; *&t;&t;This program is free software; you can redistribute it and/or&n; *&t;&t;modify it under the terms of the GNU General Public License&n; *&t;&t;as published by the Free Software Foundation; either version&n; *&t;&t;2 of the License, or (at your option) any later version.&n; */
multiline_comment|/* format of status &n;     bit&n;     0&t;&t;packet ok&n;     1&t;&t;crc error&n;     2&t;&t;frame alignment error&n;     3&t;&t;fifo overrun&n;*/
DECL|macro|STRECVD
mdefine_line|#define STRECVD 0xf1
DECL|struct|wd_ring
r_struct
id|wd_ring
(brace
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* status&t;&t;&t;&t;*/
DECL|member|next
r_int
r_char
id|next
suffix:semicolon
multiline_comment|/* pointer to next packet&t;&t;*/
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/* packet length in bytes + 4&t;&t;*/
)brace
suffix:semicolon
multiline_comment|/* interrupt status defenitions&n;   bits&n;     0&t;&t;Recv.&n;     1&t;&t;Transmit&n;     2&t;&t;RcvErr&n;     3&t;&t;Transmit  Err&n;     4&t;&t;Overwrite warning&n;     5&t;&t;Counter overflow&n;     6&t;&t;Remote DMA complete&n;     7&t;&t;Reset Status&n;*/
DECL|macro|IRCV
mdefine_line|#define IRCV&t;&t;0x1
DECL|macro|ITRS
mdefine_line|#define ITRS&t;&t;0x2
DECL|macro|IRCE
mdefine_line|#define IRCE&t;&t;0x4
DECL|macro|ITRE
mdefine_line|#define ITRE&t;&t;0x8
DECL|macro|IOVER
mdefine_line|#define IOVER&t;&t;0x10
DECL|macro|ICOUNTERS
mdefine_line|#define ICOUNTERS&t;0x20
DECL|macro|IDMA
mdefine_line|#define IDMA &t;&t;0x40
DECL|macro|IRESET
mdefine_line|#define IRESET &t;&t;0x80
DECL|macro|IOVER
mdefine_line|#define IOVER&t;&t;0x10
DECL|macro|ICOUNTERS
mdefine_line|#define ICOUNTERS&t;0x20
DECL|macro|IDMA
mdefine_line|#define IDMA &t;&t;0x40
DECL|macro|IRESET
mdefine_line|#define IRESET &t;&t;0x80
multiline_comment|/* transmit status format&n;   bits&n;    0&t;&t;Packet transmitted ok.&n;    1&t;&t;Non Deferred transmition&n;    2&t;&t;Transmit collied&n;    3&t;&t;Transmit aborted&n;    4&t;&t;Carrier Sense Lost&n;    5&t;&t;Fifo Underrun&n;    6&t;&t;CD Heartbeat&n;    7&t;&t;Out of Window Collision&n;*/
DECL|macro|TROK
mdefine_line|#define TROK&t;&t;0x1
DECL|macro|TRAB
mdefine_line|#define TRAB&t;&t;0x4
multiline_comment|/* Page 0 */
DECL|macro|CR
mdefine_line|#define CR&t;(WD_BASE+WD_NIC+0)&t;/* RW - Command&t;&t;&t;*/
DECL|macro|CLDA0
mdefine_line|#define CLDA0 &t;(WD_BASE+WD_NIC+1)&t;/* R - CurrentLocalDMA Addr 0&t;*/
DECL|macro|PSTART
mdefine_line|#define PSTART&t;(WD_BASE+WD_NIC+1)&t;/* W - Page Start Register&t;*/
DECL|macro|CLDA1
mdefine_line|#define CLDA1&t;(WD_BASE+WD_NIC+2)&t;/* R - Current Local DMA Addr 1&t;*/
DECL|macro|PSTOP
mdefine_line|#define PSTOP&t;(WD_BASE+WD_NIC+2)&t;/* W - Page Stop Register&t;*/
DECL|macro|BNRY
mdefine_line|#define BNRY&t;(WD_BASE+WD_NIC+3)&t;/* RW - Boundry Pointer&t;&t;*/
DECL|macro|TSR
mdefine_line|#define TSR&t;(WD_BASE+WD_NIC+4)&t;/* R - Transmit Status Register&t;*/
DECL|macro|TPSR
mdefine_line|#define TPSR&t;(WD_BASE+WD_NIC+4)&t;/* W - Transmit Page Start&t;*/
DECL|macro|NCR
mdefine_line|#define NCR&t;(WD_BASE+WD_NIC+5)&t;/* R - Number of Collisions&t;*/
DECL|macro|TBCR0
mdefine_line|#define TBCR0&t;(WD_BASE+WD_NIC+5)&t;/* W - Transmit Byte Count 0&t;*/
DECL|macro|FIFO
mdefine_line|#define FIFO&t;(WD_BASE+WD_NIC+6)&t;/* R - FIFO&t;&t;&t;*/
DECL|macro|TBCR1
mdefine_line|#define TBCR1&t;(WD_BASE+WD_NIC+6)&t;/* W - Transmit Byte Count 1&t;*/
DECL|macro|ISR
mdefine_line|#define ISR&t;(WD_BASE+WD_NIC+7)&t;/* RW - Interrupt Status Reg&t;*/
DECL|macro|CRDA0
mdefine_line|#define CRDA0&t;(WD_BASE+WD_NIC+8)&t;/* R - Current Remote DMA Add 0&t;*/
DECL|macro|RSAR0
mdefine_line|#define RSAR0&t;(WD_BASE+WD_NIC+8)&t;/* W - Remote Start Address 0&t;*/
DECL|macro|CRDA1
mdefine_line|#define CRDA1&t;(WD_BASE+WD_NIC+9)&t;/* R - CurrentRemote DMA Addr 1&t;*/
multiline_comment|/* R - Reserved */
DECL|macro|RBCR0
mdefine_line|#define RBCR0&t;(WD_BASE+WD_NIC+0x0a)&t;/* W - Remote Byte Count 0&t;*/
multiline_comment|/* R - Reserved */
DECL|macro|RBCR1
mdefine_line|#define RBCR1&t;(WD_BASE+WD_NIC+0x0b)&t;/* W - Remote Byte Count 1&t;*/
DECL|macro|RSR
mdefine_line|#define RSR&t;(WD_BASE+WD_NIC+0x0c)&t;/* R - Receive Status Register&t;*/
DECL|macro|RCR
mdefine_line|#define RCR&t;(WD_BASE+WD_NIC+0x0c)&t;/* W - Receive Configuration&t;*/
DECL|macro|CNTR0
mdefine_line|#define CNTR0&t;(WD_BASE+WD_NIC+0x0d)&t;/* R - Frame Alignment Errors 0&t;*/
DECL|macro|TCR
mdefine_line|#define TCR&t;(WD_BASE+WD_NIC+0x0d)&t;/* W - Transmit Configuration&t;*/
DECL|macro|CNTR1
mdefine_line|#define CNTR1&t;(WD_BASE+WD_NIC+0x0e)&t;/* R - Frame Alignment Errors 1&t;*/ 
DECL|macro|DCR
mdefine_line|#define DCR&t;(WD_BASE+WD_NIC+0x0e)&t;/* W - Data Configuration&t;*/
DECL|macro|CNTR2
mdefine_line|#define CNTR2&t;(WD_BASE+WD_NIC+0x0f)&t;/* R - Missed Packet Errors&t;*/
DECL|macro|IMR
mdefine_line|#define IMR&t;(WD_BASE+WD_NIC+0x0f)&t;/* W - Interrupt Mask Register&t;*/
multiline_comment|/* Page 1 */
multiline_comment|/* RW - Command */
DECL|macro|PAR0
mdefine_line|#define PAR0&t;(WD_BASE+WD_NIC+0x01)&t;/* RW - Physical Address 0&t;*/
DECL|macro|PAR1
mdefine_line|#define PAR1&t;(WD_BASE+WD_NIC+0x02)&t;/* RW - Physical Address 1&t;*/
DECL|macro|PAR2
mdefine_line|#define PAR2&t;(WD_BASE+WD_NIC+0x03)&t;/* RW - Physical Address 2&t;*/
DECL|macro|PAR3
mdefine_line|#define PAR3&t;(WD_BASE+WD_NIC+0x04)&t;/* RW - Physical Address 3&t;*/
DECL|macro|PAR4
mdefine_line|#define PAR4&t;(WD_BASE+WD_NIC+0x04)&t;/* RW - Physical Address 4&t;*/
DECL|macro|PAR5
mdefine_line|#define PAR5&t;(WD_BASE+WD_NIC+0x05)&t;/* RW - Physical Address 5&t;*/
DECL|macro|PAR6
mdefine_line|#define PAR6&t;(WD_BASE+WD_NIC+0x06)&t;/* RW - Physical Address 6&t;*/
DECL|macro|CURR
mdefine_line|#define CURR&t;(WD_BASE+WD_NIC+0x07)&t;/* RW - Current Page&t;&t;*/
DECL|macro|MAR0
mdefine_line|#define MAR0&t;(WD_BASE+WD_NIC+0x08)&t;/* RW - Multicast Address 0&t;*/
DECL|macro|MAR1
mdefine_line|#define MAR1&t;(WD_BASE+WD_NIC+0x09)&t;/* RW - Multicast Address 1&t;*/
DECL|macro|MAR2
mdefine_line|#define MAR2&t;(WD_BASE+WD_NIC+0x0a)&t;/* RW - Multicast Address 2&t;*/
DECL|macro|MAR3
mdefine_line|#define MAR3&t;(WD_BASE+WD_NIC+0x0b)&t;/* RW - Multicast Address 3&t;*/
DECL|macro|MAR4
mdefine_line|#define MAR4&t;(WD_BASE+WD_NIC+0x0c)&t;/* RW - Multicast Address 4&t;*/
DECL|macro|MAR5
mdefine_line|#define MAR5&t;(WD_BASE+WD_NIC+0x0d)&t;/* RW - Multicast Address 5&t;*/
DECL|macro|MAR6
mdefine_line|#define MAR6&t;(WD_BASE+WD_NIC+0x0e)&t;/* RW - Multicast Address 6&t;*/
DECL|macro|MAR7
mdefine_line|#define MAR7&t;(WD_BASE+WD_NIC+0x0f)&t;/* RW - Multicast Address 7&t;*/
multiline_comment|/* Page 2 */
multiline_comment|/* Page 2 Registers are RW opposite Page 0 */
multiline_comment|/* and should be used for diagnostic purposes only */
multiline_comment|/* Command Register bits */
DECL|macro|STOP
mdefine_line|#define STOP&t;1&t;&t;/* In progress jobs finished, reset&t;*/
DECL|macro|STA
mdefine_line|#define STA&t;2&t;&t;/* Activate the NIC&t;&t;&t;*/
DECL|macro|TXP
mdefine_line|#define TXP&t;4&t;&t;/* Initiate TX packet&t;&t;&t;*/
DECL|macro|RD0
mdefine_line|#define RD0&t;8&t;&t;/* Remote DMA commands&t;&t;&t;*/
DECL|macro|RD1
mdefine_line|#define RD1&t;0x10&t;
DECL|macro|RD2
mdefine_line|#define RD2&t;0x20
DECL|macro|PS0
mdefine_line|#define PS0&t;0x40&t;&t;/* Page Select&t;&t;&t;&t;*/
DECL|macro|PS1
mdefine_line|#define PS1&t;0x80&t;&t;/* 00 = 0, 01 = 1, 10 = 2, 11=reserved&t;*/
DECL|macro|PAGE0
mdefine_line|#define PAGE0&t;~(PS0|PS1)&t;/* Remember to AND this&t;&t;&t;*/
DECL|macro|PAGE1
mdefine_line|#define PAGE1&t;PS0&t;&t;/* these can be OR&squot;d&t;&t;&t;*/
DECL|macro|PAGE2
mdefine_line|#define PAGE2&t;PS1
DECL|macro|NO_DMA
mdefine_line|#define NO_DMA&t;RD2
multiline_comment|/* Interrupt Status Register bits */
DECL|macro|PRX
mdefine_line|#define PRX&t;1&t;&t;/* Packet received with no errors&t;*/
DECL|macro|PTX
mdefine_line|#define PTX&t;2&t;&t;/* Packet transmitted with no errors&t;*/
DECL|macro|RXE
mdefine_line|#define RXE&t;4&t;&t;/* Packet received with errors&t;&t;*/
DECL|macro|TXE
mdefine_line|#define TXE&t;8&t;&t;/* Transmit aborted with errors&t;&t;*/
DECL|macro|OVW
mdefine_line|#define OVW&t;0x10&t;&t;/* Overwrite warning&t;&t;&t;*/
DECL|macro|CNT
mdefine_line|#define CNT&t;0x20&t;&t;/* Counter overflow warning&t;&t;*/
DECL|macro|RDC
mdefine_line|#define RDC&t;0x40&t;&t;/* Remote DMA complete&t;&t;&t;*/
DECL|macro|RST
mdefine_line|#define RST&t;0x80&t;&t;/* Reset status - does not cause intr&t;*/
multiline_comment|/* Interrupt Mask Register - 1 = enabled */
DECL|macro|PRXE
mdefine_line|#define PRXE&t;1&t;&t;/* Packet received&t;&t;&t;*/
DECL|macro|PTXE
mdefine_line|#define PTXE&t;2&t;&t;/* Packet transmitted&t;&t;&t;*/
DECL|macro|RXEE
mdefine_line|#define RXEE&t;4&t;&t;/* Receive error&t;&t;&t;*/
DECL|macro|TXEE
mdefine_line|#define TXEE&t;8&t;&t;/* Transmit error&t;&t;&t;*/
DECL|macro|OVWE
mdefine_line|#define OVWE&t;0x10&t;&t;/* Overwrite error&t;&t;&t;*/
DECL|macro|CNTE
mdefine_line|#define CNTE&t;0x20&t;&t;/* Counter overflow&t;&t;&t;*/
DECL|macro|RDCE
mdefine_line|#define RDCE&t;0x40&t;&t;/* Remote DMA complete&t;&t;&t;*/
multiline_comment|/* Data Configuration Register */
DECL|macro|WTS
mdefine_line|#define WTS&t;1&t;&t;/* Word Transfer 0 = byte, 1 = word&t;*/
DECL|macro|BOS
mdefine_line|#define BOS&t;2&t;&t;/* Byte Order 0 = 8086, 1 = 68000&t;*/
DECL|macro|LAS
mdefine_line|#define LAS&t;4&t;&t;/* Long Address 0=16bit, 1=32 bit DMA&t;*/
DECL|macro|LS
mdefine_line|#define LS&t;8&t;&t;/* Loopback = 0, 1 = Normal&t;&t;*/
DECL|macro|AR
mdefine_line|#define AR&t;0x10&t;&t;/* Autoinitialize = 1 DMA, 0 = software&t;*/
DECL|macro|FT0
mdefine_line|#define FT0&t;0x20&t;&t;/* FIFO Threshold (word mode /2 )&t;*/
DECL|macro|FT1
mdefine_line|#define FT1&t;0x40&t;&t;/* 00 = 2, 01 = 4, 10 = 8, 11=12 bytes&t;*/
multiline_comment|/* Transmit Configuration Register */
DECL|macro|CRCI
mdefine_line|#define CRCI&t;1&t;&t;/* CRC inhibit = 1, append = 0&t;&t;*/
DECL|macro|LB0
mdefine_line|#define LB0&t;2&t;&t;/* Loopback control 00=normal loopback&t;*/
DECL|macro|LB1
mdefine_line|#define LB1&t;4&t;&t;/* 01=internal, 10=ext1, 11=ext2&t;*/
DECL|macro|ATD
mdefine_line|#define ATD&t;8&t;&t;/* Auto Transmit Enable=1 tx inh enb&t;*/
DECL|macro|OFST
mdefine_line|#define OFST&t;0x10&t;&t;/* Collision offset 1 = modify to low&n;&t;&t;&t;&t;   priority mode&t;&t;&t;*/
multiline_comment|/* Transmitter Status Register */
DECL|macro|PTXOK
mdefine_line|#define PTXOK&t;1&t;&t;/* Packet transmitted without error&t;*/
multiline_comment|/* reserved */
DECL|macro|COL
mdefine_line|#define COL&t;4&t;&t;/* Xmit, check NCR for count&t;&t;*/
DECL|macro|ABT
mdefine_line|#define ABT&t;8&t;&t;/* Xmit aborted - 16 tries&t;&t;*/
DECL|macro|CRS
mdefine_line|#define CRS&t;0x10&t;&t;/* Carrier Sense lost&t;&t;&t;*/
DECL|macro|FU
mdefine_line|#define FU&t;0x20&t;&t;/* FIFO underrun&t;&t;&t;*/
DECL|macro|CDH
mdefine_line|#define CDH&t;0x40&t;&t;/* CD Heartbeat failed&t;&t;&t;*/
DECL|macro|OWC
mdefine_line|#define OWC&t;0x80&t;&t;/* Out of window collision&t;&t;*/
multiline_comment|/* Receive configuration Register */
DECL|macro|SEP
mdefine_line|#define SEP&t;1&t;&t;/* Save error packets = 1&t;&t;*/
DECL|macro|ARUNT
mdefine_line|#define ARUNT&t;2&t;&t;/* Accept RUNT packets &lt; 64 bytes&t;*/
DECL|macro|AB
mdefine_line|#define AB&t;4&t;&t;/* Accept Broadcast packets&t;&t;*/
DECL|macro|AM
mdefine_line|#define AM&t;8&t;&t;/* Accept Multicast packets&t;&t;*/
DECL|macro|PRO
mdefine_line|#define PRO&t;0x10&t;&t;/* Promiscuous mode&t;&t;&t;*/
DECL|macro|MON
mdefine_line|#define MON&t;0x20&t;&t;/* Monitor mode&t;&t;&t;&t;*/
multiline_comment|/* Receive Status Register */
DECL|macro|PRX
mdefine_line|#define PRX&t;1&t;&t;/* Packet received without error&t;*/
DECL|macro|CRC
mdefine_line|#define CRC&t;2&t;&t;/* CRC error&t;&t;&t;&t;*/
DECL|macro|FAE
mdefine_line|#define FAE&t;4&t;&t;/* Frame Alignment error&t;&t;*/
DECL|macro|FO
mdefine_line|#define FO&t;8&t;&t;/* FIFO overrun error&t;&t;&t;*/
DECL|macro|MPA
mdefine_line|#define MPA&t;0x10&t;&t;/* Missed packet&t;&t;&t;*/
DECL|macro|PHY
mdefine_line|#define PHY&t;0x20&t;&t;/* Physical=0, Multicast/Broadcast = 1&t;*/
DECL|macro|DIS
mdefine_line|#define DIS&t;0x40&t;&t;/* Receiver disabled (monitor mode)&t;*/
DECL|macro|DFR
mdefine_line|#define DFR&t;0x80&t;&t;/* Deferring - jabber on line&t;&t;*/
eof
