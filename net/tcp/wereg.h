multiline_comment|/* wereg.h */
multiline_comment|/*&n;    Copyright (C) 1992  Ross Biro&n;&n;    This program is free software; you can redistribute it and/or modify&n;    it under the terms of the GNU General Public License as published by&n;    the Free Software Foundation; either version 1, or (at your option)&n;    any later version.&n;&n;    This program is distributed in the hope that it will be useful,&n;    but WITHOUT ANY WARRANTY; without even the implied warranty of&n;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n;    GNU General Public License for more details.&n;&n;    You should have received a copy of the GNU General Public License&n;    along with this program; if not, write to the Free Software&n;    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n;&n;    The Author may be reached as bir7@leland.stanford.edu or&n;    C/O Department of Mathematics; Stanford University; Stanford, CA 94305&n;*/
multiline_comment|/* $Id: wereg.h,v 0.8.4.1 1992/11/10 00:17:18 bir7 Exp $ */
multiline_comment|/* $Log: wereg.h,v $&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *&n; * Revision 0.8.3.2  1992/11/10  00:14:47  bir7&n; * Changed malloc to kmalloc and added $i&b;Id$ and $Log: wereg.h,v $&n; * Revision 0.8.4.1  1992/11/10  00:17:18  bir7&n; * version change only.&n; *.&n; * */
multiline_comment|/* This is based on if_wereg.h from bsd386 */
multiline_comment|/* Uncomment the next line if you are having troubles with your &n;   8 bit card being recognized as 16 bit. */
multiline_comment|/* #define FORCE_8BIT */
DECL|struct|wd_ring
r_struct
id|wd_ring
(brace
DECL|member|status
r_int
r_char
id|status
suffix:semicolon
multiline_comment|/* status */
multiline_comment|/* format of status &n;     bit&n;     0&t;&t;packet ok&n;     1&t;&t;crc error&n;     2&t;&t;frame alignment error&n;     3&t;&t;fifo overrun&n;     */
DECL|macro|STRECVD
mdefine_line|#define STRECVD 0xf1
DECL|member|next
r_int
r_char
id|next
suffix:semicolon
multiline_comment|/* pointer to next packet. */
DECL|member|count
r_int
r_int
id|count
suffix:semicolon
multiline_comment|/*packet lenght in bytes + 4 */
)brace
suffix:semicolon
multiline_comment|/* Format of command register. &n;   bits&n;    0&t;&t;stop&n;    1&t;&t;start&n;    2&t;&t;transmit packet&n;   3-5&t;&t;Remote DMA command&t;&t;&n;   6-7&t;&t;Page Select */
DECL|macro|CSTOP
mdefine_line|#define CSTOP 0x1
DECL|macro|CSTART
mdefine_line|#define CSTART  0x2
DECL|macro|CTRANS
mdefine_line|#define CTRANS 0x4
DECL|macro|CRDMA
mdefine_line|#define CRDMA 0x38
DECL|macro|CRDMA_SHIFT
mdefine_line|#define CRDMA_SHIFT 3
DECL|macro|CPAGE
mdefine_line|#define CPAGE 0xc0
DECL|macro|CPAGE_SHIFT
mdefine_line|#define CPAGE_SHIFT 6
DECL|macro|CPAGE1
mdefine_line|#define CPAGE1 0x40
DECL|macro|CPAGE1
mdefine_line|#define CPAGE1 0x40
multiline_comment|/* interrupt status defenitions&n;   bits&n;     0&t;&t;Recv.&n;     1&t;&t;Transmit&n;     2&t;&t;RcvErr&n;     3&t;&t;Transmit  Err&n;     4&t;&t;Overwrite warning&n;     5&t;&t;Counter overflow&n;     6&t;&t;Remote DMA complete&n;     7&t;&t;Reset Status */
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
multiline_comment|/* transmit status format&n;   bits&n;    0&t;&t;Packet transmitted ok.&n;    1&t;&t;Non Deferred transmition&n;    2&t;&t;Transmit collied&n;    3&t;&t;Transmit aborted&n;    4&t;&t;Carrier Sense Lost&n;    5&t;&t;Fifo Underrun&n;    6&t;&t;CD Heartbeat&n;    7&t;&t;Out of Window Collision */
DECL|macro|TROK
mdefine_line|#define TROK 0x1
DECL|macro|TRAB
mdefine_line|#define TRAB 0x4
multiline_comment|/* Some ID stuff */
DECL|macro|WD_ID1
mdefine_line|#define WD_ID1 0x03
DECL|macro|WD_ID2
mdefine_line|#define WD_ID2 0x05
DECL|macro|WD_CHECK
mdefine_line|#define WD_CHECK 0xff
DECL|macro|WD_PAGE
mdefine_line|#define WD_PAGE 256 /* page size in bytes. */
DECL|macro|WD_TXBS
mdefine_line|#define WD_TXBS 6   /* size of transmit buffer in pages. */
DECL|macro|WD_MAX_PAGES
mdefine_line|#define WD_MAX_PAGES 32 /* Number of pages off ram on card (8k) */
DECL|macro|WD_NIC
mdefine_line|#define WD_NIC 16   /* i/o base offset to NIC */
multiline_comment|/* Some configuration stuff. */
multiline_comment|/* where the memory is mapped in. */
DECL|macro|WD_MEM
mdefine_line|#define WD_MEM (dev-&gt;mem_start)
DECL|macro|WD_BUFFEND
mdefine_line|#define WD_BUFFEND (dev-&gt;mem_end)
DECL|macro|WD_MEMSIZE
mdefine_line|#define WD_MEMSIZE (WD_BUFFEND-WD_MEM)
DECL|macro|WD_BASE
mdefine_line|#define WD_BASE (dev-&gt;base_addr)
DECL|macro|TRANS_MASK
mdefine_line|#define TRANS_MASK 0xa
DECL|macro|RECV_MASK
mdefine_line|#define RECV_MASK  0x5
DECL|macro|WD_DCONFIG
mdefine_line|#define WD_DCONFIG 0x48
DECL|macro|WD_RCONFIG
mdefine_line|#define WD_RCONFIG 0x4
DECL|macro|WD_MCONFIG
mdefine_line|#define WD_MCONFIG 0x20
DECL|macro|WD_TCONFIG
mdefine_line|#define WD_TCONFIG 0x0
DECL|macro|WD_IMEM
mdefine_line|#define WD_IMEM (((WD_MEM&gt;&gt;13) &amp; 0x3f)|0x40)
multiline_comment|/* WD registers. */
DECL|macro|WD_ROM
mdefine_line|#define WD_ROM (WD_BASE+8)
DECL|macro|WD_CTL
mdefine_line|#define WD_CTL (WD_BASE+0)
multiline_comment|/* WD NIC register offsets */
DECL|macro|WD_COMM
mdefine_line|#define WD_COMM (WD_BASE+WD_NIC+0x00) &t;&t;/* command register */
DECL|macro|WD_PSTRT
mdefine_line|#define WD_PSTRT (WD_BASE+WD_NIC+0x01)&t;&t;/* page start register */
DECL|macro|WD_PSTOP
mdefine_line|#define WD_PSTOP (WD_BASE+WD_NIC+0x02)&t;&t;/* page stop register */
DECL|macro|WD_BNDR
mdefine_line|#define WD_BNDR  (WD_BASE+WD_NIC+0x03)&t;&t;/* Boundary Pointer */
DECL|macro|WD_TRST
mdefine_line|#define WD_TRST (WD_BASE+WD_NIC+0x04)&t;&t;/* Transmit Status */
DECL|macro|WD_TRPG
mdefine_line|#define WD_TRPG (WD_BASE+WD_NIC+0x04)&t;&t;/* Transmit Page */
DECL|macro|WD_TB0
mdefine_line|#define WD_TB0  (WD_BASE+WD_NIC+0x05)&t;&t;/* Transmit byte count, low */
DECL|macro|WD_TB1
mdefine_line|#define WD_TB1&t;(WD_BASE+WD_NIC+0x06)&t;&t;/* Transmit byte count, high */
DECL|macro|WD_ISR
mdefine_line|#define WD_ISR  (WD_BASE+WD_NIC+0x07)&t;&t;/* Interrupt status register */
DECL|macro|WD_RBY0
mdefine_line|#define WD_RBY0 (WD_BASE+WD_NIC+0x0a)            /* remote byte count low. */
DECL|macro|WD_RBY1
mdefine_line|#define WD_RBY1 (WD_BASE+WD_NIC+0x0b)            /* remote byte count high. */
DECL|macro|WD_RCC
mdefine_line|#define WD_RCC&t;(WD_BASE+WD_NIC+0x0c)&t;&t;/* receive configuration */
DECL|macro|WD_TRC
mdefine_line|#define WD_TRC&t;(WD_BASE+WD_NIC+0x0d)&t;&t;/* transmit configuration */
DECL|macro|WD_DCR
mdefine_line|#define WD_DCR  (WD_BASE+WD_NIC+0x0e)            /* data configuration */
DECL|macro|WD_IMR
mdefine_line|#define WD_IMR  (WD_BASE+WD_NIC+0x0f)            /* Interrupt Mask register. */
DECL|macro|WD_PAR0
mdefine_line|#define WD_PAR0 (WD_BASE+WD_NIC+0x01)
DECL|macro|WD_CUR
mdefine_line|#define WD_CUR  (WD_BASE+WD_NIC+0x07)
DECL|macro|WD_MAR0
mdefine_line|#define WD_MAR0 (WD_BASE+WD_NIC+0x08)
multiline_comment|/* rth additions */
DECL|macro|EN_CMD
mdefine_line|#define EN_CMD (WD_BASE+0)
DECL|macro|EN_REG1
mdefine_line|#define EN_REG1 (WD_BASE+1)
DECL|macro|EN_REG5
mdefine_line|#define EN_REG5 (WD_BASE+5)
DECL|macro|EN_SAPROM
mdefine_line|#define EN_SAPROM (WD_BASE+8)
DECL|macro|EN_REGE
mdefine_line|#define EN_REGE (WD_BASE+0x0e)
DECL|macro|EN_OFFSET
mdefine_line|#define EN_OFFSET 16
multiline_comment|/* WD Commands for EN_CMD */
DECL|macro|EN_RESET
mdefine_line|#define EN_RESET
DECL|macro|EN_MEMEN
mdefine_line|#define EN_MEMEN 0x40
DECL|macro|EN_MEM_MASK
mdefine_line|#define EN_MEM_MASK 0x3f
multiline_comment|/* WD Bus Register bits */
DECL|macro|BUS16
mdefine_line|#define BUS16 1
multiline_comment|/* WD REG5 Commands */
DECL|macro|MEM16ENABLE
mdefine_line|#define MEM16ENABLE 0x80
DECL|macro|LAN16ENABLE
mdefine_line|#define LAN16ENABLE 0x40
DECL|macro|MEMMASK
mdefine_line|#define MEMMASK 0x1f
DECL|macro|BIT19
mdefine_line|#define BIT19 0x1
multiline_comment|/* Memory test pattern to use */
DECL|macro|TESTPATTERN
mdefine_line|#define TESTPATTERN 0x5a
multiline_comment|/* Western Digital Additional Registers */
multiline_comment|/* National Semiconductor Definitions */
multiline_comment|/* Page 0 */
DECL|macro|CR
mdefine_line|#define CR&t;(WD_BASE+WD_NIC+0)&t;/* RW - Command */
DECL|macro|CLDA0
mdefine_line|#define CLDA0 &t;(WD_BASE+WD_NIC+1)&t;/* R - Current Local DMA Address 0 */
DECL|macro|PSTART
mdefine_line|#define PSTART&t;(WD_BASE+WD_NIC+1)&t;/* W - Page Start Register */
DECL|macro|CLDA1
mdefine_line|#define CLDA1&t;(WD_BASE+WD_NIC+2)&t;/* R - Current Local DMA Address 1 */
DECL|macro|PSTOP
mdefine_line|#define PSTOP&t;(WD_BASE+WD_NIC+2)&t;/* W - Page Stop Register */
DECL|macro|BNRY
mdefine_line|#define BNRY&t;(WD_BASE+WD_NIC+3)&t;/* RW - Boundry Pointer */
DECL|macro|TSR
mdefine_line|#define TSR&t;(WD_BASE+WD_NIC+4)&t;/* R - Transmit Status Register */
DECL|macro|TPSR
mdefine_line|#define TPSR&t;(WD_BASE+WD_NIC+4)&t;/* W - Transmit Page Start */
DECL|macro|NCR
mdefine_line|#define NCR&t;(WD_BASE+WD_NIC+5)&t;/* R - Number of Collisions */
DECL|macro|TBCR0
mdefine_line|#define TBCR0&t;(WD_BASE+WD_NIC+5)&t;/* W - Transmit Byte Count 0 */
DECL|macro|FIFO
mdefine_line|#define FIFO&t;(WD_BASE+WD_NIC+6)&t;/* R - FIFO */
DECL|macro|TBCR1
mdefine_line|#define TBCR1&t;(WD_BASE+WD_NIC+6)&t;/* W - Transmit Byte Count 1 */
DECL|macro|ISR
mdefine_line|#define ISR&t;(WD_BASE+WD_NIC+7)&t;/* RW - Interrupt Status Register */
DECL|macro|CRDA0
mdefine_line|#define CRDA0&t;(WD_BASE+WD_NIC+8)&t;/* R - Current Remote DMA Address 0 */
DECL|macro|RSAR0
mdefine_line|#define RSAR0&t;(WD_BASE+WD_NIC+8)&t;/* W - Remote Start Address 0 */
DECL|macro|CRDA1
mdefine_line|#define CRDA1&t;(WD_BASE+WD_NIC+9)&t;/* R - Current Remote DMA Address 1 */
DECL|macro|RSAR1
mdefine_line|#define RSAR1&t;(WD_BASE+WD_NIC+9)&t;/* W - Remote Start Address 1 */
multiline_comment|/* R - Reserved */
DECL|macro|RBCR0
mdefine_line|#define RBCR0&t;(WD_BASE+WD_NIC+0x0a)&t;/* W - Remote Byte Count 0 */
multiline_comment|/* R - Reserved */
DECL|macro|RBCR1
mdefine_line|#define RBCR1&t;(WD_BASE+WD_NIC+0x0b)&t;/* W - Remote Byte Count 1 */
DECL|macro|RSR
mdefine_line|#define RSR&t;(WD_BASE+WD_NIC+0x0c)&t;/* R - Receive Status Register */
DECL|macro|RCR
mdefine_line|#define RCR&t;(WD_BASE+WD_NIC+0x0c)&t;/* W - Receive Configuration */
DECL|macro|CNTR0
mdefine_line|#define CNTR0&t;(WD_BASE+WD_NIC+0x0d)&t;/* R - Frame Alignment Errors 0 */
DECL|macro|TCR
mdefine_line|#define TCR&t;(WD_BASE+WD_NIC+0x0d)&t;/* W - Transmit Configuration */
DECL|macro|CNTR1
mdefine_line|#define CNTR1&t;(WD_BASE+WD_NIC+0x0e)&t;/* R - Frame Alignment Errors 1 */ 
DECL|macro|DCR
mdefine_line|#define DCR&t;(WD_BASE+WD_NIC+0x0e)&t;/* W - Data Configuration */
DECL|macro|CNTR2
mdefine_line|#define CNTR2&t;(WD_BASE+WD_NIC+0x0f)&t;/* R - Missed Packet Errors */
DECL|macro|IMR
mdefine_line|#define IMR&t;(WD_BASE+WD_NIC+0x0f)&t;/* W - Interrupt Mask Register */
multiline_comment|/* Page 1 */
multiline_comment|/* RW - Command */
DECL|macro|PAR0
mdefine_line|#define PAR0&t;(WD_BASE+WD_NIC+0x01)&t;/* RW - Physical Address 0 */
DECL|macro|PAR1
mdefine_line|#define PAR1&t;(WD_BASE+WD_NIC+0x02)&t;/* RW - Physical Address 1 */
DECL|macro|PAR2
mdefine_line|#define PAR2&t;(WD_BASE+WD_NIC+0x03)&t;/* RW - Physical Address 2 */
DECL|macro|PAR3
mdefine_line|#define PAR3&t;(WD_BASE+WD_NIC+0x04)&t;/* RW - Physical Address 3 */
DECL|macro|PAR4
mdefine_line|#define PAR4&t;(WD_BASE+WD_NIC+0x04)&t;/* RW - Physical Address 4 */
DECL|macro|PAR5
mdefine_line|#define PAR5&t;(WD_BASE+WD_NIC+0x05)&t;/* RW - Physical Address 5 */
DECL|macro|PAR6
mdefine_line|#define PAR6&t;(WD_BASE+WD_NIC+0x06)&t;/* RW - Physical Address 6 */
DECL|macro|CURR
mdefine_line|#define CURR&t;(WD_BASE+WD_NIC+0x07)&t;/* RW - Current Page */
DECL|macro|MAR0
mdefine_line|#define MAR0&t;(WD_BASE+WD_NIC+0x08)&t;/* RW - Multicast Address 0 */
DECL|macro|MAR1
mdefine_line|#define MAR1&t;(WD_BASE+WD_NIC+0x09)&t;/* RW - Multicast Address 1 */
DECL|macro|MAR2
mdefine_line|#define MAR2&t;(WD_BASE+WD_NIC+0x0a)&t;/* RW - Multicast Address 2 */
DECL|macro|MAR3
mdefine_line|#define MAR3&t;(WD_BASE+WD_NIC+0x0b)&t;/* RW - Multicast Address 3 */
DECL|macro|MAR4
mdefine_line|#define MAR4&t;(WD_BASE+WD_NIC+0x0c)&t;/* RW - Multicast Address 4 */
DECL|macro|MAR5
mdefine_line|#define MAR5&t;(WD_BASE+WD_NIC+0x0d)&t;/* RW - Multicast Address 5 */
DECL|macro|MAR6
mdefine_line|#define MAR6&t;(WD_BASE+WD_NIC+0x0e)&t;/* RW - Multicast Address 6 */
DECL|macro|MAR7
mdefine_line|#define MAR7&t;(WD_BASE+WD_NIC+0x0f)&t;/* RW - Multicast Address 7 */
multiline_comment|/* Page 2 */
multiline_comment|/* Page 2 Registers are RW opposite Page 0 */
multiline_comment|/* and should be used for diagnostic purposes only */
multiline_comment|/* Command Register bits */
DECL|macro|STOP
mdefine_line|#define STOP&t;1&t;/* In progress jobs finished, software reset */
DECL|macro|STA
mdefine_line|#define STA&t;2&t;/* Activate the NIC */
DECL|macro|TXP
mdefine_line|#define TXP&t;4&t;/* Initiate TX packet */
DECL|macro|RD0
mdefine_line|#define RD0&t;8&t;/* Remote DMA commands */
DECL|macro|RD1
mdefine_line|#define RD1&t;0x10&t;
DECL|macro|RD2
mdefine_line|#define RD2&t;0x20
DECL|macro|PS0
mdefine_line|#define PS0&t;0x40&t;/* Page Select */
DECL|macro|PS1
mdefine_line|#define  PS1&t;0x80&t;/* 00 = 0, 01 = 1, 10 = 2, 11 = reserved */
DECL|macro|PAGE0
mdefine_line|#define PAGE0&t;~(PS0|PS1)&t;/* Remember to AND this */
DECL|macro|PAGE1
mdefine_line|#define PAGE1&t;PS0&t;&t;/* these can be OR&squot;d */
DECL|macro|PAGE2
mdefine_line|#define PAGE2&t;PS1
DECL|macro|NO_DMA
mdefine_line|#define NO_DMA&t;RD2
multiline_comment|/* Interrupt Status Register bits */
DECL|macro|PRX
mdefine_line|#define PRX&t;1&t;/* Packet received with no errors */
DECL|macro|PTX
mdefine_line|#define PTX&t;2&t;/* Packet transmitted with no errors */
DECL|macro|RXE
mdefine_line|#define RXE&t;4&t;/* Packet received with errors */
DECL|macro|TXE
mdefine_line|#define TXE&t;8&t;/* Transmit aborted with errors */
DECL|macro|OVW
mdefine_line|#define OVW&t;0x10&t;/* Overwrite warning */
DECL|macro|CNT
mdefine_line|#define CNT&t;0x20&t;/* Counter overflow warning */
DECL|macro|RDC
mdefine_line|#define RDC&t;0x40&t;/* Remote DMA complete */
DECL|macro|RST
mdefine_line|#define RST&t;0x80&t;/* Reset status - does not cause interrupts */
multiline_comment|/* Interrupt Mask Register - 1 = enabled */
DECL|macro|PRXE
mdefine_line|#define PRXE&t;1&t;/* Packet received */
DECL|macro|PTXE
mdefine_line|#define PTXE&t;2&t;/* Packet transmitted */
DECL|macro|RXEE
mdefine_line|#define RXEE&t;4&t;/* Receive error */
DECL|macro|TXEE
mdefine_line|#define TXEE&t;8&t;/* Transmit error */
DECL|macro|OVWE
mdefine_line|#define OVWE&t;0x10&t;/* Overwrite error */
DECL|macro|CNTE
mdefine_line|#define CNTE&t;0x20&t;/* Counter overflow */
DECL|macro|RDCE
mdefine_line|#define RDCE&t;0x40&t;/* Remote DMA complete */
multiline_comment|/* Data Configuration Register */
DECL|macro|WTS
mdefine_line|#define WTS&t;1&t;/* Word Transfer 0 = byte, 1 = word */
DECL|macro|BOS
mdefine_line|#define BOS&t;2&t;/* Byte Order 0 = 8086, 1 = 68000 */
DECL|macro|LAS
mdefine_line|#define LAS&t;4&t;/* Long Address 0 = 16bit, 1 = 32 bit DMA */
DECL|macro|LS
mdefine_line|#define LS&t;8&t;/* Loopback = 0, 1 = Normal */
DECL|macro|AR
mdefine_line|#define AR&t;0x10&t;/* Autoinitialize = 1 DMA, 0 = software */
DECL|macro|FT0
mdefine_line|#define FT0&t;0x20&t;/* FIFO Threshold (word mode /2 ) */
DECL|macro|FT1
mdefine_line|#define FT1&t;0x40&t;/* 00 = 2, 01 = 4, 10 = 8, 11 = 12 bytes */
multiline_comment|/* Transmit Configuration Register */
DECL|macro|CRCI
mdefine_line|#define CRCI&t;1&t;/* CRC inhibit = 1, append = 0 */
DECL|macro|LB0
mdefine_line|#define LB0&t;2&t;/* Loopback control 00 = normal loopback */
DECL|macro|LB1
mdefine_line|#define LB1&t;4&t;/* 01 = internal, 10 = external1, 11 = external2 */
DECL|macro|ATD
mdefine_line|#define ATD&t;8&t;/* Auto Transmit Enable = 1 tx inhibit enabled */
DECL|macro|OFST
mdefine_line|#define OFST&t;0x10&t;/* Collision offset 1 = modify to low priority mode */
multiline_comment|/* Transmitter Status Register */
DECL|macro|PTXOK
mdefine_line|#define PTXOK&t;1&t;/* Packet transmitted without error */
multiline_comment|/* reserved */
DECL|macro|COL
mdefine_line|#define COL&t;4&t;/* Transmit collided, check NCR for count */
DECL|macro|ABT
mdefine_line|#define ABT&t;8&t;/* Transmit aborted - 16 tries */
DECL|macro|CRS
mdefine_line|#define CRS&t;0x10&t;/* Carrier Sense lost */
DECL|macro|FU
mdefine_line|#define FU&t;0x20&t;/* FIFO underrun */
DECL|macro|CDH
mdefine_line|#define CDH&t;0x40&t;/* CD Heartbeat failed */
DECL|macro|OWC
mdefine_line|#define OWC&t;0x80&t;/* Out of window collision */
multiline_comment|/* Receive configuration Register */
DECL|macro|SEP
mdefine_line|#define SEP&t;1&t;/* Save error packets = 1 */
DECL|macro|ARUNT
mdefine_line|#define ARUNT&t;2&t;/* Accept RUNT packets &lt; 64 bytes */
DECL|macro|AB
mdefine_line|#define AB&t;4&t;/* Accept Broadcast packets */
DECL|macro|AM
mdefine_line|#define AM&t;8&t;/* Accept Multicast packets */
DECL|macro|PRO
mdefine_line|#define PRO&t;0x10&t;/* Promiscuous mode */
DECL|macro|MON
mdefine_line|#define MON&t;0x20&t;/* Monitor mode */
multiline_comment|/* Receive Status Register */
DECL|macro|PRX
mdefine_line|#define PRX&t;1&t;/* Packet received without error */
DECL|macro|CRC
mdefine_line|#define CRC&t;2&t;/* CRC error */
DECL|macro|FAE
mdefine_line|#define FAE&t;4&t;/* Frame Alignment error */
DECL|macro|FO
mdefine_line|#define FO&t;8&t;/* FIFO overrun error */
DECL|macro|MPA
mdefine_line|#define MPA&t;0x10&t;/* Missed packet */
DECL|macro|PHY
mdefine_line|#define PHY&t;0x20&t;/* Physical = 0, Multicast/Broadcast = 1 */
DECL|macro|DIS
mdefine_line|#define DIS&t;0x40&t;/* Receiver disabled (monitor mode) */
DECL|macro|DFR
mdefine_line|#define DFR&t;0x80&t;/* Deferring - jabber on line */
multiline_comment|/* rth additions */
DECL|macro|EN_CMD
mdefine_line|#define EN_CMD (WD_BASE+0)
DECL|macro|EN_REG1
mdefine_line|#define EN_REG1 (WD_BASE+1)
DECL|macro|EN_REG5
mdefine_line|#define EN_REG5 (WD_BASE+5)
DECL|macro|EN_SAPROM
mdefine_line|#define EN_SAPROM (WD_BASE+8)
DECL|macro|EN_REGE
mdefine_line|#define EN_REGE (WD_BASE+0x0e)
DECL|macro|EN_OFFSET
mdefine_line|#define EN_OFFSET 16
multiline_comment|/* WD Commands for EN_CMD */
DECL|macro|EN_RESET
mdefine_line|#define EN_RESET
DECL|macro|EN_MEMEN
mdefine_line|#define EN_MEMEN 0x40
DECL|macro|EN_MEM_MASK
mdefine_line|#define EN_MEM_MASK 0x3f
multiline_comment|/* WD Bus Register bits */
DECL|macro|BUS16
mdefine_line|#define BUS16 1
multiline_comment|/* WD REG5 Commands */
DECL|macro|MEM16ENABLE
mdefine_line|#define MEM16ENABLE 0x80
DECL|macro|LAN16ENABLE
mdefine_line|#define LAN16ENABLE 0x40
DECL|macro|MEMMASK
mdefine_line|#define MEMMASK 0x1f
DECL|macro|BIT19
mdefine_line|#define BIT19 0x1
multiline_comment|/* Memory test pattern to use */
DECL|macro|TESTPATTERN
mdefine_line|#define TESTPATTERN 0x5a
multiline_comment|/* Western Digital Additional Registers */
multiline_comment|/* National Semiconductor Definitions */
multiline_comment|/* Page 0 */
DECL|macro|CR
mdefine_line|#define CR&t;(WD_BASE+WD_NIC+0)&t;/* RW - Command */
DECL|macro|CLDA0
mdefine_line|#define CLDA0 &t;(WD_BASE+WD_NIC+1)&t;/* R - Current Local DMA Address 0 */
DECL|macro|PSTART
mdefine_line|#define PSTART&t;(WD_BASE+WD_NIC+1)&t;/* W - Page Start Register */
DECL|macro|CLDA1
mdefine_line|#define CLDA1&t;(WD_BASE+WD_NIC+2)&t;/* R - Current Local DMA Address 1 */
DECL|macro|PSTOP
mdefine_line|#define PSTOP&t;(WD_BASE+WD_NIC+2)&t;/* W - Page Stop Register */
DECL|macro|BNRY
mdefine_line|#define BNRY&t;(WD_BASE+WD_NIC+3)&t;/* RW - Boundry Pointer */
DECL|macro|TSR
mdefine_line|#define TSR&t;(WD_BASE+WD_NIC+4)&t;/* R - Transmit Status Register */
DECL|macro|TPSR
mdefine_line|#define TPSR&t;(WD_BASE+WD_NIC+4)&t;/* W - Transmit Page Start */
DECL|macro|NCR
mdefine_line|#define NCR&t;(WD_BASE+WD_NIC+5)&t;/* R - Number of Collisions */
DECL|macro|TBCR0
mdefine_line|#define TBCR0&t;(WD_BASE+WD_NIC+5)&t;/* W - Transmit Byte Count 0 */
DECL|macro|FIFO
mdefine_line|#define FIFO&t;(WD_BASE+WD_NIC+6)&t;/* R - FIFO */
DECL|macro|TBCR1
mdefine_line|#define TBCR1&t;(WD_BASE+WD_NIC+6)&t;/* W - Transmit Byte Count 1 */
DECL|macro|ISR
mdefine_line|#define ISR&t;(WD_BASE+WD_NIC+7)&t;/* RW - Interrupt Status Register */
DECL|macro|CRDA0
mdefine_line|#define CRDA0&t;(WD_BASE+WD_NIC+8)&t;/* R - Current Remote DMA Address 0 */
DECL|macro|RSAR0
mdefine_line|#define RSAR0&t;(WD_BASE+WD_NIC+8)&t;/* W - Remote Start Address 0 */
DECL|macro|CRDA1
mdefine_line|#define CRDA1&t;(WD_BASE+WD_NIC+9)&t;/* R - Current Remote DMA Address 1 */
DECL|macro|RSAR1
mdefine_line|#define RSAR1&t;(WD_BASE+WD_NIC+9)&t;/* W - Remote Start Address 1 */
multiline_comment|/* R - Reserved */
DECL|macro|RBCR0
mdefine_line|#define RBCR0&t;(WD_BASE+WD_NIC+0x0a)&t;/* W - Remote Byte Count 0 */
multiline_comment|/* R - Reserved */
DECL|macro|RBCR1
mdefine_line|#define RBCR1&t;(WD_BASE+WD_NIC+0x0b)&t;/* W - Remote Byte Count 1 */
DECL|macro|RSR
mdefine_line|#define RSR&t;(WD_BASE+WD_NIC+0x0c)&t;/* R - Receive Status Register */
DECL|macro|RCR
mdefine_line|#define RCR&t;(WD_BASE+WD_NIC+0x0c)&t;/* W - Receive Configuration */
DECL|macro|CNTR0
mdefine_line|#define CNTR0&t;(WD_BASE+WD_NIC+0x0d)&t;/* R - Frame Alignment Errors 0 */
DECL|macro|TCR
mdefine_line|#define TCR&t;(WD_BASE+WD_NIC+0x0d)&t;/* W - Transmit Configuration */
DECL|macro|CNTR1
mdefine_line|#define CNTR1&t;(WD_BASE+WD_NIC+0x0e)&t;/* R - Frame Alignment Errors 1 */ 
DECL|macro|DCR
mdefine_line|#define DCR&t;(WD_BASE+WD_NIC+0x0e)&t;/* W - Data Configuration */
DECL|macro|CNTR2
mdefine_line|#define CNTR2&t;(WD_BASE+WD_NIC+0x0f)&t;/* R - Missed Packet Errors */
DECL|macro|IMR
mdefine_line|#define IMR&t;(WD_BASE+WD_NIC+0x0f)&t;/* W - Interrupt Mask Register */
multiline_comment|/* Page 1 */
multiline_comment|/* RW - Command */
DECL|macro|PAR0
mdefine_line|#define PAR0&t;(WD_BASE+WD_NIC+0x01)&t;/* RW - Physical Address 0 */
DECL|macro|PAR1
mdefine_line|#define PAR1&t;(WD_BASE+WD_NIC+0x02)&t;/* RW - Physical Address 1 */
DECL|macro|PAR2
mdefine_line|#define PAR2&t;(WD_BASE+WD_NIC+0x03)&t;/* RW - Physical Address 2 */
DECL|macro|PAR3
mdefine_line|#define PAR3&t;(WD_BASE+WD_NIC+0x04)&t;/* RW - Physical Address 3 */
DECL|macro|PAR4
mdefine_line|#define PAR4&t;(WD_BASE+WD_NIC+0x04)&t;/* RW - Physical Address 4 */
DECL|macro|PAR5
mdefine_line|#define PAR5&t;(WD_BASE+WD_NIC+0x05)&t;/* RW - Physical Address 5 */
DECL|macro|PAR6
mdefine_line|#define PAR6&t;(WD_BASE+WD_NIC+0x06)&t;/* RW - Physical Address 6 */
DECL|macro|CURR
mdefine_line|#define CURR&t;(WD_BASE+WD_NIC+0x07)&t;/* RW - Current Page */
DECL|macro|MAR0
mdefine_line|#define MAR0&t;(WD_BASE+WD_NIC+0x08)&t;/* RW - Multicast Address 0 */
DECL|macro|MAR1
mdefine_line|#define MAR1&t;(WD_BASE+WD_NIC+0x09)&t;/* RW - Multicast Address 1 */
DECL|macro|MAR2
mdefine_line|#define MAR2&t;(WD_BASE+WD_NIC+0x0a)&t;/* RW - Multicast Address 2 */
DECL|macro|MAR3
mdefine_line|#define MAR3&t;(WD_BASE+WD_NIC+0x0b)&t;/* RW - Multicast Address 3 */
DECL|macro|MAR4
mdefine_line|#define MAR4&t;(WD_BASE+WD_NIC+0x0c)&t;/* RW - Multicast Address 4 */
DECL|macro|MAR5
mdefine_line|#define MAR5&t;(WD_BASE+WD_NIC+0x0d)&t;/* RW - Multicast Address 5 */
DECL|macro|MAR6
mdefine_line|#define MAR6&t;(WD_BASE+WD_NIC+0x0e)&t;/* RW - Multicast Address 6 */
DECL|macro|MAR7
mdefine_line|#define MAR7&t;(WD_BASE+WD_NIC+0x0f)&t;/* RW - Multicast Address 7 */
multiline_comment|/* Page 2 */
multiline_comment|/* Page 2 Registers are RW opposite Page 0 */
multiline_comment|/* and should be used for diagnostic purposes only */
multiline_comment|/* Command Register bits */
DECL|macro|STOP
mdefine_line|#define STOP&t;1&t;/* In progress jobs finished, software reset */
DECL|macro|STA
mdefine_line|#define STA&t;2&t;/* Activate the NIC */
DECL|macro|TXP
mdefine_line|#define TXP&t;4&t;/* Initiate TX packet */
DECL|macro|RD0
mdefine_line|#define RD0&t;8&t;/* Remote DMA commands */
DECL|macro|RD1
mdefine_line|#define RD1&t;0x10&t;
DECL|macro|RD2
mdefine_line|#define RD2&t;0x20
DECL|macro|PS0
mdefine_line|#define PS0&t;0x40&t;/* Page Select */
DECL|macro|PS1
mdefine_line|#define  PS1&t;0x80&t;/* 00 = 0, 01 = 1, 10 = 2, 11 = reserved */
DECL|macro|PAGE0
mdefine_line|#define PAGE0&t;~(PS0|PS1)&t;/* Remember to AND this */
DECL|macro|PAGE1
mdefine_line|#define PAGE1&t;PS0&t;&t;/* these can be OR&squot;d */
DECL|macro|PAGE2
mdefine_line|#define PAGE2&t;PS1
DECL|macro|NO_DMA
mdefine_line|#define NO_DMA&t;RD2
multiline_comment|/* Interrupt Status Register bits */
DECL|macro|PRX
mdefine_line|#define PRX&t;1&t;/* Packet received with no errors */
DECL|macro|PTX
mdefine_line|#define PTX&t;2&t;/* Packet transmitted with no errors */
DECL|macro|RXE
mdefine_line|#define RXE&t;4&t;/* Packet received with errors */
DECL|macro|TXE
mdefine_line|#define TXE&t;8&t;/* Transmit aborted with errors */
DECL|macro|OVW
mdefine_line|#define OVW&t;0x10&t;/* Overwrite warning */
DECL|macro|CNT
mdefine_line|#define CNT&t;0x20&t;/* Counter overflow warning */
DECL|macro|RDC
mdefine_line|#define RDC&t;0x40&t;/* Remote DMA complete */
DECL|macro|RST
mdefine_line|#define RST&t;0x80&t;/* Reset status - does not cause interrupts */
multiline_comment|/* Interrupt Mask Register - 1 = enabled */
DECL|macro|PRXE
mdefine_line|#define PRXE&t;1&t;/* Packet received */
DECL|macro|PTXE
mdefine_line|#define PTXE&t;2&t;/* Packet transmitted */
DECL|macro|RXEE
mdefine_line|#define RXEE&t;4&t;/* Receive error */
DECL|macro|TXEE
mdefine_line|#define TXEE&t;8&t;/* Transmit error */
DECL|macro|OVWE
mdefine_line|#define OVWE&t;0x10&t;/* Overwrite error */
DECL|macro|CNTE
mdefine_line|#define CNTE&t;0x20&t;/* Counter overflow */
DECL|macro|RDCE
mdefine_line|#define RDCE&t;0x40&t;/* Remote DMA complete */
multiline_comment|/* Data Configuration Register */
DECL|macro|WTS
mdefine_line|#define WTS&t;1&t;/* Word Transfer 0 = byte, 1 = word */
DECL|macro|BOS
mdefine_line|#define BOS&t;2&t;/* Byte Order 0 = 8086, 1 = 68000 */
DECL|macro|LAS
mdefine_line|#define LAS&t;4&t;/* Long Address 0 = 16bit, 1 = 32 bit DMA */
DECL|macro|LS
mdefine_line|#define LS&t;8&t;/* Loopback = 0, 1 = Normal */
DECL|macro|AR
mdefine_line|#define AR&t;0x10&t;/* Autoinitialize = 1 DMA, 0 = software */
DECL|macro|FT0
mdefine_line|#define FT0&t;0x20&t;/* FIFO Threshold (word mode /2 ) */
DECL|macro|FT1
mdefine_line|#define FT1&t;0x40&t;/* 00 = 2, 01 = 4, 10 = 8, 11 = 12 bytes */
multiline_comment|/* Transmit Configuration Register */
DECL|macro|CRCI
mdefine_line|#define CRCI&t;1&t;/* CRC inhibit = 1, append = 0 */
DECL|macro|LB0
mdefine_line|#define LB0&t;2&t;/* Loopback control 00 = normal loopback */
DECL|macro|LB1
mdefine_line|#define LB1&t;4&t;/* 01 = internal, 10 = external1, 11 = external2 */
DECL|macro|ATD
mdefine_line|#define ATD&t;8&t;/* Auto Transmit Enable = 1 tx inhibit enabled */
DECL|macro|OFST
mdefine_line|#define OFST&t;0x10&t;/* Collision offset 1 = modify to low priority mode */
multiline_comment|/* Transmitter Status Register */
DECL|macro|PTXOK
mdefine_line|#define PTXOK&t;1&t;/* Packet transmitted without error */
multiline_comment|/* reserved */
DECL|macro|COL
mdefine_line|#define COL&t;4&t;/* Transmit collided, check NCR for count */
DECL|macro|ABT
mdefine_line|#define ABT&t;8&t;/* Transmit aborted - 16 tries */
DECL|macro|CRS
mdefine_line|#define CRS&t;0x10&t;/* Carrier Sense lost */
DECL|macro|FU
mdefine_line|#define FU&t;0x20&t;/* FIFO underrun */
DECL|macro|CDH
mdefine_line|#define CDH&t;0x40&t;/* CD Heartbeat failed */
DECL|macro|OWC
mdefine_line|#define OWC&t;0x80&t;/* Out of window collision */
multiline_comment|/* Receive configuration Register */
DECL|macro|SEP
mdefine_line|#define SEP&t;1&t;/* Save error packets = 1 */
DECL|macro|ARUNT
mdefine_line|#define ARUNT&t;2&t;/* Accept RUNT packets &lt; 64 bytes */
DECL|macro|AB
mdefine_line|#define AB&t;4&t;/* Accept Broadcast packets */
DECL|macro|AM
mdefine_line|#define AM&t;8&t;/* Accept Multicast packets */
DECL|macro|PRO
mdefine_line|#define PRO&t;0x10&t;/* Promiscuous mode */
DECL|macro|MON
mdefine_line|#define MON&t;0x20&t;/* Monitor mode */
multiline_comment|/* Receive Status Register */
DECL|macro|PRX
mdefine_line|#define PRX&t;1&t;/* Packet received without error */
DECL|macro|CRC
mdefine_line|#define CRC&t;2&t;/* CRC error */
DECL|macro|FAE
mdefine_line|#define FAE&t;4&t;/* Frame Alignment error */
DECL|macro|FO
mdefine_line|#define FO&t;8&t;/* FIFO overrun error */
DECL|macro|MPA
mdefine_line|#define MPA&t;0x10&t;/* Missed packet */
DECL|macro|PHY
mdefine_line|#define PHY&t;0x20&t;/* Physical = 0, Multicast/Broadcast = 1 */
DECL|macro|DIS
mdefine_line|#define DIS&t;0x40&t;/* Receiver disabled (monitor mode) */
DECL|macro|DFR
mdefine_line|#define DFR&t;0x80&t;/* Deferring - jabber on line */
eof
