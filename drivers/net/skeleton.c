multiline_comment|/* skeleton.c: A network driver outline for linux. */
multiline_comment|/*&n;&t;Written 1993-94 by Donald Becker.&n;&n;&t;Copyright 1993 United States Government as represented by the&n;&t;Director, National Security Agency.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU Public License, incorporated herein by reference.&n;&n;&t;The author may be reached as becker@CESDIS.gsfc.nasa.gov, or C/O&n;&t;Center of Excellence in Space Data and Information Sciences&n;&t;   Code 930.5, Goddard Space Flight Center, Greenbelt MD 20771&n;&n;&t;This file is an outline for writing a network device driver for the&n;&t;the Linux operating system.&n;&n;&t;To write (or understand) a driver, have a look at the &quot;loopback.c&quot; file to&n;&t;get a feel of what is going on, and then use the code below as a skeleton&n;&t;for the new driver.&n;&n;*/
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;skeleton.c:v1.51 9/24/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
multiline_comment|/* Always include &squot;config.h&squot; first in case the user wants to turn on&n;   or override something. */
macro_line|#include &lt;linux/config.h&gt;
multiline_comment|/*&n;  Sources:&n;&t;List your sources of programming information to document that&n;&t;the driver is your own creation, and give due credit to others&n;&t;that contributed to the work.  Remember that GNU project code&n;&t;cannot use proprietary or trade secret information.&t; Interface&n;&t;definitions are generally considered non-copyrightable to the&n;&t;extent that the same names and structures must be used to be&n;&t;compatible.&n;&n;&t;Finally, keep in mind that the Linux kernel is has an API, not&n;&t;ABI.  Proprietary object-code-only distributions are not permitted&n;&t;under the GPL.&n;*/
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
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
r_extern
r_struct
id|device
op_star
id|init_etherdev
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|sizeof_private
comma
r_int
r_int
op_star
id|mem_startp
)paren
suffix:semicolon
multiline_comment|/* First, a few definitions that the brave might change. */
multiline_comment|/* A zero-terminated list of I/O addresses to be probed. */
DECL|variable|netcard_portlist
r_static
r_int
r_int
id|netcard_portlist
(braket
)braket
op_assign
(brace
l_int|0x200
comma
l_int|0x240
comma
l_int|0x280
comma
l_int|0x2C0
comma
l_int|0x300
comma
l_int|0x320
comma
l_int|0x340
comma
l_int|0
)brace
suffix:semicolon
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifndef NET_DEBUG
DECL|macro|NET_DEBUG
mdefine_line|#define NET_DEBUG 2
macro_line|#endif
DECL|variable|net_debug
r_static
r_int
r_int
id|net_debug
op_assign
id|NET_DEBUG
suffix:semicolon
multiline_comment|/* The number of low I/O ports used by the ethercard. */
DECL|macro|NETCARD_IO_EXTENT
mdefine_line|#define NETCARD_IO_EXTENT&t;32
multiline_comment|/* Information that need to be kept for each board. */
DECL|struct|net_local
r_struct
id|net_local
(brace
DECL|member|stats
r_struct
id|enet_statistics
id|stats
suffix:semicolon
DECL|member|open_time
r_int
id|open_time
suffix:semicolon
multiline_comment|/* Useless example local info. */
)brace
suffix:semicolon
multiline_comment|/* The station (ethernet) address prefix, used for IDing the board. */
DECL|macro|SA_ADDR0
mdefine_line|#define SA_ADDR0 0x00
DECL|macro|SA_ADDR1
mdefine_line|#define SA_ADDR1 0x42
DECL|macro|SA_ADDR2
mdefine_line|#define SA_ADDR2 0x65
multiline_comment|/* Index to functions, as function prototypes. */
r_extern
r_int
id|netcard_probe
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
id|netcard_probe1
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
id|net_open
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
id|net_send_packet
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
id|net_interrupt
c_func
(paren
r_int
id|reg_ptr
)paren
suffix:semicolon
r_static
r_void
id|net_rx
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
id|net_close
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
id|net_get_stats
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
multiline_comment|/* Example routines you must write ;-&gt;. */
DECL|macro|tx_done
mdefine_line|#define tx_done(dev) 1
r_extern
r_void
id|hardware_send_packet
c_func
(paren
r_int
id|ioaddr
comma
r_char
op_star
id|buf
comma
r_int
id|length
)paren
suffix:semicolon
r_extern
r_void
id|chipset_init
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|startp
)paren
suffix:semicolon
"&f;"
multiline_comment|/* Check for a network adaptor of this type, and return &squot;0&squot; iff one exists.&n;   If dev-&gt;base_addr == 0, probe all likely locations.&n;   If dev-&gt;base_addr == 1, always return failure.&n;   If dev-&gt;base_addr == 2, allocate space for the device and return success&n;   (detachable devices only).&n;   */
macro_line|#ifdef HAVE_DEVLIST
multiline_comment|/* Support for a alternate probe manager, which will eliminate the&n;   boilerplate below. */
DECL|variable|netcard_drv
r_struct
id|netdev_entry
id|netcard_drv
op_assign
(brace
l_string|&quot;netcard&quot;
comma
id|netcard_probe1
comma
id|NETCARD_IO_EXTENT
comma
id|netcard_portlist
)brace
suffix:semicolon
macro_line|#else
r_int
DECL|function|netcard_probe
id|netcard_probe
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
id|netcard_probe1
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
id|NETCARD_IO_EXTENT
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|netcard_probe1
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
multiline_comment|/* This is the real probe routine.  Linux has a history of friendly device&n;   probes on the ISA bus.  A good device probes avoids doing writes, and&n;   verifies that the correct device exists and functions.  */
DECL|function|netcard_probe1
r_static
r_int
id|netcard_probe1
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
r_static
r_int
id|version_printed
op_assign
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* For ethernet adaptors the first three octets of the station address contains&n;&t;   the manufacturer&squot;s unique code.  That might be a good probe method.&n;&t;   Ideally you would add additional checks.  */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0
)paren
op_ne
id|SA_ADDR0
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
op_ne
id|SA_ADDR1
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|2
)paren
op_ne
id|SA_ADDR2
)paren
(brace
r_return
id|ENODEV
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
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
op_logical_and
id|version_printed
op_increment
op_eq
l_int|0
)paren
id|printk
c_func
(paren
id|version
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s found at %#3x, &quot;
comma
id|dev-&gt;name
comma
l_string|&quot;network card&quot;
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Fill in the &squot;dev&squot; fields. */
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
multiline_comment|/* Retrieve and print the ethernet address. */
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
id|printk
c_func
(paren
l_string|&quot; %2.2x&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|i
)paren
)paren
suffix:semicolon
macro_line|#ifdef jumpered_interrupts
multiline_comment|/* If this board has jumpered interrupts, snarf the interrupt vector&n;&t;   now.&t; There is no point in waiting since no other device can use&n;&t;   the interrupt, and this marks the irq as busy.&n;&t;   Jumpered interrupts are typically not reported by the boards, and&n;&t;   we must used autoIRQ to find them. */
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
op_minus
l_int|1
)paren
suffix:semicolon
multiline_comment|/* Do nothing: a user-level program will set it. */
r_else
r_if
c_cond
(paren
id|dev-&gt;irq
OL
l_int|2
)paren
(brace
multiline_comment|/* &quot;Auto-IRQ&quot; */
id|autoirq_setup
c_func
(paren
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Trigger an interrupt here. */
id|dev-&gt;irq
op_assign
id|autoirq_report
c_func
(paren
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|net_debug
op_ge
l_int|2
)paren
id|printk
c_func
(paren
l_string|&quot; autoirq is %d&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
r_else
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
multiline_comment|/* Fixup for users that don&squot;t know that IRQ 2 is really IRQ 9,&n;&t; or don&squot;t know which one to set. */
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
(brace
r_int
id|irqval
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|net_interrupt
comma
l_int|0
comma
l_string|&quot;skeleton&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|irqval
)paren
(brace
id|printk
(paren
l_string|&quot;%s: unable to get IRQ %d (irqval=%d).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|dev-&gt;irq
comma
id|irqval
)paren
suffix:semicolon
r_return
id|EAGAIN
suffix:semicolon
)brace
)brace
macro_line|#endif&t;/* jumpered interrupt */
macro_line|#ifdef jumpered_dma
multiline_comment|/* If we use a jumpered DMA channel, that should be probed for and&n;&t;   allocated here as well.  See lance.c for an example. */
r_if
c_cond
(paren
id|dev-&gt;dma
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dev-&gt;dma
comma
l_string|&quot;netcard&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DMA %d allocation failed.&bslash;n&quot;
comma
id|dev-&gt;dma
)paren
suffix:semicolon
r_return
id|EAGAIN
suffix:semicolon
)brace
r_else
id|printk
c_func
(paren
l_string|&quot;, assigned DMA %d.&bslash;n&quot;
comma
id|dev-&gt;dma
)paren
suffix:semicolon
)brace
r_else
(brace
r_int
id|dma_status
comma
id|new_dma_status
suffix:semicolon
multiline_comment|/* Read the DMA channel status registers. */
id|dma_status
op_assign
(paren
(paren
id|inb
c_func
(paren
id|DMA1_STAT_REG
)paren
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)paren
op_or
(paren
id|inb
c_func
(paren
id|DMA2_STAT_REG
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
multiline_comment|/* Trigger a DMA request, perhaps pause a bit. */
id|outw
c_func
(paren
l_int|0x1234
comma
id|ioaddr
op_plus
l_int|8
)paren
suffix:semicolon
multiline_comment|/* Re-read the DMA status registers. */
id|new_dma_status
op_assign
(paren
(paren
id|inb
c_func
(paren
id|DMA1_STAT_REG
)paren
op_rshift
l_int|4
)paren
op_amp
l_int|0x0f
)paren
op_or
(paren
id|inb
c_func
(paren
id|DMA2_STAT_REG
)paren
op_amp
l_int|0xf0
)paren
suffix:semicolon
multiline_comment|/* Eliminate the old and floating requests and DMA4, the cascade. */
id|new_dma_status
op_xor_assign
id|dma_status
suffix:semicolon
id|new_dma_status
op_and_assign
op_complement
l_int|0x10
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|7
suffix:semicolon
id|i
OG
l_int|0
suffix:semicolon
id|i
op_decrement
)paren
r_if
c_cond
(paren
id|test_bit
c_func
(paren
id|new_dma
comma
op_amp
id|new_dma_status
)paren
)paren
(brace
id|dev-&gt;dma
op_assign
id|i
suffix:semicolon
r_break
suffix:semicolon
)brace
r_if
c_cond
(paren
id|i
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;DMA probe failed.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dev-&gt;dma
comma
l_string|&quot;netcard&quot;
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;probed DMA %d allocation failed.&bslash;n&quot;
comma
id|dev-&gt;dma
)paren
suffix:semicolon
r_return
id|EAGAIN
suffix:semicolon
)brace
)brace
macro_line|#endif&t;/* jumpered DMA */
multiline_comment|/* Grab the region so we can find another board if autoIRQ fails. */
id|register_iomem
c_func
(paren
id|ioaddr
comma
id|NETCARD_IO_EXTENT
comma
l_string|&quot;skeleton&quot;
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
id|dev-&gt;get_stats
op_assign
id|net_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
op_amp
id|set_multicast_list
suffix:semicolon
multiline_comment|/* Fill in the fields of the device structure with ethernet values. */
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
multiline_comment|/* Open/initialize the board.  This is called (in the current kernel)&n;   sometime after booting when the &squot;ifconfig&squot; program is run.&n;&n;   This routine should set everything up anew at each open, even&n;   registers that &quot;should&quot; only need to be set once at boot, so that&n;   there is non-reboot way to recover if something goes wrong.&n;   */
r_static
r_int
DECL|function|net_open
id|net_open
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
multiline_comment|/* This is used if the interrupt line can turned off (shared).&n;&t;   See 3c503.c for an example of selecting the IRQ at config-time. */
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
op_amp
id|net_interrupt
comma
l_int|0
comma
l_string|&quot;skeleton&quot;
)paren
)paren
(brace
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
multiline_comment|/* Always snarf the DMA channel after the IRQ, and clean up on failure. */
r_if
c_cond
(paren
id|request_dma
c_func
(paren
id|dev-&gt;dma
comma
l_string|&quot;skeleton ethernet&quot;
)paren
)paren
(brace
id|free_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
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
multiline_comment|/* Reset the hardware here.  Don&squot;t forget to set the station address. */
multiline_comment|/*chipset_init(dev, 1);*/
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
)paren
suffix:semicolon
id|lp-&gt;open_time
op_assign
id|jiffies
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|1
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
r_static
r_int
DECL|function|net_send_packet
id|net_send_packet
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
r_if
c_cond
(paren
id|dev-&gt;tbusy
)paren
(brace
multiline_comment|/* If we get here, some higher level has decided we are broken.&n;&t;&t;   There should really be a &quot;kick me&quot; function call instead. */
r_int
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
id|printk
c_func
(paren
l_string|&quot;%s: transmit timed out, %s?&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|tx_done
c_func
(paren
id|dev
)paren
ques
c_cond
l_string|&quot;IRQ conflict&quot;
suffix:colon
l_string|&quot;network cable problem&quot;
)paren
suffix:semicolon
multiline_comment|/* Try to restart the adaptor. */
id|chipset_init
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
multiline_comment|/* If some higher layer thinks we&squot;ve missed an tx-done interrupt&n;&t;   we are passed NULL. Caution: dev_tint() handles the cli()/sti()&n;&t;   itself. */
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
multiline_comment|/* Block a timer-based transmit from overlapping.  This could better be&n;&t;   done with atomic_swap(1, dev-&gt;tbusy), but set_bit() works as well. */
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
id|printk
c_func
(paren
l_string|&quot;%s: Transmitter access conflict.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_else
(brace
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
id|hardware_send_packet
c_func
(paren
id|ioaddr
comma
id|buf
comma
id|length
)paren
suffix:semicolon
id|dev-&gt;trans_start
op_assign
id|jiffies
suffix:semicolon
)brace
id|dev_kfree_skb
(paren
id|skb
comma
id|FREE_WRITE
)paren
suffix:semicolon
multiline_comment|/* You might need to clean up and record Tx statistics here. */
r_if
c_cond
(paren
id|inw
c_func
(paren
id|ioaddr
)paren
op_eq
multiline_comment|/*RU*/
l_int|81
)paren
id|lp-&gt;stats.tx_aborted_errors
op_increment
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
comma
id|status
comma
id|boguscount
op_assign
l_int|0
suffix:semicolon
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;net_interrupt(): irq %d for unknown device.&bslash;n&quot;
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
l_int|0
)paren
suffix:semicolon
r_do
(brace
r_if
c_cond
(paren
id|status
multiline_comment|/*&amp; RX_INTR*/
)paren
(brace
multiline_comment|/* Got a packet(s). */
id|net_rx
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|status
multiline_comment|/*&amp; TX_INTR*/
)paren
(brace
id|lp-&gt;stats.tx_packets
op_increment
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
multiline_comment|/* Inform upper layers. */
)brace
r_if
c_cond
(paren
id|status
multiline_comment|/*&amp; COUNTERS_INTR*/
)paren
(brace
multiline_comment|/* Increment the appropriate &squot;localstats&squot; field. */
id|lp-&gt;stats.tx_window_errors
op_increment
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
op_increment
id|boguscount
OL
l_int|20
)paren
suffix:semicolon
id|dev-&gt;interrupt
op_assign
l_int|0
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/* We have a good packet(s), get it/them out of the buffers. */
r_static
r_void
DECL|function|net_rx
id|net_rx
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
id|boguscount
op_assign
l_int|10
suffix:semicolon
r_do
(brace
r_int
id|status
op_assign
id|inw
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_int
id|pkt_len
op_assign
id|inw
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|pkt_len
op_eq
l_int|0
)paren
multiline_comment|/* Read all the frames? */
r_break
suffix:semicolon
multiline_comment|/* Done for now */
r_if
c_cond
(paren
id|status
op_amp
l_int|0x40
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
l_int|0x20
)paren
id|lp-&gt;stats.rx_frame_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x10
)paren
id|lp-&gt;stats.rx_over_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x08
)paren
id|lp-&gt;stats.rx_crc_errors
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|status
op_amp
l_int|0x04
)paren
id|lp-&gt;stats.rx_fifo_errors
op_increment
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Malloc up new buffer. */
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
id|pkt_len
comma
id|GFP_ATOMIC
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
r_break
suffix:semicolon
)brace
id|skb-&gt;len
op_assign
id|pkt_len
suffix:semicolon
id|skb-&gt;dev
op_assign
id|dev
suffix:semicolon
multiline_comment|/* &squot;skb-&gt;data&squot; points to the start of sk_buff data area. */
id|memcpy
c_func
(paren
id|skb-&gt;data
comma
(paren
r_void
op_star
)paren
id|dev-&gt;rmem_start
comma
id|pkt_len
)paren
suffix:semicolon
multiline_comment|/* or */
id|insw
c_func
(paren
id|ioaddr
comma
id|skb-&gt;data
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
)brace
r_while
c_loop
(paren
op_decrement
id|boguscount
)paren
suffix:semicolon
multiline_comment|/* If any worth-while packets have been received, dev_rint()&n;&t;   has done a mark_bh(NET_BH) for us and will work on them&n;&t;   when we get to the bottom-half routine. */
r_return
suffix:semicolon
)brace
multiline_comment|/* The inverse routine to net_open(). */
r_static
r_int
DECL|function|net_close
id|net_close
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
id|lp-&gt;open_time
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|1
suffix:semicolon
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Flush the Tx and disable Rx here. */
id|disable_dma
c_func
(paren
id|dev-&gt;dma
)paren
suffix:semicolon
multiline_comment|/* If not IRQ or DMA jumpered, free up the line. */
id|outw
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|0
)paren
suffix:semicolon
multiline_comment|/* Release the physical interrupt line. */
id|free_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|free_dma
c_func
(paren
id|dev-&gt;dma
)paren
suffix:semicolon
id|irq2dev_map
(braket
id|dev-&gt;irq
)braket
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Update the statistics here. */
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Get the current statistics.&t;This may be called with the card open or&n;   closed. */
r_static
r_struct
id|enet_statistics
op_star
DECL|function|net_get_stats
id|net_get_stats
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
id|cli
c_func
(paren
)paren
suffix:semicolon
multiline_comment|/* Update the statistics from the device registers. */
id|lp-&gt;stats.rx_missed_errors
op_assign
id|inw
c_func
(paren
id|ioaddr
op_plus
l_int|1
)paren
suffix:semicolon
id|sti
c_func
(paren
)paren
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
)paren
(brace
id|outw
c_func
(paren
l_int|69
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Enable promiscuous mode */
)brace
r_else
id|outw
c_func
(paren
l_int|99
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Disable promiscuous mode, use normal mode */
)brace
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -I/usr/src/linux/net/inet -Wall -Wstrict-prototypes -O6 -m486 -c skeleton.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  tab-width: 4&n; * End:&n; */
eof
