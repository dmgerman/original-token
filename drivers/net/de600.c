DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;de600.c: $Revision: 1.35 $,  Bjorn Ekwall (bj0rn@blox.se)&bslash;n&quot;
suffix:semicolon
multiline_comment|/*&n; *&t;de600.c&n; *&n; *&t;Linux driver for the D-Link DE-600 Ethernet pocket adapter.&n; *&n; *&t;Portions (C) Copyright 1993 by Bjorn Ekwall&n; *&t;The Author may be reached as bj0rn@blox.se&n; *&n; *&t;Based on adapter information gathered from DE600.ASM by D-Link Inc.,&n; *&t;as included on disk C in the v.2.11 of PC/TCP from FTP Software.&n; *&t;For DE600.asm:&n; *&t;&t;Portions (C) Copyright 1990 D-Link, Inc.&n; *&t;&t;Copyright, 1988-1992, Russell Nelson, Crynwr Software&n; *&n; *&t;Adapted to the sample network driver core for linux,&n; *&t;written by: Donald Becker &lt;becker@super.org&gt;&n; *&t;C/O Supercomputing Research Ctr., 17100 Science Dr., Bowie MD 20715&n; *&n; *&t;compile-command:&n; *&t;&quot;gcc -D__KERNEL__  -Wall -Wstrict-prototypes -O6 -fomit-frame-pointer &bslash;&n; *&t; -m486 -c de600.c&n; *&n; **************************************************************/
multiline_comment|/*&n; *&t;This program is free software; you can redistribute it and/or modify&n; *&t;it under the terms of the GNU General Public License as published by&n; *&t;the Free Software Foundation; either version 2, or (at your option)&n; *&t;any later version.&n; *&n; *&t;This program is distributed in the hope that it will be useful,&n; *&t;but WITHOUT ANY WARRANTY; without even the implied warranty of&n; *&t;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the&n; *&t;GNU General Public License for more details.&n; *&n; *&t;You should have received a copy of the GNU General Public License&n; *&t;along with this program; if not, write to the Free Software&n; *&t;Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. &n; *&n; **************************************************************/
multiline_comment|/* Add another &quot;; SLOW_DOWN_IO&quot; here if your adapter won&squot;t work OK: */
DECL|macro|DE600_SLOW_DOWN
mdefine_line|#define DE600_SLOW_DOWN SLOW_DOWN_IO; SLOW_DOWN_IO; SLOW_DOWN_IO
multiline_comment|/*&n; * If you still have trouble reading/writing to the adapter,&n; * modify the following &quot;#define&quot;: (see &lt;asm/io.h&gt; for more info)&n;#define REALLY_SLOW_IO&n; */
DECL|macro|SLOW_IO_BY_JUMPING
mdefine_line|#define SLOW_IO_BY_JUMPING /* Looks &quot;better&quot; than dummy write to port 0x80 :-) */
multiline_comment|/*&n; * For fix to TCP &quot;slowdown&quot;, take a look at the &quot;#define DE600_MAX_WINDOW&quot;&n; * near the end of the file...&n; */
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifdef DE600_DEBUG
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) if (de600_debug &gt;= 2) printk x
macro_line|#else
DECL|macro|DE600_DEBUG
mdefine_line|#define DE600_DEBUG 0
DECL|macro|PRINTK
mdefine_line|#define PRINTK(x) /**/
macro_line|#endif
DECL|variable|de600_debug
r_static
r_int
r_int
id|de600_debug
op_assign
id|DE600_DEBUG
suffix:semicolon
"&f;"
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;netinet/in.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;errno.h&gt;
macro_line|#include &lt;linux/inet.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#ifdef MODULE
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &quot;../../tools/version.h&quot;
macro_line|#endif
DECL|macro|netstats
mdefine_line|#define netstats enet_statistics
multiline_comment|/**************************************************&n; *                                                *&n; * Definition of D-Link Ethernet Pocket adapter   *&n; *                                                *&n; **************************************************/
multiline_comment|/*&n; * D-Link Ethernet pocket adapter ports&n; */
multiline_comment|/*&n; * OK, so I&squot;m cheating, but there are an awful lot of&n; * reads and writes in order to get anything in and out&n; * of the DE-600 with 4 bits at a time in the parallel port,&n; * so every saved instruction really helps :-)&n; *&n; * That is, I don&squot;t care what the device struct says&n; * but hope that Space.c will keep the rest of the drivers happy.&n; */
macro_line|#ifndef DE600_IO
DECL|macro|DE600_IO
mdefine_line|#define DE600_IO 0x378
macro_line|#endif
DECL|macro|DATA_PORT
mdefine_line|#define DATA_PORT&t;(DE600_IO)
DECL|macro|STATUS_PORT
mdefine_line|#define STATUS_PORT&t;(DE600_IO + 1)
DECL|macro|COMMAND_PORT
mdefine_line|#define COMMAND_PORT&t;(DE600_IO + 2)
macro_line|#ifndef DE600_IRQ
DECL|macro|DE600_IRQ
mdefine_line|#define DE600_IRQ&t;7
macro_line|#endif
multiline_comment|/*&n; * It really should look like this, and autoprobing as well...&n; *&n;#define DATA_PORT&t;(dev-&gt;base_addr + 0)&n;#define STATUS_PORT&t;(dev-&gt;base_addr + 1)&n;#define COMMAND_PORT&t;(dev-&gt;base_addr + 2)&n;#define DE600_IRQ&t;dev-&gt;irq&n; */
multiline_comment|/*&n; * D-Link COMMAND_PORT commands&n; */
DECL|macro|SELECT_NIC
mdefine_line|#define SELECT_NIC&t;0x04 /* select Network Interface Card */
DECL|macro|SELECT_PRN
mdefine_line|#define SELECT_PRN&t;0x1c /* select Printer */
DECL|macro|NML_PRN
mdefine_line|#define NML_PRN&t;&t;0xec /* normal Printer situation */
DECL|macro|IRQEN
mdefine_line|#define IRQEN&t;&t;0x10 /* enable IRQ line */
multiline_comment|/*&n; * D-Link STATUS_PORT&n; */
DECL|macro|RX_BUSY
mdefine_line|#define RX_BUSY&t;&t;0x80
DECL|macro|RX_GOOD
mdefine_line|#define RX_GOOD&t;&t;0x40
DECL|macro|TX_FAILED16
mdefine_line|#define TX_FAILED16&t;0x10
DECL|macro|TX_BUSY
mdefine_line|#define TX_BUSY&t;&t;0x08
multiline_comment|/*&n; * D-Link DATA_PORT commands&n; * command in low 4 bits&n; * data in high 4 bits&n; * select current data nibble with HI_NIBBLE bit&n; */
DECL|macro|WRITE_DATA
mdefine_line|#define WRITE_DATA&t;0x00 /* write memory */
DECL|macro|READ_DATA
mdefine_line|#define READ_DATA&t;0x01 /* read memory */
DECL|macro|STATUS
mdefine_line|#define STATUS&t;&t;0x02 /* read  status register */
DECL|macro|COMMAND
mdefine_line|#define COMMAND&t;&t;0x03 /* write command register (see COMMAND below) */
DECL|macro|NULL_COMMAND
mdefine_line|#define NULL_COMMAND&t;0x04 /* null command */
DECL|macro|RX_LEN
mdefine_line|#define RX_LEN&t;&t;0x05 /* read  received packet length */
DECL|macro|TX_ADDR
mdefine_line|#define TX_ADDR&t;&t;0x06 /* set adapter transmit memory address */
DECL|macro|RW_ADDR
mdefine_line|#define RW_ADDR&t;&t;0x07 /* set adapter read/write memory address */
DECL|macro|HI_NIBBLE
mdefine_line|#define HI_NIBBLE&t;0x08 /* read/write the high nibble of data,&n;&t;&t;&t;&t;or-ed with rest of command */
multiline_comment|/*&n; * command register, accessed through DATA_PORT with low bits = COMMAND&n; */
DECL|macro|RX_ALL
mdefine_line|#define RX_ALL&t;&t;0x01 /* PROMISCIOUS */
DECL|macro|RX_BP
mdefine_line|#define RX_BP&t;&t;0x02 /* default: BROADCAST &amp; PHYSICAL ADRESS */
DECL|macro|RX_MBP
mdefine_line|#define RX_MBP&t;&t;0x03 /* MULTICAST, BROADCAST &amp; PHYSICAL ADRESS */
DECL|macro|TX_ENABLE
mdefine_line|#define TX_ENABLE&t;0x04 /* bit 2 */
DECL|macro|RX_ENABLE
mdefine_line|#define RX_ENABLE&t;0x08 /* bit 3 */
DECL|macro|RESET
mdefine_line|#define RESET&t;&t;0x80 /* set bit 7 high */
DECL|macro|STOP_RESET
mdefine_line|#define STOP_RESET&t;0x00 /* set bit 7 low */
multiline_comment|/*&n; * data to command register&n; * (high 4 bits in write to DATA_PORT)&n; */
DECL|macro|RX_PAGE2_SELECT
mdefine_line|#define RX_PAGE2_SELECT&t;0x10 /* bit 4, only 2 pages to select */
DECL|macro|RX_BASE_PAGE
mdefine_line|#define RX_BASE_PAGE&t;0x20 /* bit 5, always set when specifying RX_ADDR */
DECL|macro|FLIP_IRQ
mdefine_line|#define FLIP_IRQ&t;0x40 /* bit 6 */
multiline_comment|/*&n; * D-Link adapter internal memory:&n; *&n; * 0-2K 1:st transmit page (send from pointer up to 2K)&n; * 2-4K&t;2:nd transmit page (send from pointer up to 4K)&n; *&n; * 4-6K 1:st receive page (data from 4K upwards)&n; * 6-8K 2:nd receive page (data from 6K upwards)&n; *&n; * 8K+&t;Adapter ROM (contains magic code and last 3 bytes of Ethernet address)&n; */
DECL|macro|MEM_2K
mdefine_line|#define MEM_2K&t;&t;0x0800 /* 2048 */
DECL|macro|MEM_4K
mdefine_line|#define MEM_4K&t;&t;0x1000 /* 4096 */
DECL|macro|MEM_6K
mdefine_line|#define MEM_6K&t;&t;0x1800 /* 6144 */
DECL|macro|NODE_ADDRESS
mdefine_line|#define NODE_ADDRESS&t;0x2000 /* 8192 */
DECL|macro|RUNT
mdefine_line|#define RUNT 60&t;&t;/* Too small Ethernet packet */
multiline_comment|/**************************************************&n; *                                                *&n; *             End of definition                  *&n; *                                                *&n; **************************************************/
multiline_comment|/*&n; * Index to functions, as function prototypes.&n; */
macro_line|#if 0
multiline_comment|/* For tricking tcp.c to announce a small max window (max 2 fast packets please :-) */
r_static
r_int
r_int
id|de600_rspace
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Routines used internally. (See &quot;convenience macros&quot;) */
r_static
r_int
id|de600_read_status
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
r_char
id|de600_read_byte
c_func
(paren
r_int
r_char
id|type
comma
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Put in the device structure. */
r_static
r_int
id|de600_open
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
id|de600_close
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
id|netstats
op_star
id|get_stats
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
id|de600_start_xmit
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
multiline_comment|/* Dispatch from interrupts. */
r_static
r_void
id|de600_interrupt
c_func
(paren
r_int
id|reg_ptr
)paren
suffix:semicolon
r_static
r_int
id|de600_tx_intr
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|irq_status
)paren
suffix:semicolon
r_static
r_void
id|de600_rx_intr
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/* Initialization */
r_static
r_void
id|trigger_interrupt
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|de600_probe
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
id|adapter_init
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n; * D-Link driver variables:&n; */
r_extern
r_struct
id|device
op_star
id|irq2dev_map
(braket
l_int|16
)braket
suffix:semicolon
DECL|variable|rx_page
r_static
r_volatile
r_int
id|rx_page
op_assign
l_int|0
suffix:semicolon
DECL|macro|TX_PAGES
mdefine_line|#define TX_PAGES 2
DECL|variable|tx_fifo
r_static
r_volatile
r_int
id|tx_fifo
(braket
id|TX_PAGES
)braket
suffix:semicolon
DECL|variable|tx_fifo_in
r_static
r_volatile
r_int
id|tx_fifo_in
op_assign
l_int|0
suffix:semicolon
DECL|variable|tx_fifo_out
r_static
r_volatile
r_int
id|tx_fifo_out
op_assign
l_int|0
suffix:semicolon
DECL|variable|free_tx_pages
r_static
r_volatile
r_int
id|free_tx_pages
op_assign
id|TX_PAGES
suffix:semicolon
multiline_comment|/*&n; * Convenience macros/functions for D-Link adapter&n; */
DECL|macro|select_prn
mdefine_line|#define select_prn() outb_p(SELECT_PRN, COMMAND_PORT); DE600_SLOW_DOWN
DECL|macro|select_nic
mdefine_line|#define select_nic() outb_p(SELECT_NIC, COMMAND_PORT); DE600_SLOW_DOWN
multiline_comment|/* Thanks for hints from Mark Burton &lt;markb@ordern.demon.co.uk&gt; */
DECL|macro|de600_put_byte
mdefine_line|#define de600_put_byte(data) ( &bslash;&n;&t;outb_p(((data) &lt;&lt; 4)   | WRITE_DATA            , DATA_PORT), &bslash;&n;&t;outb_p(((data) &amp; 0xf0) | WRITE_DATA | HI_NIBBLE, DATA_PORT))
multiline_comment|/*&n; * The first two outb_p()&squot;s below could perhaps be deleted if there&n; * would be more delay in the last two. Not certain about it yet...&n; */
DECL|macro|de600_put_command
mdefine_line|#define de600_put_command(cmd) ( &bslash;&n;&t;outb_p(( rx_page        &lt;&lt; 4)   | COMMAND            , DATA_PORT), &bslash;&n;&t;outb_p(( rx_page        &amp; 0xf0) | COMMAND | HI_NIBBLE, DATA_PORT), &bslash;&n;&t;outb_p(((rx_page | cmd) &lt;&lt; 4)   | COMMAND            , DATA_PORT), &bslash;&n;&t;outb_p(((rx_page | cmd) &amp; 0xf0) | COMMAND | HI_NIBBLE, DATA_PORT))
DECL|macro|de600_setup_address
mdefine_line|#define de600_setup_address(addr,type) ( &bslash;&n;&t;outb_p((((addr) &lt;&lt; 4) &amp; 0xf0) | type            , DATA_PORT), &bslash;&n;&t;outb_p(( (addr)       &amp; 0xf0) | type | HI_NIBBLE, DATA_PORT), &bslash;&n;&t;outb_p((((addr) &gt;&gt; 4) &amp; 0xf0) | type            , DATA_PORT), &bslash;&n;&t;outb_p((((addr) &gt;&gt; 8) &amp; 0xf0) | type | HI_NIBBLE, DATA_PORT))
DECL|macro|rx_page_adr
mdefine_line|#define rx_page_adr() ((rx_page &amp; RX_PAGE2_SELECT)?(MEM_6K):(MEM_4K))
multiline_comment|/* Flip bit, only 2 pages */
DECL|macro|next_rx_page
mdefine_line|#define next_rx_page() (rx_page ^= RX_PAGE2_SELECT)
DECL|macro|tx_page_adr
mdefine_line|#define tx_page_adr(a) (((a) + 1) * MEM_2K)
r_static
r_inline
r_int
DECL|function|de600_read_status
id|de600_read_status
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|status
suffix:semicolon
id|outb_p
c_func
(paren
id|STATUS
comma
id|DATA_PORT
)paren
suffix:semicolon
id|status
op_assign
id|inb
c_func
(paren
id|STATUS_PORT
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|NULL_COMMAND
op_or
id|HI_NIBBLE
comma
id|DATA_PORT
)paren
suffix:semicolon
r_return
id|status
suffix:semicolon
)brace
r_static
r_inline
r_int
r_char
DECL|function|de600_read_byte
id|de600_read_byte
c_func
(paren
r_int
r_char
id|type
comma
r_struct
id|device
op_star
id|dev
)paren
(brace
multiline_comment|/* dev used by macros */
r_int
r_char
id|lo
suffix:semicolon
(paren
r_void
)paren
id|outb_p
c_func
(paren
(paren
id|type
)paren
comma
id|DATA_PORT
)paren
suffix:semicolon
id|lo
op_assign
(paren
(paren
r_int
r_char
)paren
id|inb
c_func
(paren
id|STATUS_PORT
)paren
)paren
op_rshift
l_int|4
suffix:semicolon
(paren
r_void
)paren
id|outb_p
c_func
(paren
(paren
id|type
)paren
op_or
id|HI_NIBBLE
comma
id|DATA_PORT
)paren
suffix:semicolon
r_return
(paren
(paren
r_int
r_char
)paren
id|inb
c_func
(paren
id|STATUS_PORT
)paren
op_amp
(paren
r_int
r_char
)paren
l_int|0xf0
)paren
op_or
id|lo
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * Open/initialize the board.  This is called (in the current kernel)&n; * after booting when &squot;ifconfig &lt;dev-&gt;name&gt; $IP_ADDR&squot; is run (in rc.inet1).&n; *&n; * This routine should set everything up anew at each open, even&n; * registers that &quot;should&quot; only need to be set once at boot, so that&n; * there is a non-reboot way to recover if something goes wrong.&n; */
r_static
r_int
DECL|function|de600_open
id|de600_open
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
macro_line|#if 0
r_extern
r_struct
id|proto
id|tcp_prot
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|DE600_IRQ
comma
id|de600_interrupt
)paren
)paren
(brace
id|printk
(paren
l_string|&quot;%s: unable to get IRQ %d&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|DE600_IRQ
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
id|irq2dev_map
(braket
id|DE600_IRQ
)braket
op_assign
id|dev
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_INC_USE_COUNT
suffix:semicolon
macro_line|#endif
id|adapter_init
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Yes, I know!&n;&t; * This is really not nice, but since a machine that uses DE-600&n;&t; * rarely uses any other TCP/IP connection device simultaneously,&n;&t; * this hack shouldn&squot;t really slow anything up.&n;&t; * (I don&squot;t know about slip though... but it won&squot;t break it)&n;&t; *&n;&t; * This fix is better than changing in tcp.h IMHO&n;&t; */
macro_line|#if 0&t; 
id|tcp_prot.rspace
op_assign
id|de600_rspace
suffix:semicolon
multiline_comment|/* was: sock_rspace */
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * The inverse routine to de600_open().&n; */
r_static
r_int
DECL|function|de600_close
id|de600_close
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|rx_page
op_assign
l_int|0
suffix:semicolon
id|de600_put_command
c_func
(paren
id|RESET
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|STOP_RESET
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
l_int|0
)paren
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|DE600_IRQ
)paren
suffix:semicolon
id|irq2dev_map
(braket
id|DE600_IRQ
)braket
op_assign
l_int|NULL
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
macro_line|#ifdef MODULE
id|MOD_DEC_USE_COUNT
suffix:semicolon
macro_line|#endif
macro_line|#if 0
id|tcp_prot.rspace
op_assign
id|sock_rspace
suffix:semicolon
multiline_comment|/* see comment above! */
macro_line|#endif
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_struct
id|netstats
op_star
DECL|function|get_stats
id|get_stats
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_return
(paren
r_struct
id|netstats
op_star
)paren
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
)brace
r_static
r_inline
r_void
DECL|function|trigger_interrupt
id|trigger_interrupt
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
id|de600_put_command
c_func
(paren
id|FLIP_IRQ
)paren
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
id|DE600_SLOW_DOWN
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
l_int|0
)paren
suffix:semicolon
)brace
multiline_comment|/*&n; * Copy a buffer to the adapter transmit page memory.&n; * Start sending.&n; */
r_static
r_int
DECL|function|de600_start_xmit
id|de600_start_xmit
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
r_int
id|transmit_from
suffix:semicolon
r_int
id|len
suffix:semicolon
r_int
id|tickssofar
suffix:semicolon
r_int
r_char
op_star
id|buffer
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/*&n;&t; * If some higher layer thinks we&squot;ve missed a&n;&t; * tx-done interrupt we are passed NULL.&n;&t; * Caution: dev_tint() handles the cli()/sti() itself.&n;&t; */
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
r_if
c_cond
(paren
id|free_tx_pages
op_le
l_int|0
)paren
(brace
multiline_comment|/* Do timeouts, to avoid hangs. */
id|tickssofar
op_assign
id|jiffies
op_minus
id|dev-&gt;trans_start
suffix:semicolon
r_if
c_cond
(paren
id|tickssofar
OL
l_int|5
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* else */
id|printk
c_func
(paren
l_string|&quot;%s: transmit timed out (%d), %s?&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tickssofar
comma
l_string|&quot;network cable problem&quot;
)paren
suffix:semicolon
multiline_comment|/* Restart the adapter. */
id|adapter_init
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
multiline_comment|/* Start real output */
id|PRINTK
c_func
(paren
(paren
l_string|&quot;de600_start_xmit:len=%d, page %d/%d&bslash;n&quot;
comma
id|skb-&gt;len
comma
id|tx_fifo_in
comma
id|free_tx_pages
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|len
op_assign
id|skb-&gt;len
)paren
OL
id|RUNT
)paren
id|len
op_assign
id|RUNT
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|tx_fifo
(braket
id|tx_fifo_in
)braket
op_assign
id|transmit_from
op_assign
id|tx_page_adr
c_func
(paren
id|tx_fifo_in
)paren
op_minus
id|len
suffix:semicolon
id|tx_fifo_in
op_assign
(paren
id|tx_fifo_in
op_plus
l_int|1
)paren
op_mod
id|TX_PAGES
suffix:semicolon
multiline_comment|/* Next free tx page */
id|de600_setup_address
c_func
(paren
id|transmit_from
comma
id|RW_ADDR
)paren
suffix:semicolon
r_for
c_loop
(paren
suffix:semicolon
id|len
OG
l_int|0
suffix:semicolon
op_decrement
id|len
comma
op_increment
id|buffer
)paren
id|de600_put_byte
c_func
(paren
op_star
id|buffer
)paren
suffix:semicolon
r_if
c_cond
(paren
id|free_tx_pages
op_decrement
op_eq
id|TX_PAGES
)paren
(brace
multiline_comment|/* No transmission going on */
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* allow more packets into adapter */
multiline_comment|/* Send page and generate an interrupt */
id|de600_setup_address
c_func
(paren
id|transmit_from
comma
id|TX_ADDR
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|TX_ENABLE
)paren
suffix:semicolon
)brace
r_else
(brace
id|dev-&gt;tbusy
op_assign
op_logical_neg
id|free_tx_pages
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
)brace
id|sti
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* interrupts back on */
r_if
c_cond
(paren
id|skb-&gt;free
)paren
id|kfree_skb
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
multiline_comment|/*&n; * The typical workload of the driver:&n; * Handle the network interface interrupts.&n; */
r_static
r_void
DECL|function|de600_interrupt
id|de600_interrupt
c_func
(paren
r_int
id|reg_ptr
)paren
(brace
r_int
id|irq
op_assign
op_minus
(paren
(paren
(paren
r_struct
id|pt_regs
op_star
)paren
id|reg_ptr
)paren
op_member_access_from_pointer
id|orig_eax
op_plus
l_int|2
)paren
suffix:semicolon
r_struct
id|device
op_star
id|dev
op_assign
id|irq2dev_map
(braket
id|irq
)braket
suffix:semicolon
r_int
r_char
id|irq_status
suffix:semicolon
r_int
id|retrig
op_assign
l_int|0
suffix:semicolon
r_int
id|boguscount
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* This might just as well be deleted now, no crummy drivers present :-) */
r_if
c_cond
(paren
(paren
id|dev
op_eq
l_int|NULL
)paren
op_logical_or
(paren
id|dev-&gt;start
op_eq
l_int|0
)paren
op_logical_or
(paren
id|DE600_IRQ
op_ne
id|irq
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: bogus interrupt %d&bslash;n&quot;
comma
id|dev
ques
c_cond
id|dev-&gt;name
suffix:colon
l_string|&quot;DE-600&quot;
comma
id|irq
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|dev-&gt;interrupt
op_assign
l_int|1
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|irq_status
op_assign
id|de600_read_status
c_func
(paren
id|dev
)paren
suffix:semicolon
r_do
(brace
id|PRINTK
c_func
(paren
(paren
l_string|&quot;de600_interrupt (%2.2X)&bslash;n&quot;
comma
id|irq_status
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irq_status
op_amp
id|RX_GOOD
)paren
id|de600_rx_intr
c_func
(paren
id|dev
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_status
op_amp
id|RX_BUSY
)paren
)paren
id|de600_put_command
c_func
(paren
id|RX_ENABLE
)paren
suffix:semicolon
multiline_comment|/* Any transmission in progress? */
r_if
c_cond
(paren
id|free_tx_pages
OL
id|TX_PAGES
)paren
id|retrig
op_assign
id|de600_tx_intr
c_func
(paren
id|dev
comma
id|irq_status
)paren
suffix:semicolon
r_else
id|retrig
op_assign
l_int|0
suffix:semicolon
id|irq_status
op_assign
id|de600_read_status
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_while
c_loop
(paren
(paren
id|irq_status
op_amp
id|RX_GOOD
)paren
op_logical_or
(paren
(paren
op_increment
id|boguscount
OL
l_int|10
)paren
op_logical_and
id|retrig
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * Yeah, it _looks_ like busy waiting, smells like busy waiting&n;&t; * and I know it&squot;s not PC, but please, it will only occur once&n;&t; * in a while and then only for a loop or so (&lt; 1ms for sure!)&n;&t; */
multiline_comment|/* Enable adapter interrupts */
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retrig
)paren
id|trigger_interrupt
c_func
(paren
id|dev
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
r_static
r_int
DECL|function|de600_tx_intr
id|de600_tx_intr
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|irq_status
)paren
(brace
multiline_comment|/*&n;&t; * Returns 1 if tx still not done&n;&t; */
id|mark_bh
c_func
(paren
id|NET_BH
)paren
suffix:semicolon
multiline_comment|/* Check if current transmission is done yet */
r_if
c_cond
(paren
id|irq_status
op_amp
id|TX_BUSY
)paren
r_return
l_int|1
suffix:semicolon
multiline_comment|/* tx not done, try again */
multiline_comment|/* else */
multiline_comment|/* If last transmission OK then bump fifo index */
r_if
c_cond
(paren
op_logical_neg
(paren
id|irq_status
op_amp
id|TX_FAILED16
)paren
)paren
(brace
id|tx_fifo_out
op_assign
(paren
id|tx_fifo_out
op_plus
l_int|1
)paren
op_mod
id|TX_PAGES
suffix:semicolon
op_increment
id|free_tx_pages
suffix:semicolon
(paren
(paren
r_struct
id|netstats
op_star
)paren
(paren
id|dev-&gt;priv
)paren
)paren
op_member_access_from_pointer
id|tx_packets
op_increment
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
)brace
multiline_comment|/* More to send, or resend last packet? */
r_if
c_cond
(paren
(paren
id|free_tx_pages
OL
id|TX_PAGES
)paren
op_logical_or
(paren
id|irq_status
op_amp
id|TX_FAILED16
)paren
)paren
(brace
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
id|de600_setup_address
c_func
(paren
id|tx_fifo
(braket
id|tx_fifo_out
)braket
comma
id|TX_ADDR
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|TX_ENABLE
)paren
suffix:semicolon
r_return
l_int|1
suffix:semicolon
)brace
multiline_comment|/* else */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/*&n; * We have a good packet, get it out of the adapter.&n; */
r_static
r_void
DECL|function|de600_rx_intr
id|de600_rx_intr
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_struct
id|sk_buff
op_star
id|skb
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|read_from
suffix:semicolon
r_int
id|size
suffix:semicolon
r_register
r_int
r_char
op_star
id|buffer
suffix:semicolon
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Get size of received packet */
id|size
op_assign
id|de600_read_byte
c_func
(paren
id|RX_LEN
comma
id|dev
)paren
suffix:semicolon
multiline_comment|/* low byte */
id|size
op_add_assign
(paren
id|de600_read_byte
c_func
(paren
id|RX_LEN
comma
id|dev
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
multiline_comment|/* high byte */
id|size
op_sub_assign
l_int|4
suffix:semicolon
multiline_comment|/* Ignore trailing 4 CRC-bytes */
multiline_comment|/* Tell adapter where to store next incoming packet, enable receiver */
id|read_from
op_assign
id|rx_page_adr
c_func
(paren
)paren
suffix:semicolon
id|next_rx_page
c_func
(paren
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|RX_ENABLE
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|size
OL
l_int|32
)paren
op_logical_or
(paren
id|size
OG
l_int|1535
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s: Bogus packet size %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|size
)paren
suffix:semicolon
id|skb
op_assign
id|alloc_skb
c_func
(paren
id|size
comma
id|GFP_ATOMIC
)paren
suffix:semicolon
id|sti
c_func
(paren
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
l_string|&quot;%s: Couldn&squot;t allocate a sk_buff of size %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|size
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* else */
id|skb-&gt;lock
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* &squot;skb-&gt;data&squot; points to the start of sk_buff data area. */
id|buffer
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* copy the packet into the buffer */
id|de600_setup_address
c_func
(paren
id|read_from
comma
id|RW_ADDR
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
id|size
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
op_decrement
id|i
comma
op_increment
id|buffer
)paren
op_star
id|buffer
op_assign
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
suffix:semicolon
(paren
(paren
r_struct
id|netstats
op_star
)paren
(paren
id|dev-&gt;priv
)paren
)paren
op_member_access_from_pointer
id|rx_packets
op_increment
suffix:semicolon
multiline_comment|/* count all receives */
r_if
c_cond
(paren
id|dev_rint
c_func
(paren
(paren
r_int
r_char
op_star
)paren
id|skb
comma
id|size
comma
id|IN_SKBUFF
comma
id|dev
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;%s: receive buffers full.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/*&n;&t; * If any worth-while packets have been received, dev_rint()&n;&t; * has done a mark_bh(INET_BH) for us and will work on them&n;&t; * when we get to the bottom-half routine.&n;&t; */
)brace
r_int
DECL|function|de600_probe
id|de600_probe
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
r_static
r_struct
id|netstats
id|de600_netstats
suffix:semicolon
multiline_comment|/*dev-&gt;priv = kmalloc(sizeof(struct netstats), GFP_KERNEL);*/
id|printk
c_func
(paren
l_string|&quot;%s: D-Link DE-600 pocket adapter&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
multiline_comment|/* Alpha testers must have the version number to report bugs. */
r_if
c_cond
(paren
id|de600_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
id|version
)paren
suffix:semicolon
multiline_comment|/* probe for adapter */
id|rx_page
op_assign
l_int|0
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
(paren
r_void
)paren
id|de600_read_status
c_func
(paren
id|dev
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|RESET
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|STOP_RESET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|de600_read_status
c_func
(paren
id|dev
)paren
op_amp
l_int|0xf0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;: not at I/O %#3x.&bslash;n&quot;
comma
id|DATA_PORT
)paren
suffix:semicolon
r_return
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&n;&t; * Maybe we found one,&n;&t; * have to check if it is a D-Link DE-600 adapter...&n;&t; */
multiline_comment|/* Get the adapter ethernet address from the ROM */
id|de600_setup_address
c_func
(paren
id|NODE_ADDRESS
comma
id|RW_ADDR
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
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|de600_read_byte
c_func
(paren
id|READ_DATA
comma
id|dev
)paren
suffix:semicolon
id|dev-&gt;broadcast
(braket
id|i
)braket
op_assign
l_int|0xff
suffix:semicolon
)brace
multiline_comment|/* Check magic code */
r_if
c_cond
(paren
(paren
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
op_eq
l_int|0xde
)paren
op_logical_and
(paren
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
op_eq
l_int|0x15
)paren
)paren
(brace
multiline_comment|/* OK, install real address */
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
op_assign
l_int|0x00
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|1
)braket
op_assign
l_int|0x80
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|2
)braket
op_assign
l_int|0xc8
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
op_and_assign
l_int|0x0f
suffix:semicolon
id|dev-&gt;dev_addr
(braket
l_int|3
)braket
op_or_assign
l_int|0x70
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; not identified in the printer port&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ENODEV
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;, Ethernet Address: %2.2X&quot;
comma
id|dev-&gt;dev_addr
(braket
l_int|0
)braket
)paren
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|1
suffix:semicolon
id|i
OL
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot;:%2.2X&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n&quot;
)paren
suffix:semicolon
multiline_comment|/* Initialize the device structure. */
multiline_comment|/*dev-&gt;priv = kmalloc(sizeof(struct netstats), GFP_KERNEL);*/
id|dev-&gt;priv
op_assign
op_amp
id|de600_netstats
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
id|netstats
)paren
)paren
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|get_stats
suffix:semicolon
id|dev-&gt;open
op_assign
id|de600_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|de600_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
op_amp
id|de600_start_xmit
suffix:semicolon
id|ether_setup
c_func
(paren
id|dev
)paren
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_void
DECL|function|adapter_init
id|adapter_init
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
id|cli
c_func
(paren
)paren
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Transmit busy...  */
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|1
suffix:semicolon
id|select_nic
c_func
(paren
)paren
suffix:semicolon
id|rx_page
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* used by RESET */
id|de600_put_command
c_func
(paren
id|RESET
)paren
suffix:semicolon
id|de600_put_command
c_func
(paren
id|STOP_RESET
)paren
suffix:semicolon
id|tx_fifo_in
op_assign
l_int|0
suffix:semicolon
id|tx_fifo_out
op_assign
l_int|0
suffix:semicolon
id|free_tx_pages
op_assign
id|TX_PAGES
suffix:semicolon
multiline_comment|/* set the ether address. */
id|de600_setup_address
c_func
(paren
id|NODE_ADDRESS
comma
id|RW_ADDR
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
id|ETH_ALEN
suffix:semicolon
id|i
op_increment
)paren
id|de600_put_byte
c_func
(paren
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
multiline_comment|/* where to start saving incoming packets */
id|rx_page
op_assign
id|RX_BP
op_or
id|RX_BASE_PAGE
suffix:semicolon
id|de600_setup_address
c_func
(paren
id|MEM_4K
comma
id|RW_ADDR
)paren
suffix:semicolon
multiline_comment|/* Enable receiver */
id|de600_put_command
c_func
(paren
id|RX_ENABLE
)paren
suffix:semicolon
id|select_prn
c_func
(paren
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#if 0
multiline_comment|/*&n; *&t;The new router code (coming soon 8-) ) will fix this properly.&n; */
mdefine_line|#define DE600_MIN_WINDOW 1024
mdefine_line|#define DE600_MAX_WINDOW 2048
mdefine_line|#define DE600_TCP_WINDOW_DIFF 1024
multiline_comment|/*&n; * Copied from sock.c&n; *&n; * Sets a lower max receive window in order to achieve &lt;= 2&n; * packets arriving at the adapter in fast succession.&n; * (No way that a DE-600 can cope with an ethernet saturated with its packets :-)&n; *&n; * Since there are only 2 receive buffers in the DE-600&n; * and it takes some time to copy from the adapter,&n; * this is absolutely necessary for any TCP performance whatsoever!&n; *&n; */
mdefine_line|#define min(a,b)&t;((a)&lt;(b)?(a):(b))
r_static
r_int
r_int
id|de600_rspace
c_func
(paren
r_struct
id|sock
op_star
id|sk
)paren
(brace
r_int
id|amt
suffix:semicolon
r_if
c_cond
(paren
id|sk
op_ne
l_int|NULL
)paren
(brace
multiline_comment|/*&n; * Hack! You might want to play with commenting away the following line,&n; * if you know what you do!&n; */
id|sk-&gt;max_unacked
op_assign
id|DE600_MAX_WINDOW
op_minus
id|DE600_TCP_WINDOW_DIFF
suffix:semicolon
r_if
c_cond
(paren
id|sk-&gt;rmem_alloc
op_ge
id|SK_RMEM_MAX
op_minus
l_int|2
op_star
id|DE600_MIN_WINDOW
)paren
r_return
l_int|0
suffix:semicolon
id|amt
op_assign
id|min
c_func
(paren
(paren
id|SK_RMEM_MAX
op_minus
id|sk-&gt;rmem_alloc
)paren
op_div
l_int|2
op_minus
id|DE600_MIN_WINDOW
comma
id|DE600_MAX_WINDOW
)paren
suffix:semicolon
r_if
c_cond
(paren
id|amt
OL
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
r_return
id|amt
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#endif
macro_line|#ifdef MODULE
DECL|variable|kernel_version
r_char
id|kernel_version
(braket
)braket
op_assign
id|UTS_RELEASE
suffix:semicolon
DECL|variable|de600_dev
r_static
r_struct
id|device
id|de600_dev
op_assign
(brace
l_string|&quot;&quot;
multiline_comment|/*&quot;de600&quot;*/
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
l_int|0
comma
l_int|NULL
comma
id|de600_probe
)brace
suffix:semicolon
r_int
DECL|function|init_module
id|init_module
c_func
(paren
r_void
)paren
(brace
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
op_amp
id|de600_dev
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
r_if
c_cond
(paren
id|MOD_IN_USE
)paren
id|printk
c_func
(paren
l_string|&quot;de600: device busy, remove delayed&bslash;n&quot;
)paren
suffix:semicolon
r_else
id|unregister_netdev
c_func
(paren
op_amp
id|de600_dev
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof