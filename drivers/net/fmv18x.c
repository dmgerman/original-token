multiline_comment|/* fmv18x.c: A network device driver for the Fujitsu FMV-181/182/183/184.&n;&n;&t;Original: at1700.c (1993-94 by Donald Becker).&n;&t;&t;Copyright 1993 United States Government as represented by the&n;&t;&t;Director, National Security Agency.&n;&t;&t;The author may be reached as becker@CESDIS.gsfc.nasa.gov, or C/O&n;&t;&t;Center of Excellence in Space Data and Information Sciences&n;&t;&t;   Code 930.5, Goddard Space Flight Center, Greenbelt MD 20771&n;&n;&t;Modified by Yutaka TAMIYA (tamy@flab.fujitsu.co.jp)&n;&t;&t;Copyright 1994 Fujitsu Laboratories Ltd.&n;&t;Special thanks to:&n;&t;&t;Masayoshi UTAKA (utaka@ace.yk.fujitsu.co.jp)&n;&t;&t;&t;for testing this driver.&n;&t;&t;H. NEGISHI (agy, negishi@sun45.psd.cs.fujitsu.co.jp)&n;&t;&t;&t;for suggestion of some program modification.&n;&t;&t;Masahiro SEKIGUCHI &lt;seki@sysrap.cs.fujitsu.co.jp&gt;&n;&t;&t;&t;for suggestion of some program modification.&n;&t;&t;Kazutoshi MORIOKA (morioka@aurora.oaks.cs.fujitsu.co.jp)&n;&t;&t;&t;for testing this driver.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU Public License, incorporated herein by reference.&n;&n;&t;This is a device driver for the Fujitsu FMV-181/182/183/184, which&n;&t;is a straight-forward Fujitsu MB86965 implementation.&n;&n;  Sources:&n;    at1700.c&n;    The Fujitsu MB86965 datasheet.&n;    The Fujitsu FMV-181/182 user&squot;s guide&n;*/
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;fmv18x.c:v2.2.0 09/24/98  Yutaka TAMIYA (tamy@flab.fujitsu.co.jp)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
DECL|variable|__initdata
r_static
r_int
id|fmv18x_probe_list
(braket
)braket
id|__initdata
op_assign
(brace
l_int|0x220
comma
l_int|0x240
comma
l_int|0x260
comma
l_int|0x280
comma
l_int|0x2a0
comma
l_int|0x2c0
comma
l_int|0x300
comma
l_int|0x340
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG 1
macro_line|#endif
DECL|variable|net_debug
r_static
r_int
r_int
id|net_debug
op_assign
id|NET_DEBUG
suffix:semicolon
DECL|typedef|uchar
r_typedef
r_int
r_char
id|uchar
suffix:semicolon
multiline_comment|/* Information that need to be kept for each board. */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|stats
r_struct
id|net_device_stats
id|stats
suffix:semicolon
DECL|member|open_time
r_int
id|open_time
suffix:semicolon
multiline_comment|/* Useless example local info. */
DECL|member|tx_started
id|uint
id|tx_started
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Number of packet on the Tx queue. */
DECL|member|tx_queue_ready
id|uint
id|tx_queue_ready
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Tx queue is ready to be sent. */
DECL|member|rx_started
id|uint
id|rx_started
suffix:colon
l_int|1
suffix:semicolon
multiline_comment|/* Packets are Rxing. */
DECL|member|tx_queue
id|uchar
id|tx_queue
suffix:semicolon
multiline_comment|/* Number of packet on the Tx queue. */
DECL|member|tx_queue_len
id|ushort
id|tx_queue_len
suffix:semicolon
multiline_comment|/* Current length of the Tx queue. */
)brace
suffix:semicolon
multiline_comment|/* Offsets from the base address. */
DECL|macro|STATUS
mdefine_line|#define STATUS&t;&t;&t;0
DECL|macro|TX_STATUS
mdefine_line|#define TX_STATUS&t;&t;0
DECL|macro|RX_STATUS
mdefine_line|#define RX_STATUS&t;&t;1
DECL|macro|TX_INTR
mdefine_line|#define TX_INTR&t;&t;&t;2&t;&t;/* Bit-mapped interrupt enable registers. */
DECL|macro|RX_INTR
mdefine_line|#define RX_INTR&t;&t;&t;3
DECL|macro|TX_MODE
mdefine_line|#define TX_MODE&t;&t;&t;4
DECL|macro|RX_MODE
mdefine_line|#define RX_MODE&t;&t;&t;5
DECL|macro|CONFIG_0
mdefine_line|#define CONFIG_0&t;&t;6&t;&t;/* Misc. configuration settings. */
DECL|macro|CONFIG_1
mdefine_line|#define CONFIG_1&t;&t;7
multiline_comment|/* Run-time register bank 2 definitions. */
DECL|macro|DATAPORT
mdefine_line|#define DATAPORT&t;&t;8&t;&t;/* Word-wide DMA or programmed-I/O dataport. */
DECL|macro|TX_START
mdefine_line|#define TX_START&t;&t;10
DECL|macro|COL16CNTL
mdefine_line|#define COL16CNTL&t;&t;11&t;&t;/* Controll Reg for 16 collisions */
DECL|macro|MODE13
mdefine_line|#define MODE13&t;&t;&t;13
multiline_comment|/* Fujitsu FMV-18x Card Configuration */
DECL|macro|FJ_STATUS0
mdefine_line|#define&t;FJ_STATUS0&t;&t;0x10
DECL|macro|FJ_STATUS1
mdefine_line|#define&t;FJ_STATUS1&t;&t;0x11
DECL|macro|FJ_CONFIG0
mdefine_line|#define&t;FJ_CONFIG0&t;&t;0x12
DECL|macro|FJ_CONFIG1
mdefine_line|#define&t;FJ_CONFIG1&t;&t;0x13
DECL|macro|FJ_MACADDR
mdefine_line|#define&t;FJ_MACADDR&t;&t;0x14&t;/* 0x14 - 0x19 */
DECL|macro|FJ_BUFCNTL
mdefine_line|#define&t;FJ_BUFCNTL&t;&t;0x1A
DECL|macro|FJ_BUFDATA
mdefine_line|#define&t;FJ_BUFDATA&t;&t;0x1C
DECL|macro|FMV18X_IO_EXTENT
mdefine_line|#define FMV18X_IO_EXTENT&t;32
multiline_comment|/* Index to functions, as function prototypes. */
r_extern
r_int
id|fmv18x_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|fmv18x_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
suffix:semicolon
r_static
r_int
id|net_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|net_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|net_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|net_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|net_timeout
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|net_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|net_device_stats
op_star
id|net_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
multiline_comment|/* Check for a network adaptor of this type, and return &squot;0&squot; iff one exists.&n;   If dev-&gt;base_addr == 0, probe all likely locations.&n;   If dev-&gt;base_addr == 1, always return failure.&n;   If dev-&gt;base_addr == 2, allocate space for the device and return success&n;   (detachable devices only).&n;   */
DECL|function|fmv18x_probe
r_int
id|__init
id|fmv18x_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
id|base_addr
op_assign
id|dev
ques
c_cond
id|dev-&gt;base_addr
suffix:colon
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|base_addr
OG
l_int|0x1ff
)paren
multiline_comment|/* Check a single specified location. */
r_return
id|fmv18x_probe1
c_func
(paren
id|dev
comma
id|base_addr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|base_addr
op_ne
l_int|0
)paren
multiline_comment|/* Don&squot;t probe at all. */
r_return
id|ENXIO
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|fmv18x_probe_list
(braket
id|i
)braket
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|ioaddr
op_assign
id|fmv18x_probe_list
(braket
id|i
)braket
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ioaddr
comma
id|FMV18X_IO_EXTENT
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|fmv18x_probe1
c_func
(paren
id|dev
comma
id|ioaddr
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* The Fujitsu datasheet suggests that the NIC be probed for by checking its&n;   &quot;signature&quot;, the default bit pattern after a reset.  This *doesn&squot;t* work --&n;   there is no way to reset the bus interface without a complete power-cycle!&n;&n;   It turns out that ATI came to the same conclusion I did: the only thing&n;   that can be done is checking a few bits and then diving right into MAC&n;   address check. */
DECL|function|fmv18x_probe1
r_int
id|__init
id|fmv18x_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
(brace
r_char
id|irqmap
(braket
l_int|4
)braket
op_assign
(brace
l_int|3
comma
l_int|7
comma
l_int|10
comma
l_int|15
)brace
suffix:semicolon
r_char
id|irqmap_pnp
(braket
l_int|8
)braket
op_assign
(brace
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|7
comma
l_int|9
comma
l_int|10
comma
l_int|11
comma
l_int|15
)brace
suffix:semicolon
r_int
r_int
id|i
comma
id|irq
suffix:semicolon
multiline_comment|/* Resetting the chip doesn&squot;t reset the ISA interface, so don&squot;t bother.&n;&t;   That means we have to be careful with the register values we probe for.&n;&t;   */
multiline_comment|/* Check I/O address configuration and Fujitsu vendor code */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|FJ_MACADDR
)paren
op_ne
l_int|0x00
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|FJ_MACADDR
op_plus
l_int|1
)paren
op_ne
l_int|0x00
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|FJ_MACADDR
op_plus
l_int|2
)paren
op_ne
l_int|0x0e
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
multiline_comment|/* Check PnP mode for FMV-183/184/183A/184A. */
multiline_comment|/* This PnP routine is very poor. IO and IRQ should be known. */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|FJ_STATUS1
)paren
op_amp
l_int|0x20
)paren
(brace
id|irq
op_assign
id|dev-&gt;irq
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|irq
op_eq
id|irqmap_pnp
(braket
id|i
)braket
)paren
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_eq
l_int|8
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_else
(brace
r_if
c_cond
(paren
id|fmv18x_probe_list
(braket
id|inb
c_func
(paren
id|ioaddr
op_plus
id|FJ_CONFIG0
)paren
op_amp
l_int|0x07
)braket
op_ne
id|ioaddr
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
id|irq
op_assign
id|irqmap
(braket
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|FJ_CONFIG0
)paren
op_rshift
l_int|6
)paren
op_amp
l_int|0x03
)braket
suffix:semicolon
)brace
multiline_comment|/* Snarf the interrupt vector now. */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|irq
comma
op_amp
id|net_interrupt
comma
l_int|0
comma
l_string|&quot;fmv18x&quot;
comma
id|dev
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;FMV-18x found at %#3x, but it&squot;s unusable due to a conflict on&quot;
l_string|&quot;IRQ %d.&bslash;n&quot;
comma
id|ioaddr
comma
id|irq
)paren
suffix:semicolon
r_return
id|EAGAIN
suffix:semicolon
)brace
multiline_comment|/* Allocate a new &squot;dev&squot; if needed. */
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
id|dev
op_assign
id|init_etherdev
c_func
(paren
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_local
)paren
)paren
suffix:semicolon
multiline_comment|/* Grab the region so that we can find another board if the IRQ request&n;&t;   fails. */
id|request_region
c_func
(paren
id|ioaddr
comma
id|FMV18X_IO_EXTENT
comma
l_string|&quot;fmv18x&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: FMV-18x found at %#3x, IRQ %d, address &quot;
comma
id|dev-&gt;name
comma
id|ioaddr
comma
id|irq
)paren
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
r_char
id|val
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|FJ_MACADDR
op_plus
id|i
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%02x&quot;
comma
id|val
)paren
suffix:semicolon
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|val
suffix:semicolon
)brace
multiline_comment|/* &quot;FJ_STATUS0&quot; 12 bit 0x0400 means use regular 100 ohm 10baseT signals,&n;&t;   rather than 150 ohm shielded twisted pair compensation.&n;&t;   0x0000 == auto-sense the interface&n;&t;   0x0800 == use TP interface&n;&t;   0x1800 == use coax interface&n;&t;   */
(brace
r_const
r_char
op_star
id|porttype
(braket
)braket
op_assign
(brace
l_string|&quot;auto-sense&quot;
comma
l_string|&quot;10baseT&quot;
comma
l_string|&quot;auto-sense&quot;
comma
l_string|&quot;10base2/5&quot;
)brace
suffix:semicolon
id|ushort
id|setup_value
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|FJ_STATUS0
)paren
suffix:semicolon
r_switch
c_cond
(paren
id|setup_value
op_amp
l_int|0x07
)paren
(brace
r_case
l_int|0x01
multiline_comment|/* 10base5 */
suffix:colon
r_case
l_int|0x02
multiline_comment|/* 10base2 */
suffix:colon
id|dev-&gt;if_port
op_assign
l_int|0x18
suffix:semicolon
r_break
suffix:semicolon
r_case
l_int|0x04
multiline_comment|/* 10baseT */
suffix:colon
id|dev-&gt;if_port
op_assign
l_int|0x08
suffix:semicolon
r_break
suffix:semicolon
r_default
multiline_comment|/* auto-sense*/
suffix:colon
id|dev-&gt;if_port
op_assign
l_int|0x00
suffix:semicolon
r_break
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; %s interface.&bslash;n&quot;
comma
id|porttype
(braket
(paren
id|dev-&gt;if_port
op_rshift
l_int|3
)paren
op_amp
l_int|3
)braket
)paren
suffix:semicolon
)brace
multiline_comment|/* Initialize LAN Controller and LAN Card */
id|outb
c_func
(paren
l_int|0xda
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
multiline_comment|/* Initialize LAN Controller */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
multiline_comment|/* Stand by mode */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|FJ_CONFIG1
)paren
suffix:semicolon
multiline_comment|/* Disable IRQ of LAN Card */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|FJ_BUFCNTL
)paren
suffix:semicolon
multiline_comment|/* Reset ? I&squot;m not sure (TAMIYA) */
multiline_comment|/* wait for a while */
id|udelay
c_func
(paren
l_int|200
)paren
suffix:semicolon
multiline_comment|/* Set the station address in bank zero. */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|outb
c_func
(paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
comma
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* Switch to bank 1 and set the multicast table to accept none. */
id|outb
c_func
(paren
l_int|0x04
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|8
suffix:semicolon
id|i
op_increment
)paren
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
multiline_comment|/* Switch to bank 2 and lock our I/O address. */
id|outb
c_func
(paren
l_int|0x08
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
id|outb
c_func
(paren
id|dev-&gt;if_port
comma
id|ioaddr
op_plus
id|MODE13
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|COL16CNTL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
)paren
id|printk
c_func
(paren
id|version
)paren
suffix:semicolon
multiline_comment|/* Initialize the device structure. */
id|dev-&gt;priv
op_assign
id|kmalloc
c_func
(paren
r_sizeof
(paren
r_struct
id|net_local
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;priv
op_eq
l_int|NULL
)paren
r_return
op_minus
id|ENOMEM
suffix:semicolon
id|memset
c_func
(paren
id|dev-&gt;priv
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|net_local
)paren
)paren
suffix:semicolon
id|dev-&gt;open
op_assign
id|net_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|net_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|net_send_packet
suffix:semicolon
id|dev-&gt;tx_timeout
op_assign
id|net_timeout
suffix:semicolon
id|dev-&gt;watchdog_timeo
op_assign
id|HZ
op_div
l_int|10
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|net_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
id|set_multicast_list
suffix:semicolon
multiline_comment|/* Fill in the fields of &squot;dev&squot; with ethernet-generic values. */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
DECL|function|net_open
r_static
r_int
id|net_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* Set the configuration register 0 to 32K 100ns. byte-wide memory,&n;&t;   16 bit bus access, and two 4K Tx, enable the Rx and Tx. */
id|outb
c_func
(paren
l_int|0x5a
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
multiline_comment|/* Powerup and switch to register bank 2 for the run-time registers. */
id|outb
c_func
(paren
l_int|0xe8
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
id|lp-&gt;tx_started
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tx_queue_ready
op_assign
l_int|1
suffix:semicolon
id|lp-&gt;rx_started
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tx_queue
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Clear Tx and Rx Status */
id|outb
c_func
(paren
l_int|0xff
comma
id|ioaddr
op_plus
id|TX_STATUS
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
id|ioaddr
op_plus
id|RX_STATUS
)paren
suffix:semicolon
id|lp-&gt;open_time
op_assign
id|jiffies
suffix:semicolon
id|netif_start_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Enable the IRQ of the LAN Card */
id|outb
c_func
(paren
l_int|0x80
comma
id|ioaddr
op_plus
id|FJ_CONFIG1
)paren
suffix:semicolon
multiline_comment|/* Enable both Tx and Rx interrupts */
id|outw
c_func
(paren
l_int|0x8182
comma
id|ioaddr
op_plus
id|TX_INTR
)paren
suffix:semicolon
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|net_timeout
r_static
r_void
id|net_timeout
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
r_int
id|flags
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: transmit timed out with status %04x, %s?&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
id|TX_STATUS
)paren
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|TX_STATUS
)paren
op_amp
l_int|0x80
ques
c_cond
l_string|&quot;IRQ conflict&quot;
suffix:colon
l_string|&quot;network cable problem&quot;
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;%s: timeout registers: %04x %04x %04x %04x %04x %04x %04x %04x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|0
)paren
)paren
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|2
)paren
)paren
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|4
)paren
)paren
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|6
)paren
)paren
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|8
)paren
)paren
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|10
)paren
)paren
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|12
)paren
)paren
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|14
)paren
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;eth card: %04x %04x&bslash;n&quot;
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
id|FJ_STATUS0
)paren
)paren
comma
id|htons
c_func
(paren
id|inw
c_func
(paren
id|ioaddr
op_plus
id|FJ_CONFIG0
)paren
)paren
)paren
suffix:semicolon
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
multiline_comment|/* ToDo: We should try to restart the adaptor... */
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Initialize LAN Controller and LAN Card */
id|outb
c_func
(paren
l_int|0xda
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
multiline_comment|/* Initialize LAN Controller */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
multiline_comment|/* Stand by mode */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|FJ_CONFIG1
)paren
suffix:semicolon
multiline_comment|/* Disable IRQ of LAN Card */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|FJ_BUFCNTL
)paren
suffix:semicolon
multiline_comment|/* Reset ? I&squot;m not sure */
id|net_open
c_func
(paren
id|dev
)paren
suffix:semicolon
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
)brace
DECL|function|net_send_packet
r_static
r_int
id|net_send_packet
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|length
op_assign
id|ETH_ZLEN
OL
id|skb-&gt;len
ques
c_cond
id|skb-&gt;len
suffix:colon
id|ETH_ZLEN
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* Block a transmit from overlapping.  */
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|length
OG
id|ETH_FRAME_LEN
)paren
(brace
r_if
c_cond
(paren
id|net_debug
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Attempting to send a large packet (%d bytes).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|length
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|net_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Transmitting a packet of length %lu.&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
r_int
r_int
)paren
id|skb-&gt;len
)paren
suffix:semicolon
multiline_comment|/* We may not start transmitting unless we finish transferring&n;&t;   a packet into the Tx queue. During executing the following&n;&t;   codes we possibly catch a Tx interrupt. Thus we flag off&n;&t;   tx_queue_ready, so that we prevent the interrupt routine&n;&t;   (net_interrupt) to start transmitting. */
id|lp-&gt;tx_queue_ready
op_assign
l_int|0
suffix:semicolon
(brace
id|outw
c_func
(paren
id|length
comma
id|ioaddr
op_plus
id|DATAPORT
)paren
suffix:semicolon
id|outsw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
comma
id|buf
comma
(paren
id|length
op_plus
l_int|1
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
id|lp-&gt;tx_queue
op_increment
suffix:semicolon
id|lp-&gt;tx_queue_len
op_add_assign
id|length
op_plus
l_int|2
suffix:semicolon
)brace
id|lp-&gt;tx_queue_ready
op_assign
l_int|1
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;tx_started
op_eq
l_int|0
)paren
(brace
multiline_comment|/* If the Tx is idle, always trigger a transmit. */
id|outb
c_func
(paren
l_int|0x80
op_or
id|lp-&gt;tx_queue
comma
id|ioaddr
op_plus
id|TX_START
)paren
suffix:semicolon
id|lp-&gt;tx_queue
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|lp-&gt;tx_started
op_assign
l_int|1
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|lp-&gt;tx_queue_len
OL
l_int|4096
op_minus
l_int|1502
)paren
multiline_comment|/* Yes, there is room for one more packet. */
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev_kfree_skb
c_func
(paren
id|skb
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/* The typical workload of the driver:&n;   Handle the network interface interrupts. */
r_static
r_void
DECL|function|net_interrupt
id|net_interrupt
c_func
(paren
r_int
id|irq
comma
r_void
op_star
id|dev_id
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
id|dev_id
suffix:semicolon
r_struct
id|net_local
op_star
id|lp
suffix:semicolon
r_int
id|ioaddr
comma
id|status
suffix:semicolon
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|status
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|TX_STATUS
)paren
suffix:semicolon
id|outw
c_func
(paren
id|status
comma
id|ioaddr
op_plus
id|TX_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Interrupt with status %04x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|status
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;rx_started
op_eq
l_int|0
op_logical_and
(paren
id|status
op_amp
l_int|0xff00
op_logical_or
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
)paren
(brace
multiline_comment|/* Got a packet(s).&n;&t;&t;   We cannot execute net_rx more than once at the same time for&n;&t;&t;   the same device. During executing net_rx, we possibly catch a&n;&t;&t;   Tx interrupt. Thus we flag on rx_started, so that we prevent&n;&t;&t;   the interrupt routine (net_interrupt) to dive into net_rx&n;&t;&t;   again. */
id|lp-&gt;rx_started
op_assign
l_int|1
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|RX_INTR
)paren
suffix:semicolon
multiline_comment|/* Disable RX intr. */
id|net_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x81
comma
id|ioaddr
op_plus
id|RX_INTR
)paren
suffix:semicolon
multiline_comment|/* Enable  RX intr. */
id|lp-&gt;rx_started
op_assign
l_int|0
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x00ff
)paren
(brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x02
)paren
(brace
multiline_comment|/* More than 16 collisions occurred */
r_if
c_cond
(paren
id|net_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: 16 Collision occur during Txing.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Cancel sending a packet. */
id|outb
c_func
(paren
l_int|0x03
comma
id|ioaddr
op_plus
id|COL16CNTL
)paren
suffix:semicolon
id|lp-&gt;stats.collisions
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
op_amp
l_int|0x82
)paren
(brace
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;tx_queue
op_logical_and
id|lp-&gt;tx_queue_ready
)paren
(brace
id|outb
c_func
(paren
l_int|0x80
op_or
id|lp-&gt;tx_queue
comma
id|ioaddr
op_plus
id|TX_START
)paren
suffix:semicolon
id|lp-&gt;tx_queue
op_assign
l_int|0
suffix:semicolon
id|lp-&gt;tx_queue_len
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Inform upper layers. */
)brace
r_else
(brace
id|lp-&gt;tx_started
op_assign
l_int|0
suffix:semicolon
id|netif_wake_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Inform upper layers. */
)brace
)brace
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* We have a good packet(s), get it/them out of the buffers. */
DECL|function|net_rx
r_static
r_void
id|net_rx
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
id|boguscount
op_assign
l_int|5
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/* Clear PKT_RDY bit: by agy 19940922 */
multiline_comment|/* outb(0x80, ioaddr + RX_STATUS); */
id|ushort
id|status
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Rxing packet mode %02x status %04x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
comma
id|status
)paren
suffix:semicolon
macro_line|#ifndef final_version
r_if
c_cond
(paren
id|status
op_eq
l_int|0
)paren
(brace
id|outb
c_func
(paren
l_int|0x05
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
macro_line|#endif
r_if
c_cond
(paren
(paren
id|status
op_amp
l_int|0xF0
)paren
op_ne
l_int|0x20
)paren
(brace
multiline_comment|/* There was an error. */
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x08
)paren
id|lp-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x04
)paren
id|lp-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x02
)paren
id|lp-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x01
)paren
id|lp-&gt;stats.rx_over_errors
op_increment
suffix:semicolon
)brace
r_else
(brace
id|ushort
id|pkt_len
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
)paren
suffix:semicolon
multiline_comment|/* Malloc up new buffer. */
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_if
c_cond
(paren
id|pkt_len
OG
l_int|1550
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: The FMV-18x claimed a very large packet, size %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|pkt_len
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x05
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
id|lp-&gt;stats.rx_errors
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|pkt_len
op_plus
l_int|3
)paren
suffix:semicolon
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Memory squeeze, dropping packet (len %d).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|pkt_len
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x05
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_break
suffix:semicolon
)brace
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
id|insw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
comma
id|skb_put
c_func
(paren
id|skb
comma
id|pkt_len
)paren
comma
(paren
id|pkt_len
op_plus
l_int|1
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
OG
l_int|5
)paren
(brace
r_int
id|i
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Rxed packet of length %d: &quot;
comma
id|dev-&gt;name
comma
id|pkt_len
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|14
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|skb-&gt;data
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
)brace
id|skb-&gt;protocol
op_assign
id|eth_type_trans
c_func
(paren
id|skb
comma
id|dev
)paren
suffix:semicolon
id|netif_rx
c_func
(paren
id|skb
)paren
suffix:semicolon
id|lp-&gt;stats.rx_packets
op_increment
suffix:semicolon
)brace
r_if
c_cond
(paren
op_decrement
id|boguscount
op_le
l_int|0
)paren
r_break
suffix:semicolon
)brace
multiline_comment|/* If any worth-while packets have been received, dev_rint()&n;&t;   has done a mark_bh(NET_BH) for us and will work on them&n;&t;   when we get to the bottom-half routine. */
(brace
r_int
id|i
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|20
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0x40
)paren
r_break
suffix:semicolon
(paren
r_void
)paren
id|inw
c_func
(paren
id|ioaddr
op_plus
id|DATAPORT
)paren
suffix:semicolon
multiline_comment|/* dummy status read */
id|outb
c_func
(paren
l_int|0x05
comma
id|ioaddr
op_plus
l_int|14
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|net_debug
OG
l_int|5
op_logical_and
id|i
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Exint Rx packet with mode %02x after %d ticks.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|RX_MODE
)paren
comma
id|i
)paren
suffix:semicolon
)brace
r_return
suffix:semicolon
)brace
multiline_comment|/* The inverse routine to net_open(). */
DECL|function|net_close
r_static
r_int
id|net_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
(paren
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
)paren
op_member_access_from_pointer
id|open_time
op_assign
l_int|0
suffix:semicolon
id|netif_stop_queue
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Set configuration register 0 to disable Tx and Rx. */
id|outb
c_func
(paren
l_int|0xda
comma
id|ioaddr
op_plus
id|CONFIG_0
)paren
suffix:semicolon
multiline_comment|/* Update the statistics -- ToDo. */
multiline_comment|/* Power-down the chip.  Green, green, green! */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|CONFIG_1
)paren
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
multiline_comment|/* Set the ethernet adaptor disable IRQ */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|FJ_CONFIG1
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get the current statistics.&t;This may be called with the card open or&n;   closed. */
DECL|function|net_get_stats
r_static
r_struct
id|net_device_stats
op_star
id|net_get_stats
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_struct
id|net_local
op_star
id|lp
op_assign
(paren
r_struct
id|net_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
r_return
op_amp
id|lp-&gt;stats
suffix:semicolon
)brace
multiline_comment|/* Set or clear the multicast filter for this adaptor.&n;   num_addrs == -1&t;Promiscuous mode, receive all packets&n;   num_addrs == 0&t;Normal mode, clear multicast list&n;   num_addrs &gt; 0&t;Multicast mode, receive normal and MC packets, and do&n;&t;&t;&t;best-effort filtering.&n; */
DECL|function|set_multicast_list
r_static
r_void
id|set_multicast_list
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mc_count
op_logical_or
id|dev-&gt;flags
op_amp
(paren
id|IFF_PROMISC
op_or
id|IFF_ALLMULTI
)paren
)paren
(brace
multiline_comment|/*&n;&t;&t; *&t;We must make the kernel realise we had to move&n;&t;&t; *&t;into promisc mode or we start all out war on&n;&t;&t; *&t;the cable. - AC&n;&t;&t; */
id|dev-&gt;flags
op_or_assign
id|IFF_PROMISC
suffix:semicolon
id|outb
c_func
(paren
l_int|3
comma
id|ioaddr
op_plus
id|RX_MODE
)paren
suffix:semicolon
multiline_comment|/* Enable promiscuous mode */
)brace
r_else
id|outb
c_func
(paren
l_int|2
comma
id|ioaddr
op_plus
id|RX_MODE
)paren
suffix:semicolon
multiline_comment|/* Disable promiscuous, use normal mode */
)brace
macro_line|#ifdef MODULE
DECL|variable|devicename
r_static
r_char
id|devicename
(braket
l_int|9
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|dev_fmv18x
r_static
r_struct
id|net_device
id|dev_fmv18x
op_assign
(brace
id|devicename
comma
multiline_comment|/* device name is inserted by linux/drivers/net/net_init.c */
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|fmv18x_probe
)brace
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
op_assign
l_int|0x220
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
op_assign
l_int|0
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|net_debug
comma
l_string|&quot;i&quot;
)paren
suffix:semicolon
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|io
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;fmv18x: You should not use auto-probing with insmod!&bslash;n&quot;
)paren
suffix:semicolon
id|dev_fmv18x.base_addr
op_assign
id|io
suffix:semicolon
id|dev_fmv18x.irq
op_assign
id|irq
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
op_amp
id|dev_fmv18x
)paren
op_ne
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;fmv18x: register_netdev() returned non-zero.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EIO
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
r_void
DECL|function|cleanup_module
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
id|unregister_netdev
c_func
(paren
op_amp
id|dev_fmv18x
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev_fmv18x.priv
)paren
suffix:semicolon
id|dev_fmv18x.priv
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* If we don&squot;t do this, we can&squot;t re-insmod it later. */
id|free_irq
c_func
(paren
id|dev_fmv18x.irq
comma
op_amp
id|dev_fmv18x
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|dev_fmv18x.base_addr
comma
id|FMV18X_IO_EXTENT
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -I/usr/src/linux/net/inet -Wall -Wstrict-prototypes -O6 -m486 -c fmv18x.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  tab-width: 4&n; *  c-indent-level: 4&n; * End:&n; */
eof
