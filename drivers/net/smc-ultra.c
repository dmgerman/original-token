multiline_comment|/* smc-ultra.c: A SMC Ultra ethernet driver for linux. */
multiline_comment|/*&n;&t;Written 1993-94 by Donald Becker.&n;&n;&t;Copyright 1993 United States Government as represented by the&n;&t;Director, National Security Agency.&n;&n;&t;This software may be used and distributed according to the terms&n;&t;of the GNU Public License, incorporated herein by reference.&n;&n;&t;The author may be reached as becker@CESDIS.gsfc.nasa.gov, or C/O&n;&t;Center of Excellence in Space Data and Information Sciences&n;&t;&t;Code 930.5, Goddard Space Flight Center, Greenbelt MD 20771&n;&n;&t;This is a driver for the SMC Ultra ethercard.&n;&n;*/
DECL|variable|version
r_static
r_char
op_star
id|version
op_assign
l_string|&quot;smc-ultra.c:v1.11 11/21/94 Donald Becker (becker@cesdis.gsfc.nasa.gov)&bslash;n&quot;
suffix:semicolon
macro_line|#include &lt;linux/kernel.h&gt;
macro_line|#include &lt;linux/sched.h&gt;
macro_line|#include &lt;linux/errno.h&gt;
macro_line|#include &lt;linux/string.h&gt;
macro_line|#include &lt;asm/io.h&gt;
macro_line|#include &lt;asm/system.h&gt;
macro_line|#include &lt;linux/netdevice.h&gt;
macro_line|#include &quot;8390.h&quot;
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
multiline_comment|/* A zero-terminated list of I/O addresses to be probed. */
DECL|variable|ultra_portlist
r_static
r_int
r_int
id|ultra_portlist
(braket
)braket
op_assign
(brace
l_int|0x200
comma
l_int|0x220
comma
l_int|0x240
comma
l_int|0x280
comma
l_int|0x300
comma
l_int|0x340
comma
l_int|0x380
comma
l_int|0
)brace
suffix:semicolon
r_int
id|ultra_probe
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
r_int
id|ultra_probe1
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
id|ultra_open
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
id|ultra_reset_8390
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
id|ultra_block_input
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
id|ultra_block_output
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
id|start_page
)paren
suffix:semicolon
r_static
r_int
id|ultra_close_card
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
suffix:semicolon
"&f;"
DECL|macro|START_PG
mdefine_line|#define START_PG&t;&t;0x00&t;/* First page of TX buffer */
DECL|macro|ULTRA_CMDREG
mdefine_line|#define ULTRA_CMDREG&t;0&t;&t;/* Offset to ASIC command register. */
DECL|macro|ULTRA_RESET
mdefine_line|#define&t; ULTRA_RESET&t;0x80&t;/* Board reset, in ULTRA_CMDREG. */
DECL|macro|ULTRA_MEMENB
mdefine_line|#define&t; ULTRA_MEMENB&t;0x40&t;/* Enable the shared memory. */
DECL|macro|ULTRA_NIC_OFFSET
mdefine_line|#define ULTRA_NIC_OFFSET  16&t;/* NIC register offset from the base_addr. */
DECL|macro|ULTRA_IO_EXTENT
mdefine_line|#define ULTRA_IO_EXTENT 32
"&f;"
multiline_comment|/*&t;Probe for the Ultra.  This looks like a 8013 with the station&n;&t;address PROM at I/O ports &lt;base&gt;+8 to &lt;base&gt;+13, with a checksum&n;&t;following.&n;*/
macro_line|#ifdef HAVE_DEVLIST
DECL|variable|ultra_drv
r_struct
id|netdev_entry
id|ultra_drv
op_assign
(brace
l_string|&quot;ultra&quot;
comma
id|ultra_probe1
comma
id|NETCARD_IO_EXTENT
comma
id|netcard_portlist
)brace
suffix:semicolon
macro_line|#else
DECL|function|ultra_probe
r_int
id|ultra_probe
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
id|ultra_probe1
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
id|ultra_portlist
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
id|ultra_portlist
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
id|ULTRA_IO_EXTENT
)paren
)paren
r_continue
suffix:semicolon
r_if
c_cond
(paren
id|ultra_probe1
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
DECL|function|ultra_probe1
r_int
id|ultra_probe1
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
r_int
id|i
suffix:semicolon
r_int
id|checksum
op_assign
l_int|0
suffix:semicolon
r_char
op_star
id|model_name
suffix:semicolon
r_int
r_char
id|eeprom_irq
op_assign
l_int|0
suffix:semicolon
multiline_comment|/* Values from various config regs. */
r_int
r_char
id|num_pages
comma
id|irqreg
comma
id|addr
comma
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
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|7
)paren
op_amp
l_int|0xF0
)paren
op_ne
l_int|0x20
)paren
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
l_int|0xFF
)paren
r_return
id|ENODEV
suffix:semicolon
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
id|ei_device
)paren
comma
l_int|0
)paren
suffix:semicolon
id|printk
c_func
(paren
l_string|&quot;%s: SMC Ultra at %#3x,&quot;
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
multiline_comment|/* Enabled FINE16 mode to avoid BIOS ROM width mismatches @ reboot. */
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
id|irqreg
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0xd
)paren
suffix:semicolon
id|addr
op_assign
id|inb
c_func
(paren
id|ioaddr
op_plus
l_int|0xb
)paren
suffix:semicolon
multiline_comment|/* Switch back to the station address register set so that the MS-DOS driver&n;&t;   can find the card after a warm boot. */
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
id|model_name
op_assign
l_string|&quot;SMC Ultra&quot;
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
suffix:semicolon
multiline_comment|/* The IRQ bits are split. */
id|irq
op_assign
id|irqmap
(braket
(paren
(paren
id|irqreg
op_amp
l_int|0x40
)paren
op_rshift
l_int|4
)paren
op_plus
(paren
(paren
id|irqreg
op_amp
l_int|0x0c
)paren
op_rshift
l_int|2
)paren
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
id|eeprom_irq
op_assign
l_int|1
suffix:semicolon
)brace
multiline_comment|/* OK, were are certain this is going to work.  Setup the device. */
id|register_iomem
c_func
(paren
id|ioaddr
comma
l_int|32
comma
l_string|&quot;smc-ultra&quot;
)paren
suffix:semicolon
multiline_comment|/* The 8390 isn&squot;t at the base address, so fake the offset */
id|dev-&gt;base_addr
op_assign
id|ioaddr
op_plus
id|ULTRA_NIC_OFFSET
suffix:semicolon
(brace
r_int
id|addr_tbl
(braket
l_int|4
)braket
op_assign
(brace
l_int|0x0C0000
comma
l_int|0x0E0000
comma
l_int|0xFC0000
comma
l_int|0xFE0000
)brace
suffix:semicolon
r_int
id|num_pages_tbl
(braket
l_int|4
)braket
op_assign
(brace
l_int|0x20
comma
l_int|0x40
comma
l_int|0x80
comma
l_int|0xff
)brace
suffix:semicolon
id|dev-&gt;mem_start
op_assign
(paren
(paren
id|addr
op_amp
l_int|0x0f
)paren
op_lshift
l_int|13
)paren
op_plus
id|addr_tbl
(braket
(paren
id|addr
op_rshift
l_int|6
)paren
op_amp
l_int|3
)braket
suffix:semicolon
id|num_pages
op_assign
id|num_pages_tbl
(braket
(paren
id|addr
op_rshift
l_int|4
)paren
op_amp
l_int|3
)braket
suffix:semicolon
)brace
id|ethdev_init
c_func
(paren
id|dev
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
l_string|&quot;,%s IRQ %d memory %#lx-%#lx.&bslash;n&quot;
comma
id|eeprom_irq
ques
c_cond
l_string|&quot;&quot;
suffix:colon
l_string|&quot;assigned &quot;
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
id|ultra_reset_8390
suffix:semicolon
id|ei_status.block_input
op_assign
op_amp
id|ultra_block_input
suffix:semicolon
id|ei_status.block_output
op_assign
op_amp
id|ultra_block_output
suffix:semicolon
id|dev-&gt;open
op_assign
op_amp
id|ultra_open
suffix:semicolon
id|dev-&gt;stop
op_assign
op_amp
id|ultra_close_card
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
r_static
r_int
DECL|function|ultra_open
id|ultra_open
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
l_string|&quot;SMC Ultra&quot;
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
multiline_comment|/* Enable memory, 16 bit mode. */
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
r_return
id|ei_open
c_func
(paren
id|dev
)paren
suffix:semicolon
)brace
r_static
r_void
DECL|function|ultra_reset_8390
id|ultra_reset_8390
c_func
(paren
r_struct
id|device
op_star
id|dev
)paren
(brace
r_int
id|cmd_port
op_assign
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
suffix:semicolon
multiline_comment|/* ASIC base addr */
id|outb
c_func
(paren
id|ULTRA_RESET
comma
id|cmd_port
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
id|ULTRA_MEMENB
comma
id|cmd_port
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
multiline_comment|/* Block input and output are easy on shared memory ethercards, the only&n;   complication is when the ring buffer wraps. */
r_static
r_int
DECL|function|ultra_block_input
id|ultra_block_input
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
r_void
op_star
id|xfer_start
op_assign
(paren
r_void
op_star
)paren
(paren
id|dev-&gt;mem_start
op_plus
id|ring_offset
op_minus
(paren
id|START_PG
op_lshift
l_int|8
)paren
)paren
suffix:semicolon
multiline_comment|/* Enable shared memory. */
id|outb
c_func
(paren
id|ULTRA_MEMENB
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
r_if
c_cond
(paren
id|xfer_start
op_plus
id|count
OG
(paren
r_void
op_star
)paren
id|dev-&gt;rmem_end
)paren
(brace
multiline_comment|/* We must wrap the input move. */
r_int
id|semi_count
op_assign
(paren
r_void
op_star
)paren
id|dev-&gt;rmem_end
op_minus
id|xfer_start
suffix:semicolon
id|memcpy
c_func
(paren
id|buf
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
id|memcpy
c_func
(paren
id|buf
op_plus
id|semi_count
comma
(paren
r_char
op_star
)paren
id|dev-&gt;rmem_start
comma
id|count
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Disable memory. */
r_return
id|dev-&gt;rmem_start
op_plus
id|count
suffix:semicolon
)brace
id|memcpy
c_func
(paren
id|buf
comma
id|xfer_start
comma
id|count
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Disable memory. */
r_return
id|ring_offset
op_plus
id|count
suffix:semicolon
)brace
r_static
r_void
DECL|function|ultra_block_output
id|ultra_block_output
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
r_char
op_star
id|shmem
op_assign
(paren
r_int
r_char
op_star
)paren
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
multiline_comment|/* Enable shared memory. */
id|outb
c_func
(paren
id|ULTRA_MEMENB
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
id|memcpy
c_func
(paren
id|shmem
comma
id|buf
comma
id|count
)paren
suffix:semicolon
id|outb
c_func
(paren
l_int|0x00
comma
id|dev-&gt;base_addr
op_minus
id|ULTRA_NIC_OFFSET
)paren
suffix:semicolon
multiline_comment|/* Disable memory. */
)brace
r_static
r_int
DECL|function|ultra_close_card
id|ultra_close_card
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
l_int|6
)paren
suffix:semicolon
multiline_comment|/* Disable interrupts. */
id|free_irq
c_func
(paren
id|dev-&gt;irq
)paren
suffix:semicolon
id|irq2dev_map
(braket
id|dev-&gt;irq
)braket
op_assign
l_int|0
suffix:semicolon
id|NS8390_init
c_func
(paren
id|dev
comma
l_int|0
)paren
suffix:semicolon
multiline_comment|/* We should someday disable shared memory and change to 8-bit mode&n;&t;   &quot;just in case&quot;... */
r_return
l_int|0
suffix:semicolon
)brace
"&f;"
multiline_comment|/*&n; * Local variables:&n; *  compile-command: &quot;gcc -D__KERNEL__ -Wall -O6 -I/usr/src/linux/net/inet -c smc-ultra.c&quot;&n; *  version-control: t&n; *  kept-new-versions: 5&n; *  c-indent-level: 4&n; *  tab-width: 4&n; * End:&n; */
eof
