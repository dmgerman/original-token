multiline_comment|/* myri_sbus.h: Defines for MyriCOM Gigabit Ethernet SBUS card driver.&n; *&n; * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)&n; */
macro_line|#ifndef _MYRI_SBUS_H
DECL|macro|_MYRI_SBUS_H
mdefine_line|#define _MYRI_SBUS_H
DECL|struct|lanai_regs
r_struct
id|lanai_regs
(brace
DECL|member|ipf0
r_volatile
r_int
r_int
id|ipf0
suffix:semicolon
multiline_comment|/* Context zero state registers.*/
DECL|member|cur0
r_volatile
r_int
r_int
id|cur0
suffix:semicolon
DECL|member|prev0
r_volatile
r_int
r_int
id|prev0
suffix:semicolon
DECL|member|data0
r_volatile
r_int
r_int
id|data0
suffix:semicolon
DECL|member|dpf0
r_volatile
r_int
r_int
id|dpf0
suffix:semicolon
DECL|member|ipf1
r_volatile
r_int
r_int
id|ipf1
suffix:semicolon
multiline_comment|/* Context one state registers.&t;*/
DECL|member|cur1
r_volatile
r_int
r_int
id|cur1
suffix:semicolon
DECL|member|prev1
r_volatile
r_int
r_int
id|prev1
suffix:semicolon
DECL|member|data1
r_volatile
r_int
r_int
id|data1
suffix:semicolon
DECL|member|dpf1
r_volatile
r_int
r_int
id|dpf1
suffix:semicolon
DECL|member|istat
r_volatile
r_int
r_int
id|istat
suffix:semicolon
multiline_comment|/* Interrupt status.&t;&t;*/
DECL|member|eimask
r_volatile
r_int
r_int
id|eimask
suffix:semicolon
multiline_comment|/* External IRQ mask.&t;&t;*/
DECL|member|itimer
r_volatile
r_int
r_int
id|itimer
suffix:semicolon
multiline_comment|/* IRQ timer.&t;&t;&t;*/
DECL|member|rtc
r_volatile
r_int
r_int
id|rtc
suffix:semicolon
multiline_comment|/* Real Time Clock&t;&t;*/
DECL|member|csum
r_volatile
r_int
r_int
id|csum
suffix:semicolon
multiline_comment|/* Checksum.&t;&t;&t;*/
DECL|member|dma_xaddr
r_volatile
r_int
r_int
id|dma_xaddr
suffix:semicolon
multiline_comment|/* SBUS DMA external address.&t;*/
DECL|member|dma_laddr
r_volatile
r_int
r_int
id|dma_laddr
suffix:semicolon
multiline_comment|/* SBUS DMA local address.&t;*/
DECL|member|dma_ctr
r_volatile
r_int
r_int
id|dma_ctr
suffix:semicolon
multiline_comment|/* SBUS DMA counter.&t;&t;*/
DECL|member|rx_dmaptr
r_volatile
r_int
r_int
id|rx_dmaptr
suffix:semicolon
multiline_comment|/* Receive DMA pointer.&t;&t;*/
DECL|member|rx_dmalim
r_volatile
r_int
r_int
id|rx_dmalim
suffix:semicolon
multiline_comment|/* Receive DMA limit.&t;&t;*/
DECL|member|tx_dmaptr
r_volatile
r_int
r_int
id|tx_dmaptr
suffix:semicolon
multiline_comment|/* Transmit DMA pointer.&t;*/
DECL|member|tx_dmalim
r_volatile
r_int
r_int
id|tx_dmalim
suffix:semicolon
multiline_comment|/* Transmit DMA limit.&t;&t;*/
DECL|member|tx_dmalimt
r_volatile
r_int
r_int
id|tx_dmalimt
suffix:semicolon
multiline_comment|/* Transmit DMA limit w/tail.&t;*/
DECL|member|_unused0
r_int
r_int
id|_unused0
suffix:semicolon
DECL|member|rbyte
r_volatile
r_int
r_char
id|rbyte
suffix:semicolon
multiline_comment|/* Receive byte.&t;&t;*/
DECL|member|_unused1
r_int
r_char
id|_unused1
(braket
l_int|3
)braket
suffix:semicolon
DECL|member|rhalf
r_volatile
r_int
r_int
id|rhalf
suffix:semicolon
multiline_comment|/* Receive half-word.&t;&t;*/
DECL|member|_unused2
r_int
r_char
id|_unused2
(braket
l_int|2
)braket
suffix:semicolon
DECL|member|rword
r_volatile
r_int
r_int
id|rword
suffix:semicolon
multiline_comment|/* Receive word.&t;&t;*/
DECL|member|salign
r_volatile
r_int
r_int
id|salign
suffix:semicolon
multiline_comment|/* Send align.&t;&t;&t;*/
DECL|member|ss_sendbyte
r_volatile
r_int
r_int
id|ss_sendbyte
suffix:semicolon
multiline_comment|/* SingleSend send-byte.&t;*/
DECL|member|ss_sendhalf
r_volatile
r_int
r_int
id|ss_sendhalf
suffix:semicolon
multiline_comment|/* SingleSend send-halfword.&t;*/
DECL|member|ss_sendword
r_volatile
r_int
r_int
id|ss_sendword
suffix:semicolon
multiline_comment|/* SingleSend send-word.&t;*/
DECL|member|ss_sendt
r_volatile
r_int
r_int
id|ss_sendt
suffix:semicolon
multiline_comment|/* SingleSend special.&t;&t;*/
DECL|member|dma_dir
r_volatile
r_int
r_int
id|dma_dir
suffix:semicolon
multiline_comment|/* DMA direction.&t;&t;*/
DECL|member|dma_stat
r_volatile
r_int
r_int
id|dma_stat
suffix:semicolon
multiline_comment|/* DMA status.&t;&t;&t;*/
DECL|member|timeo
r_volatile
r_int
r_int
id|timeo
suffix:semicolon
multiline_comment|/* Timeout register.&t;&t;*/
DECL|member|myrinet
r_volatile
r_int
r_int
id|myrinet
suffix:semicolon
multiline_comment|/* XXX MAGIC myricom thing&t;*/
DECL|member|hwdebug
r_volatile
r_int
r_int
id|hwdebug
suffix:semicolon
multiline_comment|/* Hardware debugging reg.&t;*/
DECL|member|leds
r_volatile
r_int
r_int
id|leds
suffix:semicolon
multiline_comment|/* LED control.&t;&t;&t;*/
DECL|member|vers
r_volatile
r_int
r_int
id|vers
suffix:semicolon
multiline_comment|/* Version register.&t;&t;*/
DECL|member|link_on
r_volatile
r_int
r_int
id|link_on
suffix:semicolon
multiline_comment|/* Link activation reg.&t;&t;*/
DECL|member|_unused3
r_int
r_int
id|_unused3
(braket
l_int|0x17
)braket
suffix:semicolon
DECL|member|cval
r_volatile
r_int
r_int
id|cval
suffix:semicolon
multiline_comment|/* Clock value register.&t;*/
)brace
suffix:semicolon
multiline_comment|/* Interrupt status bits. */
DECL|macro|ISTAT_DEBUG
mdefine_line|#define ISTAT_DEBUG&t;0x80000000
DECL|macro|ISTAT_HOST
mdefine_line|#define ISTAT_HOST&t;0x40000000
DECL|macro|ISTAT_LAN7
mdefine_line|#define ISTAT_LAN7&t;0x00800000
DECL|macro|ISTAT_LAN6
mdefine_line|#define ISTAT_LAN6&t;0x00400000
DECL|macro|ISTAT_LAN5
mdefine_line|#define ISTAT_LAN5&t;0x00200000
DECL|macro|ISTAT_LAN4
mdefine_line|#define ISTAT_LAN4&t;0x00100000
DECL|macro|ISTAT_LAN3
mdefine_line|#define ISTAT_LAN3&t;0x00080000
DECL|macro|ISTAT_LAN2
mdefine_line|#define ISTAT_LAN2&t;0x00040000
DECL|macro|ISTAT_LAN1
mdefine_line|#define ISTAT_LAN1&t;0x00020000
DECL|macro|ISTAT_LAN0
mdefine_line|#define ISTAT_LAN0&t;0x00010000
DECL|macro|ISTAT_WRDY
mdefine_line|#define ISTAT_WRDY&t;0x00008000
DECL|macro|ISTAT_HRDY
mdefine_line|#define ISTAT_HRDY&t;0x00004000
DECL|macro|ISTAT_SRDY
mdefine_line|#define ISTAT_SRDY&t;0x00002000
DECL|macro|ISTAT_LINK
mdefine_line|#define ISTAT_LINK&t;0x00001000
DECL|macro|ISTAT_FRES
mdefine_line|#define ISTAT_FRES&t;0x00000800
DECL|macro|ISTAT_NRES
mdefine_line|#define ISTAT_NRES&t;0x00000800
DECL|macro|ISTAT_WAKE
mdefine_line|#define ISTAT_WAKE&t;0x00000400
DECL|macro|ISTAT_OB2
mdefine_line|#define ISTAT_OB2&t;0x00000200
DECL|macro|ISTAT_OB1
mdefine_line|#define ISTAT_OB1&t;0x00000100
DECL|macro|ISTAT_TAIL
mdefine_line|#define ISTAT_TAIL&t;0x00000080
DECL|macro|ISTAT_WDOG
mdefine_line|#define ISTAT_WDOG&t;0x00000040
DECL|macro|ISTAT_TIME
mdefine_line|#define ISTAT_TIME&t;0x00000020
DECL|macro|ISTAT_DMA
mdefine_line|#define ISTAT_DMA&t;0x00000010
DECL|macro|ISTAT_SEND
mdefine_line|#define ISTAT_SEND&t;0x00000008
DECL|macro|ISTAT_BUF
mdefine_line|#define ISTAT_BUF&t;0x00000004
DECL|macro|ISTAT_RECV
mdefine_line|#define ISTAT_RECV&t;0x00000002
DECL|macro|ISTAT_BRDY
mdefine_line|#define ISTAT_BRDY&t;0x00000001
DECL|struct|myri_regs
r_struct
id|myri_regs
(brace
DECL|member|reset_off
r_volatile
r_int
r_int
id|reset_off
suffix:semicolon
DECL|member|reset_on
r_volatile
r_int
r_int
id|reset_on
suffix:semicolon
DECL|member|irq_off
r_volatile
r_int
r_int
id|irq_off
suffix:semicolon
DECL|member|irq_on
r_volatile
r_int
r_int
id|irq_on
suffix:semicolon
DECL|member|wakeup_off
r_volatile
r_int
r_int
id|wakeup_off
suffix:semicolon
DECL|member|wakeup_on
r_volatile
r_int
r_int
id|wakeup_on
suffix:semicolon
DECL|member|irq_read
r_volatile
r_int
r_int
id|irq_read
suffix:semicolon
DECL|member|_unused
r_int
r_int
id|_unused
(braket
l_int|0xfff9
)braket
suffix:semicolon
DECL|member|local_mem
r_volatile
r_int
r_int
id|local_mem
(braket
l_int|0x10800
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Shared memory interrupt mask. */
DECL|macro|SHMEM_IMASK_RX
mdefine_line|#define SHMEM_IMASK_RX&t;&t;0x00000002
DECL|macro|SHMEM_IMASK_TX
mdefine_line|#define SHMEM_IMASK_TX&t;&t;0x00000001
multiline_comment|/* Just to make things readable. */
DECL|macro|KERNEL_CHANNEL
mdefine_line|#define KERNEL_CHANNEL&t;&t;0
multiline_comment|/* The size of this must be &gt;= 129 bytes. */
DECL|struct|myri_eeprom
r_struct
id|myri_eeprom
(brace
DECL|member|cval
r_int
r_int
id|cval
suffix:semicolon
DECL|member|cpuvers
r_int
r_int
id|cpuvers
suffix:semicolon
DECL|member|id
r_int
r_char
id|id
(braket
l_int|6
)braket
suffix:semicolon
DECL|member|ramsz
r_int
r_int
id|ramsz
suffix:semicolon
DECL|member|fvers
r_int
r_char
id|fvers
(braket
l_int|32
)braket
suffix:semicolon
DECL|member|mvers
r_int
r_char
id|mvers
(braket
l_int|16
)braket
suffix:semicolon
DECL|member|dlval
r_int
r_int
id|dlval
suffix:semicolon
DECL|member|brd_type
r_int
r_int
id|brd_type
suffix:semicolon
DECL|member|bus_type
r_int
r_int
id|bus_type
suffix:semicolon
DECL|member|prod_code
r_int
r_int
id|prod_code
suffix:semicolon
DECL|member|serial_num
r_int
r_int
id|serial_num
suffix:semicolon
DECL|member|_reserved
r_int
r_int
id|_reserved
(braket
l_int|24
)braket
suffix:semicolon
DECL|member|_unused
r_int
r_int
id|_unused
(braket
l_int|2
)braket
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* EEPROM bus types, only SBUS is valid in this driver. */
DECL|macro|BUS_TYPE_SBUS
mdefine_line|#define BUS_TYPE_SBUS&t;&t;1
multiline_comment|/* EEPROM CPU revisions. */
DECL|macro|CPUVERS_2_3
mdefine_line|#define CPUVERS_2_3&t;&t;0x0203
DECL|macro|CPUVERS_3_0
mdefine_line|#define CPUVERS_3_0&t;&t;0x0300
DECL|macro|CPUVERS_3_1
mdefine_line|#define CPUVERS_3_1&t;&t;0x0301
DECL|macro|CPUVERS_3_2
mdefine_line|#define CPUVERS_3_2&t;&t;0x0302
DECL|macro|CPUVERS_4_0
mdefine_line|#define CPUVERS_4_0&t;&t;0x0400
DECL|macro|CPUVERS_4_1
mdefine_line|#define CPUVERS_4_1&t;&t;0x0401
DECL|macro|CPUVERS_4_2
mdefine_line|#define CPUVERS_4_2&t;&t;0x0402
DECL|macro|CPUVERS_5_0
mdefine_line|#define CPUVERS_5_0&t;&t;0x0500
DECL|struct|myri_control
r_struct
id|myri_control
(brace
DECL|member|ctrl
r_volatile
r_int
r_int
id|ctrl
suffix:semicolon
DECL|member|irqlvl
r_volatile
r_int
r_int
id|irqlvl
suffix:semicolon
)brace
suffix:semicolon
multiline_comment|/* Global control register defines. */
DECL|macro|CONTROL_ROFF
mdefine_line|#define CONTROL_ROFF&t;&t;0x8000&t;/* Reset OFF.&t;&t;*/
DECL|macro|CONTROL_RON
mdefine_line|#define CONTROL_RON&t;&t;0x4000&t;/* Reset ON.&t;&t;*/
DECL|macro|CONTROL_EIRQ
mdefine_line|#define CONTROL_EIRQ&t;&t;0x2000&t;/* Enable IRQ&squot;s.&t;*/
DECL|macro|CONTROL_DIRQ
mdefine_line|#define CONTROL_DIRQ&t;&t;0x1000&t;/* Disable IRQ&squot;s.&t;*/
DECL|macro|CONTROL_WON
mdefine_line|#define CONTROL_WON&t;&t;0x0800&t;/* Wake-up ON.&t;&t;*/
DECL|macro|MYRI_SCATTER_ENTRIES
mdefine_line|#define MYRI_SCATTER_ENTRIES&t;8
DECL|macro|MYRI_GATHER_ENTRIES
mdefine_line|#define MYRI_GATHER_ENTRIES&t;16
DECL|struct|myri_sglist
r_struct
id|myri_sglist
(brace
DECL|member|addr
r_int
r_int
id|addr
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|myri_rxd
r_struct
id|myri_rxd
(brace
DECL|member|myri_scatters
r_struct
id|myri_sglist
id|myri_scatters
(braket
id|MYRI_SCATTER_ENTRIES
)braket
suffix:semicolon
multiline_comment|/* DMA scatter list.*/
DECL|member|csum
r_int
r_int
id|csum
suffix:semicolon
multiline_comment|/* HW computed checksum.    */
DECL|member|ctx
r_int
r_int
id|ctx
suffix:semicolon
DECL|member|num_sg
r_int
r_int
id|num_sg
suffix:semicolon
multiline_comment|/* Total scatter entries.   */
)brace
suffix:semicolon
DECL|struct|myri_txd
r_struct
id|myri_txd
(brace
DECL|member|myri_gathers
r_struct
id|myri_sglist
id|myri_gathers
(braket
id|MYRI_GATHER_ENTRIES
)braket
suffix:semicolon
multiline_comment|/* DMA scatter list.  */
DECL|member|num_sg
r_int
r_int
id|num_sg
suffix:semicolon
multiline_comment|/* Total scatter entries.   */
DECL|member|addr
r_int
r_int
id|addr
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* XXX address              */
DECL|member|chan
r_int
r_int
id|chan
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
multiline_comment|/* Total length of packet.  */
DECL|member|csum_off
r_int
r_int
id|csum_off
suffix:semicolon
multiline_comment|/* Where data to csum is.   */
DECL|member|csum_field
r_int
r_int
id|csum_field
suffix:semicolon
multiline_comment|/* Where csum goes in pkt.  */
)brace
suffix:semicolon
DECL|macro|MYRINET_MTU
mdefine_line|#define MYRINET_MTU        8432
DECL|macro|RX_ALLOC_SIZE
mdefine_line|#define RX_ALLOC_SIZE      8448
DECL|macro|MYRI_PAD_LEN
mdefine_line|#define MYRI_PAD_LEN       2
DECL|macro|RX_COPY_THRESHOLD
mdefine_line|#define RX_COPY_THRESHOLD  128
multiline_comment|/* These numbers are cast in stone, new firmware is needed if&n; * you want to change them.&n; */
DECL|macro|TX_RING_MAXSIZE
mdefine_line|#define TX_RING_MAXSIZE    16
DECL|macro|RX_RING_MAXSIZE
mdefine_line|#define RX_RING_MAXSIZE    16
DECL|macro|TX_RING_SIZE
mdefine_line|#define TX_RING_SIZE       16
DECL|macro|RX_RING_SIZE
mdefine_line|#define RX_RING_SIZE       16
multiline_comment|/* GRRR... */
DECL|function|NEXT_RX
r_static
id|__inline__
r_int
id|NEXT_RX
c_func
(paren
r_int
id|num
)paren
(brace
r_if
c_cond
(paren
op_increment
id|num
OG
id|RX_RING_SIZE
)paren
(brace
id|num
op_assign
l_int|0
suffix:semicolon
)brace
r_return
id|num
suffix:semicolon
)brace
DECL|function|PREV_RX
r_static
id|__inline__
r_int
id|PREV_RX
c_func
(paren
r_int
id|num
)paren
(brace
r_if
c_cond
(paren
op_decrement
id|num
OL
l_int|0
)paren
(brace
id|num
op_assign
id|RX_RING_SIZE
suffix:semicolon
)brace
r_return
id|num
suffix:semicolon
)brace
DECL|macro|NEXT_TX
mdefine_line|#define NEXT_TX(num)&t;(((num) + 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|PREV_TX
mdefine_line|#define PREV_TX(num)&t;(((num) - 1) &amp; (TX_RING_SIZE - 1))
DECL|macro|TX_BUFFS_AVAIL
mdefine_line|#define TX_BUFFS_AVAIL(head, tail)&t;&t;&bslash;&n;&t;((head) &lt;= (tail) ?&t;&t;&t;&bslash;&n;&t; (head) + (TX_RING_SIZE - 1) - (tail) :&t;&bslash;&n;&t; (head) - (tail) - 1)
DECL|struct|sendq
r_struct
id|sendq
(brace
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|hdebug
r_int
r_int
id|hdebug
suffix:semicolon
DECL|member|mdebug
r_int
r_int
id|mdebug
suffix:semicolon
DECL|member|myri_txd
r_struct
id|myri_txd
id|myri_txd
(braket
id|TX_RING_MAXSIZE
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|recvq
r_struct
id|recvq
(brace
DECL|member|head
r_int
r_int
id|head
suffix:semicolon
DECL|member|tail
r_int
r_int
id|tail
suffix:semicolon
DECL|member|hdebug
r_int
r_int
id|hdebug
suffix:semicolon
DECL|member|mdebug
r_int
r_int
id|mdebug
suffix:semicolon
DECL|member|myri_rxd
r_struct
id|myri_rxd
id|myri_rxd
(braket
id|RX_RING_MAXSIZE
op_plus
l_int|1
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|macro|MYRI_MLIST_SIZE
mdefine_line|#define MYRI_MLIST_SIZE 8
DECL|struct|mclist
r_struct
id|mclist
(brace
DECL|member|maxlen
r_int
r_int
id|maxlen
suffix:semicolon
DECL|member|len
r_int
r_int
id|len
suffix:semicolon
DECL|member|cache
r_int
r_int
id|cache
suffix:semicolon
DECL|struct|pair
r_struct
id|pair
(brace
DECL|member|addr
r_int
r_char
id|addr
(braket
l_int|8
)braket
suffix:semicolon
DECL|member|val
r_int
r_int
id|val
suffix:semicolon
DECL|member|mc_pairs
)brace
id|mc_pairs
(braket
id|MYRI_MLIST_SIZE
)braket
suffix:semicolon
DECL|member|bcast_addr
r_int
r_char
id|bcast_addr
(braket
l_int|8
)braket
suffix:semicolon
)brace
suffix:semicolon
DECL|struct|myri_channel
r_struct
id|myri_channel
(brace
DECL|member|state
r_int
r_int
id|state
suffix:semicolon
multiline_comment|/* State of the channel.&t;*/
DECL|member|busy
r_int
r_int
id|busy
suffix:semicolon
multiline_comment|/* Channel is busy.&t;&t;*/
DECL|member|sendq
r_struct
id|sendq
id|sendq
suffix:semicolon
multiline_comment|/* Device tx queue.&t;&t;*/
DECL|member|recvq
r_struct
id|recvq
id|recvq
suffix:semicolon
multiline_comment|/* Device rx queue.&t;&t;*/
DECL|member|recvqa
r_struct
id|recvq
id|recvqa
suffix:semicolon
multiline_comment|/* Device rx queue acked.&t;*/
DECL|member|rbytes
r_int
r_int
id|rbytes
suffix:semicolon
multiline_comment|/* Receive bytes.&t;&t;*/
DECL|member|sbytes
r_int
r_int
id|sbytes
suffix:semicolon
multiline_comment|/* Send bytes.&t;&t;&t;*/
DECL|member|rmsgs
r_int
r_int
id|rmsgs
suffix:semicolon
multiline_comment|/* Receive messages.&t;&t;*/
DECL|member|smsgs
r_int
r_int
id|smsgs
suffix:semicolon
multiline_comment|/* Send messages.&t;&t;*/
DECL|member|mclist
r_struct
id|mclist
id|mclist
suffix:semicolon
multiline_comment|/* Device multicast list.&t;*/
)brace
suffix:semicolon
multiline_comment|/* Values for per-channel state. */
DECL|macro|STATE_WFH
mdefine_line|#define STATE_WFH&t;0&t;&t;/* Waiting for HOST.&t;&t;*/
DECL|macro|STATE_WFN
mdefine_line|#define STATE_WFN&t;1&t;&t;/* Waiting for NET.&t;&t;*/
DECL|macro|STATE_READY
mdefine_line|#define STATE_READY&t;2&t;&t;/* Ready.&t;&t;&t;*/
DECL|struct|myri_shmem
r_struct
id|myri_shmem
(brace
DECL|member|addr
r_int
r_char
id|addr
(braket
l_int|8
)braket
suffix:semicolon
multiline_comment|/* Board&squot;s address.&t;&t;*/
DECL|member|nchan
r_int
r_int
id|nchan
suffix:semicolon
multiline_comment|/* Number of channels.&t;&t;*/
DECL|member|burst
r_int
r_int
id|burst
suffix:semicolon
multiline_comment|/* SBUS dma burst enable.&t;*/
DECL|member|shakedown
r_int
r_int
id|shakedown
suffix:semicolon
multiline_comment|/* DarkkkkStarrr Crashesss...&t;*/
DECL|member|send
r_int
r_int
id|send
suffix:semicolon
multiline_comment|/* Send wanted.&t;&t;&t;*/
DECL|member|imask
r_int
r_int
id|imask
suffix:semicolon
multiline_comment|/* Interrupt enable mask.&t;*/
DECL|member|mlevel
r_int
r_int
id|mlevel
suffix:semicolon
multiline_comment|/* Map level.&t;&t;&t;*/
DECL|member|debug
r_int
r_int
id|debug
(braket
l_int|4
)braket
suffix:semicolon
multiline_comment|/* Misc. debug areas.&t;&t;*/
DECL|member|channel
r_struct
id|myri_channel
id|channel
suffix:semicolon
multiline_comment|/* Only one channel on a host.&t;*/
)brace
suffix:semicolon
DECL|struct|myri_eth
r_struct
id|myri_eth
(brace
multiline_comment|/* These are frequently accessed, keep together&n;&t; * to obtain good cache hit rates.&n;&t; */
DECL|member|shmem
r_struct
id|myri_shmem
op_star
id|shmem
suffix:semicolon
multiline_comment|/* Shared data structures.    */
DECL|member|cregs
r_struct
id|myri_control
op_star
id|cregs
suffix:semicolon
multiline_comment|/* Control register space.    */
DECL|member|rqack
r_struct
id|recvq
op_star
id|rqack
suffix:semicolon
multiline_comment|/* Where we ack rx&squot;s.         */
DECL|member|rq
r_struct
id|recvq
op_star
id|rq
suffix:semicolon
multiline_comment|/* Where we put buffers.      */
DECL|member|sq
r_struct
id|sendq
op_star
id|sq
suffix:semicolon
multiline_comment|/* Where we stuff tx&squot;s.       */
DECL|member|dev
r_struct
id|device
op_star
id|dev
suffix:semicolon
multiline_comment|/* Linux/NET dev struct.      */
DECL|member|tx_old
r_int
id|tx_old
suffix:semicolon
multiline_comment|/* To speed up tx cleaning.   */
DECL|member|lregs
r_struct
id|lanai_regs
op_star
id|lregs
suffix:semicolon
multiline_comment|/* Quick ptr to LANAI regs.   */
DECL|member|rx_skbs
r_struct
id|sk_buff
op_star
id|rx_skbs
(braket
id|RX_RING_SIZE
op_plus
l_int|1
)braket
suffix:semicolon
multiline_comment|/* RX skb&squot;s                   */
DECL|member|tx_skbs
r_struct
id|sk_buff
op_star
id|tx_skbs
(braket
id|TX_RING_SIZE
)braket
suffix:semicolon
multiline_comment|/* TX skb&squot;s                   */
DECL|member|enet_stats
r_struct
id|enet_statistics
id|enet_stats
suffix:semicolon
multiline_comment|/* Interface stats.           */
multiline_comment|/* These are less frequently accessed. */
DECL|member|regs
r_struct
id|myri_regs
op_star
id|regs
suffix:semicolon
multiline_comment|/* MyriCOM register space.    */
DECL|member|lanai
r_int
r_int
op_star
id|lanai
suffix:semicolon
multiline_comment|/* View 2 of register space.  */
DECL|member|lanai3
r_int
r_int
op_star
id|lanai3
suffix:semicolon
multiline_comment|/* View 3 of register space.  */
DECL|member|myri_bursts
r_int
r_int
id|myri_bursts
suffix:semicolon
multiline_comment|/* SBUS bursts.               */
DECL|member|eeprom
r_struct
id|myri_eeprom
id|eeprom
suffix:semicolon
multiline_comment|/* Local copy of EEPROM.      */
DECL|member|reg_size
r_int
r_int
id|reg_size
suffix:semicolon
multiline_comment|/* Size of register space.    */
DECL|member|shmem_base
r_int
r_int
id|shmem_base
suffix:semicolon
multiline_comment|/* Offset to shared ram.      */
DECL|member|myri_sbus_dev
r_struct
id|linux_sbus_device
op_star
id|myri_sbus_dev
suffix:semicolon
multiline_comment|/* Our SBUS device struct.    */
DECL|member|next_module
r_struct
id|myri_eth
op_star
id|next_module
suffix:semicolon
multiline_comment|/* Next in adapter chain.     */
)brace
suffix:semicolon
multiline_comment|/* We use this to acquire receive skb&squot;s that we can DMA directly into. */
DECL|macro|ALIGNED_RX_SKB_ADDR
mdefine_line|#define ALIGNED_RX_SKB_ADDR(addr) &bslash;&n;        ((((unsigned long)(addr) + (64 - 1)) &amp; ~(64 - 1)) - (unsigned long)(addr))
DECL|function|myri_alloc_skb
r_static
r_inline
r_struct
id|sk_buff
op_star
id|myri_alloc_skb
c_func
(paren
r_int
r_int
id|length
comma
r_int
id|gfp_flags
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|length
op_plus
l_int|64
comma
id|gfp_flags
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
)paren
(brace
r_int
id|offset
op_assign
id|ALIGNED_RX_SKB_ADDR
c_func
(paren
id|skb-&gt;data
)paren
suffix:semicolon
r_if
c_cond
(paren
id|offset
)paren
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
id|offset
)paren
suffix:semicolon
)brace
)brace
r_return
id|skb
suffix:semicolon
)brace
macro_line|#endif /* !(_MYRI_SBUS_H) */
eof
