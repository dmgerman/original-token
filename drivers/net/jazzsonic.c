multiline_comment|/*&n; * sonic.c&n; *&n; * (C) 1996,1998 by Thomas Bogendoerfer (tsbogend@alpha.franken.de)&n; * &n; * This driver is based on work from Andreas Busse, but most of&n; * the code is rewritten.&n; * &n; * (C) 1995 by Andreas Busse (andy@waldorf-gmbh.de)&n; *&n; * A driver for the onboard Sonic ethernet controller on Mips Jazz&n; * systems (Acer Pica-61, Mips Magnum 4000, Olivetti M700 and&n; * perhaps others, too)&n; */
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/types.h&gt;
macro_line|#include &lt;linux/fcntl.h&gt;
macro_line|#include &lt;linux/interrupt.h&gt;
macro_line|#include &lt;linux/ptrace.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;linux/ioport.h&gt;
macro_line|#include &lt;linux/in.h&gt;
macro_line|#include &lt;linux/malloc.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/delay.h&gt;
macro_line|#include &lt;asm/bootinfo.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;asm/bitops.h&gt;
macro_line|#include &lt;asm/pgtable.h&gt;
macro_line|#include &lt;asm/segment.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/dma.h&gt;
macro_line|#include &lt;asm/jazz.h&gt;
macro_line|#include &lt;asm/jazzdma.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &lt;linux/skbuff.h&gt;
DECL|macro|SREGS_PAD
mdefine_line|#define SREGS_PAD(n)    u16 n;
macro_line|#include &quot;sonic.h&quot;
multiline_comment|/*&n; * Macros to access SONIC registers&n; */
DECL|macro|SONIC_READ
mdefine_line|#define SONIC_READ(reg) &bslash;&n;&t;*((volatile unsigned int *)base_addr+reg)
DECL|macro|SONIC_WRITE
mdefine_line|#define SONIC_WRITE(reg,val) &bslash;&n;&t;*((volatile unsigned int *)base_addr+reg) = val
multiline_comment|/* use 0 for production, 1 for verification, &gt;2 for debug */
macro_line|#ifdef SONIC_DEBUG
DECL|variable|sonic_debug
r_static
r_int
r_int
id|sonic_debug
op_assign
id|SONIC_DEBUG
suffix:semicolon
macro_line|#else 
DECL|variable|sonic_debug
r_static
r_int
r_int
id|sonic_debug
op_assign
l_int|1
suffix:semicolon
macro_line|#endif
multiline_comment|/*&n; * Base address and interupt of the SONIC controller on JAZZ boards&n; */
r_static
r_struct
(brace
DECL|member|port
r_int
r_int
id|port
suffix:semicolon
DECL|member|irq
r_int
r_int
id|irq
suffix:semicolon
DECL|variable|sonic_portlist
)brace
id|sonic_portlist
(braket
)braket
op_assign
(brace
(brace
id|JAZZ_ETHERNET_BASE
comma
id|JAZZ_ETHERNET_IRQ
)brace
comma
(brace
l_int|0
comma
l_int|0
)brace
)brace
suffix:semicolon
multiline_comment|/*&n; * We cannot use station (ethernet) address prefixes to detect the&n; * sonic controller since these are board manufacturer depended.&n; * So we check for known Silicon Revision IDs instead. &n; */
DECL|variable|known_revisions
r_static
r_int
r_int
id|known_revisions
(braket
)braket
op_assign
(brace
l_int|0x04
comma
multiline_comment|/* Mips Magnum 4000 */
l_int|0xffff
multiline_comment|/* end of list */
)brace
suffix:semicolon
multiline_comment|/* Index to functions, as function prototypes. */
r_extern
r_int
id|sonic_probe
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
id|sonic_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|base_addr
comma
r_int
r_int
id|irq
)paren
suffix:semicolon
multiline_comment|/*&n; * Probe for a SONIC ethernet controller on a Mips Jazz board.&n; * Actually probing is superfluous but we&squot;re paranoid.&n; */
DECL|function|sonic_probe
r_int
id|__init
id|sonic_probe
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
id|base_addr
op_assign
id|dev
ques
c_cond
id|dev-&gt;base_addr
suffix:colon
l_int|0
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;     * Don&squot;t probe if we&squot;re not running on a Jazz board.&n;     */
r_if
c_cond
(paren
id|mips_machgroup
op_ne
id|MACH_GROUP_JAZZ
)paren
r_return
op_minus
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|base_addr
op_ge
id|KSEG0
)paren
multiline_comment|/* Check a single specified location. */
r_return
id|sonic_probe1
c_func
(paren
id|dev
comma
id|base_addr
comma
id|dev-&gt;irq
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
op_minus
id|ENXIO
suffix:semicolon
r_for
c_loop
(paren
id|i
op_assign
l_int|0
suffix:semicolon
id|sonic_portlist
(braket
id|i
)braket
dot
id|port
suffix:semicolon
id|i
op_increment
)paren
(brace
r_int
id|base_addr
op_assign
id|sonic_portlist
(braket
id|i
)braket
dot
id|port
suffix:semicolon
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|base_addr
comma
l_int|0x100
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|sonic_probe1
c_func
(paren
id|dev
comma
id|base_addr
comma
id|sonic_portlist
(braket
id|i
)braket
dot
id|irq
)paren
op_eq
l_int|0
)paren
r_return
l_int|0
suffix:semicolon
)brace
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
DECL|function|sonic_probe1
r_static
r_int
id|__init
id|sonic_probe1
c_func
(paren
r_struct
id|net_device
op_star
id|dev
comma
r_int
r_int
id|base_addr
comma
r_int
r_int
id|irq
)paren
(brace
r_static
r_int
id|version_printed
op_assign
l_int|0
suffix:semicolon
r_int
r_int
id|silicon_revision
suffix:semicolon
r_int
r_int
id|val
suffix:semicolon
r_struct
id|sonic_local
op_star
id|lp
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/*&n;     * get the Silicon Revision ID. If this is one of the known&n;     * one assume that we found a SONIC ethernet controller at&n;     * the expected location.&n;     */
id|silicon_revision
op_assign
id|SONIC_READ
c_func
(paren
id|SONIC_SR
)paren
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
OG
l_int|1
)paren
id|printk
c_func
(paren
l_string|&quot;SONIC Silicon Revision = 0x%04x&bslash;n&quot;
comma
id|silicon_revision
)paren
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
(paren
id|known_revisions
(braket
id|i
)braket
op_ne
l_int|0xffff
)paren
op_logical_and
(paren
id|known_revisions
(braket
id|i
)braket
op_ne
id|silicon_revision
)paren
)paren
id|i
op_increment
suffix:semicolon
r_if
c_cond
(paren
id|known_revisions
(braket
id|i
)braket
op_eq
l_int|0xffff
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;SONIC ethernet controller not found (0x%4x)&bslash;n&quot;
comma
id|silicon_revision
)paren
suffix:semicolon
r_return
op_minus
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
op_logical_neg
id|request_region
c_func
(paren
id|base_addr
comma
l_int|0x100
comma
id|dev-&gt;name
)paren
)paren
r_return
op_minus
id|EBUSY
suffix:semicolon
r_if
c_cond
(paren
id|sonic_debug
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
l_string|&quot;%s: %s found at 0x%08x, &quot;
comma
id|dev-&gt;name
comma
l_string|&quot;SONIC ethernet&quot;
comma
id|base_addr
)paren
suffix:semicolon
multiline_comment|/* Fill in the &squot;dev&squot; fields. */
id|dev-&gt;base_addr
op_assign
id|base_addr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
multiline_comment|/*&n;     * Put the sonic into software reset, then&n;     * retrieve and print the ethernet address.&n;     */
id|SONIC_WRITE
c_func
(paren
id|SONIC_CMD
comma
id|SONIC_CR_RST
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_CEP
comma
l_int|0
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
l_int|3
suffix:semicolon
id|i
op_increment
)paren
(brace
id|val
op_assign
id|SONIC_READ
c_func
(paren
id|SONIC_CAP0
op_minus
id|i
)paren
suffix:semicolon
id|dev-&gt;dev_addr
(braket
id|i
op_star
l_int|2
)braket
op_assign
id|val
suffix:semicolon
id|dev-&gt;dev_addr
(braket
id|i
op_star
l_int|2
op_plus
l_int|1
)braket
op_assign
id|val
op_rshift
l_int|8
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;HW Address &quot;
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
(brace
id|printk
c_func
(paren
l_string|&quot;%2.2x&quot;
comma
id|dev-&gt;dev_addr
(braket
id|i
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|i
OL
l_int|5
)paren
id|printk
c_func
(paren
l_string|&quot;:&quot;
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; IRQ %d&bslash;n&quot;
comma
id|irq
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
(brace
multiline_comment|/*&n;&t; * the memory be located in the same 64kb segment&n;&t; */
id|lp
op_assign
l_int|NULL
suffix:semicolon
id|i
op_assign
l_int|0
suffix:semicolon
r_do
(brace
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|kmalloc
c_func
(paren
r_sizeof
(paren
op_star
id|lp
)paren
comma
id|GFP_KERNEL
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
r_int
r_int
)paren
id|lp
op_rshift
l_int|16
op_ne
(paren
(paren
r_int
r_int
)paren
id|lp
op_plus
r_sizeof
(paren
op_star
id|lp
)paren
)paren
op_rshift
l_int|16
)paren
(brace
multiline_comment|/* FIXME, free the memory later */
id|kfree
(paren
id|lp
)paren
suffix:semicolon
id|lp
op_assign
l_int|NULL
suffix:semicolon
)brace
)brace
r_while
c_loop
(paren
id|lp
op_eq
l_int|NULL
op_logical_and
id|i
op_increment
OL
l_int|20
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;%s: couldn&squot;t allocate memory for descriptors&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|memset
c_func
(paren
id|lp
comma
l_int|0
comma
r_sizeof
(paren
r_struct
id|sonic_local
)paren
)paren
suffix:semicolon
multiline_comment|/* get the virtual dma address */
id|lp-&gt;cda_laddr
op_assign
id|vdma_alloc
c_func
(paren
id|PHYSADDR
c_func
(paren
id|lp
)paren
comma
r_sizeof
(paren
op_star
id|lp
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|lp-&gt;cda_laddr
op_eq
op_complement
l_int|0UL
)paren
(brace
id|printk
(paren
l_string|&quot;%s: couldn&squot;t get DMA page entry for descriptors&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
id|lp-&gt;tda_laddr
op_assign
id|lp-&gt;cda_laddr
op_plus
r_sizeof
(paren
id|lp-&gt;cda
)paren
suffix:semicolon
id|lp-&gt;rra_laddr
op_assign
id|lp-&gt;tda_laddr
op_plus
r_sizeof
(paren
id|lp-&gt;tda
)paren
suffix:semicolon
id|lp-&gt;rda_laddr
op_assign
id|lp-&gt;rra_laddr
op_plus
r_sizeof
(paren
id|lp-&gt;rra
)paren
suffix:semicolon
multiline_comment|/* allocate receive buffer area */
multiline_comment|/* FIXME, maybe we should use skbs */
r_if
c_cond
(paren
(paren
id|lp-&gt;rba
op_assign
(paren
r_char
op_star
)paren
id|kmalloc
c_func
(paren
id|SONIC_NUM_RRS
op_star
id|SONIC_RBSIZE
comma
id|GFP_KERNEL
)paren
)paren
op_eq
l_int|NULL
)paren
(brace
id|printk
(paren
l_string|&quot;%s: couldn&squot;t allocate receive buffers&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* get virtual dma address */
r_if
c_cond
(paren
(paren
id|lp-&gt;rba_laddr
op_assign
id|vdma_alloc
c_func
(paren
id|PHYSADDR
c_func
(paren
id|lp-&gt;rba
)paren
comma
id|SONIC_NUM_RRS
op_star
id|SONIC_RBSIZE
)paren
)paren
op_eq
op_complement
l_int|0UL
)paren
(brace
id|printk
(paren
l_string|&quot;%s: couldn&squot;t get DMA page entry for receive buffers&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* now convert pointer to KSEG1 pointer */
id|lp-&gt;rba
op_assign
(paren
r_char
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|lp-&gt;rba
)paren
suffix:semicolon
id|flush_cache_all
c_func
(paren
)paren
suffix:semicolon
id|dev-&gt;priv
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|KSEG1ADDR
c_func
(paren
id|lp
)paren
suffix:semicolon
)brace
id|lp
op_assign
(paren
r_struct
id|sonic_local
op_star
)paren
id|dev-&gt;priv
suffix:semicolon
id|dev-&gt;open
op_assign
id|sonic_open
suffix:semicolon
id|dev-&gt;stop
op_assign
id|sonic_close
suffix:semicolon
id|dev-&gt;hard_start_xmit
op_assign
id|sonic_send_packet
suffix:semicolon
id|dev-&gt;get_stats
op_assign
id|sonic_get_stats
suffix:semicolon
id|dev-&gt;set_multicast_list
op_assign
op_amp
id|sonic_multicast_list
suffix:semicolon
multiline_comment|/*&n;     * clear tally counter&n;     */
id|SONIC_WRITE
c_func
(paren
id|SONIC_CRCT
comma
l_int|0xffff
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_FAET
comma
l_int|0xffff
)paren
suffix:semicolon
id|SONIC_WRITE
c_func
(paren
id|SONIC_MPT
comma
l_int|0xffff
)paren
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
multiline_comment|/*&n; *      SONIC uses a normal IRQ&n; */
DECL|macro|sonic_request_irq
mdefine_line|#define sonic_request_irq       request_irq
DECL|macro|sonic_free_irq
mdefine_line|#define sonic_free_irq          free_irq
DECL|macro|sonic_chiptomem
mdefine_line|#define sonic_chiptomem(x)      KSEG1ADDR(vdma_log2phys(x))
macro_line|#include &quot;sonic.c&quot;
eof
