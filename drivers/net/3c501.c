multiline_comment|/* 3c501.c: A 3Com 3c501 ethernet driver for linux. */
multiline_comment|/*&n;    Written 1992,1993,1994  Donald Becker&n;&n;    Copyright 1993 United States Government as represented by the&n;    Director, National Security Agency.  This software may be used and&n;    distributed according to the terms of the GNU Public License,&n;    incorporated herein by reference.&n;&n;    This is a device driver for the 3Com Etherlink 3c501.&n;    Do not purchase this card, even as a joke.  It&squot;s performance is horrible,&n;    and it breaks in many ways.  &n;&n;    The author may be reached as becker@CESDIS.gsfc.nasa.gov, or C/O&n;    Center of Excellence in Space Data and Information Sciences&n;       Code 930.5, Goddard Space Flight Center, Greenbelt MD 20771&n;       &n;    Fixed (again!) the missing interrupt locking on TX/RX shifting.&n;    &t;&t;Alan Cox &lt;Alan.Cox@linux.org&gt;&n;    &t;&t;&n;    Removed calls to init_etherdev since they are no longer needed, and&n;    cleaned up modularization just a bit. The driver still allows only&n;    the default address for cards when loaded as a module, but that&squot;s&n;    really less braindead than anyone using a 3c501 board. :)&n;&t;&t;    19950208 (invid@msen.com)&n;&n;    Added traps for interrupts hitting the window as we clear and TX load&n;    the board. Now getting 150K/second FTP with a 3c501 card. Still playing&n;    with a TX-TX optimisation to see if we can touch 180-200K/second as seems&n;    theoretically maximum.&n;    &t;&t;19950402 Alan Cox &lt;Alan.Cox@linux.org&gt;&n;    &t;&t;&n;    Some notes on this thing if you have to hack it.  [Alan]&n;    &n;    1]&t;Some documentation is available from 3Com. Due to the boards age&n;    &t;standard responses when you ask for this will range from &squot;be serious&squot;&n;    &t;to &squot;give it to a museum&squot;. The documentation is incomplete and mostly&n;    &t;of historical interest anyway.&n;    &t;&n;    2]  The basic system is a single buffer which can be used to receive or&n;    &t;transmit a packet. A third command mode exists when you are setting&n;    &t;things up.&n;    &t;&n;    3]&t;If it&squot;s transmitting it&squot;s not receiving and vice versa. In fact the &n;    &t;time to get the board back into useful state after an operation is&n;    &t;quite large.&n;    &t;&n;    4]&t;The driver works by keeping the board in receive mode waiting for a&n;    &t;packet to arrive. When one arrives it is copied out of the buffer&n;    &t;and delivered to the kernel. The card is reloaded and off we go.&n;    &t;&n;    5]&t;When transmitting dev-&gt;tbusy is set and the card is reset (from&n;    &t;receive mode) [possibly losing a packet just received] to command&n;    &t;mode. A packet is loaded and transmit mode triggered. The interrupt&n;    &t;handler runs different code for transmit interrupts and can handle&n;    &t;returning to receive mode or retransmissions (yes you have to help&n;    &t;out with those too).&n;    &t;&n;    Problems:&n;    &t;There are a wide variety of undocumented error returns from the card&n;    and you basically have to kick the board and pray if they turn up. Most &n;    only occur under extreme load or if you do something the board doesn&squot;t&n;    like (eg touching a register at the wrong time).&n;    &n;    &t;The driver is less efficient than it could be. It switches through&n;    receive mode even if more transmits are queued. If this worries you buy&n;    a real ethernet card.&n;    &n;    &t;The combination of slow receive restart and no real multicast&n;    filter makes the board unusable with a kernel compiled for IP&n;    multicasting in a real multicast environment. Thats down to the board, &n;    but even with no multicast programs running a multicast IP kernel is&n;    in group 224.0.0.1 and you will therefore be listening to all multicasts.&n;    One nv conference running over that ethernet and you can give up.&n;    &n;*/
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;3c501.c: 9/23/94 Donald Becker (becker@cesdis.gsfc.nasa.gov).&bslash;n&quot;
suffix:semicolon
multiline_comment|/*&n;  Braindamage remaining:&n;  The 3c501 board.&n;  */
macro_line|#include &lt;linux/config.h&gt;
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
macro_line|#else
DECL|macro|MOD_INC_USE_COUNT
mdefine_line|#define MOD_INC_USE_COUNT
DECL|macro|MOD_DEC_USE_COUNT
mdefine_line|#define MOD_DEC_USE_COUNT
macro_line|#endif
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
multiline_comment|/* A zero-terminated list of I/O addresses to be probed.&n;   The 3c501 can be at many locations, but here are the popular ones. */
DECL|variable|netcard_portlist
r_static
r_int
r_int
id|netcard_portlist
(braket
)braket
op_assign
(brace
l_int|0x280
comma
l_int|0x300
comma
l_int|0
)brace
suffix:semicolon
"&f;"
multiline_comment|/* Index to functions. */
r_int
id|el1_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|el1_probe1
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
suffix:semicolon
r_static
r_int
id|el_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|el_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|el_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
suffix:semicolon
r_static
r_void
id|el_receive
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_void
id|el_reset
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_int
id|el1_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_static
r_struct
id|enet_statistics
op_star
id|el1_get_stats
c_func
(paren
r_struct
id|device
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
id|device
op_star
id|dev
comma
r_int
id|num_addrs
comma
r_void
op_star
id|addrs
)paren
suffix:semicolon
DECL|macro|EL1_IO_EXTENT
mdefine_line|#define EL1_IO_EXTENT&t;16
macro_line|#ifndef EL_DEBUG
DECL|macro|EL_DEBUG
mdefine_line|#define EL_DEBUG  2&t;/* use 0 for production, 1 for devel., &gt;2 for debug */
macro_line|#endif&t;&t;&t;/* Anything above 5 is wordy death! */
DECL|variable|el_debug
r_static
r_int
id|el_debug
op_assign
id|EL_DEBUG
suffix:semicolon
multiline_comment|/* Board-specific info in dev-&gt;priv. */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|stats
r_struct
id|enet_statistics
id|stats
suffix:semicolon
DECL|member|tx_pkt_start
r_int
id|tx_pkt_start
suffix:semicolon
multiline_comment|/* The length of the current Tx packet. */
DECL|member|collisions
r_int
id|collisions
suffix:semicolon
multiline_comment|/* Tx collisions this packet */
DECL|member|loading
r_int
id|loading
suffix:semicolon
multiline_comment|/* Spot buffer load collisions */
)brace
suffix:semicolon
"&f;"
DECL|macro|RX_STATUS
mdefine_line|#define RX_STATUS (ioaddr + 0x06)
DECL|macro|RX_CMD
mdefine_line|#define RX_CMD&t;  RX_STATUS
DECL|macro|TX_STATUS
mdefine_line|#define TX_STATUS (ioaddr + 0x07)
DECL|macro|TX_CMD
mdefine_line|#define TX_CMD&t;  TX_STATUS
DECL|macro|GP_LOW
mdefine_line|#define GP_LOW &t;  (ioaddr + 0x08)
DECL|macro|GP_HIGH
mdefine_line|#define GP_HIGH   (ioaddr + 0x09)
DECL|macro|RX_BUF_CLR
mdefine_line|#define RX_BUF_CLR (ioaddr + 0x0A)
DECL|macro|RX_LOW
mdefine_line|#define RX_LOW&t;  (ioaddr + 0x0A)
DECL|macro|RX_HIGH
mdefine_line|#define RX_HIGH   (ioaddr + 0x0B)
DECL|macro|SAPROM
mdefine_line|#define SAPROM&t;  (ioaddr + 0x0C)
DECL|macro|AX_STATUS
mdefine_line|#define AX_STATUS (ioaddr + 0x0E)
DECL|macro|AX_CMD
mdefine_line|#define AX_CMD&t;  AX_STATUS
DECL|macro|DATAPORT
mdefine_line|#define DATAPORT  (ioaddr + 0x0F)
DECL|macro|TX_RDY
mdefine_line|#define TX_RDY 0x08&t;&t;/* In TX_STATUS */
DECL|macro|EL1_DATAPTR
mdefine_line|#define EL1_DATAPTR&t;0x08
DECL|macro|EL1_RXPTR
mdefine_line|#define EL1_RXPTR&t;0x0A
DECL|macro|EL1_SAPROM
mdefine_line|#define EL1_SAPROM&t;0x0C
DECL|macro|EL1_DATAPORT
mdefine_line|#define EL1_DATAPORT &t;0x0f
multiline_comment|/* Writes to the ax command register. */
DECL|macro|AX_OFF
mdefine_line|#define AX_OFF&t;0x00&t;&t;&t;/* Irq off, buffer access on */
DECL|macro|AX_SYS
mdefine_line|#define AX_SYS  0x40&t;&t;&t;/* Load the buffer */
DECL|macro|AX_XMIT
mdefine_line|#define AX_XMIT 0x44&t;&t;&t;/* Transmit a packet */
DECL|macro|AX_RX
mdefine_line|#define AX_RX&t;0x48&t;&t;&t;/* Receive a packet */
DECL|macro|AX_LOOP
mdefine_line|#define AX_LOOP&t;0x0C&t;&t;&t;/* Loopback mode */
DECL|macro|AX_RESET
mdefine_line|#define AX_RESET 0x80
multiline_comment|/* Normal receive mode written to RX_STATUS.  We must intr on short packets&n;   to avoid bogus rx lockups. */
DECL|macro|RX_NORM
mdefine_line|#define RX_NORM 0xA8&t;&t;/* 0x68 == all addrs, 0xA8 only to me. */
DECL|macro|RX_PROM
mdefine_line|#define RX_PROM 0x68&t;&t;/* Senior Prom, uhmm promiscuous mode. */
DECL|macro|RX_MULT
mdefine_line|#define RX_MULT 0xE8&t;&t;/* Accept multicast packets. */
DECL|macro|TX_NORM
mdefine_line|#define TX_NORM 0x0A&t;/* Interrupt on everything that might hang the chip */
multiline_comment|/* TX_STATUS register. */
DECL|macro|TX_COLLISION
mdefine_line|#define TX_COLLISION 0x02
DECL|macro|TX_16COLLISIONS
mdefine_line|#define TX_16COLLISIONS 0x04
DECL|macro|TX_READY
mdefine_line|#define TX_READY 0x08
DECL|macro|RX_RUNT
mdefine_line|#define RX_RUNT 0x08
DECL|macro|RX_MISSED
mdefine_line|#define RX_MISSED 0x01&t;&t;/* Missed a packet due to 3c501 braindamage. */
DECL|macro|RX_GOOD
mdefine_line|#define RX_GOOD&t;0x30&t;&t;/* Good packet 0x20, or simple overflow 0x10. */
"&f;"
multiline_comment|/* The boilerplate probe code. */
macro_line|#ifdef HAVE_DEVLIST
DECL|variable|el1_drv
r_struct
id|netdev_entry
id|el1_drv
op_assign
(brace
l_string|&quot;3c501&quot;
comma
id|el1_probe1
comma
id|EL1_IO_EXTENT
comma
id|netcard_portlist
)brace
suffix:semicolon
macro_line|#else
r_int
DECL|function|el1_probe
id|el1_probe
c_func
(paren
r_struct
id|device
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
id|el1_probe1
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
id|netcard_portlist
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
id|netcard_portlist
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
id|EL1_IO_EXTENT
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|el1_probe1
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
macro_line|#endif
multiline_comment|/* The actual probe. */
r_static
r_int
DECL|function|el1_probe1
id|el1_probe1
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|ioaddr
)paren
(brace
macro_line|#ifndef MODULE
r_const
r_char
op_star
id|mname
suffix:semicolon
multiline_comment|/* Vendor name */
r_int
r_char
id|station_addr
(braket
l_int|6
)braket
suffix:semicolon
r_int
id|autoirq
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Read the station address PROM data from the special port.  */
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
id|outw
c_func
(paren
id|i
comma
id|ioaddr
op_plus
id|EL1_DATAPTR
)paren
suffix:semicolon
id|station_addr
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|EL1_SAPROM
)paren
suffix:semicolon
)brace
multiline_comment|/* Check the first three octets of the S.A. for 3Com&squot;s prefix, or&n;       for the Sager NP943 prefix. */
r_if
c_cond
(paren
id|station_addr
(braket
l_int|0
)braket
op_eq
l_int|0x02
op_logical_and
id|station_addr
(braket
l_int|1
)braket
op_eq
l_int|0x60
op_logical_and
id|station_addr
(braket
l_int|2
)braket
op_eq
l_int|0x8c
)paren
(brace
id|mname
op_assign
l_string|&quot;3c501&quot;
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|station_addr
(braket
l_int|0
)braket
op_eq
l_int|0x00
op_logical_and
id|station_addr
(braket
l_int|1
)braket
op_eq
l_int|0x80
op_logical_and
id|station_addr
(braket
l_int|2
)braket
op_eq
l_int|0xC8
)paren
(brace
id|mname
op_assign
l_string|&quot;NP943&quot;
suffix:semicolon
)brace
r_else
r_return
id|ENODEV
suffix:semicolon
multiline_comment|/* Grab the region so we can find the another board if autoIRQ fails. */
id|request_region
c_func
(paren
id|ioaddr
comma
id|EL1_IO_EXTENT
comma
l_string|&quot;3c501&quot;
)paren
suffix:semicolon
multiline_comment|/* We auto-IRQ by shutting off the interrupt line and letting it float&n;       high. */
r_if
c_cond
(paren
id|dev-&gt;irq
OL
l_int|2
)paren
(brace
id|autoirq_setup
c_func
(paren
l_int|2
)paren
suffix:semicolon
id|inb
c_func
(paren
id|RX_STATUS
)paren
suffix:semicolon
multiline_comment|/* Clear pending interrupts. */
id|inb
c_func
(paren
id|TX_STATUS
)paren
suffix:semicolon
id|outb
c_func
(paren
id|AX_LOOP
op_plus
l_int|1
comma
id|AX_CMD
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|AX_CMD
)paren
suffix:semicolon
id|autoirq
op_assign
id|autoirq_report
c_func
(paren
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|autoirq
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s probe at %#x failed to detect IRQ line.&bslash;n&quot;
comma
id|mname
comma
id|ioaddr
)paren
suffix:semicolon
r_return
id|EAGAIN
suffix:semicolon
)brace
)brace
id|outb
c_func
(paren
id|AX_RESET
op_plus
id|AX_LOOP
comma
id|AX_CMD
)paren
suffix:semicolon
multiline_comment|/* Loopback mode. */
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
id|memcpy
c_func
(paren
id|dev-&gt;dev_addr
comma
id|station_addr
comma
id|ETH_ALEN
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_amp
l_int|0xf
)paren
id|el_debug
op_assign
id|dev-&gt;mem_start
op_amp
l_int|0x7
suffix:semicolon
r_if
c_cond
(paren
id|autoirq
)paren
id|dev-&gt;irq
op_assign
id|autoirq
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s EtherLink at %#lx, using %sIRQ %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|mname
comma
id|dev-&gt;base_addr
comma
id|autoirq
ques
c_cond
l_string|&quot;auto&quot;
suffix:colon
l_string|&quot;assigned &quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
macro_line|#ifdef CONFIG_IP_MULTICAST
id|printk
c_func
(paren
l_string|&quot;WARNING: Use of the 3c501 in a multicast kernel is NOT recommended.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif    
r_if
c_cond
(paren
id|el_debug
)paren
id|printk
c_func
(paren
l_string|&quot;%s&quot;
comma
id|version
)paren
suffix:semicolon
multiline_comment|/* Initialize the device structure. */
r_if
c_cond
(paren
id|dev-&gt;priv
op_eq
l_int|NULL
)paren
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
multiline_comment|/* The EL1-specific entries in the device structure. */
id|dev-&gt;open
op_assign
op_amp
id|el_open
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
op_amp
id|el_start_xmit
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|el1_close
suffix:semicolon
id|dev-&gt;get_stats
op_assign
op_amp
id|el1_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
op_amp
id|set_multicast_list
suffix:semicolon
multiline_comment|/* Setup the generic properties */
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
macro_line|#endif /* !MODULE */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Open/initialize the board. */
r_static
r_int
DECL|function|el_open
id|el_open
c_func
(paren
r_struct
id|device
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
id|el_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Doing el_open()...&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|el_interrupt
comma
l_int|0
comma
l_string|&quot;3c501&quot;
)paren
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|irq2dev_map
(braket
id|dev-&gt;irq
)braket
op_assign
id|dev
suffix:semicolon
id|el_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|1
suffix:semicolon
id|outb
c_func
(paren
id|AX_RX
comma
id|AX_CMD
)paren
suffix:semicolon
multiline_comment|/* Aux control, irq and receive enabled */
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|el_start_xmit
id|el_start_xmit
c_func
(paren
r_struct
id|sk_buff
op_star
id|skb
comma
r_struct
id|device
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
r_if
c_cond
(paren
id|dev-&gt;tbusy
)paren
(brace
r_if
c_cond
(paren
id|jiffies
op_minus
id|dev-&gt;trans_start
OL
l_int|20
)paren
(brace
r_if
c_cond
(paren
id|el_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot; transmitter busy, deferred.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|el_debug
)paren
id|printk
(paren
l_string|&quot;%s: transmit timed out, txsr %#2x axsr=%02x rxsr=%02x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|inb
c_func
(paren
id|TX_STATUS
)paren
comma
id|inb
c_func
(paren
id|AX_STATUS
)paren
comma
id|inb
c_func
(paren
id|RX_STATUS
)paren
)paren
suffix:semicolon
id|lp-&gt;stats.tx_errors
op_increment
suffix:semicolon
id|outb
c_func
(paren
id|TX_NORM
comma
id|TX_CMD
)paren
suffix:semicolon
id|outb
c_func
(paren
id|RX_NORM
comma
id|RX_CMD
)paren
suffix:semicolon
id|outb
c_func
(paren
id|AX_OFF
comma
id|AX_CMD
)paren
suffix:semicolon
multiline_comment|/* Just trigger a false interrupt. */
id|outb
c_func
(paren
id|AX_RX
comma
id|AX_CMD
)paren
suffix:semicolon
multiline_comment|/* Aux control, irq and receive enabled */
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
r_if
c_cond
(paren
id|skb
op_eq
l_int|NULL
)paren
(brace
id|dev_tint
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|save_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
multiline_comment|/* Avoid incoming interrupts between us flipping tbusy and flipping&n;       mode as the driver assumes tbusy is a faithful indicator of card&n;       state */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Avoid timer-based retransmission conflicts. */
r_if
c_cond
(paren
id|set_bit
c_func
(paren
l_int|0
comma
(paren
r_void
op_star
)paren
op_amp
id|dev-&gt;tbusy
)paren
op_ne
l_int|0
)paren
(brace
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: Transmitter access conflict.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|gp_start
op_assign
l_int|0x800
op_minus
(paren
id|ETH_ZLEN
OL
id|skb-&gt;len
ques
c_cond
id|skb-&gt;len
suffix:colon
id|ETH_ZLEN
)paren
suffix:semicolon
r_int
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
id|load_it_again_sam
suffix:colon
id|lp-&gt;tx_pkt_start
op_assign
id|gp_start
suffix:semicolon
id|lp-&gt;collisions
op_assign
l_int|0
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Command mode with status cleared should [in theory]&n;&t; *&t;mean no more interrupts can be pending on the card.&n;&t; */
id|outb
c_func
(paren
id|AX_SYS
comma
id|AX_CMD
)paren
suffix:semicolon
id|inb
c_func
(paren
id|RX_STATUS
)paren
suffix:semicolon
id|inb
c_func
(paren
id|TX_STATUS
)paren
suffix:semicolon
id|lp-&gt;loading
op_assign
l_int|1
suffix:semicolon
multiline_comment|/* &n;&t; *&t;Turn interrupts back on while we spend a pleasant afternoon&n;&t; *&t;loading bytes into the board &n;&t; */
id|restore_flags
c_func
(paren
id|flags
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0x00
comma
id|RX_BUF_CLR
)paren
suffix:semicolon
multiline_comment|/* Set rx packet area to 0. */
id|outw
c_func
(paren
id|gp_start
comma
id|GP_LOW
)paren
suffix:semicolon
multiline_comment|/* aim - packet will be loaded into buffer start */
id|outsb
c_func
(paren
id|DATAPORT
comma
id|buf
comma
id|skb-&gt;len
)paren
suffix:semicolon
multiline_comment|/* load buffer (usual thing each byte increments the pointer) */
id|outw
c_func
(paren
id|gp_start
comma
id|GP_LOW
)paren
suffix:semicolon
multiline_comment|/* the board reuses the same register */
r_if
c_cond
(paren
id|lp-&gt;loading
op_eq
l_int|2
)paren
multiline_comment|/* A receive upset our load, despite our best efforts */
(brace
r_if
c_cond
(paren
id|el_debug
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: burped during tx load.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
)brace
r_goto
id|load_it_again_sam
suffix:semicolon
multiline_comment|/* Sigh... */
)brace
id|outb
c_func
(paren
id|AX_XMIT
comma
id|AX_CMD
)paren
suffix:semicolon
multiline_comment|/* fire ... Trigger xmit.  */
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
r_if
c_cond
(paren
id|el_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot; queued xmit.&bslash;n&quot;
)paren
suffix:semicolon
id|dev_kfree_skb
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/* The typical workload of the driver:&n;   Handle the ether interface interrupts. */
r_static
r_void
DECL|function|el_interrupt
id|el_interrupt
c_func
(paren
r_int
id|irq
comma
r_struct
id|pt_regs
op_star
id|regs
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
(paren
r_struct
id|device
op_star
)paren
(paren
id|irq2dev_map
(braket
id|irq
)braket
)paren
suffix:semicolon
r_struct
id|net_local
op_star
id|lp
suffix:semicolon
r_int
id|ioaddr
suffix:semicolon
r_int
id|axsr
suffix:semicolon
multiline_comment|/* Aux. status reg. */
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
op_logical_or
id|dev-&gt;irq
op_ne
id|irq
)paren
(brace
id|printk
(paren
l_string|&quot;3c501 driver: irq %d for unknown device.&bslash;n&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
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
id|axsr
op_assign
id|inb
c_func
(paren
id|AX_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|el_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot;%s: el_interrupt() aux=%#02x&quot;
comma
id|dev-&gt;name
comma
id|axsr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;interrupt
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Reentering the interrupt driver!&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|1
suffix:semicolon
id|lp-&gt;loading
op_assign
l_int|2
suffix:semicolon
multiline_comment|/* So we can spot loading interruptions */
r_if
c_cond
(paren
id|dev-&gt;tbusy
)paren
(brace
multiline_comment|/*&n;    &t; *&t;Board in transmit mode.&n;    &t; */
r_int
id|txsr
op_assign
id|inb
c_func
(paren
id|TX_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|el_debug
OG
l_int|6
)paren
id|printk
c_func
(paren
l_string|&quot; txsr=%02x gp=%04x rp=%04x&quot;
comma
id|txsr
comma
id|inw
c_func
(paren
id|GP_LOW
)paren
comma
id|inw
c_func
(paren
id|RX_LOW
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|axsr
op_amp
l_int|0x80
)paren
op_logical_and
(paren
id|txsr
op_amp
id|TX_READY
)paren
op_eq
l_int|0
)paren
(brace
multiline_comment|/*&n;&t; *&t;FIXME: is there a logic to whether to keep on trying or&n;&t; *&t;reset immediately ?&n;&t; */
id|printk
c_func
(paren
l_string|&quot;%s: Unusual interrupt during Tx, txsr=%02x axsr=%02x&quot;
l_string|&quot; gp=%03x rp=%03x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|txsr
comma
id|axsr
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
id|EL1_DATAPTR
)paren
comma
id|inw
c_func
(paren
id|ioaddr
op_plus
id|EL1_RXPTR
)paren
)paren
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|mark_bh
c_func
(paren
id|NET_BH
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|txsr
op_amp
id|TX_16COLLISIONS
)paren
(brace
multiline_comment|/*&n;&t; *&t;Timed out&n;&t; */
r_if
c_cond
(paren
id|el_debug
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Transmit failed 16 times, ethernet jammed?&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|outb
c_func
(paren
id|AX_SYS
comma
id|AX_CMD
)paren
suffix:semicolon
id|lp-&gt;stats.tx_aborted_errors
op_increment
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|txsr
op_amp
id|TX_COLLISION
)paren
(brace
multiline_comment|/* Retrigger xmit. */
r_if
c_cond
(paren
id|el_debug
OG
l_int|6
)paren
id|printk
c_func
(paren
l_string|&quot; retransmitting after a collision.&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Poor little chip can&squot;t reset its own start pointer&n;&t; */
id|outb
c_func
(paren
id|AX_SYS
comma
id|AX_CMD
)paren
suffix:semicolon
id|outw
c_func
(paren
id|lp-&gt;tx_pkt_start
comma
id|GP_LOW
)paren
suffix:semicolon
id|outb
c_func
(paren
id|AX_XMIT
comma
id|AX_CMD
)paren
suffix:semicolon
id|lp-&gt;stats.collisions
op_increment
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/*&n;&t; *&t;It worked.. we will now fall through and receive&n;&t; */
id|lp-&gt;stats.tx_packets
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|el_debug
OG
l_int|6
)paren
id|printk
c_func
(paren
l_string|&quot; Tx succeeded %s&bslash;n&quot;
comma
(paren
id|txsr
op_amp
id|TX_RDY
)paren
ques
c_cond
l_string|&quot;.&quot;
suffix:colon
l_string|&quot;but tx is busy!&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;This is safe the interrupt is atomic WRT itself.&n;&t; */
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|mark_bh
c_func
(paren
id|NET_BH
)paren
suffix:semicolon
multiline_comment|/* In case more to transmit */
)brace
)brace
r_else
(brace
multiline_comment|/*&n;    &t; *&t;In receive mode.&n;    &t; */
r_int
id|rxsr
op_assign
id|inb
c_func
(paren
id|RX_STATUS
)paren
suffix:semicolon
r_if
c_cond
(paren
id|el_debug
OG
l_int|5
)paren
id|printk
c_func
(paren
l_string|&quot; rxsr=%02x txsr=%02x rp=%04x&quot;
comma
id|rxsr
comma
id|inb
c_func
(paren
id|TX_STATUS
)paren
comma
id|inw
c_func
(paren
id|RX_LOW
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Just reading rx_status fixes most errors. &n;&t; */
r_if
c_cond
(paren
id|rxsr
op_amp
id|RX_MISSED
)paren
id|lp-&gt;stats.rx_missed_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|rxsr
op_amp
id|RX_RUNT
)paren
(brace
multiline_comment|/* Handled to avoid board lock-up. */
id|lp-&gt;stats.rx_length_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|el_debug
OG
l_int|5
)paren
id|printk
c_func
(paren
l_string|&quot; runt.&bslash;n&quot;
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|rxsr
op_amp
id|RX_GOOD
)paren
(brace
multiline_comment|/*&n;&t; *&t;Receive worked.&n;&t; */
id|el_receive
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Nothing?  Something is broken! */
r_if
c_cond
(paren
id|el_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;%s: No packet seen, rxsr=%02x **resetting 3c501***&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|rxsr
)paren
suffix:semicolon
id|el_reset
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|el_debug
OG
l_int|3
)paren
id|printk
c_func
(paren
l_string|&quot;.&bslash;n&quot;
)paren
suffix:semicolon
)brace
multiline_comment|/*&n;     *&t;Move into receive mode &n;     */
id|outb
c_func
(paren
id|AX_RX
comma
id|AX_CMD
)paren
suffix:semicolon
id|outw
c_func
(paren
l_int|0x00
comma
id|RX_BUF_CLR
)paren
suffix:semicolon
id|inb
c_func
(paren
id|RX_STATUS
)paren
suffix:semicolon
multiline_comment|/* Be certain that interrupts are cleared. */
id|inb
c_func
(paren
id|TX_STATUS
)paren
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We have a good packet. Well, not really &quot;good&quot;, just mostly not broken.&n;   We must check everything to see if it is good. */
r_static
r_void
DECL|function|el_receive
id|el_receive
c_func
(paren
r_struct
id|device
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
id|pkt_len
suffix:semicolon
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
id|pkt_len
op_assign
id|inw
c_func
(paren
id|RX_LOW
)paren
suffix:semicolon
r_if
c_cond
(paren
id|el_debug
OG
l_int|4
)paren
id|printk
c_func
(paren
l_string|&quot; el_receive %d.&bslash;n&quot;
comma
id|pkt_len
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|pkt_len
OL
l_int|60
)paren
op_logical_or
(paren
id|pkt_len
OG
l_int|1536
)paren
)paren
(brace
r_if
c_cond
(paren
id|el_debug
)paren
id|printk
c_func
(paren
l_string|&quot;%s: bogus packet, length=%d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|pkt_len
)paren
suffix:semicolon
id|lp-&gt;stats.rx_over_errors
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n;     *&t;Command mode so we can empty the buffer&n;     */
id|outb
c_func
(paren
id|AX_SYS
comma
id|AX_CMD
)paren
suffix:semicolon
id|skb
op_assign
id|dev_alloc_skb
c_func
(paren
id|pkt_len
op_plus
l_int|2
)paren
suffix:semicolon
multiline_comment|/*&n;     *&t;Start of frame&n;     */
id|outw
c_func
(paren
l_int|0x00
comma
id|GP_LOW
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
l_string|&quot;%s: Memory squeeze, dropping packet.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|lp-&gt;stats.rx_dropped
op_increment
suffix:semicolon
r_return
suffix:semicolon
)brace
r_else
(brace
id|skb_reserve
c_func
(paren
id|skb
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* Force 16 byte alignment */
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The read increments through the bytes. The interrupt&n;&t; *&t;handler will fix the pointer when it returns to &n;&t; *&t;receive mode.&n;&t; */
id|insb
c_func
(paren
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
id|pkt_len
)paren
suffix:semicolon
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
r_return
suffix:semicolon
)brace
r_static
r_void
DECL|function|el_reset
id|el_reset
c_func
(paren
r_struct
id|device
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
id|el_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;3c501 reset...&quot;
)paren
suffix:semicolon
id|outb
c_func
(paren
id|AX_RESET
comma
id|AX_CMD
)paren
suffix:semicolon
multiline_comment|/* Reset the chip */
id|outb
c_func
(paren
id|AX_LOOP
comma
id|AX_CMD
)paren
suffix:semicolon
multiline_comment|/* Aux control, irq and loopback enabled */
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
multiline_comment|/* Set the station address. */
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
id|i
)paren
suffix:semicolon
)brace
id|outw
c_func
(paren
l_int|0
comma
id|RX_BUF_CLR
)paren
suffix:semicolon
multiline_comment|/* Set rx packet area to 0. */
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Avoid glitch on writes to CMD regs */
id|outb
c_func
(paren
id|TX_NORM
comma
id|TX_CMD
)paren
suffix:semicolon
multiline_comment|/* tx irq on done, collision */
id|outb
c_func
(paren
id|RX_NORM
comma
id|RX_CMD
)paren
suffix:semicolon
multiline_comment|/* Set Rx commands. */
id|inb
c_func
(paren
id|RX_STATUS
)paren
suffix:semicolon
multiline_comment|/* Clear status. */
id|inb
c_func
(paren
id|TX_STATUS
)paren
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
r_static
r_int
DECL|function|el1_close
id|el1_close
c_func
(paren
r_struct
id|device
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
id|el_debug
OG
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Shutting down ethercard at %#x.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ioaddr
)paren
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Free and disable the IRQ. */
id|free_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|outb
c_func
(paren
id|AX_RESET
comma
id|AX_CMD
)paren
suffix:semicolon
multiline_comment|/* Reset the chip */
id|irq2dev_map
(braket
id|dev-&gt;irq
)braket
op_assign
l_int|0
suffix:semicolon
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|enet_statistics
op_star
DECL|function|el1_get_stats
id|el1_get_stats
c_func
(paren
r_struct
id|device
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
r_static
r_void
DECL|function|set_multicast_list
id|set_multicast_list
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|num_addrs
comma
r_void
op_star
id|addrs
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
id|num_addrs
OG
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|RX_MULT
comma
id|RX_CMD
)paren
suffix:semicolon
id|inb
c_func
(paren
id|RX_STATUS
)paren
suffix:semicolon
multiline_comment|/* Clear status. */
)brace
r_else
r_if
c_cond
(paren
id|num_addrs
OL
l_int|0
)paren
(brace
id|outb
c_func
(paren
id|RX_PROM
comma
id|RX_CMD
)paren
suffix:semicolon
id|inb
c_func
(paren
id|RX_STATUS
)paren
suffix:semicolon
)brace
r_else
(brace
id|outb
c_func
(paren
id|RX_NORM
comma
id|RX_CMD
)paren
suffix:semicolon
id|inb
c_func
(paren
id|RX_STATUS
)paren
suffix:semicolon
)brace
)brace
macro_line|#ifdef MODULE
DECL|variable|kernel_version
r_char
id|kernel_version
(braket
)braket
op_assign
id|UTS_RELEASE
suffix:semicolon
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
DECL|variable|dev_3c501
r_static
r_struct
id|device
id|dev_3c501
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
l_int|0x280
comma
l_int|5
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|NULL
comma
id|el1_probe
)brace
suffix:semicolon
DECL|variable|io
r_int
id|io
op_assign
l_int|0x280
suffix:semicolon
DECL|variable|irq
r_int
id|irq
op_assign
l_int|5
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
id|dev_3c501.irq
op_assign
id|irq
suffix:semicolon
id|dev_3c501.base_addr
op_assign
id|io
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
op_amp
id|dev_3c501
)paren
op_ne
l_int|0
)paren
r_return
op_minus
id|EIO
suffix:semicolon
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
multiline_comment|/* No need to check MOD_IN_USE, as sys_delete_module() checks. */
id|unregister_netdev
c_func
(paren
op_amp
id|dev_3c501
)paren
suffix:semicolon
multiline_comment|/* Free up the private structure, or leak memory :-)  */
id|kfree
c_func
(paren
id|dev_3c501.priv
)paren
suffix:semicolon
id|dev_3c501.priv
op_assign
l_int|NULL
suffix:semicolon
multiline_comment|/* gets re-allocated by el1_probe1 */
multiline_comment|/* If we don&squot;t do this, we can&squot;t re-insmod it later. */
id|release_region
c_func
(paren
id|dev_3c501.base_addr
comma
id|EL1_IO_EXTENT
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer  -m486 -c -o 3c501.o 3c501.c&quot;&n; *  kept-new-versions: 5&n; * End:&n; */
eof
