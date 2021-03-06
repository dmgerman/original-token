multiline_comment|/* ne2.c: A NE/2 Ethernet Driver for Linux. */
multiline_comment|/*&n;   Based on the NE2000 driver written by Donald Becker (1992-94).&n;   modified by Wim Dumon (Apr 1996)&n;&n;   This software may be used and distributed according to the terms&n;   of the GNU Public License, incorporated herein by reference.&n;&n;   The author may be reached as wimpie@linux.cc.kuleuven.ac.be&n;&n;   Currently supported: NE/2&n;   This patch was never tested on other MCA-ethernet adapters, but it&n;   might work. Just give it a try and let me know if you have problems.&n;   Also mail me if it really works, please!&n;&n;   Changelog:&n;   Mon Feb  3 16:26:02 MET 1997&n;   - adapted the driver to work with the 2.1.25 kernel&n;   - multiple ne2 support (untested)&n;   - module support (untested)&n;&n;   Fri Aug 28 00:18:36 CET 1998 (David Weinehall)&n;   - fixed a few minor typos&n;   - made the MODULE_PARM conditional (it only works with the v2.1.x kernels)&n;   - fixed the module support (Now it&squot;s working...)&n;&n;   Mon Sep  7 19:01:44 CET 1998 (David Weinehall)&n;   - added support for Arco Electronics AE/2-card (experimental)&n;&n;   Mon Sep 14 09:53:42 CET 1998 (David Weinehall)&n;   - added support for Compex ENET-16MC/P (experimental) &n;&n;   Tue Sep 15 16:21:12 CET 1998 (David Weinehall, Magnus Jonsson, Tomas Ogren)&n;   - Miscellaneous bugfixes&n;&n;   Tue Sep 19 16:21:12 CET 1998 (Magnus Jonsson)&n;   - Cleanup&n;&n;   Wed Sep 23 14:33:34 CET 1998 (David Weinehall)&n;   - Restructuring and rewriting for v2.1.x compliance&n;&n;   Wed Oct 14 17:19:21 CET 1998 (David Weinehall)&n;   - Added code that unregisters irq and proc-info&n;   - Version# bump&n;&n;   Mon Nov 16 15:28:23 CET 1998 (Wim Dumon)&n;   - pass &squot;dev&squot; as last parameter of request_irq in stead of &squot;NULL&squot;   &n;   &n;   *    WARNING&n;&t;-------&n;&t;This is alpha-test software.  It is not guaranteed to work. As a&n;&t;matter of fact, I&squot;m quite sure there are *LOTS* of bugs in here. I&n;&t;would like to hear from you if you use this driver, even if it works.&n;&t;If it doesn&squot;t work, be sure to send me a mail with the problems !&n;*/
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;ne2.c:v0.91 Nov 16 1998 Wim Dumon &lt;wimpie@kotnet.org&gt;&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/version.h&gt;
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
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/mca.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
macro_line|#include &quot;8390.h&quot;
multiline_comment|/* Some defines that people can play with if so inclined. */
multiline_comment|/* Do we perform extra sanity checks on stuff ? */
multiline_comment|/* #define NE_SANITY_CHECK */
multiline_comment|/* Do we implement the read before write bugfix ? */
multiline_comment|/* #define NE_RW_BUGFIX */
multiline_comment|/* Do we have a non std. amount of memory? (in units of 256 byte pages) */
multiline_comment|/* #define PACKETBUF_MEMSIZE&t;0x40 */
multiline_comment|/* ---- No user-serviceable parts below ---- */
DECL|macro|NE_BASE
mdefine_line|#define NE_BASE&t; (dev-&gt;base_addr)
DECL|macro|NE_CMD
mdefine_line|#define NE_CMD&t; &t;0x00
DECL|macro|NE_DATAPORT
mdefine_line|#define NE_DATAPORT&t;0x10&t;/* NatSemi-defined port window offset. */
DECL|macro|NE_RESET
mdefine_line|#define NE_RESET&t;0x20&t;/* Issue a read to reset, a write to clear. */
DECL|macro|NE_IO_EXTENT
mdefine_line|#define NE_IO_EXTENT&t;0x30
DECL|macro|NE1SM_START_PG
mdefine_line|#define NE1SM_START_PG&t;0x20&t;/* First page of TX buffer */
DECL|macro|NE1SM_STOP_PG
mdefine_line|#define NE1SM_STOP_PG &t;0x40&t;/* Last page +1 of RX ring */
DECL|macro|NESM_START_PG
mdefine_line|#define NESM_START_PG&t;0x40&t;/* First page of TX buffer */
DECL|macro|NESM_STOP_PG
mdefine_line|#define NESM_STOP_PG&t;0x80&t;/* Last page +1 of RX ring */
multiline_comment|/* From the .ADF file: */
DECL|variable|__initdata
r_static
r_int
r_int
id|addresses
(braket
l_int|7
)braket
id|__initdata
op_assign
(brace
l_int|0x1000
comma
l_int|0x2020
comma
l_int|0x8020
comma
l_int|0xa0a0
comma
l_int|0xb0b0
comma
l_int|0xc0c0
comma
l_int|0xc3d0
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
id|irqs
(braket
l_int|4
)braket
id|__initdata
op_assign
(brace
l_int|3
comma
l_int|4
comma
l_int|5
comma
l_int|9
)brace
suffix:semicolon
DECL|struct|ne2_adapters_t
r_struct
id|ne2_adapters_t
(brace
DECL|member|id
r_int
r_int
id|id
suffix:semicolon
DECL|member|name
r_char
op_star
id|name
suffix:semicolon
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_struct
id|ne2_adapters_t
id|ne2_adapters
(braket
)braket
id|__initdata
op_assign
(brace
(brace
l_int|0x6354
comma
l_string|&quot;Arco Ethernet Adapter AE/2&quot;
)brace
comma
(brace
l_int|0x70DE
comma
l_string|&quot;Compex ENET-16 MC/P&quot;
)brace
comma
(brace
l_int|0x7154
comma
l_string|&quot;Novell Ethernet Adapter NE/2&quot;
)brace
comma
(brace
l_int|0x0000
comma
l_int|NULL
)brace
)brace
suffix:semicolon
r_extern
r_int
id|netcard_probe
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
id|ne2_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|slot
)paren
suffix:semicolon
r_static
r_int
id|ne_open
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
id|ne_close
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
id|ne_reset_8390
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
id|ne_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
suffix:semicolon
r_static
r_void
id|ne_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
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
id|net_device
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
multiline_comment|/*&n; * Note that at boot, this probe only picks up one card at a time.&n; */
DECL|function|ne2_probe
r_int
id|__init
id|ne2_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_static
r_int
id|current_mca_slot
op_assign
op_minus
l_int|1
suffix:semicolon
r_int
id|i
suffix:semicolon
r_int
id|adapter_found
op_assign
l_int|0
suffix:semicolon
id|SET_MODULE_OWNER
c_func
(paren
id|dev
)paren
suffix:semicolon
multiline_comment|/* Do not check any supplied i/o locations. &n;&t;   POS registers usually don&squot;t fail :) */
multiline_comment|/* MCA cards have POS registers.  &n;&t;   Autodetecting MCA cards is extremely simple. &n;&t;   Just search for the card. */
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
(paren
id|ne2_adapters
(braket
id|i
)braket
dot
id|name
op_ne
l_int|NULL
)paren
op_logical_and
op_logical_neg
id|adapter_found
suffix:semicolon
id|i
op_increment
)paren
(brace
id|current_mca_slot
op_assign
id|mca_find_unused_adapter
c_func
(paren
id|ne2_adapters
(braket
id|i
)braket
dot
id|id
comma
l_int|0
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|current_mca_slot
op_ne
id|MCA_NOTFOUND
)paren
op_logical_and
op_logical_neg
id|adapter_found
)paren
(brace
id|mca_set_adapter_name
c_func
(paren
id|current_mca_slot
comma
id|ne2_adapters
(braket
id|i
)braket
dot
id|name
)paren
suffix:semicolon
id|mca_mark_as_used
c_func
(paren
id|current_mca_slot
)paren
suffix:semicolon
r_return
id|ne2_probe1
c_func
(paren
id|dev
comma
id|current_mca_slot
)paren
suffix:semicolon
)brace
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|ne2_procinfo
r_static
r_int
id|ne2_procinfo
c_func
(paren
r_char
op_star
id|buf
comma
r_int
id|slot
comma
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
id|len
op_assign
l_int|0
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;The NE/2 Ethernet Adapter&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Driver written by Wim Dumon &quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;&lt;wimpie@kotnet.org&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Modified by &quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;David Weinehall &lt;tao@acc.umu.se&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;and by Magnus Jonsson &lt;bigfoot@acc.umu.se&gt;&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Based on the original NE2000 drivers&bslash;n&quot;
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;Base IO: %#x&bslash;n&quot;
comma
(paren
r_int
r_int
)paren
id|dev-&gt;base_addr
)paren
suffix:semicolon
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;IRQ    : %d&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
DECL|macro|HW_ADDR
mdefine_line|#define HW_ADDR(i) dev-&gt;dev_addr[i]
id|len
op_add_assign
id|sprintf
c_func
(paren
id|buf
op_plus
id|len
comma
l_string|&quot;HW addr : %x:%x:%x:%x:%x:%x&bslash;n&quot;
comma
id|HW_ADDR
c_func
(paren
l_int|0
)paren
comma
id|HW_ADDR
c_func
(paren
l_int|1
)paren
comma
id|HW_ADDR
c_func
(paren
l_int|2
)paren
comma
id|HW_ADDR
c_func
(paren
l_int|3
)paren
comma
id|HW_ADDR
c_func
(paren
l_int|4
)paren
comma
id|HW_ADDR
c_func
(paren
l_int|5
)paren
)paren
suffix:semicolon
DECL|macro|HW_ADDR
macro_line|#undef HW_ADDR
r_return
id|len
suffix:semicolon
)brace
DECL|function|ne2_probe1
r_static
r_int
id|__init
id|ne2_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|slot
)paren
(brace
r_int
id|i
comma
id|base_addr
comma
id|irq
comma
id|retval
suffix:semicolon
r_int
r_char
id|POS
suffix:semicolon
r_int
r_char
id|SA_prom
(braket
l_int|32
)braket
suffix:semicolon
r_const
r_char
op_star
id|name
op_assign
l_string|&quot;NE/2&quot;
suffix:semicolon
r_int
id|start_page
comma
id|stop_page
suffix:semicolon
r_static
r_int
id|version_printed
suffix:semicolon
r_if
c_cond
(paren
id|ei_debug
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
l_string|&quot;NE/2 ethercard found in slot %d:&quot;
comma
id|slot
)paren
suffix:semicolon
multiline_comment|/* Read base IO and IRQ from the POS-registers */
id|POS
op_assign
id|mca_read_stored_pos
c_func
(paren
id|slot
comma
l_int|2
)paren
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
(paren
id|POS
op_mod
l_int|2
)paren
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; disabled.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
id|i
op_assign
(paren
id|POS
op_amp
l_int|0xE
)paren
op_rshift
l_int|1
suffix:semicolon
multiline_comment|/* printk(&quot;Halleluja sdog, als er na de pijl een 1 staat is 1 - 1 == 0&quot;&n;&t;   &quot; en zou het moeten werken -&gt; %d&bslash;n&quot;, i);&n;&t;   The above line was for remote testing, thanx to sdog ... */
id|base_addr
op_assign
id|addresses
(braket
id|i
op_minus
l_int|1
)braket
suffix:semicolon
id|irq
op_assign
id|irqs
(braket
(paren
id|POS
op_amp
l_int|0x60
)paren
op_rshift
l_int|5
)braket
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|base_addr
comma
id|NE_IO_EXTENT
comma
id|dev-&gt;name
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
macro_line|#ifdef DEBUG
id|printk
c_func
(paren
l_string|&quot;POS info : pos 2 = %#x ; base = %#x ; irq = %ld&bslash;n&quot;
comma
id|POS
comma
id|base_addr
comma
id|irq
)paren
suffix:semicolon
macro_line|#endif
macro_line|#ifndef CRYNWR_WAY
multiline_comment|/* Reset the card the way they do it in the Crynwr packet driver */
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
l_int|0x0
comma
id|base_addr
op_plus
id|NE_RESET
)paren
suffix:semicolon
id|inb
c_func
(paren
id|base_addr
op_plus
id|NE_RESET
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x21
comma
id|base_addr
op_plus
id|NE_CMD
)paren
suffix:semicolon
r_if
c_cond
(paren
id|inb
c_func
(paren
id|base_addr
op_plus
id|NE_CMD
)paren
op_ne
l_int|0x21
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;NE/2 adapter not responding&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
multiline_comment|/* In the crynwr sources they do a RAM-test here. I skip it. I suppose&n;&t;   my RAM is okay.  Suppose your memory is broken.  Then this test&n;&t;   should fail and you won&squot;t be able to use your card.  But if I do not&n;&t;   test, you won&squot;t be able to use your card, neither.  So this test&n;&t;   won&squot;t help you. */
macro_line|#else  /* _I_ never tested it this way .. Go ahead and try ...*/
multiline_comment|/* Reset card. Who knows what dain-bramaged state it was left in. */
(brace
r_int
r_int
id|reset_start_time
op_assign
id|jiffies
suffix:semicolon
multiline_comment|/* DON&squot;T change these to inb_p/outb_p or reset will fail on &n;&t;&t;   clones.. */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|base_addr
op_plus
id|NE_RESET
)paren
comma
id|base_addr
op_plus
id|NE_RESET
)paren
suffix:semicolon
r_while
c_loop
(paren
(paren
id|inb_p
c_func
(paren
id|base_addr
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
op_star
id|HZ
op_div
l_int|100
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; not found (no reset ack).&bslash;n&quot;
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENODEV
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|outb_p
c_func
(paren
l_int|0xff
comma
id|base_addr
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack all intr. */
)brace
macro_line|#endif
multiline_comment|/* Read the 16 bytes of station address PROM.&n;&t;   We must first initialize registers, similar to &n;&t;   NS8390_init(eifdev, 0).&n;&t;   We can&squot;t reliably read the SAPROM address without this.&n;&t;   (I learned the hard way!). */
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
multiline_comment|/* Select page 0 */
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
(brace
l_int|0x49
comma
id|EN0_DCFG
)brace
comma
multiline_comment|/* Set WORD-wide (0x49) access. */
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
id|base_addr
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
l_int|6
multiline_comment|/*sizeof(SA_prom)*/
suffix:semicolon
id|i
op_add_assign
l_int|1
)paren
(brace
id|SA_prom
(braket
id|i
)braket
op_assign
id|inb
c_func
(paren
id|base_addr
op_plus
id|NE_DATAPORT
)paren
suffix:semicolon
)brace
id|start_page
op_assign
id|NESM_START_PG
suffix:semicolon
id|stop_page
op_assign
id|NESM_STOP_PG
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
multiline_comment|/* Snarf the interrupt now.  There&squot;s no point in waiting since we cannot&n;&t;   share and the board will usually be enabled. */
id|retval
op_assign
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ei_interrupt
comma
l_int|0
comma
id|dev-&gt;name
comma
id|dev
)paren
suffix:semicolon
r_if
c_cond
(paren
id|retval
)paren
(brace
id|printk
(paren
l_string|&quot; unable to get IRQ %d (irqval=%d).&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|retval
)paren
suffix:semicolon
r_goto
id|out
suffix:semicolon
)brace
id|dev-&gt;base_addr
op_assign
id|base_addr
suffix:semicolon
multiline_comment|/* Allocate dev-&gt;priv and fill in 8390 specific dev fields. */
r_if
c_cond
(paren
id|ethdev_init
c_func
(paren
id|dev
)paren
)paren
(brace
id|printk
(paren
l_string|&quot; unable to get memory for dev-&gt;priv.&bslash;n&quot;
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|retval
op_assign
op_minus
id|ENOMEM
suffix:semicolon
r_goto
id|out
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
id|ETHER_ADDR_LEN
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
)brace
id|printk
c_func
(paren
l_string|&quot;&bslash;n%s: %s found at %#x, using IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;name
comma
id|name
comma
id|base_addr
comma
id|dev-&gt;irq
)paren
suffix:semicolon
id|mca_set_adapter_procfn
c_func
(paren
id|slot
comma
(paren
id|MCA_ProcFn
)paren
id|ne2_procinfo
comma
id|dev
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
l_int|2
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
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ne_get_8390_hdr
suffix:semicolon
id|ei_status.priv
op_assign
id|slot
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ne_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ne_close
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
l_int|0
suffix:semicolon
id|out
suffix:colon
id|release_region
c_func
(paren
id|base_addr
comma
id|NE_IO_EXTENT
)paren
suffix:semicolon
r_return
id|retval
suffix:semicolon
)brace
DECL|function|ne_open
r_static
r_int
id|ne_open
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
id|ei_open
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ne_close
r_static
r_int
id|ne_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
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
l_string|&quot;%s: Shutting down ethercard.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|ei_close
c_func
(paren
id|dev
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
multiline_comment|/* Hard reset the card.  This used to pause for the same period that a&n;   8390 reset command required, but that shouldn&squot;t be necessary. */
DECL|function|ne_reset_8390
r_static
r_void
id|ne_reset_8390
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_int
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
l_string|&quot;resetting the 8390 t=%ld...&quot;
comma
id|jiffies
)paren
suffix:semicolon
multiline_comment|/* DON&squot;T change these to inb_p/outb_p or reset will fail on clones. */
id|outb
c_func
(paren
id|inb
c_func
(paren
id|NE_BASE
op_plus
id|NE_RESET
)paren
comma
id|NE_BASE
op_plus
id|NE_RESET
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|ei_status.dmaing
op_assign
l_int|0
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
op_star
id|HZ
op_div
l_int|100
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
id|outb_p
c_func
(paren
id|ENISR_RESET
comma
id|NE_BASE
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
)brace
multiline_comment|/* Grab the 8390 specific header. Similar to the block_input routine, but&n;   we don&squot;t need to be concerned with ring wrap as the header will be at&n;   the start of a page, so we optimize accordingly. */
DECL|function|ne_get_8390_hdr
r_static
r_void
id|ne_get_8390_hdr
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_struct
id|e8390_pkt_hdr
op_star
id|hdr
comma
r_int
id|ring_page
)paren
(brace
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
multiline_comment|/* This *shouldn&squot;t* happen. &n;&t;   If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne_get_8390_hdr &quot;
l_string|&quot;[DMAstat:%d][irqlock:%d].&bslash;n&quot;
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
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
comma
id|nic_base
op_plus
id|EN0_RCNTLO
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|nic_base
op_plus
id|EN0_RCNTHI
)paren
suffix:semicolon
id|outb_p
c_func
(paren
l_int|0
comma
id|nic_base
op_plus
id|EN0_RSARLO
)paren
suffix:semicolon
multiline_comment|/* On page boundary */
id|outb_p
c_func
(paren
id|ring_page
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
id|insw
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|hdr
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
op_rshift
l_int|1
)paren
suffix:semicolon
r_else
id|insb
c_func
(paren
id|NE_BASE
op_plus
id|NE_DATAPORT
comma
id|hdr
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
suffix:semicolon
id|outb_p
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
multiline_comment|/* Block input and output, similar to the Crynwr packet driver.  If you&n;   are porting to a new ethercard, look at the packet driver source for&n;   hints. The NEx000 doesn&squot;t share the on-board packet memory -- you have&n;   to put the packet out through the &quot;remote DMA&quot; dataport using outb. */
DECL|function|ne_block_input
r_static
r_void
id|ne_block_input
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
id|count
comma
r_struct
id|sk_buff
op_star
id|skb
comma
r_int
id|ring_offset
)paren
(brace
macro_line|#ifdef NE_SANITY_CHECK
r_int
id|xfer_count
op_assign
id|count
suffix:semicolon
macro_line|#endif
r_int
id|nic_base
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_char
op_star
id|buf
op_assign
id|skb-&gt;data
suffix:semicolon
multiline_comment|/* This *shouldn&squot;t* happen. &n;&t;   If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne_block_input &quot;
l_string|&quot;[DMAstat:%d][irqlock:%d].&bslash;n&quot;
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
id|insw
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
(brace
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
suffix:semicolon
macro_line|#ifdef NE_SANITY_CHECK
id|xfer_count
op_increment
suffix:semicolon
macro_line|#endif
)brace
)brace
r_else
(brace
id|insb
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
macro_line|#ifdef NE_SANITY_CHECK
multiline_comment|/* This was for the ALPHA version only, but enough people have&n;&t;   been encountering problems so it is still here.  If you see&n;&t;   this message you either 1) have a slightly incompatible clone&n;&t;   or 2) have noise/speed problems with your bus. */
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
multiline_comment|/* DON&squot;T check for &squot;inb_p(EN0_ISR) &amp; ENISR_RDC&squot; here&n;&t;&t;&t;   -- it&squot;s broken for Rx on some cards! */
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
macro_line|#endif
id|outb_p
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
)brace
DECL|function|ne_block_output
r_static
r_void
id|ne_block_output
c_func
(paren
r_struct
id|net_device
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
id|nic_base
op_assign
id|NE_BASE
suffix:semicolon
r_int
r_int
id|dma_start
suffix:semicolon
macro_line|#ifdef NE_SANITY_CHECK
r_int
id|retries
op_assign
l_int|0
suffix:semicolon
macro_line|#endif
multiline_comment|/* Round the count up for word writes. Do we need to do this?&n;&t;   What effect will an odd byte count have on the 8390?&n;&t;   I should check someday. */
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
multiline_comment|/* This *shouldn&squot;t* happen. &n;&t;   If it does, it&squot;s the last thing you&squot;ll see */
r_if
c_cond
(paren
id|ei_status.dmaing
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;%s: DMAing conflict in ne_block_output.&quot;
l_string|&quot;[DMAstat:%d][irqlock:%d]&bslash;n&quot;
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
l_int|0x01
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
macro_line|#ifdef NE_SANITY_CHECK
id|retry
suffix:colon
macro_line|#endif
macro_line|#ifdef NE8390_RW_BUGFIX
multiline_comment|/* Handle the read-before-write bug the same way as the&n;&t;   Crynwr packet driver -- the NatSemi method doesn&squot;t work.&n;&t;   Actually this doesn&squot;t always work either, but if you have&n;&t;   problems with your NEx000 this is better than nothing! */
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
multiline_comment|/* Make certain that the dummy read has occurred. */
id|SLOW_DOWN_IO
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
id|SLOW_DOWN_IO
suffix:semicolon
macro_line|#endif
id|outb_p
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
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
id|outsw
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
id|outsb
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
id|dma_start
op_assign
id|jiffies
suffix:semicolon
macro_line|#ifdef NE_SANITY_CHECK
multiline_comment|/* This was for the ALPHA version only, but enough people have&n;&t;   been encountering problems so it is still here. */
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
macro_line|#endif
r_while
c_loop
(paren
(paren
id|inb_p
c_func
(paren
id|nic_base
op_plus
id|EN0_ISR
)paren
op_amp
id|ENISR_RDC
)paren
op_eq
l_int|0
)paren
r_if
c_cond
(paren
id|jiffies
op_minus
id|dma_start
OG
l_int|2
op_star
id|HZ
op_div
l_int|100
)paren
(brace
multiline_comment|/* 20ms */
id|printk
c_func
(paren
l_string|&quot;%s: timeout waiting for Tx RDC.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|ne_reset_8390
c_func
(paren
id|dev
)paren
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|1
)paren
suffix:semicolon
r_break
suffix:semicolon
)brace
id|outb_p
c_func
(paren
id|ENISR_RDC
comma
id|nic_base
op_plus
id|EN0_ISR
)paren
suffix:semicolon
multiline_comment|/* Ack intr. */
id|ei_status.dmaing
op_and_assign
op_complement
l_int|0x01
suffix:semicolon
r_return
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|macro|MAX_NE_CARDS
mdefine_line|#define MAX_NE_CARDS&t;4&t;/* Max number of NE cards per module */
DECL|variable|dev_ne
r_static
r_struct
id|net_device
id|dev_ne
(braket
id|MAX_NE_CARDS
)braket
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_NE_CARDS
)braket
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_NE_CARDS
)braket
suffix:semicolon
DECL|variable|bad
r_static
r_int
id|bad
(braket
id|MAX_NE_CARDS
)braket
suffix:semicolon
multiline_comment|/* 0xbad = bad sig or no reset ack */
macro_line|#ifdef MODULE_PARM
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_NE_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|irq
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_NE_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|bad
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_NE_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Module code fixed by David Weinehall */
DECL|function|init_module
r_int
id|init_module
c_func
(paren
r_void
)paren
(brace
r_int
id|this_dev
comma
id|found
op_assign
l_int|0
suffix:semicolon
r_for
c_loop
(paren
id|this_dev
op_assign
l_int|0
suffix:semicolon
id|this_dev
OL
id|MAX_NE_CARDS
suffix:semicolon
id|this_dev
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
op_amp
id|dev_ne
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|bad
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;base_addr
op_assign
id|io
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;init
op_assign
id|ne2_probe
suffix:semicolon
r_if
c_cond
(paren
id|register_netdev
c_func
(paren
id|dev
)paren
op_ne
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|found
op_ne
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Got at least one. */
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;ne2.c: No NE/2 card found.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|found
op_increment
suffix:semicolon
)brace
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|cleanup_module
r_void
id|cleanup_module
c_func
(paren
r_void
)paren
(brace
r_int
id|this_dev
suffix:semicolon
r_for
c_loop
(paren
id|this_dev
op_assign
l_int|0
suffix:semicolon
id|this_dev
OL
id|MAX_NE_CARDS
suffix:semicolon
id|this_dev
op_increment
)paren
(brace
r_struct
id|net_device
op_star
id|dev
op_assign
op_amp
id|dev_ne
(braket
id|this_dev
)braket
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;priv
op_ne
l_int|NULL
)paren
(brace
id|mca_mark_as_unused
c_func
(paren
id|ei_status.priv
)paren
suffix:semicolon
id|mca_set_adapter_procfn
c_func
(paren
id|ei_status.priv
comma
l_int|NULL
comma
l_int|NULL
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|dev-&gt;priv
)paren
suffix:semicolon
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|release_region
c_func
(paren
id|dev-&gt;base_addr
comma
id|NE_IO_EXTENT
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* MODULE */
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -DKERNEL -Wall -O6 -fomit-frame-pointer -I/usr/src/linux/net/tcp -c ne2.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; * End:&n; */
eof
