multiline_comment|/* smc-ultra.c: A SMC Ultra ethernet driver for linux. */
multiline_comment|/*&n;    Most of this driver, except for ultramca_probe is nearly&n;    verbatim from smc-ultra.c by Donald Becker. The rest is&n;    written and copyright 1996 by David Weis, weisd3458@uni.edu&n;&n;    This is a driver for the SMC Ultra and SMC EtherEZ ethercards.&n;&n;    This driver uses the cards in the 8390-compatible, shared memory mode.&n;    Most of the run-time complexity is handled by the generic code in&n;    8390.c.  The code in this file is responsible for&n;&n;    This driver enables the shared memory only when doing the actual data&n;    transfers to avoid a bug in early version of the card that corrupted&n;    data transferred by a AHA1542.&n;&n;    This driver does not support the programmed-I/O data transfer mode of&n;    the EtherEZ.  That support (if available) is smc-ez.c.  Nor does it&n;    use the non-8390-compatible &quot;Altego&quot; mode. (No support currently planned.)&n;&n;    Changelog:&n;&n;    Paul Gortmaker  : multiple card support for module users.&n;    David Weis      : Micro Channel-ized it.&n;&n;*/
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
macro_line|#include &quot;smc-mca.h&quot;
macro_line|#include &lt;linux/mca.h&gt;
r_int
id|ultramca_probe
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
id|ultramca_open
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
id|ultramca_reset_8390
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
id|ultramca_get_8390_hdr
c_func
(paren
r_struct
id|device
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
id|ultramca_block_input
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
id|ultramca_block_output
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
suffix:semicolon
r_static
r_int
id|ultramca_close_card
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
DECL|macro|START_PG
mdefine_line|#define START_PG        0x00    /* First page of TX buffer */
DECL|macro|ULTRA_CMDREG
mdefine_line|#define ULTRA_CMDREG 0      /* Offset to ASIC command register. */
DECL|macro|ULTRA_RESET
mdefine_line|#define ULTRA_RESET  0x80   /* Board reset, in ULTRA_CMDREG. */
DECL|macro|ULTRA_MEMENB
mdefine_line|#define ULTRA_MEMENB 0x40   /* Enable the shared memory. */
DECL|macro|ULTRA_NIC_OFFSET
mdefine_line|#define ULTRA_NIC_OFFSET 16 /* NIC register offset from the base_addr. */
DECL|macro|ULTRA_IO_EXTENT
mdefine_line|#define ULTRA_IO_EXTENT 32
DECL|macro|EN0_ERWCNT
mdefine_line|#define EN0_ERWCNT      0x08  /* Early receive warning count. */
DECL|function|__initfunc
id|__initfunc
c_func
(paren
r_int
id|ultramca_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
)paren
(brace
r_int
r_int
id|ioaddr
suffix:semicolon
r_int
r_char
id|reg4
comma
id|num_pages
suffix:semicolon
r_char
id|slot
suffix:semicolon
r_int
r_char
id|pos2
comma
id|pos3
comma
id|pos4
comma
id|pos5
suffix:semicolon
r_int
id|i
suffix:semicolon
multiline_comment|/* Look for two flavors of SMC Elite/A (3013EP/A) -jeh- */
r_if
c_cond
(paren
(paren
(paren
id|slot
op_assign
id|mca_find_adapter
c_func
(paren
l_int|0x61c8
comma
l_int|0
)paren
)paren
op_ne
id|MCA_NOTFOUND
)paren
op_logical_or
(paren
(paren
id|slot
op_assign
id|mca_find_adapter
c_func
(paren
l_int|0xefd5
comma
l_int|0
)paren
)paren
op_ne
id|MCA_NOTFOUND
)paren
)paren
(brace
macro_line|#ifndef MODULE
id|mca_set_adapter_name
c_func
(paren
id|slot
comma
l_string|&quot;SMC Elite/A (8013EP/A)&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_if
c_cond
(paren
(paren
id|slot
op_assign
id|mca_find_adapter
c_func
(paren
l_int|0x61c9
comma
l_int|0
)paren
)paren
op_ne
id|MCA_NOTFOUND
)paren
(brace
macro_line|#ifndef MODULE
id|mca_set_adapter_name
c_func
(paren
id|slot
comma
l_string|&quot;SMC Elite10T/A (8013WP/A)&quot;
)paren
suffix:semicolon
macro_line|#endif
)brace
r_else
r_return
op_minus
id|ENODEV
suffix:semicolon
id|pos2
op_assign
id|mca_read_stored_pos
c_func
(paren
id|slot
comma
l_int|2
)paren
suffix:semicolon
multiline_comment|/* IO range */
id|pos3
op_assign
id|mca_read_stored_pos
c_func
(paren
id|slot
comma
l_int|3
)paren
suffix:semicolon
multiline_comment|/* shared mem */
id|pos4
op_assign
id|mca_read_stored_pos
c_func
(paren
id|slot
comma
l_int|4
)paren
suffix:semicolon
multiline_comment|/* bios base */
id|pos5
op_assign
id|mca_read_stored_pos
c_func
(paren
id|slot
comma
l_int|5
)paren
suffix:semicolon
multiline_comment|/* irq and media */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_assign
id|addr_table
(braket
id|pos2
op_rshift
l_int|4
)braket
dot
id|base_addr
suffix:semicolon
id|dev-&gt;irq
op_assign
id|irq_table
(braket
(paren
id|pos5
op_amp
op_complement
id|IRQ_MASK
)paren
op_rshift
l_int|2
)braket
dot
id|irq
suffix:semicolon
id|dev-&gt;mem_start
op_assign
l_int|0
suffix:semicolon
id|num_pages
op_assign
l_int|40
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
l_int|15
suffix:semicolon
id|i
op_increment
)paren
(brace
r_if
c_cond
(paren
id|mem_table
(braket
id|i
)braket
dot
id|mem_index
op_eq
(paren
id|pos3
op_amp
op_complement
id|MEM_MASK
)paren
)paren
(brace
id|dev-&gt;mem_start
op_assign
id|mem_table
(braket
id|i
)braket
dot
id|mem_start
suffix:semicolon
id|num_pages
op_assign
id|mem_table
(braket
id|i
)braket
dot
id|num_pages
suffix:semicolon
)brace
)brace
r_if
c_cond
(paren
id|dev-&gt;mem_start
op_eq
l_int|0
)paren
multiline_comment|/* sanity check, shouldn&squot;t happen */
r_return
op_minus
id|ENODEV
suffix:semicolon
id|reg4
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|4
)paren
op_amp
l_int|0x7f
suffix:semicolon
id|outb
c_func
(paren
id|reg4
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: SMC Ultra MCA at %#3x,&quot;
comma
id|dev-&gt;name
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
l_int|6
suffix:semicolon
id|i
op_increment
)paren
id|printk
c_func
(paren
l_string|&quot; %2.2X&quot;
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
l_int|8
op_plus
id|i
)paren
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Switch from the station address to the alternate register set and&n;&t; *&t;read the useful registers there.&n;&t; */
id|outb
c_func
(paren
l_int|0x80
op_or
id|reg4
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Enable FINE16 mode to avoid BIOS ROM width mismatches @ reboot.&n;&t; */
id|outb
c_func
(paren
l_int|0x80
op_or
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0x0c
)paren
comma
id|ioaddr
op_plus
l_int|0x0c
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Switch back to the station address register set so that the MS-DOS driver&n;&t; *&t;can find the card after a warm boot.&n;&t; */
id|outb
c_func
(paren
id|reg4
comma
id|ioaddr
op_plus
l_int|4
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;Allocate dev-&gt;priv and fill in 8390 specific dev fields.&n;&t; */
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
l_string|&quot;, no memory for dev-&gt;priv.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/*&n;&t; *&t;OK, we are certain this is going to work.  Setup the device.&n;&t; */
id|request_region
c_func
(paren
id|ioaddr
comma
id|ULTRA_IO_EXTENT
comma
l_string|&quot;smc-mca&quot;
)paren
suffix:semicolon
multiline_comment|/*&n;&t; *&t;The 8390 isn&squot;t at the base address, so fake the offset&n;&t; */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|ULTRA_NIC_OFFSET
suffix:semicolon
id|ei_status.name
op_assign
l_string|&quot;SMC Ultra MCA&quot;
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|ei_status.tx_start_page
op_assign
id|START_PG
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|START_PG
op_plus
id|TX_PAGES
suffix:semicolon
id|ei_status.stop_page
op_assign
id|num_pages
suffix:semicolon
id|dev-&gt;rmem_start
op_assign
id|dev-&gt;mem_start
op_plus
id|TX_PAGES
op_star
l_int|256
suffix:semicolon
id|dev-&gt;mem_end
op_assign
id|dev-&gt;rmem_end
op_assign
id|dev-&gt;mem_start
op_plus
(paren
id|ei_status.stop_page
op_minus
id|START_PG
)paren
op_star
l_int|256
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, IRQ %d memory %#lx-%#lx.&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
op_minus
l_int|1
)paren
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|ultramca_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ultramca_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ultramca_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ultramca_get_8390_hdr
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ultramca_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ultramca_close_card
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
DECL|function|ultramca_open
r_static
r_int
id|ultramca_open
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
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
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
id|ei_status.name
comma
id|dev
)paren
)paren
r_return
op_minus
id|EAGAIN
suffix:semicolon
id|outb
c_func
(paren
id|ULTRA_MEMENB
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Enable memory */
id|outb
c_func
(paren
l_int|0x80
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* ??? */
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts and memory. */
id|outb
c_func
(paren
l_int|0x04
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* ??? */
multiline_comment|/*&n;&t; *&t;Set the early receive warning level in window 0 high enough not&n;&t; *&t;to receive ERW interrupts.&n;&t; */
multiline_comment|/*&n;&t; *&t;outb_p(E8390_NODMA+E8390_PAGE0, dev-&gt;base_addr);&n;&t; *&t;outb(0xff, dev-&gt;base_addr + EN0_ERWCNT);&n;&t; */
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
DECL|function|ultramca_reset_8390
r_static
r_void
id|ultramca_reset_8390
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
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
id|outb
c_func
(paren
id|ULTRA_RESET
comma
id|ioaddr
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
l_string|&quot;resetting Ultra, t=%ld...&quot;
comma
id|jiffies
)paren
suffix:semicolon
id|ei_status.txing
op_assign
l_int|0
suffix:semicolon
id|outb
c_func
(paren
l_int|0x80
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* ??? */
id|outb
c_func
(paren
l_int|0x01
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Enable interrupts and memory. */
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
multiline_comment|/* Grab the 8390 specific header. Similar to the block_input routine, but&n;   we don&squot;t need to be concerned with ring wrap as the header will be at&n;   the start of a page, so we optimize accordingly. */
DECL|function|ultramca_get_8390_hdr
r_static
r_void
id|ultramca_get_8390_hdr
c_func
(paren
r_struct
id|device
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
id|START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
macro_line|#ifdef notdef
multiline_comment|/* Officially this is what we are doing, but the readl() is faster */
id|memcpy_fromio
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
macro_line|#else
(paren
(paren
r_int
r_int
op_star
)paren
id|hdr
)paren
(braket
l_int|0
)braket
op_assign
id|readl
c_func
(paren
id|hdr_start
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Block input and output are easy on shared memory ethercards, the only&n;   complication is when the ring buffer wraps. */
DECL|function|ultramca_block_input
r_static
r_void
id|ultramca_block_input
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
id|START_PG
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
multiline_comment|/* We must wrap the input move. */
r_int
id|semi_count
op_assign
id|dev-&gt;rmem_end
op_minus
id|xfer_start
suffix:semicolon
id|memcpy_fromio
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
id|memcpy_fromio
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
multiline_comment|/* Packet is in one chunk -- we can copy + cksum. */
id|eth_io_copy_and_sum
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
DECL|function|ultramca_block_output
r_static
r_void
id|ultramca_block_output
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
id|START_PG
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
id|memcpy_toio
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
DECL|function|ultramca_close_card
r_static
r_int
id|ultramca_close_card
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
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
id|dev-&gt;start
op_assign
l_int|0
suffix:semicolon
id|dev-&gt;tbusy
op_assign
l_int|1
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
l_string|&quot;%s: Shutting down ethercard.&bslash;n&quot;
comma
id|dev-&gt;name
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Disable interrupts. */
id|free_irq
c_func
(paren
id|dev-&gt;irq
comma
id|dev
)paren
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* We should someday disable shared memory and change to 8-bit mode&n;       &quot;just in case&quot;... */
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
macro_line|#ifdef MODULE
DECL|macro|MODULE
macro_line|#undef MODULE        /* don&squot;t want to bother now! */
DECL|macro|MAX_ULTRAMCA_CARDS
mdefine_line|#define MAX_ULTRAMCA_CARDS  4   /* Max number of Ultra cards per module */
DECL|macro|NAMELEN
mdefine_line|#define NAMELEN     8   /* # of chars for storing dev-&gt;name */
DECL|variable|namelist
r_static
r_char
id|namelist
(braket
id|NAMELEN
op_star
id|MAX_ULTRAMCA_CARDS
)braket
op_assign
(brace
l_int|0
comma
)brace
suffix:semicolon
DECL|variable|dev_ultra
r_static
r_struct
id|device
id|dev_ultra
(braket
id|MAX_ULTRAMCA_CARDS
)braket
op_assign
(brace
(brace
l_int|NULL
comma
multiline_comment|/* assign a chunk of namelist[] below */
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
id|MAX_ULTRAMCA_CARDS
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
id|MAX_ULTRAMCA_CARDS
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
id|MAX_ULTRAMCA_CARDS
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
id|MAX_ULTRAMCA_CARDS
)paren
l_string|&quot;i&quot;
)paren
suffix:semicolon
multiline_comment|/* This is set up so that only a single autoprobe takes place per call.&n;ISA device autoprobes on a running machine are not recommended. */
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
id|MAX_ULTRAMCA_CARDS
suffix:semicolon
id|this_dev
op_increment
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
op_amp
id|dev_ultra
(braket
id|this_dev
)braket
suffix:semicolon
id|dev-&gt;name
op_assign
id|namelist
op_plus
(paren
id|NAMELEN
op_star
id|this_dev
)paren
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
id|dev-&gt;init
op_assign
id|ultramca_probe
suffix:semicolon
r_if
c_cond
(paren
id|io
(braket
id|this_dev
)braket
op_eq
l_int|0
)paren
(brace
r_if
c_cond
(paren
id|this_dev
op_ne
l_int|0
)paren
r_break
suffix:semicolon
multiline_comment|/* only autoprobe 1st one */
id|printk
c_func
(paren
id|KERN_NOTICE
l_string|&quot;smc-mca.c: Presently autoprobing (not recommended) for a single card.&bslash;n&quot;
)paren
suffix:semicolon
)brace
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
l_string|&quot;smc-mca.c: No SMC Ultra card found (i/o = 0x%x).&bslash;n&quot;
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
r_return
l_int|0
suffix:semicolon
multiline_comment|/* Got at least one. */
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
id|MAX_ULTRAMCA_CARDS
suffix:semicolon
id|this_dev
op_increment
)paren
(brace
r_struct
id|device
op_star
id|dev
op_assign
op_amp
id|dev_ultra
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
multiline_comment|/* NB: ultra_close_card() does free_irq */
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
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
id|dev-&gt;priv
)paren
suffix:semicolon
id|dev-&gt;priv
op_assign
l_int|NULL
suffix:semicolon
id|release_region
c_func
(paren
id|ioaddr
comma
id|ULTRA_IO_EXTENT
)paren
suffix:semicolon
)brace
)brace
)brace
macro_line|#endif /* MODULE */
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -Wall -O6 -I/usr/src/linux/net/inet -c smc-mca.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 8&n; *  tab-width: 8&n; * End:&n; */
eof
