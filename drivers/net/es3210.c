multiline_comment|/*&n;&t;es3210.c&n;&n;&t;Linux driver for Racal-Interlan ES3210 EISA Network Adapter&n;&n;&t;Copyright (C) 1996, Paul Gortmaker.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU Public License, incorporated herein by reference.&n;&n;&t;Information and Code Sources:&n;&n;&t;1) The existing myriad of Linux 8390 drivers written by Donald Becker.&n;&n;&t;2) Once again Russ Nelson&squot;s asm packet driver provided additional info.&n;&n;&t;3) Info for getting IRQ and sh-mem gleaned from the EISA cfg files.&n;&t;   Too bad it doesn&squot;t work -- see below.&n;&n;&t;The ES3210 is an EISA shared memory NS8390 implementation. Note&n;&t;that all memory copies to/from the board must be 32bit transfers.&n;&t;Which rules out using eth_io_copy_and_sum() in this driver.&n;&n;&t;Apparently there are two slightly different revisions of the&n;&t;card, since there are two distinct EISA cfg files (!rii0101.cfg&n;&t;and !rii0102.cfg) One has media select in the cfg file and the&n;&t;other doesn&squot;t. Hopefully this will work with either.&n;&n;&t;That is about all I can tell you about it, having never actually&n;&t;even seen one of these cards. :)  Try http://www.interlan.com&n;&t;if you want more info.&n;&n;&t;Thanks go to Mark Salazar for testing v0.02 of this driver.&n;&n;&t;Bugs, to-fix, etc:&n;&n;&t;1) The EISA cfg ports that are *supposed* to have the IRQ and shared&n;&t;   mem values just read 0xff all the time. Hrrmpf. Apparently the&n;&t;   same happens with the packet driver as the code for reading&n;&t;   these registers is disabled there. In the meantime, boot with:&n;&t;   ether=&lt;IRQ&gt;,0,0x&lt;shared_mem_addr&gt;,eth0 to override the IRQ and&n;&t;   shared memory detection. (The i/o port detection is okay.)&n;&n;&t;2) Module support currently untested. Probably works though.&n;&n;*/
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;es3210.c: Driver revision v0.03, 14/09/96&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/module.h&gt;
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;linux/init.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &lt;linux/etherdevice.h&gt;
macro_line|#include &quot;8390.h&quot;
r_int
id|es_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|es_probe1
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
id|es_open
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
id|es_close
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
id|es_reset_8390
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
id|es_get_8390_hdr
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
id|es_block_input
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
id|es_block_output
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
r_int
id|start_page
)paren
suffix:semicolon
DECL|macro|ES_START_PG
mdefine_line|#define ES_START_PG&t;0x00    /* First page of TX buffer&t;&t;*/
DECL|macro|ES_STOP_PG
mdefine_line|#define ES_STOP_PG&t;0x40    /* Last page +1 of RX ring&t;&t;*/
DECL|macro|ES_IO_EXTENT
mdefine_line|#define ES_IO_EXTENT&t;0x37&t;/* The cfg file says 0xc90 -&gt; 0xcc7&t;*/
DECL|macro|ES_ID_PORT
mdefine_line|#define ES_ID_PORT&t;0xc80&t;/* Same for all EISA cards &t;&t;*/
DECL|macro|ES_SA_PROM
mdefine_line|#define ES_SA_PROM&t;0xc90&t;/* Start of e&squot;net addr.&t;&t;&t;*/
DECL|macro|ES_RESET_PORT
mdefine_line|#define ES_RESET_PORT&t;0xc84&t;/* From the packet driver source&t;*/
DECL|macro|ES_NIC_OFFSET
mdefine_line|#define ES_NIC_OFFSET&t;0xca0&t;/* Hello, the 8390 is *here*&t;&t;*/
DECL|macro|ES_ADDR0
mdefine_line|#define ES_ADDR0&t;0x02&t;/* 3 byte vendor prefix&t;&t;&t;*/
DECL|macro|ES_ADDR1
mdefine_line|#define ES_ADDR1&t;0x07
DECL|macro|ES_ADDR2
mdefine_line|#define ES_ADDR2&t;0x01
multiline_comment|/*&n; * Two card revisions. EISA ID&squot;s are always rev. minor, rev. major,, and&n; * then the three vendor letters stored in 5 bits each, with an &quot;a&quot; = 1.&n; * For eg: &quot;rii&quot; = 10010 01001 01001 = 0x4929, which is how the EISA&n; * config utility determines automagically what config file(s) to use.&n; */
DECL|macro|ES_EISA_ID1
mdefine_line|#define ES_EISA_ID1&t;0x01012949&t;/* !rii0101.cfg &t;&t;*/
DECL|macro|ES_EISA_ID2
mdefine_line|#define ES_EISA_ID2&t;0x02012949&t;/* !rii0102.cfg &t;&t;*/
DECL|macro|ES_CFG1
mdefine_line|#define ES_CFG1&t;&t;0xcc0&t;/* IOPORT(1) --&gt; IOPORT(6) in cfg file&t;*/
DECL|macro|ES_CFG2
mdefine_line|#define ES_CFG2&t;&t;0xcc1
DECL|macro|ES_CFG3
mdefine_line|#define ES_CFG3&t;&t;0xcc2
DECL|macro|ES_CFG4
mdefine_line|#define ES_CFG4&t;&t;0xcc3
DECL|macro|ES_CFG5
mdefine_line|#define ES_CFG5&t;&t;0xcc4
DECL|macro|ES_CFG6
mdefine_line|#define ES_CFG6&t;&t;0xc84&t;/* NB: 0xc84 is also &quot;reset&quot; port.&t;*/
multiline_comment|/*&n; *&t;You can OR any of the following bits together and assign it&n; *&t;to ES_DEBUG to get verbose driver info during operation.&n; *&t;Some of these don&squot;t do anything yet.&n; */
DECL|macro|ES_D_PROBE
mdefine_line|#define ES_D_PROBE&t;0x01
DECL|macro|ES_D_RX_PKT
mdefine_line|#define ES_D_RX_PKT&t;0x02
DECL|macro|ES_D_TX_PKT
mdefine_line|#define ES_D_TX_PKT&t;0x04
DECL|macro|ED_D_IRQ
mdefine_line|#define ED_D_IRQ&t;0x08
DECL|macro|ES_DEBUG
mdefine_line|#define ES_DEBUG&t;0
DECL|variable|__initdata
r_static
r_int
r_char
id|lo_irq_map
(braket
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
l_int|6
comma
l_int|7
comma
l_int|9
comma
l_int|10
)brace
suffix:semicolon
DECL|variable|__initdata
r_static
r_int
r_char
id|hi_irq_map
(braket
)braket
id|__initdata
op_assign
(brace
l_int|11
comma
l_int|12
comma
l_int|0
comma
l_int|14
comma
l_int|0
comma
l_int|0
comma
l_int|0
comma
l_int|15
)brace
suffix:semicolon
multiline_comment|/*&n; *&t;Probe for the card. The best way is to read the EISA ID if it&n; *&t;is known. Then we check the prefix of the station address&n; *&t;PROM for a match against the Racal-Interlan assigned value.&n; */
DECL|function|es_probe
r_int
id|__init
id|es_probe
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
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_if
c_cond
(paren
id|ioaddr
OG
l_int|0x1ff
)paren
multiline_comment|/* Check a single specified location. */
r_return
id|es_probe1
c_func
(paren
id|dev
comma
id|ioaddr
)paren
suffix:semicolon
r_else
r_if
c_cond
(paren
id|ioaddr
OG
l_int|0
)paren
multiline_comment|/* Don&squot;t probe at all. */
r_return
id|ENXIO
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|EISA_bus
)paren
(brace
macro_line|#if ES_DEBUG &amp; ES_D_PROBE
id|printk
c_func
(paren
l_string|&quot;es3210.c: Not EISA bus. Not probing high ports.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
r_return
id|ENXIO
suffix:semicolon
)brace
multiline_comment|/* EISA spec allows for up to 16 slots, but 8 is typical. */
r_for
c_loop
(paren
id|ioaddr
op_assign
l_int|0x1000
suffix:semicolon
id|ioaddr
OL
l_int|0x9000
suffix:semicolon
id|ioaddr
op_add_assign
l_int|0x1000
)paren
(brace
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ioaddr
op_plus
id|ES_SA_PROM
comma
id|ES_IO_EXTENT
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|es_probe1
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
DECL|function|es_probe1
r_int
id|__init
id|es_probe1
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
r_int
id|i
suffix:semicolon
r_int
r_int
id|eisa_id
suffix:semicolon
macro_line|#if ES_DEBUG &amp; ES_D_PROBE
id|printk
c_func
(paren
l_string|&quot;es3210.c: probe at %#x, ID %#8x&bslash;n&quot;
comma
id|ioaddr
comma
id|inl
c_func
(paren
id|ioaddr
op_plus
id|ES_ID_PORT
)paren
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;es3210.c: config regs: %#x %#x %#x %#x %#x %#x&bslash;n&quot;
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG1
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG2
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG3
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG4
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG5
)paren
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG6
)paren
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/*&t;Check the EISA ID of the card. */
id|eisa_id
op_assign
id|inl
c_func
(paren
id|ioaddr
op_plus
id|ES_ID_PORT
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|eisa_id
op_ne
id|ES_EISA_ID1
)paren
op_logical_and
(paren
id|eisa_id
op_ne
id|ES_EISA_ID2
)paren
)paren
(brace
r_return
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/*&t;Check the Racal vendor ID as well. */
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_SA_PROM
op_plus
l_int|0
)paren
op_ne
id|ES_ADDR0
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_SA_PROM
op_plus
l_int|1
)paren
op_ne
id|ES_ADDR1
op_logical_or
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_SA_PROM
op_plus
l_int|2
)paren
op_ne
id|ES_ADDR2
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;es3210.c: card not found&quot;
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
id|ETHER_ADDR_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_SA_PROM
op_plus
id|i
)paren
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; (invalid prefix).&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ENODEV
suffix:semicolon
)brace
multiline_comment|/* We should have a &quot;dev&quot; from Space.c or the static module table. */
r_if
c_cond
(paren
id|dev
op_eq
l_int|NULL
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;es3210.c: Passed a NULL device.&bslash;n&quot;
)paren
suffix:semicolon
id|dev
op_assign
id|init_etherdev
c_func
(paren
l_int|0
comma
l_int|0
)paren
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot;es3210.c: ES3210 rev. %ld at %#x, node&quot;
comma
id|eisa_id
op_rshift
l_int|24
comma
id|ioaddr
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
id|ETHER_ADDR_LEN
suffix:semicolon
id|i
op_increment
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; %02x&quot;
comma
(paren
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
id|ES_SA_PROM
op_plus
id|i
)paren
)paren
)paren
suffix:semicolon
)brace
multiline_comment|/* Snarf the interrupt now. */
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|0
)paren
(brace
r_int
r_char
id|hi_irq
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG2
)paren
op_amp
l_int|0x07
suffix:semicolon
r_int
r_char
id|lo_irq
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG1
)paren
op_amp
l_int|0xfe
suffix:semicolon
r_if
c_cond
(paren
id|hi_irq
op_ne
l_int|0
)paren
(brace
id|dev-&gt;irq
op_assign
id|hi_irq_map
(braket
id|hi_irq
op_minus
l_int|1
)braket
suffix:semicolon
)brace
r_else
(brace
r_int
id|i
op_assign
l_int|0
suffix:semicolon
r_while
c_loop
(paren
id|lo_irq
OG
(paren
l_int|1
op_lshift
id|i
)paren
)paren
id|i
op_increment
suffix:semicolon
id|dev-&gt;irq
op_assign
id|lo_irq_map
(braket
id|i
)braket
suffix:semicolon
)brace
id|printk
c_func
(paren
l_string|&quot; using IRQ %d&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
macro_line|#if ES_DEBUG &amp; ES_D_PROBE
id|printk
c_func
(paren
l_string|&quot;es3210.c: hi_irq %#x, lo_irq %#x, dev-&gt;irq = %d&bslash;n&quot;
comma
id|hi_irq
comma
id|lo_irq
comma
id|dev-&gt;irq
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
(brace
r_if
c_cond
(paren
id|dev-&gt;irq
op_eq
l_int|2
)paren
id|dev-&gt;irq
op_assign
l_int|9
suffix:semicolon
multiline_comment|/* Doh! */
id|printk
c_func
(paren
l_string|&quot; assigning IRQ %d&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
)brace
r_if
c_cond
(paren
id|request_irq
c_func
(paren
id|dev-&gt;irq
comma
id|ei_interrupt
comma
l_int|0
comma
l_string|&quot;es3210&quot;
comma
id|dev
)paren
)paren
(brace
id|printk
(paren
l_string|&quot; unable to get IRQ %d.&bslash;n&quot;
comma
id|dev-&gt;irq
)paren
suffix:semicolon
r_return
id|EAGAIN
suffix:semicolon
)brace
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_eq
l_int|0
)paren
(brace
r_int
r_char
id|mem_enabled
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG2
)paren
op_amp
l_int|0xc0
suffix:semicolon
r_int
r_char
id|mem_bits
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG3
)paren
op_amp
l_int|0x07
suffix:semicolon
r_if
c_cond
(paren
id|mem_enabled
op_ne
l_int|0x80
)paren
(brace
id|printk
c_func
(paren
l_string|&quot; shared mem disabled - giving up&bslash;n&quot;
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
r_return
op_minus
id|ENXIO
suffix:semicolon
)brace
id|dev-&gt;mem_start
op_assign
l_int|0xC0000
op_plus
id|mem_bits
op_star
l_int|0x4000
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot; using &quot;
)paren
suffix:semicolon
)brace
r_else
(brace
id|printk
c_func
(paren
l_string|&quot; assigning &quot;
)paren
suffix:semicolon
)brace
id|dev-&gt;mem_end
op_assign
id|dev-&gt;rmem_end
op_assign
id|dev-&gt;mem_start
op_plus
(paren
id|ES_STOP_PG
op_minus
id|ES_START_PG
)paren
op_star
l_int|256
suffix:semicolon
id|dev-&gt;rmem_start
op_assign
id|dev-&gt;mem_start
op_plus
id|TX_PAGES
op_star
l_int|256
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;mem %#lx-%#lx&bslash;n&quot;
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
l_int|1
)paren
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
l_string|&quot; unable to allocate memory for dev-&gt;priv.&bslash;n&quot;
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
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
macro_line|#if ES_DEBUG &amp; ES_D_PROBE
r_if
c_cond
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ES_CFG5
)paren
)paren
id|printk
c_func
(paren
l_string|&quot;es3210: Warning - DMA channel enabled, but not used here.&bslash;n&quot;
)paren
suffix:semicolon
macro_line|#endif
multiline_comment|/* Note, point at the 8390, and not the card... */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|ES_NIC_OFFSET
suffix:semicolon
id|request_region
c_func
(paren
id|ioaddr
op_plus
id|ES_SA_PROM
comma
id|ES_IO_EXTENT
comma
l_string|&quot;es3210&quot;
)paren
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;ES3210&quot;
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|ES_START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|ES_START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|ES_STOP_PG
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
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
id|ei_status.reset_8390
op_assign
op_amp
id|es_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|es_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|es_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|es_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|es_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|es_close
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
)brace
multiline_comment|/*&n; *&t;Reset as per the packet driver method. Judging by the EISA cfg&n; *&t;file, this just toggles the &quot;Board Enable&quot; bits (bit 2 and 0).&n; */
DECL|function|es_reset_8390
r_static
r_void
id|es_reset_8390
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
id|ioaddr
op_assign
id|dev-&gt;base_addr
suffix:semicolon
r_int
r_int
id|end
suffix:semicolon
id|outb
c_func
(paren
l_int|0x04
comma
id|ioaddr
op_plus
id|ES_RESET_PORT
)paren
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
l_string|&quot;%s: resetting the ES3210...&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|end
op_assign
id|jiffies
op_plus
l_int|2
op_star
id|HZ
op_div
l_int|100
suffix:semicolon
r_while
c_loop
(paren
(paren
r_int
)paren
(paren
id|end
op_minus
id|jiffies
)paren
OG
l_int|0
)paren
r_continue
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
op_plus
id|ES_RESET_PORT
)paren
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
l_string|&quot;reset done&bslash;n&quot;
)paren
suffix:semicolon
r_return
suffix:semicolon
)brace
multiline_comment|/*&n; *&t;Note: In the following three functions is the implicit assumption&n; *&t;that the associated memcpy will only use &quot;rep; movsl&quot; as long as&n; *&t;we keep the counts as some multiple of doublewords. This is a&n; *&t;requirement of the hardware, and also prevents us from using&n; *&t;eth_io_copy_and_sum() since we can&squot;t guarantee it will limit&n; *&t;itself to doubleword access.&n; */
multiline_comment|/*&n; *&t;Grab the 8390 specific header. Similar to the block_input routine, but&n; *&t;we don&squot;t need to be concerned with ring wrap as the header will be at&n; *&t;the start of a page, so we optimize accordingly. (A single doubleword.)&n; */
r_static
r_void
DECL|function|es_get_8390_hdr
id|es_get_8390_hdr
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
r_int
id|hdr_start
op_assign
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|ring_page
op_minus
id|ES_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|hdr
comma
id|hdr_start
comma
r_sizeof
(paren
r_struct
id|e8390_pkt_hdr
)paren
)paren
suffix:semicolon
id|hdr-&gt;count
op_assign
(paren
id|hdr-&gt;count
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* Round up allocation. */
)brace
multiline_comment|/*&n; *&t;Block input and output are easy on shared memory ethercards, the only&n; *&t;complication is when the ring buffer wraps. The count will already&n; *&t;be rounded up to a doubleword value via es_get_8390_hdr() above.&n; */
DECL|function|es_block_input
r_static
r_void
id|es_block_input
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
r_int
r_int
id|xfer_start
op_assign
id|dev-&gt;mem_start
op_plus
id|ring_offset
op_minus
(paren
id|ES_START_PG
op_lshift
l_int|8
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfer_start
op_plus
id|count
OG
id|dev-&gt;rmem_end
)paren
(brace
multiline_comment|/* Packet wraps over end of ring buffer. */
r_int
id|semi_count
op_assign
id|dev-&gt;rmem_end
op_minus
id|xfer_start
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|skb-&gt;data
comma
id|xfer_start
comma
id|semi_count
)paren
suffix:semicolon
id|count
op_sub_assign
id|semi_count
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|skb-&gt;data
op_plus
id|semi_count
comma
id|dev-&gt;rmem_start
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Packet is in one chunk. */
id|isa_eth_io_copy_and_sum
c_func
(paren
id|skb
comma
id|xfer_start
comma
id|count
comma
l_int|0
)paren
suffix:semicolon
)brace
)brace
DECL|function|es_block_output
r_static
r_void
id|es_block_output
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
r_int
id|start_page
)paren
(brace
r_int
r_int
id|shmem
op_assign
id|dev-&gt;mem_start
op_plus
(paren
(paren
id|start_page
op_minus
id|ES_START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|count
op_assign
(paren
id|count
op_plus
l_int|3
)paren
op_amp
op_complement
l_int|3
suffix:semicolon
multiline_comment|/* Round up to doubleword */
id|isa_memcpy_toio
c_func
(paren
id|shmem
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
DECL|function|es_open
r_static
r_int
id|es_open
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
id|MOD_INC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|es_close
r_static
r_int
id|es_close
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|macro|MAX_ES_CARDS
mdefine_line|#define MAX_ES_CARDS&t;4&t;/* Max number of ES3210 cards per module */
DECL|macro|NAMELEN
mdefine_line|#define NAMELEN&t;&t;8&t;/* # of chars for storing dev-&gt;name */
DECL|variable|dev_es3210
r_static
r_struct
id|net_device
id|dev_es3210
(braket
id|MAX_ES_CARDS
)braket
op_assign
(brace
(brace
l_string|&quot;&quot;
comma
multiline_comment|/* device name is inserted by net_init.c */
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
l_int|NULL
)brace
comma
)brace
suffix:semicolon
DECL|variable|io
r_static
r_int
id|io
(braket
id|MAX_ES_CARDS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|irq
r_static
r_int
id|irq
(braket
id|MAX_ES_CARDS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|mem
r_static
r_int
id|mem
(braket
id|MAX_ES_CARDS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|io
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_ES_CARDS
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
id|MAX_ES_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
id|MODULE_PARM
c_func
(paren
id|mem
comma
l_string|&quot;1-&quot;
id|__MODULE_STRING
c_func
(paren
id|MAX_ES_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
r_int
DECL|function|init_module
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
r_if
c_cond
(paren
id|load_8390_module
c_func
(paren
l_string|&quot;es3210.c&quot;
)paren
)paren
r_return
op_minus
id|ENOSYS
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
id|MAX_ES_CARDS
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
id|dev_es3210
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
id|dev-&gt;base_addr
op_assign
id|io
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;mem_start
op_assign
id|mem
(braket
id|this_dev
)braket
suffix:semicolon
multiline_comment|/* Currently ignored by driver */
id|dev-&gt;init
op_assign
id|es_probe
suffix:semicolon
multiline_comment|/* Default is to only install one card. */
r_if
c_cond
(paren
id|io
(braket
id|this_dev
)braket
op_eq
l_int|0
op_logical_and
id|this_dev
op_ne
l_int|0
)paren
r_break
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
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;es3210.c: No es3210 card found (i/o = 0x%x).&bslash;n&quot;
comma
id|io
(braket
id|this_dev
)braket
)paren
suffix:semicolon
r_if
c_cond
(paren
id|found
op_ne
l_int|0
)paren
(brace
multiline_comment|/* Got at least one. */
r_return
l_int|0
suffix:semicolon
)brace
id|unload_8390_module
c_func
(paren
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
r_void
DECL|function|cleanup_module
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
id|MAX_ES_CARDS
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
id|dev_es3210
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
r_void
op_star
id|priv
op_assign
id|dev-&gt;priv
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
id|ES_IO_EXTENT
)paren
suffix:semicolon
id|unregister_netdev
c_func
(paren
id|dev
)paren
suffix:semicolon
id|kfree
c_func
(paren
id|priv
)paren
suffix:semicolon
)brace
)brace
id|unload_8390_module
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
