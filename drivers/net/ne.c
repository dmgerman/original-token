multiline_comment|/* ne.c: A general non-shared-memory NS8390 ethernet driver for linux. */
multiline_comment|/*&n;    Written 1992,1993 by Donald Becker.&n;&n;    Copyright 1993 United States Government as represented by the&n;    Director, National Security Agency.  This software may be used and&n;    distributed according to the terms of the GNU Public License,&n;    incorporated herein by reference.&n;&n;    This driver should work with many 8390-based ethernet boards.  Currently&n;    it support the NE1000, NE2000, clones, and some Cabletron products.&n;&n;    The Author may be reached as becker@super.org or&n;    C/O Supercomputing Research Ctr., 17100 Science Dr., Bowie MD 20715&n;*/
multiline_comment|/* Routines for the NatSemi-based designs (NE[12]000). */
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;ne.c:v0.99-13s 11/17/93 Donald Becker (becker@super.org)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/config.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#ifndef port_read
macro_line|#include &quot;iow.h&quot;
macro_line|#endif
macro_line|#include &quot;dev.h&quot;
macro_line|#include &quot;8390.h&quot;
DECL|macro|NE_BASE
mdefine_line|#define NE_BASE&t; (dev-&gt;base_addr)
DECL|macro|NE_CMD
mdefine_line|#define NE_CMD&t; &t;0x00
DECL|macro|NE_DATAPORT
mdefine_line|#define NE_DATAPORT&t;0x10&t;/* NatSemi-defined port window offset. */
DECL|macro|NE_RESET
mdefine_line|#define NE_RESET&t;0x1f&t;/* Issue a read to reset, a write to clear. */
DECL|macro|NE1SM_START_PG
mdefine_line|#define NE1SM_START_PG&t;0x20&t;/* First page of TX buffer */
DECL|macro|NE1SM_STOP_PG
mdefine_line|#define NE1SM_STOP_PG &t;0x40&t;/* Last page +1 of RX ring */
DECL|macro|NESM_START_PG
mdefine_line|#define NESM_START_PG&t;0x40&t;/* First page of TX buffer */
DECL|macro|NESM_STOP_PG
mdefine_line|#define NESM_STOP_PG&t;0x80&t;/* Last page +1 of RX ring */
r_int
id|ne_probe
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
id|neprobe1
c_func
(paren
r_int
id|ioaddr
comma
r_struct
id|device
op_star
id|dev
comma
r_int
id|verbose
)paren
suffix:semicolon
r_static
r_void
id|ne_reset_8390
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
id|ne_block_input
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|count
comma
r_char
op_star
id|buf
comma
r_int
id|ring_offset
)paren
suffix:semicolon
r_static
r_void
id|ne_block_output
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_const
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_const
r_int
id|start_page
)paren
suffix:semicolon
"&f;"
multiline_comment|/*  Probe for various non-shared-memory ethercards.&n;&n;   NEx000-clone boards have a Station Address PROM (SAPROM) in the packet&n;   buffer memory space.  NE2000 clones have 0x57,0x57 in bytes 0x0e,0x0f of&n;   the SAPROM, while other supposed NE2000 clones must be detected by their&n;   SA prefix.&n;&n;   Reading the SAPROM from a word-wide card with the 8390 set in byte-wide&n;   mode results in doubled values, which can be detected and compansated for.&n;&n;   The probe is also responsible for initializing the card and filling&n;   in the &squot;dev&squot; and &squot;ei_status&squot; structures.&n;&n;   We use the minimum memory size for some ethercard product lines, iff we can&squot;t&n;   distinguish models.  You can increase the packet buffer size by setting&n;   PACKETBUF_MEMSIZE.  Reported Cabletron packet buffer locations are:&n;&t;E1010   starts at 0x100 and ends at 0x2000.&n;&t;E1010-x starts at 0x100 and ends at 0x8000. (&quot;-x&quot; means &quot;more memory&quot;)&n;&t;E2010&t; starts at 0x100 and ends at 0x4000.&n;&t;E2010-x starts at 0x100 and ends at 0xffff.  */
DECL|function|ne_probe
r_int
id|ne_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
op_star
id|port
comma
id|ports
(braket
)braket
op_assign
(brace
l_int|0x300
comma
l_int|0x280
comma
l_int|0x320
comma
l_int|0x340
comma
l_int|0x360
comma
l_int|0
)brace
suffix:semicolon
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|ioaddr
OL
l_int|0
)paren
r_return
id|ENXIO
suffix:semicolon
multiline_comment|/* Don&squot;t probe at all. */
r_if
c_cond
(paren
id|ioaddr
OG
l_int|0x100
)paren
r_return
op_logical_neg
id|neprobe1
c_func
(paren
id|ioaddr
comma
id|dev
comma
l_int|1
)paren
suffix:semicolon
r_for
c_loop
(paren
id|port
op_assign
op_amp
id|ports
(braket
l_int|0
)braket
suffix:semicolon
op_star
id|port
suffix:semicolon
id|port
op_increment
)paren
(brace
macro_line|#ifdef HAVE_PORTRESERVE
r_if
c_cond
(paren
id|check_region
c_func
(paren
op_star
id|port
comma
l_int|32
)paren
)paren
r_continue
suffix:semicolon
macro_line|#endif
r_if
c_cond
(paren
id|inb_p
c_func
(paren
op_star
id|port
)paren
op_ne
l_int|0xff
op_logical_and
id|neprobe1
c_func
(paren
op_star
id|port
comma
id|dev
comma
l_int|0
)paren
)paren
(brace
id|dev-&gt;base_addr
op_assign
op_star
id|port
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
r_return
id|ENODEV
suffix:semicolon
)brace
DECL|function|neprobe1
r_static
r_int
id|neprobe1
c_func
(paren
r_int
id|ioaddr
comma
r_struct
id|device
op_star
id|dev
comma
r_int
id|verbose
)paren
(brace
r_int
id|i
suffix:semicolon
r_int
r_char
id|SA_prom
(braket
l_int|32
)braket
suffix:semicolon
r_int
id|wordlength
op_assign
l_int|2
suffix:semicolon
r_char
op_star
id|name
suffix:semicolon
r_int
id|start_page
comma
id|stop_page
suffix:semicolon
r_int
id|neX000
comma
id|ctron
comma
id|dlink
suffix:semicolon
r_int
id|reg0
op_assign
id|inb
c_func
(paren
id|ioaddr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|reg0
op_eq
l_int|0xFF
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Do a quick preliminary check that we have a 8390. */
(brace
r_int
id|regd
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE1
op_plus
id|E8390_STOP
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|regd
op_assign
id|inb_p
c_func
(paren
id|ioaddr
op_plus
l_int|0x0d
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0xff
comma
id|ioaddr
op_plus
l_int|0x0d
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
comma
id|ioaddr
op_plus
id|E8390_CMD
)paren
suffix:semicolon
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|EN0_COUNTER0
)paren
suffix:semicolon
multiline_comment|/* Clear the counter by reading. */
r_if
c_cond
(paren
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|EN0_COUNTER0
)paren
op_ne
l_int|0
)paren
(brace
id|outb_p
c_func
(paren
id|reg0
comma
id|ioaddr
)paren
suffix:semicolon
id|outb
c_func
(paren
id|regd
comma
id|ioaddr
op_plus
l_int|0x0d
)paren
suffix:semicolon
multiline_comment|/* Restore the old values. */
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|printk
c_func
(paren
l_string|&quot;NE*000 ethercard probe at %#3x:&quot;
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Read the 16 bytes of station address prom, returning 1 for&n;       an eight-bit interface and 2 for a 16-bit interface.&n;       We must first initialize registers, similar to NS8390_init(eifdev, 0).&n;       We can&squot;t reliably read the SAPROM address without this.&n;       (I learned the hard way!). */
(brace
r_struct
(brace
r_int
r_char
id|value
comma
id|offset
suffix:semicolon
)brace
id|program_seq
(braket
)braket
op_assign
(brace
(brace
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_STOP
comma
id|E8390_CMD
)brace
comma
multiline_comment|/* Select page 0*/
(brace
l_int|0x48
comma
id|EN0_DCFG
)brace
comma
multiline_comment|/* Set byte-wide (0x48) access. */
(brace
l_int|0x00
comma
id|EN0_RCNTLO
)brace
comma
multiline_comment|/* Clear the count regs. */
(brace
l_int|0x00
comma
id|EN0_RCNTHI
)brace
comma
(brace
l_int|0x00
comma
id|EN0_IMR
)brace
comma
multiline_comment|/* Mask completion irq. */
(brace
l_int|0xFF
comma
id|EN0_ISR
)brace
comma
(brace
id|E8390_RXOFF
comma
id|EN0_RXCR
)brace
comma
multiline_comment|/* 0x20  Set to monitor */
(brace
id|E8390_TXOFF
comma
id|EN0_TXCR
)brace
comma
multiline_comment|/* 0x02  and loopback mode. */
(brace
l_int|32
comma
id|EN0_RCNTLO
)brace
comma
(brace
l_int|0x00
comma
id|EN0_RCNTHI
)brace
comma
(brace
l_int|0x00
comma
id|EN0_RSARLO
)brace
comma
multiline_comment|/* DMA starting at 0x0000. */
(brace
l_int|0x00
comma
id|EN0_RSARHI
)brace
comma
(brace
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|E8390_CMD
)brace
comma
)brace
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
r_sizeof
(paren
id|program_seq
)paren
op_div
r_sizeof
(paren
id|program_seq
(braket
l_int|0
)braket
)paren
suffix:semicolon
id|i
op_increment
)paren
id|outb_p
c_func
(paren
id|program_seq
(braket
id|i
)braket
dot
id|value
comma
id|ioaddr
op_plus
id|program_seq
(braket
id|i
)braket
dot
id|offset
)paren
suffix:semicolon
)brace
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|32
multiline_comment|/*sizeof(SA_prom)*/
suffix:semicolon
id|i
op_add_assign
l_int|2
)paren
(brace
id|SA_prom
(braket
id|i
)braket
op_assign
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
id|SA_prom
(braket
id|i
op_plus
l_int|1
)braket
op_assign
id|inb_p
c_func
(paren
id|ioaddr
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
r_if
c_cond
(paren
id|SA_prom
(braket
id|i
)braket
op_ne
id|SA_prom
(braket
id|i
op_plus
l_int|1
)braket
)paren
id|wordlength
op_assign
l_int|1
suffix:semicolon
)brace
r_if
c_cond
(paren
id|wordlength
op_eq
l_int|2
)paren
(brace
multiline_comment|/* We must set the 8390 for word mode, AND RESET IT. */
r_int
id|tmp
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x49
comma
id|ioaddr
op_plus
id|EN0_DCFG
)paren
suffix:semicolon
id|tmp
op_assign
id|inb_p
c_func
(paren
id|NE_BASE
op_plus
id|NE_RESET
)paren
suffix:semicolon
id|outb
c_func
(paren
id|tmp
comma
id|NE_BASE
op_plus
id|NE_RESET
)paren
suffix:semicolon
multiline_comment|/* Un-double the SA_prom values. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
l_int|16
suffix:semicolon
id|i
op_increment
)paren
id|SA_prom
(braket
id|i
)braket
op_assign
id|SA_prom
(braket
id|i
op_plus
id|i
)braket
suffix:semicolon
)brace
macro_line|#if defined(show_all_SAPROM)
multiline_comment|/* If your ethercard isn&squot;t detected define this to see the SA_PROM. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
r_sizeof
(paren
id|SA_prom
)paren
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %2.2x&quot;
comma
id|SA_prom
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#else
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|i
OL
id|ETHER_ADDR_LEN
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
id|SA_prom
(braket
id|i
)braket
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; %2.2x&quot;
comma
id|SA_prom
(braket
id|i
)braket
)paren
suffix:semicolon
)brace
macro_line|#endif
id|neX000
op_assign
(paren
id|SA_prom
(braket
l_int|14
)braket
op_eq
l_int|0x57
op_logical_and
id|SA_prom
(braket
l_int|15
)braket
op_eq
l_int|0x57
)paren
suffix:semicolon
id|ctron
op_assign
(paren
id|SA_prom
(braket
l_int|0
)braket
op_eq
l_int|0x00
op_logical_and
id|SA_prom
(braket
l_int|1
)braket
op_eq
l_int|0x00
op_logical_and
id|SA_prom
(braket
l_int|2
)braket
op_eq
l_int|0x1d
)paren
suffix:semicolon
id|dlink
op_assign
(paren
id|SA_prom
(braket
l_int|0
)braket
op_eq
l_int|0x00
op_logical_and
id|SA_prom
(braket
l_int|1
)braket
op_eq
l_int|0xDE
op_logical_and
id|SA_prom
(braket
l_int|2
)braket
op_eq
l_int|0x01
)paren
suffix:semicolon
multiline_comment|/* Set up the rest of the parameters. */
r_if
c_cond
(paren
id|neX000
op_logical_or
id|dlink
)paren
(brace
r_if
c_cond
(paren
id|wordlength
op_eq
l_int|2
)paren
(brace
id|name
op_assign
id|dlink
ques
c_cond
l_string|&quot;DE200&quot;
suffix:colon
l_string|&quot;NE2000&quot;
suffix:semicolon
id|start_page
op_assign
id|NESM_START_PG
suffix:semicolon
id|stop_page
op_assign
id|NESM_STOP_PG
suffix:semicolon
)brace
r_else
(brace
id|name
op_assign
id|dlink
ques
c_cond
l_string|&quot;DE100&quot;
suffix:colon
l_string|&quot;NE1000&quot;
suffix:semicolon
id|start_page
op_assign
id|NE1SM_START_PG
suffix:semicolon
id|stop_page
op_assign
id|NE1SM_STOP_PG
suffix:semicolon
)brace
)brace
r_else
r_if
c_cond
(paren
id|ctron
)paren
(brace
id|name
op_assign
l_string|&quot;Cabletron&quot;
suffix:semicolon
id|start_page
op_assign
l_int|0x01
suffix:semicolon
id|stop_page
op_assign
(paren
id|wordlength
op_eq
l_int|2
)paren
ques
c_cond
l_int|0x40
suffix:colon
l_int|0x20
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; not found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
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
l_int|0
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x50
comma
id|ioaddr
op_plus
id|EN0_IMR
)paren
suffix:semicolon
multiline_comment|/* Enable one interrupt. */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Trigger it... */
id|outb_p
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
id|EN0_IMR
)paren
suffix:semicolon
multiline_comment|/* Mask it again. */
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
id|ei_debug
OG
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
multiline_comment|/* Fixup for users that don&squot;t know that IRQ 2 is really IRQ 9,&n;&t;   or don&squot;t know which one to set. */
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* Snarf the interrupt now.  There&squot;s no point in waiting since we cannot&n;       share and the board will usually be enabled. */
(brace
r_int
id|irqval
op_assign
id|irqaction
(paren
id|dev-&gt;irq
comma
op_amp
id|ei_sigaction
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
l_string|&quot; unable to get IRQ %d (irqval=%d).&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|irqval
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
)brace
id|dev-&gt;base_addr
op_assign
id|ioaddr
suffix:semicolon
macro_line|#ifdef HAVE_PORTRESERVE
id|snarf_region
c_func
(paren
id|ioaddr
comma
l_int|32
)paren
suffix:semicolon
macro_line|#endif
id|ethdev_init
c_func
(paren
id|dev
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s: %s found at %#x, using IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|name
comma
id|ioaddr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
id|version
)paren
suffix:semicolon
id|ei_status.name
op_assign
id|name
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|start_page
suffix:semicolon
id|ei_status.stop_page
op_assign
id|stop_page
suffix:semicolon
id|ei_status.word16
op_assign
(paren
id|wordlength
op_eq
l_int|2
)paren
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|start_page
op_plus
id|TX_PAGES
suffix:semicolon
macro_line|#ifdef PACKETBUF_MEMSIZE
multiline_comment|/* Allow the packet buffer size to be overridden by know-it-alls. */
id|ei_status.stop_page
op_assign
id|ei_status.tx_start_page
op_plus
id|PACKETBUF_MEMSIZE
suffix:semicolon
macro_line|#endif
id|ei_status.reset_8390
op_assign
op_amp
id|ne_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ne_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ne_block_output
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
r_return
id|dev-&gt;base_addr
suffix:semicolon
)brace
multiline_comment|/* Hard reset the card.  This used to pause for the same period that a&n;   8390 reset command required, but that shouldn&squot;t be necessary. */
r_static
r_void
DECL|function|ne_reset_8390
id|ne_reset_8390
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|tmp
op_assign
id|inb_p
c_func
(paren
id|NE_BASE
op_plus
id|NE_RESET
)paren
suffix:semicolon
r_int
id|reset_start_time
op_assign
id|jiffies
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;resetting the 8390 t=%d...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outb_p
c_func
(paren
id|tmp
comma
id|NE_BASE
op_plus
id|NE_RESET
)paren
suffix:semicolon
multiline_comment|/* This check _should_not_ be necessary, omit eventually. */
r_while
c_loop
(paren
(paren
id|inb_p
c_func
(paren
id|NE_BASE
op_plus
id|EN0_ISR
)paren
op_amp
id|ENISR_RESET
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|jiffies
op_minus
id|reset_start_time
OG
l_int|2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: ne_reset_8390() did not complete.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
)brace
multiline_comment|/* Block input and output, similar to the Crynwr packet driver.  If you&n;   porting to a new ethercard look at the packet driver source for hints.&n;   The NEx000 doesn&squot;t share it on-board packet memory -- you have to put&n;   the packet out through the &quot;remote DMA&quot; dataport using outb. */
r_static
r_int
DECL|function|ne_block_input
id|ne_block_input
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|count
comma
r_char
op_star
id|buf
comma
r_int
id|ring_offset
)paren
(brace
r_int
id|xfer_count
op_assign
id|count
suffix:semicolon
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
r_if
c_cond
(paren
id|ei_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne_block_input.&quot;
l_string|&quot;[DMAstat:%1x][irqlock:%1x]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x01
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ring_offset
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ring_offset
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
id|port_read
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
r_if
c_cond
(paren
id|count
op_amp
l_int|0x01
)paren
id|buf
(braket
id|count
op_minus
l_int|1
)braket
op_assign
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
)paren
comma
id|xfer_count
op_increment
suffix:semicolon
)brace
r_else
(brace
id|port_read_b
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* This was for the ALPHA version only, but enough people have&n;       encountering problems that it is still here.  If you see&n;       this message you either 1) have an slightly imcompatible clone&n;       or 2) have noise/speed problems with your bus. */
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
(brace
multiline_comment|/* DMA termination address check... */
r_int
id|addr
comma
id|tries
op_assign
l_int|20
suffix:semicolon
r_do
(brace
multiline_comment|/* DON&squot;T check for &squot;inb_p(EN0_ISR) &amp; ENISR_RDC&squot; here&n;&t;       -- it&squot;s broken! Check the &quot;DMA&quot; address instead. */
r_int
id|high
op_assign
id|inb_p
c_func
(paren
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
r_int
id|low
op_assign
id|inb_p
c_func
(paren
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|high
op_lshift
l_int|8
)paren
op_plus
id|low
suffix:semicolon
r_if
c_cond
(paren
(paren
(paren
id|ring_offset
op_plus
id|xfer_count
)paren
op_amp
l_int|0xff
)paren
op_eq
id|low
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|tries
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tries
op_le
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: RX transfer address mismatch,&quot;
l_string|&quot;%#4.4x (expected) vs. %#4.4x (actual).&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ring_offset
op_plus
id|xfer_count
comma
id|addr
)paren
suffix:semicolon
)brace
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
r_return
id|ring_offset
op_plus
id|count
suffix:semicolon
)brace
r_static
r_void
DECL|function|ne_block_output
id|ne_block_output
c_func
(paren
r_struct
id|device
op_star
id|dev
comma
r_int
id|count
comma
r_const
r_int
r_char
op_star
id|buf
comma
r_const
r_int
id|start_page
)paren
(brace
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
r_int
id|nic_base
op_assign
id|NE_BASE
suffix:semicolon
multiline_comment|/* Round the count up for word writes.  Do we need to do this?&n;       What effect will an odd byte count have on the 8390?&n;       I should check someday. */
r_if
c_cond
(paren
id|ei_status.word16
op_logical_and
(paren
id|count
op_amp
l_int|0x01
)paren
)paren
id|count
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
r_if
c_cond
(paren
id|ei_debug
OG
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne_block_output.&quot;
l_string|&quot;[DMAstat:%1x][irqlock:%1x]&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|ei_status.dmaing
comma
id|ei_status.irqlock
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
id|ei_status.dmaing
op_or_assign
l_int|0x02
suffix:semicolon
multiline_comment|/* We should already be in page 0, but to be safe... */
id|outb_p
c_func
(paren
id|E8390_PAGE0
op_plus
id|E8390_START
op_plus
id|E8390_NODMA
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
id|retry
suffix:colon
macro_line|#if defined(rw_bugfix)
multiline_comment|/* Handle the read-before-write bug the same way as the&n;       Crynwr packet driver -- the NatSemi method doesn&squot;t work.&n;       Actually this doesn&squot;t aways work either, but if you have&n;       problems with your NEx000 this is better than nothing! */
id|outb_p
c_func
(paren
l_int|0x42
comma
id|nic_base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|nic_base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x42
comma
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_RREAD
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
multiline_comment|/* Make certain that the dummy read has occured. */
id|SLOW_DOWN_IO
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
macro_line|#endif  /* rw_bugfix */
multiline_comment|/* Now the normal output. */
id|outb_p
c_func
(paren
id|count
op_amp
l_int|0xff
comma
id|nic_base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|count
op_rshift
l_int|8
comma
id|nic_base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0x00
comma
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|start_page
comma
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|E8390_RWRITE
op_plus
id|E8390_START
comma
id|nic_base
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ei_status.word16
)paren
(brace
id|port_write
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|buf
comma
id|count
op_rshift
l_int|1
)paren
suffix:semicolon
)brace
r_else
(brace
id|port_write_b
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
multiline_comment|/* This was for the ALPHA version only, but enough people have&n;       encountering problems that it is still here. */
r_if
c_cond
(paren
id|ei_debug
OG
l_int|1
)paren
(brace
multiline_comment|/* DMA termination address check... */
r_int
id|addr
comma
id|tries
op_assign
l_int|20
suffix:semicolon
r_do
(brace
multiline_comment|/* DON&squot;T check for &squot;inb_p(EN0_ISR) &amp; ENISR_RDC&squot; here&n;&t;       -- it&squot;s broken! Check the &quot;DMA&quot; address instead. */
r_int
id|high
op_assign
id|inb_p
c_func
(paren
id|nic_base
op_plus
id|EN0_RSARHI
)paren
suffix:semicolon
r_int
id|low
op_assign
id|inb_p
c_func
(paren
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
id|addr
op_assign
(paren
id|high
op_lshift
l_int|8
)paren
op_plus
id|low
suffix:semicolon
r_if
c_cond
(paren
(paren
id|start_page
op_lshift
l_int|8
)paren
op_plus
id|count
op_eq
id|addr
)paren
r_break
suffix:semicolon
)brace
r_while
c_loop
(paren
op_decrement
id|tries
OG
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
id|tries
op_le
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: Tx packet transfer address mismatch,&quot;
l_string|&quot;%#4.4x (expected) vs. %#4.4x (actual).&bslash;n&quot;
comma
id|dev-&gt;name
comma
(paren
id|start_page
op_lshift
l_int|8
)paren
op_plus
id|count
comma
id|addr
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retries
op_increment
op_eq
l_int|0
)paren
r_goto
id|retry
suffix:semicolon
)brace
)brace
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x02
suffix:semicolon
r_return
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -DKERNEL -Wall -O6 -fomit-frame-pointer -I/usr/src/linux/net/tcp -c ne.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; * End:&n; */
eof