multiline_comment|/* &t;smc-ultra32.c: An SMC Ultra32 EISA ethernet driver for linux.&n;&n;Sources:&n;&n;&t;This driver is based on (cloned from) the ISA SMC Ultra driver&n;&t;written by Donald Becker. Modifications to support the EISA&n;&t;version of the card by Paul Gortmaker and Leonard N. Zubkoff.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU Public License, incorporated herein by reference.&n;&n;Theory of Operation:&n;&n;&t;The SMC Ultra32C card uses the SMC 83c790 chip which is also&n;&t;found on the ISA SMC Ultra cards. It has a shared memory mode of&n;&t;operation that makes it similar to the ISA version of the card.&n;&t;The main difference is that the EISA card has 32KB of RAM, but&n;&t;only an 8KB window into that memory. The EISA card also can be&n;&t;set for a bus-mastering mode of operation via the ECU, but that&n;&t;is not (and probably will never be) supported by this driver.&n;&t;The ECU should be run to enable shared memory and to disable the&n;&t;bus-mastering feature for use with linux.&n;&n;&t;By programming the 8390 to use only 8KB RAM, the modifications&n;&t;to the ISA driver can be limited to the probe and initialization&n;&t;code. This allows easy integration of EISA support into the ISA&n;&t;driver. However, the driver development kit from SMC provided the&n;&t;register information for sliding the 8KB window, and hence the 8390&n;&t;is programmed to use the full 32KB RAM.&n;&n;&t;Unfortunately this required code changes outside the probe/init&n;&t;routines, and thus we decided to separate the EISA driver from&n;&t;the ISA one. In this way, ISA users don&squot;t end up with a larger&n;&t;driver due to the EISA code, and EISA users don&squot;t end up with a&n;&t;larger driver due to the ISA EtherEZ PIO code. The driver is&n;&t;similar to the 3c503/16 driver, in that the window must be set&n;&t;back to the 1st 8KB of space for access to the two 8390 Tx slots.&n;&n;&t;In testing, using only 8KB RAM (3 Tx / 5 Rx) didn&squot;t appear to&n;&t;be a limiting factor, since the EISA bus could get packets off&n;&t;the card fast enough, but having the use of lots of RAM as Rx&n;&t;space is extra insurance if interrupt latencies become excessive.&n;&n;*/
DECL|variable|version
r_static
r_const
r_char
op_star
id|version
op_assign
l_string|&quot;smc-ultra32.c: 06/97 v1.00&bslash;n&quot;
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
id|ultra32_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|ultra32_probe1
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
id|ultra32_open
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
id|ultra32_reset_8390
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
id|ultra32_get_8390_hdr
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
id|ultra32_block_input
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
id|ultra32_block_output
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
suffix:semicolon
r_static
r_int
id|ultra32_close
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
DECL|macro|ULTRA32_CMDREG
mdefine_line|#define ULTRA32_CMDREG&t;0&t;/* Offset to ASIC command register. */
DECL|macro|ULTRA32_RESET
mdefine_line|#define&t; ULTRA32_RESET&t;0x80&t;/* Board reset, in ULTRA32_CMDREG. */
DECL|macro|ULTRA32_MEMENB
mdefine_line|#define&t; ULTRA32_MEMENB&t;0x40&t;/* Enable the shared memory. */
DECL|macro|ULTRA32_NIC_OFFSET
mdefine_line|#define ULTRA32_NIC_OFFSET 16&t;/* NIC register offset from the base_addr. */
DECL|macro|ULTRA32_IO_EXTENT
mdefine_line|#define ULTRA32_IO_EXTENT 32
DECL|macro|EN0_ERWCNT
mdefine_line|#define EN0_ERWCNT&t;&t;0x08&t;/* Early receive warning count. */
multiline_comment|/*&n; * Defines that apply only to the Ultra32 EISA card. Note that&n; * &quot;smc&quot; = 10011 01101 00011 = 0x4da3, and hence !smc8010.cfg translates&n; * into an EISA ID of 0x1080A34D&n; */
DECL|macro|ULTRA32_BASE
mdefine_line|#define ULTRA32_BASE&t;0xca0
DECL|macro|ULTRA32_ID
mdefine_line|#define ULTRA32_ID&t;0x1080a34d
DECL|macro|ULTRA32_IDPORT
mdefine_line|#define ULTRA32_IDPORT&t;(-0x20)&t;/* 0xc80 */
multiline_comment|/* Config regs 1-&gt;7 from the EISA !SMC8010.CFG file. */
DECL|macro|ULTRA32_CFG1
mdefine_line|#define ULTRA32_CFG1&t;0x04&t;/* 0xca4 */
DECL|macro|ULTRA32_CFG2
mdefine_line|#define ULTRA32_CFG2&t;0x05&t;/* 0xca5 */
DECL|macro|ULTRA32_CFG3
mdefine_line|#define ULTRA32_CFG3&t;(-0x18)&t;/* 0xc88 */
DECL|macro|ULTRA32_CFG4
mdefine_line|#define ULTRA32_CFG4&t;(-0x17)&t;/* 0xc89 */
DECL|macro|ULTRA32_CFG5
mdefine_line|#define ULTRA32_CFG5&t;(-0x16)&t;/* 0xc8a */
DECL|macro|ULTRA32_CFG6
mdefine_line|#define ULTRA32_CFG6&t;(-0x15)&t;/* 0xc8b */
DECL|macro|ULTRA32_CFG7
mdefine_line|#define ULTRA32_CFG7&t;0x0d&t;/* 0xcad */
multiline_comment|/*&t;Probe for the Ultra32.  This looks like a 8013 with the station&n;&t;address PROM at I/O ports &lt;base&gt;+8 to &lt;base&gt;+13, with a checksum&n;&t;following.&n;*/
DECL|function|ultra32_probe
r_int
id|__init
id|ultra32_probe
c_func
(paren
r_struct
id|net_device
op_star
id|dev
)paren
(brace
r_const
r_char
op_star
id|ifmap
(braket
)braket
op_assign
(brace
l_string|&quot;UTP No Link&quot;
comma
l_string|&quot;&quot;
comma
l_string|&quot;UTP/AUI&quot;
comma
l_string|&quot;UTP/BNC&quot;
)brace
suffix:semicolon
r_int
id|ioaddr
comma
id|edge
comma
id|media
suffix:semicolon
r_if
c_cond
(paren
op_logical_neg
id|EISA_bus
)paren
r_return
id|ENODEV
suffix:semicolon
multiline_comment|/* EISA spec allows for up to 16 slots, but 8 is typical. */
r_for
c_loop
(paren
id|ioaddr
op_assign
l_int|0x1000
op_plus
id|ULTRA32_BASE
suffix:semicolon
id|ioaddr
OL
l_int|0x9000
suffix:semicolon
id|ioaddr
op_add_assign
l_int|0x1000
)paren
r_if
c_cond
(paren
id|check_region
c_func
(paren
id|ioaddr
comma
id|ULTRA32_IO_EXTENT
)paren
op_eq
l_int|0
op_logical_and
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_IDPORT
)paren
op_ne
l_int|0xff
op_logical_and
id|inl
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_IDPORT
)paren
op_eq
id|ULTRA32_ID
)paren
(brace
id|media
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_CFG7
)paren
op_amp
l_int|0x03
suffix:semicolon
id|edge
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_CFG5
)paren
op_amp
l_int|0x08
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;SMC Ultra32 in EISA Slot %d, Media: %s, %s IRQs.&bslash;n&quot;
comma
id|ioaddr
op_rshift
l_int|12
comma
id|ifmap
(braket
id|media
)braket
comma
(paren
id|edge
ques
c_cond
l_string|&quot;Edge Triggered&quot;
suffix:colon
l_string|&quot;Level Sensitive&quot;
)paren
)paren
suffix:semicolon
r_if
c_cond
(paren
id|ultra32_probe1
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
DECL|function|ultra32_probe1
r_int
id|__init
id|ultra32_probe1
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
id|checksum
op_assign
l_int|0
suffix:semicolon
r_const
r_char
op_star
id|model_name
suffix:semicolon
r_static
r_int
id|version_printed
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Values from various config regs. */
r_int
r_char
id|idreg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|7
)paren
suffix:semicolon
r_int
r_char
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
multiline_comment|/* Check the ID nibble. */
r_if
c_cond
(paren
(paren
id|idreg
op_amp
l_int|0xf0
)paren
op_ne
l_int|0x20
)paren
multiline_comment|/* SMC Ultra */
r_return
id|ENODEV
suffix:semicolon
multiline_comment|/* Select the station address register set. */
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
id|checksum
op_add_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|8
op_plus
id|i
)paren
suffix:semicolon
r_if
c_cond
(paren
(paren
id|checksum
op_amp
l_int|0xff
)paren
op_ne
l_int|0xff
)paren
r_return
id|ENODEV
suffix:semicolon
r_if
c_cond
(paren
id|load_8390_module
c_func
(paren
l_string|&quot;smc-ultra32.c&quot;
)paren
)paren
r_return
op_minus
id|ENOSYS
suffix:semicolon
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
l_string|&quot;smc-ultra32.c: Passed a NULL device.&bslash;n&quot;
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
id|model_name
op_assign
l_string|&quot;SMC Ultra32&quot;
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: %s at 0x%X,&quot;
comma
id|dev-&gt;name
comma
id|model_name
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
multiline_comment|/* Switch from the station address to the alternate register set and&n;&t;   read the useful registers there. */
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
multiline_comment|/* Enable FINE16 mode to avoid BIOS ROM width mismatches @ reboot. */
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
multiline_comment|/* Reset RAM addr. */
id|outb
c_func
(paren
l_int|0x00
comma
id|ioaddr
op_plus
l_int|0x0b
)paren
suffix:semicolon
multiline_comment|/* Switch back to the station address register set so that the&n;&t;   MS-DOS driver can find the card after a warm boot. */
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
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_CFG5
)paren
op_amp
l_int|0x40
)paren
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;&bslash;nsmc-ultra32: Card RAM is disabled!  &quot;
l_string|&quot;Run EISA config utility.&bslash;n&quot;
)paren
suffix:semicolon
r_return
id|ENODEV
suffix:semicolon
)brace
r_if
c_cond
(paren
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_CFG2
)paren
op_amp
l_int|0x04
)paren
op_eq
l_int|0
)paren
id|printk
c_func
(paren
l_string|&quot;&bslash;nsmc-ultra32: Ignoring Bus-Master enable bit.  &quot;
l_string|&quot;Run EISA config utility.&bslash;n&quot;
)paren
suffix:semicolon
r_if
c_cond
(paren
id|dev-&gt;irq
OL
l_int|2
)paren
(brace
r_int
r_char
id|irqmap
(braket
)braket
op_assign
(brace
l_int|0
comma
l_int|9
comma
l_int|3
comma
l_int|5
comma
l_int|7
comma
l_int|10
comma
l_int|11
comma
l_int|15
)brace
suffix:semicolon
r_int
id|irq
op_assign
id|irqmap
(braket
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_CFG5
)paren
op_amp
l_int|0x07
)braket
suffix:semicolon
r_if
c_cond
(paren
id|irq
op_eq
l_int|0
)paren
(brace
id|printk
c_func
(paren
l_string|&quot;, failed to detect IRQ line.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|EAGAIN
suffix:semicolon
)brace
id|dev-&gt;irq
op_assign
id|irq
suffix:semicolon
)brace
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
l_string|&quot;, no memory for dev-&gt;priv.&bslash;n&quot;
)paren
suffix:semicolon
r_return
op_minus
id|ENOMEM
suffix:semicolon
)brace
multiline_comment|/* OK, we are certain this is going to work.  Setup the device. */
id|request_region
c_func
(paren
id|ioaddr
comma
id|ULTRA32_IO_EXTENT
comma
id|model_name
)paren
suffix:semicolon
multiline_comment|/* The 8390 isn&squot;t at the base address, so fake the offset */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|ULTRA32_NIC_OFFSET
suffix:semicolon
multiline_comment|/* Save RAM address in the unused reg0 to avoid excess inb&squot;s. */
id|ei_status.reg0
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_CFG3
)paren
op_amp
l_int|0xfc
suffix:semicolon
id|dev-&gt;mem_start
op_assign
l_int|0xc0000
op_plus
(paren
(paren
id|ei_status.reg0
op_amp
l_int|0x7c
)paren
op_lshift
l_int|11
)paren
suffix:semicolon
id|ei_status.name
op_assign
id|model_name
suffix:semicolon
id|ei_status.word16
op_assign
l_int|1
suffix:semicolon
id|ei_status.tx_start_page
op_assign
l_int|0
suffix:semicolon
id|ei_status.rx_start_page
op_assign
id|TX_PAGES
suffix:semicolon
multiline_comment|/* All Ultra32 cards have 32KB memory with an 8KB window. */
id|ei_status.stop_page
op_assign
l_int|128
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
l_int|0x1fff
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;, IRQ %d, 32KB memory, 8KB window at 0x%lx-0x%lx.&bslash;n&quot;
comma
id|dev-&gt;irq
comma
id|dev-&gt;mem_start
comma
id|dev-&gt;mem_end
)paren
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ultra32_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ultra32_block_output
suffix:semicolon
id|ei_status.get_8390_hdr
op_assign
op_amp
id|ultra32_get_8390_hdr
suffix:semicolon
id|ei_status.reset_8390
op_assign
op_amp
id|ultra32_reset_8390
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ultra32_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ultra32_close
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
DECL|function|ultra32_open
r_static
r_int
id|ultra32_open
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
op_minus
id|ULTRA32_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC addr */
r_int
id|irq_flags
op_assign
(paren
id|inb
c_func
(paren
id|ioaddr
op_plus
id|ULTRA32_CFG5
)paren
op_amp
l_int|0x08
)paren
ques
c_cond
l_int|0
suffix:colon
id|SA_SHIRQ
suffix:semicolon
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
id|irq_flags
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
id|ULTRA32_MEMENB
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Enable Shared Memory. */
id|outb
c_func
(paren
l_int|0x80
comma
id|ioaddr
op_plus
id|ULTRA32_CFG6
)paren
suffix:semicolon
multiline_comment|/* Enable Interrupts. */
id|outb
c_func
(paren
l_int|0x84
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Enable MEM16 &amp; Disable Bus Master. */
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
multiline_comment|/* Enable Interrupts. */
multiline_comment|/* Set the early receive warning level in window 0 high enough not&n;&t;   to receive ERW interrupts. */
id|outb_p
c_func
(paren
id|E8390_NODMA
op_plus
id|E8390_PAGE0
comma
id|dev-&gt;base_addr
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0xff
comma
id|dev-&gt;base_addr
op_plus
id|EN0_ERWCNT
)paren
suffix:semicolon
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
DECL|function|ultra32_close
r_static
r_int
id|ultra32_close
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
op_minus
id|ULTRA32_NIC_OFFSET
suffix:semicolon
multiline_comment|/* CMDREG */
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
id|ULTRA32_CFG6
)paren
suffix:semicolon
multiline_comment|/* Disable Interrupts. */
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
id|MOD_DEC_USE_COUNT
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
DECL|function|ultra32_reset_8390
r_static
r_void
id|ultra32_reset_8390
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
op_minus
id|ULTRA32_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC base addr */
id|outb
c_func
(paren
id|ULTRA32_RESET
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
l_string|&quot;resetting Ultra32, t=%ld...&quot;
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
id|ULTRA32_MEMENB
comma
id|ioaddr
)paren
suffix:semicolon
multiline_comment|/* Enable Shared Memory. */
id|outb
c_func
(paren
l_int|0x80
comma
id|ioaddr
op_plus
id|ULTRA32_CFG6
)paren
suffix:semicolon
multiline_comment|/* Enable Interrupts. */
id|outb
c_func
(paren
l_int|0x84
comma
id|ioaddr
op_plus
l_int|5
)paren
suffix:semicolon
multiline_comment|/* Enable MEM16 &amp; Disable Bus Master. */
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
multiline_comment|/* Enable Interrupts. */
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
DECL|function|ultra32_get_8390_hdr
r_static
r_void
id|ultra32_get_8390_hdr
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
op_amp
l_int|0x1f
)paren
op_lshift
l_int|8
)paren
suffix:semicolon
r_int
r_int
id|RamReg
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA32_NIC_OFFSET
op_plus
id|ULTRA32_CFG3
suffix:semicolon
multiline_comment|/* Select correct 8KB Window. */
id|outb
c_func
(paren
id|ei_status.reg0
op_or
(paren
(paren
id|ring_page
op_amp
l_int|0x60
)paren
op_rshift
l_int|5
)paren
comma
id|RamReg
)paren
suffix:semicolon
macro_line|#ifdef notdef
multiline_comment|/* Officially this is what we are doing, but the readl() is faster */
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
id|isa_readl
c_func
(paren
id|hdr_start
)paren
suffix:semicolon
macro_line|#endif
)brace
multiline_comment|/* Block input and output are easy on shared memory ethercards, the only&n;   complication is when the ring buffer wraps, or in this case, when a&n;   packet spans an 8KB boundary. Note that the current 8KB segment is&n;   already set by the get_8390_hdr routine. */
DECL|function|ultra32_block_input
r_static
r_void
id|ultra32_block_input
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
(paren
id|ring_offset
op_amp
l_int|0x1fff
)paren
suffix:semicolon
r_int
r_int
id|RamReg
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA32_NIC_OFFSET
op_plus
id|ULTRA32_CFG3
suffix:semicolon
r_if
c_cond
(paren
(paren
id|ring_offset
op_amp
op_complement
l_int|0x1fff
)paren
op_ne
(paren
(paren
id|ring_offset
op_plus
id|count
op_minus
l_int|1
)paren
op_amp
op_complement
l_int|0x1fff
)paren
)paren
(brace
r_int
id|semi_count
op_assign
l_int|8192
op_minus
(paren
id|ring_offset
op_amp
l_int|0x1FFF
)paren
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
r_if
c_cond
(paren
id|ring_offset
OL
l_int|96
op_star
l_int|256
)paren
(brace
multiline_comment|/* Select next 8KB Window. */
id|ring_offset
op_add_assign
id|semi_count
suffix:semicolon
id|outb
c_func
(paren
id|ei_status.reg0
op_or
(paren
(paren
id|ring_offset
op_amp
l_int|0x6000
)paren
op_rshift
l_int|13
)paren
comma
id|RamReg
)paren
suffix:semicolon
id|isa_memcpy_fromio
c_func
(paren
id|skb-&gt;data
op_plus
id|semi_count
comma
id|dev-&gt;mem_start
comma
id|count
)paren
suffix:semicolon
)brace
r_else
(brace
multiline_comment|/* Select first 8KB Window. */
id|outb
c_func
(paren
id|ei_status.reg0
comma
id|RamReg
)paren
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
)brace
r_else
(brace
multiline_comment|/* Packet is in one chunk -- we can copy + cksum. */
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
DECL|function|ultra32_block_output
r_static
r_void
id|ultra32_block_output
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
id|xfer_start
op_assign
id|dev-&gt;mem_start
op_plus
(paren
id|start_page
op_lshift
l_int|8
)paren
suffix:semicolon
r_int
r_int
id|RamReg
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA32_NIC_OFFSET
op_plus
id|ULTRA32_CFG3
suffix:semicolon
multiline_comment|/* Select first 8KB Window. */
id|outb
c_func
(paren
id|ei_status.reg0
comma
id|RamReg
)paren
suffix:semicolon
id|isa_memcpy_toio
c_func
(paren
id|xfer_start
comma
id|buf
comma
id|count
)paren
suffix:semicolon
)brace
"&f;"
macro_line|#ifdef MODULE
DECL|macro|MAX_ULTRA32_CARDS
mdefine_line|#define MAX_ULTRA32_CARDS   4&t;/* Max number of Ultra cards per module */
DECL|macro|NAMELEN
mdefine_line|#define NAMELEN&t;&t;    8&t;/* # of chars for storing dev-&gt;name */
DECL|variable|namelist
r_static
r_char
id|namelist
(braket
id|NAMELEN
op_star
id|MAX_ULTRA32_CARDS
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
id|net_device
id|dev_ultra
(braket
id|MAX_ULTRA32_CARDS
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
id|MAX_ULTRA32_CARDS
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
id|dev-&gt;init
op_assign
id|ultra32_probe
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
OG
l_int|0
)paren
(brace
multiline_comment|/* Got at least one. */
id|lock_8390_module
c_func
(paren
)paren
suffix:semicolon
r_return
l_int|0
suffix:semicolon
)brace
id|printk
c_func
(paren
id|KERN_WARNING
l_string|&quot;smc-ultra32.c: No SMC Ultra32 found.&bslash;n&quot;
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
id|lock_8390_module
c_func
(paren
)paren
suffix:semicolon
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
id|MAX_ULTRA32_CARDS
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
r_int
id|ioaddr
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA32_NIC_OFFSET
suffix:semicolon
r_void
op_star
id|priv
op_assign
id|dev-&gt;priv
suffix:semicolon
multiline_comment|/* NB: ultra32_close_card() does free_irq */
id|release_region
c_func
(paren
id|ioaddr
comma
id|ULTRA32_IO_EXTENT
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
id|unlock_8390_module
c_func
(paren
)paren
suffix:semicolon
)brace
macro_line|#endif /* MODULE */
eof
